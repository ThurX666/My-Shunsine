
IsVehicleTrashmaster(vehicleid)
{
    for (new i = 0; i != 4; i ++) if(VehicleTrashmaster[i] == vehicleid) {
        return 1;
    }
    return 0;
}
