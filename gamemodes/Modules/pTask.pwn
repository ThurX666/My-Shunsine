new bool:gWeaponAttachedObject[MAX_PLAYERS][10];


task ServerRestart[1000]()
{
	/*Server restaer timer*/
    if(g_ServerRestart)
    {
		switch(g_RestartTime)
		{
			case 1:
			{
				g_ServerRestart = 0;
				g_RestartTime = 0;
				SaveAll();
				GameModeExit();
			}
			case 3:
			{
				for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++) if(IsPlayerConnected(i))
					KickEx(i);

				g_RestartTime--;
			}
			default: {
				new times[3];
				GetElapsedTime(g_RestartTime--, times[0], times[1], times[2]);
			}
		}
    }
	return 1;
}

task MinuteCheck[60000]() 
{
    for (new i = 0; i != MAX_GARBAGE_BINS; i ++) if(GarbageData[i][garbageExists] && GarbageData[i][garbageCapacity] < 10)
    {
        SetGVarInt("TrashUpdate", GetGVarInt("TrashUpdate")+1);

        if(GetGVarInt("TrashUpdate") >= 5)
        {
            SetGVarInt("TrashUpdate", 0);
            GarbageData[i][garbageCapacity] ++;
        }
    }
}

task HouseUpdate[1000]()
{
	foreach (new house : Houses) if (hData[house][houseBuilderTime]) {
        if (gettime() >= hData[house][houseBuilderTime]) {
            hData[house][houseBuilderTime] = 0;
            hData[house][houseBuilder] = 0;
        }
    }
	return 1;
}

task PriceUpdate[1000]()
{
	new h, m, s;
    gettime(h, m, s);

    if (m == 0 && s == 0) {
		HargaBensin = Random(100,200);
		StockMaterial += 10000;
		StockCrack += 2500;
		HargaAnggur = Random(100,200);
		HargaBlueberry = Random(100,200);
		HargaStrawberry = Random(100,200);
		HargaGandum = Random(100,200);
		HargaTomat = Random(100,200);
		ammountsellwheat = 0;
		ammountsellonion = 0;
		ammountsellcarrot = 0;
		ammountsellpotato = 0;
		ammountsellcorn = 0;
		//Farm
		new String2[212];
		format(String2,sizeof(String2),""PURPLE_E2"Plant Price\n{FFFFFF}Wheat: "GREEN_E"$0.%s"WHITE_E"\nOnion: "GREEN_E"$0.%s"WHITE_E"\nCarrot: "GREEN_E"$0.%s"WHITE_E"\nPotato: "GREEN_E"$0.%s"WHITE_E"\nCorn: "GREEN_E"$0.%s"WHITE_E"", FormatMoney(HargaAnggur), FormatMoney(HargaBlueberry), FormatMoney(HargaStrawberry), FormatMoney(HargaGandum), FormatMoney(HargaTomat));
		SetDynamicObjectMaterialText(SELLFARM2, 0, String2, 130, "Arial", 30, 1, 0xFFFFFFFF, 0xFF000000, 1);
		//Fish
		FishPrice = Random(450, 800);
		new String3[212];
		format(String3,sizeof(String3),"Fish Price: \n"GREEN_E"$%s"WHITE_E"/lb", FormatMoney(FishPrice));
		SetDynamicObjectMaterialText(SELLFISH, 0, String3, 130, "Arial", 40, 1, 0xFFFFFFFF, 0xFF000000, 1);
		format(String3,sizeof(String3),"Fish Price: \n"GREEN_E"$%s"WHITE_E"/lb", FormatMoney(FishPrice));
		SetDynamicObjectMaterialText(SELLFISH2, 1, String3, 130, "Arial", 48, 1, -65366, -16777216, 1);
	}
	return 1;
}

task UpdateWeatherAndTime[1000]() {
    new h, m, s;

    gettime(h, m, s);

    if (m == 0 && s == 0) {
        gettime(current_hour, _);

        new nextWeather = random(91);

        if (nextWeather < 70) current_weather = fine_weather_ids[random(sizeof(fine_weather_ids))];
        else current_weather = wet_weather_ids[0];

        foreach(new i : Player) if (GetPlayerInterior(i) == 0) {
            SetPlayerWeather(i, current_weather);
            SetPlayerTime(i, current_hour, 0);
        }
        SendRconCommand(sprintf("weather %d", current_weather));
        SendRconCommand(sprintf("worldtime %02d:00", current_hour));
    }
    return 1;
}

ptask PlayerTimeDuty[1000](playerid) {
	if(PlayerPause[playerid] > 0) return 0;
	if(!pData[playerid][IsLoggedIn]) return 0;
	if(PlayerPause[playerid] > 0) return 0;
	if(pData[playerid][pAdmin] > 0 || pData[playerid][pHelper] > 0) {
		if(pData[playerid][pAdminDuty] > 0) pData[playerid][pAdminTime]++;
	}
	if(pData[playerid][pFaction] > 0 && pData[playerid][pOnDuty] > 0) {
		pData[playerid][pOnDutyTime]++;
		if(pData[playerid][pOnDutyTime] > 3600) {

			switch(pData[playerid][pFaction]) {
				case 1: AddPlayerSalary(playerid, "San Andreas Police Department", "Duty Faction", 50000);
				case 3: AddPlayerSalary(playerid, "San Andreas Medic Department", "Duty Faction", 50000);
				case 4: AddPlayerSalary(playerid, "San Andreas Network", "Duty Faction", 50000);
			}
			pData[playerid][pOnDutyTime] = 0;
			SendClientMessageEx(playerid, COLOR_ARWIN, "SALARY: {ffffff}Your salary factions has been updated, please check command {ffff00}'/mysalary'");
		}
	}
	if(pData[playerid][pTaxiDuty] > 0) {
		pData[playerid][pTaxiTime]++;
		if(pData[playerid][pTaxiTime] > 900) {
			pData[playerid][pTaxiTime] = 0;
			AddPlayerSalary(playerid, "Taxi Service", "Duty Taxi Service", 1500);
			SendClientMessageEx(playerid, COLOR_ARWIN, "SALARY: {ffffff}Your salary statement has been updated, please check command {ffff00}'/mysalary'");
		}
	}
	if(pData[playerid][pMechDuty] > 0) {
		pData[playerid][pMechTime]++;
		if(pData[playerid][pMechTime] > 900) {
			pData[playerid][pMechTime] = 0;
			AddPlayerSalary(playerid, "Mechanic Center", "Duty Mechanic Service", 1500);
			SendClientMessageEx(playerid, COLOR_ARWIN, "SALARY: {ffffff}Your salary statement has been updated, please check command {ffff00}'/mysalary'");
		}
	}
	return 1;
}

ptask Player_ArrestTimer[1000](playerid)
{
	if(PlayerPause[playerid] > 0) return 0;
	if(!pData[playerid][IsLoggedIn]) return 0;
	new string[128];
	//Arreset Player
	if(pData[playerid][pArrest] > 0)
	{
		if(pData[playerid][pArrestTime] > 0)
		{
			pData[playerid][pArrestTime]--;
			format(string, sizeof(string), "You will be released in ~y~%d ~w~seconds.", pData[playerid][pArrestTime]);
			PlayerTextDrawSetString(playerid, JailTD[playerid], string);
		}
		else
		{
			pData[playerid][pArrest] = 0;
			pData[playerid][pArrestTime] = 0;
			PlayerTextDrawHide(playerid, JailTD[playerid]);
			SetPlayerPositionEx(playerid, 1541.7076,-1675.2380,13.5531,89.6938, 2000);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			GameTextForPlayer(playerid, "~g~Freedom~n~~w~Jadilah warga yang baik", 1000, 1);
		}
	}
	return 1;
}

ptask Player_JailTimer[1000](playerid)
{
	if(PlayerPause[playerid] > 0) return 0;
	if(!pData[playerid][IsLoggedIn]) return 0;
	//Jail Player
	if(pData[playerid][pJail] > 0)
	{
		if(pData[playerid][pJailTime] > 0)
		{
			pData[playerid][pJailTime]--;
			new string[128];
			format(string, sizeof(string), "Jail time: ~y~%d ~w~seconds", pData[playerid][pJailTime]);
			PlayerTextDrawSetString(playerid, JailTD[playerid], string);
		}
		else
		{
			pData[playerid][pJail] = 0;
			pData[playerid][pJailTime] = 0;
			PlayerTextDrawHide(playerid, JailTD[playerid]);
			SetPlayerPositionEx(playerid, 1545.0389,-1675.6569,13.5596,89.2342);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			GameTextForPlayer(playerid, "~g~Freedom~n~~w~Jadilah warga yang baik", 1000, 1);
		}
	}
	if(pData[playerid][pJail] <= 0)
	{
		if(pData[playerid][pHunger] > 100) pData[playerid][pHunger] = 100;
		if(pData[playerid][pHunger] < 0) pData[playerid][pHunger] = 0;
		if(pData[playerid][pEnergy] > 100) pData[playerid][pEnergy] = 100;
		if(pData[playerid][pEnergy] < 0) pData[playerid][pEnergy] = 0;
	}
	return 1;
}

ptask PlayerFarm_Cheker[1000](playerid)
{
	new pid = GetClosestPlant(playerid);
	if(pid != -1)
	{
		if(IsPlayerInDynamicCP(playerid, PlantData[pid][PlantCP]) && pid != -1)
		{
			new type[24], mstr[128];
			if(PlantData[pid][PlantType] == 1) type = "Wheat";
			else if(PlantData[pid][PlantType] == 2) type = "Onion";
			else if(PlantData[pid][PlantType] == 3) type = "Carrot";
			else if(PlantData[pid][PlantType] == 4) type = "Potato";
			else if(PlantData[pid][PlantType] == 5) type = "Corn";
			if(PlantData[pid][PlantTime] > 1) format(mstr, sizeof(mstr), "~y~Plant Type: ~w~%s ~n~~y~Plant Time: ~r~%d minutes", type, PlantData[pid][PlantTime]/10);
			else format(mstr, sizeof(mstr), "~y~Plant Type: ~w~%s ~n~~y~Plant Time: ~g~Now", type);
			GameTextForPlayer(playerid, mstr, 1000, 6);
		}
	}
	//Farmer
	if(pData[playerid][pPlant] >= 20)
	{
		pData[playerid][pPlant] = 0;
		pData[playerid][pPlantTime] = 600;
	}
	if(pData[playerid][pPlantTime] > 0)
	{
		pData[playerid][pPlantTime]--;
		if(pData[playerid][pPlantTime] < 1)
		{
			pData[playerid][pPlantTime] = 0;
			pData[playerid][pPlant] = 0;
		}
	}
	return 1;
}

ptask PlayerHoursUpdate[1000](playerid)
{
	if(PlayerPause[playerid] > 0) return 0;
	if(pData[playerid][IsLoggedIn] == true /*&& cAFK[playerid] == 0*/) {
		pData[playerid][pSeconds]++;
		pData[playerid][pPaycheck]++;
		if(pData[playerid][pSeconds] >= 60) {
			pData[playerid][pSeconds] = 0;
			pData[playerid][pMinutes]++;
			if(pData[playerid][pMinutes] >= 60) {
				pData[playerid][pMinutes] = 0;
				pData[playerid][pHours]++;
				UpdatePlayerData(playerid);
				if(pData[playerid][pHours] >= GetHoursLevel(pData[playerid][pLevel])) {
					pData[playerid][pLevel]++;
					new mstr[128];
					SetPlayerScore(playerid, pData[playerid][pLevel]);
					format(mstr,sizeof(mstr),"~g~New level unlocked~n~~w~Now you're level ~r~%d", pData[playerid][pLevel]);
					GameTextForPlayer(playerid, mstr, 6000, 1);
				}
				if(pData[playerid][pPaycheck] >= 3600) {
					PlayerPlaySound(playerid, 1186, 0, 0, 0);
					if(pData[playerid][pTogPaycheck]) DisplayPaycheck(playerid);
					else SendClientMessageEx(playerid,COLOR_ARWIN,"PAYCHECK: "WHITE_E"Pergilah ke bank lalu "YELLOW_E"'/signcheck' "WHITE_E"untuk mendapat kan paycheck anda.");
				}
			}
		}
	}
	return 1;
}

ptask CharacterUpdate[1000](playerid)
{
	//Speed Hack
    new jembutveh = GetPlayerVehicleID(playerid);
    if(GetVehicleSpeed(jembutveh) > 220 || GetKecepatanPlayer(playerid) > 220)
    {
        // SendClientMessageToAllEx(TOMATO, "AdmCmd: %s(%d) was auto-kicked by BotCmd, reason: Speed Hacks", pData[playerid][pName], playerid);
        // KickEx(playerid);
    }
	for (new i = 0; i < 6; i ++) 
	{
		pData[playerid][pFitnessRating][i] = 100.0;
	}
	new Float:MaxHealth;
	if(PlayerPause[playerid] > 0) return 0;
	if(!pData[playerid][IsLoggedIn]) return 0;
    if(IsPlayerInEvent(playerid)) return 0;
	for (new i = 0; i < 6; i ++) {
		MaxHealth += pData[playerid][pFitnessRating][i];
	}
	pData[playerid][pMaxHealth] = MaxHealth/6;
    new 
        Float:server_armour = pData[playerid][pArmour],
        Float:client_armour
    ;
    GetPlayerArmour(playerid, client_armour);
    if(client_armour != server_armour) SetPlayerArmourEx(playerid, server_armour);
    if(GetPlayerMoney(playerid) != pData[playerid][pMoney]) {
        ResetPlayerMoney(playerid);
        GivePlayerMoney(playerid, pData[playerid][pMoney]);
    }
	return 1;
}

ptask PlayerData_Minus[1000](playerid)
{	
	if(PlayerPause[playerid] > 0) return 0;
	if(!pData[playerid][pAFK]) return 0;
	if(DelayPlayer[playerid][DelaySmuggler] > 0) DelayPlayer[playerid][DelaySmuggler]--;
	if(DelayPlayer[playerid][DelayTraining] > 0) DelayPlayer[playerid][DelayTraining]--;
	if(DelayPlayer[playerid][DelayWeaponCreate] > 0) DelayPlayer[playerid][DelayWeaponCreate]--;
	if(pData[playerid][pDelayCrate] > 0) pData[playerid][pDelayCrate]--;
	if(pData[playerid][pTaxiCall] > 0) pData[playerid][pTaxiCall]--;
	if(pData[playerid][pMechaCall] > 0) pData[playerid][pMechaCall]--;
	if(DelayPlayer[playerid][DelayForager] > 0) DelayPlayer[playerid][DelayForager]--;
	if(DelayPlayer[playerid][DelayMiner] > 0) DelayPlayer[playerid][DelayMiner]--;
	
	if (pData[playerid][pGYMMember] > 0 && pData[playerid][pGYMMemberTime] > 0) {
        if (gettime() >= pData[playerid][pGYMMemberTime]) {
            pData[playerid][pGYMMember] = pData[playerid][pGYMMemberTime] = 0;
        }
    }
	if(pData[playerid][pVip] > 0)
	{
		if(pData[playerid][pVipTime] != 0 && pData[playerid][pVipTime] <= gettime())
		{
			SendClientMessageEx(playerid, COLOR_ARWIN, "VIP: "YELLOW_E"Maaf, Level VIP player anda sudah habis! sekarang anda adalah player biasa!");
			pData[playerid][pVip] = 0;
			pData[playerid][pVipTime] = -1;
		}
	}
	if(pData[playerid][pExitJob] != 0 && pData[playerid][pExitJob] <= gettime()) pData[playerid][pExitJob] = 0;
	if(pData[playerid][pDriveLic] > 0)
	{
		if(pData[playerid][pDriveLicTime] != 0 && pData[playerid][pDriveLicTime] <= gettime())
		{
			SendClientMessageEx(playerid, COLOR_RED, "LISENCE: "YELLOW_E"The validity period of your vehicle license has expired!");
			pData[playerid][pDriveLic] = 2;
			pData[playerid][pDriveLicTime] = 0;
		}
	}
	if(pData[playerid][pTruckerLic] > 0)
	{
		if(pData[playerid][pTruckerLicTime] != 0 && pData[playerid][pTruckerLicTime] <= gettime())
		{
			SendClientMessageEx(playerid, COLOR_RED, "LISENCE: "YELLOW_E"The validity period of your trucker license has expired!");
			pData[playerid][pTruckerLic] = 2;
			pData[playerid][pTruckerLicTime] = 0;
		}
	}
	if(pData[playerid][pLumberLic] > 0)
	{
		if(pData[playerid][pLumberLicTime] != 0 && pData[playerid][pLumberLicTime] <= gettime())
		{
			SendClientMessageEx(playerid, COLOR_RED, "LISENCE: "YELLOW_E"The validity period of your lumberjack license has expired!");
			pData[playerid][pLumberLic] = 2;
			pData[playerid][pLumberLicTime] = 0;
		}
	}
	if(pData[playerid][pGunLic] > 0)
	{
		if(pData[playerid][pGunLicTime] != 0 && pData[playerid][pGunLicTime] <= gettime())
		{
			SendClientMessageEx(playerid, COLOR_RED, "LISENCE: "YELLOW_E"The validity period of your weapon license has expired!");
			pData[playerid][pGunLic] = 2;
			pData[playerid][pGunLicTime] = 0;
		}
	}
	if(pData[playerid][pFlyLic] > 0)
	{
		if(pData[playerid][pFlyLicTime] != 0 && pData[playerid][pFlyLicTime] <= gettime())
		{
			SendClientMessageEx(playerid, COLOR_RED, "LISENCE: "YELLOW_E"The validity period of your flying license has expired!");
			pData[playerid][pFlyLic] = 2;
			pData[playerid][pFlyLicTime] = 0;
		}
	}
	if(pData[playerid][pBoatLic] > 0)
	{
		if(pData[playerid][pBoatLicTime] != 0 && pData[playerid][pBoatLicTime] <= gettime())
		{
			SendClientMessageEx(playerid, COLOR_RED, "LISENCE: "YELLOW_E"The validity period of your boating license has expired!");
			pData[playerid][pBoatLic] = 2;
			pData[playerid][pBoatLicTime] = 0;
		}
	}
	if(DelayPlayer[playerid][DelayBusDriver] > 0)
	{
        if(--DelayPlayer[playerid][DelayBusDriver] == 0) SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOB: "YELLOW_E"You can now work as a bus driver again!");
	}
	if(DelayPlayer[playerid][DelaySweeper] > 0)
	{
        if(--DelayPlayer[playerid][DelaySweeper] == 0) SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOB: "YELLOW_E"}You can now work as a street cleaner again!");
	}
	if(DelayPlayer[playerid][DelayCourier] > 0)
	{
        if(--DelayPlayer[playerid][DelayCourier] == 0) SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOB: "YELLOW_E"You can now work as a courier again!!");				
	}
	if(DelayPlayer[playerid][DelayHauling] > 0)
	{
        if(--DelayPlayer[playerid][DelayHauling] == 0) SendClientMessageEx(playerid ,COLOR_ARWIN,"JOB: "YELLOW_E"You can now work as a hauling again!");				
	}
	if(DelayPlayer[playerid][DelayLumberJack] > 0)
	{
        if(--DelayPlayer[playerid][DelayLumberJack] == 0) SendClientMessageEx(playerid ,COLOR_ARWIN,"JOB: "YELLOW_E"You can now work as a lumber jack again!");				
	}
	if(DelayPlayer[playerid][DelayTrashmaster] > 0)
	{
        if(--DelayPlayer[playerid][DelayTrashmaster] == 0) SendClientMessage(playerid, COLOR_ARWIN, "JOB: "YELLOW_E"You can now work as a trash collector again!");			
	}
	if(DelayPlayer[playerid][DelayForklift] > 0)
	{
        if(--DelayPlayer[playerid][DelayForklift] == 0) SendClientMessage(playerid, COLOR_ARWIN, "JOB: "YELLOW_E"You can now work as a forklift again!");			
	}
	if(DelayPlayer[playerid][DelayDelivery] > 0)
	{
        if(--DelayPlayer[playerid][DelayDelivery] == 0) SendClientMessage(playerid, COLOR_ARWIN, "JOB: "YELLOW_E"You can now work as a crate delivery again!!");		
	}
	if(DelayPlayer[playerid][DelayFishing] > 0)
	{
		if(--DelayPlayer[playerid][DelayFishing] == 0) SendClientMessage(playerid, COLOR_ARWIN, "JOB: "YELLOW_E"You can now work as a fishing again!!");		
	}
	if(DelayPlayer[playerid][DelayAdvertisement] > 0)
	{
        if(--DelayPlayer[playerid][DelayAdvertisement] == 0) DelayPlayer[playerid][DelayAdvertisement] = 0;	
	}
	return 1;
}

ptask AntiCheat_Checker[1000](playerid)
{	
	if(pData[playerid][IsLoggedIn])
	{
		new surfingvehicle = GetPlayerSurfingVehicleID(playerid);
		new Float:svx, Float:svy, Float:svz, Float:npx, Float:npy, Float:npz;
		GetVehiclePos(surfingvehicle, svx, svy, svz);
		GetPlayerPos(playerid, npx, npy, npz);
		new Float:surfing = (svy + svx + svz) - (npx + npy + npz);
		if((surfingvehicle != 65535) && (surfing  < -30 || surfing > 30))
		{
			// SendAdminMessage(COLOR_RED, "%s[%d] Possibly using surfing invisible cheat", ReturnName(playerid), playerid);
			// SendClientMessageEx(playerid, COLOR_ARWIN, "AdmCmd: %s was autokicked by BotCmd, reason: surfing invisible", ReturnName(playerid));
			// KickEx(playerid);
		}
		new SurfingObject = GetPlayerSurfingObjectID(playerid);
		new Float:XObject, Float:YObject, Float:ZObject;
		GetObjectPos(SurfingObject, XObject, YObject, ZObject);
		new Float:surfing2 = (XObject + YObject + ZObject) - (npx + npy + npz);
		if((SurfingObject != 65535) && (surfing2  < -30 || surfing2 > 30))
		{
			// SendAdminMessage(COLOR_RED, "%s[%d] Possibly using surfing invisible cheat", ReturnName(playerid), playerid);
			// SendClientMessageEx(playerid, COLOR_ARWIN, "AdmCmd: %s was autokicked by BotCmd, reason: surfing invisible", ReturnName(playerid));
			// KickEx(playerid);
		}
		//Flyhack anti cheat
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			switch(GetPlayerAnimationIndex(playerid))
			{
				case 958, 959, 1538, 161, 1539, 1543, 373:
				{
					new
						Float:z,
						Float:vx,
						Float:vy,
						Float:vz;

					GetPlayerPos(playerid, z, z, z);
					GetPlayerVelocity(playerid, vx, vy, vz);

					if((z > 20.0) && (0.9 <= floatsqroot((vx * vx) + (vy * vy) + (vz * vz)) <= 1.9) && pData[playerid][pAdmin] < 5)
					{
						SendAdminMessage(TOMATO, "BotCmd: %s was kicked by BOT, reason: Flying hacks", ReturnName(playerid));
						KickEx(playerid);
					}
				}
			}
		}
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK && pData[playerid][pAdmin] < 1)
		{
			SendAdminMessage(TOMATO, "BotCmd: %s was kicked by BOT. Reason: using jetpack hack.", ReturnName(playerid));
			KickEx(playerid);
		}
		AnticheatCheck(playerid);
	}	
	return 1;
}

ptask PlayerHospital_Update[1000](playerid)
{
	if(PlayerPause[playerid] > 0) return 0;
	if(!pData[playerid][IsLoggedIn]) return 0;
	if(pData[playerid][pInjured] == 1 && pData[playerid][pHospital] != 1)
    {
		if(!IsPlayerInAnyVehicle(playerid) && GetPlayerAnimationIndex(playerid) != 0) {
			TogglePlayerControllable(playerid, true);
			// ApplyAnimation(playerid, "PED", "BIKE_fall_off", 4.0, 0, 0, 0, 1, 0, 1);
			ApplyAnimation(playerid, "PED", "KO_SKID_FRONT", 4.0, 0, 0, 0, 1, 0, 1);
			TextDrawShowForPlayer(playerid, injuredtextdraw);
		}
		if(GetPVarInt(playerid, "GiveUptime") == -1) SetPVarInt(playerid, "GiveUptime", gettime());
		if(GetPVarInt(playerid,"GiveUptime"))
        {
            if((gettime()-GetPVarInt(playerid, "GiveUptime")) > 100)
            {
                SendCustomMessage(playerid, "DEATH", "Now you can spawn, type "YELLOW_E"'/accept death' "WHITE_E"for spawn to hospital.");
                SetPVarInt(playerid, "GiveUptime", 0);
            }
        }
    }
	return 1;
}

ptask PlayerUsePills[1000](playerid)
{
	if(PlayerPause[playerid] > 0) return 0;
	if(!pData[playerid][IsLoggedIn]) return 0;
	if(pData[playerid][pUsePills] > 0)
	{
		if(--pData[playerid][pUsePills] == 0) SendCustomMessage(playerid, "PILLS", ""YELLOW_E"Anda bisa mengkonsumsi obat lagi sekarang.");
	}
	new Float:health;
	GetPlayerHealth(playerid, health);

	if(pData[playerid][pHunger] <= 10 || pData[playerid][pEnergy] <= 10)
	{
		if(pData[playerid][pMigrainRate] > 1 || pData[playerid][pFever] > 0) SetPlayerDrunkLevel(playerid, 5000*(pData[playerid][pFever]+1));

		if(pData[playerid][pFever])
		{
			if(++pData[playerid][pFeverTime] > 10)
			{
				//new pengurangan;

				switch(pData[playerid][pFever])
				{
					case 1: SetPlayerDrunkLevel(playerid, 5000*(pData[playerid][pFever]+1));
					case 2: SetPlayerDrunkLevel(playerid, 5000*(pData[playerid][pFever]+1));
					case 3: SetPlayerDrunkLevel(playerid, 5000*(pData[playerid][pFever]+1));
				}
				//SetPlayerHealth(playerid, health - pengurangan); diganti player drunk
				pData[playerid][pFeverTime] = 0;
			}
		}

		if(++pData[playerid][pMigrainTime] >= 300)
		{
			if(pData[playerid][pFever]) 
			{
				if(pData[playerid][pFever] <= 2)
				{
					SendCustomMessage(playerid, "SICK", "You got High Fever, this is dangerous disease you should go to doctor now!");
					pData[playerid][pFever] ++;
				}
			}

			if(!pData[playerid][pFever] && pData[playerid][pMigrainRate] < 4)
			{
				pData[playerid][pMigrainRate] ++;

				if(pData[playerid][pMigrainRate] < 3)
					SendCustomMessage(playerid, "SICK", "You got headache, go check to the doctor for cure your diseases.");

				if(pData[playerid][pMigrainRate] == 4) {
					SendCustomMessage(playerid, "SICK", "You got High Fever, this is dangerous disease you should go to doctor now!");
					pData[playerid][pFever] ++;
					pData[playerid][pMigrainRate] = 0;
				}
			}
			pData[playerid][pMigrainTime] = 0;
		}
	}
	else  SetPlayerDrunkLevel(playerid, 0);
	if(pData[playerid][pDrugUsed] != 0 && pData[playerid][pDrugTime] > 0)
    {
        pData[playerid][pDrugTime]--;
        if(!pData[playerid][pDrugTime])
        {
            new getime[3];
            gettime(getime[0], getime[1], getime[2]);
            SetPlayerTime(playerid, getime[0], getime[1]);

            // SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) - 500);
            //hilangin efek layar merah
            SetPlayerWeather(playerid, current_weather);

            pData[playerid][pDrugUsed] = 0;
            SendCustomMessage(playerid, "DRUG", "The effects from the drugs have subsided.");
        }
    }
	return 1;
}

ptask Player_Hunger[1000](playerid)
{
	if(PlayerPause[playerid] > 0) return 0;
	if(!pData[playerid][IsLoggedIn]) return 0;
	if(pData[playerid][pInjured] == 0 && pData[playerid][pGender] != 0 && pData[playerid][pAdminDuty] == 0 && pData[playerid][pJail] == 0) //Pengurangan Data
	{
		new
            animidx = GetPlayerAnimationIndex(playerid),
            k,
            ud,
            lr,
            Float:adjustment,
            Float:adjustment2;

        GetPlayerKeys(playerid, k, ud, lr);

        if(animidx == 43) {
            adjustment = (0.04 * 0.2); // Sitting
            adjustment2 = (0.03 * 0.2); // Sitting
        } else if(animidx == 1159) {
            adjustment = (0.04 * 1.1); // Crouching
            adjustment2 = (0.03 * 1.1); // Crouching
        } else if(animidx == 1195) {
            adjustment = (0.04 * 3.2); // Jumping
            adjustment2 = (0.03 * 3.2); // Jumping
        } else if(animidx == 1231) {
            if(k & KEY_WALK) {
                adjustment = (0.04 * 1.2); // Walking
                adjustment2 = (0.03 * 1.2); // Walking
            } else if(k & KEY_SPRINT) {
                adjustment = (0.04 * 2.2); // Sprinting
                adjustment2 = (0.03 * 2.2); // Sprinting
            } else if(k & KEY_JUMP) {
                adjustment = (0.04 * 3.2); // Jumping
                adjustment2 = (0.03 * 3.2); // Jumping
            } else {
                adjustment = (0.04 * 2.0); // Jogging
                adjustment2 = (0.03 * 2.0); // Jogging
            }
        } else {
            adjustment = 0.04;
            adjustment2 = 0.03;
        }

        adjustment *= 0.2;
        adjustment2 *= 0.2;
		SetPlayerHunger(playerid, pData[playerid][pHunger]-adjustment2);
        SetPlayerEnergy(playerid, pData[playerid][pEnergy]-adjustment);
	}
	return 1;
}

task VehicleUpdate[40000]()
{
	for (new i = 1; i != MAX_VEHICLES; i ++) if(IsEngineVehicle(i) && GetEngineStatus(i))
    {
        if(GetVehicleFuel(i) > 0)
        {
			new fuel = GetVehicleFuel(i);
            SetVehicleFuel(i, fuel - 2);

            if(GetVehicleFuel(i) >= 1 && GetVehicleFuel(i) <= 200)
            {
               SendClientMessageEx(GetVehicleDriver(i), COLOR_ARWIN,"FUEL: "RED_E"This vehicle is low on fuel. You must visit a fuel station!");
            }
        }
        if(GetVehicleFuel(i) <= 0)
        {
            SetVehicleFuel(i, 0);
            SwitchVehicleEngine(i, false);
        }
    }
	foreach(new ii : PVehicles)
	{
		if(IsValidVehicle(pvData[ii][cVeh]))
		{
			if(pvData[ii][cRent] != 0 && pvData[ii][cRent] <= gettime())
			{
				foreach(new pid : Player)  if (pvData[ii][cOwner] == pData[pid][pID]) pData[pid][pRents] = -1;
				pvData[ii][cRent] = 0;
				new query[128];
				mysql_format(g_SQL, query, sizeof(query), "DELETE FROM vehicle WHERE id = '%d'", pvData[ii][cID]);
				mysql_tquery(g_SQL, query);
				if(IsValidVehicle(pvData[ii][cVeh])) DestroyVehicle(pvData[ii][cVeh]);
				Iter_SafeRemove(PVehicles, ii, ii);
			}
		}
		if(pvData[ii][cClaimTime] != 0 && pvData[ii][cClaimTime] <= gettime()) pvData[ii][cClaimTime] = 0;
	}
	return 1;
}

ptask PlayerVehicleUpdate[200](playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(IsValidVehicle(vehicleid))
	{
		if(!GetEngineStatus(vehicleid) && IsEngineVehicle(vehicleid)) SwitchVehicleEngine(vehicleid, false);
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new Float:fHealth;
			GetVehicleHealth(vehicleid, fHealth);
			if(IsValidVehicle(vehicleid) && fHealth <= 350.0)
			{
				SetValidVehicleHealth(vehicleid, 300.0);
				SwitchVehicleEngine(vehicleid, false);
			}
		}	
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			foreach(new vehicle : VehicleData) if(VehicleData[vehicle][Vehicle] == vehicleid && VehicleData[vehicle][Storage][0] > 0) {
				TextDrawShowForPlayer(playerid, PlayerCrateTD);
				PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
				PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
				new String2[212];
				format(String2,sizeof(String2),"Product Stock~n~%d units", VehicleData[vehicle][Storage][0]);
				PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
			}
			if(pData[playerid][pHBEMode] == 1)
			{
				new Float:fDamage, fFuel, str[64];
				new Float:FuelBar, Float:HealthBar;

				fFuel = GetVehicleFuel(vehicleid);
				GetVehicleHealth(vehicleid, fDamage);

				if(fDamage <= 350.0) fDamage = 0.0;
				else if(fDamage > 1000.0) fDamage = 1000.0;

				fFuel = GetVehicleFuel(vehicleid);

				if(fFuel < 0) fFuel = 0;
				else if(fFuel > 1000) fFuel = 1000;

				format(str, sizeof(str), "%s", GetVehicleName(vehicleid));
				PlayerTextDrawSetString(playerid, SAVNameTD[playerid], str);

				format(str, sizeof(str), "%.0f", GetVehicleSpeed(vehicleid) / 2);
				PlayerTextDrawSetString(playerid, SAPVSpeedTD[playerid], str);

				FuelBar = fFuel / 10 * -42.0/100;
				PlayerTextDrawTextSize(playerid, SAVFuelTD[playerid], 7.0, FuelBar);
				PlayerTextDrawShow(playerid, SAVFuelTD[playerid]);

				HealthBar = fDamage / 10 * -42.0/100;
				PlayerTextDrawTextSize(playerid, SAVHealthTD[playerid], 7.0, HealthBar);
				PlayerTextDrawShow(playerid, SAVHealthTD[playerid]);
			}
			if(pData[playerid][pHBEMode] == 2)
			{
				new Float:fDamage, fFuel;
				new fuelstr[64], damagestr[62], speedstr[62], veh[20];

				GetVehicleHealth(vehicleid, fDamage);

				if(fDamage <= 350.0) fDamage = 0.0;
				else if(fDamage > 1000.0) fDamage = 1000.0;

				// fSpeed = GetVehicleSpeed(vehicleid);
				fFuel = GetVehicleFuel(vehicleid);

				// TextDrawShowForPlayer(playerid, simpletd[2]);
				// TextDrawColor(simpletd[2], ConvertDamageVehColor(fSpeed));
				PlayerTextDrawShow(playerid, JGVFUEL[playerid]);
				PlayerTextDrawColor(playerid, JGVFUEL[playerid], ConvertFuelVehColor(fFuel));
				PlayerTextDrawShow(playerid, JGVHP[playerid]);
				PlayerTextDrawColor(playerid, JGVHP[playerid], ConvertDamageVehColor(fDamage));

				format(speedstr, sizeof(speedstr), "~g~%.0f ~w~mph", GetVehicleSpeed(vehicleid) / 2);
				PlayerTextDrawSetString(playerid, JGVSPEED[playerid], speedstr);

				format(fuelstr, sizeof(fuelstr), "%s%d%", veh, fFuel / 10);
				PlayerTextDrawSetString(playerid, JGVFUEL[playerid], fuelstr);

				if(!GetEngineStatus(vehicleid)) format(damagestr, sizeof(damagestr), "~r~off");
				else format(damagestr, sizeof(damagestr), "%s%.0f%", veh, fDamage / 10);
				PlayerTextDrawSetString(playerid, JGVHP[playerid], damagestr);

			}
			if(pData[playerid][pHBEMode] == 3)
			{
				new Float:fDamage, fFuel;
				new  str[64];

				GetVehicleHealth(vehicleid, fDamage);

				if(fDamage <= 350.0) fDamage = 0.0;
				else if(fDamage > 1000.0) fDamage = 1000.0;

				fFuel = GetVehicleFuel(vehicleid);

				if(fFuel < 0) fFuel = 0;
				else if(fFuel > 1000) fFuel = 1000;

				format(str, sizeof(str), "%.0f", GetVehicleSpeed(vehicleid) / 2);
				PlayerTextDrawSetString(playerid, VSpeedTD[playerid], str);

				format(str, sizeof(str), "%dL", fFuel / 10);
				PlayerTextDrawSetString(playerid, VFuelTD[playerid], str);

				format(str, sizeof(str), "%.0f%", fDamage / 10);
				PlayerTextDrawSetString(playerid, VHealthTD[playerid], str);

				format(str, sizeof(str), "%s", GetVehicleName(vehicleid));
				PlayerTextDrawSetString(playerid, VNameTD[playerid], str);

			}
		}
	}
	return 1;
}

ptask PlayerTD_Update[1000](playerid)
{
	if(!pData[playerid][IsLoggedIn]) return 0;
	if(PlayerPause[playerid] > 0) return 0;
	if(pData[playerid][pHBEMode] == 1)
	{
		new Float:HungerBar, Float:ThristBar;
		if(IsPlayerInEvent(playerid))
	    {
	    	PlayerTextDrawTextSize(playerid, SAPHungerTD[playerid], 0, 0);
	    	PlayerTextDrawTextSize(playerid, SAPThirstTD[playerid], 0, 0);
	    }
		HungerBar = pData[playerid][pHunger] * 53.0/100;
	    PlayerTextDrawTextSize(playerid, SAPHungerTD[playerid], HungerBar, 8.0);
	    PlayerTextDrawShow(playerid, SAPHungerTD[playerid]);

	    ThristBar = pData[playerid][pEnergy] * 53.0/100;
	    PlayerTextDrawTextSize(playerid, SAPThirstTD[playerid], ThristBar, 8.0);
	    PlayerTextDrawShow(playerid, SAPThirstTD[playerid]);
	}
	if(pData[playerid][pHBEMode] == 2)
	{
		PlayerTextDrawShow(playerid, JGHUNGER[playerid]);
		PlayerTextDrawColor(playerid, JGHUNGER[playerid], ConvertTdColor(floatround(pData[playerid][pHunger])));
		PlayerTextDrawShow(playerid, JGTHIRST[playerid]);
		PlayerTextDrawColor(playerid, JGTHIRST[playerid], ConvertTdColor(floatround(pData[playerid][pEnergy])));

		PlayerTextDrawSetString(playerid, JGHUNGER[playerid], sprintf("%.0f%", pData[playerid][pHunger]));

		PlayerTextDrawSetString(playerid, JGTHIRST[playerid], sprintf("%.0f%", pData[playerid][pEnergy]));	
	}
	if(pData[playerid][pHBEMode] == 3)
	{
		new Float:health, Float:armor, str[64];
		GetPlayerHealth(playerid, health);
		GetPlayerArmour(playerid, armor);

		if(IsPlayerInEvent(playerid))
	    {
	    	PlayerTextDrawTextSize(playerid, PHungerTD[playerid], 0, 0);
	    	PlayerTextDrawTextSize(playerid, PThirstTD[playerid], 0, 0);
	    }
		format(str, sizeof(str), "%.0f%", pData[playerid][pHunger]);
		PlayerTextDrawSetString(playerid, PHungerTD[playerid], str);

		format(str, sizeof(str), "%.0f%", pData[playerid][pEnergy]);
		PlayerTextDrawSetString(playerid, PThirstTD[playerid], str);
	}
    // Ensure pSpec is a valid player ID before using it as an index.
    // INVALID_PLAYER_ID is typically -1, so we also check for a valid range (0 to MAX_PLAYERS-1)
    if(pData[playerid][pSpec] != INVALID_PLAYER_ID && pData[playerid][IsLoggedIn] && pData[playerid][pSpec] >= 0 && pData[playerid][pSpec] < MAX_PLAYERS) {
       	new userid = pData[playerid][pSpec], Float:healthp, Float:armor;
        GetPlayerHealth(userid, healthp);
        GetPlayerArmour(userid, armor);

        PlayerTextDrawSetString(playerid, SpecTD[playerid][1], sprintf("~g~%s (%d)~n~~w~Money: ~b~%s~n~~w~Health: ~b~%.1f~n~~w~AP: ~b~%.1f~n~~w~Int: ~b~%d~n~~w~Vw: ~b~%d~n~~w~Fps: ~b~%d", ReturnName(userid), userid, FormatMoney(pData[userid][pMoney]), healthp, armor, GetPlayerInterior(userid), GetPlayerVirtualWorld(userid), GetPlayerFps(userid)));
    }
	return 1;
}

ptask PlayerData_WeaponAttach[1000](playerid)
{
	//Weapon Atth
	if(NetStats_GetConnectedTime(playerid) - WeaponTick[playerid] >= 250 && !IsPlayerInEvent(playerid))
	{
		static weaponid, ammo, objectslot, count, index;
 
		for (new i; i < 13; i++)
		{
			GetPlayerWeaponData(playerid, i, weaponid, ammo);
			if (weaponid && ammo) {
                if (weaponid >= 22 && weaponid <= 33) index = weaponid - 22;
                else if (weaponid >= 2 && weaponid <= 15) index = weaponid + 15;
			
				if (weaponid && ammo && !WeaponSettings[playerid][index][Hidden] && IsWeaponWearable(weaponid) && EditingWeapon[playerid] != weaponid)
				{
					objectslot = GetWeaponObjectSlot(weaponid);
					if (GetPlayerWeapon(playerid) != weaponid)
					{
						SetPlayerAttachedObject(playerid, objectslot, GetWeaponModel(weaponid), WeaponSettings[playerid][index][Bone], WeaponSettings[playerid][index][Position][0], WeaponSettings[playerid][index][Position][1], WeaponSettings[playerid][index][Position][2], WeaponSettings[playerid][index][Position][3], WeaponSettings[playerid][index][Position][4], WeaponSettings[playerid][index][Position][5], 1.0, 1.0, 1.0);
						gWeaponAttachedObject[playerid][objectslot] = true;
					}
					else if(gWeaponAttachedObject[playerid][objectslot] && IsPlayerAttachedObjectSlotUsed(playerid, objectslot))
					{
						RemovePlayerAttachedObject(playerid, objectslot);
						gWeaponAttachedObject[playerid][objectslot] = false;
					}
				}
			}
		}
		for (new i = 5; i <= 8; i++) if (gWeaponAttachedObject[playerid][i] && IsPlayerAttachedObjectSlotUsed(playerid, i))
        {
            count = 0;
            for (new j = 2; j <= 38; j ++) if (PlayerHasWeapon(playerid, j) && GetWeaponObjectSlot(j) == i) count++;
            if (!count)
			{
				RemovePlayerAttachedObject(playerid, i);
				gWeaponAttachedObject[playerid][i] = false;
			}
        }
		WeaponTick[playerid] = NetStats_GetConnectedTime(playerid);
	}
	if(pData[playerid][pSpawned] == 1)
    {
		if(pData[playerid][pAdmin] < 1  && !IsPlayerInEvent(playerid))
		{
			if(GetPlayerWeapon(playerid) != pData[playerid][pWeapon])
			{
				pData[playerid][pWeapon] = GetPlayerWeapon(playerid);
				
				if(pData[playerid][pWeapon] >= 1 && pData[playerid][pWeapon] <= 45 && pData[playerid][pWeapon] != 40 && pData[playerid][pWeapon] != 2 && GetWeapon(playerid)  != GetPlayerWeapon(playerid))
				{
					SendAdminMessage(COLOR_RED, "%s(%d) has possibly used weapon hacks (%s), Please to check /spec this player first!", ReturnName(playerid), playerid, ReturnWeaponName(pData[playerid][pWeapon]));
					if(pData[playerid][pWeapon] >= 34 && pData[playerid][pWeapon] <= 38)
					    RefreshWeapon(playerid); //Reload old weapons only for heavy/cheat weapons
				}
			}
		}
    }
	return 1;
}

ptask PlayerData_WeaponCheck[1000](playerid)
{
	if(pData[playerid][pAdmin] == 0 && !IsPlayerInEvent(playerid))
	{
		if(pData[playerid][pLevel] < 3)
		{
			if(GetPlayerWeapon(playerid) == 22 || GetPlayerWeapon(playerid) == 23 || GetPlayerWeapon(playerid) == 24 || GetPlayerWeapon(playerid) == 25 || GetPlayerWeapon(playerid) == 26 || GetPlayerWeapon(playerid) == 27 || GetPlayerWeapon(playerid) == 28 || GetPlayerWeapon(playerid) == 29 || GetPlayerWeapon(playerid) == 30
		    || GetPlayerWeapon(playerid) == 31 || GetPlayerWeapon(playerid) == 32 || GetPlayerWeapon(playerid) == 33 || GetPlayerWeapon(playerid) == 34 || GetPlayerWeapon(playerid) == 35 || GetPlayerWeapon(playerid) == 36)
			{
				Kick(playerid);
			}
		}
	    if(GetPlayerWeapon(playerid) == 34)
		{
		    ResetWeapons(playerid);
			new string[180];
			format(string,sizeof(string), "BotCmd: %s telah di banned dari server", ReturnName(playerid));
	  		SendClientMessageToAllEx(TOMATO, "%s Reason: Weapon Hack", string);  
	  		format(pData[playerid][pBanBy], 128, "%s", "[BOT]");
			format(pData[playerid][pBanReason], 128, "%s", "Weapon Hack");
			pData[playerid][pBanned] = 1;
			format(charData[playerid][cCharBanReason], 128, "Weapon Hack [BOT]");
			charData[playerid][cCharBan] = 1;
			Ban(playerid);
			KickEx(playerid);
		}
	    if(GetPlayerWeapon(playerid) == 35)
		{
		    ResetWeapons(playerid);
			new string[180];
			format(string,sizeof(string), "BotCmd: %s telah di banned dari server", ReturnName(playerid));
	  		SendClientMessageToAllEx(TOMATO, "%s Reason: Weapon Hack", string);  
	  		format(pData[playerid][pBanBy], 128, "%s", "[BOT]");
			format(pData[playerid][pBanReason], 128, "%s", "Weapon Hack");
			pData[playerid][pBanned] = 1;
			format(charData[playerid][cCharBanReason], 128, "Weapon Hack [BOT]");
			charData[playerid][cCharBan] = 1;
			Ban(playerid);
			KickEx(playerid);
		}
		if(GetPlayerWeapon(playerid) == 36)
		{
		    ResetWeapons(playerid);
			new string[180];
			format(string,sizeof(string), "BotCmd: %s telah di banned dari server", ReturnName(playerid));
	  		SendClientMessageToAllEx(TOMATO, "%s Reason: Weapon Hack", string);  
	  		format(pData[playerid][pBanBy], 128, "%s", "[BOT]");
			format(pData[playerid][pBanReason], 128, "%s", "Weapon Hack");
			pData[playerid][pBanned] = 1;
			format(charData[playerid][cCharBanReason], 128, "Weapon Hack [BOT]");
			charData[playerid][cCharBan] = 1;
			Ban(playerid);
			KickEx(playerid);
		}
		if(GetPlayerWeapon(playerid) == 37)
		{
		    ResetWeapons(playerid);
			new string[180];
			format(string,sizeof(string), "BotCmd: %s telah di banned dari server", ReturnName(playerid));
	  		SendClientMessageToAllEx(TOMATO, "%s Reason: Weapon Hack", string);  
	  		format(pData[playerid][pBanBy], 128, "%s", "[BOT]");
			format(pData[playerid][pBanReason], 128, "%s", "Weapon Hack");
			pData[playerid][pBanned] = 1;
			format(charData[playerid][cCharBanReason], 128, "Weapon Hack [BOT]");
			charData[playerid][cCharBan] = 1;
			Ban(playerid);
			KickEx(playerid);
		}
        if(GetPlayerWeapon(playerid) == 38)
		{
		    ResetWeapons(playerid);
			new string[180];
			format(string,sizeof(string), "BotCmd: %s telah di banned dari server", ReturnName(playerid));
	  		SendClientMessageToAllEx(TOMATO, "%s Reason: Weapon Hack", string);  
	  		format(pData[playerid][pBanBy], 128, "%s", "[BOT]");
			format(pData[playerid][pBanReason], 128, "%s", "Weapon Hack");
			pData[playerid][pBanned] = 1;
			format(charData[playerid][cCharBanReason], 128, "Weapon Hack [BOT]");
			charData[playerid][cCharBan] = 1;
			Ban(playerid);
			KickEx(playerid);
		}
		if(GetPlayerWeapon(playerid) == 39)
		{
		    ResetWeapons(playerid);
			new string[180];
			format(string,sizeof(string), "BotCmd: %s telah di banned dari server", ReturnName(playerid));
	  		SendClientMessageToAllEx(TOMATO, "%s Reason: Weapon Hack", string);  
	  		format(pData[playerid][pBanBy], 128, "%s", "[BOT]");
			format(pData[playerid][pBanReason], 128, "%s", "Weapon Hack");
			pData[playerid][pBanned] = 1;
			format(charData[playerid][cCharBanReason], 128, "Weapon Hack [BOT]");
			charData[playerid][cCharBan] = 1;
			Ban(playerid);
			KickEx(playerid);
		}
		if(GetPlayerWeapon(playerid) == 40)
		{
		    ResetWeapons(playerid);
			new string[180];
			format(string,sizeof(string), "BotCmd: %s telah di banned dari server", ReturnName(playerid));
	  		SendClientMessageToAllEx(TOMATO, "%s Reason: Weapon Hack", string);  
	  		format(pData[playerid][pBanBy], 128, "%s", "[BOT]");
			format(pData[playerid][pBanReason], 128, "%s", "Weapon Hack");
			pData[playerid][pBanned] = 1;
			format(charData[playerid][cCharBanReason], 128, "Weapon Hack [BOT]");
			charData[playerid][cCharBan] = 1;
			Ban(playerid);
			KickEx(playerid);
		}
		if(GetPlayerWeapon(playerid) == 32)
		{
		    ResetWeapons(playerid);
			new string[180];
			format(string,sizeof(string), "BotCmd: %s telah di banned dari server", ReturnName(playerid));
	  		SendClientMessageToAllEx(TOMATO, "%s Reason: Weapon Hack", string);  
	  		format(pData[playerid][pBanBy], 128, "%s", "[BOT]");
			format(pData[playerid][pBanReason], 128, "%s", "Weapon Hack");
			pData[playerid][pBanned] = 1;
			format(charData[playerid][cCharBanReason], 128, "Weapon Hack [BOT]");
			charData[playerid][cCharBan] = 1;
			Ban(playerid);
			KickEx(playerid);
		}
	}
	return 1;
}

task ELMTimer[125]()
{
	//loop to process ELM.
	for(new v = 1, x = GetVehiclePoolSize(); v <= x; v++)
	{
		if(pvData[v][vELM])
		{
			new panels, doors, lights, tires;
			GetVehicleDamageStatus(v, panels, doors, lights, tires);

			switch(Flash[v])
			{
				case 0: UpdateVehicleDamageStatus(v, panels, doors, 2, tires);
				case 1: UpdateVehicleDamageStatus(v, panels, doors, 5, tires);
				case 2: UpdateVehicleDamageStatus(v, panels, doors, 2, tires);
				case 3: UpdateVehicleDamageStatus(v, panels, doors, 4, tires);
				case 4: UpdateVehicleDamageStatus(v, panels, doors, 5, tires);
				case 5: UpdateVehicleDamageStatus(v, panels, doors, 4, tires);
			}
			if (Flash[v] >= 5) Flash[v] = 0;
			else Flash[v] ++;
		}
	}
	return 1;
}

ptask Player_BanUpdate[1000](playerid)
{
	if(pData[playerid][pWarn] >= 20)
	{
	    SendClientMessageToAllEx(TOMATO, "BotCmd: %s telah dibanned oleh BOT", ReturnName(playerid));
		SendClientMessageToAllEx(TOMATO, "Reason: Max Point");
		format(pData[playerid][pBanBy], 128, "%s", "[BOT]");
		format(pData[playerid][pBanReason], 128, "%s", "20 Warning Point");
		pData[playerid][pBanned] = 1;
		KickEx(playerid);
	}
    if(pData[playerid][pBanned] > 0)
	{
		new String[512];
		format(String, sizeof(String), ""YELLOW_E"Your Character account is blocked\n{00FFFF}Character: %s\n{00FFFF}Reason: "WHITE_E"%s\n{00FFFF}Banned by: "WHITE_E"%s\n"YELLOW_E"Please create an unban appeal in our discrod My Sunshine Roleplay", ReturnName(playerid), pData[playerid][pBanReason], pData[playerid][pBanBy]);
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Account Blocked", String," Ok","");
		KickEx(playerid);
	}
    return 1;
}

ptask TimeUpdate[1000](playerid)
{
	new String[256],str[256],mtext[20], direction[12],year,month,day,hours,minutes,seconds;
	getdate(year, month, day), gettime(hours, minutes, seconds);
	if(month == 1) { mtext = "Jan"; }
	else if(month == 2) { mtext = "Feb"; }
	else if(month == 3) { mtext = "Mar"; }
	else if(month == 4) { mtext = "Apr"; }
	else if(month == 5) { mtext = "May"; }
	else if(month == 6) { mtext = "Jun"; }
	else if(month == 7) { mtext = "Jul"; }
	else if(month == 8) { mtext = "Aug"; }
	else if(month == 9) { mtext = "Sep"; }
	else if(month == 10) { mtext = "Oct"; }
	else if(month == 11) { mtext = "Nov"; }
	else if(month == 12) { mtext = "Dec"; }
	new date[6];
	TimestampToDate(gettime(), date[2], date[1], date[0], date[3], date[4], date[5]);
	format(String, sizeof String, "%s, %d %s %d", GetWeekDay(date[0], date[1], date[2]), day, mtext, year);
	TextDrawSetString(Date, String);
	format(String, sizeof String, "%s%d:%s%d:%s%d", (hours < 10) ? ("0") : (""), hours, (minutes < 10) ? ("0") : (""), minutes, (seconds < 10) ? ("0") : (""), seconds);
	TextDrawSetString(Time, String);
	new Float:Xn;
	new Float:Yy;
	new Float:Zz;
	GetPlayerPos(playerid, Xn, Yy, Zz);
	GetPlayerDirection(playerid, direction);
	format(str, sizeof(str), "%s", GetLocation(Xn, Yy, Zz));
	PlayerTextDrawSetString(playerid, GPSLocation[playerid], str);
	return 1;
}

ptask UpdateTazerPlayer[1000](playerid)
{
	//SAPD Tazer/Taser
	UpdateTazer(playerid);
	return 1;
}

ptask UpdatePlayerInSpikePlayer[1000](playerid)
{
	//SAPD Road Spike
	CheckPlayerInSpike(playerid);
	return 1;
}

/*ptask MechanicUpdate[1000](playerid)
{
	if(IsPlayerInDynamicArea(playerid, MechanicArea[0]))
	{
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) // mengambil state driver
    	{
			SetVehicleSpeedCap(GetPlayerVehicleID(playerid), 45.0);
		}
	}
	else SetVehicleSpeedCap(GetPlayerVehicleID(playerid), -1);
	return 1;
}*/

// ptask IsPlayerLoginAfk[1000](playerid)
// {
// 	if(charData[playerid][cCharOn] == 1)
// 	{
// 		if(charData[playerid][cCharTime] > 0)
// 		{
// 			charData[playerid][cCharTime]--;
// 			if(charData[playerid][cCharTime] <= 1)
// 			{
// 				charData[playerid][cCharTime] = 0;
// 				SendCustomMessage(playerid, "AFK", "kamu telah dikick karena terlalu lama di menu login.");
// 				KickEx(playerid);
// 			}				
// 		}
// 	}
// 	return 1;
// }

ptask UpdateSKillPlayer[1000](playerid)
{
	//Trucker
	if(pData[playerid][pScoreTrucker] >= 50 && pData[playerid][pSkillTrucker] == 1)
	{
		pData[playerid][pSkillTrucker] = 2;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your trucker skills rising to 2");
	}
	else if(pData[playerid][pScoreTrucker] >= 150 && pData[playerid][pSkillTrucker] == 2)
	{
		pData[playerid][pSkillTrucker] = 3;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your trucker skills rising to 3");
	}
	else if(pData[playerid][pScoreTrucker] >= 200 && pData[playerid][pSkillTrucker] == 3)
	{
		pData[playerid][pSkillTrucker] = 4;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your trucker skills rising to 4");
	}
	else if(pData[playerid][pScoreTrucker] >= 300 && pData[playerid][pSkillTrucker] == 4)
	{
		pData[playerid][pSkillTrucker] = 5;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your trucker skills rising to 5");
	}
	//Fishing
	else if(pData[playerid][pScoreFishing] >= 100 && pData[playerid][pSkillFishing] == 1)
	{
		pData[playerid][pSkillFishing] = 2;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your fishing skills rising to 2");
	}
	//Mechanic
	else if(pData[playerid][pScoreMecha] >= 500 && pData[playerid][pSkillMecha] == 1)
	{
		pData[playerid][pSkillMecha] = 2;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your mechanic skills rising to 2");
	}
	else if(pData[playerid][pScoreMecha] >= 1500 && pData[playerid][pSkillMecha] == 2)
	{
		pData[playerid][pSkillMecha] = 3;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your mechanic skills rising to 3");
	}
	else if(pData[playerid][pScoreMecha] >= 2500 && pData[playerid][pSkillMecha] == 3)
	{
		pData[playerid][pSkillMecha] = 4;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your mechanic skills rising to 4");
	}
	else if(pData[playerid][pScoreMecha] >= 3500 && pData[playerid][pSkillMecha] == 4)
	{
		pData[playerid][pSkillMecha] = 5;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your mechanic skills rising to 5");
	}
	//Farmer
	else if(pData[playerid][pScoreFarmer] >= 1500 && pData[playerid][pSkillFarmer] == 1)
	{
		pData[playerid][pSkillFarmer] = 2;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your farmer skills rising to 2");
	}
	else if(pData[playerid][pScoreFarmer] >= 3500 && pData[playerid][pSkillFarmer] == 2)
	{
		pData[playerid][pSkillFarmer] = 3;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your farmer skills rising to 3");
	}
	else if(pData[playerid][pScoreFarmer] >= 6500 && pData[playerid][pSkillFarmer] == 3)
	{
		pData[playerid][pSkillFarmer] = 4;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your farmer skills rising to 4");
	}
	else if(pData[playerid][pScoreFarmer] >= 8500 && pData[playerid][pSkillFarmer] == 4)
	{
		pData[playerid][pSkillFarmer] = 5;
		SendCustomMessage(playerid, "SKILL", ""YELLOW_E"Congratulations on your farmer skills rising to 5");
	}
	return 1;
}
