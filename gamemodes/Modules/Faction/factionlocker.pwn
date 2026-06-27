
CMD:locker(playerid, params[])
{
	if(pData[playerid][pFaction] < 1)
			return Error(playerid, "You cant use this commands!");

    if(pData[playerid][pAdminDuty] == 1)
        return Error(playerid, "You cannot be on duty faction if you are on admin duty");
		
	foreach(new lid : Lockers)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, lData[lid][lPosX], lData[lid][lPosY], lData[lid][lPosZ]))
		{
			if(pData[playerid][pFaction] == 1 && pData[playerid][pFaction] == lData[lid][lType])
			{
				Dialog_Show(playerid, LockerSAPD, DIALOG_STYLE_LIST, "SAPD Lockers", "Toggle Duty\nHealth\nArmour\nWeapons\nClothing\nUndercover\nClothes (0.3DL ONLY)\nFaction Bank", "Proceed", "Cancel");
			}
			else if(pData[playerid][pFaction] == 3 && pData[playerid][pFaction] == lData[lid][lType])
			{
				Dialog_Show(playerid, LockerSAMD, DIALOG_STYLE_LIST, "SAMD Lockers", "Toggle Duty\nClothing\nMedicine\nMedkit\nFaction Bank", "Proceed", "Cancel");
			}
			else if(pData[playerid][pFaction] == 4 && pData[playerid][pFaction] == lData[lid][lType])
			{
				Dialog_Show(playerid, LockerSANews, DIALOG_STYLE_LIST, "SANA Lockers", "Toggle Duty\nClothing\nFaction Bank", "Proceed", "Cancel");
			}
			else return Error(playerid, "You are not in this faction type!");
		}
	}
	return 1;
}

Dialog:LockerSAPD(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch (listitem) 
        {
            case 0: 
            {
                if(pData[playerid][pOnDuty] == 1)
                {
                    pData[playerid][pTogFaction] = 1;
                    pData[playerid][pOnDuty] = 0;
                    SetPlayerColor(playerid, COLOR_WHITE);
                    format(pData[playerid][pUnit], 24, ""RED_E"UNNASSIGNED");
                    if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                        UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s (%d)", pData[playerid][pName], playerid)));
                    SetPlayerSkin(playerid, pData[playerid][pSkin]);
                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s places their badge and gun in their locker.", ReturnName(playerid));
                    ResetWeapons(playerid);
                }
                else
                {
                    pData[playerid][pTogFaction] = 0;
                    pData[playerid][pOnDuty] = 1;
                    SetFactionColor(playerid);
                    if(pData[playerid][pGender] == 1)
                    {
                        SetPlayerSkin(playerid, 300);
                        pData[playerid][pFacSkin] = 300;
                    }
                    else
                    {
                        SetPlayerSkin(playerid, 306);
                        pData[playerid][pFacSkin] = 306;
                    }
                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s withdraws their badge and on duty from their locker", ReturnName(playerid));
                }
            }
            case 1: 
            {
                SetPlayerHealthEx(playerid, 100);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s telah mengambil medical kit dari locker", ReturnName(playerid));
            }
            case 2:
            {
                SetPlayerArmourEx(playerid, 100);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s telah mengambil armour pelindung dari locker", ReturnName(playerid));
            }
            case 3:
            {
                if(pData[playerid][pOnDuty] <= 0)
                    return Error(playerid, "You must be on duty first, before opening your locker!");
                    
                Dialog_Show(playerid, LockerWeaponSAPD, DIALOG_STYLE_LIST, "SAPD Weapons", "SPRAYCAN\nPARACHUTE\nNITE STICK\nKNIFE\nCOLT45\nSILENCED\nDEAGLE\nSHOTGUN\nSHOTGSPA\nMP5\nM4\nRIFLE\nSNIPER", "Pilih", "Batal");
            }
            case 4:
            {
                if(pData[playerid][pOnDuty] <= 0)
                    return Error(playerid, "You must be on duty first, before opening your locker!");
                
                switch (pData[playerid][pGender])
                {
                    case 1: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SAPDMale, "LSPD:", sapdmale, sizeof(sapdmale));
                    case 2: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SAPDFemale, "LSPD:", sapdfemale, sizeof(sapdfemale));
                }
            }
            case 5:
            {
                if(pData[playerid][pOnDuty] <= 0)
                    return Error(playerid, "You must be on duty first, before opening your locker!");
                if(pData[playerid][pFactionRank] < 3)
                    return Error(playerid, "You are not allowed!");
                
                switch (pData[playerid][pGender])
                {
                    case 1: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SAPDWar, "LSPD:", sapdwar, sizeof(sapdwar));
                    case 2: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SAPDFemale, "LSPD:", sapdfemale, sizeof(sapdfemale));
                }
            }
            case 6:
            {
                if(pData[playerid][pOnDuty] <= 0)
                    return Error(playerid, "You must be on duty first, before opening your locker!");
                
                switch (pData[playerid][pGender])
                {
                    case 1: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SAPDMale, "LSPD 0.3DL:", sapdmale03dl, sizeof(sapdmale03dl));
                }
            }
            case 7:
            {
                ShowFactionBankMenu(playerid);
            }
        }
    }
    return 1;
}

stock ShowFactionBankMenu(playerid)
{
    new title[64], balance[32], faction = pData[playerid][pFaction];
    switch(faction)
    {
        case 1: format(balance, sizeof(balance), FormatMoney(FactionBankSAPD));
        case 2: format(balance, sizeof(balance), FormatMoney(FactionBankSAGS));
        case 3: format(balance, sizeof(balance), FormatMoney(FactionBankSAMD));
        case 4: format(balance, sizeof(balance), FormatMoney(FactionBankSAN));
    }
    switch(faction)
    {
        case 1: title = "SAPD Faction Bank";
        case 2: title = "SAGS Faction Bank";
        case 3: title = "SAMD Faction Bank";
        case 4: title = "SANA Faction Bank";
    }
    new info[256];
    format(info, sizeof(info), "Balance: "GREEN_E"$%s\n\n"WHITE_E"Deposit\nWithdraw\nTransaction History", balance);
    Dialog_Show(playerid, FactionBankMenu, DIALOG_STYLE_LIST, title, info, "Select", "Cancel");
    return 1;
}

Dialog:FactionBankMenu(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0: // Deposit
            {
                Dialog_Show(playerid, FactionBankDeposit, DIALOG_STYLE_INPUT, "Faction Bank - Deposit", "Enter the amount you want to deposit:", "Deposit", "Cancel");
            }
            case 1: // Withdraw
            {
                new rank = pData[playerid][pFactionRank];
                new maxRank = 16;
                // Only leader (rank 16/15/14 or faction lead) can withdraw
                if(pData[playerid][pFactionLead] == 0 && rank < maxRank - 2)
                    return Error(playerid, "Only Leader, Deputy Commissioner, or Commissioner can withdraw!");
                
                Dialog_Show(playerid, FactionBankWithdraw, DIALOG_STYLE_INPUT, "Faction Bank - Withdraw", "Enter the amount you want to withdraw:", "Withdraw", "Cancel");
            }
            case 2: // History
            {
                ShowFactionBankHistory(playerid);
            }
        }
    }
    return 1;
}

Dialog:FactionBankDeposit(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new amount = strval(inputtext);
        if(amount < 1) return Error(playerid, "Invalid amount!");
        if(GetPlayerMoney(playerid) < amount) return Error(playerid, "You don't have that much money!");
        
        GivePlayerMoneyEx(playerid, -amount);
        switch(pData[playerid][pFaction])
        {
            case 1: FactionBankSAPD += amount;
            case 2: FactionBankSAGS += amount;
            case 3: FactionBankSAMD += amount;
            case 4: FactionBankSAN += amount;
        }
        InsertFactionManage(pData[playerid][pFaction], sprintf("Deposit by %s", pData[playerid][pName]), FormatMoney(amount));
        SendCustomMessage(playerid, "FACTIONBANK", "You've deposited "GREEN_E"$%s", FormatMoney(amount));
    }
    return 1;
}

Dialog:FactionBankWithdraw(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new amount = strval(inputtext);
        if(amount < 1) return Error(playerid, "Invalid amount!");
        
        switch(pData[playerid][pFaction])
        {
            case 1: {
                if(amount > FactionBankSAPD) return Error(playerid, "Insufficient faction bank balance!");
                FactionBankSAPD -= amount;
            }
            case 2: {
                if(amount > FactionBankSAGS) return Error(playerid, "Insufficient faction bank balance!");
                FactionBankSAGS -= amount;
            }
            case 3: {
                if(amount > FactionBankSAMD) return Error(playerid, "Insufficient faction bank balance!");
                FactionBankSAMD -= amount;
            }
            case 4: {
                if(amount > FactionBankSAN) return Error(playerid, "Insufficient faction bank balance!");
                FactionBankSAN -= amount;
            }
        }
        GivePlayerMoneyEx(playerid, amount);
        InsertFactionManage(pData[playerid][pFaction], sprintf("Withdraw by %s", pData[playerid][pName]), FormatMoney(amount));
        SendCustomMessage(playerid, "FACTIONBANK", "You've withdrawn "GREEN_E"$%s "WHITE_E"from faction bank", FormatMoney(amount));
    }
    return 1;
}

stock ShowFactionBankHistory(playerid)
{
    new query[256], list[1024], msg[512], nameissued[52], date[128];
    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM factionmanage WHERE factionid = '%d' ORDER BY id DESC LIMIT 20", pData[playerid][pFaction]);
    mysql_query(g_SQL, query);
    new rows = cache_num_rows();
    if(rows)
    {
        format(list, sizeof(list), "Description\tDate\tAmount\n");
        for(new i = 0; i < rows; i++)
        {
            cache_get_value_name(i, "date", date);
            cache_get_value_name(i, "reason", msg);
            cache_get_value_name(i, "ammount", nameissued);
            format(list, sizeof(list), "%s%s\t%s\t"GREEN_E"$%s\n", list, msg, date, nameissued);
        }
        new balance[32];
        switch(pData[playerid][pFaction])
        {
            case 1: format(balance, sizeof(balance), FormatMoney(FactionBankSAPD));
            case 2: format(balance, sizeof(balance), FormatMoney(FactionBankSAGS));
            case 3: format(balance, sizeof(balance), FormatMoney(FactionBankSAMD));
            case 4: format(balance, sizeof(balance), FormatMoney(FactionBankSAN));
        }
        format(list, sizeof(list), "%sBalance:\t"GREEN_E"$%s\n", list, balance);
        Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Faction Bank History", list, "Close", "");
    }
    else Error(playerid, "No transaction history!");
    return 1;
}

Dialog:LockerSAMD(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch (listitem) 
        {
            case 0: 
            {
                if(pData[playerid][pOnDuty] == 1)
                {
                    pData[playerid][pOnDuty] = 0;
                    SetPlayerColor(playerid, COLOR_WHITE);
                    if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                        UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s (%d)", pData[playerid][pName], playerid)));
                    SetPlayerSkin(playerid, pData[playerid][pSkin]);
                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s places their badge in their locker.", ReturnName(playerid));
                }
                else
                {
                    pData[playerid][pOnDuty] = 1;
                    SetFactionColor(playerid);
                    if(pData[playerid][pGender] == 1)
                    {
                        SetPlayerSkin(playerid, 276);
                        pData[playerid][pFacSkin] = 276;
                    }
                    else
                    {
                        SetPlayerSkin(playerid, 308);
                        pData[playerid][pFacSkin] = 308;
                    }
                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s withdraws their badge and on duty from their locker", ReturnName(playerid));
                }
            }
            case 1:
            {
                if(pData[playerid][pOnDuty] <= 0)
                    return Error(playerid, "You must be on duty first, before opening your locker!");
                switch (pData[playerid][pGender])
                {
                    case 1: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SAMDMale, "SAMD:", samdmale, sizeof(samdmale));
                    case 2: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SAMDFemale, "SAMD:", samdfemale, sizeof(samdfemale));
                }
            }
            case 2:
            {
                if(pData[playerid][pOnDuty] <= 0)
                    return Error(playerid, "You must be on duty first, before opening your locker!");
                pData[playerid][pMedicine]++;
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s telah mengambil medicine dari locker", ReturnName(playerid));
            }
            case 3:
            {
                if(pData[playerid][pOnDuty] <= 0)
                    return Error(playerid, "You must be on duty first, before opening your locker!");
                pData[playerid][pMedkit]++;
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s telah mengambil medkit dari locker", ReturnName(playerid));
            }
            case 4:
            {
                ShowFactionBankMenu(playerid);
            }
        }
    }
    return 1;
}

Dialog:LockerSANews(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch (listitem) 
        {
            case 0: 
            {
                if(pData[playerid][pOnDuty] == 1)
                {
                    pData[playerid][pOnDuty] = 0;
                    SetPlayerColor(playerid, COLOR_WHITE);
                    if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                        UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s (%d)", pData[playerid][pName], playerid)));
                    SetPlayerSkin(playerid, pData[playerid][pSkin]);
                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s places their badge and gun in their locker.", ReturnName(playerid));
                }
                else
                {
                    pData[playerid][pOnDuty] = 1;
                    SetFactionColor(playerid);
                    if(pData[playerid][pGender] == 1)
                    {
                        SetPlayerSkin(playerid, 189);
                        pData[playerid][pFacSkin] = 189;
                    }
                    else
                    {
                        SetPlayerSkin(playerid, 150);
                        pData[playerid][pFacSkin] = 150;
                    }
                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s withdraws their badge and on duty from their locker", ReturnName(playerid));
                }
            }
            case 1:
            {
                if(pData[playerid][pOnDuty] <= 0)
                    return Error(playerid, "You must be on duty first, before opening your locker!");
                switch (pData[playerid][pGender])
                {
                    case 1: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SANEWSMale, "SANEWS:", sanewsmale, sizeof(sanewsmale));
                    case 2: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SANEWSFemale, "SANEWS:", sanewsfemale, sizeof(sanewsfemale));
                }
            }
            case 2:
            {
                ShowFactionBankMenu(playerid);
            }
        }
    }
    return 1;
}

Dialog:LockerWeaponSAPD(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch (listitem) 
        {
            case 0:
            {
                GivePlayerWeaponEx(playerid, 41, 200);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(41));
            }
            case 1:
            {
                GivePlayerWeaponEx(playerid, 46, 1);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(46));
            }
            case 2:
            {
                GivePlayerWeaponEx(playerid, 3, 200);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(3));
            }
            case 3:
            {
                GivePlayerWeaponEx(playerid, 4, 200);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(4));
            }
            case 4:
            {
                GivePlayerWeaponEx(playerid, 22, 200);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(22));
            }
            case 5:
            {
                if(pData[playerid][pFactionRank] < 2)
                    return Error(playerid, "You are not allowed!");
                    
                GivePlayerWeaponEx(playerid, 23, 200);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(23));
            }
            case 6:
            {
                // Deagle (damage lebih tinggi dari colt, bisa dipakai semua rank)
                GivePlayerWeaponEx(playerid, 24, 200);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(24));
            }
            case 7:
            {
                if(pData[playerid][pFactionRank] < 3)
                    return Error(playerid, "You are not allowed!");
                GivePlayerWeaponEx(playerid, 25, 200);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(25));
            }
            case 8:
            {
                if(pData[playerid][pFactionRank] < 3)
                    return Error(playerid, "You are not allowed!");
                GivePlayerWeaponEx(playerid, 27, 200);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(27));
            }
            case 9:
            {
                if(pData[playerid][pFactionRank] < 3)
                    return Error(playerid, "You are not allowed!");
                GivePlayerWeaponEx(playerid, 29, 200);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(29));
            }
            case 10:
            {
                if(pData[playerid][pFactionRank] < 3)
                    return Error(playerid, "You are not allowed!");
                GivePlayerWeaponEx(playerid, 31, 200);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(31));
            }
            case 11:
            {
                if(pData[playerid][pFactionRank] < 3)
                    return Error(playerid, "You are not allowed!");
                GivePlayerWeaponEx(playerid, 33, 200);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(33));
            }
            case 12:
            {
                if(pData[playerid][pFactionRank] < 4)
                    return Error(playerid, "You are not allowed!");
                GivePlayerWeaponEx(playerid, 34, 200);
                SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid), ReturnWeaponName(34));
            }
        }
    }
    return 1;
}
