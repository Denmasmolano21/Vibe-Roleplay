/*
 *  Vibe Roleplay - Spawn & Death System
 *  File: modules/spawn/spawn.inc
 *
 *  Sistem kematian dan respawn.
 *  Anti-spawn-abuse, death timer, hospital cost.
 */

#if defined _spawn_included
    #endinput
#endif
#define _spawn_included

// ============================================================================
//  Death Timer Callback
// ============================================================================

forward OnDeathTimerExpire(playerid);
public OnDeathTimerExpire(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (!IsPlayerDead(playerid))
        return 0;

    // Respawn di rumah sakit
    PlayerData[playerid][pDeathTimer] = -1;

    SetPlayerState_(playerid, STATE_ALIVE);

    // Potong biaya rumah sakit
    if (VRP_GetPlayerMoney(playerid) >= HOSPITAL_COST)
    {
        VRP_GivePlayerMoney(playerid, -HOSPITAL_COST);

        new msg[128];
        format(msg, sizeof(msg), "Kamu dibawa ke rumah sakit. Biaya perawatan: $%d", HOSPITAL_COST);
        SendInfoMessage(playerid, msg);
    }
    else
    {
        // Uang tidak cukup — gratis tapi beri peringatan
        VRP_SetPlayerMoney(playerid, 0);
        SendWarningMessage(playerid, "Kamu dibawa ke rumah sakit. Uang tidak cukup untuk biaya perawatan.");
    }

    // Spawn di rumah sakit
    SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin],
        HOSPITAL_SPAWN_X, HOSPITAL_SPAWN_Y, HOSPITAL_SPAWN_Z, HOSPITAL_SPAWN_A,
        0, 0, 0, 0, 0, 0
    );
    SpawnPlayer(playerid);
    SetPlayerInterior(playerid, HOSPITAL_SPAWN_INT);
    SetPlayerVirtualWorld(playerid, HOSPITAL_SPAWN_VW);
    SetPlayerHealth(playerid, 50.0); // Respawn dengan HP setengah

    // Update posisi data
    PlayerData[playerid][pPosX] = HOSPITAL_SPAWN_X;
    PlayerData[playerid][pPosY] = HOSPITAL_SPAWN_Y;
    PlayerData[playerid][pPosZ] = HOSPITAL_SPAWN_Z;
    PlayerData[playerid][pPosA] = HOSPITAL_SPAWN_A;
    PlayerData[playerid][pInterior] = HOSPITAL_SPAWN_INT;
    PlayerData[playerid][pVirtualWorld] = HOSPITAL_SPAWN_VW;

    // Show HUD kembali
    HUD_Show(playerid);
    return 1;
}

// ============================================================================
//  Hooks
// ============================================================================

hook OnPlayerDeath(playerid, killerid, reason)
{
    if (!PlayerData[playerid][pLoggedIn])
        return 1;

    // Set state ke DEAD
    SetPlayerState_(playerid, STATE_DEAD);

    // Sembunyikan HUD
    HUD_Hide(playerid);

    // Pesan ke pemain
    new msg[128];
    format(msg, sizeof(msg), "Kamu tewas. Kamu akan dibawa ke rumah sakit dalam %d detik...", DEATH_WAIT_TIME);
    SendErrorMessage(playerid, msg);

    // Start death timer
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

    // Jika state masih DEAD (spawn dari SA-MP internal), abaikan
    if (IsPlayerDead(playerid))
    {
        // Freeze pemain hingga timer expire
        TogglePlayerControllable(playerid, false);
        return 1;
    }

    // Set state ke ALIVE
    SetPlayerState_(playerid, STATE_ALIVE);

    // Pastikan pemain bisa bergerak
    TogglePlayerControllable(playerid, true);

    // Show HUD
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
