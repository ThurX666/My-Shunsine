#define MAX_GYM_OBJECTS 100
enum gymObject {
    objectID,
    objectBiz,
    objectModel,
    objectInt,
    objectVw,
    Float:objectPos[3],
    Float:objectRot[3],
    objectType,
    objectCondition,
    objectStatus,
    objectgym,
    Text3D:objectLabel
};
new GYMObject[MAX_GYM_OBJECTS][gymObject],
    Iterator:GYMObjects<MAX_GYM_OBJECTS>;

new PlayerInGym[MAX_PLAYERS][3];
new PlayerEquipGym[MAX_PLAYERS];
#include <YSI\y_hooks>
hook OnPlayerConnect(playerid)
{
  PlayerInGym[playerid][0] = PlayerInGym[playerid][1] = PlayerInGym[playerid][2] = PlayerEquipGym[playerid] = -1;
  return 1;
}
