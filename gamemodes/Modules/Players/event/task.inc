
task ZombieTimer[1000]()
{
	if(!EventData[eventStart]) return 1;
	static EventZombieWinner=0;
	if(EventData[eventTypes] == TYPE_ZOMBIE)
	{
		if(EventData[eventMinutes] > 0)
		{
			EventData[eventTimer]--;
			if(EventData[eventTimer] <= 0)
			{
				EventData[eventTimer] = 60;
				EventData[eventMinutes]--;
			}
			foreach(new playerid : Player) if(IsPlayerInEvent(playerid))
			{
				if(eventZombieCD[playerid] > 0)
				{
					eventZombieCD[playerid]--;
					if(eventZombieCD[playerid] <= 0)
					{
						eventZombieCD[playerid] = 0;
						GameTextForPlayer(playerid, "Skill Ready", 4000, 6);
					}
				}
			}
		}
		else
		{
			foreach(new playerid : Player) if(IsPlayerInEvent(playerid))
			{
				if(EventData[eventHumans] > 0)
				{
					EventZombieWinner = TEAM_A;
					SendCustomMessage(playerid, "EVENT", ""GREEN_E"Humans"YELLOW_E" has won the event!");
				}
				else
				{
					EventZombieWinner = TEAM_B;
					SendCustomMessage(playerid, "EVENT", ""RED_E"Zombie"YELLOW_E" has won the event!");
				}
				if(eventTeams[playerid] == EventZombieWinner)
				{
					SendCustomMessage(playerid, "EVENT", "You've received a prize of "GREEN_E"$%s"WHITE_E" for winning the event!", FormatMoney(EventData[eventBonuses]*3));
					GivePlayerMoneyEx(playerid, EventData[eventBonuses]*3);
				}
				else
				{
					SendCustomMessage(playerid, "EVENT", "You've received "GREEN_E"$%s"WHITE_E" for event participation bonus!", FormatMoney(EventData[eventBonuses]));
					GivePlayerMoneyEx(playerid, EventData[eventBonuses]);
				}
				eventLeave(playerid);
				static const empty_player[E_EVENT];
				EventData = empty_player;
			}
		}
		EventTextdrawSetString();
	}
	return 1;
}

task EventDelay[1000]() 
{
	if(!EventData[eventOpen]) return 1;
	if(EventData[eventCountdown] > 0)
	{
		EventData[eventCountdown] --;
		new str[256];
		format(str, sizeof(str), "~w~STARTING IN: ~n~~y~%d Second", EventData[eventCountdown]);
		foreach(new playerid : Player) if(IsPlayerInEvent(playerid))
		{
			GameTextForPlayer(playerid, str, 1000, 6);
		}
	}
	else
	{
		if(!eventCount())
		{
			SendClientMessageToAllEx(COLOR_ARWIN, "EVENT: "YELLOW_E"Event dibatalkan karena. Karena, tidak ada satupun yang ikut berpartisipasi.");
			static const empty_player[E_EVENT];
	    	EventData = empty_player;
		}
		else
		{
			EventData[eventOpen] = 0;
			foreach(new playerid : Player) if(IsPlayerInEvent(playerid))
			{
				if(EventData[eventTypes] == TYPE_ZOMBIE)
				{
					EventData[eventTimer] = 60;
					EventData[eventMinutes] = 10;
					if(eventTeams[playerid] == TEAM_A)
					{
						for(new i = 0; i != 3; i++) 
						{
							if(EventData[eventWeapons][i]) 
							{
								GivePlayerEventWeapon(playerid, EventData[eventWeapons][i], EventData[eventAmmo][i]);
							}
						}
					}
					else if(eventTeams[playerid] == TEAM_B)
					{
						SetPlayerSkin(playerid, eventZombieSkin[playerid]);
						SetPlayerPos(playerid, EventData[eventSpawnX_DM], EventData[eventSpawnY_DM], EventData[eventSpawnZ_DM]);

						GivePlayerEventWeapon(playerid, 9, 1);
					}
				}
				else
				{
					for(new i = 0; i != 3; i++) 
					{
						if(EventData[eventWeapons][i]) 
						{
							GivePlayerEventWeapon(playerid, EventData[eventWeapons][i], EventData[eventAmmo][i]);
						}
					}
				}
			}
			EventData[eventStart] = 1;
		}
	}
    return 1;	
}
