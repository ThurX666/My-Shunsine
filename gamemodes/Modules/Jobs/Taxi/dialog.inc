
Dialog:BuyTaxi(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				new modelid = 420;
				new tstr[128], price = GetVehicleCost(modelid);
				pData[playerid][pBuyPvModel] = modelid;
				format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
				Dialog_Show(playerid, BuyTaxiConfirm, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
			}
			case 1:
			{
				new modelid = 438;
				new tstr[128], price = GetVehicleCost(modelid);
				pData[playerid][pBuyPvModel] = modelid;
				format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
				Dialog_Show(playerid, BuyTaxiConfirm, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
			}
		}
	}
    return 1;
}

Dialog:BuyTaxiConfirm(playerid, response, listitem, inputtext[]) {
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
			new count = 0, limit = LimitSlotPlayerVehicle(playerid);
			foreach(new ii : PVehicles)
			{
				if(pvData[ii][cOwner] == pData[playerid][pID] && pvData[ii][cClaim] != 1)
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
			model = modelid; //1700.5409,-1476.8165,13.3893,91.6928
			x = 1700.5409;
			y = -1476.8165;
			z = 13.3893;
			a = 91.6928;
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
