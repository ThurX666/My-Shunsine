
Dialog:SellFish(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		if(IsPlayerInRangeOfPoint(playerid, 4.0, 2844.0684,-1516.6871,11.3002))
		{
			new Float:count = 0.0, total;
			for(new i = 0; i < 5; i++) if(FishWeight[playerid][i] > 0.0) count += FishWeight[playerid][i];
			for(new i = 0; i < 5; i++) {
				FishWeight[playerid][i] = 0.0;
				FishName[playerid][i][0] = EOS;
			}
			StockCrateFish += 2;
			total = floatround(count*FishPrice);
			GivePlayerMoneyEx(playerid, total);
			SendClientMessageEx(playerid, COLOR_ARWIN, "FISHING: "WHITE_E"You've sold {FFFF00}%.1f lbs "WHITE_E"of fish for {FFFF00}$%s", count, FormatMoney(total));
			DelayPlayer[playerid][DelayFishing] = 1200;
			new random2 = RandomEx(1, 20);
			pData[playerid][pScoreFishing] += random2;
			if(pData[playerid][pScoreFishing] >= 100) pData[playerid][pSkillFishing] = 2;
			Crate_Save();
			new fish[212];

			format(fish, sizeof(fish), "{00FFFF}Canned Fish Crates\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup crate\nFish Available: "GREEN_E"%d "YELLOW_E"/ 40", StockCrateFish);
			UpdateDynamic3DTextLabelText(Fish2, COLOR_ARWIN, fish);
	    }
	    else if(IsPlayerInRangeOfPoint(playerid, 4.0, -769.01, 1637.18, 27.32))
	    {
			new Float:count = 0.0, total;
			for(new i = 0; i < 5; i++) if(FishWeight[playerid][i] > 0.0) count += FishWeight[playerid][i];
			for(new i = 0; i < 5; i++) {
				FishWeight[playerid][i] = 0.0;
				FishName[playerid][i][0] = EOS;
			}
			StockCrateFish2 += 2;
			Crate_Save();
			total = floatround(count*FishPrice);
			GivePlayerMoneyEx(playerid, total);
			SendClientMessageEx(playerid, COLOR_ARWIN, "FISHING: "WHITE_E"You've sold {FFFF00}%.1f lbs "WHITE_E"of fish for {FFFF00}$%s", count, FormatMoney(total));
			DelayPlayer[playerid][DelayFishing] = 1200;
			new random2 = RandomEx(1, 20);
			pData[playerid][pScoreFishing] += random2;
			if(pData[playerid][pScoreFishing] >= 100) pData[playerid][pSkillFishing] = 2;
			new fish[212];

			format(fish, sizeof(fish), "{00FFFF}Canned Fish Crates\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup crate\nFish Available: "GREEN_E"%d "YELLOW_E"/ 40", StockCrateFish2);
			UpdateDynamic3DTextLabelText(Fish3, COLOR_ARWIN, fish);
		}
	}
    return 1;
}

Dialog:BuyBait(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		new tbait = strval(inputtext);
		new String[212];
		if(!response)
		{
			format(String, sizeof(String), "Bait Price: $0.5");
			Dialog_Show( playerid, BuyBait, DIALOG_STYLE_INPUT, "Buy Bait",String, "Buy", "Cancel" );
		}
		else
		{
		    if(GetPlayerMoney(playerid) < tbait * 5) { Error(playerid, "Uang anda tidak cukup !"); return 1; }
            if(pData[playerid][pWorm] > 100) { Info(playerid, "Kamu telah memiliki banyak umpan."); return 1; }
            if(tbait < 1) { Error(playerid, "Minimal membeli 1 Umpan."); return 1; }
            new harga = tbait * 5;
			GivePlayerMoneyEx(playerid, -harga);
			format(String, sizeof(String), "FISH: Anda telah membeli %d Bait Umpan dengan harga %s",tbait, FormatMoney(harga));
			SendClientMessageEx(playerid,COLOR_ARWIN,String);
			pData[playerid][pWorm] += tbait;
		}
	}
    return 1;
}
