
//DEALER
function LoadcDealerships()
{
	new rows = cache_num_rows(), owner[128], name[128], queryBuffer[212], cdid;
 	if(rows)
  	{
		for(new id; id < rows; id++)
		{
			cache_get_value_name_int(id, "ID", cdid);
			cache_get_value_name(id, "owner", owner);
			format(CarDealershipInfo[cdid][cdOwner], 128, owner);
			cache_get_value_name(id, "name", name);
			format(CarDealershipInfo[cdid][cdMessage], 128, name);
			cache_get_value_name_float(id, "entrancex", CarDealershipInfo[cdid][cdEntranceX]);
			cache_get_value_name_float(id, "entrancey", CarDealershipInfo[cdid][cdEntranceY]);
			cache_get_value_name_float(id, "entrancez", CarDealershipInfo[cdid][cdEntranceZ]);
			cache_get_value_name_int(id, "till", CarDealershipInfo[cdid][cdTill]);
			cache_get_value_name_int(id, "interior", CarDealershipInfo[cdid][cdInterior]);
			cache_get_value_name_float(id, "vehiclespawnx", CarDealershipInfo[cdid][cdVehicleSpawn][0]);
			cache_get_value_name_float(id, "vehiclespawny", CarDealershipInfo[cdid][cdVehicleSpawn][1]);
			cache_get_value_name_float(id, "vehiclespawnz", CarDealershipInfo[cdid][cdVehicleSpawn][2]);
			cache_get_value_name_float(id, "vehiclespawna", CarDealershipInfo[cdid][cdVehicleSpawn][3]);
			cache_get_value_name_float(id, "radius", CarDealershipInfo[cdid][cdRadius]);
			cache_get_value_name_int(id, "price", CarDealershipInfo[cdid][cdPrice]);
			cache_get_value_name_int(id, "type", CarDealershipInfo[cdid][cdType]);
			for (new j = 0; j < 10; j ++)
			{
				format(queryBuffer, 24, "vehiclex%d", j);
				cache_get_value_name_float(id, queryBuffer, CarDealershipInfo[cdid][cdVehicleSpawnX][j]);

				format(queryBuffer, 24, "vehicley%d", j);
				cache_get_value_name_float(id, queryBuffer, CarDealershipInfo[cdid][cdVehicleSpawnY][j]);

				format(queryBuffer, 24, "vehiclez%d", j);
				cache_get_value_name_float(id, queryBuffer, CarDealershipInfo[cdid][cdVehicleSpawnZ][j]);

				format(queryBuffer, 24, "vehiclea%d", j);
				cache_get_value_name_float(id, queryBuffer, CarDealershipInfo[cdid][cdVehicleSpawnAngle][j]);

				format(queryBuffer, 24, "vehicleprice%d", j);
				cache_get_value_name_int(id, queryBuffer, CarDealershipInfo[cdid][cdVehicleCost][j]);

				format(queryBuffer, 24, "vehiclemodel%d", j);
				cache_get_value_name_int(id, queryBuffer, CarDealershipInfo[cdid][cdVehicleModel][j]);
			}
			CarDealershipInfo[cdid][cdID] = cdid;
			CreateDealershipPickup(cdid);
			Iter_Add(Dealership, cdid);
		}
		printf("*** [Database: Loaded] dealership data (%d count).", rows);
	}
}

SavecDealership(id)
{
	new cQuery[5000];
	for (new i = 0; i < 10; i ++)
	{
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE cd SET ");
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sowner = '%s', ", cQuery, CarDealershipInfo[id][cdOwner]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sname = '%s', ", cQuery, CarDealershipInfo[id][cdMessage]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sentrancex = '%f', ", cQuery, CarDealershipInfo[id][cdEntranceX]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sentrancey = '%f', ", cQuery, CarDealershipInfo[id][cdEntranceY]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sentrancez = '%f', ", cQuery, CarDealershipInfo[id][cdEntranceZ]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%still = '%d', ", cQuery, CarDealershipInfo[id][cdTill]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sinterior = '%d', ", cQuery, CarDealershipInfo[id][cdInterior]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclespawnx = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawn][0]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclespawny = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawn][1]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclespawnz = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawn][2]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclespawna = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawn][3]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sradius = '%f', ", cQuery, CarDealershipInfo[id][cdRadius]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sprice = '%d', ", cQuery, CarDealershipInfo[id][cdPrice]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%stype = '%d', ", cQuery, CarDealershipInfo[id][cdType]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclex0 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnX][0]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicley0 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnY][0]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclez0 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnZ][0]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclea0 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnAngle][0]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicleprice0 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleCost][0]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclemodel0 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleModel][0]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclex1 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnX][1]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicley1 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnY][1]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclez1 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnZ][1]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclea1 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnAngle][1]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicleprice1 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleCost][1]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclemodel1 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleModel][1]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclex2 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnX][2]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicley2 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnY][2]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclez2 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnZ][2]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclea2 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnAngle][2]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicleprice2 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleCost][2]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclemodel2 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleModel][2]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclex3 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnX][3]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicley3 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnY][3]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclez3 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnZ][3]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclea3 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnAngle][3]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicleprice3 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleCost][3]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclemodel3 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleModel][3]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclex4 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnX][4]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicley4 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnY][4]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclez4 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnZ][4]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclea4 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnAngle][4]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicleprice4 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleCost][4]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclemodel4 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleModel][4]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclex5 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnX][5]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicley5 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnY][5]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclez5 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnZ][5]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclea5 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnAngle][5]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicleprice5 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleCost][5]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclemodel5 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleModel][5]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclex6 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnX][6]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicley6 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnY][6]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclez6 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnZ][6]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclea6 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnAngle][6]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicleprice6 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleCost][6]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclemodel6 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleModel][6]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclex7 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnX][7]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicley7 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnY][7]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclez7 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnZ][7]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclea7 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnAngle][7]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicleprice7 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleCost][7]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclemodel7 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleModel][7]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclex8 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnX][8]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicley8 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnY][8]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclez8 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnZ][8]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclea8 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnAngle][8]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicleprice8 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleCost][8]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclemodel8 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleModel][8]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclex9 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnX][9]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicley9 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnY][9]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclez9 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnZ][9]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclea9 = '%f', ", cQuery, CarDealershipInfo[id][cdVehicleSpawnAngle][9]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehicleprice9 = '%d', ", cQuery, CarDealershipInfo[id][cdVehicleCost][9]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%svehiclemodel9 = '%d' ", cQuery, CarDealershipInfo[id][cdVehicleModel][9]);
		
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s WHERE ID = '%d'", cQuery, CarDealershipInfo[id][cdID]);
		mysql_tquery(g_SQL, cQuery);
    }
	return mysql_tquery(g_SQL, cQuery);
}    

function cdDealer(dealershipid)
{
	SavecDealership(dealershipid);
	CreateDealershipPickup(dealershipid);
	return 1;
}

CreateDealershipPickup(d)
{
	DestroyDynamic3DTextLabel(CarDealershipInfo[d][cdTextLabel]);
	DestroyDynamicPickup(CarDealershipInfo[d][cdPickupID]);
	new String[500];
	if(CarDealershipInfo[d][cdEntranceX] != 0.0 && CarDealershipInfo[d][cdEntranceY] != 0.0)
	{
		CarDealershipInfo[d][cdPickupID] = CreateDynamicPickup(1239, 1, CarDealershipInfo[d][cdEntranceX], CarDealershipInfo[d][cdEntranceY], CarDealershipInfo[d][cdEntranceZ]);
		if(strcmp(CarDealershipInfo[d][cdOwner], "-"))
		{
			format(String, sizeof(String),"{00FFFF}[id:%d]\n{FFFF00}%s\n"YELLOW_E"Owner: "WHITE_E"%s",d, CarDealershipInfo[d][cdMessage], CarDealershipInfo[d][cdOwner]);
			CarDealershipInfo[d][cdTextLabel] = CreateDynamic3DTextLabel(String,COLOR_TWAQUA,CarDealershipInfo[d][cdEntranceX], CarDealershipInfo[d][cdEntranceY], CarDealershipInfo[d][cdEntranceZ]+0.75,3.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1);
		}
		else
		{
			format(String, sizeof(String), "{00FFFF}[id:%d]\n"WHITE_E"This dealership for sale\n{FFFFFF}Price: "GREEN_E"$%s\n"WHITE_E"Use '"YELLOW_E"/buydealership"WHITE_E"' for purchase this dealership",d, FormatMoney(CarDealershipInfo[d][cdPrice]));
			CarDealershipInfo[d][cdTextLabel] = CreateDynamic3DTextLabel(String,COLOR_TWAQUA,CarDealershipInfo[d][cdEntranceX], CarDealershipInfo[d][cdEntranceY], CarDealershipInfo[d][cdEntranceZ]+0.75,3.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1);
		}
	}
	for(new fv = 0; fv < MAX_DEALERSHIPVEHICLES; fv++)
	{
		DestroyDynamic3DTextLabel(CarDealershipInfo[d][cdVehicleLabel][fv]);
		if (IsValidVehicle(CarDealershipInfo[d][cdVehicleId][fv]))
			DestroyVehicle(CarDealershipInfo[d][cdVehicleId][fv]), CarDealershipInfo[d][cdVehicleId][fv] = INVALID_VEHICLE_ID;
		if(CarDealershipInfo[d][cdVehicleModel][fv] != 0 && CarDealershipInfo[d][cdVehicleSpawnX][fv] != 0.0 && CarDealershipInfo[d][cdVehicleSpawnY][fv] != 0.0)
		{
			CarDealershipInfo[d][cdVehicleId][fv] = CreateVehicle(CarDealershipInfo[d][cdVehicleModel][fv], CarDealershipInfo[d][cdVehicleSpawnX][fv], CarDealershipInfo[d][cdVehicleSpawnY][fv], CarDealershipInfo[d][cdVehicleSpawnZ][fv], CarDealershipInfo[d][cdVehicleSpawnAngle][fv], -1, -1, -1);
			if(IsValidVehicle(CarDealershipInfo[d][cdVehicleId][fv]))
			{
				format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",fv, GetVehicleName(CarDealershipInfo[d][cdVehicleId][fv]), FormatMoney(CarDealershipInfo[d][cdVehicleCost][fv]));
				CarDealershipInfo[d][cdVehicleLabel][fv] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,8.0,INVALID_PLAYER_ID,CarDealershipInfo[d][cdVehicleId][fv]);
				SetVehicleNumberPlate(CarDealershipInfo[d][cdVehicleId][fv],""GREEN_E"DEALER");
				SetValidVehicleHealth(CarDealershipInfo[d][cdVehicleId][fv], 1000);
			}
		}
		else if(CarDealershipInfo[d][cdVehicleModel][fv] == 0 && CarDealershipInfo[d][cdVehicleSpawnX][fv] != 0.0 && CarDealershipInfo[d][cdVehicleSpawnY][fv] != 0.0)
		{
			format(String, sizeof(String), "[slot:%d]\n"GREEN_E"No vehicle to preview\n"WHITE_E"Use '"YELLOW_E"/dm > Vehicles"WHITE_E"' to display vehicle here",fv);
			CarDealershipInfo[d][cdVehicleLabel][fv] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,CarDealershipInfo[d][cdVehicleSpawnX][fv], CarDealershipInfo[d][cdVehicleSpawnY][fv], CarDealershipInfo[d][cdVehicleSpawnZ][fv],8.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID);
		}
	}
	return 1;
}

SellCarDealership(dealershipid)
{
	CarDealershipInfo[dealershipid][cdOwned] = 0;
	strmid(CarDealershipInfo[dealershipid][cdOwner], "-", 0, MAX_PLAYER_NAME, 255);
	new String[1024];
	format(String, sizeof(String), "{00FFFF}[id:%d]\n"WHITE_E"This dealership for sale\n{FFFFFF}Price: "GREEN_E"$%s\n"WHITE_E"Use '"YELLOW_E"/buydealership"WHITE_E"' for purchase this dealership",dealershipid, FormatMoney(CarDealershipInfo[dealershipid][cdPrice]));
	UpdateDynamic3DTextLabelText(CarDealershipInfo[dealershipid][cdTextLabel], COLOR_TWAQUA, String);
	SavecDealership(dealershipid);
}

IsPlayerOwnerOfCDEx(playerid, id)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(id == -1) return 0;
	if(!strcmp(CarDealershipInfo[id][cdOwner], pData[playerid][pName], true)) return 1;
	return 0;
}

forward Vehicle_Dealer(playerid, dealershipid, cdvehicleid, modelid, price, x, y, z, a);
public Vehicle_Dealer(playerid, dealershipid, cdvehicleid, modelid, price, x, y, z, a)
{
	CarDealershipInfo[dealershipid][cdVehicleDBID][cdvehicleid] = cache_insert_id();
	CarDealershipInfo[dealershipid][cdVehicleModel][cdvehicleid] = modelid;
    CarDealershipInfo[dealershipid][cdVehicleCost][cdvehicleid] = price;
    CarDealershipInfo[dealershipid][cdVehicleSpawnX][cdvehicleid] = x;
    CarDealershipInfo[dealershipid][cdVehicleSpawnY][cdvehicleid] = y;
    CarDealershipInfo[dealershipid][cdVehicleSpawnZ][cdvehicleid] = z;
    CarDealershipInfo[dealershipid][cdVehicleSpawnAngle][cdvehicleid] = a;

	SavecDealership(dealershipid);
	return 1;
}

DestroyCarDealershipVehicle(dealershipid, cdvehicleid)
{
	new query[128];
    CarDealershipInfo[dealershipid][cdVehicleModel][cdvehicleid] = 0;
    CarDealershipInfo[dealershipid][cdVehicleCost][cdvehicleid] = 0;
    CarDealershipInfo[dealershipid][cdVehicleSpawnX][cdvehicleid] = 0.0;
    CarDealershipInfo[dealershipid][cdVehicleSpawnY][cdvehicleid] = 0.0;
    CarDealershipInfo[dealershipid][cdVehicleSpawnZ][cdvehicleid] = 0.0;
    CarDealershipInfo[dealershipid][cdVehicleSpawnAngle][cdvehicleid] = 0.0;
    DestroyDynamic3DTextLabel(CarDealershipInfo[dealershipid][cdVehicleLabel][cdvehicleid]);
    DestroyVehicle(CarDealershipInfo[dealershipid][cdVehicleId][cdvehicleid]);
    CarDealershipInfo[dealershipid][cdVehicleLabel][cdvehicleid] = Text3D:INVALID_3DTEXT_ID;
    CarDealershipInfo[dealershipid][cdVehicleId][cdvehicleid] = 0;
	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM vehicledealer WHERE id=%d", CarDealershipInfo[dealershipid][cdVehicleDBID][cdvehicleid]);
	mysql_tquery(g_SQL, query);
}

IsAVehicleDealerVeh(carid)
{
	foreach(new d : Dealership)
    {
		for(new v = 0; v < MAX_DEALERSHIPVEHICLES; v++) 
		{
			if(carid == CarDealershipInfo[d][cdVehicleId][v]) return 1;
		}
	}	
	return 0;
}

GetCarDealershipVehicleId(vehicleid)
{
    foreach(new d : Dealership)
    {
        for(new v = 0; v < MAX_DEALERSHIPVEHICLES; v++)
        {
            if(vehicleid == CarDealershipInfo[d][cdVehicleId][v])
            {
                return v;
            }
		}
    }
    return 0;
}

GetCarDealershipId(vehicleid)
{
    foreach(new d : Dealership)
    {
        for(new v = 0; v < MAX_DEALERSHIPVEHICLES; v++)
        {
            if(CarDealershipInfo[d][cdVehicleId][v] == vehicleid)
            {
                return d;
            }
		}
    }
    return -1;
}

Dealer_IsEmployee(playerid, id) {
	new str[128], Cache: cache;
	format(str, sizeof(str), "SELECT * FROM `cd_employee` WHERE `Name`='%s' AND `Biz`='%d'", ReturnName(playerid), CarDealershipInfo[id][cdID]);
	cache = mysql_query(g_SQL, str);
	new result = cache_num_rows();
	cache_delete(cache);
	return result;
}

Dealer_ShowEmployee(playerid, id, type = 0)
{
	new query[255], Cache: cache;
	format(query, sizeof(query), "SELECT * FROM `cd_employee` WHERE `Biz`='%d'", CarDealershipInfo[id][cdID]);
	cache = mysql_query(g_SQL, query);

	if(!cache_num_rows()) return Error(playerid, "There are no one employee for this business.");
	
	format(query, sizeof(query), "#\tName\tDate Added\n");
	for(new i; i < cache_num_rows(); i++) {
		new biz,
            time,
			name[24];

        cache_get_value_int(i, "ID", biz);
		cache_get_value_int(i, "Time", time);
		cache_get_value(i, "Name", name, sizeof(name));
		format(query, sizeof(query), "%s%d\t%s\t%s\n", query, biz, name, experieddate(time,3));
	}
	if (!type)
		Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Business Employee", query, "Close", "");
	else
		Dialog_Show(playerid, Dealer_RemoveEmployee, DIALOG_STYLE_TABLIST_HEADERS, "Remove Employee", query, "Remove", "Close");

	cache_delete(cache);
	return 1;
}

DealerEmployee_Remove(id)
{
	new query[200];
	format(query,sizeof(query),"DELETE FROM `cd_employee` WHERE `ID`='%d'", id);
	mysql_tquery(g_SQL, query);
	return 1;
}

DealerEmployee_RemoveAll(bizid)
{
	new query[200];
	format(query,sizeof(query),"DELETE FROM `cd_employee` WHERE `Biz`='%d'", CarDealershipInfo[bizid][cdID]);
	mysql_tquery(g_SQL, query);
	return 1;
}

DealerEmployee_GetCount(bizid)
{
	new query[144], Cache: check, count;
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `cd_employee` WHERE `Biz` = '%d'", CarDealershipInfo[bizid][cdID]);
	check = mysql_query(g_SQL, query);
	new result = cache_num_rows();
	if(result) {
		for(new i; i != result; i++) {
			count++;
		}
	}
	cache_delete(check);
	return count;
}

DealerEmployee_Add(playerid, bizid)
{
	new str[128];
	format(str, sizeof(str), "INSERT INTO `cd_employee` SET `Name`='%s', `Biz`='%d', `Time`=UNIX_TIMESTAMP()", pData[playerid][pName], CarDealershipInfo[bizid][cdID]);
	mysql_tquery(g_SQL, str);
	return 1;
}
