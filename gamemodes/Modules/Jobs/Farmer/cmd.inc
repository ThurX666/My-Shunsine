
CMD:buyseeds(playerid, params[])
{
	if(IsPlayerInRangeOfPoint(playerid, 2.5, -372.3396, -1427.8840, 25.7266))
	{
		if(pData[playerid][pJob] == 5 || pData[playerid][pJob2] == 5)
		{
			new choice[32], amount;
			if(sscanf(params, "s[32]d", choice, amount))
			{
				SendClientMessageEx(playerid, COLOR_WHITE, "KEGUNAAN: /buyseeds [wheat,onion,carrot,potato,corn] [amount]");
				return 1;
			}
			if(strcmp(choice, "wheat", true) == 0)
			{
				if(amount < 0) return Error(playerid, "Tidak bisa dibawah 0");
				if(amount > 100) return Error(playerid, "Tidak bisa diatas 100");
				if(GetPlayerMoney(playerid) >= amount*HargaAnggur)
				{
					if(pData[playerid][pSeedWheat] >= 100) return Error(playerid, "Maximal di inventory 100 bibit");
					pData[playerid][pSeedWheat] = amount;
					GivePlayerMoneyEx(playerid, -amount*HargaAnggur);
					SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}Anda telah membeli bibit wheat sebanyak %d dengan harga $%s", amount, FormatMoney(HargaAnggur));
				}
				else SendClientMessage(playerid, -1, "ERROR: Uang anda tidak cukup untuk membeli bibit sebanyak itu");
			}
			else if(strcmp(choice, "onion", true) == 0)
			{
				if(amount < 0) return Error(playerid, "Tidak bisa dibawah 0");
				if(amount > 100) return Error(playerid, "Tidak bisa diatas 100");
				if(GetPlayerMoney(playerid) >= amount*HargaBlueberry)
				{
					if(pData[playerid][pSeedOnion] >= 100) return Error(playerid, "Maximal di inventory 100 bibit");
					pData[playerid][pSeedOnion] = amount;
					GivePlayerMoneyEx(playerid, -amount*HargaBlueberry);
					SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}Anda telah membeli bibit onion sebanyak %d dengan harga $%s", amount, FormatMoney(HargaBlueberry));
				}
				else SendClientMessage(playerid, -1, "ERROR: Uang anda tidak cukup untuk membeli bibit sebanyak itu");
			}
			else if(strcmp(choice, "carrot", true) == 0)
			{
				if(amount < 0) return Error(playerid, "Tidak bisa dibawah 0");
				if(amount > 100) return Error(playerid, "Tidak bisa diatas 100");
				if(GetPlayerMoney(playerid) >= amount*HargaStrawberry)
				{
					if(pData[playerid][pSeedCarrot] >= 100) return Error(playerid, "Maximal di inventory 100 bibit");
					pData[playerid][pSeedCarrot] = amount;
					GivePlayerMoneyEx(playerid, -amount*HargaStrawberry);
					SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}Anda telah membeli bibit carrot sebanyak %d dengan harga $%s", amount, FormatMoney(HargaStrawberry));
				}
				else SendClientMessage(playerid, -1, "ERROR: Uang anda tidak cukup untuk membeli bibit sebanyak itu");
			}
			else if(strcmp(choice, "potato", true) == 0)
			{
				if(amount < 0) return Error(playerid, "Tidak bisa dibawah 0");
				if(amount > 100) return Error(playerid, "Tidak bisa diatas 100");
				if(GetPlayerMoney(playerid) >= amount*HargaGandum)
				{
					if(pData[playerid][pSeedPotato] >= 100) return Error(playerid, "Maximal di inventory 100 bibit");
					pData[playerid][pSeedPotato] = amount;
					GivePlayerMoneyEx(playerid, -amount*HargaGandum);
					SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}Anda telah membeli bibit potato sebanyak %d dengan harga $%s", amount, FormatMoney(HargaGandum));
				}
				else SendClientMessage(playerid, -1, "ERROR: Uang anda tidak cukup untuk membeli bibit sebanyak itu");
			}
			else if(strcmp(choice, "corn", true) == 0)
			{
				if(amount < 0) return Error(playerid, "Tidak bisa dibawah 0");
				if(amount > 100) return Error(playerid, "Tidak bisa diatas 100");
				if(GetPlayerMoney(playerid) >= amount*HargaTomat)
				{
					if(pData[playerid][pSeedCorn] >= 100) return Error(playerid, "Maximal di inventory 100 bibit");
					pData[playerid][pSeedCorn] = amount;
					GivePlayerMoneyEx(playerid, -amount*HargaTomat);
					SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}Anda telah membeli bibit corn sebanyak %d dengan harga $%s", amount, FormatMoney(HargaTomat));
				}
				else SendClientMessage(playerid, -1, "ERROR: Uang anda tidak cukup untuk membeli bibit sebanyak itu");
			}
			return 1;
		}
		else SendClientMessage(playerid, -1, "ERROR: Anda bukan seorang Farmer");
	}	
	return 1;
}

CMD:loadplant(playerid, params[])
{
	new choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		Usage(playerid, "/loadplant [wheat,onion,carrot,potato,corn]");
		return 1;
	}
    new Float: x, Float: y, Float: z;
    new vehicleid = GetPVarInt(playerid, "LastVehicleID");
    GetVehicleBoot(GetPVarInt(playerid, "LastVehicleID"), x, y, z);
    if(GetPlayerDistanceFromPoint(playerid, x, y, z) > 3.0) return Error(playerid, "Your last vehicle is too far away.");  
    if(Vehicle_WheatTotal(vehicleid) >= 2000) return Error(playerid, "You can no longer load plants onto this vehicle.");    
    if(Vehicle_OnionTotal(vehicleid) >= 2000) return Error(playerid, "You can no longer load plants onto this vehicle.");    
	if(Vehicle_CarrotTotal(vehicleid) >= 2000) return Error(playerid, "You can no longer load plants onto this vehicle.");    
    if(Vehicle_PotatoTotal(vehicleid) >= 2000) return Error(playerid, "You can no longer load plants onto this vehicle.");    
    if(Vehicle_CornTotal(vehicleid) >= 2000) return Error(playerid, "You can no longer load plants onto this vehicle.");  
	if(!IsAPickup(vehicleid)) return Error(playerid, "You have to use a pickup type car");
    if(strcmp(choice, "wheat", true) == 0)
	{
		if(pData[playerid][pWheat] > 0)
		{
			foreach(new pv : PVehicles)
			{
				if(vehicleid == pvData[pv][cVeh])
				{
					if(pvData[pv][cOnion] > 0 || pvData[pv][cCarrot] > 0 || pvData[pv][cPotato] > 0 || pvData[pv][cCorn] > 0) return Error(playerid, "Can't put plants, there are already other plants in the storage");
					pvData[pv][cWheat] += pData[playerid][pWheat];
					SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've loaded "YELLOW_E"%d "GREEN_E"Wheat "WHITE_E"into the pickup truck, amount stored: "YELLOW_E"%d", pData[playerid][pWheat], pvData[pv][cWheat]);
					pData[playerid][pWheat] = 0;
					if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]))
					{
						DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]);
					}

					if(GetVehicleModel(pvData[pv][cVeh]) == 422)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.382, 0.126, 90.599, 0.000, 0.000);
					}
					else if(GetVehicleModel(pvData[pv][cVeh]) == 478)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.537, 0.263, 88.999, 0.000, 0.000);
					}	
					else if(GetVehicleModel(pvData[pv][cVeh]) == 543)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.338, 0.298, 89.599, 0.000, 0.000);
					}
					else if(GetVehicleModel(pvData[pv][cVeh]) == 554)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.625, 0.209, 88.900, 0.000, 0.000);
					}
				}
			}
		}
		else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman wheat");
	}
	else if(strcmp(choice, "onion", true) == 0)
	{
		if(pData[playerid][pOnion] > 0)
		{
			foreach(new pv : PVehicles)
			{
				if(vehicleid == pvData[pv][cVeh])
				{
					if(pvData[pv][cWheat] > 0 || pvData[pv][cCorn] > 0 || pvData[pv][cCarrot] > 0 || pvData[pv][cPotato] > 0) return Error(playerid, "Can't put plants, there are already other plants in the storage");
					pvData[pv][cOnion] += pData[playerid][pOnion];
					SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've loaded "YELLOW_E"%d "GREEN_E"Onion "WHITE_E"into the pickup truck, amount stored: "YELLOW_E"%d", pData[playerid][pOnion], pvData[pv][cOnion]);
					pData[playerid][pOnion] = 0;
					if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]))
					{
						DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]);
					}

					if(GetVehicleModel(pvData[pv][cVeh]) == 422)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.382, 0.126, 90.599, 0.000, 0.000);
					}
					else if(GetVehicleModel(pvData[pv][cVeh]) == 478)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.537, 0.263, 88.999, 0.000, 0.000);
					}	
					else if(GetVehicleModel(pvData[pv][cVeh]) == 543)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.338, 0.298, 89.599, 0.000, 0.000);
					}
					else if(GetVehicleModel(pvData[pv][cVeh]) == 554)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.625, 0.209, 88.900, 0.000, 0.000);
					}
				}
			}
		}
		else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman onion");
	}
	else if(strcmp(choice, "carrot", true) == 0)
	{
		if(pData[playerid][pCarrot] > 0)
		{
			foreach(new pv : PVehicles)
			{
				if(vehicleid == pvData[pv][cVeh])
				{
					if(pvData[pv][cWheat] > 0 || pvData[pv][cOnion] > 0 || pvData[pv][cCorn] > 0 || pvData[pv][cPotato] > 0) return Error(playerid, "Can't put plants, there are already other plants in the storage");
					pvData[pv][cCarrot] += pData[playerid][pCarrot];
					SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've loaded "YELLOW_E"%d "GREEN_E"Carrot "WHITE_E"into the pickup truck, amount stored: "YELLOW_E"%d", pData[playerid][pCarrot], pvData[pv][cCarrot]);
					pData[playerid][pCarrot] = 0;
					if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]))
					{
						DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]);
					}

					if(GetVehicleModel(pvData[pv][cVeh]) == 422)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.382, 0.126, 90.599, 0.000, 0.000);
					}
					else if(GetVehicleModel(pvData[pv][cVeh]) == 478)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.537, 0.263, 88.999, 0.000, 0.000);
					}	
					else if(GetVehicleModel(pvData[pv][cVeh]) == 543)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.338, 0.298, 89.599, 0.000, 0.000);
					}
					else if(GetVehicleModel(pvData[pv][cVeh]) == 554)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.625, 0.209, 88.900, 0.000, 0.000);
					}
				}
			}
		}
		else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman carrot");
	}
	else if(strcmp(choice, "potato", true) == 0)
	{
		if(pData[playerid][pPotato] > 0)
		{
			foreach(new pv : PVehicles)
			{
				if(vehicleid == pvData[pv][cVeh])
				{
					if(pvData[pv][cWheat] > 0 || pvData[pv][cOnion] > 0 || pvData[pv][cCarrot] > 0 || pvData[pv][cCorn] > 0) return Error(playerid, "Can't put plants, there are already other plants in the storage");
					pvData[pv][cPotato] += pData[playerid][pPotato];
					SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've loaded "YELLOW_E"%d "GREEN_E"Potato "WHITE_E"into the pickup truck, amount stored: "YELLOW_E"%d", pData[playerid][pPotato], pvData[pv][cPotato]);
					pData[playerid][pPotato] = 0;
					if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]))
					{
						DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]);
					}

					if(GetVehicleModel(pvData[pv][cVeh]) == 422)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.382, 0.126, 90.599, 0.000, 0.000);
					}
					else if(GetVehicleModel(pvData[pv][cVeh]) == 478)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.537, 0.263, 88.999, 0.000, 0.000);
					}	
					else if(GetVehicleModel(pvData[pv][cVeh]) == 543)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.338, 0.298, 89.599, 0.000, 0.000);
					}
					else if(GetVehicleModel(pvData[pv][cVeh]) == 554)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.625, 0.209, 88.900, 0.000, 0.000);
					}
				}
			}
		}
		else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman potato");
	}
	else if(strcmp(choice, "corn", true) == 0)
	{
		if(pData[playerid][pCorn] > 0)
		{
			foreach(new pv : PVehicles)
			{
				if(vehicleid == pvData[pv][cVeh])
				{
					if(pvData[pv][cWheat] > 0 || pvData[pv][cOnion] > 0 || pvData[pv][cCarrot] > 0 || pvData[pv][cPotato] > 0) return Error(playerid, "Can't put plants, there are already other plants in the storage");
					pvData[pv][cCorn] += pData[playerid][pCorn];
					SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've loaded "YELLOW_E"%d "GREEN_E"Corn "WHITE_E"into the pickup truck, amount stored: "YELLOW_E"%d", pData[playerid][pCorn], pvData[pv][cCorn]);
					pData[playerid][pCorn] = 0;
					if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]))
					{
						DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]);
					}

					if(GetVehicleModel(pvData[pv][cVeh]) == 422)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.382, 0.126, 90.599, 0.000, 0.000);
					}
					else if(GetVehicleModel(pvData[pv][cVeh]) == 478)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.537, 0.263, 88.999, 0.000, 0.000);
					}	
					else if(GetVehicleModel(pvData[pv][cVeh]) == 543)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.338, 0.298, 89.599, 0.000, 0.000);
					}
					else if(GetVehicleModel(pvData[pv][cVeh]) == 554)
					{
						ObjectVehicle[pvData[pv][cVeh]][2] = CreateDynamicObject(1454,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][2], pvData[pv][cVeh], 0.000, -1.625, 0.209, 88.900, 0.000, 0.000);
					}
				}
			}
		}
		else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman corn");
	}
    return 1;
}

//PERINTAH FARMER
CMD:unloadplant(playerid, params[])
{
	if(IsPlayerInRangeOfPoint(playerid, 2.5, -372.3396, -1427.8840, 25.7266))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return Error(playerid, "You are not driver in pickup truck.");
		if(!IsValidVehicle(vehicleid)) return Error(playerid, "You're not in any vehicle.");
		if(IsPlayerInRangeOfPoint(playerid, 2.5, -372.3396, -1427.8840, 25.7266))
		{
			new choice[32];
			if(sscanf(params, "s[32]", choice))
			{
				Usage(playerid, "/unloadplant [wheat,onion,carrot,potato,corn]");
				return 1;
			}
			if(strcmp(choice, "wheat", true) == 0)
			{
				foreach(new pv : PVehicles)
				{
					if(vehicleid == pvData[pv][cVeh])
					{
						if(pvData[pv][cWheat] > 0)
						{
							new mstr[128];			
							format(mstr, sizeof(mstr), "Plant Type: Wheat\nPrice: $0.%s\nAmmount: %d units\nTotal Price: $%s", FormatMoney(HargaAnggur), pvData[pv][cWheat], FormatMoney(pvData[pv][cWheat]*HargaAnggur));
							Dialog_Show(playerid, DialogSellPlant, DIALOG_STYLE_MSGBOX, "Selling plant", mstr, "Sell", "Cancel");
						}
						else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman wheat");
					}
				}
			}
			else if(strcmp(choice, "onion", true) == 0)
			{
				foreach(new pv : PVehicles)
				{
					if(vehicleid == pvData[pv][cVeh])
					{
						if(pvData[pv][cOnion] > 0)
						{
							new mstr[128];			
							format(mstr, sizeof(mstr), "Plant Type: Onion\nPrice: $0.%s\nAmmount: %d units\nTotal Price: $%s", FormatMoney(HargaBlueberry), pvData[pv][cOnion], FormatMoney(pvData[pv][cOnion]*HargaBlueberry));
							Dialog_Show(playerid, DialogSellPlant, DIALOG_STYLE_MSGBOX, "Selling plant", mstr, "Sell", "Cancel");
						}
						else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman onion");
					}
				}
			}
			else if(strcmp(choice, "carrot", true) == 0)
			{
				foreach(new pv : PVehicles)
				{
					if(vehicleid == pvData[pv][cVeh])
					{
						if(pvData[pv][cCarrot] > 0)
						{
							new mstr[128];			
							format(mstr, sizeof(mstr), "Plant Type: Carrot\nPrice: $0.%s\nAmmount: %d units\nTotal Price: $%s", FormatMoney(HargaStrawberry), pvData[pv][cCarrot], FormatMoney(pvData[pv][cCarrot]*HargaStrawberry));
							Dialog_Show(playerid, DialogSellPlant, DIALOG_STYLE_MSGBOX, "Selling plant", mstr, "Sell", "Cancel");
						}
						else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman carrot");
					}
				}
			}
			else if(strcmp(choice, "potato", true) == 0)
			{
				foreach(new pv : PVehicles)
				{
					if(vehicleid == pvData[pv][cVeh])
					{
						if(pvData[pv][cPotato] > 0)
						{
							new mstr[128];			
							format(mstr, sizeof(mstr), "Plant Type: Potato\nPrice: $0.%s\nAmmount: %d units\nTotal Price: $%s", FormatMoney(HargaGandum), pvData[pv][cPotato], FormatMoney(pvData[pv][cPotato]*HargaGandum));
							Dialog_Show(playerid, DialogSellPlant, DIALOG_STYLE_MSGBOX, "Selling plant", mstr, "Sell", "Cancel");
						}
						else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman potato");
					}
				}
			}
			else if(strcmp(choice, "corn", true) == 0)
			{
				foreach(new pv : PVehicles)
				{
					if(vehicleid == pvData[pv][cVeh])
					{
						if(pvData[pv][cCorn] > 0)
						{
							new mstr[128];			
							format(mstr, sizeof(mstr), "Plant Type: Corn\nPrice: $0.%s\nAmmount: %d units\nTotal Price: $%s", FormatMoney(HargaTomat), pvData[pv][cCorn], FormatMoney(pvData[pv][cCorn]*HargaTomat));
							Dialog_Show(playerid, DialogSellPlant, DIALOG_STYLE_MSGBOX, "Selling plant", mstr, "Sell", "Cancel");
						}
						else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman corn");
					}
				}
			}
		}	
	}	
	return 1;
}

//PERINTAH FARMER
CMD:sellberries(playerid, params[])
{
	if(IsPlayerInRangeOfPoint(playerid, 2.5, -372.3396, -1427.8840, 25.7266)) {
		if(pData[playerid][pBushForager] < 0) return Error(playerid, "Kamu tidak mempunyai berries yang bisa dijual");
		Dialog_Show(playerid, SellingBush, DIALOG_STYLE_MSGBOX, "Selling Berries", sprintf("Plant Type: Berries\nPrice: "GREEN_E"$1.00\n"WHITE_E"Amount: "YELLOW_E"%d units\n"WHITE_E"Total Price: "GREEN_E"$%s",pData[playerid][pBushForager], FormatMoney(pData[playerid][pBushForager]*100)), "Sell", "Cancel");
	}
	return 1;
}

CMD:sellallplant(playerid, params[])
{
	if(IsPlayerInRangeOfPoint(playerid, 2.5, -372.3396, -1427.8840, 25.7266))
	{
		new choice[32];
		if(sscanf(params, "s[32]", choice))
		{
			Usage(playerid, "/sellallplant [wheat,onion,carrot,potato,corn]");
			return 1;
		}
		if(strcmp(choice, "wheat", true) == 0)
		{
			if(pData[playerid][pWheat] > 0)
			{
				new mstr[128];			
				format(mstr, sizeof(mstr), "Plant Type: Wheat\nPrice: $0.%s\nAmmount: %d units\nTotal Price: $%s", FormatMoney(HargaAnggur), pData[playerid][pWheat], FormatMoney(pData[playerid][pWheat]*HargaAnggur));
				Dialog_Show(playerid, DialogSellPlant, DIALOG_STYLE_MSGBOX, "Selling plant", mstr, "Sell", "Cancel");
			}
			else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman wheat");
		}
		else if(strcmp(choice, "onion", true) == 0)
		{
			if(pData[playerid][pOnion] > 0)
			{
				new mstr[128];			
				format(mstr, sizeof(mstr), "Plant Type: Onion\nPrice: $0.%s\nAmmount: %d units\nTotal Price: $%s", FormatMoney(HargaBlueberry), pData[playerid][pOnion], FormatMoney(pData[playerid][pOnion]*HargaBlueberry));
				Dialog_Show(playerid, DialogSellPlant, DIALOG_STYLE_MSGBOX, "Selling plant", mstr, "Sell", "Cancel");
			}
			else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman onion");
		}
		else if(strcmp(choice, "carrot", true) == 0)
		{
			if(pData[playerid][pCarrot] > 0)
			{
				new mstr[128];			
				format(mstr, sizeof(mstr), "Plant Type: Carrot\nPrice: $0.%s\nAmmount: %d units\nTotal Price: $%s", FormatMoney(HargaStrawberry), pData[playerid][pCarrot], FormatMoney(pData[playerid][pCarrot]*HargaStrawberry));
				Dialog_Show(playerid, DialogSellPlant, DIALOG_STYLE_MSGBOX, "Selling plant", mstr, "Sell", "Cancel");
			}
			else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman carrot");
		}
		else if(strcmp(choice, "potato", true) == 0)
		{
			if(pData[playerid][pPotato] > 0)
			{
				new mstr[128];			
				format(mstr, sizeof(mstr), "Plant Type: Potato\nPrice: $0.%s\nAmmount: %d units\nTotal Price: $%s", FormatMoney(HargaGandum), pData[playerid][pPotato], FormatMoney(pData[playerid][pPotato]*HargaGandum));
				Dialog_Show(playerid, DialogSellPlant, DIALOG_STYLE_MSGBOX, "Selling plant", mstr, "Sell", "Cancel");
			}
			else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman potato");
		}
		else if(strcmp(choice, "corn", true) == 0)
		{
			if(pData[playerid][pCorn] > 0)
			{
				new mstr[128];			
				format(mstr, sizeof(mstr), "Plant Type: Corn\nPrice: $0.%s\nAmmount: %d units\nTotal Price: $%s", FormatMoney(HargaTomat), pData[playerid][pCorn], FormatMoney(pData[playerid][pCorn]*HargaTomat));
				Dialog_Show(playerid, DialogSellPlant, DIALOG_STYLE_MSGBOX, "Selling plant", mstr, "Sell", "Cancel");
			}
			else SendClientMessage(playerid, -1, "ERROR: Anda tidak memiliki tanaman corn");
		}
	}	
	return 1;
}

CMD:plant(playerid, params[])
{
	if(isnull(params)) return Usage(playerid, "/plant [plant/harvest/destroy]");
	if(!strcmp(params, "plant", true))
	{
		if(pData[playerid][pJob] == 5 || pData[playerid][pJob2] == 5)
		{
			if(GetPlayerInterior(playerid) > 0) return Error(playerid, "You cant plant at here!");
			if(GetPlayerVirtualWorld(playerid) > 0) return Error(playerid, "You cant plant at here!");

			new mstr[512], tstr[64];
			format(tstr, sizeof(tstr), "Planting Seed");
			format(mstr, sizeof(mstr), "Seed Name\tAmmount\n\
			"WHITE_E"Wheat\t"GREEN_E"%d units\n\
			"WHITE_E"Onion\t"GREEN_E"%d units\n\
			"WHITE_E"Carrot\t"GREEN_E"%d units\n\
			"WHITE_E"Potato\t"GREEN_E"%d units\n\
			"WHITE_E"Corn\t"GREEN_E"%d units", pData[playerid][pSeedWheat], pData[playerid][pSeedOnion], pData[playerid][pSeedCarrot], pData[playerid][pSeedPotato], pData[playerid][pSeedCorn]);
			Dialog_Show(playerid, DialogPlant, DIALOG_STYLE_TABLIST_HEADERS, tstr, mstr, "Plant", "Cancel");
		}
		else return SendClientMessageEx(playerid, COLOR_ARWIN, "FARMER: "WHITE_E"You are not farmer!");
	}
	else if(!strcmp(params, "harvest", true))
	{
		if(pData[playerid][pJob] == 5 || pData[playerid][pJob2] == 5)
		{
			new id = GetClosestPlant(playerid);
			if(id == -1) return SendClientMessageEx(playerid, COLOR_ARWIN, "FARMER: "WHITE_E"You must closes on the plant!");
			if(PlantData[id][PlantTime] > 1) return SendClientMessageEx(playerid, COLOR_ARWIN, "FARMER: "WHITE_E"This plant is not ready!");
			if(PlantData[id][PlantHarvest] == true) return SendClientMessageEx(playerid, COLOR_ARWIN, "FARMER: "WHITE_E"This plant already harvesting by someone!");

			if(pData[playerid][pSkillFarmer] == 1)
			{
				if(pData[playerid][pWheat] >= 150) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pOnion] >= 150) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pCarrot] >= 150) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pPotato] >= 150) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pCorn] >= 150) return Error(playerid, "Your inventory is full"); 
			}
			if(pData[playerid][pSkillFarmer] == 2)
			{
				if(pData[playerid][pWheat] >= 200) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pOnion] >= 200) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pCarrot] >= 200) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pPotato] >= 200) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pCorn] >= 200) return Error(playerid, "Your inventory is full"); 
			}
			if(pData[playerid][pSkillFarmer] == 3)
			{
				if(pData[playerid][pWheat] >= 250) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pOnion] >= 250) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pCarrot] >= 250) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pPotato] >= 250) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pCorn] >= 250) return Error(playerid, "Your inventory is full"); 
			}
			if(pData[playerid][pSkillFarmer] == 4)
			{
				if(pData[playerid][pWheat] >= 300) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pOnion] >= 300) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pCarrot] >= 300) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pPotato] >= 300) return Error(playerid, "Your inventory is full"); 
				if(pData[playerid][pCorn] >= 300) return Error(playerid, "Your inventory is full"); 
			}
			pData[playerid][pHarvestID] = id;
			SetPlayerEnergy(playerid, pData[playerid][pEnergy]-1.0);
			pData[playerid][pHarvest] = SetTimerEx("HarvestPlant", 1000, true, "i", playerid);
			PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Harvesting");
			for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
			SetPlayerArmedWeapon(playerid, WEAPON_KNIFE);
			ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);

			PlantData[id][PlantHarvest] = true;
		}
		else return SendClientMessageEx(playerid, COLOR_ARWIN, "FARMER: "WHITE_E"You are not farmer!");
	}
	else if(!strcmp(params, "destroy", true))
	{
		if(pData[playerid][pFaction] == 1 || pData[playerid][pFaction] == 2)
		{
			new id = GetClosestPlant(playerid);
			if(id == -1) return SendClientMessageEx(playerid, COLOR_ARWIN, "FARMER: "WHITE_E"You must closes on the plant!");
			if(PlantData[id][PlantHarvest] == true) return SendClientMessageEx(playerid, COLOR_ARWIN, "FARMER: "WHITE_E"This plant already harvesting by someone!");

			new query[128];
			PlantData[id][PlantType] = 0;
			PlantData[id][PlantTime] = 0;
			PlantData[id][PlantX] = 0.0;
			PlantData[id][PlantY] = 0.0;
			PlantData[id][PlantZ] = 0.0;
			PlantData[id][PlantHarvest] = false;
			KillTimer(PlantData[id][PlantTimer]);
			PlantData[id][PlantTimer] = -1;
			DestroyDynamicObject(PlantData[id][PlantObjID]);
			DestroyDynamicCP(PlantData[id][PlantCP]);
			DestroyDynamic3DTextLabel(PlantData[id][PlantLabel]);
			mysql_format(g_SQL, query, sizeof(query), "DELETE FROM plants WHERE id='%d'", id);
			mysql_query(g_SQL, query);
			Iter_SafeRemove(Plants, id, id);
			ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
			Info(playerid, "You has destroyed this plant!");
		}
		else return SendClientMessageEx(playerid, COLOR_ARWIN, "FARMER: "WHITE_E"You cant destroy a plant!");
	}
	return 1;
}
