
CMD:changeboard(playerid, params[])
{
    new text[128],string[128];

    if (pData[playerid][pAdmin] < 1)
        return PermissionError(playerid);
    if(!IsPlayerInNewbieSchool(playerid))
        return Error(playerid, "You're not in auction.");
    if(sscanf(params, "s[128]", text))
        return Usage(playerid, "/changeboard [text]");

    if(strlen(text) > 128)
        return Error(playerid, "Text terlalu panjang.");

    FixText(text);
    format(string,sizeof(string),"%s",ReplaceString(text));
    SetDynamicObjectMaterialText(newbieschool, 0, string, 130, "Ariel", 27, 1, -1, -16777216, 1);
    return 1;
}

CMD:auction(playerid, params[])
{
    new option[32], string[128], property[128];

    if(!IsPlayerInAuction(playerid))
        return Error(playerid, "You're not in auction.");

    if(sscanf(params, "s[32]S()[128]", option, string))
        return Usage(playerid, "/auction [create/join/bid/cancel/queue]");

    if(!strcmp(option,"create", true))
    {
        if (pData[playerid][pAdmin] < 5)
            return PermissionError(playerid);

        if(GetGVarInt("AuctionType", GLOBAL_VARTYPE_INT) != 0)
            return Error(playerid, "Auction sedang berjalan, /auction cancel tuntuk menunda.");
        Dialog_Show(playerid, AuctionType, DIALOG_STYLE_LIST, "List Property", "House\nBussines\nWorkshop\nFlat", "Next", "Close");
    }
    else if(!strcmp(option, "join", true))
    {
        if(GetGVarInt("AuctionType", GLOBAL_VARTYPE_INT) != 1) return Error(playerid, "Auction belum di mulai.");
        if(GetPVarInt(playerid, "IkutLelang")) return Error(playerid, "Anda sedang mengikuti auction ini.!");
        if(GetPlayerMoney(playerid) < 100) return Error(playerid, "Anda tidak memiliki modal uang $100 untuk mengikuti auction ini.");

        GetGVarString("AuctionLelang", property, sizeof(property), GLOBAL_VARTYPE_STRING);

        GivePlayerMoneyEx(playerid, -100);
        SendClientMessageEx(playerid, COLOR_ARWIN, "AUCTION: "WHITE_E"Gunakan perintah "YELLOW_E"'/auction bid' "WHITE_E"untuk memenangkan auction.");

        SetPVarInt(playerid, "IkutLelang", 1);
        SetGVarInt("AuctionCount", GetGVarInt("AuctionCount", GLOBAL_VARTYPE_INT)+1, GLOBAL_VARTYPE_INT);

    }
    else if(!strcmp(option, "bid", true))
    {
        new money = (GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT)+GetGVarInt("AuctionDiff", GLOBAL_VARTYPE_INT)),
            name[MAX_PLAYER_NAME];

        GetGVarString("AuctionHighest", name, sizeof(name), GLOBAL_VARTYPE_STRING);

        if(GetGVarInt("AuctionType", GLOBAL_VARTYPE_INT) == 1)
        return Error(playerid, "Auction belum di mulai.");

        if(!strcmp(name, ReturnName2(playerid), true))
        return Error(playerid, "Anda masih berada di peringkat teratas auction ini!.");

        if(!GetPVarInt(playerid, "IkutLelang"))
        return Error(playerid, "Anda tidak mengikuti auction ini.");

        if(GetPlayerMoney(playerid) < money)
        return Error(playerid, "Anda tidak memiliki uang sebesar $%s untuk mengikuti auction ini.", FormatMoney(money));

        SetGVarInt("AuctionStart", money, GLOBAL_VARTYPE_INT);
        SetGVarString("AuctionHighest", ReturnName2(playerid), GLOBAL_VARTYPE_STRING);
        SetGVarInt("AuctionTime", 10, GLOBAL_VARTYPE_INT);
    }
    else if(!strcmp(option, "cancel", true))
    {
        if (pData[playerid][pAdmin] < 5)
            return PermissionError(playerid);
        if(GetGVarInt("AuctionType", GLOBAL_VARTYPE_INT) == 0)
        return Error(playerid, "Auction sedang tidak berlangsung!.");

        foreach(new id : Player) if(IsPlayerInAuction(id))
        {
            SendClientMessageEx(id, COLOR_ARWIN, "AUCTION: "YELLOW_E"%s "WHITE_E"menunda auction.", ReturnName2(playerid));
        }
        Auction_Reset();
        SetDynamicObjectMaterialText(playerauction, 0, "Auction di tunda.", 130, "Ariel", 27, 1, -1, -16777216, 1);
    } else if (!strcmp(option, "queue", true)) {
        new Cache:check, str[650];
        
        aucQueue[playerid] = 0;

        check = mysql_query(g_SQL, sprintf("SELECT * FROM `auction_queue` LIMIT %d, 10", aucQueue[playerid] * 10));

        new rows = cache_num_rows(), location[32], id, type, misc;

        if (rows) {
            format(str,sizeof(str),"ID\tName\tLocation\n");
            for (new i = 0; i < rows; i ++) {
                cache_get_value(i, "Location", location);
                cache_get_value_int(i, "ID", id);
                cache_get_value_int(i, "Property", type);
                cache_get_value_int(i, "Type", misc);

                format(str,sizeof(str),"%s%d\t%s\t%s\n",str,id,Auction_GetType(id, type, misc),location);
            }
            Dialog_Show(playerid, AuctionQueue, DIALOG_STYLE_TABLIST_HEADERS, "Auction Queue", str, "Next", "Close");
        } else Error(playerid, "There is no auction on the queue!");

        cache_delete(check);
    }
    else 
        Usage(playerid, "/auction [create/join/bid/cancel]");

    return 1;
}
