#include <YSI\y_hooks>

hook OnPlayerEditDynObj(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(response == EDIT_RESPONSE_FINAL)
	{
		if (editDoorFactionID[playerid] != -1) {
			new mode = editDoorFactioMode[playerid];
            if(mode == 2) {
                new id = editDoorFactionID[playerid];
				DoorFaction[id][dfPosInt][0] = x;
                DoorFaction[id][dfPosInt][1] = y;
                DoorFaction[id][dfPosInt][2] = z;
                DoorFaction[id][dfPosInt][3] = rx;
                DoorFaction[id][dfPosInt][4] = ry;
                DoorFaction[id][dfPosInt][5] = rz;

				DoorFaction_Sync(id);
				DoorFaction_Save(id);
				SendCustomMessage(playerid, "DOOR", "You've successfully editing button door faction!");
				editDoorFactionID[playerid] = -1;
				editDoorFactioMode[playerid] = -1;
            }
            else if(mode == 3) {
                new id = editDoorFactionID[playerid];
				DoorFaction[id][dfPosExt][0] = x;
                DoorFaction[id][dfPosExt][1] = y;
                DoorFaction[id][dfPosExt][2] = z;
                DoorFaction[id][dfPosExt][3] = rx;
                DoorFaction[id][dfPosExt][4] = ry;
                DoorFaction[id][dfPosExt][5] = rz;

				DoorFaction_Sync(id);
				DoorFaction_Save(id);
				SendCustomMessage(playerid, "DOOR", "You've successfully editing button door faction!");
				editDoorFactionID[playerid] = -1;
				editDoorFactioMode[playerid] = -1;
            }
		}
	}
	if(response == EDIT_RESPONSE_CANCEL)
	{
		if (editDoorFactionID[playerid] != -1) {
			new mode = editDoorFactioMode[playerid];
			if(mode == 0 || mode == 1 || mode == 2 || mode  == 3)
			{
				new id = editDoorFactionID[playerid];
				DoorFaction_Sync(id);

				editDoorFactionID[playerid] = -1;		
				editDoorFactioMode[playerid] = -1;
				SendCustomMessage(playerid, "DOOR", "You've canceled editing door faction.");
				return 1;
			}
		}
	}
	return 0;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) if((newkeys & KEY_SECONDARY_ATTACK))
    {
        foreach(new id : DoorsFaction) if(IsPlayerInRangeOfPoint(playerid, 2.8, DoorFaction[id][dfPosInt][0], DoorFaction[id][dfPosInt][1], DoorFaction[id][dfPosInt][2]) ||
        IsPlayerInRangeOfPoint(playerid, 2.8, DoorFaction[id][dfPosExt][0], DoorFaction[id][dfPosExt][1], DoorFaction[id][dfPosExt][2])) {
            if(DoorFaction[id][dfFaction] != pData[playerid][pFaction]) return Error(playerid, "Acces denied!");
            if (DoorFaction[id][dfStatus] == 0)  {
                ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, 0, 0, 0, 0, 0);
                DoorFaction[id][dfStatus] = 1;
                DoorFaction_Timer[id] = 1;
                MoveDynamicObject(DoorFaction[id][dfObj], DoorFaction[id][dfMove][0], DoorFaction[id][dfMove][1], DoorFaction[id][dfMove][2], 3.0, DoorFaction[id][dfMove][3], DoorFaction[id][dfMove][4], DoorFaction[id][dfMove][5]);
                SetTimerEx("DoorFaction_Closed", 5000, false, "d", id);
            } else {
                if (DoorFaction_Timer[id]) {
                Error(playerid, "Please wait untill the door is closed!");
                }
            }
        }
    }
	return 1;
}
