
#include <YSI\y_hooks>
ptask Player_Weapon[1000](playerid)
{
	if(pData[playerid][IsLoggedIn])
	{
		new weaponid;

		if((weaponid = GetWeapon(playerid)) != 0 && !eventJoin[playerid] && !WeaponMaale(weaponid)) {
			PlayerTextDrawShow(playerid, TogAmmo[playerid]);
			PlayerTextDrawSetString(playerid, TogAmmo[playerid], sprintf("%s", GetAmmoStatus(playerid, weaponid)));
		}
		else {
			PlayerTextDrawSetString(playerid, TogAmmo[playerid], "_");
			PlayerTextDrawHide(playerid, TogAmmo[playerid]);
		}
	}
	return 1;
}
