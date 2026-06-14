#include <YSI\y_hooks>
// Player clicked a dynamic object
hook OnPlayerSelectDynObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
	if (pData[playerid][pEditFlatStructure] != -1) 
	{
    	new flatid = pData[playerid][pEditFlatStructure];
		switch (SelectStructureType[playerid]) {
		case STRUCTURE_SELECT_EDITOR: {
			foreach (new i : FlatStructures[flatid]) if (FlatStructure[flatid][i][structObject] == objectid) {
			pData[playerid][pEditStructure] = i;
			pData[playerid][pEditFlatStructure] = flatid;
			EditDynamicObject(playerid, objectid);
			SendCustomMessage(playerid, "FLAT", "You're now editing %s.", GetStructureNameByModel(FlatStructure[flatid][i][structModel]));
			break;
			}
		}
		case STRUCTURE_SELECT_RETEXTURE: {
			foreach (new i : FlatStructures[flatid]) if (FlatStructure[flatid][i][structObject] == objectid) {
			pData[playerid][pEditStructure] = i;
			pData[playerid][pEditFlatStructure] = flatid;
			CancelEdit(playerid);
			Dialog_Show(playerid, Dialog_FlatRetexture, DIALOG_STYLE_INPUT, "Retexture Flat Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel");
			break;
			}

			foreach (new i : FlatStaticStructs[flatid]) if (FlatStaticStruct[flatid][i][structObject] == objectid) {
			pData[playerid][pEditStructure] = i;
			pData[playerid][pEditFlatStructure] = flatid;
			CancelEdit(playerid);
			Dialog_Show(playerid, Dialog_StaticRetexture, DIALOG_STYLE_INPUT, "Retexture Flat Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel");
			break;
			}
		}
		case STRUCTURE_SELECT_DELETE: {
			foreach (new i : FlatStructures[flatid]) if (FlatStructure[flatid][i][structObject] == objectid) {
			SendCustomMessage(playerid, "FLAT", "You've deleted %s", GetStructureNameByModel(FlatStructure[flatid][i][structModel]));
			FlatStructure_Delete(flatid, i);
			break;
			}
		}
		case STRUCTURE_SELECT_COPY: {
			foreach (new i : FlatStructures[flatid]) if (FlatStructure[flatid][i][structObject] == objectid) {
			new price;

			for (new id = 0; id < sizeof(g_aHouseStructure); id ++) if (g_aHouseStructure[id][e_StructureModel] == FlatStructure[flatid][i][structModel]) {
				price = g_aHouseStructure[id][e_StructureCost];
			}

			if (pData[playerid][pComponent] < price)
				return Error(playerid, "You need %d Component(s) to copy this structure.", price);

			new copyId = FlatStructure_Copy(flatid, i);

			if (copyId == cellmin)
				return Error(playerid, "Your flat has reached maximum of structure");
			
			pData[playerid][pComponent] -= price;
			pData[playerid][pEditStructure] = copyId;
			pData[playerid][pEditFlatStructure] = flatid;
			EditDynamicObject(playerid, FlatStructure[flatid][copyId][structObject]);
			SendCustomMessage(playerid, "BUILDER", "You have copied structure for "GREEN_E"%d component(s)", price);
			SendCustomMessage(playerid, "BUILDER", "You're now editing copied object of %s.", GetStructureNameByModel(FlatStructure[flatid][i][structModel]));
			break;
			}
		}
		}
	}
	return 1;
}

hook OnPlayerEditDynamicObj(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(response == EDIT_RESPONSE_FINAL)
	{
        if (pData[playerid][pEditStructure] != -1 && pData[playerid][pEditFlatStructure] != -1) 
		{
			new flatid = pData[playerid][pEditFlatStructure],
			slot = pData[playerid][pEditStructure];
			if (flatid != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) {
				if (!IsPointInDynamicArea(FlatRoom[flatid][flatRoomArea], x, y, z))
					return Error(playerid, "You can't place structure outside the flat area"), CancelEdit(playerid), FlatStructure_Refresh(flatid, slot);

				FlatStructure[flatid][slot][structPos][0] = x;
				FlatStructure[flatid][slot][structPos][1] = y;
				FlatStructure[flatid][slot][structPos][2] = z;
				FlatStructure[flatid][slot][structRot][0] = rx;
				FlatStructure[flatid][slot][structRot][1] = ry;
				FlatStructure[flatid][slot][structRot][2] = rz;
				
				SetDynamicObjectPos(objectid,x,y,z);
				SetDynamicObjectRot(objectid,rx,ry,rz);
				FlatStructure_Refresh(flatid, slot);
				FlatStructure_Save(flatid, slot, true, SAVE_STRUCTURE_POS);

				SendCustomMessage(playerid, "FLAT", "You have edited the structure position of \"%s"WHITE_E"\".", GetStructureNameByModel(FlatStructure[flatid][slot][structModel]));

				pData[playerid][pEditStructure] = -1;
				pData[playerid][pEditFlatStructure] = -1;
			}
			return 1;
		}
		else if (pData[playerid][pEditStaticStructure] != -1 && pData[playerid][pEditFlatStructure] != -1) 
		{
			new flatid = pData[playerid][pEditFlatStructure],
			slot = pData[playerid][pEditStaticStructure];
			FlatStaticStruct[flatid][slot][structPos][0] = x;
			FlatStaticStruct[flatid][slot][structPos][1] = y;
			FlatStaticStruct[flatid][slot][structPos][2] = z;
			FlatStaticStruct[flatid][slot][structRot][0] = rx;
			FlatStaticStruct[flatid][slot][structRot][1] = ry;
			FlatStaticStruct[flatid][slot][structRot][2] = rz;
			
			SetDynamicObjectPos(objectid,x,y,z);
			SetDynamicObjectRot(objectid,rx,ry,rz);
			FlatStructure_Refresh(flatid, slot, false);
			FlatStructure_Save(flatid, slot, false, SAVE_STRUCTURE_POS);

			SendCustomMessage(playerid, "FLAT", "You have edited the static structure position");

			pData[playerid][pEditStaticStructure] = -1;
			pData[playerid][pEditFlatStructure] = -1;
			return 1;
		}
        else if (editDoorFlat[playerid] != -1 && pData[playerid][pEditStaticStructure] != -1) 
        {
            new flatid = editDoorFlat[playerid],
            slot = pData[playerid][pEditStaticStructure];

            FlatStaticStruct[flatid][slot][structPos][0] = x;
            FlatStaticStruct[flatid][slot][structPos][1] = y;
            FlatStaticStruct[flatid][slot][structPos][2] = z;
            FlatStaticStruct[flatid][slot][structRot][0] = rx;
            FlatStaticStruct[flatid][slot][structRot][1] = ry;
            FlatStaticStruct[flatid][slot][structRot][2] = rz;
            
            SetDynamicObjectPos(objectid,x,y,z);
            SetDynamicObjectRot(objectid,rx,ry,rz);
            FlatStructure_Refresh(flatid, slot, false);
            FlatStructure_Save(flatid, slot, false, SAVE_STRUCTURE_POS);

            pData[playerid][pEditStaticStructure] = -1;
            editDoorFlat[playerid] = -1;

            SendCustomMessage(playerid,"FLATROOM","Flat door position has been saved");
            return 1;
        }
    }
    if(response == EDIT_RESPONSE_CANCEL)
	{
        if (pData[playerid][pEditStructure] != -1 && pData[playerid][pEditFlatStructure] != -1) 
		{
			new flatid = pData[playerid][pEditFlatStructure],
			slot = pData[playerid][pEditStructure];
			FlatStructure_Refresh(flatid, slot);
			pData[playerid][pEditStructure] = -1;
			pData[playerid][pEditFlatStructure] = -1;
			return 1;
		}
		if (pData[playerid][pEditStaticStructure] != -1 && pData[playerid][pEditFlatStructure] != -1) 
		{
			new flatid = pData[playerid][pEditFlatStructure],
			slot = pData[playerid][pEditStaticStructure];
			FlatStructure_Refresh(flatid, slot, false);
			pData[playerid][pEditStaticStructure] = -1;
			pData[playerid][pEditFlatStructure] = -1;
			return 1;
		}
        if (editDoorFlat[playerid] != -1 && pData[playerid][pEditStaticStructure] != -1) 
		{
			new flatid = editDoorFlat[playerid],
			slot = pData[playerid][pEditStaticStructure];

			FlatStructure_Refresh(flatid, slot, false);
			SendCustomMessage(playerid,"FLATROOM","You've canceled editing flat door");
			editDoorFlat[playerid] = -1;
			pData[playerid][pEditStaticStructure] = -1;
			return 1;
		}
    }
    return 1;
}