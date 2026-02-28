/*
 *  Vibe Roleplay - Auth Module
 *  File: modules/auth/auth.inc
 */

#if defined _auth_included
    #endinput
#endif
#define _auth_included

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_iterate>
#include "auth_callbacks.inc"

// ============================================================================
//  Dialog Functions
// ============================================================================

ShowRegisterDialog(playerid)
{
    new caption[64], info[256];
    format(caption, sizeof(caption), "%s — Register", SERVER_NAME);
    format(info, sizeof(info), 
        EC_WHITE "Selamat datang di " EC_PRIMARY "%s" EC_WHITE "!\n\n"\
        "Akun dengan nama ini belum terdaftar.\n"\
        "Silakan buat password untuk mendaftar.\n\n"\
        EC_GREY "Password minimal %d karakter.",
        SERVER_NAME, MIN_PASSWORD_LENGTH
    );

    ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD,
        caption, info, "Daftar", "Keluar");
    
    PlayerData[playerid][pRegistering] = true;
    PlayerData[playerid][pState] = PLAYER_STATE_AUTH;
}

ShowRegisterConfirmDialog(playerid)
{
    new caption[64], info[128];
    format(caption, sizeof(caption), "%s — Konfirmasi Password", SERVER_NAME);
    format(info, sizeof(info), EC_WHITE "Ketik ulang password kamu untuk konfirmasi.");

    ShowPlayerDialog(playerid, DIALOG_REGISTER_CONFIRM, DIALOG_STYLE_PASSWORD,
        caption, info, "Konfirmasi", "Kembali");
}

ShowLoginDialog(playerid)
{
    new caption[64], info[256];
    new remaining = MAX_LOGIN_ATTEMPTS - PlayerData[playerid][pLoginAttempts];

    format(caption, sizeof(caption), "%s — Login", SERVER_NAME);
    format(info, sizeof(info),
        EC_WHITE "Selamat datang kembali di " EC_PRIMARY "%s" EC_WHITE "!\n\n" \
        "Masukkan password kamu untuk login.\n\n" \
        EC_GREY "Sisa percobaan: %d/%d",
        SERVER_NAME, remaining, MAX_LOGIN_ATTEMPTS
    );

    ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD,
        caption, info, "Login", "Keluar");
    
    PlayerData[playerid][pState] = PLAYER_STATE_AUTH;
}

// ============================================================================
//  Hooks
// ============================================================================

hook OnPlayerConnect(playerid)
{
    ResetPlayerData(playerid);
    PlayerData[playerid][pState] = PLAYER_STATE_AUTH;

    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    if (!IsValidRoleplayName(name))
    {
        SendErrorMessage(playerid, "Nama kamu tidak sesuai format roleplay.");
        SendInfoMessage(playerid, "Format yang benar: Nama_Belakang (contoh: Denmas_Molano)");
        SetTimerEx("KickPlayerDelay", 500, false, "i", playerid);
        return 1;
    }

    if (g_MySQL == MYSQL_INVALID_HANDLE)
    {
        SendErrorMessage(playerid, "Server sedang dalam maintenance.");
        SetTimerEx("KickPlayerDelay", 500, false, "i", playerid);
        return 1;
    }

    new query[256];
    mysql_format(g_MySQL, query, sizeof(query),
        "SELECT `id`, `password` FROM `players` WHERE `username` = '%e' LIMIT 1",
        name
    );
    mysql_tquery(g_MySQL, query, "OnPlayerDataCheck", "i", playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if (PlayerData[playerid][pLoggedIn])
    {
        Session_End(playerid);
        SavePlayerDataToDB(playerid);
        Stats_OnPlayerDisconnect(playerid);

        if (PlayerData[playerid][pDeathTimer] != -1)
        {
            KillTimer(PlayerData[playerid][pDeathTimer]);
            PlayerData[playerid][pDeathTimer] = -1;
        }
    }

    ResetPlayerData(playerid);
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch (dialogid)
    {
        case DIALOG_REGISTER:
        {
            if (!response)
            {
                SendErrorMessage(playerid, "Kamu harus mendaftar untuk bermain.");
                SetTimerEx("KickPlayerDelay", 500, false, "i", playerid);
                return 1;
            }

            if (isnull(inputtext))
            {
                SendErrorMessage(playerid, "Password tidak boleh kosong!");
                ShowRegisterDialog(playerid);
                return 1;
            }

            new len = strlen(inputtext);
            if (len < MIN_PASSWORD_LENGTH)
            {
                new msg[128];
                format(msg, sizeof(msg), "Password terlalu pendek! Minimal %d karakter.", MIN_PASSWORD_LENGTH);
                SendErrorMessage(playerid, msg);
                ShowRegisterDialog(playerid);
                return 1;
            }

            if (len > MAX_PASSWORD_LENGTH)
            {
                new msg[128];
                format(msg, sizeof(msg), "Password terlalu panjang! Maksimal %d karakter.", MAX_PASSWORD_LENGTH);
                SendErrorMessage(playerid, msg);
                ShowRegisterDialog(playerid);
                return 1;
            }

            format(PlayerData[playerid][pTempPassword], MAX_PASSWORD_LENGTH + 1, "%s", inputtext);
            ShowRegisterConfirmDialog(playerid);
            return 1;
        }

        case DIALOG_REGISTER_CONFIRM:
        {
            if (!response)
            {
                PlayerData[playerid][pTempPassword][0] = EOS;
                ShowRegisterDialog(playerid);
                return 1;
            }

            if (isnull(inputtext))
            {
                SendErrorMessage(playerid, "Konfirmasi password tidak boleh kosong!");
                ShowRegisterConfirmDialog(playerid);
                return 1;
            }

            if (strcmp(PlayerData[playerid][pTempPassword], inputtext, false) != 0)
            {
                SendErrorMessage(playerid, "Password tidak cocok! Silakan ulangi.");
                PlayerData[playerid][pTempPassword][0] = EOS;
                ShowRegisterDialog(playerid);
                return 1;
            }

            SendInfoMessage(playerid, "Memproses registrasi...");
            bcrypt_hash(playerid, "OnPasswordHash", inputtext, BCRYPT_COST);
            PlayerData[playerid][pTempPassword][0] = EOS;
            return 1;
        }

        case DIALOG_LOGIN:
        {
            if (!response)
            {
                SendErrorMessage(playerid, "Kamu harus login untuk bermain.");
                SetTimerEx("KickPlayerDelay", 500, false, "i", playerid);
                return 1;
            }

            if (isnull(inputtext) || strlen(inputtext) < 1)
            {
                SendErrorMessage(playerid, "Masukkan password kamu.");
                ShowLoginDialog(playerid);
                return 1;
            }

            SendInfoMessage(playerid, "Memverifikasi password...");
            bcrypt_verify(playerid, "OnPasswordVerify", inputtext, PlayerData[playerid][pPassword]);
            return 1;
        }
    }
    return 0;
}

hook OnPlayerText(playerid, text[])
{
    SendInfoMessage(playerid, "Chat dinonaktifkan. Gunakan voice chat untuk berkomunikasi.");
    return 0;
}
