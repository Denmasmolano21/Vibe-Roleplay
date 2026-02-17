/*
 * migrations.pwn — CREATE TABLE IF NOT EXISTS
 * Depends on: connection.pwn
 */

#if defined _DB_MIGRATIONS_PWN
    #endinput
#endif
#define _DB_MIGRATIONS_PWN

forward OnMigrationDone(table[]);
public  OnMigrationDone(table[]) {
    printf("[DB] Table ready: %s", table);
}

stock DB_RunMigrations() {
    // accounts
    mysql_tquery(DB_Handle(),
        "CREATE TABLE IF NOT EXISTS `accounts` ("\
        "  `id`         INT UNSIGNED     NOT NULL AUTO_INCREMENT,"\
        "  `username`   VARCHAR(24)      NOT NULL,"\
        "  `password`   VARCHAR(64)      NOT NULL,"\
        "  `level`      TINYINT UNSIGNED NOT NULL DEFAULT 1,"\
        "  `money`      INT              NOT NULL DEFAULT 50000,"\
        "  `bank`       INT              NOT NULL DEFAULT 0,"\
        "  `admin`      TINYINT UNSIGNED NOT NULL DEFAULT 0,"\
        "  `banned`     TINYINT(1)       NOT NULL DEFAULT 0,"\
        "  `last_login` DATETIME,"\
        "  `created_at` DATETIME         NOT NULL DEFAULT CURRENT_TIMESTAMP,"\
        "  PRIMARY KEY (`id`),"\
        "  UNIQUE KEY `uq_username` (`username`)"\
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4",
        "OnMigrationDone", "s", "accounts"
    );
}