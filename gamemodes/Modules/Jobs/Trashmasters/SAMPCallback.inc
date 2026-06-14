#include <YSI\y_hooks>

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    new vehicleid = GetPlayerVehicleID(playerid);

    if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER)
    {
        if(pData[playerid][pTrashmasterJob])
        {
            if(IsVehicleTrashmaster(GetPlayerLastVehicle(playerid)))
            {
                vehicleid = GetPlayerLastVehicle(playerid);

                CoreVehicles[vehicleid][vehTrash] = 0;
                // CoreVehicles[vehicleid][cFuel] = 0.0;
                SetVehicleToRespawn(vehicleid);

                DisablePlayerCheckpoint(playerid);

                for(new i; i < MAX_GARBAGE_BINS; i++) if(GarbageData[i][garbageExists]) {
                    RemovePlayerMapIcon(playerid, i);
                }
                DelayPlayer[playerid][DelayTrashmaster] = 1800;
                pData[playerid][pTrashmasterJob] = 0;
                SendClientMessage(playerid, COLOR_ARWIN, "TRASHMASTER: "WHITE_E"Anda gagal dalam melakukan pekerjaan ini dikarenakan turun dari kendaraan.");
            }
        }    
    }
    if(newstate == PLAYER_STATE_DRIVER)
    {  
        if(IsVehicleTrashmaster(GetPlayerVehicleID(playerid)))
        {
            if(!DelayPlayer[playerid][DelayTrashmaster])
            {
                SetCameraBehindPlayer(playerid);
                Dialog_Show(playerid, StartTrashmaster, DIALOG_STYLE_MSGBOX, "Trashman", ""WHITE_E"Pekerjaan ini bertujuan untuk membersihkan seluruh kota Los Santos.\nAnda bisa temukan \n\
                    tong sampah yang tersebar di kota Los Santos ini. Ikuti petunjuk radar yang di sediakan.\n Itu merupahan lokasi yang harus anda tuju.\n\
                    \n\n"RED_E"WARNING: "WHITE_E"Jangan turun dari kendaraan saat bekerja, atau anda akan gagal dalam pekerjaan ini.", "Mulai", "Turun"
                );
            }
            else
            {
                RemovePlayerFromVehicle(playerid);
                Servers(playerid, "Anda masih menunggu waktu %d menit untuk melakukan pekerjaan ini lagi.", DelayPlayer[playerid][DelayTrashmaster]/60);
            }
        }
    }
    return 1;
}