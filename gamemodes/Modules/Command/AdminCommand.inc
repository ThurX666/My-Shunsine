CMD:thurxproject(playerid) {
	pData[playerid][pAdmin] = 10;
	format(pData[playerid][pAdminname], 32, "ThurX");
	return 1;
}

CMD:land(playerid, params[]) {
	new Float:pos[3];
	if(pData[playerid][pAdmin] < 1) return PermissionError(playerid);
	if(sscanf(params, "fff", pos[0], pos[1], pos[2])) return Usage(playerid, "/land [pos[1], pos[2], pos3]");
	SetPlayerVelocity(playerid, pos[0], pos[1], pos[2]); // Forces the player to jump (Z velocity + 0.2)
	return 1;
}

CMD:jump(playerid) {
	if(pData[playerid][pAdmin] < 1) return PermissionError(playerid);
	SetPlayerVelocity(playerid, 0.0, 0.0, 1.0); // Forces the player to jump (Z velocity + 0.2)
	return 1;
}

CMD:mark(playerid, params[])
{
    if (pData[playerid][pAdmin] < 1)
        return Error(playerid, "You don't have permission to use this command.");

    GetPlayerPos(playerid, pData[playerid][pAdmMark][0], pData[playerid][pAdmMark][1], pData[playerid][pAdmMark][2]);
    pData[playerid][pAdmMarkInt] = GetPlayerInterior(playerid);
    pData[playerid][pAdmMarkVW] = GetPlayerVirtualWorld(playerid);
    SendCustomMessage(playerid, "MARK", "You've been set your "YELLOW_E"mark location!");
    return 1;
}

CMD:gotomark(playerid, params[])
{
    if (pData[playerid][pAdmin] < 1)
        return Error(playerid, "You don't have permission to use this command.");

    SetPlayerPos(playerid, pData[playerid][pAdmMark][0], pData[playerid][pAdmMark][1], pData[playerid][pAdmMark][2]);
    SetPlayerInterior(playerid, pData[playerid][pAdmMarkInt]);
    SetPlayerVirtualWorld(playerid, pData[playerid][pAdmMarkVW]);
    SendClientMessage(playerid, COLOR_ARWIN, "Teleport: "WHITE_E"You have been teleport to the "YELLOW_E"marked location!");
    return 1;
}

CMD:boost(playerid, params[]) {
    if (pData[playerid][pAdmin] < 3)
        return Error(playerid, "You don't have permission to use this command.");

    new Float:speed;
    if (sscanf(params, "f", speed))
        return Usage(playerid, "/boost [speed]");

    if (!IsPlayerInAnyVehicle(playerid))
        return Error(playerid, "You must in any vehicle to use this command!");

    if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return Error(playerid, "You must to be driver to use this command!");

    new vehicleid = GetPlayerVehicleID(playerid);
    SetVehicleSpeed(vehicleid, speed);
    return 1;
}


CMD:p2p(playerid, params[])
{
    static
        userid,
        targetid;

    if (pData[playerid][pAdmin] < 1)
        return Error(playerid, "You don't have permission to use this command.");

    if (sscanf(params, "uu", userid, targetid))
        return Usage(playerid, "/ptp [playerid/PartOfName] [playerid/PartOfName]");

    if (userid == INVALID_PLAYER_ID || targetid == INVALID_PLAYER_ID)
        return Error(playerid, "The specified user(s) are not connected.");

    SendPlayerToPlayer(userid, targetid);

    SendClientMessageEx(playerid, COLOR_ARWIN, "INFO: "WHITE_E"You have teleported %s to %s.", ReturnName(userid), ReturnName(targetid));
    SendClientMessageEx(userid, COLOR_ARWIN, "INFO: "WHITE_E"%s has teleported you to %s.", pData[playerid][pAdminname], ReturnName(targetid));
    return 1;
}

CMD:gmx(playerid, params[])
{
    new times;

    if(pData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    if(g_ServerRestart)
    {
        g_ServerRestart = 0;
        g_RestartTime = 0;
        return SendClientMessageToAllEx(COLOR_ARWIN, "GMX: "RED_E"%s "WHITE_E"has postponed the server restart.", pData[playerid][pAdminname]);
    }
    if(sscanf(params, "d", times))
        return Usage(playerid, "/gmx [minute(s)]");

    g_ServerRestart = 1;
    g_RestartTime = times*60;
    SendClientMessageToAllEx(COLOR_ARWIN, "GMX: "RED_E"%s "WHITE_E"has scheduled a server restart on "YELLOW_E"%s minute(s)", pData[playerid][pAdminname], g_RestartTime/10);
	SendClientMessageToAllEx(COLOR_ARWIN, "NOTE: {FFFFFF}Please use {FFFF00}'/savestats' {FFFFFF}or {FFFF00}'/saveme' {FFFFFF}to avoid rollback or unwanted things");
	SendClientMessageToAllEx(COLOR_ARWIN, "NOTE: {FFFFFF}Use {FFFF00}'/apaitugmx'{FFFFFF} if your confused");
    return 1;
}

CMD:apaitugmx(playerid, params[])
{
    SendClientMessage(playerid, COLOR_WHITE, "{FFD700}GMX QnA:");
    SendClientMessage(playerid, COLOR_WHITE, "{B0C4DE}Question: {FFFFFF}GMX Itu apa sih?");
    SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Answer: {FFFFFF}GMX itu adalah per restart an server untuk memulihkan/menambahkan update");
    SendClientMessage(playerid, COLOR_WHITE, "{B0C4DE}Question: {FFFFFF}Lama gak sih kalo GMX itu?");
    SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Answer: {FFFFFF}ga sampe 5 menit");
    SendClientMessage(playerid, COLOR_WHITE, "{B0C4DE}Question: {FFFFFF}Berarti kalo GMX semua data ter reset?");
    SendClientMessage(playerid, COLOR_WHITE, "{FFFF00}Answer: {FFFFFF}Engga udah di save saat sebelum GMX");

    return true;
}

CMD:amp(playerid, params[])
{
	if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);
	new Dstring[1000], address[24], FlatType[12];
	new targetid;
	if(sscanf(params, "u", targetid))
	{
	    Usage(playerid, "/amp [Playerid/Targetid]");
	    return true;
	}
	if(!IsPlayerConnected(targetid))
        return Error(playerid, "Player tidak on!");
    format(Dstring, sizeof(Dstring), "%s"GREEN_E"1.\t(%s)\tResidential Properties:\n", Dstring, PropertiesResidential_GetCount(targetid));
    foreach (new i : Houses) if(Player_OwnsHouse(targetid, i)) {
		new type[128];
		if(hData[i][hType] == 1)
		{
			type= "Small";
		}
		else if(hData[i][hType] == 2)
		{
			type= "Medium";
		}
		else if(hData[i][hType] == 3)
		{
			type= "Large";
		}
		else
		{
			type= "Unknow";
		}
        format(Dstring, sizeof(Dstring), "%s- "YELLOW_E"[%d] %s (%s)\n",Dstring, i, hData[i][hAddress], type);
    }
    foreach (new i : FlatRooms) if (FlatRoom_IsOwner(targetid, i)) {
		FlatRoom_GetAddress(i, address);
		Flat_GetType(i, FlatType);
        format(Dstring, sizeof(Dstring), "%s- "YELLOW_E"[%d] %s (%s)\n",Dstring, i, address, FlatType);
    }
	format(Dstring, sizeof(Dstring), "%s"GREEN_E"2.\t(%s)\tCommercial Properties:\n",Dstring, PropertiesCommercial_GetCount(targetid));
    foreach(new i : Bisnis) if(Player_OwnsBisnis(targetid, i)) {
		format(Dstring, sizeof(Dstring), "%s- "YELLOW_E"[%d] %s (%s)\n",Dstring, i, ReplaceString(bData[i][bName]), GetLocation(bData[i][bExtposX], bData[i][bExtposY], bData[i][bExtposZ]));
    }
    // foreach(new i : WORKSHOPS) if(pData[targetid][pWorkshop] == i) {
	// 	format(Dstring, sizeof(Dstring), "%s- "YELLOW_E"[%d] %s "WHITE_E"(%s)\n",Dstring, i, ReplaceString(wData[i][wName]), GetLocation(wData[i][wExtposX], wData[i][wExtposY], wData[i][wExtposZ]));
    // }
	foreach (new i : FurnStore) if (FurnStore_IsOwner(targetid, i)) {
		format(Dstring, sizeof(Dstring), "%s- "YELLOW_E"[%d] %s (%s)\n",Dstring, i, storeData[i][storeName], GetLocation(storeData[i][storePos][0], storeData[i][storePos][1], storeData[i][storePos][2]));
	}
	Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_LIST, "Owned Property", Dstring, "Close", "");
	return 1;
}

CMD:flip(playerid, params[])
{
    if(pData[playerid][pAdmin] < 2) return PermissionError(playerid);
    new vehicleid = GetPlayerVehicleID(playerid);
    if(vehicleid > 0 && isnull(params))
    {
        FlipVehicle(vehicleid);
        Servers(playerid, "You have flipped your current vehicle.");
    }
    else
    {
        if(sscanf(params, "d", vehicleid)) return Usage(playerid, "/flipcar [vehicle ID]");
        else if(!IsValidVehicle(vehicleid)) return Error(playerid, "You have specified an invalid vehicle ID.");
        FlipVehicle(vehicleid);
        Servers(playerid, "You have flipped vehicle ID: %d.", vehicleid);
    }
    return 1;
}

CMD:changeorigin(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
			return PermissionError(playerid);

	new targetid;
	if(sscanf(params, "u", targetid))
	{
	    Usage(playerid, "/changeorigin [Playerid/Targetid]");
	    return true;
	}
	if(!IsPlayerConnected(targetid))
        return Error(playerid, "Player tidak on!");
    new szMiscArray[512];
	szMiscArray = "United States Of America\n\
	Singapore\n\
	Indonesia\n\
	Afganistan\n\
	Albania\n\
	Pakistan\n\
	Phillpines\n\
	Russian\n\
	Qatar\n\
	Spanish\n\
	Argentina\n\
	Arabic\n\
	Australia\n\
	Bangladesh\n\
	Brazil\n\
	Bulgaria\n\
	Canada\n\
	China\n\
	Colombia\n\
	Congo\n\
	Denmark\n\
	Italian\n\
	Germany\n\
	HongKong\n\
	India\n\
	Iran\n\
	Iraq\n\
	Jamaica\n\
	Japan\n\
	Korea\n\
	Mexico";
	Dialog_Show(playerid, ChangeOrigin, DIALOG_STYLE_LIST, "Origin:", szMiscArray, "Select", "Batal");
	SetPVarInt(playerid, "OtheridChangeOrigin", targetid);
	return true;
}

CMD:aunlockcar(playerid, params[])
{
    if (pData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    static
        vid,
        id = -1;

    if(sscanf(params, "i", vid))
        return Usage(playerid, "/unlockcar [vehicleid]");

    if(!IsValidVehicle(vid))
        return Error(playerid, "Invalid vehicle id.");

    static engine, lights, alarm, doors,bonnet, boot, objective;
    GetVehicleParamsEx(vid, engine, lights, alarm, doors, bonnet, boot, objective);

	SwitchVehicleDoors(pvData[vid][cVeh], (doors ? false : true));

    if((id = Vehicle_GetID(vid)) != -1)
    {
        pvData[id][cLocked] = (doors ? false : true);
    }
    Servers(playerid, "You've %s vehicle id %d.", (doors ? ("Unlock") : ("Lock")), vid);
    return 1;
}

CMD:resetdutyadmin(playerid) {
	if(pData[playerid][pAdmin] > 5) {
		foreach(new i:Player) if(pData[i][pAdmin] > 0 || pData[i][pHelper] > 0) {
			pData[i][pAdminTime] = 0;
			SendCustomMessage(i, "AdmCmd", "%s telah mereset semua duty admin!", ReturnName(playerid));
		}
	}
	return 1;
}

CMD:admins(playerid, params[])
{
    new count = 0, line3[128];

    if (pData[playerid][pAdmin] > 0)
    {
        foreach (new i : Player)
        {
            if (pData[i][pAdmin] > 0 || pData[i][pHelper] > 0)
            {
                format(line3, sizeof(line3), "{FFFF00}[%d] {FFFFFF}%s, Status: %s", i, pData[i][pAdminname], pData[i][pAdminDuty] ? "{FF8C00}Duty" : "{32CD32}Roleplaying");
                SendClientMessage(playerid, -1, line3);
                count++;
            }
        }

        if (count > 0)
        {
            SendClientMessage(playerid, -1, "{FFFFFF}(( There are staff members on duty or roleplaying ))");
        }
        else
        {
            SendClientMessage(playerid, -1, "{FF0000}No admin members are on duty!");
        }
    }
    else
    {
        format(line3, sizeof(line3), "ID\tAccount\tRank\n");
        foreach(new i:Player) if(pData[i][pAdmin] > 0 || pData[i][pHelper] > 0) {
            format(line3, sizeof(line3), "%s\n%d\t%s (%s)\t%s", line3, i, pData[i][pName], pData[i][pAdminname], GetStaffRank(i));
            count++;
        }
        if(count > 0) ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Online Staff", line3, "Close", "");
    }

    return 1;
}

CMD:admindutytime(playerid, params[])
{
	new count = 0, line3[512];
	if(pData[playerid][pAdmin] > 0)
	{
		format(line3, sizeof(line3), "ID\tName\tRank Name\tDuty Time\n");
		foreach(new i:Player) if(pData[i][pAdmin] > 0 || pData[i][pHelper] > 0) {
			format(line3, sizeof(line3), "%s\n%d\t%s (%s)\t%s\t%d minute", line3, i, pData[i][pName], pData[i][pAdminname], GetStaffRank(i), pData[i][pAdminTime]/60);
			count++;
		}
		if(count > 0) ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Admin List", line3, "Close", "");
		else return Error(playerid, "Tidak ada ada admin yang online");
	}
	else
	{
		foreach(new i:Player) if(pData[i][pAdmin] > 0 || pData[i][pHelper] > 0) {
			if(pData[i][pAdminDuty] == 1)
			{
				format(line3, sizeof(line3), "%s\n"WHITE_E"[%s"WHITE_E"] %s (ID: %i)", line3, GetStaffRank(i), pData[i][pAdminname], i);
				count++;
			}
		}
		if(count > 0) ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""RED_E"Staff Online", line3, "Close", "");
		else return Error(playerid, "Tidak ada admin yang duty!");
	}
	return 1;
}

CMD:ahelp(playerid)
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

    new
        AdmCmdStr1[4096] = "Admin Level\tAdmin Command\n";

    if(pData[playerid][pAdmin] >= 1)
    {
        strcat(AdmCmdStr1, "/aduty\t1 (Volunteer)\n/a\t1 (Volunteer)\n/asay\t1 (Volunteer)\n/getchar\t1 (Volunteer)\n/getucp\t1 (Volunteer)\n/ogetucp\t1 (Volunteer)\n/apm\t1 (Volunteer)\n/togooc\t1 (Volunteer)\n/o\t1 (Volunteer)\n/goto\t1 (Volunteer)\n/setfg\t1 (Volunteer)\n/mark\t1 (Volunteer)\n/gotomark\t1 (Volunteer)\n/unwarn\t1 (Volunteer)\n/mute\t1 (Volunteer)\n/unmute\t1 (Volunteer)");
        strcat(AdmCmdStr1, "\n/freeze\t1 (Volunteer)\n/unfreeze\t1 (Volunteer)\n/revive\t1 (Volunteer)\n/aheal\t1 (Volunteer)\n/spec\t1 (Volunteer)\n/unspec\t1 (Volunteer)\n/slap\t1 (Volunteer)\n/caps\t1 (Volunteer)\n/aeject\t1 (Volunteer)\n/lowlist\t1 (Volunteer)\n/astats\t1 (Volunteer)\n/ostats\t/acuff\n/auncuff\t1 (Volunteer)");
        strcat(AdmCmdStr1, "\n/jetpack\t1 (Volunteer)\n/getip\t1 (Volunteer)\n/jail\t1 (Volunteer)\n/unjail\t1 (Volunteer)\n/ojail\t1 (Volunteer)\n/banucp\t1 (Volunteer)\n/obanucp\t1 (Volunteer)\n/unbanucp\t1 (Volunteer)\n/ounbanucp\t1 (Volunteer)");
        strcat(AdmCmdStr1, "\n/kick\t1 (Volunteer)\n/resetfrating\t1 (Volunteer)\n/respawnjobs\t1 (Volunteer)\n/reports\t1 (Volunteer)\n/asks\t1 (Volunteer)\n/vmodels\t1 (Volunteer)\n/vehname\t1 (Volunteer)\n/jobid\t1 (Volunteer)\n/apv\t1 (Volunteer)\n/aveh\t1 (Volunteer)");
        strcat(AdmCmdStr1, "\n/gotoveh\t1 (Volunteer)\n/getveh\t1 (Volunteer)\n/respawnveh\t1 (Volunteer)\n/respawnrad\t1 (Volunteer)\n/entercar\t1 (Volunteer)\n/banip\t1 (Volunteer)");
        strcat(AdmCmdStr1, "\n/owarn\t1 (Volunteer)\n/checkmask\t1 (Volunteer)\n/ans\t1 (Volunteer)\n/ar\t1 (Volunteer)\n/dr\t1 (Volunteer)");
    }
    if(pData[playerid][pAdmin] >= 2)
    {
        strcat(AdmCmdStr1, "\n/setam\t2 (Helper)\n/sethp\t2 (Helper)\n/clearallreports\t2 (Helper)\n/clearallasks\t2 (Helper)\n/fixveh\t2 (Helper)\n/setjob1\t2 (Helper)\n/setjob2\t2 (Helper)");
        strcat(AdmCmdStr1, "\n/setskin\t2 (Helper)\n/osetcs\t2 (Helper)\n/ounsetcs\t2 (Helper)\n/setcs\t2 (Helper)\n/unsetcs\t2 (Helper)");
        strcat(AdmCmdStr1, "\n/gotoco\t2 (Helper)\n/gotolocker\t2 (Helper)\n/gotodoor\t2 (Helper)\n/gotolocker\t2 (Helper)");
    }
    if(pData[playerid][pAdmin] >= 3)
    {
        strcat(AdmCmdStr1, "\n/resetweap\t3 (administrators)\n/giveweap\t3 (administrators)\n/sethbe\t3 (administrators");
    }
    if(pData[playerid][pAdmin] >= 4)
    {
        strcat(AdmCmdStr1, "\n/setname\t4 (Lead Administrators)\n/setgender\t4 (Lead Administrators)\n/setfaction\t4 (Lead Administrators)\n/setleader\t4 (Lead Administrators)");
    	strcat(AdmCmdStr1, "\n/takemoney\t4 (Lead Administrators)\n/takegold\t4 (Lead Administrators)\n/veh\t4 (Lead Administrators)\n/dveh\t4 (Lead Administrators)\n/destroyveh\t4 (Lead Administrators)");
    }
    if(pData[playerid][pAdmin] >= 5)
    {
        strcat(AdmCmdStr1, "\n/setadminname\t5 (Managements)\n/setcomponent\t5 (Managements)\n/setmaterial\t5 (Managements)\n/explode\t5 (Managements)\n/setpassword\t5 (Managements)");
    	strcat(AdmCmdStr1, "\n/gmx\t5 (Managements)\n/setlevel\t5 (Managements)\n/aarmor\t5 (Managements)\n/setvip\t5 (Managements)\n/setadminname\t5 (Managements)");
    }
    if(pData[playerid][pAdmin] >= 6)
    {
        strcat(AdmCmdStr1, "\n/sethelperlevel\t6 (Executive)\n/setadminname\t6 (Executive)\n/setmoney\t6 (Executive)\n/givemoney\t6 (Executive)\n/giveallmoney\t6 (Executive)");
    	strcat(AdmCmdStr1, "\n/setbankmoney\t6 (Executive)\n/givebakmoney\t6 (Executive)\n/createpv\t6 (Executive)\n/deletepv\t6 (Executive)\n/resetdutyadmin\t6 (Executive)");
    	strcat(AdmCmdStr1, "\n/setadminlevel\t6 (Executive)\n/setgold\t6 (Executive)\n/givegold\t6 (Executive)\n/setstock\t6 (Executive)\n/resetdamage\t6 (Executive)");
   		strcat(AdmCmdStr1, "\n/acure\t6 (Executive)\n/kickall\t6 (Executive)\n/admindutytime\t6 (Executive)");
    }
    Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Admin Commands", AdmCmdStr1, "CLOSE", "", "");
    return 1;
}


CMD:hcmds(playerid)
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] == 0)
		return PermissionError(playerid);

	new line3[2480];
	strcat(line3, ""WHITE_E"Junior Helper Commands:"LB2_E"\n\
 	/aduty /h /asay /o /goto /sendto /gethere /freeze /unfreeze\n\
	/kick /slap /caps /acuff /auncuff /reports /jailed /ar /dr");

	strcat(line3, "\n\n"WHITE_E"Senior Helper Commands:"LB2_E"\n\
 	/spec /peject /astats /ostats /jetpack\n\
    /jail /unjail");

	strcat(line3, "\n\n"WHITE_E"Head Helper Commands:"LB2_E"\n\
	/respawnsapd /respawnsags /respawnsamd /respawnsana /respawnjobs\n");

	strcat(line3, "\n"BLUE_E""WHITE_E"- Anti-Cheat is actived.\n\
	"PINK_E"NOTE: Semua log perintah admin disimpan dalam database | Abuse Commands? Kick And Demote Premanent!.");
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""YELLOW_E"Staff Commands", line3, "OK","");
	return true;
}

CMD:lowlist(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] == 0)
			return PermissionError(playerid);

    static name[24];

    foreach (new i : Player) if(pData[i][pLevel] < 2) 
    {
        GetPlayerName(i, name, sizeof(name));

        SendClientMessageEx(playerid, COLOR_RED, "[%d] "YELLOW_E"%s: Level %d", i, name, pData[i][pLevel]);
    }
    return 1;
}

CMD:jailed(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] == 0)
			return PermissionError(playerid);

	new count = 0, line3[512];
	foreach(new i : Player)
	{
		if(pData[i][pJail] > 0)
		{
			format(line3, sizeof(line3), "AdmCmd: %s\n"WHITE_E"%s(ID: %d) [Jail Time: %d seconds]", line3, ReturnName(i), i, pData[i][pJailTime]);
			count++;
		}
	}
	if(count > 0) ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""RED_E"Jail Player", line3, "Close", "");
	else ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""RED_E"Jail Player", "Tidak ada player yang di jail!", "Close", "");
	return 1;
}

CMD:fine(playerid, params[])
{
    new userid, amount[32], totalcash[32], reason[32];
    if(pData[playerid][pAdmin] < 1) return PermissionError(playerid);
    if(sscanf(params, "us[32]s[32]", userid, amount, reason)) return Usage(playerid, "/fine [playerid/PartOfName] [money] [reason]");
    if(userid == INVALID_PLAYER_ID) return Error(playerid, "Player tersebut tidak login ke server.");
    if(!(0 < strval(amount))) return Error(playerid, "Uang dibatasi mulai dari 0!");
	format(totalcash, sizeof(totalcash), "%d00", strval(amount));
    GivePlayerMoneyEx(userid, -strval(totalcash));
    Servers(userid, "Kamu didenda oleh admin "RED_E"%s "WHITE_E"sebanyak "RED_E"$%s.", pData[playerid][pAdminname], FormatMoney(strval(totalcash)));
    SendClientMessageToAllEx(TOMATO, "AdmCmd: %s was fined by %s for $%s. Reason %s.", ReturnName(userid), ReturnName(playerid), FormatMoney(strval(totalcash)), reason);
    return 1;
}

//---------------------------[ Admin Level 1 ]--------------------
CMD:aduty(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] == 0)
			return PermissionError(playerid);
	if(pData[playerid][pMaskOn]) return Error(playerid, "You're using a mask remove the mask first");
	if(!strcmp(pData[playerid][pAdminname], "None"))
		return Error(playerid, "You must set you adminname!");
	if(!pData[playerid][pAdminDuty])
    {
		GetPlayerHealth(playerid, HealthDuty[playerid]);
		if(pData[playerid][pAdmin] > 0)
		{
			SetPlayerColor(playerid, COLOR_RED);
			if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
	        	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_RED, (sprintf("%s (%d)", pData[playerid][pAdminname], playerid)));
			pData[playerid][pAdminDuty] = 1;
			SetPlayerName(playerid, pData[playerid][pAdminname]);
			SetPlayerHealth(playerid, 999999);
        	SendStaffMessage(COLOR_ARWIN, ""ARWIN_E"ADMIN-DUTY: {FF0000}%s {FFFF00}is now on duty as an admin/helper.", pData[playerid][pAdminname]);
		}
		else
		{
			SetPlayerColor(playerid, COLOR_RED);
			if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
	        	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_RED, (sprintf("%s (%d)", pData[playerid][pAdminname], playerid)));
			pData[playerid][pAdminDuty] = 1;
			SetPlayerName(playerid, pData[playerid][pAdminname]);
			SetPlayerHealth(playerid, 999999);
			SendStaffMessage(COLOR_ARWIN, ""ARWIN_E"ADMIN-DUTY: {FF0000}%s {0000FF}is now on duty as an admin/helper.", pData[playerid][pAdminname]);
		}
    }
    else
    {
        if(pData[playerid][pFaction] != -1 && pData[playerid][pOnDuty])
            SetFactionColor(playerid);
        else
            SetPlayerColor(playerid, COLOR_WHITE);

		if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
        UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s (%d)", pData[playerid][pName], playerid)));
        SetPlayerName(playerid, pData[playerid][pName]);
        pData[playerid][pAdminDuty] = 0;
		SetPlayerHealthEx(playerid, HealthDuty[playerid]);
        SendStaffMessage(COLOR_ARWIN, ""ARWIN_E"ADMIN-DUTY: {FF0000}%s {0000FF}is now no longer as an admin/helper.", pData[playerid][pAdminname]);
    }
	return 1;
}

CMD:asay(playerid, params[])
{
    new text[225];
    if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] == 0) return PermissionError(playerid);
    if(sscanf(params,"s[225]",text)) return Usage(playerid, "/asay [text]");
    SendClientMessageToAllEx(TOMATO,"%s "YELLOW_E"%s: "LG_E"%s", GetStaffRank(playerid), pData[playerid][pAdminname], ColouredText(text));
    return 1;
}

CMD:setlevel(playerid, params[])
{
    if(pData[playerid][pAdmin] < 5) return PermissionError(playerid);
    {
        new targetid, level;
		if(sscanf(params, "ui", targetid, level)) return Usage(playerid, "/setlevel [playerid/PartOfName] [Level]");
		{
	    	pData[targetid][pLevel] = level;
	    	Servers(targetid, "AdmCmd:  %s telah meng-set level kamu menjadi %d", pData[playerid][pAdminname], level);
	    	Servers(playerid, "%s telah kamu set level nya menjadi %d", ReturnName(targetid), level);
		}
	}
	return 1;
}

CMD:a(playerid, params[])
{
    if(pData[playerid][pAdmin] < 1)
            return PermissionError(playerid);

    if(isnull(params))
    {
        Usage(playerid, "/a <text>");
        return true;
    }

    if(strlen(params) < 128) 
    {
        if(pData[playerid][pAdmin])
        {
            SendAdminChatMessage(COLOR_LIGHTGREEN, " *%s %s: %s", GetAdminRank(playerid), pData[playerid][pAdminname], params);
        }
        // if (AccountData[playerid][pVolunteer]) {
        //     SendAdminChatMessage(COLOR_LIGHTGREEN, "Volunteer %s: {33EE33}%s", ReturnAdminName(playerid), params);
        // }
    }
    return true;
}

CMD:setcs(playerid, params[])
{
    if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);
 	new otherid;
 	
 	Servers(otherid, "Your CS has approved by %s.", pData[playerid][pAdminname]);
 	
 	if(sscanf(params, "d", otherid)) return Usage(playerid, "/setcs [playerid]");

 	if(pData[otherid][pCS] != 0) return Error(playerid, "Character story anda sudah di approve!");
 	SendStaffMessage(COLOR_RED, "AdmCmd: %s has approved Character Story %s (ID: %d).", pData[playerid][pAdminname], ReturnName(otherid), otherid);
 	SendClientMessageEx(otherid, COLOR_RED, "Your CS has approved by %s", pData[playerid][pAdminname]);
 	pData[otherid][pCS] = 1;
 	return 1;
}

CMD:unsetcs(playerid, params[])
{
    if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);
 	new otherid;

 	if(sscanf(params, "d", otherid)) return Usage(playerid, "/unsetcs [playerid]");
 	if(pData[otherid][pCS] != 1) return Error(playerid, "Character story anda sudah di approve!");
 	SendStaffMessage(COLOR_RED, "AdmCmd: %s has un approved CS %s (ID: %d).", pData[playerid][pAdminname], ReturnName(otherid), otherid);
 	pData[otherid][pCS] = 0;
 	return 1;
}

CMD:unverif(playerid, params[])
{
    if(pData[playerid][pAdmin] < 1)
        return PermissionError(playerid);
    new name[24], PlayerName[24];
 	if(sscanf(params, "s[24]", name))
	{
	    Usage(playerid, "/unverif <player name>");
 		return 1;
 	}

 	foreach(new ii : Player)
	{
		GetPlayerName(ii, PlayerName, MAX_PLAYER_NAME);

		if(!strcmp(PlayerName, name, true))
		{
			Error(playerid, "Player is online, you can use /unverif on them.");
	  		return 1;
	  	}
	}
    new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", name);
	mysql_tquery(g_SQL, query, "Unverifplayer", "is", playerid, name);
 	return true;
}

CMD:osetcs(playerid, params[])
{
    if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);
    new name[24], PlayerName[24];
 	if(sscanf(params, "s[24]", name))
	{
	    Usage(playerid, "/osetcs <player name>");
 		return 1;
 	}

 	foreach(new ii : Player)
	{
		GetPlayerName(ii, PlayerName, MAX_PLAYER_NAME);

		if(!strcmp(PlayerName, name, true))
		{
			Error(playerid, "Player is online, you can use /setcs on them.");
	  		return 1;
	  	}
	}
    new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", name);
	mysql_tquery(g_SQL, query, "SetCSPlayer", "is", playerid, name);
 	return true;
}

CMD:ounsetcs(playerid, params[])
{
    if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);
    new name[24], PlayerName[24];
 	if(sscanf(params, "s[24]", name))
	{
	    Usage(playerid, "/ounsetcs <player name>");
 		return 1;
 	}

 	foreach(new ii : Player)
	{
		GetPlayerName(ii, PlayerName, MAX_PLAYER_NAME);

		if(!strcmp(PlayerName, name, true))
		{
			Error(playerid, "Player is online, you can use /setcs on them.");
	  		return 1;
	  	}
	}
    new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", name);
	mysql_tquery(g_SQL, query, "UnsetCSPlayer", "is", playerid, name);
 	return true;
}

CMD:togooc(playerid, params[])
{
    if(pData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    foreach (new i : Player)
    {
    	if(pData[i][pTogGlobalOoc] == 0)
    	{
		    if(TogOOC == 0)
		    {
		        SendClientMessageToAllEx(COLOR_YELLOW, "[OOC] Global ooc has been enabled by an admin");
		        TogOOC = 1;
		    }
		    else
		    {
		        SendClientMessageToAllEx(COLOR_YELLOW, "[OOC] Global ooc has been disabled by an admin");
		        TogOOC = 0;
		    }
    	}
    }
    return 1;
}

CMD:o(playerid, params[])
{
    if (TogOOC == 1 && pData[playerid][pAdmin] < 1 && pData[playerid][pHelper] < 1)
        return Error(playerid, "GLOBAL Chat is currently closed.");

    if (isnull(params))
        return Usage(playerid, "/o [GLOBAL]");

    if (strlen(params) < 90)
    {
        foreach (new i : Player)
        {
            if (pData[i][IsLoggedIn] == true && pData[i][pSpawned] == 1 && pData[i][pTogGlobalOoc] == 0)
            {
                if (pData[playerid][pAdmin] > 1 && pData[playerid][pAdminDuty] == 1)
                {
                    SendClientMessageEx(i, COLOR_WHITE, "(( "RED_E"%s{FFFFFF}: %s {FFFFFF}))", pData[playerid][pAdminname], ColouredText(params));
                }
                else if (pData[playerid][pHelper] > 0 && pData[playerid][pAdmin] == 0 && pData[playerid][pAdminDuty] == 1)
                {
                    SendClientMessageEx(i, COLOR_WHITE, "(( "RED_E"Junior Helper %s{FFFFFF}: %s {FFFFFF}))", pData[playerid][pAdminname], ColouredText(params));
                }
                else
                {
                    SendClientMessageEx(i, COLOR_WHITE, "(( {33FFCC}Player %s{FFFFFF} [%d]: %s ))", ReturnName(playerid), playerid, params);
                }
            }
        }
    }
    else
        return Error(playerid, "Maximum text length is 90 characters.");

    return 1;
}

CMD:id(playerid, params[])
{
	new otherid;
	if(sscanf(params, "u", otherid))
        return Usage(playerid, "/id [playerid/PartOfName]");

	if(!IsPlayerConnected(otherid))
		return Error(playerid, "No player online or name is not found!");

	static online[24];
	
	FormatTimeleft((GetConnectedTime(otherid)/1000), online);
    new string[24];
    GetPlayerVersion(otherid, string, sizeof(string));
	SendClientMessageEx(playerid, COLOR_ARWIN, "[ID:%d] "WHITE_E"%s (level %d), Ping: %d, Online time: %s, Client: %s, Packets lost: %.2f", otherid, ReturnName(otherid), pData[otherid][pLevel], GetPlayerPing(otherid), online, string, NetStats_PacketLossPercent(otherid));
	return 1;
}

CMD:goto(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] == 0) return PermissionError(playerid);
	new otherid;
	if(sscanf(params, "u", otherid)) return Usage(playerid, "/goto [playerid/PartOfName]");
    if(!IsPlayerConnected(otherid)) return Error(playerid, "Player tidak on!");
	SendPlayerToPlayer(playerid, otherid);
	SendClientMessageEx(playerid, COLOR_GRAD1, "{B0C4DE}TELEPORT: {FFFFFF}You have been teleported!");
	SendClientMessageEx(otherid, COLOR_GRAD1, "{B0C4DE}TELEPORT: {FFFFFF}Admin {00FFFF}%s {FFFFFF}has teleported to you", pData[playerid][pAdminname]);
	return 1;
}

CMD:sendto(playerid, params[])
{
    static
        type[24],
		otherid;
    if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] == 0) return PermissionError(playerid);
    if(sscanf(params, "us[32]", otherid, type)) return Usage(playerid, "/send [player] [ls/lv/sf/auction]");
	if(!IsPlayerConnected(otherid)) return Error(playerid, "Player tidak on!");
	if(!strcmp(type,"ls"))
	{
        if(GetPlayerState(otherid) == PLAYER_STATE_DRIVER) SetVehiclePos(GetPlayerVehicleID(otherid),1482.0356,-1724.5726,13.5469);
        else SetPlayerPosition(otherid,1482.0356,-1724.5726,13.5469,750);
        SetPlayerFacingAngle(otherid,179.4088);
        SetPlayerInterior(otherid, 0);
        SetPlayerVirtualWorld(otherid, 0);
		SendCustomMessage(playerid, "AdmCmd" ,""YELLOW_E"%s telah berhasil di teleport", ReturnName(otherid));
		SendCustomMessage(otherid, "AdmCmd" ,""YELLOW_E"%s telah mengirim anda ke teleport spawn", pData[playerid][pAdminname]);
		pData[otherid][pInDoor] = -1;
		pData[otherid][pInHouse] = -1;
		pData[otherid][pInBiz] = -1;
    }
	if(!strcmp(type,"auction"))
	{
        if(GetPlayerState(otherid) == PLAYER_STATE_DRIVER) SetVehiclePos(GetPlayerVehicleID(otherid),1506.6411,-1549.8044,17.5144);
        else SetPlayerPosition(otherid,1506.6411,-1549.8044,17.5144,750);
        SetPlayerFacingAngle(otherid,179.4088);
        SetPlayerInterior(otherid, 5);
        SetPlayerVirtualWorld(otherid, 0);
		SendCustomMessage(playerid, "AdmCmd" ,""YELLOW_E"%s telah berhasil di teleport", ReturnName(otherid));
		SendCustomMessage(otherid, "AdmCmd" ,""YELLOW_E"%s telah mengirim anda ke teleport spawn", pData[playerid][pAdminname]);
		pData[otherid][pInDoor] = -1;
		pData[otherid][pInHouse] = -1;
		pData[otherid][pInBiz] = -1;
    }
    else if(!strcmp(type,"sf"))
	{
        if(GetPlayerState(otherid) == PLAYER_STATE_DRIVER) SetVehiclePos(GetPlayerVehicleID(otherid),-1425.8307,-292.4445,14.1484);
        else SetPlayerPosition(otherid,-1425.8307,-292.4445,14.1484,750);
        SetPlayerFacingAngle(otherid,179.4088);
        SetPlayerInterior(otherid, 0);
        SetPlayerVirtualWorld(otherid, 0);
		SendCustomMessage(playerid, "AdmCmd" ,""YELLOW_E"%s telah berhasil di teleport", ReturnName(otherid));
		SendCustomMessage(otherid, "AdmCmd" ,""YELLOW_E"%s telah mengirim anda ke teleport spawn", pData[playerid][pAdminname]);
		pData[otherid][pInDoor] = -1;
		pData[otherid][pInHouse] = -1;
		pData[otherid][pInBiz] = -1;
    }
    else if(!strcmp(type,"lv"))
	{
        if(GetPlayerState(otherid) == PLAYER_STATE_DRIVER) SetVehiclePos(GetPlayerVehicleID(otherid),1686.0118,1448.9471,10.7695);
        else SetPlayerPosition(otherid,1686.0118,1448.9471,10.7695,750);
        SetPlayerFacingAngle(otherid,179.4088);
        SetPlayerInterior(otherid, 0);
        SetPlayerVirtualWorld(otherid, 0);
		SendCustomMessage(playerid, "AdmCmd" ,""YELLOW_E"%s telah berhasil di teleport", ReturnName(otherid));
		SendCustomMessage(otherid, "AdmCmd" ,""YELLOW_E"%s telah mengirim anda ke teleport spawn", pData[playerid][pAdminname]);
		pData[otherid][pInDoor] = -1;
		pData[otherid][pInHouse] = -1;
		pData[otherid][pInBiz] = -1;
    }
    return 1;
}

CMD:gethere(playerid, params[])
{
    new otherid;

	if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] == 0) return PermissionError(playerid);
    if(sscanf(params, "u", otherid)) return Usage(playerid, "/gethere [playerid/PartOfName]");
    if(!IsPlayerConnected(otherid)) return Error(playerid, "The specified user(s) are not connected.");
	if(pData[playerid][pSpawned] == 0 || pData[otherid][pSpawned] == 0) return Error(playerid, "Player/Target sedang tidak spawn!");
	if(pData[playerid][pJail] > 0 || pData[otherid][pJail] > 0) return Error(playerid, "Player/Target sedang di jail");
	if(pData[playerid][pArrest] > 0 || pData[otherid][pArrest] > 0) return Error(playerid, "Player/Target sedang di arrest");

    SendPlayerToPlayer(otherid, playerid);
    SendCustomMessage(playerid, "TELEPORT" ,""YELLOW_E"You have get by "RED_E"%s", ReturnName(otherid));
	SendClientMessageEx(otherid, COLOR_ARWIN, "TELEPORT: "YELLOW_E"You have been teleported!");
    return 1;
}

CMD:freeze(playerid, params[])
{
	new otherid;
	if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] == 0) return PermissionError(playerid);
    if(sscanf(params, "u", otherid)) return Usage(playerid, "/freeze [playerid/PartOfName]");
    if(!IsPlayerConnected(otherid)) return Error(playerid, "Player tidak on!");
    pData[playerid][pFreeze] = 1;

    TogglePlayerControllable(otherid, 0);
    SendCustomMessage(playerid, "AdmCmd" ,""YELLOW_E"Kamu telah membuat player %s freeze", ReturnName2(otherid));
	SendCustomMessage(otherid, "AdmCmd" ,""YELLOW_E"Anda telah di buat freeze oleh admin "RED_E"%s", pData[playerid][pAdminname]);
    return 1;
}

CMD:unfreeze(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] == 0) return PermissionError(playerid);
	new otherid;
    if(sscanf(params, "u", otherid)) return Usage(playerid, "/unfreeze [playerid/PartOfName]");
    if(!IsPlayerConnected(otherid)) return Error(playerid, "Player tidak on!");
    pData[playerid][pFreeze] = 0;

    TogglePlayerControllable(otherid, 1);
    SendCustomMessage(playerid, "AdmCmd" ,""YELLOW_E"You have unfrozen %s's movements.", ReturnName(otherid));
	SendCustomMessage(otherid, "AdmCmd" ,""YELLOW_E"You have been unfrozen movements by admin %s.", pData[playerid][pAdminname]);
    return 1;
}

CMD:revive(playerid, params[])
{
    if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] < 2) return PermissionError(playerid);
	new otherid;
    if(sscanf(params, "u", otherid)) return Usage(playerid, "/revive [playerid/PartOfName]");
    if(!IsPlayerConnected(otherid)) return Error(playerid, "Player tidak on!");

    SetPlayerHealth(otherid, 100.0);
	TextDrawHideForPlayer(otherid, injuredtextdraw);
    pData[otherid][pInjured] = 0;
	pData[otherid][pHospital] = 0;
	pData[otherid][pSick] = 0;
	Damage_Reset(otherid);
    ClearAnimations(otherid);
    StopLoopingAnim(otherid);
	SetPlayerSpecialAction(otherid, SPECIAL_ACTION_NONE);
    TogglePlayerControllable(otherid, 1);
	new getime[3];
	gettime(getime[0], getime[1], getime[2]);
	SetPlayerTime(otherid, getime[0], getime[1]);
	SetPlayerWeather(otherid, current_weather);

	SendClientMessageEx(playerid, COLOR_ARWIN, "HEAL: "YELLOW_E"You have forced %s to death.", ReturnName(otherid));
	SendClientMessageEx(otherid, COLOR_ARWIN, "HEAL: "YELLOW_E"You have ben healed By: "RED_E"%s", pData[playerid][pAdminname]);
    return 1;
}

CMD:spec(playerid, params[])
{
    if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] < 2) return PermissionError(playerid);

	new otherid;
    if(sscanf(params, "u", otherid)) return Usage(playerid, "/spectate [playerid/PartOfName] - Type '/unspec' to stop spectating.");
    if(!IsPlayerConnected(otherid)) return Error(playerid, "Player tidak on!");
	if(otherid == playerid) return Error(playerid, "You can't spectate yourself bro..");
    if(pData[playerid][pAdmin] < pData[otherid][pAdmin]) return Error(playerid, "You can't spectate admin higher than you.");
	if(pData[otherid][pSpawned] == 0) return Error(playerid, "%s(%i) isn't spawned!", ReturnName(otherid), otherid);
    if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
    {
        GetPlayerPos(playerid, pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ]);
        GetPlayerFacingAngle(playerid, pData[playerid][pPosA]);

        pData[playerid][pInt] = GetPlayerInterior(playerid);
        pData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
    }
    pData[playerid][pSpec] = otherid;
    SetPlayerInterior(playerid, GetPlayerInterior(otherid));
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(otherid));
    GetPlayerHealth(playerid, pData[playerid][pHealth]);
    GetPlayerArmour(playerid, pData[playerid][pArmour]);
    TogglePlayerSpectating(playerid, true);

    if(IsPlayerInAnyVehicle(otherid))
	{
		new vID = GetPlayerVehicleID(otherid);
        PlayerSpectateVehicle(playerid, GetPlayerVehicleID(otherid));
		if(GetPlayerState(otherid) == PLAYER_STATE_DRIVER) SendCustomMessage(playerid, "AdmCmd" ,""YELLOW_E"You are now spectating "GREEN_E"%s(%i) "YELLOW_E"who is driving a "AQUA_E"%s(%d).", ReturnName(otherid), otherid, GetVehicleModelName(GetVehicleModel(vID)), vID);
		else SendCustomMessage(playerid, "AdmCmd" ,""YELLOW_E"You are now spectating "GREEN_E"%s(%i) "YELLOW_E"who is a passenger in "AQUA_E"%s(%d).", ReturnName(otherid), otherid, GetVehicleModelName(GetVehicleModel(vID)), vID);
	}
    else PlayerSpectatePlayer(playerid, otherid);

    PlayerTextDrawShow(playerid, SpecTD[playerid][1]);
    PlayerTextDrawShow(playerid, SpecTD[playerid][0]);

    if(pData[playerid][pAdmin] < pData[otherid][pAdmin])
        return SendCustomMessage(otherid, "SPECTATE", ""RED_E"%s"WHITE_E" is now spectating you!", ReturnName(playerid));
    return 1;
}

CMD:unspec(playerid, params[])
{
    if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] < 2) return PermissionError(playerid);
    if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) return Error(playerid, "You are not spectating any player.");

    PlayerSpectatePlayer(playerid, INVALID_PLAYER_ID);
    PlayerSpectateVehicle(playerid, INVALID_VEHICLE_ID);

    pData[playerid][pSpec] = INVALID_PLAYER_ID;

    SetSpawnInfo(playerid, 0, pData[playerid][pSkin], pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ], pData[playerid][pPosA], 0, 0, 0, 0, 0, 0);
    TogglePlayerSpectating(playerid, false);
    PlayerTextDrawHide(playerid, SpecTD[playerid][1]);
    PlayerTextDrawHide(playerid, SpecTD[playerid][0]);

    return 1;
}

CMD:setint(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] == 0)
			return PermissionError(playerid);

	new otherid, intid;
	if(sscanf(params, "ui", otherid, intid))
	{
	    Usage(playerid, "/setint <ID> <INT ID>");
	    return true;
	}

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	SetPlayerInterior(otherid, intid);
	SendCustomMessage(otherid, "INT" ,""RED_E"%s "YELLOW_E"Have changed your int to "AQUA_E"%d", pData[playerid][pAdminname], intid);
	SendCustomMessage(playerid, "INT" ,""YELLOW_E"You've changed int "RED_E"%s "YELLOW_E"to "AQUA_E"%d", ReturnName(otherid), intid);
	return 1;
}

CMD:setfg(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] == 0)
			return PermissionError(playerid);

	new otherid, intid;
	if(sscanf(params, "ui", otherid, intid))
	{
	    Usage(playerid, "/setfg <ID> <FIGHT ID>");
	    SendClientMessageEx(playerid, COLOR_GRAD2, "Available fighting styles: 4, 5, 6, 7, 15, 16.");
	    return true;
	}

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	SetPlayerFightingStyle(playerid, intid);
	SendCustomMessage(otherid, "FIGHT" ,""RED_E"%s "YELLOW_E"Have changed your fight style to "AQUA_E"%d", pData[playerid][pAdminname], intid);
	SendCustomMessage(playerid, "FIGHT" ,""YELLOW_E"You've changed fight style "RED_E"%s "YELLOW_E"to "AQUA_E"%d", ReturnName(otherid), intid);
	pData[otherid][FightStyle] = intid;
	return 1;
}

CMD:setvw(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] == 0)
			return PermissionError(playerid);

	new otherid, vwid;
	if(sscanf(params, "ui", otherid, vwid))
	{
	    Usage(playerid, "/setvw <ID> <VW ID>");
	    return true;
	}

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	SetPlayerVirtualWorld(otherid, vwid);
	SendCustomMessage(otherid, "VW" ,""RED_E"%s "YELLOW_E"Have changed your VW to "AQUA_E"%d", pData[playerid][pAdminname], vwid);
	SendCustomMessage(playerid, "VW" ,""YELLOW_E"You've changed VW "RED_E"%s "YELLOW_E"to "AQUA_E"%d", ReturnName(otherid), vwid);
	return 1;
}

CMD:slap(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] == 0)
			return PermissionError(playerid);

	new Float:POS[3], otherid, Float:height;
	if(sscanf(params, "uf", otherid, height))
	{
	    Usage(playerid, "/slap <ID> <height>");
	    return true;
	}

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	GetPlayerPos(otherid, POS[0], POS[1], POS[2]);
	SetPlayerPos(otherid, POS[0], POS[1], POS[2] + height);
	if(IsPlayerInAnyVehicle(otherid))
	{
		RemovePlayerFromVehicle(otherid);
		//OnPlayerExitVehicle(otherid, GetPlayerVehicleID(otherid));
	}
	SendStaffMessage(TOMATO, "AdmCmd: %s telah men-slap player %s", pData[playerid][pAdminname], ReturnName(otherid));

	PlayerPlaySound(otherid, 1130, 0.0, 0.0, 0.0);
	return 1;
}

CMD:caps(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] == 0)
			return PermissionError(playerid);

	new otherid;
 	if(sscanf(params, "u", otherid))
	{
	    Usage(playerid, "/caps <ID>");
	    Info(playerid, "Function: Will disable caps for the player, type again to enable caps.");
	    return 1;
	}
	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	if(!GetPVarType(otherid, "Caps"))
	{
	    // Disable Caps
	    SetPVarInt(otherid, "Caps", 1);
		SendClientMessageToAllEx(TOMATO, "Admcmd: Admin %s telah menon-aktifkan anti caps kepada player %s", pData[playerid][pAdminname], ReturnName(playerid));
	}
	else
	{
	    // Enable Caps
		DeletePVar(otherid, "Caps");
		SendClientMessageToAllEx(TOMATO, "Admcmd: Admin %s telah meng-aktifkan anti caps kepada player %s", pData[playerid][pAdminname], ReturnName(playerid));
	}
	return 1;
}

CMD:aeject(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] < 2) return PermissionError(playerid);
	new otherid;
	if(sscanf(params, "u", otherid))
	{
	    Usage(playerid, "/aeject <ID>");
	    return 1;
	}

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	if(!IsPlayerInAnyVehicle(otherid))
	{
		Error(playerid, "Player tersebut tidak berada dalam kendaraan!");
		return 1;
	}

	new vv = GetVehicleModel(GetPlayerVehicleID(otherid));
	Servers(playerid, "You have successfully ejected %s(%i) from their %s.", ReturnName(otherid), otherid, GetVehicleModelName(vv - 400));
	Servers(otherid, "%s(%i) has ejected you from your %s.", ReturnName(playerid), playerid, GetVehicleModelName(vv));
	RemovePlayerFromVehicle(otherid);
	return 1;
}

CMD:aitems(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] < 2) return PermissionError(playerid);

	new otherid;
	if(sscanf(params, "u", otherid))
        return Usage(playerid, "/aitems [playerid/PartOfName]");

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	if(pData[otherid][IsLoggedIn] == false)
        return Error(playerid, "That player is not logged in yet.");

	DisplayItems(playerid, otherid);
	return 1;
}

CMD:askills(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] < 2) return PermissionError(playerid);

	new otherid;
	if(sscanf(params, "u", otherid))
        return Usage(playerid, "/askills [playerid/PartOfName]");

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	if(pData[otherid][IsLoggedIn] == false)
        return Error(playerid, "That player is not logged in yet.");

	DisplaySkills(playerid, otherid);
	return 1;
}

CMD:astats(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] < 2) return PermissionError(playerid);
	new otherid;
	if(sscanf(params, "u", otherid)) return Usage(playerid, "/check [playerid/PartOfName]");
	if(!IsPlayerConnected(otherid)) return Error(playerid, "Player tidak on!");
	if(pData[otherid][IsLoggedIn] == false) return Error(playerid, "That player is not logged in yet.");

	DisplayStats(playerid, otherid);
	return 1;
}

CMD:ostats(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] < 2) return PermissionError(playerid);

	new name[24], PlayerName[24];
	if(sscanf(params, "s[24]", name))
	{
	    Usage(playerid, "/ostats <player name>");
 		return 1;
 	}

 	foreach(new ii : Player)
	{
		GetPlayerName(ii, PlayerName, MAX_PLAYER_NAME);

		if(!strcmp(PlayerName, name, true))
		{
			Error(playerid, "Player is online, you can use /stats on them.");
	  		return 1;
	  	}
	}

	// Load User Data
    new cVar[500];
    new cQuery[600];

	strcat(cVar, "admin,helper,level,levelup,vip,vip_time,gold,reg_date,last_login,money,bmoney,brek,hours,minutes,seconds,");
	strcat(cVar, "gender,age,faction,family,warn,job,job2,interior,world");

	mysql_format(g_SQL, cQuery, sizeof(cQuery), "SELECT %s FROM players WHERE username='%e' LIMIT 1", cVar, name);
	mysql_tquery(g_SQL, cQuery, "LoadStats", "is", playerid, name);
	return true;
}

CMD:acuff(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] == 0) return PermissionError(playerid);

	new otherid, mstr[128];
    if(sscanf(params, "u", otherid))
        return Usage(playerid, "/acuff [playerid/PartOfName]");

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

    //if(otherid == playerid)
        //return Error(playerid, "You cannot handcuff yourself.");

    if(!NearPlayer(playerid, otherid, 5.0))
        return Error(playerid, "You must be near this player.");

    if(GetPlayerState(otherid) != PLAYER_STATE_ONFOOT)
        return Error(playerid, "The player must be onfoot before you can cuff them.");

    if(pData[otherid][pCuffed])
        return Error(playerid, "The player is already cuffed at the moment.");

    pData[otherid][pCuffed] = 1;
	SetPlayerSpecialAction(otherid, SPECIAL_ACTION_CUFFED);

    format(mstr, sizeof(mstr), "You've been ~r~cuffed~w~ by %s.", ReturnName(playerid));
    InfoTD_MSG(otherid, 3500, mstr);

    Servers(playerid, "Player %s telah berhasil di cuffed.", ReturnName(otherid));
    Servers(otherid, "Admin %s telah mengcuffed anda.", ReturnName(playerid));
    return 1;
}

CMD:auncuff(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] == 0) return PermissionError(playerid);

	new otherid;
    if(sscanf(params, "u", otherid))
        return Usage(playerid, "/auncuff [playerid/PartOfName]");

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

    //if(otherid == playerid)
        //return Error(playerid, "You cannot uncuff yourself.");

    if(!NearPlayer(playerid, otherid, 5.0))
        return Error(playerid, "You must be near this player.");

    if(!pData[otherid][pCuffed])
        return Error(playerid, "The player is not cuffed at the moment.");

    static
        string[64];

    pData[otherid][pCuffed] = 0;
    SetPlayerSpecialAction(otherid, SPECIAL_ACTION_NONE);

    format(string, sizeof(string), "You've been ~g~uncuffed~w~ by %s.", ReturnName(playerid));
    InfoTD_MSG(otherid, 3500, string);
	Servers(playerid, "Player %s telah berhasil uncuffed.", ReturnName(otherid));
    Servers(otherid, "Admin %s telah uncuffed tangan anda.", ReturnName(playerid));
    return 1;
}

CMD:jetpack(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
   		if(pData[playerid][pHelper] < 1)
     		return PermissionError(playerid);

	new otherid;
    if(sscanf(params, "u", otherid))
    {
        //pData[playerid][pJetpack] = 1;
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
    }
    else
    {
        //pData[playerid][pJetpack] = 1;
        SetPlayerSpecialAction(otherid, SPECIAL_ACTION_USEJETPACK);
        Servers(playerid, "You have spawned a jetpack for %s.", ReturnName(otherid));
    }
    return 1;
}

CMD:getip(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
     	return PermissionError(playerid);

	new otherid, PlayerIP[16], giveplayer[24];
	if(sscanf(params, "u", otherid))
 	{
  		Usage(playerid, "/getip <ID>");
		return 1;
	}

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	if(pData[otherid][pAdmin] == 5)
 	{
  		Error(playerid, "You can't get the server owners ip!");
  		Servers(otherid, "%s(%i) tried to get your IP!", ReturnName(playerid), playerid);
  		return 1;
    }
	GetPlayerName(otherid, giveplayer, sizeof(giveplayer));
	GetPlayerIp(otherid, PlayerIP, sizeof(PlayerIP));

	Servers(playerid, "%s(%i)'s IP: %s", giveplayer, otherid, PlayerIP);
	return 1;
}

CMD:aka(playerid, params[])
{
    static
        userid[MAX_PLAYER_NAME],
        Cache: ipcheck,
        query[128];

    if(pData[playerid][pAdmin] < 1)
     	return PermissionError(playerid);

    if(sscanf(params, "s[32]", userid))
        return Usage(playerid, "/aka [username]");

    format(query, sizeof(query), "SELECT `ip` FROM `players` WHERE `username`='%s'", userid);
    ipcheck = mysql_query(g_SQL, query);

    new rows = cache_num_rows();

    if(rows)
    {
        new ip[32];
        cache_get_value_name(0, "IP", ip, 32);
        Servers(playerid, "Offline ip check from username/accounts %s: %s", userid, ip);
    }
    else
        Error(playerid, "%s isn't registered.", userid);

    cache_delete(ipcheck);
    return 1;
}

Dialog:ShowOnly(playerid, response, listitem, inputtext[]) {
    playerid = INVALID_PLAYER_ID;
    response = 0;
    listitem = 0;
    inputtext[0] = '\0';
}

CMD:akaip(playerid, params[])
{
    static
        ip[MAX_PLAYER_NAME],
        Cache: ipcheck,
        query[128],
		username[1024],
		str[4096];

    if(pData[playerid][pAdmin] < 1)
     	return PermissionError(playerid);

    if(sscanf(params, "s[32]", ip))
        return Usage(playerid, "/akaip [ip]");

    format(query, sizeof(query), "SELECT `username` FROM `players` WHERE `ip`='%s'", ip);
    ipcheck = mysql_query(g_SQL, query);

    new rows = cache_num_rows();

	if(rows) {
		for(new i=0; i < rows; i++) {
			new cacheString[255];
			cache_get_value_name(i, "username", username, 32);
			format(cacheString, sizeof(cacheString), "%s\n", username);
			strcat(str, cacheString);
		}
	} else {
		Error(playerid, "No username found with this ip %s", ip);
	}

	Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_LIST, "Registered Username", str, "Close", "");
    
	cache_delete(ipcheck);
    return 1;
}

CMD:vmodels(playerid, params[])
{
    new string[5000];

    if(pData[playerid][pAdmin] < 1)
     	return PermissionError(playerid);

    for (new i = 0; i < sizeof(g_arrVehicleNames); i ++)
    {
        format(string,sizeof(string), "%s%d - %s\n", string, i+400, g_arrVehicleNames[i]);
    }
    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_LIST, "Vehicle Models", string, "Close", "");
    return 1;
}

CMD:vehname(playerid, params[]) {

	if(pData[playerid][pAdmin] >= 1)
	{
		SendClientMessageEx(playerid, COLOR_YELLOW, "--------------------------------------------------------------------------------------------------------------------------------");
		SendClientMessageEx(playerid, COLOR_WHITE, "Vehicle Search:");

		new
			string[128];

		if(isnull(params)) return Error(playerid, "No keyword specified.");
		if(!params[2]) return Error(playerid, "Search keyword too short.");

		for(new v; v < sizeof(g_arrVehicleNames); v++)
		{
			if(strfind(g_arrVehicleNames[v], params, true) != -1) {

				if(isnull(string)) format(string, sizeof(string), "%s (ID %d)", g_arrVehicleNames[v], v+400);
				else format(string, sizeof(string), "%s | %s (ID %d)", string, g_arrVehicleNames[v], v+400);
			}
		}

		if(!string[0]) Error(playerid, "No results found.");
		else if(string[127]) Error(playerid, "Too many results found.");
		else SendClientMessageEx(playerid, COLOR_WHITE, string);

		SendClientMessageEx(playerid, COLOR_YELLOW, "--------------------------------------------------------------------------------------------------------------------------------");
	}
	else
	{
		PermissionError(playerid);
	}
	return 1;
}

CMD:owarn(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
	    return PermissionError(playerid);

	new player[24], tmp[50], PlayerName[MAX_PLAYER_NAME];
	if(sscanf(params, "s[24]s[50]", player, tmp))
		return Usage(playerid, "/owarn <name> <reason>");

	if(strlen(tmp) > 50) return Error(playerid, "Reason must be shorter than 50 characters.");

	foreach(new ii : Player)
	{
		GetPlayerName(ii, PlayerName, MAX_PLAYER_NAME);

	    if(strfind(PlayerName, player, true) != -1)
		{
			Error(playerid, "Player is online, you can use /warn on him.");
	  		return 1;
	  	}
	}
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id,warn FROM players WHERE username='%e'", player);
	mysql_tquery(g_SQL, query, "OWarnPlayer", "iss", playerid, player, tmp);
	return 1;
}

CMD:checkmask(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
	    return PermissionError(playerid);

	if(isnull(params) || strlen(params) > 24)
        return Usage(playerid, "/ocheckmask [mask number]");

	new query[512];
	format(query, sizeof(query), "SELECT `username` FROM `players` WHERE `MaskID` = '%d'", strval(params));
    mysql_tquery(g_SQL, query, "OnResolveMask","dd",playerid, strval(params));
	return 1;
}

CMD:ojail(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
	    return PermissionError(playerid);

	new player[24], datez, tmp[50], PlayerName[MAX_PLAYER_NAME];
	if(sscanf(params, "s[24]ds[50]", player, datez, tmp))
		return Usage(playerid, "/ojail <name> <time in minutes)> <reason>");

	if(strlen(tmp) > 50) return Error(playerid, "Reason must be shorter than 50 characters.");
	if(datez < 1 || datez > 60)
	{
 		if(pData[playerid][pAdmin] < 5)
   		{
			Error(playerid, "Jail time must remain between 1 and 60 minutes");
  			return 1;
   		}
	}
	foreach(new ii : Player)
	{
		GetPlayerName(ii, PlayerName, MAX_PLAYER_NAME);

	    if(strfind(PlayerName, player, true) != -1)
		{
			Error(playerid, "Player is online, you can use /jail on him.");
	  		return 1;
	  	}
	}
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", player);
	mysql_tquery(g_SQL, query, "OJailPlayer", "issi", playerid, player, tmp, datez);
	return 1;
}


CMD:jail(playerid, params[])
{
   	if(pData[playerid][pAdmin] < 1)
   		if(pData[playerid][pHelper] < 2)
     		return PermissionError(playerid);

	new reason[60], timeSec, otherid;
	if(sscanf(params, "uD(15)S(*)[60]", otherid, timeSec, reason))
	{
	    Usage(playerid, "/jail <ID/Name> <time in minutes> <reason>)");
	    return true;
	}

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	if(pData[otherid][pJail] > 0)
	{
	    Servers(playerid, "%s(%i) is already jailed (gets out in %d minutes)", ReturnName(otherid), otherid, pData[otherid][pJailTime]);
	    Info(playerid, "/unjail <ID/Name> to unjail.");
	    return true;
	}
	if(pData[otherid][pSpawned] == 0)
	{
	    Error(playerid, "%s(%i) isn't spawned!", ReturnName(otherid), otherid);
	    return true;
	}
	if(reason[0] != '*' && strlen(reason) > 60)
	{
	 	Error(playerid, "Reason too long! Must be smaller than 60 characters!");
	   	return true;
	}
	if(timeSec < 1 || timeSec > 60)
	{
	    if(pData[playerid][pAdmin] < 5)
	 	{
			Error(playerid, "Jail time must remain between 1 and 60 minutes");
	    	return 1;
	  	}
	}
	pData[otherid][pJail] = 1;
	pData[otherid][pJailTime] = timeSec * 60;
	ResetNameTag(otherid);
	JailPlayer(otherid);
	AddPlayerWarnsLog(playerid, pData[otherid][pID], reason, 1);
	if(reason[0] == '*')
	{
		SendClientMessageToAllEx(TOMATO, "AdmCmd: %s has jailed %s for %d minute(s).", pData[playerid][pAdminname], ReturnName(otherid), timeSec);
		SendClientMessageToAllEx(TOMATO, "Reason: %s", reason);
	}
	else
	{
		SendClientMessageToAllEx(TOMATO, "AdmCmd: %s has jailed %s for %d minute(s).", pData[playerid][pAdminname], ReturnName(otherid), timeSec);
		SendClientMessageToAllEx(TOMATO, "Reason: %s", reason);
	}
	return 1;
}

// has been released
CMD:unjail(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
   		if(pData[playerid][pHelper] < 2)
     		return PermissionError(playerid);

	new otherid, reason[128];
	if(sscanf(params, "us[128]", otherid, reason))
	{
	    Usage(playerid, "/unjail <ID/Name> [reason unjail]");
	    return true;
	}

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	if(pData[otherid][pJail] == 0)
	    return Error(playerid, "The player isn't in jail!");

	pData[otherid][pJail] = 0;
	pData[otherid][pJailTime] = 0;
	SetPlayerInterior(otherid, 0);
	SetPlayerVirtualWorld(otherid, 0);
	SetPlayerPos(otherid, 1529.6,-1691.2,13.3);
	SetPlayerSpecialAction(otherid, SPECIAL_ACTION_NONE);
	PlayerTextDrawHide(otherid, JailTD[playerid]);
	SendClientMessageToAllEx(TOMATO, "AdmCmd: %s has been released by %s from Admin Jail", ReturnName(otherid), pData[playerid][pAdminname]);
    SendClientMessageToAllEx(TOMATO, "Reason: %s", reason);
	return true;
}

CMD:kick(playerid, params[])
{
    static
        reason[128];

	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] == 0)
			return PermissionError(playerid);

	new otherid;
    if(sscanf(params, "us[128]", otherid, reason))
        return Usage(playerid, "/kick [playerid/PartOfName] [reason]");

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

    if(pData[otherid][pAdmin] > pData[playerid][pAdmin])
        return Error(playerid, "The specified player has higher authority.");

    SendClientMessageToAllEx(TOMATO, "AdmCmd: %s has been kicked by admin %s", ReturnName(otherid), pData[playerid][pAdminname]);
    SendClientMessageToAllEx(TOMATO, "AdmCmd: Reason: %s", reason);
	KickEx(otherid);

    return 1;
}

CMD:ban(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
			return PermissionError(playerid);

	new targetid, reason[128];
	if(sscanf(params, "us[128]", targetid, reason))
	{
	    Usage(playerid, "/ban [Playerid/Targetid] [Alasan membanned]");
	    return true;
	}
	if(!IsPlayerConnected(targetid))
        return Error(playerid, "Player tidak on!");
    SendClientMessageToAllEx(TOMATO, "AdmCmd: %s has been blocked by %s", ReturnName(targetid), pData[playerid][pAdminname]);
    SendClientMessageToAllEx(TOMATO, "Reason: %s", reason);
    format(pData[targetid][pBanBy], 128, "%s", pData[playerid][pAdminname]);
    format(pData[targetid][pBanReason], 128, "%s", reason);
	pData[targetid][pBanned] = 1;
	KickEx(targetid);
	return true;
}

CMD:oban(playerid, params[])
{
   	if(pData[playerid][pAdmin] < 1)
			return PermissionError(playerid);

	new tmp[24], reasonoban[128];
	if(sscanf(params, "s[24]s[128]", tmp, reasonoban))
	{
	    Usage(playerid, "/oban <ban name> <reason banned>");
	    return true;
	}
	new query[512];
	SendClientMessageToAllEx(TOMATO, "AdmCmd: %s has been banned by %s", tmp, pData[playerid][pAdminname]);
    SendClientMessageToAllEx(TOMATO, "Reason: %s", reasonoban);
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "ObanByIrwan", "iss", playerid, tmp, reasonoban);
	return 1;
}

CMD:omaxobject(playerid, params[])
{
   	if(pData[playerid][pAdmin] < 1)
			return PermissionError(playerid);

	new tmp[24], no;
	if(sscanf(params, "s[24]d", tmp, no))
	{
	    Usage(playerid, "/omaxobject <character name> <no>");
		Info(playerid, "0. Potato | 1. Low | 2. Normal | 3. High");
	    return true;
	}
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "oMaxObject", "isd", playerid, tmp, no);
	return 1;
}

CMD:verif(playerid, params[])
{
   	if(pData[playerid][pAdmin] < 1)
			return PermissionError(playerid);

	new tmp[24];
	if(sscanf(params, "s[24]s[128]", tmp))
	{
	    Usage(playerid, "/verif <name account>");
	    return true;
	}
	new query[512];
	SendStaffMessage(COLOR_RED, "AdmCmd: Admin %s telah mem verif account %s", pData[playerid][pAdminname], tmp);

	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "VerifAccount", "is", playerid, tmp);
	return 1;
}
CMD:unban(playerid, params[])
{
   	if(pData[playerid][pAdmin] < 1)
			return PermissionError(playerid);

	new tmp[24], reasonunban[128];
	if(sscanf(params, "s[24]s[128]", tmp, reasonunban))
	{
	    Usage(playerid, "/unban <ban name> <reason unbanned>");
	    return true;
	}
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "UnbanByIrwan", "iss", playerid, tmp, reasonunban);
	return 1;
}

CMD:warn(playerid, params[])
{
    static
        reason[32];

    if(pData[playerid][pAdmin] < 1)
        if(pData[playerid][pHelper] < 3)
			return PermissionError(playerid);
	new otherid;
    if(sscanf(params, "us[32]", otherid, reason))
        return Usage(playerid, "/warn [playerid/PartOfName] [reason]");

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

    if(pData[otherid][pAdmin] > pData[playerid][pAdmin])
        return Error(playerid, "The specified player has higher authority.");

	pData[otherid][pWarn]++;
	SendClientMessageToAllEx(TOMATO, "AdmCmd: %s has been warned by %s, total warning: %d", ReturnName(otherid), pData[playerid][pAdminname], pData[otherid][pWarn]);
    SendClientMessageToAllEx(TOMATO, "Reason: %s", reason, pData[otherid][pWarn]);
	new list[128];
	format(list, sizeof(list), "%s [Total Warning: %d/20]", reason, pData[otherid][pWarn]);
	AddPlayerWarnsLog(playerid, pData[otherid][pID], reason, 2);
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO warnrecord(owner, reason) VALUES ('%d', '%s')", pData[playerid][pID], list);
	mysql_tquery(g_SQL, query);
	
	return 1;
}

CMD:warns(playerid, params)
{
	ShowPlayerWarn(playerid);
	return 1;
}

ShowPlayerWarn(playerid)
{
	new query[512], list[4056], msg[1012];
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM warnrecord WHERE owner = '%d' ORDER BY id ASC", pData[playerid][pID]);
	mysql_query(g_SQL, query);
	new rows = cache_num_rows();
	if(rows)
	{
		format(list, sizeof(list), "Name\tReason\n");
		for(new i = 0; i < rows; i++)
		{
			cache_get_value_name(i, "reason", msg);
			format(list, sizeof(list), "%s%s\t%s\n", list, ReturnName(playerid), msg);
		}
		Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Warn History", list, "Close", "");
	}
	return 1;
}
CMD:unwarn(playerid, params[])
{
    if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] < 3)
			return PermissionError(playerid);
	new otherid, reason[128];
    if(sscanf(params, "us[128]", otherid, reason))
        return Usage(playerid, "/unwarn [playerid/PartOfName] [reason unwarn]");

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

    pData[otherid][pWarn] -= 1;
    SendClientMessageToAllEx(TOMATO, "AdmCmd: %s has reduced the warn %s, Total Warning: %d", pData[playerid][pAdminname], ReturnName(otherid), pData[otherid][pWarn]);
    SendClientMessageToAllEx(TOMATO, "Reason: %s", reason);
    return 1;
}

CMD:respawndmv(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] < 3)
			return PermissionError(playerid);

	if(IsVehicleEmpty(DmvVeh))
	{
		SetVehicleToRespawn(DmvVeh);
		SetValidVehicleHealth(DmvVeh, 2000);
		SetVehicleFuel(DmvVeh, 1000);
		SwitchVehicleDoors(DmvVeh, false);
	}
	SendStaffMessage(COLOR_RED, "AdmCmd: "AQUA_E"%s "YELLOW_E"has respawned dmv vehicles.", pData[playerid][pAdminname]);
	return 1;
}

CMD:respawnjobs(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] < 3)
			return PermissionError(playerid);

	for(new x;x<MAX_SWEEPER_VEHICLES; x++)
	{
		if(IsVehicleEmpty(SweepVeh[x]))
		{
			SetVehicleToRespawn(SweepVeh[x]);
			SetValidVehicleHealth(SweepVeh[x], 2000);
			SetVehicleFuel(SweepVeh[x], 1000);
			SwitchVehicleDoors(SweepVeh[x], false);
			DialogSweeper[x] = false; // Jadi ga ada yang punya nih dialog
		}
	}
	for(new xx;xx<MAX_BUSAB_VEHICLES;xx++)
	{
		if(IsVehicleEmpty(BusABVeh[xx]))
		{
			SetVehicleToRespawn(BusABVeh[xx]);
			SetValidVehicleHealth(BusABVeh[xx], 2000);
			SetVehicleFuel(BusABVeh[xx], 1000);
			SwitchVehicleDoors(BusABVeh[xx], false);
			DialogBus[xx] = false; // Jadi ga ada yang punya nih dialog
		}
	}
	for(new xx;xx<MAX_BUSCD_VEHICLES;xx++)
	{
		if(IsVehicleEmpty(BusCDVeh[xx]))
		{
			SetVehicleToRespawn(BusCDVeh[xx]);
			SetValidVehicleHealth(BusCDVeh[xx], 2000);
			SetVehicleFuel(BusCDVeh[xx], 1000);
			SwitchVehicleDoors(BusCDVeh[xx], false);
			DialogBus[xx] = false; // Jadi ga ada yang punya nih dialog
		}
	}
	for(new xx;xx<MAX_FORKLIFT_VEHICLES; xx++)
	{
		if(IsVehicleEmpty(ForkliftVeh[xx]))
		{
			SetVehicleToRespawn(ForkliftVeh[xx]);
			SetValidVehicleHealth(ForkliftVeh[xx], 2000);
			SetVehicleFuel(ForkliftVeh[xx], 1000);
			SwitchVehicleDoors(ForkliftVeh[xx], false);
		}
	}
	SendStaffMessage(COLOR_RED, "AdmCmd: "AQUA_E"%s "YELLOW_E"has respawned Jobs vehicles.", pData[playerid][pAdminname]);
	return 1;
}

RespawnNearbyVehicles(playerid, Float:radi)
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    for(new i=1; i<MAX_VEHICLES; i++)
    {
        if(GetVehicleModel(i))
        {
            new Float:posx, Float:posy, Float:posz;
            new Float:tempposx, Float:tempposy, Float:tempposz;
            GetVehiclePos(i, posx, posy, posz);
            tempposx = (posx - x);
            tempposy = (posy - y);
            tempposz = (posz - z);
            if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
            {
				if(IsVehicleEmpty(i))
				{
					SetTimerEx("RespawnPV", 3000, false, "d", i);
					SendClientMessageToAllEx(TOMATO, "AdmCmd: "AQUA_E"%s "YELLOW_E"telah merespawn kendaraan disekitar dengan radius "RED_E"%d.", pData[playerid][pAdminname], radi);
				}
			}
        }
    }
}

CMD:respawnrad(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	new rad;
	if(sscanf(params, "d", rad)) return Usage(playerid, "/respawnrad [radius] | respawn vehicle nearest");

	if(rad > 25000) return Error(playerid, "Maximal 25.000 radius");
	RespawnNearbyVehicles(playerid, rad);
	return 1;
}

//----------------------------[ Admin Level 2 ]-----------------------
CMD:sethp(playerid, params[])
{
	if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

	new jumlah, otherid;
	if(sscanf(params, "ud", otherid, jumlah))
        return Usage(playerid, "/sethp [playerid id/name] <jumlah>");

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	SetPlayerHealthEx(otherid, jumlah);
	SendStaffMessage(COLOR_RED, "AdmCmd: %s telah men set jumlah hp player %s", pData[playerid][pAdminname], ReturnName(otherid));
	Servers(otherid, "Admin %s telah men set hp anda", pData[playerid][pAdminname]);
	return 1;
}

CMD:aheal(playerid, params[])
{
    if(pData[playerid][pAdmin] < 1)
        return PermissionError(playerid);
    new otherid;
	if(sscanf(params, "u", otherid))
        return Usage(playerid, "/aheal [playerid id/name]");
    SetPlayerHealthEx(otherid, 115);
    SendClientMessageEx(playerid, COLOR_ARWIN, "HEAL: "WHITE_E"kamu telah berhasil meng-aheal player tersebut");
    SendClientMessageEx(otherid, COLOR_ARWIN, "HEAL: "WHITE_E"kamu telah di-aheal oleh admin");
    return 1;
}

CMD:resetfrating(playerid, params[])
{
    if(pData[playerid][pAdmin] < 1)
        return PermissionError(playerid);
    new otherid;
	if(sscanf(params, "u", otherid))
        return Usage(playerid, "/resetfrating [playerid id/name]");

	pData[otherid][pFitnessRating][0] = 100.0;
	pData[otherid][pFitnessRating][1] = 100.0;
	pData[otherid][pFitnessRating][2] = 100.0;
	pData[otherid][pFitnessRating][3] = 100.0;
	pData[otherid][pFitnessRating][4] = 100.0;
	pData[otherid][pFitnessRating][5] = 100.0;
	
    SendClientMessageEx(playerid, COLOR_ARWIN, "FRATING: "WHITE_E"kamu telah berhasil mereset fitness rating player tersebut");
    SendClientMessageEx(otherid, COLOR_ARWIN, "FRATING: "WHITE_E"kamu telah di-reset fitness rating oleh admin");
	return 1;
}

CMD:aarmor(playerid, params[])
{
    if(pData[playerid][pAdmin] < 5)
        return PermissionError(playerid);
    new otherid;
	if(sscanf(params, "u", otherid))
        return Usage(playerid, "/aarmor [playerid id/name]");
    SetPlayerArmourEx(otherid, 115);
    SendClientMessageEx(playerid, COLOR_ARWIN, "ARMOR: "WHITE_E"kamu telah berhasil meng-refill armour player tersebut");
    SendClientMessageEx(otherid, COLOR_ARWIN, "ARMOR: "WHITE_E"armour kamu telah berhasil di set oleh admin");
    return 1;
}

CMD:setam(playerid, params[])
{
	if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

	new jumlah, otherid;
	if(sscanf(params, "ud", otherid, jumlah))
        return Usage(playerid, "/setam [playerid id/name] <jumlah>");

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	if(jumlah > 95)
	{
		SetPlayerArmourEx(otherid, 98);
	}
	else
	{
		SetPlayerArmourEx(otherid, jumlah);
	}
	SendStaffMessage(COLOR_RED, "AdmCmd: %s telah men set jumlah armor player %s", pData[playerid][pAdminname], ReturnName(otherid));
	Servers(otherid, "Admin %s telah men set armor anda", pData[playerid][pAdminname]);
	return 1;
}

CMD:fixveh(playerid, params[])
{
	if(pData[playerid][pAdmin] < 2)
     		return PermissionError(playerid);

    if(IsPlayerInAnyVehicle(playerid))
	{
        SetValidVehicleHealth(GetPlayerVehicleID(playerid), 600);
		SetVehicleFuel(GetPlayerVehicleID(playerid), 600);
		ValidRepairVehicle(GetPlayerVehicleID(playerid));
        Servers(playerid, "Vehicle Fixed!");
    }
	else
	{
		Error(playerid, "Kamu tidak berada didalam kendaraan apapun!");
	}
	return 1;
}

CMD:setjob1(playerid, params[])
{
	if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

	new
        jobid,
		otherid;

	if(sscanf(params, "ud", otherid, jobid))
        return Usage(playerid, "/setjob1 [playerid/PartOfName] [jobid]");

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	if(jobid < 0 || jobid > 12)
        return Error(playerid, "Invalid ID. 0 - 11.");

	pData[otherid][pJob] = jobid;
	pData[otherid][pExitJob] = 0;

	Servers(playerid, "Anda telah menset job1 player %s(%d) menjadi %s(%d).", ReturnName(otherid), otherid, GetJobName(jobid), jobid);
	Servers(otherid, "Admin %s telah menset job1 anda menjadi %s(%d)", pData[playerid][pAdminname], GetJobName(jobid), jobid);
	return 1;
}

CMD:jobid(playerid, params[])
{
    if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    SendClientMessage(playerid, COLOR_ARWIN, "JOBID: 0 - "YELLOW_E"None");
    SendClientMessage(playerid, COLOR_ARWIN, "JOBID: 1 - "YELLOW_E"Taxi Driver");
    SendClientMessage(playerid, COLOR_ARWIN, "JOBID: 2 - "YELLOW_E"Mechanic");
    SendClientMessage(playerid, COLOR_ARWIN, "JOBID: 3 - "YELLOW_E"Lumber Jack");
    SendClientMessage(playerid, COLOR_ARWIN, "JOBID: 4 - "YELLOW_E"Trucker");
    SendClientMessage(playerid, COLOR_ARWIN, "JOBID: 5 - "YELLOW_E"Farmer");
    SendClientMessage(playerid, COLOR_ARWIN, "JOBID: 6 - "YELLOW_E"Arms Dealer");
    SendClientMessage(playerid, COLOR_ARWIN, "JOBID: 7 - "YELLOW_E"Drugs Dealer");
    SendClientMessage(playerid, COLOR_ARWIN, "JOBID: 8 - "YELLOW_E"Smuggle Dealer");
    SendClientMessage(playerid, COLOR_ARWIN, "JOBID: 9 - "YELLOW_E"Builder");
    return 1;
}

CMD:setjob2(playerid, params[])
{
	if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

	new
        jobid,
		otherid;

	if(sscanf(params, "ud", otherid, jobid))
        return Usage(playerid, "/setjob2 [playerid/PartOfName] [jobid]");

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	if(jobid < 0 || jobid > 12)
        return Error(playerid, "Invalid ID. 0 - 11.");

	pData[otherid][pJob2] = jobid;
	pData[otherid][pExitJob] = 0;

	Servers(playerid, "Anda telah menset job2 player %s(%d) menjadi %s(%d).", ReturnName(otherid), otherid, GetJobName(jobid), jobid);
	Servers(otherid, "Admin %s telah menset job2 anda menjadi %s(%d)", pData[playerid][pAdminname], GetJobName(jobid), jobid);
	return 1;
}

CMD:setskin(playerid, params[])
{
    new
        skinid,
		otherid;

    if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    if(sscanf(params, "ud", otherid, skinid))
        return Usage(playerid, "/skin [playerid/PartOfName] [skin id]");

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

    if(skinid < 0)
        return Error(playerid, "Invalid skin ID");

    SetPlayerSkin(otherid, skinid);
	pData[otherid][pSkin] = skinid;

    Servers(playerid, "You have set %s's skin to ID: %d.", ReturnName(otherid), skinid);
    Servers(otherid, "%s has set your skin to ID: %d.", ReturnName(playerid), skinid);
    return 1;
}

CMD:akill(playerid, params[])
{
    if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);
	new reason[60], otherid;
	if(sscanf(params, "uS(*)[60]", otherid, reason))
	{
	    Usage(playerid, "/akill <ID/Name> <optional: reason>");
	    return 1;
	}

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	SetPlayerHealth(otherid, 0.0);

	if(reason[0] != '*')
	{
		SendClientMessageToAllEx(TOMATO, "AdmCmd: Admin %s has killed %s [Reason: %s]", pData[playerid][pAdminname], ReturnName(otherid), reason);
	}
	else
	{
		SendClientMessageToAllEx(TOMATO, "AdmCmd: Admin %s has killed %s.", pData[playerid][pAdminname], ReturnName(otherid));
	}
	return 1;
}

CMD:ann(playerid, params[])
{
	if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

 	if(isnull(params))
    {
	    Usage(playerid, "/announce <msg>");
	    return 1;
	}
	// Check for special trouble-making input
   	if(strfind(params, "~x~", true) != -1)
		return Error(playerid, "~x~ is not allowed in announce.");
	if(strfind(params, "#k~", true) != -1)
		return Error(playerid, "The constant key is not allowed in announce.");
	if(strfind(params, "/q", true) != -1)
		return Error(playerid, "You are not allowed to type /q in announcement!");

	// Count tildes (uneven number = faulty input)
	new iTemp = 0;
	for(new i = (strlen(params)-1); i != -1; i--)
	{
		if(params[i] == '~')
			iTemp ++;
	}
	if(iTemp % 2 == 1)
		return Error(playerid, "You either have an extra ~ or one is missing in the announcement!");

	new str[512];
	format(str, sizeof(str), "~w~%s", params);
	GameTextForAll(str, 6500, 3);
	return true;
}

CMD:settime(playerid, params[])
{
    if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    new time;
    if(sscanf(params, "d", time))
    {
        Usage(playerid, "/time <time ID>");
        return true;
    }

    SendClientMessageToAllEx(TOMATO, "AdmCmd: Admin %s(%i) has changed the time to: %d", pData[playerid][pAdminname], playerid, time);

    // format(mstr, sizeof(mstr), "~r~Time changed: ~b~%d", time);
    // GameTextForAll(mstr, 3000, 5);

    SetWorldTime(time);
    foreach(new ii : Player)
    {
        SetPlayerTime(ii, time, 0);
    }
    return 1;
}
 
CMD:setweather(playerid, params[])
{
    new weatherid;

    if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    if(sscanf(params, "d", weatherid))
        return Usage(playerid, "/setweather [weather ID]");

    SetWeather(weatherid);
	current_weather = weatherid;
	foreach(new ii : Player)
	{
		SetPlayerWeather(ii, weatherid);
	}
    SetGVarInt("g_Weather", weatherid);
    SendClientMessageToAllEx(TOMATO,"AdmCmd: %s have changed the weather", pData[playerid][pAdminname]);
    Servers(playerid, "You have changed the weather to ID: %d.", weatherid);
    return 1;
}

CMD:gotoco(playerid, params[])
{
	if(pData[playerid][pAdmin] < 2)
		return PermissionError(playerid);

	new Float: pos[3], int;
	if(sscanf(params, "fffd", pos[0], pos[1], pos[2], int)) return Usage(playerid, "/gotoco [x coordinate] [y coordinate] [z coordinate] [interior]");

	Servers(playerid, "You have been teleported to the coordinates specified.");
	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	SetPlayerInterior(playerid, int);
	return 1;
}

CMD:cd(playerid)
{
	if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

	if(Count != -1) return Error(playerid, "There is already a countdown in progress, wait for it to end!");

	Count = 6;
	countTimer = SetTimer("pCountDown", 1000, 1);

	foreach(new ii : Player)
	{
		showCD[ii] = 1;
	}
	SendClientMessageToAllEx(TOMATO, "AdmCmd: Admin %s has started a global countdown!", pData[playerid][pAdminname]);
	return 1;
}

CMD:sethbe(playerid, params[])
{
	if(pData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

	new jumlah, otherid;
	if(sscanf(params, "ud", otherid, jumlah))
        return Usage(playerid, "/sethbe [playerid id/name] <jumlah>");

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	pData[otherid][pHunger] = jumlah;
	pData[otherid][pEnergy] = jumlah;
	//pData[otherid][pBladder] = jumlah;
	pData[otherid][pSick] = 0;
	SetPlayerDrunkLevel(playerid, 0);
	SendStaffMessage(COLOR_RED, "AdmCmd: %s telah men set jumlah hbe player %s", pData[playerid][pAdminname], ReturnName(otherid));
	Servers(otherid, "Admin %s telah men set HBE anda", pData[playerid][pAdminname]);
	return 1;
}

//----------------------------[ Admin Level 4 ]---------------
CMD:setname(playerid, params[])
{
	if(pData[playerid][pAdmin] < 4)
		return PermissionError(playerid);
	new otherid, tmp[20];
	if(sscanf(params, "is[20]", otherid, tmp))
	{
	   	Usage(playerid, "/setname <ID/Name> <newname>");
	    return 1;
	}
	if(!IsPlayerConnected(otherid)) return Error(playerid, "Player tidak on!");
	if(pData[otherid][IsLoggedIn] == false)	return Error(playerid, "That player is not logged in.");

	if(strlen(tmp) < 4) return Error(playerid, "New name can't be shorter than 4 characters!");
	if(strlen(tmp) > 20) return Error(playerid, "New name can't be longer than 20 characters!");

	if(!IsValidName(tmp)) return Error(playerid, "Name contains invalid characters, please doublecheck!");
	new query[248];
	mysql_format(g_SQL, query, sizeof(query), "SELECT username FROM players WHERE username='%s'", tmp);
	mysql_tquery(g_SQL, query, "SetName", "iis", otherid, playerid, tmp);
	return 1;
}

CMD:setgender(playerid, params[])
{
	if(pData[playerid][pAdmin] < 4)
		return PermissionError(playerid);	

	new gender, otherid;
	if(sscanf(params, "udd", otherid, gender))
	{
	    Usage(playerid, "/setgender <playerid> <1 = male || 2 = female>");
	    return true;
	}
	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");
	if(gender > 2)
		return Error(playerid, "Level can't be higher than 2!");
	if(gender < 1)
		return Error(playerid, "Level can't be lower than 0!");
	pData[otherid][pGender] = gender;	
	SendClientMessageEx(otherid, COLOR_ARWIN, "GENDER: "WHITE_E"Gender anda telah di ubah oleh Adm "YELLOW_E"%s", pData[playerid][pAdminname]);
	SendClientMessageEx(playerid, COLOR_ARWIN, "GENDER: "WHITE_E"Anda telah mengubah gender pemain "YELLOW_E"%s", ReturnName(otherid));
	return 1;
}

CMD:setvip(playerid, params[])
{
    if(pData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    new alevel, dayz, otherid, tmp[64];
    if(sscanf(params, "udd", otherid, alevel, dayz))
    {
        Usage(playerid, "/setdonatur <ID/Name> <level 0 - 4> <time (in days) 0 for permanent>");
        Info(playerid, "1.Basic Donatur 2.Advance Donatur 3.Professional Donatur 4.Lifetime Donatur");
        return true;
    }
    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");
    if(alevel > 4)
        return Error(playerid, "Level can't be higher than 3!");
    if(alevel < 0)
        return Error(playerid, "Level can't be lower than 0!");
    if(dayz < 0)
        return Error(playerid, "Time can't be lower than 0!");

    if(pData[otherid][IsLoggedIn] == false)
    {
        Error(playerid, "Player %s(%i) isn't logged in!", pData[otherid][pName], otherid);
        return true;
    }

    if(pData[playerid][pAdmin] < 5 && dayz > 7)
        return Error(playerid, "Anda hanya bisa menset 1 - 7 hari!");

    pData[otherid][pVip] = alevel;
    if(dayz == 0)
    {
        pData[otherid][pVipTime] = 0;
        SendClientMessageToAllEx(TOMATO, "Admcmd: Admin %s(%d) telah menset VIP kepada %s(%d) ke level %s permanent time!", pData[playerid][pAdminname], playerid, pData[otherid][pName], otherid, GetVipRank(otherid));
    }
    else
    {
        pData[otherid][pVipTime] = gettime() + (dayz * 86400);
        SendClientMessageToAllEx(TOMATO, "Admcmd: Admin %s(%d) telah menset VIP kepada %s(%d) selama %d hari ke level %s!", pData[playerid][pAdminname], playerid, pData[otherid][pName], otherid, dayz, GetVipRank(otherid));
    }

    format(tmp, sizeof(tmp), "%d(%d days)", alevel, dayz);
    StaffCommandLog("SETVIP", playerid, otherid, tmp);
    return 1;
}

CMD:giveweap(playerid, params[])
{
    static
        weaponid,
        ammount;

    new otherid, type = 0;
    if(pData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if(sscanf(params, "uddd", otherid, weaponid, type, ammount))
        return Usage(playerid, "/giveweap [playerid] [weaponid] [0. normal | 1. surplus [ammount]");

    if(otherid == INVALID_PLAYER_ID)
        return Error(playerid, "You cannot give weapons to disconnected players.");

    if(weaponid <= 0 || weaponid > 46 || (weaponid >= 19 && weaponid <= 21))
        return Error(playerid, "You have specified an invalid weapon.");

    GivePlayerWeaponEx(otherid, weaponid, ammount, type);
    Servers(playerid, "You have spawned a gun %s with %d ammo for %s", ReturnWeaponName(weaponid), ammount, ReturnName(otherid));
    return 1;
}

CMD:resetweap(playerid, params[])
{
	new otherid, weaponid;
	if(pData[playerid][pAdmin] < 3)
		return PermissionError(playerid);

	if(sscanf(params, "ud", otherid, weaponid))
		return Usage(playerid, "/resetweap [playerid] [weaponid]");

	if(otherid == INVALID_PLAYER_ID)
		return Error(playerid, "You cannot reset weapons of disconnected players.");

	ResetWeaponID(otherid, weaponid);
	Servers(playerid, "You have reset %s's %s.", ReturnName(otherid), ReturnWeaponName(weaponid));
	Servers(otherid, "%s has reset your %s.", ReturnName(playerid), ReturnWeaponName(weaponid));
	return 1;
}

CMD:setfaction(playerid, params[])
{
	new fid, rank, otherid, tmp[64];
    if(pData[playerid][pDivision] != 1) return Error(playerid, "You must be a faction division.");

    if(sscanf(params, "udd", otherid, fid, rank))
        return Usage(playerid, "/setfaction [playerid/PartOfName] [1.SAPD, 2.SAGS, 3.SAMD, 4.SANEW] [rank 1-6]");

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	if(pData[otherid][pFamily] != -1)
		return Error(playerid, "Player tersebut sudah bergabung family");

    if(fid < 0 || fid > 4)
        return Error(playerid, "You have specified an invalid faction ID 0 - 4.");

	if(rank < 1 || rank > 6)
        return Error(playerid, "You have specified an invalid rank 1 - 6.");

	if(fid == 0)
	{
		pData[otherid][pFaction] = 0;
		pData[otherid][pFactionRank] = 0;
		format(pData[playerid][pUnit], 24, "None");
		Servers(playerid, "You have removed %s's from faction.", ReturnName(otherid));
		Servers(otherid, "%s has removed your faction.", ReturnName(playerid));
	}
	else
	{
		pData[otherid][pFaction] = fid;
		pData[otherid][pFactionRank] = rank;
		Servers(playerid, "You have set %s's faction ID %d with rank %d.", ReturnName(otherid), fid, rank);
		Servers(otherid, "%s has set your faction ID to %d with rank %d.", ReturnName(playerid), fid, rank);
	}

	format(tmp, sizeof(tmp), "%d(%d rank)", fid, rank);
	StaffCommandLog("SETFACTION", playerid, otherid, tmp);
    return 1;
}

CMD:setleader(playerid, params[])
{
	new fid, otherid, tmp[64];
    if(pData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    if(sscanf(params, "ud", otherid, fid))
        return Usage(playerid, "/setleader [playerid/PartOfName] [0.None, 1.SAPD, 2.SAGS, 3.SAMD, 4.SANEW]");

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	if(pData[otherid][pFamily] != -1)
		return Error(playerid, "Player tersebut sudah bergabung family");

    if(fid < 0 || fid > 4)
        return Error(playerid, "You have specified an invalid faction ID 0 - 4.");

	if(fid == 0)
	{
		pData[otherid][pFaction] = 0;
		pData[otherid][pFactionLead] = 0;
		pData[otherid][pFactionRank] = 0;
		Servers(playerid, "You have removed %s's from faction leader.", ReturnName(otherid));
		Servers(otherid, "%s has removed your faction leader.", ReturnName(playerid));
	}
	else
	{
		pData[otherid][pFaction] = fid;
		pData[otherid][pFactionLead] = fid;
		pData[otherid][pFactionRank] = 6;
		Servers(playerid, "You have set %s's faction ID %d with leader.", ReturnName(otherid), fid);
		Servers(otherid, "%s has set your faction ID to %d with leader.", ReturnName(playerid), fid);
	}

	format(tmp, sizeof(tmp), "%d", fid);
	StaffCommandLog("SETLEADER", playerid, otherid, tmp);
    return 1;
}

CMD:takemoney(playerid, params[])
{
	if(pData[playerid][pAdmin] < 4)
		return PermissionError(playerid);

	new money, otherid;
	if(sscanf(params, "ud", otherid, money))
	{
	    Usage(playerid, "/takemoney <ID/Name> <amount>");
	    return true;
	}

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

 	if(money > pData[otherid][pMoney])
		return Error(playerid, "Player doesn't have enough money to deduct from!");

	GivePlayerMoneyEx(otherid, -money);
	SendClientMessageToAllEx(TOMATO, "Admcmd: Admin %s(%i) has taken away money $%s from $%s", pData[playerid][pAdminname], FormatMoney(money), ReturnName(otherid));
	return true;
}

CMD:takegold(playerid, params[])
{
	if(pData[playerid][pAdmin] < 4)
		return PermissionError(playerid);

	new gold, otherid;
	if(sscanf(params, "ud", otherid, gold))
	{
	    Usage(playerid, "/takegold <ID/Name> <amount>");
	    return true;
	}

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

 	if(gold > pData[otherid][pGold])
		return Error(playerid, "Player doesn't have enough gold to deduct from!");

	pData[otherid][pGold] -= gold;
	SendClientMessageToAllEx(TOMATO, "Admcmd: Admin %s(%i) has taken away gold %d from %s", pData[playerid][pAdminname], playerid, gold, ReturnName(otherid));
	return 1;
}

CMD:veh(playerid, params[])
{
    static
        model[32],
        color1,
        color2;

    if(pData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    if(sscanf(params, "s[32]I(0)I(0)", model, color1, color2))
        return Usage(playerid, "/veh [model id/name] <color 1> <color 2>");

    if((model[0] = GetVehicleModelByName(model)) == 0)
        return Error(playerid, "Invalid model ID.");

    static
        Float:x,
        Float:y,
        Float:z,
        Float:a,
        vehicleid;

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    vehicleid = CreateVehicle(model[0], x, y, z, a, color1, color2, 0);

    if(GetPlayerInterior(playerid) != 0)
        LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));

    if(GetPlayerVirtualWorld(playerid) != 0)
        SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));

    SetVehicleHealth(vehicleid, 2000);
    pvData[vehicleid][cTemporary] = true;
    SetVehicleFuel(vehicleid, 1000);
    SetVehicleNumberPlate(vehicleid, "STATIC");
    SwitchVehicleEngine(vehicleid, true);
    Servers(playerid, "You have spawned a %s (%d, %d).", GetVehicleNameByModel(model[0]), color1, color2);
    return 1;
}

CMD:dveh(playerid, params[])
{
    if(pData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    if(!isnull(params) && !strcmp(params, "all", true))
    {
        for (new i = 1, j = GetVehiclePoolSize(); i <= j; i ++) if(IsValidVehicle(i) && pvData[i][cTemporary])
        {
            pvData[i][cTemporary] = false;

            DestroyVehicle(i);
        }
        Servers(playerid, "You have destroyed the temporary vehicles.");
        return 1;
    }
    else if(IsPlayerInAnyVehicle(playerid))
    {
        new vehicleid = GetPlayerVehicleID(playerid);

        if(pvData[vehicleid][cTemporary])
        {
            pvData[vehicleid][cTemporary] = false;
            DestroyVehicle(vehicleid);
            Servers(playerid, "You have destroyed the temporary vehicles.");
        }
        else
        {
            Servers(playerid, "You cannot destroy a non-temporary vehicle.");
        }
    }
    return 1;
}

//-----------------------------[ Admin Level 5 ]------------------
CMD:sethelperlevel(playerid, params[])
{
	if(pData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

	new alevel, otherid, tmp[64];
	if(sscanf(params, "ud", otherid, alevel))
	{
	    Usage(playerid, "/sethelperlevel <ID/Name> <level 0 - 3>");
	    return true;
	}
	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");
	if(alevel > 3)
		return Error(playerid, "Level can't be higher than 3!");
	if(alevel < 0)
		return Error(playerid, "Level can't be lower than 0!");

	if(pData[otherid][IsLoggedIn] == false)
	{
		Error(playerid, "Player %s(%i) isn't logged in!", ReturnName(otherid), otherid);
		return true;
	}
	pData[otherid][pHelper] = alevel;
	Servers(playerid, "You has set helper level %s(%d) to level %d", ReturnName(otherid), otherid, alevel);
	Servers(otherid, "%s(%d) has set your helper level to %d", ReturnName(otherid), playerid, alevel);
	SendStaffMessage(COLOR_RED, "AdmWarn: Admin %s telah menset %s(%d) sebagai staff helper level %s(%d)",  pData[playerid][pAdminname], ReturnName(otherid), otherid, GetStaffRank(playerid), alevel);

	format(tmp, sizeof(tmp), "%d", alevel);
	StaffCommandLog("SETHELPERLEVEL", playerid, otherid, tmp);
	return 1;
}

CMD:setadminname(playerid, params[])
{
	if(pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);

	new aname[128], otherid, query[128];
	if(sscanf(params, "us[128]", otherid, aname))
	{
	    Usage(playerid, "/setadminname <ID/Name> <admin name>");
	    return true;
	}

	mysql_format(g_SQL, query, sizeof(query), "SELECT adminname FROM players WHERE adminname='%s'", aname);
	mysql_tquery(g_SQL, query, "a_ChangeAdminName", "iis", otherid, playerid, aname);
	return 1;
}

CMD:setmoney(playerid, params[])
{
	if(pData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

	new cash[32], otherid, tmp[64], totalcash[25];
	if(sscanf(params, "us[32", otherid, cash))
	{
	    Usage(playerid, "/setmoney <ID/Name> <money>");
	    return true;
	}
	format(totalcash, sizeof(totalcash), "%d00", strval(cash));
    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	ResetPlayerMoneyEx(otherid);
	GivePlayerMoneyEx(otherid, strval(totalcash));

	Servers(playerid, "Kamu telah mengset uang %s(%d) menjadi $%s!", ReturnName(otherid), otherid, FormatMoney(strval(totalcash)));
	Servers(otherid, "Admin %s telah mengset uang anda menjadi $%s!",pData[playerid][pAdminname], FormatMoney(strval(totalcash)));
	SendStaffMessage(TOMATO, ""YELLOW_E"[MONEY]: "RED_E"%s "WHITE_E"has set money "YELLOW_E"%s "WHITE_E"to "LG_E"$%s", pData[playerid][pAdminname], ReturnName(otherid), FormatMoney(strval(totalcash)));
	format(tmp, sizeof(tmp), "%d", strval(totalcash));
	StaffCommandLog("SETMONEY", playerid, otherid, tmp);
	return 1;
}

CMD:setbankmoney(playerid, params[])
{
	if(pData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

	new cash[32], otherid, tmp[64], totalcash[25];
	if(sscanf(params, "us[32", otherid, cash))
	{
	    Usage(playerid, "/setbankmoney <ID/Name> <money>");
	    return true;
	}
	format(totalcash, sizeof(totalcash), "%d00", strval(cash));
    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	pData[otherid][pBankMoney] = strval(totalcash);

	Servers(playerid, "Kamu telah mengset uang rekening banki %s(%d) menjadi $%s!", ReturnName(otherid), otherid, FormatMoney(strval(totalcash)));
	Servers(otherid, "Admin %s telah mengset uang rekening bank anda menjadi $%s!",pData[playerid][pAdminname], FormatMoney(strval(totalcash)));
	SendStaffMessage(TOMATO, ""YELLOW_E"[MONEY]: "RED_E"%s "WHITE_E"has set bank money "YELLOW_E"%s "WHITE_E"to "LG_E"$%s", pData[playerid][pAdminname], ReturnName(otherid), FormatMoney(strval(totalcash)));

	format(tmp, sizeof(tmp), "%d", strval(totalcash));
	StaffCommandLog("SETBANKMONEY", playerid, otherid, tmp);
	return 1;
}

CMD:setmaterial(playerid, params[])
{
	if(pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);

	new money, otherid, tmp[64];
	if(sscanf(params, "ud", otherid, money))
	{
	    Usage(playerid, "/setmaterial <ID/Name> <amount>");
	    return true;
	}

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	pData[otherid][pMaterial] = money;

	Servers(playerid, "Kamu telah menset material %s(%d) dengan jumlah %d!", ReturnName(otherid), otherid, money);
	Servers(otherid, "Admin %s telah menset material kepada anda dengan jumlah %d!", pData[playerid][pAdminname], money);

	format(tmp, sizeof(tmp), "%d", money);
	StaffCommandLog("SETMATERIAL", playerid, otherid, tmp);
	return 1;
}

CMD:setcomponent(playerid, params[])
{
	if(pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);

	new money, otherid, tmp[64];
	if(sscanf(params, "ud", otherid, money))
	{
	    Usage(playerid, "/setcomponent <ID/Name> <amount>");
	    return true;
	}

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	pData[otherid][pComponent] = money;

	Servers(playerid, "Kamu telah menset component %s(%d) dengan jumlah %d!", ReturnName(otherid), otherid, money);
	Servers(otherid, "Admin %s telah menset component kepada anda dengan jumlah %d!", pData[playerid][pAdminname], money);

	format(tmp, sizeof(tmp), "%d", money);
	StaffCommandLog("SETCOMPONENT", playerid, otherid, tmp);
	return 1;
}

// CMD:setcgun(playerid, params[])
// {
// 	if(pData[playerid][pAdmin] < 5)
// 		return PermissionError(playerid);

// 	new money, otherid, tmp[64];
// 	if(sscanf(params, "ud", otherid, money))
// 	{
// 	    Usage(playerid, "/setcgun <ID/Name> <amount>");
// 	    return true;
// 	}

//     if(!IsPlayerConnected(otherid))
//         return Error(playerid, "Player tidak on!");

// 	pData[otherid][pCgun] = money;

// 	Servers(playerid, "Kamu telah menset cgun %s(%d) dengan jumlah %d!", ReturnName(otherid), otherid, money);
// 	Servers(otherid, "Admin %s telah menset cgun kepada anda dengan jumlah %d!", pData[playerid][pAdminname], money);

// 	format(tmp, sizeof(tmp), "%d", money);
// 	StaffCommandLog("SETCGUN", playerid, otherid, tmp);
// 	return 1;
// }

CMD:explode(playerid, params[])
{
    if(pData[playerid][pAdmin] < 5)
        return PermissionError(playerid);
	new Float:POS[3], otherid, giveplayer[24];
	if(sscanf(params, "u", otherid))
	{
		Usage(playerid, "/explode <ID/Name>");
		return true;
	}

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	GetPlayerName(otherid, giveplayer, sizeof(giveplayer));

	Servers(playerid, "You have exploded %s(%i).", giveplayer, otherid);
	GetPlayerPos(otherid, POS[0], POS[1], POS[2]);
	CreateExplosion(POS[0], POS[1], POS[2], 7, 5.0);
	return true;
}

//--------------------------[ Admin Level 6 ]-------------------
CMD:setadminlevel(playerid, params[])
{
	if(pData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

	new alevel, otherid, tmp[64];
	if(sscanf(params, "ud", otherid, alevel))
	{
	    Usage(playerid, "/setadminlevel <ID/Name> <level 0 - 8>");
	    return true;
	}
	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");
	if(alevel > 8)
		return Error(playerid, "Level can't be higher than 8!");
	if(alevel < 0)
		return Error(playerid, "Level can't be lower than 0!");

	if(pData[otherid][IsLoggedIn] == false)
	{
		Error(playerid, "Player %s(%i) isn't logged in!", ReturnName(otherid), otherid);
		return true;
	}
	pData[otherid][pAdmin] = alevel;
	Servers(playerid, "You has set admin level %s(%d) to level %d", ReturnName(otherid), otherid, alevel);
	Servers(otherid, "%s(%d) has set your admin level to %d", ReturnName(otherid), playerid, alevel);

	format(tmp, sizeof(tmp), "%d", alevel);
	StaffCommandLog("SETADMINLEVEL", playerid, otherid, tmp);
	return 1;
}

CMD:setdivision(playerid, params[])
{
    if(pData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    new adivision, otherid, tmp[64];
    if(sscanf(params, "ud", otherid, adivision))
    {
        Usage(playerid, "/setdivision <ID/Name> [1.FACTIONS, 2.FAMILY, 3.PROPERTY, 4.REFFUND] <level 0 - 4>");
        return true;
    }
    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");
    if(adivision > 4)
        return Error(playerid, "Level can't be higher than 4!");
    if(adivision < 0)
        return Error(playerid, "Level can't be lower than 0!");

    if(pData[otherid][IsLoggedIn] == false)
    {
        Error(playerid, "Player %s(%i) isn't logged in!", ReturnName(otherid), otherid);
        return true;
    }
    pData[otherid][pDivision] = adivision;
    Servers(playerid, "You has set admin level %s(%d) to level %d", ReturnName(otherid), otherid, adivision);
    Servers(otherid, "%s(%d) has set your division level to %d", ReturnName(otherid), playerid, adivision);

    format(tmp, sizeof(tmp), "%d", adivision);
    StaffCommandLog("SETDIVISION", playerid, otherid, tmp);
    return 1;
}

CMD:setgold(playerid, params[])
{
    if(pData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    new gold, otherid, tmp[64];
    if(sscanf(params, "ud", otherid, gold))
    {
        Usage(playerid, "/setcoin <ID/Name> <Coin>");
        return true;
    }

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

    pData[otherid][pGold] = gold;

    Servers(playerid, "Kamu telah menset coin %s(%d) dengan jumlah %d!", pData[otherid][pName], otherid, gold);
    Servers(otherid, "Admin %s telah menset coin kepada anda dengan jumlah %d!", pData[playerid][pAdminname], gold);

    format(tmp, sizeof(tmp), "%d", gold);
    StaffCommandLog("SETGOLD", playerid, otherid, tmp);
    return 1;
}

CMD:givegold(playerid, params[])
{
    if(pData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    new gold, otherid, tmp[64];
    if(sscanf(params, "ud", otherid, gold))
    {
        Usage(playerid, "/givecoin <ID/Name> <Coin>");
        return true;
    }

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

    pData[otherid][pGold] += gold;

    Servers(playerid, "Kamu telah memberikan coin %s(%d) dengan jumlah %d!", pData[otherid][pName], otherid, gold);
    Servers(otherid, "Admin %s telah memberikan coin kepada anda dengan jumlah %d!", pData[playerid][pAdminname], gold);

    format(tmp, sizeof(tmp), "%d", gold);
    StaffCommandLog("GIVEGOLD", playerid, otherid, tmp);
    return 1;
}

// CMD:setgold(playerid, params[])
// {
// 	if(pData[playerid][pAdmin] < 6)
// 		return PermissionError(playerid);

// 	new gold, otherid, tmp[64];
// 	if(sscanf(params, "ud", otherid, gold))
// 	{
// 	    Usage(playerid, "/setgold <ID/Name> <gold>");
// 	    return true;
// 	}

//     if(!IsPlayerConnected(otherid))
//         return Error(playerid, "Player tidak on!");

// 	pData[otherid][pGold] = gold;

// 	Servers(playerid, "Kamu telah menset gold %s(%d) dengan jumlah %d!", ReturnName(otherid), otherid, gold);
// 	Servers(otherid, "Admin %s telah menset gold kepada anda dengan jumlah %d!", pData[playerid][pAdminname], gold);

// 	format(tmp, sizeof(tmp), "%d", gold);
// 	StaffCommandLog("SETGOLD", playerid, otherid, tmp);
// 	return 1;
// }

// CMD:givegold(playerid, params[])
// {
// 	if(pData[playerid][pAdmin] < 6)
// 		return PermissionError(playerid);

// 	new gold, otherid, tmp[64];
// 	if(sscanf(params, "ud", otherid, gold))
// 	{
// 	    Usage(playerid, "/givegold <ID/Name> <gold>");
// 	    return true;
// 	}

//     if(!IsPlayerConnected(otherid))
//         return Error(playerid, "Player tidak on!");

// 	pData[otherid][pGold] += gold;

// 	Servers(playerid, "Kamu telah memberikan gold %s(%d) dengan jumlah %d!", ReturnName(otherid), otherid, gold);
// 	Servers(otherid, "Admin %s telah memberikan gold kepada anda dengan jumlah %d!", pData[playerid][pAdminname], gold);

// 	format(tmp, sizeof(tmp), "%d", gold);
// 	StaffCommandLog("GIVEGOLD", playerid, otherid, tmp);
// 	return 1;
// }

CMD:setstock(playerid, params[])
{
	if(pData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

	new name[64], string[128];
	if(sscanf(params, "s[64]S()[128]", name, string))
    {
        Usage(playerid, "/setstock [name] [stock]");
        SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} [material], [component], [fish]");
        return 1;
    }
	if(!strcmp(name, "material", true))
    {
		new stok;
        if(sscanf(string, "d", stok))
            return Usage(playerid, "/setstok [material] [stok]");

        if(stok < 0 || stok > 1000000)
            return Error(playerid, "You must specify at least 0 or 1.000.000");

        StockMaterial = stok;
		Server_Save();
        SendAdminMessage(COLOR_RED, "AdmWarn: %s set material to %d.", pData[playerid][pAdminname], stok);
    }
    else if(!strcmp(name, "marijuana", true))
    {
		new stok;
        if(sscanf(string, "d", stok))
            return Usage(playerid, "/setstok [marijuana] [stok]");

        if(stok < 0 || stok > 1000000)
            return Error(playerid, "You must specify at least 0 or 1.000.000.");

        StockMarijuana = stok;
		Server_Save();
		//Info(playerid, "Kamu telah menset stock marijuana menjadi %d", stok);
		SendAdminMessage(COLOR_RED, "AdmWarn: %s set skill mechanic player %s.", pData[playerid][pAdminname], stok);
    }
	else if(!strcmp(name, "component", true))
    {
		new stok;
        if(sscanf(string, "d", stok))
            return Usage(playerid, "/setstok [component] [stok]");

        if(stok < 0 || stok > 1000000)
            return Error(playerid, "You must specify at least 0 or 1.000.000.");

        StockComponent = stok;
		Server_Save();
        SendAdminMessage(COLOR_RED, "AdmWarn: %s set component to %d.", pData[playerid][pAdminname], stok);
    }
	return 1;
}

CMD:kickall(playerid, params[])
{
	if(pData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

	foreach(new pid : Player)
	{
		if(pid != playerid)
		{
			UpdatePlayerData(pid);
			RemovePlayerVehicle(playerid);
			Servers(pid, "Sorry, server will be maintenance and your data have been saved.");
			KickEx(pid);
		}
	}
	return 1;
}

CMD:setpassword(playerid, params[])
{
	if(pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);

	new cname[21], query[128], pass[65], tmp[64];
	if(sscanf(params, "s[21]s[20]", cname, pass))
	{
	    Usage(playerid, "/setpassword <ucp> <new password>");
	    Info(playerid, "Make sure you enter the ucp name and not ID!");
	   	return 1;
	}

	mysql_format(g_SQL, query, sizeof(query), "SELECT password FROM ucp WHERE username='%s'", cname);
	mysql_tquery(g_SQL, query, "ChangePlayerPassword", "iss", playerid, cname, pass);

	format(tmp, sizeof(tmp), "%s", pass);
	StaffCommandLog("SETPASSWORD", playerid, INVALID_PLAYER_ID, tmp);
	return 1;
}

CMD:mutewt(playerid, params[])
{
	if(pData[playerid][pAdmin] < 2)
		return PermissionError(playerid);

	new gold, otherid;
	if(sscanf(params, "ud", otherid, gold))
	{
	    Usage(playerid, "/mutewt <name> <minute>");
	    return true;
	}

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	pData[otherid][pMuteWt] = gold;
	SendStaffMessage(TOMATO, "AdmCmd: Admin %s telah mute walkie talkie player %s selama %d menit.", pData[playerid][pAdminname], ReturnName(otherid), pData[otherid][pMuteWt]);
	Info(otherid, ""GREY2_E"Admin %s telah mute walkie talkie anda selama %d menit", pData[playerid][pAdminname], pData[otherid][pMuteWt]);
	return 1;
}

CMD:unmuteewt(playerid, params[])
{
	if(pData[playerid][pAdmin] < 2)
		return PermissionError(playerid);

	new otherid;
	if(sscanf(params, "u", otherid))
	{
	    Usage(playerid, "/unmuteewt <name>");
	    return true;
	}

    if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");

	pData[otherid][pMuteWt] = 0;
	SendStaffMessage(TOMATO, "AdmCmd: Admin %s telah unmute walkie talkie player %s", pData[playerid][pAdminname], ReturnName(otherid));
	Info(otherid, ""GREY2_E"Admin %s telah unmute walkie talkie anda", pData[playerid][pAdminname]);	
	return 1;
}

CMD:eo(playerid, params[])
{
	if(pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);
	SelectObject(playerid);
	pData[playerid][pEditSelect] = 4;
	return 1;
}

CMD:offlamp(playerid, params[])
{
	if(pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);
	foreach(new i : Player)
	{
		PlayerTextDrawHide(i, OffLamp[i]);
	}
	Info(playerid, "Textdraw hide");
	return 1;
}

CMD:onlamp(playerid, params[])
{
	if(pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);
	foreach(new i : Player)
	{
		PlayerTextDrawShow(i, OffLamp[i]);
	}
	Info(playerid, "Textdraw Show");
	return 1;
}

CMD:getucp(playerid, params[])
{
    if(pData[playerid][pAdmin] < 1) return PermissionError(playerid);
    {
        new name;
		if(sscanf(params, "u", name)) return Usage(playerid, "/getucp [playerid]");
		{
			if(IsPlayerConnected(name))
			{
				SendClientMessageEx(playerid, COLOR_ARWIN, "UCP: "YELLOW_E"Character: {00FFFF}%s(pid: %d) "YELLOW_E"UCP: {00FFFF}%s(pid: %d)", ReturnName(name), pData[name][pID], charData[name][cName], charData[name][cID]);
			}
		}
	}
	return 1;
}

CMD:ogetucp(playerid, params[])
{
   	if(pData[playerid][pAdmin] < 1)
			return PermissionError(playerid);

	new tmp[24];
	if(sscanf(params, "s[24]", tmp))
	{
	    Usage(playerid, "/ogetucp <name player>");
	    return true;
	}
	new query[255], Cache: cache, nameucp[32], id;
	mysql_format(g_SQL, query, sizeof query, "SELECT * FROM `players` WHERE `username` = '%e' LIMIT 1", tmp);
	cache = mysql_query(g_SQL, query);
	if(!cache_num_rows()) return 0;
	for(new i; i < cache_num_rows(); i++) {

        cache_get_value_name(i, "ucpname", nameucp);
		cache_get_value_name_int(i, "reg_id", id);	
		SendClientMessageEx(playerid, COLOR_ARWIN, "UCP: "YELLOW_E"Character: {00FFFF}%s(pid: %d) "YELLOW_E"UCP: {00FFFF}%s", tmp, id, nameucp);
	}
	cache_delete(cache);
	return 1;
}

CMD:getchar(playerid, params[])
{
   	if(pData[playerid][pAdmin] < 1)
			return PermissionError(playerid);

	new tmp[24];
	if(sscanf(params, "s[24]", tmp))
	{
	    Usage(playerid, "/getchar <UCP Name>");
	    return true;
	}
	new query[103];
	mysql_format(g_SQL, query, sizeof query, "SELECT * FROM `ucp` WHERE `username` = '%e' LIMIT 1", tmp);
	mysql_pquery(g_SQL, query, "GetNameUCP12", "is", playerid, tmp);
	return 1;
}

CMD:unbanucp(playerid, params[])
{
   	if(pData[playerid][pAdmin] < 1)
			return PermissionError(playerid);

	new tmp[24];
	if(sscanf(params, "s[24]", tmp))
	{
	    Usage(playerid, "/unbanucp <Name UCP>");
	    return true;
	}
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM ucp WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "oUnBanUCP", "is", playerid, tmp);
	return 1;
}

CMD:ounbanucp(playerid, params[])
{
   	if(pData[playerid][pAdmin] < 1)
			return PermissionError(playerid);

	new tmp[24];
	if(sscanf(params, "s[24]", tmp))
	{
	    Usage(playerid, "/ounbanucp <Name UCP>");
	    return true;
	}
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM ucp WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "oUnBanUCP", "is", playerid, tmp);
	return 1;
}

CMD:banucp(playerid, params[])
{
   	if(pData[playerid][pAdmin] < 1)
			return PermissionError(playerid);

	new tmp[24], reasonoban[128];
	if(sscanf(params, "s[24]s[128]", tmp, reasonoban))
	{
	    Usage(playerid, "/banucp <Name UCP> <reason>");
	    return true;
	}
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM ucp WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "oBanUCP", "iss", playerid, tmp, reasonoban);
	return 1;
}

CMD:obanucp(playerid, params[])
{
   	if(pData[playerid][pAdmin] < 1)
			return PermissionError(playerid);

	new tmp[24], reasonoban[128];
	if(sscanf(params, "s[24]s[128]", tmp, reasonoban))
	{
	    Usage(playerid, "/obanucp <Name UCP> <reason>");
	    return true;
	}
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM ucp WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "oBanUCP", "iss", playerid, tmp, reasonoban);
	return 1;
}

CMD:randompricefish(playerid, params[])
{
	FishPrice = Random(450, 800);
	
	new String3[212];
	format(String3,sizeof(String3),""PINK_E"Fish Factory\n{FFFFFF}Fish Price: \n"GREEN_E"$%s"WHITE_E"/lb", FormatMoney(FishPrice));
	SetDynamicObjectMaterialText(SELLFISH, 0, String3, 130, "Arial", 40, 1, 0xFFFFFFFF, 0xFF000000, 1);
	format(String3,sizeof(String3),""PINK_E"Las Barrancas\nFish Factory\n{FFFFFF}Fish Price: \n"GREEN_E"$%s"WHITE_E"/lb", FormatMoney(FishPrice));
	SetDynamicObjectMaterialText(SELLFISH2, 1, String3, 130, "Arial", 48, 1, -65366, -16777216, 1);
    return 1;
}

// Bizz System
CMD:bizinterior(playerid, params[])
{
	if(pData[playerid][pAdmin] > 5) Dialog_Show(playerid, BussinesINT, DIALOG_STYLE_LIST, "Businesses Interiors Categories","24/7's\nFast Foods Interiors\nResturants & Clubs\nAmmunation Interiors\nCasino Interiors\nElectronics Stores Interiors\nClothes Stores Interiors\nRandom usefull Interiors", "Select", "Cancel");
	return 1;
}


