/*
 * textdraw_manager.pwn — Global textdraws (KOMA, TITIK)
 * textdraw-streamer.inc sudah meredefine TextDrawCreate → CreateDynamicTextDraw
 * Jadi kita pakai TextDrawCreate biasa
 */

#if defined _TD_MANAGER_PWN
    #endinput
#endif
#define _TD_MANAGER_PWN

static Text:g_KOMA;
static Text:g_TITIK;

stock TextDraw_InitGlobals() {
    g_KOMA = TextDrawCreate(580.0, 72.0, ",");
    TextDrawLetterSize(g_KOMA, 0.488, 3.098);
    TextDrawAlignment(g_KOMA, 1);
    TextDrawColor(g_KOMA, 676996863);
    TextDrawSetShadow(g_KOMA, 0);
    TextDrawSetOutline(g_KOMA, 1);
    TextDrawBackgroundColor(g_KOMA, 255);
    TextDrawFont(g_KOMA, 2);
    TextDrawSetProportional(g_KOMA, 1);

    g_TITIK = TextDrawCreate(545.0, 67.0, ".");
    TextDrawLetterSize(g_TITIK, 0.449, 3.898);
    TextDrawAlignment(g_TITIK, 1);
    TextDrawColor(g_TITIK, 676996863);
    TextDrawSetShadow(g_TITIK, 0);
    TextDrawSetOutline(g_TITIK, 1);
    TextDrawBackgroundColor(g_TITIK, 255);
    TextDrawFont(g_TITIK, 3);
    TextDrawSetProportional(g_TITIK, 1);

    print("[TD] Global textdraws created");
}

stock TextDraw_DestroyGlobals() {
    TextDrawDestroy(g_KOMA);
    TextDrawDestroy(g_TITIK);
}