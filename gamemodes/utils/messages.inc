/*
 *  Vibe Roleplay - Message Utilities
 *  File: utils/messages.inc
 */

#if defined _messages_included
    #endinput
#endif
#define _messages_included

#define MAX_MSG_LENGTH          256
#define MAX_CHAT_LENGTH         144

stock SendServerMessage(playerid, const message[])
{
    if (!IsPlayerConnected(playerid))
        return 0;
    
    if (isnull(message))
        return 0;

    new string[MAX_MSG_LENGTH];
    format(string, sizeof(string), "%s[SERVER]: %s%s", EC_PRIMARY, EC_WHITE, message);
    SendClientMessage(playerid, COLOR_WHITE, string);
    return 1;
}

stock SendErrorMessage(playerid, const message[])
{
    if (!IsPlayerConnected(playerid))
        return 0;
    
    if (isnull(message))
        return 0;

    new string[MAX_MSG_LENGTH];
    format(string, sizeof(string), "%s[ERROR]: %s%s", EC_ERROR, EC_WHITE, message);
    SendClientMessage(playerid, COLOR_WHITE, string);
    return 1;
}

stock SendSuccessMessage(playerid, const message[])
{
    if (!IsPlayerConnected(playerid))
        return 0;
    
    if (isnull(message))
        return 0;

    new string[MAX_MSG_LENGTH];
    format(string, sizeof(string), "%s[SUCCESS]: %s%s", EC_SUCCESS, EC_WHITE, message);
    SendClientMessage(playerid, COLOR_WHITE, string);
    return 1;
}

stock SendInfoMessage(playerid, const message[])
{
    if (!IsPlayerConnected(playerid))
        return 0;
    
    if (isnull(message))
        return 0;

    new string[MAX_MSG_LENGTH];
    format(string, sizeof(string), "%s[INFO]: %s%s", EC_INFO, EC_WHITE, message);
    SendClientMessage(playerid, COLOR_WHITE, string);
    return 1;
}

stock SendWarningMessage(playerid, const message[])
{
    if (!IsPlayerConnected(playerid))
        return 0;
    
    if (isnull(message))
        return 0;

    new string[MAX_MSG_LENGTH];
    format(string, sizeof(string), "%s[WARNING]: %s%s", EC_WARNING, EC_WHITE, message);
    SendClientMessage(playerid, COLOR_WHITE, string);
    return 1;
}

stock SendActionMessage(playerid, const message[])
{
    if (!IsPlayerConnected(playerid))
        return 0;
    
    if (isnull(message))
        return 0;

    new string[MAX_MSG_LENGTH];
    format(string, sizeof(string), "%s* %s%s", EC_ACTION, EC_WHITE, message);
    SendClientMessage(playerid, COLOR_ACTION, string);
    return 1;
}

stock BroadcastServerMessage(const message[])
{
    if (isnull(message))
        return 0;

    new string[MAX_MSG_LENGTH];
    format(string, sizeof(string), "%s[SERVER]: %s%s", EC_PRIMARY, EC_WHITE, message);
    
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i))
            SendClientMessage(i, COLOR_WHITE, string);
    }
    return 1;
}

stock BroadcastMessage(const color[], const message[])
{
    if (isnull(message))
        return 0;

    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i))
            SendClientMessage(i, COLOR_WHITE, message);
    }
    return 1;
}
