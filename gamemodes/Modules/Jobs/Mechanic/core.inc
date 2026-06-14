new MechanicModification[MAX_PLAYERS][MAX_VEHICLE_COMPONENTS];
new PlayerTowImpound[MAX_PLAYERS] = -1;

Vehicle_ComponentTotal(vehicleid)
{
	new count = 0;
    foreach(new pv : PVehicles)
    {
        if(vehicleid == pvData[pv][cVeh])
        {
            count += pvData[pv][cComponent];
        }
    }        
	return count;
}

VehicleWorkshop_ComponentTotal(vehicleid)
{
	new count = 0;
    foreach(new vehicle : VehicleData)
    {
        if(vehicleid == VehicleData[vehicle][Vehicle])
        {
            count += VehicleData[vehicle][Storage][1];
        }
    }        
	return count;
}

stock RemoveComponent(vehicleid, componentid)
{
    if(!IsValidVehicle(vehicleid) || (componentid < 1000 || componentid > 1193))
        return 0;

    new
        id = Vehicle_GetID(vehicleid);

    if(id != -1)
    {
        pvData[id][cMod][GetVehicleComponentType(componentid)] = 0;
    }
    return RemoveVehicleComponent(vehicleid, componentid);
}

stock RemoveComponentStatic(vehicleid, componentid)
{
    if(!IsValidVehicle(vehicleid) || (componentid < 1000 || componentid > 1193))
        return 0;

    new
        id = VehicleData_GetID(vehicleid);

    if(id != -1)
    {
        VehicleData[id][Mod][GetVehicleComponentType(componentid)] = 0;
    }
    return RemoveVehicleComponent(vehicleid, componentid);
}

// stock InstallComponent(vehicleid, componentid)
// {
//     if(!IsValidVehicle(vehicleid) || (componentid < 1000 || componentid > 1193)) return 0;
//     return AddVehicleComponent(vehicleid, componentid);
// }

stock InstallComponentStatic(vehicleid, componentid)
{
    if(!IsValidVehicle(vehicleid) || (componentid < 1000 || componentid > 1193)) return 0;
    new vehicle = VehicleData_GetID(vehicleid);
    new vid = Vehicle_GetID(vehicleid);
    if(vehicle != -1 && VehicleData[vehicle][Vehicle] == vehicleid) VehicleData[vehicle][Mod][GetVehicleComponentType(componentid)] = componentid;
    else if(vid != -1 && pvData[vid][cVeh] == vehicleid) pvData[vid][cMod][GetVehicleComponentType(componentid)] = componentid;
    return AddVehicleComponent(vehicleid, componentid);
}
