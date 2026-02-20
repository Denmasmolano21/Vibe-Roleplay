/*
 *  ██╗   ██╗██╗██████╗ ███████╗    ██████╗ ██████╗ 
 *  ██║   ██║██║██╔══██╗██╔════╝    ██╔══██╗██╔══██╗
 *  ██║   ██║██║██████╔╝█████╗      ██████╔╝██████╔╝
 *  ╚██╗ ██╔╝██║██╔══██╗██╔══╝      ██╔══██╗██╔═══╝ 
 *   ╚████╔╝ ██║██████╔╝███████╗    ██║  ██║██║     
 *    ╚═══╝  ╚═╝╚═════╝ ╚══════╝    ╚═╝  ╚═╝╚═╝     
 *
 *  Vibe Roleplay — SA-MP 0.3.7 Gamemode
 *  Version: 1.0.0
 *
 *  File ini hanya sebagai LOADER.
 *  Semua logic ada di folder config/, core/, modules/, commands/, utils/.
 */

// ============================================================================
//  Library Includes
// ============================================================================

#include <a_samp>
#include <a_mysql>
#include <sscanf2>
#include <streamer>
#include <Pawn.CMD>
#include <samp_bcrypt>
#include <crashdetect>
#include <textdraw-streamer>

#define YSI_NO_HEAP_MALLOC
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_iterate>

// ============================================================================
//  Config
// ============================================================================

#include "config\server_config.inc"
#include "config\dialog_ids.inc"
#include "config\colors.inc"

// ============================================================================
//  Utils
// ============================================================================

#include "utils\name_validator.inc"
#include "utils\messages.inc"

// ============================================================================
//  Core
// ============================================================================

#include "core\database.inc"
#include "core\player_data.inc"

// ============================================================================
//  Modules
// ============================================================================

#include "modules\auth\auth.inc"

// ============================================================================
//  Commands
// ============================================================================

#include "commands\cmd_general.inc"

// ============================================================================
//  Entry Point
// ============================================================================

main()
{
    print("  ");
    print("  =============================================");
    print("    Vibe Roleplay v1.0.0");
    print("    SA-MP 0.3.7 Gamemode");
    print("  =============================================");
    print("  ");
}

// ============================================================================
//  GameMode Init — Server settings & inisialisasi
// ============================================================================

public OnGameModeInit()
{
    // Inisialisasi name validator
    NameValidator_Init();

    // Server settings
    SetGameModeText("VRP v" SERVER_VERSION);
    ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
    ShowNameTags(1);
    SetNameTagDrawDistance(30.0);
    EnableStuntBonusForAll(0);
    DisableInteriorEnterExits();
    ManualVehicleEngineAndLights();
    UsePlayerPedAnims();

    // Tambahkan class default (diperlukan oleh SA-MP)
    AddPlayerClass(0, DEFAULT_SPAWN_X, DEFAULT_SPAWN_Y, DEFAULT_SPAWN_Z,
        DEFAULT_SPAWN_A, 0, 0, 0, 0, 0, 0);

    printf("[GAMEMODE] %s v%s berhasil dimuat.", SERVER_NAME, SERVER_VERSION);
    return 1;
}

// ============================================================================
//  GameMode Exit — Cleanup
// ============================================================================

public OnGameModeExit()
{
    NameValidator_Destroy();
    return 1;
}