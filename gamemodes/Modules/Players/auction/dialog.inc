
Dialog:AuctionType(playerid, response, listitem, inputtext[]) {
    if (response) {
        switch(listitem)
        {
            case 0:
            {
                SetGVarInt("AuctionTypePro", 0, GLOBAL_VARTYPE_INT);
                Dialog_Show(playerid, AuctionProID, DIALOG_STYLE_INPUT, "Masukan ID House", "Input ID", "Next", "Close");
            }
            case 1:
            {
                SetGVarInt("AuctionTypePro", 1, GLOBAL_VARTYPE_INT);
                Dialog_Show(playerid, AuctionProID, DIALOG_STYLE_INPUT, "Masukan ID Bussines", "Input ID", "Next", "Close");
            }
            case 2:
            {
                SetGVarInt("AuctionTypePro", 2, GLOBAL_VARTYPE_INT);
                Dialog_Show(playerid, AuctionProID, DIALOG_STYLE_INPUT, "Masukan ID Workshop", "Input ID", "Next", "Close");
            }
            case 3:
            {
                SetGVarInt("AuctionTypePro", 3, GLOBAL_VARTYPE_INT);
                Dialog_Show(playerid, AuctionProID, DIALOG_STYLE_INPUT, "Masukan ID Flat", "Input ID", "Next", "Close");
            }
        }
    }
    return 1;
}

Dialog:AuctionProID(playerid, response, listitem, inputtext[]) {
    if (response) {
        new string[525], string2[525];
        switch(GetGVarInt("AuctionTypePro", GLOBAL_VARTYPE_INT))
        {
            case 0:
            {
                if (!Iter_Contains(Houses, strval(inputtext))) return Error(playerid, "Invalid ID");
                format(string,sizeof(string),"ID:[%d] HOUSE", strval(inputtext));
                SetGVarInt("AuctionProID", strval(inputtext), GLOBAL_VARTYPE_INT);
                format(string2,sizeof(string2),"Start Money %d\nDiff %d\nStart", GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionDiff", GLOBAL_VARTYPE_INT));
                Dialog_Show(playerid, AuctionProNext, DIALOG_STYLE_LIST, string, string2, "Next", "Close");
            }
            case 1:
            {
                if (!Iter_Contains(Bisnis, strval(inputtext))) return Error(playerid, "Invalid ID");
                format(string,sizeof(string),"ID:[%d] BUSSINES", strval(inputtext));
                SetGVarInt("AuctionProID", strval(inputtext), GLOBAL_VARTYPE_INT);
                format(string2,sizeof(string2),"Start Money %d\nDiff %d\nStart", GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionDiff", GLOBAL_VARTYPE_INT));
                Dialog_Show(playerid, AuctionProNext, DIALOG_STYLE_LIST, string, string2, "Next", "Close");
            }
            case 2:
            {
                if (!Iter_Contains(Workshop, strval(inputtext))) return Error(playerid, "Invalid ID");
                format(string,sizeof(string),"ID:[%d] WORKSHOP", strval(inputtext));
                SetGVarInt("AuctionProID", strval(inputtext), GLOBAL_VARTYPE_INT);
                format(string2,sizeof(string2),"Start Money %d\nDiff %d\nStart", GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionDiff", GLOBAL_VARTYPE_INT));
                Dialog_Show(playerid, AuctionProNext, DIALOG_STYLE_LIST, string, string2, "Next", "Close");
            }
            case 3:
            {
                if (!Iter_Contains(Flat, strval(inputtext))) return Error(playerid, "Invalid ID");
                format(string,sizeof(string),"ID:[%d] FLAT", strval(inputtext));
                SetGVarInt("AuctionProID", strval(inputtext), GLOBAL_VARTYPE_INT);
                format(string2,sizeof(string2),"Start Money %d\nDiff %d\nStart", GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionDiff", GLOBAL_VARTYPE_INT));
                Dialog_Show(playerid, AuctionProNext, DIALOG_STYLE_LIST, string, string2, "Next", "Close");
            }
        }
    }
    return 1;
}

Dialog:AuctionProNext(playerid, response, listitem, inputtext[]) {
    if (response) {
        new string[525];
        format(string,sizeof(string),"%s", Auction_GetIDPro(GetGVarInt("AuctionTypePro", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)));
        switch(listitem)
        {
            case 0:
            {
                Dialog_Show(playerid, AuctionProNext1, DIALOG_STYLE_INPUT, string, "Masukan uang start (dollar)", "Next", "Close");
            }
            case 1:
            {
                Dialog_Show(playerid, AuctionProNext2, DIALOG_STYLE_INPUT, string, "Masukan uang diff (dollar)", "Next", "Close");
            }
            case 2:
            {
                SetGVarInt("AuctionType", 1, GLOBAL_VARTYPE_INT);
                SetGVarInt("AuctionTime", 15, GLOBAL_VARTYPE_INT);
                SetGVarInt("AuctionCount", 0, GLOBAL_VARTYPE_INT);
                //SetGVarString("AuctionLelang", lelang, GLOBAL_VARTYPE_STRING);
                SetGVarString("AuctionHighest", "none", GLOBAL_VARTYPE_STRING);

                foreach(new id : Player) if(IsPlayerInAuction(id))
                {
                    SendClientMessageEx(id, COLOR_ARWIN, "AUCTION: "YELLOW_E"Item: "AQUA_E"%s | "YELLOW_E"Start price: "GREEN_E"$%s | "YELLOW_E"Diff: "GREEN_E"$%s", Auction_GetIDPro(GetGVarInt("AuctionTypePro", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)), FormatMoney(GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT)), FormatMoney(GetGVarInt("AuctionDiff", GLOBAL_VARTYPE_INT)));
                    SendClientMessageEx(id, COLOR_ARWIN, "AUCTION: "WHITE_E"Use command "YELLOW_E"'/auction join' "WHITE_E"to join auction.");
                }
                Auction = SetTimer("AuctionTime", 1000, true);
                new text[255];
                format(text,sizeof(text),"{00FFFF}%s\n"GREEN_E"Start: "WHITE_E"$%s\n"GREEN_E"Diff: "WHITE_E"$%s\n"GREEN_E"Participants: "WHITE_E"%d\nSeart in: %d", ReplaceString(Auction_GetIDPro(GetGVarInt("AuctionTypePro", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT))), FormatMoney(GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT)), FormatMoney(GetGVarInt("AuctionDiff", GLOBAL_VARTYPE_INT)), GetGVarInt("AuctionCount", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionTime", GLOBAL_VARTYPE_INT));
                SetDynamicObjectMaterialText(playerauction, 0, text, 130, "Ariel", 27, 1, -1, -16777216, 1);

                SendAdminMessage(TOMATO, "AdmWarn: %s start the auction, start: [$%s] diff: [$%s]", ReturnName2(playerid), FormatMoney(GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT)), FormatMoney(GetGVarInt("AuctionDiff", GLOBAL_VARTYPE_INT)));
            }
        }
    }
    return 1;
}

Dialog:AuctionProNext1(playerid, response, listitem, inputtext[]) {
    if (response) {
        new string[525], string2[525];
        new duitstart[32];
        format(duitstart, sizeof(duitstart), "%d00", strval(inputtext));
        format(string,sizeof(string),"%s", Auction_GetIDPro(GetGVarInt("AuctionTypePro", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)));
        SetGVarInt("AuctionStart", strval(duitstart), GLOBAL_VARTYPE_INT);
        format(string2,sizeof(string2),"Start Money $%d\nDiff $%d\nStart", GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionDiff", GLOBAL_VARTYPE_INT));
        Dialog_Show(playerid, AuctionProNext, DIALOG_STYLE_LIST, string, string2, "Next", "Close");
    }
    return 1;
}

Dialog:AuctionProNext2(playerid, response, listitem, inputtext[]) {
    if (response) {
        new string[525], string2[525];
        new duitbid[32];
        format(duitbid, sizeof(duitbid), "%d00", strval(inputtext));
        SetGVarInt("AuctionDiff", strval(duitbid), GLOBAL_VARTYPE_INT);
        format(string,sizeof(string),"%s", Auction_GetIDPro(GetGVarInt("AuctionTypePro", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionProID", GLOBAL_VARTYPE_INT)));
        format(string2,sizeof(string2),"Start Money %d\nDiff %d\nStart", GetGVarInt("AuctionStart", GLOBAL_VARTYPE_INT), GetGVarInt("AuctionDiff", GLOBAL_VARTYPE_INT));
        Dialog_Show(playerid, AuctionProNext, DIALOG_STYLE_LIST, string, string2, "Next", "Close");
    }
    return 1;
}

Dialog:AuctionQueue(playerid, response, listitem, inputtext[]) {
    if (response) {
        new
            Cache:query,
            str[650];

        aucQueue[playerid]++;
        query = mysql_query(g_SQL, sprintf("SELECT * FROM `auction_queue` LIMIT %d, 10", aucQueue[playerid] * 10));

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

        cache_delete(query);
    }
    else aucQueue[playerid] = 0;
    return 1;
}
