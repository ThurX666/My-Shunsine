
Dialog:StartForklift(playerid, response, listitem, inputtext[]) 
{
    new vehicleid = GetPlayerVehicleID(playerid);
	if(response)
	{
		if(pData[playerid][pFaction] > 0) return Error(playerid, "Kamu anggota faction, tidak bekerja jobs/sidejob.");
		if(DelayPlayer[playerid][DelayForklift] > 0)
		{
			Error(playerid, "Anda harus menunggu "GREY2_E"%d "WHITE_E"menit lagi.", DelayPlayer[playerid][DelayForklift]/10);
			RemovePlayerFromVehicle(playerid);
			SetTimerEx("RespawnPV", 3000, false, "d", vehicleid);
			return 1;
		}
		pData[playerid][pSideJob] = 401;
		RuteForklift[playerid] = RandomEx(4, 8);
		SetPlayerRaceCheckpoint(playerid, 1, forkliftrute[RuteForklift[playerid]][forklift_posx], forkliftrute[RuteForklift[playerid]][forklift_posy], forkliftrute[RuteForklift[playerid]][forklift_posz], 0, 0, 0, 3);
	}
	else
	{
		RemovePlayerFromVehicle(playerid);
		SetTimerEx("RespawnPV", 3000, false, "d", vehicleid);
	}
	return 1;
}
