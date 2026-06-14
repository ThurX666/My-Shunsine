
Dialog:eventWeapon(playerid, response, listitem, inputtext[])
{
    if(response) 
	{
		SetPVarInt(playerid, "selectWeapon", listitem);
		Dialog_Show(playerid, editWeaponId, DIALOG_STYLE_INPUT, "Weapon Id", "Insert Weapon ID:", "Set", "Back");
	}
    return 1;
}

Dialog:editWeaponId(playerid, response, listitem, inputtext[])
{
    if(response) {
		new id = GetPVarInt(playerid, "selectWeapon");

		if(strval(inputtext) <= 0 || strval(inputtext) > 46 || (strval(inputtext) >= 19 && strval(inputtext) <= 21))
			return Dialog_Show(playerid, editWeaponId, DIALOG_STYLE_INPUT, "Weapon Id", "You have specified an invalid weapon!\n\nInsert Weapon ID:", "Set", "Back");

		EventData[eventWeapons][id] = strval(inputtext);
		EventData[eventAmmo][id] = 9999;
		callcmd::eventtttt(playerid, "weapon");
	}
	else callcmd::eventtttt(playerid, "weapon");
    return 1;
}

Dialog:eventType(playerid, response, listitem, inputtext[])
{
    if(response) 
	{
		EventData[eventTypes] = (listitem+1);

		if(EventData[eventTypes] == TYPE_TDM)
			Dialog_Show(playerid, eventTarget, DIALOG_STYLE_INPUT, "Target Score", "How much target:", "Set", "Back");

		if(EventData[eventTypes] == TYPE_DM)
			Dialog_Show(playerid, eventTarget, DIALOG_STYLE_INPUT, "Target Score", "How much target:", "Set", "Back");

		if(EventData[eventTypes] == TYPE_ZOMBIE)
			Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, "Event "RED_E"Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");

	}
    return 1;
}

Dialog:eventTarget(playerid, response, listitem, inputtext[])
{
    if(response) 
	{
		if(strval(inputtext) < 1 || strval(inputtext) > 150)
			return Dialog_Show(playerid, eventTarget, DIALOG_STYLE_INPUT, "Target Score", "Target score must be betweed 1 - 150\n\nHow much target:", "Set", "Back");

		EventData[eventTargets] = strval(inputtext);

		if(EventData[eventTypes] == TYPE_TDM)
		{
			new string[212];
			format(string, sizeof(string), "Team 1: %d\nTeam 2: %d\nNext",EventData[eventSkin][0], EventData[eventSkin][1]);
			Dialog_Show(playerid, eventSkins, DIALOG_STYLE_LIST, "Skin Event", string, "Set", "Back");
		}
		else if(EventData[eventTypes] == TYPE_DM)
			Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, "Event "RED_E"Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");
		
	}
	else callcmd::eventtttt(playerid, "create");
    return 1;
}

Dialog:eventSkins(playerid, response, listitem, inputtext[])
{
    if(response) 
	{
		switch(listitem)
		{
			case 0: Dialog_Show(playerid, eventSkins1, DIALOG_STYLE_INPUT, "Skin Team 1", "Masukkan id skin:", "Set", "Back");
			case 1: Dialog_Show(playerid, eventSkins2, DIALOG_STYLE_INPUT, "Skin Team 2", "Masukkan id skin:", "Set", "Back");
			case 2: 
			{
				if(!EventData[eventSkin][0] || !EventData[eventSkin][1])
					return Dialog_Show(playerid, eventSkins, DIALOG_STYLE_LIST, "Skin can't 0", "Team 1: %d\nTeam 2: %d\nNext", EventData[eventSkin][0], EventData[eventSkin][1], "Set", "Back");

				Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, "Event "RED_E"Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");
			}
		}
	}
	else Dialog_Show(playerid, eventTarget, DIALOG_STYLE_INPUT, "Target Score", "How much target:", "Set", "Back");
    return 1;
}

Dialog:eventSkins1(playerid, response, listitem, inputtext[])
{
    if(response) 
	{
		if(strval(inputtext) < 1 || strval(inputtext) > 311)
			return Dialog_Show(playerid, eventSkins1, DIALOG_STYLE_INPUT, "Skin Team 1", "Id skin tidak sesuai\n\nMasukkan id skin:", "Set", "Back");

		EventData[eventSkin][0] = strval(inputtext);
		new string[212];
		format(string, sizeof(string), "Team 1: %d\nTeam 2: %d\nNext",EventData[eventSkin][0], EventData[eventSkin][1]);
		Dialog_Show(playerid, eventSkins, DIALOG_STYLE_LIST, "Skin Event", string, "Set", "Back");
	}
	else {
		new string[212];
		format(string, sizeof(string), "Team 1: %d\nTeam 2: %d\nNext",EventData[eventSkin][0], EventData[eventSkin][1]);
		Dialog_Show(playerid, eventSkins, DIALOG_STYLE_LIST, "Skin Event", string, "Set", "Back");
	}
	return 1;
}

Dialog:eventSkins2(playerid, response, listitem, inputtext[])
{
    if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 311)
			return Dialog_Show(playerid, eventSkins2, DIALOG_STYLE_INPUT, "Skin Team 2", "Id skin tidak sesuai\n\nMasukkan id skin:", "Set", "Back");

		EventData[eventSkin][1] = strval(inputtext);
		new string[212];
		format(string, sizeof(string), "Team 1: %d\nTeam 2: %d\nNext",EventData[eventSkin][0], EventData[eventSkin][1]);
		Dialog_Show(playerid, eventSkins, DIALOG_STYLE_LIST, "Skin Event", string, "Set", "Back");
	}
	else {
		new string[212];
		format(string, sizeof(string), "Team 1: %d\nTeam 2: %d\nNext",EventData[eventSkin][0], EventData[eventSkin][1]);
		Dialog_Show(playerid, eventSkins, DIALOG_STYLE_LIST, "Skin Event", string, "Set", "Back");
	}
	return 1;
}

Dialog:eventHealth(playerid, response, listitem, inputtext[])
{
    if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 100)
			return Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, "Event "RED_E"Health", "Health must between 0 - 100\n\nMasukkan value darah yang akan di berikan:", "Set", "Back");

		EventData[eventHealths] = floatstr(inputtext);
		Dialog_Show(playerid, eventArmor, DIALOG_STYLE_INPUT, "Event "WHITE_E"Armor", "Masukkan value darah putih:", "Set", "Back");

	}
	else 
	{
		if(EventData[eventTypes] == TYPE_TDM)
		{
			new string[212];
			format(string, sizeof(string), "Team 1: %d\nTeam 2: %d\nNext",EventData[eventSkin][0], EventData[eventSkin][1]);
			Dialog_Show(playerid, eventSkins, DIALOG_STYLE_LIST, "Skin Event", string, "Set", "Back");
		}
		else if(EventData[eventTypes] == TYPE_DM)
			Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, "Event "RED_E"Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");
	}
    return 1;
}

Dialog:eventArmor(playerid, response, listitem, inputtext[])
{
    if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 100)
			return Dialog_Show(playerid, eventArmor, DIALOG_STYLE_INPUT, "Event "WHITE_E"Armor", "Darah putih harus berada di antara 0 - 100\n\nMasukkan value darah putih:", "Set", "Back");

		EventData[eventArmors] = floatstr(inputtext);
		Dialog_Show(playerid, eventBonus, DIALOG_STYLE_INPUT, "Event "GREEN_E"Bonus", "Masukkan berapa bonus yang akan di berikan:\n"RED_E"NOTE: Gunakan dollar", "Set", "Back");
	}
	else Dialog_Show(playerid, eventHealth, DIALOG_STYLE_LIST, "Event "RED_E"Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");
    return 1;
}

Dialog:eventBonus(playerid, response, listitem, inputtext[])
{
    if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 900000)
			return Dialog_Show(playerid, eventBonus, DIALOG_STYLE_INPUT, "Event "GREEN_E"Bonus", "Value bonus harus di antara 0 - $900,000\n\nMasukkan berapa bonus yang akan di berikan:\n"RED_E"NOTE: Gunakan dollar", "Set", "Back");
		new totalcash[25];
		format(totalcash, sizeof(totalcash), "%d00", strval(inputtext));
		EventData[eventBonuses] = strval(totalcash);

		if(EventData[eventTypes] == TYPE_TDM)
		{
			new string[212];
			format(string, sizeof(string), "Score Target\t"YELLOW_E"%d"WHITE_E"\nSkin Team 1\t"YELLOW_E"%d"WHITE_E"\nSkin Team 2\t"YELLOW_E"%d"WHITE_E"\nHealth Spawn\t"YELLOW_E"%.1f"WHITE_E"\nArmor Spawn\t"YELLOW_E"%.1f\n"WHITE_E"Event Bonus\t"GREEN_E"%s",
			EventData[eventTargets],
				EventData[eventSkin][0],
				EventData[eventSkin][1],
				EventData[eventHealths],
				EventData[eventArmors],
				FormatMoney(EventData[eventBonuses]));
			Dialog_Show(playerid, eventFinal, DIALOG_STYLE_LIST, "Event Information", string, "Start", "Back");
		}

		if(EventData[eventTypes] == TYPE_DM)
		{
			new string[212];
			format(string, sizeof(string), "Score Target\t"YELLOW_E"%d"WHITE_E"\nHealth Spawn\t"YELLOW_E"%.1f"WHITE_E"\nArmor Spawn\t"YELLOW_E"%.1f\n"WHITE_E"Event Bonus\t"GREEN_E"%s",
				EventData[eventTargets],
				EventData[eventHealths],
				EventData[eventArmors],
				FormatMoney(EventData[eventBonuses]));
			Dialog_Show(playerid, eventFinal, DIALOG_STYLE_LIST, "Event Information", string, "Start", "Back");
		}

		if(EventData[eventTypes] == TYPE_ZOMBIE)
		{
			new string[212];
			format(string, sizeof(string), ""WHITE_E"Health Spawn\t"YELLOW_E"%.1f"WHITE_E"\nArmor Spawn\t"YELLOW_E"%.1f\n"WHITE_E"Event Bonus\t"GREEN_E"%s",
				EventData[eventHealths],
				EventData[eventArmors],
				FormatMoney(EventData[eventBonuses]));
			Dialog_Show(playerid, eventFinal, DIALOG_STYLE_LIST, "Event Information", string, "Start", "Back");
		}
	}
	else 
	{
		if(EventData[eventTypes] == TYPE_TDM) 
			Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, "Event "RED_E"Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");
		else if(EventData[eventTypes] == TYPE_DM)
			Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, "Event "RED_E"Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");
	}
    return 1;
}

Dialog:eventFinal(playerid, response, listitem, inputtext[])
{
   	if(response) {
		EventData[eventCreated] = 1;
		EventData[eventWorld] = GetPlayerVirtualWorld(playerid)+1;
		EventData[eventInt] = GetPlayerInterior(playerid);
		Servers(playerid, "You've create the event, /event start to start the event.");
	}
	else Dialog_Show(playerid, eventBonus, DIALOG_STYLE_INPUT, "Event "GREEN_E"Bonus", "Masukkan berapa bonus yang akan di berikan:", "Set", "Back");
    return 1;
}
