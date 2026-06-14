#include <YSI\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if ((GetPlayerState(playerid) == PLAYER_STATE_DRIVER) && (newkeys & KEY_CROUCH)) {
		foreach(new id : Tolls) if(IsPlayerInDynamicArea(playerid, TollGate[id][tZone])) {
			TollGate_Operate(playerid, id);
		}	 
	}
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	foreach (new id : Tolls) if(IsPlayerInDynamicArea(playerid, TollGate[id][tZone])) {
		GameTextForPlayer(playerid, "~p~TOLL GATE~n~~w~USE ~R~/PAYTOLL~w~ OR PRESS~n~~r~H~n~~w~TO PAY TOLL FEE", 1000, 4);
	}
    return 1;
}
