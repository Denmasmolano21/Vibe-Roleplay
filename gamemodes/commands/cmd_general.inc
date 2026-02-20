/*
 *  Vibe Roleplay - General Commands
 *  File: commands/cmd_general.inc
 *
 *  Command umum untuk pemain.
 *  Menggunakan Pawn.CMD (cmd:command_name).
 *
 *  Placeholder untuk Phase 2+
 */

#if defined _cmd_general_included
    #endinput
#endif
#define _cmd_general_included

// ============================================================================
//  Contoh struktur command menggunakan Pawn.CMD
// ============================================================================

/*
    Cara menambahkan command baru:

    cmd:contoh(playerid, params[])
    {
        if (!PlayerData[playerid][pLoggedIn])
            return SendErrorMessage(playerid, "Kamu harus login terlebih dahulu.");

        // Logic command di sini...
        return 1;
    }
*/
