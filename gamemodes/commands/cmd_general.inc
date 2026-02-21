/*
 *  Vibe Roleplay - General Commands
 *  File: commands/cmd_general.inc
 *
 *  Command umum untuk semua pemain.
 *  Menggunakan Pawn.CMD dan GUARD macro.
 */

#if defined _cmd_general_included
    #endinput
#endif
#define _cmd_general_included

// ============================================================================
//  /stats — Lihat statistik pemain (dialog)
// ============================================================================

CMD:stats(playerid, params[])
{
    GUARD_READY(playerid);

    new totalPlaytime = GetPlayerTotalPlaytime(playerid);
    new hours = totalPlaytime / 60;
    new mins  = totalPlaytime % 60;

    new name[MAX_PLAYER_NAME], displayName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    format(displayName, sizeof(displayName), "%s", name);
    for (new i = 0; displayName[i] != EOS; i++)
    {
        if (displayName[i] == '_')
            displayName[i] = ' ';
    }

    new caption[64];
    format(caption, sizeof(caption), "%s — Statistik", SERVER_NAME);

    new info[512];
    format(info, sizeof(info), \
        EC_PRIMARY "Nama:\t\t" EC_WHITE "%s\n"\
        EC_PRIMARY "Level:\t\t" EC_WHITE "%d\n"\
        EC_PRIMARY "Uang:\t\t" EC_SUCCESS "$%d\n\n"\
        EC_PRIMARY "Playtime:\t" EC_WHITE "%d jam %d menit",
        displayName,
        PlayerData[playerid][pLevel],
        VRP_GetPlayerMoney(playerid),
        hours, mins
    );

    ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_MSGBOX,
        caption, info, "Tutup", "");
    return 1;
}

// ============================================================================
//  /mypos — Lihat posisi sekarang (debug/admin)
// ============================================================================

CMD:mypos(playerid, params[])
{
    GUARD_READY(playerid);

    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    new caption[64];
    format(caption, sizeof(caption), "%s — Posisi", SERVER_NAME);

    new info[256];
    format(info, sizeof(info), \
        EC_PRIMARY "X:\t\t" EC_WHITE "%.4f\n"\
        EC_PRIMARY "Y:\t\t" EC_WHITE "%.4f\n"\
        EC_PRIMARY "Z:\t\t" EC_WHITE "%.4f\n"\
        EC_PRIMARY "Angle:\t\t" EC_WHITE "%.4f\n\n"\
        EC_PRIMARY "Interior:\t" EC_WHITE "%d\n"\
        EC_PRIMARY "VW:\t\t" EC_WHITE "%d",
        x, y, z, a,
        GetPlayerInterior(playerid),
        GetPlayerVirtualWorld(playerid)
    );

    ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_MSGBOX,
        caption, info, "Tutup", "");
    return 1;
}
