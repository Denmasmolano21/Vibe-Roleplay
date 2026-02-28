/*
 *  Vibe Roleplay - Business System
 *  File: modules/business/business.inc
 */

#if defined _business_included
    #endinput
#endif
#define _business_included

#include <YSI_Coding/y_hooks>
#include <YSI_Data/y_iterate>

#define MAX_BUSINESSES      100
#define MAX_BUSINESS_NAME   64

enum E_BUSINESS_TYPE
{
    BUSINESS_TYPE_NONE,
    BUSINESS_TYPE_247,
    BUSINESS_TYPE_RESTAURANT,
    BUSINESS_TYPE_GAS_STATION,
    BUSINESS_TYPE_CLOTHING,
    BUSINESS_TYPE_GUN_SHOP
}

enum E_BUSINESS_DATA
{
    bID,
    bType,
    bName[MAX_BUSINESS_NAME],
    bOwnerID,
    bOwnerName[MAX_PLAYER_NAME],
    Float:bEntranceX,
    Float:bEntranceY,
    Float:bEntranceZ,
    bPrice,
    bSafe,
    bool:bForSale,
    bPickupID,
    Text3D:bLabel
}

new BusinessData[MAX_BUSINESSES][E_BUSINESS_DATA];
new Iterator:Businesses<MAX_BUSINESSES>;

stock Business_Create(type, const name[], Float:x, Float:y, Float:z, price)
{
    new id = Iter_Free(Businesses);
    if (id == -1) return -1;

    BusinessData[id][bID] = id;
    BusinessData[id][bType] = _:type;
    format(BusinessData[id][bName], MAX_BUSINESS_NAME, "%s", name);
    BusinessData[id][bOwnerID] = 0;
    BusinessData[id][bEntranceX] = x;
    BusinessData[id][bEntranceY] = y;
    BusinessData[id][bEntranceZ] = z;
    BusinessData[id][bPrice] = price;
    BusinessData[id][bSafe] = 0;
    BusinessData[id][bForSale] = true;

    BusinessData[id][bPickupID] = CreateDynamicPickup(1274, 1, x, y, z, 0, 0);

    new labelText[256];
    format(labelText, sizeof(labelText), \
        "{00D4FF}%s\n" \
        "{00FF00}For Sale\n" \
        "{FFFFFF}Price: {00FF00}$%d\n" \
        "{AFAFAF}/business untuk info",
        name, price
    );
    BusinessData[id][bLabel] = CreateDynamic3DTextLabel(labelText, COLOR_WHITE, x, y, z + 0.5, 10.0);

    Iter_Add(Businesses, id);
    return id;
}

stock Business_ShowMenu(playerid, businessid)
{
    new caption[64];
    format(caption, sizeof(caption), "%s - Business", SERVER_NAME);

    new info[768];
    
    if (BusinessData[businessid][bForSale])
    {
        format(info, sizeof(info), \
            "{FFFFFF}Business: {00D4FF}%s\n" \
            "{FFFFFF}Status: {00FF00}For Sale\n" \
            "{FFFFFF}Price: {00FF00}$%d\n\n" \
            "{00D4FF}Buy Business\t{FFFFFF}Beli bisnis\n" \
            "{00D4FF}Enter\t\t{FFFFFF}Masuk bisnis",
            BusinessData[businessid][bName], BusinessData[businessid][bPrice]
        );
    }
    else if (BusinessData[businessid][bOwnerID] == PlayerData[playerid][pID])
    {
        format(info, sizeof(info), \
            "{FFFFFF}Business: {00D4FF}%s\n" \
            "{FFFFFF}Owner: {00D4FF}%s\n" \
            "{FFFFFF}Safe: {00FF00}$%d\n\n" \
            "{00D4FF}Enter\t\t{FFFFFF}Masuk bisnis\n" \
            "{00D4FF}Withdraw\t{FFFFFF}Ambil uang dari safe\n" \
            "{00D4FF}Sell Business\t{FFFFFF}Jual bisnis\n" \
            "{00D4FF}Manage\t\t{FFFFFF}Kelola bisnis",
            BusinessData[businessid][bName], BusinessData[businessid][bOwnerName],
            BusinessData[businessid][bSafe]
        );
    }
    else
    {
        format(info, sizeof(info), \
            "{FFFFFF}Business: {00D4FF}%s\n" \
            "{FFFFFF}Owner: {00D4FF}%s\n\n" \
            "{00D4FF}Enter\t\t{FFFFFF}Masuk bisnis",
            BusinessData[businessid][bName], BusinessData[businessid][bOwnerName]
        );
    }

    ShowPlayerDialog(playerid, DIALOG_BUSINESS_MENU, DIALOG_STYLE_TABLIST,
        caption, info, "Pilih", "Tutup");
    return 1;
}

hook OnGameModeInit()
{
    Business_Create(_:BUSINESS_TYPE_247, "24/7 Store", 1352.3, -1759.2, 13.5, 100000);
    Business_Create(_:BUSINESS_TYPE_RESTAURANT, "Burger Shot", 1199.2, -918.0, 43.1, 150000);
    
    printf("[BUSINESS] Business system loaded. Total: %d", Iter_Count(Businesses));
    return 1;
}

