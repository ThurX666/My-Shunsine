#include <YSI\y_hooks>

hook OnPlayerConnect(playerid) {
	KerjaBusCD[playerid] = -1;
	KerjaBus[playerid] = -1;
	TimerBus[playerid] = -1;
	BusLaps[playerid] = -1;
	return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
	new engine, lights, alarm, doors, bonnet, boot, objective;
	if(IsABusCDVeh(vehicleid) && KerjaBusCD[playerid] == 1) {
		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, 0);
		if(BusCDSteps[playerid][0] > 0) {
			switch(BusRuteCD[BusCDSteps[playerid][0]][bus_stop]) {
				case 0: SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][0]][bus_posx], BusRuteCD[BusCDSteps[playerid][0]][bus_posy], BusRuteCD[BusCDSteps[playerid][0]][bus_posz], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posz], 5);
				case 1: SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][0]][bus_posx], BusRuteCD[BusCDSteps[playerid][0]][bus_posy], BusRuteCD[BusCDSteps[playerid][0]][bus_posz], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posz], 2);
				case 2: SetPlayerRaceCheckpoint(playerid, 1, BusRuteCD[BusCDSteps[playerid][0]][bus_posx], BusRuteCD[BusCDSteps[playerid][0]][bus_posy], BusRuteCD[BusCDSteps[playerid][0]][bus_posz], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posz], 5);
			}
		}
		if(BusCDSteps[playerid][1] > 0) {
			switch(BusRuteCD[BusCDSteps[playerid][1]][bus_stop]) {
				case 0: SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][1]][bus_posx], BusRuteCD[BusCDSteps[playerid][1]][bus_posy], BusRuteCD[BusCDSteps[playerid][1]][bus_posz], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posz], 5);
				case 1: SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][1]][bus_posx], BusRuteCD[BusCDSteps[playerid][1]][bus_posy], BusRuteCD[BusCDSteps[playerid][1]][bus_posz], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posz], 2);
				case 2: SetPlayerRaceCheckpoint(playerid, 1, BusRuteCD[BusCDSteps[playerid][1]][bus_posx], BusRuteCD[BusCDSteps[playerid][1]][bus_posy], BusRuteCD[BusCDSteps[playerid][1]][bus_posz], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posz], 5);
			}
		}
		
	}
	if(IsABusABVeh(vehicleid) && KerjaBus[playerid] == 1) {
		if(BusSteps[playerid][0] > 0) {
			switch(BusRuteAB[BusSteps[playerid][0]][bus_stop]) {
				case 0: SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][0]][bus_posx], BusRuteAB[BusSteps[playerid][0]][bus_posy], BusRuteAB[BusSteps[playerid][0]][bus_posz], BusRuteAB[BusSteps[playerid][0]+1][bus_posx], BusRuteAB[BusSteps[playerid][0]+1][bus_posy], BusRuteAB[BusSteps[playerid][0]+1][bus_posz], 5);
				case 1: SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][0]][bus_posx], BusRuteAB[BusSteps[playerid][0]][bus_posy], BusRuteAB[BusSteps[playerid][0]][bus_posz], BusRuteAB[BusSteps[playerid][0]+1][bus_posx], BusRuteAB[BusSteps[playerid][0]+1][bus_posy], BusRuteAB[BusSteps[playerid][0]+1][bus_posz], 2);
				case 2: SetPlayerRaceCheckpoint(playerid, 1, BusRuteAB[BusSteps[playerid][0]][bus_posx], BusRuteAB[BusSteps[playerid][0]][bus_posy], BusRuteAB[BusSteps[playerid][0]][bus_posz], BusRuteAB[BusSteps[playerid][0]+1][bus_posx], BusRuteAB[BusSteps[playerid][0]+1][bus_posy], BusRuteAB[BusSteps[playerid][0]+1][bus_posz], 5);
			}
		}
		else if(BusSteps[playerid][1] > 0) {
			switch(BusRuteAB[BusSteps[playerid][1]][bus_stop]) {
				case 0: SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][1]][bus_posx], BusRuteAB[BusSteps[playerid][1]][bus_posy], BusRuteAB[BusSteps[playerid][1]][bus_posz], BusRuteAB[BusSteps[playerid][1]+1][bus_posx], BusRuteAB[BusSteps[playerid][1]+1][bus_posy], BusRuteAB[BusSteps[playerid][1]+1][bus_posz], 5);
				case 1: SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][1]][bus_posx], BusRuteAB[BusSteps[playerid][1]][bus_posy], BusRuteAB[BusSteps[playerid][1]][bus_posz], BusRuteAB[BusSteps[playerid][1]+1][bus_posx], BusRuteAB[BusSteps[playerid][1]+1][bus_posy], BusRuteAB[BusSteps[playerid][1]+1][bus_posz], 2);
				case 2: SetPlayerRaceCheckpoint(playerid, 1, BusRuteAB[BusSteps[playerid][1]][bus_posx], BusRuteAB[BusSteps[playerid][1]][bus_posy], BusRuteAB[BusSteps[playerid][1]][bus_posz], BusRuteAB[BusSteps[playerid][1]+1][bus_posx], BusRuteAB[BusSteps[playerid][1]+1][bus_posy], BusRuteAB[BusSteps[playerid][1]+1][bus_posz], 5);
			}
		}
		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, 0);
		
	}
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
	if(oldstate == PLAYER_STATE_DRIVER) {
		if(IsABusABVeh(pData[playerid][pLastCar]) && KerjaBus[playerid] == 1) {
			TimerBus[playerid] = 31;
			SetVehicleParamsForPlayer(pData[playerid][pLastCar],playerid,1,0);
			return 1;
		}
		if(IsABusCDVeh(pData[playerid][pLastCar]) && KerjaBusCD[playerid] == 1) {
			TimerBus[playerid] = 31;
			SetVehicleParamsForPlayer(pData[playerid][pLastCar],playerid,1,0);
			return 1;
		}
	}
	if(newstate == PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_PASSENGER) {
		if(IsABusCDVeh(GetPlayerVehicleID(playerid)) && KerjaBusCD[playerid] == -1)
		{
			if (pData[playerid][pFaction] != 0) {
				RemovePlayerFromVehicle(playerid);	
				Error(playerid, "Kamu anggota faction, tidak bekerja jobs/sidejob.");
				return 1;
			}

			new String[212], S3MP4K[212];
			if(DelayPlayer[playerid][DelayBusDriver] == 0)
			{
				strcat(S3MP4K, "Route\tPayout\n");
				format(String, sizeof(String), "{00FFFF}Route D: Blueberry - Flint Country\t{33AA33}$245.00\n");
				strcat(S3MP4K, String);
				format(String, sizeof(String), "{00FFFF}Route C: Palomino - Montgomery\t{33AA33}$285.00\n");
				strcat(S3MP4K, String);
				Dialog_Show(playerid, DialogBusCD, DIALOG_STYLE_TABLIST_HEADERS, "Sidejob: Bus Driver", S3MP4K, "Select", "Cancel");
			}
			else
			{
				format(String, sizeof(String),"ERROR: Kamu harus menunggu %d Menit untuk menjadi Bus Driver", DelayPlayer[playerid][DelayBusDriver]/60);
				SendClientMessage(playerid, COLOR_GRAD2, String);
				RemovePlayerFromVehicle(playerid);		
			}
		}
		if(IsABusABVeh(GetPlayerVehicleID(playerid)) && KerjaBus[playerid] == -1)
		{
			new String[212], S3MP4K[212];
			if(DelayPlayer[playerid][DelayBusDriver] == 0)
			{
				strcat(S3MP4K, "Route\tPayout\n");
				format(String, sizeof(String), "{00FFFF}Route A: Los Santos East\t{33AA33}$150.00\n");
				strcat(S3MP4K, String);
				format(String, sizeof(String), "{00FFFF}Route B: Los Santos West\t{33AA33}$150.00\n");
				strcat(S3MP4K, String);
				Dialog_Show(playerid, DialogBusAB, DIALOG_STYLE_TABLIST_HEADERS, "Sidejob: Bus Driver", S3MP4K, "Select", "Cancel");
			}
			else
			{
				format(String, sizeof(String),"ERROR: Kamu harus menunggu %d Menit untuk menjadi Bus Driver", DelayPlayer[playerid][DelayBusDriver]/60);
				SendClientMessage(playerid, COLOR_GRAD2, String);
				RemovePlayerFromVehicle(playerid);		
			}
		}
	}
	return 1;
}

hook OnPlayerLeaveRaceCp(playerid)
{
	if(KerjaBus[playerid] == 1) {
        if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 437)
        {
            if(IsPlayerInAnyVehicle(playerid))
            {
                if(BusRuteAB[BusSteps[playerid][0]][bus_rute] == 1 && BusRuteAB[BusSteps[playerid][0]][bus_stop] == 1) pData[playerid][pBusWaiting] = -1;
				if(BusRuteAB[BusSteps[playerid][1]][bus_rute] == 2 && BusRuteAB[BusSteps[playerid][1]][bus_stop] == 1) pData[playerid][pBusWaiting] = -1;
            }
        }
    }
	return 1;
}

hook OnPlayerEnterRaceCP(playerid) {
    if(KerjaBus[playerid] == 1) {
        if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 437)
        {
            if(IsPlayerInAnyVehicle(playerid))
            {
				if(BusSteps[playerid][0]) {
					//BUSAB RUTE A
					if(BusRuteAB[BusSteps[playerid][0]][bus_rute] == 1 && BusRuteAB[BusSteps[playerid][0]][bus_stop] == 0)
					{
						PlayerPlaySound(playerid, 1056, 0, 0, 0);
						BusSteps[playerid][0]++;
						switch(BusRuteAB[BusSteps[playerid][0]][bus_stop]) {
							case 0: SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][0]][bus_posx], BusRuteAB[BusSteps[playerid][0]][bus_posy], BusRuteAB[BusSteps[playerid][0]][bus_posz], BusRuteAB[BusSteps[playerid][0]+1][bus_posx], BusRuteAB[BusSteps[playerid][0]+1][bus_posy], BusRuteAB[BusSteps[playerid][0]+1][bus_posz], 5);
							case 1: SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][0]][bus_posx], BusRuteAB[BusSteps[playerid][0]][bus_posy], BusRuteAB[BusSteps[playerid][0]][bus_posz], BusRuteAB[BusSteps[playerid][0]+1][bus_posx], BusRuteAB[BusSteps[playerid][0]+1][bus_posy], BusRuteAB[BusSteps[playerid][0]+1][bus_posz], 2);
							case 2: SetPlayerRaceCheckpoint(playerid, 1, BusRuteAB[BusSteps[playerid][0]][bus_posx], BusRuteAB[BusSteps[playerid][0]][bus_posy], BusRuteAB[BusSteps[playerid][0]][bus_posz], BusRuteAB[BusSteps[playerid][0]+1][bus_posx], BusRuteAB[BusSteps[playerid][0]+1][bus_posy], BusRuteAB[BusSteps[playerid][0]+1][bus_posz], 5);
						}
						return 1;
					}
					else if(BusRuteAB[BusSteps[playerid][0]][bus_rute] == 1 && BusRuteAB[BusSteps[playerid][0]][bus_stop] == 1) pData[playerid][pBusWaiting] = 16;
					else if(BusRuteAB[BusSteps[playerid][0]][bus_rute] == 1 && BusRuteAB[BusSteps[playerid][0]][bus_stop] == 2)
					{
						if(BusLaps[playerid] < 3) {
							TogglePlayerControllable(playerid, 0);
							new str[212];
							format(str, sizeof(str), "You have finished %d out of 3 possible laps\nWould you like to continue the next lap?", BusLaps[playerid]);
							Dialog_Show(playerid, ContinueBusA, DIALOG_STYLE_MSGBOX, "Bus Driver: Continue lap?", str, "Continue", "Finish");
						}
						else {
							SendCustomMessage(playerid, "SIDEJOB", "{FFFFFF}You've earned {00FF00}$150.00 {FFFFFF}for finising a bus route lap!");
							GivePlayerMoneyEx(playerid, 15000);
							BusLaps[playerid] = -1;
							DelayPlayer[playerid][DelayBusDriver] = 1800;
							DisablePlayerRaceCheckpoint(playerid);
							RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
							KerjaBus[playerid] = -1;
							BusSteps[playerid][0] = 0;
							DialogBus[0]--;
							DialogSaya[playerid][0] = false;
						}
						return 1;
					}
				}
				else if(BusSteps[playerid][1]) {
					//BUSAB RUTE B
					if(BusRuteAB[BusSteps[playerid][1]][bus_rute] == 2 && BusRuteAB[BusSteps[playerid][1]][bus_stop] == 0)
					{
						PlayerPlaySound(playerid, 1056, 0, 0, 0);
						BusSteps[playerid][1]++;
						switch(BusRuteAB[BusSteps[playerid][1]][bus_stop]) {
							case 0: SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][1]][bus_posx], BusRuteAB[BusSteps[playerid][1]][bus_posy], BusRuteAB[BusSteps[playerid][1]][bus_posz], BusRuteAB[BusSteps[playerid][1]+1][bus_posx], BusRuteAB[BusSteps[playerid][1]+1][bus_posy], BusRuteAB[BusSteps[playerid][1]+1][bus_posz], 5);
							case 1: SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][1]][bus_posx], BusRuteAB[BusSteps[playerid][1]][bus_posy], BusRuteAB[BusSteps[playerid][1]][bus_posz], BusRuteAB[BusSteps[playerid][1]+1][bus_posx], BusRuteAB[BusSteps[playerid][1]+1][bus_posy], BusRuteAB[BusSteps[playerid][1]+1][bus_posz], 2);
							case 2: SetPlayerRaceCheckpoint(playerid, 1, BusRuteAB[BusSteps[playerid][1]][bus_posx], BusRuteAB[BusSteps[playerid][1]][bus_posy], BusRuteAB[BusSteps[playerid][1]][bus_posz], BusRuteAB[BusSteps[playerid][1]+1][bus_posx], BusRuteAB[BusSteps[playerid][1]+1][bus_posy], BusRuteAB[BusSteps[playerid][1]+1][bus_posz], 5);
						}
						return 1;
					}
					else if(BusRuteAB[BusSteps[playerid][1]][bus_rute] == 2 && BusRuteAB[BusSteps[playerid][1]][bus_stop] == 1) pData[playerid][pBusWaiting] = 16;
					else if(BusRuteAB[BusSteps[playerid][1]][bus_rute] == 2 && BusRuteAB[BusSteps[playerid][1]][bus_stop] == 2)
					{
						if(BusLaps[playerid] < 3) {
							TogglePlayerControllable(playerid, 0);
							new str[212];
							format(str, sizeof(str), "You have finished %d out of 3 possible laps\nWould you like to continue the next lap?", BusLaps[playerid]);
							Dialog_Show(playerid, ContinueBusB, DIALOG_STYLE_MSGBOX, "Bus Driver: Continue lap?", str, "Continue", "Finish");
						}
						else {
							SendCustomMessage(playerid, "SIDEJOB", "{FFFFFF}You've earned {00FF00}$150.00 {FFFFFF}for finising a bus route lap!");
							GivePlayerMoneyEx(playerid, 15000);
							BusLaps[playerid] = -1;
							DelayPlayer[playerid][DelayBusDriver] = 1800;
							DisablePlayerRaceCheckpoint(playerid);
							RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
							KerjaBus[playerid] = -1;
							BusSteps[playerid][1] = 0;
							DialogBus[1]--;
							DialogSaya[playerid][0] = false;
						}
						return 1;
					}
				}
				
            }
        }
    }
    if(KerjaBusCD[playerid] == 1) {
        if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 431)
        {
            if(IsPlayerInAnyVehicle(playerid))
            {
                if(BusCDSteps[playerid][0]) {
					//BUSCD RUTE A
					if(BusRuteCD[BusCDSteps[playerid][0]][bus_rute] == 1 && BusRuteCD[BusCDSteps[playerid][0]][bus_stop] == 0)
					{
						PlayerPlaySound(playerid, 1056, 0, 0, 0);
						BusCDSteps[playerid][0]++;
						switch(BusRuteCD[BusCDSteps[playerid][0]][bus_stop]) {
							case 0: SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][0]][bus_posx], BusRuteCD[BusCDSteps[playerid][0]][bus_posy], BusRuteCD[BusCDSteps[playerid][0]][bus_posz], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posz], 5);
							case 1: SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][0]][bus_posx], BusRuteCD[BusCDSteps[playerid][0]][bus_posy], BusRuteCD[BusCDSteps[playerid][0]][bus_posz], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posz], 2);
							case 2: SetPlayerRaceCheckpoint(playerid, 1, BusRuteCD[BusCDSteps[playerid][0]][bus_posx], BusRuteCD[BusCDSteps[playerid][0]][bus_posy], BusRuteCD[BusCDSteps[playerid][0]][bus_posz], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posz], 5);
						}
						return 1;
					}
					else if(BusRuteCD[BusCDSteps[playerid][0]][bus_rute] == 1 && BusRuteCD[BusCDSteps[playerid][0]][bus_stop] == 1) pData[playerid][pBusWaiting] = 16;
					else if(BusRuteCD[BusCDSteps[playerid][0]][bus_rute] == 1 && BusRuteCD[BusCDSteps[playerid][0]][bus_stop] == 2)
					{
						if(BusLaps[playerid] < 2) {
							TogglePlayerControllable(playerid, 0);
							new str[212];
							format(str, sizeof(str), "You have finished %d out of 2 possible laps\nWould you like to continue the next lap?", BusLaps[playerid]);
							Dialog_Show(playerid, ContinueBusC, DIALOG_STYLE_MSGBOX, "Bus Driver: Continue lap?", str, "Continue", "Finish");
						}
						else {
							SendCustomMessage(playerid, "SIDEJOB", "{FFFFFF}You've earned {00FF00}$245.00 {FFFFFF}for finising a bus route lap!");
							GivePlayerMoneyEx(playerid, 24500);
							DelayPlayer[playerid][DelayBusDriver] = 1800;
							DisablePlayerRaceCheckpoint(playerid);
							RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
							KerjaBusCD[playerid] = -1;
							BusCDSteps[playerid][0] = 0;
							DialogBusCD[0]--;
							DialogSaya[playerid][0] = false;
						}
						return 1;
					}
				}
				if(BusCDSteps[playerid][1]) {
					//BUSCD RUTE A
					if(BusRuteCD[BusCDSteps[playerid][1]][bus_rute] == 2 && BusRuteCD[BusCDSteps[playerid][1]][bus_stop] == 0)
					{
						PlayerPlaySound(playerid, 1056, 0, 0, 0);
						BusCDSteps[playerid][1]++;
						switch(BusRuteCD[BusCDSteps[playerid][1]][bus_stop]) {
							case 0: SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][1]][bus_posx], BusRuteCD[BusCDSteps[playerid][1]][bus_posy], BusRuteCD[BusCDSteps[playerid][1]][bus_posz], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posz], 5);
							case 1: SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][1]][bus_posx], BusRuteCD[BusCDSteps[playerid][1]][bus_posy], BusRuteCD[BusCDSteps[playerid][1]][bus_posz], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posz], 2);
							case 2: SetPlayerRaceCheckpoint(playerid, 1, BusRuteCD[BusCDSteps[playerid][1]][bus_posx], BusRuteCD[BusCDSteps[playerid][1]][bus_posy], BusRuteCD[BusCDSteps[playerid][1]][bus_posz], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posz], 5);
						}
						return 1;
					}
					else if(BusRuteCD[BusCDSteps[playerid][1]][bus_rute] == 2 && BusRuteCD[BusCDSteps[playerid][1]][bus_stop] == 1) pData[playerid][pBusWaiting] = 16;
					else if(BusRuteCD[BusCDSteps[playerid][1]][bus_rute] == 2 && BusRuteCD[BusCDSteps[playerid][1]][bus_stop] == 2)
					{
						if(BusLaps[playerid] < 2) {
							TogglePlayerControllable(playerid, 0);
							new str[212];
							format(str, sizeof(str), "You have finished %d out of 2 possible laps\nWould you like to continue the next lap?", BusLaps[playerid]);
							Dialog_Show(playerid, ContinueBusD, DIALOG_STYLE_MSGBOX, "Bus Driver: Continue lap?", str, "Continue", "Finish");
						}
						else {
							SendCustomMessage(playerid, "SIDEJOB", "{FFFFFF}You've earned {00FF00}$285.00 {FFFFFF}for finising a bus route lap!");
							GivePlayerMoneyEx(playerid, 28500);
							DelayPlayer[playerid][DelayBusDriver] = 1800;
							DisablePlayerRaceCheckpoint(playerid);
							RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
							KerjaBusCD[playerid] = -1;
							BusCDSteps[playerid][1] = 0;
							DialogBusCD[1]--;
							DialogSaya[playerid][0] = false;
						}
						return 1;
					}
				}
            }
        }
    }
    return 1;
}