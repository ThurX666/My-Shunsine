
IsAtFishArea(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    if(IsPlayerInRangeOfPoint(playerid,1.0,403.8266,-2088.7598,7.8359) || IsPlayerInRangeOfPoint(playerid,1.0,398.7553,-2088.7490,7.8359)) return 1;
		else if(IsPlayerInRangeOfPoint(playerid,1.0,396.2197,-2088.6692,7.8359) || IsPlayerInRangeOfPoint(playerid,1.0,391.1094,-2088.7976,7.8359)) return 1;
		else if(IsPlayerInRangeOfPoint(playerid,1.0,383.4157,-2088.7849,7.8359) || IsPlayerInRangeOfPoint(playerid,1.0,374.9598,-2088.7979,7.8359)) return 1;
		else if(IsPlayerInRangeOfPoint(playerid,1.0,369.8107,-2088.7927,7.8359) || IsPlayerInRangeOfPoint(playerid,1.0,367.3637,-2088.7925,7.8359)) return 1;
		else if(IsPlayerInRangeOfPoint(playerid,1.0,362.2244,-2088.7981,7.8359) || IsPlayerInRangeOfPoint(playerid,1.0,354.5382,-2088.7979,7.8359)) return 1;
        else if(IsPlayerInRangeOfPoint(playerid,1.0,349.8621, -2052.0488, 7.8359) || IsPlayerInRangeOfPoint(playerid,1.0,349.8976, -2059.6501, 7.8359)) return 1;
        else if(IsPlayerInRangeOfPoint(playerid,1.0,349.9232, -2064.9419, 7.8359) || IsPlayerInRangeOfPoint(playerid,1.0,349.9330, -2067.3057, 7.8359)) return 1;
        else if(IsPlayerInRangeOfPoint(playerid,1.0,349.9572, -2072.4199, 7.8359)) return 1;
	}
	return 0;
}

timer getFish[30000](playerid)
{
    if(!pData[playerid][pInFish]) return 0;
    SendCustomMessage(playerid, "FISHING", ""YELLOW_E"You caught something on the pole, press {FF0000}'Y' {FFFF00}to pull the fishing rod");
    SetPVarInt(playerid, "Fishing", 1);
    return 1;
}

AddFish(playerid, Float:weight)
{
    for(new i = 0; i < 5; i++) if(!FishWeight[playerid][i]) {
        FishWeight[playerid][i] = weight;
        pData[playerid][pFishTool]--;
        pData[playerid][pWorm]--;
        SendCustomMessage(playerid, "FISHING", "{FFFF00}Ocean fish caught!, weight: %.1f lbs", weight);
        if(pData[playerid][pFishTool] == 0) return Info(playerid, "Fish tools anda rusak silahkan beli lagi");
        
        return 1;
    }
    Error(playerid, "You already have 5 fish, go to the fish factory to sell it!");
    return 1;
}
