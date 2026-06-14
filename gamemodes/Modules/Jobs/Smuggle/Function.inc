#include <YSI\y_hooks>
new SmugglerVehicle[3];

SendSmugglerMessage(text[]) {
  foreach (new i : Player) if (pData[i][pJob] == 8 || pData[i][pJob2] == 8) {
    SendCustomMessage(i, "SMUGGLER", "%s", text);
  }
  return 1;
}

hook OnGameModeInit() {
    SmugglerVehicle[0] = AddStaticVehicle(498, 1266.0, 388.0, 19.56, 180.0, 0, 0);
    SmugglerVehicle[1] = AddStaticVehicle(498, 1272.0, 397.0, 19.56, 180.0, 0, 0);
    SmugglerVehicle[2] = AddStaticVehicle(498, 1278.0, 388.0, 19.56, 180.0, 0, 0);
    return 1;
}

IsVehicleSmugglerVehicle(vehicleid)
{
    for (new i = 0; i < sizeof(SmugglerVehicle); i++) {
        if (SmugglerVehicle[i] == vehicleid) return 1;
    }
    return 0;
}
