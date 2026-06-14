
function SuiteRoomCreate(suiteid) {
  SuiteRoom_Save(suiteid);
}

SuiteRoom_Inside(playerid) {
  foreach (new suiteid : SuiteRooms) if (IsPlayerInDynamicArea(playerid, SuiteRoom[suiteid][suiteRoomArea]) && GetPlayerVirtualWorld(playerid) == SuiteRoom[suiteid][suiteRoomWorld] && GetPlayerInterior(playerid) == SuiteRoom[suiteid][suiteRoomInterior]) {
    return suiteid;
  }
  return -1;
}

Owner_SuiteRoom(playerid, suiteid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(suiteid == -1) return 0;
	if(!strcmp(SuiteRoom[suiteid][suiteRoomOwner], pData[playerid][pName], true)) return 1;
	return 0;
}

SuiteRoom_AreaPos(suiteid, type, Float:z) {
  switch(type) {
    case 1: {
      SuiteRoom[suiteid][suiteRoomAreaPos][0] = 1806.7174;
      SuiteRoom[suiteid][suiteRoomAreaPos][1] = -1270.2147;
      SuiteRoom[suiteid][suiteRoomAreaPos][2] = 1835.4160;
      SuiteRoom[suiteid][suiteRoomAreaPos][3] = -1300.7548;
      SuiteRoom[suiteid][suiteRoomAreaPos][4] = z;
    }
    case 2: {
      SuiteRoom[suiteid][suiteRoomAreaPos][0] = 1806.7251;
      SuiteRoom[suiteid][suiteRoomAreaPos][1] = -1301.7051;
      SuiteRoom[suiteid][suiteRoomAreaPos][2] = 1835.0958;
      SuiteRoom[suiteid][suiteRoomAreaPos][3] = -1318.6306;
      SuiteRoom[suiteid][suiteRoomAreaPos][4] = z;
    }
    case 3: {
      SuiteRoom[suiteid][suiteRoomAreaPos][0] = 1800.8494;
      SuiteRoom[suiteid][suiteRoomAreaPos][1] = -1312.5021;
      SuiteRoom[suiteid][suiteRoomAreaPos][2] = 1771.3920;
      SuiteRoom[suiteid][suiteRoomAreaPos][3] = -1301.7052;
      SuiteRoom[suiteid][suiteRoomAreaPos][4] = z;
    }
  }
  return 1;
}

SuiteRoom_Delete(suiteid) {
  if(!Iter_Contains(SuiteRooms, suiteid)) return 0;
  
  if(IsValidDynamicArea(SuiteRoom[suiteid][suiteRoomArea])) DestroyDynamicArea(SuiteRoom[suiteid][suiteRoomArea]);
  if(IsValidDynamicObject(SuiteRoom[suiteid][suiteObjectDoors])) DestroyDynamicObject(SuiteRoom[suiteid][suiteObjectDoors]);
  if(IsValidDynamicObject(SuiteRoom[suiteid][suiteObjectButtons])) DestroyDynamicObject(SuiteRoom[suiteid][suiteObjectButtons]);
  if(IsValidDynamicObject(SuiteRoom[suiteid][suiteObjectText])) DestroyDynamicObject(SuiteRoom[suiteid][suiteObjectText]);
  SuiteRoom[suiteid][suiteRoomArea] = INVALID_STREAMER_ID;
  new query[128];
  mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `suiteroom` WHERE `ID`='%d'", SuiteRoom[suiteid][suiteRoomID]);
  mysql_tquery(g_SQL, query);

  SuiteStructure_DeleteAll(suiteid);
  SuiteFurniture_DeleteAll(suiteid);

  new tmp_SuiteRoom[suiteRoom];
  SuiteRoom[suiteid] = tmp_SuiteRoom;
  Iter_Remove(SuiteRooms, suiteid);
  return 1;
}

SuiteRoom_Refresh(suiteid) {
    new string[212];
    new Float:areaMinX = SuiteRoom[suiteid][suiteRoomAreaPos][0],
    Float:areaMinY = SuiteRoom[suiteid][suiteRoomAreaPos][1],
    Float:areaMaxX = SuiteRoom[suiteid][suiteRoomAreaPos][2],
    Float:areaMaxY = SuiteRoom[suiteid][suiteRoomAreaPos][3],
    Float:areaZ = SuiteRoom[suiteid][suiteRoomAreaPos][4],
    World = SuiteRoom[suiteid][suiteRoomWorld],
    Interior = SuiteRoom[suiteid][suiteRoomInterior];
    if(suiteid != -1) {
      if(IsValidDynamicObject(SuiteRoom[suiteid][suiteObjectDoors])) DestroyDynamicObject(SuiteRoom[suiteid][suiteObjectDoors]);
      if(IsValidDynamicObject(SuiteRoom[suiteid][suiteObjectButtons])) DestroyDynamicObject(SuiteRoom[suiteid][suiteObjectButtons]);
      if(IsValidDynamicObject(SuiteRoom[suiteid][suiteObjectText])) DestroyDynamicObject(SuiteRoom[suiteid][suiteObjectText]);
      if(strcmp(SuiteRoom[suiteid][suiteRoomOwner], "-")) format(string, sizeof(string), ""RED_E"[SR:%d]\n"AQUA_E"%s", suiteid, SuiteRoom[suiteid][suiteRoomOwner]);
      else format(string, sizeof(string), ""RED_E"[SR:%d]\n"AQUA_E"Price: "GREEN_E"$%s", suiteid, FormatMoney(SuiteRoom[suiteid][suiteRoomPrice]));
      
      if(SuiteRoom[suiteid][suiteRoomButtons][0] != 0) {
        SuiteRoom[suiteid][suiteObjectButtons] = CreateDynamicObject(19273, SuiteRoom[suiteid][suiteRoomButtons][0], SuiteRoom[suiteid][suiteRoomButtons][1], SuiteRoom[suiteid][suiteRoomButtons][2]-0.5, SuiteRoom[suiteid][suiteRoomButtons][3], SuiteRoom[suiteid][suiteRoomButtons][4], SuiteRoom[suiteid][suiteRoomButtons][5], -1, -1, -1, 300.00, 300.00); 
        SuiteRoom[suiteid][suiteObjectText] = CreateDynamicObject(2714, SuiteRoom[suiteid][suiteRoomButtons][0], SuiteRoom[suiteid][suiteRoomButtons][1], SuiteRoom[suiteid][suiteRoomButtons][2], SuiteRoom[suiteid][suiteRoomButtons][3], SuiteRoom[suiteid][suiteRoomButtons][4], SuiteRoom[suiteid][suiteRoomButtons][5], -1, -1, -1, 300.00, 300.00); 
        SetDynamicObjectMaterialText(SuiteRoom[suiteid][suiteObjectText], 0, string, 100, "Arial", 30, 1, 0xFFFFFFFF, 0x56A4E4FF, 1);
      }
      switch(SuiteRoom[suiteid][suiteRoomLocked])
      {
        case 0: { //Close
          SuiteRoom[suiteid][suiteObjectDoors] = CreateDynamicObject(1569,  SuiteRoom[suiteid][suiteRoomDoors][0], SuiteRoom[suiteid][suiteRoomDoors][1], SuiteRoom[suiteid][suiteRoomDoors][2], SuiteRoom[suiteid][suiteRoomDoors][3], SuiteRoom[suiteid][suiteRoomDoors][4], SuiteRoom[suiteid][suiteRoomDoors][5], -1, -1, -1, 300.00, 300.00); 
        }
        case 1: { //Open
          SuiteRoom[suiteid][suiteObjectDoors] = CreateDynamicObject(1569,  SuiteRoom[suiteid][suiteRoomDoors][0], SuiteRoom[suiteid][suiteRoomDoors][1]+1.6, SuiteRoom[suiteid][suiteRoomDoors][2], SuiteRoom[suiteid][suiteRoomDoors][3], SuiteRoom[suiteid][suiteRoomDoors][4], SuiteRoom[suiteid][suiteRoomDoors][5], -1, -1, -1, 300.00, 300.00); 
        }
      }
      if (IsValidDynamicArea(SuiteRoom[suiteid][suiteRoomArea])) {
        Streamer_SetFloatData(STREAMER_TYPE_AREA, SuiteRoom[suiteid][suiteRoomArea], E_STREAMER_MIN_X, areaMinX);
        Streamer_SetFloatData(STREAMER_TYPE_AREA, SuiteRoom[suiteid][suiteRoomArea], E_STREAMER_MIN_Y, areaMinY);
        Streamer_SetFloatData(STREAMER_TYPE_AREA, SuiteRoom[suiteid][suiteRoomArea], E_STREAMER_MAX_X, areaMaxX);
        Streamer_SetFloatData(STREAMER_TYPE_AREA, SuiteRoom[suiteid][suiteRoomArea], E_STREAMER_MAX_Y, areaMaxY);

        Streamer_SetFloatData(STREAMER_TYPE_AREA, SuiteRoom[suiteid][suiteRoomArea], E_STREAMER_MIN_Z, areaZ - 1.2);
        Streamer_SetFloatData(STREAMER_TYPE_AREA, SuiteRoom[suiteid][suiteRoomArea], E_STREAMER_MAX_Z, areaZ + 4.0);
        Streamer_SetIntData(STREAMER_TYPE_AREA, SuiteRoom[suiteid][suiteRoomArea], E_STREAMER_WORLD_ID, World);
        Streamer_SetIntData(STREAMER_TYPE_AREA, SuiteRoom[suiteid][suiteRoomArea], E_STREAMER_INTERIOR_ID, Interior);

        new info[2];
        info[0] = SUITE_AREA_INDEX;
        info[1] = suiteid;
        Streamer_SetArrayData(STREAMER_TYPE_AREA, SuiteRoom[suiteid][suiteRoomArea], E_STREAMER_EXTRA_ID, info);
      } else {
        SuiteRoom[suiteid][suiteRoomArea] = CreateDynamicCuboid(areaMinX, areaMinY, areaZ-1.5, areaMaxX, areaMaxY, areaZ+4, World, Interior);
        new info[2];
        info[0] = SUITE_AREA_INDEX;
        info[1] = suiteid;
        Streamer_SetArrayData(STREAMER_TYPE_AREA, SuiteRoom[suiteid][suiteRoomArea], E_STREAMER_EXTRA_ID, info);
      }
    }
    return 1;
}

SuiteRoom_Save(id)
{
	new dquery[2048];
	mysql_format(g_SQL, dquery, sizeof(dquery), "UPDATE suiteroom SET `owner` = '%s', `price` = '%d', `lock` = '%d', `word` = '%d', `interior` = '%d'",
	SuiteRoom[id][suiteRoomOwner],
	SuiteRoom[id][suiteRoomPrice],
	SuiteRoom[id][suiteRoomLocked],
  SuiteRoom[id][suiteRoomWorld],
	SuiteRoom[id][suiteRoomInterior]);

	mysql_format(g_SQL, dquery, sizeof(dquery), "%s, `doorpos` = '%.2f|%.2f|%.2f|%.2f|%.2f|%.2f', `buttonpos` = '%.2f|%.2f|%.2f|%.2f|%.2f|%.2f', `areapos` = '%.2f|%.2f|%.2f|%.2f|%.2f' WHERE ID='%d'", 
	dquery,
	SuiteRoom[id][suiteRoomDoors][0],
	SuiteRoom[id][suiteRoomDoors][1],
	SuiteRoom[id][suiteRoomDoors][2],
	SuiteRoom[id][suiteRoomDoors][3],
	SuiteRoom[id][suiteRoomDoors][4],
	SuiteRoom[id][suiteRoomDoors][5],
	SuiteRoom[id][suiteRoomButtons][0],
	SuiteRoom[id][suiteRoomButtons][1],
	SuiteRoom[id][suiteRoomButtons][2],
	SuiteRoom[id][suiteRoomButtons][3],
	SuiteRoom[id][suiteRoomButtons][4],
	SuiteRoom[id][suiteRoomButtons][5],
	SuiteRoom[id][suiteRoomAreaPos][0],
	SuiteRoom[id][suiteRoomAreaPos][1],
	SuiteRoom[id][suiteRoomAreaPos][2],
	SuiteRoom[id][suiteRoomAreaPos][3],
	SuiteRoom[id][suiteRoomAreaPos][4],
  id);
	return mysql_tquery(g_SQL, dquery);
}

function SuiteRoom_Loaded() {
    new rows = cache_num_rows();
    if(rows) {
        new suiteid, string[521];
        for(new i; i < rows; i++) {
            cache_get_value_name_int(i, "ID", suiteid);
            cache_get_value_name(i, "owner", SuiteRoom[suiteid][suiteRoomOwner], MAX_PLAYER_NAME);
            cache_get_value_name_int(i, "price", SuiteRoom[suiteid][suiteRoomPrice]);
            cache_get_value_name_int(i, "lock", SuiteRoom[suiteid][suiteRoomLocked]);
            cache_get_value_name_int(i, "word", SuiteRoom[suiteid][suiteRoomWorld]);
            cache_get_value_name_int(i, "interior", SuiteRoom[suiteid][suiteRoomInterior]);
            cache_get_value(i, "doorpos", string);
            sscanf(string, "p<|>ffffff", SuiteRoom[suiteid][suiteRoomDoors][0], SuiteRoom[suiteid][suiteRoomDoors][1], SuiteRoom[suiteid][suiteRoomDoors][2], SuiteRoom[suiteid][suiteRoomDoors][3], SuiteRoom[suiteid][suiteRoomDoors][4], SuiteRoom[suiteid][suiteRoomDoors][5]);
            cache_get_value(i, "buttonpos", string);
            sscanf(string, "p<|>ffffff", SuiteRoom[suiteid][suiteRoomButtons][0], SuiteRoom[suiteid][suiteRoomButtons][1], SuiteRoom[suiteid][suiteRoomButtons][2], SuiteRoom[suiteid][suiteRoomButtons][3], SuiteRoom[suiteid][suiteRoomButtons][4], SuiteRoom[suiteid][suiteRoomButtons][5]);
            cache_get_value(i, "areapos", string);
            sscanf(string, "p<|>fffff", SuiteRoom[suiteid][suiteRoomAreaPos][0], SuiteRoom[suiteid][suiteRoomAreaPos][1], SuiteRoom[suiteid][suiteRoomAreaPos][2], SuiteRoom[suiteid][suiteRoomAreaPos][3], SuiteRoom[suiteid][suiteRoomAreaPos][4]);
                
            SuiteRoom[suiteid][suiteRoomID] = suiteid;
            Iter_Add(SuiteRooms, suiteid);
            SuiteRoom_Refresh(suiteid);
            mysql_tquery(g_SQL, sprintf("SELECT * FROM `suite_furniture` WHERE `suiteid` = '%d';", SuiteRoom[suiteid][suiteRoomID]), "OnLoadSuiteFurn", "d", suiteid);
            mysql_tquery(g_SQL, sprintf("SELECT * FROM `suite_structure` WHERE `suiteid` = '%d' AND `Static`='0';", SuiteRoom[suiteid][suiteRoomID]), "OnLoadSuiteStructure", "d", suiteid);
        }
        printf("*** [Database: Loaded] suite room data (%d count).", rows);
    }
    return 1;
}

// Admin Commands
GetFreeSuiteZone() {
  for (new i = 0; i < MAX_SUITE_ROOM; i++) {
    if (testsuiteZone[i] == -1) {
      return i;
    }
  }
  return -1;
}
