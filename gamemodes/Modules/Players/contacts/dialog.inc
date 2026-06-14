
Dialog:SMSReply(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if (isnull(inputtext))
			return Dialog_Show(playerid, SMSReply, DIALOG_STYLE_INPUT, "Message Reply", "Error: Please enter a message to send.\n\nPlease enter the message to send to %d:", "Send", "Back", pData[playerid][pSMS]);

		new ph = pData[playerid][pSMS], String[212];

		if (!ph)
	    return Error(playerid, "The specified phone number is not in service.");
		format(String, sizeof(String), "%d %s", ph, inputtext);
		callcmd::sms(playerid, String);
	}
	return 1;
}

Dialog:MyPhone(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		switch (listitem)
		{
		    case 0:
		    {
		        if (pData[playerid][pPhoneOff])
		            return Error(playerid, "Your phone must be powered on.");

				Dialog_Show(playerid, DialNumber, DIALOG_STYLE_INPUT, "Dial Number", "Please enter the number that you wish to dial below:", "Dial", "Back");
			}
			case 1:
			{
			    if (pData[playerid][pPhoneOff])
		            return Error(playerid, "Your phone must be powered on.");

			    ShowContacts(playerid);
			}
		    case 2:
		    {
		        if (pData[playerid][pPhoneOff])
		            return Error(playerid, "Your phone must be powered on.");

		        Dialog_Show(playerid, SendText, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Dial", "Back");
			}
			case 3:
			{
				if(pData[playerid][pVip] < 1) return PermissionError(playerid);
				if(pData[playerid][pPhonePrivacy] == 1)
				{
					pData[playerid][pPhonePrivacy] = 0;
					SendClientMessageEx(playerid, COLOR_WHITE, "You have disabled the phone privacy feature.");
				}
				else
				{
					pData[playerid][pPhonePrivacy] = 1;
					SendClientMessageEx(playerid, COLOR_WHITE, "You have enabled the phone privacy feature.");
				}
			}
			case 4:
			{
				ShowPlayerSMS(playerid);
			}
			case 5:
			{
			    if (!pData[playerid][pPhoneOff])
			    {
					pData[playerid][pPhoneOff] = 1;
			        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has powered off their cellphone.", ReturnName(playerid));
				}
				else
				{
				    pData[playerid][pPhoneOff] = 0;
			        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has powered on their cellphone.", ReturnName(playerid));
				}
			}
		}
	}
	return 1;
}

Dialog:SendText(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new number = strval(inputtext);

	    if (isnull(inputtext) || !IsNumeric(inputtext))
	        return Dialog_Show(playerid, SendText, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Dial", "Back");

        if (GetNumberOwner(number) == INVALID_PLAYER_ID)
            return Dialog_Show(playerid, SendText, DIALOG_STYLE_INPUT, "Send Text Message", "Error: That number is not online right now.\n\nPlease enter the number that you wish to send a text message to:", "Dial", "Back");

		pData[playerid][pContact] = GetNumberOwner(number);
		Dialog_Show(playerid, TextMessage, DIALOG_STYLE_INPUT, "Text Message", "Please enter the message to send to %s:", "Send", "Back", ReturnName(pData[playerid][pContact]));
	}
	else
	{
		return callcmd::phone(playerid, "\1");
	}
	return 1;
}

Dialog:TextMessage(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if (isnull(inputtext))
			return Dialog_Show(playerid, TextMessage, DIALOG_STYLE_INPUT, "Text Message", "Error: Please enter a message to send.\n\nPlease enter the message to send to %s:", "Send", "Back", ReturnName(pData[playerid][pContact]));

		new ph = pData[playerid][pContact], String[212];

		if (!ph)
	    return Error(playerid, "The specified phone number is not in service.");
		format(String, sizeof(String), "%d %s", ph, inputtext);
		callcmd::sms(playerid, String);
	}
	else 
	{
        Dialog_Show(playerid, SendText, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Submit", "Back");
	}
	return 1;
}

Dialog:DialNumber(playerid, response, listitem, inputtext[])
{
	if (response)
	{

	    if (isnull(inputtext) || !IsNumeric(inputtext))
	        return Dialog_Show(playerid, DialNumber, DIALOG_STYLE_INPUT, "Dial Number", "Please enter the number that you wish to dial below:", "Dial", "Back");
	}
	else 
	{
		return callcmd::phone(playerid, "\1");
	}
	return 1;
}

Dialog:EnterNumber(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    static
	        name[32],
			string[128];

		strunpack(name, pData[playerid][pEditingItem]);

	    if (isnull(inputtext) || !IsNumeric(inputtext))
	        return Dialog_Show(playerid, EnterNumber, DIALOG_STYLE_INPUT, "Contact Number", "Contact Name: %s\n\nPlease enter the phone number for this contact:", "Submit", "Back", name);

		for (new i = 0; i != MAX_CONTACTS; i ++)
		{
			if (!ContactData[playerid][i][contactExists])
			{
            	ContactData[playerid][i][contactExists] = true;
            	ContactData[playerid][i][contactNumber] = strval(inputtext);

				format(ContactData[playerid][i][contactName], 32, name);

				format(string, sizeof(string), "INSERT INTO `contacts` (`ID`, `contactName`, `contactNumber`) VALUES('%d', '%s', '%d')", pData[playerid][pID], name, ContactData[playerid][i][contactNumber]);
				mysql_tquery(g_SQL, string, "OnContactAdd", "dd", playerid, i);

				Info(playerid, "You have added \"%s\" to your contacts.", name);
                return 1;
			}
	    }
	    Error(playerid, "There is no room left for anymore contacts.");
	}
	else {
		ShowContacts(playerid);
	}
	return 1;
}

Dialog:NewContact(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (isnull(inputtext))
			return Dialog_Show(playerid, NewContact, DIALOG_STYLE_INPUT, "New Contact", "Error: Please enter a contact name.\n\nPlease enter the name of the contact below:", "Submit", "Back");

	    if (strlen(inputtext) > 32)
	        return Dialog_Show(playerid, NewContact, DIALOG_STYLE_INPUT, "New Contact", "Error: The contact name can't exceed 32 characters.\n\nPlease enter the name of the contact below:", "Submit", "Back");

		strpack(pData[playerid][pEditingItem], inputtext, 32);

	    Dialog_Show(playerid, EnterNumber, DIALOG_STYLE_INPUT, "Contact Number", "Contact Name: %s\n\nPlease enter the phone number for this contact:", "Submit", "Back", inputtext);
	}
	else 
	{
		ShowContacts(playerid);
	}
	return 1;
}

Dialog:ContactInfo(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new
			id = pData[playerid][pContact],
			string[72];

		switch (listitem)
		{
		    case 0:
		    {
				new phonenumb = ContactData[playerid][id][contactNumber], String[212];
				foreach(new ii : Player)
				{
					if(pData[ii][pPhone] == phonenumb)
					{
						if(pData[ii][IsLoggedIn] == false || !IsPlayerConnected(ii)) return Error(playerid, "This number is not actived!");
						if(pData[ii][pPhoneOff] == 1) return Error(playerid, "The specified phone number went offline");
						if(pData[ii][pCall] == INVALID_PLAYER_ID)
						{
							pData[playerid][pCall] = ii;

							format(String, sizeof(String), "PHONE: {ffffff}Ponsel anda berbunyi!, nomor {ffff00}%s (%d) {ffffff}mencoba untuk menghubungi anda, /p untuk menjawab", GetContactNameByNumber(ii, pData[playerid][pPhone]), pData[playerid][pPhone]);
							SendClientMessageEx(ii, COLOR_ARWIN, String);
							format(String, sizeof(String), "PHONE: {ffffff}Anda telah mencoba menghubungi nomor {ffff00}%s (%d) {ffffff}silahkan tunggu sampai di jawab", GetContactNameByNumber(playerid, pData[ii][pPhone]), phonenumb);
							SendClientMessageEx(playerid, COLOR_ARWIN, String);
							PlayerPlaySound(playerid, 1052, 0,0,0);
							PlayerPlaySound(ii, 1139, 0,0,0);
							SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
							SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s takes out a cellphone and calling someone.", ReturnName(playerid));
							return 1;
						}
						else
						{
							Error(playerid, "Nomor ini sedang sibuk.");
							return 1;
						}
					}
				}
		    }
		    case 1:
		    {
		        format(string, sizeof(string), "DELETE FROM `contacts` WHERE `ID` = '%d' AND `contactID` = '%d'", pData[playerid][pID], ContactData[playerid][id][contactID]);
		        mysql_tquery(g_SQL, string);

		        Info(playerid, ""WHITE_E"You have deleted "YELLOW_E"%s "WHITE_E"from your contacts.", ContactData[playerid][id][contactName]);

		        ContactData[playerid][id][contactExists] = false;
		        ContactData[playerid][id][contactNumber] = 0;
		        ContactData[playerid][id][contactID] = 0;
		        ShowContacts(playerid);
		    }
		}
	}
	else 
	{
	    ShowContacts(playerid);
	}
	return 1;
}

Dialog:Contacts(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (!listitem) 
	    {
	        Dialog_Show(playerid, NewContact, DIALOG_STYLE_INPUT, "New Contact", "Please enter the name of the contact below:", "Submit", "Back");
	    }
	    else 
	    {
		    pData[playerid][pContact] = ListedContacts[playerid][listitem - 1];

	        Dialog_Show(playerid, ContactInfo, DIALOG_STYLE_LIST, ContactData[playerid][pData[playerid][pContact]][contactName], "Call Contact\nDelete Contact", "Select", "Back");
	    }
	}
	else 
	{
		return callcmd::phone(playerid, "\1");
	}
	for (new i = 0; i != MAX_CONTACTS; i ++) {
	    ListedContacts[playerid][i] = -1;
	}
	return 1;
}