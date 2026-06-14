
function OnLoadFlatStructure(flatid) {
  new rows = cache_num_rows(),
    str[128],
    slot = cellmin;

  Iter_Init(FlatStructures);
  for (new i = 0; i < rows; i ++) if ((slot = Iter_Free(FlatStructures[flatid])) != cellmin) {
    Iter_Add(FlatStructures[flatid], slot);

    cache_get_value_int(i, "ID", FlatStructure[flatid][slot][structID]);
    cache_get_value_int(i, "Model", FlatStructure[flatid][slot][structModel]);
    
    cache_get_value(i, "Position", str);
    sscanf(str, "p<|>fff", FlatStructure[flatid][slot][structPos][0], FlatStructure[flatid][slot][structPos][1], FlatStructure[flatid][slot][structPos][2]);

    cache_get_value(i, "Rotation", str);
    sscanf(str, "p<|>fff", FlatStructure[flatid][slot][structRot][0], FlatStructure[flatid][slot][structRot][1], FlatStructure[flatid][slot][structRot][2]);

    cache_get_value(i, "Material", str);
    sscanf(str, "p<|>dd", FlatStructure[flatid][slot][structMaterial], FlatStructure[flatid][slot][structColor]);

    FlatStructure_Refresh(flatid, slot);
  }
  return 1;
}

function OnLoadStaticStructure(flatid) {
  new rows = cache_num_rows(),
    str[128],
    slot = cellmin;
  
  Iter_Init(FlatStaticStructs);
  for (new i = 0; i < rows; i ++) if ((slot = Iter_Free(FlatStaticStructs[flatid])) != cellmin) {
    Iter_Add(FlatStaticStructs[flatid], slot);

    cache_get_value_int(i, "ID", FlatStaticStruct[flatid][slot][structID]);
    cache_get_value_int(i, "Model", FlatStaticStruct[flatid][slot][structModel]);
    
    cache_get_value(i, "Position", str);
    sscanf(str, "p<|>fff", FlatStaticStruct[flatid][slot][structPos][0], FlatStaticStruct[flatid][slot][structPos][1], FlatStaticStruct[flatid][slot][structPos][2]);

    cache_get_value(i, "Rotation", str);
    sscanf(str, "p<|>fff", FlatStaticStruct[flatid][slot][structRot][0], FlatStaticStruct[flatid][slot][structRot][1], FlatStaticStruct[flatid][slot][structRot][2]);

    cache_get_value(i, "Material", str);
    sscanf(str, "p<|>dd", FlatStaticStruct[flatid][slot][structMaterial], FlatStaticStruct[flatid][slot][structColor]);

    FlatStructure_Refresh(flatid, slot, false);
  }
  return 1;
}

function OnFlatStructureCreated(flatid, slot, isCustom) {
  if (!Iter_Contains(FlatStructures[flatid], slot) && !Iter_Contains(FlatStaticStructs[flatid], slot))
    return 0;
  
  if (isCustom) FlatStructure[flatid][slot][structID] = cache_insert_id(), FlatStructure_Save(flatid, slot);
  else FlatStaticStruct[flatid][slot][structID] = cache_insert_id(), FlatStructure_Save(flatid, slot, false);
  return 1;
}

FlatStructure_Create(flatid, modelid, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, bool:isCustom = true) {
  if (isCustom) {
    new slot;
    
    if (!Iter_Contains(FlatRooms, flatid))
      return 0;
    
    if ((slot = Iter_Free(FlatStructures[flatid])) != cellmin) {
      Iter_Add(FlatStructures[flatid], slot);
      
      FlatStructure[flatid][slot][structModel] = modelid;
      FlatStructure[flatid][slot][structPos][0] = x;
      FlatStructure[flatid][slot][structPos][1] = y;
      FlatStructure[flatid][slot][structPos][2] = z;
      FlatStructure[flatid][slot][structRot][0] = rx;
      FlatStructure[flatid][slot][structRot][1] = ry;
      FlatStructure[flatid][slot][structRot][2] = rz;
      FlatStructure[flatid][slot][structMaterial] = 0;
      FlatStructure[flatid][slot][structColor] = 0;
      
      FlatStructure_Refresh(flatid, slot);

      mysql_tquery(g_SQL, "INSERT INTO `flat_structure` (`Static`) VALUES ('0')", "OnFlatStructureCreated", "ddd", flatid, slot, 1);
      return slot;
    }

    return cellmin;
  } else {
    new slot;
    
    if (!Iter_Contains(FlatRooms, flatid))
      return 0;
    
    if ((slot = Iter_Free(FlatStaticStructs[flatid])) != cellmin) {
      Iter_Add(FlatStaticStructs[flatid], slot);
      
      FlatStaticStruct[flatid][slot][structModel] = modelid;
      FlatStaticStruct[flatid][slot][structPos][0] = x;
      FlatStaticStruct[flatid][slot][structPos][1] = y;
      FlatStaticStruct[flatid][slot][structPos][2] = z;
      FlatStaticStruct[flatid][slot][structRot][0] = rx;
      FlatStaticStruct[flatid][slot][structRot][1] = ry;
      FlatStaticStruct[flatid][slot][structRot][2] = rz;
      FlatStaticStruct[flatid][slot][structMaterial] = 0;
      FlatStaticStruct[flatid][slot][structColor] = 0;
      
      FlatStructure_Refresh(flatid, slot, false);

      mysql_tquery(g_SQL, "INSERT INTO `flat_structure` (`Static`) VALUES ('1')", "OnFlatStructureCreated", "ddd", flatid, slot, 0);
      return slot;
    }

    return cellmin;
  }
}

CreateFlatInterior(flatid, roomid) {
  new flatBase = Flat_ReturnID(flatid), id = cellmin;

  if (flatBase != -1) {
    switch (FlatData[flatBase][flatType]) {
      case FLAT_TYPE_HIGH: {
        for (new i = 0; i < sizeof(FlatHighInterior); i ++) if (FlatHighInterior[i][objRoomID] == roomid) {
          id = FlatStructure_Create(flatid, FlatHighInterior[i][objModel], FlatHighInterior[i][objPosX], FlatHighInterior[i][objPosY], FlatHighInterior[i][objPosZ], FlatHighInterior[i][objRotX], FlatHighInterior[i][objRotY], FlatHighInterior[i][objRotZ], false);
          
          if (id == cellmin) break;
        }

        FlatRoom[flatid][flatRoomAreaPos][0] = FlatHighAreaPos[roomid-1][minX];
        FlatRoom[flatid][flatRoomAreaPos][1] = FlatHighAreaPos[roomid-1][minY];
        FlatRoom[flatid][flatRoomAreaPos][2] = FlatHighAreaPos[roomid-1][maxX];
        FlatRoom[flatid][flatRoomAreaPos][3] = FlatHighAreaPos[roomid-1][maxY];
        FlatRoom[flatid][flatRoomAreaPos][4] = FlatHighAreaPos[roomid-1][zPos];

        #if defined DEBUG_MODE
          printf("[function  CreateFlatInterior]: AreaPos Room ID %d: %f, %f, %f, %f, %f", roomid, FlatHighAreaPos[roomid-1][minX], FlatHighAreaPos[roomid-1][minY], FlatHighAreaPos[roomid-1][maxX], FlatHighAreaPos[roomid-1][maxY], FlatHighAreaPos[roomid-1][zPos]);
        #endif

        FlatRoom_Refresh(flatid);
        FlatRoom_Save(flatid);
      }
      case FLAT_TYPE_MEDIUM: {
        for (new i = 0; i < sizeof(FlatMediumInterior); i ++) if (FlatMediumInterior[i][objRoomID] == roomid) {
          id = FlatStructure_Create(flatid, FlatMediumInterior[i][objModel], FlatMediumInterior[i][objPosX], FlatMediumInterior[i][objPosY], FlatMediumInterior[i][objPosZ], FlatMediumInterior[i][objRotX], FlatMediumInterior[i][objRotY], FlatMediumInterior[i][objRotZ], false);

          if (id == cellmin) break;
        }

        FlatRoom[flatid][flatRoomAreaPos][0] = FlatMediumAreaPos[roomid-1][minX];
        FlatRoom[flatid][flatRoomAreaPos][1] = FlatMediumAreaPos[roomid-1][minY];
        FlatRoom[flatid][flatRoomAreaPos][2] = FlatMediumAreaPos[roomid-1][maxX];
        FlatRoom[flatid][flatRoomAreaPos][3] = FlatMediumAreaPos[roomid-1][maxY];
        FlatRoom[flatid][flatRoomAreaPos][4] = FlatMediumAreaPos[roomid-1][zPos];

        #if defined DEBUG_MODE
          printf("[function  CreateFlatInterior]: AreaPos Room ID %d: %f, %f, %f, %f, %f", roomid, FlatMediumAreaPos[roomid-1][minX], FlatMediumAreaPos[roomid-1][minY], FlatMediumAreaPos[roomid-1][maxX], FlatMediumAreaPos[roomid-1][maxY], FlatMediumAreaPos[roomid-1][zPos]);
        #endif

        FlatRoom_Refresh(flatid);
        FlatRoom_Save(flatid);
      }
      case FLAT_TYPE_LOW: {
        for (new i = 0; i < sizeof(FlatLowInterior); i ++) if (FlatLowInterior[i][objRoomID] == roomid) {
          id = FlatStructure_Create(flatid, FlatLowInterior[i][objModel], FlatLowInterior[i][objPosX], FlatLowInterior[i][objPosY], FlatLowInterior[i][objPosZ], FlatLowInterior[i][objRotX], FlatLowInterior[i][objRotY], FlatLowInterior[i][objRotZ], false);

          if (id == cellmin) break;
        }

        FlatRoom[flatid][flatRoomAreaPos][0] = FlatLowAreaPos[roomid-1][minX];
        FlatRoom[flatid][flatRoomAreaPos][1] = FlatLowAreaPos[roomid-1][minY];
        FlatRoom[flatid][flatRoomAreaPos][2] = FlatLowAreaPos[roomid-1][maxX];
        FlatRoom[flatid][flatRoomAreaPos][3] = FlatLowAreaPos[roomid-1][maxY];
        FlatRoom[flatid][flatRoomAreaPos][4] = FlatLowAreaPos[roomid-1][zPos];

        #if defined DEBUG_MODE
          printf("[function  CreateFlatInterior]: AreaPos Room ID %d: %f, %f, %f, %f, %f", roomid, FlatLowAreaPos[roomid-1][minX], FlatLowAreaPos[roomid-1][minY], FlatLowAreaPos[roomid-1][maxX], FlatLowAreaPos[roomid-1][maxY], FlatLowAreaPos[roomid-1][zPos]);
        #endif

        FlatRoom_Refresh(flatid);
        FlatRoom_Save(flatid);
      }
    }
  }

  return 1;
}

FlatStructure_Refresh(flatid, slot, bool:isCustom = true) {
  if (!Iter_Contains(FlatRooms, flatid))
    return 0;

  if (!Iter_Contains(FlatStructures[flatid], slot) && !Iter_Contains(FlatStaticStructs[flatid], slot))
    return 0;
  
  if (isCustom) {
    if (!IsValidDynamicObject(FlatStructure[flatid][slot][structObject])) {
      FlatStructure[flatid][slot][structObject] = CreateDynamicObject(FlatStructure[flatid][slot][structModel], FlatStructure[flatid][slot][structPos][0], FlatStructure[flatid][slot][structPos][1], FlatStructure[flatid][slot][structPos][2], FlatStructure[flatid][slot][structRot][0], FlatStructure[flatid][slot][structRot][1], FlatStructure[flatid][slot][structRot][2], FlatRoom[flatid][flatRoomWorld], FlatRoom[flatid][flatRoomInterior], -1, STREAMER_OBJECT_SD, 200.00, FlatRoom[flatid][flatRoomArea]);
    }

    FlatStructure_Update(flatid, slot);
    foreach (new i : Player) if (IsPlayerInRangeOfPoint(i, 5.0, FlatStructure[flatid][slot][structPos][0], FlatStructure[flatid][slot][structPos][1], FlatStructure[flatid][slot][structPos][2])) {
      Streamer_Update(i);
    }
  } else {
    if (!IsValidDynamicObject(FlatStaticStruct[flatid][slot][structObject])) {
      FlatStaticStruct[flatid][slot][structObject] = CreateDynamicObject(FlatStaticStruct[flatid][slot][structModel], FlatStaticStruct[flatid][slot][structPos][0], FlatStaticStruct[flatid][slot][structPos][1], FlatStaticStruct[flatid][slot][structPos][2], FlatStaticStruct[flatid][slot][structRot][0], FlatStaticStruct[flatid][slot][structRot][1], FlatStaticStruct[flatid][slot][structRot][2], FlatRoom[flatid][flatRoomWorld], FlatRoom[flatid][flatRoomInterior], -1, STREAMER_OBJECT_SD, 200.00, (FlatStaticStruct[flatid][slot][structModel] == 1502 || FlatStaticStruct[flatid][slot][structModel] == 1536) ? (-1) : (FlatRoom[flatid][flatRoomArea]));
    }

    FlatStructure_Update(flatid, slot, false);
    foreach (new i : Player) if (IsPlayerInRangeOfPoint(i, 5.0, FlatStaticStruct[flatid][slot][structPos][0], FlatStaticStruct[flatid][slot][structPos][1], FlatStaticStruct[flatid][slot][structPos][2])) {
      Streamer_Update(i);
    }
  }

  return 1;
}

FlatStructure_Update(flatid, slot, bool:isCustom = true) {
  if (!Iter_Contains(FlatRooms, flatid))
    return 0;

  if (!Iter_Contains(FlatStructures[flatid], slot) && !Iter_Contains(FlatStaticStructs[flatid], slot))
    return 0;
  
  new objectid;
  if (isCustom) {
    objectid = FlatStructure[flatid][slot][structObject];
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_X, FlatStructure[flatid][slot][structPos][0]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Y, FlatStructure[flatid][slot][structPos][1]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Z, FlatStructure[flatid][slot][structPos][2]);

    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_X, FlatStructure[flatid][slot][structRot][0]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Y, FlatStructure[flatid][slot][structRot][1]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Z, FlatStructure[flatid][slot][structRot][2]);

    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_WORLD_ID, FlatRoom[flatid][flatRoomWorld]);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_INTERIOR_ID, FlatRoom[flatid][flatRoomInterior]);

    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_AREA_ID, FlatRoom[flatid][flatRoomArea]);

    if (FlatStructure[flatid][slot][structMaterial] > 0) {
      if (FlatStructure[flatid][slot][structModel] == 1502 || FlatStructure[flatid][slot][structModel] == 14414) SetDynamicObjectMaterial(FlatStructure[flatid][slot][structObject], 1, GetTModel(FlatStructure[flatid][slot][structMaterial]), GetTXDName(FlatStructure[flatid][slot][structMaterial]), GetTextureName(FlatStructure[flatid][slot][structMaterial]), FlatStructure[flatid][slot][structColor]);
      else SetDynamicObjectMaterial(objectid, 0, GetTModel(FlatStructure[flatid][slot][structMaterial]), GetTXDName(FlatStructure[flatid][slot][structMaterial]), GetTextureName(FlatStructure[flatid][slot][structMaterial]), FlatStructure[flatid][slot][structColor]);
    }
  } else {
    objectid = FlatStaticStruct[flatid][slot][structObject];
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_X, FlatStaticStruct[flatid][slot][structPos][0]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Y, FlatStaticStruct[flatid][slot][structPos][1]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Z, FlatStaticStruct[flatid][slot][structPos][2]);

    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_X, FlatStaticStruct[flatid][slot][structRot][0]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Y, FlatStaticStruct[flatid][slot][structRot][1]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Z, FlatStaticStruct[flatid][slot][structRot][2]);

    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_WORLD_ID, FlatRoom[flatid][flatRoomWorld]);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_INTERIOR_ID, FlatRoom[flatid][flatRoomInterior]);

    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_AREA_ID, (FlatStaticStruct[flatid][slot][structModel] == 1502 || FlatStaticStruct[flatid][slot][structModel] == 1536) ? (-1) : (FlatRoom[flatid][flatRoomArea]));

    if (FlatStaticStruct[flatid][slot][structMaterial] > 0) {
      SetDynamicObjectMaterial(objectid, (FlatStaticStruct[flatid][slot][structModel] == 1502) ? (1) : (0), GetTModel(FlatStaticStruct[flatid][slot][structMaterial]), GetTXDName(FlatStaticStruct[flatid][slot][structMaterial]), GetTextureName(FlatStaticStruct[flatid][slot][structMaterial]), FlatStaticStruct[flatid][slot][structColor]);
    }
  }
  return 1;
}

FlatStructure_Save(flatid, slot, bool:isCustom = true, mode = SAVE_STRUCTURE_ALL) {
  if (!Iter_Contains(FlatRooms, flatid))
    return 0;

  if (!Iter_Contains(FlatStructures[flatid], slot) && !Iter_Contains(FlatStaticStructs[flatid], slot))
    return 0;

  if (isCustom) {
    switch (mode) {
      case SAVE_STRUCTURE_ALL: {
        new query[2024];

        format(query, sizeof(query), "UPDATE `flat_structure` SET `Flatid`='%d', `Model`='%d', `Position`='%.2f|%.2f|%.2f', `Rotation`='%.2f|%.2f|%.2f', `Material`='%d|%d' WHERE `ID`='%d' AND `Static`='0'",
          FlatRoom[flatid][flatRoomID],
          FlatStructure[flatid][slot][structModel],
          FlatStructure[flatid][slot][structPos][0],
          FlatStructure[flatid][slot][structPos][1],
          FlatStructure[flatid][slot][structPos][2],
          FlatStructure[flatid][slot][structRot][0],
          FlatStructure[flatid][slot][structRot][1],
          FlatStructure[flatid][slot][structRot][2],
          FlatStructure[flatid][slot][structMaterial],
          FlatStructure[flatid][slot][structColor],
          FlatStructure[flatid][slot][structID]
        );
        mysql_tquery(g_SQL, query);
      }
      case SAVE_STRUCTURE_MATERIAL: {
        new query[2024];

        format(query, sizeof(query), "UPDATE `flat_structure` SET `Flatid`='%d', `Material`='%d|%d' WHERE `ID`='%d' AND `Static`='0'",
          FlatRoom[flatid][flatRoomID],
          FlatStructure[flatid][slot][structMaterial],
          FlatStructure[flatid][slot][structColor],
          FlatStructure[flatid][slot][structID]
        );
        mysql_tquery(g_SQL, query);
      }
      case SAVE_STRUCTURE_MODEL: {
        new query[2024];

        format(query, sizeof(query), "UPDATE `flat_structure` SET `Flatid`='%d', `Model`='%d' WHERE `ID`='%d' AND `Static`='0'",
          FlatRoom[flatid][flatRoomID],
          FlatStructure[flatid][slot][structModel],
          FlatStructure[flatid][slot][structID]
        );
        mysql_tquery(g_SQL, query);
      }
      case SAVE_STRUCTURE_POS: {
        new query[2024];

        format(query, sizeof(query), "UPDATE `flat_structure` SET `Flatid`='%d', `Position`='%.2f|%.2f|%.2f', `Rotation`='%.2f|%.2f|%.2f' WHERE `ID`='%d' AND `Static`='0'",
          FlatRoom[flatid][flatRoomID],
          FlatStructure[flatid][slot][structPos][0],
          FlatStructure[flatid][slot][structPos][1],
          FlatStructure[flatid][slot][structPos][2],
          FlatStructure[flatid][slot][structRot][0],
          FlatStructure[flatid][slot][structRot][1],
          FlatStructure[flatid][slot][structRot][2],
          FlatStructure[flatid][slot][structID]
        );
        mysql_tquery(g_SQL, query);
      }
    }
  } 
  else 
  {
    switch (mode) {
      case SAVE_STRUCTURE_ALL: {
        new query[2024];

        format(query, sizeof(query), "UPDATE `flat_structure` SET `Flatid`='%d', `Model`='%d', `Position`='%.2f|%.2f|%.2f', `Rotation`='%.2f|%.2f|%.2f', `Material`='%d|%d' WHERE `ID`='%d' AND `Static`='1'",
          FlatRoom[flatid][flatRoomID],
          FlatStaticStruct[flatid][slot][structModel],
          FlatStaticStruct[flatid][slot][structPos][0],
          FlatStaticStruct[flatid][slot][structPos][1],
          FlatStaticStruct[flatid][slot][structPos][2],
          FlatStaticStruct[flatid][slot][structRot][0],
          FlatStaticStruct[flatid][slot][structRot][1],
          FlatStaticStruct[flatid][slot][structRot][2],
          FlatStaticStruct[flatid][slot][structMaterial],
          FlatStaticStruct[flatid][slot][structColor],
          FlatStaticStruct[flatid][slot][structID]
        );
        mysql_tquery(g_SQL, query);
      }
      case SAVE_STRUCTURE_MATERIAL: {
        new query[2024];

        format(query, sizeof(query), "UPDATE `flat_structure` SET `Flatid`='%d', `Material`='%d|%d' WHERE `ID`='%d' AND `Static`='1'",
          FlatRoom[flatid][flatRoomID],
          FlatStaticStruct[flatid][slot][structMaterial],
          FlatStaticStruct[flatid][slot][structColor],
          FlatStaticStruct[flatid][slot][structID]
        );
        mysql_tquery(g_SQL, query);
      }
      case SAVE_STRUCTURE_MODEL: {
        new query[2024];

        format(query, sizeof(query), "UPDATE `flat_structure` SET `Flatid`='%d', `Model`='%d' WHERE `ID`='%d' AND `Static`='1'",
          FlatRoom[flatid][flatRoomID],
          FlatStaticStruct[flatid][slot][structModel],
          FlatStaticStruct[flatid][slot][structID]
        );
        mysql_tquery(g_SQL, query);
      }
      case SAVE_STRUCTURE_POS: {
        new query[2024];

        format(query, sizeof(query), "UPDATE `flat_structure` SET `Flatid`='%d', `Position`='%.2f|%.2f|%.2f', `Rotation`='%.2f|%.2f|%.2f' WHERE `ID`='%d' AND `Static`='1'",
          FlatRoom[flatid][flatRoomID],
          FlatStaticStruct[flatid][slot][structPos][0],
          FlatStaticStruct[flatid][slot][structPos][1],
          FlatStaticStruct[flatid][slot][structPos][2],
          FlatStaticStruct[flatid][slot][structRot][0],
          FlatStaticStruct[flatid][slot][structRot][1],
          FlatStaticStruct[flatid][slot][structRot][2],
          FlatStaticStruct[flatid][slot][structID]
        );
        mysql_tquery(g_SQL, query);
      }
    }
  }

  return 1;
}


FlatStructure_DeleteAll(flatid, bool:isCustom = true) {
  if (Iter_Contains(FlatRooms, flatid)) {
    if (isCustom) {
      foreach (new slot : FlatStructures[flatid]) {
        if (IsValidDynamicObject(FlatStructure[flatid][slot][structObject]))
        DestroyDynamicObject(FlatStructure[flatid][slot][structObject]), FlatStructure[flatid][slot][structObject] = INVALID_STREAMER_ID;
      
        new query[128];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `flat_structure` WHERE `ID`='%d' AND `Static`='0'", FlatStructure[flatid][slot][structID]);
        mysql_tquery(g_SQL, query);
        new tmp_FlatStructure[structEnum];
        FlatStructure[flatid][slot] = tmp_FlatStructure;  
      }

      Iter_Clear(FlatStructures[flatid]);
    } else {
      foreach (new slot : FlatStaticStructs[flatid]) {
        if (IsValidDynamicObject(FlatStaticStruct[flatid][slot][structObject]))
          DestroyDynamicObject(FlatStaticStruct[flatid][slot][structObject]), FlatStaticStruct[flatid][slot][structObject] = INVALID_STREAMER_ID;

        new query[128];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `flat_structure` WHERE `ID`='%d' AND `Static`='1'", FlatStaticStruct[flatid][slot][structID]);
        mysql_tquery(g_SQL, query);
        new tmp_FlatStaticStruct[structEnum];
        FlatStaticStruct[flatid][slot] = tmp_FlatStaticStruct;
      }

      Iter_Clear(FlatStaticStructs[flatid]);
    }
  }
  return 1;
}

FlatStructure_Delete(flatid, slot, bool:isCustom = true) {
  if (!Iter_Contains(FlatStructures[flatid], slot) && !Iter_Contains(FlatStaticStructs[flatid], slot))
    return 0;

  if (isCustom) {
    if (IsValidDynamicObject(FlatStructure[flatid][slot][structObject]))
      DestroyDynamicObject(FlatStructure[flatid][slot][structObject]), FlatStructure[flatid][slot][structObject] = INVALID_STREAMER_ID;
    
    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `flat_structure` WHERE `ID`='%d' AND `Static`='0'", FlatStructure[flatid][slot][structID]);
    mysql_tquery(g_SQL, query);
    new tmp_FlatStructure[structEnum];
    FlatStructure[flatid][slot] = tmp_FlatStructure;  

    Iter_Remove(FlatStructures[flatid], slot);
  } else {
    if (IsValidDynamicObject(FlatStaticStruct[flatid][slot][structObject]))
      DestroyDynamicObject(FlatStaticStruct[flatid][slot][structObject]), FlatStaticStruct[flatid][slot][structObject] = INVALID_STREAMER_ID;

    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `flat_structure` WHERE `ID`='%d' AND `Static`='1'", FlatStaticStruct[flatid][slot][structID]);
    mysql_tquery(g_SQL, query);
    new tmp_FlatStaticStruct[structEnum];
    FlatStaticStruct[flatid][slot] = tmp_FlatStaticStruct;

    Iter_Remove(FlatStaticStructs[flatid], slot);
  }

  return 1;
}

FlatStructure_GetCount(flatid) {
  return Iter_Count(FlatStructures[flatid]);
}

FlatStructure_Copy(flatid, slot) {
  new current = FlatStructure[flatid][slot][structObject],
    model,
    Float:curPos[3],
    Float:curRot[3],
    matModel,
    txdName[32],
    textureName[32],
    matColor,
    textureID = 0;

  model = Streamer_GetIntData(STREAMER_TYPE_OBJECT, current, E_STREAMER_MODEL_ID);
  Streamer_GetFloatData(STREAMER_TYPE_OBJECT, current, E_STREAMER_X, curPos[0]);
  Streamer_GetFloatData(STREAMER_TYPE_OBJECT, current, E_STREAMER_Y, curPos[1]);
  Streamer_GetFloatData(STREAMER_TYPE_OBJECT, current, E_STREAMER_Z, curPos[2]);
  Streamer_GetFloatData(STREAMER_TYPE_OBJECT, current, E_STREAMER_R_X, curRot[0]);
  Streamer_GetFloatData(STREAMER_TYPE_OBJECT, current, E_STREAMER_R_Y, curRot[1]);
  Streamer_GetFloatData(STREAMER_TYPE_OBJECT, current, E_STREAMER_R_Z, curRot[2]);

  if (FlatStructure[flatid][slot][structMaterial] > 0) {
    GetDynamicObjectMaterial(current, 0, matModel, txdName, textureName, matColor);
    textureID = FlatStructure[flatid][slot][structMaterial];
  }

  new copyId = FlatStructure_Create(flatid, model, curPos[0], curPos[1], curPos[2], curRot[0], curRot[1], curRot[2], true);

  if (copyId == cellmin)
    return cellmin;

  if (textureID != 0) SetDynamicObjectMaterial(FlatStructure[flatid][copyId][structObject], 0, matModel, txdName, textureName, matColor), FlatStructure[flatid][copyId][structMaterial] = textureID, FlatStructure_Save(flatid, copyId, true, SAVE_STRUCTURE_MATERIAL);

  return copyId;
}

FlatStructure_Show(playerid, flatid, bool:isCustom = true) {
  static
    count = 0,
    info[MAX_FLAT_STRUCTURE + MAX_STATIC_STRUCTURE * 64];

  if (isCustom) {
    format(info, sizeof(info), "Model\tDistance\n");
    foreach (new i : FlatStructures[flatid]) {
      format(info, sizeof(info), "%s%s\t%.2f\n", info, GetStructureNameByModel(FlatStructure[flatid][i][structModel]), GetPlayerDistanceFromPoint(playerid, FlatStructure[flatid][i][structPos][0], FlatStructure[flatid][i][structPos][1], FlatStructure[flatid][i][structPos][2]));
      ListedFlatStructures[playerid][count++] = i;
    }

    Dialog_Show(playerid, Dialog_FlatCustom, DIALOG_STYLE_TABLIST_HEADERS, "Flat Structures", info, "Select", "Back");
  } else {
    format(info, sizeof(info), "Model\tDistance\n");
    foreach (new i : FlatStaticStructs[flatid]) {
      format(info, sizeof(info), "%s"ORANGE_E"Static\t%.2f\n", info, GetPlayerDistanceFromPoint(playerid, FlatStaticStruct[flatid][i][structPos][0], FlatStaticStruct[flatid][i][structPos][1], FlatStaticStruct[flatid][i][structPos][2]));
      ListedFlatStructures[playerid][count++] = i;
    }

    Dialog_Show(playerid, Dialog_FlatStaticStruct, DIALOG_STYLE_TABLIST_HEADERS, "Flat Structures", info, "Select", "Back");
  }

  return 1;
}
