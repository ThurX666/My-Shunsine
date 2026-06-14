
CMD:createtree(playerid, params[])
{
	if(pData[playerid][pAdmin] < 4)
		return PermissionError(playerid);
	new tid = Iter_Free(Trees), query[512];
	if(tid == -1) return Error(playerid, "Can't add any more trees.");
 	new Float: x, Float: y, Float: z, Float: a;
 	GetPlayerPos(playerid, x, y, z);
 	GetPlayerFacingAngle(playerid, a);
 	x += (3.0 * floatsin(-a, degrees));
	y += (3.0 * floatcos(-a, degrees));
	z -= 1.0;
	
	TreeData[tid][treeX] = x;
	TreeData[tid][treeY] = y;
	TreeData[tid][treeZ] = z;
	TreeData[tid][treeRX] = TreeData[tid][treeRY] = TreeData[tid][treeRZ] = 0.0;
	
	TreeData[tid][treeObjID] = CreateDynamicObject(657, TreeData[tid][treeX], TreeData[tid][treeY], TreeData[tid][treeZ], TreeData[tid][treeRX], TreeData[tid][treeRY], TreeData[tid][treeRZ]);
	Iter_Add(Trees, tid);
	
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO trees SET id='%d', posx='%f', posy='%f', posz='%f', posrx='%f', posry='%f', posrz='%f'", tid, TreeData[tid][treeX], TreeData[tid][treeY], TreeData[tid][treeZ], TreeData[tid][treeRX], TreeData[tid][treeRY], TreeData[tid][treeRZ]);
	mysql_tquery(g_SQL, query, "OnTreeCreated", "di", playerid, tid);
	return 1;
}

CMD:edittree(playerid, params[])
{
    if(pData[playerid][pAdmin] < 4)
		return PermissionError(playerid);
    if(pData[playerid][EditingTreeID] != -1) return Error(playerid, "You're already editing a tree.");
	new tid;
	if(sscanf(params, "i", tid)) return Usage(playerid, "/edittree [tree id]");
	if(!Iter_Contains(Trees, tid)) return Error(playerid, "Invalid ID.");
	if(TreeData[tid][treeGettingCut]) return Error(playerid, "Can't edit specified tree because its getting cut down.");
	if(!IsPlayerInRangeOfPoint(playerid, 30.0, TreeData[tid][treeX], TreeData[tid][treeY], TreeData[tid][treeZ])) return SendClientMessage(playerid, 0xE74C3CFF, "ERROR: {FFFFFF}You're not near the tree you want to edit.");
	pData[playerid][EditingTreeID] = tid;
	EditDynamicObject(playerid, TreeData[tid][treeObjID]);
	return 1;
}

CMD:removetree(playerid, params[])
{
    if(pData[playerid][pAdmin] < 4)
		return PermissionError(playerid);
		
	new tid, query[512];
	if(sscanf(params, "i", tid)) return Usage(playerid, "/removetree [tree id]");
	if(!Iter_Contains(Trees, tid)) return Error(playerid, "Invalid ID.");
	if(TreeData[tid][treeGettingCut]) return Error(playerid, "Can't remove specified tree because its getting cut down.");
	if(Tree_BeingEdited(tid)) return Error(playerid, "Can't remove specified tree because its being edited.");
	DestroyDynamicObject(TreeData[tid][treeObjID]);
	DestroyDynamic3DTextLabel(TreeData[tid][treeLabel]);
	if(TreeData[tid][treeTimer] != -1) KillTimer(TreeData[tid][treeTimer]);
	
	TreeData[tid][treeLumber] = TreeData[tid][treeSeconds] = 0;
	TreeData[tid][treeObjID] = TreeData[tid][treeTimer] = -1;
	TreeData[tid][treeLabel] = Text3D: -1;
	Iter_Remove(Trees, tid);
	
	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM trees WHERE id=%d", tid);
	mysql_tquery(g_SQL, query);
	Servers(playerid, "Tree removed.");
	return 1;
}

CMD:gototree(playerid, params[])
{
	new tid;
	if(pData[playerid][pAdmin] < 4)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", tid))
		return Usage(playerid, "/gototree [id]");
	if(!Iter_Contains(Trees, tid)) return Error(playerid, "The tree you specified ID of doesn't exist.");
	SetPlayerPosition(playerid, TreeData[tid][treeX], TreeData[tid][treeY], TreeData[tid][treeZ], 2.0);
	pData[playerid][pInBiz] = -1;
	pData[playerid][pInHouse] = -1;
	pData[playerid][pInDoor] = -1;
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
	Servers(playerid, "You has teleport to house id %d", tid);
	return 1;
}

CMD:buychainsaw(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, -1438.4968,-1544.1377,101.7578)) return Error(playerid, "You have to be at the lumber jack point");
	if(pData[playerid][pJob] == 3 || pData[playerid][pJob2] == 3)
	{
		GivePlayerWeaponEx(playerid, 9, 1);
		GivePlayerMoneyEx(playerid, -2500);
		SendClientMessageEx(playerid, COLOR_ARWIN, "LUMBER: "YELLOW_E"Anda telah membeli chainsaw dengan harga "GREEN_E"$25.00");
	}
	else return Error(playerid, "You are not Lumber Jack");
	return 1;
}

CMD:findtree(playerid, params[])
{
	if(pData[playerid][pJob] == 3 || pData[playerid][pJob2] == 3)
	{
		if(GetAnyTree() <= 0) return Error(playerid, "Tidak ada pohon yang terbuka.");
		new id, count = GetAnyTree(), location[4096], lstr[596];
		strcat(location,"No\tLocation\tDistance\n",sizeof(location));
		Loop(itt, (count + 1), 1)
		{
			id = ReturnTreeID(itt);
			if(itt == count)
			{
				format(lstr,sizeof(lstr), "%d\t%s\t%0.2fm\n", itt, GetLocation(TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ]), GetPlayerDistanceFromPoint(playerid, TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ]));
			}
			else format(lstr,sizeof(lstr), "%d\t%s\t%0.2fm\n", itt, GetLocation(TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ]), GetPlayerDistanceFromPoint(playerid, TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ]));
			strcat(location,lstr,sizeof(location));
		}
		Dialog_Show(playerid, TrackTree, DIALOG_STYLE_TABLIST_HEADERS,"Track Tree",location,"Track","Cancel");
	}
	return 1;
}		

CMD:unloadtimber(playerid, params[])
{
	if(pData[playerid][pJob] == 3 || pData[playerid][pJob2] == 3)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return Error(playerid, "You are not driver in pickup truck.");
		if(!IsValidVehicle(vehicleid)) return Error(playerid, "You're not in any vehicle.");
		if(Vehicle_LumberCount(vehicleid) < 1) return Error(playerid, "This vehicle doesn't have any logs.");
		if(IsPlayerInRangeOfPoint(playerid, 2.5, -1426.0400,-1526.8910,101.7479))
		{
			foreach(new pv : PVehicles)
			{
				if(vehicleid == pvData[pv][cVeh])
				{
					if(pvData[pv][cLumber] > 0)
					{
						if(StockCrateLumber > 40) return Error(playerid, "Stock wood in warehouses exceeds capacity");
						new cash = pvData[pv][cLumber] * 3000;
						new list[212];
						new strings[525];
						format(list, sizeof(list), "Sold %d timbers", pvData[pv][cLumber]);
						AddPlayerSalary(playerid, "Woody Wood Works", list, cash);
						SendClientMessageEx(playerid, COLOR_ARWIN, "STORAGE: {FFFFFF}You've unloaded {FFFF00}%d timber{FFFFFF}, {00FF00}$%s {FFFFFF}has been issued to your paycheck.", pvData[pv][cLumber], FormatMoney(pvData[pv][cLumber]*(2500)));
						SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
						StockCrateLumber += pvData[pv][cLumber]/4;
						pvData[pv][cLumber] = 0;
						Crate_Save();
						DelayPlayer[playerid][DelayLumberJack] = 2000;
						if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][1])) DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][1]);
						TextDrawHideForPlayer(playerid, PlayerCrateTD);
						PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
						PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);
						format(strings, sizeof(strings), ""AQUA_E"Timber crate\n"WHITE_E"Available crates: "GREEN_E"%d "YELLOW_E"/ 40\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup a crate", StockCrateLumber);
	                	UpdateDynamic3DTextLabelText(Timber, COLOR_ARWIN, strings);
					}
				}
			}		
			Streamer_Update(playerid);
		}		
	}
	else return Error(playerid, "anda bukan pekerja lumber!");
	return 1;
}
