
CMD:paytoll(playerid, params[]) {
	if (!IsPlayerConnected(playerid)) return Error(playerid, "You are not logged in!");
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return Error(playerid, "You must to be driver to use this command!");
	foreach(new id : Tolls) if(IsPlayerInDynamicArea(playerid, TollGate[id][tZone])) TollGate_Operate(playerid, id);
	else Error(playerid, "You are not in any toll gate.");
	return 1;
}

// Admin Commands
CMD:tollgate(playerid, params[]) {
	if (pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);

	new option[24], str[32];
	if (sscanf(params, "s[24]S()[32]", option, str)) {
		Usage(playerid, "/tollgate [option]");
		SendClientMessageEx(playerid, COLOR_YELLOW, "[OPTIONS]: "WHITE_E"create, delete, position, move, near");
		return 1;
	}

	if (!strcmp(option, "create")) {
		new id, modelid, Float:playerPos[3], Float:rotate[3];
		if (sscanf(str, "d", modelid)) return Usage(playerid, "/tollgate create [modelid]");

		GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
		rotate[0] = 0.0;
		rotate[1] = 0.0;
		rotate[2] = 0.0;

		id = TollGate_Create(modelid, playerPos[0], playerPos[1], playerPos[2], rotate[0], rotate[1], rotate[2]);

		SendCustomMessage(playerid, "TOLLGATE", "You've successfully created toll gate id: "YELLOW_E"%d", id);
	} else if (!strcmp(option, "delete")) {
		new id;
		if (sscanf(str, "d", id)) return Usage(playerid, "/tollgate delete [tollgate id]");

		if (!Iter_Contains(Tolls, id)) return Error(playerid, "Invalid toll gate ID!");

		TollGate_Delete(id);

		SendCustomMessage(playerid, "TOLLGATE", "You've successfully deleted toll gate id: "YELLOW_E"%d", id);
	} else if (!strcmp(option, "position")) {
		new id;
		if (sscanf(str, "d", id)) return Usage(playerid, "/tollgate position [tollgate id]");

		if (!Iter_Contains(Tolls, id)) return Error(playerid, "Invalid toll gate ID!");

		SetPVarInt(playerid, "editTollGateID", id);
		SetPVarInt(playerid, "editTollGateMode", 0);

		EditDynamicObject(playerid, TollGate[id][tObj]);
	} else if (!strcmp(option, "move")) {
		new id;
		if (sscanf(str, "d", id)) return Usage(playerid, "/tollgate move [tollgate id]");

		if (!Iter_Contains(Tolls, id)) return Error(playerid, "Invalid toll gate ID!");

		SetPVarInt(playerid, "editTollGateID", id);
		SetPVarInt(playerid, "editTollGateMode", 1);

		EditDynamicObject(playerid, TollGate[id][tObj]);
	} else if (!strcmp(option, "near")) {
		new id = -1;

		if ((id = TollGate_Nearest(playerid)) != -1) {
		SendCustomMessage(playerid, "TOLLGATE", "Nearest toll gate id: "YELLOW_E"%d", id);
		}
	}
	return 1;
}