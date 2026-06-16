
CMD:damagelog(playerid, params[])
{
    new player;


    if(sscanf(params, "u", player))
    {
        if (!Damage_Count(playerid)) return SendCustomMessage(playerid, "DAMAGES", "You're "GREEN_E"healthy");
        else return Damage_Show(playerid, playerid);
    }

    if(player == playerid) return Error(playerid, "Use command /damages to check your damages.");
    if(player == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, player, 3.0)) return Error(playerid, "That player is disconnected or not near you.");
    if (!Damage_Count(player)) return SendCustomMessage(playerid, "DAMAGES", "This player "GREEN_E"healthy");

    Servers(player, "%s melihat kondisi karakter anda.", ReturnName(playerid));
    Servers(playerid, "Anda melihat kondisi karakter %s.", ReturnName(player));
    Damage_Show(playerid, player);
    return 1;
}

CMD:health(playerid) {
    if (!IsPlayerConnected(playerid))
        return Error(playerid, "You're not logged in!");

    Health_Show(playerid, playerid);
    return 1;
}

CMD:ahealth(playerid, params[])
{
    if (pData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    static
        userid;

    if(sscanf(params, "u", userid)) return Usage(playerid, "/ahealth [playerid]");
    if(userid == INVALID_PLAYER_ID) return Error(playerid, "That player is disconnected.");

    Health_Show(playerid, userid);
    return 1;
}

CMD:acure(playerid, params[])
{
    if (pData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    static
        userid;

    if(sscanf(params, "u", userid)) return Usage(playerid, "/acure [playerid]");
    if(userid == INVALID_PLAYER_ID) return Error(playerid, "That player is disconnected.");

    pData[userid][pCough] = 0;
    pData[userid][pMigrainRate] = 0;
    pData[userid][pFever] = 0;

    Servers(userid, "Administrator %s telah mereset penyakit di karakter anda.", pData[playerid][pAdminname]);
    Servers(playerid, "Anda telah mereset penyakit karakter %s.", ReturnName(userid));
    return 1;
}

CMD:givepills(playerid, params[])
{
    if(pData[playerid][pFaction] != 3 || !pData[playerid][pOnDuty])
        return Error(playerid, "You must be an on duty SAMD officer.");

    static
        userid,
        id,
        amount;

    if(sscanf(params, "uii", userid, id, amount)) 
    {
        Usage(playerid, "/givepills [playerid/PartOfName] [id] [amount]");
        SendCustomMessage(playerid, "ID", "1, Neladryl Acetate. | 2, Kratotamax Plus 1.0. | 3. Lazattavitus Extra.");
        return 1;
    }
    if(userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 4.0)) return Error(playerid, "That player is disconnected or not near you.");
    if(userid == playerid) return Error(playerid, "That player is you!.");
    if(amount < 1 || amount > 10) return Error(playerid, "You can give only between 1-10");

    if(id == 1)
    {
        if(pData[playerid][pCoughPills] < amount) return Error(playerid, "You don't have enough pills.");

        pData[playerid][pCoughPills] -= amount;
        pData[userid][pCoughPills] += amount;
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "*%s take's out %d Neladryl Acetate and give it to %s", ReturnName(playerid), amount, ReturnName(userid));
    }
    else if(id == 2)
    {
        if(pData[playerid][pMigrainPills] < amount) return Error(playerid, "You don't have enough pills.");   
        pData[playerid][pMigrainPills] -= amount;
        pData[userid][pMigrainPills] += amount;
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "*%s take's out %d Kratotamax Plus 1.0 and give it to %s", ReturnName(playerid), amount, ReturnName(userid));
    }
    else if(id == 3)
    {
        if(pData[playerid][pFiverPills] < amount) return Error(playerid, "You don't have enough pills.");
        pData[playerid][pFiverPills] -= amount;
        pData[userid][pFiverPills] += amount;
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "*%s take's out %d Lazattavitus Extra and give it to %s", ReturnName(playerid), amount, ReturnName(userid));
    }
    else SendCustomMessage(playerid, "ID", "1, Neladryl Acetate. | 2, Kratotamax Plus 1.0. | 3. Lazattavitus Extra.");
    return 1;
}

CMD:usepills(playerid, params[])
{
    if(pData[playerid][pUsePills]) return Error(playerid, "Tidak dapat mengkonsumsi pill sekarang, tunggu hingga %d detik lagi.", pData[playerid][pUsePills]);

    Dialog_Show(playerid, UsePills, DIALOG_STYLE_TABLIST_HEADERS, "Medicine", "Obat\tJumlah\nNeladryl Acetate\t%d\nKratotamax Plus 1.0\t%d\nLazattavitus Extra\t%d", "Take", "Close", pData[playerid][pCoughPills], pData[playerid][pMigrainPills], pData[playerid][pFiverPills]);
    return 1;
}

CMD:takepills(playerid, params[])
{
    if(pData[playerid][pFaction] != 3) 
        return Error(playerid, "You can't take pills from this locker.");
    if(!pData[playerid][pOnDuty])
        return Error(playerid, "You must be on duty to take pills.");

    if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1187.6946, -1333.6653, 3013.4844))
        return Error(playerid, "Go to pharmacy to get the pills.");

    Dialog_Show(playerid, TakePills, DIALOG_STYLE_TABLIST_HEADERS, "Medicine", "Obat\tPenyakit\nNeladryl Acetate\tCough\nKratotamax Plus 1.0\tMigrain\nLazattavitus Extra\tHigh Fever", "Take", "Close");
    //\nAmphytum Nanolacetate\tAddiction
    return 1;
}

CMD:resetdamage(playerid, params[])
{
    new player;

    if (pData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if(sscanf(params, "u", player))
        return Usage(playerid, "/resetdamage [playerid/part of name]");

    if(!IsPlayerConnected(player))
        return Error(playerid, "That player isn't logged in.");

    Damage_Reset(player);
    Servers(player, "Admin %s telah mereset damage anda.", pData[playerid][pAdminname]);
    SendStaffMessage(TOMATO, "AdmWarn: %s reset %s damages.", pData[playerid][pAdminname],ReturnName(player));
    return 1;
}

CMD:surgery(playerid, params[])
{
    new player;

    if(pData[playerid][pFaction] != 3)  return Error(playerid, "You're not medic.");
    
    if(sscanf(params, "u", player)) return Usage(playerid, "/surgery [playerid/part of name]");
    if(player == playerid) return Error(playerid, "You can't surgery yourself.");
    if(player == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, player, 3.0)) return Error(playerid, "That player is disconnected or not near you.");
    if(pData[player][pStartSurgey]) return Error(playerid, "That player is already to surgery.");
    if(!Damage_Count(player)) return SendClientMessageEx(playerid, COLOR_ARWIN, "SURGERY: "WHITE_E"This player is "GREEN_E"healthy");
    if(IsPlayerInRangeOfPoint(playerid, 8, 1225.4766,-1340.2692,3013.5083) || IsPlayerInRangeOfPoint(playerid, 8, 1225.7388,-1344.9170,3013.5083) 
    || IsPlayerInRangeOfPoint(playerid, 8, 1208.8163,-1338.2944,3013.5083) || IsPlayerInRangeOfPoint(playerid, 8, 1226.0441,-1324.3016,3013.5083))
    {
        new string[212], fstr[1000];
        format(fstr, sizeof(fstr), "Bullets\tWeapon\tBody\tTime\n");
        for(new i = 0; i < MAX_DAMAGE; i++) if(DamageData[player][i][damageExists])
        {
            switch(DamageData[player][i][damageWeapon])
            {
                case 0 .. 15: format(fstr, sizeof(fstr), "%s%d\t%s\t%s\t%s\n", fstr, DamageData[player][i][damageAmount], ReturnWeaponName(DamageData[player][i][damageWeapon]), GetBodyPartName(DamageData[player][i][damageBodypart] + 3),GetDuration(gettime() - DamageData[player][i][damageTime]));
                default: format(fstr, sizeof(fstr), "%s%d\t%s\t%s\t%s\n", fstr, DamageData[player][i][damageAmount], ReturnWeaponName(DamageData[player][i][damageWeapon]), GetBodyPartName(DamageData[player][i][damageBodypart] + 3),GetDuration(gettime() - DamageData[player][i][damageTime]));
            }
        }
        format(string, sizeof(string), "%s's weapon damages", ReturnName(player));
        Dialog_Show(playerid, TestSurgey, DIALOG_STYLE_TABLIST_HEADERS, string, fstr,"Surgery","Close");
        pData[playerid][pSurgeyID] = player;
        SetPVarInt(player, "SurgeryID", playerid);
    }
    else return Error(playerid, "You must be in emergency room!");
    return 1;
}
