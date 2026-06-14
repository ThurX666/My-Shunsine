
Dialog:StartTrashmaster(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        if(pData[playerid][pFaction] > 0) return Error(playerid, "Kamu anggota faction, tidak bekerja jobs/sidejob.");
        new String2[212];
        format(String2,sizeof(String2),"Trash~n~%d/10", CoreVehicles[GetPlayerVehicleID(playerid)][vehTrash]);
        PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);

        TextDrawShowForPlayer(playerid, PlayerCrateTD);
        PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
        PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);

        SendCustomMessage(playerid, "SIDEJOB", ""RED_E"Icon merah "WHITE_E"di map adalah lokasi tong sampah");
        SendCustomMessage(playerid, "SIDEJOB", "Pergi ke icon merah dan gunakan command "YELLOW_E"'/loadtrash' "WHITE_E"untuk mengangkut sampah ke mobil");
        SendCustomMessage(playerid, "SIDEJOB", "Jika truk sampah sudah penuh, maka kamu akan di arahkan ke pembuangan sampah");
        SendCustomMessage(playerid, "SIDEJOB", "Meninggalkan truk sampah lebih dari 60 detik artinya berhenti bekerja");
        TogglePlayerControllable(playerid, 1);
        new rand[10], rada = 50;
        for(new id = 0; id < 10; id++){
            rand[id] = RandomEx(0,25);
            if(rand[id] == rand[id]) rand[id] = RandomEx(0,25);
            TrashmasterPlayerX[playerid][id] = TrashmasterCP[id][0];
            TrashmasterPlayerY[playerid][id] = TrashmasterCP[id][1];
            TrashmasterPlayerZ[playerid][id] = TrashmasterCP[id][2];
            TrashmasterDynCP[playerid][id] = CreateDynamicSphere(TrashmasterPlayerX[playerid][id], TrashmasterPlayerY[playerid][id], TrashmasterPlayerZ[playerid][id], 6, 0, 0, playerid);
            SetPlayerMapIcon(playerid, rada+id, TrashmasterPlayerX[playerid][id], TrashmasterPlayerY[playerid][id], TrashmasterPlayerZ[playerid][id], 0, COLOR_RED, 1);
        }
        pData[playerid][pTrashmasterJob] = 1;
    }
    else RemovePlayerFromVehicle(playerid);

    return 1;
}
