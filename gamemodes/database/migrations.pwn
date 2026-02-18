// database/migrations.pwn — Schema database
// Aturan Pawn multiline string dalam argumen fungsi:
//   BENAR : setiap baris tutup " lalu buka " baru, TANPA // di antara string
//   SALAH : ada // komentar di antara dua string literal dalam satu argumen
// Depends on: database/connection.pwn

#if defined _MIGRATIONS_PWN
    #endinput
#endif
#define _MIGRATIONS_PWN

stock DB_RunMigrations() {
    mysql_tquery(DB_Handle(), \
        "CREATE TABLE IF NOT EXISTS `accounts` (" \
        "  `id`            INT          NOT NULL AUTO_INCREMENT," \
        "  `username`      VARCHAR(24)  NOT NULL UNIQUE," \
        "  `password`      VARCHAR(72)  NOT NULL," \
        "  `level`         INT          NOT NULL DEFAULT 1," \
        "  `money`         INT          NOT NULL DEFAULT 50000," \
        "  `bank`          INT          NOT NULL DEFAULT 0," \
        "  `admin`         TINYINT      NOT NULL DEFAULT 0," \
        "  `banned`        TINYINT      NOT NULL DEFAULT 0," \
        "  `ban_reason`    VARCHAR(128)     NULL DEFAULT NULL," \
        "  `last_x`        FLOAT            NULL DEFAULT NULL," \
        "  `last_y`        FLOAT            NULL DEFAULT NULL," \
        "  `last_z`        FLOAT            NULL DEFAULT NULL," \
        "  `last_a`        FLOAT            NULL DEFAULT NULL," \
        "  `last_interior` INT              NULL DEFAULT NULL," \
        "  `last_world`    INT              NULL DEFAULT NULL," \
        "  `hunger`        INT          NOT NULL DEFAULT 100," \
        "  `thirst`        INT          NOT NULL DEFAULT 100," \
        "  `last_login`    DATETIME         NULL DEFAULT NULL," \
        "  `created_at`    DATETIME     NOT NULL DEFAULT CURRENT_TIMESTAMP," \
        "  PRIMARY KEY (`id`)," \
        "  INDEX `idx_username` (`username`)" \
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;");

    mysql_tquery(DB_Handle(), \
        "CREATE TABLE IF NOT EXISTS `ban_logs` (" \
        "  `id`        INT          NOT NULL AUTO_INCREMENT," \
        "  `username`  VARCHAR(24)  NOT NULL," \
        "  `admin`     VARCHAR(24)  NOT NULL," \
        "  `reason`    VARCHAR(128) NOT NULL," \
        "  `banned_at` DATETIME     NOT NULL DEFAULT CURRENT_TIMESTAMP," \
        "  PRIMARY KEY (`id`)" \
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;");

    print("[DB] Migrations selesai.");
}
