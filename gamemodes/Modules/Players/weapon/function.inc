
IsNotFirearmsWeapon(weaponid) {
    switch (weaponid) {
        case 0, 1, 2, 3: return 1;
        case 5..15: return 1;
        case 49, 50, 51: return 1;
        case 53, 54: return 1;
    }
    return 0;
}

WeaponMaale(weaponid) {
	switch(weaponid) {
		case 0..15: return 1;
		case 35..37: return 1;
		case 39..43: return 1;
	}
	return 0;
}

RemoveWeaponInSlot(playerid, slotid) 
{
    new
        arrWeapons[2][13];
        
    for (new i = 0; i < 13; i ++) {
        GetPlayerWeaponData(playerid, i, arrWeapons[0][i], arrWeapons[1][i]);
    }
    ResetPlayerWeapons(playerid);
    
    for (new i = 0; i < 13; i ++) if (i != slotid) {
        GivePlayerWeapon(playerid, arrWeapons[0][i], arrWeapons[1][i]);
    }
    return 1;
}

PlayerHasWeaponInSlot(playerid, weaponid) 
{
    new slot = g_aWeaponSlots[weaponid];

    if(PlayerGuns[playerid][slot][weapon_id] == weaponid && PlayerGuns[playerid][slot][weapon_slot] == slot) {
        return 1;
    }
    return 0;
}

GivePlayerWeaponEx(playerid, weaponid, ammo = DEFAULT_AMMO, typeammo = 0) 
{
	if(!(0 < weaponid < 46))
		return 0;

	if(PlayerHasWeapon(playerid, weaponid))
		return 1;

	new slot = g_aWeaponSlots[weaponid];

	if(slot == 1 || slot == 10)
		ammo = 1;
	switch(typeammo) {
		case 0..2: {
			PlayerGuns[playerid][slot][weapon_typesurplus] = typeammo;
		}
	}
	PlayerGuns[playerid][slot][weapon_ammo] = ammo;
	PlayerGuns[playerid][slot][weapon_id] = weaponid;
	PlayerGuns[playerid][slot][weapon_slot] = slot;

	GivePlayerWeapon(playerid, weaponid, 999999);
	return 1;
}

AutoDropPlayerGuns(playerid)
{
	if(!IsPlayerConnected(playerid) || IsPlayerInEvent(playerid))
		return 0;

	new dropped, weaponid, ammo, typeammo;

	for(new slot = 0; slot < MAX_WEAPON_SLOT; slot++)
	{
		weaponid = PlayerGuns[playerid][slot][weapon_id];
		ammo = PlayerGuns[playerid][slot][weapon_ammo];
		typeammo = PlayerGuns[playerid][slot][weapon_typesurplus];

		if(!(22 <= weaponid <= 38) || ammo <= 0)
			continue;

		if(!CreateDropWeapon(playerid, weaponid, ammo, typeammo, dropped))
			continue;

		ResetWeaponID(playerid, weaponid);
		dropped++;
	}

	if(dropped)
		SendCustomMessage(playerid, "WEAPON", "Senjata kamu terjatuh karena kamu down/injured.");

	return dropped;
}

GetAmmoStatus(playerid, weaponid) {
	new typeammo[52], slot = g_aWeaponSlots[weaponid];
	if(PlayerGuns[playerid][slot][weapon_typesurplus] == 0) {
		if(PlayerGuns[playerid][slot][weapon_ammo]) {
			format(typeammo, sizeof(typeammo), "%d", PlayerGuns[playerid][slot][weapon_ammo]);
		}
		else typeammo = "~r~No Ammo";
	}
	else if(PlayerGuns[playerid][slot][weapon_typesurplus] == 1) {
		if(PlayerGuns[playerid][slot][weapon_ammo]) {
			format(typeammo, sizeof(typeammo), "%d Surplus", PlayerGuns[playerid][slot][weapon_ammo]);
		}
		else typeammo = "~r~No Ammo";
	}
	else if(PlayerGuns[playerid][slot][weapon_typesurplus] == 2) {
		if(PlayerGuns[playerid][slot][weapon_ammo]) {
			format(typeammo, sizeof(typeammo), "%d JHP", PlayerGuns[playerid][slot][weapon_ammo]);
		}
		else  typeammo = "~r~No Ammo";
	}
	return typeammo;
}

ResetWeaponID(playerid, weaponid) 
{
	new slot = g_aWeaponSlots[weaponid];

    PlayerGuns[playerid][slot][weapon_id] = 0;
    PlayerGuns[playerid][slot][weapon_ammo] = 0;
    PlayerGuns[playerid][slot][weapon_typesurplus] = 0;
    PlayerGuns[playerid][slot][weapon_slot] = 0;

	RemoveWeaponInSlot(playerid, slot);
	return 1;
}

ResetWeapons(playerid)
{
	ResetPlayerWeapons(playerid);
    for (new i = 0; i < MAX_WEAPON_SLOT; i ++) if(PlayerGuns[playerid][i][weapon_id]) {
        PlayerGuns[playerid][i][weapon_id] = PlayerGuns[playerid][i][weapon_ammo] = PlayerGuns[playerid][i][weapon_typesurplus] = 0;
    }
	return 1;
}

GetWeapon(playerid) 
{
    new weaponid = GetPlayerWeapon(playerid);

    if(1 < weaponid < 46 && PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_id] == weaponid)
        return weaponid;

    return 0;
}

PlayerHasWeapon(playerid, weaponid) 
{
    for (new i = 0; i < MAX_WEAPON_SLOT; i ++) if(PlayerGuns[playerid][i][weapon_id] == weaponid) {
        return 1;
    }
    return 0;
}

ReturnWeaponAmmo(playerid, weaponid)
{
	new slot = g_aWeaponSlots[weaponid];

	if(PlayerGuns[playerid][slot][weapon_id] != 0)
		return PlayerGuns[playerid][slot][weapon_ammo];

	return 0;
}

ReturnWeaponMaterial(weaponid)
{
	for(new i = 0; i < sizeof(g_aWeaponItems); i++) if(weaponid == g_aWeaponItems[i][wep_model]) {
		return g_aWeaponItems[i][wep_material];
	}
	return 0;
}

RefreshWeapon(playerid)
{
	ResetPlayerWeapons(playerid);

	for(new i = 1; i != MAX_WEAPON_SLOT; i++) if(PlayerGuns[playerid][i][weapon_id]) {
        GivePlayerWeapon(playerid, PlayerGuns[playerid][i][weapon_id], 999999);
    }
}
