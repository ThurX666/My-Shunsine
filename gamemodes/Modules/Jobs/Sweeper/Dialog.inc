
Dialog:DialogSweeper(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		if(pData[playerid][pFaction] > 0) return Error(playerid, "Kamu anggota faction, tidak bekerja jobs/sidejob.");
		switch(listitem)
		{
			case 0:
            {
                if(DialogSweeper[0] == false) // Kalau False atau tidak dipilih
                {
                    DialogSweeper[0] = true; // Dialog 0 telah di pilih
                    DialogSaya[playerid][0] = true;
                    SweeperSteps[playerid][0] = 1;
                    KerjaSweeper[playerid] = 1;
                    SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOBINFO: {FFFFFF}Ikutilah checkpoint yang tersedia pada Radar");
                    if(SweeperRute[SweeperSteps[playerid][0]][sweeper_rute] == 0) SetPlayerRaceCheckpoint(playerid, 0, SweeperRute[SweeperSteps[playerid][0]][sweeper_posx], SweeperRute[SweeperSteps[playerid][0]][sweeper_posy], SweeperRute[SweeperSteps[playerid][0]][sweeper_posz], SweeperRute[SweeperSteps[playerid][0]+1][sweeper_posx], SweeperRute[SweeperSteps[playerid][0]+1][sweeper_posy], SweeperRute[SweeperSteps[playerid][0]+1][sweeper_posz], 5);
                }
                else SendClientMessage(playerid,-1,"ERROR: Route already taken by Someone");
            }
            case 1:
            {
                if(DialogSweeper[1] == false) // Kalau False atau tidak dipilih
                {
                    DialogSweeper[1] = true; // Dialog 1 telah di pilih
                    DialogSaya[playerid][1] = true;
                    SweeperSteps[playerid][1] = 25;
                    KerjaSweeper[playerid] = 1;
                    if(SweeperRute[SweeperSteps[playerid][1]][sweeper_rute] == 1) SetPlayerRaceCheckpoint(playerid, 0, SweeperRute[SweeperSteps[playerid][1]][sweeper_posx], SweeperRute[SweeperSteps[playerid][1]][sweeper_posy], SweeperRute[SweeperSteps[playerid][1]][sweeper_posz], SweeperRute[SweeperSteps[playerid][1]+1][sweeper_posx], SweeperRute[SweeperSteps[playerid][1]+1][sweeper_posy], SweeperRute[SweeperSteps[playerid][1]+1][sweeper_posz], 5);
                    SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOBINFO: {FFFFFF}Ikutilah checkpoint yang tersedia pada Radar");
                }
                else SendClientMessage(playerid,-1,"ERROR: Route already taken by Someone");
            }
            case 2:
            {
                if(DialogSweeper[2] == false) // Kalau False atau tidak dipilih
                {
                    DialogSweeper[2] = true; // Dialog 1 telah di pilih
                    DialogSaya[playerid][2] = true;
                    SweeperSteps[playerid][2] = 41;
                    KerjaSweeper[playerid] = 1;
                    if(SweeperRute[SweeperSteps[playerid][2]][sweeper_rute] == 2) SetPlayerRaceCheckpoint(playerid, 0, SweeperRute[SweeperSteps[playerid][2]][sweeper_posx], SweeperRute[SweeperSteps[playerid][2]][sweeper_posy], SweeperRute[SweeperSteps[playerid][2]][sweeper_posz], SweeperRute[SweeperSteps[playerid][2]+1][sweeper_posx], SweeperRute[SweeperSteps[playerid][2]+1][sweeper_posy], SweeperRute[SweeperSteps[playerid][2]+1][sweeper_posz], 5);
                    SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOBINFO: {FFFFFF}Ikutilah checkpoint yang tersedia pada Radar");
                }
                else SendClientMessage(playerid,-1,"ERROR: Route already taken by Someone");
            }
		}
	}
	else RemovePlayerFromVehicle(playerid);
    return 1;
}
