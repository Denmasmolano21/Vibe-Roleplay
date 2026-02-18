// session.pwn — Auth lifecycle + login cinematic camera
// Depends on: data.pwn, query_builder.pwn, validator.pwn

#if defined _PLAYER_SESSION_PWN
    #endinput
#endif
#define _PLAYER_SESSION_PWN

// =============================================================================
// CONNECT
// =============================================================================
hook OnPlayerConnect(playerid) {
    Player_Reset(playerid);
    GetPlayerName(playerid, g_Player[playerid][p_Name], MAX_PLAYER_NAME);
    g_Player[playerid][p_ConnectTime] = gettime();

    Session_SetupLoginScreen(playerid);

    printf("[Auth] Connect  id=%d  name=%s", playerid, g_Player[playerid][p_Name]);
    DB_CheckAccount(playerid);
    return 1;
}

// =============================================================================
// KAMERA SINEMATIK — Flint County countryside
// Player disembunyikan di VW unik, karakter di bawah peta
// =============================================================================
stock Session_SetupLoginScreen(playerid) {
    SetPlayerVirtualWorld(playerid, 5000 + playerid);
    SetPlayerInterior(playerid, 0);
    SetPlayerPos(playerid, LOGIN_CAM_POS_X, LOGIN_CAM_POS_Y, LOGIN_HIDE_Z);
    TogglePlayerControllable(playerid, false);
    TogglePlayerClock(playerid, false);

    SetPlayerCameraPos(playerid,
        LOGIN_CAM_POS_X, LOGIN_CAM_POS_Y, LOGIN_CAM_POS_Z);
    SetPlayerCameraLookAt(playerid,
        LOGIN_CAM_LOOK_X, LOGIN_CAM_LOOK_Y, LOGIN_CAM_LOOK_Z,
        CAMERA_CUT);
}

// =============================================================================
// DISCONNECT
// =============================================================================
hook OnPlayerDisconnect(playerid, reason) {
    if (g_Player[playerid][p_LoggedIn]) {
        // Player_SavePosition dipanggil di dalam DB_SaveAccount
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

// =============================================================================
// BCRYPT CALLBACKS
// =============================================================================

forward OnHashDone(playerid);
public  OnHashDone(playerid) {
    if (!IsPlayerConnected(playerid)) return 1;
    bcrypt_get_hash(g_Player[playerid][p_Hash]);
    DB_InsertAccount(playerid);
    return 1;
}

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
        Dialog_ShowLogin(playerid, true, remaining);
        return 1;
    }

    DB_LoadAccount(playerid);
    return 1;
}
