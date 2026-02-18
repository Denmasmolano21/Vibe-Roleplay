// player/death.pwn — Death system + spawn protection
//
// Alur mati:
//   OnPlayerDeath → p_IsDead = true → freeze + kamera death cam
//   Timer 30 detik → pesan countdown tiap 10 detik
//   /respawn setelah waktu habis → Player_DoSpawn → spawn protection 5 detik
//
// Spawn protection:
//   5 detik setelah spawn → God mode + pesan "[Spawn Protection] X detik"
//   Habis → normal kembali
//
// Depends on: player/data.pwn, core/config.pwn

#if defined _PLAYER_DEATH_PWN
    #endinput
#endif
#define _PLAYER_DEATH_PWN

// Timestamp kapan player mati — untuk hitung sisa waktu /respawn
static s_DeathTime[MAX_PLAYERS];

// =============================================================================
// HOOK: OnPlayerDeath
// =============================================================================
hook OnPlayerDeath(playerid, killerid, reason) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;

    g_Player[playerid][p_IsDead]    = true;
    g_Player[playerid][p_SpawnProt] = false;
    s_DeathTime[playerid]           = gettime();

    // Freeze + teks info
    TogglePlayerControllable(playerid, false);
    SendClientMessage(playerid, COL_RED, \
        "  {FF4444}[Mati] {FFFFFF}Anda tewas. Ketik {00C8FF}/respawn " \
        "{FFFFFF}setelah 30 detik.");

    if (killerid != INVALID_PLAYER_ID && g_Player[killerid][p_LoggedIn]) {
        new msg[128];
        format(msg, sizeof(msg),
            "  {FF8800}[Kill] {FFFFFF}Anda membunuh {FF4444}%s{FFFFFF}.",
            g_Player[playerid][p_Name]);
        SendClientMessage(killerid, COL_ORANGE, msg);
    }

    // Log
    // printf("[Death] victim=%s  killer=%s  weapon=%d",
    //     g_Player[playerid][p_Name],
    //     (killerid != INVALID_PLAYER_ID) ? g_Player[killerid][p_Name] : "world",
    //     reason);

    return 1;
}

// =============================================================================
// ACTIVATE_SPAWN_PROTECTION — dipanggil dari spawning.pwn setelah OnPlayerSpawn
// =============================================================================
stock Death_ActivateSpawnProtection(playerid) {
    if (!g_Player[playerid][p_IsDead]) return; // hanya untuk respawn

    // Reset state mati
    g_Player[playerid][p_IsDead]    = false;
    g_Player[playerid][p_SpawnProt] = true;

    // God mode selama protection
    SetPlayerHealth(playerid, 100.0);

    SendClientMessage(playerid, COL_GREEN, \
        "  {44FF44}[Spawn] {FFFFFF}Anda telah respawn. " \
        "Perlindungan aktif 5 detik.");

    // Cabut protection setelah SPAWN_PROT_TIME ms
    SetTimerEx("_CB_SpawnProtEnd", SPAWN_PROT_TIME, false, "d", playerid);
}

// =============================================================================
// CALLBACK: akhir spawn protection
// =============================================================================
forward _CB_SpawnProtEnd(playerid);
public  _CB_SpawnProtEnd(playerid) {
    if (!IsPlayerConnected(playerid)) return 1;
    if (!g_Player[playerid][p_SpawnProt]) return 1;

    g_Player[playerid][p_SpawnProt] = false;

    // Pastikan HP tidak berubah aneh selama protection
    new Float:hp;
    GetPlayerHealth(playerid, hp);
    if (hp > 100.0) SetPlayerHealth(playerid, 100.0);

    SendClientMessage(playerid, COL_GREY,
        "  {888888}[Spawn] Perlindungan spawn habis.");
    return 1;
}

// =============================================================================
// CEK SPAWN PROTECTION — dipakai AC dan damage handler
// Saat p_SpawnProt true, player tidak bisa di-damage
// =============================================================================
stock bool:Player_HasSpawnProt(playerid) {
    return g_Player[playerid][p_SpawnProt];
}

// Sisa waktu respawn dalam detik (0 = sudah bisa respawn)
stock Player_RespawnCooldown(playerid) {
    if (!g_Player[playerid][p_IsDead]) return 0;
    new elapsed = gettime() - s_DeathTime[playerid];
    new remaining = DEATH_RESPAWN_TIME - elapsed;
    return (remaining > 0) ? remaining : 0;
}
