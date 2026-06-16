enum
{
	A_OBJECT_SLOT_SPINE = 0, 		// Batang tubuh
	A_OBJECT_SLOT_HAND, 			// Tangan
	A_OBJECT_BONE_RIGHT_HAND,			// Pinggul

};

CMD:armoury(playerid)
{
	new strings[212];
	if(pData[playerid][pFaction] != 1) return Error(playerid, "You must be a police officer.");
	if(pData[playerid][pOnDuty] <= 0) return Error(playerid, "Kamu harus On duty!");	
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 13 && IsPlayerInRangeOfPoint(playerid, 2.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
			SetPlayerArmourEx(playerid, 90);
			SAPDArmoury -= 1;
			Server_Save();
			format(strings, sizeof(strings), "[ID: %d]\nSan Andreas Police Department\n"GREEN_E"SAPD Central Armoury\n"WHITE_E"Stock: "YELLOW_E"%d/1000\n"GREEN_E"SAPD Central Ammo\n"WHITE_E"Stock: "YELLOW_E"%d/10000\n"WHITE_E"Use "YELLOW_E"'/armoury' "WHITE_E"to acces armoury\n"WHITE_E"Use "YELLOW_E"'/sapdammo' "WHITE_E"to acces ammo JHP", id, SAPDArmoury, SAPDAmmo);
			UpdateDynamic3DTextLabelText(Location[id][locLabel], -1, strings);
		} 
	}
	return 1;
}

CMD:sapdammo(playerid)
{
	new strings[212];
	if(pData[playerid][pFaction] != 1) return Error(playerid, "You must be a police officer.");
	if(pData[playerid][pOnDuty] <= 0) return Error(playerid, "Kamu harus On duty!");	
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 13 && IsPlayerInRangeOfPoint(playerid, 2.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
			new
				weaponid = GetWeapon(playerid);

			if(!weaponid) return Error(playerid, "You are not holding any weapon!");
			PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_ammo] += 500;
			PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_typesurplus] = 2;
			SendCustomMessage(playerid, "AMMO-JHP", "Anda berhasil mengambil ammo type JHP pada stock!");
			SAPDAmmo -= 500;
			Server_Save();
			format(strings, sizeof(strings), "[ID: %d]\nSan Andreas Police Department\n"GREEN_E"SAPD Central Armoury\n"WHITE_E"Stock: "YELLOW_E"%d/1000\n"GREEN_E"SAPD Central Ammo\n"WHITE_E"Stock: "YELLOW_E"%d/10000\n"WHITE_E"Use "YELLOW_E"'/armoury' "WHITE_E"to acces armoury\n"WHITE_E"Use "YELLOW_E"'/sapdammo' "WHITE_E"to acces ammo JHP", id, SAPDArmoury, SAPDAmmo);
			UpdateDynamic3DTextLabelText(Location[id][locLabel], -1, strings);
		} 
	}
	return 1;
}

CMD:setbadge(playerid, params[])
{
    if(pData[playerid][pFaction] == -1) return Error(playerid, "You must be a faction member.");
    if(pData[playerid][pFactionRank] < 4) return Error(playerid, "You must be at least rank 4");

    static
        userid,
        badge;

    if(sscanf(params, "ud", userid, badge)) return Usage(playerid, "/setbadge [playerid] [badge number]");
    if(pData[userid][pFaction] != pData[playerid][pFaction]) return Error(playerid, "This player is'nt in your faction.");

    new str[24];
    switch (pData[playerid][pFaction]) {
        case 1: format(str,sizeof(str),"%d",badge);
        case 2: format(str,sizeof(str),"%d",badge);
        case 3: format(str,sizeof(str),"%d",badge);
		case 4: format(str,sizeof(str),"%d",badge);
    }

    format(pData[userid][pBadge], 24, "%s", str);
    SendCustomMessage(userid, "BADGE", "%s have set your badge to %s", ReturnName(playerid), pData[userid][pBadge]);
    SendCustomMessage(playerid, "BADGE", "You have set badge for %s to %s", ReturnName(userid), pData[userid][pBadge]);
    return 1;
}

CMD:showbadge(playerid, params[])
{
    static 
        userid;
	if(pData[playerid][pFaction] == -1) return Error(playerid, "You must be a faction member.");
    if(sscanf(params, "d", userid)) return Usage(playerid, "/showbadge [playerid]");
    if(userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0)) return Error(playerid, "That player is disconnected or not near you.");

	new str[32];
	switch (pData[playerid][pFaction]) {
        case 1: format(str,sizeof(str),"San Andreas Police Department");
        case 2: format(str,sizeof(str),"San Andreas Goverment Service");
		case 3: format(str,sizeof(str),"San Andreas Medical Department");
		case 4: format(str,sizeof(str),"San Andreas Network");
    }
    SendClientMessageEx(userid, COLOR_YELLOW,"Official badge of {00FFFF}%s", str);
    SendClientMessageEx(userid, COLOR_YELLOW, "Full Name: {00FFFF}%s.", ReturnName(playerid));
    SendClientMessageEx(userid, COLOR_YELLOW, "Badge Number: "RED_E"%s", pData[playerid][pBadge]);
    SendClientMessageEx(userid, COLOR_YELLOW, "Rank: "RED_E"%s.", pData[playerid][pFactionRankName]);
    SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s showing his badge to %s", ReturnName(playerid), ReturnName(userid));
    return 1;
}

CMD:frankname(playerid, params[])
{
    if(pData[playerid][pFaction] == -1)
        return Error(playerid, "You must be a faction member.");

    if(pData[playerid][pFactionRank] < 5)
        return Error(playerid, "You must be at least rank 5");

    new userid, rankname[24];
    if (sscanf(params, "us[24]", userid, rankname))
        return Usage(playerid, "/frankname [playerid/name] [rank name]");

    if (userid == INVALID_PLAYER_ID || !IsPlayerConnected(userid))
        return Error(playerid, "Invalid playerid or name");

    if (strlen(rankname) < 1 || strlen(rankname) > 24)
        return Error(playerid, "Rank name cannot go below 1 or above 24 characters.");

    format(pData[userid][pFactionRankName], 24, "%s", rankname);
    SendCustomMessage(playerid, "FACTION", "You've been set "YELLOW_E"%s "WHITE_E"faction rank name to: "YELLOW_E"%s", ReturnName(userid), rankname);
    SendCustomMessage(userid, "FACTION", YELLOW_E"%s "WHITE_E"has been set your faction rank name to: "YELLOW_E"%s", ReturnName(playerid), rankname);
    return 1;
}

//-----------[ Faction Commands ]------------
CMD:factionhelp(playerid)
{
	if(pData[playerid][pFaction] == 1)
	{
		new str[3500];
		strcat(str, ""BLUE_E"SAPD: /locker /or (/r)adio /od /d(epartement) (/gov)ernment (/m)egaphone /invite /uninvite /setrank /frankname /setbadge\n");
		strcat(str, ""BLUE_E"SAPD: /sapdonline /(un)cuff /tazer /getphone /tracephone /traceplate /setunit /detain /arrest /release /flare /destroyflare /checkveh\n");
		strcat(str, ""BLUE_E"SAPD: /createlicense /spike /destroyspike /impound /locktire /pdveh /destroyallspike /take /revoke\n");
		strcat(str, ""YELLOW_E"NOTE: Lama waktu duty anda akan menjadi gaji anda pada saat paycheck!\n");
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "San Andreas Police Department", str, "Close", "");
	}
	else if(pData[playerid][pFaction] == 2)
	{
		new str[3500];
		strcat(str, ""LB_E"SAGS: /locker /or (/r)adio /od /d(epartement) (/gov)ernment (/m)egaphone /invite /uninvite /setrank /frankname /setbadge\n");
		strcat(str, ""LB_E"SAGS: /sagsonline /(un)cuff\n");
		strcat(str, ""YELLOW_E"NOTE: Lama waktu duty anda akan menjadi gaji anda pada saat paycheck!\n");
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "San Andreas Goverment Service", str, "Close", "");
	}
	else if(pData[playerid][pFaction] == 3)
	{
		new str[3500];
		strcat(str, ""PINK_E"SAMD: /locker /or (/r)adio /od /d(epartement) (/gov)ernment (/m)egaphone /invite /uninvite /setrank /frankname /setbadge\n");
		strcat(str, ""PINK_E"SAMD: /samdonline /loadinjured /dropinjured /ems /findems /rescue /treatment /surgery /takepills /givepills \n");
		strcat(str, ""YELLOW_E"NOTE: Lama waktu duty anda akan menjadi gaji anda pada saat paycheck!\n");
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "San Andreas Medical Department", str, "Close", "");
	}
	else if(pData[playerid][pFaction] == 4)
	{
		new str[3500];
		strcat(str, ""ORANGE_E"SANA: /locker /or (/r)adio /od /d(epartement) (/gov)ernment (/m)egaphone /invite /uninvite /setrank /frankname /setbadge\n");
		strcat(str, ""ORANGE_E"SANA: /sanaonline /broadcast /bc /live /inviteguest /removeguest\n");
		strcat(str, ""YELLOW_E"NOTE: Lama waktu duty anda akan menjadi gaji anda pada saat paycheck!\n");
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "San Andreas Network", str, "Close", "");
	}
	else if(pData[playerid][pFamily] != -1)
	{
		new str[3500];
		strcat(str, ""WHITE_E"Family: /fsave /f(amily) /finvite /funinvite /fsetrank\n");
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Family Command", str, "Close", "");
	}
	else
	{
		Error(playerid, "Anda tidak bergabung dalam faction/family manapun!");
	}
	return 1;
}

CMD:or(playerid, params[])
{
    new text[128];
    
    if(pData[playerid][pFaction] == 0)
        return Error(playerid, "You must in faction member to use this command");
            
    if(sscanf(params,"s[128]",text))
        return Usage(playerid, "/or(OOC radio) [text]");

    if(strval(text) > 128)
        return Error(playerid,"Text too long.");

    if(pData[playerid][pFaction] == 1) {
        SendFactionMessage(1, COLOR_ARWIN, "(( %s: %s ))", ReturnName(playerid), text);
		//format(mstr, sizeof(mstr), "[<RADIO>]\n* %s *", text);
		//SetPlayerChatBubble(playerid, mstr, COLOR_RADIO, 10.0, 3000);
    }
    else if(pData[playerid][pFaction] == 2) {
        SendFactionMessage(2, COLOR_ARWIN, "(( %s: %s ))", ReturnName(playerid), text);
		//format(mstr, sizeof(mstr), "[<RADIO>]\n* %s *", text);
		//SetPlayerChatBubble(playerid, mstr, COLOR_RADIO, 10.0, 3000);
    }
    else if(pData[playerid][pFaction] == 3) {
        SendFactionMessage(3, COLOR_ARWIN, "(( %s: %s ))", ReturnName(playerid), text);
		//format(mstr, sizeof(mstr), "[<RADIO>]\n* %s *", text);
		//SetPlayerChatBubble(playerid, mstr, COLOR_RADIO, 10.0, 3000);
    }
    else if(pData[playerid][pFaction] == 4) {
        SendFactionMessage(4, COLOR_ARWIN, "(( %s: %s ))", ReturnName(playerid), text);
		//format(mstr, sizeof(mstr), "[<RADIO>]\n* %s *", text);
		//SetPlayerChatBubble(playerid, mstr, COLOR_RADIO, 10.0, 3000);
    }
    else
            return Error(playerid, "You are'nt in any faction");
    return 1;
}

CMD:r(playerid, params[])
{
    new text[128];

    if(pData[playerid][pInjured] == 1) return Error(playerid, "You injured at the moment.");
    if(pData[playerid][pFaction] == 0) return Error(playerid, "You must in faction member to use this command");
    if(sscanf(params,"s[128]",text)) return Usage(playerid, "/r(adio) [text]");
	if(strval(text) > 128) return Error(playerid,"Text too long.");
	if(pData[playerid][pTogRadio] == 1) return Error(playerid, "Your radio is turned off!");

	new badgeStr[32];
	if(pData[playerid][pBadge][0] != EOS && strlen(pData[playerid][pBadge]) > 0)
		format(badgeStr, sizeof(badgeStr), " [#%s]", pData[playerid][pBadge]);
	else
		badgeStr[0] = EOS;

  	if(pData[playerid][pFaction] == 1) {
   		SendFactionMessage(1, COLOR_RADIO, "{2F93F5}[RADIO] %s %s%s: %s", pData[playerid][pFactionRankName], ReturnName2(playerid), badgeStr, FormatRadio(playerid, text));

    }
    else if(pData[playerid][pFaction] == 2) {
    	SendFactionMessage(2, COLOR_RADIO, "[RADIO] %s %s%s: %s", pData[playerid][pFactionRankName], ReturnName2(playerid), badgeStr, FormatRadio(playerid, text));
	}
   	else if(pData[playerid][pFaction] == 3) {
    	SendFactionMessage(3, COLOR_RADIO, ""PINK_E"[RADIO] %s %s%s: %s", pData[playerid][pFactionRankName], ReturnName2(playerid), badgeStr, FormatRadio(playerid, text));
	}
   	else if(pData[playerid][pFaction] == 4) {
     	SendFactionMessage(4, COLOR_RADIO, ""ORANGE_E"[RADIO] %s %s%s: %s", pData[playerid][pFactionRankName], ReturnName2(playerid), badgeStr, FormatRadio(playerid, text));
	}
    else
    	return Error(playerid, "You are'nt in any faction");
    return 1;
}
CMD:od(playerid, params[])
{
    new text[128];

    if(pData[playerid][pFaction] == 0)
        return Error(playerid, "You must in faction member to use this command");

    if(sscanf(params,"s[128]",text))
        return Usage(playerid, "/od(OOC departement) [text]");

    if(strval(text) > 128)
        return Error(playerid,"Text too long.");

    if(pData[playerid][pFaction] < 1 || pData[playerid][pFaction] > 4)
        return Error(playerid, "You are'nt in any faction");

    SendFactionMessage(pData[playerid][pFaction], 0xFFD7004A, "(( %s: %s ))", ReturnName(playerid), text);
    return 1;
}

CMD:d(playerid, params[])
{
    new text[128];

    if(pData[playerid][pFaction] == 0)
        return Error(playerid, "You must in faction member to use this command");

    if(sscanf(params,"s[128]",text))
        return Usage(playerid, "/d(epartement) [text]");

    if(strval(text) > 128)
        return Error(playerid,"Text too long.");

    switch(pData[playerid][pFaction])
    {
        case 1:
        {
            SendFactionMessage(1, COLOR_RADIO, ""BLUE_E"SAPD Departement: %s %s: %s", pData[playerid][pFactionRankName], ReturnName2(playerid), FormatRadio(playerid, text));
        }
        case 2:
        {
            SendFactionMessage(2, COLOR_RADIO, ""BLUE_E"SAGS Departement: %s %s: %s", pData[playerid][pFactionRankName], ReturnName2(playerid), FormatRadio(playerid, text));
        }
        case 3:
        {
            SendFactionMessage(3, COLOR_RADIO, ""PINK_E"SAMD Departement: %s %s: %s", pData[playerid][pFactionRankName], ReturnName2(playerid), FormatRadio(playerid, text));
        }
        case 4:
        {
            SendFactionMessage(4, COLOR_RADIO, ""ORANGE_E"SANA Departement: %s %s: %s", pData[playerid][pFactionRankName], ReturnName2(playerid), FormatRadio(playerid, text));
        }
        default:
        {
            return Error(playerid, "You are'nt in any faction");
        }
    }

    return 1;
}

CMD:m(playerid, params[])
{
	if(pData[playerid][pFaction] <= 0)
		return Error(playerid, "You are not faction!");

	if(pData[playerid][pOnDuty] <= 0)
		return Error(playerid, "Kamu harus On duty untuk menggunakan megaphone!");	

	if(isnull(params)) return Usage(playerid, "/m(egaphone) [text]");
	
	if(strlen(params) > 64) 
	{
        SendNearbyMessage(playerid, 60.0, COLOR_YELLOW, "[MEGAPHONE] %s : %.64s", ReturnName2(playerid), params);
        SendNearbyMessage(playerid, 60.0, COLOR_YELLOW, "...%s", params[64]);
    }
    else 
	{
        SendNearbyMessage(playerid, 60.0, COLOR_YELLOW, "[MEGAPHONE] %s : %s", ReturnName2(playerid), params);
    }
	return 1;
}

CMD:gov(playerid, params[])
{
	if(pData[playerid][pFaction] <= 0)
		return Error(playerid, "You are not faction!");
	
	if(pData[playerid][pFactionRank] < 5)
		return Error(playerid, "Only faction level 5-6");
		
	if(pData[playerid][pFaction] == 1)
	{
		new lstr[1024];
		format(lstr, sizeof(lstr), "** SAPD: %s(%d) %s: %s **", pData[playerid][pFactionRankName], pData[playerid][pFactionRank], ReturnName2(playerid), FormatRadio(playerid, params));
		SendClientMessageToAll(COLOR_WHITE, "|___________ Government News Announcement ___________|");
		SendClientMessageToAll(COLOR_BLUE, lstr);
	}
	else if(pData[playerid][pFaction] == 2)
	{
		new lstr[1024];
		format(lstr, sizeof(lstr), "** SAGS: %s(%d) %s: %s **", pData[playerid][pFactionRankName], pData[playerid][pFactionRank], ReturnName2(playerid), FormatRadio(playerid, params));
		SendClientMessageToAll(COLOR_WHITE, "|___________ Government News Announcement ___________|");
		SendClientMessageToAll(COLOR_LBLUE, lstr);
	}
	else if(pData[playerid][pFaction] == 3)
	{
		new lstr[1024];
		format(lstr, sizeof(lstr), "** SAMD: %s(%d) %s: %s **", pData[playerid][pFactionRankName], pData[playerid][pFactionRank], ReturnName2(playerid), FormatRadio(playerid, params));
		SendClientMessageToAll(COLOR_WHITE, "|___________ Government News Announcement ___________|");
		SendClientMessageToAll(COLOR_PINK2, lstr);
	}
	else if(pData[playerid][pFaction] == 4)
	{
		new lstr[1024];
		format(lstr, sizeof(lstr), "** SANA: %s(%d) %s: %s **", pData[playerid][pFactionRankName], pData[playerid][pFactionRank], ReturnName2(playerid), FormatRadio(playerid, params));
		SendClientMessageToAll(COLOR_WHITE, "|___________ Government News Announcement ___________|");
		SendClientMessageToAll(COLOR_ORANGE2, lstr);
	}
	return 1;
}

CMD:setrank(playerid, params[])
{
	new rank, otherid;
	if(pData[playerid][pFactionLead] == 0)return Error(playerid, "You must faction leader!");
	if(pData[playerid][pFactionRank] < 5) return Error(playerid, "You must faction leader!");
	if(sscanf(params, "ud", otherid, rank)) return Usage(playerid, "/setrank [playerid/PartOfName] [rank 1-6]");
	if(otherid == INVALID_PLAYER_ID) return Error(playerid, "Invalid ID.");
	if(otherid == playerid) return Error(playerid, "Invalid ID.");
	if(pData[otherid][pFaction] != pData[playerid][pFaction]) return Error(playerid, "This player is not in your devision!");
	if(rank < 1 || rank > 6) return Error(playerid, "rank must 1 - 6 only");
	pData[otherid][pFactionRank] = rank;
	Servers(playerid, "You has set %s faction rank to level %d", ReturnName2(otherid), rank);
	Servers(otherid, "%s has set your faction rank to level %d", ReturnName2(playerid), rank);
	return 1;
}

CMD:uninvite(playerid, params[])
{
	if(pData[playerid][pFaction] <= 0)
		return Error(playerid, "You are not faction!");
		
	if(pData[playerid][pFactionRank] < 5)
		return Error(playerid, "You must faction level 5 - 6!");
	
	if(!pData[playerid][pOnDuty])
        return Error(playerid, "You must on duty!.");
	new otherid;
    if(sscanf(params, "u", otherid))
        return Usage(playerid, "/uninvite [playerid/PartOfName]");
		
	if(!IsPlayerConnected(otherid))
		return Error(playerid, "Invalid ID.");
	
	if(otherid == playerid)
		return Error(playerid, "Invalid ID.");
	
	if(pData[otherid][pFactionRank] > pData[playerid][pFactionRank])
		return Error(playerid, "You cant kick him.");
		
	pData[otherid][pFactionRank] = 0;
	pData[otherid][pFaction] = 0;
	Servers(playerid, "Anda telah mengeluarkan %s dari faction.", ReturnName2(otherid));
	Servers(otherid, "%s telah mengkick anda dari faction.", ReturnName2(playerid));
	return 1;
}

CMD:invite(playerid, params[])
{
	if(pData[playerid][pFaction] <= 0)
		return Error(playerid, "You are not faction!");
		
	if(pData[playerid][pFactionRank] < 5)
		return Error(playerid, "You must faction level 5 - 6!");
	
	if(!pData[playerid][pOnDuty])
        return Error(playerid, "You must on duty!.");
	new otherid;
    if(sscanf(params, "u", otherid))
        return Usage(playerid, "/invite [playerid/PartOfName]");
		
	if(!IsPlayerConnected(otherid))
		return Error(playerid, "Invalid ID.");
	
	if(otherid == playerid)
		return Error(playerid, "Invalid ID.");
	
	if(!NearPlayer(playerid, otherid, 5.0))
        return Error(playerid, "You must be near this player.");
	
	if(pData[otherid][pFamily] != -1)
		return Error(playerid, "Player tersebut sudah bergabung family");
		
	if(pData[otherid][pFaction] != 0)
		return Error(playerid, "Player tersebut sudah bergabung faction!");

	if(pData[otherid][pCS] < 0)
		return Error(playerid, "You must approved a char story by admin!");
		
	pData[otherid][pFacInvite] = pData[playerid][pFaction];
	pData[otherid][pFacOffer] = playerid;
	Servers(playerid, "Anda telah menginvite %s untuk menjadi faction.", ReturnName2(otherid));
	Servers(otherid, "%s telah menginvite anda untuk menjadi faction. Type: /accept faction or /deny faction!", ReturnName2(playerid));
	return 1;
}

//SAPD Commands
CMD:sapdonline(playerid, params[])
{
	if(pData[playerid][pFaction] != 1)
        return Error(playerid, "You must be a police officer.");
	if(pData[playerid][pFactionRank] < 1)
		return Error(playerid, "You must be high rank!");
		
	new duty[16], lstr[1024];
	format(lstr, sizeof(lstr), "Name\tRank\tStatus\tUnit\tDuty Time\n");
	foreach(new i: Player)
	{
		if(pData[i][pFaction] == 1)
		{
			switch(pData[i][pOnDuty])
			{
				case 0:
				{
					duty = "Off Duty";
				}
				case 1:
				{
					duty = ""BLUE_E"On Duty";
				}
			}
			format(lstr, sizeof(lstr), "%s%s(%d)\t%s(%d)\t%s\t%s\t%d minute", lstr, ReturnName2(i), i, pData[i][pFactionRankName], pData[i][pFactionRank], duty, GetPlayerCallsign(i), pData[i][pOnDutyTime]/10);
			format(lstr, sizeof(lstr), "%s\n", lstr);
		}
	}
	format(lstr, sizeof(lstr), "%s\n", lstr);
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "SAPD Online", lstr, "Close", "");
	return 1;
}

CMD:setunit(playerid, params[]) {
    if (pData[playerid][pFaction] == -1) return Error(playerid, "You must be a faction member.");
    if (!pData[playerid][pOnDuty]) return Error(playerid, "You must duty first");

    new unit[24];
    if (sscanf(params, "s[24]", unit)) return Usage(playerid, "/setunit [callsign]");
    if (strlen(unit) > 24) return Error(playerid, "Callsign too long");
    
    format(pData[playerid][pUnit], 24, "%s", unit);
    SendCustomMessage(playerid, "RADIO", "Radio callsign set to: "YELLOW_E"%s", unit);
    return 1;
}

CMD:flare(playerid, params[])
{
	if(pData[playerid][pFaction] != 1)
        return Error(playerid, "You must be a police officer.");
		
    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	if(IsValidDynamicObject(pData[playerid][pFlare]))
		DestroyDynamicObject(pData[playerid][pFlare]);
		
	pData[playerid][pFlare] = CreateDynamicObject(18728, x, y, z-2.8, 0, 0, a-90);
	SendClientMessageEx(playerid, COLOR_ARWIN, "FLARE: "WHITE_E"request backup is actived! /destroyflare to delete flare.");
	SendFactionMessage(1, COLOR_RADIO, "FLARE: "BLUE_E"Officer "YELLOW_E"%s "BLUE_E"has request a backup in near "RED_E"%s", ReturnName2(playerid), GetLocation(x, y, z));
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s deployed a flare on the ground.", ReturnName2(playerid));
	foreach (new ii : Player) if(pData[ii][pFaction] == 1) SetPlayerGPS(ii, x, y, z);		
    return 1;
}

// CMD:givesim(playerid, params[])
// {
// 	if(pData[playerid][pFaction] != 1)
//         return Error(playerid, "You must be a police officer.");
// 	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 246.1122,120.3927,1003.2743)) return Error(playerid, "Anda harus berada di SAPD!");

//     new otherid;
//     if(sscanf(params, "d", otherid)) return Usage(playerid, "/givesim [playerid]");

// 	pData[otherid][pDriveLic] = 1;
// 	pData[otherid][pDriveLicTime] = gettime() + (91 * 86400);
// 	SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"Anda telah berhasil memberikan surat izin mengemudi kepada "YELLOW_E"%s", ReturnName2(otherid));
// 	SendClientMessageEx(otherid, COLOR_ARWIN, "LICENSE: "YELLOW_E"%s "WHITE_E"telah berhasil memberikan surat izin mengemudi kepada anda", ReturnName2(playerid));
// 	new sext[40], mstr[128];
// 	if(pData[otherid][pGender] == 1) { sext = "Laki-Laki"; } else { sext = "Perempuan"; }
// 	format(mstr, sizeof(mstr), "{FFFFFF}Nama: %s\nNegara: San Andreas\nTgl Lahir: %s\nJenis Kelamin: %s\nBerlaku hingga 14 hari!", ReturnName2(otherid), pData[otherid][pAge], sext);
// 	ShowPlayerDialog(otherid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "ID-Card", mstr, "Tutup", "");	
//     return 1;
// }

CMD:createlicense(playerid, params[])
{
	if(pData[playerid][pFaction] == 1)
	{
		new String[10000], giveplayerid, type;
		if(sscanf(params, "ud", giveplayerid, type))
		{
			SendClientMessageEx(playerid, COLOR_WHITE, "KEGUNAAN: /createlicense [playerid] [type]");
			SendClientMessageEx(playerid, COLOR_GRAD2, "Types: 1 = Weapon, 2 = Trucker, 3 = Lumberjack");
			return 1;
		}

		if(!IsPlayerConnected(giveplayerid))
		{
			SendClientMessageEx(playerid, COLOR_GRAD2, "Invalid player specified.");
			return 1;
		}
		switch(type)
		{
			case 1:
			{
				if(pData[giveplayerid][pGunLic] == 1)
				{
					SendClientMessageEx(playerid, COLOR_GRAD2, "This player already has a Weapon's license.");
					return 1;
				}
				format(String, sizeof(String), "You have given a Weapon license to %s.", ReturnName2(giveplayerid));
				SendClientMessageEx(playerid, COLOR_WHITE, String);
				format(String, sizeof(String), "%s has given you a Weapon license.",ReturnName2(playerid));
				SendClientMessageEx(giveplayerid, COLOR_WHITE, String);
				SendClientMessageEx(giveplayerid, COLOR_ARWIN, "NOTE: "WHITE_E"Your {00FFFF}Weapon license "WHITE_E"is active for "YELLOW_E"3 months");   
				pData[giveplayerid][pGunLic] = 1;
				pData[giveplayerid][pGunLicTime] = gettime() + (91 * 86400);
				return 1;
			}
			case 2:
			{
				if(pData[giveplayerid][pTruckerLic] == 1)
				{
					SendClientMessageEx(playerid, COLOR_GRAD2, "This player already has a Trucking license.");
					return 1;
				}
				format(String, sizeof(String), "You have given a Trucking license to %s.",ReturnName2(giveplayerid));
				SendClientMessageEx(playerid, COLOR_WHITE, String);
				format(String, sizeof(String), "%s has given you a Trucking license.",ReturnName2(playerid));
				SendClientMessageEx(giveplayerid, COLOR_WHITE, String);
				SendClientMessageEx(giveplayerid, COLOR_ARWIN, "NOTE: "WHITE_E"Your {00FFFF}Trucking license "WHITE_E"is active for "YELLOW_E"3 months");   
				pData[giveplayerid][pTruckerLic] = 1;
				pData[giveplayerid][pTruckerLicTime] = gettime() + (91 * 86400);
				return 1;
			}
			case 3:
			{
				if(pData[giveplayerid][pLumberLic] == 1)
				{
					SendClientMessageEx(playerid, COLOR_GRAD2, "This player already has a Lumberjack license.");
					return 1;
				}
				format(String, sizeof(String), "You have given a Lumberjack license to %s.",ReturnName2(giveplayerid));
				SendClientMessageEx(playerid, COLOR_WHITE, String);
				format(String, sizeof(String), "%s has given you a Lumberjack license.",ReturnName2(playerid));
				SendClientMessageEx(giveplayerid, COLOR_ARWIN, "NOTE: "WHITE_E"Your {00FFFF}Lumberjack license "WHITE_E"is active for "YELLOW_E"3 months");   
				SendClientMessageEx(giveplayerid, COLOR_WHITE, String);
				pData[giveplayerid][pLumberLic] = 1;
				pData[giveplayerid][pLumberLicTime] = gettime() + (91 * 86400);
				return 1;
			}
			default:
			{
				SendClientMessageEx(playerid, COLOR_WHITE, "Invalid license type! /createlicense [playerid] [type]");
				SendClientMessageEx(playerid, COLOR_GRAD2, "Types: 1 = Weapon, 2 = Trucker, 3 = Lumberjack");
			}
		}
	}
	return 1;
}

CMD:destroyflare(playerid, params[])
{
	if(pData[playerid][pFaction] != 1)
        return Error(playerid, "You must be a police officer.");
		
	if(IsValidDynamicObject(pData[playerid][pFlare]))
		DestroyDynamicObject(pData[playerid][pFlare]);
	SendClientMessageEx(playerid, COLOR_ARWIN, "FLARE: "WHITE_E"Your flare is deleted.");
	return 1;
}

alias:detain("undetain")
CMD:detain(playerid, params[])
{
    new vehicleid = GetNearestVehicleToPlayer(playerid, 3.0, false), otherid;

    if(pData[playerid][pFaction] != 1)
        return Error(playerid, "You must be a police officer.");
	
    if(sscanf(params, "u", otherid))
        return Usage(playerid, "/detain [playerid/PartOfName]");

    if(otherid == INVALID_PLAYER_ID)
        return Error(playerid, "That player is disconnected.");

    if(otherid == playerid)
        return Error(playerid, "You cannot detained yourself.");

    if(!NearPlayer(playerid, otherid, 5.0))
        return Error(playerid, "You must be near this player.");

    if(!pData[otherid][pCuffed])
        return Error(playerid, "The player is not cuffed at the moment.");

    if(vehicleid == INVALID_VEHICLE_ID)
        return Error(playerid, "You are not near any vehicle.");

    if(GetVehicleMaxSeats(vehicleid) < 2)
        return Error(playerid, "You can't detain that player in this vehicle.");

    if(IsPlayerInVehicle(otherid, vehicleid))
    {
        TogglePlayerControllable(otherid, 1);

        RemoveFromVehicle(otherid);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "%s opens the door and pulls %s out the vehicle.", ReturnName2(playerid), ReturnName2(otherid));
    }
    else
    {
        new seatid = GetAvailableSeat(vehicleid, 2);

        if(seatid == -1)
            return Error(playerid, "There are no more seats remaining.");

        new
            string[64];

        format(string, sizeof(string), "You've been ~r~detained~w~ by %s.", ReturnName2(playerid));
        TogglePlayerControllable(otherid, 0);

        //StopDragging(otherid);
        PutPlayerInVehicle(otherid, vehicleid, seatid);

        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "%s opens the door and places %s into the vehicle.", ReturnName2(playerid), ReturnName2(otherid));
        InfoTD_MSG(otherid, 3500, string);
    }
    return 1;
}

CMD:cuff(playerid, params[])
{
	if(pData[playerid][pFaction] == 1 || pData[playerid][pFaction] == 2)
	{
		if(!pData[playerid][pOnDuty])
			return Error(playerid, "You must on duty to use cuff.");
		
		new otherid;
		if(sscanf(params, "u", otherid))
			return Usage(playerid, "/cuff [playerid/PartOfName]");

		if(otherid == INVALID_PLAYER_ID)
			return Error(playerid, "That player is disconnected.");

		if(otherid == playerid)
			return Error(playerid, "You cannot handcuff yourself.");

		if(!NearPlayer(playerid, otherid, 5.0))
			return Error(playerid, "You must be near this player.");

		if(GetPlayerState(otherid) != PLAYER_STATE_ONFOOT)
			return Error(playerid, "The player must be onfoot before you can cuff them.");

		if(pData[otherid][pCuffed])
			return Error(playerid, "The player is already cuffed at the moment.");

		pData[otherid][pCuffed] = 1;
		SetPlayerSpecialAction(otherid, SPECIAL_ACTION_CUFFED);
		SetPlayerAttachedObject(otherid, A_OBJECT_SLOT_HAND, 19418, A_OBJECT_BONE_RIGHT_HAND, -0.011, 0.028, -0.022, -15.600012, -33.699977, -81.700035, 0.891999, 1.00, 1.168);

		new mstr[128];
		format(mstr, sizeof(mstr), "CUFF: "WHITE_E" You have been cuffed by "BLUE_E"%s", ReturnName2(otherid));
		SendClientMessage(playerid, COLOR_ARWIN, mstr);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s tightens a pair of handcuffs on %s's wrists.", ReturnName2(playerid), ReturnName2(otherid));
	}
	else
	{
		return Error(playerid, "You not police/gov.");
	}
    return 1;
}

CMD:uncuff(playerid, params[])
{
	if(pData[playerid][pFaction] == 1 || pData[playerid][pFaction] == 2)
	{
	
		if(!pData[playerid][pOnDuty])
			return Error(playerid, "You must on duty to use cuff.");
		
		new otherid;
		if(sscanf(params, "u", otherid))
			return Usage(playerid, "/uncuff [playerid/PartOfName]");

		if(otherid == INVALID_PLAYER_ID)
			return Error(playerid, "That player is disconnected.");

		if(otherid == playerid)
			return Error(playerid, "You cannot uncuff yourself.");

		if(!NearPlayer(playerid, otherid, 5.0))
			return Error(playerid, "You must be near this player.");

		if(!pData[otherid][pCuffed])
			return Error(playerid, "The player is not cuffed at the moment.");

		static
			string[64];

		pData[otherid][pCuffed] = 0;
		SetPlayerSpecialAction(otherid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(otherid, A_OBJECT_SLOT_HAND);
		
		format(string, sizeof(string), "You've been ~g~uncuffed~w~ by %s.", ReturnName2(playerid));
		InfoTD_MSG(otherid, 3500, string);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s loosens the pair of handcuffs on %s's wrists.", ReturnName2(playerid), ReturnName2(otherid));
	}
	else
	{
		return Error(playerid, "You not police/gov.");
	}
    return 1;
}

CMD:blskit(playerid, params[])
{
	if(pData[playerid][pFaction] != 1)
        return Error(playerid, "You must be a sapd officer.");

	new otherid;
	if(sscanf(params, "u", otherid))
        return Usage(playerid, "/blskit [playerid/PartOfName]");

    if(otherid == INVALID_PLAYER_ID || !NearPlayer(playerid, otherid, 5.0))
        return Error(playerid, "That player is disconnected or not near you.");

    if(otherid == playerid)
        return Error(playerid, "You can't bls yourself.");

    if(!pData[otherid][pInjured])
        return Error(playerid, "That player is not injured.");
	
	SetPlayerHealthEx(otherid, 15.0);
	TextDrawHideForPlayer(playerid, injuredtextdraw);
    pData[otherid][pInjured] = 0;
	pData[otherid][pHospital] = 0;
	pData[otherid][pSick] = 0;
    ClearAnimations(otherid);
    TogglePlayerControllable(otherid, 1);
	
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s has rescue %s with bls kit.", ReturnName2(playerid), ReturnName2(otherid));
    SamdInfo(otherid, "Officer %s has rescue your character.", ReturnName2(playerid));
	return 1;
}

CMD:release(playerid, params[])
{
	if(pData[playerid][pFaction] != 1)
        return Error(playerid, "You must be a police officer.");
	
	new arrestid = GetClosestArrest(playerid);
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, DynArrest[arrestid][arrestPos][0], DynArrest[arrestid][arrestPos][1], DynArrest[arrestid][arrestPos][2]))
		return Error(playerid, "You must be near an arrest point.");

	new otherid;
	if(sscanf(params, "u", otherid))
	{
	    Usage(playerid, "/release <ID/Name>");
	    return true;
	}

    if(otherid == INVALID_PLAYER_ID)
        return Error(playerid, "Player not connected!");
	
	if(pData[otherid][pArrest] == 0)
	    return Error(playerid, "The player isn't in arrest!");

	pData[otherid][pArrest] = 0;
	pData[otherid][pArrestTime] = 0;
	SetPlayerInterior(otherid, 0);
	PlayerTextDrawHide(otherid, JailTD[otherid]);
	SetPlayerVirtualWorld(otherid, 0);
	SetPlayerPositionEx(otherid, 1526.69, -1678.05, 5.89, 267.76, 2000);
	SetPlayerSpecialAction(otherid, SPECIAL_ACTION_NONE);

	SendFactionMessage(1, COLOR_BLUE, ""BLUE_E"PRISON: "BLUE_E"Officer "YELLOW_E"%s "BLUE_E"telah membebaskan "RED_E"%s "BLUE_E"dari penjara.", ReturnName2(playerid), ReturnName2(otherid));
	return true;
}

CMD:arrest(playerid, params[])
{
    static
        denda[52],
		totalcash[52],
        time,
		otherid,
		reason[128];

    if(pData[playerid][pFaction] != 1) return Error(playerid, "You must be a police officer.");
	new arrestid = GetClosestArrest(playerid);
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, DynArrest[arrestid][arrestPos][0], DynArrest[arrestid][arrestPos][1], DynArrest[arrestid][arrestPos][2]))
		return Error(playerid, "You must be near an arrest point.");

    if(sscanf(params, "uds[52]s[128]", otherid, time, denda, reason)) return Usage(playerid, "/arrest [playerid/PartOfName] [minutes] [fine] [reason]");
    if(otherid == INVALID_PLAYER_ID || !NearPlayer(playerid, otherid, 5.0)) return Error(playerid, "The player is disconnected or not near you.");	
    if(time < 1 || time > 300) return Error(playerid, "The specified time can't be below 1 or above 120.");

	format(totalcash, sizeof(totalcash), "%d00", strval(denda));
	GivePlayerMoneyEx(otherid, -strval(totalcash));
    pData[otherid][pArrest] = 1;
    pData[otherid][pArrestTime] = time * 60;
	
	SetPlayerArrest(otherid);
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO arrestrecord(owner, reason, issued, date, fine) VALUES ('%d', '%s', '%s', CURRENT_TIMESTAMP(), '%d')", pData[otherid][pID], reason, ReturnName(playerid), strval(totalcash));
	mysql_tquery(g_SQL, query);
    SendFactionMessage( 1, COLOR_BLUE, ""BLUE_E"ARREST: "RED_E"%s "YELLOW_E"has been arrested by "BLUE_E"%s "RED_E"%d "YELLOW_E"days with fine "GREEN_E"$%s", ReturnName2(otherid), ReturnName2(playerid), time, FormatMoney(strval(totalcash)));
    return 1;
}

CMD:checkveh(playerid, params[])
{
	if(pData[playerid][pFaction] != 1)
		if(pData[playerid][pAdmin] < 1)
			return Error(playerid, "You must be a sapd officer.");
		
	static carid = -1;
	new vehicleid = GetNearestVehicleToPlayer(playerid, 3.0, false);

	if(vehicleid == INVALID_VEHICLE_ID || !IsValidVehicle(vehicleid))
		return Error(playerid, "You not in near any vehicles.");
	
	if((carid = Vehicle_Nearest(playerid)) != -1)
	{
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "SELECT username FROM players WHERE reg_id='%d'", pvData[carid][cOwner]);
		mysql_query(g_SQL, query);
		new rows = cache_num_rows();
		if(rows) 
		{
			new owner[32];
			cache_get_value_index(0, 0, owner);
			
			if(strcmp(pvData[carid][cPlate], "NoHave"))
			{
				SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"ID: %d | Model: %s | Owner: %s | Plate: %s | Plate Time: %s", vehicleid, GetVehicleName(vehicleid), owner, pvData[carid][cPlate], experieddate(pvData[carid][cPlateTime],1));
			}
			else
			{
				SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"ID: %d | Model: %s | Owner: %s | Plate: None | Plate Time: None", vehicleid, GetVehicleName(vehicleid), owner);
			}
		}
		else
		{
			Error(playerid, "This vehicle no owned found!");
			return 1;
		}
	}
	else
	{
		Error(playerid, "You are not in near owned private vehicle.");
		return 1;
	}	
	return 1;
}

CMD:take(playerid, params[])
{
    if(pData[playerid][pFaction] != 1)
        return Error(playerid, "You must be a sapd officer.");
	if(pData[playerid][pFactionRank] < 1)
		return Error(playerid, "You must be 1 rank level!");
	if(IsPlayerConnected(playerid))
	{
		new name[24], otherid;
        if(sscanf(params, "us[24]", otherid, name))
		{
			Usage(playerid, "/take [playerid] [name]");
			Info(playerid, "Names: pot, crack, material, weapon");
			return 1;
		}
		if(otherid == INVALID_PLAYER_ID || otherid == playerid || !NearPlayer(playerid, otherid, 3.0))
			return Error(playerid, "Invalid playerid!");

		if(strcmp(name,"pot",true) == 0)
		{
			if(pData[otherid][pPot] < 1)
				return Error(playerid, "Players don't have pots");

			pData[otherid][pPot] = 0;
			SendClientMessageEx(playerid, COLOR_ARWIN, "TAKE: "WHITE_E"You managed to take all the pots belonging to %s", ReturnName2(otherid));
			SendClientMessageEx(otherid, COLOR_ARWIN, "TAKE: "WHITE_E"%s managed to take all your pots", ReturnName2(playerid));
		}
        else if(strcmp(name,"crack",true) == 0)
		{
			if(pData[otherid][pCrack] < 1)
				return Error(playerid, "Players don't have crack");

			pData[otherid][pCrack] = 0;
			SendClientMessageEx(playerid, COLOR_ARWIN, "TAKE: "WHITE_E"You managed to take all the crack belonging to %s", ReturnName2(otherid));
			SendClientMessageEx(otherid, COLOR_ARWIN, "TAKE: "WHITE_E"%s managed to take all your crack", ReturnName2(playerid));
		}
        else if(strcmp(name,"material",true) == 0)
		{
			if(pData[otherid][pMaterial] < 1)
				return Error(playerid, "Players don't have crack");

			pData[otherid][pMaterial] = 0;
			SendClientMessageEx(playerid, COLOR_ARWIN, "TAKE: "WHITE_E"You managed to take all the material belonging to %s", ReturnName2(otherid));
			SendClientMessageEx(otherid, COLOR_ARWIN, "TAKE: "WHITE_E"%s managed to take all your material", ReturnName2(playerid));
		}
		else if(strcmp(name,"weapon",true) == 0)
		{
			ResetWeapons(otherid);
			SendClientMessageEx(playerid, COLOR_ARWIN, "TAKE: "WHITE_E"You take %s's weapon", ReturnName2(otherid));
        	SendClientMessageEx(otherid, COLOR_ARWIN, "TAKE: "WHITE_E"%s picks up your weapon", ReturnName2(playerid));
		}
	}
	return 1;
}

CMD:revoke(playerid, params[])
{
    if(pData[playerid][pFaction] != 1)
        return Error(playerid, "You must be a sapd officer.");
	if(pData[playerid][pFactionRank] < 1)
		return Error(playerid, "You must be 1 rank level!");
	if(IsPlayerConnected(playerid))
	{
		new name[24], otherid;
        if(sscanf(params, "us[24]d", otherid, name))
		{
			Usage(playerid, "/revoke [playerid] [name]");
			Info(playerid, "Names: weapon, trucker, boat, driver, lumber, flying, schematic");
			return 1;
		}
		if(otherid == INVALID_PLAYER_ID || otherid == playerid || !NearPlayer(playerid, otherid, 3.0))
			return Error(playerid, "Invalid playerid!");

		if(strcmp(name,"weapon",true) == 0)
		{
			if(pData[otherid][pGunLic] < 1)
				return Error(playerid, "The player does not have a license");

			pData[otherid][pGunLicTime] = 0;
			pData[otherid][pGunLic] = 0;

			SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"You've revoked a "AQUA_E"Weapon License "WHITE_E"from "YELLOW_E"%s", ReturnName2(otherid));
			SendClientMessageEx(otherid, COLOR_ARWIN, "LICENSE: "YELLOW_E"%s "WHITE_E"revoked your "AQUA_E"Weapon License", ReturnName2(playerid));
		}
        else if(strcmp(name,"trucker",true) == 0)
		{
			if(pData[otherid][pTruckerLic] < 1)
				return Error(playerid, "The player does not have a license");

			pData[otherid][pTruckerLicTime] = 0;
			pData[otherid][pTruckerLic] = 0;
			SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"You've revoked a "AQUA_E"Truck License "WHITE_E"from "YELLOW_E"%s", ReturnName2(otherid));
			SendClientMessageEx(otherid, COLOR_ARWIN, "LICENSE: "YELLOW_E"%s "WHITE_E"revoked your "AQUA_E"Truck License", ReturnName2(playerid));
		}
        else if(strcmp(name,"boat",true) == 0)
		{
			if(pData[otherid][pBoatLic] < 1)
				return Error(playerid, "The player does not have a license");

			pData[otherid][pBoatLicTime] = 0;
			pData[otherid][pBoatLic] = 0;
			SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"You've revoked a "AQUA_E"Boat License "WHITE_E"from "YELLOW_E"%s", ReturnName2(otherid));
			SendClientMessageEx(otherid, COLOR_ARWIN, "LICENSE: "YELLOW_E"%s "WHITE_E"revoked your "AQUA_E"Boat License", ReturnName2(playerid));
		}
        else if(strcmp(name,"driver",true) == 0)
		{
			if(pData[otherid][pDriveLic] < 1)
				return Error(playerid, "The player does not have a license");

			pData[otherid][pDriveLicTime] = 0;
			pData[otherid][pDriveLic] = 0;

			SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"You've revoked a "AQUA_E"Driver License "WHITE_E"from "YELLOW_E"%s", ReturnName2(otherid));
			SendClientMessageEx(otherid, COLOR_ARWIN, "LICENSE: "YELLOW_E"%s "WHITE_E"revokes your "AQUA_E"Driver License", ReturnName2(playerid));
		}
        else if(strcmp(name,"lumber",true) == 0)
		{
			if(pData[otherid][pLumberLic] < 1)
				return Error(playerid, "The player does not have a license");

			pData[otherid][pLumberLicTime] = 0;
			pData[otherid][pLumberLic] = 0;
			SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"You've revoked a "AQUA_E"Lumber License "WHITE_E"from "YELLOW_E"%s", ReturnName2(otherid));
			SendClientMessageEx(otherid, COLOR_ARWIN, "LICENSE: "YELLOW_E"%s "WHITE_E"revokes your "AQUA_E"Lumber License", ReturnName2(playerid));

		}
        else if(strcmp(name,"flying",true) == 0)
		{
			if(pData[otherid][pFlyLic] < 1)
				return Error(playerid, "The player does not have a license");

			pData[otherid][pFlyLicTime] = 0;
			pData[otherid][pFlyLic] = 0;
			SendClientMessageEx(playerid, COLOR_ARWIN, "REVOKE: "WHITE_E"You revoked %s's license", ReturnName2(otherid));
			SendClientMessageEx(otherid, COLOR_ARWIN, "REVOKE: "WHITE_E"%s revokes your flying license", ReturnName2(playerid));
		}
		else if(strcmp(name,"schematic",true) == 0)
		{
			for (new i = 0; i != 5; i++) {
				pData[otherid][pSchematic][i] = 0;
				SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"You've revoked a "AQUA_E"Gun Schematic "WHITE_E"from "YELLOW_E"%s", ReturnName2(otherid));
				SendClientMessageEx(otherid, COLOR_ARWIN, "LICENSE: "YELLOW_E"%s "WHITE_E"revokes your "AQUA_E"Gun Schematic", ReturnName2(playerid));
			}
		}
	}
	return 1;
}

//SAGS Commands
CMD:sagsonline(playerid, params[])
{
	if(pData[playerid][pFaction] != 2)
        return Error(playerid, "You must be a sags officer.");
	if(pData[playerid][pFactionRank] < 1)
		return Error(playerid, "You must be high rank!");
		
	new duty[16], lstr[1024];
	format(lstr, sizeof(lstr), "Name\tRank\tStatus\tDuty Time\n");
	foreach(new i: Player)
	{
		if(pData[i][pFaction] == 2)
		{
			switch(pData[i][pOnDuty])
			{
				case 0:
				{
					duty = "Off Duty";
				}
				case 1:
				{
					duty = ""BLUE_E"On Duty";
				}
			}
			format(lstr, sizeof(lstr), "%s%s(%d)\t%s(%d)\t%s\t%d minute", lstr, ReturnName2(i), i, pData[i][pFactionRankName], pData[i][pFactionRank], duty, pData[i][pOnDutyTime]/10);
			format(lstr, sizeof(lstr), "%s\n", lstr);
		}
	}
	format(lstr, sizeof(lstr), "%s\n", lstr);
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "SAGS Online", lstr, "Close", "");
	return 1;
}

//SAMD Commands
CMD:loadinjured(playerid, params[])
{
    static
        seatid,
		otherid;

    if(pData[playerid][pFaction] != 3)
        return Error(playerid, "You must be part of a medical faction.");

    if(sscanf(params, "u", otherid))
        return Usage(playerid, "/loadinjured [playerid/PartOfName]");

    if(otherid == INVALID_PLAYER_ID || !NearPlayer(playerid, otherid, 10.0))
        return Error(playerid, "That player is disconnected or not near you.");

    if(otherid == playerid)
        return Error(playerid, "You can't load yourself into an ambulance.");

    if(!pData[otherid][pInjured])
        return Error(playerid, "That player is not injured.");
	
	if(!IsPlayerInAnyVehicle(playerid))
	{
	    Error(playerid, "You must be in a Ambulance to load patient!");
	    return true;
	}
		
	new i = GetPlayerVehicleID(playerid);
    if(GetVehicleModel(i) == 416)
    {
        seatid = GetAvailableSeat(i, 2);

        if(seatid == -1)
            return Error(playerid, "There is no room for the patient.");

        ClearAnimations(otherid);
        pData[otherid][pInjured] = 2;

        PutPlayerInVehicle(otherid, i, seatid);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s opens up the ambulance and loads %s on the stretcher.", ReturnName2(playerid), ReturnName2(otherid));

        TogglePlayerControllable(otherid, 0);
        SetPlayerHealth(otherid, 100.0);
		TextDrawHideForPlayer(playerid, injuredtextdraw);
        SamdInfo(otherid, "You're injurednow you're on ambulance.");
        return 1;
    }
    else Error(playerid, "You must be in an ambulance.");
    return 1;
}

CMD:dropinjured(playerid, params[])
{

    if(pData[playerid][pFaction] != 3)
        return Error(playerid, "You must be part of a medical faction.");
	new otherid;
    if(sscanf(params, "u", otherid))
        return Usage(playerid, "/dropinjured [playerid/PartOfName]");

    if(otherid == INVALID_PLAYER_ID || !IsPlayerInVehicle(playerid, GetPlayerVehicleID(playerid)))
        return Error(playerid, "That player is disconnected or not near you.");

    if(otherid == playerid)
        return Error(playerid, "You can't deliver yourself to the hospital.");

    if(pData[otherid][pInjured] != 2)
        return Error(playerid, "That player is not injured.");

    if(IsPlayerInRangeOfPoint(playerid, 5.0, 1142.38, -1330.74, 13.62))
    {
		RemovePlayerFromVehicle(otherid);
		pData[otherid][pHospital] = 1;
		pData[otherid][pHospitalTime] = 0;
		pData[otherid][pInjured] = 1;
		ResetWeapons(otherid);
		TextDrawHideForPlayer(playerid, injuredtextdraw);
        SamdInfo(playerid, "You have delivered %s to the hospital.", ReturnName2(otherid));
        SamdInfo(otherid, "You have recovered at the nearest hospital by officer %s.", ReturnName2(playerid));
    }
    else Error(playerid, "You must be near a hospital deliver location.");
    return 1;
}

CMD:samdonline(playerid, params[])
{
	if(pData[playerid][pFaction] != 3)
        return Error(playerid, "You must be a samd officer.");
	if(pData[playerid][pFactionRank] < 1)
		return Error(playerid, "You must be high rank!");
		
	new duty[16], lstr[1024];
	format(lstr, sizeof(lstr), "Name\tRank\tStatus\tDuty Time\n");
	foreach(new i: Player)
	{
		if(pData[i][pFaction] == 3)
		{
			switch(pData[i][pOnDuty])
			{
				case 0:
				{
					duty = "Off Duty";
				}
				case 1:
				{
					duty = ""BLUE_E"On Duty";
				}
			}
			format(lstr, sizeof(lstr), "%s%s(%d)\t%s(%d)\t%s\t%d minute", lstr, ReturnName2(i), i, pData[i][pFactionRankName], pData[i][pFactionRank], duty, pData[i][pOnDutyTime]/10);
			format(lstr, sizeof(lstr), "%s\n", lstr);
		}
	}
	format(lstr, sizeof(lstr), "%s\n", lstr);
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "SAMD Online", lstr, "Close", "");
	return 1;
}

CMD:ems(playerid, params[])
{
	if(pData[playerid][pFaction] != 3)
        return Error(playerid, "You must be a samd officer.");
	
	foreach(new ii : Player)
	{
		if(pData[ii][pInjured])
		{
			SendClientMessageEx(playerid, COLOR_PINK2, "EMS Player: "WHITE_E"%s(id: %d)", ReturnName2(ii), ii);
		}
	}
	SamdInfo(playerid, "/findems [id] to search injured player!");
	return 1;
}

CMD:findems(playerid, params[])
{
	if(pData[playerid][pFaction] != 3)
        return Error(playerid, "You must be a samd officer.");
		
	new otherid;
	if(sscanf(params, "u", otherid))
        return Usage(playerid, "/findems [playerid/PartOfName]");
	
	if(!IsPlayerConnected(otherid)) return Error(playerid, "Player is not connected");
	
	if(otherid == playerid)
        return Error(playerid, "You can't find yourself.");
	
	if(!pData[otherid][pInjured]) return Error(playerid, "You can't find a player that's not injured.");
	
	new Float:x, Float:y, Float:z;
	GetPlayerPos(otherid, x, y, z);
	SetPlayerCheckpoint(playerid, x, y, x, 4.0);
	pData[playerid][pFindEms] = otherid;
	SamdInfo(otherid, "Officer %s sedang menuju ke lokasi anda. harap tunggu!", ReturnName2(playerid));
	return 1;
}

CMD:rescue(playerid, params[])
{
	if(pData[playerid][pFaction] != 3)
        return Error(playerid, "You must be a samd officer.");
	
	if(pData[playerid][pMedkit] < 1) return Error(playerid, "You need medkit.");
	new otherid;
	if(sscanf(params, "u", otherid))
        return Usage(playerid, "/rescue [playerid/PartOfName]");

    if(otherid == INVALID_PLAYER_ID || !NearPlayer(playerid, otherid, 5.0))
        return Error(playerid, "That player is disconnected or not near you.");

    if(otherid == playerid)
        return Error(playerid, "You can't rescue yourself.");

    if(!pData[otherid][pInjured])
        return Error(playerid, "That player is not injured.");
	
	pData[playerid][pMedkit]--;
	
	SetPlayerHealthEx(otherid, 50.0);
	TextDrawHideForPlayer(playerid, injuredtextdraw);
    pData[otherid][pInjured] = 0;
	pData[otherid][pHospital] = 0;
	pData[otherid][pSick] = 0;
    ClearAnimations(otherid);
    TogglePlayerControllable(otherid, 1);
	new getime[3];
	gettime(getime[0], getime[1], getime[2]);
	SetPlayerTime(otherid, getime[0], getime[1]);
	SetPlayerWeather(otherid, current_weather);
	
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s has rescuered %s with medkit tools.", ReturnName2(playerid), ReturnName2(otherid));
    SamdInfo(otherid, "Officer %s has rescue your character.", ReturnName2(playerid));
	return 1;
}

CMD:treatment(playerid, params[])
{
	if(pData[playerid][pFaction] != 3)
        return Error(playerid, "You must be a samd officer.");

	if(pData[playerid][pMedkit] < 1) return Error(playerid, "You need medkit.");
	new otherid;
	if(sscanf(params, "u", otherid))
        return Usage(playerid, "/treatment [playerid/PartOfName]");

    if(otherid == INVALID_PLAYER_ID || !NearPlayer(playerid, otherid, 5.0))
        return Error(playerid, "That player is disconnected or not near you.");

    if(otherid == playerid)
        return Error(playerid, "You can't treatment yourself.");
	
	if(pData[playerid][pActivity] != 0)
		return Error(playerid, "You are already doing an activity.");

	pData[playerid][pActivity] = 1;
	pData[playerid][pActivityTime] = 0;
	pData[playerid][pTreatTarget] = otherid;
	
	PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Treating Patient");
	for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
	
	ApplyAnimation(playerid, "MEDIC", "CPR", 4.1, 0, 0, 0, 1, 0, 1);
	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s starts treating %s with a medkit.", ReturnName2(playerid), ReturnName2(otherid));
	SamdInfo(otherid, "Officer %s is treating your character, please stand still.", ReturnName2(playerid));
	return 1;
}

//SANEW Commands
CMD:sanaonline(playerid, params[])
{
	if(pData[playerid][pFaction] != 4)
        return Error(playerid, "You must be a sanew officer.");
	if(pData[playerid][pFactionRank] < 1)
		return Error(playerid, "You must be high rank!");
		
	new duty[16], lstr[1024];
	format(lstr, sizeof(lstr), "Name\tRank\tStatus\tDuty Time\n");
	foreach(new i: Player)
	{
		if(pData[i][pFaction] == 4)
		{
			switch(pData[i][pOnDuty])
			{
				case 0:
				{
					duty = "Off Duty";
				}
				case 1:
				{
					duty = ""BLUE_E"On Duty";
				}
			}
			format(lstr, sizeof(lstr), "%s%s(%d)\t%s(%d)\t%s\t%d minute", lstr, ReturnName2(i), i, pData[i][pFactionRankName], pData[i][pFactionRank], duty, pData[i][pOnDutyTime]/10);
			format(lstr, sizeof(lstr), "%s\n", lstr);
		}
	}
	format(lstr, sizeof(lstr), "%s\n", lstr);
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "SANA Online", lstr, "Close", "");
	return 1;
}

CMD:broadcast(playerid, params[])
{
    if(pData[playerid][pFaction] != 4)
        return Error(playerid, "You must be part of a news faction.");

    //if(!IsSANEWCar(GetPlayerVehicleID(playerid)) || !IsPlayerInRangeOfPoint(playerid, 5, 255.63, 1757.39, 701.09))
    //    return Error(playerid, "You must be inside a news van or chopper or in sanew studio.");

    if(!pData[playerid][pBroadcast])
    {
        pData[playerid][pBroadcast] = true;

        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s has started a news broadcast.", ReturnName2(playerid));
        Servers(playerid, "You have started a news broadcast (use \"/bc [broadcast text]\" to broadcast).");
    }
    else
    {
        pData[playerid][pBroadcast] = false;

        foreach (new i : Player) if(pData[i][pNewsGuest] == playerid) 
		{
            pData[i][pNewsGuest] = INVALID_PLAYER_ID;
        }
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s has stopped a news broadcast.", ReturnName2(playerid));
        Servers(playerid, "You have stopped the news broadcast.");
    }
    return 1;
}


CMD:bc(playerid, params[])
{
    if(pData[playerid][pFaction] != 4)
        return Error(playerid, "You must be part of a news faction.");

    if(isnull(params))
        return Usage(playerid, "/bc [broadcast text]");

    //if(!IsSANEWCar(GetPlayerVehicleID(playerid)) || !IsPlayerInRangeOfPoint(playerid, 5, 255.63, 1757.39, 701.09))
    //    return Error(playerid, "You must be inside a news van or chopper or in sanew studio.");

    if(!pData[playerid][pBroadcast])
        return Error(playerid, "You must be broadcasting to use this command.");

    if(strlen(params) > 64) {
        foreach (new i : Player) /*if(!pData[i][pDisableBC])*/ {
            SendClientMessageEx(i, COLOR_ORANGE, "[SANA] Reporter %s: %.64s", ReturnName2(playerid), params);
            SendClientMessageEx(i, COLOR_ORANGE, "...%s", params[64]);
        }
    }
    else {
        foreach (new i : Player) /*if(!pData[i][pDisableBC])*/ {
            SendClientMessageEx(i, COLOR_ORANGE, "[SANA] Reporter %s: %s", ReturnName2(playerid), params);
        }
    }
    return 1;
}

CMD:live(playerid, params[])
{
    static
        livechat[128];
        
    if(sscanf(params, "s[128]", livechat))
        return Usage(playerid, "/live [live chat]");

    if(pData[playerid][pNewsGuest] == INVALID_PLAYER_ID)
        return Error(playerid, "You're now invite by sanew member to live!");

	foreach (new i : Player) /*if(!pData[i][pDisableBC])*/ {
		SendClientMessageEx(i, COLOR_ORANGE, "SANA: Guest %s: %s", ReturnName2(playerid), livechat);
	}
    return 1;
}

CMD:inviteguest(playerid, params[])
{
    if(pData[playerid][pFaction] != 4)
        return Error(playerid, "You must be part of a news faction.");
		
	new otherid;
    if(sscanf(params, "u", otherid))
        return Usage(playerid, "/inviteguest [playerid/PartOfName]");

    if(!pData[playerid][pBroadcast])
        return Error(playerid, "You must be broadcasting to use this command.");

    if(otherid == INVALID_PLAYER_ID || !NearPlayer(playerid, otherid, 5.0))
        return Error(playerid, "That player is disconnected or not near you.");

    if(otherid == playerid)
        return Error(playerid, "You can't add yourself as a guest.");

    if(pData[otherid][pNewsGuest] == playerid)
        return Error(playerid, "That player is already a guest of your broadcast.");

    if(pData[otherid][pNewsGuest] != INVALID_PLAYER_ID)
        return Error(playerid, "That player is already a guest of another broadcast.");

    pData[otherid][pNewsGuest] = playerid;

    Info(playerid, "You have added %s as a broadcast guest.", ReturnName2(otherid));
    Info(otherid, "%s has added you as a broadcast guest ((/live to start broadcast)).", ReturnName2(otherid));
    return 1;
}

CMD:removeguest(playerid, params[])
{

    if(pData[playerid][pFaction] != 4)
        return Error(playerid, "You must be part of a news faction.");
	new otherid;
    if(sscanf(params, "u", otherid))
        return Usage(playerid, "/removeguest [playerid/PartOfName]");

    if(!pData[playerid][pBroadcast])
        return Error(playerid, "You must be broadcasting to use this command.");

    if(otherid == INVALID_PLAYER_ID || !NearPlayer(playerid, otherid, 5.0))
        return Error(playerid, "That player is disconnected or not near you.");

    if(otherid == playerid)
        return Error(playerid, "You can't remove yourself as a guest.");

    if(pData[otherid][pNewsGuest] != playerid)
        return Error(playerid, "That player is not a guest of your broadcast.");

    pData[otherid][pNewsGuest] = INVALID_PLAYER_ID;

    Info(playerid, "You have removed %s from your broadcast.", ReturnName2(otherid));
    Info(otherid, "%s has removed you from their broadcast.", ReturnName2(otherid));
    return 1;
}

ptask TreatmentProgress[200](playerid) {
	if(pData[playerid][pActivity] != 1) return 1;

	new targetid = pData[playerid][pTreatTarget];
	if(!IsPlayerConnected(targetid) || !NearPlayer(playerid, targetid, 5.0)) {
		pData[playerid][pActivity] = 0;
		pData[playerid][pActivityTime] = 0;
		pData[playerid][pTreatTarget] = INVALID_PLAYER_ID;
		ClearAnimations(playerid, 1);
		HideProgressBar(playerid);
		Error(playerid, "Treatment cancelled - target moved too far.");
		return 1;
	}

	pData[playerid][pActivityTime]++;
	SetProgressBar(playerid, pData[playerid][pActivityTime]);

	if(pData[playerid][pActivityTime] >= 100) {
		pData[playerid][pActivity] = 0;
		pData[playerid][pActivityTime] = 0;
		pData[playerid][pMedkit]--;

		SetPlayerHealthEx(targetid, 100);
		ClearAnimations(playerid, 1);
		HideProgressBar(playerid);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s has treatment %s with medkit.", ReturnName2(playerid), ReturnName2(targetid));
		SamdInfo(targetid, "Officer %s has treatment your character.", ReturnName2(playerid));
		pData[playerid][pTreatTarget] = INVALID_PLAYER_ID;
	}
	return 1;
}

CMD:kickoffsapd(playerid, params[])
{
    if(pData[playerid][pFaction] != 1)
        return Error(playerid, "You must be part of a news faction.");
		
	if(pData[playerid][pFactionRank] < 5)
		return Error(playerid, "You must faction level 5 - 6!");

	new tmp[24];
	if(sscanf(params, "s[24]", tmp))
	{
	    Usage(playerid, "/kickoffpd <Name_Account>");
	    return true;
	}
	new query[512];
    Info(playerid, "Kamu telah mengkick offline player "YELLOW_E"%s", tmp);
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "KickOffPD", "is", playerid, tmp);
	return 1;
}

CMD:kickoffsags(playerid, params[])
{
    if(pData[playerid][pFaction] != 2)
        return Error(playerid, "You must be part of a news faction.");
		
	if(pData[playerid][pFactionRank] < 5)
		return Error(playerid, "You must faction level 5 - 6!");

	new tmp[24];
	if(sscanf(params, "s[24]", tmp))
	{
	    Usage(playerid, "/kickoffsags <Name_Account>");
	    return true;
	}
	new query[512];
    Info(playerid, "Kamu telah mengkick offline player "YELLOW_E"%s", tmp);
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "KickOffSAGS", "is", playerid, tmp);
	return 1;
}

CMD:kickoffsamd(playerid, params[])
{
    if(pData[playerid][pFaction] != 3)
        return Error(playerid, "You must be part of a news faction.");
		
	if(pData[playerid][pFactionRank] < 5)
		return Error(playerid, "You must faction level 5 - 6!");

	new tmp[24];
	if(sscanf(params, "s[24]", tmp))
	{
	    Usage(playerid, "/kickoffsamd <Name_Account>");
	    return true;
	}
	new query[512];
    Info(playerid, "Kamu telah mengkick offline player "YELLOW_E"%s", tmp);
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "KickOffSAMD", "is", playerid, tmp);
	return 1;
}

CMD:kickoffnews(playerid, params[])
{
    if(pData[playerid][pFaction] != 4)
        return Error(playerid, "You must be part of a news faction.");
		
	if(pData[playerid][pFactionRank] < 5)
		return Error(playerid, "You must faction level 5 - 6!");

	new tmp[24];
	if(sscanf(params, "s[24]", tmp))
	{
	    Usage(playerid, "/kickoffnews <Name_Account>");
	    return true;
	}
	new query[512];
    Info(playerid, "Kamu telah mengkick offline player "YELLOW_E"%s", tmp);
	mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE username='%e'", tmp);
	mysql_tquery(g_SQL, query, "KickOffNEWS", "is", playerid, tmp);
	return 1;
}

CMD:segelbiz(playerid, params[])
{
    if(pData[playerid][pFaction] != 2)
        return Error(playerid, "You must be part of a sags faction.");
		
	if(pData[playerid][pFactionRank] < 3)
		return Error(playerid, "You must faction level 3 - 6!");

	foreach(new bid : Bisnis)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]))
		{
			if(bData[bid][bSegel] != 1) return Error(playerid, "Bisnis ini sudah di segel");
			bData[bid][bSegel] = 1;
			Bisnis_Save(bid);
			Bisnis_Refresh(bid);
			SendClientMessageEx(playerid, COLOR_ARWIN, "SAGS: "WHITE_E"You have sealed business "YELLOW_E"ID %d", bid);
			SendFactionMessage(3, COLOR_ARWIN, "SAGS: {00FFFF}%s "WHITE_E"has sealed the "YELLOW_E"ID %d "WHITE_E"business", ReturnName2(playerid), bid);
		}
	}
	return 1;
}

CMD:unsegelbiz(playerid, params[])
{
    if(pData[playerid][pFaction] != 2)
        return Error(playerid, "You must be part of a sags faction.");
		
	if(pData[playerid][pFactionRank] < 3)
		return Error(playerid, "You must faction level 3 - 6!");

	foreach(new bid : Bisnis)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]))
		{
			if(bData[bid][bSegel] != 0) return Error(playerid, "Bisnis ini belum di segel");
			bData[bid][bSegel] = 0;
			Bisnis_Save(bid);
			Bisnis_Refresh(bid);
			SendClientMessageEx(playerid, COLOR_ARWIN, "SAGS: "WHITE_E"You have unsealed the business "YELLOW_E"ID %d", bid);
			SendFactionMessage(3, COLOR_ARWIN, "SAGS: {00FFFF}%s "WHITE_E"has unsealed the "YELLOW_E"ID %d "WHITE_E"business", ReturnName2(playerid), bid);
		}
	}
	return 1;
}

CMD:getphone(playerid, params[])
{
    if(pData[playerid][pFaction] != 1) return Error(playerid, "You not SAPD");
	if (!IsPlayerInAnyVehicle(playerid)) return Error(playerid, "You must be inside a vehicle.");
	if (!IsSAPDCar(GetPlayerVehicleID(playerid), playerid)) return Error(playerid, "You must be inside a police vehicle.");

	new otherid, no;
	if(sscanf(params, "ud", otherid, no))
	{
		Usage(playerid, "/getphone <ID/Name> <phone>");
		return true;
	}

	if(!IsPlayerConnected(otherid))
        return Error(playerid, "Player tidak on!");
    
	foreach(new id : Player)
	{
		if(pData[id][pPhone] == no)
		{
			SendClientMessageEx(playerid, COLOR_ARWIN, "PHONE: "YELLOW_E"The target phone number is %d");
		}
	}
	return true;
}

CMD:tracephone(playerid, params[])
{
	new no;
    if(pData[playerid][pFaction] != 1) return Error(playerid, "You not SAPD");
	if (!IsPlayerInAnyVehicle(playerid)) return Error(playerid, "You must be inside a vehicle.");
	if (!IsSAPDCar(GetPlayerVehicleID(playerid), playerid)) return Error(playerid, "You must be inside a police vehicle.");
	if(sscanf(params, "d", no)) return Usage(playerid, "/tracephone [no phone]");

	foreach(new id : Player)
	{
		if(pData[id][pPhone] == no)
		{
			new Float:pz[3];
			GetPlayerLocationEx(id, pz[0], pz[1], pz[2]);
			SetPlayerGPS(playerid, pz[0], pz[1], pz[2]);
			if(pData[id][pPhoneOff] > 0) return SendClientMessageEx(playerid, COLOR_GREY, "kamu tidak dapat melacaknya karena Handphone tersangka dalam keadaan mati.");
			SendClientMessageEx(playerid, COLOR_ARWIN, "TRACE: "YELLOW_E"The target marker is on your radar.");
		}
	}
	return 1;
}

CMD:traceplate(playerid, params[])
{
	new no[32];
    if(pData[playerid][pFaction] != 1) return Error(playerid, "You not SAPD");
	if (!IsPlayerInAnyVehicle(playerid)) return Error(playerid, "You must be inside a vehicle.");
	if (!IsSAPDCar(GetPlayerVehicleID(playerid), playerid)) return Error(playerid, "You must be inside a police vehicle.");
	if(sscanf(params, "s[32]", no)) return Usage(playerid, "/traceplate [plate]");

	foreach(new id : PVehicles)
	{
		if(strcmp(pvData[id][cPlate], no))
		{
			new Float:pz[3];
			GetVehiclePos(pvData[id][cVeh], pz[0], pz[1], pz[2]);
			SetPlayerGPS(playerid, pz[0], pz[1], pz[2]);
			SendClientMessageEx(playerid, COLOR_ARWIN, "TRACE: "YELLOW_E"The target marker is on your radar.");
		}
	}
	return 1;
}

// /family - Melihat daftar family (badside) yang online di kota
CMD:family(playerid, params[])
{
    new string[4096];
    new found = 0;

    format(string, sizeof(string), ""WHITE_E"[Badside Online]\n\n");

    foreach(new fid : FAMILYS)
    {
        new memberCount = 0;
        new memberStr[2048];
        new isFirst = 1;

        foreach(new i : Player)
        {
            if(pData[i][pFamily] == fid)
            {
                memberCount++;
                if(isFirst)
                {
                    format(memberStr, sizeof(memberStr), "%s%s (ID:%d)", ReturnName2(i), i);
                    isFirst = 0;
                }
                else
                {
                    format(memberStr, sizeof(memberStr), "%s, %s (ID:%d)", memberStr, ReturnName2(i), i);
                }
            }
        }

        if(memberCount > 0)
        {
            format(string, sizeof(string), "%s\n"YELLOW_E"%s "WHITE_E"[%d member]: "GREY_E"%s", string, fData[fid][fName], memberCount, memberStr);
            found++;
        }
    }

    if(found == 0)
        return SendClientMessageEx(playerid, COLOR_ARWIN, "INFO: "WHITE_E"Tidak ada badside (family) yang online saat ini.");

    format(string, sizeof(string), "%s\n\n"GREY_E"Total badside family online: %d", string, found);
    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Badside Online", string, "Close", "");
    return 1;
}

// /flist - Melihat daftar faction (goodside) yang online di kota
CMD:flist(playerid, params[])
{
    new string[4096];
    new found = 0;
    new factionNames[][] = {
        "SAPD",
        "SAGS",
        "SAMD",
        "SANA"
    };

    format(string, sizeof(string), ""WHITE_E"[Goodside Online]\n\n");

    for(new fid = 1; fid <= 4; fid++)
    {
        new memberCount = 0;
        new memberStr[2048];
        new isFirst = 1;

        foreach(new i : Player)
        {
            if(pData[i][pFaction] == fid)
            {
                memberCount++;
                if(isFirst)
                {
                    format(memberStr, sizeof(memberStr), "%s%s (ID:%d)", ReturnName2(i), i);
                    isFirst = 0;
                }
                else
                {
                    format(memberStr, sizeof(memberStr), "%s, %s (ID:%d)", memberStr, ReturnName2(i), i);
                }
            }
        }

        if(memberCount > 0)
        {
            format(string, sizeof(string), "%s\n"BLUE_E"%s "WHITE_E"[%d member]: "GREY_E"%s", string, factionNames[fid-1], memberCount, memberStr);
            found++;
        }
    }

    if(found == 0)
        return SendClientMessageEx(playerid, COLOR_ARWIN, "INFO: "WHITE_E"Tidak ada goodside (faction) yang online saat ini.");

    format(string, sizeof(string), "%s\n\n"GREY_E"Total goodside faction online: %d", string, found);
    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Goodside Online", string, "Close", "");
    return 1;
}
