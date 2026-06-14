SetPlayerGPS(playerid, Float:x, Float:y, Float:z) {
    SetPlayerRaceCheckpoint(playerid, 1, x, y, z, 0,0,0, 4);
    SetPVarInt(playerid, "PlayerGPS", 1);
    return 1;
}