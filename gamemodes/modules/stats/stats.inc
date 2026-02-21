/*
 *  Vibe Roleplay - Stats System
 *  File: modules/stats/stats.inc
 *
 *  Sistem hunger, thirst, dan playtime.
 *  Timer-based decay + HP drain + persistent ke database.
 */

#if defined _stats_included
    #endinput
#endif
#define _stats_included

// Include HUD
#include "stats_hud.inc"

// ============================================================================
//  Stats Initialization (panggil setelah login)
// ============================================================================

stock Stats_OnPlayerLogin(playerid)
{
    // Create & show HUD
    HUD_Create(playerid);
    HUD_Show(playerid);
    HUD_Update(playerid);
    return 1;
}

stock Stats_OnPlayerDisconnect(playerid)
{
    HUD_Hide(playerid);
    HUD_Destroy(playerid);
    return 1;
}

// ============================================================================
//  Stats Decay Timer (y_timers)
// ============================================================================

timer StatsDecayTimer[STATS_DECAY_INTERVAL]()
{
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (!IsPlayerConnected(i))
            continue;

        if (!PlayerData[i][pLoggedIn])
            continue;

        if (!IsPlayerAlive(i))
            continue;

        // Decay hunger
        PlayerData[i][pHunger] -= HUNGER_DECAY_RATE;
        if (PlayerData[i][pHunger] < 0)
            PlayerData[i][pHunger] = 0;

        // Decay thirst
        PlayerData[i][pThirst] -= THIRST_DECAY_RATE;
        if (PlayerData[i][pThirst] < 0)
            PlayerData[i][pThirst] = 0;

        // HP drain jika hunger atau thirst = 0
        if (PlayerData[i][pHunger] == 0 || PlayerData[i][pThirst] == 0)
        {
            new Float:hp;
            GetPlayerHealth(i, hp);

            if (hp > 0.0)
            {
                SetPlayerHealth(i, hp - STATS_HP_DRAIN);

                if (PlayerData[i][pHunger] == 0 && PlayerData[i][pThirst] == 0)
                {
                    SendWarningMessage(i, "Kamu kelaparan dan kehausan! HP berkurang.");
                }
                else if (PlayerData[i][pHunger] == 0)
                {
                    SendWarningMessage(i, "Kamu kelaparan! HP berkurang.");
                }
                else
                {
                    SendWarningMessage(i, "Kamu kehausan! HP berkurang.");
                }
            }
        }

        // Update HUD
        HUD_Update(i);
    }
}

// ============================================================================
//  Stats Manipulation (untuk command eat/drink nanti)
// ============================================================================

stock Stats_AddHunger(playerid, amount)
{
    PlayerData[playerid][pHunger] += amount;
    if (PlayerData[playerid][pHunger] > MAX_HUNGER)
        PlayerData[playerid][pHunger] = MAX_HUNGER;

    HUD_Update(playerid);
    return 1;
}

stock Stats_AddThirst(playerid, amount)
{
    PlayerData[playerid][pThirst] += amount;
    if (PlayerData[playerid][pThirst] > MAX_THIRST)
        PlayerData[playerid][pThirst] = MAX_THIRST;

    HUD_Update(playerid);
    return 1;
}

stock Stats_SetHunger(playerid, amount)
{
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
    PlayerData[playerid][pThirst] = amount;
    if (PlayerData[playerid][pThirst] > MAX_THIRST)
        PlayerData[playerid][pThirst] = MAX_THIRST;
    if (PlayerData[playerid][pThirst] < 0)
        PlayerData[playerid][pThirst] = 0;

    HUD_Update(playerid);
    return 1;
}

// ============================================================================
//  Hooks
// ============================================================================

hook OnGameModeInit()
{
    defer StatsDecayTimer();
    printf("[STATS] Stats decay timer aktif (interval: %d detik).", STATS_DECAY_INTERVAL / 1000);
    return 1;
}
