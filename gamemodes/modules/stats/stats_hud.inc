/*
 *  Vibe Roleplay - Stats HUD
 *  File: modules/stats/stats_hud.inc
 */

#if defined _stats_hud_included
    #endinput
#endif
#define _stats_hud_included

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_iterate>

new Text:g_KOMA;
new Text:g_TITIK;

new PlayerText:ptd_BG_MINUM[MAX_PLAYERS];
new PlayerText:ptd_BG_MAKAN[MAX_PLAYERS];
new PlayerText:ptd_ICON_MINUM[MAX_PLAYERS];
new PlayerText:ptd_ICON_MAKAN[MAX_PLAYERS];
new PlayerText:ptd_BAR_MINUM[MAX_PLAYERS];
new PlayerText:ptd_BAR_MAKAN[MAX_PLAYERS];
new PlayerText:ptd_BG_NAMA[MAX_PLAYERS];
new PlayerText:ptd_NAMA_PLAYER[MAX_PLAYERS];
new bool:ptd_HUD_Created[MAX_PLAYERS];

stock HUD_InitGlobal()
{
    g_KOMA = TextDrawCreate(580.000, 72.000, ",");
    TextDrawLetterSize(g_KOMA, 0.488, 3.098);
    TextDrawAlignment(g_KOMA, 1);
    TextDrawColor(g_KOMA, 676996863);
    TextDrawSetShadow(g_KOMA, 0);
    TextDrawSetOutline(g_KOMA, 1);
    TextDrawBackgroundColor(g_KOMA, 255);
    TextDrawFont(g_KOMA, 2);
    TextDrawSetProportional(g_KOMA, 1);

    g_TITIK = TextDrawCreate(545.000, 67.000, ".");
    TextDrawLetterSize(g_TITIK, 0.449, 3.898);
    TextDrawAlignment(g_TITIK, 1);
    TextDrawColor(g_TITIK, 676996863);
    TextDrawSetShadow(g_TITIK, 0);
    TextDrawSetOutline(g_TITIK, 1);
    TextDrawBackgroundColor(g_TITIK, 255);
    TextDrawFont(g_TITIK, 3);
    TextDrawSetProportional(g_TITIK, 1);

    printf("[HUD] Global textdraws dimuat.");
    return 1;
}

stock HUD_DestroyGlobal()
{
    TextDrawDestroy(g_KOMA);
    TextDrawDestroy(g_TITIK);
    return 1;
}

stock HUD_Create(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (ptd_HUD_Created[playerid])
    {
        HUD_Destroy(playerid);
    }

    ptd_BG_MINUM[playerid] = CreatePlayerTextDraw(playerid, 555.000, 130.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ptd_BG_MINUM[playerid], 53.000, 17.000);
    PlayerTextDrawAlignment(playerid, ptd_BG_MINUM[playerid], 1);
    PlayerTextDrawColor(playerid, ptd_BG_MINUM[playerid], 200);
    PlayerTextDrawFont(playerid, ptd_BG_MINUM[playerid], 4);
    PlayerTextDrawSetProportional(playerid, ptd_BG_MINUM[playerid], 1);

    ptd_BG_MAKAN[playerid] = CreatePlayerTextDraw(playerid, 498.000, 130.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ptd_BG_MAKAN[playerid], 52.000, 17.000);
    PlayerTextDrawAlignment(playerid, ptd_BG_MAKAN[playerid], 1);
    PlayerTextDrawColor(playerid, ptd_BG_MAKAN[playerid], 200);
    PlayerTextDrawFont(playerid, ptd_BG_MAKAN[playerid], 4);
    PlayerTextDrawSetProportional(playerid, ptd_BG_MAKAN[playerid], 1);

    ptd_ICON_MINUM[playerid] = CreatePlayerTextDraw(playerid, 570.000, 133.000, "HUD:radar_diner");
    PlayerTextDrawTextSize(playerid, ptd_ICON_MINUM[playerid], -10.000, 10.000);
    PlayerTextDrawAlignment(playerid, ptd_ICON_MINUM[playerid], 1);
    PlayerTextDrawColor(playerid, ptd_ICON_MINUM[playerid], -1);
    PlayerTextDrawFont(playerid, ptd_ICON_MINUM[playerid], 4);
    PlayerTextDrawSetProportional(playerid, ptd_ICON_MINUM[playerid], 1);

    ptd_ICON_MAKAN[playerid] = CreatePlayerTextDraw(playerid, 514.000, 133.000, "HUD:radar_dateFood");
    PlayerTextDrawTextSize(playerid, ptd_ICON_MAKAN[playerid], -11.000, 10.000);
    PlayerTextDrawAlignment(playerid, ptd_ICON_MAKAN[playerid], 1);
    PlayerTextDrawColor(playerid, ptd_ICON_MAKAN[playerid], -1);
    PlayerTextDrawFont(playerid, ptd_ICON_MAKAN[playerid], 4);
    PlayerTextDrawSetProportional(playerid, ptd_ICON_MAKAN[playerid], 1);

    ptd_BAR_MINUM[playerid] = CreatePlayerTextDraw(playerid, 579.000, 133.000, "100");
    PlayerTextDrawLetterSize(playerid, ptd_BAR_MINUM[playerid], 0.200, 1.098);
    PlayerTextDrawAlignment(playerid, ptd_BAR_MINUM[playerid], 1);
    PlayerTextDrawColor(playerid, ptd_BAR_MINUM[playerid], -56);
    PlayerTextDrawFont(playerid, ptd_BAR_MINUM[playerid], 1);
    PlayerTextDrawSetProportional(playerid, ptd_BAR_MINUM[playerid], 1);

    ptd_BAR_MAKAN[playerid] = CreatePlayerTextDraw(playerid, 522.000, 133.000, "100");
    PlayerTextDrawLetterSize(playerid, ptd_BAR_MAKAN[playerid], 0.200, 1.098);
    PlayerTextDrawAlignment(playerid, ptd_BAR_MAKAN[playerid], 1);
    PlayerTextDrawColor(playerid, ptd_BAR_MAKAN[playerid], -56);
    PlayerTextDrawFont(playerid, ptd_BAR_MAKAN[playerid], 1);
    PlayerTextDrawSetProportional(playerid, ptd_BAR_MAKAN[playerid], 1);

    ptd_BG_NAMA[playerid] = CreatePlayerTextDraw(playerid, 498.000, 107.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ptd_BG_NAMA[playerid], 110.000, 21.000);
    PlayerTextDrawAlignment(playerid, ptd_BG_NAMA[playerid], 1);
    PlayerTextDrawColor(playerid, ptd_BG_NAMA[playerid], 200);
    PlayerTextDrawFont(playerid, ptd_BG_NAMA[playerid], 4);
    PlayerTextDrawSetProportional(playerid, ptd_BG_NAMA[playerid], 1);

    new name[MAX_PLAYER_NAME], displayName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    FormatRPName(name, displayName, sizeof(displayName));

    ptd_NAMA_PLAYER[playerid] = CreatePlayerTextDraw(playerid, 521.000, 109.000, displayName);
    PlayerTextDrawLetterSize(playerid, ptd_NAMA_PLAYER[playerid], 0.349, 1.498);
    PlayerTextDrawAlignment(playerid, ptd_NAMA_PLAYER[playerid], 1);
    PlayerTextDrawColor(playerid, ptd_NAMA_PLAYER[playerid], -56);
    PlayerTextDrawSetShadow(playerid, ptd_NAMA_PLAYER[playerid], 1);
    PlayerTextDrawSetOutline(playerid, ptd_NAMA_PLAYER[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, ptd_NAMA_PLAYER[playerid], 150);
    PlayerTextDrawFont(playerid, ptd_NAMA_PLAYER[playerid], 0);
    PlayerTextDrawSetProportional(playerid, ptd_NAMA_PLAYER[playerid], 1);

    ptd_HUD_Created[playerid] = true;
    return 1;
}

stock HUD_Show(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (!ptd_HUD_Created[playerid])
        return 0;

    TextDrawShowForPlayer(playerid, g_KOMA);
    TextDrawShowForPlayer(playerid, g_TITIK);

    PlayerTextDrawShow(playerid, ptd_BG_MINUM[playerid]);
    PlayerTextDrawShow(playerid, ptd_BG_MAKAN[playerid]);
    PlayerTextDrawShow(playerid, ptd_ICON_MINUM[playerid]);
    PlayerTextDrawShow(playerid, ptd_ICON_MAKAN[playerid]);
    PlayerTextDrawShow(playerid, ptd_BAR_MINUM[playerid]);
    PlayerTextDrawShow(playerid, ptd_BAR_MAKAN[playerid]);
    PlayerTextDrawShow(playerid, ptd_BG_NAMA[playerid]);
    PlayerTextDrawShow(playerid, ptd_NAMA_PLAYER[playerid]);
    return 1;
}

stock HUD_Hide(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    TextDrawHideForPlayer(playerid, g_KOMA);
    TextDrawHideForPlayer(playerid, g_TITIK);

    if (!ptd_HUD_Created[playerid])
        return 0;

    PlayerTextDrawHide(playerid, ptd_BG_MINUM[playerid]);
    PlayerTextDrawHide(playerid, ptd_BG_MAKAN[playerid]);
    PlayerTextDrawHide(playerid, ptd_ICON_MINUM[playerid]);
    PlayerTextDrawHide(playerid, ptd_ICON_MAKAN[playerid]);
    PlayerTextDrawHide(playerid, ptd_BAR_MINUM[playerid]);
    PlayerTextDrawHide(playerid, ptd_BAR_MAKAN[playerid]);
    PlayerTextDrawHide(playerid, ptd_BG_NAMA[playerid]);
    PlayerTextDrawHide(playerid, ptd_NAMA_PLAYER[playerid]);
    return 1;
}

stock HUD_Destroy(playerid)
{
    if (!ptd_HUD_Created[playerid])
        return 0;

    PlayerTextDrawDestroy(playerid, ptd_BG_MINUM[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_BG_MAKAN[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_ICON_MINUM[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_ICON_MAKAN[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_BAR_MINUM[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_BAR_MAKAN[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_BG_NAMA[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_NAMA_PLAYER[playerid]);

    ptd_HUD_Created[playerid] = false;
    return 1;
}

stock HUD_Update(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (!ptd_HUD_Created[playerid])
        return 0;

    new str[8];

    format(str, sizeof(str), "%d", PlayerData[playerid][pHunger]);
    PlayerTextDrawSetString(playerid, ptd_BAR_MAKAN[playerid], str);

    format(str, sizeof(str), "%d", PlayerData[playerid][pThirst]);
    PlayerTextDrawSetString(playerid, ptd_BAR_MINUM[playerid], str);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    ptd_HUD_Created[playerid] = false;
    return 1;
}
