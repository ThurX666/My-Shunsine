
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
				Dialog_Show(playerid, LockerSAPD, DIALOG_STYLE_LIST, "SAPD Lockers", "Toggle Duty\nHealth\nArmour\nWeapons\nClothing\nUndercover\nClothes (0.3DL ONLY)", "Proceed", "Cancel");
			}
			else if(pData[playerid][pFaction] == 3 && pData[playerid][pFaction] == lData[lid][lType])
			{
				Dialog_Show(playerid, LockerSAMD, DIALOG_STYLE_LIST, "SAMD Lockers", "Toggle Duty\nClothing\nMedicine\nMedkit", "Proceed", "Cancel");
			}
			else if(pData[playerid][pFaction] == 4 && pData[playerid][pFaction] == lData[lid][lType])
			{
				Dialog_Show(playerid, LockerSANews, DIALOG_STYLE_LIST, "SANA Lockers", "Toggle Duty\nClothing", "Proceed", "Cancel");
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
        }
    }
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
                        SetPlayerSkin(playerid, 150); //194
                        pData[playerid][pFacSkin] = 150; //194
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
