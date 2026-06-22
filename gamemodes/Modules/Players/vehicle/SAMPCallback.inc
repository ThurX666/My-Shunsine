#include <YSI\y_hooks>

// Timer: setiap 3 detik cek player yang berada dalam radius kendaraan dengan radio aktif
task ProcessVehicleRadio[3000]()
{
    foreach (new vehicleid : Vehicle)
    {
        if(!IsValidVehicle(vehicleid)) continue;
        if(!CoreVehicles[vehicleid][vehRadio]) continue;

        new
            Float:fVehX,
            Float:fVehY,
            Float:fVehZ,
            szURL[128];

        GetVehiclePos(vehicleid, fVehX, fVehY, fVehZ);
        strunpack(szURL, CoreVehicles[vehicleid][vehURL], 128);

        foreach (new i : Player)
        {
            if(!IsPlayerConnected(i)) continue;

            // Player di dalam kendaraan
            if(IsPlayerInVehicle(i, vehicleid))
            {
                if(!pData[i][pRadioVehicleOn] || pData[i][pRadioVehicleVeh] != vehicleid)
                {
                    pData[i][pRadioVehicleOn] = 1;
                    pData[i][pRadioVehicleVeh] = vehicleid;
                    if(pData[i][pRadioVehicleListening])
                    {
                        pData[i][pRadioVehicleListening] = 0;
                        pData[i][pRadioVehicleVeh] = 0;
                    }
                    StopAudioStreamForPlayer(i);
                    PlayAudioStreamForPlayer(i, szURL);
                }
                continue;
            }

            // Player di luar kendaraan — cek jarak
            new Float:fDist = GetPlayerDistanceFromPoint(i, fVehX, fVehY, fVehZ);
            if(fDist <= 30.0 && GetPlayerInterior(i) == 0 && GetPlayerVirtualWorld(i) == 0)
            {
                if(!pData[i][pRadioVehicleListening] || pData[i][pRadioVehicleVeh] != vehicleid)
                {
                    // Player baru masuk radius
                    if(pData[i][pRadioVehicleOn])
                    {
                        pData[i][pRadioVehicleOn] = 0;
                    }
                    pData[i][pRadioVehicleListening] = 1;
                    pData[i][pRadioVehicleVeh] = vehicleid;
                    StopAudioStreamForPlayer(i);
                    PlayAudioStreamForPlayer(i, szURL);
                }
            }
            else
            {
                // Player keluar radius — stop jika sedang mendengarkan radio vehicle ini
                if(pData[i][pRadioVehicleListening] && pData[i][pRadioVehicleVeh] == vehicleid)
                {
                    StopAudioStreamForPlayer(i);
                    pData[i][pRadioVehicleListening] = 0;
                    pData[i][pRadioVehicleVeh] = 0;
                }
            }
        }
    }
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    // Player keluar dari kendaraan
    if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
    {
        if(pData[playerid][pRadioVehicleOn])
        {
            pData[playerid][pRadioVehicleOn] = 0;
            pData[playerid][pRadioVehicleVeh] = 0;
            // Jangan stop audio — biarkan ProcessVehicleRadio yang handle
            // karena player mungkin masih dalam radius
        }
    }

    // Player masuk ke kendaraan sebagai driver/passenger
    if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(CoreVehicles[vehicleid][vehRadio])
        {
            new szURL[128];
            strunpack(szURL, CoreVehicles[vehicleid][vehURL], 128);

            pData[playerid][pRadioVehicleOn] = 1;
            pData[playerid][pRadioVehicleVeh] = vehicleid;
            if(pData[playerid][pRadioVehicleListening])
            {
                pData[playerid][pRadioVehicleListening] = 0;
                pData[playerid][pRadioVehicleVeh] = 0;
            }
            StopAudioStreamForPlayer(playerid);
            PlayAudioStreamForPlayer(playerid, szURL);
        }
    }

    return 1;
}
