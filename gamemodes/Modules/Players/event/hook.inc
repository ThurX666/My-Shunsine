#include <YSI\y_hooks>

hook OnPlayerDeath(playerid, killerid, reason)
{
	if(IsPlayerInEvent(playerid)) {
		ClearAnimations(playerid);
		if(killerid != INVALID_PLAYER_ID) {
			if(EventData[eventTypes] == TYPE_TDM) {
				EventData[eventScore][eventTeams[killerid]-1]++;
				EventTextdrawSetString();
				foreach(new i : Player) {
					if(eventTeams[playerid] == TEAM_A) {
						new string[212];
						format(string, 212, ""BLUE_E"%s "YELLOW_E"has killed "RED_E"%s"YELLOW_E", Team B Score:"GREEN_E"%d/%d", ReturnName2(killerid), ReturnName2(playerid), EventData[eventScore][eventTeams[killerid]-1], EventData[eventTargets]); 
						SendEventMessageAll(COLOR_ARWIN, string); 
					}
					if(eventTeams[playerid] == TEAM_B) {
						new string[212];
						format(string, 212, ""RED_E"%s "YELLOW_E"has killed "BLUE_E"%s"YELLOW_E", Team A Score:"GREEN_E"%d/%d", ReturnName2(killerid), ReturnName2(playerid), EventData[eventScore][eventTeams[killerid]-1], EventData[eventTargets]); 
						SendEventMessageAll(COLOR_ARWIN, string); 
					}
					break;
				}
				if(EventData[eventScore][eventTeams[killerid]-1] >= EventData[eventTargets])  {
					EventData[eventWinner] = eventTeams[killerid];
					new string[212];
					format(string, 212, "EVENT: "WHITE_E""YELLOW_E"Team %s "WHITE_E"has won the event!", (eventTeams[killerid] == TEAM_A) ? ("A") : ("B"));
					SendEventMessageAll(COLOR_ARWIN, string);

					foreach(new i : Player) { 
						if(IsPlayerInEvent(i)) {
							if(i == EventData[eventWinner]) {
								GivePlayerMoneyEx(i, EventData[eventBonuses]*3);

								SendCustomMessage(i, "EVENT", "You've reveived a prize of "GREEN_E"$%s"WHITE_E" fir winning the event!", FormatMoney(EventData[eventBonuses]*3));
							}
							else {
								GivePlayerMoneyEx(i, EventData[eventBonuses]);
								SendCustomMessage(i, "EVENT", "You've received "GREEN_E"$%s "WHITE_E"for event participation bonus!.", FormatMoney(EventData[eventBonuses]));
							}
							eventLeave(i);
						}
					}
					static const empty_player[E_EVENT];
					EventData = empty_player;
				}
				else eventWaitingSpawn[playerid] = 1;
			}
			else if(EventData[eventTypes] == TYPE_DM)
			{
				eventScore_DM[killerid]++;
				new string[212];
				format(string, 212, "{00FFFF}%s "YELLOW_E"has killed "RED_E"%s "YELLOW_E"Total Score: "GREEN_E"%d.", ReturnName2(killerid), ReturnName2(playerid), eventScore_DM[killerid]);
				SendEventMessageAll(COLOR_ARWIN, string);
				if(eventScore_DM[killerid] >= EventData[eventTargets])
				{
					EventData[eventWinner] = killerid;
					format(string, 212, "EVENT: "RED_E"%s "YELLOW_E"has won the event!.", ReturnName2(killerid));
					SendEventMessageAll(COLOR_ARWIN, string);

					foreach(new i : Player) if(IsPlayerInEvent(i)) {
						if(i == EventData[eventWinner]){
							GivePlayerMoneyEx(i, EventData[eventBonuses]*3);
							SendCustomMessage(i, "EVENT", "You've reveived a prize of "GREEN_E"$%s"WHITE_E" fir winning the event!", FormatMoney(EventData[eventBonuses]*3));
						} else {
							GivePlayerMoneyEx(i, EventData[eventBonuses]);
							SendCustomMessage(i, "EVENT", "You've received "GREEN_E"$%s "WHITE_E"for event participation bonus!.", FormatMoney(EventData[eventBonuses]));
						}
						eventLeave(i);
					}
					static const empty_player[E_EVENT];
					EventData = empty_player;
				}
				else eventWaitingSpawn[playerid] = 1;
			}
			else if(EventData[eventTypes] == TYPE_ZOMBIE)
			{
				if(eventTeams[playerid] == TEAM_A)
				{
					eventTeams[playerid] = TEAM_B;
					EventData[eventHumans]--;
					if(EventData[eventHumans] > 0) eventWaitingSpawn[playerid] = 1;
					else EventData[eventMinutes] = 0;
				}
				EventTextdrawSetString();
			}
		}
	}
	return 1;
}
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys == KEY_NO)
	{
		if(IsPlayerInEvent(playerid))
		{
			foreach(new otherid : Player) if(IsPlayerInEvent(otherid) && !eventZombieCD[playerid] && otherid != playerid)
			{
				if(NearPlayer(playerid, otherid, 2))
				{
					TogglePlayerControllable(playerid, false);
					eventZombieCD[playerid] = 10;
					GameTextForPlayer(playerid, "Skill Cooldown", 4000, 6);
					SetTimerEx("ClearEventFreeze", 2000, false, "d", playerid);
				}
			}
		}
	}
	return 1;
}

hook OnPlayerText(playerid, text[])
{
	if(IsPlayerInEvent(playerid))
	{
		foreach(new i : Player) if(IsPlayerInEvent(i))
		{ 
			if(EventData[eventTypes] == TYPE_TDM) 
			{
				if (strlen(text) > 64)
				{
					SendClientMessageEx(i, eventTeams[playerid] == TEAM_A ? COLOR_RED : COLOR_BLUE, "%s: "WHITE_E"%.64s ..", ReturnName2(playerid), text);
					SendClientMessageEx(i, eventTeams[playerid] == TEAM_A ? COLOR_RED : COLOR_BLUE, "%s: "WHITE_E".. %s", ReturnName2(playerid), text[64]);
				}
				else
				{
					SendClientMessageEx(i, eventTeams[playerid] == TEAM_A ? COLOR_RED : COLOR_BLUE, "%s: "WHITE_E"%s", ReturnName2(playerid), text);
				}
			}
			if(EventData[eventTypes] == TYPE_ZOMBIE) 
			{
				if (strlen(text) > 64)
				{
					SendClientMessageEx(i, eventTeams[playerid] == TEAM_A ? COLOR_GREEN : COLOR_RED, "%s: "WHITE_E"%.64s ..", ReturnName2(playerid), text);
					SendClientMessageEx(i, eventTeams[playerid] == TEAM_A ? COLOR_GREEN : COLOR_RED, "%s: "WHITE_E".. %s", ReturnName2(playerid), text[64]);
				}
				else
				{
					SendClientMessageEx(i, eventTeams[playerid] == TEAM_A ? COLOR_GREEN : COLOR_RED, "%s: "WHITE_E"%s", ReturnName2(playerid), text);
				}
			}
			else if(EventData[eventTypes] == TYPE_DM)
			{
				if (strlen(text) > 64)
				{
					SendClientMessageEx(i, COLOR_LIGHTRED, "%s: "WHITE_E"%.64s ..", ReturnName2(playerid), text);
					SendClientMessageEx(i, COLOR_LIGHTRED, "%s: "WHITE_E".. %s", ReturnName2(playerid), text[64]);
				}
				else
				{
					SendClientMessageEx(i, COLOR_LIGHTRED, "%s: "WHITE_E"%s", ReturnName2(playerid), text);
				}
			}
		}
	}
	return 1;
}
