
CMD:asks(playerid, params[]) {
    if (pData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    if(!Ask_Count()) return Error(playerid, "There are no one ask active.");

    new
        dialog[900],
        text[128];

    format(dialog, sizeof(dialog),"ID\tIssuer\tQuestion\n");
    for (new i = 0; i != MAX_ASK; i ++) if(AskData[i][askExists]) {
        strunpack(text, AskData[i][askQuestion]);

        if(strlen(text) > 32)
            format(dialog, sizeof(dialog), "%s%d\t%s (%d)\t%.32s ...\n", dialog, i, ReturnName(AskData[i][askPlayer]), AskData[i][askPlayer], text);
        else
            format(dialog, sizeof(dialog), "%s%d\t%s (%d)\t%s\n", dialog, i, ReturnName(AskData[i][askPlayer]), AskData[i][askPlayer], text);
    }
    Dialog_Show(playerid, DialogAsks, DIALOG_STYLE_TABLIST_HEADERS,"Asks", dialog,"Next","Cancel");
    return 1;
}

CMD:clearallasks(playerid) {
    if (pData[playerid][pAdmin] < 5)
        return PermissionError(playerid);
        
    new
        count;

    for (new i = 0; i != MAX_ASK; i ++)
    {
        if(AskData[i][askExists]) {
            Ask_Remove(i);
            count++;
        }
    }
    if(!count)
        return Error(playerid, "There are no active asks to display.");
            
    SendAdminMessage(TOMATO, "CLEAR: "WHITE_E"%s has removed all asks on the server.",ReturnName(playerid));
    return 1;
}

CMD:ask(playerid, params[])
{
    if(isnull(params))
        return Usage(playerid, "/ask [questions]");

    if(pData[playerid][pAsk] || Ask_GetCount(playerid) > 0)
        return Error(playerid, "Waiting answered from admin to repeat your questions again..");

    if(pData[playerid][pAskTime] > 0)
    {
        Error(playerid,"Wait 120 seconds before sending another ask");
        return 1;
    }

    if((Ask_Add(playerid, params)) != -1)
    {
        SendQuestionMessage(COLOR_ARWIN, "[ASK] "WHITE_E"%s[%d]: "YELLOW_E"%s", ReturnName(playerid), playerid, params);
        pData[playerid][pAsk] = true;
        format(pData[playerid][pAskQ], 128, params);

        pData[playerid][pAskTime] = 180;

        Servers(playerid, "You have sent a questions to helper/admin online.");
    }
    else Error(playerid, "The ask list is full. Please wait for a while.");
    return 1;
}

CMD:ans(playerid, params[])
{
    static
        userid,
        text[128];

    if (pData[playerid][pAdmin] < 1 && !pData[playerid][pHelper])
        return PermissionError(playerid);

    if(sscanf(params, "us[128]", userid, text)) return Usage(playerid, "/ans [playerid/PartOfName] [message]");
    if(userid == INVALID_PLAYER_ID) return Error(playerid, "You have specified an invalid player.");
    if(!pData[userid][pAsk]) return Error(playerid, "This player don't ask anything");

    SendClientMessageEx(userid, COLOR_ARWIN, "QUESTIONS: "YELLOW_E"%s", pData[playerid][pAskQ]);
    SendClientMessageEx(userid, COLOR_ARWIN, "ANSWER: "YELLOW_E"%s", text);
    SendStaffMessage(COLOR_YELLOW, ""YELLOW_E"[ANS]: "RED_E"%s "WHITE_E"to ID %d: "YELLOW_E"%s", pData[playerid][pAdminname], userid, text);

    pData[userid][pAsk] = false;
    pData[userid][pAskQ] = EOS;
    Ask_Clear(userid);
    return 1;
}
