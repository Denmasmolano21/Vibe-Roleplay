/*
 *  Vibe Roleplay - Admin Commands
 *  File: commands/cmd_admin.inc
 */

#if defined _cmd_admin_included
    #endinput
#endif
#define _cmd_admin_included

// LEVEL 1+ - HELPER COMMANDS

CMD:a(playerid, params[])
{
    GUARD_ADMIN(playerid);

    if (isnull(params))
    {
        SendErrorMessage(playerid, "Penggunaan: /a [pesan]");
        return 1;
    }

    new msg[144], name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    
    new levelName[32];
    format(levelName, sizeof(levelName), "%s", GetAdminLevelName(PlayerData[playerid][pAdminLevel]));
    
    format(msg, sizeof(msg), "[%s %s]: %s", levelName, name, params);
    
    foreach(new i : Player)
    {
        if (PlayerData[i][pAdminLevel] >= 1)
        {
            new color = GetAdminLevelColor(PlayerData[playerid][pAdminLevel]);
            SendClientMessage(i, color, msg);
        }
    }
    
    return 1;
}

CMD:goto(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_HELPER);

    new targetid;
    if (sscanf(params, "u", targetid))
    {
        SendErrorMessage(playerid, "Penggunaan: /goto [playerid]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    new Float:x, Float:y, Float:z;
    GetPlayerPos(targetid, x, y, z);
    SetPlayerPos(playerid, x + 1, y, z);
    SetPlayerInterior(playerid, GetPlayerInterior(targetid));
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));

    new targetName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    
    new msg[128];
    format(msg, sizeof(msg), "Teleport ke %s", targetName);
    SendSuccessMessage(playerid, msg);
    
    format(msg, sizeof(msg), "Teleport to %s (ID: %d)", targetName, targetid);
    AdminLogEx(playerid, msg);
    
    return 1;
}

CMD:gethere(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_HELPER);

    new targetid;
    if (sscanf(params, "u", targetid))
    {
        SendErrorMessage(playerid, "Penggunaan: /gethere [playerid]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    SetPlayerPos(targetid, x + 1, y, z);
    SetPlayerInterior(targetid, GetPlayerInterior(playerid));
    SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));

    new targetName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    
    new msg[128];
    format(msg, sizeof(msg), "Teleport %s ke kamu", targetName);
    SendSuccessMessage(playerid, msg);
    
    format(msg, sizeof(msg), "Get here %s (ID: %d)", targetName, targetid);
    AdminLogEx(playerid, msg);
    
    return 1;
}

CMD:freeze(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_HELPER);

    new targetid;
    if (sscanf(params, "u", targetid))
    {
        SendErrorMessage(playerid, "Penggunaan: /freeze [playerid]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    TogglePlayerControllable(targetid, false);

    new targetName[MAX_PLAYER_NAME], adminName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    GetPlayerName(playerid, adminName, sizeof(adminName));
    
    new msg[128];
    format(msg, sizeof(msg), "Kamu freeze %s", targetName);
    SendSuccessMessage(playerid, msg);
    
    format(msg, sizeof(msg), "Kamu di-freeze oleh admin %s", adminName);
    SendErrorMessage(targetid, msg);
    
    format(msg, sizeof(msg), "Freeze %s (ID: %d)", targetName, targetid);
    AdminLogEx(playerid, msg);
    
    return 1;
}

CMD:unfreeze(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_HELPER);

    new targetid;
    if (sscanf(params, "u", targetid))
    {
        SendErrorMessage(playerid, "Penggunaan: /unfreeze [playerid]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    TogglePlayerControllable(targetid, true);

    new targetName[MAX_PLAYER_NAME], adminName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    GetPlayerName(playerid, adminName, sizeof(adminName));
    
    new msg[128];
    format(msg, sizeof(msg), "Kamu unfreeze %s", targetName);
    SendSuccessMessage(playerid, msg);
    
    format(msg, sizeof(msg), "Kamu di-unfreeze oleh admin %s", adminName);
    SendSuccessMessage(targetid, msg);
    
    format(msg, sizeof(msg), "Unfreeze %s (ID: %d)", targetName, targetid);
    AdminLogEx(playerid, msg);
    
    return 1;
}

CMD:slap(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_HELPER);

    new targetid;
    if (sscanf(params, "u", targetid))
    {
        SendErrorMessage(playerid, "Penggunaan: /slap [playerid]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    new Float:x, Float:y, Float:z;
    GetPlayerPos(targetid, x, y, z);
    SetPlayerPos(targetid, x, y, z + 5);

    new targetName[MAX_PLAYER_NAME], adminName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    GetPlayerName(playerid, adminName, sizeof(adminName));
    
    new msg[128];
    format(msg, sizeof(msg), "Kamu slap %s", targetName);
    SendSuccessMessage(playerid, msg);
    
    format(msg, sizeof(msg), "Kamu di-slap oleh admin %s", adminName);
    SendErrorMessage(targetid, msg);
    
    format(msg, sizeof(msg), "Slap %s (ID: %d)", targetName, targetid);
    AdminLogEx(playerid, msg);
    
    return 1;
}

CMD:kick(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_HELPER);

    new targetid, reason[64];
    if (sscanf(params, "us[64]", targetid, reason))
    {
        SendErrorMessage(playerid, "Penggunaan: /kick [playerid] [alasan]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    if (PlayerData[targetid][pAdminLevel] >= PlayerData[playerid][pAdminLevel])
    {
        SendErrorMessage(playerid, "Kamu tidak bisa kick admin yang level nya sama atau lebih tinggi.");
        return 1;
    }

    new targetName[MAX_PLAYER_NAME], adminName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    GetPlayerName(playerid, adminName, sizeof(adminName));
    
    new msg[144];
    format(msg, sizeof(msg), "{FF0000}%s telah di-kick oleh admin %s. Alasan: %s", 
        targetName, adminName, reason);
    SendClientMessageToAll(COLOR_WHITE, msg);
    
    format(msg, sizeof(msg), "Kick %s (ID: %d) - Reason: %s", targetName, targetid, reason);
    AdminLogEx(playerid, msg);
    
    SetTimerEx("KickPlayer", 500, false, "i", targetid);
    return 1;
}

// LEVEL 2+ - MODERATOR COMMANDS

CMD:jail(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_MODERATOR);

    new targetid, minutes, reason[64];
    if (sscanf(params, "uis[64]", targetid, minutes, reason))
    {
        SendErrorMessage(playerid, "Penggunaan: /jail [playerid] [menit] [alasan]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    if (minutes < 1 || minutes > 60)
    {
        SendErrorMessage(playerid, "Durasi jail: 1-60 menit.");
        return 1;
    }

    if (PlayerData[targetid][pAdminLevel] >= PlayerData[playerid][pAdminLevel])
    {
        SendErrorMessage(playerid, "Kamu tidak bisa jail admin yang level nya sama atau lebih tinggi.");
        return 1;
    }

    // Jail player (implement jail system later)
    SetPlayerPos(targetid, 264.0, 77.0, 1001.0);
    SetPlayerInterior(targetid, 6);
    SetPlayerVirtualWorld(targetid, targetid + 1);
    TogglePlayerControllable(targetid, false);

    new targetName[MAX_PLAYER_NAME], adminName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    GetPlayerName(playerid, adminName, sizeof(adminName));
    
    new msg[144];
    format(msg, sizeof(msg), "{FF6B00}%s telah di-jail oleh admin %s selama %d menit. Alasan: %s", 
        targetName, adminName, minutes, reason);
    SendClientMessageToAll(COLOR_WHITE, msg);
    
    format(msg, sizeof(msg), "Jail %s (ID: %d) for %d minutes - Reason: %s", 
        targetName, targetid, minutes, reason);
    AdminLogEx(playerid, msg);
    
    return 1;
}

CMD:unjail(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_MODERATOR);

    new targetid;
    if (sscanf(params, "u", targetid))
    {
        SendErrorMessage(playerid, "Penggunaan: /unjail [playerid]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    // Unjail player
    SpawnPlayer(targetid);
    TogglePlayerControllable(targetid, true);

    new targetName[MAX_PLAYER_NAME], adminName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    GetPlayerName(playerid, adminName, sizeof(adminName));
    
    new msg[128];
    format(msg, sizeof(msg), "Kamu unjail %s", targetName);
    SendSuccessMessage(playerid, msg);
    
    format(msg, sizeof(msg), "Kamu di-unjail oleh admin %s", adminName);
    SendSuccessMessage(targetid, msg);
    
    format(msg, sizeof(msg), "Unjail %s (ID: %d)", targetName, targetid);
    AdminLogEx(playerid, msg);
    
    return 1;
}

CMD:ban(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_MODERATOR);

    new targetid, reason[64];
    if (sscanf(params, "us[64]", targetid, reason))
    {
        SendErrorMessage(playerid, "Penggunaan: /ban [playerid] [alasan]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    if (PlayerData[targetid][pAdminLevel] >= PlayerData[playerid][pAdminLevel])
    {
        SendErrorMessage(playerid, "Kamu tidak bisa ban admin yang level nya sama atau lebih tinggi.");
        return 1;
    }

    new targetName[MAX_PLAYER_NAME], adminName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    GetPlayerName(playerid, adminName, sizeof(adminName));
    
    new msg[144];
    format(msg, sizeof(msg), "{FF0000}%s telah di-ban oleh admin %s. Alasan: %s", 
        targetName, adminName, reason);
    SendClientMessageToAll(COLOR_WHITE, msg);
    
    format(msg, sizeof(msg), "Ban %s (ID: %d) - Reason: %s", targetName, targetid, reason);
    AdminLogEx(playerid, msg);
    
    // Ban player (implement ban system later)
    BanEx(targetid, reason);
    
    return 1;
}

CMD:akill(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_MODERATOR);

    new targetid;
    if (sscanf(params, "u", targetid))
    {
        SendErrorMessage(playerid, "Penggunaan: /akill [playerid]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    SetPlayerHealth(targetid, 0.0);

    new targetName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    
    new msg[128];
    format(msg, sizeof(msg), "Kamu kill %s", targetName);
    SendSuccessMessage(playerid, msg);
    
    format(msg, sizeof(msg), "Kill %s (ID: %d)", targetName, targetid);
    AdminLogEx(playerid, msg);
    
    return 1;
}

// LEVEL 3+ - ADMIN COMMANDS

CMD:announce(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_ADMIN);

    if (isnull(params))
    {
        SendErrorMessage(playerid, "Penggunaan: /announce [pesan]");
        return 1;
    }

    new msg[144];
    format(msg, sizeof(msg), "~r~ANNOUNCEMENT~n~~w~%s", params);
    
    foreach(new i : Player)
    {
        GameTextForPlayer(i, msg, 5000, 3);
    }
    
    format(msg, sizeof(msg), "{FF0000}[ANNOUNCEMENT] {FFFFFF}%s", params);
    SendClientMessageToAll(COLOR_WHITE, msg);
    
    format(msg, sizeof(msg), "Announce: %s", params);
    AdminLogEx(playerid, msg);
    
    return 1;
}

CMD:givemoney(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_ADMIN);

    new targetid, amount;
    if (sscanf(params, "ui", targetid, amount))
    {
        SendErrorMessage(playerid, "Penggunaan: /givemoney [playerid] [amount]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    // Level 3 max 100k, Level 4 max 1M, Level 5+ unlimited
    new maxAmount = 100000;
    if (PlayerData[playerid][pAdminLevel] >= ADMIN_LEVEL_HEAD_ADMIN)
        maxAmount = 1000000;
    if (PlayerData[playerid][pAdminLevel] >= ADMIN_LEVEL_MANAGER)
        maxAmount = 999999999;

    if (amount > maxAmount)
    {
        new msg[128];
        format(msg, sizeof(msg), "Maximum amount untuk level kamu: $%s", FormatNumber(maxAmount));
        SendErrorMessage(playerid, msg);
        return 1;
    }

    PlayerData[targetid][pMoney] += amount;
    GivePlayerMoney(targetid, amount);

    new targetName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    
    new msg[128];
    format(msg, sizeof(msg), "Kamu berikan $%s kepada %s", FormatNumber(amount), targetName);
    SendSuccessMessage(playerid, msg);
    
    format(msg, sizeof(msg), "Admin memberikan $%s kepada kamu", FormatNumber(amount));
    SendSuccessMessage(targetid, msg);
    
    format(msg, sizeof(msg), "Give money $%s to %s (ID: %d)", FormatNumber(amount), targetName, targetid);
    AdminLogEx(playerid, msg);
    
    return 1;
}

CMD:sethealth(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_ADMIN);

    new targetid, Float:health;
    if (sscanf(params, "uf", targetid, health))
    {
        SendErrorMessage(playerid, "Penggunaan: /sethealth [playerid] [amount]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    if (health < 0 || health > 100)
    {
        SendErrorMessage(playerid, "Health: 0-100");
        return 1;
    }

    SetPlayerHealth(targetid, health);

    new targetName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    
    new msg[128];
    format(msg, sizeof(msg), "Set health %s menjadi %.0f", targetName, health);
    SendSuccessMessage(playerid, msg);
    
    format(msg, sizeof(msg), "Set health %s (ID: %d) to %.0f", targetName, targetid, health);
    AdminLogEx(playerid, msg);
    
    return 1;
}

CMD:setarmour(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_ADMIN);

    new targetid, Float:armour;
    if (sscanf(params, "uf", targetid, armour))
    {
        SendErrorMessage(playerid, "Penggunaan: /setarmour [playerid] [amount]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    if (armour < 0 || armour > 100)
    {
        SendErrorMessage(playerid, "Armour: 0-100");
        return 1;
    }

    SetPlayerArmour(targetid, armour);

    new targetName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    
    new msg[128];
    format(msg, sizeof(msg), "Set armour %s menjadi %.0f", targetName, armour);
    SendSuccessMessage(playerid, msg);
    
    format(msg, sizeof(msg), "Set armour %s (ID: %d) to %.0f", targetName, targetid, armour);
    AdminLogEx(playerid, msg);
    
    return 1;
}

// LEVEL 4+ - HEAD ADMIN COMMANDS

CMD:makeadmin(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_HEAD_ADMIN);

    new targetid, level;
    if (sscanf(params, "ui", targetid, level))
    {
        SendErrorMessage(playerid, "Penggunaan: /makeadmin [playerid] [level]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    // Level restrictions
    new maxLevel = 2;
    if (PlayerData[playerid][pAdminLevel] >= ADMIN_LEVEL_MANAGER)
        maxLevel = 3;
    if (PlayerData[playerid][pAdminLevel] >= ADMIN_LEVEL_DEVELOPER)
        maxLevel = 5;
    if (PlayerData[playerid][pAdminLevel] >= ADMIN_LEVEL_OWNER)
        maxLevel = 7;

    if (level > maxLevel)
    {
        new msg[128];
        format(msg, sizeof(msg), "Kamu hanya bisa set admin level maksimal %d", maxLevel);
        SendErrorMessage(playerid, msg);
        return 1;
    }

    if (level < 0 || level > 7)
    {
        SendErrorMessage(playerid, "Admin level: 0-7");
        return 1;
    }

    PlayerData[targetid][pAdminLevel] = level;
    SavePlayerDataToDB(targetid);

    new targetName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    
    new msg[128];
    format(msg, sizeof(msg), "Set admin level %s menjadi %d (%s)", 
        targetName, level, GetAdminLevelName(level));
    SendSuccessMessage(playerid, msg);
    
    format(msg, sizeof(msg), "Admin level kamu diubah menjadi %d (%s)", 
        level, GetAdminLevelName(level));
    SendSuccessMessage(targetid, msg);
    
    format(msg, sizeof(msg), "Set admin level %s (ID: %d) to %d", targetName, targetid, level);
    AdminLogEx(playerid, msg);
    
    return 1;
}

// LEVEL 6+ - DEVELOPER COMMANDS

CMD:gmx(playerid, params[])
{
    GUARD_ADMIN_LEVEL(playerid, ADMIN_LEVEL_DEVELOPER);

    new msg[128];
    format(msg, sizeof(msg), "{FF0000}[SERVER] {FFFFFF}Server akan restart dalam 5 detik...");
    SendClientMessageToAll(COLOR_WHITE, msg);
    
    format(msg, sizeof(msg), "GMX (Server Restart)");
    AdminLogEx(playerid, msg);
    
    SetTimer("ServerGMX", 5000, false);
    return 1;
}

// Helper Functions

forward KickPlayer(playerid);
public KickPlayer(playerid)
{
    Kick(playerid);
    return 1;
}

forward ServerGMX();
public ServerGMX()
{
    SendRconCommand("gmx");
    return 1;
}

// Admin Panel Menu

CMD:admin(playerid, params[])
{
    GUARD_READY(playerid);
    GUARD_ADMIN(playerid);

    new caption[64];
    format(caption, sizeof(caption), "%s - Admin Panel", SERVER_NAME);

    new info[768];
    format(info, sizeof(info), \
        "{FFFFFF}Selamat datang di Admin Panel\n" \
        "{AFAFAF}Level: {00FF00}%s\n\n" \
        "{FF6B00}Player Management\t{FFFFFF}Kelola player online\n" \
        "{FF6B00}Teleport Menu\t\t{FFFFFF}Teleport ke player/lokasi\n" \
        "{FF6B00}Vehicle Menu\t\t{FFFFFF}Spawn/kelola kendaraan\n" \
        "{FF6B00}Server Tools\t\t{FFFFFF}Tools server & pengumuman\n" \
        "{FF6B00}Reports & Asks\t\t{FFFFFF}Lihat report/ask (%d)\n" \
        "{FF6B00}Admin Help\t\t{FFFFFF}Bantuan command admin",
        GetAdminLevelName(PlayerData[playerid][pAdminLevel]),
        Report_GetCount()
    );

    ShowPlayerDialog(playerid, DIALOG_ADMIN_MAIN, DIALOG_STYLE_TABLIST,
        caption, info, "Pilih", "Tutup");
    return 1;
}

CMD:pm(playerid, params[])
{
    GUARD_READY(playerid);
    GUARD_ADMIN(playerid);

    new caption[64];
    format(caption, sizeof(caption), "%s - Admin Panel", SERVER_NAME);

    new info[768];
    format(info, sizeof(info), \
        "{FFFFFF}Selamat datang di Admin Panel\n" \
        "{AFAFAF}Level: {00FF00}%s\n\n" \
        "{FF6B00}Player Management\t{FFFFFF}Kelola player online\n" \
        "{FF6B00}Teleport Menu\t\t{FFFFFF}Teleport ke player/lokasi\n" \
        "{FF6B00}Vehicle Menu\t\t{FFFFFF}Spawn/kelola kendaraan\n" \
        "{FF6B00}Server Tools\t\t{FFFFFF}Tools server & pengumuman\n" \
        "{FF6B00}Reports & Asks\t\t{FFFFFF}Lihat report/ask (%d)\n" \
        "{FF6B00}Admin Help\t\t{FFFFFF}Bantuan command admin",
        GetAdminLevelName(PlayerData[playerid][pAdminLevel]),
        Report_GetCount()
    );

    ShowPlayerDialog(playerid, DIALOG_ADMIN_MAIN, DIALOG_STYLE_TABLIST,
        caption, info, "Pilih", "Tutup");
    return 1;
}

CMD:ahelp(playerid, params[])
{
    GUARD_ADMIN(playerid);

    new caption[64];
    format(caption, sizeof(caption), "%s - Admin Commands", SERVER_NAME);

    new info[2048];
    format(info, sizeof(info), \
        "{FFFFFF}Admin Commands - Level %d (%s)\n\n",
        PlayerData[playerid][pAdminLevel],
        GetAdminLevelName(PlayerData[playerid][pAdminLevel])
    );

    // Level 1+
    if (PlayerData[playerid][pAdminLevel] >= ADMIN_LEVEL_HELPER)
    {
        format(info, sizeof(info), "%s{00FF00}[Level 1 - Helper]\n", info);
        format(info, sizeof(info), "%s{FFFFFF}/a, /goto, /gethere, /freeze, /unfreeze\n", info);
        format(info, sizeof(info), "%s{FFFFFF}/slap, /kick\n\n", info);
    }

    // Level 2+
    if (PlayerData[playerid][pAdminLevel] >= ADMIN_LEVEL_MODERATOR)
    {
        format(info, sizeof(info), "%s{00D4FF}[Level 2 - Moderator]\n", info);
        format(info, sizeof(info), "%s{FFFFFF}/jail, /unjail, /ban, /akill\n\n", info);
    }

    // Level 3+
    if (PlayerData[playerid][pAdminLevel] >= ADMIN_LEVEL_ADMIN)
    {
        format(info, sizeof(info), "%s{FF6B00}[Level 3 - Admin]\n", info);
        format(info, sizeof(info), "%s{FFFFFF}/announce, /givemoney, /sethealth, /setarmour\n\n", info);
    }

    // Level 4+
    if (PlayerData[playerid][pAdminLevel] >= ADMIN_LEVEL_HEAD_ADMIN)
    {
        format(info, sizeof(info), "%s{FF0000}[Level 4 - Head Admin]\n", info);
        format(info, sizeof(info), "%s{FFFFFF}/makeadmin, /setlevel\n\n", info);
    }

    // Level 6+
    if (PlayerData[playerid][pAdminLevel] >= ADMIN_LEVEL_DEVELOPER)
    {
        format(info, sizeof(info), "%s{FFFF00}[Level 6 - Developer]\n", info);
        format(info, sizeof(info), "%s{FFFFFF}/gmx\n\n", info);
    }

    ShowPlayerDialog(playerid, DIALOG_ADMIN_HELP, DIALOG_STYLE_MSGBOX,
        caption, info, "Tutup", "");
    return 1;
}
