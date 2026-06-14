#include <YSI\y_hooks>
hook OnPlayerConnect(playerid) {
    for(new i; i < MAX_VEHICLE_COMPONENTS; i++) MechanicModification[playerid][i] = -1;
    PlayerTowImpound[playerid] = -1;
    Mechanic[playerid] = -1;
    return 1;
}