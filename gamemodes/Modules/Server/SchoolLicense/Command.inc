
CMD:taketest(playerid, params[])
{
    if(pData[playerid][pTaketest] > 0)
    return Error(playerid, "You haven't had the test yet");
    if(IsPlayerInRangeOfPoint(playerid, 3.0, 1491.14, 1306.33, 1093.28)) {
        new cost = 5000;
        if(pData[playerid][pMoney] < cost) return Error(playerid, "Your money is not enough");
        GivePlayerMoneyEx(playerid, -cost);
        TakeLicense[playerid] = 1;
        SendClientMessageEx(playerid, COLOR_ARWIN, "SERVER: "YELLOW_E"Silahkan keluar dari ruangan ini dan masuk ke mobil premier, ikuti langkah selanjutnya");
    }
    else if(IsPlayerInRangeOfPoint(playerid, 3.0, -2032.7240,-117.5565,1035.1719)) {
        TakeTestBoat[playerid] = 1;
        BoatStep[playerid] = 1;
        SendClientMessageEx(playerid, COLOR_ARWIN, "SERVER: "YELLOW_E"Silahkan keluar dari ruangan ini dan naiki boat speeder dibawah, ikuti langkah selanjutnya");
    }
    return 1;
}

CMD:renewlic(playerid, params[])
{
    if(pData[playerid][pTaketest] < 1)
    return Error(playerid, "You haven't had the test yet");
    if(pData[playerid][pDriveLic] > 0)
    return Error(playerid, "You still have an active license");
    if(IsPlayerInRangeOfPoint(playerid, 3.0, 1491.14, 1306.33, 1093.28)) {
        new cost = 2500;
        if(pData[playerid][pMoney] < cost) return Error(playerid, "Your money is not enough");
        pData[playerid][pDriveLic] = 1;
        pData[playerid][pDriveLicTime] = gettime() + (15 * 86400);
        SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"You have renewed your driver's license");     
        GivePlayerMoneyEx(playerid, -cost);
    }
    else if(IsPlayerInRangeOfPoint(playerid, 3.0, -2032.7240,-117.5565,1035.1719)) {
        new cost = 5000;
        if(pData[playerid][pMoney] < cost) return Error(playerid, "Your money is not enough");
        pData[playerid][pBoatLic] = 1;
        pData[playerid][pBoatLicTime] = gettime() + (15 * 86400);
        SendClientMessageEx(playerid, COLOR_ARWIN, "LICENSE: "WHITE_E"You have renewed your boat license");     
        GivePlayerMoneyEx(playerid, -cost);
    }
    return 1;
}