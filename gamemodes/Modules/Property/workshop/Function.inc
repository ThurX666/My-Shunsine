WorkshopSave(id)
{
	new dquery[2048];
	mysql_format(g_SQL, dquery, sizeof(dquery), "UPDATE workshop SET `name` = '%s', `owner` = '%s', `price` = '%d', `type` = '%d', `dynamic` = '%d', `status` = '%d', `cash` = '%d', `component` = '%d', `text` = '%s'",
	WorkshopData[id][Name],
	WorkshopData[id][Owner],
	WorkshopData[id][Price],
    WorkshopData[id][Type],
    WorkshopData[id][Dynamic],
	WorkshopData[id][StatusWorkshop],
	WorkshopData[id][StorageWorkshop][0],
	WorkshopData[id][StorageWorkshop][1],
    WorkshopData[id][TextWorkshop]);

	mysql_format(g_SQL, dquery, sizeof(dquery), "%s, `wspos` = '%.2f|%.2f|%.2f|%.2f|%.2f|%.2f', `gateposf` = '%.2f|%.2f|%.2f|%.2f|%.2f|%.2f', `gateposr` = '%.2f|%.2f|%.2f|%.2f|%.2f|%.2f', `boardpos` = '%.2f|%.2f|%.2f|%.2f|%.2f|%.2f' WHERE ID='%d'", 
	dquery,
	WorkshopData[id][WorkshopPos][0],
	WorkshopData[id][WorkshopPos][1],
	WorkshopData[id][WorkshopPos][2],
	WorkshopData[id][WorkshopPos][3],
	WorkshopData[id][WorkshopPos][4],
	WorkshopData[id][WorkshopPos][5],
	WorkshopData[id][GatePosF][0],
	WorkshopData[id][GatePosF][1],
	WorkshopData[id][GatePosF][2],
	WorkshopData[id][GatePosF][3],
	WorkshopData[id][GatePosF][4],
	WorkshopData[id][GatePosF][5],
    WorkshopData[id][GatePosR][0],
	WorkshopData[id][GatePosR][1],
	WorkshopData[id][GatePosR][2],
	WorkshopData[id][GatePosR][3],
	WorkshopData[id][GatePosR][4],
	WorkshopData[id][GatePosR][5],
	WorkshopData[id][BoardPos][0],
	WorkshopData[id][BoardPos][1],
	WorkshopData[id][BoardPos][2],
	WorkshopData[id][BoardPos][3],
	WorkshopData[id][BoardPos][4],
	WorkshopData[id][BoardPos][5],
    id);
	return mysql_tquery(g_SQL, dquery);
}

function WorkshopLoad()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new wsid, string[521];
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", wsid);
            cache_get_value_name(i, "name", WorkshopData[wsid][Name], 52);
		    cache_get_value_name(i, "owner", WorkshopData[wsid][Owner], MAX_PLAYER_NAME);
			cache_get_value_name_int(i, "price", WorkshopData[wsid][Price]);
            cache_get_value_name_int(i, "type", WorkshopData[wsid][Type]);
            cache_get_value_name_int(i, "dynamic", WorkshopData[wsid][Dynamic]);
            cache_get_value_name_int(i, "status", WorkshopData[wsid][StatusWorkshop]);
            cache_get_value_name_int(i, "cash", WorkshopData[wsid][StorageWorkshop][0]);
            cache_get_value_name_int(i, "component", WorkshopData[wsid][StorageWorkshop][1]);
            cache_get_value_name(i, "text", WorkshopData[wsid][TextWorkshop], 128);
			cache_get_value(i, "wspos", string);
      		sscanf(string, "p<|>ffffff", WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2], WorkshopData[wsid][WorkshopPos][3], WorkshopData[wsid][WorkshopPos][4], WorkshopData[wsid][WorkshopPos][5]);
			cache_get_value(i, "gateposf", string);
      		sscanf(string, "p<|>ffffff", WorkshopData[wsid][GatePosF][0], WorkshopData[wsid][GatePosF][1], WorkshopData[wsid][GatePosF][2], WorkshopData[wsid][GatePosF][3], WorkshopData[wsid][GatePosF][4], WorkshopData[wsid][GatePosF][5]);
            cache_get_value(i, "gateposr", string);
      		sscanf(string, "p<|>ffffff", WorkshopData[wsid][GatePosR][0], WorkshopData[wsid][GatePosR][1], WorkshopData[wsid][GatePosR][2], WorkshopData[wsid][GatePosR][3], WorkshopData[wsid][GatePosR][4], WorkshopData[wsid][GatePosR][5]);
            cache_get_value(i, "boardpos", string);
      		sscanf(string, "p<|>ffffff", WorkshopData[wsid][BoardPos][0], WorkshopData[wsid][BoardPos][1], WorkshopData[wsid][BoardPos][2], WorkshopData[wsid][BoardPos][3], WorkshopData[wsid][BoardPos][4], WorkshopData[wsid][BoardPos][5]);
            
			WorkshopData[wsid][ID] = wsid;
			WorkshopData[wsid][StatusWorkshop] = 0;
			Iter_Add(Workshop, wsid);
			WorkshopRefresh(wsid);
	    }
	    printf("*** [Database: Loaded] workshop data (%d count).", rows);
	}
}

GetTypeWorkshop(wsid) {
	new type[52];
	switch(WorkshopData[wsid][Type]) {
		case 0: {
			type = "Transfender";
		}
		case 1: {
			type = "WAA & Lowrider";
		}
	}
	return type;
}

WorkshopRefresh(wsid) {
    new string[212], label[256];
    if(wsid != -1) {
        if(IsValidDynamicObject(WorkshopObj[wsid])) DestroyDynamicObject(WorkshopObj[wsid]);
        if(IsValidDynamicObject(WorkshopData[wsid][ObjectBoard])) DestroyDynamicObject(WorkshopData[wsid][ObjectBoard]);
        if(IsValidDynamicObject(WorkshopData[wsid][ObjectGate][0])) DestroyDynamicObject(WorkshopData[wsid][ObjectGate][0]);
		if(IsValidDynamicObject(WorkshopData[wsid][ObjectGate][1])) DestroyDynamicObject(WorkshopData[wsid][ObjectGate][1]);
        if(IsValidDynamicObject(WorkshopData[wsid][ObjectButton])) DestroyDynamicObject(WorkshopData[wsid][ObjectButton]);
        if(IsValidDynamic3DTextLabel(WorkshopLabel[wsid])) DestroyDynamic3DTextLabel(WorkshopLabel[wsid]);
        if(IsValidDynamicPickup(WorkshopPickup[wsid])) DestroyDynamicPickup(WorkshopPickup[wsid]);

        if(strcmp(WorkshopData[wsid][Owner], "-")) format(string, sizeof(string), "%s\n%s", ReplaceString(WorkshopData[wsid][Name]), ReplaceString(WorkshopData[wsid][TextWorkshop]));
        else format(string, sizeof(string), "{00FFFF}[ID: %d]\n{00FF00}This workshop for sell\n{FFFFFF}Addres: {FFFF00}%s\n{FFFFFF}Type: {FFFF00}%s\n{FFFFFF}Price: {FFFF00}$%s", wsid, GetLocation(WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]), GetTypeWorkshop(wsid), FormatMoney(WorkshopData[wsid][Price]));

        if(WorkshopData[wsid][Dynamic] == 0) {
            // Static: Create visual objects
            WorkshopObj[wsid] = CreateDynamicObject(12929, WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2], WorkshopData[wsid][WorkshopPos][3], WorkshopData[wsid][WorkshopPos][4], WorkshopData[wsid][WorkshopPos][5], 0, 0, -1, 300.00, 300.00); 

            if(WorkshopData[wsid][BoardPos][0] != 0) {
                WorkshopData[wsid][ObjectBoard] = CreateDynamicObject(18244, WorkshopData[wsid][BoardPos][0], WorkshopData[wsid][BoardPos][1], WorkshopData[wsid][BoardPos][2], WorkshopData[wsid][BoardPos][3], WorkshopData[wsid][BoardPos][4], WorkshopData[wsid][BoardPos][5], 0, 0, -1, 300.00, 300.00); 
                SetDynamicObjectMaterialText(WorkshopData[wsid][ObjectBoard], 0, string, 90, "Arial", 20, 1, 0xFFFFFFFF, 0xFF000000, 1);
            }
            switch(WorkshopData[wsid][StatusWorkshop])
            {
                case 0: { //Close
                    if(WorkshopData[wsid][GatePosF][0] != 0) WorkshopData[wsid][ObjectGate][0] = CreateDynamicObject(13028,  WorkshopData[wsid][GatePosF][0], WorkshopData[wsid][GatePosF][1], WorkshopData[wsid][GatePosF][2], WorkshopData[wsid][GatePosF][3], WorkshopData[wsid][GatePosF][4], WorkshopData[wsid][GatePosF][5], 0, 0, -1, 300.00, 300.00); //Depan
                    if(WorkshopData[wsid][GatePosR][0] != 0) WorkshopData[wsid][ObjectGate][1] = CreateDynamicObject(13028,  WorkshopData[wsid][GatePosR][0], WorkshopData[wsid][GatePosR][1], WorkshopData[wsid][GatePosR][2], WorkshopData[wsid][GatePosR][3], WorkshopData[wsid][GatePosR][4], WorkshopData[wsid][GatePosR][5], 0, 0, -1, 300.00, 300.00); //Samping
                }
                case 1: { //Open
                    if(WorkshopData[wsid][GatePosF][0] != 0) WorkshopData[wsid][ObjectGate][0] = CreateDynamicObject(13028,  WorkshopData[wsid][GatePosF][0], WorkshopData[wsid][GatePosF][1], WorkshopData[wsid][GatePosF][2], WorkshopData[wsid][GatePosF][3], WorkshopData[wsid][GatePosF][4], WorkshopData[wsid][GatePosF][5], 0, 0, -1, 300.00, 300.00); //Depan
                    if(WorkshopData[wsid][GatePosR][0] != 0) WorkshopData[wsid][ObjectGate][1] = CreateDynamicObject(13028,  WorkshopData[wsid][GatePosR][0], WorkshopData[wsid][GatePosR][1], WorkshopData[wsid][GatePosR][2]-5, WorkshopData[wsid][GatePosR][3], WorkshopData[wsid][GatePosR][4], WorkshopData[wsid][GatePosR][5], 0, 0, -1, 300.00, 300.00); //Samping
                }
            }
        } else {
            // Dynamic: Create 3D text label + pickup with workshop info
            if(strcmp(WorkshopData[wsid][Owner], "-"))
            {
                format(label, sizeof(label), "{00FFFF}[id:%d]\n{FFFFFF}%s\n{FFFFFF}Owner: {FFFF00}%s",
                    wsid,
                    ReplaceString(WorkshopData[wsid][Name]),
                    WorkshopData[wsid][Owner]);
            }
            else
            {
                format(label, sizeof(label), "{00FFFF}[id:%d]\n{FFFFFF}%s\n{00FF00}This workshop for sell\n{FFFFFF}Type: {FFFF00}%s\n{FFFFFF}Price: {00FF00}$%s",
                    wsid,
                    ReplaceString(WorkshopData[wsid][Name]),
                    GetTypeWorkshop(wsid),
                    FormatMoney(WorkshopData[wsid][Price]));
            }
            WorkshopLabel[wsid] = CreateDynamic3DTextLabel(label, 0xFFFFFFFF, WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2] + 0.8, 20.0, .testlos = 1, .worldid = 0, .interiorid = 0);
            WorkshopPickup[wsid] = CreateDynamicPickup(1274, 23, WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2], 0, 0, _, 10.0); // Pickup label point for dynamic workshop
        }
    }
    return 1;
}

function WorkshopCreate(id)
{
	WorkshopSave(id);
	return 1;
}

OwnerWorkshop(playerid, id)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(id == -1) return 0;
	if(!strcmp(WorkshopData[id][Owner], pData[playerid][pName], true)) return 1;
	return 0;
}

Workshop_IsEmployee(playerid, wsid) {
	new str[128], Cache: cache;
	format(str, sizeof(str), "SELECT * FROM `workshop_employee` WHERE `Name`='%s' AND `Workshop`='%d'", ReturnName(playerid), WorkshopData[wsid][ID]);
	cache = mysql_query(g_SQL, str);
	new result = cache_num_rows();
	cache_delete(cache);
	return result;
}

WorkshopEmployee_Add(playerid, wsid)
{
	new str[128];
	format(str, sizeof(str), "INSERT INTO `workshop_employee` SET `Name`='%s', `Workshop`='%d', `Time`=UNIX_TIMESTAMP()", ReturnName(playerid), WorkshopData[wsid][ID]);
	mysql_tquery(g_SQL, str);
	return 1;
}

WorkshopEmployee_Remove(id)
{
	new query[200];
	format(query,sizeof(query),"DELETE FROM `workshop_employee` WHERE `ID`='%d'", id);
	mysql_tquery(g_SQL, query);
	return 1;
}

WorkshopEmployee_RemoveAll(wsid)
{
	new query[200];
	format(query,sizeof(query),"DELETE FROM `workshop_employee` WHERE `Workshop`='%d'", WorkshopData[wsid][ID]);
	mysql_tquery(g_SQL, query);
	return 1;
}

WorkshopEmployee_GetCount(wsid)
{
	new query[144], Cache: check, count;
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `workshop_employee` WHERE `Workshop` = '%d'", WorkshopData[wsid][ID]);
	check = mysql_query(g_SQL, query);
	new result = cache_num_rows();
	if(result) {
		for(new i; i != result; i++) {
			count++;
		}
	}
	cache_delete(check);
	return count;
}

Workshop_ShowEmployee(playerid, id, type = 0)
{
	new query[255], Cache: cache;
	format(query, sizeof(query), "SELECT * FROM `workshop_employee` WHERE `Workshop`='%d'", WorkshopData[id][ID]);
	cache = mysql_query(g_SQL, query);

	if(!cache_num_rows()) return Error(playerid, "There are no one employee for this business.");
	
	format(query, sizeof(query), "#\tName\tDate Added\n");
	for(new i; i < cache_num_rows(); i++) {
		new biz,
            time,
			name[24];

        cache_get_value_int(i, "ID", biz);
		cache_get_value_int(i, "Time", time);
		cache_get_value(i, "Name", name, sizeof(name));
		format(query, sizeof(query), "%s%d\t%s\t%s\n", query, biz, name, experieddate(time,3));
	}
	if (!type)
		Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Business Employee", query, "Close", "");
	else
		Dialog_Show(playerid, Workshop_RemoveEmployee, DIALOG_STYLE_TABLIST_HEADERS, "Remove Employee", query, "Remove", "Close");

	cache_delete(cache);
	return 1;
}
