/*
 *  Vibe Roleplay - Session Manager
 *  File: modules/session/session.inc
 *
 *  Autosave berkala dan session tracking.
 *  Menggunakan y_timers untuk repeating timer.
 */

#if defined _session_included
    #endinput
#endif
#define _session_included

// ============================================================================
//  Session Start / End
// ============================================================================

stock Session_Start(playerid)
{
    PlayerData[playerid][pSessionStart] = GetTickCount();
    printf("[SESSION] Session dimulai untuk player %d", playerid);
    return 1;
}

stock Session_End(playerid)
{
    if (PlayerData[playerid][pSessionStart] > 0)
    {
        // Tambahkan waktu sesi ke total playtime
        new sessionMinutes = GetPlayerSessionMinutes(playerid);
        PlayerData[playerid][pPlaytime] += sessionMinutes;
        PlayerData[playerid][pSessionStart] = 0;

        printf("[SESSION] Session berakhir untuk player %d (sesi: %d menit)", playerid, sessionMinutes);
    }
    return 1;
}

// ============================================================================
//  Autosave Timer (y_timers)
// ============================================================================

timer AutosaveAllPlayers[AUTOSAVE_INTERVAL]()
{
    new count = 0;

    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (!IsPlayerConnected(i))
            continue;

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

// ============================================================================
//  Hooks
// ============================================================================

hook OnGameModeInit()
{
    // Start autosave timer
    defer AutosaveAllPlayers();
    printf("[SESSION] Autosave timer aktif (interval: %d detik).", AUTOSAVE_INTERVAL / 1000);
    return 1;
}
