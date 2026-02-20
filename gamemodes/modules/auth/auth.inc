/*
 *  Vibe Roleplay - Auth Module
 *  File: modules/auth/auth.inc
 *
 *  Sistem autentikasi: login, register, validasi nama.
 *  Flow: OnPlayerConnect → cek DB → register/login → spawn.
 */

#if defined _auth_included
    #endinput
#endif
#define _auth_included

// Include auth callbacks
#include "auth_callbacks.inc"

// ============================================================================
//  Dialog Display Functions
// ============================================================================

stock ShowRegisterDialog(playerid)
{
    new caption[64], info[256];

    format(caption, sizeof(caption), "%s — Register", SERVER_NAME);
    format(info, sizeof(info), \
        EC_WHITE "Selamat datang di " EC_PRIMARY "%s" EC_WHITE "!\n\n"\
        "Akun dengan nama ini belum terdaftar.\n"\
        "Silakan buat password untuk mendaftar.\n\n"\
        EC_GREY "Password minimal %d karakter.",
        SERVER_NAME, MIN_PASSWORD_LENGTH
    );

    ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD,
        caption, info, "Daftar", "Keluar");
    
    PlayerData[playerid][pRegistering] = true;
    return 1;
}

stock ShowRegisterConfirmDialog(playerid)
{
    new caption[64], info[128];

    format(caption, sizeof(caption), "%s — Konfirmasi Password", SERVER_NAME);
    format(info, sizeof(info),
        EC_WHITE "Ketik ulang password kamu untuk konfirmasi."
    );

    ShowPlayerDialog(playerid, DIALOG_REGISTER_CONFIRM, DIALOG_STYLE_PASSWORD,
        caption, info, "Konfirmasi", "Kembali");
    return 1;
}

stock ShowLoginDialog(playerid)
{
    new caption[64], info[256];
    new remaining = MAX_LOGIN_ATTEMPTS - PlayerData[playerid][pLoginAttempts];

    format(caption, sizeof(caption), "%s — Login", SERVER_NAME);
    format(info, sizeof(info),
        EC_WHITE "Selamat datang kembali di " EC_PRIMARY "%s" EC_WHITE "!\n\n"\
        "Masukkan password kamu untuk login.\n\n"\
        EC_GREY "Sisa percobaan: %d/%d",
        SERVER_NAME, remaining, MAX_LOGIN_ATTEMPTS
    );

    ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD,
        caption, info, "Login", "Keluar");
    return 1;
}

// ============================================================================
//  Hooks
// ============================================================================

hook OnPlayerConnect(playerid)
{
    // Reset data pemain
    ResetPlayerData(playerid);

    // Validasi nama roleplay
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    if (!IsValidRoleplayName(name))
    {
        SendErrorMessage(playerid, "Nama kamu tidak sesuai format roleplay.");
        SendInfoMessage(playerid, "Format yang benar: Nama_Belakang (contoh: Denmas_Molano)");
        SetTimerEx("KickPlayerDelay", 1000, false, "i", playerid);
        return 1;
    }

    // Cek apakah akun sudah terdaftar di database
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
    // Simpan data jika sudah login
    if (PlayerData[playerid][pLoggedIn])
    {
        // Ambil posisi terakhir
        GetPlayerPos(playerid,
            PlayerData[playerid][pPosX],
            PlayerData[playerid][pPosY],
            PlayerData[playerid][pPosZ]
        );
        GetPlayerFacingAngle(playerid, PlayerData[playerid][pPosA]);
        PlayerData[playerid][pInterior] = GetPlayerInterior(playerid);
        PlayerData[playerid][pVirtualWorld] = GetPlayerVirtualWorld(playerid);
        PlayerData[playerid][pMoney] = GetPlayerMoney(playerid);
        PlayerData[playerid][pSkin] = GetPlayerSkin(playerid);

        // Simpan ke database
        new query[512];
        mysql_format(g_MySQL, query, sizeof(query),
            "UPDATE `players` SET \
                `skin` = %d, \
                `money` = %d, \
                `level` = %d, \
                `pos_x` = %f, \
                `pos_y` = %f, \
                `pos_z` = %f, \
                `pos_a` = %f, \
                `interior` = %d, \
                `virtual_world` = %d \
            WHERE `id` = %d",
            PlayerData[playerid][pSkin],
            PlayerData[playerid][pMoney],
            PlayerData[playerid][pLevel],
            PlayerData[playerid][pPosX],
            PlayerData[playerid][pPosY],
            PlayerData[playerid][pPosZ],
            PlayerData[playerid][pPosA],
            PlayerData[playerid][pInterior],
            PlayerData[playerid][pVirtualWorld],
            PlayerData[playerid][pID]
        );
        mysql_tquery(g_MySQL, query, "OnPlayerDataSave", "i", playerid);
    }

    ResetPlayerData(playerid);
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch (dialogid)
    {
        // ====================================================================
        //  REGISTER — Input password pertama kali
        // ====================================================================
        case DIALOG_REGISTER:
        {
            if (!response)
            {
                // Klik "Keluar" — kick
                SendErrorMessage(playerid, "Kamu harus mendaftar untuk bermain.");
                SetTimerEx("KickPlayerDelay", 500, false, "i", playerid);
                return 1;
            }

            // Validasi panjang password
            if (strlen(inputtext) < MIN_PASSWORD_LENGTH)
            {
                new msg[128];
                format(msg, sizeof(msg), "Password terlalu pendek! Minimal %d karakter.", MIN_PASSWORD_LENGTH);
                SendErrorMessage(playerid, msg);
                ShowRegisterDialog(playerid);
                return 1;
            }

            if (strlen(inputtext) > MAX_PASSWORD_LENGTH)
            {
                new msg[128];
                format(msg, sizeof(msg), "Password terlalu panjang! Maksimal %d karakter.", MAX_PASSWORD_LENGTH);
                SendErrorMessage(playerid, msg);
                ShowRegisterDialog(playerid);
                return 1;
            }

            // Simpan password sementara, minta konfirmasi
            strcat(PlayerData[playerid][pTempPassword], inputtext, MAX_PASSWORD_LENGTH + 1);
            ShowRegisterConfirmDialog(playerid);
            return 1;
        }

        // ====================================================================
        //  REGISTER CONFIRM — Konfirmasi password
        // ====================================================================
        case DIALOG_REGISTER_CONFIRM:
        {
            if (!response)
            {
                // Klik "Kembali" — kembali ke dialog register
                PlayerData[playerid][pTempPassword][0] = EOS;
                ShowRegisterDialog(playerid);
                return 1;
            }

            // Cek kecocokan password
            if (strcmp(PlayerData[playerid][pTempPassword], inputtext, false) != 0)
            {
                SendErrorMessage(playerid, "Password tidak cocok! Silakan ulangi.");
                PlayerData[playerid][pTempPassword][0] = EOS;
                ShowRegisterDialog(playerid);
                return 1;
            }

            // Password cocok — hash dengan bcrypt
            SendInfoMessage(playerid, "Memproses registrasi...");
            bcrypt_hash(playerid, "OnPasswordHash", inputtext, BCRYPT_COST);

            // Hapus password sementara dari memory
            PlayerData[playerid][pTempPassword][0] = EOS;
            return 1;
        }

        // ====================================================================
        //  LOGIN — Input password
        // ====================================================================
        case DIALOG_LOGIN:
        {
            if (!response)
            {
                // Klik "Keluar" — kick
                SendErrorMessage(playerid, "Kamu harus login untuk bermain.");
                SetTimerEx("KickPlayerDelay", 500, false, "i", playerid);
                return 1;
            }

            // Validasi input kosong
            if (strlen(inputtext) < 1)
            {
                SendErrorMessage(playerid, "Masukkan password kamu.");
                ShowLoginDialog(playerid);
                return 1;
            }

            // Verifikasi password dengan bcrypt
            SendInfoMessage(playerid, "Memverifikasi password...");
            bcrypt_verify(playerid, "OnPasswordVerify", inputtext, PlayerData[playerid][pPassword]);
            return 1;
        }
    }
    return 0;
}

hook OnPlayerRequestClass(playerid, classid)
{
    // Jangan tampilkan class selection — langsung freeze
    if (!PlayerData[playerid][pLoggedIn])
    {
        // Pemain belum login, tetap di layar gelap
        TogglePlayerSpectating(playerid, true);
        return 0;
    }
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if (!PlayerData[playerid][pLoggedIn])
    {
        // Jangan spawn jika belum login — ini seharusnya tidak terjadi
        TogglePlayerSpectating(playerid, true);
        return 0;
    }
    return 1;
}

hook OnPlayerText(playerid, text[])
{
    // Disable chat — server ini menggunakan voice chat
    SendInfoMessage(playerid, "Chat dinonaktifkan. Gunakan voice chat untuk berkomunikasi.");
    return 0;
}

// ============================================================================
//  GameMode Init Hook — Inisialisasi regex dan server settings
// ============================================================================

hook OnGameModeInit()
{
    // Inisialisasi name validator
    NameValidator_Init();

    // Server settings
    SetGameModeText("Vibe RP v" SERVER_VERSION);
    ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
    ShowNameTags(1);
    SetNameTagDrawDistance(30.0);
    EnableStuntBonusForAll(0);
    DisableInteriorEnterExits();
    ManualVehicleEngineAndLights();
    UsePlayerPedAnims();

    // Tambahkan class default (diperlukan oleh SA-MP)
    AddPlayerClass(0, DEFAULT_SPAWN_X, DEFAULT_SPAWN_Y, DEFAULT_SPAWN_Z,
        DEFAULT_SPAWN_A, 0, 0, 0, 0, 0, 0);

    printf("[GAMEMODE] %s v%s berhasil dimuat.", SERVER_NAME, SERVER_VERSION);
    return 1;
}

hook OnGameModeExit()
{
    NameValidator_Destroy();
    return 1;
}
