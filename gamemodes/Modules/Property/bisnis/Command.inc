//Bisnis System
CMD:createbisnis(playerid, params[])
{
	if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");
	
	new query[512];
	new bid = Iter_Free(Bisnis), address[128];
	if(bid == -1) return Error(playerid, "You cant create more bisnis!");
	new type;
	if(sscanf(params, "d", type)) return Usage(playerid, "/createbisnis [type, 1.Fastfood 2.Market 3.Clothes 4.Sportshop 5.Electronic 6.GYM 7.Ammunation]");
	format(bData[bid][bOwner], 128, "-");
	GetPlayerPos(playerid, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]);
	GetPlayerFacingAngle(playerid, bData[bid][bExtposA]);
	bData[bid][bExtVw] = GetPlayerVirtualWorld(playerid);
	bData[bid][bExtInt] = GetPlayerInterior(playerid);
	bData[bid][bPrice] = 5500000;
	bData[bid][bType] = type;
	address = GetLocation(bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]);
	format(bData[bid][bName], 128, address);
	bData[bid][bLocked] = 0;
	bData[bid][bInt] = 0;
	bData[bid][bIntposX] = 0;
	bData[bid][bIntposY] = 0;
	bData[bid][bIntposZ] = 0;
	bData[bid][bIntposA] = 0;
	bData[bid][bLastVisited] = 0;
	bData[bid][bRestock] = 1;
	bData[bid][bMoney] = 0;
	bData[bid][bProd] = 1000;

	if(type == 1) // Fast Food
	{
		// $5.00 - Fried Chicken (Menu +12, HP+10)
		bData[bid][bP][0] = 500;
		// $8.00 - Pizza Stack (Menu +20, HP+10)
		bData[bid][bP][1] = 800;
		// $12.00 - Patty Burger (Menu +30, HP+10)
		bData[bid][bP][2] = 1200;
		// $5.00 - Sprunk (Energy +20, HP+10)
		bData[bid][bP][3] = 500;
	}
	else if(type == 2) // 24/7 Market
	{
		// $3.00 - Snack (1x inventory item)
		bData[bid][bP][0] = 300;
		// $3.00 - Sprunk (1x inventory item)
		bData[bid][bP][1] = 300;
		// $15.00 - Bandage (1x heal item)
		bData[bid][bP][2] = 1500;
		// $5.00 - Cigarettes (pack)
		bData[bid][bP][3] = 500;
		// $12.00 - Toll Card (50 uses)
		bData[bid][bP][4] = 1200;
	}
	else if(type == 3) // Clothes Store
	{
		// $25.00 - Clothes
		bData[bid][bP][0] = 2500;
		// $10.00 - Hats
		bData[bid][bP][1] = 1000;
		// $10.00 - Glasses
		bData[bid][bP][2] = 1000;
		// $10.00 - Helmet
		bData[bid][bP][3] = 1000;
		// $15.00 - Accessory
		bData[bid][bP][4] = 1500;
		// $15.00 - Mask
		bData[bid][bP][5] = 1500;
	}
	else if(type == 4) // Sports Store
	{
		// $5.00 - Baseball Bat
		bData[bid][bP][0] = 500;
		// $5.00 - Shovel
		bData[bid][bP][1] = 500;
		// $5.00 - Cane
		bData[bid][bP][2] = 500;
		// $35.00 - Fishing Tools
		bData[bid][bP][3] = 3500;
		// $35.00 - Mask
		bData[bid][bP][4] = 3500;
	}
	else if(type == 5) // Electronic Store
	{
		// $250.00 - Handphone
		bData[bid][bP][0] = 25000;
		// $50.00 - GPS
		bData[bid][bP][1] = 5000;
		// $10.00 - Phone Credit (1000)
		bData[bid][bP][2] = 1000;
		// $25.00 - Walkie Talkie
		bData[bid][bP][3] = 2500;
		// $50.00 - Phone Book
		bData[bid][bP][4] = 5000;
	}
	else if(type == 6) // GYM
	{
		// $35.00 - GYM Membership
		bData[bid][bP][0] = 3500;
		// $5.00 - Energy Drink
		bData[bid][bP][1] = 500;
		// $3.00 - Water
		bData[bid][bP][2] = 300;
		// $3.00 - Snack
		bData[bid][bP][3] = 300;
	}
	Bisnis_ProductNameRefresh(bid);
	Bisnis_Type(bid);
    Bisnis_Refresh(bid);
	Iter_Add(Bisnis, bid);
	new String[212];
	format(String, sizeof(String), "AdmWarn: "YELLOW_E"%s "WHITE_E"Have created a Business ID "YELLOW_E"%d.", pData[playerid][pAdminname], bid);
	SendClientAdm(COLOR_ARWIN, String, 4); 
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO bisnis SET ID='%d', owner='%s', price='%d', type='%d', extposx='%f', extposy='%f', extposz='%f', extposa='%f', name='%s'", bid, bData[bid][bOwner], bData[bid][bPrice], bData[bid][bType], bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ], bData[bid][bExtposA], bData[bid][bName]);
	mysql_tquery(g_SQL, query, "OnBisnisCreated", "i", bid);
	return 1;
}

CMD:gotobisnis(playerid, params[])
{
	new bid;
	if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");
		
	if(sscanf(params, "d", bid))
		return Usage(playerid, "/gotobisnis [id]");
	if(!Iter_Contains(Bisnis, bid)) return Error(playerid, "The Bisnis you specified ID of doesn't exist.");
	SetPlayerPosition(playerid, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ], bData[bid][bExtposA]);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
	SendClientMessageEx(playerid, COLOR_WHITE, "You has teleport to bisnis id %d", bid);
	pData[playerid][pInDoor] = -1;
	pData[playerid][pInHouse] = -1;
	pData[playerid][pInBiz] = -1;
	return 1;
}

CMD:editbisnis(playerid, params[])
{
    static
        bid,
        type[24],
        string[128];

	if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");
	
    if(sscanf(params, "ds[24]S()[128]", bid, type, string))
    {
        Usage(playerid, "/editbisnis [id] [name]");
        SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, interior, locked, owner, point, price, type, product, restock, reset, garage, drivethru");
        return 1;
    }
    if((bid < 0 || bid >= MAX_BISNIS))
        return Error(playerid, "You have specified an invalid ID.");
	if(!Iter_Contains(Bisnis, bid)) return Error(playerid, "The bisnis you specified ID of doesn't exist.");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]);
		GetPlayerFacingAngle(playerid, bData[bid][bExtposA]);
        Bisnis_Save(bid);
		Bisnis_Refresh(bid);

        SendAdminMessage(COLOR_RED, "%s has adjusted the location of bisnis ID: %d.", pData[playerid][pAdminname], bid);
    }
	else if(!strcmp(type, "drivethru", true))
    {
		if(bData[bid][bType] == 1) {
			GetPlayerPos(playerid, bData[bid][bDriveThru][0], bData[bid][bDriveThru][1], bData[bid][bDriveThru][2]);
			Bisnis_Save(bid);
			Bisnis_Refresh(bid);
			SendAdminMessage(COLOR_RED, "%s has adjusted the drivethru spawn of bisnis ID: %d.", pData[playerid][pAdminname], bid);
		}
        else return Error(playerid, "Anda tidak bisa menset drivethru pada bisnis ini");
    }
	else if(!strcmp(type, "garage", true))
    {
        new slot;

        if(sscanf(string, "d", slot))
            return Usage(playerid, "/editbisnis [id] [garage] [slot 0-1 (0 > Disable Garage, 1 > Activate the garage)]");
		switch(slot)
		{
			case 0:
			{
				BussinesGarage[bid][ExtPos][0] = BussinesGarage[bid][ExtPos][1] = BussinesGarage[bid][ExtPos][2] = 0;
				BussinesGarage[bid][BizGarage] = 0;
				Bisnis_Save(bid);
				Bisnis_Refresh(bid);
				SendCustomMessage(playerid, "GARAGE", "You have deactivated this business garage");
			}
			case 1:
			{
				GetPlayerPos(playerid, BussinesGarage[bid][ExtPos][0], BussinesGarage[bid][ExtPos][1], BussinesGarage[bid][ExtPos][2]);
				BussinesGarage[bid][BizGarage] = 1;
				Bisnis_Save(bid);
				Bisnis_Refresh(bid);
				SendCustomMessage(playerid, "GARAGE", "You have activated this business garage");
			}
		}
    }
    else if(!strcmp(type, "interior", true))
    {
        GetPlayerPos(playerid, bData[bid][bIntposX], bData[bid][bIntposY], bData[bid][bIntposZ]);
		GetPlayerFacingAngle(playerid, bData[bid][bIntposA]);
		bData[bid][bInt] = GetPlayerInterior(playerid);

        Bisnis_Save(bid);
		Bisnis_Refresh(bid);

        SendAdminMessage(COLOR_RED, "%s has adjusted the interior spawn of bisnis ID: %d.", pData[playerid][pAdminname], bid);
    }
    else if(!strcmp(type, "locked", true))
    {
        new locked;

        if(sscanf(string, "d", locked))
            return Usage(playerid, "/editbisnis [id] [locked] [0/1]");

        if(locked < 0 || locked > 1)
            return Error(playerid, "You must specify at least 0 or 1.");

        bData[bid][bLocked] = locked;
        Bisnis_Save(bid);
		Bisnis_Refresh(bid);

        if(locked) {
            SendAdminMessage(COLOR_RED, "%s has locked bisnis ID: %d.", pData[playerid][pAdminname], bid);
        }
        else {
            SendAdminMessage(COLOR_RED, "%s has unlocked bisnis ID: %d.", pData[playerid][pAdminname], bid);
        }
    }
    else if(!strcmp(type, "price", true))
    {
        new price;

        if(sscanf(string, "d", price))
            return Usage(playerid, "/editbisnis [id] [Price] [Amount]");

        bData[bid][bPrice] = price;

        Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the price of bisnis ID: %d to %d.", pData[playerid][pAdminname], bid, price);
    }
	else if(!strcmp(type, "type", true))
    {
        new btype;

        if(sscanf(string, "d", btype))
            return Usage(playerid, "/editbisnis [id] [Type] [1.Fastfood 2.Market 3.Clothes 4.Equipment]");

        bData[bid][bType] = btype;
		Bisnis_Type(bid);
        Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the type of bisnis ID: %d to %d.", pData[playerid][pAdminname], bid, btype);
    }
	else if(!strcmp(type, "product", true))
    {
        new prod;

        if(sscanf(string, "d", prod))
            return Usage(playerid, "/editbisnis [id] [product] [Ammount]");

        bData[bid][bProd] = prod;
        Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the product of bisnis ID: %d to %d.", pData[playerid][pAdminname], bid, prod);
    }
	else if(!strcmp(type, "money", true))
    {
        new money;

        if(sscanf(string, "d", money))
            return Usage(playerid, "/editbisnis [id] [money] [Ammount]");

        bData[bid][bMoney] = money;
        Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the money of bisnis ID: %d to %s.", pData[playerid][pAdminname], bid, FormatMoney(money));
    }
	else if(!strcmp(type, "restock", true))
    {
        new prod;

        if(sscanf(string, "d", prod))
            return Usage(playerid, "/editbisnis [id] [restock] [0-1]");
		
		if(prod == 0)
		{
			bData[bid][bRestock] = 0;
			Bisnis_Save(bid);
			Bisnis_Refresh(bid);
			SendAdminMessage(COLOR_RED, "%s has adjusted the restock of bisnis ID: %d to disable.", pData[playerid][pAdminname], bid);
		}
		else if(prod == 1)
		{
			bData[bid][bRestock] = 1;
			Bisnis_Save(bid);
			Bisnis_Refresh(bid);
			SendAdminMessage(COLOR_RED, "%s has adjusted the restock of bisnis ID: %d to enable.", pData[playerid][pAdminname], bid);
		}
		else return Error(playerid, "Hanya id 0-1");
    }
    else if(!strcmp(type, "owner", true))
    {
        new owners[MAX_PLAYER_NAME];

        if(sscanf(string, "s[32]", owners))
            return Usage(playerid, "/editbisnis [id] [owner] [player name] (use '-' to no owner)");

        format(bData[bid][bOwner], MAX_PLAYER_NAME, owners);
  
        Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the owner of bisnis ID: %d to %s", pData[playerid][pAdminname], bid, owners);
    }
    else if(!strcmp(type, "reset", true))
    {
        Bisnis_Reset(bid);
		Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has reset bisnis ID: %d.", pData[playerid][pAdminname], bid);
    }
	else if(!strcmp(type, "point", true))
    {
		new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
		bData[bid][bPointX] = x;
		bData[bid][bPointY] = y;
		bData[bid][bPointZ] = z;
		Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has edit bisnis point ID: %d.", pData[playerid][pAdminname], bid);
    }
	else if(!strcmp(type, "delete", true))
    {
		Bisnis_Reset(bid);
		// if(IsValidDynamicMapIcon(bData[bid][bIcon])) DestroyDynamicMapIcon(bData[bid][bIcon]);
		if(IsValidDynamic3DTextLabel(bData[bid][bLabel])) DestroyDynamic3DTextLabel(bData[bid][bLabel]);
        if(IsValidDynamicPickup(bData[bid][bPickup][0])) DestroyDynamicPickup(bData[bid][bPickup][0]);
		if(IsValidDynamicPickup(bData[bid][bPickup][1])) DestroyDynamicPickup(bData[bid][bPickup][1]);
		if(IsValidDynamic3DTextLabel(bData[bid][bLabelPoint])) DestroyDynamic3DTextLabel(bData[bid][bLabelPoint]);
        if(IsValidDynamicPickup(bData[bid][bPickPoint])) DestroyDynamicPickup(bData[bid][bPickPoint]);
		if(IsValidDynamicCP(bData[bid][bCP][0])) DestroyDynamicCP(bData[bid][bCP][0]);
		if(IsValidDynamicCP(bData[bid][bCP][1])) DestroyDynamicCP(bData[bid][bCP][1]);
		if(IsValidDynamic3DTextLabel(BussinesGarage[bid][GarageText])) DestroyDynamic3DTextLabel(BussinesGarage[bid][GarageText]);
        if(IsValidDynamicPickup(BussinesGarage[bid][GaragePick])) DestroyDynamicPickup(BussinesGarage[bid][GaragePick]);

		Iter_Remove(Bisnis, bid);
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM bisnis WHERE ID=%d", bid);
		mysql_tquery(g_SQL, query);
        SendAdminMessage(COLOR_RED, "%s has delete bisnis ID: %d.", pData[playerid][pAdminname], bid);
	}
    return 1;
}

CMD:lockbisnis(playerid, params[])
{
	foreach(new bid : Bisnis)
	{
		if(IsPlayerInDynamicCP(playerid, bData[bid][bCP][0]))
		{
			if(!Player_OwnsBisnis(playerid, bid) && !Business_IsEmployee(playerid, bid)) return Error(playerid, "You don't own this bisnis.");
			if(!bData[bid][bLocked])
			{
				bData[bid][bLocked] = 1;
				Bisnis_Save(bid);

				InfoTD_MSG(playerid, 4000, "You have ~r~locked~w~ your bisnis!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
			else
			{
				bData[bid][bLocked] = 0;
				Bisnis_Save(bid);

				InfoTD_MSG(playerid, 4000,"You have ~g~unlocked~w~ your bisnis!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
		}
	}
	return 1;
}

CMD:mybis(playerid)
{
	if(GetOwnedBisnis(playerid) == -1) return Error(playerid, "You don't have a bisnis.");
	//if(!Player_OwnsBusiness(playerid, id)) return Error(playerid, "You don't own this business.");
	new hid, _tmpstring[128], count = GetOwnedBisnis(playerid), CMDSString[512];
	CMDSString = "";
	new lock[128];
	Loop(itt, (count + 1), 1)
	{
	    hid = ReturnPlayerBisnisID(playerid, itt);
		if(hData[hid][hLocked] == 1) lock = "{FF0000}Locked";
		else lock = "{00FF00}Unlocked";
		if(itt == count) format(_tmpstring, sizeof(_tmpstring), ""LB_E"%d.\t{FFFF2A}%s   (%s)\n", itt, ReplaceString(bData[hid][bName]), lock);
		else format(_tmpstring, sizeof(_tmpstring), ""LB_E"%d.\t{FFFF2A}%s  (%s)\n", itt, ReplaceString(bData[hid][bName]), lock);
		strcat(CMDSString, _tmpstring);
	}
	Dialog_Show(playerid, MyBisnis, DIALOG_STYLE_LIST, "{FF0000}{0000FF}Bisnis", CMDSString, "Select", "Cancel");
	return 1;
}

CMD:bm(playerid, params[])
{
	if(pData[playerid][pInBiz] == -1) return 0;
	if(!Player_OwnsBisnis(playerid, pData[playerid][pInBiz]) && !Business_IsEmployee(playerid, pData[playerid][pInBiz])) return Error(playerid, "You don't own this bisnis.");
    new string[212];
	if(bData[pData[playerid][pInBiz]][bType] == 1) format(string, sizeof(string), "Bisnis Info\nChange Name\nProduct Menu\nChange Name Product Menu\nRequest Restock\nRadio URL(Music)\nEmployees\nRestock Product Vehicle Bisnis");
	else format(string, sizeof(string), "Bisnis Info\nChange Name\nProduct Menu\nChange Name Product Menu\nRequest Restock\nRadio URL(Music)\nEmployees");
	Dialog_Show(playerid, MenuBisnis, DIALOG_STYLE_LIST, "Bisnis Menu",string,"Next","Close");
    return 1;
}

CMD:givebisnis(playerid, params[])
{
	new bid, otherid;
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1424.31, 1546.21, 3010.83)) return Error(playerid, "Anda harus berada di Citty Hall!");
	if(pData[playerid][pLevel] < 3)
		return Error(playerid, "Anda harus level 3 untuk menggunakan fitur ini");
		
	if(sscanf(params, "ud", otherid, bid)) return Usage(playerid, "/givebisnis [playerid/name] [id] | /mybisnis - for show info");
	if(bid == -1) return Error(playerid, "Invalid id");
	
	if(!IsPlayerConnected(otherid) || !NearPlayer(playerid, otherid, 4.0))
        return Error(playerid, "The specified player is disconnected or not near you.");
	
	if(!IsValidTarget(playerid, otherid))
	    return Error(playerid, "Kamu tidak bisa memberikan bisnis kepada diri sendiri.");

	if(!Player_OwnsBisnis(playerid, bid)) return Error(playerid, "You don't own this bisnis.");
	if(bData[bid][bSegel] == 1) return Error(playerid, "Biz anda masih tersegel.");
	if(PropertiCommercial_CountMax(otherid) >= PropertiesCommercial_Max(otherid)) return Error(playerid, "property slots are full");
	GetPlayerName(otherid, bData[bid][bOwner], MAX_PLAYER_NAME);
	bData[bid][bLastVisited] = gettime();
	
	Bisnis_Refresh(bid);
	Bisnis_Save(bid);
	SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: Anda memberikan bisnis id: %d kepada %s", bid, ReturnName(otherid));
	SendClientMessageEx(otherid, COLOR_ARWIN, "BISNIS: %s memberikan bisnis id: %d kepada anda", bid, ReturnName(playerid));
	return 1;
}

CMD:bwithdraw(playerid, params[])
{
	if(pData[playerid][pInBiz] == -1) return 0;
	if(!Player_OwnsBisnis(playerid, pData[playerid][pInBiz])) return Error(playerid, "You don't own this bisnis.");

	new bid = pData[playerid][pInBiz];
	if(bData[bid][bSegel] == 1) return Error(playerid, "Biz anda masih tersegel.");
	new String[512], amount[32], dollars, cents, duit[32];

	if(sscanf(params, "s[32]", amount))
	{
		SendClientMessageEx(playerid, COLOR_GRAD2, "KEGUNAAN: /bwithdraw [Jumlah]");
		format(String, sizeof(String), "Anda memiliki uang sebesar %s di dalam Akun bisnis Anda.", FormatMoney(bData[bid][bMoney]));
		SendClientMessageEx(playerid, COLOR_GRAD3, String);
		return 1;
	}
	if(strfind(amount, ".", true) != 1)
	{
	   	sscanf(amount, "p<.>dd", dollars, cents);
	    format(duit, sizeof(duit), "%d%02d", dollars, cents);
		if(strval(duit) > bData[bid][bMoney])
		{
			SendClientMessageEx(playerid, COLOR_GRAD2, "Anda tidak memiliki uang sebesar itu di dalam Akun bisnis anda!");
			return 1;
		}
		if(strval(duit) < 0) return SendClientMessageEx(playerid, COLOR_GREY, "Tidak bisa dibawah $0.00");
		GivePlayerMoneyEx(playerid,strval(duit));
		bData[bid][bMoney]=bData[bid][bMoney]-strval(duit);
		format(String, sizeof(String), "BISNIS: {ffffff}You've withdrawn {ffff00}%s{ffffff} from your bisnis account", FormatMoney(strval(duit)));
		SendClientMessageEx(playerid, COLOR_ARWIN, String);
		format(String, sizeof(String), "BISNIS: {ffff00}%s",FormatMoney(bData[bid][bMoney]));
		SendClientMessageEx(playerid, COLOR_ARWIN, String);
	}
	else
	{
	   	sscanf(amount, "d", dollars);
	    format(duit, sizeof(duit), "%d00", dollars);
		if(strval(duit) > bData[bid][bMoney])
		{
			SendClientMessageEx(playerid, COLOR_GRAD2, "Anda tidak memiliki uang sebesar itu di dalam Akun bisnis anda!");
			return 1;
		}
		if(strval(duit) < 0) return SendClientMessageEx(playerid, COLOR_GREY, "Tidak bisa dibawah $0.00");
		GivePlayerMoneyEx(playerid,strval(duit));
		bData[bid][bMoney]=bData[bid][bMoney]-strval(duit);
		format(String, sizeof(String), "BISNIS: {ffffff}You've withdrawn {ffff00}%s{ffffff} from your bisnis account", FormatMoney(strval(duit)));
		SendClientMessageEx(playerid, COLOR_ARWIN, String);
		format(String, sizeof(String), "BISNIS: {ffff00}%s",FormatMoney(bData[bid][bMoney]));
		SendClientMessageEx(playerid, COLOR_ARWIN, String);
	}
	return 1;
}

CMD:bdeposit(playerid, params[])
{
	if(pData[playerid][pInBiz] == -1) return 0;
	if(!Player_OwnsBisnis(playerid, pData[playerid][pInBiz])) return Error(playerid, "You don't own this bisnis.");

	new bid = pData[playerid][pInBiz];
	if(bData[bid][bSegel] == 1) return Error(playerid, "Biz anda masih tersegel.");
	new String[512], amount[32], dollars, duit[32];

	if(sscanf(params, "s[32]", amount))
	{
		SendClientMessageEx(playerid, COLOR_GRAD2, "KEGUNAAN: /bdeposit [Jumlah]");
		format(String, sizeof(String), "Anda memiliki uang sebesar %s di dalam Akun bisnis Anda.", FormatMoney(bData[bid][bMoney]));
		SendClientMessageEx(playerid, COLOR_GRAD3, String);
		return 1;
	}
	sscanf(amount, "d", dollars);
	format(duit, sizeof(duit), "%d00", dollars);
	if(strval(duit) > GetPlayerMoney(playerid))
	{
		SendClientMessageEx(playerid, COLOR_GRAD2, "Anda tidak memiliki uang sebesar itu di dalam Akun bisnis anda!");
		return 1;
	}
	if(strval(duit) < 0) return SendClientMessageEx(playerid, COLOR_GREY, "Tidak bisa dibawah $0.00");
	GivePlayerMoneyEx(playerid, -strval(duit));
	bData[bid][bMoney]+=strval(duit);
	format(String, sizeof(String), "BISNIS: {ffffff}You have saved {ffff00}%s{ffffff} to your business account", FormatMoney(strval(duit)));
	SendClientMessageEx(playerid, COLOR_ARWIN, String);
	format(String, sizeof(String), "BISNIS: {ffff00}%s",FormatMoney(bData[bid][bMoney]));
	SendClientMessageEx(playerid, COLOR_ARWIN, String);
	return 1;
}
