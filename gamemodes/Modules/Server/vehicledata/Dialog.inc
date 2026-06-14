
Dialog:VehicleStaticSpawn(playerid, response, listitem, inputtext[]) {
    if(response) {
		if(!Iter_Contains(VehicleData, gListedItems[playerid][listitem])) return Error(playerid, "The vehicle you specified ID of doesn't exist.");
		foreach(new vehid : VehicleData) {
			if(vehid == gListedItems[playerid][listitem]) {
				if(IsValidVehicle(VehicleData[vehid][Vehicle])) return Error(playerid, "Vehicle spawned by "RED_E"%s", VehicleData[vehid][VehicleOwner]);
				else if(!IsValidVehicle(VehicleData[vehid][Vehicle])) {
					format(VehicleData[vehid][VehicleOwner], 52, "%s", pData[playerid][pName]);
					VehicleRespawn(vehid);
				}
			}
		}
    }
	return 1;
}

Dialog:VehicleStaticEdit(playerid, response, listitem, inputtext[]) {
    if(response) {
		switch(listitem) {
			case 0: {
				Dialog_Show(playerid, VehStaticOwner, DIALOG_STYLE_LIST, "Set Vehicle Static Owner", "Faction\nBisnis\nWorkshop", "Select", "Close");
			}
			case 1: {
				Dialog_Show(playerid, VehStaticRespray, DIALOG_STYLE_INPUT, "Set Vehicle Static Respray", "Input Color: contoh 1 1\n"RED_E"NOTE: "YELLOW_E"Tidak bisa lebih dari 255 atau kurang dari 0", "Respray", "Close");
			}
			case 2: {
				Dialog_Show(playerid, VehStaticPlate, DIALOG_STYLE_INPUT, "Set Vehicle Static Plate", "Masukan text yang ingin anda jadikan plate", "Set", "Close");
			}
			case 3: {
				Dialog_Show(playerid, VehStaticSpawn, DIALOG_STYLE_LIST, "Set Vehicle Static Spawn Type", "Always\nOn-Demand", "Set", "Close");
			}
			case 4: {
				foreach(new vehid : VehicleData) if(VehicleData[vehid][Vehicle] == GetPlayerVehicleID(playerid)) {
					GetVehiclePos(GetPlayerVehicleID(playerid), VehicleData[vehid][Pos][0], VehicleData[vehid][Pos][1], VehicleData[vehid][Pos][2]);
					GetVehicleZAngle(GetPlayerVehicleID(playerid), VehicleData[vehid][Pos][3]);
					SaveVehicleData(vehid);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					return callcmd::vehicle(playerid, "edit");
				}
			}
		}
    }
	return 1;
}

Dialog:VehStaticOwner(playerid, response, listitem, inputtext[]) 
{
    if(!response) SetCameraBehindPlayer(playerid);
    if(response) {
		switch(listitem) {
			case 0: {
				Dialog_Show(playerid, VehStaticFact, DIALOG_STYLE_LIST, "Set Vehicle Static Owner", "San Andreas Police\nSan Andreas Medic\nSan Andreas Network", "Set", "Close");
			}
			case 1: {
				Dialog_Show(playerid, VehStaticBiz, DIALOG_STYLE_INPUT, "Set Vehicle Static Owner", "Masukan ID Bisnis\n input bellow:", "Set", "Close");
			}
			case 2: {
				Dialog_Show(playerid, VehStaticWorkshop, DIALOG_STYLE_INPUT, "Set Vehicle Static Owner", "Masukan ID Workshop\n input bellow:", "Set", "Close");
			}
		}
    }
    return 1;
}

Dialog:VehStaticWorkshop(playerid, response, listitem, inputtext[]) 
{
    if(!response) SetCameraBehindPlayer(playerid);
    if(response) {
        foreach(new vehid : VehicleData) if(VehicleData[vehid][Vehicle] == GetPlayerVehicleID(playerid)) {
            VehicleData[vehid][Workshop] = strval(inputtext);
			SendCustomMessage(playerid, "VEHSTATIC", "Anda telah menset kendaraan static ke property %s", ReplaceString(bData[strval(inputtext)][bName]));
			SaveVehicleData(vehid);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			return callcmd::vehicle(playerid, "edit");
        }
    }
    return 1;
}

Dialog:VehStaticBiz(playerid, response, listitem, inputtext[]) 
{
    if(!response) SetCameraBehindPlayer(playerid);
    if(response) {
        foreach(new vehid : VehicleData) if(VehicleData[vehid][Vehicle] == GetPlayerVehicleID(playerid)) {
            VehicleData[vehid][Bisnis] = strval(inputtext);
			SendCustomMessage(playerid, "VEHSTATIC", "Anda telah menset kendaraan static ke property %s", ReplaceString(bData[strval(inputtext)][bName]));
			SaveVehicleData(vehid);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
			return callcmd::vehicle(playerid, "edit");
        }
    }
    return 1;
}

Dialog:VehStaticFact(playerid, response, listitem, inputtext[]) 
{
    if(!response) SetCameraBehindPlayer(playerid);
    if(response) {
		switch(listitem) {
			case 0: {
				foreach(new vehid : VehicleData) if(VehicleData[vehid][Vehicle] == GetPlayerVehicleID(playerid)) {
					VehicleData[vehid][Faction] = 1;
					SaveVehicleData(vehid);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					return callcmd::vehicle(playerid, "edit");
				}
			}
			case 1: {
				foreach(new vehid : VehicleData) if(VehicleData[vehid][Vehicle] == GetPlayerVehicleID(playerid)) {
					VehicleData[vehid][Faction] = 3;
					SaveVehicleData(vehid);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					return callcmd::vehicle(playerid, "edit");
				}
			}
			case 2: {
				foreach(new vehid : VehicleData) if(VehicleData[vehid][Vehicle] == GetPlayerVehicleID(playerid)) {
					VehicleData[vehid][Faction] = 4;
					SaveVehicleData(vehid);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					return callcmd::vehicle(playerid, "edit");
				}
			}
		}
    }
    return 1;
}

Dialog:VehStaticRespray(playerid, response, listitem, inputtext[]) 
{
    if(!response) SetCameraBehindPlayer(playerid);
    if(response) {
		new pos[2];
        if(!sscanf(inputtext, "dd",pos[0],pos[1])) 
        {
			foreach(new vehid : VehicleData) if(VehicleData[vehid][Vehicle] == GetPlayerVehicleID(playerid)) {
				ChangeVehicleColor(VehicleData[vehid][Vehicle],pos[0],pos[1]);
				VehicleData[vehid][Color][0] = pos[0];
				VehicleData[vehid][Color][1] = pos[1];
				SaveVehicleData(vehid);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				return callcmd::vehicle(playerid, "edit");
			}
		}
    }
    return 1;
}

Dialog:VehStaticSpawn(playerid, response, listitem, inputtext[]) 
{
    if(!response) SetCameraBehindPlayer(playerid);
    if(response) {
		switch(listitem) {
			case 0: {
				foreach(new vehid : VehicleData) if(VehicleData[vehid][Vehicle] == GetPlayerVehicleID(playerid)) {
					VehicleData[vehid][SpawnType] = 0;
					SaveVehicleData(vehid);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				}
			}
			case 1: {
				foreach(new vehid : VehicleData) if(VehicleData[vehid][Vehicle] == GetPlayerVehicleID(playerid)) {
					VehicleData[vehid][SpawnType] = 1;
					SaveVehicleData(vehid);
					DestroyVehicle(VehicleData[vehid][Vehicle]);
					VehicleData[vehid][Vehicle] = INVALID_VEHICLE_ID;
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				}
			}
		}
    }
    return 1;
}

Dialog:VehStaticPlate(playerid, response, listitem, inputtext[]) 
{
    if(!response) SetCameraBehindPlayer(playerid);
    if(response) {
        foreach(new vehid : VehicleData) if(VehicleData[vehid][Vehicle] == GetPlayerVehicleID(playerid)) {
            format(VehicleData[vehid][Plate], 32, "%s", inputtext);
            new plate[62];
            format(plate, sizeof(plate), ""BLUE_E"%s", VehicleData[vehid][Plate]);
            SetVehicleNumberPlate(VehicleData[vehid][Vehicle], plate);
            SendClientMessageEx(playerid, COLOR_ARWIN, "MOD: "WHITE_E"You've turned your vehicle's plate into a {00FFFF}%s", inputtext);
            SaveVehicleData(vehid);
			PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
        }
    }
    return 1;
}

Dialog:RestockVehicleBisnis(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        new bid = pData[playerid][pInBiz], idiot = floatround(strval(inputtext));
		if(bData[bid][bProd] < 0) return Error(playerid, "Stock product di bisnis anda 0");
		foreach(new vehicleid : VehicleData) if(VehicleData[vehicleid][Bisnis] == bid) {
			if(idiot+VehicleData[vehicleid][Storage][0] > 100) return Error(playerid, "Storage mobil bisnis anda sudah penuh maksimal 100 food");
			VehicleData[vehicleid][Storage][0] += idiot;
			bData[bid][bProd] -= idiot;
			SendClientMessageEx(playerid, COLOR_ARWIN, "BUSSINES: "WHITE_E"You successfully restock a business vehicle, with products of "YELLOW_E"%d unit(s), "WHITE_E"total in storage: "YELLOW_E"%d unit(s)", idiot, VehicleData[vehicleid][Storage][0]);
		}
    }
	return 1;
}

Dialog:BuyProdVehicle(playerid, response, listitem, inputtext[])
{
	if (response)
	{
        new
            bizid = ProductOffer[playerid][1],
            price,
            vehicleid = ProductOffer[playerid][2],
            otherid = ProductOffer[playerid][0];

		if(bizid != -1 && response && listitem != -1)
		{
			price = bData[bizid][bP][listitem];
			if(GetPlayerMoney(playerid) < price) return Error(playerid, "Not enough money!");

			new Float:health;
			GetPlayerHealth(playerid,health);
			if(bData[bizid][bType] == 1)
			{
				switch(listitem)
				{
					case 0:
					{
                        if(pData[playerid][pHunger]+12 > 100) pData[playerid][pHunger] = 100;
                        else pData[playerid][pHunger] += 12;
						GivePlayerMoneyEx(playerid, -price);
						SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}$%s", ReplaceString(bData[bizid][bPName0]), FormatMoney(price));
                        GivePlayerMoneyEx(otherid, price);
                        VehicleData[vehicleid][Storage][0]--;
					}
					case 1:
					{
						GivePlayerMoneyEx(playerid, -price);
						if(pData[playerid][pHunger]+45 > 100) pData[playerid][pHunger] = 100;
                        else pData[playerid][pHunger] += 45;
						SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}$%s", ReplaceString(bData[bizid][bPName1]), FormatMoney(price));
						GivePlayerMoneyEx(otherid, price);
                        VehicleData[vehicleid][Storage][0]--;
					}
					case 2:
					{
						GivePlayerMoneyEx(playerid, -price);
						if(pData[playerid][pHunger]+60 > 100) pData[playerid][pHunger] = 100;
                        else pData[playerid][pHunger] += 60;
						SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}$%s", ReplaceString(bData[bizid][bPName2]), FormatMoney(price));
						GivePlayerMoneyEx(otherid, price);
                        VehicleData[vehicleid][Storage][0]--;
					}
					case 3:
					{
						GivePlayerMoneyEx(playerid, -price);
						GivePlayerMoneyEx(otherid, price);
                        VehicleData[vehicleid][Storage][0]--;
                        if(pData[playerid][pEnergy]+45 > 100) pData[playerid][pEnergy] = 100;
                        else pData[playerid][pEnergy] += 45;
						SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}$%s", ReplaceString(bData[bizid][bPName3]), FormatMoney(price));
					}
				}
			}
		}
    }
    return 1;
}
