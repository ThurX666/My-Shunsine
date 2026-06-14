
#define 	MULTIPLE_MATERIAL	10
#define 	MAX_WEAPON_SLOT		13
#define 	DEFAULT_AMMO		20

#define 	PLAYER_NORMAL 		1
#define 	PLAYER_OFFICIAL		2

enum e_WeaponItems {
	wep_model,
	wep_material,
	wep_auth
};

new const g_aWeaponItems[][e_WeaponItems] = {
	{WEAPON_KNIFE, 500, PLAYER_NORMAL},
	{WEAPON_RIFLE, 1000, PLAYER_NORMAL},
	//{WEAPON_COLT45, 1500, PLAYER_NORMAL},
	{WEAPON_SILENCED, 1750, PLAYER_NORMAL},
	{WEAPON_SHOTGUN, 2000, PLAYER_NORMAL},
	{WEAPON_DEAGLE, 3500, PLAYER_OFFICIAL},
	{WEAPON_AK47, 7000, PLAYER_OFFICIAL},
	{WEAPON_TEC9, 6500, PLAYER_OFFICIAL}
};

new const MaxGunAmmo[54] = {
	0,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,10,10,10,0,
	0,0,850,350,350,250,200,350,2000,2000,
	2000,750,2000,100,50,5,5,10,9999,10,
	-1,500,500,10,-1,-1,-1,0,0,0,
	0,0,0,0
};


enum E_WEAPON_DATA {
	weapon_id,
	weapon_slot,
	weapon_ammo,
	weapon_typesurplus
};

new 
	PlayerGuns[MAX_PLAYERS][MAX_WEAPON_SLOT][E_WEAPON_DATA];
	// ListedWeapons[MAX_PLAYERS][MAX_WEAPON_SLOT];
