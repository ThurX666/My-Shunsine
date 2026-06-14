
CMD:fcreate(playerid, params[])
{
	if(pData[playerid][pDivision] != 2) return Error(playerid, "You must be a family division.");
	Dialog_Show(playerid, FCName, DIALOG_STYLE_INPUT, "Family Create", "Masukan nama family yang akan dibuat:", "Next", "Cancel");
	return 1;
}

CMD:fdelete(playerid, params[])
{
 	if(pData[playerid][pDivision] != 2) return Error(playerid, "You must be a family division.");
    new fid, query[128];
	if(sscanf(params, "i", fid)) return Usage(playerid, "/fdelete [fid]");
	if(!Iter_Contains(FAMILYS, fid)) return Error(playerid, "The you specified ID of doesn't exist.");
	
    format(fData[fid][fName], 50, "None");
	format(fData[fid][fLeader], 50, "None");
	format(fData[fid][fMotd], 50, "None");
	fData[fid][fExtposX] = 0;
	fData[fid][fExtposY] = 0;
	fData[fid][fExtposZ] = 0;
	fData[fid][fExtposA] = 0;
	
	fData[fid][fIntposX] = 0;
	fData[fid][fIntposY] = 0;
	fData[fid][fIntposZ] = 0;
	fData[fid][fIntposA] = 0;
	fData[fid][fInt] = 0;
	
	fData[fid][fMoney] = 0;
	fData[fid][fMarijuana] = 0;
	fData[fid][fComponent] = 0;
	fData[fid][fMaterial] = 0;
	fData[fid][fSafeposX] = 0;
	fData[fid][fSafeposY] = 0;
	fData[fid][fSafeposZ] = 0;
	
	DestroyDynamic3DTextLabel(fData[fid][fLabelext]);
	DestroyDynamicPickup(fData[fid][fPickext]);
	DestroyDynamic3DTextLabel(fData[fid][fLabelint]);
	DestroyDynamicPickup(fData[fid][fPickint]);
	DestroyDynamic3DTextLabel(fData[fid][fLabelsafe]);
	DestroyDynamicPickup(fData[fid][fPicksafe]);
	Iter_Remove(FAMILYS, fid);
	
	mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET family=-1,familyrank=0 WHERE family=%d", fid);
	mysql_tquery(g_SQL, query);
	
	foreach(new ii : Player)
	{
 		if(pData[ii][pFamily] == fid)
   		{
			pData[ii][pFamily]= -1;
			pData[ii][pFamilyRank] = 0;
		}
	}

	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM familys WHERE ID=%d", fid);
	mysql_tquery(g_SQL, query);
    SendStaffMessage(TOMATO, "Admin %s telah menghapus family ID: %d.", pData[playerid][pAdminname], fid);
	return 1;
}

CMD:fedit(playerid, params[])
{
    static
        fid,
        type[24],
        string[128],
		otherid;

	if(pData[playerid][pDivision] != 2) return Error(playerid, "You must be a family division.");

    if(sscanf(params, "ds[24]S()[128]", fid, type, string))
    {
        Usage(playerid, "/fedit [id] [name]");
        SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, interior, name, leader");
        return 1;
    }
    if((fid < 0 || fid >= MAX_FAMILY))
        return Error(playerid, "You have specified an invalid ID.");
	if(!Iter_Contains(FAMILYS, fid)) return Error(playerid, "The you specified ID of doesn't exist.");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, fData[fid][fExtposX], fData[fid][fExtposY], fData[fid][fExtposZ]);
		GetPlayerFacingAngle(playerid, fData[fid][fExtposA]);

        Family_Save(fid);
		Family_Refresh(fid);

        SendStaffMessage(TOMATO, "%s has adjusted the location of entrance ID: %d.", pData[playerid][pAdminname], fid);
    }
    else if(!strcmp(type, "interior", true))
    {
        GetPlayerPos(playerid, fData[fid][fIntposX], fData[fid][fIntposY], fData[fid][fIntposZ]);
		GetPlayerFacingAngle(playerid, fData[fid][fIntposA]);

		fData[fid][fInt] = GetPlayerInterior(playerid);
        Family_Save(fid);
		Family_Refresh(fid);

        SendStaffMessage(TOMATO, "%s has adjusted the interior spawn of entrance ID: %d.", pData[playerid][pAdminname], fid);
    }
    else if(!strcmp(type, "name", true))
    {
        new name[50];

        if(sscanf(string, "s[50]", name))
            return Usage(playerid, "/fedit [id] [name] [fname]");

        format(fData[fid][fName], 50, name);
		Family_Save(fid);
		Family_Refresh(fid);

        SendStaffMessage(TOMATO, "Admin %s has changed the family name ID: %d to: %s.", pData[playerid][pAdminname], fid, name);
    }
    else if(!strcmp(type, "leader", true))
    {
        if(sscanf(string, "d", otherid))
            return Usage(playerid, "/fedit [id] [leader] [playerid]");
		
		if(otherid == INVALID_PLAYER_ID)
			return Error(playerid, "invalid player fid");

        format(fData[fid][fLeader], 50, pData[otherid][pName]);
		Family_Save(fid);
		Family_Refresh(fid);

        SendStaffMessage(TOMATO, "Admin %s has changed the family leader ID: %d to: %s.", pData[playerid][pAdminname], fid, pData[otherid][pName]);
    }
    // else if(!strcmp(type, "safe", true))
    // {
    //     GetPlayerPos(playerid, fData[fid][fSafeposX], fData[fid][fSafeposY], fData[fid][fSafeposZ]);

    //     Family_Save(fid);
	// 	Family_Refresh(fid);
		
	// 	SendStaffMessage(TOMATO, "Admin %s has changed the family safepos ID: %d.", pData[playerid][pAdminname], fid);
    // }
    // else if(!strcmp(type, "money", true))
    // {
    //     new money;

    //     if(sscanf(string, "d", money))
    //         return Usage(playerid, "/fedit [id] [money] [ammount]");

    //     fData[fid][fMoney] = money;
		
    //     Family_Save(fid);
	// 	Family_Refresh(fid);
		
	// 	SendStaffMessage(TOMATO, "Admin %s has changed the family money ID: %d to %s.", pData[playerid][pAdminname], fid, FormatMoney(money));
    // }
    // else if(!strcmp(type, "marijuana", true))
    // {
    //     new marijuana;

    //     if(sscanf(string, "d", marijuana))
    //         return Usage(playerid, "/fedit [id] [marijuana] [ammount]");

    //     fData[fid][fMarijuana] = marijuana;
		
    //     Family_Save(fid);
	// 	Family_Refresh(fid);
		
	// 	SendStaffMessage(TOMATO, "Admin %s has changed the family marijuana ID: %d to %s.", pData[playerid][pAdminname], fid, marijuana);
    // }
	// else if(!strcmp(type, "component", true))
    // {
    //     new comp;

    //     if(sscanf(string, "d", comp))
    //         return Usage(playerid, "/fedit [id] [component] [ammount]");

    //     fData[fid][fComponent] = comp;
		
    //     Family_Save(fid);
	// 	Family_Refresh(fid);
		
	// 	SendStaffMessage(TOMATO, "Admin %s has changed the family component ID: %d to %s.", pData[playerid][pAdminname], fid, comp);
    // }
	// else if(!strcmp(type, "material", true))
    // {
    //     new mat;

    //     if(sscanf(string, "d", mat))
    //         return Usage(playerid, "/fedit [id] [material] [ammount]");

    //     fData[fid][fMarijuana] = mat;
		
    //     Family_Save(fid);
	// 	Family_Refresh(fid);
		
	// 	SendStaffMessage(TOMATO, "Admin %s has changed the family material ID: %d to %s.", pData[playerid][pAdminname], fid, mat);
    // }
    return 1;
}

// CMD:fsafe(playerid)
// {
// 	if(pData[playerid][pFamily] == -1)
// 		return Error(playerid, "Anda bukan anggota family");
		
// 	new fid = pData[playerid][pFamily];
// 	if(IsPlayerInRangeOfPoint(playerid, 3.0, fData[fid][fSafeposX], fData[fid][fSafeposY], fData[fid][fSafeposZ]))
//     {
//      	ShowPlayerDialog(playerid, FAMILY_SAFE, DIALOG_STYLE_LIST, "Family SAFE", "Storage\nMarijuana\nComponent\nCgun\nMoney", "Select", "Cancel");
//     }
//  	else Error(playerid, "You aren't in range in area family safe.");
// 	return 1;
// }

CMD:finvite(playerid, params[])
{
	if(pData[playerid][pFamily] == -1) return Error(playerid, "You are not in family!"); 
	if(pData[playerid][pFamilyRank] < 5) return Error(playerid, "You must family rank 5 - 6!"); 
	new otherid;
	if(pData[otherid][pCS] < 0) return Error(playerid, "This player Character Story has not been aproved!");
    if(sscanf(params, "u", otherid)) return Usage(playerid, "/finvite [playerid/PartOfName]"); 
	if(!IsPlayerConnected(otherid)) return Error(playerid, "Invalid ID.");
	if(otherid == playerid) return Error(playerid, "Invalid ID."); 
	if(!NearPlayer(playerid, otherid, 5.0)) return Error(playerid, "You must be near this player.");
	if(pData[otherid][pFamily] != -1) return Error(playerid, "Player tersebut sudah bergabung family!");
	if(pData[otherid][pFaction] != 0) return Error(playerid, "Player tersebut sudah bergabung faction!");
		
	pData[otherid][pFamInvite] = pData[playerid][pFamily];
	pData[otherid][pFamOffer] = playerid;
	Servers(playerid, "Anda telah menginvite %s untuk menjadi anggota family.", pData[otherid][pName]);
	Servers(otherid, "%s telah menginvite anda untuk menjadi anggota family. Type: /accept family or /deny family!", ReturnName2(playerid));
	return 1;
}

CMD:fvehicle(playerid, params[])
{
	if(pData[playerid][pFamily] == -1) return Error(playerid, "You are not in family!"); 
	if(pData[playerid][pFamilyRank] < 5) return Error(playerid, "You must family rank 5 - 6!");
		
	new string[212], bid = pData[playerid][pFamily];
	if(fData[bid][fVehicleModel][0] != 0) format(string,sizeof(string),"%s{00FFFF}%s\t"YELLOW_E"%s\n", string, GetVehicleName(fData[bid][fVehicle][0]));
	else format(string, sizeof(string), "%sBuy Vehicle\n", string);
	if(fData[bid][fVehicleModel][1] != 0) format(string,sizeof(string),"%s{00FFFF}%s\t"YELLOW_E"%s\n", string, GetVehicleName(fData[bid][fVehicle][1]));
	else format(string, sizeof(string), "%sBuy Vehicle\n", string);
	if(fData[bid][fVehicleModel][2] != 0) format(string,sizeof(string),"%s{00FFFF}%s\t"YELLOW_E"%s\n", string, GetVehicleName(fData[bid][fVehicle][2]));
	else format(string, sizeof(string), "%sBuy Vehicle\n", string);
	if(fData[bid][fVehicleModel][3] != 0) format(string,sizeof(string),"%s{00FFFF}%s\t"YELLOW_E"%s\n", string, GetVehicleName(fData[bid][fVehicle][3]));
	else format(string, sizeof(string), "%sBuy Vehicle\n", string);
	if(fData[bid][fVehicleModel][4] != 0) format(string,sizeof(string),"%s{00FFFF}%s\t"YELLOW_E"%s\n", string, GetVehicleName(fData[bid][fVehicle][4]));
	else format(string, sizeof(string), "%sBuy Vehicle\n", string);
	Dialog_Show(playerid, VehicleFamily, DIALOG_STYLE_LIST, "Vehicle Family:", string, "Select", "Close");
	return 1;
}

CMD:funinvite(playerid, params[])
{
	if(pData[playerid][pFamily] == -1)
		return Error(playerid, "You are not in family!");
		
	if(pData[playerid][pFamilyRank] < 5)
		return Error(playerid, "You must family level 5 - 6!");
	
	new otherid;
    if(sscanf(params, "u", otherid))
        return Usage(playerid, "/uninvite [playerid/PartOfName]");
		
	if(!IsPlayerConnected(otherid))
		return Error(playerid, "Invalid ID.");
	
	if(otherid == playerid)
		return Error(playerid, "Invalid ID.");
	
	if(pData[otherid][pFamilyRank] > pData[playerid][pFamilyRank])
		return Error(playerid, "You cant kick him.");
		
	pData[otherid][pFamilyRank] = 0;
	pData[otherid][pFamily] = -1;
	Servers(playerid, "Anda telah mengeluarkan %s dari anggota family.", pData[otherid][pName]);
	Servers(otherid, "%s telah mengeluarkan anda dari anggota family.", ReturnName2(playerid));
	return 1;
}

CMD:fkickoff(playerid, params[])
{
	if(pData[playerid][pFamily] == -1)
		return Error(playerid, "You are not in family!");
		
	if(pData[playerid][pFamilyRank] < 5)
		return Error(playerid, "You must family level 5 - 6!");

	new tmp[24];
	if(sscanf(params, "s[24]s[128]", tmp))
	{
	    Usage(playerid, "/fkickoff <Name_Account>");
	    return true;
	}
	new query[512];
    Info(playerid, "Kamu telah mengkick offline player "YELLOW_E"%s", tmp);
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "KickOfflineFamily", "is", playerid, tmp);
	return 1;
}

CMD:fsetrank(playerid, params[])
{
	new rank, otherid;
	if(pData[playerid][pFamilyRank] < 6)
		return Error(playerid, "You must family leader!");
		
	if(sscanf(params, "ud", otherid, rank))
        return Usage(playerid, "/fsetrank [playerid/PartOfName] [rank 1-6]");
	
	if(!IsPlayerConnected(otherid))
		return Error(playerid, "Invalid ID.");
	
	if(otherid == playerid)
		return Error(playerid, "Invalid ID.");
	
	if(pData[otherid][pFamily] != pData[playerid][pFamily])
		return Error(playerid, "This player is not in your family!");
	
	if(rank < 1 || rank > 6)
		return Error(playerid, "rank must 1 - 6 only");
	
	pData[otherid][pFamilyRank] = rank;
	Servers(playerid, "You has set %s family rank to level %d", pData[otherid][pName], rank);
	Servers(otherid, "%s has set your family rank to level %d", ReturnName2(playerid), rank);
	return 1;
}

CMD:f(playerid, params[])
{
    new text[128];

    if(pData[playerid][pInjured] == 1) return Error(playerid, "You injured at the moment.");
    if(pData[playerid][pFamily] == -1) return Error(playerid, "You must in family member to use this command");
    if(sscanf(params,"s[128]",text)) return Usage(playerid, "/f(family) [text]");
    if(strval(text) > 128) return Error(playerid,"Text too long.");
	SendFamilyMessage(pData[playerid][pFamily], COLOR_FAMILY, "[RADIO] %s %s: %s", GetFamilyRank(playerid), ReturnName2(playerid), params);
    return 1;
}

CMD:families(playerid) {
    new string[512];
    format(string, sizeof(string), "#\tName\tType\n");
    foreach(new fid : FAMILYS) {
        format(string, sizeof(string), "%s%d\t%d%s\t%s\n", string, fid, fData[fid][fName], fData[fid][fType]);
    }
    Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Official Families", string, "Close", "");
}

alias:finfo("fstat", "fstats")
CMD:finfo(playerid, params[])
{
	if(pData[playerid][pFamily] == -1) return Error(playerid, "You must in family member to use this command!");
	Dialog_Show(playerid, FamilyInfo, DIALOG_STYLE_LIST, "Family Info", "Family Info\nFamily Online\nFamily Member\nChange Rank Name", "Select", "Cancel");
	return 1;
}
