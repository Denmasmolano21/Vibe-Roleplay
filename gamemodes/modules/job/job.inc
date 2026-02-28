/*
 *  Vibe Roleplay - Job System
 *  File: modules/job/job.inc
 */

#if defined _job_included
    #endinput
#endif
#define _job_included

#include <YSI_Coding/y_hooks>
#include <YSI_Data/y_iterate>

#define MAX_JOBS            20
#define MAX_JOB_NAME        32
#define MAX_JOB_DESC        128

enum E_JOB_TYPE
{
    JOB_NONE,
    JOB_TRUCKER,
    JOB_TAXI,
    JOB_BUS_DRIVER,
    JOB_MECHANIC,
    JOB_MEDIC,
    JOB_PIZZA_BOY,
    JOB_SWEEPER,
    JOB_MINER
}

enum E_JOB_DATA
{
    jobID,
    jobName[MAX_JOB_NAME],
    jobDesc[MAX_JOB_DESC],
    jobSalary,
    jobMinLevel,
    Float:jobLocationX,
    Float:jobLocationY,
    Float:jobLocationZ,
    jobPickupID,
    Text3D:jobLabel
}

new JobData[][E_JOB_DATA] = {
    {_:JOB_TRUCKER, "Trucker", "Antar barang ke seluruh San Andreas", 500, 1, 2200.0, -2298.0, 13.5},
    {_:JOB_TAXI, "Taxi Driver", "Antar penumpang ke tujuan mereka", 300, 1, 1744.3, -1862.5, 13.5},
    {_:JOB_BUS_DRIVER, "Bus Driver", "Antar penumpang dengan bus", 400, 2, 1809.0, -1905.0, 13.5},
    {_:JOB_MECHANIC, "Mechanic", "Perbaiki kendaraan pemain", 350, 1, 2064.0, -1831.0, 13.5},
    {_:JOB_MEDIC, "Medic", "Bantu pemain yang terluka", 450, 3, 1172.0, -1323.0, 15.4},
    {_:JOB_PIZZA_BOY, "Pizza Boy", "Antar pizza ke pelanggan", 250, 1, 2105.0, -1806.0, 13.5},
    {_:JOB_SWEEPER, "Street Sweeper", "Bersihkan jalanan kota", 200, 1, 1610.0, -1893.0, 13.5},
    {_:JOB_MINER, "Miner", "Tambang material berharga", 600, 5, 589.0, 869.0, -43.0}
};

new E_JOB_TYPE:PlayerJob[MAX_PLAYERS];
new bool:PlayerOnDuty[MAX_PLAYERS];

stock Job_ShowMenu(playerid)
{
    new caption[64];
    format(caption, sizeof(caption), "%s - Job Menu", SERVER_NAME);

    new info[1024];
    
    if (PlayerJob[playerid] == E_JOB_TYPE:JOB_NONE)
    {
        format(info, sizeof(info), \
            "{FFFFFF}Kamu belum memiliki pekerjaan.\n" \
            "{AFAFAF}Pilih pekerjaan yang tersedia:\n\n"
        );
        
        for (new i = 0; i < sizeof(JobData); i++)
        {
            format(info, sizeof(info), "%s{00D4FF}%s\t{FFFFFF}$%d/job (Lv.%d)\n",
                info, JobData[i][jobName], JobData[i][jobSalary], JobData[i][jobMinLevel]
            );
        }
    }
    else
    {
        new currentJobName[MAX_JOB_NAME];
        format(currentJobName, sizeof(currentJobName), "%s", JobData[_:PlayerJob[playerid]][jobName]);
        
        format(info, sizeof(info), \
            "{FFFFFF}Pekerjaan: {00D4FF}%s\n" \
            "{FFFFFF}Status: %s\n\n" \
            "{00D4FF}Start Duty\t{FFFFFF}Mulai bekerja\n" \
            "{00D4FF}Stop Duty\t{FFFFFF}Berhenti bekerja\n" \
            "{00D4FF}Quit Job\t{FFFFFF}Resign dari pekerjaan\n" \
            "{00D4FF}Job Info\t{FFFFFF}Info pekerjaan",
            currentJobName, PlayerOnDuty[playerid] ? ("{00FF00}On Duty") : ("{FF0000}Off Duty")
        );
    }

    ShowPlayerDialog(playerid, DIALOG_JOB_MENU, DIALOG_STYLE_TABLIST,
        caption, info, "Pilih", "Tutup");
    return 1;
}

stock Job_Accept(playerid, jobid)
{
    if (jobid < 0 || jobid >= sizeof(JobData))
        return 0;

    if (PlayerData[playerid][pLevel] < JobData[jobid][jobMinLevel])
    {
        new msg[128];
        format(msg, sizeof(msg), "Level minimum untuk job ini: %d", JobData[jobid][jobMinLevel]);
        SendErrorMessage(playerid, msg);
        return 0;
    }

    PlayerJob[playerid] = E_JOB_TYPE:jobid;
    
    new msg[128];
    format(msg, sizeof(msg), "Selamat! Kamu sekarang bekerja sebagai %s", JobData[jobid][jobName]);
    SendSuccessMessage(playerid, msg);
    SendInfoMessage(playerid, "Gunakan /job untuk mulai bekerja.");
    
    return 1;
}

stock Job_Quit(playerid)
{
    if (PlayerJob[playerid] == E_JOB_TYPE:JOB_NONE)
    {
        SendErrorMessage(playerid, "Kamu tidak memiliki pekerjaan.");
        return 0;
    }

    if (PlayerOnDuty[playerid])
    {
        SendErrorMessage(playerid, "Stop duty terlebih dahulu.");
        return 0;
    }

    new currentJobName[MAX_JOB_NAME];
    format(currentJobName, sizeof(currentJobName), "%s", JobData[_:PlayerJob[playerid]][jobName]);
    
    PlayerJob[playerid] = E_JOB_TYPE:JOB_NONE;
    
    new msg[128];
    format(msg, sizeof(msg), "Kamu resign dari pekerjaan %s", currentJobName);
    SendInfoMessage(playerid, msg);
    
    return 1;
}

hook OnPlayerConnect(playerid)
{
    PlayerJob[playerid] = E_JOB_TYPE:JOB_NONE;
    PlayerOnDuty[playerid] = false;
    return 1;
}

hook OnGameModeInit()
{
    for (new i = 0; i < sizeof(JobData); i++)
    {
        JobData[i][jobPickupID] = CreateDynamicPickup(1275, 1, 
            JobData[i][jobLocationX], JobData[i][jobLocationY], JobData[i][jobLocationZ], 0, 0);

        new labelText[256];
        format(labelText, sizeof(labelText), \
            "{00D4FF}%s\n" \
            "{FFFFFF}%s\n" \
            "{00FF00}Salary: $%d\n" \
            "{AFAFAF}/job untuk info",
            JobData[i][jobName], JobData[i][jobDesc], JobData[i][jobSalary]
        );
        JobData[i][jobLabel] = CreateDynamic3DTextLabel(labelText, COLOR_WHITE, 
            JobData[i][jobLocationX], JobData[i][jobLocationY], JobData[i][jobLocationZ] + 0.5, 10.0);
    }
    
    printf("[JOB] Job system loaded. Total jobs: %d", sizeof(JobData));
    return 1;
}

