//ELM - created by Blacky 03/02/2018
#include <YSI\y_hooks>

#define LIGHT_TOGGLE_DELAY 500
#define KeyPressed(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define KeyRelease(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
// ---------------------------------------

hook OnVehicleDeath(vehicleid, killerid)
{
	if(pvData[vehicleid][vELM] == false)
	{
		pvData[vehicleid][vEmergencyLights] = 0;
		ToggleVehicleLights(vehicleid, 0);
		pvData[vehicleid][vLights] = 0;
	}
    return 1;
}

// ---------------------------------------
//ELM

stock ToggleVehicleLights(vehicleid, toggle)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, engine, toggle, alarm, doors, bonnet, boot, objective);
	return true;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new VehID = GetPlayerVehicleID(playerid);
	if(KeyPressed(KEY_SUBMISSION))
	{
		// if(IsABoat(VehID) || IsAPlane(VehID) || IsAHelicopter(VehID)) return true;
		if(!pvData[VehID][vELM])
		{
			ToggleVehicleLights(VehID, 1);
			pvData[VehID][vEmergencyLights] = 0;

			pvData[VehID][vELM] = true;
		}
		else if(pvData[VehID][vELM])
		{
			pvData[VehID][vEmergencyLights] = 0;
			ToggleVehicleLights(VehID, pvData[VehID][vLights]);

			new panels, doors, lights, tires;
			GetVehicleDamageStatus(VehID, panels, doors, lights, tires);
			UpdateVehicleDamageStatus(VehID, panels, doors, 0, tires);
			// endClientMessageEx(playerid, COLOR_ARWIN, "ELM: "WHITE_E"Emergency Lights Turned {8B0000}Off");
			pvData[VehID][vELM] = false;
		}
	}
	return 1;
}

CMD:elm(playerid)
{
	if(pData[playerid][pFaction] == 1)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(!IsPlayerInAnyVehicle(playerid)) return Error(playerid, "You must be inside a vehicle.");

		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER && (GetPlayerVehicleSeat(playerid) != 1 && GetPlayerState(playerid) == PLAYER_STATE_PASSENGER))
		{
			return Error(playerid, "You must the driver or the front passenger.");
		
		}	

		if(!pvData[vehicleid][vELM])
		{
			ToggleVehicleLights(vehicleid, 1);
			pvData[vehicleid][vEmergencyLights] = 0;

			pvData[vehicleid][vELM] = true;
			SendClientMessageEx(playerid, COLOR_ARWIN, "ELM: "WHITE_E"Emergency Lights Turned {4BB74C}On");
		}
		else if(pvData[vehicleid][vELM])
		{
			pvData[vehicleid][vEmergencyLights] = 0;
			ToggleVehicleLights(vehicleid, pvData[vehicleid][vLights]);

			new panels, doors, lights, tires;
			GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
			UpdateVehicleDamageStatus(vehicleid, panels, doors, 0, tires);
			SendClientMessageEx(playerid, COLOR_ARWIN, "ELM: "WHITE_E"Emergency Lights Turned {8B0000}Off");
			pvData[vehicleid][vELM] = false;
		}
	}	
	else if(pData[playerid][pFaction] == 3)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(!IsPlayerInAnyVehicle(playerid)) return Error(playerid, "You must be inside a vehicle.");

		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER && (GetPlayerVehicleSeat(playerid) != 1 && GetPlayerState(playerid) == PLAYER_STATE_PASSENGER))
		{
			return Error(playerid, "You must the driver or the front passenger.");
		
		}	

		if(!pvData[vehicleid][vELM])
		{
			ToggleVehicleLights(vehicleid, 1);
			pvData[vehicleid][vEmergencyLights] = 0;

			pvData[vehicleid][vELM] = true;
			SendClientMessageEx(playerid, COLOR_ARWIN, "ELM: "WHITE_E"Emergency Lights Turned {4BB74C}On");
		}
		else if(pvData[vehicleid][vELM])
		{
			pvData[vehicleid][vEmergencyLights] = 0;
			ToggleVehicleLights(vehicleid, pvData[vehicleid][vLights]);

			new panels, doors, lights, tires;
			GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
			UpdateVehicleDamageStatus(vehicleid, panels, doors, 0, tires);
			SendClientMessageEx(playerid, COLOR_ARWIN, "ELM: "WHITE_E"Emergency Lights Turned {8B0000}Off");
			pvData[vehicleid][vELM] = false;
		}
	}
	return true;
}

CMD:togsiren(playerid, params[])
{
	if(pData[playerid][pFaction] != 1) return Error(playerid, "You not SAPD");
	return callcmd::elm(playerid);
}

stock encode_lights(light1, light2, light3, light4)
{
	return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);
}
