
ptask TrashmasterTimer[1000](playerid) 
{
    if(!IsPlayerInAnyVehicle(playerid) && TimerTrashmaster[playerid] > 0)
    {
        TimerTrashmaster[playerid]--;
        new str[256];
        format(str, sizeof(str), "~w~Return To Trashmaster Vehicle ~n~in ~y~%d seconds", TimerTrashmaster[playerid]);
        GameTextForPlayer(playerid, str, 1000, 6);
        PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
        if(TimerTrashmaster[playerid] == 0)
        {
            new list[128], rada = 50, vehicleid = GetPVarInt(playerid, "LastVehicleID");
            new cash = CoreVehicles[vehicleid][vehTrash]*1500;
            for(new i; i < 11; i++) {
                RemovePlayerMapIcon(playerid, rada+i);
            }
            format(list, sizeof(list), "Cleared %d trash dumps", CoreVehicles[vehicleid][vehTrash]);
            SetVehicleToRespawn(vehicleid);
            AddPlayerSalary(playerid, "Public Service (Trashmaster)", list, cash);	
            SendClientMessageEx(playerid, COLOR_ARWIN, "SIDEJOB: {ffffff}Trashmaster sidejob failed, {3BBD44}$%s {ffffff}has been issued for your next paycheck", FormatMoney(cash));
            SendClientMessageEx(playerid, COLOR_ARWIN, "SALARY: {ffffff}Your salary statement has been updated, please check command {ffff00}'/mysalary'");
            CoreVehicles[vehicleid][vehTrash] = 0;
            pData[playerid][pTrashmasterJob] = 0;
            DelayPlayer[playerid][DelayTrashmaster] = 1800;
            TextDrawHideForPlayer(playerid, PlayerCrateTD);
            PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
            PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);
        }
    }
    return 1;
}
