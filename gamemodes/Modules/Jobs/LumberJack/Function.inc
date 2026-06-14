
function OnTreeCreated(playerid, tid)
{
	Tree_Save(tid);
	
	pData[playerid][EditingTreeID] = tid;
	EditDynamicObject(playerid, TreeData[tid][treeObjID]);
	Servers(playerid, "Tree created.");
	Servers(playerid, "You can edit it right now, or cancel editing and edit it some other time.");
	return 1;
}

GetClosestTree(playerid, Float: range = 3.0)
{
	new id = -1, Float: dist = range, Float: tempdist;
	foreach(new i : Trees)
	{
	    tempdist = GetPlayerDistanceFromPoint(playerid, TreeData[i][treeX], TreeData[i][treeY], TreeData[i][treeZ]);

	    if(tempdist > range) continue;
		if(tempdist <= dist)
		{
			dist = tempdist;
			id = i;
		}
	}
	return id;
}

Player_ResetCutting(playerid)
{
	if(!IsPlayerConnected(playerid) || pData[playerid][CuttingTreeID] == -1) return 0;
	new id = pData[playerid][CuttingTreeID];
	TreeData[id][treeGettingCut] = false;
	if(TreeData[id][treeSeconds] < 1) Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, TreeData[id][treeLabel], E_STREAMER_COLOR, 0x2ECC71FF);
	
	ClearAnimations(playerid);
    TogglePlayerControllable(playerid, 1);
    pData[playerid][CuttingTreeID] = -1;
    
    if(pData[playerid][pActivity] != -1)
	{
	    KillTimer(pData[playerid][pActivity]);
		pData[playerid][pActivity] = -1;
		pData[playerid][pActivityTime] = 0;
	}
	PlayerTextDrawHide(playerid, ActiveTD[playerid]);
	HidePlayerProgressBar(playerid, pData[playerid][activitybar]);
	return 1;
}

Player_RemoveLumber(playerid)
{
	if(!IsPlayerConnected(playerid) || !pData[playerid][CarryingLumber]) return 0;
	RemovePlayerAttachedObject(playerid, 9);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	pData[playerid][CarryingLumber] = false;
	return 1;
}

function RespawnTree(id)
{
	new label[96];
	if(TreeData[id][treeSeconds] > 1) 
	{
	    TreeData[id][treeSeconds]--;
	    format(label, sizeof(label), "Tree (%d)\n{FFFFFF}%s", id, ConvertToMinutes(TreeData[id][treeSeconds]));
		UpdateDynamic3DTextLabelText(TreeData[id][treeLabel], COLOR_GREEN, label);
	}
	else if(TreeData[id][treeSeconds] == 1) 
	{
	    KillTimer(TreeData[id][treeTimer]);

	    TreeData[id][treeLumber] = 0;
	    TreeData[id][treeSeconds] = 0;
	    TreeData[id][treeTimer] = -1;
	    
	    SetDynamicObjectPos(TreeData[id][treeObjID], TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ]);
     	SetDynamicObjectRot(TreeData[id][treeObjID], TreeData[id][treeRX], TreeData[id][treeRY], TreeData[id][treeRZ]);
     	
     	format(label, sizeof(label), "Tree (%d)\n", id);
     	UpdateDynamic3DTextLabelText(TreeData[id][treeLabel], COLOR_GREEN, label);
	}
	return 1;
}
	
function LoadTrees()
{
    new tid;
	
	new rows = cache_num_rows();
 	if(rows)
  	{
		for(new i; i < rows; i++)
		{
			cache_get_value_name_int(i, "id", tid);
			cache_get_value_name_float(i, "posx", TreeData[tid][treeX]);
			cache_get_value_name_float(i, "posy", TreeData[tid][treeY]);
			cache_get_value_name_float(i, "posz", TreeData[tid][treeZ]);
			cache_get_value_name_float(i, "posrx", TreeData[tid][treeRX]);
			cache_get_value_name_float(i, "posry", TreeData[tid][treeRY]);
			cache_get_value_name_float(i, "posrz", TreeData[tid][treeRZ]);
			
			TreeData[tid][treeCP] = CreateDynamicCP(TreeData[tid][treeX], TreeData[tid][treeY], TreeData[tid][treeZ]-1, 3.5, 0, 0, -1, 7.0);
			TreeData[tid][treeObjID] = CreateDynamicObject(657, TreeData[tid][treeX], TreeData[tid][treeY], TreeData[tid][treeZ], TreeData[tid][treeRX], TreeData[tid][treeRY], TreeData[tid][treeRZ]);
			Iter_Add(Trees, tid);
			
			TreeData[tid][treeGettingCut] = false;
			TreeData[tid][treeSeconds] = 0;
		}
		printf("*** [Database: Loaded] tree data (%d count).", rows);
	}
}

Tree_Save(tid)
{
	new cQuery[512];
	format(cQuery, sizeof(cQuery), "UPDATE trees SET posx='%f', posy='%f', posz='%f', posrx='%f', posry='%f', posrz='%f' WHERE id='%d'",
	TreeData[tid][treeX],
	TreeData[tid][treeY],
	TreeData[tid][treeZ],
	TreeData[tid][treeRX],
	TreeData[tid][treeRY],
	TreeData[tid][treeRZ],
	tid
	);
	return mysql_tquery(g_SQL, cQuery);
}

Tree_Refresh(tid)
{
    if(!Iter_Contains(Trees, tid)) return 0;
    new label[96];
    
    if(TreeData[tid][treeLumber] > 0) {
	    format(label, sizeof(label), "Tree (%d)\n"WHITE_E"Lumber: "GREEN_E"%d\n"WHITE_E"Use /lumber take.", tid, TreeData[tid][treeLumber]);
		UpdateDynamic3DTextLabelText(TreeData[tid][treeLabel], COLOR_GREEN, label);
	}else{
	    TreeData[tid][treeTimer] = SetTimerEx("RespawnTree", 1000, true, "i", tid);
	    
	    format(label, sizeof(label), "Tree (%d)\n"WHITE_E"%s", tid, ConvertToMinutes(TreeData[tid][treeSeconds]));
		UpdateDynamic3DTextLabelText(TreeData[tid][treeLabel], COLOR_GREEN, label);
	}
	
	return 1;
}

Tree_BeingEdited(tid)
{
	if(!Iter_Contains(Trees, tid)) return 0;
	foreach(new i : Player) if(pData[i][EditingTreeID] == tid) return 1;
	return 0;
}

ConvertToMinutes(time)
{
    // http://forum.sa-mp.com/showpost.php?p=3223897&postcount=11
    new string[15];//-2000000000:00 could happen, so make the string 15 chars to avoid any errors
    format(string, sizeof(string), "%02d:%02d", time / 60, time % 60);
    return string;
}

//untuk mencari pohon digps
GetAnyTree()
{
	new tmpcount;
	foreach(new id : Trees)
	{
     	tmpcount++;
	}
	return tmpcount;
}

ReturnTreeID(slot)
{
	new tmpcount;
	if(slot < 1 && slot > MAX_TREES) return -1;
	foreach(new id : Trees)
	{
        tmpcount++;
        if(tmpcount == slot)
        {
            return id;
        }
	}
	return -1;
}

Vehicle_LumberCount(vehicleid)
{
	if(GetVehicleModel(vehicleid) == 0) return 0;
	new count = 0;
    foreach(new pv : PVehicles)
    {
        if(vehicleid == pvData[pv][cVeh])
        {
            count += pvData[pv][cLumber];
        }
    }    
	return count;
}

function LoadTimber(playerid, tid) {
	if(!TreeData[tid][treeGettingCut]) return 0;
	if(pData[playerid][pActivityTime] >= 100)
	{
		SetPlayerEnergy(playerid, pData[playerid][pEnergy]-3.0);
		ClearAnimations(playerid);
		StopLoopingAnim(playerid);
		TogglePlayerControllable(playerid, 1);
		new Float: x, Float: y, Float: z;
		new vehicleid = pData[playerid][pLastCar];
		GetVehicleBoot(pData[playerid][pLastCar], x, y, z);
		if(GetPlayerDistanceFromPoint(playerid, x, y, z) > 6) {
			Error(playerid, "Your last vehicle is too far away.");  
			KillTimer(pData[playerid][pActivity]);
			pData[playerid][pActivityTime] = 0;
			for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
			ClearAnimations(playerid);
			StopLoopingAnim(playerid);
			TogglePlayerControllable(playerid, 1);
			return 1;
		}
		foreach(new carid : PVehicles) {
			if(vehicleid == pvData[carid][cVeh]) {
				if(pvData[carid][cVeh] == INVALID_VEHICLE_ID) return Error(playerid, "You not in near any vehicles.");
				pvData[carid][cLumber]++;
				SendCustomMessage(playerid, "STORAGE", "Anda berhasil memuat pohon. storage: %d/5", pvData[carid][cLumber]);
				if(pvData[carid][cLumber] > 0) if(IsValidVehicle(carid)) {
					if(IsValidDynamicObject(ObjectVehicle[pvData[carid][cVeh]][1])) DestroyDynamicObject(ObjectVehicle[pvData[carid][cVeh]][1]);
					if(GetVehicleModel(pvData[carid][cVeh]) == 422)
					{
						ObjectVehicle[pvData[carid][cVeh]][1] = CreateDynamicObject(1463,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[carid][cVeh]][1], pvData[carid][cVeh], 0.005, -1.440, -0.130, 0.000, 179.999, 90.899);
					}
					else if(GetVehicleModel(pvData[carid][cVeh]) == 478)
					{
						ObjectVehicle[pvData[carid][cVeh]][1] = CreateDynamicObject(1463,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[carid][cVeh]][1], pvData[carid][cVeh], 0.000, -1.420, 0.080, 180.000, 0.000, 90.000);
					}	
					else if(GetVehicleModel(pvData[carid][cVeh]) == 543)
					{
						ObjectVehicle[pvData[carid][cVeh]][1] = CreateDynamicObject(1463,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[carid][cVeh]][1], pvData[carid][cVeh], 0.000, -1.651, 0.000, 180.000, 0.000, 90.000);
					}
					else if(GetVehicleModel(pvData[carid][cVeh]) == 554)
					{
						ObjectVehicle[pvData[carid][cVeh]][1] = CreateDynamicObject(1463,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
						AttachDynamicObjectToVehicle(ObjectVehicle[pvData[carid][cVeh]][1], pvData[carid][cVeh], -0.070, -1.581, 0.100, 180.000, 0.000, 90.000);
					}
				} 
			}
		}
		if(IsValidDynamicObject(TreeData[tid][treeObjID])) DestroyDynamicObject(TreeData[tid][treeObjID]);
		TreeData[tid][treeSeconds] = TREE_RESPAWN;
		TreeData[tid][treeGettingCut] = false;
		KillTimer(pData[playerid][pActivity]);
		pData[playerid][pActivityTime] = 0;
		for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
		Streamer_Update(playerid);
		return 1;
	}
	else if(pData[playerid][pActivityTime] < 100)
	{
		pData[playerid][pActivityTime]++;
		SetProgressBar(playerid, pData[playerid][pActivityTime]);
	}
	return 1;
}

function RemoveLumber(tid)
{
	if(!Iter_Count(Lumbers, tid)) return 1;
	
	if(LumberData[tid][lumberSeconds] > 1) 
	{
	    LumberData[tid][lumberSeconds]--;

        new label[128];
	    format(label, sizeof(label), "Lumber (%d)\n"WHITE_E"Dropped By "GREEN_E"%s\n"WHITE_E"%s\nUse /lumber pickup.", tid, LumberData[tid][lumberDroppedBy], ConvertToMinutes(LumberData[tid][lumberSeconds]));
		UpdateDynamic3DTextLabelText(LumberData[tid][lumberLabel], COLOR_GREEN, label);
	}
	else if(LumberData[tid][lumberSeconds] == 1) 
	{
	    KillTimer(LumberData[tid][lumberTimer]);
	    DestroyDynamicObject(LumberData[tid][lumberObjID]);
		DestroyDynamic3DTextLabel(LumberData[tid][lumberLabel]);
		
	    LumberData[tid][lumberTimer] = -1;
        LumberData[tid][lumberObjID] = -1;
        LumberData[tid][lumberLabel] = Text3D: -1;

		Iter_Remove(Lumbers, tid);
	}
	
	return 1;
}
