// data.pwn — Global player array + getters/setters
// Harus di-include PERTAMA dari semua player/*.pwn
// Depends on: core/enums.pwn

#if defined _PLAYER_DATA_PWN
    #endinput
#endif
#define _PLAYER_DATA_PWN

// Array global — bukan static agar visible di semua modul
new g_Player[MAX_PLAYERS][E_PLAYER];

// Reset semua field ke default
stock Player_Reset(playerid) {
    g_Player[playerid][p_DbId]        = 0;
    g_Player[playerid][p_LoggedIn]    = false;
    g_Player[playerid][p_Tries]       = 0;
    g_Player[playerid][p_Level]       = 1;
    g_Player[playerid][p_Money]       = SPAWN_CASH;
    g_Player[playerid][p_Bank]        = 0;
    g_Player[playerid][p_Admin]       = 0;
    g_Player[playerid][p_Banned]      = false;
    g_Player[playerid][p_ConnectTime] = 0;
    g_Player[playerid][p_Hunger]      = 100;
    g_Player[playerid][p_Thirst]      = 100;
    g_Player[playerid][p_Name][0]     = EOS;
    g_Player[playerid][p_Hash][0]     = EOS;
}

// Dipanggil setelah DB load berhasil
// Player_DoSpawn() ada di player/spawning.pwn (include setelah data.pwn)
forward Player_DoSpawn(playerid);

stock Player_FinishLogin(playerid) {
    g_Player[playerid][p_LoggedIn] = true;

    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, g_Player[playerid][p_Money]);

    SendClientMessage(playerid, COL_GREEN,
        "[VRP] Login berhasil! Ketik /help untuk daftar perintah.");

    // Panggil Player_DoSpawn (bukan SpawnPlayer langsung)
    // Player_DoSpawn memanggil SetSpawnInfo dulu baru SpawnPlayer
    Player_DoSpawn(playerid);
}

// Kick dengan delay 100ms — cegah crash on connect
stock Player_Kick(playerid) {
    SetTimerEx("_CB_KickDelay", 100, false, "d", playerid);
}

forward _CB_KickDelay(playerid);
public _CB_KickDelay(playerid) {
    if (IsPlayerConnected(playerid)) Kick(playerid);
}

// Getters
stock bool:Player_IsLoggedIn(playerid) { return g_Player[playerid][p_LoggedIn]; }
stock       Player_GetAdmin(playerid)  { return g_Player[playerid][p_Admin];    }
stock       Player_GetLevel(playerid)  { return g_Player[playerid][p_Level];    }
stock       Player_GetMoney(playerid)  { return g_Player[playerid][p_Money];    }

// Money helpers
stock Player_SetMoney(playerid, amount) {
    g_Player[playerid][p_Money] = amount;
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, amount);
}

stock Player_GiveMoney(playerid, amount) {
    g_Player[playerid][p_Money] += amount;
    GivePlayerMoney(playerid, amount);
}
