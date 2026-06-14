
ptask CourierTimer[1000](playerid) 
{
    if(CourierJob[playerid] && !IsPlayerInAnyVehicle(playerid) && CourierCrate[playerid])
    {
        TimerCourier[playerid]--;
        new str[256];
        format(str, sizeof(str), "~w~Return To Vehicle ~n~in ~y~%d seconds", TimerCourier[playerid]);
        GameTextForPlayer(playerid, str, 1000, 6);
        PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
        if(TimerCourier[playerid] == 0)
        {
            new gaji;
            gaji = CourierCount[playerid]*2500;
            TimerCourier[playerid] = 0;
            CourierJob[playerid] = false;
            new rada = 50;
            for(new i; i < 11; i++) {
                RemovePlayerMapIcon(playerid, rada+i);
            }
            DisablePlayerRaceCheckpoint(playerid);
            SetVehicleToRespawn(GetPVarInt(playerid, "LastVehicleID"));
            format(str, sizeof(str), "Delivered %d packages");
            AddPlayerSalary(playerid, "San Andreas Express", str, gaji);	
            SendClientMessageEx(playerid, COLOR_ARWIN, "COURIER: {ffffff}Courier sidejob failed, {3BBD44}$%s {ffffff}has been issued for your next paycheck", FormatMoney(gaji));
            SendClientMessageEx(playerid, COLOR_ARWIN, "SALARY: {ffffff}Your salary statement has been updated, please check command {ffff00}'/mysalary'");
            CourierCount[playerid] = 0;
            CourierCrate[playerid] = 0;
            RemovePlayerAttachedObject(playerid, 9);
            DelayPlayer[playerid][DelayCourier] = 1600;
            for(new i = 0; i < 2; i++) 
            {
                TextDrawHideForPlayer(playerid, PlayerCrateTD);
                PlayerTextDrawHide(playerid, PlayerCrate[playerid][i]);
            }
            for(new id; id < 11; id++)
            {
                CourierStatus[playerid][id] = false;
            }
        }
    }
    return 1;
}
