/*
 *  ██╗   ██╗██╗██████╗ ███████╗    ██████╗ ██████╗ 
 *  ██║   ██║██║██╔══██╗██╔════╝    ██╔══██╗██╔══██╗
 *  ██║   ██║██║██████╔╝█████╗      ██████╔╝██████╔╝
 *  ╚██╗ ██╔╝██║██╔══██╗██╔══╝      ██╔══██╗██╔═══╝ 
 *   ╚████╔╝ ██║██████╔╝███████╗    ██║  ██║██║     
 *    ╚═══╝  ╚═╝╚═════╝ ╚══════╝    ╚═╝  ╚═╝╚═╝     
 *
 *  Vibe Roleplay — SA-MP 0.3.7 ( Gamemode )
 *  Version: 1.0.3
 *  Author: Denmasmolano
 *
 *  Changelog:
 *  - v1.0.3: Simplified code - use direct variables instead of wrapper functions
 *  - v1.0.2: Fixed include order, improved code quality
 *  - v1.0.1: Initial release with auth system
 *  - v1.0.0: Base gamemode
 */

// ============================================================================
//  SA-MP Native Includes (Harus pertama)
// ============================================================================

#include <a_samp>

// ============================================================================
//  Plugin Includes
// ============================================================================

#include <a_mysql>
#include <sscanf2>
#include <streamer>
#include <Pawn.CMD>
#include <samp_bcrypt>
#include <crashdetect>
#include <textdraw-streamer>
#include <Pawn.Regex>

// ============================================================================
//  YSI Libraries
// ============================================================================

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
#include "utils\command_guard.inc"

// ============================================================================
//  Core
// ============================================================================

#include "core\database.inc"
#include "core\player_data.inc"
#include "core\player_state.inc"

// ============================================================================
//  Modules
// ============================================================================

#include "modules\auth\auth.inc"
#include "modules\session\session.inc"
#include "modules\stats\stats.inc"
#include "modules\spawn\spawn.inc"

// ============================================================================
//  Commands
// ============================================================================

#include "commands\cmd_general.inc"

// ============================================================================
//  Entry Point
// ============================================================================

main()
{
    print("==============================================");
    print("  Vibe Roleplay - Gamemode Loaded");
    print("  Version: " SERVER_VERSION);
    print("  Author: Denmasmolano");
    print("==============================================");
}

// ============================================================================
//  GameMode Init
// ============================================================================

public OnGameModeInit()
{
    NameValidator_Init();

    SetGameModeText("VRP v" SERVER_VERSION);
    ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
    ShowNameTags(1);
    SetNameTagDrawDistance(30.0);
    EnableStuntBonusForAll(0);
    DisableInteriorEnterExits();
    ManualVehicleEngineAndLights();
    UsePlayerPedAnims();

    AddPlayerClass(0, DEFAULT_SPAWN_X, DEFAULT_SPAWN_Y, DEFAULT_SPAWN_Z,
        DEFAULT_SPAWN_A, 0, 0, 0, 0, 0, 0);

    printf("[GAMEMODE] %s v%s berhasil dimuat.", SERVER_NAME, SERVER_VERSION);
    return 1;
}

// ============================================================================
//  GameMode Exit
// ============================================================================

public OnGameModeExit()
{
    NameValidator_Destroy();
    return 1;
}