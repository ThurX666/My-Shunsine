
GetClosestOre(playerid) {
    foreach (new id : Ores) if (IsPlayerInDynamicArea(playerid, OreData[id][oreArea])) {
        return id;
    }
    return -1;
}

function LoadOres()
{
    new tid;
	
	new rows = cache_num_rows();
 	if(rows)
  	{
		for(new i; i < rows; i++)
		{
			cache_get_value_name_int(i, "id", tid);
			cache_get_value_name_float(i, "posx", OreData[tid][oreX]);
			cache_get_value_name_float(i, "posy", OreData[tid][oreY]);
			cache_get_value_name_float(i, "posz", OreData[tid][oreZ]);
			cache_get_value_name_float(i, "posrx", OreData[tid][oreRX]);
			cache_get_value_name_float(i, "posry", OreData[tid][oreRY]);
			cache_get_value_name_float(i, "posrz", OreData[tid][oreRZ]);
			Iter_Add(Ores, tid);
			OreData[tid][oreGettingMiner] = false;
			OreData[tid][oreSeconds] = 0;
			OreData[tid][oreObjID] = CreateDynamicObject(3930, OreData[tid][oreX], OreData[tid][oreY], OreData[tid][oreZ], OreData[tid][oreRX], OreData[tid][oreRY], OreData[tid][oreRZ]);
			SetDynamicObjectMaterial(OreData[tid][oreObjID], 0, 2936, "kmb_rckx", "larock256", RGBAToARGB(0xB87333FF));
			if (!IsValidDynamicArea(OreData[tid][oreArea]))
        	OreData[tid][oreArea] = CreateDynamicSphere(OreData[tid][oreX], OreData[tid][oreY], OreData[tid][oreZ], 3, -1, -1);
		}
		printf("[Dynamic Ore] Number of Loaded: %d.", rows);
	}
}

Ore_Save(tid)
{
	new cQuery[512];
	format(cQuery, sizeof(cQuery), "UPDATE ores SET posx='%f', posy='%f', posz='%f', posrx='%f', posry='%f', posrz='%f' WHERE id='%d'",
	OreData[tid][oreX],
	OreData[tid][oreY],
	OreData[tid][oreZ],
	OreData[tid][oreRX],
	OreData[tid][oreRY],
	OreData[tid][oreRZ],
	tid
	);
	return mysql_tquery(g_SQL, cQuery);
}

function OnOreCreated(playerid, tid)
{
	Ore_Save(tid);
	Servers(playerid, "Ore created.");
	return 1;
}
