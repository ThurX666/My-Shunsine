
CMD:addfurnstore(playerid, params[])
{
	if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");

	static
		price;

	if(sscanf(params, "d", price))
		return Usage(playerid, "/addfurnstore [price]");

	new id = FurnStore_Create(playerid, price);

	if(id == cellmin)
		return Error(playerid, "Tidak ada slot furniture store lagi.");

	Servers(playerid, "Furniture store id %d telah di buat, gunakan /editfurnstore untuk mengubah sesuatu.", id);
	return 1;
}

CMD:destroyfurnstore(playerid, params[])
{
	if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");

	new
		id;

	if(sscanf(params, "d", id))
		return Usage(playerid, "/destroyfurnstore [index]");

	if(!Iter_Contains(FurnStore, id))
		return Error(playerid, "Invalid furnstore id.");

	for (new i = 0; i < MAX_FURN_OBJECT; i ++) if(Iter_Contains(FurnObject, i) && FurnStore[i][furnStoreId] == storeData[id][storeID])
	{
		if (IsValidDynamic3DTextLabel(FurnStore[i][furnLabel]))
			DestroyDynamic3DTextLabel(FurnStore[i][furnLabel]);
		
		if (IsValidDynamicObject(FurnStore[i][furnObject]))
			DestroyDynamicObject(FurnStore[i][furnObject]);

		FurnStore[i][furnObject] = INVALID_STREAMER_ID;
		FurnStore[i][furnLabel] = Text3D:INVALID_STREAMER_ID;

		new query[128];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `furnobject` WHERE id='%d'", FurnStore[i][furnID]);
        mysql_tquery(g_SQL, query);
		FurnStore[i][furnID] = 0;
		FurnStore[i][furnStoreId] = 0;

		Iter_Remove(FurnObject, i);
	}

	new query[128];
	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `furnstore` WHERE id = '%d'", storeData[id][storeID]);
	mysql_tquery(g_SQL, query);
	storeData[id][storeID] = 0;
	storeData[id][storeOwner] = 0;

	if (IsValidDynamicPickup(storeData[id][storePickup]))
		DestroyDynamicPickup(storeData[id][storePickup]);

	if (IsValidDynamic3DTextLabel(storeData[id][storeLabel]))
		DestroyDynamic3DTextLabel(storeData[id][storeLabel]);

	if (IsValidDynamicCP(storeData[id][storeCP]))
		DestroyDynamicCP(storeData[id][storeCP]);

	Iter_Remove(FurnStore, id);	

	Servers(playerid, "Kamu telah menghapus furnstore id %d", id);
	return 1;
}

CMD:editfurnstore(playerid, params[])
{
	if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");

	static
		id,
		opsi[32],
		extend_str[128];

	if(sscanf(params, "ds[32]S()[128]", id, opsi, extend_str))
		return Usage(playerid, "/editfurnstore [index] [location/price/vault/resetemployee/sell]");

	if(!Iter_Contains(FurnStore, id))
		return Error(playerid, "Invalid furnstore id.");

	if(!strcmp(opsi, "location"))
	{
		GetPlayerPos(playerid, storeData[id][storePos][0], storeData[id][storePos][1], storeData[id][storePos][2]);

		FurnStore_Refresh(id);
		FurnStore_Save(id);
	}
	else if(!strcmp(opsi, "price"))
	{
		new price;

		if(sscanf(extend_str, "d", price))
			return Usage(playerid, "/editfurnstore [id] [price]");

		storeData[id][storePrice] = price;
		Servers(playerid, "You've update price for furnstore id #%d to %d.", id, price);

		FurnStore_Refresh(id);
		FurnStore_Save(id);
	}
	else if(!strcmp(opsi, "vault"))
	{
		new vault;

		if(sscanf(extend_str, "d", vault))
			return Usage(playerid, "/editfurnstore [id] [vault]");

		storeData[id][storeVault] = vault;
		Servers(playerid, "You've update vault for furnstore id #%d to %s.", id, FormatMoney(vault));

		FurnStore_Refresh(id);
		FurnStore_Save(id);
	}
	else if(!strcmp(opsi, "resetemployee"))
	{
		storeData[id][storeEmploye][0] = storeData[id][storeEmploye][1] = storeData[id][storeEmploye][2] = 0;
		Servers(playerid, "You've reset employee for furnstore id #%d", id);
		FurnStore_Save(id);
	}
	else if(!strcmp(opsi, "sell"))
	{
		if (pData[playerid][pAdmin] < 5)
			return PermissionError(playerid);

		if(!storeData[id][storeOwner])
			return Error(playerid, "There are no one owned this furnstore.");

		storeData[id][storeVault] = storeData[id][storeOwner] = 0;
		storeData[id][storeEmploye][0] = storeData[id][storeEmploye][1] = storeData[id][storeEmploye][2] = 0;
		format(storeData[id][storeOwnerName], MAX_PLAYER_NAME, "NONE");

		Servers(playerid, "You've selling furnstore id #%d.", id);

		FurnStore_Refresh(id);
		FurnStore_Save(id);
	}
	else if(!strcmp(opsi, "employee"))
	{
		if (pData[playerid][pAdmin] < 5)
			return PermissionError(playerid);

		ManageFurnStore[playerid] = id;
		Employee_List(playerid, id);
		Servers(playerid, "You've edit employee for furnstore id #%d", id);
	}
	else Usage(playerid, "/editfurnstore [index] [location/price/vault/resetemployee/sell]");
	return 1;
}

CMD:buyfurnstore(playerid, params[])
{
	static
		id = -1;

	if((id = FurnStore_Nearest(playerid)) != -1)
	{
		if(PropertiCommercial_CountMax(playerid) >= PropertiesCommercial_Max(playerid)) return Error(playerid, "You can no longer buy a business, your property slots are full");
		if (FurnStore_GetCount(playerid))
			return Error(playerid, "You've already have furniture store!");

		if(GetPlayerMoney(playerid) < storeData[id][storePrice])
			return Error(playerid, "Uang kamu tidak mencukupi.");

		if (storeData[id][storeOwner])
			return Error(playerid, "This furniture store is already owned by other players.");

		storeData[id][storeOwner] = pData[playerid][pID];
		format(storeData[id][storeOwnerName], MAX_PLAYER_NAME, ReturnName(playerid));

		FurnStore_Refresh(id);
		FurnStore_Save(id);

		GivePlayerMoneyEx(playerid, -storeData[id][storePrice]);
		Servers(playerid, "Kamu telah membeli furniture store baru!.");
		return 1;
	}
	Error(playerid, "Kamu tidak berada di dekat furnstore.");
	return 1;
}

CMD:fsm(playerid, params[])
{
	static
		id = -1;

	if((id = FurnStore_Inside(playerid)) != -1)
	{
		if(FurnStore_IsOwner(playerid, id) || FurnStore_IsEmployee(playerid, id))
		{
			Dialog_Show(playerid, FurnStoreMenu, DIALOG_STYLE_LIST, "Furniture Store Menu", "Exhibits%s", "Select", "Close", FurnStore_IsOwner(playerid, id) ? ("\nEmployee\nBank\nChange Name") : (""));
			ManageFurnStore[playerid] = id;
			return 1;
		}
		Error(playerid, "Kamu bukan pemilik/pegawai furniture store ini (%d-%d).", FurnStore_IsOwner(playerid, id), FurnStore_IsEmployee(playerid, id));
		return 1;
	}
	Error(playerid, "Kamu tidak berada di dalam furniture store.");
	return 1;
}

CMD:gotofurnstore(playerid, params[])
{
	if(pData[playerid][pDivision] != 3) return Error(playerid, "You must be a bussines division.");
	
	static
		index;

	if(sscanf(params, "d", index))
		return Usage(playerid, "/gotofurnstore [id]");

	if(!Iter_Contains(FurnStore, index))
		return Error(playerid, "Invalid furnstore id.");

	SetPlayerPos(playerid, storeData[index][storePos][0], storeData[index][storePos][1], storeData[index][storePos][2]);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	Servers(playerid, "You've teleported to furn store id %d.", index);
	return 1;
}

CMD:buyfurniture(playerid, params[])
{
	static
		id = -1;

	if((id = FurnStore_Inside(playerid)) != -1)
	{
        if (!storeData[id][storeOwner])
            return Error(playerid, "This furniture store has no owner, you cannot buy furniture on here.");

        if (storeData[id][storeSeal])
            return Error(playerid, "This furniture store is sealed by authority.");
        
        new i;
        if (sscanf(params, "d", i))
            return Usage(playerid, "/buyfurniture [furniture id]");

		if (!Iter_Contains(FurnObject, i))
            return Error(playerid, "Invalid furniture id.");
        
        if (FurnStore[i][furnStoreId] == storeData[id][storeID]) {
            if (!FurnStore[i][furnStock])
                return Error(playerid, "Tidak ada furniture yang dapat di jual sekarang.");
            
            if (GetPlayerMoney(playerid) < FurnStore[i][furnPrice])
			    return Error(playerid, "You don't have enough money.");

		    SetPVarInt(playerid, "furnObject", i);
            Dialog_Show(playerid, SelectProperty, DIALOG_STYLE_LIST, "Select Property", "Flat\nHouse\nSuite Room", "Select", "Cancel");
        }
	}
	else Error(playerid, "You're not inside furniture store.");
	return 1;
}
