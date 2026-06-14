
Dialog:SelectProperty(playerid, response, listitem, inputtext[]) {
    if (response) {
        switch (listitem) {
            case 0: {
                new str[256], count = 0, address[32], location[64];
                strcat(str, "ID\tFlat Name\tLocation\n");
                foreach (new flatroom : FlatRooms) if (FlatRoom_IsOwner(playerid, flatroom) || FlatRoom_IsBuilder(playerid, flatroom)) {
                    FlatRoom_GetAddress(flatroom, address);
                    FlatRoom_GetLocation(flatroom, location);
                    format(str, sizeof(str), "%s%d\t%s\t%s\n",str,flatroom,address,location);
                    ListedFlat[playerid][count++] = flatroom;
                }
                if (count) Dialog_Show(playerid, FlatFurniture, DIALOG_STYLE_TABLIST_HEADERS, "Select Flat", str, "Select", "Close");
                else Error(playerid, "You don't have any flat");
            }
			case 1: {
                new str[256], count = 0;
                strcat(str, "ID\tAddress\tLocation\n");
                foreach (new i : Houses) if(Player_OwnsHouse(playerid, i) || hData[i][houseBuilder] == pData[playerid][pID]) {
                    format(str, sizeof(str), "%s%d\t%s\t%s\n",str,i,hData[i][hAddress],GetLocation(hData[i][hExtposX],hData[i][hExtposY],hData[i][hExtposZ]));
                    ListedHouse[playerid][count++] = i;
                }
                if (count) Dialog_Show(playerid, HouseFurniture, DIALOG_STYLE_TABLIST_HEADERS, "Select House", str, "Select", "Close");
                else Error(playerid, "You don't have any house");
            }
			case 2: {
				new str[256], count = 0;
                strcat(str, "ID\tLocation\n");
                foreach (new suiteid : SuiteRooms) if(Owner_SuiteRoom(playerid, suiteid)) {
                    format(str, sizeof(str), "%s%d\t%s\n",str,suiteid,GetLocation(SuiteRoom[suiteid][suiteRoomDoors][0], SuiteRoom[suiteid][suiteRoomDoors][1], SuiteRoom[suiteid][suiteRoomDoors][2]));
                    ListedSuiteRoom[playerid][count++] = suiteid;
                }
                if (count) Dialog_Show(playerid, SuiteRoomFurniture, DIALOG_STYLE_TABLIST_HEADERS, "Select Suite Room", str, "Select", "Close");
                else Error(playerid, "You don't have any suite room");
            }
        }
    }
    return 1;
}

Dialog:SuiteRoomFurniture(playerid, response, listitem, inputtext[]) {
	if (response) {
		new furnid = -1,
			id = GetPVarInt(playerid, "furnObject"),
			storeid = FurnStore_Inside(playerid),
			price = FurnStore[id][furnPrice],
			model = FurnStore[id][furnModel],
			suiteid = ListedSuiteRoom[playerid][listitem];

		if (storeid != -1) {
            if (!Owner_SuiteRoom(playerid, suiteid)) return Error(playerid, "You're not the owner this suiteroom.");
			if(SuiteFurniture_GetCount(suiteid) >= MAX_SUITE_FURNITURE)
				return Error(playerid, "You can only have %d furniture items in your suiteroom.", MAX_SUITE_FURNITURE);

			furnid = SuiteFurniture_Add(suiteid, FurnStore[id][furnName], model, 0.0, 0.0, 0.0);
			if(furnid == cellmin) return Error(playerid, "You don't have any suiteroom furniture slots left.");

			for (new i = 0; i < MAX_MATERIALS; i ++) if (FurnStore[id][furnMaterials][i] > 0) {
				SuiteFurniture[suiteid][furnid][suitefurnMaterials][i] = FurnStore[id][furnMaterials][i];
			}

			SuiteFurniture_Save(furnid, suiteid);
			GivePlayerMoneyEx(playerid, -price);
			SendCustomMessage(playerid, "FURNSTORE", "\"%s"WHITE_E"\" has arrived to your suiteroom", FurnStore[id][furnName]);

			FurnStore[id][furnStock]--;
			storeData[storeid][storeVault] += price;

			FurnObject_Refresh(id);
			FurnStore_Save(storeid);
		}
	}
	return 1;
}

Dialog:HouseFurniture(playerid, response, listitem, inputtext[]) {
	if (response) {
		new furnid = -1,
			id = GetPVarInt(playerid, "furnObject"),
			storeid = FurnStore_Inside(playerid),
			price = FurnStore[id][furnPrice],
			model = FurnStore[id][furnModel],
			houseid = ListedHouse[playerid][listitem];

		if (storeid != -1) {
            if (!House_IsBuilder(playerid) && !Player_OwnsHouse(playerid, houseid))
                return Error(playerid, "You're not the owner or builder of this house.");

            if(Furniture_GetCount(houseid) >= Furniture_GetMaxItems(houseid))
                return Error(playerid, "You can only have %d furniture items in your house.", Furniture_GetMaxItems(houseid));

            furnid = Furniture_Add(houseid, FurnStore[id][furnName], model, 0.0, 0.0, 0.0);

            if(furnid == cellmin)
                return Error(playerid, "You don't have any house furniture slots left.");

            for (new i = 0; i < MAX_MATERIALS; i ++) if (FurnStore[id][furnMaterials][i] > 0) {
                FurnitureData[houseid][furnid][furnitureMaterials][i] = FurnStore[id][furnMaterials][i];
            }

            Furniture_Save(furnid, houseid);
            GivePlayerMoneyEx(playerid, -price);
            SendCustomMessage(playerid, "FURNSTORE", "\"%s"WHITE_E"\" has arrived to your house", FurnStore[id][furnName]);

            FurnStore[id][furnStock]--;
            storeData[storeid][storeVault] += price;

            FurnObject_Refresh(id);
            FurnStore_Save(storeid);
		}
	}
	return 1;
}

Dialog:FlatFurniture(playerid, response, listitem, inputtext[]) {
	if (response) {
		new furnid = -1,
			id = GetPVarInt(playerid, "furnObject"),
			storeid = FurnStore_Inside(playerid),
			price = FurnStore[id][furnPrice],
			model = FurnStore[id][furnModel],
            flatid = ListedFlat[playerid][listitem];

		if (storeid != -1) {
            if (!FlatRoom_IsOwner(playerid, flatid) && !FlatRoom_IsBuilder(playerid, flatid))
                return Error(playerid, "You're not the owner or builder of this flat.");

            if(FlatFurniture_GetCount(flatid) >= FlatRoom_GetItemsMax(flatid))
                return Error(playerid, "You can only have %d furniture items in your flat.", FlatRoom_GetItemsMax(flatid));

            furnid = FlatFurniture_Add(flatid, FurnStore[id][furnName], model, 0.0, 0.0, 0.0);

            if(furnid == cellmin)
                return Error(playerid, "You don't have any flat furniture slots left.");

            for (new i = 0; i < MAX_MATERIALS; i ++) if (FurnStore[id][furnMaterials][i] > 0) {
                FlatFurniture[flatid][furnid][furnMaterials][i] = FurnStore[id][furnMaterials][i];
            }

            FlatFurniture_Save(furnid, flatid);
            GivePlayerMoneyEx(playerid, -price);
            SendCustomMessage(playerid, "FURNSTORE", "%s"WHITE_E" has arrived to your flat", FurnStore[id][furnName]);

            FurnStore[id][furnStock]--;
            storeData[storeid][storeVault] += price;

            FurnObject_Refresh(id);
            FurnStore_Save(storeid);
		}
	}
	return 1;
}

Dialog:SelectType(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new models[500] = {-1, ... },
				count;
		for (new i = 0; i < sizeof(g_aFurnitureData); i ++) if(g_aFurnitureData[i][e_FurnitureType] == listitem + 1) {
			models[count++] = g_aFurnitureData[i][e_FurnitureModel];
		}
		ShowCustomSelection(playerid, "Furniture List", MODEL_SELECTION_FURNITURE, models, count);
	}
	else FurnObject_List(playerid, ManageFurnStore[playerid]);
	return 1;
}

Dialog:Dialog_AddFurnObject(playerid, response, listitem, inputtext[])
{
	if (response)
	{           
		new id = FurnObject_Add(playerid, strval(inputtext), ManageFurnStore[playerid]);

		if(id == cellmin)
			return Error(playerid, "Furniture object untuk furniture store ini sudah mencapai batas maksimal.");

		ManageFurnObject[playerid] = id;
		Dialog_Show(playerid, ManageFurnObject, DIALOG_STYLE_LIST, "Manage Object", "Produce\nMove\nSet Name\nSet Price\nTexture\nDelete", "Select", "Close");

		Servers(playerid, "Object baru telah di buat, silahkan untuk memposisikan object dengan benar Menyalah gunakan akan mendapat sanksi berupa BANNED 3 hari.", 5000);
	} else FurnObject_Category(playerid);
	return 1;
}

Dialog:ManageFurn(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!strcmp(inputtext, "Add New"))
		{
			FurnObject_Category(playerid);
			return 1;
		}

		ManageFurnObject[playerid] = ListedFurnObject[playerid][listitem];
		Dialog_Show(playerid, ManageFurnObject, DIALOG_STYLE_LIST, "Manage Object", "Produce\nMove\nSet Name\nSet Price\nTexture\nDelete", "Select", "Close");
	}
	else Dialog_Show(playerid, FurnStoreMenu, DIALOG_STYLE_LIST, "Furniture Store Menu", "Exhibits%s", "Select", "Close", FurnStore_IsOwner(playerid, ManageFurnStore[playerid]) ? ("\nEmployee\nBank\nChange Name") : (""));
	return 1;
}

Dialog:ManageFurnObject(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new id = ManageFurnObject[playerid];
		switch(listitem)
		{
			case 0: {
				if(IsPlayerInDynamicArea(playerid, production))
					return Error(playerid, "Kamu harus berada di luar area kerja terlebih dahulu.");

				Dialog_Show(playerid, FurnStoreProduct, DIALOG_STYLE_INPUT, "Produce", "Berapa banyak yang akan di produksi?.", "Start", "Close");
			}
			case 1: {
				editFurnPosition[playerid] = id;
				PlayerEditPoint(playerid, FurnStore[id][furnPos][0], FurnStore[id][furnPos][1], FurnStore[id][furnPos][2], FurnStore[id][furnRot][0], FurnStore[id][furnRot][1], FurnStore[id][furnRot][2], "editFurnObject", FurnStore[id][furnObject]);
			}
			case 2: Dialog_Show(playerid, FurnObjectName, DIALOG_STYLE_INPUT, "Set Name", "Masukkan nama untuk furniture ini", "Set", "Close");
			case 3: Dialog_Show(playerid, FurnObjectPrice, DIALOG_STYLE_INPUT, "Set Price", "Masukkan harga untuk furniture ini", "Set", "Close");
			case 4: Dialog_Show(playerid, FurnObjectTexture, DIALOG_STYLE_INPUT, "Set Texture", "Masukkan data texture dengan mengikuti format berikut:\nFormat: "YELLOW_E"[index(0-16)] [Model ID] [TXD Name] [Texture Name]", "Update", "Back");
			case 5: {
				if (IsValidDynamic3DTextLabel(FurnStore[id][furnLabel]))
					DestroyDynamic3DTextLabel(FurnStore[id][furnLabel]);
				
				if (IsValidDynamicObject(FurnStore[id][furnObject]))
					DestroyDynamicObject(FurnStore[id][furnObject]);

				FurnStore[id][furnObject] = INVALID_STREAMER_ID;
				FurnStore[id][furnLabel] = Text3D:INVALID_STREAMER_ID;

				new query[128];
				mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `furnobject` WHERE id='%d'", FurnStore[id][furnID]);
				mysql_tquery(g_SQL, query);
				FurnStore[id][furnID] = 0;
				FurnStore[id][furnStoreId] = 0;

				Iter_Remove(FurnObject, id);
			}
		}
	}
	else FurnObject_List(playerid, ManageFurnStore[playerid]);
	return 1;
}

Dialog:FurnStoreProduct(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(strval(inputtext) < 1 || strval(inputtext) > 10)
			return Dialog_Show(playerid, FurnStoreProduct, DIALOG_STYLE_INPUT, "Produce", "Error: Tidak dapat memasukkan kurang dari 1 dan lebih dari 10.\n\nBerapa banyak yang akan di produksi?.", "Start", "Close");

		new component = strval(inputtext)*15;
		if (pData[playerid][pComponent] < component) return Error(playerid, "You need %d component(s) to produce furniture.", component);

		new index = ManageFurnObject[playerid];

		startProduce[playerid] = true;

		productionAdd[playerid] = strval(inputtext);
		productionCount[playerid] = 0;

		produceObject[playerid] = CreateDynamicObject(FurnStore[index][furnModel], 1489.54, 1789.14, 10.90, 0.0, 0.0, 0.0, (FurnStore[index][furnStoreId]+1), 3);
		
		for(new i = 0; i != MAX_MATERIALS; i++) if(FurnStore[index][furnMaterials][i] > 0)
		{
			SetDynamicObjectMaterial(produceObject[playerid], i, 
				GetTModel(FurnStore[index][furnMaterials][i]), 
				GetTXDName(FurnStore[index][furnMaterials][i]), 
				GetTextureName(FurnStore[index][furnMaterials][i]), 0
			);
		}
		SetPVarInt(playerid, "lagiedit", 2);
        SendCustomMessage(playerid, "STORE", "Go to the back room and hold "RED_E"N "WHITE_E"to start producing this furniture");
	}
	else Dialog_Show(playerid, ManageFurnObject, DIALOG_STYLE_LIST, "Manage Object", "Produce\nMove\nSet Name\nSet Price\nTexture\nDelete", "Select", "Close");
	return 1;
}

Dialog:FurnObjectTexture(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new index, model, txd[32], textures[32];

		if(sscanf(inputtext, "dds[32]s[32]", index, model, txd, textures))
			return Dialog_Show(playerid, FurnObjectTexture, DIALOG_STYLE_INPUT, "Set Price", "Masukkan data texture dengan mengikuti format berikut:\nFormat: "YELLOW_E"[index(0-16)] [Model ID] [TXD Name] [Texture Name]", "Update", "Back");

		if(index < 0 || index > 16)
			return Dialog_Show(playerid, FurnObjectTexture, DIALOG_STYLE_INPUT, "Set Price", "ERROR: Index yang hanya dapat di gunakan 0 - 16\n\nMasukkan data texture dengan mengikuti format berikut:\nFormat: "YELLOW_E"[index(0-16)] [Model ID] [TXD Name] [Texture Name]", "Update", "Back");

		if(!IsValidTexture(textures))
			return Dialog_Show(playerid, FurnObjectTexture, DIALOG_STYLE_INPUT, "Set Price", "ERROR: Texture model tidak terdaftar dalam database.\n\nMasukkan data texture dengan mengikuti format berikut:\nFormat: "YELLOW_E"[index(0-16)] [Model ID] [TXD Name] [Texture Name]", "Update", "Back");

		for (new i = 0; i < MAX_MATERIALS; i ++) {
			//RemoveDynamicObjectMaterial(FurnStore[ManageFurnObject[playerid]][furnObject], i);
		}
		
		FurnStore[ManageFurnObject[playerid]][furnMaterials][index] = GetTextureIndex(textures);
		
		FurnObject_Refresh(ManageFurnObject[playerid]);
		FurnObject_Save(ManageFurnObject[playerid]);

		Dialog_Show(playerid, ManageFurnObject, DIALOG_STYLE_LIST, "Manage Object", "Produce\nMove\nSet Name\nSet Price\nTexture\nDelete", "Select", "Close");
	}
	else Dialog_Show(playerid, ManageFurnObject, DIALOG_STYLE_LIST, "Manage Object", "Produce\nMove\nSet Name\nSet Price\nTexture\nDelete", "Select", "Close");
	return 1;
}

Dialog:FurnObjectName(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext))
			return Dialog_Show(playerid, FurnObjectName, DIALOG_STYLE_INPUT, "Set Name", "ERROR: Nama tidak boleh kosong\nMasukkan nama untuk furniture ini", "Set", "Close");

		if(strval(inputtext) > 32)
			return Dialog_Show(playerid, FurnObjectName, DIALOG_STYLE_INPUT, "Set Name", "ERROR: Nama terlalu panjang, maksimal 32 karakter\nMasukkan nama untuk furniture ini", "Set", "Close");

		format(FurnStore[ManageFurnObject[playerid]][furnName], 32, inputtext);
		FurnObject_Refresh(ManageFurnObject[playerid]);
		FurnObject_Save(ManageFurnObject[playerid]);
		Servers(playerid, "Nama telah di ganti menjadi: "GREEN_E"%s", FurnStore[ManageFurnObject[playerid]][furnName]);
	}
	return 1;
}

Dialog:FurnObjectPrice(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext))
			return Dialog_Show(playerid, FurnObjectPrice, DIALOG_STYLE_INPUT, "Set Name", "ERROR: Harga tidak boleh kosong\nMasukkan harga untuk furniture ini", "Set", "Close");

		if(strval(inputtext) < 1)
			return Dialog_Show(playerid, FurnObjectPrice, DIALOG_STYLE_INPUT, "Set Name", "ERROR: Harga tidak sesuai, tidak dapat di bawah harga 1\nMasukkan harga untuk furniture ini", "Set", "Close");
		new totalcash[25];
		format(totalcash, sizeof(totalcash), "%d00", strval(inputtext));
		FurnStore[ManageFurnObject[playerid]][furnPrice] = strval(totalcash);
		FurnObject_Refresh(ManageFurnObject[playerid]);
		FurnObject_Save(ManageFurnObject[playerid]);
		Servers(playerid, "Harga telah di ganti menjadi: "YELLOW_E"$%s", FormatMoney((FurnStore[ManageFurnObject[playerid]][furnPrice])));
	}
	return 1;
}

Dialog:FurnStoreMenu(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new index = ManageFurnStore[playerid];

		switch(listitem)
		{
			case 0: FurnObject_List(playerid, index);
			case 1: Employee_List(playerid, index);
			case 2: Dialog_Show(playerid, FurnStoreBank, DIALOG_STYLE_LIST, "Furniture Store Bank", "Deposit\nWithdraw\nCurrent balance: %s", "Select", "Close", FormatMoney(storeData[index][storeVault]));
			case 3: Dialog_Show(playerid, FurnStoreName, DIALOG_STYLE_INPUT, "Furniture Store Change Name", "Masukkan nama baru untuk furniture store ini:", "Change", "Close");
		}
	}
	return 1;
}

Dialog:FurnStoreEmployee(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!strcmp(inputtext, "Hire"))
			return Dialog_Show(playerid, HireEmployee, DIALOG_STYLE_INPUT, "Hire Employee", "Masukkan nama ataupun id player yang akan di pekerjakan:", "Hire", "Close");

		Dialog_Show(playerid, FiredEmployee, DIALOG_STYLE_MSGBOX, "Fired Employee", "Kamu yakin ingin memecat pegawai ini?", "Fired", "No");
		SetPVarInt(playerid, "SelectToFired", SelectToFired[playerid][listitem]);
	}
	return 1;
}

Dialog:HireEmployee(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new userid,
			index = ManageFurnStore[playerid];

		if(sscanf(inputtext, "u", userid)) 
			return Dialog_Show(playerid, HireEmployee, DIALOG_STYLE_INPUT, "Hire Employee", "ERROR: ID atau playerid tidak di masukkan\nMasukkan nama ataupun id player yang akan di pekerjakan:", "Hire", "Close");

		if(!IsPlayerNearPlayer(playerid, userid, 5.0))
			return Dialog_Show(playerid, HireEmployee, DIALOG_STYLE_INPUT, "Hire Employee", "ERROR: Player tersebut tidak berada dekat denganmu\nMasukkan nama ataupun id player yang akan di pekerjakan:", "Hire", "Close");

		if(IsPlayerConnected(userid))
		{
			for(new i = 0; i != MAX_EMPLOYE; i++) if(!storeData[index][storeEmploye][i])
			{
				storeData[index][storeEmploye][i] = pData[playerid][pID];
				FurnStore_Save(index);
				Servers(playerid, "Kamu telah mempekerjakan "YELLOW_E"%s "WHITE_E"ke dalam furniture store milikmu.", ReturnName(userid));
				Servers(playerid, "Kamu telah dipekerjakan oleh "YELLOW_E"%s "WHITE_E"di furniture store miliknya.", ReturnName(playerid));
				printf("Slot: %d", i);
				return 1;
			}
		}
		Dialog_Show(playerid, HireEmployee, DIALOG_STYLE_INPUT, "Hire Employee", "ERROR: ID atau playerid tidak berada dalam server\nMasukkan nama ataupun id player yang akan di pekerjakan:", "Hire", "Close");
		return 1;
	}
	return 1;
}

Dialog:FiredEmployee(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new index = ManageFurnStore[playerid],
			list = GetPVarInt(playerid, "SelectToFired");

		if(response)
		{
			storeData[index][storeEmploye][list] = 0;
			FurnStore_Save(index);

			Servers(playerid, "Kamu telah memecat pegawai dari furniture store milikmu.");

			DeletePVar(playerid, "SelectToFired");
			ManageFurnStore[playerid] = -1;
		}
		else Employee_List(playerid, index);
	}
	return 1;
}

Dialog:FurnStoreBank(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0: Dialog_Show(playerid, BankSelect, DIALOG_STYLE_INPUT, "Deposit", "Masukkan berapa uang yang akan kamu simpan:", "Deposit", "Close"), SetPVarInt(playerid, "bankSelect", 1);
			case 1: Dialog_Show(playerid, BankSelect, DIALOG_STYLE_INPUT, "Withdraw", "Masukkan berapa uang yang akan kamu ambil:", "Withdraw", "Close"), SetPVarInt(playerid, "bankSelect", 2);
			case 2: Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "Balance", "Current balance on this furniture store: %s", "Close", "", FormatMoney(storeData[ManageFurnStore[playerid]][storeVault]));
		}
	}
	return 1;
}

Dialog:BankSelect(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new index = ManageFurnStore[playerid],
			type = GetPVarInt(playerid, "bankSelect");

		if(strval(inputtext) < 1)
			return Dialog_Show(playerid, BankSelect, DIALOG_STYLE_INPUT, (type == 1) ? ("Deposit") : ("Withdraw"), "ERROR: Tidak dapat memasukkan input kurang dari 0\nMasukkan berapa uang yang akan kamu %s:", (type == 1) ? ("Deposit") : ("Withdraw"), "Close", (type == 1) ? ("simpan") : ("ambil"));

		if(type == 1) {
			if(GetPlayerMoney(playerid) < strval(inputtext))
				return Dialog_Show(playerid, BankSelect, DIALOG_STYLE_INPUT, "Deposit", "ERROR: Uang kamu tidak mencukupi\nMasukkan berapa uang yang akan kamu simpan:", "Deposit", "Close");
		}
		else {
			if(strval(inputtext) > storeData[index][storeVault])
				return Dialog_Show(playerid, BankSelect, DIALOG_STYLE_INPUT, "Withdraw", "ERROR: Uang dalam furniture store tidak mencukupi\nMasukkan berapa uang yang akan kamu ambil:", "Withdraw", "Close");
		}

		switch(type)
		{
			case 1: GivePlayerMoneyEx(playerid, -strval(inputtext)), storeData[index][storeVault] += strval(inputtext);
			case 2: GivePlayerMoneyEx(playerid, strval(inputtext)), storeData[index][storeVault] -= strval(inputtext);
		}
		Servers(playerid, "Kamu telah %s uang sebesar %s %s furniture store.", (type == 1) ? ("menyimpan") : ("mengambil"), FormatMoney(strval(inputtext)), (type == 1) ? ("untuk") : ("dari"));
		FurnStore_Save(index);

		DeletePVar(playerid, "bankSelect");
	}
	return 1;
}

Dialog:FurnStoreName(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext))
			return Dialog_Show(playerid, FurnStoreName, DIALOG_STYLE_INPUT, "Furniture Store Change Name", "ERROR: Masukkan nama yang benar, tidak boleh di kosongkan\nMasukkan nama baru untuk furniture store ini:", "Change", "Close");

		if(strlen(inputtext) > 32)
			return Dialog_Show(playerid, FurnStoreName, DIALOG_STYLE_INPUT, "Furniture Store Change Name", "ERROR: Nama yang kamu masukkan terlalu panjang ...\n ... maksimal memasukkan 32 karakter\nMasukkan nama baru untuk furniture store ini:", "Change", "Close");

		format(storeData[ManageFurnStore[playerid]][storeName], 32, ColouredText(inputtext));

		Servers(playerid, "Nama furniture store di ganti menjadi: %s", storeData[ManageFurnStore[playerid]][storeName]);

		FurnStore_Save(ManageFurnStore[playerid]);
		FurnStore_Refresh(ManageFurnStore[playerid]);
	}
	return 1;
}
