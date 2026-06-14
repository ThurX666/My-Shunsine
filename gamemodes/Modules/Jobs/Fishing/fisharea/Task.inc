
ptask Update_Zone_Fish[1000](playerid)
{
    new h, m, s;
    gettime(h, m, s);
    if (m == 0 && s == 0) {
        foreach(new fishing : FishingArea) {
            FishingData[fishing][Type] = random(3);
            if(IsValidDynamicMapIcon(mapiconfishing[playerid][fishing])) DestroyDynamicMapIcon(mapiconfishing[playerid][fishing]);
            if(IsABoat(GetPlayerVehicleID(playerid)))
            {
                switch(FishingData[fishing][Type]) {
                    case 0: mapiconfishing[playerid][fishing] = CreateDynamicMapIcon(FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2], 0, COLOR_RED, 0, 0, playerid, 1000, MAPICON_LOCAL);
					case 1: mapiconfishing[playerid][fishing] = CreateDynamicMapIcon(FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2], 0, COLOR_YELLOW, 0, 0, playerid, 1000, MAPICON_LOCAL);
					case 2: mapiconfishing[playerid][fishing] = CreateDynamicMapIcon(FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2], 0, COLOR_GREEN, 0, 0, playerid, 1000, MAPICON_LOCAL);
                }
            }
        }
    }
    return 1;
}
