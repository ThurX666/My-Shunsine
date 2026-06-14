
ptask repairGYMEquip[800](playerid) 
{
    new id = GetPVarInt(playerid, "pMekanikID");
    if(GetPVarInt(playerid, "pMekanik") > 0) {
        if(pData[playerid][pJob] == 2 || pData[playerid][pJob2] == 2 && GYMObject_Nearest(playerid) == id) {
            SetPVarInt(playerid, "pMekanikTime", GetPVarInt(playerid, "pMekanikTime")+1);
            new string[128];
            format(string,sizeof(string),"~b~Repairing GYM Equipment~n~Waiting for repairing progress for ~g~%d~b~/100", GetPVarInt(playerid, "pMekanikTime"));
            GameTextForPlayer(playerid, string, 1500, 6);

            if(GetPVarInt(playerid, "pMekanikTime") >= 100) {
                GYMObject[id][objectCondition] = 3000;
                UpdateDynamic3DTextLabelText(GYMObject[id][objectLabel], -1, sprintf(""AQUA_E"[id:%d]\n%s\n"WHITE_E"Durability"YELLOW_E"%d"WHITE_E"/3000",id, GetGYMObjectStatus(id), GYMObject[id][objectCondition]));
                pData[playerid][pComponent] -= 100;
                GameTextForPlayer(playerid, "~g~~h~GYM Equipment Fixed!", 1500, 6);
                SetPlayerArmedWeapon(playerid, 0);
                DeletePVar(playerid, "pMekanik");
                DeletePVar(playerid, "pMekanikTime");
                DeletePVar(playerid, "pMekanikID");
                return 1;
            }
        } else {
            DeletePVar(playerid, "pMekanik");
            DeletePVar(playerid, "pMekanikTime");
            DeletePVar(playerid, "pMekanikID");
            SetPlayerArmedWeapon(playerid, 0);
            SendCustomMessage(playerid, "REPAIR","Gagal memperbaiki GYM Equipment, terlalu jauh dari GYM Equipment.");
            return 1;
        }
    }
    return 1;
}

ptask PlayerFitness[1000](playerid)
{
    if(!pData[playerid][IsLoggedIn]) return 0;
    new id = PlayerEquipGym[playerid];
    if (PlayerInGym[playerid][0] > 0 && PlayerInGym[playerid][1]) 
    {   
        GYMObject[id][objectCondition]--;
        PlayerInGym[playerid][0]--;
        PlayerInGym[playerid][2]++;
        SetPlayerEnergy(playerid, pData[playerid][pEnergy]-1.0);
        UpdateDynamic3DTextLabelText(GYMObject[id][objectLabel], -1, sprintf(""AQUA_E"[id:%d]\n%s\n"WHITE_E"Durability"YELLOW_E"%d"WHITE_E"/3000",id, GetGYMObjectStatus(id), GYMObject[id][objectCondition]));
        if (PlayerInGym[playerid][0] == 0 && PlayerInGym[playerid][1]) FinishFitness(playerid);
    }
    return 1;
}
