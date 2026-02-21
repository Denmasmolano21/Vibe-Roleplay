/*
 *  Vibe Roleplay - Player Data
 *  File: core/player_data.inc
 *
 *  Struktur data pemain, fungsi reset, spawn, dan economy wrapper.
 *  Semua modul mengakses data pemain dari sini.
 */

#if defined _player_data_included
    #endinput
#endif
#define _player_data_included

// ============================================================================
//  Player Data Enum
// ============================================================================

enum E_PLAYER_DATA
{
    // Database
    pID,
    pPassword[BCRYPT_HASH_LENGTH],

    // Status & State
    bool:pLoggedIn,
    bool:pRegistering,
    pLoginAttempts,
    pTempPassword[MAX_PASSWORD_LENGTH + 1],
    pState,                     // E_PLAYER_STATE

    // Stats
    pSkin,
    pMoney,
    pLevel,
    pHunger,
    pThirst,
    pPlaytime,                  // total menit bermain (persistent)
    pSessionStart,              // GetTickCount() saat login

    // Position
    Float:pPosX,
    Float:pPosY,
    Float:pPosZ,
    Float:pPosA,
    pInterior,
    pVirtualWorld,

    // Death
    pDeathTimer
};

new PlayerData[MAX_PLAYERS][E_PLAYER_DATA];

// ============================================================================
//  Reset Player Data
// ============================================================================

stock ResetPlayerData(playerid)
{
    PlayerData[playerid][pID]               = 0;
    PlayerData[playerid][pPassword][0]      = EOS;
    PlayerData[playerid][pLoggedIn]         = false;
    PlayerData[playerid][pRegistering]      = false;
    PlayerData[playerid][pLoginAttempts]    = 0;
    PlayerData[playerid][pTempPassword][0]  = EOS;
    PlayerData[playerid][pState]            = 0;  // STATE_NONE
    PlayerData[playerid][pSkin]             = DEFAULT_SPAWN_SKIN;
    PlayerData[playerid][pMoney]            = 0;
    PlayerData[playerid][pLevel]            = 1;
    PlayerData[playerid][pHunger]           = DEFAULT_HUNGER;
    PlayerData[playerid][pThirst]           = DEFAULT_THIRST;
    PlayerData[playerid][pPlaytime]         = 0;
    PlayerData[playerid][pSessionStart]     = 0;
    PlayerData[playerid][pPosX]             = DEFAULT_SPAWN_X;
    PlayerData[playerid][pPosY]             = DEFAULT_SPAWN_Y;
    PlayerData[playerid][pPosZ]             = DEFAULT_SPAWN_Z;
    PlayerData[playerid][pPosA]             = DEFAULT_SPAWN_A;
    PlayerData[playerid][pInterior]         = DEFAULT_SPAWN_INTERIOR;
    PlayerData[playerid][pVirtualWorld]     = DEFAULT_SPAWN_VW;
    PlayerData[playerid][pDeathTimer]       = -1;
    return 1;
}

// ============================================================================
//  Spawn Player
// ============================================================================

stock SpawnPlayerAtSavedPosition(playerid)
{
    // Disable spectating mode (digunakan saat menunggu login)
    TogglePlayerSpectating(playerid, false);

    SetSpawnInfo(playerid, 0,
        PlayerData[playerid][pSkin],
        PlayerData[playerid][pPosX],
        PlayerData[playerid][pPosY],
        PlayerData[playerid][pPosZ],
        PlayerData[playerid][pPosA],
        0, 0, 0, 0, 0, 0
    );
    SpawnPlayer(playerid);

    SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
    SetPlayerVirtualWorld(playerid, PlayerData[playerid][pVirtualWorld]);
    VRP_SetPlayerMoney(playerid, PlayerData[playerid][pMoney]);
    SetPlayerScore(playerid, PlayerData[playerid][pLevel]);
    return 1;
}

// ============================================================================
//  Economy Wrapper — semua money harus lewat sini
// ============================================================================

stock VRP_SetPlayerMoney(playerid, amount)
{
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, amount);
    PlayerData[playerid][pMoney] = amount;
    return 1;
}

stock VRP_GivePlayerMoney(playerid, amount)
{
    PlayerData[playerid][pMoney] += amount;
    GivePlayerMoney(playerid, amount);
    return 1;
}

stock VRP_GetPlayerMoney(playerid)
{
    return PlayerData[playerid][pMoney];
}

// ============================================================================
//  Playtime Helper
// ============================================================================

stock GetPlayerSessionMinutes(playerid)
{
    if (PlayerData[playerid][pSessionStart] == 0)
        return 0;

    new elapsed = (GetTickCount() - PlayerData[playerid][pSessionStart]) / 60000;
    return elapsed;
}

stock GetPlayerTotalPlaytime(playerid)
{
    return PlayerData[playerid][pPlaytime] + GetPlayerSessionMinutes(playerid);
}

// ============================================================================
//  Save Player Data to DB (shared oleh disconnect & autosave)
// ============================================================================

stock SavePlayerDataToDB(playerid)
{
    if (!PlayerData[playerid][pLoggedIn])
        return 0;

    // Update posisi terakhir
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

    // Hitung playtime total
    new totalPlaytime = GetPlayerTotalPlaytime(playerid);

    new query[768];
    mysql_format(g_MySQL, query, sizeof(query),
        "UPDATE `players` SET \
            `skin` = %d, \
            `money` = %d, \
            `level` = %d, \
            `hunger` = %d, \
            `thirst` = %d, \
            `playtime` = %d, \
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
        PlayerData[playerid][pHunger],
        PlayerData[playerid][pThirst],
        totalPlaytime,
        PlayerData[playerid][pPosX],
        PlayerData[playerid][pPosY],
        PlayerData[playerid][pPosZ],
        PlayerData[playerid][pPosA],
        PlayerData[playerid][pInterior],
        PlayerData[playerid][pVirtualWorld],
        PlayerData[playerid][pID]
    );
    mysql_tquery(g_MySQL, query);
    return 1;
}
