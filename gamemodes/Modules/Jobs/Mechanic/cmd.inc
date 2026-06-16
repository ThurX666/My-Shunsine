
CMD:acceptmecha(playerid, params[])
{
	static otherid, Float:x, Float:y, Float:z, id = -1;
    if(sscanf(params, "u", otherid))
        return Usage(playerid, "/acceptmecha [playerid/PartOfName]");
	if(pData[playerid][pJob] == 2 || pData[playerid][pJob2] == 2)
	{
		if(pData[otherid][pMechaCall] > 0)
		{
    		if((id = House_Inside(playerid)) != -1)
		    {
		        x = hData[id][hExtposX];
		        y = hData[id][hExtposY];
		        z = hData[id][hExtposZ];
		    }
		    else if((id = Business_Inside(playerid)) != -1)
		    {
		        x = bData[id][bExtposX];
		        y = bData[id][bExtposY];
		        z = bData[id][bExtposZ];
		    }
		   	else if((id = Entrance_Inside(playerid)) != -1)
			{
			   	x = dData[id][dExtposX];
			    y = dData[id][dExtposY];
			    z = dData[id][dExtposZ];
		    }
		    else GetPlayerPos(playerid, x, y, z);
			GetPlayerPos(otherid, x, y, z);
			SetPlayerCheckpoint(playerid, x, y, z, 5.0);
			SendClientMessageEx(playerid, COLOR_ARWIN, "SERVICE: "WHITE_E"You've accepted the mechanic request from {00FFFF}%s "YELLOW_E"%d", pData[otherid][pName], pData[otherid][pPhone]);
			SendClientMessageEx(otherid, COLOR_ARWIN, "SERVICE: {00FFFF}%s "YELLOW_E"(%d) "WHITE_E"has accepted your mechanic call. Please wait patiently until they arrive.", pData[playerid][pName], pData[playerid][pPhone]);
			SendClientMessageEx(playerid, COLOR_ARWIN, "SERVICE: Notes from client: "YELLOW_E"%s", pData[otherid][pServiceText]);
			SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: Navigation set to client's current location");
			pData[otherid][pMechaCall] = -1;
			format(pData[otherid][pServiceText], 128, "");
		}
		else
		{
			Error(playerid, "That Player does not require any taxi service");
		}
	}	
	return 1;
}

CMD:vm(playerid, params[])
{
	if(pData[playerid][pJob] == 2 || pData[playerid][pJob2] == 2)
	{
		if(IsPlayerAtMechanicPoint(playerid)){
			if(pData[playerid][pMechDuty] == 1) {
				if(pData[playerid][pMechVeh] == INVALID_VEHICLE_ID)
				{
					new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);
					if(!GetHoodStatus(vehicleid) && !IsABike(vehicleid)) return Error(playerid,"Please open the vehicle Hood before checking services");
					if(vehicleid == INVALID_VEHICLE_ID) return Error(playerid, "Anda tidak berada di dekat kendaraan mana pun.");
					if(pData[playerid][pActivityTime] > 5) return Error(playerid, "Anda sudah memeriksa kendaraan!");
					
					// agar menu Remove/Install Modification tampil, pastikan pMechVeh terisi
					pData[playerid][pMechVeh] = vehicleid;

					Mechanic[playerid] = 0;
					
					PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Examining Vehicle");
					for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
					SendVehicleOwnedMessage(vehicleid, sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started examining your {00FFFF}%s", ReturnName2(playerid), GetVehicleName(vehicleid)));	
					return 1;
				}
				if(GetNearestVehicleToPlayer(playerid, 3.5, false) == pData[playerid][pMechVeh])
				{
					new Dstring[800], Float:health, engine;
					new panels, doors, light, tires, body;
					GetVehicleHealth(pData[playerid][pMechVeh], health);
					if(health > 1000.0) health = 1000.0;
					if(health > 0.0) health *= -1;
					engine = floatround(health, floatround_round) / 10 + 100;
					
					GetVehicleDamageStatus(pData[playerid][pMechVeh], panels, doors, light, tires);
					new cpanels = panels / 1000000;
					new lights = light / 2;
					new pintu;
					if(doors != 0) pintu = 5;
					if(doors == 0) pintu = 0;
					body = cpanels + lights + pintu;
					format(Dstring, sizeof(Dstring), "Action\tComponent Cost\n\
					Repair Engine\t%d\n", engine);
					format(Dstring, sizeof(Dstring), "%sReplace Tires\t50\n", Dstring);
					format(Dstring, sizeof(Dstring), "%sRepair Body\t%d\n", Dstring, body);
					format(Dstring, sizeof(Dstring), "%sRespray Color\t60\n", Dstring);
					format(Dstring, sizeof(Dstring), "%sVehicle Upgrade\n", Dstring);
					Dialog_Show(playerid, DialogService, DIALOG_STYLE_TABLIST_HEADERS, "Vehicle Menu", Dstring, "Service", "Cancel");	
				}
				else {
					new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);
					if(!GetHoodStatus(vehicleid) && !IsABike(vehicleid)) return Error(playerid,"Please open the vehicle Hood before checking services");
					if(vehicleid == INVALID_VEHICLE_ID) return Error(playerid, "Anda tidak berada di dekat kendaraan mana pun.");
					if(pData[playerid][pActivityTime] > 5) return Error(playerid, "Anda sudah memeriksa kendaraan!");

					// agar menu Remove/Install Modification tampil, pastikan pMechVeh terisi
					pData[playerid][pMechVeh] = vehicleid;

					Mechanic[playerid] = 0;
					PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Examining Vehicle");
					for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
					SendVehicleOwnedMessage(vehicleid, sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started examining your {00FFFF}%s", ReturnName2(playerid), GetVehicleName(vehicleid)));	
				}
				return 1;
			}
			else return Error(playerid, "Anda harus on duty mechanic");
		}
		new wsid = GetPlayerNearbyWorkshop(playerid);
		if(wsid != -1)
		{
			if(IsPlayerWorkshopWorker(playerid, wsid))
			{
				if(pData[playerid][pMechVeh] == INVALID_VEHICLE_ID)
				{
					new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);
					if(!GetHoodStatus(vehicleid) && !IsABike(vehicleid)) return Error(playerid,"Please open the vehicle Hood before checking services");
					if(vehicleid == INVALID_VEHICLE_ID) return Error(playerid, "Anda tidak berada di dekat kendaraan mana pun.");
					if(pData[playerid][pActivityTime] > 5) return Error(playerid, "Anda sudah memeriksa kendaraan!");

					// agar menu Remove/Install Modification tampil, pastikan pMechVeh terisi
					pData[playerid][pMechVeh] = vehicleid;

					Mechanic[playerid] = 0;
					PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Examining Vehicle");
					for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
					SendVehicleOwnedMessage(vehicleid, sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started examining your {00FFFF}%s", ReturnName2(playerid), GetVehicleName(vehicleid)));	
					return 1;
				}
				if(GetNearestVehicleToPlayer(playerid, 3.5, false) == pData[playerid][pMechVeh])
				{
					new Dstring[800], Float:health, engine;
					new panels, doors, light, tires, body;
					GetVehicleHealth(pData[playerid][pMechVeh], health);
					if(health > 1000.0) health = 1000.0;
					if(health > 0.0) health *= -1;
					engine = floatround(health, floatround_round) / 10 + 100;
					
					GetVehicleDamageStatus(pData[playerid][pMechVeh], panels, doors, light, tires);
					new cpanels = panels / 1000000;
					new lights = light / 2;
					new pintu;
					if(doors != 0) pintu = 5;
					if(doors == 0) pintu = 0;
					body = cpanels + lights + pintu;
					format(Dstring, sizeof(Dstring), "Action\tComponent Cost\n\
					Repair Engine\t%d\n", engine);
					format(Dstring, sizeof(Dstring), "%sReplace Tires\t50\n", Dstring);
					format(Dstring, sizeof(Dstring), "%sRepair Body\t%d\n", Dstring, body);
					format(Dstring, sizeof(Dstring), "%sRespray Color\t60\n", Dstring);
					format(Dstring, sizeof(Dstring), "%sVehicle Upgrade\n", Dstring);
					format(Dstring, sizeof(Dstring), "%sRemove Modification\n", Dstring);
					format(Dstring, sizeof(Dstring), "%sInstall Modification\n", Dstring);

					Dialog_Show(playerid, DialogService, DIALOG_STYLE_TABLIST_HEADERS, "Vehicle Menu", Dstring, "Service", "Cancel");	
				}
				else {
					new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);
					if(!GetHoodStatus(vehicleid) && !IsABike(vehicleid)) return Error(playerid,"Please open the vehicle Hood before checking services");
					if(vehicleid == INVALID_VEHICLE_ID) return Error(playerid, "Anda tidak berada di dekat kendaraan mana pun.");
					if(pData[playerid][pActivityTime] > 5) return Error(playerid, "Anda sudah memeriksa kendaraan!");
					pData[playerid][pMechVeh] = vehicleid;
					Mechanic[playerid] = 0;
					PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Examining Vehicle");
					for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
					SendVehicleOwnedMessage(vehicleid, sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started examining your {00FFFF}%s", ReturnName2(playerid), GetVehicleName(vehicleid)));	
				}
				return 1;
			}
			else return Error(playerid, "You are not an employee of this workshop!");
		}
		return Error(playerid, "You have to be near a workshop or mechanic point to use this command!");
	}
	else return Error(playerid, "You are not a mechanic!");	
}

CMD:unloadcomponent(playerid, params[])
{
    new Float: x, Float: y, Float: z;
    new vehicleid = GetPVarInt(playerid, "LastVehicleID");
    GetVehicleBoot(GetPVarInt(playerid, "LastVehicleID"), x, y, z);
    if(GetPlayerDistanceFromPoint(playerid, x, y, z) > 3.0) return Error(playerid, "Your last vehicle is too far away.");  
    if(!IsAMechanic(vehicleid)) return Error(playerid, "You have to use a pickup type car");
   
	foreach(new pv : PVehicles)
	{
		if(vehicleid == pvData[pv][cVeh] && pvData[pv][cComponent] > 0)
		{
			new amount = 250 - pData[playerid][pComponent];
			if(pvData[pv][cComponent] < amount) {
				pData[playerid][pComponent] += pvData[pv][cComponent];
				pvData[pv][cComponent] = 0;
			}
			else {
				pvData[pv][cComponent] -= amount;
				pData[playerid][pComponent] += amount;
			}
			SendClientMessageEx(playerid, COLOR_ARWIN, "COMPONENT: {FFFFFF}You have taken "YELLOW_E"%d units "GREEN_E"Component "WHITE_E"from inside the pickup truck, total components: "YELLOW_E"%d units", amount, pvData[pv][cComponent]);
			if(pvData[pv][cComponent] == 0)
			{
				if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][0])) DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][0]);
			}
		}
	}
    return 1;
}

CMD:loadcomponent(playerid, params[])
{
	new ammount;
	if(sscanf(params, "d", ammount)) return Usage(playerid, "/loadcomponent [ammount]");
	
    new Float: x, Float: y, Float: z;
    new vehicleid = GetPVarInt(playerid, "LastVehicleID");
    GetVehicleBoot(GetPVarInt(playerid, "LastVehicleID"), x, y, z);
    if(GetPlayerDistanceFromPoint(playerid, x, y, z) > 3.0) return Error(playerid, "Your last vehicle is too far away.");  
    if(Vehicle_ComponentTotal(vehicleid) >= 1000) return Error(playerid, "You can no longer load component onto this vehicle.");    
    if(VehicleWorkshop_ComponentTotal(vehicleid) >= 1000) return Error(playerid, "You can no longer load component onto this vehicle.");    
    if(!IsAMechanic(vehicleid)) return Error(playerid, "You have to use a pickup type car");
    
	if(ammount < 1 || ammount > pData[playerid][pComponent]) return Error(playerid, "You don't have a component");
	foreach(new pv : PVehicles)
	{
		if(vehicleid == pvData[pv][cVeh])
		{
			pvData[pv][cComponent] += ammount;
			pData[playerid][pComponent] -= ammount;
			SendClientMessageEx(playerid, COLOR_ARWIN, "COMPONENT: {FFFFFF}You've loaded "YELLOW_E"%d "GREEN_E"Component "WHITE_E"into the pickup truck, amount stored: "YELLOW_E"%d", ammount, pvData[pv][cComponent]);
			if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][0])) DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][0]);
			if(GetVehicleModel(pvData[pv][cVeh]) == 422)
			{
				ObjectVehicle[pvData[pv][cVeh]][0] = CreateDynamicObject(964,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][0], pvData[pv][cVeh], 0.000, -1.370, -0.320, 0.000, 0.000, 0.000);
			}
			else if(GetVehicleModel(pvData[pv][cVeh]) == 543)
			{
				ObjectVehicle[pvData[pv][cVeh]][0] = CreateDynamicObject(964,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][0], pvData[pv][cVeh], 0.000, -1.521, -0.250, 0.000, 0.000, 0.000);
			}	
			else if(GetVehicleModel(pvData[pv][cVeh]) == 525)
			{
				ObjectVehicle[pvData[pv][cVeh]][0] = CreateDynamicObject(964,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][0], pvData[pv][cVeh], 0.000, -1.000, 0.190, 0.000, 0.000, 0.000);
			}
		}
	}
	foreach(new vehicle : VehicleData) {
		if(VehicleData[vehicle][Vehicle] == vehicleid)
		{
			VehicleData[vehicle][Storage][1] += ammount;
			pData[playerid][pComponent] -= ammount;
			SendClientMessageEx(playerid, COLOR_ARWIN, "COMPONENT: {FFFFFF}You've loaded "YELLOW_E"%d "GREEN_E"Component "WHITE_E"into the pickup truck, amount stored: "YELLOW_E"%d", ammount, VehicleData[vehicle][Storage][1]);
			if(!IsValidDynamicObject(ObjectVehicle[VehicleData[vehicle][Vehicle]][0]))
			{
				if(GetVehicleModel(VehicleData[vehicle][Vehicle]) == 525)
				{
					ObjectVehicle[VehicleData[vehicle][Vehicle]][0] = CreateDynamicObject(964,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
					AttachDynamicObjectToVehicle(ObjectVehicle[VehicleData[vehicle][Vehicle]][0], VehicleData[vehicle][Vehicle], 0.000, -1.000, 0.190, 0.000, 0.000, 0.000);
				}
			}
		}
	}
    return 1;
}

CMD:buytowtruck(playerid, params[])
{
	if(!IsPlayerAtMechanicPoint(playerid) && !IsPlayerInRangeOfPoint(playerid, 5.0, 1809.17, -2064.89, 13.55)) return Error(playerid, "You have to be at the mechanic point");
	if(pData[playerid][pJob] == 2 || pData[playerid][pJob2] == 2)
	{
		new cost = GetVehicleCost(525);
		if(GetPlayerMoney(playerid) < cost) return Error(playerid, "Your money is not enough to buy a vehicle");
		new count = 0, limit = LimitSlotPlayerVehicle(playerid);
		foreach(new ii : PVehicles)
		{
			if(pvData[ii][cOwner] == pData[playerid][pID])
				count++;
		}
		if(count >= limit)
		{
			Error(playerid, "Slot kendaraan anda sudah penuh, silahkan jual beberapa kendaraan anda terlebih dahulu!");
			return 1;
		}
		Server_Save();
		GivePlayerMoneyEx(playerid, -cost);
		new cQuery[1024];
		new Float:x,Float:y,Float:z, Float:a;
		new model, color1, color2;
		color1 = 0;
		color2 = 0;
		model = 525;
		x = 2320.6848;
		y = -2314.9629;
		z = 13.1147;
		a = 138.0695;
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
		mysql_tquery(g_SQL, cQuery, "OnVehBuyPV", "ddddddffff", playerid, pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
	}
	else return Error(playerid, "You must be a mechanic to buy a tow truck.");
	return 1;
}
