#include <YSI\y_hooks>

hook OnGameModeInit()
{
    new strings[212];
    //SIDE JOB SWEEPER VEHICLE
	SweepVeh[0] = AddStaticVehicle(574, 1615.5201, -1896.2864, 13.2474, 0.0000, 1, 1);
	SweepVeh[1] = AddStaticVehicle(574, 1622.4797, -1896.2864, 13.2474, 0.0000, 1, 1);
	SweepVeh[2] = AddStaticVehicle(574, 1619.0095, -1896.2864, 13.2474, 0.0000, 1, 1);
	for(new x;x<MAX_SWEEPER_VEHICLES; x++)
	{
	    format(strings, sizeof(strings), ""GREEN_E"SWEPEER-%d", SweepVeh[x]);
	    SetVehicleNumberPlate(SweepVeh[x], strings);
	    SetVehicleToRespawn(SweepVeh[x]);
	}
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
    if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
    {
        if(KerjaSweeper[playerid] != 0)
		{
			KerjaSweeper[playerid] = 0;
			for(new i = 0; i < 3; i++)
			{
				if(DialogSaya[playerid][i] == true) // Cari apakah dia punya salah satu diantara 10 dialog tersebut
				{
                    DelayPlayer[playerid][DelaySweeper] = 900;
                    KerjaSweeper[playerid] = -1;
					DialogSaya[playerid][i] = false; // Ubah Jadi Dia ga punya dialog lagi Kalau Udah Disconnect (Bukan dia lagi pemilik)
					DialogSweeper[i] = false; // Jadi ga ada yang punya nih dialog
					RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
				}
			}
			DisablePlayerRaceCheckpoint(playerid);
		}
    }
    if(newstate == PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_PASSENGER)
	{
        if(IsASweeperVeh(GetPlayerVehicleID(playerid)))
		{
			new String[212];
			if(DelayPlayer[playerid][DelaySweeper] == 0)
			{
				format(String, sizeof(String), "Route\tPrice\n");
				format(String, sizeof(String), "%sRoute A: Idlewood\t"GREEN_E"$50.00\n", String);
				format(String, sizeof(String), "%sRoute B: Pershing Square\t"GREEN_E"$55.00\n", String);
				format(String, sizeof(String), "%sRoute C: Verona Beach\t"GREEN_E"$75.00\n", String);
				Dialog_Show(playerid, DialogSweeper, DIALOG_STYLE_TABLIST_HEADERS, "Sweeper Sidejob", String, "Select", "Cancel");
			}
			else
			{
				format(String, sizeof(String),"ERROR: Kamu harus menunggu %d Menit untuk menjadi Street Cleaner", DelayPlayer[playerid][DelaySweeper]/60);
				SendClientMessage(playerid, COLOR_GRAD2, String);
				RemovePlayerFromVehicle(playerid);
				SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			}
		}
    }
    return 1;
}

hook OnPlayerEnterRaceCP(playerid) {
    if(KerjaSweeper[playerid]) {
		if(IsPlayerInAnyVehicle(playerid))
		{
			if(SweeperSteps[playerid][0]) {
				if(SweeperRute[SweeperSteps[playerid][0]][sweeper_rute] == 0 && SweeperRute[SweeperSteps[playerid][0]][sweeper_finish] == 0)
				{
					PlayerPlaySound(playerid, 1056, 0, 0, 0);
					SweeperSteps[playerid][0]++;
					switch(SweeperRute[SweeperSteps[playerid][0]][sweeper_finish]) {
						case 0: SetPlayerRaceCheckpoint(playerid, 0, SweeperRute[SweeperSteps[playerid][0]][sweeper_posx], SweeperRute[SweeperSteps[playerid][0]][sweeper_posy], SweeperRute[SweeperSteps[playerid][0]][sweeper_posz], SweeperRute[SweeperSteps[playerid][0]+1][sweeper_posx], SweeperRute[SweeperSteps[playerid][0]+1][sweeper_posy], SweeperRute[SweeperSteps[playerid][0]+1][sweeper_posz], 5);
						case 1: SetPlayerRaceCheckpoint(playerid, 1, SweeperRute[SweeperSteps[playerid][0]][sweeper_posx], SweeperRute[SweeperSteps[playerid][0]][sweeper_posy], SweeperRute[SweeperSteps[playerid][0]][sweeper_posz], SweeperRute[SweeperSteps[playerid][0]+1][sweeper_posx], SweeperRute[SweeperSteps[playerid][0]+1][sweeper_posy], SweeperRute[SweeperSteps[playerid][0]+1][sweeper_posz], 5);
					}
					return 1;
				}
				else if(SweeperRute[SweeperSteps[playerid][0]][sweeper_rute] == 0 && SweeperRute[SweeperSteps[playerid][0]][sweeper_finish] == 1) {
                    DialogSweeper[0] = false; // Dialog 0 telah di pilih
                    DialogSaya[playerid][0] = false;
                    GivePlayerMoneyEx(playerid, 5000);
                    SendClientMessageEx(playerid, COLOR_ARWIN, "SIDEJOB: "WHITE_E"You've earned "GREEN_E"$50.00 "WHITE_E"for finishing sweeper sidejob");
                    DelayPlayer[playerid][DelaySweeper] = 900;
                    KerjaSweeper[playerid] = -1;
                    SweeperSteps[playerid][0] = -1;
                    RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
                }
			}
            if(SweeperSteps[playerid][1]) {
				if(SweeperRute[SweeperSteps[playerid][1]][sweeper_rute] == 1 && SweeperRute[SweeperSteps[playerid][1]][sweeper_finish] == 0)
				{
					PlayerPlaySound(playerid, 1056, 0, 0, 0);
					SweeperSteps[playerid][1]++;
					switch(SweeperRute[SweeperSteps[playerid][1]][sweeper_finish]) {
						case 0: SetPlayerRaceCheckpoint(playerid, 0, SweeperRute[SweeperSteps[playerid][1]][sweeper_posx], SweeperRute[SweeperSteps[playerid][1]][sweeper_posy], SweeperRute[SweeperSteps[playerid][1]][sweeper_posz], SweeperRute[SweeperSteps[playerid][1]+1][sweeper_posx], SweeperRute[SweeperSteps[playerid][1]+1][sweeper_posy], SweeperRute[SweeperSteps[playerid][1]+1][sweeper_posz], 5);
						case 1: SetPlayerRaceCheckpoint(playerid, 1, SweeperRute[SweeperSteps[playerid][1]][sweeper_posx], SweeperRute[SweeperSteps[playerid][1]][sweeper_posy], SweeperRute[SweeperSteps[playerid][1]][sweeper_posz], SweeperRute[SweeperSteps[playerid][1]+1][sweeper_posx], SweeperRute[SweeperSteps[playerid][1]+1][sweeper_posy], SweeperRute[SweeperSteps[playerid][1]+1][sweeper_posz], 5);
					}
					return 1;
				}
				else if(SweeperRute[SweeperSteps[playerid][1]][sweeper_rute] == 1 && SweeperRute[SweeperSteps[playerid][1]][sweeper_finish] == 1) {
                    DialogSweeper[0] = false; // Dialog 0 telah di pilih
                    DialogSaya[playerid][0] = false;
                    GivePlayerMoneyEx(playerid, 5500);
                    SendClientMessageEx(playerid, COLOR_ARWIN, "SIDEJOB: "WHITE_E"You've earned "GREEN_E"$55.00 "WHITE_E"for finishing sweeper sidejob");
                    DelayPlayer[playerid][DelaySweeper] = 900;
                    KerjaSweeper[playerid] = -1;
                    SweeperSteps[playerid][1] = -1;
                    RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
                }
			}
            if(SweeperSteps[playerid][2]) {
				if(SweeperRute[SweeperSteps[playerid][2]][sweeper_rute] == 2 && SweeperRute[SweeperSteps[playerid][2]][sweeper_finish] == 0)
				{
					PlayerPlaySound(playerid, 1056, 0, 0, 0);
					SweeperSteps[playerid][2]++;
					switch(SweeperRute[SweeperSteps[playerid][2]][sweeper_finish]) {
						case 0: SetPlayerRaceCheckpoint(playerid, 0, SweeperRute[SweeperSteps[playerid][2]][sweeper_posx], SweeperRute[SweeperSteps[playerid][2]][sweeper_posy], SweeperRute[SweeperSteps[playerid][2]][sweeper_posz], SweeperRute[SweeperSteps[playerid][2]+1][sweeper_posx], SweeperRute[SweeperSteps[playerid][2]+1][sweeper_posy], SweeperRute[SweeperSteps[playerid][2]+1][sweeper_posz], 5);
						case 1: SetPlayerRaceCheckpoint(playerid, 1, SweeperRute[SweeperSteps[playerid][2]][sweeper_posx], SweeperRute[SweeperSteps[playerid][2]][sweeper_posy], SweeperRute[SweeperSteps[playerid][2]][sweeper_posz], SweeperRute[SweeperSteps[playerid][2]][sweeper_posx], SweeperRute[SweeperSteps[playerid][2]][sweeper_posy], SweeperRute[SweeperSteps[playerid][2]][sweeper_posz], 5);
					}
					return 1;
				}
				else if(SweeperRute[SweeperSteps[playerid][2]][sweeper_rute] == 2 && SweeperRute[SweeperSteps[playerid][2]][sweeper_finish] == 1) {
                    DialogSweeper[0] = false; // Dialog 0 telah di pilih
                    DialogSaya[playerid][0] = false;
                    GivePlayerMoneyEx(playerid, 7500);
                    SendClientMessageEx(playerid, COLOR_ARWIN, "SIDEJOB: "WHITE_E"You've earned "GREEN_E"$75.00 "WHITE_E"for finishing sweeper sidejob");
                    DelayPlayer[playerid][DelaySweeper] = 900;
                    KerjaSweeper[playerid] = -1;
                    SweeperSteps[playerid][2] = -1;
                    RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
                }
			}
		}
    }
    return 1;
}

IsASweeperVeh(carid)
{
	for(new v = 0; v < MAX_SWEEPER_VEHICLES; v++) {
	    if(carid == SweepVeh[v]) return 1;
	}
	return 0;
}
