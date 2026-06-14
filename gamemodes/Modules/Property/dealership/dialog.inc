
Dialog:ShowDealer_Employee(playerid, response, listitem, inputtext[]) {
    static
        bizid = -1;

    if((bizid = GetPVarInt(playerid, "editingcd")) != -1)
    {
		if (response) {
			switch(listitem)
			{
				case 0: {
					Dialog_Show(playerid, Dealer_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Masukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");
				}
				case 1: {
					Dealer_ShowEmployee(playerid, bizid, 1);
				}
				case 2: {
					DealerEmployee_RemoveAll(bizid);
					SendCustomMessage(playerid, "BUSINESS", "You've remove all employe on this business.");
				}
				case 3: Dealer_ShowEmployee(playerid, bizid, 0);
			}
		} else callcmd::bm(playerid, "\1");
	}
    return 1;
}

Dialog:Dealer_RemoveEmployee(playerid, response, listitem, inputtext[]) {
    if (response) {
        DealerEmployee_Remove(strval(inputtext));
		SendCustomMessage(playerid, "BUSINESS", "You've remove list employee number #%d from your business.", strval(inputtext));
    }
    return 1;
}

Dialog:Dealer_AddEmployee(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		new id,
			bizid = GetPVarInt(playerid, "editingcd");

		if (DealerEmployee_GetCount(bizid) >= 3) return Error(playerid, "This business is limited 3 employee.");
		if (sscanf(inputtext, "u", id)) return Dialog_Show(playerid, Dealer_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Masukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");
		if (!IsPlayerConnected(id)) return Dialog_Show(playerid, Dealer_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Player yang kamu masukkan tidak terkoneksi dalam game\nMasukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");
        if (id == playerid) return Dialog_Show(playerid, Dealer_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Tidak dapat memasukkan karakter kamu sendiri\nMasukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");
		if (Dealer_IsEmployee(id, bizid)) return Dialog_Show(playerid, Dealer_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Player tersebut sudah masuk dalam list employee\nMasukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");

		DealerEmployee_Add(id, bizid);
		SendCustomMessage(playerid, "BUSINESS", "Kamu memasukkan "YELLOW_E"%s "WHITE_E"ke dalam list pekerja bisnismu.", pData[id][pName]);
		SendCustomMessage(id, "BUSINESS", YELLOW_E"%s "WHITE_E"mempekerjakan kamu di bisnis miliknya (Bisnis: %s).", pData[playerid][pName], CarDealershipInfo[bizid][cdMessage]);
	}
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    new String[500], string[512], count = CountPlayerVehicle(playerid), found = false;
    if(dialogid == DIALOG_CDEDIT)
	{ // car dealership dialog
		if(response && GetPVarInt(playerid, "editingcd") != -1)
		{
            if(listitem == 0) // My Vehicles
			{
				format(string,sizeof(string),"Vehicle\tCost\n");
				for (new i = 0; i < 10; i ++)
				{
					if(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdVehicleModel][i] != 0) format(string,sizeof(string),"%s{00FFFF}%s\t"GREEN_E"$%s\n", string, GetVehicleName(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdVehicleId][i]),FormatMoney(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdVehicleCost][i]));
					else format(string, sizeof(string), "%sSpawn\n", string);
					gListedItems[playerid][found] = i;
					found++;
				}
				if(found)  ShowPlayerDialog(playerid, DIALOG_CDEDITCARS, DIALOG_STYLE_TABLIST_HEADERS, "Car Dealership:", string, "Edit", "Back");
			}
			else if(listitem == 1) // Till
			{
				new listitems[] = "1 Withdraw\n2 Deposit";
			    ShowPlayerDialog(playerid,DIALOG_CDTILL,DIALOG_STYLE_LIST,"Choose an item to continue", listitems,"Select","Cancel");
			}
			else if(listitem == 2) Dialog_Show(playerid, DialogCDSetting, DIALOG_STYLE_LIST, "Setting Dealership", "Change Name Dealership\nChange Category Dealership", "Select", "Close");
			else if(listitem == 3) Dialog_Show(playerid, ShowDealer_Employee, DIALOG_STYLE_LIST, "Employees Management", "Add Employee\nRemove Employee\nRemove All Employees\nEmployees Members", "Select", "Close");
		}
		else
		{
			SavecDealership(GetPVarInt(playerid, "editingcd"));
            SetPVarInt(playerid, "editingcd", -1);
		}
	}
	else if(dialogid == DIALOG_CDTILL)
	{ // car dealership dialog
	    if(response && GetPVarInt(playerid, "editingcd") != -1)
		{
            if(listitem == 0) // Withdraw
			{
				format(String, sizeof(String), "{FFFFFF}You have {00FF00}$%s {FFFFFF}in your till account.\nHow much money to withdraw?", FormatMoney(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdTill]));
				ShowPlayerDialog(playerid,DIALOG_CDWITHDRAW,DIALOG_STYLE_INPUT,"Withdraw", String,"Select","Cancel");
			}
			else if(listitem == 1) // Deposit
			{
				format(String, sizeof(String), "{FFFFFF}You have {00FF00}$%s {FFFFFF}in your till account.\nHow much money to deposit?", FormatMoney(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdTill]));
				ShowPlayerDialog(playerid,DIALOG_CDDEPOSIT,DIALOG_STYLE_INPUT,"Deposit", String,"Select","Cancel");
			}
		}
		else
		{
            SavecDealership(GetPVarInt(playerid, "editingcd"));
            SetPVarInt(playerid, "editingcd", -1);
		}
	}
	else if(dialogid == DIALOG_CDWITHDRAW)
	{ // car dealership dialog
		if(response && GetPVarInt(playerid, "editingcd") != -1)
		{
		    if(IsNumeric(inputtext))
	        {
	             new money = strval(inputtext);
	             if(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdTill] < money)
	             {
                     format(String, sizeof(String), "You don't have that much in your till!\n\nYou have $%s in your till account.\n\nHow much money to withdraw?", FormatMoney(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdTill]));
				     ShowPlayerDialog(playerid,DIALOG_CDWITHDRAW,DIALOG_STYLE_INPUT,"Withdraw", String,"Select","Cancel");
                     return 1;
	             }
	             CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdTill] -= money;
	             GivePlayerMoneyEx(playerid, money);
	             SendCustomMessage(playerid, "BISNIS", "You have successfully withdrawn "GREEN_E"$%s "WHITE_E"from your till, new balance: "GREEN_E"$%s", FormatMoney(money), FormatMoney(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdTill]));
	             SavecDealership(GetPVarInt(playerid, "editingcd"));
                 SetPVarInt(playerid, "editingcd", -1);
			}
        }
		else
		{
             SavecDealership(GetPVarInt(playerid, "editingcd"));
             SetPVarInt(playerid, "editingcd", -1);
		}
	}
	else if(dialogid == DIALOG_CDDEPOSIT)
	{ // car dealership dialog
		if(response && GetPVarInt(playerid, "editingcd") != -1)
		{
		    if(IsNumeric(inputtext))
	        {
	             new money = strval(inputtext);
	             if(GetPlayerMoney(playerid) < money)
	             {
                     format(String, sizeof(String), "You don't have that much in your wallet!\n\nYou have $%s in your till account.\n\n\tHow much money to deposit?", FormatMoney(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdTill]));
				     ShowPlayerDialog(playerid,DIALOG_CDDEPOSIT,DIALOG_STYLE_INPUT,"Deposit", String,"Select","Cancel");
                     return 1;
	             }
	             CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdTill] += money;
	             GivePlayerMoneyEx(playerid, -money);
	             SendCustomMessage(playerid, "BISNIS", "You have successfully deposited "GREEN_E"$%s "WHITE_E"to your till, new balance: "GREEN_E"$%s", FormatMoney(money), FormatMoney(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdTill]));
	             SavecDealership(GetPVarInt(playerid, "editingcd"));
                 SetPVarInt(playerid, "editingcd", -1);
			}
		}
		else
		{
             SavecDealership(GetPVarInt(playerid, "editingcd"));
             SetPVarInt(playerid, "editingcd", -1);
		}
	}
	else if(dialogid == DIALOG_CDNAME)
	{ // car dealership dialog
		if(response && GetPVarInt(playerid, "editingcd") != -1)
		{
			new d = GetPVarInt(playerid, "editingcd");
            if(!strlen(inputtext))
			{
			    SendClientMessageEx(playerid, COLOR_LIGHTRED, "** You must type a name **");
    	        ShowPlayerDialog(playerid, DIALOG_CDNAME, DIALOG_STYLE_INPUT, "Car Dealership:", " Choose the new name:", "Edit", "Back");
		        return 1;
			}
			strmid(CarDealershipInfo[d][cdMessage], inputtext, 0, strlen(inputtext), 255);
	        format(String,128,"{00FFFF}[id:%d]\n{FFFF00}%s\n{00FF00}Owner: %s",d, CarDealershipInfo[d][cdMessage], CarDealershipInfo[d][cdOwner]);
	        UpdateDynamic3DTextLabelText(CarDealershipInfo[d][cdTextLabel], COLOR_TWAQUA, String);
	        SavecDealership(GetPVarInt(playerid, "editingcd"));
		}
	}
	else if(dialogid == DIALOG_CDEDITCARS)
	{ // car dealership dialog
		if(response && GetPVarInt(playerid, "editingcd") != -1)
		{
			if(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdVehicleModel][gListedItems[playerid][listitem]] == 0)
			{
				pData[playerid][pListitems] = gListedItems[playerid][listitem];
				switch(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdType]) {
					case 1: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Motorcycle, "Dealership Vehicle:", dmvehicle1, sizeof(dmvehicle1));
					case 2: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Motorcycle, "Dealership Vehicle:", dmvehicle2, sizeof(dmvehicle2));
					case 3: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Motorcycle, "Dealership Vehicle:", dmvehicle3, sizeof(dmvehicle3));
					case 4: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Motorcycle, "Dealership Vehicle:", dmvehicle4, sizeof(dmvehicle4));
					case 5: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Motorcycle, "Dealership Vehicle:", dmvehicle5, sizeof(dmvehicle5));
					case 6: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Motorcycle, "Dealership Vehicle:", dmvehicle6, sizeof(dmvehicle6));
					case 7: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Motorcycle, "Dealership Vehicle:", dmvehicle7, sizeof(dmvehicle7));
					case 8: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Motorcycle, "Dealership Vehicle:", dmvehicle8, sizeof(dmvehicle8));
				}
			}
		}
		else
		{
		    new listitems[] = "Restock Vehicles\nBank\nChange Name Dealership\nEmployees";
			ShowPlayerDialog(playerid,DIALOG_CDEDIT,DIALOG_STYLE_LIST,"Choose an item to continue", listitems,"Select","Cancel");
		}
	}
	
	else if(dialogid == DIALOG_CDEDITPARK)
	{ // car dealership dialog
		if(response && GetPVarInt(playerid, "editingcd") != -1 && pData[playerid][pListitems] != -1 &&  GetPVarInt(playerid, "editingcdvehpos") == 1 || GetPVarInt(playerid, "editingcdvehnew"))
		{
			new Float: x, Float: y, Float: z, Float: a;
			GetPlayerPos(playerid,x,y,z);
	        GetPlayerFacingAngle(playerid, a);
			new d = GetPVarInt(playerid, "editingcd");
			new v = pData[playerid][pListitems];
			
			if(IsPlayerInRangeOfPoint(playerid, CarDealershipInfo[d][cdRadius], CarDealershipInfo[d][cdEntranceX], CarDealershipInfo[d][cdEntranceY], CarDealershipInfo[d][cdEntranceZ]))
		    {
				CarDealershipInfo[d][cdVehicleSpawnX][v] = x;
				CarDealershipInfo[d][cdVehicleSpawnY][v] = y;
				CarDealershipInfo[d][cdVehicleSpawnZ][v] = z;
				CarDealershipInfo[d][cdVehicleSpawnAngle][v] = a;
				SetPVarInt(playerid, "editingcdvehpos", 0);
				SetPVarInt(playerid, "editingcdvehnew", 0);
				CreateDealershipPickup(d);

				TogglePlayerControllable(playerid, true);
				SavecDealership(d);
			}
			else
			{
				SendClientMessageEx(playerid, COLOR_GREY, "ERROR: You are out of this Car Dealership radius, please try again.");
				TogglePlayerControllable(playerid, true);
			}
		}
		else if(response && GetPVarInt(playerid, "editingcd") != -1 && GetPVarInt(playerid, "editingcdvehpos") == 2)
		{
			new Float: x, Float: y, Float: z, Float: a;
			new d;
			GetPlayerPos(playerid,x,y,z);
	        GetPlayerFacingAngle(playerid, a);
			d = GetPVarInt(playerid, "editingcd");
			if(IsPlayerInRangeOfPoint(playerid, CarDealershipInfo[d][cdRadius], CarDealershipInfo[d][cdEntranceX], CarDealershipInfo[d][cdEntranceY], CarDealershipInfo[d][cdEntranceZ]))
		    {
				CarDealershipInfo[d][cdVehicleSpawn][0] = x;
				CarDealershipInfo[d][cdVehicleSpawn][1] = y;
				CarDealershipInfo[d][cdVehicleSpawn][2] = z;
				CarDealershipInfo[d][cdVehicleSpawn][3] = a;
				SetPVarInt(playerid, "editingcdvehpos", 0);
				TogglePlayerControllable(playerid, true);
				SavecDealership(d);
			}
			else
			{
				SendClientMessageEx(playerid, COLOR_GREY, "ERROR: You are out of this Car Dealership radius, please try again.");
				TogglePlayerControllable(playerid, true);
			}
		}
		else if(!response && GetPVarInt(playerid, "editingcd") != -1 && GetPVarInt(playerid, "editingcdvehpos") == 2)
		{
            TogglePlayerControllable(playerid, true);
			SetPVarInt(playerid, "editingcdvehpos", 0);
		}
	}
	else if(dialogid == DIALOG_CDNEWVEH)
	{ // car dealership dialog
		if(response && GetPVarInt(playerid, "editingcd") != -1)
		{
			if(listitem == 0) // Motorcycle
			{
				ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Motorcycle, "Dealership Vehicle:", dmvehicle1, sizeof(dmvehicle1));
			}	
			else if(listitem == 1) // SUV
			{
				ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SUV, "Dealership Vehicle:", dmvehicle2, sizeof(dmvehicle2));
			}	
			else if(listitem == 2) // Pickup Vehicles
			{
				ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_PickupVehicles, "Dealership Vehicle:", dmvehicle3, sizeof(dmvehicle3));
			}	
			else if(listitem == 3) // Lowriders
			{
				ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Lowriders, "Dealership Vehicle:", dmvehicle4, sizeof(dmvehicle4));
			}	
			else if(listitem == 4) // Saloons
			{
				ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Saloons, "Dealership Vehicle:", dmvehicle5, sizeof(dmvehicle5));
			}	
			else if(listitem == 5) // Sport
			{
				ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Sport, "Dealership Vehicle:", dmvehicle6, sizeof(dmvehicle6));
			}	
	        else
	        {
				SendClientMessageEx(playerid, COLOR_GREY, "ERROR: You are out of this Car Dealership radius, please try again.");
				TogglePlayerControllable(playerid, true);
	        }
		}
		else
		{
            TogglePlayerControllable(playerid, true);
			SetPVarInt(playerid, "editingcd", -1);
		}
	}
	else if(dialogid == DIALOG_CDBUY)
	{

	    // Account Eating Bug Fix
	    if(!IsPlayerInAnyVehicle(playerid))
		{
		    TogglePlayerControllable(playerid, 1);
			SendClientMessageEx(playerid,COLOR_GRAD2,"You need to be in the vehicle you wish to purchase.");
			return 1;
		}

		new vehicleid = GetPlayerVehicleID(playerid);
		new v = GetCarDealershipVehicleId(vehicleid);
		new d = GetCarDealershipId(vehicleid);
		if(response)
		{
            if(CarDealershipInfo[d][cdVehicleSpawn][0] == 0.0 && CarDealershipInfo[d][cdVehicleSpawn][1] == 0.0 && CarDealershipInfo[d][cdVehicleSpawn][2] == 0.0)
            {
				SendClientMessageEx(playerid, COLOR_GRAD1, "ERROR: The owner of this Car Dealership hasn't set the purchased vehicles spawn point.");
				RemovePlayerFromVehicle(playerid);
				return 1;
            }
            new limit = LimitSlotPlayerVehicle(playerid);
			if(count >= limit)
			{
				SendClientMessageEx(playerid, COLOR_GREY, "ERROR: Slot kendaraan anda penuh");
                RemovePlayerFromVehicle(playerid);
				return 1;
			}
		    new randcolor1 = Random(0, 126);
		    new randcolor2 = Random(0, 126);
		    SetPlayerPos(playerid, CarDealershipInfo[d][cdVehicleSpawn][0], CarDealershipInfo[d][cdVehicleSpawn][1], CarDealershipInfo[d][cdVehicleSpawn][2]+2);
		    TogglePlayerControllable(playerid, 1);
		    new cost;
		    cost = CarDealershipInfo[d][cdVehicleCost][v];
	        if(GetPlayerMoney(playerid) < CarDealershipInfo[d][cdVehicleCost][v])
	        {
				SendClientMessageEx(playerid, COLOR_GRAD1, "ERROR: You don't have enough money to buy this.");
				RemovePlayerFromVehicle(playerid);
				return 1;
			}
            GivePlayerMoneyEx(playerid, -CarDealershipInfo[d][cdVehicleCost][v]);
		    CarDealershipInfo[d][cdTill] += ((CarDealershipInfo[d][cdVehicleCost][v]*5)/100)+CarDealershipInfo[d][cdVehicleCost][v];
      		new cQuery[1024];
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[playerid][pID], CarDealershipInfo[d][cdVehicleModel][v], randcolor1, randcolor2, cost, CarDealershipInfo[d][cdVehicleSpawn][0], CarDealershipInfo[d][cdVehicleSpawn][1], CarDealershipInfo[d][cdVehicleSpawn][2], CarDealershipInfo[d][cdVehicleSpawn][3]);
			mysql_tquery(g_SQL, cQuery, "OnVehBuyPV", "ddddddffff", playerid, pData[playerid][pID], CarDealershipInfo[d][cdVehicleModel][v], randcolor1, randcolor2, cost, CarDealershipInfo[d][cdVehicleSpawn][0], CarDealershipInfo[d][cdVehicleSpawn][1], CarDealershipInfo[d][cdVehicleSpawn][2], CarDealershipInfo[d][cdVehicleSpawn][3]);
            //Plate
			DestroyVehicle(CarDealershipInfo[d][cdVehicleId][v]);
			DestroyDynamic3DTextLabel(CarDealershipInfo[d][cdVehicleLabel][v]);
			CarDealershipInfo[d][cdVehicleId][v] = INVALID_VEHICLE_ID;
			CarDealershipInfo[d][cdVehicleModel][v] = 0;
    		CarDealershipInfo[d][cdVehicleCost][v] = 0;
			format(String, sizeof(String), "[slot:%d]\n"GREEN_E"No vehicle to preview\n"WHITE_E"Use '"YELLOW_E"/dm > Vehicles"WHITE_E"' to display vehicle here",v);
			CarDealershipInfo[d][cdVehicleLabel][v] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,CarDealershipInfo[d][cdVehicleSpawnX][v], CarDealershipInfo[d][cdVehicleSpawnY][v], CarDealershipInfo[d][cdVehicleSpawnZ][v],8.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID);
            SavecDealership(d);
		}
		else return RemovePlayerFromVehicle(playerid);
	}
	else if(dialogid == DIALOG_CDSELL)
	{
		if(response)
		{
			if(GetPVarInt(playerid, "editingcd") == -1) return 1;
            GivePlayerMoneyEx(playerid, CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdPrice]);
			SellCarDealership(GetPVarInt(playerid, "editingcd"));
			format(String, sizeof(String), "Car Dealership successfully sold for %s!", FormatMoney(CarDealershipInfo[GetPVarInt(playerid, "editingcd")][cdPrice]));
			SendClientMessageEx(playerid, COLOR_WHITE, String);
		}
		else
		{
            SetPVarInt(playerid, "editingcd", -1);
			return 1;
		}
	}
    return 1;
}

Dialog:DialogCDSetting(playerid, response, listitem, inputtext[]) {
	if(response)
	{
		switch(listitem) {
            case 0: ShowPlayerDialog(playerid, DIALOG_CDNAME, DIALOG_STYLE_INPUT, "Car Dealership:", " Choose the new name:", "Edit", "Back");
            case 1: Dialog_Show(playerid, DialogCDCategory, DIALOG_STYLE_LIST, "Category Dealership", "Category 1\t$500.0\nCategory 2\t$500.0\nCategory 3\t$500.0\nCategory 4\t$500.0\nCategory 5\t$500.0\nCategory 6\t$500.0\nCategory 7\t$500.0\nCategory 8\t$500.0", "Select", "Close");
        }
	}
    return 1;
}

Dialog:DialogCDCategory(playerid, response, listitem, inputtext[]) {
    new d = GetPVarInt(playerid, "editingcd");
	if(response)
	{
		switch(listitem) {
            case 0: {
				CarDealershipInfo[d][cdType] = 1;
				CarDealershipInfo[d][cdTill] -= 50000;
				SendCustomMessage(playerid, "BISNIS", ""YELLOW_E"Anda telah merubah category bisnis dealership anda, dan dikenakan biaya "GREEN_E"$500.00");
			}
			case 1: {
				CarDealershipInfo[d][cdType] = 2;
				CarDealershipInfo[d][cdTill] -= 50000;
				SendCustomMessage(playerid, "BISNIS", ""YELLOW_E"Anda telah merubah category bisnis dealership anda, dan dikenakan biaya "GREEN_E"$500.00");
			}
			case 2: {
				CarDealershipInfo[d][cdType] = 3;
				CarDealershipInfo[d][cdTill] -= 50000;
				SendCustomMessage(playerid, "BISNIS", ""YELLOW_E"Anda telah merubah category bisnis dealership anda, dan dikenakan biaya "GREEN_E"$500.00");
			}
			case 3: {
				CarDealershipInfo[d][cdType] = 4;
				CarDealershipInfo[d][cdTill] -= 50000;
				SendCustomMessage(playerid, "BISNIS", ""YELLOW_E"Anda telah merubah category bisnis dealership anda, dan dikenakan biaya "GREEN_E"$500.00");
			}
			case 4: {
				CarDealershipInfo[d][cdType] = 5;
				CarDealershipInfo[d][cdTill] -= 50000;
				SendCustomMessage(playerid, "BISNIS", ""YELLOW_E"Anda telah merubah category bisnis dealership anda, dan dikenakan biaya "GREEN_E"$500.00");
			}
			case 5: {
				CarDealershipInfo[d][cdType] = 6;
				CarDealershipInfo[d][cdTill] -= 50000;
				SendCustomMessage(playerid, "BISNIS", ""YELLOW_E"Anda telah merubah category bisnis dealership anda, dan dikenakan biaya "GREEN_E"$500.00");
			}
			case 6: {
				CarDealershipInfo[d][cdType] = 7;
				CarDealershipInfo[d][cdTill] -= 50000;
				SendCustomMessage(playerid, "BISNIS", ""YELLOW_E"Anda telah merubah category bisnis dealership anda, dan dikenakan biaya "GREEN_E"$500.00");
			}
			case 7: {
				CarDealershipInfo[d][cdType] = 8;
				CarDealershipInfo[d][cdTill] -= 50000;
				SendCustomMessage(playerid, "BISNIS", ""YELLOW_E"Anda telah merubah category bisnis dealership anda, dan dikenakan biaya "GREEN_E"$500.00");
		}}

	}
    return 1;
}
