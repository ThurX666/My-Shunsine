
Dialog:Dialog_FlatMenu(playerid,response,listitem,inputtext[]) {
  new flatid;

  if ((flatid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
    if (response) {
      switch (listitem) {
        case 0: {
          callcmd::flock(playerid);
          callcmd::flatmenu(playerid);
        }
        case 1: {
          if (FlatRoom_IsBuilder(playerid, flatid))
            return Error(playerid, "Access denied");

          Flat_OpenStorage(playerid, flatid);
        }
        case 2: {
          if (FlatRoom_IsBuilder(playerid, flatid))
            return Error(playerid, "Access denied");

          FlatFurniture_Show(playerid, flatid);
        }
        case 3: {
          if (pData[playerid][pJob] != 9 && pData[playerid][pJob2] != 9)
            return Error(playerid, "You're not a Builder");

          Dialog_Show(playerid, Flat_Structures, DIALOG_STYLE_LIST, "Select Flat Structure", "Add structure\nMove structure\nRetexture structure\nDestroy structure\nCopy structure\nDestroy all structure\nStructure list\nMove furniture\nDestroy furniture\nStore furniture\nFurniture list", "Select", "Back");
        }
        case 4: {
          if (FlatRoom_IsBuilder(playerid, flatid))
            return Error(playerid, "Access denied");

          if (!FlatRoom[flatid][flatRoomBuilder])
            Dialog_Show(playerid, Flat_AssignBuilder, DIALOG_STYLE_INPUT, "Assign Builder", "Enter player id or name to assign", "Assign", "Back");
          else
            Dialog_Show(playerid, Flat_UnassignBuilder, DIALOG_STYLE_MSGBOX, "Unassign Builder", WHITE_E"Your flat is already assigned a Builder the contract will be expire on "GREEN_E"%s"WHITE_E", do you want to fired them?", "Yes", "Back", experieddate(FlatRoom[flatid][flatRoomBuilderTime],3));
        }
      }
    }
  }
  return 1;
}

Dialog:Flat_AssignBuilder(playerid,response,listitem,inputtext[]) {
  if (!response) callcmd::flatmenu(playerid);
  else {
    new flatid;
    if ((flatid = FlatRoom_Inside(playerid)) != -1 && FlatRoom_IsOwner(playerid, flatid)) {
      new userid;
      if (isnull(inputtext))
        return Dialog_Show(playerid, Flat_AssignBuilder, DIALOG_STYLE_INPUT, "Assign Builder", "Enter player id or name to assign", "Assign", "Back"), Error(playerid, "Invalid input!");

      if (sscanf(inputtext, "u", userid))
        return Dialog_Show(playerid, Flat_AssignBuilder, DIALOG_STYLE_INPUT, "Assign Builder", "Enter player id or name to assign", "Assign", "Back"), Error(playerid, "Invalid input!");

      if (!IsPlayerConnected(userid))
        return Error(playerid, "Invalid playerid or name!");

      if (userid == playerid)
        return Error(playerid, "Cannot assign yourself");

      if (pData[playerid][pJob] != 9 && pData[playerid][pJob2] != 9)
        return Error(playerid, "That player are not a Bulder");

      FlatRoom[flatid][flatRoomBuilder] = pData[userid][pID];
      FlatRoom[flatid][flatRoomBuilderTime] = (gettime()+((24*3600)*7));
      SendCustomMessage(playerid, "FLAT", "You've been assigned "YELLOW_E"%s "WHITE_E"as your flat builder, it will automatically fired for 7 days.", ReturnName(userid));
      SendCustomMessage(userid, "FLAT", ""YELLOW_E"%s "WHITE_E"has assigned you as flat builder.", ReturnName(playerid));
    }
  }
  return 1;
}

Dialog:Flat_UnassignBuilder(playerid,response,listitem,inputtext[]) {
  if (!response) callcmd::flatmenu(playerid);
  else {
    new flatid;
    if ((flatid = FlatRoom_Inside(playerid)) != -1 && FlatRoom_IsOwner(playerid, flatid)) {
      FlatRoom[flatid][flatRoomBuilder] = 0;
      FlatRoom[flatid][flatRoomBuilderTime] = 0;
      SendCustomMessage(playerid, "FLAT", "You've been unassigned your flat builder");
    }
  }
  return 1;
}

Dialog:Flat_EditStatic(playerid,response,listitem,inputtext[]) {
  if (response) {
    new flatid;
    if ((flatid = FlatRoom_Inside(playerid)) != -1) {
      new slot = ListedFlatStructures[playerid][listitem],
        info[512];
      
      pData[playerid][pEditFlatStructure] = flatid;
      pData[playerid][pEditStaticStructure] = slot;

      format(info, sizeof(info), "Model\t%d\n", FlatStaticStruct[flatid][slot][structModel]);
      format(info, sizeof(info), "%sPos X\t%.2f\n", info, FlatStaticStruct[flatid][slot][structPos][0]);
      format(info, sizeof(info), "%sPos Y\t%.2f\n", info, FlatStaticStruct[flatid][slot][structPos][1]);
      format(info, sizeof(info), "%sPos Z\t%.2f\n", info, FlatStaticStruct[flatid][slot][structPos][2]);
      format(info, sizeof(info), "%sRot X\t%.2f\n", info, FlatStaticStruct[flatid][slot][structRot][0]);
      format(info, sizeof(info), "%sRot Y\t%.2f\n", info, FlatStaticStruct[flatid][slot][structRot][1]);
      format(info, sizeof(info), "%sRot Z\t%.2f\n", info, FlatStaticStruct[flatid][slot][structRot][2]);
      format(info, sizeof(info), "%sOpen editor\t\n", info);
      format(info, sizeof(info), "%sDestroy\t", info);
      Dialog_Show(playerid, Flat_EditPage, DIALOG_STYLE_TABLIST, "Edit Static Flat", info, "Edit", "Close");
    }
  }
  return 1;
}

Dialog:Flat_EditPage(playerid,response,listitem,inputtext[]) {
  if (response) {
    SetPVarInt(playerid, "StaticStructUpdate", listitem);

    switch (listitem) {
      case 0: {
        Dialog_Show(playerid, Flat_StructureUpdate, DIALOG_STYLE_INPUT, "Edit Model", "Input new model id: "GREEN_E"(input below)", "Update", "Close");
      }
      case 1: {
        Dialog_Show(playerid, Flat_StructureUpdate, DIALOG_STYLE_INPUT, "Edit Pos X", "Input new Pos X: "GREEN_E"(input below)", "Update", "Close");
      }
      case 2: {
        Dialog_Show(playerid, Flat_StructureUpdate, DIALOG_STYLE_INPUT, "Edit Pos Y", "Input new Pos Y: "GREEN_E"(input below)", "Update", "Close");
      }
      case 3: {
        Dialog_Show(playerid, Flat_StructureUpdate, DIALOG_STYLE_INPUT, "Edit Pos Z", "Input new Pos Z: "GREEN_E"(input below)", "Update", "Close");
      }
      case 4: {
        Dialog_Show(playerid, Flat_StructureUpdate, DIALOG_STYLE_INPUT, "Edit Rot X", "Input new Rot X: "GREEN_E"(input below)", "Update", "Close");
      }
      case 5: {
        Dialog_Show(playerid, Flat_StructureUpdate, DIALOG_STYLE_INPUT, "Edit Rot Y", "Input new Rot Y: "GREEN_E"(input below)", "Update", "Close");
      }
      case 6: {
        Dialog_Show(playerid, Flat_StructureUpdate, DIALOG_STYLE_INPUT, "Edit Rot z", "Input new Rot z: "GREEN_E"(input below)", "Update", "Close");
      }
      case 7: {
        new flatid = pData[playerid][pEditFlatStructure],
          slot = pData[playerid][pEditStaticStructure];
        
        EditDynamicObject(playerid, FlatStaticStruct[flatid][slot][structObject]);
        SendCustomMessage(playerid, "FLAT", "You're now editing static structure "YELLOW_E"%d "WHITE_E"for flat ID: "YELLOW_E"%d", slot, flatid);
      }
      case 8: {
        new flatid = pData[playerid][pEditFlatStructure],
          slot = pData[playerid][pEditStaticStructure];
        
        SendCustomMessage(playerid, "FLAT", "You've deleted static structure "YELLOW_E"%d "WHITE_E"flat ID: "YELLOW_E"%d", slot, flatid);
        FlatStructure_Delete(flatid, slot, false);
      }
    }
  }
  return 1;
}

Dialog:Flat_StructureUpdate(playerid,response,listitem,inputtext[]) {
  if (response) {
    new index = GetPVarInt(playerid, "StaticStructUpdate"),
      flatid = pData[playerid][pEditFlatStructure],
      slot = pData[playerid][pEditStaticStructure];
    
    if (!Iter_Contains(FlatStaticStructs[flatid], slot))
      return Error(playerid, "Invalid structure ID");

    switch (index) {
      case 0: {
        new model;
        if (sscanf(inputtext, "d", model))
          return Error(playerid, "Invalid input"), DeletePVar(playerid, "StaticStructUpdate");

        FlatStaticStruct[flatid][slot][structModel] = model;
        FlatStructure_Refresh(flatid, slot, false);
        FlatStructure_Save(flatid, slot, false, SAVE_STRUCTURE_MODEL);
        SendCustomMessage(playerid, "FLAT", "You've been changed model id of static structure ID: "YELLOW_E"%d "WHITE_E"to "YELLOW_E"%d", slot, model);
        DeletePVar(playerid, "StaticStructUpdate");
      }
      case 1: {
        new Float:pos;
        if (sscanf(inputtext, "f", pos))
          return Error(playerid, "Invalid input"), DeletePVar(playerid, "StaticStructUpdate");

        FlatStaticStruct[flatid][slot][structPos][0] = pos;
        FlatStructure_Refresh(flatid, slot, false);
        FlatStructure_Save(flatid, slot, false, SAVE_STRUCTURE_POS);
        SendCustomMessage(playerid, "FLAT", "You've been changed Pos X of static structure ID: "YELLOW_E"%d "WHITE_E"to "YELLOW_E"%.2f", slot, pos);
        DeletePVar(playerid, "StaticStructUpdate");
      }
      case 2: {
        new Float:pos;
        if (sscanf(inputtext, "f", pos))
          return Error(playerid, "Invalid input"), DeletePVar(playerid, "StaticStructUpdate");

        FlatStaticStruct[flatid][slot][structPos][1] = pos;
        FlatStructure_Refresh(flatid, slot, false);
        FlatStructure_Save(flatid, slot, false, SAVE_STRUCTURE_POS);
        SendCustomMessage(playerid, "FLAT", "You've been changed Pos Y of static structure ID: "YELLOW_E"%d "WHITE_E"to "YELLOW_E"%.2f", slot, pos);
        DeletePVar(playerid, "StaticStructUpdate");
      }
      case 3: {
        new Float:pos;
        if (sscanf(inputtext, "f", pos))
          return Error(playerid, "Invalid input"), DeletePVar(playerid, "StaticStructUpdate");

        FlatStaticStruct[flatid][slot][structPos][2] = pos;
        FlatStructure_Refresh(flatid, slot, false);
        FlatStructure_Save(flatid, slot, false, SAVE_STRUCTURE_POS);
        SendCustomMessage(playerid, "FLAT", "You've been changed Pos Z of static structure ID: "YELLOW_E"%d "WHITE_E"to "YELLOW_E"%.2f", slot, pos);
        DeletePVar(playerid, "StaticStructUpdate");
      }
      case 4: {
        new Float:pos;
        if (sscanf(inputtext, "f", pos))
          return Error(playerid, "Invalid input"), DeletePVar(playerid, "StaticStructUpdate");

        FlatStaticStruct[flatid][slot][structRot][0] = pos;
        FlatStructure_Refresh(flatid, slot, false);
        FlatStructure_Save(flatid, slot, false, SAVE_STRUCTURE_POS);
        SendCustomMessage(playerid, "FLAT", "You've been changed Rot X of static structure ID: "YELLOW_E"%d "WHITE_E"to "YELLOW_E"%.2f", slot, pos);
        DeletePVar(playerid, "StaticStructUpdate");
      }
      case 5: {
        new Float:pos;
        if (sscanf(inputtext, "f", pos))
          return Error(playerid, "Invalid input"), DeletePVar(playerid, "StaticStructUpdate");

        FlatStaticStruct[flatid][slot][structRot][1] = pos;
        FlatStructure_Refresh(flatid, slot, false);
        FlatStructure_Save(flatid, slot, false, SAVE_STRUCTURE_POS);
        SendCustomMessage(playerid, "FLAT", "You've been changed Rot Y of static structure ID: "YELLOW_E"%d "WHITE_E"to "YELLOW_E"%.2f", slot, pos);
        DeletePVar(playerid, "StaticStructUpdate");
      }
      case 6: {
        new Float:pos;
        if (sscanf(inputtext, "f", pos))
          return Error(playerid, "Invalid input"), DeletePVar(playerid, "StaticStructUpdate");

        FlatStaticStruct[flatid][slot][structRot][2] = pos;
        FlatStructure_Refresh(flatid, slot, false);
        FlatStructure_Save(flatid, slot, false, SAVE_STRUCTURE_POS);
        SendCustomMessage(playerid, "FLAT", "You've been changed Rot Z of static structure ID: "YELLOW_E"%d "WHITE_E"to "YELLOW_E"%.2f", slot, pos);
        DeletePVar(playerid, "StaticStructUpdate");
      }
    }
  }
  return 1;
}

Dialog:ListedFlatFurniture(playerid, response, listitem, inputtext[]) {
  if(response) {
    new flatid = FlatRoom_Inside(playerid);

    if (flatid == -1)
      return Error(playerid, "You're not inside a flat.");
    
    if (!FlatRoom_IsOwner(playerid, flatid) && !FlatRoom_IsBuilder(playerid, flatid))
      return Error(playerid, "You're not the owner or builder of this flat");
    
    pData[playerid][pEditFurniture] = ListedFlatFurnitures[playerid][listitem];
    pData[playerid][pEditFurnFlat] = flatid;
    Dialog_Show(playerid, FlatFurnitureSelect, DIALOG_STYLE_LIST, FlatFurniture[flatid][pData[playerid][pEditFurniture]][furnName], "Edit Position\nMove to in front me\nDestroy Furniture\nStore Furniture", "Select", "Cancel");
  }
  return 1;
}

Dialog:FlatFurnitureSelect(playerid, response, listitem, inputtext[]) {
  if(response) {
    new flatid = FlatRoom_Inside(playerid);
    
    if (flatid != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
      new Float:pos[4];
      GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
      GetPlayerFacingAngle(playerid, pos[3]);

      pos[0] += 1.0 * floatsin(-pos[3], degrees);
      pos[1] += 1.0 * floatcos(-pos[3], degrees);

      switch (listitem) {
        case 0: {
          new slot = pData[playerid][pEditFurniture];

          if (FlatFurniture[flatid][slot][furnUnused]) {
            FlatFurniture[flatid][slot][furnUnused] = 0;
            FlatFurniture[flatid][slot][furnPos][0] = pos[0];
            FlatFurniture[flatid][slot][furnPos][1] = pos[1];
            FlatFurniture[flatid][slot][furnPos][2] = pos[2];
            FlatFurniture[flatid][slot][furnRot][0] = 0.0;
            FlatFurniture[flatid][slot][furnRot][1] = 0.0;
            FlatFurniture[flatid][slot][furnRot][2] = pos[3];

            FlatFurniture_Refresh(slot, flatid);
          }
          EditDynamicObject(playerid, FlatFurniture[flatid][slot][furnObject]);
          SendCustomMessage(playerid, "FURNITURE", "You are now editing the position of \"%s"WHITE_E"\".", FlatFurniture[flatid][slot][furnName]);
        }
        case 1: {
          new slot = pData[playerid][pEditFurniture];

          if(FlatFurniture[flatid][slot][furnUnused])
            return Error(playerid, "Attach this furniture first by select option \"Editing Position\"");

          FlatFurniture[flatid][slot][furnUnused] = 0;
          FlatFurniture[flatid][slot][furnPos][0] = pos[0];
          FlatFurniture[flatid][slot][furnPos][1] = pos[1];
          FlatFurniture[flatid][slot][furnPos][2] = pos[2];
          FlatFurniture[flatid][slot][furnRot][0] = 0.0;
          FlatFurniture[flatid][slot][furnRot][1] = 0.0;
          FlatFurniture[flatid][slot][furnRot][2] = pos[3];

          SetDynamicObjectPos(FlatFurniture[flatid][slot][furnObject], FlatFurniture[flatid][slot][furnPos][0], FlatFurniture[flatid][slot][furnPos][1], FlatFurniture[flatid][slot][furnPos][2]);
          SetDynamicObjectRot(FlatFurniture[flatid][slot][furnObject], FlatFurniture[flatid][slot][furnRot][0], FlatFurniture[flatid][slot][furnRot][1], FlatFurniture[flatid][slot][furnRot][2]);
          FlatFurniture_Refresh(slot, flatid);
          FlatFurniture_Save(slot, flatid);
          SendCustomMessage(playerid, "FURNITURE", "Now this furniture is moved to in front you.");
        }
        case 2: {
          SendCustomMessage(playerid, "FURNITURE", "You have destroyed furniture \"%s"WHITE_E"\".", FlatFurniture[flatid][pData[playerid][pEditFurniture]][furnName]);
          FlatFurniture_Delete(pData[playerid][pEditFurniture], flatid);

          CancelEdit(playerid);
          pData[playerid][pEditFurniture] = -1;
          pData[playerid][pEditFurnFlat] = -1;
        }
        case 3: {
          new slot = pData[playerid][pEditFurniture];

          if (FlatFurniture[flatid][slot][furnUnused])
            return Error(playerid, "This furniture already stored.");
          
          FlatFurniture[flatid][slot][furnUnused] = 1;
          FlatFurniture_Refresh(slot, flatid);
          FlatFurniture_Save(slot, flatid);
          SendCustomMessage(playerid, "FURNITURE", "You have stored furniture \"%s"WHITE_E"\" into your flat.", FlatFurniture[flatid][slot][furnName]);
          pData[playerid][pEditFurniture] = -1;
          pData[playerid][pEditFurnFlat] = -1;
        }
      }
    } else {
      pData[playerid][pEditFurniture] = -1;
      pData[playerid][pEditFurnFlat] = -1;
      return 1;
    }
  } else FlatFurniture_Show(playerid, pData[playerid][pEditFurnFlat]);
  return 1;
}

// Dialogs
Dialog:FlatWeapons(playerid, response, listitem, inputtext[]) {
  new
    roomid;

  if((roomid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, roomid) || pData[playerid][pAdmin] > 5))
  {
    if(response)
    {
      if(FlatRoom[roomid][flatRoomWeapon][listitem] != 0)
      {
        if(pData[playerid][pOnDuty] > 1)
          return Error(playerid, "Duty faction tidak dapat mengambil senjata.");

        if(PlayerHasWeapon(playerid, FlatRoom[roomid][flatRoomWeapon][listitem]))
          return Error(playerid, "Kamu sudah memiliki senjata yang sama.");
        switch(FlatRoom[roomid][flatRoomTypeAmmo][listitem]) {
          case 0: {
            GivePlayerWeaponEx(playerid, FlatRoom[roomid][flatRoomWeapon][listitem], FlatRoom[roomid][flatRoomAmmo][listitem], 0);
          }
          case 1: {
            GivePlayerWeaponEx(playerid, FlatRoom[roomid][flatRoomWeapon][listitem], FlatRoom[roomid][flatRoomAmmo][listitem], 1);
          }
        }
        SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "** %s has taken a \"%s\" from their weapon storage.", ReturnName(playerid), ReturnWeaponName(FlatRoom[roomid][flatRoomWeapon][listitem]));

        new query[128];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `flat_weapon` WHERE `flatroomid` = '%d' AND `ammo`='%d' AND `weaponid`='%d' AND `durability`='%d'", FlatRoom[roomid][flatRoomID], FlatRoom[roomid][flatRoomAmmo][listitem], FlatRoom[roomid][flatRoomWeapon][listitem], FlatRoom[roomid][flatRoomDurability][listitem]);
        mysql_tquery(g_SQL, query);
        FlatRoom[roomid][flatRoomWeapon][listitem]      = 0;
        FlatRoom[roomid][flatRoomAmmo][listitem]         = 0;
        FlatRoom[roomid][flatRoomDurability][listitem]   = 0;
        FlatRoom[roomid][flatRoomTypeAmmo][listitem]     = 0;
        
        Flat_WeaponStorage(playerid, roomid);
      }
      else
      {
        new
          weaponid = GetWeapon(playerid),
          ammo = ReturnWeaponAmmo(playerid, weaponid);

        if(pData[playerid][pOnDuty] > 1)
            return Error(playerid, "Duty faction tidak dapat menyimpan senjata.");

        if(!weaponid)
            return Error(playerid, "You are not holding any weapon!");
        if(PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_typesurplus] == 2) return Error(playerid, "Senjata bertype JHP tidak bisa disimpan di flat!");
        FlatRoom[roomid][flatRoomWeapon][listitem] = weaponid;
        FlatRoom[roomid][flatRoomAmmo][listitem] = ammo;
        switch(PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_typesurplus]) {
          case 0: {
            FlatRoom[roomid][flatRoomTypeAmmo][listitem]     = 0;
          }
          case 1: {
            FlatRoom[roomid][flatRoomTypeAmmo][listitem]     = 1;
          }
        }
        new string[212];
        mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `flat_weapon` (`flatroomid`, `weaponid`, `ammo`, `typeammo`) VALUES ('%d','%d','%d','%d')", FlatRoom[roomid][flatRoomID], weaponid, ammo, FlatRoom[roomid][flatRoomTypeAmmo][listitem]);
        mysql_tquery(g_SQL, string);
        
        ResetWeaponID(playerid, weaponid);
        Flat_WeaponStorage(playerid, roomid);
        
        SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their weapon storage.", ReturnName(playerid), ReturnWeaponName(weaponid));
      }
    }
    else Flat_OpenStorage(playerid, roomid);
  }
  return 1;
}

// Dialog:FlatTake(playerid, response, listitem, inputtext[]) {
//   new
//     roomid,
//     string[32];

//   if((roomid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, roomid) || pData[playerid][pAdmin] > 5))
//   {
//     strunpack(string, FlatStorage[roomid][pData[playerid][pStorageItem]][rItemName]);

//     if(response)
//     {
//       new amount = strval(inputtext);

//       if(amount < 1 || amount > FlatStorage[roomid][pData[playerid][pStorageItem]][rItemQuantity])
//         return Dialog_Show(playerid, FlatTake, DIALOG_STYLE_INPUT, "Flat Take", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to take for this item:", "Take", "Back", string, FlatStorage[roomid][pData[playerid][pInventoryItem]][rItemQuantity]);

//       for (new i = 0; i < sizeof(g_aInventoryItems); i ++) if(!strcmp(g_aInventoryItems[i][e_InventoryItem], string, true)) {
//         if((Inventory_Count(playerid, g_aInventoryItems[i][e_InventoryItem])+amount) > g_aInventoryItems[i][e_InventoryMax])
//           return Dialog_Show(playerid, FlatTake, DIALOG_STYLE_INPUT, "Flat Take", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to take for this item:\n(You can take %d %s now!)", "Take", "Back", string, FlatStorage[roomid][pData[playerid][pInventoryItem]][rItemQuantity], (g_aInventoryItems[i][e_InventoryMax]-Inventory_Count(playerid, g_aInventoryItems[i][e_InventoryItem])), string);
//       }

//       new id = Inventory_Add(playerid, string, FlatStorage[roomid][pData[playerid][pStorageItem]][rItemModel], amount);

//       if(id == -1)
//           return Error(playerid, "You don't have any inventory slots left.");

//       Flat_RemoveItem(roomid, string, amount);
//       SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "** %s has taken a \"%s\" from their room storage.", ReturnName(playerid), string);

//       Flat_ShowItems(playerid, roomid);
//     }
//     else Flat_OpenStorage(playerid, roomid);
//   }
//   return 1;
// }

Dialog:Dialog_FlatStorage(playerid, response, listitem, inputtext[]) {
  new
    roomid = -1;

  if((roomid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, roomid) || pData[playerid][pAdmin] >= 3))
  {
    if(response)
    {
      if(listitem == 0) {
        Flat_ShowItems(playerid, roomid);
      }
      else if(listitem == 1) {
        if(pData[playerid][pLevel] < 2)
          return Error(playerid, "You're not allowed to access this storage if you're not level 2.");

        if (!pData[playerid][pCS])
          return Error(playerid, "You must have an active character story to access this option.");

        Flat_WeaponStorage(playerid, roomid);
      }
      else if(listitem == 2) {
        Dialog_Show(playerid, FlatMoney, DIALOG_STYLE_LIST, "Money Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
      }
    }
  }
  return 1;
}

// Dialog:Dialog_FlatItems(playerid, response, listitem, inputtext[]) {
//   new
//     roomid,
//     string[64];

//   if((roomid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, roomid) || pData[playerid][pAdmin] > 5))
//   {
//     if(response)
//     {
//       if(Iter_Contains(FlatStorages[roomid], listitem))
//       {
//         pData[playerid][pStorageItem] = listitem;
//         pData[playerid][pInventoryItem] = listitem;

//         strunpack(string, FlatStorage[roomid][listitem][rItemName]);

//         format(string, sizeof(string), "%s (Quantity: %d)", string, FlatStorage[roomid][listitem][rItemQuantity]);
//         Dialog_Show(playerid, Flat_StorageOptions, DIALOG_STYLE_LIST, string, "Take Item\nStore Item", "Select", "Back");
//       }
//       else {
//         OpenInventory(playerid);

//         pData[playerid][pStorageSelect] = 5;
//       }
//     }
//     else Flat_OpenStorage(playerid, roomid);
//   }
//   return 1;
// }

// Dialog:Flat_StorageOptions(playerid, response, listitem, inputtext[]) {
//   new
//     roomid = -1,
//     itemid = -1,
//     string[32];

//   if((roomid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, roomid) || pData[playerid][pAdmin] >= 3))
//   {
//     itemid = pData[playerid][pStorageItem];

//     strunpack(string, FlatStorage[roomid][itemid][rItemName]);

//     if(response)
//     {
//       switch (listitem)
//       {
//         case 0:
//         {
//           if(FlatStorage[roomid][itemid][rItemQuantity] == 1)
//           {
//             if(!strcmp(string, "Backpack") && Inventory_HasItem(playerid, "Backpack"))
//               return Error(playerid, "You already have a backpack in your inventory.");

//             for (new i = 0; i < sizeof(g_aInventoryItems); i ++) if(!strcmp(g_aInventoryItems[i][e_InventoryItem], string, true)) {
//               if((Inventory_Count(playerid, g_aInventoryItems[i][e_InventoryItem])+1) > g_aInventoryItems[i][e_InventoryMax])
//                 return Error(playerid, "You're limited %d for %s.", g_aInventoryItems[i][e_InventoryMax], string);
//             }

//             new id = Inventory_Add(playerid, string, FlatStorage[roomid][itemid][rItemModel], 1);

//             if(id == -1)
//               return Error(playerid, "You don't have any inventory slots left.");

//             Flat_RemoveItem(roomid, string);
//             SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "** %s has taken a \"%s\" from their room storage.", ReturnName(playerid), string);

//             Flat_ShowItems(playerid, roomid);
//             Log_Write("logs/storage_log.txt", "[%s] %s has taken \"%s\" from room ID: %d.", ReturnDate(), ReturnName(playerid), string, roomid);
//           }
//           else
//           {
//             Dialog_Show(playerid, FlatTake, DIALOG_STYLE_INPUT, "Flat Take", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to take for this item:", "Take", "Back", string, FlatStorage[roomid][itemid][rItemQuantity]);
//           }
//         }
//         case 1:
//         {
//           new id = Inventory_GetItemID(playerid, string);

//           if(!strcmp(string, "Backpack")) {
//             Flat_ShowItems(playerid, roomid);

//             return Error(playerid, "You can only store one backpack in your room.");
//           }
//           else if(id == -1) {
//             Flat_ShowItems(playerid, roomid);

//             return Error(playerid, "You don't have anymore of this item to store!");
//           }
//           else if(InventoryData[playerid][id][invQuantity] == 1)
//           {
//             Flat_AddItem(roomid, string, InventoryData[playerid][id][invModel]);
//             Inventory_Remove(playerid, string);

//             SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their room storage.", ReturnName(playerid), string);
//             Log_Write("logs/storage_log.txt", "[%s] %s has stored \"%s\" into their room ID: %d.", ReturnDate(), ReturnName(playerid), string, roomid);
//             Flat_ShowItems(playerid, roomid);
//           }
//           else if(InventoryData[playerid][id][invQuantity] > 1) {
//             pData[playerid][pInventoryItem] = id;

//             Dialog_Show(playerid, FlatDeposit, DIALOG_STYLE_INPUT, "Flat Deposit", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", "Store", "Back", string, InventoryData[playerid][id][invQuantity]);
//           }
//         }
//       }
//     }
//     else
//     {
//       Flat_ShowItems(playerid, roomid);
//     }
//   }
//   return 1;
// }

// Dialog:FlatDeposit(playerid, response, listitem, inputtext[]) {
//   new
//     roomid,
//     string[32];

//   if((roomid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, roomid)))
//   {
//     strunpack(string, InventoryData[playerid][pData[playerid][pInventoryItem]][invItem]);

//     if(response)
//     {
//       new amount = strval(inputtext);

//       if(amount < 1 || amount > InventoryData[playerid][pData[playerid][pInventoryItem]][invQuantity])
//         return Dialog_Show(playerid, FlatDeposit, DIALOG_STYLE_INPUT, "Flat Deposit", "Item: %s (Quantity: %d)\n\nPlease enter the quantity that you wish to store for this item:", "Store", "Back", string, InventoryData[playerid][pData[playerid][pInventoryItem]][invQuantity]);

//       Flat_AddItem(roomid, string, InventoryData[playerid][pData[playerid][pInventoryItem]][invModel], amount);
//       Inventory_Remove(playerid, string, amount);

//       SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their room storage.", ReturnName(playerid), string);
//       Log_Write("logs/storage_log.txt", "[%s] %s has stored \"%s\" (%d) into their room ID: %d.", ReturnDate(), ReturnName(playerid), string, amount, roomid);

//       Flat_ShowItems(playerid, roomid);
//     }
//     else Flat_OpenStorage(playerid, roomid);
//   }	
//   return 1;
// }

Dialog:FlatMoney(playerid, response, listitem, inputtext[]) {
  new
    roomid;

  if((roomid = FlatRoom_Inside(playerid)) != -1 && FlatRoom_IsOwner(playerid, roomid) || pData[playerid][pAdmin] > 5)
  {
    if(response)
    {
      switch (listitem)
      {
        case 0: Dialog_Show(playerid, FlatWithdrawCash, DIALOG_STYLE_INPUT, "Withdraw from safe", "Safe Balance: %s\n\nPlease enter how much money you wish to withdraw from the safe:", "Withdraw", "Back", FormatMoney(FlatRoom[roomid][flatRoomMoney]));
        case 1: Dialog_Show(playerid, FlatDepositCash, DIALOG_STYLE_INPUT, "Deposit into safe", "Safe Balance: %s\n\nPlease enter how much money you wish to deposit into the safe:", "Deposit", "Back", FormatMoney(FlatRoom[roomid][flatRoomMoney]));
      }
    }
    else Flat_OpenStorage(playerid, roomid);
  }
  return 1;
}

Dialog:FlatWithdrawCash(playerid, response, listitem, inputtext[]) {
  new
    roomid;

  if((roomid = FlatRoom_Inside(playerid)) != -1 && (FlatRoom_IsOwner(playerid, roomid) || pData[playerid][pAdmin] > 5))
  {
    if(response)
    {
      new amount = strval(inputtext);

      if(isnull(inputtext))
        return Dialog_Show(playerid, FlatWithdrawCash, DIALOG_STYLE_INPUT, "Withdraw from safe", "Safe Balance: %s\n\nPlease enter how much money you wish to withdraw from the safe:", "Withdraw", "Back", FormatMoney(FlatRoom[roomid][flatRoomMoney]));

      if(amount < 1 || amount > FlatRoom[roomid][flatRoomMoney])
        return Dialog_Show(playerid, FlatWithdrawCash, DIALOG_STYLE_INPUT, "Withdraw from safe", "Error: Insufficient funds.\n\nSafe Balance: %s\n\nPlease enter how much money you wish to withdraw from the safe:", "Withdraw", "Back", FormatMoney(FlatRoom[roomid][flatRoomMoney]));

      FlatRoom[roomid][flatRoomMoney] -= amount;
      GivePlayerMoneyEx(playerid, amount);

      FlatRoom_Save(roomid);
      Flat_OpenStorage(playerid, roomid);

      SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "** %s has withdrawn %s from their room safe.", ReturnName(playerid), FormatMoney(amount));
    }
    else Dialog_Show(playerid, FlatMoney, DIALOG_STYLE_LIST, "Money Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
  }
  return 1;
}

Dialog:FlatDepositCash(playerid, response, listitem, inputtext[]) {
  new
    roomid;

  if((roomid = FlatRoom_Inside(playerid)) != -1 && FlatRoom_IsOwner(playerid, roomid))
  {
    if(response)
    {
      new amount = strval(inputtext);

      if(isnull(inputtext))
        return Dialog_Show(playerid, FlatDepositCash, DIALOG_STYLE_INPUT, "Deposit into safe", "Safe Balance: %s\n\nPlease enter how much money you wish to deposit into the safe:", "Deposit", "Back", FormatMoney(FlatRoom[roomid][flatRoomMoney]));

      if(amount < 1 || amount > GetPlayerMoney(playerid))
        return Dialog_Show(playerid, FlatDepositCash, DIALOG_STYLE_INPUT, "Deposit into safe", "Error: Insufficient funds.\n\nSafe Balance: %s\n\nPlease enter how much money you wish to deposit into the safe:", "Deposit", "Back", FormatMoney(FlatRoom[roomid][flatRoomMoney]));

      FlatRoom[roomid][flatRoomMoney] += amount;
      GivePlayerMoneyEx(playerid, -amount);

      FlatRoom_Save(roomid);
      Flat_OpenStorage(playerid, roomid);

      SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "** %s has deposited %s into their room safe.", ReturnName(playerid), FormatMoney(amount));
    }
    else Dialog_Show(playerid, FlatMoney, DIALOG_STYLE_LIST, "Money Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
  }
  return 1;
}