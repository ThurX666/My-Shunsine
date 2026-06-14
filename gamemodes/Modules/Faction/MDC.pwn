
CMD:mdc(playerid, params[])
{
    if(pData[playerid][pFaction] != 1)
        return Error(playerid, "You must be a police officer.");

    if(pData[playerid][pOnDuty] <= 0)
        return Error(playerid, "You must be on-duty");

    if(pData[playerid][pFaction] == 1 && pData[playerid][pOnDuty] == 1)
    {
        Dialog_Show(playerid, DialogMDCSAPD, DIALOG_STYLE_LIST, "Mobile Data Computer", "Quick Scan Nearest Vehicle\nName search\nPlate number search\nPhone number search", "Select", "Cancel");
    }
    return 1;
}

Dialog:DialogMDCSAPD(playerid, response, listitem, inputtext[])
{
	if (response)
	{
        switch(listitem)
        {
            case 0:
            {
                // Quick Scan Nearest Vehicle - otomatis lacak plate + no HP dari driver/passenger
                new vehicleid = GetNearestVehicleToPlayer(playerid, 5.0, false);
                if(vehicleid == INVALID_VEHICLE_ID)
                    return Error(playerid, "Tidak ada kendaraan di dekat Anda.");

                new plate[32], foundOwner = -1, foundDriver = INVALID_PLAYER_ID;
                plate[0] = EOS;

                // Cari owner kendaraan dari database PVehicles
                foreach(new ii : PVehicles)
                {
                    if(vehicleid == pvData[ii][cVeh])
                    {
                        format(plate, sizeof(plate), "%s", pvData[ii][cPlate]);
                        foundOwner = pvData[ii][cOwner];
                        break;
                    }
                }

                // Cari driver kendaraan
                foreach(new i : Player)
                {
                    if(GetPlayerVehicleID(i) == vehicleid && GetPlayerState(i) == PLAYER_STATE_DRIVER)
                    {
                        foundDriver = i;
                        break;
                    }
                }

                new string[1024];
                format(string, sizeof(string), ""WHITE_E"[MDC: Quick Scan Result]\n\n");
                format(string, sizeof(string), "%s"WHITE_E"Vehicle ID: "YELLOW_E"%d\n", string, vehicleid);
                format(string, sizeof(string), "%s"WHITE_E"Model: "YELLOW_E"%s\n", string, GetVehicleName(vehicleid));

                if(plate[0] != EOS)
                    format(string, sizeof(string), "%s"WHITE_E"Plate: "YELLOW_E"%s\n", string, plate);
                else
                    format(string, sizeof(string), "%s"WHITE_E"Plate: "RED_E"NoHave\n", string);

                if(foundOwner != -1)
                    format(string, sizeof(string), "%s"WHITE_E"Owner PID: "YELLOW_E"%d\n", string, foundOwner);

                if(foundDriver != INVALID_PLAYER_ID)
                {
                    format(string, sizeof(string), "%s"WHITE_E"Driver: "YELLOW_E"%s (ID: %d)\n", string, ReturnName2(foundDriver), foundDriver);
                    if(pData[foundDriver][pPhone] > 0)
                    {
                        if(pData[foundDriver][pPhoneOff] > 0)
                            format(string, sizeof(string), "%s"WHITE_E"Phone: "RED_E"%d (OFF)\n", string, pData[foundDriver][pPhone]);
                        else
                            format(string, sizeof(string), "%s"WHITE_E"Phone: "GREEN_E"%d (ON)\n", string, pData[foundDriver][pPhone]);
                    }
                    else
                        format(string, sizeof(string), "%s"WHITE_E"Phone: "GREY_E"None\n", string);
                }
                else
                    format(string, sizeof(string), "%s"WHITE_E"Driver: "GREY_E"Tidak ada driver\n", string);

                // List semua player di dalam kendaraan (passengers)
                format(string, sizeof(string), "%s\n"WHITE_E"Passengers:\n", string);
                new pCount = 0;
                foreach(new i : Player)
                {
                    if(GetPlayerVehicleID(i) == vehicleid && GetPlayerState(i) == PLAYER_STATE_PASSENGER)
                    {
                        pCount++;
                        format(string, sizeof(string), "%s"YELLOW_E" - %s (ID: %d) | HP: ", string, ReturnName2(i), i);
                        if(pData[i][pPhone] > 0)
                        {
                            if(pData[i][pPhoneOff] > 0)
                                format(string, sizeof(string), "%s"RED_E"%d (OFF)\n", string, pData[i][pPhone]);
                            else
                                format(string, sizeof(string), "%s"GREEN_E"%d (ON)\n", string, pData[i][pPhone]);
                        }
                        else
                            format(string, sizeof(string), "%s"GREY_E"None\n", string);
                    }
                }
                if(pCount == 0)
                    format(string, sizeof(string), "%s"GREY_E"Tidak ada penumpang.\n", string);

                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "MDC: Quick Scan", string, "Close", "");
            }
            case 1:
            {
                Dialog_Show(playerid, DialogMDCSearchName, DIALOG_STYLE_INPUT, "MDC: Search name", "Please input player name:", "Search", "back");
            }
            case 2:
            {
                Dialog_Show(playerid, DialogMDCSearchPlate, DIALOG_STYLE_INPUT, "MDC: Search plate", "Please input plate number:", "Search", "back");
            }
            case 3:
            {
                Dialog_Show(playerid, DialogMDCSearchPhone, DIALOG_STYLE_INPUT, "MDC: Search phone", "Please input phone number:", "Search", "back");
            }
        }
    }
    return 1;
}

Dialog:DialogMDCSearchPlate(playerid, response, listitem, inputtext[])
{
	if (response)  return callcmd::traceplate(playerid, inputtext);
    else Dialog_Show(playerid, DialogMDCSAPD, DIALOG_STYLE_LIST, "Mobile Data Computer", "Quick Scan Nearest Vehicle\nName search\nPlate number search\nPhone number search", "Select", "Cancel");
    return 1;
}

Dialog:DialogMDCSearchPhone(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        new no;
        if(sscanf(inputtext, "d", no))
        {
            SendClientMessageEx(playerid, COLOR_GREY, "MDC: "WHITE_E"Format nomor telepon salah.");
            return 1;
        }

        // Cari player dengan nomor HP tersebut
        new found = 0, foundid = INVALID_PLAYER_ID;
        foreach(new id : Player)
        {
            if(pData[id][pPhone] == no)
            {
                found = 1;
                foundid = id;
                break;
            }
        }

        if(!found)
        {
            SendClientMessageEx(playerid, COLOR_GREY, "MDC: "WHITE_E"Tidak ada data dengan nomor telepon %d.", no);
        }
        else
        {
            // Set GPS ke lokasi player
            new Float:pz[3];
            GetPlayerPos(foundid, pz[0], pz[1], pz[2]);
            SetPlayerGPS(playerid, pz[0], pz[1], pz[2]);

            new msg[256];
            format(msg, sizeof(msg), ""WHITE_E"[MDC: Phone Lookup Result]\n\n");
            format(msg, sizeof(msg), "%s"WHITE_E"Name: "YELLOW_E"%s\n", msg, ReturnName2(foundid));
            format(msg, sizeof(msg), "%s"WHITE_E"Phone: "YELLOW_E"%d\n", msg, pData[foundid][pPhone]);
            if(pData[foundid][pPhoneOff] > 0)
                format(msg, sizeof(msg), "%s"WHITE_E"Status: "RED_E"OFF\n", msg);
            else
                format(msg, sizeof(msg), "%s"WHITE_E"Status: "GREEN_E"ON\n", msg);
            format(msg, sizeof(msg), "%s"WHITE_E"Location: "YELLOW_E"%s", msg, GetLocation(pz[0], pz[1], pz[2]));

            ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "MDC: Phone Lookup", msg, "Close", "");
            SendClientMessageEx(playerid, COLOR_ARWIN, "TRACE: "YELLOW_E"Phone target berhasil ditemukan, marker ada di radar Anda.");
        }
    }
    else Dialog_Show(playerid, DialogMDCSAPD, DIALOG_STYLE_LIST, "Mobile Data Computer", "Quick Scan Nearest Vehicle\nName search\nPlate number search\nPhone number search", "Select", "Cancel");
    return 1;
}

Dialog:DialogMDCSearchName(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        // Cari player berdasarkan nama
        new otherid = INVALID_PLAYER_ID;
        foreach(new i : Player)
        {
            if(strfind(pData[i][pName], inputtext, true) != -1)
            {
                otherid = i;
                break;
            }
        }

        if(otherid == INVALID_PLAYER_ID)
            return Error(playerid, "Data of people with that name is not found!");

        SetPVarInt(playerid, "MDCotherid", otherid);
        new plate[62];
        format(plate, sizeof(plate), "MDC: Personal Data (%s)", pData[otherid][pName]);
        Dialog_Show(playerid, DialogMDCNameData, DIALOG_STYLE_LIST, plate, "Arrest Record\nCrime Record", "Search", "back");
    }
    else Dialog_Show(playerid, DialogMDCSAPD, DIALOG_STYLE_LIST, "Mobile Data Computer", "Quick Scan Nearest Vehicle\nName search\nPlate number search\nPhone number search", "Select", "Cancel");
    return 1;
}


Dialog:DialogMDCNameData(playerid, response, listitem, inputtext[])
{
	if (response)
	{
        switch(listitem)
        {
            case 0:
            {
                new id = GetPVarInt(playerid, "MDCotherid");
                ShowArrestRecord(playerid, id);
            }
            case 1:
            {
                new id = GetPVarInt(playerid, "MDCotherid");
                ShowCrimeRecord(playerid, id);
            }
        }
    }
	else
	{
        new otherid = GetPVarInt(playerid, "MDCotherid");
        new plate[62];
        format(plate, sizeof(plate), "MDC: Personal Data (%s)", pData[otherid][pName]);
        Dialog_Show(playerid, DialogMDCNameData, DIALOG_STYLE_LIST, plate, "Arrest Record\nCrime Record", "Search", "back");
    }
	return 1;
}

ShowCrimeRecord(playerid, targetid)
{
	new query[512], list[1128], msg[1012], nameissued[52], date[128];
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM crimerecord WHERE owner = '%d' ORDER BY id ASC", pData[targetid][pID]);
	mysql_query(g_SQL, query);
	new rows = cache_num_rows();
	if(rows)
	{
		format(list, sizeof(list), "Date\tName\tCharge description\tIssued By\n");
		for(new i = 0; i < rows; i++)
		{
            cache_get_value_name(i, "date", date);
			cache_get_value_name(i, "reason", msg);
            cache_get_value_name(i, "issue", nameissued);
			format(list, sizeof(list), "%s%s\t"YELLOW_E"%s\t"PINK_E"%s\t"BLUE_E"%s\n", list, date, pData[playerid][pName], msg, nameissued);
		}
		Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Crime Record:", list, "Close", "");
	}
	return 1;
}

ShowArrestRecord(playerid, targetid)
{
	new query[512], list[1128], msg[1012], nameissued[52], date[128], fine;
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM arrestrecord WHERE owner = '%d' ORDER BY id ASC", pData[targetid][pID]);
	mysql_query(g_SQL, query);
	new rows = cache_num_rows();
	if(rows)
	{
		format(list, sizeof(list), "Date\tName\tCharge description\tIssued By\tFine\n");
		for(new i = 0; i < rows; i++)
		{
            cache_get_value_name(i, "date", date);
            cache_get_value_name(i, "issued", nameissued);
			cache_get_value_name(i, "reason", msg);
            cache_get_value_name_int(i, "fine", fine);
			format(list, sizeof(list), "%s%s\t"YELLOW_E"%s\t"PINK_E"%s\t"BLUE_E"%s\t"GREEN_E"$%s\n", list, date, pData[playerid][pName], msg, nameissued, FormatMoney(fine));
		}
		Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Arrest Record:", list, "Close", "");
	}
	return 1;
}
