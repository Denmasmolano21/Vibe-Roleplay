/*
 *  Vibe Roleplay - Vehicle Core
 *  File: modules/vehicle/vehicle_core.inc
 */

#if defined _vehicle_core_included
    #endinput
#endif
#define _vehicle_core_included

#include <YSI_Coding/y_hooks>
#include <YSI_Coding/y_timers>
#include <YSI_Data/y_iterate>
#include "modules/vehicle/vehicle_data.inc"

stock Vehicle_Spawn(dataid)
{
    if (dataid < 0 || dataid >= MAX_VEHICLES_DB)
        return 0;

    if (!Iter_Contains(Vehicles, dataid))
        return 0;

    if (VehicleData[dataid][vSpawned])
        Vehicle_Destroy(dataid);

    new vehicleid = CreateVehicle(
        VehicleData[dataid][vModel],
        VehicleData[dataid][vSpawnX],
        VehicleData[dataid][vSpawnY],
        VehicleData[dataid][vSpawnZ],
        VehicleData[dataid][vSpawnA],
        VehicleData[dataid][vColor1],
        VehicleData[dataid][vColor2],
        -1
    );

    if (vehicleid == INVALID_VEHICLE_ID)
        return 0;

    VehicleData[dataid][vVehicleID] = vehicleid;
    VehicleData[dataid][vSpawned] = true;

    SetVehicleHealth(vehicleid, VehicleData[dataid][vHealth]);
    SetVehicleNumberPlate(vehicleid, VehicleData[dataid][vPlate]);
    LinkVehicleToInterior(vehicleid, VehicleData[dataid][vInterior]);
    SetVehicleVirtualWorld(vehicleid, VehicleData[dataid][vVirtualWorld]);

    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(vehicleid, VehicleData[dataid][vEngine], VehicleData[dataid][vLights], alarm, VehicleData[dataid][vLocked], bonnet, boot, objective);

    return vehicleid;
}

stock Vehicle_Destroy(dataid)
{
    if (dataid < 0 || dataid >= MAX_VEHICLES_DB)
        return 0;

    if (!VehicleData[dataid][vSpawned])
        return 0;

    if (VehicleData[dataid][vVehicleID] != INVALID_VEHICLE_ID)
    {
        DestroyVehicle(VehicleData[dataid][vVehicleID]);
        VehicleData[dataid][vVehicleID] = INVALID_VEHICLE_ID;
    }

    VehicleData[dataid][vSpawned] = false;
    return 1;
}

stock Vehicle_Save(dataid)
{
    if (dataid < 0 || dataid >= MAX_VEHICLES_DB)
        return 0;

    if (!Iter_Contains(Vehicles, dataid))
        return 0;

    if (VehicleData[dataid][vSpawned] && VehicleData[dataid][vVehicleID] != INVALID_VEHICLE_ID)
    {
        GetVehiclePos(VehicleData[dataid][vVehicleID], 
            VehicleData[dataid][vSpawnX],
            VehicleData[dataid][vSpawnY],
            VehicleData[dataid][vSpawnZ]
        );
        GetVehicleZAngle(VehicleData[dataid][vVehicleID], VehicleData[dataid][vSpawnA]);
        GetVehicleHealth(VehicleData[dataid][vVehicleID], VehicleData[dataid][vHealth]);
    }

    new query[1024];
    mysql_format(g_MySQL, query, sizeof(query),
        "UPDATE `vehicles` SET \
            `model` = %d, \
            `owner_id` = %d, \
            `spawn_x` = %f, \
            `spawn_y` = %f, \
            `spawn_z` = %f, \
            `spawn_a` = %f, \
            `color1` = %d, \
            `color2` = %d, \
            `fuel` = %f, \
            `locked` = %d, \
            `health` = %f, \
            `mileage` = %f, \
            `plate` = '%e', \
            `faction` = %d, \
            `job` = %d \
        WHERE `id` = %d",
        VehicleData[dataid][vModel],
        VehicleData[dataid][vOwnerID],
        VehicleData[dataid][vSpawnX],
        VehicleData[dataid][vSpawnY],
        VehicleData[dataid][vSpawnZ],
        VehicleData[dataid][vSpawnA],
        VehicleData[dataid][vColor1],
        VehicleData[dataid][vColor2],
        VehicleData[dataid][vFuel],
        VehicleData[dataid][vLocked],
        VehicleData[dataid][vHealth],
        VehicleData[dataid][vMileage],
        VehicleData[dataid][vPlate],
        VehicleData[dataid][vFaction],
        VehicleData[dataid][vJob],
        VehicleData[dataid][vID]
    );
    mysql_tquery(g_MySQL, query);
    return 1;
}

stock Vehicle_Create(playerid, modelid, Float:x, Float:y, Float:z, Float:a, color1, color2, price = 0)
{
    new dataid = GetFreeVehicleDataSlot();
    if (dataid == -1)
    {
        SendErrorMessage(playerid, "Slot kendaraan penuh!");
        return -1;
    }

    ResetVehicleData(dataid);

    VehicleData[dataid][vModel] = modelid;
    VehicleData[dataid][vOwnerID] = PlayerData[playerid][pID];
    GetPlayerName(playerid, VehicleData[dataid][vOwnerName], MAX_PLAYER_NAME);
    VehicleData[dataid][vSpawnX] = x;
    VehicleData[dataid][vSpawnY] = y;
    VehicleData[dataid][vSpawnZ] = z;
    VehicleData[dataid][vSpawnA] = a;
    VehicleData[dataid][vColor1] = color1;
    VehicleData[dataid][vColor2] = color2;
    VehicleData[dataid][vFuel] = MAX_FUEL;
    VehicleData[dataid][vHealth] = 1000.0;
    VehicleData[dataid][vPrice] = price;
    format(VehicleData[dataid][vPlate], 32, "VRP-%04d", dataid);

    new query[1024];
    mysql_format(g_MySQL, query, sizeof(query),
        "INSERT INTO `vehicles` \
        (`model`, `owner_id`, `spawn_x`, `spawn_y`, `spawn_z`, `spawn_a`, `color1`, `color2`, `fuel`, `health`, `plate`, `price`) \
        VALUES (%d, %d, %f, %f, %f, %f, %d, %d, %f, %f, '%e', %d)",
        modelid, VehicleData[dataid][vOwnerID],
        x, y, z, a, color1, color2,
        VehicleData[dataid][vFuel],
        VehicleData[dataid][vHealth],
        VehicleData[dataid][vPlate],
        price
    );
    mysql_tquery(g_MySQL, query, "OnVehicleCreated", "ii", playerid, dataid);

    return dataid;
}

forward OnVehicleCreated(playerid, dataid);
public OnVehicleCreated(playerid, dataid)
{
    VehicleData[dataid][vID] = cache_insert_id();
    Iter_Add(Vehicles, dataid);
    
    Vehicle_Spawn(dataid);
    PlayerVehicleID[playerid] = dataid;

    new msg[128];
    format(msg, sizeof(msg), "Kendaraan berhasil dibuat! ID: %d", dataid);
    SendSuccessMessage(playerid, msg);
    return 1;
}

stock Vehicle_ToggleEngine(playerid, dataid)
{
    if (!VehicleData[dataid][vSpawned])
        return 0;

    new vehicleid = VehicleData[dataid][vVehicleID];
    if (vehicleid == INVALID_VEHICLE_ID)
        return 0;

    if (VehicleData[dataid][vFuel] <= 0.0)
    {
        SendErrorMessage(playerid, "Kendaraan kehabisan bensin!");
        return 0;
    }

    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

    VehicleData[dataid][vEngine] = !VehicleData[dataid][vEngine];
    SetVehicleParamsEx(vehicleid, VehicleData[dataid][vEngine], lights, alarm, doors, bonnet, boot, objective);

    new msg[128];
    if (VehicleData[dataid][vEngine])
    {
        format(msg, sizeof(msg), "* %s menyalakan mesin kendaraan.", GetPlayerNameEx(playerid));
        SendNearbyMessage(playerid, 20.0, COLOR_ACTION, msg);
    }
    else
    {
        format(msg, sizeof(msg), "* %s mematikan mesin kendaraan.", GetPlayerNameEx(playerid));
        SendNearbyMessage(playerid, 20.0, COLOR_ACTION, msg);
    }
    return 1;
}

stock Vehicle_ToggleLights(playerid, dataid)
{
    if (!VehicleData[dataid][vSpawned])
        return 0;

    new vehicleid = VehicleData[dataid][vVehicleID];
    if (vehicleid == INVALID_VEHICLE_ID)
        return 0;

    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

    VehicleData[dataid][vLights] = !VehicleData[dataid][vLights];
    SetVehicleParamsEx(vehicleid, engine, VehicleData[dataid][vLights], alarm, doors, bonnet, boot, objective);

    new msg[128];
    if (VehicleData[dataid][vLights])
        format(msg, sizeof(msg), "* %s menyalakan lampu kendaraan.", GetPlayerNameEx(playerid));
    else
        format(msg, sizeof(msg), "* %s mematikan lampu kendaraan.", GetPlayerNameEx(playerid));

    SendNearbyMessage(playerid, 20.0, COLOR_ACTION, msg);
    return 1;
}

stock Vehicle_ToggleLock(playerid, dataid)
{
    if (!VehicleData[dataid][vSpawned])
        return 0;

    new vehicleid = VehicleData[dataid][vVehicleID];
    if (vehicleid == INVALID_VEHICLE_ID)
        return 0;

    new engine, lights, alarm, doors, bonnet, boot, objective;
    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

    VehicleData[dataid][vLocked] = !VehicleData[dataid][vLocked];
    SetVehicleParamsEx(vehicleid, engine, lights, alarm, VehicleData[dataid][vLocked], bonnet, boot, objective);

    new msg[128];
    if (VehicleData[dataid][vLocked])
    {
        format(msg, sizeof(msg), "* %s mengunci kendaraan.", GetPlayerNameEx(playerid));
        SendNearbyMessage(playerid, 20.0, COLOR_ACTION, msg);
        GameTextForPlayer(playerid, "~r~LOCKED", 3000, 3);
    }
    else
    {
        format(msg, sizeof(msg), "* %s membuka kunci kendaraan.", GetPlayerNameEx(playerid));
        SendNearbyMessage(playerid, 20.0, COLOR_ACTION, msg);
        GameTextForPlayer(playerid, "~g~UNLOCKED", 3000, 3);
    }
    return 1;
}

stock Vehicle_Park(playerid, dataid)
{
    if (!VehicleData[dataid][vSpawned])
        return 0;

    new vehicleid = VehicleData[dataid][vVehicleID];
    if (vehicleid == INVALID_VEHICLE_ID)
        return 0;

    GetVehiclePos(vehicleid, 
        VehicleData[dataid][vSpawnX],
        VehicleData[dataid][vSpawnY],
        VehicleData[dataid][vSpawnZ]
    );
    GetVehicleZAngle(vehicleid, VehicleData[dataid][vSpawnA]);

    Vehicle_Save(dataid);

    SendSuccessMessage(playerid, "Kendaraan berhasil diparkir di posisi ini.");
    return 1;
}

stock Vehicle_Refuel(playerid, dataid, Float:amount)
{
    if (dataid < 0 || dataid >= MAX_VEHICLES_DB)
        return 0;

    new Float:newFuel = VehicleData[dataid][vFuel] + amount;
    if (newFuel > MAX_FUEL)
        newFuel = MAX_FUEL;

    new cost = floatround((newFuel - VehicleData[dataid][vFuel]) * FUEL_PRICE_PER_LITER);

    if (VRP_GetPlayerMoney(playerid) < cost)
    {
        SendErrorMessage(playerid, "Uang kamu tidak cukup!");
        return 0;
    }

    VehicleData[dataid][vFuel] = newFuel;
    VRP_TakePlayerMoney(playerid, cost);

    new msg[128];
    format(msg, sizeof(msg), "Kendaraan diisi bensin %.1f liter. Biaya: $%d", amount, cost);
    SendSuccessMessage(playerid, msg);
    return 1;
}

timer VehicleFuelTimer[1000]()
{
    foreach(new i : Vehicles)
    {
        if (!VehicleData[i][vSpawned])
            continue;

        if (!VehicleData[i][vEngine])
            continue;

        if (VehicleData[i][vFuel] <= 0.0)
        {
            VehicleData[i][vFuel] = 0.0;
            VehicleData[i][vEngine] = 0;

            new vehicleid = VehicleData[i][vVehicleID];
            new engine, lights, alarm, doors, bonnet, boot, objective;
            GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
            SetVehicleParamsEx(vehicleid, 0, lights, alarm, doors, bonnet, boot, objective);

            for (new p = 0; p < MAX_PLAYERS; p++)
            {
                if (IsPlayerInVehicle(p, vehicleid))
                    SendWarningMessage(p, "Kendaraan kehabisan bensin!");
            }
            continue;
        }

        VehicleData[i][vFuel] -= FUEL_CONSUMPTION_RATE / 60.0;
        if (VehicleData[i][vFuel] < 0.0)
            VehicleData[i][vFuel] = 0.0;
    }
}

stock GetPlayerNameEx(playerid)
{
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    return name;
}

stock SendNearbyMessage(playerid, Float:range, color, const message[])
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (!IsPlayerConnected(i))
            continue;

        if (GetPlayerVirtualWorld(i) != GetPlayerVirtualWorld(playerid))
            continue;

        if (GetPlayerInterior(i) != GetPlayerInterior(playerid))
            continue;

        if (IsPlayerInRangeOfPoint(i, range, x, y, z))
            SendClientMessage(i, color, message);
    }
    return 1;
}

hook OnGameModeInit()
{
    mysql_tquery(g_MySQL, "\
        CREATE TABLE IF NOT EXISTS `vehicles` (\
            `id` INT(11) NOT NULL AUTO_INCREMENT,\
            `model` INT(5) NOT NULL,\
            `owner_id` INT(11) NOT NULL DEFAULT '0',\
            `spawn_x` FLOAT NOT NULL,\
            `spawn_y` FLOAT NOT NULL,\
            `spawn_z` FLOAT NOT NULL,\
            `spawn_a` FLOAT NOT NULL,\
            `color1` INT(5) NOT NULL DEFAULT '0',\
            `color2` INT(5) NOT NULL DEFAULT '0',\
            `fuel` FLOAT NOT NULL DEFAULT '100.0',\
            `locked` INT(1) NOT NULL DEFAULT '0',\
            `health` FLOAT NOT NULL DEFAULT '1000.0',\
            `mileage` FLOAT NOT NULL DEFAULT '0.0',\
            `plate` VARCHAR(32) NOT NULL,\
            `faction` INT(5) NOT NULL DEFAULT '0',\
            `job` INT(5) NOT NULL DEFAULT '0',\
            `price` INT(11) NOT NULL DEFAULT '0',\
            `interior` INT(5) NOT NULL DEFAULT '0',\
            `virtual_world` INT(5) NOT NULL DEFAULT '0',\
            PRIMARY KEY (`id`)\
        ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;\
    ");

    repeat VehicleFuelTimer();
    printf("[VEHICLE] Vehicle system loaded.");
    return 1;
}

hook OnPlayerConnect(playerid)
{
    PlayerVehicleID[playerid] = -1;
    LastVehicleUsed[playerid] = -1;
    return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    new dataid = GetVehicleDataID(vehicleid);
    if (dataid == -1)
        return 1;

    if (VehicleData[dataid][vLocked] && !IsVehicleOwner(playerid, dataid))
    {
        ClearAnimations(playerid);
        SendErrorMessage(playerid, "Kendaraan ini terkunci!");
        return 1;
    }

    LastVehicleUsed[playerid] = dataid;
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if (newstate == PLAYER_STATE_DRIVER)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        new dataid = GetVehicleDataID(vehicleid);

        if (dataid != -1)
        {
            new msg[128];
            format(msg, sizeof(msg), "~w~Fuel: ~g~%.1f~w~/~g~%.0f", VehicleData[dataid][vFuel], MAX_FUEL);
            GameTextForPlayer(playerid, msg, 3000, 3);

            if (!VehicleData[dataid][vEngine])
                SendInfoMessage(playerid, "Gunakan /v engine untuk menyalakan mesin.");
        }
    }
    return 1;
}

stock IsPlayerInRangeOfVehicle(playerid, vehicleid, Float:range)
{
    if (vehicleid < 1 || vehicleid > MAX_VEHICLES)
        return 0;

    new Float:x, Float:y, Float:z;
    GetVehiclePos(vehicleid, x, y, z);
    return IsPlayerInRangeOfPoint(playerid, range, x, y, z);
}

stock GetVehicleModelName(modelid, name[], len = sizeof(name))
{
    new vehicleNames[][] = {
        "Landstalker", "Bravura", "Buffalo", "Linerunner", "Perennial", "Sentinel", "Dumper", "Firetruck", "Trashmaster", "Stretch",
        "Manana", "Infernus", "Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam", "Esperanto",
        "Taxi", "Washington", "Bobcat", "Mr Whoopee", "BF Injection", "Hunter", "Premier", "Enforcer", "Securicar", "Banshee",
        "Predator", "Bus", "Rhino", "Barracks", "Hotknife", "Trailer", "Previon", "Coach", "Cabbie", "Stallion",
        "Rumpo", "RC Bandit", "Romero", "Packer", "Monster", "Admiral", "Squalo", "Seasparrow", "Pizzaboy", "Tram",
        "Trailer", "Turismo", "Speeder", "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair", "Berkley's RC Van",
        "Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale", "Oceanic", "Sanchez", "Sparrow",
        "Patriot", "Quad", "Coastguard", "Dinghy", "Hermes", "Sabre", "Rustler", "ZR-350", "Walton", "Regina",
        "Comet", "BMX", "Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick", "News Chopper", "Rancher",
        "FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring", "Sandking", "Blista Compact", "Police Maverick", "Boxville", "Benson",
        "Mesa", "RC Goblin", "Hotring Racer A", "Hotring Racer B", "Bloodring Banger", "Rancher", "Super GT", "Elegant", "Journey", "Bike",
        "Mountain Bike", "Beagle", "Cropdust", "Stunt", "Tanker", "RoadTrain", "Nebula", "Majestic", "Buccaneer", "Shamal",
        "Hydra", "FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Tow Truck", "Fortune", "Cadrona", "FBI Truck", "Willard",
        "Forklift", "Tractor", "Combine", "Feltzer", "Remington", "Slamvan", "Blade", "Freight", "Streak", "Vortex",
        "Vincent", "Bullet", "Clover", "Sadler", "Firetruck", "Hustler", "Intruder", "Primo", "Cargobob", "Tampa",
        "Sunrise", "Merit", "Utility", "Nevada", "Yosemite", "Windsor", "Monster A", "Monster B", "Uranus", "Jester",
        "Sultan", "Stratum", "Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito", "Freight",
        "Trailer", "Kart", "Mower", "Duneride", "Sweeper", "Broadway", "Tornado", "AT-400", "DFT-30", "Huntley",
        "Stafford", "BF-400", "Newsvan", "Tug", "Trailer A", "Emperor", "Wayfarer", "Euros", "Hotdog", "Club",
        "Trailer B", "Trailer C", "Andromada", "Dodo", "RC Cam", "Launch", "Police Car (LSPD)", "Police Car (SFPD)", "Police Car (LVPD)", "Police Ranger",
        "Picador", "S.W.A.T. Van", "Alpha", "Phoenix", "Glendale", "Sadler", "Luggage Trailer A", "Luggage Trailer B", "Stair Trailer", "Boxville",
        "Farm Plow", "Utility Trailer"
    };

    if (modelid < 400 || modelid > 611)
    {
        format(name, len, "Unknown");
        return 0;
    }

    format(name, len, "%s", vehicleNames[modelid - 400]);
    return 1;
}
