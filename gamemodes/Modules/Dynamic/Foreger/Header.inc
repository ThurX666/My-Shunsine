#define MAX_BRUSH_FORAGER (200)
enum brushEnum {
    bushID,
    bushType,
    bushAmount,
    Float:bushPos[3],
    Float:bushRot[3],
    bushObject,
    bushArea
};
new ForegerData[MAX_BRUSH_FORAGER][brushEnum],
    Iterator:BushForager<MAX_BRUSH_FORAGER>;
new EditBushForager[MAX_PLAYERS];
new pForaging[MAX_PLAYERS];
new pForager[MAX_PLAYERS];