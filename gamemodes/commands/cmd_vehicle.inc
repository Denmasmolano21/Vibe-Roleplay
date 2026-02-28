/*
 *  Vibe Roleplay - Vehicle Commands
 *  File: commands/cmd_vehicle.inc
 */

#if defined _cmd_vehicle_included
    #endinput
#endif
#define _cmd_vehicle_included

// VEHICLE MENU - USER FRIENDLY INTERFACE

CMD:v(playerid, params[])
{
    GUARD_READY(playerid);

    new caption[64];
    format(caption, sizeof(caption), "%s - Vehicle Menu", SERVER_NAME);

    new info[768];
    format(info, sizeof(info), \
        "{FFFFFF}Selamat datang di Vehicle Menu\n" \
        "{AFAFAF}Pilih opsi yang ingin kamu gunakan:\n\n" \
        "{00D4FF}My Vehicles\t{FFFFFF}Lihat kendaraan kamu\n" \
        "{00D4FF}Engine\t\t{FFFFFF}Nyalakan/matikan mesin\n" \
        "{00D4FF}Lights\t\t{FFFFFF}Nyalakan/matikan lampu\n" \
        "{00D4FF}Lock/Unlock\t{FFFFFF}Kunci/buka kendaraan\n" \
        "{00D4FF}Park\t\t{FFFFFF}Parkir kendaraan di sini\n" \
        "{00D4FF}Refuel\t\t{FFFFFF}Isi bensin kendaraan\n" \
        "{00D4FF}Trunk\t\t{FFFFFF}Buka bagasi kendaraan\n" \
        "{00D4FF}Hood\t\t{FFFFFF}Buka kap mesin"
    );

    ShowPlayerDialog(playerid, DIALOG_VEHICLE_MENU, DIALOG_STYLE_TABLIST,
        caption, info, "Pilih", "Tutup");
    return 1;
}

CMD:engine(playerid, params[])
{
    GUARD_READY(playerid);

    if (!IsPlayerInAnyVehicle(playerid))
    {
        SendErrorMessage(playerid, "Kamu harus berada di dalam kendaraan.");
        return 1;
    }

    if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
    {
        SendErrorMessage(playerid, "Kamu harus menjadi driver.");
        return 1;
    }

    new vehicleid = GetPlayerVehicleID(playerid);
    new dataid = GetVehicleDataID(vehicleid);

    if (dataid == -1)
    {
        SendErrorMessage(playerid, "Kendaraan ini tidak terdaftar.");
        return 1;
    }

    Vehicle_ToggleEngine(playerid, dataid);
    return 1;
}

CMD:lights(playerid, params[])
{
    GUARD_READY(playerid);

    if (!IsPlayerInAnyVehicle(playerid))
    {
        SendErrorMessage(playerid, "Kamu harus berada di dalam kendaraan.");
        return 1;
    }

    new vehicleid = GetPlayerVehicleID(playerid);
    new dataid = GetVehicleDataID(vehicleid);

    if (dataid == -1)
    {
        SendErrorMessage(playerid, "Kendaraan ini tidak terdaftar.");
        return 1;
    }

    Vehicle_ToggleLights(playerid, dataid);
    return 1;
}

CMD:lock(playerid, params[])
{
    GUARD_READY(playerid);

    new dataid = LastVehicleUsed[playerid];
    if (dataid == -1)
    {
        SendErrorMessage(playerid, "Kamu belum menggunakan kendaraan apapun.");
        return 1;
    }

    if (!IsVehicleOwner(playerid, dataid))
    {
        SendErrorMessage(playerid, "Ini bukan kendaraan kamu.");
        return 1;
    }

    new vehicleid = VehicleData[dataid][vVehicleID];
    if (!IsPlayerInRangeOfVehicle(playerid, vehicleid, 5.0))
    {
        SendErrorMessage(playerid, "Kamu terlalu jauh dari kendaraan.");
        return 1;
    }

    Vehicle_ToggleLock(playerid, dataid);
    return 1;
}

CMD:park(playerid, params[])
{
    GUARD_READY(playerid);

    if (!IsPlayerInAnyVehicle(playerid))
    {
        SendErrorMessage(playerid, "Kamu harus berada di dalam kendaraan.");
        return 1;
    }

    if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
    {
        SendErrorMessage(playerid, "Kamu harus menjadi driver.");
        return 1;
    }

    new vehicleid = GetPlayerVehicleID(playerid);
    new dataid = GetVehicleDataID(vehicleid);

    if (dataid == -1)
    {
        SendErrorMessage(playerid, "Kendaraan ini tidak terdaftar.");
        return 1;
    }

    if (!IsVehicleOwner(playerid, dataid))
    {
        SendErrorMessage(playerid, "Ini bukan kendaraan kamu.");
        return 1;
    }

    Vehicle_Park(playerid, dataid);
    return 1;
}

CMD:myvehicles(playerid, params[])
{
    GUARD_READY(playerid);

    new count = 0;
    new info[2048];
    format(info, sizeof(info), "{00D4FF}Model\t{00D4FF}Plate\t{00D4FF}Fuel\t{00D4FF}Status\n");

    foreach(new i : Vehicles)
    {
        if (VehicleData[i][vOwnerID] == PlayerData[playerid][pID])
        {
            new modelName[32];
            GetVehicleModelName(VehicleData[i][vModel], modelName, sizeof(modelName));

            new status[16];
            if (VehicleData[i][vSpawned])
                format(status, sizeof(status), "{00FF00}Spawned");
            else
                format(status, sizeof(status), "{FF0000}Despawned");

            format(info, sizeof(info), "%s{FFFFFF}%s\t{AFAFAF}%s\t{FFFFFF}%.1f\t%s\n",
                info, modelName, VehicleData[i][vPlate], VehicleData[i][vFuel], status);
            count++;
        }
    }

    if (count == 0)
    {
        SendInfoMessage(playerid, "Kamu belum memiliki kendaraan.");
        return 1;
    }

    new caption[64];
    format(caption, sizeof(caption), "%s - My Vehicles (%d)", SERVER_NAME, count);

    ShowPlayerDialog(playerid, DIALOG_VEHICLE_LIST, DIALOG_STYLE_TABLIST_HEADERS,
        caption, info, "Pilih", "Tutup");
    return 1;
}

