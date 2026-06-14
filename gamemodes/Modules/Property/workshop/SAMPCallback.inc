#include <YSI\y_hooks>
hook OnPlayerEditDynamicObj(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(response == EDIT_RESPONSE_FINAL)
	{ 
        if(WorkshopEdit[playerid][0] == 1)
		{
			new wsid = WorkshopEdit[playerid][2];
			switch(WorkshopEdit[playerid][1])
			{
				case 1: {
					WorkshopData[wsid][WorkshopPos][0] = x;
					WorkshopData[wsid][WorkshopPos][1] = y; 
					WorkshopData[wsid][WorkshopPos][2] = z;
					WorkshopData[wsid][WorkshopPos][3] = rx;
					WorkshopData[wsid][WorkshopPos][4] = ry;
					WorkshopData[wsid][WorkshopPos][5] = rz;
					SetDynamicObjectPos(objectid,  WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]);
					SetDynamicObjectRot(objectid, WorkshopData[wsid][WorkshopPos][3], WorkshopData[wsid][WorkshopPos][4], WorkshopData[wsid][WorkshopPos][5]);
					SendCustomMessage(playerid, "EDIT", ""AQUA_E"Successfully edit workshop ID %d", wsid);
					WorkshopSave(wsid);
					WorkshopRefresh(wsid);
					Streamer_UpdateEx(playerid, WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]);
					WorkshopEdit[playerid][0] = -1;
					WorkshopEdit[playerid][1] = -1;
					WorkshopEdit[playerid][2] = -1;
				}
				case 2: {
					WorkshopData[wsid][BoardPos][0] = x;
					WorkshopData[wsid][BoardPos][1] = y; 
					WorkshopData[wsid][BoardPos][2] = z;
					WorkshopData[wsid][BoardPos][3] = rx;
					WorkshopData[wsid][BoardPos][4] = ry;
					WorkshopData[wsid][BoardPos][5] = rz;
					SetDynamicObjectPos(objectid,  WorkshopData[wsid][BoardPos][0], WorkshopData[wsid][BoardPos][1], WorkshopData[wsid][BoardPos][2]);
					SetDynamicObjectRot(objectid, WorkshopData[wsid][BoardPos][3], WorkshopData[wsid][BoardPos][4], WorkshopData[wsid][BoardPos][5]);
					SendCustomMessage(playerid, "EDIT", ""AQUA_E"Successfully edit workshop ID %d", wsid);
					WorkshopSave(wsid);
					WorkshopRefresh(wsid);
					Streamer_UpdateEx(playerid, WorkshopData[wsid][BoardPos][0], WorkshopData[wsid][BoardPos][1], WorkshopData[wsid][BoardPos][2]);
					WorkshopEdit[playerid][0] = -1;
					WorkshopEdit[playerid][1] = -1;
					WorkshopEdit[playerid][2] = -1;
				}
				case 3: {
					WorkshopData[wsid][GatePosF][0] = x;
					WorkshopData[wsid][GatePosF][1] = y; 
					WorkshopData[wsid][GatePosF][2] = z;
					WorkshopData[wsid][GatePosF][3] = rx;
					WorkshopData[wsid][GatePosF][4] = ry;
					WorkshopData[wsid][GatePosF][5] = rz;
					SetDynamicObjectPos(objectid,  WorkshopData[wsid][GatePosF][0], WorkshopData[wsid][GatePosF][1], WorkshopData[wsid][GatePosF][2]);
					SetDynamicObjectRot(objectid, WorkshopData[wsid][GatePosF][3], WorkshopData[wsid][GatePosF][4], WorkshopData[wsid][GatePosF][5]);
					SendCustomMessage(playerid, "EDIT", ""AQUA_E"Successfully edit workshop ID %d", wsid);
					WorkshopSave(wsid);
					WorkshopRefresh(wsid);
					Streamer_UpdateEx(playerid, WorkshopData[wsid][GatePosF][0], WorkshopData[wsid][GatePosF][1], WorkshopData[wsid][GatePosF][2]);
					WorkshopEdit[playerid][0] = -1;
					WorkshopEdit[playerid][1] = -1;
					WorkshopEdit[playerid][2] = -1;
				}
				case 4: {
					WorkshopData[wsid][GatePosR][0] = x;
					WorkshopData[wsid][GatePosR][1] = y; 
					WorkshopData[wsid][GatePosR][2] = z;
					WorkshopData[wsid][GatePosR][3] = rx;
					WorkshopData[wsid][GatePosR][4] = ry;
					WorkshopData[wsid][GatePosR][5] = rz;
					SetDynamicObjectPos(objectid,  WorkshopData[wsid][GatePosR][0], WorkshopData[wsid][GatePosR][1], WorkshopData[wsid][GatePosR][2]);
					SetDynamicObjectRot(objectid, WorkshopData[wsid][GatePosR][3], WorkshopData[wsid][GatePosR][4], WorkshopData[wsid][GatePosR][5]);
					SendCustomMessage(playerid, "EDIT", ""AQUA_E"Successfully edit workshop ID %d", wsid);
					WorkshopSave(wsid);
					WorkshopRefresh(wsid);
					Streamer_UpdateEx(playerid, WorkshopData[wsid][GatePosR][0], WorkshopData[wsid][GatePosR][1], WorkshopData[wsid][GatePosR][2]);
					WorkshopEdit[playerid][0] = -1;
					WorkshopEdit[playerid][1] = -1;
					WorkshopEdit[playerid][2] = -1;
				}
			}
			return 1;
		}
	}
	return 0;
}
