#include <YSI\y_hooks>

hook OnGameModeExit()
{
	foreach(new vehicleid : VehicleData) SaveVehicleData(vehicleid);
    Iter_Clear(VehicleData);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
	// foreach(new vehicleid : VehicleData) if(!strcmp(VehicleData[vehicleid][VehicleOwner], pData[playerid][pName], true)) {
	//	VehicleData[vehicleid][VehicleSpawnTime] = 300;
	// }
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(newstate == PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_PASSENGER)
	{
		foreach(new vehicle : VehicleData) if(VehicleData[vehicle][Vehicle] == vehicleid) {
			if(VehicleData[vehicle][Storage][0] > 0) {
				TextDrawShowForPlayer(playerid, PlayerCrateTD);
				PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
				PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
				new String2[212];
				format(String2,sizeof(String2),"Product Stock~n~%d units", VehicleData[vehicle][Storage][0]);
				PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
			}
			if(IsFactionVeh(vehicleid)) {
				if(VehicleData[vehicle][Faction] != pData[playerid][pFaction]) {
					new Float:x, Float:y, Float:z;
					GetPlayerPos(playerid, x, y, z);
					SetPlayerPos(playerid, x, y, z);
					Error(playerid, "You're not member of this faction.");
					return 1;
				}
			}
			if(IsBisnisVeh(vehicleid)) {
				if(!Player_OwnsBisnis(playerid, VehicleData[vehicle][Bisnis]) && !Business_IsEmployee(playerid, VehicleData[vehicle][Bisnis])) {
					new Float:x, Float:y, Float:z;
					GetPlayerPos(playerid, x, y, z);
					SetPlayerPos(playerid, x, y, z);
					Error(playerid, "You're not employee or owner of this business.");
					return 1;
				}
			}
			if(IsWorkshopVeh(vehicleid)) {
				if(!OwnerWorkshop(playerid, VehicleData[vehicle][Workshop]) && !Workshop_IsEmployee(playerid, VehicleData[vehicle][Workshop])) {
					new Float:x, Float:y, Float:z;
					GetPlayerPos(playerid, x, y, z);
					SetPlayerPos(playerid, x, y, z);
					Error(playerid, "You're not employee or owner of this business.");
					return 1;
				}
			}
		}
	}
    return 1;
}

hook OnPlayerExitVehicle(playerid, vehicleid)
{
	foreach(new vehicle : VehicleData) if(VehicleData[vehicle][Vehicle] == vehicleid) {
		GetVehicleDamageStatus(VehicleData[vehicle][Vehicle], VehicleData[vehicle][Damage][0], VehicleData[vehicle][Damage][1], VehicleData[vehicle][Damage][2], VehicleData[vehicle][Damage][3]);
		GetVehicleHealth(VehicleData[vehicle][Vehicle], VehicleData[vehicle][Health]);
		VehicleData[vehicle][Fuel] = GetVehicleFuel(VehicleData[vehicle][Vehicle]);
	}
	return 1;
}	
