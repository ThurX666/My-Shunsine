
function LoadVehicleData()
{
	new str[128];
 	new count = cache_num_rows(), i;
	if(count > 0)
	{
		for(new z = 0; z < count; z++)
		{
			if((i = Iter_Free(VehicleData)) != cellmin)
			{
                Iter_Add(VehicleData, i);
                VehicleDataReset(i);
                cache_get_value_name_int(z, "ID", VehicleData[i][ID]);
                cache_get_value_name_int(z, "Faction", VehicleData[i][Faction]);
                cache_get_value_name_int(z, "Bisnis", VehicleData[i][Bisnis]);
                cache_get_value_name_int(z, "Workshop", VehicleData[i][Workshop]);
                cache_get_value_name_int(z, "SpawnType", VehicleData[i][SpawnType]);
                cache_get_value_name_int(z, "Model", VehicleData[i][Model]);
                cache_get_value(z, "Color", str);
                sscanf(str, "p<|>dd", VehicleData[i][Color][0], VehicleData[i][Color][1]);
                cache_get_value_name_int(z, "Paintjob", VehicleData[i][PaintJob]);
                cache_get_value_name_int(z, "Locked", VehicleData[i][Locked]);
                cache_get_value_name(z, "Plate", VehicleData[i][Plate], 52);
                cache_get_value(z, "HealthFuel", str);
                sscanf(str, "p<|>fd", VehicleData[i][Health], VehicleData[i][Fuel]);
                cache_get_value(z, "VehiclePos", str);
                sscanf(str, "p<|>ffff", VehicleData[i][Pos][0], VehicleData[i][Pos][1], 
                VehicleData[i][Pos][2], VehicleData[i][Pos][3]);
                cache_get_value(z, "IntVw", str);
                sscanf(str, "p<|>dd", VehicleData[i][Interior], VehicleData[i][Virtual]);
                cache_get_value(z, "Damage", str);
                sscanf(str, "p<|>dddd", VehicleData[i][Damage][0], VehicleData[i][Damage][1],
                VehicleData[i][Damage][2], VehicleData[i][Damage][3]);
                cache_get_value(z, "Mod", str);
                sscanf(str, "p<|>ddddddddddddddddd", VehicleData[i][Mod][0], VehicleData[i][Mod][1],
                VehicleData[i][Mod][2], VehicleData[i][Mod][3], VehicleData[i][Mod][4],
                VehicleData[i][Mod][5], VehicleData[i][Mod][6], VehicleData[i][Mod][7],
                VehicleData[i][Mod][8], VehicleData[i][Mod][9], VehicleData[i][Mod][10],
                VehicleData[i][Mod][11], VehicleData[i][Mod][12], VehicleData[i][Mod][13],
                VehicleData[i][Mod][14], VehicleData[i][Mod][15], VehicleData[i][Mod][16]);
                cache_get_value(z, "Weapon", str);
                sscanf(str, "p<|>dddd", VehicleData[i][Weapon][0], VehicleData[i][Weapon][1],
                VehicleData[i][Weapon][2], VehicleData[i][Weapon][3]);
                cache_get_value(z, "Ammo", str);
                sscanf(str, "p<|>dddd", VehicleData[i][Ammo][0], VehicleData[i][Ammo][1],
                VehicleData[i][Ammo][2], VehicleData[i][Ammo][3]);
                cache_get_value(z, "TypeAmmo", str);
                sscanf(str, "p<|>dddd", VehicleData[i][TypeAmmo][0], VehicleData[i][TypeAmmo][1],
                VehicleData[i][TypeAmmo][2], VehicleData[i][TypeAmmo][3]);
                cache_get_value(z, "Storage", str);
                sscanf(str, "p<|>dddd", VehicleData[i][Storage][0], VehicleData[i][Storage][1],
                VehicleData[i][Storage][2], VehicleData[i][Storage][3]);
                
                if(VehicleData[i][SpawnType] == 0) VehicleRespawn(i); 
            }
	    }
	    printf("*** [Database: Loaded] Vehicle data (%d count).", count);
	}
    return 1;
}

SaveVehicleData(vehicleid)
{
    if(IsValidVehicle(VehicleData[vehicleid][Vehicle])) {
        GetVehicleDamageStatus(VehicleData[vehicleid][Vehicle], VehicleData[vehicleid][Damage][0], VehicleData[vehicleid][Damage][1], VehicleData[vehicleid][Damage][2], VehicleData[vehicleid][Damage][3]);
        GetVehicleHealth(VehicleData[vehicleid][Vehicle], VehicleData[vehicleid][Health]);
        VehicleData[vehicleid][Fuel] = GetVehicleFuel(VehicleData[vehicleid][Vehicle]);
        SaveModVehicle(vehicleid);
    }
    new cQuery[5248]/*, color1, color2, paintjob*/;
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `vehicledata` SET `Faction`='%d'", VehicleData[vehicleid][Faction]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Bisnis`='%d'", cQuery, VehicleData[vehicleid][Bisnis]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Workshop`='%d'", cQuery, VehicleData[vehicleid][Workshop]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `SpawnType`='%d'", cQuery, VehicleData[vehicleid][SpawnType]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Model`='%d'", cQuery, VehicleData[vehicleid][Model]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Color`='%d|%d'", cQuery, VehicleData[vehicleid][Color][0], VehicleData[vehicleid][Color][1]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Paintjob`='%d'", cQuery, VehicleData[vehicleid][PaintJob]);
    if(VehicleData[vehicleid][Locked] == 1) mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Locked`=1", cQuery);
    else mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Locked`=0", cQuery);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Plate`='%e'", cQuery, VehicleData[vehicleid][Plate]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `HealthFuel`='%f|%d'", cQuery, VehicleData[vehicleid][Health], VehicleData[vehicleid][Fuel]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `VehiclePos`='%.4f|%.4f|%.4f|%.4f'", cQuery, VehicleData[vehicleid][Pos][0], VehicleData[vehicleid][Pos][1], VehicleData[vehicleid][Pos][2], VehicleData[vehicleid][Pos][3]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `IntVw`='%d|%d'", cQuery, VehicleData[vehicleid][Interior], VehicleData[vehicleid][Virtual]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Damage`='%d|%d|%d|%d'", cQuery, VehicleData[vehicleid][Damage][0], VehicleData[vehicleid][Damage][1], VehicleData[vehicleid][Damage][2], VehicleData[vehicleid][Damage][3]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Mod`='%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d'", cQuery, VehicleData[vehicleid][Mod][0], VehicleData[vehicleid][Mod][1],
    VehicleData[vehicleid][Mod][2], VehicleData[vehicleid][Mod][3], VehicleData[vehicleid][Mod][4],
    VehicleData[vehicleid][Mod][5], VehicleData[vehicleid][Mod][6], VehicleData[vehicleid][Mod][7],
    VehicleData[vehicleid][Mod][8], VehicleData[vehicleid][Mod][9], VehicleData[vehicleid][Mod][10],
    VehicleData[vehicleid][Mod][11], VehicleData[vehicleid][Mod][12], VehicleData[vehicleid][Mod][13],
    VehicleData[vehicleid][Mod][14], VehicleData[vehicleid][Mod][15], VehicleData[vehicleid][Mod][16]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Weapon`='%d|%d|%d|%d'", cQuery, VehicleData[vehicleid][Weapon][0], VehicleData[vehicleid][Weapon][1],
    VehicleData[vehicleid][Weapon][2], VehicleData[vehicleid][Weapon][3]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Ammo`='%d|%d|%d|%d'", cQuery, VehicleData[vehicleid][Ammo][0], VehicleData[vehicleid][Ammo][1],
    VehicleData[vehicleid][Ammo][2], VehicleData[vehicleid][Ammo][3]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `TypeAmmo`='%d|%d|%d|%d'", cQuery, VehicleData[vehicleid][TypeAmmo][0], VehicleData[vehicleid][TypeAmmo][1],
    VehicleData[vehicleid][TypeAmmo][2], VehicleData[vehicleid][TypeAmmo][3]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `Storage`='%d|%d|%d|%d'", cQuery, VehicleData[vehicleid][Storage][0], VehicleData[vehicleid][Storage][1],
    VehicleData[vehicleid][Storage][2], VehicleData[vehicleid][Storage][3]);

    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s WHERE `ID` = %d", cQuery, vehicleid);
    mysql_tquery(g_SQL, cQuery);
	return 1;
}

VehicleRespawn(vehicleid) {
    VehicleData[vehicleid][Vehicle] = AddStaticVehicleEx(VehicleData[vehicleid][Model], VehicleData[vehicleid][Pos][0], VehicleData[vehicleid][Pos][1], VehicleData[vehicleid][Pos][2], VehicleData[vehicleid][Pos][3], VehicleData[vehicleid][Color][0], VehicleData[vehicleid][Color][1], VEHICLE_RESPAWN, 1);
	if(IsValidVehicle(VehicleData[vehicleid][Vehicle]))
	{
		new plate[62];
		format(plate, sizeof(plate), "%s", VehicleData[vehicleid][Plate]);
		SetVehicleNumberPlate(VehicleData[vehicleid][Vehicle], plate);
		SetVehicleVirtualWorld(VehicleData[vehicleid][Vehicle], VehicleData[vehicleid][Virtual]);
		LinkVehicleToInterior(VehicleData[vehicleid][Vehicle], VehicleData[vehicleid][Interior]);
		
		if(VehicleData[vehicleid][Health] < 350.0) SetValidVehicleHealth(VehicleData[vehicleid][Vehicle], 350.0);
		else SetValidVehicleHealth(VehicleData[vehicleid][Vehicle], VehicleData[vehicleid][Health]);
		UpdateVehicleDamageStatus(VehicleData[vehicleid][Vehicle], VehicleData[vehicleid][Damage][0], VehicleData[vehicleid][Damage][1], VehicleData[vehicleid][Damage][2], VehicleData[vehicleid][Damage][3]);
		if(VehicleData[vehicleid][PaintJob] != -1) ChangeVehiclePaintjob(VehicleData[vehicleid][Vehicle], VehicleData[vehicleid][PaintJob]);
		for(new mod = 0; mod < MAX_MODS; mod++) if(VehicleData[vehicleid][Mod][mod]) AddVehicleComponent(VehicleData[vehicleid][Vehicle], VehicleData[vehicleid][Mod][mod]);
		if(VehicleData[vehicleid][Locked] == 1) SwitchVehicleDoors(VehicleData[vehicleid][Vehicle], true);
		else SwitchVehicleDoors(VehicleData[vehicleid][Vehicle], false);
	}
	return 1;
}

VehicleDataReset(i) {
    format(VehicleData[i][VehicleOwner], 52, "-");
    VehicleData[i][Vehicle] = INVALID_VEHICLE_ID;
	VehicleData[i][Faction] = 0;
	VehicleData[i][Bisnis] = 0;
	VehicleData[i][Workshop] = 0;
	VehicleData[i][SpawnType] = 0;
	VehicleData[i][Model] = 0;
	VehicleData[i][Color][0] = 0;
	VehicleData[i][Color][1] = 0;
	VehicleData[i][PaintJob] = 0;
	VehicleData[i][Locked] = 0;
	VehicleData[i][VehicleSpawnTime] = 0;
	for(new j = 0; j < 5; j++)
	{
		VehicleData[i][Weapon][j] = 0;
		VehicleData[i][Ammo][j] = 0;
        VehicleData[i][TypeAmmo][j] = 0;
        VehicleData[i][Storage][j] = 0;
	}
	for(new j = 0; j < MAX_MODS; j++)
		VehicleData[i][Mod][j] = 0;
	return 1;
}

VehicleData_GetID(vehicleid)
{
    if (!IsValidVehicle(vehicleid)) return -1;
    foreach (new i : VehicleData) if (VehicleData[i][Vehicle] == vehicleid) {
        return i;
    }
    return -1;
}

SaveModVehicle(vehicleid)
{
    new componentid;
    GetVehicleColor(VehicleData[vehicleid][Vehicle], VehicleData[vehicleid][Color][0], VehicleData[vehicleid][Color][1]);
    for(new mod = 0; mod < MAX_MODS; mod++)
    {
        componentid = GetVehicleComponentInSlot(VehicleData[vehicleid][Vehicle], mod);
        for(new s = 0; s < 20; s++) if(componentid == pv_spoiler[s][0]) VehicleData[vehicleid][Mod][0] = componentid;
        for(new s = 0; s < 4; s++) if(componentid == pv_bscoop[s][0]) VehicleData[vehicleid][Mod][1] = componentid;
        for(new s = 0; s < 17; s++) if(componentid == pv_roof[s][0]) VehicleData[vehicleid][Mod][2] = componentid;
        for(new s = 0; s < 21; s++) if(componentid == pv_lskirt[s][0]) VehicleData[vehicleid][Mod][3] = componentid;
        for(new s = 0; s < 2; s++) if(componentid == pv_lights[s][0]) VehicleData[vehicleid][Mod][4] = componentid;
        for(new s = 0; s < 3; s++) if(componentid == pv_nitro[s][0]) VehicleData[vehicleid][Mod][5] = componentid;
        for(new s = 0; s < 28; s++) if(componentid == pv_exhaust[s][0]) VehicleData[vehicleid][Mod][6] = componentid;
        for(new s = 0; s < 17; s++) if(componentid == pv_wheels[s][0]) VehicleData[vehicleid][Mod][7] = componentid;
        for(new s = 0; s < 1; s++) if(componentid == pv_base[s][0]) VehicleData[vehicleid][Mod][8] = componentid;
        for(new s = 0; s < 1; s++) if(componentid == pv_hydraulics[s][0]) VehicleData[vehicleid][Mod][9] = componentid;
        for(new s = 0; s < 23; s++) if(componentid == pv_fbumper[s][0]) VehicleData[vehicleid][Mod][10] = componentid;
        for(new s = 0; s < 22; s++) if(componentid == pv_rbumper[s][0]) VehicleData[vehicleid][Mod][11] = componentid;
        for(new s = 0; s < 2; s++) if(componentid == pv_bventl[s][0]) VehicleData[vehicleid][Mod][12] = componentid;
        for(new s = 0; s < 2; s++) if(componentid == pv_bventr[s][0]) VehicleData[vehicleid][Mod][13] = componentid;
        for(new s = 0; s < 21; s++) if(componentid == pv_rskirt[s][0]) VehicleData[vehicleid][Mod][14] = componentid;
        for(new s = 0; s < 4; s++) if(componentid == pv_rbbars[s][0]) VehicleData[vehicleid][Mod][15] = componentid;
        for(new s = 0; s < 2; s++) if(componentid == pv_fbbars[s][0]) VehicleData[vehicleid][Mod][16] = componentid;
    }
    return 1;
}

function VehicleStaticCreate(playerid, vehicleid, model, color1, color2, Float:x, Float:y, Float:z, Float:a)
{
	VehicleData[vehicleid][ID] = vehicleid;
    VehicleData[vehicleid][Model] = model;
    VehicleData[vehicleid][Faction] = -1;
    VehicleData[vehicleid][Bisnis] = -1;
    VehicleData[vehicleid][Workshop] = -1;
    VehicleData[vehicleid][SpawnType] = 0;
	VehicleData[vehicleid][Color][0] = color1;
	VehicleData[vehicleid][Color][1] = color2;
    VehicleData[vehicleid][Pos][0] = x;
    VehicleData[vehicleid][Pos][1] = y;
    VehicleData[vehicleid][Pos][2] = z;
    VehicleData[vehicleid][Pos][3] = a;
    
	VehicleData[vehicleid][PaintJob] = -1;
	VehicleData[vehicleid][Locked] = 0;
	VehicleData[vehicleid][Health] = 2000;
	VehicleData[vehicleid][Fuel] = 1000;
	format(VehicleData[vehicleid][Plate], 16, "Static");
	VehicleData[vehicleid][Interior] = VehicleData[vehicleid][Virtual] = 0;
    VehicleData[vehicleid][Damage][0] = VehicleData[vehicleid][Damage][1] = VehicleData[vehicleid][Damage][2] = VehicleData[vehicleid][Damage][3] = 0;
	for(new j = 0; j < 5; j++)
	{
		VehicleData[vehicleid][Weapon][j] = 0;
		VehicleData[vehicleid][Ammo][j] = 0;
        VehicleData[vehicleid][TypeAmmo][j] = 0;
        VehicleData[vehicleid][Storage][j] = 0;
	}
	for(new j = 0; j < MAX_MODS; j++) VehicleData[vehicleid][Mod][j] = 0;
    SendCustomMessage(playerid, "VEHICLE", ""WHITE_E"You have created a static "AQUA_E"%s "WHITE_E"vehicle", GetVehicleModelName(VehicleData[vehicleid][Model]));
    SendCustomMessage(playerid, "NOTE", "Use "AQUA_E"'/vehicle edit' "WHITE_E"to edit static vehicles");
    VehicleRespawn(vehicleid);
    return 1;
}

GetVehicleStaticOwner(vehicleid) {
    new string[212];
    if(VehicleData[vehicleid][Faction] > 0) string = "Faction";
    else if(VehicleData[vehicleid][Bisnis] > 0) string = "Bisnis";
    else if(VehicleData[vehicleid][Workshop] > 0) string = "Workshop";
    return string;
}

GetVehicleStaticSpawn(vehicleid) {
    new string[212];
    if(!VehicleData[vehicleid][SpawnType]) string = "Always Spawn";
    else if(VehicleData[vehicleid][SpawnType]) string = "On-Demand";
    return string;
}

/*GetVehicleStaticStatus(vehicleid) {
    new string[212];
    if(!IsValidVehicle(VehicleData[vehicleid][Vehicle])) string = "Despawned";
    else if(IsValidVehicle(VehicleData[vehicleid][Vehicle])) string = "Spawned";
    return string;
}*/

IsSAPDCar(carid, playerid)
{
	foreach(new vehicleid : VehicleData) {
	    if(VehicleData[vehicleid][Vehicle] == carid && VehicleData[vehicleid][Faction] == pData[playerid][pFaction]) return 1;
	}
	return 0;
}

IsFactionVeh(carid)
{
    foreach(new vehicleid : VehicleData) {
	    if(VehicleData[vehicleid][Vehicle] == carid && VehicleData[vehicleid][Faction] != -1) return 1;
	}
	return 0;
}

VehData_GoodFactionVeh(vehicleid, factionid)
{
    if(factionid < 1 || factionid > 4) return -1;
    foreach(new id : VehicleData) {
        if(VehicleData[id][Vehicle] == vehicleid && VehicleData[id][Faction] == factionid) return id;
    }
    return -1;
}

VehicleData_WeaponStorage(playerid, vehicleid)
{
    new id = VehicleData_GetID(vehicleid);
    if(id == -1) return 0;

    static string[320];
    string[0] = 0;

    for(new i = 0; i < 4; i++) {
        if(!VehicleData[id][Weapon][i]) format(string, sizeof(string), "%sEmpty Slot\n", string);
        else format(string, sizeof(string), "%s%s (Ammo: %d)\n", string, ReturnWeaponName(VehicleData[id][Weapon][i]), VehicleData[id][Ammo][i]);
    }
    pData[playerid][pUseVehicleid] = vehicleid;
    Dialog_Show(playerid, VehicleDataWeapon, DIALOG_STYLE_LIST, "Faction Weapon Storage", string, "Select", "Cancel");
    return 1;
}

VehicleData_OpenStorage(playerid, vehicleid)
{
    new id = VehData_GoodFactionVeh(vehicleid, pData[playerid][pFaction]);
    if(id == -1) return 0;

    new items;
    for(new i = 0; i < 4; i++) if(VehicleData[id][Weapon][i]) items++;

    pData[playerid][pUseVehicleid] = vehicleid;
    Dialog_Show(playerid, VehicleDataStorage, DIALOG_STYLE_LIST, "Faction Trunk Storage", sprintf("Weapon Storage (%d/4)", items), "Select", "Cancel");
    return 1;
}

IsBisnisVeh(carid)
{
    foreach(new vehicleid : VehicleData) {
        if(VehicleData[vehicleid][Vehicle] == carid && VehicleData[vehicleid][Bisnis] != -1) return 1;
    }
    return 0;
}

IsWorkshopVeh(carid)
{
    foreach(new vehicleid : VehicleData) {
        if(VehicleData[vehicleid][Vehicle] == carid && VehicleData[vehicleid][Workshop] != -1) return 1;
    }
    return 0;
}

