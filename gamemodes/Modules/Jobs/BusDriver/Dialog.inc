
Dialog:DialogBusAB(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		if(pData[playerid][pFaction] > 0) return Error(playerid, "Kamu anggota faction, tidak bekerja jobs/sidejob.");
		switch(listitem)
		{
			case 0:
			{
				if(DelayPlayer[playerid][DelayBusDriver] == 0)
				{
					if(DialogBus[0] < 2) // Kalau False atau tidak dipilih
					{
						DialogBus[0]++; // Dialog 0 telah di pilih
						DialogSaya[playerid][0] = true;
						BusSteps[playerid][0] = 1;
						KerjaBus[playerid] = 1;
						BusLaps[playerid] = 1;
						ChangeVehicleColor(GetPlayerVehicleID(playerid), 2, 2);
						SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][0]-1][bus_posx], BusRuteAB[BusSteps[playerid][0]-1][bus_posy], BusRuteAB[BusSteps[playerid][0]-1][bus_posz], BusRuteAB[BusSteps[playerid][0]][bus_posx], BusRuteAB[BusSteps[playerid][0]][bus_posy], BusRuteAB[BusSteps[playerid][0]][bus_posz], 5);
						SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOB: {FFFFFF}You've started working as a Bus Driver, please follow the checkpoint");
					}
					else return SendClientMessage(playerid,-1,"ERROR: Route already taken by Someone");
				}
			}
			case 1: {
				if(DelayPlayer[playerid][DelayBusDriver] == 0)
				{
					if(DialogBus[1] < 2) // Kalau False atau tidak dipilih
					{
						DialogBus[1]++; // Dialog 0 telah di pilih
						DialogSaya[playerid][0] = true;
						BusSteps[playerid][1] = 53;
						KerjaBus[playerid] = 1;
						BusLaps[playerid] = 1;
						ChangeVehicleColor(GetPlayerVehicleID(playerid), 3, 3);
						if(BusRuteAB[BusSteps[playerid][1]][bus_rute] == 2) {
							SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][1]][bus_posx], BusRuteAB[BusSteps[playerid][1]][bus_posy], BusRuteAB[BusSteps[playerid][1]][bus_posz], BusRuteAB[BusSteps[playerid][1]+1][bus_posx], BusRuteAB[BusSteps[playerid][1]+1][bus_posy], BusRuteAB[BusSteps[playerid][1]+1][bus_posz], 5);
						}
						SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOB: {FFFFFF}You've started working as a Bus Driver, please follow the checkpoint");
					}
					else return SendClientMessage(playerid,-1,"ERROR: Route already taken by Someone");
				}
			}
		}
	}
	else {
		SetVehicleToRespawn(pData[playerid][pLastCar]);
		RemovePlayerFromVehicle(playerid);
	}
    return 1;
}

Dialog:DialogBusCD(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		if(pData[playerid][pFaction] > 0) return Error(playerid, "Kamu anggota faction, tidak bekerja jobs/sidejob.");
		switch(listitem)
		{
			case 0:
			{
				if(DelayPlayer[playerid][DelayBusDriver] == 0)
				{
					if(DialogBusCD[0] < 2) // Kalau False atau tidak dipilih
					{
						DialogBusCD[0]++; // Dialog 0 telah di pilih
						DialogSaya[playerid][0] = true;
						BusCDSteps[playerid][0] = 1;
						KerjaBusCD[playerid] = 1;
						BusLaps[playerid] = 1;
                        ChangeVehicleColor(GetPlayerVehicleID(playerid), 128, 128);
						if(BusRuteCD[BusCDSteps[playerid][0]][bus_rute] == 1) {
							SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][0]-1][bus_posx], BusRuteCD[BusCDSteps[playerid][0]-1][bus_posy], BusRuteCD[BusCDSteps[playerid][0]-1][bus_posz], BusRuteCD[BusCDSteps[playerid][0]][bus_posx], BusRuteCD[BusCDSteps[playerid][0]][bus_posy], BusRuteCD[BusCDSteps[playerid][0]][bus_posz], 5);
						}
						SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOB: {FFFFFF}You've started working as a Bus Driver, please follow the checkpoint");
					}
					else return SendClientMessage(playerid,-1,"ERROR: Route already taken by Someone");
				}
			}
			case 1:
			{
				if(DelayPlayer[playerid][DelayBusDriver] == 0)
				{
					if(DialogBusCD[1] < 2) // Kalau False atau tidak dipilih
					{
						DialogBusCD[1]++; // Dialog 0 telah di pilih
						DialogSaya[playerid][0] = true;
						BusCDSteps[playerid][1] = 61;
						KerjaBusCD[playerid] = 1;
						BusLaps[playerid] = 1;
                        ChangeVehicleColor(GetPlayerVehicleID(playerid), 211, 211);
						if(BusRuteCD[BusCDSteps[playerid][1]][bus_rute] == 2) {
							SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][1]][bus_posx], BusRuteCD[BusCDSteps[playerid][1]][bus_posy], BusRuteCD[BusCDSteps[playerid][1]][bus_posz], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posz], 5);
						}
						SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOB: {FFFFFF}You've started working as a Bus Driver, please follow the checkpoint");
					}
					else return SendClientMessage(playerid,-1,"ERROR: Route already taken by Someone");
				}
			}
		}
	}
	else {
		SetVehicleToRespawn(pData[playerid][pLastCar]);
		RemovePlayerFromVehicle(playerid);
	}
    return 1;
}
  
Dialog:ContinueBusA(playerid, response, listitem, inputtext[]) {
    if(response) { 
		TogglePlayerControllable(playerid, 1);
		BusLaps[playerid]++;
		BusSteps[playerid][0] = 1;
		SendCustomMessage(playerid, "SIDEJOB", "{FFFFFF}You've earned {00FF00}$150.00 {FFFFFF}for finising a bus route lap!");
		GivePlayerMoneyEx(playerid, 15000);
		SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][0]-1][bus_posx], BusRuteAB[BusSteps[playerid][0]-1][bus_posy], BusRuteAB[BusSteps[playerid][0]-1][bus_posz], BusRuteAB[BusSteps[playerid][0]][bus_posx], BusRuteAB[BusSteps[playerid][0]][bus_posy], BusRuteAB[BusSteps[playerid][0]][bus_posz], 5);
	}
	else {
		TogglePlayerControllable(playerid, 1);
		SendCustomMessage(playerid, "SIDEJOB", "{FFFFFF}You've earned {00FF00}$150.00 {FFFFFF}for finising a bus route lap!");
		GivePlayerMoneyEx(playerid, 15000);
		DelayPlayer[playerid][DelayBusDriver] = 1800;
		DisablePlayerRaceCheckpoint(playerid);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		BusLaps[playerid] = -1;
		KerjaBus[playerid] = -1;
		BusSteps[playerid][0] = 0;
		DialogBus[0]--; // Dialog 0 telah di pilih
		DialogSaya[playerid][0] = false;
		return 1;
	}
    return 1;
}
  
Dialog:ContinueBusB(playerid, response, listitem, inputtext[]) {
    if(response) { 
		TogglePlayerControllable(playerid, 1);
		BusLaps[playerid]++;
		BusSteps[playerid][1] = 53;
		SendCustomMessage(playerid, "SIDEJOB", "{FFFFFF}You've earned {00FF00}$150.00 {FFFFFF}for finising a bus route lap!");
		GivePlayerMoneyEx(playerid, 15000);
		SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][1]][bus_posx], BusRuteAB[BusSteps[playerid][1]][bus_posy], BusRuteAB[BusSteps[playerid][1]+1][bus_posz], BusRuteAB[BusSteps[playerid][1]+1][bus_posx], BusRuteAB[BusSteps[playerid][1]+1][bus_posy], BusRuteAB[BusSteps[playerid][1]][bus_posz], 5);
	}
	else {
		TogglePlayerControllable(playerid, 1);
		SendCustomMessage(playerid, "SIDEJOB", "{FFFFFF}You've earned {00FF00}$150.00 {FFFFFF}for finising a bus route lap!");
		GivePlayerMoneyEx(playerid, 15000);
		BusLaps[playerid] = -1;
		DelayPlayer[playerid][DelayBusDriver] = 1800;
		DisablePlayerRaceCheckpoint(playerid);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		KerjaBus[playerid] = -1;
		BusSteps[playerid][1] = 0;
		DialogBus[0]--; // Dialog 0 telah di pilih
		DialogSaya[playerid][0] = false;
		return 1;
	}
    return 1;
}

Dialog:ContinueBusC(playerid, response, listitem, inputtext[]) {
    if(response) { 
		TogglePlayerControllable(playerid, 1);
		BusLaps[playerid]++;
		SendCustomMessage(playerid, "SIDEJOB", "{FFFFFF}You've earned {00FF00}$245.00 {FFFFFF}for finising a bus route lap!");
		GivePlayerMoneyEx(playerid, 24500);
		BusCDSteps[playerid][0] = 1;
		if(BusRuteCD[BusCDSteps[playerid][0]][bus_rute] == 1) {
			SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][0]-1][bus_posx], BusRuteCD[BusCDSteps[playerid][0]-1][bus_posy], BusRuteCD[BusCDSteps[playerid][0]-1][bus_posz], BusRuteCD[BusCDSteps[playerid][0]][bus_posx], BusRuteCD[BusCDSteps[playerid][0]][bus_posy], BusRuteCD[BusCDSteps[playerid][0]][bus_posz], 5);
		}
	}
	else {
		TogglePlayerControllable(playerid, 1);
		SendCustomMessage(playerid, "SIDEJOB", "{FFFFFF}You've earned {00FF00}$245.00 {FFFFFF}for finising a bus route lap!");
		GivePlayerMoneyEx(playerid, 24500);
		DelayPlayer[playerid][DelayBusDriver] = 1800;
		DisablePlayerRaceCheckpoint(playerid);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		KerjaBusCD[playerid] = -1;
		BusCDSteps[playerid][0] = 0;
		DialogBusCD[0]--; // Dialog 0 telah di pilih
		DialogSaya[playerid][0] = false;
		return 1;
	}
    return 1;
}
  
Dialog:ContinueBusD(playerid, response, listitem, inputtext[]) {
    if(response) { 
		TogglePlayerControllable(playerid, 1);
		BusLaps[playerid]++;
		SendCustomMessage(playerid, "SIDEJOB", "{FFFFFF}You've earned {00FF00}$285.00 {FFFFFF}for finising a bus route lap!");
		GivePlayerMoneyEx(playerid, 28500);
		BusCDSteps[playerid][1] = 61;
		if(BusRuteCD[BusCDSteps[playerid][1]][bus_rute] == 2) {
			SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][1]][bus_posx], BusRuteCD[BusCDSteps[playerid][1]][bus_posy], BusRuteCD[BusCDSteps[playerid][1]][bus_posz], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posz], 5);
		}
	}
	else {
		TogglePlayerControllable(playerid, 1);
		SendCustomMessage(playerid, "SIDEJOB", "{FFFFFF}You've earned {00FF00}$285.00 {FFFFFF}for finising a bus route lap!");
		GivePlayerMoneyEx(playerid, 28500);
		DelayPlayer[playerid][DelayBusDriver] = 1800;
		DisablePlayerRaceCheckpoint(playerid);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		KerjaBusCD[playerid] = -1;
		BusCDSteps[playerid][1] = 0;
		DialogBusCD[1]--; // Dialog 0 telah di pilih
		DialogSaya[playerid][0] = false;
		return 1;
	}
    return 1;
}
  