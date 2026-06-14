#include <YSI\y_hooks>

hook OnGameModeInit() {
    new string[512];
    format(string, sizeof(string), "{00FFFF}Miner Sidejob\n"YELLOW_E"'/startmine' "WHITE_E"To start mining\n"YELLOW_E"'/stopmine' "WHITE_E" To stop mining");
    CreateDynamicPickup(1239, 23, 2822.4126,2839.3374,48.3318, -1);
	CreateDynamic3DTextLabel(string, COLOR_ARWIN, 2822.4126,2839.3374,48.3318, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // ID Card
    return 1;
}

hook OnPlayerConnect(playerid) {
    pTimeMiningOre[playerid] = 0;
    pMiningOre[playerid] = 0;
    pTotalCashOre[playerid] = 0;
    pData[playerid][pStartMine] = 0;
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
    if((newkeys & KEY_NO) && !(oldkeys & KEY_NO) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
    // if((newkeys & KEY_NO) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        foreach (new id : Ores) if (IsPlayerInDynamicArea(playerid, OreData[id][oreArea])) {
            if(pData[playerid][pStartMine] < 1) return Error(playerid, "Anda harus menggunakan command '/startmine' untuk menambang ore!");
            if (OreData[id][oreGettingMiner] == true) return Error(playerid, "Ore tidak ada!");
            if (pData[playerid][pEnergy] < 20.0) return Error(playerid, "Tidak bisa menambang, kamu kehausan");
            if (pMiningOre[playerid] == 1) return Error(playerid, "You're being mining ore");
            PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Mining Ore");
            for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
            SetPVarInt(playerid, "nearOree", id);
            ApplyAnimation(playerid, "BASEBALL", "Bat_4", 4.1, 1, 0, 0, 1, 0, 1);
            OreData[id][oreGettingMiner] = true;
            pTimeMiningOre[playerid] = 0;
            pMiningOre[playerid] = 1;
        }
    }
    return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid) {
    if(!pData[playerid][IsLoggedIn]) return 0;
    foreach(new id : Ores) if(areaid == OreData[id][oreArea]) {
        if(OreData[id][oreGettingMiner] == false) GameTextForPlayer(playerid, "~p~MINIABLE ORE~n~~w~HOLD ~r~N ~w~MINE ORE", 3000, 4);
    }
    return 1;
}
