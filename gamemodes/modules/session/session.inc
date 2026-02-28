/*
 *  Vibe Roleplay - Session Manager
 *  File: modules/session/session.inc
 */

#if defined _session_included
    #endinput
#endif
#define _session_included

#include <YSI_Coding/y_hooks>
#include <YSI_Coding/y_timers>
#include <YSI_Data/y_iterate>

stock Session_Start(playerid)
{
    if (playerid < 0 || playerid >= MAX_PLAYERS)
        return 0;

    PlayerData[playerid][pSessionStart] = GetTickCount();
    printf("[SESSION] Session dimulai untuk player %d", playerid);
    return 1;
}

stock Session_End(playerid)
{
    if (playerid < 0 || playerid >= MAX_PLAYERS)
        return 0;

    if (PlayerData[playerid][pSessionStart] > 0)
    {
        new sessionMinutes = GetPlayerSessionMinutes(playerid);
        PlayerData[playerid][pPlaytime] += sessionMinutes;
        PlayerData[playerid][pSessionStart] = 0;

        printf("[SESSION] Session berakhir untuk player %d (sesi: %d menit, total: %d menit)", 
            playerid, sessionMinutes, PlayerData[playerid][pPlaytime]);
    }
    return 1;
}

timer AutosaveAllPlayers[AUTOSAVE_INTERVAL]()
{
    new count = 0;

    foreach (new i : Player)
    {
        if (!PlayerData[i][pLoggedIn])
            continue;

        SavePlayerDataToDB(i);
        count++;
    }

    if (count > 0)
    {
        printf("[AUTOSAVE] Data %d pemain berhasil disimpan.", count);
    }
}

hook OnGameModeInit()
{
    // Start autosave timer
    defer AutosaveAllPlayers();
    printf("[SESSION] Autosave timer aktif (interval: %d detik).", AUTOSAVE_INTERVAL / 1000);
    return 1;
}

