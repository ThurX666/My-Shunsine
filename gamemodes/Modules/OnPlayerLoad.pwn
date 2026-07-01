
function SafeLogin(playerid) 
{
    for (new i = 0; i < 3; i++) 
	{
		TextDrawHideForPlayer(playerid, MYSUNSHINE[i]);
	}

	PlayAudioStreamForPlayer(playerid, "http://i.top4top.io/m_37912m59d1.mp3");

    new hour;
    gettime(hour, _, _);
    SetPlayerTime(playerid, hour, 0);
	SetPlayerJoinCamera(playerid);
	SQL_CheckAccount(playerid);
	SetPlayerColor(playerid, COLOR_GREY);
	if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
       UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_GREY, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
}

SQL_CheckAccount(playerid) 
{
   	new query[103];
	mysql_format(g_SQL, query, sizeof query, "SELECT * FROM `ucp` WHERE `username` = '%e' LIMIT 1", charData[playerid][cName]);
	mysql_tquery(g_SQL, query, "OnPlayerDataLoaded", "dd", playerid, g_MysqlRaceCheck[playerid]);
    return 1;
}

SetPlayerSpawn(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		if(pData[playerid][pnewplayer] == 0)
		{
			TogglePlayerControllable(playerid,0);
			SetPlayerHealth(playerid, 100.0);
			SetPlayerArmour(playerid, 0.0);
			SetPlayerPos(playerid, 2936.16, -2051.81, 3.56);
			SetPlayerCameraPos(playerid,2936.16, -2051.81,22.0264);
			SetPlayerCameraLookAt(playerid,2936.16, -2051.81,22.0264);
			SetPlayerVirtualWorld(playerid, 0);
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
			ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_LIST, "Origin:", szMiscArray, "Select", "Batal");
		}
		else
		{
			SetPlayerColor(playerid, COLOR_WHITE);
		   	if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
        		UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
			SetPlayerSkin(playerid, pData[playerid][pSkin]);
			
			PlayerHBEShow(playerid);

			if(pData[playerid][pOnDuty] >= 1)
			{
				SetPlayerSkin(playerid, pData[playerid][pFacSkin]);
				SetFactionColor(playerid);
			}
			if(pData[playerid][pAdminDuty] > 0) 
			{
				SetPlayerColor(playerid, COLOR_RED);
		    	if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
        			UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_RED, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
			}
			ResetNameTag(playerid);
			Dyoc_Attach(playerid);
			ResetPlayerMoney(playerid);
			GivePlayerMoney(playerid, pData[playerid][pMoney]);
			SetPlayerScore(playerid, pData[playerid][pLevel]);
			pData[playerid][pSpawned] = 1;
			SetCameraBehindPlayer(playerid);
			RefreshWeapon(playerid);
			SetPlayerArmedWeapon(playerid, 0);
			SetPlayerInterior(playerid, pData[playerid][pInt]);
			SetPlayerVirtualWorld(playerid, pData[playerid][pWorld]);
			SetPlayerHealth(playerid, pData[playerid][pHealth]);
			SetPlayerArmour(playerid, pData[playerid][pArmour]);
			SetPlayerStreamerSettings(playerid);
			pData[playerid][pFreeze] = 1;
			pData[playerid][pFreezeTimer1] = SetTimerEx("PlayerUnfreeze", 5000, false, "i", playerid);
			TogglePlayerControllable(playerid, 0);
			TogglePlayerSpectating(playerid, 0);
			// if(pData[playerid][pJail] > 0) JailPlayer(playerid); 
			if(pData[playerid][pArrestTime] > 0) SetPlayerArrest(playerid);
			
			if(pData[playerid][pNotifSpawn] == 1)
			{
				// InterpolateCameraPos(playerid, pData[playerid][pPosX]-2.5, pData[playerid][pPosY],250.00,pData[playerid][pPosX]-2.5, pData[playerid][pPosY], pData[playerid][pPosZ]+2.5,2500,CAMERA_MOVE);
				// InterpolateCameraLookAt(playerid, pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ], pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ], 2500, CAMERA_MOVE);
				new date[6];
				TimestampToDate(gettime(), date[2], date[1], date[0], date[3], date[4], date[5]);
				SendClientMessageEx(playerid, COLOR_AQUA, "SERVER: "WHITE_E"Selamat datang "YELLOW_E"%s", pData[playerid][pName]);
				SendClientMessageEx(playerid, COLOR_ARWIN, "MOTD: "GREEN_E"JANGAN BIASAKAN KIRIM PM KE STAFF ATAU ADMIN YANG ON DUTY - "RED_E"myrl");
				if(pData[playerid][pFaction])
				{
					SendClientMessageEx(playerid, COLOR_RED, "Faction Note: "YELLOW_E"JIKA INGIN OFF-DUTY MOHON UNIT DIKEMBALIKAN LAGI KE BASEMENT");
				}
				if(pData[playerid][pAdmin])
				{
					SendClientMessageEx(playerid, COLOR_YELLOW, "Admin MOTD: "YELLOW_E"Dilarang abuse command untuk kepentingan sendiri punishment demote & block account");
				}
				// SendClientMessageEx(playerid, COLOR_RED, "SERVER: "YELLOW_E"Gunakan command "RED_E"'/maxobject' "YELLOW_E"untuk mengatur jarak object!");
				SendClientMessageEx(playerid, COLOR_ARWIN, "SERVER: {FFFFFF}Anda terakhir login {FFFF00}%s", pData[playerid][pLastLogin]);
				SendClientMessageEx(playerid, COLOR_AQUA, "SERVER: {ffffff}Today is {ffff00}%s %s %s %i", GetWeekDay(date[0], date[1], date[2]), GetDay(date[0]), GetMonthName(date[1]));
				SendClientMessageEx(playerid, COLOR_AQUA, "SERVER: {FFFFFF}Server memerlukan waktu {FFFF00}%d milisecond {FFFFFF}untuk memuat data char anda!", GetPlayerPing(playerid));
				pData[playerid][pNotifSpawn] = 0;
				if(pData[playerid][pTogMask] == 1) callcmd::togmask(playerid, "");
				if(TogglePlayer[playerid][ToggleMoney]) TextDrawShowForPlayer(playerid, DollarCents);
				if(TogglePlayer[playerid][ToggleDate]) TextDrawShowForPlayer(playerid, Date);
				if(TogglePlayer[playerid][ToggleTime]) TextDrawShowForPlayer(playerid, Time);
				if(TogglePlayer[playerid][ToggleGPS]) PlayerTextDrawShow(playerid, GPSLocation[playerid]);
				if(TogglePlayer[playerid][ToggleWeb]) TextDrawShowForPlayer(playerid, Webtd[2]);
				// if(TogglePlayer[playerid][ToggleWeb]) TextDrawShowForPlayer(playerid, Webtd[1]);
				// if(TogglePlayer[playerid][ToggleWeb]) TextDrawShowForPlayer(playerid, Webtd[2]);
				// SetTimerEx("SetPlayerCameraBehind", 4500, false, "i", playerid);
				for (new i; i < 3; i++) TextDrawShowForPlayer(playerid, SUNSHINELOGO[i]);
			}
			for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
		}	
	}
}

function SetPlayerCameraBehind(playerid)
{
	SetCameraBehindPlayer(playerid);
	return 1;
}

function OnPlayerDataLoaded(playerid, race_check)
{
	new BannedReason[128], verifemail;
	if(race_check != g_MysqlRaceCheck[playerid]) return Kick(playerid);
	if(cache_num_rows() > 0)
	{
		cache_get_value_name_int(0, "reg_id", charData[playerid][cID]);
		cache_get_value_name(0, "password", charData[playerid][cPassword], 65);
		cache_get_value_name(0, "salt", charData[playerid][cSalt], 17);
		cache_get_value_name_int(0, "CharName", charData[playerid][cCharName]);
		cache_get_value_name_int(0, "CharName2", charData[playerid][cCharName2]);
		cache_get_value_name_int(0, "CharName3", charData[playerid][cCharName3]);
		cache_get_value_name_int(0, "banned", charData[playerid][cCharBan]);
		cache_get_value_name_int(0, "pin", charData[playerid][cCharPinCode]);
		cache_get_value_name(0, "bannedreason", BannedReason);
		format(charData[playerid][cCharBanReason], 128, "%s", BannedReason);
		cache_get_value_name_int(0, "verifemail", verifemail);
		foreach(new i : Player)
		{
			if(!strcmp(charData[i][cName], ReturnName(playerid)) && i != playerid)
			{
				SendCustomMessage(playerid, "UCP", "Seseorang sedang login menggunakan UCP yang sama.");
				KickEx(playerid);
				return 1;
			}
		}
		pData[playerid][IsLoggedIn] = true;
		pData[playerid][LoginAttempts] = 0;
		if(charData[playerid][cCharBan] > 0)
		{
			new String[512];
			format(String, sizeof(String), ""YELLOW_E"Your UCP account is blocked\n{00FFFF}User: %s\n{00FFFF}Reason: "WHITE_E"%s\n"YELLOW_E"Please create an unban appeal in our discrod My Sunshine Roleplay", charData[playerid][cName], BannedReason);
			ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Account Blocked", String," Ok","");
			KickEx(playerid);
		}
		else
		{
			charData[playerid][cCharOn] = 1;
			charData[playerid][cCharTime] = 60;
			new String[512];
			format(String, sizeof(String), "UCP Account: {00FFFF}%s\n"WHITE_E"Attemp: {00FFFF}%d/5\n"WHITE_E"Password: "GREEN_E"(input below)", charData[playerid][cName], pData[playerid][LoginAttempts]);
			ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Account Login", String," Login","Exit");
		}
		if(verifemail == 0)
		{
			ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Enter the pin code", "Enter the pin code sent in your discrod message!"," Regis","Exit");
		}
	}
	else
	{
		new query[103];
		mysql_format(g_SQL, query, sizeof query, "SELECT * FROM `players` WHERE `username` = '%e' LIMIT 1", charData[playerid][cName]);
		mysql_pquery(g_SQL, query, "OnPlayerDataLoaded1", "dd", playerid, g_MysqlRaceCheck[playerid]);
	}
	return 1;
}

function OnPlayerDataLoaded1(playerid, race_check)
{
	if(race_check != g_MysqlRaceCheck[playerid]) return Kick(playerid);
	if(cache_num_rows() > 0)
	{
		cache_get_value_name(0, "ucpname", charData[playerid][cName], 52);
		new query[103];
		mysql_format(g_SQL, query, sizeof query, "SELECT * FROM `ucp` WHERE `username` = '%e' LIMIT 1", charData[playerid][cName]);
		mysql_pquery(g_SQL, query, "OnPlayerDataLoaded", "dd", playerid, g_MysqlRaceCheck[playerid]);
	}
	else
	{
		new String[212];
		format(String, sizeof(String), "{FFFFFF}UCP Account: {00FFFF}%s\n"YELLOW_E"Not registered on the server", charData[playerid][cName]);
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Unregistered", String, "Ok", "");
		KickEx(playerid);
	}
	return 1;
}

function LoadPlayerChar(playerid)
{
	new query[128];
	format(query,sizeof(query),"SELECT * FROM `players` WHERE `reg_id` = '%d'",charData[playerid][cCharName]);
	mysql_tquery(g_SQL,query, "CharName", "i", playerid);
	
	format(query,sizeof(query),"SELECT * FROM `players` WHERE `reg_id` = '%d'",charData[playerid][cCharName2]);
	mysql_tquery(g_SQL,query, "CharName2", "i", playerid);

	format(query,sizeof(query),"SELECT * FROM `players` WHERE `reg_id` = '%d'",charData[playerid][cCharName3]);
	mysql_tquery(g_SQL,query, "CharName3", "i", playerid);
	charData[playerid][cCharOn] = 0;
	charData[playerid][cCharTime] = 0;
	return 1;
}

function CharName(playerid)
{
 	if(cache_num_rows() > 0)
 	{
	    cache_get_value_name(0, "username", charData[playerid][cChar1], MAX_PLAYER_NAME+1);
		cache_get_value_name_int(0, "level", charData[playerid][cCharLevel1]);
		cache_get_value_name(0, "last_login", charData[playerid][cCharLastLogin1], 128);
 	    SetPVarInt(playerid,"Char1da",1);
 	}
	return 1;
}

function CharName2(playerid)
{
 	if(cache_num_rows() > 0)
 	{
	    cache_get_value_name(0, "username", charData[playerid][cChar2], MAX_PLAYER_NAME+1);
		cache_get_value_name_int(0, "level", charData[playerid][cCharLevel2]);
		cache_get_value_name(0, "last_login", charData[playerid][cCharLastLogin2], 128);
 	    SetPVarInt(playerid,"Char2da",1);
 	}
	return 1;
}

function CharName3(playerid)
{
 	if(cache_num_rows() > 0)
 	{
	    cache_get_value_name(0, "username", charData[playerid][cChar3], MAX_PLAYER_NAME+1);
		cache_get_value_name_int(0, "level", charData[playerid][cCharLevel3]);
		cache_get_value_name(0, "last_login", charData[playerid][cCharLastLogin3], 128);
 	    SetPVarInt(playerid,"Char3da",1);
 	}
	EndLoadChar(playerid);
	return 1;
}

function EndLoadChar(playerid)
{
	new String[212],type1[128],type2[128],type3[128];
	strcat(String, "Name\tLevel\tLast Login\n");
	if(GetPVarInt(playerid,"Char1da")==1)
	{
		format(type1, 128, charData[playerid][cChar1]);
	}
	else
	{
		format(type1, 128, "Create Character");
	}
	if(GetPVarInt(playerid,"Char2da")==1)
	{
		format(type2, 128, charData[playerid][cChar2]);
	}
	else
	{
		format(type2, 128, "Create Character");
	}
	if(GetPVarInt(playerid,"Char3da")==1)
	{
		format(type3, 128, charData[playerid][cChar3]);
	}
	else
	{
		format(type3, 128, "Create Character");
	}
	format(String, sizeof(String),"%s%s\t%d\t%s\n", String, type1, charData[playerid][cCharLevel1], charData[playerid][cCharLastLogin1]);
	format(String, sizeof(String),"%s%s\t%d\t%s\n", String, type2, charData[playerid][cCharLevel2], charData[playerid][cCharLastLogin2]);
	format(String, sizeof(String),"%s%s\t%d\t%s\n", String, type3, charData[playerid][cCharLevel3], charData[playerid][cCharLastLogin3]);
	ShowPlayerDialog(playerid,DIALOG_LOGINCHAR,DIALOG_STYLE_TABLIST_HEADERS,"Select Character",String,"Select","Close");
}

loadPlayerChars(playerid,nummer)
{
	new query[250];
	if(nummer==1)
	{
		format(query,sizeof(query),"SELECT * FROM `players` WHERE `reg_id`='%d'", charData[playerid][cCharName]);
		mysql_tquery(g_SQL,query, "AssignPlayerData", "dd", playerid, g_MysqlRaceCheck[playerid]);
	}
	if(nummer==2)
	{
		format(query,sizeof(query),"SELECT * FROM `players` WHERE `reg_id`='%d'", charData[playerid][cCharName2]);
		mysql_tquery(g_SQL,query, "AssignPlayerData", "dd", playerid, g_MysqlRaceCheck[playerid]);
	}
	if(nummer==3)
	{
		format(query,sizeof(query),"SELECT * FROM `players` WHERE `reg_id`='%d'", charData[playerid][cCharName3]);
		mysql_tquery(g_SQL,query, "AssignPlayerData", "dd", playerid, g_MysqlRaceCheck[playerid]);
	}
	return 1;
}

function AssignPlayerData(playerid, race_check)
{
	if(race_check != g_MysqlRaceCheck[playerid])
	    return Kick(playerid);
	new aname[MAX_PLAYER_NAME], name[MAX_PLAYER_NAME], 
	str[412];
	
	cache_get_value_name_int(0, "reg_id", pData[playerid][pID]);	
	cache_get_value_name(0, "username", name);
	format(pData[playerid][pName], MAX_PLAYER_NAME, "%s", name);
	cache_get_value_name(0, "adminname", aname);
	format(pData[playerid][pAdminname], MAX_PLAYER_NAME, "%s", aname);
	cache_get_value_name(0, "ip", pData[playerid][pIP], 128);
	cache_get_value_name_int(0, "division", pData[playerid][pDivision]);
	cache_get_value_name_int(0, "admin", pData[playerid][pAdmin]);
	cache_get_value_name_int(0, "admintime", pData[playerid][pAdminTime]);
	cache_get_value_name_int(0, "helper", pData[playerid][pHelper]);
	cache_get_value_name_int(0, "level", pData[playerid][pLevel]);
	cache_get_value_name_int(0, "levelup", pData[playerid][pLevelUp]);
	cache_get_value_name_int(0, "cschar", pData[playerid][pCS]);
	cache_get_value_name_int(0, "vip", pData[playerid][pVip]);
	cache_get_value_name_int(0, "vip_time", pData[playerid][pVipTime]);
	cache_get_value_name_int(0, "gold", pData[playerid][pGold]);
	cache_get_value_name(0, "reg_date", pData[playerid][pRegDate], 128);
	cache_get_value_name(0, "last_login", pData[playerid][pLastLogin], 128);
	cache_get_value_name_int(0, "money", pData[playerid][pMoney]);
	cache_get_value_name_int(0, "bmoney", pData[playerid][pBankMoney]);
	cache_get_value_name_int(0, "brek", pData[playerid][pBankRek]);
	cache_get_value_name_int(0, "phone", pData[playerid][pPhone]);
	cache_get_value_name_int(0, "phonestatus", pData[playerid][pPhoneStatus]);
	cache_get_value_name_int(0, "phonekuota", pData[playerid][pKuota]);
	cache_get_value_name_int(0, "phonecredit", pData[playerid][pPhoneCredit]);
	cache_get_value_name_int(0, "phonebook", pData[playerid][pPhoneBook]);
	cache_get_value_name_int(0, "twitter", pData[playerid][pTwitter]);
	cache_get_value_name_int(0, "twitterstatus", pData[playerid][pTwitterStatus]);
	cache_get_value_name_int(0, "wt", pData[playerid][pWT]);
	cache_get_value_name_int(0, "hours", pData[playerid][pHours]);
	cache_get_value_name_int(0, "minutes", pData[playerid][pMinutes]);
	cache_get_value_name_int(0, "seconds", pData[playerid][pSeconds]);
	cache_get_value_name_int(0, "paycheck", pData[playerid][pPaycheck]);
	cache_get_value_name_int(0, "skin", pData[playerid][pSkin]);
	cache_get_value_name_int(0, "facskin", pData[playerid][pFacSkin]);
	cache_get_value_name_int(0, "gender", pData[playerid][pGender]);
	cache_get_value_name_int(0, "newp", pData[playerid][pnewplayer]);
	cache_get_value_name(0, "age", pData[playerid][pAge], 128);
	cache_get_value_name_float(0, "posx", pData[playerid][pPosX]);
	cache_get_value_name_float(0, "posy", pData[playerid][pPosY]);
	cache_get_value_name_float(0, "posz", pData[playerid][pPosZ]);
	cache_get_value_name_float(0, "posa", pData[playerid][pPosA]);
	cache_get_value_name_int(0, "interior", pData[playerid][pInt]);
	cache_get_value_name_int(0, "world", pData[playerid][pWorld]);
	cache_get_value_name_float(0, "health", pData[playerid][pHealth]);
	cache_get_value_name_float(0, "maxhealth", pData[playerid][pMaxHealth]);
	cache_get_value_name_float(0, "armour", pData[playerid][pArmour]);
	cache_get_value_name_float(0, "hunger", pData[playerid][pHunger]);
	cache_get_value_name_float(0, "energy", pData[playerid][pEnergy]);
	cache_get_value_name_int(0, "sick", pData[playerid][pSick]);
	cache_get_value_name_int(0, "hospital", pData[playerid][pHospital]);
	cache_get_value_name_int(0, "injured", pData[playerid][pInjured]);
	cache_get_value_name_int(0, "duty", pData[playerid][pOnDuty]);
	cache_get_value_name_int(0, "dutytime", pData[playerid][pOnDutyTime]);
	cache_get_value_name_int(0, "faction", pData[playerid][pFaction]);
	cache_get_value_name_int(0, "factionrank", pData[playerid][pFactionRank]);
	cache_get_value_name_int(0, "factionlead", pData[playerid][pFactionLead]);
	cache_get_value_name_int(0, "family", pData[playerid][pFamily]);
	cache_get_value_name_int(0, "familyrank", pData[playerid][pFamilyRank]);
	cache_get_value_name_int(0, "jail", pData[playerid][pJail]);
	cache_get_value_name_int(0, "jail_time", pData[playerid][pJailTime]);
	cache_get_value_name_int(0, "arrest", pData[playerid][pArrest]);
	cache_get_value_name_int(0, "arrest_time", pData[playerid][pArrestTime]);
	cache_get_value_name_int(0, "warn", pData[playerid][pWarn]);
	cache_get_value_name_int(0, "job", pData[playerid][pJob]);
	cache_get_value_name_int(0, "job2", pData[playerid][pJob2]);
	cache_get_value_name_int(0, "exitjob", pData[playerid][pExitJob]);
	cache_get_value_name_int(0, "taxitime", pData[playerid][pTaxiTime]);
	cache_get_value_name_int(0, "medicine", pData[playerid][pMedicine]);
	cache_get_value_name_int(0, "medkit", pData[playerid][pMedkit]);
	cache_get_value_name_int(0, "mask", pData[playerid][pMask]);
	cache_get_value_name_int(0, "helmet", pData[playerid][pHelmet]);
	cache_get_value_name_int(0, "snack", pData[playerid][pSnack]);
	cache_get_value_name_int(0, "sprunk", pData[playerid][pSprunk]);
	cache_get_value_name_int(0, "gas", pData[playerid][pGas]);
	cache_get_value_name_int(0, "bandage", pData[playerid][pBandage]);
	cache_get_value_name_int(0, "gps", pData[playerid][pGPS]);
	cache_get_value_name_int(0, "material", pData[playerid][pMaterial]);
	cache_get_value_name_int(0, "component", pData[playerid][pComponent]);
	cache_get_value_name_int(0, "food", pData[playerid][pFood]);
	cache_get_value_name_int(0, "seedwheat", pData[playerid][pSeedWheat]);
	cache_get_value_name_int(0, "seedonion", pData[playerid][pSeedOnion]);
	cache_get_value_name_int(0, "seedcarrot", pData[playerid][pSeedCarrot]);
	cache_get_value_name_int(0, "seedpotato", pData[playerid][pSeedPotato]);
	cache_get_value_name_int(0, "seedcorn", pData[playerid][pSeedCorn]);
	cache_get_value_name_int(0, "wheat", pData[playerid][pWheat]);
	cache_get_value_name_int(0, "onion", pData[playerid][pOnion]);
	cache_get_value_name_int(0, "carrot", pData[playerid][pCarrot]);
	cache_get_value_name_int(0, "potato", pData[playerid][pPotato]);
	cache_get_value_name_int(0, "corn", pData[playerid][pCorn]);
	cache_get_value_name_int(0, "price1", pData[playerid][pPrice1]);
	cache_get_value_name_int(0, "price2", pData[playerid][pPrice2]);
	cache_get_value_name_int(0, "price3", pData[playerid][pPrice3]);
	cache_get_value_name_int(0, "price4", pData[playerid][pPrice4]);
	cache_get_value_name_int(0, "crack", pData[playerid][pCrack]);
	cache_get_value_name_int(0, "pot", pData[playerid][pPot]);
	cache_get_value_name_int(0, "plant", pData[playerid][pPlant]);
	cache_get_value_name_int(0, "plant_time", pData[playerid][pPlantTime]);
	cache_get_value_name_int(0, "fishtool", pData[playerid][pFishTool]);
	cache_get_value(0, "fish0", str, 24);
	sscanf(str, "p<|>f", FishWeight[playerid][0]);
	cache_get_value(0, "fish1", str, 24);
	sscanf(str, "p<|>f", FishWeight[playerid][1]);
	cache_get_value(0, "fish2", str, 24);
	sscanf(str, "p<|>f", FishWeight[playerid][2]);
	cache_get_value(0, "fish3", str, 24);
	sscanf(str, "p<|>f", FishWeight[playerid][3]);
	cache_get_value(0, "fish4", str, 24);
	sscanf(str, "p<|>f", FishWeight[playerid][4]);
	cache_get_value_name_int(0, "worm", pData[playerid][pWorm]);
	cache_get_value_name_int(0, "drivelic", pData[playerid][pDriveLic]);
	cache_get_value_name_int(0, "drivelic_time", pData[playerid][pDriveLicTime]);
	cache_get_value_name_int(0, "flylic", pData[playerid][pFlyLic]);
	cache_get_value_name_int(0, "flylic_time", pData[playerid][pFlyLicTime]);
	cache_get_value_name_int(0, "boatlic", pData[playerid][pBoatLic]);
	cache_get_value_name_int(0, "boatlic_time", pData[playerid][pBoatLicTime]);
	cache_get_value_name_int(0, "gunlic", pData[playerid][pGunLic]);
	cache_get_value_name_int(0, "gunlic_time", pData[playerid][pGunLicTime]);
	cache_get_value_name_int(0, "trucker", pData[playerid][pTruckerLic]);
	cache_get_value_name_int(0, "trucker_time", pData[playerid][pTruckerLicTime]);
	cache_get_value_name_int(0, "lumber", pData[playerid][pLumberLic]);
	cache_get_value_name_int(0, "lumber_time", pData[playerid][pLumberLicTime]);
	cache_get_value_name_int(0, "hbemode", pData[playerid][pHBEMode]);
	cache_get_value_name_int(0, "togpm", pData[playerid][pTogPM]);
	cache_get_value_name_int(0, "togads", pData[playerid][pTogAds]);
	cache_get_value_name_int(0, "togwt", pData[playerid][pTogWT]);
	cache_get_value_name_int(0, "togglobalooc", pData[playerid][pTogGlobalOoc]);
	cache_get_value_name_int(0, "togquizvote", pData[playerid][pTogQuizVote]);
	cache_get_value_name_int(0, "togstaffquestion", pData[playerid][pTogStaffQuestion]);
	cache_get_value_name_int(0, "togstaffreport", pData[playerid][pTogStaffReport]);
	cache_get_value_name_int(0, "togstaffchat", pData[playerid][pTogStaffChat]);
	cache_get_value_name_int(0, "togfaction", pData[playerid][pTogFaction]);
	cache_get_value_name_int(0, "togradio", pData[playerid][pTogRadio]);
	cache_get_value_name_int(0, "togpaycheck", pData[playerid][pTogPaycheck]);
	cache_get_value_name_int(0, "togseatbelt", pData[playerid][pTogSealtbelt]);
	cache_get_value_name_int(0, "togchat", pData[playerid][pTogChat]);
	cache_get_value_name_int(0, "toghelmet", pData[playerid][pTogHelmet]);
	cache_get_value_name_int(0, "togmask", pData[playerid][pTogMask]);
	cache_get_value_name_int(0, "togammo", pData[playerid][pTogAmmo]);

	cache_get_value_name_int(0, "Gun1", PlayerGuns[playerid][0][weapon_id]);
	cache_get_value_name_int(0, "Gun2", PlayerGuns[playerid][1][weapon_id]);
	cache_get_value_name_int(0, "Gun3", PlayerGuns[playerid][2][weapon_id]);
	cache_get_value_name_int(0, "Gun4", PlayerGuns[playerid][3][weapon_id]);
	cache_get_value_name_int(0, "Gun5", PlayerGuns[playerid][4][weapon_id]);
	cache_get_value_name_int(0, "Gun6", PlayerGuns[playerid][5][weapon_id]);
	cache_get_value_name_int(0, "Gun7", PlayerGuns[playerid][6][weapon_id]);
	cache_get_value_name_int(0, "Gun8", PlayerGuns[playerid][7][weapon_id]);
	cache_get_value_name_int(0, "Gun9", PlayerGuns[playerid][8][weapon_id]);
	cache_get_value_name_int(0, "Gun10", PlayerGuns[playerid][9][weapon_id]);
	cache_get_value_name_int(0, "Gun11", PlayerGuns[playerid][10][weapon_id]);
	cache_get_value_name_int(0, "Gun12", PlayerGuns[playerid][11][weapon_id]);
	cache_get_value_name_int(0, "Gun13", PlayerGuns[playerid][12][weapon_id]);
	
	cache_get_value_name_int(0, "Ammo1", PlayerGuns[playerid][0][weapon_ammo]);
	cache_get_value_name_int(0, "Ammo2", PlayerGuns[playerid][1][weapon_ammo]);
	cache_get_value_name_int(0, "Ammo3", PlayerGuns[playerid][2][weapon_ammo]);
	cache_get_value_name_int(0, "Ammo4", PlayerGuns[playerid][3][weapon_ammo]);
	cache_get_value_name_int(0, "Ammo5", PlayerGuns[playerid][4][weapon_ammo]);
	cache_get_value_name_int(0, "Ammo6", PlayerGuns[playerid][5][weapon_ammo]);
	cache_get_value_name_int(0, "Ammo7", PlayerGuns[playerid][6][weapon_ammo]);
	cache_get_value_name_int(0, "Ammo8", PlayerGuns[playerid][7][weapon_ammo]);
	cache_get_value_name_int(0, "Ammo9", PlayerGuns[playerid][8][weapon_ammo]);
	cache_get_value_name_int(0, "Ammo10", PlayerGuns[playerid][9][weapon_ammo]);
	cache_get_value_name_int(0, "Ammo11", PlayerGuns[playerid][10][weapon_ammo]);
	cache_get_value_name_int(0, "Ammo12", PlayerGuns[playerid][11][weapon_ammo]);
	cache_get_value_name_int(0, "Ammo13", PlayerGuns[playerid][12][weapon_ammo]);

	cache_get_value_name(0, "AmmoType", str);
	sscanf(str, "p<|>ddddddddddddd", PlayerGuns[playerid][0][weapon_typesurplus], PlayerGuns[playerid][1][weapon_typesurplus],
	PlayerGuns[playerid][2][weapon_typesurplus], PlayerGuns[playerid][3][weapon_typesurplus], PlayerGuns[playerid][4][weapon_typesurplus],
	PlayerGuns[playerid][5][weapon_typesurplus], PlayerGuns[playerid][6][weapon_typesurplus], PlayerGuns[playerid][7][weapon_typesurplus],
	PlayerGuns[playerid][8][weapon_typesurplus], PlayerGuns[playerid][9][weapon_typesurplus], PlayerGuns[playerid][10][weapon_typesurplus], 
	PlayerGuns[playerid][11][weapon_typesurplus], PlayerGuns[playerid][12][weapon_typesurplus]);

	cache_get_value_name_int(0, "pbanned", pData[playerid][pBanned]);
    cache_get_value_name(0, "pbanreason", pData[playerid][pBanReason], 128);
	cache_get_value_name(0, "pbanby", pData[playerid][pBanBy], 128);
	cache_get_value_name_int(0, "workshop", pData[playerid][pWorkshop]);
	cache_get_value_name_int(0, "workshoprank", pData[playerid][pWorkshopRank]);
    cache_get_value_name_int(0, "rokok", pData[playerid][pRokok]);
    cache_get_value_name_int(0, "cgun", pData[playerid][pCgun]);
	cache_get_value_name_int(0, "fightstyle", pData[playerid][FightStyle]);
	cache_get_value_name_int(0, "married", pData[playerid][pMarried]);
	cache_get_value_name(0, "marriedto", pData[playerid][pMarriedTo], 50);
	cache_get_value_name_int(0, "paytoll", pData[playerid][pPayToll]);
	cache_get_value_name_int(0, "apart", pData[playerid][pApart]);
	cache_get_value_name_int(0, "ladang", pData[playerid][pLadang]);
	cache_get_value_name_int(0, "ladangrank", pData[playerid][pLadangRank]);
	cache_get_value_name_int(0, "maskid", pData[playerid][pMaskID]);
	cache_get_value_name_int(0, "mutewt", pData[playerid][pMuteWt]);
	cache_get_value_name_int(0, "skillbuilder", pData[playerid][pSkillBuilder]);
	cache_get_value_name_int(0, "skillmecha", pData[playerid][pSkillMecha]);
	cache_get_value_name_int(0, "rentveh", pData[playerid][pRents]);
	cache_get_value_name_int(0, "accent", pData[playerid][pAccent1]);
	cache_get_value_name_int(0, "furnstore", pData[playerid][pFurnStore]);
	cache_get_value_name(0, "GYMMember", str);
	sscanf(str, "p<|>dd", pData[playerid][pGYMMember], pData[playerid][pGYMMemberTime]);
	cache_get_value_name(0, "FitnessRating", str);
	sscanf(str, "p<|>ffffff", pData[playerid][pFitnessRating][0], pData[playerid][pFitnessRating][1], pData[playerid][pFitnessRating][2], pData[playerid][pFitnessRating][3], pData[playerid][pFitnessRating][4], pData[playerid][pFitnessRating][5]);
	cache_get_value_name(0, "Cough", str);
	sscanf(str, "p<|>dd", pData[playerid][pCough], pData[playerid][pCoughPills]);
	cache_get_value_name(0, "Fever", str);
	sscanf(str, "p<|>ddd", pData[playerid][pFever], pData[playerid][pFiverPills], pData[playerid][pFeverUsed]);
	cache_get_value_name(0, "Migrain", str);
	sscanf(str, "p<|>dddd", pData[playerid][pMigrainTime], pData[playerid][pMigrainRate], pData[playerid][pMigrainPills], pData[playerid][pMigrainUsed]);
	cache_get_value_name_int(0, "UsePills", pData[playerid][pUsePills]);
	cache_get_value_name(0, "Badge", str);
	sscanf(str, "p<|>s[24]s[24]", pData[playerid][pBadge], pData[playerid][pFactionRankName]);
	cache_get_value_name(0, "InInt", str);
	sscanf(str, "p<|>dddd", pData[playerid][pInDoor], pData[playerid][pInHouse], pData[playerid][pInBiz], pData[playerid][pInFlat]);
	cache_get_value_name(0, "scoreskill", str);
	sscanf(str, "p<|>dddd", pData[playerid][pScoreTrucker], pData[playerid][pScoreFishing], pData[playerid][pScoreMecha], pData[playerid][pScoreFarmer]);
	cache_get_value_name(0, "skilljob", str);
	sscanf(str, "p<|>dddd", pData[playerid][pSkillTrucker], pData[playerid][pSkillFishing], pData[playerid][pSkillMecha], pData[playerid][pSkillFarmer]);
	cache_get_value_name_int(0, "streamer", pData[playerid][pStreamer]);
	cache_get_value_name(0, "claimvip", str);
	sscanf(str, "p<|>ddd", pData[playerid][pClaimVIP][0], pData[playerid][pClaimVIP][1], pData[playerid][pClaimVIP][2]);
	cache_get_value_name(0, "schematicgun", str);
	sscanf(str, "p<|>dddddd", pData[playerid][pSchematic][0], pData[playerid][pSchematic][1], pData[playerid][pSchematic][2], pData[playerid][pSchematic][3], pData[playerid][pSchematic][4], pData[playerid][pSchematic][5]);
	cache_get_value_name(0, "skillweapon", str);
	sscanf(str, "p<|>ddddd", pData[playerid][pSkillWeapon][0], pData[playerid][pSkillWeapon][1], pData[playerid][pSkillWeapon][2], pData[playerid][pSkillWeapon][3], pData[playerid][pSkillWeapon][4]);
	cache_get_value_name(0, "TogAuto", str);
	sscanf(str, "p<|>dddddddd", pData[playerid][pTogPaycheck], pData[playerid][pTogHandbrake], pData[playerid][pTogHelmet], pData[playerid][pRadioStream], pData[playerid][pTogChat], pData[playerid][pTogMask], pData[playerid][pTogSealtbelt], pData[playerid][pTogAmmo]);
	cache_get_value_name(0, "Toggle", str);
	sscanf(str, "p<|>ddddd", TogglePlayer[playerid][ToggleDate], TogglePlayer[playerid][ToggleTime], TogglePlayer[playerid][ToggleMoney], TogglePlayer[playerid][ToggleGPS], TogglePlayer[playerid][ToggleWeb]);
	cache_get_value_name(0, "Delay", str);
	sscanf(str, "p<|>dddddddddddddd", DelayPlayer[playerid][DelaySweeper], DelayPlayer[playerid][DelayTrashmaster], DelayPlayer[playerid][DelayCourier],
	DelayPlayer[playerid][DelayBusDriver], DelayPlayer[playerid][DelayForklift], DelayPlayer[playerid][DelayFishing], DelayPlayer[playerid][DelayDelivery],
	DelayPlayer[playerid][DelayHauling], DelayPlayer[playerid][DelayLumberJack], DelayPlayer[playerid][DelaySmuggler], DelayPlayer[playerid][DelayWeaponCreate],
	DelayPlayer[playerid][DelayTraining], DelayPlayer[playerid][DelayAdvertisement], DelayPlayer[playerid][DelayMiner]);
	cache_get_value_name(0, "Bush", str);
	sscanf(str, "p<|>ddd", DelayPlayer[playerid][DelayForager], pData[playerid][pBushForager], DelayPlayer[playerid][DelayMilker]);
	cache_get_value_name_int(0, "starterpack", pData[playerid][pStarterPack]);
	
	for (new i = 0; i < 31; i++)
	{
		WeaponSettings[playerid][i][Position][0] = -0.116;
		WeaponSettings[playerid][i][Position][1] = 0.189;
		WeaponSettings[playerid][i][Position][2] = 0.088;
		WeaponSettings[playerid][i][Position][3] = 0.0;
		WeaponSettings[playerid][i][Position][4] = 44.5;
		WeaponSettings[playerid][i][Position][5] = 0.0;
		WeaponSettings[playerid][i][Bone] = 1;
		WeaponSettings[playerid][i][Hidden] = false;
	}
	WeaponTick[playerid] = 0;
	EditingWeapon[playerid] = 0;
	new string[128];
	mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM weaponsettings WHERE Owner = '%d'", pData[playerid][pID]);
	mysql_tquery(g_SQL, string, "OnWeaponsLoaded", "d", playerid);

    mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM contacts WHERE ID = '%d'", pData[playerid][pID]);
	mysql_tquery(g_SQL, string, "OnContactsLoad", "d", playerid);	

	mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `damages` WHERE `ID` = '%d'", pData[playerid][pID]);
	mysql_tquery(g_SQL, string, "OnLoadDamage", "d", playerid);	

    mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `aksesoris` WHERE `accID` = '%d' ORDER BY `accID` DESC LIMIT %d", pData[playerid][pID], MAX_ACC);
	mysql_tquery(g_SQL, string, "LoadPlayerToys", "d", playerid);

	format(string,sizeof(string),"SELECT * FROM `vehicle` WHERE `owner` = '%d' ORDER BY `id` ASC", pData[playerid][pID]);
	mysql_tquery(g_SQL, string, "LoadPlayerVehicle", "dd", playerid, g_MysqlRaceCheck[playerid]);

	//mysql_tquery(g_SQL, sprintf("SELECT * FROM `weapon_players` WHERE `userid` = '%d';", pData[playerid][pID]), "OnLoadPlayerWeapons", "d", playerid);

	//LoadPlayerVehicle(playerid);
	KillTimer(pData[playerid][LoginTimer]);
	pData[playerid][LoginTimer] = 0;
	pData[playerid][IsLoggedIn] = true;

	SetPlayerInterior(playerid, pData[playerid][pInt]);
	SetPlayerVirtualWorld(playerid, pData[playerid][pWorld]);
	SetSpawnInfo(playerid, NO_TEAM, pData[playerid][pSkin], pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ], pData[playerid][pPosA], 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	Streamer_UpdateEx(playerid, pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ], pData[playerid][pWorld], pData[playerid][pInt]);
	
	pData[playerid][pNotifSpawn] = 1;
	if(pData[playerid][pID] < 1)
	{
		Error(playerid, "Database player not found!");
		KickEx(playerid);
		return 1;
	}
	return 1;
}
