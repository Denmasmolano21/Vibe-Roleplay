// core/enums.pwn — Semua enum & warna global
// Pure defines + enum, tidak ada #include di sini.

#if defined _ENUMS_PWN
    #endinput
#endif
#define _ENUMS_PWN

// =============================================================================
// PLAYER DATA STRUCT
// =============================================================================
enum E_PLAYER {
    p_DbId,
    p_Name          [MAX_PLAYER_NAME + 1],
    p_Hash          [HASH_LEN + 1],

    bool:p_LoggedIn,
    p_Tries,

    p_Level,
    p_Money,
    p_Bank,
    p_Admin,
    bool:p_Banned,
    p_BanReason     [128],

    // Last position — p_HasLastPos false = player baru, spawn default
    bool:p_HasLastPos,
    Float:p_LastX,
    Float:p_LastY,
    Float:p_LastZ,
    Float:p_LastA,
    p_LastInterior,
    p_LastWorld,

    // Survival needs (0-100)
    p_Hunger,
    p_Thirst,

    // Death / spawn state
    bool:p_IsDead,
    bool:p_SpawnProt,   // true = sedang dalam spawn protection

    p_ConnectTime
};

// Note: p_TempPass TIDAK ada di struct.
// Disimpan di static array di dialog_router.pwn.

// =============================================================================
// DIALOG IDs
// =============================================================================
enum {
    DIALOG_UNUSED = 0,
    DIALOG_LOGIN,
    DIALOG_REGISTER,
    DIALOG_REGISTER_CONFIRM
};

// =============================================================================
// WARNA — hex RGBA untuk SendClientMessage
// =============================================================================
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
