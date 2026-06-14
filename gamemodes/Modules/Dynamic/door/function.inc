
Doors_Save(id)
{
	new dquery[2048];
	mysql_format(g_SQL, dquery, sizeof(dquery), "UPDATE doors SET name='%s', password='%s', icon='%d', locked='%d', admin='%d', vip='%d', faction='%d', family='%d', garage='%d', custom='%d', extvw='%d', extint='%d', extposx='%f', extposy='%f', extposz='%f', extposa='%f', intvw='%d', intint='%d', intposx='%f', intposy='%f', intposz='%f', intposa='%f' WHERE ID='%d'",
	dData[id][dName], dData[id][dPass], dData[id][dIcon], dData[id][dLocked], dData[id][dAdmin], dData[id][dVip], dData[id][dFaction], dData[id][dFamily], dData[id][dGarage], dData[id][dCustom], dData[id][dExtvw], dData[id][dExtint], dData[id][dExtposX], dData[id][dExtposY], dData[id][dExtposZ], dData[id][dExtposA], dData[id][dIntvw], dData[id][dIntint],
	dData[id][dIntposX], dData[id][dIntposY], dData[id][dIntposZ], dData[id][dIntposA], id);
	mysql_tquery(g_SQL, dquery);
	return 1;
}

Doors_Updatelabel(id)
{
	new mstr[512];
	if(id != -1)
	{
		if(IsValidDynamic3DTextLabel(dData[id][dLabelext])) DestroyDynamic3DTextLabel(dData[id][dLabelext]);
        if(IsValidDynamicPickup(dData[id][dPickupext])) DestroyDynamicPickup(dData[id][dPickupext]);
        if(IsValidDynamic3DTextLabel(dData[id][dLabelint])) DestroyDynamic3DTextLabel(dData[id][dLabelint]);
        if(IsValidDynamicPickup(dData[id][dPickupint])) DestroyDynamicPickup(dData[id][dPickupint]);
		if(IsValidDynamicCP(dData[id][dCP][0])) DestroyDynamicCP(dData[id][dCP][0]);
		if(IsValidDynamicCP(dData[id][dCP][1])) DestroyDynamicCP(dData[id][dCP][1]);
		
		if(dData[id][dGarage] == 1) format(mstr,sizeof(mstr),"{00FFFF}[ID: %d]\n{FFFF00}%s\n{FFFFFF}Press '{FF0000}ALT{FFFFFF}' to enter/exit the door", id, dData[id][dName]);
		else format(mstr,sizeof(mstr),""AQUA_E"[EE:%d]\n"YELLOW_E"%s\n{FFFFFF}Press '{FF0000}ENTER{FFFFFF}' to enter/exit", id, dData[id][dName]);
		
		dData[id][dPickupext] = CreateDynamicPickup(dData[id][dIcon], 23, dData[id][dExtposX], dData[id][dExtposY], dData[id][dExtposZ], dData[id][dExtvw], dData[id][dExtint]);
		dData[id][dCP][0] = CreateDynamicCP(dData[id][dExtposX], dData[id][dExtposY], dData[id][dExtposZ], 1, dData[id][dExtvw], dData[id][dExtint], -1, 5.0);
		dData[id][dLabelext] = CreateDynamic3DTextLabel(mstr, COLOR_YELLOW, dData[id][dExtposX], dData[id][dExtposY], dData[id][dExtposZ]+0.35, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, dData[id][dExtvw], dData[id][dExtint]);
        
		if(dData[id][dIntposX] != 0.0 && dData[id][dIntposY] != 0.0 && dData[id][dIntposZ] != 0.0)
        {
			if(dData[id][dGarage] == 1) format(mstr,sizeof(mstr),"{00FFFF}[id: %d]\n{FFFF00}%s\n{FFFFFF}Press '{FF0000}ALT{FFFFFF}' to enter/exit the door", id, dData[id][dName]);
			else format(mstr,sizeof(mstr),""AQUA_E"[EE:%d]\n"YELLOW_E"%s\n{FFFFFF}Press '{FF0000}ENTER{FFFFFF}' to enter/exit", id, dData[id][dName]);
			dData[id][dLabelint] = CreateDynamic3DTextLabel(mstr, COLOR_YELLOW, dData[id][dIntposX], dData[id][dIntposY], dData[id][dIntposZ]+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, dData[id][dIntvw], dData[id][dIntint]);
			dData[id][dPickupint] = CreateDynamicPickup(dData[id][dIcon], 23, dData[id][dIntposX], dData[id][dIntposY], dData[id][dIntposZ], dData[id][dIntvw], dData[id][dIntint], -1, 7);
			dData[id][dCP][1] = CreateDynamicCP(dData[id][dIntposX], dData[id][dIntposY], dData[id][dIntposZ], 1, dData[id][dIntvw], dData[id][dIntint], -1, 5.0);
		}
	}
}

function OnDoorsCreated(id)
{
	Doors_Save(id);
	Doors_Updatelabel(id);
	return 1;
}

function LoadDoors()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new did, name[128], password[128];
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", did);
	    	cache_get_value_name(i, "name", name);
			format(dData[did][dName], 128, name);
		    cache_get_value_name(i, "password", password);
			format(dData[did][dPass], 128, password);
		    cache_get_value_name_int(i, "icon", dData[did][dIcon]);
		    cache_get_value_name_int(i, "locked", dData[did][dLocked]);
		    cache_get_value_name_int(i, "admin", dData[did][dAdmin]);
		    cache_get_value_name_int(i, "vip", dData[did][dVip]);
		    cache_get_value_name_int(i, "faction", dData[did][dFaction]);
		    cache_get_value_name_int(i, "family", dData[did][dFamily]);
			cache_get_value_name_int(i, "garage", dData[did][dGarage]);
		    cache_get_value_name_int(i, "custom", dData[did][dCustom]);
		    cache_get_value_name_int(i, "extvw", dData[did][dExtvw]);
		    cache_get_value_name_int(i, "extint", dData[did][dExtint]);
		    cache_get_value_name_float(i, "extposx", dData[did][dExtposX]);
			cache_get_value_name_float(i, "extposy", dData[did][dExtposY]);
			cache_get_value_name_float(i, "extposz", dData[did][dExtposZ]);
			cache_get_value_name_float(i, "extposa", dData[did][dExtposA]);
			cache_get_value_name_int(i, "intvw", dData[did][dIntvw]);
			cache_get_value_name_int(i, "intint", dData[did][dIntint]);
			cache_get_value_name_float(i, "intposx", dData[did][dIntposX]);
			cache_get_value_name_float(i, "intposy", dData[did][dIntposY]);
			cache_get_value_name_float(i, "intposz", dData[did][dIntposZ]);
			cache_get_value_name_float(i, "intposa", dData[did][dIntposA]);
			
			Iter_Add(Doors, did);
			Doors_Updatelabel(did);
	    }
	    printf("*** [Database: Loaded] Door data (%d count).", rows);
	}
}

Entrance_Inside(playerid)
{
	new did = Iter_Free(Doors);
   	if(pData[playerid][pInDoor] != -1)
    {
        for (new i = 0; i != MAX_DOOR; i ++) if(did == pData[playerid][pInDoor] && GetPlayerInterior(playerid) == dData[i][dIntint] && GetPlayerVirtualWorld(playerid) == dData[i][dIntvw]) {
            return i;
        }
    }
    return -1;
}