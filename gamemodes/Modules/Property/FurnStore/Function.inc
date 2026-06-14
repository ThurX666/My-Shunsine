
function FurnStore_Load()
{
	for(new index = 0; index != cache_num_rows(); index++)
	{
		new id = Iter_Free(FurnStore);

		Iter_Add(FurnStore, index);

		cache_get_value_int(index, "id", storeData[id][storeID]);
		cache_get_value_int(index, "owner", storeData[id][storeOwner]);
		cache_get_value_int(index, "price", storeData[id][storePrice]);
		cache_get_value_int(index, "vault", storeData[id][storeVault]);
		cache_get_value_int(index, "employe1", storeData[id][storeEmploye][0]);
		cache_get_value_int(index, "employe2", storeData[id][storeEmploye][1]);
		cache_get_value_int(index, "employe3", storeData[id][storeEmploye][2]);
		cache_get_value_int(index, "seal", storeData[id][storeSeal]);

		cache_get_value(index, "name", storeData[id][storeName], 32);
		cache_get_value(index, "ownername", storeData[id][storeOwnerName], MAX_PLAYER_NAME);

		cache_get_value_float(index, "x", storeData[id][storePos][0]);
		cache_get_value_float(index, "y", storeData[id][storePos][1]);
		cache_get_value_float(index, "z", storeData[id][storePos][2]);

		cache_get_value_float(index, "i_x", storeData[id][storeIntPos][0]);
		cache_get_value_float(index, "i_y", storeData[id][storeIntPos][1]);
		cache_get_value_float(index, "i_z", storeData[id][storeIntPos][2]);

		storeData[id][storeLocked] = 1;

		FurnStore_Refresh(id);
	}
	printf("*** [Database: Loaded] furnstore data (%d count).", cache_num_rows());
	return 1;
}

function OnFurnstoreCreated(index)
{
	storeData[index][storeID] = cache_insert_id();

	FurnStore_Save(index);
	FurnStore_Refresh(index);
	return 1;
}

FurnStore_Save(index)
{
	if(Iter_Contains(FurnStore, index))
	{
		new query[500];
		format(query, sizeof(query), "UPDATE `furnstore` SET `ownername` ='%s', `name` ='%s', `x` =%.1f, `y` =%.1f, `z` =%.1f, `i_x` =%.1f, `owner` =%d, `price`=%d, `vault` =%d, `employe1` =%d, `employe2` =%d, `employe3` =%d, `i_y` =%.1f, `i_z` =%.1f, `seal`=%d WHERE `id` = %d",
			storeData[index][storeOwnerName],
			storeData[index][storeName],
			storeData[index][storePos][0],
			storeData[index][storePos][1],
			storeData[index][storePos][2],
			storeData[index][storeIntPos][0],
			storeData[index][storeOwner],
			storeData[index][storePrice],
			storeData[index][storeVault],
			storeData[index][storeEmploye][0],
			storeData[index][storeEmploye][1],
			storeData[index][storeEmploye][2],
			storeData[index][storeIntPos][1],
			storeData[index][storeIntPos][2],
			storeData[index][storeSeal],
			storeData[index][storeID]
		);

		mysql_tquery(g_SQL, query);
	}
	return 1;
}

FurnStore_Create(playerid, price)
{
	new index = cellmin;

	if((index = Iter_Free(FurnStore)) != cellmin)
	{
		Iter_Add(FurnStore, index);

		new Float:x, Float:y, Float:z;

		GetPlayerPos(playerid, x, y, z);

		storeData[index][storePos][0] = x;
		storeData[index][storePos][1] = y;
		storeData[index][storePos][2] = z;

		storeData[index][storeIntPos][0] = 1464.39;
		storeData[index][storeIntPos][1] = 1768.27;
		storeData[index][storeIntPos][2] = 10.90;

		storeData[index][storePrice] = price;
		storeData[index][storeOwner] = 0;
		storeData[index][storeVault] = 0;
		storeData[index][storeEmploye][0] = storeData[index][storeEmploye][1] = storeData[index][storeEmploye][2] = 0;
		storeData[index][storeSeal] = 0;
		storeData[index][storeLocked] = 1;

		mysql_tquery(g_SQL, "INSERT INTO `furnstore` (`price`) VALUES (1)", "OnFurnstoreCreated", "d", index);

		return index;
	}
	return cellmin;
}

FurnStore_Refresh(index)
{
	if(Iter_Contains(FurnStore, index))
	{
		if(IsValidDynamicPickup(storeData[index][storePickup]))
			DestroyDynamicPickup(storeData[index][storePickup]);

		if(IsValidDynamic3DTextLabel(storeData[index][storeLabel]))
			DestroyDynamic3DTextLabel(storeData[index][storeLabel]);

		if(IsValidDynamicCP(storeData[index][storeCP]))
			DestroyDynamicCP(storeData[index][storeCP]);

		if(storeData[index][storeOwner])  {
			if (storeData[index][storeSeal]) {
				new string[212];
				format(string, sizeof(string), "[ID:%d]\n%s\n"WHITE_E"Owned by: "YELLOW_E"%s\n"WHITE_E"This furniture store is sealed by "RED_E"authority", index, storeData[index][storeName], storeData[index][storeOwnerName]);
				storeData[index][storeLabel] = CreateDynamic3DTextLabel(string, COLOR_BLUE, storeData[index][storePos][0], storeData[index][storePos][1], storeData[index][storePos][2]+0.5, 10, _, _, 1, 0, 0);
			} else {
				new string[212];
				format(string, sizeof(string), "[ID:%d]\n%s\n"WHITE_E"Owned by: "YELLOW_E"%s\n"WHITE_E"This furniture store is sealed by "RED_E"authority", index, storeData[index][storeName], storeData[index][storeOwnerName]);
				storeData[index][storeLabel] = CreateDynamic3DTextLabel(string, COLOR_BLUE, storeData[index][storePos][0], storeData[index][storePos][1], storeData[index][storePos][2]+0.5, 10, _, _, 1, 0, 0);
			}
		}
		else {
			new string[212];
			format(string, sizeof(string), "[ID:%d]\n"GREEN_E"This Furniture Store is for sale\n"WHITE_E"Price: "YELLOW_E"$%s\n"WHITE_E"Type /buyfurnstore to buy this", index, FormatMoney(storeData[index][storePrice]));
			storeData[index][storeLabel] = CreateDynamic3DTextLabel(string, COLOR_BLUE, storeData[index][storePos][0], storeData[index][storePos][1], storeData[index][storePos][2]+0.5, 10, _, _, 1, 0, 0);
		}

		storeData[index][storePickup] = CreateDynamicPickup(1239, 23, storeData[index][storePos][0], storeData[index][storePos][1], storeData[index][storePos][2], 0, 0, _, 5);
		storeData[index][storeCP] = CreateDynamicCP(storeData[index][storePos][0], storeData[index][storePos][1], storeData[index][storePos][2], 1.5, 0, 0, _, 3);
	}
	return 1;
}

FurnStore_Nearest(playerid)
{
	foreach(new i : FurnStore) if(IsPlayerInRangeOfPoint(playerid, 4, storeData[i][storePos][0], storeData[i][storePos][1], storeData[i][storePos][2]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0) {
		return i;
	}
	return -1;
}

FurnStore_Inside(playerid)
{
	if(pData[playerid][pFurnStore] != -1)
	{
		foreach(new i : FurnStore) if(storeData[i][storeID] == pData[playerid][pFurnStore] && GetPlayerInterior(playerid) == 3 && GetPlayerVirtualWorld(playerid) == (storeData[i][storeID]+1)) {
			return i;
		}
	}
	return -1;
}

FurnStore_IsOwner(playerid, index)
{
	if(pData[playerid][pID] == -1)
		return 0;

	if((Iter_Contains(FurnStore, index) && storeData[index][storeOwner] != 0) && storeData[index][storeOwner] == pData[playerid][pID])
		return 1;

	return 0;
}

FurnStore_IsEmployee(playerid, index)
{
	if(pData[playerid][pID] == -1)
		return 0;

	if(Iter_Contains(FurnStore, index) && storeData[index][storeOwner] != 0) {
		for(new i = 0; i != MAX_EMPLOYE; i++) if(storeData[index][storeEmploye][i] == pData[playerid][pID]) {
			return 1;
		}
	}
	return 0;
}

stock FurnStore_GetCount(playerid) {
	new count = 0;
	foreach (new i : FurnStore) if (storeData[i][storeOwner] == pData[playerid][pID]) count++;
	return count;
}

GetDataByIndex(index, type = 0)
{
	new name[MAX_PLAYER_NAME] = "None",
		seen,
		Cache:getname,
		string[212];
	mysql_format(g_SQL, string, sizeof(string), "SELECT `%s` FROM `characters` WHERE `ID`='%d'", !type ? ("Character") : ("LoginDate"), index);
	getname = mysql_query(g_SQL, string);
	if(cache_num_rows()) {
		if(!type)
			cache_get_value(0, "Character", name);
		else {
			cache_get_value_int(0, "LoginDate", seen);
			format(name, MAX_PLAYER_NAME, "%s", GetDuration(gettime()-seen));
		}
	}
	cache_delete(getname);
	return name;
}

Employee_List(playerid, index)
{
	if(!Iter_Contains(FurnStore, index))
		return 0;

	new info[128],
		employe_count = 0;

	strcat(info, "Slot\tEmployee\tLast Login\n");
	for(new i = 0; i != MAX_EMPLOYE; i++) if(storeData[index][storeEmploye][i] > 0)
	{
		format(info, sizeof(info), "%s%d\t%s\t%s\n", info, i+1, GetDataByIndex(storeData[index][storeEmploye][i]), GetDataByIndex(storeData[index][storeEmploye][i], 1));
		SelectToFired[playerid][employe_count++] = i;
	}
	if(employe_count != MAX_EMPLOYE)
		format(info, sizeof(info), "%sHire\tNew employee\t-\n", info);

	Dialog_Show(playerid, FurnStoreEmployee, DIALOG_STYLE_TABLIST_HEADERS, "Employee Management", info, "Hire/Fire", "Close");
	return 1;
}

function editFurnObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:offx, Float:offy, Float:offz)
{
	if(response == EDIT_RESPONSE_CANCEL)
	{
		if(editFurnPosition[playerid] != -1) 
		{
			new i = editFurnPosition[playerid];
			FurnObject_Refresh(i);
			
			editFurnPosition[playerid] = -1;
		}
	}
	if(response == EDIT_RESPONSE_FINAL)
	{
		new id = editFurnPosition[playerid];

		if(Iter_Contains(FurnObject, id))
		{
			FurnStore[id][furnPos][0] = x;
			FurnStore[id][furnPos][1] = y;
			FurnStore[id][furnPos][2] = z;
			FurnStore[id][furnRot][0] = rx;
			FurnStore[id][furnRot][1] = ry;
			FurnStore[id][furnRot][2] = rz;

			FurnObject_Refresh(id);
			FurnObject_Save(id);

			editFurnPosition[playerid] = -1;
		}
	}
	return 1;
}

function FurnObject_Load(index)
{
	new query[32], id = cellmin;

	for(new i = 0; i != cache_num_rows(); i++) if ((id = Iter_Free(FurnObject)) != cellmin)
	{
		Iter_Add(FurnObject, id);

		cache_get_value(i, "name", FurnStore[id][furnName], 32);

		cache_get_value(i, "materials", query, 32);
		sscanf(query, "p<|>dddddddddddddddd", 
			FurnStore[id][furnMaterials][0],
			FurnStore[id][furnMaterials][1],
			FurnStore[id][furnMaterials][2],
			FurnStore[id][furnMaterials][3],
			FurnStore[id][furnMaterials][4],
			FurnStore[id][furnMaterials][5],
			FurnStore[id][furnMaterials][6],
			FurnStore[id][furnMaterials][7],
			FurnStore[id][furnMaterials][8],
			FurnStore[id][furnMaterials][9],
			FurnStore[id][furnMaterials][10],
			FurnStore[id][furnMaterials][11],
			FurnStore[id][furnMaterials][12],
			FurnStore[id][furnMaterials][13],
			FurnStore[id][furnMaterials][14],
			FurnStore[id][furnMaterials][15]
		);

		cache_get_value_int(i, "id", FurnStore[id][furnID]);
		cache_get_value_int(i, "model", FurnStore[id][furnModel]);

		cache_get_value_float(i, "x", FurnStore[id][furnPos][0]);
		cache_get_value_float(i, "y", FurnStore[id][furnPos][1]);
		cache_get_value_float(i, "z", FurnStore[id][furnPos][2]);
		cache_get_value_float(i, "rx", FurnStore[id][furnRot][0]);
		cache_get_value_float(i, "ry", FurnStore[id][furnRot][1]);
		cache_get_value_float(i, "rz", FurnStore[id][furnRot][2]);
		
		cache_get_value_int(i, "price", FurnStore[id][furnPrice]);
		cache_get_value_int(i, "stock", FurnStore[id][furnStock]);
		cache_get_value_int(i, "storeid", FurnStore[id][furnStoreId]);

		FurnObject_Refresh(id);
	}
	printf("*** [Database: Loaded] furnobject data (%d count).", cache_num_rows());
	return 1;
}

FurnObject_Save(index)
{
	if(Iter_Contains(FurnObject, index))
	{
		new query[500];

		format(query, sizeof(query), "UPDATE `furnobject` SET model=%d,name='%s',x=%.3f,y=%.3f,z=%.3f,rx=%.3f,ry=%.3f,rz=%.3f", 
			FurnStore[index][furnModel],
			FurnStore[index][furnName],
			FurnStore[index][furnPos][0],
			FurnStore[index][furnPos][1],
			FurnStore[index][furnPos][2],
			FurnStore[index][furnRot][0],
			FurnStore[index][furnRot][1],
			FurnStore[index][furnRot][2]
		);
		format(query, sizeof(query), "%s, price=%d,stock=%d,storeid=%d,materials='%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d' WHERE id=%d", 
			query,
			FurnStore[index][furnPrice],
			FurnStore[index][furnStock],
			FurnStore[index][furnStoreId],
			FurnStore[index][furnMaterials][0],
			FurnStore[index][furnMaterials][1],
			FurnStore[index][furnMaterials][2],
			FurnStore[index][furnMaterials][3],
			FurnStore[index][furnMaterials][4],
			FurnStore[index][furnMaterials][5],
			FurnStore[index][furnMaterials][6],
			FurnStore[index][furnMaterials][7],
			FurnStore[index][furnMaterials][8],
			FurnStore[index][furnMaterials][9],
			FurnStore[index][furnMaterials][10],
			FurnStore[index][furnMaterials][11],
			FurnStore[index][furnMaterials][12],
			FurnStore[index][furnMaterials][13],
			FurnStore[index][furnMaterials][14],
			FurnStore[index][furnMaterials][15],
			FurnStore[index][furnID]
		);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

FurnObject_Sync(index)
{
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnStore[index][furnObject], E_STREAMER_X, FurnStore[index][furnPos][0]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnStore[index][furnObject], E_STREAMER_Y, FurnStore[index][furnPos][1]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnStore[index][furnObject], E_STREAMER_Z, FurnStore[index][furnPos][2]);

	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnStore[index][furnObject], E_STREAMER_R_X, FurnStore[index][furnRot][0]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnStore[index][furnObject], E_STREAMER_R_Y, FurnStore[index][furnRot][1]);
	Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnStore[index][furnObject], E_STREAMER_R_Z, FurnStore[index][furnRot][2]);

	Streamer_SetIntData(STREAMER_TYPE_OBJECT, FurnStore[index][furnObject], E_STREAMER_MODEL_ID, FurnStore[index][furnModel]);

	for(new i = 0; i != MAX_MATERIALS; i++) if(FurnStore[index][furnMaterials][i] > 0) {
		SetDynamicObjectMaterial(FurnStore[index][furnObject], i, GetTModel(FurnStore[index][furnMaterials][i]), GetTXDName(FurnStore[index][furnMaterials][i]), GetTextureName(FurnStore[index][furnMaterials][i]), 0);
	}
	return 1;
}

FurnObject_Refresh(index)
{
	if(Iter_Contains(FurnObject, index)) 
	{
		if(!IsValidDynamicObject(FurnStore[index][furnObject]))
		{
			FurnStore[index][furnObject] = CreateDynamicObject(FurnStore[index][furnModel], 
				FurnStore[index][furnPos][0], FurnStore[index][furnPos][1], FurnStore[index][furnPos][2], 
				FurnStore[index][furnRot][0], FurnStore[index][furnRot][1], FurnStore[index][furnRot][2], 
				(FurnStore[index][furnStoreId]+1), 3
			);
		}
		FurnObject_Sync(index);	    
			
		if(IsValidDynamic3DTextLabel(FurnStore[index][furnLabel]))
			DestroyDynamic3DTextLabel(FurnStore[index][furnLabel]);

		new string[212];
		format(string, sizeof(string), ""AQUA_E"[id:%d]\n"YELLOW_E"%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Stock: "GREEN_E"%d", index, FurnStore[index][furnName], FormatMoney(FurnStore[index][furnPrice]), FurnStore[index][furnStock]);
		FurnStore[index][furnLabel] = CreateDynamic3DTextLabel(string, COLOR_BLUE, FurnStore[index][furnPos][0], FurnStore[index][furnPos][1], FurnStore[index][furnPos][2], 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, (FurnStore[index][furnStoreId]+1), 3);

		foreach(new i : Player) if(IsPlayerInRangeOfPoint(i, 5, FurnStore[index][furnPos][0], FurnStore[index][furnPos][1], FurnStore[index][furnPos][2])) {
			Streamer_Update(i);
		}
	}
	return 1;
}

FurnObject_List(playerid, index)
{
	if(Iter_Contains(FurnStore, index))
	{
		new count = 0,
			info[MAX_FURNSTORE_OBJECT * 128];

		strcat(info, "Furniture\tSlot (ID)\tDistance (meters)\n");
		foreach(new i : FurnObject) if(FurnStore[i][furnStoreId] == storeData[index][storeID])
		{
			format(info, sizeof(info), "%s%s\t%d\t%.1f\n", info, FurnStore[i][furnName], i, GetPlayerDistanceFromPoint(playerid, FurnStore[i][furnPos][0], FurnStore[i][furnPos][1], FurnStore[i][furnPos][2]));
			ListedFurnObject[playerid][count] = i;
			count++;
		}
		if(count != MAX_FURNSTORE_OBJECT)
			format(info, sizeof(info), "%sAdd New\t\n", info);

		Dialog_Show(playerid, ManageFurn, DIALOG_STYLE_TABLIST_HEADERS, "Exhibits", info, "Select", "Back");
		printf("FurnObject_List: playerid(%d) listed %d furniture objects from storeid(%d)", playerid, count, index);
	}
	return 1;
}

FurnObject_Category(playerid)
{
	new string[120];
	for (new i = 0; i < sizeof(g_aFurnitureTypes); i ++) {
		format(string, sizeof(string), "%s%s\n", string, g_aFurnitureTypes[i]);
	}
	Dialog_Show(playerid, SelectType, DIALOG_STYLE_LIST, "Object Category", string, "Modify", "Cancel");
	return 1;
}

FurnObject_Count(index)
{
	new count = 0;

	foreach(new i : FurnObject) if(FurnStore[i][furnStoreId] == storeData[index][storeID]) {
		count++;
	}
	return count;
}

FurnObject_Add(playerid, objectid, index)
{
	if(FurnObject_Count(index) >= MAX_FURNSTORE_OBJECT) return -1;

	if (pData[playerid][pComponent] < 30)
		return Error(playerid, "You need 30 components to create new furniture.");

	new id = Iter_Free(FurnObject),
		Float:x, Float:y, Float:z;

	if (id == cellmin)
		return Error(playerid, "Server has reached the maximum of furniture object!");

	GetPlayerPos(playerid, x, y, z);

	format(FurnStore[id][furnName], 32, "Unnamed");

	FurnStore[id][furnPos][0] = x;
	FurnStore[id][furnPos][1] = y;
	FurnStore[id][furnPos][2] = z;
	FurnStore[id][furnRot][0] = 0;
	FurnStore[id][furnRot][1] = 0;
	FurnStore[id][furnRot][2] = 0;

	FurnStore[id][furnModel] = objectid;
	FurnStore[id][furnStoreId] = storeData[index][storeID];
	FurnStore[id][furnPrice] = 0;
	FurnStore[id][furnStock] = 0;
	pData[playerid][pComponent] -= 30;

	Iter_Add(FurnObject, id);

	mysql_tquery(g_SQL, "INSERT INTO `furnobject`(`price`) VALUES (0)", "FurnObject_Created", "d", id);
	
	FurnObject_Refresh(id);
	Streamer_Update(playerid);
	return id;
}

function FurnObject_Created(index)
{
	FurnStore[index][furnID] = cache_insert_id();
	
	FurnObject_Save(index);
	return 1;
}
