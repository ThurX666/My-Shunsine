
// Admin Commands
CMD:dynarrest(playerid, params[]) {
	if (pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);

	new option[24], str[32];
	if (sscanf(params, "s[24]S()[32]", option, str)) {
		Usage(playerid, "/dynarrest [option]");
		SendClientMessageEx(playerid, COLOR_YELLOW, "[OPTIONS]: "WHITE_E"create, delete, position, cellpos");
		return 1;
	}
	if (!strcmp(option, "create")) {
		new id = Iter_Free(DynArrests), query[512];
		if(id == -1) return Error(playerid, "Can't add any more Dyn Arrest.");
		new Float: x, Float: y, Float: z;
		GetPlayerPos(playerid, x, y, z);

		DynArrest[id][arrestPos][0] = x;
		DynArrest[id][arrestPos][1] = y;
		DynArrest[id][arrestPos][2] = z;
		DynArrest[id][arrestInt] = GetPlayerInterior(playerid);
		DynArrest[id][arrestWorld] = GetPlayerVirtualWorld(playerid);
		
		new strings[128];
		DynArrest[id][arrestPickup] = CreateDynamicPickup(1247, 23, DynArrest[id][arrestPos][0], DynArrest[id][arrestPos][1], DynArrest[id][arrestPos][2], -1);
		format(strings, sizeof(strings), "{00FFFF}[id:%d] Arrest Point\n"YELLOW_E"/'arrest' "WHITE_E"arrest wanted player", id);
		DynArrest[id][arrestLabel] = CreateDynamic3DTextLabel(strings, COLOR_ARWIN, DynArrest[id][arrestPos][0], DynArrest[id][arrestPos][1], DynArrest[id][arrestPos][2], 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // arrest
		Iter_Add(DynArrests, id);
		
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO dynarrests SET id='%d', posx='%f', posy='%f', posz='%f', interior='%d', world='%d'", id, DynArrest[id][arrestPos][0], DynArrest[id][arrestPos][1], DynArrest[id][arrestPos][2], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
		mysql_tquery(g_SQL, query, "OnDynArrestCreated", "ii", playerid, id);
	} else if (!strcmp(option, "delete")) {
		new id, query[512];
		if (sscanf(str, "d", id)) return Usage(playerid, "/dynarrest delete [dynarrest id]");
		if(!Iter_Contains(DynArrests, id)) return Error(playerid, "Invalid ID.");
		DestroyDynamicPickup(DynArrest[id][arrestPickup]);
		DestroyDynamic3DTextLabel(DynArrest[id][arrestLabel]);
		Iter_Remove(DynArrests, id);
		
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM dynarrests WHERE id=%d", id);
		mysql_tquery(g_SQL, query);
		Servers(playerid, "You removed Dyn Arrest id %d.", id);
	} else if (!strcmp(option, "position")) {
		new id;
		if (sscanf(str, "d", id)) return Usage(playerid, "/dynarrest position [dynarrest id]");
		if(!Iter_Contains(DynArrests, id)) return Error(playerid, "Invalid ID.");
		new Float: x, Float: y, Float: z;
		GetPlayerPos(playerid, x, y, z);
		DestroyDynamicPickup(DynArrest[id][arrestPickup]);
		DestroyDynamic3DTextLabel(DynArrest[id][arrestLabel]);
		DynArrest[id][arrestPos][0] = x;
		DynArrest[id][arrestPos][1] = y;
		DynArrest[id][arrestPos][2] = z;
		DynArrest[id][arrestInt] = GetPlayerInterior(playerid);
		DynArrest[id][arrestWorld] = GetPlayerVirtualWorld(playerid);
		DynArrest_Save(id);
		new strings[128];
		DynArrest[id][arrestPickup] = CreateDynamicPickup(1247, 23, DynArrest[id][arrestPos][0], DynArrest[id][arrestPos][1], DynArrest[id][arrestPos][2], -1);
		format(strings, sizeof(strings), "{00FFFF}[id:%d] Arrest Point\n"YELLOW_E"/'arrest' "WHITE_E"arrest wanted player", id);
		DynArrest[id][arrestLabel] = CreateDynamic3DTextLabel(strings, COLOR_ARWIN, DynArrest[id][arrestPos][0], DynArrest[id][arrestPos][1], DynArrest[id][arrestPos][2], 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // arrest
	} else if (!strcmp(option, "cellpos")) {
		new id;
		if (sscanf(str, "d", id)) return Usage(playerid, "/dynarrest buttonint [dynarrest id]");
		if(!Iter_Contains(DynArrests, id)) return Error(playerid, "Invalid ID.");
		new Float: x, Float: y, Float: z;
		GetPlayerPos(playerid, x, y, z);
		DynArrest[id][arrestCell][0] = x;
		DynArrest[id][arrestCell][1] = y;
		DynArrest[id][arrestCell][2] = z;
		DynArrest[id][arrestIntCell] = GetPlayerInterior(playerid);
		DynArrest[id][arrestWorldCell] = GetPlayerVirtualWorld(playerid);
		DynArrest_Save(id);
	} 
	return 1;
}