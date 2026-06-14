#define MAX_LOCATION 100

enum locationenum {
    locID,
    locType,
    Float:locPos[4],
    locInterior,
    locWorld,
    locPickup,
	Text3D:locLabel
}
new Location[MAX_LOCATION][locationenum],
    Iterator:Locations<MAX_LOCATION>;