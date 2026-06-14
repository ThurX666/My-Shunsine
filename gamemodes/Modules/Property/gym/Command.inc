
SSCANF:GYMObjectMenu(string[]) {
    if (!strcmp(string, "create", true)) return 1;
    else if (!strcmp(string, "edit", true)) return 2;
    else if (!strcmp(string, "delete", true)) return 3;
    else if (!strcmp(string, "condition", true)) return 4;
    else if (!strcmp(string, "biz", true)) return 5;
    else if (!strcmp(string, "goto", true)) return 6;
    return 0;
}

// GYM SYSTEM
CMD:gymobject(playerid, params[]) {
    if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");

    new id, action, subparam[64];
    if (sscanf(params, "k<GYMObjectMenu>S()[64]", action, subparam))
        return Usage(playerid, "/gymobject [create/edit/delete/condition/biz/goto]");

    switch (action) {
        case 1: {
            new bizid, type[10];
            if (sscanf(subparam, "ds[10]", bizid, type))
                return Usage(playerid, "/gymobject create [bizid] [bike/treadmill/boxing]");

            if(!Iter_Contains(Bisnis, bizid)) return Error(playerid, "The bisnis you specified ID of doesn't exist.");

            new Float:pos[4];
            GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
            GetPlayerFacingAngle(playerid, pos[3]);

            if (!strcmp(type, "bike", true)) {
                id = GYMObject_Add(bizid, 2630, 1, pos[0], pos[1], pos[2], 0.0, 0.0, pos[3], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

                if (id == cellmin)
                    return Error(playerid, "Server has been reached the maximum of GYM Object");

                SendCustomMessage(playerid, "GYMOBJECT", "You've been created gym object id: "YELLOW_E"%d", id);
            } else if (!strcmp(type, "treadmill", true)) {
                id = GYMObject_Add(bizid, 2627, 2, pos[0], pos[1], pos[2], 0.0, 0.0, pos[3], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

                if (id == cellmin)
                    return Error(playerid, "Server has been reached the maximum of GYM Object");

                SendCustomMessage(playerid, "GYMOBJECT", "You've been created gym object id: "YELLOW_E"%d", id);
            } else if (!strcmp(type, "boxing", true)) {
                id = GYMObject_Add(bizid, 1985, 3, pos[0], pos[1], pos[2], 0.0, 0.0, pos[3], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));

                if (id == cellmin)
                    return Error(playerid, "Server has been reached the maximum of GYM Object");

                SendCustomMessage(playerid, "GYMOBJECT", "You've been created gym object id: "YELLOW_E"%d", id);
            } else Error(playerid, "Invalid type!");
        }
        case 2: {
            if (sscanf(subparam, "d", id))
                return Usage(playerid, "/gymobject edit [gymobject id]");

            if (!Iter_Contains(GYMObjects, id))
                return Error(playerid, "Invalid gymobject id!");

            pData[playerid][pEditGYMObject] = id;
            pData[playerid][pEditingMode] = 5;
            EditDynamicObject(playerid, GYMObject[id][objectgym]);
            SendCustomMessage(playerid, "GYMOBJECT", "You're now editing gymobject id: "YELLOW_E"%d", id);
        }
        case 3: {
            if (sscanf(subparam, "d", id))
                return Usage(playerid, "/gymobject delete [gymobject id]");

            if (!Iter_Contains(GYMObjects, id))
                return Error(playerid, "Invalid gymobject id!");

            GYMObject_Destroy(id);
            SendCustomMessage(playerid, "GYMOBJECT", "You've been deleted gymobject id: "YELLOW_E"%d", id);
        }
        case 4: {
            new amount;
            if (sscanf(subparam, "dd", id, amount))
                return Usage(playerid, "/gymobject condition [gymobject id] [amount]");

            if (!Iter_Contains(GYMObjects, id))
                return Error(playerid, "Invalid gymobject id!");

            new bizid = pData[playerid][pInBiz];

            if (bizid != -1) {
                GYMObject[id][objectCondition] = amount;
                GYMObject_Refresh(id);
                GYMObject_Save(id);
                SendCustomMessage(playerid, "GYMOBJECT", "You've been set condition of gymobject id: "YELLOW_E"%d "WHITE_E"to "YELLOW_E"%d", id, amount);
            }
        }
        case 5: {
            new bizid;
            if (sscanf(subparam, "dd", id, bizid))
                return Usage(playerid, "/gymobject biz [gymobject id] [biz id]");

            if (!Iter_Contains(GYMObjects, id))
                return Error(playerid, "Invalid gymobject id!");

            GYMObject[id][objectBiz] = bizid;
            GYMObject_Save(id);
            SendCustomMessage(playerid, "GYMOBJECT", "You've been set biz id of gymobject id: "YELLOW_E"%d "WHITE_E"to "YELLOW_E"%d", id, bizid);
        }
        case 6: {
            if (sscanf(subparam, "d", id))
                return Usage(playerid, "/gymobject goto [gymobject id]");

            if (!Iter_Contains(GYMObjects, id))
                return Error(playerid, "Invalid gymobject id!");

            SetPlayerPos(playerid, GYMObject[id][objectPos][0], GYMObject[id][objectPos][1], GYMObject[id][objectPos][2]);
            SetPlayerFacingAngle(playerid, GYMObject[id][objectRot][2]);

            SendCustomMessage(playerid, "TELE", "You've been teleported gymobject id: "YELLOW_E"%d", id);
        }
        default: Usage(playerid, "/gymobject [create/edit/delete/condition/biz/goto]");
    }
    return 1;
}

CMD:fitness(playerid, params[]) {
    new bizid = -1;

    if ((bizid = pData[playerid][pInBiz]) != -1 && bData[bizid][bType] == 6) {
        if (pData[playerid][pGYMMember] != pData[playerid][pInBiz])
            return Error(playerid, "You don't have any valid GYM Membership on this GYM.");

        if (pData[playerid][pEnergy] <= 20.0) return Error(playerid, "You're thirsty right now!");
        if (PlayerInGym[playerid][0] > 0) return Error(playerid, "You're being fitness right now, use '/stopfitness' to stop fitness");

        new id = -1;
        if ((id = GYMObject_Nearest(playerid)) != -1) {
            if (GYMObject[id][objectStatus] == 4 || GYMObject[id][objectStatus] == 3)
                return Error(playerid, "This GYM Fitness is being used by other players or has already broken!");

            PlayerInGym[playerid][0] = floatround(pData[playerid][pEnergy] - 20.0);
            PlayerInGym[playerid][1] = GYMObject[id][objectType];
            GYMObject[id][objectStatus] = 4;
            PlayerEquipGym[playerid] = id;
            SetPVarInt(playerid, "holdingGYMEquip", id);
            new Float:rot[3];
            GetDynamicObjectRot(GYMObject[id][objectgym], rot[0], rot[1], rot[2]);
            // if (PlayerInGym[playerid][1] == 1) {
            //     SetPlayerPos(playerid, GYMObject[id][objectPos][0]+0.5, GYMObject[id][objectPos][1], GYMObject[id][objectPos][2]+0.5);
            //     SetPlayerFacingAngle(playerid, rot[2]+180);
            // } else if (PlayerInGym[playerid][1] == 2) {
            //     SetPlayerPos(playerid, GYMObject[id][objectPos][0], GYMObject[id][objectPos][1], GYMObject[id][objectPos][2]+0.5);
            //     SetPlayerFacingAngle(playerid, rot[2]);
            // }
            if (PlayerInGym[playerid][1] == 1) {
                SetPlayerPos(playerid, GYMObject[id][objectPos][0]+0.5, GYMObject[id][objectPos][1]-0.5, GYMObject[id][objectPos][2]);
                SetPlayerFacingAngle(playerid, rot[2]+180);
            } else if (PlayerInGym[playerid][1] == 2) {
                SetPlayerPos(playerid, GYMObject[id][objectPos][0], GYMObject[id][objectPos][1]+1.5, GYMObject[id][objectPos][2]+0.5);
                SetPlayerFacingAngle(playerid, rot[2]);
            }
            SetCameraBehindPlayer(playerid);
            SetPlayerFitnessAnimation(playerid);
            //GYMObject_Refresh(id, bizid);
            Info(playerid, "%d equip", id);
            SendCustomMessage(playerid, "FITNESS", "{FFFFFF}Fitness started, use command '{FFFF00}/stopfitness{FFFFFF}' to stop this action.");
        } else Error(playerid, "You're not in any GYM Fitness");
    } else Error(playerid, "You're not in any GYM.");
    return 1;
}

CMD:stopfitness(playerid) {
    if (!PlayerInGym[playerid][0])
        return Error(playerid, "You're not in fitness.");

    new id = GetPVarInt(playerid, "holdingGYMEquip"), bizid = pData[playerid][pInBiz];
    if (bizid != -1) {
        ClearAnimations(playerid, 1);
        FinishFitness(playerid);
        GYMObject[id][objectStatus] = 1;
        GYMObject_Refresh(id);
        DeletePVar(playerid, "holdingGYMEquip");
        PlayerInGym[playerid][0] = PlayerInGym[playerid][1] = PlayerInGym[playerid][1] = -1;
    }
    return 1;
}

CMD:repairgymequip(playerid, params[]) {
    new id = -1;
    if (sscanf(params, "d", id)) return Usage(playerid, "/repairgymequip [id gym]");
    if(pData[playerid][pInBiz] == -1) return 0;
	if(!Player_OwnsBisnis(playerid, pData[playerid][pInBiz]) && !Business_IsEmployee(playerid, pData[playerid][pInBiz])) return Error(playerid, "You don't own this bisnis.");
    if(pData[playerid][pComponent] < 100) return Error(playerid, "Minimal harus mempunyai 100 komponen untuk memperbaiki GYM Equipment.");
    if(GYMObject[id][objectCondition] > 2500) return Error(playerid, "This GYM Equip condition is good.");
    SetPVarInt(playerid, "pMekanik", 1);
    SetPVarInt(playerid, "pMekanikTime", 0);
    SetPVarInt(playerid, "pMekanikID", id);
    return 1;
}
