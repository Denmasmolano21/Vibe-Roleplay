// query_builder.pwn — Semua SQL query + dialog launcher
// Depends on: connection.pwn, player/data.pwn, core/config.pwn

#if defined _QUERY_BUILDER_PWN
    #endinput
#endif
#define _QUERY_BUILDER_PWN

// =============================================================================
// DIALOG LAUNCHERS
// Dialog dirancang dengan prinsip SA-MP color embedding:
//   - Caption: judul dialog (satu baris)
//   - Info   : badan dialog (\n = baris baru, \t = tab)
//   - Color embedding: {RRGGBB} reset di setiap \n pada STYLE_PASSWORD
// =============================================================================

// ─── Dialog LOGIN ─────────────────────────────────────────────────────────────
//     password_wrong = true → tampilkan pesan salah + sisa percobaan
stock Dialog_ShowLogin(playerid, bool:password_wrong = false, remaining = 0) {
    new info[512], name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name, sizeof(name));

    if (password_wrong) {
        format(info, sizeof(info),
            "{FF6B6B}Password salah! {888888}(%d percobaan tersisa)\n"\
            "\n"\
            "{CCCCCC}Selamat datang kembali,\n"\
            "{00C8FF}%s{CCCCCC}.\n"\
            "\n"\
            "{FFFFFF}Masukkan password Anda:",
            remaining, name
        );
    } else {
        format(info, sizeof(info),
            "{CCCCCC}Selamat datang kembali,\n"\
            "{00C8FF}%s{CCCCCC}.\n"\
            "\n"\
            "{FFFFFF}Masukkan password Anda:",
            name
        );
    }

    ShowPlayerDialog(playerid, DIALOG_LOGIN,
        DIALOG_STYLE_PASSWORD,
        "{FFFFFF}Vibe Roleplay  {888888}|  {00C8FF}Masuk",
        info,
        "Masuk",
        "Keluar"
    );
}

// ─── Dialog REGISTER ─────────────────────────────────────────────────────────
//     pass_error = "" → dialog normal
//     pass_error = "pesan" → tampilkan error di atas form
stock Dialog_ShowRegister(playerid, const pass_error[] = "") {
    new info[512], name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name, sizeof(name));

    if (strlen(pass_error) > 0) {
        format(info, sizeof(info),
            "%s\n"\
            "\n"\
            "{CCCCCC}Halo, {00C8FF}%s{CCCCCC}!\n"\
            "{888888}Akun belum terdaftar. Buat password:\n"\
            "\n"\
            "{FFFFFF}Password baru Anda:",
            pass_error, name
        );
    } else {
        format(info, sizeof(info),
            "{CCCCCC}Halo, {00C8FF}%s{CCCCCC}!\n"\
            "{888888}Akun belum terdaftar. Buat password:\n"\
            "\n"\
            "{888888}%d-%d karakter  •  huruf, angka, !@#$%%_-.\n"\
            "\n"\
            "{FFFFFF}Password baru Anda:",
            name, MIN_PASS_LEN, MAX_PASS_LEN
        );
    }

    ShowPlayerDialog(playerid, DIALOG_REGISTER,
        DIALOG_STYLE_PASSWORD,
        "{FFFFFF}Vibe Roleplay  {888888}|  {44FF88}Daftar",
        info,
        "Daftar",
        "Keluar"
    );
}

// ─── Dialog KONFIRMASI PASSWORD ────────────────────────────────────────────────
//     not_match = true → tampilkan error tidak cocok
stock Dialog_ShowConfirm(playerid, bool:not_match = false) {
    new info[256];

    if (not_match) {
        format(info, sizeof(info),
            "{FF6B6B}Password tidak cocok!\n"\
            "\n"\
            "{CCCCCC}Ulangi password Anda\n"\
            "{888888}untuk konfirmasi:"
        );
    } else {
        format(info, sizeof(info),
            "{CCCCCC}Konfirmasi Password\n"\
            "\n"\
            "{888888}Ketik ulang password Anda\n"\
            "{888888}untuk memastikan kebenaran:"
        );
    }

    ShowPlayerDialog(playerid, DIALOG_REGISTER_CONFIRM,
        DIALOG_STYLE_PASSWORD,
        "{FFFFFF}Vibe Roleplay  {888888}|  {44FF88}Konfirmasi",
        info,
        "Konfirmasi",
        "Kembali"
    );
}

// =============================================================================
// SQL QUERIES
// =============================================================================

stock DB_CheckAccount(playerid) {
    new q[256];
    mysql_format(DB_Handle(), q, sizeof(q),
        "SELECT `id`,`password`,`banned` FROM `accounts` "\
        "WHERE `username`='%e' LIMIT 1",
        g_Player[playerid][p_Name]
    );
    mysql_tquery(DB_Handle(), q, "OnDB_CheckAccount", "d", playerid);
}

stock DB_InsertAccount(playerid) {
    new q[512];
    mysql_format(DB_Handle(), q, sizeof(q),
        "INSERT INTO `accounts` "\
        "(`username`,`password`,`level`,`money`,`bank`,`admin`,`banned`) "\
        "VALUES ('%e','%e',%d,%d,%d,%d,%d)",
        g_Player[playerid][p_Name],
        g_Player[playerid][p_Hash],
        g_Player[playerid][p_Level],
        g_Player[playerid][p_Money],
        g_Player[playerid][p_Bank],
        g_Player[playerid][p_Admin],
        _:g_Player[playerid][p_Banned]
    );
    mysql_tquery(DB_Handle(), q, "OnDB_InsertAccount", "d", playerid);
}

stock DB_LoadAccount(playerid) {
    new q[128];
    mysql_format(DB_Handle(), q, sizeof(q),
        "SELECT `id`,`level`,`money`,`bank`,`admin`,`banned` "\
        "FROM `accounts` WHERE `username`='%e' LIMIT 1",
        g_Player[playerid][p_Name]
    );
    mysql_tquery(DB_Handle(), q, "OnDB_LoadAccount", "d", playerid);
}

stock DB_SaveAccount(playerid) {
    if (!g_Player[playerid][p_LoggedIn]) return;
    new q[512];
    mysql_format(DB_Handle(), q, sizeof(q),
        "UPDATE `accounts` SET `level`=%d,`money`=%d,`bank`=%d,"\
        "`admin`=%d,`last_login`=NOW() WHERE `id`=%d LIMIT 1",
        g_Player[playerid][p_Level],
        g_Player[playerid][p_Money],
        g_Player[playerid][p_Bank],
        g_Player[playerid][p_Admin],
        g_Player[playerid][p_DbId]
    );
    mysql_tquery(DB_Handle(), q);
}

// =============================================================================
// QUERY CALLBACKS
// =============================================================================

forward OnDB_CheckAccount(playerid);
public  OnDB_CheckAccount(playerid) {
    if (!IsPlayerConnected(playerid)) return 1;

    if (cache_num_rows() == 0) {
        Dialog_ShowRegister(playerid);
        return 1;
    }

    new banned;
    cache_get_value_int(0, "banned", banned);
    if (banned) {
        SendClientMessage(playerid, COL_RED,
            "  {FF4444}[✗] {FFFFFF}Akun Anda di-banned dari server ini.");
        Player_Kick(playerid);
        return 1;
    }

    cache_get_value_int(0, "id",       g_Player[playerid][p_DbId]);
    cache_get_value    (0, "password", g_Player[playerid][p_Hash], HASH_LEN + 1);
    Dialog_ShowLogin(playerid);
    return 1;
}

forward OnDB_InsertAccount(playerid);
public  OnDB_InsertAccount(playerid) {
    if (!IsPlayerConnected(playerid)) return 1;
    g_Player[playerid][p_DbId] = cache_insert_id();
    Player_FinishLogin(playerid);
    printf("[Auth] Registered  name=%s  dbid=%d",
        g_Player[playerid][p_Name], g_Player[playerid][p_DbId]);
    return 1;
}

forward OnDB_LoadAccount(playerid);
public  OnDB_LoadAccount(playerid) {
    if (!IsPlayerConnected(playerid)) return 1;
    if (cache_num_rows() == 0) return 1;

    cache_get_value_int(0, "id",    g_Player[playerid][p_DbId]);
    cache_get_value_int(0, "level", g_Player[playerid][p_Level]);
    cache_get_value_int(0, "money", g_Player[playerid][p_Money]);
    cache_get_value_int(0, "bank",  g_Player[playerid][p_Bank]);
    cache_get_value_int(0, "admin", g_Player[playerid][p_Admin]);

    new banned;
    cache_get_value_int(0, "banned", banned);
    g_Player[playerid][p_Banned] = bool:banned;

    Player_FinishLogin(playerid);
    printf("[Auth] Login  name=%s  dbid=%d  level=%d",
        g_Player[playerid][p_Name],
        g_Player[playerid][p_DbId],
        g_Player[playerid][p_Level]
    );
    return 1;
}
