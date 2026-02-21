-- ============================================================================
-- Vibe Roleplay — SQL Setup (Phase 2)
-- Database: vrp
-- ============================================================================

CREATE DATABASE IF NOT EXISTS `vrp` DEFAULT CHARACTER SET utf8mb4;
USE `vrp`;

CREATE TABLE IF NOT EXISTS `players` (
    `id`            INT(11)         NOT NULL AUTO_INCREMENT,
    `username`      VARCHAR(24)     NOT NULL,
    `password`      VARCHAR(61)     NOT NULL,
    `skin`          INT(5)          NOT NULL DEFAULT '299',
    `money`         INT(11)         NOT NULL DEFAULT '0',
    `level`         INT(5)          NOT NULL DEFAULT '1',
    `hunger`        INT(3)          NOT NULL DEFAULT '100',
    `thirst`        INT(3)          NOT NULL DEFAULT '100',
    `playtime`      INT(11)         NOT NULL DEFAULT '0',
    `pos_x`         FLOAT           NOT NULL DEFAULT '1481.053',
    `pos_y`         FLOAT           NOT NULL DEFAULT '-1770.616',
    `pos_z`         FLOAT           NOT NULL DEFAULT '18.795',
    `pos_a`         FLOAT           NOT NULL DEFAULT '0.0',
    `interior`      INT(3)          NOT NULL DEFAULT '0',
    `virtual_world` INT(5)          NOT NULL DEFAULT '0',
    `created_at`    DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `last_login`    DATETIME        NULL DEFAULT NULL,
    PRIMARY KEY (`id`),
    UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Jika upgrading dari Phase 1, tambahkan kolom baru:
-- ALTER TABLE `players` ADD COLUMN `hunger` INT(3) NOT NULL DEFAULT '100' AFTER `level`;
-- ALTER TABLE `players` ADD COLUMN `thirst` INT(3) NOT NULL DEFAULT '100' AFTER `hunger`;
-- ALTER TABLE `players` ADD COLUMN `playtime` INT(11) NOT NULL DEFAULT '0' AFTER `thirst`;
