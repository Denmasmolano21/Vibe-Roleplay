// utils/math.pwn — Fungsi matematika murni
// Tidak ada state global, tidak ada dependency ke modul lain.

#if defined _UTIL_MATH_PWN
    #endinput
#endif
#define _UTIL_MATH_PWN

// Jarak 3D antara dua titik
stock Float:Util_Dist3D(Float:x1, Float:y1, Float:z1,
                         Float:x2, Float:y2, Float:z2) {
    return floatsqroot(
        (x2 - x1) * (x2 - x1) +
        (y2 - y1) * (y2 - y1) +
        (z2 - z1) * (z2 - z1)
    );
}

// Jarak 2D (abaikan Z)
stock Float:Util_Dist2D(Float:x1, Float:y1, Float:x2, Float:y2) {
    return floatsqroot(
        (x2 - x1) * (x2 - x1) +
        (y2 - y1) * (y2 - y1)
    );
}

// Clamp integer
stock Util_Clamp(val, lo, hi) {
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

// Clamp float
stock Float:Util_ClampF(Float:val, Float:lo, Float:hi) {
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

// Random integer [lo, hi]
stock Util_Rand(lo, hi) {
    return lo + random(hi - lo + 1);
}

// Kecepatan kendaraan dari velocity vector → km/h
// SA-MP velocity unit ≈ 1 unit/tick × 180 = km/h
stock Float:Util_VehicleSpeed(Float:vx, Float:vy, Float:vz) {
    return floatsqroot(vx * vx + vy * vy + vz * vz) * 180.0;
}
