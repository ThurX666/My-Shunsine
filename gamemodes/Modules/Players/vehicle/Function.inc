
Vehicle_GetID(vehicleid)
{
    if (!IsValidVehicle(vehicleid))
        return -1;

    foreach (new i : PVehicles) if(Iter_Contains(PVehicles, i)) if (!pvData[i][cClaim] &&  pvData[i][cVeh] == vehicleid) {
        return i;
    }
    return -1;
}

GetEngineStatus(vehicleid)
{
    static
        engine,
        lights,
        alarm,
        doors,
        bonnet,
        boot,
        objective;

    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

    if(engine != 1)
        return 0;

    return 1;
}

GetLightStatus(vehicleid)
{
    static
        engine,
        lights,
        alarm,
        doors,
        bonnet,
        boot,
        objective;

    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

    if(lights != 1)
        return 0;

    return 1;
}

GetHoodStatus(vehicleid)
{
    static
        engine,
        lights,
        alarm,
        doors,
        bonnet,
        boot,
        objective;

    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

    if(bonnet != 1)
        return 0;

    return 1;
}

GetVehicleModelByName(const name[])
{
    if(IsNumeric(name) && (strval(name) >= 400 && strval(name) <= 611))
        return strval(name);

    for (new i = 0; i < sizeof(g_arrVehicleNames); i ++)
    {
        if(strfind(g_arrVehicleNames[i], name, true) != -1)
        {
                    return i + 400;
        }
    }
    return 0;
}

Vehicle_Nearest(playerid, Float:range = 3.5)
{
    static
        Float:fX,
        Float:fY,
        Float:fZ;

    foreach(new i:PVehicles)
	{
		if(Iter_Contains(PVehicles, i)) 
		{
			GetVehiclePos(pvData[i][cVeh], fX, fY, fZ);

			if(IsPlayerInRangeOfPoint(playerid, range, fX, fY, fZ)) 
			{
				return i;
			}
		}
    }
    return -1;
}

Vehicle_IsOwner(playerid, carid)
{
	if(!pData[playerid][IsLoggedIn] || pData[playerid][pID] == -1)
		return 0;

	if((Iter_Contains(PVehicles, carid) && pvData[carid][cOwner] == pData[playerid][pID]))
		return 1;

	return 0;
}

SetVehiclePosEx(vehicleid, Float:x, Float:y, Float:z, Float:a, vw, int) {
	SetVehiclePos(vehicleid, x, y, z);
	SetVehicleZAngle(vehicleid, a);
	SetVehicleVirtualWorld(vehicleid, vw);
	LinkVehicleToInterior(vehicleid, int);
	foreach(new vehid : PVehicles) {
		if(pvData[vehid][cVeh] == vehicleid) {
			pvData[vehid][cInt] = int;
			pvData[vehid][cVw] = vw;
		}
	}
	foreach(new i : Player) if(GetPlayerState(i) == PLAYER_STATE_PASSENGER && GetPlayerVehicleID(i) == vehicleid) {
		SetPlayerInterior(i, int);
		SetPlayerVirtualWorld(i, vw);
	}
	return 1;
}

Vehicle_Lock(vehicleid, playerid) {
	foreach(new i : PVehicles) if(vehicleid == pvData[i][cVeh]) if(pvData[i][cOwner] == pData[playerid][pID])  {
		if(!pvData[i][cLocked])
		{
			pvData[i][cLocked] = 1;
			GameTextForPlayer(playerid,sprintf("~w~%s ~r~locked", GetVehicleName(pvData[i][cVeh])), 5000,6);
			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
			SwitchVehicleDoors(pvData[i][cVeh], true);
		}
		else
		{
			pvData[i][cLocked] = 0;
			GameTextForPlayer(playerid,sprintf("~w~%s ~g~unlocked", GetVehicleName(pvData[i][cVeh])), 5000,6);
			PlayerPlaySound(playerid, 1149, 0.0, 0.0, 0.0);
			SwitchVehicleDoors(pvData[i][cVeh], false);
		}
	}
	return 1;
}

Vehicle_GetStatus(carid)
{
    GetVehicleDamageStatus(pvData[carid][cVeh], pvData[carid][cDamage0], pvData[carid][cDamage1], pvData[carid][cDamage2], pvData[carid][cDamage3]);
	GetVehicleColor(pvData[carid][cVeh], pvData[carid][cColor1], pvData[carid][cColor2]);
    GetVehicleHealth(pvData[carid][cVeh], pvData[carid][cHealth]);
	pvData[carid][cFuel] = GetVehicleFuel(pvData[carid][cVeh]);
	SaveModsPVehicle(carid);
    if(pvData[carid][cOwner])
    {
        GetVehiclePos(pvData[carid][cVeh], pvData[carid][cPosX], pvData[carid][cPosY], pvData[carid][cPosZ]);
        GetVehicleZAngle(pvData[carid][cVeh],pvData[carid][cPosA]);
    }
	for(new id = 0; id < 5; id++) if(IsValidDynamicObject(ObjectVehicle[pvData[carid][cVeh]][id])) DestroyDynamicObject(ObjectVehicle[pvData[carid][cVeh]][id]);
    return 1;
}

SaveModsPVehicle(vehicleid)
{
    new componentid;
    for(new mod = 0; mod < MAX_MODS; mod++)
    {
        componentid = GetVehicleComponentInSlot(pvData[vehicleid][cVeh], mod);
        for(new s = 0; s < 20; s++) if(componentid == pv_spoiler[s][0]) pvData[vehicleid][cMod][0] = componentid;
        for(new s = 0; s < 4; s++) if(componentid == pv_bscoop[s][0]) pvData[vehicleid][cMod][1] = componentid;
        for(new s = 0; s < 17; s++) if(componentid == pv_roof[s][0]) pvData[vehicleid][cMod][2] = componentid;
        for(new s = 0; s < 21; s++) if(componentid == pv_lskirt[s][0]) pvData[vehicleid][cMod][3] = componentid;
        for(new s = 0; s < 2; s++) if(componentid == pv_lights[s][0]) pvData[vehicleid][cMod][4] = componentid;
        for(new s = 0; s < 3; s++) if(componentid == pv_nitro[s][0]) pvData[vehicleid][cMod][5] = componentid;
        for(new s = 0; s < 28; s++) if(componentid == pv_exhaust[s][0]) pvData[vehicleid][cMod][6] = componentid;
        for(new s = 0; s < 17; s++) if(componentid == pv_wheels[s][0]) pvData[vehicleid][cMod][7] = componentid;
        for(new s = 0; s < 1; s++) if(componentid == pv_base[s][0]) pvData[vehicleid][cMod][8] = componentid;
        for(new s = 0; s < 1; s++) if(componentid == pv_hydraulics[s][0]) pvData[vehicleid][cMod][9] = componentid;
        for(new s = 0; s < 23; s++) if(componentid == pv_fbumper[s][0]) pvData[vehicleid][cMod][10] = componentid;
        for(new s = 0; s < 22; s++) if(componentid == pv_rbumper[s][0]) pvData[vehicleid][cMod][11] = componentid;
        for(new s = 0; s < 2; s++) if(componentid == pv_bventl[s][0]) pvData[vehicleid][cMod][12] = componentid;
        for(new s = 0; s < 2; s++) if(componentid == pv_bventr[s][0]) pvData[vehicleid][cMod][13] = componentid;
        for(new s = 0; s < 21; s++) if(componentid == pv_rskirt[s][0]) pvData[vehicleid][cMod][14] = componentid;
        for(new s = 0; s < 4; s++) if(componentid == pv_rbbars[s][0]) pvData[vehicleid][cMod][15] = componentid;
        for(new s = 0; s < 2; s++) if(componentid == pv_fbbars[s][0]) pvData[vehicleid][cMod][16] = componentid;
    }
    return 1;
}

SetValidVehicleHealth(vehicleid, Float:health) {
    VehicleHealthSecurity[vehicleid] = true;
    SetVehicleHealth(vehicleid, health);
    return 1;
}

ValidRepairVehicle(vehicleid) {
    VehicleHealthSecurity[vehicleid] = true;
    RepairVehicle(vehicleid);
    return 1;
}

function OnLoadVehicleStorage(i)
{
	if(IsValidVehicle(pvData[i][cVeh]))
	{
		if(pvData[i][cTogNeon] == 1)
		{
			if(pvData[i][cNeon] != 0) SetVehicleNeonLights(pvData[i][cVeh], true, pvData[i][cNeon], 0);
			return 1;
		}
		if(pvData[i][cComponent] >= 1)
		{
			if(IsValidDynamicObject(ObjectVehicle[pvData[i][cVeh]][0])) DestroyDynamicObject(ObjectVehicle[pvData[i][cVeh]][0]);
			if(GetVehicleModel(pvData[i][cVeh]) == 422)
			{
				ObjectVehicle[pvData[i][cVeh]][0] = CreateDynamicObject(964,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[i][cVeh]][0], pvData[i][cVeh], 0.000, -1.370, -0.320, 0.000, 0.000, 0.000);
			}
			else if(GetVehicleModel(pvData[i][cVeh]) == 543)
			{
				ObjectVehicle[pvData[i][cVeh]][0] = CreateDynamicObject(964,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[i][cVeh]][0], pvData[i][cVeh], 0.000, -1.521, -0.250, 0.000, 0.000, 0.000);
			}	
			else if(GetVehicleModel(pvData[i][cVeh]) == 525)
			{
				ObjectVehicle[pvData[i][cVeh]][0] = CreateDynamicObject(964,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[i][cVeh]][0], pvData[i][cVeh], 0.000, -1.000, 0.190, 0.000, 0.000, 0.000);
			}
			return 1;
		}
		if(pvData[i][cOnion] >= 1 || pvData[i][cCarrot] >= 1 || pvData[i][cPotato] >= 1 || pvData[i][cCorn] >= 1 || pvData[i][cWheat] >= 1)
		{
			if(IsValidDynamicObject(ObjectVehicle[pvData[i][cVeh]][2])) DestroyDynamicObject(ObjectVehicle[pvData[i][cVeh]][2]);
			if(GetVehicleModel(pvData[i][cVeh]) == 422)
			{
				ObjectVehicle[pvData[i][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[i][cVeh]][2], pvData[i][cVeh], 0.000, -1.382, 0.126, 90.599, 0.000, 0.000);
			}
			else if(GetVehicleModel(pvData[i][cVeh]) == 478)
			{
				ObjectVehicle[pvData[i][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[i][cVeh]][2], pvData[i][cVeh], 0.000, -1.537, 0.263, 88.999, 0.000, 0.000);
			}	
			else if(GetVehicleModel(pvData[i][cVeh]) == 543)
			{
				ObjectVehicle[pvData[i][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[i][cVeh]][2], pvData[i][cVeh], 0.000, -1.338, 0.298, 89.599, 0.000, 0.000);
			}
			else if(GetVehicleModel(pvData[i][cVeh]) == 554)
			{
				ObjectVehicle[pvData[i][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[i][cVeh]][2], pvData[i][cVeh], 0.000, -1.625, 0.209, 88.900, 0.000, 0.000);
			}
			return 1;
		}	
		if(pvData[i][cLumber] >= 1)
		{
			if(IsValidDynamicObject(ObjectVehicle[pvData[i][cVeh]][1])) DestroyDynamicObject(ObjectVehicle[pvData[i][cVeh]][1]);
			if(GetVehicleModel(pvData[i][cVeh]) == 422)
			{
				ObjectVehicle[pvData[i][cVeh]][1] = CreateDynamicObject(1463,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[i][cVeh]][1], pvData[i][cVeh], 0.005, -1.440, -0.130, 0.000, 179.999, 90.899);
			}
			else if(GetVehicleModel(pvData[i][cVeh]) == 478)
			{
				ObjectVehicle[pvData[i][cVeh]][1] = CreateDynamicObject(1463,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[i][cVeh]][1], pvData[i][cVeh], 0.000, -1.420, 0.080, 180.000, 0.000, 90.000);
			}	
			else if(GetVehicleModel(pvData[i][cVeh]) == 543)
			{
				ObjectVehicle[pvData[i][cVeh]][1] = CreateDynamicObject(1463,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[i][cVeh]][1], pvData[i][cVeh], 0.000, -1.651, 0.000, 180.000, 0.000, 90.000);
			}
			else if(GetVehicleModel(pvData[i][cVeh]) == 554)
			{
				ObjectVehicle[pvData[i][cVeh]][1] = CreateDynamicObject(1463,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[i][cVeh]][1], pvData[i][cVeh], -0.070, -1.581, 0.100, 180.000, 0.000, 90.000);
			}
			return 1;
		}
	}
	return 1;
}

function PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
    new Float:oldposx, Float:oldposy, Float:oldposz;
    new Float:tempposx, Float:tempposy, Float:tempposz;
    GetPlayerPos(playerid, oldposx, oldposy, oldposz);
    tempposx = (oldposx -x);
    tempposy = (oldposy -y);
    tempposz = (oldposz -z);
    if(((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
    {
        return 1;
    }
    return 0;
}


function LoadPlayerVehicle(playerid, race_check)
{
    if(race_check != g_MysqlRaceCheck[playerid]) return Kick(playerid);
    new count = cache_num_rows(), i;
	if(count > 0)
	{
		for(new z = 0; z < count; z++)
		{
			if((i = Iter_Free(PVehicles)) != cellmin)
			{
				Iter_Add(PVehicles, i);
				VehicleReset(i);
				cache_get_value_name_int(z, "id", pvData[i][cID]);
				cache_get_value_name_int(z, "owner", pvData[i][cOwner]);
				cache_get_value_name_int(z, "locked", pvData[i][cLocked]);
				cache_get_value_name_float(z, "x", pvData[i][cPosX]);
				cache_get_value_name_float(z, "y", pvData[i][cPosY]);
				cache_get_value_name_float(z, "z", pvData[i][cPosZ]);
				cache_get_value_name_float(z, "a", pvData[i][cPosA]);
				cache_get_value_name_float(z, "health", pvData[i][cHealth]);
				// cache_get_value_name_int(z, "fuel", pvData[i][cFuel]);
				cache_get_value_name_int(z, "int", pvData[i][cInt]);
				cache_get_value_name_int(z, "vw", pvData[i][cVw]);
				cache_get_value_name_int(z, "damage0", pvData[i][cDamage0]);
				cache_get_value_name_int(z, "damage1", pvData[i][cDamage1]);
				cache_get_value_name_int(z, "damage2", pvData[i][cDamage2]);
				cache_get_value_name_int(z, "damage3", pvData[i][cDamage3]);
				cache_get_value_name_int(z, "color1", pvData[i][cColor1]);
				cache_get_value_name_int(z, "color2", pvData[i][cColor2]);
				cache_get_value_name_int(z, "paintjob", pvData[i][cPaintJob]);
				cache_get_value_name_int(z, "neon", pvData[i][cNeon]);
				cache_get_value_name_int(z, "price", pvData[i][cPrice]);
				cache_get_value_name_int(z, "model", pvData[i][cModel]);
				cache_get_value_name(z, "plate", pvData[i][cPlate], 212);
				cache_get_value_name_int(z, "plate_time", pvData[i][cPlateTime]);
				cache_get_value_name_int(z, "ticket", pvData[i][cTicket]);
				
				cache_get_value_name_int(z, "mod0", pvData[i][cMod][0]);
				cache_get_value_name_int(z, "mod1", pvData[i][cMod][1]);
				cache_get_value_name_int(z, "mod2", pvData[i][cMod][2]);
				cache_get_value_name_int(z, "mod3", pvData[i][cMod][3]);
				cache_get_value_name_int(z, "mod4", pvData[i][cMod][4]);
				cache_get_value_name_int(z, "mod5", pvData[i][cMod][5]);
				cache_get_value_name_int(z, "mod6", pvData[i][cMod][6]);
				cache_get_value_name_int(z, "mod7", pvData[i][cMod][7]);
				cache_get_value_name_int(z, "mod8", pvData[i][cMod][8]);
				cache_get_value_name_int(z, "mod9", pvData[i][cMod][9]);
				cache_get_value_name_int(z, "mod10", pvData[i][cMod][10]);
				cache_get_value_name_int(z, "mod11", pvData[i][cMod][11]);
				cache_get_value_name_int(z, "mod12", pvData[i][cMod][12]);
				cache_get_value_name_int(z, "mod13", pvData[i][cMod][13]);
				cache_get_value_name_int(z, "mod14", pvData[i][cMod][14]);
				cache_get_value_name_int(z, "mod15", pvData[i][cMod][15]);
				cache_get_value_name_int(z, "mod16", pvData[i][cMod][16]);
				cache_get_value_name_int(z, "lumber", pvData[i][cLumber]);
				cache_get_value_name_int(z, "rental", pvData[i][cRent]);
				cache_get_value_name_int(z, "gun1", pvData[i][cWeapon][0]);
				cache_get_value_name_int(z, "gun2", pvData[i][cWeapon][1]);
				cache_get_value_name_int(z, "gun3", pvData[i][cWeapon][2]);
				cache_get_value_name_int(z, "gun4", pvData[i][cWeapon][3]);
				cache_get_value_name_int(z, "gun5", pvData[i][cWeapon][4]);
				cache_get_value_name_int(z, "gun6", pvData[i][cWeapon][5]);
				cache_get_value_name_int(z, "gun7", pvData[i][cWeapon][6]);
				cache_get_value_name_int(z, "gun8", pvData[i][cWeapon][7]);
				cache_get_value_name_int(z, "gun9", pvData[i][cWeapon][8]);
				cache_get_value_name_int(z, "gun10", pvData[i][cWeapon][9]);
				cache_get_value_name_int(z, "ammo1", pvData[i][cAmmo][0]);
				cache_get_value_name_int(z, "ammo2", pvData[i][cAmmo][1]);
				cache_get_value_name_int(z, "ammo3", pvData[i][cAmmo][2]);
				cache_get_value_name_int(z, "ammo4", pvData[i][cAmmo][3]);
				cache_get_value_name_int(z, "ammo5", pvData[i][cAmmo][4]);
				cache_get_value_name_int(z, "ammo6", pvData[i][cAmmo][5]);
				cache_get_value_name_int(z, "ammo7", pvData[i][cAmmo][6]);
				cache_get_value_name_int(z, "ammo8", pvData[i][cAmmo][7]);
				cache_get_value_name_int(z, "ammo9", pvData[i][cAmmo][8]);
				cache_get_value_name_int(z, "ammo10", pvData[i][cAmmo][9]);
				new ammo[52];
				cache_get_value_name(i, "ammotype", ammo);
				sscanf(ammo, "p<|>dddddddddd",pvData[i][cAmmoType][0],pvData[i][cAmmoType][1],
				pvData[i][cAmmoType][2],pvData[i][cAmmoType][3],pvData[i][cAmmoType][4],pvData[i][cAmmoType][5],
				pvData[i][cAmmoType][6],pvData[i][cAmmoType][7],pvData[i][cAmmoType][8],pvData[i][cAmmoType][9]);
            
				cache_get_value_name_int(z, "cratecomponent", pvData[i][cCrateComponent]);
				cache_get_value_name_int(z, "cratefish", pvData[i][cCrateFish]);
				cache_get_value_name_int(z, "cratefish2", pvData[i][cCrateFish2]);
				cache_get_value_name_int(z, "cratelumber", pvData[i][cCrateLumber]);
				cache_get_value_name_int(z, "crateplant", pvData[i][cCratePlant]);
				cache_get_value_name_int(z, "plantwheat", pvData[i][cWheat]);
				cache_get_value_name_int(z, "plantonion", pvData[i][cOnion]);
				cache_get_value_name_int(z, "plantcarrot", pvData[i][cCarrot]);
				cache_get_value_name_int(z, "plantpotato", pvData[i][cPotato]);
				cache_get_value_name_int(z, "plantcorn", pvData[i][cCorn]);
				cache_get_value_name_int(z, "trunkcrack", pvData[i][cCrack]);
				cache_get_value_name_int(z, "trunkpot", pvData[i][cPot]);
				cache_get_value_name_int(z, "trunkmaterial", pvData[i][cMaterial]);
				cache_get_value_name_int(z, "trunkcomponent", pvData[i][cComponent]);
				cache_get_value_name_int(z, "trunkcgun", pvData[i][cCgun]);
				cache_get_value_name_int(z, "upgradeengine", pvData[i][cMesinUpgrade]);
				cache_get_value_name_int(z, "upgradebody", pvData[i][pvBodyUpgrade]);
				cache_get_value_name_int(z, "insurance", pvData[i][cInsu]);
				cache_get_value_name_int(z, "insuranceclaim", pvData[i][cClaim]);
				cache_get_value_name_int(z, "insuranceclaimtime", pvData[i][cClaimTime]);
				cache_get_value_name_int(z, "ticketime", pvData[i][cTicketTime]);
				cache_get_value_name_int(z, "park", pvData[i][cPark]);
				cache_get_value_name_int(z, "spawned", pvData[i][cDespawn]);
				cache_get_value_name_int(z, "impound", pvData[i][cImpound]);
				cache_get_value_name(z, "impoundprice", pvData[i][cImpoundReason], 128);
				cache_get_value_name_int(z, "tirelock", pvData[i][vLockTire]);
				cache_get_value_name_int(z, "vehgarage", pvData[i][cVehicleGarage]);
				cache_get_value_name_int(z, "fuel", pvData[i][cFuel]);

				if(!IsValidVehicle(pvData[i][cVeh]))
				{
				    if(pvData[i][cImpound] > 0 || pvData[i][cVehicleGarage] > -1 || pvData[i][cClaim] == 1)
				    {
				        OnPlayerVehicleRespawn(i);
				    }
				    else if(GetPlayerDistanceFromPoint(playerid, pvData[i][cPosX], pvData[i][cPosY], pvData[i][cPosZ]) > 30.0)
				    {
				        pvData[i][cDespawn] = 1;
				        SendVehicleOwnedMessage(i, sprintf("VEHICLE: "WHITE_E"Your "AQUA_E"%s "WHITE_E"is too far and has been despawned. Use /spawn near its location.", GetVehicleModelName(pvData[i][cModel])));
				    }
				    else OnPlayerVehicleRespawn(i);
				}
			}
		}
	}
	return 1;
}


OnPlayerVehicleRespawn(i)
{
	if(pvData[i][cImpound] > 0) return 0;
	if(pvData[i][cVehicleGarage] > -1) return 0;
	if(pvData[i][cClaim] == 1) return 0;
	pvData[i][cDespawn] = 0;
	pvData[i][cVeh] = CreateVehicle(pvData[i][cModel], pvData[i][cPosX], pvData[i][cPosY], pvData[i][cPosZ], pvData[i][cPosA], pvData[i][cColor1], pvData[i][cColor2], -1);
	if(IsValidVehicle(pvData[i][cVeh]))
	{
		new plate[62];
		format(plate, sizeof(plate), "%s", pvData[i][cPlate]);
		SetVehicleNumberPlate(pvData[i][cVeh], plate);
		SetVehicleVirtualWorld(pvData[i][cVeh], pvData[i][cVw]);
		LinkVehicleToInterior(pvData[i][cVeh], pvData[i][cInt]);
		SetVehicleFuel(pvData[i][cVeh], pvData[i][cFuel]);
		if(pvData[i][cHealth] < 350.0) SetValidVehicleHealth(pvData[i][cVeh], 350.0);
		else SetValidVehicleHealth(pvData[i][cVeh], pvData[i][cHealth]);
		
		UpdateVehicleDamageStatus(pvData[i][cVeh], pvData[i][cDamage0], pvData[i][cDamage1], pvData[i][cDamage2], pvData[i][cDamage3]);
		if(pvData[i][cPaintJob] != -1) ChangeVehiclePaintjob(pvData[i][cVeh], pvData[i][cPaintJob]);
		for(new z = 0; z < MAX_MODS; z++) if(pvData[i][cMod][z]) AddVehicleComponent(pvData[i][cVeh], pvData[i][cMod][z]);
		if(pvData[i][cLocked] == 1) SwitchVehicleDoors(pvData[i][cVeh], true);
		else SwitchVehicleDoors(pvData[i][cVeh], false);
        if (pvData[i][cOwner]) {
            new vehicleid = GetClosestVehicleToVehicle(pvData[i][cVeh]), vehid = -1;
                
            if (vehicleid != INVALID_VEHICLE_ID && vehicleid != pvData[i][cVeh]) {
                if ((vehid = Vehicle_GetID(vehicleid)) != -1 && pvData[vehid][cDespawn] == 0) {
                    if (pvData[vehid][cOwner]) {
                        if (IsVehicleOccupied(pvData[vehid][cVeh])) {
                            new vehname[32];

                            GetVehicleNameByVehicle(pvData[i][cVeh], vehname);
                            LinkVehicleToInterior(pvData[i][cVeh], pvData[i][cInt]);
                            SetVehicleVirtualWorld(pvData[i][cVeh], pvData[i][cID]);
                            SendVehicleOwnedMessage(i, sprintf("VEHICLE: "WHITE_E"Your "AQUA_E"%s "WHITE_E"has been despawned due to conflict with other vehicle.", vehname));
                            pvData[i][cDespawn] = 1;
                        } else {
                            new vehname[32];

                            GetVehicleNameByVehicle(pvData[i][cVeh], vehname);
                            LinkVehicleToInterior(pvData[vehid][cVeh], pvData[vehid][cInt]);
                            SetVehicleVirtualWorld(pvData[vehid][cVeh], pvData[vehid][cID]);
                            SendVehicleOwnedMessage(vehid, sprintf("VEHICLE: "WHITE_E"Your "AQUA_E"%s "WHITE_E"has been despawned due to conflict with other vehicle.", vehname));
                            pvData[vehid][cDespawn] = 1;
                        }
                    }
                }
            } else {
                LinkVehicleToInterior(pvData[i][cVeh], pvData[i][cInt]);
                SetVehicleVirtualWorld(pvData[i][cVeh], pvData[i][cVw]);
            }
        } else {
            LinkVehicleToInterior(pvData[i][cVeh], pvData[i][cInt]);
            SetVehicleVirtualWorld(pvData[i][cVeh], pvData[i][cVw]);
        }
		if(pvData[i][vLockTire])
		{
			if(!IsValidDynamic3DTextLabel(pvData[i][vLockTireText]))
				pvData[i][vLockTireText] = CreateDynamic3DTextLabel("** Vehicle Tire locked **", COLOR_PURPLE, pvData[i][cPosX], pvData[i][cPosY], pvData[i][cPosZ], 15, INVALID_PLAYER_ID, pvData[i][cVeh], 1);
			
			Vehicle_StartLockTire(i);
		}
		if(pvData[i][cDespawn] == 1)
		{
			LinkVehicleToInterior(pvData[i][cVeh], pvData[i][cInt]);
			SetVehicleVirtualWorld(pvData[i][cVeh], pvData[i][cID]);
		}
		SetTimerEx("OnLoadVehicleStorage", 5000, false, "d", i);
		new string[128];
		mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `vehicle_object` WHERE `vehicle`=%d", pvData[i][cID]);
		mysql_tquery(g_SQL, string, "Vehicle_ObjectLoaded", "d", i); // Coba lag
	}
	return 1;
}	

function EngineStatus(playerid, vehicleid)
{
	if(!GetEngineStatus(vehicleid))
    {
		if(pData[playerid][pTogHandbrake] == 1) 
		{
			if(pvData[vehicleid][cHandbrake]) {
				pvData[vehicleid][cHandbrake] = 0;
				SendClientMessage(playerid, -1, "VEHICLE: {FFFFFF}Handbrakes {FF0000}disengaged");
	           	GetVehiclePos(pvData[vehicleid][cVeh], pvData[vehicleid][cPosX], pvData[vehicleid][cPosY], pvData[vehicleid][cPosZ]);
				GetVehicleZAngle(pvData[vehicleid][cVeh],pvData[vehicleid][cPosA]);
			}
        }
		foreach(new ii : PVehicles) if(vehicleid == pvData[ii][cVeh]) {
			if(pvData[ii][cTicket] >= 2000) return Error(playerid, "This vehicle has a pending ticket in SAPD Officer! /v insu - to check pending ticket");
		}
		new Float: f_vHealth;
		GetVehicleHealth(vehicleid, f_vHealth);
		if(f_vHealth < 350.0) return Error(playerid, "The car won't start - it's totalled!");
		if(GetVehicleFuel(vehicleid) <= 0.0) return Error(playerid, "The car won't start - there's no fuel in the tank!");
		// DeletePVar(playerid, "EngineOn");
		SwitchVehicleEngine(vehicleid, true);
		// pvData[vehicleid][cHandbrake] = 1;
		SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You have "GREEN_E"succesfully "WHITE_E"started the vehicle engine.");
	}
	else
	{
		if(pData[playerid][pTogHandbrake] == 1) {
            if(JB_IsBicycle(vehicleid) && IsABike(vehicleid)) return 1;
			if(!pvData[vehicleid][cHandbrake]) {
				pvData[vehicleid][cHandbrake] = 1;
				SendClientMessage(playerid, -1, "VEHICLE: {FFFFFF}Handbrakes {00FF00}engaged");
			}
        }
		SendClientMessageEx(playerid, COLOR_WHITE, "ENGINE: Anda telah mematikan Mesin");
		SwitchVehicleEngine(vehicleid, false);
		SwitchVehicleLight(vehicleid, false);
	}
	return 1;
}

RemovePlayerVehicle(playerid)
{
	foreach(new i : PVehicles)
	{
		if(pvData[i][cOwner] == pData[playerid][pID])
		{
			if(IsValidVehicle(pvData[i][cVeh])) Vehicle_GetStatus(i);
			pvData[i][cOwner] = -1;
			new cQuery[5248]/*, color1, color2, paintjob*/;
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `vehicle` SET ");
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`x`='%.4f', ", cQuery, pvData[i][cPosX]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`y`='%.4f', ", cQuery, pvData[i][cPosY]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`z`='%.4f', ", cQuery, pvData[i][cPosZ]+0.1);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`a`='%.4f', ", cQuery, pvData[i][cPosA]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`health`='%f', ", cQuery, pvData[i][cHealth]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`fuel`=%d, ", cQuery, pvData[i][cFuel]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`int`=%d, ", cQuery, pvData[i][cInt]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`price`=%d, ", cQuery, pvData[i][cPrice]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`vw`=%d, ", cQuery, GetVehicleVirtualWorld(pvData[i][cVeh])); 
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`model`=%d, ", cQuery, pvData[i][cModel]);
			if(pvData[i][cLocked] == 1)
				mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`locked`=1, ", cQuery);
			else
				mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`locked`=0, ", cQuery);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`plate`='%e', ", cQuery, pvData[i][cPlate]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`plate_time`='%d', ", cQuery, pvData[i][cPlateTime]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ticket`='%d', ", cQuery, pvData[i][cTicket]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`color1`=%d, ", cQuery, pvData[i][cColor1]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`color2`=%d, ", cQuery, pvData[i][cColor2]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`paintjob`=%d, ", cQuery, pvData[i][cPaintJob]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`neon`=%d, ", cQuery, pvData[i][cNeon]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`damage0`=%d, ", cQuery, pvData[i][cDamage0]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`damage1`=%d, ", cQuery, pvData[i][cDamage1]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`damage2`=%d, ", cQuery, pvData[i][cDamage2]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`damage3`=%d, ", cQuery, pvData[i][cDamage3]);
			new tempString[56];
			for(new z = 0; z < MAX_MODS; z++)
			{
				format(tempString, sizeof(tempString), "mod%d", z);
				mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`%s`=%d, ", cQuery, tempString, pvData[i][cMod][z]);
			}
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`lumber`=%d, ", cQuery, pvData[i][cLumber]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`rental`=%d, ", cQuery, pvData[i][cRent]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gun1`=%d, ", cQuery, pvData[i][cWeapon][0]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gun2`=%d, ", cQuery, pvData[i][cWeapon][1]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gun3`=%d, ", cQuery, pvData[i][cWeapon][2]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gun4`=%d,", cQuery, pvData[i][cWeapon][3]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gun5`=%d,", cQuery, pvData[i][cWeapon][4]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gun6`=%d, ", cQuery,pvData[i][cWeapon][5]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gun7`=%d, ", cQuery, pvData[i][cWeapon][6]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gun8`=%d, ", cQuery, pvData[i][cWeapon][7]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gun9`=%d, ", cQuery, pvData[i][cWeapon][8]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`gun10`=%d, ", cQuery, pvData[i][cWeapon][9]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ammo1`=%d, ", cQuery, pvData[i][cAmmo][0]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ammo2`=%d, ", cQuery, pvData[i][cAmmo][1]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ammo3`=%d, ", cQuery, pvData[i][cAmmo][2]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ammo4`=%d,", cQuery, pvData[i][cAmmo][3]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ammo5`=%d,", cQuery, pvData[i][cAmmo][4]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ammo6`=%d, ", cQuery,pvData[i][cAmmo][5]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ammo7`=%d, ", cQuery, pvData[i][cAmmo][6]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ammo8`=%d, ", cQuery, pvData[i][cAmmo][7]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ammo9`=%d, ", cQuery, pvData[i][cAmmo][8]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ammo10`=%d, ", cQuery, pvData[i][cAmmo][9]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ammotype`=%d|%d|%d|%d|%d|%d|%d|%d|%d|%d, ", cQuery, pvData[i][cAmmoType][0],pvData[i][cAmmoType][1],
			pvData[i][cAmmoType][2],pvData[i][cAmmoType][3],pvData[i][cAmmoType][4],pvData[i][cAmmoType][5],
			pvData[i][cAmmoType][6],pvData[i][cAmmoType][7],pvData[i][cAmmoType][8],pvData[i][cAmmoType][9]);

			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`cratecomponent`=%d, ", cQuery, pvData[i][cCrateComponent]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`cratefish`=%d, ", cQuery, pvData[i][cCrateFish]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`cratefish2`=%d, ", cQuery, pvData[i][cCrateFish2]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`cratelumber`=%d, ", cQuery, pvData[i][cCrateLumber]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`crateplant`=%d, ", cQuery, pvData[i][cCratePlant]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`plantwheat`=%d, ", cQuery, pvData[i][cWheat]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`plantonion`=%d, ", cQuery, pvData[i][cOnion]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`plantcarrot`=%d, ", cQuery, pvData[i][cCarrot]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`plantpotato`=%d, ", cQuery, pvData[i][cPotato]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`plantcorn`=%d, ", cQuery, pvData[i][cCorn]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`trunkcrack`=%d, ", cQuery, pvData[i][cCrack]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`trunkpot`=%d, ", cQuery, pvData[i][cPot]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`trunkmaterial`=%d, ", cQuery, pvData[i][cMaterial]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`trunkcomponent`=%d, ", cQuery, pvData[i][cComponent]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`trunkcgun`=%d, ", cQuery, pvData[i][cCgun]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`upgradeengine`=%d, ", cQuery, pvData[i][cMesinUpgrade]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`upgradebody`=%d, ", cQuery, pvData[i][pvBodyUpgrade]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`insurance`=%d, ", cQuery, pvData[i][cInsu]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`insuranceclaim`=%d, ", cQuery, pvData[i][cClaim]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`insuranceclaimtime`=%d, ", cQuery, pvData[i][cClaimTime]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ticketime`=%d, ", cQuery, pvData[i][cTicketTime]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`impound`=%d, ", cQuery, pvData[i][cImpound]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`despawn`=1, ", cQuery);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`impoundprice`='%e', ", cQuery, pvData[i][cImpoundReason]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`park`=%d, ", cQuery, pvData[i][cPark]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`tirelock`=%d, ", cQuery, pvData[i][vLockTire]);
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`vehgarage`=%d ", cQuery, pvData[i][cVehicleGarage]);

			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `id` = %d", cQuery, pvData[i][cID]);
			mysql_tquery(g_SQL, cQuery);
			Vehicle_ObjectDestroy(i);
			if(IsValidDynamic3DTextLabel(pvData[i][vLockTireText])) DestroyDynamic3DTextLabel(pvData[i][vLockTireText]);
			if(IsValidVehicle(pvData[i][cVeh])) DestroyVehicle(pvData[i][cVeh]);
			new tmp_pvData[pvdata];
			pvData[i] = tmp_pvData;

			pvData[i][cVeh] = INVALID_VEHICLE_ID;
			new current = i;
			Iter_SafeRemove(PVehicles, current, i);
		}
	}
	return 1;
}

IsVIPVehicle(vehicleid)
{
	new vehmodel = GetVehicleModel(vehicleid);
	switch(vehmodel)
	{
		case 541,480,565,434,494,502,503,411,506,555,477,568,424,504,457,483,508,571,500,444,556,471,495,539,470,573,514,515:
		{
			return 1;
		}
		
	}
	return 0;
}

VehicleReset(i) {
	pvData[i][cVeh] = INVALID_VEHICLE_ID;
	pvData[i][cNeon] = 0;
	pvData[i][cTogNeon] = 0;
	pvData[i][cLocked] = 0;
	pvData[i][cClaim] = 0;
	pvData[i][cClaimTime] = 0;
	pvData[i][cTicket] = 0;
	pvData[i][cPlateTime] = 0;
	pvData[i][cInt] = 0;
	pvData[i][cVw] = 0;
	pvData[i][cLumber] = 0;
	pvData[i][cMesinUpgrade] = 0;
	pvData[i][pvBodyUpgrade] = 0;
	pvData[i][cRent] = 0;
	pvData[i][cCrack] = 0;
	pvData[i][cPot] = 0;
	pvData[i][cMaterial] = 0;
	pvData[i][cCgun] = 0;
	pvData[i][cComponent] = 0;
	pvData[i][cCrateComponent] = 0;
	pvData[i][cCrateFish] = 0;
	pvData[i][cCrateFish2] = 0;
	pvData[i][cCrateLumber] = 0;
	pvData[i][cCratePlant] = 0;
	pvData[i][cWheat] = 0;
	pvData[i][cCarrot] = 0;
	pvData[i][cPotato] = 0;
	pvData[i][cCorn] = 0;
	pvData[i][cWheat] = 0;
	pvData[i][cCarrot] = 0;
	pvData[i][cPotato] = 0;
	pvData[i][cCorn] = 0;
	pvData[i][cImpound] = 0;
	pvData[i][vLockTire] = 0;
	pvData[i][cVehicleGarage] = -1;
	pvData[i][cHandbrake] = 0;
	for(new j = 0; j < 10; j++)
	{
		pvData[i][cWeapon][j] = 0;
		pvData[i][cAmmo][j] = 0;
	}
	pvData[i][vDestroyed] = -1;
	for(new j = 0; j < MAX_MODS; j++)
		pvData[i][cMod][j] = 0;
	if(IsValidDynamic3DTextLabel(pvData[i][vLockTireText])) DestroyDynamic3DTextLabel(pvData[i][vLockTireText]);
	if(IsValidDynamic3DTextLabel(pvData[i][vLockTireText])) DestroyDynamic3DTextLabel(pvData[i][vLockTireText]);
	return 1;
}

function OnVehCreated(playerid, oid, pid, model, color1, color2, Float:x, Float:y, Float:z, Float:a)
{
	new i = Iter_Free(PVehicles);
	new price = GetVehicleCost(model);
	pvData[i][cID] = cache_insert_id();
	pvData[i][cOwner] = pid;
	pvData[i][cModel] = model;
	pvData[i][cColor1] = color1;
	pvData[i][cColor2] = color2;
	pvData[i][cPaintJob] = -1;
	pvData[i][cNeon] = 0;
	pvData[i][cTogNeon] = 0;
	pvData[i][cLocked] = 0;
	pvData[i][cInsu] = 3;
	pvData[i][cClaim] = 0;
	pvData[i][cClaimTime] = 0;
	pvData[i][cTicket] = 0;
	pvData[i][cPrice] = price;
	pvData[i][cHealth] = 2000;
	pvData[i][cFuel] = 1000;
	format(pvData[i][cPlate], 16, "No Have");
	pvData[i][cPlateTime] = 0;
	pvData[i][cPosX] = x;
	pvData[i][cPosY] = y;
	pvData[i][cPosZ] = z;
	pvData[i][cPosA] = a;
	pvData[i][cInt] = 0;
	pvData[i][cVw] = 0;
	pvData[i][cLumber] = 0;
	pvData[i][cMesinUpgrade] = 0;
	pvData[i][pvBodyUpgrade] = 0;
	pvData[i][cRent] = 0;
	pvData[i][cCrack] = 0;
	pvData[i][cPot] = 0;
	pvData[i][cMaterial] = 0;
	pvData[i][cCgun] = 0;
	pvData[i][cComponent] = 0;
	pvData[i][cCrateComponent] = 0;
	pvData[i][cCrateFish] = 0;
	pvData[i][cCrateFish2] = 0;
	pvData[i][cCrateLumber] = 0;
	pvData[i][cCratePlant] = 0;
	pvData[i][cWheat] = 0;
	pvData[i][cCarrot] = 0;
	pvData[i][cPotato] = 0;
	pvData[i][cCorn] = 0;
	pvData[i][cWheat] = 0;
	pvData[i][cCarrot] = 0;
	pvData[i][cPotato] = 0;
	pvData[i][cCorn] = 0;
	pvData[i][cImpound] = 0;
	pvData[i][vLockTire] = 0;
	pvData[i][cVehicleGarage] = -1;
	for(new j = 0; j < 10; j++)
	{
		pvData[i][cWeapon][j] = 0;
		pvData[i][cAmmo][j] = 0;
	}
	pvData[i][vDestroyed] = -1;
	for(new j = 0; j < MAX_MODS; j++)
		pvData[i][cMod][j] = 0;
	if(IsValidDynamic3DTextLabel(pvData[i][vLockTireText])) DestroyDynamic3DTextLabel(pvData[i][vLockTireText]);
	Iter_Add(PVehicles, i);
	OnPlayerVehicleRespawn(i);
	Servers(playerid, "You have made the vehicle to "YELLOW_E"%s "WHITE_E"with {00FFFF}(model=%d, color1=%d, color2=%d)", pData[oid][pName], model, color1, color2);
	return 1;
}

function OnVehStarterpack(playerid, pid, model, color1, color2, Float:x, Float:y, Float:z, Float:a)
{
	new i = Iter_Free(PVehicles);
	pvData[i][cID] = cache_insert_id();
	pvData[i][cOwner] = pid;
	pvData[i][cModel] = model;
	pvData[i][cColor1] = color1;
	pvData[i][cColor2] = color2;
	pvData[i][cPaintJob] = -1;
	pvData[i][cNeon] = 0;
	pvData[i][cTogNeon] = 0;
	pvData[i][cLocked] = 0;
	pvData[i][cInsu] = 3;
	pvData[i][cClaim] = 0;
	pvData[i][cClaimTime] = 0;
	pvData[i][cTicket] = 0;
	pvData[i][cPrice] = 0;
	pvData[i][cHealth] = 2000;
	pvData[i][cFuel] = 1000;
	format(pvData[i][cPlate], 16, "No Have");
	pvData[i][cPlateTime] = 0;
	pvData[i][cPosX] = x;
	pvData[i][cPosY] = y;
	pvData[i][cPosZ] = z;
	pvData[i][cPosA] = a;
	pvData[i][cInt] = 0;
	pvData[i][cVw] = 0;
	pvData[i][cLumber] = 0;
	pvData[i][cMesinUpgrade] = 0;
	pvData[i][pvBodyUpgrade] = 0;
	pvData[i][cRent] = 0;
	pvData[i][cCrack] = 0;
	pvData[i][cPot] = 0;
	pvData[i][cMaterial] = 0;
	pvData[i][cCgun] = 0;
	pvData[i][cComponent] = 0;
	pvData[i][cCrateComponent] = 0;
	pvData[i][cCrateFish] = 0;
	pvData[i][cCrateFish2] = 0;
	pvData[i][cCrateLumber] = 0;
	pvData[i][cCratePlant] = 0;
	pvData[i][cWheat] = 0;
	pvData[i][cCarrot] = 0;
	pvData[i][cPotato] = 0;
	pvData[i][cCorn] = 0;
	pvData[i][cImpound] = 0;
	pvData[i][vLockTire] = 0;
	pvData[i][cVehicleGarage] = -1;
	for(new j = 0; j < 10; j++)
	{
		pvData[i][cWeapon][j] = 0;
		pvData[i][cAmmo][j] = 0;
	}
	pvData[i][vDestroyed] = -1;
	for(new j = 0; j < MAX_MODS; j++)
		pvData[i][cMod][j] = 0;
	if(IsValidDynamic3DTextLabel(pvData[i][vLockTireText])) DestroyDynamic3DTextLabel(pvData[i][vLockTireText]);
	Iter_Add(PVehicles, i);
	OnPlayerVehicleRespawn(i);
	//SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You have purchased a vehicle for "GREEN_E"$%s "WHITE_E"with model {00FFFF}%s", FormatMoney(cost), GetVehicleModelName(model));
	PutPlayerInVehicle(playerid, pvData[i][cVeh], 0);
	SetPVarInt(playerid, "CarID", pvData[i][cVeh]);
	//pData[playerid][pBuyPvModel] = 0;
	return 1;
}

function OnVehBuyPV(playerid, pid, model, color1, color2, cost, Float:x, Float:y, Float:z, Float:a)
{
	new i = Iter_Free(PVehicles);
	pvData[i][cID] = cache_insert_id();
	pvData[i][cOwner] = pid;
	pvData[i][cModel] = model;
	pvData[i][cColor1] = color1;
	pvData[i][cColor2] = color2;
	pvData[i][cPaintJob] = -1;
	pvData[i][cNeon] = 0;
	pvData[i][cTogNeon] = 0;
	pvData[i][cLocked] = 0;
	pvData[i][cInsu] = 3;
	pvData[i][cClaim] = 0;
	pvData[i][cClaimTime] = 0;
	pvData[i][cTicket] = 0;
	pvData[i][cPrice] = cost;
	pvData[i][cHealth] = 2000;
	pvData[i][cFuel] = 1000;
	format(pvData[i][cPlate], 16, "No Have");
	pvData[i][cPlateTime] = 0;
	pvData[i][cPosX] = x;
	pvData[i][cPosY] = y;
	pvData[i][cPosZ] = z;
	pvData[i][cPosA] = a;
	pvData[i][cInt] = 0;
	pvData[i][cVw] = 0;
	pvData[i][cLumber] = 0;
	pvData[i][cMesinUpgrade] = 0;
	pvData[i][pvBodyUpgrade] = 0;
	pvData[i][cRent] = 0;
	pvData[i][cCrack] = 0;
	pvData[i][cPot] = 0;
	pvData[i][cMaterial] = 0;
	pvData[i][cCgun] = 0;
	pvData[i][cComponent] = 0;
	pvData[i][cCrateComponent] = 0;
	pvData[i][cCrateFish] = 0;
	pvData[i][cCrateFish2] = 0;
	pvData[i][cCrateLumber] = 0;
	pvData[i][cCratePlant] = 0;
	pvData[i][cWheat] = 0;
	pvData[i][cCarrot] = 0;
	pvData[i][cPotato] = 0;
	pvData[i][cCorn] = 0;
	pvData[i][cImpound] = 0;
	pvData[i][vLockTire] = 0;
	pvData[i][cVehicleGarage] = -1;
	for(new j = 0; j < 10; j++)
	{
		pvData[i][cWeapon][j] = 0;
		pvData[i][cAmmo][j] = 0;
	}
	pvData[i][vDestroyed] = -1;
	for(new j = 0; j < MAX_MODS; j++)
		pvData[i][cMod][j] = 0;
	if(IsValidDynamic3DTextLabel(pvData[i][vLockTireText])) DestroyDynamic3DTextLabel(pvData[i][vLockTireText]);
	Iter_Add(PVehicles, i);
	OnPlayerVehicleRespawn(i);
	SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You have purchased a vehicle for "GREEN_E"$%s "WHITE_E"with model {00FFFF}%s", FormatMoney(cost), GetVehicleModelName(model));
	PutPlayerInVehicle(playerid, pvData[i][cVeh], 0);
	SetPVarInt(playerid, "CarID", pvData[i][cVeh]);
	pData[playerid][pBuyPvModel] = 0;
	return 1;
}

function OnVehBuyPVBOAT(playerid, pid, model, color1, color2, cost, Float:x, Float:y, Float:z, Float:a)
{
	new i = Iter_Free(PVehicles);
	pvData[i][cID] = cache_insert_id();
	pvData[i][cOwner] = pid;
	pvData[i][cModel] = model;
	pvData[i][cColor1] = color1;
	pvData[i][cColor2] = color2;
	pvData[i][cPaintJob] = -1;
	pvData[i][cNeon] = 0;
	pvData[i][cTogNeon] = 0;
	pvData[i][cLocked] = 0;
	pvData[i][cInsu] = 3;
	pvData[i][cClaim] = 0;
	pvData[i][cClaimTime] = 0;
	pvData[i][cTicket] = 0;
	pvData[i][cPrice] = cost;
	pvData[i][cHealth] = 2000;
	pvData[i][cFuel] = 1000;
	format(pvData[i][cPlate], 16, "No Have");
	pvData[i][cPlateTime] = 0;
	pvData[i][cPosX] = x;
	pvData[i][cPosY] = y;
	pvData[i][cPosZ] = z;
	pvData[i][cPosA] = a;
	pvData[i][cInt] = 0;
	pvData[i][cVw] = 0;
	pvData[i][cLumber] = 0;
	pvData[i][cMesinUpgrade] = 0;
	pvData[i][pvBodyUpgrade] = 0;
	pvData[i][cRent] = 0;
	pvData[i][cCrack] = 0;
	pvData[i][cPot] = 0;
	pvData[i][cMaterial] = 0;
	pvData[i][cCgun] = 0;
	pvData[i][cComponent] = 0;
	pvData[i][cCrateComponent] = 0;
	pvData[i][cCrateFish] = 0;
	pvData[i][cCrateFish2] = 0;
	pvData[i][cCrateLumber] = 0;
	pvData[i][cCratePlant] = 0;
	pvData[i][cWheat] = 0;
	pvData[i][cCarrot] = 0;
	pvData[i][cPotato] = 0;
	pvData[i][cCorn] = 0;
	pvData[i][cImpound] = 0;
	pvData[i][vLockTire] = 0;
	pvData[i][cVehicleGarage] = -1;
	for(new j = 0; j < 10; j++)
	{
		pvData[i][cWeapon][j] = 0;
		pvData[i][cAmmo][j] = 0;
	}
	pvData[i][vDestroyed] = -1;
	for(new j = 0; j < MAX_MODS; j++)
		pvData[i][cMod][j] = 0;
	if(IsValidDynamic3DTextLabel(pvData[i][vLockTireText])) DestroyDynamic3DTextLabel(pvData[i][vLockTireText]);
	Iter_Add(PVehicles, i);
	OnPlayerVehicleRespawn(i);
	SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You have purchased a vehicle for "GREEN_E"%s "WHITE_E"with model {00FFFF}%s", FormatMoney(GetVehicleCost(model)), GetVehicleModelName(model));
	PutPlayerInVehicle(playerid, pvData[i][cVeh], 0);
	pData[playerid][pBuyPvModel] = 0;
	return 1;
}

function OnVehBuyPVLS(playerid, pid, model, color1, color2, cost, Float:x, Float:y, Float:z, Float:a)
{
	new i = Iter_Free(PVehicles);
	pvData[i][cID] = cache_insert_id();
	pvData[i][cOwner] = pid;
	pvData[i][cModel] = model;
	pvData[i][cColor1] = color1;
	pvData[i][cColor2] = color2;
	pvData[i][cPaintJob] = -1;
	pvData[i][cNeon] = 0;
	pvData[i][cTogNeon] = 0;
	pvData[i][cLocked] = 0;
	pvData[i][cInsu] = 3;
	pvData[i][cClaim] = 0;
	pvData[i][cClaimTime] = 0;
	pvData[i][cTicket] = 0;
	pvData[i][cPrice] = cost;
	pvData[i][cHealth] = 2000;
	pvData[i][cFuel] = 1000;
	format(pvData[i][cPlate], 16, "No Have");
	pvData[i][cPlateTime] = 0;
	pvData[i][cPosX] = x;
	pvData[i][cPosY] = y;
	pvData[i][cPosZ] = z;
	pvData[i][cPosA] = a;
	pvData[i][cInt] = 0;
	pvData[i][cVw] = 0;
	pvData[i][cLumber] = 0;
	pvData[i][cMesinUpgrade] = 0;
	pvData[i][pvBodyUpgrade] = 0;
	pvData[i][cRent] = 0;
	pvData[i][cCrack] = 0;
	pvData[i][cPot] = 0;
	pvData[i][cMaterial] = 0;
	pvData[i][cCgun] = 0;
	pvData[i][cComponent] = 0;
	pvData[i][cCrateComponent] = 0;
	pvData[i][cCrateFish] = 0;
	pvData[i][cCrateFish2] = 0;
	pvData[i][cCrateLumber] = 0;
	pvData[i][cCratePlant] = 0;
	pvData[i][cWheat] = 0;
	pvData[i][cCarrot] = 0;
	pvData[i][cPotato] = 0;
	pvData[i][cCorn] = 0;
	pvData[i][cImpound] = 0;
	pvData[i][cDespawn] = 0;
	pvData[i][vLockTire] = 0;
	pvData[i][cVehicleGarage] = -1;
	for(new j = 0; j < 10; j++)
	{
		pvData[i][cWeapon][j] = 0;
		pvData[i][cAmmo][j] = 0;
	}
	pvData[i][vDestroyed] = -1;
	for(new j = 0; j < MAX_MODS; j++)
		pvData[i][cMod][j] = 0;
	if(IsValidDynamic3DTextLabel(pvData[i][vLockTireText])) DestroyDynamic3DTextLabel(pvData[i][vLockTireText]);
	Iter_Add(PVehicles, i);
	OnPlayerVehicleRespawn(i);
	SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You have purchased a vehicle for "GREEN_E"%s "WHITE_E"with model {00FFFF}%s", FormatMoney(cost), GetVehicleModelName(model));
	PutPlayerInVehicle(playerid, pvData[i][cVeh], 0);
	pData[playerid][pBuyPvModel] = 0;
	return 1;
}

function OnVehRentPV(playerid, pid, model, color1, color2, cost, Float:x, Float:y, Float:z, Float:a, rental)
{
	new i = Iter_Free(PVehicles);
	pvData[i][cID] = cache_insert_id();
	pvData[i][cOwner] = pid;
	pvData[i][cModel] = model;
	pvData[i][cColor1] = color1;
	pvData[i][cColor2] = color2;
	pvData[i][cPaintJob] = -1;
	pvData[i][cNeon] = 0;
	pvData[i][cTogNeon] = 0;
	pvData[i][cLocked] = 0;
	pvData[i][cInsu] = 3;
	pvData[i][cClaim] = 0;
	pvData[i][cClaimTime] = 0;
	pvData[i][cTicket] = 0;
	pvData[i][cPrice] = cost;
	pvData[i][cHealth] = 2000;
	pvData[i][cFuel] = 1000;
	format(pvData[i][cPlate], 16, "RENTAL");
	pvData[i][cPlateTime] = 0;
	pvData[i][cPosX] = x;
	pvData[i][cPosY] = y;
	pvData[i][cPosZ] = z;
	pvData[i][cPosA] = a;
	pvData[i][cInt] = 0;
	pvData[i][cVw] = 0;
	pvData[i][cLumber] = 0;
	pvData[i][cMesinUpgrade] = 0;
	pvData[i][pvBodyUpgrade] = 0;
	pvData[i][cRent] = rental;
	pvData[i][cCrack] = 0;
	pvData[i][cPot] = 0;
	pvData[i][cMaterial] = 0;
	pvData[i][cCgun] = 0;
	pvData[i][cComponent] = 0;
	pvData[i][cCrateComponent] = 0;
	pvData[i][cCrateFish] = 0;
	pvData[i][cCrateFish2] = 0;
	pvData[i][cCrateLumber] = 0;
	pvData[i][cCratePlant] = 0;
	pvData[i][cWheat] = 0;
	pvData[i][cCarrot] = 0;
	pvData[i][cPotato] = 0;
	pvData[i][cCorn] = 0;
	pvData[i][cImpound] = 0;
	pvData[i][vLockTire] = 0;
	pvData[i][cVehicleGarage] = -1;
	for(new j = 0; j < 10; j++)
	{
		pvData[i][cWeapon][j] = 0;
		pvData[i][cAmmo][j] = 0;
	}
	pvData[i][vDestroyed] = -1;
	for(new j = 0; j < MAX_MODS; j++)
		pvData[i][cMod][j] = 0;
	if(IsValidDynamic3DTextLabel(pvData[i][vLockTireText])) DestroyDynamic3DTextLabel(pvData[i][vLockTireText]);
	
	pData[playerid][pRents] = pvData[i][cID];
	Iter_Add(PVehicles, i);
	OnPlayerVehicleRespawn(i);
	SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You have rented a vehicle with a {00FFFF}model %s", GetVehicleModelName(model));
	PutPlayerInVehicle(playerid, pvData[i][cVeh], 0);
	pData[playerid][pBuyPvModel] = 0;
	return 1;
}

function VehBuyVIP(playerid, pid, model, color1, color2, cost, Float:x, Float:y, Float:z, Float:a)
{
	new i = Iter_Free(PVehicles);
	pvData[i][cID] = cache_insert_id();
	pvData[i][cOwner] = pid;
	pvData[i][cModel] = model;
	pvData[i][cColor1] = color1;
	pvData[i][cColor2] = color2;
	pvData[i][cPaintJob] = -1;
	pvData[i][cNeon] = 0;
	pvData[i][cTogNeon] = 0;
	pvData[i][cLocked] = 0;
	pvData[i][cInsu] = 3;
	pvData[i][cClaim] = 0;
	pvData[i][cClaimTime] = 0;
	pvData[i][cTicket] = 0;
	pvData[i][cPrice] = cost;
	pvData[i][cHealth] = 2000;
	pvData[i][cFuel] = 1000;
	format(pvData[i][cPlate], 16, "No Have");
	pvData[i][cPlateTime] = 0;
	pvData[i][cPosX] = x;
	pvData[i][cPosY] = y;
	pvData[i][cPosZ] = z;
	pvData[i][cPosA] = a;
	pvData[i][cInt] = 0;
	pvData[i][cVw] = 0;
	pvData[i][cLumber] = 0;
	pvData[i][cMesinUpgrade] = 0;
	pvData[i][pvBodyUpgrade] = 0;
	pvData[i][cRent] = 0;
	pvData[i][cCrack] = 0;
	pvData[i][cPot] = 0;
	pvData[i][cMaterial] = 0;
	pvData[i][cCgun] = 0;
	pvData[i][cComponent] = 0;
	pvData[i][cCrateComponent] = 0;
	pvData[i][cCrateFish] = 0;
	pvData[i][cCrateFish2] = 0;
	pvData[i][cCrateLumber] = 0;
	pvData[i][cCratePlant] = 0;
	pvData[i][cWheat] = 0;
	pvData[i][cCarrot] = 0;
	pvData[i][cPotato] = 0;
	pvData[i][cCorn] = 0;
	pvData[i][cImpound] = 0;
	pvData[i][vLockTire] = 0;
	pvData[i][cVehicleGarage] = -1;
	for(new j = 0; j < 10; j++)
	{
		pvData[i][cWeapon][j] = 0;
		pvData[i][cAmmo][j] = 0;
	}
	pvData[i][vDestroyed] = -1;
	for(new j = 0; j < MAX_MODS; j++)
		pvData[i][cMod][j] = 0;
	if(IsValidDynamic3DTextLabel(pvData[i][vLockTireText])) DestroyDynamic3DTextLabel(pvData[i][vLockTireText]);
	Iter_Add(PVehicles, i);
	OnPlayerVehicleRespawn(i);
	SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You have purchased a vehicle for "GREEN_E"%s "WHITE_E"with model {00FFFF}%s", FormatMoney(GetVehicleDealerCost(model)), GetVehicleModelName(model));
	PutPlayerInVehicle(playerid, pvData[i][cVeh], 0);
	pData[playerid][pBuyPvModel] = 0;
	return 1;
}

function RespawnPV(vehicleid)
{
	SetVehicleToRespawn(vehicleid);
	SetValidVehicleHealth(vehicleid, 1000);
	SetVehicleFuel(vehicleid, 1000);
	return 1;
}

Vehicle_WeaponStorage(playerid, vehicleid)
{
    foreach(new ii : PVehicles)
	{
		if(pvData[ii][cVeh] == vehicleid)
		{

			static
				string[320];

			string[0] = 0;

			for (new i = 0; i < 5; i ++)
			{
				if(!pvData[ii][cWeapon][i])
					format(string, sizeof(string), "%sEmpty Slot\n", string);

				else
					format(string, sizeof(string), "%s%s (Ammo: %d)\n", string, ReturnWeaponName(pvData[ii][cWeapon][i]), pvData[ii][cAmmo][i]);
			}
			Dialog_Show(playerid, PVehicleWeapon, DIALOG_STYLE_LIST, "Weapon Storage", string, "Select", "Cancel");
		}
	}	
	return 1;
}

Vehicle_OpenStorage(playerid, vehicleid)
{
	foreach(new ii : PVehicles)
	{
		if(pvData[ii][cVeh] == vehicleid && pvData[ii][cOwner] == pData[playerid][pID] && pvData[ii][cLocked] == 0)
		{
			new
				items[1],
				string[212];

			for (new i = 0; i < 5; i ++) if(pvData[ii][cWeapon][i])
			{
				items[0]++;
			}
			pData[playerid][pUseVehicleid] = pvData[ii][cVeh];
			format(string, sizeof(string), "Weapon Storage (%d/5)\nComponent (%d/2000)\nMaterial (%d/2000)\nCrack (%d/1000)\nPot (%d/1000)", items[0], pvData[ii][cComponent], pvData[ii][cMaterial], pvData[ii][cCrack], pvData[ii][cPot]);

			Dialog_Show(playerid, PVehicleStorage, DIALOG_STYLE_LIST, "Trunk Storage", string, "Select", "Cancel");
		}	
	}	
    return 1;
}

Vehicle_OpenStorageSAPD(playerid, vehicleid)
{
	foreach(new ii : PVehicles)
	{
		if(pvData[ii][cVeh] == vehicleid)
		{
			new
				items[1],
				string[212];

			for (new i = 0; i < 5; i ++) if(pvData[ii][cWeapon][i])
			{
				items[0]++;
			}
			pData[playerid][pUseVehicleid] = pvData[ii][cVeh];
			format(string, sizeof(string), "Weapon Storage (%d/5)\nComponent (%d/2000)\nMaterial (%d/2000)\nCrack (%d/1000)\nPot (%d/1000)", items[0], pvData[ii][cComponent], pvData[ii][cMaterial], pvData[ii][cCrack], pvData[ii][cPot]);

			Dialog_Show(playerid, PVehicleStorage, DIALOG_STYLE_LIST, "Trunk Storage", string, "Select", "Cancel");
		}	
	}	
    return 1;
}

GetDistanceToCar(playerid, veh, Float: posX = 0.0, Float: posY = 0.0, Float: posZ = 0.0) {

	new
	    Float: Floats[2][3];

	if(posX == 0.0 && posY == 0.0 && posZ == 0.0) {
		if(!IsPlayerInAnyVehicle(playerid)) GetPlayerPos(playerid, Floats[0][0], Floats[0][1], Floats[0][2]);
		else GetVehiclePos(GetPlayerVehicleID(playerid), Floats[0][0], Floats[0][1], Floats[0][2]);
	}
	else {
		Floats[0][0] = posX;
		Floats[0][1] = posY;
		Floats[0][2] = posZ;
	}
	GetVehiclePos(veh, Floats[1][0], Floats[1][1], Floats[1][2]);
	return floatround(floatsqroot((Floats[1][0] - Floats[0][0]) * (Floats[1][0] - Floats[0][0]) + (Floats[1][1] - Floats[0][1]) * (Floats[1][1] - Floats[0][1]) + (Floats[1][2] - Floats[0][2]) * (Floats[1][2] - Floats[0][2])));
}

GetClosestCar(playerid, exception = INVALID_VEHICLE_ID) 
{

    new
		Float: Distance,
		target = -1,
		Float: vPos[3];

	if(!IsPlayerInAnyVehicle(playerid)) GetPlayerPos(playerid, vPos[0], vPos[1], vPos[2]);
	else GetVehiclePos(GetPlayerVehicleID(playerid), vPos[0], vPos[1], vPos[2]);

    for(new v; v < MAX_VEHICLES; v++) if(GetVehicleModel(v) >= 400) {
        if(v != exception && (target < 0 || Distance > GetDistanceToCar(playerid, v, vPos[0], vPos[1], vPos[2]))) {
            target = v;
            Distance = GetDistanceToCar(playerid, v, vPos[0], vPos[1], vPos[2]); // Before the rewrite, we'd be running GetPlayerPos 2000 times...
        }
    }
    return target;
}

stock GetPlayerVehicle(playerid, vehicleid)
{
	if(!IsPlayerConnected(playerid)) return -1;
	if(!GetVehicleModel(vehicleid)) return -1;
    for(new v = 0; v < MAX_VEHICLES; v++)
    {
        if(pvData[v][cID] == vehicleid)
        {
            return v;
        }
    }
    return -1;
}

CountPlayerVehicle(playerid)
{
	new count = 0;
	foreach(new vehicle : PVehicles) {
		if(IsValidVehicle(pvData[vehicle][cVeh]))
		{
			if(pvData[vehicle][cOwner] == pData[playerid][pID] && pvData[vehicle][cClaim] == 0 && pvData[vehicle][cImpound] == 0 && pvData[vehicle][cVehicleGarage] == -1)
			{
				count++;
			}
		}
	}
	return count;
}

GetStatusVehiclePlayer(vehicle)
{
	new type[128];
	if(pvData[vehicle][cVehicleGarage] == 1) type= ""YELLOW_E"Garage";
	else if(pvData[vehicle][cImpound] == 1) type= ""RED_E"Impound";
	else if(pvData[vehicle][cClaim] == 1) type= ""RED_E"Insurance";
	else if(pvData[vehicle][cClaim] == 1) type= ""RED_E"Insurance";
	else if(pvData[vehicle][cDespawn] == 1) type= ""ORANGE_E"Despawn";
	else if(pvData[vehicle][cLocked] == 0) type= ""GREEN_E"Unlocked";
	else if(pvData[vehicle][cRent]) type= ""AQUA_E"Rental";
	return type;
}

IsValidPlayerVehicle(playerid, vehicle)
{
	if(pvData[vehicle][cOwner] == pData[playerid][pID] && pvData[vehicle][cClaim] == 0 && pvData[vehicle][cImpound] == 0 && pvData[vehicle][cVehicleGarage] == -1) return 1;
	return 0;
}

SetVehicleRadio(vehicleid, url[])
{
    if(IsValidVehicle(vehicleid) && IsEngineVehicle(vehicleid))
    {
        CoreVehicles[vehicleid][vehRadio] = 1;
        strpack(CoreVehicles[vehicleid][vehURL], url, 128 char);

        new
            Float:fVehX,
            Float:fVehY,
            Float:fVehZ,
            Float:fDist;

        GetVehiclePos(vehicleid, fVehX, fVehY, fVehZ);

        foreach (new i : Player)
        {
            if(!IsPlayerConnected(i)) continue;

            // Player di dalam kendaraan — set flag
            if(IsPlayerInVehicle(i, vehicleid))
            {
                pData[i][pRadioVehicleOn] = 1;
                pData[i][pRadioVehicleVeh] = vehicleid;
                pData[i][pRadioVehicleListening] = 0;
                StopAudioStreamForPlayer(i);
                PlayAudioStreamForPlayer(i, url);
            }
            else
            {
                // Player di luar kendaraan — cek jarak (radius 30 meter)
                fDist = GetPlayerDistanceFromPoint(i, fVehX, fVehY, fVehZ);
                if(fDist <= 30.0 && GetPlayerInterior(i) == 0 && GetPlayerVirtualWorld(i) == 0)
                {
                    pData[i][pRadioVehicleListening] = 1;
                    pData[i][pRadioVehicleVeh] = vehicleid;
                    StopAudioStreamForPlayer(i);
                    PlayAudioStreamForPlayer(i, url);
                }
            }
        }
    }
    return 1;
}

StopVehicleRadio(vehicleid)
{
    if((IsValidVehicle(vehicleid) && IsEngineVehicle(vehicleid)) && CoreVehicles[vehicleid][vehRadio])
    {
        CoreVehicles[vehicleid][vehRadio] = 0;

        foreach (new i : Player)
        {
            if(!IsPlayerConnected(i)) continue;

            if(IsPlayerInVehicle(i, vehicleid) && pData[i][pRadioVehicleOn])
            {
                StopAudioStreamForPlayer(i);
                pData[i][pRadioVehicleOn] = 0;
            }

            if(pData[i][pRadioVehicleListening] && pData[i][pRadioVehicleVeh] == vehicleid)
            {
                StopAudioStreamForPlayer(i);
                pData[i][pRadioVehicleListening] = 0;
                pData[i][pRadioVehicleVeh] = 0;
            }
        }
    }
    return 1;
}

SendVehicleOwnedMessage(id, text[]) {
	foreach(new vehicleid : PVehicles) if(pvData[vehicleid][cVeh] == id) {
		foreach(new i : Player) if(pvData[vehicleid][cOwner] == pData[i][pID]) {
			SendClientMessageEx(i, COLOR_ARWIN, text);
			return 1;
		}
	}
    return 0;
}

stock GetClosestVehicleToVehicle(vehicleid, ignoredid = INVALID_VEHICLE_ID) {
    new Float:distance = 10, closestid = INVALID_VEHICLE_ID, Float:distance2, vw = GetVehicleVirtualWorld(vehicleid);

    foreach (new i : Vehicle) {
		if (vehicleid == i || i == ignoredid || vw != GetVehicleVirtualWorld(i)) {
            continue;
        }

        if ((distance2 = GetDistanceBetweenVehicles(vehicleid, i)) < distance) {
            distance = distance2;
            closestid = i;
        }
    }

    return closestid;
}

GetVehicleNameByVehicle(vehicleid, dest[], len = sizeof(dest))
{
    new
        model = GetVehicleModel(vehicleid);

    if(model < 400 || model > 611)
        format(dest, len, "None");
    else
        format(dest, len, g_arrVehicleNames[model - 400]);
    
    return 1;
}

GetVehicleNumberPlate(vehicleid, dest[], len = sizeof(dest)) {
    new id = -1;
    if ((id = Vehicle_GetID(vehicleid)) != -1) {
        format(dest,len,"%s",pvData[id][cPlate]);
    } else format(dest,len,"STATIC");
}

GetVehicleDirection(vehicleid, dest[], len = sizeof(dest)) {
    new Float:angle;
    GetVehicleZAngle(vehicleid, angle);

    static const directionName[][] = {
        "North",
        "NE",
        "East",
        "SE",
        "South",
        "SW",
        "West",
        "NW"
    };

    new angleConvert = floatround(angle), index = (((angleConvert %= 360) < 0 ? angleConvert + 360 : angleConvert) / 45) % 8;
    format(dest, len, "%s", directionName[index]);
    return 1;
}

GetPlayerDirection(playerid, dest[], len = sizeof(dest)) {
    new Float:angle;

    if(IsPlayerInAnyVehicle(playerid))
    {
    	GetVehicleZAngle(GetPlayerVehicleID(playerid), angle);
    }
    else
    {
    	GetPlayerFacingAngle(playerid, angle);
	}

    static const directionName[][] = {
        "N",
        "NW",
        "W",
        "SW",
        "S",
        "SE",
        "E",
        "NE"
    };

    new angleConvert = floatround(angle), index = (((angleConvert %= 360) < 0 ? angleConvert + 360 : angleConvert) / 45) % 8;
    format(dest, len, "%s", directionName[index]);
    return 1;
}

GetVehicleNameByModel(model)
{
    new
        name[32] = "None";

    if(model < 400 || model > 611)
        return name;

    format(name, sizeof(name), g_arrVehicleNames[model - 400]);
    return name;
}
