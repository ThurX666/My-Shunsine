
forward Rent_Load();
public Rent_Load()
{
	new rows = cache_num_rows(), id;
 	if(rows)
  	{
		for(new i; i < rows; i++)
		{
            cache_get_value_name_int(i, "rID", id);
		    cache_get_value_name_float(i, "rX", rentData[id][rX]);
		    cache_get_value_name_float(i, "rY", rentData[id][rY]);
		    cache_get_value_name_float(i, "rZ", rentData[id][rZ]);
		    
		    cache_get_value_name_float(i, "rRX", rentData[id][rRX]);
		    cache_get_value_name_float(i, "rRY", rentData[id][rRY]);
		    cache_get_value_name_float(i, "rRZ", rentData[id][rRZ]);
            cache_get_value_name_float(i, "rRA", rentData[id][rRA]);
            cache_get_value_name_int(i, "rType", rentData[id][rType]);	

			Iter_Add(Rents, id);
			Rent_Refresh(id);
		}
	}
	printf("*** [Database: Loaded] rent data (%d count).", rows);
	return 1;
}

stock Rent_Save(id)
{
	new
	    query[512];

	format(query, sizeof(query), "UPDATE `rentplayer` SET `rX` = '%f', `rY` = '%f', `rZ` = '%f', `rRX` = '%f', `rRY` = '%f', `rRZ` = '%f', `rRA` = '%f', `rType` = '%d' WHERE `rID` = '%d'",
		rentData[id][rX],
        rentData[id][rY],
        rentData[id][rZ],
        rentData[id][rRX],
        rentData[id][rRY],
        rentData[id][rRZ],
        rentData[id][rRA],
        rentData[id][rType],
        id
	);
	return mysql_tquery(g_SQL, query);
}

stock Rent_Refresh(id)
{
	if(id != -1)
	{
        if(IsValidDynamicPickup(rentData[id][rPickup]))
            DestroyDynamicPickup(rentData[id][rPickup]);

        if(IsValidDynamic3DTextLabel(rentData[id][rLabelPoint]))
            DestroyDynamic3DTextLabel(rentData[id][rLabelPoint]);

		new string[212];
        format(string, sizeof(string), "{00FFFF}Pickup Rental(%d)\n"WHITE_E"Use "YELLOW_E"'/rentveh' "WHITE_E"to rent a vehicle\n"WHITE_E"Use "YELLOW_E"'/unrentveh' "WHITE_E"to return any rented vehicle", id);
        rentData[id][rPickup] = CreateDynamicPickup(1239, 1, rentData[id][rX], rentData[id][rY], rentData[id][rZ]);
        rentData[id][rLabelPoint] = CreateDynamic3DTextLabel(string, COLOR_ARWIN, rentData[id][rX], rentData[id][rY], rentData[id][rZ]+0.5,3.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1);
	}
}

function RentCreate(id)
{
	Rent_Save(id);
	Rent_Refresh(id);
	return 1;
}
