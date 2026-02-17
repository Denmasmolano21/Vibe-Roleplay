// enums.pwn — Semua enum & warna global

#if defined _ENUMS_PWN
    #endinput
#endif
#define _ENUMS_PWN

// ─── Player data ──────────────────────────────────────────────────────────────
enum E_PLAYER {
    p_DbId,
    p_Name      [MAX_PLAYER_NAME + 1],
    p_Hash      [HASH_LEN + 1],
    p_TempPass  [MAX_PASS_LEN + 1],   // Sementara: konfirmasi register

    bool:p_LoggedIn,
    p_Tries,

    p_Level,
    p_Money,
    p_Bank,
    p_Admin,
    bool:p_Banned,

    p_ConnectTime,
    p_Hunger,
    p_Thirst
};

// ─── Dialog IDs ───────────────────────────────────────────────────────────────
enum {
    DIALOG_UNUSED = 0,
    DIALOG_LOGIN,
    DIALOG_REGISTER,
    DIALOG_REGISTER_CONFIRM     // Step 2: ulangi password
};

// ─── Warna pesan (hex RGBA, untuk SendClientMessage) ─────────────────────────
#define COL_WHITE           (0xFFFFFFFF)
#define COL_RED             (0xFF4444FF)
#define COL_GREEN           (0x44FF44FF)
#define COL_YELLOW          (0xFFFF44FF)
#define COL_ORANGE          (0xFF8800FF)
#define COL_GREY            (0xAAAAAAFF)
#define COL_LIGHTBLUE       (0x00C8FFFF)
#define COL_PURPLE          (0xC2A2DAFF)
#define COL_PINK            (0xFF69B4FF)
#define COL_DARKGREY        (0x666666FF)
