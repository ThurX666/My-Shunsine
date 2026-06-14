CMD:createpv(playerid, params[])
{
	if(pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);
	
	new model, color1, color2, otherid;
	if(sscanf(params, "uddd", otherid, model, color1, color2)) return Usage(playerid, "/createpv [name/playerid] [model] [color1] [color2]");
	
	if(color1 < 0 || color1 > 255) { Error(playerid, "Color Number can't be below 0 or above 255 !"); return 1; }
    if(color2 < 0 || color2 > 255) { Error(playerid, "Color Number can't be below 0 or above 255 !"); return 1; }
    if(model < 400 || model > 611) { Error(playerid, "Vehicle Number can't be below 400 or above 611 !"); return 1; }
	if(otherid == INVALID_PLAYER_ID) return Error(playerid, "Invalid player ID!");
	new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(playerid);
	if(count >= limit)
	{
		Error(playerid, "This player have too many vehicles, sell a vehicle first!");
		return 1;
	}
	new cQuery[1024];
	new Float:x,Float:y,Float:z, Float:a;
    GetPlayerPos(otherid,x,y,z);
    GetPlayerFacingAngle(otherid,a);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[otherid][pID], model, color1, color2, x, y, z, a);
	mysql_tquery(g_SQL, cQuery, "OnVehCreated", "ddddddffff", playerid, otherid, pData[otherid][pID], model, color1, color2, x, y, z, a);
	return 1;
}

CMD:deletepv(playerid, params[])
{
	if(pData[playerid][pAdmin] < 6)
		return PermissionError(playerid);
		
	new vehid;
	if(sscanf(params, "d", vehid)) return Usage(playerid, "/deletepv [vehid] | /apv - for find vehid");
	if(vehid == INVALID_VEHICLE_ID) return Error(playerid, "Invalid id");
	if(vehid < 2) return Error(playerid, "Tidak bisa di bawah 1");		
	foreach(new i : PVehicles)			
	{
		if(vehid == pvData[i][cVeh])
		{
			Servers(playerid, "Your deleted private vehicle id %d (database id: %d).", vehid, pvData[i][cID]);
			new query[128];
			mysql_format(g_SQL, query, sizeof(query), "DELETE FROM vehicle WHERE id = '%d'", pvData[i][cID]);
			mysql_tquery(g_SQL, query);
			Vehicle_ObjectDestroy(pvData[i][cVeh]);
			for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++) Vehicle_ObjectDelete(pvData[i][cVeh], slot);
			for(new ii; ii < 5; ii++) if(IsValidDynamicObject(ObjectVehicle[pvData[i][cVeh]][ii])) DestroyDynamicObject(ObjectVehicle[pvData[i][cVeh]][ii]);
			if(IsValidVehicle(pvData[i][cVeh])) DestroyVehicle(pvData[i][cVeh]);
			Iter_SafeRemove(PVehicles, i, i);
		}
	}
	return 1;
}

CMD:pvlist(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);
	
	new count = 0, created = 0;
	foreach(new i : PVehicles)
	{
		count++;
		if(IsValidVehicle(pvData[i][cVeh]))
		{
			created++;
		}
	}
	SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"Foreach total: %d, Created: %d", count, created);
	return 1;
}

CMD:ainsu(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);
	
	new otherid;
	if(sscanf(params, "u", otherid)) return Usage(playerid, "/ainsu [name/playerid]");
	if(otherid == INVALID_PLAYER_ID || !IsPlayerConnected(otherid)) return Error(playerid, "Invalid playerid");
	
	new bool:found = false, msg2[512];
	format(msg2, sizeof(msg2), "ID\tInsurance\tClaim Time\tTicket\n");
	foreach(new i : PVehicles)
	{
		if(pvData[i][cOwner] == pData[otherid][pID])
		{
			if(pvData[i][cClaimTime] != 0)
			{
				format(msg2, sizeof(msg2), "%s\t%d\t%s - %d\t%s\t%s\n", msg2, pvData[i][cVeh], GetVehicleModelName(pvData[i][cModel]), pvData[i][cVeh], pvData[i][cInsu], experieddate(pvData[i][cClaimTime], 3), FormatMoney(pvData[i][cTicket]));
				found = true;
			}
			else
			{
				format(msg2, sizeof(msg2), "%s\t%d\t%s - %d\tClaimed\t%s\n", msg2, pvData[i][cVeh], GetVehicleModelName(pvData[i][cModel]), pvData[i][cVeh], pvData[i][cInsu], FormatMoney(pvData[i][cTicket]));
				found = true;
			}
		}
	}
	if(found)
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Insurance Vehicles", msg2, "Close", "");
	else
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Vehicles", "Player tidak memeliki kendaraan", "Close", "");
	return 1;
}

CMD:limitspeed(playerid, params[])
{
    if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) // mengambil state driver
    {
        new Float:speed;
        if(sscanf(params, "f", speed))
            return Usage(playerid, "/limitspeed [speed / 0 untuk mematikan]"); // memberikan client message jika parameter float null
        if(speed > 200)
        	return Error(playerid, "tidak bisa di atas 200!");
        
        if(speed > 1.0)
        {
            SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"SetSpeed Lock %f", speed); // Memberikan Client Message saat vehicle Limit Berhasil di Execute
            SetVehicleSpeedCap(GetPlayerVehicleID(playerid), speed); // Function ini berguna untuk membatasi Kecepatan suatu Kendaraan terhadap Speed yang sudah di Execute
        }
        else if(speed < 1.0)
        {
            SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"Kamu Mematikan SetSpeed"); // Client Message disable
            DisableVehicleSpeedCap(GetPlayerVehicleID(playerid)); // mendisable Speed Limit jika angka float dibawah angka 1
        }
    }
    return 1;
}

CMD:aveh(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);
		
	new vehicleid = GetNearestVehicleToPlayer(playerid, 5.0, false);

	if(vehicleid == INVALID_VEHICLE_ID)
		return Error(playerid, "You not in near any vehicles.");
	
	SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"Vehicle ID near on you id: %d (Model: %s(%d))", vehicleid, GetVehicleName(vehicleid), GetVehicleModel(vehicleid));
	return 1;
}

CMD:avehhealth(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);
		
	new vehicleid = GetNearestVehicleToPlayer(playerid, 5.0, false);
	new Float:health, engine;
	if(vehicleid == INVALID_VEHICLE_ID) return Error(playerid, "You not in near any vehicles.");
	GetVehicleHealth(vehicleid, health);
	engine = floatround(health, floatround_round) / 20;

	Info(playerid, "health %d", engine);
	return 1;
}

CMD:putpv(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);
	new vehid;
	if(sscanf(params, "d", vehid)) return Usage(playerid, "/putpv [vehid] | /v my - for find vehid");
	if(vehid == INVALID_VEHICLE_ID) return Error(playerid, "Invalid id");
	if(!IsValidVehicle(vehid)) return Error(playerid, "Invalid veh id");
	PutPlayerInVehicle(playerid, vehid, 0);
	return 1;
}

CMD:pdveh(playerid, params[])
{
	if(pData[playerid][pFaction] != 1)
        return Error(playerid, "Anda bukan petugas kepolisian.");

	new vehicleid = GetNearestVehicleToPlayer(playerid, 5.0, false);

	if(vehicleid == INVALID_VEHICLE_ID)
		return Error(playerid, "You not in near any vehicles.");

	SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"Vehicle ID near on you id: "YELLOW_E"%d (Model: %s(%d))", vehicleid, GetVehicleName(vehicleid), GetVehicleModel(vehicleid));
	return 1;
}

CMD:sendveh(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);
	
	new otherid, vehid, Float:x, Float:y, Float:z;
	if(sscanf(params, "ud", otherid, vehid)) return Usage(playerid, "/sendveh [playerid/name] [vehid] | /apv - for find vehid");
	
	if(!IsPlayerConnected(otherid)) return Error(playerid, "Player id not online!");
	if(!IsValidVehicle(vehid)) return Error(playerid, "Invalid veh id");
	
	GetPlayerPos(otherid, x, y, z);
	SetVehiclePos(vehid, x, y, z+0.5);
	SetVehicleVirtualWorld(vehid, GetPlayerVirtualWorld(otherid));
	LinkVehicleToInterior(vehid, GetPlayerInterior(otherid));
	SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"Your has send vehicle id %d to player %s(%d) | Location: %s.", vehid, pData[otherid][pName], otherid, GetLocation(x, y, z));
	return 1;
}

CMD:seatbelt(playerid,params[])
{
    if(IsPlayerInAnyVehicle(playerid) && Seatbelt{playerid} == 0 && !IsABike(GetPlayerVehicleID(playerid)))
    {
        Seatbelt{playerid} = 1;
        // SetPlayerAttachedObject(playerid, JOB_SLOT, 18634, 7,0.000000, 0.100000, 0.350000, -35.224993, 45.215000, 1.500000, 5.000000, 1.500000, 1.500000);
        SendClientMessage(playerid, COLOR_GREEN, "You have put on your seatbelt. This will supress the impact of a crash.");
        callcmd::ame(playerid, "reaches for their seatbelt, and takes it off");
    }
    else if(IsPlayerInAnyVehicle(playerid) && Seatbelt{playerid} == 1 && !IsABike(GetPlayerVehicleID(playerid)))
    {
        Seatbelt{playerid} = 0;
        SendClientMessage(playerid, COLOR_GREEN, "You have taken off your seatbelt. You will no longer be protected from crashes.");
        callcmd::ame(playerid, "reaches for their seatbelt, and unbuckles it");
        // if(IsPlayerAttachedObjectSlotUsed(playerid, JOB_SLOT)) RemovePlayerAttachedObject(playerid, JOB_SLOT);
    }
    return 1;
}

CMD:checkseatbelt(playerid, params[])
{
    new userID,string[128];
    if(sscanf(params, "u", userID)) return Usage(playerid, "/checkseatbelt [playerid]");
    if(pData[playerid][pFaction] != 1) return Error(playerid, "You must be a police officer.");
    if(!pData[playerid][pOnDuty]) return Error(playerid, "You must duty first.");
    if(IsPlayerConnected(userID) && userID != INVALID_PLAYER_ID)
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(userID, x, y, z);
        if(PlayerToPoint(6.0, playerid, x, y, z) && Seatbelt{userID} == 1)
        {
            format(string, sizeof(string), "%s is wearing their seatbelt", ReturnName(playerid));
            SendClientMessage(playerid, COLOR_GREEN, string);
            return 1;
        }
        else if(PlayerToPoint(6.0, playerid, x, y, z) && Seatbelt{userID} == 0)
        {
            format(string, sizeof(string), "%s is not wearing their seatbelt", ReturnName(playerid));
            SendClientMessage(playerid, COLOR_GREEN, string);
            return 1;
        }
        else
        {
            SendClientMessage(playerid, COLOR_ARWIN, ""WHITE_E"You are not near that player");
            return 1;
        }
    }
    else SendClientMessage(playerid, COLOR_ARWIN, ""WHITE_E"The ID you have entered does not exist");
    return 1;
}

CMD:getveh(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);
		
	new vehid, Float:posisiX, Float:posisiY, Float:posisiZ, Float:posisiA;
	if(sscanf(params, "d", vehid)) return Usage(playerid, "/getveh [vehid] | /apv - for find vehid");
	if(vehid == INVALID_VEHICLE_ID) return Error(playerid, "Invalid id");
	if(!IsValidVehicle(vehid)) return Error(playerid, "Invalid veh id");
	GetPlayerPos(playerid, posisiX, posisiY, posisiZ);
	GetPlayerFacingAngle(playerid, posisiA);
	SendClientMessageEx(playerid, COLOR_ARWIN, "TELEPORT: "AQUA_E"Your get spawn vehicle to %s (vehicle id: %d).", GetLocation(posisiX, posisiY, posisiZ), vehid);
	SetVehiclePos(vehid, posisiX, posisiY, posisiZ+0.5);
	SetVehicleZAngle(vehid, posisiA);
	SetVehicleVirtualWorld(vehid, GetPlayerVirtualWorld(playerid));
	LinkVehicleToInterior(vehid, GetPlayerInterior(playerid));
	PutPlayerInVehicle(playerid, vehid, 0);
	return 1;
}

CMD:gotoveh(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);
		
	new vehid, Float:posisiX, Float:posisiY, Float:posisiZ;
	if(sscanf(params, "d", vehid)) return Usage(playerid, "/gotoveh [vehid] | /apv - for find vehid");
	if(vehid == INVALID_VEHICLE_ID) return Error(playerid, "Invalid id");
	if(!IsValidVehicle(vehid)) return Error(playerid, "Invalid id");
	
	GetVehiclePos(vehid, posisiX, posisiY, posisiZ);
	Servers(playerid, "Your teleport to %s (vehicle id: %d).", GetLocation(posisiX, posisiY, posisiZ), vehid);
	SetPlayerPosition(playerid, posisiX, posisiY, posisiZ+3.0, 4.0, 0);
	return 1;
}

CMD:respawnveh(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);
		
	new vehid, Float:posisiX, Float:posisiY, Float:posisiZ;
	if(sscanf(params, "d", vehid)) return Usage(playerid, "/respawnveh [vehid] | /apv - for find vehid");
	if(vehid == INVALID_VEHICLE_ID) return Error(playerid, "Invalid id");
	if(!IsValidVehicle(vehid)) return Error(playerid, "Invalid id");
	GetVehiclePos(vehid, posisiX, posisiY, posisiZ);
	if(IsVehicleEmpty(vehid))
	{
		SetTimerEx("RespawnPV", 5000, false, "d", vehid);
		Servers(playerid, "Your respawned vehicle location %s (vehicle id: %d).", GetLocation(posisiX, posisiY, posisiZ), vehid);
	}
	else Error(playerid, "This Vehicle in used by someone.");
	return 1;
}

CMD:apv(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);
	
	new otherid;
	if(sscanf(params, "u", otherid)) return Usage(playerid, "/apv [name/playerid]");
	if(otherid == INVALID_PLAYER_ID) return Error(playerid, "Invalid playerid");
	
	new bool:found = false, msg2[512];
	format(msg2, sizeof(msg2), "Model\tStatus\n");
	foreach(new i : PVehicles)
	{
		if(pvData[i][cOwner] == pData[otherid][pID])
		{
			format(msg2, sizeof(msg2), "%s%s(id: %d)\t%s\n", msg2, GetVehicleModelName(pvData[i][cModel]), pvData[i][cVeh], GetStatusVehiclePlayer(i));
			found = true;
		}
	}
	if(found)
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Player Vehicles", msg2, "Close", "");
	else
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Vehicles", "Player ini tidak memeliki kendaraan", "Close", "");
	return 1;
}

CMD:spawnvehicle(playerid, params[])
{
	new found = false, msg2[512];
	new Float:VPos[3];
	
	foreach(new i : PVehicles)
	{
		if(IsValidVehicle(pvData[i][cVeh]))
		{
			GetVehiclePos(pvData[i][cVeh], VPos[0], VPos[1], VPos[2]);
			if(pvData[i][cOwner] == pData[playerid][pID] && IsPlayerInRangeOfPoint(playerid, 5, VPos[0], VPos[1], VPos[2]))
			{
				format(msg2, sizeof(msg2), ""WHITE_E"Kendaraan "AQUA_E"%s "AQUA_E"telah kami despawn untuk mencegah menyatunya dengan kendaraan player lain.", GetVehicleModelName(pvData[i][cModel]));
				found++;
			}
		}
	}
	if(found) Dialog_Show(playerid, DialogVehicle, DIALOG_STYLE_MSGBOX, "Spawn Vehicles", msg2, "Spawn", "Close");
	else ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Spawn Vehicles", "Anda tidak memeliki kendaraan", "Close", "");
	return 1;
}

CMD:mv(playerid, params[])
{		
	new found = false, msg2[512], tsr[512];
	new Float:VPos[3];
	GetPlayerPos(playerid, VPos[0], VPos[1], VPos[2]);
	new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(playerid);
	format(msg2, sizeof(msg2), "#\tVehicle\tDistance\tStatus\n");
	foreach(new i : PVehicles)
	{
		if(pvData[i][cOwner] == pData[playerid][pID])
		{
		// if(IsValidPlayerVehicle(playerid, i))
		// {
			gListedItems[playerid][found] = i;
			found++;
			format(msg2, sizeof(msg2), "%s"WHITE_E"V%d:\t"AQUA_E"%s\t"WHITE_E"%.1f\t%s\n", msg2, pvData[i][cVeh], GetVehicleModelName(pvData[i][cModel]), GetDistanceBetweenPoints(VPos[0], VPos[1], VPos[2], pvData[i][cPosX], pvData[i][cPosY], pvData[i][cPosZ]), GetStatusVehiclePlayer(i));
		}
	}
	format(tsr, sizeof(tsr), "My Vehicle (%d/%d)", count, limit);
	if(found) Dialog_Show(playerid, DialogVehicle, DIALOG_STYLE_TABLIST_HEADERS, tsr, msg2, "Select", "Close");
	else ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Vehicles", "Anda tidak memeliki kendaraan", "Close", "");
	return 1;
}

CMD:spawn(playerid, params[])
{
	new dialog[512], found = false;

	format(dialog, sizeof(dialog), "Vehicle\tDistance\tStatus\n");
	foreach(new i : PVehicles)
	{
		if(IsValidPlayerVehicle(playerid, i))
		{
			gListedItems[playerid][found] = i;
			found++;
			format(dialog, sizeof(dialog), "%s"WHITE_E"%s\t%.1f\t%s\n", dialog, GetVehicleModelName(pvData[i][cModel]), GetPlayerDistanceFromPoint(playerid, pvData[i][cPosX], pvData[i][cPosY], pvData[i][cPosZ]), GetStatusVehiclePlayer(i));
		}
	}
	if (found) Dialog_Show(playerid, VehicleSpawn, DIALOG_STYLE_TABLIST_HEADERS, "Vehicle Unstuck", dialog, "Spawn", "Close");
	else Error(playerid, "Tidak ada kendaraan untuk anda spawn");
}


CMD:lock(playerid, params[])
{
	new found = 0, msg2[512];
	new Float:VPos[3];
	GetPlayerPos(playerid, VPos[0], VPos[1], VPos[2]);
	format(msg2, sizeof(msg2), "#\tVehicle\tDistance\tStatus\n");
	format(msg2,sizeof(msg2),"%sN\t"YELLOW_E"Nearest\t \n",msg2);
	foreach(new i : PVehicles) {
		if(IsValidPlayerVehicle(playerid, i))
		{
			gListedItems[playerid][found] = i;
			found++;
			format(msg2, sizeof(msg2), "%s"WHITE_E"V%d:\t"AQUA_E"%s\t"WHITE_E"%.1f\t%s\n", msg2, pvData[i][cID], GetVehicleModelName(pvData[i][cModel]), GetDistanceBetweenPoints(VPos[0], VPos[1], VPos[2], pvData[i][cPosX], pvData[i][cPosY], pvData[i][cPosZ]), GetStatusVehiclePlayer(i));
		}
	}
	if(found) Dialog_Show(playerid, CarLock, DIALOG_STYLE_TABLIST_HEADERS, "Vehicle Locking", msg2, "Toggle", "Close");
	return 1;
}

CMD:vradio(playerid, params[])
{
	if(isnull(params)) 
	{
		Usage(playerid, "/vradio [listen/stop/url]");
		return 1;
	}
	if(IsABike(GetPlayerVehicleID(playerid))) return Error(playerid, "Bike does't have radio.");
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return Error(playerid, "You need to be driver to use this command.");

	if (!strcmp(params, "listen", true)) 
	{
		new output[1024];
		for (new i = 0; i < 34; i ++) {
			strcat(output, sprintf("%s\n", RadioStation[i][Name]));
		}
		Dialog_Show(playerid, RadioList, DIALOG_STYLE_LIST, "Radio List", output, "Select", "Close");
	} else if (!strcmp(params, "stop", true)) 
	{
		StopVehicleRadio(GetPlayerVehicleID(playerid));
		SendCustomMessage(playerid, "RADIO", "You've been stopped vehicle radio.");
	} 
	else if (!strcmp(params, "url", true)) 
	{
		Dialog_Show(playerid, RadioLink, DIALOG_STYLE_INPUT, "Insert URL", "Masukkan link radio yang akan di dengar:", "Play", "Close");
	} else Usage(playerid, "/vradio [listen/stop/url]");
	return 1;
}

CMD:toglight(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{	
		if(!IsEngineVehicle(vehicleid))
		return SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You are not in any vehicle.");
		
		switch(GetLightStatus(vehicleid))
		{
			case false:
			{
				SwitchVehicleLight(vehicleid, true);
				SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"Light {00D900}ON.");
				pvData[vehicleid][vELM] = false;
				SetVehicleNeonLights(pvData[vehicleid][cVeh], true, pvData[vehicleid][cNeon], 0);
				pvData[vehicleid][cTogNeon] = 1;
				foreach(new vehid : PVehicles) if(pvData[vehid][cVeh] == vehicleid) {
					for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++) { 
						if(Iter_Contains(PVehicles, vehid)) {
							if(VehicleObjects[vehid][slot][vehObjectType] == OBJECT_TYPE_LIGHT) {
								new
									model       = VehicleObjects[vehid][slot][vehObjectModel],
									Float:x     = VehicleObjects[vehid][slot][vehObjectPosX],
									Float:y     = VehicleObjects[vehid][slot][vehObjectPosY],
									Float:z     = VehicleObjects[vehid][slot][vehObjectPosZ],
									Float:rx    = VehicleObjects[vehid][slot][vehObjectPosRX],
									Float:ry    = VehicleObjects[vehid][slot][vehObjectPosRY],
									Float:rz    = VehicleObjects[vehid][slot][vehObjectPosRZ],
									Float:vposx,
									Float:vposy,
									Float:vposz
								;
								if(IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
									DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);

								VehicleObjects[vehicleid][slot][vehObject] = INVALID_OBJECT_ID;
								GetVehiclePos(pvData[vehid][cVeh], vposx, vposy, vposz);

								VehicleObjects[vehid][slot][vehObject] = CreateDynamicObject(model, vposx, vposy, vposz, rx, ry, rz);

								AttachDynamicObjectToVehicle(VehicleObjects[vehid][slot][vehObject], pvData[vehid][cVeh], x, y, z, rx, ry, rz);
							}	
							if(VehicleObjects[vehid][slot][vehObjectType] == OBJECT_TYPE_NEON) {
								new
									model       = VehicleObjects[vehid][slot][vehObjectModel],
									Float:x     = VehicleObjects[vehid][slot][vehObjectPosX],
									Float:y     = VehicleObjects[vehid][slot][vehObjectPosY],
									Float:z     = VehicleObjects[vehid][slot][vehObjectPosZ],
									Float:rx    = VehicleObjects[vehid][slot][vehObjectPosRX],
									Float:ry    = VehicleObjects[vehid][slot][vehObjectPosRY],
									Float:rz    = VehicleObjects[vehid][slot][vehObjectPosRZ],
									Float:vposx,
									Float:vposy,
									Float:vposz
								;
								if(IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
									DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);

								VehicleObjects[vehicleid][slot][vehObject] = INVALID_OBJECT_ID;
								GetVehiclePos(pvData[vehid][cVeh], vposx, vposy, vposz);

								VehicleObjects[vehid][slot][vehObject] = CreateDynamicObject(model, vposx, vposy, vposz, rx, ry, rz);

								AttachDynamicObjectToVehicle(VehicleObjects[vehid][slot][vehObject], pvData[vehid][cVeh], x, y, z, rx, ry, rz);
							}	
						}
					}	
				}
			}
			case true:
			{
				SwitchVehicleLight(vehicleid, false);
				SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"Light {FF0000}OFF.");
				pvData[vehicleid][vELM] = false;
				SetVehicleNeonLights(pvData[vehicleid][cVeh], false, pvData[vehicleid][cNeon], 0);
				pvData[vehicleid][cTogNeon] = 0;
				foreach(new vehid : PVehicles) if(pvData[vehid][cVeh] == vehicleid) {
					for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++) { 
						if(Iter_Contains(PVehicles, vehid)) {
							if(VehicleObjects[vehid][slot][vehObjectType] == OBJECT_TYPE_LIGHT) {
								if(IsValidDynamicObject(VehicleObjects[vehid][slot][vehObject]))
									DestroyDynamicObject(VehicleObjects[vehid][slot][vehObject]);
								VehicleObjects[vehid][slot][vehObject] = INVALID_OBJECT_ID;
							}	
							if(VehicleObjects[vehid][slot][vehObjectType] == OBJECT_TYPE_NEON) {
								if(IsValidDynamicObject(VehicleObjects[vehid][slot][vehObject]))
									DestroyDynamicObject(VehicleObjects[vehid][slot][vehObject]);
								VehicleObjects[vehid][slot][vehObject] = INVALID_OBJECT_ID;
							}	
						}
					}	
				}
			}
		}
	}
	else return SendClientMessageEx(playerid, COLOR_ARWIN, "Anda harus mengendarai kendaraan!");
	return 1;
}

CMD:hood(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "You must exit from the vehicle.");
			
	new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);

	if(vehicleid == INVALID_VEHICLE_ID)
		return SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You not in near any vehicles.");

	switch (GetHoodStatus(vehicleid))
	{
		case false:
		{
			SwitchVehicleBonnet(vehicleid, true);
			SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"Hood {00D900}Opened.");
		}
		case true:
		{
			SwitchVehicleBonnet(vehicleid, false);
			SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"Hood {FF0000}Closed.");
		}
	}
	return 1;
}

CMD:engine(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{	
		if(!IsEngineVehicle(vehicleid))
		return SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You are not in any vehicle.");
		
		if(GetEngineStatus(vehicleid))
		{
			EngineStatus(playerid, vehicleid);
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_ARWIN, "ENGINE: "WHITE_E"Anda mencoba menghidupkan Mesin.");
			SetTimerEx("EngineStatus", 1000, false, "id", playerid, vehicleid);
		}
	}
	else return SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"Anda harus mengendarai kendaraan!");
	return 1;
}

CMD:trunk(playerid, params[])
{
	new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);

	if(vehicleid == INVALID_VEHICLE_ID)
		return SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You not in near any vehicles.");
	if(!IsABoat(vehicleid) && !IsABike(vehicleid) && !IsAPlane(vehicleid) && !IsAHelicopter(vehicleid))
	{
		Vehicle_OpenStorage(playerid, vehicleid);
		SwitchVehicleBoot(vehicleid, true);
	}
	return 1;
}

CMD:checktrunk(playerid, params[])
{
	if(pData[playerid][pFaction] == 1)
	{
		if(!pData[playerid][pOnDuty]) return Error(playerid, "You must be onduty first");
		new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);

		if(vehicleid == INVALID_VEHICLE_ID)
			return SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You not in near any vehicles.");
		if(!IsABoat(vehicleid) && !IsABike(vehicleid) && !IsAPlane(vehicleid) && !IsAHelicopter(vehicleid))
		{
			Vehicle_OpenStorageSAPD(playerid, vehicleid);
			SwitchVehicleBoot(vehicleid, true);
		}
	}
	else return Error(playerid, "You are not a police officer");
	return 1;
}

CMD:nlock(playerid, params[])
{
	foreach(new i : PVehicles) if(GetNearestVehicleToPlayer(playerid, 3.5, false) == pvData[i][cVeh]) if(pvData[i][cOwner] == pData[playerid][pID])  {
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

// CMD:sellpv(playerid, params[])
// {
// 	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1657.9524,-1394.4664,13.5469)) return Error(playerid, "You must be at the insurance office");
	
// 	new vehid;
// 	if(sscanf(params, "d", vehid)) return Usage(playerid, "/sellpv [vehid] | /v my(mypv) - for find vehid");
// 	if(vehid == INVALID_VEHICLE_ID) return Error(playerid, "Invalid id");
			
// 	foreach(new i : PVehicles)
// 	{
// 		if(vehid == pvData[i][cVeh])
// 		{
// 			if(pvData[i][cOwner] == pData[playerid][pID])
// 			{
// 				if(!IsValidVehicle(pvData[i][cVeh])) return Error(playerid, "Your vehicle is not spanwed!");
// 				if(pvData[i][cRent] != 0) return Error(playerid, "You can't sell rental vehicle!");
// 				new pay = pvData[i][cPrice] / 30;

// 				GivePlayerMoneyEx(playerid, pay);
				
// 				SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You sell your "AQUA_E"%s "WHITE_E"vehicle for "GREEN_E"$%s", GetVehicleName(vehid), FormatMoney(pay));
// 				new query[128];
// 				mysql_format(g_SQL, query, sizeof(query), "DELETE FROM vehicle WHERE id = '%d'", pvData[i][cID]);
// 				mysql_tquery(g_SQL, query);
// 				if(IsValidVehicle(pvData[i][cVeh])) DestroyVehicle(pvData[i][cVeh]);
// 				Iter_SafeRemove(PVehicles, i, i);
// 			}
// 			else return Error(playerid, "ID kendaraan ini bukan punya mu! gunakan /v my(/mypv) untuk mencari ID.");
// 		}
// 	}
// 	return 1;
// }

CMD:buyinsurance(playerid, params[])
{		
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 5 && IsPlayerInRangeOfPoint(playerid, 2.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
			new found = false, msg2[512];
			new Float:VPos[3];
			GetPlayerPos(playerid, VPos[0], VPos[1], VPos[2]);
			format(msg2, sizeof(msg2), "Model(ID)\tInsurance\tPrice\n");
			foreach(new i : PVehicles)
			{
				if(pvData[i][cOwner] == pData[playerid][pID] && pvData[i][cClaim] == 0)
				{
					new price = pvData[i][cPrice] / 4;
					gListedItems[playerid][found] = i;
					found++;
					format(msg2, sizeof(msg2), "%s{00FFFF}%s(%d)\t"YELLOW_E"%d\t"GREEN_E"$%s\n", msg2, GetVehicleModelName(pvData[i][cModel]), pvData[i][cVeh], pvData[i][cInsu], FormatMoney(price));
				}
			}
			if(found) Dialog_Show(playerid, BuyInsurance, DIALOG_STYLE_TABLIST_HEADERS, "Buy Insurance", msg2, "Buy", "Close");
		}
	}
	return 1;
}

CMD:buyplate(playerid, params[])
{		
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 1 && IsPlayerInRangeOfPoint(playerid, 2.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
			new found = false, msg2[512];
			format(msg2, sizeof(msg2), "Model(ID)\tPlate\n");
			foreach(new i : PVehicles) if(IsValidVehicle(pvData[i][cVeh])) {
				if(pvData[i][cOwner] == pData[playerid][pID])
				{
					gListedItems[playerid][found] = i;
					found++;
					format(msg2, sizeof(msg2), "%s{00FFFF}%s\t%s\n", msg2, GetVehicleModelName(pvData[i][cModel]), pvData[i][cPlate]);
				}
			}
			if(found) Dialog_Show(playerid, BuyPlate, DIALOG_STYLE_TABLIST_HEADERS, "Buy Plate", msg2, "Buy", "Close");
		}
	}
	return 1;
}

CMD:claiminsurance(playerid, params[])
{		
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 5 && IsPlayerInRangeOfPoint(playerid, 2.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
			new found = false, msg2[512];
			format(msg2, sizeof(msg2), "Model(ID)\tClaim time\n");
			foreach(new i : PVehicles)
			{
				if(pvData[i][cClaim] == 1 && pvData[i][cClaimTime] == 0)
				{
					if(pvData[i][cOwner] == pData[playerid][pID])
					{
						gListedItems[playerid][found] = i;
						found++;
						format(msg2, sizeof(msg2), "%s{00FFFF}%s(%d)\t"GREEN_E"Now\n", msg2, GetVehicleModelName(pvData[i][cModel]), pvData[i][cVeh]);
					}
				}	
			}
			if(found) Dialog_Show(playerid, ClaimInsurance, DIALOG_STYLE_TABLIST_HEADERS, "Claim Insurance", msg2, "Claim", "Close");
			else return Error(playerid, "Vehicle is not ready to bey claimed");
		}
	}	
	return 1;
}

CMD:aclaiminsurance(playerid, params[])
{		
	new otherid;
	if(sscanf(params, "u", otherid)) return Usage(playerid, "/aclaiminsurance [playerid/name]");
	new found = false, msg2[512];
	format(msg2, sizeof(msg2), "Model(ID)\tClaim time\n");
	foreach(new i : PVehicles)
	{
		if(pvData[i][cClaim] == 1)
		// if(pvData[i][cClaim] == 1 && pvData[i][cClaimTime] != 0)
		{
			if(pvData[i][cOwner] == pData[otherid][pID])
			{
				gListedItems[playerid][found] = i;
				found++;
				format(msg2, sizeof(msg2), "%s{00FFFF}%s(%d)\t"GREEN_E"%s\n", msg2, GetVehicleModelName(pvData[i][cModel]), pvData[i][cVeh], experieddate(pvData[i][cClaimTime], 3));
			}
		}	
	}
	SetPVarInt(playerid, "AdmClaimInsurance", otherid);
	if(found) Dialog_Show(playerid, AdmClaimInsurance, DIALOG_STYLE_TABLIST_HEADERS, "Claim Insurance", msg2, "Claim", "Close");
	return 1;
}

CMD:acceptvehicle(playerid, params[])
{
	new otherid = SellIDPlayerVehicle[playerid], cash = SellPriceVehicle[playerid], vehicleid = SellIDVehiclePlayer[playerid];
	if(!IsPlayerConnected(otherid)) return Error(playerid, "Tidak ada yang menjual kendaraan kepada anda");
	if(cash > GetPlayerMoney(playerid)) return Error(playerid, "Anda tidak mempunyai uang untuk membeli kendaraan dari player lain");
	new query[128];
	foreach(new vehid : PVehicles) if(pvData[vehicleid][cVeh] == pvData[vehid][cVeh]) {
		pvData[vehid][cOwner] = pData[playerid][pID];
		pvData[vehid][cCrack] = 0;
		pvData[vehid][cMaterial] = 0;
		pvData[vehid][cCgun] = 0;
		pvData[vehid][cComponent] = 0;
		pvData[vehid][cCrateComponent] = 0;
		pvData[vehid][cCrateFish] = 0;
		pvData[vehid][cCrateFish2] = 0;
		pvData[vehid][cCrateLumber] = 0;
		pvData[vehid][cCratePlant] = 0;
		pvData[vehid][cWheat] = 0;
		pvData[vehid][cCarrot] = 0;
		pvData[vehid][cPotato] = 0;
		pvData[vehid][cCorn] = 0;
		for(new j = 0; j < 10; j++)
		{
			pvData[vehid][cWeapon][j] = 0;
			pvData[vehid][cAmmo][j] = 0;
		}
		mysql_format(g_SQL, query, sizeof(query), "UPDATE vehicle SET owner='%d' WHERE id=%d", pvData[vehid][cOwner], pvData[vehid][cID]);
		mysql_tquery(g_SQL, query);
		GivePlayerMoneyEx(otherid, cash);
		GivePlayerMoneyEx(playerid, -cash);
		SendCustomMessage(playerid, "VEHICLE", "You managed to buy a "AQUA_E"%s "WHITE_E"vehicle from player "YELLOW_E"%s "WHITE_E"at a price of "GREEN_E"$%s", GetVehicleName(pvData[vehid][cVeh]), ReturnName2(otherid), FormatMoney(cash));
		SendCustomMessage(otherid, "VEHICLE", ""YELLOW_E"%s "WHITE_E"Successfully Buys Your Vehicle at "GREEN_E"$%s", ReturnName2(playerid), FormatMoney(cash));
	}
	return 1;
}

CMD:accepttransfer(playerid, params[])
{
	new otherid = TradePlayerID[playerid], vehplayerid = TradeVehicleID[playerid];
	new vehotherid = TradeVehicleID[otherid];
	if(!IsPlayerNearPlayer(playerid, otherid, 5.0))
		return Error(playerid, "You are not near that player.");
	new query[128];
	foreach(new vehid : PVehicles) if(pvData[vehplayerid][cVeh] == pvData[vehid][cVeh]) {
		pvData[vehid][cOwner] = pData[playerid][pID];
		pvData[vehid][cCrack] = 0;
		pvData[vehid][cMaterial] = 0;
		pvData[vehid][cCgun] = 0;
		pvData[vehid][cComponent] = 0;
		pvData[vehid][cCrateComponent] = 0;
		pvData[vehid][cCrateFish] = 0;
		pvData[vehid][cCrateFish2] = 0;
		pvData[vehid][cCrateLumber] = 0;
		pvData[vehid][cCratePlant] = 0;
		pvData[vehid][cWheat] = 0;
		pvData[vehid][cCarrot] = 0;
		pvData[vehid][cPotato] = 0;
		pvData[vehid][cCorn] = 0;
		for(new j = 0; j < 10; j++)
		{
			pvData[vehid][cWeapon][j] = 0;
			pvData[vehid][cAmmo][j] = 0;
		}
		mysql_format(g_SQL, query, sizeof(query), "UPDATE vehicle SET owner='%d' WHERE id=%d", pvData[vehid][cOwner], pvData[vehid][cID]);
		mysql_tquery(g_SQL, query);
	}
	foreach(new vehid : PVehicles) if(pvData[vehotherid][cVeh] == pvData[vehid][cVeh]) {
		pvData[vehid][cOwner] = pData[otherid][pID];
		pvData[vehid][cCrack] = 0;
		pvData[vehid][cMaterial] = 0;
		pvData[vehid][cCgun] = 0;
		pvData[vehid][cComponent] = 0;
		pvData[vehid][cCrateComponent] = 0;
		pvData[vehid][cCrateFish] = 0;
		pvData[vehid][cCrateFish2] = 0;
		pvData[vehid][cCrateLumber] = 0;
		pvData[vehid][cCratePlant] = 0;
		pvData[vehid][cWheat] = 0;
		pvData[vehid][cCarrot] = 0;
		pvData[vehid][cPotato] = 0;
		pvData[vehid][cCorn] = 0;
		for(new j = 0; j < 10; j++)
		{
			pvData[vehid][cWeapon][j] = 0;
			pvData[vehid][cAmmo][j] = 0;
		}
		mysql_format(g_SQL, query, sizeof(query), "UPDATE vehicle SET owner='%d' WHERE id=%d", pvData[vehid][cOwner], pvData[vehid][cID]);
		mysql_tquery(g_SQL, query);
	}
	SendCustomMessage(otherid, "VEHICLE", "Your request has been accepted by "YELLOW_E"%s"WHITE_E", and transaction was successfull.",ReturnName2(playerid));
	SendCustomMessage(playerid, "VEHICLE", "You has accepted "YELLOW_E"%s"WHITE_E" request, and transaction was successfull.",ReturnName2(otherid));
	return 1;
}

CMD:canceltransfer(playerid, params[])
{
	new otherid = TradePlayerID[playerid];
	if(otherid != INVALID_PLAYER_ID) {
		TradePlayerID[otherid] = -1;
		TradeVehicleID[otherid] = -1;
		TradePlayerID[playerid] = -1;
		TradeVehicleID[playerid] = -1;
		SendCustomMessage(otherid, "VEHICLE", "Your request has been rejected by "YELLOW_E"%s"WHITE_E"",ReturnName2(playerid));
		SendCustomMessage(playerid, "VEHICLE", "You have declined the request for "YELLOW_E"%s"WHITE_E".",ReturnName2(otherid));
	}
	return 1;
}

CMD:givepv(playerid, params[])
{
	new vehid, otherid;
	
	if(pData[playerid][pLevel] < 3)
	    return Error(playerid, "Anda harus level 3 untuk bisa melalukan akses ini");
	    
	if(sscanf(params, "ud", otherid, vehid)) return Usage(playerid, "/givepv [playerid/name] [vehid] | /v my(mypv) - for find vehid");
	
	if(vehid == INVALID_VEHICLE_ID) return Error(playerid, "Invalid id");

	if(!IsPlayerConnected(otherid) || !NearPlayer(playerid, otherid, 4.0))
        return Error(playerid, "The specified player is disconnected or not near you.");
    
	new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(otherid);
	if(count >= limit)
	{
		Error(playerid, "This player have too many vehicles, sell a vehicle first!");
		return 1;
	}
	foreach(new i : PVehicles)
	{
		if(vehid == pvData[i][cVeh])
		{
			if(pvData[i][cOwner] == pData[playerid][pID])
			{
				if(IsVIPVehicle(vehid) && !pData[otherid][pVip]) return Error(playerid, "You can't give a VIP vehicle to a player who isn't a VIP!");
				new nearid = GetNearestVehicleToPlayer(playerid, 5.0, false);
				if(vehid == nearid)
				{
					if(pvData[i][cRent] != 0) return Error(playerid, "You can't give rental vehicle!");
					SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"Anda memberikan kendaraan %s(%d) anda kepada %s.", GetVehicleName(vehid), GetVehicleModel(vehid), ReturnName(otherid));
					SendClientMessageEx(otherid, COLOR_ARWIN, "VEHICLE: "WHITE_E"%s Telah memberikan kendaraan %s(%d) kepada anda.(/mypv)", ReturnName(playerid), GetVehicleName(vehid), GetVehicleModel(vehid));
					pvData[i][cOwner] = pData[otherid][pID];
					new query[128];
					mysql_format(g_SQL, query, sizeof(query), "UPDATE vehicle SET owner='%d' WHERE id='%d'", pData[otherid][pID], pvData[i][cID]);
					mysql_tquery(g_SQL, query);
					return 1;
				}
				else return Error(playerid, "Anda harus berada di dekat kendaraan yang anda jual!");
			}
			else return Error(playerid, "ID kendaraan ini bukan punya mu! gunakan /v my(/mypv) untuk mencari ID.");
		}
	}
	return 1;
}

CMD:tow(playerid, params[]) 
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		new carid = GetPlayerVehicleID(playerid);
		if(IsATowTruck(carid))
		{
			new closestcar = GetClosestCar(playerid, carid);

			if(GetDistanceToCar(playerid, closestcar) <= 8 && !IsTrailerAttachedToVehicle(carid)) 
			{
				SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You has towed the vehicle in trailer.");
				AttachTrailerToVehicle(closestcar, carid);
				return 1;
			}
		}
		else
		{
			Error(playerid, "Anda harus mengendarai Tow truck.");
			return 1;
		}
	}
	else
	{
		Error(playerid, "Anda harus mengendarai Tow truck.");
		return 1;
	}
	return 1;
}

CMD:untow(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
		{
			SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You has untowed the vehicle trailer.");
			DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
		}
		else
		{
			Error(playerid, "Tow penderek kosong!");
		}
	}
	else
	{
		Error(playerid, "Anda harus mengendarai Tow truck.");
		return 1;
	}
	return 1;
}
