
Dialog:DialogReport(playerid, response, listitem, inputtext[]) 
{
	if(response) 
	{
		new i = ListItemReportId[playerid][listitem];
		if(pData[playerid][pAdmin] < 1)
			if(pData[playerid][pHelper] == 0)
				return PermissionError(playerid);
		new String[212];
		
		format(String, sizeof(String), ""YELLOW_E"[RESPOND]{F4F0CA}[%d] "RED_E"%s {F4F0CA}has responded to "YELLOW_E"%s"WHITE_E"{F4F0CA}'s report", Reports[i][ReportFrom], pData[playerid][pAdminname], ReturnName(Reports[i][ReportFrom]));
		SendStaffMessage(COLOR_YELLOW, String, 1);
		SendClientMessageEx(playerid, COLOR_ARWIN, "RESPOND: {FF0000}%s", Reports[i][Report]);
		format(String, sizeof(String), "RESPOND: {FF0000}%s "YELLOW_E"has responded to your report", pData[playerid][pAdminname]);
		SendClientMessageEx(Reports[i][ReportFrom], COLOR_ARWIN, String);
		Reports[i][BeingUsed] = 0;
		Reports[i][ReportFrom] = 999;
		Reports[i][CheckingReport] = 999;
		Reports[i][CheckingReport] = playerid;
		Reports[i][BeingUsed] = 0;
		Reports[i][TimeToExpire] = 0;
		Reports[i][ReportHour] = Reports[i][ReportMinutes] = Reports[i][ReportSecond] = 0;
		strmid(Reports[i][Report], "None", 0, 4, 4);
	}
	return 1;
}