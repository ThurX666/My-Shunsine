
function DoorFaction_Load() {
	new rows = cache_num_rows();

	for(new i; i < rows; i++) {
		cache_get_value_int(i, "ID", DoorFaction[i][dfID]);
		cache_get_value_int(i, "Model", DoorFaction[i][dfModel]);
        cache_get_value_int(i, "Faction", DoorFaction[i][dfFaction]);
		DoorFaction[i][dfStatus] = 0;
		cache_get_value_float(i, "PosX", DoorFaction[i][dfPos][0]);
		cache_get_value_float(i, "PosY", DoorFaction[i][dfPos][1]);
		cache_get_value_float(i, "PosZ", DoorFaction[i][dfPos][2]);
		cache_get_value_float(i, "RotX", DoorFaction[i][dfPos][3]);
		cache_get_value_float(i, "RotY", DoorFaction[i][dfPos][4]);
		cache_get_value_float(i, "RotZ", DoorFaction[i][dfPos][5]);
		cache_get_value_float(i, "MoveX", DoorFaction[i][dfMove][0]);
		cache_get_value_float(i, "MoveY", DoorFaction[i][dfMove][1]);
		cache_get_value_float(i, "MoveZ", DoorFaction[i][dfMove][2]);
		cache_get_value_float(i, "MoveRotX", DoorFaction[i][dfMove][3]);
		cache_get_value_float(i, "MoveRotY", DoorFaction[i][dfMove][4]);
		cache_get_value_float(i, "MoveRotZ", DoorFaction[i][dfMove][5]);
        cache_get_value_float(i, "PosXInt", DoorFaction[i][dfPosInt][0]);
		cache_get_value_float(i, "PosYInt", DoorFaction[i][dfPosInt][1]);
		cache_get_value_float(i, "PosZInt", DoorFaction[i][dfPosInt][2]);
		cache_get_value_float(i, "RotXInt", DoorFaction[i][dfPosInt][3]);
		cache_get_value_float(i, "RotYInt", DoorFaction[i][dfPosInt][4]);
		cache_get_value_float(i, "RotZInt", DoorFaction[i][dfPosInt][5]);
		cache_get_value_float(i, "PosXExt", DoorFaction[i][dfPosExt][0]);
		cache_get_value_float(i, "PosYExt", DoorFaction[i][dfPosExt][1]);
		cache_get_value_float(i, "PosZExt", DoorFaction[i][dfPosExt][2]);
		cache_get_value_float(i, "RotXExt", DoorFaction[i][dfPosExt][3]);
		cache_get_value_float(i, "RotYExt", DoorFaction[i][dfPosExt][4]);
		cache_get_value_float(i, "RotZExt", DoorFaction[i][dfPosExt][5]);

		Iter_Add(DoorsFaction, i);

		DoorFaction_Refresh(i);
	}
	printf("*** [Database: Loaded] door faction data (%d count)", rows);
	return 1;
}

DoorFaction_Create(modelid, faction, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
	new id = INVALID_ITERATOR_SLOT;

	if ((id = Iter_Free(DoorsFaction)) != INVALID_ITERATOR_SLOT) {
		Iter_Add(DoorsFaction, id);
		
		DoorFaction[id][dfModel] = modelid;
        DoorFaction[id][dfFaction] = faction;
		DoorFaction[id][dfStatus] = 0;
		DoorFaction[id][dfPos][0] = x;
		DoorFaction[id][dfPos][1] = y;
		DoorFaction[id][dfPos][2] = z;
		DoorFaction[id][dfPos][3] = rx;
		DoorFaction[id][dfPos][4] = ry;
		DoorFaction[id][dfPos][5] = rz;
		DoorFaction[id][dfMove][0] = x;
		DoorFaction[id][dfMove][1] = y;
		DoorFaction[id][dfMove][2] = z;
		DoorFaction[id][dfMove][3] = rx;
		DoorFaction[id][dfMove][4] = ry;
		DoorFaction[id][dfMove][5] = rz;

        DoorFaction[id][dfPosInt][0] = x;
        DoorFaction[id][dfPosInt][1] = y;
        DoorFaction[id][dfPosInt][2] = z;
        DoorFaction[id][dfPosInt][3] = rx;
        DoorFaction[id][dfPosInt][4] = ry;
        DoorFaction[id][dfPosInt][5] = rz;

        DoorFaction[id][dfPosExt][0] = x;
        DoorFaction[id][dfPosExt][1] = y;
        DoorFaction[id][dfPosExt][2] = z;
        DoorFaction[id][dfPosExt][3] = rx;
        DoorFaction[id][dfPosExt][4] = ry;
        DoorFaction[id][dfPosExt][5] = rz;

		new cQuery[2248];
		format(cQuery, sizeof(cQuery), "INSERT INTO `doorfaction` (`Model`) VALUES ('%d')", modelid);
		mysql_tquery(g_SQL, cQuery, "OnDoorFactionCreated", "d", id);
		return id;
	}
	return INVALID_ITERATOR_SLOT;
}

function OnDoorFactionCreated(id) {
	if (Iter_Contains(DoorsFaction, id)) {
		DoorFaction[id][dfID] = cache_insert_id();

		DoorFaction_Refresh(id);
		DoorFaction_Save(id);
		return 1;
	}
	return 0;
}

DoorFaction_Save(id) {
	new cQuery[5248];
	format(cQuery,sizeof(cQuery),"UPDATE `doorfaction` SET `Model` = '%d'", DoorFaction[id][dfModel]);
	format(cQuery,sizeof(cQuery), "%s, `Faction`='%d'", DoorFaction[id][dfFaction]);
	format(cQuery,sizeof(cQuery), "%s, `PosX`='%f'", DoorFaction[id][dfPos][0]);
	format(cQuery,sizeof(cQuery), "%s, `PosY`='%f'", DoorFaction[id][dfPos][1]);
	format(cQuery,sizeof(cQuery), "%s, `PosZ`='%f'", DoorFaction[id][dfPos][2]);
	format(cQuery,sizeof(cQuery), "%s, `RotX`='%f'", DoorFaction[id][dfPos][3]);
	format(cQuery,sizeof(cQuery), "%s, `RotY`='%f'", DoorFaction[id][dfPos][4]);
	format(cQuery,sizeof(cQuery), "%s, `RotZ`='%f'", DoorFaction[id][dfPos][5]);
	format(cQuery,sizeof(cQuery), "%s, `MoveX`='%f'", DoorFaction[id][dfMove][0]);
	format(cQuery,sizeof(cQuery), "%s, `MoveY`='%f'", DoorFaction[id][dfMove][1]);
	format(cQuery,sizeof(cQuery), "%s, `MoveZ`='%f'", DoorFaction[id][dfMove][2]);
	format(cQuery,sizeof(cQuery), "%s, `MoveRotX`='%f'", DoorFaction[id][dfMove][3]);
	format(cQuery,sizeof(cQuery), "%s, `MoveRotY`='%f'", DoorFaction[id][dfMove][4]);
	format(cQuery,sizeof(cQuery), "%s, `MoveRotZ`='%f'", DoorFaction[id][dfMove][5]);
	format(cQuery,sizeof(cQuery), "%s, `PosXInt`='%f'", DoorFaction[id][dfPosInt][0]);
	format(cQuery,sizeof(cQuery), "%s, `PosYInt`='%f'", DoorFaction[id][dfPosInt][1]);
	format(cQuery,sizeof(cQuery), "%s, `PosZInt`='%f'", DoorFaction[id][dfPosInt][2]);
	format(cQuery,sizeof(cQuery), "%s, `RotXInt`='%f'", DoorFaction[id][dfPosInt][3]);
	format(cQuery,sizeof(cQuery), "%s, `RotYInt`='%f'", DoorFaction[id][dfPosInt][4]);
	format(cQuery,sizeof(cQuery), "%s, `RotZInt`='%f'", DoorFaction[id][dfPosInt][5]);
	format(cQuery,sizeof(cQuery), "%s, `PosXExt`='%f'", DoorFaction[id][dfPosExt][0]);
	format(cQuery,sizeof(cQuery), "%s, `PosYExt`='%f'", DoorFaction[id][dfPosExt][1]);
	format(cQuery,sizeof(cQuery), "%s, `PosZExt`='%f'", DoorFaction[id][dfPosExt][2]);
	format(cQuery,sizeof(cQuery), "%s, `RotXExt`='%f'", DoorFaction[id][dfPosExt][3]);
	format(cQuery,sizeof(cQuery), "%s, `RotYExt`='%f'", DoorFaction[id][dfPosExt][4]);
	format(cQuery,sizeof(cQuery), "%s, `RotZExt`='%f'", DoorFaction[id][dfPosExt][5]);
	format(cQuery,sizeof(cQuery), "%s WHERE `ID` = '%d'", DoorFaction[id][dfID]);
	return mysql_tquery(g_SQL, cQuery);
}

DoorFaction_Delete(id) {
	if (Iter_Contains(DoorsFaction, id)) {
		Iter_Remove(DoorsFaction, id);
		new cQuery[2248];
		format(cQuery, sizeof(cQuery), "DELETE FROM `doorfaction` WHERE `ID` = '%d'", DoorFaction[id][dfID]);
		mysql_tquery(g_SQL, cQuery);
		if (IsValidDynamicObject(DoorFaction[id][dfObj]))
		DestroyDynamicObject(DoorFaction[id][dfObj]);
        if (IsValidDynamicObject(DoorFaction[id][dfObjDInt]))
		DestroyDynamicObject(DoorFaction[id][dfObjDInt]);
        if (IsValidDynamicObject(DoorFaction[id][dfObjDExt]))
		DestroyDynamicObject(DoorFaction[id][dfObjDExt]);
		DoorFaction[id][dfID] = 0;
		DoorFaction[id][dfObj] = DoorFaction[id][dfObjDInt] = DoorFaction[id][dfObjDExt] = INVALID_STREAMER_ID;
		return 1;
	}
	return 0;
}

DoorFaction_Refresh(id) {
    if (IsValidDynamicObject(DoorFaction[id][dfObj])) DestroyDynamicObject(DoorFaction[id][dfObj]);
    if (IsValidDynamicObject(DoorFaction[id][dfObjDInt])) DestroyDynamicObject(DoorFaction[id][dfObjDInt]);
    if (IsValidDynamicObject(DoorFaction[id][dfObjDExt])) DestroyDynamicObject(DoorFaction[id][dfObjDExt]);
	DoorFaction[id][dfObj] = CreateDynamicObject(DoorFaction[id][dfModel], 
    DoorFaction[id][dfPos][0],
	DoorFaction[id][dfPos][1],
	DoorFaction[id][dfPos][2],
	DoorFaction[id][dfPos][3],
	DoorFaction[id][dfPos][4],
	DoorFaction[id][dfPos][5]);
    DoorFaction[id][dfObjDInt] = CreateDynamicObject(19273, 
    DoorFaction[id][dfPosInt][0],
	DoorFaction[id][dfPosInt][1],
	DoorFaction[id][dfPosInt][2],
	DoorFaction[id][dfPosInt][3],
	DoorFaction[id][dfPosInt][4],
	DoorFaction[id][dfPosInt][5]);
    DoorFaction[id][dfObjDExt] = CreateDynamicObject(19273, 
    DoorFaction[id][dfPosExt][0],
	DoorFaction[id][dfPosExt][1],
	DoorFaction[id][dfPosExt][2],
	DoorFaction[id][dfPosExt][3],
	DoorFaction[id][dfPosExt][4],
	DoorFaction[id][dfPosExt][5]);
	DoorFaction[id][dfStatus] = 0;
	DoorFaction_Sync(id);
	return 1;
}

DoorFaction_Sync(id) {
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObj],E_STREAMER_MODEL_ID,DoorFaction[id][dfModel]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObj],E_STREAMER_X,DoorFaction[id][dfPos][0]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObj],E_STREAMER_Y,DoorFaction[id][dfPos][1]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObj],E_STREAMER_Z,DoorFaction[id][dfPos][2]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObj],E_STREAMER_R_X,DoorFaction[id][dfPos][3]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObj],E_STREAMER_R_Y,DoorFaction[id][dfPos][4]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObj],E_STREAMER_R_Z,DoorFaction[id][dfPos][5]);

    Streamer_SetIntData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDInt],E_STREAMER_MODEL_ID,19273);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDInt],E_STREAMER_X,DoorFaction[id][dfPosInt][0]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDInt],E_STREAMER_Y,DoorFaction[id][dfPosInt][1]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDInt],E_STREAMER_Z,DoorFaction[id][dfPosInt][2]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDInt],E_STREAMER_R_X,DoorFaction[id][dfPosInt][3]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDInt],E_STREAMER_R_Y,DoorFaction[id][dfPosInt][4]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDInt],E_STREAMER_R_Z,DoorFaction[id][dfPosInt][5]);

    Streamer_SetIntData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDExt],E_STREAMER_MODEL_ID,19273);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDExt],E_STREAMER_X,DoorFaction[id][dfPosExt][0]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDExt],E_STREAMER_Y,DoorFaction[id][dfPosExt][1]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDExt],E_STREAMER_Z,DoorFaction[id][dfPosExt][2]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDExt],E_STREAMER_R_X,DoorFaction[id][dfPosExt][3]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDExt],E_STREAMER_R_Y,DoorFaction[id][dfPosExt][4]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,DoorFaction[id][dfObjDExt],E_STREAMER_R_Z,DoorFaction[id][dfPosExt][5]);
	return 1;
}

DoorFaction_Nearest(playerid) {
  	new id = -1, Float: playerdist, Float: tempdist = 9999.0;
	
	foreach (new i : DoorsFaction)
	{
		playerdist = GetPlayerDistanceFromPoint(playerid, DoorFaction[i][dfPos][0], DoorFaction[i][dfPos][1], DoorFaction[i][dfPos][2]);
		if(playerdist > 10.0) continue;
		if(playerdist <= tempdist) {
			tempdist = playerdist;
			id = i;
		}
	}
  	return id;
}

// DoorFaction_Operate(playerid, id) {
// 	new vehicleid = GetPlayerVehicleID(playerid);
// 	if (DoorFaction[id][dfStatus] == 0) 
// 	{
// 		DoorFaction[id][dfStatus] = 1;
		
// 		if (DoorFaction[id][dfModel] == 968) {
// 			DoorFaction_Timer[id] = 1;

// 			RotateDynamicObject(DoorFaction[id][dfObj], DoorFaction[id][dfMove][3], DoorFaction[id][dfMove][4], DoorFaction[id][dfMove][5], 1);

// 			SetTimerEx("DoorFaction_Closed", 5000, false, "d", id);
// 			if(IsFactionVeh(vehicleid) || IsABusABVeh(GetPlayerVehicleID(playerid)) || IsABusCDVeh(GetPlayerVehicleID(playerid))) {
// 				SendClientMessage(playerid,COLOR_ARWIN,"TOLL: {FFFFFF}Government Issued vehicle pay no toll access");
// 				return 1;
// 			}
// 			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 403 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 514 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 515) {
// 				if (pData[playerid][pPayToll] > 0) {
// 					pData[playerid][pPayToll] -= 2;
// 					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: {FFFFFF}Used {00FFFF}2 toll card point {FFFFFF}to pay toll access.");
// 				} else {
// 					GivePlayerMoneyEx(playerid, -150);
// 					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: "WHITE_E"Kamu telah membayar Toll "GREEN_E"$1.50");
// 				}
// 			}
// 			else {
// 				if (pData[playerid][pPayToll] > 0) {
// 					pData[playerid][pPayToll] -= 1;
// 					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: {FFFFFF}Used {00FFFF}1 toll card point {FFFFFF}to pay toll access.");
// 				} else {
// 					GivePlayerMoneyEx(playerid, -50);
// 					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: "WHITE_E"Kamu telah membayar Toll "GREEN_E"$0.50");
// 				}
// 			}
// 		} else {
// 			MoveDynamicObject(DoorFaction[id][dfObj], MoveArrTollGate{id});

// 			DoorFaction_Timer[id] = 1;

// 			SetTimerEx("DoorFaction_Closed", 5000, false, "d", id);

// 			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 403 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 514 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 515) {
// 				if (pData[playerid][pPayToll] > 0) {
// 					pData[playerid][pPayToll] -= 2;
// 					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: {FFFFFF}Used {00FFFF}2 toll card point {FFFFFF}to pay toll access.");
// 				} else {
// 					GivePlayerMoneyEx(playerid, -150);
// 					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: "WHITE_E"Kamu telah membayar Toll "GREEN_E"$1.50");
// 				}
// 			}
// 			else {
// 				if (pData[playerid][pPayToll] > 0) {
// 					pData[playerid][pPayToll] -= 1;
// 					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: {FFFFFF}Used {00FFFF}1 toll card point {FFFFFF}to pay toll access.");
// 				} else {
// 					GivePlayerMoneyEx(playerid, -50);
// 					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: "WHITE_E"Kamu telah membayar Toll "GREEN_E"$0.50");
// 				}
// 			}
// 		}
// 	} else {
// 		if (DoorFaction_Timer[id]) {
// 		Error(playerid, "Please wait untill the gate is closed!");
// 		}
// 	}
// 	return 1;
// }

function DoorFaction_Closed(id) {
	if (DoorFaction[id][dfModel] == 968) {
		DoorFaction[id][dfStatus] = 0;
		RotateDynamicObject(DoorFaction[id][dfObj], DoorFaction[id][dfPos][3], DoorFaction[id][dfPos][4], DoorFaction[id][dfPos][5], 1.0);
		DoorFaction_Timer[id] = 0;
	} else {
		DoorFaction[id][dfStatus] = 0;
		MoveDynamicObject(DoorFaction[id][dfObj], DoorFaction[id][dfPos][0], DoorFaction[id][dfPos][1], DoorFaction[id][dfPos][2], 3.0, DoorFaction[id][dfPos][3], DoorFaction[id][dfPos][4], DoorFaction[id][dfPos][5]);
		DoorFaction_Timer[id] = 0;
	}
	return 1;
}

DoorFaction_SetObjectPos(id, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
	if (Iter_Contains(DoorsFaction, id)) {
		DoorFaction[id][dfPos][0] = x;
		DoorFaction[id][dfPos][1] = y;
		DoorFaction[id][dfPos][2] = z;
		DoorFaction[id][dfPos][3] = rx;
		DoorFaction[id][dfPos][4] = ry;
		DoorFaction[id][dfPos][5] = rz;
		return 1;
	}
	return 0;
}

DoorFaction_SetObjectMove(id, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
	if (Iter_Contains(DoorsFaction, id)) {
		DoorFaction[id][dfMove][0] = x;
		DoorFaction[id][dfMove][1] = y;
		DoorFaction[id][dfMove][2] = z;
		DoorFaction[id][dfMove][3] = rx;
		DoorFaction[id][dfMove][4] = ry;
		DoorFaction[id][dfMove][5] = rz;
		return 1;
	}
	return 0;
}
