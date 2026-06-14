#define MAX_FISHING_AREA 50
enum fishingarea {
    ID,
    Float:Pos[3],
    Type,
    Zone
}
new FishingData[MAX_FISHING_AREA][fishingarea],
    Iterator:FishingArea<MAX_FISHING_AREA>;
new mapiconfishing[MAX_PLAYERS][MAX_FISHING_AREA];
