#define MAX_WORKSHOP 5
new PlayerInWorkshop[MAX_PLAYERS] = -1;
enum workshop {
    ID,
    Name[52],
    Owner[MAX_PLAYER_NAME],
    Price,
    Type,
    Dynamic, // 0 = Static (mapped in world), 1 = Dynamic (object created)
    Float:WorkshopPos[6],
    Float:GatePosF[6],
    Float:GatePosR[6],
    Float:BoardPos[6],
    StatusWorkshop,
	StorageWorkshop[2],
    TextWorkshop[128],
    ObjectGate[2],
    ObjectButton,
    ObjectBoard
}
new WorkshopData[MAX_WORKSHOP][workshop],
    WorkshopObj[MAX_WORKSHOP],
    WorkshopPickup[MAX_WORKSHOP] = {-1, ...},
    Iterator:Workshop<MAX_WORKSHOP>;

new Text3D:WorkshopLabel[MAX_WORKSHOP];
