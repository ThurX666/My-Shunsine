function OnLoadSuiteFurn(suiteid) {
  new rows = cache_num_rows(),
    str[128],
    slot = cellmin;
  
  Iter_Init(SuiteFurnitures);
  for (new i = 0; i < rows; i ++) if ((slot = Iter_Free(SuiteFurnitures[suiteid])) != cellmin) {
    Iter_Add(SuiteFurnitures[suiteid], slot);

    cache_get_value_int(i, "ID", SuiteFurniture[suiteid][slot][suitefurnID]);
    cache_get_value_int(i, "Model", SuiteFurniture[suiteid][slot][suitefurnModel]);
    cache_get_value_int(i, "Unused", SuiteFurniture[suiteid][slot][suitefurnUnused]);
    cache_get_value(i, "Name", SuiteFurniture[suiteid][slot][suitefurnName], 128);

    cache_get_value(i, "Position", str, 64);
    sscanf(str, "p<|>fff", SuiteFurniture[suiteid][slot][suitefurnPos][0], SuiteFurniture[suiteid][slot][suitefurnPos][1], SuiteFurniture[suiteid][slot][suitefurnPos][2]);

    cache_get_value(i, "Rotation", str, 64);
    sscanf(str, "p<|>fff", SuiteFurniture[suiteid][slot][suitefurnRot][0], SuiteFurniture[suiteid][slot][suitefurnRot][1], SuiteFurniture[suiteid][slot][suitefurnRot][2]);

    cache_get_value(i, "Materials", str, 128);
    sscanf(str, "p<|>dddddddddddddddd",
      SuiteFurniture[suiteid][slot][suitefurnMaterials][0],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][1],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][2],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][3],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][4],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][5],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][6],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][7],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][8],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][9],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][10],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][11],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][12],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][13],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][14],
      SuiteFurniture[suiteid][slot][suitefurnMaterials][15]
    );
    SuiteFurniture_Refresh(slot, suiteid);
  }
  return 1;
}

function OnSuiteFurnitureCreated(suiteid, slot) {
  if (!Iter_Contains(SuiteFurnitures[suiteid], slot))
    return 0;

  SuiteFurniture[suiteid][slot][suitefurnID] = cache_insert_id();
  SuiteFurniture_Save(slot, suiteid);
  return 1;
}

SuiteFurniture_Refresh(slot, suiteid) {
  if (Iter_Contains(SuiteFurnitures[suiteid], slot)) {
    if (!IsValidDynamicObject(SuiteFurniture[suiteid][slot][suitefurnObject])) {
      if (SuiteFurniture[suiteid][slot][suitefurnUnused] == 0) {
        SuiteFurniture[suiteid][slot][suitefurnObject] = CreateDynamicObject(SuiteFurniture[suiteid][slot][suitefurnModel], SuiteFurniture[suiteid][slot][suitefurnPos][0], SuiteFurniture[suiteid][slot][suitefurnPos][1], SuiteFurniture[suiteid][slot][suitefurnPos][2], SuiteFurniture[suiteid][slot][suitefurnRot][0], SuiteFurniture[suiteid][slot][suitefurnRot][1], SuiteFurniture[suiteid][slot][suitefurnRot][2], SuiteRoom[suiteid][suiteRoomWorld], SuiteRoom[suiteid][suiteRoomInterior], -1, STREAMER_OBJECT_SD, 200.00,SuiteRoom[suiteid][suiteRoomArea]);
      }
    }
    SuiteFurniture_Update(slot, suiteid);

    foreach(new i : Player) if(IsPlayerInRangeOfPoint(i, 5, SuiteFurniture[suiteid][slot][suitefurnPos][0], SuiteFurniture[suiteid][slot][suitefurnPos][1], SuiteFurniture[suiteid][slot][suitefurnPos][2])) {
			Streamer_Update(i);
		}
  }
  return 1;
}

SuiteFurniture_Update(slot, suiteid) {
  if (Iter_Contains(SuiteFurnitures[suiteid], slot)) {
    if (!IsValidDynamicObject(SuiteFurniture[suiteid][slot][suitefurnObject]))
      return 0; 
    if (SuiteFurniture[suiteid][slot][suitefurnUnused] == 1) {
      DestroyDynamicObject(SuiteFurniture[suiteid][slot][suitefurnObject]);
      SuiteFurniture[suiteid][slot][suitefurnObject] = INVALID_STREAMER_ID;
      return 1;
    }
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, SuiteFurniture[suiteid][slot][suitefurnObject], E_STREAMER_X, SuiteFurniture[suiteid][slot][suitefurnPos][0]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, SuiteFurniture[suiteid][slot][suitefurnObject], E_STREAMER_Y,SuiteFurniture[suiteid][slot][suitefurnPos][1]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, SuiteFurniture[suiteid][slot][suitefurnObject], E_STREAMER_Z, SuiteFurniture[suiteid][slot][suitefurnPos][2]);

    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, SuiteFurniture[suiteid][slot][suitefurnObject], E_STREAMER_R_X, SuiteFurniture[suiteid][slot][suitefurnRot][0]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, SuiteFurniture[suiteid][slot][suitefurnObject], E_STREAMER_R_Y, SuiteFurniture[suiteid][slot][suitefurnRot][1]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, SuiteFurniture[suiteid][slot][suitefurnObject], E_STREAMER_R_Z, SuiteFurniture[suiteid][slot][suitefurnRot][2]);

    Streamer_SetIntData(STREAMER_TYPE_OBJECT, SuiteFurniture[suiteid][slot][suitefurnObject], E_STREAMER_WORLD_ID, SuiteRoom[suiteid][suiteRoomWorld]);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, SuiteFurniture[suiteid][slot][suitefurnObject], E_STREAMER_INTERIOR_ID, SuiteRoom[suiteid][suiteRoomInterior]);

    Streamer_SetIntData(STREAMER_TYPE_OBJECT, SuiteFurniture[suiteid][slot][suitefurnObject], E_STREAMER_AREA_ID, SuiteRoom[suiteid][suiteRoomArea]);

    for(new i = 0; i != MAX_MATERIALS; i++) if(SuiteFurniture[suiteid][slot][suitefurnMaterials][i] > 0) {
      SetDynamicObjectMaterial(SuiteFurniture[suiteid][slot][suitefurnObject], i, 
        GetTModel(SuiteFurniture[suiteid][slot][suitefurnMaterials][i]), 
        GetTXDName(SuiteFurniture[suiteid][slot][suitefurnMaterials][i]), 
        GetTextureName(SuiteFurniture[suiteid][slot][suitefurnMaterials][i]), 0
      );
    }
    return 1;
  }
  return 0;
}

SuiteFurniture_Add(suiteid, name[], modelid, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, unused = 1) {
  static
    slot = cellmin;
  
  if ((slot = Iter_Free(SuiteFurnitures[suiteid])) != cellmin) {
    Iter_Add(SuiteFurnitures[suiteid], slot);

    SuiteFurniture[suiteid][slot][suitefurnModel] = modelid;
    SuiteFurniture[suiteid][slot][suitefurnPos][0] = x;
    SuiteFurniture[suiteid][slot][suitefurnPos][1] = y;
    SuiteFurniture[suiteid][slot][suitefurnPos][2] = z;
    SuiteFurniture[suiteid][slot][suitefurnRot][0] = rx;
    SuiteFurniture[suiteid][slot][suitefurnRot][1] = ry;
    SuiteFurniture[suiteid][slot][suitefurnRot][2] = rz;
    SuiteFurniture[suiteid][slot][suitefurnUnused] = unused;
    format(SuiteFurniture[suiteid][slot][suitefurnName], 128, name);

    SuiteFurniture_Refresh(slot, suiteid);
    new string[212];
    format(string,sizeof(string),"INSERT INTO `suite_furniture` (`suiteid`) VALUES ('%d')", SuiteRoom[suiteid][suiteRoomID]);
    mysql_tquery(g_SQL, string, "OnSuiteFurnitureCreated", "dd", suiteid, slot);
    return slot;
  }
  return cellmin;
}

SuiteFurniture_DeleteAll(suiteid) {
  foreach (new slot : SuiteFurnitures[suiteid]) {
    if (IsValidDynamicObject(SuiteFurniture[suiteid][slot][suitefurnObject])) {
      DestroyDynamicObject(SuiteFurniture[suiteid][slot][suitefurnObject]);
      SuiteFurniture[suiteid][slot][suitefurnObject] = INVALID_STREAMER_ID;
    }
    
    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `suite_furniture` WHERE `ID` = '%d'", SuiteFurniture[suiteid][slot][suitefurnID]);
    mysql_tquery(g_SQL, query);
    new tmp_SuiteFurniture[suiteFurniture];
    SuiteFurniture[suiteid][slot] = tmp_SuiteFurniture;
  }
  
  Iter_Clear(SuiteFurnitures[suiteid]);
  return 1;
}

SuiteFurniture_Delete(slot, suiteid) {
  if (Iter_Contains(SuiteFurnitures[suiteid], slot)) {
    if (IsValidDynamicObject(SuiteFurniture[suiteid][slot][suitefurnObject])) {
      DestroyDynamicObject(SuiteFurniture[suiteid][slot][suitefurnObject]);
      SuiteFurniture[suiteid][slot][suitefurnObject] = INVALID_STREAMER_ID;
    }
    
    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `suite_furniture` WHERE `ID` = '%d'", SuiteFurniture[suiteid][slot][suitefurnID]);
    mysql_tquery(g_SQL, query);
    new tmp_SuiteFurniture[suiteFurniture];
    SuiteFurniture[suiteid][slot] = tmp_SuiteFurniture;

    Iter_Remove(SuiteFurnitures[suiteid], slot);
    return 1;
  }
  return 0;
}

SuiteFurniture_Save(slot, suiteid) {
  if (!Iter_Contains(SuiteFurnitures[suiteid], slot))
    return 0;
  
  new query[1024];
  format(query,sizeof(query),"UPDATE `suite_furniture` SET `suiteid`='%d', `Model`='%d', `Name`='%s', `Unused`='%d', `Position`='%.2f|%.2f|%.2f', `Rotation`='%.2f|%.2f|%.2f', `Materials`='%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d' WHERE `ID`='%d';",
    SuiteRoom[suiteid][suiteRoomID],
    SuiteFurniture[suiteid][slot][suitefurnModel],
    SuiteFurniture[suiteid][slot][suitefurnName],
    SuiteFurniture[suiteid][slot][suitefurnUnused],
    SuiteFurniture[suiteid][slot][suitefurnPos][0],
    SuiteFurniture[suiteid][slot][suitefurnPos][1],
    SuiteFurniture[suiteid][slot][suitefurnPos][2],
    SuiteFurniture[suiteid][slot][suitefurnRot][0],
    SuiteFurniture[suiteid][slot][suitefurnRot][1],
    SuiteFurniture[suiteid][slot][suitefurnRot][2],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][0],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][1],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][2],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][3],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][4],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][5],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][6],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][7],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][8],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][9],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][10],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][11],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][12],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][13],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][14],
    SuiteFurniture[suiteid][slot][suitefurnMaterials][15],
    SuiteFurniture[suiteid][slot][suitefurnID]
  );

  return mysql_tquery(g_SQL, query);
}

SuiteFurniture_GetCount(suiteid) {
  return Iter_Count(SuiteFurnitures[suiteid]);
}

SuiteFurniture_Show(playerid, suiteid) {
  new
    count = 0,
    string[MAX_SUITE_FURNITURE * 64];

  if(!SuiteFurniture_GetCount(suiteid))
    return Error(playerid, "This suite room doesn't have any furniture spawned.");

  strcat(string, "Model\tDistance\n");
  foreach (new i : SuiteFurnitures[suiteid])
  {
    if(SuiteFurniture[suiteid][i][suitefurnUnused]) 
      format(string, sizeof(string), "%s%s\t(Not placed)\n", string, SuiteFurniture[suiteid][i][suitefurnName]);
    else 
      format(string, sizeof(string), "%s%s\t%.2f\n", string, SuiteFurniture[suiteid][i][suitefurnName], GetPlayerDistanceFromPoint(playerid, SuiteFurniture[suiteid][i][suitefurnPos][0], SuiteFurniture[suiteid][i][suitefurnPos][1], SuiteFurniture[suiteid][i][suitefurnPos][2]));

    ListedSuiteFurnitures[playerid][count++] = i;
  }
  Dialog_Show(playerid, ListedSuiteFurniture, DIALOG_STYLE_TABLIST_HEADERS, "SuiteRoom Furniture", string, "Select", "Cancel");
  return 1;
}
