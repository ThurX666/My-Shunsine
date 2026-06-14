
Ask_GetCount(playerid) {
    new count = 0;

    for (new i = 0; i < MAX_ASK; i++) if (AskData[i][askExists] && AskData[i][askPlayer] == playerid) {
        count++;
    }
    return count;
}

Ask_Count() {
    new count = 0;

    for (new i = 0; i != MAX_ASK; i ++) if(AskData[i][askExists]) {
        count++;
    }
    return count;
}

Ask_Clear(playerid) {
    for (new i = 0; i < MAX_ASK; i++) if (AskData[i][askExists] && AskData[i][askPlayer] == playerid) {
        Ask_Remove(i);
    }
    return 1;
}

Ask_Add(playerid, const text[])
{
    for (new i = 0; i != MAX_ASK; i ++)
    {
        if(!AskData[i][askExists])
        {
            AskData[i][askExists] = true;
            AskData[i][askPlayer] = playerid;

            strpack(AskData[i][askQuestion], text, 128 char);
            return i;
        }
    }
    return -1;
}

Ask_Remove(askid)
{
    if(askid != -1 && AskData[askid][askExists])
    {
        AskData[askid][askExists] = false;
        AskData[askid][askPlayer] = INVALID_PLAYER_ID;
    }
    return 1;
}

stock SendQuestionMessage(color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 8)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 8); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player)
        {
            if(pData[i][pAdmin] >= 1 && pData[i][pTogStaffQuestion] == 0) {
                SendClientMessage(i, color, string);
            }
        }
        return 1;
    }
    foreach (new i : Player)
    {
        if(pData[i][pAdmin] >= 1 && pData[i][pTogStaffQuestion] == 0) {
            SendClientMessage(i, color, str);
        }
    }
    return 1;
}
