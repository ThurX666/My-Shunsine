
Gate_Save(id)
{
	new dquery[2048];
	mysql_format(g_SQL, dquery, sizeof(dquery), "UPDATE gates SET model='%d', password='%s', admin='%d', vip='%d', faction='%d', family='%d', speed='%f', cX='%f', cY='%f', cZ='%f', cRX='%f', cRY='%f', cRZ='%f', oX='%f', oY='%f', oZ='%f', oRX='%f', oRY='%f', oRZ='%f' WHERE ID='%d'",
	gData[id][gModel], gData[id][gPass], gData[id][gAdmin], gData[id][gVip], gData[id][gFaction], gData[id][gFamily], gData[id][gSpeed], gData[id][gCX], gData[id][gCY], gData[id][gCZ], gData[id][gCRX], gData[id][gCRY], gData[id][gCRZ], gData[id][gOX], gData[id][gOY], gData[id][gOZ], gData[id][gORX], gData[id][gORY], gData[id][gORZ], id);
	mysql_tquery(g_SQL, dquery);
	return 1;
}

function LoadGates()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new id, password[36];
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", id);
	    	cache_get_value_name_int(i, "model", gData[id][gModel]);
		    cache_get_value_name(i, "password", password);
			format(gData[id][gPass], 36, password);
		    cache_get_value_name_int(i, "admin", gData[id][gAdmin]);
		    cache_get_value_name_int(i, "vip", gData[id][gVip]);
		    cache_get_value_name_int(i, "faction", gData[id][gFaction]);
		    cache_get_value_name_int(i, "family", gData[id][gFamily]);
		    cache_get_value_name_float(i, "speed", gData[id][gSpeed]);
		    cache_get_value_name_float(i, "cX", gData[id][gCX]);
			cache_get_value_name_float(i, "cY", gData[id][gCY]);
			cache_get_value_name_float(i, "cZ", gData[id][gCZ]);
			cache_get_value_name_float(i, "cRX", gData[id][gCRX]);
			cache_get_value_name_float(i, "cRY", gData[id][gCRY]);
			cache_get_value_name_float(i, "cRZ", gData[id][gCRZ]);
			cache_get_value_name_float(i, "oX", gData[id][gOX]);
			cache_get_value_name_float(i, "oY", gData[id][gOY]);
			cache_get_value_name_float(i, "oZ", gData[id][gOZ]);
			cache_get_value_name_float(i, "oRX", gData[id][gORX]);
			cache_get_value_name_float(i, "oRY", gData[id][gORY]);
			cache_get_value_name_float(i, "oRZ", gData[id][gORZ]);
			
			Iter_Add(Gates, id);
			gData[id][gObjID] = CreateDynamicObject(gData[id][gModel], gData[id][gCX], gData[id][gCY], gData[id][gCZ], gData[id][gCRX], gData[id][gCRY], gData[id][gCRZ], -1, -1, -1, 50.0, 50.0);
			
			gData[id][gStatus] = 0;
	    }
	    printf("*** [Database: Loaded] Gate data (%d count).", rows);
	}
}

function OnGateCreated(id)
{
	Gate_Save(id);
	return 1;
}

function DynamicGateClose(idx)
{
   	gData[idx][gStatus] = 0;
	MoveDynamicObject(gData[idx][gObjID], gData[idx][gCX], gData[idx][gCY], gData[idx][gCZ], gData[idx][gSpeed]);
	SetDynamicObjectRot(gData[idx][gObjID], gData[idx][gCRX], gData[idx][gCRY], gData[idx][gCRZ]);
	return 1;
}
