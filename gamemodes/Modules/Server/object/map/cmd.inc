
SSCANF:objectmenu(string[])
{
	if(!strcmp(string,"create",true)) return 1;
	else if(!strcmp(string,"add",true)) return 1;
	else if(!strcmp(string,"delete",true)) return 2;
	else if(!strcmp(string,"destroy",true)) return 2;
	else if(!strcmp(string,"remove",true)) return 2;
	else if(!strcmp(string,"clear",true)) return 3;
	else if(!strcmp(string,"reset",true)) return 3;
	else if(!strcmp(string,"copy",true)) return 4;
	else if(!strcmp(string,"duplicate",true)) return 4;
	else if(!strcmp(string,"move",true)) return 5;
	else if(!strcmp(string,"rot",true)) return 6;
	else if(!strcmp(string,"rotate",true)) return 6;
	else if(!strcmp(string,"select",true)) return 7;
	else if(!strcmp(string,"control",true)) return 7;
	else if(!strcmp(string,"tele",true)) return 10;
	else if(!strcmp(string,"goto",true)) return 10;
	else if(!strcmp(string,"mgethere",true)) return 11;
	else if(!strcmp(string,"mmove",true)) return 12;
	else if(!strcmp(string,"export",true)) return 13;
	else if(!strcmp(string,"model",true)) return 14;
	else if(!strcmp(string,"attach",true)) return 15;
	else if(!strcmp(string,"gethere",true)) return 16;
	else if(!strcmp(string,"material",true)) return 18;
	else if(!strcmp(string,"import",true)) return 19;
	else if(!strcmp(string,"textprop",true)) return 20;
	else if(!strcmp(string,"resetmaterial",true)) return 21;
	else if(!strcmp(string,"clearmaterial",true))	return 21;
	else if(!strcmp(string,"deletemode",true)) return 22;
	else if(!strcmp(string,"rdelete",true)) return 23;
	else if(!strcmp(string,"rremove",true)) return 23;
	else if(!strcmp(string,"rdestroy",true)) return 23;
	else if(!strcmp(string,"paintbrush",true)) return 24;
	else if(!strcmp(string,"cleanbrush",true)) return 25;
	else if(!strcmp(string,"setpriority",true)) return 26;
	else if(!strcmp(string,"priority",true)) return 26;
	return 0;
}

SSCANF:colour(string[])
{
	new color = 0;
	new red,green,blue,alpha;
	if(!sscanf(string,"dddD(255)",red,green,blue,alpha))
	{
		color = RGBAToInt(red,green,blue,alpha);
	}
	return color;
}

CMD:map(playerid, params[])
{
    static
        type[24],
        string[128],
        str[52],
        int, vw;

    if(pData[playerid][pAdmin] < 6) return PermissionError(playerid);
    if(sscanf(params, "s[24]S()[128]", type, string)) return Usage(playerid, "/map [import/unload]");
    if(!strcmp(type, "import", true))
    {
        if(sscanf(string, "s[52]dd", str, int, vw)) return Usage(playerid, "/map [import] [name map] [int] [vw]");
        new id = Iter_Free(Maps);
        format(MapData[id][eName], 52, str);
        MapData[id][eInt] = int; 
        MapData[id][eVw] = vw;
        Map_Load(playerid, str, int, vw);
        new query[512];
        mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `maps` (`Name`, `LoadBy`, `Int`, `Vw`) VALUES ('%s', '%s', '%d', '%d')", str, pData[playerid][pAdminname], int, vw);
        mysql_tquery(g_SQL, query, "OnMapCreated", "d", id);
    }
    if(!strcmp(type, "unload", true))
    {
        if(sscanf(string, "s[52]", str)) return Usage(playerid, "/map [unload] [name map]");
        foreach(new map : Maps) if(strfind(MapData[map][eName], str, true) == -1) return 1;
        new query[128];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM maps WHERE Name = '%s'", str);
        mysql_tquery(g_SQL, query);
        SendClientMessageEx(playerid, COLOR_ARWIN, "MAP: "YELLOW_E"You have removed the '"GREEN_E"%s"WHITE_E"'", str);
        foreach(new objid : DynObject) {
          if(strfind(DynObjName[objid], str, true) != -1) {
            DestroyDynamicObject(DynObj[objid]);
            //Iter_Remove(DynObject, objid);
          }
        }
        foreach(new removeid : RemoveBuild) {
          if(strfind(RemoveObj[removeid][rName], str, true) != -1) {
            CreateDynamicObject(RemoveObj[removeid][rModel], RemoveObj[removeid][rX], RemoveObj[removeid][rY], RemoveObj[removeid][rZ],0.0,0.0,0.0, 0,0);
            //Iter_Remove(RemoveBuild, removeid);
          }
        }
    }
    return 1;
}

CMD:showgtaobjects(playerid, params[]) {
	foreach(new player : Player) if(pData[player][pAdmin] > 3) {
		new index, name[52];
		AO_RESULT = db_query(AO_DB, "SELECT * FROM `buildings`");
		do
		{
			index = db_get_field_int(AO_RESULT, 0);
			db_get_field(AO_RESULT, 3, name, sizeof name[]);
			
            GTAObjectText[index] = CreateDynamic3DTextLabel(
				sprintf(""AQUA_E"[OBJECTS]\n"WHITE_E"SLOT: "YELLOW_E"[%i]\n"WHITE_E"ModelID: "YELLOW_E"[%i]", index, db_get_field_int(AO_RESULT, 1)), 
				-1, 
				db_get_field_float(AO_RESULT, 4), db_get_field_float(AO_RESULT, 5), db_get_field_float(AO_RESULT, 6) + db_get_field_float(AO_RESULT, 10), 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, player, 5
			);
		}
		while(db_next_row(AO_RESULT));
	}
	return 1;
}

CMD:hidegtaobjects(playerid, params[]) {
	for(new i = 0; i < SEARCH_DATA_SIZE; i++) DestroyDynamic3DTextLabel(GTAObjectText[i]);
	return 1;
}

CMD:rbuild(playerid, params[]) {
	if(pData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

	new model;
	if(sscanf(params,"d",model)) return Usage(playerid, "/rbuild [slot]");
	{
		if(model < 0 || model >= SEARCH_DATA_SIZE) return Error(playerid, "Slot must be between 0 and %i", SEARCH_DATA_SIZE-1);
		AO_RESULT = db_query(AO_DB, sprintf("SELECT * FROM `buildings` WHERE `ID` = %i", model));
		
		AddRemoveBuilding(db_get_field_int(AO_RESULT, 1), db_get_field_float(AO_RESULT, 4), db_get_field_float(AO_RESULT, 5), db_get_field_float(AO_RESULT, 6), 0.25);
		if(db_get_field_int(AO_RESULT, 2) != INVALID_OBJECT_ID)
			AddRemoveBuilding(db_get_field_int(AO_RESULT, 2), db_get_field_float(AO_RESULT, 4), db_get_field_float(AO_RESULT, 5), db_get_field_float(AO_RESULT, 6), 0.25);

		UpdateDynamic3DTextLabelText(GTAObjectText[model], -1, sprintf(""AQUA_E"[OBJECTS]\n"WHITE_E"SLOT: "YELLOW_E"[%i]\n"WHITE_E"ModelID: "YELLOW_E"[%i]\n"RED_E"REMOVED", model, db_get_field_int(AO_RESULT, 1)));
	}
	return 1;
}

CMD:swapbuild(playerid, params[]) {
	if(pData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

	new model;
	if(sscanf(params,"d",model)) return Usage(playerid, "/swapbuild [slot]");
	{
		if(model < 0 || model >= SEARCH_DATA_SIZE) return Error(playerid, "Slot must be between 0 and %i", SEARCH_DATA_SIZE-1);
		AO_RESULT = db_query(AO_DB, sprintf("SELECT * FROM `buildings` WHERE `ID` = %i", model));
		
		for(new i = 0; i < MAX_REMOVE_BUILDING; i++) {
			if(RemoveData[i][rModel] == 0 && RemoveData[i][rX] == db_get_field_float(AO_RESULT, 4)) {
				CreateDynamicObject(RemoveData[i][rModel], RemoveData[i][rX], RemoveData[i][rY], RemoveData[i][rZ],0.0,0.0,0.0, 0,0);
				RemoveData[i][rModel] = 0;
				RemoveData[i][rX] = RemoveData[i][rY] = RemoveData[i][rZ] = 0;
			}
		}
		UpdateDynamic3DTextLabelText(GTAObjectText[model], -1, sprintf(""AQUA_E"[OBJECTS]\n"WHITE_E"SLOT: "YELLOW_E"[%i]\n"WHITE_E"ModelID: "YELLOW_E"[%i]\n", model, db_get_field_int(AO_RESULT, 1)));
	}
	return 1;
}

CMD:object(playerid,params[])
{
	if(pData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

	new string[256],item,subparam[96];
	sscanf(params,"K<objectmenu>(0)S()[96]",item,subparam);
	switch(item)
	{
		case 1:
		{
			if(!IsNull(subparam))
			{
				new model = strval(subparam);
				new slot = Iter_Free(DynamicObjects);
				if(slot != cellmin)
				{
					new Float:cPos[3];
					GetPlayerPos(playerid,cPos[0],cPos[1],cPos[2]);
					DynamicObject[slot] = CreateDynamicObject(model,cPos[0]+2,cPos[1]+2,cPos[2],0.0,0.0,0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
					DynamicObjectPriority[slot] = 0;
					ObjectEditor[slot] = INVALID_PLAYER_ID;
					Iter_Add(DynamicObjects,slot);
					Streamer_Update(playerid);
					format(string,144,"OBJECT: "WHITE_E"Object created with "YELLOW_E"ID %d"WHITE_E", total objects: "GREEN_E"%d",slot,Iter_Count(DynamicObjects));
					SendClientMessageEx(playerid,COLOR_ARWIN,string);
				}
				else SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Full slot!");
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object create [object model id]");
		}
		case 2:
		{
			if(!IsNull(subparam))
			{
				new slot = strval(subparam);
				if(Iter_Contains(DynamicObjects,slot))
				{
					Iter_Remove(DynamicObjects,slot);
					DestroyDynamicObject(DynamicObject[slot]);
					Looping(i,MAX_OBJECT_MATERIAL_SLOT)
					{
						DynamicObjectMaterial[slot][i] = MATERIAL_TYPE_NONE;
					}
					format(string,144,"OBJECT: "WHITE_E"Object with "YELLOW_E"ID %d "WHITE_E"has been deleted, total objects: "GREEN_E"%d",slot,Iter_Count(DynamicObjects));
					SendClientMessageEx(playerid,COLOR_ARWIN,string);
				}
				else SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Invalid objectid!");
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object delete [object id]");
		}
		case 3:
		{
			if((!IsNull(subparam)) && (!strcmp(subparam,"confirm",true)))
			{
				for(new i = 0; i < MAX_REMOVE_BUILDING; i++)
				{
					if(RemoveData[i][rModel] != 0)
					{
						CreateDynamicObject(RemoveData[i][rModel], RemoveData[i][rX], RemoveData[i][rY], RemoveData[i][rZ],0.0,0.0,0.0, 0,0);
						RemoveData[i][rModel] = 0;
						RemoveData[i][rX] = RemoveData[i][rY] = RemoveData[i][rZ] = 0;
					}
				}
				foreach(new slot : DynamicObjects)
				{
					DestroyDynamicObject(DynamicObject[slot]);
					Looping(i,MAX_OBJECT_MATERIAL_SLOT)
					{
						DynamicObjectMaterial[slot][i] = MATERIAL_TYPE_NONE;
					}
				}
				format(string,144,"OBJECT: "YELLOW_E"%d objects "WHITE_E"have been cleared",Iter_Count(DynamicObjects));
				Iter_Clear(DynamicObjects);
				SendClientMessageEx(playerid,COLOR_ARWIN,string);
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"WARNING: Are you sure you want to clear all the objects ? (/object clear confirm)");
		}
		case 4:
		{
			if(!IsNull(subparam))
			{
				new slot = strval(subparam);
				if(Iter_Contains(DynamicObjects,slot))
				{
					new slot2 = Iter_Free(DynamicObjects);
					if(slot2 != cellmin)
					{
						new model,Float:cPos[3],Float:cRot[3];
						model = Streamer_GetIntData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_MODEL_ID);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_X,cPos[0]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Y,cPos[1]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Z,cPos[2]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_X,cRot[0]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_Y,cRot[1]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_Z,cRot[2]);
						DynamicObject[slot2] = CreateDynamicObject(model,cPos[0],cPos[1],cPos[2],cRot[0],cRot[1],cRot[2]);
						DynamicObjectPriority[slot2] = 0;
						Iter_Add(DynamicObjects,slot2);
						Looping(index,MAX_OBJECT_MATERIAL_SLOT)
						{
							if(DynamicObjectMaterial[slot][index] == MATERIAL_TYPE_TEXTURE)
							{
								new modelid,txdname[32],texturename[32],color;
								GetDynamicObjectMaterial(DynamicObject[slot],index,modelid,txdname,texturename,color);
								SetDynamicObjectMaterial(DynamicObject[slot2],index,modelid,txdname,texturename,color);
								DynamicObjectMaterial[slot2][index] = MATERIAL_TYPE_TEXTURE;
							}
							else if(DynamicObjectMaterial[slot][index] == MATERIAL_TYPE_MESSAGE)
							{
								new text[128],resolution,font[20],size,bold,fcolor,bcolor,alignment;
								GetDynamicObjectMaterialText(DynamicObject[slot],index,text,resolution,font,size,bold,fcolor,bcolor,alignment);
								SetDynamicObjectMaterialText(DynamicObject[slot2],index,text,resolution,font,size,bold,fcolor,bcolor,alignment);
								DynamicObjectMaterial[slot2][index] = MATERIAL_TYPE_MESSAGE;
							}
						}
						ObjectEditor[slot2] = INVALID_PLAYER_ID;
						Streamer_Update(playerid);
						format(string,144,"OBJECT: "WHITE_E"Duplicated object with "YELLOW_E"ID %d "WHITE_E" to "YELLOW_E"ID %d"WHITE_E", total objects: "GREEN_E"%d",slot,slot2,Iter_Count(DynamicObjects));
						SendClientMessageEx(playerid,COLOR_ARWIN,string);
					}
					else SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Full slot!");
				}
				else SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Invalid objectid!");
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object copy [object id]");
		}
		case 6:
		{
			new slot,Float:cRot[3];
			if(!sscanf(subparam,"dfff",slot,cRot[0],cRot[1],cRot[2]))
			{
				if(Iter_Contains(DynamicObjects,slot))
				{
					SetDynamicObjectRot(DynamicObject[slot],cRot[0],cRot[1],cRot[2]);
				}
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object rotate [object id] [rotation X] [rotation Y] [rotation Z]");
		}
		case 7:
		{
			if(GetPVarType(playerid,"EditingObject") > 0) return SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: You must first release your current object!");
			if(!IsNull(subparam))
			{
				new slot = strval(subparam);
				if(Iter_Contains(DynamicObjects,slot))
				{
					if(ObjectEditor[slot] != INVALID_PLAYER_ID)
					{
						new editor = ObjectEditor[slot];
						if(GetPVarType(editor,"EditingObject") == slot)
						{
							format(string,sizeof(string),"ERROR: %s is currently editing this object!",ReturnPlayerName(editor));
							return SendClientMessageEx(playerid,COLOR_ARWIN,string);
						}
					}
					format(string,sizeof(string),"OBJECT: "WHITE_E"Selected object "YELLOW_E"id %d",slot);
					ObjectEditor[slot] = playerid;
					SetPVarInt(playerid,"EditingObject",slot);
					EditDynamicObject(playerid,DynamicObject[slot]);
					SendClientMessageEx(playerid,COLOR_ARWIN,string);
				}
				else SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Invalid object id!");
			}
			else 
			{
				SendClientMessageEx(playerid,COLOR_ARWIN,"EDITOR: "YELLOW_E"Shoot at object to select it!");
				SelectObjectType[playerid] = OBJECT_SELECT_EDITOR;
			}
		}
		case 10:
		{
			if(!IsNull(subparam))
			{
				new slot = strval(subparam);
				if(Iter_Contains(DynamicObjects,slot))
				{
					new Float:cPos[3];
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_X,cPos[0]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Y,cPos[1]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Z,cPos[2]);
					SetPlayerPos(playerid,cPos[0],cPos[1],cPos[2]);
					format(string,144,"OBJECT: "WHITE_E"Teleported to object "YELLOW_E"id %d",slot);
					SendClientMessageEx(playerid,COLOR_ARWIN,string);
				}
			}
		}
		case 11:
		{
			if((!IsNull(subparam)) && (!strcmp(subparam,"confirm",true)))
			{
				new Float:myPos[3],Float:Pos1[3],Float:Pos2[3],Float:newPos[3];
				GetPlayerPos(playerid,myPos[0],myPos[1],myPos[2]);
				foreach(new slot : DynamicObjects)
				{
					if(slot == 0)
					{
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_X,Pos1[0]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Y,Pos1[1]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Z,Pos1[2]);
						SetDynamicObjectPos(DynamicObject[slot],myPos[0],myPos[1],myPos[2]);
					}
					else
					{
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_X,Pos2[0]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Y,Pos2[1]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Z,Pos2[2]);
						newPos[0] = (myPos[0]+(Pos2[0]-Pos1[0]));
						newPos[1] = (myPos[1]+(Pos2[1]-Pos1[1]));
						newPos[2] = (myPos[2]+(Pos2[2]-Pos1[2]));
						SetDynamicObjectPos(DynamicObject[slot],newPos[0],newPos[1],newPos[2]);
					}
				}
				format(string,144,"OBJECT: "YELLOW_E"%d objects "WHITE_E"has been teleported to your location!",Iter_Count(DynamicObjects));
				SendClientMessageEx(playerid,COLOR_ARWIN,string);
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"WARNING: Are you sure you want to teleport all the objects to your location ? (/object mgethere confirm)");
		}
		case 12:
		{
			new direction,Float:amount,Float:speed;
			if(!sscanf(subparam,"cfF(5.0)",direction,amount,speed))
			{
				if(floatround(speed) <= 0) return SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Speed cannot go below 1!");
				foreach(new slot : DynamicObjects)
				{
					new Float:cPos[3];
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_X,cPos[0]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Y,cPos[1]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Z,cPos[2]);
					switch(direction)
					{
						case 'N','n': cPos[1] += amount;
						case 'S','s': cPos[1] -= amount;
						case 'E','e': cPos[0] += amount;
						case 'W','w': cPos[0] -= amount;
						case 'U','u': cPos[2] += amount;
						case 'D','d': cPos[2] -= amount;
						default: return SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Invalid direction!");
					}
					MoveDynamicObjectEx(DynamicObject[slot],cPos[0],cPos[1],cPos[2],speed);
				}
				format(string,144,"OBJECT: "YELLOW_E"%d objects "WHITE_E"have been moved",Iter_Count(DynamicObjects));
				SendClientMessageEx(playerid,COLOR_ARWIN,string);
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object mmove [directoion (N/S/E/W/U(p)/D(own))] [amount] [opt:speed = 5.0]");
		}
		case 13:
		{
			if(!IsNull(subparam))
			{
				new name[64];
				format(name,sizeof(name),"input/objects/samp/%s.pwn",subparam);
				if(Iter_Count(DynamicObjects) != 0)
				{
					new File:hFile = fopen(name,io_write);
					new model,Float:cPos[3],Float:cRot[3], bool:writeobject, mobjects;
					for(new i = 0; i < MAX_REMOVE_BUILDING; i++)
					{
						if(RemoveData[i][rModel] != 0)
						{
							format(string, sizeof(string), "RemoveBuildingForPlayer(playerid, %i, %.3f, %.3f, %.3f, %.3f);\r\n", RemoveData[i][rModel], RemoveData[i][rX], RemoveData[i][rY], RemoveData[i][rZ], RemoveData[i][rRange]);
							fwrite(hFile,string);
						}
					}
					fwrite(hFile,"\r\n//Objects////////////////////////////////////////////////////////////////////////////////////////////////////////\r\n");

					// Temp object for setting materials
					format(string,sizeof(string),"new tmpobjid;\r\n");
					fwrite(hFile,string);
					foreach(new slot : DynamicObjects)
					{
						model = Streamer_GetIntData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_MODEL_ID);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_X,cPos[0]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Y,cPos[1]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Z,cPos[2]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_X,cRot[0]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_Y,cRot[1]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_Z,cRot[2]);
						Looping(index,MAX_OBJECT_MATERIAL_SLOT)
						{
							new modelid,txdname[32],texturename[32],color;
							GetDynamicObjectMaterial(DynamicObject[slot],index,modelid,txdname,texturename,color);
							if(modelid != 0 || color != 0 || DynamicObjectMaterial[slot][index] == MATERIAL_TYPE_MESSAGE)
							{
								writeobject = true;
								break;
							}
						}
						if(writeobject) {
							mobjects++;
							format(string,sizeof(string),"tmpobjid = CreateDynamicObject(%i,%f,%f,%f,%f,%f,%f, -1, -1, -1, 250.00, 250.00);\r\n",model,cPos[0],cPos[1],cPos[2],cRot[0],cRot[1],cRot[2]);
							fwrite(hFile,string);
							Looping(index,MAX_OBJECT_MATERIAL_SLOT)
							{
								if(DynamicObjectMaterial[slot][index] == MATERIAL_TYPE_TEXTURE)
								{
									new modelid,txdname[32],texturename[32],color;
									GetDynamicObjectMaterial(DynamicObject[slot],index,modelid,txdname,texturename,color);
									if(modelid != 0) {
										format(string,sizeof(string),"SetDynamicObjectMaterial(tmpobjid, %i, %i, %c%s%c, %c%s%c, %x);\r\n", index, modelid, 34, txdname, 34, 34,texturename, 34, color);
										fwrite(hFile,string);
									}
									else {
										format(string,sizeof(string),"SetDynamicObjectMaterial(tmpobjid, %i, -1, %c%s%c, %c%s%c, %x);\r\n", index, 34, "none", 34, 34,"none", 34, color);
										fwrite(hFile,string);
									}
								}
								if(DynamicObjectMaterial[slot][index] == MATERIAL_TYPE_MESSAGE)
								{
									new text[128],resolution,font[20],size,bold,fcolor,bcolor,alignment;
									GetDynamicObjectMaterialText(DynamicObject[slot],index,text,resolution,font,size,bold,fcolor,bcolor,alignment);
									format(string,sizeof(string),"SetDynamicObjectMaterialText(tmpobjid, %i, %c%s%c, %i, %c%s%c, %i, %i, %x, %x, %i);\r\n",
										index, 
										34, text, 34,
										resolution,
										34, font, 34,
										size,
										bold,
										fcolor,
										bcolor,
										alignment
									);
									fwrite(hFile,string);
								}
							}
						}
					}
					if(mobjects)
					{
						fwrite(hFile, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////\r\n");
						fwrite(hFile, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////\r\n");
						fwrite(hFile, "/////////////////////////////////////////////////////////////////////////////////////////////////////////////////\r\n");
					}
					foreach(new slot : DynamicObjects)
					{
						model = Streamer_GetIntData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_MODEL_ID);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_X,cPos[0]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Y,cPos[1]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Z,cPos[2]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_X,cRot[0]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_Y,cRot[1]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_Z,cRot[2]);
						Looping(index,MAX_OBJECT_MATERIAL_SLOT)
						{
							new modelid,txdname[32],texturename[32],color;
							GetDynamicObjectMaterial(DynamicObject[slot],index,modelid,txdname,texturename,color);
							if(modelid != 0 || color != 0 || DynamicObjectMaterial[slot][index] == MATERIAL_TYPE_MESSAGE)
							{
								writeobject = false;
								break;
							}
						}
						if(writeobject) {
							format(string,sizeof(string),"tmpobjid = CreateDynamicObject(%i,%f,%f,%f,%f,%f,%f, -1, -1, -1, 250.00, 250.00);\r\n",model,cPos[0],cPos[1],cPos[2],cRot[0],cRot[1],cRot[2]);
							fwrite(hFile,string);
						}
					}
					fclose(hFile);
					format(string,144,"OBJECT: "YELLOW_E"%d objects "WHITE_E"saved to file "GREEN_E"%s",Iter_Count(DynamicObjects),name);
					SendClientMessageEx(playerid,COLOR_ARWIN,string);
				}
			}
		}
		case 14:
		{
			new slot,newmodel;
			if(!sscanf(subparam,"dd",slot,newmodel))
			{
				if(Iter_Contains(DynamicObjects,slot))
				{
					Streamer_SetIntData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_MODEL_ID,newmodel);
					Streamer_Update(playerid);
				}
				else SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Invalid object slot!");
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object model [object id] [object model]");
		}
		case 15:
		{
			new slot,vid,Float:offsetx,Float:offsety,Float:offsetz,Float:rotX,Float:rotY,Float:rotZ;
			if(!sscanf(subparam,"ddF(0.0)F(0.0)F(0.0)F(0.0)F(0.0)F(0.0)",slot,vid,offsetx,offsety,offsetz,rotX,rotY,rotZ))
			{
				if(Iter_Contains(DynamicObjects,slot))
				{
					if(GetVehicleModel(vid) > 0)
					{
						AttachDynamicObjectToVehicle(DynamicObject[slot],vid,offsetx,offsety,offsetz,rotX,rotY,rotZ);
					}
					else
					{
						Streamer_SetIntData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_ATTACHED_VEHICLE,INVALID_VEHICLE_ID);
					}
				}
				else SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Invalid object slot!");
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object attach [object id] [offset X] [offset Y] [offset Z] [rotation X] [rotation Y] [rotation Z]");
		}
		case 16:
		{
			if(!IsNull(subparam))
			{
				new slot = strval(subparam);
				if(Iter_Contains(DynamicObjects,slot))
				{
					new Float:cPos[3];
					GetPlayerPos(playerid,cPos[0],cPos[1],cPos[2]);
					SetDynamicObjectPos(DynamicObject[slot],cPos[0],cPos[1],cPos[2]);
					format(string,144,"OBJECT: Teleported object id %d to your location!",slot);
					SendClientMessageEx(playerid,COLOR_ARWIN,string);
				}
			}
		}
		case 18:
		{
			new slot,index,model,txdname[32],texture[32],color[4];
			if(!sscanf(subparam,"ddds[32]s[32]D(0)D(0)D(0)D(0)",slot,index,model,txdname,texture,color[0],color[1],color[2],color[3]))
			{
				if((index >= MAX_OBJECT_MATERIAL_SLOT) || (index < 0)) return SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: index cannot go below 0 or over 9!");
				if(Iter_Contains(DynamicObjects,slot))
				{
					if(model == 0)
					{
						model = Streamer_GetIntData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_MODEL_ID);
					}
					SetDynamicObjectMaterial(DynamicObject[slot],index,model,txdname,texture,RGBAToInt(color[0],color[1],color[2],color[3]));
					DynamicObjectMaterial[slot][index] = MATERIAL_TYPE_TEXTURE;
				}
				else SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Invalid object slot!");
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object material [object id] [index] [model] [txdname] [texture] [opt: alpha] [opt: red]  [opt: green]  [opt: blue]");
		}
		case 19:
		{
			new name[32],confirm[10], dir[64],tmp[32],templastid[32],lastSlot,loaded,model,Float:pos[3],Float:rot[3];
			if(!sscanf(subparam,"s[32]S()[10]",name,confirm))
			{   
				if(IsNull(confirm)) return SendClientMessageEx(playerid,COLOR_ARWIN,"WARNING: Are you sure you wanto to import this map ? (/object import [name] confirm)");
				if(Iter_Count(DynamicObjects) == 0)
				{
					format(dir,sizeof(dir),"input/objects/samp/%s.pwn",name);
					if(fexist(dir))
					{
						new File:hFile = fopen(dir,io_read);
						while(fread(hFile,string,sizeof(string)))
						{
							strtrim(string);

							new type;
							if(strfind(string, "CreateObject(", true) != -1) type = 1;
							else if(strfind(string, "CreateDynamicObject(", true) != -1) type = 1;
							else if(strfind(string, "SetObjectMaterial(", true) != -1) type = 3;
							else if(strfind(string, "SetDynamicObjectMaterial(", true) != -1) type = 3;
							else if(strfind(string, "SetObjectMaterialText(", true) != -1) type = 4;
							else if(strfind(string, "SetDynamicObjectMaterialText(", true) != -1) type = 5;
							else continue;
							
							new assignment = strfind(string, "="); 
							if(assignment != -1) {
								strmid(templastid, string, 0, assignment);
								strtrim(templastid);
							}
							
							strmid(string, string, strfind(string, "(") + 1, strfind(string, ");"), sizeof(string));

							if (type == 1) {
								if(!sscanf(string,"p<,>dffffff",model,pos[0],pos[1],pos[2],rot[0],rot[1],rot[2])) {
									new slot = lastSlot = Iter_Free(DynamicObjects);
									if(slot == cellmin) break;
									Iter_Add(DynamicObjects,slot);
									DynamicObject[slot] = CreateDynamicObject(model,pos[0],pos[1],pos[2],rot[0],rot[1],rot[2]);
									ObjectEditor[slot] = INVALID_PLAYER_ID;
									loaded++;
								}
							}
							if (type == 3) {
								
								strreplace(string, "\"", "");
								new index,txdname[32],texture[32],color;
								if (!sscanf(string,"p<,>s[32]iis[32]s[32]x",tmp,index,model,txdname,texture,color)) {
									if(!strcmp(tmp, templastid)) {
										if(MAX_OBJECT_MATERIAL_SLOT > index >= 0)
										{
											SetDynamicObjectMaterial(DynamicObject[lastSlot],index,model,txdname,texture,color);
											DynamicObjectMaterial[lastSlot][index] = MATERIAL_TYPE_TEXTURE;
										}
									}
								}
							}
							if (type == 4) {
								strreplace(string, "\"", "");
								new text[128],index,resolution,font[32],fontsize,bold,fontcolor,backcolor,alignment;
								if (!sscanf(string, "p<,>s[32]s[128]iis[32]iixxi",tmp,text,index,resolution,font,fontsize,bold,fontcolor,backcolor,alignment)) {
									if (!strcmp(tmp, templastid)) {
										if(MAX_OBJECT_MATERIAL_SLOT > index >= 0)
										{
											SetDynamicObjectMaterialText(DynamicObject[lastSlot],index,text,resolution,font,fontsize,bold,fontcolor,backcolor,alignment);
											DynamicObjectMaterial[lastSlot][index] = MATERIAL_TYPE_MESSAGE;
										}
									}
								}
							}
							if (type == 5) {
								strreplace(string, "\"", "");
								new index,text[128],resolution,font[32],fontsize,bold,fontcolor,color,alignment;
								if(!sscanf(string,"p<,>s[32]is[128]is[32]iixxi",tmp,index,text,resolution,font,fontsize,bold,fontcolor,color,alignment)) {
									if(!strcmp(tmp, templastid)) {
										if(MAX_OBJECT_MATERIAL_SLOT > index >= 0)
										{
											SetDynamicObjectMaterialText(DynamicObject[lastSlot],index,text,resolution,font,fontsize,bold,fontcolor,color,alignment);
											DynamicObjectMaterial[lastSlot][index] = MATERIAL_TYPE_MESSAGE;
										}
									}
								}
							}
						}
						fclose(hFile);
					}
					format(string,144,"OBJECT: "YELLOW_E"%d objects "WHITE_E"loaded from file '"GREEN_E"%s"WHITE_E"'",loaded,dir);
					SendClientMessageEx(playerid,COLOR_ARWIN,string);
				}
				else SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: You must first clear your current map!");
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object import [name] [confirm]");
		}
		case 20:
		{
			new slot,index;
			if(!sscanf(subparam,"dD(0)",slot,index))
			{
				if((index >= MAX_OBJECT_MATERIAL_SLOT) || (index < 0)) return SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: index cannot go below 0 or over 9!");
				if(Iter_Contains(DynamicObjects,slot))
				{
					if(DynamicObjectMaterial[slot][index] != MATERIAL_TYPE_MESSAGE)
					{
						SetDynamicObjectMaterialText(DynamicObject[slot],index,"Text Here",OBJECT_MATERIAL_SIZE_256x128,"Arial",24,1,0xFFFFFFFF,0xFF000000);
						DynamicObjectMaterial[slot][index] = MATERIAL_TYPE_MESSAGE;
					}
					SetPVarInt(playerid,"EditingObject",slot);
					SetPVarInt(playerid,"EditingIndex",index);
					Dialog_Show(playerid,Obj_TextMenu,DIALOG_STYLE_LIST,"Material Text","Text\nResolution\nFont\nFont Size\nToggle Bold\nFont Color\nBackground Color\nText Alignment\nReset","Select","Close");
				}
				else SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Invalid object slot!");
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object textprop [object id] [index]");
		}
		case 21:
		{
			if(!IsNull(subparam))
			{
				new slot = strval(subparam);
				if(Iter_Contains(DynamicObjects,slot))
				{
					new model,Float:cPos[3],Float:cRot[3];
					model = Streamer_GetIntData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_MODEL_ID);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_X,cPos[0]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Y,cPos[1]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Z,cPos[2]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_X,cRot[0]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_Y,cRot[1]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_Z,cRot[2]);
					DestroyDynamicObject(DynamicObject[slot]);
					Looping(index,MAX_OBJECT_MATERIAL_SLOT)
					{
						DynamicObjectMaterial[slot][index] = MATERIAL_TYPE_NONE;
					}
					DynamicObject[slot] = CreateDynamicObject(model,cPos[0],cPos[1],cPos[2],cRot[0],cRot[1],cRot[2]);
					Streamer_Update(playerid);
				}
				else SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Invalid objectid!");
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object resetmaterial [object id]");
		}
		case 22:
		{
			SelectObjectType[playerid] = OBJECT_SELECT_DELETE;
			SendClientMessageEx(playerid,COLOR_ARWIN,"OBJECT: "YELLOW_E"Click an object to delete it!");
			SelectObject(playerid);
		}
		case 23:
		{
			new Float:radius;
			if(!sscanf(subparam,"f",radius))
			{
				new Float:cPos[3];
				new count = 0;
				radius = floatabs(radius);
				foreach(new slot : DynamicObjects)
				{
					GetDynamicObjectPos(DynamicObject[slot],cPos[0],cPos[1],cPos[2]);
					if(IsPlayerInRangeOfPoint(playerid,radius,cPos[0],cPos[1],cPos[2]))
					{
						new next;
						DestroyDynamicObject(DynamicObject[slot]);
						Looping(i,MAX_OBJECT_MATERIAL_SLOT)
						{
							DynamicObjectMaterial[slot][i] = MATERIAL_TYPE_NONE;
						}
						Iter_SafeRemove(DynamicObjects,slot,next);
						slot = next;
						count++;
					}
				}
				format(string,144,"OBJECT: "YELLOW_E"%d objects "WHITE_E"has been deleted, total objects: "GREEN_E"%d",count,Iter_Count(DynamicObjects));
				SendClientMessageEx(playerid,COLOR_ARWIN,string);
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object rdelete [radius]");
		}
		case 24:
		{
			new index,model,txdname[32],texture[32],color[4];
			if(!sscanf(subparam,"dds[32]s[32]D(0)D(0)D(0)D(0)",index,model,txdname,texture,color[0],color[1],color[2],color[3]))
			{
				if((index >= MAX_OBJECT_MATERIAL_SLOT) || (index < 0)) return SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: index cannot go below 0 or over 9!");
				format(string,sizeof(string),"%d|%d|%s|%s|%d",index,model,txdname,texture,RGBAToInt(color[0],color[1],color[2],color[3]));
				SetPVarString(playerid,"PaintParam",string);
				SelectObjectType[playerid] = OBJECT_SELECT_PAINT;
				SendClientMessageEx(playerid,COLOR_ARWIN,"EDITOR: "YELLOW_E"Shoot at object to paint it!");
			}
			else SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object paintbrush [index] [model] [txdname] [texture] [opt: alpha] [opt: red]  [opt: green]  [opt: blue]");
		}
		case 25:
		{
			SelectObjectType[playerid] = OBJECT_SELECT_CLEAN;
			SendClientMessageEx(playerid,COLOR_ARWIN,"EDITOR: "YELLOW_E"Shoot at object to clean it!");
		}
		case 26:
		{
			new slot,priority;
			if(sscanf(params,"dd",slot,priority)) return SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object priority [slot] [priority]");
			if(Iter_Contains(DynamicObjects,slot))
			{
				if(priority > 5 || priority < 0) return SendClientMessageEx(playerid,COLOR_ARWIN,"ERROR: Priority cannot go over 5 or below 0!");
				format(string,144,"OBJECT: "WHITE_E"Object "YELLOW_E"slot %d "WHITE_E"priority is set to "GREEN_E"%d "WHITE_E"from "RED_E"%d",slot,priority,DynamicObjectPriority[slot]);
				DynamicObjectPriority[slot] = priority;
				SendClientMessageEx(playerid,COLOR_ARWIN,string);
			}
		}
		default:
		{
			SendClientMessageEx(playerid,COLOR_ARWIN,"SYNTAX: /object [option]");
			SendClientMessageEx(playerid,COLOR_ARWIN,"OPTIONS: create, remove, clear, copy, move, rotate, select, tele, mgethere, mmove");
			SendClientMessageEx(playerid,COLOR_ARWIN,"OPTIONS: export, model, attach, gethere, material, import, textprop, resetmaterial, deletemode, rdelete");
			SendClientMessageEx(playerid,COLOR_ARWIN,"OPTIONS: paintbrush, cleanbrush, priority");
		}
	}
	return 1;
}
