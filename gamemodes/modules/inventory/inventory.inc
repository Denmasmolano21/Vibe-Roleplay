/*
 *  Vibe Roleplay - Inventory System
 *  File: modules/inventory/inventory.inc
 */

#if defined _inventory_included
    #endinput
#endif
#define _inventory_included

#include <YSI_Coding/y_hooks>
#include <YSI_Data/y_iterate>

// INVENTORY CONFIGURATION

#define MAX_INVENTORY_SLOTS     20
#define MAX_ITEM_NAME          32
#define MAX_ITEM_TYPES         100

// Item Types
#define ITEM_TYPE_NONE         0
#define ITEM_TYPE_FOOD         1
#define ITEM_TYPE_DRINK        2
#define ITEM_TYPE_WEAPON       3
#define ITEM_TYPE_TOOL         4
#define ITEM_TYPE_MATERIAL     5
#define ITEM_TYPE_PHONE        6
#define ITEM_TYPE_KEY          7
#define ITEM_TYPE_MISC         8

// INVENTORY DATA STRUCTURES

enum E_ITEM_DATA
{
    itemID,
    itemName[MAX_ITEM_NAME],
    itemType,
    itemValue,
    bool:itemStackable,
    itemMaxStack
}

new ItemData[][E_ITEM_DATA] = {
    {0, "None", ITEM_TYPE_NONE, 0, false, 1},
    {1, "Burger", ITEM_TYPE_FOOD, 50, true, 10},
    {2, "Pizza", ITEM_TYPE_FOOD, 75, true, 10},
    {3, "Hotdog", ITEM_TYPE_FOOD, 30, true, 10},
    {4, "Water Bottle", ITEM_TYPE_DRINK, 40, true, 10},
    {5, "Soda", ITEM_TYPE_DRINK, 25, true, 10},
    {6, "Energy Drink", ITEM_TYPE_DRINK, 50, true, 10},
    {7, "Phone", ITEM_TYPE_PHONE, 500, false, 1},
    {8, "Rope", ITEM_TYPE_TOOL, 100, true, 5},
    {9, "Lockpick", ITEM_TYPE_TOOL, 250, true, 3},
    {10, "Medkit", ITEM_TYPE_MISC, 500, true, 5}
};

enum E_INVENTORY_SLOT
{
    invItemID,
    invAmount
}

new PlayerInventory[MAX_PLAYERS][MAX_INVENTORY_SLOTS][E_INVENTORY_SLOT];
new SelectedInventorySlot[MAX_PLAYERS];

// INVENTORY FUNCTIONS

stock Inventory_Reset(playerid)
{
    for (new i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        PlayerInventory[playerid][i][invItemID] = 0;
        PlayerInventory[playerid][i][invAmount] = 0;
    }
    SelectedInventorySlot[playerid] = -1;
    return 1;
}

stock Inventory_AddItem(playerid, itemid, amount = 1)
{
    if (itemid <= 0 || itemid >= sizeof(ItemData))
        return 0;

    // Check if item is stackable
    if (ItemData[itemid][itemStackable])
    {
        // Find existing stack
        for (new i = 0; i < MAX_INVENTORY_SLOTS; i++)
        {
            if (PlayerInventory[playerid][i][invItemID] == itemid)
            {
                new newAmount = PlayerInventory[playerid][i][invAmount] + amount;
                if (newAmount <= ItemData[itemid][itemMaxStack])
                {
                    PlayerInventory[playerid][i][invAmount] = newAmount;
                    return 1;
                }
            }
        }
    }

    // Find empty slot
    for (new i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if (PlayerInventory[playerid][i][invItemID] == 0)
        {
            PlayerInventory[playerid][i][invItemID] = itemid;
            PlayerInventory[playerid][i][invAmount] = amount;
            return 1;
        }
    }

    return 0; // Inventory full
}

stock Inventory_RemoveItem(playerid, itemid, amount = 1)
{
    for (new i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if (PlayerInventory[playerid][i][invItemID] == itemid)
        {
            if (PlayerInventory[playerid][i][invAmount] >= amount)
            {
                PlayerInventory[playerid][i][invAmount] -= amount;
                
                if (PlayerInventory[playerid][i][invAmount] <= 0)
                {
                    PlayerInventory[playerid][i][invItemID] = 0;
                    PlayerInventory[playerid][i][invAmount] = 0;
                }
                return 1;
            }
        }
    }
    return 0;
}

stock Inventory_HasItem(playerid, itemid, amount = 1)
{
    new totalAmount = 0;
    for (new i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if (PlayerInventory[playerid][i][invItemID] == itemid)
        {
            totalAmount += PlayerInventory[playerid][i][invAmount];
        }
    }
    return (totalAmount >= amount);
}

stock Inventory_GetItemCount(playerid, itemid)
{
    new totalAmount = 0;
    for (new i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if (PlayerInventory[playerid][i][invItemID] == itemid)
        {
            totalAmount += PlayerInventory[playerid][i][invAmount];
        }
    }
    return totalAmount;
}

stock Inventory_UseItem(playerid, slot)
{
    if (slot < 0 || slot >= MAX_INVENTORY_SLOTS)
        return 0;

    new itemid = PlayerInventory[playerid][slot][invItemID];
    if (itemid == 0)
        return 0;

    new type = ItemData[itemid][itemType];
    
    switch (type)
    {
        case ITEM_TYPE_FOOD:
        {
            Stats_AddHunger(playerid, ItemData[itemid][itemValue]);
            Inventory_RemoveItem(playerid, itemid, 1);
            
            new msg[128];
            format(msg, sizeof(msg), "* %s memakan %s.", GetPlayerNameEx(playerid), ItemData[itemid][itemName]);
            SendNearbyMessage(playerid, 20.0, COLOR_ACTION, msg);
            return 1;
        }
        case ITEM_TYPE_DRINK:
        {
            Stats_AddThirst(playerid, ItemData[itemid][itemValue]);
            Inventory_RemoveItem(playerid, itemid, 1);
            
            new msg[128];
            format(msg, sizeof(msg), "* %s meminum %s.", GetPlayerNameEx(playerid), ItemData[itemid][itemName]);
            SendNearbyMessage(playerid, 20.0, COLOR_ACTION, msg);
            return 1;
        }
        case ITEM_TYPE_PHONE:
        {
            Phone_ShowMenu(playerid);
            return 1;
        }
    }
    
    SendErrorMessage(playerid, "Item ini tidak bisa digunakan.");
    return 0;
}

stock Inventory_ShowMenu(playerid)
{
    new caption[64];
    format(caption, sizeof(caption), "%s - Inventory", SERVER_NAME);

    new info[2048];
    format(info, sizeof(info), "{00D4FF}Slot\t{00D4FF}Item\t{00D4FF}Amount\n");

    new count = 0;
    for (new i = 0; i < MAX_INVENTORY_SLOTS; i++)
    {
        if (PlayerInventory[playerid][i][invItemID] > 0)
        {
            new itemid = PlayerInventory[playerid][i][invItemID];
            format(info, sizeof(info), "%s{FFFFFF}%d\t{AFAFAF}%s\t{FFFFFF}x%d\n",
                info, i + 1, ItemData[itemid][itemName], PlayerInventory[playerid][i][invAmount]);
            count++;
        }
        else
        {
            format(info, sizeof(info), "%s{666666}%d\t{666666}Empty\t{666666}-\n", info, i + 1);
        }
    }

    if (count == 0)
    {
        format(info, sizeof(info), "{FFFFFF}Inventory kamu kosong.\n\n{AFAFAF}Kamu bisa mendapatkan item dari:\n- Toko\n- Job\n- Player lain");
    }

    ShowPlayerDialog(playerid, DIALOG_INVENTORY_MAIN, DIALOG_STYLE_TABLIST_HEADERS,
        caption, info, "Use", "Tutup");
    return 1;
}

// HOOKS

hook OnPlayerConnect(playerid)
{
    Inventory_Reset(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    // TODO: Save inventory to database
    Inventory_Reset(playerid);
    return 1;
}

