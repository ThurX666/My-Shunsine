#include <YSI\y_hooks>

hook OnPlayerLeaveDynArea(playerid, areaid) {
  new info[2];
  Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, info);

  if (info[0] == FLAT_AREA_INDEX) {
    #if defined DEVELOPMENT
      new flatroom = info[1];
      SendClientMessageEx(playerid, -1, "[debug]: you've leaving from flatroom area ID: "YELLOW_E"%d", flatroom);
    #endif

    CancelEdit(playerid);
  }
  return 1;
}
