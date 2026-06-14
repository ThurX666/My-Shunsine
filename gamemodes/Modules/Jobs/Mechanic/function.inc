#include <YSI\y_hooks>

stock IsPlayerAtMechanicPoint(playerid)
{
	return (
		IsPlayerInRangeOfPoint(playerid, 30.0, 1781.5748, -2061.7913, 13.5904) ||
		IsPlayerInRangeOfPoint(playerid, 30.0, -243.8492, 1217.4625, 19.7422)
	);
}

stock GetPlayerNearbyWorkshop(playerid, Float:radius = 30.0)
{
	foreach(new wsid : Workshop)
	{
		if(IsPlayerInRangeOfPoint(playerid, radius, WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]))
		{
			return wsid;
		}
	}
	return -1;
}

stock IsPlayerWorkshopWorker(playerid, wsid)
{
	if(wsid == -1) return 0;
	return (OwnerWorkshop(playerid, wsid) || Workshop_IsEmployee(playerid, wsid));
}

hook OnPlayerEnterRaceCP(playerid) {
    foreach(new i : PVehicles) if(pvData[i][cimpoundTake] == playerid && PlayerTowImpound[playerid] == i) {
        SendCustomMessage(playerid, "IMPOUND", "Anda berhasil mengantarkan mobil ke tempat impound, anda diberi $%s", FormatMoney(pvData[i][cPrice]/70));
        GivePlayerMoneyEx(playerid, pvData[i][cPrice]/70);
        GetVehicleDamageStatus(pvData[i][cVeh], pvData[i][cDamage0], pvData[i][cDamage1], pvData[i][cDamage2], pvData[i][cDamage3]);
        GetVehicleHealth(pvData[i][cVeh], pvData[i][cHealth]);
        pvData[i][cFuel] = GetVehicleFuel(pvData[i][cVeh]);
        pvData[i][cImpound] = 2;
        DestroyVehicle(pvData[i][cVeh]);
        DisablePlayerRaceCheckpoint(playerid);
    }
    return 1;
}
