
ptask PickingBerries[100](playerid) {
    if(Bush_Nearest(playerid) == GetPVarInt(playerid,"nearTreeForager") && pForaging[playerid]) {
        new id = GetPVarInt(playerid,"nearTreeForager");
        pForager[playerid]++;
        SetProgressBar(playerid, pForager[playerid]);
        if (pForager[playerid] >= 100) {
            new rand = RandomEx(5, 10);

            ForegerData[id][bushAmount] -= rand;
            pData[playerid][pBushForager] += rand;
            if (ForegerData[id][bushAmount] < 2) ForegerData[id][bushAmount] = 1;
            Bush_Save(id);

            ClearAnimations(playerid, 1);
            DeletePVar(playerid, "nearTreeForager");
            pForager[playerid] = 0;
            pForaging[playerid] = 0;
            SendCustomMessage(playerid, "FORAGER","{FFFFFF}You have harvested {FFFF00}%d wild berries {FFFFFF}from this bush.", rand);
            HideProgressBar(playerid);
        }
    }
    return 1;
}

task BushUpdate[1000]() 
{
    new second, minute;
    if(++second > 60) {
        second = 0;
        if(++minute > 10) {
            minute = 0;
            foreach (new id : BushForager) if (ForegerData[id][bushAmount] < 5) {
                ForegerData[id][bushAmount]++;
                if (ForegerData[id][bushAmount] > 5) ForegerData[id][bushAmount] = 5;
            }
        }
    }
    return 1;
}