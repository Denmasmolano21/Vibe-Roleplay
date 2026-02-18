/*
 * gamemode.pwn — Entry point Vibe Roleplay
 *
 * INCLUDE ORDER (strict dependency):
 *   Tier 0  : Plugin includes
 *   Tier 1  : Pawn.CMD (sebelum y_hooks — ALS chain)
 *   Tier 2  : YSI — y_hooks, y_timers, y_iterate
 *   Tier 3  : core/      — config, enums
 *   Tier 4  : utils/     — math, string, time, validator
 *   Tier 5  : database/  — connection, migrations
 *   Tier 6  : player/data.pwn  (WAJIB sebelum semua pakai g_Player[])
 *   Tier 7  : ui/        — textdraw_manager, hud
 *   Tier 8  : database/query_builder
 *   Tier 9  : player/    — spawning, death, anti_cheat, session
 *   Tier 10 : ui/dialog_router
 *   Tier 11 : systems/   — survival
 *   Tier 12 : commands/  — SEMUA CMD di sini, zero CMD di file lain
 *
 * Full Voice Server — tidak ada chat system
 */

#pragma tabsize 0

// ─── Tier 0: Plugins ──────────────────────────────────────────────────────────
#include <a_samp>
#include <a_mysql>
#include <sscanf2>
#include <streamer>
#include <chrono>
#include <Pawn.CMD>
#include <Pawn.Regex>
#include <samp_bcrypt>
#include <crashdetect>
#include <profiler>
#include <KeyListener>
#include <textdraw-streamer>

#define YSI_NO_HEAP_MALLOC
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_iterate>

// ─── Tier 1: Core ─────────────────────────────────────────────────────────────
#include "core\config.pwn"
#include "core\enums.pwn"

// ─── Tier 2: Utils ────────────────────────────────────────────────────────────
#include "utils\math.pwn"
#include "utils\string.pwn"
#include "utils\time.pwn"
#include "utils\validator.pwn"

// ─── Tier 3: Database ─────────────────────────────────────────────────────────
#include "database\connection.pwn"
#include "database\migrations.pwn"

// ─── Tier 4: Player data ──────────────────────────────────────────────────────
#include "player\data.pwn"

// ─── Tier 5: UI ───────────────────────────────────────────────────────────────
#include "ui\textdraw_manager.pwn"
#include "ui\hud.pwn"

// ─── Tier 6: DB queries + dialog launchers ────────────────────────────────────
#include "database\query_builder.pwn"

// ─── Tier 7: Player logic ─────────────────────────────────────────────────────
#include "player\spawning.pwn"
#include "player\death.pwn"
#include "player\anti_cheat.pwn"
#include "player\session.pwn"

// ─── Tier 8: Dialog router ────────────────────────────────────────────────────
#include "ui\dialog_router.pwn"

// ─── Tier 9: Systems ──────────────────────────────────────────────────────────
#include "systems\survival\survival.pwn"

// ─── Tier 10: Commands ────────────────────────────────────────────────────────
#include "commands\general_cmd.pwn"
#include "commands\survival_cmd.pwn"
#include "commands\admin_cmd.pwn"
// #include "commands\vehicle_cmd.pwn"  // next

// =============================================================================
main() {
    print("  ==========================================");
    print("   Vibe Roleplay  |  " SERVER_VERSION);
    print("   Full Voice — No Chat System");
    print("  ==========================================");
}

// =============================================================================
// INIT
// =============================================================================
hook OnGameModeInit() {
    if (!DB_Connect()) {
        print("[FATAL] MySQL gagal connect. Shutdown.");
        SendRconCommand("exit");
        return 1;
    }
    DB_RunMigrations();

    SetGameModeText(SERVER_NAME " " SERVER_VERSION);
    ShowNameTags(true);
    ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
    EnableStuntBonusForAll(false);
    DisableInteriorEnterExits();
    SetNameTagDrawDistance(40.0);
    ManualVehicleEngineAndLights();
    UsePlayerPedAnims();

    // SA-MP: minimal 1 AddPlayerClass agar SpawnPlayer() berfungsi
    AddPlayerClass(SPAWN_SKIN, SPAWN_X, SPAWN_Y, SPAWN_Z, SPAWN_A,
        0, 0, 0, 0, 0, 0);

    Streamer_SetTickRate(50);
    Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 500);
    Streamer_SetVisibleItems(STREAMER_TYPE_PICKUP, 50);

    TextDraw_InitGlobals();

    repeat Timer_HUD();
    repeat Timer_AC();
    repeat Timer_AutoSave();
    repeat Timer_Survival();

    print("[Init] Vibe Roleplay siap.");
    return 1;
}

// =============================================================================
// EXIT
// =============================================================================
hook OnGameModeExit() {
    foreach (new i : Player) {
        if (g_Player[i][p_LoggedIn]) DB_SaveAccount(i);
    }
    TextDraw_DestroyGlobals();
    DB_Disconnect();
    print("[Exit] Shutdown bersih.");
    return 1;
}

// =============================================================================
// COMMAND FALLBACK
// =============================================================================
public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
    if (!result) {
        SendClientMessage(playerid, COL_RED,
            "  {FF4444}[!] {FFFFFF}Perintah tidak dikenal. Ketik {00C8FF}/help{FFFFFF}.");
    }
    return 1;
}

// =============================================================================
// TIMERS
// =============================================================================

// HUD — update speedometer tiap 1 detik
timer Timer_HUD[INTERVAL_HUD]() {
    foreach (new i : Player) {
        if (g_Player[i][p_LoggedIn]) HUD_UpdateVehicle(i);
    }
}

// Anti-cheat — tiap 3 detik
timer Timer_AC[INTERVAL_AC]() {
    foreach (new i : Player) AC_CheckPlayer(i);
}

// Auto-save — tiap 5 menit
timer Timer_AutoSave[INTERVAL_SAVE]() {
    new count = 0;
    foreach (new i : Player) {
        if (g_Player[i][p_LoggedIn]) {
            DB_SaveAccount(i);
            count++;
        }
    }
    if (count > 0) printf("[AutoSave] %d player tersimpan.", count);
}

// Survival decay — tiap 1 menit
timer Timer_Survival[INTERVAL_SURVIVAL]() {
    Survival_Tick();
}
