
Dialog:House_Menu(playerid, response, listitem, inputtext[]) {
    if (response) {
        new id = pData[playerid][pInHouse];
        if (id != -1) {
            switch (listitem) {
                case 0: {
                    if(hData[id][house_Lights]) {
                        foreach (new i : Player) if(pData[i][pInHouse] == id) {
                            TextDrawShowForPlayer(i, HouseLight);
                        }
                        SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "* %s flicks the light switch off.", ReturnName(playerid));
                        hData[id][house_Lights] = false;
                        callcmd::hm(playerid, "\0");
                    } else {
                        foreach (new i : Player) if(pData[i][pInHouse] == id) {
                            TextDrawHideForPlayer(i, HouseLight);
                        }
                        SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "* %s flicks the light switch on.", ReturnName(playerid));
                        hData[id][house_Lights] = true;
                        callcmd::hm(playerid, "\0");
                    }
                }
                case 1: House_OpenStorage(playerid, id);
                case 2: {
                    if (hData[id][houseBuilder]) Dialog_Show(playerid, House_FiredBuilder, DIALOG_STYLE_MSGBOX, "Fired Builder", WHITE_E"Your house is already assigned a Builder the contract will be expire on "GREEN_E"%s"WHITE_E", do you want to fired them?", "Yes", "Back", experieddate(hData[id][houseBuilderTime],3));
                    else Dialog_Show(playerid, House_AssignBuilder, DIALOG_STYLE_INPUT, "House Assign Builder", "Please input the playerid or name:", "Assign", "Back");
                }
            }
        }
    }
    return 1;
}

Dialog:House_Abandon(playerid, response, listitem, inputtext[]) {
    new id = pData[playerid][pInHouse];
    if (id != -1) {
        if (response) {
            House_RemoveFurniture(id);
            HouseStructure_DeleteAll(id);
            House_Refresh(id);
            House_Save(id);

            SendCustomMessage(playerid, "HOUSE", "You have abandoned your house: %s.", hData[id][hAddress]);
        }
    } else callcmd::hm(playerid, "\0");
    return 1;
}

Dialog:House_AssignBuilder(playerid, response, listitem, inputtext[]) {
    new houseid = pData[playerid][pInHouse];

    if (houseid != -1) {
        if (response) {
            new userid;
            if (isnull(inputtext))
                return Dialog_Show(playerid, House_AssignBuilder, DIALOG_STYLE_INPUT, "House Assign Builder", "Please input the playerid or name:", "Assign", "Back"), Error(playerid, "Invalid input!");

            if (sscanf(inputtext, "u", userid))
                return Dialog_Show(playerid, House_AssignBuilder, DIALOG_STYLE_INPUT, "House Assign Builder", "Please input the playerid or name:", "Assign", "Back"), Error(playerid, "Invalid input!");

            if (!IsPlayerConnected(userid))
                return Error(playerid, "Invalid playerid or name!");

            if (userid == playerid)
                return Error(playerid, "Cannot assign yourself");

            if (pData[userid][pJob] != 9 && pData[userid][pJob2] != 9)
                return Error(playerid, "That player are not a Bulder");

            hData[houseid][houseBuilder] = pData[userid][pID];
            hData[houseid][houseBuilderTime] = (gettime()+((24*3600)*7));
            SendCustomMessage(playerid, "HOUSE", "You've been assigned "YELLOW_E"%s "WHITE_E"as your house builder, it will automatically fired for 7 days.", ReturnName(userid));
            SendCustomMessage(userid, "HOUSE", ""YELLOW_E"%s "WHITE_E"has assigned you as house builder.", ReturnName(playerid));
        }
    }
    return 1;
}

Dialog:House_FiredBuilder(playerid, response, listitem, inputtext[]) {
    if (!response)
        return callcmd::hm(playerid, "\0");
    
    new houseid = pData[playerid][pInHouse];
    if (houseid != -1) {
        hData[houseid][houseBuilder] = 0;
        hData[houseid][houseBuilderTime] = 0;
        SendCustomMessage(playerid, "HOUSE", "You've been fired your house builder.");
    }
    return 1;
}

Dialog:ListedFurniture(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new id = pData[playerid][pInHouse];

        if(id != -1 && (Player_OwnsHouse(playerid, id) || hData[id][houseBuilder] == pData[playerid][pID]))
        {
            pData[playerid][pEditFurniture] = ListedFurniture[playerid][listitem];
            pData[playerid][pEditFurnHouse] = id;
            Dialog_Show(playerid, FurnitureList, DIALOG_STYLE_LIST, FurnitureData[id][pData[playerid][pEditFurniture]][furnitureName], "Edit Position\nMove to in front me\nDestroy Furniture\nStore Furniture", "Select", "Cancel");
        }
    }
    return 1;
}

Dialog:FurnitureList(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new id = pData[playerid][pInHouse],
            Float:x,
            Float:y,
            Float:z,
            Float:angle;

        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, angle);

        x += 1.0 * floatsin(-angle, degrees);
        y += 1.0 * floatcos(-angle, degrees);

        if(id != -1 && (Player_OwnsHouse(playerid, id) || hData[id][houseBuilder] == pData[playerid][pID]))
        {
            switch (listitem)
            {
                case 0:
                {
                    new furnitureid = pData[playerid][pEditFurniture];

                    if(FurnitureData[id][furnitureid][furnitureUnused])
                    {
                        FurnitureData[id][furnitureid][furnitureUnused] = 0;
                        FurnitureData[id][furnitureid][furniturePos][0] = x;
                        FurnitureData[id][furnitureid][furniturePos][1] = y;
                        FurnitureData[id][furnitureid][furniturePos][2] = z;
                        FurnitureData[id][furnitureid][furnitureRot][0] = 0.0;
                        FurnitureData[id][furnitureid][furnitureRot][1] = 0.0;
                        FurnitureData[id][furnitureid][furnitureRot][2] = angle;

                        Furniture_Refresh(furnitureid, id);
                    }
                    EditDynamicObject(playerid, FurnitureData[id][furnitureid][furnitureObject]);
                    SendCustomMessage(playerid, "HOUSE", "You are now editing the position of item \"%s"WHITE_E"\".", FurnitureData[id][furnitureid][furnitureName]);
                }
                case 1:
                {
                    new furnitureid = pData[playerid][pEditFurniture];

                    if(FurnitureData[id][pData[playerid][pEditFurniture]][furnitureUnused])
                        return Error(playerid, "Attach this furniture first by select option \"Editing Position\"");

                    FurnitureData[id][furnitureid][furnitureUnused] = 0;
                    FurnitureData[id][furnitureid][furniturePos][0] = x;
                    FurnitureData[id][furnitureid][furniturePos][1] = y;
                    FurnitureData[id][furnitureid][furniturePos][2] = z;
                    FurnitureData[id][furnitureid][furnitureRot][0] = 0.0;
                    FurnitureData[id][furnitureid][furnitureRot][1] = 0.0;
                    FurnitureData[id][furnitureid][furnitureRot][2] = angle;

                    SetDynamicObjectPos(FurnitureData[id][furnitureid][furnitureObject], FurnitureData[id][furnitureid][furniturePos][0], FurnitureData[id][furnitureid][furniturePos][1], FurnitureData[id][furnitureid][furniturePos][2]);
                    SetDynamicObjectRot(FurnitureData[id][furnitureid][furnitureObject], FurnitureData[id][furnitureid][furnitureRot][0], FurnitureData[id][furnitureid][furnitureRot][1], FurnitureData[id][furnitureid][furnitureRot][2]);
                    Furniture_Refresh(furnitureid, id);
                    Furniture_Save(furnitureid, id);
                    SendCustomMessage(playerid, "HOUSE", "Now this furniture is moved to in front you.");
                }
                case 2:
                {
                    SendCustomMessage(playerid, "HOUSE", "You have destroyed furniture \"%s"WHITE_E"\".", FurnitureData[id][pData[playerid][pEditFurniture]][furnitureName]);
                    Furniture_Delete(pData[playerid][pEditFurniture], id);

                    CancelEdit(playerid);
                    pData[playerid][pEditFurniture] = -1;
                    pData[playerid][pEditFurnHouse] = -1;
                }
                case 3: {
                    new furnitureid = pData[playerid][pEditFurniture];

                    if (FurnitureData[id][furnitureid][furnitureUnused])
                        return Error(playerid, "This furniture is already stored");
                    
                    FurnitureData[id][furnitureid][furnitureUnused] = 1;
                    Furniture_Refresh(furnitureid, id);
                    Furniture_Save(furnitureid, id);
                    SendCustomMessage(playerid, "HOUSE", "You have stored furniture \"%s"WHITE_E"\" into your house.", FurnitureData[id][furnitureid][furnitureName]);
                }
            }
        }
        else {
            pData[playerid][pEditFurniture] = -1;
            pData[playerid][pEditFurnHouse] = -1;
        }
    }
    else {
        pData[playerid][pEditFurniture] = -1;
        pData[playerid][pEditFurnHouse] = -1;
    }
    return 1;
}

Dialog:ListedStructure(playerid, response, listitem, inputtext[]) {
    if (response) {
        new id = pData[playerid][pInHouse];

        if (id != -1 && (Player_OwnsHouse(playerid, id) || hData[id][houseBuilder] == pData[playerid][pID])) {
            pData[playerid][pEditStructure] = ListedStructure[playerid][listitem];
            pData[playerid][pEditHouseStructure] = id;
            Dialog_Show(playerid, StructureList, DIALOG_STYLE_LIST, "House Structure: Edit", "Move\nRetexture\nCopy\nDestroy", "Select", "Back");
        }
    } else callcmd::dyoh(playerid, "\0");
    return 1;
}

Dialog:StructureList(playerid, response, listitem, inputtext[]) {
    if (response) {
        new houseid = pData[playerid][pInHouse], id = pData[playerid][pEditStructure];

        if (houseid != -1) {
            switch (listitem) {
                case 0: {
                    if (HouseStructure[houseid][id][structureType] > 0)
                        return Error(playerid, "Cannot move static house structure.");

                    pData[playerid][pEditHouseStructure] = houseid;
                    EditDynamicObject(playerid, HouseStructure[houseid][id][structureObject]);
                    SendCustomMessage(playerid, "HOUSE", "You're now editing %s.", GetStructureNameByModel(HouseStructure[houseid][id][structureModel]));
                }
                case 1: {
                    SetPVarInt(playerid, "structureObj", id);
                    pData[playerid][pEditHouseStructure] = houseid;
                    Dialog_Show(playerid, House_StructureRetexture, DIALOG_STYLE_INPUT, "Retexture House Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel");
                }
                case 2: {
                    if (HouseStructure[houseid][id][structureType] > 0)
                        return Error(playerid, "Cannot copy static house structure.");
                    
                    new price;

                    for (new i = 0; i < sizeof(g_aHouseStructure); i ++) if (g_aHouseStructure[i][e_StructureModel] == HouseStructure[houseid][id][structureModel]) {
                        price = g_aHouseStructure[i][e_StructureCost];
                    }

                    if (pData[playerid][pComponent] < price)
                        return Error(playerid, "You need %d Component(s) to copy this structure.", price);

                    new copyId = HouseStructure_CopyObject(id, houseid);

                    if (copyId == cellmin)
                        return Error(playerid, "Your house has reached maximum of structure");

                    pData[playerid][pComponent] -= price;
                    pData[playerid][pEditStructure] = copyId;
                    EditingHouseStructure[playerid] = 1;
                    pData[playerid][pEditHouseStructure] = houseid;
                    EditDynamicObject(playerid, HouseStructure[houseid][copyId][structureObject]);
                    SendCustomMessage(playerid, "BUILDER", "You have copied structure for "GREEN_E"%d component(s)", price);
                    SendCustomMessage(playerid, "BUILDER", "You're now editing copied object of %s.", GetStructureNameByModel(HouseStructure[houseid][id][structureModel]));
                }
                case 3: {
                    if (HouseStructure[houseid][id][structureType] > 0)
                        return Error(playerid, "Cannot destroy static house structure.");

                    SendCustomMessage(playerid, "HOUSE", "You've been successfully deleted %s", GetStructureNameByModel(HouseStructure[houseid][id][structureModel]));
                    HouseStructure_Delete(id, houseid);
                }
            }
        }
    } else callcmd::dyoh(playerid, "\0");
    return 1;
}

Dialog:House_Structure(playerid, response, listitem, inputtext[]) {
    if (response) {
        new id = pData[playerid][pInHouse];
        if (id != -1) {
            switch (listitem) {
                case 0: {
                    new str[128];
                    strcat(str, "Type\tCost (components)\n");
                    for (new i = 0; i < sizeof(g_aHouseStructure); i ++) {
                        format(str, sizeof(str), "%s%s\t%d\n", str, g_aHouseStructure[i][e_StructureName], g_aHouseStructure[i][e_StructureCost]);
                    }
                    Dialog_Show(playerid, House_StructureAdd, DIALOG_STYLE_TABLIST_HEADERS, "House Structure Modification", str, "Select", "Back");
                }
                case 1: {
                    pData[playerid][pEditHouseStructure] = id;
                    SelectStructureType[playerid] = STRUCTURE_SELECT_EDITOR;
                    SelectObject(playerid);
                    SendCustomMessage(playerid, "BUILDER", "Please select the structure, you wish to move.");
                }
                case 2: {
                    pData[playerid][pEditHouseStructure] = id;
                    SelectStructureType[playerid] = STRUCTURE_SELECT_RETEXTURE;
                    SelectObject(playerid);
                    SendCustomMessage(playerid, "BUILDER", "Please select the structure, you wish to retexture.");
                }
                case 3: {
                    pData[playerid][pEditHouseStructure] = id;
                    SelectStructureType[playerid] = STRUCTURE_SELECT_DELETE;
                    SelectObject(playerid);
                    SendCustomMessage(playerid, "BUILDER", "Please select the structure, you wish to destroy.");
                }
                case 4: {
                    pData[playerid][pEditHouseStructure] = id;
                    SelectStructureType[playerid] = STRUCTURE_SELECT_COPY;
                    SelectObject(playerid);
                    SendCustomMessage(playerid, "BUILDER", "Please select the structure, you wish to copy.");
                }
                case 5: {
                    if (!HouseStructure_GetCount(id))
                        return Error(playerid, "There are no structures in this house.");
                    
                    pData[playerid][pEditHouseStructure] = id;
                    Dialog_Show(playerid, House_StructureDestroy, DIALOG_STYLE_MSGBOX, "Destroy All Structures", RED_E"WARNING:\n"WHITE_E"Are you sure you want to destroy all structures in this house?", "Yes", "No");
                }
                case 6: {
                    pData[playerid][pEditHouseStructure] = id;
                    Dialog_Show(playerid, House_StructureType, DIALOG_STYLE_LIST, "Structure Type", "Static\nCostum", "Select", "Cancel");
                }
                case 7: {
                    pData[playerid][pEditFurnHouse] = id;
                    SelectFurnitureType[playerid] = FURNITURE_SELECT_MOVE;
                    SelectObject(playerid);
                    SendCustomMessage(playerid, "BUILDER", "Plase select the furniture, you wish to move.");
                }
                case 8: {
                    pData[playerid][pEditFurnHouse] = id;
                    SelectFurnitureType[playerid] = FURNITURE_SELECT_DESTROY;
                    SelectObject(playerid);
                    SendCustomMessage(playerid, "BUILDER", "Plase select the furniture, you wish to destroy.");
                }
                case 9: {
                    pData[playerid][pEditFurnHouse] = id;
                    SelectFurnitureType[playerid] = FURNITURE_SELECT_STORE;
                    SelectObject(playerid);
                    SendCustomMessage(playerid, "BUILDER", "Plase select the furniture, you wish to store.");
                }
                case 10: {
                    new
                        count = 0,
                        string[MAX_FURNITURE * 64];

                    if(!Furniture_GetCount(id))
                        return Error(playerid, "This house doesn't have any furniture spawned.");

                    strcat(string, "Model\tDistance\n");
                    foreach (new i : HouseFurnitures[id])
                    {
                        if(FurnitureData[id][i][furnitureUnused]) 
                            format(string, sizeof(string), "%s%s\t(Not placed)\n", string, FurnitureData[id][i][furnitureName]);
                        else 
                            format(string, sizeof(string), "%s%s\t%.2f\n", string, FurnitureData[id][i][furnitureName], GetPlayerDistanceFromPoint(playerid, FurnitureData[id][i][furniturePos][0], FurnitureData[id][i][furniturePos][1], FurnitureData[id][i][furniturePos][2]));

                        ListedFurniture[playerid][count++] = i;
                    }
                    Dialog_Show(playerid, ListedFurniture, DIALOG_STYLE_TABLIST_HEADERS, "House Furniture", string, "Select", "Cancel");
                }
                case 11: Dialog_Show(playerid, House_Abandon, DIALOG_STYLE_MSGBOX, "House Abandon", "Are you sure want to abandon your house?", "Sure", "Back");
            }
        }
    }
    return 1;
}

Dialog:House_StructureDestroy(playerid, response, listitem, inputtext[]) {
    if (!response)
        return callcmd::dyoh(playerid, "\0");
    
    new houseid = pData[playerid][pEditHouseStructure];

    if (houseid != -1 && (Player_OwnsHouse(playerid, houseid) || hData[houseid][houseBuilder] == pData[playerid][pID])) {
        HouseStructure_DeleteAll(houseid);
        SendCustomMessage(playerid, "BUILDER", "All structures in this house have been destroyed.");
    }
    return 1;
}

Dialog:House_StructureType(playerid, response, listitem, inputtext[]) {
    if (response) {
        new id = pData[playerid][pInHouse];
        if (id != -1) {
            switch (listitem) {
                case 0: {
                    new
                        count = 0,
                        string[90 * 64];

                    strcat(string, "Model\tDistance\n");
                    foreach (new i : HouseStruct[id]) if (HouseStructure[id][i][structureType] > 0) {
                        format(string, sizeof(string), ORANGE_E"%sStatic\t%.2f\n", string, GetPlayerDistanceFromPoint(playerid, HouseStructure[id][i][structurePos][0], HouseStructure[id][i][structurePos][1], HouseStructure[id][i][structurePos][2]));
                        ListedStructure[playerid][count++] = i;
                    }
                    Dialog_Show(playerid, ListedStructure, DIALOG_STYLE_TABLIST_HEADERS, "Static House Structure", string, "Select", "Cancel");
                }
                case 1: {
                    new
                        count = 0,
                        string[MAX_HOUSE_STRUCTURES * 64];

                    if(!HouseStructure_GetCount(id))
                        return Error(playerid, "This house doesn't have any structures.");

                    strcat(string, "Model\tDistance\n");
                    foreach (new i : HouseStruct[id]) if (HouseStructure[id][i][structureType] == 0) {
                        format(string, sizeof(string), "%s%s\t%.2f\n", string, GetStructureNameByModel(HouseStructure[id][i][structureModel]), GetPlayerDistanceFromPoint(playerid, HouseStructure[id][i][structurePos][0], HouseStructure[id][i][structurePos][1], HouseStructure[id][i][structurePos][2]));
                        ListedStructure[playerid][count++] = i;
                    }
                    Dialog_Show(playerid, ListedStructure, DIALOG_STYLE_TABLIST_HEADERS, "Custom House Structure", string, "Select", "Cancel");
                }
            }
        }
    }
    return 1;
}

Dialog:House_StructureAdd(playerid, response, listitem, inputtext[]) {
    new houseid = pData[playerid][pInHouse];
    if (houseid != -1) {
        if (response) {
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

            if(HouseStructure_GetCount(houseid) >= MAX_HOUSE_STRUCTURES)
                return Error(playerid, "You can only have %d structure items in your house.", MAX_HOUSE_STRUCTURES);

            new id = HouseStructure_Add(houseid, g_aHouseStructure[listitem][e_StructureModel], x+1, y, z, 0.0, 0.0, angle);

            if (id == cellmin)
                return Error(playerid, "Server has been reached maximum of house structure");

            pData[playerid][pComponent] -= g_aHouseStructure[listitem][e_StructureCost];
            pData[playerid][pEditStructure] = id;
            pData[playerid][pEditHouseStructure] = houseid;
            EditingHouseStructure[playerid] = 1;
            EditDynamicObject(playerid, HouseStructure[houseid][id][structureObject]);
            SendCustomMessage(playerid, "HOUSE", "You've been created "YELLOW_E"%s "WHITE_E"structure for "GREEN_E"%d components", g_aHouseStructure[listitem][e_StructureName], g_aHouseStructure[listitem][e_StructureCost]);
        } else callcmd::dyoh(playerid, "\0");
    }
    return 1;
}

Dialog:House_StructureRetexture(playerid, response, listitem, inputtext[]) {
    new houseid = pData[playerid][pInHouse];
    if (houseid != -1) {
        new id = GetPVarInt(playerid, "structureObj");
        if (response) {
            new model,color[4];
            new const txdname[32],texture[32];
            if (isnull(inputtext))
                return Dialog_Show(playerid, House_StructureRetexture, DIALOG_STYLE_INPUT, "Retexture House Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel"), Error(playerid, "Invalid input!");

            if (sscanf(inputtext, "ds[32]s[32]D(0)D(0)D(0)D(0)",model,txdname,texture,color[0],color[1],color[2],color[3]))
                return Dialog_Show(playerid, House_StructureRetexture, DIALOG_STYLE_INPUT, "Retexture House Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel"), Error(playerid, "Invalid input!");

            if (!IsValidTexture(texture))
                return Dialog_Show(playerid, House_StructureRetexture, DIALOG_STYLE_INPUT, "Retexture House Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel"), Error(playerid, "Texture model tidak terdaftar dalam database");

            if (pData[playerid][pComponent] < 10)
                return Error(playerid, "You need 10 components to retexture the house structure");

            HouseStructure[houseid][id][structureMaterial] = GetTextureIndex(texture);
            HouseStructure[houseid][id][structureColor] = RGBAToInt(color[1], color[2], color[3], color[0]);
            HouseStructure_Refresh(id, houseid);
            HouseStructure_Save(id, houseid);

            pData[playerid][pComponent] -= 10;
            SendCustomMessage(playerid, "BUILDER", "You've been retextured the house structure with "YELLOW_E"10 components");
        } else callcmd::dyoh(playerid, "\0");
    }
    return 1;
}

Dialog:HouseCrack(playerid, response, listitem, inputtext[]) 
{
    new houseid = pData[playerid][pInHouse];
    if(response)
    {
        switch (listitem)
        {
            case 0: 
            {
                new str[128];
                format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:");
                Dialog_Show(playerid, HouseWithdrawCrack, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
            }
            case 1: 
            {
                new str[128];
                format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:");
                Dialog_Show(playerid, HouseDepositCrack, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
            }
        }
    }
    else House_OpenStorage(playerid, houseid);
    return 1;
}

Dialog:HouseWithdrawCrack(playerid, response, listitem, inputtext[]) 
{
    new houseid = pData[playerid][pInHouse];
    if(response)
    {
        new amount = strval(inputtext);

        if(isnull(inputtext))
        {
            new str[128];
            format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:");
            Dialog_Show(playerid, HouseWithdrawCrack, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
            return 1;
        }
        if(amount < 1 || amount > hData[houseid][hCrack])
        {
            new str[128];
            format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:");
            Dialog_Show(playerid, HouseWithdrawCrack, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
            return 1;
        }
        hData[houseid][hCrack] -= amount;
        pData[playerid][pCrack] += amount;

        House_Save(houseid);
        House_OpenStorage(playerid, houseid);

        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has withdrawn %s from their house safe.", ReturnName(playerid), amount);
    }
	else Dialog_Show(playerid, HouseCrack, DIALOG_STYLE_LIST, "Crack", "Withdraw from safe\nDeposit into safe", "Select", "Back");
    return 1;
}

Dialog:HouseDepositCrack(playerid, response, listitem, inputtext[]) 
{
    new houseid = pData[playerid][pInHouse];
    if(response)
    {
        new amount = strval(inputtext);

        if(isnull(inputtext))
        {
            new str[128];
            format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:");
            Dialog_Show(playerid, HouseDepositCrack, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
            return 1;
        }
        if(amount < 1 || amount > pData[playerid][pCrack])
        {
            new str[128];
            format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:");
            Dialog_Show(playerid, HouseDepositCrack, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
            return 1;
        }
        hData[houseid][hCrack] += amount;
        pData[playerid][pCrack] -= amount;

        House_Save(houseid);
        House_OpenStorage(playerid, houseid);

        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deposited %s into their house safe.", ReturnName(playerid), amount);
    }
	else Dialog_Show(playerid, HouseCrack, DIALOG_STYLE_LIST, "Crack", "Withdraw from safe\nDeposit into safe", "Select", "Back");
    return 1;
}

Dialog:HousePot(playerid, response, listitem, inputtext[]) 
{
    new houseid = pData[playerid][pInHouse];
    if(response)
    {
        switch (listitem)
        {
            case 0: 
            {
                new str[128];
                format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:");
                Dialog_Show(playerid, HouseWithdrawPot, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
            }
            case 1: 
            {
                new str[128];
                format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:");
                Dialog_Show(playerid, HouseDepositPot, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
            }
        }
    }
    else House_OpenStorage(playerid, houseid);
    return 1;
}

Dialog:HouseWithdrawPot(playerid, response, listitem, inputtext[]) 
{
    new houseid = pData[playerid][pInHouse];
    if(response)
    {
        new amount = strval(inputtext);

        if(isnull(inputtext))
        {
            new str[128];
            format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:");
            Dialog_Show(playerid, HouseWithdrawPot, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
            return 1;
        }
        if(amount < 1 || amount > hData[houseid][hPot])
        {
            new str[128];
            format(str, sizeof(str), "Please enter how much you wish to withdraw from the safe:");
            Dialog_Show(playerid, HouseWithdrawPot, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
            return 1;
        }
        hData[houseid][hPot] -= amount;
        pData[playerid][pPot] += amount;

        House_Save(houseid);
        House_OpenStorage(playerid, houseid);

        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has withdrawn %s from their house safe.", ReturnName(playerid), amount);
    }
	else Dialog_Show(playerid, HousePot, DIALOG_STYLE_LIST, "Pot", "Withdraw from safe\nDeposit into safe", "Select", "Back");
    return 1;
}

Dialog:HouseDepositPot(playerid, response, listitem, inputtext[]) 
{
    new houseid = pData[playerid][pInHouse];
    if(response)
    {
        new amount = strval(inputtext);

        if(isnull(inputtext))
        {
            new str[128];
            format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:");
            Dialog_Show(playerid, HouseDepositPot, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
            return 1;
        }
        if(amount < 1 || amount > pData[playerid][pPot])
        {
            new str[128];
            format(str, sizeof(str), "Please enter how much you wish to deposit into the safe:");
            Dialog_Show(playerid, HouseDepositPot, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
            return 1;
        }
        hData[houseid][hPot] += amount;
        pData[playerid][pPot] -= amount;

        House_Save(houseid);
        House_OpenStorage(playerid, houseid);

        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deposited %s into their house safe.", ReturnName(playerid), amount);
    }
	else Dialog_Show(playerid, HousePot, DIALOG_STYLE_LIST, "Pot", "Withdraw from safe\nDeposit into safe", "Select", "Back");
    return 1;
}
