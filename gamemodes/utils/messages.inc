/*
 *  Vibe Roleplay - Message Utilities
 *  File: utils/messages.inc
 *
 *  Fungsi-fungsi untuk mengirim pesan terformat ke pemain.
 */

#if defined _messages_included
    #endinput
#endif
#define _messages_included

stock SendServerMessage(playerid, const message[])
{
    new string[256];
    format(string, sizeof(string), "{5B8CFF}[SERVER] {FFFFFF}%s", message);
    SendClientMessage(playerid, COLOR_WHITE, string);
    return 1;
}

stock SendErrorMessage(playerid, const message[])
{
    new string[256];
    format(string, sizeof(string), "{E74C3C}[!] {FFFFFF}%s", message);
    SendClientMessage(playerid, COLOR_WHITE, string);
    return 1;
}

stock SendSuccessMessage(playerid, const message[])
{
    new string[256];
    format(string, sizeof(string), "{4CAF50}[✓] {FFFFFF}%s", message);
    SendClientMessage(playerid, COLOR_WHITE, string);
    return 1;
}

stock SendInfoMessage(playerid, const message[])
{
    new string[256];
    format(string, sizeof(string), "{3498DB}[i] {FFFFFF}%s", message);
    SendClientMessage(playerid, COLOR_WHITE, string);
    return 1;
}

stock SendWarningMessage(playerid, const message[])
{
    new string[256];
    format(string, sizeof(string), "{F39C12}[!] {FFFFFF}%s", message);
    SendClientMessage(playerid, COLOR_WHITE, string);
    return 1;
}
