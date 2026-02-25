/*
 *  Vibe Roleplay - Player State
 *  File: core/player_state.inc
 *
 *  State constants untuk tracking status pemain.
 *  Tidak perlu fungsi wrapper - langsung pakai variabel PlayerData[playerid][pState]
 */

#if defined _player_state_included
    #endinput
#endif
#define _player_state_included

// ============================================================================
//  Player State Constants (langsung pakai ini)
// ============================================================================

#define PLAYER_STATE_AUTH           1   // Sedang login/register
#define PLAYER_STATE_ALIVE          2   // Sudah login, hidup
#define PLAYER_STATE_DEAD           3   // Mati, menunggu respawn

// ============================================================================
//  Helper Macros (opsional, bisa juga langsung cek PlayerData)
// ============================================================================

#define IsPlayerLoggedIn(%0)        (PlayerData[%0][pLoggedIn])
#define IsPlayerAliveState(%0)      (PlayerData[%0][pState] == PLAYER_STATE_ALIVE)
#define IsPlayerDeadState(%0)       (PlayerData[%0][pState] == PLAYER_STATE_DEAD)
#define IsPlayerInAuth(%0)          (PlayerData[%0][pState] == PLAYER_STATE_AUTH)
#define IsPlayerReady(%0)           (PlayerData[%0][pLoggedIn] && PlayerData[%0][pState] == PLAYER_STATE_ALIVE)
