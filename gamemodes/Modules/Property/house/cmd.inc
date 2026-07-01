//House System
CMD:createhouse(playerid, params[])
{
	if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");
	new hid = Iter_Free(Houses), address[128];
	if(hid == -1) return Error(playerid, "You cant create more door!");
	new type, query[512];
	if(sscanf(params, "ds[128]", type, address)) return Usage(playerid, "/createhouse [type, 0.small 1.medium 2.Big] [addres]");
	format(hData[hid][hOwner], 128, "-");
	GetPlayerPos(playerid, hData[hid][hExtposX], hData[hid][hExtposY], hData[hid][hExtposZ]);
	GetPlayerFacingAngle(playerid, hData[hid][hExtposA]);
	hData[hid][hExtVw] = GetPlayerVirtualWorld(playerid);
	hData[hid][hExtInt] = GetPlayerInterior(playerid);
	format(hData[hid][hAddress], 128, address);
	hData[hid][hLocked] = 0;
	hData[hid][hMoney] = 0;
	hData[hid][hIntposX] = arrHouseInteriors[type][eHouseX];
	hData[hid][hIntposY] = arrHouseInteriors[type][eHouseY];
	hData[hid][hIntposZ] = arrHouseInteriors[type][eHouseZ];
	hData[hid][hIntposA] = arrHouseInteriors[type][eHouseAngle];
	hData[hid][hInt] = arrHouseInteriors[type][eHouseInterior];
	hData[hid][hLastVisited] = 0;
	hData[hid][hType] = type+1;
	if(type == 0) hData[hid][hPrice] = 700000;
	else if(type == 1) hData[hid][hPrice] = 1100000;
	else if(type == 2) hData[hid][hPrice] = 2000000;
	
	for (new i = 0; i < HOUSE_WEAPON_SLOTS; i ++)
	{
        hData[hid][hWeapon][i] = 0;
        hData[hid][hAmmo][i] = 0;
		hData[hid][hTypeAmmo][i] = 0;
    }

    for (new i = 0; i < HOUSE_SCHEMATIC_SLOTS; i ++)
    {
        hData[hid][hSchematic][i] = 0;
    }
    House_Refresh(hid);
	Iter_Add(Houses, hid);
	
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO houses SET ID='%d', owner='%s', price='%d', type='%d', extposx='%f', extposy='%f', extposz='%f', extposa='%f', address='%s'", hid, hData[hid][hOwner], hData[hid][hPrice], hData[hid][hType], hData[hid][hExtposX], hData[hid][hExtposY], hData[hid][hExtposZ], hData[hid][hExtposA], hData[hid][hAddress]);
	mysql_tquery(g_SQL, query, "OnHousesCreated", "i", hid);
	return 1;
}

CMD:gotohouse(playerid, params[])
{
	new hid;
	if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");

	if(sscanf(params, "d", hid))
		return Usage(playerid, "/gotohouse [id]");
	if(!Iter_Contains(Houses, hid)) return Error(playerid, "The doors you specified ID of doesn't exist.");
	SetPlayerPosition(playerid, hData[hid][hExtposX], hData[hid][hExtposY], hData[hid][hExtposZ], hData[hid][hExtposA]);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
	SendClientMessageEx(playerid, COLOR_WHITE, "You has teleport to house id %d", hid);
	pData[playerid][pInDoor] = -1;
	pData[playerid][pInHouse] = -1;
	pData[playerid][pInBiz] = -1;
	return 1;
}

CMD:edithouse(playerid, params[])
{
    static
        hid,
        type[24],
        string[128];

	if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");

    if(sscanf(params, "ds[24]S()[128]", hid, type, string))
    {
        Usage(playerid, "/edithouse [id] [name]");
        SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, interior, locked, owner, price, type, reset, delete");
        return 1;
    }
    if((hid < 0 || hid >= MAX_HOUSES))
        return Error(playerid, "You have specified an invalid ID.");
	if(!Iter_Contains(Houses, hid)) return Error(playerid, "The doors you specified ID of doesn't exist.");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, hData[hid][hExtposX], hData[hid][hExtposY], hData[hid][hExtposZ]);
		GetPlayerFacingAngle(playerid, hData[hid][hExtposA]);
        House_Save(hid);
		House_Refresh(hid);

        SendAdminMessage(TOMATO, "%s has adjusted the location of house ID: %d.", pData[playerid][pAdminname], hid);
    }
	else if(!strcmp(type, "interior", true))
    {
        new typeint;

        if(sscanf(string, "d", typeint))
            return Usage(playerid, "/edithouse [id] [interior1] [interior 0:Small 1:Medium 2:Big]");

        if(typeint < 0 || typeint > 2)
            return Error(playerid, "The specified interior must be between 0-2.");

        hData[hid][hIntposX] = arrHouseInteriors[typeint][eHouseX];
		hData[hid][hIntposY] = arrHouseInteriors[typeint][eHouseY];
		hData[hid][hIntposZ] = arrHouseInteriors[typeint][eHouseZ];
		hData[hid][hIntposA] = arrHouseInteriors[typeint][eHouseAngle];
		hData[hid][hInt] = arrHouseInteriors[typeint][eHouseInterior];
        hData[hid][hType] = typeint+1;

        foreach (new i : HouseStruct[hid]) {
            new query[128];
            mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `housestruct` WHERE `ID`='%d'", HouseStructure[hid][i][structureID]);
            mysql_tquery(g_SQL, query);
            if (IsValidDynamicObject(HouseStructure[hid][i][structureObject])) {
                DestroyDynamicObject(HouseStructure[hid][i][structureObject]);
                HouseStructure[hid][i][structureObject] = INVALID_STREAMER_ID;
            }

            new tmp_houseStructure[houseStructure];
            HouseStructure[hid][i] = tmp_houseStructure;

            new current = i;
            Iter_SafeRemove(HouseStruct[hid], current, i);
        }

        CreateHouseInterior(hid);

        foreach (new i : Player) if(pData[i][pInHouse] == hData[hid][hID])
        {
           	SetPlayerPos(i, hData[hid][hIntposX], hData[hid][hIntposY], hData[hid][hIntposZ]);
            SetPlayerFacingAngle(i, hData[hid][hIntposA]);

            SetPlayerInterior(i, hData[hid][hInt]);
            SetCameraBehindPlayer(i);
        }
        House_Save(hid);
        SendAdminMessage(COLOR_RED, "AdmCmd: %s has adjusted the interior of house ID: %d to %d.", ReturnName(playerid), hid, typeint);
    }
    else if(!strcmp(type, "locked", true))
    {
        new locked;

        if(sscanf(string, "d", locked))
            return Usage(playerid, "/edithouse [id] [locked] [0/1]");

        if(locked < 0 || locked > 1)
            return Error(playerid, "You must specify at least 0 or 1.");

        hData[hid][hLocked] = locked;
        House_Save(hid);
		House_Refresh(hid);

        if(locked) {
            SendAdminMessage(TOMATO, "%s has locked house ID: %d.", pData[playerid][pAdminname], hid);
        }
        else {
            SendAdminMessage(TOMATO, "%s has unlocked house ID: %d.", pData[playerid][pAdminname], hid);
        }
    }
    else if(!strcmp(type, "price", true))
    {
        new price;

        if(sscanf(string, "d", price))
            return Usage(playerid, "/edithouse [id] [Price] [Amount]");

        hData[hid][hPrice] = price;

        House_Save(hid);
		House_Refresh(hid);
        SendAdminMessage(TOMATO, "%s has adjusted the price of house ID: %d to %d.", pData[playerid][pAdminname], hid, price);
    }
	else if(!strcmp(type, "type", true))
    {
        new htype;

        if(sscanf(string, "d", htype))
            return Usage(playerid, "/edithouse [id] [Type] [1.small 2.medium 3.Big]");

        hData[hid][hType] = htype;
		House_Type(hid);
        House_Save(hid);
		House_Refresh(hid);
        SendAdminMessage(TOMATO, "%s has adjusted the type of house ID: %d to %d.", pData[playerid][pAdminname], hid, htype);
    }
    else if(!strcmp(type, "owner", true))
    {
        new owners[MAX_PLAYER_NAME];

        if(sscanf(string, "s[32]", owners))
            return Usage(playerid, "/edithouse [id] [owner] [player name] (use '-' to no owner)");

        format(hData[hid][hOwner], MAX_PLAYER_NAME, owners);

        House_Save(hid);
		House_Refresh(hid);
        SendAdminMessage(TOMATO, "%s has adjusted the owner of house ID: %d to %s", pData[playerid][pAdminname], hid, owners);
    }
    else if(!strcmp(type, "reset", true))
    {
        HouseReset(hid);
		House_Save(hid);
		House_Refresh(hid);
        SendAdminMessage(TOMATO, "%s has reset house ID: %d.", pData[playerid][pAdminname], hid);
    }
	else if(!strcmp(type, "garage", true))
    {
		GetPlayerPos(playerid, hData[hid][hGarageposX], hData[hid][hGarageposY], hData[hid][hGarageposZ]);
		hData[hid][hGarage] = 1;
        House_Save(hid);
		House_Refresh(hid);

        SendAdminMessage(TOMATO, "%s has adjusted the garage of house ID: %d.", pData[playerid][pAdminname], hid);
    }
	else if(!strcmp(type, "delete", true))
	{
		if(IsValidDynamic3DTextLabel(hData[hid][hLabel])) DestroyDynamic3DTextLabel(hData[hid][hLabel]);
        if(IsValidDynamicPickup(hData[hid][hPickup][0])) DestroyDynamicPickup(hData[hid][hPickup][0]);
		if(IsValidDynamicPickup(hData[hid][hPickup][1])) DestroyDynamicPickup(hData[hid][hPickup][1]);
		if(IsValidDynamicCP(hData[hid][hCP][0])) DestroyDynamicCP(hData[hid][hCP][0]);
		if(IsValidDynamicCP(hData[hid][hCP][1])) DestroyDynamicCP(hData[hid][hCP][1]);
        if(IsValidDynamic3DTextLabel(hData[hid][hGarageLabel])) DestroyDynamic3DTextLabel(hData[hid][hGarageLabel]);
        if(IsValidDynamicPickup(hData[hid][hGaragePickup])) DestroyDynamicPickup(hData[hid][hGaragePickup]);
		if(IsValidDynamicCP(hData[hid][hGarageCP])) DestroyDynamicCP(hData[hid][hGarageCP]);
		HouseReset(hid);
		foreach (new i : HouseStruct[hid]) {
            new query[128];
            mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `housestruct` WHERE `ID`='%d'", HouseStructure[hid][i][structureID]);
            mysql_tquery(g_SQL, query);
            if (IsValidDynamicObject(HouseStructure[hid][i][structureObject])) {
                DestroyDynamicObject(HouseStructure[hid][i][structureObject]);
                HouseStructure[hid][i][structureObject] = INVALID_STREAMER_ID;
            }

            new tmp_houseStructure[houseStructure];
            HouseStructure[hid][i] = tmp_houseStructure;

            new current = i;
            Iter_SafeRemove(HouseStruct[hid], current, i);
        }
		Iter_Remove(Houses, hid);
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM houses WHERE ID=%d", hid);
		mysql_tquery(g_SQL, query);
        SendAdminMessage(TOMATO, "%s has delete house ID: %d.", pData[playerid][pAdminname], hid);
	}
    return 1;
}

CMD:lockhousetes(playerid, params[])
{
	foreach(new hid : Houses)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, hData[hid][hExtposX], hData[hid][hExtposY], hData[hid][hExtposZ]))
		{
			if(!Player_OwnsHouse(playerid, hid)) return Error(playerid, "You don't own this house.");
			if(!hData[hid][hLocked])
			{
				hData[hid][hLocked] = 1;
				House_Save(hid);

                GameTextForPlayer(playerid,"~w~house ~r~locked",1000,6);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
			else
			{
				hData[hid][hLocked] = 0;
				House_Save(hid);

                GameTextForPlayer(playerid,"~w~house ~g~unlocked",5000,6);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
		}
		else 
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.5, hData[hid][hIntposX], hData[hid][hIntposY], hData[hid][hIntposZ]))
			if(!Player_OwnsHouse(playerid, hid)) return Error(playerid, "You don't own this house.");
			if(!hData[hid][hLocked])
			{
				hData[hid][hLocked] = 1;
				House_Save(hid);

                GameTextForPlayer(playerid,"~w~house ~r~locked",1000,6);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
			else
			{
				hData[hid][hLocked] = 0;
				House_Save(hid);

                GameTextForPlayer(playerid,"~w~house ~g~unlocked",5000,6);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
		}
	}
	return 1;
}

CMD:lockhouse(playerid, params[])
{
	foreach(new hid : Houses)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, hData[hid][hExtposX], hData[hid][hExtposY], hData[hid][hExtposZ]))
		{
			if(!Player_OwnsHouse(playerid, hid)) return Error(playerid, "You don't own this house.");
			if(!hData[hid][hLocked])
			{
				hData[hid][hLocked] = 1;
				House_Save(hid);

                GameTextForPlayer(playerid,"~w~house ~r~locked",1000,6);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
			else
			{
				hData[hid][hLocked] = 0;
				House_Save(hid);

                GameTextForPlayer(playerid,"~w~house ~g~unlocked",5000,6);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
		}
	}
	return 1;
}

CMD:givehouse(playerid, params[])
{
	new hid, otherid;
	
	if(pData[playerid][pLevel] < 3)
	    return Error(playerid, "Anda harus level 3 untuk bisa melalukan akses ini");
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1424.31, 1546.21, 3010.83)) return Error(playerid, "Anda harus berada di City Hall!");
	if(sscanf(params, "ud", otherid, hid)) return Usage(playerid, "/givehouse [playerid/name] [id] | /myhouse - for show info");
	if(hid == -1) return Error(playerid, "Invalid id");
	

	if(!IsPlayerConnected(otherid) || !NearPlayer(playerid, otherid, 4.0))
        return Error(playerid, "The specified player is disconnected or not near you.");

	if(!Player_OwnsHouse(playerid, hid)) return Error(playerid, "You dont own this id house.");

	if(PropertiResidential_CountMax(otherid) >= PropertiesResidential_Max(otherid)) return Error(playerid, "property slots are full");
	GetPlayerName(otherid, hData[hid][hOwner], MAX_PLAYER_NAME);
	hData[hid][hLastVisited] = gettime();

	House_Refresh(hid);
	House_Save(hid);
	Info(playerid, "Anda memberikan rumah id: %d kepada %s", hid, ReturnName(otherid));
	Info(otherid, "%s memberikan rumah id: %d kepada anda", hid, ReturnName(playerid));
	return 1;
}

CMD:myhouse(playerid)
{
	if(GetOwnedHouses(playerid) == -1) return Error(playerid, "You don't have a houses.");
	//if(!Player_OwnsBusiness(playerid, id)) return Error(playerid, "You don't own this business.");
	new hid, _tmpstring[128], count = GetOwnedHouses(playerid), CMDSString[1024];
	CMDSString = "";
	new lock[128];
	Loop(itt, (count + 1), 1)
	{
	    hid = ReturnPlayerHousesID(playerid, itt);
		if(hData[hid][hLocked] == 1)
		{
			lock = ""RED_E"Dikunci";

		}
		else
		{
			lock = ""GREEN_E"Dibuka";
		}
		if(itt == count)
		{
		    format(_tmpstring, sizeof(_tmpstring), ""LB_E"%d.\t"WHITE_E"%s   (%s)\n", itt, hData[hid][hAddress], lock);
		}
		else format(_tmpstring, sizeof(_tmpstring), ""LB_E"%d.\t"WHITE_E"%s  (%s)\n", itt, hData[hid][hAddress], lock);
		strcat(CMDSString, _tmpstring);
	}
	ShowPlayerDialog(playerid, DIALOG_MY_HOUSES, DIALOG_STYLE_LIST, "{0000FF}Houses", CMDSString, "Select", "Cancel");
	return 1;
}

CMD:hm(playerid, params[]) {
    static
        id = -1;

    if ((id = pData[playerid][pInHouse]) != -1) {
        if (Player_OwnsHouse(playerid, id)) {
            Dialog_Show(playerid, House_Menu, DIALOG_STYLE_LIST, "House Option", "Toggle light\nStorage\nGive Builder Acces", "Select", "Cancel");
            return 1;
        }
        Error(playerid, "You must be in your house to open house menu.");
        return 1;
    }
    Error(playerid, "You must be in a house to open house menu.");
    return 1;
}

CMD:hl(playerid, params[])
{
    new bool:house, string[128];
    for(new hid = 1; hid < MAX_HOUSES; hid++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 20, hData[hid][hIntposX], hData[hid][hIntposY], hData[hid][hIntposZ]) && GetPlayerVirtualWorld(playerid) == hid)
		{
		    switch (hData[hid][house_Lights])
			{
				case false:
				{
					format(string, sizeof(string), "* %s turned on the lights in their property.", pData[playerid][pName]);
					hData[hid][house_Lights] = true;
					foreach (new i : Player)
					{
					    if(IsPlayerInRangeOfPoint(i, 50, hData[hid][hIntposX], hData[hid][hIntposY], hData[hid][hIntposZ]) && GetPlayerVirtualWorld(playerid) == hid)
						{
						    TextDrawHideForPlayer(i, HouseLight);
						    house = true;
						}
					}
					break;
				}
				case true:
				{
					format(string, sizeof(string), "* %s turned off the lights in their property.", pData[playerid][pName]);
					hData[hid][house_Lights] = false;
					foreach (new i : Player)
					{
					    if(IsPlayerInRangeOfPoint(i, 50, hData[hid][hIntposX], hData[hid][hIntposY], hData[hid][hIntposZ]) && GetPlayerVirtualWorld(playerid) == hid)
						{
                            TextDrawShowForPlayer(i, HouseLight);
                            house = true;
						}
					}
					break;
				}
			}
		}
	}
	if (house) SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, string);
    if (!house) return Error(playerid, "You are not in inside a house!");
	return 1;
}

CMD:dyoh(playerid, params[]) {
    static
        id = -1;

    if (pData[playerid][pJob] != 9 && pData[playerid][pJob2] != 9)
        return Error(playerid, "You're not a Builder!");

    if ((id = pData[playerid][pInHouse]) != -1) {
        if (hData[id][houseBuilder] == pData[playerid][pID] || Player_OwnsHouse(playerid, id)) {
            Dialog_Show(playerid, House_Structure, DIALOG_STYLE_LIST, "House Structure", "Add structure\nMove structure\nRetexture structure\nDestroy structure\nCopy structure\nDestroy all structure\nStructure list\nMove furniture\nDestroy furniture\nStore furniture\nFurniture list\nAbandon", "Select", "Back");
            return 1;
        }
        Error(playerid, "You don't have any permission to access this house structures");
        return 1;
    }
    Error(playerid, "You're not in any house.");
    return 1;
}

CMD:segelrumah(playerid, params[])
{
    if(pData[playerid][pAdmin] < 6) return PermissionError(playerid);
    
    new hid, reason[64];
    if(sscanf(params, "ds[64]", hid, reason))
        return Usage(playerid, "/segelrumah [houseid] [alasan]");

    if(!Iter_Contains(Houses, hid)) return Error(playerid, "Rumah tidak ditemukan.");

    if(!strcmp(hData[hid][hOwner], "-"))
        return Error(playerid, "Rumah ini tidak memiliki pemilik.");

    if(hData[hid][hSegel] == 1)
        return Error(playerid, "Rumah ini sudah dalam status segel.");

    if(gettime() - hData[hid][hLastVisited] < 15 * 86400)
        return Error(playerid, "Pemilik masih aktif dalam 15 hari terakhir. Tidak bisa disegel.");

    hData[hid][hSegel] = 1;
    hData[hid][hSegelTime] = gettime();
    format(hData[hid][hSegelAdmin], 24, "%s", pData[playerid][pAdminname]);
    format(hData[hid][hSegelReason], 128, "%s", reason);
    hData[hid][hLocked] = 1;

    House_Refresh(hid);
    House_Save(hid);

    Servers(playerid, "Anda telah menyegel rumah ID %d dengan alasan: %s", hid, reason);
    new str[128];
    format(str, sizeof(str), "INFO: Rumah ID %d milik %s telah disegel oleh admin.", hid, hData[hid][hOwner]);
    SendClientMessageToAll(COLOR_RED, str);
    return 1;
}

CMD:hapussegel(playerid, params[])
{
    if(pData[playerid][pAdmin] < 6) return PermissionError(playerid);

    new hid;
    if(sscanf(params, "d", hid))
        return Usage(playerid, "/hapussegel [houseid]");

    if(!Iter_Contains(Houses, hid)) return Error(playerid, "Rumah tidak ditemukan.");
    if(hData[hid][hSegel] == 0) return Error(playerid, "Rumah ini tidak dalam status segel.");

    hData[hid][hSegel] = 0;
    hData[hid][hSegelTime] = 0;
    format(hData[hid][hSegelAdmin], 24, "-");
    format(hData[hid][hSegelReason], 128, "-");

    House_Refresh(hid);
    House_Save(hid);

    Servers(playerid, "Anda telah membuka segel rumah ID %d.", hid);
    return 1;
}

CMD:tebusrumah(playerid, params[])
{
    new hid;
    if(sscanf(params, "d", hid))
        return Usage(playerid, "/tebusrumah [houseid]");

    if(!Iter_Contains(Houses, hid)) return Error(playerid, "Rumah tidak ditemukan.");
    if(hData[hid][hSegel] == 0) return Error(playerid, "Rumah ini tidak dalam status segel.");

    if(strcmp(hData[hid][hOwner], pData[playerid][pName]))
        return Error(playerid, "Anda bukan pemilik rumah ini.");

    if(gettime() - hData[hid][hSegelTime] > 7 * 86400)
        return Error(playerid, "Waktu tebus sudah habis (7 hari). Rumah akan dilelang oleh admin.");

    new tebus = hData[hid][hPrice] * 25 / 100; // 25% of house price
    if(pData[playerid][pMoney] < tebus)
        return Error(playerid, "Uang anda tidak cukup. Butuh $%s untuk menebus.", FormatMoney(tebus));

    GivePlayerMoneyEx(playerid, -tebus);
    hData[hid][hSegel] = 0;
    hData[hid][hSegelTime] = 0;
    format(hData[hid][hSegelAdmin], 24, "-");
    format(hData[hid][hSegelReason], 128, "-");

    House_Refresh(hid);
    House_Save(hid);

    SendCustomMessage(playerid, "HOUSE", "Anda telah menebus rumah ID %d seharga $%s.", hid, FormatMoney(tebus));
    return 1;
}

CMD:infosegel(playerid, params[])
{
    new hid, hari;
    if(sscanf(params, "d", hid))
        return Usage(playerid, "/infosegel [houseid]");

    if(!Iter_Contains(Houses, hid)) return Error(playerid, "Rumah tidak ditemukan.");
    if(hData[hid][hSegel] == 0) return Error(playerid, "Rumah ini tidak dalam status segel.");

    hari = (gettime() - hData[hid][hSegelTime]) / 86400;
    SendClientMessageEx(playerid, -1, "{FF0000}=====[ {FFFFFF}House Seal Info {FF0000}]=====");
    SendClientMessageEx(playerid, -1, "House ID: %d | Owner: %s", hid, hData[hid][hOwner]);
    SendClientMessageEx(playerid, -1, "Admin: %s | Alasan: %s", hData[hid][hSegelAdmin], hData[hid][hSegelReason]);
    SendClientMessageEx(playerid, -1, "Disimpan: %d hari yang lalu | Sisa: %d hari lagi untuk tebus.", hari, 7 - hari);
    SendClientMessageEx(playerid, -1, "Harga Tebus: $%s (25%% dari harga rumah)", FormatMoney(hData[hid][hPrice] * 25 / 100));
    return 1;
}
