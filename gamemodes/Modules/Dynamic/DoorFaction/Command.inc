
// Admin Commands
CMD:doorfaction(playerid, params[]) {
	if (pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);

	new option[24], str[32];
	if (sscanf(params, "s[24]S()[32]", option, str)) {
		Usage(playerid, "/doorfaction [option]");
		SendClientMessageEx(playerid, COLOR_YELLOW, "[OPTIONS]: "WHITE_E"create, delete, position, move, near, buttonint, buttonext");
		return 1;
	}
	
	if (!strcmp(option, "create")) {
		new id, modelid, faction, Float:playerPos[3], Float:rotate[3];
		if (sscanf(str, "dd", modelid, faction)) return Usage(playerid, "/doorfaction create [modelid] [faction (1.SAPD 2.SAGS 3.SAMD 4.SANEWS)]");
		GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
		rotate[0] = 0.0;
		rotate[1] = 0.0;
		rotate[2] = 0.0;

		id = DoorFaction_Create(modelid, faction, playerPos[0], playerPos[1], playerPos[2], rotate[0], rotate[1], rotate[2]);

		SendCustomMessage(playerid, "DOOR", "You've successfully created door faction id: "YELLOW_E"%d", id);
	} else if (!strcmp(option, "delete")) {
		new id;
		if (sscanf(str, "d", id)) return Usage(playerid, "/doorfaction delete [doorF id]");
		if (!Iter_Contains(DoorsFaction, id)) return Error(playerid, "Invalid door faction ID!");
		DoorFaction_Delete(id);
		SendCustomMessage(playerid, "DOOR", "You've successfully deleted door faction id: "YELLOW_E"%d", id);
	} else if (!strcmp(option, "position")) {
		new id;
		if (sscanf(str, "d", id)) return Usage(playerid, "/doorfaction position [doorF id]");
		
		if (!Iter_Contains(DoorsFaction, id)) return Error(playerid, "Invalid door faction ID!");

		SetPVarInt(playerid, "editDoorFactionID", id);
		SetPVarInt(playerid, "editDoorFactionMode", 0);
		EditDynamicObject(playerid, DoorFaction[id][dfObj]);
	} else if (!strcmp(option, "move")) {
		new id;
		if (sscanf(str, "d", id)) return Usage(playerid, "/doorfaction move [doorF id]");
		
		if (!Iter_Contains(DoorsFaction, id)) return Error(playerid, "Invalid door faction ID!");
		
		SetPVarInt(playerid, "editDoorFactionID", id);
		SetPVarInt(playerid, "editDoorFactionMode", 1);

		EditDynamicObject(playerid, DoorFaction[id][dfObj]);
	} else if (!strcmp(option, "near")) {
		new id = -1;
		if ((id = DoorFaction_Nearest(playerid)) != -1) {
		SendCustomMessage(playerid, "DOOR", "Nearest door faction id: "YELLOW_E"%d", id);
		}
	} else if (!strcmp(option, "buttonint")) {
		new id;
		if (sscanf(str, "d", id)) return Usage(playerid, "/doorfaction buttonint [doorF id]");
		if (!Iter_Contains(DoorsFaction, id)) return Error(playerid, "Invalid door faction ID!");
		editDoorFactionID[playerid] = id;
		editDoorFactioMode[playerid] = 2;

		EditDynamicObject(playerid, DoorFaction[id][dfObjDInt]);
	} else if (!strcmp(option, "buttonext")) {
		new id;
		if (sscanf(str, "d", id)) return Usage(playerid, "/doorfaction buttonext [doorF id]");
		if (!Iter_Contains(DoorsFaction, id)) return Error(playerid, "Invalid door faction ID!");
		editDoorFactionID[playerid] = id;
		editDoorFactioMode[playerid] = 3;

		EditDynamicObject(playerid, DoorFaction[id][dfObjDExt]);
	}
	return 1;
}