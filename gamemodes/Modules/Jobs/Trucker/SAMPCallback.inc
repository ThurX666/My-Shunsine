#include <YSI\y_hooks>
hook OnPlayerEnterRaceCP(playerid) {
    if(SedangHauling[playerid] > 0)
	{
		if(SedangHauling[playerid] == 2)
		{
			if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
			{
			    DisablePlayerRaceCheckpoint(playerid);
                SedangHauling[playerid] = 0;
				AddPlayerSalary(playerid, "Ocean Dock Imports", "Delivered cargo", 35000);
                DelayPlayer[playerid][DelayHauling] += 10*60;
                DialogHauling[0] = false;
                DialogSaya[playerid][0] = false;
				TextDrawSetString(TDMoneyHauling[0], (DialogHauling[0] == true) ? ("~r~Taken") : ("~g~$350.00"));
				if(DialogHauling[0] == false) TextDrawBoxColor(TDBoxHauling[0], 9109759);
				foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[0]);
                DestroyVehicle(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
				SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                return 1;
			}
		}
		else if(SedangHauling[playerid] == 4)
		{
			if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
			{
			    DisablePlayerRaceCheckpoint(playerid);
                SedangHauling[playerid] = 0;
				AddPlayerSalary(playerid, "Ocean Dock Imports", "Delivered cargo", 30000);
                DelayPlayer[playerid][DelayHauling] += 10*60;
                DialogHauling[1] = false;
                DialogSaya[playerid][1] = false;
				TextDrawSetString(TDMoneyHauling[1], (DialogHauling[1] == true) ? ("~r~Taken") : ("~g~$300.00"));
				if(DialogHauling[1] == false) TextDrawBoxColor(TDBoxHauling[1], 9109759);
				foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[1]);
                DestroyVehicle(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
                SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                return 1;
			}
		}
		else if(SedangHauling[playerid] == 6)
		{
			if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
			{
			    DisablePlayerRaceCheckpoint(playerid);
                SedangHauling[playerid] = 0;
				AddPlayerSalary(playerid, "Angel Pine Exports", "Delivered cargo", 25000);
                DelayPlayer[playerid][DelayHauling] += 10*60;
                DialogHauling[2] = false;
                DialogSaya[playerid][2] = false;
				TextDrawSetString(TDMoneyHauling[2], (DialogHauling[2] == true) ? ("~r~Taken") : ("~g~$250.00"));
				if(DialogHauling[2] == false) TextDrawBoxColor(TDBoxHauling[2], 9109759);
				foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[2]);
                DestroyVehicle(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
                SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                return 1;
			}
		}
		else if(SedangHauling[playerid] == 8)
		{
			if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
			{
			    DisablePlayerRaceCheckpoint(playerid);
                SedangHauling[playerid] = 0;
				AddPlayerSalary(playerid, "Angel Pine Exports", "Delivered cargo", 27000);
                DelayPlayer[playerid][DelayHauling] += 10*60;
                DialogHauling[3] = false;
                DialogSaya[playerid][3] = false;
				TextDrawSetString(TDMoneyHauling[3], (DialogHauling[3] == true) ? ("~r~Taken") : ("~g~$270.00"));
				if(DialogHauling[3] == false) TextDrawBoxColor(TDBoxHauling[3], 9109759);
				foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[3]);
                DestroyVehicle(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
                SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                return 1;
			}
		}
		else if(SedangHauling[playerid] == 10)
		{
			if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
			{
			    DisablePlayerRaceCheckpoint(playerid);
                SedangHauling[playerid] = 0;
				AddPlayerSalary(playerid, "Chilliad Deport", "Delivered cargo", 39900);
                DelayPlayer[playerid][DelayHauling] += 10*60;
                DialogHauling[4] = false;
                DialogSaya[playerid][4] = false;
				TextDrawSetString(TDMoneyHauling[4], (DialogHauling[4] == true) ? ("~r~Taken") : ("~g~$399.00"));
				if(DialogHauling[4] == false) TextDrawBoxColor(TDBoxHauling[4], 9109759);
				foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[4]);
                DestroyVehicle(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
                SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                return 1;
			}
		}
		else if(SedangHauling[playerid] == 12)
		{
			if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
			{
			    DisablePlayerRaceCheckpoint(playerid);
                SedangHauling[playerid] = 0;
				AddPlayerSalary(playerid, "Chilliad Deport", "Delivered cargo", 20000);
                DelayPlayer[playerid][DelayHauling] += 10*60;
                DialogHauling[5] = false;
                DialogSaya[playerid][5] = false;
				TextDrawSetString(TDMoneyHauling[5], (DialogHauling[5] == true) ? ("~r~Taken") : ("~g~$200.00"));
				if(DialogHauling[5] == false) TextDrawBoxColor(TDBoxHauling[5], 9109759);
				foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[5]);
                DestroyVehicle(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
                SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                return 1;
			}
		}
		else if(SedangHauling[playerid] == 14)
		{
			if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
			{
			    DisablePlayerRaceCheckpoint(playerid);
                SedangHauling[playerid] = 0;
				AddPlayerSalary(playerid, "Easter Import", "Delivered cargo", 31000);
                DelayPlayer[playerid][DelayHauling] += 10*60;
                DialogHauling[6] = false;
                DialogSaya[playerid][6] = false;
				TextDrawSetString(TDMoneyHauling[6], (DialogHauling[6] == true) ? ("~r~Taken") : ("~g~$310.00"));
				if(DialogHauling[6] == false) TextDrawBoxColor(TDBoxHauling[6], 9109759);
				foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[6]);
                DestroyVehicle(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
                SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                return 1;
			}
		}
		else if(SedangHauling[playerid] == 16)
		{
			if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
			{
			    DisablePlayerRaceCheckpoint(playerid);
                SedangHauling[playerid] = 0;
				AddPlayerSalary(playerid, "Blueberry Export", "Delivered cargo", 33300);
                DelayPlayer[playerid][DelayHauling] += 10*60;
                DialogHauling[7] = false;
                DialogSaya[playerid][7] = false;
				TextDrawSetString(TDMoneyHauling[7], (DialogHauling[7] == true) ? ("~r~Taken") : ("~g~$333.00"));
				if(DialogHauling[7] == false) TextDrawBoxColor(TDBoxHauling[7], 9109759);
				foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[7]);
                DestroyVehicle(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
                SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                return 1;
			}
		}
		else if(SedangHauling[playerid] == 18)
		{
			if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
			{
			    DisablePlayerRaceCheckpoint(playerid);
                SedangHauling[playerid] = 0;
				AddPlayerSalary(playerid, "Las Venturas Deport", "Delivered cargo", 29000);
                DelayPlayer[playerid][DelayHauling] += 10*60;
                DialogHauling[8] = false;
                DialogSaya[playerid][8] = false;
				TextDrawSetString(TDMoneyHauling[8], (DialogHauling[8] == true) ? ("~r~Taken") : ("~g~$290.00"));
				if(DialogHauling[8] == false) TextDrawBoxColor(TDBoxHauling[8], 9109759);
				foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[8]);
                DestroyVehicle(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
                SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                return 1;
			}
		}
		else if(SedangHauling[playerid] == 20)
		{
			if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
			{
			    DisablePlayerRaceCheckpoint(playerid);
                SedangHauling[playerid] = 0;
				AddPlayerSalary(playerid, "Las Venturas Fuel & Gas", "Delivered cargo", 22500);
                DelayPlayer[playerid][DelayHauling] += 10*60;
                DialogHauling[9] = false;
                DialogSaya[playerid][9] = false;
				TextDrawSetString(TDMoneyHauling[9], (DialogHauling[9] == true) ? ("~r~Taken") : ("~g~$255.00"));
				if(DialogHauling[9] == false) TextDrawBoxColor(TDBoxHauling[9], 9109759);
				foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[9]);
                DestroyVehicle(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
                SendClientMessage(playerid, COLOR_ARWIN, "SALARY: "WHITE_E"Your salary statement has been update, please check command "YELLOW_E"'/mysalary'");
                return 1;
			}
		}
		return 1;
	}
    return 1;
}
