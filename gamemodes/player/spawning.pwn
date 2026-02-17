// spawning.pwn — Logika spawn player
// Depends on: player/data.pwn, core/config.pwn

#if defined _SPAWNING_PWN
    #endinput
#endif
#define _SPAWNING_PWN

// ─── OnPlayerRequestClass ─────────────────────────────────────────────────────
//     Dipanggil SA-MP sebelum player bisa spawn untuk pertama kali.
//     Kita blok class selection screen dan tempel kamera login screen.
hook OnPlayerRequestClass(playerid, classid) {
    // Pastikan kamera login screen tetap aktif (SA-MP reset kamera saat request class)
    SetPlayerCameraPos(playerid,
        LOGIN_CAM_POS_X, LOGIN_CAM_POS_Y, LOGIN_CAM_POS_Z);
    SetPlayerCameraLookAt(playerid,
        LOGIN_CAM_LOOK_X, LOGIN_CAM_LOOK_Y, LOGIN_CAM_LOOK_Z,
        CAMERA_CUT);
    TogglePlayerControllable(playerid, false);
    return 1;
}

// ─── OnPlayerSpawn ────────────────────────────────────────────────────────────
hook OnPlayerSpawn(playerid) {
    // Guard: jangan proses spawn jika belum login
    // (bisa terjadi jika ada bug flow atau exploit)
    if (!g_Player[playerid][p_LoggedIn]) {
        TogglePlayerControllable(playerid, false);
        return 1;
    }

    Player_ApplySpawn(playerid);
    HUD_Show(playerid);
    return 1;
}

// ─── Player_DoSpawn ───────────────────────────────────────────────────────────
//     Dipanggil dari Player_FinishLogin (data.pwn).
//     SetSpawnInfo WAJIB sebelum SpawnPlayer — SA-MP butuh ini untuk menentukan
//     posisi spawn. Tanpa SetSpawnInfo, SpawnPlayer() bisa spawn di (0,0,0).
stock Player_DoSpawn(playerid) {
    SetSpawnInfo(playerid,
        NO_TEAM, SPAWN_SKIN,
        SPAWN_X, SPAWN_Y, SPAWN_Z, SPAWN_A,
        0, 0, 0, 0, 0, 0
    );
    SpawnPlayer(playerid);
    // → trigger OnPlayerSpawn → Player_ApplySpawn + HUD_Show
}

// ─── Player_ApplySpawn ────────────────────────────────────────────────────────
//     Dipanggil dari OnPlayerSpawn.
//     Set posisi, skin, health, reset weapon & kamera.
stock Player_ApplySpawn(playerid) {
    // Kembalikan ke virtual world normal (waktu login kita isolasi ke VW unik)
    SetPlayerVirtualWorld(playerid, SPAWN_WORLD);
    SetPlayerInterior(playerid, SPAWN_INTERIOR);

    // Posisi Pershing Square — lantai beton, Z=13.36, TIDAK jatuh
    SetPlayerPos(playerid, SPAWN_X, SPAWN_Y, SPAWN_Z);
    SetPlayerFacingAngle(playerid, SPAWN_A);

    SetPlayerSkin(playerid, SPAWN_SKIN);
    SetPlayerHealth(playerid, 100.0);
    SetPlayerArmour(playerid, 0.0);
    ResetPlayerWeapons(playerid);
    TogglePlayerControllable(playerid, true);

    // Kembalikan kamera ke belakang player (setelah kamera login screen)
    SetCameraBehindPlayer(playerid);
}
