/*
 *  Vibe Roleplay - Player State
 *  File: core/player_state.inc
 */

#if defined _player_state_included
    #endinput
#endif
#define _player_state_included

#define PLAYER_STATE_AUTH           1
#define PLAYER_STATE_ALIVE          2
#define PLAYER_STATE_DEAD           3

#define IsPlayerLoggedIn(%0)        (PlayerData[%0][pLoggedIn])
#define IsPlayerAliveState(%0)      (PlayerData[%0][pState] == PLAYER_STATE_ALIVE)
#define IsPlayerDeadState(%0)       (PlayerData[%0][pState] == PLAYER_STATE_DEAD)
#define IsPlayerInAuth(%0)          (PlayerData[%0][pState] == PLAYER_STATE_AUTH)
#define IsPlayerReady(%0)           (PlayerData[%0][pLoggedIn] && PlayerData[%0][pState] == PLAYER_STATE_ALIVE)
