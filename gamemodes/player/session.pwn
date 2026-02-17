// session.pwn — Auth lifecycle + login cinematic camera
// Depends on: data.pwn, query_builder.pwn, validator.pwn

#if defined _PLAYER_SESSION_PWN
    #endinput
#endif
#define _PLAYER_SESSION_PWN

// ─── Connect ──────────────────────────────────────────────────────────────────
hook OnPlayerConnect(playerid) {
    Player_Reset(playerid);
    GetPlayerName(playerid, g_Player[playerid][p_Name], MAX_PLAYER_NAME);
    g_Player[playerid][p_ConnectTime] = gettime();

    // Setup tampilan sinematik pedesaan sebelum dialog muncul
    Session_SetupLoginScreen(playerid);

    printf("[Auth] Connect  id=%d  name=%s", playerid, g_Player[playerid][p_Name]);
    DB_CheckAccount(playerid);
    return 1;
}

// ─── Setup kamera sinematik — Flint County countryside ────────────────────────
//     Sembunyikan player, atur kamera ke pemandangan pedesaan SA-MP
stock Session_SetupLoginScreen(playerid) {
    // Isolasi player ke virtual world unik — tidak terlihat player lain
    SetPlayerVirtualWorld(playerid, 5000 + playerid);
    SetPlayerInterior(playerid, 0);

    // Letakkan karakter jauh di bawah peta — tidak ada yang melihat
    SetPlayerPos(playerid, LOGIN_CAM_POS_X, LOGIN_CAM_POS_Y, LOGIN_HIDE_Z);

    // Freeze: player tidak bisa gerak sebelum login
    TogglePlayerControllable(playerid, false);

    // Kamera sinematik menghadap ladang Flint County
    // CAMERA_CUT = snap langsung (tidak ada transisi)
    SetPlayerCameraPos(playerid,
        LOGIN_CAM_POS_X, LOGIN_CAM_POS_Y, LOGIN_CAM_POS_Z);
    SetPlayerCameraLookAt(playerid,
        LOGIN_CAM_LOOK_X, LOGIN_CAM_LOOK_Y, LOGIN_CAM_LOOK_Z,
        CAMERA_CUT);

    // Hilangkan jam SA-MP bawaan
    TogglePlayerClock(playerid, false);
}

// ─── Disconnect ───────────────────────────────────────────────────────────────
hook OnPlayerDisconnect(playerid, reason) {
    if (g_Player[playerid][p_LoggedIn]) {
        DB_SaveAccount(playerid);
        printf("[Auth] Disconnect  name=%s  reason=%d  online=%ds",
            g_Player[playerid][p_Name],
            reason,
            gettime() - g_Player[playerid][p_ConnectTime]
        );
    }
    HUD_Destroy(playerid);
    Player_Reset(playerid);
    return 1;
}

// ─── Bcrypt: selesai hash password baru (register) ───────────────────────────
forward OnHashDone(playerid);
public  OnHashDone(playerid) {
    if (!IsPlayerConnected(playerid)) return 1;
    bcrypt_get_hash(g_Player[playerid][p_Hash]);
    DB_InsertAccount(playerid);
    return 1;
}

// ─── Bcrypt: selesai verify password (login) ─────────────────────────────────
forward OnVerifyDone(playerid, bool:success);
public  OnVerifyDone(playerid, bool:success) {
    if (!IsPlayerConnected(playerid)) return 1;

    if (!success) {
        g_Player[playerid][p_Tries]++;
        new remaining = MAX_LOGIN_TRIES - g_Player[playerid][p_Tries];

        if (remaining <= 0) {
            SendClientMessage(playerid, COL_RED,
                "  {FF4444}[!] {FFFFFF}Terlalu banyak percobaan. Anda di-kick.");
            Player_Kick(playerid);
            return 1;
        }
        // Tampilkan dialog login lagi dengan pesan error
        Dialog_ShowLogin(playerid, true, remaining);
        return 1;
    }

    DB_LoadAccount(playerid);
    return 1;
}
