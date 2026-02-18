// spawning.pwn — Logika spawn + posisi terakhir
// Depends on: player/data.pwn, core/config.pwn, ui/hud.pwn

#if defined _SPAWNING_PWN
    #endinput
#endif
#define _SPAWNING_PWN

// =============================================================================
// HOOKS
// =============================================================================

hook OnPlayerRequestClass(playerid, classid) {
    // Blok class selection — pastikan kamera login screen tetap aktif
    SetPlayerCameraPos(playerid,
        LOGIN_CAM_POS_X, LOGIN_CAM_POS_Y, LOGIN_CAM_POS_Z);
    SetPlayerCameraLookAt(playerid,
        LOGIN_CAM_LOOK_X, LOGIN_CAM_LOOK_Y, LOGIN_CAM_LOOK_Z,
        CAMERA_CUT);
    TogglePlayerControllable(playerid, false);
    return 1;
}

hook OnPlayerSpawn(playerid) {
    if (!g_Player[playerid][p_LoggedIn]) {
        TogglePlayerControllable(playerid, false);
        return 1;
    }
    Player_ApplySpawn(playerid);
    HUD_Show(playerid);
    
    // Aktifkan spawn protection jika ini adalah respawn setelah mati
    Death_ActivateSpawnProtection(playerid);
    
    return 1;
}

// =============================================================================
// PLAYER_DOSPAWN
// Dipanggil dari Player_FinishLogin.
// SetSpawnInfo WAJIB sebelum SpawnPlayer — SA-MP butuh ini.
// =============================================================================
stock Player_DoSpawn(playerid) {
    // Tentukan titik spawn
    new Float:sx, Float:sy, Float:sz, Float:sa;
    new s_interior, s_world;

    if (Player_IsFirstSpawn(playerid)) {
        // Player baru — pakai default spawn Pershing Square
        sx = SPAWN_X;   sy = SPAWN_Y;
        sz = SPAWN_Z;   sa = SPAWN_A;
        s_interior = SPAWN_INTERIOR;
        s_world    = SPAWN_WORLD;
    } else {
        // Player lama — kembalikan ke posisi terakhir
        sx = g_Player[playerid][p_LastX];
        sy = g_Player[playerid][p_LastY];
        sz = g_Player[playerid][p_LastZ];
        sa = g_Player[playerid][p_LastA];
        s_interior = g_Player[playerid][p_LastInterior];
        s_world    = g_Player[playerid][p_LastWorld];
    }

    SetSpawnInfo(playerid,
        NO_TEAM, SPAWN_SKIN,
        sx, sy, sz, sa,
        0, 0, 0, 0, 0, 0
    );

    // Terapkan interior & world SEBELUM SpawnPlayer
    // supaya player tidak sejenak muncul di VW default
    SetPlayerInterior(playerid, s_interior);
    SetPlayerVirtualWorld(playerid, s_world);

    SpawnPlayer(playerid);
}

// =============================================================================
// PLAYER_APPLYSPAWN
// Dipanggil dari OnPlayerSpawn (setelah SpawnPlayer trigger).
// =============================================================================
stock Player_ApplySpawn(playerid) {
    new Float:sx, Float:sy, Float:sz, Float:sa;
    new s_interior, s_world;

    if (Player_IsFirstSpawn(playerid)) {
        sx = SPAWN_X;   sy = SPAWN_Y;
        sz = SPAWN_Z;   sa = SPAWN_A;
        s_interior = SPAWN_INTERIOR;
        s_world    = SPAWN_WORLD;
    } else {
        sx = g_Player[playerid][p_LastX];
        sy = g_Player[playerid][p_LastY];
        sz = g_Player[playerid][p_LastZ];
        sa = g_Player[playerid][p_LastA];
        s_interior = g_Player[playerid][p_LastInterior];
        s_world    = g_Player[playerid][p_LastWorld];
    }

    SetPlayerVirtualWorld(playerid, s_world);
    SetPlayerInterior(playerid, s_interior);
    SetPlayerPos(playerid, sx, sy, sz);
    SetPlayerFacingAngle(playerid, sa);

    SetPlayerSkin(playerid, SPAWN_SKIN);
    SetPlayerHealth(playerid, 100.0);
    SetPlayerArmour(playerid, 0.0);
    ResetPlayerWeapons(playerid);
    TogglePlayerControllable(playerid, true);
    SetCameraBehindPlayer(playerid);
}
