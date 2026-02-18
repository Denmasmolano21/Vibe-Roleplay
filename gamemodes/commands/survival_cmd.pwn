// commands/survival_cmd.pwn — /makan /minum
// Depends on: player/data.pwn, systems/survival/survival.pwn

#if defined _CMD_SURVIVAL_PWN
    #endinput
#endif
#define _CMD_SURVIVAL_PWN

static const s_FoodName[][]  = {"Burger","Pizza","Nasi Goreng","Sandwich","Kentang Goreng"};
static const s_FoodFill[]    = {35, 50, 60, 30, 20};
static const s_FoodPrice[]   = {150, 300, 250, 120, 80};

static const s_DrinkName[][] = {"Air Mineral","Jus Jeruk","Kopi","Soda","Susu"};
static const s_DrinkFill[]   = {40, 35, 25, 30, 45};
static const s_DrinkPrice[]  = {50, 200, 150, 100, 180};

// ─── /makan ───────────────────────────────────────────────────────────────────
CMD:makan(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;

    if (g_Player[playerid][p_Hunger] >= NEEDS_MAX) {
        SendClientMessage(playerid, COL_GREY, "  {888888}Anda tidak lapar.");
        return 1;
    }
    if (Util_IsEmpty(params) || !Util_IsNumeric(params)) {
        SendClientMessage(playerid, COL_LIGHTBLUE,
            "  ──── {FFFFFF}Menu Makanan {00C8FF}────");
        new str[96];
        for (new i = 0; i < sizeof(s_FoodName); i++) {
            format(str, sizeof(str),
                "  {AAAAAA}[%d] {FFFFFF}%-16s {E88B2C}+%d%% {888888}$%d",
                i + 1, s_FoodName[i], s_FoodFill[i], s_FoodPrice[i]);
            SendClientMessage(playerid, -1, str);
        }
        SendClientMessage(playerid, COL_GREY, "  {888888}/makan [1-5]");
        return 1;
    }
    new idx = strval(params) - 1;
    if (idx < 0 || idx >= sizeof(s_FoodName)) {
        SendClientMessage(playerid, COL_RED, "  [!] Pilihan tidak valid.");
        return 1;
    }
    if (g_Player[playerid][p_Money] < s_FoodPrice[idx]) {
        new str[80];
        format(str, sizeof(str),
            "  {FF4444}[!] {FFFFFF}Uang tidak cukup. Butuh {44FF44}$%d{FFFFFF}.", s_FoodPrice[idx]);
        SendClientMessage(playerid, -1, str);
        return 1;
    }
    Player_GiveMoney(playerid, -s_FoodPrice[idx]);
    Survival_Eat(playerid, s_FoodFill[idx]);
    new str[128];
    format(str, sizeof(str), \
        "  {44FF44}[v] {FFFFFF}Anda makan {E88B2C}%s{FFFFFF}. " \
        "Lapar {E88B2C}+%d%%{FFFFFF}.", \
        s_FoodName[idx], s_FoodFill[idx]);
    SendClientMessage(playerid, -1, str);
    return 1;
}

// ─── /minum ───────────────────────────────────────────────────────────────────
CMD:minum(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) return 1;

    if (g_Player[playerid][p_Thirst] >= NEEDS_MAX) {
        SendClientMessage(playerid, COL_GREY, "  {888888}Anda tidak haus.");
        return 1;
    }
    if (Util_IsEmpty(params) || !Util_IsNumeric(params)) {
        SendClientMessage(playerid, COL_LIGHTBLUE,
            "  ──── {FFFFFF}Menu Minuman {00C8FF}────");
        new str[96];
        for (new i = 0; i < sizeof(s_DrinkName); i++) {
            format(str, sizeof(str),
                "  {AAAAAA}[%d] {FFFFFF}%-16s {2CA8E8}+%d%% {888888}$%d",
                i + 1, s_DrinkName[i], s_DrinkFill[i], s_DrinkPrice[i]);
            SendClientMessage(playerid, -1, str);
        }
        SendClientMessage(playerid, COL_GREY, "  {888888}/minum [1-5]");
        return 1;
    }
    new idx = strval(params) - 1;
    if (idx < 0 || idx >= sizeof(s_DrinkName)) {
        SendClientMessage(playerid, COL_RED, "  [!] Pilihan tidak valid.");
        return 1;
    }
    if (g_Player[playerid][p_Money] < s_DrinkPrice[idx]) {
        new str[80];
        format(str, sizeof(str),
            "  {FF4444}[!] {FFFFFF}Uang tidak cukup. Butuh {44FF44}$%d{FFFFFF}.", s_DrinkPrice[idx]);
        SendClientMessage(playerid, -1, str);
        return 1;
    }
    Player_GiveMoney(playerid, -s_DrinkPrice[idx]);
    Survival_Drink(playerid, s_DrinkFill[idx]);
    new str[128];
    format(str, sizeof(str), \
        "  {44FF44}[v] {FFFFFF}Anda minum {2CA8E8}%s{FFFFFF}. " \
        "Haus {2CA8E8}+%d%%{FFFFFF}.", \
        s_DrinkName[idx], s_DrinkFill[idx]);
    SendClientMessage(playerid, -1, str);
    return 1;
}
