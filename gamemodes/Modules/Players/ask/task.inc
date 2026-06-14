
ptask Canusingask[1000](playerid)
{
    pData[playerid][pAskTime]--;
    if(pData[playerid][pAskTime] == 0)
    {
        if(pData[playerid][pAsk])
        {
            pData[playerid][pAsk] = false;
            pData[playerid][pAskQ] = EOS;
            Servers(playerid, "No one answer your questions, now you can use /ask again.");
        }
    }
    return 1;
}
