//NOTE: DialogBisniRestockVehicle Ada ni > vehicleother > dialog
Dialog:Business_RemoveEmployee(playerid, response, listitem, inputtext[]) {
    if (response) {
        BusinessEmployee_Remove(strval(inputtext));
		SendCustomMessage(playerid, "BUSINESS", "You've remove list employee number #%d from your business.", strval(inputtext));
    }
    return 1;
}

Dialog:ShowBusiness_Employee(playerid, response, listitem, inputtext[]) {
    static
        bizid = -1;

    if((bizid = pData[playerid][pInBiz]) != -1 && Player_OwnsBisnis(playerid, bizid))
    {
		if (response) {
			switch(listitem)
			{
				case 0: {
					Dialog_Show(playerid, Business_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Masukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");
				}
				case 1: {
					Business_ShowEmployee(playerid, bizid, 1);
				}
				case 2: {
					BusinessEmployee_RemoveAll(bizid);
					SendCustomMessage(playerid, "BUSINESS", "You've remove all employe on this business.");
				}
				case 3: Business_ShowEmployee(playerid, bizid, 0);
			}
		} else callcmd::bm(playerid, "\1");
	}
    return 1;
}

Dialog:Business_AddEmployee(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		new id,
			bizid = pData[playerid][pInBiz];

		if (BusinessEmployee_GetCount(bizid) >= 3) return Error(playerid, "This business is limited 3 employee.");
		if (sscanf(inputtext, "u", id)) return Dialog_Show(playerid, Business_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Masukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");
		if (!IsPlayerConnected(id)) return Dialog_Show(playerid, Business_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Player yang kamu masukkan tidak terkoneksi dalam game\nMasukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");
        if (id == playerid) return Dialog_Show(playerid, Business_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Tidak dapat memasukkan karakter kamu sendiri\nMasukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");
		if (Business_IsEmployee(id, bizid)) return Dialog_Show(playerid, Business_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Player tersebut sudah masuk dalam list employee\nMasukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");

		BusinessEmployee_Add(id, bizid);
		SendCustomMessage(playerid, "BUSINESS", "Kamu memasukkan "YELLOW_E"%s "WHITE_E"ke dalam list pekerja bisnismu.", ReturnName(id));
		SendCustomMessage(id, "BUSINESS", YELLOW_E"%s "WHITE_E"mempekerjakan kamu di bisnis miliknya (Bisnis: %s).", ReturnName(playerid), ReplaceString(bData[bizid][bName]));
	}
    return 1;
}

Dialog:RandNumber(playerid, response, listitem, inputtext[])
{
    new number[150], bizid = pData[playerid][pInBiz], price = bData[bizid][bP][0];
    if(response)
    {
		if(GetPlayerMoney(playerid) < price) return Error(playerid, "Not enough money!");
		if(!BusinnesProduct[bizid][BussinesProduct][0]) return Error(playerid, "This business is out of stock product.");
        pData[playerid][pPhone] = strval(inputtext);

		SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName0]), FormatMoney(price));
		SendCustomMessage(playerid, "NOTE", ""YELLOW_E"Nomor handphone anda %d", pData[playerid][pPhone]);
		bData[bizid][bProd]--;
		BusinnesProduct[bizid][BussinesProduct][0]--;
		bData[bizid][bMoney] += Server_Percent(price);
		Server_AddPercent(price);
		Bisnis_Save(bizid);
		GivePlayerMoneyEx(playerid, -price);
		// Save phone number immediately to database
		new cQuery[256];
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `players` SET `phone`='%d' WHERE `reg_id`='%d'", pData[playerid][pPhone], pData[playerid][pID]);
		mysql_tquery(g_SQL, cQuery);
    }
    else
    {
        for(new i; i != 10; i++)
        {
            format(number, sizeof(number), "%s{%s}%d\n", number, ((i+1) % 2 == 0) ? ("C0C0C0") : ("FFFFFF") , (random(900000)+100000));
        }
        Dialog_Show(playerid, RandNumber, DIALOG_STYLE_LIST, "Phone Number", number, "Select", "Refresh");
    }
    return 1;
}

Dialog:SellBisnis(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
	new str[248];
	SetPVarInt(playerid, "SellingBisnis", ReturnPlayerBisnisID(playerid, (listitem + 1)));
	new bid = GetPVarInt(playerid, "SellingBisnis");
	if(bData[bid][bSegel] == 1) return Error(playerid, "Biz anda masih tersegel.");
	format(str, sizeof(str), "Are you sure you will sell bisnis id: %d", GetPVarInt(playerid, "SellingBisnis"));
			
	Dialog_Show(playerid, SellBisnis1, DIALOG_STYLE_MSGBOX, "Sell Bisnis", str, "Sell", "Cancel");
    return 1;
}

Dialog:SellBisnis1(playerid, response, listitem, inputtext[])
{
    if(response)
	{
		new bid = GetPVarInt(playerid, "SellingBisnis");
		GivePlayerMoneyEx(playerid, 2);
		SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: "WHITE_E"Anda berhasil menjual bisnis id (%d) dengan setengah harga("LG_E"$2"WHITE_E") pada saat anda membelinya.", bid);
		Bisnis_Reset(bid);
		Bisnis_Save(bid);
		Bisnis_Refresh(bid);
	}
	DeletePVar(playerid, "SellingBisnis");
	return 1;
}

Dialog:MyBisnis(playerid, response, listitem, inputtext[])
{
    if(!response) return true;
	SetPVarInt(playerid, "ClickedBisnis", ReturnPlayerBisnisID(playerid, (listitem + 1)));
	Dialog_Show(playerid, BisnisInfo, DIALOG_STYLE_LIST, "{0000FF}Bisnis", "Show Information\nTrack Bisnis", "Select", "Cancel");
	return 1;
}

Dialog:RadioURlBisnis(playerid, response, listitem, inputtext[])
{
    if(response)
	{
		if(strlen(inputtext))
		{
			new bid = pData[playerid][pInBiz];
			format(bData[bid][bStream], 128, inputtext);
			SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: "WHITE_E"You have set the radio URL with the URL "YELLOW_E"%s", inputtext);
			new Float:BBCoord[3];
			GetPlayerPos(playerid, BBCoord[0], BBCoord[1], BBCoord[2]);
			PlayStream(playerid, inputtext, BBCoord[0], BBCoord[1], BBCoord[2], 30.0, 1);	
		}
	}
	return 1;
}

Dialog:BisnisBuyRestock(playerid, response, listitem, inputtext[])
{
    if (response)
	{
		new bid = pData[playerid][pInBiz];
		new idiot = floatround(strval(inputtext));
		new value = idiot * 50, String[212];
		if(bData[bid][bMoney] < value) return Error(playerid, "Uang Di Bisnis anda tidak cukup untuk merestock bisnis");
		bData[bid][bMoney] -= value;
		bData[bid][bProd] += idiot;
		format(String, sizeof(String), "BISNIS: "WHITE_E"Anda telah membeli product bisnis {00FFFF}%d "WHITE_E"unit dengan harga "YELLOW_E"%s", idiot, FormatMoney(value));
		SendClientMessage(playerid, COLOR_ARWIN, String);
	}
	return 1;
}

Dialog:BisnisName(playerid, response, listitem, inputtext[])
{
    if(response)
	{
		new bid = pData[playerid][pInBiz];

		if(!Player_OwnsBisnis(playerid, pData[playerid][pInBiz])) return Error(playerid, "You don't own this bisnis.");
		
		if (isnull(inputtext))
		{
			new mstr[512];
			format(mstr,sizeof(mstr),""RED_E"NOTE: "WHITE_E"Nama Bisnis tidak di perbolehkan kosong!\n\n"WHITE_E"Nama sebelumnya: %s\n\nMasukkan nama Bisnis yang kamu inginkan\nMaksimal 32 karakter untuk nama Bisnis", ReplaceString(bData[bid][bName]));
			Dialog_Show(playerid, BisnisName, DIALOG_STYLE_INPUT,"Bisnis Name", mstr,"Done","Back");
			return 1;
		}
		if(strlen(inputtext) > 32 || strlen(inputtext) < 5)
		{
			new mstr[512];
			format(mstr,sizeof(mstr),""RED_E"NOTE: "WHITE_E"Nama Bisnis harus 5 sampai 32 karakter.\n\n"WHITE_E"Nama sebelumnya: %s\n\nMasukkan nama Bisnis yang kamu inginkan\nMaksimal 32 karakter untuk nama Bisnis", ReplaceString(bData[bid][bName]));
			Dialog_Show(playerid, BisnisName, DIALOG_STYLE_INPUT,"Bisnis Name", mstr,"Done","Back");
			return 1;
		}
		format(bData[bid][bName], 32, ColouredText(inputtext));

		Bisnis_Refresh(bid);
		Bisnis_Save(bid);

		SendCustomMessage(playerid, "BISNIS", "Bisnis name set to: \"%s\".", ReplaceString(bData[bid][bName]));
	}
	else return callcmd::bm(playerid, "\0");
	return 1;
}

Dialog:MenuBisnis(playerid, response, listitem, inputtext[])
{
    new bid = pData[playerid][pInBiz];
	new lock[128];
	if(bData[bid][bLocked] == 1) lock = "Locked";
	else lock = "Unlocked";
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{	
				new mstr[248], lstr[512];
				format(mstr,sizeof(mstr),"Bisnis ID %d", bid);
				format(lstr,sizeof(lstr),"Bisnis Name:\t%s\nBisnis Locked:\t%s\nBisnis Product:\t%d\nBisnis Vault:\t%s", ReplaceString(bData[bid][bName]), lock, bData[bid][bProd], FormatMoney(bData[bid][bMoney]));
				Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST, mstr, lstr,"Back","Close");
			}
			case 1:
			{
				new mstr[248];
				format(mstr,sizeof(mstr),""BLUE_E"HINT:\n"WHITE_E"- Teks mendukung bbcode, gunakan (n):untuk membuat baris baru, \
				(r):warna merah, (w):putih, \n\
				\t(b):biru, (bl):hitam, (g):hijau, (bl):kuning\n\
				\tContoh: Ganti (r)saya (w)menjadi merah dan seterusnya putih\n\
				- Tidak memasukkan teks kepanjangan\n\n\
				Maksimal teks tidak lebih dari 40 huruf:", "Ubah", "Keluar");
				Dialog_Show(playerid, BisnisName, DIALOG_STYLE_INPUT,"Bisnis Name", mstr,"Done","Back");
			}
			case 2: Bisnis_ProductMenu(playerid, bid);
			case 3: Bisnis_ProductMenuName(playerid, bid);
			case 4: Bisnis_ProductStock(playerid, bid);
			case 5: Dialog_Show(playerid, RadioURlBisnis, DIALOG_STYLE_INPUT, "Radio URL", "Enter music url to play music", "Play", "Cancel");
			case 6: Dialog_Show(playerid, ShowBusiness_Employee, DIALOG_STYLE_LIST, "Employees Management", "Add Employee\nRemove Employee\nRemove All Employees\nEmployees Members", "Select", "Close");
			case 7: Dialog_Show(playerid, RestockVehicleBisnis, DIALOG_STYLE_INPUT, "Restock Product Vehicle:", "Masukan jumlah product yang ingin anda restock pada kendaraan", "Restock", "Back");
		}
	}
	return 1;
}

Dialog:BisnisInfo(playerid, response, listitem, inputtext[])
{
    if(!response) return true;
	new bid = GetPVarInt(playerid, "ClickedBisnis");
	switch(listitem)
	{
		case 0:
		{
			new line9[900];
			new lock[128], type[128];
			if(bData[bid][bLocked] == 1) lock = "{FF0000}Locked";
			else lock = "{00FF00}Unlocked";
			if(bData[bid][bType] == 1) type= "Fast Food";
			else if(bData[bid][bType] == 2) type= "Market";
			else if(bData[bid][bType] == 3) type= "Clothes";
			else if(bData[bid][bType] == 4) type= "Sportshop";
			else if(bData[bid][bType] == 5) type= "Electronic";
			else if(bData[bid][bType] == 6) type= "GYM";
			else if(bData[bid][bType] == 7) type= "Ammunation";
			else type = "Unknow";
			format(line9, sizeof(line9), "Bisnis ID: %d\nBisnis Owner: %s\nBisnis Name: %s\nBisnis Price: %s\nBisnis Type: %s\nBisnis Status: %s\nBisnis Product: %d",
			bid, bData[bid][bOwner], ReplaceString(bData[bid][bName]), FormatMoney(bData[bid][bPrice]), type, lock, bData[bid][bProd]);

			Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Bisnis Info", line9, "Close","");
		}
		case 1:
		{
			new S3MP4K[512];	
			pData[playerid][pTrackBisnis] = 1;
			SetPlayerRaceCheckpoint(playerid,1, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ], 0.0, 0.0, 0.0, 3.5);
			SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"Ikuti checkpoint untuk menemukan bisnis anda!");
			format(S3MP4K, sizeof(S3MP4K), "HINT: {FFFFFF}Your bisnis waypoint was set to "YELLOW_E"%s.", GetLocation(bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ]));
			SendClientMessageEx(playerid, COLOR_ARWIN, S3MP4K);	
		}
	}
    return 1;
}

Dialog:RestockProduct(playerid, response, listitem, inputtext[])
{
    if(!Player_OwnsBisnis(playerid, pData[playerid][pInBiz]) && !Business_IsEmployee(playerid, pData[playerid][pInBiz])) return Error(playerid, "You don't own this bisnis.");
	{
		if(response)
		{
			static
				item[40],
				str[128];

			strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
			strpack(pData[playerid][pEditingItem], item, 40 char);

			pData[playerid][pProductModify] = listitem;
			format(str,sizeof(str), "Masukan jumlah product yang ingin anda restock:");
			Dialog_Show(playerid, BussinesRestock, DIALOG_STYLE_INPUT, "Business: restock product", str, "Restock", "Back");
		}
		else return callcmd::bm(playerid, "\0");
	}
    return 1;
}

Dialog:BussinesRestock(playerid, response, listitem, inputtext[])
{
    static
	item[40];
	new bizid = pData[playerid][pInBiz];
	if(!Player_OwnsBisnis(playerid, pData[playerid][pInBiz]) && !Business_IsEmployee(playerid, pData[playerid][pInBiz])) return Error(playerid, "You don't own this bisnis.");
	{
		if(response)
		{
			strunpack(item, pData[playerid][pEditingItem]);

			if(isnull(inputtext))
			{
				new str[128];
				format(str,sizeof(str), "Masukan jumlah product yang ingin anda restock:");
			    Dialog_Show(playerid, BussinesRestock, DIALOG_STYLE_INPUT, "Business: restock product", str, "Restock", "Back");
				return 1;
			}
			if(strval(inputtext) < 1 || strval(inputtext) > 5000)
			{
				new str[128];
				format(str,sizeof(str), "Masukan jumlah product yang ingin anda restock:");
			    Dialog_Show(playerid, BussinesRestock, DIALOG_STYLE_INPUT, "Business: restock product", str, "Restock", "Back");
				return 1;
			}
            new idiot = strval(inputtext);
		    new value = idiot * 500;
            BusinnesProduct[bizid][BussinesProduct][pData[playerid][pProductModify]] += idiot;
            bData[bizid][bMoney] -= value;
			Bisnis_Save(bizid);
            Bisnis_ProductStock(playerid, bizid);
            SendCustomMessage(playerid, "BUSSINES", "Anda telah merestock product "YELLOW_E"%d units "WHITE_E"dengan harga "GREEN_E"%s", idiot, FormatMoney(value));
		}
		else Bisnis_ProductStock(playerid, bizid);
	}
    return 1;
}

Dialog:BisnisSetProd(playerid, response, listitem, inputtext[])
{
    if(Player_OwnsBisnis(playerid, pData[playerid][pInBiz]))
	{
		if(response)
		{
			static
				item[40],
				str[128];

			strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
			strpack(pData[playerid][pEditingItem], item, 40 char);

			pData[playerid][pProductModify] = listitem;
			format(str,sizeof(str), "Please enter the new product price for %s:\n"AQUA_E"NOTE: Use Dollar", item);
			Dialog_Show(playerid, BisnisSetPrice, DIALOG_STYLE_INPUT, "Business: Set Price", str, "Modify", "Back");
		}
		else
			return callcmd::bm(playerid, "\0");
	}
    return 1;
}

Dialog:BisnisSetPrice(playerid, response, listitem, inputtext[])
{
    static
	item[40];
	new bizid = pData[playerid][pInBiz];
	if(Player_OwnsBisnis(playerid, pData[playerid][pInBiz]))
	{
		if(response)
		{
			strunpack(item, pData[playerid][pEditingItem]);

			if(isnull(inputtext))
			{
				new str[128];
				format(str,sizeof(str), "Please enter the new product price for %s:", item);
				Dialog_Show(playerid, BisnisSetPrice, DIALOG_STYLE_INPUT, "Business: Set Price", str, "Modify", "Back");
				return 1;
			}
			if(strval(inputtext) < 1 || strval(inputtext) > 5000)
			{
				new str[128];
				format(str,sizeof(str), "Please enter the new product price for %s ($1 to $50.00):", item);
				Dialog_Show(playerid, BisnisSetPrice, DIALOG_STYLE_INPUT, "Business: Set Price", str, "Modify", "Back");
				return 1;
			}
			new duit[32];
			format(duit, sizeof(duit), "%d00", strval(inputtext));
			bData[bizid][bP][pData[playerid][pProductModify]] = strval(duit);
			Bisnis_Save(bizid);

			SendCustomMessage(playerid, "BISNIS", "You have adjusted the price of %s to: %s!", item, FormatMoney(strval(duit)));
			Bisnis_ProductMenu(playerid, bizid);
		}
		else
		{
			Bisnis_ProductMenu(playerid, bizid);
		}
	}
    return 1;
}

Dialog:BizSetProdName(playerid, response, listitem, inputtext[])
{
    new bid = pData[playerid][pInBiz];
	if(response)
	{
		if(!Player_OwnsBisnis(playerid, pData[playerid][pInBiz])) return 1;
		if(pData[playerid][pProductModify] == 0)
		{
			format(bData[bid][bPName0], 128, inputtext);
			Bisnis_Save(bid);

			SendCustomMessage(playerid, "BISNIS", "You have adjusted the name %s!", inputtext);
			Bisnis_ProductMenuName(playerid, bid);
		}
		else if(pData[playerid][pProductModify] == 1)
		{
			format(bData[bid][bPName1], 128, inputtext);
			Bisnis_Save(bid);

			SendCustomMessage(playerid, "BISNIS", "You have adjusted the name %s!", inputtext);
			Bisnis_ProductMenuName(playerid, bid);
		}
		else if(pData[playerid][pProductModify] == 2)
		{
			format(bData[bid][bPName2], 128, inputtext);
			Bisnis_Save(bid);

			SendCustomMessage(playerid, "BISNIS", "You have adjusted the name %s!", inputtext);
			Bisnis_ProductMenuName(playerid, bid);
		}
		else if(pData[playerid][pProductModify] == 3)
		{
			format(bData[bid][bPName3], 128, inputtext);
			Bisnis_Save(bid);

			SendCustomMessage(playerid, "BISNIS", "You have adjusted the name %s!", inputtext);
			Bisnis_ProductMenuName(playerid, bid);
		}
		else if(pData[playerid][pProductModify] == 4)
		{
			format(bData[bid][bPName4], 128, inputtext);
			Bisnis_Save(bid);

			SendCustomMessage(playerid, "BISNIS", "You have adjusted the name %s!", inputtext);
			Bisnis_ProductMenuName(playerid, bid);
		}
		else if(pData[playerid][pProductModify] == 5)
		{
			format(bData[bid][bPName5], 128, inputtext);
			Bisnis_Save(bid);

			SendCustomMessage(playerid, "BISNIS", "You have adjusted the name %s!", inputtext);
			Bisnis_ProductMenuName(playerid, bid);
		}
		else if(pData[playerid][pProductModify] == 6)
		{
			format(bData[bid][bPName6], 128, inputtext);
			Bisnis_Save(bid);

			SendCustomMessage(playerid, "BISNIS", "You have adjusted the name %s!", inputtext);
			Bisnis_ProductMenuName(playerid, bid);
		}
		else if(pData[playerid][pProductModify] == 7)
		{
			format(bData[bid][bPName7], 128, inputtext);
			Bisnis_Save(bid);

			SendCustomMessage(playerid, "BISNIS", "You have adjusted the name %s!", inputtext);
			Bisnis_ProductMenuName(playerid, bid);
		}
		else if(pData[playerid][pProductModify] == 8)
		{
			format(bData[bid][bPName8], 128, inputtext);
			Bisnis_Save(bid);

			SendCustomMessage(playerid, "BISNIS", "You have adjusted the name %s!", inputtext);
			Bisnis_ProductMenuName(playerid, bid);
		}
		else if(pData[playerid][pProductModify] == 9)
		{
			format(bData[bid][bPName9], 128, inputtext);
			Bisnis_Save(bid);

			SendCustomMessage(playerid, "BISNIS", "You have adjusted the name %s!", inputtext);
			Bisnis_ProductMenuName(playerid, bid);
		}
		else if(pData[playerid][pProductModify] == 10)
		{
			format(bData[bid][bPName10], 128, inputtext);
			Bisnis_Save(bid);

			SendCustomMessage(playerid, "BISNIS", "You have adjusted the name %s!", inputtext);
			Bisnis_ProductMenuName(playerid, bid);
		}
	}
	else return Bisnis_ProductMenuName(playerid, bid);
    return 1;
}

Dialog:BizEditProdName(playerid, response, listitem, inputtext[])
{
    if(Player_OwnsBisnis(playerid, pData[playerid][pInBiz]))
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					static
						item[40],
						str[128];

					strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
					strpack(pData[playerid][pEditingItem], item, 40 char);

					pData[playerid][pProductModify] = 0;
					format(str,sizeof(str), "Please enter the new product name for %s:", item);
					Dialog_Show(playerid, BizSetProdName, DIALOG_STYLE_INPUT, "Business: Set Name", str, "Modify", "Back");
				}
				case 1:
				{
					static
						item[40],
						str[128];

					strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
					strpack(pData[playerid][pEditingItem], item, 40 char);

					pData[playerid][pProductModify] = 1;
					format(str,sizeof(str), "Please enter the new product name for %s:", item);
					Dialog_Show(playerid, BizSetProdName, DIALOG_STYLE_INPUT, "Business: Set Name", str, "Modify", "Back");
				}
				case 2:
				{
					static
						item[40],
						str[128];

					strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
					strpack(pData[playerid][pEditingItem], item, 40 char);

					pData[playerid][pProductModify] = 2;
					format(str,sizeof(str), "Please enter the new product name for %s:", item);
					Dialog_Show(playerid, BizSetProdName, DIALOG_STYLE_INPUT, "Business: Set Name", str, "Modify", "Back");
				}
				case 3:
				{
					static
						item[40],
						str[128];

					strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
					strpack(pData[playerid][pEditingItem], item, 40 char);

					pData[playerid][pProductModify] = 3;
					format(str,sizeof(str), "Please enter the new product name for %s:", item);
					Dialog_Show(playerid, BizSetProdName, DIALOG_STYLE_INPUT, "Business: Set Name", str, "Modify", "Back");
				}
				case 4:
				{
					static
						item[40],
						str[128];

					strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
					strpack(pData[playerid][pEditingItem], item, 40 char);

					pData[playerid][pProductModify] = 4;
					format(str,sizeof(str), "Please enter the new product name for %s:", item);
					Dialog_Show(playerid, BizSetProdName, DIALOG_STYLE_INPUT, "Business: Set Name", str, "Modify", "Back");
				}
				case 5:
				{
					static
						item[40],
						str[128];

					strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
					strpack(pData[playerid][pEditingItem], item, 40 char);

					pData[playerid][pProductModify] = 5;
					format(str,sizeof(str), "Please enter the new product name for %s:", item);
					Dialog_Show(playerid, BizSetProdName, DIALOG_STYLE_INPUT, "Business: Set Name", str, "Modify", "Back");
				}
				case 6:
				{
					static
						item[40],
						str[128];

					strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
					strpack(pData[playerid][pEditingItem], item, 40 char);

					pData[playerid][pProductModify] = 6;
					format(str,sizeof(str), "Please enter the new product name for %s:", item);
					Dialog_Show(playerid, BizSetProdName, DIALOG_STYLE_INPUT, "Business: Set Name", str, "Modify", "Back");
				}
				case 7:
				{
					static
						item[40],
						str[128];

					strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
					strpack(pData[playerid][pEditingItem], item, 40 char);

					pData[playerid][pProductModify] = 7;
					format(str,sizeof(str), "Please enter the new product name for %s:", item);
					Dialog_Show(playerid, BizSetProdName, DIALOG_STYLE_INPUT, "Business: Set Name", str, "Modify", "Back");
				}
				case 8:
				{
					static
						item[40],
						str[128];

					strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
					strpack(pData[playerid][pEditingItem], item, 40 char);

					pData[playerid][pProductModify] = 8;
					format(str,sizeof(str), "Please enter the new product name for %s:", item);
					Dialog_Show(playerid, BizSetProdName, DIALOG_STYLE_INPUT, "Business: Set Name", str, "Modify", "Back");
				}
				case 9:
				{
					static
						item[40],
						str[128];

					strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
					strpack(pData[playerid][pEditingItem], item, 40 char);

					pData[playerid][pProductModify] = 9;
					format(str,sizeof(str), "Please enter the new product name for %s:", item);
					Dialog_Show(playerid, BizSetProdName, DIALOG_STYLE_INPUT, "Business: Set Name", str, "Modify", "Back");
				}
				case 10:
				{
					static
						item[40],
						str[128];

					strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
					strpack(pData[playerid][pEditingItem], item, 40 char);

					pData[playerid][pProductModify] = 10;
					format(str,sizeof(str), "Please enter the new product name for %s:", item);
					Dialog_Show(playerid, BizSetProdName, DIALOG_STYLE_INPUT, "Business: Set Name", str, "Modify", "Back");
				}
				case 11:
				{
					static
						item[40],
						str[128];

					strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
					strpack(pData[playerid][pEditingItem], item, 40 char);

					pData[playerid][pProductModify] = 11;
					format(str,sizeof(str), "Please enter the new product name for %s:", item);
					Dialog_Show(playerid, BizSetProdName, DIALOG_STYLE_INPUT, "Business: Set Name", str, "Modify", "Back");
				}
			}	
		}
		else
			return callcmd::bm(playerid, "\0");
	}
    return 1;
}

Dialog:BisnisPlayerBuyProd(playerid, response, listitem, inputtext[])
{
    static
	bizid = -1,
	price;

	if((bizid = pData[playerid][pInBiz]) != -1 && response && listitem != -1)
	{
		price = bData[bizid][bP][listitem];
		if(GetPlayerMoney(playerid) < price) return Error(playerid, "Not enough money!");
		new Float:health;
		GetPlayerHealth(playerid,health);
		if(bData[bizid][bType] == 1)
		{
			switch(listitem)
			{
				case 0:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][0]) return Error(playerid, "This business is out of stock product.");
					GivePlayerMoneyEx(playerid, -price);
					if(pData[playerid][pHunger]+12 > 100) pData[playerid][pHunger] = 100;
					else pData[playerid][pHunger] += 12;
					new Float:darah;
					GetPlayerHealth(playerid, darah);
					SetPlayerHealthEx(playerid, darah+10);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName0]), FormatMoney(price));
					
					bData[bizid][bMoney] += Server_Percent(price);
					BusinnesProduct[bizid][BussinesProduct][0]--;
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 1:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][1]) return Error(playerid, "This business is out of stock product.");
					GivePlayerMoneyEx(playerid, -price);
					if(pData[playerid][pHunger]+20 > 100) pData[playerid][pHunger] = 100;
					else pData[playerid][pHunger] += 20;
					new Float:darah;
					GetPlayerHealth(playerid, darah);
					SetPlayerHealthEx(playerid, darah+10);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName1]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][1]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 2:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][2]) return Error(playerid, "This business is out of stock product.");
					GivePlayerMoneyEx(playerid, -price);
					if(pData[playerid][pHunger]+30 > 100) pData[playerid][pHunger] = 100;
					else pData[playerid][pHunger] += 30;
					new Float:darah;
					GetPlayerHealth(playerid, darah);
					SetPlayerHealthEx(playerid, darah+10);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName2]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][2]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 3:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][3]) return Error(playerid, "This business is out of stock product.");
					GivePlayerMoneyEx(playerid, -price);
					BusinnesProduct[bizid][BussinesProduct][3]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
					if(pData[playerid][pEnergy]+20 > 100) pData[playerid][pEnergy] = 100;
					else pData[playerid][pEnergy] += 20;
					new Float:darah;
					GetPlayerHealth(playerid, darah);
					SetPlayerHealthEx(playerid, darah+10);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName3]), FormatMoney(price));
				}
			}
		}
		else if(bData[bizid][bType] == 2)
		{
			switch(listitem)
			{
				case 0:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][0]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pSnack] >= 5) return Error(playerid, "Maximum snack inventory is 5.");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pSnack]++;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName0]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][0]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 1:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][1]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pSprunk] >= 5) return Error(playerid, "Maximum sprunk inventory is 5.");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pSprunk]++;
					
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName1]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][1]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 2:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][2]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pBandage] >= 5) return Error(playerid, "Maximum bandage inventory is 5.");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pBandage]++;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName2]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][2]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 3:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][3]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pRokok] >= 5) return Error(playerid, "Maximum cigarettes inventory is 5.");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pRokok]++;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName3]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][3]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 4:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][4]) return Error(playerid, "This business is out of stock product.");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pPayToll] += 50;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName4]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][4]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
			}
		}
		else if(bData[bizid][bType] == 3)
		{
			new models[50] = {-1, ... },
				count;
			switch(listitem)
			{
				case 0:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][0]) return Error(playerid, "This business is out of stock product.");
					price = bData[bizid][bP][0];
					if(GetPlayerMoney(playerid) < price) return Error(playerid, "You have insufficient funds for the purchase.");
					GivePlayerMoneyEx(playerid, -price);
					BusinnesProduct[bizid][BussinesProduct][0]--;
					bData[bizid][bMoney] += Server_Percent(price);

					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
					switch(pData[playerid][pGender])
					{
						case 1: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SkinMale, "Clothes Shop", g_aMaleSkins, sizeof(g_aMaleSkins));
						case 2: ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_SkinFemale, "Clothes Shop", g_aFemaleSkins, sizeof(g_aFemaleSkins));
					}
				}
				case 1:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][1]) return Error(playerid, "This business is out of stock product.");

					if (pData[playerid][pVip] > 0) {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC)
						return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					} else {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC-2)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					}
					price = bData[bizid][bP][1];
					if(GetPlayerMoney(playerid) < price) return Error(playerid, "You have insufficient funds for the purchase.");
					GivePlayerMoneyEx(playerid, -price);
					BusinnesProduct[bizid][BussinesProduct][1]--;
					bData[bizid][bMoney] += Server_Percent(price);

					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}Toys {ffffff}for {00ff00}%s", FormatMoney(price));
					pData[playerid][pClothesType] = 2;
						
					for (new id; id < sizeof(accList); id++) if(accList[id][accListType] == 1) {
						models[count++] = accList[id][accListModel];
					}
					ShowCustomSelection(playerid, "Cap List", MODEL_SELECTION_AKSESORIS, models, count);
				}
				case 2:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][2]) return Error(playerid, "This business is out of stock product.");
					if (pData[playerid][pVip] > 0) {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					} else {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC-2)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					}
					price = bData[bizid][bP][2];
					if(GetPlayerMoney(playerid) < price) return Error(playerid, "You have insufficient funds for the purchase.");
					GivePlayerMoneyEx(playerid, -price);
					BusinnesProduct[bizid][BussinesProduct][2]--;
					bData[bizid][bMoney] += Server_Percent(price);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}Toys {ffffff}for {00ff00}%s", FormatMoney(price));
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
					pData[playerid][pClothesType] = 3;

					for (new id; id < sizeof(accList); id++) if(accList[id][accListType] == 2) {
						models[count++] = accList[id][accListModel];
					}
					ShowCustomSelection(playerid, "Bandana List", MODEL_SELECTION_AKSESORIS, models, count);
				}
				case 3:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][3]) return Error(playerid, "This business is out of stock product.");
					if (pData[playerid][pVip] > 0) {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC)
						return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					} else {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC-2)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					}
					price = bData[bizid][bP][3];
					if(GetPlayerMoney(playerid) < price) return Error(playerid, "You have insufficient funds for the purchase.");
					GivePlayerMoneyEx(playerid, -price);
					BusinnesProduct[bizid][BussinesProduct][3]--;
					bData[bizid][bMoney] += Server_Percent(price);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}Toys {ffffff}for {00ff00}%s", FormatMoney(price));
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
					pData[playerid][pClothesType] = 4;

					for (new id; id < sizeof(accList); id++) if(accList[id][accListType] == 3) {
						models[count++] = accList[id][accListModel];
					}
					ShowCustomSelection(playerid, "Mask List", MODEL_SELECTION_AKSESORIS, models, count);
				}
				case 4:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][4]) return Error(playerid, "This business is out of stock product.");
					if (pData[playerid][pVip] > 0) {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					} else {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC-2)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					}
					price = bData[bizid][bP][4];
					if(GetPlayerMoney(playerid) < price) return Error(playerid, "You have insufficient funds for the purchase.");
					GivePlayerMoneyEx(playerid, -price);
					BusinnesProduct[bizid][BussinesProduct][4]--;
					bData[bizid][bMoney] += Server_Percent(price);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}Toys {ffffff}for {00ff00}%s", FormatMoney(price));
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
					pData[playerid][pClothesType] = 5;

					for (new id; id < sizeof(accList); id++) if(accList[id][accListType] == 4) {
						models[count++] = accList[id][accListModel];
					}
					pData[playerid][pHelmet] = 1;
					ShowCustomSelection(playerid, "Helmet List", MODEL_SELECTION_AKSESORIS, models, count);
				}
				case 5:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][5]) return Error(playerid, "This business is out of stock product.");
					if (pData[playerid][pVip] > 0) {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					} else {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC-2)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					}
					price = bData[bizid][bP][5];
					if(GetPlayerMoney(playerid) < price) return Error(playerid, "You have insufficient funds for the purchase.");
					GivePlayerMoneyEx(playerid, -price);
					BusinnesProduct[bizid][BussinesProduct][5]--;
					bData[bizid][bMoney] += Server_Percent(price);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}Toys {ffffff}for {00ff00}%s", FormatMoney(price));
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
					pData[playerid][pClothesType] = 6;

					for (new id; id < sizeof(accList); id++) if(accList[id][accListType] == 5) {
						models[count++] = accList[id][accListModel];
					}
					ShowCustomSelection(playerid, "Watch List", MODEL_SELECTION_AKSESORIS, models, count);
				}
				case 6:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][6]) return Error(playerid, "This business is out of stock product.");
					if (pData[playerid][pVip] > 0) {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					} else {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC-2)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					}	
					price = bData[bizid][bP][6];
					if(GetPlayerMoney(playerid) < price) return Error(playerid, "You have insufficient funds for the purchase.");
					GivePlayerMoneyEx(playerid, -price);
					BusinnesProduct[bizid][BussinesProduct][6]--;
					bData[bizid][bMoney] += Server_Percent(price);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}Toys {ffffff}for {00ff00}%s", FormatMoney(price));
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
					pData[playerid][pClothesType] = 7;

					for (new id; id < sizeof(accList); id++) if(accList[id][accListType] == 6) {
						models[count++] = accList[id][accListModel];
					}
					ShowCustomSelection(playerid, "Glasses List", MODEL_SELECTION_AKSESORIS, models, count);
				}
				case 7:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][7]) return Error(playerid, "This business is out of stock product.");
					if (pData[playerid][pVip] > 0) {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					} else {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC-2)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					}
					price = bData[bizid][bP][7];
					if(GetPlayerMoney(playerid) < price) return Error(playerid, "You have insufficient funds for the purchase.");
					GivePlayerMoneyEx(playerid, -price);
					BusinnesProduct[bizid][BussinesProduct][7]--;
					bData[bizid][bMoney] += Server_Percent(price);

					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
					pData[playerid][pClothesType] = 8;

					for (new id; id < sizeof(accList); id++) if(accList[id][accListType] == 7) {
						models[count++] = accList[id][accListModel];
					}
					ShowCustomSelection(playerid, "Hair List", MODEL_SELECTION_AKSESORIS, models, count);
				}
				case 8:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][8]) return Error(playerid, "This business is out of stock product.");
					if (pData[playerid][pVip] > 0) {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					} else {
						if(Aksesoris_GetCount(playerid) >= MAX_ACC-2)
							return Error(playerid, "Slot untuk aksesoris sudah penuh.");
					}
					price = bData[bizid][bP][8];
					if(GetPlayerMoney(playerid) < price) return Error(playerid, "You have insufficient funds for the purchase.");
					GivePlayerMoneyEx(playerid, -price);
					BusinnesProduct[bizid][BussinesProduct][8]--;
					bData[bizid][bMoney] += Server_Percent(price);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}Toys {ffffff}for {00ff00}%s", FormatMoney(price));
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
					pData[playerid][pClothesType] = 9;

					for (new id; id < sizeof(accList); id++) if(accList[id][accListType] == 8) {
						models[count++] = accList[id][accListModel];
					}
					ShowCustomSelection(playerid, "Misc List", MODEL_SELECTION_AKSESORIS, models, count);
				}
			}
		}
		else if(bData[bizid][bType] == 4)
		{
			switch(listitem)
			{
				case 0:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][0]) return Error(playerid, "This business is out of stock product.");
					GivePlayerMoneyEx(playerid, -price);
					GivePlayerWeaponEx(playerid, 5, 1);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName0]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][0]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 1:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][1]) return Error(playerid, "This business is out of stock product.");
					GivePlayerMoneyEx(playerid, -price);
					GivePlayerWeaponEx(playerid, 6, 1);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName1]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][1]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 2:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][2]) return Error(playerid, "This business is out of stock product.");
					GivePlayerMoneyEx(playerid, -price);
					GivePlayerWeaponEx(playerid, 15, 1);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName2]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][2]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 3:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][3]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pFishTool] > 1) return Error(playerid, "Anda masih memiliki pancingan!");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pFishTool] = 100;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName3]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][3]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 4:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][4]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pMask] > 0) return Error(playerid, "Anda sudah memiliki Mask");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pMask] = 1;
					pData[playerid][pMaskID] = random(9999)+1000+pData[playerid][pMask];
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName4]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][4]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
			}
		}
		else if(bData[bizid][bType] == 5)
		{
			switch(listitem)
			{
				case 0:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][0]) return Error(playerid, "This business is out of stock product.");
					//if(pData[playerid][pPhone] > 0) return Error(playerid, "You have a cellphone already");
					new number[150];

					for(new i; i != 10; i++)
					{
						format(number, sizeof(number), "%s{%s}%d\n", number, ((i+1) % 2 == 0) ? ("C0C0C0") : ("FFFFFF"), (random(900000)+100000));
					}
					Dialog_Show(playerid, RandNumber, DIALOG_STYLE_LIST, "Phone Number", number, "Select", "Refresh");
				}	
				case 1:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][1]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pGPS] > 0) return Error(playerid, "Anda sudah memiliki GPS");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pGPS] = 1;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName1]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][1]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 2:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][2]) return Error(playerid, "This business is out of stock product.");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pPhoneCredit] += 1000;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName2]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][2]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 3:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][3]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pWT] > 0) return Error(playerid, "Anda sudah memiliki walkie talkie");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pWT] = 1;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName3]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][3]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 4:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][4]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pPhoneBook] > 0) return Error(playerid, "Anda sudah memiliki Phone Book!");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pPhoneBook] = 1;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName4]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][4]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
					ShowContacts(playerid);
				}
			}
		}	
		else if(bData[bizid][bType] == 6)
		{
			switch(listitem)
			{
				case 0:
				{
					new string[212];
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pGYMMember] = pData[playerid][pInBiz];
					pData[playerid][pGYMMemberTime] = (gettime()+3600);
					format(string, sizeof(string), "SHOP: {ffffff}You've purchased {ffff00}GYM Membership {ffffff}for {00ff00}%s", FormatMoney(price));
					SendClientMessage(playerid, COLOR_ARWIN, string);
					BusinnesProduct[bizid][BussinesProduct][0]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}	
				case 1:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][1]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pSprunk] > 5) return Error(playerid, "maximum bring spurnk in invetory 5");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pSprunk]++;
					
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName1]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][1]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 2:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][2]) return Error(playerid, "This business is out of stock product.");
					
					if(pData[playerid][pSnack] > 5) return Error(playerid, "maximum bring snacks in invetory 5");
					GivePlayerMoneyEx(playerid, -price);
					pData[playerid][pSnack]++;
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName3]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][2]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
				}
				case 3:
				{
					Dialog_Show(playerid, FightStyle, DIALOG_STYLE_LIST, "Fight Style", "Fight Style Normal\nFight Style Boxing\nFight Style Kunfu\nFight Style Kneehead\nFight Style Grabkick\nFight Style Elbow", "Buy", "Cancel");
				}
			}
		}		
		else if(bData[bizid][bType] == 7)
		{
			switch(listitem)
			{
				case 0:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][0]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pGunLic] == 0) return Error(playerid, "You don't have a gun license");
					new string[212];
					GivePlayerMoneyEx(playerid, -price);
					format(string, sizeof(string), "SHOP: {ffffff}You've purchased {ffff00}Weapon AK47 {ffffff}for {00ff00}%s", FormatMoney(price));
					GivePlayerWeaponEx(playerid, 30, 200);
					SendClientMessage(playerid, COLOR_ARWIN, string);
					bData[bizid][bMoney] += Server_Percent(price);
					BusinnesProduct[bizid][BussinesProduct][0]--;
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				}	
				case 1:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][1]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pGunLic] == 0) return Error(playerid, "You don't have a gun license");
					GivePlayerMoneyEx(playerid, -price);
					GivePlayerWeaponEx(playerid, 29, 200);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}Weapon MP5 {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName1]), FormatMoney(price));
					bData[bizid][bMoney] += Server_Percent(price);
					BusinnesProduct[bizid][BussinesProduct][1]--;
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				}
				case 2:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][2]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pGunLic] == 0) return Error(playerid, "You don't have a gun license");
					GivePlayerMoneyEx(playerid, -price);
					GivePlayerWeaponEx(playerid, 24, 200);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}Weapon Desert Eeagle {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName3]), FormatMoney(price));
					bData[bizid][bMoney] += Server_Percent(price);
					BusinnesProduct[bizid][BussinesProduct][2]--;
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				}
				case 3:
				{
					if(!BusinnesProduct[bizid][BussinesProduct][3]) return Error(playerid, "This business is out of stock product.");
					if(pData[playerid][pGunLic] == 0) return Error(playerid, "You don't have a gun license");
					GivePlayerMoneyEx(playerid, -price);
					GivePlayerWeaponEx(playerid, 25, 200);
					SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}Weapon Shotgun {ffffff}for {00ff00}%s", ReplaceString(bData[bizid][bPName3]), FormatMoney(price));
					BusinnesProduct[bizid][BussinesProduct][3]--;
					bData[bizid][bMoney] += Server_Percent(price);
					Server_AddPercent(price);
					Bisnis_Save(bizid);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
				}
				case 4:
				{
					if(IsTraining[playerid] != 0) return Error(playerid, "You are already training!");
					if(DelayPlayer[playerid][DelayTraining] != 0) return Error(playerid, "Tidak bisa menggunakan command ini");
					new String[212];
					format(String, sizeof(String), "Weapons Name\tSkill Level\tTraining Price\n");
					format(String, sizeof(String),"%sCountry Rifle\t%d\t$50.00\nShotgun\t%d\t$75.00\nDesert Eagle\t%d\t$95.00\nMP5\t%d\t$105.00\nAK47\t%d\t$115.00", String, pData[playerid][pSkillWeapon][0], pData[playerid][pSkillWeapon][1], pData[playerid][pSkillWeapon][2],pData[playerid][pSkillWeapon][3], pData[playerid][pSkillWeapon][4]);
					Dialog_Show(playerid, TrainingWeapon, DIALOG_STYLE_TABLIST_HEADERS, "Weapon Training", String, "Select", "Close");
				}
			}
		}		
	}
    return 1;
}

Dialog:FightStyle(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new
			bizid = pData[playerid][pInBiz],
			price;

		price = bData[bizid][bP][3];
		switch(listitem)
		{
			case 0:
			{
				SetPlayerFightingStyle(playerid, 4);
				GivePlayerMoneyEx(playerid, -price);
				SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", inputtext, FormatMoney(price));
				bData[bizid][bProd]--;
				bData[bizid][bMoney] += Server_Percent(price);
				Server_AddPercent(price);
				Bisnis_Save(bizid);
				pData[playerid][FightStyle] = 4;
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 1:
			{
				SetPlayerFightingStyle(playerid, 5);
				GivePlayerMoneyEx(playerid, -price);
				SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", inputtext, FormatMoney(price));
				bData[bizid][bProd]--;
				bData[bizid][bMoney] += Server_Percent(price);
				Server_AddPercent(price);
				Bisnis_Save(bizid);
				pData[playerid][FightStyle] = 5;
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 2:
			{
				SetPlayerFightingStyle(playerid, 6);
				GivePlayerMoneyEx(playerid, -price);
				SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", inputtext, FormatMoney(price));
				bData[bizid][bProd]--;
				bData[bizid][bMoney] += Server_Percent(price);
				Server_AddPercent(price);
				Bisnis_Save(bizid);
				pData[playerid][FightStyle] = 6;
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 3:
			{
				SetPlayerFightingStyle(playerid, 7);
				SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", inputtext, FormatMoney(price));
				bData[bizid][bProd]--;
				bData[bizid][bMoney] += Server_Percent(price);
				Server_AddPercent(price);
				Bisnis_Save(bizid);
				pData[playerid][FightStyle] = 7;
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 4:
			{
				SetPlayerFightingStyle(playerid, 15);
				SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", inputtext, FormatMoney(price));
				bData[bizid][bProd]--;
				bData[bizid][bMoney] += Server_Percent(price);
				Server_AddPercent(price);
				Bisnis_Save(bizid);
				pData[playerid][FightStyle] = 15;
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
			case 5:
			{
				SetPlayerFightingStyle(playerid, 16);
				SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}%s {ffffff}for {00ff00}%s", inputtext, FormatMoney(price));
				bData[bizid][bProd]--;
				bData[bizid][bMoney] += Server_Percent(price);
				Server_AddPercent(price);
				Bisnis_Save(bizid);
				pData[playerid][FightStyle] = 16;
				PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
			}
		}
	}
    return 1;
}


Dialog:DialogAksesorisDL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new models[50] = {-1, ... },
			count;	
		switch(listitem)
		{
			case 0:
			{
				for (new id; id < sizeof(accList); id++) if(accList[id][accListType] == 9) {
					models[count++] = accList[id][accListModel];
				}
				ShowCustomSelection(playerid, "0.3DL", MODEL_SELECTION_AKSESORIS, models, count);
			}
			case 1:
			{
				for (new id; id < sizeof(accList); id++) if(accList[id][accListType] == 10) {
					models[count++] = accList[id][accListModel];
				}
				ShowCustomSelection(playerid, "0.3DL", MODEL_SELECTION_AKSESORIS, models, count);
			}
		}
	}
    return 1;
}