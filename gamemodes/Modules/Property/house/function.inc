
function OnHousesCreated(hid)
{
    new id;
	House_Save(hid);
    CreateHouseInterior(hid);
    for (new i = 0; i < sizeof(g_aHouseInteriors); i ++) if (g_aHouseInteriors[i][e_Type] == hData[hid][hType]) {
        if ((id = Iter_Free(HouseStruct[hid])) != cellmin) {
            Iter_Add(HouseStruct[hid], id);
            
            HouseStructure[hid][id][structureModel] = g_aHouseInteriors[i][e_ObjModel];
            HouseStructure[hid][id][structurePos][0] = g_aHouseInteriors[i][e_ObjPosX];
            HouseStructure[hid][id][structurePos][1] = g_aHouseInteriors[i][e_ObjPosY];
            HouseStructure[hid][id][structurePos][2] = g_aHouseInteriors[i][e_ObjPosZ];
            HouseStructure[hid][id][structureRot][0] = g_aHouseInteriors[i][e_ObjRotX];
            HouseStructure[hid][id][structureRot][1] = g_aHouseInteriors[i][e_ObjRotY];
            HouseStructure[hid][id][structureRot][2] = g_aHouseInteriors[i][e_ObjRotZ];
            HouseStructure[hid][id][structureMaterial] = 0;
            HouseStructure[hid][id][structureColor] = 0;
            HouseStructure[hid][id][structureType] = 1;

            HouseStructure_Refresh(id, hid);
            new query[128];
            mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `housestruct` (`HouseID`) VALUES ('%d')", hid);
            mysql_tquery(g_SQL, query, "OnHouseStructureCreated", "dd", id, hid);
        }
    }
	return 1;
}

House_RemoveFurniture(houseid)
{
    if(Iter_Contains(Houses, houseid))
    {
        foreach (new furnitureid : HouseFurnitures[houseid]) {
            new query[128];
            mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `furniture` WHERE `furnitureID` = '%d'", FurnitureData[houseid][furnitureid][furnitureID]);
            mysql_tquery(g_SQL, query);
            if (IsValidDynamicObject(FurnitureData[houseid][furnitureid][furnitureObject])) {
                DestroyDynamicObject(FurnitureData[houseid][furnitureid][furnitureObject]);
                FurnitureData[houseid][furnitureid][furnitureObject] = INVALID_STREAMER_ID;
            }

            new tmp_furniture[furnitureData];
            FurnitureData[houseid][furnitureid] = tmp_furniture;

            new current = furnitureid;
            Iter_SafeRemove(HouseFurnitures[houseid], current, furnitureid);
        }
    }
    return 1;
}

Furniture_GetCount(houseid) {
    return Iter_Count(HouseFurnitures[houseid]);
}

Furniture_GetMaxItems(houseid) {
    new maxItems = 0;

    switch (hData[houseid][hType]) {
        case 1: maxItems = 100; // Small house
        case 2: maxItems = 150; // Medium house
        case 3: maxItems = 200; // Big house
    }

    return maxItems;
}

Furniture_Refresh(furnitureid, houseid)
{
    if(Iter_Contains(HouseFurnitures[houseid], furnitureid))
    {
        if(!IsValidDynamicObject(FurnitureData[houseid][furnitureid][furnitureObject])) {
            if(FurnitureData[houseid][furnitureid][furnitureUnused] == 0)
            {
                FurnitureData[houseid][furnitureid][furnitureObject] = CreateDynamicObject(
                    FurnitureData[houseid][furnitureid][furnitureModel],
                    FurnitureData[houseid][furnitureid][furniturePos][0],
                    FurnitureData[houseid][furnitureid][furniturePos][1],
                    FurnitureData[houseid][furnitureid][furniturePos][2],
                    FurnitureData[houseid][furnitureid][furnitureRot][0],
                    FurnitureData[houseid][furnitureid][furnitureRot][1],
                    FurnitureData[houseid][furnitureid][furnitureRot][2],
                    houseid,
                    hData[houseid][hInt]
                );
            }
        }
        Furniture_Update(furnitureid, houseid);

        foreach(new i : Player) if(IsPlayerInRangeOfPoint(i, 5, FurnitureData[houseid][furnitureid][furniturePos][0], FurnitureData[houseid][furnitureid][furniturePos][1], FurnitureData[houseid][furnitureid][furniturePos][2])) {
			Streamer_Update(i);
		}
    }
    return 1;
}

Furniture_Update(furnitureid, houseid) {
    if(Iter_Contains(HouseFurnitures[houseid], furnitureid)) {
        if (!IsValidDynamicObject(FurnitureData[houseid][furnitureid][furnitureObject]))
            return 0;

        if (FurnitureData[houseid][furnitureid][furnitureUnused] == 1) {
            DestroyDynamicObject(FurnitureData[houseid][furnitureid][furnitureObject]);
            FurnitureData[houseid][furnitureid][furnitureObject] = INVALID_STREAMER_ID;
            
            return 1;
        }

		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[houseid][furnitureid][furnitureObject], E_STREAMER_X, FurnitureData[houseid][furnitureid][furniturePos][0]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[houseid][furnitureid][furnitureObject], E_STREAMER_Y,FurnitureData[houseid][furnitureid][furniturePos][1]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[houseid][furnitureid][furnitureObject], E_STREAMER_Z, FurnitureData[houseid][furnitureid][furniturePos][2]);

		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[houseid][furnitureid][furnitureObject], E_STREAMER_R_X, FurnitureData[houseid][furnitureid][furnitureRot][0]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[houseid][furnitureid][furnitureObject], E_STREAMER_R_Y, FurnitureData[houseid][furnitureid][furnitureRot][1]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, FurnitureData[houseid][furnitureid][furnitureObject], E_STREAMER_R_Z, FurnitureData[houseid][furnitureid][furnitureRot][2]);

		Streamer_SetIntData(STREAMER_TYPE_OBJECT, FurnitureData[houseid][furnitureid][furnitureObject], E_STREAMER_WORLD_ID, houseid);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, FurnitureData[houseid][furnitureid][furnitureObject], E_STREAMER_INTERIOR_ID, hData[houseid][hInt]);

        for(new i = 0; i != MAX_MATERIALS; i++) if(FurnitureData[houseid][furnitureid][furnitureMaterials][i] > 0) {
            SetDynamicObjectMaterial(FurnitureData[houseid][furnitureid][furnitureObject], i, 
                GetTModel(FurnitureData[houseid][furnitureid][furnitureMaterials][i]), 
                GetTXDName(FurnitureData[houseid][furnitureid][furnitureMaterials][i]), 
                GetTextureName(FurnitureData[houseid][furnitureid][furnitureMaterials][i]), 0
            );
        }

        return 1;
    }
    return 0;
}

Furniture_Save(furnitureid, houseid)
{
    static
        string[1024];

    format(string, sizeof(string), "UPDATE `furniture` SET `ID` = '%d', `furnitureModel` = '%d', `furnitureName` = '%s', `furnitureX` = '%.4f', `furnitureY` = '%.4f', `furnitureZ` = '%.4f', `furnitureRX` = '%.4f', `furnitureRY` = '%.4f', `furnitureRZ` = '%.4f', `furnitureUnused` = '%d', `furnitureMaterials` = '%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d' WHERE `furnitureID` = '%d'",
        hData[houseid][hID],
        FurnitureData[houseid][furnitureid][furnitureModel],
        FurnitureData[houseid][furnitureid][furnitureName],
        FurnitureData[houseid][furnitureid][furniturePos][0],
        FurnitureData[houseid][furnitureid][furniturePos][1],
        FurnitureData[houseid][furnitureid][furniturePos][2],
        FurnitureData[houseid][furnitureid][furnitureRot][0],
        FurnitureData[houseid][furnitureid][furnitureRot][1],
        FurnitureData[houseid][furnitureid][furnitureRot][2],
        FurnitureData[houseid][furnitureid][furnitureUnused],
        FurnitureData[houseid][furnitureid][furnitureMaterials][0],
        FurnitureData[houseid][furnitureid][furnitureMaterials][1],
        FurnitureData[houseid][furnitureid][furnitureMaterials][2],
        FurnitureData[houseid][furnitureid][furnitureMaterials][3],
        FurnitureData[houseid][furnitureid][furnitureMaterials][4],
        FurnitureData[houseid][furnitureid][furnitureMaterials][5],
        FurnitureData[houseid][furnitureid][furnitureMaterials][6],
        FurnitureData[houseid][furnitureid][furnitureMaterials][7],
        FurnitureData[houseid][furnitureid][furnitureMaterials][8],
        FurnitureData[houseid][furnitureid][furnitureMaterials][9],
        FurnitureData[houseid][furnitureid][furnitureMaterials][10],
        FurnitureData[houseid][furnitureid][furnitureMaterials][11],
        FurnitureData[houseid][furnitureid][furnitureMaterials][12],
        FurnitureData[houseid][furnitureid][furnitureMaterials][13],
        FurnitureData[houseid][furnitureid][furnitureMaterials][14],
        FurnitureData[houseid][furnitureid][furnitureMaterials][15],
        FurnitureData[houseid][furnitureid][furnitureID]
    );
    return mysql_tquery(g_SQL, string);
}

Furniture_Add(houseid, name[], modelid, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, unused = 1)
{
    static
        id = cellmin;

    if(!Iter_Contains(Houses, houseid))
        return 0;

    if((id = Iter_Free(HouseFurnitures[houseid])) != cellmin)
    {
        Iter_Add(HouseFurnitures[houseid], id);

        format(FurnitureData[houseid][id][furnitureName], 32, name);
        FurnitureData[houseid][id][furnitureModel] = modelid;
        FurnitureData[houseid][id][furniturePos][0] = x;
        FurnitureData[houseid][id][furniturePos][1] = y;
        FurnitureData[houseid][id][furniturePos][2] = z;
        FurnitureData[houseid][id][furnitureRot][0] = rx;
        FurnitureData[houseid][id][furnitureRot][1] = ry;
        FurnitureData[houseid][id][furnitureRot][2] = rz;
        FurnitureData[houseid][id][furnitureUnused] = unused;

        Furniture_Refresh(id, houseid);
        new string[212];
        format(string,sizeof(string),"INSERT INTO `furniture` (`ID`) VALUES('%d')", hData[houseid][hID]);
        mysql_tquery(g_SQL, string, "OnFurnitureCreated", "dd", id, houseid);

        return id;
    }
    return cellmin;
}

Furniture_Delete(furnitureid, houseid)
{
    if(Iter_Contains(HouseFurnitures[houseid], furnitureid))
    {
        new query[128];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `furniture` WHERE `furnitureID` = '%d'", FurnitureData[houseid][furnitureid][furnitureID]);
        mysql_tquery(g_SQL, query);
        if (IsValidDynamicObject(FurnitureData[houseid][furnitureid][furnitureObject])) {
            DestroyDynamicObject(FurnitureData[houseid][furnitureid][furnitureObject]);
            FurnitureData[houseid][furnitureid][furnitureObject] = INVALID_STREAMER_ID;
        }

        Iter_Remove(HouseFurnitures[houseid], furnitureid);

        new tmp_furniture[furnitureData];
        FurnitureData[houseid][furnitureid] = tmp_furniture;
    }
    return 1;
}

function OnFurnitureCreated(furnitureid, houseid)
{
    FurnitureData[houseid][furnitureid][furnitureID] = cache_insert_id();
    Furniture_Save(furnitureid, houseid);
    return 1;
}

House_IsBuilder(playerid) {
    foreach (new i : Houses) if (hData[i][houseBuilder] == pData[playerid][pID]) {
        return 1;
    }
    return 0;
}

Player_OwnsHouse(playerid, houseid)
{
	if(houseid == -1) return 0;
	if(!IsPlayerConnected(playerid)) return 0;
	if(!strcmp(hData[houseid][hOwner], pData[playerid][pName], true)) return 1;
	return 0;
}

HouseReset(houseid)
{
	format(hData[houseid][hOwner], MAX_PLAYER_NAME, "-");
	hData[houseid][hLocked] = 1;
    hData[houseid][hMoney] = 0;
    hData[houseid][hCrack] = 0;
    hData[houseid][hPot] = 0;
	hData[houseid][hCgun] = 0;
	hData[houseid][hWeapon] = 0;
	hData[houseid][hAmmo] = 0;
    hData[houseid][hTypeAmmo] = 0;
	hData[houseid][hLastVisited] = 0;
	hData[houseid][hGarage] = 0;
    hData[houseid][hExtposX] = 0;
    hData[houseid][hExtposY] = 0;
    hData[houseid][hExtposZ] = 0;
    hData[houseid][hExtposA] = 0;
    hData[houseid][hPrice] = 0;
    hData[houseid][hInt] = 0;
    hData[houseid][hIntposX] = 0;
    hData[houseid][hIntposY] = 0;
    hData[houseid][hIntposZ] = 0;
    hData[houseid][hIntposA] = 0;
    hData[houseid][hLabel] = Text3D: INVALID_3DTEXT_ID;
	House_Type(houseid);

	for (new i = 0; i < 10; i ++)
    {
        hData[houseid][hWeapon][i] = 0;

		hData[houseid][hAmmo][i] = 0;
        hData[houseid][hTypeAmmo][i] = 0;
    }
}

House_WeaponStorage(playerid, houseid)
{
    if(houseid == -1)
        return 0;

    static
        string[320];

    string[0] = 0;

    for (new i = 0; i < 5; i ++)
    {
        if(!hData[houseid][hWeapon][i])
            format(string, sizeof(string), "%sEmpty Slot\n", string);

        else
            format(string, sizeof(string), "%s%s (%s)\n", string, ReturnWeaponName(hData[houseid][hWeapon][i]), GetAmmoTypeHouse(houseid));
    }
    ShowPlayerDialog(playerid, HOUSE_WEAPONS, DIALOG_STYLE_LIST, "Weapon Storage", string, "Select", "Cancel");
    return 1;
}

GetAmmoTypeHouse(houseid) {
    new type[52];
    for (new i = 0; i < 5; i ++)
    {
        if(hData[houseid][hWeapon][i]) {
            if(hData[houseid][hTypeAmmo][i]) {
                format(type, sizeof(type), "Ammo: %d Surplus", hData[houseid][hAmmo][i]);
            }
            else {
                format(type, sizeof(type), "Ammo: %d", hData[houseid][hAmmo][i]);
            }
        }
    }
    return type;
}

House_OpenStorage(playerid, houseid)
{
    if(houseid == -1)
        return 0;

    new
        items[1],
        string[10 * 32];

    for (new i = 0; i < 5; i ++) if(hData[houseid][hWeapon][i])
	{
        items[0]++;
    }
    if(!Player_OwnsHouse(playerid, houseid))
        format(string, sizeof(string), "Weapon Storage (%d/5)", items[0]);

    else
        format(string, sizeof(string), "Weapon Storage (%d/5)\nMoney Safe (%s)\nCrack (%d)\nPot (%d)", items[0], FormatMoney(hData[houseid][hMoney]), hData[houseid][hCrack], hData[houseid][hPot]);

    ShowPlayerDialog(playerid, HOUSE_STORAGE, DIALOG_STYLE_LIST, "House Storage", string, "Select", "Cancel");
    return 1;
}

GetOwnedHouses(playerid)
{
	new tmpcount;
	foreach(new hid : Houses)
	{
	    if(!strcmp(hData[hid][hOwner], pData[playerid][pName], true))
	    {
     		tmpcount++;
		}
	}
	return tmpcount;
}

ReturnPlayerHousesID(playerid, hslot)
{
	new tmpcount;
	if(hslot < 1 && hslot > LIMIT_PER_PLAYER) return -1;
	foreach(new hid : Houses)
	{
	    if(!strcmp(pData[playerid][pName], hData[hid][hOwner], true))
	    {
     		tmpcount++;
       		if(tmpcount == hslot)
       		{
        		return hid;
  			}
	    }
	}
	return -1;
}

House_Save(houseid)
{
	new cQuery[3000];
	format(cQuery, sizeof(cQuery), "UPDATE houses SET owner='%s', address='%s', price='%d', type='%d', locked='%d', money='%d', crack='%d', pot='%d'",
	hData[houseid][hOwner],
	hData[houseid][hAddress],
	hData[houseid][hPrice],
	hData[houseid][hType],
	hData[houseid][hLocked],
	hData[houseid][hMoney],
    hData[houseid][hCrack],
    hData[houseid][hPot]
	);

	for (new i = 0; i < 10; i ++)
	{
        format(cQuery, sizeof(cQuery), "%s, houseWeapon%d='%d', houseAmmo%d='%d'", cQuery, i + 1, hData[houseid][hWeapon][i], i + 1, hData[houseid][hAmmo][i]);
    }
    format(cQuery, sizeof(cQuery), "%s, houseAmmoType='%d|%d|%d|%d|%d|%d|%d|%d|%d|%d'", cQuery, 
	hData[houseid][hTypeAmmo][0], hData[houseid][hTypeAmmo][1], hData[houseid][hTypeAmmo][2], hData[houseid][hTypeAmmo][3],
    hData[houseid][hTypeAmmo][4], hData[houseid][hTypeAmmo][5], hData[houseid][hTypeAmmo][6], hData[houseid][hTypeAmmo][7],
    hData[houseid][hTypeAmmo][8], hData[houseid][hTypeAmmo][9]);

	format(cQuery, sizeof(cQuery), "%s, houseint='%d', extvw='%d', extint='%d', extposx='%f', extposy='%f', extposz='%f', extposa='%f', intposx='%f', intposy='%f', intposz='%f', intposa='%f', visit='%d', garage='%d', garageposx='%f', garageposy='%f', garageposz='%f', houseBuilder = '%d', houseBuilderTime = '%d' WHERE ID='%d'",
        cQuery,
        hData[houseid][hInt],
		hData[houseid][hExtVw],
		hData[houseid][hExtInt],
        hData[houseid][hExtposX],
        hData[houseid][hExtposY],
		hData[houseid][hExtposZ],
		hData[houseid][hExtposA],
		hData[houseid][hIntposX],
		hData[houseid][hIntposY],
		hData[houseid][hIntposZ],
		hData[houseid][hIntposA],
		hData[houseid][hLastVisited],
		hData[houseid][hGarage],
        hData[houseid][hGarageposX],
        hData[houseid][hGarageposY],
		hData[houseid][hGarageposZ],
        hData[houseid][houseBuilder],
        hData[houseid][houseBuilderTime],
        houseid
    );
	return mysql_tquery(g_SQL, cQuery);
}

HouseStructure_Save(id, houseid) {
    if (Iter_Contains(HouseStruct[houseid], id)) {
        static
            query[600];

        format(query, sizeof(query), "UPDATE `housestruct` SET `HouseID`='%d', `Model`='%d', `PosX`='%.4f', `PosY`='%.4f', `PosZ`='%.4f', `RotX`='%.4f', `RotY`='%.4f', `RotZ`='%.4f', `Material`='%d', `Color`='%d', `Type`='%d' WHERE `ID`='%d'",
            hData[houseid][hID],
            HouseStructure[houseid][id][structureModel],
            HouseStructure[houseid][id][structurePos][0],
            HouseStructure[houseid][id][structurePos][1],
            HouseStructure[houseid][id][structurePos][2],
            HouseStructure[houseid][id][structureRot][0],
            HouseStructure[houseid][id][structureRot][1],
            HouseStructure[houseid][id][structureRot][2],
            HouseStructure[houseid][id][structureMaterial],
            HouseStructure[houseid][id][structureColor],
            HouseStructure[houseid][id][structureType],
            HouseStructure[houseid][id][structureID]
        );
        return mysql_tquery(g_SQL, query);
    }
    return 0;
}

House_Type(houseid)
{
	if(hData[houseid][hType] == 1)
	{
	    switch(random(3))
		{
			case 0:
			{
				hData[houseid][hIntposX] = 845.89;
				hData[houseid][hIntposY] = -2048.00;
				hData[houseid][hIntposZ] = 1476.91;
				hData[houseid][hIntposA] = 92.60;
				hData[houseid][hInt] = 1;
			}
			case 1:
			{
				hData[houseid][hIntposX] = 337.61;
				hData[houseid][hIntposY] = 1854.10;
				hData[houseid][hIntposZ] = 1002.08;
				hData[houseid][hIntposA] = 265.14;
				hData[houseid][hInt] = 1;
			}
			case 2:
			{
				hData[houseid][hIntposX] = 338.29;
				hData[houseid][hIntposY] = 1794.87;
				hData[houseid][hIntposZ] = 1002.17;
				hData[houseid][hIntposA] = 269.09;
				hData[houseid][hInt] = 1;
			}
		}
	}
	if(hData[houseid][hType] == 2)
	{
	    switch(random(3))
		{
			case 0:
			{
				hData[houseid][hIntposX] = 736.03;
				hData[houseid][hIntposY] = 1672.08;
				hData[houseid][hIntposZ] = 501.08;
				hData[houseid][hIntposA] = 356.23;
				hData[houseid][hInt] = 1;
			}
			case 1:
			{
				hData[houseid][hIntposX] = 338.78;
				hData[houseid][hIntposY] = 1734.95;
				hData[houseid][hIntposZ] = 1002.08;
				hData[houseid][hIntposA] = 268.46;
				hData[houseid][hInt] = 1;
			}
			case 2:
			{
				hData[houseid][hIntposX] = 351.59;
				hData[houseid][hIntposY] = 1669.31;
				hData[houseid][hIntposZ] = 1002.17;
				hData[houseid][hIntposA] = 176.03;
				hData[houseid][hInt] = 1;
			}
		}
	}
	if(hData[houseid][hType] == 3)
	{
	    switch(random(4))
		{
			case 0:
			{
				hData[houseid][hIntposX] = 1855.38;
				hData[houseid][hIntposY] = -1709.12;
				hData[houseid][hIntposZ] = 1720.06;
				hData[houseid][hIntposA] = 273.58;
				hData[houseid][hInt] = 1;
			}
			case 1:
			{
				hData[houseid][hIntposX] = 4577.82;
				hData[houseid][hIntposY] = -2527.82;
				hData[houseid][hIntposZ] = 5.28;
				hData[houseid][hIntposA] = 262.63;
				hData[houseid][hInt] = 1;
			}
			case 2:
			{
				hData[houseid][hIntposX] = 1263.68;
				hData[houseid][hIntposY] = -605.30;
				hData[houseid][hIntposZ] = 1001.08;
				hData[houseid][hIntposA] = 189.50;
				hData[houseid][hInt] = 1;
			}
			case 3:
			{
				hData[houseid][hIntposX] = 1224.34;
				hData[houseid][hIntposY] = -749.22;
				hData[houseid][hIntposZ] = 1085.72;
				hData[houseid][hIntposA] = 265.59;
				hData[houseid][hInt] = 1;
			}
		}
	}
}

House_Refresh(houseid)
{
    if(houseid != -1)
    {
        if(IsValidDynamic3DTextLabel(hData[houseid][hLabel])) DestroyDynamic3DTextLabel(hData[houseid][hLabel]);
        if(IsValidDynamicPickup(hData[houseid][hPickup][0])) DestroyDynamicPickup(hData[houseid][hPickup][0]);
		if(IsValidDynamicPickup(hData[houseid][hPickup][1])) DestroyDynamicPickup(hData[houseid][hPickup][1]);
		if(IsValidDynamicCP(hData[houseid][hCP][0])) DestroyDynamicCP(hData[houseid][hCP][0]);
		if(IsValidDynamicCP(hData[houseid][hCP][1])) DestroyDynamicCP(hData[houseid][hCP][1]);
        if(IsValidDynamic3DTextLabel(hData[houseid][hGarageLabel])) DestroyDynamic3DTextLabel(hData[houseid][hGarageLabel]);
        if(IsValidDynamicPickup(hData[houseid][hGaragePickup])) DestroyDynamicPickup(hData[houseid][hGaragePickup]);
		if(IsValidDynamicCP(hData[houseid][hGarageCP])) DestroyDynamicCP(hData[houseid][hGarageCP]);

        static
        string[255];
		
		new type[128];
		if(hData[houseid][hType] == 1)
		{
			type= "Small";
		}
		else if(hData[houseid][hType] == 2)
		{
			type= "Medium";
		}
		else if(hData[houseid][hType] == 3)
		{
			type= "Large";
		}
		else
		{
			type= "Unknow";
		}

        if(strcmp(hData[houseid][hOwner], "-")) format(string, sizeof(string), ""AQUA_E"[H:%d]\n"YELLOW_E"Owner: {FFFFFF}%s\n"GREY_E"%s", houseid, hData[houseid][hOwner], hData[houseid][hAddress]);
        else  format(string, sizeof(string), "{00FFFF}[H:%d]\n{00FF00}This house for sell\n{FFFFFF}Addres: {FFFF00}%s\n{FFFFFF}House Price: {FFFF00}$%s\n"WHITE_E"Type /buy to purchase", houseid, hData[houseid][hAddress], FormatMoney(hData[houseid][hPrice]));
        
        hData[houseid][hPickup][0] = CreateDynamicPickup(19132, 23, hData[houseid][hExtposX], hData[houseid][hExtposY], hData[houseid][hExtposZ]+0.2, 0, 0, _, 5);
        hData[houseid][hPickup][1] = CreateDynamicPickup(19132, 23, hData[houseid][hIntposX], hData[houseid][hIntposY], hData[houseid][hIntposZ]+0.2, houseid, hData[houseid][hInt], _, 5);
        hData[houseid][hLabel] = CreateDynamic3DTextLabel(string, COLOR_GREEN, hData[houseid][hExtposX], hData[houseid][hExtposY], hData[houseid][hExtposZ]+0.5, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0);
		hData[houseid][hCP][0] = CreateDynamicCP(hData[houseid][hExtposX], hData[houseid][hExtposY], hData[houseid][hExtposZ], 2, 0, 0, _, 3);
        hData[houseid][hCP][1] = CreateDynamicCP(hData[houseid][hIntposX], hData[houseid][hIntposY], hData[houseid][hIntposZ], 1, houseid, hData[houseid][hInt], _, 3);
        
        if(hData[houseid][hGarage] > 0) {
			new str[212];
			format(str, sizeof(str), "{00FFFF}[HG:%d]\n"GREEN_E"House Garage\n"WHITE_E"Use '/storeveh' to store vehicle\nUse '/takeveh' to take vehicle\nUse '/switchveh' to switch vehicle", houseid);
			hData[houseid][hGarageLabel] = CreateDynamic3DTextLabel(str, COLOR_GREEN, hData[houseid][hGarageposX], hData[houseid][hGarageposY], hData[houseid][hGarageposZ]+0.5, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0);
			hData[houseid][hGaragePickup] = CreateDynamicPickup(1239, 23, hData[houseid][hGarageposX], hData[houseid][hGarageposY], hData[houseid][hGarageposZ], -1, -1);
		}
		hData[houseid][house_Lights] = false;
    }
    return 1;
}

HouseStructure_Refresh(id, houseid) {
    if (Iter_Contains(HouseStruct[houseid], id)) {
        if (!IsValidDynamicObject(HouseStructure[houseid][id][structureObject])) {
            HouseStructure[houseid][id][structureObject] = CreateDynamicObject(HouseStructure[houseid][id][structureModel], HouseStructure[houseid][id][structurePos][0], HouseStructure[houseid][id][structurePos][1], HouseStructure[houseid][id][structurePos][2], HouseStructure[houseid][id][structureRot][0], HouseStructure[houseid][id][structureRot][1], HouseStructure[houseid][id][structureRot][2], houseid, hData[houseid][hInt]);
        }
        HouseStructure_ObjectUpdate(id, houseid);

        foreach (new i : Player) if (IsPlayerInRangeOfPoint(i, 5.0, HouseStructure[houseid][id][structurePos][0], HouseStructure[houseid][id][structurePos][1], HouseStructure[houseid][id][structurePos][2])) {
            Streamer_Update(i);
        }
    }
    return 1;
}

HouseStructure_ObjectUpdate(id, houseid) {
    if (Iter_Contains(HouseStruct[houseid], id)) {
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, HouseStructure[houseid][id][structureObject], E_STREAMER_X, HouseStructure[houseid][id][structurePos][0]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, HouseStructure[houseid][id][structureObject], E_STREAMER_Y, HouseStructure[houseid][id][structurePos][1]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, HouseStructure[houseid][id][structureObject], E_STREAMER_Z, HouseStructure[houseid][id][structurePos][2]);

		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, HouseStructure[houseid][id][structureObject], E_STREAMER_R_X, HouseStructure[houseid][id][structureRot][0]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, HouseStructure[houseid][id][structureObject], E_STREAMER_R_Y, HouseStructure[houseid][id][structureRot][1]);
		Streamer_SetFloatData(STREAMER_TYPE_OBJECT, HouseStructure[houseid][id][structureObject], E_STREAMER_R_Z, HouseStructure[houseid][id][structureRot][2]);

		Streamer_SetIntData(STREAMER_TYPE_OBJECT, HouseStructure[houseid][id][structureObject], E_STREAMER_WORLD_ID, houseid);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, HouseStructure[houseid][id][structureObject], E_STREAMER_INTERIOR_ID, hData[houseid][hInt]);
        
        if (HouseStructure[houseid][id][structureMaterial] > 0) {
            if (HouseStructure[houseid][id][structureModel] == 1502 || HouseStructure[houseid][id][structureModel] == 14414) SetDynamicObjectMaterial(HouseStructure[houseid][id][structureObject], 1, GetTModel(HouseStructure[houseid][id][structureMaterial]), GetTXDName(HouseStructure[houseid][id][structureMaterial]), GetTextureName(HouseStructure[houseid][id][structureMaterial]), HouseStructure[houseid][id][structureColor]);
            else SetDynamicObjectMaterial(HouseStructure[houseid][id][structureObject], 0, GetTModel(HouseStructure[houseid][id][structureMaterial]), GetTXDName(HouseStructure[houseid][id][structureMaterial]), GetTextureName(HouseStructure[houseid][id][structureMaterial]), HouseStructure[houseid][id][structureColor]);
        }
		return 1;
    }
    return 0;
}

CreateHouseInterior(houseid) {
    for (new i = 0; i < sizeof(g_aHouseInteriors); i ++) if (g_aHouseInteriors[i][e_Type] == hData[houseid][hType]) {
        HouseStructure_Add(houseid, g_aHouseInteriors[i][e_ObjModel], g_aHouseInteriors[i][e_ObjPosX], g_aHouseInteriors[i][e_ObjPosY], g_aHouseInteriors[i][e_ObjPosZ], g_aHouseInteriors[i][e_ObjRotX], g_aHouseInteriors[i][e_ObjRotY], g_aHouseInteriors[i][e_ObjRotZ], 1);
    }
    return 1;
}

HouseStructure_CopyObject(id, houseid) {
    new current = HouseStructure[houseid][id][structureObject],
        model,
        Float:curPos[3],
        Float:curRot[3],
        matModel,
        txdName[32],
        textureName[32],
        matColor,
        textureID = 0;

    model = Streamer_GetIntData(STREAMER_TYPE_OBJECT, current, E_STREAMER_MODEL_ID);
    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, current, E_STREAMER_X, curPos[0]);
    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, current, E_STREAMER_Y, curPos[1]);
    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, current, E_STREAMER_Z, curPos[2]);
    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, current, E_STREAMER_R_X, curRot[0]);
    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, current, E_STREAMER_R_Y, curRot[1]);
    Streamer_GetFloatData(STREAMER_TYPE_OBJECT, current, E_STREAMER_R_Z, curRot[2]);

    if (HouseStructure[houseid][id][structureMaterial] > 0) {
        GetDynamicObjectMaterial(current, 0, matModel, txdName, textureName, matColor);
        textureID = HouseStructure[houseid][id][structureMaterial];
    }

    new copyId = HouseStructure_Add(houseid, model, curPos[0], curPos[1], curPos[2], curRot[0], curRot[1], curRot[2]);

    if (copyId == cellmin)
        return cellmin;

    if (textureID != 0) SetDynamicObjectMaterial(HouseStructure[houseid][copyId][structureObject], 0, matModel, txdName, textureName, matColor), HouseStructure[houseid][copyId][structureMaterial] = textureID, HouseStructure_Save(copyId, houseid);

    return copyId;
}

HouseStructure_GetCount(houseid) {
    new count;

    foreach (new i : HouseStruct[houseid]) if (HouseStructure[houseid][i][structureType] == 0) count++;

    return count;
}

function OnLoadHouseStructure(houseid) {
    new rows = cache_num_rows(),
        id = cellmin;

    Iter_Init(HouseStruct);
    if (rows) {
        for (new i = 0; i < rows; i ++) if ((id = Iter_Free(HouseStruct[houseid])) != cellmin) {
            Iter_Add(HouseStruct[houseid], id);

            cache_get_value_int(i, "ID", HouseStructure[houseid][id][structureID]);
            cache_get_value_int(i, "Model", HouseStructure[houseid][id][structureModel]);
            cache_get_value_float(i, "PosX", HouseStructure[houseid][id][structurePos][0]);
            cache_get_value_float(i, "PosY", HouseStructure[houseid][id][structurePos][1]);
            cache_get_value_float(i, "PosZ", HouseStructure[houseid][id][structurePos][2]);
            cache_get_value_float(i, "RotX", HouseStructure[houseid][id][structureRot][0]);
            cache_get_value_float(i, "RotY", HouseStructure[houseid][id][structureRot][1]);
            cache_get_value_float(i, "RotZ", HouseStructure[houseid][id][structureRot][2]);
            cache_get_value_int(i, "Material", HouseStructure[houseid][id][structureMaterial]);
            cache_get_value_int(i, "Color", HouseStructure[houseid][id][structureColor]);
            cache_get_value_int(i, "Type", HouseStructure[houseid][id][structureType]);

            HouseStructure_Refresh(id, houseid);
        }
    }
    return 1;
}

function OnLoadFurniture(houseid)
{
    new
        rows = cache_num_rows(),
        id = cellmin,
        str[32];

    Iter_Init(HouseFurnitures);
    if (rows) {
        for (new i = 0; i != rows; i ++) if((id = Iter_Free(HouseFurnitures[houseid])) != cellmin) {
            Iter_Add(HouseFurnitures[houseid], id);

            cache_get_value(i, "furnitureName", FurnitureData[houseid][id][furnitureName], 32);
            cache_get_value_int(i, "furnitureID", FurnitureData[houseid][id][furnitureID]);
            cache_get_value_int(i, "furnitureModel", FurnitureData[houseid][id][furnitureModel]);
            cache_get_value_int(i, "furnitureUnused", FurnitureData[houseid][id][furnitureUnused]);
            cache_get_value_float(i, "furnitureX", FurnitureData[houseid][id][furniturePos][0]);
            cache_get_value_float(i, "furnitureY", FurnitureData[houseid][id][furniturePos][1]);
            cache_get_value_float(i, "furnitureZ", FurnitureData[houseid][id][furniturePos][2]);
            cache_get_value_float(i, "furnitureRX", FurnitureData[houseid][id][furnitureRot][0]);
            cache_get_value_float(i, "furnitureRY", FurnitureData[houseid][id][furnitureRot][1]);
            cache_get_value_float(i, "furnitureRZ", FurnitureData[houseid][id][furnitureRot][2]);

            cache_get_value(i, "furnitureMaterials", str, 32);
            sscanf(str, "p<|>dddddddddddddddd", 
                FurnitureData[houseid][id][furnitureMaterials][0],
                FurnitureData[houseid][id][furnitureMaterials][1],
                FurnitureData[houseid][id][furnitureMaterials][2],
                FurnitureData[houseid][id][furnitureMaterials][3],
                FurnitureData[houseid][id][furnitureMaterials][4],
                FurnitureData[houseid][id][furnitureMaterials][5],
                FurnitureData[houseid][id][furnitureMaterials][6],
                FurnitureData[houseid][id][furnitureMaterials][7],
                FurnitureData[houseid][id][furnitureMaterials][8],
                FurnitureData[houseid][id][furnitureMaterials][9],
                FurnitureData[houseid][id][furnitureMaterials][10],
                FurnitureData[houseid][id][furnitureMaterials][11],
                FurnitureData[houseid][id][furnitureMaterials][12],
                FurnitureData[houseid][id][furnitureMaterials][13],
                FurnitureData[houseid][id][furnitureMaterials][14],
                FurnitureData[houseid][id][furnitureMaterials][15]
            );

            Furniture_Refresh(id, houseid);
        }
    }
    return 1;
}

function LoadHouses()
{
    static
        str[128],
		hid;

	new rows = cache_num_rows(), owner[128], address[128];
 	if(rows)
  	{
		for(new i; i < rows; i++)
		{
			cache_get_value_name_int(i, "ID", hid);
			cache_get_value_name(i, "owner", owner);
			format(hData[hid][hOwner], 128, owner);
			cache_get_value_name(i, "address", address);
			format(hData[hid][hAddress], 128, address);
			cache_get_value_name_int(i, "price", hData[hid][hPrice]);
			cache_get_value_name_int(i, "type", hData[hid][hType]);
			cache_get_value_name_float(i, "extposx", hData[hid][hExtposX]);
			cache_get_value_name_float(i, "extposy", hData[hid][hExtposY]);
			cache_get_value_name_float(i, "extposz", hData[hid][hExtposZ]);
			cache_get_value_name_float(i, "extposa", hData[hid][hExtposA]);
			cache_get_value_name_float(i, "intposx", hData[hid][hIntposX]);
			cache_get_value_name_float(i, "intposy", hData[hid][hIntposY]);
			cache_get_value_name_float(i, "intposz", hData[hid][hIntposZ]);
			cache_get_value_name_float(i, "intposa", hData[hid][hIntposA]);
			cache_get_value_name_int(i, "houseint", hData[hid][hInt]);
			cache_get_value_name_int(i, "extvw", hData[hid][hExtVw]);
			cache_get_value_name_int(i, "extint", hData[hid][hExtInt]);
			cache_get_value_name_int(i, "money", hData[hid][hMoney]);
            cache_get_value_name_int(i, "crack", hData[hid][hCrack]);
            cache_get_value_name_int(i, "pot", hData[hid][hPot]);
			cache_get_value_name_int(i, "locked", hData[hid][hLocked]);
			cache_get_value_name_int(i, "visit", hData[hid][hLastVisited]);
			cache_get_value_name_int(i, "garage", hData[hid][hGarage]);
			cache_get_value_name_float(i, "garageposx", hData[hid][hGarageposX]);
			cache_get_value_name_float(i, "garageposy", hData[hid][hGarageposY]);
			cache_get_value_name_float(i, "garageposz", hData[hid][hGarageposZ]);
			cache_get_value_name_int(i, "houseBuilder", hData[hid][houseBuilder]);
			cache_get_value_name_int(i, "houseBuilderTime", hData[hid][houseBuilderTime]);

			hData[hid][hID] = hid;

			format(str, sizeof(str), "SELECT * FROM `housestruct` WHERE `HouseID` = '%d'", hData[hid][hID]);
            mysql_tquery(g_SQL, str, "OnLoadHouseStructure", "d", hid);

			format(str, sizeof(str), "SELECT * FROM `furniture` WHERE `ID` = '%d'", hData[hid][hID]);
            mysql_tquery(g_SQL, str, "OnLoadFurniture", "d", hid);

			for (new j = 0; j < 10; j ++)
			{
				format(str, 24, "houseWeapon%d", j + 1);
				cache_get_value_name_int(i, str, hData[hid][hWeapon][j]);

				format(str, 24, "houseAmmo%d", j + 1);
				cache_get_value_name_int(i, str, hData[hid][hAmmo][j]);
			}
            new ammo[52];
            cache_get_value_name(i, "houseAmmoType", ammo);
            sscanf(ammo, "p<|>dddddddddd", hData[hid][hTypeAmmo][0], hData[hid][hTypeAmmo][1],
            hData[hid][hTypeAmmo][2], hData[hid][hTypeAmmo][3], hData[hid][hTypeAmmo][4], hData[hid][hTypeAmmo][5],
            hData[hid][hTypeAmmo][6], hData[hid][hTypeAmmo][7], hData[hid][hTypeAmmo][8], hData[hid][hTypeAmmo][9]);
            
            hData[hid][housePacket] = 0;
			House_Refresh(hid);
			Iter_Add(Houses, hid);
		}
		printf("*** [Database: Loaded] house data (%d count).", rows);
	}
}

HouseStructure_Add(houseid, modelid, Float:x, Float:y, Float:z, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, type = 0) {
    static
        id = cellmin;

    if(!Iter_Contains(Houses, houseid))
        return 0;

    if ((id = Iter_Free(HouseStruct[houseid])) != cellmin) {
        Iter_Add(HouseStruct[houseid], id);
        
        HouseStructure[houseid][id][structureModel] = modelid;
        HouseStructure[houseid][id][structurePos][0] = x;
        HouseStructure[houseid][id][structurePos][1] = y;
        HouseStructure[houseid][id][structurePos][2] = z;
        HouseStructure[houseid][id][structureRot][0] = rx;
        HouseStructure[houseid][id][structureRot][1] = ry;
        HouseStructure[houseid][id][structureRot][2] = rz;
        HouseStructure[houseid][id][structureMaterial] = 0;
        HouseStructure[houseid][id][structureColor] = 0;
        HouseStructure[houseid][id][structureType] = type;

        HouseStructure_Refresh(id, houseid);
        new query[128];
        mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `housestruct` (`HouseID`) VALUES ('%d')", houseid);
        mysql_tquery(g_SQL, query, "OnHouseStructureCreated", "dd", id, houseid);
        return id;
    }

    return cellmin;
}

HouseStructure_DeleteAll(houseid) {
    if (Iter_Contains(Houses, houseid)) {
        foreach (new id : HouseStruct[houseid]) if (HouseStructure[houseid][id][structureType] == 0) {
            new query[128];
            mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `housestruct` WHERE `ID`='%d'", HouseStructure[houseid][id][structureID]);
            mysql_tquery(g_SQL, query);
            if (IsValidDynamicObject(HouseStructure[houseid][id][structureObject])) {
                DestroyDynamicObject(HouseStructure[houseid][id][structureObject]);
                HouseStructure[houseid][id][structureObject] = INVALID_STREAMER_ID;
            }

            new tmp_houseStructure[houseStructure];
            HouseStructure[houseid][id] = tmp_houseStructure;

            new current = id;
            Iter_SafeRemove(HouseStruct[houseid], current, id);
        }
    }
    return 1;
}

HouseStructure_Delete(id, houseid) {
    if (Iter_Contains(HouseStruct[houseid], id)) {
        new query[128];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `housestruct` WHERE `ID`='%d'", HouseStructure[houseid][id][structureID]);
        mysql_tquery(g_SQL, query);
        if (IsValidDynamicObject(HouseStructure[houseid][id][structureObject])) {
            DestroyDynamicObject(HouseStructure[houseid][id][structureObject]);
            HouseStructure[houseid][id][structureObject] = INVALID_STREAMER_ID;
        }

        Iter_Remove(HouseStruct[houseid], id);

        new tmp_houseStructure[houseStructure];
        HouseStructure[houseid][id] = tmp_houseStructure;
    }
    return 1;
}

function OnHouseStructureCreated(id, houseid) {
    HouseStructure[houseid][id][structureID] = cache_insert_id();
    HouseStructure_Save(id, houseid);
    return 1;
}

House_Nearest(playerid)
{
    foreach (new i : Houses) if(IsPlayerInRangeOfPoint(playerid, 2.5, hData[i][hExtposX], hData[i][hExtposY], hData[i][hExtposZ]))
    {
        if(GetPlayerInterior(playerid) == hData[i][hExtInt] && GetPlayerVirtualWorld(playerid) == hData[i][hExtVw])
        return i;
    }
    return -1;
}

House_Inside(playerid)
{
    if(pData[playerid][pInHouse] != -1)
    {
        foreach (new i : Houses) if(hData[i][hID] == pData[playerid][pInHouse] && GetPlayerInterior(playerid) == hData[i][hInt] && GetPlayerVirtualWorld(playerid) > 0) {
            return i;
        }
    }
    return -1;
}