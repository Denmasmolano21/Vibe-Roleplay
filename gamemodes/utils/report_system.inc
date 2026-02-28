/*
 *  Vibe Roleplay - Report & Ask System
 *  File: utils/report_system.inc
 */

#if defined _report_system_included
    #endinput
#endif
#define _report_system_included

#define MAX_REPORTS             50
#define MAX_REPORT_TEXT         128

enum E_REPORT_TYPE
{
    REPORT_TYPE_NONE,
    REPORT_TYPE_REPORT,
    REPORT_TYPE_ASK
};

enum E_REPORT_DATA
{
    rID,
    rPlayerID,
    rPlayerName[MAX_PLAYER_NAME],
    E_REPORT_TYPE:rType,
    rMessage[MAX_REPORT_TEXT],
    rTimestamp,
    bool:rActive
};

new ReportData[MAX_REPORTS][E_REPORT_DATA];
new Iterator:Reports<MAX_REPORTS>;

stock Report_Create(playerid, E_REPORT_TYPE:type, const message[])
{
    if (!IsPlayerConnected(playerid))
        return -1;

    new id = Iter_Free(Reports);
    if (id == INVALID_ITERATOR_SLOT)
        return -1;

    ReportData[id][rID] = id;
    ReportData[id][rPlayerID] = playerid;
    GetPlayerName(playerid, ReportData[id][rPlayerName], MAX_PLAYER_NAME);
    ReportData[id][rType] = type;
    format(ReportData[id][rMessage], MAX_REPORT_TEXT, "%s", message);
    ReportData[id][rTimestamp] = gettime();
    ReportData[id][rActive] = true;

    Iter_Add(Reports, id);
    return id;
}

stock Report_Remove(id)
{
    if (!Iter_Contains(Reports, id))
        return 0;

    ReportData[id][rActive] = false;
    Iter_Remove(Reports, id);
    return 1;
}

stock Report_GetPlayerID(id)
{
    if (!Iter_Contains(Reports, id))
        return INVALID_PLAYER_ID;

    return ReportData[id][rPlayerID];
}

stock Report_GetType(id)
{
    if (!Iter_Contains(Reports, id))
        return REPORT_TYPE_NONE;

    return ReportData[id][rType];
}

stock Report_GetMessage(id, message[], len)
{
    if (!Iter_Contains(Reports, id))
        return 0;

    format(message, len, "%s", ReportData[id][rMessage]);
    return 1;
}

stock Report_GetPlayerName(id, name[], len)
{
    if (!Iter_Contains(Reports, id))
        return 0;

    format(name, len, "%s", ReportData[id][rPlayerName]);
    return 1;
}

stock Report_GetTimestamp(id)
{
    if (!Iter_Contains(Reports, id))
        return 0;

    return ReportData[id][rTimestamp];
}

stock Report_GetCount()
{
    return Iter_Count(Reports);
}

stock Report_Clear()
{
    foreach(new i : Reports)
    {
        Report_Remove(i);
    }
    return 1;
}
