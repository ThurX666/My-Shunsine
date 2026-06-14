
GetClosestArrest(playerid, Float: range = 3.0)
{
	new id = -1, Float: dist = range, Float: tempdist;
	foreach(new i : DynArrests)
	{
	    tempdist = GetPlayerDistanceFromPoint(playerid, DynArrest[i][arrestPos][0], DynArrest[i][arrestPos][1], DynArrest[i][arrestPos][2]);

	    if(tempdist > range) continue;
		if(tempdist <= dist && GetPlayerInterior(playerid) == DynArrest[i][arrestInt] && GetPlayerVirtualWorld(playerid) == DynArrest[i][arrestWorld])
		{
			dist = tempdist;
			id = i;
		}
	}
	return id;
}

function LoadDynArrest()
{
	new rows;
	cache_get_row_count(rows);
	if(rows)
  	{
 		new id, i = 0;
		while(i < rows)
		{
		    cache_get_value_name_int(i, "id", id);
			cache_get_value_name_float(i, "posx", DynArrest[id][arrestPos][0]);
			cache_get_value_name_float(i, "posy", DynArrest[id][arrestPos][1]);
			cache_get_value_name_float(i, "posz", DynArrest[id][arrestPos][2]);
			cache_get_value_name_int(i, "interior", DynArrest[id][arrestInt]);
			cache_get_value_name_int(i, "world", DynArrest[id][arrestWorld]);
			cache_get_value_name_float(i, "posxcell", DynArrest[id][arrestCell][0]);
			cache_get_value_name_float(i, "posycell", DynArrest[id][arrestCell][1]);
			cache_get_value_name_float(i, "poszcell", DynArrest[id][arrestCell][2]);
			cache_get_value_name_int(i, "interiorcell", DynArrest[id][arrestIntCell]);
			cache_get_value_name_int(i, "worldcell", DynArrest[id][arrestWorldCell]);
            Iter_Add(DynArrests, id);
			DynArrest_Refresh(id);
	    	i++;
		}
		printf("*** [Database: Loaded] Dyn Arrest data (%d count).", i);
	}
}

DynArrest_Refresh(id) {
	new strings[212];
	format(strings, sizeof(strings), "{00FFFF}[id:%d] Arrest Point\n"YELLOW_E"/'arrest' "WHITE_E"arrest wanted player", id);
	if(!IsValidDynamicPickup(DynArrest[id][arrestPickup])) DynArrest[id][arrestPickup] = CreateDynamicPickup(1247, 23, DynArrest[id][arrestPos][0], DynArrest[id][arrestPos][1], DynArrest[id][arrestPos][2], -1);
	if(!IsValidDynamic3DTextLabel(DynArrest[id][arrestLabel])) DynArrest[id][arrestLabel] = CreateDynamic3DTextLabel(strings, COLOR_ARWIN, DynArrest[id][arrestPos][0], DynArrest[id][arrestPos][1], DynArrest[id][arrestPos][2], 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // arrest
	return 1;
}

DynArrest_Save(id)
{
	new cQuery[512];
	format(cQuery, sizeof(cQuery), "UPDATE dynarrests SET posx='%f', posy='%f', posz='%f', interior='%d', world='%d', posxcell='%f', posycell='%f', poszcell='%f', interiorcell='%d', worldcell='%d' WHERE id='%d'",
	DynArrest[id][arrestPos][0],
	DynArrest[id][arrestPos][1],
	DynArrest[id][arrestPos][2],
	DynArrest[id][arrestInt],
	DynArrest[id][arrestWorld],
    DynArrest[id][arrestCell][0],
	DynArrest[id][arrestCell][1],
	DynArrest[id][arrestCell][2],
	DynArrest[id][arrestIntCell],
	DynArrest[id][arrestWorldCell],
	id
	);
	return mysql_tquery(g_SQL, cQuery);
}

function OnDynArrestCreated(playerid, id)
{
	DynArrest_Save(id);
	Servers(playerid, "You has created DynArrest id: %d.", id);
	return 1;
}
