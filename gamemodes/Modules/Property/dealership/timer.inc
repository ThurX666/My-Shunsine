task VehicleCD_Handbrake[1000]() {
    foreach(new d : Dealership) {
        for (new fv = 0; fv != MAX_DEALERSHIPVEHICLES; fv ++) {
            new Float:distance = GetVehicleDistanceFromPoint(CarDealershipInfo[d][cdVehicleId][fv], CarDealershipInfo[d][cdVehicleSpawnX][fv], CarDealershipInfo[d][cdVehicleSpawnY][fv], CarDealershipInfo[d][cdVehicleSpawnZ][fv]);
            if(distance >= Float:2.0) {
                SetVehicleZAngle(CarDealershipInfo[d][cdVehicleId][fv], CarDealershipInfo[d][cdVehicleSpawnAngle][fv]);
                SetVehiclePos(CarDealershipInfo[d][cdVehicleId][fv], CarDealershipInfo[d][cdVehicleSpawnX][fv], CarDealershipInfo[d][cdVehicleSpawnY][fv], CarDealershipInfo[d][cdVehicleSpawnZ][fv]);
            }
        }
    }
    return 1;
}
