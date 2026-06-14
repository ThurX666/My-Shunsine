#include <YSI\y_hooks>

hook OnPlayerDisconnect(playerid, reason) {
    if(pData[playerid][pSideJob] == 401) {
        SetVehicleToRespawn(GetPlayerVehicleID(playerid));
        if(IsValidDynamicObject(CoreVehicles[GetPlayerVehicleID(playerid)][vehObject])) DestroyDynamicObject(CoreVehicles[GetPlayerVehicleID(playerid)][vehObject]);
    }
    return 1;
}

hook OnPlayerEnterRaceCP(playerid) {
    if(pData[playerid][pSideJob] == 401) {
        if(IsPlayerInAnyVehicle(playerid)) {
            if(RuteForklift[playerid] > -1) {
                if(forkliftrute[RuteForklift[playerid]][forklift_load] == 1) {
                    if(++CountForklift[playerid] < 10) {
                        new vehicleid = GetPlayerVehicleID(playerid);
                        if(IsValidDynamicObject(CoreVehicles[vehicleid][vehObject])) DestroyDynamicObject(CoreVehicles[vehicleid][vehObject]);
                        RuteForklift[playerid] = RandomEx(4, 8);
                        SetPlayerRaceCheckpoint(playerid, 1, forkliftrute[RuteForklift[playerid]][forklift_posx], forkliftrute[RuteForklift[playerid]][forklift_posy], forkliftrute[RuteForklift[playerid]][forklift_posz], 0, 0, 0, 3);
                    } else {
                        RuteForklift[playerid] = 9;
                        SetPlayerRaceCheckpoint(playerid, 1, forkliftrute[RuteForklift[playerid]][forklift_posx], forkliftrute[RuteForklift[playerid]][forklift_posy], forkliftrute[RuteForklift[playerid]][forklift_posz], 0, 0, 0, 3);
                    }
                }
                else if(forkliftrute[RuteForklift[playerid]][forklift_load] == 2) {
                    pData[playerid][pActivity] = SetTimerEx("ForkliftJob", 250, true, "i", playerid);
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Load Crate");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                }
                else if(forkliftrute[RuteForklift[playerid]][forklift_load] == 3) {
                    pData[playerid][pSideJob] = 0;
                    DelayPlayer[playerid][DelayForklift] = 1800;
                    DisablePlayerCheckpoint(playerid);
                    GivePlayerMoneyEx(playerid, 17500);
                    SendClientMessageEx(playerid, COLOR_ARWIN, "SIDEJOB: "WHITE_E"You've earned "GREEN_E"$175.00 "WHITE_E"for finishing forklift sidejob");
                    RemovePlayerFromVehicle(playerid);
                    SetVehicleToRespawn(GetPlayerVehicleID(playerid));
                    DisablePlayerRaceCheckpoint(playerid);
                    if(IsValidDynamicObject(CoreVehicles[GetPlayerVehicleID(playerid)][vehObject])) DestroyDynamicObject(CoreVehicles[GetPlayerVehicleID(playerid)][vehObject]);
                }
            }
        }
    }
    return 1;
}
