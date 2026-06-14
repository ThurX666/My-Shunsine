
CMD:dmvehicleposspawn(playerid, params[])
{
    if(pData[playerid][pAdmin] >= 6)
	{
	    new d;
	    if(sscanf(params, "d", d))  return SendClientMessageEx(playerid, COLOR_WHITE, "USAGE: /dmvehicleposspawn [dealerid]");
	    new Float: x, Float: y, Float: z, Float: a;
		GetPlayerPos(playerid,x,y,z);
		GetPlayerFacingAngle(playerid, a);
		CarDealershipInfo[d][cdVehicleSpawn][0] = x;
		CarDealershipInfo[d][cdVehicleSpawn][1] = y;
		CarDealershipInfo[d][cdVehicleSpawn][2] = z;
		CarDealershipInfo[d][cdVehicleSpawn][3] = a;
		SavecDealership(d);
		SendClientMessageEx(playerid, COLOR_ARWIN, "DEALERSHIP: "YELLOW_E"Succesfull set vehicle pos spawn "YELLOW_E"dealership id {00FFFF}%d", d);
	}
	else return SendClientMessageEx(playerid, COLOR_GREY, " You are not allowed to use this command.");
    return 1;
}
	
CMD:dmvehiclepos(playerid, params[])
{
    if(pData[playerid][pAdmin] >= 6)
	{
	    new d, v;
	    if(sscanf(params, "dd", d, v)) 
		{
			SendClientMessageEx(playerid, COLOR_WHITE, "USAGE: /dmvehiclepos [dealerid] [slot]");
			return 1;
		}
	    new Float: x, Float: y, Float: z, Float: a;
		GetPlayerPos(playerid,x,y,z);
		GetPlayerFacingAngle(playerid, a);
		CarDealershipInfo[d][cdVehicleSpawnX][v] = x;
		CarDealershipInfo[d][cdVehicleSpawnY][v] = y;
		CarDealershipInfo[d][cdVehicleSpawnZ][v] = z;
		CarDealershipInfo[d][cdVehicleSpawnAngle][v] = a;
		SetPVarInt(playerid, "editingcdvehpos", 0);
		SetPVarInt(playerid, "editingcdvehnew", 0);
		CreateDealershipPickup(d);

		SavecDealership(d);
		SendClientMessageEx(playerid, COLOR_ARWIN, "DEALERSHIP: "YELLOW_E"Succesfull set vehicle pos slot {00FFFF}%d "YELLOW_E"dealership id {00FFFF}%d", v, d);
	}
	else
	{
        SendClientMessageEx(playerid, COLOR_GREY, " You are not allowed to use this command.");
	}
    return 1;
}
	
CMD:editcd(playerid, params[])
{
    static
        d,
        type[24],
        string[128];

    if(pData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", d, type, string))
    {
        Usage(playerid, "/editcd [dealerid] [name]");
        SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} owner, location, money");
        return 1;
    }
    if(!Iter_Contains(Dealership, d)) return Error(playerid, "You have specified an invalid ID.");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, CarDealershipInfo[d][cdEntranceX], CarDealershipInfo[d][cdEntranceY], CarDealershipInfo[d][cdEntranceZ]);
		CreateDealershipPickup(d);

		SavecDealership(d);
		SendClientMessageEx(playerid, COLOR_ARWIN, "DEALERSHIP: "YELLOW_E"Succesfull location dealerid {00FFFF}%d",d);
    }
    else if(!strcmp(type, "owner", true))
    {
        new owners[MAX_PLAYER_NAME];

        if(sscanf(string, "s[32]", owners))
            return Usage(playerid, "/editcd [dealerid] [owner] [player name] (use '-' to no owner)");

        format(CarDealershipInfo[d][cdOwner], MAX_PLAYER_NAME, owners);
  
        CreateDealershipPickup(d);

		SavecDealership(d);
        SendAdminMessage(COLOR_RED, "%s has adjusted the owner of dealer ID: %d to %s", pData[playerid][pAdminname], d, owners);
    }
	else if(!strcmp(type, "money", true))
    {
        new money;

        if(sscanf(string, "d", money))
            return Usage(playerid, "/editcd [dealerid] [money] [Ammount]");

        CarDealershipInfo[d][cdTill] = money;
        SavecDealership(d);
        SendAdminMessage(COLOR_RED, "%s has adjusted the money of Dealer ID: %d to %s.", pData[playerid][pAdminname], d, FormatMoney(money));
    }
    return 1;
}

//DEALER
CMD:dm(playerid, params[])
{
    foreach(new d : Dealership)
	{
        if(IsPlayerInRangeOfPoint(playerid, 3.0, CarDealershipInfo[d][cdEntranceX], CarDealershipInfo[d][cdEntranceY], CarDealershipInfo[d][cdEntranceZ])) {
            if(IsPlayerOwnerOfCDEx(playerid, d))
			{
                SetPVarInt(playerid, "editingcd", d);
                SetPVarInt(playerid, "editingcdveh", -1);
                SetPVarInt(playerid, "editingcdvehpos", 0);
                SetPVarInt(playerid, "editingcdvehnew", 0);
                new listitems[] = "Vehicles\nDealership - Safes\nChange Name Dealership\nEmployees";
                ShowPlayerDialog(playerid,DIALOG_CDEDIT,DIALOG_STYLE_LIST,"Choose an item to continue", listitems,"Select","Cancel");
                return 1;
            }
            else if(Dealer_IsEmployee(playerid, d))
			{
                SetPVarInt(playerid, "editingcd", d);
                SetPVarInt(playerid, "editingcdveh", -1);
                SetPVarInt(playerid, "editingcdvehpos", 0);
                SetPVarInt(playerid, "editingcdvehnew", 0);
                new listitems[] = "Vehicles\nDealership - Safes\nChange Name Dealership\nEmployees";
                ShowPlayerDialog(playerid,DIALOG_CDEDIT,DIALOG_STYLE_LIST,"Choose an item to continue", listitems,"Select","Cancel");
                return 1;
            }
            else
			{
                SendClientMessageEx(playerid, COLOR_GREY, "You do not own that Car Dealership.");
                return 1;
            }
        }
    }
    SendClientMessageEx(playerid, COLOR_GREY, "ERROR: You must be standing inside the radius of the Car Dealership.");
    return 1;
}

CMD:pputdm(playerid, params[])
{
    foreach(new d : Dealership)
	{
        if(IsPlayerInRangeOfPoint(playerid, 3.0, CarDealershipInfo[d][cdEntranceX], CarDealershipInfo[d][cdEntranceY], CarDealershipInfo[d][cdEntranceZ])) {
            if(!IsPlayerOwnerOfCDEx(playerid, d) && Dealer_IsEmployee(playerid, d))
            {
            	SetPVarInt(playerid, "editingcd", d);
	            SetPVarInt(playerid, "editingcdveh", -1);
	            SetPVarInt(playerid, "editingcdvehpos", 0);
	            SetPVarInt(playerid, "editingcdvehnew", 0);
	            new listitems[] = "Restock Vehicles\nBank\nDealership Settings\nEmployees";
	            ShowPlayerDialog(playerid,DIALOG_CDEDIT,DIALOG_STYLE_LIST,"Choose an item to continue", listitems,"Select","Cancel");
       	 	}
        	else
			{
           		SendClientMessageEx(playerid, COLOR_GREY, "You are not the owner of this car dealership.");
            	return 1;
            }
        }
    }
    SendClientMessageEx(playerid, COLOR_GREY, "ERROR: You must be standing inside the radius of the Car Dealership.");
    return 1;
}

CMD:destroydealership(playerid, params[])
{
    if(pData[playerid][pAdmin] < 6)
	{
        SendClientMessageEx(playerid, COLOR_GREY, " You are not allowed to use this command.");
        return 1;
    }

    new string[128], query[128], dealershipid;
    if(sscanf(params, "d", dealershipid)) return SendClientMessageEx(playerid, COLOR_WHITE, "USAGE: /destroydealership [dealershipid]");
    if((dealershipid < 0 || dealershipid >= MAX_CARDEALERSHIPS))
        return Error(playerid, "You have specified an invalid ID.");
	if(!Iter_Contains(Dealership, dealershipid)) return Error(playerid, "The bisnis you specified ID of doesn't exist.");
    SendCustomMessage(playerid, "SUCCES", "You have successfully deleted the dealer's business property "AQUA_E"ID: %d", dealershipid);
	CarDealershipInfo[dealershipid][cdEntranceX] = 0.0;
	CarDealershipInfo[dealershipid][cdEntranceY] = 0.0;
	CarDealershipInfo[dealershipid][cdEntranceZ] = 0.0;
	CarDealershipInfo[dealershipid][cdRadius] = 0.0;
	CarDealershipInfo[dealershipid][cdTill] = 0;
	CarDealershipInfo[dealershipid][cdOwned] = 0;
	CarDealershipInfo[dealershipid][cdPrice] = 0;
	CarDealershipInfo[dealershipid][cdType] = 0;
	format(string, sizeof(string), "-");
	strmid(CarDealershipInfo[dealershipid][cdOwner], string, 0, strlen(string), 255);
	format(string, sizeof(string), "None");
	strmid(CarDealershipInfo[dealershipid][cdMessage], string, 0, strlen(string), 255);
	DestroyDynamic3DTextLabel(CarDealershipInfo[dealershipid][cdTextLabel]);
	DestroyDynamicPickup(CarDealershipInfo[dealershipid][cdPickupID]);
	CarDealershipInfo[dealershipid][cdPickupID] = 0;
	CarDealershipInfo[dealershipid][cdTextLabel] = Text3D:INVALID_3DTEXT_ID;
	CarDealershipInfo[dealershipid][cdVehicleSpawn][0] = 0.0;
    CarDealershipInfo[dealershipid][cdVehicleSpawn][1] = 0.0;
    CarDealershipInfo[dealershipid][cdVehicleSpawn][2] = 0.0;
    CarDealershipInfo[dealershipid][cdVehicleSpawn][3] = 0.0;
	for(new v = 0; v < MAX_DEALERSHIPVEHICLES; v++)
	{
		if(CarDealershipInfo[dealershipid][cdVehicleModel][v] != 0)
		{
	        DestroyCarDealershipVehicle(dealershipid, v);
			CarDealershipInfo[dealershipid][cdVehicleId][v] = INVALID_VEHICLE_ID;
		}
	}
	Iter_Remove(Dealership, dealershipid);
	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM cd WHERE ID=%d", CarDealershipInfo[dealershipid][cdID]);
	mysql_tquery(g_SQL, query);
    return 1;
}

CMD:buydealership(playerid, params[])
{
    foreach(new d : Dealership)
	{
        if(IsPlayerInRangeOfPoint(playerid, 3.0, CarDealershipInfo[d][cdEntranceX], CarDealershipInfo[d][cdEntranceY], CarDealershipInfo[d][cdEntranceZ]))
		{
            if(PropertiCommercial_CountMax(playerid) >= PropertiesCommercial_Max(playerid)) return Error(playerid, "You can no longer buy a business, your property slots are full");
			if(strcmp(CarDealershipInfo[d][cdOwner], "-")) return Error(playerid, "That Car Dealership is already owned and it's not for sale.");

			if(GetPlayerMoney(playerid) < CarDealershipInfo[d][cdPrice])
			{
				SendClientMessageEx(playerid, COLOR_GREY, "Uang Anda kurang untuk membeli dealer kendaraan ini.");
				return 1;
			}
			GivePlayerMoneyEx(playerid, -CarDealershipInfo[d][cdPrice]);
			GetPlayerName(playerid, CarDealershipInfo[d][cdOwner], MAX_PLAYER_NAME);
			new String[212];
			format(String, sizeof(String), "{00FFFF}[id:%d]\n{FFFF00}%s\n{FFFFFF}Owner: {00FF00}%s",d, CarDealershipInfo[d][cdMessage], CarDealershipInfo[d][cdOwner]);
			UpdateDynamic3DTextLabelText(CarDealershipInfo[d][cdTextLabel], COLOR_TWAQUA, String);
			SavecDealership(d);
        }
    }
    return 1;
}

CMD:selldealership(playerid, params[])
{
	new string[128];

    foreach(new d : Dealership)
	{
        if(IsPlayerInRangeOfPoint(playerid, 3.0, CarDealershipInfo[d][cdEntranceX], CarDealershipInfo[d][cdEntranceY], CarDealershipInfo[d][cdEntranceZ]))
		{
            if(IsPlayerOwnerOfCDEx(playerid, d))
			{
                SetPVarInt(playerid, "editingcd", d);
                format(string,128,"Are you sure you want to sell this Car Dealership for $%s?\n.", FormatMoney(CarDealershipInfo[d][cdPrice]));
                ShowPlayerDialog(playerid,DIALOG_CDSELL,DIALOG_STYLE_MSGBOX,"Warning:",string,"Sell","Cancel");
                return 1;
            }
            else
			{
                SendClientMessageEx(playerid, COLOR_GREY, "You are not the owner of this car dealership.");
                return 1;
            }
        }
    }
    SendClientMessageEx(playerid, COLOR_GREY, "You have to be near a car dealership.");
    return 1;
}

CMD:destroycdveh(playerid, params[])
{
    if(pData[playerid][pAdmin] < 6)
	{
        SendClientMessageEx(playerid, COLOR_GREY, " You are not allowed to use this command.");
        return 1;
    }

    new string[128], vehid;
    if(sscanf(params, "d", vehid)) return SendClientMessageEx(playerid, COLOR_WHITE, "USAGE: /destroycdveh [vehicleid]");
    DestroyCarDealershipVehicle(GetCarDealershipId(vehid), GetCarDealershipVehicleId(vehid));
    SavecDealership(GetCarDealershipId(vehid));
    format(string, sizeof(string), "Car Dealership Vehicle deleted with ID %d.", vehid);
    SendClientMessageEx(playerid, COLOR_GRAD1, string);
    return 1;
}

CMD:createdealership(playerid, params[])
{
    if(pData[playerid][pAdmin] >= 6)
	{
	    new query[512], dealershipid = Iter_Free(Dealership), Float:X,Float:Y,Float:Z;

	    GetPlayerPos(playerid,X,Y,Z);
	    if(dealershipid == -1) return Error(playerid, "Car Dealerships limit reached.");
        format(CarDealershipInfo[dealershipid][cdOwner], 128, "-");
        CarDealershipInfo[dealershipid][cdEntranceX] = X;
        CarDealershipInfo[dealershipid][cdEntranceY] = Y;
        CarDealershipInfo[dealershipid][cdEntranceZ] = Z;
        CarDealershipInfo[dealershipid][cdRadius] = 30;
        CarDealershipInfo[dealershipid][cdPrice] = 6500000;
        CarDealershipInfo[dealershipid][cdType] = 1;
        format(CarDealershipInfo[dealershipid][cdMessage], 212, "");
        SendCustomMessage(playerid, "SUCCES", "You have succeeded in creating a dealer business property at a price "GREEN_E"$%s "WHITE_E", ID:"AQUA_E"[%d]", FormatMoney(CarDealershipInfo[dealershipid][cdPrice]), dealershipid);
        
        Iter_Add(Dealership, dealershipid);
        mysql_format(g_SQL, query, sizeof(query), "INSERT INTO cd SET ID='%d', entrancex='%f', entrancey='%f', entrancez='%f', price='%d'", dealershipid, CarDealershipInfo[dealershipid][cdEntranceX], CarDealershipInfo[dealershipid][cdEntranceY], CarDealershipInfo[dealershipid][cdEntranceZ], CarDealershipInfo[dealershipid][cdPrice]);
	    mysql_tquery(g_SQL, query, "cdDealer", "i", dealershipid);
	}
	else PermissionError(playerid);
    return 1;
}

CMD:gotocd(playerid, params[])
{
    if(pData[playerid][pAdmin] < 2)
	{
        SendClientMessageEx(playerid, COLOR_GREY, " You are not allowed to use this command.");
        return 1;
    }
	new dealershipid;
    if(sscanf(params, "d", dealershipid)) return SendClientMessageEx(playerid, COLOR_WHITE, "USAGE: /gotodealership [dealershipid]");
    if (!Iter_Contains(Dealership, dealershipid))
        return Error(playerid, "Invalid CarDealership id.");
    SetPlayerPos(playerid, CarDealershipInfo[dealershipid][cdEntranceX], CarDealershipInfo[dealershipid][cdEntranceY], CarDealershipInfo[dealershipid][cdEntranceZ]);
    return 1;
}
