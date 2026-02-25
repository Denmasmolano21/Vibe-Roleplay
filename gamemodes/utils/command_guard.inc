/*
 *  Vibe Roleplay - Command Guard
 *  File: utils/command_guard.inc
 *
 *  Macro untuk validasi command.
 */

#if defined _command_guard_included
    #endinput
#endif
#define _command_guard_included

// ============================================================================
//  Command Guard Macros
// ============================================================================

// Cek apakah pemain sudah login
#define GUARD_LOGGED_IN(%0) \
    if (!PlayerData[(%0)][pLoggedIn]) \
        return SendErrorMessage((%0), "Kamu harus login terlebih dahulu.")

// Cek apakah pemain dalam keadaan hidup (state = ALIVE)
#define GUARD_ALIVE(%0) \
    if (PlayerData[%0][pState] != PLAYER_STATE_ALIVE) \
        return SendErrorMessage((%0), "Kamu tidak bisa melakukan ini sekarang.")

// Cek apakah pemain siap (login + alive)
#define GUARD_READY(%0) \
    if (!PlayerData[%0][pLoggedIn] || PlayerData[%0][pState] != PLAYER_STATE_ALIVE) \
        return SendErrorMessage((%0), "Kamu tidak bisa melakukan ini sekarang.")

// Cek apakah pemain adalah admin (level 1+)
#define GUARD_ADMIN(%0) \
    if (PlayerData[%0][pAdminLevel] < 1) \
        return SendErrorMessage((%0), "Kamu tidak memiliki akses command ini.")

// Cek parameter tidak kosong
#define GUARD_PARAMS(%0,%1) \
    if (isnull(%1)) \
        return SendErrorMessage((%0), "Penggunaan: /" #%0 " [parameter]")

// Cek apakah pemain dalam kendaraan
#define GUARD_IN_VEHICLE(%0) \
    if (!IsPlayerInAnyVehicle(%0)) \
        return SendErrorMessage((%0), "Kamu harus berada di dalam kendaraan.")

// Cek apakah pemain tidak dalam kendaraan
#define GUARD_ON_FOOT(%0) \
    if (IsPlayerInAnyVehicle(%0)) \
        return SendErrorMessage((%0), "Kamu harus keluar dari kendaraan terlebih dahulu.")
