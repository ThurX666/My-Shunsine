alias:suiteroommenu("srm")

CMD:suiteroommenu(playerid, params[]) {
    new id = -1;
    if ((id = SuiteRoom_Inside(playerid)) != -1) {
        if (!Owner_SuiteRoom(playerid, id)) return Error(playerid, "You're not the owner of this apartment");
        Dialog_Show(playerid, Dialog_ApartmentMenu, DIALOG_STYLE_LIST, "SuiteRoom Menu", "Furnitures\nStructures\nAssign Builder", "Select", "Cancel");
        return 1;
    }
    Error(playerid,"You're not in range of any suite room");
    return 1;
}

CMD:suiteroom(playerid, params[])
{
    static type[24], string[128];
    if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");
    if(sscanf(params, "s[24]S()[128]", type, string)) return Usage(playerid, "/suiteroom [create/doorpos/buttonpos/owner/delete]");
    if(!strcmp(type, "create", true))
    {
        new typesuite;
        if(sscanf(string, "d", typesuite)) return Usage(playerid, "/suiteroom [create] [type [1. 1Room] [2.2Room] [3.3Room]]");
        new Float:pos[3];
        GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
        new suiteid = Iter_Free(SuiteRooms);
        if(suiteid == -1) return Error(playerid, "You cant create more suite room!");
        SuiteRoom[suiteid][suiteRoomPrice] = 1000000;
        SuiteRoom[suiteid][suiteRoomLocked] = 0;
        format(SuiteRoom[suiteid][suiteRoomOwner], 52, "-");

        if(IsValidDynamicObject(SuiteRoom[suiteid][suiteObjectDoors])) DestroyDynamicObject(SuiteRoom[suiteid][suiteObjectDoors]);
        GetPlayerPos(playerid, SuiteRoom[suiteid][suiteRoomDoors][0], SuiteRoom[suiteid][suiteRoomDoors][1], SuiteRoom[suiteid][suiteRoomDoors][2]);
        SuiteRoom[suiteid][suiteRoomDoors][3] = SuiteRoom[suiteid][suiteRoomDoors][4] = SuiteRoom[suiteid][suiteRoomDoors][5] = 0;
        SuiteRoom[suiteid][suiteRoomButtons][0] = SuiteRoom[suiteid][suiteRoomButtons][1] = SuiteRoom[suiteid][suiteRoomButtons][2] = 0;
        SuiteRoom[suiteid][suiteRoomButtons][3] = SuiteRoom[suiteid][suiteRoomButtons][4] = SuiteRoom[suiteid][suiteRoomButtons][5] = 0;
        SuiteRoom[suiteid][suiteObjectDoors] = CreateDynamicObject(1569, SuiteRoom[suiteid][suiteRoomDoors][0], SuiteRoom[suiteid][suiteRoomDoors][1], SuiteRoom[suiteid][suiteRoomDoors][2], SuiteRoom[suiteid][suiteRoomDoors][3], SuiteRoom[suiteid][suiteRoomDoors][4], SuiteRoom[suiteid][suiteRoomDoors][5], 0, 0, -1, 300.00, 300.00); 
        
        SuiteRoom_AreaPos(suiteid, typesuite, pos[2]);

        EditDynamicObject(playerid, SuiteRoom[suiteid][suiteObjectDoors]);
        PlayerEditSuiteRoom[playerid][0] = 1;
        PlayerEditSuiteRoom[playerid][1] = suiteid;
        
        Iter_Add(SuiteRooms, suiteid);
        new query[128];
        mysql_format(g_SQL, query, sizeof(query), "INSERT INTO suiteroom SET ID=%d, owner='%s', price='%d'", suiteid, SuiteRoom[suiteid][suiteRoomOwner], SuiteRoom[suiteid][suiteRoomPrice]);
        mysql_tquery(g_SQL, query, "SuiteRoomCreate", "i", suiteid);
    }
    else if(!strcmp(type, "doorpos", true))
    {
        new slot;
        if(sscanf(string, "d", slot)) return Usage(playerid, "/suiteroom [doorpos] [id]");
		if(!Iter_Contains(SuiteRooms, slot)) return Error(playerid, "The you specified ID of doesn't exist.");
        if(IsValidDynamicObject(SuiteRoom[slot][suiteObjectDoors])) {
            GetDynamicObjectPos(SuiteRoom[slot][suiteObjectDoors], SuiteRoom[slot][suiteRoomDoors][0], SuiteRoom[slot][suiteRoomDoors][1], SuiteRoom[slot][suiteRoomDoors][2]);
            GetDynamicObjectRot(SuiteRoom[slot][suiteObjectDoors], SuiteRoom[slot][suiteRoomDoors][3], SuiteRoom[slot][suiteRoomDoors][4], SuiteRoom[slot][suiteRoomDoors][5]);
            EditDynamicObject(playerid, SuiteRoom[slot][suiteObjectDoors]);
            PlayerEditSuiteRoom[playerid][0] = 1;
            PlayerEditSuiteRoom[playerid][1] = slot;
        } 
    }
    else if(!strcmp(type, "owner", true))
    {
        new slot, owner[52];
        if (sscanf(string, "ds[52]", slot, owner))
            return Usage(playerid, "/suiteroom owner [name]]");
        
        if(!Iter_Contains(SuiteRooms, slot)) return Error(playerid, "The you specified ID of doesn't exist.");
        format(SuiteRoom[slot][suiteRoomOwner], 52, owner);
        SuiteRoom_Save(slot);
        SuiteRoom_Refresh(slot);
        SuiteStructure_DeleteAll(slot);
        SuiteFurniture_DeleteAll(slot);
    }
    else if(!strcmp(type, "areapos", true))
    {
        new slot, typearea, Float:Pos[3];
        if (sscanf(string, "dd", slot, typearea))
            return Usage(playerid, "/suiteroom areapos [suiteroom id] [type [1. 1Room] [2.2Room] [3.3Room]]");
        
        if(!Iter_Contains(SuiteRooms, slot)) return Error(playerid, "The you specified ID of doesn't exist.");
        GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
        SuiteRoom_AreaPos(slot, typearea, Pos[2]);
        SuiteRoom_Save(slot);
        SuiteRoom_Refresh(slot);
        SendCustomMessage(playerid, "SUITEROOM","You've set suite room ID: "YELLOW_E"%d"WHITE_E" area pos to: "YELLOW_E"%.2f, %.2f, %.2f, %.2f", slot, SuiteRoom[slot][suiteRoomAreaPos][0], SuiteRoom[slot][suiteRoomAreaPos][1], SuiteRoom[slot][suiteRoomAreaPos][2], SuiteRoom[slot][suiteRoomAreaPos][3]);
    }
    else if(!strcmp(type, "buttonpos", true))
    {
        new slot;
        if(sscanf(string, "d", slot)) return Usage(playerid, "/suiteroom [buttonpos] [id]");
		if(!Iter_Contains(SuiteRooms, slot)) return Error(playerid, "The you specified ID of doesn't exist.");
        if(IsValidDynamicObject(SuiteRoom[slot][suiteObjectText])) {
            GetDynamicObjectPos(SuiteRoom[slot][suiteObjectText], SuiteRoom[slot][suiteRoomButtons][0], SuiteRoom[slot][suiteRoomButtons][1], SuiteRoom[slot][suiteRoomButtons][2]);
            GetDynamicObjectRot(SuiteRoom[slot][suiteObjectText], SuiteRoom[slot][suiteRoomButtons][3], SuiteRoom[slot][suiteRoomButtons][4], SuiteRoom[slot][suiteRoomButtons][5]);
            EditDynamicObject(playerid, SuiteRoom[slot][suiteObjectText]);
            PlayerEditSuiteRoom[playerid][0] = 2;
            PlayerEditSuiteRoom[playerid][1] = slot;
        } 
        else {
            GetPlayerPos(playerid, SuiteRoom[slot][suiteRoomButtons][0], SuiteRoom[slot][suiteRoomButtons][1], SuiteRoom[slot][suiteRoomButtons][2]);
            SuiteRoom[slot][suiteRoomButtons][3] = SuiteRoom[slot][suiteRoomButtons][4] = SuiteRoom[slot][suiteRoomButtons][5] = 0;
            SuiteRoom[slot][suiteObjectText] = CreateDynamicObject(2714, SuiteRoom[slot][suiteRoomButtons][0], SuiteRoom[slot][suiteRoomButtons][1], SuiteRoom[slot][suiteRoomButtons][2], SuiteRoom[slot][suiteRoomButtons][3], SuiteRoom[slot][suiteRoomButtons][4], SuiteRoom[slot][suiteRoomButtons][5], -1, -1, -1, 300.00, 300.00); 
            GetDynamicObjectPos(SuiteRoom[slot][suiteObjectText], SuiteRoom[slot][suiteRoomButtons][0], SuiteRoom[slot][suiteRoomButtons][1], SuiteRoom[slot][suiteRoomButtons][2]);
            GetDynamicObjectRot(SuiteRoom[slot][suiteObjectText], SuiteRoom[slot][suiteRoomButtons][3], SuiteRoom[slot][suiteRoomButtons][4], SuiteRoom[slot][suiteRoomButtons][5]);
            EditDynamicObject(playerid, SuiteRoom[slot][suiteObjectText]);
            PlayerEditSuiteRoom[playerid][0] = 2;
            PlayerEditSuiteRoom[playerid][1] = slot;
        }
    }
    else if(!strcmp(type, "gangzone", true))
    {
        new slot;
        if(sscanf(string, "d", slot)) return Usage(playerid, "/suiteroom [gangzone] [id]");
		if(!Iter_Contains(SuiteRooms, slot)) return Error(playerid, "The you specified ID of doesn't exist.");
        new gangID = GetFreeSuiteZone();
        if (gangID == -1) return Error(playerid, "No free gang zones available");
        testsuiteZone[gangID] = GangZoneCreate(SuiteRoom[slot][suiteRoomAreaPos][0], SuiteRoom[slot][suiteRoomAreaPos][1], SuiteRoom[slot][suiteRoomAreaPos][2], SuiteRoom[slot][suiteRoomAreaPos][3]);
        GangZoneShowForAll(testsuiteZone[gangID], 0xFF0000FF);
        GangZoneFlashForAll(testsuiteZone[gangID], 0xFF0000FF);
        SendCustomMessage(playerid,"SUITEROOM","You've created gang zone ID: "YELLOW_E"%d"WHITE_E" for suite room ID: "YELLOW_E"%d", gangID, slot);
    }
    else if(!strcmp(type, "gangzonedelete", true))
    {
        new slot, gangid;
        if(sscanf(string, "dd", slot, gangid)) return Usage(playerid, "/suiteroom [gangzone] [id] [gangid]");
		if(!Iter_Contains(SuiteRooms, slot)) return Error(playerid, "The you specified ID of doesn't exist.");
        GangZoneDestroy(testsuiteZone[gangid]);
        SendCustomMessage(playerid,"SUITEROOM","You've delete gang zone ID: "YELLOW_E"%d"WHITE_E" from suite room ID: "YELLOW_E"%d", gangid, slot);
    }
    else if(!strcmp(type, "goto", true))
    {
        new slot;
        if(sscanf(string, "dd", slot)) return Usage(playerid, "/suiteroom [goto] [id]");
		if(!Iter_Contains(SuiteRooms, slot)) return Error(playerid, "The you specified ID of doesn't exist.");
        SetPlayerPos(playerid, SuiteRoom[slot][suiteRoomDoors][0], SuiteRoom[slot][suiteRoomDoors][1], SuiteRoom[slot][suiteRoomDoors][2]);
    }
    else if(!strcmp(type, "delete", true))
    {
        new slot;
        if(sscanf(string, "dd", slot)) return Usage(playerid, "/suiteroom [delete] [id]");
		if(!Iter_Contains(SuiteRooms, slot)) return Error(playerid, "The you specified ID of doesn't exist.");
        if (SuiteRoom_Delete(slot))
            SendCustomMessage(playerid,"SUITEROOM","You've deleted suite room ID: "YELLOW_E"%d", slot);
        else
            return Error(playerid, "Unable to delete suite room");
    }
    return 1;
}
