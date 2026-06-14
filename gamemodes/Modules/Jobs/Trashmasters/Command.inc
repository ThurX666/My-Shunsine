
CMD:creategarbage(playerid, params[])
{
    static
        id = -1,
        type;

    if (pData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if(sscanf(params, "d", type))
    {
        Usage(playerid, "/creategarbage [type]");
        SendClientMessage(playerid, COLOR_ARWIN, "[TYPES]:"WHITE_E" 1: Dumpster | 2: Trash Can");
        return 1;
    }
    if(type < 1 || type > 2)
        return Error(playerid, "The specified type can't be below 1 or above 2.");

    id = Garbage_Create(playerid, type);

    if(id == -1)
        return Error(playerid, "The server has reached the limit for garbage bins.");

    Servers(playerid, "You have successfully created garbage bin ID: %d.", id);
    return 1;
}

CMD:destroygarbage(playerid, params[])
{
    static
        id = 0;

    if (pData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if(sscanf(params, "d", id))
        return Usage(playerid, "/destroygarbage [garbage id]");

    if((id < 0 || id >= MAX_GARBAGE_BINS) || !GarbageData[id][garbageExists])
        return Error(playerid, "You have specified an invalid garbage ID.");

    Garbage_Delete(id);
    Servers(playerid, "You have successfully destroyed garbage bin ID: %d.", id);
    return 1;
}

CMD:loadtrash(playerid, params[])
{
    new
        id,
        vehicleid = GetPlayerVehicleID(playerid);

    if((id = Garbage_Nearest(playerid)) == -1)
        return Error(playerid, "Anda tidak berada di dekat tong sampah.");

    if(!IsPlayerInAnyVehicle(playerid))
        return Error(playerid, "Anda tidak berada di dalam kendaraan.");
    
    if(!IsVehicleTrashmaster(vehicleid))
        return Error(playerid, "Ini bukan mobil khusus untuk pekerjaan trashman.");

    if(GarbageData[id][garbageCapacity] < 1)
        return Error(playerid, "Tong sampah ini tidak ada isinya.");

    if(CoreVehicles[vehicleid][vehTrash] > MAX_SAMPAH)
    {
        SetPlayerRaceCheckpoint(playerid, 1, 2101.2063,-2032.8599,14.0905, 0.0, 0.0, 0.0, 5.0);
        return SendClientMessage(playerid, COLOR_ARWIN, "TRASH: "WHITE_E"Kapasitas kendaraan sudah penuh, silahkan di antar ke tempat pengumpulan sampah.");
    }
     
    if((GarbageData[id][garbageCapacity] + CoreVehicles[vehicleid][vehTrash]) < 50) 
    {
        CoreVehicles[vehicleid][vehTrash] += GarbageData[id][garbageCapacity];
        new string[128];
        format(string, sizeof(string), "TRASG: "WHITE_E"Anda mendapat %d kantong sampah, cari ke lokasi lainnya untuk mendapatkan lebih banyak", GarbageData[id][garbageCapacity], CoreVehicles[vehicleid][vehTrash]);
        SendClientMessage(playerid, COLOR_ARWIN, string);
        // ShowPlayerFooter(playerid, sprintf("~g~Trashmaster: ~w~Anda mendapat %d kantong sampah, cari ke lokasi lainnya untuk -~n~mendapatkan lebih banyak lagi.", GarbageData[id][garbageCapacity], CoreVehicles[vehicleid][vehTrash]), 3000, 1);

        GarbageData[id][garbageCapacity] = 0;
    }
    else
    {
        SendClientMessage(playerid, COLOR_ARWIN, "TRASH: "WHITE_E"Kapasitas mobil telah penuh terisi kantong sampah, ikuti checkpoint untuk mendapatkan upah.");
        SetPlayerRaceCheckpoint(playerid, 1, 2101.2063,-2032.8599,14.0905, 0.0, 0.0, 0.0, 5.0);

        GarbageData[id][garbageCapacity] -= (MAX_SAMPAH-CoreVehicles[vehicleid][vehTrash]);
        CoreVehicles[vehicleid][vehTrash] = MAX_SAMPAH;
    }
    new String2[212];
    format(String2,sizeof(String2),"Trash~n~%d/%d", CoreVehicles[vehicleid][vehTrash], MAX_SAMPAH); 
    PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);

    Garbage_Save(id);
    return 1;
}

CMD:unloadtrash(playerid, params[])
{
    new
        vehicleid = GetPlayerVehicleID(playerid);

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) 
        return Error(playerid, "Selain pengemudi tidak dapat menggunakan perintah ini!.");
    
    if(!IsVehicleTrashmaster(vehicleid)) 
        return Error(playerid, "Anda harus mengendarai mobil Trashmaster.");
    
    if(!IsPlayerInRangeOfPoint(playerid, 4, 2101.2063,-2032.8599,14.0905)) 
        return Error(playerid, "Anda tidak berada di lokasi pemungutan sampah.");

    if(CoreVehicles[vehicleid][vehTrash] < 1) 
        return Error(playerid, "Sampah di mobil ini tidak ada.");
    
    for(new i; i < MAX_GARBAGE_BINS; i++) if(GarbageData[i][garbageExists]) {
        RemovePlayerMapIcon(playerid, i);
    }

    TextDrawHideForPlayer(playerid, PlayerCrateTD);
    PlayerTextDrawHide(playerid, PlayerCrate[playerid][0]);
    PlayerTextDrawHide(playerid, PlayerCrate[playerid][1]);
    new cash = CoreVehicles[vehicleid][vehTrash]*900;
    new list[128];
    format(list, sizeof(list), "Cleared %d trash dumps", CoreVehicles[vehicleid][vehTrash]);
    SetVehicleToRespawn(vehicleid);
    AddPlayerSalary(playerid, "Public Service (Trashmaster)", list, cash); 
    DisablePlayerCheckpoint(playerid);
    DisablePlayerRaceCheckpoint(playerid);
    SendClientMessageEx(playerid, COLOR_ARWIN, "SIDEJOB: {ffffff}Trashmaster sidejob succes, {3BBD44}$%s {ffffff}has been issued for your next paycheck", FormatMoney(cash));
    SendClientMessageEx(playerid, COLOR_ARWIN, "SALARY: {ffffff}Your salary statement has been updated, please check command {ffff00}'/mysalary'");

    CoreVehicles[vehicleid][vehTrash] = 0;
    DelayPlayer[playerid][DelayTrashmaster] = 1800;
    pData[playerid][pTrashmasterJob] = 0;

    SetVehicleToRespawn(vehicleid);
    RemovePlayerFromVehicle(playerid);
    return 1;
}