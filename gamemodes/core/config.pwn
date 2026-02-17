// config.pwn — Konstanta global server
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

// ─── Default spawn — Pershing Square, LS (lantai beton datar, Z=13.36) ────────
//     Koordinat ini adalah area datar di depan gedung Pershing Square
//     Z = 13.3663 — dijamin tidak jatuh
#define SPAWN_X             (1499.8069)
#define SPAWN_Y             (-1640.7380)
#define SPAWN_Z             (13.3663)
#define SPAWN_A             (90.0)
#define SPAWN_INTERIOR      (0)
#define SPAWN_WORLD         (0)
#define SPAWN_SKIN          (23)
#define SPAWN_CASH          (50000)

// ─── Login camera — Flint County countryside ──────────────────────────────────
//     Kamera di tepi bukit menghadap ladang hijau, tenang dan sinematik
#define LOGIN_CAM_POS_X     (-213.9044)
#define LOGIN_CAM_POS_Y     (-113.0438)
#define LOGIN_CAM_POS_Z     (8.5000)
#define LOGIN_CAM_LOOK_X    (-185.0)
#define LOGIN_CAM_LOOK_Y    (-113.0438)
#define LOGIN_CAM_LOOK_Z    (4.0)
// Player disembunyikan di bawah peta — tidak terlihat siapapun
#define LOGIN_HIDE_Z        (-500.0)

// ─── Timer intervals (ms) ─────────────────────────────────────────────────────
#define INTERVAL_HUD        (1000)
#define INTERVAL_AC         (3000)
#define INTERVAL_SAVE       (300000)

// ─── Anti-cheat ───────────────────────────────────────────────────────────────
#define AC_MAX_PING         (500)
#define AC_MAX_HEALTH       (100.1)
#define AC_MAX_ARMOUR       (100.1)

// ─── Chat proximity radius ────────────────────────────────────────────────────
#define CHAT_RADIUS_NORMAL  (20.0)
#define CHAT_RADIUS_SHOUT   (40.0)
#define CHAT_RADIUS_WHISPER (3.0)
#define CHAT_RADIUS_DO      (20.0)
#define CHAT_RADIUS_ME      (20.0)

// ─── Server info (untuk dialog) ───────────────────────────────────────────────
#define SERVER_NAME         "Vibe Roleplay"
#define SERVER_VERSION      "v1.0"
#define SERVER_DISCORD      "discord.gg/vibeRP"
