
stock EventTextdrawSetString()
{
	if(EventData[eventTypes] == TYPE_TDM)
	{
		new str[518];
		format(str, sizeof(str), "~y~-_Score_- ~n~~w~target:_~g~%d ~n~~r~team_a:_%d ~n~~b~team_b:_%d", EventData[eventTargets], EventData[eventScore][0], EventData[eventScore][1]);
		TextDrawSetString(EventTD[1], str);
	}
	if(EventData[eventTypes] == TYPE_ZOMBIE)
	{
		new str[518];
		if(EventData[eventTimer] < 10) format(str, sizeof(str), "~y~-_Time_Left- ~n~~w~0%d:0%d ~n~humans:_~g~%d", EventData[eventMinutes],EventData[eventTimer], EventData[eventHumans]);
		else format(str, sizeof(str), "~y~-_Time_Left- ~n~~w~0%d:%d ~n~humans:_~g~%d", EventData[eventMinutes],EventData[eventTimer], EventData[eventHumans]);
		TextDrawSetString(EventTD[1], str);
	}
	return 1;
}

stock EventTypes(type)
{
	new name[25];
	switch(type)
	{
		case TYPE_TDM: name = "Team Deathmatch";
		case TYPE_DM: name = "Deathmatch";
		case TYPE_ZOMBIE: name = "Zombie";
		case TYPE_NONE: name = "N/A";
	}
	return name;
}

stock eventCount()
{
	new count = 0;
	foreach(new i : Player) if(IsPlayerInEvent(i)) {
		count++;
	}
	return count;
}

stock SendEventMessageAll(color, message[])
{
	foreach(new i : Player) if(IsPlayerInEvent(i)) 
	{
		SendClientMessageEx(i, color, message);
	}
	return 1;
}

function eventSpawnTimer(playerid)
{
	SetPlayerVirtualWorld(playerid, EventData[eventWorld]);
	TogglePlayerControllable(playerid, 1);
	SendCustomMessage(playerid, "EVENT", ""RED_E"You can kill enemy now!.");
	if(EventData[eventTypes] == TYPE_ZOMBIE)
	{
		if(eventTeams[playerid] == TEAM_A)
		{
			for(new i = 0; i != 3; i++) 
			{
				if(EventData[eventWeapons][i]) 
				{
					GivePlayerEventWeapon(playerid, EventData[eventWeapons][i], EventData[eventAmmo][i]);
				}
			}
		}
		else if(eventTeams[playerid] == TEAM_B)
		{
			GivePlayerEventWeapon(playerid, 9, 1);
		}
	}
	else
	{
		for(new i = 0; i != 3; i++) 
		{
			if(EventData[eventWeapons][i]) 
			{
				GivePlayerEventWeapon(playerid, EventData[eventWeapons][i], EventData[eventAmmo][i]);
			}
		}
	}
	eventWaitingSpawn[playerid] = 0;
	eventSpawn(playerid);
	return 1;
}

stock eventSpawn(playerid)
{
	if(IsPlayerInEvent(playerid))
	{
		if(eventWaitingSpawn[playerid])
		{
			GameTextForPlayer(playerid, "SPAWN IN~n~3 SECONDS", 1000, 6);
			SetPlayerVirtualWorld(playerid, playerid+12);
			TogglePlayerControllable(playerid, 0);
			if(EventData[eventTypes] == TYPE_TDM) {
				SetPlayerPos(playerid, EventData[eventSpawnX][eventTeams[playerid]-1], EventData[eventSpawnY][eventTeams[playerid]-1], EventData[eventSpawnZ][eventTeams[playerid]-1]);
			}
			else if(EventData[eventTypes] == TYPE_DM) {
				SetPlayerPos(playerid, EventData[eventSpawnX_DM], EventData[eventSpawnY_DM], EventData[eventSpawnZ_DM]);
			}
			else if(EventData[eventTypes] == TYPE_ZOMBIE) {
				SetPlayerPos(playerid, EventData[eventSpawnX_DM], EventData[eventSpawnY_DM], EventData[eventSpawnZ_DM]);
			}
			SetTimerEx("eventSpawnTimer", 3000, false, "d", playerid);
			SendCustomMessage(playerid, "EVENT", ""RED_E"Waiting 3 seconds to spawn with other player.");
			return 1;
		}
		if(EventData[eventTypes] == TYPE_TDM)
		{
			SetPlayerPos(playerid, EventData[eventSpawnX][eventTeams[playerid]-1], EventData[eventSpawnY][eventTeams[playerid]-1], EventData[eventSpawnZ][eventTeams[playerid]-1]);
			SetPlayerFacingAngle(playerid, EventData[eventSpawnA][eventTeams[playerid]-1]);
			SetCameraBehindPlayer(playerid);

			SetPlayerSkin(playerid, EventData[eventSkin][eventTeams[playerid]-1]);

			SetPlayerInterior(playerid, EventData[eventInt]);
			SetPlayerVirtualWorld(playerid, EventData[eventWorld]);
			defer eventSpawnProp[500](playerid);
		}
		else if(EventData[eventTypes] == TYPE_DM)
		{
			SetPlayerTeam(playerid, NO_TEAM);
			SetPlayerPos(playerid, EventData[eventSpawnX_DM], EventData[eventSpawnY_DM], EventData[eventSpawnZ_DM]);
			SetCameraBehindPlayer(playerid);

			SetPlayerInterior(playerid, EventData[eventInt]);
			SetPlayerVirtualWorld(playerid, EventData[eventWorld]);
			defer eventSpawnProp[500](playerid);
		}
		else if(EventData[eventTypes] == TYPE_ZOMBIE)
		{
			if(eventTeams[playerid] == TEAM_B)
			{
				new rand = RandomEx(1,3);

				if(rand == 1)
					eventZombieSkin[playerid] = 162;
				else if(rand == 2)
					eventZombieSkin[playerid] = 205;
				else if(rand == 3)
					eventZombieSkin[playerid] = 99;
				SetPlayerSkin(playerid, eventZombieSkin[playerid]);
				SetPlayerColor(playerid, COLOR_GREEN);
				if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                    UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_GREEN, (sprintf("%s {ffffff}(%d)", ReturnName(playerid), playerid)));
			}
			SetPlayerTeam(playerid, eventTeams[playerid]);
			SetPlayerPos(playerid, EventData[eventSpawnX_DM], EventData[eventSpawnY_DM], EventData[eventSpawnZ_DM]);
			SetCameraBehindPlayer(playerid);

			SetPlayerInterior(playerid, EventData[eventInt]);
			SetPlayerVirtualWorld(playerid, EventData[eventWorld]);
			defer eventSpawnProp[500](playerid);
		}
	}
	return 1;
}

stock GivePlayerEventWeapon(playerid, weaponid, ammo)
{
	if(IsPlayerInEvent(playerid))
	{
		GivePlayerWeapon(playerid, weaponid, ammo);
	}
	return 1;
}

timer eventSpawnProp[500](playerid)
{
	if(IsPlayerConnected(playerid) && IsPlayerInEvent(playerid))
	{
		SetPlayerHealth(playerid, EventData[eventHealths]);
		SetPlayerArmour(playerid, EventData[eventArmors]);
	}
	return 1;
}

stock EventTextdrawHide()
{
	foreach(new playerid : Player)
	{
		if(IsPlayerInEvent(playerid) && EventData[eventStart])
		{
			TextDrawHideForPlayer(playerid, EventTD[0]);
			TextDrawHideForPlayer(playerid, EventTD[1]);
		}
	}
	return 1;
}

stock eventLeave(playerid)
{
	EventTextdrawHide();
	ResetPlayerWeapons(playerid);
	eventTeams[playerid] = TEAM_NONE;
	SetPlayerTeam(playerid, NO_TEAM);

	eventScore_DM[playerid] = 0;
	eventJoin[playerid] = 0;
    SetPlayerInterior(playerid, pData[playerid][pIntEvent]);
	SetPlayerVirtualWorld(playerid, pData[playerid][pWorldEvent]);

	if(GetPlayerState(playerid) == PLAYER_STATE_WASTED)
	{
		SetSpawnInfo(playerid, NO_TEAM, pData[playerid][pSkin], pData[playerid][pPos][0], pData[playerid][pPos][1], pData[playerid][pPos][2], 0.0, 0, 0, 0, 0, 0, 0);
	}
	if(pData[playerid][pAdminDuty])
	{
		SetPlayerSkin(playerid, pData[playerid][pSkin]);
		SetPlayerColor(playerid, COLOR_RED);
		if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
            UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_RED, (sprintf("%s {ffffff}(%d)", ReturnName(playerid), playerid)));
	}
	else if (pData[playerid][pOnDuty])
	{
		SetFactionColor(playerid);
		SetPlayerSkin(playerid, pData[playerid][pFacSkin]);
	}
	else
	{
		SetPlayerSkin(playerid, pData[playerid][pSkin]);
		SetPlayerColor(playerid, COLOR_WHITE);
		RefreshWeapon(playerid);
		if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
    		UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s {ffffff}(%d)", ReturnName(playerid), playerid)));
	}
	
	Dyoc_Attach(playerid);
	HBEShowEvent(playerid);
	SetPlayerPos(playerid, pData[playerid][pPos][0], pData[playerid][pPos][1], pData[playerid][pPos][2]);
	SetPlayerFacingAngle(playerid, pData[playerid][pPos][3]);
	SetPlayerSkin(playerid, pData[playerid][pSkin]);
	SetPlayerHealthEx(playerid, pData[playerid][pEventHealth]);
	SetPlayerArmourEx(playerid, pData[playerid][pEventArmour]);
	eventZombieSkin[playerid] = 0; 
	eventZombieCD[playerid] = 0;
	eventWaitingSpawn[playerid] = 0;
	DisablePlayerRaceCheckpoint(playerid);
	return 1;
}

stock HBEHideEvent(playerid)
{
	PlayerHBEHide(playerid);
	return 1;
}

stock HBEShowEvent(playerid)
{
	PlayerHBEShow(playerid);
	return 1;
}

function ClearEventFreeze(playerid)
{
	TogglePlayerControllable(playerid, true);
	SetCameraBehindPlayer(playerid);
	return 1;
}