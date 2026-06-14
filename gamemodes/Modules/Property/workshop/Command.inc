CMD:ws(playerid, params[]) {
    new str[128];
    foreach(new wsid : Workshop) if(IsPlayerInRangeOfPoint(playerid, 10, WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2])) {
        if(!OwnerWorkshop(playerid, wsid) && !Workshop_IsEmployee(playerid, wsid)) return Error(playerid, "You don't own this bisnis workshop.");
        {
            format(str, 128, "Workshop Status\t%s\nName Workshop\nBoard Text\nComponent\t%d units\nBank\t$%s\nEmployee", (WorkshopData[wsid][StatusWorkshop]) ? (""GREEN_E"Open") : (""RED_E"Close"), WorkshopData[wsid][StorageWorkshop][1], FormatMoney(WorkshopData[wsid][StorageWorkshop][0]));
            Dialog_Show(playerid, Workshop_Menu, DIALOG_STYLE_LIST, "Workshop Menu", str, "Select", "Close");
            PlayerInWorkshop[playerid] = wsid;
        }
    }
    return 1;
}

CMD:workshop(playerid, params[])
{
    static type[24], string[128];
    if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");
    
    if(sscanf(params, "s[24]S()[128]", type, string)) return Usage(playerid, "/workshop [create/wspos/boardpos/gateposf/gateposr/owner/delete]");
    if(!strcmp(type, "create", true))
    {
        new type1, dynamic;
        if(sscanf(string, "dd", type1, dynamic)) return Usage(playerid, "/workshop [create] [0.Transfender/1.WAA&Lowrider] [0.Static/1.Dynamic]");
        {
            new wsid = Iter_Free(Workshop);
            if(wsid == -1) return Error(playerid, "You cant create more workshop!");
            WorkshopData[wsid][Price] = 6500000;
            WorkshopData[wsid][Type] = type1;
            WorkshopData[wsid][Dynamic] = dynamic;
            GetPlayerPos(playerid, WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]);
            WorkshopData[wsid][WorkshopPos][3] = WorkshopData[wsid][WorkshopPos][4] = WorkshopData[wsid][WorkshopPos][5] = 0;
            WorkshopData[wsid][BoardPos][0] = WorkshopData[wsid][BoardPos][1] = WorkshopData[wsid][BoardPos][2] = 0;
            WorkshopData[wsid][BoardPos][3] = WorkshopData[wsid][BoardPos][4] = WorkshopData[wsid][BoardPos][5] = 0;
            WorkshopData[wsid][GatePosF][0] = WorkshopData[wsid][GatePosF][1] = WorkshopData[wsid][GatePosF][2] = WorkshopData[wsid][StatusWorkshop] = 0;
            WorkshopData[wsid][GatePosF][3] = WorkshopData[wsid][GatePosF][4] = WorkshopData[wsid][GatePosF][5] = 0;
            WorkshopData[wsid][GatePosR][0] = WorkshopData[wsid][GatePosR][1] = WorkshopData[wsid][GatePosR][2] = 0;
            WorkshopData[wsid][GatePosR][3] = WorkshopData[wsid][GatePosR][4] = WorkshopData[wsid][GatePosR][5] = 0;

            if(dynamic == 0) {
                // Static: Create visual object
                WorkshopObj[wsid] = CreateDynamicObject(12929, WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2], WorkshopData[wsid][WorkshopPos][3], WorkshopData[wsid][WorkshopPos][4], WorkshopData[wsid][WorkshopPos][5], 0, 0, -1, 300.00, 300.00); 
                GetDynamicObjectPos(WorkshopObj[wsid], WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]);
                GetDynamicObjectRot(WorkshopObj[wsid], WorkshopData[wsid][WorkshopPos][3], WorkshopData[wsid][WorkshopPos][4], WorkshopData[wsid][WorkshopPos][5]);
                EditDynamicObject(playerid, WorkshopObj[wsid]);
                WorkshopEdit[playerid][0] = 1;
                WorkshopEdit[playerid][1] = 1;
                WorkshopEdit[playerid][2] = wsid;
            } else {
                // Dynamic: No visual object, just save position
                SendCustomMessage(playerid, "WORKSHOP", "Dynamic workshop created at your position.");
            }

            format(WorkshopData[wsid][Owner], 52, "-");
            format(WorkshopData[wsid][Name], 52, "%s Workshop", GetLocation(WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]));
            WorkshopRefresh(wsid);
            Iter_Add(Workshop, wsid);
            new query[128];
            mysql_format(g_SQL, query, sizeof(query), "INSERT INTO workshop SET ID=%d, Owner='%s', Name='%s', Price='%d', type='%d', dynamic='%d'", wsid, WorkshopData[wsid][Owner], WorkshopData[wsid][Name], WorkshopData[wsid][Price], type1, dynamic);
            mysql_tquery(g_SQL, query, "WorkshopCreate", "i", wsid);
        }
    }
    else if(!strcmp(type, "wspos", true))
    {
        new wsid;
        if(sscanf(string, "d", wsid)) return Usage(playerid, "/workshop [wspos] [id]");
		if(!Iter_Contains(Workshop, wsid)) return Error(playerid, "The you specified ID of doesn't exist.");
        if(WorkshopData[wsid][Dynamic] == 1) return Error(playerid, "This workshop is dynamic, cannot edit object position.");
        if(IsValidDynamicObject(WorkshopObj[wsid])) {
            GetDynamicObjectPos(WorkshopObj[wsid], WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]);
            GetDynamicObjectRot(WorkshopObj[wsid], WorkshopData[wsid][WorkshopPos][3], WorkshopData[wsid][WorkshopPos][4], WorkshopData[wsid][WorkshopPos][5]);
            EditDynamicObject(playerid, WorkshopObj[wsid]);
            WorkshopEdit[playerid][0] = 1;
            WorkshopEdit[playerid][1] = 1;
            WorkshopEdit[playerid][2] = wsid;
        } 
    }
    else if(!strcmp(type, "boardpos", true))
    {
        new wsid;
        if(sscanf(string, "d", wsid)) return Usage(playerid, "/workshop [boardpos] [id]");
		if(!Iter_Contains(Workshop, wsid)) return Error(playerid, "The you specified ID of doesn't exist.");
        if(WorkshopData[wsid][Dynamic] == 1) return Error(playerid, "This workshop is dynamic, cannot edit board position.");
        if(IsValidDynamicObject(WorkshopData[wsid][ObjectBoard])) {
            GetDynamicObjectPos(WorkshopData[wsid][ObjectBoard], WorkshopData[wsid][BoardPos][0], WorkshopData[wsid][BoardPos][1], WorkshopData[wsid][BoardPos][2]);
            GetDynamicObjectRot(WorkshopData[wsid][ObjectBoard], WorkshopData[wsid][BoardPos][3], WorkshopData[wsid][BoardPos][4], WorkshopData[wsid][BoardPos][5]);
            EditDynamicObject(playerid, WorkshopData[wsid][ObjectBoard]);
            WorkshopEdit[playerid][0] = 1;
            WorkshopEdit[playerid][1] = 2;
            WorkshopEdit[playerid][2] = wsid;
        } 
        else {
            GetPlayerPos(playerid, WorkshopData[wsid][BoardPos][0], WorkshopData[wsid][BoardPos][1], WorkshopData[wsid][BoardPos][2]);
            WorkshopData[wsid][BoardPos][3] = WorkshopData[wsid][BoardPos][4] = WorkshopData[wsid][BoardPos][5] = 0;
            WorkshopData[wsid][ObjectBoard] = CreateDynamicObject(18244, WorkshopData[wsid][BoardPos][0], WorkshopData[wsid][BoardPos][1], WorkshopData[wsid][BoardPos][2], WorkshopData[wsid][BoardPos][3], WorkshopData[wsid][BoardPos][4], WorkshopData[wsid][BoardPos][5], 0, 0, -1, 300.00, 300.00); 
            GetDynamicObjectPos(WorkshopData[wsid][ObjectBoard], WorkshopData[wsid][BoardPos][0], WorkshopData[wsid][BoardPos][1], WorkshopData[wsid][BoardPos][2]);
            GetDynamicObjectRot(WorkshopData[wsid][ObjectBoard], WorkshopData[wsid][BoardPos][3], WorkshopData[wsid][BoardPos][4], WorkshopData[wsid][BoardPos][5]);
            EditDynamicObject(playerid, WorkshopData[wsid][ObjectBoard]);
            WorkshopEdit[playerid][0] = 1;
            WorkshopEdit[playerid][1] = 2;
            WorkshopEdit[playerid][2] = wsid;
        }
    }
    else if(!strcmp(type, "gateposf", true))
    {
        new wsid;
        if(sscanf(string, "d", wsid)) return Usage(playerid, "/workshop [gateposf] [id]");
		if(!Iter_Contains(Workshop, wsid)) return Error(playerid, "The you specified ID of doesn't exist.");
        if(WorkshopData[wsid][Dynamic] == 1) return Error(playerid, "This workshop is dynamic, cannot edit gate position.");
        if(IsValidDynamicObject(WorkshopData[wsid][ObjectGate][0])) {
            GetDynamicObjectPos(WorkshopData[wsid][ObjectGate][0], WorkshopData[wsid][GatePosF][0], WorkshopData[wsid][GatePosF][1], WorkshopData[wsid][GatePosF][2]);
            GetDynamicObjectRot(WorkshopData[wsid][ObjectGate][0], WorkshopData[wsid][GatePosF][3], WorkshopData[wsid][GatePosF][4], WorkshopData[wsid][GatePosF][5]);
            EditDynamicObject(playerid, WorkshopData[wsid][ObjectGate][0]);
            WorkshopEdit[playerid][0] = 1;
            WorkshopEdit[playerid][1] = 3;
            WorkshopEdit[playerid][2] = wsid;
        } 
        else {
            GetPlayerPos(playerid, WorkshopData[wsid][GatePosF][0], WorkshopData[wsid][GatePosF][1], WorkshopData[wsid][GatePosF][2]);
            WorkshopData[wsid][GatePosF][3] = WorkshopData[wsid][GatePosF][4] = WorkshopData[wsid][GatePosF][5] = 0;
            WorkshopData[wsid][ObjectGate][0] = CreateDynamicObject(13028,  WorkshopData[wsid][GatePosF][0], WorkshopData[wsid][GatePosF][1], WorkshopData[wsid][GatePosF][2], WorkshopData[wsid][GatePosF][3], WorkshopData[wsid][GatePosF][4], WorkshopData[wsid][GatePosF][5], 0, 0, -1, 300.00, 300.00); 
            GetDynamicObjectPos(WorkshopData[wsid][ObjectGate][0], WorkshopData[wsid][GatePosF][0], WorkshopData[wsid][GatePosF][1], WorkshopData[wsid][GatePosF][2]);
            GetDynamicObjectRot(WorkshopData[wsid][ObjectGate][0], WorkshopData[wsid][GatePosF][3], WorkshopData[wsid][GatePosF][4], WorkshopData[wsid][GatePosF][5]);
            EditDynamicObject(playerid, WorkshopData[wsid][ObjectGate][0]);
            WorkshopEdit[playerid][0] = 1;
            WorkshopEdit[playerid][1] = 3;
            WorkshopEdit[playerid][2] = wsid;
        }
    }
    else if(!strcmp(type, "gateposr", true))
    {
        new wsid;
        if(sscanf(string, "d", wsid)) return Usage(playerid, "/workshop [gateposr] [id]");
		if(!Iter_Contains(Workshop, wsid)) return Error(playerid, "The you specified ID of doesn't exist.");
        if(WorkshopData[wsid][Dynamic] == 1) return Error(playerid, "This workshop is dynamic, cannot edit gate position.");
        if(IsValidDynamicObject(WorkshopData[wsid][ObjectGate][1])) {
            GetDynamicObjectPos(WorkshopData[wsid][ObjectGate][1], WorkshopData[wsid][GatePosR][0], WorkshopData[wsid][GatePosR][1], WorkshopData[wsid][GatePosR][2]);
            GetDynamicObjectRot(WorkshopData[wsid][ObjectGate][1], WorkshopData[wsid][GatePosR][3], WorkshopData[wsid][GatePosR][4], WorkshopData[wsid][GatePosR][5]);
            EditDynamicObject(playerid, WorkshopData[wsid][ObjectGate][1]);
            WorkshopEdit[playerid][0] = 1;
            WorkshopEdit[playerid][1] = 4;
            WorkshopEdit[playerid][2] = wsid;
        } 
        else {
            GetPlayerPos(playerid, WorkshopData[wsid][GatePosR][0], WorkshopData[wsid][GatePosR][1], WorkshopData[wsid][GatePosR][2]);
            WorkshopData[wsid][GatePosR][3] = WorkshopData[wsid][GatePosR][4] = WorkshopData[wsid][GatePosR][5] = 0;
            WorkshopData[wsid][ObjectGate][1] = CreateDynamicObject(13028,  WorkshopData[wsid][GatePosR][0], WorkshopData[wsid][GatePosR][1], WorkshopData[wsid][GatePosR][2], WorkshopData[wsid][GatePosR][3], WorkshopData[wsid][GatePosR][4], WorkshopData[wsid][GatePosR][5], 0, 0, -1, 300.00, 300.00); 
            GetDynamicObjectPos(WorkshopData[wsid][ObjectGate][1], WorkshopData[wsid][GatePosR][0], WorkshopData[wsid][GatePosR][1], WorkshopData[wsid][GatePosR][2]);
            GetDynamicObjectRot(WorkshopData[wsid][ObjectGate][1], WorkshopData[wsid][GatePosR][3], WorkshopData[wsid][GatePosR][4], WorkshopData[wsid][GatePosR][5]);
            EditDynamicObject(playerid, WorkshopData[wsid][ObjectGate][1]);
            WorkshopEdit[playerid][0] = 1;
            WorkshopEdit[playerid][1] = 4;
            WorkshopEdit[playerid][2] = wsid;
        }
    }
    else if(!strcmp(type, "owner", true))
    {
        new wsid, owner[MAX_PLAYER_NAME];
        if(sscanf(string, "ds[32]", wsid, owner)) return Usage(playerid, "/workshop [owner] [id] [name]");
		if(!Iter_Contains(Workshop, wsid)) return Error(playerid, "The you specified ID of doesn't exist.");
        format(WorkshopData[wsid][Owner], MAX_PLAYER_NAME, owner);
        WorkshopSave(wsid);
        WorkshopRefresh(wsid);
        SendCustomMessage(playerid, "WORKSHOP", ""GREEN_E"You successfully turn the owner of the workshop into a player "AQUA_E"%s", WorkshopData[wsid][Owner]);
    }
    else if(!strcmp(type, "open", true))
    {
        new wsid;
        if(sscanf(string, "d", wsid)) return Usage(playerid, "/workshop [open] [id]");
		if(!Iter_Contains(Workshop, wsid)) return Error(playerid, "The you specified ID of doesn't exist.");
        if(WorkshopData[wsid][Dynamic] == 1) return Error(playerid, "This workshop is dynamic, cannot open/close gate.");
        switch(WorkshopData[wsid][StatusWorkshop]) {
            case 0: {
                MoveDynamicObject(WorkshopData[wsid][ObjectGate][0], WorkshopData[wsid][GatePosF][0], WorkshopData[wsid][GatePosF][1], WorkshopData[wsid][GatePosF][2]-4, 3.0, WorkshopData[wsid][GatePosF][3], WorkshopData[wsid][GatePosF][4], WorkshopData[wsid][GatePosF][5]);
                MoveDynamicObject(WorkshopData[wsid][ObjectGate][1], WorkshopData[wsid][GatePosR][0], WorkshopData[wsid][GatePosR][1], WorkshopData[wsid][GatePosR][2]-4, 3.0, WorkshopData[wsid][GatePosR][3], WorkshopData[wsid][GatePosR][4], WorkshopData[wsid][GatePosR][5]);
                WorkshopData[wsid][StatusWorkshop] = 1;
                WorkshopSave(wsid);
            }
            case 1: {
                MoveDynamicObject(WorkshopData[wsid][ObjectGate][0], WorkshopData[wsid][GatePosR][0], WorkshopData[wsid][GatePosR][1], WorkshopData[wsid][GatePosR][2], 3.0, WorkshopData[wsid][GatePosR][3], WorkshopData[wsid][GatePosR][4], WorkshopData[wsid][GatePosR][5]);
                MoveDynamicObject(WorkshopData[wsid][ObjectGate][1], WorkshopData[wsid][GatePosR][0], WorkshopData[wsid][GatePosR][1], WorkshopData[wsid][GatePosR][2], 3.0, WorkshopData[wsid][GatePosR][3], WorkshopData[wsid][GatePosR][4], WorkshopData[wsid][GatePosR][5]);
                WorkshopData[wsid][StatusWorkshop] = 0;
                WorkshopSave(wsid);
            }
        }
    }
    else if(!strcmp(type, "delete", true))
    {
        new wsid;
        if(sscanf(string, "d", wsid)) return Usage(playerid, "/workshop [delete] [id]");
		if(!Iter_Contains(Workshop, wsid)) return Error(playerid, "The you specified ID of doesn't exist.");
        WorkshopData[wsid][WorkshopPos][0] = WorkshopData[wsid][WorkshopPos][1] = WorkshopData[wsid][WorkshopPos][2] = WorkshopData[wsid][WorkshopPos][3] = WorkshopData[wsid][WorkshopPos][4] = WorkshopData[wsid][WorkshopPos][5] = 0;
        if(IsValidDynamicObject(WorkshopObj[wsid])) DestroyDynamicObject(WorkshopObj[wsid]);
        if(IsValidDynamicObject(WorkshopData[wsid][ObjectBoard])) DestroyDynamicObject(WorkshopData[wsid][ObjectBoard]);
        if(IsValidDynamicObject(WorkshopData[wsid][ObjectGate][0])) DestroyDynamicObject(WorkshopData[wsid][ObjectGate][0]);
        if(IsValidDynamicObject(WorkshopData[wsid][ObjectGate][1])) DestroyDynamicObject(WorkshopData[wsid][ObjectGate][1]);
        if(IsValidDynamicObject(WorkshopData[wsid][ObjectButton])) DestroyDynamicObject(WorkshopData[wsid][ObjectButton]);
        if(IsValidDynamic3DTextLabel(WorkshopLabel[wsid])) DestroyDynamic3DTextLabel(WorkshopLabel[wsid]);
        SendCustomMessage(playerid, "WORKSHOP", ""GREEN_E"You successfully deleted workshop "AQUA_E"[ID: %d]", wsid);
        Iter_Remove(Workshop, wsid);
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM workshop WHERE ID=%d", wsid);
		mysql_tquery(g_SQL, query);
    }
    return 1;
}

CMD:buyworkshop(playerid, params[])
{
    foreach(new wsid : Workshop) if(IsPlayerInRangeOfPoint(playerid, 10, WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2])) {
        if(PropertiCommercial_CountMax(playerid) >= PropertiesCommercial_Max(playerid)) return Error(playerid, "You can no longer buy a business, your property slots are full");
        if(WorkshopData[wsid][Price] > GetPlayerMoney(playerid)) return Error(playerid, "Not enough money, you can't afford this Workshop.");
        if(strcmp(WorkshopData[wsid][Owner], "-")) return Error(playerid, "Someone already owns this Workshop.");
        GivePlayerMoneyEx(playerid, -WorkshopData[wsid][Price]);
        GetPlayerName(playerid, WorkshopData[wsid][Owner], MAX_PLAYER_NAME);
        format(WorkshopData[wsid][TextWorkshop], 128, "(w)Repair (g)$0-$250(n)(w)Modification (g)$50(n)(w)Upgrade (g)$250(n)");
        WorkshopRefresh(wsid);
        WorkshopSave(wsid);
        SendClientMessageEx(playerid, COLOR_ARWIN, "WORKSHOP: "WHITE_E"Anda berhasil membeli workshop dengan harga "GREEN_E"$%s", FormatMoney(WorkshopData[wsid][Price]));
    }
    return 1;
}
