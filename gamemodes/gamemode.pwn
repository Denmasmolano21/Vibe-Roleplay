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
 */

#include <a_samp>

#include <a_mysql>
#include <sscanf2>
#include <streamer>
#include <Pawn.CMD>
#include <samp_bcrypt>
#include <crashdetect>
#include <textdraw-streamer>
#include <Pawn.Regex>

#define YSI_NO_HEAP_MALLOC
#include <YSI_Coding/y_hooks>
#include <YSI_Coding/y_timers>
#include <YSI_Data/y_iterate>

#include "config/server_config.inc"
#include "config/dialog_ids.inc"
#include "config/colors.inc"
#include "config/admin_levels.inc"

#include "utils/name_validator.inc"
#include "utils/messages.inc"
#include "utils/command_guard.inc"
#include "utils/admin_log.inc"
#include "utils/report_system.inc"
#include "utils/player_utils.inc"

#include "core/database.inc"
#include "core/player_data.inc"
#include "core/player_state.inc"

#include "modules/auth/auth.inc"
#include "modules/session/session.inc"
#include "modules/stats/stats.inc"
#include "modules/spawn/spawn.inc"
#include "modules/mapping/mapping.inc"
#include "modules/vehicle/vehicle_core.inc"
#include "modules/inventory/inventory.inc"
#include "modules/phone/phone.inc"
#include "modules/house/house.inc"
#include "modules/business/business.inc"
#include "modules/job/job.inc"
#include "modules/faction/faction.inc"
#include "modules/banking/banking.inc"
#include "modules/payday/payday.inc"

#include "utils/dialog_handler.inc"

#include "commands/cmd_general.inc"
#include "commands/cmd_admin.inc"
#include "commands/cmd_vehicle.inc"
#include "commands/cmd_inventory.inc"
#include "commands/cmd_phone.inc"
#include "commands/cmd_house.inc"
#include "commands/cmd_business.inc"
#include "commands/cmd_job.inc"
#include "commands/cmd_faction.inc"
#include "commands/cmd_banking.inc"
#include "commands/cmd_payday.inc"

main()
{
    print("==============================================");
    print("  Vibe Roleplay - Gamemode Loaded");
    print("  Version: " SERVER_VERSION);
    print("  Author: Denmasmolano");
    print("==============================================");
}

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

public OnGameModeExit()
{
    NameValidator_Destroy();
    return 1;
}