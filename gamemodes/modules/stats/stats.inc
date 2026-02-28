/*
 *  Vibe Roleplay - Stats System
 *  File: modules/stats/stats.inc
 */

#if defined _stats_included
    #endinput
#endif
#define _stats_included

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_iterate>
#include "stats_hud.inc"

stock Stats_OnPlayerLogin(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    HUD_Create(playerid);
    HUD_Show(playerid);
    HUD_Update(playerid);
    return 1;
}

stock Stats_OnPlayerDisconnect(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    HUD_Hide(playerid);
    HUD_Destroy(playerid);
    return 1;
}

timer StatsDecayTimer[STATS_DECAY_INTERVAL]()
{
    foreach (new i : Player)
    {
        if (!PlayerData[i][pLoggedIn])
            continue;

        if (PlayerData[i][pState] != PLAYER_STATE_ALIVE)
            continue;

        PlayerData[i][pHunger] -= HUNGER_DECAY_RATE;
        if (PlayerData[i][pHunger] < 0)
            PlayerData[i][pHunger] = 0;

        PlayerData[i][pThirst] -= THIRST_DECAY_RATE;
        if (PlayerData[i][pThirst] < 0)
            PlayerData[i][pThirst] = 0;

        if (PlayerData[i][pHunger] == 0 || PlayerData[i][pThirst] == 0)
        {
            new Float:hp;
            GetPlayerHealth(i, hp);

            if (hp > 0.0)
            {
                SetPlayerHealth(i, hp - STATS_HP_DRAIN);

                if (PlayerData[i][pHunger] == 0 && PlayerData[i][pThirst] == 0)
                    SendWarningMessage(i, "Kamu kelaparan dan kehausan! HP berkurang.");
                else if (PlayerData[i][pHunger] == 0)
                    SendWarningMessage(i, "Kamu kelaparan! Makan sesuatu segera.");
                else
                    SendWarningMessage(i, "Kamu kehausan! Minum sesuatu segera.");
            }
        }

        HUD_Update(i);
    }
}

stock Stats_AddHunger(playerid, amount)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (amount <= 0)
        return 0;

    PlayerData[playerid][pHunger] += amount;
    if (PlayerData[playerid][pHunger] > MAX_HUNGER)
        PlayerData[playerid][pHunger] = MAX_HUNGER;

    HUD_Update(playerid);
    
    new msg[64];
    format(msg, sizeof(msg), "Hunger +%d (sekarang: %d)", amount, PlayerData[playerid][pHunger]);
    SendInfoMessage(playerid, msg);
    
    return 1;
}

stock Stats_AddThirst(playerid, amount)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (amount <= 0)
        return 0;

    PlayerData[playerid][pThirst] += amount;
    if (PlayerData[playerid][pThirst] > MAX_THIRST)
        PlayerData[playerid][pThirst] = MAX_THIRST;

    HUD_Update(playerid);
    
    new msg[64];
    format(msg, sizeof(msg), "Thirst +%d (sekarang: %d)", amount, PlayerData[playerid][pThirst]);
    SendInfoMessage(playerid, msg);
    
    return 1;
}

stock Stats_SetHunger(playerid, amount)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    PlayerData[playerid][pHunger] = amount;
    if (PlayerData[playerid][pHunger] > MAX_HUNGER)
        PlayerData[playerid][pHunger] = MAX_HUNGER;
    if (PlayerData[playerid][pHunger] < 0)
        PlayerData[playerid][pHunger] = 0;

    HUD_Update(playerid);
    return 1;
}

stock Stats_SetThirst(playerid, amount)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    PlayerData[playerid][pThirst] = amount;
    if (PlayerData[playerid][pThirst] > MAX_THIRST)
        PlayerData[playerid][pThirst] = MAX_THIRST;
    if (PlayerData[playerid][pThirst] < 0)
        PlayerData[playerid][pThirst] = 0;

    HUD_Update(playerid);
    return 1;
}

stock Stats_GetHunger(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    return PlayerData[playerid][pHunger];
}

stock Stats_GetThirst(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    return PlayerData[playerid][pThirst];
}

hook OnGameModeInit()
{
    defer StatsDecayTimer();
    printf("[STATS] Stats decay timer aktif (interval: %d detik).", STATS_DECAY_INTERVAL / 1000);
    return 1;
}
