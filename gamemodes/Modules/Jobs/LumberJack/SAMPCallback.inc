#include <YSI\y_hooks>


hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_FIRE) || PRESSED(KEY_HANDBRAKE))
	{
        new tid = GetClosestTree(playerid);
        if(tid != -1 && GetPlayerWeapon(playerid) == WEAPON_CHAINSAW)
        {
            if(!Tree_BeingEdited(tid) && !TreeData[tid][treeGettingCut] && TreeData[tid][treeSeconds] < 1)
            {
                TreeData[tid][treeGettingCut] = true;
                Player_ResetCutting(playerid);
                Tree_Refresh(tid);
                SetPlayerEnergy(playerid, pData[playerid][pEnergy]-8.0);
                MoveDynamicObject(TreeData[tid][treeObjID], TreeData[tid][treeX], TreeData[tid][treeY], TreeData[tid][treeZ] + 0.03, 0.025, TreeData[tid][treeRX], TreeData[tid][treeRY] - 80.0, TreeData[tid][treeRZ]);
                Streamer_Update(playerid);
            }
            return 1;
        }
	}
    if(newkeys & KEY_NO && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
        new tid = -1;
        if ((tid = GetClosestTree(playerid)) != -1) {
            if(TreeData[tid][treeGettingCut]) {
                new Float: x, Float: y, Float: z;
                new vehicleid = pData[playerid][pLastCar];
                GetVehicleBoot(pData[playerid][pLastCar], x, y, z);
                if(GetPlayerDistanceFromPoint(playerid, x, y, z) > 6) return Error(playerid, "Your last vehicle is too far away.");  
                if(vehicleid == INVALID_VEHICLE_ID) return Error(playerid, "You not in near any vehicles.");
                if(!IsAPickup(vehicleid)) return Error(playerid, "You're not near a pickup car.");
                if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Anda harus keluar dari kendaraan.");
                if(Vehicle_LumberCount(vehicleid) >= LUMBER_LIMIT) return Error(playerid, "You can't load any more logs to this vehicle.");
                pData[playerid][pActivity] = SetTimerEx("LoadTimber", 250, true, "id", playerid, tid);
                PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Loading Timber");
                for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                TogglePlayerControllable(playerid, 0);
                SetPlayerArmedWeapon(playerid, WEAPON_CHAINSAW);
                ApplyAnimation(playerid, "BOMBER", "BOM_PLANT_LOOP", 4.1, 1, 0, 0, 1, 0, 1);
            }
        }
	}
	return 1;
}
