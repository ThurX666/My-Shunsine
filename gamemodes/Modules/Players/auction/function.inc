
IsPlayerInNewbieSchool(playerid)
{
    if(IsPlayerInRangeOfPoint(playerid, 40.0, 1493.8127,-1555.4021,15.0255) && GetPlayerInterior(playerid) == 5)
        return 1;
    return 0;
}

IsPlayerInAuction(playerid)
{
    if(IsPlayerInRangeOfPoint(playerid, 40.0, 1386.0345,1372.3097,11.0572) && GetPlayerInterior(playerid) == 1)
        return 1;
    return 0;
}

Auction_GetType(id, type, misc) {
    new output[128], typeName[24];

    switch (type) {
        case 1: {
            new name[128];
            if(bData[id][bType] == 1)
            {
                name= "Fast Food";
            }
            else if(bData[id][bType] == 2)
            {
                name= "Market";
            }
            else if(bData[id][bType] == 3)
            {
                name= "Clothes";
            }
            else if(bData[id][bType] == 4)
            {
                name= "Sportshop";
            }
            else if(bData[id][bType] == 5)
            {
                name= "Electronic";
            }
            else if(bData[id][bType] == 6)
            {
                name= "GYM";
            }
            else
            {
                name= "Unknow";
            }
            format(output,sizeof(output),"Bisnis %s",name);
        }
        case 2: {
            new name[128];
            if(hData[id][hType] == 1)
            {
                name= "Small";
            }
            else if(hData[id][hType] == 2)
            {
                name= "Medium";
            }
            else if(hData[id][hType] == 3)
            {
                name= "Large";
            }
            else
            {
                name= "Unknow";
            }
            format(output,sizeof(output),"House %s", name);
        }
        case 4: format(output,sizeof(output),"Workshop");
        case 5: format(output,sizeof(output),"Private Farm");
        case 6: {
            Flat_GetType2(misc, typeName);
            format(output,sizeof(output),"Flat %s", typeName);
        }
    }

    return output;
}

Auction_GetIDPro(type, id) {
    new output[128], typeName[24];

    switch (type) {
        case 0: {
            format(output,sizeof(output),"ID:[%d] HOUSE\n%s", id, GetLocation(hData[id][hExtposX], hData[id][hExtposY], hData[id][hExtposZ]));
        }
        case 1: {
            format(output,sizeof(output),"ID:[%d] BUSSINES\n%s", id, GetLocation(bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ]));
        }
        //case 2: format(output,sizeof(output),"ID:[%d] WORKSHOP\n%s", id, GetLocation(wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]));
        case 3: {
            Flat_GetType2(id, typeName);
            format(output,sizeof(output),"ID:[%d] FLAT\n%s", id, typeName);
        }
    }
    return output;
}

Auction_Reset()
{
    foreach(new id : Player) if(GetPVarInt(id, "IkutLelang") == 1)
    {
        SetPVarInt(id, "IkutLelang", 0);
    }

    SetGVarInt("AuctionType", 0, GLOBAL_VARTYPE_INT);
    SetGVarInt("AuctionCount", 0, GLOBAL_VARTYPE_INT);
    SetGVarInt("AuctionStart", 0, GLOBAL_VARTYPE_INT);
    SetGVarInt("AuctionDiff", 0, GLOBAL_VARTYPE_INT);
    SetGVarInt("AuctionProID", -1, GLOBAL_VARTYPE_INT);
    SetGVarInt("AuctionTypePro", -1, GLOBAL_VARTYPE_INT);
    SetGVarString("AuctionLelang", "none", GLOBAL_VARTYPE_STRING);
    SetGVarString("AuctionHighest", "none", GLOBAL_VARTYPE_STRING);
    KillTimer(Auction);
    return 1;
}

function AuctionTime()
{
    new text[255], property[128],name[MAX_PLAYER_NAME];
    format(property,sizeof(property),"%s", Auction_GetIDPro(GetGVarInt("AuctionTypePro", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)));
    GetGVarString("AuctionHighest", name, sizeof(name), GLOBAL_VARTYPE_STRING);

    switch(GetGVarInt("AuctionType", GLOBAL_VARTYPE_INT))
    {
        case 1: 
        {
            SetGVarInt("AuctionTime", GetGVarInt("AuctionTime", GLOBAL_VARTYPE_INT)-1, GLOBAL_VARTYPE_INT);
            format(text,sizeof(text),""AQUA_E"%s\n"WHITE_E"Start: "GREEN_E"$%s\n"WHITE_E"Diff: "GREEN_E"$%s\n"WHITE_E"Participants: "YELLOW_E"%d\n"WHITE_E"Start in: "RED_E"%d", ReplaceString(property), FormatMoney(GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT)), FormatMoney(GetGVarInt("AuctionDiff", GLOBAL_VARTYPE_INT)), GetGVarInt("AuctionCount", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionTime", GLOBAL_VARTYPE_INT));

            if(GetGVarInt("AuctionTime", GLOBAL_VARTYPE_INT) == 0)
            {
                if(!GetGVarInt("AuctionCount", GLOBAL_VARTYPE_INT))
                {
                    SetDynamicObjectMaterialText(playerauction, 0, "No one join this auction.", 130, "Ariel", 27, 1, -1, -16777216, 1);
                    Auction_Reset();
                }
                else
                {
                    SetGVarInt("AuctionType", 2, GLOBAL_VARTYPE_INT);
                    SetGVarInt("AuctionTime", 10, GLOBAL_VARTYPE_INT);
                }
            }
        }
        case 2: 
        {
            SetGVarInt("AuctionTime", GetGVarInt("AuctionTime", GLOBAL_VARTYPE_INT)-1, GLOBAL_VARTYPE_INT);
            format(text,sizeof(text),"{00FFFF}%s\n"WHITE_E"Highest bidder: "YELLOW_E"%s\n"WHITE_E"Offer: "GREEN_E"$%s\n"WHITE_E"Countdown: "RED_E"%d", ReplaceString(property), name, FormatMoney(GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT)), GetGVarInt("AuctionTime", GLOBAL_VARTYPE_INT));

            if(GetGVarInt("AuctionTime", GLOBAL_VARTYPE_INT) == 0)
            {
                format(text,sizeof(text),"{00FFFF}%s\n"WHITE_E"Highest bidder: "YELLOW_E"%s\n"WHITE_E"Offer: "GREEN_E"$%s\n"WHITE_E"Countdown: "RED_E"0", ReplaceString(property), name, FormatMoney(GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT)));
                foreach(new id : Player) if(IsPlayerInAuction(id))
                {
                    SetPVarInt(id, "IkutLelang", 0);
                    SendClientMessageEx(id, COLOR_ARWIN, "AUCTION: "WHITE_E"Congrast to "AQUA_E"%s "WHITE_E"for winning "GREEN_E"%s", name, property);

                    if(!strcmp(name,ReturnName2(id), true))
                    {
                        SendClientMessageEx(id, COLOR_ARWIN, "AUCTION: "WHITE_E"Anda telah memenangkan %s - "GREEN_E"$%s", property,FormatMoney(GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT)));
                        switch(GetGVarInt("AuctionTypePro", GLOBAL_VARTYPE_INT))
                        {
                            case 0:
                            {
                                if(PropertiResidential_CountMax(id) >= PropertiesResidential_Max(id)) return Error(id, "You can no longer buy a house, your property slots are full");
                                GivePlayerMoneyEx(id, -GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT));
                                GetPlayerName(id, hData[GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)][hOwner], MAX_PLAYER_NAME);
                                hData[GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)][hLastVisited] = gettime();
                                
                                House_Refresh(GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT));
                                House_Save(GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT));
                            }   
                            case 1:
                            {
                                if(PropertiCommercial_CountMax(id) >= PropertiesCommercial_Max(id)) return Error(id, "You can no longer buy a business, your property slots are full");
                                GivePlayerMoneyEx(id, -GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT));
                                GetPlayerName(id, bData[GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)][bOwner], MAX_PLAYER_NAME);
                                bData[GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)][bLastVisited] = gettime();
                                
                                Bisnis_Refresh(GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT));
                                Bisnis_Save(GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT));
                            }
                            case 2:
                            {
                                if(PropertiCommercial_CountMax(id) >= PropertiesCommercial_Max(id)) return Error(id, "You can no longer buy a business, your property slots are full");
                                GivePlayerMoneyEx(id, -GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT));
                                GetPlayerName(id, WorkshopData[GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)][Owner], MAX_PLAYER_NAME);
                                format(WorkshopData[GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)][TextWorkshop], 128, "(w)Repair (g)$0-$250(n)(w)Modification (g)$50(n)(w)Upgrade (g)$250(n)");
                                WorkshopRefresh(GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT));
                                WorkshopSave(GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT));
                            }
                            case 3:
                            {
                                if(PropertiResidential_CountMax(id) >= PropertiesResidential_Max(id)) return Error(id, "You can no longer buy a flat, your property slots are full");
                                GivePlayerMoneyEx(id, -GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT));
                                FlatRoom[GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)][flatRoomOwner] = pData[id][pID];
                                FlatRoom[GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)][flatRoomSeal] = 0;
                                FlatRoom[GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)][flatRoomMoney] = 0;
                                FlatRoom[GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)][flatRoomLastVisited] = gettime();
                                Flat_RemoveAllItems(GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT));
                                FlatFurniture_DeleteAll(GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT));
                                FlatStructure_DeleteAll(GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT), true);

                                FlatRoom_Refresh(GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT));
                                FlatRoom_Save(GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT));
                            }
                        }
                    }
                }
                Auction_Reset();
            }
        }
    }
    SetDynamicObjectMaterialText(playerauction, 0, text, 130, "Ariel", 27, 1, -1, -16777216, 1);
    return 1;
}
