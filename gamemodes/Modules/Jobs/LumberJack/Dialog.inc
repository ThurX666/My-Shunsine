
Dialog:TrackTree(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		new id = ReturnTreeID((listitem + 1));

		pData[playerid][pLoc] = id;
		SetPlayerRaceCheckpoint(playerid,1, TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ], 0.0, 0.0, 0.0, 3.5);
		Info(playerid, "Tree Checkpoint targeted! (%s)", GetLocation(TreeData[id][treeX], TreeData[id][treeY], TreeData[id][treeZ]));
	}
	return 1;
}
