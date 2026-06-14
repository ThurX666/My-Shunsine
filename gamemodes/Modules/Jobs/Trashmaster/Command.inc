
CMD:loadtrash(playerid, params[])
{
    new
        vehicleid = GetPlayerVehicleID(playerid);
    if(!IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Anda tidak berada di dalam kendaraan.");
    if(!IsVehicleTrashmaster(vehicleid)) return Error(playerid, "Ini bukan mobil khusus untuk pekerjaan trashman.");
    for(new id = 0; id < 11; id++) {
        if(IsPlayerInDynamicArea(playerid, TrashmasterDynCP[playerid][id])) {
            if(TrashStatus[playerid][id] == false && pData[playerid][pTrashmasterJob] == 1) {
                CoreVehicles[vehicleid][vehTrash]++;
                TrashStatus[playerid][id] = true;
                RemovePlayerMapIcon(playerid, 50+id);
                SendCustomMessage(playerid, "TRASH", "You have loaded trash into your trashmaster from the gerbage dump, trash loaded "YELLOW_E"%d/10", CoreVehicles[vehicleid][vehTrash]);
                if(CoreVehicles[vehicleid][vehTrash] == 10)
                {
                    SendCustomMessage(playerid, "TRASH", "You have loaded trash into your trashmaster from the gerbage dump, "GREEN_E"your trashmaster is now full");
                    SendCustomMessage(playerid, "TRASH", "Your trashmaster is "GREEN_E"already full"WHITE_E", return to the trash dump to finish sidejob!");
                    SetPlayerRaceCheckpoint(playerid, 1, 2101.2063,-2032.8599,14.0905, 0.0, 0.0, 0.0, 5.0);
                    for(new i; i < 11; i++) RemovePlayerMapIcon(playerid, 50+i);
                    new String2[212];
                    format(String2,sizeof(String2),"Trash~n~%d/10", CoreVehicles[vehicleid][vehTrash]); 
                    PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
                    return 1;
                }
            }
        }
    }
    new String2[212];
    format(String2,sizeof(String2),"Trash~n~%d/10", CoreVehicles[vehicleid][vehTrash]); 
    PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
    return 1;
}
