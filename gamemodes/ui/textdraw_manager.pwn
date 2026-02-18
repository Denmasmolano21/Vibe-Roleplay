// textdraw_manager.pwn — Global textdraw (terlihat semua player)
//
// Global TDs: elemen yang tampil ke semua player sekaligus.
// Per-player TDs ada di hud.pwn (Create/Destroy per session).
//
// CATATAN: textdraw-streamer.inc redefine TextDrawCreate → CreateDynamicTD.
//          Semua fungsi TextDraw* di sini otomatis pakai dynamic version.

#if defined _TEXTDRAW_MANAGER_PWN
    #endinput
#endif
#define _TEXTDRAW_MANAGER_PWN

// =============================================================================
// GLOBAL HANDLES
// =============================================================================
new Text:g_TD_ServerName = Text:INVALID_TEXT_DRAW;
new Text:g_TD_ServerVer  = Text:INVALID_TEXT_DRAW;

// =============================================================================
// INIT — dipanggil dari OnGameModeInit (Phase 4)
// =============================================================================
stock TextDraw_InitGlobals() {
    // ── Nama server — pojok kanan atas ────────────────────────────────────────
    g_TD_ServerName = TextDrawCreate(487.0, 14.0, SERVER_NAME);
    TextDrawFont        (g_TD_ServerName, TEXT_DRAW_FONT_2);
    TextDrawLetterSize  (g_TD_ServerName, 0.28, 1.2);
    TextDrawColor       (g_TD_ServerName, 0xFFFFFFCC);
    TextDrawSetShadow   (g_TD_ServerName, 0);
    TextDrawSetOutline  (g_TD_ServerName, 1);
    TextDrawAlignment   (g_TD_ServerName, TEXT_DRAW_ALIGN_RIGHT);
    TextDrawUseBox      (g_TD_ServerName, false);
    TextDrawShowForAll  (g_TD_ServerName);

    // ── Versi — di bawah nama server ─────────────────────────────────────────
    g_TD_ServerVer = TextDrawCreate(487.0, 27.0, SERVER_VERSION);
    TextDrawFont        (g_TD_ServerVer, TEXT_DRAW_FONT_1);
    TextDrawLetterSize  (g_TD_ServerVer, 0.16, 0.7);
    TextDrawColor       (g_TD_ServerVer, 0x888888CC);
    TextDrawSetShadow   (g_TD_ServerVer, 0);
    TextDrawSetOutline  (g_TD_ServerVer, 1);
    TextDrawAlignment   (g_TD_ServerVer, TEXT_DRAW_ALIGN_RIGHT);
    TextDrawShowForAll  (g_TD_ServerVer);

    print("[TextDraw] Global TDs siap.");
}

// =============================================================================
// DESTROY — dipanggil dari OnGameModeExit
// =============================================================================
stock TextDraw_DestroyGlobals() {
    if (g_TD_ServerName != Text:INVALID_TEXT_DRAW) {
        TextDrawDestroy(g_TD_ServerName);
        g_TD_ServerName = Text:INVALID_TEXT_DRAW;
    }
    if (g_TD_ServerVer != Text:INVALID_TEXT_DRAW) {
        TextDrawDestroy(g_TD_ServerVer);
        g_TD_ServerVer = Text:INVALID_TEXT_DRAW;
    }
}
