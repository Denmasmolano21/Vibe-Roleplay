// core/config.pwn — Konstanta global server
// Pure defines, tidak ada #include di sini.

#if defined _CONFIG_PWN
    #endinput
#endif
#define _CONFIG_PWN

// ─── Database ─────────────────────────────────────────────────────────────────
#define DB_HOST             "localhost"
#define DB_USER             "root"
#define DB_PASS             ""
#define DB_NAME             "vrp"
#define DB_PORT             3306

// ─── Bcrypt ───────────────────────────────────────────────────────────────────
#define BCRYPT_WORK         (12)
#define HASH_LEN            (61)

// ─── Auth ─────────────────────────────────────────────────────────────────────
#define MAX_PASS_LEN        (32)
#define MIN_PASS_LEN        (6)
#define MAX_LOGIN_TRIES     (3)

// ─── Default spawn — Pershing Square, LS ─────────────────────────────────────
//     Z = 13.3663 — lantai beton, tidak jatuh
//     Hanya untuk player BARU. Player lama load last position.
#define SPAWN_X             (1499.8069)
#define SPAWN_Y             (-1640.7380)
#define SPAWN_Z             (13.3663)
#define SPAWN_A             (90.0)
#define SPAWN_INTERIOR      (0)
#define SPAWN_WORLD         (0)
#define SPAWN_SKIN          (23)
#define SPAWN_CASH          (50000)

// ─── Login camera — Flint County countryside ──────────────────────────────────
#define LOGIN_CAM_POS_X     (-213.9044)
#define LOGIN_CAM_POS_Y     (-113.0438)
#define LOGIN_CAM_POS_Z     (8.5000)
#define LOGIN_CAM_LOOK_X    (-185.0)
#define LOGIN_CAM_LOOK_Y    (-113.0438)
#define LOGIN_CAM_LOOK_Z    (4.0)
#define LOGIN_HIDE_Z        (-500.0)

// ─── Timer intervals (ms) ─────────────────────────────────────────────────────
#define INTERVAL_HUD        (1000)
#define INTERVAL_AC         (3000)
#define INTERVAL_SAVE       (300000)
#define INTERVAL_SURVIVAL   (60000)

// ─── Anti-cheat ───────────────────────────────────────────────────────────────
#define AC_MAX_PING         (500)
#define AC_MAX_HEALTH       (100.1)
#define AC_MAX_ARMOUR       (100.1)

// ─── Survival system ──────────────────────────────────────────────────────────
#define NEEDS_MAX           (100)
#define NEEDS_MIN           (0)
#define HUNGER_DECAY        (2)
#define THIRST_DECAY        (3)
#define NEEDS_WARN_LEVEL    (30)
#define NEEDS_CRIT_LEVEL    (10)
#define HUNGER_CRIT_DMG     (2.0)
#define THIRST_CRIT_DMG     (3.0)

// ─── Death system ─────────────────────────────────────────────────────────────
#define DEATH_RESPAWN_TIME  (30)    // detik tunggu sebelum bisa /respawn
#define SPAWN_PROT_TIME     (5000)  // ms spawn protection setelah respawn

// ─── Admin levels ─────────────────────────────────────────────────────────────
#define ADMIN_NONE          (0)
#define ADMIN_MOD           (1)     // Moderator  — kick, warn
#define ADMIN_ADMIN         (2)     // Admin      — ban, setlevel, goto
#define ADMIN_OWNER         (3)     // Owner      — semua akses

// ─── TextDraw constants ───────────────────────────────────────────────────────
#define TEXT_DRAW_FONT_0            (0)
#define TEXT_DRAW_FONT_1            (1)     // Big font
#define TEXT_DRAW_FONT_2            (2)     // Tall font
#define TEXT_DRAW_FONT_3            (3)     // Pricedown font
// TEXT_DRAW_FONT_SPRITE_DRAW sudah didefinisikan di a_samp.inc
#define TEXT_DRAW_ALIGN_LEFT        (0)
#define TEXT_DRAW_ALIGN_CENTER      (1)
#define TEXT_DRAW_ALIGN_RIGHT       (2)

// ─── Server info ──────────────────────────────────────────────────────────────
#define SERVER_NAME         "Vibe Roleplay"
#define SERVER_VERSION      "v1.0"
#define SERVER_DISCORD      "discord.gg/vibeRP"
