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

#include <Pawn.Regex>

// Pattern: Huruf kapital di awal, diikuti huruf kecil, underscore, kapital lagi, huruf kecil.
// Contoh valid: Denmas_Molano, John_Smith, Ana_Maria
// Contoh invalid: denmas_molano, DENMAS_MOLANO, Denmas, DenmasMolano, D_M
static Regex:g_RegexRPName;

stock NameValidator_Init()
{
    g_RegexRPName = Regex_New("^[A-Z][a-z]{1,}_{1}[A-Z][a-z]{1,}$");
    if (g_RegexRPName == Regex:0)
    {
        printf("[ERROR] Gagal membuat regex untuk validasi nama RP!");
    }
    return 1;
}

stock NameValidator_Destroy()
{
    if (g_RegexRPName != Regex:0)
    {
        Regex_Delete(g_RegexRPName);
    }
    return 1;
}

stock bool:IsValidRoleplayName(const name[])
{
    if (g_RegexRPName == Regex:0)
        return false;

    return Regex_Check(name, g_RegexRPName) ? true : false;
}
