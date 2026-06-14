
Dialog:Apart_Structures(playerid,response,listitem,inputtext[]) {
  if (!response) return callcmd::suiteroommenu(playerid, "");

  new suiteid;
  if ((suiteid = SuiteRoom_Inside(playerid)) != -1 && (Owner_SuiteRoom(playerid, suiteid))) {
    switch (listitem) {
      case 0: {
        new str[128];
        strcat(str, "Type\tCost (components)\n");
        format(str, sizeof(str), "Half wall\t25\nFull wall\t50\nFull wall with door\t40\nFull wall with window\t40\nDoor\t20", str);
        Dialog_Show(playerid, Apart_StructureAdd, DIALOG_STYLE_TABLIST_HEADERS, "Structure Modification", str, "Select", "Back");
      }
      case 1: {
        EditSuiteStructure[playerid][1] = suiteid;
        SelectSuiteType[playerid] = STRUCTURE_SELECT_EDITOR;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Please select the structure, you wish to move.");
      }
      case 2: {
        EditSuiteStructure[playerid][1] = suiteid;
        SelectSuiteType[playerid] = STRUCTURE_SELECT_RETEXTURE;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Please select the structure, you wish to retexture.");
      }
      case 3: {
        EditSuiteStructure[playerid][1] = suiteid;
        SelectSuiteType[playerid] = STRUCTURE_SELECT_DELETE;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Please select the structure, you wish to destroy.");
      }
      case 4: {
        EditSuiteStructure[playerid][1] = suiteid;
        SelectSuiteType[playerid] = STRUCTURE_SELECT_COPY;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Please select the structure, you wish to copy.");
      }
      case 5: {
        if (!ApartStructure_GetCount(suiteid))
          return Error(playerid, "There are no structures in this suite.");

        EditSuiteStructure[playerid][1] = suiteid;
        Dialog_Show(playerid, Dialog_ApartDestroy, DIALOG_STYLE_MSGBOX, "Destroy All Structures", RED_E"WARNING:\n"WHITE_E"Are you sure you want to destroy all structures in this suiteroom?", "Yes", "No");
      }
      case 6: {
        SuiteStructure_Show(playerid, suiteid);
      }
      case 7: {
        EditSuiteFurniture[playerid][0] = suiteid;
        SelectFurnitureType[playerid] = FURNITURE_SELECT_MOVE;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Plase select the furniture, you wish to move.");
      }
      case 8: {
        EditSuiteFurniture[playerid][0] = suiteid;
        SelectFurnitureType[playerid] = FURNITURE_SELECT_DESTROY;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Plase select the furniture, you wish to destroy.");
      }
      case 9: {
        EditSuiteFurniture[playerid][0] = suiteid;
        SelectFurnitureType[playerid] = FURNITURE_SELECT_STORE;
        SelectObject(playerid);
        SendCustomMessage(playerid, "BUILDER", "Plase select the furniture, you wish to store.");
      }
      case 10: {
        SuiteFurniture_Show(playerid, suiteid);
      }
    }
  }
  return 1;
}

Dialog:Dialog_ApartDestroy(playerid,response,listitem,inputtext[]) {
  if (!response)
    return Dialog_Show(playerid, Apart_Structures, DIALOG_STYLE_LIST, "Select Suite Structure", "Add structure\nMove structure\nRetexture structure\nDestroy structure\nCopy structure\nDestroy all structure\nStructure list\nMove furniture\nDestroy furniture\nStore furniture\nFurniture list", "Select", "Back");

  new suiteid = EditSuiteStructure[playerid][1];
  if(suiteid != -1 && Owner_SuiteRoom(playerid, suiteid)) {
    SuiteStructure_DeleteAll(suiteid);
    SendCustomMessage(playerid, "BUILDER", "All structures in this suiteroom have been destroyed.");
  } 
  return 1;
}

Dialog:Dialog_SuiteCustom(playerid, response, listitem, inputtext[]) {
  if (!response) {
    Dialog_Show(playerid, Apart_Structures, DIALOG_STYLE_LIST, "Select Suite Structure", "Add structure\nMove structure\nRetexture structure\nDestroy structure\nCopy structure\nDestroy all structure\nStructure list\nMove furniture\nDestroy furniture\nStore furniture\nFurniture list", "Select", "Back");
  }
  new suiteid;
  if ((suiteid = SuiteRoom_Inside(playerid)) != -1 && (Owner_SuiteRoom(playerid, suiteid))) {
    new slot = ListedSuiteStructures[playerid][listitem];
    EditSuiteStructure[playerid][0] = slot;
    EditSuiteStructure[playerid][1] = suiteid;
    Dialog_Show(playerid, Dialog_EditSuiteCustom, DIALOG_STYLE_LIST, "Edit Suite Structure", "Move\nRetexture\nCopy\nDestroy", "Select", "Back");
  }
  return 1;
}

Dialog:Dialog_EditSuiteCustom(playerid, response, listitem, inputtext[]) {
  if (!response) {
    Dialog_Show(playerid, Apart_Structures, DIALOG_STYLE_LIST, "Select Suite Structure", "Add structure\nMove structure\nRetexture structure\nDestroy structure\nCopy structure\nDestroy all structure\nStructure list\nMove furniture\nDestroy furniture\nStore furniture\nFurniture list", "Select", "Back");
  }
  new suiteid;
  if ((suiteid = SuiteRoom_Inside(playerid)) != -1 && (Owner_SuiteRoom(playerid, suiteid))) {
    new slot = EditSuiteStructure[playerid][0];

    switch (listitem) {
      case 0: {
        EditSuiteStructure[playerid][1] = suiteid;
        EditDynamicObject(playerid, SuiteStructure[suiteid][slot][suitestructObject]);
        SendCustomMessage(playerid, "BUILDER", "You're now editing %s", GetStructureNameByModel(SuiteStructure[suiteid][slot][suitestructModel]));
      }
      case 1: {
        EditSuiteStructure[playerid][1] = suiteid;
        Dialog_Show(playerid, Dialog_SuiteRetexture, DIALOG_STYLE_INPUT, "Retexture Suite Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel");
      }
      case 2: {
        new price;

        for (new id = 0; id < sizeof(g_aHouseStructure); id ++) if (g_aHouseStructure[id][e_StructureModel] == SuiteStructure[suiteid][slot][suitestructModel]) {
          price = g_aHouseStructure[id][e_StructureCost];
        }

        if (pData[playerid][pComponent] < price)
          return Error(playerid, "You need %d Component(s) to copy this structure.", price);

        new copyId = SuiteStructure_Copy(suiteid, slot);
        if (copyId == cellmin) return Error(playerid, "Your suiteroom has reached maximum of structure");
        
        pData[playerid][pComponent] -= price;
        EditSuiteStructure[playerid][0] = copyId;
        EditSuiteStructure[playerid][1] = suiteid;
        EditDynamicObject(playerid, SuiteStructure[suiteid][copyId][suitestructObject]);
        SendCustomMessage(playerid, "BUILDER", "You have copied structure for "GREEN_E"%d component(s)", price);
        SendCustomMessage(playerid, "BUILDER", "You're now editing copied object of %s.", GetStructureNameByModel(SuiteStructure[suiteid][slot][suitestructModel]));
      }
      case 3: {
        SendCustomMessage(playerid, "BUILDER", "You've destroyed %s", GetStructureNameByModel(SuiteStructure[suiteid][slot][suitestructModel]));
        SuiteStructure_Delete(suiteid, slot);
      }
    }
  }
  return 1;
}

Dialog:Dialog_SuiteRetexture(playerid, response, listitem, inputtext[]) {
    if (response) {
        new suiteid;
        if ((suiteid = SuiteRoom_Inside(playerid)) != -1 && (Owner_SuiteRoom(playerid, suiteid))) {
            new slot = EditSuiteStructure[playerid][0];

            new model, color[4];
            new const txdname[32], texture[32];
            if (isnull(inputtext))
            return Dialog_Show(playerid, Dialog_SuiteRetexture, DIALOG_STYLE_INPUT, "Retexture Suite Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel"), Error(playerid, "Invalid input!");
            if (sscanf(inputtext, "ds[32]s[32]D(0)D(0)D(0)D(0)",model,txdname,texture,color[0],color[1],color[2],color[3]))
            return Dialog_Show(playerid, Dialog_SuiteRetexture, DIALOG_STYLE_INPUT, "Retexture Suite Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel"), Error(playerid, "Invalid input!");
            if (!IsValidTexture(texture))
            return Dialog_Show(playerid, Dialog_SuiteRetexture, DIALOG_STYLE_INPUT, "Retexture Suite Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel"), Error(playerid, "Invalid texture name!");
            if (pData[playerid][pComponent] < 10)
            return Error(playerid, "You need 10 components to retexture the suiteroom structure");
            
            SuiteStructure[suiteid][slot][suitestructMaterial] = GetTextureIndex(texture);
            SuiteStructure[suiteid][slot][suitestructColor] = RGBAToInt(color[1], color[2], color[3], color[0]);
            SuiteStructure_Refresh(suiteid, slot);
            ApartStructure_Save(suiteid, slot, SAVE_STRUCTURE_MATERIAL);
        }
    }
    return 1;
}

Dialog:Apart_StructureAdd(playerid,response,listitem,inputtext[]) {
  if (!response)
    return callcmd::suiteroommenu(playerid, "");

  new suiteid;
  if ((suiteid = SuiteRoom_Inside(playerid)) != -1 && (Owner_SuiteRoom(playerid, suiteid))) {
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
    
    if (ApartStructure_GetCount(suiteid) >= 200)
      return Error(playerid, "You can only have 200 custom structure in your suiteroom.");
    
    new slot = ApartStructure_Create(suiteid, g_aHouseStructure[listitem][e_StructureModel], x+1, y, z, 0.0, 0.0, angle);

    if (slot == cellmin) return Error(playerid, "You can't create more structure in this suiteroom");
    
    pData[playerid][pComponent] -= g_aHouseStructure[listitem][e_StructureCost];
    EditSuiteStructure[playerid][0] = slot;
    EditSuiteStructure[playerid][1] = suiteid;
    EditDynamicObject(playerid, SuiteStructure[suiteid][slot][suitestructObject]);
    SendCustomMessage(playerid, "SUITEROOM", "You've been created "YELLOW_E"%s "WHITE_E"structure for "GREEN_E"%d components", g_aHouseStructure[listitem][e_StructureName], g_aHouseStructure[listitem][e_StructureCost]);
  }
  return 1;
}
