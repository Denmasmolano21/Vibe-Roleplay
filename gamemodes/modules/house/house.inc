/*
 *  Vibe Roleplay - House System
 *  File: modules/house/house.inc
 */

#if defined _house_included
    #endinput
#endif
#define _house_included

#include <YSI_Coding/y_hooks>
#include <YSI_Data/y_iterate>

// HOUSE CONFIGURATION

#define MAX_HOUSES          500
#define MAX_HOUSE_STORAGE   50

// HOUSE DATA STRUCTURES

enum E_HOUSE_DATA
{
    hID,
    hOwnerID,
    hOwnerName[MAX_PLAYER_NAME],
    Float:hEntranceX,
    Float:hEntranceY,
    Float:hEntranceZ,
    Float:hExitX,
    Float:hExitY,
    Float:hExitZ,
    hInterior,
    hVirtualWorld,
    hPrice,
    hRentPrice,
    bool:hLocked,
    bool:hForSale,
    hPickupID,
    Text3D:hLabel
}

new HouseData[MAX_HOUSES][E_HOUSE_DATA];
new Iterator:Houses<MAX_HOUSES>;
new PlayerInHouse[MAX_PLAYERS] = {-1, ...};

// HOUSE FUNCTIONS

stock House_Create(Float:x, Float:y, Float:z, interior, price)
{
    new id = Iter_Free(Houses);
    if (id == -1)
        return -1;

    HouseData[id][hID] = id;
    HouseData[id][hOwnerID] = 0;
    HouseData[id][hOwnerName][0] = EOS;
    HouseData[id][hEntranceX] = x;
    HouseData[id][hEntranceY] = y;
    HouseData[id][hEntranceZ] = z;
    HouseData[id][hInterior] = interior;
    HouseData[id][hVirtualWorld] = id + 1;
    HouseData[id][hPrice] = price;
    HouseData[id][hRentPrice] = price / 100;
    HouseData[id][hLocked] = false;
    HouseData[id][hForSale] = true;

    // Create pickup and label
    HouseData[id][hPickupID] = CreateDynamicPickup(1273, 1, x, y, z, 0, 0);

    new labelText[256];
    format(labelText, sizeof(labelText), \
        "{00D4FF}House ID: {FFFFFF}%d\n" \
        "{00D4FF}Status: {00FF00}For Sale\n" \
        "{00D4FF}Price: {00FF00}$%d\n" \
        "{AFAFAF}Tekan {FFFFFF}F {AFAFAF}atau ketik {FFFFFF}/house",
        id, price
    );
    HouseData[id][hLabel] = CreateDynamic3DTextLabel(labelText, COLOR_WHITE, x, y, z + 0.5, 10.0);

    Iter_Add(Houses, id);
    return id;
}

stock House_Buy(playerid, houseid)
{
    if (houseid < 0 || houseid >= MAX_HOUSES)
        return 0;

    if (!Iter_Contains(Houses, houseid))
        return 0;

    if (!HouseData[houseid][hForSale])
    {
        SendErrorMessage(playerid, "Rumah ini tidak dijual.");
        return 0;
    }

    if (VRP_GetPlayerMoney(playerid) < HouseData[houseid][hPrice])
    {
        SendErrorMessage(playerid, "Uang kamu tidak cukup.");
        return 0;
    }

    VRP_TakePlayerMoney(playerid, HouseData[houseid][hPrice]);
    
    HouseData[houseid][hOwnerID] = PlayerData[playerid][pID];
    GetPlayerName(playerid, HouseData[houseid][hOwnerName], MAX_PLAYER_NAME);
    HouseData[houseid][hForSale] = false;
    HouseData[houseid][hLocked] = true;

    // Update label
    new labelText[256];
    format(labelText, sizeof(labelText), \
        "{00D4FF}House ID: {FFFFFF}%d\n" \
        "{00D4FF}Owner: {FFFFFF}%s\n" \
        "{AFAFAF}Tekan {FFFFFF}F {AFAFAF}atau ketik {FFFFFF}/house",
        houseid, HouseData[houseid][hOwnerName]
    );
    UpdateDynamic3DTextLabelText(HouseData[houseid][hLabel], COLOR_WHITE, labelText);

    new msg[128];
    format(msg, sizeof(msg), "Selamat! Kamu membeli rumah ID %d seharga $%d", houseid, HouseData[houseid][hPrice]);
    SendSuccessMessage(playerid, msg);

    return 1;
}

stock House_Sell(playerid, houseid)
{
    if (houseid < 0 || houseid >= MAX_HOUSES)
        return 0;

    if (!Iter_Contains(Houses, houseid))
        return 0;

    if (HouseData[houseid][hOwnerID] != PlayerData[playerid][pID])
    {
        SendErrorMessage(playerid, "Ini bukan rumah kamu.");
        return 0;
    }

    new sellPrice = HouseData[houseid][hPrice] / 2;
    VRP_GivePlayerMoney(playerid, sellPrice);

    HouseData[houseid][hOwnerID] = 0;
    HouseData[houseid][hOwnerName][0] = EOS;
    HouseData[houseid][hForSale] = true;
    HouseData[houseid][hLocked] = false;

    // Update label
    new labelText[256];
    format(labelText, sizeof(labelText), \
        "{00D4FF}House ID: {FFFFFF}%d\n" \
        "{00D4FF}Status: {00FF00}For Sale\n" \
        "{00D4FF}Price: {00FF00}$%d\n" \
        "{AFAFAF}Tekan {FFFFFF}F {AFAFAF}atau ketik {FFFFFF}/house",
        houseid, HouseData[houseid][hPrice]
    );
    UpdateDynamic3DTextLabelText(HouseData[houseid][hLabel], COLOR_WHITE, labelText);

    new msg[128];
    format(msg, sizeof(msg), "Kamu menjual rumah ID %d seharga $%d", houseid, sellPrice);
    SendSuccessMessage(playerid, msg);

    return 1;
}

stock House_Enter(playerid, houseid)
{
    if (houseid < 0 || houseid >= MAX_HOUSES)
        return 0;

    if (!Iter_Contains(Houses, houseid))
        return 0;

    if (HouseData[houseid][hLocked] && HouseData[houseid][hOwnerID] != PlayerData[playerid][pID])
    {
        SendErrorMessage(playerid, "Rumah ini terkunci.");
        return 0;
    }

    SetPlayerPos(playerid, HouseData[houseid][hExitX], HouseData[houseid][hExitY], HouseData[houseid][hExitZ]);
    SetPlayerInterior(playerid, HouseData[houseid][hInterior]);
    SetPlayerVirtualWorld(playerid, HouseData[houseid][hVirtualWorld]);
    PlayerInHouse[playerid] = houseid;

    SendInfoMessage(playerid, "Gunakan /exit untuk keluar.");
    return 1;
}

stock House_Exit(playerid)
{
    new houseid = PlayerInHouse[playerid];
    if (houseid == -1)
    {
        SendErrorMessage(playerid, "Kamu tidak berada di dalam rumah.");
        return 0;
    }

    SetPlayerPos(playerid, HouseData[houseid][hEntranceX], HouseData[houseid][hEntranceY], HouseData[houseid][hEntranceZ]);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    PlayerInHouse[playerid] = -1;

    return 1;
}

stock House_ShowMenu(playerid, houseid)
{
    new caption[64];
    format(caption, sizeof(caption), "%s - House Menu", SERVER_NAME);

    new info[768];
    
    if (HouseData[houseid][hForSale])
    {
        format(info, sizeof(info), \
            "{FFFFFF}House ID: {00D4FF}%d\n" \
            "{FFFFFF}Status: {00FF00}For Sale\n" \
            "{FFFFFF}Price: {00FF00}$%d\n\n" \
            "{00D4FF}Buy House\t{FFFFFF}Beli rumah ini\n" \
            "{00D4FF}View Interior\t{FFFFFF}Lihat interior",
            houseid, HouseData[houseid][hPrice]
        );
    }
    else if (HouseData[houseid][hOwnerID] == PlayerData[playerid][pID])
    {
        format(info, sizeof(info), \
            "{FFFFFF}House ID: {00D4FF}%d\n" \
            "{FFFFFF}Owner: {00D4FF}%s\n\n" \
            "{00D4FF}Enter\t\t{FFFFFF}Masuk rumah\n" \
            "{00D4FF}Lock/Unlock\t{FFFFFF}Kunci/buka rumah\n" \
            "{00D4FF}Sell House\t{FFFFFF}Jual rumah\n" \
            "{00D4FF}Upgrade\t\t{FFFFFF}Upgrade rumah\n" \
            "{00D4FF}Storage\t\t{FFFFFF}Akses storage",
            houseid, HouseData[houseid][hOwnerName]
        );
    }
    else
    {
        format(info, sizeof(info), \
            "{FFFFFF}House ID: {00D4FF}%d\n" \
            "{FFFFFF}Owner: {00D4FF}%s\n" \
            "{FFFFFF}Status: {FF0000}Owned\n\n" \
            "{AFAFAF}Rumah ini sudah dimiliki.",
            houseid, HouseData[houseid][hOwnerName]
        );
    }

    ShowPlayerDialog(playerid, DIALOG_HOUSE_MENU, DIALOG_STYLE_TABLIST,
        caption, info, "Pilih", "Tutup");
    return 1;
}

// HOOKS

hook OnPlayerConnect(playerid)
{
    PlayerInHouse[playerid] = -1;
    return 1;
}

hook OnGameModeInit()
{
    // Example houses
    House_Create(2495.9, -1688.2, 13.8, 2, 50000);
    House_Create(2468.6, -1698.2, 13.5, 5, 75000);
    House_Create(2451.7, -1639.9, 13.6, 1, 45000);
    
    printf("[HOUSE] House system loaded. Total houses: %d", Iter_Count(Houses));
    return 1;
}

