/*
 *  Vibe Roleplay - Command Guard
 *  File: utils/command_guard.inc
 */

#if defined _command_guard_included
    #endinput
#endif
#define _command_guard_included

#define GUARD_LOGGED_IN(%0) \
    if (!PlayerData[(%0)][pLoggedIn]) \
        return SendErrorMessage((%0), "Kamu harus login terlebih dahulu.")

#define GUARD_ALIVE(%0) \
    if (PlayerData[%0][pState] != PLAYER_STATE_ALIVE) \
        return SendErrorMessage((%0), "Kamu tidak bisa melakukan ini sekarang.")

#define GUARD_READY(%0) \
    if (!PlayerData[%0][pLoggedIn] || PlayerData[%0][pState] != PLAYER_STATE_ALIVE) \
        return SendErrorMessage((%0), "Kamu tidak bisa melakukan ini sekarang.")

#define GUARD_ADMIN(%0) \
    if (PlayerData[%0][pAdminLevel] < 1) \
        return SendErrorMessage((%0), "Kamu tidak memiliki akses command ini.")

#define GUARD_ADMIN_LEVEL(%0,%1) \
    if (PlayerData[%0][pAdminLevel] < %1) return _GuardAdminLevel(%0, %1)

stock _GuardAdminLevel(playerid, level)
{
    new msg[64];
    format(msg, sizeof(msg), "Command ini membutuhkan admin level %d.", level);
    return SendErrorMessage(playerid, msg);
}

#define GUARD_PARAMS(%0,%1) \
    if (isnull(%1)) \
        return SendErrorMessage((%0), "Penggunaan: /" #%0 " [parameter]")

#define GUARD_IN_VEHICLE(%0) \
    if (!IsPlayerInAnyVehicle(%0)) \
        return SendErrorMessage((%0), "Kamu harus berada di dalam kendaraan.")

#define GUARD_ON_FOOT(%0) \
    if (IsPlayerInAnyVehicle(%0)) \
        return SendErrorMessage((%0), "Kamu harus keluar dari kendaraan terlebih dahulu.")
