
function OnContactsLoad(playerid)
{
    new owner[128];
	
    new rows = cache_num_rows();
 	if(rows)
  	{
		for (new i = 0; i < rows && i < MAX_CONTACTS; i ++) 
		{
			ContactData[playerid][i][contactExists] = true;
			cache_get_value_name_int(i, "contactID", ContactData[playerid][i][contactID]);
			cache_get_value_name(i, "contactName", owner);
			format(ContactData[playerid][i][contactName], 128, owner);			
			cache_get_value_name_int(i, "contactNumber", ContactData[playerid][i][contactNumber]);
		}	
	}
}

function OnContactAdd(playerid, id)
{
	ContactData[playerid][id][contactID] = cache_insert_id();
	return 1;
}

GetNumberOwner(number)
{
	foreach (new i : Player) if (pData[i][pPhone] == number)
	{
		return i;
	}
	return INVALID_PLAYER_ID;
}

GetContactNameByNumber(playerid, number)
{
    new 
        name[MAX_PLAYER_NAME];

    for (new i = 0; i != MAX_CONTACTS; i ++) if(ContactData[playerid][i][contactExists] && ContactData[playerid][i][contactNumber] == number) {
        format(name, 24, "%s", ContactData[playerid][i][contactName]);
        return name;
    }
    format(name, 24, "Unknown");
    return name;
}

stock ShowContacts(playerid)
{
	new
	    string[32 * MAX_CONTACTS],
		count = 0;

	string = "Add Contact\n";

	for (new i = 0; i != MAX_CONTACTS; i ++) if (ContactData[playerid][i][contactExists]) 
	{
	    format(string, sizeof(string), "%s%s - "YELLOW_E"#%d\n", string, ContactData[playerid][i][contactName], ContactData[playerid][i][contactNumber]);

		ListedContacts[playerid][count++] = i;
	}
	Dialog_Show(playerid, Contacts, DIALOG_STYLE_LIST, "My Contacts", string, "Select", "Back");
	return 1;
}

ShowPlayerSMS(playerid)
{
	new query[512], list[4056], type, number, msg[1012];
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM sms WHERE owner = '%d' ORDER BY id ASC", pData[playerid][pID]);
	mysql_query(g_SQL, query);
	new rows = cache_num_rows();
	if(rows)
	{
		format(list, sizeof(list), "Info\tMessage\n");
		for(new i = 0; i < rows; i++)
		{
			cache_get_value_name_int(i, "type", type);
			cache_get_value_name_int(i, "number", number);
			cache_get_value_name(i, "message", msg);
			switch(type)
			{
				case 1:
				{
					format(list, sizeof(list), "%sSMS To #%d\t%s\n", list, number, msg);
				}
				case 2:
				{
					format(list, sizeof(list), "%sSMS From #%d\t%s\n", list, number, msg);
				}
			}
		}
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "SMS History", list, "Close", "");
	}
	return 1;
}

function OnSMSsend(playerid, no, sms[])
{
	new name[32], id, String[212];
	if(cache_num_rows() > 0)
	{
		cache_get_value_name(0, "username", name);
		cache_get_value_name_int(0, "reg_id", id);	
		new query[512];
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO sms(owner, message, number, type) VALUES ('%d', '%s', '%d', '%d')", id, sms, pData[playerid][pPhone], 2);
		mysql_tquery(g_SQL, query);

		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO sms(owner, message, number, type) VALUES ('%d', '%s', '%d', '%d')", pData[playerid][pID], sms, no, 1);
		mysql_tquery(g_SQL, query);

		new nametarget[32];
		for (new i = 0; i != MAX_CONTACTS; i ++) if (ContactData[playerid][i][contactExists]) 
		{
			if(no == ContactData[playerid][i][contactNumber])
			{
				format(nametarget, 32, "%s", ContactData[playerid][i][contactName]);
			}
			else
			{
				format(nametarget, 32, "%s", "Unknow");
			}
		}
		SendClientMessageEx(playerid, COLOR_WHITE, "AME: {C2A2DA}types something to his cellphone");
		format(String, sizeof(String), "types something to his cellphone");
		SetPlayerChatBubble(playerid, String, COLOR_PURPLE, 5.0, 5000);
		SendClientMessageEx(playerid, COLOR_RED, "SMS: "YELLOW_E"Message sent to {00FFFF}%s (%d)", nametarget, no);
		SendClientMessageEx(playerid, COLOR_RED, "MESSAGE: "YELLOW_E"%s", sms);
	}
	return 1;
}
