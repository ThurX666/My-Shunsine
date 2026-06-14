
function ForkliftJob(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(!IsPlayerConnected(playerid)) return 0;
    if(pData[playerid][pSideJob] == 401)
	{
		if(pData[playerid][pActivityTime] >= 100)
		{
		    CoreVehicles[vehicleid][vehObject] = CreateDynamicObject(1271,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
		    AttachDynamicObjectToVehicle(CoreVehicles[vehicleid][vehObject], vehicleid, 0.000, 0.530, 0.260, 0.000, 0.000, 0.000);
			RuteForklift[playerid] = RandomEx(0, 3);
			SetPlayerRaceCheckpoint(playerid, 1, forkliftrute[RuteForklift[playerid]][forklift_posx], forkliftrute[RuteForklift[playerid]][forklift_posy], forkliftrute[RuteForklift[playerid]][forklift_posz], 0, 0, 0, 3);
			KillTimer(pData[playerid][pActivity]);
			pData[playerid][pActivityTime] = 0;
			for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
			return 1;
		}
		else if(pData[playerid][pActivityTime] < 100)
		{
			pData[playerid][pActivityTime]++;
			SetProgressBar(playerid, pData[playerid][pActivityTime]);
		}
	}
	return 1;
}
