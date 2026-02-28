/*
 *  Vibe Roleplay - Banking & ATM System
 *  File: modules/banking/banking.inc
 */

#if defined _banking_included
    #endinput
#endif
#define _banking_included

#include <YSI_Coding/y_hooks>
#include <YSI_Data/y_iterate>

#define MAX_TRANSACTION_HISTORY     50
#define MAX_TRANSACTION_DESC        64
#define TRANSFER_FEE_PERCENT        1
#define MIN_TRANSFER_AMOUNT         100
#define MAX_TRANSFER_AMOUNT         10000000

enum E_TRANSACTION_TYPE
{
    TRANS_DEPOSIT,
    TRANS_WITHDRAW,
    TRANS_TRANSFER_IN,
    TRANS_TRANSFER_OUT
}

enum E_TRANSACTION_DATA
{
    transID,
    transPlayerID,
    E_TRANSACTION_TYPE:transType,
    transAmount,
    transBalance,
    transDesc[MAX_TRANSACTION_DESC],
    transTimestamp
}

new PlayerTransactions[MAX_PLAYERS][MAX_TRANSACTION_HISTORY][E_TRANSACTION_DATA];
new PlayerTransactionCount[MAX_PLAYERS];

new Float:ATMLocations[][3] = {
    {1481.0, -1771.0, 18.8},
    {2412.0, -1492.0, 24.0},
    {1038.0, -1340.0, 13.7},
    {2230.0, -1159.0, 25.9},
    {2647.0, -2091.0, 13.5}
};

stock Banking_AddTransaction(playerid, E_TRANSACTION_TYPE:type, amount, const description[])
{
    if (!IsPlayerConnected(playerid))
        return 0;

    new slot = PlayerTransactionCount[playerid] % MAX_TRANSACTION_HISTORY;
    
    PlayerTransactions[playerid][slot][transPlayerID] = playerid;
    PlayerTransactions[playerid][slot][transType] = type;
    PlayerTransactions[playerid][slot][transAmount] = amount;
    PlayerTransactions[playerid][slot][transBalance] = PlayerData[playerid][pBankMoney];
    format(PlayerTransactions[playerid][slot][transDesc], MAX_TRANSACTION_DESC, "%s", description);
    PlayerTransactions[playerid][slot][transTimestamp] = gettime();
    
    PlayerTransactionCount[playerid]++;
    return 1;
}

stock Banking_ShowATMMenu(playerid)
{
    new caption[64];
    format(caption, sizeof(caption), "%s - ATM", SERVER_NAME);

    new info[768];
    format(info, sizeof(info), \
        "{FFFFFF}Selamat datang di ATM\n" \
        "{AFAFAF}Saldo Bank: {00FF00}$%s\n" \
        "{AFAFAF}Uang Tunai: {00FF00}$%s\n\n" \
        "{00D4FF}Deposit\t{FFFFFF}Setor uang ke bank\n" \
        "{00D4FF}Withdraw\t{FFFFFF}Tarik uang dari bank\n" \
        "{00D4FF}Transfer\t{FFFFFF}Transfer ke player lain\n" \
        "{00D4FF}History\t{FFFFFF}Riwayat transaksi",
        FormatNumber(PlayerData[playerid][pBankMoney]),
        FormatNumber(PlayerData[playerid][pMoney])
    );

    ShowPlayerDialog(playerid, DIALOG_ATM_MENU, DIALOG_STYLE_TABLIST,
        caption, info, "Pilih", "Tutup");
    return 1;
}

stock Banking_Deposit(playerid, amount)
{
    if (amount < 1)
    {
        SendErrorMessage(playerid, "Jumlah tidak valid.");
        return 0;
    }

    if (PlayerData[playerid][pMoney] < amount)
    {
        SendErrorMessage(playerid, "Uang tunai tidak cukup.");
        return 0;
    }

    PlayerData[playerid][pMoney] -= amount;
    PlayerData[playerid][pBankMoney] += amount;
    GivePlayerMoney(playerid, -amount);

    new desc[MAX_TRANSACTION_DESC];
    format(desc, sizeof(desc), "Deposit $%s", FormatNumber(amount));
    Banking_AddTransaction(playerid, TRANS_DEPOSIT, amount, desc);

    new msg[128];
    format(msg, sizeof(msg), "Berhasil deposit $%s. Saldo bank: $%s", 
        FormatNumber(amount), FormatNumber(PlayerData[playerid][pBankMoney]));
    SendSuccessMessage(playerid, msg);

    SavePlayerDataToDB(playerid);
    return 1;
}

stock Banking_Withdraw(playerid, amount)
{
    if (amount < 1)
    {
        SendErrorMessage(playerid, "Jumlah tidak valid.");
        return 0;
    }

    if (PlayerData[playerid][pBankMoney] < amount)
    {
        SendErrorMessage(playerid, "Saldo bank tidak cukup.");
        return 0;
    }

    PlayerData[playerid][pBankMoney] -= amount;
    PlayerData[playerid][pMoney] += amount;
    GivePlayerMoney(playerid, amount);

    new desc[MAX_TRANSACTION_DESC];
    format(desc, sizeof(desc), "Withdraw $%s", FormatNumber(amount));
    Banking_AddTransaction(playerid, TRANS_WITHDRAW, amount, desc);

    new msg[128];
    format(msg, sizeof(msg), "Berhasil tarik $%s. Saldo bank: $%s", 
        FormatNumber(amount), FormatNumber(PlayerData[playerid][pBankMoney]));
    SendSuccessMessage(playerid, msg);

    SavePlayerDataToDB(playerid);
    return 1;
}

stock Banking_Transfer(playerid, targetid, amount)
{
    if (!IsPlayerConnected(targetid))
    {
        SendErrorMessage(playerid, "Player tidak ditemukan.");
        return 0;
    }

    if (playerid == targetid)
    {
        SendErrorMessage(playerid, "Tidak bisa transfer ke diri sendiri.");
        return 0;
    }

    if (amount < MIN_TRANSFER_AMOUNT)
    {
        new msg[128];
        format(msg, sizeof(msg), "Minimum transfer $%s", FormatNumber(MIN_TRANSFER_AMOUNT));
        SendErrorMessage(playerid, msg);
        return 0;
    }

    if (amount > MAX_TRANSFER_AMOUNT)
    {
        new msg[128];
        format(msg, sizeof(msg), "Maximum transfer $%s", FormatNumber(MAX_TRANSFER_AMOUNT));
        SendErrorMessage(playerid, msg);
        return 0;
    }

    new fee = (amount * TRANSFER_FEE_PERCENT) / 100;
    new total = amount + fee;

    if (PlayerData[playerid][pBankMoney] < total)
    {
        new msg[128];
        format(msg, sizeof(msg), "Saldo tidak cukup. Butuh $%s (termasuk fee $%s)", 
            FormatNumber(total), FormatNumber(fee));
        SendErrorMessage(playerid, msg);
        return 0;
    }

    PlayerData[playerid][pBankMoney] -= total;
    PlayerData[targetid][pBankMoney] += amount;

    new desc[MAX_TRANSACTION_DESC];
    new targetName[MAX_PLAYER_NAME];
    GetPlayerName(targetid, targetName, sizeof(targetName));
    
    format(desc, sizeof(desc), "Transfer to %s", targetName);
    Banking_AddTransaction(playerid, TRANS_TRANSFER_OUT, amount, desc);

    new senderName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, senderName, sizeof(senderName));
    format(desc, sizeof(desc), "Transfer from %s", senderName);
    Banking_AddTransaction(targetid, TRANS_TRANSFER_IN, amount, desc);

    new msg[128];
    format(msg, sizeof(msg), "Transfer $%s ke %s berhasil (fee: $%s)", 
        FormatNumber(amount), targetName, FormatNumber(fee));
    SendSuccessMessage(playerid, msg);

    format(msg, sizeof(msg), "Kamu menerima transfer $%s dari %s", 
        FormatNumber(amount), senderName);
    SendSuccessMessage(targetid, msg);

    SavePlayerDataToDB(playerid);
    SavePlayerDataToDB(targetid);
    return 1;
}

stock Banking_ShowHistory(playerid)
{
    new caption[64];
    format(caption, sizeof(caption), "%s - Transaction History", SERVER_NAME);

    new info[2048];
    format(info, sizeof(info), "{00D4FF}Type\t{00D4FF}Amount\t{00D4FF}Balance\n");

    new count = 0;
    new start = (PlayerTransactionCount[playerid] > MAX_TRANSACTION_HISTORY) ? 
        (PlayerTransactionCount[playerid] - MAX_TRANSACTION_HISTORY) : 0;

    for (new i = PlayerTransactionCount[playerid] - 1; i >= start && count < 20; i--)
    {
        new slot = i % MAX_TRANSACTION_HISTORY;
        new typeStr[32];
        
        switch (PlayerTransactions[playerid][slot][transType])
        {
            case TRANS_DEPOSIT: format(typeStr, sizeof(typeStr), "{00FF00}Deposit");
            case TRANS_WITHDRAW: format(typeStr, sizeof(typeStr), "{FF6B00}Withdraw");
            case TRANS_TRANSFER_IN: format(typeStr, sizeof(typeStr), "{00FF00}Transfer In");
            case TRANS_TRANSFER_OUT: format(typeStr, sizeof(typeStr), "{FF0000}Transfer Out");
        }

        format(info, sizeof(info), "%s%s\t{FFFFFF}$%s\t{FFFFFF}$%s\n",
            info, typeStr,
            FormatNumber(PlayerTransactions[playerid][slot][transAmount]),
            FormatNumber(PlayerTransactions[playerid][slot][transBalance])
        );
        count++;
    }

    if (count == 0)
        format(info, sizeof(info), "{FFFFFF}Belum ada transaksi.");

    ShowPlayerDialog(playerid, DIALOG_ATM_HISTORY, DIALOG_STYLE_TABLIST_HEADERS,
        caption, info, "Tutup", "");
    return 1;
}

stock IsPlayerNearATM(playerid)
{
    for (new i = 0; i < sizeof(ATMLocations); i++)
    {
        if (IsPlayerInRangeOfPoint(playerid, 2.0, ATMLocations[i][0], ATMLocations[i][1], ATMLocations[i][2]))
            return 1;
    }
    return 0;
}

stock FormatNumber(number)
{
    new str[32], formatted[32];
    format(str, sizeof(str), "%d", number);
    
    new len = strlen(str);
    new pos = 0;
    
    for (new i = len - 1; i >= 0; i--)
    {
        formatted[pos++] = str[i];
        if ((len - i) % 3 == 0 && i != 0)
            formatted[pos++] = ',';
    }
    
    formatted[pos] = '\0';
    
    new result[32];
    pos = 0;
    for (new i = strlen(formatted) - 1; i >= 0; i--)
        result[pos++] = formatted[i];
    
    result[pos] = '\0';
    return result;
}

hook OnPlayerConnect(playerid)
{
    PlayerTransactionCount[playerid] = 0;
    return 1;
}

hook OnGameModeInit()
{
    for (new i = 0; i < sizeof(ATMLocations); i++)
    {
        CreateDynamicPickup(1274, 1, ATMLocations[i][0], ATMLocations[i][1], ATMLocations[i][2], 0, 0);
        
        new labelText[128];
        format(labelText, sizeof(labelText), \
            "{00D4FF}ATM\n" \
            "{FFFFFF}Gunakan {00FF00}/atm{FFFFFF} untuk mengakses"
        );
        CreateDynamic3DTextLabel(labelText, COLOR_WHITE, 
            ATMLocations[i][0], ATMLocations[i][1], ATMLocations[i][2] + 0.5, 10.0);
    }
    
    printf("[BANKING] Banking system loaded. ATM locations: %d", sizeof(ATMLocations));
    return 1;
}
