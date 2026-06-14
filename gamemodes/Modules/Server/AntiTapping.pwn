forward OnVehUpdate(playerid, vehicleid);

new Timer:onvehicle_timer[MAX_PLAYERS] = {Timer:-1, ...};

#include <YSI\y_hooks>
hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER && GetPlayerVehicleID(playerid) != INVALID_VEHICLE_ID)
	{
		static vehicleid;

		vehicleid = GetPlayerVehicleID(playerid);
		onvehicle_timer[playerid] = repeat OnVehUpdate(playerid, vehicleid);
	}
	else if(oldstate == PLAYER_STATE_DRIVER) {
		stop onvehicle_timer[playerid];
		onvehicle_timer[playerid] = Timer:-1;
	}
	return 1;
}


hook OnPlayerDisconnectEx(playerid)
{
	if(onvehicle_timer[playerid] != Timer:-1) {
		stop onvehicle_timer[playerid];
		onvehicle_timer[playerid] = Timer:-1;
	}
	return 1;
}
