
Dialog:RentVehicleBoat(playerid, response, listitem, inputtext[]) {
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new modelid = 473;
                new tstr[128];
                pData[playerid][pBuyPvModel] = modelid;
                format(tstr, sizeof(tstr), ""WHITE_E"Anda akan menyewa kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$75.00 / hours", GetVehicleModelName(modelid));
                Dialog_Show(playerid, RentVehicleConfirm, DIALOG_STYLE_MSGBOX, "Rental Vehicles", tstr, "Rental", "Batal");
                
            }
            case 1:
            {
                new modelid = 453;
                new tstr[128];
                pData[playerid][pBuyPvModel] = modelid;
                format(tstr, sizeof(tstr), ""WHITE_E"Anda akan menyewa kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$50.00 / hours", GetVehicleModelName(modelid));
                Dialog_Show(playerid, RentVehicleConfirm, DIALOG_STYLE_MSGBOX, "Rental Vehicles", tstr, "Rental", "Batal");
            }
        }
    }
    return 1;
}

Dialog:RentVehicleJobs(playerid, response, listitem, inputtext[]) {
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new modelid = 438;
                new tstr[128];
                pData[playerid][pBuyPvModel] = modelid;
                format(tstr, sizeof(tstr), ""WHITE_E"Anda akan menyewa kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$75.00 / hours", GetVehicleModelName(modelid));
                Dialog_Show(playerid, RentVehicleConfirm, DIALOG_STYLE_MSGBOX, "Rental Vehicles", tstr, "Rental", "Batal");
            }
            case 1:
            {
                new modelid = 420;
                new tstr[128];
                pData[playerid][pBuyPvModel] = modelid;
                format(tstr, sizeof(tstr), ""WHITE_E"Anda akan menyewa kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$50.00 / hours", GetVehicleModelName(modelid));
                Dialog_Show(playerid, RentVehicleConfirm, DIALOG_STYLE_MSGBOX, "Rental Vehicles", tstr, "Rental", "Batal");
            }
            case 2:
            {
                new modelid = 422;
                new tstr[128];
                pData[playerid][pBuyPvModel] = modelid;
                format(tstr, sizeof(tstr), ""WHITE_E"Anda akan menyewa kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$50.00 / hours", GetVehicleModelName(modelid));
                Dialog_Show(playerid, RentVehicleConfirm, DIALOG_STYLE_MSGBOX, "Rental Vehicles", tstr, "Rental", "Batal");
            }
            case 3:
            {
                new modelid = 543;
                new tstr[128];
                pData[playerid][pBuyPvModel] = modelid;
                format(tstr, sizeof(tstr), ""WHITE_E"Anda akan menyewa kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$50.00 / hours", GetVehicleModelName(modelid));
                Dialog_Show(playerid, RentVehicleConfirm, DIALOG_STYLE_MSGBOX, "Rental Vehicles", tstr, "Rental", "Batal");
            }
            case 4:
            {
                new modelid = 499;
                new tstr[128];
                pData[playerid][pBuyPvModel] = modelid;
                format(tstr, sizeof(tstr), ""WHITE_E"Anda akan menyewa kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$50.00 / hours", GetVehicleModelName(modelid));
                Dialog_Show(playerid, RentVehicleConfirm, DIALOG_STYLE_MSGBOX, "Rental Vehicles", tstr, "Rental", "Batal");
            }
        }
    }
    return 1;
}

Dialog:RentVehicle(playerid, response, listitem, inputtext[]) {
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new modelid = 462;
                new tstr[128];
                pData[playerid][pBuyPvModel] = modelid;
                format(tstr, sizeof(tstr), ""WHITE_E"Anda akan menyewa kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$25.00 / hours", GetVehicleModelName(modelid));
                Dialog_Show(playerid, RentVehicleConfirm, DIALOG_STYLE_MSGBOX, "Rental Vehicles", tstr, "Rental", "Batal");
            }
            case 1:
            {
                new modelid = 586;
                new tstr[128];
                pData[playerid][pBuyPvModel] = modelid;
                format(tstr, sizeof(tstr), ""WHITE_E"Anda akan menyewa kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$50.00 / hours", GetVehicleModelName(modelid));
                Dialog_Show(playerid, RentVehicleConfirm, DIALOG_STYLE_MSGBOX, "Rental Vehicles", tstr, "Rental", "Batal");
            }
            case 2:
            {
                new modelid = 509;
                new tstr[128];
                pData[playerid][pBuyPvModel] = modelid;
                format(tstr, sizeof(tstr), ""WHITE_E"Anda akan menyewa kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$75.00 / hours", GetVehicleModelName(modelid));
                Dialog_Show(playerid, RentVehicleConfirm, DIALOG_STYLE_MSGBOX, "Rental Vehicles", tstr, "Rental", "Batal");
            }
        }
    }
    return 1;
}

Dialog:RentVehicleConfirm(playerid, response, listitem, inputtext[]) {
    if(response)
    {
        new modelid = pData[playerid][pBuyPvModel];
		new id = pData[playerid][pRentData];
		if(response)
		{
			if(rentData[id][rRX] != 0.0)
	    	{
				if(modelid <= 0) return Error(playerid, "Invalid model id.");
				new cost = 0;
				if(modelid == 462)
				{
					cost = 2500;
				}
				else if(modelid == 586)
				{
					cost = 5000;
				}
				else if(modelid == 509)
				{
					cost = 7500;
				}
				else if(modelid == 481)
				{
					cost = 5000;
				}
				else if(modelid == 566)
				{
					cost = 7500;
				}
				else if(modelid == 445)
				{
					cost = 6000;
				}
				else if(modelid == 483)
				{
					cost = 5000;
				}
				else if(modelid == 420)
				{
					cost = 7500;
				}
				else if(modelid == 422)
				{
					cost = 7000;
				}
				else if(modelid == 543)
				{
					cost = 7000;
				}
				else if(modelid == 499)
				{
					cost = 7500;
				}
				else if(modelid == 473)
				{
					cost = 4500;
				}
				else if(modelid == 453)
				{
					cost = 5000;
				}
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
				GivePlayerMoneyEx(playerid, -cost);
				new cQuery[1024];
				new Float:x,Float:y,Float:z, Float:a;
				new model, color1, color2, rental;
				color1 = 0;
				color2 = 0;
				model = modelid;
				x = rentData[id][rRX];
				y = rentData[id][rRY];
				z = rentData[id][rRZ];
				a = rentData[id][rRA];
				rental = gettime() + (1 * 86400);
				mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`, `rental`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f', '%d')", pData[playerid][pID], model, color1, color2, cost, x, y, z, a, rental);
				mysql_tquery(g_SQL, cQuery, "OnVehRentPV", "ddddddffffd", playerid, pData[playerid][pID], model, color1, color2, cost, x, y, z, a, rental);
				return 1;
			}
			else return Error(playerid, "Titik spawn belum di buat");	
		}
		else
		{
			pData[playerid][pBuyPvModel] = 0;
		}
    }
    return 1;
}
