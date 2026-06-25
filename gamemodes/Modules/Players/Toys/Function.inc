
function LoadPlayerToys(extraid)
{
	static
		string[128];
    new rows;
	rows = cache_num_rows();

	for (new i = 0; i != rows; i ++) {
		AccData[extraid][i][accExists] = true;

		cache_get_value(i, "Type", AccData[extraid][i][accName], 32);
		
		cache_get_value(i, "Color1", string);
		sscanf(string, "p<|>ddd",AccData[extraid][i][accColor1][0],AccData[extraid][i][accColor1][1],AccData[extraid][i][accColor1][2]);
		
		cache_get_value(i, "Color2", string);
		sscanf(string, "p<|>ddd",AccData[extraid][i][accColor2][0],AccData[extraid][i][accColor2][1],AccData[extraid][i][accColor2][2]);
		
		cache_get_value(i, "Offset", string);
		sscanf(string, "p<|>fff",AccData[extraid][i][accOffset][0],AccData[extraid][i][accOffset][1],AccData[extraid][i][accOffset][2]);

		cache_get_value(i, "Rot", string);
		sscanf(string, "p<|>fff",AccData[extraid][i][accRot][0],AccData[extraid][i][accRot][1],AccData[extraid][i][accRot][2]);

		cache_get_value(i, "Scale", string);
		sscanf(string, "p<|>fff",AccData[extraid][i][accScale][0],AccData[extraid][i][accScale][1],AccData[extraid][i][accScale][2]);

		cache_get_value_int(i, "ID", AccData[extraid][i][accID]);
		cache_get_value_int(i, "Model", AccData[extraid][i][accModel]);
		cache_get_value_int(i, "Bone", AccData[extraid][i][accBone]);
		cache_get_value_int(i, "Show", AccData[extraid][i][accShow]);
		
    }
	return 1;
}

Dyoc_Attach(playerid)
{
    for (new index = 0; index != MAX_ACC; index ++) 
    {
        if(AccData[playerid][index][accShow] == 1) 
        {
            SetPlayerAttachedObject(playerid,index, AccData[playerid][index][accModel], AccData[playerid][index][accBone],
                AccData[playerid][index][accOffset][0], AccData[playerid][index][accOffset][1], AccData[playerid][index][accOffset][2],
                AccData[playerid][index][accRot][0], AccData[playerid][index][accRot][1], AccData[playerid][index][accRot][2],
                AccData[playerid][index][accScale][0], AccData[playerid][index][accScale][1], AccData[playerid][index][accScale][2], RGBAToARGB(GetRGBColor(playerid, index, 1)), RGBAToARGB(GetRGBColor(playerid, index, 2)));
        }
    }
    return 1;
}

Aksesoris_Attach(playerid, index)
{
    SetPlayerAttachedObject(playerid,index, AccData[playerid][index][accModel], AccData[playerid][index][accBone],
        AccData[playerid][index][accOffset][0], AccData[playerid][index][accOffset][1], AccData[playerid][index][accOffset][2],
        AccData[playerid][index][accRot][0], AccData[playerid][index][accRot][1], AccData[playerid][index][accRot][2],
        AccData[playerid][index][accScale][0], AccData[playerid][index][accScale][1], AccData[playerid][index][accScale][2], RGBAToARGB(GetRGBColor(playerid, index, 1)), RGBAToARGB(GetRGBColor(playerid, index, 2)));
            
    AccData[playerid][index][accShow] = 1;
            
    MySQL_SavePlayerToys(playerid, index);
    return 1;
}

MySQL_SavePlayerToys(playerid, id)
{
    new query[1024],
        bone = (!AccData[playerid][id][accBone]) ? (1) : (AccData[playerid][id][accBone]);

    format(query,sizeof(query),"UPDATE `aksesoris` SET `Model`='%d',`Bone`='%d',`Color1`='%03d|%03d|%03d',`Color2`='%d|%d|%d',`Offset`='%.04f|%.04f|%.04f',`Rot`='%.04f|%.04f|%.04f'",
        AccData[playerid][id][accModel],
        bone,
        AccData[playerid][id][accColor1][0],
        AccData[playerid][id][accColor1][1],
        AccData[playerid][id][accColor1][2],
        AccData[playerid][id][accColor2][0],
        AccData[playerid][id][accColor2][1],
        AccData[playerid][id][accColor2][2],
        AccData[playerid][id][accOffset][0],
        AccData[playerid][id][accOffset][1],
        AccData[playerid][id][accOffset][2],
        AccData[playerid][id][accRot][0],
        AccData[playerid][id][accRot][1],
        AccData[playerid][id][accRot][2]
    );

    format(query,sizeof(query),"%s,`Scale`='%.04f|%.04f|%.04f', `Type`='%s', `Show`='%d' WHERE `ID` = '%d'",
        query,
        AccData[playerid][id][accScale][0],
        AccData[playerid][id][accScale][1],
        AccData[playerid][id][accScale][2],
        AccData[playerid][id][accName],
        AccData[playerid][id][accShow],
        AccData[playerid][id][accID]
    );

    return mysql_tquery(g_SQL, query);
}

Aksesoris_GetCount(playerid)
{
    new count;
    for (new i = 0; i != MAX_ACC; i++) if(AccData[playerid][i][accExists]) {
        count++;
    }
    return count;
}

Aksesoris_Create(playerid, model, name[])
{
    new query[128];
    
    for (new i = 0; i != MAX_ACC; i++) if(!AccData[playerid][i][accExists]) {
        AccData[playerid][i][accExists] = 1;
        AccData[playerid][i][accShow] = 1;
        format(AccData[playerid][i][accName], 32, name);
        
        AccData[playerid][i][accModel] = model;
        
        AccData[playerid][i][accBone] = 1;
        
        pData[playerid][pAksesoris] = i;
        AccData[playerid][i][accColor1][0] = AccData[playerid][i][accColor1][1] = AccData[playerid][i][accColor1][2] = 255;
        AccData[playerid][i][accColor2][0] = AccData[playerid][i][accColor2][1] = AccData[playerid][i][accColor2][2] = 255;
        
        AccData[playerid][i][accScale][0] = AccData[playerid][i][accScale][1] = AccData[playerid][i][accScale][2] = 1.0;

        format(query,sizeof(query),"INSERT INTO `aksesoris` (`accID`) VALUES (%d)", pData[playerid][pID]);
        mysql_tquery(g_SQL, query, "OnAksesorisCreated", "dd", playerid, i);
        
        return i;
    }
    return 1;
}

function OnAksesorisCreated(playerid, id)
{
    AccData[playerid][id][accID] = cache_insert_id();
    MySQL_SavePlayerToys(playerid, id);
    Aksesoris_Attach(playerid, id);

    new string[256+1];
    for(new i; i < sizeof(accBones); i++)
    {
        format(string,sizeof(string),"%s%s\n",string,accBones[i]);
    }
    Dialog_Show(playerid, AksesorisBone, DIALOG_STYLE_LIST, "Edit Bone",string,"Select","Close");
    SendCustomMessage(playerid, "DYOC","Accessory created, type /dyoc to edit this accessory.");
    return 1;
}

GetAksesorisNameByModel(model)
{
    new
        name[32];

    for (new i = 0; i < sizeof(accList); i ++) if(accList[i][accListModel] == model) {
        strcat(name, accList[i][accListName]);

        break;
    }
    return name;
}
