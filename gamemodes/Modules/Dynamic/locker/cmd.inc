//Dynamic Locker System
CMD:createlocker(playerid, params[])
{
	if(pData[playerid][pAdmin] < 4)
		return PermissionError(playerid);
	
	new lid = Iter_Free(Lockers), query[128];
	if(lid == -1) return Error(playerid, "You cant create more locker!");
	new type;
	if(sscanf(params, "d", type)) return Usage(playerid, "/createlocker [type, 1.SAPD 2.SAGS 3.SAMD 4.SANA 5.VIP Locker]");
	
	if(type < 1 || type > 5) return Error(playerid, "Invalid type.");
	
	GetPlayerPos(playerid, lData[lid][lPosX], lData[lid][lPosY], lData[lid][lPosZ]);
	lData[lid][lInt] = GetPlayerInterior(playerid);
	lData[lid][lType] = type;
    Locker_Refresh(lid);
	Iter_Add(Lockers, lid);

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO lockers SET id='%d', type='%d', posx='%f', posy='%f', posz='%f'", lid, lData[lid][lType], lData[lid][lPosX], lData[lid][lPosY], lData[lid][lPosZ]);
	mysql_tquery(g_SQL, query, "OnLockerCreated", "i", lid);
	return 1;
}

CMD:gotolocker(playerid, params[])
{
	new lid;
	if(pData[playerid][pAdmin] < 2)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", lid))
		return Usage(playerid, "/gotolocker [id]");
	if(!Iter_Contains(Lockers, lid)) return Error(playerid, "The locker you specified ID of doesn't exist.");
	SetPlayerPosition(playerid, lData[lid][lPosX], lData[lid][lPosY], lData[lid][lPosZ], 2.0);
    SetPlayerInterior(playerid, lData[lid][lInt]);
    SetPlayerVirtualWorld(playerid, 0);
	Servers(playerid, "You has teleport to locker id %d", lid);
	return 1;
}

CMD:editlocker(playerid, params[])
{
    static
        lid,
        type[24],
        string[128];

    if(pData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", lid, type, string))
    {
        Usage(playerid, "/editlocker [id] [name]");
        SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, type, delete");
        return 1;
    }
    if((lid < 0 || lid >= MAX_LOCKERS))
        return Error(playerid, "You have specified an invalid ID.");
	if(!Iter_Contains(Lockers, lid)) return Error(playerid, "The doors you specified ID of doesn't exist.");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, lData[lid][lPosX], lData[lid][lPosY], lData[lid][lPosZ]);
		lData[lid][lInt] = GetPlayerInterior(playerid);
        Locker_Save(lid);
		Locker_Refresh(lid);

        SendAdminMessage(COLOR_RED, "%s has adjusted the location of locker ID: %d.", pData[playerid][pAdminname], lid);
    }
    else if(!strcmp(type, "type", true))
    {
        new tipe;

        if(sscanf(string, "d", tipe))
            return Usage(playerid, "/editlocker [id] [type] [type, 1.SAPD 2.SAGS 3.SAMD 4.SANA 5.VIP Locker]");

        if(tipe < 1 || tipe > 5)
            return Error(playerid, "You must specify at least 1 - 5.");

        lData[lid][lType] = tipe;
        Locker_Save(lid);
		Locker_Refresh(lid);

        SendAdminMessage(COLOR_RED, "%s has set locker ID: %d to type id faction %d.", pData[playerid][pAdminname], lid, tipe);
    }
    else if(!strcmp(type, "delete", true))
    {
		new query[128];
		DestroyDynamic3DTextLabel(lData[lid][lLabel]);
		DestroyDynamicPickup(lData[lid][lPickup]);
		lData[lid][lPosX] = 0;
		lData[lid][lPosY] = 0;
		lData[lid][lPosZ] = 0;
		lData[lid][lInt] = 0;
		lData[lid][lLabel] = Text3D: INVALID_3DTEXT_ID;
		lData[lid][lPickup] = -1;
		Iter_Remove(Lockers, lid);
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM lockers WHERE id=%d", lid);
		mysql_tquery(g_SQL, query);
        SendAdminMessage(COLOR_RED, "%s has delete locker ID: %d.", pData[playerid][pAdminname], lid);
    }
    return 1;
}