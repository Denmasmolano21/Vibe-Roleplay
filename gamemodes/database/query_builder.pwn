// database/query_builder.pwn — Semua SQL query + dialog launchers
// Depends on: connection.pwn, player/data.pwn, core/config.pwn

#if defined _QUERY_BUILDER_PWN
    #endinput
#endif
#define _QUERY_BUILDER_PWN

// =============================================================================
// DIALOG LAUNCHERS
// =============================================================================

stock Dialog_ShowLogin(playerid, bool:password_wrong = false, remaining = 0) {
    new info[512], name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name, sizeof(name));

    if (password_wrong) {
        format(info, sizeof(info), \
            "{FF6B6B}Password salah! {888888}(%d percobaan tersisa)\n" \
            "\n" \
            "{CCCCCC}Selamat datang kembali,\n" \
            "{00C8FF}%s{CCCCCC}.\n" \
            "\n" \
            "{FFFFFF}Masukkan password Anda:", \
            remaining, name);
    } else {
        format(info, sizeof(info), \
            "{CCCCCC}Selamat datang kembali,\n" \
            "{00C8FF}%s{CCCCCC}.\n" \
            "\n" \
            "{FFFFFF}Masukkan password Anda:", \
            name);
    }

    ShowPlayerDialog(playerid, DIALOG_LOGIN,
        DIALOG_STYLE_PASSWORD,
        "{FFFFFF}Vibe Roleplay  {888888}|  {00C8FF}Masuk",
        info, "Masuk", "Keluar");
}

stock Dialog_ShowRegister(playerid, const pass_error[] = "") {
    new info[512], name[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, name, sizeof(name));

    if (strlen(pass_error) > 0) {
        format(info, sizeof(info), \
            "%s\n" \
            "\n" \
            "{CCCCCC}Halo, {00C8FF}%s{CCCCCC}!\n" \
            "{888888}Akun belum terdaftar. Buat password:\n" \
            "\n" \
            "{FFFFFF}Password baru Anda:", \
            pass_error, name);
    } else {
        format(info, sizeof(info), \
            "{CCCCCC}Halo, {00C8FF}%s{CCCCCC}!\n" \
            "{888888}Akun belum terdaftar. Buat password:\n" \
            "\n" \
            "{888888}%d-%d karakter  huruf, angka, !@#$%%_-.\n" \
            "\n" \
            "{FFFFFF}Password baru Anda:",
            name, MIN_PASS_LEN, MAX_PASS_LEN);
    }

    ShowPlayerDialog(playerid, DIALOG_REGISTER,
        DIALOG_STYLE_PASSWORD,
        "{FFFFFF}Vibe Roleplay  {888888}|  {44FF88}Daftar",
        info, "Daftar", "Keluar");
}

stock Dialog_ShowConfirm(playerid, bool:not_match = false) {
    new info[256];
    if (not_match) {
        format(info, sizeof(info), \
            "{FF6B6B}Password tidak cocok!\n" \
            "\n" \
            "{CCCCCC}Ulangi password Anda\n" \
            "{888888}untuk konfirmasi");
    } else {
        format(info, sizeof(info), \
            "{CCCCCC}Konfirmasi Password\n" \
            "\n" \
            "{888888}Ketik ulang password Anda\n" \
            "{888888}untuk memastikan kebenaran:");
    }
    ShowPlayerDialog(playerid, DIALOG_REGISTER_CONFIRM,
        DIALOG_STYLE_PASSWORD,
        "{FFFFFF}Vibe Roleplay  {888888}|  {44FF88}Konfirmasi",
        info, "Konfirmasi", "Kembali");
}

// =============================================================================
// SQL QUERIES
// =============================================================================

stock DB_CheckAccount(playerid) {
    new q[256];
    mysql_format(DB_Handle(), q, sizeof(q), \
        "SELECT `id`,`password`,`banned`,`ban_reason` " \
        "FROM `accounts` WHERE `username`='%e' LIMIT 1",
        g_Player[playerid][p_Name]);
    mysql_tquery(DB_Handle(), q, "OnDB_CheckAccount", "d", playerid);
}

stock DB_InsertAccount(playerid) {
    new q[512];
    mysql_format(DB_Handle(), q, sizeof(q), \
        "INSERT INTO `accounts` " \
        "(`username`,`password`,`level`,`money`,`bank`,`admin`,`banned`," \
        " `hunger`,`thirst`) " \
        "VALUES ('%e','%e',%d,%d,%d,%d,%d,%d,%d)",
        g_Player[playerid][p_Name],
        g_Player[playerid][p_Hash],
        g_Player[playerid][p_Level],
        g_Player[playerid][p_Money],
        g_Player[playerid][p_Bank],
        g_Player[playerid][p_Admin],
        _:g_Player[playerid][p_Banned],
        g_Player[playerid][p_Hunger],
        g_Player[playerid][p_Thirst]);
    mysql_tquery(DB_Handle(), q, "OnDB_InsertAccount", "d", playerid);
}

stock DB_LoadAccount(playerid) {
    new q[256];
    mysql_format(DB_Handle(), q, sizeof(q), \
        "SELECT `id`,`level`,`money`,`bank`,`admin`,`banned`,`ban_reason`," \
        "       `last_x`,`last_y`,`last_z`,`last_a`," \
        "       `last_interior`,`last_world`," \
        "       `hunger`,`thirst` " \
        "FROM `accounts` WHERE `username`='%e' LIMIT 1",
        g_Player[playerid][p_Name]);
    mysql_tquery(DB_Handle(), q, "OnDB_LoadAccount", "d", playerid);
}

stock DB_SaveAccount(playerid) {
    if (!g_Player[playerid][p_LoggedIn]) return;

    Player_SavePosition(playerid);

    new q[512];
    mysql_format(DB_Handle(), q, sizeof(q), \
        "UPDATE `accounts` SET " \
        "`level`=%d, `money`=%d, `bank`=%d, `admin`=%d," \
        "`last_x`=%.4f, `last_y`=%.4f, `last_z`=%.4f, `last_a`=%.4f," \
        "`last_interior`=%d, `last_world`=%d," \
        "`hunger`=%d, `thirst`=%d," \
        "`last_login`=NOW() " \
        "WHERE `id`=%d LIMIT 1",
        g_Player[playerid][p_Level],
        g_Player[playerid][p_Money],
        g_Player[playerid][p_Bank],
        g_Player[playerid][p_Admin],
        g_Player[playerid][p_LastX],
        g_Player[playerid][p_LastY],
        g_Player[playerid][p_LastZ],
        g_Player[playerid][p_LastA],
        g_Player[playerid][p_LastInterior],
        g_Player[playerid][p_LastWorld],
        g_Player[playerid][p_Hunger],
        g_Player[playerid][p_Thirst],
        g_Player[playerid][p_DbId]);
    mysql_tquery(DB_Handle(), q);
}

stock DB_BanPlayer(targetid, adminid) {
    new q[512];
    mysql_format(DB_Handle(), q, sizeof(q),
        "UPDATE `accounts` SET `banned`=1, `ban_reason`='%e' WHERE `id`=%d LIMIT 1",
        g_Player[targetid][p_BanReason],
        g_Player[targetid][p_DbId]);
    mysql_tquery(DB_Handle(), q);

    new qlog[512];
    mysql_format(DB_Handle(), qlog, sizeof(qlog), \
        "INSERT INTO `ban_logs` (`username`,`admin`,`reason`) " \
        "VALUES ('%e','%e','%e')",
        g_Player[targetid][p_Name],
        g_Player[adminid][p_Name],
        g_Player[targetid][p_BanReason]);
    mysql_tquery(DB_Handle(), qlog);
}

stock DB_UnbanPlayer(const username[]) {
    new q[256];
    mysql_format(DB_Handle(), q, sizeof(q), \
        "UPDATE `accounts` SET `banned`=0, `ban_reason`=NULL " \
        "WHERE `username`='%e' LIMIT 1",
        username);
    mysql_tquery(DB_Handle(), q);
}

// =============================================================================
// CALLBACKS
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
        new reason[128];
        cache_get_value(0, "ban_reason", reason, sizeof(reason));
        new msg[192];
        format(msg, sizeof(msg), \
            "  {FF4444}[x] {FFFFFF}Akun Anda di-banned.\n" \
            "  {888888}Alasan: {FFFFFF}%s", reason);
        SendClientMessage(playerid, COL_RED, msg);
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

    cache_get_value_int  (0, "id",           g_Player[playerid][p_DbId]);
    cache_get_value_int  (0, "level",        g_Player[playerid][p_Level]);
    cache_get_value_int  (0, "money",        g_Player[playerid][p_Money]);
    cache_get_value_int  (0, "bank",         g_Player[playerid][p_Bank]);
    cache_get_value_int  (0, "admin",        g_Player[playerid][p_Admin]);

    new banned;
    cache_get_value_int  (0, "banned",       banned);
    g_Player[playerid][p_Banned] = bool:banned;

    // Last position — jika last_x NULL di DB, cache_get_value_float return 0.0
    // p_HasLastPos di-set berdasarkan apakah kolom tidak NULL
    new Float:lx;
    cache_get_value_float(0, "last_x", lx);
    if (lx != 0.0) {
        g_Player[playerid][p_HasLastPos]    = true;
        g_Player[playerid][p_LastX]         = lx;
        cache_get_value_float(0, "last_y",       g_Player[playerid][p_LastY]);
        cache_get_value_float(0, "last_z",       g_Player[playerid][p_LastZ]);
        cache_get_value_float(0, "last_a",       g_Player[playerid][p_LastA]);
        cache_get_value_int  (0, "last_interior",g_Player[playerid][p_LastInterior]);
        cache_get_value_int  (0, "last_world",   g_Player[playerid][p_LastWorld]);
    }

    cache_get_value_int  (0, "hunger",       g_Player[playerid][p_Hunger]);
    cache_get_value_int  (0, "thirst",       g_Player[playerid][p_Thirst]);

    Player_FinishLogin(playerid);
    printf("[Auth] Login  name=%s  dbid=%d  level=%d",
        g_Player[playerid][p_Name],
        g_Player[playerid][p_DbId],
        g_Player[playerid][p_Level]);
    return 1;
}
