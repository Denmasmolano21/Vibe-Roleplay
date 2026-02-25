/*
 *  Vibe Roleplay - Server Configuration
 *  File: config/server_config.inc
 *
 *  Konfigurasi utama server: MySQL, spawn, dan setting global.
 */

#if defined _server_config_included
    #endinput
#endif
#define _server_config_included

// ============================================================================
//  Server Info
// ============================================================================

#define SERVER_NAME             "Vibe Roleplay"
#define SERVER_VERSION          "1.0.2"
#define SERVER_WEBSITE          "www.vrp.com"
#define SERVER_DISCORD          "discord.gg/vrp"

// ============================================================================
//  MySQL Configuration
// ============================================================================

#define MYSQL_HOST              "127.0.0.1"
#define MYSQL_USER              "root"
#define MYSQL_PASS              ""
#define MYSQL_DB                "vrp"

// ============================================================================
//  Auth Settings
// ============================================================================

#define MAX_LOGIN_ATTEMPTS      3
#define MIN_PASSWORD_LENGTH     6
#define MAX_PASSWORD_LENGTH     30

// ============================================================================
//  Player Stats Defaults
// ============================================================================

#define DEFAULT_HUNGER          100
#define DEFAULT_THIRST          100
#define MAX_HUNGER              100
#define MAX_THIRST              100

// ============================================================================
//  Timer Intervals (dalam milidetik)
// ============================================================================

#define AUTOSAVE_INTERVAL       300000      // 5 menit
#define STATS_DECAY_INTERVAL    60000       // 1 menit
#define STATS_HUD_INTERVAL      5000        // 5 detik (update HUD)

// ============================================================================
//  Stats Decay Rates (per interval)
// ============================================================================

#define HUNGER_DECAY_RATE       2           // -2 per menit
#define THIRST_DECAY_RATE       3           // -3 per menit
#define STATS_HP_DRAIN          5.0         // HP drain saat hunger/thirst = 0

// ============================================================================
//  Death & Hospital Settings
// ============================================================================

#define DEATH_WAIT_TIME         15          // detik menunggu sebelum respawn
#define HOSPITAL_COST           500         // biaya rumah sakit

// Hospital spawn (All Saints General Hospital, LS)
#define HOSPITAL_SPAWN_X        2034.3547
#define HOSPITAL_SPAWN_Y        -1404.8188
#define HOSPITAL_SPAWN_Z        17.2500
#define HOSPITAL_SPAWN_A        135.0000
#define HOSPITAL_SPAWN_INT      0
#define HOSPITAL_SPAWN_VW       0

// ============================================================================
//  Default Spawn Position (Los Santos City Hall area)
// ============================================================================

#define DEFAULT_SPAWN_X         1481.0530
#define DEFAULT_SPAWN_Y         -1770.6168
#define DEFAULT_SPAWN_Z         18.7958
#define DEFAULT_SPAWN_A         0.0000
#define DEFAULT_SPAWN_INTERIOR  0
#define DEFAULT_SPAWN_VW        0
#define DEFAULT_SPAWN_SKIN      299
