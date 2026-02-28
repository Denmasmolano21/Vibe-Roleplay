/*
 *  Vibe Roleplay - Faction System
 *  File: modules/faction/faction.inc
 */

#if defined _faction_included
    #endinput
#endif
#define _faction_included

#include <YSI_Coding/y_hooks>
#include <YSI_Data/y_iterate>

#define MAX_FACTIONS        20
#define MAX_FACTION_NAME    64
#define MAX_FACTION_MEMBERS 50
#define MAX_FACTION_RANKS   10

enum E_FACTION_TYPE
{
    FACTION_TYPE_NONE,
    FACTION_TYPE_POLICE,
    FACTION_TYPE_MEDIC,
    FACTION_TYPE_GOVERNMENT,
    FACTION_TYPE_GANG,
    FACTION_TYPE_MAFIA
}

enum E_FACTION_DATA
{
    fID,
    fType,
    fName[MAX_FACTION_NAME],
    fLeaderID,
    fLeaderName[MAX_PLAYER_NAME],
    fColor,
    Float:fHQX,
    Float:fHQY,
    Float:fHQZ,
    fPickupID,
    Text3D:fLabel
}

new FactionData[MAX_FACTIONS][E_FACTION_DATA];
new Iterator:Factions<MAX_FACTIONS>;
new PlayerFaction[MAX_PLAYERS];
new PlayerFactionRank[MAX_PLAYERS];

stock Faction_Create(type, const name[], color, Float:x, Float:y, Float:z)
{
    new id = Iter_Free(Factions);
    if (id == -1) return -1;

    FactionData[id][fID] = id;
    FactionData[id][fType] = type;
    format(FactionData[id][fName], MAX_FACTION_NAME, "%s", name);
    FactionData[id][fLeaderID] = 0;
    FactionData[id][fColor] = color;
    FactionData[id][fHQX] = x;
    FactionData[id][fHQY] = y;
    FactionData[id][fHQZ] = z;

    FactionData[id][fPickupID] = CreateDynamicPickup(1239, 1, x, y, z, 0, 0);

    new labelText[256];
    format(labelText, sizeof(labelText), \
        "{00D4FF}%s\n" \
        "{FFFFFF}Headquarters\n" \
        "{AFAFAF}/faction untuk info",
        name
    );
    FactionData[id][fLabel] = CreateDynamic3DTextLabel(labelText, color, x, y, z + 0.5, 10.0);

    Iter_Add(Factions, id);
    return id;
}

stock Faction_ShowMenu(playerid)
{
    new caption[64];
    format(caption, sizeof(caption), "%s - Faction Menu", SERVER_NAME);

    new info[1024];
    
    if (PlayerFaction[playerid] == 0)
    {
        format(info, sizeof(info), \
            "{FFFFFF}Kamu belum bergabung dengan faction.\n\n" \
            "{AFAFAF}Faction yang tersedia:\n\n"
        );
        
        foreach(new i : Factions)
        {
            format(info, sizeof(info), "%s{00D4FF}%s\n",
                info, FactionData[i][fName]
            );
        }
    }
    else
    {
        new factionid = PlayerFaction[playerid];
        
        format(info, sizeof(info), \
            "{FFFFFF}Faction: {00D4FF}%s\n" \
            "{FFFFFF}Rank: {00D4FF}%d\n\n" \
            "{00D4FF}Members\t\t{FFFFFF}Lihat anggota\n" \
            "{00D4FF}Invite\t\t{FFFFFF}Invite pemain\n" \
            "{00D4FF}Kick\t\t{FFFFFF}Kick anggota\n" \
            "{00D4FF}Ranks\t\t{FFFFFF}Kelola rank\n" \
            "{00D4FF}Leave\t\t{FFFFFF}Keluar faction",
            FactionData[factionid][fName], PlayerFactionRank[playerid]
        );
    }

    ShowPlayerDialog(playerid, DIALOG_FACTION_MENU, DIALOG_STYLE_TABLIST,
        caption, info, "Pilih", "Tutup");
    return 1;
}

stock Faction_Invite(playerid, targetid, factionid)
{
    if (factionid < 0 || factionid >= MAX_FACTIONS)
        return 0;

    if (!Iter_Contains(Factions, factionid))
        return 0;

    if (PlayerFaction[targetid] != 0)
    {
        SendErrorMessage(playerid, "Pemain sudah bergabung dengan faction lain.");
        return 0;
    }

    PlayerFaction[targetid] = factionid;
    PlayerFactionRank[targetid] = 1;

    new msg[128];
    format(msg, sizeof(msg), "Kamu diundang ke faction %s", FactionData[factionid][fName]);
    SendSuccessMessage(targetid, msg);

    format(msg, sizeof(msg), "Berhasil invite %s ke faction.", GetPlayerNameEx(targetid));
    SendSuccessMessage(playerid, msg);

    return 1;
}

hook OnPlayerConnect(playerid)
{
    PlayerFaction[playerid] = 0;
    PlayerFactionRank[playerid] = 0;
    return 1;
}

hook OnGameModeInit()
{
    Faction_Create(_:FACTION_TYPE_POLICE, "Los Santos Police Department", 0x3498DBFF, 1554.5, -1675.6, 16.2);
    Faction_Create(_:FACTION_TYPE_MEDIC, "Los Santos Medical Center", 0xE74C3CFF, 1172.0, -1323.0, 15.4);
    Faction_Create(_:FACTION_TYPE_GOVERNMENT, "San Andreas Government", 0xF39C12FF, 1481.0, -1772.0, 18.8);
    
    printf("[FACTION] Faction system loaded. Total: %d", Iter_Count(Factions));
    return 1;
}

