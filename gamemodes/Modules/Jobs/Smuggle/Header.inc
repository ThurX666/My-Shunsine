#define SMUGGLER_SALARY 35000
#define MAX_PACKET 5

new selectedLocation;
new packetStatus[MAX_PACKET];
new packetPlayerid[MAX_PACKET] = {INVALID_PLAYER_ID, ...};
new packetObject[MAX_PACKET], Text3D:packetLabel[MAX_PACKET];
new packetActive = 0;

new Float:pickPacket[][3] = {
  {-1293.7229,2524.0850,87.4563},
  {-772.7677,2423.5154,157.0893}
};

new Float:storePacket[][3] = {
  {1568.2803,30.8219,24.1641},
  {859.2977,-18.9858,63.3022}
};
