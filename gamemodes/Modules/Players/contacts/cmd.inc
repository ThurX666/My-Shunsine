
CMD:call(playerid, params[])
{
	new phonenumb;
	new String[500];
	if(pData[playerid][pPhone] == 0) return Error(playerid, "You dont have phone!");
	if(pData[playerid][pPhoneCredit] <= 0) return Error(playerid, "You dont have phone credits!");
	if (pData[playerid][pPhoneOff])
		return Error(playerid, "Your phone must be powered on.");
	if(sscanf(params, "d", phonenumb))
	{
		Usage(playerid, "/call [number]");
		SendClientMessageEx(playerid, COLOR_ARWIN, "OPERATOR: {FFFFFF}You've reached the operator");
		SendClientMessageEx(playerid, COLOR_ARWIN, "OPERATOR: {FFFFFF}Call 911 for emergency services");
		SendClientMessageEx(playerid, COLOR_ARWIN, "OPERATOR: {FFFFFF}Call 888 for SAGS call center");	
		SendClientMessageEx(playerid, COLOR_ARWIN, "OPERATOR: {FFFFFF}Call 111 for Taxi/Mechanic service");	
		return 1;	
	}
	if(phonenumb == 888)
	{
		SendClientMessageEx(playerid, COLOR_ARWIN, "888: {FFFFFF}You have reached the SAGS call center.");
		SendClientMessageEx(playerid, COLOR_ARWIN, "888: {FFFFFF}How can I help you?");
		Mobile[playerid] = 888;
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
		return 1;
	}
	if(phonenumb == 911)
	{
		SendClientMessageEx(playerid, COLOR_ARWIN, "911: {FFFFFF}You have reached the 911 Emergency Service.");
		SendClientMessageEx(playerid, COLOR_ARWIN, "911: {FFFFFF}Do you need a police or a paramedic ?");
		Mobile[playerid] = 911;
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
		return 1;
	}
	if(phonenumb == 111)
	{
		SendClientMessageEx(playerid, COLOR_ARWIN, "111: {FFFFFF}You have reached the 111 Service.");
		SendClientMessageEx(playerid, COLOR_ARWIN, "111: {FFFFFF}Do you need a taxi or a mechanic ?");
		Mobile[playerid] = 111;
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
		return 1;
	}
	if(Mobile[playerid] != INVALID_PLAYER_ID)
	{
		SendClientMessageEx(playerid, COLOR_GRAD2, "You are already on a call...");
		return 1;
	}
	if(phonenumb == pData[playerid][pPhone]) return Error(playerid, "Nomor sedang sibuk!");
	if(phonenumb < 1) return Error(playerid, "Tidak bisa call di bawah no 0");
	foreach(new ii : Player)
	{
		if(pData[ii][pPhone] == phonenumb)
		{
			if (pData[ii][pPhoneOff])
				return Error(playerid, "The recipient has their cellphone powered off.");
			if(pData[ii][IsLoggedIn] == false || !IsPlayerConnected(ii)) return Error(playerid, "This number is not actived!");

			if(pData[ii][pCall] == INVALID_PLAYER_ID)
			{
				pData[playerid][pCall] = ii;
				format(String, sizeof(String), "PHONE: "YELLOW_E"Anda telah mencoba menghubungi {00FFFF}%s (%d)"YELLOW_E" silahkan tunggu sampai di jawab", GetContactNameByNumber(playerid, pData[ii][pPhone]), pData[ii][pPhone]);
				SendClientMessageEx(playerid, COLOR_RED, String);

				format(String, sizeof(String), "PHONE: "RED_E"%s (%d) "WHITE_E"is trying to call you, use "YELLOW_E"'/p' to answer call", GetContactNameByNumber(ii, pData[playerid][pPhone]), pData[playerid][pPhone]);
				SendClientMessageEx(ii, COLOR_ARWIN, String);
				
				PlayerPlaySound(playerid, 1052, 0,0,0);
				PlayerPlaySound(ii, 1139, 0,0,0);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
				SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s takes out a cellphone and calling someone.", ReturnName(playerid));
				return 1;
			}
			else return Error(playerid, "Nomor ini sedang sibuk.");
		}
	}
	return 1;
}

CMD:p(playerid, params[])
{
	if(pData[playerid][pCall] != INVALID_PLAYER_ID)
		return Error(playerid, "Anda sudah sedang menelpon seseorang!");
		
	if(pData[playerid][pInjured] != 0)
		return Error(playerid, "You cant do that in this time.");
		
	foreach(new ii : Player)
	{
		if(playerid == pData[ii][pCall])
		{
			pData[ii][pPhoneCredit]--;
			
			pData[playerid][pCall] = ii;
			SendClientMessageEx(ii, COLOR_ARWIN, "CELLPHONE: {ffffff}Telepon anda telah di jawab.");
			SendClientMessageEx(ii, COLOR_ARWIN, "CELLPHONE: {ffffff}Gunakan chat biasa untuk berkomunikasi lewat telpon, '/hu' untuk menutup telpon.");
			SendClientMessageEx(playerid, COLOR_ARWIN, "CELLPHONE: {ffffff}Anda telah menjawab telepon.");
			SendClientMessageEx(playerid, COLOR_ARWIN, "CELLPHONE: {ffffff}Gunakan chat biasa untuk berkomunikasi lewat telpon, '/hu' untuk menutup telpon.");
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
			return 1;
		}
	}
	return 1;
}

CMD:hu(playerid, params[])
{
	new caller = pData[playerid][pCall];
	if(IsPlayerConnected(caller) && caller != INVALID_PLAYER_ID)
	{
		pData[caller][pCall] = INVALID_PLAYER_ID;
		SetPlayerSpecialAction(caller, SPECIAL_ACTION_STOPUSECELLPHONE);
		//SendNearbyMessage(caller, 20.0, COLOR_PURPLE, "* %s puts away their cellphone.", ReturnName(caller));
		SendClientMessageEx(caller, COLOR_GREY, "Telepon terputus...");
		
		//SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s puts away their cellphone.", ReturnName(playerid));
		SendClientMessageEx(playerid, COLOR_GREY, "Telepon terputus...");
		pData[playerid][pCall] = INVALID_PLAYER_ID;
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		DeletePVar(playerid, "UsePayphone");
	}
	return 1;
}

CMD:reply(playerid, params[])
{
	if(!pData[playerid][pPhone])
	    return Error(playerid, "You don't have a cellphone on you.");

    if (pData[playerid][pInjured])
	    return Error(playerid, "You can't use this command now.");

	if(pData[playerid][pSMS] == 0)
	    return Error(playerid, "There is no one messaging you.");
	if (pData[playerid][pPhoneOff])
		return Error(playerid, "Your phone must be powered on.");
	new str[128];
	format(str, sizeof(str), "Reply to: %d\nMessage:", GetContactNameByNumber(playerid, pData[playerid][pSMS]));
	Dialog_Show(playerid, SMSReply, DIALOG_STYLE_INPUT, "Message Reply", str, "Send", "Close");
	return 1;
}

/*CMD:phone(playerid, params[])
{
	if(pData[playerid][pPhone] == 0) return Error(playerid, "You dont have phone!");
	static
	    str[32];

	format(str, sizeof(str), "Phone (#%d)", pData[playerid][pPhone]);

	if (pData[playerid][pPhoneOff]) {
		Dialog_Show(playerid, MyPhone, DIALOG_STYLE_LIST, str, "Call\nContact\nSend Text Message\nPhone Privacy\nMessaging\n"ORANGE_E"Power off", "Select", "Cancel");
	}
	else
	{
	    Dialog_Show(playerid, MyPhone, DIALOG_STYLE_LIST, str, "Call\nContact\nSend Text Message\nPhone Privacy\nMessaging\n"ORANGE_E"Power off", "Select", "Cancel");
	}
	return 1;
}*/

CMD:sms(playerid, params[])
{
	new ph, text[50], String[500], ii, nametarget[32], nameplayerid[32];
	if(pData[playerid][pPhone] == 0) return Error(playerid, "You dont have phone!");
	if(pData[playerid][pPhoneCredit] <= 0) return Error(playerid, "You dont have phone credits!");
	if(pData[playerid][pInjured] != 0) return Error(playerid, "You cant do at this time.");
	if (pData[playerid][pPhoneOff])
		return Error(playerid, "Your phone must be powered on.");
	if(sscanf(params, "ds[50]", ph, text))
        return Usage(playerid, "/sms [phone number] [message max 50 text]");

	if (!ph)
	    return Error(playerid, "The specified phone number is not in service.");

	if ((ii = GetNumberOwner(ph)) != INVALID_PLAYER_ID)
	{
	/*    if (ii == playerid)
	        return SendErrorMessage(playerid, "You can't text yourself!");*/

		if (pData[ii][pPhoneOff])
		    return Error(playerid, "The recipient has their cellphone powered off.");

		for (new i = 0; i != MAX_CONTACTS; i ++) if (ContactData[playerid][i][contactExists]) 
		{
			if(pData[ii][pPhone] == ContactData[playerid][i][contactNumber])
			{
				format(nametarget, 32, "%s", ContactData[playerid][i][contactName]);
			}
			else
			{
				format(nametarget, 32, "%s", "Unknown");
			}
		}
		else for (new id = 0; id != MAX_CONTACTS; id ++) if (ContactData[ii][id][contactExists]) 
		{
			if(pData[ii][pPhone] == ContactData[ii][id][contactNumber])
			{
				format(nameplayerid, 32, "%s", ContactData[ii][id][contactName]);
			}
			else
			{
				format(nameplayerid, 32, "%s", "Unknown");
			}
		}
		SendClientMessageEx(ii, COLOR_RED, "SMS: "YELLOW_E"Message from "AQUA_E"%s (%d)", GetContactNameByNumber(ii, pData[playerid][pPhone]), pData[playerid][pPhone]);
		SendClientMessageEx(ii, COLOR_RED, "MESSAGE: "YELLOW_E"%s", text);

		SendClientMessageEx(playerid, COLOR_WHITE, "AME: {C2A2DA}types something to his cellphone");
		format(String, sizeof(String), "types something to his cellphone");
		SetPlayerChatBubble(playerid, String, COLOR_PURPLE, 5.0, 5000);
		SendClientMessageEx(playerid, COLOR_RED, "SMS: "YELLOW_E"Message sent to {00FFFF}%s %d", GetContactNameByNumber(playerid, pData[ii][pPhone]), pData[ii][pPhone]);
		SendClientMessageEx(playerid, COLOR_RED, "MESSAGE: "YELLOW_E"%s", text);

		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		PlayerPlaySound(ii, 1139, 0.0, 0.0, 0.0);
		pData[ii][pSMS] = pData[playerid][pPhone];
		
		pData[playerid][pPhoneCredit] -= 1;

		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO sms(owner, message, number, type) VALUES ('%d', '%s', '%d', '%d')", pData[ii][pID], text, pData[playerid][pPhone], 2);
		mysql_tquery(g_SQL, query);

		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO sms(owner, message, number, type) VALUES ('%d', '%s', '%d', '%d')", pData[playerid][pID], text, pData[ii][pPhone], 1);
		mysql_tquery(g_SQL, query);
	}
	else
	{
	    new query[103];
		mysql_format(g_SQL, query, sizeof query, "SELECT * FROM `players` WHERE `phone` = '%d' LIMIT 1", ph);
		mysql_pquery(g_SQL, query, "OnSMSsend", "dds", playerid, ph, text);
	}
	return 1;
}
