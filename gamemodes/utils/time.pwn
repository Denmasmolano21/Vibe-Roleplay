// utils/time.pwn — Helper waktu murni
// Tidak ada state global, tidak ada dependency ke modul lain.

#if defined _UTIL_TIME_PWN
    #endinput
#endif
#define _UTIL_TIME_PWN

// Format unix timestamp → "HH:MM:SS"
stock Util_TimeStr(out[], len = sizeof(out)) {
    new h, m, s;
    gettime(h, m, s);
    format(out, len, "%02d:%02d:%02d", h, m, s);
}

// Format unix timestamp → "DD/MM/YYYY"
stock Util_DateStr(out[], len = sizeof(out)) {
    new y, mo, d;
    getdate(y, mo, d);
    format(out, len, "%02d/%02d/%04d", d, mo, y);
}

// Konversi detik → string "Xj Ym Zd"
stock Util_SecondsToHMS(seconds, out[], len = sizeof(out)) {
    new h = seconds / 3600;
    new m = (seconds % 3600) / 60;
    new s = seconds % 60;
    if (h > 0) format(out, len, "%dj %dm %dd", h, m, s);
    else if (m > 0) format(out, len, "%dm %dd", m, s);
    else format(out, len, "%dd", s);
}
