
function TollGate_Load() {
	new rows = cache_num_rows();

	for (new i = 0; i < rows; i ++) {
		cache_get_value_int(i, "ID", TollGate[i][tID]);
		cache_get_value_int(i, "Model", TollGate[i][tModel]);
		TollGate[i][tStatus] = 0;
		cache_get_value_float(i, "PosX", TollGate[i][tPos][0]);
		cache_get_value_float(i, "PosY", TollGate[i][tPos][1]);
		cache_get_value_float(i, "PosZ", TollGate[i][tPos][2]);
		cache_get_value_float(i, "RotX", TollGate[i][tPos][3]);
		cache_get_value_float(i, "RotY", TollGate[i][tPos][4]);
		cache_get_value_float(i, "RotZ", TollGate[i][tPos][5]);
		cache_get_value_float(i, "MoveX", TollGate[i][tMove][0]);
		cache_get_value_float(i, "MoveY", TollGate[i][tMove][1]);
		cache_get_value_float(i, "MoveZ", TollGate[i][tMove][2]);
		cache_get_value_float(i, "MoveRotX", TollGate[i][tMove][3]);
		cache_get_value_float(i, "MoveRotY", TollGate[i][tMove][4]);
		cache_get_value_float(i, "MoveRotZ", TollGate[i][tMove][5]);

		Iter_Add(Tolls, i);

		TollGate_Refresh(i);
	}
	printf("*** [Database: Loaded] toll gate data (%d count)", rows);
	return 1;
}

TollGate_Create(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
	new id = INVALID_ITERATOR_SLOT;

	if ((id = Iter_Free(Tolls)) != INVALID_ITERATOR_SLOT) {
		Iter_Add(Tolls, id);
		
		TollGate[id][tModel] = modelid;
		TollGate[id][tStatus] = 0;
		TollGate[id][tPos][0] = x;
		TollGate[id][tPos][1] = y;
		TollGate[id][tPos][2] = z;
		TollGate[id][tPos][3] = rx;
		TollGate[id][tPos][4] = ry;
		TollGate[id][tPos][5] = rz;
		TollGate[id][tMove][0] = x;
		TollGate[id][tMove][1] = y;
		TollGate[id][tMove][2] = z;
		TollGate[id][tMove][3] = rx;
		TollGate[id][tMove][4] = ry;
		TollGate[id][tMove][5] = rz;
		new cQuery[2248];
		format(cQuery, sizeof(cQuery), "INSERT INTO `tollgate` (`Model`) VALUES ('%d')", modelid);
		mysql_tquery(g_SQL, cQuery, "OnTollGateCreated", "d", id);
		return id;
	}
	return INVALID_ITERATOR_SLOT;
}

function OnTollGateCreated(id) {
	if (Iter_Contains(Tolls, id)) {
		TollGate[id][tID] = cache_insert_id();

		TollGate_Refresh(id);
		TollGate_Save(id);
		return 1;
	}
	return 0;
}

TollGate_Save(id) {
	new query[650];

	format(query,sizeof(query),"UPDATE `tollgate` SET `Model` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `RotX` = '%f', `RotY` = '%f', `RotZ` = '%f', `MoveX` = '%f', `MoveY` = '%f', `MoveZ` = '%f', `MoveRotX` = '%f', `MoveRotY` = '%f', `MoveRotZ` = '%f' WHERE `ID` = '%d'",
	TollGate[id][tModel],
	TollGate[id][tPos][0],
	TollGate[id][tPos][1],
	TollGate[id][tPos][2],
	TollGate[id][tPos][3],
	TollGate[id][tPos][4],
	TollGate[id][tPos][5],
	TollGate[id][tMove][0],
	TollGate[id][tMove][1],
	TollGate[id][tMove][2],
	TollGate[id][tMove][3],
	TollGate[id][tMove][4],
	TollGate[id][tMove][5],
	TollGate[id][tID]
	);
	return mysql_tquery(g_SQL, query);
}

TollGate_Delete(id) {
	if (Iter_Contains(Tolls, id)) {
		Iter_Remove(Tolls, id);
		new cQuery[2248];
		format(cQuery, sizeof(cQuery), "DELETE FROM `tollgate` WHERE `ID` = '%d'", TollGate[id][tID]);
		mysql_tquery(g_SQL, cQuery);
		if (IsValidDynamicObject(TollGate[id][tObj]))
		DestroyDynamicObject(TollGate[id][tObj]);

		TollGate[id][tID] = 0;
		TollGate[id][tObj] = INVALID_STREAMER_ID;
		return 1;
	}
	return 0;
}

TollGate_Refresh(id) {
	if (!IsValidDynamicObject(TollGate[id][tObj])) TollGate[id][tObj] = CreateDynamicObject(TollGate[id][tModel], PosArrTollGate{id});
	TollGate[id][tZone] = CreateDynamicSphere(TollGate[id][tPos][0], TollGate[id][tPos][1], TollGate[id][tPos][2], 10, 0, 0);
	TollGate_Sync(id);
	TollGate[id][tStatus] = 0;
	return 1;
}

TollGate_Sync(id) {
	Streamer_SetIntData(STREAMER_TYPE_OBJECT,TollGate[id][tObj],E_STREAMER_MODEL_ID,TollGate[id][tModel]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,TollGate[id][tObj],E_STREAMER_X,TollGate[id][tPos][0]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,TollGate[id][tObj],E_STREAMER_Y,TollGate[id][tPos][1]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,TollGate[id][tObj],E_STREAMER_Z,TollGate[id][tPos][2]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,TollGate[id][tObj],E_STREAMER_R_X,TollGate[id][tPos][3]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,TollGate[id][tObj],E_STREAMER_R_Y,TollGate[id][tPos][4]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT,TollGate[id][tObj],E_STREAMER_R_Z,TollGate[id][tPos][5]);
	return 1;
}

TollGate_Nearest(playerid) {
  	new id = -1, Float: playerdist, Float: tempdist = 9999.0;
	
	foreach (new i : Tolls)
	{
		playerdist = GetPlayerDistanceFromPoint(playerid, TollGate[i][tPos][0], TollGate[i][tPos][1], TollGate[i][tPos][2]);
		if(playerdist > 10.0) continue;
		if(playerdist <= tempdist) {
			tempdist = playerdist;
			id = i;
		}
	}
  	return id;
}

TollGate_Operate(playerid, id) {
	new vehicleid = GetPlayerVehicleID(playerid);
	if (TollGate[id][tStatus] == 0) 
	{
		TollGate[id][tStatus] = 1;
		
		if (TollGate[id][tModel] == 968) {
			TollGate_Timer[id] = 1;

			RotateDynamicObject(TollGate[id][tObj], TollGate[id][tMove][3], TollGate[id][tMove][4], TollGate[id][tMove][5], 1);

			SetTimerEx("TollGate_Closed", 5000, false, "d", id);
			if(IsFactionVeh(vehicleid) || IsABusABVeh(GetPlayerVehicleID(playerid)) || IsABusCDVeh(GetPlayerVehicleID(playerid))) {
				SendClientMessage(playerid,COLOR_ARWIN,"TOLL: {FFFFFF}Government Issued vehicle pay no toll access");
				return 1;
			}
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 403 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 514 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 515) {
				if (pData[playerid][pPayToll] > 0) {
					pData[playerid][pPayToll] -= 2;
					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: {FFFFFF}Used {00FFFF}2 toll card point {FFFFFF}to pay toll access.");
				} else {
					GivePlayerMoneyEx(playerid, -150);
					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: "WHITE_E"Kamu telah membayar Toll "GREEN_E"$1.50");
				}
			}
			else {
				if (pData[playerid][pPayToll] > 0) {
					pData[playerid][pPayToll] -= 1;
					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: {FFFFFF}Used {00FFFF}1 toll card point {FFFFFF}to pay toll access.");
				} else {
					GivePlayerMoneyEx(playerid, -50);
					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: "WHITE_E"Kamu telah membayar Toll "GREEN_E"$0.50");
				}
			}
		} else {
			MoveDynamicObject(TollGate[id][tObj], MoveArrTollGate{id});

			TollGate_Timer[id] = 1;

			SetTimerEx("TollGate_Closed", 5000, false, "d", id);

			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 403 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 514 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 515) {
				if (pData[playerid][pPayToll] > 0) {
					pData[playerid][pPayToll] -= 2;
					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: {FFFFFF}Used {00FFFF}2 toll card point {FFFFFF}to pay toll access.");
				} else {
					GivePlayerMoneyEx(playerid, -150);
					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: "WHITE_E"Kamu telah membayar Toll "GREEN_E"$1.50");
				}
			}
			else {
				if (pData[playerid][pPayToll] > 0) {
					pData[playerid][pPayToll] -= 1;
					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: {FFFFFF}Used {00FFFF}1 toll card point {FFFFFF}to pay toll access.");
				} else {
					GivePlayerMoneyEx(playerid, -50);
					SendClientMessage(playerid,COLOR_ARWIN,"TOLL: "WHITE_E"Kamu telah membayar Toll "GREEN_E"$0.50");
				}
			}
		}
	} else {
		if (TollGate_Timer[id]) {
		Error(playerid, "Please wait untill the gate is closed!");
		}
	}
	return 1;
}

function TollGate_Closed(id) {
	if (TollGate[id][tModel] == 968) {
		TollGate[id][tStatus] = 0;
		RotateDynamicObject(TollGate[id][tObj], TollGate[id][tPos][3], TollGate[id][tPos][4], TollGate[id][tPos][5], 1.0);
		TollGate_Timer[id] = 0;
	} else {
		TollGate[id][tStatus] = 0;
		MoveDynamicObject(TollGate[id][tObj], TollGate[id][tPos][0], TollGate[id][tPos][1], TollGate[id][tPos][2], 3.0, TollGate[id][tPos][3], TollGate[id][tPos][4], TollGate[id][tPos][5]);
		TollGate_Timer[id] = 0;
	}
	return 1;
}

TollGate_SetObjectPos(id, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
	if (Iter_Contains(Tolls, id)) {
		TollGate[id][tPos][0] = x;
		TollGate[id][tPos][1] = y;
		TollGate[id][tPos][2] = z;
		TollGate[id][tPos][3] = rx;
		TollGate[id][tPos][4] = ry;
		TollGate[id][tPos][5] = rz;
		return 1;
	}
	return 0;
}

TollGate_SetObjectMove(id, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
	if (Iter_Contains(Tolls, id)) {
		TollGate[id][tMove][0] = x;
		TollGate[id][tMove][1] = y;
		TollGate[id][tMove][2] = z;
		TollGate[id][tMove][3] = rx;
		TollGate[id][tMove][4] = ry;
		TollGate[id][tMove][5] = rz;
		return 1;
	}
	return 0;
}

RotateDynamicObject(objectid, Float:rotX, Float:rotY, Float:rotZ, Float:Speed)
{
	new Float:X, Float:Y, Float:Z;
	new Float:SpeedConverted = floatmul(Speed, 0.01);
	GetDynamicObjectPos(objectid, X, Y, Z);
	SetDynamicObjectPos(objectid, X, Y, floatadd(Z, 0.01));
	MoveDynamicObject(objectid, X, Y, Z, SpeedConverted, rotX, rotY, rotZ);
	return 1;
}
