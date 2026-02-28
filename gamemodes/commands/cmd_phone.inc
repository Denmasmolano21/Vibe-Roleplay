/*
 *  Vibe Roleplay - Phone Commands
 *  File: commands/cmd_phone.inc
 */

#if defined _cmd_phone_included
    #endinput
#endif
#define _cmd_phone_included

// PHONE COMMANDS - USER FRIENDLY INTERFACE

CMD:phone(playerid, params[])
{
    GUARD_READY(playerid);
    Phone_ShowMenu(playerid);
    return 1;
}

CMD:p(playerid, params[])
{
    GUARD_READY(playerid);
    Phone_ShowMenu(playerid);
    return 1;
}

CMD:call(playerid, params[])
{
    GUARD_READY(playerid);

    new number;
    if (sscanf(params, "i", number))
    {
        SendErrorMessage(playerid, "Penggunaan: /call [nomor]");
        return 1;
    }

    new targetid = INVALID_PLAYER_ID;
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && PlayerPhoneNumber[i] == number)
        {
            targetid = i;
            break;
        }
    }

    if (targetid == INVALID_PLAYER_ID)
    {
        SendErrorMessage(playerid, "Nomor tidak ditemukan.");
        return 1;
    }

    Phone_Call(playerid, targetid);
    return 1;
}

CMD:pickup(playerid, params[])
{
    GUARD_READY(playerid);

    new callerid = INVALID_PLAYER_ID;
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && PlayerInCall[i] == playerid)
        {
            callerid = i;
            break;
        }
    }

    if (callerid == INVALID_PLAYER_ID)
    {
        SendErrorMessage(playerid, "Tidak ada panggilan masuk.");
        return 1;
    }

    SendSuccessMessage(playerid, "Panggilan terhubung. Gunakan /h untuk menutup.");
    SendSuccessMessage(callerid, "Panggilan terhubung.");

    new msg[128];
    format(msg, sizeof(msg), "* %s mengangkat phone.", GetPlayerNameEx(playerid));
    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, msg);

    return 1;
}

CMD:hangup(playerid, params[])
{
    GUARD_READY(playerid);
    Phone_Hangup(playerid);
    return 1;
}

CMD:h(playerid, params[])
{
    GUARD_READY(playerid);
    Phone_Hangup(playerid);
    return 1;
}

CMD:sms(playerid, params[])
{
    GUARD_READY(playerid);

    new number, message[128];
    if (sscanf(params, "is[128]", number, message))
    {
        SendErrorMessage(playerid, "Penggunaan: /sms [nomor] [pesan]");
        return 1;
    }

    new targetid = INVALID_PLAYER_ID;
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && PlayerPhoneNumber[i] == number)
        {
            targetid = i;
            break;
        }
    }

    if (targetid == INVALID_PLAYER_ID)
    {
        SendErrorMessage(playerid, "Nomor tidak ditemukan.");
        return 1;
    }

    Phone_SendSMS(playerid, targetid, message);
    return 1;
}

