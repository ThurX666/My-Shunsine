#include <YSI\y_hooks>

hook OnPlayerConnect(playerid) {
    RemoveBuildingForPlayer(playerid, 2629, 764.867, -59.710, 999.671, 0.250);
    RemoveBuildingForPlayer(playerid, 2629, 768.539, -59.554, 999.671, 0.250);
    RemoveBuildingForPlayer(playerid, 1985, 773.351, -59.250, 1002.590, 0.250);
    RemoveBuildingForPlayer(playerid, 1985, 773.351, -61.531, 1002.590, 0.250);
    RemoveBuildingForPlayer(playerid, 1985, 776.156, -64.726, 1002.590, 0.250);
    RemoveBuildingForPlayer(playerid, 1985, 773.867, -64.718, 1002.590, 0.250);
    RemoveBuildingForPlayer(playerid, 2630, 774.625, -68.640, 999.679, 0.250);
    RemoveBuildingForPlayer(playerid, 2627, 758.382, -65.507, 999.671, 0.250);
    RemoveBuildingForPlayer(playerid, 2631, 759.179, -60.062, 999.726, 0.250);
    return 1;
}
