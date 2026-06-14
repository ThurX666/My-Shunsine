
Locker_Refresh(lid)
{
    if(lid != -1)
    {
        if(IsValidDynamic3DTextLabel(lData[lid][lLabel]))
            DestroyDynamic3DTextLabel(lData[lid][lLabel]);

        if(IsValidDynamicPickup(lData[lid][lPickup]))
            DestroyDynamicPickup(lData[lid][lPickup]);

        static
        string[255];
		
		new type[128];
		if(lData[lid][lType] == 1)
		{
			type= "San Andrease Police Departement";
		}
		else if(lData[lid][lType] == 2)
		{
			type= "San Andreas Goverment Service";
		}
		else if(lData[lid][lType] == 3)
		{
			type= "San Andreas Medical Departement";
		}
		else if(lData[lid][lType] == 4)
		{
			type= "San Andreas News Agency";
		}
		else if(lData[lid][lType] == 5)
		{
			type= "VIP";
		}
		else
		{
			type= "Unknown";
		}

		format(string, sizeof(string), "{00FFFF}[id: %d]\n"WHITE_E"Type: "YELLOW_E"%s\n"WHITE_E"Type '"RED_E"/locker"WHITE_E"' to open", lid, type);
		lData[lid][lPickup] = CreateDynamicPickup(1239, 23, lData[lid][lPosX], lData[lid][lPosY], lData[lid][lPosZ]+0.2, 0, lData[lid][lInt], _, 15.0);
		lData[lid][lLabel] = CreateDynamic3DTextLabel(string, COLOR_BLUE, lData[lid][lPosX], lData[lid][lPosY], lData[lid][lPosZ]+0.5, 5.0);
	}
    return 1;
}

function LoadLockers()
{
	new rows = cache_num_rows();
 	if(rows)
  	{
		new lid;
		for(new i; i < rows; i++)
		{
			cache_get_value_name_int(i, "id", lid);
			cache_get_value_name_int(i, "type", lData[lid][lType]);
			cache_get_value_name_float(i, "posx", lData[lid][lPosX]);
			cache_get_value_name_float(i, "posy", lData[lid][lPosY]);
			cache_get_value_name_float(i, "posz", lData[lid][lPosZ]);
			cache_get_value_name_int(i, "interior", lData[lid][lInt]);
			
			Iter_Add(Lockers, lid);
			Locker_Refresh(lid);
		}
		printf("*** [Database: Loaded] locker data (%d count)..", rows);
	}
}
	
Locker_Save(lid)
{
	new cQuery[512];
	format(cQuery, sizeof(cQuery), "UPDATE lockers SET type='%d', posx='%f', posy='%f', posz='%f', interior='%d' WHERE id='%d'",
	lData[lid][lType],
	lData[lid][lPosX],
	lData[lid][lPosY],
	lData[lid][lPosZ],
	lData[lid][lInt],
	lid
	);
	return mysql_tquery(g_SQL, cQuery);
}

function OnLockerCreated(lid)
{
	Locker_Save(lid);
	return 1;
}
