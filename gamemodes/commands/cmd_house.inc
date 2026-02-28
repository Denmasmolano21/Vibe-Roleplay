/*
 *  Vibe Roleplay - House Commands
 *  File: commands/cmd_house.inc
 */

#if defined _cmd_house_included
    #endinput
#endif
#define _cmd_house_included

CMD:house(playerid, params[])
{
    GUARD_READY(playerid);

    new houseid = -1;
    new Float:minDist = 3.0;
    
    foreach(new i : Houses)
    {
        new Float:dist = GetPlayerDistanceFromPoint(playerid, 
            HouseData[i][hEntranceX], HouseData[i][hEntranceY], HouseData[i][hEntranceZ]);
        
        if (dist < minDist)
        {
            houseid = i;
            minDist = dist;
        }
    }
    
    if (houseid == -1)
    {
        SendErrorMessage(playerid, "Kamu tidak berada di dekat rumah manapun.");
        return 1;
    }
    
    House_ShowMenu(playerid, houseid);
    return 1;
}

CMD:exit(playerid, params[])
{
    GUARD_READY(playerid);
    House_Exit(playerid);
    return 1;
}

