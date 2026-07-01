
CMD:createatm(playerid, params[])
{
	if(pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);
		
	new id = Iter_Free(ATMS), query[512];
	if(id == -1) return Error(playerid, "Can't add any more ATM.");
 	new Float: x, Float: y, Float: z;
 	GetPlayerPos(playerid, x, y, z);

	AtmData[id][atmX] = x;
	AtmData[id][atmY] = y;
	AtmData[id][atmZ] = z;
	AtmData[id][atmRX] = AtmData[id][atmRY] = AtmData[id][atmRZ] = 0.0;
	AtmData[id][atmInt] = GetPlayerInterior(playerid);
	AtmData[id][atmWorld] = GetPlayerVirtualWorld(playerid);
	AtmData[id][atmMoney] = 1000000;
	
	new str[128];
	AtmData[id][atmObjID] = CreateDynamicObject(19324, AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ], AtmData[id][atmRX], AtmData[id][atmRY], AtmData[id][atmRZ], AtmData[id][atmWorld], AtmData[id][atmInt], -1, 10.0, 10.0);
	format(str, sizeof(str), "{00FFFF}[ID: %d]\n"YELLOW_E"/ATM", id);
	AtmData[id][atmLabel] = CreateDynamic3DTextLabel(str, COLOR_LIGHTGREEN, AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, AtmData[id][atmWorld], AtmData[id][atmInt], -1, 10.0);
	AtmData[id][atmpickup] = CreateDynamicCP(AtmData[id][atmX], AtmData[id][atmY]+1, AtmData[id][atmZ], 1.0, -1, -1, -1, 5.0);
	Iter_Add(ATMS, id);
	
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO atms SET id='%d', posx='%f', posy='%f', posz='%f', posrx='%f', posry='%f', posrz='%f', interior='%d', world='%d'", id, AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ], AtmData[id][atmRX], AtmData[id][atmRY], AtmData[id][atmRZ], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	mysql_tquery(g_SQL, query, "OnAtmCreated", "ii", playerid, id);
	return 1;
}

CMD:editatm(playerid, params[])
{
    if(pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);
	
	if(pData[playerid][EditingATMID] != -1) return Error(playerid, "You're already editing.");

	new id;
	if(sscanf(params, "i", id)) return Usage(playerid, "/editatm [id]");
	if(!Iter_Contains(ATMS, id)) return Error(playerid, "Invalid ID.");
	if(!IsPlayerInRangeOfPoint(playerid, 30.0, AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ])) return Error(playerid, "You're not near the atm you want to edit.");
	pData[playerid][EditingATMID] = id;
	EditDynamicObject(playerid, AtmData[id][atmObjID]);
	return 1;
}

CMD:removeatm(playerid, params[])
{
    if(pData[playerid][pAdmin] < 5)
		return PermissionError(playerid);
		
	new id, query[512];
	if(sscanf(params, "i", id)) return Usage(playerid, "/removeatm [id]");
	if(!Iter_Contains(ATMS, id)) return Error(playerid, "Invalid ID.");
	
	if(Atm_BeingEdited(id)) return Error(playerid, "Can't remove specified atm because its being edited.");
	DestroyDynamicObject(AtmData[id][atmObjID]);
	DestroyDynamic3DTextLabel(AtmData[id][atmLabel]);
	if(IsValidDynamicPickup(AtmData[id][atmpickup]))
		DestroyDynamicPickup(AtmData[id][atmpickup]);

	AtmData[id][atmX] = AtmData[id][atmY] = AtmData[id][atmZ] = AtmData[id][atmRX] = AtmData[id][atmRY] = AtmData[id][atmRZ] = 0.0;
	AtmData[id][atmInt] = AtmData[id][atmWorld] = 0;
	AtmData[id][atmObjID] = -1;
	AtmData[id][atmLabel] = Text3D: -1;
	Iter_Remove(ATMS, id);
	
	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM atms WHERE id=%d", id);
	mysql_tquery(g_SQL, query);
	Servers(playerid, "You removed ATM id %d.", id);
	return 1;
}

CMD:nearatm(playerid, params[])
{
	if(pData[playerid][pAdmin] < 5) return PermissionError(playerid);
	new id = -1;
	id = GetClosestATM(playerid);
	if(id > -1)
	{
		SendCustomMessage(playerid, "ATM", ""YELLOW_E"ATM ID: %d", id);
	}
	return 1;
}

CMD:gotoatm(playerid, params[])
{
	new id;
	if(pData[playerid][pAdmin] < 3)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", id))
		return Usage(playerid, "/gotoatm [id]");
	if(!Iter_Contains(ATMS, id)) return Error(playerid, "The atm you specified ID of doesn't exist.");
	
	SetPlayerPosition(playerid, AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ], 2.0);
    SetPlayerInterior(playerid, AtmData[id][atmInt]);
    SetPlayerVirtualWorld(playerid, AtmData[id][atmWorld]);
	Servers(playerid, "You has teleport to atm id %d", id);
	return 1;
}

CMD:atm(playerid, params[])
{
	new id = -1;
	id = GetClosestATM(playerid);

	if(pData[playerid][IsLoggedIn] == false) return Error(playerid, "You must logged in!");
	if(pData[playerid][pInjured] >= 1) return Error(playerid, "You can't use this at this moment!");
	
	if(IsPlayerInDynamicCP(playerid, AtmData[id][atmpickup]))
	{
		new tstr[128];
		format(tstr, sizeof(tstr), ""ORANGE_E"No Rek: "LB_E"%d", pData[playerid][pBankRek]);
		Dialog_Show(playerid, DialogATM, DIALOG_STYLE_LIST, tstr, "Check Balance\nWithdraw Money\nSign Paycheck", "Select", "Cancel");
	}
	return 1;
}

CMD:deposit(playerid, params[])
{
	new String[500], amount[32];
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 4 && IsPlayerInRangeOfPoint(playerid, 3.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
			if(sscanf(params, "s[32]", amount))
			{
				SendClientMessageEx(playerid, COLOR_WHITE, "KEGUNAAN: /deposit [amount($0.01+)]");
				return 1;
			}

			new totalcash[25], dollars, cents;
			if(strfind(amount, ".", true) != -1)
			{
				sscanf(amount, "p<.>dd", dollars, cents);
				format(totalcash, sizeof(totalcash), "%d%02d", dollars, cents);
			}
			else
			{
				sscanf(amount, "d", dollars);
				format(totalcash, sizeof(totalcash), "%d00", dollars);
			}

			if(strval(totalcash) > GetPlayerMoney(playerid))
			{
				SendClientMessageEx(playerid, COLOR_GREY, "Anda tidak memiliki uang sebesar itu.");
				return 1;
			}
			if(strval(totalcash) <= 0) { SendClientMessageEx(playerid,COLOR_WHITE,"ERROR: Tidak bisa dibawah $0.00 ."); return 1; }
			GivePlayerMoneyEx(playerid, -strval(totalcash));
			pData[playerid][pBankMoney] += strval(totalcash);
			new query[512];
			mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET bmoney=%d,money=%d WHERE reg_id=%d", pData[playerid][pBankMoney], pData[playerid][pMoney], pData[playerid][pID]);
			mysql_tquery(g_SQL, query);
			format(String, sizeof(String), "BANK: {ffffff}You've stored {ffff00}%s{ffffff} into your bank account", FormatMoney(strval(totalcash)));
			SendClientMessageEx(playerid, COLOR_ARWIN, String);
			format(String, sizeof(String), "BALANCE: {ffff00}%s", FormatMoney(pData[playerid][pBankMoney]));
			SendClientMessageEx(playerid, COLOR_ARWIN, String);
		}
	}
	return 1;
}

CMD:withdraw(playerid, params[])
{
	new String[500], amount[32];
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 4 && IsPlayerInRangeOfPoint(playerid, 3.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
			if(sscanf(params, "s[32]", amount))
			{
				SendClientMessageEx(playerid, COLOR_GRAD2, "KEGUNAAN: /withdraw [Jumlah]");
				format(String, sizeof(String), "BANK: "WHITE_E"Anda memiliki uang sebesar "GREEN_E"%s "WHITE_E"di dalam Akun ATM Anda.", FormatMoney(pData[playerid][pBankMoney]));
				SendClientMessageEx(playerid, COLOR_ARWIN, String);
				return 1;
			}

			new totalcash[25], dollars, cents;
			if(strfind(amount, ".", true) != -1)
			{
				sscanf(amount, "p<.>dd", dollars, cents);
				format(totalcash, sizeof(totalcash), "%d%02d", dollars, cents);
			}
			else
			{
				sscanf(amount, "d", dollars);
				format(totalcash, sizeof(totalcash), "%d00", dollars);
			}

			if(strval(totalcash) > pData[playerid][pBankMoney])
			{
				return SendClientMessageEx(playerid, COLOR_GRAD2, "Anda tidak memiliki uang sebesar itu di dalam Akun ATM anda!");
			}
			if(strval(totalcash) <= 0) return SendClientMessageEx(playerid, COLOR_GREY, "Tidak bisa dibawah $0.00");
			GivePlayerMoneyEx(playerid, strval(totalcash));
			pData[playerid][pBankMoney] -= strval(totalcash);
			new query[512];
			mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET bmoney=%d,money=%d WHERE reg_id=%d", pData[playerid][pBankMoney], pData[playerid][pMoney], pData[playerid][pID]);
			mysql_tquery(g_SQL, query);
			format(String, sizeof(String), "BANK: {ffffff}You've withdrawn {ffff00}%s{ffffff} from your bank account", FormatMoney(strval(totalcash)));
			SendClientMessageEx(playerid, COLOR_ARWIN, String);
			format(String, sizeof(String), "BALANCE: {ffff00}%s",FormatMoney(pData[playerid][pBankMoney]));
			SendClientMessageEx(playerid, COLOR_ARWIN, String);
		}
	}
	return 1;
}

CMD:transfer(playerid, params[])
{
	new amount[32], otherid;
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 4 && IsPlayerInRangeOfPoint(playerid, 3.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
			if(sscanf(params, "us[32]", otherid, amount)) return SendClientMessageEx(playerid, COLOR_WHITE, "KEGUNAAN: /transfer [playerid/name] [ammount]");
			if(otherid == INVALID_PLAYER_ID) return Error(playerid, "That player is disconnected.");
			if(otherid == playerid) return Error(playerid, "You can't transfer money to yourself.");

			new totalcash[25], dollars, cents;
			if(strfind(amount, ".", true) != -1)
			{
				sscanf(amount, "p<.>dd", dollars, cents);
				format(totalcash, sizeof(totalcash), "%d%02d", dollars, cents);
			}
			else
			{
				sscanf(amount, "d", dollars);
				format(totalcash, sizeof(totalcash), "%d00", dollars);
			}

			if(strval(totalcash) > pData[playerid][pBankMoney]) return SendClientMessageEx(playerid, COLOR_GREY, "Anda tidak memiliki uang sebesar itu dibank anda");
			if(strval(totalcash) <= 0) { SendClientMessageEx(playerid,COLOR_WHITE,"ERROR: Tidak bisa dibawah $0.00 ."); return 1; }
			pData[playerid][pBankMoney] -= strval(totalcash);
			pData[otherid][pBankMoney] += strval(totalcash);
			SendCustomMessage(playerid, "BANK", "You successfully transferred "GREEN_E"%s "WHITE_E"to "AQUA_E"%s", FormatMoney(strval(totalcash)), pData[otherid][pName]);
			SendCustomMessage(otherid, "BANK", "You transferred "GREEN_E"%s "WHITE_E"from "AQUA_E"%s", FormatMoney(strval(totalcash)), pData[playerid][pName]);
		}
	}
	return 1;
}
