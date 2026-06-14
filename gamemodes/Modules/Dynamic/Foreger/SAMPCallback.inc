
#include <YSI\y_hooks>
hook OnGameModeExit() {
    foreach (new i : BushForager) {
        Bush_Save(i);
    }
    return 1;
}

hook OnPlayerConnect(playerid) {
    EditBushForager[playerid] = -1;
    pForaging[playerid] = -1;
    pForager[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid) {
    EditBushForager[playerid] = -1;
    pForaging[playerid] = -1;
    pForager[playerid] = -1;
    return 1;
}

hook OnPlayerEditDynObj(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {
    if (EditBushForager[playerid] != -1) {
        switch (response) {
            case EDIT_RESPONSE_CANCEL: {
                new id = EditBushForager[playerid],Float:position[3],Float:rotation[3];

                Streamer_GetFloatData(STREAMER_TYPE_OBJECT,ForegerData[id][bushObject],E_STREAMER_X,position[0]);
                Streamer_GetFloatData(STREAMER_TYPE_OBJECT,ForegerData[id][bushObject],E_STREAMER_Y,position[1]);
                Streamer_GetFloatData(STREAMER_TYPE_OBJECT,ForegerData[id][bushObject],E_STREAMER_Z,position[2]);
                Streamer_GetFloatData(STREAMER_TYPE_OBJECT,ForegerData[id][bushObject],E_STREAMER_R_X,rotation[0]);
                Streamer_GetFloatData(STREAMER_TYPE_OBJECT,ForegerData[id][bushObject],E_STREAMER_R_Y,rotation[1]);
                Streamer_GetFloatData(STREAMER_TYPE_OBJECT,ForegerData[id][bushObject],E_STREAMER_R_Z,rotation[2]);
                SetDynamicObjectPos(objectid,position[0],position[1],position[2]);
                SetDynamicObjectRot(objectid,rotation[0],rotation[1],rotation[2]);

                EditBushForager[playerid] = -1;
                SendCustomMessage(playerid,"FORAGER","You've canceled editing bush.");
            }
            case EDIT_RESPONSE_FINAL: {
                new id = EditBushForager[playerid];

                ForegerData[id][bushPos][0] = x;
                ForegerData[id][bushPos][1] = y;
                ForegerData[id][bushPos][2] = z;
                ForegerData[id][bushRot][0] = rx;
                ForegerData[id][bushRot][1] = ry;
                ForegerData[id][bushRot][2] = rz;
                
                SetDynamicObjectPos(objectid,x,y,z);
                SetDynamicObjectRot(objectid,rx,ry,rz);
                Bush_Refresh(id);
                Bush_Save(id);

                EditBushForager[playerid] = -1;
                SendCustomMessage(playerid,"FORAGER","Bush position has been saved.");
            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if((newkeys & KEY_NO) && !(oldkeys & KEY_NO) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
    // if(newkeys & KEY_NO && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        new id = -1;
        if ((id = Bush_Nearest(playerid)) != -1) {
            if(DelayPlayer[playerid][DelayForager])
                return Error(playerid, "You must wait for %d minute(s)", (DelayPlayer[playerid][DelayForager]/60));

            if (ForegerData[id][bushAmount] < 1) return Error(playerid, "This bush has no berries!");
            if (pData[playerid][pBushForager] >= 100) return Error(playerid, "Cannot carry more than 100 berries!");
            if (pForaging[playerid] == 1) return Error(playerid, "You're being foraging");
            PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Picking Berries");
            for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
            SetPVarInt(playerid, "nearTreeForager", id);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 1, 0, 1);
            pForager[playerid] = 0;
            pForaging[playerid] = 1;
        }
    }
    return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid) {
    foreach(new id : BushForager) if(areaid == ForegerData[id][bushArea]) {
        if (ForegerData[id][bushAmount] < 1) GameTextForPlayer(playerid, "~p~Berry Bush~n~~r~No Berries Available~n~To Harvest", 3000, 4);
        else GameTextForPlayer(playerid, "~p~Berry Bush~n~~w~Hold '~y~N~w~' to harvest~n~~w~berries", 3000, 4);
    }
    return 1;
}