
ApartStructure_GetCount(suiteid) {
  return Iter_Count(SuiteStructures[suiteid]);
}

ApartStructure_Create(suiteid, modelid, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0) {
  new slot;
  if (!Iter_Contains(SuiteRooms, suiteid)) return 0;
  if ((slot = Iter_Free(SuiteStructures[suiteid])) != cellmin) {
    Iter_Add(SuiteStructures[suiteid], slot);
    
    SuiteStructure[suiteid][slot][suitestructModel] = modelid;
    SuiteStructure[suiteid][slot][suitestructPos][0] = x;
    SuiteStructure[suiteid][slot][suitestructPos][1] = y;
    SuiteStructure[suiteid][slot][suitestructPos][2] = z;
    SuiteStructure[suiteid][slot][suitestructRot][0] = rx;
    SuiteStructure[suiteid][slot][suitestructRot][1] = ry;
    SuiteStructure[suiteid][slot][suitestructRot][2] = rz;
    SuiteStructure[suiteid][slot][suitestructMaterial] = 0;
    SuiteStructure[suiteid][slot][suitestructColor] = 0;
    SuiteStructure_Refresh(suiteid, slot);
    mysql_tquery(g_SQL, "INSERT INTO `suite_structure` (`Static`) VALUES ('0')", "OnSuiteStructureCreated", "dd", suiteid, slot);
    return slot;
  }
  return cellmin;
}

function OnSuiteStructureCreated(suiteid, slot) {
  if (!Iter_Contains(SuiteStructures[suiteid], slot)) return 0;
  SuiteStructure[suiteid][slot][suitestructID] = cache_insert_id(), ApartStructure_Save(suiteid, slot);
  return 1;
}

function OnLoadSuiteStructure(suiteid) {
  new rows = cache_num_rows(),
    str[128],
    slot = cellmin;

  Iter_Init(SuiteStructures);
  for (new i = 0; i < rows; i ++) if ((slot = Iter_Free(SuiteStructures[suiteid])) != cellmin) {
    Iter_Add(SuiteStructures[suiteid], slot);

    cache_get_value_int(i, "ID", SuiteStructure[suiteid][slot][suitestructID]);
    cache_get_value_int(i, "Model", SuiteStructure[suiteid][slot][suitestructModel]);
    
    cache_get_value(i, "Position", str);
    sscanf(str, "p<|>fff", SuiteStructure[suiteid][slot][suitestructPos][0], SuiteStructure[suiteid][slot][suitestructPos][1], SuiteStructure[suiteid][slot][suitestructPos][2]);

    cache_get_value(i, "Rotation", str);
    sscanf(str, "p<|>fff", SuiteStructure[suiteid][slot][suitestructRot][0], SuiteStructure[suiteid][slot][suitestructRot][1], SuiteStructure[suiteid][slot][suitestructRot][2]);

    cache_get_value(i, "Material", str);
    sscanf(str, "p<|>dd", SuiteStructure[suiteid][slot][suitestructMaterial], SuiteStructure[suiteid][slot][suitestructColor]);

    SuiteStructure_Refresh(suiteid, slot);
  }
  return 1;
}

SuiteStructure_Refresh(suiteid, slot) {
  if (!Iter_Contains(SuiteRooms, suiteid)) return 0;
  if (!Iter_Contains(SuiteStructures[suiteid], slot)) return 0;
  
  if (!IsValidDynamicObject(SuiteStructure[suiteid][slot][suitestructObject])) {
    SuiteStructure[suiteid][slot][suitestructObject] = CreateDynamicObject(SuiteStructure[suiteid][slot][suitestructModel], SuiteStructure[suiteid][slot][suitestructPos][0], SuiteStructure[suiteid][slot][suitestructPos][1], SuiteStructure[suiteid][slot][suitestructPos][2], SuiteStructure[suiteid][slot][suitestructRot][0], SuiteStructure[suiteid][slot][suitestructRot][1], SuiteStructure[suiteid][slot][suitestructRot][2], SuiteRoom[suiteid][suiteRoomWorld], SuiteRoom[suiteid][suiteRoomInterior], -1, STREAMER_OBJECT_SD, 200.00, SuiteRoom[suiteid][suiteRoomArea]);
  }

  SuiteStructure_Update(suiteid, slot);
  foreach (new i : Player) if (IsPlayerInRangeOfPoint(i, 5.0, SuiteStructure[suiteid][slot][suitestructPos][0], SuiteStructure[suiteid][slot][suitestructPos][1], SuiteStructure[suiteid][slot][suitestructPos][2])) {
    Streamer_Update(i);
  }
  return 1;
}

SuiteStructure_Update(suiteid, slot) {
  if (!Iter_Contains(SuiteRooms, suiteid)) return 0;
  if (!Iter_Contains(SuiteStructures[suiteid], slot)) return 0;
  
  new objectid;
  objectid = SuiteStructure[suiteid][slot][suitestructObject];
  Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_X, SuiteStructure[suiteid][slot][suitestructPos][0]);
  Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Y, SuiteStructure[suiteid][slot][suitestructPos][1]);
  Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Z, SuiteStructure[suiteid][slot][suitestructPos][2]);

  Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_X, SuiteStructure[suiteid][slot][suitestructRot][0]);
  Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Y, SuiteStructure[suiteid][slot][suitestructRot][1]);
  Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Z, SuiteStructure[suiteid][slot][suitestructRot][2]);

  Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_WORLD_ID, SuiteRoom[suiteid][suiteRoomWorld]);
  Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_INTERIOR_ID, SuiteRoom[suiteid][suiteRoomInterior]);

  Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_AREA_ID, SuiteRoom[suiteid][suiteRoomArea]);

  if (SuiteStructure[suiteid][slot][suitestructMaterial] > 0) {
    if (SuiteStructure[suiteid][slot][suitestructModel] == 1502 || SuiteStructure[suiteid][slot][suitestructModel] == 14414) SetDynamicObjectMaterial(SuiteStructure[suiteid][slot][suitestructObject], 1, GetTModel(SuiteStructure[suiteid][slot][suitestructMaterial]), GetTXDName(SuiteStructure[suiteid][slot][suitestructMaterial]), GetTextureName(SuiteStructure[suiteid][slot][suitestructMaterial]), SuiteStructure[suiteid][slot][suitestructColor]);
    else SetDynamicObjectMaterial(objectid, 0, GetTModel(SuiteStructure[suiteid][slot][suitestructMaterial]), GetTXDName(SuiteStructure[suiteid][slot][suitestructMaterial]), GetTextureName(SuiteStructure[suiteid][slot][suitestructMaterial]), SuiteStructure[suiteid][slot][suitestructColor]);
  }
  return 1;
}

SuiteStructure_Delete(suiteid, slot) {
  if (!Iter_Contains(SuiteStructures[suiteid], slot)) return 0;

  if (IsValidDynamicObject(SuiteStructure[suiteid][slot][suitestructObject]))
    DestroyDynamicObject(SuiteStructure[suiteid][slot][suitestructObject]), SuiteStructure[suiteid][slot][suitestructObject] = INVALID_STREAMER_ID;
  
  new query[128];
  mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `suite_structure` WHERE `ID`='%d' AND `Static`='0'", SuiteStructure[suiteid][slot][suitestructID]);
  mysql_tquery(g_SQL, query);
  new tmp_SuiteStructure[suitestruct];
  SuiteStructure[suiteid][slot] = tmp_SuiteStructure;  
  Iter_Remove(SuiteStructures[suiteid], slot);
  return 1;
}

SuiteStructure_DeleteAll(suiteid) {
  if (Iter_Contains(SuiteRooms, suiteid)) {
    foreach (new slot : SuiteStructures[suiteid]) {
      if (IsValidDynamicObject(SuiteStructure[suiteid][slot][suitestructObject]))
        DestroyDynamicObject(SuiteStructure[suiteid][slot][suitestructObject]), SuiteStructure[suiteid][slot][suitestructObject] = INVALID_STREAMER_ID;
    
      new query[128];
      mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `suite_structure` WHERE `ID`='%d' AND `Static`='0'", SuiteStructure[suiteid][slot][suitestructID]);
      mysql_tquery(g_SQL, query);
      new tmp_SuiteStructure[suitestruct];
      SuiteStructure[suiteid][slot] = tmp_SuiteStructure;  
    }
    Iter_Clear(SuiteStructures[suiteid]);
  }
  return 1;
}

SuiteStructure_Copy(suiteid, slot) {
  new current = SuiteStructure[suiteid][slot][suitestructObject],
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

  if (SuiteStructure[suiteid][slot][suitestructMaterial] > 0) {
    GetDynamicObjectMaterial(current, 0, matModel, txdName, textureName, matColor);
    textureID = SuiteStructure[suiteid][slot][suitestructMaterial];
  }

  new copyId = ApartStructure_Create(suiteid, model, curPos[0], curPos[1], curPos[2], curRot[0], curRot[1], curRot[2]);

  if (copyId == cellmin)
    return cellmin;

  if (textureID != 0) SetDynamicObjectMaterial(SuiteStructure[suiteid][copyId][suitestructObject], 0, matModel, txdName, textureName, matColor), SuiteStructure[suiteid][copyId][suitestructMaterial] = textureID, ApartStructure_Save(suiteid, copyId, SAVE_STRUCTURE_MATERIAL);

  return copyId;
}

SuiteStructure_Show(playerid, suiteid) {
  new
    count = 0,
    info[MAX_SUITE_STRUCTURE];
  format(info, sizeof(info), "Model\tDistance\n");
  foreach (new i : SuiteStructures[suiteid]) {
    format(info, sizeof(info), "%s%s\t%.2f\n", info, GetStructureNameByModel(SuiteStructure[suiteid][i][suitestructModel]), GetPlayerDistanceFromPoint(playerid, SuiteStructure[suiteid][i][suitestructPos][0], SuiteStructure[suiteid][i][suitestructPos][1], SuiteStructure[suiteid][i][suitestructPos][2]));
    ListedSuiteStructures[playerid][count++] = i;
  }
  Dialog_Show(playerid, Dialog_SuiteCustom, DIALOG_STYLE_TABLIST_HEADERS, "Suite Structures", info, "Select", "Back");
  return 1;
}

ApartStructure_Save(suiteid, slot, mode = SAVE_STRUCTURE_ALL) {
  if (!Iter_Contains(SuiteRooms, suiteid)) return 0;
  if (!Iter_Contains(SuiteStructures[suiteid], slot))  return 0;
  switch (mode) {
    case SAVE_STRUCTURE_ALL: {
      new query[2024];
      format(query, sizeof(query), "UPDATE `suite_structure` SET `suiteid`='%d', `Model`='%d', `Position`='%.2f|%.2f|%.2f', `Rotation`='%.2f|%.2f|%.2f', `Material`='%d|%d' WHERE `ID`='%d' AND `Static`='0'",
        SuiteRoom[suiteid][suiteRoomID],
        SuiteStructure[suiteid][slot][suitestructModel],
        SuiteStructure[suiteid][slot][suitestructPos][0],
        SuiteStructure[suiteid][slot][suitestructPos][1],
        SuiteStructure[suiteid][slot][suitestructPos][2],
        SuiteStructure[suiteid][slot][suitestructRot][0],
        SuiteStructure[suiteid][slot][suitestructRot][1],
        SuiteStructure[suiteid][slot][suitestructRot][2],
        SuiteStructure[suiteid][slot][suitestructMaterial],
        SuiteStructure[suiteid][slot][suitestructColor],
        SuiteStructure[suiteid][slot][suitestructID]
      );
      mysql_tquery(g_SQL, query);
    }
    case SAVE_STRUCTURE_MATERIAL: {
      new query[2024];
      format(query, sizeof(query), "UPDATE `suite_structure` SET `suiteid`='%d', `Material`='%d|%d' WHERE `ID`='%d' AND `Static`='0'",
        SuiteRoom[suiteid][suiteRoomID],
        SuiteStructure[suiteid][slot][suitestructMaterial],
        SuiteStructure[suiteid][slot][suitestructColor],
        SuiteStructure[suiteid][slot][suitestructID]
      );
      mysql_tquery(g_SQL, query);
    }
    case SAVE_STRUCTURE_MODEL: {
      new query[2024];
      format(query, sizeof(query), "UPDATE `suite_structure` SET `suiteid`='%d', `Model`='%d' WHERE `ID`='%d' AND `Static`='0'",
        SuiteRoom[suiteid][suiteRoomID],
        SuiteStructure[suiteid][slot][suitestructModel],
        SuiteStructure[suiteid][slot][suitestructID]
      );
      mysql_tquery(g_SQL, query);
    }
    case SAVE_STRUCTURE_POS: {
      new query[2024];
      format(query, sizeof(query), "UPDATE `suite_structure` SET `suiteid`='%d', `Position`='%.2f|%.2f|%.2f', `Rotation`='%.2f|%.2f|%.2f' WHERE `ID`='%d' AND `Static`='0'",
        SuiteRoom[suiteid][suiteRoomID],
        SuiteStructure[suiteid][slot][suitestructPos][0],
        SuiteStructure[suiteid][slot][suitestructPos][1],
        SuiteStructure[suiteid][slot][suitestructPos][2],
        SuiteStructure[suiteid][slot][suitestructRot][0],
        SuiteStructure[suiteid][slot][suitestructRot][1],
        SuiteStructure[suiteid][slot][suitestructRot][2],
        SuiteStructure[suiteid][slot][suitestructID]
      );
      mysql_tquery(g_SQL, query);
    }
  }
  return 1;
}

