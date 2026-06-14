#include <YSI\y_hooks>
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_SECONDARY_ATTACK))
	{
		static
			id = -1;

		if((id = FurnStore_Nearest(playerid)) != -1 && IsPlayerInDynamicCP(playerid, storeData[id][storeCP]))
		{
			if (storeData[id][storeSeal]) return Error(playerid, "This furniture store is sealed by authority.");
			SetPlayerPos(playerid, storeData[id][storeIntPos][0], storeData[id][storeIntPos][1], storeData[id][storeIntPos][2]);
			SetPlayerFacingAngle(playerid, 269.60);
			SetPlayerInterior(playerid, 3);
			SetPlayerVirtualWorld(playerid, storeData[id][storeID] + 1);

			Streamer_Update(playerid);

			pData[playerid][pFurnStore] = storeData[id][storeID];
			SetPlayerWeather(playerid, 0);
			SetPlayerTime(playerid, 12, 0);
			return 1;
		}
		if((id = FurnStore_Inside(playerid)) != -1 && IsPlayerInRangeOfPoint(playerid, 2.5, storeData[id][storeIntPos][0], storeData[id][storeIntPos][1], storeData[id][storeIntPos][2]))
		{
			SetPlayerPos(playerid, storeData[id][storePos][0], storeData[id][storePos][1], storeData[id][storePos][2]);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			SetCameraBehindPlayer(playerid);

			pData[playerid][pFurnStore] = -1;
			return 1;
		}
	}
	return 1;
}
