
Dialog:UsePills(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0: 
            {
                //Butuh 5 pil untuk menghilangkan 1 efek batuk.
                if(pData[playerid][pCoughPills] < 1) return Error(playerid, "Anda tidak ada pil untuk penyakit ini.");
                if(pData[playerid][pCough] < 1) return Error(playerid, "Anda tidak dapat mengkonsumsi pil ini.");

                pData[playerid][pCoughPills] --;
                pData[playerid][pCough] = 0;
                SendClientMessage(playerid, COLOR_ARWIN, "MEDICINEINFO: {FFff00}You've use Neladryl Acetate");
            }
            case 1:
            {
                if(pData[playerid][pMigrainPills] < 1) return Error(playerid, "Anda tidak ada pil untuk penyakit ini.");
                if(pData[playerid][pMigrainRate] < 1) return Error(playerid, "Anda tidak dapat mengkonsumsi pil ini.");

                pData[playerid][pMigrainPills] --;
                if(++pData[playerid][pMigrainUsed] >= 5)
                {
                    pData[playerid][pMigrainRate]  = 0;
                    pData[playerid][pMigrainUsed] = 0;
                }
                SendClientMessage(playerid, COLOR_ARWIN, "MEDICINEINFO: {FFff00}You've use Kratotamax Plus");
            }
            case 2:
            {
                if(pData[playerid][pFiverPills] < 1) return Error(playerid, "Anda tidak ada pil untuk penyakit ini.");
                if(pData[playerid][pFever] < 1) return Error(playerid, "Anda tidak dapat mengkonsumsi pil ini.");

                pData[playerid][pFiverPills] --;
                if(++pData[playerid][pFeverUsed] >= 5)
                {
                    pData[playerid][pFeverUsed] = 0;
                    pData[playerid][pFever] = 0;
                }
                SendClientMessage(playerid, COLOR_ARWIN, "MEDICINEINFO: {FFff00}You've use Lazattavitus Extra");
            }
        }
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "*%s take's out %s and eat it.", ReturnName(playerid), inputtext);
        pData[playerid][pUsePills] = 100;
    }
    return 1;
}

Dialog:TakePills(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0: pData[playerid][pCoughPills] ++;
            case 1: pData[playerid][pMigrainPills] ++;
            case 2: pData[playerid][pFiverPills] ++;
        }
        SendClientMessageEx(playerid,COLOR_ARWIN,"MEDICINFO: {FFFFFF}You've take "YELLOW_E"%s {FFFFFF}from Equipment Medicine.", inputtext);
    }
    return 1;
}

Dialog:TestSurgey(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new player = pData[playerid][pSurgeyID];

        pData[player][pStartSurgey] = 1;
        pData[player][pSurgeryTimer] = SetTimerEx("Treatment", 60000, false, "d", player);
        SendCustomMessage(player, "SURGERY", ""YELLOW_E"%s "WHITE_E"memulai operasi pada Anda.", ReturnName(playerid));
        SendCustomMessage(player, "SURGERY", "Anda diharuskan menunggu sekitar "GREEN_E"2 menit "WHITE_E"untuk menyelesaikan operasi.");
        SendCustomMessage(playerid, "SURGERY", "Anda melakukan operasi untuk "YELLOW_E"%s.", ReturnName(player));
    }
    return 1;
}
