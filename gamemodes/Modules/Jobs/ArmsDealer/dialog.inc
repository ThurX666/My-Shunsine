Dialog:BuyPot(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		new strings2[214];
		if(GetPlayerMoney(playerid) < 30436) return Error(playerid, "You don't have enough cash");
		GivePlayerMoneyEx(playerid, -30436);
		pData[playerid][pPot] += 100;
		StockCrack -= 100;
		format(strings2, sizeof(strings2), ""RED_E"Job: Drugs Dealer\n"YELLOW_E"'/joinjob' "WHITE_E"to be an Drug Dealer\n"YELLOW_E"'/buypacket' "WHITE_E"to buy drugs package\nAvailable packages: "GREEN_E"%d", StockCrack);
		UpdateDynamic3DTextLabelText(Crack, COLOR_ARWIN, strings2);
		SendClientMessageEx(playerid, COLOR_ARWIN, "DEALER: "WHITE_E"You've purchase a drug package that contains "YELLOW_E"100 grams "WHITE_E"of pot for "GREEN_E"$304.36");
	}
	return 1;
}

Dialog:BuyCrack(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		new strings2[214];
		if(GetPlayerMoney(playerid) < 30436) return Error(playerid, "You don't have enough cash");
		GivePlayerMoneyEx(playerid, -30436);
		pData[playerid][pCrack] += 50;
		StockCrack -= 50;
		format(strings2, sizeof(strings2), ""RED_E"Job: Drugs Dealer\n"YELLOW_E"'/joinjob' "WHITE_E"to be an Drug Dealer\n"YELLOW_E"'/buypacket' "WHITE_E"to buy drugs package\nAvailable packages: "GREEN_E"%d", StockCrack);
		UpdateDynamic3DTextLabelText(Crack, COLOR_ARWIN, strings2);
		SendClientMessageEx(playerid, COLOR_ARWIN, "DEALER: "WHITE_E"You've purchase a drug package that contains "YELLOW_E"50 grams "WHITE_E"of crack for "GREEN_E"$304.36");
	}
	return 1;
}

Dialog:PacketMaterial(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		new strings[214];
		if(GetPlayerMoney(playerid) < 200368) return Error(playerid, "You don't have enough cash");
		GivePlayerMoneyEx(playerid, -200368);
		pData[playerid][pMaterial] += 2500;
		StockMaterial -= 2500;
		format(strings, sizeof(strings), ""RED_E"Job: Arms Dealer\n"YELLOW_E"'/joinjob' "WHITE_E"to be an Arms Dealer\n"YELLOW_E"'/buypacket' "WHITE_E"to buy gun material package\nAvailable packages: "GREEN_E"%d", StockMaterial);
		UpdateDynamic3DTextLabelText(Material, COLOR_ARWIN, strings);
		SendClientMessageEx(playerid, COLOR_ARWIN, "DEALER: "WHITE_E"You've purchase a material package that contains "YELLOW_E"2500 units "WHITE_E"of material for "GREEN_E"$2,003.68");
	}
	return 1;
}

Dialog:CreateGun(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				if(pData[playerid][pMaterial] >= 2000)
				{
					if(!pData[playerid][pSchematic][1]) return Error(playerid, "You don't have the schematic of the weapon");
					if(PlayerHasWeapon(playerid, 25))
						return Error(playerid, "You already have %s, /buyammo to add more ammo.", ReturnWeaponName(25));

					if(PlayerHasWeaponInSlot(playerid, 25))
						return Error(playerid, "You already have weapon in the same slot.");
					GivePlayerWeaponEx(playerid, 25, 50);
					pData[playerid][pMaterial] -= 2000;
					DelayPlayer[playerid][DelayWeaponCreate] = 600;
					SendClientMessageEx(playerid, COLOR_ARWIN, "CRAFTING: "WHITE_E"You've crafted "YELLOW_E"Shotgun "WHITE_E"Using {00FFFF}2000 materials");
				}
				else
				{
					Error(playerid, "You don't have enough materials.");
				}
			}
			case 1:
			{
				if(pData[playerid][pMaterial] >= 3000)
				{
					if(!pData[playerid][pSchematic][2]) return Error(playerid, "You don't have the schematic of the weapon");
					if(PlayerHasWeapon(playerid, 26))
						return Error(playerid, "You already have %s, /buyammo to add more ammo.", ReturnWeaponName(26));

					if(PlayerHasWeaponInSlot(playerid, 26))
						return Error(playerid, "You already have weapon in the same slot.");
					GivePlayerWeaponEx(playerid, 26, 50);
					pData[playerid][pMaterial] -= 3000;
					DelayPlayer[playerid][DelayWeaponCreate] = 600;
					SendClientMessageEx(playerid, COLOR_ARWIN, "CRAFTING: "WHITE_E"You've crafted "YELLOW_E"Sawn Of Shotgun "WHITE_E"Using {00FFFF}3000 materials");
				}
				else
				{
					Error(playerid, "You don't have enough materials.");
				}
			}
			case 2:
			{
				if(pData[playerid][pFamily] < 0) return Error(playerid, "You're not in a family.");
				if(pData[playerid][pMaterial] >= 2500)
				{
					if(!pData[playerid][pSchematic][3]) return Error(playerid, "You don't have the schematic of the weapon");
					if(PlayerHasWeapon(playerid, 24))
						return Error(playerid, "You already have %s, /buyammo to add more ammo.", ReturnWeaponName(24));

					if(PlayerHasWeaponInSlot(playerid, 24))
						return Error(playerid, "You already have weapon in the same slot.");
					GivePlayerWeaponEx(playerid, 24, 100);
					pData[playerid][pMaterial] -= 2500;
					DelayPlayer[playerid][DelayWeaponCreate] = 600;
					SendClientMessageEx(playerid, COLOR_ARWIN, "CRAFTING: "WHITE_E"You've crafted "YELLOW_E"Desert Eagle "WHITE_E"Using {00FFFF}2500 materials");
				}
				else
				{
					Error(playerid, "You don't have enough materials.");
				}
			}
			case 3:
			{
				if(pData[playerid][pFamily] < 0) return Error(playerid, "You're not in a family.");
				if(pData[playerid][pMaterial] >= 5000)
				{
					if(!pData[playerid][pSchematic][4]) return Error(playerid, "You don't have the schematic of the weapon");
					if(PlayerHasWeapon(playerid, 29))
						return Error(playerid, "You already have %s, /buyammo to add more ammo.", ReturnWeaponName(29));

					if(PlayerHasWeaponInSlot(playerid, 29))
						return Error(playerid, "You already have weapon in the same slot.");
					GivePlayerWeaponEx(playerid, 29, 100);
					pData[playerid][pMaterial] -= 5000;
					DelayPlayer[playerid][DelayWeaponCreate] = 600;
					SendClientMessageEx(playerid, COLOR_ARWIN, "CRAFTING: "WHITE_E"You've crafted "YELLOW_E"MP5 "WHITE_E"Using {00FFFF}5000 materials");
				}
				else
				{
					Error(playerid, "You don't have enough materials.");
				}
			}
			case 4:
			{
				if(pData[playerid][pFamily] < 0) return Error(playerid, "You're not in a family.");
				if(pData[playerid][pMaterial] >= 7000)
				{
					if(!pData[playerid][pSchematic][5]) return Error(playerid, "You don't have the schematic of the weapon");
					if(PlayerHasWeapon(playerid, 30))
						return Error(playerid, "You already have %s, /buyammo to add more ammo.", ReturnWeaponName(30));

					if(PlayerHasWeaponInSlot(playerid, 30))
						return Error(playerid, "You already have weapon in the same slot.");
					GivePlayerWeaponEx(playerid, 30, 100);
					pData[playerid][pMaterial] -= 7000;
					DelayPlayer[playerid][DelayWeaponCreate] = 600;
					SendClientMessageEx(playerid, COLOR_ARWIN, "CRAFTING: "WHITE_E"You've crafted "YELLOW_E"AK47 "WHITE_E" Using {00FFFF}7000 materials");
				}
				else
				{
					Error(playerid, "You don't have enough materials.");
				}
			}
		}
	}
	return 1;
}

Dialog:CreateAmmo(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		new weaponid = GetWeapon(playerid);
		if(weaponid == 0)
		{
			new foundWeapon = 0, foundCount = 0;
			for(new i = 0; i < MAX_WEAPON_SLOT; i++) {
				new current = PlayerGuns[playerid][i][weapon_id];
				if(current >= 22 && current <= 38) {
					foundWeapon = current;
					foundCount++;
					if(foundCount > 1) break;
				}
			}
			if(foundCount == 1)
				weaponid = foundWeapon;
			else
				return Error(playerid, "Hold the weapon you want to craft ammo for.");
		}

		new amount = (MaxGunAmmo[weaponid]-ReturnWeaponAmmo(playerid, weaponid));

		if(floatround(amount/2) > pData[playerid][pMaterial])
			return Error(playerid, "Jumlah material tidak mencukupi.");

		if(weaponid >= 22 && weaponid <= 38)
		{
			if(amount <= 0) return Error(playerid, "Your weapon already has full ammo.");
			PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_ammo] += amount;
			pData[playerid][pMaterial] -= floatround((amount/2));
			SendClientMessageEx(playerid, COLOR_ARWIN, "CRAFTING: "WHITE_E"Crafted "YELLOW_E"%d Ammo "WHITE_E"Using "YELLOW_E"%d materials", amount, floatround((amount/2)));
		}
		else
		{
			return Error(playerid, "No valid ranged weapon selected.");
		}
	}
	return 1;
}

Dialog:BuySchematic(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				if(pData[playerid][pSchematic][0]) return Error(playerid, "You already have the schematic of the weapon");
				if(GetPlayerMoney(playerid) < 12500) return Error(playerid, "You don't have money");
				pData[playerid][pSchematic][0]++;
				GivePlayerMoneyEx(playerid, -12500);
				SendCustomMessage(playerid, "SCHEMATIC", "You've purchased the "RED_E"Country Rifle Schematic "WHITE_E"for "GREEN_E"$125.00");
			}
			case 1:
			{
				if(pData[playerid][pSchematic][1]) return Error(playerid, "You already have the schematic of the weapon");
				if(GetPlayerMoney(playerid) < 12500) return Error(playerid, "You don't have money");
				pData[playerid][pSchematic][1]++;
				GivePlayerMoneyEx(playerid, -12500);
				SendCustomMessage(playerid, "SCHEMATIC", "You've purchased the "RED_E"Shotgun Schematic "WHITE_E"for "GREEN_E"$125.00");
			}
			case 2:
			{
				if(pData[playerid][pSchematic][2]) return Error(playerid, "You already have the schematic of the weapon");
				if(GetPlayerMoney(playerid) < 12500) return Error(playerid, "You don't have money");
				pData[playerid][pSchematic][2]++;
				GivePlayerMoneyEx(playerid, -12500);
				SendCustomMessage(playerid, "SCHEMATIC", "You've purchased the "RED_E"Sawn Of Shotgun Schematic "WHITE_E"for "GREEN_E"$125.00");
			}
			case 3:
			{
				if(pData[playerid][pSchematic][3]) return Error(playerid, "You already have the schematic of the weapon");
				if(GetPlayerMoney(playerid) < 20000) return Error(playerid, "You don't have money");
				pData[playerid][pSchematic][3]++;
				GivePlayerMoneyEx(playerid, -20000);
				SendCustomMessage(playerid, "SCHEMATIC", "You've purchased the "RED_E"Desert Eagle Schematic "WHITE_E"for "GREEN_E"$200.00");
			}
			case 4:
			{
				if(pData[playerid][pSchematic][4]) return Error(playerid, "You already have the schematic of the weapon");
				if(GetPlayerMoney(playerid) < 25000) return Error(playerid, "You don't have money");
				pData[playerid][pSchematic][4]++;
				GivePlayerMoneyEx(playerid, -25000);
				SendCustomMessage(playerid, "SCHEMATIC", "You've purchased the "RED_E"MP-5 Schematic "WHITE_E"for "GREEN_E"$250.00");
			}
			case 5:
			{
				if(pData[playerid][pSchematic][5]) return Error(playerid, "You already have the schematic of the weapon");
				if(GetPlayerMoney(playerid) < 45000) return Error(playerid, "You don't have money");
				pData[playerid][pSchematic][5]++;
				GivePlayerMoneyEx(playerid, -45000);
				SendCustomMessage(playerid, "SCHEMATIC", "You've purchased the "RED_E"AK-47 Schematic "WHITE_E"for "GREEN_E"$450.00");
			}
		}
	}
	return 1;
}