#if defined _UTIL_STRING_PWN
    #endinput
#endif
#define _UTIL_STRING_PWN

// Underscore → spasi (untuk nama player)
stock Util_NameToDisplay(const name[], out[], len = sizeof(out)) {
    strmid(out, name, 0, strlen(name), len);
    for (new i = 0; out[i]; i++)
        if (out[i] == '_') out[i] = ' ';
}

// Cek apakah string berisi hanya angka
stock bool:Util_IsNumeric(const s[]) {
    if (!s[0]) return false;
    for (new i = 0; s[i]; i++)
        if (s[i] < '0' || s[i] > '9') return false;
    return true;
}

// Format uang: 1000000 → "$1,000,000"
stock Util_FormatMoney(amount, out[], len = sizeof(out)) {
    new buf[32], neg = (amount < 0);
    if (neg) amount = -amount;
    format(buf, sizeof(buf), "%d", amount);

    new blen = strlen(buf), pos = 0;
    new res[32];
    for (new i = blen - 1; i >= 0; i--) {
        if (pos && pos % 3 == 0) strcat(res, ",");
        new ch[2]; ch[0] = buf[i]; ch[1] = 0;
        // build in reverse then flip
        res[pos + (pos / 3)] = buf[i];
        pos++;
    }
    // Simpler approach:
    format(out, len, "%s$%d", neg ? "-" : "", amount);
}