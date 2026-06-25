
//----------[ Dialog Login Register]----------
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    while(strfind(inputtext, "%s",true) !=-1) strdel(inputtext,strfind(inputtext, "%s",true),strfind(inputtext, "%s",true)+2);
	while(strfind(inputtext, "%s",true) !=-1) strdel(inputtext,strfind(inputtext, "%s",true),strfind(inputtext, "%s",true)+2);

	if(dialogid == DIALOG_LOGIN)
	{
        if(!response) return Kick(playerid);

		new hashed_pass[65];
		SHA256_PassHash(inputtext, charData[playerid][cSalt], hashed_pass, 65);
		
		if (strcmp(hashed_pass, charData[playerid][cPassword]) == 0)
		{
			charData[playerid][cCharOn] = 0;
            LoadPlayerChar(playerid);
		}
		else
		{
			pData[playerid][LoginAttempts]++;

			if (pData[playerid][LoginAttempts] >= 5)
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Login", "Anda terlalu sering salah mengetik kata sandi (3 kali).", "Okay", "");
				KickEx(playerid);
			}
			else
			{
				new String[512];
				format(String, sizeof(String), "UCP Account: {00FFFF}%s\n"WHITE_E"Attemp: {00FFFF}%d/5\n"WHITE_E"Password: "GREEN_E"(input below)", charData[playerid][cName], pData[playerid][LoginAttempts]);
				ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Account Login", String," Login","Exit");
			}
		}
        return 1;
    }
    if( dialogid == DIALOG_LOGINCHAR)
	{
		if(!response) return 1;
		switch(listitem)
		{
			case 0:
			{
				if(GetPVarInt(playerid,"Char1da")==1)
				{
					loadPlayerChars(playerid,1);
					SetPlayerName(playerid, charData[playerid][cChar1]);
				}
				else
				{
					SendCustomMessage(playerid, ""RED_E"NOTE", ""YELLOW_E"Penggunaan nama harus mengikuti format Firstname_Lastname.");
					SendCustomMessage(playerid, ""RED_E"NOTE", ""YELLOW_E"Sebagai contoh, Steven_Dreschler, Nick_Raymond, dll.");
					ShowPlayerDialog(playerid, DIALOG_CREATECHARNEW1, DIALOG_STYLE_INPUT, "Username Character","Masukan Username yang mau anda gunakan","Next","Close");
					SetPVarInt(playerid,"createchar1",1);
				}
				return 1;
			}
			case 1:
			{
				if(GetPVarInt(playerid,"Char2da")==1)
				{
					loadPlayerChars(playerid,2);
					SetPlayerName(playerid, charData[playerid][cChar2]);
				}
				else
				{
					SendCustomMessage(playerid, ""RED_E"NOTE", ""YELLOW_E"Penggunaan nama harus mengikuti format Firstname_Lastname.");
					SendCustomMessage(playerid, ""RED_E"NOTE", ""YELLOW_E"Sebagai contoh, Steven_Dreschler, Nick_Raymond, dll.");
					ShowPlayerDialog(playerid, DIALOG_CREATECHARNEW1, DIALOG_STYLE_INPUT, "Username Character","Masukan Username yang mau anda gunakan","Next","Close");
					SetPVarInt(playerid,"createchar2",1);
				}
				return 1;
			}
			case 2:
			{
				if(GetPVarInt(playerid,"Char3da")==1)
				{
					loadPlayerChars(playerid,3);
					SetPlayerName(playerid, charData[playerid][cChar3]);
				}
				else
				{
					SendCustomMessage(playerid, ""RED_E"NOTE", ""YELLOW_E"Penggunaan nama harus mengikuti format Firstname_Lastname.");
					SendCustomMessage(playerid, ""RED_E"NOTE", ""YELLOW_E"Sebagai contoh, Steven_Dreschler, Nick_Raymond, dll.");
					ShowPlayerDialog(playerid, DIALOG_CREATECHARNEW1, DIALOG_STYLE_INPUT, "Username Character","Masukan Username yang mau anda gunakan","Next","Close");
					SetPVarInt(playerid,"createchar3",1);
				}
				return 1;
			}
		}
		return 1;
	}
	if( dialogid == DIALOG_CREATECHARNEW1)
	{
		if(!response) return 1;
		if(!IsValidName(inputtext))
		{
			Error(playerid, "Nama tidak sesuai format untuk server mode roleplay.");
			Error(playerid, "Penggunaan nama harus mengikuti format Firstname_Lastname.");
			Error(playerid, "Sebagai contoh, Steven_Dreschler, Nick_Raymond, dll.");
			ShowPlayerDialog(playerid, DIALOG_CREATECHARNEW1, DIALOG_STYLE_INPUT, "Username Character","Masukan Username yang mau anda gunakan","Next","Close");
			return 1;
		}
		charData[playerid][cCharOn] = 0;
		charData[playerid][cCharTime] = 0;
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "SELECT username FROM players WHERE username='%e'", inputtext);
		mysql_tquery(g_SQL, query, "CreateChar", "is", playerid, inputtext);
		return 1;
	}
	if(dialogid == DIALOG_EMOTE)
	{
		if(!response) return 1;
		return ApplyEmoteDialog(playerid, listitem);
	}
	if(dialogid == DIALOG_REGISTER1)
	{
		if (!response) return Kick(playerid);
		if (strlen(inputtext) <= 5) return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Registration", "Kata sandi Anda harus lebih dari 5 karakter!\nSilakan masukkan kata sandi Anda di bidang di bawah ini:", "Register", "Abort");
		
		if(!IsValidPassword(inputtext))
		{
			Error(playerid, "Kata sandi hanya dapat berisi A-Z, a-z, 0-9, _, [ ], ( )");
			ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Registration", "Your password must be valid characters!\nSilakan masukkan kata sandi Anda di bidang di bawah ini:", "Register", "Abort");
			return 1;
		}
		new query[512], pass[65], salt[16], verif=1;
		for (new i = 0; i < 16; i++) salt[i] = random(94) + 33;
		SHA256_PassHash(inputtext, salt, pass, 65);

		mysql_format(g_SQL, query, sizeof(query), "UPDATE ucp SET password='%s', salt='%e', verifemail='%d' WHERE username='%s'", pass, salt, verif, charData[playerid][cName]);
		mysql_tquery(g_SQL, query);

		ShowPlayerDialog(playerid, DIALOG_CREATECHARNEW1, DIALOG_STYLE_INPUT, "Username Character","Masukan Username yang mau anda gunakan","Next","Close");
		SetPVarInt(playerid,"createchar1",1);
		return 1;
	}	
	if(dialogid == DIALOG_REGISTER)
    {
		if (!response) return Kick(playerid);

		new String[512];
		format(String, sizeof(String), "UCP Account: {00FFFF}%s\n"WHITE_E"Attemp: {00FFFF}%d/5\n"WHITE_E"Password: "GREEN_E"(input below)", charData[playerid][cName], pData[playerid][LoginAttempts]);
		if(charData[playerid][cCharPinCode] == strval(inputtext))
		{
			ShowPlayerDialog(playerid, DIALOG_REGISTER1, DIALOG_STYLE_PASSWORD, "Register", String," Regis","Exit");
		}
		else return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Enter the pin code", "Enter the pin code sent in your discrod message!"," Regis","Exit");
	}
	if(dialogid == DIALOG_AGE)
    {
		if(!response) return ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Tanggal Lahir", "Masukan tanggal lahir (Tgl/Bulan/Tahun): 15/04/1998", "Pilih", "Batal");
		if(response)
		{
			new
				iDay,
				iMonth,
				iYear,
				day,
				month,
				year;
				
			getdate(year, month, day);

			static const
					arrMonthDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

			if(sscanf(inputtext, "p</>ddd", iDay, iMonth, iYear)) {
				ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Tanggal Lahir", "Error! Invalid Input\nMasukan tanggal lahir (Tgl/Bulan/Tahun): 15/04/1998", "Pilih", "Batal");
			}
			else if(iYear < 1900 || iYear > year) {
				ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Tahun Lahir", "Error! Invalid Input\nMasukan tanggal lahir (Tgl/Bulan/Tahun): 15/04/1998", "Pilih", "Batal");
			}
			else if(iMonth < 1 || iMonth > 12) {
				ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Bulan Lahir", "Error! Invalid Input\nMasukan tanggal lahir (Tgl/Bulan/Tahun): 15/04/1998", "Pilih", "Batal");
			}
			else if(iDay < 1 || iDay > arrMonthDays[iMonth - 1]) {
				ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Tanggal Lahir", "Error! Invalid Input\nMasukan tanggal lahir (Tgl/Bulan/Tahun): 15/04/1998", "Pilih", "Batal");
			}
			else 
			{
				format(pData[playerid][pAge], 50, inputtext);
				TogglePlayerControllable(playerid,0);
				SetPlayerHealth(playerid, 100.0);
				SetPlayerArmour(playerid, 0.0);
				SetPlayerPos(playerid, 2936.16, -2051.81, 3.56);
				SetPlayerCameraPos(playerid,2936.16, -2051.81,22.0264);
				SetPlayerCameraLookAt(playerid,2936.16, -2051.81,22.0264);
				SetPlayerVirtualWorld(playerid, 0);
				new query[842];
				mysql_format(g_SQL, query, sizeof query, "INSERT INTO `players` (`username`, `age`) VALUES ('%e', '%s')", pData[playerid][pName], inputtext);
				mysql_tquery(g_SQL, query, "OnPlayerRegisterChar", "i", playerid);
			}
		}
		else ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Tanggal Lahir", "Masukan tanggal lahir (Tgl/Bulan/Tahun): 15/04/1998", "Pilih", "Batal");
		return 1;
	}
	if(dialogid == DIALOG_GENDER)
    {
		if(!response) return ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
		if(response)
		{
			pData[playerid][pGender] = listitem + 1;
			switch (listitem) 
			{
				case 0: 
				{
					switch (pData[playerid][pGender])
					{
						case 1: 
						{
							new rand = Random(1, 7);
							pData[playerid][pSkin] = rand;
						}
						case 2: 
						{
							new rand = Random(10, 13);
							pData[playerid][pSkin] = rand;
						}	
					}
				}
				case 1: 
				{
					switch (pData[playerid][pGender])
					{
						case 1: 
						{
							new rand = Random(1, 7);
							pData[playerid][pSkin] = rand;
						}
						case 2: 
						{
							new rand = Random(10, 13);
							pData[playerid][pSkin] = rand;
						}	
					}
				}
			}
			ResetNameTag(playerid);
			SetPlayerStreamerSettings(playerid);
			pData[playerid][pnewplayer] = 1;
			pData[playerid][pNotifSpawn] = 1;
			SetSpawnInfo(playerid, 0, pData[playerid][pSkin], 2936.16, -2051.81, 3.56, 90.0000, 0, 0, 0, 0, 0, 0);
			SpawnPlayer(playerid);
			SendClientMessageEx(playerid, COLOR_ARWIN, "ACCOUNT: "WHITE_E"You've arrive at Stadium Pier with "GREEN_E"$200.00 {FFFFFF}in your hand and "GREEN_E"$200.00 {FFFFFF}on your Bank Account");
		}
		else ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
		return 1;
	}
	if(dialogid == DIALOG_ORIGIN)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					pData[playerid][pAccent1] = 0;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 1:
				{	
					pData[playerid][pAccent1] = 1;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 2:
				{
					pData[playerid][pAccent1] = 2;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 3:
				{
					pData[playerid][pAccent1] = 3;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 4:
				{
					pData[playerid][pAccent1] = 4;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 5:
				{
					pData[playerid][pAccent1] = 5;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 6:
				{
					pData[playerid][pAccent1] = 6;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 7:
				{	
					pData[playerid][pAccent1] = 7;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 8:
				{
					pData[playerid][pAccent1] = 8;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 9:
				{
					pData[playerid][pAccent1] = 9;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 10:
				{
					pData[playerid][pAccent1] = 10;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 11:
				{
					pData[playerid][pAccent1] = 11;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 12:
				{
					pData[playerid][pAccent1] = 12;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 13:
				{	
					pData[playerid][pAccent1] = 13;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 14:
				{
					pData[playerid][pAccent1] = 14;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 15:
				{
					pData[playerid][pAccent1] = 15;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 16:
				{
					pData[playerid][pAccent1] = 16;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 17:
				{
					pData[playerid][pAccent1] = 17;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 18:
				{
					pData[playerid][pAccent1] = 18;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 19:
				{	
					pData[playerid][pAccent1] = 19;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 20:
				{
					pData[playerid][pAccent1] = 20;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 21:
				{
					pData[playerid][pAccent1] = 21;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 22:
				{
					pData[playerid][pAccent1] = 22;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 23:
				{
					pData[playerid][pAccent1] = 23;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 24:
				{
					pData[playerid][pAccent1] = 24;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 25:
				{	
					pData[playerid][pAccent1] = 25;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 26:
				{
					pData[playerid][pAccent1] = 26;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 27:
				{
					pData[playerid][pAccent1] = 27;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 28:
				{
					pData[playerid][pAccent1] = 28;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 29:
				{
					pData[playerid][pAccent1] = 29;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
				case 30:
				{
					pData[playerid][pAccent1] = 30;
					new String[256];
					format(String, sizeof(String), "ORIGIN: {ffffff}Your character's accent has been set to '{ffff00}%s{ffffff}'", GetPlayerAccent(playerid));
					SendClientMessageEx(playerid,COLOR_ARWIN,String);
					ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Gender", "1. Male\n2. Female", "Pilih", "Batal");
				}
			}
		}
	}
	if(dialogid == DIALOG_CHANGEAGE)
    {
		if(response)
		{
			new
				iDay,
				iMonth,
				iYear,
				day,
				month,
				year;
				
			getdate(year, month, day);

			static const
					arrMonthDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

			if(sscanf(inputtext, "p</>ddd", iDay, iMonth, iYear)) {
				ShowPlayerDialog(playerid, DIALOG_CHANGEAGE, DIALOG_STYLE_INPUT, "Tanggal Lahir", "Error! Invalid Input\nMasukan tanggal lahir (Tgl/Bulan/Tahun): 15/04/1998", "Pilih", "Batal");
			}
			else if(iYear < 1900 || iYear > year) {
				ShowPlayerDialog(playerid, DIALOG_CHANGEAGE, DIALOG_STYLE_INPUT, "Tahun Lahir", "Error! Invalid Input\nMasukan tanggal lahir (Tgl/Bulan/Tahun): 15/04/1998", "Pilih", "Batal");
			}
			else if(iMonth < 1 || iMonth > 12) {
				ShowPlayerDialog(playerid, DIALOG_CHANGEAGE, DIALOG_STYLE_INPUT, "Bulan Lahir", "Error! Invalid Input\nMasukan tanggal lahir (Tgl/Bulan/Tahun): 15/04/1998", "Pilih", "Batal");
			}
			else if(iDay < 1 || iDay > arrMonthDays[iMonth - 1]) {
				ShowPlayerDialog(playerid, DIALOG_CHANGEAGE, DIALOG_STYLE_INPUT, "Tanggal Lahir", "Error! Invalid Input\nMasukan tanggal lahir (Tgl/Bulan/Tahun): 15/04/1998", "Pilih", "Batal");
			}
			else 
			{
				format(pData[playerid][pAge], 50, inputtext);
				SendClientMessageEx(playerid, COLOR_ARWIN, "AGE: "WHITE_E"New Age for your character is "YELLOW_E"%s.", pData[playerid][pAge]);
				GivePlayerMoneyEx(playerid, -300);
				Server_AddMoney(300);
			}
		}
		return 1;
	}
	//-----------[ House Dialog ]------------------
	if(dialogid == DIALOG_SELL_HOUSES)
	{
		if(!response) return 1;
		new str[248];
		SetPVarInt(playerid, "SellingHouse", ReturnPlayerHousesID(playerid, (listitem + 1)));
		format(str, sizeof(str), "Are you sure you will sell house id: %d", GetPVarInt(playerid, "SellingHouse"));
				
		ShowPlayerDialog(playerid, DIALOG_SELL_HOUSE, DIALOG_STYLE_MSGBOX, "Sell House", str, "Sell", "Cancel");
	}
	if(dialogid == DIALOG_SELL_HOUSE)
	{
		if(response)
		{
			new hid = GetPVarInt(playerid, "SellingHouse");
			GivePlayerMoneyEx(playerid, 2);
			SendCustomMessage(playerid, "HOUSE", "Anda berhasil menjual rumah id (%d) dengan setengah harga("LG_E"$2"WHITE_E") pada saat anda membelinya.", hid);
			HouseReset(hid);
			House_Save(hid);
			House_Refresh(hid);
		}
		DeletePVar(playerid, "SellingHouse");
		return 1;
	}
	if(dialogid == DIALOG_MY_HOUSES)
	{
		if(!response) return 1;
		SetPVarInt(playerid, "ClickedHouse", ReturnPlayerHousesID(playerid, (listitem + 1)));
		ShowPlayerDialog(playerid, HOUSE_INFO, DIALOG_STYLE_LIST, "{0000FF}Houses", "Show Information\nTrack House", "Select", "Cancel");
		return 1;
	}
	if(dialogid == HOUSE_INFO)
	{
		if(!response) return 1;
		new hid = GetPVarInt(playerid, "ClickedHouse");
		switch(listitem)
		{
			case 0:
			{
				new line9[900];
				new lock[128], type[128];
				if(hData[hid][hLocked] == 1)
				{
					lock = "{FF0000}Locked";
			
				}
				else
				{
					lock = "{00FF00}Unlocked";
				}
				if(hData[hid][hType] == 1)
				{
					type = "Small";
			
				}
				else if(hData[hid][hType] == 2)
				{
					type = "Medium";
				}
				else if(hData[hid][hType] == 3)
				{
					type = "Big";
				}
				else
				{
					type = "Unknow";
				}
				format(line9, sizeof(line9), "House ID: %d\nHouse Owner: %s\nHouse Address: %s\nHouse Price: %s\nHouse Type: %s\nHouse Status: %s",
				hid, hData[hid][hOwner], hData[hid][hAddress], FormatMoney(hData[hid][hPrice]), type, lock);

				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "House Info", line9, "Close","");
			}
			case 1:
			{
				pData[playerid][pTrackHouse] = 1;
				SetPlayerRaceCheckpoint(playerid,1, hData[hid][hExtposX], hData[hid][hExtposY], hData[hid][hExtposZ], 0.0, 0.0, 0.0, 3.5);
				//SetPlayerCheckpoint(playerid, hData[hid][hExtpos][0], hData[hid][hExtpos][1], hData[hid][hExtpos][2], 4.0);
				SendCustomMessage(playerid, "HOUSE", "Ikuti checkpoint untuk menemukan rumah anda!");
			}
		}
		return 1;
	}
	if(dialogid == HOUSE_STORAGE)
	{
		new hid = pData[playerid][pInHouse];
		if(response)
		{
			if(listitem == 0) 
			{
				House_WeaponStorage(playerid, hid);
			}
			else if(listitem == 1) 
			{
				Dialog_Show(playerid, HouseComponent, DIALOG_STYLE_LIST, "Component Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
			}
			else if(listitem == 2) 
			{
				Dialog_Show(playerid, HouseMaterial, DIALOG_STYLE_LIST, "Material Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
			}
			else if(listitem == 3) 
			{
				House_ShowSchematicDialog(playerid, hid);
			}
			else if(listitem == 4) 
			{
				ShowPlayerDialog(playerid, HOUSE_MONEY, DIALOG_STYLE_LIST, "Money Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
			}
			else if(listitem == 5) 
			{
				Dialog_Show(playerid, HouseCrack, DIALOG_STYLE_LIST, "Crack", "Withdraw from safe\nDeposit into safe", "Select", "Back");
			}
			else if(listitem == 6) 
			{
				Dialog_Show(playerid, HousePot, DIALOG_STYLE_LIST, "Pot", "Withdraw from safe\nDeposit into safe", "Select", "Back");
			}
		}
		return 1;
	}
	if(dialogid == HOUSE_WEAPONS)
	{
		new houseid = pData[playerid][pInHouse];
				
		if(response)
		{
			if(hData[houseid][hWeapon][listitem] != 0)
			{
				switch(hData[houseid][hTypeAmmo][listitem]) {
					case 0: {
						GivePlayerWeaponEx(playerid, hData[houseid][hWeapon][listitem], hData[houseid][hAmmo][listitem], 0);
					}
					case 1: {
						GivePlayerWeaponEx(playerid, hData[houseid][hWeapon][listitem], hData[houseid][hAmmo][listitem], 1);
					}
				}
				
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has taken a \"%s\" from their weapon storage.", ReturnName(playerid), ReturnWeaponName(hData[houseid][hWeapon][listitem]));

				hData[houseid][hWeapon][listitem] = 0;
				hData[houseid][hAmmo][listitem] = 0;
                hData[houseid][hTypeAmmo][listitem] = 0;

				House_Save(houseid);
				House_WeaponStorage(playerid, houseid);
			}
			else
			{
				new
					weaponid = GetWeapon(playerid),
					ammo = ReturnWeaponAmmo(playerid, weaponid);

				if(!weaponid)
					return Error(playerid, "You are not holding any weapon!");
				
				if(PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_typesurplus] == 2) return Error(playerid, "Senjata bertype JHP tidak bisa disimpan dirumah!");
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their weapon storage.", ReturnName(playerid), ReturnWeaponName(weaponid));
				hData[houseid][hWeapon][listitem] = weaponid;
				hData[houseid][hAmmo][listitem] = ammo;
				switch(PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_typesurplus]) {
					case 0: {
						hData[houseid][hTypeAmmo][listitem] = 0;
					}
					case 1: {
						hData[houseid][hTypeAmmo][listitem] = 1;
					}
				}
                ResetWeaponID(playerid, weaponid);
				House_Save(houseid);
				House_WeaponStorage(playerid, houseid);
			}
		}
		else House_OpenStorage(playerid, houseid);
		return 1;
	}
	if(dialogid == HOUSE_MONEY)
	{
		new houseid = pData[playerid][pInHouse];
		if(response)
		{
			switch (listitem)
			{
				case 0: 
				{
					new str[128];
					format(str, sizeof(str), "Safe Balance: %s\n\nPlease enter how much money you wish to withdraw from the safe:", FormatMoney(hData[houseid][hMoney]));
					ShowPlayerDialog(playerid, HOUSE_WITHDRAWMONEY, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
				}
				case 1: 
				{
					new str[128];
					format(str, sizeof(str), "Safe Balance: %s\n\nPlease enter how much money you wish to deposit into the safe:", FormatMoney(hData[houseid][hMoney]));
					ShowPlayerDialog(playerid, HOUSE_DEPOSITMONEY, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
				}
			}
		}
		else House_OpenStorage(playerid, houseid);
		return 1;
	}
	if(dialogid == HOUSE_WITHDRAWMONEY)
	{
		new houseid = pData[playerid][pInHouse];
		if(response)
		{
			new amount = strval(inputtext);

			if(isnull(inputtext))
			{
				new str[128];
				format(str, sizeof(str), "Safe Balance: %s\n\nPlease enter how much money you wish to withdraw from the safe:", FormatMoney(hData[houseid][hMoney]));
				ShowPlayerDialog(playerid, HOUSE_WITHDRAWMONEY, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
				return 1;
			}
			if(amount < 1 || amount > hData[houseid][hMoney])
			{
				new str[128];
				format(str, sizeof(str), "Error: Insufficient funds.\n\nSafe Balance: %s\n\nPlease enter how much money you wish to withdraw from the safe:", FormatMoney(hData[houseid][hMoney]));
				ShowPlayerDialog(playerid, HOUSE_WITHDRAWMONEY, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
				return 1;
			}
			hData[houseid][hMoney] -= amount;
			GivePlayerMoneyEx(playerid, amount);

			House_Save(houseid);
			House_OpenStorage(playerid, houseid);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has withdrawn %s from their house safe.", ReturnName(playerid), FormatMoney(amount));
		}
		else ShowPlayerDialog(playerid, HOUSE_MONEY, DIALOG_STYLE_LIST, "Money Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
		return 1;
	}
	if(dialogid == HOUSE_DEPOSITMONEY)
	{
		new houseid = pData[playerid][pInHouse];
		if(response)
		{
			new amount = strval(inputtext);

			if(isnull(inputtext))
			{
				new str[128];
				format(str, sizeof(str), "Safe Balance: %s\n\nPlease enter how much money you wish to deposit into the safe:", FormatMoney(hData[houseid][hMoney]));
				ShowPlayerDialog(playerid, HOUSE_DEPOSITMONEY, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
				return 1;
			}
			if(amount < 1 || amount > GetPlayerMoney(playerid))
			{
				new str[128];
				format(str, sizeof(str), "Error: Insufficient funds.\n\nSafe Balance: %s\n\nPlease enter how much money you wish to deposit into the safe:", FormatMoney(hData[houseid][hMoney]));
				ShowPlayerDialog(playerid, HOUSE_DEPOSITMONEY, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
				return 1;
			}
			hData[houseid][hMoney] += amount;
			GivePlayerMoneyEx(playerid, -amount);

			House_Save(houseid);
			House_OpenStorage(playerid, houseid);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deposited %s into their house safe.", ReturnName(playerid), FormatMoney(amount));
		}
		else ShowPlayerDialog(playerid, HOUSE_MONEY, DIALOG_STYLE_LIST, "Money Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
		return 1;
	}
	//-------------[ Player Weapons Atth ]-----------2262.7527,2036.2036,10.8203,266.1790
	if(dialogid == DIALOG_EDITBONE)
	{
		if(response)
		{
			new weaponid = EditingWeapon[playerid], weaponname[18], string[150];
			new index = (weaponid >= 22 && weaponid <= 38) ? (weaponid - 22) : (weaponid + 15);
	 
			GetWeaponName(weaponid, weaponname, sizeof(weaponname));
		   
			WeaponSettings[playerid][index][Bone] = listitem + 1;

			SendClientMessageEx(playerid, COLOR_ARWIN, "WEAPONINFO: "WHITE_E"You have successfully changed the bone of your %s.", weaponname);
		   
			mysql_format(g_SQL, string, sizeof(string), "INSERT INTO weaponsettings (Owner, WeaponID, Bone) VALUES ('%d', %d, %d) ON DUPLICATE KEY UPDATE Bone = VALUES(Bone)", pData[playerid][pID], weaponid, listitem + 1);
			mysql_tquery(g_SQL, string);
		}
		EditingWeapon[playerid] = 0;
	}
	//------------[ Family Dialog ]------------
	//-------------[ Faction Commands Dialog ]-----------
	if(dialogid == DIALOG_EDIT_PRICE)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Masukan harga Sprunk(1 - 500):\nPrice 1(Sprunk): "GREEN_E"$%s", FormatMoney(pData[playerid][pPrice1]));
					ShowPlayerDialog(playerid, DIALOG_EDIT_PRICE1, DIALOG_STYLE_INPUT, "Price 1", mstr, "Edit", "Cancel");
				}
				case 1:
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Masukan harga Snack(1 - 500):\nPrice 2(Snack): "GREEN_E"$%s", FormatMoney(pData[playerid][pPrice2]));
					ShowPlayerDialog(playerid, DIALOG_EDIT_PRICE2, DIALOG_STYLE_INPUT, "Price 2", mstr, "Edit", "Cancel");
				}
				case 2:
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Masukan harga Ice Cream Orange(1 - 500):\nPrice 3(Ice Cream Orange): "GREEN_E"$%s", FormatMoney(pData[playerid][pPrice3]));
					ShowPlayerDialog(playerid, DIALOG_EDIT_PRICE3, DIALOG_STYLE_INPUT, "Price 3", mstr, "Edit", "Cancel");
				}
				case 3:
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Masukan harga Hotdog(1 - 500):\nPrice 4(Hotdog): "GREEN_E"$%s", FormatMoney(pData[playerid][pPrice4]));
					ShowPlayerDialog(playerid, DIALOG_EDIT_PRICE4, DIALOG_STYLE_INPUT, "Price 4", mstr, "Edit", "Cancel");
				}
			}
		}
	}
	if(dialogid == DIALOG_EDIT_PRICE1)
	{
		if(response)
		{
			new amount = floatround(strval(inputtext));
			
			if(amount < 0 || amount > 10000) return Error(playerid, "Invalid price! $1 - $100.00");
			pData[playerid][pPrice1] = amount;
			SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: "WHITE_E"Anda berhasil mengedit price 1(Sprunk) ke "GREEN_E"$%s.", FormatMoney(amount));
			return 1;
		}
	}
	if(dialogid == DIALOG_EDIT_PRICE2)
	{
		if(response)
		{
			new amount = floatround(strval(inputtext));
			
			if(amount < 0 || amount > 10000) return Error(playerid, "Invalid price! $1 - $100.00.");
			pData[playerid][pPrice2] = amount;
			SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: "WHITE_E"Anda berhasil mengedit price 2(Snack) ke "GREEN_E"$%s.", FormatMoney(amount));
			return 1;
		}
	}
	if(dialogid == DIALOG_EDIT_PRICE3)
	{
		if(response)
		{
			new amount = floatround(strval(inputtext));
			
			if(amount < 0 || amount > 10000) return Error(playerid, "Invalid price! $1 - $100.00.");
			pData[playerid][pPrice3] = amount;
			SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: "WHITE_E"Anda berhasil mengedit price 3(Ice Cream Orange) ke "GREEN_E"$%s.", FormatMoney(amount));
			return 1;
		}
	}
	if(dialogid == DIALOG_EDIT_PRICE4)
	{
		if(response)
		{
			new amount = floatround(strval(inputtext));
			
			if(amount < 0 || amount > 10000) return Error(playerid, "Invalid price! $1 - $100.00.");
			pData[playerid][pPrice4] = amount;
			SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: "WHITE_E"Anda berhasil mengedit price 4(Hotdog) ke "GREEN_E"$%s.", FormatMoney(amount));
			return 1;
		}
	}
	if(dialogid == DIALOG_OFFER)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new id = pData[playerid][pOffer];
					if(!IsPlayerConnected(id) || !NearPlayer(playerid, id, 4.0))
						return Error(playerid, "You not near with offer player!");
					
					if(GetPlayerMoney(playerid) < pData[id][pPrice1])
						return Error(playerid, "Not enough money!");
						
					if(pData[id][pFood] < 5)
						return Error(playerid, "Food stock empty!");
					
					GivePlayerMoneyEx(id, pData[id][pPrice1]);
					pData[id][pFood] -= 5;
					
					GivePlayerMoneyEx(playerid, -pData[id][pPrice1]);
					pData[playerid][pSprunk] += 1;
					
					SendNearbyMessage(playerid, 10.0, COLOR_PURPLE, "** %s telah membeli sprunk seharga $%s.", ReturnName(playerid), FormatMoney(pData[id][pPrice1]));
				}
				case 1:
				{
					new id = pData[playerid][pOffer];
					if(!IsPlayerConnected(id) || !NearPlayer(playerid, id, 4.0))
						return Error(playerid, "You not near with offer player!");
					
					if(GetPlayerMoney(playerid) < pData[id][pPrice2])
						return Error(playerid, "Not enough money!");
					
					if(pData[id][pFood] < 5)
						return Error(playerid, "Food stock empty!");
						
					GivePlayerMoneyEx(id, pData[id][pPrice2]);
					pData[id][pFood] -= 5;
					
					GivePlayerMoneyEx(playerid, -pData[id][pPrice2]);
					pData[playerid][pSnack] += 1;
					
					SendNearbyMessage(playerid, 10.0, COLOR_PURPLE, "** %s telah membeli snack seharga $%s.", ReturnName(playerid), FormatMoney(pData[id][pPrice2]));	
				}
				case 2:
				{
					new id = pData[playerid][pOffer];
					if(!IsPlayerConnected(id) || !NearPlayer(playerid, id, 4.0))
						return Error(playerid, "You not near with offer player!");
					
					if(GetPlayerMoney(playerid) < pData[id][pPrice3])
						return Error(playerid, "Not enough money!");
					
					if(pData[id][pFood] < 10)
						return Error(playerid, "Food stock empty!");
						
					GivePlayerMoneyEx(id, pData[id][pPrice3]);
					pData[id][pFood] -= 10;
					
					GivePlayerMoneyEx(playerid, -pData[id][pPrice3]);
					pData[playerid][pEnergy] += 30;
					
					SendNearbyMessage(playerid, 10.0, COLOR_PURPLE, "** %s telah membeli ice cream orange seharga $%s.", ReturnName(playerid), FormatMoney(pData[id][pPrice3]));
				}
				case 3:
				{
					new id = pData[playerid][pOffer];
					if(!IsPlayerConnected(id) || !NearPlayer(playerid, id, 4.0))
						return Error(playerid, "You not near with offer player!");
					
					if(GetPlayerMoney(playerid) < pData[id][pPrice4])
						return Error(playerid, "Not enough money!");
						
					if(pData[id][pFood] < 10)
						return Error(playerid, "Food stock empty!");
					
					GivePlayerMoneyEx(id, pData[id][pPrice4]);
					pData[id][pFood] -= 10;
					
					GivePlayerMoneyEx(playerid, -pData[id][pPrice4]);
					pData[playerid][pHunger] += 30;
					
					SendNearbyMessage(playerid, 10.0, COLOR_PURPLE, "** %s telah membeli hotdog seharga $%s.", ReturnName(playerid), FormatMoney(pData[id][pPrice4]));
				}
			}
		}
		pData[playerid][pOffer] = -1;
	}
	if(dialogid == DIALOG_ATMWITHDRAW)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					if(pData[playerid][pBankMoney] < 5000)
						return Error(playerid, "Not enough balance!");
					
					GivePlayerMoneyEx(playerid, 5000);
					pData[playerid][pBankMoney] -= 5000;
					SendClientMessageEx(playerid, COLOR_ARWIN, "ATMINFO: "WHITE_E"You withdraw "LG_E"$50.00");
				}
				case 1:
				{
					if(pData[playerid][pBankMoney] < 20000)
						return Error(playerid, "Not enough balance!");
					
					GivePlayerMoneyEx(playerid, 20000);
					pData[playerid][pBankMoney] -= 20000;
					SendClientMessageEx(playerid, COLOR_ARWIN, "ATMINFO: "WHITE_E"You withdraw "LG_E"$200.00");
				}
				case 2:
				{
					if(pData[playerid][pBankMoney] < 50000)
						return Error(playerid, "Not enough balance!");
					
					GivePlayerMoneyEx(playerid, 50000);
					pData[playerid][pBankMoney] -= 50000;
					SendClientMessageEx(playerid, COLOR_ARWIN, "ATMINFO: "WHITE_E"You withdraw "LG_E"$500.00");
				}
				case 3:
				{
					if(pData[playerid][pBankMoney] < 100000)
						return Error(playerid, "Not enough balance!");
					
					GivePlayerMoneyEx(playerid, 100000);
					pData[playerid][pBankMoney] -= 100000;
					SendClientMessageEx(playerid, COLOR_ARWIN, "ATMINFO: "WHITE_E"You withdraw "LG_E"$1,000.00");
				}
				case 4:
				{
					if(pData[playerid][pBankMoney] < 500000)
						return Error(playerid, "Not enough balance!");
					
					GivePlayerMoneyEx(playerid, 500000);
					pData[playerid][pBankMoney] -= 500000;
					SendClientMessageEx(playerid, COLOR_ARWIN, "ATMINFO: "WHITE_E"You withdraw "LG_E"$5,000.00");
				}
			}
		}
	}
	if(dialogid == DIALOG_BANK)
	{
		if(!response) return true;
		switch(listitem)
		{
			case 0: // Check Balance
			{
				new mstr[512];
				format(mstr, sizeof(mstr), "{F6F6F6}You have "LB_E"$%s {F6F6F6}in your bank account.", FormatMoney(pData[playerid][pBankMoney]));
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""LB_E"Bank", mstr, "Close", "");
			}
			case 1:
			{
				DisplayPaycheck(playerid);
			}
		}
	}
	if(dialogid == DIALOG_BANKREKENING)
	{
		if(!response) return true;
		new amount = floatround(strval(inputtext));
		if(amount > pData[playerid][pBankMoney]) return Error(playerid, "Uang dalam rekening anda kurang.");
		if(amount < 1) return Error(playerid, "You have entered an invalid amount!");

		else
		{
			pData[playerid][pTransfer] = amount;
			ShowPlayerDialog(playerid, DIALOG_BANKTRANSFER, DIALOG_STYLE_INPUT, ""LB_E"Bank", "Masukan nomor rekening target:", "Transfer", "Cancel");
		}
	}
	if(dialogid == DIALOG_BANKTRANSFER)
	{

		/*if(!response) return true;
		new rek = floatround(strval(inputtext)), query[128];
	    if(rek < 1) return Error(playerid, "You have entered an invalid no rek!");
	    
		mysql_format(g_SQL, query, sizeof(query), "SELECT brek FROM players WHERE brek='%d'", rek);
	    mysql_tquery(g_SQL, query, "SearchRek", "id", playerid, rek);*/
		return 1;
	}
	if(dialogid == DIALOG_BANKCONFIRM)
	{
		if(response)
		{
			new query[128], mstr[248];
			mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET bmoney=bmoney+%d WHERE brek=%d", pData[playerid][pTransfer], pData[playerid][pTransferRek]);
			mysql_tquery(g_SQL, query);
			
			foreach(new ii : Player)
			{
				if(pData[ii][pBankRek] == pData[playerid][pTransferRek])
				{
					pData[ii][pBankMoney] += pData[playerid][pTransfer];
				}
			}
			
			pData[playerid][pBankMoney] -= pData[playerid][pTransfer];
			
			format(mstr, sizeof(mstr), ""WHITE_E"No Rek Target: "YELLOW_E"%d\n"WHITE_E"Nama Target: "YELLOW_E"%s\n"WHITE_E"Jumlah: "GREEN_E"%s\n\n"WHITE_E"Anda telah berhasil mentransfer!", pData[playerid][pTransferRek], pData[playerid][pTransferName], FormatMoney(pData[playerid][pTransfer]));
			ShowPlayerDialog(playerid, DIALOG_BANKSUKSES, DIALOG_STYLE_MSGBOX, ""LB_E"Transfer Sukses", mstr, "Sukses", "");
		}
	}
	if(dialogid == DIALOG_BANKSUKSES)
	{
		if(response)
		{
			pData[playerid][pTransfer] = 0;
			pData[playerid][pTransferRek] = 0;
		}
	}
	if(dialogid == DIALOG_PAYCHECK)
	{
		if(response)
		{
			if(pData[playerid][pPaycheck] < 0) return Error(playerid, "Sekarang belum waktunya anda mengambil paycheck.");
			
			new oldbalance = pData[playerid][pBankMoney]; 
			new query[512];
			mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM salary WHERE owner='%d' ORDER BY id ASC LIMIT 100", pData[playerid][pID]);
			mysql_query(g_SQL, query);
			new rows = cache_num_rows();
			if(rows) 
			{
				new date[30], info[16], money, totalduty, gajiduty, totalsal, total, pajak, hasil;
				
				totalduty = pData[playerid][pOnDutyTime] + pData[playerid][pTaxiTime];
				for(new i; i < rows; ++i)
				{
					cache_get_value_name(i, "info", info);
					cache_get_value_name(i, "date", date);
					cache_get_value_name_int(i, "money", money);
					totalsal += money;
				}
				
				if(totalduty > 1500)
				{
					gajiduty = 600;
				}
				else
				{
					gajiduty = totalduty;
				}
				total = gajiduty + totalsal;
				pajak = total / 100 * 10;
				hasil = total - pajak;
				pData[playerid][pBankMoney] += hasil;
				SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}<====================< "WHITE_E"Paycheck {00FFFF}>====================>");
				SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}=> "WHITE_E"Previous Balance: "GREEN_E"$%s", FormatMoney(oldbalance));
				SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}=> "WHITE_E"Income Tax: "RED_E"$%s", FormatMoney(pajak));
				SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}=> "WHITE_E"New Balance: "GREEN_E"$%s", FormatMoney(pData[playerid][pBankMoney]));
				SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}<======================================================================>");
				Server_MinMoney(hasil);
				pData[playerid][pPaycheck] = 0;
				pData[playerid][pOnDutyTime] = 0;
				pData[playerid][pTaxiTime] = 0;
				mysql_format(g_SQL, query, sizeof(query), "DELETE FROM salary WHERE owner='%d'", pData[playerid][pID]);
				mysql_query(g_SQL, query);
			}
			else
			{
				new totalduty, gajiduty, total, pajak, hasil;
				
				totalduty = pData[playerid][pOnDutyTime] + pData[playerid][pTaxiTime];
				
				if(totalduty > 600)
				{
					gajiduty = 600;
				}
				else
				{
					gajiduty = totalduty;
				}
				total = gajiduty;
				pajak = total / 100 * 10;
				hasil = total - pajak;
				
				pData[playerid][pBankMoney] += hasil;
				SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}<====================< "WHITE_E"Paycheck{00FFFF} >====================>");
				SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}=> "WHITE_E"Previous Balance: "GREEN_E"$%s", FormatMoney(oldbalance));
				SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}=> "WHITE_E"Income Tax: "RED_E"$%s", FormatMoney(pajak));
				SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}=> "WHITE_E"New Balance: "GREEN_E"$%s", FormatMoney(pData[playerid][pBankMoney]));
				SendClientMessageEx(playerid, COLOR_ARWIN, "{00FFFF}<======================================================================>");
				Server_MinMoney(hasil);
				pData[playerid][pPaycheck] = 0;
				pData[playerid][pOnDutyTime] = 0;
				pData[playerid][pTaxiTime] = 0;
			}
		}
	}
    if(dialogid == SWEEPERJOB)
	{
		if(response)
		{
		    switch(listitem)
			{
			    case 0:
			    {
					if(DialogSweeper[0] == false) // Kalau False atau tidak dipilih
					{
						DialogSweeper[0] = true; // Dialog 0 telah di pilih
						DialogSaya[playerid][0] = true;
						SweeperSteps[playerid][0] = 2;
						KerjaSweeper[playerid] = 1;
						SetPlayerRaceCheckpoint(playerid, 0, 1631.1259,-1875.8676,13.1079,1679.4075,-1867.3059,13.1157, 5.0);
						SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOBINFO: {FFFFFF}Ikutilah checkpoint yang tersedia pada Radar");
					}
					else SendClientMessage(playerid,-1,"ERROR: Route already taken by Someone");
				}
				case 1:
			    {
					if(DialogSweeper[1] == false) // Kalau False atau tidak dipilih
					{
						DialogSweeper[1] = true; // Dialog 1 telah di pilih
						DialogSaya[playerid][1] = true;
						SweeperSteps[playerid][1] = 2;
						KerjaSweeper[playerid] = 2;
						SetPlayerRaceCheckpoint(playerid, 0, 1613.3342,-1876.3984,13.1080,1543.2211,-1870.5433,13.1079, 5);
						SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOBINFO: {FFFFFF}Ikutilah checkpoint yang tersedia pada Radar");
					}
					else SendClientMessage(playerid,-1,"ERROR: Route already taken by Someone");
				}
                case 2:
			    {
					if(DialogSweeper[2] == false) // Kalau False atau tidak dipilih
					{
						DialogSweeper[2] = true; // Dialog 1 telah di pilih
						DialogSaya[playerid][2] = true;
						SweeperSteps[playerid][2] = 2;
						KerjaSweeper[playerid] = 3;
						SetPlayerRaceCheckpoint(playerid, 0, 1631.8092,-1875.8730,13.4909,1691.4486,-1833.3379,13.4829, 5);
						SendClientMessage(playerid, COLOR_ARWIN, "SIDEJOBINFO: {FFFFFF}Ikutilah checkpoint yang tersedia pada Radar");
					}
					else SendClientMessage(playerid,-1,"ERROR: Route already taken by Someone");
				}
			}
		}
		else RemovePlayerFromVehicle(playerid);
	}
	if(dialogid == DIALOG_BUYVEHVIP_CONFIRM)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new modelid = 522;
					new tstr[128], price = GetVehicleCostVIP(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHVIP_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 1:
				{
					new modelid = 411;
					new tstr[128], price = GetVehicleCostVIP(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHVIP_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 2:
				{
					new modelid = 451;
					new tstr[128], price = GetVehicleCostVIP(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHVIP_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 3:
				{
					new modelid = 494;
					new tstr[128], price = GetVehicleCostVIP(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHVIP_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 4:
				{
					new modelid = 541;
					new tstr[128], price = GetVehicleCostVIP(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHVIP_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 5:
				{
					new modelid = 573;
					new tstr[128], price = GetVehicleCostVIP(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHVIP_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
			}
		}
	}
	if(dialogid == DIALOG_BUYVEHVIP_CONFIRM2)
	{
		new modelid = pData[playerid][pBuyPvModel];
		if(response)
		{
			if(modelid <= 0) return Error(playerid, "Invalid model id.");
			new cost = GetVehicleCostVIP(modelid);
			
			if(pData[playerid][pMoney] < cost)
			{
				Error(playerid, "Uang anda tidak mencukupi.!");
				return 1;
			}
			new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(playerid);
			if(count >= limit)
			{
				Error(playerid, "Slot kendaraan anda sudah penuh, silahkan jual beberapa kendaraan anda terlebih dahulu!");
				return 1;
			}
			Server_Save();
			GivePlayerMoneyEx(playerid, -cost);
			pData[playerid][pClaimVIP][0]--;
			new cQuery[1024];
			new Float:x,Float:y,Float:z, Float:a;
			new model, color1, color2;
			new randcolor1 = Random(0, 126);
		    new randcolor2 = Random(0, 126);
			color1 = randcolor1;
			color2 = randcolor2;
			model = modelid;
			x = 561.8560;
			y = -1280.7902;
			z = 16.9526;
			a = 10.5345;
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			mysql_tquery(g_SQL, cQuery, "VehBuyVIP", "ddddddffff", playerid, pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			return 1;
		}
		else
		{
			pData[playerid][pBuyPvModel] = 0;
		}
	}

	if(dialogid == DIALOG_BUYVEHSUV_CONFIRM)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new modelid = 496;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSUV_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 1:
				{
					new modelid = 470;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSUV_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 2:
				{
					new modelid = 489;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSUV_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 3:
				{
					new modelid = 495;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSUV_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 4:
				{
					new modelid = 500;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSUV_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 5:
				{
					new modelid = 400;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSUV_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 6:
				{
					new modelid = 579;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSUV_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
			}
		}
	}
	if(dialogid == DIALOG_BUYVEHSUV_CONFIRM2)
	{
		new modelid = pData[playerid][pBuyPvModel];
		if(response)
		{
			if(modelid <= 0) return Error(playerid, "Invalid model id.");
			new cost = GetVehicleCost(modelid);
			
			if(pData[playerid][pMoney] < cost)
			{
				Error(playerid, "Uang anda tidak mencukupi.!");
				return 1;
			}
			new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(playerid);
			if(count >= limit)
			{
				Error(playerid, "Slot kendaraan anda sudah penuh, silahkan jual beberapa kendaraan anda terlebih dahulu!");
				return 1;
			}
			Server_Save();
			GivePlayerMoneyEx(playerid, -cost);
			new cQuery[1024];
			new Float:x,Float:y,Float:z, Float:a;
			new model, color1, color2;
			new randcolor1 = Random(0, 126);
		    new randcolor2 = Random(0, 126);
			color1 = randcolor1;
			color2 = randcolor2;
			model = modelid;
			x = 2119.2500;
			y = -1154.2800;
			z = 23.7900;
			a = 14.0500;
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			mysql_tquery(g_SQL, cQuery, "OnVehBuyPVLS", "ddddddffff", playerid, pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			return 1;
		}
		else
		{
			pData[playerid][pBuyPvModel] = 0;
		}
	}

	if(dialogid == DIALOG_BUYVEHJOB_CONFIRM)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new modelid = 554;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHJOB_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 1:
				{
					new modelid = 543;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHJOB_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 2:
				{
					new modelid = 422;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHJOB_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 3:
				{
					new modelid = 478;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHJOB_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 4:
				{
					new modelid = 455;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHJOB_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 5:
				{
					new modelid = 456;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHJOB_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 6:
				{
					new modelid = 499;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHJOB_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 7:
				{
					new modelid = 475;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHJOB_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 8:
				{
					new modelid = 559;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHJOB_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 9:
				{
					new modelid = 565;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHJOB_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
			}
		}
	}
	if(dialogid == DIALOG_BUYVEHJOB_CONFIRM2)
	{
		new modelid = pData[playerid][pBuyPvModel];
		if(response)
		{
			if(modelid <= 0) return Error(playerid, "Invalid model id.");
			new cost = GetVehicleCost(modelid);
			
			if(pData[playerid][pMoney] < cost)
			{
				Error(playerid, "Uang anda tidak mencukupi.!");
				return 1;
			}
			new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(playerid);
			if(count >= limit)
			{
				Error(playerid, "Slot kendaraan anda sudah penuh, silahkan jual beberapa kendaraan anda terlebih dahulu!");
				return 1;
			}
			Server_Save();
			GivePlayerMoneyEx(playerid, -cost);
			new cQuery[1024];
			new Float:x,Float:y,Float:z, Float:a;
			new model, color1, color2;
			new randcolor1 = Random(0, 126);
		    new randcolor2 = Random(0, 126);
			color1 = randcolor1;
			color2 = randcolor2;
			model = modelid;
			x = -252.58;
			y = -2218.14;
			z = 28.39;
			a = 71.80;
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			mysql_tquery(g_SQL, cQuery, "OnVehBuyPVLS", "ddddddffff", playerid, pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			return 1;
		}
		else
		{
			pData[playerid][pBuyPvModel] = 0;
		}
	}

	if(dialogid == DIALOG_BUYVEHSALOONS_CONFIRM)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new modelid = 445;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 1:
				{
					new modelid = 550;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 2:
				{
					new modelid = 540;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 3:
				{
					new modelid = 560;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 4:
				{
					new modelid = 491;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 5:
				{
					new modelid = 507;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 6:
				{
					new modelid = 492;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 7:
				{
					new modelid = 516;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 8:
				{
					new modelid = 405;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 9:
				{
					new modelid = 410;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 10:
				{
					new modelid = 426;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 11:
				{
					new modelid = 474;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSALOONS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
			}
		}
	}
	if(dialogid == DIALOG_BUYVEHSALOONS_CONFIRM2)
	{
		new modelid = pData[playerid][pBuyPvModel];
		if(response)
		{
			if(modelid <= 0) return Error(playerid, "Invalid model id.");
			new cost = GetVehicleCost(modelid);
			
			if(pData[playerid][pMoney] < cost)
			{
				Error(playerid, "Uang anda tidak mencukupi.!");
				return 1;
			}
			new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(playerid);
			if(count >= limit)
			{
				Error(playerid, "Slot kendaraan anda sudah penuh, silahkan jual beberapa kendaraan anda terlebih dahulu!");
				return 1;
			}
			Server_Save();
			GivePlayerMoneyEx(playerid, -cost);
			new cQuery[1024];
			new Float:x,Float:y,Float:z, Float:a;
			new model, color1, color2;
			new randcolor1 = Random(0, 126);
		    new randcolor2 = Random(0, 126);
			color1 = randcolor1;
			color2 = randcolor2;
			model = modelid;
			x = 2348.3600;
			y = -1999.6400;
			z = 13.0800;
			a = 35.2700;
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			mysql_tquery(g_SQL, cQuery, "OnVehBuyPVLS", "ddddddffff", playerid, pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			return 1;
		}
		else
		{
			pData[playerid][pBuyPvModel] = 0;
		}
	}

	if(dialogid == DIALOG_BUYVEHSPORTS_CONFIRM)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new modelid = 602;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSPORTS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 1:
				{
					new modelid = 506;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSPORTS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 2:
				{
					new modelid = 402;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSPORTS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 3:
				{
					new modelid = 415;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSPORTS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 4:
				{
					new modelid = 480;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSPORTS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 5:
				{
					new modelid = 562;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSPORTS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 6:
				{
					new modelid = 558;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSPORTS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 7:
				{
					new modelid = 475;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSPORTS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 8:
				{
					new modelid = 559;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSPORTS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 9:
				{
					new modelid = 565;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHSPORTS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
			}
		}
	}
	if(dialogid == DIALOG_BUYVEHSPORTS_CONFIRM2)
	{
		new modelid = pData[playerid][pBuyPvModel];
		if(response)
		{
			if(modelid <= 0) return Error(playerid, "Invalid model id.");
			new cost = GetVehicleCost(modelid);
			
			if(pData[playerid][pMoney] < cost)
			{
				Error(playerid, "Uang anda tidak mencukupi.!");
				return 1;
			}
			new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(playerid);
			if(count >= limit)
			{
				Error(playerid, "Slot kendaraan anda sudah penuh, silahkan jual beberapa kendaraan anda terlebih dahulu!");
				return 1;
			}
			Server_Save();
			GivePlayerMoneyEx(playerid, -cost);
			new cQuery[1024];
			new Float:x,Float:y,Float:z, Float:a;
			new model, color1, color2;
			new randcolor1 = Random(0, 126);
		    new randcolor2 = Random(0, 126);
			color1 = randcolor1;
			color2 = randcolor2;
			model = modelid;
			x = 2301.9400;
			y = -2340.8200;
			z = 13.3600;
			a = 183.33;
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			mysql_tquery(g_SQL, cQuery, "OnVehBuyPVLS", "ddddddffff", playerid, pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			return 1;
		}
		else
		{
			pData[playerid][pBuyPvModel] = 0;
		}
	}

	if(dialogid == DIALOG_BUYVEHLOWRIDERS_CONFIRM)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new modelid = 536;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHLOWRIDERS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 1:
				{
					new modelid = 575;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHLOWRIDERS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 2:
				{
					new modelid = 533;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHLOWRIDERS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 3:
				{
					new modelid = 534;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHLOWRIDERS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 4:
				{
					new modelid = 567;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHLOWRIDERS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 5:
				{
					new modelid = 535;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHLOWRIDERS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 6:
				{
					new modelid = 576;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHLOWRIDERS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 7:
				{
					new modelid = 412;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYVEHLOWRIDERS_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
			}
		}
	}
	if(dialogid == DIALOG_BUYVEHLOWRIDERS_CONFIRM2)
	{
		new modelid = pData[playerid][pBuyPvModel];
		if(response)
		{
			if(modelid <= 0) return Error(playerid, "Invalid model id.");
			new cost = GetVehicleCost(modelid);

			if(pData[playerid][pMoney] < cost)
			{
				Error(playerid, "Uang anda tidak mencukupi.!");
				return 1;
			}
			new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(playerid);
			if(count >= limit)
			{
				Error(playerid, "Slot kendaraan anda sudah penuh, silahkan jual beberapa kendaraan anda terlebih dahulu!");
				return 1;
			}
			Server_Save();
			GivePlayerMoneyEx(playerid, -cost);
			new cQuery[1024];
			new Float:x,Float:y,Float:z, Float:a;
			new model, color1, color2;
			new randcolor1 = Random(0, 126);
		    new randcolor2 = Random(0, 126);
			color1 = randcolor1;
			color2 = randcolor2;
			model = modelid;
			x = 1090.1200;
			y = -1230.7700;
			z = 15.8200;
			a = 270.0000;
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			mysql_tquery(g_SQL, cQuery, "OnVehBuyPVLS", "ddddddffff", playerid, pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			return 1;
		}
		else
		{
			pData[playerid][pBuyPvModel] = 0;
		}
	}


	if(dialogid == DIALOG_BUYBIKE_CONFIRM)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new modelid = 481;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYBIKE_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 1:
				{
					new modelid = 509;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYBIKE_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 2:
				{
					new modelid = 510;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYBIKE_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 3:
				{
					new modelid = 581;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYBIKE_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 4:
				{
					new modelid = 462;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYBIKE_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 5:
				{
					new modelid = 521;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYBIKE_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 6:
				{
					new modelid = 463;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYBIKE_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 7:
				{
					new modelid = 468;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYBIKE_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 8:
				{
					new modelid = 586;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYBIKE_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 9:
				{
					new modelid = 461;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYBIKE_CONFIRM2, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
			}
		}
	}
	if(dialogid == DIALOG_BUYBIKE_CONFIRM2)
	{
		new modelid = pData[playerid][pBuyPvModel];
		if(response)
		{
			if(modelid <= 0) return Error(playerid, "Invalid model id.");
			new cost = GetVehicleCost(modelid);
			
			if(pData[playerid][pMoney] < cost)
			{
				Error(playerid, "Uang anda tidak mencukupi.!");
				return 1;
			}
			new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(playerid);
			if(count >= limit)
			{
				Error(playerid, "Slot kendaraan anda sudah penuh, silahkan jual beberapa kendaraan anda terlebih dahulu!");
				return 1;
			}
			Server_Save();
			GivePlayerMoneyEx(playerid, -cost);
			new cQuery[1024];
			new Float:x,Float:y,Float:z, Float:a;
			new model, color1, color2;
			new randcolor1 = Random(0, 126);
		    new randcolor2 = Random(0, 126);
			color1 = randcolor1;
			color2 = randcolor2;
			model = modelid;
			foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
				if(Location[id][locType] == 8 && IsPlayerInRangeOfPoint(playerid, 50, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
					x = Location[id][locPos][0];
					y = Location[id][locPos][1];
					z = Location[id][locPos][2];
					a = Location[id][locPos][3];
				}
			}
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			mysql_tquery(g_SQL, cQuery, "OnVehBuyPVLS", "ddddddffff", playerid, pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			return 1;
		}
		else pData[playerid][pBuyPvModel] = 0;
	}
	if(dialogid == DIALOG_SHARELOC)
	{
		if(response)
		{
			new otherid = strval(inputtext);

			if(pData[playerid][pInjured] == 1)
		        return Error(playerid, "You are injured at the moment.");

			if(!IsPlayerConnected(otherid) || otherid == playerid) return SendClientMessage(playerid, 0xCECECEFF, "Tidak ada pemain seperti itu");

		    SetPVarInt(otherid, "sharelok", playerid);
		    //Info(otherid, "%s Telah menawari sharelok kepada anda, /accept sharelok untuk menerimanya /deny sharelok untuk membatalkannya.", ReturnName(playerid));
			SendClientMessageEx(playerid, COLOR_ARWIN, "SHARELOC: "WHITE_E"Anda berhasil menawari sharelok kepada player %s", ReturnName(otherid));
			SendClientMessageEx(otherid, COLOR_ARWIN, "SHARELOC: "WHITE_E"%s Telah menawari sharelok kepada anda, /accept sharelok untuk menerimanya /deny sharelok untuk membatalkannya.", ReturnName(playerid));

		}
		return 1;
	}
	if(dialogid == DIALOG_BUYPVCP_BOAT)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new modelid = 453;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYPVBOAT_CONFIRM, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 1:
				{
					new modelid = 452;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYPVBOAT_CONFIRM, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 2:
				{
					new modelid = 473;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYPVBOAT_CONFIRM, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 3:
				{
					new modelid = 484;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYPVBOAT_CONFIRM, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 4:
				{
					new modelid = 493;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYPVBOAT_CONFIRM, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
				case 5:
				{
					new modelid = 446;
					new tstr[128], price = GetVehicleCost(modelid);
					pData[playerid][pBuyPvModel] = modelid;
					format(tstr, sizeof(tstr), ""WHITE_E"Anda akan membeli kendaraan "PINK_E"%s "WHITE_E"dengan harga "LG_E"$%s", GetVehicleModelName(modelid), FormatMoney(price));
					ShowPlayerDialog(playerid, DIALOG_BUYPVBOAT_CONFIRM, DIALOG_STYLE_MSGBOX, "Private Vehicles", tstr, "Buy", "Batal");
				}
			}
		}
	}
	if(dialogid == DIALOG_BUYPVBOAT_CONFIRM)
	{
		new modelid = pData[playerid][pBuyPvModel];
		if(response)
		{
			if(modelid <= 0) return Error(playerid, "Invalid model id.");
			new cost = GetVehicleCost(modelid);
			if(pData[playerid][pMoney] < cost)
			{
				Error(playerid, "Uang anda tidak mencukupi.!");
				return 1;
			}
			new count = CountPlayerVehicle(playerid), limit = LimitSlotPlayerVehicle(playerid);
			if(count >= limit)
			{
				Error(playerid, "Slot kendaraan anda sudah penuh, silahkan jual beberapa kendaraan anda terlebih dahulu!");
				return 1;
			}
			GivePlayerMoneyEx(playerid, -cost);
			new cQuery[1024];
			new Float:x,Float:y,Float:z, Float:a;
			new model, color1, color2;
			color1 = 0;
			color2 = 0;
			model = modelid;
			foreach(new id : Locations) if(Location[id][locInterior] == GetPlayerInterior(playerid) && Location[id][locWorld] == GetPlayerVirtualWorld(playerid)) {
				if(Location[id][locType] == 11 && IsPlayerInRangeOfPoint(playerid, 50, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2])) {
					x = Location[id][locPos][0];
					y = Location[id][locPos][1];
					z = Location[id][locPos][2];
					a = Location[id][locPos][3];
				}
			}
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `vehicle` (`owner`, `model`, `color1`, `color2`, `price`, `x`, `y`, `z`, `a`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f')", pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			mysql_tquery(g_SQL, cQuery, "OnVehBuyPVBOAT", "ddddddffff", playerid, pData[playerid][pID], model, color1, color2, cost, x, y, z, a);
			return 1;
		}
		else
		{
			pData[playerid][pBuyPvModel] = 0;
		}
	}
	if(dialogid == DIALOG_FIGHTSTYLE)
	{
		if(response)
		{
			switch (listitem)
			{
				case 0:
				{
					if(GetPlayerMoney(playerid) < 12500)
						return Error(playerid, "Not enough money!");
					SetPlayerFightingStyle(playerid, 4);
					SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: "WHITE_E"You've managed to buy a fight style.");
					GivePlayerMoneyEx(playerid, -12500);
					pData[playerid][FightStyle] = 4;
				}
				case 1:
				{
					if(GetPlayerMoney(playerid) < 12500)
						return Error(playerid, "Not enough money!");
					SetPlayerFightingStyle(playerid, 5);
					SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: "WHITE_E"You've managed to buy a fight style.");
					GivePlayerMoneyEx(playerid, -12500);
					pData[playerid][FightStyle] = 5;
				}
				case 2:
				{
					if(GetPlayerMoney(playerid) < 12500)
						return Error(playerid, "Not enough money!");
					SetPlayerFightingStyle(playerid, 6);
					SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: "WHITE_E"You've managed to buy a fight style.");
					GivePlayerMoneyEx(playerid, -12500);
					pData[playerid][FightStyle] = 6;
				}
				case 3:
				{
					if(GetPlayerMoney(playerid) < 12500)
						return Error(playerid, "Not enough money!");		
					SetPlayerFightingStyle(playerid, 7);
					SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: "WHITE_E"You've managed to buy a fight style.");
					GivePlayerMoneyEx(playerid, -12500);
					pData[playerid][FightStyle] = 7;
				}
				case 4:
				{
					if(GetPlayerMoney(playerid) < 12500)
						return Error(playerid, "Not enough money!");			
					SetPlayerFightingStyle(playerid, 15);
					SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: "WHITE_E"You've managed to buy a fight style.");
					GivePlayerMoneyEx(playerid, -12500);
					pData[playerid][FightStyle] = 15;
				}
				case 5:
				{
					if(GetPlayerMoney(playerid) < 12500)
						return Error(playerid, "Not enough money!");
					SetPlayerFightingStyle(playerid, 16);
					SendClientMessageEx(playerid, COLOR_ARWIN, "BISNIS: "WHITE_E"You've managed to buy a fight style.");
					GivePlayerMoneyEx(playerid, -12500);
					pData[playerid][FightStyle] = 16;
				}
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_URL_BOOMBOX)
	{
		if(response)
		{
		    if(strlen(inputtext))
		    {
				new string[128], Float:BBCoord[4];
				GetPlayerPos(playerid, BBCoord[0], BBCoord[1], BBCoord[2]);
				GetPlayerFacingAngle(playerid, BBCoord[3]);
				SetPVarFloat(playerid, "BBX", BBCoord[0]);
				SetPVarFloat(playerid, "BBY", BBCoord[1]);
				SetPVarFloat(playerid, "BBZ", BBCoord[2]);
				BBCoord[0] += (2 * floatsin(-BBCoord[3], degrees));
				BBCoord[1] += (2 * floatcos(-BBCoord[3], degrees));
				BBCoord[2] -= 1.0;
				if(GetPVarInt(playerid, "PlacedBB")) return Error(playerid, "You already placed a radio");
				foreach(new i : Player)
				{
					if(GetPVarType(i, "PlacedBB"))
					{
						if(IsPlayerInRangeOfPoint(playerid, 30.0, GetPVarFloat(i, "BBX"), GetPVarFloat(i, "BBY"), GetPVarFloat(i, "BBZ")))
						{
							SendClientMessage(playerid, COLOR_ARWIN, "RADIO: "WHITE_E"You cannot put your radio in this Radius as their is already one placed in this radius");
							return 1;
						}
					}
				}
				SetPVarInt(playerid, "PlacedBB", CreateDynamicObject(2226, BBCoord[0], BBCoord[1], BBCoord[2], 0.0, 0.0, 0.0, .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid)));
				format(string, sizeof(string), "{00FFFF}[RADIO]\n"YELLOW_E"%s", ReturnName(playerid));
				SetPVarInt(playerid, "BBLabel", _:CreateDynamic3DTextLabel(string, -1, BBCoord[0], BBCoord[1], BBCoord[2]+0.6, 5, .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid)));
				SetPVarInt(playerid, "BBArea", CreateDynamicSphere(BBCoord[0], BBCoord[1], BBCoord[2], 30.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid)));
				SetPVarInt(playerid, "BBInt", GetPlayerInterior(playerid));
				SetPVarInt(playerid, "BBVW", GetPlayerVirtualWorld(playerid));
		        if(GetPVarType(playerid, "PlacedBB"))
				{
					// Pastikan owner radio langsung ikut play (tidak tergantung IsPlayerInDynamicArea)
					if(GetPVarType(playerid, "pAudioStream"))
					{
						StopAudioStreamForPlayer(playerid);
						DeletePVar(playerid, "pAudioStream");
					}
					SetPVarInt(playerid, "pAudioStream", 1);
					PlayAudioStreamForPlayer(playerid, inputtext, GetPVarFloat(playerid, "BBX"), GetPVarFloat(playerid, "BBY"), GetPVarFloat(playerid, "BBZ"), 30.0, 1);
					SendCustomMessage(playerid,"RADIO","You've been set the radio to: "YELLOW_E"%s", inputtext);

				    foreach(new i : Player)
					{
						if(i == playerid) continue;
						if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "BBArea")))
						{
							if(GetPVarType(i, "pAudioStream"))
							{
								StopAudioStreamForPlayer(i);
								DeletePVar(i, "pAudioStream");
							}
							SetPVarInt(i, "pAudioStream", 1);
							PlayAudioStreamForPlayer(i, inputtext, GetPVarFloat(playerid, "BBX"), GetPVarFloat(playerid, "BBY"), GetPVarFloat(playerid, "BBZ"), 30.0, 1);
						}
				  	}
			  		SetPVarString(playerid, "BBStation", inputtext);
				}
			}
		}
	}
	//Farm
	if(dialogid == FARM_SAFE)
	{
		if(!response) return 1;
		switch(listitem)
		{
			case 0:
			{
				ShowPlayerDialog(playerid, FARM_PRODUCT, DIALOG_STYLE_LIST, "Potato", "Withdraw from safe\nDeposit into safe", "Select", "Back");
			}
			case 1:
			{
				ShowPlayerDialog(playerid, FARM_WHITE, DIALOG_STYLE_LIST, "Wheat", "Withdraw from safe\nDeposit into safe", "Select", "Back");
			}
			case 2:
			{
				ShowPlayerDialog(playerid, FARM_ORANGE, DIALOG_STYLE_LIST, "Orange", "Withdraw from safe\nDeposit into safe", "Select", "Back");
			}
			case 3:
			{
				if(pData[playerid][pLadangRank] < 5)
					return Error(playerid, "You must Farm level 5 - 6!");
				ShowPlayerDialog(playerid, FARM_CHANGENAME, DIALOG_STYLE_INPUT, "Farm Change Name","Change Name Farm","OK","Exit");
			}
		}
		return 1;
	}
	if(dialogid == FARM_CHANGENAME)
	{
		if(response) 
		{
			new wid = pData[playerid][pLadang];
		    format(laData[wid][laName], 50, inputtext);
			Ladang_Save(wid);
			Ladang_Refresh(wid);
			SendClientMessageEx(playerid, COLOR_ARWIN, "FARM: "WHITE_E"kamu telah mengganti nama Farm menjadi "YELLOW_E"%s.", inputtext);
		}
		return 1;
	}
	if(dialogid == FARM_PRODUCT)
	{
		if(response)
		{
			new wid = pData[playerid][pLadang];
			if(wid == -1) return Error(playerid, "You don't have farm.");
			if(response)
			{
				switch (listitem)
				{
					case 0:
					{
						if(pData[playerid][pLadangRank] < 5)
							return Error(playerid, "You must farm owner!");
						new str[128];
						format(str, sizeof(str), "Product Balance: %d\n\nPlease enter how much product you wish to withdraw from the safe:", laData[wid][laProduct]);
						ShowPlayerDialog(playerid, FARM_WITHDRAWPRODUCT, DIALOG_STYLE_INPUT, "Withdraw from safe", str, "Withdraw", "Back");
					}
					case 1:
					{
						new str[128];
						format(str, sizeof(str), "Product Balance: %d\n\nPlease enter how much Product you wish to deposit into the safe:", laData[wid][laProduct]);
						ShowPlayerDialog(playerid, FARM_DEPOSITPRODUCT, DIALOG_STYLE_INPUT, "Deposit into safe", str, "Deposit", "Back");
					}
				}
			}
			else callcmd::lasafe(playerid);
		}
		return 1;
	}
	return 1;
}

Dialog:PVehicleStorage(playerid, response, listitem, inputtext[]) {
	new vehicleid = pData[playerid][pUseVehicleid];
    if(response)  {
		if(listitem == 0)  Vehicle_WeaponStorage(playerid, vehicleid);
		else if(listitem == 1)  Dialog_Show(playerid, VehicleComponent, DIALOG_STYLE_LIST, "Component Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
		else if(listitem == 2)  Dialog_Show(playerid, VehicleMaterial, DIALOG_STYLE_LIST, "Material Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
		else if(listitem == 3)  Dialog_Show(playerid, VehicleCrack, DIALOG_STYLE_LIST, "Crack Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
		else if(listitem == 4)  Dialog_Show(playerid, VehiclePot, DIALOG_STYLE_LIST, "Pot Safe", "Withdraw from safe\nDeposit into safe", "Select", "Back");
	} else SwitchVehicleBoot(vehicleid, false);
    return 1;
}

Dialog:VehicleDataStorage(playerid, response, listitem, inputtext[]) {
	new vehicleid = pData[playerid][pUseVehicleid];
    if(response) {
		if(listitem == 0) VehicleData_WeaponStorage(playerid, vehicleid);
	} else SwitchVehicleBoot(vehicleid, false);
    return 1;
}

Dialog:VehicleDataWeapon(playerid, response, listitem, inputtext[]) {
    new vehicleid = pData[playerid][pUseVehicleid],
        id = VehData_GoodFactionVeh(vehicleid, pData[playerid][pFaction]);

    if(id == -1) return Error(playerid, "Kendaraan faction tidak ditemukan.");
	if(response)  {
        if(listitem < 0 || listitem >= 4) return 1;

		if(VehicleData[id][Weapon][listitem] != 0)
		{
			switch(VehicleData[id][TypeAmmo][listitem]) {
				case 0: GivePlayerWeaponEx(playerid, VehicleData[id][Weapon][listitem], VehicleData[id][Ammo][listitem], 0);
				case 1: GivePlayerWeaponEx(playerid, VehicleData[id][Weapon][listitem], VehicleData[id][Ammo][listitem], 1);
			}
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has taken a \"%s\" from their faction vehicle trunk.", ReturnName(playerid), ReturnWeaponName(VehicleData[id][Weapon][listitem]));
			VehicleData[id][Weapon][listitem] = 0;
			VehicleData[id][Ammo][listitem] = 0;
			VehicleData[id][TypeAmmo][listitem] = 0;
			SaveVehicleData(id);
			VehicleData_WeaponStorage(playerid, vehicleid);
		}
		else
		{
			new weaponid = GetWeapon(playerid),
				ammo = ReturnWeaponAmmo(playerid, weaponid);

			if(!weaponid) return Error(playerid, "You are not holding any weapon!");
			if(PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_typesurplus] == 2) return Error(playerid, "Senjata bertype JHP tidak bisa disimpan dimobil!");

			SetPVarInt(playerid, "VehicleWeaponSlot", listitem);
			SetPVarInt(playerid, "VehicleWeaponStorageType", 1);
			Dialog_Show(playerid, VehicleWeaponAmmoInput, DIALOG_STYLE_INPUT, "Faction Weapon Storage", sprintf("Weapon: %s\nAmmo tersedia: %d\n\nMasukkan jumlah ammo yang ingin disimpan:", ReturnWeaponName(weaponid), ammo), "Store", "Back");
		}
	}
	else SwitchVehicleBoot(vehicleid, false);
    return 1;
}

Dialog:PVehicleWeapon(playerid, response, listitem, inputtext[]) {
    new vehicleid = pData[playerid][pUseVehicleid];
	if(response)  {
		foreach(new ii : PVehicles) if(pvData[ii][cVeh] == vehicleid) {
			if(pvData[ii][cWeapon][listitem] != 0)
			{
				switch(pvData[ii][cAmmoType][listitem]) {
					case 0:  GivePlayerWeaponEx(playerid, pvData[ii][cWeapon][listitem], pvData[ii][cAmmo][listitem], 0);
					case 1:  GivePlayerWeaponEx(playerid, pvData[ii][cWeapon][listitem], pvData[ii][cAmmo][listitem], 1);
				}
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has taken a \"%s\" from their weapon storage.", ReturnName(playerid), ReturnWeaponName(pvData[ii][cWeapon][listitem]));
				pvData[ii][cWeapon][listitem] = 0;
				pvData[ii][cAmmo][listitem] = 0;
				pvData[ii][cAmmoType][listitem] = 0;
				Vehicle_WeaponStorage(playerid, vehicleid);
			}
			else
			{
				new
					weaponid = GetWeapon(playerid),
					ammo = ReturnWeaponAmmo(playerid, weaponid);

				if(!weaponid) return Error(playerid, "You are not holding any weapon!");
				if(PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_typesurplus] == 2) return Error(playerid, "Senjata bertype JHP tidak bisa disimpan dimobil!");

				SetPVarInt(playerid, "VehicleWeaponSlot", listitem);
				SetPVarInt(playerid, "VehicleWeaponStorageType", 2);
				Dialog_Show(playerid, VehicleWeaponAmmoInput, DIALOG_STYLE_INPUT, "Weapon Storage", sprintf("Weapon: %s\nAmmo tersedia: %d\n\nMasukkan jumlah ammo yang ingin disimpan:", ReturnWeaponName(weaponid), ammo), "Store", "Back");
			}
		}  
	}
	else SwitchVehicleBoot(vehicleid, false);
    return 1;
}

Dialog:VehicleWeaponAmmoInput(playerid, response, listitem, inputtext[]) {
	new vehicleid = pData[playerid][pUseVehicleid];

	if(!response)
	{
		if(GetPVarInt(playerid, "VehicleWeaponStorageType") == 1) VehicleData_WeaponStorage(playerid, vehicleid);
		else Vehicle_WeaponStorage(playerid, vehicleid);
		return 1;
	}

	if(isnull(inputtext) || !IsNumeric(inputtext))
		return Error(playerid, "Masukkan jumlah ammo yang valid.");

	new weaponid = GetWeapon(playerid),
		ammo = ReturnWeaponAmmo(playerid, weaponid),
		slot = GetPVarInt(playerid, "VehicleWeaponSlot"),
		storageType = GetPVarInt(playerid, "VehicleWeaponStorageType"),
		storeAmmo = strval(inputtext),
		weaponSlot = g_aWeaponSlots[weaponid],
		typeAmmo = PlayerGuns[playerid][weaponSlot][weapon_typesurplus];

	if(!weaponid) return Error(playerid, "You are not holding any weapon!");
	if(typeAmmo == 2) return Error(playerid, "Senjata bertype JHP tidak bisa disimpan dimobil!");
	if(storeAmmo < 1 || storeAmmo > ammo) return Error(playerid, "Jumlah ammo harus diantara 1 sampai %d.", ammo);

	if(storageType == 1)
	{
		new id = VehData_GoodFactionVeh(vehicleid, pData[playerid][pFaction]);
		if(id == -1) return Error(playerid, "Kendaraan faction tidak ditemukan.");
		if(slot < 0 || slot >= 4) return 1;
		if(VehicleData[id][Weapon][slot] != 0) return VehicleData_WeaponStorage(playerid, vehicleid);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their faction vehicle trunk.", ReturnName(playerid), ReturnWeaponName(weaponid));
		VehicleData[id][Weapon][slot] = weaponid;
		VehicleData[id][Ammo][slot] = storeAmmo;
		switch(typeAmmo) {
			case 0: VehicleData[id][TypeAmmo][slot] = 0;
			case 1: VehicleData[id][TypeAmmo][slot] = 1;
		}
		if(storeAmmo >= ammo) ResetWeaponID(playerid, weaponid);
		else PlayerGuns[playerid][weaponSlot][weapon_ammo] -= storeAmmo;
		SaveVehicleData(id);
		return VehicleData_WeaponStorage(playerid, vehicleid);
	}
	else if(storageType == 2)
	{
		foreach(new ii : PVehicles) if(pvData[ii][cVeh] == vehicleid)
		{
			if(slot < 0 || slot >= 5) return 1;
			if(pvData[ii][cWeapon][slot] != 0) return Vehicle_WeaponStorage(playerid, vehicleid);

			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has stored a \"%s\" into their weapon storage.", ReturnName(playerid), ReturnWeaponName(weaponid));
			pvData[ii][cWeapon][slot] = weaponid;
			pvData[ii][cAmmo][slot] = storeAmmo;
			switch(typeAmmo) {
				case 0: pvData[ii][cAmmoType][slot] = 0;
				case 1: pvData[ii][cAmmoType][slot] = 1;
			}
			if(storeAmmo >= ammo) ResetWeaponID(playerid, weaponid);
			else PlayerGuns[playerid][weaponSlot][weapon_ammo] -= storeAmmo;
			return Vehicle_WeaponStorage(playerid, vehicleid);
		}
	}
	return 1;
}
