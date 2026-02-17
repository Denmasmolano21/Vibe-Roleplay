#if defined _UTIL_MATH_PWN
    #endinput
#endif
#define _UTIL_MATH_PWN

stock Float:Util_Dist3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2) {
    return floatsqroot((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));
}

stock Float:Util_Dist2D(Float:x1,Float:y1,Float:x2,Float:y2) {
    return floatsqroot((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

stock Util_Clamp(val, lo, hi) {
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

stock Float:Util_ClampF(Float:val, Float:lo, Float:hi) {
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

stock Util_Rand(lo, hi) {
    return random(hi - lo + 1) + lo;
}

stock Float:Util_VehicleSpeed(vehicleid) {
    new Float:vx, Float:vy, Float:vz;
    GetVehicleVelocity(vehicleid, vx, vy, vz);
    return floatsqroot(vx*vx + vy*vy + vz*vz) * 180.0;
}