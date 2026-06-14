
Dialog:StartTrashmaster(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        if(pData[playerid][pFaction] > 0) return Error(playerid, "Kamu anggota faction, tidak bekerja jobs/sidejob.");
        new String2[212];
        format(String2,sizeof(String2),"Trash~n~%02d/%d", CoreVehicles[GetPlayerVehicleID(playerid)][vehTrash], MAX_SAMPAH);
        PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);

        TextDrawShowForPlayer(playerid, PlayerCrateTD);
        PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
        PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);

        SendCustomMessage(playerid, "HINT", "Ikuti tanda di radar Map, itu merupakan lokasi untuk menemukan tong sampah.");
        SendCustomMessage(playerid, "HINT", "Perintah '"YELLOW_E"/loadtrash"WHITE_E"' untuk mengambil sampah dan '"YELLOW_E"/unloadtrash"WHITE_E"' untuk ...");
        SendClientMessage(playerid, COLOR_WHITE, ".. mendapatkan upah setelah sampah terkumpul. Kembali ke tempat awal untuk menjual garbage.");
        
        // CoreVehicles[VehicleTrashmaster[GetPlayerVehicleID(playerid)]][vehFuel] = 100.0;
        SwitchVehicleEngine(GetPlayerVehicleID(playerid), true);

        for(new i; i < MAX_GARBAGE_BINS; i++) if(GarbageData[i][garbageExists]) {
            SetPlayerMapIcon(playerid, i, GarbageData[i][garbagePos][0], GarbageData[i][garbagePos][1], GarbageData[i][garbagePos][2], 56, 0, MAPICON_GLOBAL);
        }
        pData[playerid][pTrashmasterJob] = 1;
    }
    else RemovePlayerFromVehicle(playerid);

    return 1;
}
