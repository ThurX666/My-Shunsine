#include <YSI\y_hooks>

//Faction Vehicle
#define MAX_FORKLIFT_VEHICLES 3
#define MAX_SWEEPER_VEHICLES 3
#define MAX_BUSAB_VEHICLES 4
#define MAX_BUSCD_VEHICLES 4

new BusABVeh[MAX_BUSAB_VEHICLES];
new BusCDVeh[MAX_BUSCD_VEHICLES];
new ForkliftVeh[MAX_FORKLIFT_VEHICLES];
// new VehicleTrashmaster[4];
new SweepVeh[MAX_SWEEPER_VEHICLES];
new DmvVeh; 

IsAForkliftVeh(carid)
{
	for(new v = 0; v < MAX_FORKLIFT_VEHICLES; v++) 
	{
	    if(carid == ForkliftVeh[v]) return 1;
	}
	return 0;
}

IsABusABVeh(carid)
{
	for(new v = 0; v < MAX_BUSAB_VEHICLES; v++) {
	    if(carid == BusABVeh[v]) return 1;
	}
	return 0;
}

IsABusCDVeh(carid)
{
	for(new v = 0; v < MAX_BUSCD_VEHICLES; v++) {
	    if(carid == BusCDVeh[v]) return 1;
	}
	return 0;
}

CreateVehicleFaction()
{
	new strings[212];
	//SIDE JOB BUS VEHICLE
    BusABVeh[0] = AddStaticVehicle(437,1706.685,-1507.622,13.389,358.372,1,1);
    BusABVeh[1] = AddStaticVehicle(437,1706.712,-1525.643,13.382,0.065,1,1);
    BusABVeh[2] = AddStaticVehicle(437,1695.269,-1532.492,13.546,359.192,1,1);
	BusABVeh[3] = AddStaticVehicle(437,1694.885,-1499.217,13.546,359.815,1,1);

	for(new x;x<MAX_BUSAB_VEHICLES;x++)
	{
	    format(strings, sizeof(strings), ""GREEN_E"COACH-%d", BusABVeh[x]);
	    SetVehicleNumberPlate(BusABVeh[x], strings);
	    SetVehicleToRespawn(BusABVeh[x]);
	}
	//SIDE JOB BUS VEHICLE
	BusCDVeh[0] = AddStaticVehicle(431, 1802.932, -1930.035, 13.386, 30.789, 1, 1);
    BusCDVeh[1] = AddStaticVehicle(431, 1801.388, -1918.678, 13.392, 38.142, 1, 1);
    BusCDVeh[2] = AddStaticVehicle(431, 1801.523, -1909.784, 13.396, 28.951, 1, 1);
    BusCDVeh[3] = AddStaticVehicle(431, 1803.232, -1903.325, 13.399, 28.721, 1, 1);

	for(new x;x<MAX_BUSCD_VEHICLES;x++)
	{
	    format(strings, sizeof(strings), ""GREEN_E"BUS-%d", BusCDVeh[x]);
	    SetVehicleNumberPlate(BusCDVeh[x], strings);
	    SetVehicleToRespawn(BusCDVeh[x]);
	}
	
	//SIDE JOB FORKLIFT VEHICLE
	ForkliftVeh[0] = AddStaticVehicle(530, 2739.3379,-2385.8154,13.3960,176.5227, 1, 1);
	ForkliftVeh[1] = AddStaticVehicle(530, 2743.3752,-2385.7520,13.3853,179.6861, 1, 1);
	ForkliftVeh[2] = AddStaticVehicle(530, 2741.3396,-2385.8645,13.3962,180.0499, 1, 1);

	for(new x;x<MAX_FORKLIFT_VEHICLES; x++)
	{
	    format(strings, sizeof(strings), ""GREEN_E"FORKLIFT-%d", ForkliftVeh[x]);
	    SetVehicleNumberPlate(ForkliftVeh[x], strings);
	    SetVehicleToRespawn(ForkliftVeh[x]);
		if(IsValidDynamicObject(CoreVehicles[x][vehObject]))
			DestroyDynamicObject(CoreVehicles[x][vehObject]);
	}	
}


task VehicleS_Handbrake[1000]() {
	new Float:x, Float:y, Float:z;
    for (new vehicleid = 0; vehicleid != MAX_VEHICLES; vehicleid ++) {
		for(new v = 0; v < MAX_BUSAB_VEHICLES; v++) if(vehicleid == BusABVeh[v]) {
			if(IsVehicleEmpty(vehicleid) && !GetEngineStatus(vehicleid)) {
				GetVehiclePos(vehicleid, x, y, z);
				new Float:distance = GetVehicleDistanceFromPoint(vehicleid, x, y, z);
				if(distance >= Float:2.0) SetVehicleToRespawn(vehicleid);
			}
		}
		for(new v = 0; v < MAX_BUSCD_VEHICLES; v++) if(vehicleid == BusCDVeh[v]) {
			if(IsVehicleEmpty(vehicleid) && !GetEngineStatus(vehicleid)) {
				GetVehiclePos(vehicleid, x, y, z);
				new Float:distance = GetVehicleDistanceFromPoint(vehicleid, x, y, z);
				if(distance >= Float:2.0) SetVehicleToRespawn(vehicleid);
			}
		}
		for(new v = 0; v < MAX_FORKLIFT_VEHICLES; v++) if(vehicleid == ForkliftVeh[v]) {
			if(IsVehicleEmpty(vehicleid) && !GetEngineStatus(vehicleid)) {
				GetVehiclePos(vehicleid, x, y, z);
				new Float:distance = GetVehicleDistanceFromPoint(vehicleid, x, y, z);
				if(distance >= Float:2.0) SetVehicleToRespawn(vehicleid);
			}
		}
		for(new v = 0; v < MAX_SWEEPER_VEHICLES; v++) if(vehicleid == SweepVeh[v]) {
			if(IsVehicleEmpty(vehicleid) && !GetEngineStatus(vehicleid)) {
				GetVehiclePos(vehicleid, x, y, z);
				new Float:distance = GetVehicleDistanceFromPoint(vehicleid, x, y, z);
				if(distance >= Float:2.0) SetVehicleToRespawn(vehicleid);
			}
		}
		if(vehicleid == DmvVeh) {
			if(IsVehicleEmpty(vehicleid) && !GetEngineStatus(vehicleid)) {
				GetVehiclePos(vehicleid, x, y, z);
				new Float:distance = GetVehicleDistanceFromPoint(vehicleid, x, y, z);
				if(distance >= Float:2.0) SetVehicleToRespawn(vehicleid);
			}
		}
    }
    return 1;
}