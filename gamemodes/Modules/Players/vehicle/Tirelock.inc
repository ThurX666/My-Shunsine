
timer Vehicle_LockTireUpdate[1000](vehicleid)
{
    new Float:distance = GetVehicleDistanceFromPoint(pvData[vehicleid][cVeh], pvData[vehicleid][cPosX], pvData[vehicleid][cPosY], pvData[vehicleid][cPosZ]);
    if(distance >= Float:2.0)
    {
        if(pvData[vehicleid][vLockTire] == 1)
        {
            SetVehicleZAngle(pvData[vehicleid][cVeh], pvData[vehicleid][cPosA]);
            SetVehiclePos(pvData[vehicleid][cVeh], pvData[vehicleid][cPosX], pvData[vehicleid][cPosY], pvData[vehicleid][cPosZ]);
        }
    }
	return 1;
}

// IsVehicleInRangeOfPoint(vehicleid, Float:range, Float:x, Float:y, Float:z)
// {
//     if(GetVehicleDistanceFromPoint(pvData[vehicleid][cVeh], pvData[vehicleid][cPosX], pvData[vehicleid][cPosY], pvData[vehicleid][cPosZ]) <= 2)  return 1;
//     return -1;
// }

Vehicle_StopLockTire(vehicleid)
{
	if(Iter_Contains(PVehicles, vehicleid))
	{
		if(pvData[vehicleid][vLockTire])
		{
			stop pvData[vehicleid][vLockTireTimer];
		}
		return 1;
	}
	return 0;
}

Vehicle_StartLockTire(vehicleid)
{
	if(Iter_Contains(PVehicles, vehicleid))
	{
		pvData[vehicleid][vLockTire] = 1;
		pvData[vehicleid][vLockTireTimer] = repeat Vehicle_LockTireUpdate(vehicleid);
		return 1;
	}
	return 0;
}

alias:tirelock("locktire")
CMD:tirelock(playerid, params[])
{
	if(pData[playerid][pFaction] != 1) return Error(playerid, "Anda bukan petugas kepolisian.");
	if(pData[playerid][pOnDuty] != 1) return Error(playerid, "Anda harus on duty.");
	new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false), denda[52], totalcash[52];
	if(vehicleid == INVALID_VEHICLE_ID) return SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You not in near any vehicles.");
	if(sscanf(params, "s[52]", denda)) return Usage(playerid, "/padlock [ammount(dollar)]");
    format(totalcash, sizeof(totalcash), "%d00", strval(denda));
	foreach(new ii : PVehicles)
	{
		if(vehicleid == pvData[ii][cVeh])
		{
			if(!pvData[ii][vLockTire])
            {
                GetVehiclePos(pvData[ii][cVeh], pvData[ii][cPosX], pvData[ii][cPosY], pvData[ii][cPosZ]);
                GetVehicleZAngle(pvData[ii][cVeh], pvData[ii][cPosA]);

                if(!IsValidDynamic3DTextLabel(pvData[ii][vLockTireText]))
                    pvData[ii][vLockTireText] = CreateDynamic3DTextLabel("*Vehicle is padlocked*", COLOR_PURPLE, pvData[ii][cPosX], pvData[ii][cPosY], pvData[ii][cPosZ], 15, INVALID_PLAYER_ID, pvData[ii][cVeh], 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
                
                Vehicle_StartLockTire(ii);
                pvData[ii][cTicket] += strval(totalcash);
                SendCustomMessage(playerid, "VEHICLE", "Padlock has been applied to "AQUA_E"%s", GetVehicleName(vehicleid));
                ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
            }
		}
	}
	return 1;
}

CMD:impound(playerid, params[])
{
	if(pData[playerid][pFaction] != 1) return Error(playerid, "Anda bukan petugas kepolisian.");
	if(pData[playerid][pOnDuty] != 1) return Error(playerid, "Anda harus on duty.");
	new reason[212];
	if(sscanf(params, "s[212]", reason)) return Usage(playerid, "/impound [reason impound]");
	new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);
	if(vehicleid == INVALID_VEHICLE_ID)
		return SendClientMessageEx(playerid, COLOR_ARWIN, "VEHICLE: "WHITE_E"You not in near any vehicles.");
	
	foreach(new ii : PVehicles)
	{
		if(vehicleid == pvData[ii][cVeh])
		{
			foreach(new pid : Player) if (pvData[ii][cOwner] == pData[pid][pID])
			{
				new str[32];
				switch (pData[playerid][pFaction]) {
					case 1: format(str,sizeof(str),"Police");
				}
				SendCustomMessage(pid, "IMPOUND", "Your "YELLOW_E"%s "WHITE_E"has been impounded by {2641FE}%s "WHITE_E"for "GREEN_E"$%s "WHITE_E"reason "YELLOW_E"%s", GetVehicleName(vehicleid), str, FormatMoney(pvData[ii][cPrice]/80), reason);
				SendFactionMessage(1, COLOR_RADIO, "HQ: %s has impounded %s's %s.", ReturnName2(playerid),  ReturnName2(pid), GetVehicleName(vehicleid));		
				pvData[ii][cImpound] = 1;	
				pvData[ii][cimpoundTake] = -1;
				if(IsValidVehicle(pvData[ii][cVeh])) DestroyVehicle(pvData[ii][cVeh]);
				pvData[ii][cVeh] = INVALID_VEHICLE_ID;
				format(pvData[ii][cImpoundReason], 212, "%s", reason);
			}
		}
	}
	return 1;
}

CMD:ticket(playerid, params[])
{
	if(pData[playerid][pFaction] != 1) return Error(playerid, "You must be a sapd officer.");
	if(pData[playerid][pOnDuty] != 1) return Error(playerid, "Anda harus on duty.");
	new denda[52], totalcash[52];
	if(sscanf(params, "s[52]", denda))
		return Usage(playerid, "/ticket [ammount(dollar)]");
	
	new nearid = GetNearestVehicleToPlayer(playerid, 5.0, false);
	format(totalcash, sizeof(totalcash), "%d00", strval(denda));
	foreach(new ii : PVehicles)
	{
		if(nearid == pvData[ii][cVeh])
		{
			pvData[ii][cTicket] += strval(totalcash);
			pvData[ii][cTicketTime] = 3600;
			SendClientMessageEx(playerid, COLOR_ARWIN, "TICKET: "WHITE_E"You have ticketed the vehicle {00FFFF}%s "WHITE_E"with a fine of a certain amount "GREEN_E"$%s", GetVehicleName(pvData[ii][cVeh]), FormatMoney(strval(totalcash)));
			return 1;
		}
	}
	return 1;
}

CMD:payticket(playerid, params[])
{
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 3 && IsPlayerInRangeOfPoint(playerid, 2.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
			new found = false, msg2[512];
			format(msg2, sizeof(msg2), "Vehicle\tTicket Pay\n");
			foreach(new i : PVehicles)
			{
				if(pvData[i][cOwner] == pData[playerid][pID])
				{
					if(pvData[i][cTicket] > 0) {
						new price = pvData[i][cTicket];
						gListedItems[playerid][found] = i;
						found++;
						format(msg2, sizeof(msg2), "%s{00FFFF}%s\t"GREEN_E"$%s\n", msg2, GetVehicleModelName(pvData[i][cModel]), FormatMoney(price));
					}
				}
				if(found) Dialog_Show(playerid, VehiclePayTicket, DIALOG_STYLE_TABLIST_HEADERS, "Pay Ticket", msg2, "Pay", "Close");
			}
		}
	}
	return 1;
}

CMD:unlocktire(playerid, params[])
{
	foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
		if(Location[id][locType] == 3 && IsPlayerInRangeOfPoint(playerid, 2.0, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
			new found = false, msg2[512];
			format(msg2, sizeof(msg2), "Vehicle\tTicket Pay\n");
			foreach(new i : PVehicles)
			{
				if(pvData[i][cOwner] == pData[playerid][pID])
				{
					if(pvData[i][vLockTire] > 0) {
						new price = pvData[i][cTicket];
						gListedItems[playerid][found] = i;
						found++;
						format(msg2, sizeof(msg2), "%s{00FFFF}%s\t"GREEN_E"$%s\n", msg2, GetVehicleModelName(pvData[i][cModel]), FormatMoney(price));
					}
				}
				if(found) Dialog_Show(playerid, VehiclePayTicket, DIALOG_STYLE_TABLIST_HEADERS, "Unlock Tire", msg2, "Pay", "Close");
			}
		}
	}
	return 1;
}

CMD:unimpound(playerid, params[])
{		
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1579.75, -1631.52, 13.38)) return Error(playerid, "You must be at the impound center");
	new found = false, msg2[512];
	format(msg2, sizeof(msg2), "Vehicle\tFine\tReason\n");
	foreach(new i : PVehicles)
	{
		if(pvData[i][cOwner] == pData[playerid][pID])
		{
			if(pvData[i][cImpound] == 1)
			{
				new price = pvData[i][cPrice]/55;
				gListedItems[playerid][found] = i;
				found++;
				format(msg2, sizeof(msg2), "%s{00FFFF}%s\t"GREEN_E"$%s\t%s\n", msg2, GetVehicleModelName(pvData[i][cModel]), FormatMoney(price), pvData[i][cImpoundReason]);
			}
		}	
	}
	if(found) Dialog_Show(playerid, VehicleImpound, DIALOG_STYLE_TABLIST_HEADERS, "Claim Impound", msg2, "Claim", "Close");
	else Error(playerid, "Vehicle is not ready to bey claimed");
	return 1;
}
