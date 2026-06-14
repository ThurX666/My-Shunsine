
Family_Save(id)
{
	new dquery[2048];
	format(dquery, sizeof(dquery), "UPDATE familys SET name='%s', leader='%s', motd='%s', extposx='%f', extposy='%f', extposz='%f', extposa='%f', intposx='%f', intposy='%f', intposz='%f', intposa='%f', fint='%d'",
	fData[id][fName],
	fData[id][fLeader],
	fData[id][fMotd],
	fData[id][fExtposX],
	fData[id][fExtposY],
	fData[id][fExtposZ],
	fData[id][fExtposA],
	fData[id][fIntposX],
	fData[id][fIntposY],
	fData[id][fIntposZ],
	fData[id][fIntposA],
	fData[id][fInt]);
	
	for (new i = 0; i < 10; i ++) 
	{
        format(dquery, sizeof(dquery), "%s, Weapon%d='%d', Ammo%d='%d', TypeAmmo%d='%d'", dquery, i + 1, fData[id][fGun][i], i + 1, fData[id][fAmmo][i], i + 1, fData[id][fTypeAmmo][i]);
    }

	format(dquery, sizeof(dquery), "%s, vehiclemodel='%d|%d|%d|%d|%d', vehiclefuel='%d|%d|%d|%d|%d', vehiclehealth='%f|%f|%f|%f|%f', vehiclepos1='%.2f|%.2f|%.2f|%.2f', vehiclepos2='%.2f|%.2f|%.2f|%.2f', vehiclepos3='%.2f|%.2f|%.2f|%.2f', vehiclepos4='%.2f|%.2f|%.2f|%.2f', vehiclepos5='%.2f|%.2f|%.2f|%.2f'",
	dquery,
	fData[id][fVehicleModel][0],
	fData[id][fVehicleModel][1],
	fData[id][fVehicleModel][2],
	fData[id][fVehicleModel][3],
	fData[id][fVehicleModel][4],
	fData[id][fVehicleFuel][0],
	fData[id][fVehicleFuel][1],
	fData[id][fVehicleFuel][2],
	fData[id][fVehicleFuel][3],
	fData[id][fVehicleFuel][4],
	fData[id][fVehicleHealth][0],
	fData[id][fVehicleHealth][1],
	fData[id][fVehicleHealth][2],
	fData[id][fVehicleHealth][3],
	fData[id][fVehicleHealth][4],
	fData[id][fVehiclePos][0],
	fData[id][fVehiclePos][1],
	fData[id][fVehiclePos][2],
	fData[id][fVehiclePos][3],
	fData[id][fVehiclePos1][0],
	fData[id][fVehiclePos1][1],
	fData[id][fVehiclePos1][2],
	fData[id][fVehiclePos1][3],
	fData[id][fVehiclePos2][0],
	fData[id][fVehiclePos2][1],
	fData[id][fVehiclePos2][2],
	fData[id][fVehiclePos2][3],
	fData[id][fVehiclePos3][0],
	fData[id][fVehiclePos3][1],
	fData[id][fVehiclePos3][2],
	fData[id][fVehiclePos3][3],
	fData[id][fVehiclePos4][0],
	fData[id][fVehiclePos4][1],
	fData[id][fVehiclePos4][2],
	fData[id][fVehiclePos4][3]);

	format(dquery, sizeof(dquery), "%s, safex='%f', safey='%f', safez='%f', money='%d', marijuana='%d', component='%d', material='%d' WHERE ID='%d'",
	dquery,
	fData[id][fSafeposX],
	fData[id][fSafeposY],
	fData[id][fSafeposZ],
	fData[id][fMoney],
	fData[id][fMarijuana],
	fData[id][fComponent],
	fData[id][fMaterial],
	id);
	return mysql_tquery(g_SQL, dquery);
}


Family_Refresh(id)
{
	if(id != -1)
	{
		if(IsValidDynamic3DTextLabel(fData[id][fLabelext]))
            DestroyDynamic3DTextLabel(fData[id][fLabelext]);

        if(IsValidDynamicPickup(fData[id][fPickext]))
            DestroyDynamicPickup(fData[id][fPickext]);

        if(IsValidDynamic3DTextLabel(fData[id][fLabelint]))
            DestroyDynamic3DTextLabel(fData[id][fLabelint]);

        if(IsValidDynamicPickup(fData[id][fPickint]))
            DestroyDynamicPickup(fData[id][fPickint]);
			
		if(IsValidDynamic3DTextLabel(fData[id][fLabelsafe]))
            DestroyDynamic3DTextLabel(fData[id][fLabelsafe]);

        if(IsValidDynamicPickup(fData[id][fPicksafe]))
            DestroyDynamicPickup(fData[id][fPicksafe]);
		
		new mstr[512];
		format(mstr,sizeof(mstr),"[Family ID: %d]\n{FFFFFF}%s\n{FFFFFF}Press {FF0000}ENTER {FFFFFF}to enter", id, fData[id][fName]);
		fData[id][fPickext] = CreateDynamicPickup(19130, 23, fData[id][fExtposX], fData[id][fExtposY], fData[id][fExtposZ], 0, 0);
		fData[id][fLabelext] = CreateDynamic3DTextLabel(mstr, COLOR_YELLOW, fData[id][fExtposX], fData[id][fExtposY], fData[id][fExtposZ]+0.35, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0);

        if(fData[id][fIntposX] != 0.0 && fData[id][fIntposY] != 0.0 && fData[id][fIntposZ] != 0.0)
        {
            format(mstr,sizeof(mstr),"[Family ID: %d]\n{FFFFFF}%s\n{FFFFFF}Press {FF0000}ENTER {FFFFFF}to exit", id, fData[id][fName]);

            fData[id][fLabelint] = CreateDynamic3DTextLabel(mstr, COLOR_YELLOW, fData[id][fIntposX], fData[id][fIntposY], fData[id][fIntposZ]+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, id, fData[id][fInt]);
            fData[id][fPickint] = CreateDynamicPickup(19130, 23, fData[id][fIntposX], fData[id][fIntposY], fData[id][fIntposZ], id, fData[id][fInt], -1, 7);
        }
		// if(fData[id][fSafeposX] != 0.0 && fData[id][fSafeposY] != 0.0 && fData[id][fSafeposZ] != 0.0)
		// {
		// 	format(tstr, sizeof(tstr), "[Family ID: %d]\nSafe Point", id);
		// 	fData[id][fLabelsafe] = CreateDynamic3DTextLabel(tstr, COLOR_YELLOW, fData[id][fSafeposX], fData[id][fSafeposY], fData[id][fSafeposZ]+0.7, 5.0);
        //     fData[id][fPicksafe] = CreateDynamicPickup(1239, 23, fData[id][fSafeposX], fData[id][fSafeposY], fData[id][fSafeposZ], id, fData[id][fInt], -1, 7);
		// }

		if(IsValidVehicle(fData[id][fVehicle][0])) DestroyVehicle(fData[id][fVehicle][0]);
		if(IsValidVehicle(fData[id][fVehicle][1])) DestroyVehicle(fData[id][fVehicle][1]);
		if(IsValidVehicle(fData[id][fVehicle][2])) DestroyVehicle(fData[id][fVehicle][2]);
		if(IsValidVehicle(fData[id][fVehicle][3])) DestroyVehicle(fData[id][fVehicle][3]);
		if(IsValidVehicle(fData[id][fVehicle][4])) DestroyVehicle(fData[id][fVehicle][4]);
		if(fData[id][fVehicleModel][0] != 0)
		{
			fData[id][fVehicle][0] = CreateVehicle(fData[id][fVehicleModel][0], fData[id][fVehiclePos][0], fData[id][fVehiclePos][1], fData[id][fVehiclePos][2], fData[id][fVehiclePos][3], -1, -1, VEHICLE_RESPAWN);
			CoreVehicles[fData[id][fVehicle][0]][vehFamily] = id;
			new str[52];
			format(str, sizeof(str), ""GREEN_E"%s", fName);
			SetVehicleNumberPlate(fData[id][fVehicle][0], str);
			SetVehicleHealth(fData[id][fVehicle][0], fData[id][fVehicleHealth][0]);
		}
		if(fData[id][fVehicleModel][1] != 0)
		{
			fData[id][fVehicle][1] = CreateVehicle(fData[id][fVehicleModel][1], fData[id][fVehiclePos1][0], fData[id][fVehiclePos1][1], fData[id][fVehiclePos1][2], fData[id][fVehiclePos1][3], -1, -1, VEHICLE_RESPAWN);
			CoreVehicles[fData[id][fVehicle][1]][vehFamily] = id;
			new str[52];
			format(str, sizeof(str), ""GREEN_E"%s", fName);
			SetVehicleNumberPlate(fData[id][fVehicle][1], str);
			SetVehicleHealth(fData[id][fVehicle][1], fData[id][fVehicleHealth][1]);
		}
		if(fData[id][fVehicleModel][2] != 0)
		{
			fData[id][fVehicle][0] = CreateVehicle(fData[id][fVehicleModel][2], fData[id][fVehiclePos2][0], fData[id][fVehiclePos2][1], fData[id][fVehiclePos2][2], fData[id][fVehiclePos2][3], -1, -1, VEHICLE_RESPAWN);
			CoreVehicles[fData[id][fVehicle][0]][vehFamily] = id;
			new str[52];
			format(str, sizeof(str), ""GREEN_E"%s", fName);
			SetVehicleNumberPlate(fData[id][fVehicle][0], str);
			SetVehicleHealth(fData[id][fVehicle][2], fData[id][fVehicleHealth][2]);
		}
		if(fData[id][fVehicleModel][3] != 0)
		{
			fData[id][fVehicle][1] = CreateVehicle(fData[id][fVehicleModel][3], fData[id][fVehiclePos3][0], fData[id][fVehiclePos3][1], fData[id][fVehiclePos3][2], fData[id][fVehiclePos3][3], -1, -1, VEHICLE_RESPAWN);
			CoreVehicles[fData[id][fVehicle][1]][vehFamily] = id;
			new str[52];
			format(str, sizeof(str), ""GREEN_E"%s", fName);
			SetVehicleNumberPlate(fData[id][fVehicle][1], str);
			SetVehicleHealth(fData[id][fVehicle][3], fData[id][fVehicleHealth][3]);
		}
		if(fData[id][fVehicleModel][4] != 0)
		{
			fData[id][fVehicle][0] = CreateVehicle(fData[id][fVehicleModel][4], fData[id][fVehiclePos4][0], fData[id][fVehiclePos4][1], fData[id][fVehiclePos4][2], fData[id][fVehiclePos4][3], -1, -1, VEHICLE_RESPAWN);
			CoreVehicles[fData[id][fVehicle][0]][vehFamily] = id;
			new str[52];
			format(str, sizeof(str), ""GREEN_E"%s", fName);
			SetVehicleNumberPlate(fData[id][fVehicle][0], str);
			SetVehicleHealth(fData[id][fVehicle][4], fData[id][fVehicleHealth][4]);
		}
	}
}

function OnFamilyCreated(id)
{
	Family_Save(id);
	Family_Refresh(id);
	return 1;
}

function LoadFamilys()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new fid, name[50], leader[MAX_PLAYER_NAME], motd[100], str[128];
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", fid);
	    	cache_get_value_name(i, "name", name);
			format(fData[fid][fName], 50, name);
		    cache_get_value_name(i, "leader", leader);
			format(fData[fid][fLeader], MAX_PLAYER_NAME, leader);
			cache_get_value_name(i, "motd", motd);
			format(fData[fid][fMotd], 100, motd);
		    cache_get_value_name_float(i, "extposx", fData[fid][fExtposX]);
		    cache_get_value_name_float(i, "extposy", fData[fid][fExtposY]);
		    cache_get_value_name_float(i, "extposz", fData[fid][fExtposZ]);
		    cache_get_value_name_float(i, "extposa", fData[fid][fExtposA]);
		    cache_get_value_name_float(i, "intposx", fData[fid][fIntposX]);
		    cache_get_value_name_float(i, "intposy", fData[fid][fIntposY]);
		    cache_get_value_name_float(i, "intposz", fData[fid][fIntposZ]);
		    cache_get_value_name_float(i, "intposa", fData[fid][fIntposA]);
		    cache_get_value_name_int(i, "fint", fData[fid][fInt]);
			cache_get_value_name_float(i, "safex", fData[fid][fSafeposX]);
			cache_get_value_name_float(i, "safey", fData[fid][fSafeposY]);
			cache_get_value_name_float(i, "safez", fData[fid][fSafeposZ]);
			cache_get_value_name_int(i, "money", fData[fid][fMoney]);
			cache_get_value_name_int(i, "marijuana", fData[fid][fMarijuana]);
			cache_get_value_name_int(i, "component", fData[fid][fComponent]);
			cache_get_value_name_int(i, "material", fData[fid][fMaterial]);
			
			cache_get_value_name_int(i, "Weapon1", fData[fid][fGun][0]);
			cache_get_value_name_int(i, "Weapon2", fData[fid][fGun][1]);
			cache_get_value_name_int(i, "Weapon3", fData[fid][fGun][2]);
			cache_get_value_name_int(i, "Weapon4", fData[fid][fGun][3]);
			cache_get_value_name_int(i, "Weapon5", fData[fid][fGun][4]);
			cache_get_value_name_int(i, "Weapon6", fData[fid][fGun][5]);
			cache_get_value_name_int(i, "Weapon7", fData[fid][fGun][6]);
			cache_get_value_name_int(i, "Weapon8", fData[fid][fGun][7]);
			cache_get_value_name_int(i, "Weapon9", fData[fid][fGun][8]);
			cache_get_value_name_int(i, "Weapon10", fData[fid][fGun][9]);
			
			cache_get_value_name_int(i, "Ammo1", fData[fid][fAmmo][0]);
			cache_get_value_name_int(i, "Ammo2", fData[fid][fAmmo][1]);
			cache_get_value_name_int(i, "Ammo3", fData[fid][fAmmo][2]);
			cache_get_value_name_int(i, "Ammo4", fData[fid][fAmmo][3]);
			cache_get_value_name_int(i, "Ammo5", fData[fid][fAmmo][4]);
			cache_get_value_name_int(i, "Ammo6", fData[fid][fAmmo][5]);
			cache_get_value_name_int(i, "Ammo7", fData[fid][fAmmo][6]);
			cache_get_value_name_int(i, "Ammo8", fData[fid][fAmmo][7]);
			cache_get_value_name_int(i, "Ammo9", fData[fid][fAmmo][8]);
			cache_get_value_name_int(i, "Ammo10", fData[fid][fAmmo][9]);
			
			cache_get_value_name_int(i, "TypeAmmo1", fData[fid][fTypeAmmo][0]);
			cache_get_value_name_int(i, "TypeAmmo2", fData[fid][fTypeAmmo][1]);
			cache_get_value_name_int(i, "TypeAmmo3", fData[fid][fTypeAmmo][2]);
			cache_get_value_name_int(i, "TypeAmmo4", fData[fid][fTypeAmmo][3]);
			cache_get_value_name_int(i, "TypeAmmo5", fData[fid][fTypeAmmo][4]);
			cache_get_value_name_int(i, "TypeAmmo6", fData[fid][fTypeAmmo][5]);
			cache_get_value_name_int(i, "TypeAmmo7", fData[fid][fTypeAmmo][6]);
			cache_get_value_name_int(i, "TypeAmmo8", fData[fid][fTypeAmmo][7]);
			cache_get_value_name_int(i, "TypeAmmo9", fData[fid][fTypeAmmo][8]);
			cache_get_value_name_int(i, "TypeAmmo10", fData[fid][fTypeAmmo][9]);

			cache_get_value(i, "vehiclemodel", str);
      		sscanf(str, "p<|>ddddd", fData[fid][fVehicleModel][0], fData[fid][fVehicleModel][1], fData[fid][fVehicleModel][2], fData[fid][fVehicleModel][3], fData[fid][fVehicleModel][4]);

			cache_get_value(i, "vehiclefuel", str);
      		sscanf(str, "p<|>ddddd", fData[fid][fVehicleFuel][0], fData[fid][fVehicleFuel][1], fData[fid][fVehicleFuel][2], fData[fid][fVehicleFuel][3], fData[fid][fVehicleFuel][4]);
			
			cache_get_value(i, "vehiclehealth", str);
      		sscanf(str, "p<|>fffff", fData[fid][fVehicleHealth][0], fData[fid][fVehicleHealth][1], fData[fid][fVehicleHealth][2], fData[fid][fVehicleHealth][3], fData[fid][fVehicleHealth][4]);

			cache_get_value(i, "vehiclepos1", str);
      		sscanf(str, "p<|>ffff", fData[fid][fVehiclePos][0], fData[fid][fVehiclePos][1], fData[fid][fVehiclePos][2], fData[fid][fVehiclePos][3]);

			cache_get_value(i, "vehiclepos2", str);
      		sscanf(str, "p<|>ffff", fData[fid][fVehiclePos1][0], fData[fid][fVehiclePos1][1], fData[fid][fVehiclePos1][2], fData[fid][fVehiclePos1][3]);

			cache_get_value(i, "vehiclepos3", str);
      		sscanf(str, "p<|>ffff", fData[fid][fVehiclePos2][0], fData[fid][fVehiclePos2][1], fData[fid][fVehiclePos2][2], fData[fid][fVehiclePos2][3]);

			cache_get_value(i, "vehiclepos4", str);
      		sscanf(str, "p<|>ffff", fData[fid][fVehiclePos3][0], fData[fid][fVehiclePos3][1], fData[fid][fVehiclePos3][2], fData[fid][fVehiclePos3][3]);

			cache_get_value(i, "vehiclepos5", str);
      		sscanf(str, "p<|>ffff", fData[fid][fVehiclePos4][0], fData[fid][fVehiclePos4][1], fData[fid][fVehiclePos4][2], fData[fid][fVehiclePos4][3]);

			Iter_Add(FAMILYS, fid);
			Family_Refresh(fid);
	    }
	    printf("*** [Database: Loaded] family data (%d count).", rows);
	}
}

function KickOfflineFamily(playerid, NamaUntukDiKick[])
{
	if(cache_num_rows() < 1)
	{
		return Error(playerid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NamaUntukDiKick);
	}
	else
	{
	    new RegID;
		new rank = 0;
		new family = -1;
		cache_get_value_index_int(0, 0, RegID);
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET family=%d, familyrank=%d WHERE reg_id=%d", family, rank, RegID);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

function ShowFamilyInfo(playerid)
{
	new rows = cache_num_rows();
 	if(rows)
  	{
 		new fname[50],
 			fleader[50],
			ftype[50],
			string[512];
			
		cache_get_value_index(0, 0, fname);
		cache_get_value_index(0, 1, fleader);
        cache_get_value_index(0, 1, fleader);

		format(string, sizeof(string), "Family ID: %d\nFamily Name: %s\nFamily Leader: %s\nFamily Type: %s",
		pData[playerid][pFamily], fname, fleader, ftype);
		
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Family Info", string, "Okay", "");
	}
}

function ShowFamilyMember(playerid)
{
	new rows = cache_num_rows(), pid, username[50], frank, query[1048];
 	if(rows)
  	{
		for(new i = 0; i != rows; i++)
		{
			cache_get_value_index(i, 0, username);
			pid = GetID(username);
			
			format(query, sizeof(query), "%s"WHITE_E"%d. %s ", query, (i+1), username);
			
			if(IsPlayerConnected(pid))
				strcat(query, ""GREEN_E"(ONLINE) ");
			else
				strcat(query, ""RED_E"(OFFLINE) ");
			
			cache_get_value_index_int(i, 1, frank);
			if(frank == 1) format(query, sizeof(query), "%s", fData[pData[playerid][pFamily]][fNameRank1]);
			else if(frank == 2) format(query, sizeof(query), "%s", fData[pData[playerid][pFamily]][fNameRank2]);
			else if(frank == 3) format(query, sizeof(query), "%s", fData[pData[playerid][pFamily]][fNameRank3]);
			else if(frank == 4) format(query, sizeof(query), "%s", fData[pData[playerid][pFamily]][fNameRank4]);
			else if(frank == 5) format(query, sizeof(query), "%s", fData[pData[playerid][pFamily]][fNameRank5]);
			else if(frank == 6) format(query, sizeof(query), "%s", fData[pData[playerid][pFamily]][fNameRank6]);
			else strcat(query, ""FAMILY_E"None(0)");
			strcat(query, "\n{FFFFFF}");
		}
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Family Member", query, "Okay", "");
	}
}
