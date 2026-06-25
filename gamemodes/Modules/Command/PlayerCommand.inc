//-------------[ Player Commands ]-------------//
SuitChoiceFromText(const text[])
{
	if(!strcmp(text, "batu", true) || !strcmp(text, "rock", true) || !strcmp(text, "b", true)) return 1;
	if(!strcmp(text, "gunting", true) || !strcmp(text, "scissors", true) || !strcmp(text, "g", true)) return 2;
	if(!strcmp(text, "kertas", true) || !strcmp(text, "paper", true) || !strcmp(text, "k", true)) return 3;
	return 0;
}

SuitChoiceName(choice)
{
	static name[8];

	switch(choice)
	{
		case 1: format(name, sizeof(name), "batu");
		case 2: format(name, sizeof(name), "gunting");
		case 3: format(name, sizeof(name), "kertas");
		default: format(name, sizeof(name), "-");
	}
	return name;
}

SuitClear(playerid)
{
	DeletePVar(playerid, "SuitFrom");
	DeletePVar(playerid, "SuitTo");
	DeletePVar(playerid, "SuitChoice");
	DeletePVar(playerid, "SuitExpire");
	return 1;
}

SuitWinner(challengerChoice, targetChoice)
{
	if(challengerChoice == targetChoice) return 0;
	if((challengerChoice == 1 && targetChoice == 2) || (challengerChoice == 2 && targetChoice == 3) || (challengerChoice == 3 && targetChoice == 1)) return 1;
	return 2;
}

CMD:suit(playerid, params[])
{
	new arg[32], choiceText[16];

	if(sscanf(params, "s[32]S()[16]", arg, choiceText))
	{
		Usage(playerid, "/suit [playerid] [batu/gunting/kertas]");
		Usage(playerid, "/suit accept [batu/gunting/kertas] | /suit deny | /suit cancel");
		return 1;
	}

	if(!strcmp(arg, "accept", true))
	{
		new challengerid = GetPVarInt(playerid, "SuitFrom");
		new challengerChoice = GetPVarInt(playerid, "SuitChoice");
		new targetChoice = SuitChoiceFromText(choiceText);

		if(!GetPVarType(playerid, "SuitFrom")) return Error(playerid, "Tidak ada tantangan suit yang masuk.");
		if(!targetChoice) return Usage(playerid, "/suit accept [batu/gunting/kertas]");
		if(!IsPlayerConnected(challengerid))
		{
			SuitClear(playerid);
			return Error(playerid, "Player yang menantang sudah tidak terhubung.");
		}
		if(gettime() > GetPVarInt(playerid, "SuitExpire"))
		{
			SuitClear(challengerid);
			SuitClear(playerid);
			return Error(playerid, "Tantangan suit sudah kadaluarsa.");
		}
		if(!NearPlayer(playerid, challengerid, 5.0))
		{
			SuitClear(challengerid);
			SuitClear(playerid);
			return Error(playerid, "Kamu harus dekat dengan player yang menantang suit.");
		}
		if(pData[playerid][pInjured] || pData[challengerid][pInjured])
		{
			SuitClear(challengerid);
			SuitClear(playerid);
			return Error(playerid, "Suit dibatalkan karena salah satu player sedang injured.");
		}

		new winner = SuitWinner(challengerChoice, targetChoice);
		new challengerChoiceName[8], targetChoiceName[8];
		format(challengerChoiceName, sizeof(challengerChoiceName), "%s", SuitChoiceName(challengerChoice));
		format(targetChoiceName, sizeof(targetChoiceName), "%s", SuitChoiceName(targetChoice));

		SendClientMessageEx(challengerid, COLOR_ARWIN, "SUIT: "WHITE_E"%s memilih %s, %s memilih %s.", ReturnName2(challengerid), challengerChoiceName, ReturnName2(playerid), targetChoiceName);
		SendClientMessageEx(playerid, COLOR_ARWIN, "SUIT: "WHITE_E"%s memilih %s, %s memilih %s.", ReturnName2(challengerid), challengerChoiceName, ReturnName2(playerid), targetChoiceName);

		if(!winner)
		{
			SendClientMessageEx(challengerid, COLOR_ARWIN, "SUIT: "WHITE_E"Hasil seri.");
			SendClientMessageEx(playerid, COLOR_ARWIN, "SUIT: "WHITE_E"Hasil seri.");
			SendNearbyMessage(challengerid, 15.0, COLOR_PURPLE, "** Hasil suit %s melawan %s seri. (%s vs %s)", ReturnName2(challengerid), ReturnName2(playerid), challengerChoiceName, targetChoiceName);
		}
		else if(winner == 1)
		{
			SendClientMessageEx(challengerid, COLOR_ARWIN, "SUIT: "WHITE_E"Kamu menang melawan %s.", ReturnName2(playerid));
			SendClientMessageEx(playerid, COLOR_ARWIN, "SUIT: "WHITE_E"Kamu kalah melawan %s.", ReturnName2(challengerid));
			SendNearbyMessage(challengerid, 15.0, COLOR_PURPLE, "** Hasil suit: %s menang melawan %s. (%s vs %s)", ReturnName2(challengerid), ReturnName2(playerid), challengerChoiceName, targetChoiceName);
		}
		else
		{
			SendClientMessageEx(challengerid, COLOR_ARWIN, "SUIT: "WHITE_E"Kamu kalah melawan %s.", ReturnName2(playerid));
			SendClientMessageEx(playerid, COLOR_ARWIN, "SUIT: "WHITE_E"Kamu menang melawan %s.", ReturnName2(challengerid));
			SendNearbyMessage(challengerid, 15.0, COLOR_PURPLE, "** Hasil suit: %s menang melawan %s. (%s vs %s)", ReturnName2(playerid), ReturnName2(challengerid), targetChoiceName, challengerChoiceName);
		}

		SuitClear(challengerid);
		SuitClear(playerid);
		return 1;
	}
	else if(!strcmp(arg, "deny", true))
	{
		new challengerid = GetPVarInt(playerid, "SuitFrom");

		if(!GetPVarType(playerid, "SuitFrom")) return Error(playerid, "Tidak ada tantangan suit yang masuk.");
		if(IsPlayerConnected(challengerid))
		{
			SendClientMessageEx(challengerid, COLOR_ARWIN, "SUIT: "WHITE_E"%s menolak tantangan suit kamu.", ReturnName2(playerid));
			SuitClear(challengerid);
		}
		SendClientMessageEx(playerid, COLOR_ARWIN, "SUIT: "WHITE_E"Kamu menolak tantangan suit.");
		SuitClear(playerid);
		return 1;
	}
	else if(!strcmp(arg, "cancel", true))
	{
		new targetid = GetPVarInt(playerid, "SuitTo");

		if(!GetPVarType(playerid, "SuitTo")) return Error(playerid, "Kamu tidak memiliki tantangan suit yang aktif.");
		if(IsPlayerConnected(targetid))
		{
			SendClientMessageEx(targetid, COLOR_ARWIN, "SUIT: "WHITE_E"%s membatalkan tantangan suit.", ReturnName2(playerid));
			SuitClear(targetid);
		}
		SendClientMessageEx(playerid, COLOR_ARWIN, "SUIT: "WHITE_E"Kamu membatalkan tantangan suit.");
		SuitClear(playerid);
		return 1;
	}

	new targetid, challengeChoiceText[16];
	if(sscanf(params, "us[16]", targetid, challengeChoiceText)) return Usage(playerid, "/suit [playerid] [batu/gunting/kertas]");

	new choice = SuitChoiceFromText(challengeChoiceText);
	if(!choice)
	{
		Usage(playerid, "/suit [playerid] [batu/gunting/kertas]");
		return 1;
	}
	if(targetid == INVALID_PLAYER_ID || !IsPlayerConnected(targetid)) return Error(playerid, "Player tidak ditemukan.");
	if(targetid == playerid) return Error(playerid, "Kamu tidak bisa suit dengan diri sendiri.");
	if(!NearPlayer(playerid, targetid, 5.0)) return Error(playerid, "Kamu harus dekat dengan player tersebut.");
	if(pData[playerid][pInjured] || pData[targetid][pInjured]) return Error(playerid, "Player injured tidak bisa bermain suit.");

	if(GetPVarType(playerid, "SuitTo"))
	{
		new oldTarget = GetPVarInt(playerid, "SuitTo");
		if(IsPlayerConnected(oldTarget) && GetPVarInt(oldTarget, "SuitExpire") >= gettime()) return Error(playerid, "Kamu masih memiliki tantangan suit aktif. Gunakan /suit cancel.");
		SuitClear(playerid);
		if(IsPlayerConnected(oldTarget)) SuitClear(oldTarget);
	}
	if(GetPVarType(targetid, "SuitFrom"))
	{
		new oldChallenger = GetPVarInt(targetid, "SuitFrom");
		if(GetPVarInt(targetid, "SuitExpire") >= gettime()) return Error(playerid, "Player tersebut masih memiliki tantangan suit aktif.");
		SuitClear(targetid);
		if(IsPlayerConnected(oldChallenger)) SuitClear(oldChallenger);
	}

	SetPVarInt(playerid, "SuitTo", targetid);
	SetPVarInt(targetid, "SuitFrom", playerid);
	SetPVarInt(targetid, "SuitChoice", choice);
	SetPVarInt(targetid, "SuitExpire", gettime() + 60);

	SendClientMessageEx(playerid, COLOR_ARWIN, "SUIT: "WHITE_E"Kamu menantang %s. Tunggu dia menggunakan /suit accept [batu/gunting/kertas].", ReturnName2(targetid));
	SendClientMessageEx(targetid, COLOR_ARWIN, "SUIT: "WHITE_E"%s menantang kamu suit. Gunakan /suit accept [batu/gunting/kertas] atau /suit deny.", ReturnName2(playerid));
	SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "** %s mengajak %s bermain suit.", ReturnName2(playerid), ReturnName2(targetid));
	return 1;
}

/*CMD:changelog(playerid)
{
    Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "NEW UPDATES", ""WHITE"Available update on {9ACD32} v0.3.2d"WHITE"\n\n \
        "GREEN"Added:"WHITE"\n\
        |- Flat System with structures and furnitures system\n\
        |- Copy structure and store furniture with select object for Builder\n\
        |- Command alias for vehicle commands\n\
        |- Add protection when player logged with same ucp\n\
        |- Add object mapping for per business\n\
        |- `/searchtexture` to check available texture for Builder\n\
        |- Last suspect information on Speed Camera\n\n\
        "LIGHTBLUE"Changed:"WHITE"\n\
        |- Server version to 0.3.7-R2 before 0.3.DL\n\
        |- Auto roleplay `/me` changed to `/ame`\n\
        |- Change list of weather IDs\n\
        |- Updates anticheat settings\n\
        |- Decreased all mapping streamer distance\n\
        |- House structure & furniture also veh trunk load system\n\n\
        "RED"Bug fixed/Deleted:"WHITE"\n\
        |- Fix Furniture, structure house texture\n\
        |- Fix Streamer settings or `/maxobject`\n\
        |- Fix World time for player\n\
        |- Delete Apartment System\n\
        |- Delete Unused mapping\n\n\
        ""WHITE"* Untuk informasi lebih lanjut silahkan kunjungi Discord kami di www.crimson.com","Close","","
    );

    return 1;
}*/

/*ShowChangelog(playerid)
{
	static string[1024];
	if(IsNull(string))
	{
		strcat(string, "Change Notes \""TEXT_GAMEMODE"\"":\n\n"WHITE_E",sizeof(string))
		strcat(string, "1. [ADD] Add command '/mark' & '/gotomark'\n",sizeof(string))
		strcat(string, "2. [ADD] Add command '/togglename' for hide nametag\n",sizeof(string))
	}
}*/

/*CMD:changelog(playerid)
{
	new
		str[4096]
	;

	format(str, sizeof str, "Changelogs v0.3.4d Thousand\n", str);
	
	format(str, sizeof str, "%s\n\n{FFFF00}[Changes & Updates]{FFFFFF}\n", str);

	format(str, sizeof str, "%s[+] Added mapping Sweeper\n", str);
	format(str, sizeof str, "%s[+] Added mapping rockshore bridge - palomino\n", str);
	format(str, sizeof str, "%s[+] Changed SAPD Interior\n", str);

	format(str, sizeof str, "%s\n\n{FFFF00}[Fixes & Improvements]{FFFFFF}\n", str);


	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Server Changelogs", str, "Back", "");
	return 1;
}*/

CMD:starterpack(playerid)
{
	if(pData[playerid][pStarterPack] == 1) return Error(playerid, "You have already claimed your starter pack!");
	GivePlayerMoneyEx(playerid, 100000);
	
	new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(playerid);
	if(count >= limit)
	{
		Error(playerid, "Slot kendaraan anda sudah penuh, silahkan jual beberapa kendaraan anda terlebih dahulu!");
		return 1;
	}

	new cQuery[1024];
	new Float:x,Float:y,Float:z, Float:a;
	new model, color1, color2;
	color1 = 1;
	color2 = 6;
	model = 422;
	x = 2633.7461;
	y = -2224.4370;
	z = 16.2871;
	a = 89.5940;
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[playerid][pID], model, color1, color2, 0, x, y, z, a);
	mysql_tquery(g_SQL, cQuery, "OnVehStarterpack", "dddddffff", playerid, pData[playerid][pID], model, color1, color2, x, y, z, a);

	pData[playerid][pStarterPack] = 1;
	SendClientMessageEx(playerid, COLOR_GREEN, "You've claimed your starter pack! You got $1,000.00 and a free car, enjoy!");
	return 1;
}

CMD:ds(playerid, params[])
{
    if(isnull(params))
        return Usage(playerid, "/ds (door shout) [text]");

    new id = -1;

    if ((id = House_Nearest(playerid)) != -1) 
    {
        foreach (new i : Player) if(House_Inside(i) == id) 
        {
            SendClientMessageEx(i, COLOR_GREY, "%s shouts [door]: %s!", ReturnName(playerid), params);
        }
        SendClientMessageEx(playerid, COLOR_GREY, "%s shouts [door]: %s!", ReturnName(playerid), params);
    } 
    else Error(playerid, "Kamu tidak berada di pintu apapun.");
    return 1;
}

CMD:charity(playerid, params[])
{
    new amount[32], totalcash[32], reason[32];
    if(sscanf(params, "s[32]s[32]", amount, reason)) return Usage(playerid, "/charity [amount] [reason]");
    if(!(0 < strval(amount))) return Error(playerid, "Uang dibatasi mulai dari 0!");
	format(totalcash, sizeof(totalcash), "%d00", strval(amount));
    GivePlayerMoneyEx(playerid, -strval(totalcash));
    SendClientMessageEx(playerid, COLOR_YELLOW, "CHARITY: Thank you %s!. May the God bless you for you kind donation of $%s. Reason %s.", ReturnName2(playerid), FormatMoney(strval(totalcash)), reason);
    return 1;
}

 CMD:togglename(playerid)
 {
    if(GetPVarInt(playerid,"TagNama") == 0)
    {
        foreach(new ii : Player) ShowPlayerNameTagForPlayer(playerid, ii, true);
        InfoTD_MSG(playerid, 3000, "Toggle name ~g~enable");
        SetPVarInt(playerid, "TagNama", 1);
    } 
	else 
	{
        foreach(new ii : Player) ShowPlayerNameTagForPlayer(playerid, ii, false);
        InfoTD_MSG(playerid, 3000, "Toggle name ~r~disable");
        SetPVarInt(playerid, "TagNama", 0);
    }
    return 1;
 }

CMD:sellproperty(playerid, params[]) {
    if (!IsPlayerInRangeOfPoint(playerid, 3.0, 1424.31, 1546.21, 3010.83))
        return Error(playerid, "You must be in City Hall to use this command");

    Dialog_Show(playerid, ListProperties, DIALOG_STYLE_LIST, "List Properties", "House\nBusiness\nWorkshop\nFurniture Store\nFlat", "Select", "Close");
    return 1;
}

CMD:claims(playerid, params[])
{
	new Dstring[155];
    format(Dstring, sizeof(Dstring), "Items\tAmount\n");
    format(Dstring, sizeof(Dstring), "%s"WHITE_E"VIP Dealership Claims\t"YELLOW_E"%d\n", Dstring, pData[playerid][pClaimVIP][0]);
    format(Dstring, sizeof(Dstring), "%s"WHITE_E"Custom Gate\t"YELLOW_E"%d\n",Dstring, pData[playerid][pClaimVIP][1]);
    format(Dstring, sizeof(Dstring), "%s"WHITE_E"Custom House Exterior Mapping\t"YELLOW_E"%d\n", Dstring, pData[playerid][pClaimVIP][2]);
    Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "My Claims", Dstring, "Close", "");
	return 1;
}

CMD:myproperty(playerid, params[])
{
	new Dstring[1000], address[24], FlatType[12];
    format(Dstring, sizeof(Dstring), "%s"WHITE_E"1.\t(%s)\tResidential Properties:\n", Dstring, PropertiesResidential_GetCount(playerid));
    foreach (new i : Houses) if(Player_OwnsHouse(playerid, i)) 
    {
        format(Dstring, sizeof(Dstring), "%sH%d:\t"LG_E"House [owner]\t"WHITE_E"%s\n",Dstring, i, hData[i][hAddress]);
    }
    foreach (new i : FlatRooms) if (FlatRoom_IsOwner(playerid, i)) {
		FlatRoom_GetAddress(i, address);
		Flat_GetType(i, FlatType);
        format(Dstring, sizeof(Dstring), "%sF%d:\t"PURPLE_E"Flat "LG_E"[owner]\t"WHITE_E"%s\n",Dstring, i, address);
    }
	format(Dstring, sizeof(Dstring), "%s"WHITE_E"2.\t(%s)\tCommercial Properties:\n",Dstring, PropertiesCommercial_GetCount(playerid));
    foreach(new i : Bisnis) if(Player_OwnsBisnis(playerid, i)) {
		format(Dstring, sizeof(Dstring), "%sB:%d\t"AQUA_E"%s (Bisnis)"GREEN_E"[Owner]\t"WHITE_E"%s\n",Dstring, i, ReplaceString(bData[i][bName]), GetLocation(bData[i][bExtposX], bData[i][bExtposY], bData[i][bExtposZ]));
    }
    foreach(new i : Bisnis) if(Player_OwnsFarms(playerid, i)) {
		format(Dstring, sizeof(Dstring), "%sR2%d:\t"LG_E"Farms "BLUE_E"[owner]\t"WHITE_E"%s\n",Dstring, i, GetLocation(laData[i][laExtposX], laData[i][laExtposY], laData[i][laExtposZ]));
    }
    // foreach(new i : WORKSHOPS) if(pData[playerid][pWorkshop] == i) {
	// 	format(Dstring, sizeof(Dstring), "%sW:%d\t"AQUA_E"%s (Workshop)"GREEN_E"[Owner]\t"WHITE_E"%s\n",Dstring, i, ReplaceString(wData[i][wName]), GetLocation(wData[i][wExtposX], wData[i][wExtposY], wData[i][wExtposZ]));
    // }
	foreach (new i : FurnStore) if (FurnStore_IsOwner(playerid, i)) {
		format(Dstring, sizeof(Dstring), "%sFB:%d\t"AQUA_E"%s (Furniture)"GREEN_E"[Owner]\t"WHITE_E"%s\n\n",Dstring, i, storeData[i][storeName], GetLocation(storeData[i][storePos][0], storeData[i][storePos][1], storeData[i][storePos][2]));
	}
	foreach (new pvid : PrivateGarage) if (OwnerPvGarage(playerid, pvid)) {
		format(Dstring, sizeof(Dstring), "%sG%d:\t"BLUE_E"Garage "LG_E"[owner]\t"WHITE_E"%s\n\n",Dstring, pvid, GetLocation(PrivateGarage[pvid][GaragePos][0], PrivateGarage[pvid][GaragePos][1], PrivateGarage[pvid][GaragePos][2]));
	}
	Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_LIST, "Owned Property", Dstring, "Close", "");
	return 1;
}

CMD:takeclaims(playerid, params[])
{
	if(pData[playerid][pAdmin] < 5) return PermissionError(playerid);
	new giveplayerid;
	if(sscanf(params, "u", giveplayerid))
	{
		Usage(playerid, "/takeclaims [playerid");
		return 1;
	}
	if(!IsPlayerConnected(giveplayerid))
		return Error(playerid, "The specified player is disconnected");
	SetPVarInt(playerid, "OtheridTakeClaims", giveplayerid);
	new Dstring[155];
    format(Dstring, sizeof(Dstring), "Name Feature\tAmmount\n");
    format(Dstring, sizeof(Dstring), "%s"WHITE_E"Custom Gate\t"YELLOW_E"%d\n", Dstring, pData[playerid][pClaimVIP][1]);
    format(Dstring, sizeof(Dstring), "%s"WHITE_E"Custom House Exterior Mapping\t"YELLOW_E"%d\n", Dstring, pData[playerid][pClaimVIP][2]);
    Dialog_Show(playerid, TakeClaims, DIALOG_STYLE_TABLIST_HEADERS, "Claims Donatur", Dstring, "Close", "");
	return 1;
}

CMD:usegold(playerid, params[])
{
	new Dstring[261];
	format(Dstring, sizeof(Dstring), "Gold Shop\tPrice\n");
	format(Dstring, sizeof(Dstring), "%sClear Warning(-1)\t50 Gold\n", Dstring);
	format(Dstring, sizeof(Dstring), "%sChange Phone Number\t150 Gold\n", Dstring);
	format(Dstring, sizeof(Dstring), "%sChange Bank Number\t100 Gold\n", Dstring);
	format(Dstring, sizeof(Dstring), "%sChange Plate Vehicle\t100 Gold\n", Dstring);
	format(Dstring, sizeof(Dstring), "%sChange Mask Number\t250 Gold\n", Dstring);
	format(Dstring, sizeof(Dstring), "%sHouse Gate\t500 Gold\n", Dstring);
	format(Dstring, sizeof(Dstring), "%sHouse Mapping\t750 Gold\n", Dstring);
	format(Dstring, sizeof(Dstring), "%sVIP Dealership Claims\t550 Gold\n", Dstring);
	Dialog_Show(playerid, GoldShop, DIALOG_STYLE_TABLIST_HEADERS, "Gold Shop", Dstring, "Buy", "Cancel");
	return 1;
}

CMD:maxobject(playerid) {
    new str[155];
	strcat(str, "Setting\tObject Limit\tMultiplier\n");
	strcat(str, RED_E"Potato\t250\t0.2\n");
    strcat(str, ORANGE_E"Low\t500\t0.5\n");
    strcat(str, WHITE_E"Normal\t700\t1.0\n");
    strcat(str, GREEN_E"High\t800\t1.5\n");
    strcat(str, YELLOW_E"Stonks\t950\t2.0");
    Dialog_Show(playerid, StreamerSettings, DIALOG_STYLE_TABLIST_HEADERS, "Maximum object Configuration", str, "Set", "Cancel");
    return 1;
}

CMD:cancel(playerid, params[])
{
	if(IsPlayerConnected(playerid)) 
	{
        if(isnull(params)) 
		{
            Usage(playerid, "USAGE: /cancel [name]");
            Info(playerid, "Names: ask, report");
            return 1;
        }
		if(strcmp(params,"ask",true) == 0) 
		{
			if (!pData[playerid][pAsk] || !Ask_GetCount(playerid))
            	return Error(playerid, "You don't have any active ask.");
			
			pData[playerid][pAsk] = false;
			pData[playerid][pAskQ] = EOS;
			pData[playerid][pAskTime] = 0;
			Ask_Clear(playerid);
			SendCustomMessage(playerid, "CANCEL", "You've been canceled your ask.");
		}
		else if(strcmp(params,"report",true) == 0) 
		{
			for(new i=0;i<MAX_REPORTS;i++)
			{
				if(Reports[i][ReportFrom] == playerid && Reports[i][BeingUsed] == 1)
				{
					pData[playerid][pReportTime] = 0;
					Reports[i][BeingUsed] = 0;
					Reports[i][ReportFrom] = 999;
					Reports[i][CheckingReport] = 999;
					Reports[i][CheckingReport] = playerid;
					Reports[i][BeingUsed] = 0;
					Reports[i][TimeToExpire] = 0;
					strmid(Reports[i][Report], "None", 0, 4, 4);
					SendCustomMessage(playerid, "CANCEL", "You've been canceled your report.");
				}
				else return Error(playerid, "You don't have any active report.");
			}
		}
	}
	return 1;
}

CMD:help(playerid, params[])
{
	Dialog_Show(playerid, DialogHelp, DIALOG_STYLE_LIST, "Help Categories:", "Apa itu Roleplay?\nBasic Commands\nChat\nMoney & Banking\nVehicle Help\nJob Help\nFaction Commands\nFamily Commands\nBisnis Commands\nFurniture Store\nHouse Commands\nFlat Apartments Help\nWorkshop Commands\nFarm Commands\nGarage Commands\nDonatur Commands", "Select", "Close");
	return 1;
}

CMD:credits(playerid)
{
	new line1[1200], line2[300], line3[500];
	strcat(line3, ""LB_E"Developer: "YELLOW_E"Hans&Xfadzz\n");
	format(line2, sizeof(line2), ""LB_E"Server Support: All SA-MP Team\n\n\
	"GREEN_E"Terima kasih telah bergabung dengan kami! Copyright © 2025 | DailyLife 2025");
	format(line1, sizeof(line1), "%s%s", line3, line2);
   	Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Server Credits", line1, "OK", "");
	return 1;
}

CMD:savestats(playerid, params[])
{
	if(pData[playerid][IsLoggedIn] == false)
		return Error(playerid, "You are not logged in!");
		
	UpdatePlayerData(playerid);
	Servers(playerid, "Akun anda telah di save di database!");
	return 1;
}

CMD:mypos(playerid, params[])
{
	new int, Float:px,Float:py,Float:pz, Float:a;
	GetPlayerPos(playerid, px, py, pz);
	GetPlayerFacingAngle(playerid, a);
	int = GetPlayerInterior(playerid);
	new zone[MAX_ZONE_NAME];
	GetPlayer3DZone(playerid, zone, sizeof(zone));
	SendClientMessageEx(playerid, COLOR_WHITE, "Lokasi Anda Saat Ini: %s (%0.2f, %0.2f, %0.2f, %0.2f) Int = %d", zone, px, py, pz, a, int);
	return 1;
}


CMD:vehpos(playerid, params[])
{
	new int, Float:px,Float:py,Float:pz, Float:a;
	GetVehiclePos(playerid, px, py, pz);
	GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	int = GetPlayerInterior(playerid);
	new zone[MAX_ZONE_NAME];
	GetPlayer3DZone(playerid, zone, sizeof(zone));
	SendClientMessageEx(playerid, COLOR_WHITE, "Lokasi Anda Saat Ini: %s (%0.2f, %0.2f, %0.2f, %0.2f) Int = %d", zone, px, py, pz, a, int);
	return 1;
}

CMD:gps(playerid, params[])
{
	if(pData[playerid][pGPS] < 1) return SendClientMessage(playerid, COLOR_GREY, "You don't have a GPS!, buy one at the Electronic Shop!");
	DisablePlayerCheckpoint(playerid);
	DisablePlayerRaceCheckpoint(playerid);
	Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
	return 1;
}

CMD:gajiserver(playerid, params[])
{
	new string[1600];
	format(string, sizeof(string), "Job/Sidejob\tGaji\n");
	format(string, sizeof(string), "%sFaction Duty\t$%s / 60 menit\n", string, FormatMoney(50000));
	format(string, sizeof(string), "%sTaxi Service\t$%s / 15 menit duty\n", string, FormatMoney(1500));
	format(string, sizeof(string), "%sMechanic Service\t$%s / 15 menit duty\n", string, FormatMoney(1500));
	format(string, sizeof(string), "%sCourier\t$%s per paket, max $%s / 10 paket\n", string, FormatMoney(2500), FormatMoney(25000));
	format(string, sizeof(string), "%sBus Driver\t$%s per lap\n", string, FormatMoney(15000));
	format(string, sizeof(string), "%sTrucker Hauling\t$%s - $%s per cargo\n", string, FormatMoney(20000), FormatMoney(39900));
	format(string, sizeof(string), "%sTrucker Crates\t$%s per crate\n", string, FormatMoney(1250));
	format(string, sizeof(string), "%sFarmer\t$%s - $%s per unit panen\n", string, FormatMoney(100), FormatMoney(200));
	format(string, sizeof(string), "%sLumber/Fish/Trashmaster\tSesuai jumlah item yang dijual/diantar\n", string);
	Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Gaji Server", string, "Close", "");
	return 1;
}

CMD:sleep(playerid, params[])
{
	if(pData[playerid][pInjured] == 1)
        return Error(playerid, "You can't use this command at the injured moment.");
	
	if(pData[playerid][pInHouse] == -1)
		return Error(playerid, "You must inside a house to sleep.");
	
	// InfoTD_MSG(playerid, 10000, "Sleeping... Please wait!");
	// TogglePlayerControllable(playerid, 0);
	// new time = (100) * (400);
    // SetTimerEx("UnfreezeSleep", time, 0, "i", playerid);
	switch(random(6))
	{
		case 0: ApplyAnimation(playerid, "INT_HOUSE", "BED_In_L",4.1,0,0,0,1,1);
		case 1: ApplyAnimation(playerid, "INT_HOUSE", "BED_In_R",4.1,0,0,0,1,1);
		case 2: ApplyAnimation(playerid, "INT_HOUSE", "BED_Loop_L",4.1,1,0,0,1,1);
		case 3: ApplyAnimation(playerid, "INT_HOUSE", "BED_Loop_R",4.1,1,0,0,1,1);
		case 4: ApplyAnimation(playerid, "INT_HOUSE", "BED_Out_L",4.1,0,1,1,0,0);
		case 5: ApplyAnimation(playerid, "INT_HOUSE", "BED_Out_R",4.1,0,1,1,0,0);
	}
	return 1;
}

CMD:time(playerid, params[])
{
	new String[512];
    new mtext[20];
    new year, month,day;
    getdate(year, month, day);
    if(month == 1) { mtext = "Januari"; }
    else if(month == 2) { mtext = "Februari"; }
    else if(month == 3) { mtext = "Maret"; }
    else if(month == 4) { mtext = "April"; }
    else if(month == 5) { mtext = "Mei"; }
    else if(month == 6) { mtext = "Juni"; }
    else if(month == 7) { mtext = "Juli"; }
    else if(month == 8) { mtext = "Agustus"; }
    else if(month == 9) { mtext = "September"; }
    else if(month == 10) { mtext = "Oktober"; }
    else if(month == 11) { mtext = "November"; }
    else if(month == 12) { mtext = "Desember"; }
    new hour,minuite,second;
    gettime(hour,minuite,second);
    new pc = pData[playerid][pPaycheck]/60;

    if (minuite < 10)
	{
        if (pData[playerid][pJailTime] > 0)
		{
            format(String, sizeof(String), "Tanggal : %d\nBulan : %s\nJam : %d:0%d\nJail Time Left: %d sec\nAnda dapat mengambil paycheck %d menit lagi", day, mtext, hour, minuite, pData[playerid][pJailTime]-10,pc);
        }
        else
		{
            format(String, sizeof(String), "Tanggal : %d\nBulan : %s\nJam : %d:0%d\nAnda dapat mengambil paycheck %d menit lagi", day, mtext, hour, minuite,pc);
        }
    }
    else
	{
        if (pData[playerid][pJailTime] > 0)
		{
            format(String, sizeof(String), "Tanggal : %d\nBulan : %s\nJam : %d:%d\nJail Time Left: %d sec\nAnda dapat mengambil paycheck %d menit lagi", day, mtext, hour, minuite, pData[playerid][pJailTime]-10,pc);
        }
        else
		{
            format(String, sizeof(String), "Tanggal : %d\nBulan : %s\nJam : %d:%d\nAnda dapat mengambil paycheck %d menit lagi", day, mtext, hour, minuite,pc);
        }
    }
    Dialog_Show(playerid,ShowOnly,DIALOG_STYLE_MSGBOX ,"Time",String,"Ok","Exit");
    return 1;
}

CMD:delays(playerid)
{
	if(pData[playerid][IsLoggedIn] == false) return Error(playerid, "You must logged in!");
	new string[700];
  	format(string, sizeof(string), "Delay type\tTime (minutes)\n");
    format(string, sizeof(string), "%sSweeper\t%d\nTrash Collector\t%d\nCourier\t%d\nBus Driver\t%d\nForklift Driver\t%d\nFishing\t%d\nTruck Delivery \t%d\nHauling\t%d\nLumber Jack\t%d\nSmuggler\t%d\nForeger\t%d\nWeapon Creation\t%d\nWeapon Training\t%d\nAdvertisement\t%d\n", 
    string, 
    DelayPlayer[playerid][DelaySweeper]/60,
    DelayPlayer[playerid][DelayTrashmaster]/60,
    DelayPlayer[playerid][DelayCourier]/60,
    DelayPlayer[playerid][DelayBusDriver]/60,
    DelayPlayer[playerid][DelayForklift]/60,
    DelayPlayer[playerid][DelayFishing]/60,
    DelayPlayer[playerid][DelayDelivery]/60,
    DelayPlayer[playerid][DelayHauling]/60,
    DelayPlayer[playerid][DelayLumberJack]/60,
    DelayPlayer[playerid][DelaySmuggler]/60,
	DelayPlayer[playerid][DelayForager]/60,
    DelayPlayer[playerid][DelayWeaponCreate]/60,
    DelayPlayer[playerid][DelayTraining]/60,
    DelayPlayer[playerid][DelayAdvertisement]/60);

	Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Delays", string, "Close", "");
	return 1;
}

CMD:newage(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 431.1708,2419.5818,356.2569)) return Error(playerid, "Anda harus berada di City Hall!");
	//if(pData[playerid][pIDCard] != 0) return Error(playerid, "Anda sudah memiliki ID Card!");
	if(GetPlayerMoney(playerid) < 300) return Error(playerid, "Anda butuh $3.00 untuk mengganti tgl lahir anda!");
	if(pData[playerid][IsLoggedIn] == false) return Error(playerid, "Anda harus login terlebih dahulu!");
	ShowPlayerDialog(playerid, DIALOG_CHANGEAGE, DIALOG_STYLE_INPUT, "Tanggal Lahir", "Masukan tanggal lahir (Tgl/Bulan/Tahun): 15/04/1998", "Change", "Cancel");
	return 1;
}

CMD:newrek(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1429.3341,-985.9102,996.1050)) return Error(playerid, "Anda harus berada di Bank!");
	if(GetPlayerMoney(playerid) < 50) return Error(playerid, "Not enough money!");
	new query[128], rand = RandomEx(111111, 999999);
	new rek = rand+pData[playerid][pID];
	mysql_format(g_SQL, query, sizeof(query), "SELECT brek FROM players WHERE brek='%d'", rek);
	mysql_tquery(g_SQL, query, "BankRek", "id", playerid, rek);
	SendClientMessage(playerid, COLOR_ARWIN, "BANK: "WHITE_E"New rekening bank!");
	GivePlayerMoneyEx(playerid, -50);
	Server_AddMoney(50);
	return 1;
}

CMD:mybank(playerid, params[])
{
	SendClientMessageEx(playerid, COLOR_ARWIN, "BANK: "WHITE_E"Your bank account number is: "LG_E"%d", pData[playerid][pBankRek]);
	return 1;
}

CMD:bank(playerid, params[])
{
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 4 && IsPlayerInRangeOfPoint(playerid, 3.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]))
		{
			new tstr[128];
			format(tstr, sizeof(tstr), ""ORANGE_E"No Rek: "LB_E"%d", pData[playerid][pBankRek]);
			ShowPlayerDialog(playerid, DIALOG_BANK, DIALOG_STYLE_LIST, tstr, "Check Balance\nSign Paycheck", "Select", "Cancel");
		}
	}
	return 1;
}

CMD:signcheck(playerid, params[])
{
	new atm = -1;
	atm = GetClosestATM(playerid);
	if(atm > -1)
	{
		DisplayPaycheck(playerid);
	}
	return 1;
}

CMD:showvehlic(playerid, params[])
{
    new string[500], giveplayerid, vehid;
    if(sscanf(params, "ud", giveplayerid, vehid)) return SendClientMessageEx(playerid, COLOR_ARWIN, "KEGUNAAN: "WHITE_E"/showvehlic [playerid] [vehid]");
	if(!IsPlayerConnected(giveplayerid) || !NearPlayer(playerid, giveplayerid, 4.0))
		return Error(playerid, "The specified player is disconnected or not near you.");
	if(vehid == INVALID_VEHICLE_ID) return Error(playerid, "Invalid id");
	foreach(new i : PVehicles)
	{
		if(vehid == pvData[i][cVeh])
		{
			if(pvData[i][cOwner] == pData[playerid][pID])
			{
				SendClientMessageEx(giveplayerid, COLOR_ARWIN,"=================[Vehicle Ownership]=================\n");
				format(string, sizeof(string), "Vehicle: {FFFF00}%s\n", GetVehicleModelName(pvData[i][cModel]));
				SendClientMessage(giveplayerid, COLOR_ARWIN, string);
				format(string, sizeof(string), "Insurances: {FFFF00}%d\n", pvData[i][cInsu]);
				SendClientMessage(giveplayerid, COLOR_ARWIN, string);
				format(string, sizeof(string), "Plate: {FFFF00}%s\n", pvData[i][cPlate]);
				SendClientMessage(giveplayerid, COLOR_ARWIN, string);
			 	if(pvData[i][cMesinUpgrade] == 1)
				{
				    SendClientMessageEx(giveplayerid, COLOR_ARWIN,"Upgrades:\n");
					format(string, sizeof(string), "{FFFFFF}- {00FF00}Engine\n");
			   		SendClientMessageEx(giveplayerid, COLOR_ARWIN, string);
			 	}
			 	if(pvData[i][pvBodyUpgrade] == 1)
				{
					format(string, sizeof(string), "{FFFFFF}- {00FF00}Body");
					SendClientMessageEx(giveplayerid, COLOR_ARWIN, string);
			 	}
			}
			else return Error(playerid, "ID kendaraan ini bukan punya anda! gunakan /mv untuk mencari ID.");
		}
	}
	return 1;
}

CMD:givemoneyall(playerid, params[])
{
    if(pData[playerid][pAdmin] < 6) return PermissionError(playerid);
        
    new money[32], mstr[128], totalcash[25];
    if(sscanf(params, "s[32]", money)) return Usage(playerid, "/givemoneyall <money>");

	format(totalcash, sizeof(totalcash), "%d00", strval(money));

    foreach(new pid : Player)
    {
        GivePlayerMoneyEx(pid, strval(totalcash));
		format(mstr, sizeof(mstr), "Admin %s telah memberikan $%s kepada semua player online", pData[playerid][pAdminname], FormatMoney(strval(totalcash)));
		SendClientMessage(pid, COLOR_LIGHTRED, mstr);
    }
    
    return 1;
}

CMD:pay(playerid, params[])
{
    static
        userid,
        amount,
        targetid;

    if(sscanf(params, "dd", userid, amount)) return Usage(playerid, "/pay [playerid/mask] [amount]");

    if((targetid = GetMaskOwner(userid)) != INVALID_PLAYER_ID) {
		if(!IsPlayerConnected(targetid) || !NearPlayer(playerid, targetid, 4.0))
        	return Error(playerid, "The specified player is disconnected or not near you.");
        if(targetid == playerid) return Error(playerid, "You can't give yourself money.");
        if(amount < 1) return Error(playerid, "Please specify an amount abov 1 dollar.");
        if(amount > GetPlayerMoney(playerid)) return Error(playerid, "You don't have that much money.");

        static
            string[72];

        GivePlayerMoneyEx(playerid, -amount);
        GivePlayerMoneyEx(targetid, amount);

		format(string, sizeof(string), "PAYINFO: "WHITE_E"You've paid "LG_E"$%s to "YELLOW_E"%s", FormatMoney(amount), ReturnName2(targetid));
		SendClientMessageEx(playerid, COLOR_ARWIN, string);
		format(string, sizeof(string), "PAYINFO: "WHITE_E"You've received "GREEN_E"$%s "WHITE_E"from "YELLOW_E"%s", FormatMoney(amount), ReturnName2(playerid));
		SendClientMessageEx(targetid, COLOR_ARWIN, string);

		ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
		ApplyAnimation(targetid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);

		SendStaffMessage(COLOR_YELLOW, ""YELLOW_E"[PAY] %s to %s for %s", ReturnName2(playerid), FormatMoney(amount), ReturnName2(targetid));
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO logpay (player,playerid,toplayer,toplayerid,ammount,time) VALUES('%s','%d','%s','%d','%d',UNIX_TIMESTAMP())", ReturnName(playerid), pData[playerid][pID], ReturnName(targetid), pData[targetid][pID], amount);
		mysql_tquery(g_SQL, query);	
	    return 1;
    }

	if(!IsPlayerConnected(userid) || !NearPlayer(playerid, userid, 4.0))
        return Error(playerid, "The specified player is disconnected or not near you.");
    if(userid == playerid) return Error(playerid, "You can't give yourself money.");
    if(amount < 1) return Error(playerid, "Please specify an amount above 1 dollar.");
    if(amount > GetPlayerMoney(playerid)) return Error(playerid, "You don't have that much money.");

    static
        string[72];

    GivePlayerMoneyEx(playerid, -amount);
    GivePlayerMoneyEx(userid, amount);

	format(string, sizeof(string), "PAYINFO: "WHITE_E"You've paid "GREEN_E"$%s to "YELLOW_E"%s", FormatMoney(amount), ReturnName2(userid));
	SendClientMessageEx(playerid, COLOR_ARWIN, string);
	format(string, sizeof(string), "PAYINFO: "YELLOW_E"%s "WHITE_E"has paid "GREEN_E"$%s "WHITE_E"to you", ReturnName2(playerid), FormatMoney(amount));
	SendClientMessageEx(userid, COLOR_ARWIN, string);

	ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
	ApplyAnimation(userid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);

	SendStaffMessage(COLOR_YELLOW, ""YELLOW_E"[PAY] %s to %s for %s", ReturnName2(playerid), FormatMoney(amount), ReturnName2(userid));
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO logpay (player,playerid,toplayer,toplayerid,ammount,time) VALUES('%s','%d','%s','%d','%d',UNIX_TIMESTAMP())", ReturnName(playerid), pData[playerid][pID], ReturnName(userid), pData[userid][pID], amount);
	mysql_tquery(g_SQL, query);	
    return 1;
}

CMD:stats(playerid, params[])
{
	if(pData[playerid][IsLoggedIn] == false)
	{
	    Error(playerid, "You must be logged in to check statistics!");
	    return 1;
	}
	if (pData[playerid][pStreamMode]) {
		DisplayStats(playerid, playerid);
	}
	else
	{
		DisplayStatsStream(playerid, playerid);    
	}
	return 1;
}

CMD:togauto(playerid, params[])
{
	new handbrake[64], paycheck[64], mask[64], chat[64], sealtbeath[64], helm[64], rstream[64], ammo[64];

	if(pData[playerid][pTogPaycheck] == 0) paycheck = ""RED_E"Disable";
	else paycheck = ""LG_E"Enable";
	if(pData[playerid][pTogHelmet] == 0) helm = ""RED_E"Disable";
	else helm = ""LG_E"Enable";
	if(pData[playerid][pRadioStream] == 0) rstream = ""RED_E"Disable";
	else rstream = ""LG_E"Enable";
	if(pData[playerid][pTogChat] == 0) chat = ""RED_E"Disable";
	else chat = ""LG_E"Enable";
	if(pData[playerid][pTogMask] == 0) mask = ""RED_E"Disable";
	else mask = ""LG_E"Enable";
	if(pData[playerid][pTogSealtbelt] == 0) sealtbeath = ""RED_E"Disable";
	else sealtbeath = ""LG_E"Enable";
	if(pData[playerid][pTogHandbrake] == 0) handbrake = ""RED_E"Disable";
	else handbrake = ""LG_E"Enable";
	if(pData[playerid][pTogAmmo] == 0) ammo = ""RED_E"Disable";
	else ammo = ""LG_E"Enable";

	new String[512];
	format(String, sizeof(String),"Option\tSetting\n");
	format(String, sizeof(String),"%sAutomatic Paycheck:\t%s\n", String, paycheck);
	format(String, sizeof(String),"%sAutomatic-Handbrake on Engine off:\t%s\n", String, handbrake);
	format(String, sizeof(String),"%sAutomatic Sealtbelt:\t%s\n", String, sealtbeath);
	format(String, sizeof(String),"%sAuto-Wear Motorcycle Helmet:\t%s\n", String, helm);
	format(String, sizeof(String),"%sAuto Disable Radiostream:\t%s\n", String, rstream);
	format(String, sizeof(String),"%sAuto Upper-case Chat:\t%s\n", String, chat);
	format(String, sizeof(String),"%sEnable Mask on Login:\t%s\n", String, mask);
	format(String, sizeof(String),"%sToggle TD Ammo:\t%s\n", String, ammo);
	Dialog_Show(playerid, TogAuto, DIALOG_STYLE_TABLIST_HEADERS, "Toggle Auto Settings", String, "Toggle", "Cancel");
	return 1;
}

CMD:hudmode(playerid)
{
	if(pData[playerid][IsLoggedIn] == false) return Error(playerid, "You must be logged in to check statistics!");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return Error(playerid, "you must be outside the vehicle");
	new str[512], hbemode[64], togdate[64], togtime[64], togmoney[64], toggps[64], togweb[64];
	if(pData[playerid][pHBEMode] == 0) hbemode = "Enabled";
	else if(pData[playerid][pHBEMode] == 1) hbemode = "SA STYLE";
	else if(pData[playerid][pHBEMode] == 2) hbemode = "SIMPLE";
	else if(pData[playerid][pHBEMode] == 3) hbemode = "OLD SCHOOL";
	if(TogglePlayer[playerid][ToggleDate] == 0) togdate = ""RED_E"Disabled";
	else togdate = ""GREEN_E"Enabled";
	if(TogglePlayer[playerid][ToggleTime] == 0) togtime = ""RED_E"Disabled";
	else togtime = ""GREEN_E"Enabled";
	if(TogglePlayer[playerid][ToggleMoney] == 0) togmoney = ""RED_E"Disabled";
	else togmoney = ""GREEN_E"Enabled";
	if(TogglePlayer[playerid][ToggleGPS] == 0) toggps = ""RED_E"Disabled";
	else toggps = ""GREEN_E"Enabled";
	if(TogglePlayer[playerid][ToggleWeb] == 0) togweb = ""RED_E"Disabled";
	else togweb = ""GREEN_E"Enabled";

	format(str, sizeof(str), "Option\tSetting\nHUD Mode:\t%s\nDate:\t%s\nTime:\t%s\nMoney Dot:\t%s\nGPS Location:\t%s\nWebsite:\t%s",
	hbemode,togdate,togtime,togmoney,toggps,togweb);
	Dialog_Show(playerid, DialogHudMode, DIALOG_STYLE_TABLIST_HEADERS, "HUD Options", str, "Toggle", "Close");
	return 1;
}

CMD:toggle(playerid)
{
	if(pData[playerid][IsLoggedIn] == false) return Error(playerid, "You must be logged in to check statistics!");
	new str[512], togglobal[64], togpm[64], togstaff[64], togfaction[64], togads[64], togquizvote[64], togstaffquestion[64], togstaffreport[64], togwt[64], toguang[64], togradio[64];

	if(pData[playerid][pTogGlobalOoc] == 0) togglobal = ""RED_E"Disabled";
	else togglobal = ""GREEN_E"Enabled";
	if(pData[playerid][pTogPM] == 0) togpm = ""RED_E"Disabled";
	else togpm = ""GREEN_E"Enabled";
	if(pData[playerid][pTogFaction] == 0) togfaction = ""RED_E"Disabled";
	else togfaction = ""GREEN_E"Enabled";
	if(pData[playerid][pTogAds] == 0) togads = ""RED_E"Disabled";
	else togads = ""GREEN_E"Enabled";
	if(pData[playerid][pTogWT] == 0) togwt = ""RED_E"Disabled";
	else togwt = ""GREEN_E"Enabled";
	if(pData[playerid][pTogMoney] == 1) toguang = ""RED_E"Disabled";
	else toguang = ""GREEN_E"Enabled";
	if(pData[playerid][pTogRadio] == 0) togradio = ""RED_E"Disabled";
	else togradio = ""GREEN_E"Enabled";
	if(pData[playerid][pTogQuizVote] == 1) togquizvote = ""RED_E"Disabled";
	else togquizvote = ""GREEN_E"Enabled";
	if(pData[playerid][pTogStaffQuestion] == 0) togstaffquestion = ""RED_E"Disabled";
	else togstaffquestion = ""GREEN_E"Enabled";
	if(pData[playerid][pTogStaffReport] == 0) togstaffreport = ""RED_E"Disabled";
	else togstaffreport = ""GREEN_E"Enabled";
	if(pData[playerid][pTogStaffChat] == 0) togstaff = ""RED_E"Disabled";
	else togstaff = ""GREEN_E"Enabled";

	format(str, sizeof(str), "Message\tToggle\nGlobal OOC Chat\t%s\nPersonal Message\t%s\nWalkie Talkie:\t%s\nFaction Message:\t%s\nAdvertisements:\t%s\nQuiz and Votes\t%s\n[STAFF] Questions\t%s\n[STAFF] Reports\t%s\n[STAFF] Admin Chat\t%s",
	togglobal,
	togpm,
	togwt,
	togads,
	togfaction,
	togquizvote,
	togstaffquestion,
	togstaffreport,
	togstaff
	);
	Dialog_Show(playerid, DialogToggle, DIALOG_STYLE_TABLIST_HEADERS, "Toggle Message", str, "Toggle", "Close");
	return 1;
}

CMD:items(playerid, params[])
{
	if(pData[playerid][IsLoggedIn] == false)
	{
	    Error(playerid, "You must be logged in to check items!");
	    return true;
	}
	DisplayItems(playerid, playerid);
	return 1;
}

CMD:joinjob(playerid, params[])
{	
	if(pData[playerid][pVip] > 3)
	{
		if(pData[playerid][pJob] == 0 || pData[playerid][pJob2] == 0)
		{
			if(pData[playerid][pJob] == 0)
			{
				if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1685.4528,-1464.4073,13.5469))
				{
					if(pData[playerid][pDriveLic] < 1) return Error(playerid, "You don't have a driver's license");
					pData[playerid][pGetJob] = 1;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Taxi Driver, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1809.17, -2064.89, 13.55))
				{
					pData[playerid][pGetJob] = 2;
					
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Mechanic, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -1432.7500,-1538.4900,102.2578))
				{
					pData[playerid][pGetJob] = 3;
					
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Lumberjack, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -77.1687,-1136.5388,1.0781))
				{
					if(pData[playerid][pDriveLic] < 1) return Error(playerid, "You don't have a driver's license");
					pData[playerid][pGetJob] = 4;
					
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Trucker, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -382.7033,-1438.9998,26.1691))
				{
					pData[playerid][pGetJob] = 5;
					
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Farmer, {00CCFF}'/accept job'{FFFFFF}.");
				}
                else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 321.5652,1121.2504,1083.8828))
				{
					pData[playerid][pGetJob] = 6;
					
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Arms Dealer, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -882.1044,1110.8616,5442.8203))
				{
					pData[playerid][pGetJob] = 7;
					
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Drugs Dealer, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1273.3732,392.2403,19.5614))
				{
					pData[playerid][pGetJob] = 8;
					
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Smuggle, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1289.0930,-1272.1663,13.5422))
				{
					pData[playerid][pGetJob] = 9;
					
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Builder, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else return Error(playerid, "Anda sudah memiliki job atau tidak berada di dekat pendaftaran job.");
			}
			else if(pData[playerid][pJob2] == 0)
			{
				if(pData[playerid][pJob2] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1685.4528,-1464.4073,13.5469))
				{
					if(pData[playerid][pDriveLic] < 1) return Error(playerid, "You don't have a driver's license");
					pData[playerid][pGetJob2] = 1;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Taxi Driver, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob2] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1809.17, -2064.89, 13.55))
				{
					pData[playerid][pGetJob2] = 2;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Mechanic, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob2] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -1432.7500,-1538.4900,102.2578))
				{
					pData[playerid][pGetJob2] = 3;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Lumber Jack, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob2] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -77.1687,-1136.5388,1.0781))
				{
					if(pData[playerid][pDriveLic] < 1) return Error(playerid, "You don't have a driver's license");
					pData[playerid][pGetJob2] = 4;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Trucker, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob2] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -382.7033,-1438.9998,26.1691))
				{
					pData[playerid][pGetJob2] = 5;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Farmer, {00CCFF}'/accept job'{FFFFFF}.");
				}
                else if(pData[playerid][pJob2] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 321.5652,1121.2504,1083.8828))
				{
					pData[playerid][pGetJob2] = 6;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Arms Dealer, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob2] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -882.1044,1110.8616,5442.8203))
				{
					pData[playerid][pGetJob2] = 7;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Drugs Dealer, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob2] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1273.3732,392.2403,19.5614))
				{
					pData[playerid][pGetJob2] = 8;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Smuggle, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob2] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1289.0930,-1272.1663,13.5422))
				{
					pData[playerid][pGetJob2] = 9;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Builder, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else return Error(playerid, "Anda sudah memiliki job atau tidak berada di dekat pendaftaran job.");
			}
			else return Error(playerid, "Anda sudah memiliki 2 pekerjaan!");
		}
		else return Error(playerid, "Anda sudah memiliki 2 pekerjaan!");
	}
	else
	{
		if(pData[playerid][pJob] == 0 || pData[playerid][pJob2] == 0)
		{
			if(pData[playerid][pJob] == 0)
			{
				if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1685.4528,-1464.4073,13.5469))
				{
					if(pData[playerid][pDriveLic] < 1) return Error(playerid, "You don't have a driver's license");
					pData[playerid][pGetJob] = 1;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Taxi Driver, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1809.17, -2064.89, 13.55))
				{
					pData[playerid][pGetJob] = 2;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Mechanic, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -1432.7500,-1538.4900,102.2578))
				{
					pData[playerid][pGetJob] = 3;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Lumber Jack, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -77.1687,-1136.5388,1.0781))
				{
					if(pData[playerid][pDriveLic] < 1) return Error(playerid, "You don't have a driver's license");
					pData[playerid][pGetJob] = 4;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Trucker, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -382.7033,-1438.9998,26.1691))
				{
					pData[playerid][pGetJob] = 5;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Farmer, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 321.5652,1121.2504,1083.8828))
				{
					pData[playerid][pGetJob] = 6;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Arms Dealer, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -882.1044,1110.8616,5442.8203))
				{
					pData[playerid][pGetJob] = 7;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Drugs Dealer, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1273.3732,392.2403,19.5614))
				{
					pData[playerid][pGetJob] = 8;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Smuggle, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1289.0930,-1272.1663,13.5422))
				{
					pData[playerid][pGetJob] = 9;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Builder, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else return Error(playerid, "Anda sudah memiliki job atau tidak berada di dekat pendaftaran job.");
			}
			else if(pData[playerid][pJob2] == 0)
			{
				if(pData[playerid][pCS] < 1) return Error(playerid, "Kamu butuh CS untuk membuka slot job kedua!");
				if(pData[playerid][pJob2] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 321.5652,1121.2504,1083.8828))
				{
					pData[playerid][pGetJob2] = 6;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Arms Dealer, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob2] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, -882.1044,1110.8616,5442.8203))
				{
					pData[playerid][pGetJob2] = 7;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Drugs Dealer, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else if(pData[playerid][pJob2] == 0 && GetPlayerState(playerid) == 1 && IsPlayerInRangeOfPoint(playerid, 3.0, 1273.3732,392.2403,19.5614))
				{
					pData[playerid][pGetJob2] = 8;
					SendClientMessageEx(playerid, COLOR_YELLOW, "JOINJOB: {FFFFFF}Jika anda yakin bekerja menjadi Smuggle, {00CCFF}'/accept job'{FFFFFF}.");
				}
				else return Error(playerid, "Anda hanya bisa join illegal jobs sebagai pekerjaan kedua!");
			}
		}
		else return Error(playerid, "Anda sudah memiliki 2 pekerjaan!");
	}
	return 1;
}

CMD:frisk(playerid, params[])
{
    static
        userid,
        targetid;

    if(sscanf(params, "d", userid)) return Usage(playerid, "/frisk [playerid/mask]");

    if ((targetid = GetMaskOwner(userid)) != INVALID_PLAYER_ID) {
	    if(targetid == INVALID_PLAYER_ID || !NearPlayer(playerid, targetid, 5.0))
	        return Error(playerid, "The specified player is disconnected or not near you.");

        if(targetid == playerid) return Error(playerid, "You cannot frisk yourself.");

        pData[targetid][pFriskOffer] = playerid;

	   	SendClientMessageEx(targetid, COLOR_ARWIN, "FRISK: "WHITE_E"%s has offered to frisk you (type \"/accept frisk or /deny frisk\").", ReturnName2(playerid));
	    SendClientMessageEx(playerid, COLOR_ARWIN, "FRISK: "WHITE_E"You've asked permission to frisk "AQUA_E"%s, please wait for their response.", ReturnName2(targetid));
        return 1;
    }

	if(userid == INVALID_PLAYER_ID || !NearPlayer(playerid, userid, 5.0))
	    return Error(playerid, "The specified player is disconnected or not near you.");

    pData[userid][pFriskOffer] = playerid;
   	SendClientMessageEx(userid, COLOR_ARWIN, "FRISK: "WHITE_E"%s has offered to frisk you (type \"/accept frisk or /deny frisk\").", ReturnName2(playerid));
    SendClientMessageEx(playerid, COLOR_ARWIN, "FRISK: "WHITE_E"You've asked permission to frisk "AQUA_E"%s, please wait for their response.", ReturnName2(userid));
	return 1;
}

CMD:accept(playerid, params[])
{
	if(IsPlayerConnected(playerid)) 
	{
        if(isnull(params)) return Usage(playerid, "USAGE: /accept [faction/family/workshop/drag/frisk/job/inspect/marriage/divorce/death]");
		if(strcmp(params,"menu",true) == 0)
	   	{
			if(ProductOffer[playerid][0] == INVALID_PLAYER_ID || !NearPlayer(playerid, ProductOffer[playerid][0], 5.0)) return Error(playerid, "The specified player is disconnected or not near you.");
			new string[512], bizid = ProductOffer[playerid][1];
	   	    format(string, sizeof(string), "%s (Menu +12)  - $%s\n%s (Menu +45)  - $%s\n%s (Menu +60)  - $%s\n%s (Energy Drink) - $%s",
				bData[bizid][bPName0],
				FormatMoney(bData[bizid][bP][0]),
				bData[bizid][bPName1],
				FormatMoney(bData[bizid][bP][1]),
				bData[bizid][bPName2],
				FormatMoney(bData[bizid][bP][2]),
				bData[bizid][bPName3],
				FormatMoney(bData[bizid][bP][3])
			);
			Dialog_Show(playerid, BuyProdVehicle, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Buy", "Cancel");
      	}
		if(strcmp(params,"faction",true) == 0) 
		{
            if(IsPlayerConnected(pData[playerid][pFacOffer])) 
			{
                if(pData[playerid][pFacInvite] > 0) 
				{
					if(pData[playerid][pCS] > 0)
					{
						pData[playerid][pFaction] = pData[playerid][pFacInvite];
						pData[playerid][pFactionRank] = 1;
						SendClientMessageEx(playerid, COLOR_ARWIN, "ACCEPT: "WHITE_E"Anda telah menerima invite faction dari %s", ReturnName2(pData[playerid][pFacOffer]));
						SendClientMessageEx(pData[playerid][pFacOffer], COLOR_ARWIN, "ACCEPT: "WHITE_E"%s telah menerima invite faction yang anda tawari", ReturnName2(playerid));
						pData[playerid][pFacInvite] = 0;
						pData[playerid][pFacOffer] = -1;
					}
					else return Error(playerid, "Anda tidak mempunyai CS");
				}
				else
				{
					Error(playerid, "Invalid faction id!");
					return 1;
				}
            }
            else 
			{
                Error(playerid, "Tidak ada player yang menawari anda!");
                return 1;
            }
        }
		if(strcmp(params,"inspect",true) == 0)
	   	{
	   	    Health_Show(pData[playerid][nspectOffer], playerid);
			pData[playerid][nspectOffer] = INVALID_PLAYER_ID;
      	}
		if(strcmp(params,"family",true) == 0) 
		{
            if(IsPlayerConnected(pData[playerid][pFamOffer])) 
			{
                if(pData[playerid][pFamInvite] > -1) 
				{
					if(pData[playerid][pCS] > 0)
					{
						pData[playerid][pFamily] = pData[playerid][pFamInvite];
						pData[playerid][pFamilyRank] = 1;
						SendClientMessageEx(playerid, COLOR_ARWIN, "ACCEPT: "WHITE_E"Anda telah menerima invite family dari %s", ReturnName2(pData[playerid][pFamOffer]));
						SendClientMessageEx(pData[playerid][pFamOffer], COLOR_ARWIN, "ACCEPT: "WHITE_E"%s telah menerima invite family yang anda tawari", ReturnName2(playerid));
						pData[playerid][pFamInvite] = 0;
						pData[playerid][pFamOffer] = -1;
					}
					else return Error(playerid, "Anda tidak mempunyai CS");	
				}
				else
				{
					Error(playerid, "Invalid family id!");
					return 1;
				}
            }
            else 
			{
                Error(playerid, "Tidak ada player yang menawari anda!");
                return 1;
            }
        }
		if(strcmp(params,"workshop",true) == 0)
		{
            if(IsPlayerConnected(pData[playerid][pWorkOffer]))
			{
                if(pData[playerid][pWorkInvite] > -1)
				{
					if(pData[playerid][pCS] > 0)
					{
						pData[playerid][pWorkshop] = pData[playerid][pWorkInvite];
						pData[playerid][pWorkshopRank] = 1;
						SendClientMessageEx(playerid, COLOR_ARWIN, "ACCEPT: "WHITE_E"Anda telah menerima invite workshop dari %s", ReturnName2(pData[playerid][pWorkOffer]));
						SendClientMessageEx(pData[playerid][pWorkOffer], COLOR_ARWIN, "ACCEPT: "WHITE_E"%s telah menerima invite workshop yang anda tawari", ReturnName2(playerid));
						pData[playerid][pWorkInvite] = 0;
						pData[playerid][pWorkOffer] = -1;
					}
					else return Error(playerid, "Anda tidak mempunyai CS");	
				}
				else
				{
					Error(playerid, "Invalid workshop id!");
					return 1;
				}
            }
            else
			{
                Error(playerid, "Tidak ada player yang menawari anda!");
                return 1;
            }
        }
		if(strcmp(params,"farm",true) == 0)
		{
            if(IsPlayerConnected(pData[playerid][pLadangOffer]))
			{
                if(pData[playerid][pLadangInvite] > -1)
				{
					if(pData[playerid][pCS] > 0)
					{
						pData[playerid][pLadang] = pData[playerid][pLadangInvite];
						pData[playerid][pLadangRank] = 1;
						SendClientMessageEx(playerid, COLOR_ARWIN, "ACCEPT: "WHITE_E"Anda telah menerima invite Farm dari %s", ReturnName2(pData[playerid][pLadangOffer]));
						SendClientMessageEx(pData[playerid][pLadangOffer], COLOR_ARWIN, "ACCEPT: "WHITE_E"%s telah menerima invite Farm yang anda tawari", ReturnName2(playerid));
						pData[playerid][pLadangInvite] = 0;
						pData[playerid][pLadangOffer] = -1;
					}
					else return Error(playerid, "Anda tidak mempunyai CS");		
				}
				else
				{
					Error(playerid, "Invalid Ladang id!");
					return 1;
				}
            }
            else
			{
                Error(playerid, "Tidak ada player yang menawari anda!");
                return 1;
            }
        }
		else if(strcmp(params,"drag",true) == 0)
		{
			new dragby = GetPVarInt(playerid, "DragBy");
			if(dragby == INVALID_PLAYER_ID || dragby == playerid)
				return Error(playerid, "That player is disconnected.");
        
			if(!NearPlayer(playerid, dragby, 5.0))
				return Error(playerid, "You must be near this player.");
        
			pData[playerid][pDragged] = 1;
			pData[playerid][pDraggedBy] = dragby;

			pData[playerid][pDragTimer] = SetTimerEx("DragUpdate", 1000, true, "ii", dragby, playerid);
			SendNearbyMessage(dragby, 30.0, COLOR_PURPLE, "* %s grabs %s and starts dragging them, (/undrag).", ReturnName2(dragby), ReturnName2(playerid));
			return true;
		}
		else if(strcmp(params,"frisk",true) == 0)
		{
			if(pData[playerid][pFriskOffer] == INVALID_PLAYER_ID || !IsPlayerConnected(pData[playerid][pFriskOffer]))
				return Error(playerid, "That player not connected!");
			
			if(!NearPlayer(playerid, pData[playerid][pFriskOffer], 5.0))
				return Error(playerid, "You must be near this player.");
				
			DisplayItems2(pData[playerid][pFriskOffer], playerid);
			Servers(playerid, "Anda telah berhasil menaccept tawaran frisk kepada %s.", ReturnName2(pData[playerid][pFriskOffer]));
			pData[playerid][pFriskOffer] = INVALID_PLAYER_ID;
		}
		else if(strcmp(params,"marriage",true) == 0)
		{
			new String[500];
			if(pData[playerid][pMarriedAccept] == INVALID_PLAYER_ID || !IsPlayerConnected(pData[playerid][pMarriedAccept]))
				return Error(playerid, "That player not connected!");
			
			if(!NearPlayer(playerid, pData[playerid][pMarriedAccept], 5.0))
				return Error(playerid, "You must be near this player.");

			if(pData[playerid][pGender] == 1 && pData[pData[playerid][pMarriedAccept]][pGender] == 2)
			{
				format(String, sizeof(String), "Priest: %s and %s i pronounce you now... Husband & Wife, you may kiss the bride.", ReturnName2(playerid), ReturnName2(pData[playerid][pMarriedAccept]));
				SendClientMessageEx(playerid, COLOR_WHITE, String);
		   		format(String, sizeof(String), "Priest: %s and %s i pronounce you now... Husband & Wife, you may kiss the groom.", ReturnName2(pData[playerid][pMarriedAccept]), ReturnName2(playerid));
				SendClientMessageEx(pData[playerid][pMarriedAccept], COLOR_WHITE, String);
				format(String, sizeof(String), "Marriage News: We have a new lovely couple! {FFFF00}%s {FFFFFF}& {FFFF00}%s have been married.", ReturnName2(playerid), ReturnName2(pData[playerid][pMarriedAccept]));
				OOCNews(COLOR_WHITE, String);
			}
			else if(pData[playerid][pGender] == 1 && pData[pData[playerid][pMarriedAccept]][pGender] == 1)
			{
				format(String, sizeof(String), "Priest: %s and %s i pronounce you now... Husband & Husband, you may kiss the bride.", ReturnName2(playerid), ReturnName2(pData[playerid][pMarriedAccept]));
				SendClientMessageEx(playerid, COLOR_WHITE, String);
		   		format(String, sizeof(String), "Priest: %s and %s i pronounce you now... Husband & Husband, you may kiss the groom.", ReturnName2(pData[playerid][pMarriedAccept]), ReturnName2(playerid));
				SendClientMessageEx(pData[playerid][pMarriedAccept], COLOR_WHITE, String);
				format(String, sizeof(String), "Marriage News: We have a new gay couple! {FFFF00}%s {FFFFFF}& {FFFF00}%s have been married.", ReturnName2(playerid), ReturnName2(pData[playerid][pMarriedAccept]));
				OOCNews(COLOR_WHITE, String);
			}
			else if(pData[playerid][pGender] == 2 && pData[pData[playerid][pMarriedAccept]][pGender] == 2)
			{
				format(String, sizeof(String), "Priest: %s and %s i pronounce you now... Wife & Wife, you may kiss the Bride.", ReturnName2(playerid), ReturnName2(pData[playerid][pMarriedAccept]));
				SendClientMessageEx(playerid, COLOR_WHITE, String);
		   		format(String, sizeof(String), "Priest: %s and %s i pronounce you now... Wife & Wife, you may kiss the Groom.", ReturnName2(pData[playerid][pMarriedAccept]), ReturnName2(playerid));
				SendClientMessageEx(pData[playerid][pMarriedAccept], COLOR_WHITE, String);
				format(String, sizeof(String), "Marriage News: We have a new lesbian couple! {FFFF00}%s {FFFFFF}& {FFFF00}%s have been married.", ReturnName2(playerid), ReturnName2(pData[playerid][pMarriedAccept]));
				OOCNews(COLOR_WHITE, String);
			}
			format(pData[pData[playerid][pMarriedAccept]][pMarriedTo], MAX_PLAYER_NAME, "%s", ReturnName(playerid));
			format(pData[playerid][pMarriedTo], MAX_PLAYER_NAME, "%s", ReturnName(pData[playerid][pMarriedAccept]));
			GivePlayerMoney(pData[playerid][pMarriedAccept], -10000);
			pData[playerid][pMarried] = 1;
			pData[pData[playerid][pMarriedAccept]][pMarried] = 1;
			pData[playerid][pMarriedAccept] = INVALID_PLAYER_ID;
		}
		else if(strcmp(params,"divorce",true) == 0)
		{
			if(pData[playerid][pMarriedCancel] == INVALID_PLAYER_ID || !IsPlayerConnected(pData[playerid][pMarriedCancel]))
				return Error(playerid, "That player not connected!");
			
			if(!NearPlayer(playerid, pData[playerid][pMarriedCancel], 5.0))
				return Error(playerid, "You must be near this player.");

			if(pData[playerid][pGender] == 1)
			{
				format(pData[playerid][pMarriedTo], 50, "Duda");
			}
			else if(pData[playerid][pGender] == 2)
			{
				format(pData[playerid][pMarriedTo], 50, "Janda");
			}
			if(pData[pData[playerid][pMarriedCancel]][pGender] == 1)
			{
				format(pData[pData[playerid][pMarriedCancel]][pMarriedTo], 50, "Duda");
			}
			else if(pData[pData[playerid][pMarriedCancel]][pGender] == 2)
			{
				format(pData[pData[playerid][pMarriedCancel]][pMarriedTo], 50, "Janda");
			}
			pData[playerid][pMarried] = 0;
			pData[pData[playerid][pMarriedCancel]][pMarried] = 0;
			pData[playerid][pMarriedCancel] = INVALID_PLAYER_ID;
			SendClientMessageEx(playerid, COLOR_ARWIN, "ACCEPT: "WHITE_E"Anda telah pisah/cerai dengan %s", ReturnName2(pData[playerid][pMarriedCancel]));
			SendClientMessageEx(pData[pData[playerid][pMarriedCancel]][pMarried], COLOR_ARWIN, "ACCEPT: "WHITE_E"Anda telah pisah/cerai dengan %s", ReturnName(playerid));
		}
		else if(strcmp(params,"job",true) == 0) 
		{
			if(pData[playerid][pGetJob] > 0)
			{
				pData[playerid][pJob] = pData[playerid][pGetJob];
				SendClientMessageEx(playerid, COLOR_ARWIN, "* Congratulations with your new Job, type /help to see your new command");
				pData[playerid][pGetJob] = 0;
				pData[playerid][pExitJob] = gettime() + (1 * 18000);
			}
			else if(pData[playerid][pGetJob2] > 0)
			{
				pData[playerid][pJob2] = pData[playerid][pGetJob2];
				SendClientMessageEx(playerid, COLOR_ARWIN, "* Congratulations with your new Job, type /help to see your new command");
				SendClientMessageEx(playerid, COLOR_YELLOW, "Donater: You have taken this as a secondary job.");
				pData[playerid][pGetJob2] = 0;
				pData[playerid][pExitJob] = gettime() + (1 * 18000);
			}
		}
		else if(strcmp(params,"death",true) == 0) 
		{
			if(pData[playerid][pInjured] < 1) return Error(playerid, "You are not injured at the moment.");
			if(pData[playerid][pJail] > 0) return Error(playerid, "You can't do this when in jail!");
			if(pData[playerid][pArrest] > 0) return Error(playerid, "You can't do this when in arrest sapd!");
			if((gettime()-GetPVarInt(playerid, "GiveUptime")) < 100) return SendClientMessage(playerid, COLOR_ARWIN, "DEATH: "WHITE_E"You must waiting 3 minutes for spawn to hospital");
			if(pData[playerid][pDragged] > 0) return Error(playerid, "You can't do this when in drag!");

			SendClientMessage(playerid, COLOR_ARWIN, "DEATH: "WHITE_E"You have given up and accepted your death");
			TextDrawHideForPlayer(playerid, injuredtextdraw);
			pData[playerid][pInjured] = 0;
			pData[playerid][pHospitalTime] = 0;
			pData[playerid][pHospital] = 0;
			pData[playerid][pHunger] = 50;
			pData[playerid][pEnergy] = 50;
			SetPlayerHealthEx(playerid, 50);
			pData[playerid][pSick] = 0;
			GivePlayerMoneyEx(playerid, -50000);
			ResetWeapons(playerid);
			Damage_Reset(playerid);
			for (new i; i < 5; i++) SendClientMessage(playerid, -1, "");
			SendClientMessage(playerid, COLOR_ARWIN, "INFO: "WHITE_E"The hospital has charged you "RED_E"$500.00 "WHITE_E"for the treatment!");
			SetPlayerPosition(playerid, 1182.8778, -1324.2023, 13.5784, 269.8747);
			TogglePlayerControllable(playerid, 1);
			SetCameraBehindPlayer(playerid);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
			ClearAnimations(playerid);
			pData[playerid][pSpawned] = 1;
			for (new i = 0; i < 6; i ++) {
				pData[playerid][pFitnessRating][i] -= RandomFloat(1.0,5.0);
			}
			SetPVarInt(playerid, "GiveUptime", -1);
			new getime[3];
			gettime(getime[0], getime[1], getime[2]);
			SetPlayerTime(playerid, getime[0], getime[1]);
			SetPlayerWeather(playerid, current_weather);
		}
	}
	return 1;
}

CMD:deny(playerid, params[])
{
	if(IsPlayerConnected(playerid)) 
	{
        if(isnull(params)) 
		{
            Usage(playerid, "USAGE: /deny [name]");
            Info(playerid, "Names: faction, drag, sharelok, frisk, job1, job2");
            return 1;
        }
		if(strcmp(params,"faction",true) == 0) 
		{
            if(pData[playerid][pFacOffer] > -1) 
			{
                if(pData[playerid][pFacInvite] > 0) 
				{
					SendClientMessageEx(playerid, COLOR_ARWIN, "DENY: "WHITE_E"Anda telah menolak faction dari %s", ReturnName2(pData[playerid][pFacOffer]));
					Info(pData[playerid][pFacOffer], "%s telah menolak invite faction yang anda tawari", ReturnName2(playerid));
					pData[playerid][pFacInvite] = 0;
					pData[playerid][pFacOffer] = -1;
				}
				else
				{
					Error(playerid, "Invalid faction id!");
					return 1;
				}
            }
            else 
			{
                Error(playerid, "Tidak ada player yang menawari anda!");
                return 1;
            }
        }
		else if(strcmp(params,"drag",true) == 0)
		{
			new dragby = GetPVarInt(playerid, "DragBy");
			if(dragby == INVALID_PLAYER_ID || dragby == playerid)
				return Error(playerid, "That player is disconnected.");

			SendClientMessageEx(playerid, COLOR_ARWIN, "DENY: "WHITE_E"Anda telah menolak drag.");
			SendClientMessageEx(dragby, COLOR_ARWIN, "DENY: "WHITE_E"Player telah menolak drag yang anda tawari.");
			
			DeletePVar(playerid, "DragBy");
			pData[playerid][pDragged] = 0;
			pData[playerid][pDraggedBy] = INVALID_PLAYER_ID;
			return 1;
		}
		else if(strcmp(params,"sharelok",true) == 0)
		{
 			new sharelok = GetPVarInt(playerid, "sharelok");
			if(sharelok == INVALID_PLAYER_ID || sharelok == playerid)
				return Error(playerid, "That player is disconnected.");

			SendClientMessageEx(playerid, COLOR_ARWIN, "DENY: "WHITE_E"Anda telah menolak sharelok.");
			SendClientMessageEx(sharelok, COLOR_ARWIN, "DENY: "WHITE_E"Player telah menolak sharelok yang anda tawari.");

			DeletePVar(playerid, "sharelok");
		//	pData[playerid][pDragged] = 0;
		//	pData[playerid][pDraggedBy] = INVALID_PLAYER_ID;
			return 1;
		}
		else if(strcmp(params,"frisk",true) == 0)
		{
			if(pData[playerid][pFriskOffer] == INVALID_PLAYER_ID || !IsPlayerConnected(pData[playerid][pFriskOffer]))
				return Error(playerid, "That player not connected!");
			
			SendClientMessageEx(playerid, COLOR_ARWIN, "DENY: "WHITE_E"Anda telah menolak tawaran frisk kepada %s.", ReturnName2(pData[playerid][pFriskOffer]));
			pData[playerid][pFriskOffer] = INVALID_PLAYER_ID;
			return 1;
		}
		else if(strcmp(params,"job1",true) == 0) 
		{
			if(pData[playerid][pJob] == 0) return Error(playerid, "Anda tidak memiliki job apapun.");
			{
				if(pData[playerid][pExitJob] != 0) return Error(playerid, "Kamu harus menunggu 1 hari setelah join job lain nya agar bisa quit job");
				{
					pData[playerid][pJob] = 0;
					SendClientMessageEx(playerid, COLOR_ARWIN, "DENY: "WHITE_E"Anda berhasil keluar dari pekerjaan anda.");
					return 1;
				}
			}
		}
		else if(strcmp(params,"job2",true) == 0) 
		{
			if(pData[playerid][pJob2] == 0) return Error(playerid, "Anda tidak memiliki job apapun.");
			{
				pData[playerid][pJob2] = 0;
				SendClientMessageEx(playerid, COLOR_ARWIN, "DENY: "WHITE_E"Anda berhasil keluar dari pekerjaan anda.");
				return 1;
			}
		}
	}
	return 1;
}

CMD:give(playerid, params[])
{
	if(IsPlayerConnected(playerid))
	{
		new name[24], ammount, otherid;
        if(sscanf(params, "us[24]d", otherid, name, ammount))
		{
			Usage(playerid, "/give [playerid] [name] [ammount]");
			Info(playerid, "Names: bandage, medicine, snack, sprunk, rokok, material, component, crack, pot");
			return 1;
		}
		if(otherid == INVALID_PLAYER_ID || otherid == playerid || !NearPlayer(playerid, otherid, 3.0))
			return Error(playerid, "Invalid playerid!");

		if(strcmp(name,"bandage",true) == 0)
		{
			if(ammount < 1) return SendClientMessage(playerid, 0xCECECEFF, "tidak bisa kurang dari 1");

			if(pData[playerid][pBandage] < ammount)
				return Error(playerid, "Item anda tidak cukup.");

			pData[playerid][pBandage] -= ammount;
			pData[otherid][pBandage] += ammount;
			SendClientMessageEx(playerid, COLOR_YELLOW, "* You given %d bandage to %s", ammount, ReturnName2(playerid));
			SendClientMessageEx(otherid, COLOR_YELLOW, "* You received %d bandage from %s", ammount, ReturnName2(playerid));
			ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
			ApplyAnimation(otherid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
		}
		else if(strcmp(name,"medicine",true) == 0)
		{
			if(ammount < 1) return SendClientMessage(playerid, 0xCECECEFF, "tidak bisa kurang dari 1");	
					
			if(pData[playerid][pMedicine] < ammount)
				return Error(playerid, "Item anda tidak cukup.");

			pData[playerid][pMedicine] -= ammount;
			pData[otherid][pMedicine] += ammount;
			SendClientMessageEx(playerid, COLOR_YELLOW, "* You given %d medicine to %s", ammount, ReturnName2(playerid));
			SendClientMessageEx(otherid, COLOR_YELLOW, "* You received %d medicine from %s", ammount, ReturnName2(playerid));
			ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
			ApplyAnimation(otherid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
		}
		else if(strcmp(name,"snack",true) == 0)
		{
			if(ammount < 1) return SendClientMessage(playerid, 0xCECECEFF, "tidak bisa kurang dari 1");

			if(pData[playerid][pSnack] < ammount)
				return Error(playerid, "Item anda tidak cukup.");

			pData[playerid][pSnack] -= ammount;
			pData[otherid][pSnack] += ammount;
			SendClientMessageEx(playerid, COLOR_YELLOW, "* You given %d snack to %s", ammount, ReturnName2(playerid));
			SendClientMessageEx(otherid, COLOR_YELLOW, "* You received %d snack from %s", ammount, ReturnName2(playerid));
			ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
			ApplyAnimation(otherid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
		}
		else if(strcmp(name,"sprunk",true) == 0)
		{
			if(ammount < 1) return SendClientMessage(playerid, 0xCECECEFF, "tidak bisa kurang dari 1");

			if(pData[playerid][pSprunk] < ammount)
				return Error(playerid, "Item anda tidak cukup.");

			pData[playerid][pSprunk] -= ammount;
			pData[otherid][pSprunk] += ammount;
			SendClientMessageEx(playerid, COLOR_YELLOW, "* You given %d sprunk to %s", ammount, ReturnName2(playerid));
			SendClientMessageEx(otherid, COLOR_YELLOW, "* You received %d sprunk from %s", ammount, ReturnName2(playerid));
			ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
			ApplyAnimation(otherid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
		}
		else if(strcmp(name,"rokok",true) == 0)
		{
			if(ammount < 1) return SendClientMessage(playerid, 0xCECECEFF, "tidak bisa kurang dari 1");

			if(pData[playerid][pRokok] < ammount)
				return Error(playerid, "Item anda tidak cukup.");

			pData[playerid][pRokok] -= ammount;
			pData[otherid][pRokok] += ammount;
			SendClientMessageEx(playerid, COLOR_YELLOW, "* You given %d cigar to %s", ammount, ReturnName2(playerid));
			SendClientMessageEx(otherid, COLOR_YELLOW, "* You received %d cigar from %s", ammount, ReturnName2(playerid));
			ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
			ApplyAnimation(otherid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
		}
		else if(strcmp(name,"material",true) == 0)
		{
			if(ammount < 1) return SendClientMessage(playerid, 0xCECECEFF, "tidak bisa kurang dari 1");

			if(pData[playerid][pMaterial] < ammount)
				return Error(playerid, "Item anda tidak cukup.");

			pData[playerid][pMaterial] -= ammount;
			pData[otherid][pMaterial] += ammount;
			SendClientMessageEx(playerid, COLOR_YELLOW, "* You given %d materials to %s", ammount, ReturnName2(playerid));
			SendClientMessageEx(otherid, COLOR_YELLOW, "* You received %d materials from %s", ammount, ReturnName2(playerid));
			ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
			ApplyAnimation(otherid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
		}
		else if(strcmp(name,"component",true) == 0)
		{
			if(ammount < 1) return SendClientMessage(playerid, 0xCECECEFF, "tidak bisa kurang dari 1");

			if(pData[playerid][pComponent] < ammount)
				return Error(playerid, "Item anda tidak cukup.");

			pData[playerid][pComponent] -= ammount;
			pData[otherid][pComponent] += ammount;
			SendClientMessageEx(playerid, COLOR_YELLOW, "* You given %d components to %s", ammount, ReturnName2(playerid));
			SendClientMessageEx(otherid, COLOR_YELLOW, "* You received %d components from %s", ammount, ReturnName2(playerid));
			ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
			ApplyAnimation(otherid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
		}
		else if(strcmp(name,"crack",true) == 0)
		{
			if(ammount < 1) return SendClientMessage(playerid, 0xCECECEFF, "tidak bisa kurang dari 1");

			if(pData[playerid][pCrack] < ammount)
				return Error(playerid, "Item anda tidak cukup.");

			pData[playerid][pCrack] -= ammount;
			pData[otherid][pCrack] += ammount;
			SendClientMessageEx(playerid, COLOR_YELLOW, "* You given %d crack to %s", ammount, ReturnName2(playerid));
			SendClientMessageEx(otherid, COLOR_YELLOW, "* You received %d crack from %s", ammount, ReturnName2(playerid));
			ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
			ApplyAnimation(otherid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
		}
		else if(strcmp(name,"pot",true) == 0)
		{
			if(ammount < 1) return SendClientMessage(playerid, 0xCECECEFF, "tidak bisa kurang dari 1");

			if(pData[playerid][pPot] < ammount)
				return Error(playerid, "Item anda tidak cukup.");

			pData[playerid][pPot] -= ammount;
			pData[otherid][pPot] += ammount;
			SendClientMessageEx(playerid, COLOR_YELLOW, "* You given %d pot to %s", ammount, ReturnName2(playerid));
			SendClientMessageEx(otherid, COLOR_YELLOW, "* You received %d pot from %s", ammount, ReturnName2(playerid));
			ApplyAnimation(playerid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
			ApplyAnimation(otherid, "DEALER", "shop_pay", 4.0, 0, 0, 0, 0, 0);
		}
	}
	return 1;
}

CMD:usesprunk(playerid, params[])
{
	if(IsPlayerConnected(playerid)) 
	{
		if(pData[playerid][pSprunk] < 1)
			return Error(playerid, "Anda tidak memiliki sprunk.");

		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_SPRUNK);
		pData[playerid][pSprunk]--;
	}
	return 1;
}
	
CMD:use(playerid, params[])
{
	if(IsPlayerConnected(playerid)) 
	{
        if(isnull(params)) 
		{
            Usage(playerid, "USAGE: /use [name]");
            Info(playerid, "Names: bandage, snack, sprunk, cigar, gas, medicine, crack, pot");
            return 1;
        }
		if(strcmp(params,"bandage",true) == 0) 
		{
			if(pData[playerid][pBandage] < 1)
				return Error(playerid, "Anda tidak memiliki perban.");
			
			new Float:darah;
			GetPlayerHealth(playerid, darah);
			if(darah+10 > 99) return Error(playerid, "You can't use bandage anymore");
			SetPlayerHealthEx(playerid, darah+10);
			
			pData[playerid][pBandage]--;
			SendClientMessageEx(playerid, COLOR_ARWIN, "USE: "WHITE_E"Anda telah berhasil menggunakan perban.");
		}
		else if(strcmp(params,"snack",true) == 0) 
		{
			if(pData[playerid][pSnack] < 1) return Error(playerid, "Anda tidak memiliki snack.");
			
			pData[playerid][pSnack]--;
			if(pData[playerid][pHunger]+10 > 100) pData[playerid][pHunger] = 100;
			else pData[playerid][pHunger] += 10;
			SendClientMessageEx(playerid, COLOR_ARWIN, "USE: "WHITE_E"Anda telah berhasil menggunakan snack.");
			ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
		}
		else if(strcmp(params,"sprunk",true) == 0) 
		{
			if(pData[playerid][pSprunk] < 1) return Error(playerid, "Anda tidak memiliki sprunk.");

			pData[playerid][pSprunk]--;
			if(pData[playerid][pEnergy]+10 > 100) pData[playerid][pEnergy] = 100;
			else pData[playerid][pEnergy] += 10;
			SendClientMessageEx(playerid, COLOR_ARWIN, "USE: "WHITE_E"Anda telah berhasil meminum sprunk.");
			ApplyAnimation(playerid, "VENDING", "VEND_Drink2_P", 4.1, 0, 0, 0, 0, 0, 1);
		}
		else if(strcmp(params,"cigar",true) == 0) 
		{
			if(pData[playerid][pRokok] < 1)
				return Error(playerid, "Anda tidak memiliki rokok.");

			new Float:darah;
			GetPlayerHealth(playerid, darah);
			SetPlayerHealthEx(playerid, darah+10);
			ApplyAnimation(playerid,"SMOKING","M_smklean_loop",4.1, 0, 1, 1, 1, 1, 1);
			pData[playerid][pRokok]--;

		}
		else if(strcmp(params,"gas",true) == 0) 
		{
			if(pData[playerid][pGas] < 1) return Error(playerid, "Anda tidak memiliki gas.");
			if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Anda harus berada diluar kendaraan!");
			if(pData[playerid][pActivityTime] > 5) return Error(playerid, "Anda masih memiliki activity progress!");
			new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);
			if(IsValidVehicle(vehicleid))
			{
				new fuel = GetVehicleFuel(vehicleid);
			
				if(GetEngineStatus(vehicleid)) return Error(playerid, "Turn off vehicle engine.");
				if(fuel >= 999.0) return Error(playerid, "This vehicle gas is full.");
				if(!IsEngineVehicle(vehicleid)) return Error(playerid, "This vehicle can't be refull.");
				if(!GetHoodStatus(vehicleid)) return Error(playerid, "The hood must be opened before refull the vehicle.");
				pData[playerid][pGas]--;
				Info(playerid, "Don't move from your position or you will failed to refulling this vehicle.");
				ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
				PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Refulling");
				for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
				pData[playerid][pActivity] = SetTimerEx("RefullCar", 1000, true, "id", playerid, vehicleid);
				return 1;
			}
		}
		else if(strcmp(params,"medicine",true) == 0) 
		{
			if(pData[playerid][pMedicine] < 1) return Error(playerid, "Anda tidak memiliki medicine.");
			
			pData[playerid][pMedicine]--;
			pData[playerid][pSick] = 0;
			pData[playerid][pSickTime] = 0;
			SetPlayerDrunkLevel(playerid, 0);
			SendClientMessageEx(playerid, COLOR_ARWIN, "USE: "WHITE_E"Anda menggunakan medicine.");		
			ApplyAnimation(playerid,"SMOKING","M_smkstnd_loop",2.1,0,0,0,0,0);
		}
        else if(strcmp(params,"medkit",true) == 0)
		{
			if(pData[playerid][pMedkit] < 1) return Error(playerid, "Anda tidak memiliki medicine.");

			pData[playerid][pMedkit]--;
			pData[playerid][pSick] = 0;
			pData[playerid][pSickTime] = 0;
			
			new Float:darah;
			GetPlayerHealth(playerid, darah);
			if(darah+30 > 99) return Error(playerid, "You can't use medkit anymore");
			SetPlayerHealthEx(playerid, darah+30);
			
			SendClientMessageEx(playerid, COLOR_ARWIN, "USE: "WHITE_E"Anda menggunakan medicine.");
			ApplyAnimation(playerid,"SMOKING","M_smkstnd_loop",2.1,0,0,0,0,0);
		}
		else if(strcmp(params,"crack",true) == 0) 
		{
			if(pData[playerid][pCrack] < 1)
				return Error(playerid, "You dont have crack.");
			if(pData[playerid][pCough] >= 20) return Error(playerid, "You have a severe illness, can not consume excessive crack!.");
			
			new Float:armor;
			GetPlayerArmour(playerid, armor);
			if(armor+10 > 90) return Error(playerid, "You can't use crack anymore");
			
			pData[playerid][pCrack]--;
			pData[playerid][pCough]++;
			pData[playerid][pDrugTime] += RandomEx(10,15);
        	pData[playerid][pDrugUsed] = 1;
			SetPlayerArmourEx(playerid, armor+10);
			ApplyAnimation(playerid,"SMOKING","M_smkstnd_loop",2.1,0,0,0,0,0);
			SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 1000);
			SetPlayerWeather(playerid, -67);
			SetPlayerTime(playerid, 12, 12);
		}
		else if(strcmp(params,"pot",true) == 0) 
		{
			if(pData[playerid][pPot] < 1)
				return Error(playerid, "You dont have pot.");
			if(pData[playerid][pCough] >= 20) return Error(playerid, "You have a severe illness, can not consume excessive crack!.");
			
			new Float:armor;
			GetPlayerArmour(playerid, armor);
			if(armor+5 > 25) return Error(playerid, "You can't use pot anymore");
			
			pData[playerid][pPot]--;
			pData[playerid][pCough]++;
			pData[playerid][pDrugTime] += RandomEx(10,15);
        	pData[playerid][pDrugUsed] = 2;
			SetPlayerArmourEx(playerid, armor+5);
			ApplyAnimation(playerid,"SMOKING","M_smkstnd_loop",2.1,0,0,0,0,0);
			SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 1000);
			SetPlayerWeather(playerid, -67);
			SetPlayerTime(playerid, 12, 12);
		}
	}
	return 1;
}

CMD:enter(playerid, params[])
{
	if(pData[playerid][pInjured] == 0)
    {
		foreach(new did : Doors)
		{
			if(IsPlayerInDynamicCP(playerid, dData[did][dCP][0]))
			{
				if(!Door_HasInterior(did)) return Error(playerid, "Interior entrance masih kosong, atau tidak memiliki interior.");
				if(dData[did][dLocked]) return Error(playerid, "This entrance is locked at the moment.");
				if(pData[playerid][pArrest] == 1) return Error(playerid, "You are under arrest!");
				if(dData[did][dFaction] > 0) if(dData[did][dFaction] != pData[playerid][pFaction]) return Error(playerid, "This door only for faction.");
				if(dData[did][dFamily] > 0) if(dData[did][dFamily] != pData[playerid][pFamily]) return Error(playerid, "This door only for family.");
				if(dData[did][dVip] > pData[playerid][pVip]) return Error(playerid, "Your VIP level not enough to enter this door.");
				if(dData[did][dAdmin] > pData[playerid][pAdmin]) return Error(playerid, "Your admin level not enough to enter this door.");
					
				if(strlen(dData[did][dPass]))
				{
					new strr[256];
					if(sscanf(strr, "s[256]", strr)) return Usage(playerid, "/enter [password]");
					if(strcmp(strr, dData[did][dPass])) return Error(playerid, "Invalid door password.");
					
					if(dData[did][dCustom]) SetPlayerPositionEx(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
					else SetPlayerPositionEx(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
					pData[playerid][pInDoor] = did;
					SetPlayerInterior(playerid, dData[did][dIntint]);
					SetPlayerVirtualWorld(playerid, dData[did][dIntvw]);
					SetCameraBehindPlayer(playerid);
					SetPlayerWeather(playerid, 0);
				}
				else
				{
					if(dData[did][dCustom]) SetPlayerPositionEx(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
					else SetPlayerPositionEx(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
					pData[playerid][pInDoor] = did;
					SetPlayerInterior(playerid, dData[did][dIntint]);
					SetPlayerVirtualWorld(playerid, dData[did][dIntvw]);
					SetCameraBehindPlayer(playerid);
					SetPlayerWeather(playerid, 0);
				}
			}
			if(IsPlayerInDynamicCP(playerid, dData[did][dCP][1]))
			{
				if(dData[did][dFaction] > 0) if(dData[did][dFaction] != pData[playerid][pFaction]) return Error(playerid, "This door only for faction.");
				if(pData[playerid][pArrest] == 1) return Error(playerid, "You are under arrest!");

				if(dData[did][dCustom]) SetPlayerPositionEx(playerid, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtposA]);
				else SetPlayerPositionEx(playerid, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtposA]);

				pData[playerid][pInDoor] = -1;
				SetPlayerInterior(playerid, dData[did][dExtint]);
				SetPlayerVirtualWorld(playerid, dData[did][dExtvw]);
				SetCameraBehindPlayer(playerid);
				SetPlayerWeather(playerid, current_weather);
				Streamer_UpdateEx(playerid, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ]);
				pData[playerid][pInt] = 0;
				pData[playerid][pWorld] = 0;
			}
		}
		//Houses
		foreach(new hid : Houses)
		{
			if(IsPlayerInDynamicCP(playerid, hData[hid][hCP][0]))
			{
				if(hData[hid][hIntposX] == 0.0 && hData[hid][hIntposY] == 0.0 && hData[hid][hIntposZ] == 0.0)
					return Error(playerid, "Interior house masih kosong, atau tidak memiliki interior.");

				if(hData[hid][hLocked])
					return Error(playerid, "This house is locked!");
				
				pData[playerid][pInHouse] = hid;
				SetPlayerPositionEx(playerid, hData[hid][hIntposX], hData[hid][hIntposY], hData[hid][hIntposZ], hData[hid][hIntposA]);

				SetPlayerInterior(playerid, hData[hid][hInt]);
				SetPlayerVirtualWorld(playerid, hid);
				SetCameraBehindPlayer(playerid);
				SetPlayerWeather(playerid, 0);
				if(!hData[hid][house_Lights]) TextDrawShowForPlayer(playerid, HouseLight);
			}
			if(IsPlayerInDynamicCP(playerid, hData[hid][hCP][1]))
			{
				pData[playerid][pInHouse] = -1;
				SetPlayerPositionEx(playerid, hData[hid][hExtposX], hData[hid][hExtposY], hData[hid][hExtposZ], hData[hid][hExtposA]);
				
				SetPlayerInterior(playerid, hData[hid][hExtInt]);
				SetPlayerVirtualWorld(playerid, hData[hid][hExtVw]);
				pData[playerid][pInt] = 0;
				pData[playerid][pWorld] = 0;
				SetCameraBehindPlayer(playerid);
				SetPlayerWeather(playerid, current_weather);
				TextDrawHideForPlayer(playerid, HouseLight);
			}
        }
		//Bisnis
		foreach(new bid : Bisnis)
		{
			if(IsPlayerInDynamicCP(playerid, bData[bid][bCP][0]))
			{
				if(bData[bid][bIntposX] == 0.0 && bData[bid][bIntposY] == 0.0 && bData[bid][bIntposZ] == 0.0) return Error(playerid, "Interior bisnis masih kosong, atau tidak memiliki interior.");
				if(bData[bid][bLocked]) return GameTextForPlayer(playerid, "~w~Biz ~r~Terkunci!", 1000, 5);
				if(bData[bid][bSegel] == 1) return GameTextForPlayer(playerid, "~w~Biz ini ~r~Disegel", 1000, 5);
				pData[playerid][pInBiz] = bid;
				SetPlayerPositionEx(playerid, bData[bid][bIntposX], bData[bid][bIntposY], bData[bid][bIntposZ], bData[bid][bIntposA]);
				SetPlayerInterior(playerid, bData[bid][bInt]);
				SetPlayerVirtualWorld(playerid, bid);
				SetCameraBehindPlayer(playerid);
				SetPlayerWeather(playerid, 0);
				PlayStream(playerid, bData[bid][bStream], bData[bid][bIntposX], bData[bid][bIntposY], bData[bid][bIntposZ], 30.0, 1);
			}
			if(IsPlayerInDynamicCP(playerid, bData[bid][bCP][1])) {
				SetPlayerPositionEx(playerid, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ], bData[bid][bExtposA]);
				SetPlayerInterior(playerid, bData[bid][bExtInt]);
				SetPlayerVirtualWorld(playerid, bData[bid][bExtVw]);
				SetCameraBehindPlayer(playerid);
				SetPlayerWeather(playerid, current_weather);
				StopStream(playerid);
				pData[playerid][pInt] = 0;
				pData[playerid][pWorld] = 0;
			}
        }
		//Family
		foreach(new fid : FAMILYS)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.8, fData[fid][fExtposX], fData[fid][fExtposY], fData[fid][fExtposZ]))
			{
				if(fData[fid][fIntposX] == 0.0 && fData[fid][fIntposY] == 0.0 && fData[fid][fIntposZ] == 0.0) return Error(playerid, "Interior masih kosong, atau tidak memiliki interior.");
				if(pData[playerid][pFaction] == 0) if(pData[playerid][pFamily] == -1) return Error(playerid, "You dont have registered for this door!");
				SetPlayerPositionEx(playerid, fData[fid][fIntposX], fData[fid][fIntposY], fData[fid][fIntposZ], fData[fid][fIntposA]);
				SetPlayerInterior(playerid, fData[fid][fInt]);
				SetPlayerVirtualWorld(playerid, fid);
				SetCameraBehindPlayer(playerid);
				SetPlayerWeather(playerid, 0);
			}
			if(IsPlayerInRangeOfPoint(playerid, 2.8, fData[fid][fIntposX], fData[fid][fIntposY], fData[fid][fIntposZ]))
			{
				SetPlayerPositionEx(playerid, fData[fid][fExtposX], fData[fid][fExtposY], fData[fid][fExtposZ], fData[fid][fExtposA]);

				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetCameraBehindPlayer(playerid);
				SetPlayerWeather(playerid, current_weather);
				//pData[playerid][pInBiz] = -1;
			}
        }
	}
	return 1;
}

CMD:inspect(playerid, params[])
{
	new String[500], giveplayerid;

	if(sscanf(params, "u", giveplayerid))
        return Usage(playerid, "/inspect [playerid/PartOfName]");

	if(giveplayerid == INVALID_PLAYER_ID)
		return Error(playerid, "Invalid playerid!");

	if(!NearPlayer(playerid, giveplayerid, 5.0)) return Error(playerid, "Invalid playerid!");

    format(String, sizeof(String), "INSPECT: {FF0000}%s {FFFFFF}ingin meng-inspect anda, {FFFF00}/accept inspect {FFFFFF}untuk memberi izin untuk meng-inspect anda", ReturnName2(playerid));
    SendClientMessageEx(giveplayerid, COLOR_ARWIN, String);
    format(String, sizeof(String), "INSPECT: {FFFFFF}Anda telah merequest izin kepada {FF0000}%s {FFFFFF}untuk memeriksa kondisi anda", ReturnName2(giveplayerid));
    SendClientMessageEx(playerid, COLOR_ARWIN, String);
    pData[giveplayerid][nspectOffer] = playerid;

	return 1;
}

CMD:drag(playerid, params[])
{
	new otherid;
    if(sscanf(params, "u", otherid)) return Usage(playerid, "/drag [playerid/PartOfName] || /undrag [playerid]");
    if(otherid == INVALID_PLAYER_ID) return Error(playerid, "That player is disconnected.");
    if(otherid == playerid) return Error(playerid, "You cannot drag yourself.");
    if(!NearPlayer(playerid, otherid, 5.0)) return Error(playerid, "You must be near this player.");
    if(!pData[otherid][pInjured]) return Error(playerid, "kamu tidak bisa drag orang yang tidak mati.");

    SetPVarInt(otherid, "DragBy", playerid);
    SendClientMessageEx(otherid, COLOR_ARWIN, "DRAG: "WHITE_E"%s Telah menawari drag kepada anda, /accept drag untuk menerimanya /deny drag untuk membatalkannya.", ReturnName(playerid));
	SendClientMessageEx(playerid, COLOR_ARWIN, "DRAG: "WHITE_E"Anda berhasil menawari drag kepada player %s", ReturnName(otherid));
    return 1;
}

CMD:undrag(playerid, params[])
{
	new otherid;
    if(sscanf(params, "u", otherid)) return Usage(playerid, "/undrag [playerid]");
	if(pData[otherid][pDragged])
    {
        DeletePVar(playerid, "DragBy");
        DeletePVar(otherid, "DragBy");
        pData[otherid][pDragged] = 0;
        pData[otherid][pDraggedBy] = INVALID_PLAYER_ID;

        KillTimer(pData[otherid][pDragTimer]);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s releases %s from their grip.", ReturnName(playerid), ReturnName(otherid));
    }
    return 1;
}

//Mask
CMD:masked(playerid, params[])
{
	if(pData[playerid][pAdmin] < 1)
		if(pData[playerid][pHelper] == 0)
			return PermissionError(playerid);

    static
        name[24];

    SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");

    foreach (new i : Player) if(pData[i][pMaskOn]) {
        GetPlayerName(i, name, sizeof(name));

        SendClientMessageEx(playerid, COLOR_WHITE, "* %s (#%d)", name, pData[i][pMaskID]);
    }
    SendClientMessage(playerid, COLOR_GREY, "-----------------------------------------------------------");
    return 1;
}

CMD:togmask(playerid, params[]) 
{
	if(IsPlayerConnected(playerid))
	{
		if(pData[playerid][pMask] == 0)
		{
			 Error(playerid, "Anda tidak memiliki mask.");
			 return 1;
		}
        if(pData[playerid][pLevel] < 3) {
            Error(playerid, "Anda belum mencapai level 3");
            return 1;
        }
		if(pData[playerid][pMaskOn] == 0)
		{
		    if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
		    	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("Mask_#%d", pData[playerid][pMaskID])));
			SendClientMessageEx(playerid, COLOR_ARWIN, "MASKINFO: "WHITE_E"Mask {00D900}ON!");
            pData[playerid][pMaskOn] = 1;
		}
		else if(pData[playerid][pMaskOn] == 1)
		{
		    if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
		        UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s {ffffff}(%d)", ReturnName2(playerid), playerid)));

            pData[playerid][pMaskOn] = 0;
			SendClientMessageEx(playerid, COLOR_ARWIN, "MASKINFO: "WHITE_E"Mask {FF0000}OFF!");
		}
	}
	return 1;
}

/*CMD:togmask(playerid, params[]) {
    if(IsPlayerConnected(playerid)){
        if(pData[playerid][pMask] == 0){
             Error(playerid, "Anda tidak memiliki mask.");
             return 1;
        }
        if(pData[playerid][pLevel] < 3){
            Error(playerid, "Anda belum mencapai level 3");
            return 1;
        }
        if(pData[playerid][pMaskOn] == 0)
        {
            for(new i = 0; i < MAX_PLAYERS; i++)
            {
                    new string[128];
                    ShowPlayerNameTagForPlayer(i, playerid, false);
                    pData[playerid][pMaskOn] = 1;
                    format(string, sizeof(string), "Mask_#%d\nH: ["RED_E"%.1f"WHITE_E"] A: [%.1f]", pData[playerid][pMaskID], pData[playerid][pHealth], pData[playerid][pArmour]);
                    MaskLabel[playerid] = CreateDynamic3DTextLabel(string, -1, 0, 0, -10, 10.0, playerid);
                    Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, MaskLabel[playerid] , E_STREAMER_ATTACH_OFFSET_Z, 0.30);
                    SendClientMessage(playerid, COLOR_WHITE, "MASKINFO: Mask {00D900}ON!");
                    return 1;
            }
        }
        else if(pData[playerid][pMaskOn] == 1)
        {
            for(new i = 0; i < MAX_PLAYERS; i++)
            {
                    ShowPlayerNameTagForPlayer(i, playerid, true);
                    pData[playerid][pMaskOn] = 0;
                    DestroyDynamic3DTextLabel(MaskLabel[playerid]);
                    SendClientMessage(playerid, COLOR_WHITE, "MASKINFO: Mask {FF0000}OFF!");
                    return 1;
            }
        }
    }
    return 1;
}*/

//Text and Chat Commands
CMD:try(playerid, params[])
{
    if(isnull(params)) return Usage(playerid, "/try [action]");
	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
	if(pData[playerid][pTogChat]) params[0] = toupper(params[0]);
    if(strlen(params) > 64) 
	{
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s %.64s ..", ReturnName(playerid), params);
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, ".. %s, %s", params[64], (random(2) == 0) ? ("and success") : ("but fail"));
    }
    else  SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s %s, %s", ReturnName(playerid), params, (random(2) == 0) ? ("and success") : ("but fail"));
    return 1;
}

CMD:delado(playerid, params[])
{
    if (!pData[playerid][pAdoActive]) return Error(playerid, "You're not actived your 'ado' text.");
    if (IsValidDynamic3DTextLabel(pData[playerid][pAdoTag])) DestroyDynamic3DTextLabel(pData[playerid][pAdoTag]);
    SendClientMessageEx(playerid, COLOR_ARWIN, "ADO: "WHITE_E"You're removed your ado text.");
    pData[playerid][pAdoActive] = false;
    return 1;
}


CMD:ado(playerid, params[])
{
    new flyingtext[164], Float:x, Float:y, Float:z;

    if(isnull(params))
	{
        Usage(playerid, "/ado [text]");
		return 1;
	}
    if(strlen(params) > 128) return Error(playerid, "Max text can only maximmum 128 characters.");

    FixText(params);
    format(flyingtext, sizeof(flyingtext), "* %s *\n(( %s ))", ReturnName(playerid), params);

	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
	if(pData[playerid][pTogChat]) params[0] = toupper(params[0]);
    if(strlen(params) > 64) 
	{
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* [ADO]: %.64s ..", params);
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, ".. %s", params[64]);
    }
    else  SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* [ADO]: %s", params);
    GetPlayerPos(playerid, x, y, z);
    if(pData[playerid][pAdoActive])
    {
        if (IsValidDynamic3DTextLabel(pData[playerid][pAdoTag])) UpdateDynamic3DTextLabelText(pData[playerid][pAdoTag], COLOR_PURPLE, flyingtext);
        else pData[playerid][pAdoTag] = CreateDynamic3DTextLabel(flyingtext, COLOR_PURPLE, x, y, z, 15, _, _, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    }
    else
    {
        pData[playerid][pAdoActive] = true;
        pData[playerid][pAdoTag] = CreateDynamic3DTextLabel(flyingtext, COLOR_PURPLE, x, y, z, 15, _, _, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    }
	printf("[ADO] %s(%d) : %s", ReturnName(playerid), playerid, params);
    return 1;
}

CMD:ame(playerid, params[])
{
    new flyingtext[164];

    if(isnull(params)) return Usage(playerid, "/ame [action]");
    if(strlen(params) > 40) return Error(playerid, "Max action can only maximmum 40 characters.");
	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
	if(pData[playerid][pTogChat]) params[0] = toupper(params[0]);
    format(flyingtext, sizeof(flyingtext), "* %s %s*", ReturnName(playerid), params);
    SetPlayerChatBubble(playerid, flyingtext, COLOR_PURPLE, 10.0, 10000);
	printf("[AME] %s(%d) : %s", ReturnName(playerid), playerid, params);
	SendClientMessageEx(playerid, COLOR_WHITE, "AME: {D0AEEB}%s", params);
    return 1;
}

CMD:me(playerid, params[])
{
    if(isnull(params))
        return Usage(playerid, "/me [action]");
	
	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
	if(pData[playerid][pTogChat]) params[0] = toupper(params[0]);
    if(strlen(params) > 64) 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s %.64s ..", name, params);
        	SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "...%s", params[64]);
		}
		else
		{
			SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s %.64s ..", ReturnName2(playerid), params);
        	SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "...%s", params[64]);
		}
    }
    else 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s %s", name, params);
		}
		else
		{
			SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s %s", ReturnName2(playerid), params);
		}
    }
    return 1;
}

CMD:lme(playerid, params[])
{
    if(isnull(params))
        return Usage(playerid, "/lme [action]");
	
	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
	if(pData[playerid][pTogChat]) params[0] = toupper(params[0]);
    if(strlen(params) > 64) 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 5.0, COLOR_LME, "* %s %.64s ..", name, params);
        	SendNearbyMessage(playerid, 5.0, COLOR_LME, "...%s", params[64]);
		}
		else
		{
			SendNearbyMessage(playerid, 5.0, COLOR_LME, "* %s %.64s ..", ReturnName2(playerid), params);
        	SendNearbyMessage(playerid, 5.0, COLOR_LME, "...%s", params[64]);
		}
    }
    else 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 5.0, COLOR_LME, "* %s %s", name, params);
		}
		else
		{
			SendNearbyMessage(playerid, 5.0, COLOR_LME, "* %s %s", ReturnName2(playerid), params);
		}
    }
    return 1;
}

CMD:do(playerid, params[])
{
    if(isnull(params))
        return Usage(playerid, "/do [description]");

	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
	if(pData[playerid][pTogChat]) params[0] = toupper(params[0]);
	if(strlen(params) > 64) 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %.64s ..", params);
        	SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "... %s (( %s ))", params[64], name);
		}
		else
		{
			SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %.64s ..", params);
        	SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "... %s (( %s ))", params[64], ReturnName2(playerid));
		}
    }
    else 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s (( %s ))", params, name);
		}
		else
		{
			SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s (( %s ))", params, ReturnName2(playerid));
		}
    }
    return 1;
}

CMD:ldo(playerid, params[])
{
    if(isnull(params))
        return Usage(playerid, "/ldo [description]");

	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
	if(pData[playerid][pTogChat]) params[0] = toupper(params[0]);
	if(strlen(params) > 64) 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 5.0, COLOR_LME, "* %.64s ..", params);
        	SendNearbyMessage(playerid, 5.0, COLOR_LME, "... %s (( %s ))", params[64], name);
		}
		else
		{
			SendNearbyMessage(playerid, 5.0, COLOR_LME, "* %.64s ..", params);
        	SendNearbyMessage(playerid, 5.0, COLOR_LME, "... %s (( %s ))", params[64], ReturnName2(playerid));
		}
    }
    else 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 5.0, COLOR_LME, "* %s (( %s ))", params, name);
		}
		else
		{
			SendNearbyMessage(playerid, 5.0, COLOR_LME, "* %s (( %s ))", params, ReturnName2(playerid));
		}
    }
    return 1;
}

CMD:togstaff(playerid)
{
	if(!pData[playerid][pTogStaffChat])
	{
		pData[playerid][pTogStaffChat] = 1;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan log server.");
	}
	else
	{
		pData[playerid][pTogStaffChat] = 0;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan log server.");
	}
	return 1;
}

CMD:togfaction(playerid)
{
	if(!pData[playerid][pTogFaction])
	{
		pData[playerid][pTogFaction] = 1;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan log server.");
	}
	else
	{
		pData[playerid][pTogFaction] = 0;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan log server.");
	}
	return 1;
}

CMD:togpm(playerid)
{
	if(!pData[playerid][pTogPM])
	{
		pData[playerid][pTogPM] = 1;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan PM");
	}
	else
	{
		pData[playerid][pTogPM] = 0;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan PM");
	}
	return 1;
}

CMD:togstream(playerid)
{
	if(!pData[playerid][pStreamMode])
	{
		pData[playerid][pStreamMode] = 1;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan stream mode");
	}
	else
	{
		pData[playerid][pStreamMode] = 0;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan stream mode");
	}
	return 1;
}

CMD:togradiostream(playerid)
{
	if(!pData[playerid][pRadioStream])
	{
		pData[playerid][pRadioStream] = 1;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan radio stream");
	}
	else
	{
		pData[playerid][pRadioStream] = 0;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan radio stream");
	}
	return 1;
}

CMD:togvip(playerid)
{
	if(!pData[playerid][pTogVip])
	{
		pData[playerid][pTogVip] = 1;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan Chat VIP");
	}
	else
	{
		pData[playerid][pTogVip] = 0;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan Chat VIP");
	}
	return 1;
}

CMD:togads(playerid)
{
	if(!pData[playerid][pTogAds])
	{
		pData[playerid][pTogAds] = 1;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan Ads/Iklan.");
	}
	else
	{
		pData[playerid][pTogAds] = 0;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan Ads/Iklan.");
	}
	return 1;
}

CMD:togwt(playerid)
{
	if(!pData[playerid][pTogWT])
	{
		pData[playerid][pTogWT] = 1;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan Walkie Talkie.");
	}
	else
	{
		pData[playerid][pTogWT] = 0;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan Walkie Talkie.");
	}
	return 1;
}
CMD:togradio(playerid)
{
	if(!pData[playerid][pTogRadio])
	{
		pData[playerid][pTogRadio] = 1;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan Radio.");
	}
	else
	{
		pData[playerid][pTogRadio] = 0;
		SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan Radio.");
	}
	return 1;
}

CMD:apm(playerid, params[])
{
    static
        userid,
            text[128];

	if(pData[playerid][pAdmin] < 1) if(pData[playerid][pHelper] < 2) return PermissionError(playerid);

    if(sscanf(params, "us[128]", userid, text))
        return Usage(playerid, "/apm [playerid/PartOfName] [message]");

    if(userid == INVALID_PLAYER_ID)
        return Error(playerid, "You have specified an invalid player.");

    SendClientMessageEx(userid, COLOR_YELLOW, "PM from "RED_E"Admin: %s", text);
    SendStaffMessage(COLOR_YELLOW, "(!) "YELLOW_E"%s "WHITE_E"APMED to "RED_E"%s"WHITE_E"(%d) for: "YELLOW_E"%s", pData[playerid][pAdminname], ReturnName2(userid), userid, text);
    return 1;
}

CMD:pm(playerid, params[])
{
	if(!IsPlayerConnected(playerid)) return SendClientMessage(playerid,-1, "{FFFF00}[Informasi]{FFFFFF} Anda belum login!");
	if(pData[playerid][pSpawned] == 0)
	{
		Error(playerid, "Anda sedang tidak spawn!");
		return 1;
	}
	
    static text[128], otherid;
    if(sscanf(params, "us[128]", otherid, text))
        return Usage(playerid, "/pm [playerid/PartOfName] [message]");
		
	if(otherid == INVALID_PLAYER_ID)
        return Error(playerid, "You have specified an invalid player.");

    // if(otherid == playerid)
    //     return Error(playerid, "You can't private message yourself.");

    if(pData[otherid][pTogPM] && pData[playerid][pAdmin] < 1)
        return Error(playerid, "That player has disabled private messaging.");

    PlayerPlaySound(otherid, 1085, 0.0, 0.0, 0.0);

    SendClientMessageEx(otherid, COLOR_YELLOW, "(( PM from %s (%d): %s ))", ReturnName2(playerid), playerid, text);
    SendClientMessageEx(playerid, COLOR_YELLOW, "(( PM to %s (%d): %s ))", ReturnName2(otherid), otherid, text);
    SendAdminMessage(COLOR_LIGHTGREEN, ""YELLOW_E"[SPY PM] %s (%d) to %s (%d): %s", ReturnName2(playerid), playerid, ReturnName2(otherid), otherid, text);
    return 1;
}

CMD:whisper(playerid, params[])
{
	new text[128], otherid;
    if(sscanf(params, "us[128]", otherid, text))
        return Usage(playerid, "/(w)hisper [playerid/PartOfName] [text]");

    if(otherid == INVALID_PLAYER_ID || !NearPlayer(playerid, otherid, 5.0))
        return Error(playerid, "That player is disconnected or not near you.");

    if(otherid == playerid)
        return Error(playerid, "You can't whisper yourself.");

	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
	if(pData[playerid][pTogChat]) params[0] = toupper(params[0]);
    if(strlen(text) > 64) 
	{
        SendClientMessageEx(otherid, COLOR_YELLOW, "** Whisper from %s (%d): %.64s", ReturnName2(playerid), playerid, text);
        SendClientMessageEx(otherid, COLOR_YELLOW, "...%s **", text[64]);

        SendClientMessageEx(playerid, COLOR_YELLOW, "** Whisper to %s (%d): %.64s", ReturnName2(otherid), otherid, text);
        SendClientMessageEx(playerid, COLOR_YELLOW, "...%s **", text[64]);
    }
    else 
	{
        SendClientMessageEx(otherid, COLOR_YELLOW, "** Whisper from %s (%d): %s **", ReturnName2(playerid), playerid, text);
        SendClientMessageEx(playerid, COLOR_YELLOW, "** Whisper to %s (%d): %s **", ReturnName2(otherid), otherid, text);
    }
    SendNearbyMessage(playerid, 10.0, COLOR_PURPLE, "* %s mutters something in %s's ear.", ReturnName2(playerid), ReturnName2(otherid));
    SendAdminMessage(COLOR_YELLOW2, "[SPY WHISPER] %s (%d) to %s (%d): %s", ReturnName2(playerid), playerid, ReturnName2(otherid), otherid, text);
    return 1;
}

CMD:l(playerid, params[])
{
    if(isnull(params))
        return Usage(playerid, "/(l)ow [low text]");

	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
	if(pData[playerid][pTogChat]) params[0] = toupper(params[0]);
    if(strlen(params) > 64) 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 5.0, COLOR_WHITE, "[low] %s says: %.64s ..", name, params);
        	SendNearbyMessage(playerid, 5.0, COLOR_WHITE, "...%s!", params[64]);
		}
		else
		{
			SendNearbyMessage(playerid, 5.0, COLOR_WHITE, "[low] %s says: %.64s ..", ReturnName2(playerid), params);
        	SendNearbyMessage(playerid, 5.0, COLOR_WHITE, "...%s", params[64]);
		}
    }
    else 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 5.0, COLOR_WHITE, "[low] %s says: %s", name, params);
		}
		else
		{
			SendNearbyMessage(playerid, 5.0, COLOR_WHITE, "[low] %s says: %s", ReturnName2(playerid), params);
		}
    }
    return 1;
}

CMD:c(playerid, params[])
{
    if(isnull(params))
        return Usage(playerid, "/(c)ar [car chat]");

	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
	if(pData[playerid][pTogChat]) params[0] = toupper(params[0]);
	if(IsPlayerInAnyVehicle(playerid))
	{
		foreach(new i : Player)
		{
			if(IsPlayerInAnyVehicle(i) && GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid))
			{
				if(strlen(params) > 64) 
				{
					if(pData[playerid][pMaskOn] == 1)
					{
						new name[52];
						format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
						SendClientMessageEx(i, COLOR_WHITE, "[car] %s says: %.64s ..", name, params);
						SendClientMessageEx(i, COLOR_WHITE, "...%s", params[64]);
					}
					else
					{
						SendClientMessageEx(i, COLOR_WHITE, "[car] %s says: %.64s ..", ReturnName2(playerid), params);
						SendClientMessageEx(i, COLOR_WHITE, "...%s", params[64]);
					}
				}
				else 
				{
					if(pData[playerid][pMaskOn] == 1)
					{
						new name[52];
						format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
						SendClientMessageEx(i, COLOR_WHITE, "[car] %s says: %s", name, params);
					}
					else
					{
						SendClientMessageEx(i, COLOR_WHITE, "[car] %s says: %s", ReturnName2(playerid), params);
					}
				}
			}
		}
	}
	return 1;
}

CMD:s(playerid, params[])
{
	new mstr[212];
    if(isnull(params))
        return Usage(playerid, "/(s)hout [shout text] /ds for in the door");

	if(GetPVarType(playerid, "Caps")) UpperToLower(params);
	if(pData[playerid][pTogChat]) params[0] = toupper(params[0]);
    if(strlen(params) > 64) 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 30.0, COLOR_WHITE, "%s shouts: %.64s ..", name, params);
        	SendNearbyMessage(playerid, 30.0, COLOR_WHITE, "...%s!", params[64]);
       		format(mstr, sizeof(mstr), "[shout] %s!", params);
		}
		else
		{
			SendNearbyMessage(playerid, 30.0, COLOR_WHITE, "%s shouts: %.64s ..", ReturnName2(playerid), params);
        	SendNearbyMessage(playerid, 30.0, COLOR_WHITE, "...%s!", params[64]);
       		format(mstr, sizeof(mstr), "[shout] %s!", params);		}
    }
    else 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 30.0, COLOR_WHITE, "%s shouts: %s!", name, params);
       		format(mstr, sizeof(mstr), "[shout] %s!", params);
		}
		else
		{
			SendNearbyMessage(playerid, 30.0, COLOR_WHITE, "%s shouts: %s!", ReturnName2(playerid), params);
       		format(mstr, sizeof(mstr), "[shout] %s!", params);
   		}
    }
    return 1;
}

CMD:b(playerid, params[])
{
    if(isnull(params))
        return Usage(playerid, "/b [local OOC]");
	
	if(pData[playerid][pTogChat]) params[0] = toupper(params[0]);
    if(strlen(params) > 64) 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 20.0, COLOR_WHITE, "%s: (( %.64s ..", name, params);
        	SendNearbyMessage(playerid, 20.0, COLOR_WHITE, "... %s ))", params[64]);
		}
		else
		{
			SendNearbyMessage(playerid, 20.0, COLOR_WHITE, "%s: (( %.64s ..", ReturnName2(playerid), params);
        	SendNearbyMessage(playerid, 20.0, COLOR_WHITE, "...%s ))", params[64]);
		}
    }
    else 
	{
		if(pData[playerid][pMaskOn] == 1)
		{
			new name[52];
			format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
			SendNearbyMessage(playerid, 20.0, COLOR_WHITE, "%s: (( %s ))", name, params);
		}
		else
		{
			SendNearbyMessage(playerid, 20.0, COLOR_WHITE, "%s: (( %s ))", ReturnName2(playerid), params);
		}
    }
    return 1;
}

CMD:setfq(playerid, params[])
{
	if(pData[playerid][pWT] == 0)
		return Error(playerid, "You dont have walkie talkie!");
		
 	if(pData[playerid][pLevel] == 1)
		return Error(playerid, "You must have level 3 or above");
		
  	if(pData[playerid][pLevel] == 2)
		return Error(playerid, "You must have level 3 or above");
	
	new channel;
	if(sscanf(params, "d", channel))
		return Usage(playerid, "/setfq [channel 1 - 1000]");
	
	if(pData[playerid][pTogWT] == 1) return Error(playerid, "Your walkie talkie is turned off.");
	if(channel == pData[playerid][pWT]) return Error(playerid, "You are already in this channel.");
	
	if(channel > 0 && channel <= 1000)
	{
		foreach(new i : Player)
		{
		    if(pData[i][pWT] == channel)
		    {
				SendClientMessageEx(i, COLOR_LIME, "[WT] "WHITE_E"%s has joined in to this channel!", ReturnName(playerid));
		    }
		}
		SendClientMessageEx(playerid, COLOR_WHITE, "[WT] Channel set to '%d'", channel);
		pData[playerid][pWT] = channel;
	}
	else
	{
		Error(playerid, "Invalid channel id! 1 - 1000");
	}
	return 1;
}

CMD:wt(playerid, params[])
{
	if(pData[playerid][pInjured] == 1)
        return Error(playerid, "You injured at the moment.");
    
	if(pData[playerid][pWT] == 0)
		return Error(playerid, "You dont have walkie talkie!");
		
	if(pData[playerid][pTogWT] == 1)
		return Error(playerid, "Your walkie talkie is turned off!");
	
	if(pData[playerid][pMuteWt] > 1)
		return PermissionError(playerid);

	new msg[128], mstr[512];
	if(sscanf(params, "s[128]", msg)) return Usage(playerid, "/wt [message]");
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	foreach(new i : Player)
	{
	    if(pData[i][pTogWT] == 0)
	    {
	        if(pData[i][pWT] == pData[playerid][pWT])
	        {
				if(IsPlayerInRangeOfPoint(i, 220.0, x, y, z))
				{
					if (pData[playerid][pStreamMode]) {
						SendClientMessageEx(i, COLOR_YELLOW, "[WT:%d] {75AE5D}%s : %s", pData[playerid][pWT], pData[playerid][pName], msg);
						format(mstr, sizeof(mstr), "[<WT>]\n* %s *", msg);
						SetPlayerChatBubble(i, mstr, COLOR_PINK, 10.0, 3000);
					}
					else
					{
						SendClientMessageEx(i, COLOR_YELLOW, "[WT] {75AE5D}%s : %s", pData[playerid][pName], msg);
						format(mstr, sizeof(mstr), "[<WT>]\n* %s *", msg);
						SetPlayerChatBubble(i, mstr, COLOR_PINK, 10.0, 3000);
					}
				}	
	        }
	    }
	}
	return 1;
}

CMD:license(playerid, params[])
{
	new giveplayerid;
	if(sscanf(params, "u", giveplayerid))
	{
		SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"Your license");
		SendClientMessageEx(playerid, COLOR_ARWIN, "1. {00FFFF}Driver license: %s", GetLicenseDriver(playerid));
		SendClientMessageEx(playerid, COLOR_ARWIN, "2. {00FFFF}Flying license: %s", GetLicenseFly(playerid));
		SendClientMessageEx(playerid, COLOR_ARWIN, "3. {00FFFF}Boating license: %s", GetLicenseBoat(playerid));
		SendClientMessageEx(playerid, COLOR_ARWIN, "4. {00FFFF}Heavy Truck license: %s", GetLicenseTrucker(playerid));
		SendClientMessageEx(playerid, COLOR_ARWIN, "5. {00FFFF}Lumberjack license: %s", GetLicenseLumber(playerid));
		SendClientMessageEx(playerid, COLOR_ARWIN, "6. {00FFFF}Weapon license: %s", GetLicenseGun(playerid));
		return 1;
	}
	if(giveplayerid == INVALID_PLAYER_ID || !NearPlayer(playerid, giveplayerid, 5.0)) return Error(playerid, "The specified player is disconnected or not near you.");
	SendClientMessageEx(giveplayerid, COLOR_ARWIN, "LICENSE: "WHITE_E"Your license");
	SendClientMessageEx(giveplayerid, COLOR_ARWIN, "1. {00FFFF}Driver license: %s", GetLicenseDriver(playerid));
	SendClientMessageEx(giveplayerid, COLOR_ARWIN, "2. {00FFFF}Flying license: %s", GetLicenseFly(playerid));
	SendClientMessageEx(giveplayerid, COLOR_ARWIN, "3. {00FFFF}Boating license: %s", GetLicenseBoat(playerid));
	SendClientMessageEx(giveplayerid, COLOR_ARWIN, "4. {00FFFF}Heavy Truck license: %s", GetLicenseTrucker(playerid));
	SendClientMessageEx(giveplayerid, COLOR_ARWIN, "5. {00FFFF}Lumberjack license: %s", GetLicenseLumber(playerid));
	SendClientMessageEx(giveplayerid, COLOR_ARWIN, "6. {00FFFF}Weapon license: %s", GetLicenseGun(playerid));
	return 1;
}

CMD:showidcard(playerid, params[])
{
	new otherid;
	if(sscanf(params, "u", otherid)) {
		SendClientMessageEx(playerid, -1, ""YELLOW_E"==========[ "AQUA_E"San Andreas Identification Card "YELLOW_E"]==========");
		SendClientMessageEx(playerid, -1, "Social Security : "GREEN_E"#SA0%d", pData[playerid][pID]);
		SendClientMessageEx(playerid, -1, "Full Name: "GREEN_E"%s", ReturnName2(playerid));
		SendClientMessageEx(playerid, -1, "Sex: "GREEN_E"%s", GetPlayerGender(playerid));
		SendClientMessageEx(playerid, -1, "Date Of Birth: "GREEN_E"%s", pData[playerid][pAge]);
		return 1;
	}
    if(otherid == INVALID_PLAYER_ID || !NearPlayer(playerid, otherid, 5.0)) return Error(playerid, "That player is disconnected or not near you.");
    SendClientMessageEx(otherid, -1, ""YELLOW_E"==========[ "AQUA_E"San Andreas Identification Card "YELLOW_E"]==========");
	SendClientMessageEx(otherid, -1, "Social Security : "GREEN_E"#%d", pData[playerid][pID]);
	SendClientMessageEx(otherid, -1, "Full Name: "GREEN_E"%s", ReturnName2(playerid));
	SendClientMessageEx(otherid, -1, "Sex: "GREEN_E"%s", GetPlayerGender(playerid));
	SendClientMessageEx(otherid, -1, "Date Of Birth: "GREEN_E"%s", pData[playerid][pAge]);
	return 1;
}

CMD:buycomponent(playerid, params[])
{
	//Component
	if(IsPlayerInRangeOfPoint(playerid, 3, 854.5825,-605.2015,18.4219))
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new mstr[128];
			format(mstr, sizeof(mstr), "Component Price: $0.50\nComponent Available: %d", StockComponent);
			Dialog_Show(playerid, DialogComponent, DIALOG_STYLE_INPUT, "Buy Component", mstr, "Buy", "Cancel");
		}
		else
		{
			if(pData[playerid][pComponent] >= 250) return Error(playerid, "Anda sudah membawa 250 Component!");
			new mstr[128];
			format(mstr, sizeof(mstr), "Component Price: $0.50\nComponent Available: %d", StockComponent);
			Dialog_Show(playerid, DialogComponent, DIALOG_STYLE_INPUT, "Buy Component", mstr, "Buy", "Cancel");
		}	
	}
	return 1;
}

//------------------[ Bisnis and Buy Commands ]-------
CMD:buy(playerid, params[])
{
	//Buy farm
	foreach(new ap : FARMS)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, laData[ap][laExtposX], laData[ap][laExtposY], laData[ap][laExtposZ]))
		{
			if(laData[ap][laPrice] > GetPlayerMoney(playerid)) return Error(playerid, "Not enough money, you can't afford this Farm.");
			if(strcmp(laData[ap][laOwner], "-")) return Error(playerid, "Someone already owns this Farm.");
			if(pData[playerid][pLadang] > 0)
				return Error(playerid, "Anda sudah mempunyai Farm");
			GivePlayerMoneyEx(playerid, -laData[ap][laPrice]);
			GetPlayerName(playerid, laData[ap][laOwner], MAX_PLAYER_NAME);
			pData[playerid][pLadang] = ap;
			pData[playerid][pLadangRank] = 6;
			Ladang_Refresh(ap);
			Ladang_Save(ap);
			SendClientMessageEx(playerid, COLOR_ARWIN, "FARM: "WHITE_E"Anda berhasil membeli farm dengan harga "GREEN_E"$%s", FormatMoney(laData[ap][laPrice]));
		}
	}
	//Buy Bisnis
	foreach(new suiteid : SuiteRooms)
	{
		if(IsPlayerInRangeOfPoint(playerid, 1.5, SuiteRoom[suiteid][suiteRoomButtons][0], SuiteRoom[suiteid][suiteRoomButtons][1], SuiteRoom[suiteid][suiteRoomButtons][2]))
		{
			if(SuiteRoom[suiteid][suiteRoomPrice] > GetPlayerMoney(playerid)) return Error(playerid, "Not enough money, you can't afford this bisnis.");
			if(strcmp(SuiteRoom[suiteid][suiteRoomOwner], "-")) return Error(playerid, "Someone already owns this private garage.");
			if(PropertiCommercial_CountMax(playerid) >= PropertiesCommercial_Max(playerid)) return Error(playerid, "You can no longer buy a business, your property slots are full");
			GivePlayerMoneyEx(playerid, -SuiteRoom[suiteid][suiteRoomPrice]);
			Server_AddMoney(-SuiteRoom[suiteid][suiteRoomPrice]);
			GetPlayerName(playerid, SuiteRoom[suiteid][suiteRoomOwner], MAX_PLAYER_NAME);

			SuiteRoom_Save(suiteid);
        	SuiteRoom_Refresh(suiteid);
		}
	}
	//Buy Bisnis
	foreach(new pvid : PrivateGarage)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, PrivateGarage[pvid][TextPos][0], PrivateGarage[pvid][TextPos][1], PrivateGarage[pvid][TextPos][2]))
		{
			if(PrivateGarage[pvid][Price] > GetPlayerMoney(playerid)) return Error(playerid, "Not enough money, you can't afford this bisnis.");
			if(strcmp(PrivateGarage[pvid][Owner], "-")) return Error(playerid, "Someone already owns this private garage.");
			if(PropertiCommercial_CountMax(playerid) >= PropertiesCommercial_Max(playerid)) return Error(playerid, "You can no longer buy a business, your property slots are full");
			GivePlayerMoneyEx(playerid, -PrivateGarage[pvid][Price]);
			Server_AddMoney(-PrivateGarage[pvid][Price]);
			GetPlayerName(playerid, PrivateGarage[pvid][Owner], MAX_PLAYER_NAME);

			PvGarageSave(pvid);
			PvGarageRefresh(pvid);
		}
	}
	//Buy Bisnis
	foreach(new bid : Bisnis)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]))
		{
			if(bData[bid][bPrice] > GetPlayerMoney(playerid)) return Error(playerid, "Not enough money, you can't afford this bisnis.");
			if(strcmp(bData[bid][bOwner], "-")) return Error(playerid, "Someone already owns this bisnis.");
			if(PropertiCommercial_CountMax(playerid) >= PropertiesCommercial_Max(playerid)) return Error(playerid, "You can no longer buy a business, your property slots are full");
			GivePlayerMoneyEx(playerid, -bData[bid][bPrice]);
			Server_AddMoney(-bData[bid][bPrice]);
			GetPlayerName(playerid, bData[bid][bOwner], MAX_PLAYER_NAME);
			bData[bid][bLastVisited] = gettime();
			
			Bisnis_Refresh(bid);
			Bisnis_Save(bid);
		}
		if(IsPlayerInRangeOfPoint(playerid, 3, bData[bid][bDriveThru][0], bData[bid][bDriveThru][1], bData[bid][bDriveThru][2])) {
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				pData[playerid][pInBiz] = bid;
				Bisnis_BuyMenu(playerid, pData[playerid][pInBiz]);
			}
			else return Error(playerid, "Anda tidak berada di point buy bisnis");
		}
	}
	//Buy Bisnis menu
	if(pData[playerid][pInBiz] >= 0 && IsPlayerInRangeOfPoint(playerid, 2.5, bData[pData[playerid][pInBiz]][bPointX], bData[pData[playerid][pInBiz]][bPointY], bData[pData[playerid][pInBiz]][bPointZ]))
	{
		Bisnis_BuyMenu(playerid, pData[playerid][pInBiz]);
	}
	//Buy House
	foreach(new hid : Houses)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, hData[hid][hExtposX], hData[hid][hExtposY], hData[hid][hExtposZ]))
		{
			if(hData[hid][hPrice] > GetPlayerMoney(playerid)) return Error(playerid, "Not enough money, you can't afford this houses.");
			if(strcmp(hData[hid][hOwner], "-")) return Error(playerid, "Someone already owns this house.");
			if(PropertiResidential_CountMax(playerid) >= PropertiesResidential_Max(playerid)) return Error(playerid, "You can no longer buy a house, your property slots are full");
			SendClientMessageEx(playerid, COLOR_ARWIN, "HOUSE: {FFFFFF}You've succesfuly bought this house, use {FFFF00}'/help'{FFFFFF} to show more command");
			GivePlayerMoneyEx(playerid, -hData[hid][hPrice]);
			Server_AddMoney(hData[hid][hPrice]);
			GetPlayerName(playerid, hData[hid][hOwner], MAX_PLAYER_NAME);
			hData[hid][hLastVisited] = gettime();
			
			House_Refresh(hid);
			House_Save(hid);
		}
	}
	return 1;
}

CMD:accent(playerid, params[])
{
	if(pData[playerid][pLevel] < 4) 
		return Error(playerid, "Untuk menggunakan command ini anda harus level 4 ke atas");

	new length = strlen(params), idx, String[256];
	while ((idx < length) && (params[idx] <= ' '))
	{
		idx++;
	}
	new offset = idx;
	new result[16];
	while ((idx < length) && ((idx - offset) < (sizeof(result) - 1)))
	{
		result[idx - offset] = params[idx];
		idx++;
	}
	result[idx - offset] = EOS;
	if(!strlen(result))
	{
		Usage(playerid, "/accent [name]");
		return 1;
	}
	format(pData[playerid][pAccent], 80, "%s", result);
	format(String, sizeof(String), "ACCENT: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", pData[playerid][pAccent]);
	SendClientMessageEx(playerid,COLOR_ARWIN,String);
	SendClientMessageEx(playerid,COLOR_ARWIN,"NOTE: Jika ingin menghapus accent gunakan command "YELLOW_E"'/offaccent'");
	return 1;
}

CMD:offaccent(playerid, params[])
{
	if(pData[playerid][pLevel] ==  1) 
		return Error(playerid, "Untuk menggunakan command ini anda harus level 5 ke atas");
	if(pData[playerid][pLevel] ==  2) 
		return Error(playerid, "Untuk menggunakan command ini anda harus level 5 ke atas");
	if(pData[playerid][pLevel] ==  3) 
		return Error(playerid, "Untuk menggunakan command ini anda harus level 5 ke atas");
	if(pData[playerid][pLevel] ==  4) 
		return Error(playerid, "Untuk menggunakan command ini anda harus level 5 ke atas");
	if(pData[playerid][pTogAccent] == 1)
	{
		SendClientMessageEx(playerid, COLOR_ARWIN, "ACCENT: "WHITE_E"Accent OFF!");
		pData[playerid][pTogAccent] = 0;
	}	
	return 1;
}

CMD:cerai(playerid, params[])
{
	if(pData[playerid][pMarried] < 0)
	{
		SendClientMessageEx(playerid, COLOR_GREY, "You are already Married!");
		return 1;
	}

	new String[500], giveplayerid;
	if(sscanf(params, "u", giveplayerid)) return SendClientMessageEx(playerid, COLOR_WHITE, "KEGUNAAN: /cerai [playerid]");

	if(IsPlayerConnected(giveplayerid))
	{
		if(pData[giveplayerid][pMarried] < 0)
		{
			SendClientMessageEx(playerid, COLOR_GREY, "That player is already married!");
			return 1;
		}
		if (ProxDetectorS(8.0, playerid, giveplayerid))
		{
			if(giveplayerid == playerid) { SendClientMessageEx(playerid, COLOR_GREY, "You cannot Propose to yourself!"); return 1; }
			format(String, sizeof(String), "* Kamu mengajak cerai/pisah %s.", ReturnName(giveplayerid));
			SendClientMessageEx(playerid, COLOR_LIGHTBLUE, String);
			format(String, sizeof(String), "* %s Mengajak cerai/pisah kamu (type /accept cerai) to accept.", ReturnName(playerid));
			SendClientMessageEx(giveplayerid, COLOR_LIGHTBLUE, String);
			pData[giveplayerid][pMarriedCancel] = playerid;
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_GREY, "That player isn't near you.");
			return 1;
		}

	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Invalid player specified.");
		return 1;
	}
	return 1;
}

CMD:cc(playerid, params[])
{
	return callcmd::clear(playerid, "");
}

CMD:clear(playerid, params[])
{
	for(new i=0; i<100; i++)
	{
	    SendClientMessageEx(playerid, COLOR_WHITE, "");
	}
	return 1;
}

CMD:radio(playerid, params[])
{
	if(pData[playerid][pVip] < 2)
		return PermissionError(playerid);

	if(isnull(params))
		return Usage(playerid, "/radio [off/set]");

	if(strcmp(params, "off", true) == 0)
	{
		if(GetPVarType(playerid, "BBArea"))
		{
			SendClientMessageEx(playerid, COLOR_ARWIN, "RADIO: "WHITE_E"You've turned off the radio");
			foreach(new i : Player)
			{
				if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "BBArea")))
				{
					StopStream(i);
				}
			}
			DeletePVar(playerid, "BBStation");
			PickUpBoombox(playerid);
		}
		return 1;
	}

	if(strcmp(params, "set", true) == 0)
	{
		ShowPlayerDialog(playerid, DIALOG_URL_BOOMBOX, DIALOG_STYLE_INPUT, "Radio URL", "Enter music url to play music", "Play", "Cancel");
		return 1;
	}

	return Usage(playerid, "/radio [off/set]");
}

CMD:jobduty(playerid, params[])
{
	if(IsPlayerConnected(playerid)) 
	{
        if(isnull(params)) 
		{
            Usage(playerid, "USAGE: /jobduty [name]");
            Info(playerid, "Names: mechanic, taxi");
            return 1;
		}
		if(strcmp(params,"mechanic",true) == 0) 
		{
			new wsid = GetPlayerNearbyWorkshop(playerid);
			if(IsPlayerAtMechanicPoint(playerid) || IsPlayerWorkshopWorker(playerid, wsid))
			{
				if(pData[playerid][pJob] == 2 || pData[playerid][pJob2] == 2)
				{
					if(pData[playerid][pMechDuty] == 0)
					{
						pData[playerid][pMechDuty] = 1;
						SetPlayerColor(playerid, COLOR_GREEN);
						if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
				        	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_GREEN, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
						SendClientMessageEx(playerid, COLOR_ARWIN, "JOB: "YELLOW_E"You are now on duty mechanic!");
					}
					else
					{
						pData[playerid][pMechDuty] = 0;
						SetPlayerColor(playerid, COLOR_WHITE);
						if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
				       		UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s {ffffff}(%d)", ReturnName2(playerid), playerid)));
						SendClientMessageEx(playerid, COLOR_ARWIN, "JOB: "RED_E"You are now off duty mechanic!");
					}
				}
				else return Error(playerid, "You are not a mechanic worker!");
			}
			else if(wsid != -1) return Error(playerid, "You are not an employee of this workshop!");
			else return Error(playerid, "You have to be in mechanic city, mechanic desert, or workshop");
        }
		if(strcmp(params,"taxi",true) == 0) 
		{
			if(pData[playerid][pJob] == 1 || pData[playerid][pJob2] == 1)
			{
				new modelid = GetVehicleModel(GetPlayerVehicleID(playerid));
				
				if(modelid != 438 && modelid != 420)
					return Error(playerid, "Anda harus berada di dalam taksi.");
					
				if(pData[playerid][pTaxiDuty] == 0)
				{
					pData[playerid][pTaxiDuty] = 1;
					SetPlayerColor(playerid, COLOR_YELLOW);
					if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
			        	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_YELLOW, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
					SendClientMessageEx(playerid, COLOR_ARWIN, "JOB: "YELLOW_E"You are now on duty taxi!");
				}
				else
				{
					pData[playerid][pTaxiDuty] = 0;
					SetPlayerColor(playerid, COLOR_WHITE);
					if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
			        	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s {ffffff}(%d)", ReturnName2(playerid), playerid)));
					SendClientMessageEx(playerid, COLOR_ARWIN, "JOB: "RED_E"You are now off duty taxi!");
				}
			}
			else return Error(playerid, "Anda bukan pekerja taxi driver.");
        }
	}	
	return 1;
}

CMD:buybait(playerid,params[])
{
    new String[212];
	if(!IsPlayerInRangeOfPoint(playerid,3,361.2099,-2032.1703,7.8359))
	{
	    Error(playerid, "Kamu harus di Toko Umpan untuk membeli umpan");
	    return 1;
	}
	if(pData[playerid][pWorm] > 150) return SendClientMessageEx(playerid,COLOR_RED,"Anda tidak dapat membawa umpan lagi.");
	format(String, sizeof(String), "Bait Price: $0.5");
	Dialog_Show(playerid, BuyBait, DIALOG_STYLE_INPUT, "Buy Bait",String, "Buy", "Cancel" );
	return 1;
}

CMD:flashlight(playerid, params[])
{
	if(pData[playerid][pUsedFlashlight] == 0)
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid,8)) RemovePlayerAttachedObject(playerid,8);
		if(IsPlayerAttachedObjectSlotUsed(playerid,9)) RemovePlayerAttachedObject(playerid,9);
		SetPlayerAttachedObject(playerid, 8, 18656, 5, 0.1, 0.038, -0.01, -90, 180, 0, 0.03, 0.1, 0.03);
		SetPlayerAttachedObject(playerid, 9, 18641, 5, 0.1, 0.02, -0.05, 0, 0, 0, 1, 1, 1);
		SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "** %s takes out a flashlight and turns it on.", ReturnName(playerid));

		pData[playerid][pUsedFlashlight] =1;
	}
	else
	{
 		RemovePlayerAttachedObject(playerid,8);
		RemovePlayerAttachedObject(playerid,9);
  		pData[playerid][pUsedFlashlight] =0;
  		SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "** %s puts their flashlight back in their pocket.", ReturnName(playerid));
	}
	return 1;
}

CMD:eject(playerid, params[])
{
	new targetid;

	if(sscanf(params, "u", targetid))
	{
	    return Usage(playerid, "/eject [playerid]");
	}
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
	    return Error(playerid, "You are not driving any vehicle.");
	}
	if(!IsPlayerConnected(targetid) || !IsPlayerInVehicle(targetid, GetPlayerVehicleID(playerid)))
	{
	    return Error(playerid, "The player specified is disconnected, or is not in your vehicle.");
	}

	RemovePlayerFromVehicle(targetid);
	SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "**{C2A2DA} %s ejects %s from the vehicle.", ReturnName2(playerid), ReturnName2(targetid));
	return 1;
}

CMD:stuck(playerid, params[])
{
    if((gettime() - pData[playerid][pStuck]) < 60) return Error(playerid, "Tunggu 1 menit untuk mengulangi pelaporan.");
    Dialog_Show(playerid, Stuck, DIALOG_STYLE_LIST, "Stuck", "Wrong virtual world id.\nWrong interior id.\nStuck inside house/business/etc\nStuck at blueberry\nDeath without reason\nFreeze without reason\nStuck on vehicle", "Report", "Close");
    return 1;
}

Dialog:Stuck(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        switch(listitem)
        {
            case 0: SendAdminMessage(TOMATO, "STUCK: [%d] %s ( %.19s )  current vw: [ %d ] | location: [%s] | jailed: [%s].", playerid, ReturnName2(playerid), inputtext, GetPlayerVirtualWorld(playerid), GetLocation(x, y, z), (!pData[playerid][pJailTime]) ? ("No") : ("Yes")), SetPVarInt(playerid, "stuckHelp", 1);
            case 1: SendAdminMessage(TOMATO, "STUCK: [%d] %s ( %.14s )  current interior: [ %d ] | location: [%s] | jailed: [%s].", playerid, ReturnName2(playerid), inputtext, GetPlayerInterior(playerid), GetLocation(x, y, z), (!pData[playerid][pJailTime]) ? ("No") : ("Yes")), SetPVarInt(playerid, "stuckHelp", 2);
            case 2: SendAdminMessage(TOMATO, "STUCK: [%d] %s ( %s )  current vw/int: [ %d/%d ] | location: [%s] | jailed: [%s].", playerid, ReturnName2(playerid), inputtext, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), GetLocation(x,y,z), (!pData[playerid][pJailTime]) ? ("No") : ("Yes")), SetPVarInt(playerid, "stuckHelp", 3);
            case 3: SendAdminMessage(TOMATO, "STUCK: [%d] %s ( %s )  curr vw/int: [ %d/%d ] | loc / curr position: [%s, %.1f|%.1f|%.1f] | jailed: [%s].", playerid, ReturnName2(playerid), inputtext, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), GetLocation(x, y, z), x, y, z, (!pData[playerid][pJailTime]) ? ("No") : ("Yes")), SetPVarInt(playerid, "stuckHelp", 4);
            case 4: SendAdminMessage(TOMATO, "STUCK: [%d] %s ( %.5s )  curr vw/int: [ %d/%d ] | location: [%s] | injured: [%s] | jailed: [%s].", playerid, ReturnName2(playerid), inputtext, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), GetLocation(x, y, z), (!pData[playerid][pInjured]) ? ("No") : ("Yes"), (!pData[playerid][pJailTime]) ? ("No") : ("Yes")), SetPVarInt(playerid, "stuckHelp", 5);
            case 5:
            {
            	if(pData[playerid][pCuffed])
 					return Error(playerid, "The player is already cuffed at the moment.");

				SendAdminMessage(TOMATO, "STUCK: [%d] %s ( %.6s )  curr vw/int: [ %d/%d ] | freeze: [%s] | jailed: [%s].", playerid, ReturnName2(playerid), inputtext, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), (!pData[playerid][pFreeze]) ? ("No") : ("Yes"), (!pData[playerid][pJailTime]) ? ("No") : ("Yes")), SetPVarInt(playerid, "stuckHelp", 6);
        	}
            case 6:
            {
            	new Float:POS[3];
            	GetPlayerPos(playerid, POS[0], POS[1], POS[2]);
				SetPlayerPos(playerid, POS[0], POS[1], POS[2] + 3);
				SendClientMessage(playerid, COLOR_ARWIN, "STUCK: "WHITE_E"You have successfully used stuck on vehicle");
        	}
        }
        pData[playerid][pStuck] = gettime();
    }
    return 1;
}

CMD:acceptstuck(playerid, params[])
{
    if (pData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    static userid;
    if(sscanf(params, "u", userid)) return Usage(playerid, "/acceptstuck [playerid/PartOfName]");
    if (userid == INVALID_PLAYER_ID || !pData[playerid][pSpawned]) return Error(playerid, "Invalid playerid or name!");
    if((gettime() - pData[userid][pStuck]) > 60) return Error(playerid, "This player is'nt request anything.");
    pData[userid][pStuck] = (gettime()-60);

    switch (GetPVarInt(userid, "stuckHelp")) {
        case 1: {
            SetPlayerVirtualWorld(userid, 0);
        }
        case 2: {
            SetPlayerInterior(userid, 0);
        }
        case 3: {
            SetPlayerPos(userid, 1482.0356,-1724.5726,13.5469);
            SetPlayerVirtualWorld(userid, 0);
            SetPlayerInterior(userid, 0);
        }
        case 4: {
            SetPlayerPos(userid, 1482.0356,-1724.5726,13.5469);
            SetPlayerVirtualWorld(userid, 0);
            SetPlayerInterior(userid, 0);
        }
        case 5: {
			SetPlayerHealth(userid, pData[playerid][pHealth]);
			pData[userid][pInjured] = 0;
			pData[userid][pHospital] = 0;
			pData[userid][pSick] = 0;
			TextDrawHideForPlayer(playerid, injuredtextdraw);
			ClearAnimations(userid);
			TogglePlayerControllable(userid, 1);
            SetPlayerArmedWeapon(userid, 0);
        }
        case 6: {
            TogglePlayerControllable(userid, 1);
        }
    }

    SendCustomMessage(userid, "STUCK REQUEST","Administrator/Helper "RED_E"%s "WHITE_E"accept your stuck request.", pData[playerid][pAdminname]);
    SendAdminMessage(TOMATO, "STUCK REQUEST: %s accept %s stuck request.", pData[playerid][pAdminname], ReturnName2(userid));
    return 1;
}

CMD:cleardelay(playerid, params[])
{
	if(pData[playerid][pAdmin] > 5)
	{
 		DelayPlayer[playerid][DelayDelivery] = 0;
	    DelayPlayer[playerid][DelayFishing] = 0;
		DelayPlayer[playerid][DelayForklift] = 0;
		DelayPlayer[playerid][DelayTrashmaster] = 0;
		DelayPlayer[playerid][DelayHauling] = 0;
		DelayPlayer[playerid][DelayBusDriver] = 0;
		DelayPlayer[playerid][DelaySweeper] = 0;
		DelayPlayer[playerid][DelayWeaponCreate] = 0;
		DelayPlayer[playerid][DelayForager] = 0;
		DelayPlayer[playerid][DelayCourier] = 0;
		Info(playerid, "Succes Clear Delays time Jobs and Activity");
	}
	return 1;
}

CMD:propose(playerid, params[])
{
	if(GetPlayerMoney(playerid) < 100000)
	{
		SendClientMessageEx(playerid, COLOR_GREY, "The Marriage & Reception costs $1,000.00!");
		return 1;
	}
	if(pData[playerid][pMarried] > 0)
	{
		SendClientMessageEx(playerid, COLOR_GREY, "You are already Married!");
		return 1;
	}

	new String[512], giveplayerid;
	if(sscanf(params, "u", giveplayerid)) return SendClientMessageEx(playerid, COLOR_WHITE, "KEGUNAAN: /propose [playerid]");

	if(IsPlayerConnected(giveplayerid))
	{
		if(pData[giveplayerid][pMarried] > 0)
		{
			SendClientMessageEx(playerid, COLOR_GREY, "That player is already married!");
			return 1;
		}
		if (ProxDetectorS(8.0, playerid, giveplayerid))
		{
			if(giveplayerid == playerid) { SendClientMessageEx(playerid, COLOR_GREY, "You cannot Propose to yourself!"); return 1; }
			format(String, sizeof(String), "* You proposed to %s.", ReturnName2(giveplayerid));
			SendClientMessageEx(playerid, COLOR_LIGHTBLUE, String);
			format(String, sizeof(String), "* %s just proposed to you (type /accept marriage) to accept.", ReturnName2(playerid));
			SendClientMessageEx(giveplayerid, COLOR_LIGHTBLUE, String);
			pData[giveplayerid][pMarriedAccept] = playerid;
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_GREY, "That player isn't near you.");
			return 1;
		}

	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Invalid player specified.");
		return 1;
	}
	return 1;
}

CMD:buyboat(playerid) //453 Reefer 452 Speeder 473 Dinghy 484 Marquis 493 Jetmax  446 Squalo 454 Tropic
{
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 10 && IsPlayerInRangeOfPoint(playerid, 2.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
			new String[512];
			format(String, sizeof(String), "Model\tCost\n");
			format(String, sizeof(String),"%s%s\t$%s\n", String, GetVehicleModelName(453), FormatMoney(GetVehicleCost(453)));
			format(String, sizeof(String),"%s%s\t$%s\n", String, GetVehicleModelName(452), FormatMoney(GetVehicleCost(452)));
			format(String, sizeof(String),"%s%s\t$%s\n", String, GetVehicleModelName(473), FormatMoney(GetVehicleCost(473)));
			format(String, sizeof(String),"%s%s\t$%s\n", String, GetVehicleModelName(484), FormatMoney(GetVehicleCost(484)));
			format(String, sizeof(String),"%s%s\t$%s\n", String, GetVehicleModelName(493), FormatMoney(GetVehicleCost(493)));
			format(String, sizeof(String),"%s%s\t$%s\n", String, GetVehicleModelName(446), FormatMoney(GetVehicleCost(446)));
			ShowPlayerDialog(playerid, DIALOG_BUYPVCP_BOAT, DIALOG_STYLE_TABLIST_HEADERS, "Boat List", String, "Buy", "Cancel");
		}
	}
	return 1;
}

CMD:buyvehicle(playerid, params[])
{
	if(IsPlayerInRangeOfPoint(playerid,3,563.3856,-1292.2179,17.2482))
	{
	    if(pData[playerid][pVip] > 0)
		{
			new String[512], S3MP4K[512];
			strcat(S3MP4K, "Model\tCost\n");
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(522), FormatMoney(GetVehicleCostVIP(522)));
			strcat(S3MP4K, String);
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(411), FormatMoney(GetVehicleCostVIP(411)));
			strcat(S3MP4K, String);
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(451), FormatMoney(GetVehicleCostVIP(451)));
			strcat(S3MP4K, String);
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(494), FormatMoney(GetVehicleCostVIP(494)));
			strcat(S3MP4K, String);
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(541), FormatMoney(GetVehicleCostVIP(541)));
			strcat(S3MP4K, String);
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(573), FormatMoney(GetVehicleCostVIP(573)));
			strcat(S3MP4K, String);
			ShowPlayerDialog(playerid, DIALOG_BUYVEHVIP_CONFIRM, DIALOG_STYLE_TABLIST_HEADERS, "Buying Vehicle", S3MP4K, "Buy", "Cancel");
		}
		else return Error(playerid, "To access a VIP dealership you must be a donators");
	}
	else if(IsPlayerInRangeOfPoint(playerid,3,2131.7900,-1151.1900,24.0600))
	{
		new String[512], S3MP4K[512];
		strcat(S3MP4K, "Model\tCost\n");
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(496), FormatMoney(GetVehicleCost(496)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(470), FormatMoney(GetVehicleCost(470)));
		strcat(S3MP4K, String);
		// format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(505), FormatMoney(GetVehicleCost(505)));
		// strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(489), FormatMoney(GetVehicleCost(489)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(495), FormatMoney(GetVehicleCost(495)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(500), FormatMoney(GetVehicleCost(500)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(400), FormatMoney(GetVehicleCost(400)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(579), FormatMoney(GetVehicleCost(579)));
		strcat(S3MP4K, String);
		ShowPlayerDialog(playerid, DIALOG_BUYVEHSUV_CONFIRM, DIALOG_STYLE_TABLIST_HEADERS, "Buying Vehicle: SUV", S3MP4K, "Buy", "Cancel");
	}
	else if(IsPlayerInRangeOfPoint(playerid,3,2357.6700,-1990.5500,13.5400))
	{
		new String[512], S3MP4K[512];
		strcat(S3MP4K, "Model\tCost\n");
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(445), FormatMoney(GetVehicleCost(445)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(550), FormatMoney(GetVehicleCost(550)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(540), FormatMoney(GetVehicleCost(540)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(560), FormatMoney(GetVehicleCost(560)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(491), FormatMoney(GetVehicleCost(491)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(507), FormatMoney(GetVehicleCost(507)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(492), FormatMoney(GetVehicleCost(492)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(516), FormatMoney(GetVehicleCost(516)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(405), FormatMoney(GetVehicleCost(405)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(410), FormatMoney(GetVehicleCost(410)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(426), FormatMoney(GetVehicleCost(426)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(474), FormatMoney(GetVehicleCost(474)));
		strcat(S3MP4K, String);
		ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM, DIALOG_STYLE_TABLIST_HEADERS, "Buying Vehicle: Saloons", S3MP4K, "Buy", "Cancel");
	}
	else if(IsPlayerInRangeOfPoint(playerid,3,2281.3900, -2364.770, 13.5500))
	{
		new String[512], S3MP4K[512];
		strcat(S3MP4K, "Model\tCost\n");
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(602), FormatMoney(GetVehicleCost(602)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(506), FormatMoney(GetVehicleCost(506)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(402), FormatMoney(GetVehicleCost(402)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(415), FormatMoney(GetVehicleCost(415)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(480), FormatMoney(GetVehicleCost(480)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(562), FormatMoney(GetVehicleCost(562)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(558), FormatMoney(GetVehicleCost(558)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(475), FormatMoney(GetVehicleCost(475)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(559), FormatMoney(GetVehicleCost(559)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(565), FormatMoney(GetVehicleCost(565)));
		strcat(S3MP4K, String);
		ShowPlayerDialog(playerid, DIALOG_BUYVEHSPORTS_CONFIRM, DIALOG_STYLE_TABLIST_HEADERS, "Buying Vehicle: Sports", S3MP4K, "Buy", "Cancel");
	}
	else if(IsPlayerInRangeOfPoint(playerid,3,-265.70, -2213.12, 29.04))
	{
		new String[512], S3MP4K[512];
		strcat(S3MP4K, "Model\tCost\n");
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(554), FormatMoney(GetVehicleCost(554)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(543), FormatMoney(GetVehicleCost(543)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(422), FormatMoney(GetVehicleCost(422)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(478), FormatMoney(GetVehicleCost(478)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(455), FormatMoney(GetVehicleCost(455)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(456), FormatMoney(GetVehicleCost(456)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(499), FormatMoney(GetVehicleCost(499)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(475), FormatMoney(GetVehicleCost(475)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(559), FormatMoney(GetVehicleCost(559)));
		strcat(S3MP4K, String);
		format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(565), FormatMoney(GetVehicleCost(565)));
		strcat(S3MP4K, String);
		ShowPlayerDialog(playerid, DIALOG_BUYVEHJOB_CONFIRM, DIALOG_STYLE_TABLIST_HEADERS, "Buying Vehicle: Jobs", S3MP4K, "Buy", "Cancel");
	}
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 8 && IsPlayerInRangeOfPoint(playerid, 2.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
			new String[512], S3MP4K[512];
			strcat(S3MP4K, "Model\tCost\n");
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(481), FormatMoney(GetVehicleCost(481)));
			strcat(S3MP4K, String);
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(509), FormatMoney(GetVehicleCost(509)));
			strcat(S3MP4K, String);
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(510), FormatMoney(GetVehicleCost(510)));
			strcat(S3MP4K, String);
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(581), FormatMoney(GetVehicleCost(581)));
			strcat(S3MP4K, String);
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(462), FormatMoney(GetVehicleCost(462)));
			strcat(S3MP4K, String);
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(521), FormatMoney(GetVehicleCost(521)));
			strcat(S3MP4K, String);
			format(String, sizeof(String),"%s\t$%s\n", GetVehicleModelName(463), FormatMoney(GetVehicleCost(463)));
			strcat(S3MP4K, String);
			ShowPlayerDialog(playerid, DIALOG_BUYBIKE_CONFIRM, DIALOG_STYLE_TABLIST_HEADERS, "Buying Bicycle", S3MP4K, "Buy", "Cancel");
		}
	}
	return 1;
}

CMD:livestream(playerid, params[])
{
    foreach(new i : Player)
    {
        new count = 0;
        if(pData[i][pLiveText])
        {
            count++;
        }
        if(count)
        {
        new string[256];
	    format(string, sizeof(string), "{C6E2FF}[ID:%d] {FFFFFF}%s : {FFFF00}%s", i, ReturnName(i), pData[i][pLiveText]);
        SendClientMessage(playerid, -1, string);
        }
    }
    return 1;
}

CMD:livemode(playerid, params[])
{
    new liveteks[256];

    if(sscanf(params, "s[256]", liveteks))
        return SendClientMessage(playerid, -1, "{C6E2FF}LIVE:{FFFFFF} /livemode [live text]"), SendClientMessage(playerid, -1, "INFO: Your live text will visible at {FFFF00}'/livestream'{FFFFFF} command");

    if(strfind(liveteks, "", true) != -1)
        return Error(playerid, "Please enter the valid live text!");

    format(pData[playerid][pLiveText], 256, liveteks);
    pData[playerid][pRadioStream] = 1;
    pData[playerid][pStreamMode] = 0;
    new string[256];
    format(string, sizeof(string), "INFO:{FFFFFF} You has set your live text to "YELLOW_E"%s", liveteks);
    SendClientMessage(playerid, COLOR_ARWIN, string);
	SendClientMessage(playerid, COLOR_ARWIN, "INFO: "WHITE_E"Livestream mode "LG_E"enabled");
	SendClientMessage(playerid, COLOR_ARWIN, "RADIO: "WHITE_E"Radio streaming "RED_E"disabled");
    return 1;
}

CMD:quiz(playerid, params[])
{
    new choice[10], subparam[128];
    if(sscanf(params, "s[10]S()[128]", choice, subparam)) 
        return Usage(playerid, "/quiz [create/answer/end]");

    if(!strcmp(choice, "create"))
    {
        if (pData[playerid][pAdmin] < 2)
            return PermissionError(playerid);

        new quest[128], answer[128];
        if(GetGVarInt("QuizReady", GLOBAL_VARTYPE_INT))
            return Error(playerid, "You can't create more than 1 quiz.");

        if(sscanf(subparam, "p<:>s[128]s[128]", quest,answer))
            return Usage(playerid, "/quiz create [questions] : [answer]");
                 
        SetGVarInt("QuizReady", 1, GLOBAL_VARTYPE_INT);
        SetGVarString("QuizQuest", quest, GLOBAL_VARTYPE_STRING);
        SetGVarString("QuizAnswer", answer, GLOBAL_VARTYPE_STRING);

		SendQuizVoteMessage(COLOR_ARWIN, "QUIZ: "YELLOW_E"%s", quest);
		SendQuizVoteMessage(COLOR_YELLOW, "NOTE: "YELLOW_E"Use '"RED_E"/quiz answer"YELLOW_E"' to answer that quiz!.");
		SendAdminMessage(TOMATO, "Quiz added by %s", pData[playerid][pAdminname]);
    }
    else if(!strcmp(choice, "answer"))
    {
        new answer[128],answered[128];

        GetGVarString("QuizAnswer", answer, sizeof(answer), GLOBAL_VARTYPE_STRING);

        if(sscanf(subparam,"s[128]", answered))
        return Usage(playerid, "/quiz answer [answer]");

        if(!GetGVarInt("QuizReady", GLOBAL_VARTYPE_INT))
        return Error(playerid, "There is no available quiz.");

        if(!strcmp(answered, answer, true))
        {
		    SendQuizVoteMessage(COLOR_ARWIN, "QUIZ: "AQUA_E"%s "YELLOW_E" guessed the correct answer!",ReturnName2(playerid));
		    SendQuizVoteMessage(COLOR_ARWIN, "ANSWER: "YELLOW_E"%s",answer);

            SetGVarInt("QuizReady", 0, GLOBAL_VARTYPE_INT);
            SetGVarString("QuizQuest", "(null)", GLOBAL_VARTYPE_STRING);
            SetGVarString("QuizAnswer", "(null)", GLOBAL_VARTYPE_STRING);
        }
        else
            Error(playerid, "Wrong answer.");
    }
    else if(!strcmp(choice, "end"))
    {
        new quest[128],answer[128];

        GetGVarString("QuizQuest", quest, sizeof(quest), GLOBAL_VARTYPE_STRING);
        GetGVarString("QuizAnswer", answer, sizeof(answer), GLOBAL_VARTYPE_STRING);

        if (pData[playerid][pAdmin] < 2)
            return PermissionError(playerid);
            
        if(!GetGVarInt("QuizReady", GLOBAL_VARTYPE_INT))
        return Error(playerid, "There is no available quiz.");

		SendQuizVoteMessage(COLOR_YELLOW, "QUIZINFO"WHITE_E": Admin "YELLOW_E"%s"WHITE_E" ended the quiz. The correct answer was '"YELLOW_E"%s"WHITE_E"", ReturnName2(playerid), answer);

        SendClientMessageToAllEx(COLOR_YELLOW, "QUIZINFO"WHITE_E": Admin "YELLOW_E"%s"WHITE_E" ended the quiz. The correct answer was '"YELLOW_E"%s"WHITE_E"", ReturnName2(playerid), answer);
        SetGVarInt("QuizReady", 0, GLOBAL_VARTYPE_INT);
        SetGVarString("QuizQuest", "(null)", GLOBAL_VARTYPE_STRING);
        SetGVarString("QuizAnswer", "(null)", GLOBAL_VARTYPE_STRING);
    }
    else return SendClientMessage(playerid, 0xAFAFAFAA, "USAGE: /quiz [create/answer/end]");
    return 1;
}

function VoteTime()
{
    new pertanyaan[128], unknown, count = Iter_Count(Player);
    unknown = count-(GetGVarInt("Yes")+GetGVarInt("No"));

    GetGVarString("VoteQuest", pertanyaan, 128);

	SendQuizVoteMessage(COLOR_ARWIN, "VOTE: "YELLOW_E"%s", pertanyaan);
    SendQuizVoteMessage(COLOR_ARWIN, "VOTE: "GREEN_E"(%d) Yes"WHITE_E", "RED_E"(%d) No, "WHITE_E"(%d) "ARWIN_E"Unknown", GetGVarInt("Yes"), GetGVarInt("No"), (unknown < 0) ? (unknown*-1) : unknown);

    foreach(new i : Player) {
        SetPVarInt(i, "Vote", 0);
    }
    SetGVarInt("Yes", 0);
    SetGVarInt("No", 0);
    SetGVarInt("Vote", 0);
    return 1;
}

CMD:vote(playerid, params[])
{
    new vote[10], string[64];

    if (pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);

    if(sscanf(params, "s[10]S()[64]", vote, string))
        return Usage(playerid, "/vote [create/end]");

    if(!strcmp(vote, "create", true))
    {
        new pertanyaan[128];
    
        if(sscanf(string,"s[128]", pertanyaan))
            return Usage(playerid, "/vote create [vote]");

		SendQuizVoteMessage(COLOR_ARWIN, "VOTE: "YELLOW_E"%s", pertanyaan);
        SendQuizVoteMessage(COLOR_ARWIN, "VOTE: "GREEN_E"/yes "WHITE_E"to accept, "RED_E"/no"WHITE_E" to deny");

        SetGVarString("VoteQuest", pertanyaan);
        SetGVarInt("Yes", 0);
        SetGVarInt("No", 0);
        SetGVarInt("Vote", 1);
    
        TimerVote = SetTimer("VoteTime", 45000, false);
        foreach(new i : Player) {
            SetPVarInt(i, "Vote", 0);
        }
    }
    if(!strcmp(vote, "end", true))
    {
        if(!GetGVarInt("Vote"))
        return Error(playerid, "Tidak ada vote yang sedang berlangsung.");

        SendQuizVoteMessage(TOMATO, "AdmCmd: %s ended this voting.",ReturnName2(playerid));        SetGVarString("VoteQuest", "(null)");

        SetGVarInt("Vote", 0);
        SetGVarInt("Yes", 0);
        SetGVarInt("No", 0);

        foreach(new i : Player) {
            SetPVarInt(i, "Vote", 0);
        }
        KillTimer(TimerVote);
    }
    return 1;
}

CMD:no(playerid, params[])
{
    if(!GetGVarInt("Vote"))
        return Error(playerid, "Tidak ada vote yang sedang berlangsung.");

    if(GetPVarInt(playerid, "Vote"))
        return Error(playerid, "Anda sudah memvoting sebelumnya.");

    SetGVarInt("No", GetGVarInt("No")+1);
    SetPVarInt(playerid, "Vote", 1);
    Servers(playerid, "You're vote "RED_E"No");
    return 1;
}

CMD:yes(playerid, params[])
{
    if(!GetGVarInt("Vote"))
        return Error(playerid, "Tidak ada vote yang sedang berlangsung.");

    if(GetPVarInt(playerid, "Vote"))
        return Error(playerid, "Anda sudah memvoting sebelumnya.");

    SetGVarInt("Yes", GetGVarInt("Yes")+1);
    SetPVarInt(playerid, "Vote", 1);
    Servers(playerid, "You're vote "GREEN_E"Yes");
    return 1;
}

CMD:switchveh(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return Error(playerid, "Anda harus mengendarai kendaraan");
	new vehicleid = GetPlayerVehicleID(playerid);
	foreach(new hid : Houses) {
		if(IsPlayerInRangeOfPoint(playerid, 2.5, hData[hid][hGarageposX], hData[hid][hGarageposY], hData[hid][hGarageposZ])) {
			if (Player_OwnsHouse(playerid, hid)) {
				foreach(new vehicle : PVehicles) if(pvData[vehicle][cOwner] == pData[playerid][pID]) {
					if(pvData[vehicle][cVeh] == vehicleid) {
						GetVehicleDamageStatus(pvData[vehicle][cVeh], pvData[vehicle][cDamage0], pvData[vehicle][cDamage1], pvData[vehicle][cDamage2], pvData[vehicle][cDamage3]);
						GetVehicleHealth(pvData[vehicle][cVeh], pvData[vehicle][cHealth]);
						pvData[vehicle][cFuel] = GetVehicleFuel(pvData[vehicle][cVeh]);
						GetVehiclePos(pvData[vehicle][cVeh], pvData[vehicle][cPosX], pvData[vehicle][cPosY], pvData[vehicle][cPosZ]);
						GetVehicleZAngle(pvData[vehicle][cVeh],pvData[vehicle][cPosA]);
						Vehicle_ObjectDestroy(vehicle);
						for(new id = 0; id < 5; id++) if(IsValidDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id])) DestroyDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id]);
						DestroyVehicle(pvData[vehicle][cVeh]);
						pvData[vehicle][cVeh] = INVALID_VEHICLE_ID;
						SetTimerEx("VehicleGarage", 1000, false, "dd", vehicle, hid);
					}
					if(pvData[vehicle][cVehicleGarage] == hid) {
						pvData[vehicle][cVehicleGarage] = -1;
						if(!IsValidVehicle(pvData[vehicle][cVeh]))  OnPlayerVehicleRespawn(vehicle); 
						PutPlayerInVehicle(playerid, pvData[vehicle][cVeh], 0);
					}
				}
			}
		}
	}
	for(new biz = 0 ; biz < MAX_BISNIS; biz++) {
		if(IsPlayerInRangeOfPoint(playerid, 2.5, BussinesGarage[biz][ExtPos][0], BussinesGarage[biz][ExtPos][1], BussinesGarage[biz][ExtPos][2])) {
			if (Player_OwnsBisnis(playerid, biz)) {
				foreach(new vehicle : PVehicles) if(pvData[vehicle][cOwner] == pData[playerid][pID]) {
					if(pvData[vehicle][cVeh] == vehicleid) {
						GetVehicleDamageStatus(pvData[vehicle][cVeh], pvData[vehicle][cDamage0], pvData[vehicle][cDamage1], pvData[vehicle][cDamage2], pvData[vehicle][cDamage3]);
						GetVehicleHealth(pvData[vehicle][cVeh], pvData[vehicle][cHealth]);
						pvData[vehicle][cFuel] = GetVehicleFuel(pvData[vehicle][cVeh]);
						GetVehiclePos(pvData[vehicle][cVeh], pvData[vehicle][cPosX], pvData[vehicle][cPosY], pvData[vehicle][cPosZ]);
						GetVehicleZAngle(pvData[vehicle][cVeh],pvData[vehicle][cPosA]);
						Vehicle_ObjectDestroy(vehicle);
						DestroyVehicle(pvData[vehicle][cVeh]);
						for(new id = 0; id < 5; id++) if(IsValidDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id])) DestroyDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id]);
						pvData[vehicle][cVeh] = INVALID_VEHICLE_ID;
						SetTimerEx("VehicleGarage", 1000, false, "dd", vehicle, biz);
					}
					if(pvData[vehicle][cVehicleGarage] == biz) {
						pvData[vehicle][cVehicleGarage] = -1;
						if(!IsValidVehicle(pvData[vehicle][cVeh]))  OnPlayerVehicleRespawn(vehicle); 
						PutPlayerInVehicle(playerid, pvData[vehicle][cVeh], 0);
					}
				}
			}
		}
	}
	foreach(new flat : Flat) {
		if(IsPlayerInRangeOfPoint(playerid, 2.5, FlatData[flat][flatGaragePos][0], FlatData[flat][flatGaragePos][1], FlatData[flat][flatGaragePos][2])) {
			foreach(new flatid : FlatRooms) if(FlatRoom[flatid][flatID] == FlatData[flat][flatID]) {
				if (FlatRoom_IsOwner(playerid,flatid)) {
					foreach(new vehicle : PVehicles) if(pvData[vehicle][cOwner] == pData[playerid][pID]) {
						if(pvData[vehicle][cVeh] == vehicleid) {
							GetVehicleDamageStatus(pvData[vehicle][cVeh], pvData[vehicle][cDamage0], pvData[vehicle][cDamage1], pvData[vehicle][cDamage2], pvData[vehicle][cDamage3]);
							GetVehicleHealth(pvData[vehicle][cVeh], pvData[vehicle][cHealth]);
							pvData[vehicle][cFuel] = GetVehicleFuel(pvData[vehicle][cVeh]);
							GetVehiclePos(pvData[vehicle][cVeh], pvData[vehicle][cPosX], pvData[vehicle][cPosY], pvData[vehicle][cPosZ]);
							GetVehicleZAngle(pvData[vehicle][cVeh],pvData[vehicle][cPosA]);
							Vehicle_ObjectDestroy(vehicle);
							DestroyVehicle(pvData[vehicle][cVeh]);
							for(new id = 0; id < 5; id++) if(IsValidDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id])) DestroyDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id]);
							pvData[vehicle][cVeh] = INVALID_VEHICLE_ID;
							SetTimerEx("VehicleGarage", 1000, false, "dd", vehicle, flatid);
						}
						if(pvData[vehicle][cVehicleGarage] == flatid) {
							pvData[vehicle][cVehicleGarage] = -1;
							if(!IsValidVehicle(pvData[vehicle][cVeh]))  OnPlayerVehicleRespawn(vehicle); 
							PutPlayerInVehicle(playerid, pvData[vehicle][cVeh], 0);
						}
					}
				}
			}
		}
	}
	return 1;
}

function VehicleGarage(vehicle, id) {
	pvData[vehicle][cVehicleGarage] = id;
}

CMD:takeveh(playerid, params[]) {
	foreach(new hid : Houses) {
		if(IsPlayerInRangeOfPoint(playerid, 2.5, hData[hid][hGarageposX], hData[hid][hGarageposY], hData[hid][hGarageposZ])) {
			if (Player_OwnsHouse(playerid, hid)) {
				foreach(new vehicle : PVehicles) if(pvData[vehicle][cOwner] == pData[playerid][pID] && pvData[vehicle][cVehicleGarage] == hid) {
					pvData[vehicle][cVehicleGarage] = -1;
					if(!IsValidVehicle(pvData[vehicle][cVeh]))  OnPlayerVehicleRespawn(vehicle); 
					PutPlayerInVehicle(playerid, pvData[vehicle][cVeh], 0);
					
					SendCustomMessage(playerid, "TAKEVEH", ""AQUA_E"%s {FFFFFF}You have been taken from the garage", GetVehicleName(pvData[vehicle][cVeh]));
				}
			}
		}
	}
	for(new biz = 0 ; biz < MAX_BISNIS; biz++) {
		if(IsPlayerInRangeOfPoint(playerid, 2.5, BussinesGarage[biz][ExtPos][0], BussinesGarage[biz][ExtPos][1], BussinesGarage[biz][ExtPos][2])) {
			if (Player_OwnsBisnis(playerid, biz)) {
				foreach(new vehicle : PVehicles) if(pvData[vehicle][cOwner] == pData[playerid][pID] && pvData[vehicle][cVehicleGarage] == biz) {
					pvData[vehicle][cVehicleGarage] = -1;
					if(!IsValidVehicle(pvData[vehicle][cVeh]))  OnPlayerVehicleRespawn(vehicle); 
					PutPlayerInVehicle(playerid, pvData[vehicle][cVeh], 0);
					
					SendCustomMessage(playerid, "TAKEVEH", ""AQUA_E"%s {FFFFFF}You have been taken from the garage", GetVehicleName(pvData[vehicle][cVeh]));
				}
			}
		}
	}
	foreach(new flat : Flat) {
		if(IsPlayerInRangeOfPoint(playerid, 2.5, FlatData[flat][flatGaragePos][0], FlatData[flat][flatGaragePos][1], FlatData[flat][flatGaragePos][2])) {
			foreach(new flatid : FlatRooms) if(FlatRoom[flatid][flatID] == FlatData[flat][flatID]) {
				if (FlatRoom_IsOwner(playerid,flatid)) {
					foreach(new vehicle : PVehicles) if(pvData[vehicle][cOwner] == pData[playerid][pID] && pvData[vehicle][cVehicleGarage] == flatid) {
						pvData[vehicle][cVehicleGarage] = -1;
						if(!IsValidVehicle(pvData[vehicle][cVeh]))  OnPlayerVehicleRespawn(vehicle); 
						PutPlayerInVehicle(playerid, pvData[vehicle][cVeh], 0);
						
						SendCustomMessage(playerid, "TAKEVEH", ""AQUA_E"%s {FFFFFF}You have been taken from the garage", GetVehicleName(pvData[vehicle][cVeh]));
					}
				}
			}
		}
	}
	foreach(new pvid : PrivateGarage) {
		if(IsPlayerInRangeOfPoint(playerid, 3, PrivateGarage[pvid][GaragePos][0], PrivateGarage[pvid][GaragePos][1], PrivateGarage[pvid][GaragePos][2])) {
			if (OwnerPvGarage(playerid, pvid)) {
				new string[512], str[212], count = 0;
				foreach(new vehicle : PVehicles) if(pvData[vehicle][cOwner] == pData[playerid][pID] && pvData[vehicle][cVehicleGarage] == pvid) {
					gListedItems[playerid][count] = vehicle;
					count++;
					format(string, sizeof(string), "%s[VID: %d] %s\n", string, pvData[vehicle][cID], GetVehicleNameByModel(pvData[vehicle][cModel]));
				}
				format(str, sizeof(str), "Private Garage (%d/5)", count);
				Dialog_Show(playerid, PvGarageDialog, DIALOG_STYLE_LIST, str, string, "Select", "Close");
			}
		}
	}
	return 1;
}

CMD:storeveh(playerid, params[])
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return Error(playerid, "Anda harus mengendarai kendaraan");
	new count = 0;
	foreach(new hid : Houses) {
		if(IsPlayerInRangeOfPoint(playerid, 2.5, hData[hid][hGarageposX], hData[hid][hGarageposY], hData[hid][hGarageposZ])) {
			if (Player_OwnsHouse(playerid, hid) && hData[hid][hGarage] > 0) {
				foreach(new vehicle : PVehicles) if(pvData[vehicle][cOwner] == pData[playerid][pID]) {
					if(pvData[vehicle][cVehicleGarage] == hid) count++;
					if(count) return Error(playerid, "Ada mobil didalam garasi harap keluarkan terlebih dahulu");
					if(pvData[vehicle][cVehicleGarage] != hid && pvData[vehicle][cVeh] == GetPlayerVehicleID(playerid))	{
						pvData[vehicle][cVehicleGarage] = hid;
						pvData[vehicle][cDespawn] = 0;
						GetVehicleDamageStatus(pvData[vehicle][cVeh], pvData[vehicle][cDamage0], pvData[vehicle][cDamage1], pvData[vehicle][cDamage2], pvData[vehicle][cDamage3]);
						GetVehicleHealth(pvData[vehicle][cVeh], pvData[vehicle][cHealth]);
						pvData[vehicle][cFuel] = GetVehicleFuel(pvData[vehicle][cVeh]);
						GetVehiclePos(pvData[vehicle][cVeh], pvData[vehicle][cPosX], pvData[vehicle][cPosY], pvData[vehicle][cPosZ]);
						GetVehicleZAngle(pvData[vehicle][cVeh],pvData[vehicle][cPosA]);
						SendCustomMessage(playerid, "STOREVEH", "Your "AQUA_E"%s {FFFFFF}has been stored. You may release it with {FFFF00}'/takeveh'.", GetVehicleName(pvData[vehicle][cVeh]));
						Vehicle_ObjectDestroy(vehicle);
						for(new id = 0; id < 5; id++) if(IsValidDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id])) DestroyDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id]);
						DestroyVehicle(pvData[vehicle][cVeh]);
						pvData[vehicle][cVeh] = INVALID_VEHICLE_ID;
					}
				}
			}
		}
	}
	for(new biz = 0 ; biz < MAX_BISNIS; biz++) {
		if(IsPlayerInRangeOfPoint(playerid, 2.5, BussinesGarage[biz][ExtPos][0], BussinesGarage[biz][ExtPos][1], BussinesGarage[biz][ExtPos][2])) {
			if (Player_OwnsBisnis(playerid, biz) && BussinesGarage[biz][BizGarage] > 0) {
				foreach(new vehicle : PVehicles) if(pvData[vehicle][cOwner] == pData[playerid][pID]) {
					if(pvData[vehicle][cVehicleGarage] == biz) count++;
					if(count) return Error(playerid, "Ada mobil didalam garasi harap keluarkan terlebih dahulu");
					if(pvData[vehicle][cVehicleGarage] != biz && pvData[vehicle][cVeh] == GetPlayerVehicleID(playerid))	{
						pvData[vehicle][cVehicleGarage] = biz;
						GetVehicleDamageStatus(pvData[vehicle][cVeh], pvData[vehicle][cDamage0], pvData[vehicle][cDamage1], pvData[vehicle][cDamage2], pvData[vehicle][cDamage3]);
						GetVehicleHealth(pvData[vehicle][cVeh], pvData[vehicle][cHealth]);
						pvData[vehicle][cFuel] = GetVehicleFuel(pvData[vehicle][cVeh]);
						GetVehiclePos(pvData[vehicle][cVeh], pvData[vehicle][cPosX], pvData[vehicle][cPosY], pvData[vehicle][cPosZ]);
						GetVehicleZAngle(pvData[vehicle][cVeh],pvData[vehicle][cPosA]);
						SendCustomMessage(playerid, "STOREVEH", "Your "AQUA_E"%s {FFFFFF}has been stored. You may release it with {FFFF00}'/takeveh'.", GetVehicleName(pvData[vehicle][cVeh]));
						Vehicle_ObjectDestroy(vehicle);
						DestroyVehicle(pvData[vehicle][cVeh]);
						for(new id = 0; id < 5; id++) if(IsValidDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id])) DestroyDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id]);
						pvData[vehicle][cVeh] = INVALID_VEHICLE_ID;
					}
				}
			}
		}
	}
	foreach(new flat : Flat) {
		if(IsPlayerInRangeOfPoint(playerid, 2.5, FlatData[flat][flatGaragePos][0], FlatData[flat][flatGaragePos][1], FlatData[flat][flatGaragePos][2])) {
			foreach(new flatid : FlatRooms) if(FlatRoom[flatid][flatID] == FlatData[flat][flatID]) {
				if (FlatRoom_IsOwner(playerid,flatid)) {
					foreach(new vehicle : PVehicles) if(pvData[vehicle][cOwner] == pData[playerid][pID]) {
						if(pvData[vehicle][cVehicleGarage] == flatid) count++;
						if(count) return Error(playerid, "Ada mobil didalam garasi harap keluarkan terlebih dahulu");
						if(pvData[vehicle][cVehicleGarage] != flatid && pvData[vehicle][cVeh] == GetPlayerVehicleID(playerid)) {							
							pvData[vehicle][cVehicleGarage] = flatid;
							GetVehicleDamageStatus(pvData[vehicle][cVeh], pvData[vehicle][cDamage0], pvData[vehicle][cDamage1], pvData[vehicle][cDamage2], pvData[vehicle][cDamage3]);
							GetVehicleHealth(pvData[vehicle][cVeh], pvData[vehicle][cHealth]);
							pvData[vehicle][cFuel] = GetVehicleFuel(pvData[vehicle][cVeh]);
							GetVehiclePos(pvData[vehicle][cVeh], pvData[vehicle][cPosX], pvData[vehicle][cPosY], pvData[vehicle][cPosZ]);
							GetVehicleZAngle(pvData[vehicle][cVeh],pvData[vehicle][cPosA]);
							SendCustomMessage(playerid, "STOREVEH", "Your "AQUA_E"%s {FFFFFF}has been stored. You may release it with {FFFF00}'/takeveh'.", GetVehicleName(pvData[vehicle][cVeh]));
							Vehicle_ObjectDestroy(vehicle);
							DestroyVehicle(pvData[vehicle][cVeh]);
							for(new id = 0; id < 5; id++) if(IsValidDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id])) DestroyDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id]);
							pvData[vehicle][cVeh] = INVALID_VEHICLE_ID;
						}
					}
				}
			}
		}
	}
	foreach(new pvid : PrivateGarage) {
		if(IsPlayerInRangeOfPoint(playerid, 3, PrivateGarage[pvid][GaragePos][0], PrivateGarage[pvid][GaragePos][1], PrivateGarage[pvid][GaragePos][2])) {
			if (OwnerPvGarage(playerid, pvid)) {
				foreach(new vehicle : PVehicles) if(pvData[vehicle][cOwner] == pData[playerid][pID]) {
					if(pvData[vehicle][cVehicleGarage] == pvid) {
						count++;
					}
					if(count > 5) return Error(playerid, "Your vehicle's slot in the garage is full");
					if(pvData[vehicle][cVeh] == GetPlayerVehicleID(playerid)) {
						pvData[vehicle][cVehicleGarage] = pvid;
						GetVehicleDamageStatus(pvData[vehicle][cVeh], pvData[vehicle][cDamage0], pvData[vehicle][cDamage1], pvData[vehicle][cDamage2], pvData[vehicle][cDamage3]);
						GetVehicleHealth(pvData[vehicle][cVeh], pvData[vehicle][cHealth]);
						pvData[vehicle][cFuel] = GetVehicleFuel(pvData[vehicle][cVeh]);
						GetVehiclePos(pvData[vehicle][cVeh], pvData[vehicle][cPosX], pvData[vehicle][cPosY], pvData[vehicle][cPosZ]);
						GetVehicleZAngle(pvData[vehicle][cVeh],pvData[vehicle][cPosA]);
						SendCustomMessage(playerid, "STOREVEH", "Your "AQUA_E"%s {FFFFFF}has been stored. You may release it with {FFFF00}'/takeveh'.", GetVehicleName(pvData[vehicle][cVeh]));
						Vehicle_ObjectDestroy(vehicle);
						DestroyVehicle(pvData[vehicle][cVeh]);
						for(new id = 0; id < 5; id++) if(IsValidDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id])) DestroyDynamicObject(ObjectVehicle[pvData[vehicle][cVeh]][id]);
						pvData[vehicle][cVeh] = INVALID_VEHICLE_ID;
					}
				}
			}
		}
	}
	return 1;
}

Dialog:PvGarageDialog(playerid, response, listitem, inputtext[]) {
    if(response)
    {
		new vehicle = gListedItems[playerid][listitem];
		
		if(response)
		{
			pvData[vehicle][cVehicleGarage] = -1;
			if(!IsValidVehicle(pvData[vehicle][cVeh]))  OnPlayerVehicleRespawn(vehicle); 
			PutPlayerInVehicle(playerid, pvData[vehicle][cVeh], 0);
			SendCustomMessage(playerid, "TAKEVEH", ""AQUA_E"%s {FFFFFF}You have been taken from the garage", GetVehicleName(pvData[vehicle][cVeh]));
		}
	}
	return 1;
}
