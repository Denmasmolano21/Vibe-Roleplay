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
//  /help — Lihat daftar command
// ============================================================================

CMD:help(playerid, params[])
{
    new caption[64];
    format(caption, sizeof(caption), "%s — Bantuan", SERVER_NAME);

    new info[512];
    format(info, sizeof(info), \
        EC_PRIMARY "Command Umum:\n" EC_WHITE \
        "/stats — Lihat statistik pemain\n" \
        "/mypos — Lihat posisi sekarang\n" \
        "/help — Tampilkan bantuan ini\n\n" \
        EC_PRIMARY "Catatan:\n" EC_WHITE \
        "Server ini menggunakan voice chat untuk komunikasi.\n" \
        "Chat teks dinonaktifkan."
    );

    ShowPlayerDialog(playerid, DIALOG_HELP, DIALOG_STYLE_MSGBOX,
        caption, info, "Tutup", "");
    return 1;
}

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
    FormatRPName(name, displayName, sizeof(displayName));

    new caption[64];
    format(caption, sizeof(caption), "%s — Statistik", SERVER_NAME);

    new info[512];
    format(info, sizeof(info), \
        EC_PRIMARY "Nama:\t\t" EC_WHITE "%s\n" \
        EC_PRIMARY "Level:\t\t" EC_WHITE "%d\n" \
        EC_PRIMARY "Uang:\t\t" EC_SUCCESS "$%d\n" \
        EC_PRIMARY "Hunger:\t\t" EC_WHITE "%d/%d\n" \
        EC_PRIMARY "Thirst:\t\t" EC_WHITE "%d/%d\n\n" \
        EC_PRIMARY "Playtime:\t" EC_WHITE "%d jam %d menit",
        displayName,
        PlayerData[playerid][pLevel],
        VRP_GetPlayerMoney(playerid),
        PlayerData[playerid][pHunger], MAX_HUNGER,
        PlayerData[playerid][pThirst], MAX_THIRST,
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
        EC_PRIMARY "X:\t\t" EC_WHITE "%.4f\n" \
        EC_PRIMARY "Y:\t\t" EC_WHITE "%.4f\n" \
        EC_PRIMARY "Z:\t\t" EC_WHITE "%.4f\n" \
        EC_PRIMARY "Angle:\t\t" EC_WHITE "%.4f\n\n" \
        EC_PRIMARY "Interior:\t" EC_WHITE "%d\n" \
        EC_PRIMARY "VW:\t\t" EC_WHITE "%d",
        x, y, z, a,
        GetPlayerInterior(playerid),
        GetPlayerVirtualWorld(playerid)
    );

    ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_MSGBOX,
        caption, info, "Tutup", "");
    return 1;
}

// ============================================================================
//  /eat — Makan (contoh command untuk testing hunger system)
// ============================================================================

CMD:eat(playerid, params[])
{
    GUARD_READY(playerid);

    // Cek apakah pemain di dekat tempat makan (bisa dikembangkan lebih lanjut)
    // Untuk sekarang, command ini langsung menambah hunger

    Stats_AddHunger(playerid, 20);
    SendSuccessMessage(playerid, "Kamu telah makan. Hunger +20");
    return 1;
}

// ============================================================================
//  /drink — Minum (contoh command untuk testing thirst system)
// ============================================================================

CMD:drink(playerid, params[])
{
    GUARD_READY(playerid);

    // Cek apakah pemain di dekat tempat minum (bisa dikembangkan lebih lanjut)
    // Untuk sekarang, command ini langsung menambah thirst

    Stats_AddThirst(playerid, 20);
    SendSuccessMessage(playerid, "Kamu telah minum. Thirst +20");
    return 1;
}

// ============================================================================
//  Admin Commands
// ============================================================================

// ============================================================================
//  /sethunger — Set hunger pemain (admin only)
// ============================================================================

CMD:sethunger(playerid, params[])
{
    GUARD_READY(playerid);
    GUARD_ADMIN(playerid);

    new targetid, amount;
    if (sscanf(params, "ui", targetid, amount))
    {
        SendErrorMessage(playerid, "Penggunaan: /sethunger [playerid] [amount]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Pemain tidak ditemukan.");
        return 1;
    }

    Stats_SetHunger(targetid, amount);
    
    new msg[128];
    format(msg, sizeof(msg), "Hunger %d diubah menjadi %d.", targetid, amount);
    SendSuccessMessage(playerid, msg);
    return 1;
}

// ============================================================================
//  /setthirst — Set thirst pemain (admin only)
// ============================================================================

CMD:setthirst(playerid, params[])
{
    GUARD_READY(playerid);
    GUARD_ADMIN(playerid);

    new targetid, amount;
    if (sscanf(params, "ui", targetid, amount))
    {
        SendErrorMessage(playerid, "Penggunaan: /setthirst [playerid] [amount]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Pemain tidak ditemukan.");
        return 1;
    }

    Stats_SetThirst(targetid, amount);
    
    new msg[128];
    format(msg, sizeof(msg), "Thirst %d diubah menjadi %d.", targetid, amount);
    SendSuccessMessage(playerid, msg);
    return 1;
}

// ============================================================================
//  /givemoney — Beri uang ke pemain (admin only)
// ============================================================================

CMD:givemoney(playerid, params[])
{
    GUARD_READY(playerid);
    GUARD_ADMIN(playerid);

    new targetid, amount;
    if (sscanf(params, "ui", targetid, amount))
    {
        SendErrorMessage(playerid, "Penggunaan: /givemoney [playerid] [amount]");
        return 1;
    }

    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Pemain tidak ditemukan.");
        return 1;
    }

    if (amount <= 0)
    {
        SendErrorMessage(playerid, "Jumlah uang harus positif.");
        return 1;
    }

    VRP_GivePlayerMoney(targetid, amount);
    
    new msg[128];
    format(msg, sizeof(msg), "Berhasil memberikan $%d kepada %d.", amount, targetid);
    SendSuccessMessage(playerid, msg);
    
    format(msg, sizeof(msg), "Admin memberikan kamu $%d.", amount);
    SendSuccessMessage(targetid, msg);
    
    return 1;
}
