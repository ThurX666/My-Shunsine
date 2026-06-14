
Dialog:Workshop_Menu(playerid, response, listitem, inputtext[])
{
	new str[129];
    if(!response) return PlayerInWorkshop[playerid] = -1;
	switch(listitem) {
		case 0: {
			new wsid0 = PlayerInWorkshop[playerid];
			if(WorkshopData[wsid0][Dynamic] == 1) return Error(playerid, "This workshop is dynamic, cannot open/close gate.");
			switch(WorkshopData[wsid0][StatusWorkshop]) {
				case 0: {
					MoveDynamicObject(WorkshopData[wsid0][ObjectGate][0], WorkshopData[wsid0][GatePosF][0], WorkshopData[wsid0][GatePosF][1], WorkshopData[wsid0][GatePosF][2]-4, 3.0, WorkshopData[wsid0][GatePosF][3], WorkshopData[wsid0][GatePosF][4], WorkshopData[wsid0][GatePosF][5]);
					MoveDynamicObject(WorkshopData[wsid0][ObjectGate][1], WorkshopData[wsid0][GatePosR][0], WorkshopData[wsid0][GatePosR][1], WorkshopData[wsid0][GatePosR][2]-4, 3.0, WorkshopData[wsid0][GatePosR][3], WorkshopData[wsid0][GatePosR][4], WorkshopData[wsid0][GatePosR][5]);
					WorkshopData[wsid0][StatusWorkshop] = 1;
					WorkshopSave(wsid0);
				}
				case 1: {
					MoveDynamicObject(WorkshopData[wsid0][ObjectGate][0], WorkshopData[wsid0][GatePosF][0], WorkshopData[wsid0][GatePosF][1], WorkshopData[wsid0][GatePosF][2], 3.0, WorkshopData[wsid0][GatePosF][3], WorkshopData[wsid0][GatePosF][4], WorkshopData[wsid0][GatePosF][5]);
					MoveDynamicObject(WorkshopData[wsid0][ObjectGate][1], WorkshopData[wsid0][GatePosR][0], WorkshopData[wsid0][GatePosR][1], WorkshopData[wsid0][GatePosR][2], 3.0, WorkshopData[wsid0][GatePosR][3], WorkshopData[wsid0][GatePosR][4], WorkshopData[wsid0][GatePosR][5]);
					WorkshopData[wsid0][StatusWorkshop] = 0;
					WorkshopSave(wsid0);
				}
			}
		}
		case 1: {
			if(!OwnerWorkshop(playerid, PlayerInWorkshop[playerid])) return Error(playerid, "You can't access, you're not the owner of this workshop");
			Dialog_Show(playerid, Workshop_Name, DIALOG_STYLE_INPUT, "Workshop Name",""BLUE_E"HINT:\n"WHITE_E"- Teks mendukung bbcode, gunakan (n):untuk membuat baris baru, \
				(r):warna merah, (w):putih, \n\
				\t(b):biru, (bl):hitam, (g):hijau, (bl):kuning\n\
				\tContoh: Ganti (r)saya (w)menjadi merah dan seterusnya putih\n\
				- Tidak memasukkan teks kepanjangan\n\n\
				Maksimal teks tidak lebih dari 40 huruf:", "Change", "Close");
		}
		case 2: {
			if(!OwnerWorkshop(playerid, PlayerInWorkshop[playerid])) return Error(playerid, "You can't access, you're not the owner of this workshop");
			Dialog_Show(playerid, Workshop_BoardText, DIALOG_STYLE_INPUT, "Workshop Board",""BLUE_E"HINT:\n"WHITE_E"- Teks mendukung bbcode, gunakan (n):untuk membuat baris baru, \
				(r):warna merah, (w):putih, \n\
				\t(b):biru, (bl):hitam, (g):hijau, (bl):kuning\n\
				\tContoh: Ganti (r)saya (w)menjadi merah dan seterusnya putih\n\
				- Tidak memasukkan teks kepanjangan\n\n\
				Maksimal teks tidak lebih dari 40 huruf:", "Change", "Close");
		}
		case 3: {
			format(str, 129, "Store\t%d units in hands\nWithdraw\t%d units in storage", pData[playerid][pComponent], WorkshopData[PlayerInWorkshop[playerid]][StorageWorkshop][1]);
			Dialog_Show(playerid, Workshop_Storage, DIALOG_STYLE_LIST, "Workshop Storage", str, "Select", "Cancel");
		}
		case 4: {
			format(str, 129, "Deposit\t$%s in hands\nWithdraw\t$%s in Bank", FormatMoney(GetPlayerMoney(playerid)), FormatMoney(WorkshopData[PlayerInWorkshop[playerid]][StorageWorkshop][0]));
			Dialog_Show(playerid, Workshop_Bank, DIALOG_STYLE_LIST, "Workshop Bank", str, "Select", "Cancel");
		}
		case 5: {
			Dialog_Show(playerid, Workshop_Employee, DIALOG_STYLE_LIST, "Employees Management", "Add Employee\nRemove Employee\nRemove All Employees\nEmployees Members", "Select", "Close");
		}
	}
    return 1;
}

Dialog:Workshop_Name(playerid, response, listitem, inputtext[]) {
    new wsid = PlayerInWorkshop[playerid];
	if(response)
	{
		format(WorkshopData[wsid][Name], 128, "%s", inputtext);
		SendCustomMessage(playerid, "WORKSHOP", "Kamu mengganti nama workshop menjadi %s", inputtext);
		WorkshopRefresh(wsid);
		WorkshopSave(wsid);
	}
    return 1;
}

Dialog:Workshop_BoardText(playerid, response, listitem, inputtext[]) {
    new wsid = PlayerInWorkshop[playerid];
	if(response)
	{
		format(WorkshopData[wsid][TextWorkshop], 128, "%s", inputtext);
		WorkshopRefresh(wsid);
		WorkshopSave(wsid);
	}
    return 1;
}

Dialog:Workshop_Bank(playerid, response, listitem, inputtext[]) {
    new wsid = PlayerInWorkshop[playerid];
	if(response)
	{
		switch(listitem) {
			case 0: {
				Dialog_Show(playerid, Workshop_BankDeposit, DIALOG_STYLE_INPUT, "Bank Deposit", "Masukan jumlah yang ingin di masukan ke bank workshop (dollar):", "Input", "Close");
			}
			case 1: {
				if(!OwnerWorkshop(playerid, PlayerInWorkshop[playerid])) return Error(playerid, "You can't access, you're not the owner of this workshop");
				GivePlayerMoneyEx(playerid, WorkshopData[wsid][StorageWorkshop][0]);
				SendCustomMessage(playerid, "WORKSHOP", "You have taken "GREEN_E"$%s"WHITE_E" Money from inside the safe workshop, total money: "AQUA_E"$0", FormatMoney(WorkshopData[wsid][StorageWorkshop][0]));
				WorkshopData[wsid][StorageWorkshop][0] = 0;
				WorkshopSave(wsid);
			}
		}
	}
    return 1;
}

Dialog:Workshop_BankDeposit(playerid, response, listitem, inputtext[]) {
    new wsid = PlayerInWorkshop[playerid], totalcash[52];
	if(response)
	{
		format(totalcash, sizeof(totalcash), "%d00", strval(inputtext));
		if(strval(totalcash) < 0) return SendClientMessageEx(playerid, COLOR_GREY, "Tidak bisa dibawah $0.00");
		if (strval(totalcash) > GetPlayerMoney(playerid)) return SendClientMessageEx(playerid, COLOR_GREY, "Anda tidak memiliki uang sebesar itu.");
		WorkshopData[wsid][StorageWorkshop][0] += strval(totalcash);
		GivePlayerMoneyEx(playerid, -strval(totalcash));
		SendCustomMessage(playerid, "WORKSHOP", "You have deposited "GREEN_E"$%s{ffffff} Money into your workshop safe, total money: "AQUA_E"$%s", FormatMoney(strval(totalcash)), FormatMoney(WorkshopData[wsid][StorageWorkshop][0]));
	}
    return 1;
}

Dialog:Workshop_Storage(playerid, response, listitem, inputtext[]) {
    new wsid = PlayerInWorkshop[playerid];
	if(response)
	{
		switch(listitem) {
			case 0: {
				WorkshopData[wsid][StorageWorkshop][1] += pData[playerid][pComponent];
				SendCustomMessage(playerid, "WORKSHOP", "You've stored {ffff00}%d units component{ffffff} into your workshop safe, total components: "YELLOW_E"%d units", pData[playerid][pComponent], WorkshopData[wsid][StorageWorkshop][1]);
				pData[playerid][pComponent] = 0;
				WorkshopSave(wsid);
			}
			case 1: {
				new amount = 250 - pData[playerid][pComponent];
				if(amount > WorkshopData[wsid][StorageWorkshop][1]) {
					pData[playerid][pComponent] += WorkshopData[wsid][StorageWorkshop][1];
					WorkshopData[wsid][StorageWorkshop][1] = 0;
					SendCustomMessage(playerid, "WORKSHOP", "You have taken "YELLOW_E"%d units "GREEN_E"Component "WHITE_E"from inside workshop safe, total components: "YELLOW_E"0 units", amount);
				}
				else {
					pData[playerid][pComponent] += amount;
					WorkshopData[wsid][StorageWorkshop][1] -= amount;
					SendCustomMessage(playerid, "WORKSHOP", "You have taken "YELLOW_E"%d units "GREEN_E"Component "WHITE_E"from inside workshop safe, total components: "YELLOW_E"%d units", amount, WorkshopData[wsid][StorageWorkshop][1]);
				}
				WorkshopSave(wsid);
			}
		}
	}
    return 1;
}

Dialog:Workshop_Employee(playerid, response, listitem, inputtext[]) {
    static
        wsid = -1;

    if((wsid = PlayerInWorkshop[playerid]) != -1)
    {
		if (response) {
			switch(listitem)
			{
				case 0: {
                    if(!OwnerWorkshop(playerid, wsid)) return Error(playerid, "You can't access, you're not the owner of this workshop");
					Dialog_Show(playerid, Workshop_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Masukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");
				}
				case 1: {
                    if(!OwnerWorkshop(playerid, wsid)) return Error(playerid, "You can't access, you're not the owner of this workshop");
					Workshop_ShowEmployee(playerid, wsid, 1);
				}
				case 2: {
                    if(!OwnerWorkshop(playerid, wsid)) return Error(playerid, "You can't access, you're not the owner of this workshop");
					WorkshopEmployee_RemoveAll(wsid);
					SendCustomMessage(playerid, "WORKSHOP", "You've remove all employe on this business.");
				}
				case 3: Workshop_ShowEmployee(playerid, wsid, 0);
			}
		} else callcmd::ws(playerid, "\1");
	}
    return 1;
}

Dialog:Workshop_AddEmployee(playerid, response, listitem, inputtext[]) {
    if(response)
	{
		new id,
			wsid = PlayerInWorkshop[playerid];

		if (WorkshopEmployee_GetCount(wsid) >= 5) return Error(playerid, "This business is limited 5 employee.");
		if (sscanf(inputtext, "u", id)) return Dialog_Show(playerid, Workshop_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Masukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");
		if (!IsPlayerConnected(id)) return Dialog_Show(playerid, Workshop_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Player yang kamu masukkan tidak terkoneksi dalam game\nMasukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");
        if (id == playerid) return Dialog_Show(playerid, Workshop_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Tidak dapat memasukkan karakter kamu sendiri\nMasukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");
		if (Workshop_IsEmployee(id, wsid)) return Dialog_Show(playerid, Workshop_AddEmployee, DIALOG_STYLE_INPUT, "Add Employe", "Player tersebut sudah masuk dalam list employee\nMasukkan nama ataupun id player untuk kamu masukkan sebagai -\npekerja di bisnis ini.", "Add", "Close");

		WorkshopEmployee_Add(id, wsid);
		SendCustomMessage(playerid, "HIRED", "Kamu memasukkan "YELLOW_E"%s "WHITE_E"ke dalam list pekerja bisnismu.", ReturnName(id));
		SendCustomMessage(id, "HIRED", YELLOW_E"%s "WHITE_E"mempekerjakan kamu di bisnis miliknya (Bisnis: %s).", ReturnName(playerid), ReplaceString(WorkshopData[wsid][Name]));
	}
    return 1;
}

Dialog:Workshop_RemoveEmployee(playerid, response, listitem, inputtext[]) {
    if (response) {
        WorkshopEmployee_Remove(strval(inputtext));
		SendCustomMessage(playerid, "WORKSHOP", "You've remove list employee number #%d from your business.", strval(inputtext));
    }
    return 1;
}
