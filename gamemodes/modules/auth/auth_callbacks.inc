/*
 *  Vibe Roleplay - Auth Callbacks
 *  File: modules/auth/auth_callbacks.inc
 *
 *  Semua callback async dari MySQL dan bcrypt untuk sistem auth.
 *  Dipisahkan dari auth.inc supaya clean.
 */

#if defined _auth_callbacks_included
    #endinput
#endif
#define _auth_callbacks_included

// ============================================================================
//  MySQL Callback: Cek apakah pemain sudah terdaftar
// ============================================================================

forward OnPlayerDataCheck(playerid);
public OnPlayerDataCheck(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    new rows = cache_num_rows();

    if (rows > 0)
    {
        // Akun ditemukan — ambil password hash dan ID
        cache_get_value_name_int(0, "id", PlayerData[playerid][pID]);
        cache_get_value_name(0, "password", PlayerData[playerid][pPassword], BCRYPT_HASH_LENGTH);

        // Tampilkan dialog login
        ShowLoginDialog(playerid);
    }
    else
    {
        // Akun belum ada — tampilkan dialog register
        ShowRegisterDialog(playerid);
    }
    return 1;
}

// ============================================================================
//  bcrypt Callback: Setelah password di-hash (registrasi)
// ============================================================================

forward OnPasswordHash(playerid, hashid);
public OnPasswordHash(playerid, hashid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    new hash[BCRYPT_HASH_LENGTH];
    bcrypt_get_hash(hash);

    // Simpan hash ke memory
    format(PlayerData[playerid][pPassword], BCRYPT_HASH_LENGTH, "%s", hash);

    // Insert ke database
    new query[512], name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    mysql_format(g_MySQL, query, sizeof(query),
        "INSERT INTO `players` (`username`, `password`) VALUES ('%e', '%e')",
        name, hash
    );
    mysql_tquery(g_MySQL, query, "OnPlayerRegisterInsert", "i", playerid);
    return 1;
}

// ============================================================================
//  MySQL Callback: Setelah INSERT registrasi
// ============================================================================

forward OnPlayerRegisterInsert(playerid);
public OnPlayerRegisterInsert(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    PlayerData[playerid][pID] = cache_insert_id();
    PlayerData[playerid][pLoggedIn] = true;
    PlayerData[playerid][pRegistering] = false;
    PlayerData[playerid][pTempPassword][0] = EOS;

    // Update last_login
    new query[256];
    mysql_format(g_MySQL, query, sizeof(query),
        "UPDATE `players` SET `last_login` = NOW() WHERE `id` = %d",
        PlayerData[playerid][pID]
    );
    mysql_tquery(g_MySQL, query);

    SendSuccessMessage(playerid, "Registrasi berhasil! Selamat datang di Vibe Roleplay.");
    SendInfoMessage(playerid, "Gunakan voice chat untuk berkomunikasi.");

    // Spawn pemain
    SpawnPlayerAtSavedPosition(playerid);
    return 1;
}

// ============================================================================
//  bcrypt Callback: Setelah verifikasi password (login)
// ============================================================================

forward OnPasswordVerify(playerid, bool:success);
public OnPasswordVerify(playerid, bool:success)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (success)
    {
        // Password benar — load data pemain
        new query[256], name[MAX_PLAYER_NAME];
        GetPlayerName(playerid, name, sizeof(name));

        mysql_format(g_MySQL, query, sizeof(query),
            "SELECT * FROM `players` WHERE `username` = '%e' LIMIT 1",
            name
        );
        mysql_tquery(g_MySQL, query, "OnPlayerDataLoad", "i", playerid);
    }
    else
    {
        // Password salah
        PlayerData[playerid][pLoginAttempts]++;

        new remaining = MAX_LOGIN_ATTEMPTS - PlayerData[playerid][pLoginAttempts];

        if (remaining <= 0)
        {
            SendErrorMessage(playerid, "Terlalu banyak percobaan login. Kamu akan di-kick.");
            SetTimerEx("KickPlayerDelay", 500, false, "i", playerid);
            return 1;
        }

        new msg[128];
        format(msg, sizeof(msg), "Password salah! Sisa percobaan: %d/%d", remaining, MAX_LOGIN_ATTEMPTS);
        SendErrorMessage(playerid, msg);

        ShowLoginDialog(playerid);
    }
    return 1;
}

// ============================================================================
//  MySQL Callback: Load player data setelah login berhasil
// ============================================================================

forward OnPlayerDataLoad(playerid);
public OnPlayerDataLoad(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (cache_num_rows() == 0)
        return 0;

    // Load semua data dari database
    cache_get_value_name_int(0, "id", PlayerData[playerid][pID]);
    cache_get_value_name_int(0, "skin", PlayerData[playerid][pSkin]);
    cache_get_value_name_int(0, "money", PlayerData[playerid][pMoney]);
    cache_get_value_name_int(0, "level", PlayerData[playerid][pLevel]);
    cache_get_value_name_float(0, "pos_x", PlayerData[playerid][pPosX]);
    cache_get_value_name_float(0, "pos_y", PlayerData[playerid][pPosY]);
    cache_get_value_name_float(0, "pos_z", PlayerData[playerid][pPosZ]);
    cache_get_value_name_float(0, "pos_a", PlayerData[playerid][pPosA]);
    cache_get_value_name_int(0, "interior", PlayerData[playerid][pInterior]);
    cache_get_value_name_int(0, "virtual_world", PlayerData[playerid][pVirtualWorld]);

    PlayerData[playerid][pLoggedIn] = true;

    // Update last_login
    new query[256];
    mysql_format(g_MySQL, query, sizeof(query),
        "UPDATE `players` SET `last_login` = NOW() WHERE `id` = %d",
        PlayerData[playerid][pID]
    );
    mysql_tquery(g_MySQL, query);

    SendSuccessMessage(playerid, "Login berhasil! Selamat datang kembali.");

    // Spawn pemain
    SpawnPlayerAtSavedPosition(playerid);
    return 1;
}

// ============================================================================
//  MySQL Callback: Simpan data pemain (disconnect)
// ============================================================================

forward OnPlayerDataSave(playerid);
public OnPlayerDataSave(playerid)
{
    // Callback opsional — untuk logging jika diperlukan
    return 1;
}

// ============================================================================
//  Utility: Delayed kick (agar pesan error sempat terkirim)
// ============================================================================

forward KickPlayerDelay(playerid);
public KickPlayerDelay(playerid)
{
    Kick(playerid);
    return 1;
}
