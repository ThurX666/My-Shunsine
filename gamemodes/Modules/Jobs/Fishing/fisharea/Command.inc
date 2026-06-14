
CMD:fishing(playerid, params[])
{
    static type[24], string[128];
    if(pData[playerid][pAdmin] < 6) return PermissionError(playerid);
    if(sscanf(params, "s[24]S()[128]", type, string)) return Usage(playerid, "/fishing [create/pos/random/goto/delete]");
    if(!strcmp(type, "create", true))
    {
        new fishing = Iter_Free(FishingArea);
        if(fishing == -1) return Error(playerid, "Anda tidak bisa membuat area mancing lagi!");
        GetPlayerPos(playerid, FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2]);
        FishingData[fishing][Type] = random(3);
        SendCustomMessage(playerid, "FISHINGAREA", "Anda berhasil membuat area mancing ID:%d", fishing);
        Iter_Add(FishingArea, fishing);
        new query[128];
        mysql_format(g_SQL, query, sizeof(query), "INSERT INTO fishingarea SET ID=%d, PosX='%f', PosY='%f', PosZ='%f'", fishing, FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2]);
        mysql_tquery(g_SQL, query);
    }
    else if(!strcmp(type, "pos", true))
    {
        new fishing;
        if(sscanf(string, "d", fishing)) return Usage(playerid, "/fishing [pos] [id]");
		if(!Iter_Contains(FishingArea, fishing)) return Error(playerid, "The you specified ID of doesn't exist.");
        GetPlayerPos(playerid, FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2]);
        SendCustomMessage(playerid, "FISHINGAREA", "Anda telah mengganti posisi area mancing ID:%d", fishing);
        FishingAreaSave(fishing);
    }
    else if(!strcmp(type, "random", true))
    {
        foreach(new fishing : FishingArea) {
            FishingData[fishing][Type] = random(3);
            if(IsValidDynamicMapIcon(mapiconfishing[playerid][fishing])) DestroyDynamicMapIcon(mapiconfishing[playerid][fishing]);
            if(IsABoat(GetPlayerVehicleID(playerid)))
            {
                switch(FishingData[fishing][Type]) {
                    case 0: mapiconfishing[playerid][fishing] = CreateDynamicMapIcon(FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2], 0, COLOR_RED, 0, 0, playerid, 1000, MAPICON_LOCAL);
                    case 1: mapiconfishing[playerid][fishing] = CreateDynamicMapIcon(FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2], 0, 0xFFFF0000, 0, 0, playerid, 1000, MAPICON_LOCAL);
                    case 2: mapiconfishing[playerid][fishing] = CreateDynamicMapIcon(FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2], 0, 0x00FF0000, 0, 0, playerid, 1000, MAPICON_LOCAL);
                }
            }
        }
    }
    else if(!strcmp(type, "goto", true))
    {
        new fishing;
        if(sscanf(string, "d", fishing)) return Usage(playerid, "/fishing [goto] [id]");
		if(!Iter_Contains(FishingArea, fishing)) return Error(playerid, "The you specified ID of doesn't exist.");
        SetPlayerPos(playerid, FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2]);
    }
    else if(!strcmp(type, "delete", true))
    {
        new fishing;
        if(sscanf(string, "d", fishing)) return Usage(playerid, "/fishing [pos] [id]");
		if(!Iter_Contains(FishingArea, fishing)) return Error(playerid, "The you specified ID of doesn't exist.");
        SendCustomMessage(playerid, "FISHINGAREA", "Anda telah menghapus area mancing ID:%d", fishing);
        Iter_Remove(FishingArea, fishing);
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM fishingarea WHERE ID=%d", fishing);
		mysql_tquery(g_SQL, query);
    }
    return 1;
}
