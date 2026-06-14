
Dialog:FCName(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        SetPVarString(playerid, "FCName", inputtext);
		Dialog_Show(playerid, FCType, DIALOG_STYLE_INPUT, "Family Create", "Masukan nama Type Family yang akan dibuat", "Select", "Cancel");
    }
	return 1;
}

Dialog:FCType(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        SetPVarString(playerid, "FCType", inputtext);
		Dialog_Show(playerid, FCLeader, DIALOG_STYLE_INPUT, "Family Create", "Masukan ID player yang ingin menjadi Leader:", "Select", "Cancel");
    }
	return 1;
}

Dialog:FCLeader(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new string[512];
        SetPVarInt(playerid, "FCLeader", strval(inputtext));
		new name[50], type[50];
		GetPVarString(playerid, "FCName", name, sizeof(name));
		GetPVarString(playerid, "FCType", type, sizeof(type));
		format(string, sizeof(string), "Name:\t%s\nType:\t%s\nLeader:\t%s", name, type, ReturnName(strval(inputtext)));
		Dialog_Show(playerid, FamilyCreate, DIALOG_STYLE_MSGBOX, "Family Create", string, "Create", "Cancel");
	}
	return 1;
}

Dialog:FamilyCreate(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new fid = Iter_Free(FAMILYS), name[50], type[50], query[128];
		GetPVarString(playerid, "FCName", name, sizeof(name));
		GetPVarString(playerid, "FCType", type, sizeof(type));
		new otherid = GetPVarInt(playerid, "FCLeader");
		if(fid == -1) return Error(playerid, "You cant create more family slot empty!");
        if(otherid == INVALID_PLAYER_ID) return Error(playerid, "invalid playerid.");
		if(pData[otherid][pFamily] != -1) return Error(playerid, "Player tersebut sudah bergabung family");
		if(pData[otherid][pFaction] != 0) return Error(playerid, "Player tersebut sudah bergabung faction");
			
		pData[otherid][pFamily] = fid;
		pData[otherid][pFamilyRank] = 6;
			
		format(fData[fid][fName], 50, name);
		format(fData[fid][fType], 50, type);
		format(fData[fid][fLeader], 50, pData[otherid][pName]);
		format(fData[fid][fMotd], 50, "None");
		format(fData[fid][fNameRank1], 50, "None");
		format(fData[fid][fNameRank2], 50, "None");
		format(fData[fid][fNameRank3], 50, "None");
		format(fData[fid][fNameRank4], 50, "None");
		format(fData[fid][fNameRank5], 50, "None");
		format(fData[fid][fNameRank6], 50, "None");

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

		Iter_Add(FAMILYS, fid);
		Servers(playerid, "Anda telah berhasil membuat family ID: %d dengan leader: %s", fid, pData[otherid][pName]);
		Servers(otherid, "Admin %s telah menset anda sebagai leader dari family ID: %d", pData[playerid][pAdminname], fid);
		
		new String[212];
		format(String, sizeof(String), "AdmWarn: "YELLOW_E"%s "WHITE_E"telah membuat family ID "YELLOW_E"%d "WHITE_E"dengan leader: "YELLOW_E"%s.", pData[playerid][pAdminname], fid, pData[otherid][pName]);
		SendClientAdm(COLOR_ARWIN, String, 4); 

		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO familys SET ID=%d, name='%s', leader='%s', type='%s'", fid, name, pData[otherid][pName], type);
		mysql_tquery(g_SQL, query, "OnFamilyCreated", "i", fid);
    }
	return 1;
}

Dialog:FamilyInfo(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        switch(listitem)
        {
            case 0:
            {
                if(pData[playerid][pFamily] == -1) return Error(playerid, "You dont have family!");
                new query[512];
                mysql_format(g_SQL, query, sizeof(query), "SELECT name,leader,type FROM familys WHERE ID = %d", pData[playerid][pFamily]);
                mysql_tquery(g_SQL, query, "ShowFamilyInfo", "i", playerid);
            }
            case 1:
            {
                if(pData[playerid][pFamily] == -1) return Error(playerid, "You dont have family!");

                new lstr[1024];
                format(lstr, sizeof(lstr), "Rank\tName\n");
                foreach(new i: Player)
                {
                    if(pData[i][pFamily] == pData[playerid][pFamily])
                    {
                        format(lstr, sizeof(lstr), "%s%s\t%s(%d)", lstr, GetFamilyRank(i), ReturnName(i), i);
                        format(lstr, sizeof(lstr), "%s\n", lstr);
                    }
                }
                format(lstr, sizeof(lstr), "%s\n", lstr);
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Family Online", lstr, "Close", "");

            }
            case 2:
            {
                if(pData[playerid][pFamily] == -1)
                    return Error(playerid, "You dont have family!");
                new query[512];
                mysql_format(g_SQL, query, sizeof(query), "SELECT username,familyrank FROM players WHERE family = %d", pData[playerid][pFamily]);
                mysql_tquery(g_SQL, query, "ShowFamilyMember", "i", playerid);
            }
            case 3:
            {
				if(pData[playerid][pFamilyRank] < 5) return Error(playerid, "Anda tidak memiliki akses");
                new string[512];
                if(pData[playerid][pFamily] == -1) return Error(playerid, "You dont have family!");
                format(string, sizeof(string), "%s\n%s\n%s\n%s\n%s\n%s", 
				fData[pData[playerid][pFamily]][fNameRank1],
				fData[pData[playerid][pFamily]][fNameRank2],
				fData[pData[playerid][pFamily]][fNameRank3],
				fData[pData[playerid][pFamily]][fNameRank4],
				fData[pData[playerid][pFamily]][fNameRank5],
				fData[pData[playerid][pFamily]][fNameRank6]);
				Dialog_Show(playerid, FamilyRank, DIALOG_STYLE_LIST, "Family Rank", string, "Select", "Cancel");
            }
        }
    }
	return 1;
}

Dialog:FamilyRank(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				SetPVarInt(playerid, "FamilyRank", 1);
				new string[512];
                format(string, sizeof(string), "Old Name: %s\nMasukan nama rank yang baru:", 
				fData[pData[playerid][pFamily]][fNameRank1]);
				Dialog_Show(playerid, FamilyChangeRank, DIALOG_STYLE_INPUT, "Family Rank", string, "Input", "Cancel");
			}
			case 1:
			{
				SetPVarInt(playerid, "FamilyRank", 2);
				new string[512];
                format(string, sizeof(string), "Old Name: %s\nMasukan nama rank yang baru:", 
				fData[pData[playerid][pFamily]][fNameRank2]);
				Dialog_Show(playerid, FamilyChangeRank, DIALOG_STYLE_INPUT, "Family Rank", string, "Input", "Cancel");
			}
			case 2:
			{
				SetPVarInt(playerid, "FamilyRank", 3);
				new string[512];
                format(string, sizeof(string), "Old Name: %s\nMasukan nama rank yang baru:", 
				fData[pData[playerid][pFamily]][fNameRank3]);
				Dialog_Show(playerid, FamilyChangeRank, DIALOG_STYLE_INPUT, "Family Rank", string, "Input", "Cancel");
			}
			case 3:
			{
				SetPVarInt(playerid, "FamilyRank", 4);
				new string[512];
                format(string, sizeof(string), "Old Name: %s\nMasukan nama rank yang baru:", 
				fData[pData[playerid][pFamily]][fNameRank4]);
				Dialog_Show(playerid, FamilyChangeRank, DIALOG_STYLE_INPUT, "Family Rank", string, "Input", "Cancel");
			}
			case 4:
			{
				SetPVarInt(playerid, "FamilyRank", 5);
				new string[512];
                format(string, sizeof(string), "Old Name: %s\nMasukan nama rank yang baru:", 
				fData[pData[playerid][pFamily]][fNameRank5]);
				Dialog_Show(playerid, FamilyChangeRank, DIALOG_STYLE_INPUT, "Family Rank", string, "Input", "Cancel");
			}
			case 5:
			{
				SetPVarInt(playerid, "FamilyRank", 6);
				new string[512];
                format(string, sizeof(string), "Old Name: %s\nMasukan nama rank yang baru:", 
				fData[pData[playerid][pFamily]][fNameRank6]);
				Dialog_Show(playerid, FamilyChangeRank, DIALOG_STYLE_INPUT, "Family Rank", string, "Input", "Cancel");
			}
		}
    }
	return 1;
}

Dialog:FamilyChangeRank(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		switch(GetPVarInt(playerid, "FamilyRank"))
		{
			case 1:
			{
				format(fData[pData[playerid][pFamily]][fNameRank1], 50, inputtext);
				SendCustomMessage(playerid, "FAMILY", "Kamu telah mengganti nama rank menjadi %s", inputtext);
				Family_Save(pData[playerid][pFamily]);
			}
			case 2:
			{
				format(fData[pData[playerid][pFamily]][fNameRank2], 50, inputtext);
				SendCustomMessage(playerid, "FAMILY", "Kamu telah mengganti nama rank menjadi %s", inputtext);
				Family_Save(pData[playerid][pFamily]);
			}
			case 3:
			{
				format(fData[pData[playerid][pFamily]][fNameRank3], 50, inputtext);
				SendCustomMessage(playerid, "FAMILY", "Kamu telah mengganti nama rank menjadi %s", inputtext);
				Family_Save(pData[playerid][pFamily]);
			}
			case 4:
			{
				format(fData[pData[playerid][pFamily]][fNameRank4], 50, inputtext);
				SendCustomMessage(playerid, "FAMILY", "Kamu telah mengganti nama rank menjadi %s", inputtext);
				Family_Save(pData[playerid][pFamily]);
			}
			case 5:
			{
				format(fData[pData[playerid][pFamily]][fNameRank5], 50, inputtext);
				SendCustomMessage(playerid, "FAMILY", "Kamu telah mengganti nama rank menjadi %s", inputtext);
				Family_Save(pData[playerid][pFamily]);
			}
			case 6:
			{
				format(fData[pData[playerid][pFamily]][fNameRank6], 50, inputtext);
				SendCustomMessage(playerid, "FAMILY", "Kamu telah mengganti nama rank menjadi %s", inputtext);
				Family_Save(pData[playerid][pFamily]);
			}
		}
		DeletePVar(playerid, "FamilyRank");
    }
	return 1;
}

Dialog:VehicleFamily(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new bid = pData[playerid][pFamily];
		switch(listitem)
		{
			case 0:
			{
				if(fData[bid][fVehicleModel][0] != 0) Dialog_Show(playerid, VehicleFamilySell, DIALOG_STYLE_LIST, "Family Vehicle:", "Sell Vehicle", "Select", "Back");
				else ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_FVEHICLE, "Family Vehicle:", familyvehicle, sizeof(familyvehicle));
			}
			case 1:
			{
				if(fData[bid][fVehicleModel][1] != 0) Dialog_Show(playerid, VehicleFamilySell, DIALOG_STYLE_LIST, "Family Vehicle:", "Sell Vehicle", "Select", "Back");
				else ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_FVEHICLE, "Family Vehicle:", familyvehicle, sizeof(familyvehicle));
			}
			case 2:
			{
				if(fData[bid][fVehicleModel][2] != 0) Dialog_Show(playerid, VehicleFamilySell, DIALOG_STYLE_LIST, "Family Vehicle:", "Sell Vehicle", "Select", "Back");
				else ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_FVEHICLE, "Family Vehicle:", familyvehicle, sizeof(familyvehicle));
			}
			case 3:
			{
				if(fData[bid][fVehicleModel][3] != 0) Dialog_Show(playerid, VehicleFamilySell, DIALOG_STYLE_LIST, "Family Vehicle:", "Sell Vehicle", "Select", "Back");
				else ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_FVEHICLE, "Family Vehicle:", familyvehicle, sizeof(familyvehicle));
			}
			case 4:
			{
				if(fData[bid][fVehicleModel][4] != 0) Dialog_Show(playerid, VehicleFamilySell, DIALOG_STYLE_LIST, "Family Vehicle:", "Sell Vehicle", "Select", "Back");
				else ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_FVEHICLE, "Family Vehicle:", familyvehicle, sizeof(familyvehicle));
			}
		}
    }
	return 1;
}

Dialog:VehicleFamilySell(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				new fid = pData[playerid][pFamily];
				if(fData[fid][fVehicleModel][0] != 0)
				{
					if(IsValidVehicle(fData[fid][fVehicle][0])) DestroyVehicle(fData[fid][fVehicle][0]);
					fData[fid][fVehicleModel][0] = 0;
					fData[fid][fVehicleFuel][0] = 0;
					fData[fid][fVehicleHealth][0] = 0;
					fData[fid][fVehiclePos][0] = 0;
					fData[fid][fVehiclePos][1] = 0;
					fData[fid][fVehiclePos][2] = 0;
					fData[fid][fVehiclePos][3] = 0;
					Family_Save(fid);
					GivePlayerMoneyEx(playerid, 50000);
					SendCustomMessage(playerid, "FAMILY", "You successfully sold the family vehicle at a price of $500.00");
				}
			}
			case 1:
			{
				new fid = pData[playerid][pFamily];
				if(fData[fid][fVehicleModel][1] != 0)
				{
					if(IsValidVehicle(fData[fid][fVehicle][1])) DestroyVehicle(fData[fid][fVehicle][1]);
					fData[fid][fVehicleModel][1] = 0;
					fData[fid][fVehicleFuel][1] = 0;
					fData[fid][fVehicleHealth][1] = 0;
					fData[fid][fVehiclePos1][0] = 0;
					fData[fid][fVehiclePos1][1] = 0;
					fData[fid][fVehiclePos1][2] = 0;
					fData[fid][fVehiclePos1][3] = 0;
					Family_Save(fid);
					GivePlayerMoneyEx(playerid, 50000);
					SendCustomMessage(playerid, "FAMILY", "You successfully sold the family vehicle at a price of $500.00");
				}
			}
			case 2:
			{
				new fid = pData[playerid][pFamily];
				if(fData[fid][fVehicleModel][2] != 0)
				{
					if(IsValidVehicle(fData[fid][fVehicle][2])) DestroyVehicle(fData[fid][fVehicle][2]);
					fData[fid][fVehicleModel][2] = 0;
					fData[fid][fVehicleFuel][2] = 0;
					fData[fid][fVehicleHealth][2] = 0;
					fData[fid][fVehiclePos2][0] = 0;
					fData[fid][fVehiclePos2][1] = 0;
					fData[fid][fVehiclePos2][2] = 0;
					fData[fid][fVehiclePos2][3] = 0;
					Family_Save(fid);
					GivePlayerMoneyEx(playerid, 50000);
					SendCustomMessage(playerid, "FAMILY", "You successfully sold the family vehicle at a price of $500.00");
				}
			}
			case 3:
			{
				new fid = pData[playerid][pFamily];
				if(fData[fid][fVehicleModel][3] != 0)
				{
					if(IsValidVehicle(fData[fid][fVehicle][3])) DestroyVehicle(fData[fid][fVehicle][3]);
					fData[fid][fVehicleModel][3] = 0;
					fData[fid][fVehicleFuel][3] = 0;
					fData[fid][fVehicleHealth][3] = 0;
					fData[fid][fVehiclePos3][0] = 0;
					fData[fid][fVehiclePos3][1] = 0;
					fData[fid][fVehiclePos3][2] = 0;
					fData[fid][fVehiclePos3][3] = 0;
					Family_Save(fid);
					GivePlayerMoneyEx(playerid, 50000);
					SendCustomMessage(playerid, "FAMILY", "You successfully sold the family vehicle at a price of $500.00");
				}
			}
			case 4:
			{
				new fid = pData[playerid][pFamily];
				if(fData[fid][fVehicleModel][4] != 0)
				{
					if(IsValidVehicle(fData[fid][fVehicle][4])) DestroyVehicle(fData[fid][fVehicle][4]);
					fData[fid][fVehicleModel][4] = 0;
					fData[fid][fVehicleFuel][4] = 0;
					fData[fid][fVehicleHealth][4] = 0;
					fData[fid][fVehiclePos4][0] = 0;
					fData[fid][fVehiclePos4][1] = 0;
					fData[fid][fVehiclePos4][2] = 0;
					fData[fid][fVehiclePos4][3] = 0;
					Family_Save(fid);
					GivePlayerMoneyEx(playerid, 50000);
					SendCustomMessage(playerid, "FAMILY", "You successfully sold the family vehicle at a price of $500.00");
				}
			}
		}
    }
	return 1;
}
