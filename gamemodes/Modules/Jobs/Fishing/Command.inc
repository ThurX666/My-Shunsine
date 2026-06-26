
CMD:fish(playerid,params[])
{
	if(pData[playerid][pFaction] > 0) return Error(playerid, "Kamu anggota faction, tidak bekerja jobs/sidejob.");
	new vehicleid = GetNearestVehicleToPlayer(playerid, 5.0, false);
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) return Error(playerid, "Anda tidak bisa menggunakan command ini disaat mengendarai!");
	if(DelayPlayer[playerid][DelayFishing] > 0) return Error(playerid, "Tidak bisa /fish gunakan /delay untuk mengecek");
	if(pData[playerid][pEnergy] <= 20) return Error(playerid, "Anda terlalu lelah untuk memancing lagi.");
	if(pData[playerid][pFishTool] < 1) return Error(playerid, "Anda tidak mempunyai fishing tool/pancingan.");
	if(pData[playerid][pWorm] < 1) return Error(playerid, "Anda tidak mempunyai umpan.");
	if(pData[playerid][pInFish] == 1) return Error(playerid, "Tunggu beberapa saat lagi.");
	if(FishWeight[playerid][4]) return Error(playerid, "You already have 5 fish, go to the fish factory to sell it!");
	foreach(new fishing : FishingArea) {
		if(IsPlayerInRangeOfPoint(playerid, 70, FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2])) {
			if(IsAtFishArea(playerid)) {
				stop pData[playerid][pFishingTime];
				pData[playerid][pFishingTime] = defer getFish(playerid);
				pData[playerid][pInFish] = 1;
				SendCustomMessage(playerid, "FISHING", "You've started fishing, you can cancel anytime using {FFFF00}'Y'");
				TogglePlayerControllable(playerid, 0);
				ApplyAnimation(playerid,"SWORD","sword_block",50.0 ,0,1,0,1,1);
				SetPlayerAttachedObject(playerid, 9,18632,6,0.079376,0.037070,0.007706,181.482910,0.000000,0.000000,1.000000,1.000000,1.000000);
			}
			else if(IsABoat(vehicleid) && pData[playerid][pSkillFishing] == 2) {
				stop pData[playerid][pFishingTime];
				pData[playerid][pFishingTime] = defer getFish(playerid);
				pData[playerid][pInFish] = 1;
				SendCustomMessage(playerid, "FISHING", "You've started fishing, you can cancel anytime using {FFFF00}'Y'");
				TogglePlayerControllable(playerid, 0);
				ApplyAnimation(playerid,"SWORD","sword_block",50.0 ,0,1,0,1,1);
				SetPlayerAttachedObject(playerid, 9,18632,6,0.079376,0.037070,0.007706,181.482910,0.000000,0.000000,1.000000,1.000000,1.000000);
			}
		}
	}
	return 1;
}

CMD:sellallfish(playerid,params[])
{
   	if(IsPlayerInRangeOfPoint(playerid, 4.0, 2844.0684,-1516.6871,11.3002))
    {
		new String[412], Float:count;
		format(String, sizeof(String), "Fish\tWeight\tPrice\n");
		for(new i = 0; i < 5; i++) if(FishWeight[playerid][i] > 0.0) {
			new total = floatround(FishWeight[playerid][i]*FishPrice);
			count += FishWeight[playerid][i];
			format(String, sizeof(String), "%s"WHITE_E"Ocean Fish\t"WHITE_E"%.1f lbs\t"GREEN_E"$%s\n", String, FishWeight[playerid][i], FormatMoney(total));
	    }
		format(String, sizeof(String), "%s"WHITE_E"Total:\t%.1f lbs\t"GREEN_E"$%s",String,count,FormatMoney(count*FishPrice));
		Dialog_Show(playerid,SellFish,DIALOG_STYLE_TABLIST_HEADERS,"Selling Fish",String,"Sell","Cancel");
    }
    else if(IsPlayerInRangeOfPoint(playerid, 4.0, -769.01, 1637.18, 27.32))
    {
		new String[412], Float:count;
		format(String, sizeof(String), "Fish\tWeight\tPrice\n");
		for(new i = 0; i < 5; i++) if(FishWeight[playerid][i] > 0.0) {
			new total = floatround(FishWeight[playerid][i]*FishPrice);
			count += FishWeight[playerid][i];
			format(String, sizeof(String), "%s"WHITE_E"Ocean Fish\t"WHITE_E"%.1f lbs\t"GREEN_E"$%s\n", String, FishWeight[playerid][i], FormatMoney(total));
	    }
		format(String, sizeof(String), "%s"WHITE_E"Total:\t%.1f lbs\t"GREEN_E"$%s",String,count,FormatMoney(count*FishPrice));
		Dialog_Show(playerid,SellFish,DIALOG_STYLE_TABLIST_HEADERS,"Selling Fish",String,"Sell","Cancel");
    }
    return 1;
}
