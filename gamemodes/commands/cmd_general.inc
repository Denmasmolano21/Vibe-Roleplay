/*
 *  Vibe Roleplay - General Commands
 *  File: commands/cmd_general.inc
 */

#if defined _cmd_general_included
    #endinput
#endif
#define _cmd_general_included

// HELP COMMAND

CMD:help(playerid, params[])
{
    new caption[64];
    format(caption, sizeof(caption), "%s - Bantuan", SERVER_NAME);

    new info[512];
    format(info, sizeof(info), \
        "{FFFFFF}Pilih kategori bantuan yang ingin kamu lihat:\n\n" \
        "{00D4FF}General\t\t{FFFFFF}Command umum pemain\n" \
        "{00D4FF}Vehicle\t\t{FFFFFF}Command kendaraan\n" \
        "{00D4FF}Job\t\t{FFFFFF}Command pekerjaan\n" \
        "{00D4FF}Property\t\t{FFFFFF}Command properti\n" \
        "{00D4FF}Faction\t\t{FFFFFF}Command faction"
    );

    ShowPlayerDialog(playerid, DIALOG_HELP_CATEGORY, DIALOG_STYLE_TABLIST,
        caption, info, "Pilih", "Tutup");
    return 1;
}

// REPORT & ASK SYSTEM

CMD:report(playerid, params[])
{
    GUARD_READY(playerid);

    if (isnull(params))
    {
        SendErrorMessage(playerid, "Penggunaan: /report [laporan]");
        return 1;
    }

    if (strlen(params) < 10)
    {
        SendErrorMessage(playerid, "Laporan terlalu pendek. Minimal 10 karakter.");
        return 1;
    }

    new reportid = Report_Create(playerid, REPORT_TYPE_REPORT, params);
    if (reportid == -1)
    {
        SendErrorMessage(playerid, "Sistem report penuh. Silakan coba lagi nanti.");
        return 1;
    }

    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    new msg[256];
    format(msg, sizeof(msg), "[REPORT #%d] %s (ID: %d): %s", reportid, name, playerid, params);
    
    new adminCount = 0;
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && PlayerData[i][pAdminLevel] >= 1)
        {
            SendClientMessage(i, COLOR_WARNING, msg);
            SendClientMessage(i, COLOR_INFO, "Gunakan /reports untuk melihat dan membalas.");
            adminCount++;
        }
    }

    ReportLog(playerid, params);

    if (adminCount > 0)
    {
        format(msg, sizeof(msg), "Laporan kamu telah dikirim ke %d admin online. (ID: #%d)", adminCount, reportid);
        SendSuccessMessage(playerid, msg);
    }
    else
    {
        format(msg, sizeof(msg), "Tidak ada admin online. Laporan kamu telah disimpan. (ID: #%d)", reportid);
        SendInfoMessage(playerid, msg);
    }
    return 1;
}

CMD:ask(playerid, params[])
{
    GUARD_READY(playerid);

    if (isnull(params))
    {
        SendErrorMessage(playerid, "Penggunaan: /ask [pertanyaan]");
        return 1;
    }

    if (strlen(params) < 10)
    {
        SendErrorMessage(playerid, "Pertanyaan terlalu pendek. Minimal 10 karakter.");
        return 1;
    }

    new reportid = Report_Create(playerid, REPORT_TYPE_ASK, params);
    if (reportid == -1)
    {
        SendErrorMessage(playerid, "Sistem ask penuh. Silakan coba lagi nanti.");
        return 1;
    }

    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    new msg[256];
    format(msg, sizeof(msg), "[ASK #%d] %s (ID: %d): %s", reportid, name, playerid, params);
    
    new adminCount = 0;
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && PlayerData[i][pAdminLevel] >= 1)
        {
            SendClientMessage(i, COLOR_INFO, msg);
            SendClientMessage(i, COLOR_INFO, "Gunakan /reports untuk melihat dan membalas.");
            adminCount++;
        }
    }

    if (adminCount > 0)
    {
        format(msg, sizeof(msg), "Pertanyaan kamu telah dikirim ke %d admin online. (ID: #%d)", adminCount, reportid);
        SendSuccessMessage(playerid, msg);
    }
    else
    {
        format(msg, sizeof(msg), "Tidak ada admin online. Pertanyaan kamu telah disimpan. (ID: #%d)", reportid);
        SendInfoMessage(playerid, msg);
    }
    return 1;
}

// STATS COMMANDS

CMD:stats(playerid, params[])
{
    GUARD_READY(playerid);

    new totalPlaytime = GetPlayerTotalPlaytime(playerid);
    new hours = totalPlaytime / 60;
    new mins  = totalPlaytime % 60;

    new name[MAX_PLAYER_NAME], displayName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    FormatRPName(name, displayName, sizeof(displayName));

    new caption[64];
    format(caption, sizeof(caption), "%s - Statistik", SERVER_NAME);

    new info[512];
    format(info, sizeof(info), \
        "{00D4FF}Nama\t\t{FFFFFF}%s\n" \
        "{00D4FF}Level\t\t{FFFFFF}%d\n" \
        "{00D4FF}Uang\t\t{00FF00}$%d\n" \
        "{00D4FF}Hunger\t\t{FFFFFF}%d/100\n" \
        "{00D4FF}Thirst\t\t{FFFFFF}%d/100\n" \
        "{00D4FF}Playtime\t{FFFFFF}%d jam %d menit",
        displayName,
        PlayerData[playerid][pLevel],
        VRP_GetPlayerMoney(playerid),
        PlayerData[playerid][pHunger],
        PlayerData[playerid][pThirst],
        hours, mins
    );

    ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_TABLIST,
        caption, info, "Tutup", "");
    return 1;
}

CMD:mypos(playerid, params[])
{
    GUARD_READY(playerid);

    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    new caption[64];
    format(caption, sizeof(caption), "%s - Posisi", SERVER_NAME);

    new info[256];
    format(info, sizeof(info), \
        "{00D4FF}X\t\t{FFFFFF}%.4f\n" \
        "{00D4FF}Y\t\t{FFFFFF}%.4f\n" \
        "{00D4FF}Z\t\t{FFFFFF}%.4f\n" \
        "{00D4FF}Angle\t\t{FFFFFF}%.4f\n" \
        "{00D4FF}Interior\t{FFFFFF}%d\n" \
        "{00D4FF}VW\t\t{FFFFFF}%d",
        x, y, z, a,
        GetPlayerInterior(playerid),
        GetPlayerVirtualWorld(playerid)
    );

    ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_TABLIST,
        caption, info, "Tutup", "");
    return 1;
}

// ACTION COMMANDS

CMD:eat(playerid, params[])
{
    GUARD_READY(playerid);

    Stats_AddHunger(playerid, 20);
    SendSuccessMessage(playerid, "Kamu telah makan. Hunger +20");
    return 1;
}

CMD:drink(playerid, params[])
{
    GUARD_READY(playerid);

    Stats_AddThirst(playerid, 20);
    SendSuccessMessage(playerid, "Kamu telah minum. Thirst +20");
    return 1;
}
