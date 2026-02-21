/*
 *  Vibe Roleplay - Player State Machine
 *  File: core/player_state.inc
 *
 *  Manajemen state pemain untuk mencegah exploit:
 *  anti-spawn-abuse, anti-double-login, validasi aksi.
 */

#if defined _player_state_included
    #endinput
#endif
#define _player_state_included

// ============================================================================
//  Player State Enum
// ============================================================================

enum E_PLAYER_STATE
{
    STATE_NONE = 0,         // Baru connect, belum apa-apa
    STATE_AUTH,             // Sedang dalam proses login/register
    STATE_ALIVE,            // Sudah login, hidup, bisa beraktivitas
    STATE_DEAD,             // Mati, menunggu respawn
    STATE_SPECTATING        // Mode spectator
};

// ============================================================================
//  State Functions
// ============================================================================

stock SetPlayerState_(playerid, E_PLAYER_STATE:state)
{
    PlayerData[playerid][pState] = _:state;
    return 1;
}

stock E_PLAYER_STATE:GetPlayerState_(playerid)
{
    return E_PLAYER_STATE:PlayerData[playerid][pState];
}

stock bool:IsPlayerAlive(playerid)
{
    return (GetPlayerState_(playerid) == STATE_ALIVE);
}

stock bool:IsPlayerDead(playerid)
{
    return (GetPlayerState_(playerid) == STATE_DEAD);
}

stock bool:IsPlayerInAuth(playerid)
{
    return (GetPlayerState_(playerid) == STATE_AUTH);
}

stock bool:IsPlayerReady(playerid)
{
    // Pemain harus logged in DAN alive untuk bisa melakukan aksi
    if (!PlayerData[playerid][pLoggedIn])
        return false;

    if (!IsPlayerAlive(playerid))
        return false;

    return true;
}
