/*
 *  Vibe Roleplay - Color Definitions
 *  File: config/colors.inc
 *
 *  Warna untuk chat, dialog, dan UI.
 *  Format: 0xRRGGBBAA (untuk SendClientMessage)
 *  Embedded: {RRGGBB} (untuk dialog/textdraw)
 */

#if defined _colors_included
    #endinput
#endif
#define _colors_included

// ============================================================================
//  Primary Colors (SendClientMessage format - 0xRRGGBBAA)
// ============================================================================

#define COLOR_WHITE             0xFFFFFFFF
#define COLOR_BLACK             0x000000FF
#define COLOR_GREY              0xAFAFAFFF
#define COLOR_LIGHT_GREY        0xD0D0D0FF

// Server branding
#define COLOR_PRIMARY           0x5B8CFFFF  // Soft blue — primary accent
#define COLOR_SECONDARY         0x9B7CFFFF  // Soft purple — secondary accent

// Functional colors
#define COLOR_SUCCESS           0x4CAF50FF  // Green
#define COLOR_ERROR             0xE74C3CFF  // Red
#define COLOR_WARNING           0xF39C12FF  // Orange/amber
#define COLOR_INFO              0x3498DBFF  // Blue

// Chat & roleplay
#define COLOR_SERVER            0x5B8CFFFF  // Same as primary
#define COLOR_OOC               0xB4B4B4FF  // Light grey for OOC
#define COLOR_ACTION            0xC2A2DAFF  // Purple for /me, /do

// ============================================================================
//  Embedded Colors (untuk dialog strings - {RRGGBB})
// ============================================================================

#define EC_WHITE                "{FFFFFF}"
#define EC_GREY                 "{AFAFAF}"
#define EC_LIGHT_GREY           "{D0D0D0}"
#define EC_PRIMARY              "{5B8CFF}"
#define EC_SECONDARY            "{9B7CFF}"
#define EC_SUCCESS              "{4CAF50}"
#define EC_ERROR                "{E74C3C}"
#define EC_WARNING              "{F39C12}"
#define EC_INFO                 "{3498DB}"
