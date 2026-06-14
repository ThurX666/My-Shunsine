
/* [COMMAND] */
CMD:eventtttt(playerid, params[])
{
	static
		option[10],
		extendstring[128];

	if(sscanf(params, "s[10]S()[128]", option, extendstring))
	{
		if(pData[playerid][pAdmin] > 4) 
		{
			Usage(playerid, "/event [entity]");
			Usage(playerid, "ENTITY : create/end/open/start/weapon/tdmspawn1/tdmspawn2/dmspawn/zombiespawn");
			return 1;
		}
		else 
		{
			return Usage(playerid, "/event [join/leave]");
		}
	}
    if(!strcmp(option, "leave")) {
		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		if(!IsPlayerInEvent(playerid))
			return Error(playerid, "Kamu tidak dalam acara event.");

		if(!EventData[eventStart])
			return Error(playerid, "Event belum di mulai, tidak dapat meninggalkan event.");

		eventLeave(playerid);
        Servers(playerid, "Kamu telah meninggalkan event yang sedang berlangsung, kamu tidak mendapatkan bonus dari event.");
	}
	else if(!strcmp(option, "start")) {
		if(pData[playerid][pAdmin] < 4)
			return PermissionError(playerid);

		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		if(EventData[eventTypes] == TYPE_TDM && (EventData[eventSpawnX][0] == 0.0 || EventData[eventSpawnX][1] == 0.0))
			return Error(playerid, "Lokasi team belum di tentukan, /event [tdmspawn1/2].");

		if(EventData[eventTypes] == TYPE_DM && (EventData[eventSpawnY_DM] == 0.0 || EventData[eventSpawnY_DM] == 0.0))
			return Error(playerid, "Lokasi team spawn belum di tentukan, /event [dmspawn].");

		if(EventData[eventTypes] == TYPE_DM && (EventData[eventSpawnY_DM] == 0.0 || EventData[eventSpawnY_DM] == 0.0))
			return Error(playerid, "Lokasi team spawn belum di tentukan, /event [zombiespawn].");

		if(EventData[eventStart])
			return Error(playerid, "Event telah dimulai sebelumnya.");

		EventData[eventStart] = 0;
		EventData[eventScore][0] = 0;
		EventData[eventScore][1] = 0;
		EventData[eventOpen] = 1;
		EventData[eventCountdown] = 30;
		foreach(new i : Player) 
		{
			if(IsPlayerInEvent(i)) 
			{
				SetPlayerVirtualWorld(i, EventData[eventWorld]);
			}
		}
		SendClientMessageToAllEx(COLOR_ARWIN, "EVENT: "RED_E"%s "YELLOW_E"has started a "RED_E"%s"YELLOW_E" event!", pData[playerid][pAdminname], EventTypes(EventData[eventTypes]));
		SendClientMessageToAllEx(COLOR_ARWIN, "EVENT: "YELLOW_E"use "RED_E"'/event join'"YELLOW_E" to participate in the event!.", pData[playerid][pAdminname],EventTypes(EventData[eventTypes]));
	}
	else if(!strcmp(option, "join")) 
	{
		if(!EventData[eventCreated] || !EventData[eventOpen])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		if(EventData[eventStart])
			return Error(playerid, "Event sedang berlangsung, tidak dapat mengikutinya lagi.");
		if(IsPlayerInEvent(playerid))
			return Error(playerid, "Kamu telah berada dalam event.");

		if(pData[playerid][pJailTime])
			return Error(playerid, "Waktu di penjara belum habis, tidak dapat mengikuti event.");

		if (pData[playerid][pAdminDuty])
			return Error(playerid, "You must off duty admin to join event.");

		if (pData[playerid][pMaskOn])
			return Error(playerid, "Disable your mask first!");

		//Team Selection
		eventJoin[playerid] = 1;
		
		for (new id = 0; id < MAX_PLAYER_ATTACHED_OBJECTS; id++) if(IsPlayerAttachedObjectSlotUsed(playerid, id)) 
		{
			RemovePlayerAttachedObject(playerid, id);
		
		}
		pData[playerid][pIntEvent] = GetPlayerInterior(playerid);
		pData[playerid][pWorldEvent] = GetPlayerVirtualWorld(playerid);
		
		GetPlayerPos(playerid, pData[playerid][pPos][0], pData[playerid][pPos][1], pData[playerid][pPos][2]);
		GetPlayerFacingAngle(playerid, pData[playerid][pPos][3]);
		
		GetPlayerHealth(playerid, pData[playerid][pEventHealth]);
		GetPlayerArmour(playerid, pData[playerid][pEventArmour]);
		ResetPlayerWeapons(playerid);
		HBEHideEvent(playerid);

		if(EventData[eventTypes] == TYPE_TDM)
		{
			if(EventData[eventSelectTeam])  {
				EventData[eventSelectTeam] = 0;
				eventTeams[playerid] = TEAM_A;
				SetPlayerColor(playerid, COLOR_RED);
				if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                    UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_RED, (sprintf("%s {ffffff}(%d)", ReturnName(playerid), playerid)));
			}
			else {
				EventData[eventSelectTeam] = 1; 
				eventTeams[playerid] = TEAM_B;
				SetPlayerColor(playerid, COLOR_BLUE);
				if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                    UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_BLUE, (sprintf("%s {ffffff}(%d)", ReturnName(playerid), playerid)));
			}
			new str[518];
			format(str, sizeof(str), "~y~-_Score_- ~n~~w~target:_~g~%d ~n~~r~team_a:_%d ~n~~b~team_b:_%d", EventData[eventTargets], EventData[eventScore][0], EventData[eventScore][1]);
			TextDrawSetString(EventTD[1], str);
			TextDrawShowForPlayer(playerid, EventTD[0]);
			TextDrawShowForPlayer(playerid, EventTD[1]);
			SetPlayerTeam(playerid, eventTeams[playerid]);

			//New event data
			eventSpawn(playerid);
			SendCustomMessage(playerid, "EVENT", ""YELLOW_E"Welcome to the event, the event will start in a moment");
			SendCustomMessage(playerid, "EVENT", ""YELLOW_E"Please avoid harming other player before the event started");
			SendCustomMessage(playerid, "EVENT", ""YELLOW_E"This is a "RED_E"%s "YELLOW_E"event, please avoid friendly-fire", EventTypes(EventData[eventTypes]));
		}
		else if(EventData[eventTypes] == TYPE_DM)
		{
			eventTeams[playerid] = NO_TEAM;
			SetPlayerTeam(playerid, eventTeams[playerid]);
			eventSpawn(playerid);

			SendCustomMessage(playerid, "EVENT", ""YELLOW_E"Welcome to the event, the event will start in a moment");
			SendCustomMessage(playerid, "EVENT", ""YELLOW_E"Please avoid harming other player before the event started");
		}
		else if(EventData[eventTypes] == TYPE_ZOMBIE)
		{
			if(EventData[eventSelectTeam])  {
				EventData[eventSelectTeam] = 0;
				eventTeams[playerid] = TEAM_A;
				EventData[eventHumans]++;
				SetPlayerColor(playerid, COLOR_GREEN);
				if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                    UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_GREEN, (sprintf("%s {ffffff}(%d)", ReturnName(playerid), playerid)));
			}
			else {
				EventData[eventSelectTeam] = 1; 
				eventTeams[playerid] = TEAM_B;
				new rand = RandomEx(1,3);
		 		SetPlayerColor(playerid, COLOR_RED);
				if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                    UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_RED, (sprintf("%s {ffffff}(%d)", ReturnName(playerid), playerid)));
				if(rand == 1)
					eventZombieSkin[playerid] = 162;
				else if(rand == 2)
					eventZombieSkin[playerid] = 205;
				else if(rand == 3)
					eventZombieSkin[playerid] = 99;
			}
			SetPlayerTeam(playerid, eventTeams[playerid]);
			new str[518];
			if(EventData[eventTimer] < 10) format(str, sizeof(str), "~y~-_Time_Left- ~n~~w~0%d:0%d ~n~humans:_~g~%d", EventData[eventMinutes],EventData[eventTimer], EventData[eventHumans]);
			else format(str, sizeof(str), "~y~-_Time_Left- ~n~~w~0%d:%d ~n~humans:_~g~%d", EventData[eventMinutes],EventData[eventTimer], EventData[eventHumans]);
			TextDrawLetterSize(EventTD[0], 0.600000, 3.499);
			TextDrawSetString(EventTD[1], str);
			TextDrawShowForPlayer(playerid, EventTD[0]);
			TextDrawShowForPlayer(playerid, EventTD[1]);
			eventSpawn(playerid);
			SendCustomMessage(playerid, "EVENT", ""YELLOW_E"Welcome to the event, the event will start in a moment");
			SendCustomMessage(playerid, "EVENT", ""YELLOW_E"Please avoid harming other player before the event started");
		}
	}
	else if(!strcmp(option, "create")) {
		if(pData[playerid][pAdmin] < 4)
			return PermissionError(playerid);

		if(EventData[eventStart])
			return Error(playerid, "Event telah berlangsung.");

		Dialog_Show(playerid, eventType, DIALOG_STYLE_LIST, "Event Type", "TDM\nDM\nZOMBIE", "Select", "Close");
	}
	else if(!strcmp(option, "end")) {
		if(pData[playerid][pAdmin] < 4)
			return PermissionError(playerid);

		static const empty_player[E_EVENT];
	    EventData = empty_player;
		SendEventMessageAll(COLOR_ARWIN, "EVENT: "RED_E"Admin menghentikan event yang sedang berlangsung.");
	    Servers(playerid, "Kamu menghentikan event.");
	    eventLeave(playerid);
		foreach(new i : Player) 
		{
			if(IsPlayerInEvent(i)) 
			{
				eventLeave(i);
			}
		}
	}
	else if(!strcmp(option, "tdmspawn1")) {
		if(pData[playerid][pAdmin] < 4)
			return PermissionError(playerid);

		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		GetPlayerPos(playerid, EventData[eventSpawnX][0], EventData[eventSpawnY][0], EventData[eventSpawnZ][0]);
		GetPlayerFacingAngle(playerid, EventData[eventSpawnA][0]);
		Servers(playerid, "Kamu telah menentukan spawn untuk "RED_E"team A");
	}
	else if(!strcmp(option, "tdmspawn2")) {
		if(pData[playerid][pAdmin] < 4)
			return PermissionError(playerid);

		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		GetPlayerPos(playerid, EventData[eventSpawnX][1], EventData[eventSpawnY][1], EventData[eventSpawnZ][1]);
		GetPlayerFacingAngle(playerid, EventData[eventSpawnA][1]);
		Servers(playerid, "Kamu telah menentukan spawn untuk {0049FF}team B");
	}
	else if(!strcmp(option, "dmspawn")) {
		if(pData[playerid][pAdmin] < 4)
			return PermissionError(playerid);

		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		GetPlayerPos(playerid, EventData[eventSpawnX_DM], EventData[eventSpawnY_DM], EventData[eventSpawnZ_DM]);
		Servers(playerid, "Kamu telah menentukan spawn untuk Event DM");
	}
	else if(!strcmp(option, "zombiespawn")) {
		if(pData[playerid][pAdmin] < 4)
			return PermissionError(playerid);

		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		GetPlayerPos(playerid, EventData[eventSpawnX_DM], EventData[eventSpawnY_DM], EventData[eventSpawnZ_DM]);
		Servers(playerid, "Kamu telah menentukan spawn untuk Event Zombie");
	}
	else if(!strcmp(option, "weapon")) {
		if(pData[playerid][pAdmin] < 4)
			return PermissionError(playerid);

		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");
		new string[212];
		format(string, sizeof(string), "Weapon 1: %s - %d\nWeapon 2: %s - %d\nWeapon 3: %s - %d", ReturnWeaponName(EventData[eventWeapons][0]),EventData[eventAmmo][0],ReturnWeaponName(EventData[eventWeapons][1]),EventData[eventAmmo][1],ReturnWeaponName(EventData[eventWeapons][2]), EventData[eventAmmo][2]);
		Dialog_Show(playerid, eventWeapon, DIALOG_STYLE_LIST, "Event Weapon", string,"Edit", "Close");
	}
	return 1;
}
