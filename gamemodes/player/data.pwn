// player/data.pwn — Global player array + helpers dasar
// HARUS di-include PERTAMA dari semua player/*.pwn
// Depends on: core/enums.pwn, core/config.pwn

#if defined _PLAYER_DATA_PWN
    #endinput
#endif
#define _PLAYER_DATA_PWN

new g_Player[MAX_PLAYERS][E_PLAYER];

// =============================================================================
// RESET
// =============================================================================
stock Player_Reset(playerid) {
    g_Player[playerid][p_DbId]          = 0;
    g_Player[playerid][p_Name][0]       = EOS;
    g_Player[playerid][p_Hash][0]       = EOS;

    g_Player[playerid][p_LoggedIn]      = false;
    g_Player[playerid][p_Tries]         = 0;

    g_Player[playerid][p_Level]         = 1;
    g_Player[playerid][p_Money]         = SPAWN_CASH;
    g_Player[playerid][p_Bank]          = 0;
    g_Player[playerid][p_Admin]         = 0;
    g_Player[playerid][p_Banned]        = false;
    g_Player[playerid][p_BanReason][0]  = EOS;

    // Pakai dedicated bool — tidak ada ambiguitas koordinat 0,0
    g_Player[playerid][p_HasLastPos]    = false;
    g_Player[playerid][p_LastX]         = 0.0;
    g_Player[playerid][p_LastY]         = 0.0;
    g_Player[playerid][p_LastZ]         = 0.0;
    g_Player[playerid][p_LastA]         = 0.0;
    g_Player[playerid][p_LastInterior]  = 0;
    g_Player[playerid][p_LastWorld]     = 0;

    g_Player[playerid][p_Hunger]        = NEEDS_MAX;
    g_Player[playerid][p_Thirst]        = NEEDS_MAX;

    g_Player[playerid][p_IsDead]        = false;
    g_Player[playerid][p_SpawnProt]     = false;

    g_Player[playerid][p_ConnectTime]   = 0;
}

// =============================================================================
// FINISH LOGIN
// =============================================================================
forward Player_DoSpawn(playerid);

stock Player_FinishLogin(playerid) {
    g_Player[playerid][p_LoggedIn] = true;

    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, g_Player[playerid][p_Money]);

    SendClientMessage(playerid, COL_GREEN,
        "  {44FF44}[v] {FFFFFF}Login berhasil. Selamat datang!");

    Player_DoSpawn(playerid);
}

// =============================================================================
// KICK (delayed 100ms — cegah crash on connect)
// =============================================================================
stock Player_Kick(playerid) {
    SetTimerEx("_CB_KickDelay", 100, false, "d", playerid);
}

forward _CB_KickDelay(playerid);
public  _CB_KickDelay(playerid) {
    if (IsPlayerConnected(playerid)) Kick(playerid);
}

// =============================================================================
// SAVE POSISI — dipanggil dari DB_SaveAccount
// =============================================================================
stock Player_SavePosition(playerid) {
    if (!IsPlayerConnected(playerid)) return;
    if (g_Player[playerid][p_IsDead])  return; // jangan save posisi saat mati

    GetPlayerPos(playerid,
        g_Player[playerid][p_LastX],
        g_Player[playerid][p_LastY],
        g_Player[playerid][p_LastZ]);
    GetPlayerFacingAngle(playerid, g_Player[playerid][p_LastA]);
    g_Player[playerid][p_LastInterior] = GetPlayerInterior(playerid);
    g_Player[playerid][p_LastWorld]    = GetPlayerVirtualWorld(playerid);
    g_Player[playerid][p_HasLastPos]   = true;
}

// =============================================================================
// DETEKSI PLAYER BARU
// =============================================================================
stock bool:Player_IsFirstSpawn(playerid) {
    return bool:(!g_Player[playerid][p_HasLastPos]);
}

// =============================================================================
// GETTERS / SETTERS
// =============================================================================
stock bool:Player_IsLoggedIn(playerid) { return g_Player[playerid][p_LoggedIn]; }
stock       Player_GetAdmin(playerid)  { return g_Player[playerid][p_Admin];    }
stock       Player_GetLevel(playerid)  { return g_Player[playerid][p_Level];    }
stock       Player_GetMoney(playerid)  { return g_Player[playerid][p_Money];    }

stock Player_SetMoney(playerid, amount) {
    g_Player[playerid][p_Money] = amount;
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, amount);
}

stock Player_GiveMoney(playerid, amount) {
    g_Player[playerid][p_Money] += amount;
    GivePlayerMoney(playerid, amount);
}
