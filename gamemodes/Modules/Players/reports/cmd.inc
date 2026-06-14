
CMD:report(playerid, params[])
{
	if(pData[playerid][pReportTime] > 0)
	{
		Error(playerid,"Wait 120 seconds before sending another report!");
		return 1;
	}

	if(isnull(params)) return Usage(playerid, "/report [text]");

	pData[playerid][pReportTime] = 120;
	SendReportToQue(playerid, params);
	SendClientMessageEx(playerid, COLOR_ARWIN, "REPORT: {ffffff}Your report has been issued to the queue, use '{ffff00}/reports{ffffff}' to see your report");
	return 1;
}

CMD:reports(playerid, params[])
{
	new reportdialog[1000], itemid = 0;
	format(reportdialog, sizeof(reportdialog), "Reporter\tTime\tMessage\n");
	for(new i; i < MAX_REPORTS; ++i)
	{
		if(Reports[i][BeingUsed] == 1 && itemid < 40)
		{
			ListItemReportId[playerid][itemid] = i;
			itemid++;
			format(reportdialog, sizeof(reportdialog), "%sP%d: "YELLOW_E"%s"WHITE_E"\t%d:%d:%d\t%s", reportdialog, Reports[i][ReportFrom], ReturnName(Reports[i][ReportFrom]), Reports[i][ReportHour], Reports[i][ReportMinutes], Reports[i][ReportSecond], (Reports[i][Report]));
			format(reportdialog, sizeof(reportdialog), "%s\n", reportdialog);
		}
	}
	CancelReport[playerid] = itemid;
	format(reportdialog, sizeof(reportdialog), "%s", reportdialog);
	Dialog_Show(playerid, DialogReport, DIALOG_STYLE_TABLIST_HEADERS, "Report Queue", reportdialog, "Respond", "Close");
	return 1;
}

CMD:ar(playerid, params[])
{
	if(pData[playerid][pAdmin] >= 1)
	{
		new String[212], reportid;
		if(sscanf(params, "d", reportid)) return Usage(playerid, "/ar [reportid]");
		if(reportid < 0 || reportid > 999) { Error(playerid, "Report ID not below 0 or above 999!"); return 1; }
		if(Reports[reportid][BeingUsed] == 0) return Error(playerid, "That report ID is not being used!");
		if(!IsPlayerConnected(Reports[reportid][ReportFrom]))
		{
			Error(playerid, "The reporter has disconnected !");
			Reports[reportid][ReportFrom] = 999;
			Reports[reportid][BeingUsed] = 0;
			return 1;
		}
		format(String, sizeof(String), ""YELLOW_E"[RESPOND]{F4F0CA}[%d] "RED_E"%s {F4F0CA}has responded to "YELLOW_E"%s"WHITE_E"{F4F0CA}'s report", Reports[reportid][ReportFrom], pData[playerid][pAdminname], ReturnName(Reports[reportid][ReportFrom]));
		SendStaffMessage(COLOR_YELLOW, String, 1);
		format(String, sizeof(String), "RESPOND: {FF0000}%s {FFFFFF}has responded to your report", pData[playerid][pAdminname]);
		SendClientMessageEx(Reports[reportid][ReportFrom], COLOR_ARWIN, String);
	    Reports[reportid][BeingUsed] = 0;
		Reports[reportid][ReportFrom] = 999;
	    Reports[reportid][CheckingReport] = 999;
		Reports[reportid][CheckingReport] = playerid;
		Reports[reportid][BeingUsed] = 0;
		Reports[reportid][TimeToExpire] = 0;
		strmid(Reports[reportid][Report], "None", 0, 4, 4);
	}
	return 1;
}

CMD:dr(playerid, params[])
{
	if(pData[playerid][pAdmin] >= 1)
	{
		new string[212], reportid;
		if(sscanf(params, "d", reportid)) return Usage(playerid, "/dr [reportid]");

		if(reportid < 0 || reportid > 999) { Error(playerid, "Report ID not below 0 or above 999!"); return 1; }
		if(Reports[reportid][BeingUsed] == 0) return Error(playerid, "That report ID is not being used!");
		if(!IsPlayerConnected(Reports[reportid][ReportFrom]))
		{
			Error(playerid, "The reporter has disconnected !");
			Reports[reportid][ReportFrom] = 999;
			Reports[reportid][BeingUsed] = 0;
			return 1;
		}
		format(string, sizeof(string), "[RESPOND]{F4F0CA}[%d] "RED_E"%s has denied to "YELLOW_E"%s"WHITE_E"{F4F0CA}'s report", Reports[reportid][ReportFrom], pData[playerid][pAdminname], ReturnName(Reports[reportid][ReportFrom]));
		SendStaffMessage(COLOR_YELLOW, string, 1);
		Reports[reportid][ReportFrom] = 999;
		Reports[reportid][BeingUsed] = 0;
		Reports[reportid][TimeToExpire] = 0;
		strmid(Reports[reportid][Report], "None", 0, 4, 4);
	}
	return 1;
}

CMD:clearallreports(playerid, params[])
{
    if (pData[playerid][pAdmin] >= 5) {
        new String[212];
        ClearReports();
        SendClientMessageEx(playerid,COLOR_GRAD1, "You have cleared all the active reports.");
        format(String, sizeof(String), "{FF6347}AdmCmd: %s has cleared all the pending reports.", pData[playerid][pAdminname]);
        SendStaffMessage(TOMATO, String, 2);
    }
    else {
        Error(playerid, "You don't have the privilege to use this command!");
    }
    return 1;
}
