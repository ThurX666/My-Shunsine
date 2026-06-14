
function GYMObject_Load() {
    new rows = cache_num_rows(),
        slot = cellmin,
        string[128];

    if (rows) {
        for (new i = 0; i < rows; i ++) if ((slot = Iter_Free(GYMObjects)) != cellmin) {
            Iter_Add(GYMObjects, slot);

            cache_get_value_int(i, "ID", GYMObject[slot][objectID]);
            cache_get_value_int(i, "BizID", GYMObject[slot][objectBiz]);
            cache_get_value_int(i, "Model", GYMObject[slot][objectModel]);
            cache_get_value_int(i, "Int", GYMObject[slot][objectInt]);
            cache_get_value_int(i, "Vw", GYMObject[slot][objectVw]);
            cache_get_value(i, "Position", string);
            sscanf(string, "p<|>fff", GYMObject[slot][objectPos][0], GYMObject[slot][objectPos][1], GYMObject[slot][objectPos][2]);
            cache_get_value(i, "Rotation", string);
            sscanf(string, "p<|>fff", GYMObject[slot][objectRot][0], GYMObject[slot][objectRot][1], GYMObject[slot][objectRot][2]);
            cache_get_value_int(i, "Type", GYMObject[slot][objectType]);
            cache_get_value_int(i, "Condition", GYMObject[slot][objectCondition]);
            GYMObject[slot][objectStatus] = 1;
            GYMObject_Refresh(slot);
        }
    }
    return 1;
}

function OnGYMObjectCreated(id) {
    GYMObject[id][objectID] = cache_insert_id();
    GYMObject_Save(id);
    return 1;
}

GYMObject_Refresh(id) {
    if (!Iter_Contains(GYMObjects, id))
        return 0;

    if (!IsValidDynamicObject(GYMObject[id][objectgym])) {
        GYMObject[id][objectgym] = CreateDynamicObject(GYMObject[id][objectModel], GYMObject[id][objectPos][0], GYMObject[id][objectPos][1], GYMObject[id][objectPos][2], GYMObject[id][objectRot][0], GYMObject[id][objectRot][1], GYMObject[id][objectRot][2], GYMObject[id][objectVw], GYMObject[id][objectInt]);
    }
    GYMObject_Update(id);
    if (IsValidDynamic3DTextLabel(GYMObject[id][objectLabel])) DestroyDynamic3DTextLabel(GYMObject[id][objectLabel]);

    new string[212];
    format(string, sizeof(string), ""AQUA_E"[id:%d]\n%s\n"WHITE_E"Durability"YELLOW_E"%d"WHITE_E"/3000",id, GetGYMObjectStatus(id), GYMObject[id][objectCondition]);
    GYMObject[id][objectLabel] = CreateDynamic3DTextLabel(string, COLOR_ARWIN, GYMObject[id][objectPos][0], GYMObject[id][objectPos][1], GYMObject[id][objectPos][2]+1, 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GYMObject[id][objectVw], GYMObject[id][objectInt], -1, 5);
    return 1;
}

GetGYMObjectStatus(id) {
    new output[24];
    switch (GYMObject[id][objectStatus]) {
        case 1: format(output,sizeof(output),GREEN_E"Available");
        case 2: format(output,sizeof(output),RED_E"Unavailable");
        case 3: format(output,sizeof(output),RED_E"Broken");
        case 4: format(output,sizeof(output),YELLOW_E"In use");
    }
    return output;
}

GYMObject_Update(id) {
    new objectid = GYMObject[id][objectgym];

    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_X, GYMObject[id][objectPos][0]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Y, GYMObject[id][objectPos][1]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_Z, GYMObject[id][objectPos][2]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_X, GYMObject[id][objectRot][0]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Y, GYMObject[id][objectRot][1]);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_R_Z, GYMObject[id][objectRot][2]);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_WORLD_ID, GYMObject[id][objectVw]);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_INTERIOR_ID, GYMObject[id][objectInt]);
    return 1;
}

GYMObject_Add(bizid, modelid, type, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, int, vw) {
    static
        string[64],
        id = cellmin;

    if ((id = Iter_Free(GYMObjects)) != cellmin) {
        Iter_Add(GYMObjects, id);

        GYMObject[id][objectModel] = modelid;
        GYMObject[id][objectBiz] = bizid;
        GYMObject[id][objectInt] = int;
        GYMObject[id][objectVw] = vw;
        GYMObject[id][objectPos][0] = x;
        GYMObject[id][objectPos][1] = y;
        GYMObject[id][objectPos][2] = z;
        GYMObject[id][objectRot][0] = rx;
        GYMObject[id][objectRot][1] = ry;
        GYMObject[id][objectRot][2] = rz;
        GYMObject[id][objectType] = type;
        GYMObject[id][objectCondition] = 3000;
        GYMObject[id][objectStatus] = 1;
        
        GYMObject_Refresh(id);

        format(string,sizeof(string),"INSERT INTO `gymobjects` (`Model`) VALUES ('%d')", GYMObject[id][objectModel]);
        mysql_tquery(g_SQL, string, "OnGYMObjectCreated", "d", id);

        return id;
    }
    return cellmin;
}

GYMObject_Save(id) {
    new query[512];
    format(query, sizeof(query), "UPDATE `gymobjects` SET `Model`='%d', `BizID`='%d', `Int`='%d', `Vw`='%d', `Position`='%.2f|%.2f|%.2f', `Rotation`='%.2f|%.2f|%.2f', `Condition`='%d', `Type`='%d' WHERE `ID`='%d'",
        GYMObject[id][objectModel],
        GYMObject[id][objectBiz],
        GYMObject[id][objectInt],
        GYMObject[id][objectVw],
        GYMObject[id][objectPos][0],
        GYMObject[id][objectPos][1],
        GYMObject[id][objectPos][2],
        GYMObject[id][objectRot][0],
        GYMObject[id][objectRot][1],
        GYMObject[id][objectRot][2],
        GYMObject[id][objectCondition],
        GYMObject[id][objectType],
        GYMObject[id][objectID]
    );
    mysql_tquery(g_SQL, query);
    return 1;
}

GYMObject_Destroy(id) {
    if (!Iter_Contains(GYMObjects, id))
        return 0;

    if (IsValidDynamicObject(GYMObject[id][objectgym])) DestroyDynamicObject(GYMObject[id][objectgym]);
    if (IsValidDynamic3DTextLabel(GYMObject[id][objectLabel])) DestroyDynamic3DTextLabel(GYMObject[id][objectLabel]);
    GYMObject[id][objectgym] = INVALID_STREAMER_ID;

    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `gymobjects` WHERE `ID`='%d'", GYMObject[id][objectID]);
    mysql_tquery(g_SQL, query);
    Iter_Remove(GYMObjects, id);
    return 1;
}

GYMObject_Nearest(playerid) {
    foreach (new i : GYMObjects) if (IsPlayerInRangeOfPoint(playerid, 3.0, GYMObject[i][objectPos][0], GYMObject[i][objectPos][1], GYMObject[i][objectPos][2])) {
        if(GetPlayerInterior(playerid) == GYMObject[i][objectInt] && GetPlayerVirtualWorld(playerid) ==  GYMObject[i][objectVw]) return i;
    }
    return -1;
}

SetPlayerFitnessAnimation(playerid) {
    switch (PlayerInGym[playerid][1]) {
        case 1: ApplyAnimation(playerid, "GYMNASIUM", "gym_bike_faster", 4.1, 1, 0, 0, 1, 0, 1);
        case 2: ApplyAnimation(playerid, "GYMNASIUM", "gym_tread_sprint", 4.1, 1, 0, 0, 1, 0, 1);
        case 3: ApplyAnimation(playerid, "GYMNASIUM", "GYMshadowbox", 4.1, 1, 0, 0, 1, 0, 1);
    }
    return 1;
}

FinishFitness(playerid) {
    new Float:oldvar, Float:rand;
    switch (PlayerInGym[playerid][1]) {
        case 1: {
            oldvar = pData[playerid][pFitnessRating][1];
            oldvar = pData[playerid][pFitnessRating][2];
            oldvar = pData[playerid][pFitnessRating][3];
            oldvar = pData[playerid][pFitnessRating][4];
            oldvar = pData[playerid][pFitnessRating][5];
            if(PlayerInGym[playerid][2] >= 25) {
                rand = RandomFloat(1.0,1.5);
                pData[playerid][pFitnessRating][1] += rand;
                pData[playerid][pFitnessRating][2] += rand;
                pData[playerid][pFitnessRating][3] +=rand;
                pData[playerid][pFitnessRating][4] += rand;
                pData[playerid][pFitnessRating][5] += rand;
            }
            SendClientMessageEx(playerid, COLOR_ARWIN, "Fitness Report:\n");
            if (pData[playerid][pFitnessRating][1] >= 150.0) pData[playerid][pFitnessRating][1] = 150.0;
            if (pData[playerid][pFitnessRating][2] >= 150.0) pData[playerid][pFitnessRating][2] = 150.0;
            if (pData[playerid][pFitnessRating][3] >= 150.0) pData[playerid][pFitnessRating][3] = 150.0;
            if (pData[playerid][pFitnessRating][4] >= 150.0) pData[playerid][pFitnessRating][4] = 150.0;
            if (pData[playerid][pFitnessRating][5] >= 150.0) pData[playerid][pFitnessRating][5] = 150.0;
            
            SendCustomMessage(playerid, ""YELLOW_E"Groin", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][1]);
            SendCustomMessage(playerid, ""YELLOW_E"Right Arm", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][2]);
            SendCustomMessage(playerid, ""YELLOW_E"Left Arm", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][3]);
            SendCustomMessage(playerid, ""YELLOW_E"Right Leg", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][4]);
            SendCustomMessage(playerid, ""YELLOW_E"Left Leg", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][5]);
        }
        case 2: {
            oldvar = pData[playerid][pFitnessRating][0];
            oldvar = pData[playerid][pFitnessRating][1];
            oldvar = pData[playerid][pFitnessRating][2];
            oldvar = pData[playerid][pFitnessRating][3];
            oldvar = pData[playerid][pFitnessRating][4];
            oldvar = pData[playerid][pFitnessRating][5];
            if(PlayerInGym[playerid][2] >= 25) {
                rand = RandomFloat(1.0,1.5);
                pData[playerid][pFitnessRating][0] +=rand;
                pData[playerid][pFitnessRating][1] += rand;
                pData[playerid][pFitnessRating][2] += rand;
                pData[playerid][pFitnessRating][3] += rand;
                pData[playerid][pFitnessRating][4] += rand;
                pData[playerid][pFitnessRating][5] += rand;
            }
            SendClientMessageEx(playerid, COLOR_ARWIN, "Fitness Report:\n");
            if (pData[playerid][pFitnessRating][0] >= 150.0) pData[playerid][pFitnessRating][0] = 150.0;
            if (pData[playerid][pFitnessRating][1] >= 150.0) pData[playerid][pFitnessRating][1] = 150.0;
            if (pData[playerid][pFitnessRating][2] >= 150.0) pData[playerid][pFitnessRating][2] = 150.0;
            if (pData[playerid][pFitnessRating][3] >= 150.0) pData[playerid][pFitnessRating][3] = 150.0;
            if (pData[playerid][pFitnessRating][4] >= 150.0) pData[playerid][pFitnessRating][4] = 150.0;
            if (pData[playerid][pFitnessRating][5] >= 150.0) pData[playerid][pFitnessRating][5] = 150.0;

            SendCustomMessage(playerid, ""YELLOW_E"Torso", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][0]);
            SendCustomMessage(playerid, ""YELLOW_E"Groin", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][1]);
            SendCustomMessage(playerid, ""YELLOW_E"Right Arm", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][2]);
            SendCustomMessage(playerid, ""YELLOW_E"Left Arm", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][3]);
            SendCustomMessage(playerid, ""YELLOW_E"Right Leg", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][4]);
            SendCustomMessage(playerid, ""YELLOW_E"Left Leg", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][5]);
        }
        case 3: {
            SendClientMessageEx(playerid, COLOR_ARWIN, "Fitness Report:\n");
            oldvar = pData[playerid][pFitnessRating][0];
            oldvar = pData[playerid][pFitnessRating][2];
            oldvar = pData[playerid][pFitnessRating][3];
            if(PlayerInGym[playerid][2] >= 25) {
                rand = RandomFloat(1.0,1.5);
                pData[playerid][pFitnessRating][0] += rand;
                pData[playerid][pFitnessRating][2] += rand;
                pData[playerid][pFitnessRating][3] += rand;
            }
            SendCustomMessage(playerid, ""YELLOW_E"Torso", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][0]);
            SendCustomMessage(playerid, ""YELLOW_E"Right Arm", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][2]);
            SendCustomMessage(playerid, ""YELLOW_E"Left Arm", ""RED_E"%.2f "WHITE_E"> "GREEN_E"%.2f", oldvar, pData[playerid][pFitnessRating][3]);
        }
    }
    new id = GetPVarInt(playerid, "holdingGYMEquip"), bizid = pData[playerid][pInBiz];
    if (bizid != -1) {
        ClearAnimations(playerid, 1);
        GYMObject[id][objectStatus] = 1;
        GYMObject_Refresh(id);
        DeletePVar(playerid, "holdingGYMEquip");
        PlayerInGym[playerid][0] = PlayerInGym[playerid][1] = PlayerInGym[playerid][2] = 0;
    }
}
