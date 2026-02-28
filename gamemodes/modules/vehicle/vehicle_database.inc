/*
 *  Vibe Roleplay - Vehicle Database
 *  File: modules/vehicle/vehicle_database.inc
 */

#if defined _vehicle_database_included
    #endinput
#endif
#define _vehicle_database_included

stock Vehicle_CreateTable()
{
    mysql_tquery(g_MySQL, "\
        CREATE TABLE IF NOT EXISTS `vehicles` (\
            `id`            INT(11)         NOT NULL AUTO_INCREMENT,\
            `model`         INT(5)          NOT NULL,\
            `owner_id`      INT(11)         NOT NULL DEFAULT '0',\
            `owner_name`    VARCHAR(24)     NULL DEFAULT NULL,\
            `spawn_x`       FLOAT           NOT NULL,\
            `spawn_y`       FLOAT           NOT NULL,\
            `spawn_z`       FLOAT           NOT NULL,\
            `spawn_a`       FLOAT           NOT NULL,\
            `color1`        INT(5)          NOT NULL DEFAULT '0',\
            `color2`        INT(5)          NOT NULL DEFAULT '0',\
            `fuel`          FLOAT           NOT NULL DEFAULT '100.0',\
            `locked`        INT(1)          NOT NULL DEFAULT '0',\
            `health`        FLOAT           NOT NULL DEFAULT '1000.0',\
            `mileage`       FLOAT           NOT NULL DEFAULT '0.0',\
            `plate`         VARCHAR(32)     NOT NULL DEFAULT 'VRP-0000',\
            `faction`       INT(5)          NOT NULL DEFAULT '0',\
            `job`           INT(5)          NOT NULL DEFAULT '0',\
            `price`         INT(11)         NOT NULL DEFAULT '0',\
            `created_at`    DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP,\
            PRIMARY KEY (`id`),\
            KEY `owner_id` (`owner_id`)\
        ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;\
    ");

    printf("[VEHICLE] Table 'vehicles' created/verified.");
    return 1;
}
