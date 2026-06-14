#include <YSI\y_hooks>

hook OnGameModeInit(){

    new strings[212];
    DmvVeh = AddStaticVehicleEx(426, 2062.4031,-1904.4381,13.3260,179.6736, 1, 1, VEHICLE_RESPAWN);
	BoatLic = AddStaticVehicleEx(452, 2954.4072, -1497.4480, -0.2639, 176.9170, 1, 1, VEHICLE_RESPAWN); // speeder

    //DMV
	CreateDynamicPickup(1239, 23, 1491.14, 1306.33, 1093.28, -1);
	format(strings, sizeof(strings), "{00FFFF}[Car License]\n"YELLOW_E"/taketest "WHITE_E"- cost $50.00\n"YELLOW_E"/renewlic - "WHITE_E"Cost $25.00 for renew licenses");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 1491.14, 1306.33, 1093.28, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Veh insurance

	//DMV
	CreateDynamicPickup(1239, 23, -2032.7240,-117.5565,1035.1719, -1);
	format(strings, sizeof(strings), "{00FFFF}[Boat License]\n"YELLOW_E"/taketest "WHITE_E"- cost $100.00\n"YELLOW_E"/renewlic - "WHITE_E"Cost $50.00 for renew licenses");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, -2032.7240,-117.5565,1035.1719, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Veh insurance
}

hook OnPlayerConnect(playerid) {
	TakeLicense[playerid] = -1;
	TakeTestBoat[playerid] = -1;
	return 1;
}

hook OnPlayerEnterRaceCP(playerid) {
    if(TakeTestBoat[playerid] > 0) {
        if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 452)
        {
            if(IsPlayerInAnyVehicle(playerid))
            {
				if(BoatStep[playerid]) {
                    if(BoatLicense[BoatStep[playerid]][step] == 0)
					{
						PlayerPlaySound(playerid, 1056, 0, 0, 0);
						BoatStep[playerid]++;
                        switch(BoatLicense[BoatStep[playerid]][step]) {
                            case 0: SetPlayerRaceCheckpoint(playerid, 0, BoatLicense[BoatStep[playerid]][boat_posx], BoatLicense[BoatStep[playerid]][boat_posy], BoatLicense[BoatStep[playerid]][boat_posz], BoatLicense[BoatStep[playerid]+1][boat_posx], BoatLicense[BoatStep[playerid]+1][boat_posy], BoatLicense[BoatStep[playerid]+1][boat_posz], 5);
                            case 1: SetPlayerRaceCheckpoint(playerid, 1, BoatLicense[BoatStep[playerid]][boat_posx], BoatLicense[BoatStep[playerid]][boat_posy], BoatLicense[BoatStep[playerid]][boat_posz], BoatLicense[BoatStep[playerid]][boat_posx], BoatLicense[BoatStep[playerid]][boat_posy], BoatLicense[BoatStep[playerid]][boat_posz], 5);
                        }
                    }
					else if(BoatLicense[BoatStep[playerid]][step] == 1)
					{
						DisablePlayerRaceCheckpoint(playerid);				        
				        BoatStep[playerid] = 0;
				        TakeTestBoat[playerid] = 0;
				        pData[playerid][pBoatLic] = 1;
	                    pData[playerid][pBoatLicTime] = gettime() + (91 * 86400);
	                    SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"You have successfully passed the test and received your license");     
	                    SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"Your {00FFFF}Boat license "WHITE_E"is active for "YELLOW_E"3 months");   
						SetVehicleToRespawn(GetPlayerVehicleID(playerid));
						PlayerPlaySound(playerid, 183, 0.0, 0.0, 0.0);
                        GivePlayerMoneyEx(playerid, -10000);
						return 1;
					}
				}
            }
        }
    }
    if(TakeLicense[playerid] == 1)
	{
	   if(DmvSteps[playerid] > 0)
		{
		 if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426)
		    {
			 	if(IsPlayerInAnyVehicle(playerid))
				{
				    if(DmvSteps[playerid] == 2)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 3;
				        SetPlayerRaceCheckpoint(playerid, 0, 1968.0247,-1930.1829,13.0882,1824.0208,-1917.7654,13.0856, 5);
				        return 1;
				    }
				    else if(DmvSteps[playerid] == 3)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 4;
				        SetPlayerRaceCheckpoint(playerid, 0, 1824.0208,-1917.7654,13.0856,1787.3108,-1827.8440,13.0876, 5);
				        return 1;
				    }
				    else if(DmvSteps[playerid] == 4)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 5;
				        SetPlayerRaceCheckpoint(playerid, 0, 1787.3108,-1827.8440,13.0876,1688.0021,-1840.3541,13.0876, 5);
				        return 1;
				    }
				    else if(DmvSteps[playerid] == 5)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 6;
				        SetPlayerRaceCheckpoint(playerid, 0, 1688.0021,-1840.3541,13.0876,1625.1812,-1870.2305,13.0882, 5);
				        return 1;
				    }
				    else if(DmvSteps[playerid] == 6)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 7;
				        SetPlayerRaceCheckpoint(playerid, 0, 1625.1812,-1870.2305,13.0882,1571.7096,-1852.4192,13.0876, 5);
				        return 1;
				    }
					else if(DmvSteps[playerid] == 7)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 8;
				        SetPlayerRaceCheckpoint(playerid, 0, 1571.7096,-1852.4192,13.0876,1556.1931,-1730.5265,13.0875, 5);
				        return 1;
				    }
					else if(DmvSteps[playerid] == 8)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 9;
				        SetPlayerRaceCheckpoint(playerid, 0, 1556.1931,-1730.5265,13.0875,1531.9980,-1715.3065,13.0876, 5);
				        return 1;
				    }
					else if(DmvSteps[playerid] == 9)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 10;
				        SetPlayerRaceCheckpoint(playerid, 0, 1531.9980,-1715.3065,13.0876,1542.4998,-1594.5765,13.0876, 5);
				        return 1;
				    }
					else if(DmvSteps[playerid] == 10)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 11;
				        SetPlayerRaceCheckpoint(playerid, 0, 1542.4998,-1594.5765,13.0876,1680.8341,-1595.0997,13.0914, 5);
				        return 1;
				    }
					else if(DmvSteps[playerid] == 11)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 12;
				        SetPlayerRaceCheckpoint(playerid, 0, 1680.8341,-1595.0997,13.0914,1844.6248,-1614.3239,13.0882, 5);
				        return 1;
				    }
					else if(DmvSteps[playerid] == 12)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 13;
				        SetPlayerRaceCheckpoint(playerid, 0, 1844.6248,-1614.3239,13.0882,1939.3665,-1631.7688,13.0875, 5);
				        return 1;
				    }
					else if(DmvSteps[playerid] == 13)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 14;
				        SetPlayerRaceCheckpoint(playerid, 0, 1939.3665,-1631.7688,13.0875,1958.7997,-1769.8575,13.0876, 5);
				        return 1;
				    }
					else if(DmvSteps[playerid] == 14)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 15;
				        SetPlayerRaceCheckpoint(playerid, 0, 1958.7997,-1769.8575,13.0876,1980.0818,-1814.7788,13.0877, 5);
				        return 1;
				    }
					else if(DmvSteps[playerid] == 15)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 16;
				        SetPlayerRaceCheckpoint(playerid, 0, 1980.0818,-1814.7788,13.0877,2079.0569,-1824.9231,13.0873, 5);
				        return 1;
				    }
					else if(DmvSteps[playerid] == 16)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 17;
				        SetPlayerRaceCheckpoint(playerid, 0, 2079.0569,-1824.9231,13.0873,2061.8386,-1913.1362,13.2507, 5);
				        return 1;
				    }
					else if(DmvSteps[playerid] == 17)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 18;
				        SetPlayerRaceCheckpoint(playerid, 1, 2061.8386,-1913.1362,13.2507,2061.8386,-1913.1362,13.2507, 5);
				        return 1;
				    }
				    else if(DmvSteps[playerid] == 18)
				    {
				        DisablePlayerRaceCheckpoint(playerid);				        
				        DmvSteps[playerid] = 0;
				        TakeLicense[playerid] = 0;
				        pData[playerid][pTaketest] = 1;
				        pData[playerid][pDriveLic] = 1;
	                    pData[playerid][pDriveLicTime] = gettime() + (91 * 86400);
	                    SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"You have successfully passed the test and received your license");     
	                    SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"Your {00FFFF}Drive license "WHITE_E"is active for "YELLOW_E"3 months");   
						SetVehicleToRespawn(GetPlayerVehicleID(playerid));
				        return 1;
				    }
				}
			}
		}
	}
    return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(IsADmvVeh(vehicleid))
	{
		if(TakeLicense[playerid] > 0)
		{
			DmvSteps[playerid] = 2;
			SetPlayerRaceCheckpoint(playerid, 0, 2047.1849,-1930.2665,13.0876,1968.0247,-1930.1829,13.0882, 5.0);
			InfoTD_MSG(playerid, 3000, "Ikuti Checkpoint!");
		}
		else
		{
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);
			SetPlayerPos(playerid, x, y, z);
			Error(playerid, "Anda tidak memiliki izin, sikahkan taketes terlebih dahulu!");
		}
		return 1;
	}
    if(IsABoatLicense(vehicleid))
	{
		if(TakeTestBoat[playerid] > 0) SetPlayerRaceCheckpoint(playerid, 0, BoatLicense[BoatStep[playerid]][boat_posx], BoatLicense[BoatStep[playerid]][boat_posy], BoatLicense[BoatStep[playerid]][boat_posz], BoatLicense[BoatStep[playerid]+1][boat_posx], BoatLicense[BoatStep[playerid]+1][boat_posy], BoatLicense[BoatStep[playerid]+1][boat_posz], 5);
		else {
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);
			SetPlayerPos(playerid, x, y, z);
			Error(playerid, "Anda tidak memiliki izin, sikahkan taketes terlebih dahulu!");
		}
		return 1;
	}
	return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
    {
		if(IsADmvVeh(GetPlayerVehicleID(playerid)))
		{
			DisablePlayerRaceCheckpoint(playerid);
			TakeLicense[playerid] = 0;
            DmvSteps[playerid] = 0;
			SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			SetPlayerPos(playerid, 2047.97, -1903.19, 13.54);
			SendClientMessage(playerid, COLOR_ARWIN, " SERVER: {FFFFFF}Test Mengemudi gagal karena anda turun dari kendaraan");
			// return 1;
		}
        if(IsABoatLicense(GetPlayerVehicleID(playerid)))
		{
			DisablePlayerRaceCheckpoint(playerid);
			TakeTestBoat[playerid] = 0;
            BoatStep[playerid] = 0;
			SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			SetPlayerPos(playerid, 2047.97, -1903.19, 13.54);
			SendClientMessage(playerid, COLOR_ARWIN, " SERVER: {FFFFFF}Test Mengemudi gagal karena anda turun dari kendaraan");
			// return 1;
		}
	}
    return 1;
}

hook OnPlayerUpdate(playerid)
{
	if(IsADmvVeh(GetPlayerVehicleID(playerid)))
	{
		new Float:healthveh;
		GetVehicleHealth(GetPlayerVehicleID(playerid), healthveh);
		if(healthveh < 1000)
		{
			DisablePlayerRaceCheckpoint(playerid);
			SetPlayerPos(playerid, 2047.97, -1903.19, 13.54);
			TakeLicense[playerid] = 0;
            DmvSteps[playerid] = 0;
            SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			SendClientMessage(playerid, COLOR_WHITE, "INSTRUCTOR: Look wat you've done!, you wreck the car!");
			SendClientMessage(playerid, COLOR_WHITE, "NOTE: if other player hit you by purpose, report him/her to the admin!");
		}
	}
	return 1;
}