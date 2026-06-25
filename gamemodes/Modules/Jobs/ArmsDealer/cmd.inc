
CMD:buypacket(playerid, params[])
{
	if(IsPlayerInRangeOfPoint(playerid, 3.5, 321.5652,1121.2504,1083.8828))
	{
		if(pData[playerid][pJob] != 6 && pData[playerid][pJob2] != 6) return Error(playerid, "Kamu tidak bekerja sebagai arms dealer.");
		Dialog_Show(playerid, PacketMaterial, DIALOG_STYLE_MSGBOX, "Buying Material","Price per packet: "GREEN_E"$2,003.68\nAmmount: "YELLOW_E"2500 units\nConfirm purchase?", "Yes", "No" );
	}
	else if(IsPlayerInRangeOfPoint(playerid, 3.5, -882.1044,1110.8616,5442.8203))
	{
		if(pData[playerid][pJob] == 7 || pData[playerid][pJob2] == 7)
		{
			if(isnull(params)) 
			{
				Usage(playerid, "/buypacket [pot/crack]");
				return 1;
			}
			if(strcmp(params,"pot",true) == 0) 
			{
				Dialog_Show(playerid,BuyPot,DIALOG_STYLE_MSGBOX,"Buying Drug: Pot","Price per packet: "GREEN_E"$304.36\n"GREEN_E"Weight: "YELLOW_E"100 grams\nConfirm purchase?", "Yes", "No" );
			}
			if(strcmp(params,"crack",true) == 0) 
			{
				if(pData[playerid][pFamily] == -1)
					return Error(playerid, "You are not in family!");
				Dialog_Show(playerid,BuyCrack,DIALOG_STYLE_MSGBOX,"Buying Drug: Crack","Price per packet: "GREEN_E"$304.36\n"GREEN_E"Weight: "YELLOW_E"50 grams\nConfirm purchase?", "Yes", "No" );
			}
		}	
	}
	return 1;	
}

CMD:buyschematic(playerid)
{
    //Ubah Sendiri
    if(pData[playerid][pJob] != 6 && pData[playerid][pJob2] != 6) 
        return Error(playerid, "Kamu tidak bekerja sebagai arms dealer.");
        
    if(!IsPlayerInRangeOfPoint(playerid, 3.5, 321.5652,1121.2504,1083.8828)) 
        return Error(playerid, "You're not near schematic buy point");
        
    new str[518];
    
    // Pengecekan status Family
    if(pData[playerid][pFamily] > 0)
    {
        // Tampilan untuk anggota Family (Semua Senjata)
        format(str, sizeof(str), "Schematic\tCost\nCountry Rifle\t$125.00\nShotgun\t$125.00\nSawn Of Shotgun\t$200.00\nDesert Eagle\t$200.00\nMP5\t$250.00\nAK47\t$450.00");
    }
    else
    {
        // Tampilan untuk Warga Biasa (Hanya senjata ringan)
        format(str, sizeof(str), "Schematic\tCost\nCountry Rifle\t$125.00\nShotgun\t$125.00\nSawn Of Shotgun\t$200.00");
    }
    
    Dialog_Show(playerid, BuySchematic, DIALOG_STYLE_TABLIST_HEADERS, "Buying Schematic", str, "Buy", "Cancel");
    return 1;
}

CMD:creategun(playerid, params[]) 
{
	if(pData[playerid][pOnDuty]) 
        return Error(playerid, "Kamu sedang duty faction.");

    if(pData[playerid][pJob] != 6 && pData[playerid][pJob2] != 6)
    	return Error(playerid, "Kamu tidak bekerja sebagai arms dealer.");

	if (!pData[playerid][pCS])
		return Error(playerid, "You must have accepted character story for creating a gun.");
	if(DelayPlayer[playerid][DelayWeaponCreate] != 0) return Error(playerid, "Tidak bisa menggunakan command ini");
    new String[512];

	if(pData[playerid][pFamily] > 0)
	{
		format(String, sizeof(String), "Weapons Name\tMaterial Cost\tRequire Schematic\n");
		format(String, sizeof(String),"%sShotgun\t2000\t%s\nSawn Of Shotgun\t3000\t%s\nDesert Eagle\t2500\t%s\nMP5\t5000\t%s\nAK47\t7000\t%s",String, SchematicRequire(playerid, 1), SchematicRequire(playerid, 2), SchematicRequire(playerid, 3), SchematicRequire(playerid, 4), SchematicRequire(playerid, 5));
	}
	else
	{
		format(String, sizeof(String), "Weapons Name\tMaterial Cost\tRequire Schematic\n");
		format(String, sizeof(String),"%sShotgun\t2000\t%s\nSawn Of Shotgun\t3000\t%s",String, SchematicRequire(playerid, 1), SchematicRequire(playerid, 2));
	}
    Dialog_Show(playerid, CreateGun, DIALOG_STYLE_TABLIST_HEADERS, "Weapon Crafting", String, "Create", "Cancel");
	return 1;
}

CMD:createammo(playerid, params[])
{
    new weaponid, amount;
    if(sscanf(params, "d", amount))
        return Usage(playerid, "/createammo [ammount]");

    if(pData[playerid][pOnDuty]) 
        return Error(playerid, "Kamu sedang duty faction.");

    if(pData[playerid][pJob] != 6 && pData[playerid][pJob2] != 6)
    	return Error(playerid, "Kamu tidak bekerja sebagai arms dealer.");

	if (!pData[playerid][pCS])
        return Error(playerid, "You must have accepted character story for creating ammo.");

    if(!pData[playerid][pMaterial])
        return Error(playerid, "Kamu tidak memiliki material.");

    if((weaponid = GetWeapon(playerid)) == 0)
    {
        new foundWeapon = 0, foundCount = 0;
        for(new i = 0; i < MAX_WEAPON_SLOT; i++) {
            new current = PlayerGuns[playerid][i][weapon_id];
            if(current >= 22 && current <= 38 && ReturnWeaponAmmo(playerid, current) < MaxGunAmmo[current]) {
                foundWeapon = current;
                foundCount++;
                if(foundCount > 1) break;
            }
        }
        if(foundCount == 1)
            weaponid = foundWeapon;
        else
            return Error(playerid, "Kamu tidak memegang senjata apapun atau pilih senjata yang ingin diisi amunisi.");
    }

    if(g_aWeaponSlots[weaponid] == 1)
        return Error(playerid, "Senjata ini tidak dapat diisi amunisi.");

    new currentAmmo;
    if(ReturnWeaponAmmo(playerid, weaponid) >= MaxGunAmmo[weaponid])
        return Error(playerid, "Senjata ini tidak memerlukan amunisi lagi.");

    if(amount <= 0)
        return Error(playerid, "Jumlah amunisi tidak valid.");

    currentAmmo = ReturnWeaponAmmo(playerid, weaponid);
    if(currentAmmo + amount > MaxGunAmmo[weaponid])
        return Error(playerid, "Senjata ini tidak memerlukan amunisi lagi.");

    if(floatround((amount / 2.0) * 5.0) > pData[playerid][pMaterial])
        return Error(playerid, "Jumlah material tidak mencukupi.");

    if(weaponid >= 22 && weaponid <= 38)
    {
        PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_ammo] += amount;
        pData[playerid][pMaterial] -= floatround((amount / 2.0) * 5.0);
        PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_typesurplus] = 1;
        SendClientMessageEx(playerid, COLOR_ARWIN, "CRAFTING: "WHITE_E"Crafted "YELLOW_E"%d Ammo Surplus "WHITE_E"Using "YELLOW_E"%d materials", amount, floatround((amount / 2.0) * 5.0));
    }
    return 1;
}
