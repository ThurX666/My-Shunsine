
Dialog:DialogPlant(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(pData[playerid][pSeedWheat] < 1) return Error(playerid, "Not enough seed!");
                new pid = GetNearPlant(playerid);
                if(pid != -1) return Error(playerid, "You too closes with other plant!");
                
                new id = Iter_Free(Plants);
                if(id == -1) return Error(playerid, "Cant plant any more plant!");
                
                //if(pData[playerid][pPlantTime] > 0) return Error(playerid, "You must wait 10 minutes for plant again!");
                new laid = pData[playerid][pLadang];
                if(IsPlayerInDynamicArea(playerid, FarmArea[0]) || IsPlayerInDynamicArea(playerid, FarmArea[3])
                || IsPlayerInDynamicArea(playerid, FarmArea[1]) || IsPlayerInDynamicArea(playerid, FarmArea[4])
                || IsPlayerInDynamicArea(playerid, FarmArea[2]) || IsPlayerInDynamicArea(playerid, FarmArea[5])
                || IsPlayerInRangeOfPoint(playerid, 80, laData[laid][laExtTanemX], laData[laid][laExtTanemY], laData[laid][laExtTanemZ]))
                {
                
                    pData[playerid][pSeedWheat] -= 1;
                    new Float:x, Float:y, Float:z, query[512];
                    GetPlayerPos(playerid, x, y, z);
                    
                    PlantData[id][PlantType] = 1;
                    PlantData[id][PlantTime] = 900;
                    PlantData[id][PlantX] = x;
                    PlantData[id][PlantY] = y;
                    PlantData[id][PlantZ] = z;
                    PlantData[id][PlantHarvest] = false;
                    PlantData[id][PlantTimer] = SetTimerEx("PlantGrowup", 1000, true, "i", id);
                    Iter_Add(Plants, id);
                    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO plants SET id='%d', type='%d', time='%d', posx='%f', posy='%f', posz='%f'", id, PlantData[id][PlantType], PlantData[id][PlantTime], x, y, z);
                    mysql_tquery(g_SQL, query, "OnPlantCreated", "di", playerid, id);
                    pData[playerid][pPlant]++;
                }
                else return Error(playerid, "Kamu harus berada di flint area atau ladang pribadi kamu");
            }
            case 1:
            {
                if(pData[playerid][pSeedOnion] < 1) return Error(playerid, "Not enough seed!");
                new pid = GetNearPlant(playerid);
                if(pid != -1) return Error(playerid, "You too closes with other plant!");
                
                new id = Iter_Free(Plants);
                if(id == -1) return Error(playerid, "Cant plant any more plant!");
                
                //if(pData[playerid][pPlantTime] > 0) return Error(playerid, "You must wait 10 minutes for plant again!");
                new laid = pData[playerid][pLadang];
                if(IsPlayerInDynamicArea(playerid, FarmArea[0]) || IsPlayerInDynamicArea(playerid, FarmArea[3])
                || IsPlayerInDynamicArea(playerid, FarmArea[1]) || IsPlayerInDynamicArea(playerid, FarmArea[4])
                || IsPlayerInDynamicArea(playerid, FarmArea[2]) || IsPlayerInDynamicArea(playerid, FarmArea[5])
                || IsPlayerInRangeOfPoint(playerid, 80, laData[laid][laExtTanemX], laData[laid][laExtTanemY], laData[laid][laExtTanemZ]))
                {
                
                    pData[playerid][pSeedOnion] -= 1;
                    new Float:x, Float:y, Float:z, query[512];
                    GetPlayerPos(playerid, x, y, z);
                    
                    PlantData[id][PlantType] = 2;
                    PlantData[id][PlantTime] = 900;
                    PlantData[id][PlantX] = x;
                    PlantData[id][PlantY] = y;
                    PlantData[id][PlantZ] = z;
                    PlantData[id][PlantHarvest] = false;
                    PlantData[id][PlantTimer] = SetTimerEx("PlantGrowup", 1000, true, "i", id);
                    Iter_Add(Plants, id);
                    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO plants SET id='%d', type='%d', time='%d', posx='%f', posy='%f', posz='%f'", id, PlantData[id][PlantType], PlantData[id][PlantTime], x, y, z);
                    mysql_tquery(g_SQL, query, "OnPlantCreated", "di", playerid, id);
                    pData[playerid][pPlant]++;
                }
                else return Error(playerid, "Kamu harus berada di flint area atau ladang pribadi kamu");
            }
            case 2:
            {
                if(pData[playerid][pSeedCarrot] < 1) return Error(playerid, "Not enough seed!");
                new pid = GetNearPlant(playerid);
                if(pid != -1) return Error(playerid, "You too closes with other plant!");
                
                new id = Iter_Free(Plants);
                if(id == -1) return Error(playerid, "Cant plant any more plant!");
                
                //if(pData[playerid][pPlantTime] > 0) return Error(playerid, "You must wait 10 minutes for plant again!");
                new laid = pData[playerid][pLadang];
                if(IsPlayerInDynamicArea(playerid, FarmArea[0]) || IsPlayerInDynamicArea(playerid, FarmArea[3])
                || IsPlayerInDynamicArea(playerid, FarmArea[1]) || IsPlayerInDynamicArea(playerid, FarmArea[4])
                || IsPlayerInDynamicArea(playerid, FarmArea[2]) || IsPlayerInDynamicArea(playerid, FarmArea[5])
                || IsPlayerInRangeOfPoint(playerid, 80, laData[laid][laExtTanemX], laData[laid][laExtTanemY], laData[laid][laExtTanemZ]))
                {
                
                    pData[playerid][pSeedCarrot] -= 1;
                    new Float:x, Float:y, Float:z, query[512];
                    GetPlayerPos(playerid, x, y, z);
                    
                    PlantData[id][PlantType] = 3;
                    PlantData[id][PlantTime] = 900;
                    PlantData[id][PlantX] = x;
                    PlantData[id][PlantY] = y;
                    PlantData[id][PlantZ] = z;
                    PlantData[id][PlantHarvest] = false;
                    PlantData[id][PlantTimer] = SetTimerEx("PlantGrowup", 1000, true, "i", id);
                    Iter_Add(Plants, id);
                    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO plants SET id='%d', type='%d', time='%d', posx='%f', posy='%f', posz='%f'", id, PlantData[id][PlantType], PlantData[id][PlantTime], x, y, z);
                    mysql_tquery(g_SQL, query, "OnPlantCreated", "di", playerid, id);
                    pData[playerid][pPlant]++;
                }
                else return Error(playerid, "Kamu harus berada di flint area atau ladang pribadi kamu");
            }
            case 3:
            {
                if(pData[playerid][pSeedPotato] < 1) return Error(playerid, "Not enough seed!");
                new pid = GetNearPlant(playerid);
                if(pid != -1) return Error(playerid, "You too closes with other plant!");
                
                new id = Iter_Free(Plants);
                if(id == -1) return Error(playerid, "Cant plant any more plant!");
                
                //if(pData[playerid][pPlantTime] > 0) return Error(playerid, "You must wait 10 minutes for plant again!");
                new laid = pData[playerid][pLadang];
                if(IsPlayerInDynamicArea(playerid, FarmArea[0]) || IsPlayerInDynamicArea(playerid, FarmArea[3])
                || IsPlayerInDynamicArea(playerid, FarmArea[1]) || IsPlayerInDynamicArea(playerid, FarmArea[4])
                || IsPlayerInDynamicArea(playerid, FarmArea[2]) || IsPlayerInDynamicArea(playerid, FarmArea[5])
                || IsPlayerInRangeOfPoint(playerid, 80, laData[laid][laExtTanemX], laData[laid][laExtTanemY], laData[laid][laExtTanemZ]))
                {
                
                    pData[playerid][pSeedPotato] -= 1;
                    new Float:x, Float:y, Float:z, query[512];
                    GetPlayerPos(playerid, x, y, z);
                    
                    PlantData[id][PlantType] = 4;
                    PlantData[id][PlantTime] = 900;
                    PlantData[id][PlantX] = x;
                    PlantData[id][PlantY] = y;
                    PlantData[id][PlantZ] = z;
                    PlantData[id][PlantHarvest] = false;
                    PlantData[id][PlantTimer] = SetTimerEx("PlantGrowup", 1000, true, "i", id);
                    Iter_Add(Plants, id);
                    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO plants SET id='%d', type='%d', time='%d', posx='%f', posy='%f', posz='%f'", id, PlantData[id][PlantType], PlantData[id][PlantTime], x, y, z);
                    mysql_tquery(g_SQL, query, "OnPlantCreated", "di", playerid, id);
                    pData[playerid][pPlant]++;
                }
                else return Error(playerid, "Kamu harus berada di flint area atau ladang pribadi kamu");
            }
            case 4:
            {
                if(pData[playerid][pSeedCorn] < 1) return Error(playerid, "Not enough seed!");
                new pid = GetNearPlant(playerid);
                if(pid != -1) return Error(playerid, "You too closes with other plant!");
                
                new id = Iter_Free(Plants);
                if(id == -1) return Error(playerid, "Cant plant any more plant!");
                
                //if(pData[playerid][pPlantTime] > 0) return Error(playerid, "You must wait 10 minutes for plant again!");
                new laid = pData[playerid][pLadang];
                if(IsPlayerInDynamicArea(playerid, FarmArea[0]) || IsPlayerInDynamicArea(playerid, FarmArea[3])
                || IsPlayerInDynamicArea(playerid, FarmArea[1]) || IsPlayerInDynamicArea(playerid, FarmArea[4])
                || IsPlayerInDynamicArea(playerid, FarmArea[2]) || IsPlayerInDynamicArea(playerid, FarmArea[5])
                || IsPlayerInRangeOfPoint(playerid, 80, laData[laid][laExtTanemX], laData[laid][laExtTanemY], laData[laid][laExtTanemZ]))
                {
                
                    pData[playerid][pSeedCorn] -= 1;
                    new Float:x, Float:y, Float:z, query[512];
                    GetPlayerPos(playerid, x, y, z);
                    
                    PlantData[id][PlantType] = 5;
                    PlantData[id][PlantTime] = 900;
                    PlantData[id][PlantX] = x;
                    PlantData[id][PlantY] = y;
                    PlantData[id][PlantZ] = z;
                    PlantData[id][PlantHarvest] = false;
                    PlantData[id][PlantTimer] = SetTimerEx("PlantGrowup", 1000, true, "i", id);
                    Iter_Add(Plants, id);
                    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO plants SET id='%d', type='%d', time='%d', posx='%f', posy='%f', posz='%f'", id, PlantData[id][PlantType], PlantData[id][PlantTime], x, y, z);
                    mysql_tquery(g_SQL, query, "OnPlantCreated", "di", playerid, id);
                    pData[playerid][pPlant]++;
                }
                else return Error(playerid, "Kamu harus berada di flint area atau ladang pribadi kamu");
            }
        }
    }
    return 1;
}

Dialog:DialogSellPlant(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			if(!IsValidVehicle(vehicleid)) return Error(playerid, "You're not in any vehicle.");
			foreach(new pv : PVehicles)
			{
				if(vehicleid == pvData[pv][cVeh])
				{
					if(pvData[pv][cWheat] > 0)
					{
						StockCratePlant += pvData[pv][cWheat]/150;
						new cash = pvData[pv][cWheat]*HargaAnggur;
						new list[212];
						format(list, sizeof(list), "Sold %d units of wheat", pvData[pv][cWheat]);
						AddPlayerSalary(playerid, "Farmer Storage Co", list, cash);
						SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've sold "YELLOW_E"%d "WHITE_E"units of "YELLOW_E"Wheat "WHITE_E"for "GREEN_E"$%s", pvData[pv][cWheat], FormatMoney(cash));
						pvData[pv][cWheat] = 0;
						if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]))
						{
							DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]);
						}
						TextDrawHideForPlayer(playerid, PlayerCrateTD);
                        PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
                        PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);
						ammountsellwheat++;
					}
					else if(pvData[pv][cOnion] > 0)
					{
						StockCratePlant += pvData[pv][cOnion]/150;
						new cash = pvData[pv][cOnion] * HargaBlueberry;
						new list[212];
						format(list, sizeof(list), "Sold %d units of wheat", pvData[pv][cOnion]);
						AddPlayerSalary(playerid, "Farmer Storage Co", list, cash);
						SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've sold "YELLOW_E"%d "WHITE_E"units of "YELLOW_E"Onion "WHITE_E"for "GREEN_E"$%s", pvData[pv][cOnion], FormatMoney(cash));
						pvData[pv][cOnion] = 0;
						if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]))
						{
							DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]);
						}
						TextDrawHideForPlayer(playerid, PlayerCrateTD);
                        PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
                        PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);
						ammountsellonion++;
					}
					else if(pvData[pv][cCarrot] > 0)
					{
						StockCratePlant += pvData[pv][cCarrot]/150;
						new cash = pvData[pv][cCarrot] * HargaStrawberry;
						new list[212];
						format(list, sizeof(list), "Sold %d units of wheat", pvData[pv][cCarrot]);
						AddPlayerSalary(playerid, "Farmer Storage Co", list, cash);
						SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've sold "YELLOW_E"%d "WHITE_E"units of "YELLOW_E"Carrot "WHITE_E"for "GREEN_E"$%s", pvData[pv][cCarrot], FormatMoney(cash));
						pvData[pv][cCarrot] = 0;
						if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]))
						{
							DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]);
						}
						TextDrawHideForPlayer(playerid, PlayerCrateTD);
                        PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
                        PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);
						ammountsellcarrot++;
					}
					else if(pvData[pv][cPotato] > 0)
					{
						StockCratePlant += pvData[pv][cPotato]/150;
						new cash = pvData[pv][cPotato] * HargaGandum;
						new list[212];
						format(list, sizeof(list), "Sold %d units of wheat", pvData[pv][cPotato]);
						AddPlayerSalary(playerid, "Farmer Storage Co", list, cash);
						SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've sold "YELLOW_E"%d "WHITE_E"units of "YELLOW_E"Potato "WHITE_E"for "GREEN_E"$%s", pvData[pv][cPotato], FormatMoney(cash));
						pvData[pv][cPotato] = 0;
						if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]))
						{
							DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]);
						}
						TextDrawHideForPlayer(playerid, PlayerCrateTD);
                        PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
                        PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);
						ammountsellpotato++;
					}
					else if(pvData[pv][cCorn] > 0)
					{
						StockCratePlant += pvData[pv][cCorn]/150;
						new cash = pvData[pv][cCorn] * HargaTomat;
						new list[212];
						format(list, sizeof(list), "Sold %d units of wheat", pvData[pv][cCorn]);
						AddPlayerSalary(playerid, "Farmer Storage Co", list, cash);
						SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've sold "YELLOW_E"%d "WHITE_E"units of "YELLOW_E"Corn "WHITE_E"for "GREEN_E"$%s", pvData[pv][cCorn], FormatMoney(cash));
						pvData[pv][cCorn] = 0;
						if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]))
						{
							DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][2]);
						}
						TextDrawHideForPlayer(playerid, PlayerCrateTD);
                        PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
                        PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);
						ammountsellcorn++;
					}
                    new strings[525];
                    format(strings, sizeof(strings), ""AQUA_E"Plant crate\n"WHITE_E"Available crates: "GREEN_E"%d "YELLOW_E"/ 40\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup a crate", StockCratePlant);
	                UpdateDynamic3DTextLabelText(PlantCrate, COLOR_ARWIN, strings);
				}
			}			
		}
		else
		{
			if(pData[playerid][pWheat] > 0)
			{
				StockCratePlant += pData[playerid][pWheat]/150;
				new cash = pData[playerid][pWheat] * HargaAnggur;
				new list[212];
				format(list, sizeof(list), "Sold %d units of wheat", pData[playerid][pWheat]);
				AddPlayerSalary(playerid, "Farmer Storage Co", list, cash);
				SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've sold "YELLOW_E"%d "WHITE_E"units of "YELLOW_E"Wheat "WHITE_E"for "GREEN_E"$%s", pData[playerid][pWheat], FormatMoney(cash));
				pData[playerid][pWheat] = 0;
				ammountsellwheat++;
			}
			else if(pData[playerid][pOnion] > 0)
			{
				StockCratePlant += pData[playerid][pOnion]/150;
				new cash = pData[playerid][pOnion] * HargaBlueberry;
				new list[212];
				format(list, sizeof(list), "Sold %d units of onion", pData[playerid][pOnion]);
				AddPlayerSalary(playerid, "Farmer Storage Co", list, cash);
				SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've sold "YELLOW_E"%d "WHITE_E"units of "YELLOW_E"Onion "WHITE_E"for "GREEN_E"$%s", pData[playerid][pOnion], FormatMoney(cash));
				pData[playerid][pOnion] = 0;
				ammountsellonion++;
			}
			else if(pData[playerid][pCarrot] > 0)
			{
				StockCratePlant += pData[playerid][pCarrot]/150;
				new cash = pData[playerid][pCarrot] * HargaStrawberry;
				new list[212];
				format(list, sizeof(list), "Sold %d units of Carrot", pData[playerid][pCarrot]);
				AddPlayerSalary(playerid, "Farmer Storage Co", list, cash);
				SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've sold "YELLOW_E"%d "WHITE_E"units of "YELLOW_E"Carrot "WHITE_E"for "GREEN_E"$%s", pData[playerid][pCarrot], FormatMoney(cash));
				pData[playerid][pCarrot] = 0;
				ammountsellcarrot++;
			}
			else if(pData[playerid][pPotato] > 0)
			{
				StockCratePlant += pData[playerid][pPotato]/150;
				new cash = pData[playerid][pPotato] * HargaGandum;
				new list[212];
				format(list, sizeof(list), "Sold %d units of Potato", pData[playerid][pPotato]);
				AddPlayerSalary(playerid, "Farmer Storage Co", list, cash);
				SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've sold "YELLOW_E"%d "WHITE_E"units of "YELLOW_E"Potato "WHITE_E"for "GREEN_E"$%s", pData[playerid][pPotato], FormatMoney(cash));
				pData[playerid][pPotato] = 0;
				ammountsellpotato++;
			}
			else if(pData[playerid][pCorn] > 0)
			{
				StockCratePlant += pData[playerid][pCorn]/150;
				new cash = pData[playerid][pCorn] * HargaTomat;
				new list[212];
				format(list, sizeof(list), "Sold %d units of Corn", pData[playerid][pCorn]);
				AddPlayerSalary(playerid, "Farmer Storage Co", list, cash);
				SendClientMessageEx(playerid, COLOR_ARWIN, "PLANTINFO: {FFFFFF}You've sold "YELLOW_E"%d "WHITE_E"units of "YELLOW_E"Corn "WHITE_E"for "GREEN_E"$%s", pData[playerid][pCorn], FormatMoney(cash));
				pData[playerid][pCorn] = 0;
				ammountsellcorn++;
			}
            new strings[525];
            format(strings, sizeof(strings), ""AQUA_E"Plant crate\n"WHITE_E"Available crates: "GREEN_E"%d "YELLOW_E"/ 40\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup a crate", StockCratePlant);
            UpdateDynamic3DTextLabelText(PlantCrate, COLOR_ARWIN, strings);
		}
		
	}
    return 1;
}

Dialog:SellingBush(playerid, response, listitem, inputtext[])
{
    if(response) {
        if(pData[playerid][pBushForager] > 0) {
            SendCustomMessage(playerid, "FOREGER", "You've sold {FFFF00}%d wild berries "RED_E"for {00FF00}$%s", pData[playerid][pBushForager], FormatMoney(pData[playerid][pBushForager]*100));
            GivePlayerMoneyEx(playerid, pData[playerid][pBushForager]*100);
            StockCratePlant += pData[playerid][pBushForager]/100;
            pData[playerid][pBushForager] = 0;
            DelayPlayer[playerid][DelayForager] = 1800;
        }
        new strings[525];
        format(strings, sizeof(strings), ""AQUA_E"Plant crate\n"WHITE_E"Available crates: "GREEN_E"%d "YELLOW_E"/ 40\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup a crate", StockCratePlant);
        UpdateDynamic3DTextLabelText(PlantCrate, COLOR_ARWIN, strings);
    }
    return 1;
}
