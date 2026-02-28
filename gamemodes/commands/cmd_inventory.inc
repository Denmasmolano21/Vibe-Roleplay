/*
 *  Vibe Roleplay - Inventory Commands
 *  File: commands/cmd_inventory.inc
 */

#if defined _cmd_inventory_included
    #endinput
#endif
#define _cmd_inventory_included

// INVENTORY COMMANDS - USER FRIENDLY INTERFACE

CMD:inv(playerid, params[])
{
    GUARD_READY(playerid);
    Inventory_ShowMenu(playerid);
    return 1;
}

CMD:inventory(playerid, params[])
{
    GUARD_READY(playerid);
    Inventory_ShowMenu(playerid);
    return 1;
}

CMD:i(playerid, params[])
{
    GUARD_READY(playerid);
    Inventory_ShowMenu(playerid);
    return 1;
}

CMD:giveitem(playerid, params[])
{
    GUARD_READY(playerid);

    new targetid, itemid, amount;
    if (sscanf(params, "uii", targetid, itemid, amount))
    {
        SendErrorMessage(playerid, "Penggunaan: /giveitem [playerid] [itemid] [amount]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Pemain tidak ditemukan.");
        return 1;
    }

    if (!IsPlayerInRangeOfPlayer(playerid, targetid, 3.0))
    {
        SendErrorMessage(playerid, "Pemain terlalu jauh.");
        return 1;
    }

    if (!Inventory_HasItem(playerid, itemid, amount))
    {
        SendErrorMessage(playerid, "Kamu tidak memiliki item tersebut.");
        return 1;
    }

    if (!Inventory_AddItem(targetid, itemid, amount))
    {
        SendErrorMessage(playerid, "Inventory pemain penuh.");
        return 1;
    }

    Inventory_RemoveItem(playerid, itemid, amount);

    new msg[128], targetName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    
    format(msg, sizeof(msg), "* %s memberikan %s kepada %s.", 
        GetPlayerNameEx(playerid), ItemData[itemid][itemName], targetName);
    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, msg);
    
    return 1;
}

CMD:dropitem(playerid, params[])
{
    GUARD_READY(playerid);

    new itemid, amount;
    if (sscanf(params, "ii", itemid, amount))
    {
        SendErrorMessage(playerid, "Penggunaan: /dropitem [itemid] [amount]");
        return 1;
    }

    if (!Inventory_HasItem(playerid, itemid, amount))
    {
        SendErrorMessage(playerid, "Kamu tidak memiliki item tersebut.");
        return 1;
    }

    Inventory_RemoveItem(playerid, itemid, amount);

    new msg[128];
    format(msg, sizeof(msg), "* %s membuang %s.", GetPlayerNameEx(playerid), ItemData[itemid][itemName]);
    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, msg);
    
    SendSuccessMessage(playerid, "Item berhasil dibuang.");
    return 1;
}

