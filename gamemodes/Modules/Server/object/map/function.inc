
function Maps_Load() {
  new rows = cache_num_rows();
  for (new i = 0; i < rows; i ++) {
    Iter_Add(Maps, i);
    cache_get_value_int(i, "ID", MapData[i][eID]);
    cache_get_value(i, "Name", MapData[i][eName], 64);
    cache_get_value(i, "LoadBy", MapData[i][eLoadedBy], 52);
    cache_get_value_int(i, "Int", MapData[i][eInt]);
    cache_get_value_int(i, "Vw", MapData[i][eVw]);
    Map_Load(-1, MapData[i][eName], MapData[i][eInt], MapData[i][eVw]);
  }
  return 1;
}

function OnMapCreated(id) {
  MapData[id][eID] = cache_insert_id();
  ImportMap_Save(id);
  return 1;
}

ImportMap_Save(id)
{
  new query[2024];
  format(query, sizeof(query), "UPDATE `maps` SET `Name`='%s', `LoadBy`='%s', `Int`='%d', `Vw`='%d' WHERE `ID`='%d'",
  MapData[id][eName], MapData[id][eLoadedBy], MapData[id][eInt], MapData[id][eVw], MapData[id][eID]);
  mysql_tquery(g_SQL, query);
  return 1;
}

Map_Load(playerid, name[], int, vw) {
  new string[212],dir[64],tmp[32],templastid[32],lastSlot,loaded,model,Float:pos[3],Float:rot[3],loadremove;
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
      else if(strfind(string, "RemoveBuildingForPlayer(", true) != -1) type = 6;
      else continue;
      
      new assignment = strfind(string, "="); 
      if(assignment != -1) {
        strmid(templastid, string, 0, assignment);
        strtrim(templastid);
      }
      
      strmid(string, string, strfind(string, "(") + 1, strfind(string, ");"), sizeof(string));

      if (type == 1) {
        if(!sscanf(string,"p<,>dffffff",model,pos[0],pos[1],pos[2],rot[0],rot[1],rot[2])) {
          new slot = lastSlot = Iter_Free(DynObject);
          if(slot == cellmin) break;
          Iter_Add(DynObject,slot);
          DynObj[slot] = CreateDynamicObject(model,pos[0],pos[1],pos[2],rot[0],rot[1],rot[2],vw,int);
          format(DynObjName[slot], 52, name);
          loaded++;
        }
      }
      else if (type == 3) {
        
        strreplace(string, "\"", "");
        new index,txdname[32],texture[32],color;
        if (!sscanf(string,"p<,>s[32]iis[32]s[32]x",tmp,index,model,txdname,texture,color)) {
          if(!strcmp(tmp, templastid)) {
            if(10 > index >= 0)
            {
              SetDynamicObjectMaterial(DynObj[lastSlot],index,model,txdname,texture,color);
              DynObMats[lastSlot][index] = 1;
            }
          }
        }
      }
      else if (type == 4) {
        strreplace(string, "\"", "");
        new text[128],index,resolution,font[32],fontsize,bold,fontcolor,backcolor,alignment;
        if (!sscanf(string, "p<,>s[32]s[128]iis[32]iixxi",tmp,text,index,resolution,font,fontsize,bold,fontcolor,backcolor,alignment)) {
          if (!strcmp(tmp, templastid)) {
            if(10 > index >= 0)
            {
              SetDynamicObjectMaterialText(DynObj[lastSlot],index,text,resolution,font,fontsize,bold,fontcolor,backcolor,alignment);
              DynObMats[lastSlot][index] = 2;
            }
          }
        }
      }
      else if (type == 5) {
        strreplace(string, "\"", "");
        new index,text[128],resolution,font[32],fontsize,bold,fontcolor,color,alignment;
        if(!sscanf(string,"p<,>s[32]is[128]is[32]iixxi",tmp,index,text,resolution,font,fontsize,bold,fontcolor,color,alignment)) {
          if(!strcmp(tmp, templastid)) {
            if(10 > index >= 0)
            {
              SetDynamicObjectMaterialText(DynObj[lastSlot],index,text,resolution,font,fontsize,bold,fontcolor,color,alignment);
              DynObMats[lastSlot][index] = 2;
            }
          }
        }
      }
      else if (type == 6) {
        if(sscanf(string, "p<,>s[16]ifff", tmp, model,pos[0],pos[1],pos[2]))
          continue;
        new slotremove = INVALID_ITERATOR_SLOT;

        if ((slotremove = Iter_Free(RemoveBuild)) != INVALID_ITERATOR_SLOT) {
          Iter_Add(RemoveBuild, slotremove);

          format(RemoveObj[slotremove][rName], 52, name);
          RemoveObj[slotremove][rModel] = model;
          RemoveObj[slotremove][rX] = pos[0];
          RemoveObj[slotremove][rY] = pos[1];
          RemoveObj[slotremove][rZ] = pos[2];

          foreach(new player : Player) RemoveBuildingForPlayer(player, RemoveObj[slotremove][rModel], RemoveObj[slotremove][rX], RemoveObj[slotremove][rY], RemoveObj[slotremove][rZ], 0.250);
        }
        if(slotremove == cellmin) break;
        loadremove++;
      }
    }
    fclose(hFile);
  }
  if(loadremove) SendClientMessageEx(playerid, COLOR_ARWIN, "OBJECT: "YELLOW_E"%d Remove "WHITE_E"loaded from file '"GREEN_E"%s"WHITE_E"'",loadremove,dir);
  format(string,144,"OBJECT: "YELLOW_E"%d objects "WHITE_E"loaded from file '"GREEN_E"%s"WHITE_E"'",loaded,dir);
  SendClientMessageEx(playerid,COLOR_ARWIN,string);
  return 1;
}

MoveDynamicObjectEx(objectid,Float:x,Float:y,Float:z,Float:speed)
{
	if(IsDynamicObjectMoving(objectid)) StopDynamicObject(objectid);
	return MoveDynamicObject(objectid,x,y,z,speed);
}

// Add a remove building
AddRemoveBuilding(model, Float:x, Float:y, Float:z, Float:range)
{
	for(new i = 0; i < MAX_REMOVE_BUILDING; i++)
	{
	    if(RemoveData[i][rModel] == 0)
	    {
	        RemoveData[i][rModel] = model;
	        RemoveData[i][rX] = x;
	        RemoveData[i][rY] = y;
	        RemoveData[i][rZ] = z;
	        RemoveData[i][rRange] = range;
			foreach(new j : Player) RemoveBuildingForPlayer(j, model, x, y, z, range);
			return 1;
	    }
	}
	return 0;
}
