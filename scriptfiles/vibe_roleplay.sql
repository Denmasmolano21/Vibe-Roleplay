-- ============================================================================
--  Vibe Roleplay - Database Setup
--  File: scriptfiles/vibe_roleplay.sql
--
--  Jalankan file ini di MySQL untuk membuat database dan tabel.
--  Atau biarkan gamemode yang membuat tabel secara otomatis.
-- ============================================================================

CREATE DATABASE IF NOT EXISTS `vibe_roleplay`
    CHARACTER SET utf8mb4
    COLLATE utf8mb4_general_ci;

USE `vibe_roleplay`;

CREATE TABLE IF NOT EXISTS `players` (
    `id`            INT(11)         NOT NULL AUTO_INCREMENT,
    `username`      VARCHAR(24)     NOT NULL,
    `password`      VARCHAR(61)     NOT NULL,
    `skin`          INT(5)          NOT NULL DEFAULT '299',
    `money`         INT(11)         NOT NULL DEFAULT '0',
    `level`         INT(5)          NOT NULL DEFAULT '1',
    `pos_x`         FLOAT           NOT NULL DEFAULT '1481.053',
    `pos_y`         FLOAT           NOT NULL DEFAULT '-1770.616',
    `pos_z`         FLOAT           NOT NULL DEFAULT '18.795',
    `pos_a`         FLOAT           NOT NULL DEFAULT '0.0',
    `interior`      INT(3)          NOT NULL DEFAULT '0',
    `virtual_world` INT(5)          NOT NULL DEFAULT '0',
    `created_at`    DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `last_login`    DATETIME        NULL DEFAULT NULL,
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
