#define MAX_VEHICLE_FACTION 1000

enum factionvehicle {
    fVehicleID,
    fVehicleModel,
    Float:fVehicleHealth,
    fVehicleFuel,
    fVehicleColor1,
    fVehicleColor2,
    fVehicleFaction,
    Float:fVehiclePos[4],
    fVehicleObject,
    fVehicleOwner,
    fVehicle
}
new FactionVehicle[MAX_VEHICLE_FACTION][factionvehicle],
    Iterator:FVehicle<MAX_VEHICLE_FACTION>;

IsFactionVeh(carid)
{
	foreach(new vehid : FVehicle) {
	    if(carid == FactionVehicle[vehid][fVehicle]) return 1;
	}
	return 0;
}

CMD:spawnveh(playerid, params[])
{
    // Sapd Vehicle - unlimited spawn (kapasitas iterator sudah dinaikkan)
    if(pData[playerid][pFaction] == 1)
    {
        if(!IsPlayerInRangeOfPoint(playerid, 8.0, 1568.40, -1695.66, 5.89) && !IsPlayerInRangeOfPoint(playerid, 8.0, 1569.1587,-1641.0361,28.5788))
            return Error(playerid, "You must be at SAPD vehicle spawn point!.");

        // Cek apakah masih ada slot kosong untuk spawn
        if(Iter_Free(FVehicle) == cellmin)
            return Error(playerid, "Slot faction vehicle sudah penuh! Gunakan /despawn untuk menghapus kendaraan yang sudah ada.");

        ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SAPDVEHICLE, "LSPD:", sapvehicle, sizeof(sapvehicle));
        return 1;
    }
    else if(pData[playerid][pFaction] == 3)
    {
        if(!IsPlayerInRangeOfPoint(playerid, 8.0, 1131.5339, -1332.3248, 13.5797) && !IsPlayerInRangeOfPoint(playerid, 8.0, 1162.8176, -1313.8239, 32.2215))
            return Error(playerid, "You must be at medical officer location!.");

        ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SAMDVEHICLE, "SAMD:", samdvehicle, sizeof(samdvehicle));
        return 1;
    }
    else if(pData[playerid][pFaction] == 4)
    {
        if(!IsPlayerInRangeOfPoint(playerid, 8.0, 743.5262, -1332.2343, 13.8414) && !IsPlayerInRangeOfPoint(playerid, 8.0, 741.9764,-1371.2441,25.8835))
            return Error(playerid, "You must be at Sana officer location!.");

        ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SANAVEHICLE, "SANA:", sanavehicle, sizeof(sanavehicle));
        return 1;
    }
    else
    {
        return Error(playerid, "Anda bukan anggota faction.");
    }
}

CMD:despawn(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);
    foreach(new vehid : FVehicle)
    {
        if(vehicleid == FactionVehicle[vehid][fVehicle])
        {
            // SAPD - harus di point spawn untuk despawn
            if(pData[playerid][pFaction] == 1)
            {
                if(!IsPlayerInRangeOfPoint(playerid, 8.0, 1568.40, -1695.66, 5.89) && !IsPlayerInRangeOfPoint(playerid, 8.0, 1569.1587,-1641.0361,28.5788))
                    return Error(playerid, "You must be at SAPD vehicle spawn point to despawn!.");

                if (FactionVehicle[vehid][fVehicle] != INVALID_VEHICLE_ID) {
                    if(IsValidVehicle(FactionVehicle[vehid][fVehicle]))
                        DestroyVehicle(FactionVehicle[vehid][fVehicle]);

                    FactionVehicle[vehid][fVehicle] = INVALID_VEHICLE_ID;
                }
                new current = vehid,
                    next = Iter_Next(FVehicle, current);

                Iter_Remove(FVehicle, current);

                vehid = next;
                GameTextForPlayer(playerid, "~w~Vehicles ~r~Despawned", 3500, 3);
            }
            else if(pData[playerid][pFaction] == 3)
            {
                if(!IsPlayerInRangeOfPoint(playerid, 8.0, 1131.5339, -1332.3248, 13.5797) && !IsPlayerInRangeOfPoint(playerid, 8.0, 1162.8176, -1313.8239, 32.2215))
                    return Error(playerid, "You must be at medical officer faction!.");

                if (FactionVehicle[vehid][fVehicle] != INVALID_VEHICLE_ID) {
                    if(IsValidVehicle(FactionVehicle[vehid][fVehicle]))
                        DestroyVehicle(FactionVehicle[vehid][fVehicle]);

                    FactionVehicle[vehid][fVehicle] = INVALID_VEHICLE_ID;
                }
                new current = vehid,
                    next = Iter_Next(FVehicle, current);

                Iter_Remove(FVehicle, current);

                vehid = next;
                GameTextForPlayer(playerid, "~w~Vehicles ~r~Despawned", 3500, 3);
            }
            else if(pData[playerid][pFaction] == 4)
            {
                if(!IsPlayerInRangeOfPoint(playerid, 8.0, 743.5262, -1332.2343, 13.8414) && !IsPlayerInRangeOfPoint(playerid, 8.0, 741.9764,-1371.2441,25.8835))
                    return Error(playerid, "You must be at Sana officer faction!.");

                if (FactionVehicle[vehid][fVehicle] != INVALID_VEHICLE_ID) {
                    if(IsValidVehicle(FactionVehicle[vehid][fVehicle]))
                        DestroyVehicle(FactionVehicle[vehid][fVehicle]);

                    FactionVehicle[vehid][fVehicle] = INVALID_VEHICLE_ID;
                }
                new current = vehid,
                    next = Iter_Next(FVehicle, current);

                Iter_Remove(FVehicle, current);

                vehid = next;
                GameTextForPlayer(playerid, "~w~Vehicles ~r~Despawned", 3500, 3);
            }
        }
    }
    return 1;
}

CMD:efv(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);
    foreach(new vehid : FVehicle)
    {
        if(vehicleid == FactionVehicle[vehid][fVehicle])
        {
            // Sapd Vehicle
            if(IsPlayerInRangeOfPoint(playerid, 8.0, 1568.40, -1695.66, 5.89) || IsPlayerInRangeOfPoint(playerid, 8.0, 1569.1587,-1641.0361,28.5788)
            || IsPlayerInRangeOfPoint(playerid, 8.0, 1568.40, -1695.66, 5.89) || IsPlayerInRangeOfPoint(playerid, 8.0, 1569.1587,-1641.0361,28.5788))
            {
                if(pData[playerid][pFaction] == 1)
                {
                    Dialog_Show(playerid, DialogVFactionModif, DIALOG_STYLE_LIST, "Vehicle Menu", "Wheels Car\nNitro\nPlate", "Service", "Cancel");	
                }
            }
            else if(IsPlayerInRangeOfPoint(playerid, 8.0, 1131.5339, -1332.3248, 13.5797) || IsPlayerInRangeOfPoint(playerid, 8.0, 1162.8176, -1313.8239, 32.2215))
            {
                if(pData[playerid][pFaction] != 3)
                    return Error(playerid, "You must be at medical officer faction!.");

                Dialog_Show(playerid, DialogVFactionModif, DIALOG_STYLE_LIST, "Vehicle Menu", "Wheels Car\nNitro\nPlate", "Service", "Cancel");	
            }
            else if(IsPlayerInRangeOfPoint(playerid, 8.0, 743.5262, -1332.2343, 13.8414) || IsPlayerInRangeOfPoint(playerid, 8.0, 741.9764,-1371.2441,25.8835))
            {
                if(pData[playerid][pFaction] != 4)
                    return Error(playerid, "You must be at Sana officer faction!.");
                Dialog_Show(playerid, DialogVFactionModif, DIALOG_STYLE_LIST, "Vehicle Menu", "Wheels Car\nNitro\nPlate", "Service", "Cancel");	
            }
        }
    }
    return 1;
}

Dialog:SpawnVehiclePD(playerid, response, listitem, inputtext[])
{
	if (response)
	{
        new pos[2];
        if(!sscanf(inputtext, "dd",pos[0],pos[1])) 
        {
            new id = cellmin;
            if((id = Iter_Free(FVehicle)) != cellmin)
            {
                Iter_Add(FVehicle, id);
                SetPVarInt(playerid, "Color1", pos[0]);
                SetPVarInt(playerid, "Color2", pos[1]);
                OnFactionVehicleRespawn(id, playerid);
            }
        }
    }
    return 1;
}

OnFactionVehicleRespawn(id, playerid)
{
    if (IsValidVehicle(FactionVehicle[id][fVehicle]))
		DestroyVehicle(FactionVehicle[id][fVehicle]), FactionVehicle[id][fVehicle] = INVALID_VEHICLE_ID;
    new Float:x, Float:y, Float:z, Float:A, strings[212];
    new modelid = GetPVarInt(playerid, "FactionModelVehicle");
    new pos1 = GetPVarInt(playerid, "Color1");
    new pos2 = GetPVarInt(playerid, "Color2");
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, A);
    FactionVehicle[id][fVehicle] = CreateVehicle(modelid, x, y, z, A, pos1, pos2, VEHICLE_RESPAWN, 1);
    if(IsValidVehicle(FactionVehicle[id][fVehicle]))
	{
        PutPlayerInVehicle(playerid, FactionVehicle[id][fVehicle], 0);
        DeletePVar(playerid, "FactionModelVehicle");
        DeletePVar(playerid, "Color1");
        DeletePVar(playerid, "Color2");
        format(strings, sizeof(strings), ""GREEN_E"%s-%d", pData[playerid][pFactionRankName], id);
        SetVehicleNumberPlate(FactionVehicle[id][fVehicle], strings);
        FactionVehicle[id][fVehicleFaction] = pData[playerid][pFaction];
        FactionVehicle[id][fVehicleOwner] = pData[playerid][pID];
        if(GetVehicleModel(FactionVehicle[id][fVehicle]) == 426 && pData[playerid][pFaction] == 3)
        {
            FactionVehicle[id][fVehicleObject] = CreateDynamicObject(11702,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            AttachDynamicObjectToVehicle(FactionVehicle[id][fVehicleObject], FactionVehicle[id][fVehicle], 0.000, -0.480, 0.860, 0.000, 0.000, 0.000);
        }
        SendCustomMessage(playerid, "VEHICLE", "You have succefully spawned Vehicles '"YELLOW_E"/despawn"WHITE_E"' to despawn vehicles");
    }
    return 1;
}

CMD:respawnsapd(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] < 3)
			return PermissionError(playerid);

	foreach(new vehid : FVehicle)
    {
        if (IsValidVehicle(FactionVehicle[vehid][fVehicle]))
        {
            if(FactionVehicle[vehid][fVehicleFaction] == 1)
            {
                foreach(new i : Player)
                {
                    if(GetPlayerState(i) != PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) != vehid)
                    {
                        DestroyVehicle(FactionVehicle[vehid][fVehicle]), FactionVehicle[vehid][fVehicle] = INVALID_VEHICLE_ID;
                        DestroyDynamicObject(FactionVehicle[vehid][fVehicleObject]);
                    }
                }
            }
        }
    }
	SendStaffMessage(COLOR_RED, "AdmCmd: Admin "YELLOW_E"%s "WHITE_E"has respawned vehicle sapd.", pData[playerid][pAdminname]);
	return 1;
}

CMD:resetvehiclesapd(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	new count = 0;
	foreach(new vehid : FVehicle)
    {
        if(FactionVehicle[vehid][fVehicleFaction] == 1)
        {
            // Cek apakah ada player di dalam mobil
            new hasDriver = 0;
            foreach(new i : Player)
            {
                if(GetPlayerVehicleID(i) == FactionVehicle[vehid][fVehicle] && GetPlayerState(i) == PLAYER_STATE_DRIVER)
                {
                    hasDriver = 1;
                    break;
                }
            }

            // Hanya hapus jika tidak ada driver
            if(!hasDriver)
            {
                if(IsValidVehicle(FactionVehicle[vehid][fVehicle]))
                {
                    DestroyVehicle(FactionVehicle[vehid][fVehicle]);
                    count++;
                }
                if(IsValidDynamicObject(FactionVehicle[vehid][fVehicleObject]))
                {
                    DestroyDynamicObject(FactionVehicle[vehid][fVehicleObject]);
                }
                FactionVehicle[vehid][fVehicle] = INVALID_VEHICLE_ID;
                FactionVehicle[vehid][fVehicleObject] = INVALID_STREAMER_ID;
                Iter_Remove(FVehicle, vehid);
            }
        }
    }
	SendStaffMessage(COLOR_RED, "AdmCmd: Admin "YELLOW_E"%s "WHITE_E"has cleaned %d unused SAPD vehicles.", pData[playerid][pAdminname], count);
	Servers(playerid, "VEHICLE: "WHITE_E"Berhasil membersihkan "YELLOW_E"%d "WHITE_E"kendaraan SAPD yang tidak terpakai.", count);
	return 1;
}

CMD:respawnsamd(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] < 3)
			return PermissionError(playerid);

	foreach(new vehid : FVehicle)
    {
        if (IsValidVehicle(FactionVehicle[vehid][fVehicle]))
        {
            if(FactionVehicle[vehid][fVehicleFaction] == 3)
            {
                foreach(new i : Player)
                {
                    if(GetPlayerState(i) != PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) != vehid)
                    {
                        DestroyVehicle(FactionVehicle[vehid][fVehicle]), FactionVehicle[vehid][fVehicle] = INVALID_VEHICLE_ID;
                        DestroyDynamicObject(FactionVehicle[vehid][fVehicleObject]);
                    }
                }
            }
        }
    }
	SendStaffMessage(COLOR_RED, "AdmCmd: Admin "YELLOW_E"%s "WHITE_E"has respawned vehicle samd.", pData[playerid][pAdminname]);
	return 1;
}

CMD:respawnsana(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] < 3)
			return PermissionError(playerid);

	foreach(new vehid : FVehicle)
    {
        if (IsValidVehicle(FactionVehicle[vehid][fVehicle]))
        {
            if(FactionVehicle[vehid][fVehicleFaction] == 4)
            {
                foreach(new i : Player)
                {
                    if(GetPlayerState(i) != PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) != vehid)
                    {
                        DestroyVehicle(FactionVehicle[vehid][fVehicle]), FactionVehicle[vehid][fVehicle] = INVALID_VEHICLE_ID;
                        DestroyDynamicObject(FactionVehicle[vehid][fVehicleObject]);
                    }
                }
            }
        }
    }
	SendStaffMessage(COLOR_RED, "AdmCmd: Admin "YELLOW_E"%s "WHITE_E"has respawned vehicle sana.", pData[playerid][pAdminname]);
	return 1;
}

IsSAPDCar(carid)
{
	for(new v = 0; v < MAX_VEHICLE_FACTION; v++) {
	    if(carid == FactionVehicle[v][fVehicle]) return 1;
	}
	return 0;
}

IsSAPDCar(carid, playerid)
{
	foreach(new vehicleid : VehicleData) {
	    if(VehicleData[vehicleid][Vehicle] == carid && VehicleData[vehicleid][Faction] == pData[playerid][pFaction]) return 1;
	}
	return 0;
}

function OnLightFlash(vehicleid)
{
    new panels, doors, lights, tires;
    GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

    switch(Flash[vehicleid])
    {
        case 0: 
        {
            UpdateVehicleDamageStatus(vehicleid, panels, doors, 2, tires);
        }
        case 1: 
        {
            UpdateVehicleDamageStatus(vehicleid, panels, doors, 5, tires);
        }
        case 2: 
        {
            UpdateVehicleDamageStatus(vehicleid, panels, doors, 2, tires);
        }
        case 3: 
        {
            UpdateVehicleDamageStatus(vehicleid, panels, doors, 4, tires);
        }
        case 4: 
        {
            UpdateVehicleDamageStatus(vehicleid, panels, doors, 5, tires);
        }
        case 5: 
        {
            UpdateVehicleDamageStatus(vehicleid, panels, doors, 4, tires);
        }
    }
    if (Flash[vehicleid] >= 5) Flash[vehicleid] = 0;
    else Flash[vehicleid] ++;
    return 1;
}


//1010
Dialog:DialogVFactionModif(playerid, response, listitem, inputtext[])
{
	if (response)
	{
        switch(listitem)
        {
            case 0:
            {
                Dialog_Show(playerid, DialogVFactionWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar", "Confirm", "back");
            }
            case 1:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1010);
                        }
                    }
                }
            }
            case 2:
            {
                Dialog_Show(playerid, DialogVFactionPlate, DIALOG_STYLE_INPUT, "Plate:", "Masukan Nama plate yang mau anda gunakan", "Confirm", "back");
            }
        }
    }
    return 1;
}

Dialog:DialogVFactionPlate(playerid, response, listitem, inputtext[])
{
	if (response)
	{
        new vehicleid = GetPlayerVehicleID(playerid);
        if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            foreach(new vehid : FVehicle)
            {
                if(vehicleid == FactionVehicle[vehid][fVehicle])
                {
                    new plate[62];
                    format(plate, sizeof(plate), ""GREEN_E"%s", inputtext);
                    SetVehicleNumberPlate(FactionVehicle[vehid][fVehicle], inputtext);
                    SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You've turned your vehicle's plate into a {00FFFF}%s", inputtext);
                }
            }
        }
    }
    return 1;
}

Dialog:DialogVFactionWheels(playerid, response, listitem, inputtext[])
{
	if (response)
	{
        switch(listitem)
        {
            case 0:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1025);
                        }
                    }
                }
            }
            case 1:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1074);
                        }
                    }
                }
            }
            case 2:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1076);
                        }
                    }
                }
            }
            case 3:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1078);
                        }
                    }
                }
            }
            case 4:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1081);
                        }
                    }
                }
            }
            case 5:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1082);
                        }
                    }
                }
            }
            case 6:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1085);
                        }
                    }
                }
            }
            case 7:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1096);
                        }
                    }
                }
            }
            case 8:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1097);
                        }
                    }
                }
            }
            case 9:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1098);
                        }
                    }
                }
            }
            case 10:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1084);
                        }
                    }
                }
            }
            case 11:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1073);
                        }
                    }
                }
            }
            case 12:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1075);
                        }
                    }
                }
            }
            case 13:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1077);
                        }
                    }
                }
            }
            case 14:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1079);
                        }
                    }
                }
            }
            case 15:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1080);
                        }
                    }
                }
            }
            case 16:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    foreach(new vehid : FVehicle)
                    {
                        if(vehicleid == FactionVehicle[vehid][fVehicle])
                        {
                            AddVehicleComponent(FactionVehicle[vehid][fVehicle], 1083);
                        }
                    }
                }
            }
        }
    }
    return 1;
}
