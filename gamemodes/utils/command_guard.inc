/*
 *  Vibe Roleplay - Command Guard
 *  File: utils/command_guard.inc
 *
 *  Macro untuk validasi command: harus login + alive.
 *  Pakai di awal setiap command handler.
 */

#if defined _command_guard_included
    #endinput
#endif
#define _command_guard_included

// Cek apakah pemain sudah login
#define GUARD_LOGGED_IN(%0) \
    if (!PlayerData[(%0)][pLoggedIn]) \
        return SendErrorMessage((%0), "Kamu harus login terlebih dahulu.")

// Cek apakah pemain dalam keadaan hidup
#define GUARD_ALIVE(%0) \
    if (!IsPlayerAlive((%0))) \
        return SendErrorMessage((%0), "Kamu tidak bisa melakukan ini sekarang.")

// Cek apakah pemain siap (login + alive)
#define GUARD_READY(%0) \
    if (!IsPlayerReady((%0))) \
        return SendErrorMessage((%0), "Kamu tidak bisa melakukan ini sekarang.")
