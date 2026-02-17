/*
 * hud.pwn — Player textdraws (HUD)
 * textdraw-streamer.inc meredefine CreatePlayerTextDraw → CreateDynamicPlayerTextDraw
 * Jadi pakai API standar SA-MP — otomatis dynamic
 * Depends on: data.pwn
 */

#if defined _HUD_PWN
    #endinput
#endif
#define _HUD_PWN

// ─── Handle per player ────────────────────────────────────────────────────────
static PlayerText:ptd_BgNama    [MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static PlayerText:ptd_Nama      [MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static PlayerText:ptd_BgMakan   [MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static PlayerText:ptd_BgMinum   [MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static PlayerText:ptd_BarMakan  [MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static PlayerText:ptd_BarMinum  [MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static PlayerText:ptd_BgSpedo   [MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static PlayerText:ptd_Speed     [MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static PlayerText:ptd_SpeedMph  [MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static PlayerText:ptd_Fuel      [MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static PlayerText:ptd_Hp        [MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static PlayerText:ptd_Lock      [MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

// ─── Buat semua HUD untuk satu player ────────────────────────────────────────
stock HUD_Create(playerid) {
    // BG Nama
    ptd_BgNama[playerid] = CreatePlayerTextDraw(playerid, 498.0, 107.0, "LD_SPAC:white");
    PlayerTextDrawTextSize      (playerid, ptd_BgNama[playerid], 110.0, 21.0);
    PlayerTextDrawAlignment     (playerid, ptd_BgNama[playerid], 1);
    PlayerTextDrawColor         (playerid, ptd_BgNama[playerid], 200);
    PlayerTextDrawSetShadow     (playerid, ptd_BgNama[playerid], 0);
    PlayerTextDrawSetOutline    (playerid, ptd_BgNama[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, ptd_BgNama[playerid], 255);
    PlayerTextDrawFont          (playerid, ptd_BgNama[playerid], 4);
    PlayerTextDrawSetProportional(playerid, ptd_BgNama[playerid], 1);

    // Nama Player
    ptd_Nama[playerid] = CreatePlayerTextDraw(playerid, 521.0, 109.0,
        g_Player[playerid][p_Name]);
    PlayerTextDrawLetterSize    (playerid, ptd_Nama[playerid], 0.349, 1.498);
    PlayerTextDrawAlignment     (playerid, ptd_Nama[playerid], 1);
    PlayerTextDrawColor         (playerid, ptd_Nama[playerid], -56);
    PlayerTextDrawSetShadow     (playerid, ptd_Nama[playerid], 1);
    PlayerTextDrawSetOutline    (playerid, ptd_Nama[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, ptd_Nama[playerid], 150);
    PlayerTextDrawFont          (playerid, ptd_Nama[playerid], 0);
    PlayerTextDrawSetProportional(playerid, ptd_Nama[playerid], 1);

    // BG Makan
    ptd_BgMakan[playerid] = CreatePlayerTextDraw(playerid, 498.0, 130.0, "LD_SPAC:white");
    PlayerTextDrawTextSize      (playerid, ptd_BgMakan[playerid], 52.0, 17.0);
    PlayerTextDrawAlignment     (playerid, ptd_BgMakan[playerid], 1);
    PlayerTextDrawColor         (playerid, ptd_BgMakan[playerid], 200);
    PlayerTextDrawSetShadow     (playerid, ptd_BgMakan[playerid], 0);
    PlayerTextDrawSetOutline    (playerid, ptd_BgMakan[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, ptd_BgMakan[playerid], 255);
    PlayerTextDrawFont          (playerid, ptd_BgMakan[playerid], 4);
    PlayerTextDrawSetProportional(playerid, ptd_BgMakan[playerid], 1);

    // Bar Makan
    ptd_BarMakan[playerid] = CreatePlayerTextDraw(playerid, 522.0, 133.0, "100");
    PlayerTextDrawLetterSize    (playerid, ptd_BarMakan[playerid], 0.200, 1.098);
    PlayerTextDrawAlignment     (playerid, ptd_BarMakan[playerid], 1);
    PlayerTextDrawColor         (playerid, ptd_BarMakan[playerid], -56);
    PlayerTextDrawSetShadow     (playerid, ptd_BarMakan[playerid], 0);
    PlayerTextDrawSetOutline    (playerid, ptd_BarMakan[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, ptd_BarMakan[playerid], 255);
    PlayerTextDrawFont          (playerid, ptd_BarMakan[playerid], 1);
    PlayerTextDrawSetProportional(playerid, ptd_BarMakan[playerid], 1);

    // BG Minum
    ptd_BgMinum[playerid] = CreatePlayerTextDraw(playerid, 555.0, 130.0, "LD_SPAC:white");
    PlayerTextDrawTextSize      (playerid, ptd_BgMinum[playerid], 53.0, 17.0);
    PlayerTextDrawAlignment     (playerid, ptd_BgMinum[playerid], 1);
    PlayerTextDrawColor         (playerid, ptd_BgMinum[playerid], 200);
    PlayerTextDrawSetShadow     (playerid, ptd_BgMinum[playerid], 0);
    PlayerTextDrawSetOutline    (playerid, ptd_BgMinum[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, ptd_BgMinum[playerid], 255);
    PlayerTextDrawFont          (playerid, ptd_BgMinum[playerid], 4);
    PlayerTextDrawSetProportional(playerid, ptd_BgMinum[playerid], 1);

    // Bar Minum
    ptd_BarMinum[playerid] = CreatePlayerTextDraw(playerid, 579.0, 133.0, "100");
    PlayerTextDrawLetterSize    (playerid, ptd_BarMinum[playerid], 0.200, 1.098);
    PlayerTextDrawAlignment     (playerid, ptd_BarMinum[playerid], 1);
    PlayerTextDrawColor         (playerid, ptd_BarMinum[playerid], -56);
    PlayerTextDrawSetShadow     (playerid, ptd_BarMinum[playerid], 0);
    PlayerTextDrawSetOutline    (playerid, ptd_BarMinum[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, ptd_BarMinum[playerid], 255);
    PlayerTextDrawFont          (playerid, ptd_BarMinum[playerid], 1);
    PlayerTextDrawSetProportional(playerid, ptd_BarMinum[playerid], 1);

    // BG Speedometer
    ptd_BgSpedo[playerid] = CreatePlayerTextDraw(playerid, 517.0, 343.0, "LD_SPAC:white");
    PlayerTextDrawTextSize      (playerid, ptd_BgSpedo[playerid], 89.0, 87.0);
    PlayerTextDrawAlignment     (playerid, ptd_BgSpedo[playerid], 1);
    PlayerTextDrawColor         (playerid, ptd_BgSpedo[playerid], 200);
    PlayerTextDrawSetShadow     (playerid, ptd_BgSpedo[playerid], 0);
    PlayerTextDrawSetOutline    (playerid, ptd_BgSpedo[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, ptd_BgSpedo[playerid], 255);
    PlayerTextDrawFont          (playerid, ptd_BgSpedo[playerid], 4);
    PlayerTextDrawSetProportional(playerid, ptd_BgSpedo[playerid], 1);

    // Speed value
    ptd_Speed[playerid] = CreatePlayerTextDraw(playerid, 556.0, 348.0, "0");
    PlayerTextDrawLetterSize    (playerid, ptd_Speed[playerid], 0.229, 1.297);
    PlayerTextDrawAlignment     (playerid, ptd_Speed[playerid], 1);
    PlayerTextDrawColor         (playerid, ptd_Speed[playerid], -1);
    PlayerTextDrawSetShadow     (playerid, ptd_Speed[playerid], 1);
    PlayerTextDrawSetOutline    (playerid, ptd_Speed[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, ptd_Speed[playerid], 150);
    PlayerTextDrawFont          (playerid, ptd_Speed[playerid], 1);
    PlayerTextDrawSetProportional(playerid, ptd_Speed[playerid], 1);

    // Speed unit
    ptd_SpeedMph[playerid] = CreatePlayerTextDraw(playerid, 576.0, 348.0, "Km/h");
    PlayerTextDrawLetterSize    (playerid, ptd_SpeedMph[playerid], 0.229, 1.297);
    PlayerTextDrawAlignment     (playerid, ptd_SpeedMph[playerid], 1);
    PlayerTextDrawColor         (playerid, ptd_SpeedMph[playerid], -1);
    PlayerTextDrawSetShadow     (playerid, ptd_SpeedMph[playerid], 1);
    PlayerTextDrawSetOutline    (playerid, ptd_SpeedMph[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, ptd_SpeedMph[playerid], 150);
    PlayerTextDrawFont          (playerid, ptd_SpeedMph[playerid], 1);
    PlayerTextDrawSetProportional(playerid, ptd_SpeedMph[playerid], 1);

    // Fuel
    ptd_Fuel[playerid] = CreatePlayerTextDraw(playerid, 556.0, 368.0, "100");
    PlayerTextDrawLetterSize    (playerid, ptd_Fuel[playerid], 0.229, 1.297);
    PlayerTextDrawAlignment     (playerid, ptd_Fuel[playerid], 1);
    PlayerTextDrawColor         (playerid, ptd_Fuel[playerid], -1);
    PlayerTextDrawSetShadow     (playerid, ptd_Fuel[playerid], 1);
    PlayerTextDrawSetOutline    (playerid, ptd_Fuel[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, ptd_Fuel[playerid], 150);
    PlayerTextDrawFont          (playerid, ptd_Fuel[playerid], 1);
    PlayerTextDrawSetProportional(playerid, ptd_Fuel[playerid], 1);

    // HP
    ptd_Hp[playerid] = CreatePlayerTextDraw(playerid, 556.0, 390.0, "100");
    PlayerTextDrawLetterSize    (playerid, ptd_Hp[playerid], 0.229, 1.297);
    PlayerTextDrawAlignment     (playerid, ptd_Hp[playerid], 1);
    PlayerTextDrawColor         (playerid, ptd_Hp[playerid], -1);
    PlayerTextDrawSetShadow     (playerid, ptd_Hp[playerid], 1);
    PlayerTextDrawSetOutline    (playerid, ptd_Hp[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, ptd_Hp[playerid], 150);
    PlayerTextDrawFont          (playerid, ptd_Hp[playerid], 1);
    PlayerTextDrawSetProportional(playerid, ptd_Hp[playerid], 1);

    // Lock status
    ptd_Lock[playerid] = CreatePlayerTextDraw(playerid, 556.0, 411.0, "LOCKED");
    PlayerTextDrawLetterSize    (playerid, ptd_Lock[playerid], 0.229, 1.297);
    PlayerTextDrawAlignment     (playerid, ptd_Lock[playerid], 1);
    PlayerTextDrawColor         (playerid, ptd_Lock[playerid], 1018393087);
    PlayerTextDrawSetShadow     (playerid, ptd_Lock[playerid], 1);
    PlayerTextDrawSetOutline    (playerid, ptd_Lock[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, ptd_Lock[playerid], 150);
    PlayerTextDrawFont          (playerid, ptd_Lock[playerid], 1);
    PlayerTextDrawSetProportional(playerid, ptd_Lock[playerid], 1);
}

// ─── Show ─────────────────────────────────────────────────────────────────────
stock HUD_Show(playerid) {
    HUD_Create(playerid);

    PlayerTextDrawShow(playerid, ptd_BgNama[playerid]);
    PlayerTextDrawShow(playerid, ptd_Nama[playerid]);
    PlayerTextDrawShow(playerid, ptd_BgMakan[playerid]);
    PlayerTextDrawShow(playerid, ptd_BarMakan[playerid]);
    PlayerTextDrawShow(playerid, ptd_BgMinum[playerid]);
    PlayerTextDrawShow(playerid, ptd_BarMinum[playerid]);
    // Speedometer hidden by default — muncul saat masuk kendaraan
}

// ─── Destroy ──────────────────────────────────────────────────────────────────
stock HUD_Destroy(playerid) {
    PlayerTextDrawDestroy(playerid, ptd_BgNama[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_Nama[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_BgMakan[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_BarMakan[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_BgMinum[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_BarMinum[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_BgSpedo[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_Speed[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_SpeedMph[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_Fuel[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_Hp[playerid]);
    PlayerTextDrawDestroy(playerid, ptd_Lock[playerid]);
}

// ─── Update speedometer ───────────────────────────────────────────────────────
stock HUD_UpdateVehicle(playerid) {
    if (!IsPlayerInAnyVehicle(playerid)) {
        PlayerTextDrawHide(playerid, ptd_BgSpedo[playerid]);
        PlayerTextDrawHide(playerid, ptd_Speed[playerid]);
        PlayerTextDrawHide(playerid, ptd_SpeedMph[playerid]);
        PlayerTextDrawHide(playerid, ptd_Fuel[playerid]);
        PlayerTextDrawHide(playerid, ptd_Hp[playerid]);
        PlayerTextDrawHide(playerid, ptd_Lock[playerid]);
        return;
    }

    new vid = GetPlayerVehicleID(playerid);
    new Float:vx, Float:vy, Float:vz;
    GetVehicleVelocity(vid, vx, vy, vz);

    new spd = floatround(floatsqroot(vx*vx + vy*vy + vz*vz) * 180.0);
    new Float:hp;
    GetVehicleHealth(vid, hp);

    new str[16];
    format(str, sizeof(str), "%d", spd);
    PlayerTextDrawSetString(playerid, ptd_Speed[playerid], str);

    format(str, sizeof(str), "%d", floatround(hp / 10.0));
    PlayerTextDrawSetString(playerid, ptd_Hp[playerid], str);

    PlayerTextDrawShow(playerid, ptd_BgSpedo[playerid]);
    PlayerTextDrawShow(playerid, ptd_Speed[playerid]);
    PlayerTextDrawShow(playerid, ptd_SpeedMph[playerid]);
    PlayerTextDrawShow(playerid, ptd_Fuel[playerid]);
    PlayerTextDrawShow(playerid, ptd_Hp[playerid]);
    PlayerTextDrawShow(playerid, ptd_Lock[playerid]);
}

// ─── Update hunger/thirst ─────────────────────────────────────────────────────
stock HUD_SetHunger(playerid, value) {
    new str[8];
    format(str, sizeof(str), "%d", value);
    PlayerTextDrawSetString(playerid, ptd_BarMakan[playerid], str);
}

stock HUD_SetThirst(playerid, value) {
    new str[8];
    format(str, sizeof(str), "%d", value);
    PlayerTextDrawSetString(playerid, ptd_BarMinum[playerid], str);
}