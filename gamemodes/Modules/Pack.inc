DEFINE_HOOK_REPLACEMENT( Unoccupied , Uncp );
#include <YSI_Coding\y_hooks>
#include <tp.inc>

#define CHEAT_TYPES 10

enum
{
	CHEAT_FLY_HACK,
	CHEAT_SPEED_HACK,
	CHEAT_INVISIBLE,
	CHEAT_JETPACK,
	CHEAT_TROLL_1,
	CHEAT_FAKE_KILL_1,
	CHEAT_TP,
	CHEAT_AB,
	CHEAT_HP,
	CHEAT_AM
};

enum AC_Enums
{
	AC_Warnings[CHEAT_TYPES],
	AC_Kicked,
	Float: AC_POS[3],
	AC_LFWeapon,
	Float: AC_Velocity[3],
};

new 
	AC_VARIABLE[MAX_PLAYERS][AC_Enums];

new player_rpc_count[MAX_PLAYERS];
new player_rpc_last_time[MAX_PLAYERS];

forward OnIncomingRPC(playerid, rpcid, BitStream:bs);
public OnIncomingRPC(playerid, rpcid, BitStream:bs)
{


    if (rpcid == 136)
    {
        new currentTime = GetTickCount();


        if (player_rpc_count[playerid] == 0)
        {
            player_rpc_count[playerid] = 1;
            player_rpc_last_time[playerid] = currentTime;
        }
        else
        {
      
            if (currentTime - player_rpc_last_time[playerid] <= 3000)
            {
                player_rpc_count[playerid]++;
                if (player_rpc_count[playerid] >= 5)
                {
                 
                    Kick(playerid);
                    player_rpc_count[playerid] = 0;
                    player_rpc_last_time[playerid] = 0;
                }
            }
            else
            {

                player_rpc_count[playerid] = 1;
                player_rpc_last_time[playerid] = currentTime;
            }
        }
    }
    
    return 1;
}

public OnPlayerTeleport(playerid, Float:distance)
{
	if(pData[playerid][pAdmin] < 1)
	{
	    if(!IsPlayerInRangeOfPoint(playerid, 3.0, pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ]))
	    {
		    if(AC_VARIABLE[playerid][AC_Warnings][CHEAT_TP] > 0) 
		    	return OnCheatDetect(playerid, "Teleport hack");

			OnWarningExecute(playerid, CHEAT_TP, "Teleport hack");
		}
	}
	return 1;
}

public OnPlayerAirbreak(playerid)
{
	if(pData[playerid][pAdmin] < 1)
	{
	    if(AC_VARIABLE[playerid][AC_Warnings][CHEAT_AB] > 0) 
			return OnCheatDetect(playerid, "Airbreak hack");

		OnWarningExecute(playerid, CHEAT_AB, "Airbreak hack");
	}
	return 1;
}

function cheatDetect(playerid, cheat_id)
{
	if(pData[playerid][pAdminDuty]) return 0;
	switch(cheat_id)
	{
		case CHEAT_FLY_HACK:
		{
			new 
				playerAnim = GetPlayerAnimationIndex(playerid);

			if(playerAnim == 373 || playerAnim == 958 || playerAnim == 959 || playerAnim == 1231 || playerAnim == 1189 || playerAnim == 1538 || playerAnim == 1539 || playerAnim == 1543)
			{
				new
					Float:z,
					Float:vx,
					Float:vy,
					Float:vz;

				GetPlayerPos(playerid, z, z, z);
				GetPlayerVelocity(playerid, vx, vy, vz);

				if((z > 20.0) && (0.9 <= floatsqroot((vx * vx) + (vy * vy) + (vz * vz)) <= 1.9) && !pData[playerid][pAdmin] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					if(AC_VARIABLE[playerid][AC_Warnings][CHEAT_FLY_HACK] > 4) 
						return OnCheatDetect(playerid, "fly-hack");

					SendStaffMessage(COLOR_LIGHTRED, "AdmWarning: %s[%i] is possibly fly hack, speed: %i km/h.", ReturnName(playerid), playerid, GetVehicleSpeed(GetPlayerVehicleID(playerid)));
					OnWarningExecute(playerid, CHEAT_FLY_HACK, "fly-hack");
				}
			}
		}
		case CHEAT_SPEED_HACK:
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !IsAPlane(GetPlayerVehicleID(playerid)) && GetVehicleSpeed(playerid) > 300)
			{
				if(AC_VARIABLE[playerid][AC_Warnings][CHEAT_SPEED_HACK] > 7) 
						return OnCheatDetect(playerid, "speed-hack");

				SendStaffMessage(COLOR_LIGHTRED, "AdmWarning: %s[%i] is possibly vehicle speed hack, speed: %i km/h.", ReturnName(playerid), playerid, GetVehicleSpeed(GetPlayerVehicleID(playerid)));
				OnWarningExecute(playerid, CHEAT_SPEED_HACK, "speed-hack");
			}
		}
		case CHEAT_INVISIBLE:
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING && !pData[playerid][pAdmin]) 
				return OnCheatDetect(playerid, "invisible or spectate");
		}
		case CHEAT_JETPACK:
		{
			if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK && !pData[playerid][pAdmin]) 
				return OnCheatDetect(playerid, "jetpack");
		}
		case CHEAT_TROLL_1:
		{
			new 
				Float: velX, Float: velY, Float: velZ,
				Float: X, Float: Y, Float: Z;

			GetPlayerPos(playerid, X, Y, Z);

			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && !IsPlayerInAnyVehicle(playerid))
			{
				if(Z > 5.0000)
				{
					GetPlayerVelocity(playerid, velX, velY, velZ);

					new 
						Float: velXAmount = velX - AC_VARIABLE[playerid][AC_Velocity][0],
						Float: velYAmount = velY - AC_VARIABLE[playerid][AC_Velocity][1];

					if(velXAmount > 3.0 || velXAmount < -4.0 || velYAmount  > 10.0 || velYAmount < -10.0 || velZ == 0.100000) 
						return OnCheatDetect(playerid, "troll-hack #1");
				}

				GetPlayerVelocity(playerid, AC_VARIABLE[playerid][AC_Velocity][0], AC_VARIABLE[playerid][AC_Velocity][1], AC_VARIABLE[playerid][AC_Velocity][2]);
			}

			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				GetVehicleVelocity(GetPlayerVehicleID(playerid), velX, velY, velZ);

				if(velY == -90.000000 && velZ == 0.100000) 
					return OnCheatDetect(playerid, "troll-hack #2");
			}
		}
		case CHEAT_FAKE_KILL_1:
		{
			if(AC_VARIABLE[playerid][AC_Warnings][CHEAT_FAKE_KILL_1] > 3) 
				return OnCheatDetect(playerid, "fake-kill #1");

			OnWarningExecute(playerid, CHEAT_SPEED_HACK, "fake-kill #1");
		}
	}

	return true;
}

OnWarningExecute(playerid, cheat_id, const cheat_name[])
{
	if(AC_VARIABLE[playerid][AC_Kicked]) 
		return true;

	AC_VARIABLE[playerid][AC_Warnings][cheat_id] ++;

	new 
		String[146];

	format(String, sizeof String, "[ANTICHEAT] %s possible used cheats %s [%d warnings]!", 
		ReturnName(playerid), cheat_name, AC_VARIABLE[playerid][AC_Warnings][cheat_id]);
	SendClientMessageToAll(TOMATO, String);

	return true;
}

OnCheatDetect(playerid, const cheat_name[])
{
	if(AC_VARIABLE[playerid][AC_Kicked]) 
		return true;

	new 
		String[100];

	format(String, sizeof String, "%s Telah di kick dari server, reason: %s", ReturnName(playerid), cheat_name);
	SendClientMessageToAll(TOMATO, String);

	format(String, 70, "You has been kicked by Admbot, reason: %s", cheat_name);
	SendClientMessage(playerid, TOMATO, String);

	AC_VARIABLE[playerid][AC_Kicked] = true;
	KickEx(playerid);

	return true;
}

function onCheatTime()
{
	foreach(new i : Player)
	{
        if(pData[i][IsLoggedIn] == false) return 0;
	    if(pData[i][pSpawned] == 0) return 0;
		if(!AC_VARIABLE[i][AC_Kicked])
		{
			forex(x, 5) cheatDetect(i, x);

			#if defined AC_DEBUG_MODE
				va_SendClientMessage(i, -1, "[OLD] X: %f, Y: %f, Z: %f", AC_VARIABLE[i][AC_POS][0], AC_VARIABLE[i][AC_POS][1], AC_VARIABLE[i][AC_POS][2]);
			#endif

			#if defined AC_DEBUG_MODE
				va_SendClientMessage(i, -1, "[NEW] X: %f, Y: %f, Z: %f", AC_VARIABLE[i][AC_POS][0], AC_VARIABLE[i][AC_POS][1], AC_VARIABLE[i][AC_POS][2]);
				va_SendClientMessage(i, -1, "Anim: %d / Vehicle: %d", GetPlayerAnimationIndex(i), GetPlayerVehicleID(i));
			#endif
		}
	}
	return 1;
}

//================== PUBLICS ==================//

hook OnPlayerConnect(playerid)
{
	AC_VARIABLE[playerid][AC_Kicked] = false;
	AC_VARIABLE[playerid][AC_LFWeapon] = 0;
	for(new i = 0; i < CHEAT_TYPES; i ++) if(AC_VARIABLE[playerid][AC_Warnings][i] > 0) AC_VARIABLE[playerid][AC_Warnings][i] = 0;
	for(new i = 0; i < 3; i ++) AC_VARIABLE[playerid][AC_Velocity][i] = -1;

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if(damagedid != INVALID_PLAYER_ID && bodypart == 0 && weaponid < 16) cheatDetect(playerid, CHEAT_FAKE_KILL_1);

	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerUpdate(playerid)
{
	// Anti Fcrash
    if(GetPlayerWeapon(playerid) == 40) return Kick(playerid); // jangan dikasih delay kick

	// Anti Fcrash
    if(pData[playerid][IsLoggedIn] != true) 
    {
    	return Kick(playerid); // jangan dikasih delay kick
    }
    return 1;
}

hook OnUncpVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	if((new_x != new_x || new_y != new_y || new_z != new_z ||
		floatabs(new_x) >= 25000.0 || floatabs(new_y) >= 25000.0 || floatabs(new_z) >= 25000.0)) 
			return OnCheatDetect(playerid, "troll-hack #3");

	new 
		Float: X, Float: Y, Float: Z;

	GetVehiclePos(vehicleid, X, Y, Z);

	if(passenger_seat > 0)
	{
		new 
			Float: difference = new_z - Z;

		if(difference >= -5.0 && (floatabs(new_x - X) >= 12.0 || floatabs(new_y - Y) >= 12.0)) 
			return OnCheatDetect(playerid, "troll-hack #4");
	}

	return Y_HOOKS_CONTINUE_RETURN_1;
}