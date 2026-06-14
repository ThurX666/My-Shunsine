
CMD:ads(playerid, params[])
{
	ShowAdvertisements(playerid);
	return 1;
}

CMD:ad(playerid, params[])
{
	if(isnull(params)) return Usage(playerid, "(/ad)vertise [advert text]");
    if(pData[playerid][pPhone] < 1) return Error(playerid, "You dont have phone!");
	if(pData[playerid][pCS] < 1) return Error(playerid, "Anda harus mempunyai Character Story untuk membuat iklan!");
	if(pData[playerid][pVip] > 1)
	{
		if(DelayPlayer[playerid][DelayAdvertisement] > 0) return Error(playerid, "Tunggu %d menit untuk membuat iklan.", DelayPlayer[playerid][DelayAdvertisement] / 60);
		if(isnull(params)) return Usage(playerid, "(/ad)vertise [advert text]");
		if (strlen(params) > 200) return Error(playerid, "Max characters length is 200 chars");
		format(pData[playerid][pAdvertise], 200, params);
		Dialog_Show(playerid, AdsType, DIALOG_STYLE_LIST, "Advertisement Type", "Automotive\nProperty\nEvent\nService\nJob Search", "Input", "Close");
    }
	else
	{
		foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
			if(Location[id][locType] == 12 && IsPlayerInRangeOfPoint(playerid, 3, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
				if(DelayPlayer[playerid][DelayAdvertisement] > 0) return Error(playerid, "Tunggu %d menit untuk membuat iklan.", DelayPlayer[playerid][DelayAdvertisement] / 60);
				if(isnull(params)) return Usage(playerid, "(/ad)vertise [advert text]");
				if (strlen(params) > 200) return Error(playerid, "Max characters length is 200 chars");
				format(pData[playerid][pAdvertise], 200, params);
				Dialog_Show(playerid, AdsType, DIALOG_STYLE_LIST, "Advertisement Type", "Automotive\nProperty\nEvent\nService\nJob Search", "Input", "Close");
			}
		}
	}
    return 1;
}
