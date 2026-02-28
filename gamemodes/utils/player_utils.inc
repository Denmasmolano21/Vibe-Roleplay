/*
 *  Vibe Roleplay - Player Utilities
 *  File: utils/player_utils.inc
 */

#if defined _player_utils_included
    #endinput
#endif
#define _player_utils_included

stock IsPlayerInRangeOfPlayer(playerid, targetid, Float:range)
{
    if (!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid))
        return 0;

    if (GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(targetid))
        return 0;

    if (GetPlayerInterior(playerid) != GetPlayerInterior(targetid))
        return 0;

    new Float:x, Float:y, Float:z;
    GetPlayerPos(targetid, x, y, z);
    return IsPlayerInRangeOfPoint(playerid, range, x, y, z);
}
