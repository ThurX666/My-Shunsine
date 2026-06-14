#include <YSI\y_hooks>
task Vehicle_Handbrake[1000]() {
    for (new vehicleid = 0; vehicleid != MAX_VEHICLES; vehicleid ++) {
        new Float:distance = GetVehicleDistanceFromPoint(pvData[vehicleid][cVeh], pvData[vehicleid][cPosX], pvData[vehicleid][cPosY], pvData[vehicleid][cPosZ]);
        if(distance >= Float:2.0) 
        {
            if(pvData[vehicleid][cHandbrake] == 1) {
                SetVehicleZAngle(pvData[vehicleid][cVeh], pvData[vehicleid][cPosA]);
                SetVehiclePos(pvData[vehicleid][cVeh], pvData[vehicleid][cPosX], pvData[vehicleid][cPosY], pvData[vehicleid][cPosZ]);
            }
        }
    }
    return 1;
}