
Dialog:BuyTruck(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				new modelid = 456;
				new tstr[128], price = GetVehicleCost(modelid);
				pData[playerid][pBuyPvModel] = modelid;
				format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
				Dialog_Show(playerid, BuyTruckConfirm, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
			}
			case 1:
			{
				new modelid = 414;
				new tstr[128], price = GetVehicleCost(modelid);
				pData[playerid][pBuyPvModel] = modelid;
				format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
				Dialog_Show(playerid, BuyTruckConfirm, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
			}
			case 2:
			{
				new modelid = 499;
				new tstr[128], price = GetVehicleCost(modelid);
				pData[playerid][pBuyPvModel] = modelid;
				format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
				Dialog_Show(playerid, BuyTruckConfirm, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
			}
			case 3:
			{
				new modelid = 455;
				new tstr[128], price = GetVehicleCost(modelid);
				pData[playerid][pBuyPvModel] = modelid;
				format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
				Dialog_Show(playerid, BuyTruckConfirm, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
			}
			case 4:
			{
				new modelid = 403;
				new tstr[128], price = GetVehicleCost(modelid);
				pData[playerid][pBuyPvModel] = modelid;
				format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
				Dialog_Show(playerid, BuyTruckConfirm, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
			}
			case 5:
			{
				new modelid = 514;
				new tstr[128], price = GetVehicleCost(modelid);
				pData[playerid][pBuyPvModel] = modelid;
				format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
				Dialog_Show(playerid, BuyTruckConfirm, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
			}
			case 6:
			{
				new modelid = 515;
				new tstr[128], price = GetVehicleCost(modelid);
				pData[playerid][pBuyPvModel] = modelid;
				format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
				Dialog_Show(playerid, BuyTruckConfirm, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
			}
		}
	}
    return 1;
}

Dialog:BuyTruckConfirm(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		new modelid = pData[playerid][pBuyPvModel];
		if(response)
		{
			if(modelid <= 0) return Error(playerid, "Invalid model id.");
			new cost = GetVehicleCost(modelid);
			
			if(pData[playerid][pMoney] < cost)
			{
				Error(playerid, "Uang anda tidak mencukupi.!");
				return 1;
			}
			// new count = 0, limit = LimitSlotPlayerVehicle(playerid);
			new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(playerid);			if(count >= limit)
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
			model = modelid;
			x = -72.1491;
			y = -1129.5632;
			z = 1.0781;
			a = 69.9099;
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			mysql_tquery(g_SQL, cQuery, "OnVehBuyPV", "ddddddffff", playerid, pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			return 1;
		}
		else
		{
			pData[playerid][pBuyPvModel] = 0;
		}
	}
    return 1;
}

Dialog:TruckMission(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				SetPlayerGPS(playerid, -366.3686,-1419.0941,25.7266); // 
			}
			case 1:
			{
				SetPlayerGPS(playerid, 335.0611, 896.4723, 21.2162);
			}
			case 2:
			{
				SetPlayerGPS(playerid, 2836.9445,-1539.5584,11.0991); //
			}
			case 3:
			{
				SetPlayerGPS(playerid, -1446.71, -1544.53, 102.25); //
			}
			case 4:
			{
				SetPlayerGPS(playerid, 2792.4355,-2456.1199,13.63255); //
			}
			case 5:
			{
				SetPlayerGPS(playerid, -759.54, 1640.60, 27.39); //
			}
			case 6:
			{
				SetPlayerGPS(playerid, -577.1335,-503.6530,25.5107);
			}
			case 7:
			{
				SetPlayerGPS(playerid, 797.7953,-616.8799,16.3359);
			}
		}
	}
    return 1;
}
