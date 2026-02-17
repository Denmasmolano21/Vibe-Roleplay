// chat.pwn — Format chat RP server standar
//
// Sistem chat RP standar:
//   - Proximity chat  : pesan hanya diterima dalam radius tertentu
//   - /me             : * Nama melakukan sesuatu
//   - /do             : * deskripsi situasi (Nama)
//   - /b              : (( OOC lokal ))
//   - /ooc            : (( OOC global server ))
//   - /pm             : pesan pribadi
//   - /s              : teriak — radius 2x normal
//   - /w              : bisik — radius sangat kecil
//   - /ame            : /me + chat lokal
//   - OnPlayerText    : intercept → proximity chat
//
// Depends on: core/config.pwn, core/enums.pwn, player/data.pwn, utils/

#if defined _SYSTEMS_CHAT_PWN
    #endinput
#endif
#define _SYSTEMS_CHAT_PWN

// ─── Warna chat — standar server RP Indonesia ─────────────────────────────────
#define CHAT_COL_SAY        "{FFFFFF}"
#define CHAT_COL_ME         "{C2A2DA}"
#define CHAT_COL_DO         "{C2A2DA}"
#define CHAT_COL_OOC_LOCAL  "{AAAAAA}"
#define CHAT_COL_OOC_GLOBAL "{AAAAAA}"
#define CHAT_COL_PM_SEND    "{FFE100}"
#define CHAT_COL_PM_RECV    "{FFE100}"
#define CHAT_COL_SHOUT      "{FFFF66}"
#define CHAT_COL_WHISPER    "{888888}"
#define CHAT_COL_SERVER     "{FF8C00}"
#define CHAT_COL_ERROR_CHAT "{FF4444}"

// ─── Kirim pesan ke semua player dalam radius dari sumber ─────────────────────
static stock Chat_Proximity(source, Float:radius, const msg[]) {
    new Float:sx, Float:sy, Float:sz;
    GetPlayerPos(source, sx, sy, sz);

    foreach (new i : Player) {
        if (GetPlayerVirtualWorld(i) != GetPlayerVirtualWorld(source)) continue;
        if (GetPlayerInterior(i)     != GetPlayerInterior(source))     continue;

        new Float:tx, Float:ty, Float:tz;
        GetPlayerPos(i, tx, ty, tz);

        if (Util_Dist3D(sx, sy, sz, tx, ty, tz) <= radius)
            SendClientMessage(i, -1, msg);
    }
}

// =============================================================================
// INTERCEPT CHAT BIASA → PROXIMITY
// =============================================================================
hook OnPlayerText(playerid, text[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 0;

    new name[MAX_PLAYER_NAME + 1], msg[152];
    GetPlayerName(playerid, name, sizeof(name));

    // Format: Nama_Pemain berkata: "pesan"
    format(msg, sizeof(msg),
        CHAT_COL_SAY"%s : {FFFFFF}%s",
        name, text
    );
    Chat_Proximity(playerid, CHAT_RADIUS_NORMAL, msg);

    return 0; // return 0 = cegah SA-MP broadcast chat ke semua
}

// =============================================================================
// /me — aksi roleplaying karakter
// Format: * Nama_Pemain [aksi]
// =============================================================================
CMD:me(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;
    if (Util_IsEmpty(params)) {
        SendClientMessage(playerid, -1,
            CHAT_COL_ERROR_CHAT"Gunakan: /me [aksi]  Contoh: /me melambaikan tangan");
        return 1;
    }
    new name[MAX_PLAYER_NAME + 1], msg[152];
    GetPlayerName(playerid, name, sizeof(name));
    format(msg, sizeof(msg), CHAT_COL_ME"* %s %s", name, params);
    Chat_Proximity(playerid, CHAT_RADIUS_ME, msg);
    return 1;
}

// =============================================================================
// /do — deskripsi situasi / lingkungan
// Format: * [deskripsi] (Nama_Pemain)
// =============================================================================
CMD:do(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;
    if (Util_IsEmpty(params)) {
        SendClientMessage(playerid, -1,
            CHAT_COL_ERROR_CHAT"Gunakan: /do [situasi]  Contoh: /do Pintu terkunci rapat.");
        return 1;
    }
    new name[MAX_PLAYER_NAME + 1], msg[152];
    GetPlayerName(playerid, name, sizeof(name));
    format(msg, sizeof(msg),
        CHAT_COL_DO"* %s {888888}(%s)", params, name);
    Chat_Proximity(playerid, CHAT_RADIUS_DO, msg);
    return 1;
}

// =============================================================================
// /b — OOC lokal (hanya radius sekitar, bukan global)
// Format: (( Nama: pesan ))
// =============================================================================
CMD:b(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;
    if (Util_IsEmpty(params)) {
        SendClientMessage(playerid, -1,
            CHAT_COL_ERROR_CHAT"Gunakan: /b [pesan OOC]");
        return 1;
    }
    new name[MAX_PLAYER_NAME + 1], msg[152];
    GetPlayerName(playerid, name, sizeof(name));
    format(msg, sizeof(msg), CHAT_COL_OOC_LOCAL"(( %s: %s ))", name, params);
    Chat_Proximity(playerid, CHAT_RADIUS_NORMAL, msg);
    return 1;
}

// =============================================================================
// /ooc — OOC global seluruh server
// Format: (( Nama [ID]: pesan ))
// =============================================================================
CMD:ooc(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;
    if (Util_IsEmpty(params)) {
        SendClientMessage(playerid, -1,
            CHAT_COL_ERROR_CHAT"Gunakan: /ooc [pesan]");
        return 1;
    }
    new name[MAX_PLAYER_NAME + 1], msg[152];
    GetPlayerName(playerid, name, sizeof(name));
    format(msg, sizeof(msg),
        CHAT_COL_OOC_GLOBAL"(( %s [%d]: %s ))", name, playerid, params);
    SendClientMessageToAll(-1, msg);
    return 1;
}

// =============================================================================
// /pm — pesan pribadi
// Format kirim  : [PM → Tujuan]: pesan
// Format terima : [PM dari Pengirim]: pesan
// =============================================================================
CMD:pm(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;

    new targetId, message[128];
    if (sscanf(params, "dS(1)[128]", targetId, message)) {
        SendClientMessage(playerid, -1,
            CHAT_COL_ERROR_CHAT"Gunakan: /pm [ID] [pesan]");
        return 1;
    }
    if (!IsPlayerConnected(targetId) || targetId == playerid) {
        SendClientMessage(playerid, -1,
            CHAT_COL_ERROR_CHAT"[!] Player tidak ditemukan.");
        return 1;
    }
    if (!g_Player[targetId][p_LoggedIn]) {
        SendClientMessage(playerid, -1,
            CHAT_COL_ERROR_CHAT"[!] Player belum login.");
        return 1;
    }

    new sName[MAX_PLAYER_NAME + 1], tName[MAX_PLAYER_NAME + 1], msg[192];
    GetPlayerName(playerid, sName, sizeof(sName));
    GetPlayerName(targetId,  tName,  sizeof(tName));

    format(msg, sizeof(msg),
        CHAT_COL_PM_SEND"[PM → {FFFFFF}%s{FFE100}]: {FFFFFF}%s", tName, message);
    SendClientMessage(playerid, -1, msg);

    format(msg, sizeof(msg),
        CHAT_COL_PM_RECV"[PM dari {FFFFFF}%s{FFE100}]: {FFFFFF}%s", sName, message);
    SendClientMessage(targetId, -1, msg);

    printf("[PM] %s(%d) -> %s(%d): %s", sName, playerid, tName, targetId, message);
    return 1;
}

// =============================================================================
// /s — teriak, radius 2x normal
// Format: Nama berteriak: "pesan!"
// =============================================================================
CMD:s(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;
    if (Util_IsEmpty(params)) {
        SendClientMessage(playerid, -1,
            CHAT_COL_ERROR_CHAT"Gunakan: /s [pesan]");
        return 1;
    }
    new name[MAX_PLAYER_NAME + 1], msg[152];
    GetPlayerName(playerid, name, sizeof(name));
    format(msg, sizeof(msg),
        CHAT_COL_SHOUT"%s {CCCCCC}berteriak: {FFFF66}\"%s!\"", name, params);
    Chat_Proximity(playerid, CHAT_RADIUS_SHOUT, msg);
    return 1;
}

// =============================================================================
// /w — bisik, radius sangat kecil (3 unit)
// Format: Nama berbisik: "pesan"
// =============================================================================
CMD:w(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;
    if (Util_IsEmpty(params)) {
        SendClientMessage(playerid, -1,
            CHAT_COL_ERROR_CHAT"Gunakan: /w [pesan]");
        return 1;
    }
    new name[MAX_PLAYER_NAME + 1], msg[152];
    GetPlayerName(playerid, name, sizeof(name));
    format(msg, sizeof(msg),
        CHAT_COL_WHISPER"%s {666666}berbisik: {888888}\"%s\"", name, params);
    Chat_Proximity(playerid, CHAT_RADIUS_WHISPER, msg);
    return 1;
}

// =============================================================================
// /ame — /me versi announce (juga ke chat lokal, tanpa header nama)
// Format: * [aksi]
// =============================================================================
CMD:ame(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;
    if (Util_IsEmpty(params)) {
        SendClientMessage(playerid, -1,
            CHAT_COL_ERROR_CHAT"Gunakan: /ame [aksi]");
        return 1;
    }
    new name[MAX_PLAYER_NAME + 1], msg[152];
    GetPlayerName(playerid, name, sizeof(name));
    format(msg, sizeof(msg), CHAT_COL_ME"* %s %s", name, params);
    Chat_Proximity(playerid, CHAT_RADIUS_ME, msg);
    return 1;
}
