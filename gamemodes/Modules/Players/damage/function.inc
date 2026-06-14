
function OnLoadDamage(playerid)
{
    new rows = cache_num_rows();
 	if(rows)
  	{
		for (new i = 0; i < rows && i < MAX_DAMAGE; i ++) if(!DamageData[playerid][i][damageExists]) {
            DamageData[playerid][i][damageExists] = true;
            cache_get_value_int(i, "ID", DamageData[playerid][i][damageID]);
            cache_get_value_int(i, "amount", DamageData[playerid][i][damageAmount]);
            cache_get_value_int(i, "weapon", DamageData[playerid][i][damageWeapon]);
            cache_get_value_int(i, "bodypart", DamageData[playerid][i][damageBodypart]);
            cache_get_value_int(i, "time", DamageData[playerid][i][damageTime]);
        }	
	}
}

function DamageCreated(playerid, damageid)
{
    DamageData[playerid][damageid][damageID] = cache_insert_id();
    Damage_Save(playerid, damageid);
    return 1;
}

// Damage_Remove(playerid, damage)
// {
//     new string[212];
//     format(string, sizeof(string), "DELETE FROM `damages` WHERE `ID`='%d' && `IDs`='%d'", DamageData[playerid][damage][damageID], pData[playerid][pID]);
//     mysql_tquery(g_SQL, string);

//     DamageData[playerid][damage][damageExists] = false;
//     DamageData[playerid][damage][damageWeapon] = 0;

//     DamageData[playerid][damage][damageBodypart] = 0;
//     DamageData[playerid][damage][damageTime] = 0;
//     DamageData[playerid][damage][damageAmount] = 0;
//     DamageData[playerid][damage][damageID] = 0;
//     return 1;
// }

Damage_Reset(playerid, type = 0)
{
    if(!type){
        new string[212];
        format(string, sizeof(string), "DELETE FROM `damages` WHERE `IDs`='%d'", pData[playerid][pID]);
        mysql_tquery(g_SQL, string);
    }

    for(new id; id != MAX_DAMAGE; id++) if(DamageData[playerid][id][damageExists])
    {
        DamageData[playerid][id][damageExists] = false;
        DamageData[playerid][id][damageWeapon] = DamageData[playerid][id][damageBodypart] = 0;
        DamageData[playerid][id][damageTime] = DamageData[playerid][id][damageID] = 0;
        DamageData[playerid][id][damageAmount] = 0;
    }
    return 1;
}

Damage_Save(playerid, damage)
{
    new query[128];

    format(query, sizeof(query), "UPDATE `damages` SET `weapon`='%d', `bodypart`='%d', `amount`='%d', `time`='%d' WHERE `ID`='%d' && `IDs`='%d'", 
        DamageData[playerid][damage][damageWeapon],
        DamageData[playerid][damage][damageBodypart],
        DamageData[playerid][damage][damageAmount],
        DamageData[playerid][damage][damageTime],
        DamageData[playerid][damage][damageID],
        pData[playerid][pID]
    );
    return mysql_tquery(g_SQL, query);
}

AddDamage(playerid, bodypart, weapon)
{
    for (new id = 0; id != MAX_DAMAGE; id++) 
    {
        if(DamageData[playerid][id][damageExists] && DamageData[playerid][id][damageWeapon] == weapon && DamageData[playerid][id][damageBodypart] == bodypart)
        {
            DamageData[playerid][id][damageAmount] ++;
            DamageData[playerid][id][damageTime] = gettime();
            return 1;
        }
        else if(!DamageData[playerid][id][damageExists])
        {
            DamageData[playerid][id][damageExists] = true;
            DamageData[playerid][id][damageWeapon] = weapon;
            DamageData[playerid][id][damageBodypart] = bodypart;
            DamageData[playerid][id][damageAmount] = 1;
            DamageData[playerid][id][damageTime] = gettime();
            new string[212];
            format(string, sizeof(string), "INSERT INTO `damages` SET `weapon`='%d', `bodypart`='%d', `IDs`='%d'", DamageData[playerid][id][damageWeapon], DamageData[playerid][id][damageBodypart], pData[playerid][pID]);
            mysql_tquery(g_SQL, string, "DamageCreated", "dd", playerid, id);
            return 1;
        }
    }
    return 1;
}

Damage_Count(playerid)
{
    new count = 0;
    for(new i; i != MAX_DAMAGE; i++) if(DamageData[playerid][i][damageExists]) {
        count ++;
    }
    return count;
}

Damage_CountByBodypart(playerid, bodypart) {
    new count = 0;
    for (new i; i != MAX_DAMAGE; i++) if(DamageData[playerid][i][damageExists] && DamageData[playerid][i][damageBodypart] == bodypart) {
        count ++;
    }
    return count;
}

function Treatment(playerid)
{
    Damage_Reset(playerid);
    pData[playerid][pStartSurgey] = 0;
    Servers(GetPVarInt(playerid, "SurgeryID"), "%s menyelesaikan operasinya.", ReturnName(playerid));
    DeletePVar(playerid, "SurgeryID");
    KillTimer(pData[playerid][pSurgeryTimer]);
    SendClientMessageEx(playerid, COLOR_ARWIN, "SURGERY: "YELLOW_E"Operasi sukses, efek damage yang di berikan telah hilang.");
    return 1;
}

Health_Show(playerid, player) {
    new title[64];
    format(title, sizeof(title), "%s's Health", ReturnName(player));
    new strings[1500];
    format(strings, sizeof(strings), "{C2A2DA}===[Body part status]===\n");
    format(strings, sizeof(strings), "%s"WHITE_E"Part: "YELLOW_E"Torso"WHITE_E" | Fitness Rating:"GREEN_E" %.2f\n", strings, pData[player][pFitnessRating][0]);
    format(strings, sizeof(strings), "%s"WHITE_E"Condition: %s\n", strings, GetPlayerBodypartStatus(player, BODY_PART_TORSO));
    format(strings, sizeof(strings), "%s"WHITE_E"Part: "YELLOW_E"Groin"WHITE_E" | Fitness Rating:"GREEN_E" %.2f\n", strings, pData[player][pFitnessRating][1]);
    format(strings, sizeof(strings), "%s"WHITE_E"Condition: %s\n", strings, GetPlayerBodypartStatus(player, BODY_PART_GROIN));
    format(strings, sizeof(strings), "%s"WHITE_E"Part: "YELLOW_E"Right Arm"WHITE_E" | Fitness Rating:"GREEN_E" %.2f\n", strings, pData[player][pFitnessRating][2]);
    format(strings, sizeof(strings), "%s"WHITE_E"Condition: %s\n", strings, GetPlayerBodypartStatus(player, BODY_PART_RIGHT_ARM));
    format(strings, sizeof(strings), "%s"WHITE_E"Part: "YELLOW_E"Left Arm"WHITE_E" | Fitness Rating:"GREEN_E" %.2f\n", strings, pData[player][pFitnessRating][3]);
    format(strings, sizeof(strings), "%s"WHITE_E"Condition: %s\n", strings, GetPlayerBodypartStatus(player, BODY_PART_LEFT_ARM));
    format(strings, sizeof(strings), "%s"WHITE_E"Part: "YELLOW_E"Right Leg"WHITE_E" | Fitness Rating:"GREEN_E" %.2f\n", strings, pData[player][pFitnessRating][4]);
    format(strings, sizeof(strings), "%s"WHITE_E"Condition: %s\n", strings, GetPlayerBodypartStatus(player, BODY_PART_RIGHT_LEG));
    format(strings, sizeof(strings), "%s"WHITE_E"Part: "YELLOW_E"Left Leg"WHITE_E" | Fitness Rating:"GREEN_E" %.2f\n", strings, pData[player][pFitnessRating][5]);
    format(strings, sizeof(strings), "%s"WHITE_E"Condition: %s\n", strings, GetPlayerBodypartStatus(player, BODY_PART_LEFT_LEG));
    format(strings, sizeof(strings), "%s"WHITE_E"Part: "YELLOW_E"Head\n", strings);
    format(strings, sizeof(strings), "%s"WHITE_E"Condition: %s", strings, GetPlayerBodypartStatus(player, BODY_PART_HEAD));

    if (pData[playerid][pFaction] == 3) {
        format(strings, sizeof(strings), "%s\n{C2A2DA}===[Body Health]===\n", strings);
        if(pData[player][pCough] >= 5)
        {
            new rate[7];

            switch((pData[player][pCough]/5))
            {
                case 1: rate="LOW";
                case 2: rate="MEDIUM";
                case 3: rate="HIGH";
            }
            
            format(strings, sizeof(strings), "%s"WHITE_E"Disease: "YELLOW_E"SICK (Cough)\n", strings);
            format(strings, sizeof(strings), "%s"WHITE_E"Cure: "YELLOW_E"eat Neladryl Acetate\n", strings);
            format(strings, sizeof(strings), "%s"WHITE_E"Sickness rate: "YELLOW_E"%s\n\n", strings, rate);
        }
        if(pData[player][pMigrainRate])
        {
            new rate[7];

            switch((pData[player][pMigrainRate]))
            {
                case 1: rate="LOW";
                case 2: rate="MEDIUM";
                case 3: rate="HIGH";
            }
            
            format(strings, sizeof(strings), "%s"WHITE_E"Disease: "YELLOW_E"SICK (Migrain)\n", strings);
            format(strings, sizeof(strings), "%s"WHITE_E"Cure: "YELLOW_E"eat Kratotamax Plus 1.0\n", strings);
            format(strings, sizeof(strings), "%s"WHITE_E"Sickness rate: "YELLOW_E"%s\n\n", strings, rate);
        }
        if(pData[player][pFever])
        {
            new rate[7];

            switch((pData[player][pFever]))
            {
                case 1: rate="LOW";
                case 2: rate="MEDIUM";
                case 3: rate="HIGH";
            }

            format(strings, sizeof(strings), "%s"WHITE_E"Disease: "YELLOW_E"SICK (High fever)\n", strings);
            format(strings, sizeof(strings), "%s"WHITE_E"Cure: "YELLOW_E"eat Lazattavitus Extra\n", strings);
            format(strings, sizeof(strings), "%s"WHITE_E"Sickness rate: "YELLOW_E"%s\n", strings, rate);
        }
    }
    Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, title, strings, "Close", "");
    return 1;
}

GetBodyPartName(bodypart)
{
    new part[11];
    switch(bodypart)
    {
        case BODY_PART_TORSO: part = "Torso";
        case BODY_PART_GROIN: part = "Groin";
        case BODY_PART_LEFT_ARM: part = "Left Arm";
        case BODY_PART_RIGHT_ARM: part = "Right Arm";
        case BODY_PART_LEFT_LEG: part = "Left Leg";
        case BODY_PART_RIGHT_LEG: part = "Right Leg";
        case BODY_PART_HEAD: part = "Head";
        default: part = "None";
    }
    return part;
}

Damage_Show(playerid, player)
{
    new title[64];
    format(title, sizeof(title), "%s's weapon damages", ReturnName(player));
    new strings[1000], fstr[128];
    strcat(strings, "Bullets\tWeapon\tBody\tTime\n");
    for(new i = 0; i < MAX_DAMAGE; i++) if(DamageData[player][i][damageExists])
    {
        switch(DamageData[player][i][damageWeapon])
        {
            case 0 .. 15: format(fstr, sizeof(fstr), "%d\t%s\t%s\t%s\n", DamageData[player][i][damageAmount], ReturnWeaponName(DamageData[player][i][damageWeapon]), GetBodyPartName(DamageData[player][i][damageBodypart]),GetDuration(gettime() - DamageData[player][i][damageTime]));
            default: format(fstr, sizeof(fstr), "%d\t%s\t%s\t%s\n", DamageData[player][i][damageAmount], ReturnWeaponName(DamageData[player][i][damageWeapon]), GetBodyPartName(DamageData[player][i][damageBodypart]),GetDuration(gettime() - DamageData[player][i][damageTime]));
        }
        strcat(strings, fstr);
    }
    Dialog_Show(playerid, DisplayDamage, DIALOG_STYLE_TABLIST_HEADERS, title, strings,"Close","");
    return 1;
}

GetPlayerBodypartStatus(player, bodypart) {
    new result[128];
    if (!Damage_CountByBodypart(player, bodypart)) {
        format(result, sizeof(result), GREEN_E"Normal");
        return result;
    }

    for(new i = 0; i < MAX_DAMAGE; i++) if(DamageData[player][i][damageExists]) {
        if (bodypart == DamageData[player][i][damageBodypart]) {
            switch (DamageData[player][i][damageWeapon]) {
                case 4: {
                    if (DamageData[player][i][damageAmount] == 2) format(result, sizeof(result), YELLOW_E"Graze");
                    else if (DamageData[player][i][damageAmount] >= 4) format(result, sizeof(result), "%s"ORANGE_E" Cut", result);
                    else format(result, sizeof(result), "%s"RED_E" Bleeding", result);
                }
                case 22..38: {
                    if (DamageData[player][i][damageAmount] >= 2 && DamageData[player][i][damageAmount] <= 4) format(result, sizeof(result), RED_E"Flesh wound (%d bullets)", DamageData[player][i][damageAmount]);
                    else if (DamageData[player][i][damageAmount] >= 5) format(result, sizeof(result), "%s"RED_E" Vital wound (%d bullets)", result, DamageData[player][i][damageAmount]-2);
                    else format(result, sizeof(result), "%s"YELLOW_E" Graze", result);
                }
                case 0..3, 5..15: {
                    format(result, sizeof(result), GREEN_E"Bruise");
                }
                case 49: { // Vehicle collision
                    if (DamageData[player][i][damageAmount] >= 3) format(result, sizeof(result), RED_E"Crushed");
                    else if (DamageData[player][i][damageAmount] >= 2) format(result, sizeof(result), ORANGE_E"Severe Bruise");
                    else format(result, sizeof(result), YELLOW_E"Bruise");
                }
                case 50: { // Helicopter blade
                    if (DamageData[player][i][damageAmount] >= 2) format(result, sizeof(result), RED_E"Deep Laceration");
                    else format(result, sizeof(result), ORANGE_E"Laceration");
                }
                case 51: { // Explosion
                    if (DamageData[player][i][damageAmount] >= 3) format(result, sizeof(result), RED_E"Severe Blast Injury");
                    else if (DamageData[player][i][damageAmount] >= 2) format(result, sizeof(result), ORANGE_E"Blast Wound");
                    else format(result, sizeof(result), YELLOW_E"Burn");
                }
                case 52: { // Drowning
                    format(result, sizeof(result), ORANGE_E"Water In Lungs");
                }
                case 54: { // Fall damage (Splat)
                    if (DamageData[player][i][damageAmount] >= 3) format(result, sizeof(result), RED_E"Broken Bone");
                    else if (DamageData[player][i][damageAmount] >= 2) format(result, sizeof(result), ORANGE_E"Severe Bruise");
                    else format(result, sizeof(result), YELLOW_E"Bruise");
                }
                default: {
                    if (DamageData[player][i][damageAmount] >= 1 && DamageData[player][i][damageAmount] < 5) format(result,sizeof(result),WHITE_E"Dislocated");
                    else if (DamageData[player][i][damageAmount] >= 5) format(result,sizeof(result),WHITE_E"Broken Bone");
                    else format(result,sizeof(result),GREEN_E"Normal");
                }
            }
        }
    }
    return result;
}
