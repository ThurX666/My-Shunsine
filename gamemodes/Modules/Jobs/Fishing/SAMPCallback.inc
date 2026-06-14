#include <YSI\y_hooks>
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_YES) {
		if(pData[playerid][pInFish] == 1 && !GetPVarInt(playerid, "Fishing")) {
			TogglePlayerControllable(playerid, 1);
			ClearAnimations(playerid);
			StopLoopingAnim(playerid);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			RemovePlayerAttachedObject(playerid, 9);
			pData[playerid][pInFish] = 0;
			DeletePVar(playerid, "Fishing");
			stop pData[playerid][pFishingTime];
			return 1;
		}
		else if(GetPVarInt(playerid, "Fishing") && pData[playerid][pInFish] == 1) {
			TogglePlayerControllable(playerid, 1);
			foreach(new fishing : FishingArea) if(IsPlayerInRangeOfPoint(playerid, 70, FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2])) {
				new rand = random(8);
				switch(FishingData[fishing][Type])
				{
					case 0: {
						switch(rand)
						{
							case 0: SendCustomMessage(playerid, "FISHING", "You caught only junk");
							case 1: AddFish(playerid, RandomFloat(1.0,3.5));
							case 2: AddFish(playerid, RandomFloat(1.0,3.5));
							case 3: AddFish(playerid, RandomFloat(1.0,3.5));
							case 4: SendCustomMessage(playerid, "FISHING", "You caught only junk");
							case 5: AddFish(playerid, RandomFloat(1.0,3.5));
							case 6: AddFish(playerid, RandomFloat(1.0,3.5));
							case 7: SendCustomMessage(playerid, "FISHING", "You caught only junk");
						}
					}
					case 1: {
						switch(rand)
						{
							case 0: AddFish(playerid, RandomFloat(1.9,4.5));
							case 1: AddFish(playerid, RandomFloat(1.9,4.5));
							case 2: AddFish(playerid, RandomFloat(1.9,4.5));
							case 3: AddFish(playerid, RandomFloat(1.9,4.5));
							case 4: SendCustomMessage(playerid, "FISHING", "You caught only junk");
							case 5: AddFish(playerid, RandomFloat(1.9,4.5));
							case 6: AddFish(playerid, RandomFloat(1.9,4.5));
							case 7: SendCustomMessage(playerid, "FISHING", "You caught only junk");
						}
					}
					case 2: {
						switch(rand)
						{
							case 0: AddFish(playerid, RandomFloat(2.5,6.5));
							case 1: AddFish(playerid, RandomFloat(2.5,6.5));
							case 2: SendCustomMessage(playerid, "FISHING", "You caught only junk");
							case 3: AddFish(playerid, RandomFloat(2.5,6.5));
							case 4: AddFish(playerid, RandomFloat(2.5,6.5));
							case 5: AddFish(playerid, RandomFloat(2.5,6.5));
							case 6: AddFish(playerid, RandomFloat(2.5,6.5));
							case 7: AddFish(playerid, RandomFloat(2.5,6.5));
						}
					}
				} 
			}
			stop pData[playerid][pFishingTime];
			ClearAnimations(playerid);
			StopLoopingAnim(playerid);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			RemovePlayerAttachedObject(playerid, 9);
			pData[playerid][pInFish] = 0;
			DeletePVar(playerid, "Fishing");
			return 1;
		}
	}
	return 1;
}
