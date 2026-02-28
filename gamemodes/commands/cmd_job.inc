/*
 *  Vibe Roleplay - Job Commands
 *  File: commands/cmd_job.inc
 */

#if defined _cmd_job_included
    #endinput
#endif
#define _cmd_job_included

CMD:job(playerid, params[])
{
    GUARD_READY(playerid);
    Job_ShowMenu(playerid);
    return 1;
}

CMD:duty(playerid, params[])
{
    GUARD_READY(playerid);

    if (_:PlayerJob[playerid] == _:JOB_NONE)
    {
        SendErrorMessage(playerid, "Kamu tidak memiliki pekerjaan.");
        return 1;
    }

    PlayerOnDuty[playerid] = !PlayerOnDuty[playerid];

    if (PlayerOnDuty[playerid])
    {
        SendSuccessMessage(playerid, "Kamu mulai bekerja. Selamat bekerja!");
    }
    else
    {
        SendInfoMessage(playerid, "Kamu berhenti bekerja.");
    }

    return 1;
}

CMD:quitjob(playerid, params[])
{
    GUARD_READY(playerid);
    Job_Quit(playerid);
    return 1;
}

