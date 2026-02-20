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
#define SERVER_VERSION          "1.0.0"
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
//  Default Spawn Position (Los Santos City Hall area)
// ============================================================================

#define DEFAULT_SPAWN_X         1481.0530
#define DEFAULT_SPAWN_Y         -1770.6168
#define DEFAULT_SPAWN_Z         18.7958
#define DEFAULT_SPAWN_A         0.0000
#define DEFAULT_SPAWN_INTERIOR  0
#define DEFAULT_SPAWN_VW        0
#define DEFAULT_SPAWN_SKIN      299
