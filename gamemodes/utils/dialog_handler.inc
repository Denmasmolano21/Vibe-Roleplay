/*
 *  Vibe Roleplay - Dialog Handler
 *  File: utils/dialog_handler.inc
 */

#if defined _dialog_handler_included
    #endinput
#endif
#define _dialog_handler_included

#include <YSI_Coding/y_hooks>

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        // VEHICLE MENU
        case DIALOG_VEHICLE_MENU:
        {
            if (!response) return 1;
            
            switch(listitem)
            {
                case 0: // My Vehicles
                {
                    new count = 0, info[2048];
                    format(info, sizeof(info), "{00D4FF}Model\t{00D4FF}Plate\t{00D4FF}Fuel\n");

                    foreach(new i : Vehicle)
                    {
                        if (VehicleData[i][vOwnerID] == PlayerData[playerid][pID])
                        {
                            format(info, sizeof(info), "%s{FFFFFF}%d\t{AFAFAF}%s\t{FFFFFF}%.1f\n",
                                info, VehicleData[i][vModel], VehicleData[i][vPlate], VehicleData[i][vFuel]);
                            count++;
                        }
                    }

                    if (count == 0)
                    {
                        SendInfoMessage(playerid, "Kamu belum memiliki kendaraan.");
                        return 1;
                    }

                    ShowPlayerDialog(playerid, DIALOG_VEHICLE_LIST, DIALOG_STYLE_TABLIST_HEADERS,
                        "My Vehicles", info, "Tutup", "");
                }
                case 1: // Engine
                {
                    if (!IsPlayerInAnyVehicle(playerid))
                    {
                        SendErrorMessage(playerid, "Kamu harus berada di dalam kendaraan.");
                        return 1;
                    }

                    new vehicleid = GetPlayerVehicleID(playerid);
                    new dataid = GetVehicleDataID(vehicleid);
                    if (dataid != -1) Vehicle_ToggleEngine(playerid, dataid);
                }
                case 2: // Lights
                {
                    if (!IsPlayerInAnyVehicle(playerid))
                    {
                        SendErrorMessage(playerid, "Kamu harus berada di dalam kendaraan.");
                        return 1;
                    }

                    new vehicleid = GetPlayerVehicleID(playerid);
                    new dataid = GetVehicleDataID(vehicleid);
                    if (dataid != -1) Vehicle_ToggleLights(playerid, dataid);
                }
                case 3: // Lock
                {
                    new dataid = LastVehicleUsed[playerid];
                    if (dataid == -1)
                    {
                        SendErrorMessage(playerid, "Kamu belum menggunakan kendaraan apapun.");
                        return 1;
                    }
                    Vehicle_ToggleLock(playerid, dataid);
                }
                case 4: // Park
                {
                    if (!IsPlayerInAnyVehicle(playerid))
                    {
                        SendErrorMessage(playerid, "Kamu harus berada di dalam kendaraan.");
                        return 1;
                    }

                    new vehicleid = GetPlayerVehicleID(playerid);
                    new dataid = GetVehicleDataID(vehicleid);
                    if (dataid != -1) Vehicle_Park(playerid, dataid);
                }
                default: SendInfoMessage(playerid, "Fitur ini segera hadir!");
            }
            return 1;
        }
        
        // INVENTORY MENU
        case DIALOG_INVENTORY_MAIN:
        {
            if (!response) return 1;
            
            if (PlayerInventory[playerid][listitem][invItemID] == 0)
            {
                SendErrorMessage(playerid, "Slot ini kosong.");
                return 1;
            }
            
            Inventory_UseItem(playerid, listitem);
            Inventory_ShowMenu(playerid);
            return 1;
        }
        
        // PHONE MENU
        case DIALOG_PHONE_MAIN:
        {
            if (!response) return 1;
            
            switch(listitem)
            {
                case 1: SendInfoMessage(playerid, "Gunakan /call [nomor] untuk menelepon.");
                case 2: SendInfoMessage(playerid, "Gunakan /sms [nomor] [pesan] untuk kirim SMS.");
                default: SendInfoMessage(playerid, "Fitur ini segera hadir!");
            }
            return 1;
        }
        
        // HOUSE MENU
        case DIALOG_HOUSE_MENU:
        {
            if (!response) return 1;
            SendInfoMessage(playerid, "House menu coming soon!");
            return 1;
        }
        
        // BUSINESS MENU
        case DIALOG_BUSINESS_MENU:
        {
            if (!response) return 1;
            SendInfoMessage(playerid, "Business menu coming soon!");
            return 1;
        }
        
        // JOB MENU
        case DIALOG_JOB_MENU:
        {
            if (!response) return 1;
            
            if (PlayerJob[playerid] == E_JOB_TYPE:JOB_NONE)
            {
                if (listitem < sizeof(JobData))
                {
                    Job_Accept(playerid, listitem);
                }
            }
            else
            {
                switch(listitem)
                {
                    case 0: 
                    {
                        PlayerOnDuty[playerid] = true;
                        SendSuccessMessage(playerid, "Kamu mulai bekerja!");
                    }
                    case 1: 
                    {
                        PlayerOnDuty[playerid] = false;
                        SendInfoMessage(playerid, "Kamu berhenti bekerja.");
                    }
                    case 2: Job_Quit(playerid);
                    default: SendInfoMessage(playerid, "Info job segera hadir!");
                }
            }
            return 1;
        }
        
        // FACTION MENU
        case DIALOG_FACTION_MENU:
        {
            if (!response) return 1;
            
            if (PlayerFaction[playerid] == 0)
            {
                SendInfoMessage(playerid, "Hubungi leader faction untuk bergabung.");
            }
            else
            {
                if (listitem == 4)
                {
                    PlayerFaction[playerid] = 0;
                    PlayerFactionRank[playerid] = 0;
                    SendInfoMessage(playerid, "Kamu keluar dari faction.");
                }
                else
                {
                    SendInfoMessage(playerid, "Fitur ini segera hadir!");
                }
            }
            return 1;
        }
        
        // ADMIN MENU
        case DIALOG_ADMIN_MAIN:
        {
            if (!response) return 1;
            
            switch(listitem)
            {
                case 4: SendInfoMessage(playerid, "Gunakan /reports untuk melihat report.");
                case 5: SendInfoMessage(playerid, "Gunakan /ahelp untuk bantuan admin.");
                default: SendInfoMessage(playerid, "Fitur ini coming soon!");
            }
            return 1;
        }

        // ATM MENU
        case DIALOG_ATM_MENU:
        {
            if (!response) return 1;
            
            switch(listitem)
            {
                case 0: // Deposit
                {
                    new dialog[256];
                    format(dialog, sizeof(dialog),
                        "{FFFFFF}Masukkan jumlah uang yang ingin disetor:\n\n" \
                        "{AFAFAF}Uang Tunai: {00FF00}$%s",
                        FormatNumber(PlayerData[playerid][pMoney]));
                    
                    ShowPlayerDialog(playerid, DIALOG_ATM_DEPOSIT, DIALOG_STYLE_INPUT,
                        "ATM - Deposit", dialog, "Deposit", "Batal");
                }
                case 1: // Withdraw
                {
                    new dialog[256];
                    format(dialog, sizeof(dialog),
                        "{FFFFFF}Masukkan jumlah uang yang ingin ditarik:\n\n" \
                        "{AFAFAF}Saldo Bank: {00FF00}$%s",
                        FormatNumber(PlayerData[playerid][pBankMoney]));
                    
                    ShowPlayerDialog(playerid, DIALOG_ATM_WITHDRAW, DIALOG_STYLE_INPUT,
                        "ATM - Withdraw", dialog, "Withdraw", "Batal");
                }
                case 2: // Transfer
                {
                    new dialog[256];
                    format(dialog, sizeof(dialog),
                        "{FFFFFF}Masukkan ID player yang ingin ditransfer:\n\n" \
                        "{AFAFAF}Saldo Bank: {00FF00}$%s\n" \
                        "{FF6B00}Fee: 1%% dari jumlah transfer",
                        FormatNumber(PlayerData[playerid][pBankMoney]));
                    
                    ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER, DIALOG_STYLE_INPUT,
                        "ATM - Transfer", dialog, "Lanjut", "Batal");
                }
                case 3: // History
                {
                    Banking_ShowHistory(playerid);
                }
            }
            return 1;
        }

        case DIALOG_ATM_DEPOSIT:
        {
            if (!response) return Banking_ShowATMMenu(playerid);
            
            new amount = strval(inputtext);
            if (amount < 1)
            {
                SendErrorMessage(playerid, "Jumlah tidak valid.");
                return Banking_ShowATMMenu(playerid);
            }
            
            Banking_Deposit(playerid, amount);
            return 1;
        }

        case DIALOG_ATM_WITHDRAW:
        {
            if (!response) return Banking_ShowATMMenu(playerid);
            
            new amount = strval(inputtext);
            if (amount < 1)
            {
                SendErrorMessage(playerid, "Jumlah tidak valid.");
                return Banking_ShowATMMenu(playerid);
            }
            
            Banking_Withdraw(playerid, amount);
            return 1;
        }

        case DIALOG_ATM_TRANSFER:
        {
            if (!response) return Banking_ShowATMMenu(playerid);
            
            new targetid = strval(inputtext);
            if (!IsPlayerConnected(targetid))
            {
                SendErrorMessage(playerid, "Player tidak ditemukan.");
                return Banking_ShowATMMenu(playerid);
            }
            
            SetPVarInt(playerid, "TransferTarget", targetid);
            
            new targetName[MAX_PLAYER_NAME];
            GetPlayerName(targetid, targetName, sizeof(targetName));
            
            new dialog[256];
            format(dialog, sizeof(dialog),
                "{FFFFFF}Transfer ke: {00D4FF}%s\n\n" \
                "{FFFFFF}Masukkan jumlah yang ingin ditransfer:\n" \
                "{AFAFAF}Saldo Bank: {00FF00}$%s\n" \
                "{FF6B00}Fee: 1%% dari jumlah transfer",
                targetName, FormatNumber(PlayerData[playerid][pBankMoney]));
            
            ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER_AMOUNT, DIALOG_STYLE_INPUT,
                "ATM - Transfer Amount", dialog, "Transfer", "Batal");
            return 1;
        }

        case DIALOG_ATM_TRANSFER_AMOUNT:
        {
            if (!response)
            {
                DeletePVar(playerid, "TransferTarget");
                return Banking_ShowATMMenu(playerid);
            }
            
            new amount = strval(inputtext);
            new targetid = GetPVarInt(playerid, "TransferTarget");
            
            Banking_Transfer(playerid, targetid, amount);
            DeletePVar(playerid, "TransferTarget");
            return 1;
        }
    }
    
    return 0;
}

