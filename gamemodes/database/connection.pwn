/*
 * connection.pwn — MySQL handle + connect/disconnect
 * Depends on: config.pwn
 */

#if defined _DB_CONNECTION_PWN
    #endinput
#endif
#define _DB_CONNECTION_PWN

static MySQL:g_hSQL = MYSQL_INVALID_HANDLE;

// ─── Accessor ─────────────────────────────────────────────────────────────────
stock MySQL:DB_Handle() {
    return g_hSQL;
}

// ─── Connect ──────────────────────────────────────────────────────────────────
stock bool:DB_Connect() {
    new MySQLOpt:opt = mysql_init_options();
    mysql_set_option(opt, AUTO_RECONNECT,  true);
    mysql_set_option(opt, MULTI_STATEMENTS, false);
    mysql_set_option(opt, POOL_SIZE,        3);
    mysql_set_option(opt, SERVER_PORT,      DB_PORT);

    g_hSQL = mysql_connect(DB_HOST, DB_USER, DB_PASS, DB_NAME, opt);

    if (g_hSQL == MYSQL_INVALID_HANDLE || mysql_errno(g_hSQL) != 0) {
        printf("[DB] FATAL — connect failed: %s:%s@%s/%s",
            DB_USER, DB_PASS, DB_HOST, DB_NAME);
        return false;
    }

    mysql_set_charset("utf8mb4", g_hSQL);
    printf("[DB] Connected  host=%s  db=%s  pool=3", DB_HOST, DB_NAME);
    return true;
}

// ─── Disconnect ───────────────────────────────────────────────────────────────
stock DB_Disconnect() {
    if (g_hSQL != MYSQL_INVALID_HANDLE) {
        mysql_close(g_hSQL);
        g_hSQL = MYSQL_INVALID_HANDLE;
        print("[DB] Connection closed");
    }
}