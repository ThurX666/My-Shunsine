
task Vehicle_Despawned[1000]() {
    foreach(new slot : VehicleData) {
        if(VehicleData[slot][VehicleSpawnTime] > 0 && !IsPlayerConnected(VehicleData[slot][VehicleOwner])) {
            VehicleData[slot][VehicleSpawnTime]--;
            if(VehicleData[slot][VehicleSpawnTime] == 0) {
                DestroyVehicle(VehicleData[slot][Vehicle]);
                VehicleData[slot][Vehicle] = INVALID_VEHICLE_ID;
                format(VehicleData[slot][VehicleOwner], 52, "-");
            }
        }
        if(VehicleData[slot][VehicleSpawnTime] > 0 && IsPlayerConnected(VehicleData[slot][VehicleOwner])) {
            VehicleData[slot][VehicleSpawnTime] = -1;
        }
    }
    return 1;
}