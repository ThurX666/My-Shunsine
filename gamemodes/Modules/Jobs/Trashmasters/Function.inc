#include <YSI\y_hooks>
hook OnGameModeInit()
{
    VehicleTrashmaster[0] = AddStaticVehicle(408,2118.483,-2078.253,13.546,141.301,44,44);
    VehicleTrashmaster[1] = AddStaticVehicle(408,2126.990,-2084.031,13.546,136.226,44,44);
    VehicleTrashmaster[2] = AddStaticVehicle(408,2134.713,-2090.880,13.546,134.353,44,44);
    // VehicleTrashmaster[3] = AddStaticVehicle(408,2144.713,-2090.880,13.546,134.353,44,44);
}



IsVehicleTrashmaster(vehicleid)
{
    for (new i = 0; i != 3; i ++) if(VehicleTrashmaster[i] == vehicleid) {
        return 1;
    }
    return 0;
}

Garbage_Create(playerid, type)
{
    for (new i = 0; i != MAX_GARBAGE_BINS; i ++) if(!GarbageData[i][garbageExists])
    {
        switch (type) {
            case 1: GarbageData[i][garbageModel] = 1236;
            case 2: GarbageData[i][garbageModel] = 1300;
        }
        GarbageData[i][garbageExists] = true;
        GarbageData[i][garbageCapacity] = 0;

        GetPlayerPos(playerid, GarbageData[i][garbagePos][0], GarbageData[i][garbagePos][1], GarbageData[i][garbagePos][2]);
        GetPlayerFacingAngle(playerid, GarbageData[i][garbagePos][3]);

        switch (type) {
            case 1: {
                GarbageData[i][garbagePos][0] = GarbageData[i][garbagePos][0] + (1.8 * floatsin(-GarbageData[i][garbagePos][3], degrees));
                GarbageData[i][garbagePos][1] = GarbageData[i][garbagePos][1] + (1.8 * floatcos(-GarbageData[i][garbagePos][3], degrees));
            }
            case 2: {
                GarbageData[i][garbagePos][0] = GarbageData[i][garbagePos][0] + (1.0 * floatsin(-GarbageData[i][garbagePos][3], degrees));
                GarbageData[i][garbagePos][1] = GarbageData[i][garbagePos][1] + (1.0 * floatcos(-GarbageData[i][garbagePos][3], degrees));
            }
        }
        GarbageData[i][garbageInterior] = GetPlayerInterior(playerid);
        GarbageData[i][garbageWorld] = GetPlayerVirtualWorld(playerid);

        Garbage_Refresh(i);
        mysql_tquery(g_SQL, "INSERT INTO `garbage` (`garbageCapacity`) VALUES(0)", "OnGarbageCreated", "d", i);
        return i;
    }
    return -1;
}

Garbage_Delete(garbageid)
{
    if(garbageid != -1 && GarbageData[garbageid][garbageExists])
    {
        new
            string[64];

        format(string, sizeof(string), "DELETE FROM `garbage` WHERE `garbageID` = '%d'", GarbageData[garbageid][garbageID]);
        mysql_tquery(g_SQL, string);

        if(IsValidDynamicObject(GarbageData[garbageid][garbageObject]))
            DestroyDynamicObject(GarbageData[garbageid][garbageObject]);

        GarbageData[garbageid][garbageExists] = false;
        GarbageData[garbageid][garbageCapacity] = 0;
        GarbageData[garbageid][garbageID] = 0;
        GarbageData[garbageid][garbageObject] = INVALID_STREAMER_ID;
    }
    return 1;
}

Garbage_Nearest(playerid)
{
    for (new i = 0; i != MAX_GARBAGE_BINS; i ++) if(GarbageData[i][garbageExists] && IsPlayerInRangeOfPoint(playerid, 5.0, GarbageData[i][garbagePos][0], GarbageData[i][garbagePos][1], GarbageData[i][garbagePos][2]))
    {
        if(GetPlayerInterior(playerid) == GarbageData[i][garbageInterior] && GetPlayerVirtualWorld(playerid) == GarbageData[i][garbageWorld])
        return i;
    }
    return -1;
}

Garbage_Refresh(garbageid)
{
    if(garbageid != -1 && GarbageData[garbageid][garbageExists])
    {
        if(!IsValidDynamicObject(GarbageData[garbageid][garbageObject])) GarbageData[garbageid][garbageObject] = CreateDynamicObject(GarbageData[garbageid][garbageModel], GarbageData[garbageid][garbagePos][0], GarbageData[garbageid][garbagePos][1], (GarbageData[garbageid][garbageModel] == 1236) ? (GarbageData[garbageid][garbagePos][2] - 0.4) : (GarbageData[garbageid][garbagePos][2] - 0.6), 0.0, 0.0, GarbageData[garbageid][garbagePos][3], GarbageData[garbageid][garbageWorld], GarbageData[garbageid][garbageInterior]);
        Garbage_ObjectUpdate(garbageid);
    }
    return 1;
}

Garbage_ObjectUpdate(garbageid) {
    new objectid = GarbageData[garbageid][garbageObject];

    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_X, GarbageData[garbageid][garbagePos][0]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Y, GarbageData[garbageid][garbagePos][1]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Z, (GarbageData[garbageid][garbageModel] == 1236) ? (GarbageData[garbageid][garbagePos][2] - 0.4) : (GarbageData[garbageid][garbagePos][2] - 0.6));
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Z, GarbageData[garbageid][garbagePos][3]);

    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_WORLD_ID, GarbageData[garbageid][garbageWorld]);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_INTERIOR_ID, GarbageData[garbageid][garbageInterior]);
    return 1;
}

Garbage_Save(garbageid)
{
    new
        query[300];

    format(query, sizeof(query), "UPDATE `garbage` SET `garbageModel` = '%d', `garbageCapacity` = '%d', `garbageX` = '%.4f', `garbageY` = '%.4f', `garbageZ` = '%.4f', `garbageA` = '%.4f', `garbageInterior` = '%d', `garbageWorld` = '%d' WHERE `garbageID` = '%d'",
        GarbageData[garbageid][garbageModel],
        GarbageData[garbageid][garbageCapacity],
        GarbageData[garbageid][garbagePos][0],
        GarbageData[garbageid][garbagePos][1],
        GarbageData[garbageid][garbagePos][2],
        GarbageData[garbageid][garbagePos][3],
        GarbageData[garbageid][garbageInterior],
        GarbageData[garbageid][garbageWorld],
        GarbageData[garbageid][garbageID]
    );
    return mysql_tquery(g_SQL, query);
}

function Garbage_Load()
{
    new
        rows = cache_num_rows();

    for (new i = 0; i < rows; i ++) if(i < MAX_GARBAGE_BINS)
    {
        GarbageData[i][garbageExists] = true;
        cache_get_value_int(i, "garbageID", GarbageData[i][garbageID]);
        cache_get_value_int(i, "garbageModel", GarbageData[i][garbageModel]);
        cache_get_value_int(i, "garbageCapacity", GarbageData[i][garbageCapacity]);
        cache_get_value_float(i, "garbageX", GarbageData[i][garbagePos][0]);
        cache_get_value_float(i, "garbageY", GarbageData[i][garbagePos][1]);
        cache_get_value_float(i, "garbageZ", GarbageData[i][garbagePos][2]);
        cache_get_value_float(i, "garbageA", GarbageData[i][garbagePos][3]);
        cache_get_value_int(i, "garbageInterior", GarbageData[i][garbageInterior]);
        cache_get_value_int(i, "garbageWorld", GarbageData[i][garbageWorld]);

        Garbage_Refresh(i);
    }
    printf("*** [Database: Loaded] garbage data (%d count).", rows);
    return 1;
}

function OnGarbageCreated(garbageid)
{
    if(garbageid == -1 || !GarbageData[garbageid][garbageExists])
        return 0;

    GarbageData[garbageid][garbageID] = cache_insert_id();
    Garbage_Save(garbageid);

    return 1;
}