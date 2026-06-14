
CMD:weapon(playerid, params[]) 
{
	if(pData[playerid][pInjured])
        return Error(playerid, "Tidak bisa menggunakan perintah ini ketika injured.");

    if(pData[playerid][pHospitalTime])
        return Error(playerid, "Tidak bisa menggunakan perintah ini ketika dalam masa pemulihan.");

	new category[32], string[32];

	if(sscanf(params, "s[32]S()[32]", category, string))
		return Usage(playerid, "/weapon [give/view/acceptview/scrap/destroy]");

	if(!strcmp(category, "give"))
	{
		new userid, weaponid;

		if(sscanf(string, "u", userid))
			return Usage(playerid, "/weapon give [userid]");

		if(userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0)) 
			return Error(playerid, "Player tidak login atau tidak bedara didekatmu.");

		if (!pData[userid][pCS])
			return Error(playerid, "That player must have accepted character story.");

		if(!(weaponid = GetWeapon(playerid)))
			return Error(playerid, "Kamu tidak memegang senjata apapun.");

        // if(PlayerHasWeaponInSlot(userid, weaponid))
        // 	return Error(playerid, "Player tersebut memiliki senjata di slot yang sama.");

		if(PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_typesurplus] == 1) {
			GivePlayerWeaponEx(userid, weaponid, PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_ammo], 1);
		}
		else if(PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_typesurplus] == 0) {
			GivePlayerWeaponEx(userid, weaponid, PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_ammo], 0);
		}
		else if(PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_typesurplus] == 2) return Error(playerid, "Anda tidak bisa memberikan senjata type JHP!");
		ResetWeaponID(playerid, weaponid);
		SendCustomMessage(playerid, "WEAPON", "You have given "RED_E"%s"WHITE_E" to "YELLOW_E"%s.", ReturnWeaponName(weaponid), ReturnName2(userid));
		SendCustomMessage(userid, "WEAPON", ""YELLOW_E"%s"WHITE_E" give "RED_E"%s"WHITE_E" to you.", ReturnName2(playerid), ReturnWeaponName(weaponid));
	}
	else if(!strcmp(category, "scrap"))
	{
		new weaponid, confirm[10] ;

		if(!(weaponid = GetWeapon(playerid)))
			return Error(playerid, "Kamu tidak memegang senjata apapun.");

		if(sscanf(string, "s[10]", confirm)) {
			SendCustomMessage(playerid, "USAGE","/weapon scrap ['confirm']");
			SendCustomMessage(playerid, "INFO","Perintah ini untuk menggantikan senjata dan peluru menjadi material!");
			return 1;
		}

		if(!strcmp(confirm, "confirm"))
		{
			if (weaponid >= 2 && weaponid <= 15 || weaponid > 38)
				return Error(playerid, "Senjata jenis ini tidak dapat discrap!");

			pData[playerid][pMaterial] += floatround((ReturnWeaponMaterial(weaponid)/4));
			SendCustomMessage(playerid, "WEAPON", "Successfully scraping weapons "RED_E"%s "WHITE_E"become "YELLOW_E"%d material(s)", ReturnWeaponName(weaponid), floatround((ReturnWeaponMaterial(weaponid)/4)));

			
			if(PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_typesurplus]) {
				pData[playerid][pMaterial] += floatround((PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_ammo]/2*2));
			}
			else {
				pData[playerid][pMaterial] += floatround((PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_ammo]/2));
			}
			SendCustomMessage(playerid, "WEAPON", "Successfully performed scrap "RED_E"%d ammo "WHITE_E"become "YELLOW_E"%d material(s)", PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_ammo], floatround((PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_ammo]/2)));

			ResetWeaponID(playerid, weaponid);
		}
	}
	else if(!strcmp(category, "destroy"))
	{
		new weaponid, confirm[10];

		if((weaponid = GetWeapon(playerid)) == 0)
			return Error(playerid, "Kamu tidak memegang senjata apapun.");

		if(sscanf(string, "s[10]", confirm)) {
			SendCustomMessage(playerid, "USAGE", "/weapon destroy ['confirm']");
			SendCustomMessage(playerid, "WARNING","Perintah ini digunakan untuk menghancurkan habis senjatamu, termasuk peluru di dalamnya!");
			SendCustomMessage(playerid, "WARNING","Tidak ada refund setelah menggunakan perintah ini!");
			return 1;
		}

		if(!strcmp(confirm, "confirm"))
		{
			SendCustomMessage(playerid, "WEAPON", "Successfully destroyed weapons "RED_E"%s.", ReturnWeaponName(weaponid));
			ResetWeaponID(playerid, weaponid);
		}
	}
	else if(!strcmp(category, "view"))
	{
		new userid, weaponid;
		if((weaponid = GetWeapon(playerid)) == 0)
			return Error(playerid, "Kamu tidak memegang senjata apapun.");

		if(sscanf(string, "u", userid)) {
			SendCustomMessage(playerid, "WEAPON", "[%s] "AQUA_E"AMMO: "WHITE_E"[%s]", ReturnWeaponName(weaponid), GetAmmoStatus(playerid, weaponid));
			return 1;
		}
		if(userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0)) 
			return Error(playerid, "Player tidak login atau tidak bedara didekatmu.");

		SendCustomMessage(userid, "WEAPON", "[%s] "AQUA_E"AMMO: "WHITE_E"[%s]", ReturnWeaponName(weaponid), GetAmmoStatus(playerid, weaponid));
		Servers(playerid, "Kamu memperlihatkan senjatamu kepada %s.", ReturnName2(userid));
	}
	else Usage(playerid, "/weapon [give/view/acceptview/scrap/destroy]");
	return 1;
}
