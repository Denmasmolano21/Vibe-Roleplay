/*
 *  Vibe Roleplay - Business Commands
 *  File: commands/cmd_business.inc
 */

#if defined _cmd_business_included
    #endinput
#endif
#define _cmd_business_included

CMD:business(playerid, params[])
{
    GUARD_READY(playerid);

    new businessid = -1;
    new Float:minDist = 3.0;
    
    foreach(new i : Businesses)
    {
        new Float:dist = GetPlayerDistanceFromPoint(playerid, 
            BusinessData[i][bEntranceX], BusinessData[i][bEntranceY], BusinessData[i][bEntranceZ]);
        
        if (dist < minDist)
        {
            businessid = i;
            minDist = dist;
        }
    }
    
    if (businessid == -1)
    {
        SendErrorMessage(playerid, "Kamu tidak berada di dekat bisnis manapun.");
        return 1;
    }
    
    Business_ShowMenu(playerid, businessid);
    return 1;
}

CMD:biz(playerid, params[])
{
    GUARD_READY(playerid);

    new businessid = -1;
    new Float:minDist = 3.0;
    
    foreach(new i : Businesses)
    {
        new Float:dist = GetPlayerDistanceFromPoint(playerid, 
            BusinessData[i][bEntranceX], BusinessData[i][bEntranceY], BusinessData[i][bEntranceZ]);
        
        if (dist < minDist)
        {
            businessid = i;
            minDist = dist;
        }
    }
    
    if (businessid == -1)
    {
        SendErrorMessage(playerid, "Kamu tidak berada di dekat bisnis manapun.");
        return 1;
    }
    
    Business_ShowMenu(playerid, businessid);
    return 1;
}

