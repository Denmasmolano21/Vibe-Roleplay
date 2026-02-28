/*
 *  Vibe Roleplay - Spawn & Death System
 *  File: modules/spawn/spawn.inc
 */

#if defined _spawn_included
    #endinput
#endif
#define _spawn_included

#include <YSI_Coding/y_hooks>
#include <YSI_Coding/y_timers>
#include <YSI_Data/y_iterate>

forward OnDeathTimerExpire(playerid);
public OnDeathTimerExpire(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (PlayerData[playerid][pState] != PLAYER_STATE_DEAD)
        return 0;

    PlayerData[playerid][pDeathTimer] = -1;
    PlayerData[playerid][pState] = PLAYER_STATE_ALIVE;

    if (VRP_GetPlayerMoney(playerid) >= HOSPITAL_COST)
    {
        VRP_GivePlayerMoney(playerid, -HOSPITAL_COST);
        new msg[128];
        format(msg, sizeof(msg), "Kamu dibawa ke rumah sakit. Biaya perawatan: $%d", HOSPITAL_COST);
        SendInfoMessage(playerid, msg);
    }
    else
    {
        VRP_SetPlayerMoney(playerid, 0);
        SendWarningMessage(playerid, "Kamu dibawa ke rumah sakit. Uang tidak cukup untuk biaya perawatan.");
    }

    SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin],
        HOSPITAL_SPAWN_X, HOSPITAL_SPAWN_Y, HOSPITAL_SPAWN_Z, HOSPITAL_SPAWN_A,
        0, 0, 0, 0, 0, 0
    );
    SpawnPlayer(playerid);
    SetPlayerInterior(playerid, HOSPITAL_SPAWN_INT);
    SetPlayerVirtualWorld(playerid, HOSPITAL_SPAWN_VW);
    SetPlayerHealth(playerid, 50.0);

    PlayerData[playerid][pPosX] = HOSPITAL_SPAWN_X;
    PlayerData[playerid][pPosY] = HOSPITAL_SPAWN_Y;
    PlayerData[playerid][pPosZ] = HOSPITAL_SPAWN_Z;
    PlayerData[playerid][pPosA] = HOSPITAL_SPAWN_A;
    PlayerData[playerid][pInterior] = HOSPITAL_SPAWN_INT;
    PlayerData[playerid][pVirtualWorld] = HOSPITAL_SPAWN_VW;

    HUD_Show(playerid);
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    if (!PlayerData[playerid][pLoggedIn])
        return 1;

    PlayerData[playerid][pState] = PLAYER_STATE_DEAD;
    HUD_Hide(playerid);

    new msg[128];
    format(msg, sizeof(msg), "Kamu tewas. Kamu akan dibawa ke rumah sakit dalam %d detik...", DEATH_WAIT_TIME);
    SendErrorMessage(playerid, msg);

    PlayerData[playerid][pDeathTimer] = SetTimerEx("OnDeathTimerExpire",
        DEATH_WAIT_TIME * 1000, false, "i", playerid);

    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if (!PlayerData[playerid][pLoggedIn])
    {
        TogglePlayerSpectating(playerid, true);
        return 0;
    }

    if (PlayerData[playerid][pState] == PLAYER_STATE_DEAD)
    {
        TogglePlayerControllable(playerid, false);
        return 1;
    }

    PlayerData[playerid][pState] = PLAYER_STATE_ALIVE;
    TogglePlayerControllable(playerid, true);
    HUD_Show(playerid);

    return 1;
}

hook OnPlayerRequestClass(playerid, classid)
{
    if (!PlayerData[playerid][pLoggedIn])
    {
        TogglePlayerSpectating(playerid, true);
        return 0;
    }
    return 1;
}

hook OnPlayerRequestSpawn(playerid)
{
    if (!PlayerData[playerid][pLoggedIn])
    {
        return 0;
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    if (!PlayerData[playerid][pLoggedIn])
    {
        TogglePlayerSpectating(playerid, true);
        return 0;
    }

    // Jika state masih DEAD (spawn dari SA-MP internal), abaikan
    if (IsPlayerDeadState(playerid))
    {
        // Freeze pemain hingga timer expire
        TogglePlayerControllable(playerid, false);
        return 1;
    }

    // Set state ke ALIVE
    GetPlayerState(playerid);

    // Pastikan pemain bisa bergerak
    TogglePlayerControllable(playerid, true);

    // Show HUD
    HUD_Show(playerid);

    return 1;
}