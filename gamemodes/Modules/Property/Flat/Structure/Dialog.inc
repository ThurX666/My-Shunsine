
Dialog:Dialog_FlatStaticStruct(playerid, response, listitem, inputtext[]) {
  if (!response)
    return Dialog_Show(playerid, Select_FlatStructures, DIALOG_STYLE_LIST, "Select Flat Structure", "Static\nCustom", "Select", "Back");

  new flatid;

  if ((flatid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
    new slot = ListedFlatStructures[playerid][listitem];
    pData[playerid][pEditStructure] = slot;
    pData[playerid][pEditFlatStructure] = flatid;
    Dialog_Show(playerid, Dialog_FlatStatic, DIALOG_STYLE_LIST, "Edit Flat Structure", "Retexture", "Select", "Back");
  }
  return 1;
}

Dialog:Dialog_FlatStatic(playerid, response, listitem, inputtext[]) {
  if (!response)
    return Dialog_Show(playerid, Select_FlatStructures, DIALOG_STYLE_LIST, "Select Flat Structure", "Static\nCustom", "Select", "Back");

  new flatid;

  if ((flatid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
    switch (listitem) {
      case 0: {
        Dialog_Show(playerid, Dialog_StaticRetexture, DIALOG_STYLE_INPUT, "Retexture Flat Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel");
      }
    }
  }
  return 1;
}

Dialog:Dialog_FlatCustom(playerid, response, listitem, inputtext[]) {
  if (!response)
    return Dialog_Show(playerid, Select_FlatStructures, DIALOG_STYLE_LIST, "Select Flat Structure", "Static\nCustom", "Select", "Back");

  new flatid;

  if ((flatid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
    new slot = ListedFlatStructures[playerid][listitem];
    pData[playerid][pEditStructure] = slot;
    pData[playerid][pEditFlatStructure] = flatid;
    Dialog_Show(playerid, Dialog_EditFlatCustom, DIALOG_STYLE_LIST, "Edit Flat Structure", "Move\nRetexture\nCopy\nDestroy", "Select", "Back");
  }
  return 1;
}

Dialog:Dialog_EditFlatCustom(playerid, response, listitem, inputtext[]) {
  if (!response)
    return Dialog_Show(playerid, Select_FlatStructures, DIALOG_STYLE_LIST, "Select Flat Structure", "Static\nCustom", "Select", "Back");

  new flatid;

  if ((flatid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
    new slot = pData[playerid][pEditStructure];

    switch (listitem) {
      case 0: {
        pData[playerid][pEditFlatStructure] = flatid;
        EditDynamicObject(playerid, FlatStructure[flatid][slot][structObject]);
        SendCustomMessage(playerid, "BUILDER", "You're now editing %s", GetStructureNameByModel(FlatStructure[flatid][slot][structModel]));
      }
      case 1: {
        pData[playerid][pEditFlatStructure] = flatid;
        Dialog_Show(playerid, Dialog_FlatRetexture, DIALOG_STYLE_INPUT, "Retexture Flat Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel");
      }
      case 2: {
        new price;

        for (new id = 0; id < sizeof(g_aHouseStructure); id ++) if (g_aHouseStructure[id][e_StructureModel] == FlatStructure[flatid][slot][structModel]) {
          price = g_aHouseStructure[id][e_StructureCost];
        }

        if (pData[playerid][pComponent] < price)
          return Error(playerid, "You need %d Component(s) to copy this structure.", price);

        new copyId = FlatStructure_Copy(flatid, slot);

        if (copyId == cellmin)
          return Error(playerid, "Your flat has reached maximum of structure");
        
        pData[playerid][pComponent] -= price;
        pData[playerid][pEditStructure] = copyId;
        pData[playerid][pEditFlatStructure] = flatid;
        EditDynamicObject(playerid, FlatStructure[flatid][copyId][structObject]);
        SendCustomMessage(playerid, "BUILDER", "You have copied structure for "GREEN_E"%d component(s)", price);
        SendCustomMessage(playerid, "BUILDER", "You're now editing copied object of %s.", GetStructureNameByModel(FlatStructure[flatid][slot][structModel]));
      }
      case 3: {
        SendCustomMessage(playerid, "BUILDER", "You've destroyed %s", GetStructureNameByModel(FlatStructure[flatid][slot][structModel]));
        FlatStructure_Delete(flatid, slot);
      }
    }
  }
  return 1;
}

Dialog:Dialog_FlatRetexture(playerid, response, listitem, inputtext[]) {
  if (response) {
    new flatid;

    if ((flatid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
      new slot = pData[playerid][pEditStructure];

      new model, color[4];
      new const txdname[32], texture[32];
      if (isnull(inputtext))
        return Dialog_Show(playerid, Dialog_FlatRetexture, DIALOG_STYLE_INPUT, "Retexture Flat Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel"), Error(playerid, "Invalid input!");

      if (sscanf(inputtext, "ds[32]s[32]D(0)D(0)D(0)D(0)",model,txdname,texture,color[0],color[1],color[2],color[3]))
        return Dialog_Show(playerid, Dialog_FlatRetexture, DIALOG_STYLE_INPUT, "Retexture Flat Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel"), Error(playerid, "Invalid input!");
      
      if (!IsValidTexture(texture))
        return Dialog_Show(playerid, Dialog_FlatRetexture, DIALOG_STYLE_INPUT, "Retexture Flat Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel"), Error(playerid, "Invalid texture name!");
      
      if (pData[playerid][pComponent] < 10)
        return Error(playerid, "You need 10 components to retexture the flat structure");
      
      FlatStructure[flatid][slot][structMaterial] = GetTextureIndex(texture);
      FlatStructure[flatid][slot][structColor] = RGBAToInt(color[1], color[2], color[3], color[0]);
      FlatStructure_Refresh(flatid, slot);
      FlatStructure_Save(flatid, slot, true, SAVE_STRUCTURE_MATERIAL);
    }
  }
  return 1;
}

Dialog:Dialog_StaticRetexture(playerid, response, listitem, inputtext[]) {
  if (response) {
    new flatid;

    if ((flatid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
      new slot = pData[playerid][pEditStructure];

      new model, color[4];
      new const txdname[32], texture[32];
      if (isnull(inputtext))
        return Dialog_Show(playerid, Dialog_StaticRetexture, DIALOG_STYLE_INPUT, "Retexture Flat Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel"), Error(playerid, "Invalid input!");

      if (sscanf(inputtext, "ds[32]s[32]D(0)D(0)D(0)D(0)",model,txdname,texture,color[0],color[1],color[2],color[3]))
        return Dialog_Show(playerid, Dialog_StaticRetexture, DIALOG_STYLE_INPUT, "Retexture Flat Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel"), Error(playerid, "Invalid input!");
      
      if (!IsValidTexture(texture))
        return Dialog_Show(playerid, Dialog_StaticRetexture, DIALOG_STYLE_INPUT, "Retexture Flat Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel"), Error(playerid, "Invalid texture name!");
      
      if (pData[playerid][pComponent] < 10)
        return Error(playerid, "You need 10 components to retexture the flat structure");
      
      FlatStaticStruct[flatid][slot][structMaterial] = GetTextureIndex(texture);
      FlatStaticStruct[flatid][slot][structColor] = RGBAToInt(color[1], color[2], color[3], color[0]);
      FlatStructure_Refresh(flatid, slot, false);
      FlatStructure_Save(flatid, slot, false, SAVE_STRUCTURE_MATERIAL);
    }
  }
  return 1;
}

Dialog:Flat_Structures(playerid,response,listitem,inputtext[]) {
  if (!response)
    return callcmd::flatmenu(playerid);

  new flatid;
  if ((flatid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
    switch (listitem) {
      case 0: {
        new str[128];
        strcat(str, "Type\tCost (components)\n");
        format(str, sizeof(str), "Half wall\t25\nFull wall\t50\nFull wall with door\t40\nFull wall with window\t40\nDoor\t20", str);
        Dialog_Show(playerid, Flat_StructureAdd, DIALOG_STYLE_TABLIST_HEADERS, "Flat Structure Modification", str, "Select", "Back");
      }
      case 1: {
        pData[playerid][pEditFlatStructure] = flatid;
        SelectStructureType[playerid] = STRUCTURE_SELECT_EDITOR;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Please select the structure, you wish to move.");
      }
      case 2: {
        pData[playerid][pEditFlatStructure] = flatid;
        SelectStructureType[playerid] = STRUCTURE_SELECT_RETEXTURE;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Please select the structure, you wish to retexture.");
      }
      case 3: {
        pData[playerid][pEditFlatStructure] = flatid;
        SelectStructureType[playerid] = STRUCTURE_SELECT_DELETE;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Please select the structure, you wish to destroy.");
      }
      case 4: {
        pData[playerid][pEditFlatStructure] = flatid;
        SelectStructureType[playerid] = STRUCTURE_SELECT_COPY;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Please select the structure, you wish to copy.");
      }
      case 5: {
        if (!FlatStructure_GetCount(flatid))
          return Error(playerid, "There are no structures in this flat.");

        pData[playerid][pEditFlatStructure] = flatid;
        Dialog_Show(playerid, Dialog_ConfirmDestroy, DIALOG_STYLE_MSGBOX, "Destroy All Structures", RED_E"WARNING:\n"WHITE_E"Are you sure you want to destroy all structures in this flat?", "Yes", "No");
      }
      case 6: {
        Dialog_Show(playerid, Select_FlatStructures, DIALOG_STYLE_LIST, "Flat Structure List", "Static\nCustom", "Select", "Back");
      }
      case 7: {
        pData[playerid][pEditFurnFlat] = flatid;
        SelectFurnitureType[playerid] = FURNITURE_SELECT_MOVE;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Plase select the furniture, you wish to move.");
      }
      case 8: {
        pData[playerid][pEditFurnFlat] = flatid;
        SelectFurnitureType[playerid] = FURNITURE_SELECT_DESTROY;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Plase select the furniture, you wish to destroy.");
      }
      case 9: {
        pData[playerid][pEditFurnFlat] = flatid;
        SelectFurnitureType[playerid] = FURNITURE_SELECT_STORE;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Plase select the furniture, you wish to store.");
      }
      case 10: {
        FlatFurniture_Show(playerid, flatid);
      }
    }
  }
  return 1;
}

Dialog:Dialog_ConfirmDestroy(playerid,response,listitem,inputtext[]) {
  if (!response)
    return Dialog_Show(playerid, Flat_Structures, DIALOG_STYLE_LIST, "Select Flat Structure", "Add structure\nMove structure\nRetexture structure\nDestroy structure\nCopy structure\nDestroy all structure\nStructure list\nMove furniture\nDestroy furniture\nStore furniture\nFurniture list", "Select", "Back");
  
  new flatid = pData[playerid][pEditFlatStructure];

  if (flatid != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
    FlatStructure_DeleteAll(flatid);
    SendCustomMessage(playerid, "BUILDER", "All structures in this flat have been destroyed.");
  }
  return 1;
}

Dialog:Flat_StructureAdd(playerid,response,listitem,inputtext[]) {
  if (!response)
    return callcmd::flatmenu(playerid);

  new flatid;
  if ((flatid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
    static
      Float:x,
      Float:y,
      Float:z,
      Float:angle
    ;

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, angle);

    if (pData[playerid][pComponent] < g_aHouseStructure[listitem][e_StructureCost])
      return Error(playerid, "You need %d component to created %s structure", g_aHouseStructure[listitem][e_StructureCost], g_aHouseStructure[listitem][e_StructureName]);
    
    if (FlatStructure_GetCount(flatid) >= FlatRoom_GetItemsMax(flatid))
      return Error(playerid, "You can only have %d custom structure in your flat.", FlatRoom_GetItemsMax(flatid));
    
    new slot = FlatStructure_Create(flatid, g_aHouseStructure[listitem][e_StructureModel], x+1, y, z, 0.0, 0.0, angle, true);

    if (slot == cellmin)
      return Error(playerid, "You can't create more structure in this flat");
    
    pData[playerid][pComponent] -= g_aHouseStructure[listitem][e_StructureCost];
    pData[playerid][pEditStructure] = slot;
    pData[playerid][pEditFlatStructure] = flatid;
    EditDynamicObject(playerid, FlatStructure[flatid][slot][structObject]);
    SendCustomMessage(playerid, "FLAT", "You've been created "YELLOW_E"%s "WHITE_E"structure for "GREEN_E"%d components", g_aHouseStructure[listitem][e_StructureName], g_aHouseStructure[listitem][e_StructureCost]);
  }
  return 1;
}

Dialog:Select_FlatStructures(playerid,response,listitem,inputtext[]) {
  if (!response)
    return Dialog_Show(playerid, Flat_Structures, DIALOG_STYLE_LIST, "Select Flat Structure", "Add structure\nMove structure\nRetexture structure\nDestroy structure\nCopy structure\nDestroy all structure\nStructure list\nMove furniture\nDestroy furniture\nStore furniture\nFurniture list", "Select", "Back");

  new flatid;
  if ((flatid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
    switch (listitem) {
      case 0: {
        FlatStructure_Show(playerid, flatid, false);
      }
      case 1: {
        FlatStructure_Show(playerid, flatid, true);
      }
    }
  }
  return 1;
}