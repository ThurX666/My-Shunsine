
CMD:createore(playerid, params[])
{
	if(pData[playerid][pAdmin] < 4) return PermissionError(playerid);
	new tid = Iter_Free(Ores), query[512];
	if(tid == -1) return Error(playerid, "Can't add any more ores.");
	
 	new Float: x, Float: y, Float: z, Float: a;
 	GetPlayerPos(playerid, x, y, z);
 	GetPlayerFacingAngle(playerid, a);
 	x += (3.0 * floatsin(-a, degrees));
	y += (3.0 * floatcos(-a, degrees));
	z -= 1.0;
	OreData[tid][oreX] = x;
	OreData[tid][oreY] = y;
	OreData[tid][oreZ] = z;
	OreData[tid][oreRX] = OreData[tid][oreRY] = OreData[tid][oreRZ] = 0.0;
	
	OreData[tid][oreObjID] = CreateDynamicObject(3930, OreData[tid][oreX], OreData[tid][oreY], OreData[tid][oreZ], OreData[tid][oreRX], OreData[tid][oreRY], OreData[tid][oreRZ]);
	OreData[tid][oreArea] = CreateDynamicSphere(OreData[tid][oreX], OreData[tid][oreY], OreData[tid][oreZ], 3, 5, 5);
	Iter_Add(Ores, tid);
	
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO ores SET id='%d', posx='%f', posy='%f', posz='%f', posrx='%f', posry='%f', posrz='%f'", tid, OreData[tid][oreX], OreData[tid][oreY], OreData[tid][oreZ], OreData[tid][oreRX], OreData[tid][oreRY], OreData[tid][oreRZ]);
	mysql_tquery(g_SQL, query, "OnOreCreated", "di", playerid, tid);
	return 1;
}

CMD:editore(playerid, params[])
{
    if(pData[playerid][pAdmin] < 4) return PermissionError(playerid);
	new tid;
	if(sscanf(params, "i", tid)) return Usage(playerid, "/editore [id]");
	if(!Iter_Contains(Ores, tid)) return Error(playerid, "Invalid ID.");
	if(OreData[tid][oreGettingMiner]) return Error(playerid, "Can't edit specified ore because its getting miner.");
	if(!IsPlayerInRangeOfPoint(playerid, 30.0, OreData[tid][oreX], OreData[tid][oreY], OreData[tid][oreZ])) return Error(playerid, "You're not near the ore you want to edit.");
    GetPlayerPos(playerid, OreData[tid][oreX], OreData[tid][oreY], OreData[tid][oreZ]);
	DestroyDynamicObject(OreData[tid][oreObjID]);
	DestroyDynamicArea(OreData[tid][oreArea]);
	OreData[tid][oreObjID] = CreateDynamicObject(3930, OreData[tid][oreX], OreData[tid][oreY], OreData[tid][oreZ], OreData[tid][oreRX], OreData[tid][oreRY], OreData[tid][oreRZ]);
	SetDynamicObjectMaterial(OreData[tid][oreObjID], 0, 2936, "kmb_rckx", "larock256", RGBAToARGB(0xB87333FF));
	if (!IsValidDynamicArea(OreData[tid][oreArea]))
		OreData[tid][oreArea] = CreateDynamicSphere(OreData[tid][oreX], OreData[tid][oreY], OreData[tid][oreZ], 3, 5, 5);
	return 1;
}

CMD:removeore(playerid, params[])
{
    if(pData[playerid][pAdmin] < 4)
		return PermissionError(playerid);
		
	new tid, query[512];
	if(sscanf(params, "i", tid)) return Usage(playerid, "/removeore [id]");
	if(!Iter_Contains(Ores, tid)) return Error(playerid, "Invalid ID.");
	if(OreData[tid][oreGettingMiner]) return Error(playerid, "Can't remove specified ore because its getting cut down.");
	DestroyDynamicObject(OreData[tid][oreObjID]);
	DestroyDynamicArea(OreData[tid][oreArea]);
	OreData[tid][oreSeconds] = 0;
	OreData[tid][oreObjID] = -1;
	Iter_Remove(Ores, tid);
	
	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM ores WHERE id=%d", tid);
	mysql_tquery(g_SQL, query);
	Servers(playerid, "Ore removed.");
	return 1;
}

CMD:nearore(playerid) {
	foreach (new id : Ores) if (IsPlayerInDynamicArea(playerid, OreData[id][oreArea])) return Info(playerid, "Ore ID: %d", id);
	return 1;
}

CMD:gotoore(playerid, params[])
{
	new tid;
	if(pData[playerid][pAdmin] < 4) return PermissionError(playerid);
		
	if(sscanf(params, "d", tid)) return Usage(playerid, "/gotoore [id]");
	if(!Iter_Contains(Ores, tid)) return Error(playerid, "The ore you specified ID of doesn't exist.");
	SetPlayerPosition(playerid, OreData[tid][oreX], OreData[tid][oreY], OreData[tid][oreZ], 2.0);
	pData[playerid][pInBiz] = -1;
	pData[playerid][pInHouse] = -1;
	pData[playerid][pInDoor] = -1;
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
	Servers(playerid, "You has teleport to house id %d", tid);
	return 1;
}

CMD:startmine(playerid, params[]) {
	if(pData[playerid][pFaction] > 0) return Error(playerid, "Kamu anggota faction, tidak bekerja jobs/sidejob.");
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 2822.4126,2839.3374,48.3318)) {
		if(pData[playerid][pEnergy] < 20) return Error(playerid, "Tidak bisa melakukan menambang, anda kehausan!");
		SendCustomMessage(playerid, "SIDEJOB", "You've joined miner sidejob, hold "YELLOW_E"N "WHITE_E"to start mining ore");
		SendCustomMessage(playerid, "NOTE", "Sidejob will end if your energy go below 20, you exited the mine, our you logged out");
		pData[playerid][pStartMine] = 1;
		SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.1180, 0.0669, 0.2469, 0.0000, 102.4000, -94.1999, 1.0000, 1.0000, 1.0000);
	}
	return 1;
}

CMD:stopmine(playerid, params[]) {
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 2822.4126,2839.3374,48.3318)) {
		if(pData[playerid][pStartMine] < 1) return Error(playerid, "Anda tidak melakukan menambang!");
		SendCustomMessage(playerid, "SIDEJOB", "You stopped mining");
		pData[playerid][pStartMine] = 0;
		pTimeMiningOre[playerid] = 0;
		pMiningOre[playerid] = 0;
		pTotalCashOre[playerid] = 0;
		RemovePlayerAttachedObject(playerid, 9);
		pData[playerid][pStartMine] = 0;
		new totalMiner = pData[playerid][pMiner];
		if(totalMiner > 0) {
			GivePlayerMoneyEx(playerid, totalMiner);
			SendCustomMessage(playerid, "SIDEJOB", "Kamu berhenti menambang, total uang yang dikumpulkan "GREEN_E"$%s "WHITE_E"telah masuk ke cash kamu", FormatMoney(totalMiner));
		} else {
			SendCustomMessage(playerid, "SIDEJOB", "Kamu berhenti menambang, namun belum ada uang yang dikumpulkan");
		}
		pData[playerid][pMiner] = 0;
		RemovePlayerAttachedObject(playerid, 9);
	}
	return 1;
}
