// dialog_router.pwn — Central router untuk semua OnDialogResponse
// Depends on: query_builder.pwn, validator.pwn, session.pwn

#if defined _DIALOG_ROUTER_PWN
    #endinput
#endif
#define _DIALOG_ROUTER_PWN

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    switch (dialogid) {

        // ─────────────────────────────────────────────────────────────────────
        case DIALOG_LOGIN: {
            if (!response) {
                // Tekan "Keluar" atau ESC
                Player_Kick(playerid);
                return 1;
            }

            // Validasi: tidak boleh kosong
            if (Util_IsEmpty(inputtext)) {
                Dialog_ShowLogin(playerid, true,
                    MAX_LOGIN_TRIES - g_Player[playerid][p_Tries]);
                return 1;
            }

            // Kirim ke bcrypt verify → OnVerifyDone di session.pwn
            bcrypt_verify(playerid, "OnVerifyDone",
                inputtext, g_Player[playerid][p_Hash]);
            return 1;
        }

        // ─────────────────────────────────────────────────────────────────────
        case DIALOG_REGISTER: {
            if (!response) {
                Player_Kick(playerid);
                return 1;
            }

            // Validasi password
            new reason;
            if (!Util_ValidatePass(inputtext, reason)) {
                new errMsg[128];
                Util_PassError(reason, errMsg);
                Dialog_ShowRegister(playerid, errMsg);
                return 1;
            }

            // Simpan sementara — akan dicek saat konfirmasi
            strmid(g_Player[playerid][p_TempPass], inputtext,
                0, strlen(inputtext), MAX_PASS_LEN + 1);

            Dialog_ShowConfirm(playerid);
            return 1;
        }

        // ─────────────────────────────────────────────────────────────────────
        case DIALOG_REGISTER_CONFIRM: {
            if (!response) {
                // Tekan "Kembali" → balik ke dialog register
                // Bersihkan TempPass terlebih dahulu
                g_Player[playerid][p_TempPass][0] = EOS;
                Dialog_ShowRegister(playerid);
                return 1;
            }

            // Cek kecocokan dengan password sementara
            if (strcmp(inputtext, g_Player[playerid][p_TempPass]) != 0) {
                Dialog_ShowConfirm(playerid, true);
                return 1;
            }

            // Password cocok — hash dan daftarkan
            bcrypt_hash(playerid, "OnHashDone",
                g_Player[playerid][p_TempPass], BCRYPT_WORK);

            // Hapus password sementara dari memori segera setelah dikirim ke bcrypt
            g_Player[playerid][p_TempPass][0] = EOS;
            return 1;
        }
    }
    return 0;
}
