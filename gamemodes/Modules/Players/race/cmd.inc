
CMD:race(playerid, params[]) {
	new type[24], string[128], Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	if(sscanf(params, "s[24]S()[128]", type, string)) {
		Usage(playerid, "/race [names]");
		SendClientMessage(playerid, COLOR_YELLOW, "NAMES: "WHITE_E"save (1-9), finish, invite, joinme, start");
		return 1;
	}
	if(!strcmp(type, "save", true)) {
		new ind;
		if(sscanf(string, "d", ind)) 
			return Usage(playerid, "/race save [index 1 - 9]");

		if(ind < 1 || ind > 9)
			return Usage(playerid,"Invalid route index!");

		new dex = ind - 1;
		RacePos[playerid][dex][0] = pos[0];
		RacePos[playerid][dex][1] = pos[1];
		RacePos[playerid][dex][2] = pos[2];
		SendCustomMessage(playerid, "RACE", "Checkpoint %d recorded and saved!", ind);
	}
	else if(!strcmp(type, "finish", true)) {
		RacePos[playerid][9][0] = pos[0];
		RacePos[playerid][9][1] = pos[1];
		RacePos[playerid][9][2] = pos[2];
		SendCustomMessage(playerid, "RACE", "Finish checkpoint recorded!");
	}
	else if(!strcmp(type, "joinme", true)) {
		RaceWith[playerid] = playerid;
		SendCustomMessage(playerid, "RACE", "Kamu mengikuti balapan milikmu sendiri!");
	}
	else if(!strcmp(type, "invite", true)) {
		new pid;
		if(sscanf(string, "u", pid))
			return Usage(playerid, "/race invite [playerid]");

		if(!IsPlayerNearPlayer(playerid, pid, 5.0) || pid == INVALID_PLAYER_ID)
			return Error(playerid, "Player tersebut tidak didekatmu!");

		if(RaceWith[pid] != INVALID_PLAYER_ID)
			return Error(playerid, "Player tersebut sudah ada di balapan lain!");

		if(pid == playerid)
			return Error(playerid, "Gunakan /race joinme");

		RaceWith[pid] = playerid;
		RaceWith[playerid] = playerid;
		SendCustomMessage(playerid, "RACE", "Kamu telah mengundang "YELLOW_E"%s "WHITE_E"untuk ikut balapan mu!", ReturnName(pid));
		SendCustomMessage(pid, "RACE", "Kamu telah diundang oleh "YELLOW_E"%s "WHITE_E"untuk mengikuti balapan!", ReturnName(playerid));
	}
	else if(!strcmp(type, "start", true)) {
		for(new i = 0; i < MAX_ROUTE - 1; i++) {
			if(RacePos[playerid][i][0] == 0 && RacePos[playerid][i][1] == 0 && RacePos[playerid][i][2] == 0) {
				SendCustomMessage(playerid, "RACE", "Route %d masih belum di record!", i + 1);
				return 1;
			}
		}
		if(RacePos[playerid][9][0] == 0 && RacePos[playerid][9][1] == 0 && RacePos[playerid][9][2] == 0)
			return Error(playerid, "Finish Route belum di record!");

		foreach (new player : Player) if(IsPlayerConnected(player) && RaceWith[player] == playerid) 
		{
			InRace[playerid] = true;
			RaceIndex[playerid] = 0;
			InRace[player] = true;
			RaceIndex[player] = 0;
			GameTextForPlayer(player, "Balapan dimulai!", 3000, 5);
			DisablePlayerRaceCheckpoint(player);
			SetPlayerRaceCheckpoint(player, 0, RacePos[RaceWith[player]][RaceIndex[player]][0], RacePos[RaceWith[player]][RaceIndex[player]][1], RacePos[RaceWith[player]][RaceIndex[player]][2], RacePos[RaceWith[player]][RaceIndex[player]+1][0], RacePos[RaceWith[player]][RaceIndex[player]+1][1], RacePos[RaceWith[player]][RaceIndex[player]+1][2], 5.0);
			GameTextForPlayer(playerid, "Balapan dimulai!", 3000, 5);
			DisablePlayerRaceCheckpoint(playerid);
			SetPlayerRaceCheckpoint(playerid, 0, RacePos[playerid][RaceIndex[playerid]][0], RacePos[playerid][RaceIndex[playerid]][1], RacePos[playerid][RaceIndex[playerid]][2], RacePos[playerid][RaceIndex[playerid]+1][0], RacePos[playerid][RaceIndex[playerid]+1][1], RacePos[playerid][RaceIndex[playerid]+1][2], 5.0);
		}
	}
	return 1;
}
