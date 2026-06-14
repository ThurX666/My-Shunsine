
ptask MiningOre[100](playerid) {
    if(GetClosestOre(playerid) == GetPVarInt(playerid,"nearOree") && pMiningOre[playerid]) {
        new id = GetPVarInt(playerid,"nearOree");
        pTimeMiningOre[playerid]++;
        SetProgressBar(playerid, pTimeMiningOre[playerid]);
        if (pTimeMiningOre[playerid] >= 100) {
            new rand = RandomEx(0, 3);
            switch(rand) {
                case 0: {
                    new cash = RandomEx(3000, 7000);
                    SendCustomMessage(playerid, "MINER", "You have found "ORANGE_E"Copper ore "WHITE_E"worth "GREEN_E"$%s", FormatMoney(cash));
                    pData[playerid][pMiner] += cash;
                }
                case 1: {
                    new cash = RandomEx(1500, 5000);
                    SendCustomMessage(playerid, "MINER", "You've found "RED_E"Coal ore "WHITE_E"worth "GREEN_E"$%s", FormatMoney(cash));
                    pData[playerid][pMiner] += cash;
                }
                case 2: {
                    new cash = RandomEx(7000, 15000);
                    SendCustomMessage(playerid, "MINER", "You've found "AQUA_E"Diamond ore "WHITE_E"worth "GREEN_E"$%s", FormatMoney(cash));
                    pData[playerid][pMiner] += cash;
                }
            }
            pData[playerid][pEnergy] -= 4.0;
            if(pData[playerid][pEnergy] <= 20.0) {
                pData[playerid][pStartMine] = 0;
                SendCustomMessage(playerid, "SIDEJOB", "Energi kamu habis! Gunakan "YELLOW_E"/stopmine "WHITE_E"untuk mengambil uang mining kamu sebesar "GREEN_E"$%s", FormatMoney(pData[playerid][pMiner]));
                RemovePlayerAttachedObject(playerid, 9);
            }
            OreData[id][oreSeconds] = 300;
            ClearAnimations(playerid, 1);
            DeletePVar(playerid, "nearOree");
            pTimeMiningOre[playerid] = 0;
            pMiningOre[playerid] = 0;
            HideProgressBar(playerid);
        }
    }
    else if(GetClosestOre(playerid) != GetPVarInt(playerid,"nearOree") && pMiningOre[playerid]) {
        ClearAnimations(playerid, 1);
        OreData[GetPVarInt(playerid,"nearOree")][oreGettingMiner] = false;
        DeletePVar(playerid, "nearOree");
        pTimeMiningOre[playerid] = 0;
        pMiningOre[playerid] = 0;
        HideProgressBar(playerid);
    }
    return 1;
}

ptask OreMineUpdate[1000](playerid) 
{
    foreach(new id : Ores) {
        if(OreData[id][oreGettingMiner] == true) {
           if(OreData[id][oreSeconds] > 0) {
                OreData[id][oreSeconds]--; 
                if(OreData[id][oreSeconds] == 0) OreData[id][oreGettingMiner] = false;
           }
        }
        if(IsPlayerInDynamicArea(playerid, OreData[id][oreArea])) {
            if(!pData[playerid][IsLoggedIn]) return 0;
            if(OreData[id][oreSeconds] > 0) GameTextForPlayer(playerid, sprintf("~p~CANNOT BE MINED ORE~n~~w~%d second", OreData[id][oreSeconds]), 3000, 4);
        }
    }
    return 1;
}