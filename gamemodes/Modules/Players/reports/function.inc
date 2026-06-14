
stock SendReportToQue(reportfrom, report[])
{
    new bool:breakingloop = false, newid = INVALID_REPORT_ID;

	for(new i=0;i<MAX_REPORTS;i++)
	{
		if(!breakingloop)
		{
			if(Reports[i][HasBeenUsed] == 0)
			{
				breakingloop = true;
				newid = i;
			}
		}
    }
    if(newid != INVALID_REPORT_ID)
    {
        strmid(Reports[newid][Report], report, 0, strlen(report), 128);
        Reports[newid][ReportFrom] = reportfrom;
        Reports[newid][TimeToExpire] = 5;
        Reports[newid][HasBeenUsed] = 1;
        Reports[newid][BeingUsed] = 1;
		gettime(Reports[newid][ReportHour], Reports[newid][ReportMinutes], Reports[newid][ReportSecond]);
        Reports[newid][ReportExpireTimer] = SetTimerEx("ReportTimer", 60000, 0, "d", newid);
        SendReportMessage(COLOR_ARWIN, ""YELLOW_E"[REPORT]{F4F0CA}[%d] %s: %s", newid, ReturnName(reportfrom), (report));
    }
    else
    {
        ClearReports();
        SendReportToQue(reportfrom, report);
    }
}

function ClearReports()
{
	for(new i=0;i<MAX_REPORTS;i++)
	{
		strmid(Reports[i][Report], "None", 0, 4, 4);
		Reports[i][CheckingReport] = 999;
        Reports[i][ReportFrom] = 999;
        Reports[i][TimeToExpire] = 5;
        Reports[i][HasBeenUsed] = 0;
        Reports[i][BeingUsed] = 0;
	}
	return 1;
}

function ReportTimer(reportid)
{
	if(Reports[reportid][BeingUsed] == 1)
	{
	    if(Reports[reportid][TimeToExpire] > 0)
	    {
	        Reports[reportid][TimeToExpire]--;
	        if(Reports[reportid][TimeToExpire] == 0)
	        {
	            SendClientMessageEx(Reports[reportid][ReportFrom], COLOR_GRAD2, "Your report has expired. You can attempt to report again if you wish.");
	            Reports[reportid][BeingUsed] = 0;
	            Reports[reportid][ReportFrom] = 999;
	            return 1;
	        }
  			Reports[reportid][ReportExpireTimer] = SetTimerEx("ReportTimer", 60000, 0, "d", reportid);
		}
	}
	return 1;
}

stock SendReportMessage(color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 8)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 8); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player)
        {
            if(pData[i][pAdmin] >= 1 && pData[i][pTogStaffReport] == 0) {
                SendClientMessage(i, color, string);
            }
        }
        return 1;
    }
    foreach (new i : Player)
    {
        if(pData[i][pAdmin] >= 1 && pData[i][pTogStaffReport] == 0) {
            SendClientMessage(i, color, str);
        }
    }
    return 1;
}
