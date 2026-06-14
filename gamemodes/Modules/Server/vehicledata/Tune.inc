CMD:tune(playerid, params[])
{
    if(pData[playerid][pAdmin] < 6) return PermissionError(playerid);
    Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
    return 1;
}

Dialog:TuneMain(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:  Dialog_Show(playerid, TunePaintjob, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\nPaint Job 4\nPaint Job 5\n \nBack", "Apply", "Close");
            case 1:  Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            case 2:  Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
            case 3:  Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
            case 4:  Dialog_Show(playerid, TuneLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "Apply", "Close");
            case 5:  Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
            case 6:  Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
            case 7:  Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
            case 8:  Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
            case 9:  Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
            case 10: Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
            case 11: Dialog_Show(playerid, TuneBullbars, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "Apply", "Close");
            case 12: Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            case 13: Dialog_Show(playerid, TuneStreo, DIALOG_STYLE_LIST, "Car Stereo", "Bass Boost\n \nBack", "Apply", "Close");
            case 14: Dialog_Show(playerid, TuneHydraulic, DIALOG_STYLE_LIST, "Hydaulics", "Hydaulics\n \nBack", "Apply", "Close");
            case 15: Dialog_Show(playerid, TuneNitro, DIALOG_STYLE_LIST, "Nitrous Oxide", "2x Nitrous\n5x Nitrous\n10x Nitrous\n \nBack", "Apply", "Close");
        }
    }
    return 1;
}

Dialog:TunePaintjob(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:// Paintjobs
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 || // Broadway
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 535 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehiclePaintjob(car,0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added paintjob to car");
                Dialog_Show(playerid, TunePaintjob, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\nPaint Job 4\nPaint Job 5\n \nBack", "Apply", "Close");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
            }
                else
            {
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"Paintjob is only for Wheel Arch Angrls and Loco Low Co types of cars");
                Dialog_Show(playerid, TunePaintjob, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\nPaint Job 4\nPaint Job 5\n \nBack", "Apply", "Close");
            }
            }
            case 1: // Colors
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 || // Broadway
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 535 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehiclePaintjob(car,1);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added paintjob to car");
                Dialog_Show(playerid, TunePaintjob, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\nPaint Job 4\nPaint Job 5\n \nBack", "Apply", "Close");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
            }
                else
            {
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"Paintjob is only for Wheel Arch Angrls and Loco Low Co types of cars");
                Dialog_Show(playerid, TunePaintjob, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\nPaint Job 4\nPaint Job 5\n \nBack", "Apply", "Close");
            }
            }
            case 2: // Exhausts
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 || // Broadway
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 535 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehiclePaintjob(car,2);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added paintjob to car");
                Dialog_Show(playerid, TunePaintjob, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\nPaint Job 4\nPaint Job 5\n \nBack", "Apply", "Close");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
            }
                else
            {
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"Paintjob is only for Wheel Arch Angrls and Loco Low Co types of cars");
                Dialog_Show(playerid, TunePaintjob, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\nPaint Job 4\nPaint Job 5\n \nBack", "Apply", "Close");
            }
            }
            case 3: // Front Bumpers
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 || // Broadway
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 535 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehiclePaintjob(car,3);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added paintjob to car");
                Dialog_Show(playerid, TunePaintjob, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\nPaint Job 4\nPaint Job 5\n \nBack", "Apply", "Close");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
            }
                else
            {
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"Paintjob is only for Wheel Arch Angrls and Loco Low Co types of cars");
                Dialog_Show(playerid, TunePaintjob, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\nPaint Job 4\nPaint Job 5\n \nBack", "Apply", "Close");
            }
            }
            case 4: // Rear Bumpers
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 || // Broadway
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 535 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehiclePaintjob(car,4);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added paintjob to car");
                Dialog_Show(playerid, TunePaintjob, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\nPaint Job 4\nPaint Job 5\n \nBack", "Apply", "Close");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
            }
                else
            {
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"Paintjob is only for Wheel Arch Angrls and Loco Low Co types of cars");
                Dialog_Show(playerid, TunePaintjob, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\nPaint Job 4\nPaint Job 5\n \nBack", "Apply", "Close");
            }
            }
            case 5:
            {
                Dialog_Show(playerid, TunePaintjob, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\nPaint Job 4\nPaint Job 5\n \nBack", "Apply", "Close");
            }
            case 6:
            {
                Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneColor(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,0,0);
                //GivePlayerMoney(playerid,-150);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);

            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 1:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,1,1);
            //    GivePlayerMoney(playerid,-150);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 2:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,3,3);
                //  GivePlayerMoney(playerid,-150);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 3:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,79,79);
                //   GivePlayerMoney(playerid,-150);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 4:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,86,86);
                //   GivePlayerMoney(playerid,-150);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 5:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,6,6);
                //  GivePlayerMoney(playerid,-150);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 6:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,126,126);
            //      GivePlayerMoney(playerid,-150);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 7:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,66,66);
            //    GivePlayerMoney(playerid,-150);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 8:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,24,24);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 9:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,123,123);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 10:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,53,53);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 11:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,93,93);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 12:
            {
                    if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,83,83);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
                    else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 13:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,60,60);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 14:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,161,161);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 15:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                ChangeVehicleColor(car,153,153);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully repainted to car");
                PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            }
            case 16:
            {
                Dialog_Show(playerid, TuneColor, DIALOG_STYLE_LIST, "Colors", "Black\nWhite\nRed\nBlue\nGreen\nYellow\nPink\nBrown\nGrey\nGold\nDark Blue\nLight Blue\nCold Green\nLight Grey\nDark Red\nDark Brown\n \nBack", "Apply", "Close");
            }
            case 17:
            {
                Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneExhaust(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562)
                {
                    AddVehicleComponent(car,1034);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565)
                {
                    AddVehicleComponent(car,1046);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559)
                {
                    AddVehicleComponent(car,1065);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561)
                {
                    AddVehicleComponent(car,1064);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
                {
                    AddVehicleComponent(car,1028);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)
                {
                    AddVehicleComponent(car,1089);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
            }
            case 1:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)

            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562)
                {
                    AddVehicleComponent(car,1037);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565)
                {
                    AddVehicleComponent(car,1045);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559)
                {
                    AddVehicleComponent(car,1066);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561)
                {
                    AddVehicleComponent(car,1059);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
                {
                    AddVehicleComponent(car,1029);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)
                {
                    AddVehicleComponent(car,1092);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
            }
            case 2:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)

            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
                {
                    AddVehicleComponent(car,1044);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)// Remington
                {
                    AddVehicleComponent(car,1126);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)// Savanna
                {
                    AddVehicleComponent(car,1129);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
                {
                    AddVehicleComponent(car,1104);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
                {
                    AddVehicleComponent(car,1113);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
                {
                    AddVehicleComponent(car,1136);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
            }
            case 3:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)
            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
                {
                    AddVehicleComponent(car,1043);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)// Remington
                {
                    AddVehicleComponent(car,1127);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)// Savanna
                {
                    AddVehicleComponent(car,1132);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
                {
                    AddVehicleComponent(car,1105);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }

                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
                {
                    AddVehicleComponent(car,1114);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }

                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
                {
                    AddVehicleComponent(car,1135);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }

                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                }
            }
            case 4:// Large
            {
                if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 527 ||//cadrona
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 542 ||//clover
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||//club
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 400 ||//landstalker
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||//premier
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ||//sentinel
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 580 ||//stafford
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 549 ||//tampa
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)//zr-350
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527) // cadrona
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542) // clover
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589) // club
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400) // landstalker
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 580) // stafford
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // zr-350
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
                    {
                    AddVehicleComponent(car,1020);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                }
                else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
            }
            case 5: // Medium
            {
                    if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 527 ||//cadrona
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 542 ||//clover
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 400 ||//landstalker
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||//premier
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||//previon
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ||//sentinel
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)//zr-350
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527) // cadrona
                    {
                    AddVehicleComponent(car,1021);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542) // clover
                    {
                    AddVehicleComponent(car,1021);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400) // landstalker
                    {
                    AddVehicleComponent(car,1021);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426) // premier
                    {
                    AddVehicleComponent(car,1021);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
                    {
                    AddVehicleComponent(car,1021);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
                    {
                    AddVehicleComponent(car,1021);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
                    {
                    AddVehicleComponent(car,1021);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // zr350
                    {
                    AddVehicleComponent(car,1021);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
            }
            case 6: // Small
            {
                    if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 436)//previon
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
                    {
                    AddVehicleComponent(car,1022);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
            }
            case 7: // Twin
            {
                    if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||//cheetah
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 542 ||//clover
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 400 ||//landstalker
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||//premier
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||//previon
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ||//sentinel
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 549 ||//tampa
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)//zr-350
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 415) // cheetah
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542) // clover
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400) // landstalker
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426) // premier
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ) // sentinel
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // zr-350
                    {
                    AddVehicleComponent(car,1019);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
            }
            case 8: // Upswept
            {
                    if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||//cheetah
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 542 ||//clover
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 400 ||//landstalker
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||//premier
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||//cheetah
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ||//sentinel
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 549 ||//tampa
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)//zr-350
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 415) // cheetah
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527) // cadrona
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542) // clover
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589) // club
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400) // landstalker
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 580) // stafford
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
                    {
                    AddVehicleComponent(car,1018);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // zr-350
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
                    {
                    AddVehicleComponent(car,1018);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
                    }
            }
            case 9: // _
            {
            Dialog_Show(playerid, TuneExhaust, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "Apply", "Close");
            }
            case 10: // Back
            {
            Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneFBumps(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
                {
                    AddVehicleComponent(car,1171);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
                {
                    AddVehicleComponent(car,1153);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jester
                {
                    AddVehicleComponent(car,1160);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
                {
                    AddVehicleComponent(car,1155);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
                {
                    AddVehicleComponent(car,1169);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558) // Uranus
                {
                    AddVehicleComponent(car,1166);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
            }
            case 1:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
            {

                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
                {
                    AddVehicleComponent(car,1172);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
                {
                    AddVehicleComponent(car,1152);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jetser
                {
                    AddVehicleComponent(car,1173);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
                {
                    AddVehicleComponent(car,1157);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
                {
                    AddVehicleComponent(car,1170);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)  // Uranus
                {
                    AddVehicleComponent(car,1165);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
            }
            case 2:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)
            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
                {
                    AddVehicleComponent(car,1174);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)// Remington
                {
                    AddVehicleComponent(car,1179);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)// Savanna
                {
                    AddVehicleComponent(car,1189);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
                {
                    AddVehicleComponent(car,1182);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
                {
                    AddVehicleComponent(car,1115);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
                {
                    AddVehicleComponent(car,1191);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
            }
            case 3:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 535 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 576)
            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
                {
                    AddVehicleComponent(car,1175);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)// Remington
                {
                    AddVehicleComponent(car,1185);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)// Savanna
                {
                    AddVehicleComponent(car,1188);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
                {
                    AddVehicleComponent(car,1181);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }

                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
                {
                    AddVehicleComponent(car,1116);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
                {
                    AddVehicleComponent(car,1190);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }

                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
            }
            case 4:
            {
            Dialog_Show(playerid, TuneFBumps, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "Apply", "Close");
            }
            case 5:
            {
            Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneRBumps(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
            {

                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
                {
                    AddVehicleComponent(car,1149);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
                {
                    AddVehicleComponent(car,1150);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jester
                {
                    AddVehicleComponent(car,1159);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
                {
                    AddVehicleComponent(car,1154);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
                {
                    AddVehicleComponent(car,1141);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558) // Uranus
                {
                    AddVehicleComponent(car,1168);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
            }
            case 1:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
            {


                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
                {
                    AddVehicleComponent(car,1148);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"YComponent successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
                {
                    AddVehicleComponent(car,1151);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jetser
                {
                    AddVehicleComponent(car,1161);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
                {
                    AddVehicleComponent(car,1156);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
                {
                    AddVehicleComponent(car,1140);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)  // Uranus
                {
                    AddVehicleComponent(car,1167);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
            }
            case 2:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
            {


                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
                {
                    AddVehicleComponent(car,1148);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
                {
                    AddVehicleComponent(car,1151);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jetser
                {
                    AddVehicleComponent(car,1161);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
                {
                    AddVehicleComponent(car,1156);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
                {
                    AddVehicleComponent(car,1140);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)  // Uranus
                {
                    AddVehicleComponent(car,1167);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                }
                    else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
            }
            case 3:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)
            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
                {
                    AddVehicleComponent(car,1177);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)// Remington
                {
                    AddVehicleComponent(car,1178);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)// Savanna
                {
                    AddVehicleComponent(car,1186);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
                {
                    AddVehicleComponent(car,1183);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }

                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
                {
                    AddVehicleComponent(car,1110);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }

                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
                {
                    AddVehicleComponent(car,1193);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }

                }
                    else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
                }
            }
            case 4:
            {
                Dialog_Show(playerid, TuneRBumps, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "Apply", "Close");
            }
            case 5:
            {
                Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneRoof(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
            {

                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
                {
                    AddVehicleComponent(car,1038);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
                {
                    AddVehicleComponent(car,1054);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jester
                {
                    AddVehicleComponent(car,1067);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
                {
                    AddVehicleComponent(car,1055);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
                {
                    AddVehicleComponent(car,1032);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558) // Uranus
                {
                    AddVehicleComponent(car,1088);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                }
                    else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
            }
            case 1:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
            {


                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
                {
                    AddVehicleComponent(car,1035);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
                {
                    AddVehicleComponent(car,1053);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jetser
                {
                    AddVehicleComponent(car,1068);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
                {
                    AddVehicleComponent(car,1061);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
                {
                    AddVehicleComponent(car,1033);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)  // Uranus
                {
                    AddVehicleComponent(car,1091);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                }
                    else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
            }
            case 2:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 536)
            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567) // Savanna
                {
                    AddVehicleComponent(car,1130);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
                {
                    AddVehicleComponent(car,1128);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                }
                    else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
            }
            case 3:
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 536)
            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567) // Savanna
                {
                    AddVehicleComponent(car,1131);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                    else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
                {
                    AddVehicleComponent(car,1103);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
                }
                    else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
                }
            }
            case 4:
            {
                if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 492 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 580 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 550||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401)
                    {
                    AddVehicleComponent(car,1006);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Roof Scoop\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518)
                    {
                    AddVehicleComponent(car,1006);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Roof Scoop\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589)
                    {
                    AddVehicleComponent(car,1006);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Roof Scoop\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 492)
                    {
                    AddVehicleComponent(car,1006);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Roof Scoop\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546)
                    {
                    AddVehicleComponent(car,1006);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Roof Scoop\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603)
                    {
                    AddVehicleComponent(car,1006);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Roof Scoop\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426)
                    {
                    AddVehicleComponent(car,1006);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Roof Scoop\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436)
                    {
                    AddVehicleComponent(car,1006);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Roof Scoop\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 580)
                    {
                    AddVehicleComponent(car,1006);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Roof Scoop\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550)
                    {
                    AddVehicleComponent(car,1006);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Roof Scoop\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)
                    {
                    AddVehicleComponent(car,1006);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Roof Scoop\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Roof Scoop\n \nBack", "Apply", "Close");
                    }
            }
            case 5:
            {
                Dialog_Show(playerid, TuneRoof, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "Apply", "Close");
            }
            case 6:
            {
            Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneSpoiler(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
            {

                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
                {
                    AddVehicleComponent(car,1147);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
                {
                    AddVehicleComponent(car,1049);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jester
                {
                    AddVehicleComponent(car,1162);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
                {
                    AddVehicleComponent(car,1158);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
                {
                    AddVehicleComponent(car,1138);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558) // Uranus
                {
                    AddVehicleComponent(car,1164);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
            }
            case 1:
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
            {


                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
                {
                    AddVehicleComponent(car,1146);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
                {
                    AddVehicleComponent(car,1150);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jetser
                {
                    AddVehicleComponent(car,1158);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
                {
                    AddVehicleComponent(car,1060);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
                {
                    AddVehicleComponent(car,1139);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)  // Uranus
                {
                    AddVehicleComponent(car,1163);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                }
            }
            case 2:// Win
            {
            if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 527 ||//cadrona
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||//cheetah
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||//premier
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||//previon
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ||//sentinel
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 477 ||//stallion
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 580 ||//stafford
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)//tampa
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527) // cadrona
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 415) // cheetah
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426) // premier
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // stallion
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 580) // stafford
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
                    {
                    AddVehicleComponent(car,1001);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
            }
            case 3: // Fury
            {
                    if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||//cheetah
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ||//sentinel
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 477 ||//stallion
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 580 ||//stafford
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)//tampa
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
                    {
                    AddVehicleComponent(car,1023);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 415) // cheetah
                    {
                    AddVehicleComponent(car,1023);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
                    {
                    AddVehicleComponent(car,1023);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
                    {
                    AddVehicleComponent(car,1023);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
                    {
                    AddVehicleComponent(car,1023);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
                    {
                    AddVehicleComponent(car,1023);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // stallion
                    {
                    AddVehicleComponent(car,1023);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 580) // stafford
                    {
                    AddVehicleComponent(car,1023);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
                    {
                    AddVehicleComponent(car,1023);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
                    {
                    AddVehicleComponent(car,1023);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
            }
            case 4: // Alpha
            {
                    if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||//cheetah
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||//premier
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||//previon
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 477 ||//stallion
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)//tampa
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
                    {
                    AddVehicleComponent(car,1003);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 415) // cheetah
                    {
                    AddVehicleComponent(car,1003);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
                    {
                    AddVehicleComponent(car,1003);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
                    {
                    AddVehicleComponent(car,1003);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426) // premier
                    {
                    AddVehicleComponent(car,1003);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
                    {
                    AddVehicleComponent(car,1003);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // stallion
                    {
                    AddVehicleComponent(car,1003);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
                    {
                    AddVehicleComponent(car,1003);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
                    {
                    AddVehicleComponent(car,1003);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
                    {
                    AddVehicleComponent(car,1003);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
            }
            case 5: // Pro
            {
                    if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||//club
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 492 ||//greenwood
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 405)//sentinel
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // club
                    {
                    AddVehicleComponent(car,1000);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 492) // greenwood
                    {
                    AddVehicleComponent(car,1000);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
                    {
                    AddVehicleComponent(car,1000);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
                    {
                    AddVehicleComponent(car,1000);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
            }
            case 6: // Champ
            {
                    if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 527 ||//cadrona
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 542 ||//clover
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 405)//sentinel
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527) // cadrona
                    {
                    AddVehicleComponent(car,1014);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542) // clover
                    {
                    AddVehicleComponent(car,1014);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
                    {
                    AddVehicleComponent(car,1014);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
            }
            case 7: // Race
            {
            if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 527 ||//cadrona
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 542)//clover
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527) // cadrona
                    {
                    AddVehicleComponent(car,1014);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542) // clover
                    {
                    AddVehicleComponent(car,1014);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
            }
            case 8: // Drag
            {
            if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 517)//majestic
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
                    {
                    AddVehicleComponent(car,1002);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
                    {
                    AddVehicleComponent(car,1002);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
                    }
            }
            case 9:
            {
            Dialog_Show(playerid, TuneSpoiler, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "Apply", "Close");
            }
            case 10:
            {
            Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneSidekirt(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
            {

                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
                {
                    AddVehicleComponent(car,1036);
                    AddVehicleComponent(car,1040);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
                {
                    AddVehicleComponent(car,1047);
                    AddVehicleComponent(car,1051);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jester
                {
                    AddVehicleComponent(car,1069);
                    AddVehicleComponent(car,1071);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"YComponent successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
                {
                    AddVehicleComponent(car,1056);
                    AddVehicleComponent(car,1062);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
                {
                    AddVehicleComponent(car,1026);
                    AddVehicleComponent(car,1027);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558) // Uranus
                {
                    AddVehicleComponent(car,1090);
                    AddVehicleComponent(car,1094);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
            }
            case 1:
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
            {


                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
                {
                    AddVehicleComponent(car,1039);
                    AddVehicleComponent(car,1041);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
                {
                    AddVehicleComponent(car,1048);
                    AddVehicleComponent(car,1052);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jetser
                {
                    AddVehicleComponent(car,1070);
                    AddVehicleComponent(car,1072);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
                {
                    AddVehicleComponent(car,1057);
                    AddVehicleComponent(car,1063);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
                {
                    AddVehicleComponent(car,1031);
                    AddVehicleComponent(car,1030);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)  // Uranus
                {
                    AddVehicleComponent(car,1093);
                    AddVehicleComponent(car,1095);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
            }
            case 2:
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)
                {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
                {
                    AddVehicleComponent(car,1042);
                    AddVehicleComponent(car,1099);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567) // Savanna
                {
                    AddVehicleComponent(car,1102);
                    AddVehicleComponent(car,1133);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
                {
                    AddVehicleComponent(car,1134);
                    AddVehicleComponent(car,1137);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
                {
                    AddVehicleComponent(car,1108);
                    AddVehicleComponent(car,1107);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
            }
            case 3:
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)
            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534) // Remington
                {
                    AddVehicleComponent(car,1122);
                    AddVehicleComponent(car,1101);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car.");
                Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
            }
            case 4:
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
            GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)
            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534) // Remington
                {
                    AddVehicleComponent(car,1106);
                    AddVehicleComponent(car,1124);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car. ");
                Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
            }
            case 5:
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)

            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
                {
                    AddVehicleComponent(car,1118);
                    AddVehicleComponent(car,1120);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car. ");
                Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
            }
            case 6:
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)

            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
                {
                    AddVehicleComponent(car,1119);
                    AddVehicleComponent(car,1121);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car. ");
                Dialog_Show(playerid, TuneSidekirt, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "Apply", "Close");
                }
            }
        }
    }
    return 1;
}

Dialog:TuneBullbars(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)

            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534) // Remington
                {
                    AddVehicleComponent(car,1100);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneBullbars, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car. ");
                Dialog_Show(playerid, TuneBullbars, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "Apply", "Close");
                }
            }
            case 1: 
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)

            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534) // Remington
                {
                    AddVehicleComponent(car,1123);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneBullbars, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car. ");
                Dialog_Show(playerid, TuneBullbars, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "Apply", "Close");
                }
            }
            case 2:
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)

            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534) // Remington
                {
                    AddVehicleComponent(car,1125);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneBullbars, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] You cannot install this component to your car. ");
                Dialog_Show(playerid, TuneBullbars, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "Apply", "Close");
                }
            }
            case 3:
            {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)

            {
                new car = GetPlayerVehicleID(playerid);
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
                {
                    AddVehicleComponent(car,1117);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                    Dialog_Show(playerid, TuneBullbars, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "Apply", "Close");
                }
                }
                else
                {
                SendClientMessage(playerid,COLOR_YELLOW,"[WARNING] ou cannot install this component to your car. ");
                Dialog_Show(playerid, TuneBullbars, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "Apply", "Close");
                }
            }
            case 4:
            {
            Dialog_Show(playerid, TuneBullbars, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "Apply", "Close");
            }
            case 5:
            {
            Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneWheels(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1025);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Offroad Wheels ");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 1:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1074);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Mega Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 2:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1076);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Wires Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 3:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1078);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Twist Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 4:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1081);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Grove Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 5:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1082);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Import Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 6:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1085);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Atomic Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 7:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1096);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Ahab Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 8:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1097);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Virtual Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 9:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1098);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Access Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 10:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1084);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Trance Wheels ");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 11:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1073);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Shadow Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 12:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1075);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Rimshine Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 13:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1077);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Classic Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 14:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1079);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Cutter Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 15:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1080);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Switch Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 16:
            {
                if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1083);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You have succesfully added Dollar Wheels");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
                else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            }
            case 17:
            {
                Dialog_Show(playerid, TuneWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "Apply", "Close");
            }
            case 18:
            {
            Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneStreo(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:
            {
                if(GetPlayerMoney(playerid) >= 0)
                {
                    new car = GetPlayerVehicleID(playerid);
                    AddVehicleComponent(car,1086);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added. ");
                    Dialog_Show(playerid, TuneStreo, DIALOG_STYLE_LIST, "Car Stereo", "Bass Boost\n \nBack", "Apply", "Close");
                }
                else
                {
                    SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                    Dialog_Show(playerid, TuneStreo, DIALOG_STYLE_LIST, "Car Stereo", "Bass Boost\n \nBack", "Apply", "Close");
                }
            }
            case 1:
            {
                Dialog_Show(playerid, TuneStreo, DIALOG_STYLE_LIST, "Car Stereo", "Bass Boost\n \nBack", "Apply", "Close");
            }
            case 2:
            {
                Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneHydraulic(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1087);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added. ");
                Dialog_Show(playerid, TuneHydraulic, DIALOG_STYLE_LIST, "Hydaulics", "Hydaulics\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneHydraulic, DIALOG_STYLE_LIST, "Hydaulics", "Hydaulics\n \nBack", "Apply", "Close");
            }
            }
            case 1:
            {
            Dialog_Show(playerid, TuneHydraulic, DIALOG_STYLE_LIST, "Hydaulics", "Hydaulics\n \nBack", "Apply", "Close");
            }
            case 2:
            {
            Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneNitro(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1008);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added. ");
                Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
            }
            case 1:
            {
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1009);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
            }
            case 2:
            if(GetPlayerMoney(playerid) >= 0)
            {
                new car = GetPlayerVehicleID(playerid);
                AddVehicleComponent(car,1010);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added.");
                Dialog_Show(playerid, TuneNitro, DIALOG_STYLE_LIST, "Nitrous Oxide", "2x Nitrous\n5x Nitrous\n10x Nitrous\n \nBack", "Apply", "Close");
            }
            else
            {
                SendClientMessage(playerid,COLOR_RED,"Not enough money!");
                Dialog_Show(playerid, TuneNitro, DIALOG_STYLE_LIST, "Nitrous Oxide", "2x Nitrous\n5x Nitrous\n10x Nitrous\n \nBack", "Apply", "Close");
            }
            case 3:
            {
            Dialog_Show(playerid, TuneNitro, DIALOG_STYLE_LIST, "Nitrous Oxide", "2x Nitrous\n5x Nitrous\n10x Nitrous\n \nBack", "Apply", "Close");
            }
            case 4:
            {
            Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneHoods(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:// fury
            {
                if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 492 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 550)
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
                    {
                    AddVehicleComponent(car,1005);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
                    {
                    AddVehicleComponent(car,1005);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589) // club
                    {
                    AddVehicleComponent(car,1005);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 492) // greenwood
                    {
                    AddVehicleComponent(car,1005);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426) // premier
                    {
                    AddVehicleComponent(car,1005);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
                    {
                    AddVehicleComponent(car,1005);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                }
                else
                {
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                }
            }
            case 1: // Champ
            {
            if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 492 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 550)
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
                    {
                    AddVehicleComponent(car,1004);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
                    {
                    AddVehicleComponent(car,1004);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 492) // greenwood
                    {
                    AddVehicleComponent(car,1004);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426) // premier
                    {
                    AddVehicleComponent(car,1004);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
                    {
                    AddVehicleComponent(car,1004);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                }
                else
                {
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                }
            }
            case 2: // Race
            {
            if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
                    {
                    AddVehicleComponent(car,1011);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                }
                else
                {
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                }
            }
            case 3: // Worx
            {
            if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
                    {
                    AddVehicleComponent(car,1012);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added");
                    Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                    }
                }
                else
                {
                SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
                }
            }
            case 4:
            {
            Dialog_Show(playerid, TuneHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "Apply", "Close");
            }
            case 5: // Back
            {
            Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneVents(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:// Oval
            {
                if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 439 ||//stallion
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)//tampa
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
                    {
                    AddVehicleComponent(car,1142);
                    AddVehicleComponent(car,1143);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
                    {
                    AddVehicleComponent(car,1142);
                    AddVehicleComponent(car,1143);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
                    {
                    AddVehicleComponent(car,1142);
                    AddVehicleComponent(car,1143);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
                    {
                    AddVehicleComponent(car,1142);
                    AddVehicleComponent(car,1143);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
                    {
                    AddVehicleComponent(car,1142);
                    AddVehicleComponent(car,1143);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
                    {
                    AddVehicleComponent(car,1142);
                    AddVehicleComponent(car,1143);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 439) // stallion
                    {
                    AddVehicleComponent(car,1142);
                    AddVehicleComponent(car,1143);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
                    {
                    AddVehicleComponent(car,1142);
                    AddVehicleComponent(car,1143);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
                    {
                    AddVehicleComponent(car,1142);
                    AddVehicleComponent(car,1143);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                }
                else
                    {
                        SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                        Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
            }
            case 1: // Square
            {
            if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||//club
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 439 ||//stallion
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)//tampa
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
                    {
                    AddVehicleComponent(car,1144);
                    AddVehicleComponent(car,1145);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
                    {
                    AddVehicleComponent(car,1144);
                    AddVehicleComponent(car,1145);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589) // club
                    {
                    AddVehicleComponent(car,1144);
                    AddVehicleComponent(car,1145);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
                    {
                    AddVehicleComponent(car,1144);
                    AddVehicleComponent(car,1145);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
                    {
                    AddVehicleComponent(car,1144);
                    AddVehicleComponent(car,1145);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
                    {
                    AddVehicleComponent(car,1144);
                    AddVehicleComponent(car,1145);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 439) // stallion
                    {
                    AddVehicleComponent(car,1144);
                    AddVehicleComponent(car,1145);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
                    {
                    AddVehicleComponent(car,1144);
                    AddVehicleComponent(car,1145);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
                    {
                    AddVehicleComponent(car,1144);
                    AddVehicleComponent(car,1145);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                }
                    else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
            }
            case 2: // _
            {
            Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
            }
            case 3: // Back
            {
            Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}

Dialog:TuneLight(playerid, response, listitem, inputtext[]) 
{
    if(!response)
    {
        SetCameraBehindPlayer(playerid);
    }
    if(response)
    {
        switch(listitem)// Checking which list item was selected
        {
            case 0:// round
            {
                if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||//club
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 400 ||//landstalker
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||//previon
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 439)//stallion
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
                    {
                    AddVehicleComponent(car,1013);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendClientMessage(playerid,COLOR_WHITE,"[INFO]Component successfully added");
                    Dialog_Show(playerid, TuneLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
                    {
                    AddVehicleComponent(car,1013);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589) // club
                    {
                    AddVehicleComponent(car,1013);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400) // landstalker
                    {
                    AddVehicleComponent(car,1013);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
                    {
                    AddVehicleComponent(car,1013);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 439) // stallion
                    {
                    AddVehicleComponent(car,1013);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "Apply", "Close");
                    }
                }
                else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "Apply", "Close");
                    }
            }
            case 1: // Square
            {
            if(
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||//club
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
                GetVehicleModel(GetPlayerVehicleID(playerid)) == 400)//landstalker
                {
                    new car = GetPlayerVehicleID(playerid);
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589) // club
                    {
                    AddVehicleComponent(car,1024);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
                    {
                    AddVehicleComponent(car,1024);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400) // landstalker
                    {
                    AddVehicleComponent(car,1024);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"Component successfully added");
                    Dialog_Show(playerid, TuneVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "Apply", "Close");
                    }
                }
                else
                    {
                    SendCustomMessage(playerid, "MOD", ""YELLOW_E"You cannot install this component on your car.");
                    Dialog_Show(playerid, TuneLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "Apply", "Close");
                    }
            }
            case 2: // _
            {
            Dialog_Show(playerid, TuneLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "Apply", "Close");
            }
            case 3: // Back
            {
            Dialog_Show(playerid, TuneMain, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide\nRepair Car", "Enter", "Close");
            }
        }
    }
    return 1;
}
