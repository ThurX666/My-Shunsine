
function Bush_Load() {
    new rows = cache_num_rows(), str[65];
    for (new i = 0; i < rows; i ++) {
        Iter_Add(BushForager, i);

        cache_get_value_int(i, "ID", ForegerData[i][bushID]);
        cache_get_value_int(i, "Type", ForegerData[i][bushType]);
        cache_get_value_int(i, "Amount", ForegerData[i][bushAmount]);

        cache_get_value(i, "Position", str);
        sscanf(str, "p<|>fff", ForegerData[i][bushPos][0], ForegerData[i][bushPos][1], ForegerData[i][bushPos][2]);

        cache_get_value(i, "Rotation", str);
        sscanf(str, "p<|>fff", ForegerData[i][bushRot][0], ForegerData[i][bushRot][1], ForegerData[i][bushRot][2]);

        Bush_Refresh(i);
    }
    printf("*** [Database: Loaded] bush forager data loaded (%d count)", rows);
    return 1;
}

Bush_Refresh(id) {
    if (!Iter_Contains(BushForager, id))
        return 0;
    
    if (!IsValidDynamicObject(ForegerData[id][bushObject]))
        ForegerData[id][bushObject] = CreateDynamicObject(ForegerData[id][bushType], ForegerData[id][bushPos][0], ForegerData[id][bushPos][1], ForegerData[id][bushPos][2], ForegerData[id][bushRot][0], ForegerData[id][bushRot][1], ForegerData[id][bushRot][2], 0, 0);
    if (!IsValidDynamicArea(ForegerData[id][bushArea]))
        ForegerData[id][bushArea] = CreateDynamicSphere(ForegerData[id][bushPos][0], ForegerData[id][bushPos][1], ForegerData[id][bushPos][2], 3, 0, 0);
    Bush_Update(id);
    return 1;
}

Bush_Update(id) {
    if (!Iter_Contains(BushForager, id))
        return 0;
    if (IsValidDynamicArea(ForegerData[id][bushArea])) {
        Streamer_SetFloatData(STREAMER_TYPE_AREA, ForegerData[id][bushArea], E_STREAMER_X, ForegerData[id][bushPos][0]);
        Streamer_SetFloatData(STREAMER_TYPE_AREA, ForegerData[id][bushArea], E_STREAMER_Y, ForegerData[id][bushPos][1]);
        Streamer_SetFloatData(STREAMER_TYPE_AREA, ForegerData[id][bushArea], E_STREAMER_Z, ForegerData[id][bushPos][2]);
    }
    if (IsValidDynamicObject(ForegerData[id][bushObject])) {
        new objectid = ForegerData[id][bushObject];

        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_X, ForegerData[id][bushPos][0]);
        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Y, ForegerData[id][bushPos][1]);
        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Z, ForegerData[id][bushPos][2]);
        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_X, ForegerData[id][bushRot][0]);
        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Y, ForegerData[id][bushRot][1]);
        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Z, ForegerData[id][bushRot][2]);

        Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_WORLD_ID, 0);
        Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_INTERIOR_ID, 0);
    }
    return 1;
}

Bush_Create(type, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0) {
    new id = cellmin;

    if ((id = Iter_Free(BushForager)) != cellmin) {
        Iter_Add(BushForager, id);

        ForegerData[id][bushType] = type;
        ForegerData[id][bushPos][0] = x;
        ForegerData[id][bushPos][1] = y;
        ForegerData[id][bushPos][2] = z;
        ForegerData[id][bushRot][0] = rx;
        ForegerData[id][bushRot][1] = ry;
        ForegerData[id][bushRot][2] = rz;
        ForegerData[id][bushAmount] = 100;
        Bush_Refresh(id);

        mysql_tquery(g_SQL, sprintf("INSERT INTO `bush_forager` (`Type`) VALUES ('%d')",ForegerData[id][bushType]), "OnBushCreated", "d", id);

        return id;
    }
    return cellmin;
}

function OnBushCreated(id) {
    if (!Iter_Contains(BushForager, id))
        return 0;

    ForegerData[id][bushID] = cache_insert_id();
    Bush_Save(id);
    return 1;
}

Bush_Delete(id) {
    if (!Iter_Contains(BushForager, id))
        return 0;
    
    if (IsValidDynamicObject(ForegerData[id][bushObject])) DestroyDynamicObject(ForegerData[id][bushObject]);
    if(IsValidDynamicArea(ForegerData[id][bushArea])) DestroyDynamicArea(ForegerData[id][bushArea]);
    ForegerData[id][bushObject] = INVALID_STREAMER_ID;
    ForegerData[id][bushPos][0] = ForegerData[id][bushPos][1] = ForegerData[id][bushPos][2] = 0.0;
    ForegerData[id][bushRot][0] = ForegerData[id][bushRot][1] = ForegerData[id][bushRot][2] = 0.0;
    mysql_tquery(g_SQL, sprintf("DELETE FROM `bush_forager` WHERE `ID` = '%d'",ForegerData[id][bushID]));
    Iter_Remove(BushForager, id);
    return 1;
}

Bush_Save(id) {
    if (!Iter_Contains(BushForager, id))
        return 0;
    
    new query[256];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `bush_forager` SET `Type`='%d', `Amount`='%d', `Position`='%.2f|%.2f|%.2f', `Rotation`='%.2f|%.2f|%.2f' WHERE `ID`='%d'",
    ForegerData[id][bushType],
    ForegerData[id][bushAmount],
    ForegerData[id][bushPos][0],
    ForegerData[id][bushPos][1],
    ForegerData[id][bushPos][2],
    ForegerData[id][bushRot][0],
    ForegerData[id][bushRot][1],
    ForegerData[id][bushRot][2],
    ForegerData[id][bushID]);
    return mysql_tquery(g_SQL, query);
}

Bush_Nearest(playerid) {
    foreach (new id : BushForager) if (IsPlayerInDynamicArea(playerid, ForegerData[id][bushArea])) {
        if (GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0) return id;
    }
    return -1;
}
