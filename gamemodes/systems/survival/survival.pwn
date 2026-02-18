// systems/survival/survival.pwn — Sistem hunger & thirst
//
// Alur:
//   Timer_Survival (1 menit) → Survival_Tick()
//   Decay hunger -2/menit, thirst -3/menit
//   <= NEEDS_WARN  : warning di chat
//   <= NEEDS_CRIT  : HP berkurang tiap tick
//   Nilai minimal  : 0 (tidak pernah negatif)
//
// Depends on: core/config.pwn, player/data.pwn, ui/hud.pwn

#if defined _SURVIVAL_PWN
    #endinput
#endif
#define _SURVIVAL_PWN

// ─── Tick — dipanggil dari timer gamemode ─────────────────────────────────────
stock Survival_Tick() {
    foreach (new i : Player) {
        if (!g_Player[i][p_LoggedIn]) continue;
        if (g_Player[i][p_IsDead])    continue;
        Survival_DecayHunger(i);
        Survival_DecayThirst(i);
    }
}

// ─── Decay hunger ─────────────────────────────────────────────────────────────
static stock Survival_DecayHunger(playerid) {
    new val = g_Player[playerid][p_Hunger] - HUNGER_DECAY;
    if (val < NEEDS_MIN) val = NEEDS_MIN;
    g_Player[playerid][p_Hunger] = val;
    HUD_SetHunger(playerid, val);

    if (val <= NEEDS_CRIT_LEVEL) {
        new Float:hp;
        GetPlayerHealth(playerid, hp);
        hp -= HUNGER_CRIT_DMG;
        if (hp < 1.0) hp = 1.0;
        SetPlayerHealth(playerid, hp);
        SendClientMessage(playerid, COL_RED,
            "  {FF4444}[!] {FFFFFF}Anda sangat lapar! Segera cari makan.");
    } else if (val <= NEEDS_WARN_LEVEL) {
        SendClientMessage(playerid, COL_ORANGE,
            "  {FF8800}[!] {FFFFFF}Perut Anda mulai lapar.");
    }
}

// ─── Decay thirst ─────────────────────────────────────────────────────────────
static stock Survival_DecayThirst(playerid) {
    new val = g_Player[playerid][p_Thirst] - THIRST_DECAY;
    if (val < NEEDS_MIN) val = NEEDS_MIN;
    g_Player[playerid][p_Thirst] = val;
    HUD_SetThirst(playerid, val);

    if (val <= NEEDS_CRIT_LEVEL) {
        new Float:hp;
        GetPlayerHealth(playerid, hp);
        hp -= THIRST_CRIT_DMG;
        if (hp < 1.0) hp = 1.0;
        SetPlayerHealth(playerid, hp);
        SendClientMessage(playerid, COL_RED,
            "  {FF4444}[!] {FFFFFF}Anda sangat haus! Segera minum.");
    } else if (val <= NEEDS_WARN_LEVEL) {
        SendClientMessage(playerid, COL_ORANGE,
            "  {FF8800}[!] {FFFFFF}Tenggorokan Anda mulai kering.");
    }
}

// ─── API publik (dipanggil dari commands/survival_cmd.pwn) ────────────────────
stock Survival_Eat(playerid, amount) {
    new val = g_Player[playerid][p_Hunger] + amount;
    if (val > NEEDS_MAX) val = NEEDS_MAX;
    g_Player[playerid][p_Hunger] = val;
    HUD_SetHunger(playerid, val);
}

stock Survival_Drink(playerid, amount) {
    new val = g_Player[playerid][p_Thirst] + amount;
    if (val > NEEDS_MAX) val = NEEDS_MAX;
    g_Player[playerid][p_Thirst] = val;
    HUD_SetThirst(playerid, val);
}

stock Survival_GetHunger(playerid) { return g_Player[playerid][p_Hunger]; }
stock Survival_GetThirst(playerid) { return g_Player[playerid][p_Thirst]; }
