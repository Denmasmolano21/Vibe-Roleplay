/*
 *  Vibe Roleplay - Faction Commands
 *  File: commands/cmd_faction.inc
 */

#if defined _cmd_faction_included
    #endinput
#endif
#define _cmd_faction_included

CMD:faction(playerid, params[])
{
    GUARD_READY(playerid);
    Faction_ShowMenu(playerid);
    return 1;
}

CMD:f(playerid, params[])
{
    GUARD_READY(playerid);

    if (PlayerFaction[playerid] == 0)
    {
        SendErrorMessage(playerid, "Kamu tidak bergabung dengan faction.");
        return 1;
    }

    if (isnull(params))
    {
        SendErrorMessage(playerid, "Penggunaan: /f [pesan]");
        return 1;
    }

    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    new msg[256];
    format(msg, sizeof(msg), "[FACTION] %s: %s", name, params);

    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && PlayerFaction[i] == PlayerFaction[playerid])
        {
            SendClientMessage(i, FactionData[PlayerFaction[playerid]][fColor], msg);
        }
    }

    return 1;
}

CMD:finvite(playerid, params[])
{
    GUARD_READY(playerid);

    if (PlayerFaction[playerid] == 0)
    {
        SendErrorMessage(playerid, "Kamu tidak bergabung dengan faction.");
        return 1;
    }

    if (PlayerFactionRank[playerid] < 5)
    {
        SendErrorMessage(playerid, "Rank kamu tidak cukup untuk invite.");
        return 1;
    }

    new targetid;
    if (sscanf(params, "u", targetid))
    {
        SendErrorMessage(playerid, "Penggunaan: /finvite [playerid]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Pemain tidak ditemukan.");
        return 1;
    }

    Faction_Invite(playerid, targetid, PlayerFaction[playerid]);
    return 1;
}

