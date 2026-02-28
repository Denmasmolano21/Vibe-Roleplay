/*
 *  Vibe Roleplay - Admin Log System
 *  File: utils/admin_log.inc
 */

#if defined _admin_log_included
    #endinput
#endif
#define _admin_log_included

stock AdminLog(const action[])
{
    if (isnull(action))
        return 0;

    new File:file = fopen(ADMIN_LOG_FILE, io_append);
    if (!file)
        return 0;

    new timestamp[64], date[32], time[32];
    getdate(date[2], date[1], date[0]);
    gettime(time[0], time[1], time[2]);
    format(timestamp, sizeof(timestamp), "[%02d/%02d/%d %02d:%02d:%02d]", 
        date[0], date[1], date[2], time[0], time[1], time[2]);

    new log[256];
    format(log, sizeof(log), "%s %s\r\n", timestamp, action);
    fwrite(file, log);
    fclose(file);
    return 1;
}

stock AdminLogEx(playerid, const action[])
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (isnull(action))
        return 0;

    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    new log[256];
    format(log, sizeof(log), "[ADMIN: %s (ID: %d)] %s", name, playerid, action);
    return AdminLog(log);
}

stock ReportLog(playerid, const report[])
{
    if (!IsPlayerConnected(playerid))
        return 0;

    if (isnull(report))
        return 0;

    new File:file = fopen(REPORT_LOG_FILE, io_append);
    if (!file)
        return 0;

    new timestamp[64], date[32], time[32];
    getdate(date[2], date[1], date[0]);
    gettime(time[0], time[1], time[2]);
    format(timestamp, sizeof(timestamp), "[%02d/%02d/%d %02d:%02d:%02d]", 
        date[0], date[1], date[2], time[0], time[1], time[2]);

    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    new log[256];
    format(log, sizeof(log), "%s [%s (ID: %d)] %s\r\n", timestamp, name, playerid, report);
    fwrite(file, log);
    fclose(file);
    return 1;
}
