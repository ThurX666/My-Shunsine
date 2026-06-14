CMD:radar(playerid, params[]) {
    switch (p_Direction[playerid]) {
		case 0: {
			p_Direction[playerid] = true;
			SendClientMessage(playerid, COLOR_BLUE, "PLD:{FFFFFF} Street radar is now turned "COL_GREEN"ON{FFFFFF}.");
		}
		case 1: {
			p_Direction[playerid] = false;
			SendClientMessage(playerid, COLOR_BLUE, "PLD:{FFFFFF} Street radar is now turned "COL_RED"OFF{FFFFFF}.");
		}
	}
	return 1;
}