/*
 *  Vibe Roleplay - Name Validator
 *  File: utils/name_validator.inc
 *
 *  Validasi nama roleplay menggunakan Pawn.Regex.
 *  Format yang diterima: Nama_Belakang (contoh: Denmas_Molano)
 */

#if defined _name_validator_included
    #endinput
#endif
#define _name_validator_included

// ============================================================================
//  Constants
// ============================================================================

#define MIN_RP_NAME_LENGTH      3       // Minimal panjang nama (contoh: A_B)
#define MAX_RP_NAME_LENGTH      24      // Maksimal panjang nama SA-MP

// ============================================================================
//  Variables
// ============================================================================

static Regex:g_RegexRPName = Regex:0;

// ============================================================================
//  Functions
// ============================================================================

stock NameValidator_Init()
{
    // Pattern: Huruf kapital di awal, diikuti huruf kecil, underscore, kapital lagi, huruf kecil.
    // Contoh valid: Denmas_Molano, John_Smith, Ana_Maria
    // Contoh invalid: denmas_molano, DENMAS_MOLANO, Denmas, DenmasMolano, D_M
    g_RegexRPName = Regex_New("^[A-Z][a-z]{1,}_{1}[A-Z][a-z]{1,}$");
    
    if (g_RegexRPName == Regex:0)
    {
        printf("[ERROR] Gagal membuat regex untuk validasi nama RP!");
        return 0;
    }
    
    printf("[NAME VALIDATOR] Regex pattern loaded successfully.");
    return 1;
}

stock NameValidator_Destroy()
{
    if (g_RegexRPName != Regex:0)
    {
        Regex_Delete(g_RegexRPName);
        g_RegexRPName = Regex:0;
    }
    return 1;
}

stock bool:IsValidRoleplayName(const name[])
{
    if (isnull(name))
        return false;
    
    if (strlen(name) < MIN_RP_NAME_LENGTH)
        return false;
    
    if (g_RegexRPName == Regex:0)
        return false;

    return Regex_Check(name, g_RegexRPName) ? true : false;
}

stock FormatRPName(const input[], output[], maxsize)
{
    // Ganti underscore dengan spasi untuk tampilan
    if (isnull(input))
    {
        output[0] = EOS;
        return 0;
    }
    
    format(output, maxsize, "%s", input);
    
    for (new i = 0; output[i] != EOS && i < maxsize; i++)
    {
        if (output[i] == '_')
            output[i] = ' ';
    }
    return 1;
}
