// Admin Commands
static GetFreeZone() {
  for (new i = 0; i < MAX_FLAT_ROOM; i++) {
    if (testZone[i] == -1) {
      return i;
    }
  }
  return -1;
}

SSCANF:FlatMenu(string[]) {
  if (!strcmp(string, "create", true)) return 1;
  else if (!strcmp(string, "type", true)) return 2;
  else if (!strcmp(string, "name", true)) return 3;
  else if (!strcmp(string, "location", true)) return 4;
  else if (!strcmp(string, "interior", true)) return 5;
  else if (!strcmp(string, "goto", true)) return 6;
  else if (!strcmp(string, "garagepos", true)) return 7;
  else if (!strcmp(string, "delete", true)) return 8;
  return 0;
}

CMD:flat(playerid, params[]) {
  if (pData[playerid][pAdmin] < 5)
    return PermissionError(playerid);

  new menus, extendstr[128];
  if (sscanf(params, "k<FlatMenu>S()[128]", menus, extendstr)) {
    Usage(playerid, "/flat [menu]");
    SendClientMessage(playerid, COLOR_YELLOW, "[MENUS]: "WHITE_E"create, delete, type, name, location, interior, goto, garagepos");
    return 1;
  }

  switch (menus) {
    case 1: { // Create
      new name[32], type;
      if (sscanf(extendstr, "ds[32]", type, name))
        return Usage(playerid, "/flat create [type] [name]");
      
      new Float:position[3];
      GetPlayerPos(playerid, position[0], position[1], position[2]);

      new flatid = Flat_Create(name, type, position[0], position[1], position[2], GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
      
      if (flatid == cellmin)
        return Error(playerid, "Cannot create more flat!");
      
      SendCustomMessage(playerid, "FLAT","You've created flat ID: "YELLOW_E"%d", flatid);
    }
    case 2: { // Type
      new flatid, type;
      if (sscanf(extendstr, "dd", flatid, type))
        return Usage(playerid, "/flat type [flat id] [type]"), SendClientMessage(playerid, COLOR_YELLOW, "[TYPES]: "WHITE_E"1 = low, 2 = medium, 3 = high");
      
      if (!Iter_Contains(Flat, flatid))
        return Error(playerid, "Invalid flat ID");
      
      new typeName[12];
      FlatData[flatid][flatType] = type;
      Flat_GetType(flatid, typeName);
      Flat_Refresh(flatid);
      Flat_Save(flatid);

      SendCustomMessage(playerid, "FLAT", "You've changed type of flat ID: "YELLOW_E"%d "WHITE_E"to "YELLOW_E"%s", flatid, typeName);
    }
    case 3: { // Name
      new flatid, name[32];
      if (sscanf(extendstr, "ds[32]", flatid, name))
        return Usage(playerid, "/flat name [flat id] [flat name]");
      
      if (!Iter_Contains(Flat, flatid))
        return Error(playerid, "Invalid flat ID");
      
      if (strlen(name) > 32)
        return Error(playerid, "Maximum character name is 32 characters");
      
      format(FlatData[flatid][flatName], 32, name);
      Flat_Refresh(flatid);
      Flat_Save(flatid);

      SendCustomMessage(playerid, "FLAT","You've changed name of flat ID: "YELLOW_E"%d "WHITE_E"to "YELLOW_E"%s", flatid, FlatData[flatid][flatName]);
    }
    case 4: { // location
      new flatid;
      if (sscanf(extendstr, "d", flatid))
        return Usage(playerid, "/flat location [flat id]");
      
      if (!Iter_Contains(Flat, flatid))
        return Error(playerid, "Invalid flat ID");
      
      new Float:playerPos[3];
      GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);

      FlatData[flatid][flatPos][0] = playerPos[0];
      FlatData[flatid][flatPos][1] = playerPos[1];
      FlatData[flatid][flatPos][2] = playerPos[2];
      FlatData[flatid][flatWorld] = GetPlayerVirtualWorld(playerid);
      FlatData[flatid][flatInterior] = GetPlayerInterior(playerid);
      Flat_Refresh(flatid);
      Flat_Save(flatid);

      SendCustomMessage(playerid, "FLAT", "You've changed location of flat ID: "YELLOW_E"%d "WHITE_E"to your current location", flatid);
    }
    case 5: { // interior
      new flatid;
      if (sscanf(extendstr, "d", flatid))
        return Usage(playerid, "/flat interior [flat id]");
      
      if (!Iter_Contains(Flat, flatid))
        return Error(playerid, "Invalid flat ID");
      
      new Float:playerPos[3];
      GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);

      FlatData[flatid][flatIntPos][0] = playerPos[0];
      FlatData[flatid][flatIntPos][1] = playerPos[1];
      FlatData[flatid][flatIntPos][2] = playerPos[2];
      FlatData[flatid][flatIntWorld] = GetPlayerVirtualWorld(playerid);
      FlatData[flatid][flatIntInterior] = GetPlayerInterior(playerid);
      Flat_Refresh(flatid);
      Flat_Save(flatid);

      SendCustomMessage(playerid, "FLAT", "You've changed interior of flat ID: "YELLOW_E"%d "WHITE_E"to your current interior", flatid);
    }
    case 6: { // goto
      new flatid;
      if (sscanf(extendstr, "d", flatid))
        return Usage(playerid, "/flat goto [flat id]");
      
      if (!Iter_Contains(Flat, flatid))
        return Error(playerid, "Invalid flat ID");
      
      SetPlayerPos(playerid, FlatData[flatid][flatPos][0],FlatData[flatid][flatPos][1],FlatData[flatid][flatPos][2]);
      SetPlayerVirtualWorld(playerid, FlatData[flatid][flatWorld]);
      SetPlayerInterior(playerid, FlatData[flatid][flatInterior]);

      SendCustomMessage(playerid, "FLAT", "You've been teleported to flat ID: "YELLOW_E"%d", flatid);
    }
    case 7: { // garagepos
      new flatid;
      if (sscanf(extendstr, "d", flatid))
        return Usage(playerid, "/flat garagepos [flat id]");
      
      if (!Iter_Contains(Flat, flatid))
        return Error(playerid, "Invalid flat ID");
      
      new Float:gPos[3];
      GetPlayerPos(playerid, gPos[0], gPos[1], gPos[2]);
      FlatData[flatid][flatGaragePos][0] = gPos[0];
      FlatData[flatid][flatGaragePos][1] = gPos[1];
      FlatData[flatid][flatGaragePos][2] = gPos[2];
      Flat_Refresh(flatid);
      Flat_Save(flatid);

      SendCustomMessage(playerid, "FLAT", "You've changed garage position of flat ID: "YELLOW_E"%d", flatid);
    }
    case 8: { // delete
      new flatid;
      if (sscanf(extendstr, "d", flatid))
        return Usage(playerid, "/flat delete [flat id]");
      
      if (!Iter_Contains(Flat, flatid))
        return Error(playerid, "Invalid flat ID");
      
      if (Flat_Delete(flatid)){
        foreach (new flatroom : FlatRooms) if (FlatRoom[flatroom][flatID] == FlatData[flatid][flatID]) {
          FlatRoom_Delete(flatroom);
        }
        SendCustomMessage(playerid, "FLAT","You've deleted flat ID: "YELLOW_E"%d", flatid);
      } else return Error(playerid, "Unable to delete flat ID: "YELLOW_E"%d", flatid);
    }
    default: {
      Usage(playerid, "/flat [menu]");
      SendClientMessage(playerid, COLOR_YELLOW, "[MENUS]: "WHITE_E"create, delete, type, name, location, interior, goto, garagepos");
      return 1;
    }
  }
  return 1;
}

SSCANF:FlatRoomMenu(string[]) {
  if (!strcmp(string,"create",true)) return 1;
  else if (!strcmp(string,"delete",true)) return 2;
  else if (!strcmp(string,"editdoor",true)) return 3;
  else if (!strcmp(string,"areapos",true)) return 4;
  else if (!strcmp(string,"price",true)) return 5;
  else if (!strcmp(string,"location",true)) return 6;
  else if (!strcmp(string,"resetowner",true)) return 7;
  else if (!strcmp(string,"gangzone",true)) return 8;
  else if (!strcmp(string,"structure",true)) return 9;
  else if (!strcmp(string,"editstructure",true)) return 10;
  else if (!strcmp(string,"createinterior",true)) return 11;
  else if (!strcmp(string,"goto",true)) return 12;
  return 0;
}

CMD:flatroommenu(playerid, params[]) {
  if (pData[playerid][pAdmin] < 5)
    return PermissionError(playerid);
  
  new menus, extendstr[128];
  if (sscanf(params,"k<FlatRoomMenu>S()[128]",menus,extendstr)) {
    Usage(playerid, "/flatroommenu [menu]");
    SendClientMessage(playerid, COLOR_YELLOW, "[MENUS]: "WHITE_E"create, delete, editdoor, areapos, price, location, resetowner, structure, editstructure, createinterior, goto");
    return 1;
  }

  switch (menus) {
    case 1: { // create
      new price, flatid = pData[playerid][pInFlat];
      if (sscanf(extendstr,"d",price))
        return Usage(playerid, "/flatroommenu create [price]");
      
      if (price < 1)
        return Error(playerid, "Price cannot go below 1");
      
      if (flatid == -1)
        return Error(playerid, "You're not on inside flat");
      
      new Float:pos[3];
      GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

      new flatroom = FlatRoom_Create(price, pos[0], pos[1], pos[2], GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), flatid);

      if (flatroom == cellmin)
        return Error(playerid, "Cannot create more flat room");
      
      SendCustomMessage(playerid,"FLATROOM","You've created flat room ID: "YELLOW_E"%d", flatroom);
    }
    case 2: { // delete
      new flatroom;
      if (sscanf(extendstr, "d", flatroom))
        return Usage(playerid, "/flatroommenu delete [flatroom id]");
      
      if (!Iter_Contains(FlatRooms, flatroom))
        return Error(playerid, "Invalid flat room ID");
      
      if (FlatRoom_Delete(flatroom))
        SendCustomMessage(playerid,"FLATROOM","You've deleted flat room ID: "YELLOW_E"%d", flatroom);
      else
        return Error(playerid, "Unable to delete flat room");
    }
    case 3: { // editdoor
      new flatroom;
      if (sscanf(extendstr, "d", flatroom))
        return Usage(playerid, "/flatroommenu editdoor [flatroom id]");
      
      if (!Iter_Contains(FlatRooms, flatroom))
        return Error(playerid, "Invalid flat room ID");
      
      foreach (new i : FlatStaticStructs[flatroom]) if (IsValidDynamicObject(FlatStaticStruct[flatroom][i][structObject])) {
        new model = Streamer_GetIntData(STREAMER_TYPE_OBJECT, FlatStaticStruct[flatroom][i][structObject], E_STREAMER_MODEL_ID);

        if (model == 1502 || model == 19430) {
          editDoorFlat[playerid] = flatroom;
          pData[playerid][pEditStaticStructure] = i;
          EditDynamicObject(playerid, FlatStaticStruct[flatroom][i][structObject]);
          SendCustomMessage(playerid, "FLATROOM","You're now editing flat room door ID: "YELLOW_E"%d", flatroom);
          break;
        }
      }
    }
    case 4: { // areapos
      new flatroom, Float:minPos[2], Float:maxPos[2], Float:height;
      if (sscanf(extendstr, "dfffff", flatroom, minPos[0], minPos[1], maxPos[0], maxPos[1], height))
        return Usage(playerid, "/flatroommenu areapos [flatroom id] [minx/barat] [miny/selatan] [maxx/timur] [maxy/utara] [z/tinggi]");
      
      if (!Iter_Contains(FlatRooms, flatroom))
        return Error(playerid, "Invalid flat room ID");

      FlatRoom[flatroom][flatRoomAreaPos][0] = minPos[0];
      FlatRoom[flatroom][flatRoomAreaPos][1] = minPos[1];
      FlatRoom[flatroom][flatRoomAreaPos][2] = maxPos[0];
      FlatRoom[flatroom][flatRoomAreaPos][3] = maxPos[1];
      FlatRoom[flatroom][flatRoomAreaPos][4] = height;

      FlatRoom_Refresh(flatroom);
      FlatRoom_Save(flatroom);

      SendCustomMessage(playerid, "FLATROOM","You've set flat room ID: "YELLOW_E"%d"WHITE_E" area pos to: "YELLOW_E"%.2f, %.2f, %.2f, %.2f", flatroom, minPos[0], minPos[1], maxPos[0], maxPos[1]);
    }
    case 5: { // price
      new flatroom, price;
      if (sscanf(extendstr, "dd", flatroom, price))
        return Usage(playerid, "/flatroommenu price [flatroom id] [price]");
      
      if (!Iter_Contains(FlatRooms, flatroom))
        return Error(playerid, "Invalid flat room ID");
      
      if (price < 1)
        return Error(playerid, "Price cannot go below 1");
      
      FlatRoom[flatroom][flatRoomPrice] = price;
      FlatRoom_Refresh(flatroom);
      FlatRoom_Save(flatroom);

      SendCustomMessage(playerid,"FLATROOM","You've set new price of flat room ID: "YELLOW_E"%d "WHITE_E"to "GREEN_E"%s",flatroom,FormatMoney(FlatRoom[flatroom][flatRoomPrice]));
    }
    case 6: { // location
      new flatroom;
      if (sscanf(extendstr, "d", flatroom))
        return Usage(playerid, "/flatroommenu location [flatroom id]");
      
      if (!Iter_Contains(FlatRooms, flatroom))
        return Error(playerid, "Invalid flat room ID");
      
      new Float:fPos[3];
      GetPlayerPos(playerid, fPos[0], fPos[1], fPos[2]);
      FlatRoom[flatroom][flatRoomPos][0] = fPos[0];
      FlatRoom[flatroom][flatRoomPos][1] = fPos[1];
      FlatRoom[flatroom][flatRoomPos][2] = fPos[2];
      FlatRoom[flatroom][flatRoomWorld] = GetPlayerVirtualWorld(playerid);
      FlatRoom[flatroom][flatRoomInterior] = GetPlayerInterior(playerid);

      foreach (new i : FlatStaticStructs[flatroom]) if (IsValidDynamicObject(FlatStaticStruct[flatroom][i][structObject])) {
        new curModel = Streamer_GetIntData(STREAMER_TYPE_OBJECT, FlatStaticStruct[flatroom][i][structObject], E_STREAMER_MODEL_ID);

        if (curModel == 1536 || curModel == 1502) {
          FlatStaticStruct[flatroom][i][structPos][0] = fPos[0];
          FlatStaticStruct[flatroom][i][structPos][1] = fPos[1];
          FlatStaticStruct[flatroom][i][structPos][2] = fPos[2];
          FlatStructure_Refresh(flatroom, i, false);
          FlatStructure_Save(flatroom, i, false, SAVE_STRUCTURE_POS);
        }
      }

      FlatRoom_Refresh(flatroom);
      FlatRoom_Save(flatroom);

      SendCustomMessage(playerid,"FLATROOM","You've changed location of flat room ID: "YELLOW_E"%d", flatroom);
    }
    case 7: { // resetowner
      new flatroom;
      if (sscanf(extendstr, "d", flatroom))
        return Usage(playerid, "/flatroommenu resetowner [flatroom id]");
      
      if (!Iter_Contains(FlatRooms, flatroom))
        return Error(playerid, "Invalid flat room ID");
      
      FlatRoom[flatroom][flatRoomOwner] = 0;
      FlatRoom_Refresh(flatroom);
      FlatRoom_Save(flatroom);

      SendCustomMessage(playerid,"FLATROOM","You've reset owner of flat room ID: "YELLOW_E"%d", flatroom);
    }
    case 8: { // gangzone
      new flatroom;
      if (sscanf(extendstr, "d", flatroom))
        return Usage(playerid, "/flatroommenu gangzone [flatroom id]");
      
      if (!Iter_Contains(FlatRooms, flatroom))
        return Error(playerid, "Invalid flat room ID");
      
      new gangID = GetFreeZone();
      if (gangID == -1)
        return Error(playerid, "No free gang zones available");
      
      testZone[gangID] = GangZoneCreate(FlatRoom[flatroom][flatRoomAreaPos][0], FlatRoom[flatroom][flatRoomAreaPos][1], FlatRoom[flatroom][flatRoomAreaPos][2], FlatRoom[flatroom][flatRoomAreaPos][3]);
      GangZoneShowForAll(testZone[gangID], 0xFF0000FF);
      GangZoneFlashForAll(testZone[gangID], 0xFF0000FF);

      SendCustomMessage(playerid,"FLATROOM","You've created gang zone ID: "YELLOW_E"%d"WHITE_E" for flat room ID: "YELLOW_E"%d", gangID, flatroom);
    }
    case 9: { // create Structure
      new flatroom, modelid;
      if (sscanf(extendstr, "dd", flatroom, modelid))
        return Usage(playerid, "/flatroommenu structure [flatroom id] [modelid]");
      
      if (!Iter_Contains(FlatRooms, flatroom))
        return Error(playerid, "Invalid flat room ID");
      
      static
        Float:x,
        Float:y,
        Float:z,
        Float:angle
      ;

      GetPlayerPos(playerid, z, z, z);
      GetPlayerFacingAngle(playerid, angle);

      new slot = FlatStructure_Create(flatroom, modelid, x, y, z, 0.0, 0.0, angle, false);

      if (slot == cellmin)
        return Error(playerid, "You can't create more structure in this flat");

      pData[playerid][pEditStaticStructure] = slot;
      pData[playerid][pEditFlatStructure] = flatroom;
      EditDynamicObject(playerid, FlatStaticStruct[flatroom][slot][structObject]);
    }
    case 10: { // edit Structure
      new flatroom;
      if (sscanf(extendstr, "d", flatroom))
        return Usage(playerid, "/flatroommenu editstructure [flatroom id]");
      
      if (!Iter_Contains(FlatRooms, flatroom))
        return Error(playerid, "Invalid flat room ID");
      
      new info[256], count = 0;

      strcat(info,"Model\tDistance\n");
      foreach (new i : FlatStaticStructs[flatroom]) if (IsValidDynamicObject(FlatStaticStruct[flatroom][i][structObject])) {
        format(info, sizeof(info), "%s%d\t%.1f\n", info, FlatStaticStruct[flatroom][i][structModel], GetPlayerDistanceFromPoint(playerid, FlatStaticStruct[flatroom][i][structPos][0], FlatStaticStruct[flatroom][i][structPos][1], FlatStaticStruct[flatroom][i][structPos][2]));
        ListedFlatStructures[playerid][count++] = i;
      }

      if (count) Dialog_Show(playerid, Flat_EditStatic, DIALOG_STYLE_TABLIST_HEADERS, "Edit Static Structures", info, "Select", "Cancel");
      else Error(playerid, "There are no static structure on this flat");
    }
    case 11: { // Create Interior
      new flatroom, roomid;
      if (sscanf(extendstr, "dd", flatroom, roomid))
        return Usage(playerid, "/flatroommenu createinterior [flatroom id] [room id]");
      
      if (!Iter_Contains(FlatRooms, flatroom))
        return Error(playerid, "Invalid flat room ID");
      
      if (roomid < 1)
        return Error(playerid, "Invalid Room ID!");
      
      new maxRoom, flatBase = Flat_ReturnID(flatroom);

      if (flatBase != -1) {
        switch (FlatData[flatBase][flatType]) {
          case FLAT_TYPE_LOW: maxRoom = 12;
          case FLAT_TYPE_MEDIUM: maxRoom = 16;
          case FLAT_TYPE_HIGH: maxRoom = 16;
        }

        if (roomid > maxRoom)
          return Error(playerid, "Invalid Room ID!");

        CreateFlatInterior(flatroom, roomid);
        SendCustomMessage(playerid, "FLAT", "You've been created flat interior for ID: "YELLOW_E"%d", flatroom);
      }
    }
    case 12: { // goto
      new flatroom;
      if (sscanf(extendstr, "d", flatroom))
        return Usage(playerid, "/flatroommenu goto [flatroom id]");
      
      if (!Iter_Contains(FlatRooms, flatroom))
        return Error(playerid, "Invalid flat room ID");
      
      SetPlayerPos(playerid, FlatRoom[flatroom][flatRoomPos][0],FlatRoom[flatroom][flatRoomPos][1],FlatRoom[flatroom][flatRoomPos][2]);
      SetPlayerVirtualWorld(playerid, FlatRoom[flatroom][flatRoomWorld]);
      SetPlayerInterior(playerid, FlatRoom[flatroom][flatRoomInterior]);

      SendCustomMessage(playerid, "FLATROOM", "You've been teleported to flatroom ID: "YELLOW_E"%d", flatroom);
    }
    default: {
      Usage(playerid, "/flatroommenu [menu]");
      SendClientMessage(playerid, COLOR_YELLOW, "[MENUS]: "WHITE_E"create, delete, editdoor, areapos, price, location, resetowner, structure, editstructure, createinterior");
      return 1;
    }
  }
  return 1;
}

// Player Commands
CMD:buyflat(playerid,params[]) {
  new flatroom = -1;
  if ((flatroom = FlatRoom_Nearest(playerid)) != -1) {
    if (!IsValidDynamicArea(FlatRoom[flatroom][flatRoomArea]))
      return Error(playerid, "This flat has no interior, please contact Head Admin");
    
    if (!pData[playerid][pCS])
      return Error(playerid, "You must have accepted character story to buying any property");

    if(PropertiResidential_CountMax(playerid) >= PropertiesResidential_Max(playerid)) return Error(playerid, "You can no longer buy a flat, your property slots are full");
  
    if (FlatRoom[flatroom][flatRoomOwner])
      return Error(playerid, "This flat is already owned by other players");
    
    if (GetPlayerMoney(playerid) < FlatRoom[flatroom][flatRoomPrice])
      return Error(playerid,"You don't have enough money to buy this flat");
    
    FlatRoom[flatroom][flatRoomOwner] = pData[playerid][pID];
    FlatRoom[flatroom][flatRoomSeal] = 0;
    FlatRoom[flatroom][flatRoomMoney] = 0;
    FlatRoom[flatroom][flatRoomLastVisited] = gettime();
    GivePlayerMoneyEx(playerid, -FlatRoom[flatroom][flatRoomPrice]);
    Flat_RemoveAllItems(flatroom);
    FlatFurniture_DeleteAll(flatroom);
    FlatStructure_DeleteAll(flatroom, true);

    FlatRoom_Refresh(flatroom);
    FlatRoom_Save(flatroom);
    return 1;
  }
  Error(playerid, "You're not in range of any flat");
  return 1;
}

CMD:flock(playerid) {
  new id = -1;
  if ((id = FlatRoom_Nearest(playerid)) != -1 || (id = FlatRoom_Inside(playerid)) != -1) {
    if (FlatRoom[id][flatRoomSeal])
      return Error(playerid, "This flat is sealed by the authority");

    if (!FlatRoom_IsOwner(playerid,id) && !FlatRoom_IsBuilder(playerid,id))
      return Error(playerid, "You're not the owner or builder of this flat");
    
    FlatRoom[id][flatRoomLocked] = FlatRoom[id][flatRoomLocked] ? 0 : 1;
    switch(FlatRoom[id][flatRoomLocked])
    {
      case 0:
      {
        GameTextForPlayer(playerid, "~w~Flat ~r~Locked",  1000, 6);
      }
      case 1:
      {
        GameTextForPlayer(playerid, "~w~Flat ~g~Unlocked", 1000, 6);
      }
    }
    FlatRoom_Refresh(id);
    FlatRoom_Save(id);
    return 1;
  }
  Error(playerid, "You're not in range of any flat");
  return 1;
}

CMD:flatmenu(playerid) {
  new id = -1;
  if ((id = FlatRoom_Inside(playerid)) != -1) {
    if (FlatRoom[id][flatRoomSeal])
      return Error(playerid, "This flat is sealed by the authority");

    if (!FlatRoom_IsOwner(playerid, id) && !FlatRoom_IsBuilder(playerid, id))
      return Error(playerid, "You're not the owner or builder of this flat");
    
    Dialog_Show(playerid, Dialog_FlatMenu, DIALOG_STYLE_LIST, "Flat Menu", "%s Flat\nFlat Storage\nFurnitures\nStructures\nAssign Builder", (FlatRoom[id][flatRoomLocked]) ? ("Unlock") : ("Lock"), "Select", "Cancel");
    return 1;
  }
  Error(playerid,"You're not in range of any flat");
  return 1;
}

CMD:getfreestruct(playerid, params[]) {
  if (pData[playerid][pAdmin] < 5)
    return PermissionError(playerid);
  
  new flatid, type[12];
  if (sscanf(params, "ds[12]", flatid, type))
    return Usage(playerid, "/getfreestruct [flat id] [type]");
  
  if (!strcmp(type, "static", true)) {
    if (!Iter_Contains(FlatRooms, flatid))
      return Error(playerid, "Invalid flat room ID");
    
    new freeid;

    if ((freeid = Iter_Free(FlatStaticStructs[flatid])) != cellmin) {
      SendCustomMessage(playerid, "FREEID", "Available for Flat ID: "YELLOW_E"%d "WHITE_E"Static structure ID: "YELLOW_E"%d", flatid, freeid);
    } else {
      Error(playerid, "There are no free static structures for this flat");
    }
  } else if (!strcmp(type, "custom", true)) {
    if (!Iter_Contains(FlatRooms, flatid))
      return Error(playerid, "Invalid flat room ID");
    
    new freeid;

    if ((freeid = Iter_Free(FlatStructures[flatid])) != cellmin) {
      SendCustomMessage(playerid, "FREEID", "Available for Flat ID: "YELLOW_E"%d "WHITE_E"Custom structure ID: "YELLOW_E"%d", flatid, freeid);
    } else {
      Error(playerid, "There are no free custom structures for this flat");
    }
  }
  return 1;
}

CMD:giveflat(playerid, params[])
{
    new hid, otherid;
    
    if(pData[playerid][pLevel] < 3) return Error(playerid, "Anda harus level 3 untuk bisa melalukan akses ini");
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1424.31, 1546.21, 3010.83)) return Error(playerid, "Anda harus berada di City Hall!");
    if(sscanf(params, "ud", otherid, hid)) return Usage(playerid, "/giveflat [playerid/name] [id flat]");
    if(hid == -1) return Error(playerid, "Invalid id");
    
    if(!IsPlayerConnected(otherid) || !NearPlayer(playerid, otherid, 4.0)) return Error(playerid, "The specified player is disconnected or not near you.");

    if(!FlatRoom_IsOwner(playerid, hid)) return Error(playerid, "You dont own this id flat.");
    if(PropertiResidential_CountMax(otherid) >= PropertiesResidential_Max(otherid)) return Error(playerid, "property slots are full");
    FlatRoom[hid][flatRoomOwner] = pData[otherid][pID];
    FlatRoom[hid][flatRoomMoney] = 0;
    FlatRoom[hid][flatRoomLastVisited] = gettime();
    Flat_RemoveAllItems(hid);

    FlatRoom_Refresh(hid);
    FlatRoom_Save(hid);
    SendCustomMessage(playerid, "FLAT", "You have successfully purchased %s's Flat", ReturnName(otherid));
    SendCustomMessage(otherid, "FLAT", "%s has successfully purchased your Flat", ReturnName(playerid));
    return 1;
}
