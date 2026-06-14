
CMD:aforager(playerid, params[]) {
    if (pData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    new option[24], value[32];
    if (sscanf(params,"s[24]S()[32]",option,value))
        return Usage(playerid,"/aforager [option]"),SendClientMessage(playerid, COLOR_ARWIN, "[OPTIONS]: "WHITE_E"create, delete, edit, amount, type, goto");
    
    new id;
    if (!strcmp(option,"create",true)) {
        new Float:pos[3];
        GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
        
        id = Bush_Create(14402, pos[0], pos[1], pos[2]-0.5);
        if (id == cellmin) return Error(playerid, "Failed to create tree forager");
        SendCustomMessage(playerid,"FORAGER","You've created tree forager ID: %d",id);
    } else if (!strcmp(option,"delete",true)) {
        if (sscanf(value,"d",id)) return Usage(playerid,"/aforager delete [bush id]");
        if (!Iter_Contains(BushForager, id)) return Error(playerid, "Invalid tree id");
        
        Bush_Delete(id);
        SendCustomMessage(playerid,"FORAGER","You've deleted tree forager ID: %d",id);
    } else if (!strcmp(option,"edit",true)) {
        if (sscanf(value,"d",id))
            return Usage(playerid,"/aforager edit [bush id]");
        
        if (!Iter_Contains(BushForager, id))
            return Error(playerid, "Invalid tree id");

        EditBushForager[playerid] = id;
        EditDynamicObject(playerid, ForegerData[id][bushObject]);
        SendCustomMessage(playerid,"FORAGER","You're now editing tree forager ID: %d",id);
    } else if (!strcmp(option,"amount",true)) {
        new amount;
        if (sscanf(value,"dd",id,amount))
            return Usage(playerid,"/aforager amount [bush id] [amount]");
        
        if (amount < 1)
            return Error(playerid, "Invalid amount");
        
        if (!Iter_Contains(BushForager, id))
            return Error(playerid, "Invalid tree id");
        
        ForegerData[id][bushAmount] = amount;
        Bush_Save(id);

        SendCustomMessage(playerid,"FORAGER","You've edited amount of tree forager ID: %d, to %d",id,amount);
    } else if (!strcmp(option,"goto",true)) {
        if (sscanf(value,"d",id))
            return Usage(playerid,"/aforager goto [bush id]");
        
        if (!Iter_Contains(BushForager, id))
            return Error(playerid, "Invalid tree id");
        
        SetPlayerPos(playerid,ForegerData[id][bushPos][0],ForegerData[id][bushPos][1],ForegerData[id][bushPos][2]+0.5);
        SendCustomMessage(playerid,"FORAGER","You've teleported to tree forager ID: %d",id);
    } else Usage(playerid,"/aforager [option]"),SendClientMessage(playerid, COLOR_ARWIN, "[OPTION]: "WHITE_E"create, delete, edit, amount, type");
    return 1;
}
