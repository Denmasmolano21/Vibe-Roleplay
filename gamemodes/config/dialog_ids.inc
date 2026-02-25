/*
 *  Vibe Roleplay - Dialog IDs
 *  File: config/dialog_ids.inc
 *
 *  Semua dialog ID terpusat di sini agar tidak bentrok.
 *  Range: Auth (100-109), General (200-299), Admin (300-399), dst.
 */

#if defined _dialog_ids_included
    #endinput
#endif
#define _dialog_ids_included

// ============================================================================
//  Auth Dialogs (100 - 109)
// ============================================================================

#define DIALOG_REGISTER             100
#define DIALOG_REGISTER_CONFIRM     101
#define DIALOG_LOGIN                102

// ============================================================================
//  Death/Spawn Dialogs (103 - 109)
// ============================================================================

#define DIALOG_DEATH                103
#define DIALOG_STATS                104

// ============================================================================
//  General Dialogs (200 - 299)
// ============================================================================

#define DIALOG_HELP                 200
#define DIALOG_RULES                201

// ============================================================================
//  Admin Dialogs (300 - 399)
// ============================================================================

#define DIALOG_ADMIN_MENU           300
#define DIALOG_ADMIN_PLAYER_LIST    301
