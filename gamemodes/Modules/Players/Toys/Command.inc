
CMD:destroyacc(playerid, params[]) {
    if (pData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new userid,index;
    if (sscanf(params, "ud", userid,index))
        return Usage(playerid, "/destroyacc [playerid/name] [acc index]");
    
    new string[128];
    AccData[userid][index][accExists] = 0;
    AccData[userid][index][accModel] = 0;
    
    if(IsPlayerAttachedObjectSlotUsed(userid, index))
    {
        RemovePlayerAttachedObject(userid, index);
        AccData[userid][index][accShow] = 0;
        MySQL_SavePlayerToys(userid, index);
    }
    format(string,sizeof(string),"DELETE FROM `aksesoris` WHERE `ID`='%d'", AccData[userid][index][accID]);
    mysql_tquery(g_SQL, string);
    
    SendCustomMessage(playerid, "DYOC","You have removed %s accessory index #%d.", ReturnName(userid), index);
    SendCustomMessage(userid, "DYOC","%s has removed your accessory index #%d.", ReturnName(playerid), index);
    return 1;
}

CMD:dyoc(playerid)
{
    new info[300],
        count = 0;

    strcat(info,"Index\tName\tBone\n");
    for (new id = 0; id != MAX_ACC; id++) if(AccData[playerid][id][accExists]) {
		if (!AccData[playerid][id][accBone]) { // proteksi buat player android
			AccData[playerid][id][accBone] = 1;
		}
		format(info, sizeof(info),  "%s%d\t%s\t%s\n", info, id, AccData[playerid][id][accName], accBones[AccData[playerid][id][accBone]-1]);
		if (count < MAX_ACC) {
			ListedAcc[playerid][count] = id;
			count++;
		}
    }
    if(!count) Error(playerid, "You don't have some accesories.");
    else Dialog_Show(playerid, Aksesoris, DIALOG_STYLE_TABLIST_HEADERS, "Player Accesories", info, "Select","Exit");
    return 1;
}
