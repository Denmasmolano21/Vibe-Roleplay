// validator.pwn — Validasi semua input user
// Depends on: core/config.pwn

#if defined _UTIL_VALIDATOR_PWN
    #endinput
#endif
#define _UTIL_VALIDATOR_PWN

// ─── Reason codes ─────────────────────────────────────────────────────────────
#define PASS_OK             (0)
#define PASS_ERR_EMPTY      (1)
#define PASS_ERR_SHORT      (2)
#define PASS_ERR_LONG       (3)
#define PASS_ERR_CHAR       (4)

// ─── Validasi password — return true jika valid ───────────────────────────────
stock bool:Util_ValidatePass(const pass[], &reason) {
    new len = strlen(pass);

    if (len == 0)            { reason = PASS_ERR_EMPTY; return false; }
    if (len < MIN_PASS_LEN)  { reason = PASS_ERR_SHORT; return false; }
    if (len > MAX_PASS_LEN)  { reason = PASS_ERR_LONG;  return false; }

    // Whitelist karakter: huruf, angka, simbol umum
    for (new i = 0; i < len; i++) {
        new c = pass[i];
        if (!( (c >= 'A' && c <= 'Z') ||
               (c >= 'a' && c <= 'z') ||
               (c >= '0' && c <= '9') ||
                c == '!' || c == '@' || c == '#' || c == '$' ||
                c == '%' || c == '_' || c == '-' || c == '.' )) {
            reason = PASS_ERR_CHAR;
            return false;
        }
    }
    reason = PASS_OK;
    return true;
}

// Shortcut tanpa reason detail
stock bool:Util_ValidPass(const pass[]) {
    new r;
    return Util_ValidatePass(pass, r);
}

// Tulis pesan error ke buffer — pakai embed warna dialog
stock Util_PassError(reason, out[], len = sizeof(out)) {
    switch (reason) {
        case PASS_ERR_EMPTY: format(out, len,
            "{FF6B6B}╳  Password tidak boleh kosong!");
        case PASS_ERR_SHORT: format(out, len,
            "{FF6B6B}╳  Password terlalu pendek! {AAAAAA}(min. %d karakter)", MIN_PASS_LEN);
        case PASS_ERR_LONG:  format(out, len,
            "{FF6B6B}╳  Password terlalu panjang! {AAAAAA}(maks. %d karakter)", MAX_PASS_LEN);
        case PASS_ERR_CHAR:  format(out, len,
            "{FF6B6B}╳  Karakter tidak diizinkan!\n"\
            "{888888}   Gunakan: huruf · angka · !@#$%%_-.");
        default: format(out, len, "{FF6B6B}╳  Password tidak valid.");
    }
}


// // ─── Cek string hanya angka ───────────────────────────────────────────────────
// stock bool:Util_IsNumeric(const s[]) {
//     if (!s[0]) return false;
//     for (new i = 0; s[i]; i++)
//         if (s[i] < '0' || s[i] > '9') return false;
//     return true;
// }

// ─── Nama player valid ────────────────────────────────────────────────────────
stock bool:Util_ValidName(const name[]) {
    new len = strlen(name);
    if (len < 3 || len > MAX_PLAYER_NAME) return false;
    for (new i = 0; i < len; i++) {
        new c = name[i];
        if (!( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
               (c >= '0' && c <= '9') ||  c == '_' ))
            return false;
    }
    return true;
}
