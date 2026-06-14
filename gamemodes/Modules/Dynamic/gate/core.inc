
enum E_GATE
{
	gModel,
	gPass[36],
	gAdmin,
	gVip,
	gFaction,
	gFamily,
	Float:gSpeed,
	Float:gCX,
	Float:gCY,
	Float:gCZ,
	Float:gCRX,
	Float:gCRY,
	Float:gCRZ,
	Float:gOX,
	Float:gOY,
	Float:gOZ,
	Float:gORX,
	Float:gORY,
	Float:gORZ,
	gStatus,
	gObjID,
	Text3D:gText
}
new gData[MAX_GATES][E_GATE],
	Iterator: Gates<MAX_GATES>;
	
new Float:gPosX[MAX_PLAYERS],
	Float:gPosY[MAX_PLAYERS],
	Float:gPosZ[MAX_PLAYERS],
	Float:gRotX[MAX_PLAYERS],
	Float:gRotY[MAX_PLAYERS],
	Float:gRotZ[MAX_PLAYERS];
