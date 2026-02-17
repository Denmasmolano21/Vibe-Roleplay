// anti_cheat.pwn — Cek health, armour, money, ping
// Depends on: player/data.pwn
// CATATAN: fungsi ini bernama AC_CheckPlayer (bukan AC_Tick)
//          agar tidak bentrok dengan "timer AC_Tick" di gamemode.pwn

#if defined _AC_PWN
    #endinput
#endif
#define _AC_PWN

stock AC_CheckPlayer(playerid) {
    if (!g_Player[playerid][p_LoggedIn]) return;

    // -- 1. Ping check --
    new ping = GetPlayerPing(playerid);
    if (ping > AC_MAX_PING) {
        new msg[64];
        format(msg, sizeof(msg), "[AC] Kick: ping terlalu tinggi (%d ms)", ping);
        SendClientMessage(playerid, COL_RED, msg);
        Player_Kick(playerid);
        return;
    }

    // -- 2. Health cheat --
    new Float:hp;
    GetPlayerHealth(playerid, hp);
    if (hp > AC_MAX_HEALTH) {
        SetPlayerHealth(playerid, 100.0);
        printf("[AC] Health reset  name=%s  val=%.1f",
            g_Player[playerid][p_Name], hp);
    }

    // -- 3. Armour cheat --
    new Float:arm;
    GetPlayerArmour(playerid, arm);
    if (arm > AC_MAX_ARMOUR) {
        SetPlayerArmour(playerid, 0.0);
        printf("[AC] Armour reset  name=%s  val=%.1f",
            g_Player[playerid][p_Name], arm);
    }

    // -- 4. Money desync --
    new client_cash = GetPlayerMoney(playerid);
    if (client_cash != g_Player[playerid][p_Money]) {
        ResetPlayerMoney(playerid);
        GivePlayerMoney(playerid, g_Player[playerid][p_Money]);
        printf("[AC] Money desync  name=%s  client=%d  server=%d",
            g_Player[playerid][p_Name],
            client_cash,
            g_Player[playerid][p_Money]
        );
    }
}
