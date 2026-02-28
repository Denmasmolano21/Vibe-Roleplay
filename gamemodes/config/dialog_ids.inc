/*
 *  Vibe Roleplay - Dialog IDs
 *  File: config/dialog_ids.inc
 */

#if defined _dialog_ids_included
    #endinput
#endif
#define _dialog_ids_included

// Auth Dialogs (100-119)
#define DIALOG_REGISTER             100
#define DIALOG_REGISTER_CONFIRM     101
#define DIALOG_LOGIN                102
#define DIALOG_DEATH                103
#define DIALOG_STATS                104

// Help & Info Dialogs (200-249)
#define DIALOG_HELP                 200
#define DIALOG_HELP_CATEGORY        201
#define DIALOG_HELP_GENERAL         202
#define DIALOG_HELP_VEHICLE         203
#define DIALOG_HELP_JOB             204
#define DIALOG_HELP_PROPERTY        205
#define DIALOG_HELP_FACTION         206
#define DIALOG_RULES                207

// Report System (250-269)
#define DIALOG_REPORT               250
#define DIALOG_ASK                  251
#define DIALOG_REPORTS_LIST         252
#define DIALOG_REPORT_VIEW          253
#define DIALOG_REPORT_REPLY         254

// Admin System (300-399)
#define DIALOG_ADMIN_MAIN           300
#define DIALOG_ADMIN_MENU           300  // Alias untuk DIALOG_ADMIN_MAIN
#define DIALOG_ADMIN_PLAYER_SELECT  301
#define DIALOG_ADMIN_ACTION_SELECT  302
#define DIALOG_ADMIN_INPUT          303
#define DIALOG_ADMIN_TELEPORT       304
#define DIALOG_ADMIN_VEHICLE        305
#define DIALOG_ADMIN_WEAPON         306
#define DIALOG_ADMIN_CONFIRM        307
#define DIALOG_ADMIN_SERVER         308
#define DIALOG_AHELP_CATEGORY       309

// Vehicle System (400-449)
#define DIALOG_VEHICLE_MENU         400
#define DIALOG_VEHICLE_LIST         401
#define DIALOG_VEHICLE_ACTIONS      402
#define DIALOG_VEHICLE_SPAWN        403
#define DIALOG_VEHICLE_COLOR1       404
#define DIALOG_VEHICLE_COLOR2       405
#define DIALOG_VEHICLE_REFUEL       406
#define DIALOG_VEHICLE_SELL         407
#define DIALOG_VEHICLE_UPGRADE      408

// Inventory System (450-499)
#define DIALOG_INVENTORY_MAIN       450
#define DIALOG_INVENTORY_USE        451
#define DIALOG_INVENTORY_DROP       452
#define DIALOG_INVENTORY_GIVE       453
#define DIALOG_INVENTORY_AMOUNT     454
#define DIALOG_INVENTORY_TARGET     455

// Phone System (500-549)
#define DIALOG_PHONE_MAIN           500
#define DIALOG_PHONE_CONTACTS       501
#define DIALOG_PHONE_CALL           502
#define DIALOG_PHONE_SMS            503
#define DIALOG_PHONE_SMS_SEND       504
#define DIALOG_PHONE_SETTINGS       505
#define DIALOG_PHONE_ADD_CONTACT    506
#define DIALOG_PHONE_EDIT_CONTACT   507

// House System (550-599)
#define DIALOG_HOUSE_MENU           550
#define DIALOG_HOUSE_BUY            551
#define DIALOG_HOUSE_SELL           552
#define DIALOG_HOUSE_UPGRADE        553
#define DIALOG_HOUSE_FURNITURE      554
#define DIALOG_HOUSE_STORAGE        555
#define DIALOG_HOUSE_SETTINGS       556
#define DIALOG_HOUSE_RENT           557

// Business System (600-649)
#define DIALOG_BUSINESS_MENU        600
#define DIALOG_BUSINESS_BUY         601
#define DIALOG_BUSINESS_SELL        602
#define DIALOG_BUSINESS_MANAGE      603
#define DIALOG_BUSINESS_PRODUCTS    604
#define DIALOG_BUSINESS_EMPLOYEES   605
#define DIALOG_BUSINESS_SAFE        606

// Job System (650-699)
#define DIALOG_JOB_MENU             650
#define DIALOG_JOB_LIST             651
#define DIALOG_JOB_INFO             652
#define DIALOG_JOB_ACCEPT           653
#define DIALOG_JOB_QUIT             654
#define DIALOG_JOB_DUTY             655

// Faction System (700-749)
#define DIALOG_FACTION_MENU         700
#define DIALOG_FACTION_LIST         701
#define DIALOG_FACTION_INFO         702
#define DIALOG_FACTION_INVITE       703
#define DIALOG_FACTION_MEMBERS      704
#define DIALOG_FACTION_RANKS        705
#define DIALOG_FACTION_SETTINGS     706


// Banking System (750-799)
#define DIALOG_ATM_MENU             750
#define DIALOG_ATM_DEPOSIT          751
#define DIALOG_ATM_WITHDRAW         752
#define DIALOG_ATM_TRANSFER         753
#define DIALOG_ATM_TRANSFER_AMOUNT  754
#define DIALOG_ATM_HISTORY          755

// Payday System (800-849)
#define DIALOG_PAYDAY_INFO          800
#define DIALOG_SALARY_INFO          801
#define DIALOG_PLAYTIME_INFO        802

// Admin Help (850-899)
#define DIALOG_ADMIN_HELP           850
