// utils/string.pwn — Helper string murni
// Tidak ada state global, tidak ada dependency ke modul lain.

#if defined _UTIL_STRING_PWN
    #endinput
#endif
#define _UTIL_STRING_PWN

// Ubah underscore jadi spasi: "John_Doe" → "John Doe"
stock Util_NameToDisplay(const name[], out[], len = sizeof(out)) {
    strmid(out, name, 0, strlen(name), len);
    for (new i = 0; out[i]; i++)
        if (out[i] == '_') out[i] = ' ';
}

// Format uang dengan koma: 1500000 → "1,500,000"
stock Util_FormatMoney(amount, out[], len = sizeof(out)) {
    new tmp[16], neg = (amount < 0);
    if (neg) amount = -amount;

    format(tmp, sizeof(tmp), "%d", amount);
    new tlen = strlen(tmp), olen = 0;
    new buf[16];

    for (new i = 0; i < tlen; i++) {
        if (i > 0 && (tlen - i) % 3 == 0)
            buf[olen++] = ',';
        buf[olen++] = tmp[i];
    }
    buf[olen] = EOS;

    if (neg) format(out, len, "-%s", buf);
    else     strmid(out, buf, 0, olen, len);
}

// Cek apakah string hanya spasi/kosong
stock bool:Util_IsEmpty(const str[]) {
    for (new i = 0; str[i]; i++)
        if (str[i] > ' ') return false;
    return true;
}

// Cek apakah string hanya angka
stock bool:Util_IsNumeric(const s[]) {
    if (!s[0]) return false;
    for (new i = 0; s[i]; i++)
        if (s[i] < '0' || s[i] > '9') return false;
    return true;
}

// Truncate string dengan "..." jika melebihi maxlen
stock Util_Truncate(const str[], out[], maxlen, len = sizeof(out)) {
    if (strlen(str) <= maxlen) {
        strmid(out, str, 0, strlen(str), len);
    } else {
        strmid(out, str, 0, maxlen - 3, len);
        strcat(out, "...", len);
    }
}
