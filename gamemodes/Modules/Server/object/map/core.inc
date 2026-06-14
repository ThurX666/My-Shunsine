#define MAX_REMOVE_BUILDING         10000
#define MAX_BUILDING                10000

#define MATERIAL_TYPE_NONE			0
#define MATERIAL_TYPE_TEXTURE		1
#define MATERIAL_TYPE_MESSAGE		2

#define OBJECT_SELECT_EDITOR		1
#define OBJECT_SELECT_DELETE		2
#define OBJECT_SELECT_PAINT			3
#define OBJECT_SELECT_CLEAN			4

#define MAX_EDITING_OBJECT			500
#define MAX_OBJECT_MATERIAL_SLOT	10
#define SEARCH_DATA_SIZE (44763)

#define Looping(%0,%1) for(new %0 = 0; %0 < %1; %0++) 
#define IsNull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))    // IsNull macro 			by 	Y_Less

new const WinFonts[15][20] = {
  {"Arial"},
  {"Calibri"},
  {"Comic Sans MS"},
  {"Georgia"},
  {"Times New Roman"},
  {"Consolas"},
  {"Constantia"},
  {"Corbel"},
  {"Courier New"},
  {"Impact"},
  {"Lucida Console"},
  {"Palatino Linotype"},
  {"Tahoma"},
  {"Trebuchet MS"},
  {"Verdana"}
};

// Removebuilding information enum
enum REMOVEINFO
{
	rModel,
	Float:rX,
	Float:rY,
	Float:rZ,
	Float:rRange
}
// Removebuilding array

enum e_map {
  eID,
  eName[64],
  eLoadedBy[MAX_PLAYER_NAME],
  eInt,
  eVw
};
new MapData[MAX_MAP][e_map],
  Iterator:Maps<MAX_MAP>;

// Removebuilding information enum
enum removedata
{
	rModel,
  rName[52],
	Float:rX,
	Float:rY,
	Float:rZ,
	Float:rRange,
}
// Removebuilding array
new RemoveObj[MAX_REMOVE_BUILDING][removedata],
    Iterator:RemoveBuild<MAX_REMOVE_BUILDING>;
new Iterator:DynObject<MAX_BUILDING>;
new DynObj[MAX_BUILDING];
new DynObjName[MAX_BUILDING][52];
new DynObMats[MAX_BUILDING][10];
new Text3D:GTAObjectText[SEARCH_DATA_SIZE];
new RemoveData[MAX_REMOVE_BUILDING][REMOVEINFO];
new Iterator:DynamicObjects<MAX_EDITING_OBJECT>;
new DynamicObject[MAX_EDITING_OBJECT];
new ObjectEditor[MAX_EDITING_OBJECT];
new DynamicObjectMaterial[MAX_EDITING_OBJECT][MAX_OBJECT_MATERIAL_SLOT];
new DynamicObjectPriority[MAX_EDITING_OBJECT];
new SelectObjectType[MAX_PLAYERS];