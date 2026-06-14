
Dialog:ListProperties(playerid, response, listitem, inputtext[]) {
    if (response) {
        switch (listitem) {
            case 0: {
                if(!GetOwnedHouses(playerid)) return Error(playerid, "You don't have a houses.");

                new str[256], price, count;
                strcat(str, "ID\tAddress\tPrice\n");
                foreach (new i : Houses) if (Player_OwnsHouse(playerid, i)) {
                    price = hData[i][hPrice]/30;
                    strcat(str, sprintf("%d\t%s\t"GREEN_E"$%s\n",i,hData[i][hAddress],FormatMoney(price)));
                    ListedHouse[playerid][count++] = i;
                }
				if(count) Dialog_Show(playerid, SellHouse, DIALOG_STYLE_TABLIST_HEADERS, "Sell House", str, "Sell", "Back");
				else Dialog_Show(playerid, Unesed, DIALOG_STYLE_MSGBOX, "Selling Property", "Anda tidak mempunyai property", "Back", "");
            }
            case 1: {
                if(!GetOwnedBisnis(playerid)) return Error(playerid, "You don't have a bisnis.");

                new str[256], price, count;
                strcat(str, "ID\tName\tLocation\tPrice\n");
                for (new i = 0; i < MAX_BISNIS; i ++) if (Player_OwnsBisnis(playerid, i)) {
                    price = bData[i][bPrice]/2;
                    strcat(str, sprintf("%d\t%s\t%s\t"GREEN_E"$%s\n",i,ReplaceString(bData[i][bName]),GetLocation(bData[i][bExtposX], bData[i][bExtposY], bData[i][bExtposZ]),FormatMoney(price)));
                    ListedBusiness[playerid][count++] = i;
                }
				if(count) Dialog_Show(playerid, SellBusiness, DIALOG_STYLE_TABLIST_HEADERS, "Sell Business", str, "Sell", "Back");
				else Dialog_Show(playerid, Unesed, DIALOG_STYLE_MSGBOX, "Selling Property", "Anda tidak mempunyai property", "Back", "");
            }
            case 2: {
                new str[256], price, count;
                strcat(str, "ID\tName\tLocation\tPrice\n");
                foreach (new wsid : Workshop) if(OwnerWorkshop(playerid, wsid)) {
                    price = WorkshopData[wsid][Price]/2;
                    strcat(str, sprintf("%d\t%s\t%s\t"GREEN_E"$%s\n",wsid,ReplaceString(WorkshopData[wsid][Name]),GetLocation(WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]),FormatMoney(price)));
                    ListedWorkshop[playerid][count++] = wsid;
                }
				if(count) Dialog_Show(playerid, SellWorkshop, DIALOG_STYLE_TABLIST_HEADERS, "Sell Workshop", str, "Sell", "Back");
				else Dialog_Show(playerid, Unesed, DIALOG_STYLE_MSGBOX, "Selling Property", "Anda tidak mempunyai property", "Back", "");
            }
            case 3: {
                if (!FurnStore_GetCount(playerid))
                    return Error(playerid, "You don't have any furn store");

                new str[128], price, count;
                strcat(str, "ID\tName\tLocation\tPrice\n");
                foreach (new i : FurnStore) if (FurnStore_IsOwner(playerid, i)) {
                    price = storeData[i][storePrice]/2;
                    strcat(str,sprintf("%d\t%s\t%s\t$%s\n", i, storeData[i][storeName], GetLocation(storeData[i][storePos][0], storeData[i][storePos][1], storeData[i][storePos][2]), FormatMoney(price)));
                    ListedFurnstore[playerid][count++] = i;
                }
				if(count) Dialog_Show(playerid, SellFurnstore, DIALOG_STYLE_TABLIST_HEADERS, "Sell Furniture Store", str, "Sell", "Back");
				else Dialog_Show(playerid, Unesed, DIALOG_STYLE_MSGBOX, "Selling Property", "Anda tidak mempunyai property", "Back", "");
            }
            case 4: {
                if (!FlatRoom_GetCount(playerid))
                    return Error(playerid, "You don't have any flat");
                
                new str[128], price, count, FlatType[12], address[24];
                strcat(str, "ID\tType\tAddress\tPrice\n");
                foreach (new i : FlatRooms) if (FlatRoom_IsOwner(playerid, i)) {
                    price = FlatRoom[i][flatRoomPrice]/2;
                    Flat_GetType(i, FlatType);
                    FlatRoom_GetAddress(i, address);
                    strcat(str,sprintf("%d\t%s\t%s\t$%s\n",i,FlatType,address,FormatMoney(price)));
                    ListedFlat[playerid][count++] = i;
                }
				if(count) Dialog_Show(playerid, SellFlat, DIALOG_STYLE_TABLIST_HEADERS, "Sell Flat", str, "Sell", "Back");
				else Dialog_Show(playerid, Unesed, DIALOG_STYLE_MSGBOX, "Selling Property", "Anda tidak mempunyai property", "Back", "");
            }
			case 5: {
                if (!GetOwnedPvGarage(playerid))
                    return Error(playerid, "You don't have any private garage");
                
                new str[128], price, count;
                strcat(str, "ID\tAddress\tPrice\n");
                foreach (new pvid : PrivateGarage) if (OwnerPvGarage(playerid, pvid)) {
                    price = PrivateGarage[pvid][Price]/2;
                    strcat(str,sprintf("%d\t%s\t$%s\n",pvid,GetLocation(PrivateGarage[pvid][GaragePos][0], PrivateGarage[pvid][GaragePos][1], PrivateGarage[pvid][GaragePos][2]),FormatMoney(price)));
                    ListedPvGarage[playerid][count++] = pvid;
                }
				if(count) Dialog_Show(playerid, SellPvGarage, DIALOG_STYLE_TABLIST_HEADERS, "Selling Private Garage", str, "Selling", "Back");
				else Dialog_Show(playerid, Unesed, DIALOG_STYLE_MSGBOX, "Selling Property", "Anda tidak mempunyai property", "Back", "");
            }
        }
    }
    return 1;
}

Dialog:SellPvGarage(playerid, response, listitem, inputtext[]) {
    if (response) {
        new pvid = ListedPvGarage[playerid][listitem],
            price = PrivateGarage[pvid][Price]/2;
        
        if (price < 1)
            return Error(playerid, "You can't sell this house");
		format(PrivateGarage[pvid][Owner], MAX_PLAYER_NAME, "-");
		PvGarageRefresh(pvid);
		PvGarageSave(pvid);
        GivePlayerMoneyEx(playerid, price);
        SendCustomMessage(playerid, "PROPERTIES", "You've been sold your private garage for "GREEN_E"$%s", FormatMoney(price));
    } else callcmd::sellproperty(playerid, "");
    return 1;
}

Dialog:SellHouse(playerid, response, listitem, inputtext[]) {
    if (response) {
        new houseid = ListedHouse[playerid][listitem],
            price = hData[houseid][hPrice]/30;

        if (price < 1)
            return Error(playerid, "You can't sell this house");

		HouseReset(houseid);
        House_RemoveFurniture(houseid);
        HouseStructure_DeleteAll(houseid);
		House_Save(houseid);
		House_Refresh(houseid);

        GivePlayerMoneyEx(playerid, price);
        SendCustomMessage(playerid, "PROPERTIES", "You've been sold your house for "GREEN_E"$%s", FormatMoney(price));
    } else callcmd::sellproperty(playerid, "");
    return 1;
}

Dialog:SellBusiness(playerid, response, listitem, inputtext[]) {
    if (response) {
        new bizid = ListedBusiness[playerid][listitem],
            price = bData[bizid][bPrice]/2;
        
        if (price < 1)
            return Error(playerid, "You can't sell this business");

        Bisnis_Reset(bizid);
		Bisnis_Save(bizid);
		Bisnis_Refresh(bizid);

        GivePlayerMoneyEx(playerid, price);
        SendCustomMessage(playerid, "PROPERTIES", "You've been sold your business for "GREEN_E"$%s", FormatMoney(price));
    } else callcmd::sellproperty(playerid, "");
    return 1;
}

Dialog:SellWorkshop(playerid, response, listitem, inputtext[]) {
    if (response) {
        new wsid = ListedWorkshop[playerid][listitem], price = WorkshopData[wsid][Price]/2;
        if (price < 1) return Error(playerid, "You can't sell this workshop");

		GivePlayerMoneyEx(playerid, price);
        SendCustomMessage(playerid, "PROPERTIES", "You've been sold your workshop for "GREEN_E"%s", FormatMoney(price));
        format(WorkshopData[wsid][Owner], 52, "-");
        format(WorkshopData[wsid][Name], 52, "%s Workshop", GetLocation(WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]));
		WorkshopData[wsid][Price] = 999999;
        WorkshopData[wsid][StorageWorkshop][0] = 0;
        WorkshopData[wsid][StorageWorkshop][1] = 0;
		WorkshopEmployee_RemoveAll(wsid);
		WorkshopRefresh(wsid);
        WorkshopSave(wsid);
    } else callcmd::sellproperty(playerid, "");
    return 1;
}

Dialog:SellFurnstore(playerid, response, listitem, inputtext[]) {
    if (response) {
        new id = ListedFurnstore[playerid][listitem],
            price = storeData[id][storePrice]/2;
        
        if (price < 1)
            return Error(playerid, "You can't sell this store");

        storeData[id][storeVault] = storeData[id][storeOwner] = 0;
		storeData[id][storeEmploye][0] = storeData[id][storeEmploye][1] = storeData[id][storeEmploye][2] = 0;
		format(storeData[id][storeOwnerName], MAX_PLAYER_NAME, "None");

        foreach(new i : FurnObject) if(FurnStore[i][furnStoreId] == storeData[id][storeID])
        {
            DestroyDynamic3DTextLabel(FurnStore[i][furnLabel]);
            DestroyDynamicObject(FurnStore[i][furnObject]);
            FurnStore[i][furnObject] = INVALID_STREAMER_ID;

            mysql_tquery(g_SQL, sprintf("DELETE FROM `furnobject` WHERE id=%d", FurnStore[i][furnID]));

            FurnStore[i][furnID] = 0;
            FurnStore[i][furnStoreId] = 0;

            new current = i;
            Iter_SafeRemove(FurnObject, current, i);
        }

		FurnStore_Refresh(id);
		FurnStore_Save(id);
		
        GivePlayerMoneyEx(playerid, price);
        SendCustomMessage(playerid, "PROPERTIES", "You've been sold your furnstore for "GREEN_E"$%s", FormatMoney(price));
    } else callcmd::sellproperty(playerid, "");
    return 1;
}

Dialog:SellFlat(playerid, response, listitem, inputtext[]) {
    if (!response)
        return callcmd::sellproperty(playerid, "");
    
    new flatid = ListedFlat[playerid][listitem],
        price = FlatRoom[flatid][flatRoomPrice]/2;

    if (price < 1)
        return Error(playerid, "You can't sell this flat");
    
    FlatRoom[flatid][flatRoomOwner] = 0;
    GivePlayerMoneyEx(playerid, price);
    FlatStructure_DeleteAll(flatid, true);
    FlatFurniture_DeleteAll(flatid);
    Flat_RemoveAllItems(flatid);

    FlatRoom_Refresh(flatid);
    FlatRoom_Save(flatid);
    SendCustomMessage(playerid, "PROPERTIES", "You've been sold your flat for "GREEN_E"$%s", FormatMoney(price));
    return 1;
}

Dialog:ChangeOrigin(playerid, response, listitem, inputtext[]) {
    if (response) {
		new Otherid = GetPVarInt(playerid, "OtheridChangeOrigin");
		switch(listitem)
		{
			case 0:
			{
				pData[Otherid][pAccent1] = 0;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 1:
			{	
				pData[Otherid][pAccent1] = 1;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 2:
			{
				pData[Otherid][pAccent1] = 2;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 3:
			{
				pData[Otherid][pAccent1] = 3;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 4:
			{
				pData[Otherid][pAccent1] = 4;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 5:
			{
				pData[Otherid][pAccent1] = 5;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 6:
			{
				pData[Otherid][pAccent1] = 6;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 7:
			{	
				pData[Otherid][pAccent1] = 7;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 8:
			{
				pData[Otherid][pAccent1] = 8;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 9:
			{
				pData[Otherid][pAccent1] = 9;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 10:
			{
				pData[Otherid][pAccent1] = 10;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 11:
			{
				pData[Otherid][pAccent1] = 11;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 12:
			{
				pData[Otherid][pAccent1] = 12;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 13:
			{	
				pData[Otherid][pAccent1] = 13;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 14:
			{
				pData[Otherid][pAccent1] = 14;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 15:
			{
				pData[Otherid][pAccent1] = 15;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 16:
			{
				pData[Otherid][pAccent1] = 16;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 17:
			{
				pData[Otherid][pAccent1] = 17;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 18:
			{
				pData[Otherid][pAccent1] = 18;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 19:
			{	
				pData[Otherid][pAccent1] = 19;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 20:
			{
				pData[Otherid][pAccent1] = 20;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 21:
			{
				pData[Otherid][pAccent1] = 21;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 22:
			{
				pData[Otherid][pAccent1] = 22;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 23:
			{
				pData[Otherid][pAccent1] = 23;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 24:
			{
				pData[Otherid][pAccent1] = 24;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 25:
			{	
				pData[Otherid][pAccent1] = 25;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 26:
			{
				pData[Otherid][pAccent1] = 26;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 27:
			{
				pData[Otherid][pAccent1] = 27;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 28:
			{
				pData[Otherid][pAccent1] = 28;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 29:
			{
				pData[Otherid][pAccent1] = 29;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
			case 30:
			{
				pData[Otherid][pAccent1] = 30;
				new String[256];
				format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
				SendClientMessageEx(playerid,COLOR_ARWIN,String);
				SendCustomMessage(playerid, "ORIGIN", "You've set the origin of "AQUA_E"%s "WHITE_E"to "GREEN_E"'%s'", ReturnName(Otherid), GetPlayerAccent(Otherid));
			}
		}
	}
    return 1;
}

Dialog:TakeClaims(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new otherid = GetPVarInt(playerid, "OtheridTakeClaims");
		switch(listitem)
		{	
			case 0:
			{
				pData[playerid][pClaimVIP][2]--;
				SendClientMessageEx(playerid, COLOR_ARWIN, "TAKE: "YELLOW_E"You managed to take "AQUA_E"%s's "YELLOW_E"house gate", ReturnName2(otherid));
				DeletePVar(playerid, "OtheridTakeClaims");
			}
			case 1:
			{
				pData[playerid][pClaimVIP][0]--;
				SendClientMessageEx(playerid, COLOR_ARWIN, "TAKE: "YELLOW_E"You managed to take "AQUA_E"%s's "YELLOW_E"house mapping", ReturnName2(otherid));
				DeletePVar(playerid, "OtheridTakeClaims");
			}
		}
	}
	else DeletePVar(playerid, "OtheridTakeClaims");
    return 1;
}

Dialog:ChangeMask(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		if(strlen(inputtext) < 7) return Error(playerid, "New phone number can't be shorter than 7 characters!"),  Dialog_Show(playerid, ChangeMask, DIALOG_STYLE_INPUT, ""YELLOW_E"Change Mask Number ", "Masukan no mask Yang Mau Anda Gunakan", "Change", "Exit");
		if(strlen(inputtext) > 8) return Error(playerid, "New phone number can't be longer than 8 characters!"),  Dialog_Show(playerid, ChangeMask, DIALOG_STYLE_INPUT, ""YELLOW_E"Change Mask Number ", "Masukan no mask Yang Mau Anda Gunakan", "Change", "Exit");
		
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "SELECT mask FROM players WHERE mask='%d'", strval(inputtext));
		mysql_tquery(g_SQL, query, "ChangeMask", "ii", playerid, strval(inputtext));
	}
    return 1;
}

Dialog:CustomPlate(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		pData[playerid][pListitems] = gListedItems[playerid][listitem];
		Dialog_Show(playerid, CustomPlate1, DIALOG_STYLE_INPUT, "Custom Plate", "Masukan teks yang ingin anda jadikan plate kendaraan anda", "Select", "Close");
	}
    return 1;
}

Dialog:CustomPlate1(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new carid = pData[playerid][pListitems];
		if(!IsValidVehicle(pvData[carid][cVeh])) return 0;
		if(pvData[carid][cOwner] == pData[playerid][pID])
		{
			format(pvData[carid][cPlate], 32, "%s", inputtext);
			new plate[62];
			format(plate, sizeof(plate), ""GREEN_E"%s", pvData[carid][cPlate]);
			SetVehicleNumberPlate(pvData[carid][cVeh], plate);
			SetVehicleNumberPlate(pvData[carid][cVeh], inputtext);
			SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You've turned your vehicle's plate into a {00FFFF}%s", inputtext);
			pData[playerid][pGold] -= 100;
		}
	}
    return 1;
}

Dialog:ChangePhone(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		if(strlen(inputtext) < 4) return Error(playerid, "New phone number can't be shorter than 4 characters!"),  Dialog_Show(playerid, ChangePhone, DIALOG_STYLE_INPUT, ""YELLOW_E"Change Phone Number ", "Masukan No Phone Yang Mau Anda Gunakan", "Change", "Exit");
		if(strlen(inputtext) > 8) return Error(playerid, "New phone number can't be longer than 8 characters!"),  Dialog_Show(playerid, ChangePhone, DIALOG_STYLE_INPUT, ""YELLOW_E"Change Phone Number ", "Masukan No Phone Yang Mau Anda Gunakan", "Change", "Exit");
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "SELECT phone FROM players WHERE phone='%d'", strval(inputtext));
		mysql_tquery(g_SQL, query, "PhoneNumberUpdate", "ii", playerid, strval(inputtext));
	}
    return 1;
}

Dialog:ChangeBank(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		if(strlen(inputtext) < 8) return Error(playerid, "New Bank Account number can't be shorter than 8 characters!"),  Dialog_Show(playerid, ChangeBank, DIALOG_STYLE_INPUT, ""YELLOW_E"Change Phone Number ", "Masukan No Phone Yang Mau Anda Gunakan", "Change", "Exit");
		if(strlen(inputtext) > 9) return Error(playerid, "New phone Account can't be longer than 9 characters!"),  Dialog_Show(playerid, ChangeBank, DIALOG_STYLE_INPUT, ""YELLOW_E"Change Phone Number ", "Masukan No Phone Yang Mau Anda Gunakan", "Change", "Exit");
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "SELECT brek FROM players WHERE brek='%d'", strval(inputtext));
		mysql_tquery(g_SQL, query, "BankNumberUpdate", "ii", playerid, strval(inputtext));
	}
    return 1;
}

Dialog:DialogHBE(playerid, response, listitem, inputtext[]) {
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
				PlayerTextDrawHide(playerid, JGHUNGER[playerid]);
				PlayerTextDrawHide(playerid, JGTHIRST[playerid]);
				TextDrawHideForPlayer(playerid, simpletd[3]);
				TextDrawHideForPlayer(playerid, simpletd[8]);
				TextDrawHideForPlayer(playerid, simpletd[0]);

				for(new i; i < 4; i++)
				{
					TextDrawHideForPlayer(playerid, SimpleStyleTD[i]);
				}
				PlayerTextDrawHide(playerid, PHungerTD[playerid]);
				PlayerTextDrawHide(playerid, PThirstTD[playerid]);

                pData[playerid][pHBEMode] = 1;
 
				for(new i; i < 6; i++)
				{
					TextDrawShowForPlayer(playerid, SaStyleTD[i]);
				}
				PlayerTextDrawShow(playerid, SAPHungerTD[playerid]);
				PlayerTextDrawShow(playerid, SAPThirstTD[playerid]);
			
            }
            case 1:
            {
				for(new i; i < 6; i++)
				{
					TextDrawHideForPlayer(playerid, SaStyleTD[i]);
				}
				PlayerTextDrawHide(playerid, SAPHungerTD[playerid]);
				PlayerTextDrawHide(playerid, SAPThirstTD[playerid]);

				for(new i; i < 4; i++)
				{
					TextDrawHideForPlayer(playerid, SimpleStyleTD[i]);
				}
				PlayerTextDrawHide(playerid, PHungerTD[playerid]);
				PlayerTextDrawHide(playerid, PThirstTD[playerid]);

                pData[playerid][pHBEMode] = 2;
				TextDrawShowForPlayer(playerid, simpletd[0]);
				PlayerTextDrawShow(playerid, JGHUNGER[playerid]);
				PlayerTextDrawShow(playerid, JGTHIRST[playerid]);
				TextDrawShowForPlayer(playerid, simpletd[3]);
				TextDrawShowForPlayer(playerid, simpletd[8]);
            }
			case 2:
			{
				for(new i; i < 6; i++)
				{
					TextDrawHideForPlayer(playerid, SaStyleTD[i]);
				}
				PlayerTextDrawHide(playerid, SAPHungerTD[playerid]);
				PlayerTextDrawHide(playerid, SAPThirstTD[playerid]);	

				TextDrawHideForPlayer(playerid, simpletd[0]);
				PlayerTextDrawHide(playerid, JGHUNGER[playerid]);
				PlayerTextDrawHide(playerid, JGTHIRST[playerid]);
				TextDrawHideForPlayer(playerid, simpletd[3]);
				TextDrawHideForPlayer(playerid, simpletd[8]);

                pData[playerid][pHBEMode] = 3;
				for(new i; i < 4; i++)
				{
					TextDrawShowForPlayer(playerid, SimpleStyleTD[i]);
				}
				PlayerTextDrawShow(playerid, PHungerTD[playerid]);
				PlayerTextDrawShow(playerid, PThirstTD[playerid]);
			}
            case 3:
            {
                pData[playerid][pHBEMode] = 0;
		
				for(new i; i < 6; i++)
				{
					TextDrawHideForPlayer(playerid, SaStyleTD[i]);
				}
				PlayerTextDrawHide(playerid, SAPHungerTD[playerid]);
				PlayerTextDrawHide(playerid, SAPThirstTD[playerid]);
				
				TextDrawHideForPlayer(playerid, simpletd[0]);
				PlayerTextDrawHide(playerid, JGHUNGER[playerid]);
				PlayerTextDrawHide(playerid, JGTHIRST[playerid]);
				TextDrawHideForPlayer(playerid, simpletd[3]);
				TextDrawHideForPlayer(playerid, simpletd[8]);

				for(new i; i < 4; i++)
				{
					TextDrawHideForPlayer(playerid, SimpleStyleTD[i]);
				}
				PlayerTextDrawHide(playerid, PHungerTD[playerid]);
				PlayerTextDrawHide(playerid, PThirstTD[playerid]);
            }
        }
    }
    return 1;
}

Dialog:DialogHudMode(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				Dialog_Show(playerid, DialogHBE, DIALOG_STYLE_LIST, "HBE Mode", "SA STYLE\nSIMPLE\nOLD SCHOOL\nHide", "Set", "Close");
			}
			case 1:
			{	
				if(TogglePlayer[playerid][ToggleDate])
				{
					TextDrawHideForPlayer(playerid, Date);
					TogglePlayer[playerid][ToggleDate] = 0;
				}
				else {
					TextDrawShowForPlayer(playerid, Date);
					TogglePlayer[playerid][ToggleDate] = 1;
				}
			}
			case 2:
			{
				if(TogglePlayer[playerid][ToggleTime])
				{
					TextDrawHideForPlayer(playerid, Time);
					TogglePlayer[playerid][ToggleTime] = 0;
				}
				else {
					TextDrawShowForPlayer(playerid, Time);
					TogglePlayer[playerid][ToggleTime] = 1;
				}
			}
			case 3:
			{
				if(TogglePlayer[playerid][ToggleMoney])
				{
					TextDrawHideForPlayer(playerid, DollarCents);
					TogglePlayer[playerid][ToggleMoney] = 0;
				}
				else {
					TextDrawShowForPlayer(playerid, DollarCents);
					TogglePlayer[playerid][ToggleMoney] = 1;
				}
			}
			case 4:
			{
				if(TogglePlayer[playerid][ToggleGPS])
				{
					PlayerTextDrawHide(playerid, GPSLocation[playerid]);
					TogglePlayer[playerid][ToggleGPS] = 0;
				}
				else {
					PlayerTextDrawShow(playerid, GPSLocation[playerid]);
					TogglePlayer[playerid][ToggleGPS] = 1;
				}
			}
			case 5:
			{
				if(TogglePlayer[playerid][ToggleWeb])
				{
					TextDrawHideForPlayer(playerid, Webtd[2]);
					// TextDrawHideForPlayer(playerid, Webtd[1]);
					// TextDrawHideForPlayer(playerid, Webtd[2]);
					TogglePlayer[playerid][ToggleWeb] = 0;
				}
				else {
					TextDrawShowForPlayer(playerid, Webtd[2]);
					// TextDrawShowForPlayer(playerid, Webtd[1]);
					// TextDrawShowForPlayer(playerid, Webtd[2]);
					TogglePlayer[playerid][ToggleWeb] = 1;
				}
			}
		}
	}
    return 1;
}

Dialog:DialogToggle(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				if(!pData[playerid][pTogGlobalOoc])
				{
					pData[playerid][pTogGlobalOoc] = 1;
					// SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan log server.");
				}
				else
				{
					pData[playerid][pTogGlobalOoc] = 0;
					// SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan log server.");
				}
			}
			case 1:
			{
				return callcmd::togpm(playerid);
			}
			case 2:
			{	
				return callcmd::togwt(playerid);
			}
			case 3:
			{	
				return callcmd::togfaction(playerid);
			}
			case 4:
			{
				return callcmd::togads(playerid);
			}
			case 5:
			{
				if(!pData[playerid][pTogQuizVote])
				{
					pData[playerid][pTogQuizVote] = 1;
					// SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan log server.");
				}
				else
				{
					pData[playerid][pTogQuizVote] = 0;
					// SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan log server.");
				}
			}
			case 6:
			{
				if(!pData[playerid][pTogStaffQuestion])
				{
					pData[playerid][pTogStaffQuestion] = 1;
					// SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan log server.");
				}
				else
				{
					pData[playerid][pTogStaffQuestion] = 0;
					// SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan log server.");
				}
			}
			case 7:
			{
				if(!pData[playerid][pTogStaffReport])
				{
					pData[playerid][pTogStaffReport] = 1;
					// SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan log server.");
				}
				else
				{
					pData[playerid][pTogStaffReport] = 0;
					// SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan log server.");
				}
			}
			case 8:
			{
				if(!pData[playerid][pTogStaffChat])
				{
					pData[playerid][pTogStaffChat] = 1;
					// SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah menonaktifkan log server.");
				}
				else
				{
					pData[playerid][pTogStaffChat] = 0;
					// SendClientMessageEx(playerid, COLOR_ARWIN, "TOG: "WHITE_E"Anda telah mengaktifkan log server.");
				}
			}
		}
	}
    return 1;
}

Dialog:TogAuto(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				if(pData[playerid][pTogPaycheck] == 0)
				{
					pData[playerid][pTogPaycheck] = 1;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Automatic Paycheck claiming has been "GREEN_E"enable");
					return callcmd::togauto(playerid, "");
				}
				else
				{
					pData[playerid][pTogPaycheck] = 0;	
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Automatic Paycheck claiming has been "RED_E"disable");
					return callcmd::togauto(playerid, "");
				}
			}
			case 1:
			{
				if(pData[playerid][pTogHandbrake] == 0) {
					pData[playerid][pTogHandbrake] = 1;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: {FFFFFF}Automatic vehicle handbrake has been {00FF00}enabled");
					return callcmd::togauto(playerid, "");
				}
				else {
					pData[playerid][pTogHandbrake] = 0;	
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: {FFFFFF}Automatic vehicle handbrake has been {FF0000}disabled");
					return callcmd::togauto(playerid, "");
				}
			}
			case 2:
			{
				if(pData[playerid][pTogSealtbelt] == 0)
				{
					pData[playerid][pTogSealtbelt] = 1;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Automatic car seatbelt has been "GREEN_E"enable");
					return callcmd::togauto(playerid, "");
				}
				else
				{
					pData[playerid][pTogSealtbelt] = 0;	
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Automatic car seatbelt has been "RED_E"disable");
					return callcmd::togauto(playerid, "");
				}
			}
			case 3:
			{
				if(pData[playerid][pTogHelmet] == 0)
				{
					pData[playerid][pTogHelmet] = 1;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Automatic wear/remove motorclycle Helmet has been "GREEN_E"enable");
					return callcmd::togauto(playerid, "");
				}
				else
				{
					pData[playerid][pTogHelmet] = 0;	
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Automatic wear/remove motorclycle Helmet has been "RED_E"disable");
					return callcmd::togauto(playerid, "");
				}
			}
			case 4:
			{
				if(pData[playerid][pRadioStream] == 0)
				{
					pData[playerid][pRadioStream] = 1;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Automatic disable radiostream motorclycle Helmet has been "GREEN_E"enable");
					return callcmd::togauto(playerid, "");
				}
				else
				{
					pData[playerid][pRadioStream] = 0;	
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Automatic disble audio stream has been "RED_E"disable");
					return callcmd::togauto(playerid, "");
				}
			}
			case 5:
			{
				if(pData[playerid][pTogChat] == 0)
				{
					pData[playerid][pTogChat] = 1;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Automatic Upper-case first leter of chat "GREEN_E"enable");
					return callcmd::togauto(playerid, "");
				}
				else
				{
					pData[playerid][pTogChat] = 0;	
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Automatic Upper-case first leter of chat "RED_E"disable");
					return callcmd::togauto(playerid, "");
				}
			}
			case 6:
			{
				if(pData[playerid][pTogMask] == 0)
				{
					pData[playerid][pTogMask] = 1;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Automatic Nametag masking on login has been "GREEN_E"enable");
					return callcmd::togauto(playerid, "");
				}
				else
				{
					pData[playerid][pTogMask] = 0;	
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Automatic Nametag masking on login has been "RED_E"disable");
					return callcmd::togauto(playerid, "");
				}
			}
			case 7:
			{
				if(pData[playerid][pTogAmmo] == 0)
				{
					pData[playerid][pTogAmmo] = 1;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Toggle TD Ammo has been "GREEN_E"enable");
					return callcmd::togauto(playerid, "");
				}
				else
				{
					pData[playerid][pTogAmmo] = 0;	
					SendClientMessageEx(playerid, COLOR_ARWIN, "SETTING: "WHITE_E"Toggle TD Ammo has been "RED_E"disable");
					return callcmd::togauto(playerid, "");
				}
			}
		}
	}
    return 1;
}

Dialog:DialogHelp(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				new string[1256];
				format(string, sizeof(string), "\nRoleplay (RP)\tatau bermain peran adalah, adalah aktifitas dimana seorang meniru atau memainkan peran seperti orang lain\nPlayer / Pemain\tadalah manusia asli yang mengendalikan character untuk bermain peran di game ini\nCharacter\tadalah sebuah istilah yang mengacu kepada hal atau informasi yang berhubungan dengan atau diketahui Character\nOut Of Character (OOC)\tadalah istiah yang mengacu kepada hal atau informasi yang berhubungan dengan atau diketahui Player/Pemain\nMetagaming (MG)\tTindakan dimana Player/Pemain memanfaatkan atau menggunakan informasi OOC demi keuntungan Character yang ia mainkan\nPowergaming (PG)\tSuatu tindkan yang dilakukan oleh Character yang tidak bisa atau mustahil jika dilakukan di dunia nyata\nMixxing\tMenyalahgunakan atau mencampurkan chat yang seharusnya digunakan untuk IC untuk keperluan OOC atau sebaliknya\nDeathmatch (DM)\tMenyakiti atau membunuh Character pemain lain tanpa ada alasan atau tujuan yang jelas\nPlayer Kill (PK)\tSituasi dimana character mati Dibunuh oleh Character lain, pemain masih bisa memainkan characternya kembali setelah respawn\nCharacter Kill (CK)\tSituai dimana Character mati total dan pemain tidak bisa bermain sebagai characternya kembali");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Apa itu Roleplay?", string, "Close", "", "");
			}
			case 1:
			{
				new string[1256];
				format(string, sizeof(string), "\n/stats\tMenampilkan informasi character yang kamu sedang mainkan\n/report [id pemain] [text laporan]\tMengirim laporan kepada admin terhadap pemain yang melanggar peraturan\n/ask [pertanyaan]\tMenanyakan pertanyaan seputar server kepada staff yang online\n/stuck\tMeminta bantuan dari staff yang online saat character kamu nyngkut atau bugged\n/me [tindakan]\tMenjelaskan tindakan/aksi yang dilakukan oleh character kamu di chat\n/do [deskripsi]\tMendeskripsikan suatu benda atau suasana sekitar\n/ame [action]\tsama seperti command '/me', hanya muncul di atas kepala character sesaat\n/ado [action]\tsama seperti command '/do', bisa menempel di tempat atau di kendaraan\n/delado\tMenghapus text yang dibuat dengan '/ado'\n/helth\tMemeriksa kondisi dan kesehatan tubuh character kamu\n/inspect\tMemeriksa kondisi dan kesehatan tubuh character milik pemain lain\n/map\tMenampilkan menu yang berisi lokasi-lokasi penting\n/admins\tMenampilkan nama-nama staff yang sedang online dan bertugas\n/mywarns\tMenampilkan peringatan/warnings yang perndiberikan oleh Staff\n/togauto\tMengatur feature otomatis yang bisa dimanfaatkan\n/toggle\tMematikan atau memunculkan pesan pesan yang ada di ingame\n/hudmode\tMengatur hudmode kamu yang bisa di show/hide");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Basic Commands", string, "Close", "", "");
			}			
			case 2:
			{
				new string[1256];
				format(string, sizeof(string), "\n/l\tUntuk berbicara dengan jarak yang dekat\n/c\tUntuk berbicara ketika character sedang di dalam kendaraan\n/s\tUntuk berteriak\n/pm [playerid]\tDigunakan sebagai Private Message tetapi bersifat OOC\n/whisper [playerid]\tDigunakan untuk berbisik kepada player yang di targetkan\n/o\tDigunakan untuk global chat bersifat OOC\n/me\tDigunakan untuk memberi roleplay apa yang dilakukan character\n/ame\tDigunakan untuk memberi roleplay apa yang dilakukan character dengan jarak yang dekat\n/do\tDigunakan untuk menggambarkan sesuatu terhadap\n/ado\tMendeskripsikan keadaan sekitar yang dapat menetap di suatu tempat atau kendaraan");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Chat", string, "Close", "", "");
			}
			case 3:
			{
				new string[1256];
				format(string, sizeof(string), "\n/pay [playerid/name] [amount]\tMemberikan uang kepada character lain\n/mysalary\tMenampilkan semua gaji atau upah dari sidejob atau job\n/atm\tDigunakan untuk mengoperasikan mesin atm\nBank\tAdalah tempat dimana character kamu bisa mengambil, menarik dan meng-transfer uang ke character lain\n/mybank\tMenampilkan nomor rekening bank milik kamu\n/withdraw [amount]\tMenarik uang yang tersimpan di bank\n/deposit [amount]\tMenyimpan uang ke dalam bank\n/transfer [bank] [amount]\tMentransfer uang ke characte lain\n/bank\tMelihat balance dan sign paycheck di bank");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Money & Banking", string, "Close", "", "");
			}
			case 4:
			{
				new string[1256];
				format(string, sizeof(string), "\n/mv\tMenampilkan semua kendaraan milik player\n/engine\tMenyalakan atau mematikan mesin kendaraan yang di kendarai character\n/lock | /nlock\tMengunci atau membuka kendaraan yang kamu miliki\n/toglight\tMenylakan atau mematikan lampu yang dikendarai character\n/trunk\tMengakses garasi kendaraan yang kamu miliki\n/hood\tMembuka atau menutup kap mesin kendaraan kamu\n/limitspeed\tMembatasi laju kendaraan yang dikendarai character\n/rentveh\tMenyewa kendaraan untuk character kamu dari tempat penyewaan kendaraan\n/unrentveh\tMengembalikan kendaraan sewaan balik ke tempat penyewaan\n/fill\tMengisi bensin ke kendaraan yang di kendarai character di pom bensin\n/fillveh\tMengisi bensin ke kendaraan yang dekat dari jerigen bensin\n/eject\tMengeluarkan paksa penumpang dari kendaraan yang dikendarai character\n/belt\tMemakai atau melepas sabuk pengaman ke character kami saat di dalam kendaraan\n/buyinsurance\tMembeli insurance kendaraan di tempat insurance\n/claiminsurance\tMengambil knndaraan yang ada di gedung insurance\n/vradio\tMenyetel stasiun radio internet di dalam kendaraan yang sedang di kendarai");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Vehicle Help", string, "Close", "", "");
			}
			case 5:
			{
				Dialog_Show(playerid, DialogJobHelp, DIALOG_STYLE_LIST, "Jobs", "{00FFFF}Jobs: "WHITE_E"Taxi Drivers\n{00FFFF}Jobs: "WHITE_E"Mechanic\n{00FFFF}Jobs: "WHITE_E"Lumber Jack\n{00FFFF}Jobs: "WHITE_E"Trucker\n{00FFFF}Jobs: "WHITE_E"Farmer\n{00FFFF}Jobs: "WHITE_E"Builder\n"YELLOW_E"Sidejobs: "WHITE_E"TrashMaster\n"YELLOW_E"Sidejobs: "WHITE_E"Forklift\n"RED_E"IlegalJobs: "WHITE_E"Arms Dealer\n"RED_E"IlegalJobs: "WHITE_E"Drugs Dealer\n"RED_E"IlegalJobs: "WHITE_E"Smuggle", "Select", "Close");
				return 1;
			}
			case 6:
			{
				return callcmd::factionhelp(playerid);
			}
			case 7:
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Family Commands", "/fsafe /finvite /funinvite /fsetrank /finfo",  "", "Close");
			}
			case 8:
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Bisnis Commands", "/buy /bm /lockbisnis /unlockbisnis /bwithdraw /bdeposit",  "", "Close");
			}
			case 9:
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Furniture Store Help", "/buyfurnstore /fsm /buyfurniture",  "", "Close");
			}
			case 10:
			{
				Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "House Commands", "/buyhouse /lockhouse /myhouse /findhouse",  "", "Close");
			}
			case 11:
			{
				Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Flat Apartments Help", "/buyflat /flock /flatmenu",  "", "Close");
			}
			case 12:
			{
				Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Workshop Commands", "/buy /dcw(untuk deposit component) /wcw (untuk withdraw component)/dmw(untuk deposit money) /wmw(untuk withdraw money) /winvite /wuninvite /winfo",  "", "Close");
			}
			case 13:
			{
				Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Farm Commands", "/buy /lainvite /lasafe /launinvite /lainfo /sellfarm /givefarm",  "", "Close");
			}
			case 14:
			{
				new string[512];
				format(string, sizeof(string), "\n/buy\tMembeli garasi untuk character kamu\n/storeveh\tMenyimpan kendaraan kedalam garasi\n/takeveh\tMengambil kendaraan dari garasi\n/givegarge\tMemberikan garasi kepada player lain");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Garage Commands", string, "Close", "", "");
			}
			case 15:
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Donatur Commands", "/usegold /radio /usegold",  "", "Close");
			}
		}
	}
    return 1;
}

Dialog:DialogJobHelp(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		switch(listitem)
		{
			case 0:
			{
				new string[256];
				format(string, sizeof(string), "\n/jobduty [taxi]\tUntuk memulai bekerja sebagi Taxi Driver\n/accept taxi [playerid]\tUntuk menerima orderan taxi dari pemain lain");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Jobs Taxi Help", string, "Close", "", "");
			}
			case 1:
			{
				new string[1024];
				format(string, sizeof(string), "\n/jobduty [mechanic]\tUntuk memulai bekerja sebagi Mechanic\n/vm\tUntuk memeriksa dan merepair kendaraan menggunakan component\n/acceptmecha\tUntuk menerima panggilan dari seseorang untuk mentowing kendaraan\n/unloadcomponent\tUntuk mengambil component dari sebuah kendaraan\n/loadcomponent\tUntuk memasukan component kedalam kendaraan\n/impounds\tUntuk mengantarkan kendaraan yang akan di antarkan ke Impound Center\n/tow\tUntuk menderek kendaraan menggunakan kendaraan tow\tUntuk melepaskan derek dari kendaraan towing");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Jobs Mechanic Help", string, "Close", "", "");
			}
			case 2:
			{
				new string[512];
				format(string, sizeof(string), "\n/unloadtimber\tUntuk menjual timber/kayu ke tempat penjualan timber\n/buychainsaw\tUntuk membeli chainsaw di Lumberjack Jobs");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Jobs LumberJack Help", string, "Close", "", "");
			}
			case 3:
			{
				new string[512];
				format(string, sizeof(string), "\n/missions\tUntuk mengambil misi truck hauling menggunakan truck trailer\n/getcrate\tUntuk Mengambil crate di sebuah pengambilan crate\n/dropcrate\tUntuk menaruh crate yang di angakt oleh character\n/unloadcrate\tUntuk mengunload create sesuai dengan type crate tersebut");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Trucker Help", string, "Close", "", "");
			}
			case 4:
			{
				new string[1024];
				format(string, sizeof(string), "\n/plant\tUntuk menampilkan opsi pada tanaman\n/buyseeds\tUntuk membeli benih tanaman dari farmer\n/unloadplant\tUntuk menjual tanaman ke tempat penjualan tanaman didalam kendaraan\n/sellallplant\tSama seperti command '/unloadplant', tetapi diluar kendaraan\n/sellberries\tUntuk menjual berrie ke tempat penjualan berries");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Farmer Help", string, "Close", "", "");
				//Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Farmer Help", "/plant /buyseeds /unloadplant /loadplant",  "Close", "", "");
			}
			case 5:
			{
				Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Builder Help", "/dyoh /flatroommenu",  "", "Close");
			}
			case 6:
			{
				Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Trashmaster Help", "/loadtrash",  "", "Close");
			}
			case 7:
			{
				Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Forklift Help", "/loadcrate /unloadcreate",  "", "Close");
			}
			case 8:
			{
				new string[1024];
				format(string, sizeof(string), "\n/buypacket\tUntuk membeli material di Black Market\n/creategun\tUntuk membuat sebuah senjata pada Blackmarket\n/creatammo\tUntuk membuat ammo senjata dengan type normal\n/creatammo [surplus]\tUntuk membuat ammo senjata ber type Surplus");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Arms Dealer Help", string, "Close", "", "");
			}
			case 9:
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Drugs Dealer Help", "/buycrack",  "", "Close");
			}
			case 10:
			{
				new string[512];
				format(string, sizeof(string), "\n/findpacket\tUntuk menemukan sebuah packet pada map anda\n/storepacket\tUntuk mengstore packet pada tempat store packet\n/getpacket\tUntuk mengambil packet yang belum di ambil pemain lain\n/pickpacket\tUntuk menaruh packet di lokasi anda");
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Smuggler Help", string, "Close", "", "");
			}
		}
	}
    return 1;
}

Dialog:DialogGps(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		switch(listitem)
        {
            case 0:
            {
                Dialog_Show(playerid, DialogGpsPublic, DIALOG_STYLE_LIST, "GPS Menu", "General\nJobs\nSidejobs", "Select", "Close");
            }
            case 1:
            {
            	Dialog_Show(playerid, DialogGpsDealership, DIALOG_STYLE_LIST, "GPS:Dealership", "Suv Dealership\nSaloons Dealership\nSports Dealership\nLowriders Dealership\nMotorcycle Dealership\nJobs Dealership\nVip Dealership", "Select", "Close");
            }
            // case 1:
            // {
            //    new msg2[512], found = false;
            //    format(msg2, sizeof(msg2), "Name\tLocation\n");
            //    foreach(new id : Dealership)
            //    {	
            //        gListedItems[playerid][found] = id;
            //        format(msg2,sizeof(msg2), "%s%s\t%0.2fm\n", msg2, CarDealershipInfo[id][cdMessage], GetPlayerDistanceFromPoint(playerid,CarDealershipInfo[id][cdEntranceX], CarDealershipInfo[id][cdEntranceY], CarDealershipInfo[id][cdEntranceZ]));
            //        found++;
            //    }
            //    Dialog_Show(playerid, DialogGpsDealer, DIALOG_STYLE_TABLIST_HEADERS,"GPS: Dealership",msg2,"Goto","Cancel");
            // }
            case 2:
            {
                new msg2[512], found = false;
                format(msg2, sizeof(msg2), "Name\tDistance\n");
                for(new id = 0; id < MAX_BISNIS; id++)
                {	
                    if(bData[id][bType] == 1)
                    {
                        gListedItems[playerid][found] = id;
                        format(msg2,sizeof(msg2), "%s%s\t%0.2fm\n", msg2, ReplaceString(bData[id][bName]), GetPlayerDistanceFromPoint(playerid, bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ]));
                        found++;
                    }
                }
                Dialog_Show(playerid, DialogGpsResto, DIALOG_STYLE_TABLIST_HEADERS,"GPS: Restaurant",msg2,"Goto","Cancel");
            }
            case 3:
            {
                new msg2[512], found = false;
                format(msg2, sizeof(msg2), "Name\tDistance\n");
                for(new id = 0; id < MAX_BISNIS; id++)
                {	
                    if(bData[id][bType] == 5)
                    {
                        gListedItems[playerid][found] = id;
                        format(msg2,sizeof(msg2), "%s%s\t%0.2fm\n", msg2, ReplaceString(bData[id][bName]), GetPlayerDistanceFromPoint(playerid, bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ]));
                        found++;
                    }
                }
                Dialog_Show(playerid, DialogGpsEle, DIALOG_STYLE_TABLIST_HEADERS,"GPS: Electronic",msg2,"Goto","Cancel");
            }
            case 4:
            {
                new msg2[512], found = false;
                format(msg2, sizeof(msg2), "Name\tDistance\n");
                for(new id = 0; id < MAX_BISNIS; id++)
                {	
                    if(bData[id][bType] == 4)
                    {
                        gListedItems[playerid][found] = id;
                        format(msg2,sizeof(msg2), "%s%s\t%0.2fm\n", msg2, ReplaceString(bData[id][bName]), GetPlayerDistanceFromPoint(playerid, bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ]));
                        found++;
                    }
                }
                Dialog_Show(playerid, DialogGpsSport, DIALOG_STYLE_TABLIST_HEADERS,"GPS: Sports Store",msg2,"Goto","Cancel");
            }
            case 5:
            {
                new msg2[512], found = false;
                format(msg2, sizeof(msg2), "Name\tDistance\n");
                for(new id = 0; id < MAX_BISNIS; id++)
                {	
                    if(bData[id][bType] == 2)
                    {
                        gListedItems[playerid][found] = id;
                        format(msg2,sizeof(msg2), "%s%s\t%0.2fm\n", msg2, ReplaceString(bData[id][bName]), GetPlayerDistanceFromPoint(playerid, bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ]));
                        found++;
                    }
                }
                Dialog_Show(playerid, DialogGpsMarket, DIALOG_STYLE_TABLIST_HEADERS,"GPS: Supermarket",msg2,"Goto","Cancel");
            }
            case 6:
            {
                new msg2[512], found = false;
                format(msg2, sizeof(msg2), "Name\tDistance\n");
                for(new id = 0; id < MAX_BISNIS; id++)
                {	
                    if(bData[id][bType] == 3)
                    {
                        gListedItems[playerid][found] = id;
                        format(msg2,sizeof(msg2), "%s%s\t%0.2fm\n", msg2, ReplaceString(bData[id][bName]), GetPlayerDistanceFromPoint(playerid, bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ]));
                        found++;
                    }
                }
                Dialog_Show(playerid, DialogGpsClothes, DIALOG_STYLE_TABLIST_HEADERS,"GPS: Clothes",msg2,"Goto","Cancel");
            }
            case 7:
            {
                new msg2[512], found = false;
                format(msg2, sizeof(msg2), "Name\tDistance\n");
                foreach(new id : GStation)
                {
                    gListedItems[playerid][found] = id;
                    format(msg2,sizeof(msg2), "%s%s\t%0.2fm\n", msg2, GetLocation(gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ]), GetPlayerDistanceFromPoint(playerid, gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ]));
                    found++;
                }
                Dialog_Show(playerid, DialogGpsGas, DIALOG_STYLE_TABLIST_HEADERS,"GPS: Gas Station",msg2,"Goto","Cancel");
            }
            case 8:
            {
                new msg2[512], found = false;
                format(msg2, sizeof(msg2), "Name\tType\tDistance\n");
                foreach(new wsid : Workshop)
                {
                    gListedItems[playerid][found] = wsid;
                    format(msg2,sizeof(msg2), "%s%s Workshop\t%s\t%0.2fm\n", msg2, GetLocation(WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]), GetTypeWorkshop(wsid), GetPlayerDistanceFromPoint(playerid, WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]));
                    found++;
                }
                Dialog_Show(playerid, DialogGpsWs, DIALOG_STYLE_TABLIST_HEADERS,"GPS: Workshop",msg2,"Goto","Cancel");
            }
			case 9:
            {
                new msg2[512], found = false;
                format(msg2, sizeof(msg2), "Name\tDistance\n");
                foreach(new fsid : FurnStore)
                {
                    gListedItems[playerid][found] = fsid;
                    format(msg2, sizeof(msg2), "%s%s\t%0.2fm\n", msg2, storeData[fsid][storeName], GetPlayerDistanceFromPoint(playerid, storeData[fsid][storePos][0], storeData[fsid][storePos][1], storeData[fsid][storePos][2]));
                    found++;
                }
                Dialog_Show(playerid, DialogGpsFurn, DIALOG_STYLE_TABLIST_HEADERS, "GPS: Furniture Store", msg2, "Goto", "Cancel");
            }
			case 10:
            {
				Dialog_Show(playerid, DialogAddresSearch, DIALOG_STYLE_INPUT,"Search Addres","input the addres you wish to search: "YELLOW_E"(min 3 latter)","Seach","Back");
            }
            case 11:
            {
                new found = 0, msg2[512];
				new
					Float:fX,
					Float:fY,
					Float:fZ;
				format(msg2, sizeof(msg2), "Vehicle\tLocation\n");
				foreach(new i : PVehicles) {
					if(pvData[i][cOwner] == pData[playerid][pID] && pvData[i][cClaim] == 0 && pvData[i][cImpound] == 0 && pvData[i][cVehicleGarage] == -1)
					{
						GetVehiclePos(pvData[i][cVeh], fX, fY, fZ);
						gListedItems[playerid][found] = i;
						found++;
						format(msg2, sizeof(msg2), "%s{00FFFF}%s\t%s\n", msg2, GetVehicleModelName(pvData[i][cModel]), GetLocation(fX, fY, fZ));
					}
				}
				if(found) Dialog_Show(playerid, TrackCar, DIALOG_STYLE_TABLIST_HEADERS, "Location Vehicle", msg2, "Track", "Close");
            }
        }
	}
    return 1;
}

Dialog:TrackCar(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new carid = gListedItems[playerid][listitem];
		new Float:x, Float:y, Float:z;
		GetVehiclePos(pvData[carid][cVeh], x, y, z);
		SetPlayerGPS(playerid, x, y, z);
		SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: "WHITE_E"Vehicle Checkpoint targeted! (%s)", GetLocation(x, y, z));
	}
    return 1;
}

Dialog:DialogAddresSearch(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
		new string[512], found = 0, str[512];
		format(string, sizeof(string), "Type\tAddres\n");
		foreach(new hid : Houses) {
			if(strfind(hData[hid][hAddress], inputtext, true) != -1) {
				gListedItems[playerid][found] = hid;
				found++;
				format(string, sizeof(string), "%s"AQUA_E"House\t"GREEN_E"%s\n", string, hData[hid][hAddress]);
			}
			if(!string[0]) Error(playerid, "No results found.");
			else Dialog_Show(playerid, AddresSearch, DIALOG_STYLE_TABLIST_HEADERS, "Addres Search", string, "Select", "Close");
		}
		foreach(new flatid : Flat) {
			if(strfind(FlatData[flatid][flatName], inputtext, true) != -1) {
				gListedItems[playerid][found] = flatid;
				found++;
				format(str, sizeof(str), "%s"AQUA_E"Flat\t"GREEN_E"%s\n", str, FlatData[flatid][flatName]);
			}
			if(!str[0]) Error(playerid, "No results found.");
			else Dialog_Show(playerid, AddresSearchFlat, DIALOG_STYLE_TABLIST_HEADERS, "Addres Search", str, "Select", "Close");
		}
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:AddresSearch(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        new id = gListedItems[playerid][listitem];
		SetPlayerGPS(playerid, hData[id][hExtposX], hData[id][hExtposY], hData[id][hExtposZ]);
        SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: "WHITE_E"House Checkpoint targeted! (%s)", GetLocation(hData[id][hExtposX], hData[id][hExtposY], hData[id][hExtposZ]));
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:AddresSearchFlat(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        new flatid = gListedItems[playerid][listitem];
		SetPlayerGPS(playerid, FlatData[flatid][flatPos][0], FlatData[flatid][flatPos][1], FlatData[flatid][flatPos][2]);
        SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: "WHITE_E"Flat Checkpoint targeted! (%s)", GetLocation(FlatData[flatid][flatPos][0], FlatData[flatid][flatPos][1], FlatData[flatid][flatPos][2]));
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsWs(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        new wsid = gListedItems[playerid][listitem];
		SetPlayerGPS(playerid, WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]);
        SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: "WHITE_E"Workshop Checkpoint targeted! (%s)", GetLocation(WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2]));
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsFurn(playerid, response, listitem, inputtext[]) {
    if(response)
	{
        new fsid = gListedItems[playerid][listitem];
		SetPlayerGPS(playerid, storeData[fsid][storePos][0], storeData[fsid][storePos][1], storeData[fsid][storePos][2]);
        SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: "WHITE_E"Furniture Store Checkpoint targeted! (%s)", GetLocation(storeData[fsid][storePos][0], storeData[fsid][storePos][1], storeData[fsid][storePos][2]));
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsGas(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        new gsid = gListedItems[playerid][listitem];
		SetPlayerGPS(playerid, gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ]);
        SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: "WHITE_E"Gas Station Checkpoint targeted! (%s)", GetLocation(gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ]));
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsClothes(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        new bid = gListedItems[playerid][listitem];
		SetPlayerGPS(playerid, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]);
       	SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: "WHITE_E"Bisnis Checkpoint targeted! (%s)", GetLocation(bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]));
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsMarket(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        new bid = gListedItems[playerid][listitem];
		SetPlayerGPS(playerid, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]);
        SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: "WHITE_E"Bisnis Checkpoint targeted! (%s)", GetLocation(bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]));
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsSport(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        new bid = gListedItems[playerid][listitem];

        SetPlayerGPS(playerid, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]);
        SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: "WHITE_E"Bisnis Checkpoint targeted! "YELLOW_E"(%s)", GetLocation(bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]));
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsEle(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        new bid = gListedItems[playerid][listitem];

        SetPlayerGPS(playerid, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]);
        SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: "WHITE_E"Bisnis Checkpoint targeted! "YELLOW_E"(%s)", GetLocation(bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]));
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsResto(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        new bid = gListedItems[playerid][listitem];

        SetPlayerGPS(playerid, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]);
        SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: "WHITE_E"Bisnis Checkpoint targeted! "YELLOW_E"(%s)", GetLocation(bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]));
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsDealer(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        new dealershipid = gListedItems[playerid][listitem];
		SetPlayerGPS(playerid, CarDealershipInfo[dealershipid][cdEntranceX], CarDealershipInfo[dealershipid][cdEntranceY], CarDealershipInfo[dealershipid][cdEntranceZ]);
        SendClientMessageEx(playerid, COLOR_ARWIN, "GPS: "WHITE_E"Dealership Checkpoint targeted! (%s)", GetLocation(CarDealershipInfo[dealershipid][cdEntranceX], CarDealershipInfo[dealershipid][cdEntranceY], CarDealershipInfo[dealershipid][cdEntranceZ]));
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsPublic(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        switch(listitem)
        {
            case 0:
            {
                Dialog_Show(playerid, DialogGpsGeneral, DIALOG_STYLE_LIST, "GPS Menu", "Bank Los Santos\nDriving School\nMechanic City\nMechanic Dessert\nComponent Factory\nLos Santos Fish Factory\nLas Barrancas Fish Factory\nLos Santos Impound Center\nCity Hall\nModshop\nBoat Repair\nInsurance Company", "Select", "Close");
            }
            case 1:
            {
                Dialog_Show(playerid, DialogGpsJobs, DIALOG_STYLE_LIST, "GPS JOB", "Taxi\nMechanic\nLumber Jack\nTrucker\nFarmer", "Select", "Close");
            }
            case 2:
            {
                Dialog_Show(playerid, DialogGpsSideJobs, DIALOG_STYLE_LIST, "GPS JOB", "Sidejob: Sweeper\nSidejob: Bus [A/B]\nSidejob: Bus [C/D]\nSidejob: TrashMaster\nSidejob: Forklift\nSidejob: Courier\nSidejob: Miner\nActivity: Fishing", "Select", "Close");
            }
        }
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsSideJobs(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        switch(listitem)
        {
            case 0:
            {
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
                SetPlayerGPS(playerid, 1625.3225, -1892.8766, 13.5503);
            }
            case 1:
            {
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
                SetPlayerGPS(playerid, 1697.1055,-1530.4958,13.3828);
            }
            case 2:
            {
                SetPlayerGPS(playerid, 1794.7983, -1930.6672, 13.3874); //Bus
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
                
            }
            case 3:
            {
                SetPlayerGPS(playerid, 2107.8608, -2059.4216, 13.5544); //TrashMaster
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
                
            }
            case 4:
            {
                SetPlayerGPS(playerid, 2742.4250, -2420.9465, 13.6463); //Forklift
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
                
            }
			case 5:
            {
                SetPlayerGPS(playerid, 1779.0067, -1694.7094, 13.4662); //Fish
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
                
            }
            case 6:
            {
                SetPlayerGPS(playerid, 496.09, 782.30, -21.88); //Miner
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
                
            }
            case 7:
            {
                SetPlayerGPS(playerid, 361.2099,-2032.1703,7.8359);  //Fish
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
                
            }
        }
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsJobs(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        switch(listitem)
        {
            case 0:
            {
                SetPlayerGPS(playerid, 1685.4528,-1464.4073,13.5469); //Taxi
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 1:
            {
                SetPlayerGPS(playerid, 1809.17, -2064.89, 13.55); //Mechanic
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 2:
            {
                SetPlayerGPS(playerid, -1438.4968,-1544.1377,101.7578); //Lumber
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
                
            }
            case 3:
            {
                SetPlayerGPS(playerid, -77.1687,-1136.5388,1.0781); //Trucker
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 4:
            {
                SetPlayerGPS(playerid, -382.7033,-1438.9998,26.1691); //Farmer
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
        }
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsDealership(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        switch(listitem)
        {
            case 0:
            {
                SetPlayerGPS(playerid, 2131.7900,-1151.1900,24.0600);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 1:
            {
                SetPlayerGPS(playerid, 2357.6700,-1990.5500,13.5400);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 2:
            {
                SetPlayerGPS(playerid, 2281.3900, -2364.770, 13.5500);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 3:
            {
                SetPlayerGPS(playerid, 1083.1200, -1226.7700,  15.8200);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 4:
            {
                SetPlayerGPS(playerid, 1359.7000, -1854.4200, 13.5700);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 5:
            {
                SetPlayerGPS(playerid, -265.70, -2213.12, 29.04);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 6:
            {
                SetPlayerGPS(playerid, 563.7400, -1291.4600, 17.2400);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
        }
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:DialogGpsGeneral(playerid, response, listitem, inputtext[]) {
    if(response) 
	{
        switch(listitem)
        {
            case 0:
            {
                SetPlayerGPS(playerid, 1462.2328,-1021.0492,24.1048);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 1:
            {
                SetPlayerGPS(playerid, 2059.1587,-1912.5458,13.5469);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 2:
            {
                SetPlayerGPS(playerid, 1791.99, -2062.14, 13.57);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 3:
            {
                SetPlayerGPS(playerid, -243.7400,1216.4500,19.4400);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 4:
            {
                SetPlayerGPS(playerid, 323.6411, 904.5583, 21.5862);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 5:
            {
                SetPlayerGPS(playerid, 2836.3945,-1541.1984,11.0991);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 6:
            {
                SetPlayerGPS(playerid, -746.33, 1639.18, 27.36);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 7:
            {
                SetPlayerGPS(playerid, 1579.75, -1631.52, 13.38);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 8:
            {
                SetPlayerGPS(playerid, 1479.78, -1738.69, 13.54);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 9:
            {
                SetPlayerGPS(playerid, 1799.74, -2039.48, 13.53);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 10:
            {
                SetPlayerGPS(playerid, 2615.8027,-2473.2822,3.1963);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
            case 11:
            {
                SetPlayerGPS(playerid, 1070.60, -1766.85, 13.36);
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"GPS active! follow the checkpoint.");
            }
        }
    }
    else return Dialog_Show(playerid, DialogGps, DIALOG_STYLE_LIST, "GPS Menu", "Public Location\nDealership\nRestaurants\nElectronic Store\nSports Store\nSupermarket\nClothes Store\nGas Station\nWorkshop\nFurniture Store\nAddres Search\nMy Vehicle", "Select", "Close");
    return 1;
}

Dialog:StreamerSettings(playerid, response, listitem, inputtext[]) {
    if (response) {
        pData[playerid][pStreamer] = listitem;
        SetPlayerStreamerSettings(playerid);
        SendCustomMessage(playerid, "STREAMER", "Streamer settings saved!");
    }
    return 1;
}

Dialog:DialogComponent(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new amount = floatround(strval(inputtext));
        new total = pData[playerid][pComponent] + amount;
        new vehicleid = GetPlayerVehicleID(playerid), strings[212];
        new total1 = pvData[vehicleid][cComponent] + amount;
        new value = amount * 50;
        if(amount < 0 || amount > 1000) return Error(playerid, "amount maximal 0 - 1000");
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            if(total1 > 1000) return Error(playerid, "Component too full in your inventory! Maximal 1000");
            if(GetPlayerMoney(playerid) < value) return Error(playerid, "Uang anda kurang.");
            if(StockComponent < amount) return Error(playerid, "Component stock tidak mencukupi.");
            // foreach(new wid : WORKSHOPS)
            // {
            //     if(wData[wid][wVehicle] == vehicleid)
            //     {
            //         GivePlayerMoneyEx(playerid, -value);
            //         wData[wid][wVehicleComponent] += amount;
            //         StockComponent -= amount;
            //         Server_AddMoney(value);
            //         ComponentStockRefresh();
            //         SendClientMessageEx(playerid, COLOR_ARWIN, "COMPONENT: "WHITE_E"You successfully purchased "YELLOW_E"%d Component"WHITE_E" for "GREEN_E"$%s "WHITE_E"amount stored: "YELLOW_E"%d", amount, FormatMoney(value), wData[wid][wVehicleComponent]);
            //         if(IsValidDynamicObject(ObjectVehicle[wData[wid][wVehicle]][0]))
            //         {
            //             DestroyDynamicObject(ObjectVehicle[wData[wid][wVehicle]][0]);
            //         }
            //         if(GetVehicleModel(wData[wid][wVehicle]) == 525)
            //         {
            //             ObjectVehicle[wData[wid][wVehicle]][0] = CreateDynamicObject(964,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            //             AttachDynamicObjectToVehicle(ObjectVehicle[wData[wid][wVehicle]][0], wData[wid][wVehicle], 0.000, -1.000, 0.190, 0.000, 0.000, 0.000);
            //         }
            //     }
            // }
            foreach(new pv : PVehicles)
            {
                if(vehicleid == pvData[pv][cVeh])
                {
                    GivePlayerMoneyEx(playerid, -value);
                    pvData[vehicleid][cComponent] += amount;
                    StockComponent -= amount;
                    Server_AddMoney(value);
                    ComponentStockRefresh();
                    SendClientMessageEx(playerid, COLOR_ARWIN, "COMPONENT: "WHITE_E"You successfully purchased "YELLOW_E"%d Component"WHITE_E" for "GREEN_E"$%s "WHITE_E"amount stored: "YELLOW_E"%d", amount, FormatMoney(value), pvData[vehicleid][cComponent]);
                    if(IsValidDynamicObject(ObjectVehicle[pvData[pv][cVeh]][0]))
                    {
                        DestroyDynamicObject(ObjectVehicle[pvData[pv][cVeh]][0]);
                    }

                    if(GetVehicleModel(pvData[pv][cVeh]) == 422)
                    {
                        ObjectVehicle[pvData[pv][cVeh]][0] = CreateDynamicObject(964,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                        AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][0], pvData[pv][cVeh], 0.000, -1.370, -0.320, 0.000, 0.000, 0.000);
                    }
                    else if(GetVehicleModel(pvData[pv][cVeh]) == 543)
                    {
                        ObjectVehicle[pvData[pv][cVeh]][0] = CreateDynamicObject(964,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                        AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][0], pvData[pv][cVeh], 0.000, -1.521, -0.250, 0.000, 0.000, 0.000);
                    }	
                    else if(GetVehicleModel(pvData[pv][cVeh]) == 525)
                    {
                        ObjectVehicle[pvData[pv][cVeh]][0] = CreateDynamicObject(964,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                        AttachDynamicObjectToVehicle(ObjectVehicle[pvData[pv][cVeh]][0], pvData[pv][cVeh], 0.000, -1.000, 0.190, 0.000, 0.000, 0.000);
                    }
                    format(strings, sizeof(strings), "{00FFFF}Component Factory\n"WHITE_E"Price: "GREEN_E"$0.50 "WHITE_E"/ unit\n"WHITE_E"Stock: "GREEN_E"%d "YELLOW_E"/ 50000\n"WHITE_E"Use '"YELLOW_E"/buycomponent"WHITE_E"' to buy components", StockComponent);
                    UpdateDynamic3DTextLabelText(Compo2, COLOR_ARWIN, strings);
                }
            }
        }
        else
        {
            if(total > 250) return Error(playerid, "Component too full in your inventory! Maximal 250");
            if(GetPlayerMoney(playerid) < value) return Error(playerid, "Uang anda kurang.");
            if(StockComponent < amount) return Error(playerid, "Component stock tidak mencukupi.");
            GivePlayerMoneyEx(playerid, -value);
            pData[playerid][pComponent] += amount;
            StockComponent -= amount;
            Server_AddMoney(value);
            ComponentStockRefresh();
            SendClientMessageEx(playerid, COLOR_ARWIN, "COMPONENT: "WHITE_E"Anda berhasil membeli "GREEN_E"%d "WHITE_E"component seharga "RED_E"$%s.", amount, FormatMoney(value));
            format(strings, sizeof(strings), "{00FFFF}Component Factory\n"WHITE_E"Price: "GREEN_E"$0.50 "WHITE_E"/ unit\n"WHITE_E"Stock: "GREEN_E"%d "YELLOW_E"/ 50000\n"WHITE_E"Use '"YELLOW_E"/buycomponent"WHITE_E"' to buy components", StockComponent);
            UpdateDynamic3DTextLabelText(Compo2, COLOR_ARWIN, strings);
        }
    }
    return 1;
}

Dialog:BussinesINT(playerid, response, listitem, inputtext[]) {
    if (response) {
        if(listitem == 0) // 24/7
		{
			Dialog_Show(playerid, BussinesINT1, DIALOG_STYLE_LIST, "24/7's", "24/7 Interior 1 \n24/7 Interior 2 \n24/7 Interior 3 \n24/7 Interior 4 \n24/7 Interior 5 \n24/7 Interior 6 \nBack", "Select", "Cancel");
		}
		if(listitem == 1) // Fast Foods
		{
			Dialog_Show(playerid, BussinesINT2, DIALOG_STYLE_LIST, "Fast Foods Interiors", "Burger Shot \nWell Stacked Pizza \nCluckin' Bell \nRusty Donut's\nBack", "Select", "Cancel");
		}
		if(listitem == 2) // Resturants & Clubs
		{
			Dialog_Show(playerid, BussinesINT3, DIALOG_STYLE_LIST, "Resturants & Clubs","Bar \nDinner \nWorld Of Coq \nThe Pig Pen \nClub \nJay's Diner\nFanny Batter's Whore House\nCustom Resturant [Decent]\nCustom Bar Interior\nBack", "Select", "Cancel");
		}
	 	if(listitem == 3) // Ammunations
		{
			Dialog_Show(playerid, BussinesINT4, DIALOG_STYLE_LIST, "Ammunation Interiors", "Ammunation 1 \nAmmunation 2 \nAmmunation 3 \nAmmunation 4 \nAmmunation 5 \nBack", "Select", "Cancel");
		}
  		if(listitem == 4) // Casino Interiors
		{
			Dialog_Show(playerid, BussinesINT5, DIALOG_STYLE_LIST, "Casino Interiors", "Four Dragons Casino\nBig Spread Ranch\nStrip Club\nBack", "Select", "Cancel");
		}
		if(listitem == 5) //  Electronics
		{
			Dialog_Show(playerid, BussinesINT6, DIALOG_STYLE_LIST, "Electronic Stores Interiors", "Electronic Store\nZero RC Shop\nBack", "Select", "Cancel");
		}
		if(listitem == 6) //  Clothes
		{
			Dialog_Show(playerid, BussinesINT7, DIALOG_STYLE_LIST, "Clothes Interiors", "Binco\nDidier sachs\nProlaps\nSuburban\nVictim\nZip", "Select", "Cancel");
		}
    }
    return 1;
}

Dialog:BussinesINT1(playerid, response, listitem, inputtext[]) {
    if (response) {
        if(listitem == 0) // 24/7 1
		{
			SetPlayerPos(playerid,-25.884499,-185.868988,1003.549988);
			SetPlayerInterior(playerid,17);
		}
		if(listitem == 1) // 24/7 2
		{
			SetPlayerPos(playerid,-6.091180,-29.271898,1003.549988);
			SetPlayerInterior(playerid,10);
		}
		if(listitem == 2) //  24/7 3
		{
			SetPlayerPos(playerid,-30.946699,-89.609596,1003.549988);
			SetPlayerInterior(playerid,18);
		}
		if(listitem == 3) //  24/7 4
		{
			SetPlayerPos(playerid,-25.132599,-139.066986,1003.549988);
			SetPlayerInterior(playerid,16);
		}
		if(listitem == 4) //  24/7 5
		{
			SetPlayerPos(playerid,-27.312300,-29.277599,1003.549988);
			SetPlayerInterior(playerid,4);
		}
		if(listitem == 5) // 24/7 6
		{
			SetPlayerPos(playerid,-26.691599,-55.714897,1003.549988);
			SetPlayerInterior(playerid,6);
		}
		if(listitem == 6) // Back
		{
			Dialog_Show(playerid, BussinesINT, DIALOG_STYLE_LIST, "Businesses interiors categories","24/7's\nFast Foods Interiors\nResturants & Clubs\nAmmunation Interiors\nCasino Interiors\nElectronics Store\nClothes Shops Interiors\nUsefull Random Interiors", "Select", "Cancel");
		}
    }
    return 1;
}

Dialog:BussinesINT2(playerid, response, listitem, inputtext[]) {
    if (response) {
        if(listitem == 0) // Burger Shot
		{
			SetPlayerPos(playerid,365.4099,-73.6167,1001.5078);
			SetPlayerInterior(playerid,10);
		}
		if(listitem == 1) // Well Stacked
		{
			SetPlayerPos(playerid,372.3520,-131.6510,1001.4922);
			SetPlayerInterior(playerid,5);
		}
		if(listitem == 2) // Cluckin Bell
		{
			SetPlayerPos(playerid,365.7158,-9.8873,1001.8516);
			SetPlayerInterior(playerid,9);
		}
		if(listitem == 3) // Rusty Donut's
		{
			SetPlayerPos(playerid,378.026,-190.5155,1000.6328);
			SetPlayerInterior(playerid,17);
		}
		if(listitem == 4) // Back
		{
			Dialog_Show(playerid, BussinesINT, DIALOG_STYLE_LIST, "Businesses interiors categories","24/7's\nFast Foods Interiors\nResturants & Clubs\nAmmunation Interiors\nCasino Interiors\nElectronics Store\nClothes Shops Interiors\nUsefull Random Interiors", "Select", "Cancel");
		}
    }
    return 1;
}

Dialog:BussinesINT3(playerid, response, listitem, inputtext[]) {
    if (response) {
        if(listitem == 0) // Big Spread Ranch
		{
			SetPlayerPos(playerid,501.980987,-69.150199,998.757812);
			SetPlayerInterior(playerid,11);
		}
		if(listitem == 1) // Dinner
		{
			SetPlayerPos(playerid,454.9853, -107.2548, 999.4376);
			SetPlayerInterior(playerid,5);
		}
		if(listitem == 2) // World Of Coq
		{
			SetPlayerPos(playerid,445.6003, -6.9823, 1000.7344);
			SetPlayerInterior(playerid,1);
		}
		if(listitem == 3) // The Pig Pen
		{
			SetPlayerPos(playerid,1204.9326,-8.1650,1000.9219);
			SetPlayerInterior(playerid,2);
		}
		if(listitem == 4) // Dance Club
		{
			SetPlayerPos(playerid,490.2701,-18.4260,1000.6797);
			SetPlayerInterior(playerid,17);
		}
		if(listitem == 5) // Jay's Dinner
		{
			SetPlayerPos(playerid,449.0172, -88.9894, 999.5547);
			SetPlayerInterior(playerid,4);
		}
		if(listitem == 6) // Fanny Batter's Whore House
		{
			SetPlayerPos(playerid,748.4623, 1438.2378, 1102.9531);
			SetPlayerInterior(playerid,6);
		}
		if(listitem == 7) // Decent Resturant interior
		{
			SetPlayerPos(playerid,1518.6910,-1566.9099,13.7989);
			SetPlayerInterior(playerid,0);
		}
		if(listitem == 8) // Custom Bar interior
		{
			SetPlayerPos(playerid,-159.7749,1765.2834,-99.7741);
			SetPlayerInterior(playerid,0);
		}
		if(listitem == 9) // Back
		{
			Dialog_Show(playerid, BussinesINT, DIALOG_STYLE_LIST, "Businesses interiors categories","24/7's\nFast Foods Interiors\nResturants & Clubs\nAmmunation Interiors\nCasino Interiors\nElectronics Store\nClothes Shops Interiors\nUsefull Random Interiors", "Select", "Cancel");
		}
    }
    return 1;
}

Dialog:BussinesINT4(playerid, response, listitem, inputtext[]) {
    if (response) {
        if(listitem == 0) // Ammunation 1
		{
			SetPlayerPos(playerid,286.148987,-40.644398,1001.569946);
			SetPlayerInterior(playerid,1);
		}
		if(listitem == 1) // Ammunation 2
		{
			SetPlayerPos(playerid,286.800995,-82.547600,1001.539978);
			SetPlayerInterior(playerid,4);
		}
		if(listitem == 2) // Ammunation 3
		{
			SetPlayerPos(playerid,296.919983,-108.071999,1001.569946);
			SetPlayerInterior(playerid,6);
		}
		if(listitem == 3) // Ammunation 4
		{
			SetPlayerPos(playerid,314.820984,-141.431992,999.661987);
			SetPlayerInterior(playerid,7);
		}
		if(listitem == 4) // Ammunation 5
		{
			SetPlayerPos(playerid,316.524994,-167.706985,999.661987);
			SetPlayerInterior(playerid,6);
		}
		if(listitem == 5) // Back
		{
			Dialog_Show(playerid, BussinesINT, DIALOG_STYLE_LIST, "Businesses interiors categories","24/7's\nFast Foods Interiors\nResturants & Clubs\nAmmunation Interiors\nCasino Interiors\nElectronics Store\nClothes Shops Interiors\nUsefull Random Interiors", "Select", "Cancel");
		}
    }
    return 1;
}

Dialog:BussinesINT5(playerid, response, listitem, inputtext[]) {
    if (response) {
        if(listitem == 0) // 4 Dragons Casino
		{
			SetPlayerPos(playerid,2016.2699,1017.7790,996.8750);
			SetPlayerInterior(playerid,10);
		}
		if(listitem == 1) // Big Spread Ranch
		{
			SetPlayerPos(playerid,1212.019897,-28.663099,1000.953125);
			SetPlayerInterior(playerid,3);
		}
		if(listitem == 2) // Strip Club
		{
			SetPlayerPos(playerid,1204.809936,-11.586799,1000.921875);
			SetPlayerInterior(playerid,2);
		}
		if(listitem == 3) // Pleause Domes
		{
			SetPlayerPos(playerid,-2640.762939,1406.682006,906.460937);
			SetPlayerInterior(playerid,3);
		}
		if(listitem == 4) // Back
		{
			Dialog_Show(playerid, BussinesINT, DIALOG_STYLE_LIST, "Businesses interiors categories","24/7's\nFast Foods Interiors\nResturants & Clubs\nAmmunation Interiors\nCasino Interiors\nElectronics Store\nClothes Shops Interiors\nUsefull Random Interiors", "Select", "Cancel");
		}
    }
    return 1;
}

Dialog:BussinesINT6(playerid, response, listitem, inputtext[]) {
    if (response) {
        if(listitem == 0) // Electronics Store
		{
			SetPlayerPos(playerid,1003.6486,52.0992,55.3221);
			SetPlayerInterior(playerid,10);
		}
		if(listitem == 1) //
		{
			SetPlayerPos(playerid,-2240.468505,137.060440,1035.414062);
			SetPlayerInterior(playerid,6);
		}
		if(listitem == 2) // Back
		{
			Dialog_Show(playerid, BussinesINT, DIALOG_STYLE_LIST, "Businesses interiors categories","24/7's\nFast Foods Interiors\nResturants & Clubs\nAmmunation Interiors\nCasino Interiors\nElectronics Store\nClothes Shops Interiors\nUsefull Random Interiors", "Select", "Cancel");
		}
    }
    return 1;
}

Dialog:BussinesINT7(playerid, response, listitem, inputtext[]) {
    if (response) {
        if(listitem == 0) // Binco
		{
			SetPlayerPos(playerid,207.737991,-109.019996,1005.132812);
			SetPlayerInterior(playerid,15);
		}
		if(listitem == 1) // Didier sachs
		{
			SetPlayerPos(playerid,204.332992,-166.694992,1000.523437);
			SetPlayerInterior(playerid,14);
		}
		if(listitem == 2) // ProLaps
		{
			SetPlayerPos(playerid,207.054992,-138.804992,1003.507812);
			SetPlayerInterior(playerid,3);
		}
		if(listitem == 3) // Suburban
		{
			SetPlayerPos(playerid,203.777999,-48.492397,1001.804687);
			SetPlayerInterior(playerid,1);
		}
		if(listitem == 4) // Victim
		{
			SetPlayerPos(playerid,226.293991,-7.431529,1002.210937);
			SetPlayerInterior(playerid,5);
		}
		if(listitem == 5) // Zip
		{
			SetPlayerPos(playerid,161.391006,-93.159156,1001.804687);
			SetPlayerInterior(playerid,18);
		}
		if(listitem == 6) // Back
		{
			Dialog_Show(playerid, BussinesINT, DIALOG_STYLE_LIST, "Businesses interiors categories","24/7's\nFast Foods Interiors\nResturants & Clubs\nAmmunation Interiors\nCasino Interiors\nElectronics Store\nClothes Shops Interiors\nUsefull Random Interiors", "Select", "Cancel");
		}
    }
    return 1;
}

Dialog:GoldShop(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				if(pData[playerid][pGold] < 50) return Error(playerid, "Not enough gold!");
				pData[playerid][pGold] -= 50;
				pData[playerid][pWarn]--;
				SendClientMessageEx(playerid, COLOR_ARWIN, "GOLD: "WHITE_E"You reduce 1 warning point");
			}
			case 1:
			{
				if(pData[playerid][pGold] < 150) return Error(playerid, "Not enough gold!");
				Dialog_Show(playerid, ChangePhone, DIALOG_STYLE_INPUT, ""YELLOW_E"Change Phone Number ", "Masukan No Phone Yang Mau Anda Gunakan", "Change", "Exit");
			}
			case 2:
			{
				if(pData[playerid][pGold] < 100) return Error(playerid, "Not enough gold!");
				Dialog_Show(playerid, ChangeBank, DIALOG_STYLE_INPUT, ""YELLOW_E"Change Bank Number ", "Masukan No Bank Account Yang Mau Anda Gunakan", "Change", "Exit");
			}
			case 3:
			{
				if(pData[playerid][pGold] < 100) return Error(playerid, "Not enough gold!");
				new found = false, msg2[512];
				format(msg2, sizeof(msg2), "Model(ID)\tPlate\n");
				for(new i = 0; i < MAX_VEHICLES; i++)
				{
					if(pvData[i][cClaim] == 1) continue;
					if(pvData[i][cOwner] == pData[playerid][pID])
					{
						gListedItems[playerid][found] = i;
						format(msg2, sizeof(msg2), "%s%s(%d)\t%s\n", msg2, GetVehicleModelName(pvData[i][cModel]), pvData[i][cVeh], pvData[i][cPlate]);
						found++;
					}
				}
				if(found) Dialog_Show(playerid, CustomPlate, DIALOG_STYLE_TABLIST_HEADERS, "Custom Plate", msg2, "Select", "Close");
			}
			case 4:
			{
				if(pData[playerid][pGold] < 250) return Error(playerid, "Not enough gold!");
				Dialog_Show(playerid, ChangeMask, DIALOG_STYLE_INPUT, ""YELLOW_E"Change Mask Number ", "Masukan no mask Yang Mau Anda Gunakan", "Change", "Exit");
			}
			case 5:
			{
				if(pData[playerid][pGold] < 500) return Error(playerid, "Not enough gold!");
				pData[playerid][pGold] -= 500;
				pData[playerid][pClaimVIP][1]++;
				SendClientMessageEx(playerid, COLOR_ARWIN, "GOLD: "YELLOW_E"You have successfully purchased a house gate with gold 500");
			}
			case 6:
			{
				if(pData[playerid][pGold] < 750) return Error(playerid, "Not enough gold!");
				pData[playerid][pGold] -= 750;
				pData[playerid][pClaimVIP][2]++;
				SendClientMessageEx(playerid, COLOR_ARWIN, "GOLD: "YELLOW_E"You have successfully purchased a house mapping with gold 750");
			}
			case 7:
			{
				if(pData[playerid][pGold] < 550) return Error(playerid, "Not enough gold!");
				pData[playerid][pGold] -= 550;
				pData[playerid][pClaimVIP][0]++;
				SendClientMessageEx(playerid, COLOR_ARWIN, "GOLD: "YELLOW_E"You have successfully purchased a VIP Dealership Claims with gold 550");
			}
		}
	}
    return 1;
}

Dialog:DialogBug(playerid, response, listitem, inputtext[]) {
    if(response)
    {
        new String[212];
        if(listitem == 0)
        {
            foreach(new i : Player)
            {
                if(pData[i][pAdmin] > 0)
                {
                    format(String,sizeof(String), "[STUCK]: {00FFFF}%s[id:%d] "YELLOW_E"Freeze bug while Spawn or Death.", ReturnName(playerid), playerid);
                    SendClientMessage(playerid, COLOR_ARWIN, String);
                }
            }
            SendClientMessage(playerid, COLOR_ARWIN, "REPORTINFO: "WHITE_E"Report anda telah dikirim ke Administrator yang online");
            return 1;
        }
        if(listitem == 1)
        {
            foreach(new i : Player)
            {
                if(pData[i][pAdmin] > 0)
                {
                    format(String,sizeof(String), "[STUCK]: {00FFFF}%s[id:%d] "YELLOW_E"Wrong World ID (WWID) (vw: %d, int: %d)",ReturnName(playerid), playerid, pData[playerid][pWorld], pData[playerid][pInt]);
                    SendClientMessage(playerid, COLOR_ARWIN, String);
                }
            }
            SendClientMessage(playerid, COLOR_ARWIN, "REPORTINFO: "WHITE_E"Report anda telah dikirim ke Administrator yang online");
            return 1;
        }
        if(listitem == 2)
        {
            foreach(new i : Player)
            {
                if(pData[i][pAdmin] > 0)
                {
                    format(String,sizeof(String), "[STUCK]: {00FFFF}%s[id:%d] "YELLOW_E"Stuck at someone property or entraance (vw: %d, int: %d)",ReturnName(playerid), playerid, pData[playerid][pWorld], pData[playerid][pInt]);
                    SendClientMessage(playerid, COLOR_ARWIN, String);
                }
            }
            SendClientMessage(playerid, COLOR_ARWIN, "REPORTINFO: "WHITE_E"Report anda telah dikirim ke Administrator yang online");
            return 1;
        }
        if(listitem == 3)
        {
            foreach(new i : Player)
            {
                if(pData[i][pAdmin] > 0)
                {
                    format(String,sizeof(String), "[STUCK]: {00FFFF}%s[id:%d] "YELLOW_E"Spawn at Blueberry (vw: %d, int: %d)",ReturnName(playerid), playerid, pData[playerid][pWorld], pData[playerid][pInt]);
                    SendClientMessage(playerid, COLOR_ARWIN, String);
                }
            }
            SendClientMessage(playerid, COLOR_ARWIN, "REPORTINFO: "WHITE_E"Report anda telah dikirim ke Administrator yang online");
            return 1;
        }
        if(listitem == 4)
        {
            foreach(new i : Player)
            {
                if(pData[i][pAdmin] > 0)
                {
                    format(String,sizeof(String), "[STUCK]: {00FFFF}%s[id:%d] "YELLOW_E"Bug Death (vw: %d, int: %d)",ReturnName(playerid), playerid, pData[playerid][pWorld], pData[playerid][pInt]);
                    SendClientMessage(playerid, COLOR_ARWIN, String);
                }
            }
            SendClientMessage(playerid, COLOR_ARWIN, "REPORTINFO: "WHITE_E"Report anda telah dikirim ke Administrator yang online");
            return 1;
        }
    }
    return 1;
}
