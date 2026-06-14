#include <YSI\y_hooks>
hook OnGameModeInit()
{
    new objectcourier;
    CourierVehicle[0] = AddStaticVehicle(498,1772.3386,-1702.9760,13.5782,11.1372,2,1);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "AMAZING", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[0], -1.210, -0.670, 0.900, 0.000, 0.000, 0.000);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "AMAZING", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[0], 1.216, -0.709, 0.870, 0.000, 0.000, 179.700);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "PRIME", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[0], -1.221, -1.271, 0.400, 0.000, 0.000, 0.000);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "PRIME", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[0], 1.230, -0.229, 0.320, 0.000, 0.000, 179.800);

    CourierVehicle[1] = AddStaticVehicle(498,1776.0262,-1702.9165,13.5767,9.1052,2,1);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "AMAZING", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[1], -1.210, -0.670, 0.900, 0.000, 0.000, 0.000);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "AMAZING", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[1], 1.216, -0.709, 0.870, 0.000, 0.000, 179.700);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "PRIME", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[1], -1.221, -1.271, 0.400, 0.000, 0.000, 0.000);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "PRIME", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[1], 1.230, -0.229, 0.320, 0.000, 0.000, 179.800);


    CourierVehicle[2] = AddStaticVehicle(498,1780.6472,-1702.3958,13.5761,10.6289,2,1);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "AMAZING", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[2], -1.210, -0.670, 0.900, 0.000, 0.000, 0.000);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "AMAZING", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[2], 1.216, -0.709, 0.870, 0.000, 0.000, 179.700);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "PRIME", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[2], -1.221, -1.271, 0.400, 0.000, 0.000, 0.000);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "PRIME", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[2], 1.230, -0.229, 0.320, 0.000, 0.000, 179.800);

    CourierVehicle[3] = AddStaticVehicle(498,1784.5532,-1702.2916,13.5749,10.9174,2,1);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "AMAZING", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[3], -1.210, -0.670, 0.900, 0.000, 0.000, 0.000);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "AMAZING", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[3], 1.216, -0.709, 0.870, 0.000, 0.000, 179.700);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "PRIME", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[3], -1.221, -1.271, 0.400, 0.000, 0.000, 0.000);
    objectcourier = CreateDynamicObject(18667,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
    SetDynamicObjectMaterialText(objectcourier, 0, "PRIME", 130, "Courier New", 110, 1, -1, 0, 0);
    AttachDynamicObjectToVehicle(objectcourier, CourierVehicle[3], 1.230, -0.229, 0.320, 0.000, 0.000, 179.800);

}

IsACourierVeh(carid)
{
    for(new v = 0; v < sizeof(CourierVehicle); v++) {
        if(carid == CourierVehicle[v]) return 1;
    }
    return 0;
}
