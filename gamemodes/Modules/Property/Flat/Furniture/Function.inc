function OnLoadFlatFurniture(flatid) {
  new rows = cache_num_rows(),
    str[128],
    slot = cellmin;
  
  Iter_Init(FlatFurnitures);
  for (new i = 0; i < rows; i ++) if ((slot = Iter_Free(FlatFurnitures[flatid])) != cellmin) {
    Iter_Add(FlatFurnitures[flatid], slot);

    cache_get_value_int(i, "ID", FlatFurniture[flatid][slot][furnID]);
    cache_get_value_int(i, "Model", FlatFurniture[flatid][slot][furnModel]);
    cache_get_value_int(i, "Unused", FlatFurniture[flatid][slot][furnUnused]);
    cache_get_value(i, "Name", str, 32);
    format(FlatFurniture[flatid][slot][furnName], 32, "%s", str);

    cache_get_value(i, "Position", str, 64);
    sscanf(str, "p<|>fff", FlatFurniture[flatid][slot][furnPos][0], FlatFurniture[flatid][slot][furnPos][1], FlatFurniture[flatid][slot][furnPos][2]);

    cache_get_value(i, "Rotation", str, 64);
    sscanf(str, "p<|>fff", FlatFurniture[flatid][slot][furnRot][0], FlatFurniture[flatid][slot][furnRot][1], FlatFurniture[flatid][slot][furnRot][2]);

    cache_get_value(i, "Materials", str, 128);
    sscanf(str, "p<|>dddddddddddddddd",
      FlatFurniture[flatid][slot][furnMaterials][0],
      FlatFurniture[flatid][slot][furnMaterials][1],
      FlatFurniture[flatid][slot][furnMaterials][2],
      FlatFurniture[flatid][slot][furnMaterials][3],
      FlatFurniture[flatid][slot][furnMaterials][4],
      FlatFurniture[flatid][slot][furnMaterials][5],
      FlatFurniture[flatid][slot][furnMaterials][6],
      FlatFurniture[flatid][slot][furnMaterials][7],
      FlatFurniture[flatid][slot][furnMaterials][8],
      FlatFurniture[flatid][slot][furnMaterials][9],
      FlatFurniture[flatid][slot][furnMaterials][10],
      FlatFurniture[flatid][slot][furnMaterials][11],
      FlatFurniture[flatid][slot][furnMaterials][12],
      FlatFurniture[flatid][slot][furnMaterials][13],
      FlatFurniture[flatid][slot][furnMaterials][14],
      FlatFurniture[flatid][slot][furnMaterials][15]
    );

    FlatFurniture_Refresh(slot, flatid);
  }
  return 1;
}

function OnFlatFurnitureCreated(flatid, slot) {
  if (!Iter_Contains(FlatFurnitures[flatid], slot))
    return 0;

  FlatFurniture[flatid][slot][furnID] = cache_insert_id();
  FlatFurniture_Save(slot, flatid);
  return 1;
}

FlatFurniture_Refresh(slot, flatid) {
  if (Iter_Contains(FlatFurnitures[flatid], slot)) {
    if (!IsValidDynamicObject(FlatFurniture[flatid][slot][furnObject])) {
      if (FlatFurniture[flatid][slot][furnUnused] == 0) {
        FlatFurniture[flatid][slot][furnObject] = CreateDynamicObject(FlatFurniture[flatid][slot][furnModel], FlatFurniture[flatid][slot][furnPos][0], FlatFurniture[flatid][slot][furnPos][1], FlatFurniture[flatid][slot][furnPos][2], FlatFurniture[flatid][slot][furnRot][0], FlatFurniture[flatid][slot][furnRot][1], FlatFurniture[flatid][slot][furnRot][2], FlatRoom[flatid][flatRoomWorld], FlatRoom[flatid][flatRoomInterior], -1, STREAMER_OBJECT_SD, 200.00, FlatRoom[flatid][flatRoomArea]);
      }
    }
    FlatFurniture_Update(slot, flatid);

    foreach(new i : Player) if(IsPlayerInRangeOfPoint(i, 5, FlatFurniture[flatid][slot][furnPos][0], FlatFurniture[flatid][slot][furnPos][1], FlatFurniture[flatid][slot][furnPos][2])) {
			Streamer_Update(i);
		}
  }
  return 1;
}

FlatFurniture_Update(slot, flatid) {
  if (Iter_Contains(FlatFurnitures[flatid], slot)) {
    if (!IsValidDynamicObject(FlatFurniture[flatid][slot][furnObject]))
      return 0;
    
    if (FlatFurniture[flatid][slot][furnUnused] == 1) {
      DestroyDynamicObject(FlatFurniture[flatid][slot][furnObject]);
      FlatFurniture[flatid][slot][furnObject] = INVALID_STREAMER_ID;

      return 1;
    }
    
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FlatFurniture[flatid][slot][furnObject], E_STREAMER_X, FlatFurniture[flatid][slot][furnPos][0]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FlatFurniture[flatid][slot][furnObject], E_STREAMER_Y,FlatFurniture[flatid][slot][furnPos][1]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FlatFurniture[flatid][slot][furnObject], E_STREAMER_Z, FlatFurniture[flatid][slot][furnPos][2]);

    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FlatFurniture[flatid][slot][furnObject], E_STREAMER_R_X, FlatFurniture[flatid][slot][furnRot][0]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FlatFurniture[flatid][slot][furnObject], E_STREAMER_R_Y, FlatFurniture[flatid][slot][furnRot][1]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FlatFurniture[flatid][slot][furnObject], E_STREAMER_R_Z, FlatFurniture[flatid][slot][furnRot][2]);

    Streamer_SetIntData(STREAMER_TYPE_OBJECT, FlatFurniture[flatid][slot][furnObject], E_STREAMER_WORLD_ID, FlatRoom[flatid][flatRoomWorld]);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, FlatFurniture[flatid][slot][furnObject], E_STREAMER_INTERIOR_ID, FlatRoom[flatid][flatRoomInterior]);

    Streamer_SetIntData(STREAMER_TYPE_OBJECT, FlatFurniture[flatid][slot][furnObject], E_STREAMER_AREA_ID, FlatRoom[flatid][flatRoomArea]);

    for(new i = 0; i != MAX_MATERIALS; i++) if(FlatFurniture[flatid][slot][furnMaterials][i] > 0) {
      SetDynamicObjectMaterial(FlatFurniture[flatid][slot][furnObject], i, 
        GetTModel(FlatFurniture[flatid][slot][furnMaterials][i]), 
        GetTXDName(FlatFurniture[flatid][slot][furnMaterials][i]), 
        GetTextureName(FlatFurniture[flatid][slot][furnMaterials][i]), 0
      );
    }

    return 1;
  }
  return 0;
}

FlatFurniture_Add(flatid, name[], modelid, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, unused = 1) {
  static
    slot = cellmin;
  
  if ((slot = Iter_Free(FlatFurnitures[flatid])) != cellmin) {
    Iter_Add(FlatFurnitures[flatid], slot);

    FlatFurniture[flatid][slot][furnModel] = modelid;
    FlatFurniture[flatid][slot][furnPos][0] = x;
    FlatFurniture[flatid][slot][furnPos][1] = y;
    FlatFurniture[flatid][slot][furnPos][2] = z;
    FlatFurniture[flatid][slot][furnRot][0] = rx;
    FlatFurniture[flatid][slot][furnRot][1] = ry;
    FlatFurniture[flatid][slot][furnRot][2] = rz;
    FlatFurniture[flatid][slot][furnUnused] = unused;
    format(FlatFurniture[flatid][slot][furnName], 32, "%s", name);

    FlatFurniture_Refresh(slot, flatid);
    new string[212];
    format(string,sizeof(string),"INSERT INTO `flat_furniture` (`Flatid`) VALUES ('%d')", FlatRoom[flatid][flatRoomID]);
    mysql_tquery(g_SQL, string, "OnFlatFurnitureCreated", "dd", flatid, slot);

    return slot;
  }
  return cellmin;
}

FlatFurniture_DeleteAll(flatid) {
  foreach (new slot : FlatFurnitures[flatid]) {
    if (IsValidDynamicObject(FlatFurniture[flatid][slot][furnObject])) {
      DestroyDynamicObject(FlatFurniture[flatid][slot][furnObject]);
      FlatFurniture[flatid][slot][furnObject] = INVALID_STREAMER_ID;
    }
    
    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `flat_furniture` WHERE `ID` = '%d'", FlatFurniture[flatid][slot][furnID]);
    mysql_tquery(g_SQL, query);
    new tmp_FlatFurniture[flatFurniture];
    FlatFurniture[flatid][slot] = tmp_FlatFurniture;
  }
  
  Iter_Clear(FlatFurnitures[flatid]);
  return 1;
}

FlatFurniture_Delete(slot, flatid) {
  if (Iter_Contains(FlatFurnitures[flatid], slot)) {
    if (IsValidDynamicObject(FlatFurniture[flatid][slot][furnObject])) {
      DestroyDynamicObject(FlatFurniture[flatid][slot][furnObject]);
      FlatFurniture[flatid][slot][furnObject] = INVALID_STREAMER_ID;
    }
    
    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `flat_furniture` WHERE `ID` = '%d'", FlatFurniture[flatid][slot][furnID]);
    mysql_tquery(g_SQL, query);
    new tmp_FlatFurniture[flatFurniture];
    FlatFurniture[flatid][slot] = tmp_FlatFurniture;

    Iter_Remove(FlatFurnitures[flatid], slot);
    return 1;
  }
  return 0;
}

FlatFurniture_Save(slot, flatid) {
  if (!Iter_Contains(FlatFurnitures[flatid], slot))
    return 0;
  
  new query[1024];
  format(query,sizeof(query),"UPDATE `flat_furniture` SET `Flatid`='%d', `Model`='%d', `Name`='%s', `Unused`='%d', `Position`='%.2f|%.2f|%.2f', `Rotation`='%.2f|%.2f|%.2f', `Materials`='%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d' WHERE `ID`='%d';",
    FlatRoom[flatid][flatRoomID],
    FlatFurniture[flatid][slot][furnModel],
    FlatFurniture[flatid][slot][furnName],
    FlatFurniture[flatid][slot][furnUnused],
    FlatFurniture[flatid][slot][furnPos][0],
    FlatFurniture[flatid][slot][furnPos][1],
    FlatFurniture[flatid][slot][furnPos][2],
    FlatFurniture[flatid][slot][furnRot][0],
    FlatFurniture[flatid][slot][furnRot][1],
    FlatFurniture[flatid][slot][furnRot][2],
    FlatFurniture[flatid][slot][furnMaterials][0],
    FlatFurniture[flatid][slot][furnMaterials][1],
    FlatFurniture[flatid][slot][furnMaterials][2],
    FlatFurniture[flatid][slot][furnMaterials][3],
    FlatFurniture[flatid][slot][furnMaterials][4],
    FlatFurniture[flatid][slot][furnMaterials][5],
    FlatFurniture[flatid][slot][furnMaterials][6],
    FlatFurniture[flatid][slot][furnMaterials][7],
    FlatFurniture[flatid][slot][furnMaterials][8],
    FlatFurniture[flatid][slot][furnMaterials][9],
    FlatFurniture[flatid][slot][furnMaterials][10],
    FlatFurniture[flatid][slot][furnMaterials][11],
    FlatFurniture[flatid][slot][furnMaterials][12],
    FlatFurniture[flatid][slot][furnMaterials][13],
    FlatFurniture[flatid][slot][furnMaterials][14],
    FlatFurniture[flatid][slot][furnMaterials][15],
    FlatFurniture[flatid][slot][furnID]
  );

  return mysql_tquery(g_SQL, query);
}

FlatFurniture_GetCount(flatid) {
  return Iter_Count(FlatFurnitures[flatid]);
}

FlatFurniture_Show(playerid, flatid) {
  new
    count = 0,
    string[MAX_FLAT_FURNITURE * 64];

  if(!FlatFurniture_GetCount(flatid))
    return Error(playerid, "This flat doesn't have any furniture spawned.");

  strcat(string, "Model\tDistance\n");
  foreach (new i : FlatFurnitures[flatid])
  {
    if(FlatFurniture[flatid][i][furnUnused]) 
      format(string, sizeof(string), "%s%s\t(Not placed)\n", string, FlatFurniture[flatid][i][furnName]);
    else 
      format(string, sizeof(string), "%s%s\t%.2f\n", string, FlatFurniture[flatid][i][furnName], GetPlayerDistanceFromPoint(playerid, FlatFurniture[flatid][i][furnPos][0], FlatFurniture[flatid][i][furnPos][1], FlatFurniture[flatid][i][furnPos][2]));

    ListedFlatFurnitures[playerid][count++] = i;
  }
  Dialog_Show(playerid, ListedFlatFurniture, DIALOG_STYLE_TABLIST_HEADERS, "Flat Furniture", string, "Select", "Cancel");
  return 1;
}
