/*
 *  Vibe Roleplay - Player Data
 *  File: core/player_data.inc
 */

#if defined _player_data_included
    #endinput
#endif
#define _player_data_included

#define MAX_PLAYER_PASSWORD     65

enum E_PLAYER_DATA
{
    pID,
    pPassword[MAX_PLAYER_PASSWORD],

    bool:pLoggedIn,
    bool:pRegistering,
    pLoginAttempts,
    pTempPassword[MAX_PASSWORD_LENGTH + 1],
    pState,

    pAdminLevel,

    pSkin,
    pMoney,
    pBankMoney,
    pLevel,
    pHunger,
    pThirst,
    pPlaytime,
    pSessionStart,

    Float:pPosX,
    Float:pPosY,
    Float:pPosZ,
    Float:pPosA,
    pInterior,
    pVirtualWorld,

    pDeathTimer
};

new PlayerData[MAX_PLAYERS][E_PLAYER_DATA];

stock ResetPlayerData(playerid)
{
    if (playerid < 0 || playerid >= MAX_PLAYERS)
        return 0;

    PlayerData[playerid][pID]               = 0;
    PlayerData[playerid][pPassword][0]      = EOS;
    PlayerData[playerid][pLoggedIn]         = false;
    PlayerData[playerid][pRegistering]      = false;
    PlayerData[playerid][pLoginAttempts]    = 0;
    PlayerData[playerid][pTempPassword][0]  = EOS;
    PlayerData[playerid][pState]            = 0;
    PlayerData[playerid][pAdminLevel]       = 0;
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

stock SpawnPlayerAtSavedPosition(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

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

stock VRP_SetPlayerMoney(playerid, amount)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, amount);
    PlayerData[playerid][pMoney] = amount;
    return 1;
}

stock VRP_GivePlayerMoney(playerid, amount)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    PlayerData[playerid][pMoney] += amount;
    GivePlayerMoney(playerid, amount);
    return 1;
}

stock VRP_TakePlayerMoney(playerid, amount)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (PlayerData[playerid][pMoney] < amount)
    {
        PlayerData[playerid][pMoney] = 0;
        ResetPlayerMoney(playerid);
        return 0;
    }

    PlayerData[playerid][pMoney] -= amount;
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, PlayerData[playerid][pMoney]);
    return 1;
}

stock VRP_GetPlayerMoney(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    return PlayerData[playerid][pMoney];
}

stock GetPlayerSessionMinutes(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (PlayerData[playerid][pSessionStart] == 0)
        return 0;

    new elapsed = (GetTickCount() - PlayerData[playerid][pSessionStart]) / 60000;
    return elapsed;
}

stock GetPlayerTotalPlaytime(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    return PlayerData[playerid][pPlaytime] + GetPlayerSessionMinutes(playerid);
}

stock GetPlayerSessionTime(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    return GetPlayerSessionMinutes(playerid) * 60;
}

stock SavePlayerDataToDB(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (!PlayerData[playerid][pLoggedIn])
        return 0;

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

    new totalPlaytime = GetPlayerTotalPlaytime(playerid);

    new query[768];
    mysql_format(g_MySQL, query, sizeof(query),
        "UPDATE `players` SET \
            `skin` = %d, \
            `money` = %d, \
            `bank_money` = %d, \
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
        PlayerData[playerid][pBankMoney],
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
