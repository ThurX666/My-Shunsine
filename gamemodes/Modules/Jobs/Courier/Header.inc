//#define BOX_INDEX 0
new CourierVehicle[4];
new TimerCourier[MAX_PLAYERS], CourierCrate[MAX_PLAYERS], bool:CourierJob[MAX_PLAYERS], CourierCount[MAX_PLAYERS], CourierID[MAX_PLAYERS][11];
new STREAMER_TAG_MAP_ICON:MapIconCourier[MAX_PLAYERS][11];
new Float: CourierPlayerX[MAX_PLAYERS][11];
new Float: CourierPlayerY[MAX_PLAYERS][11];
new Float: CourierPlayerZ[MAX_PLAYERS][11];
new bool:CourierStatus[MAX_PLAYERS][11];