AddPlayerSalary(playerid, info[], reason[], money)
{
	new query[1245];
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO salary(owner, info, reason, money, date) VALUES ('%d', '%s', '%s', '%d', CURRENT_TIMESTAMP())", pData[playerid][pID], info, reason, money);
	mysql_tquery(g_SQL, query);
	return true;
}

DisplaySalary(playerid)
{
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM salary WHERE owner='%d' ORDER BY id ASC LIMIT 100", pData[playerid][pID]);
	mysql_query(g_SQL, query);
	new rows = cache_num_rows();
	if(rows) 
	{
		new list[5000], listfirst[515], date[30], info[46], reason[124], money, totalsal, total;
		format(listfirst, sizeof(listfirst), "Date\tIssuer\tAmount\tReason\n");
		for(new i; i < rows; ++i)
	    {
			cache_get_value_name(i, "info", info);
			cache_get_value_name(i, "date", date);
			cache_get_value_name_int(i, "money", money);
			cache_get_value_name(i, "reason", reason);
			
			format(list, sizeof(list), "%s"WHITE_E"%s\t%s\t$%s\t%s\n", list, date, info, FormatMoney(money), reason);
			totalsal += money;
		}
		total = totalsal;
		format(list, sizeof(list), "%sGrand Total:\t\t\t"LG_E"$%s\n%s", listfirst, FormatMoney(total), list);
		
		new title[48];
		format(title, sizeof(title), "Pending Salary");
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Close", "");
	}
	else return Error(playerid, "You don't have a pending salary");
	return 1;
}


DisplayPaycheck(playerid)
{
	if(pData[playerid][pPaycheck] <= 3600) return Error(playerid, "Sekarang belum waktunya anda mengambil paycheck.");
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM salary WHERE owner='%d' ORDER BY id ASC LIMIT 100", pData[playerid][pID]);
	mysql_query(g_SQL, query);
	new rows = cache_num_rows();
	if(rows) 
	{
		new money, total, pajak, taxvehicle, taxhouse, taxbisnis, hasil, jumlahkendaraan, jumlahbisnis, jumlahrumah;
		for(new i; i < rows; ++i)
		{
			cache_get_value_name_int(i, "money", money);
			total += money;
		}
		foreach(new vehicleid : PVehicles) if(pvData[vehicleid][cOwner] == pData[playerid][pID] && pvData[vehicleid][cClaim] == 0 && pvData[vehicleid][cImpound] == 0) jumlahkendaraan++;
		taxvehicle = jumlahkendaraan*500;
		foreach (new i : Houses) if(Player_OwnsHouse(playerid, i)) jumlahrumah++;
		foreach (new i : FlatRooms) if (FlatRoom_IsOwner(playerid, i)) jumlahrumah++;
		taxhouse = jumlahrumah*780;
		foreach(new i : Bisnis) if(Player_OwnsBisnis(playerid, i)) jumlahbisnis++;
		foreach(new i : Workshop) if(OwnerWorkshop(playerid, i)) jumlahbisnis++;
		foreach (new i : FurnStore) if (FurnStore_IsOwner(playerid, i)) jumlahbisnis++;
		foreach(new i : Dealership) if(IsPlayerOwnerOfCDEx(playerid, i)) jumlahbisnis++;

		taxbisnis = jumlahbisnis*1000;
		pajak = taxbisnis+taxhouse+taxvehicle;
		hasil = total - pajak;
		SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}<====================< "WHITE_E"Paycheck #%d {00FFFF}>====================>", pData[playerid][pPaycheck]);
		SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}=> "WHITE_E"Bank interest: {00FF00}$%s", FormatMoney(total));
		SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}=> "WHITE_E"Income Tax: {FF0000}$%s", FormatMoney(pajak));
		pData[playerid][pBankMoney] += hasil;
		SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}=> "WHITE_E"New Balance: {00FF00}$%s", FormatMoney(pData[playerid][pBankMoney]));
		SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}<====================================================>");
		Server_MinMoney(hasil);
		pData[playerid][pPaycheck] = 0;
		pData[playerid][pOnDutyTime] = 0;
		pData[playerid][pTaxiTime] = 0;
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM salary WHERE owner='%d'", pData[playerid][pID]);
		mysql_query(g_SQL, query);
	}
	else
	{
		new total, pajak, taxvehicle, taxhouse, taxbisnis, hasil, jumlahkendaraan, jumlahbisnis, jumlahrumah;
		foreach(new vehicleid : PVehicles) if(pvData[vehicleid][cOwner] == pData[playerid][pID] && pvData[vehicleid][cClaim] == 0 && pvData[vehicleid][cImpound] == 0) jumlahkendaraan++;
		taxvehicle = jumlahkendaraan*500;
		foreach (new i : Houses) if(Player_OwnsHouse(playerid, i)) jumlahrumah++;
		foreach (new i : FlatRooms) if (FlatRoom_IsOwner(playerid, i)) jumlahrumah++;
		taxhouse = jumlahrumah*780;
		foreach(new i : Bisnis) if(Player_OwnsBisnis(playerid, i)) jumlahbisnis++;
		foreach(new i : Workshop) if(OwnerWorkshop(playerid, i)) jumlahbisnis++;
		foreach (new i : FurnStore) if (FurnStore_IsOwner(playerid, i)) jumlahbisnis++;
		foreach(new i : Dealership) if(IsPlayerOwnerOfCDEx(playerid, i)) jumlahbisnis++;

		taxbisnis = jumlahbisnis*1000;
		pajak = taxbisnis+taxhouse+taxvehicle;
		hasil = total - pajak;
		SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}<====================< "WHITE_E"Paycheck {00FFFF}>====================>");
		SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}=> "WHITE_E"Bank interest: {00FF00}$%s", FormatMoney(total));
		SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}=> "WHITE_E"Income Tax: {FF0000}$%s", FormatMoney(pajak));
		pData[playerid][pBankMoney] += hasil;
		SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}=> "WHITE_E"New Balance: {00FF00}$%s", FormatMoney(pData[playerid][pBankMoney]));
		SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}<====================================================>");
		Server_MinMoney(hasil);
		pData[playerid][pPaycheck] = 0;
		pData[playerid][pOnDutyTime] = 0;
		pData[playerid][pTaxiTime] = 0;
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM salary WHERE owner='%d'", pData[playerid][pID]);
		mysql_query(g_SQL, query);
	}
	return 1;
}
