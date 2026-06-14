
CMD:showproduct(playerid, params[])
{
	new vehicleid = VehicleData_GetID(GetPlayerVehicleID(playerid)), otherid, bizid = VehicleData[vehicleid][Bisnis];
	if(sscanf(params, "u", otherid)) return Usage(playerid, "/showproduct [playerid/PartOfName]");

    if(otherid == INVALID_PLAYER_ID || !NearPlayer(playerid, otherid, 5.0))
        return Error(playerid, "The specified player is disconnected or not near you.");
    if(VehicleData[vehicleid][Storage][0] < 1) return Error(playerid, "This vehicle don't have food storage");
    ProductOffer[otherid][0] = playerid;
    ProductOffer[otherid][1] = VehicleData[vehicleid][Bisnis];
    ProductOffer[otherid][2] = vehicleid;
    SendClientMessageEx(playerid, COLOR_ARWIN, "MENU: "WHITE_E"You show the menu to the player "YELLOW_E"%s", ReturnName(otherid));
    SendCustomMessage(otherid, "BUSINESS", "{00FFFF}%s {FFFFFF}has offered you products of {0000FF}%s", ReturnName2(playerid), ReplaceString(bData[bizid][bName]));
    SendCustomMessage(otherid, "HINT", "Use '{FFFF00}/accept menu{FFFFFF}' to open the product offerings");
	return 1;
}

CMD:savevehicle(playerid, params[]) {
    if(pData[playerid][pAdmin] < 6) return PermissionError(playerid);
    foreach(new vehicleid : VehicleData) {
        SaveVehicleData(vehicleid);
    }
    return 1;
}

CMD:spawnveh(playerid, params[]) {
    new string[512], found = false;
    new owner[52], status[64];
    foreach(new loc : Locations) if(IsPlayerInRangeOfPoint(playerid, 5, Location[loc][locPos][0], Location[loc][locPos][1], Location[loc][locPos][2]) && Location[loc][locType] == 0) {
        format(string, sizeof(string), "Vehicle\tStatus\n");
        foreach(new slot : VehicleData) if(IsPlayerInRangeOfPoint(playerid, 100, VehicleData[slot][Pos][0],VehicleData[slot][Pos][1],VehicleData[slot][Pos][2])) {
            if(VehicleData[slot][Faction] == pData[playerid][pFaction]) {
                gListedItems[playerid][found] = slot;
                found++;
                format(owner, sizeof(owner), "%s", VehicleData[slot][VehicleOwner]);
                format(status, sizeof(status), "Spawned by %s", owner);
                format(string, sizeof(string), "%s%s\t%s\n",
                    string,
                    GetVehicleModelName(VehicleData[slot][Model]),
                    status
                );
            }
        }
        if(found) Dialog_Show(playerid, VehicleStaticSpawn, DIALOG_STYLE_TABLIST_HEADERS, "Vehicle Static Spawn", string, "Spawn", "Close");
        else Error(playerid, "There are no static vehicles found near your position");
    }
    return 1;
}

CMD:despawnveh(playerid, params[]) {
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
        foreach(new loc : Locations) if(IsPlayerInRangeOfPoint(playerid, 5, Location[loc][locPos][0], Location[loc][locPos][1], Location[loc][locPos][2]) && Location[loc][locType] == 0) {
            foreach(new vehicleid : VehicleData)  {
                if(VehicleData[vehicleid][Vehicle] == GetPlayerVehicleID(playerid)) {
                    DestroyVehicle(VehicleData[vehicleid][Vehicle]);
                    VehicleData[vehicleid][Vehicle] = INVALID_VEHICLE_ID;
                    format(VehicleData[vehicleid][VehicleOwner], 52, "-");
                }
            }
        }
    }
    else return Error(playerid, "You have to drive a static vehicle");
    return 1;
}

CMD:vehicle(playerid, params[])
{
    static
        type[24],
        string[128];
    new cQuery[1024], Float:x,Float:y,Float:z, Float:a;
    if(pData[playerid][pAdmin] < 6) return PermissionError(playerid);
    GetPlayerPos(playerid,x,y,z);
    GetPlayerFacingAngle(playerid,a);
    if(sscanf(params, "s[24]S()[128]", type, string)) return Usage(playerid, "/vehicle [add/edit/delete/showtext3d/hidetext3d]");
    if(!strcmp(type, "add", true))
    {
        new model, color1, color2;

        if(sscanf(string, "ddd", model, color1, color2)) {
            Usage(playerid, "/vehicle [add] [model] [color1] [color2]");
            return 1;
        }
        new Vehicleid = Iter_Free(VehicleData);
	    if(Vehicleid == -1) return 1;
        if(color1 < 0 || color1 > 255 || color2 < 0 || color2 > 255) { Error(playerid, "Color Number can't be below 0 or above 255 !"); return 1; }
        if(model < 400 || model > 611) { Error(playerid, "Vehicle Number can't be below 400 or above 611 !"); return 1; }
        Iter_Add(VehicleData, Vehicleid);
        mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO vehicledata SET ID='%d', Model='%d', Color='%d|%d', VehiclePos='%.4f|%.4f|%.4f|%.4f'", Vehicleid, model, color1, color2, x, y, z, a);
        mysql_tquery(g_SQL, cQuery, "VehicleStaticCreate", "dddddffff", playerid, Vehicleid, model, color1, color2, x, y, z, a);
    }
    else if(!strcmp(type, "edit", true))
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
            new msg[512], found = false;
            format(msg, sizeof(msg), "Option\tValue\n");
            foreach(new slot : VehicleData) if(VehicleData[slot][Vehicle] == GetPlayerVehicleID(playerid)) {
                found++;
                format(msg, sizeof(msg), "%sSet Owner\t%s\nRespray\t%d %d\nSet plate number\t%s\nSpawn Type\t%s\nPosition", msg, GetVehicleStaticOwner(slot), VehicleData[slot][Color][0], VehicleData[slot][Color][1], VehicleData[slot][Plate], GetVehicleStaticSpawn(slot));
            }
            if(found) Dialog_Show(playerid, VehicleStaticEdit, DIALOG_STYLE_TABLIST_HEADERS, "Edit Static Vehicle", msg, "Select", "Close");
        }
        else return Error(playerid, "You have to drive a static vehicle");
    }
    else if(!strcmp(type, "delete", true))
    {
        new slot, veh;

        if(sscanf(string, "d", slot)) {
            Usage(playerid, "/vehicle [delete] [ID]");
            return 1;
        }
        foreach(new vehicle : VehicleData) if(VehicleData[vehicle][Vehicle] == slot) {
            veh = vehicle;
        }
        SendCustomMessage(playerid, "VEHICLE", ""YELLOW_E"Anda berhasil menghapus kendaraan "AQUA_E"%s [VID: %d]", GetVehicleModelName(VehicleData[veh][Model]), veh);
        new query[128];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM vehicledata WHERE ID=%d", VehicleData[veh][ID]);
        mysql_tquery(g_SQL, query);
        if(IsValidVehicle(VehicleData[veh][Vehicle])) DestroyVehicle(VehicleData[veh][Vehicle]);
        new tmp_VehicleData[vehicledata];
        VehicleData[veh] = tmp_VehicleData;

        VehicleData[veh][Vehicle] = INVALID_VEHICLE_ID;
        Iter_Remove(VehicleData, veh);
    }
    else if(!strcmp(type, "showtext3d", true))
    {
        new tstr[912], Status[52];
        foreach(new vehicle : VehicleData) if(VehicleData[vehicle][Vehicle]) {
            if(IsValidDynamic3DTextLabel(VehicleData[vehicle][VehicleText])) DestroyDynamic3DTextLabel(VehicleData[vehicle][VehicleText]);
            if(VehicleData[vehicle][Faction] == 1) format(Status, 52, "San Andreas Police Department");
            else if(VehicleData[vehicle][Faction] == 3) format(Status, 52, "San Andreas Medical Department");
            else if(VehicleData[vehicle][Faction] == 4) format(Status, 52, "San Andreas Network");
            else if(VehicleData[vehicle][Bisnis] != -1) format(Status, 52, "Bisnis [%s]", ReplaceString(bData[VehicleData[vehicle][Bisnis]][bName]));
            else if(VehicleData[vehicle][Workshop] != -1) format(Status, 52, "Workshop [%s]", ReplaceString(WorkshopData[VehicleData[vehicle][Workshop]][Name]));
            format(tstr, 912, ""AQUA_E"[VDID:%d]\n"WHITE_E"Vehicle Type: "AQUA_E"%s\n"WHITE_E"Vehicle Pos: "AQUA_E"%.4f|%.4f|%.4f|%.4f\n"WHITE_E"Vehicle Fuel: "AQUA_E"%d", vehicle, Status, VehicleData[vehicle][Pos][0], VehicleData[vehicle][Pos][1], VehicleData[vehicle][Pos][2], GetVehicleFuel(VehicleData[vehicle][Vehicle])/10);
            VehicleData[vehicle][VehicleText] = CreateDynamic3DTextLabel(tstr, -1, VehicleData[vehicle][Pos][0], VehicleData[vehicle][Pos][1], VehicleData[vehicle][Pos][2], 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, VehicleData[vehicle][Virtual], VehicleData[vehicle][Interior]);
        }
    }
    else if(!strcmp(type, "hidetext3d", true))
    {
        foreach(new vehicle : VehicleData) if(VehicleData[vehicle][Vehicle]) {
            if(IsValidDynamic3DTextLabel(VehicleData[vehicle][VehicleText])) DestroyDynamic3DTextLabel(VehicleData[vehicle][VehicleText]);
        }
    }
    return 1;
}
