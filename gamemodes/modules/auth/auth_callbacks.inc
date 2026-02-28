/*
 *  Vibe Roleplay - Auth Callbacks
 *  File: modules/auth/auth_callbacks.inc
 */

#if defined _auth_callbacks_included
    #endinput
#endif
#define _auth_callbacks_included

forward OnPlayerDataCheck(playerid);
public OnPlayerDataCheck(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    new rows = cache_num_rows();

    if (rows > 0)
    {
        cache_get_value_name_int(0, "id", PlayerData[playerid][pID]);
        cache_get_value_name(0, "password", PlayerData[playerid][pPassword], MAX_PLAYER_PASSWORD);
        ShowLoginDialog(playerid);
    }
    else
    {
        ShowRegisterDialog(playerid);
    }
    return 1;
}

forward OnPasswordHash(playerid, hashid);
public OnPasswordHash(playerid, hashid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    new hash[BCRYPT_HASH_LENGTH];
    bcrypt_get_hash(hash);
    format(PlayerData[playerid][pPassword], MAX_PLAYER_PASSWORD, "%s", hash);

    new query[512], name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    mysql_format(g_MySQL, query, sizeof(query),
        "INSERT INTO `players` (`username`, `password`) VALUES ('%e', '%e')",
        name, hash
    );
    mysql_tquery(g_MySQL, query, "OnPlayerRegisterInsert", "i", playerid);
    return 1;
}

forward OnPlayerRegisterInsert(playerid);
public OnPlayerRegisterInsert(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    PlayerData[playerid][pID] = cache_insert_id();
    PlayerData[playerid][pLoggedIn] = true;
    PlayerData[playerid][pRegistering] = false;
    PlayerData[playerid][pTempPassword][0] = EOS;
    PlayerData[playerid][pState] = PLAYER_STATE_ALIVE;

    Session_Start(playerid);

    new query[256];
    mysql_format(g_MySQL, query, sizeof(query),
        "UPDATE `players` SET `last_login` = NOW() WHERE `id` = %d",
        PlayerData[playerid][pID]
    );
    mysql_tquery(g_MySQL, query);

    SendSuccessMessage(playerid, "Registrasi berhasil! Selamat datang di Vibe Roleplay.");
    SendInfoMessage(playerid, "Gunakan voice chat untuk berkomunikasi.");

    SpawnPlayerAtSavedPosition(playerid);
    Stats_OnPlayerLogin(playerid);
    return 1;
}

forward OnPasswordVerify(playerid, bool:success);
public OnPasswordVerify(playerid, bool:success)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (success)
    {
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

forward OnPlayerDataLoad(playerid);
public OnPlayerDataLoad(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (cache_num_rows() == 0)
    {
        SendErrorMessage(playerid, "Terjadi kesalahan saat memuat data.");
        SetTimerEx("KickPlayerDelay", 500, false, "i", playerid);
        return 0;
    }

    cache_get_value_name_int(0, "id", PlayerData[playerid][pID]);
    cache_get_value_name_int(0, "admin_level", PlayerData[playerid][pAdminLevel]);
    cache_get_value_name_int(0, "skin", PlayerData[playerid][pSkin]);
    cache_get_value_name_int(0, "money", PlayerData[playerid][pMoney]);
    cache_get_value_name_int(0, "bank_money", PlayerData[playerid][pBankMoney]);
    cache_get_value_name_int(0, "level", PlayerData[playerid][pLevel]);
    cache_get_value_name_int(0, "hunger", PlayerData[playerid][pHunger]);
    cache_get_value_name_int(0, "thirst", PlayerData[playerid][pThirst]);
    cache_get_value_name_int(0, "playtime", PlayerData[playerid][pPlaytime]);
    cache_get_value_name_float(0, "pos_x", PlayerData[playerid][pPosX]);
    cache_get_value_name_float(0, "pos_y", PlayerData[playerid][pPosY]);
    cache_get_value_name_float(0, "pos_z", PlayerData[playerid][pPosZ]);
    cache_get_value_name_float(0, "pos_a", PlayerData[playerid][pPosA]);
    cache_get_value_name_int(0, "interior", PlayerData[playerid][pInterior]);
    cache_get_value_name_int(0, "virtual_world", PlayerData[playerid][pVirtualWorld]);

    PlayerData[playerid][pLoggedIn] = true;
    PlayerData[playerid][pState] = PLAYER_STATE_ALIVE;

    Session_Start(playerid);

    new query[256];
    mysql_format(g_MySQL, query, sizeof(query),
        "UPDATE `players` SET `last_login` = NOW() WHERE `id` = %d",
        PlayerData[playerid][pID]
    );
    mysql_tquery(g_MySQL, query);

    SendSuccessMessage(playerid, "Login berhasil! Selamat datang kembali.");

    SpawnPlayerAtSavedPosition(playerid);
    Stats_OnPlayerLogin(playerid);
    return 1;
}

forward KickPlayerDelay(playerid);
public KickPlayerDelay(playerid)
{
    if (IsPlayerConnected(playerid))
    {
        Kick(playerid);
    }
    return 1;
}
