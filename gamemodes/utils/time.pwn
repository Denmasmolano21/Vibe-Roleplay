#if defined _UTIL_TIME_PWN
    #endinput
#endif
#define _UTIL_TIME_PWN

stock Util_TimeStr(out[], len = sizeof(out)) {
    new h, m, s;
    gettime(h, m, s);
    format(out, len, "%02d:%02d:%02d", h, m, s);
}

stock Util_DateStr(out[], len = sizeof(out)) {
    new y, mo, d;
    getdate(y, mo, d);
    format(out, len, "%02d/%02d/%04d", d, mo, y);
}

stock Util_SecondsToHMS(sec, out[], len = sizeof(out)) {
    new h = sec/3600, m = (sec%3600)/60, s = sec%60;
    if (h) format(out, len, "%dj %dm %ds", h, m, s);
    else if (m) format(out, len, "%dm %ds", m, s);
    else format(out, len, "%ds", s);
}