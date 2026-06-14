#include <YSI\y_hooks>
hook OnPlayerConnect(playerid) {
	TimerCourier[playerid] = -1;
	CourierCrate[playerid] = -1;
	CourierCount[playerid] = -1;
	CourierJob[playerid] = false;
    for(new i; i < 11; i++) {
		CourierStatus[playerid][i] = false;
		MapIconCourier[playerid][i] = -1;
	}
	return 1;
}
