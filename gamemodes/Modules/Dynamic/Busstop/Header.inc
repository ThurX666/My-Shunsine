#define MAX_DOOR_FACTION 200

enum doorfaction {
	dfID,
	dfObj,
    dfObjDInt,
    dfObjDExt,
	dfStatus,
	dfModel,
	dfFaction,
	Float:dfPos[6],
	Float:dfMove[6],
    Float:dfPosInt[6],
	Float:dfPosExt[6]
};
new DoorFaction[MAX_DOOR_FACTION][doorfaction], Iterator:DoorsFaction<MAX_DOOR_FACTION>;
new DoorFaction_Timer[MAX_DOOR_FACTION];
new editDoorFactionID[MAX_PLAYERS] = -1;
new editDoorFactioMode[MAX_PLAYERS] = -1;
