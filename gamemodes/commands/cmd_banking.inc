/*
 *  Vibe Roleplay - Banking Commands
 *  File: commands/cmd_banking.inc
 */

#if defined _cmd_banking_included
    #endinput
#endif
#define _cmd_banking_included

CMD:atm(playerid, params[])
{
    GUARD_READY(playerid);

    if (!IsPlayerNearATM(playerid))
    {
        SendErrorMessage(playerid, "Kamu tidak berada di dekat ATM.");
        return 1;
    }

    Banking_ShowATMMenu(playerid);
    return 1;
}

CMD:balance(playerid, params[])
{
    GUARD_READY(playerid);

    new msg[128];
    format(msg, sizeof(msg), "Saldo Bank: {00FF00}$%s {FFFFFF}| Uang Tunai: {00FF00}$%s", 
        FormatNumber(PlayerData[playerid][pBankMoney]),
        FormatNumber(PlayerData[playerid][pMoney])
    );
    SendInfoMessage(playerid, msg);
    return 1;
}

CMD:deposit(playerid, params[])
{
    GUARD_READY(playerid);

    if (!IsPlayerNearATM(playerid))
    {
        SendErrorMessage(playerid, "Kamu tidak berada di dekat ATM.");
        return 1;
    }

    new amount;
    if (sscanf(params, "i", amount))
    {
        SendErrorMessage(playerid, "Penggunaan: /deposit [jumlah]");
        return 1;
    }

    Banking_Deposit(playerid, amount);
    return 1;
}

CMD:withdraw(playerid, params[])
{
    GUARD_READY(playerid);

    if (!IsPlayerNearATM(playerid))
    {
        SendErrorMessage(playerid, "Kamu tidak berada di dekat ATM.");
        return 1;
    }

    new amount;
    if (sscanf(params, "i", amount))
    {
        SendErrorMessage(playerid, "Penggunaan: /withdraw [jumlah]");
        return 1;
    }

    Banking_Withdraw(playerid, amount);
    return 1;
}

CMD:transfer(playerid, params[])
{
    GUARD_READY(playerid);

    if (!IsPlayerNearATM(playerid))
    {
        SendErrorMessage(playerid, "Kamu tidak berada di dekat ATM.");
        return 1;
    }

    new targetid, amount;
    if (sscanf(params, "ui", targetid, amount))
    {
        SendErrorMessage(playerid, "Penggunaan: /transfer [playerid] [jumlah]");
        return 1;
    }

    Banking_Transfer(playerid, targetid, amount);
    return 1;
}
