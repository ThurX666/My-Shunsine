
ptask productionTimers[200](playerid)
{
	if(startProduce[playerid] && IsPlayerInDynamicArea(playerid, production) && GetPVarInt(playerid, "lagiedit") == 2)
	{
        productionCount[playerid]++;
        PlayerTextDrawTextSize(playerid, ProggresBar[playerid][1], productionCount[playerid]*126.0/100, 16.5);
        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Producing Furniture");
        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
		if(productionCount[playerid] > 100)
		{
			new index = ManageFurnObject[playerid], component = productionAdd[playerid]*15;
			FurnStore[index][furnStock] += productionAdd[playerid];

			if (IsValidDynamicObject(produceObject[playerid])) DestroyDynamicObject(produceObject[playerid]);
			produceObject[playerid] = INVALID_STREAMER_ID;

			FurnObject_Refresh(index);
			FurnObject_Save(index);
            ClearAnimations(playerid);
            for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
			pData[playerid][pComponent] -= component;
			DeletePVar(playerid, "lagiedit");
            productionCount[playerid] = 0;
            startProduce[playerid] = false;
		}
	}
    return 1;
}
