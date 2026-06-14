#define MAX_SUITE_ROOM (20)
new PlayerEditSuiteRoom[MAX_PLAYERS][2];
new testsuiteZone[MAX_SUITE_ROOM] = {-1, ...};
new EditSuiteFurniture[MAX_PLAYERS][2];
new EditSuiteStructure[MAX_PLAYERS][2];
new SelectSuiteType[MAX_PLAYERS];
new ListedSuiteRoom[MAX_PLAYERS][LIMIT_PER_PLAYER+4];

enum {
    INVALID_AREA_INDEX = 0,
    SUITE_AREA_INDEX
}

enum suiteRoom {
  suiteRoomID,
  suiteRoomOwner[52],
  suiteRoomLocked,
  suiteRoomPrice,
  Float:suiteRoomDoors[6],
  Float:suiteRoomButtons[6],
  Float:suiteRoomAreaPos[5],
  suiteRoomWorld,
  suiteRoomInterior,
  suiteObjectDoors,
  suiteObjectButtons,
  suiteObjectText,
  suiteRoomArea
};
new SuiteRoom[MAX_SUITE_ROOM][suiteRoom],
  Iterator:SuiteRooms<MAX_SUITE_ROOM>;
