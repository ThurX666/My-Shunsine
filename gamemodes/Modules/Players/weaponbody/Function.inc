
GetWeaponObjectSlot(weaponid)
{
	new objectslot;

	switch (weaponid)
	{
        case 2..15: objectslot = 5;
    	case 22..27: objectslot = 6;
		case 28..32: objectslot = 7;
		case 33..38: objectslot = 8;
	}
	return objectslot;
}

GetWeaponModel(weaponid) //Will only return the model of wearable weapons (22-38)
{
    new model;
   
    switch(weaponid)
    {
        case 2: model = 333;
        case 3: model = 334;
        case 4: model = 335;
        case 5: model = 336;
        case 6: model = 337;
        case 7: model = 338;
        case 8: model = 339;
        case 9: model = 341;
        case 10: model = 321;
        case 11: model = 322;
        case 12: model = 323;
        case 13: model = 324;
        case 14: model = 325;
        case 15: model = 326;
        case 22..29: model = 324 + weaponid;
        case 30: model = 355;
        case 31: model = 356;
        case 32: model = 372;
        case 33..38: model = 324 + weaponid;
    }
    return model;
}
 
IsWeaponWearable(weaponid)
    return ((weaponid >= 2 && weaponid <= 15) || (weaponid >= 22 && weaponid <= 38));
 
IsWeaponHideable(weaponid)
    return ((weaponid >= 2 && weaponid <= 15) || (weaponid >= 22 && weaponid <= 38));

ReturnWeaponName(weaponid)
{
    new weapon[22];
    switch(weaponid)
    {
        case 0: weapon = "Fist";
        case 18: weapon = "Molotov Cocktail";
        case 44: weapon = "Night Vision Goggles";
        case 45: weapon = "Thermal Goggles";
        case 54: weapon = "Fall";
        default: GetWeaponName(weaponid, weapon, sizeof(weapon));
    }
    return weapon;
}

// //Weapon Attach System
function OnWeaponsLoaded(playerid)
{
    new rows, weaponid, index;
   
    cache_get_row_count(rows);
   
    for (new i; i < rows; i++)
    {
        cache_get_value_name_int(i, "WeaponID", weaponid);
        index = (weaponid >= 22 && weaponid <= 38) ? (weaponid - 22) : (weaponid + 15);
       
        cache_get_value_name_float(i, "PosX", WeaponSettings[playerid][index][Position][0]);
        cache_get_value_name_float(i, "PosY", WeaponSettings[playerid][index][Position][1]);
        cache_get_value_name_float(i, "PosZ", WeaponSettings[playerid][index][Position][2]);
       
        cache_get_value_name_float(i, "RotX", WeaponSettings[playerid][index][Position][3]);
        cache_get_value_name_float(i, "RotY", WeaponSettings[playerid][index][Position][4]);
        cache_get_value_name_float(i, "RotZ", WeaponSettings[playerid][index][Position][5]);
       
        cache_get_value_name_int(i, "Bone", WeaponSettings[playerid][index][Bone]);
        cache_get_value_name_int(i, "Hidden", WeaponSettings[playerid][index][Hidden]);
    }
}
