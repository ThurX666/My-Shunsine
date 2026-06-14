
// CMD:training(playerid, params[])
// {
//     if(!IsPlayerInRangeOfPoint(playerid, 3, 286.0590,-30.4579,1001.5156) && ) return Error(playerid, "Anda harus berada di ammunation shooting range");
// 	if(IsTraining[playerid] != 0) return Error(playerid, "You are already training!");
//     if(DelayPlayer[playerid][DelayTraining] != 0) return Error(playerid, "Tidak bisa menggunakan command ini");
// 	new String[212];
//     format(String, sizeof(String), "Weapons Name\tSkill Level\tTraining Price\n");
//     format(String, sizeof(String),"%sCountry Rifle\t%d\t$50.00\nShotgun\t%d\t$75.00\nDesert Eagle\t%d\t$95.00\nMP5\t%d\t$105.00\nAK47\t%d\t$115.00", String, pData[playerid][pSkillWeapon][0], pData[playerid][pSkillWeapon][1], pData[playerid][pSkillWeapon][2],pData[playerid][pSkillWeapon][3], pData[playerid][pSkillWeapon][4]);
//     Dialog_Show(playerid, TrainingWeapon, DIALOG_STYLE_TABLIST_HEADERS, "Weapon Training", String, "Select", "Close");
//     return 1;
// }

ptask PlayerTrainingWeapon[1000](playerid)
{
    new String[212];
    if(IsTraining[playerid] == 2 && TimeTraning[playerid])
    {
        TimeTraning[playerid]--;
        format(String, sizeof(String), "~y~Start in~n~~w~%d", TimeTraning[playerid]);
        PlayerTextDrawSetString(playerid, TextStartTraining[playerid], String);
        if(TimeTraning[playerid] == 0)
        {
            TextDrawHideForPlayer(playerid, BoxStartTraining);
            PlayerTextDrawHide(playerid, TextStartTraining[playerid]);
            IsTraining[playerid] = 1;
            TimeTraning[playerid] = 90;
            format(String, sizeof(String), "~y~Time Left~n~~w~%d~n~~y~Score~n~~w~%d", TimeTraning[playerid], CountTraining[playerid]);
            PlayerTextDrawSetString(playerid, TextTraining[playerid], String);
            TextDrawShowForPlayer(playerid, BoxTraining);
            PlayerTextDrawShow(playerid, TextTraining[playerid]);
            slottrain[playerid][0] = CreatePlayerObject(playerid, 1583, 290.313842, -15.290032, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
    }
    if(IsTraining[playerid] == 1 && TimeTraning[playerid])
    {
        TimeTraning[playerid]--;
        format(String, sizeof(String), "~y~Time Left~n~~w~%d~n~~y~Score~n~~w~%d", TimeTraning[playerid], CountTraining[playerid]);
        PlayerTextDrawSetString(playerid, TextTraining[playerid], String);
        if(TimeTraning[playerid] == 0)
        {
            TextDrawHideForPlayer(playerid, BoxTraining);
            PlayerTextDrawHide(playerid, TextTraining[playerid]);
            IsTraining[playerid] = 0;
            TimeTraning[playerid] = 0;
            new bizid = pData[playerid][pInBiz];
            SetPlayerPos(playerid, bData[bizid][bPointX], bData[bizid][bPointY], bData[bizid][bPointZ]);
            SetPlayerInterior(playerid, bData[bizid][bInt]);
            switch(TrainingSelectWeap[playerid])
            {
                case 0:
                {
                    pData[playerid][pSkillWeapon][0] = CountTraining[playerid];
                    SetPlayerSkillLevel(playerid, WEAPON_RIFLE, pData[playerid][pSkillWeapon][0]);
                    CountTraining[playerid] = 0;
                }
                case 1:
                {
                    pData[playerid][pSkillWeapon][1] = CountTraining[playerid];
                    SetPlayerSkillLevel(playerid, WEAPON_SHOTGUN, pData[playerid][pSkillWeapon][1]);
                    CountTraining[playerid] = 0;
                }
                case 2:
                {
                    pData[playerid][pSkillWeapon][2] = CountTraining[playerid];
                    SetPlayerSkillLevel(playerid, WEAPON_DEAGLE, pData[playerid][pSkillWeapon][2]);
                    CountTraining[playerid] = 0;
                }
                case 3:
                {
                    pData[playerid][pSkillWeapon][3] = CountTraining[playerid];
                    SetPlayerSkillLevel(playerid, WEAPON_MP5, pData[playerid][pSkillWeapon][3]);
                    CountTraining[playerid] = 0;
                }
                case 4:
                {
                    pData[playerid][pSkillWeapon][4] = CountTraining[playerid];
                    SetPlayerSkillLevel(playerid, WEAPON_AK47, pData[playerid][pSkillWeapon][4]);
                    CountTraining[playerid] = 0;
                }
            }
            DelayPlayer[playerid][DelayTraining] = 600;
            RefreshWeapon(playerid);
            TrainingSelectWeap[playerid] = -1;
            DestroyPlayerObject(playerid, slottrain[playerid][0]);
            DestroyPlayerObject(playerid, slottrain[playerid][1]);
            DestroyPlayerObject(playerid, slottrain[playerid][2]);
            DestroyPlayerObject(playerid, slottrain[playerid][3]);
            DestroyPlayerObject(playerid, slottrain[playerid][4]);
            DestroyPlayerObject(playerid, slottrain[playerid][5]);
            DestroyPlayerObject(playerid, slottrain[playerid][6]);
            DestroyPlayerObject(playerid, slottrain[playerid][7]);
            DestroyPlayerObject(playerid, slottrain[playerid][8]);
            DestroyPlayerObject(playerid, slottrain[playerid][9]);
            DestroyPlayerObject(playerid, slottrain[playerid][10]);
            DestroyPlayerObject(playerid, slottrain[playerid][11]);
            DestroyPlayerObject(playerid, slottrain[playerid][12]);
            DestroyPlayerObject(playerid, slottrain[playerid][13]);
            DestroyPlayerObject(playerid, slottrain[playerid][14]);
        }
    }
    return 1;
}

Dialog:TrainingWeapon(playerid, response, listitem, inputtext[]) {
    if(response)
	{
        new String[212];
        foreach(new player : Player) if(IsTraining[player] != 0 && pData[playerid][pInBiz] == pData[player][pInBiz]) return Error(playerid, "Ada player lain sedang latihan menembak");
		switch(listitem)
		{
			case 0:
			{
                new bizid = pData[playerid][pInBiz];
                if(GetPlayerMoney(playerid) < 5000) return Error(playerid, "Anda tidak memiliki cukup uang");
				GivePlayerMoneyEx(playerid, -5000);
                bData[bizid][bMoney] += Server_Percent(5000);
                Server_AddPercent(5000);
                Bisnis_Save(bizid);
                SetPlayerPos(playerid, 287.7236,-26.8233,1001.5156);
                SetPlayerInterior(playerid, bData[bizid][bInt]);
                ResetPlayerWeapons(playerid);
                GivePlayerWeapon(playerid, 33, 999999);
                IsTraining[playerid] = 2;
                TimeTraning[playerid] = 10;
                CountTraining[playerid] = 0;
                TrainingSelectWeap[playerid] = 0;
                format(String, sizeof(String), "~y~Start in~n~~w~%d", TimeTraning[playerid]);
                PlayerTextDrawSetString(playerid, TextStartTraining[playerid], String);
                TextDrawShowForPlayer(playerid, BoxStartTraining);
                PlayerTextDrawShow(playerid, TextStartTraining[playerid]);
			}
			case 1:
			{
                new bizid = pData[playerid][pInBiz];
				if(GetPlayerMoney(playerid) < 7500) return Error(playerid, "Anda tidak memiliki cukup uang");
                GivePlayerMoneyEx(playerid, -7500);
                bData[bizid][bMoney] += Server_Percent(7500);
                Server_AddPercent(7500);
                Bisnis_Save(bizid);
                SetPlayerPos(playerid, 287.7236,-26.8233,1001.5156);
                SetPlayerInterior(playerid, bData[bizid][bInt]);
                ResetPlayerWeapons(playerid);
                GivePlayerWeapon(playerid, 25, 999999);
                IsTraining[playerid] = 2;
                TimeTraning[playerid] = 10;
                CountTraining[playerid] = 0;
                TrainingSelectWeap[playerid] = 1;
                format(String, sizeof(String), "~y~Start in~n~~w~%d", TimeTraning[playerid]);
                PlayerTextDrawSetString(playerid, TextStartTraining[playerid], String);
                TextDrawShowForPlayer(playerid, BoxStartTraining);
                PlayerTextDrawShow(playerid, TextStartTraining[playerid]);
			}
			case 2:
			{
                new bizid = pData[playerid][pInBiz];
				if(GetPlayerMoney(playerid) < 9500) return Error(playerid, "Anda tidak memiliki cukup uang");
                GivePlayerMoneyEx(playerid, -9500);
                bData[bizid][bMoney] += Server_Percent(9500);
                Server_AddPercent(9500);
                Bisnis_Save(bizid);
                SetPlayerPos(playerid, 287.7236,-26.8233,1001.5156);
                SetPlayerInterior(playerid, bData[bizid][bInt]);
                ResetPlayerWeapons(playerid);
                GivePlayerWeapon(playerid, 24, 999999);
                IsTraining[playerid] = 2;
                TimeTraning[playerid] = 10;
                CountTraining[playerid] = 0;
                TrainingSelectWeap[playerid] = 2;
                format(String, sizeof(String), "~y~Start in~n~~w~%d", TimeTraning[playerid]);
                PlayerTextDrawSetString(playerid, TextStartTraining[playerid], String);
                TextDrawShowForPlayer(playerid, BoxStartTraining);
                PlayerTextDrawShow(playerid, TextStartTraining[playerid]);
			}
			case 3:
			{
                new bizid = pData[playerid][pInBiz];
				if(GetPlayerMoney(playerid) < 10500) return Error(playerid, "Anda tidak memiliki cukup uang");
                GivePlayerMoneyEx(playerid, -10500);
                bData[bizid][bMoney] += Server_Percent(10500);
                Server_AddPercent(10500);
                Bisnis_Save(bizid);
                SetPlayerPos(playerid, 287.7236,-26.8233,1001.5156);
                SetPlayerInterior(playerid, bData[bizid][bInt]);
                ResetPlayerWeapons(playerid);
                GivePlayerWeapon(playerid, 29, 999999);
                IsTraining[playerid] = 2;
                TimeTraning[playerid] = 10;
                CountTraining[playerid] = 0;
                TrainingSelectWeap[playerid] = 3;
                format(String, sizeof(String), "~y~Start in~n~~w~%d", TimeTraning[playerid]);
                PlayerTextDrawSetString(playerid, TextStartTraining[playerid], String);
                TextDrawShowForPlayer(playerid, BoxStartTraining);
                PlayerTextDrawShow(playerid, TextStartTraining[playerid]);
			}
			case 4:
			{
                new bizid = pData[playerid][pInBiz];
				if(GetPlayerMoney(playerid) < 11500) return Error(playerid, "Anda tidak memiliki cukup uang");
                GivePlayerMoneyEx(playerid, -11500);
                bData[bizid][bMoney] += Server_Percent(11500);
                Server_AddPercent(11500);
                Bisnis_Save(bizid);
                SetPlayerPos(playerid, 287.7236,-26.8233,1001.5156);
                SetPlayerInterior(playerid, bData[bizid][bInt]);
                ResetPlayerWeapons(playerid);
                GivePlayerWeapon(playerid, 30, 999999);
                IsTraining[playerid] = 2;
                TimeTraning[playerid] = 10;
                CountTraining[playerid] = 0;
                TrainingSelectWeap[playerid] = 4;
                format(String, sizeof(String), "~y~Start in~n~~w~%d", TimeTraning[playerid]);
                PlayerTextDrawSetString(playerid, TextStartTraining[playerid], String);
                TextDrawShowForPlayer(playerid, BoxStartTraining);
                PlayerTextDrawShow(playerid, TextStartTraining[playerid]);
			}
		}
	}
	return 1;
}

TrainingRandom(playerid)
{
    new rand = RandomEx(0, 15);
    DestroyPlayerObject(playerid, slottrain[playerid][0]);
    DestroyPlayerObject(playerid, slottrain[playerid][1]);
    DestroyPlayerObject(playerid, slottrain[playerid][2]);
    DestroyPlayerObject(playerid, slottrain[playerid][3]);
    DestroyPlayerObject(playerid, slottrain[playerid][4]);
    DestroyPlayerObject(playerid, slottrain[playerid][5]);
    DestroyPlayerObject(playerid, slottrain[playerid][6]);
    DestroyPlayerObject(playerid, slottrain[playerid][7]);
    DestroyPlayerObject(playerid, slottrain[playerid][8]);
    DestroyPlayerObject(playerid, slottrain[playerid][9]);
    DestroyPlayerObject(playerid, slottrain[playerid][10]);
    DestroyPlayerObject(playerid, slottrain[playerid][11]);
    DestroyPlayerObject(playerid, slottrain[playerid][12]);
    DestroyPlayerObject(playerid, slottrain[playerid][13]);
    DestroyPlayerObject(playerid, slottrain[playerid][14]);
    switch(rand)
    {
        case 0:
        {
            slottrain[playerid][1] = CreatePlayerObject(playerid, 1583, 292.683746, -15.290032, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 1:
        {
            slottrain[playerid][2] = CreatePlayerObject(playerid, 1583, 294.483825, -15.290032, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 2:
        {
            slottrain[playerid][3] = CreatePlayerObject(playerid, 1583, 296.193725, -15.290032, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 3:
        {
            slottrain[playerid][4] = CreatePlayerObject(playerid, 1583, 297.783691, -15.290032, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 4:
        {
            slottrain[playerid][5] = CreatePlayerObject(playerid, 1583, 299.333801, -15.290032, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00);
        }
        case 5:
        {
            slottrain[playerid][6] = CreatePlayerObject(playerid, 1583, 288.573638, -15.290032, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 6:
        {
            slottrain[playerid][7] = CreatePlayerObject(playerid, 1583, 286.803588, -15.290032, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 7:
        {
            slottrain[playerid][8] = CreatePlayerObject(playerid, 1583, 285.183349, -15.290032, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 8:
        {
            slottrain[playerid][9] = CreatePlayerObject(playerid, 1583, 292.683746, -17.520044, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 9:
        {
            slottrain[playerid][10] = CreatePlayerObject(playerid, 1583, 289.283752, -17.520044, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 10:
        {
            slottrain[playerid][11] = CreatePlayerObject(playerid, 1583, 287.133728, -17.520044, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 11:
        {
            slottrain[playerid][12] = CreatePlayerObject(playerid, 1583, 291.003631, -17.520044, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 12:
        {
            slottrain[playerid][13] = CreatePlayerObject(playerid, 1583, 294.663665, -17.520044, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 13:
        {
            slottrain[playerid][14] = CreatePlayerObject(playerid, 1583, 296.853698, -17.520044, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
        case 14:
        {
            slottrain[playerid][0] = CreatePlayerObject(playerid, 1583, 290.313842, -15.290032, 1001.656005, 0.000000, 0.000000, 0.000000, 100.00); 
        }
    }
    return 1;
}