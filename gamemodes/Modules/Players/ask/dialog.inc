
Dialog:DialogAsks(playerid, response, listitem, inputtext[]) {
    if (response) {
        new string[225],
            i = strval(inputtext),
            text[128],
            header[25];
        
        strunpack(text, AskData[i][askQuestion]);
        format(header, sizeof(header), ""RED_E"Ask Id: #%d", i);
        format(string,sizeof(string),""WHITE_E"Issuer: "YELLOW_E"%s\n"WHITE_E"Question: "YELLOW_E"%s.", ReturnName(AskData[i][askPlayer]), text);
        SetPVarInt(playerid, "holdingAskPlayer", AskData[i][askPlayer]);
        Dialog_Show(playerid, DialogAns, DIALOG_STYLE_INPUT,header,string,"Answer","Back");
    }
    return 1;
}

Dialog:DialogAns(playerid, response, listitem, inputtext[]) {
    if (response) {
        new issuerid = GetPVarInt(playerid, "holdingAskPlayer");

        if (!isnull(inputtext)) {
            SendClientMessageEx(issuerid, COLOR_ARWIN, "QUESTIONS: "YELLOW_E"%s", pData[playerid][pAskQ]);
            SendClientMessageEx(issuerid, COLOR_ARWIN, "ANSWER: "YELLOW_E"%s", inputtext);
            SendStaffMessage(COLOR_YELLOW, ""YELLOW_E"[ANS]: "RED_E"%s "WHITE_E"to ID %d: "YELLOW_E"%s", pData[playerid][pAdminname], issuerid, inputtext);

            pData[issuerid][pAsk] = false;
            pData[issuerid][pAskQ] = EOS;
            pData[issuerid][pAskTime] = 0;
            Ask_Clear(issuerid);
        }
    } else callcmd::ans(playerid, "\0"), DeletePVar(playerid, "holdingAskPlayer");
    return 1;
}
