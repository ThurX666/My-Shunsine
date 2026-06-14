
ptask LumberTree[1000](playerid)
{
	new tid = GetClosestTree(playerid);
	if(tid != -1)
	{
		if(IsPlayerInDynamicCP(playerid, TreeData[tid][treeCP]) && tid != -1)
		{
			new mstr[128];
			new string[128];
			PlayerTextDrawSetString(playerid, JailTD[playerid], string);
			if(TreeData[tid][treeSeconds] > 1 && !TreeData[tid][treeGettingCut]) format(string, sizeof(string), "Grow Time: ~y~%s", ConvertToMinutes(TreeData[tid][treeSeconds]));
			else if(TreeData[tid][treeSeconds] < 1 && !TreeData[tid][treeGettingCut]) format(mstr, sizeof(mstr), "~g~Can cut down Now");
            if(TreeData[tid][treeGettingCut]) format(mstr, sizeof(mstr), "~r~Cut");
			GameTextForPlayer(playerid, mstr, 1000, 6);
			PlayerTextDrawSetString(playerid, JailTD[playerid], string);
		}
	}
    foreach(new id : Trees) {
        if(TreeData[id][treeSeconds] > 1)  {
            TreeData[id][treeSeconds]--;
            if(TreeData[id][treeSeconds] == 0) {
                TreeData[tid][treeGettingCut] = false;
                TreeData[id][treeObjID] = CreateDynamicObject(657, TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ], TreeData[id][treeRX], TreeData[id][treeRY], TreeData[id][treeRZ]);
            }
        }
    }
    return 1;
}