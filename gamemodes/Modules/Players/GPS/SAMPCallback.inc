#include <YSI\y_hooks>
hook OnPlayerEnterRaceCP(playerid) {
	if(GetPVarInt(playerid, "PlayerGPS")) {
        DisablePlayerRaceCheckpoint(playerid);
        DeletePVar(playerid, "PlayerGPS");
        SendClientMessage(playerid, TOMATO, "GPSINFO: You have arrived!");
    }
	return 1;
}
