#define MAX_PRIVATE_GARAGE 10000
enum privategarage {
    ID,
    Price,
    Owner[52],
    Float:GaragePos[6],
    Float:TextPos[6],
    Float:GatePos[6],
    Vehicle[6],
    VehModel[6],
    DoorsStatus,
    ObjectGarage,
    ObjectText,
    ObjectButton,
    ObjectDoors
}
new PrivateGarage[MAX_PRIVATE_GARAGE][privategarage],
    Iterator: PrivateGarage<MAX_PRIVATE_GARAGE>;