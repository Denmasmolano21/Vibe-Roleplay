/*
 *  Vibe Roleplay - Database Core
 *  File: core/database.inc
 */

#if defined _database_included
    #endinput
#endif
#define _database_included

#include <YSI_Coding/y_hooks>
#include <YSI_Coding/y_timers>
#include <YSI_Data/y_iterate>

new MySQL:g_MySQL = MYSQL_INVALID_HANDLE;
new bool:g_DatabaseConnected = false;

stock Database_Connect()
{
    mysql_log(ALL);
    g_MySQL = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB);

    if (g_MySQL == MYSQL_INVALID_HANDLE || mysql_errno(g_MySQL) != 0)
    {
        printf("[DATABASE] GAGAL terhubung ke MySQL! Error: %d", mysql_errno(g_MySQL));
        g_DatabaseConnected = false;
        SendRconCommand("exit");
        return 0;
    }

    printf("[DATABASE] Berhasil terhubung ke MySQL database '%s'.", MYSQL_DB);
    mysql_set_charset("utf8mb4", g_MySQL);
    g_DatabaseConnected = true;
    return 1;
}

stock Database_CreateTables()
{
    if (!g_DatabaseConnected || g_MySQL == MYSQL_INVALID_HANDLE)
    {
        printf("[DATABASE] ERROR: Tidak bisa membuat tabel, koneksi belum tersedia.");
        return 0;
    }

    mysql_tquery(g_MySQL, "\
        CREATE TABLE IF NOT EXISTS `players` (\
            `id`            INT(11)         NOT NULL AUTO_INCREMENT,\
            `username`      VARCHAR(24)     NOT NULL,\
            `password`      VARCHAR(65)     NOT NULL,\
            `admin_level`   INT(2)          NOT NULL DEFAULT '0',\
            `skin`          INT(5)          NOT NULL DEFAULT '299',\
            `money`         INT(11)         NOT NULL DEFAULT '0',\
            `bank_money`    INT(11)         NOT NULL DEFAULT '5000',\
            `level`         INT(5)          NOT NULL DEFAULT '1',\
            `hunger`        INT(3)          NOT NULL DEFAULT '100',\
            `thirst`        INT(3)          NOT NULL DEFAULT '100',\
            `playtime`      INT(11)         NOT NULL DEFAULT '0',\
            `pos_x`         FLOAT           NOT NULL DEFAULT '1481.053',\
            `pos_y`         FLOAT           NOT NULL DEFAULT '-1770.616',\
            `pos_z`         FLOAT           NOT NULL DEFAULT '18.795',\
            `pos_a`         FLOAT           NOT NULL DEFAULT '0.0',\
            `interior`      INT(3)          NOT NULL DEFAULT '0',\
            `virtual_world` INT(5)          NOT NULL DEFAULT '0',\
            `created_at`    DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP,\
            `last_login`    DATETIME        NULL DEFAULT NULL,\
            PRIMARY KEY (`id`),\
            UNIQUE KEY `username` (`username`)\
        ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;\
    ");

    printf("[DATABASE] Tabel 'players' siap.");
    return 1;
}

stock Database_Close()
{
    if (g_MySQL != MYSQL_INVALID_HANDLE)
    {
        mysql_close(g_MySQL);
        g_MySQL = MYSQL_INVALID_HANDLE;
        g_DatabaseConnected = false;
        printf("[DATABASE] Koneksi MySQL ditutup.");
    }
    return 1;
}

hook OnGameModeInit()
{
    Database_Connect();
    Database_CreateTables();
    return 1;
}

hook OnGameModeExit()
{
    Database_Close();
    return 1;
}
