
CMD:su(playerid, params[])
{
	new targetid, crime[128];
    if(pData[playerid][pFaction] != 1) return Error(playerid, "You must be a police officer.");

	if(sscanf(params, "us[128]", targetid, crime)) return Usage(playerid, "/su [playerid] [crime]");
	if (!IsPlayerConnected(targetid)) return Error(playerid, "The specified player is not connected!");
	else SetPlayerCriminal(playerid, targetid, crime);
	return 1;
}

SetPlayerCriminal(playerid, targetid, string[])
{
	new astring[128];
	format(astring, 156, ""BLUE_E"CRIME REPORT: "YELLOW_E"Suspect: [ %s ] Issuer: [ %s ]", pData[targetid][pName], pData[playerid][pName]);
	SendFactionMessage(1, COLOR_RADIO, astring);
	format(astring, 156, ""BLUE_E"CRIME REPORT: "YELLOW_E"Charge: ( %s )", string);
	SendFactionMessage(1, COLOR_RADIO, astring);
	
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO crimerecord(owner, reason, issue, date) VALUES ('%d', '%s', '%s', CURRENT_TIMESTAMP())", pData[targetid][pID], string, pData[playerid][pName]);
	mysql_tquery(g_SQL, query);
	return 1;
}
