
Dialog:DialogVehicleInfo(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				new i = pData[playerid][pListitems];
				new irwan[500], string[500];
				if(Vehicle_IsOwner(playerid, i))
				{
					format(string, sizeof(string), "{FFFFFF}Vehicle: {00FFFF}%s\n", GetVehicleModelName(pvData[i][cModel]));
					strcat(irwan, string);
					format(string, sizeof(string), "{FFFFFF}Plate Vehicle: {FFFF00}%s\n", pvData[i][cPlate]);
					strcat(irwan, string);
					format(string, sizeof(string), "{FFFFFF}Insurance: {FFFF00}%d year(s)\n", pvData[i][cInsu]);
					strcat(irwan, string);
					format(string, sizeof(string), "{FFFFFF}Upgarde\n");
					strcat(irwan, string);
					if(pvData[i][cMesinUpgrade] == 1)
					{
						format(string, sizeof(string), "{FFFFFF}- {00FF00}Engine\n");
						strcat(irwan, string);
					}	
					if(pvData[i][pvBodyUpgrade] == 1)
					{
						format(string, sizeof(string), "{FFFFFF}- {00FF00}Body");
						strcat(irwan, string);
					}	
					format(string, sizeof(string), "{FFFFFF}Input a player ID or Name to show this information to other player:"GREEN_E" input below\n");
					strcat(irwan, string);
					Dialog_Show(playerid, VehicleDetail, DIALOG_STYLE_INPUT, "Vehicle Detail", irwan, "Show", "Back");
				}
			}
			case 1:
			{
				new i = pData[playerid][pListitems];
				new irwan[500], string[500];
				if(Vehicle_IsOwner(playerid, i))
				{
					format(string, sizeof(string), "{FFFFFF}Vehicle: {00FFFF}%s\n", GetVehicleModelName(pvData[i][cModel]));
					strcat(irwan, string);
					format(string, sizeof(string), "{FFFFFF}Plate Vehicle: {FFFF00}%s\n", pvData[i][cPlate]);
					strcat(irwan, string);
					format(string, sizeof(string), "{FFFFFF}Insurance: {FFFF00}%d year(s)\n", pvData[i][cInsu]);
					strcat(irwan, string);
					format(string, sizeof(string), "{FFFFFF}Upgarde\n");
					strcat(irwan, string);
					if(pvData[i][cMesinUpgrade] == 1)
					{
						format(string, sizeof(string), "{FFFFFF}- {00FF00}Engine\n");
						strcat(irwan, string);
					}	
					if(pvData[i][pvBodyUpgrade] == 1)
					{
						format(string, sizeof(string), "{FFFFFF}- {00FF00}Body");
						strcat(irwan, string);
					}
					format(string, sizeof(string), "{FFFFFF}Enter the selling price of your vehicle\n"RED_E"NOTE: Use dollar currency");
					strcat(irwan, string);
					Dialog_Show(playerid, VehicleSellPlayer, DIALOG_STYLE_INPUT, "Vehicle Sell", irwan, "Next", "Back");
				}
			}
			case 2:
			{
				new i = pData[playerid][pListitems];
				new irwan[500], string[500];
				if(Vehicle_IsOwner(playerid, i))
				{
					format(string, sizeof(string), "{FFFFFF}Vehicle: {00FFFF}%s\n", GetVehicleModelName(pvData[i][cModel]));
					strcat(irwan, string);
					format(string, sizeof(string), "{FFFFFF}Plate Vehicle: {FFFF00}%s\n", pvData[i][cPlate]);
					strcat(irwan, string);
					format(string, sizeof(string), "{FFFFFF}Insurance: {FFFF00}%d year(s)\n", pvData[i][cInsu]);
					strcat(irwan, string);
					format(string, sizeof(string), "{FFFFFF}Upgarde\n");
					strcat(irwan, string);
					if(pvData[i][cMesinUpgrade] == 1)
					{
						format(string, sizeof(string), "{FFFFFF}- {00FF00}Engine\n");
						strcat(irwan, string);
					}	
					if(pvData[i][pvBodyUpgrade] == 1)
					{
						format(string, sizeof(string), "{FFFFFF}- {00FF00}Body");
						strcat(irwan, string);
					}	
					format(string, sizeof(string), "{FFFFFF}Enter the player ID or Name to give your vehicle to another player:"GREEN_E" input below\n");
					strcat(irwan, string);
					Dialog_Show(playerid, VehicleGivePlayer, DIALOG_STYLE_INPUT, "Vehicle Give", irwan, "Give", "Back");
				}
			}
			case 3:
			{
				new i = pData[playerid][pListitems];
				new string[500];
				if(Vehicle_IsOwner(playerid, i))
				{
					format(string, sizeof(string), "{FFFFFF}Vehicle to trade: "AQUA_E"\n{FFFFFF}Input playerid or name: "GREEN_E"(input below)", GetVehicleModelName(pvData[i][cModel]));
					Dialog_Show(playerid, VehicleTradePlayer, DIALOG_STYLE_INPUT, "Trade vehicle with Player", string, "Next", "Back");
				}
			}
			case 4:
			{
				new i = pData[playerid][pListitems];
				new string[500];
				if(Vehicle_IsOwner(playerid, i))
				{
					format(string, sizeof(string), "{FFFFFF}Do you want to sell your "AQUA_E"%s {FFFFFF}vehicle for "GREEN_E"$%s?", GetVehicleModelName(pvData[i][cModel]), pvData[i][cPrice]/30);
					Dialog_Show(playerid, SellVehicleServer, DIALOG_STYLE_MSGBOX, "Selling Vehicle", string, "Yes", "Back");
				}
			}
		}
	}
    return 1;
}

Dialog:VehicleSpawn(playerid, response, listitem, inputtext[]) {
    if (response) 
	{
		if (listitem != -1)
        {
			new i = gListedItems[playerid][listitem];
	        
			// if (pvData[i][cImpound] ==0 0) return Error(playerid, "Can't go to impounded vehicle.");
			// if (pvData[i][cPark] != -1) return Error(playerid, "Cannot go to vehicle inside garage!");
			// if (pvData[i][cVehicleGarage] != -1) return Error(playerid, "Cannot go to vehicle inside garage!");
			//if (pvData[i][cInsideInsurance] != -1) return Error(playerid, "Cannot go to vehicle inside insurance!");
			if (pvData[i][cDespawn] == 0) return Error(playerid, "Cannot spawn vehicles that have not spawned!");

			OnPlayerVehicleRespawn(i);
			SetVehicleVirtualWorld(pvData[i][cVeh], GetPlayerVirtualWorld(playerid));
			LinkVehicleToInterior(pvData[i][cVeh], GetPlayerInterior(playerid));
			SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE:"WHITE_E" Your "AQUA_E"%s"WHITE_E" has been spawned back into the world!", GetVehicleModelName(pvData[i][cModel]));
		} else Error(playerid, "Select Kendaraan yang ada ingin spawn");
    }
    return 1;
}

Dialog:SellVehicleServer(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new vehicleid = pData[playerid][pListitems];
		foreach(new i : PVehicles)
		{
			if(pvData[vehicleid][cVeh] == pvData[i][cVeh])
			{
				if(pvData[i][cOwner] == pData[playerid][pID])
				{
					if(!IsValidVehicle(pvData[i][cVeh])) return Error(playerid, "Your vehicle is not spanwed!");
					if(pvData[i][cRent] != 0) return Error(playerid, "You can't sell rental vehicle!");
					new pay = pvData[i][cPrice]/30;

					GivePlayerMoneyEx(playerid, pay);
					SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You sell your "AQUA_E"%s "WHITE_E"vehicle for "GREEN_E"$%s", GetVehicleModelName(pvData[i][cModel]), FormatMoney(pay));
					new query[128];
					mysql_format(g_SQL, query, sizeof(query), "DELETE FROM vehicle WHERE id = '%d'", pvData[i][cID]);
					mysql_tquery(g_SQL, query);
					if(IsValidVehicle(pvData[i][cVeh])) DestroyVehicle(pvData[i][cVeh]);
					Iter_SafeRemove(PVehicles, i, i);
				}
			}
		}
	}
    return 1;
}

Dialog:VehicleTradePlayer(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new vehicleid = pData[playerid][pListitems], otherid = strval(inputtext);
		if (!IsPlayerNearPlayer(playerid, otherid, 5.0))
            return Error(playerid, "You're not not near with that player");
		TradeVehicleID[otherid] = vehicleid;
		TradePlayerID[otherid] = playerid;
		new info[256], count = 0;

		strcat(info,"Vehicle\tInsurance\n");
		foreach(new i : PVehicles)  if (pData[otherid][pID] == pvData[i][cOwner]) {
			strcat(info,sprintf("%s\t%d\n",GetVehicleModelName(pvData[i][cModel]),pvData[i][cInsu]));
			ListedVehicles[playerid][count++] = i;
		}
		if (count) Dialog_Show(playerid, VehicleTrade, DIALOG_STYLE_TABLIST_HEADERS, "Vehicle Trade", info, "Trade", "Cancel");
		else Error(playerid, "That player doesn't have any vehicle");
	}
    return 1;
}

Dialog:VehicleTrade(playerid, response, listitem, inputtext[]) {
    if (!response)
        return 0;

    new vehid = ListedVehicles[playerid][listitem], userid = INVALID_PLAYER_ID;

    foreach (new i : Player) if (TradePlayerID[i] == playerid) {
        userid = i;
    }

    if (userid != INVALID_PLAYER_ID) {
        TradePlayerID[playerid] = userid;
        TradeVehicleID[playerid] = vehid;
        new playerveh = TradeVehicleID[userid],
            vehnameplayerid[32],
            vehnameuserid[32],
			string[212];

		GetVehicleNameByVehicle(pvData[vehid][cVeh], vehnameplayerid);
		GetVehicleNameByVehicle(pvData[playerveh][cVeh], vehnameuserid);
		SendClientMessageEx(userid, COLOR_ARWIN, "TRANSFER: "YELLOW_E"%s "WHITE_E"has offeredyou to trade "AQUA_E"%s "WHITE_E"with your "GREEN_E"%s", ReturnName(playerid), vehnameuserid, vehnameplayerid);
        format(string, sizeof(string), "Vehicle: "AQUA_E"%s", vehnameuserid);
		SendClientMessageEx(userid, COLOR_ARWIN, string);
		format(string, sizeof(string), "Plate Vehicle: {FFFF00}%s", pvData[pvData[playerveh][cVeh]][cPlate]);
		SendClientMessageEx(userid, COLOR_ARWIN, string);
		format(string, sizeof(string), "Insurance: {FFFF00}%d year(s)", pvData[pvData[playerveh][cVeh]][cInsu]);
		SendClientMessageEx(userid, COLOR_ARWIN, string);
		format(string, sizeof(string), "Upgarde\n");
		SendClientMessageEx(userid, COLOR_ARWIN, string);
		if(pvData[pvData[playerveh][cVeh]][cMesinUpgrade] == 1)
		{
			format(string, sizeof(string), "{FFFFFF}- {00FF00}Engine\n");
			SendClientMessageEx(userid, COLOR_ARWIN, string);
		}	
		if(pvData[pvData[playerveh][cVeh]][pvBodyUpgrade] == 1)
		{
			format(string, sizeof(string), "{FFFFFF}- {00FF00}Body");
			SendClientMessageEx(userid, COLOR_ARWIN, string);
		}
        SendClientMessageEx(userid, COLOR_ARWIN, "HINT: Use "WHITE_E"'"YELLOW_E"/accepttransfer"WHITE_E"' to accept the trade or "WHITE_E"'"YELLOW_E"/canceltransfer"WHITE_E"' to deny to transaction");
        
    } else Error(playerid, "That player has been disconnected.");
    return 1;
}

Dialog:VehicleGivePlayer(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new vehicleid = pData[playerid][pListitems], otherid = strval(inputtext);
		new count = 0, limit = LimitSlotPlayerVehicle(otherid);
		foreach(new ii : PVehicles)
		{
			if(pvData[ii][cOwner] == pData[otherid][pID])
				count++;
		}
		if(count >= limit)
		{
			Error(playerid, "This player have too many vehicles, sell a vehicle first!");
			return 1;
		}
		if(!IsValidVehicle(pvData[vehicleid][cVeh])) return 0;
		if(!IsPlayerConnected(otherid)) return 0;
		new query[128];
		foreach(new vehid : PVehicles) if(pvData[vehid][cVeh] == pvData[vehicleid][cVeh]) 
		{
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
			pvData[vehid][cImpound] = 0;
			for(new j = 0; j < 10; j++)
			{
				pvData[vehid][cWeapon][j] = 0;
				pvData[vehid][cAmmo][j] = 0;
			}
			mysql_format(g_SQL, query, sizeof(query), "UPDATE vehicle SET owner='%d' WHERE id=%d", pvData[vehid][cOwner], pvData[vehid][cID]);
			mysql_tquery(g_SQL, query);
			SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You managed to give the "AQUA_E"%s's "WHITE_E"vehicle to "YELLOW_E"%s", GetVehicleName(pvData[vehid][cVeh]), ReturnName2(otherid));
			SendClientMessageEx(otherid, COLOR_ARWIN, "VEHICLE: "YELLOW_E"%s "WHITE_E"gives his "AQUA_E"%s's "WHITE_E"vehicle to you", ReturnName2(playerid), GetVehicleName(pvData[vehid][cVeh]));
		}
	}
    return 1;
}

Dialog:VehicleSellPlayer(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		if(strval(inputtext) < 1)
		{
			Dialog_Show(playerid, VehicleSellPlayer, DIALOG_STYLE_INPUT, "Vehicle Sell", "Enter the selling price of your vehicle:\n"RED_E"NOTE: Use dollar currency", "Next", "Back");
			return 1;
		}
		new duit[32];
		format(duit, sizeof(duit), "%d00", strval(inputtext));
		SellPriceVehicle[playerid] = strval(duit);
		new i = pData[playerid][pListitems];
		new irwan[500], string[500];
		if(Vehicle_IsOwner(playerid, i))
		{
			format(string, sizeof(string), "{FFFFFF}Vehicle: {00FFFF}%s\n", GetVehicleName(pvData[i][cVeh]));
			strcat(irwan, string);
			format(string, sizeof(string), "{FFFFFF}Plate Vehicle: {FFFF00}%s\n", pvData[i][cPlate]);
			strcat(irwan, string);
			format(string, sizeof(string), "{FFFFFF}Insurance: {FFFF00}%d year(s)\n", pvData[i][cInsu]);
			strcat(irwan, string);
			format(string, sizeof(string), "{FFFFFF}Upgarde\n");
			strcat(irwan, string);
			if(pvData[i][cMesinUpgrade] == 1)
			{
				format(string, sizeof(string), "{FFFFFF}- {00FF00}Engine\n");
				strcat(irwan, string);
			}	
			if(pvData[i][pvBodyUpgrade] == 1)
			{
				format(string, sizeof(string), "{FFFFFF}- {00FF00}Body");
				strcat(irwan, string);
			}
			format(string, sizeof(string), "{FFFFFF}Are you sure you want to sell your vehicle for "GREEN_E"$%s?\n{FFFFFF}If so, enter the id or name of the player who wants to buy your vehicle", FormatMoney(strval(duit)));
			strcat(irwan, string);
			Dialog_Show(playerid, VehicleSellConfirm, DIALOG_STYLE_INPUT, "Vehicle Sell", irwan, "Sell", "Back");
		}
	}
    return 1;
}

Dialog:VehicleSellConfirm(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new vehicleid = pData[playerid][pListitems], otherid = strval(inputtext);
		if(!IsPlayerConnected(otherid)) return 0;
		new count = 0, limit = LimitSlotPlayerVehicle(otherid);
		foreach(new ii : PVehicles)
		{
			if(pvData[ii][cOwner] == pData[otherid][pID])
				count++;
		}
		if(count >= limit)
		{
			Error(playerid, "This player have too many vehicles, sell a vehicle first!");
			return 1;
		}
		SellPriceVehicle[otherid] = SellPriceVehicle[playerid];
		SellIDPlayerVehicle[otherid] = playerid;
		SellIDPlayerVehicle[playerid] = otherid; 
		SellIDVehiclePlayer[otherid] = vehicleid;
		SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You sold the "AQUA_E"%s's "WHITE_E"vehicle to "YELLOW_E"%s "WHITE_E"for "GREEN_E"$%s", GetVehicleName(pvData[vehicleid][cVeh]), ReturnName(otherid), FormatMoney(SellPriceVehicle[playerid]));
		SendCustomMessage(otherid, "VEHICLE", ""YELLOW_E"%s "WHITE_E"sells the "AQUA_E"%s "WHITE_E"vehicle to you for "GREEN_E"$%s", ReturnName2(playerid), GetVehicleName(pvData[vehicleid][cVeh]), FormatMoney(SellPriceVehicle[playerid]));
		SendCustomMessage(otherid, "NOTE", ""WHITE_E"if you receive use the command "YELLOW_E"'/acceptvehicle'");
	}
    return 1;
}

Dialog:VehicleDetail(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new vehicleid = pData[playerid][pListitems], otherid = strval(inputtext), string[512];
		
		if(!IsValidVehicle(pvData[vehicleid][cVeh])) return 0;
		if(!IsPlayerConnected(otherid)) return 0;
		SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You show your {00FFFF}%s "WHITE_E"vehicle license to "YELLOW_E"%s", GetVehicleName(vehicleid), ReturnName(otherid));
		SendClientMessageEx(otherid, COLOR_ARWIN,"=================[Vehicle Ownership]=================\n");
		format(string, sizeof(string), "Vehicle: "AQUA_E"%s", GetVehicleModelName(pvData[vehicleid][cModel]));
		SendClientMessageEx(otherid, COLOR_ARWIN, string);
		format(string, sizeof(string), "Plate Vehicle: {FFFF00}%s", pvData[vehicleid][cPlate]);
		SendClientMessageEx(otherid, COLOR_ARWIN, string);
		format(string, sizeof(string), "Insurance: {FFFF00}%d year(s)", pvData[vehicleid][cInsu]);
		SendClientMessageEx(otherid, COLOR_ARWIN, string);
		format(string, sizeof(string), "Upgarde\n");
		SendClientMessageEx(otherid, COLOR_ARWIN, string);
		if(pvData[vehicleid][cMesinUpgrade] == 1)
		{
			format(string, sizeof(string), "{FFFFFF}- {00FF00}Engine\n");
			SendClientMessageEx(otherid, COLOR_ARWIN, string);
		}	
		if(pvData[vehicleid][pvBodyUpgrade] == 1)
		{
			format(string, sizeof(string), "{FFFFFF}- {00FF00}Body");
			SendClientMessageEx(otherid, COLOR_ARWIN, string);
		}
	}
    return 1;
}

Dialog:DialogVehicle(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		pData[playerid][pListitems] = gListedItems[playerid][listitem];
		Dialog_Show(playerid, DialogVehicleInfo, DIALOG_STYLE_LIST, "Vehicle Info", "Details\nSell to Player\nGive to Player\nTrade with Player\nSell to Server", "Select", "Close");	
	}
    return 1;
}

Dialog:CarLock(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		if (listitem == 0) {
            if (GetNearestVehicleToPlayer(playerid,4.0,false) == INVALID_VEHICLE_ID) return Error(playerid, "You are not standing near any vehicle");
            Vehicle_Lock(GetNearestVehicleToPlayer(playerid,4.0,false), playerid);
			return 1;
		}
		if (listitem != -1) {
			Vehicle_Lock(gListedItems[playerid][listitem], playerid);
		}
	}
    return 1;
}

Dialog:VehicleImpound(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new vehicleid = gListedItems[playerid][listitem];
		new price = pvData[vehicleid][cPrice]/55;
		if(GetPlayerMoney(playerid) < price) return Error(playerid, "You don't have enough money to pay the fine");
		if(pvData[vehicleid][cOwner] == pData[playerid][pID] && pvData[vehicleid][cImpound] == 1)
		{
			pvData[vehicleid][cPosX] = 1588.30;
			pvData[vehicleid][cPosY] = -1609.02;
			pvData[vehicleid][cPosZ] = 13.38;
			pvData[vehicleid][cImpound] = 0;
			GivePlayerMoneyEx(playerid, -price);
			if(!IsValidVehicle(pvData[vehicleid][cVeh]))  OnPlayerVehicleRespawn(vehicleid); 
			PutPlayerInVehicle(playerid, pvData[vehicleid][cVeh], 0);
			SendClientMessageEx(playerid, COLOR_ARWIN, "IMPOUND: "WHITE_E"You've unimpound your {00FFFF}%s "WHITE_E"from the impound center for "GREEN_E"$%s", GetVehicleModelName(pvData[vehicleid][cModel]), FormatMoney(price));
		}	
	}
    return 1;
}

Dialog:VehiclePayTicket(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new vehicleid = gListedItems[playerid][listitem];
		new price = pvData[vehicleid][cTicket];
		if(GetPlayerMoney(playerid) < price) return Error(playerid, "You don't have enough money to pay the fine");
		if(!IsValidVehicle(pvData[vehicleid][cVeh])) return 0;
		if(pvData[vehicleid][cOwner] == pData[playerid][pID])
		{
			if(pvData[vehicleid][cTicket] > 1 && !pvData[vehicleid][vLockTire])
			{
				pvData[vehicleid][cTicket] = 0;
				pvData[vehicleid][cTicketTime] = 0;
				GivePlayerMoneyEx(playerid, -price);
				SendClientMessageEx(playerid, COLOR_ARWIN, "TICKET: "WHITE_E"You have successfully paid the vehicle fine {00FFFF}%s", GetVehicleModelName(pvData[vehicleid][cModel]));
			}
			else if(pvData[vehicleid][cTicket] > 1 && pvData[vehicleid][vLockTire])
			{
				if(IsValidDynamic3DTextLabel(pvData[vehicleid][vLockTireText]))
                    DestroyDynamic3DTextLabel(pvData[vehicleid][vLockTireText]);

                pvData[vehicleid][vLockTire] = 0;
                pvData[vehicleid][vLockTireText] = Text3D:INVALID_STREAMER_ID;
                Vehicle_StopLockTire(vehicleid);
				pvData[vehicleid][cTicket] = 0;
				pvData[vehicleid][cTicketTime] = 0;
				GivePlayerMoneyEx(playerid, -price);
				SendClientMessageEx(playerid, COLOR_ARWIN, "TICKET: "WHITE_E"You have successfully paid the vehicle fine {00FFFF}%s", GetVehicleModelName(pvData[vehicleid][cModel]));
			}
		}	
	}
    return 1;
}

Dialog:AdmClaimInsurance(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new vehicleid = gListedItems[playerid][listitem], otherid = GetPVarInt(playerid, "AdmClaimInsurance");
		if(pvData[vehicleid][cOwner] == pData[otherid][pID] && pvData[vehicleid][cClaim] == 1)
		{
			new Float:x, Float:y, Float:z, Float:ang;
			GetPlayerPos(playerid, Float:x, Float:y, Float:z);
			GetPlayerFacingAngle(playerid, Float:ang);
			pvData[vehicleid][cPosX] = x;
			pvData[vehicleid][cPosY] = y;
			pvData[vehicleid][cPosZ] = z;
			pvData[vehicleid][cPosA] = ang;
			pvData[vehicleid][cHealth] = 1000;
			pvData[vehicleid][cFuel] = 1000;
			pvData[vehicleid][cVw] = GetPlayerVirtualWorld(playerid);
			pvData[vehicleid][cInt] = GetPlayerInterior(playerid);
			pvData[vehicleid][cClaim] = 0;
			pvData[vehicleid][cClaimTime] = 0;
			pvData[vehicleid][cInsu]++;
			if(!IsValidVehicle(pvData[vehicleid][cVeh]))  OnPlayerVehicleRespawn(vehicleid); 
			SendCustomMessage(playerid, "INSURANCE", "You have successfully claimed vehicle insurance");
			SendClientMessageEx(otherid, COLOR_ARWIN, "INSURANCE: "WHITE_E"Your vehicle has been successfully claimed by the admin ");
		}	
	}
    return 1;
}

Dialog:ClaimInsurance(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new vehicleid = gListedItems[playerid][listitem];
		switch(pvData[vehicleid][cModel]) {
			case 430, 446, 452, 453, 454, 472, 473, 484, 493, 595: {
				foreach(new id : Locations) if(IsPlayerInRangeOfPoint(playerid, 40.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]) && Location[id][locType] == 7) {
					if(pvData[vehicleid][cOwner] == pData[playerid][pID] && pvData[vehicleid][cClaim] == 1)
					{
						pvData[vehicleid][cPosX] = Location[id][locPos][0];
						pvData[vehicleid][cPosY] = Location[id][locPos][1];
						pvData[vehicleid][cPosZ] = Location[id][locPos][2];
						pvData[vehicleid][cPosA] = Location[id][locPos][3];
						pvData[vehicleid][cHealth] = 1000;
						pvData[vehicleid][cFuel] = 1000;
						pvData[vehicleid][cVw] = 0;
						pvData[vehicleid][cInt] = 0;
						pvData[vehicleid][cClaim] = 0;
						if(!IsValidVehicle(pvData[vehicleid][cVeh]))  OnPlayerVehicleRespawn(vehicleid); 
						SendClientMessageEx(playerid, COLOR_ARWIN, "INSURANCE: "WHITE_E"You have successfully claimed the {00FFFF}%s "WHITE_E"vehicle", GetVehicleModelName(pvData[vehicleid][cModel]));
					}	
				}
			}
			default: {
				foreach(new id : Locations) if(IsPlayerInRangeOfPoint(playerid, 40.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]) && Location[id][locType] == 6) {
					if(pvData[vehicleid][cOwner] == pData[playerid][pID] && pvData[vehicleid][cClaim] == 1)
					{
						pvData[vehicleid][cPosX] = Location[id][locPos][0];
						pvData[vehicleid][cPosY] = Location[id][locPos][1];
						pvData[vehicleid][cPosZ] = Location[id][locPos][2];
						pvData[vehicleid][cPosA] = Location[id][locPos][3];
						pvData[vehicleid][cHealth] = 1000;
						pvData[vehicleid][cFuel] = 1000;
						pvData[vehicleid][cVw] = 0;
						pvData[vehicleid][cInt] = 0;
						pvData[vehicleid][cClaim] = 0;
						if(!IsValidVehicle(pvData[vehicleid][cVeh]))  OnPlayerVehicleRespawn(vehicleid); 
						SendClientMessageEx(playerid, COLOR_ARWIN, "INSURANCE: "WHITE_E"You have successfully claimed the {00FFFF}%s "WHITE_E"vehicle", GetVehicleModelName(pvData[vehicleid][cModel]));
					}	
				}
			}
		}
	}
    return 1;
}

Dialog:BuyInsurance(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new vehicleid = gListedItems[playerid][listitem];
		new price = pvData[vehicleid][cPrice] / 4;
		if(GetPlayerMoney(playerid) < price) return Error(playerid, "You don't have enough money to buy insurance");
		if(!IsValidVehicle(pvData[vehicleid][cVeh])) return 0;
		if(Vehicle_IsOwner(playerid, vehicleid) && pvData[vehicleid][cClaim] == 0)
		{
			pvData[vehicleid][cInsu]++;
			GivePlayerMoneyEx(playerid, -price);
			SendClientMessageEx(playerid, COLOR_ARWIN, "INSURANCE: "WHITE_E"You buy insurance for "GREEN_E"$%s "WHITE_E"for the {00FFFF}%s "WHITE_E"car, total insurance "YELLOW_E"%d", FormatMoney(price), GetVehicleModelName(pvData[vehicleid][cModel]), pvData[vehicleid][cInsu]);
		}
	}
    return 1;
}

Dialog:BuyPlate(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new i = gListedItems[playerid][listitem];
		if(GetPlayerMoney(playerid) < 2500) return Error(playerid, "You don't have enough money to pay the fine");
		if(Vehicle_IsOwner(playerid, i))
		{
			foreach(new id : Locations) if(Location[id][locType] == 2) {
				new Float:distance = GetVehicleDistanceFromPoint(pvData[i][cVeh], Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
				if(distance >= Float:30.0) {
					return Error(playerid, "Selected vehicle needs to be parked outside this building");
				}
				else {
					format(pvData[i][cPlate], 32, "%s", GenerateRandomPlate());
					SetVehicleNumberPlate(pvData[i][cVeh], pvData[i][cPlate]);
					GivePlayerMoneyEx(playerid, -2500);
					SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"Model: ["GREEN_E"%s"WHITE_E"] || New plate: ["GREEN_E"%s"WHITE_E"]", GetVehicleModelName(pvData[i][cModel]), pvData[i][cPlate]);
				}
			}
		}	
	}
    return 1;
}

Dialog:RadioLink(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        if(!IsPlayerInAnyVehicle(playerid)) return Error(playerid, "You're not in vehicle.");
        SetVehicleRadio(GetPlayerVehicleID(playerid), inputtext);
    }
    return 1;
}

Dialog:RadioList(playerid, response, listitem, inputtext[]) 
{
    if (response) 
	{
        new url[128];
        format(url,sizeof(url),"%s",RadioStation[listitem][Link]);

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
            SetVehicleRadio(GetPlayerVehicleID(playerid), url);
            SendCustomMessage(playerid,"RADIO","You've been set the radio to: "YELLOW_E"%s", inputtext);
            return 1;
        }
    }
    return 1;
}

Dialog:VehiclePot(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)
	{
		switch (listitem)
		{
			case 0: 
			{
				new str[128];
				format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:");
				Dialog_Show(playerid, VehicleWithdrawPot, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
			}
			case 1: 
			{
				new str[128];
				format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:");
				Dialog_Show(playerid, VehicleDepositPot, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
			}
		}
	}
	else Vehicle_OpenStorage(playerid, vehicleid);
    return 1;
}

Dialog:VehicleWithdrawPot(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)
	{
		foreach(new ii : PVehicles)
		{
			if(pvData[ii][cVeh] == vehicleid)
			{
				new amount = strval(inputtext);

				if(isnull(inputtext))
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:", pvData[ii][cPot]);
					Dialog_Show(playerid, VehicleWithdrawPot, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
					return 1;
				}
				if(amount < 1 || amount > pvData[ii][cPot])
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:", pvData[ii][cPot]);
					Dialog_Show(playerid, VehicleWithdrawPot, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
					return 1;
				}
				pvData[ii][cPot] -= amount;
				pData[playerid][pPot] += amount;

				Vehicle_OpenStorage(playerid, vehicleid);

				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has withdrawn %d from their trunk safe.", ReturnName(playerid), amount);
			}
		}    
	}
	else Dialog_Show(playerid, VehiclePot, DIALOG_STYLE_LIST, "Pot Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
    return 1;
}

Dialog:VehicleDepositPot(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)
	{
		foreach(new ii : PVehicles)
		{
			if(pvData[ii][cVeh] == vehicleid)
			{
				new amount = strval(inputtext);

				if(isnull(inputtext))
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:", pvData[ii][cPot]);
					Dialog_Show(playerid, VehicleDepositPot, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
					return 1;
				}
				if(amount < 1 || amount > pData[playerid][pPot])
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:", pvData[ii][cPot]);
					Dialog_Show(playerid, VehicleDepositPot, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
					return 1;
				}
				if(pvData[ii][cPot] > 2000) return Error(playerid, "Tidak bisa memasukan barang lagi");
				pvData[ii][cPot] += amount;
				pData[playerid][pPot] -= amount;
				Vehicle_OpenStorage(playerid, vehicleid);
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deposited %d into their trunk safe.", ReturnName(playerid), amount);
			}
		}    
	}
	else Dialog_Show(playerid, VehiclePot, DIALOG_STYLE_LIST, "Pot Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
    return 1;
}

Dialog:VehicleCrack(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)
	{
		switch (listitem)
		{
			case 0: 
			{
				new str[128];
				format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:");
				Dialog_Show(playerid, VehicleWithdrawCrack, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
			}
			case 1: 
			{
				new str[128];
				format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:");
				Dialog_Show(playerid, VehicleDepositCrack, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
			}
		}
	}
	else Vehicle_OpenStorage(playerid, vehicleid);
    return 1;
}

Dialog:VehicleWithdrawCrack(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)
	{
		foreach(new ii : PVehicles)
		{
			if(pvData[ii][cVeh] == vehicleid)
			{
				new amount = strval(inputtext);

				if(isnull(inputtext))
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:", pvData[ii][cCrack]);
					Dialog_Show(playerid, VehicleWithdrawCrack, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
					return 1;
				}
				if(amount < 1 || amount > pvData[ii][cCrack])
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:", pvData[ii][cCrack]);
					Dialog_Show(playerid, VehicleWithdrawCrack, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
					return 1;
				}
				pvData[ii][cCrack] -= amount;
				pData[playerid][pCrack] += amount;

				Vehicle_OpenStorage(playerid, vehicleid);

				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has withdrawn %d from their trunk safe.", ReturnName(playerid), amount);
			}
		}    
	}
	else Dialog_Show(playerid, VehicleCrack, DIALOG_STYLE_LIST, "Crack Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
    return 1;
}

Dialog:VehicleDepositCrack(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)
	{
		foreach(new ii : PVehicles)
		{
			if(pvData[ii][cVeh] == vehicleid)
			{
				new amount = strval(inputtext);

				if(isnull(inputtext))
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:", pvData[ii][cCrack]);
					Dialog_Show(playerid, VehicleDepositCrack, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
					return 1;
				}
				if(amount < 1 || amount > pData[playerid][pCrack])
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:", pvData[ii][cCrack]);
					Dialog_Show(playerid, VehicleDepositCrack, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
					return 1;
				}
				if(pvData[ii][cCrack] > 2000) return Error(playerid, "Tidak bisa memasukan barang lagi");
				pvData[ii][cCrack] += amount;
				pData[playerid][pCrack] -= amount;
				Vehicle_OpenStorage(playerid, vehicleid);
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deposited %d into their trunk safe.", ReturnName(playerid), amount);
			}
		}    
	}
	else Dialog_Show(playerid, VehicleCrack, DIALOG_STYLE_LIST, "Crack Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
    return 1;
}

Dialog:VehicleMaterial(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)
	{
		switch (listitem)
		{
			case 0: 
			{
				new str[128];
				format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:");
				Dialog_Show(playerid, VehicleWithMaterial, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
			}
			case 1: 
			{
				new str[128];
				format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:");
				Dialog_Show(playerid, VehicleDepoMaterial, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
			}
		}
	}
	else Vehicle_OpenStorage(playerid, vehicleid);
    return 1;
}

Dialog:VehicleWithMaterial(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)
	{
		foreach(new ii : PVehicles)
		{
			if(pvData[ii][cVeh] == vehicleid)
			{
				new amount = strval(inputtext);

				if(isnull(inputtext))
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:", pvData[ii][cMaterial]);
					Dialog_Show(playerid, VehicleWithMaterial, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
					return 1;
				}
				if(amount < 1 || amount > pvData[ii][cMaterial])
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:", pvData[ii][cMaterial]);
					Dialog_Show(playerid, VehicleWithMaterial, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
					return 1;
				}
				pvData[ii][cMaterial] -= amount;
				pData[playerid][pMaterial] += amount;

				Vehicle_OpenStorage(playerid, vehicleid);

				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has withdrawn %d from their trunk safe.", ReturnName(playerid), amount);
			}
		}    
	}
	else Dialog_Show(playerid, VehicleMaterial, DIALOG_STYLE_LIST, "Material Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
    return 1;
}

Dialog:VehicleDepoMaterial(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)
	{
		foreach(new ii : PVehicles)
		{
			if(pvData[ii][cVeh] == vehicleid)
			{
				new amount = strval(inputtext);

				if(isnull(inputtext))
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:", pvData[ii][cMaterial]);
					Dialog_Show(playerid, VehicleDepoMaterial, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
					return 1;
				}
				if(amount < 1 || amount > pData[playerid][pMaterial])
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:", pvData[ii][cMaterial]);
					Dialog_Show(playerid, VehicleDepoMaterial, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
					return 1;
				}
				if(pvData[ii][cMaterial] > 2000) return Error(playerid, "Tidak bisa memasukan barang lagi");
				pvData[ii][cMaterial] += amount;
				pData[playerid][pMaterial] -= amount;
				Vehicle_OpenStorage(playerid, vehicleid);
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deposited %d into their trunk safe.", ReturnName(playerid), amount);
			}
		}    
	}
	else Dialog_Show(playerid, VehicleMaterial, DIALOG_STYLE_LIST, "Material Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
    return 1;
}

Dialog:VehicleComponent(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)
	{
		switch (listitem)
		{
			case 0: 
			{
				new str[128];
				format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:");
				Dialog_Show(playerid, VehWithCompo, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
			}
			case 1: 
			{
				new str[128];
				format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:");
				Dialog_Show(playerid, VehDepoCompo, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
			}
		}
	}
	else Vehicle_OpenStorage(playerid, vehicleid);
    return 1;
}

Dialog:VehWithCompo(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)
	{
		foreach(new ii : PVehicles)
		{
			if(pvData[ii][cVeh] == vehicleid)
			{
				new amount = strval(inputtext);

				if(isnull(inputtext))
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:", pvData[ii][cComponent]);
					Dialog_Show(playerid, VehWithCompo, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
					return 1;
				}
				if(amount < 1 || amount > pvData[ii][cComponent])
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:", pvData[ii][cComponent]);
					Dialog_Show(playerid, VehWithCompo, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
					return 1;
				}
				pvData[ii][cComponent] -= amount;
				pData[playerid][pComponent] += amount;

				Vehicle_OpenStorage(playerid, vehicleid);

				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has withdrawn %d from their trunk safe.", ReturnName(playerid), amount);
			}
		}    
	}
	else Dialog_Show(playerid, VehicleComponent, DIALOG_STYLE_LIST, "Component Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
    return 1;
}

Dialog:VehDepoCompo(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)
	{
		foreach(new ii : PVehicles)
		{
			if(pvData[ii][cVeh] == vehicleid)
			{
				new amount = strval(inputtext);

				if(isnull(inputtext))
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:", pvData[ii][cComponent]);
					Dialog_Show(playerid, VehDepoCompo, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
					return 1;
				}
				if(amount < 1 || amount > pData[playerid][pComponent])
				{
					new str[128];
					format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:", pvData[ii][cComponent]);
					Dialog_Show(playerid, VehDepoCompo, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
					return 1;
				}
				if(pvData[ii][cComponent] > 1000) return Error(playerid, "Tidak bisa memasukan barang lagi");
				pvData[ii][cComponent] += amount;
				pData[playerid][pComponent] -= amount;

				Vehicle_OpenStorage(playerid, vehicleid);
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deposited %d into their trunk safe.", ReturnName(playerid), amount);
			}
		}    
	}
	else Dialog_Show(playerid, VehicleComponent, DIALOG_STYLE_LIST, "Component Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
    return 1;
}
