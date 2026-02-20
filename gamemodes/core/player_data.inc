/*
 *  Vibe Roleplay - Player Data
 *  File: core/player_data.inc
 *
 *  Struktur data pemain dan fungsi reset.
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

    // Status
    bool:pLoggedIn,
    bool:pRegistering,
    pLoginAttempts,
    pTempPassword[MAX_PASSWORD_LENGTH + 1],

    // Stats
    pSkin,
    pMoney,
    pLevel,

    // Position
    Float:pPosX,
    Float:pPosY,
    Float:pPosZ,
    Float:pPosA,
    pInterior,
    pVirtualWorld
};

new PlayerData[MAX_PLAYERS][E_PLAYER_DATA];

// ============================================================================
//  Functions
// ============================================================================

stock ResetPlayerData(playerid)
{
    PlayerData[playerid][pID]           = 0;
    PlayerData[playerid][pPassword][0]  = EOS;
    PlayerData[playerid][pLoggedIn]     = false;
    PlayerData[playerid][pRegistering]  = false;
    PlayerData[playerid][pLoginAttempts]= 0;
    PlayerData[playerid][pTempPassword][0] = EOS;
    PlayerData[playerid][pSkin]         = DEFAULT_SPAWN_SKIN;
    PlayerData[playerid][pMoney]        = 0;
    PlayerData[playerid][pLevel]        = 1;
    PlayerData[playerid][pPosX]         = DEFAULT_SPAWN_X;
    PlayerData[playerid][pPosY]         = DEFAULT_SPAWN_Y;
    PlayerData[playerid][pPosZ]         = DEFAULT_SPAWN_Z;
    PlayerData[playerid][pPosA]         = DEFAULT_SPAWN_A;
    PlayerData[playerid][pInterior]     = DEFAULT_SPAWN_INTERIOR;
    PlayerData[playerid][pVirtualWorld] = DEFAULT_SPAWN_VW;
    return 1;
}

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

// Utility: Set player money (reset + give)
stock VRP_SetPlayerMoney(playerid, amount)
{
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, amount);
    return 1;
}
