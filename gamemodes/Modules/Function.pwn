
//----------[ Function Sidejob Vehicle Respawn]----------
stock RespawnSidejobVehicle(vehicleid)
{
	SetVehicleToRespawn(vehicleid);
	if(IsACourierVeh(vehicleid) || IsABusABVeh(vehicleid) || IsABusCDVeh(vehicleid) || IsASweeperVeh(vehicleid) || IsAForkliftVeh(vehicleid) || IsVehicleTrashmaster(vehicleid))
	{
		SetVehicleFuel(vehicleid, 1000);
		RepairVehicle(vehicleid);
		SetVehicleHealth(vehicleid, 1000.0);
	}
	return 1;
}

//----------[ Function Login Register]----------

function CreateChar(playerid, name[])
{
	if(cache_num_rows() > 0)
	{
		Error(playerid, "Nama tersebut sudah di gunakan player lain");
		ShowPlayerDialog(playerid, DIALOG_CREATECHARNEW1, DIALOG_STYLE_INPUT, "Username Character","Masukan Username yang mau anda gunakan","Next","Close");
	}
	else
	{
		format(pData[playerid][pName], MAX_PLAYER_NAME, name);
		SetPlayerName(playerid, pData[playerid][pName]);
		ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Tanggal Lahir", "Masukan tanggal lahir (Tgl/Bulan/Tahun): 15/04/1998", "Enter", "Batal");
	}
    return 1;
}

function OnPlayerRegisterChar(playerid)
{
	pData[playerid][pID] = cache_insert_id();
	pData[playerid][IsLoggedIn] = true;
	if(GetPVarInt(playerid,"CreateChar1")==1)
	{
	    charData[playerid][cCharName]=pData[playerid][pID];
		new cQuery[3048];
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `ucp` SET ");
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`CharName` = '%d' ", cQuery, pData[playerid][pID]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `username` = '%s'", cQuery, charData[playerid][cName]);
		mysql_tquery(g_SQL, cQuery);
	}
	if(GetPVarInt(playerid,"CreateChar2")==1)
	{
	    charData[playerid][cCharName2]=pData[playerid][pID];
		new cQuery[3048];
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `ucp` SET ");
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`CharName2` = '%d' ", cQuery, pData[playerid][pID]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `username` = '%s'", cQuery, charData[playerid][cName]);
		mysql_tquery(g_SQL, cQuery);
	}
	if(GetPVarInt(playerid,"CreateChar3")==1)
	{
		charData[playerid][cCharName3]=pData[playerid][pID];
		new cQuery[3048];
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `ucp` SET ");
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`CharName3` = '%d' ", cQuery, pData[playerid][pID]);
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `username` = '%s'", cQuery, charData[playerid][cName]);
		mysql_tquery(g_SQL, cQuery);
	}
	pData[playerid][pnewplayer] = 0;
	pData[playerid][pPosX] = 2592.3923;
	pData[playerid][pPosY] = -2206.3506;
	pData[playerid][pPosZ] = 17.3572;
	pData[playerid][pPosA] = 180.3556;
	pData[playerid][pInt] = 0;
	pData[playerid][pWorld] = 0; 
	pData[playerid][pGender] = 0;

	format(pData[playerid][pAdminname], MAX_PLAYER_NAME, "None");
	pData[playerid][pHealth] = 100.0;
	pData[playerid][pArmour] = 0.0;
	pData[playerid][pLevel] = 1;
	pData[playerid][pHunger] = 100;
	pData[playerid][pEnergy] = 100;
	pData[playerid][pMoney] = 20000;
	pData[playerid][pBankMoney] = 10000;
	TogglePlayer[playerid][ToggleMoney] = TogglePlayer[playerid][ToggleDate] = TogglePlayer[playerid][ToggleTime] = TogglePlayer[playerid][ToggleGPS] = 1;
	TogglePlayer[playerid][ToggleWeb] = 0;
	new query[128], rand = RandomEx(111111, 999999);
	new rek = rand+pData[playerid][pID];
	mysql_format(g_SQL, query, sizeof(query), "SELECT brek FROM players WHERE brek='%d'", rek);
	mysql_tquery(g_SQL, query, "BankRek", "id", playerid, rek);
	SetSpawnInfo(playerid, NO_TEAM, 0, pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ], pData[playerid][pPosA], 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	return 1;
}

stock SetDefaultSpawn(playerid)
{
	Dialog_Show(playerid, FirstSpawn, DIALOG_STYLE_LIST, "Arrival Location", "Los Santos Airport\nLos Santos Market Station\nLos Santos Unity Station", "Choose", "Default");
    return 1;
}

Dialog:FirstSpawn(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
				SendClientMessageEx(playerid, COLOR_ARWIN, "ACCOUNT: "WHITE_E"You've arrive at Bandara Los Santos International with "GREEN_E"$50.00 {FFFFFF}in your hand and "GREEN_E"$100.00 {FFFFFF}on your Bank Account");

                SetPlayerPos(playerid, 1642.6522,-2331.9292,13.5469);
                SetPlayerFacingAngle(playerid, 359.7889);
                SetPlayerInterior(playerid, 0);
                SetPlayerVirtualWorld(playerid, 0);
            }
            case 1:
            {
                SendClientMessageEx(playerid, COLOR_ARWIN, "ACCOUNT: "WHITE_E"You've arrive at Market Station with "GREEN_E"$50.00 {FFFFFF}in your hand and "GREEN_E"$100.00 {FFFFFF}on your Bank Account");
                SetPlayerPos(playerid, 823.1542,-1341.9429,13.5172);
                SetPlayerFacingAngle(playerid, 90.7645);
                SetPlayerInterior(playerid, 0);
                SetPlayerVirtualWorld(playerid, 0);
                SetCameraBehindPlayer(playerid);
                TogglePlayerControllable(playerid, 1);
            }
            case 2:
            {
                SendClientMessageEx(playerid, COLOR_ARWIN, "ACCOUNT: "WHITE_E"You've arrive at Market Station with "GREEN_E"$50.00 {FFFFFF}in your hand and "GREEN_E"$100.00 {FFFFFF}on your Bank Account");

                SetPlayerPos(playerid, 1778.2902,-1941.7074,13.5658);
                SetPlayerFacingAngle(playerid, 359.2084);
                SetPlayerInterior(playerid, 0);
                SetPlayerVirtualWorld(playerid, 0);
                SetCameraBehindPlayer(playerid);
                TogglePlayerControllable(playerid, 1);
            }
        }
    }
    else
    {
       	SendClientMessageEx(playerid, COLOR_ARWIN, "ACCOUNT: "WHITE_E"You've arrive at Bandara Los Santos International with "GREEN_E"$50.00 {FFFFFF}in your hand and "GREEN_E"$100.00 {FFFFFF}on your Bank Account");
        SetPlayerPos(playerid, 1642.6522,-2331.9292,13.5469);
        SetPlayerFacingAngle(playerid, 359.7889);
        SetPlayerInterior(playerid, 0);
        SetPlayerVirtualWorld(playerid, 0);
        SetCameraBehindPlayer(playerid);
        TogglePlayerControllable(playerid, 1);
    }
    return 1;
}

function KickOffPD(playerid, NamaUntukDiKick[])
{
	if(cache_num_rows() < 1)
	{
		return Error(playerid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NamaUntukDiKick);
	}
	else
	{
	    new RegID;
		new rank = 0;
		new family = 0;
		new leader = 0;
		cache_get_value_index_int(0, 0, RegID);
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET faction=%d, factionrank=%d, factionlead=%d WHERE reg_id=%d", family, rank, leader, RegID);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

function KickOffSAGS(playerid, NamaUntukDiKick[])
{
	if(cache_num_rows() < 1)
	{
		return Error(playerid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NamaUntukDiKick);
	}
	else
	{
	    new RegID;
		new rank = 0;
		new family = 0;
		new leader = 0;
		cache_get_value_index_int(0, 0, RegID);
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET faction=%d, factionrank=%d, factionlead=%d WHERE reg_id=%d", family, rank, leader, RegID);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

function KickOffSAMD(playerid, NamaUntukDiKick[])
{
	if(cache_num_rows() < 1)
	{
		return Error(playerid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NamaUntukDiKick);
	}
	else
	{
	    new RegID;
		new rank = 0;
		new family = 0;
		new leader = 0;
		cache_get_value_index_int(0, 0, RegID);
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET faction=%d, factionrank=%d, factionlead=%d WHERE reg_id=%d", family, rank, leader, RegID);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

function KickOffNEWS(playerid, NamaUntukDiKick[])
{
	if(cache_num_rows() < 1)
	{
		return Error(playerid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NamaUntukDiKick);
	}
	else
	{
	    new RegID;
		new rank = 0;
		new family = 0;
		new leader = 0;
		cache_get_value_index_int(0, 0, RegID);
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET faction=%d, factionrank=%d, factionlead=%d WHERE reg_id=%d", family, rank, leader, RegID);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

function UnbanByIrwan(adminid, NamaUntukDiUnban[], ReasonUnban[])
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NamaUntukDiUnban);
	}
	else
	{
	    new RegID;
	    new unbannedbyirwan = 0;
		cache_get_value_index_int(0, 0, RegID);
		SendClientMessageToAllEx(TOMATO, "AdmCmd: %s has been unblocked by %s", NamaUntukDiUnban, pData[adminid][pAdminname]);
		SendClientMessageToAllEx(TOMATO, "Reason: %s", ReasonUnban);
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET pbanned=%d WHERE reg_id=%d", unbannedbyirwan, RegID);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

function SetName(otherplayer, playerid, nname[])
{
	if(!cache_num_rows())
	{
		new oldname[24], newname[24], query[248];
		GetPlayerName(otherplayer, oldname, sizeof(oldname));

		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET username='%s' WHERE reg_id=%d", nname, pData[otherplayer][pID]);
		mysql_tquery(g_SQL, query);

		Servers(otherplayer, "Admin %s telah mengganti nickname anda menjadi (%s)", pData[playerid][pAdminname], nname);
		SendClientMessageEx(otherplayer, COLOR_ARWIN, "NICKNAME: "WHITE_E"Pastikan anda mengingat dan mengganti nickname anda pada saat login kembali!");
		SendStaffMessage(COLOR_RED, "Admin %s telah mengganti nickname player %s(%d) menjadi %s", pData[playerid][pAdminname], oldname, otherplayer, nname);

		SetPlayerName(otherplayer, nname);
		GetPlayerName(otherplayer, newname, sizeof(newname));
		format(pData[otherplayer][pName], 52, newname);
		// House
		foreach(new h : Houses)
		{
			if(!strcmp(hData[h][hOwner], oldname, true))
   			{
   			    // Has House
   			    format(hData[h][hOwner], 24, "%s", newname);
          		mysql_format(g_SQL, query, sizeof(query), "UPDATE houses SET owner='%s' WHERE ID=%d", newname, h);
				mysql_tquery(g_SQL, query);
				House_Refresh(h);
				House_Save(h);
			}
		}
		// Bisnis
		foreach(new b : Bisnis)
		{
			if(!strcmp(bData[b][bOwner], oldname, true))
   			{
   			    // Has Business
   			    format(bData[b][bOwner], 24, "%s", newname);
          		mysql_format(g_SQL, query, sizeof(query), "UPDATE bisnis SET owner='%s' WHERE ID=%d", newname, b);
				mysql_tquery(g_SQL, query);
				Bisnis_Refresh(b);
				Bisnis_Save(b);
			}
		}
	}
	else
	{
	    // Name Exists
		Error(playerid, "The name "DARK_E"'%s' "WHITE_E"already exists in the database, please use a different name!", nname);
	}
    return 1;
}

function PhoneNumberUpdate(playerid, phone)
{
	if(!cache_num_rows())
	{
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET phone='%d' WHERE reg_id=%d", phone, pData[playerid][pID]);
		mysql_tquery(g_SQL, query);
		pData[playerid][pPhone] = phone;
		pData[playerid][pGold] -= 150;
		SendClientMessageEx(playerid, COLOR_ARWIN, "GOLD: "WHITE_E"No Phone anda telah di ubah menjadi "YELLOW_E"%d", phone);
	}
	else
	{
	    // Name Exists
		Error(playerid, "The Phone Number "DARK_E"'%d' "WHITE_E"already exists in the database, please use a different name!", phone);
		return 1;
	}
	return true;
}

function BankNumberUpdate(playerid, bank)
{
	if(!cache_num_rows())
	{
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET brek='%d' WHERE reg_id=%d", bank, pData[playerid][pID]);
		mysql_tquery(g_SQL, query);
		pData[playerid][pBankRek] = bank;
		pData[playerid][pGold] -= 150;
		SendClientMessageEx(playerid, COLOR_ARWIN, "GOLD: "WHITE_E"Bank Rekening anda telah di ubah menjadi "YELLOW_E"%d", bank);
	}
	else
	{
	    // Name Exists
		Error(playerid, "The Phone Number "DARK_E"'%d' "WHITE_E"already exists in the database, please use a different name!", bank);
		return 1;
	}
	return true;
}

function ChangeMask(playerid, mask)
{
	if(!cache_num_rows())
	{
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET mask='%d' WHERE reg_id=%d", mask, pData[playerid][pID]);
		mysql_tquery(g_SQL, query);
		pData[playerid][pMaskID] = mask;
		pData[playerid][pGold] -= 250;
		SendClientMessageEx(playerid, COLOR_ARWIN, "GOLD: "WHITE_E"No Mask anda telah di ubah menjadi "YELLOW_E"%d", mask);
	}
	else
	{
	    // Name Exists
		Error(playerid, "The Mask Number "DARK_E"'%d' "WHITE_E"already exists in the database, please use a different name!", mask);
		return 1;
	}
	return true;
}

// function ChangeName(playerid, nname[])
// {
// 	if(!cache_num_rows())
// 	{
// 		if(pData[playerid][pGold] < 500) return Error(playerid, "Not enough gold!");
// 		pData[playerid][pGold] -= 500;

// 		new oldname[24], newname[24], query[248];
// 		GetPlayerName(playerid, oldname, sizeof(oldname));

// 		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET username='%s' WHERE reg_id=%d", nname, pData[playerid][pID]);
// 		mysql_tquery(g_SQL, query);

// 		SendCustomMessage(playerid, "NAME", "Anda telah mengganti nickname anda menjadi (%s)", nname);
// 		SendClientMessageEx(playerid, COLOR_ARWIN, "NICKNAME: "WHITE_E"Pastikan anda mengingat dan mengganti nickname anda pada saat login kembali!");
// 		SendStaffMessage(COLOR_RED, "Player %s(%d) telah mengganti nickname menjadi %s(%d)", oldname, playerid, nname, playerid);

// 		SetPlayerName(playerid, nname);
// 		GetPlayerName(playerid, newname, sizeof(newname));
// 		format(pData[playerid][pName], 52, newname);
// 		// House
// 		foreach(new h : Houses)
// 		{
// 			if(!strcmp(hData[h][hOwner], oldname, true))
//    			{
//    			    // Has House
//    			    format(hData[h][hOwner], 24, "%s", newname);
//           		mysql_format(g_SQL, query, sizeof(query), "UPDATE houses SET owner='%s' WHERE ID=%d", newname, h);
// 				mysql_tquery(g_SQL, query);
// 				House_Refresh(h);
// 				House_Save(h);
// 			}
// 		}
// 		// Bisnis
// 		foreach(new b : Bisnis)
// 		{
// 			if(!strcmp(bData[b][bOwner], oldname, true))
//    			{
//    			    // Has Business
//    			    format(bData[b][bOwner], 24, "%s", newname);
//           		mysql_format(g_SQL, query, sizeof(query), "UPDATE bisnis SET owner='%s' WHERE ID=%d", newname, b);
// 				mysql_tquery(g_SQL, query);
// 				Bisnis_Refresh(b);
// 				Bisnis_Save(b);
// 			}
// 		}
// 	}
// 	else
// 	{
// 	    // Name Exists
// 		Error(playerid, "The name "DARK_E"'%s' "WHITE_E"already exists in the database, please use a different name!", nname);
// 		return 1;
// 	}
//     return 1;
// }

function ChangePlayerPassword(admin, cPlayer[], newpass[])
{
	if(cache_num_rows() > 0)
	{
		new query[512], pass[65], salt[16];
		Servers(admin, "Password for %s has been set to \"%s\"", cPlayer, newpass);

		for (new i = 0; i < 16; i++) salt[i] = random(94) + 33;
		SHA256_PassHash(newpass, salt, pass, 65);

		mysql_format(g_SQL, query, sizeof(query), "UPDATE ucp SET password='%s', salt='%e' WHERE username='%s'", pass, salt, cPlayer);
		mysql_tquery(g_SQL, query);
	}
	else
	{
	    // Name Exists
		Error(admin, "The name"DARK_E"'%s' "WHITE_E"doesn't exist in the database!", cPlayer);
	}
    return 1;
}

function OWarnPlayer(adminid, NameToWarn[], warnReason[])
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NameToWarn);
	}
	else
	{
	    new RegID, warn;
		cache_get_value_index_int(0, 0, RegID);
		cache_get_value_index_int(0, 1, warn);
		AddPlayerWarnsLog(adminid, RegID, warnReason, 2);
		SendClientMessageToAllEx(TOMATO, "Admcmd: %s has been remote warned by %s total warns: %d",  NameToWarn, pData[adminid][pAdminname], warn+1);
        SendClientMessageToAllEx(TOMATO, "Reason: %s", warnReason);

		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET warn=%d WHERE reg_id=%d", warn+1, RegID);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

function OfflineMask(adminid, NameToWarn)
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Mask "GREY2_E"'%d' "WHITE_E"does not exist.", NameToWarn);
	}
	else
	{
	    new RegID;
		cache_get_value_index_int(0, 0, RegID);
		new Cache:checkMask, query[128];
		format(query, sizeof(query), "SELECT * FROM `username` WHERE `reg_id`='%d'", RegID);
		checkMask = mysql_query(g_SQL, query);
		
		new rows = cache_num_rows(), fname[128];
		
		if(rows)
		{
			new fam[128];
			cache_get_value_name(0, "username", fam);
			format(fname, 128, fam);
		}
		SendClientMessageEx(adminid, COLOR_ARWIN,"MASK: "WHITE_E"Username "YELLOW_E"%s "WHITE_E"MaskID"YELLOW_E"%d", fname, NameToWarn);
		cache_delete(checkMask);
	}
	return 1;
}

function OnResolveMask(playerid,number)
{
    new
        rows = cache_num_rows();

    if(!rows)
        return Error(playerid, "There is no account linked with the specified name.");

    new name[MAX_PLAYER_NAME+1];

    cache_get_value(0, "username", name);

    SendClientMessageEx(playerid, COLOR_WHITE, "MASK: Owner of "AQUA_E"Mask %d "WHITE_E"is "YELLOW_E"%s",number, name);

    return 1;
}

function OJailPlayer(adminid, NameToJail[], jailReason[], jailTime)
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NameToJail);
	}
	else
	{
	    new fixbugjailbyirwan = 1;
	    new RegID, JailMinutes = jailTime * 60;
		cache_get_value_index_int(0, 0, RegID);
		AddPlayerWarnsLog(adminid, RegID, jailReason, 1);
		SendClientMessageToAllEx(TOMATO, "AdmCmd: %s has jailed %s for %d minute(s)", pData[adminid][pAdminname], NameToJail, jailTime);
		SendClientMessageToAllEx(TOMATO, "Reason: %s", jailReason);
		new query[512];  
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET jail=%d, jail_time=%d WHERE reg_id=%d", fixbugjailbyirwan, JailMinutes, RegID);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

function SetCSPlayer(adminid, NameToSetcs[])
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NameToSetcs);
	}
	else
	{
	    new setcsbyanang = 1;
	    new RegID;
		cache_get_value_index_int(0, 0, RegID);

		SendStaffMessage(COLOR_RED, "AdmCmd: "GREY2_E"Admin %s telah approved Char Story player %s", pData[adminid][pAdminname], NameToSetcs);
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET cschar=%d, WHERE reg_id=%d", setcsbyanang, RegID);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

function UnsetCSPlayer(adminid, NameToUnSetcs[])
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NameToUnSetcs);
	}
	else
	{
	    new unsetcsbyanang = 0;
	    new RegID;
		cache_get_value_index_int(0, 0, RegID);

		SendStaffMessage(COLOR_RED, "AdmCmd: "GREY2_E"Admin %s telah menghapus Char Story player %s", pData[adminid][pAdminname], NameToUnSetcs);
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET cschar=%d, WHERE reg_id=%d", unsetcsbyanang, RegID);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

function ObanByIrwan(adminid, NamaUntukDiOban[], OBanReason[])
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NamaUntukDiOban);
	}
	else
	{
	    new RegID;
	    new obannedbyirwan = 1;
		cache_get_value_index_int(0, 0, RegID);
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET pbanned=%d, pbanreason='%s', pbanby='%s' WHERE reg_id=%d", obannedbyirwan, OBanReason, pData[adminid][pAdminname], RegID);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

function oMaxObject(adminid, NamaUntukDiOban[], no)
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NamaUntukDiOban);
	}
	else
	{
	    new RegID;
		cache_get_value_index_int(0, 0, RegID);
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET streamer=%d WHERE reg_id=%d", no, RegID);
		mysql_tquery(g_SQL, query);
	}
	return 1;
}

function BankRek(playerid, brek)
{
	if(cache_num_rows() > 0)
	{
		//Rekening Exist
		new query[128], rand = RandomEx(111111111, 999999999);
		new rek = rand+pData[playerid][pID];
		mysql_format(g_SQL, query, sizeof(query), "SELECT brek FROM players WHERE brek='%d'", rek);
		mysql_tquery(g_SQL, query, "BankRek", "is", playerid, rek);
		SendCustomMessage(playerid, "BANK", "Your Bank rekening number is same with someone. We will research new.");
	}
	else
	{
		new query[128];
	    mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET brek='%d' WHERE reg_id=%d", brek, pData[playerid][pID]);
		mysql_tquery(g_SQL, query);
		pData[playerid][pBankRek] = brek;
	}
    return true;
}

// function PhoneNumber(playerid, phone)
// {
// 	if(cache_num_rows() > 0)
// 	{
// 		//Rekening Exist
// 		new query[128], rand = RandomEx(11111111, 99999999);
// 		new phones = rand+pData[playerid][pID];
// 		mysql_format(g_SQL, query, sizeof(query), "SELECT phone FROM players WHERE phone='%d'", phones);
// 		mysql_tquery(g_SQL, query, "PhoneNumber", "is", playerid, phones);
// 		SendCustomMessage(playerid, "PHONE", "Your Phone number is same with someone. We will research new.");
// 	}
// 	else
// 	{
// 		new query[128];
// 	    mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET phone='%d' WHERE reg_id=%d", phone, pData[playerid][pID]);
// 		mysql_tquery(g_SQL, query);
// 		pData[playerid][pPhone] = phone;
// 	}
//     return true;
// }

function OnLoginTimeout(playerid)
{
	pData[playerid][LoginTimer] = 0;

	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Login", "You have been kicked for taking too long to login successfully to your account.", "Okay", "");
	KickEx(playerid);
	return 1;
}


function _KickPlayerDelayed(playerid)
{
	Kick(playerid);
	return 1;
}

// Info textdraw timer for hiding the textdraw
function InfoTD_MSG(playerid, ms_time, text[])
{
	if(GetPVarInt(playerid, "InfoTDshown") != -1)
	{
	    PlayerTextDrawHide(playerid, InfoTD[playerid]);
	    KillTimer(GetPVarInt(playerid, "InfoTDshown"));
	}

    PlayerTextDrawSetString(playerid, InfoTD[playerid], text);
    PlayerTextDrawShow(playerid, InfoTD[playerid]);
	SetPVarInt(playerid, "InfoTDshown", SetTimerEx("InfoTD_Hide", ms_time, false, "i", playerid));
}

function InfoTD_Hide(playerid)
{
	SetPVarInt(playerid, "InfoTDshown", -1);
	PlayerTextDrawHide(playerid, InfoTD[playerid]);
}

//---------[Admin Function ]----------

function a_ChangeAdminName(otherplayer, playerid, nname[])
{
	if(cache_num_rows() > 0)
	{
		// Name Exists
		Error(playerid, "The name "DARK_E"'%s' "GREY_E"already exists in the database, please use a different name!", nname);
	}
	else
	{
		new query[512];
	    format(query, sizeof(query), "UPDATE players SET adminname='%e' WHERE reg_id=%d", nname, pData[otherplayer][pID]);
		mysql_tquery(g_SQL, query);
		format(pData[otherplayer][pAdminname], MAX_PLAYER_NAME, "%s", nname);
		SendCustomMessage(playerid, "NAME", "You has set admin name player %s to %s", pData[otherplayer][pName], nname);
	}
    return true;
}

function LoadStats(playerid, PlayersName[])
{
	if(!cache_num_rows())
	{
		Error(playerid, "Account '%s' does not exist.", PlayersName);
	}
	else
	{
		new email[40], admin, helper, level, levelup, vip, viptime, coin, regdate[40], lastlogin[40], money, bmoney, brek,
			jam, menit, detik, gender, age[40], faction, family, warn, job, job2, int, world;
		cache_get_value_index(0, 0, email);
		cache_get_value_index_int(0, 1, admin);
		cache_get_value_index_int(0, 2, helper);
		cache_get_value_index_int(0, 3, level);
		cache_get_value_index_int(0, 4, levelup);
		cache_get_value_index_int(0, 5, vip);
		cache_get_value_index_int(0, 6, viptime);
		cache_get_value_index(0, 8, regdate);
		cache_get_value_index(0, 9, lastlogin);
		cache_get_value_index_int(0, 10, money);
		cache_get_value_index_int(0, 11, bmoney);
		cache_get_value_index_int(0, 12, brek);
		cache_get_value_index_int(0, 13, jam);
		cache_get_value_index_int(0, 14, menit);
		cache_get_value_index_int(0, 15, detik);
		cache_get_value_index_int(0, 16, gender);
		cache_get_value_index(0, 17, age);
		cache_get_value_index_int(0, 18, faction);
		cache_get_value_index_int(0, 19, family);
		cache_get_value_index_int(0, 20, warn);
		cache_get_value_index_int(0, 21, job);
		cache_get_value_index_int(0, 22, job2);
		cache_get_value_index_int(0, 23, int);
		cache_get_value_index_int(0, 24, world);
		
		new header[248], scoremath = ((level)*8), fac[24], Cache:checkfamily, gstr[2468], query[128];
	
		if(faction == 1)
		{
			fac = "SAPD";
		}
		else if(faction == 2)
		{
			fac = "SAGS";
		}
		else if(faction == 3)
		{
			fac = "SAMD";
		}
		else if(faction == 4)
		{
			fac = "SANA";
		}
		else
		{
			fac = "None";
		}
		
		new name[40];
		if(admin == 1)
		{
			name = ""RED_E"Staff Administrator(1)";
		}
		else if(admin == 2)
		{
			name = ""RED_E"Administrator(2)";
		}
		else if(admin == 3)
		{
			name = ""RED_E"Senior Admin(3)";
		}
		else if(admin == 4)
		{
			name = ""RED_E"Lead Admin(4)";
		}
		else if(admin== 5)
		{
			name = ""RED_E"Head Admin(5)";
		}
		else if(helper >= 1 && admin == 0)
		{
			name = ""GREEN_E"Helper";
		}
		else
		{
			name = "None";
		}
		
		new name1[30];
		if(vip == 1)
		{
			name1 = ""LG_E"Regular(1)";
		}
		else if(vip == 2)
		{
			name1 = ""YELLOW_E"Premium(2)";
		}
		else if(vip == 3)
		{
			name1 = ""PURPLE_E"VIP Player(3)";
		}
		else
		{
			name1 = "None";
		}
		
		format(query, sizeof(query), "SELECT * FROM `familys` WHERE `ID`='%d'", family);
		checkfamily = mysql_query(g_SQL, query);
		
		new rows = cache_num_rows(), fname[128];
		
		if(rows)
		{
			new fam[128];
			cache_get_value_name(0, "name", fam);
			format(fname, 128, fam);
		}
		else
		{
			format(fname, 128, "None");
		}
		
		format(header,sizeof(header),"Stats:"YELLOW_E"%s"WHITE_E" ("BLUE_E"%s"WHITE_E")", PlayersName, ReturnTime());
		format(gstr,sizeof(gstr),""RED_E"In Character"WHITE_E"\n");
		format(gstr,sizeof(gstr),"%sGender: [%s] | Money: ["GREEN_E"$%s"WHITE_E"] | Bank: ["GREEN_E"$%s"WHITE_E"] | Rekening Bank: [%d] | Phone Number: [None]\n", gstr,(gender == 2) ? ("Female") : ("Male") , FormatMoney(money), FormatMoney(bmoney), brek);
		format(gstr,sizeof(gstr),"%sBirdthdate: [%s] | Job: [None] | Job2: [None] | Faction: [%s] | Family: [%s]\n\n", gstr, age, fac, fname);
		format(gstr,sizeof(gstr),"%s"RED_E"Out of Character"WHITE_E"\n",gstr);
		format(gstr,sizeof(gstr),"%sLevel score: [%d/%d] | Email: [%s] | Warning:[%d/10] | Last Login: [%s]\n", gstr, levelup, scoremath, email, warn, lastlogin);
		format(gstr,sizeof(gstr),"%sStaff: [%s"WHITE_E"] | Time Played: [%d hour(s) %d minute(s) %02d second(s)] | Gold Coin: [%d]\n", gstr, name, jam, menit, detik, coin);
		if(vip != 0)
		{
			format(gstr,sizeof(gstr),"%sInterior: [%d] | Virtual World: [%d] | Register Date: [%s] | VIP Level: [%s"WHITE_E"] | VIP Time: [%s]", gstr, int, world, regdate, name1, ConvertTimestamp(Timestamp:viptime));
		}
		else
		{
			format(gstr,sizeof(gstr),"%sInterior: [%d] | Virtual World: [%d] | Register Date: [%s] | VIP Level: [%s"WHITE_E"] | VIP Time: [None]", gstr, int, world, regdate, name1);
		}
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, header, gstr, "Close", "");
		
		cache_delete(checkfamily);
	}
	return true;
}

function SetPlayerArrest(playerid)
{
	SetPlayerPositionEx(playerid, -304.14, 1871.05, 29.89, 353.84);
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 100);
	PlayerPlaySound(playerid, 1186, 0, 0, 0);
    ResetWeapons(playerid);
	ResetNameTag(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	pData[playerid][pCuffed] = 0;
	pData[playerid][pInBiz] = -1;
	pData[playerid][pInHouse] = -1;
	pData[playerid][pInDoor] = -1;
	PlayerTextDrawShow(playerid, JailTD[playerid]);
	return true;
}

function JailPlayer(playerid)
{
	new rand = random(4);
	// SetPlayerPositionEx(playerid, -18.60, 2322.81, 24.30, 332.19, 2000);
	switch(rand)
	{

		case 0: SetPlayerPos(playerid, -18.60, 2322.81, 24.30);
		case 1: SetPlayerPos(playerid, -27.71, 2320.70, 24.30);
		case 2: SetPlayerPos(playerid, -10.67, 2329.07, 24.30);
		case 3: SetPlayerPos(playerid, -9.65, 2336.90, 24.30);
	}
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 200);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	pData[playerid][pInBiz] = -1;
	pData[playerid][pInHouse] = -1;
	pData[playerid][pInDoor] = -1;
	pData[playerid][pCuffed] = 0;
	PlayerPlaySound(playerid, 1186, 0, 0, 0);
	PlayerTextDrawShow(playerid, JailTD[playerid]);
	return true;
}

//-------------[ Player Update Function ]----------

function DragUpdate(playerid, targetid)
{
    if(pData[targetid][pDragged] && pData[targetid][pDraggedBy] == playerid)
    {
        static
        Float:fX,
        Float:fY,
        Float:fZ,
        Float:fAngle;

        GetPlayerPos(playerid, fX, fY, fZ);
        GetPlayerFacingAngle(playerid, fAngle);

        fX -= 3.0 * floatsin(-fAngle, degrees);
        fY -= 3.0 * floatcos(-fAngle, degrees);

        SetPlayerPos(targetid, fX, fY, fZ);
        SetPlayerInterior(targetid, GetPlayerInterior(playerid));
        SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));
		ApplyAnimation(targetid,"PED","WALK_civi",4.1,1,1,1,1,1);
    }
    return 1;
}

function UnfreezePee(playerid)
{
    TogglePlayerControllable(playerid, 1);
    ClearAnimations(playerid);
	StopLoopingAnim(playerid);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	return 1;
}

function UnfreezeSleep(playerid)
{
    TogglePlayerControllable(playerid, 1);
    pData[playerid][pEnergy] = 100;
	pData[playerid][pHunger] -= 3;
    ClearAnimations(playerid);
	StopLoopingAnim(playerid);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	InfoTD_MSG(playerid, 6000, "Sleeping Done!");
	return 1;
}

function RefullCar(playerid, vehicleid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	//if(!IsValidVehicle(vehicleid)) return 0;
	if(GetNearestVehicleToPlayer(playerid, 3.8, false) == vehicleid)
    {
		if(pData[playerid][pActivityTime] >= 100 && IsValidVehicle(vehicleid))
		{
			new fuels = GetVehicleFuel(vehicleid);
			SetVehicleFuel(vehicleid, fuels+300);
			InfoTD_MSG(playerid, 8000, "Refulling done!");
			//SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has successfully refulling the vehicle.", ReturnName(playerid));
			KillTimer(pData[playerid][pActivity]);
			pData[playerid][pActivityTime] = 0;
			for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
		}
		else if(pData[playerid][pActivityTime] < 100 && IsValidVehicle(vehicleid))
		{
			pData[playerid][pActivityTime] += 5;
			SetProgressBar(playerid, pData[playerid][pActivityTime]);
		}
		else
		{
			Error(playerid, "Refulling fail! Anda tidak berada didekat kendaraan tersebut!");
			KillTimer(pData[playerid][pActivity]);
			pData[playerid][pActivityTime] = 0;
			for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
		}
	}
	else
	{
		Error(playerid, "Refulling fail! Anda tidak berada didekat kendaraan tersebut!");
		KillTimer(pData[playerid][pActivity]);
		pData[playerid][pActivityTime] = 0;
		for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
		return 1;
	}
	return 1;
}

//Bank
function SearchRek(playerid, rek)
{
	if(!cache_num_rows())
	{
		// Rekening tidak ada
		Error(playerid, "Rekening bank "YELLOW_E"'%d' "WHITE_E"tidak terdaftar!", rek);
		pData[playerid][pTransfer] = 0;
	    
	}
	else
	{
	    // Proceed
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "SELECT username,brek FROM players WHERE brek='%d'", rek);
		mysql_tquery(g_SQL, query, "SearchRek2", "id", playerid, rek);
	}
}

function SearchRek2(playerid, rek)
{
	if(cache_num_rows())
	{
		new name[128], brek, mstr[128];
		cache_get_value_index(0, 0, name);
		cache_get_value_index_int(0, 1, brek);
		
		//format(pData[playerid][pTransferName], 128, "%s" name);
		pData[playerid][pTransferName] = name;
		pData[playerid][pTransferRek] = brek;
		format(mstr, sizeof(mstr), ""WHITE_E"No Rek Target: "YELLOW_E"%d\n"WHITE_E"Nama Target: "YELLOW_E"%s\n"WHITE_E"Jumlah: "GREEN_E"%s\n\n"WHITE_E"Anda yakin akan melanjutkan mentransfer?", brek, name, FormatMoney(pData[playerid][pTransfer]));
		ShowPlayerDialog(playerid, DIALOG_BANKCONFIRM, DIALOG_STYLE_MSGBOX, ""LB_E"Bank", mstr, "Transfer", "Cancel");
	}
	return true;
}

//----------[ JOB FUNCTION ]-------------

//Server Timer
function pCountDown()
{
	Count--;
	if(0 >= Count)
	{
		Count = -1;
		KillTimer(countTimer);
		foreach(new ii : Player)
		{
 			if(showCD[ii] == 1)
   			{
   				GameTextForPlayer(ii, "~w~GO~r~!~g~!~b~!", 2500, 6);
   				PlayerPlaySound(ii, 1057, 0, 0, 0);
   				showCD[ii] = 0;
			}
		}
	}
	else
	{
		foreach(new ii : Player)
		{
 			if(showCD[ii] == 1)
   			{
				GameTextForPlayer(ii, CountText[Count-1], 2500, 6);
				PlayerPlaySound(ii, 1056, 0, 0, 0);
   			}
		}
	}
	return 1;
}

//----------[ Other Function ]-----------

function SetPlayerToUnfreeze(playerid, Float:x, Float:y, Float:z, Float:a)
{
    if(!IsPlayerInRangeOfPoint(playerid, 15.0, x, y, z))
        return 0;

    pData[playerid][pFreeze] = 0;
	TogglePlayerControllable(playerid, 1);
    return 1;
}

function PlayerUnfreeze(playerid)
{
    pData[playerid][pFreeze] = 0;
	Streamer_ToggleIdleUpdate(playerid,0);
	TogglePlayerControllable(playerid, 1);
	KillTimer(pData[playerid][pFreezeTimer1]);
    return 1;
}

function SetVehicleToUnfreeze(playerid, vehicleid, Float:x, Float:y, Float:z, Float:a)
{
    if(!IsPlayerInRangeOfPoint(playerid, 15.0, x, y, z))
        return 0;

    pData[playerid][pFreeze] = 0;
    SetVehiclePos(vehicleid, x, y, z);
	SetVehicleZAngle(vehicleid, a);
    TogglePlayerControllable(playerid, 1);
    return 1;
}

function HideTextDrawNotif(playerid)
{
	TextDrawHideForPlayer(playerid, notifTD[0]);
	TextDrawHideForPlayer(playerid, notifTD[1]);
	return 1;
}

function EnterExitTimer(playerid)
{
	TogglePlayerControllable(playerid, 1);
	return 1;
}

function CigarStop(playerid)
{
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    return 1;
}

function DrugEffectGone(playerid)
{
    new time[3];
    new pogoda;

    gettime(time[0], time[1], time[2]);
    SetPlayerTime(playerid, time[0], time[1]);
    SetPlayerWeather(playerid, pogoda);
    SetPlayerDrunkLevel(playerid, 0);
    return 1;
}

function OOCNews(color,String[])
{
	foreach(new i : Player)
	{
		if(!gNews[i])
		{
			SendClientMessageEx(i, color, String);
		}
	}
}

function SAPDLobbyDoorClose()
{
	MoveDynamicObject(SAPDLobbyDoor[0], 1327.769531, 728.931030, 110.300323, 3);
	return 1;
}

function StealingCloseDoor()
{
	MoveDynamicObject(gatestealingjobs, 1534.755371, -1451.642211, 14.615850, 3);
	return 1;
}

function oUnBanUCP(adminid, NamaUntukDiOban[])
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NamaUntukDiOban);
	}
	else
	{
	    new RegID;
	    new obannedbyirwan = 0;
		new reason[511];
		reason = "";
		cache_get_value_index_int(0, 0, RegID);
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE ucp SET banned=%d, bannedreason='%s' WHERE reg_id=%d", obannedbyirwan, reason, RegID);
		mysql_tquery(g_SQL, query);
		SendClientMessageToAllEx(TOMATO, "AdmCmd: %s has been unblocked UCP account %s", pData[adminid][pAdminname], NamaUntukDiOban);
	}
	return 1;
}

function oBanUCP(adminid, NamaUntukDiOban[], OBanReason[])
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", NamaUntukDiOban);
	}
	else
	{
	    new RegID;
	    new obannedbyirwan = 1;
		new reason[511];
		cache_get_value_index_int(0, 0, RegID);
		format(reason, 128, "%s [%s] %s", OBanReason, pData[adminid][pAdminname]);
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE ucp SET banned=%d, bannedreason='%s' WHERE reg_id=%d", obannedbyirwan, reason, RegID);
		mysql_tquery(g_SQL, query);
		SendClientMessageToAllEx(TOMATO, "AdmCmd: UCP %s has been blocked by %s", NamaUntukDiOban, pData[adminid][pAdminname]);
    	SendClientMessageToAllEx(TOMATO, "AdmCmd: Reason: %s", OBanReason);
	}
	return 1;
}

function GetNameUCP12(playerid, nameucp[])
{
	new name1, name2, name3;
	if(cache_num_rows() > 0)
	{
		cache_get_value_name_int(0, "CharName", name1);	
		cache_get_value_name_int(0, "CharName2", name2);	
		cache_get_value_name_int(0, "CharName3", name3);	
		new query[128];
		format(query,sizeof(query),"SELECT * FROM `players` WHERE `reg_id` = '%d'",name1);
		mysql_tquery(g_SQL,query, "CNUCP1", "i", playerid);
		
		format(query,sizeof(query),"SELECT * FROM `players` WHERE `reg_id` = '%d'",name2);
		mysql_tquery(g_SQL,query, "CNUCP2", "i", playerid);

		format(query,sizeof(query),"SELECT * FROM `players` WHERE `reg_id` = '%d'",name3);
		mysql_tquery(g_SQL,query, "CNUCP3", "i", playerid);
		format(NameUCP[playerid], MAX_PLAYER_NAME, "%s", nameucp);
	}
	return 1;
}

function CNUCP1(playerid)
{
	new name1[MAX_PLAYER_NAME];
 	if(cache_num_rows() > 0)
 	{
	    cache_get_value_name(0, "username", name1);
		format(CharNameUCP1[playerid], MAX_PLAYER_NAME, "%s", name1);
 	}
	return 1;
}

function CNUCP2(playerid)
{
	new name2[MAX_PLAYER_NAME];
 	if(cache_num_rows() > 0)
 	{
	    cache_get_value_name(0, "username", name2);
		format(CharNameUCP2[playerid], MAX_PLAYER_NAME, "%s", name2);
 	}
	return 1;
}

function CNUCP3(playerid)
{
	new name3[MAX_PLAYER_NAME];
 	if(cache_num_rows() > 0)
 	{
	    cache_get_value_name(0, "username", name3);
		format(CharNameUCP3[playerid], MAX_PLAYER_NAME, "%s", name3);
 	}
	EndLoadCharName(playerid);
	return 1;
}

function EndLoadCharName(playerid)
{
	SendClientMessageEx(playerid, COLOR_ARWIN, ""YELLOW_E"UCP: {00FFFF}%s "YELLOW_E"Character: {00FFFF}%s "YELLOW_E"Character: {00FFFF}%s "YELLOW_E"Character: {00FFFF}%s", NameUCP[playerid], CharNameUCP1[playerid], CharNameUCP2[playerid], CharNameUCP3[playerid]);
	return 1;
}

function OfflineSetFaction(adminid, targetName[], factionid, rank)
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", targetName);
	}

	new regid, currentFamily, username[MAX_PLAYER_NAME], query[256];
	cache_get_value_name_int(0, "reg_id", regid);
	cache_get_value_name_int(0, "family", currentFamily);
	cache_get_value_name(0, "username", username);

	if(currentFamily != -1)
	{
		return Error(adminid, "Player tersebut sudah bergabung family");
	}

	mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET faction=%d, factionrank=%d WHERE reg_id=%d", factionid, rank, regid);
	mysql_tquery(g_SQL, query);

	if(factionid == 0)
	{
		Servers(adminid, "You have removed %s's from faction.", username);
	}
	else
	{
		Servers(adminid, "You have set offline player %s's faction ID %d with rank %d.", username, factionid, rank);
	}
	return 1;
}

function OfflineSetAdmin(adminid, targetName[], adminLevel)
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Account "GREY2_E"'%s' "WHITE_E"does not exist.", targetName);
	}

	new regid, username[MAX_PLAYER_NAME], query[128];
	cache_get_value_name_int(0, "reg_id", regid);
	cache_get_value_name(0, "username", username);

	mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET admin=%d WHERE reg_id=%d", adminLevel, regid);
	mysql_tquery(g_SQL, query);
	Servers(adminid, "You has set offline admin level %s to level %d", username, adminLevel);
	return 1;
}

function OfflineCheckUCP(adminid, keyword[])
{
	if(cache_num_rows() < 1)
	{
		return Error(adminid, "Character/ID "GREY2_E"'%s' "WHITE_E"does not exist.", keyword);
	}

	new regid, username[MAX_PLAYER_NAME], ucpname[MAX_PLAYER_NAME];
	cache_get_value_name_int(0, "reg_id", regid);
	cache_get_value_name(0, "username", username);
	cache_get_value_name(0, "ucpname", ucpname);

	if(isnull(ucpname))
	{
		format(ucpname, sizeof(ucpname), "Unknown");
	}

	SendClientMessageEx(adminid, COLOR_ARWIN, "UCP: "YELLOW_E"Character: {00FFFF}%s(pid: %d) "YELLOW_E"UCP: {00FFFF}%s", username, regid, ucpname);
	return 1;
}

function OfflineCheckUCPList(playerid, ucpname[])
{
	new name1, name2, name3;
	format(NameUCP[playerid], MAX_PLAYER_NAME, "%s", ucpname);
	format(CharNameUCP1[playerid], MAX_PLAYER_NAME, "-");
	format(CharNameUCP2[playerid], MAX_PLAYER_NAME, "-");
	format(CharNameUCP3[playerid], MAX_PLAYER_NAME, "-");

	if(cache_num_rows() < 1)
	{
		return Error(playerid, "UCP "GREY2_E"'%s' "WHITE_E"does not exist.", ucpname);
	}

	cache_get_value_name_int(0, "CharName", name1);
	cache_get_value_name_int(0, "CharName2", name2);
	cache_get_value_name_int(0, "CharName3", name3);

	new query[128], Cache:charCache;
	if(name1 > 0)
	{
		format(query, sizeof(query), "SELECT username FROM `players` WHERE `reg_id` = '%d'", name1);
		charCache = mysql_query(g_SQL, query);
		if(cache_num_rows() > 0) cache_get_value_name(0, "username", CharNameUCP1[playerid], MAX_PLAYER_NAME);
		cache_delete(charCache);
	}
	if(name2 > 0)
	{
		format(query, sizeof(query), "SELECT username FROM `players` WHERE `reg_id` = '%d'", name2);
		charCache = mysql_query(g_SQL, query);
		if(cache_num_rows() > 0) cache_get_value_name(0, "username", CharNameUCP2[playerid], MAX_PLAYER_NAME);
		cache_delete(charCache);
	}
	if(name3 > 0)
	{
		format(query, sizeof(query), "SELECT username FROM `players` WHERE `reg_id` = '%d'", name3);
		charCache = mysql_query(g_SQL, query);
		if(cache_num_rows() > 0) cache_get_value_name(0, "username", CharNameUCP3[playerid], MAX_PLAYER_NAME);
		cache_delete(charCache);
	}
	return EndOfflineCheckUCPList(playerid);
}

function EndOfflineCheckUCPList(playerid)
{
	foreach(new i : Player)
	{
		if(!strcmp(ReturnName(i), CharNameUCP1[playerid], true) || !strcmp(ReturnName(i), CharNameUCP2[playerid], true) || !strcmp(ReturnName(i), CharNameUCP3[playerid], true))
		{
			return Error(playerid, "%s(ID:%d) sedang online!", ReturnName(i), i);
		}
	}

	SendClientMessageEx(playerid, COLOR_ARWIN, ""YELLOW_E"UCP: {00FFFF}%s "YELLOW_E"Character 1: {00FFFF}%s "YELLOW_E"Character 2: {00FFFF}%s "YELLOW_E"Character 3: {00FFFF}%s", NameUCP[playerid], CharNameUCP1[playerid], CharNameUCP2[playerid], CharNameUCP3[playerid]);
	SendClientMessageEx(playerid, COLOR_ARWIN, ""YELLOW_E"Gunakan {00FFFF}/ostats [Nama_Character] "YELLOW_E"untuk cek stats karakter offline.");
	return 1;
}

