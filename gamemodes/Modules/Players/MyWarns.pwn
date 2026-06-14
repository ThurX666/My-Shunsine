AddPlayerWarnsLog(playerid, regid, reason[], type) {
    switch(type) {
        case 1: {
            new query[512];
            mysql_format(g_SQL, query, sizeof(query), "INSERT INTO mywarns(owner, reason, type, issuer, date) VALUES ('%d', '%s', '%d', '%s', CURRENT_TIMESTAMP())", regid, reason, type, pData[playerid][pAdminname]);
            mysql_tquery(g_SQL, query);
        }
        case 2: {
            new query[512];
            mysql_format(g_SQL, query, sizeof(query), "INSERT INTO mywarns(owner, reason, type, issuer, date) VALUES ('%d', '%s', '%d', '%s', CURRENT_TIMESTAMP())", regid, reason, type, pData[playerid][pAdminname]);
            mysql_tquery(g_SQL, query);
        }
    }
    return 1;
}

CMD:mywarns(playerid, params) {
    ShowMyWarns(playerid, playerid);
    return 1;
}

ShowMyWarns(playerid, p2) {
	new query[512], list[1241], msg[212], string[512], issuer[212], date[128], type;
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM mywarns WHERE owner = '%d'", pData[p2][pID]);
	mysql_query(g_SQL, query);
	new rows = cache_num_rows();
    format(string, sizeof(string), "Warns of %s:", pData[p2][pName]);
	if(rows) {
		format(list, sizeof(list), "Type\tIssuer\tIssue Date\tReason\n");
		for(new i = 0; i < rows; i++)
		{
			cache_get_value_name(i, "reason", msg);
            cache_get_value_name(i, "date", date);
            cache_get_value_name(i, "issuer", issuer);
            cache_get_value_name_int(i, "type", type);
            if(type == 1) {
                format(list, sizeof(list), "%s"YELLOW_E"[JAIL]\t%s\t%s\t%s\n", list, issuer, date, msg);
            }
            else if(type == 2) {
                format(list, sizeof(list), "%s"GREEN_E"[WARN]\t%s\t%s\t%s\n", list, issuer, date, msg);
            }
		}
	}
    Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, string, list, "Close", "");
	return 1;
}
