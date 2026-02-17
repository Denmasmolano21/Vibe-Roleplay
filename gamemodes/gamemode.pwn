/*
 * gamemode.pwn — Entry point utama Vibe Roleplay
 *
 * ATURAN INCLUDE ORDER:
 *   Tier 0 : Plugin includes (a_samp, a_mysql, dst)
 *   Tier 1 : Pawn.CMD — hook OnGameModeInit via ALS internal
 *   Tier 2 : y_hooks — SETELAH Pawn.CMD supaya bisa chain
 *   Tier 3+ : Modul kita, urutan dependency ketat
 *
 * KENAPA TIDAK ADA public OnGameModeInit():
 *   Pawn.CMD.inc sudah define public OnGameModeInit() sendiri
 *   dan redefine macro-nya ke PawnCmd_OnGameModeInit.
 *   y_hooks lalu chain "hook OnGameModeInit()" kita ke sana.
 *   Jangan pernah tulis public OnGameModeInit() secara manual.
 */

#pragma tabsize 0

// =============================================================================
// TIER 0 — Plugin & library includes
// =============================================================================
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

// =============================================================================
// TIER 1 — Core (tanpa dependensi)
// =============================================================================
#include "core\config.pwn"
#include "core\enums.pwn"

// =============================================================================
// TIER 2 — Pure utilities (tidak ada state global)
// =============================================================================
#include "utils\math.pwn"
#include "utils\string.pwn"
#include "utils\time.pwn"
#include "utils\validator.pwn"

// =============================================================================
// TIER 3 — Database connection
// =============================================================================
#include "database\connection.pwn"
#include "database\migrations.pwn"

// =============================================================================
// TIER 4 — Player data container
//          HARUS sebelum query_builder (QB pakai g_Player[])
//          HARUS sebelum semua player/*.pwn dan ui/*.pwn
// =============================================================================
#include "player\data.pwn"

// =============================================================================
// TIER 5 — UI
//          textdraw-streamer sudah di-include di Tier 0
// =============================================================================
#include "ui\textdraw_manager.pwn"
#include "ui\hud.pwn"

// =============================================================================
// TIER 6 — Database queries
//          Setelah data.pwn karena pakai g_Player[]
// =============================================================================
#include "database\query_builder.pwn"

// =============================================================================
// TIER 7 — Player logic
// =============================================================================
#include "player\spawning.pwn"
#include "player\anti_cheat.pwn"
#include "player\session.pwn"

// =============================================================================
// TIER 8 — Dialog router
// =============================================================================
#include "ui\dialog_router.pwn"

// =============================================================================
// TIER 9 — RP Systems
// =============================================================================
#include "systems\\chat\\chat.pwn"

// Future systems:
// #include "systems\\inventory\\inventory.pwn"
// #include "systems\\vehicles\\vehicle_system.pwn"

// =============================================================================
main() {
    print("  ======================================");
    print("  Vibe Roleplay  |  Production v1.0");
    print("  ======================================");
}

// =============================================================================
// INIT — y_hooks chain ke PawnCmd_OnGameModeInit secara otomatis
// =============================================================================
hook OnGameModeInit() {
    // Phase 1: Database
    if (!DB_Connect()) {
        print("[FATAL] MySQL gagal connect. Server shutdown.");
        SendRconCommand("exit");
        return 1;
    }
    DB_RunMigrations();

    // Phase 2: Server settings
    SetGameModeText("Vrp v1.0");
    ShowNameTags(true);
    ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
    EnableStuntBonusForAll(false);
    DisableInteriorEnterExits();
    SetNameTagDrawDistance(40.0);
    ManualVehicleEngineAndLights();
    UsePlayerPedAnims();

    // SA-MP WAJIB: minimal 1 AddPlayerClass terdaftar
    // agar SpawnPlayer() berfungsi dengan benar.
    // Kita pakai class dummy — spawn actual dihandle Player_DoSpawn via SetSpawnInfo.
    AddPlayerClass(SPAWN_SKIN, SPAWN_X, SPAWN_Y, SPAWN_Z, SPAWN_A, 0,0,0,0,0,0);

    // Phase 3: Streamer
    Streamer_SetTickRate(50);
    Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 500);
    Streamer_SetVisibleItems(STREAMER_TYPE_PICKUP, 50);

    // Phase 4: Global textdraws
    TextDraw_InitGlobals();

    // Phase 5: Start timers
    // y_timers: deklarasi "timer X[]" hanya mendaftarkan timer.
    // "repeat X();" yang benar-benar menjalankannya sebagai repeating timer.
    repeat Timer_HUD();
    repeat Timer_AC();
    repeat Timer_AutoSave();

    print("[Init] Server siap.");
    return 1;
}

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
// TIMERS — y_timers: tidak perlu forward/SetTimer manual
//
// FIX: timer bernama "AC_Tick" bentrok dengan stock AC_Tick() di anti_cheat.pwn
//      Solusi: timer diganti nama "Timer_AC", stock di anti_cheat.pwn
//      sudah diganti menjadi AC_CheckPlayer()
// =============================================================================

timer Timer_HUD[INTERVAL_HUD]() {
    foreach (new i : Player) {
        if (g_Player[i][p_LoggedIn]) {
            HUD_UpdateVehicle(i);
        }
    }
}

timer Timer_AC[INTERVAL_AC]() {
    foreach (new i : Player) {
        AC_CheckPlayer(i);
    }
}

timer Timer_AutoSave[INTERVAL_SAVE]() {
    new count = 0;
    foreach (new i : Player) {
        if (g_Player[i][p_LoggedIn]) {
            DB_SaveAccount(i);
            count++;
        }
    }
    printf("[AutoSave] %d player tersimpan.", count);
}

// =============================================================================
// COMMANDS
// =============================================================================

CMD:help(playerid, params[]) {
    SendClientMessage(playerid, COL_GREEN, "==============================");
    SendClientMessage(playerid, COL_WHITE, " /stats  /waktu  /rules");
    SendClientMessage(playerid, COL_GREEN, "==============================");
    return 1;
}

// FIX error 001 pada CMD:stats:
// Masalah: format() dengan string literal multi-baris menggunakan
//   MSG_* macro (yang berisi "{XXXXXX}") tidak bisa digabung
//   sebagai argument terpisah di Pawn.
// Solusi: tulis format string sebagai satu string literal biasa.
CMD:stats(playerid, params[]) {
    if (!g_Player[playerid][p_LoggedIn]) {
        SendClientMessage(playerid, COL_RED, "[!] Belum login.");
        return 1;
    }
    new str[192];
    format(str, sizeof(str),
        "{FFFFFF}Nama: {44FF44}%s  {FFFFFF}Level: {44FF44}%d  {FFFFFF}Uang: {44FF44}$%d",
        g_Player[playerid][p_Name],
        g_Player[playerid][p_Level],
        g_Player[playerid][p_Money]
    );
    SendClientMessage(playerid, -1, str);
    return 1;
}

CMD:waktu(playerid, params[]) {
    new t[16], msg[64];
    Util_TimeStr(t);
    format(msg, sizeof(msg), "[VRP] Waktu server: %s", t);
    SendClientMessage(playerid, COL_WHITE, msg);
    return 1;
}

// Command fallback — dipanggil Pawn.CMD jika perintah tidak ditemukan
public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
    if (!result) {
        SendClientMessage(playerid, COL_RED, "[!] Perintah tidak dikenal. /help");
    }
    return 1;
}
