new fmQueue[MAX_PLAYERS] = {0, ...};
CMD:factionmanage(playerid) {
	new str[512];
	if(pData[playerid][pFaction] == 1) {
		format(str, sizeof(str), "History Balance\nWithdraw Balance\t$%s\nRestock Armoury\nRestock Ammo-JHP", FormatMoney(BalanceSAPD));
		Dialog_Show(playerid, FactionManage, DIALOG_STYLE_LIST, "San Andreas Police", str, "Select", "Cancel");
	}
	else if(pData[playerid][pFaction] == 2)
	{
		format(str, sizeof(str), "History Balance\nWithdraw Balance\t$%s", FormatMoney(BalanceSAGS));
		Dialog_Show(playerid, FactionManage, DIALOG_STYLE_LIST, "San Andreas Goverment", str, "Select", "Cancel");
	}
	else if(pData[playerid][pFaction] == 3)
	{
		format(str, sizeof(str), "History Balance\nWithdraw Balance\t$%s", FormatMoney(BalanceSAMD));
		Dialog_Show(playerid, FactionManage, DIALOG_STYLE_LIST, "San Andreas Medical", str, "Select", "Cancel");
	}
	else if(pData[playerid][pFaction] == 4)
	{
		format(str, sizeof(str), "History Balance\nWithdraw Balance\t$%s", FormatMoney(BalanceSAN));
		Dialog_Show(playerid, FactionManage, DIALOG_STYLE_LIST, "San Andreas Network", str, "Select", "Cancel");
	}
	else return Error(playerid, "Anda tidak bergabung dalam faction!");
	return 1;
}

Dialog:FactionManageNext(playerid, response, listitem, inputtext[]) {
    if (response) {
        new
            Cache:query;

        fmQueue[playerid]++;
        query = mysql_query(g_SQL, sprintf("SELECT * FROM `factionmanage` WHERE factionid = '%d' LIMIT %d, 10", pData[playerid][pFaction], fmQueue[playerid] * 10));

        new rows = cache_num_rows(), list[512], msg[512], nameissued[52], date[128];

        if (rows) {
            format(list, sizeof(list), "Description\tDate\tAmount\n");
            for(new i = 0; i < rows; i++)
            {
                cache_get_value_name(i, "date", date);
                cache_get_value_name(i, "reason", msg);
                cache_get_value_name(i, "ammount", nameissued);
                format(list, sizeof(list), "%s%s\t%s\t"GREEN_E"$%s\n", list, msg, date, nameissued);
            }
            switch(pData[playerid][pFaction]) {
                case 1: format(list, sizeof(list), "%sBalance:\t"GREEN_E"$%s\n", list, FormatMoney(BalanceSAPD));
                case 2: format(list, sizeof(list), "%sBalance:\t"GREEN_E"$%s\n", list, FormatMoney(BalanceSAGS));
                case 3: format(list, sizeof(list), "%sBalance:\t"GREEN_E"$%s\n", list, FormatMoney(BalanceSAMD));
                case 4: format(list, sizeof(list), "%sBalance:\t"GREEN_E"$%s\n", list, FormatMoney(BalanceSAN));
            }
            Dialog_Show(playerid, FactionManageNext, DIALOG_STYLE_TABLIST_HEADERS, "History Balance:", list, "Close", "");
        } else Error(playerid, "Tidak ada history!");
        cache_delete(query);
    }
    else fmQueue[playerid] = 0;
    return 1;
}

Dialog:FactionManage(playerid, response, listitem, inputtext[]) {
    if (response) {
        switch(listitem) {
            case 0: {
                new query[512], list[512], msg[512], nameissued[52], date[128];
                mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM factionmanage WHERE factionid = '%d' ORDER BY id ASC", pData[playerid][pFaction]);
                mysql_query(g_SQL, query);
                new rows = cache_num_rows();
                if(rows)
                {
                    format(list, sizeof(list), "Description\tDate\tAmount\n");
                    for(new i = 0; i < rows; i++)
                    {
                        cache_get_value_name(i, "date", date);
                        cache_get_value_name(i, "reason", msg);
                        cache_get_value_name(i, "ammount", nameissued);
                        format(list, sizeof(list), "%s%s\t%s\t"GREEN_E"$%s\n", list, msg, date, nameissued);
                    }
                    switch(pData[playerid][pFaction]) {
                        case 1: format(list, sizeof(list), "%sBalance:\t"GREEN_E"$%s\n", list, FormatMoney(BalanceSAPD));
                        case 2: format(list, sizeof(list), "%sBalance:\t"GREEN_E"$%s\n", list, FormatMoney(BalanceSAGS));
                        case 3: format(list, sizeof(list), "%sBalance:\t"GREEN_E"$%s\n", list, FormatMoney(BalanceSAMD));
                        case 4: format(list, sizeof(list), "%sBalance:\t"GREEN_E"$%s\n", list, FormatMoney(BalanceSAN));
                    }
                    Dialog_Show(playerid, FactionManageNext, DIALOG_STYLE_TABLIST_HEADERS, "History Balance:", list, "Next", "Close");
                }
            }
            case 1: {
                if(pData[playerid][pFactionRank] < 5) return Error(playerid, "You must be at least rank 5");
                switch(pData[playerid][pFaction]) {
                    case 1: Dialog_Show(playerid, FactionBalanceWith, DIALOG_STYLE_INPUT, sprintf("Balance Faction: "GREEN_E"$%s", FormatMoney(BalanceSAPD)), "Masukan nominal yang ingin anda ambil:", "Withdraw", "Close");
                    case 2: Dialog_Show(playerid, FactionBalanceWith, DIALOG_STYLE_INPUT, sprintf("Balance Faction: "GREEN_E"$%s", FormatMoney(BalanceSAGS)), "Masukan nominal yang ingin anda ambil:", "Withdraw", "Close");
                    case 3: Dialog_Show(playerid, FactionBalanceWith, DIALOG_STYLE_INPUT, sprintf("Balance Faction: "GREEN_E"$%s", FormatMoney(BalanceSAMD)), "Masukan nominal yang ingin anda ambil:", "Withdraw", "Close");
                    case 4: Dialog_Show(playerid, FactionBalanceWith, DIALOG_STYLE_INPUT, sprintf("Balance Faction: "GREEN_E"$%s", FormatMoney(BalanceSAN)), "Masukan nominal yang ingin anda ambil:", "Withdraw", "Close");
                }
                
            }
            case 2: {
                if(pData[playerid][pFactionRank] < 5) return Error(playerid, "You must be at least rank 5");
                new total = 1000 - SAPDArmoury;
                new totalprice = total*5500;
                new string[502];
                format(string, sizeof(string), ""WHITE_E"Product: "AQUA_E"Armoury\n\
                "WHITE_E"Price: "AQUA_E"$55.00/units\n\
                "WHITE_E"Amount Product: "AQUA_E"%d\n\
                "WHITE_E"Products Price: "AQUA_E"$%s\n\
                "GREEN_E"Confirm Order?", total, FormatMoney(totalprice));
                Dialog_Show(playerid, FactionRestockArmoury, DIALOG_STYLE_MSGBOX, "Restock Order:", string, "Confirm", "Cancel");
            }
            case 3: {
                if(pData[playerid][pFactionRank] < 5) return Error(playerid, "You must be at least rank 5");
                new total = 10000 - SAPDAmmo;
                new totalprice = total*2500;
                new string[502];
                format(string, sizeof(string), ""WHITE_E"Product: "AQUA_E"Ammo-JHP\n\
                "WHITE_E"Price: "AQUA_E"$25.00/units\n\
                "WHITE_E"Amount Product: "AQUA_E"%d\n\
                "WHITE_E"Products Price: "AQUA_E"$%s\n\
                "GREEN_E"Confirm Order?", total, FormatMoney(totalprice));
                Dialog_Show(playerid, FactionRestockAmmo, DIALOG_STYLE_MSGBOX, "Restock Order:", string, "Confirm", "Cancel");
            }
        }
    }
    return 1;
}

Dialog:FactionRestockAmmo(playerid, response, listitem, inputtext[]) {
    if (response) {
        new total = 10000 - SAPDAmmo;
        new totalprice = total*2500;
        new strings[212];
        SAPDAmmo += total;
        BalanceSAPD -= totalprice;
        SendCustomMessage(playerid, "RESTOCK:", "Anda berhasil merestock ammo-JHP dengan jumlah "AQUA_E"%d units "WHITE_E"dengan harga "GREEN_E"$%s", total, FormatMoney(totalprice));
        InsertFactionManage(1, sprintf("Restock Ammo-JHP by %s", pData[playerid][pName]), FormatMoney(totalprice));
        foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
            if(Location[id][locType] == 13 && IsPlayerInRangeOfPoint(playerid, 2.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
                format(strings, sizeof(strings), "[ID: %d]\nSan Andreas Police Department\n"GREEN_E"SAPD Central Armoury\n"WHITE_E"Stock: "YELLOW_E"%d/1000\n"GREEN_E"SAPD Central Ammo\n"WHITE_E"Stock: "YELLOW_E"%d/10000\n"WHITE_E"Use "YELLOW_E"'/armoury' "WHITE_E"to acces armoury\n"WHITE_E"Use "YELLOW_E"'/sapdammo' "WHITE_E"to acces ammo JHP", id, SAPDArmoury, SAPDAmmo);
			    UpdateDynamic3DTextLabelText(Location[id][locLabel], -1, strings);
            } 
        }
        Server_Save();
    }
    return 1;
}

Dialog:FactionRestockArmoury(playerid, response, listitem, inputtext[]) {
    if (response) {
        new total = 1000 - SAPDArmoury;
        new totalprice = total*5500;
        new strings[212];
        SAPDArmoury += total;
        BalanceSAPD -= totalprice;
        SendCustomMessage(playerid, "RESTOCK:", "Anda berhasil merestock armor dengan jumlah "AQUA_E"%d units "WHITE_E"dengan harga "GREEN_E"$%s", total, FormatMoney(totalprice));
        InsertFactionManage(1, sprintf("Restock Armory by %s", pData[playerid][pName]), FormatMoney(totalprice));
        foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
            if(Location[id][locType] == 13 && IsPlayerInRangeOfPoint(playerid, 2.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
                format(strings, sizeof(strings), "[ID: %d]\nSan Andreas Police Department\n"GREEN_E"SAPD Central Armoury\n"WHITE_E"Stock: "YELLOW_E"%d/1000\n"GREEN_E"SAPD Central Ammo\n"WHITE_E"Stock: "YELLOW_E"%d/10000\n"WHITE_E"Use "YELLOW_E"'/armoury' "WHITE_E"to acces armoury\n"WHITE_E"Use "YELLOW_E"'/sapdammo' "WHITE_E"to acces ammo JHP", id, SAPDArmoury, SAPDAmmo);
			    UpdateDynamic3DTextLabelText(Location[id][locLabel], -1, strings);
            } 
        }
        Server_Save();
    }
    return 1;
}

Dialog:FactionBalanceWith(playerid, response, listitem, inputtext[]) {
    if (response) {
        new totalcash[52];
        format(totalcash, sizeof(totalcash), "%d00", strval(inputtext));
        if(strval(totalcash) < 0) return SendClientMessageEx(playerid, COLOR_GREY, "Tidak bisa dibawah $0.00");
        switch(pData[playerid][pFaction]) {
            case 1: {
                if(strval(totalcash) > BalanceSAPD) return SendClientMessageEx(playerid, -1, "ERROR: Anda tidak memiliki uang sebesar itu di dalam Akun ATM anda!");
                GivePlayerMoneyEx(playerid, strval(totalcash));
                BalanceSAPD -= strval(totalcash);
                SendCustomMessage(playerid, "BANKFACTION:", "Anda berhasil mengambil uang sebesar $%s dari bank faction", FormatMoney(strval(totalcash)));
                InsertFactionManage(1, sprintf("Withdraw money by %s", pData[playerid][pName]), totalcash);
            }
            case 2: {
                if(strval(totalcash) > BalanceSAGS) return SendClientMessageEx(playerid, -1, "ERROR: Anda tidak memiliki uang sebesar itu di dalam Akun ATM anda!");
                GivePlayerMoneyEx(playerid, strval(totalcash));
                BalanceSAGS -= strval(totalcash);
                SendCustomMessage(playerid, "BANKFACTION:", "Anda berhasil mengambil uang sebesar $%s dari bank faction", FormatMoney(strval(totalcash)));
                InsertFactionManage(2, sprintf("Withdraw money by %s", pData[playerid][pName]), totalcash);
            }
            case 3: {
                if(strval(totalcash) > BalanceSAMD) return SendClientMessageEx(playerid, -1, "ERROR: Anda tidak memiliki uang sebesar itu di dalam Akun ATM anda!");
                GivePlayerMoneyEx(playerid, strval(totalcash));
                BalanceSAMD -= strval(totalcash);
                SendCustomMessage(playerid, "BANKFACTION:", "Anda berhasil mengambil uang sebesar $%s dari bank faction", FormatMoney(strval(totalcash)));
                InsertFactionManage(3, sprintf("Withdraw money by %s", pData[playerid][pName]), totalcash);
            }
            case 4: {
                if(strval(totalcash) > BalanceSAN) return SendClientMessageEx(playerid, -1, "ERROR: Anda tidak memiliki uang sebesar itu di dalam Akun ATM anda!");
                GivePlayerMoneyEx(playerid, strval(totalcash));
                BalanceSAN -= strval(totalcash);
                SendCustomMessage(playerid, "BANKFACTION:", "Anda berhasil mengambil uang sebesar $%s dari bank faction", FormatMoney(strval(totalcash)));
                InsertFactionManage(4, sprintf("Withdraw money by %s", pData[playerid][pName]), totalcash);
            }
        }
    }
    return 1;
}

InsertFactionManage(factionid, reason[], ammount[])
{
    Server_Save();
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO factionmanage(factionid, reason, ammount, date) VALUES ('%d', '%s', '%s', CURRENT_TIMESTAMP())", factionid, reason, ammount);
	mysql_tquery(g_SQL, query);
	return 1;
}
