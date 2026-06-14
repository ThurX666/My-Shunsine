
function FishingAreaLoad()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new fishing;
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", fishing);
			cache_get_value_name_float(i, "PosX", FishingData[fishing][Pos][0]);
            cache_get_value_name_float(i, "PosY", FishingData[fishing][Pos][1]);
            cache_get_value_name_float(i, "PosZ", FishingData[fishing][Pos][2]);
			FishingData[fishing][ID] = fishing;
            FishingData[fishing][Type] = random(3);
			FishingData[fishing][Zone] = CreateDynamicSphere(FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2], 70, 0, 0);
			Iter_Add(FishingArea, fishing);
	    }
	    printf("*** [Database: Loaded] Fishing Area data (%d count).", rows);
	}
}

FishingAreaSave(fishing)
{
	new dquery[2048];
	mysql_format(g_SQL, dquery, sizeof(dquery), "UPDATE fishingarea SET `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f' WHERE ID='%d'",
	FishingData[fishing][Pos][0],
	FishingData[fishing][Pos][1],
	FishingData[fishing][Pos][2],
    fishing);
	return mysql_tquery(g_SQL, dquery);
}
