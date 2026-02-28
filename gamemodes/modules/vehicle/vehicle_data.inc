/*
 *  Vibe Roleplay - Vehicle Data
 *  File: modules/vehicle/vehicle_data.inc
 */

#if defined _vehicle_data_included
    #endinput
#endif
#define _vehicle_data_included

#define MAX_VEHICLES_DB         1000
#define MAX_FUEL                100.0
#define FUEL_CONSUMPTION_RATE   0.5
#define FUEL_PRICE_PER_LITER    10

enum E_VEHICLE_DATA
{
    vID,
    vModel,
    vOwnerID,
    vOwnerName[MAX_PLAYER_NAME],
    Float:vSpawnX,
    Float:vSpawnY,
    Float:vSpawnZ,
    Float:vSpawnA,
    vColor1,
    vColor2,
    Float:vFuel,
    vLocked,
    vEngine,
    vLights,
    Float:vHealth,
    Float:vMileage,
    vPlate[32],
    vFaction,
    vJob,
    vPrice,
    bool:vSpawned,
    vVehicleID,
    vInterior,
    vVirtualWorld
};

new VehicleData[MAX_VEHICLES_DB][E_VEHICLE_DATA];
new Iterator:Vehicles<MAX_VEHICLES_DB>;

new PlayerVehicleID[MAX_PLAYERS] = {-1, ...};
new LastVehicleUsed[MAX_PLAYERS] = {-1, ...};

stock GetVehicleDataID(vehicleid)
{
    if (vehicleid < 1 || vehicleid >= MAX_VEHICLES)
        return -1;

    foreach(new i : Vehicles)
    {
        if (VehicleData[i][vSpawned] && VehicleData[i][vVehicleID] == vehicleid)
            return i;
    }
    return -1;
}

stock GetPlayerVehicleDataID(playerid)
{
    if (!IsPlayerConnected(playerid))
        return -1;

    return PlayerVehicleID[playerid];
}

stock IsVehicleOwner(playerid, dataid)
{
    if (dataid < 0 || dataid >= MAX_VEHICLES_DB)
        return 0;

    if (!Iter_Contains(Vehicles, dataid))
        return 0;

    return (VehicleData[dataid][vOwnerID] == PlayerData[playerid][pID]);
}

stock GetFreeVehicleDataSlot()
{
    for (new i = 0; i < MAX_VEHICLES_DB; i++)
    {
        if (!Iter_Contains(Vehicles, i))
            return i;
    }
    return -1;
}

stock ResetVehicleData(dataid)
{
    if (dataid < 0 || dataid >= MAX_VEHICLES_DB)
        return 0;

    VehicleData[dataid][vID] = 0;
    VehicleData[dataid][vModel] = 0;
    VehicleData[dataid][vOwnerID] = 0;
    VehicleData[dataid][vOwnerName][0] = EOS;
    VehicleData[dataid][vSpawnX] = 0.0;
    VehicleData[dataid][vSpawnY] = 0.0;
    VehicleData[dataid][vSpawnZ] = 0.0;
    VehicleData[dataid][vSpawnA] = 0.0;
    VehicleData[dataid][vColor1] = 0;
    VehicleData[dataid][vColor2] = 0;
    VehicleData[dataid][vFuel] = MAX_FUEL;
    VehicleData[dataid][vLocked] = 0;
    VehicleData[dataid][vEngine] = 0;
    VehicleData[dataid][vLights] = 0;
    VehicleData[dataid][vHealth] = 1000.0;
    VehicleData[dataid][vMileage] = 0.0;
    VehicleData[dataid][vPlate][0] = EOS;
    VehicleData[dataid][vFaction] = 0;
    VehicleData[dataid][vJob] = 0;
    VehicleData[dataid][vPrice] = 0;
    VehicleData[dataid][vSpawned] = false;
    VehicleData[dataid][vVehicleID] = INVALID_VEHICLE_ID;
    VehicleData[dataid][vInterior] = 0;
    VehicleData[dataid][vVirtualWorld] = 0;
    return 1;
}
