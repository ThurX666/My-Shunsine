
CMD:buytruck(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, -77.1687,-1136.5388,1.0781)) return Error(playerid, "You have to be at the trucker point");
	if(pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4)
	{
		new mstr[515];
        format(mstr, sizeof(mstr), "Model\tType\tPrice\n");
        format(mstr, sizeof(mstr), "%s"WHITE_E"%s\tLight/Medium\t"GREEN_E"$%s\n"WHITE_E"%s\tLight/Medium\t"GREEN_E"$%s\n"WHITE_E"%s\tLight/Medium\t"GREEN_E"$%s\n"WHITE_E"%s\tLight/Medium\t"GREEN_E"$%s\n"WHITE_E"%s\tHeavy\t"GREEN_E"$%s\n"WHITE_E"%s\tHeavy\t"GREEN_E"$%s\n"WHITE_E"%s\tHeavy\t"GREEN_E"$%s\n", mstr, 
        GetVehicleModelName(456), FormatMoney(GetVehicleCost(456)),
		GetVehicleModelName(414), FormatMoney(GetVehicleCost(414)),
        GetVehicleModelName(499), FormatMoney(GetVehicleCost(499)),
        GetVehicleModelName(455), FormatMoney(GetVehicleCost(455)),
		GetVehicleModelName(403), FormatMoney(GetVehicleCost(403)),
        GetVehicleModelName(514), FormatMoney(GetVehicleCost(514)),
        GetVehicleModelName(515), FormatMoney(GetVehicleCost(515)));
        Dialog_Show(playerid, BuyTruck, DIALOG_STYLE_TABLIST_HEADERS, "Buying Truck", mstr, "Purchase", "Cancel");
	}
	else return Error(playerid, "You are not trucker driver job.");
	return 1;
}

CMD:missions(playerid,params[])
{
	if(pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4)
	{
        if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 456 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 414 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 499 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 455)
        {
            new Dstring[512];
            format(Dstring, sizeof(Dstring), "Location\tType\tContent\n");
            format(Dstring, sizeof(Dstring), "%sL173: Farmer's Storage\tBarn / Shed\t%d crate\n", Dstring, StockCratePlant);
            format(Dstring, sizeof(Dstring), "%sL175: My Sunshine Mine\tMine\tRaw Components Crates\n", Dstring);
            format(Dstring, sizeof(Dstring), "%sL177: Fish Factory Inc.\tFactory\t%d crates\n", Dstring, StockCrateFish);
            format(Dstring, sizeof(Dstring), "%sL179: Woody's Woods Works\tMill\t%d crates\n", Dstring, StockCrateLumber);
            format(Dstring, sizeof(Dstring), "%sL181: Plants & Timber Dropoff\tExport\tPlants or Timber Crates\n", Dstring);
            format(Dstring, sizeof(Dstring), "%sL182: Fish Factory Inc.\tFactory\t%d crates\n", Dstring, StockCrateFish2);
            format(Dstring, sizeof(Dstring), "%sL184: Fish Dropoff\tExport\tCanned Fish Crates\n", Dstring);
            format(Dstring, sizeof(Dstring), "%sL185: Raw Components Dropoff\tExport\tRaw Components Crates\n", Dstring);
            Dialog_Show(playerid, TruckMission, DIALOG_STYLE_TABLIST_HEADERS, "Missions", Dstring, "Select", "Quit");
        }
 		else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 403 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 514 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 515)
		{
            if(DelayPlayer[playerid][DelayHauling] > 0) return Error(playerid, "Tidak bisa /hauling gunakan /time untuk mengecek");
            if(pData[playerid][pSkillTrucker] < 3) return Error(playerid, "Level Trucker Kamu Masih Rendah");
            if(pData[playerid][pTruckerLic] < 1) return Error(playerid, "You don't have a trucker license");
            if(SedangHauling[playerid] >= 1) return Error(playerid, "Kamu sedang dalam pengiriman.");
			new Float:VPos[3], string[521];
			GetPlayerPos(playerid, VPos[0], VPos[1], VPos[2]);
			for (new i; i < 10; i++) {
                if(i < 6) { TextDrawShowForPlayer(playerid, TDHauling[i]); }
				format(string, sizeof(string), "%.1f miles", GetDistanceBetweenPoints(VPos[0], VPos[1], VPos[2], 2791.4016, -2494.5452, 14.2522)/2);
				TextDrawSetString(TDDistanceHauling[0], string);
				format(string, sizeof(string), "%.1f miles", GetDistanceBetweenPoints(VPos[0], VPos[1], VPos[2], 2784.3132, -2456.6299, 14.2415)/2);
				TextDrawSetString(TDDistanceHauling[1], string);
				format(string, sizeof(string), "%.1f miles", GetDistanceBetweenPoints(VPos[0], VPos[1], VPos[2], -1963.0142, -2436.3079, 31.2311)/2);
				TextDrawSetString(TDDistanceHauling[2], string);
				format(string, sizeof(string), "%.1f miles", GetDistanceBetweenPoints(VPos[0], VPos[1], VPos[2], -1966.5603, -2439.9380, 31.2306)/2);
				TextDrawSetString(TDDistanceHauling[3], string);
				format(string, sizeof(string), "%.1f miles", GetDistanceBetweenPoints(VPos[0], VPos[1], VPos[2], -1863.1541, -1720.5603, 22.3558)/2);
				TextDrawSetString(TDDistanceHauling[4], string);
				format(string, sizeof(string), "%.1f miles", GetDistanceBetweenPoints(VPos[0], VPos[1], VPos[2], -1855.7255, -1726.0389, 22.3566)/2);
				TextDrawSetString(TDDistanceHauling[5], string);
				format(string, sizeof(string), "%.1f miles", GetDistanceBetweenPoints(VPos[0], VPos[1], VPos[2], -1053.6145, -658.6473, 32.6319)/2);
				TextDrawSetString(TDDistanceHauling[6], string);
				format(string, sizeof(string), "%.1f miles", GetDistanceBetweenPoints(VPos[0], VPos[1], VPos[2], -459.3511, -48.3457, 60.5507)/2);
				TextDrawSetString(TDDistanceHauling[7], string);
				format(string, sizeof(string), "%.1f miles", GetDistanceBetweenPoints(VPos[0], VPos[1], VPos[2], 847.0450, 921.0422, 13.9579)/2);
				TextDrawSetString(TDDistanceHauling[8], string);
				format(string, sizeof(string), "%.1f miles", GetDistanceBetweenPoints(VPos[0], VPos[1], VPos[2], 249.6713, 1395.7150, 11.1923)/2);
				TextDrawSetString(TDDistanceHauling[9], string);
				TextDrawSetString(TDMoneyHauling[0], (DialogHauling[0] == true) ? ("~r~Taken") : ("~g~$350.00"));
				TextDrawSetString(TDMoneyHauling[1], (DialogHauling[1] == true) ? ("~r~Taken") : ("~g~$300.00"));
				TextDrawSetString(TDMoneyHauling[2], (DialogHauling[2] == true) ? ("~r~Taken") : ("~g~$250.00"));
				TextDrawSetString(TDMoneyHauling[3], (DialogHauling[3] == true) ? ("~r~Taken") : ("~g~$270.00"));
				TextDrawSetString(TDMoneyHauling[4], (DialogHauling[4] == true) ? ("~r~Taken") : ("~g~$399.00"));
				TextDrawSetString(TDMoneyHauling[5], (DialogHauling[5] == true) ? ("~r~Taken") : ("~g~$200.00"));
				TextDrawSetString(TDMoneyHauling[6], (DialogHauling[6] == true) ? ("~r~Taken") : ("~g~$310.00"));
				TextDrawSetString(TDMoneyHauling[7], (DialogHauling[7] == true) ? ("~r~Taken") : ("~g~$333.00"));
				TextDrawSetString(TDMoneyHauling[8], (DialogHauling[8] == true) ? ("~r~Taken") : ("~g~$290.00"));
				TextDrawSetString(TDMoneyHauling[9], (DialogHauling[9] == true) ? ("~r~Taken") : ("~g~$255.00"));
				if(DialogHauling[0] == true) TextDrawBoxColor(TDBoxHauling[0], 255);
				if(DialogHauling[1] == true) TextDrawBoxColor(TDBoxHauling[1], 255);
				if(DialogHauling[2] == true) TextDrawBoxColor(TDBoxHauling[2], 255);
				if(DialogHauling[3] == true) TextDrawBoxColor(TDBoxHauling[3], 255);
				if(DialogHauling[4] == true) TextDrawBoxColor(TDBoxHauling[4], 255);
				if(DialogHauling[5] == true) TextDrawBoxColor(TDBoxHauling[5], 255);
				if(DialogHauling[6] == true) TextDrawBoxColor(TDBoxHauling[6], 255);
				if(DialogHauling[7] == true) TextDrawBoxColor(TDBoxHauling[7], 255);
				if(DialogHauling[8] == true) TextDrawBoxColor(TDBoxHauling[8], 255);
				if(DialogHauling[9] == true) TextDrawBoxColor(TDBoxHauling[9], 255);
				TextDrawShowForPlayer(playerid, TDDistanceHauling[i]);
				TextDrawShowForPlayer(playerid, TDNameHauling[i]);
				TextDrawShowForPlayer(playerid, TDMoneyHauling[i]);
				TextDrawShowForPlayer(playerid, TDBoxHauling[i]);
				SelectTextDraw(playerid, 0xCCFFFFFF);
			}
            SetPVarInt(playerid, "UseMissions", 1);
            SendCustomMessage(playerid, "NOTE", ""YELLOW_E"Untuk menyembunyikan texdraw tekan "RED_E"N "YELLOW_E"pada keyboard anda");
		} 
        else return Error(playerid, "You are not in the Truck."); 
	}
	else return Error(playerid, "You are not a trucker.");
	return 1;
}

CMD:getcrate(playerid, params[])
{
    if(DelayPlayer[playerid][DelayDelivery] == 0) 
    {
        if(pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4)
        {
            if(pData[playerid][pCrate] > 0) return Error(playerid, "Kamu sudah membawa crate, harap masukan kedalam mobil terlebih dahulu!");
            if(IsPlayerInRangeOfPoint(playerid, 4.0, 335.0611, 896.4723, 21.2162))
            {
                SendClientMessageEx(playerid, COLOR_ARWIN, "STORAGE: "WHITE_E"You've picked up "AQUA_E"1 raw component crate");    
                pData[playerid][pCrate] = 1;
                SetPlayerSpecialAction(playerid,SPECIAL_ACTION_CARRY);
                SetPlayerAttachedObject(playerid, 9, 2912, 1, 0.233, 0.359, -0.198, 1.400, 0.000, 0.000, 0.640, 0.625, 0.654);
                pData[playerid][pCrateType] = 1;
            }
            else if(IsPlayerInRangeOfPoint(playerid, 4.0, 2836.3945,-1541.1984,11.0991))
            {
                if(StockCrateFish > 0)
                {
                    new fish[212];
                    SendClientMessageEx(playerid, COLOR_ARWIN, "STORAGE: "WHITE_E"You've picked up "AQUA_E"1 canned fish crate");    
                    pData[playerid][pCrate] = 1;
                    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_CARRY);
                    SetPlayerAttachedObject(playerid, 9, 2912, 1, 0.233, 0.359, -0.198, 1.400, 0.000, 0.000, 0.640, 0.625, 0.654);
                    pData[playerid][pCrateType] = 2;
                    StockCrateFish--;
                    Crate_Save();
                    format(fish, sizeof(fish), "{00FFFF}Canned Fish Crates\nAvailable crates: "GREEN_E"%d "YELLOW_E"/ 40\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup a crate", StockCrateFish);
	                UpdateDynamic3DTextLabelText(Fish2, COLOR_ARWIN, fish);
                } 
                else return Error(playerid, "Current crate is 0, can't take crate!"); 
            }
            else if(IsPlayerInRangeOfPoint(playerid, 4.0, -366.3686,-1419.0941,25.7266))
            {
                if(StockCratePlant > 0)
                {
                    new strings[525];
                    SendClientMessageEx(playerid, COLOR_ARWIN, "STORAGE: "WHITE_E"You've picked up "AQUA_E"1 plant crate");    
                    pData[playerid][pCrate] = 1;
                    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_CARRY);
                    SetPlayerAttachedObject(playerid, 9, 2912, 1, 0.233, 0.359, -0.198, 1.400, 0.000, 0.000, 0.640, 0.625, 0.654);
                    pData[playerid][pCrateType] = 3;
                    StockCratePlant--;
                    Crate_Save();
                    format(strings, sizeof(strings), ""AQUA_E"Plant crate\n"WHITE_E"Available crates: "GREEN_E"%d "YELLOW_E"/ 40\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup a crate", StockCratePlant);
	                UpdateDynamic3DTextLabelText(PlantCrate, COLOR_ARWIN, strings);
                }
                else return Error(playerid, "Current crate is 0, can't take crate!");  
            }
            else if(IsPlayerInRangeOfPoint(playerid, 4.0, -1446.6145,-1544.0745,101.7935))
            {
                if(StockCrateLumber > 0)
                {
                    new strings[525];
                    SendClientMessageEx(playerid, COLOR_ARWIN, "STORAGE: "WHITE_E"You've picked up "AQUA_E"1 timber crate");    
                    pData[playerid][pCrate] = 1;
                    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_CARRY);
                    SetPlayerAttachedObject(playerid, 9, 2912, 1, 0.233, 0.359, -0.198, 1.400, 0.000, 0.000, 0.640, 0.625, 0.654);
                    pData[playerid][pCrateType] = 4;
                    StockCrateLumber--;
                    Crate_Save();
                    format(strings, sizeof(strings), ""AQUA_E"Timber crate\n"WHITE_E"Available crates: "GREEN_E"%d "YELLOW_E"/ 40\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup a crate", StockCrateLumber);
	                UpdateDynamic3DTextLabelText(Timber, COLOR_ARWIN, strings);
                }
                else return Error(playerid, "Current crate is 0, can't take crate!"); 
            }
            else if(IsPlayerInRangeOfPoint(playerid, 4.0, -759.54, 1640.60, 27.39))
            {
                if(StockCrateFish2 > 0)
                {
                    new fish[212];
                    SendClientMessageEx(playerid, COLOR_ARWIN, "STORAGE: "WHITE_E"You've picked up "AQUA_E"1 canned fish crate");    
                    pData[playerid][pCrate] = 1;
                    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_CARRY);
                    SetPlayerAttachedObject(playerid, 9, 2912, 1, 0.233, 0.359, -0.198, 1.400, 0.000, 0.000, 0.640, 0.625, 0.654);
                    pData[playerid][pCrateType] = 5;
                    StockCrateFish2--;
                    Crate_Save();
                    format(fish, sizeof(fish), "{00FFFF}Canned Fish Crates\nAvailable crates: "GREEN_E"%d "YELLOW_E"/ 40\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup a crate", StockCrateFish2);
                    UpdateDynamic3DTextLabelText(Fish3, COLOR_ARWIN, fish);
                } 
                else return Error(playerid, "Current crate is 0, can't take crate!"); 
            }
        }
        else return Error(playerid, "You are not a trucker");
    }
    else 
    {
        new String[212];
        format(String, sizeof(String),"ERROR: "WHITE_E"Kamu harus menunggu "YELLOW_E"%d Menit "WHITE_E"untuk mengangkat crate lagi", DelayPlayer[playerid][DelayDelivery]/60);
        SendClientMessage(playerid, COLOR_ARWIN, String);
    }    
    return 1;
}

CMD:loadcrate(playerid, params[])
{
    if(pData[playerid][pCrate] < 1) return Error(playerid, "You didn't bring the crate");
    new Float: x, Float: y, Float: z;
    new vehicleid = GetPVarInt(playerid, "LastVehicleID");
    GetVehicleBoot(GetPVarInt(playerid, "LastVehicleID"), x, y, z);
    if(GetPlayerDistanceFromPoint(playerid, x, y, z) > 3.0) return Error(playerid, "Your last vehicle is too far away.");  
    if(Vehicle_CrateComponentTotal(vehicleid) >= 10) return Error(playerid, "You can't load any more crate to this vehicle.");    
    if(Vehicle_CratePlantTotal(vehicleid) >= 10) return Error(playerid, "You can't load any more crate to this vehicle.");    
    if(Vehicle_CrateLumberTotal(vehicleid) >= 10) return Error(playerid, "You can't load any more crate to this vehicle.");    
    if(Vehicle_CrateFishTotal(vehicleid) >= 10) return Error(playerid, "You can't load any more crate to this vehicle.");    
    if(!IsATruckCrate(vehicleid)) return Error(playerid, "You must use a crate type car");
    if(pData[playerid][pCrateType] == 1)
    {
        foreach(new pv : PVehicles)
        {
            if(vehicleid == pvData[pv][cVeh])
            {
                pvData[pv][cCrateComponent]++;
                pData[playerid][pCrate] = 0;
                SendClientMessageEx(playerid, COLOR_ARWIN, "TRUCK: "WHITE_E"You've loaded "YELLOW_E" a crate "WHITE_E"of raw components, total crates: "GREEN_E"%d", pvData[pv][cCrateComponent]); 
                SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
                RemovePlayerAttachedObject(playerid, 9);
            }
        }   
    }
    else if(pData[playerid][pCrateType] == 2)
    {
        foreach(new pv : PVehicles)
        {
            if(vehicleid == pvData[pv][cVeh])
            {
                pvData[pv][cCrateFish]++;
                pData[playerid][pCrate] = 0;
                SendClientMessageEx(playerid, COLOR_ARWIN, "TRUCK: "WHITE_E"You've loaded "YELLOW_E" a crate "WHITE_E"of las canned fish, total crates: "GREEN_E"%d", pvData[pv][cCrateFish]); 
                SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
                RemovePlayerAttachedObject(playerid, 9);
            }
        }   
    }
    else if(pData[playerid][pCrateType] == 3)
    {
        foreach(new pv : PVehicles)
        {
            if(vehicleid == pvData[pv][cVeh])
            {
                pvData[pv][cCratePlant]++;
                pData[playerid][pCrate] = 0;
                SendClientMessageEx(playerid, COLOR_ARWIN, "TRUCK: "WHITE_E"You've loaded "YELLOW_E" a crate "WHITE_E"of plant crate, total crates: "GREEN_E"%d", pvData[pv][cCratePlant]); 
                SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
                RemovePlayerAttachedObject(playerid, 9);
            }
        }   
    }
    else if(pData[playerid][pCrateType] == 4)
    {
        foreach(new pv : PVehicles)
        {
            if(vehicleid == pvData[pv][cVeh])
            {
                pvData[pv][cCrateLumber]++;
                pData[playerid][pCrate] = 0;
                SendClientMessageEx(playerid, COLOR_ARWIN, "TRUCK: "WHITE_E"You've loaded "YELLOW_E" a crate "WHITE_E"of timber crate, total crates: "GREEN_E"%d", pvData[pv][cCrateLumber]); 
                SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
                RemovePlayerAttachedObject(playerid, 9);
            }
        }   
    }
    else if(pData[playerid][pCrateType] == 4)
    {
        foreach(new pv : PVehicles)
        {
            if(vehicleid == pvData[pv][cVeh])
            {
                pvData[pv][cCrateFish2]++;
                pData[playerid][pCrate] = 0;
                SendClientMessageEx(playerid, COLOR_ARWIN, "TRUCK: "WHITE_E"You've loaded "YELLOW_E" a crate "WHITE_E"of canned fish, total crates: "GREEN_E"%d", pvData[pv][cCrateFish2]); 
                SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
                RemovePlayerAttachedObject(playerid, 9);
            }
        }   
    }
    return 1;
}

CMD:unloadcrate(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return Error(playerid, "You are not driver in crate truck.");
    if(!IsValidVehicle(vehicleid)) return Error(playerid, "You're not in any vehicle.");
    if(IsPlayerInRangeOfPoint(playerid, 4.0, 797.7953,-616.8799,16.3359))
    {
        foreach(new pv : PVehicles)
        {
            if(vehicleid == pvData[pv][cVeh])
            {
                if(pvData[pv][cCrateComponent] > 0)
                {
                    if(StockComponent > 50000) return Error(playerid, "Stock components in the warehouse exceed capacity");
                    new cash = pvData[pv][cCrateComponent] * 1250;
                    if(cash < 1) return Error(playerid, "This vehicle crate is empty!");
                    StockComponent += pvData[pv][cCrateComponent] + 10;
                    new list[212];
                    format(list, sizeof(list), "Delivered %d component crates", pvData[pv][cCrateComponent]);
                    AddPlayerSalary(playerid, "Trucking Co.", list, cash);
                    SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                    pvData[pv][cCrateComponent] = 0;
                    DelayPlayer[playerid][DelayDelivery] = 600;
                    pData[playerid][pScoreTrucker] += 10;
                    TextDrawHideForPlayer(playerid, PlayerCrateTD);
                    PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
                    PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);
                    new strings[212];
                    format(strings, sizeof(strings), "{00FFFF}Component Factory\n"WHITE_E"Price: "GREEN_E"$0.50 "WHITE_E"/ unit\n"WHITE_E"Stock: "GREEN_E"%d "YELLOW_E"/ 50000\n"WHITE_E"Use '"YELLOW_E"/buycomponent"WHITE_E"' to buy components", StockComponent);
	                UpdateDynamic3DTextLabelText(Compo2, COLOR_ARWIN, strings);
                }  
            }
        }       
          
    }
    else if(IsPlayerInRangeOfPoint(playerid, 4.0, -577.1335,-503.6530,25.5107))
    {
        foreach(new pv : PVehicles)
        {
            if(vehicleid == pvData[pv][cVeh])
            {
                if(pvData[pv][cCrateFish] > 0)
                {
                    new cash = pvData[pv][cCrateFish] * 1250;
                    if(cash < 1) return Error(playerid, "This vehicle crate is empty!");
                    StockComponent += pvData[pv][cCrateFish] + 10;
                    new list[212];
                    format(list, sizeof(list), "Delivered %d fish crates", pvData[pv][cCrateFish]);
                    AddPlayerSalary(playerid, "Trucking Co.", list, cash);
                    SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                    pvData[pv][cCrateFish] = 0;
                    DelayPlayer[playerid][DelayDelivery] = 600;
                    pData[playerid][pScoreTrucker] += 10;
                    if(pData[playerid][pScoreTrucker] >= 50)
                    {
                        pData[playerid][pSkillTrucker] = 2;
                    }
                    else if(pData[playerid][pScoreTrucker] >= 150)
                    {
                        pData[playerid][pSkillTrucker] = 3;
                    }
                    else if(pData[playerid][pScoreTrucker] >= 200)
                    {
                        pData[playerid][pSkillTrucker] = 4;
                    }
                    else if(pData[playerid][pScoreTrucker] >= 300)
                    {
                        pData[playerid][pSkillTrucker] = 5;
                    }
                    TextDrawHideForPlayer(playerid, PlayerCrateTD);
                    PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
                    PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);	
                }  
                else if(pvData[pv][cCrateFish2] > 0)
                {
                    new cash = pvData[pv][cCrateFish2] * 1250;
                    if(cash < 1) return Error(playerid, "This vehicle crate is empty!");
                    StockComponent += pvData[pv][cCrateFish2] + 10;
                    new list[212];
                    format(list, sizeof(list), "Delivered %d fish crates", pvData[pv][cCrateFish2]);
                    AddPlayerSalary(playerid, "Trucking Co.", list, cash);
                    SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                    pvData[pv][cCrateFish2] = 0;
                    DelayPlayer[playerid][DelayDelivery] = 600;
                    pData[playerid][pScoreTrucker] += 10;
                    if(pData[playerid][pScoreTrucker] >= 50)
                    {
                        pData[playerid][pSkillTrucker] = 2;
                    }
                    else if(pData[playerid][pScoreTrucker] >= 150)
                    {
                        pData[playerid][pSkillTrucker] = 3;
                    }
                    else if(pData[playerid][pScoreTrucker] >= 200)
                    {
                        pData[playerid][pSkillTrucker] = 4;
                    }
                    else if(pData[playerid][pScoreTrucker] >= 300)
                    {
                        pData[playerid][pSkillTrucker] = 5;
                    }
                    TextDrawHideForPlayer(playerid, PlayerCrateTD);
                    PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
                    PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]); 
                }  
            }
        }       
                
    } 
    else if(IsPlayerInRangeOfPoint(playerid, 4.0, 2792.4355,-2456.1199,13.6325))
    {
        foreach(new pv : PVehicles)
        {
            if(vehicleid == pvData[pv][cVeh])
            {
                if(pvData[pv][cCratePlant] > 0)
                {
                    new cash = pvData[pv][cCratePlant] * 1250;
                    if(cash < 1) return Error(playerid, "This vehicle crate is empty!");
                    StockComponent += pvData[pv][cCratePlant] + 10;
                    new list[212];
                    format(list, sizeof(list), "Delivered %d plant crates", pvData[pv][cCratePlant]);
                    AddPlayerSalary(playerid, "Trucking Co.", list, cash);
                    SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                    pvData[pv][cCratePlant] = 0;
                    DelayPlayer[playerid][DelayDelivery] = 600;
                    pData[playerid][pScoreTrucker] += 10;
                    if(pData[playerid][pScoreTrucker] >= 50)
                    {
                        pData[playerid][pSkillTrucker] = 2;
                    }
                    else if(pData[playerid][pScoreTrucker] >= 150)
                    {
                        pData[playerid][pSkillTrucker] = 3;
                    }
                    else if(pData[playerid][pScoreTrucker] >= 200)
                    {
                        pData[playerid][pSkillTrucker] = 4;
                    }
                    else if(pData[playerid][pScoreTrucker] >= 300)
                    {
                        pData[playerid][pSkillTrucker] = 5;
                    }
                    TextDrawHideForPlayer(playerid, PlayerCrateTD);
                    PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
                    PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);
                } 
                else  if(pvData[pv][cCrateLumber] > 0)
                {
                    new cash = pvData[pv][cCrateLumber] * 1250;
                    if(cash < 1) return Error(playerid, "This vehicle crate is empty!");
                    StockComponent += pvData[pv][cCrateLumber] + 10;
                    new list[212];
                    format(list, sizeof(list), "Delivered %d lumber crates", pvData[pv][cCrateLumber]);
                    AddPlayerSalary(playerid, "Trucking Co.", list, cash);
                    SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                    pvData[pv][cCrateLumber] = 0;
                    DelayPlayer[playerid][DelayDelivery] = 600;
                    pData[playerid][pScoreTrucker] += 10;
                    if(pData[playerid][pScoreTrucker] >= 50)
                    {
                        pData[playerid][pSkillTrucker] = 2;
                    }
                    else if(pData[playerid][pScoreTrucker] >= 150)
                    {
                        pData[playerid][pSkillTrucker] = 3;
                    }
                    else if(pData[playerid][pScoreTrucker] >= 200)
                    {
                        pData[playerid][pSkillTrucker] = 4;
                    }
                    else if(pData[playerid][pScoreTrucker] >= 300)
                    {
                        pData[playerid][pSkillTrucker] = 5;
                    }
                    TextDrawHideForPlayer(playerid, PlayerCrateTD);
                    PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
                    PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);	
                } 
            }
        }       
                
    } 
    return 1;
}

CMD:dropcrate(playerid, params[])
{
    if(pData[playerid][pCrate] > 0)
    {
        pData[playerid][pCrate] = 0;
        SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 9);
        SendClientMessageEx(playerid, COLOR_ARWIN, "JOB: "YELLOW_E"You have dropped the crate");    
    }
    return 1;
}
