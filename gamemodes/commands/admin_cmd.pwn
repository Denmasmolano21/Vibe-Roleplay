// commands/admin_cmd.pwn — Command admin
//
// Level akses (dari core/config.pwn):
//   ADMIN_MOD   (1) — /kick /warn /ann
//   ADMIN_ADMIN (2) — /ban /unban /setlevel /goto /gethere
//   ADMIN_OWNER (3) — semua
//
// Pola guard: macro REQUIRE_ADMIN(level) — return 1 jika tidak cukup
// Depends on: player/data.pwn, database/query_builder.pwn

#if defined _CMD_ADMIN_PWN
    #endinput
#endif
#define _CMD_ADMIN_PWN

// Guard macro — berhenti jika level kurang
#define REQUIRE_ADMIN(%1) \
    if (g_Player[playerid][p_Admin] < %1) { \
        SendClientMessage(playerid, COL_RED, \
            "  {FF4444}[!] {FFFFFF}Akses ditolak."); \
        return 1; \
    }

// Helper: parse "id" atau "nama" → playerid, return INVALID_PLAYER_ID jika gagal
static stock Admin_FindPlayer(const input[]) {
    if (Util_IsNumeric(input)) {
        new id = strval(input);
        if (IsPlayerConnected(id)) return id;
        return INVALID_PLAYER_ID;
    }
    // Cari by nama (partial match)
    foreach (new i : Player) {
        if (strfind(g_Player[i][p_Name], input, true) != -1) return i;
    }
    return INVALID_PLAYER_ID;
}

// =============================================================================
// /kick [id/nama] [alasan]
// Level: MOD
// =============================================================================
CMD:kick(playerid, params[]) {
    REQUIRE_ADMIN(ADMIN_MOD)

    new arg1[32], reason[64];
    if (sscanf(params, "s[32]S[64](Tanpa alasan)", arg1, reason)) {
        SendClientMessage(playerid, COL_RED, "  [!] Penggunaan: /kick [id/nama] [alasan]");
        return 1;
    }

    new target = Admin_FindPlayer(arg1);
    if (target == INVALID_PLAYER_ID) {
        SendClientMessage(playerid, COL_RED, "  [!] Player tidak ditemukan.");
        return 1;
    }
    if (target == playerid) {
        SendClientMessage(playerid, COL_RED, "  [!] Tidak bisa kick diri sendiri.");
        return 1;
    }
    if (g_Player[target][p_Admin] >= g_Player[playerid][p_Admin]) {
        SendClientMessage(playerid, COL_RED, "  [!] Tidak bisa kick admin selevel atau lebih tinggi.");
        return 1;
    }

    new msg[192];

    // Beritahu target
    format(msg, sizeof(msg), \
        "  {FF4444}[Kick] {FFFFFF}Anda di-kick oleh {FF8800}%s{FFFFFF}. " \
        "Alasan: {FFFFFF}%s", \
        g_Player[playerid][p_Name], reason);
    SendClientMessage(target, COL_RED, msg);

    // Beritahu semua admin
    format(msg, sizeof(msg),
        "  {FF8800}[Admin] {888888}%s kick %s — %s",
        g_Player[playerid][p_Name], g_Player[target][p_Name], reason);
    Admin_Announce(msg, ADMIN_MOD);

    printf("[Admin] KICK  admin=%s  target=%s  reason=%s",
        g_Player[playerid][p_Name], g_Player[target][p_Name], reason);

    Player_Kick(target);
    return 1;
}

// =============================================================================
// /ban [id/nama] [alasan]
// Level: ADMIN
// =============================================================================
CMD:ban(playerid, params[]) {
    REQUIRE_ADMIN(ADMIN_ADMIN)

    new arg1[32], reason[128];
    if (sscanf(params, "s[32]S[128](Tidak ada alasan)", arg1, reason)) {
        SendClientMessage(playerid, COL_RED, "  [!] Penggunaan: /ban [id/nama] [alasan]");
        return 1;
    }

    new target = Admin_FindPlayer(arg1);
    if (target == INVALID_PLAYER_ID) {
        SendClientMessage(playerid, COL_RED, "  [!] Player tidak ditemukan.");
        return 1;
    }
    if (target == playerid) {
        SendClientMessage(playerid, COL_RED, "  [!] Tidak bisa ban diri sendiri.");
        return 1;
    }
    if (g_Player[target][p_Admin] >= g_Player[playerid][p_Admin]) {
        SendClientMessage(playerid, COL_RED, "  [!] Tidak bisa ban admin selevel atau lebih tinggi.");
        return 1;
    }

    // Simpan reason ke struct sebelum DB_BanPlayer
    strmid(g_Player[target][p_BanReason], reason, 0, strlen(reason), 128);
    g_Player[target][p_Banned] = true;

    DB_BanPlayer(target, playerid);

    new msg[192];
    format(msg, sizeof(msg), \
        "  {FF4444}[Ban] {FFFFFF}Anda di-banned oleh {FF8800}%s{FFFFFF}. " \
        "Alasan: {FFFFFF}%s", \
        g_Player[playerid][p_Name], reason);
    SendClientMessage(target, COL_RED, msg);

    format(msg, sizeof(msg),
        "  {FF4444}[Admin] {888888}%s ban %s — %s",
        g_Player[playerid][p_Name], g_Player[target][p_Name], reason);
    Admin_Announce(msg, ADMIN_MOD);

    printf("[Admin] BAN  admin=%s  target=%s  reason=%s",
        g_Player[playerid][p_Name], g_Player[target][p_Name], reason);

    Player_Kick(target);
    return 1;
}

// =============================================================================
// /unban [nama]
// Level: ADMIN — unban akun offline via nama persis
// =============================================================================
CMD:unban(playerid, params[]) {
    REQUIRE_ADMIN(ADMIN_ADMIN)

    if (Util_IsEmpty(params)) {
        SendClientMessage(playerid, COL_RED, "  [!] Penggunaan: /unban [nama akun]");
        return 1;
    }

    DB_UnbanPlayer(params);

    new msg[128];
    format(msg, sizeof(msg),
        "  {44FF44}[Admin] {FFFFFF}Akun {00C8FF}%s {FFFFFF}telah di-unban.", params);
    SendClientMessage(playerid, COL_GREEN, msg);
    printf("[Admin] UNBAN  admin=%s  target=%s",
        g_Player[playerid][p_Name], params);
    return 1;
}

// =============================================================================
// /setlevel [id/nama] [level]
// Level: ADMIN
// =============================================================================
CMD:setlevel(playerid, params[]) {
    REQUIRE_ADMIN(ADMIN_ADMIN)

    new arg1[32], level;
    if (sscanf(params, "s[32]i", arg1, level)) {
        SendClientMessage(playerid, COL_RED, "  [!] Penggunaan: /setlevel [id/nama] [level]");
        return 1;
    }

    new target = Admin_FindPlayer(arg1);
    if (target == INVALID_PLAYER_ID) {
        SendClientMessage(playerid, COL_RED, "  [!] Player tidak ditemukan.");
        return 1;
    }

    if (level < 1 || level > 999) {
        SendClientMessage(playerid, COL_RED, "  [!] Level harus antara 1–999.");
        return 1;
    }

    g_Player[target][p_Level] = level;
    DB_SaveAccount(target);

    new msg[128];
    format(msg, sizeof(msg),
        "  {44FF44}[Admin] {FFFFFF}Level {00C8FF}%s {FFFFFF}diset ke {44FF44}%d{FFFFFF} "\
        "oleh {FF8800}%s{FFFFFF}.",
        g_Player[target][p_Name], level, g_Player[playerid][p_Name]);
    SendClientMessage(target, COL_GREEN, msg);
    SendClientMessage(playerid, COL_GREEN, msg);
    return 1;
}

// =============================================================================
// /setadmin [id/nama] [level 0-3]
// Level: OWNER
// =============================================================================
CMD:setadmin(playerid, params[]) {
    REQUIRE_ADMIN(ADMIN_OWNER)

    new arg1[32], level;
    if (sscanf(params, "s[32]i", arg1, level)) {
        SendClientMessage(playerid, COL_RED, "  [!] Penggunaan: /setadmin [id/nama] [0-3]");
        return 1;
    }

    new target = Admin_FindPlayer(arg1);
    if (target == INVALID_PLAYER_ID) {
        SendClientMessage(playerid, COL_RED, "  [!] Player tidak ditemukan.");
        return 1;
    }

    if (level < ADMIN_NONE || level > ADMIN_OWNER) {
        SendClientMessage(playerid, COL_RED, "  [!] Level admin: 0=None 1=Mod 2=Admin 3=Owner.");
        return 1;
    }

    g_Player[target][p_Admin] = level;
    DB_SaveAccount(target);

    new label[16];
    if      (level == ADMIN_OWNER) strmid(label, "Owner",     0, 5, 16);
    else if (level == ADMIN_ADMIN) strmid(label, "Admin",     0, 5, 16);
    else if (level == ADMIN_MOD)   strmid(label, "Moderator", 0, 9, 16);
    else                           strmid(label, "Dicabut",   0, 7, 16);

    new msg[128];
    format(msg, sizeof(msg),
        "  {FF8800}[Admin] {FFFFFF}%s diset sebagai {FF8800}%s {FFFFFF}oleh %s.",
        g_Player[target][p_Name], label, g_Player[playerid][p_Name]);
    Admin_Announce(msg, ADMIN_MOD);
    return 1;
}

// =============================================================================
// /goto [id/nama] — teleport ke player
// Level: ADMIN
// =============================================================================
CMD:goto(playerid, params[]) {
    REQUIRE_ADMIN(ADMIN_ADMIN)

    new target = Admin_FindPlayer(params);
    if (target == INVALID_PLAYER_ID) {
        SendClientMessage(playerid, COL_RED, "  [!] Player tidak ditemukan.");
        return 1;
    }
    if (target == playerid) {
        SendClientMessage(playerid, COL_RED, "  [!] Tidak bisa teleport ke diri sendiri.");
        return 1;
    }

    new Float:tx, Float:ty, Float:tz;
    GetPlayerPos(target, tx, ty, tz);
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(target));
    SetPlayerInterior   (playerid, GetPlayerInterior(target));
    SetPlayerPos        (playerid, tx + 1.0, ty, tz);

    new msg[96];
    format(msg, sizeof(msg),
        "  {44FF44}[TP] {FFFFFF}Teleport ke {00C8FF}%s{FFFFFF}.",
        g_Player[target][p_Name]);
    SendClientMessage(playerid, COL_GREEN, msg);
    return 1;
}

// =============================================================================
// /gethere [id/nama] — tarik player ke posisi admin
// Level: ADMIN
// =============================================================================
CMD:gethere(playerid, params[]) {
    REQUIRE_ADMIN(ADMIN_ADMIN)

    new target = Admin_FindPlayer(params);
    if (target == INVALID_PLAYER_ID) {
        SendClientMessage(playerid, COL_RED, "  [!] Player tidak ditemukan.");
        return 1;
    }
    if (target == playerid) {
        SendClientMessage(playerid, COL_RED, "  [!] Tidak bisa tarik diri sendiri.");
        return 1;
    }

    new Float:ax, Float:ay, Float:az;
    GetPlayerPos(playerid, ax, ay, az);
    SetPlayerVirtualWorld(target, GetPlayerVirtualWorld(playerid));
    SetPlayerInterior   (target, GetPlayerInterior(playerid));
    SetPlayerPos        (target, ax + 1.0, ay, az);

    new msg[96];
    format(msg, sizeof(msg),
        "  {FF8800}[TP] {FFFFFF}Admin {FF8800}%s {FFFFFF}memindahkan Anda.",
        g_Player[playerid][p_Name]);
    SendClientMessage(target, COL_ORANGE, msg);

    format(msg, sizeof(msg),
        "  {44FF44}[TP] {00C8FF}%s {FFFFFF}berhasil dipindahkan.",
        g_Player[target][p_Name]);
    SendClientMessage(playerid, COL_GREEN, msg);
    return 1;
}

// =============================================================================
// /ann [pesan] — server announcement
// Level: MOD
// =============================================================================
CMD:ann(playerid, params[]) {
    REQUIRE_ADMIN(ADMIN_MOD)

    if (Util_IsEmpty(params)) {
        SendClientMessage(playerid, COL_RED, "  [!] Penggunaan: /ann [pesan]");
        return 1;
    }

    new msg[256];
    format(msg, sizeof(msg),
        "  {FF8800}[Pengumuman] {FFFFFF}%s", params);
    SendClientMessageToAll(COL_ORANGE, msg);

    printf("[Admin] ANN  admin=%s  msg=%s",
        g_Player[playerid][p_Name], params);
    return 1;
}

// =============================================================================
// /players — lihat semua player online (admin only)
// Level: MOD
// =============================================================================
CMD:players(playerid, params[]) {
    REQUIRE_ADMIN(ADMIN_MOD)

    SendClientMessage(playerid, COL_LIGHTBLUE,
        "  ──── {FFFFFF}Player Online {00C8FF}────");

    new count = 0, str[96];
    foreach (new i : Player) {
        if (!g_Player[i][p_LoggedIn]) continue;
        format(str, sizeof(str),
            "  {AAAAAA}[%d] {FFFFFF}%-20s {888888}Lv.%d  Admin:%d  Ping:%d",
            i,
            g_Player[i][p_Name],
            g_Player[i][p_Level],
            g_Player[i][p_Admin],
            GetPlayerPing(i));
        SendClientMessage(playerid, -1, str);
        count++;
    }

    format(str, sizeof(str),
        "  {888888}Total: %d player online.", count);
    SendClientMessage(playerid, COL_GREY, str);
    return 1;
}

// =============================================================================
// INTERNAL: kirim pesan ke semua admin >= minLevel
// =============================================================================
stock Admin_Announce(const msg[], minLevel = ADMIN_MOD) {
    foreach (new i : Player) {
        if (g_Player[i][p_Admin] >= minLevel)
            SendClientMessage(i, COL_ORANGE, msg);
    }
}

// Bersihkan macro agar tidak leak ke file lain
#undef REQUIRE_ADMIN
