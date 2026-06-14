
Dialog:ListedSuiteFurniture(playerid, response, listitem, inputtext[]) {
  if(response) {
    new suiteid = SuiteRoom_Inside(playerid);
    if (suiteid == -1) return Error(playerid, "You're not inside a suite.");
    if (!Owner_SuiteRoom(playerid, suiteid)) return Error(playerid, "You're not the owner or builder of this suite room");
    
    EditSuiteFurniture[playerid][1] = ListedSuiteFurnitures[playerid][listitem];
    EditSuiteFurniture[playerid][0] = suiteid;
    Dialog_Show(playerid, SuiteFurnitureSelect, DIALOG_STYLE_LIST, SuiteFurniture[suiteid][EditSuiteFurniture[playerid][1]][suitefurnName], "Edit Position\nMove to in front me\nDestroy Furniture\nStore Furniture", "Select", "Cancel");
  }
  return 1;
}

Dialog:SuiteFurnitureSelect(playerid, response, listitem, inputtext[]) {
  if(response) {
    new suiteid = SuiteRoom_Inside(playerid);
    
    if (suiteid != -1 && (Owner_SuiteRoom(playerid, suiteid))) {
      new Float:pos[4];
      GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
      GetPlayerFacingAngle(playerid, pos[3]);

      pos[0] += 1.0 * floatsin(-pos[3], degrees);
      pos[1] += 1.0 * floatcos(-pos[3], degrees);

      switch (listitem) {
        case 0: {
          new slot = EditSuiteFurniture[playerid][1];

          if (SuiteFurniture[suiteid][slot][suitefurnUnused]) {
            SuiteFurniture[suiteid][slot][suitefurnUnused] = 0;
            SuiteFurniture[suiteid][slot][suitefurnPos][0] = pos[0];
            SuiteFurniture[suiteid][slot][suitefurnPos][1] = pos[1];
            SuiteFurniture[suiteid][slot][suitefurnPos][2] = pos[2];
            SuiteFurniture[suiteid][slot][suitefurnRot][0] = 0.0;
            SuiteFurniture[suiteid][slot][suitefurnRot][1] = 0.0;
            SuiteFurniture[suiteid][slot][suitefurnRot][2] = pos[3];

            SuiteFurniture_Refresh(slot, suiteid);
          }
          EditDynamicObject(playerid, SuiteFurniture[suiteid][slot][suitefurnObject]);
          SendCustomMessage(playerid, "FURNITURE", "You are now editing the position of \"%s"WHITE_E"\".", SuiteFurniture[suiteid][slot][suitefurnName]);
        }
        case 1: {
          new slot = EditSuiteFurniture[playerid][1];

          if(SuiteFurniture[suiteid][slot][suitefurnUnused])
            return Error(playerid, "Attach this furniture first by select option \"Editing Position\"");

          SuiteFurniture[suiteid][slot][suitefurnUnused] = 0;
          SuiteFurniture[suiteid][slot][suitefurnPos][0] = pos[0];
          SuiteFurniture[suiteid][slot][suitefurnPos][1] = pos[1];
          SuiteFurniture[suiteid][slot][suitefurnPos][2] = pos[2];
          SuiteFurniture[suiteid][slot][suitefurnRot][0] = 0.0;
          SuiteFurniture[suiteid][slot][suitefurnRot][1] = 0.0;
          SuiteFurniture[suiteid][slot][suitefurnRot][2] = pos[3];

          SetDynamicObjectPos(SuiteFurniture[suiteid][slot][suitefurnObject], SuiteFurniture[suiteid][slot][suitefurnPos][0], SuiteFurniture[suiteid][slot][suitefurnPos][1], SuiteFurniture[suiteid][slot][suitefurnPos][2]);
          SetDynamicObjectRot(SuiteFurniture[suiteid][slot][suitefurnObject], SuiteFurniture[suiteid][slot][suitefurnRot][0], SuiteFurniture[suiteid][slot][suitefurnRot][1], SuiteFurniture[suiteid][slot][suitefurnRot][2]);
          SuiteFurniture_Refresh(slot, suiteid);
          SuiteFurniture_Save(slot, suiteid);
          SendCustomMessage(playerid, "FURNITURE", "Now this furniture is moved to in front you.");
        }
        case 2: {
          SendCustomMessage(playerid, "FURNITURE", "You have destroyed furniture \"%s"WHITE_E"\".", SuiteFurniture[suiteid][EditSuiteFurniture[playerid][1]][suitefurnName]);
          SuiteFurniture_Delete(EditSuiteFurniture[playerid][1], suiteid);

          CancelEdit(playerid);
          EditSuiteFurniture[playerid][1] = -1;
          EditSuiteFurniture[playerid][0] = -1;
        }
        case 3: {
          new slot = EditSuiteFurniture[playerid][1];

          if (SuiteFurniture[suiteid][slot][suitefurnUnused])
            return Error(playerid, "This furniture already stored.");
          
          SuiteFurniture[suiteid][slot][suitefurnUnused] = 1;
          SuiteFurniture_Refresh(slot, suiteid);
          SuiteFurniture_Save(slot, suiteid);
          SendCustomMessage(playerid, "FURNITURE", "You have stored furniture \"%s"WHITE_E"\" into your suiteroom.", SuiteFurniture[suiteid][slot][suitefurnName]);
          EditSuiteFurniture[playerid][1] = -1;
          EditSuiteFurniture[playerid][0] = -1;
        }
      }
    } else {
      EditSuiteFurniture[playerid][1] = -1;
      EditSuiteFurniture[playerid][0] = -1;
      return 1;
    }
  } else SuiteFurniture_Show(playerid, EditSuiteFurniture[playerid][0]);
  return 1;
}
