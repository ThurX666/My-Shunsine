
CMD:syow(playerid, params[])
{
	new weaponid = GetWeapon(playerid);
	
	new name[20], give[128];
	if(sscanf(params, "s[20]S()[128]", name, give))
		return Usage(playerid, "/syow [pos/bone/hide]");

	if(!strcmp(name, "pos", true))
	{
		new index = (weaponid >= 22 && weaponid <= 38) ? (weaponid - 22) : (weaponid + 15);
		if (!weaponid) return SendClientMessageEx(playerid, COLOR_ARWIN, "SYOW: "WHITE_E"You are not holding a weapon.");
		if (EditingWeapon[playerid]) return SendClientMessageEx(playerid, COLOR_ARWIN, "SYOW: "WHITE_E"You are already editing a weapon.");
		if (WeaponSettings[playerid][index][Hidden]) return SendClientMessageEx(playerid, COLOR_ARWIN, "SYOW: "WHITE_E"You cannot adjust a hidden weapon.");
		SetPlayerArmedWeapon(playerid, 0);
	  	Dialog_Show(playerid, WepPosition, DIALOG_STYLE_LIST, "Weapon Position", "For PC\nFor Android", "Select", "Close");
		EditingWeapon[playerid] = weaponid;
	}
	else if (!strcmp(name, "bone", true))
	{
		if (!weaponid)
			return SendClientMessageEx(playerid, COLOR_ARWIN, "SYOW: "WHITE_E"You are not holding a weapon.");

		if (EditingWeapon[playerid])
			return SendClientMessageEx(playerid, COLOR_ARWIN, "SYOW: "WHITE_E"You are already editing a weapon");

		ShowPlayerDialog(playerid, DIALOG_EDITBONE, DIALOG_STYLE_LIST, "Bone", "Spine\nHead\nLeft upper arm\nRight upper arm\nLeft hand\nRight hand\nLeft thigh\nRight thigh\nLeft foot\nRight foot\nRight calf\nLeft calf\nLeft forearm\nRight forearm\nLeft shoulder\nRight shoulder\nNeck\nJaw", "Choose", "Cancel");
		EditingWeapon[playerid] = weaponid;
	}
	else if (!strcmp(name, "hide", true))
	{
		if (!weaponid)
			return SendClientMessageEx(playerid, COLOR_ARWIN, "SYOW: "WHITE_E"You are not holding a weapon.");

		if (!IsWeaponWearable(weaponid))
			return SendClientMessageEx(playerid, COLOR_ARWIN, "SYOW: "WHITE_E"This weapon cannot be edited");
			
		if (EditingWeapon[playerid])
			return SendClientMessageEx(playerid, COLOR_ARWIN, "SYOW: "WHITE_E"You are already editing a weapon");

		if (!IsWeaponHideable(weaponid))
			return SendClientMessageEx(playerid, COLOR_ARWIN, "SYOW: "WHITE_E"You cannot adjust a hidden weapon.");

		new index = (weaponid >= 22 && weaponid <= 38) ? (weaponid - 22) : (weaponid + 15), weaponname[18], string[150];

		GetWeaponName(weaponid, weaponname, sizeof(weaponname));
	   
		if (WeaponSettings[playerid][index][Hidden])
		{
			SendClientMessageEx(playerid, COLOR_ARWIN, "SYOW: "WHITE_E"You have set your "AQUA_E"%s "WHITE_E"to show.", weaponname);
			WeaponSettings[playerid][index][Hidden] = false;
		}
		else
		{
			if (IsPlayerAttachedObjectSlotUsed(playerid, GetWeaponObjectSlot(weaponid)))
				RemovePlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid));

			SendClientMessageEx(playerid, COLOR_ARWIN, "SYOW: "WHITE_E"You have set your "AQUA_E"%s "WHITE_E"not to show.", weaponname);
			WeaponSettings[playerid][index][Hidden] = true;
		}
	   
		mysql_format(g_SQL, string, sizeof(string), "INSERT INTO weaponsettings (Owner, WeaponID, Hidden) VALUES ('%d', %d, %d) ON DUPLICATE KEY UPDATE Hidden = VALUES(Hidden)", pData[playerid][pID], weaponid, WeaponSettings[playerid][index][Hidden]);
		mysql_tquery(g_SQL, string);
	}
	else Error(playerid, "You have specified an invalid option.");
	return 1;
}
