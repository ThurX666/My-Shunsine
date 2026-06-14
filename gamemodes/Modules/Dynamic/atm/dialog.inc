
Dialog:DialogATM(playerid, response, listitem, inputtext[]) {
    if(!response) return 1;
    switch(listitem)
    {
        case 0: // Check Balance
        {
            new mstr[512];
            format(mstr, sizeof(mstr), "{F6F6F6}You have "LB_E"$%s {F6F6F6}in your bank account.", FormatMoney(pData[playerid][pBankMoney]));
            Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""LB_E"Bank", mstr, "Close", "");
        }
        case 1: // Withdraw
        {
            new mstr[128];			
            format(mstr, sizeof(mstr), ""WHITE_E"My Balance: "LB_E"$%s", FormatMoney(pData[playerid][pBankMoney]));
            Dialog_Show(playerid, DialogATMWithdraw, DIALOG_STYLE_LIST, mstr, "$50.00\n$200.00\n$500.00\n$1,000.00\n$5,000.00", "Withdraw", "Cancel");
        }
        case 2: //Paycheck
        {
            if(pData[playerid][pPaycheck] <= 3600) return Error(playerid, "Sekarang belum waktunya anda mengambil paycheck.");
            DisplayPaycheck(playerid);
        }
    }
    return 1;
}

Dialog:DialogATMWithdraw(playerid, response, listitem, inputtext[]) {
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(pData[playerid][pBankMoney] < 5000)
                    return Error(playerid, "Not enough balance!");
                
                GivePlayerMoneyEx(playerid, 5000);
                pData[playerid][pBankMoney] -= 5000;
                SendClientMessageEx(playerid, COLOR_ARWIN, "ATMINFO: "WHITE_E"You withdraw "LG_E"$50.00");
            }
            case 1:
            {
                if(pData[playerid][pBankMoney] < 20000)
                    return Error(playerid, "Not enough balance!");
                
                GivePlayerMoneyEx(playerid, 20000);
                pData[playerid][pBankMoney] -= 20000;
                SendClientMessageEx(playerid, COLOR_ARWIN, "ATMINFO: "WHITE_E"You withdraw "LG_E"$200.00");
            }
            case 2:
            {
                if(pData[playerid][pBankMoney] < 50000)
                    return Error(playerid, "Not enough balance!");
                
                GivePlayerMoneyEx(playerid, 50000);
                pData[playerid][pBankMoney] -= 50000;
                SendClientMessageEx(playerid, COLOR_ARWIN, "ATMINFO: "WHITE_E"You withdraw "LG_E"$500.00");
            }
            case 3:
            {
                if(pData[playerid][pBankMoney] < 100000)
                    return Error(playerid, "Not enough balance!");
                
                GivePlayerMoneyEx(playerid, 100000);
                pData[playerid][pBankMoney] -= 100000;
                SendClientMessageEx(playerid, COLOR_ARWIN, "ATMINFO: "WHITE_E"You withdraw "LG_E"$1,000.00");
            }
            case 4:
            {
                if(pData[playerid][pBankMoney] < 500000)
                    return Error(playerid, "Not enough balance!");
                
                GivePlayerMoneyEx(playerid, 500000);
                pData[playerid][pBankMoney] -= 500000;
                SendClientMessageEx(playerid, COLOR_ARWIN, "ATMINFO: "WHITE_E"You withdraw "LG_E"$5,000.00");
            }
        }
    }
    return 1;
}
