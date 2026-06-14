// Selected vehicle needs to be parked outside this building
CMD:location(playerid, params[])
{
    static
        type[24],
        string[128];
    if(pData[playerid][pAdmin] < 6) return PermissionError(playerid);
    if(sscanf(params, "s[24]S()[128]", type, string)) return Usage(playerid, "/location [add/delete/near/goto]");
    if(!strcmp(type, "add", true))
    {
        Dialog_Show(playerid, LocationAdd, DIALOG_STYLE_LIST, "Add New Location", "\
        Static vehicle spawnpoint\n\
        PD Buy Plate\n\
        PD Buy Plate (outside check)\n\
        PD Buy Ticket / Tirelock Release\n\
        Bank Point\n\
        Insurance Claim Point\n\
        Insurance Claim Spawn (Darat)\n\
        Insurance Claim Spawn (Air)\n\
        Bicycle Dealer\n\
        Bicycle Dealer (Spawn)\n\
        Boat Dealer\n\
        Boat Dealer (spawn)\n\
        Advertisement Point\n\
        SAPD Central Armoury\
        ", "Add", "Cancel");
    }
    else if(!strcmp(type, "near", true))
    {
        foreach(new id : Locations) if(IsPlayerInRangeOfPoint(playerid, 3, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
            if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
                SendCustomMessage(playerid, "LOCATION", ""YELLOW_E"ID:%d nears", id);
            }
        }
    }
    else if(!strcmp(type, "goto", true))
    {
        new slot;

        if(sscanf(string, "d", slot)) {
            Usage(playerid, "/location [goto] [ID]");
            return 1;
        }
        if(!Iter_Contains(Locations, slot)) return Error(playerid, "The you specified ID of doesn't exist.");
        SendCustomMessage(playerid, "TELEPORT", "You successfully teleport to location "AQUA_E"id:%d", slot);
        SetPlayerPos(playerid, Location[slot][locPos][0], Location[slot][locPos][1], Location[slot][locPos][2]);
        SetPlayerFacingAngle(playerid, Location[slot][locPos][3]);
        SetPlayerVirtualWorld(playerid, Location[slot][locWorld]);
        SetPlayerInterior(playerid, Location[slot][locInterior]);
    }
    else if(!strcmp(type, "delete", true))
    {
        new slot;

        if(sscanf(string, "d", slot)) {
            Usage(playerid, "/location [delete] [ID]");
            return 1;
        }
        if(!Iter_Contains(Locations, slot)) return Error(playerid, "The you specified ID of doesn't exist.");
        SendCustomMessage(playerid, "LOCATION", "You successfully removed location "AQUA_E"id:%d", slot);
        if(IsValidDynamic3DTextLabel(Location[slot][locLabel])) DestroyDynamic3DTextLabel(Location[slot][locLabel]);
        if(IsValidDynamicPickup(Location[slot][locPickup])) DestroyDynamicPickup(Location[slot][locPickup]);
        new query[128];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM location WHERE ID=%d", Location[slot][locID]);
        mysql_tquery(g_SQL, query);
        new tmp_VehicleData[locationenum];
        Location[slot] = tmp_VehicleData;
        Iter_Remove(Locations, slot);
    }
    return 1;
}
