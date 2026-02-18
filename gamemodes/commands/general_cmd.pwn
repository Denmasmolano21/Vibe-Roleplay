// commands/general_cmd.pwn — Command umum player
// Depends on: player/data.pwn, utils/

#if defined _CMD_GENERAL_PWN
    #endinput
#endif
#define _CMD_GENERAL_PWN

// =============================================================================
// /help — daftar command
// =============================================================================
CMD:help(playerid, params[]) {
    SendClientMessage(playerid, COL_LIGHTBLUE,
        "  ─────────────── {FFFFFF}Command {00C8FF}Umum {FFFFFF}───────────────");
    SendClientMessage(playerid, COL_WHITE,
        "  {AAAAAA}/stats     {FFFFFF}— Lihat statistik karakter Anda");
    SendClientMessage(playerid, COL_WHITE,
        "  {AAAAAA}/id        {FFFFFF}— Lihat ID player di sekitar");
    SendClientMessage(playerid, COL_WHITE,
        "  {AAAAAA}/waktu     {FFFFFF}— Jam server saat ini");
    SendClientMessage(playerid, COL_WHITE,
        "  {AAAAAA}/kebutuhan {FFFFFF}— Lihat level lapar & haus");
    SendClientMessage(playerid, COL_LIGHTBLUE,
        "  ───────────────────────────────────────");
    return 1;
}

// =============================================================================
// /stats — statistik karakter
// =============================================================================
CMD:stats(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) {
        SendClientMessage(playerid, COL_RED, "  [!] Belum login.");
        return 1;
    }

    new target = playerid;

    // Admin bisa cek stats player lain: /stats [id]
    if (g_Player[playerid][p_Admin] >= 1 && !Util_IsEmpty(params)) {
        if (Util_IsNumeric(params)) {
            target = strval(params);
            if (!IsPlayerConnected(target)) {
                SendClientMessage(playerid, COL_RED, "  [!] Player tidak ditemukan.");
                return 1;
            }
        }
    }

    new str[256];
    SendClientMessage(playerid, COL_LIGHTBLUE,
        "  ─────────── {FFFFFF}Statistik Karakter {00C8FF}───────────");

    format(str, sizeof(str),
        "  {AAAAAA}Nama   : {FFFFFF}%s {AAAAAA}(ID: %d)",
        g_Player[target][p_Name], target);
    SendClientMessage(playerid, -1, str);

    format(str, sizeof(str),
        "  {AAAAAA}Level  : {FFFFFF}%d",
        g_Player[target][p_Level]);
    SendClientMessage(playerid, -1, str);

    format(str, sizeof(str),
        "  {AAAAAA}Uang   : {44FF44}$%d  {AAAAAA}Bank: {44FF44}$%d",
        g_Player[target][p_Money], g_Player[target][p_Bank]);
    SendClientMessage(playerid, -1, str);

    format(str, sizeof(str),
        "  {AAAAAA}Lapar  : {E88B2C}%d%%   {AAAAAA}Haus: {2CA8E8}%d%%",
        g_Player[target][p_Hunger], g_Player[target][p_Thirst]);
    SendClientMessage(playerid, -1, str);

    SendClientMessage(playerid, COL_LIGHTBLUE,
        "  ──────────────────────────────────────────");
    return 1;
}

// =============================================================================
// /id — cek ID semua player di dekat Anda (radius 10 unit)
// =============================================================================
CMD:id(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;

    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);

    SendClientMessage(playerid, COL_LIGHTBLUE,
        "  ────── {FFFFFF}Player di Sekitar Anda {00C8FF}──────");

    new count = 0;
    foreach (new i : Player) {
        if (i == playerid || !g_Player[i][p_LoggedIn]) continue;
        if (GetPlayerVirtualWorld(i) != GetPlayerVirtualWorld(playerid)) continue;
        if (GetPlayerInterior(i)     != GetPlayerInterior(playerid))     continue;

        new Float:tx, Float:ty, Float:tz;
        GetPlayerPos(i, tx, ty, tz);

        if (Util_Dist3D(px, py, pz, tx, ty, tz) <= 10.0) {
            new str[96];
            format(str, sizeof(str), "  {AAAAAA}[%d] {FFFFFF}%s", i, g_Player[i][p_Name]);
            SendClientMessage(playerid, -1, str);
            count++;
        }
    }

    if (count == 0) {
        SendClientMessage(playerid, COL_GREY,
            "  {888888}Tidak ada player lain di sekitar Anda.");
    }
    SendClientMessage(playerid, COL_LIGHTBLUE,
        "  ────────────────────────────────────────");
    return 1;
}

// =============================================================================
// /waktu — jam server
// =============================================================================
CMD:waktu(playerid, params[]) {
    new t[16], msg[64];
    Util_TimeStr(t);
    format(msg, sizeof(msg), "  {AAAAAA}Waktu server: {FFFFFF}%s", t);
    SendClientMessage(playerid, COL_WHITE, msg);
    return 1;
}

// =============================================================================
// /kebutuhan — cek hunger & thirst secara detail
// =============================================================================
CMD:kebutuhan(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;

    new str[128];
    SendClientMessage(playerid, COL_LIGHTBLUE,
        "  ──────── {FFFFFF}Kebutuhan Karakter {00C8FF}────────");

    // Hunger
    new hunger = g_Player[playerid][p_Hunger];
    new hungerColor[8];
    if (hunger > NEEDS_WARN_LEVEL)       format(hungerColor, 8, "E88B2C");
    else if (hunger > NEEDS_CRIT_LEVEL)  format(hungerColor, 8, "FFCC00");
    else                                 format(hungerColor, 8, "FF4444");
    format(str, sizeof(str),
        "  {AAAAAA}Lapar : {%s}%d%%  {888888}%s",
        hungerColor, hunger,
        hunger > NEEDS_WARN_LEVEL ? "Normal" :
        hunger > NEEDS_CRIT_LEVEL ? "Perlu makan" : "KRITIS!"
    );
    SendClientMessage(playerid, -1, str);

    // Thirst
    new thirst = g_Player[playerid][p_Thirst];
    new thirstColor[8];
    if (thirst > NEEDS_WARN_LEVEL)       format(thirstColor, 8, "2CA8E8");
    else if (thirst > NEEDS_CRIT_LEVEL)  format(thirstColor, 8, "FFCC00");
    else                                 format(thirstColor, 8, "FF4444");
    format(str, sizeof(str),
        "  {AAAAAA}Haus  : {%s}%d%%  {888888}%s",
        thirstColor, thirst,
        thirst > NEEDS_WARN_LEVEL ? "Normal" :
        thirst > NEEDS_CRIT_LEVEL ? "Perlu minum" : "KRITIS!"
    );
    SendClientMessage(playerid, -1, str);

    SendClientMessage(playerid, COL_LIGHTBLUE,
        "  ───────────────────────────────────────");
    return 1;
}

// =============================================================================
// /respawn — respawn setelah mati (cooldown 30 detik)
// =============================================================================
CMD:respawn(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;

    if (!g_Player[playerid][p_IsDead]) {
        SendClientMessage(playerid, COL_GREY,
            "  {888888}Anda tidak sedang mati.");
        return 1;
    }

    new remaining = Player_RespawnCooldown(playerid);
    if (remaining > 0) {
        new str[96];
        format(str, sizeof(str),
            "  {FF4444}[!] {FFFFFF}Tunggu {FF4444}%d detik {FFFFFF}lagi untuk respawn.",
            remaining);
        SendClientMessage(playerid, COL_RED, str);
        return 1;
    }

    // Reset state sebelum spawn
    g_Player[playerid][p_IsDead] = false;
    Player_DoSpawn(playerid);
    return 1;
}
