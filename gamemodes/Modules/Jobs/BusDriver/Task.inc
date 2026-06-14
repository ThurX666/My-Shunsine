
ptask PlayerBus[1000](playerid)
{
	if(pData[playerid][pBusWaiting] > 0)
	{
		if(pData[playerid][pBusWaiting] > 0)
		{
			pData[playerid][pBusWaiting]--;
			new string[212];
			format(string,32,"~w~PLEASE WAIT~n~~y~%i SECOND",pData[playerid][pBusWaiting]);
			TogglePlayerControllable(playerid, 0);
			GameTextForPlayer(playerid, string, 2000, 6);
			PlayerPlaySound(playerid, 1056, 0, 0, 0);
			if(pData[playerid][pBusWaiting] == 0)
			{
				PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 437 && KerjaBus[playerid] == 1) {
					if(BusRuteAB[BusSteps[playerid][0]][bus_rute] == 1 && BusRuteAB[BusSteps[playerid][0]][bus_stop] == 1)
					{
						BusSteps[playerid][0]++;
						TogglePlayerControllable(playerid, 1);
						SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][0]][bus_posx], BusRuteAB[BusSteps[playerid][0]][bus_posy], BusRuteAB[BusSteps[playerid][0]][bus_posz], BusRuteAB[BusSteps[playerid][0]+1][bus_posx], BusRuteAB[BusSteps[playerid][0]+1][bus_posy], BusRuteAB[BusSteps[playerid][0]+1][bus_posz], 5);
					}
					else if(BusRuteAB[BusSteps[playerid][1]][bus_rute] == 2 && BusRuteAB[BusSteps[playerid][1]][bus_stop] == 1)
					{
						BusSteps[playerid][1]++;
						TogglePlayerControllable(playerid, 1);
						SetPlayerRaceCheckpoint(playerid, 0, BusRuteAB[BusSteps[playerid][1]][bus_posx], BusRuteAB[BusSteps[playerid][1]][bus_posy], BusRuteAB[BusSteps[playerid][1]][bus_posz], BusRuteAB[BusSteps[playerid][1]+1][bus_posx], BusRuteAB[BusSteps[playerid][1]+1][bus_posy], BusRuteAB[BusSteps[playerid][1]+1][bus_posz], 5);
					}
				}
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 431 && KerjaBusCD[playerid] == 1) {
					if(BusRuteCD[BusCDSteps[playerid][0]][bus_rute] == 1 && BusRuteCD[BusCDSteps[playerid][0]][bus_stop] == 1)
					{
						BusCDSteps[playerid][0]++;
						TogglePlayerControllable(playerid, 1);
						SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][0]][bus_posx], BusRuteCD[BusCDSteps[playerid][0]][bus_posy], BusRuteCD[BusCDSteps[playerid][0]][bus_posz], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][0]+1][bus_posz], 5);
					}
					else if(BusRuteCD[BusCDSteps[playerid][1]][bus_rute] == 2 && BusRuteCD[BusCDSteps[playerid][1]][bus_stop] == 1)
					{
						BusCDSteps[playerid][1]++;
						TogglePlayerControllable(playerid, 1);
						SetPlayerRaceCheckpoint(playerid, 0, BusRuteCD[BusCDSteps[playerid][1]][bus_posx], BusRuteCD[BusCDSteps[playerid][1]][bus_posy], BusRuteCD[BusCDSteps[playerid][1]][bus_posz], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posx], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posy], BusRuteCD[BusCDSteps[playerid][1]+1][bus_posz], 5);
					}
				}
			}	
		}
	}	
	if(KerjaBus[playerid] > 0 && TimerBus[playerid] > 0 && !IsPlayerInAnyVehicle(playerid)) {
		TimerBus[playerid]--;
        new str[256];
        format(str, sizeof(str), "~w~Return To Vehicle ~n~in ~y~%d seconds", TimerBus[playerid]);
        GameTextForPlayer(playerid, str, 1000, 6);
        PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
		if(TimerBus[playerid] == 0) { 
			DelayPlayer[playerid][DelayBusDriver] = 1800;
			DisablePlayerRaceCheckpoint(playerid);
			SetVehicleToRespawn(pData[playerid][pLastCar]);
			BusLaps[playerid] = -1;
			KerjaBus[playerid] = -1;
			BusSteps[playerid][0] = 0;
			DialogBus[0]--; // Dialog 0 telah di pilih
			DialogSaya[playerid][0] = false;
		}
	}
	if(KerjaBusCD[playerid] > 0 && TimerBus[playerid] > 0 && !IsPlayerInAnyVehicle(playerid)) {
		TimerBus[playerid]--;
        new str[256];
        format(str, sizeof(str), "~w~Return To Vehicle ~n~in ~y~%d seconds", TimerBus[playerid]);
        GameTextForPlayer(playerid, str, 1000, 6);
        PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
		if(TimerBus[playerid] == 0) { 
			DelayPlayer[playerid][DelayBusDriver] = 1800;
			DisablePlayerRaceCheckpoint(playerid);
			SetVehicleToRespawn(pData[playerid][pLastCar]);
			BusLaps[playerid] = -1;
			KerjaBusCD[playerid] = -1;
			BusSteps[playerid][0] = 0;
			DialogBus[0]--; // Dialog 0 telah di pilih
			DialogSaya[playerid][0] = false;
		}
	}
	return 1;
}
