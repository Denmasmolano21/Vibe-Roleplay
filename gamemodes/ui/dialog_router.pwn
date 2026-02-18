// dialog_router.pwn — Central router OnDialogResponse
// Depends on: query_builder.pwn, validator.pwn, session.pwn

#if defined _DIALOG_ROUTER_PWN
    #endinput
#endif
#define _DIALOG_ROUTER_PWN

// TempPass disimpan di sini — static array per player.
// Tidak perlu ada di E_PLAYER karena hanya hidup selama proses register
// (antara DIALOG_REGISTER dan DIALOG_REGISTER_CONFIRM).
static s_TempPass[MAX_PLAYERS][MAX_PASS_LEN + 1];

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    switch (dialogid) {

        // ─────────────────────────────────────────────────────────────────────
        case DIALOG_LOGIN: {
            if (!response) { Player_Kick(playerid); return 1; }

            if (Util_IsEmpty(inputtext)) {
                Dialog_ShowLogin(playerid, true,
                    MAX_LOGIN_TRIES - g_Player[playerid][p_Tries]);
                return 1;
            }

            bcrypt_verify(playerid, "OnVerifyDone",
                inputtext, g_Player[playerid][p_Hash]);
            return 1;
        }

        // ─────────────────────────────────────────────────────────────────────
        case DIALOG_REGISTER: {
            if (!response) { Player_Kick(playerid); return 1; }

            new reason;
            if (!Util_ValidatePass(inputtext, reason)) {
                new errMsg[128];
                Util_PassError(reason, errMsg);
                Dialog_ShowRegister(playerid, errMsg);
                return 1;
            }

            // Simpan sementara ke static array — bukan di struct player
            strmid(s_TempPass[playerid], inputtext,
                0, strlen(inputtext), MAX_PASS_LEN + 1);

            Dialog_ShowConfirm(playerid);
            return 1;
        }

        // ─────────────────────────────────────────────────────────────────────
        case DIALOG_REGISTER_CONFIRM: {
            if (!response) {
                // Bersihkan temp pass, kembali ke step 1
                s_TempPass[playerid][0] = EOS;
                Dialog_ShowRegister(playerid);
                return 1;
            }

            if (strcmp(inputtext, s_TempPass[playerid]) != 0) {
                Dialog_ShowConfirm(playerid, true);
                return 1;
            }

            // Hash dan register
            bcrypt_hash(playerid, "OnHashDone",
                s_TempPass[playerid], BCRYPT_WORK);

            // Hapus dari memori segera setelah dikirim ke bcrypt
            s_TempPass[playerid][0] = EOS;
            return 1;
        }
    }
    return 0;
}
