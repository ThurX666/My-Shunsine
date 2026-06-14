
Dialog:CourierSidejob(playerid, response, listitem, inputtext[]) {
    if(response)
    {
        if(pData[playerid][pFaction] > 0) return Error(playerid, "Kamu anggota faction, tidak bekerja jobs/sidejob.");
        if(DelayPlayer[playerid][DelayCourier] > 0) return Error(playerid, "Kamu harus menunggu %d Menit untuk menjadi pengantar paket", DelayPlayer[playerid][DelayCourier]/60);
        SendCustomMessage(playerid, "SIDEJOB", "Icon merah {FFFFFF}di radar map adalah lokasi pengiriman paket ke rumah");
        SendCustomMessage(playerid, "SIDEJOB", "Setelah sampai rumah, keluar dari kendaraan lalu antar paket ke pintu rumah");
        SendCustomMessage(playerid, "SIDEJOB", "Jika sudah mengantar 10 paket, mohon kembalikan kendaraan ke tempat awal");
        SendCustomMessage(playerid, "SIDEJOB", "Meninggalkan mobil Boxville selama 60 detik artinya berhenti bekerja");
        new String2[212];
        format(String2,sizeof(String2),"Deliveries~n~%d/10", CourierCount[playerid]);
        PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);

        TextDrawShowForPlayer(playerid, PlayerCrateTD);
        PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
        PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
        TogglePlayerControllable(playerid, 1);
        
        CourierJob[playerid] = true;
        CourierCount[playerid] = 0;
        new rand[10], rada = 50, count = 0;

        new validHouseIDs[101];
        foreach(new hid : Houses) 
        {
            if(hid <= 100 && !hData[hid][housePacket]) 
            {
                validHouseIDs[count] = hid;
                count++;
            }
        }

        for(new id = 0; id < 10; id++)
        {
            if(count > 0) 
            {
                rand[id] = random(count);
                CourierStatus[playerid][id] = false;
                CourierID[playerid][id] = validHouseIDs[rand[id]];

                CourierPlayerX[playerid][id] = hData[CourierID[playerid][id]][hExtposX];
                CourierPlayerY[playerid][id] = hData[CourierID[playerid][id]][hExtposY];
                CourierPlayerZ[playerid][id] = hData[CourierID[playerid][id]][hExtposZ];
                SetPlayerMapIcon(playerid, rada+id, CourierPlayerX[playerid][id], CourierPlayerY[playerid][id], CourierPlayerZ[playerid][id], 0, COLOR_RED, MAPICON_GLOBAL);

                for(new j = rand[id]; j < count - 1; j++)
                {
                    validHouseIDs[j] = validHouseIDs[j + 1];
                }
                count--;
            }
        }
    }
    else
    {
        RemovePlayerFromVehicle(playerid);
        SetVehicleToRespawn(GetPlayerVehicleID(playerid));
    }
    return 1;
}
