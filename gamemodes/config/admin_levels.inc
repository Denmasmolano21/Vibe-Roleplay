/*
 *  Vibe Roleplay - Admin Level Configuration
 *  File: config/admin_levels.inc
 */

#if defined _admin_levels_included
    #endinput
#endif
#define _admin_levels_included

// Admin Level Definitions
#define ADMIN_LEVEL_NONE        0
#define ADMIN_LEVEL_HELPER      1
#define ADMIN_LEVEL_MODERATOR   2
#define ADMIN_LEVEL_ADMIN       3
#define ADMIN_LEVEL_HEAD_ADMIN  4
#define ADMIN_LEVEL_MANAGER     5
#define ADMIN_LEVEL_DEVELOPER   6
#define ADMIN_LEVEL_OWNER       7

// Admin Level Names
stock GetAdminLevelName(level)
{
    new name[32];
    switch(level)
    {
        case ADMIN_LEVEL_NONE: name = "Player";
        case ADMIN_LEVEL_HELPER: name = "Helper";
        case ADMIN_LEVEL_MODERATOR: name = "Moderator";
        case ADMIN_LEVEL_ADMIN: name = "Admin";
        case ADMIN_LEVEL_HEAD_ADMIN: name = "Head Admin";
        case ADMIN_LEVEL_MANAGER: name = "Manager";
        case ADMIN_LEVEL_DEVELOPER: name = "Developer";
        case ADMIN_LEVEL_OWNER: name = "Owner";
        default: name = "Unknown";
    }
    return name;
}

// Admin Level Colors
stock GetAdminLevelColor(level)
{
    new color;
    switch(level)
    {
        case ADMIN_LEVEL_HELPER: color = 0x00FF00FF;      // Green
        case ADMIN_LEVEL_MODERATOR: color = 0x00D4FFFF;   // Light Blue
        case ADMIN_LEVEL_ADMIN: color = 0xFF6B00FF;       // Orange
        case ADMIN_LEVEL_HEAD_ADMIN: color = 0xFF0000FF;  // Red
        case ADMIN_LEVEL_MANAGER: color = 0xFF00FFFF;     // Magenta
        case ADMIN_LEVEL_DEVELOPER: color = 0xFFFF00FF;   // Yellow
        case ADMIN_LEVEL_OWNER: color = 0xFF0000FF;       // Red
        default: color = 0xFFFFFFFF;                      // White
    }
    return color;
}

/*
 *  ADMIN LEVEL PERMISSIONS
 *  
 *  Level 1 - Helper:
 *  - /a (admin chat)
 *  - /reports, /reply
 *  - /goto, /gethere
 *  - /freeze, /unfreeze
 *  - /slap, /warn
 *  - /kick (with reason)
 *  - /spec, /specoff
 *  
 *  Level 2 - Moderator:
 *  - All Level 1 commands
 *  - /jail, /unjail
 *  - /mute, /unmute
 *  - /ban (temporary, max 7 days)
 *  - /kick (without reason required)
 *  - /akill
 *  - /disarm
 *  
 *  Level 3 - Admin:
 *  - All Level 2 commands
 *  - /ban (permanent)
 *  - /setstat (limited)
 *  - /givemoney (max 100k)
 *  - /setskin
 *  - /sethealth, /setarmour
 *  - /veh (spawn vehicle)
 *  - /dv (delete vehicle)
 *  - /announce
 *  
 *  Level 4 - Head Admin:
 *  - All Level 3 commands
 *  - /setlevel (max level 10)
 *  - /givemoney (max 1M)
 *  - /setstat (full access)
 *  - /makeadmin (up to level 2)
 *  - /offlineban
 *  - /unban
 *  - /respawnallveh
 *  
 *  Level 5 - Manager:
 *  - All Level 4 commands
 *  - /makeadmin (up to level 3)
 *  - /setlevel (unlimited)
 *  - /givemoney (unlimited)
 *  - /createhouse
 *  - /createbusiness
 *  - /edithouse
 *  - /editbusiness
 *  
 *  Level 6 - Developer:
 *  - All Level 5 commands
 *  - /makeadmin (up to level 5)
 *  - /gmx (restart server)
 *  - /loadfs, /unloadfs
 *  - /reloadbans
 *  - /setweather, /settime
 *  - /createobject
 *  
 *  Level 7 - Owner:
 *  - All commands
 *  - /makeadmin (up to level 7)
 *  - /rcon
 *  - Full server control
 */
