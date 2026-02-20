/*
 *  Vibe Roleplay - Database Core
 *  File: core/database.inc
 *
 *  Koneksi MySQL dan pembuatan tabel.
 *  Menggunakan y_hooks supaya modular.
 */

#if defined _database_included
    #endinput
#endif
#define _database_included

// Handle koneksi MySQL global
new MySQL:g_MySQL = MYSQL_INVALID_HANDLE;

// ============================================================================
//  Database Functions
// ============================================================================

stock Database_Connect()
{
    mysql_log(ALL);

    g_MySQL = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB);

    if (g_MySQL == MYSQL_INVALID_HANDLE || mysql_errno(g_MySQL) != 0)
    {
        printf("[DATABASE] GAGAL terhubung ke MySQL! Server akan dimatikan.");
        SendRconCommand("exit");
        return 0;
    }

    printf("[DATABASE] Berhasil terhubung ke MySQL database '%s'.", MYSQL_DB);
    mysql_set_charset("utf8mb4", g_MySQL);
    return 1;
}

stock Database_CreateTables()
{
    mysql_tquery(g_MySQL, "\
        CREATE TABLE IF NOT EXISTS `players` (\
            `id`            INT(11)         NOT NULL AUTO_INCREMENT,\
            `username`      VARCHAR(24)     NOT NULL,\
            `password`      VARCHAR(61)     NOT NULL,\
            `skin`          INT(5)          NOT NULL DEFAULT '299',\
            `money`         INT(11)         NOT NULL DEFAULT '0',\
            `level`         INT(5)          NOT NULL DEFAULT '1',\
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
        printf("[DATABASE] Koneksi MySQL ditutup.");
    }
    return 1;
}

// ============================================================================
//  Hooks
// ============================================================================

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
