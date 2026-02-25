// =============================================================================
// filterscripts/voice_manager.pwn
// Deskripsi : SampVoice sebagai filterscript (WAJIB — tidak bisa di gamemode)
//             Gamemode berkomunikasi via CallRemoteFunction
// Dependensi: sampvoice.inc
// Author    : Vibe Dev Team
// Tanggal   : 2026
// =============================================================================
#define FILTERSCRIPT

#include <a_samp>
#undef MAX_PLAYERS
#define MAX_PLAYERS 250

#include <streamer>
#include <sampvoice>
#include <sscanf2>

// ─── Stream per player ────────────────────────────────────────────────────────
static SV_PTR: s_LocalStream[MAX_PLAYERS];

// ─── Stream admin global ──────────────────────────────────────────────────────
static SV_PTR: s_AdminStream = SV_NULL;

// =============================================================================
// INIT
// =============================================================================
public OnFilterScriptInit() {
    SvInit(24000);  // 24kbps

    s_AdminStream = SvCreateGStream(0xFF8800FF, "Admin");

    for (new i = 0; i < MAX_PLAYERS; i++) {
        s_LocalStream[i] = SV_NULL;
    }

    print("[Voice] SampVoice filterscript aktif.");
    print("[Voice] Bitrate: 24000  |  Admin stream: dibuat");
    return 1;
}

public OnFilterScriptExit() {
    for (new i = 0; i < MAX_PLAYERS; i++) {
        if (s_LocalStream[i] != SV_NULL) {
            SvDeleteStream(s_LocalStream[i]);
            s_LocalStream[i] = SV_NULL;
        }
    }
    if (s_AdminStream != SV_NULL) {
        SvDeleteStream(s_AdminStream);
        s_AdminStream = SV_NULL;
    }
    print("[Voice] SampVoice dibersihkan.");
    return 1;
}

// =============================================================================
// PLAYER CONNECT
// =============================================================================
public OnPlayerConnect(playerid) {
    // Buat proximity stream untuk player ini
    // 20.0 = radius dalam unit SA-MP (sekitar 20 meter)
    s_LocalStream[playerid] = SvCreateSLStreamAtPlayer(
        20.0,           // radius
        playerid,       // player yang jadi pusat stream
        0xFFFFFFFF,     // warna stream
        "Local"         // nama stream
    );

    if (s_LocalStream[playerid] != SV_NULL) {
        // Player ini adalah speaker default-nya sendiri
        SvAttachSpeakerToStream(s_LocalStream[playerid], playerid);
    }

    // Set push-to-talk key: B = 0x42
    SvAddKey(playerid, 0x42);

    printf("[Voice] Stream dibuat untuk player %d", playerid);
    return 1;
}

// =============================================================================
// PLAYER DISCONNECT
// =============================================================================
public OnPlayerDisconnect(playerid, reason) {
    if (s_LocalStream[playerid] != SV_NULL) {
        SvDeleteStream(s_LocalStream[playerid]);
        s_LocalStream[playerid] = SV_NULL;
    }
    return 1;
}

// =============================================================================
// KEY EVENTS
// =============================================================================
public OnPlayerActivationKeyPress(playerid, keyid) {
    // Mulai berbicara di local stream
    if (s_LocalStream[playerid] != SV_NULL) {
        SvAttachSpeakerToStream(s_LocalStream[playerid], playerid);
    }
}

public OnPlayerActivationKeyRelease(playerid, keyid) {
    // Berhenti berbicara
    if (s_LocalStream[playerid] != SV_NULL) {
        SvDetachSpeakerFromStream(s_LocalStream[playerid], playerid);
    }
}

// =============================================================================
// API — dipanggil dari gamemode via CallRemoteFunction
// =============================================================================

// Mute player
forward Voice_MutePlayer(playerid);
public  Voice_MutePlayer(playerid) {
    if (!IsPlayerConnected(playerid)) return 0;
    SvMutePlayerEnable(playerid);
    printf("[Voice] Player %d dimute.", playerid);
    return 1;
}

// Unmute player
forward Voice_UnmutePlayer(playerid);
public  Voice_UnmutePlayer(playerid) {
    if (!IsPlayerConnected(playerid)) return 0;
    SvMutePlayerDisable(playerid);
    printf("[Voice] Player %d di-unmute.", playerid);
    return 1;
}

// Cek apakah player punya mic
forward Voice_HasMic(playerid);
public  Voice_HasMic(playerid) {
    if (!IsPlayerConnected(playerid)) return 0;
    return _:SvHasMicro(playerid);
}

// Tambahkan player ke admin stream (dengar dan bicara)
forward Voice_AddToAdminStream(playerid);
public  Voice_AddToAdminStream(playerid) {
    if (!IsPlayerConnected(playerid)) return 0;
    if (s_AdminStream == SV_NULL) return 0;
    SvAttachListenerToStream(s_AdminStream, playerid);
    SvAttachSpeakerToStream(s_AdminStream, playerid);
    printf("[Voice] Player %d ditambahkan ke admin stream.", playerid);
    return 1;
}

// Hapus player dari admin stream
forward Voice_RemoveFromAdminStream(playerid);
public  Voice_RemoveFromAdminStream(playerid) {
    if (!IsPlayerConnected(playerid)) return 0;
    if (s_AdminStream == SV_NULL) return 0;
    SvDetachListenerFromStream(s_AdminStream, playerid);
    SvDetachSpeakerFromStream(s_AdminStream, playerid);
    return 1;
}

// Set radius voice player (default 20.0)
forward Voice_SetRadius(playerid, Float:radius);
public  Voice_SetRadius(playerid, Float:radius) {
    if (!IsPlayerConnected(playerid)) return 0;
    if (s_LocalStream[playerid] == SV_NULL) return 0;
    // Hapus stream lama, buat baru dengan radius baru
    SvDeleteStream(s_LocalStream[playerid]);
    s_LocalStream[playerid] = SvCreateSLStreamAtPlayer(
        radius, playerid, 0xFFFFFFFF, "Local");
    if (s_LocalStream[playerid] != SV_NULL) {
        SvAttachSpeakerToStream(s_LocalStream[playerid], playerid);
    }
    return 1;
}
