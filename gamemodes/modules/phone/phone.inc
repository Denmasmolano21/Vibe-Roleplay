/*
 *  Vibe Roleplay - Phone System
 *  File: modules/phone/phone.inc
 */

#if defined _phone_included
    #endinput
#endif
#define _phone_included

#include <YSI_Coding/y_hooks>
#include <YSI_Data/y_iterate>

// PHONE CONFIGURATION

#define MAX_CONTACTS        50
#define MAX_SMS_HISTORY     20
#define MAX_CONTACT_NAME    32

// PHONE DATA STRUCTURES

enum E_CONTACT_DATA
{
    contactID,
    contactName[MAX_CONTACT_NAME],
    contactNumber
}

enum E_SMS_DATA
{
    smsFrom,
    smsTo,
    smsMessage[128],
    smsTimestamp
}

new PlayerContacts[MAX_PLAYERS][MAX_CONTACTS][E_CONTACT_DATA];
new PlayerSMS[MAX_PLAYERS][MAX_SMS_HISTORY][E_SMS_DATA];
new PlayerPhoneNumber[MAX_PLAYERS];
new bool:PlayerHasPhone[MAX_PLAYERS];
new PlayerInCall[MAX_PLAYERS] = {INVALID_PLAYER_ID, ...};
new SelectedContact[MAX_PLAYERS];

// PHONE FUNCTIONS

stock Phone_Reset(playerid)
{
    for (new i = 0; i < MAX_CONTACTS; i++)
    {
        PlayerContacts[playerid][i][contactID] = 0;
        PlayerContacts[playerid][i][contactName][0] = EOS;
        PlayerContacts[playerid][i][contactNumber] = 0;
    }
    
    for (new i = 0; i < MAX_SMS_HISTORY; i++)
    {
        PlayerSMS[playerid][i][smsFrom] = 0;
        PlayerSMS[playerid][i][smsTo] = 0;
        PlayerSMS[playerid][i][smsMessage][0] = EOS;
        PlayerSMS[playerid][i][smsTimestamp] = 0;
    }
    
    PlayerPhoneNumber[playerid] = 0;
    PlayerHasPhone[playerid] = false;
    PlayerInCall[playerid] = INVALID_PLAYER_ID;
    SelectedContact[playerid] = -1;
    return 1;
}

stock Phone_GivePhone(playerid)
{
    if (PlayerHasPhone[playerid])
        return 0;
        
    PlayerHasPhone[playerid] = true;
    PlayerPhoneNumber[playerid] = 1000000 + random(8999999);
    
    new msg[128];
    format(msg, sizeof(msg), "Kamu mendapat phone! Nomor: %d", PlayerPhoneNumber[playerid]);
    SendSuccessMessage(playerid, msg);
    return 1;
}

stock Phone_AddContact(playerid, const name[], number)
{
    for (new i = 0; i < MAX_CONTACTS; i++)
    {
        if (PlayerContacts[playerid][i][contactID] == 0)
        {
            PlayerContacts[playerid][i][contactID] = i + 1;
            format(PlayerContacts[playerid][i][contactName], MAX_CONTACT_NAME, "%s", name);
            PlayerContacts[playerid][i][contactNumber] = number;
            return 1;
        }
    }
    return 0;
}

stock Phone_RemoveContact(playerid, slot)
{
    if (slot < 0 || slot >= MAX_CONTACTS)
        return 0;
        
    PlayerContacts[playerid][slot][contactID] = 0;
    PlayerContacts[playerid][slot][contactName][0] = EOS;
    PlayerContacts[playerid][slot][contactNumber] = 0;
    return 1;
}

stock Phone_SendSMS(playerid, targetid, const message[])
{
    if (!PlayerHasPhone[playerid])
    {
        SendErrorMessage(playerid, "Kamu tidak memiliki phone.");
        return 0;
    }
    
    if (!PlayerHasPhone[targetid])
    {
        SendErrorMessage(playerid, "Nomor tidak aktif.");
        return 0;
    }
    
    // Add to sender's history
    for (new i = MAX_SMS_HISTORY - 1; i > 0; i--)
    {
        PlayerSMS[playerid][i] = PlayerSMS[playerid][i - 1];
    }
    PlayerSMS[playerid][0][smsFrom] = PlayerPhoneNumber[playerid];
    PlayerSMS[playerid][0][smsTo] = PlayerPhoneNumber[targetid];
    format(PlayerSMS[playerid][0][smsMessage], 128, "%s", message);
    PlayerSMS[playerid][0][smsTimestamp] = gettime();
    
    // Add to receiver's history
    for (new i = MAX_SMS_HISTORY - 1; i > 0; i--)
    {
        PlayerSMS[targetid][i] = PlayerSMS[targetid][i - 1];
    }
    PlayerSMS[targetid][0][smsFrom] = PlayerPhoneNumber[playerid];
    PlayerSMS[targetid][0][smsTo] = PlayerPhoneNumber[targetid];
    format(PlayerSMS[targetid][0][smsMessage], 128, "%s", message);
    PlayerSMS[targetid][0][smsTimestamp] = gettime();
    
    // Notify
    new msg[256];
    format(msg, sizeof(msg), "[SMS dari %d] %s", PlayerPhoneNumber[playerid], message);
    SendClientMessage(targetid, COLOR_INFO, msg);
    
    format(msg, sizeof(msg), "[SMS ke %d] %s", PlayerPhoneNumber[targetid], message);
    SendClientMessage(playerid, COLOR_SUCCESS, msg);
    
    return 1;
}

stock Phone_Call(playerid, targetid)
{
    if (!PlayerHasPhone[playerid])
    {
        SendErrorMessage(playerid, "Kamu tidak memiliki phone.");
        return 0;
    }
    
    if (!PlayerHasPhone[targetid])
    {
        SendErrorMessage(playerid, "Nomor tidak aktif.");
        return 0;
    }
    
    if (PlayerInCall[targetid] != INVALID_PLAYER_ID)
    {
        SendErrorMessage(playerid, "Nomor sedang sibuk.");
        return 0;
    }
    
    PlayerInCall[playerid] = targetid;
    PlayerInCall[targetid] = playerid;
    
    new msg[128];
    format(msg, sizeof(msg), "* %s mengangkat phone dan menelepon.", GetPlayerNameEx(playerid));
    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, msg);
    
    format(msg, sizeof(msg), "[PHONE] Panggilan dari %d. Ketik /pickup untuk menjawab.", PlayerPhoneNumber[playerid]);
    SendClientMessage(targetid, COLOR_INFO, msg);
    
    SendSuccessMessage(playerid, "Menghubungi...");
    return 1;
}

stock Phone_Hangup(playerid)
{
    if (PlayerInCall[playerid] == INVALID_PLAYER_ID)
    {
        SendErrorMessage(playerid, "Kamu tidak sedang dalam panggilan.");
        return 0;
    }
    
    new targetid = PlayerInCall[playerid];
    
    PlayerInCall[playerid] = INVALID_PLAYER_ID;
    PlayerInCall[targetid] = INVALID_PLAYER_ID;
    
    SendInfoMessage(playerid, "Panggilan diakhiri.");
    SendInfoMessage(targetid, "Panggilan diakhiri.");
    
    new msg[128];
    format(msg, sizeof(msg), "* %s menutup phone.", GetPlayerNameEx(playerid));
    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, msg);
    
    return 1;
}

stock Phone_ShowMenu(playerid)
{
    if (!PlayerHasPhone[playerid])
    {
        SendErrorMessage(playerid, "Kamu tidak memiliki phone. Beli di toko!");
        return 0;
    }
    
    new caption[64];
    format(caption, sizeof(caption), "%s - Phone", SERVER_NAME);

    new info[768];
    format(info, sizeof(info), \
        "{FFFFFF}Phone Menu\n" \
        "{AFAFAF}Nomor kamu: {00D4FF}%d\n\n" \
        "{00D4FF}Contacts\t{FFFFFF}Lihat kontak\n" \
        "{00D4FF}Call\t\t{FFFFFF}Telepon seseorang\n" \
        "{00D4FF}SMS\t\t{FFFFFF}Kirim pesan\n" \
        "{00D4FF}SMS History\t{FFFFFF}Lihat riwayat SMS\n" \
        "{00D4FF}Add Contact\t{FFFFFF}Tambah kontak baru\n" \
        "{00D4FF}Settings\t{FFFFFF}Pengaturan phone",
        PlayerPhoneNumber[playerid]
    );

    ShowPlayerDialog(playerid, DIALOG_PHONE_MAIN, DIALOG_STYLE_TABLIST,
        caption, info, "Pilih", "Tutup");
    return 1;
}

// HOOKS

hook OnPlayerConnect(playerid)
{
    Phone_Reset(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if (PlayerInCall[playerid] != INVALID_PLAYER_ID)
    {
        Phone_Hangup(playerid);
    }
    Phone_Reset(playerid);
    return 1;
}

