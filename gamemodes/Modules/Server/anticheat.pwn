new
    hack_health[MAX_PLAYERS] = {0, ...},
    hack_armour[MAX_PLAYERS] = {0, ...},
    hack_teleport[MAX_PLAYERS] = {0, ...},
    hack_airbreak[MAX_PLAYERS] = {0, ...},
    hack_vehiclehealth[MAX_PLAYERS] = {0, ...},
    hack_vehtele[MAX_PLAYERS] = {0, ...},
    hack_fly[MAX_PLAYERS] = {0, ...},
    wrap_veh[MAX_PLAYERS] = {0, ...},
    veh_speedhack[MAX_PLAYERS] = {0, ...},
    onfoot_speedhack[MAX_PLAYERS] = {0, ...}
;

function OnCheatDetected(playerid, ip_address[], type, code)
{
    if(!pData[playerid][IsLoggedIn] && !IsPlayerInEvent(playerid) && !pData[playerid][pAdminDuty] && !pData[playerid][pAdmin])
        return 0;

    if(type) BlockIpAddress(ip_address, 0);
	else {
        switch(code)
        {
            case 0: {
                if(++hack_airbreak[playerid] == 3)
                {
                    // foreach (new i : Player) {
                    //     SendClientMessageEx(i, TOMATO, "BotCmd: %s have been kicked from the server.", ReturnName(playerid));
                    //     SendClientMessageEx(i, TOMATO, "Reason: Airbreak Hack");
                    // }
                    hack_airbreak[playerid] = 0;
                   // KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat onfoot airbreak hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 1: {
                if(++hack_airbreak[playerid] == 3)
                {
                    // foreach (new i : Player) {
                    //     SendClientMessageEx(i, TOMATO, "BotCmd: %s have been kicked from the server.", ReturnName(playerid));
                    //     SendClientMessageEx(i, TOMATO, "Reason: Vehicle Airbreak Hack");
                    // }
                    hack_airbreak[playerid] = 0;
                    //KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat vehicle airbreak hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 2:
            {
                new Float:x, Float:y, Float:z;
                AntiCheatGetPos(playerid, x, y, z);
                SetPlayerPos(playerid, x, y, z);

                if(++hack_teleport[playerid] == 3)
                {
                    // foreach (new i : Player) {
                    //     SendClientMessageEx(i, TOMATO, "BotCmd: %s have been kicked from the server.", ReturnName(playerid));
                    //     SendClientMessageEx(i, TOMATO, "Reason: Teleport Hack");
                    // }
                    hack_teleport[playerid] = 0;
                    //KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat teleport hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 3:
            {
                new Float:x, Float:y, Float:z;
                AntiCheatGetPos(playerid, x, y, z);
                SetPlayerPos(playerid, x, y, z);

                if(++hack_vehtele[playerid] == 3)
                {
                    // foreach (new i : Player) {
                    //     SendClientMessageEx(i, TOMATO, "BotCmd: %s have been kicked from the server.", ReturnName(playerid));
                    //     SendClientMessageEx(i, TOMATO, "Reason: Vehicle Teleport Hack");
                    // }
                    hack_vehtele[playerid] = 0;
                    //KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat vehicle teleport hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 4:
            {
                if (++wrap_veh[playerid] == 3) {
                    // foreach (new i : Player) {
                    //     SendClientMessageEx(i, TOMATO, "BotCmd: %s have been kicked from the server.", ReturnName(playerid));
                    //     SendClientMessageEx(i, TOMATO, "Reason: Wrap vehicle hack");
                    // }
                    wrap_veh[playerid] = 0;
                    //KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat wrap vehicle hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 5: {
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat vehicle teleport to player hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
        
            case 7: {
                if(++hack_fly[playerid] == 3)
                {
                    // foreach (new i : Player) {
                    //     SendClientMessageEx(i, TOMATO, "BotCmd: %s have been kicked from the server.", ReturnName(playerid));
                    //     SendClientMessageEx(i, TOMATO, "Reason: Fly Hack");
                    // }
                    hack_fly[playerid] = 0;
                    //KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: %s IP: "RED_E"%s "YELLOW_E"possible cheat fly hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }    
            case 8: {
                if(++hack_fly[playerid] == 3)
                {
                    // foreach (new i : Player) {
                    //     SendClientMessageEx(i, TOMATO, "BotCmd: %s have been kicked from the server.", ReturnName(playerid));
                    //     SendClientMessageEx(i, TOMATO, "Reason: Vehicle Fly Hack");
                    // }
                    hack_fly[playerid] = 0;
                    //KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat vehicle fly hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 9: {
                if (++onfoot_speedhack[playerid] == 3) {
                    // foreach (new i : Player) {
                    //     SendClientMessageEx(i, TOMATO, "BotCmd: %s have been kicked from the server.", ReturnName(playerid));
                    //     SendClientMessageEx(i, TOMATO, "Reason: Onfoot speed hack");
                    // }
                    onfoot_speedhack[playerid] = 0;
                    //KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat onfoot speed hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 10: {
                if (++veh_speedhack[playerid] == 3) {
                    // foreach (new i : Player) {
                    //     SendClientMessageEx(i, TOMATO, "BotCmd: %s have been kicked from the server.", ReturnName(playerid));
                    //     SendClientMessageEx(i, TOMATO, "Reason: Vehicle speed hack");
                    // }
                    veh_speedhack[playerid] = 0;
                    //KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat vehicle speed hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 11: 
            {
                if(++hack_vehiclehealth[playerid] == 3)
                {
                    new Float:health;
                    AntiCheatGetVehicleHealth(AntiCheatGetVehicleID(playerid), health);
                    SetVehicleHealth(AntiCheatGetVehicleID(playerid), health);

                    // foreach (new i : Player) {
                    //     SendClientMessageEx(i, TOMATO, "BotCmd: %s have been kicked from the server.", ReturnName(playerid));
                    //     SendClientMessageEx(i, TOMATO, "Reason: Vehicle Health Hack");
                    // }
                    hack_vehiclehealth[playerid] = 0;
                    //KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat vehicle health hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 12: 
            {
                if(++hack_health[playerid] == 3)
                {
                    new Float:health;
                    AntiCheatGetHealth(playerid, health);
                    SetPlayerHealth(playerid, health);

                    // foreach (new i : Player) {
                    //     SendClientMessageEx(i, TOMATO, "BotCmd: %s have been kicked from the server.", ReturnName(playerid));
                    //     SendClientMessageEx(i, TOMATO, "Reason: Health Hack");
                    // }
                    hack_health[playerid] = 0;
                    //KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat health hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 13: 
            {
                if(++hack_armour[playerid] == 3)
                {
                    new Float:armor;
                    AntiCheatGetArmour(playerid, armor);
                    SetPlayerArmour(playerid, armor);

                    // foreach (new i : Player) {
                    //     SendClientMessageEx(i, TOMATO, "BotCmd: %s have been kicked from the server.", ReturnName(playerid));
                    //     SendClientMessageEx(i, TOMATO, "Reason: Armour Hack");
                    // }
                    hack_armour[playerid] = 0;
                    //KickEx(playerid);
                    return 1;
                }
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat armour hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 15: 
            {
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat weapon hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
                //KickEx(playerid);
            }
            case 16: 
            {
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat add ammo hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 17: 
            {
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat infinite ammo hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
            case 18:
            {
                SendAdminMessage(COLOR_YELLOW, "AdmWarn: [id:%d] "RED_E"%s (%s) "YELLOW_E"IP: "RED_E"%s "YELLOW_E"possible cheat using special animations hack.", playerid, ReturnName(playerid), pData[playerid][pAdminname], pData[playerid][pIP]);
            }
        }
        // AntiCheatKickWithDesync(playerid, code);
    }
    return 1;
}