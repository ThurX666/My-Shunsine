
#define MAX_SPEED_CAMERAS           50

enum speedData {
    speedID,
    speedExists,
    Float:speedPos[4],
    Float:speedRange,
    Float:speedLimit,
    speedObject,
    Text3D:speedText3D,
    speedVehicle,
    speedVehPlate[24],
    speedVehSpeed
};

new SpeedData[MAX_SPEED_CAMERAS][speedData];
