// ui/hud.pwn — Per-player HUD textdraws
//
// Layout (kiri bawah):
//   [Lapar] ████████░░  <- hunger bar
//   [Haus ] ███████░░░  <- thirst bar
//
// Speedometer (kanan bawah, hanya saat di kendaraan):
//   120 km/h
//
// Depends on: core/enums.pwn, core/config.pwn, player/data.pwn

#if defined _HUD_PWN
    #endinput
#endif
#define _HUD_PWN

// =============================================================================
// POSISI — koordinat SA-MP textdraw (640x480 virtual screen)
// =============================================================================
#define HUD_HUNGER_X        (5.0)
#define HUD_HUNGER_Y        (388.0)
#define HUD_HUNGER_W        (60.0)
#define HUD_HUNGER_H        (4.0)

#define HUD_THIRST_X        (5.0)
#define HUD_THIRST_Y        (396.0)
#define HUD_THIRST_W        (60.0)
#define HUD_THIRST_H        (4.0)

#define HUD_LABEL_X         (5.0)
#define HUD_LABEL_HUNGER_Y  (383.0)
#define HUD_LABEL_THIRST_Y  (391.0)

#define HUD_SPEED_X         (547.0)
#define HUD_SPEED_Y         (382.0)

// =============================================================================
// HANDLE ARRAY — satu set per player
// Dideklarasikan sebagai enum untuk type safety, tapi di-loop pakai index int
// =============================================================================
enum E_HUD_TD {
    td_HungerBg,
    td_HungerFill,
    td_ThirstBg,
    td_ThirstFill,
    td_LabelHunger,
    td_LabelThirst,
    td_SpeedBg,
    td_SpeedValue,
    td_SpeedUnit
};
#define HUD_TD_COUNT (9)   // harus sama dengan jumlah field E_HUD_TD

new PlayerText:g_HUD[MAX_PLAYERS][E_HUD_TD];

// =============================================================================
// HUD_INIT_HANDLES — set semua handle ke INVALID saat awal
// Dipanggil dari Player_Reset atau OnGameModeInit
// =============================================================================
stock HUD_InitHandles(playerid) {
    // Loop pakai index integer biasa — TIDAK cast ke E_HUD_TD
    // karena Pawn tidak support E_HUD_TD:i saat indexing array
    g_HUD[playerid][td_HungerBg]    = INVALID_TEXT_DRAW;
    g_HUD[playerid][td_HungerFill]  = INVALID_TEXT_DRAW;
    g_HUD[playerid][td_ThirstBg]    = INVALID_TEXT_DRAW;
    g_HUD[playerid][td_ThirstFill]  = INVALID_TEXT_DRAW;
    g_HUD[playerid][td_LabelHunger] = INVALID_TEXT_DRAW;
    g_HUD[playerid][td_LabelThirst] = INVALID_TEXT_DRAW;
    g_HUD[playerid][td_SpeedBg]     = INVALID_TEXT_DRAW;
    g_HUD[playerid][td_SpeedValue]  = INVALID_TEXT_DRAW;
    g_HUD[playerid][td_SpeedUnit]   = INVALID_TEXT_DRAW;
}

// =============================================================================
// HUD_CREATE — buat semua textdraw saat player spawn
// =============================================================================
stock HUD_Create(playerid) {
    // ── Hunger background
    g_HUD[playerid][td_HungerBg] = CreatePlayerTextDraw(playerid,
        HUD_HUNGER_X, HUD_HUNGER_Y, "LD_SPAC:white");
    PlayerTextDrawTextSize  (playerid, g_HUD[playerid][td_HungerBg], HUD_HUNGER_W, HUD_HUNGER_H);
    PlayerTextDrawColor     (playerid, g_HUD[playerid][td_HungerBg], 0x33333388);
    PlayerTextDrawFont      (playerid, g_HUD[playerid][td_HungerBg], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawUseBox    (playerid, g_HUD[playerid][td_HungerBg], true);

    // ── Hunger fill
    g_HUD[playerid][td_HungerFill] = CreatePlayerTextDraw(playerid,
        HUD_HUNGER_X, HUD_HUNGER_Y, "LD_SPAC:white");
    PlayerTextDrawTextSize  (playerid, g_HUD[playerid][td_HungerFill], HUD_HUNGER_W, HUD_HUNGER_H);
    PlayerTextDrawColor     (playerid, g_HUD[playerid][td_HungerFill], 0xE88B2CFF);
    PlayerTextDrawFont      (playerid, g_HUD[playerid][td_HungerFill], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawUseBox    (playerid, g_HUD[playerid][td_HungerFill], true);

    // ── Thirst background
    g_HUD[playerid][td_ThirstBg] = CreatePlayerTextDraw(playerid,
        HUD_THIRST_X, HUD_THIRST_Y, "LD_SPAC:white");
    PlayerTextDrawTextSize  (playerid, g_HUD[playerid][td_ThirstBg], HUD_THIRST_W, HUD_THIRST_H);
    PlayerTextDrawColor     (playerid, g_HUD[playerid][td_ThirstBg], 0x33333388);
    PlayerTextDrawFont      (playerid, g_HUD[playerid][td_ThirstBg], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawUseBox    (playerid, g_HUD[playerid][td_ThirstBg], true);

    // ── Thirst fill
    g_HUD[playerid][td_ThirstFill] = CreatePlayerTextDraw(playerid,
        HUD_THIRST_X, HUD_THIRST_Y, "LD_SPAC:white");
    PlayerTextDrawTextSize  (playerid, g_HUD[playerid][td_ThirstFill], HUD_THIRST_W, HUD_THIRST_H);
    PlayerTextDrawColor     (playerid, g_HUD[playerid][td_ThirstFill], 0x2CA8E8FF);
    PlayerTextDrawFont      (playerid, g_HUD[playerid][td_ThirstFill], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawUseBox    (playerid, g_HUD[playerid][td_ThirstFill], true);

    // ── Label Lapar
    g_HUD[playerid][td_LabelHunger] = CreatePlayerTextDraw(playerid,
        HUD_LABEL_X, HUD_LABEL_HUNGER_Y, "Lapar");
    PlayerTextDrawFont      (playerid, g_HUD[playerid][td_LabelHunger], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, g_HUD[playerid][td_LabelHunger], 0.15, 0.7);
    PlayerTextDrawColor     (playerid, g_HUD[playerid][td_LabelHunger], 0xE88B2CFF);
    PlayerTextDrawSetShadow (playerid, g_HUD[playerid][td_LabelHunger], 0);
    PlayerTextDrawSetOutline(playerid, g_HUD[playerid][td_LabelHunger], 1);

    // ── Label Haus
    g_HUD[playerid][td_LabelThirst] = CreatePlayerTextDraw(playerid,
        HUD_LABEL_X, HUD_LABEL_THIRST_Y, "Haus");
    PlayerTextDrawFont      (playerid, g_HUD[playerid][td_LabelThirst], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, g_HUD[playerid][td_LabelThirst], 0.15, 0.7);
    PlayerTextDrawColor     (playerid, g_HUD[playerid][td_LabelThirst], 0x2CA8E8FF);
    PlayerTextDrawSetShadow (playerid, g_HUD[playerid][td_LabelThirst], 0);
    PlayerTextDrawSetOutline(playerid, g_HUD[playerid][td_LabelThirst], 1);

    // ── Speed background
    g_HUD[playerid][td_SpeedBg] = CreatePlayerTextDraw(playerid,
        HUD_SPEED_X - 2.0, HUD_SPEED_Y - 2.0, "LD_SPAC:white");
    PlayerTextDrawTextSize  (playerid, g_HUD[playerid][td_SpeedBg], 88.0, 20.0);
    PlayerTextDrawColor     (playerid, g_HUD[playerid][td_SpeedBg], 0x00000066);
    PlayerTextDrawFont      (playerid, g_HUD[playerid][td_SpeedBg], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawUseBox    (playerid, g_HUD[playerid][td_SpeedBg], true);

    // ── Speed angka
    g_HUD[playerid][td_SpeedValue] = CreatePlayerTextDraw(playerid,
        HUD_SPEED_X, HUD_SPEED_Y, "0");
    PlayerTextDrawFont      (playerid, g_HUD[playerid][td_SpeedValue], TEXT_DRAW_FONT_2);
    PlayerTextDrawLetterSize(playerid, g_HUD[playerid][td_SpeedValue], 0.35, 1.5);
    PlayerTextDrawColor     (playerid, g_HUD[playerid][td_SpeedValue], 0xFFFFFFFF);
    PlayerTextDrawSetShadow (playerid, g_HUD[playerid][td_SpeedValue], 0);
    PlayerTextDrawSetOutline(playerid, g_HUD[playerid][td_SpeedValue], 1);
    PlayerTextDrawAlignment (playerid, g_HUD[playerid][td_SpeedValue], TEXT_DRAW_ALIGN_RIGHT);

    // ── Speed unit
    g_HUD[playerid][td_SpeedUnit] = CreatePlayerTextDraw(playerid,
        HUD_SPEED_X, HUD_SPEED_Y + 11.0, "km/h");
    PlayerTextDrawFont      (playerid, g_HUD[playerid][td_SpeedUnit], TEXT_DRAW_FONT_1);
    PlayerTextDrawLetterSize(playerid, g_HUD[playerid][td_SpeedUnit], 0.15, 0.7);
    PlayerTextDrawColor     (playerid, g_HUD[playerid][td_SpeedUnit], 0xAAAAAAAA);
    PlayerTextDrawSetShadow (playerid, g_HUD[playerid][td_SpeedUnit], 0);
    PlayerTextDrawSetOutline(playerid, g_HUD[playerid][td_SpeedUnit], 1);
    PlayerTextDrawAlignment (playerid, g_HUD[playerid][td_SpeedUnit], TEXT_DRAW_ALIGN_RIGHT);
}

// =============================================================================
// HUD_SHOW
// =============================================================================
stock HUD_Show(playerid) {
    HUD_Create(playerid);
    HUD_SetHunger(playerid, g_Player[playerid][p_Hunger]);
    HUD_SetThirst(playerid, g_Player[playerid][p_Thirst]);

    PlayerTextDrawShow(playerid, g_HUD[playerid][td_HungerBg]);
    PlayerTextDrawShow(playerid, g_HUD[playerid][td_HungerFill]);
    PlayerTextDrawShow(playerid, g_HUD[playerid][td_ThirstBg]);
    PlayerTextDrawShow(playerid, g_HUD[playerid][td_ThirstFill]);
    PlayerTextDrawShow(playerid, g_HUD[playerid][td_LabelHunger]);
    PlayerTextDrawShow(playerid, g_HUD[playerid][td_LabelThirst]);

    PlayerTextDrawHide(playerid, g_HUD[playerid][td_SpeedBg]);
    PlayerTextDrawHide(playerid, g_HUD[playerid][td_SpeedValue]);
    PlayerTextDrawHide(playerid, g_HUD[playerid][td_SpeedUnit]);
}

// =============================================================================
// HUD_DESTROY — safe: cek INVALID sebelum destroy, pakai index langsung
// =============================================================================
stock HUD_Destroy(playerid) {
    // Manual per-field — Pawn tidak support enum cast saat array index
    #define _HUD_SAFE_DESTROY(%1) \
        if (g_HUD[playerid][%1] != PlayerText:INVALID_TEXT_DRAW) { \
            PlayerTextDrawDestroy(playerid, g_HUD[playerid][%1]); \
            g_HUD[playerid][%1] = PlayerText:INVALID_TEXT_DRAW; \
        }

    _HUD_SAFE_DESTROY(td_HungerBg)
    _HUD_SAFE_DESTROY(td_HungerFill)
    _HUD_SAFE_DESTROY(td_ThirstBg)
    _HUD_SAFE_DESTROY(td_ThirstFill)
    _HUD_SAFE_DESTROY(td_LabelHunger)
    _HUD_SAFE_DESTROY(td_LabelThirst)
    _HUD_SAFE_DESTROY(td_SpeedBg)
    _HUD_SAFE_DESTROY(td_SpeedValue)
    _HUD_SAFE_DESTROY(td_SpeedUnit)

    #undef _HUD_SAFE_DESTROY
}

// =============================================================================
// HUD_SETHUNGER — update lebar bar proporsional + warna berubah
// =============================================================================
stock HUD_SetHunger(playerid, value) {
    if (g_HUD[playerid][td_HungerFill] == PlayerText:INVALID_TEXT_DRAW) return;

    new Float:w = (Float:value / Float:NEEDS_MAX) * HUD_HUNGER_W;
    if (w < 0.5) w = 0.5; // minimum agar tidak invisible

    new color;
    if      (value > NEEDS_WARN_LEVEL) color = 0xE88B2CFF;
    else if (value > NEEDS_CRIT_LEVEL) color = 0xFFCC00FF;
    else                               color = 0xFF4444FF;

    PlayerTextDrawTextSize(playerid, g_HUD[playerid][td_HungerFill], w, HUD_HUNGER_H);
    PlayerTextDrawColor   (playerid, g_HUD[playerid][td_HungerFill], color);
    PlayerTextDrawShow    (playerid, g_HUD[playerid][td_HungerFill]);
}

// =============================================================================
// HUD_SETTHIRST
// =============================================================================
stock HUD_SetThirst(playerid, value) {
    if (g_HUD[playerid][td_ThirstFill] == PlayerText:INVALID_TEXT_DRAW) return;

    new Float:w = (Float:value / Float:NEEDS_MAX) * HUD_THIRST_W;
    if (w < 0.5) w = 0.5;

    new color;
    if      (value > NEEDS_WARN_LEVEL) color = 0x2CA8E8FF;
    else if (value > NEEDS_CRIT_LEVEL) color = 0xFFCC00FF;
    else                               color = 0xFF4444FF;

    PlayerTextDrawTextSize(playerid, g_HUD[playerid][td_ThirstFill], w, HUD_THIRST_H);
    PlayerTextDrawColor   (playerid, g_HUD[playerid][td_ThirstFill], color);
    PlayerTextDrawShow    (playerid, g_HUD[playerid][td_ThirstFill]);
}

// =============================================================================
// HUD_UPDATEVEHICLE — dipanggil tiap Timer_HUD
// =============================================================================
stock HUD_UpdateVehicle(playerid) {
    if (!IsPlayerInAnyVehicle(playerid)) {
        PlayerTextDrawHide(playerid, g_HUD[playerid][td_SpeedBg]);
        PlayerTextDrawHide(playerid, g_HUD[playerid][td_SpeedValue]);
        PlayerTextDrawHide(playerid, g_HUD[playerid][td_SpeedUnit]);
        return;
    }

    new Float:vx, Float:vy, Float:vz;
    GetVehicleVelocity(GetPlayerVehicleID(playerid), vx, vy, vz);
    new speed = floatround(Util_VehicleSpeed(vx, vy, vz));

    new str[8];
    format(str, sizeof(str), "%d", speed);
    PlayerTextDrawSetString(playerid, g_HUD[playerid][td_SpeedValue], str);

    PlayerTextDrawShow(playerid, g_HUD[playerid][td_SpeedBg]);
    PlayerTextDrawShow(playerid, g_HUD[playerid][td_SpeedValue]);
    PlayerTextDrawShow(playerid, g_HUD[playerid][td_SpeedUnit]);
}
