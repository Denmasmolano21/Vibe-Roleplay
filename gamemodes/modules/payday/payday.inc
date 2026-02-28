/*
 *  Vibe Roleplay - Payday System
 *  File: modules/payday/payday.inc
 */

#if defined _payday_included
    #endinput
#endif
#define _payday_included

#include <YSI_Coding/y_hooks>
#include <YSI_Coding/y_timers>

#define PAYDAY_INTERVAL         3600    // 1 hour in seconds
#define PAYDAY_MIN_PLAYTIME     1800    // 30 minutes minimum
#define BASE_SALARY             5000
#define SALARY_PER_LEVEL        500
#define TAX_RATE                10      // 10% tax
#define LEVEL_UP_PLAYTIME       7200    // 2 hours per level
#define LEVEL_UP_BONUS          10000

new PlayerPaydayTime[MAX_PLAYERS];
new PlayerNextPayday[MAX_PLAYERS];
new bool:PlayerPaydayEligible[MAX_PLAYERS];

stock Payday_Calculate(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    new playtime = GetPlayerSessionTime(playerid);
    
    if (playtime < PAYDAY_MIN_PLAYTIME)
    {
        new remaining = PAYDAY_MIN_PLAYTIME - playtime;
        new msg[128];
        format(msg, sizeof(msg), "Kamu belum eligible untuk payday. Butuh %d menit lagi.", remaining / 60);
        SendErrorMessage(playerid, msg);
        return 0;
    }

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
    
    PlayerData[playerid][pBankMoney] += netSalary;
    
    new totalPlaytime = GetPlayerTotalPlaytime(playerid);
    new oldLevel = PlayerData[playerid][pLevel];
    new newLevel = (totalPlaytime / LEVEL_UP_PLAYTIME) + 1;
    
    if (newLevel > oldLevel)
    {
        PlayerData[playerid][pLevel] = newLevel;
        PlayerData[playerid][pBankMoney] += LEVEL_UP_BONUS;
        
        new msg[256];
        format(msg, sizeof(msg), 
            "~g~LEVEL UP!~n~~w~Level ~y~%d ~w~-> ~y~%d~n~~g~+$%s ~w~Bonus",
            oldLevel, newLevel, FormatNumber(LEVEL_UP_BONUS));
        GameTextForPlayer(playerid, msg, 5000, 3);
        
        format(msg, sizeof(msg), 
            "Selamat! Kamu naik ke level %d dan mendapat bonus $%s!",
            newLevel, FormatNumber(LEVEL_UP_BONUS));
        SendSuccessMessage(playerid, msg);
    }
    
    Payday_ShowInfo(playerid, totalSalary, tax, netSalary, jobPay, factionSalary);
    
    SavePlayerDataToDB(playerid);
    PlayerPaydayTime[playerid] = 0;
    PlayerNextPayday[playerid] = gettime() + PAYDAY_INTERVAL;
    
    return 1;
}

stock Payday_ShowInfo(playerid, totalSalary, tax, netSalary, jobPay, factionSalary)
{
    new caption[64];
    format(caption, sizeof(caption), "%s - Payday", SERVER_NAME);

    new info[1024];
    format(info, sizeof(info), \
        "{FFFFFF}Payday Report\n\n" \
        "{00D4FF}Base Salary:\t{FFFFFF}$%s\n" \
        "{00D4FF}Level Bonus:\t{FFFFFF}$%s (Lv.%d)\n",
        FormatNumber(BASE_SALARY),
        FormatNumber(PlayerData[playerid][pLevel] * SALARY_PER_LEVEL),
        PlayerData[playerid][pLevel]
    );
    
    if (jobPay > 0)
    {
        format(info, sizeof(info), "%s{00D4FF}Job Salary:\t{FFFFFF}$%s\n",
            info, FormatNumber(jobPay));
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
        "{AFAFAF}Saldo Bank: {00FF00}$%s\n" \
        "{AFAFAF}Playtime: {FFFFFF}%d jam %d menit",
        info,
        FormatNumber(totalSalary),
        TAX_RATE,
        FormatNumber(tax),
        FormatNumber(netSalary),
        FormatNumber(PlayerData[playerid][pBankMoney]),
        GetPlayerTotalPlaytime(playerid) / 3600,
        (GetPlayerTotalPlaytime(playerid) % 3600) / 60
    );

    ShowPlayerDialog(playerid, DIALOG_PAYDAY_INFO, DIALOG_STYLE_MSGBOX,
        caption, info, "Tutup", "");
    
    new msg[128];
    format(msg, sizeof(msg), "~g~PAYDAY~n~~w~+$%s", FormatNumber(netSalary));
    GameTextForPlayer(playerid, msg, 3000, 3);
    
    return 1;
}

stock Payday_CheckEligibility(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    new currentTime = gettime();
    
    if (currentTime >= PlayerNextPayday[playerid])
    {
        PlayerPaydayEligible[playerid] = true;
        return 1;
    }
    
    return 0;
}

stock Payday_GetTimeRemaining(playerid)
{
    if (!IsPlayerConnected(playerid))
        return 0;

    new currentTime = gettime();
    new remaining = PlayerNextPayday[playerid] - currentTime;
    
    if (remaining < 0)
        remaining = 0;
    
    return remaining;
}

stock Payday_ShowTimeRemaining(playerid)
{
    new remaining = Payday_GetTimeRemaining(playerid);
    
    if (remaining <= 0)
    {
        SendInfoMessage(playerid, "Payday sudah tersedia! Gunakan /payday untuk claim.");
        return 1;
    }
    
    new hours = remaining / 3600;
    new minutes = (remaining % 3600) / 60;
    new seconds = remaining % 60;
    
    new msg[128];
    format(msg, sizeof(msg), "Payday berikutnya dalam: %02d:%02d:%02d", hours, minutes, seconds);
    SendInfoMessage(playerid, msg);
    
    return 1;
}

timer PaydayTimer[60000]()
{
    foreach(new i : Player)
    {
        if (!PlayerData[i][pLoggedIn])
            continue;
        
        Payday_CheckEligibility(i);
        
        if (PlayerPaydayEligible[i])
        {
            new msg[128];
            format(msg, sizeof(msg), 
                "{00FF00}[PAYDAY] {FFFFFF}Payday tersedia! Gunakan {00FF00}/payday {FFFFFF}untuk claim salary.");
            SendClientMessage(i, COLOR_WHITE, msg);
        }
        
        new remaining = Payday_GetTimeRemaining(i);
        if (remaining == 600 || remaining == 300 || remaining == 60)
        {
            new msg[128];
            format(msg, sizeof(msg), 
                "{00D4FF}[INFO] {FFFFFF}Payday dalam %d menit.", remaining / 60);
            SendClientMessage(i, COLOR_WHITE, msg);
        }
    }
}

hook OnPlayerConnect(playerid)
{
    PlayerPaydayTime[playerid] = 0;
    PlayerNextPayday[playerid] = gettime() + PAYDAY_INTERVAL;
    PlayerPaydayEligible[playerid] = false;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    PlayerPaydayTime[playerid] = 0;
    PlayerNextPayday[playerid] = 0;
    PlayerPaydayEligible[playerid] = false;
    return 1;
}

hook OnGameModeInit()
{
    repeat PaydayTimer();
    printf("[PAYDAY] Payday system loaded. Interval: %d seconds", PAYDAY_INTERVAL);
    return 1;
}
