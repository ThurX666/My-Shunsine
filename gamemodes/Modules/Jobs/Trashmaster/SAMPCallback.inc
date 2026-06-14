#include <YSI\y_hooks>
hook OnGameModeInit()
{
    VehicleTrashmaster[0] = AddStaticVehicle(408,2118.483,-2078.253,13.546,141.301,44,44);
    VehicleTrashmaster[1] = AddStaticVehicle(408,2126.990,-2084.031,13.546,136.226,44,44);
    VehicleTrashmaster[2] = AddStaticVehicle(408,2134.713,-2090.880,13.546,134.353,44,44);
}

hook OnPlayerConnect(playerid) {
	TimerTrashmaster[playerid] = -1;
	pData[playerid][pTrashmasterJob] = -1;
	TrashmasterCrate[playerid] = -1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
    new engine, lights, alarm, doors, bonnet, boot, objective;
    if(newstate == PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_PASSENGER) {
        if(IsVehicleTrashmaster(GetPlayerVehicleID(playerid)) && !pData[playerid][pTrashmasterJob])
        {
            if(!DelayPlayer[playerid][DelayTrashmaster])
            {
                SetCameraBehindPlayer(playerid);
                TogglePlayerControllable(playerid, 0);
                Dialog_Show(playerid, StartTrashmaster, DIALOG_STYLE_MSGBOX, "Sidejob: Trash Collector", ""WHITE_E"Apakah anda siap bekerja menjadi trash collector?", "Yes", "Cancel"
                	);
            }
            else
            {
            	TogglePlayerControllable(playerid, 1);
                RemovePlayerFromVehicle(playerid);
                Servers(playerid, "Anda masih menunggu waktu %d menit untuk melakukan pekerjaan ini lagi.", DelayPlayer[playerid][DelayTrashmaster]/60);
            }
        }
        if(IsVehicleTrashmaster(GetPlayerVehicleID(playerid)) && pData[playerid][pTrashmasterJob]) {
			GetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, 0); // ONLY the engine param was changed to VEHICLE_PARAMS_ON (1)
			for(new i = 0; i < 2; i++) 
			{
				TextDrawShowForPlayer(playerid, PlayerCrateTD);
				PlayerTextDrawShow(playerid, PlayerCrate[playerid][i]);
			}
			new String2[212];
			format(String2,sizeof(String2),"Trash~n~%d/10", CoreVehicles[GetPlayerVehicleID(playerid)][vehTrash]);
			PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
			return 1;
		}
    }
    if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) {
        if(pData[playerid][pTrashmasterJob]) {
			TimerTrashmaster[playerid] = 61;
			SetVehicleParamsForPlayer(pData[playerid][pLastCar],playerid,1,0);
			return 1;
		}
    }
    return 1;
}

hook OnPlayerEnterRaceCP(playerid) {
    if(pData[playerid][pTrashmasterJob] == 1 && CoreVehicles[GetPlayerVehicleID(playerid)][vehTrash] == 10 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		TextDrawHideForPlayer(playerid, PlayerCrateTD);
		PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
		PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);

		new list[128];
		new cash = CoreVehicles[GetPlayerVehicleID(playerid)][vehTrash]*1500;
		format(list, sizeof(list), "Cleared %d trash dumps", CoreVehicles[GetPlayerVehicleID(playerid)][vehTrash]);
		AddPlayerSalary(playerid, "Public Service (Trashmaster)", list, cash);
		SendCustomMessage(playerid, "TRASH", "Trashmaster sidejob completed, "GREEN_E"$%s "WHITE_E"has been issued for your next paycheck", FormatMoney(cash));
		SendClientMessageEx(playerid, COLOR_ARWIN, "SALARY: {ffffff}Your salary statement has been updated, please check command {ffff00}'/mysalary'");

		CoreVehicles[GetPlayerVehicleID(playerid)][vehTrash] = 0;
		pData[playerid][pTrashmasterJob] = 0;
		DelayPlayer[playerid][DelayTrashmaster] = 1800;
		DisablePlayerRaceCheckpoint(playerid);
		TimerTrashmaster[playerid] = -1;
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		RemovePlayerFromVehicle(playerid);
	}
    return 1;
}