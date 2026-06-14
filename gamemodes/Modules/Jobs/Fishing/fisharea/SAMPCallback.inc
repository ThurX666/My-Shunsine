#include <YSI\y_hooks>
hook OnPlayerEnterDynArea(playerid, areaid)
{
    if(IsPlayerInAnyVehicle(playerid) && IsABoat(GetPlayerVehicleID(playerid))) {
        foreach(new fishing : FishingArea) if (areaid == FishingData[fishing][Zone]) {
            new zone[52];
            switch(FishingData[fishing][Type]) {
                case 0: zone = "~r~Low";
                case 1: zone = "~y~Medium";
                case 2: zone = "~g~High";
            }
            TextDrawShowForPlayer(playerid, PlayerCrateTD);
            PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
            PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
            PlayerTextDrawSetString(playerid, PlayerCrate[playerid][0], "Fish Density");
            new str[212];
            format(str, sizeof(str), "Type: ~p~Ocean~n~~w~Density: %s", zone);
            PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], str);
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, areaid)
{
	foreach(new fishing : FishingArea) if (areaid == FishingData[fishing][Zone]) {
        TextDrawHideForPlayer(playerid, PlayerCrateTD);
        PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
        PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);
    }
	return 1;
}
