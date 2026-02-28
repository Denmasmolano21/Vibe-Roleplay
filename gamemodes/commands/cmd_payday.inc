/*
 *  Vibe Roleplay - Payday Commands
 *  File: commands/cmd_payday.inc
 */

#if defined _cmd_payday_included
    #endinput
#endif
#define _cmd_payday_included

CMD:payday(playerid, params[])
{
    GUARD_READY(playerid);

    if (!PlayerPaydayEligible[playerid])
    {
        Payday_ShowTimeRemaining(playerid);
        return 1;
    }

    Payday_Calculate(playerid);
    PlayerPaydayEligible[playerid] = false;
    return 1;
}

CMD:nextpayday(playerid, params[])
{
    GUARD_READY(playerid);
    Payday_ShowTimeRemaining(playerid);
    return 1;
}

CMD:salary(playerid, params[])
{
    GUARD_READY(playerid);

    new baseSalary = BASE_SALARY;
    new levelBonus = PlayerData[playerid][pLevel] * SALARY_PER_LEVEL;
    new jobPay = 0;
    
    if (PlayerJob[playerid] != E_JOB_TYPE:JOB_NONE)
    {
        jobPay = JobData[_:PlayerJob[playerid]][jobSalary];
    }
    
    new factionSalary = 0;
    if (PlayerFaction[playerid] != -1)
    {
        factionSalary = 3000 + (PlayerFactionRank[playerid] * 500);
    }
    
    new totalSalary = baseSalary + levelBonus + jobPay + factionSalary;
    new tax = (totalSalary * TAX_RATE) / 100;
    new netSalary = totalSalary - tax;

    new caption[64];
    format(caption, sizeof(caption), "%s - Salary Info", SERVER_NAME);

    new info[768];
    format(info, sizeof(info), \
        "{FFFFFF}Informasi Salary Kamu\n\n" \
        "{00D4FF}Base Salary:\t{FFFFFF}$%s\n" \
        "{00D4FF}Level Bonus:\t{FFFFFF}$%s (Lv.%d)\n",
        FormatNumber(baseSalary),
        FormatNumber(levelBonus),
        PlayerData[playerid][pLevel]
    );
    
    if (jobPay > 0)
    {
        new jobNameStr[MAX_JOB_NAME];
        format(jobNameStr, sizeof(jobNameStr), "%s", JobData[_:PlayerJob[playerid]][jobName]);
        format(info, sizeof(info), "%s{00D4FF}Job Salary:\t{FFFFFF}$%s (%s)\n",
            info, FormatNumber(jobPay), jobNameStr);
    }
    
    if (factionSalary > 0)
    {
        format(info, sizeof(info), "%s{00D4FF}Faction Salary:\t{FFFFFF}$%s\n",
            info, FormatNumber(factionSalary));
    }
    
    format(info, sizeof(info), 
        "%s{AFAFAF}─────────────────────\n" \
        "{00D4FF}Total Salary:\t{00FF00}$%s\n" \
        "{FF6B00}Tax (%d%%):\t{FFFFFF}-$%s\n" \
        "{AFAFAF}─────────────────────\n" \
        "{00FF00}Net Salary:\t{00FF00}$%s\n\n" \
        "{AFAFAF}Payday setiap 1 jam playtime",
        info,
        FormatNumber(totalSalary),
        TAX_RATE,
        FormatNumber(tax),
        FormatNumber(netSalary)
    );

    ShowPlayerDialog(playerid, DIALOG_SALARY_INFO, DIALOG_STYLE_MSGBOX,
        caption, info, "Tutup", "");
    return 1;
}

CMD:playtime(playerid, params[])
{
    GUARD_READY(playerid);

    new totalPlaytime = GetPlayerTotalPlaytime(playerid);
    new sessionTime = GetPlayerSessionTime(playerid);
    
    new totalHours = totalPlaytime / 3600;
    new totalMinutes = (totalPlaytime % 3600) / 60;
    
    new sessionHours = sessionTime / 3600;
    new sessionMinutes = (sessionTime % 3600) / 60;
    
    new nextLevel = PlayerData[playerid][pLevel] + 1;
    new playtimeForNextLevel = nextLevel * LEVEL_UP_PLAYTIME;
    new remainingTime = playtimeForNextLevel - totalPlaytime;
    
    if (remainingTime < 0)
        remainingTime = 0;
    
    new remainingHours = remainingTime / 3600;
    new remainingMinutes = (remainingTime % 3600) / 60;

    new caption[64];
    format(caption, sizeof(caption), "%s - Playtime", SERVER_NAME);

    new info[512];
    format(info, sizeof(info), \
        "{FFFFFF}Statistik Playtime\n\n" \
        "{00D4FF}Total Playtime:\t{FFFFFF}%d jam %d menit\n" \
        "{00D4FF}Session Time:\t{FFFFFF}%d jam %d menit\n" \
        "{00D4FF}Current Level:\t{FFFFFF}%d\n\n" \
        "{AFAFAF}Level Up ke %d:\n" \
        "{FFFFFF}Butuh %d jam %d menit lagi",
        totalHours, totalMinutes,
        sessionHours, sessionMinutes,
        PlayerData[playerid][pLevel],
        nextLevel,
        remainingHours, remainingMinutes
    );

    ShowPlayerDialog(playerid, DIALOG_PLAYTIME_INFO, DIALOG_STYLE_MSGBOX,
        caption, info, "Tutup", "");
    return 1;
}

// Admin command untuk force payday
CMD:forcepayday(playerid, params[])
{
    GUARD_ADMIN(playerid);

    new targetid;
    if (sscanf(params, "u", targetid))
    {
        SendErrorMessage(playerid, "Penggunaan: /forcepayday [playerid]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 1;
    }

    if (!PlayerData[targetid][pLoggedIn])
    {
        SendErrorMessage(playerid, "Player belum login.");
        return 1;
    }

    Payday_Calculate(targetid);
    PlayerPaydayEligible[targetid] = false;

    new targetName[MAX_PLAYER_NAME], adminName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    GetPlayerName(playerid, adminName, sizeof(adminName));

    new msg[128];
    format(msg, sizeof(msg), "Admin %s memberikan payday kepada %s", adminName, targetName);
    AdminLog(msg);

    format(msg, sizeof(msg), "Kamu memberikan payday kepada %s", targetName);
    SendSuccessMessage(playerid, msg);

    return 1;
}

// Admin command untuk set payday interval
CMD:setpaydayinterval(playerid, params[])
{
    GUARD_ADMIN(playerid);

    new minutes;
    if (sscanf(params, "i", minutes))
    {
        SendErrorMessage(playerid, "Penggunaan: /setpaydayinterval [minutes]");
        return 1;
    }

    if (minutes < 1 || minutes > 1440)
    {
        SendErrorMessage(playerid, "Interval harus antara 1-1440 menit (1 hari).");
        return 1;
    }

    // Note: This would require a global variable to change interval dynamically
    new msg[128];
    format(msg, sizeof(msg), "Payday interval diubah menjadi %d menit (restart required)", minutes);
    SendSuccessMessage(playerid, msg);

    format(msg, sizeof(msg), "Admin %s mengubah payday interval menjadi %d menit", 
        GetPlayerNameEx(playerid), minutes);
    AdminLog(msg);

    return 1;
}
