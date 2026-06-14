#include <YSI\y_hooks>

// Phone Textdraws IndoGreat
new Text:PhoneTD[33];
new Text:phoneclosetd;
new Text:mesaagetd;
new Text:contactstd;
new Text:calltd;
new Text:twittertd;
new Text:banktd;
new Text:apptd;
new Text:gpstd;
new Text:settingtd;
new Text:cameratd;

//-----[ Selfie System ]-----
new takingselfie[MAX_PLAYERS];
new Float:SelfieDegree[MAX_PLAYERS];
const Float: SelfieRadius = 1.4; //do not edit this
const Float: SelfieSpeed  = 1.25; //do not edit this
const Float: SelfieHeight = 1.0; // do not edit this
new Float:Selfielx[MAX_PLAYERS];
new Float:Selfiely[MAX_PLAYERS];
new Float:Selfielz[MAX_PLAYERS];

//-----[ Download System ]-----
new download[MAX_PLAYERS];

task onlineTimer[1000]()
{	
	//Date and Time Textdraw
	new datestring[64];
	new hours,
	minutes,
	seconds,
	days,
	months,
	years;
	new MonthName[12][] =
	{
		"January", "February", "March", "April", "May", "June",
		"July",	"August", "September", "October", "November", "December"
	};
	getdate(years, months, days);
 	gettime(hours, minutes, seconds);
	format(datestring, sizeof datestring, "%s%d %s %s%d", ((days < 10) ? ("0") : ("")), days, MonthName[months-1], (years < 10) ? ("0") : (""), years);
	//Phone Time
	format(datestring, sizeof datestring, "%s%d:%s%d", (hours < 10) ? ("0") : (""), hours, (minutes < 10) ? ("0") : (""), minutes);
	TextDrawSetString(PhoneTD[13], datestring);
	return 1;
}
	
hook main(){
	SetTimer("onlineTimer", 1000, true);
}

hook OnGameModeInit()
{
	CreatePhoneTD();
	return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	// PHONE  TEXTDRAWS
	if(clickedid == calltd) 
	{
		if(pData[playerid][pPhoneStatus] == 0) 
		{
			return Error(playerid, "Handphone anda sedang dimatikan");
		}
		
		Dialog_Show(playerid, PhoneDialNumber, DIALOG_STYLE_INPUT, "Dial Number", "Please enter the number that you wish to dial below:", "Dial", "Back");
	}
	if(clickedid == mesaagetd) 
	{
		if(pData[playerid][pPhoneStatus] == 0) 
		{
			return Error(playerid, "Handphone anda sedang dimatikan");
		}

		Dialog_Show(playerid, PhoneSendSMS, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Dial", "Back");
	}
	if(clickedid == banktd) 
	{
		if(pData[playerid][pPhoneStatus] == 0) 
		{
			return Error(playerid, "Handphone anda sedang dimatikan");
		}
		if(pData[playerid][pVip])
		{
			return Dialog_Show(playerid, IBank, DIALOG_STYLE_LIST, "{6688FF}I-Bank", "Check Balance\nTransfer Money\nSign Paycheck", "Select", "Cancel");
		}

		Dialog_Show(playerid, IBank, DIALOG_STYLE_LIST, "{6688FF}I-Bank", "Check Balance\nTransfer Money", "Select", "Cancel");
 		/*for(new i = 0; i < 5; i++) {
			TextDrawShowForPlayer(playerid, PhoneAtmTD[i]);
		}
		PlayerTextDrawShow(playerid, PhoneAtmPlayer[playerid]);
		TextDrawShowForPlayer(playerid, PhoneAtmTransfer);
		TextDrawShowForPlayer(playerid, PhoneAtmExit);
		SelectTextDraw(playerid, COLOR_LIGHTBLUE);*/
	}
	if(clickedid == contactstd) 
	{
		if (pData[playerid][pPhoneStatus] == 0)
			return Error(playerid, "Your phone must be powered on.");

		if(pData[playerid][pPhoneBook] == 0)
			return Error(playerid, "You dont have a phone book.");

		ShowContacts(playerid);
	}
	if(clickedid == twittertd) 
	{
		new notif[20];
		if(pData[playerid][pTwitterStatus] == 1)
		{
			notif = "{ff0000}OFF";
		}
		else
		{
			notif = "{3BBD44}ON";
		}

		if(pData[playerid][pPhoneStatus] == 0) 
		{
			return Error(playerid, "Handphone anda sedang dimatikan");
		}
		if(pData[playerid][pTwitter] < 1)
		{	
			return Error(playerid, "Anda belum memiliki Twitter, harap download!");
		}

		/*new string[100];
		format(string, sizeof(string), "Tweet\nChangename Twitter({0099ff}%s{ffffff})\nNotification: {ff0000}MAINTENANCE", pData[playerid][pTwittername]);
		//format(string, sizeof(string), "Tweet\nChangename Twitter({0099ff}%s{ffffff})\nNotification: %s", pData[playerid][pTwittername], notif);
		ShowPlayerDialog(playerid, DIALOG_TWITTER, DIALOG_STYLE_LIST, "Twitter", string, "Select", "Close");*/
		Error(playerid, "Untuk saat ini Twitter tidak dapat digunakan!");
	}
	if(clickedid == apptd) 
	{
		if(pData[playerid][pPhoneStatus] == 0) 
		{
			return Error(playerid, "Handphone anda sedang dimatikan");
		}

		new string[512];
		format(string, sizeof(string),"App Store\nIsi Kuota");
		Dialog_Show(playerid, IsiKuota, DIALOG_STYLE_LIST,"Phone",string,"Pilih","Batal");

		//pData[playerid][pMusicType] = MUSIC_MP3PLAYER;
		//ShowDialogToPlayer(playerid, DIALOG_MP3PLAYER);
	}
	if(clickedid == phoneclosetd) 
	{
 		for(new i = 0; i < 33; i++) {
			TextDrawHideForPlayer(playerid, PhoneTD[i]);
		}
		TextDrawHideForPlayer(playerid, phoneclosetd);
		TextDrawHideForPlayer(playerid, banktd);
		TextDrawHideForPlayer(playerid, mesaagetd);
		TextDrawHideForPlayer(playerid, calltd);
		TextDrawHideForPlayer(playerid, contactstd);
		TextDrawHideForPlayer(playerid, phoneclosetd);
		TextDrawHideForPlayer(playerid, apptd);
		TextDrawHideForPlayer(playerid, twittertd);
		TextDrawHideForPlayer(playerid, gpstd);
		TextDrawHideForPlayer(playerid, settingtd);
		TextDrawHideForPlayer(playerid, cameratd);
		CancelSelectTextDraw(playerid);
	}
	if(clickedid == settingtd)
	{
		Dialog_Show(playerid, TogglePhone, DIALOG_STYLE_LIST, "Setting", "Phone On\nPhone Off", "Select", "Back");
	}
	if(clickedid == cameratd)
	{
		callcmd::selfie(playerid, "");
	}
	if(clickedid == gpstd)
	{
		if(pData[playerid][pPhoneStatus] == 0) 
		{
			return Error(playerid, "Handphone anda sedang dimatikan");
		}
		callcmd::gps(playerid, "");
	}
	return 1;
}

CreatePhoneTD()
{
	//------------[ Phone Textdraws IndoGreat ]
	PhoneTD[0] = TextDrawCreate(512.000000, 111.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[0], 4);
	TextDrawLetterSize(PhoneTD[0], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[0], 25.000000, 25.000000);
	TextDrawSetOutline(PhoneTD[0], 1);
	TextDrawSetShadow(PhoneTD[0], 0);
	TextDrawAlignment(PhoneTD[0], 1);
	TextDrawColor(PhoneTD[0], 255);
	TextDrawBackgroundColor(PhoneTD[0], 255);
	TextDrawBoxColor(PhoneTD[0], 50);
	TextDrawUseBox(PhoneTD[0], 1);
	TextDrawSetProportional(PhoneTD[0], 1);
	TextDrawSetSelectable(PhoneTD[0], 0);

	PhoneTD[1] = TextDrawCreate(410.000000, 111.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[1], 4);
	TextDrawLetterSize(PhoneTD[1], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[1], 25.000000, 25.000000);
	TextDrawSetOutline(PhoneTD[1], 1);
	TextDrawSetShadow(PhoneTD[1], 0);
	TextDrawAlignment(PhoneTD[1], 1);
	TextDrawColor(PhoneTD[1], 255);
	TextDrawBackgroundColor(PhoneTD[1], 255);
	TextDrawBoxColor(PhoneTD[1], 50);
	TextDrawUseBox(PhoneTD[1], 1);
	TextDrawSetProportional(PhoneTD[1], 1);
	TextDrawSetSelectable(PhoneTD[1], 0);

	PhoneTD[2] = TextDrawCreate(410.000000, 321.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[2], 4);
	TextDrawLetterSize(PhoneTD[2], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[2], 25.000000, 25.000000);
	TextDrawSetOutline(PhoneTD[2], 1);
	TextDrawSetShadow(PhoneTD[2], 0);
	TextDrawAlignment(PhoneTD[2], 1);
	TextDrawColor(PhoneTD[2], 255);
	TextDrawBackgroundColor(PhoneTD[2], 255);
	TextDrawBoxColor(PhoneTD[2], 50);
	TextDrawUseBox(PhoneTD[2], 1);
	TextDrawSetProportional(PhoneTD[2], 1);
	TextDrawSetSelectable(PhoneTD[2], 0);

	PhoneTD[3] = TextDrawCreate(512.000000, 321.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[3], 4);
	TextDrawLetterSize(PhoneTD[3], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[3], 25.000000, 25.000000);
	TextDrawSetOutline(PhoneTD[3], 1);
	TextDrawSetShadow(PhoneTD[3], 0);
	TextDrawAlignment(PhoneTD[3], 1);
	TextDrawColor(PhoneTD[3], 255);
	TextDrawBackgroundColor(PhoneTD[3], 255);
	TextDrawBoxColor(PhoneTD[3], 50);
	TextDrawUseBox(PhoneTD[3], 1);
	TextDrawSetProportional(PhoneTD[3], 1);
	TextDrawSetSelectable(PhoneTD[3], 0);

	PhoneTD[4] = TextDrawCreate(473.000000, 117.500000, "_");
	TextDrawFont(PhoneTD[4], 1);
	TextDrawLetterSize(PhoneTD[4], 0.554166, 24.650011);
	TextDrawTextSize(PhoneTD[4], 261.000000, 101.500000);
	TextDrawSetOutline(PhoneTD[4], 1);
	TextDrawSetShadow(PhoneTD[4], 0);
	TextDrawAlignment(PhoneTD[4], 2);
	TextDrawColor(PhoneTD[4], -1);
	TextDrawBackgroundColor(PhoneTD[4], 255);
	TextDrawBoxColor(PhoneTD[4], 255);
	TextDrawUseBox(PhoneTD[4], 1);
	TextDrawSetProportional(PhoneTD[4], 1);
	TextDrawSetSelectable(PhoneTD[4], 0);

	PhoneTD[5] = TextDrawCreate(473.500000, 123.500000, "_");
	TextDrawFont(PhoneTD[5], 1);
	TextDrawLetterSize(PhoneTD[5], 0.554166, 23.050035);
	TextDrawTextSize(PhoneTD[5], 252.500000, 114.500000);
	TextDrawSetOutline(PhoneTD[5], 1);
	TextDrawSetShadow(PhoneTD[5], 0);
	TextDrawAlignment(PhoneTD[5], 2);
	TextDrawColor(PhoneTD[5], -1);
	TextDrawBackgroundColor(PhoneTD[5], 255);
	TextDrawBoxColor(PhoneTD[5], 255);
	TextDrawUseBox(PhoneTD[5], 1);
	TextDrawSetProportional(PhoneTD[5], 1);
	TextDrawSetSelectable(PhoneTD[5], 0);

	PhoneTD[6] = TextDrawCreate(419.000000, 318.000000, "ld_dual:backgnd");
	TextDrawFont(PhoneTD[6], 4);
	TextDrawLetterSize(PhoneTD[6], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[6], 109.500000, -198.000000);
	TextDrawSetOutline(PhoneTD[6], 1);
	TextDrawSetShadow(PhoneTD[6], 0);
	TextDrawAlignment(PhoneTD[6], 1);
	TextDrawColor(PhoneTD[6], -1);
	TextDrawBackgroundColor(PhoneTD[6], 255);
	TextDrawBoxColor(PhoneTD[6], 50);
	TextDrawUseBox(PhoneTD[6], 1);
	TextDrawSetProportional(PhoneTD[6], 1);
	TextDrawSetSelectable(PhoneTD[6], 0);

	PhoneTD[7] = TextDrawCreate(473.500000, 120.500000, "_");
	TextDrawFont(PhoneTD[7], 1);
	TextDrawLetterSize(PhoneTD[7], 0.554166, 1.700037);
	TextDrawTextSize(PhoneTD[7], 252.500000, 105.000000);
	TextDrawSetOutline(PhoneTD[7], 1);
	TextDrawSetShadow(PhoneTD[7], 0);
	TextDrawAlignment(PhoneTD[7], 2);
	TextDrawColor(PhoneTD[7], -1);
	TextDrawBackgroundColor(PhoneTD[7], 255);
	TextDrawBoxColor(PhoneTD[7], 255);
	TextDrawUseBox(PhoneTD[7], 1);
	TextDrawSetProportional(PhoneTD[7], 1);
	TextDrawSetSelectable(PhoneTD[7], 0);

	PhoneTD[8] = TextDrawCreate(474.000000, 123.000000, "_");
	TextDrawFont(PhoneTD[8], 1);
	TextDrawLetterSize(PhoneTD[8], 0.600000, -0.199993);
	TextDrawTextSize(PhoneTD[8], 326.000000, 21.000000);
	TextDrawSetOutline(PhoneTD[8], 1);
	TextDrawSetShadow(PhoneTD[8], 0);
	TextDrawAlignment(PhoneTD[8], 2);
	TextDrawColor(PhoneTD[8], -1);
	TextDrawBackgroundColor(PhoneTD[8], 255);
	TextDrawBoxColor(PhoneTD[8], -1);
	TextDrawUseBox(PhoneTD[8], 1);
	TextDrawSetProportional(PhoneTD[8], 1);
	TextDrawSetSelectable(PhoneTD[8], 0);

	PhoneTD[9] = TextDrawCreate(512.000000, 321.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[9], 4);
	TextDrawLetterSize(PhoneTD[9], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[9], 25.000000, 25.000000);
	TextDrawSetOutline(PhoneTD[9], 1);
	TextDrawSetShadow(PhoneTD[9], 0);
	TextDrawAlignment(PhoneTD[9], 1);
	TextDrawColor(PhoneTD[9], 255);
	TextDrawBackgroundColor(PhoneTD[9], 255);
	TextDrawBoxColor(PhoneTD[9], 50);
	TextDrawUseBox(PhoneTD[9], 1);
	TextDrawSetProportional(PhoneTD[9], 1);
	TextDrawSetSelectable(PhoneTD[9], 0);

	PhoneTD[10] = TextDrawCreate(480.000000, 119.500000, "ld_beat:chit");
	TextDrawFont(PhoneTD[10], 4);
	TextDrawLetterSize(PhoneTD[10], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[10], 10.000000, 5.000000);
	TextDrawSetOutline(PhoneTD[10], 1);
	TextDrawSetShadow(PhoneTD[10], 0);
	TextDrawAlignment(PhoneTD[10], 1);
	TextDrawColor(PhoneTD[10], -1);
	TextDrawBackgroundColor(PhoneTD[10], 255);
	TextDrawBoxColor(PhoneTD[10], 50);
	TextDrawUseBox(PhoneTD[10], 1);
	TextDrawSetProportional(PhoneTD[10], 1);
	TextDrawSetSelectable(PhoneTD[10], 0);

	PhoneTD[11] = TextDrawCreate(457.000000, 119.500000, "ld_beat:chit");
	TextDrawFont(PhoneTD[11], 4);
	TextDrawLetterSize(PhoneTD[11], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[11], 10.000000, 5.000000);
	TextDrawSetOutline(PhoneTD[11], 1);
	TextDrawSetShadow(PhoneTD[11], 0);
	TextDrawAlignment(PhoneTD[11], 1);
	TextDrawColor(PhoneTD[11], -1);
	TextDrawBackgroundColor(PhoneTD[11], 255);
	TextDrawBoxColor(PhoneTD[11], 50);
	TextDrawUseBox(PhoneTD[11], 1);
	TextDrawSetProportional(PhoneTD[11], 1);
	TextDrawSetSelectable(PhoneTD[11], 0);

	PhoneTD[12] = TextDrawCreate(452.000000, 119.500000, "ld_beat:chit");
	TextDrawFont(PhoneTD[12], 4);
	TextDrawLetterSize(PhoneTD[12], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[12], 5.000000, 5.000000);
	TextDrawSetOutline(PhoneTD[12], 1);
	TextDrawSetShadow(PhoneTD[12], 0);
	TextDrawAlignment(PhoneTD[12], 1);
	TextDrawColor(PhoneTD[12], -1);
	TextDrawBackgroundColor(PhoneTD[12], 255);
	TextDrawBoxColor(PhoneTD[12], 50);
	TextDrawUseBox(PhoneTD[12], 1);
	TextDrawSetProportional(PhoneTD[12], 1);
	TextDrawSetSelectable(PhoneTD[12], 0);

	PhoneTD[13] = TextDrawCreate(422.000000, 138.000000, "00:00");
	TextDrawFont(PhoneTD[13], 3);
	TextDrawLetterSize(PhoneTD[13], 0.220833, 1.100000);
	TextDrawTextSize(PhoneTD[13], 550.000000, 17.000000);
	TextDrawSetOutline(PhoneTD[13], 1);
	TextDrawSetShadow(PhoneTD[13], 0);
	TextDrawAlignment(PhoneTD[13], 1);
	TextDrawColor(PhoneTD[13], -1);
	TextDrawBackgroundColor(PhoneTD[13], 255);
	TextDrawBoxColor(PhoneTD[13], 50);
	TextDrawUseBox(PhoneTD[13], 0);
	TextDrawSetProportional(PhoneTD[13], 1);
	TextDrawSetSelectable(PhoneTD[13], 0);

	PhoneTD[14] = TextDrawCreate(416.000000, 151.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[14], 4);
	TextDrawLetterSize(PhoneTD[14], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[14], 40.000000, 40.000000);
	TextDrawSetOutline(PhoneTD[14], 1);
	TextDrawSetShadow(PhoneTD[14], 0);
	TextDrawAlignment(PhoneTD[14], 1);
	TextDrawColor(PhoneTD[14], 1687547391);
	TextDrawBackgroundColor(PhoneTD[14], 1097458175);
	TextDrawBoxColor(PhoneTD[14], 1687547186);
	TextDrawUseBox(PhoneTD[14], 1);
	TextDrawSetProportional(PhoneTD[14], 1);
	TextDrawSetSelectable(PhoneTD[14], 0);

	PhoneTD[15] = TextDrawCreate(454.000000, 151.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[15], 4);
	TextDrawLetterSize(PhoneTD[15], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[15], 40.000000, 40.000000);
	TextDrawSetOutline(PhoneTD[15], 1);
	TextDrawSetShadow(PhoneTD[15], 0);
	TextDrawAlignment(PhoneTD[15], 1);
	TextDrawColor(PhoneTD[15], -65281);
	TextDrawBackgroundColor(PhoneTD[15], 255);
	TextDrawBoxColor(PhoneTD[15], 50);
	TextDrawUseBox(PhoneTD[15], 1);
	TextDrawSetProportional(PhoneTD[15], 1);
	TextDrawSetSelectable(PhoneTD[15], 0);

	PhoneTD[16] = TextDrawCreate(491.000000, 151.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[16], 4);
	TextDrawLetterSize(PhoneTD[16], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[16], 40.000000, 40.000000);
	TextDrawSetOutline(PhoneTD[16], 1);
	TextDrawSetShadow(PhoneTD[16], 0);
	TextDrawAlignment(PhoneTD[16], 1);
	TextDrawColor(PhoneTD[16], 1296911871);
	TextDrawBackgroundColor(PhoneTD[16], 255);
	TextDrawBoxColor(PhoneTD[16], -16777166);
	TextDrawUseBox(PhoneTD[16], 1);
	TextDrawSetProportional(PhoneTD[16], 1);
	TextDrawSetSelectable(PhoneTD[16], 0);

	PhoneTD[17] = TextDrawCreate(491.000000, 193.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[17], 4);
	TextDrawLetterSize(PhoneTD[17], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[17], 40.000000, 40.000000);
	TextDrawSetOutline(PhoneTD[17], 1);
	TextDrawSetShadow(PhoneTD[17], 0);
	TextDrawAlignment(PhoneTD[17], 1);
	TextDrawColor(PhoneTD[17], -16776961);
	TextDrawBackgroundColor(PhoneTD[17], 255);
	TextDrawBoxColor(PhoneTD[17], -16777166);
	TextDrawUseBox(PhoneTD[17], 1);
	TextDrawSetProportional(PhoneTD[17], 1);
	TextDrawSetSelectable(PhoneTD[17], 0);

	PhoneTD[18] = TextDrawCreate(491.000000, 238.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[18], 4);
	TextDrawLetterSize(PhoneTD[18], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[18], 40.000000, 40.000000);
	TextDrawSetOutline(PhoneTD[18], 1);
	TextDrawSetShadow(PhoneTD[18], 0);
	TextDrawAlignment(PhoneTD[18], 1);
	TextDrawColor(PhoneTD[18], 9145343);
	TextDrawBackgroundColor(PhoneTD[18], 255);
	TextDrawBoxColor(PhoneTD[18], -16777166);
	TextDrawUseBox(PhoneTD[18], 1);
	TextDrawSetProportional(PhoneTD[18], 1);
	TextDrawSetSelectable(PhoneTD[18], 0);

	PhoneTD[19] = TextDrawCreate(416.000000, 193.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[19], 4);
	TextDrawLetterSize(PhoneTD[19], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[19], 40.000000, 40.000000);
	TextDrawSetOutline(PhoneTD[19], 1);
	TextDrawSetShadow(PhoneTD[19], 0);
	TextDrawAlignment(PhoneTD[19], 1);
	TextDrawColor(PhoneTD[19], -1);
	TextDrawBackgroundColor(PhoneTD[19], 1097458175);
	TextDrawBoxColor(PhoneTD[19], 1687547186);
	TextDrawUseBox(PhoneTD[19], 1);
	TextDrawSetProportional(PhoneTD[19], 1);
	TextDrawSetSelectable(PhoneTD[19], 0);

	PhoneTD[20] = TextDrawCreate(416.000000, 238.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[20], 4);
	TextDrawLetterSize(PhoneTD[20], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[20], 40.000000, 40.000000);
	TextDrawSetOutline(PhoneTD[20], 1);
	TextDrawSetShadow(PhoneTD[20], 0);
	TextDrawAlignment(PhoneTD[20], 1);
	TextDrawColor(PhoneTD[20], 65535);
	TextDrawBackgroundColor(PhoneTD[20], 1097458175);
	TextDrawBoxColor(PhoneTD[20], 1687547186);
	TextDrawUseBox(PhoneTD[20], 1);
	TextDrawSetProportional(PhoneTD[20], 1);
	TextDrawSetSelectable(PhoneTD[20], 0);

	PhoneTD[21] = TextDrawCreate(454.000000, 193.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[21], 4);
	TextDrawLetterSize(PhoneTD[21], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[21], 40.000000, 40.000000);
	TextDrawSetOutline(PhoneTD[21], 1);
	TextDrawSetShadow(PhoneTD[21], 0);
	TextDrawAlignment(PhoneTD[21], 1);
	TextDrawColor(PhoneTD[21], 1433087999);
	TextDrawBackgroundColor(PhoneTD[21], 255);
	TextDrawBoxColor(PhoneTD[21], 50);
	TextDrawUseBox(PhoneTD[21], 1);
	TextDrawSetProportional(PhoneTD[21], 1);
	TextDrawSetSelectable(PhoneTD[21], 0);

	PhoneTD[22] = TextDrawCreate(454.000000, 238.000000, "ld_beat:chit");
	TextDrawFont(PhoneTD[22], 4);
	TextDrawLetterSize(PhoneTD[22], 0.600000, 2.000000);
	TextDrawTextSize(PhoneTD[22], 40.000000, 40.000000);
	TextDrawSetOutline(PhoneTD[22], 1);
	TextDrawSetShadow(PhoneTD[22], 0);
	TextDrawAlignment(PhoneTD[22], 1);
	TextDrawColor(PhoneTD[22], -1962934017);
	TextDrawBackgroundColor(PhoneTD[22], 255);
	TextDrawBoxColor(PhoneTD[22], 50);
	TextDrawUseBox(PhoneTD[22], 1);
	TextDrawSetProportional(PhoneTD[22], 1);
	TextDrawSetSelectable(PhoneTD[22], 0);

	PhoneTD[23] = TextDrawCreate(428.000000, 186.000000, "SMS");
	TextDrawFont(PhoneTD[23], 1);
	TextDrawLetterSize(PhoneTD[23], 0.224998, 1.000000);
	TextDrawTextSize(PhoneTD[23], 555.500000, 17.000000);
	TextDrawSetOutline(PhoneTD[23], 1);
	TextDrawSetShadow(PhoneTD[23], 0);
	TextDrawAlignment(PhoneTD[23], 1);
	TextDrawColor(PhoneTD[23], -1);
	TextDrawBackgroundColor(PhoneTD[23], 255);
	TextDrawBoxColor(PhoneTD[23], 50);
	TextDrawUseBox(PhoneTD[23], 0);
	TextDrawSetProportional(PhoneTD[23], 1);
	TextDrawSetSelectable(PhoneTD[23], 0);

	PhoneTD[24] = TextDrawCreate(458.000000, 186.000000, "CONTACT");
	TextDrawFont(PhoneTD[24], 1);
	TextDrawLetterSize(PhoneTD[24], 0.224998, 1.000000);
	TextDrawTextSize(PhoneTD[24], 555.500000, 17.000000);
	TextDrawSetOutline(PhoneTD[24], 1);
	TextDrawSetShadow(PhoneTD[24], 0);
	TextDrawAlignment(PhoneTD[24], 1);
	TextDrawColor(PhoneTD[24], -1);
	TextDrawBackgroundColor(PhoneTD[24], 255);
	TextDrawBoxColor(PhoneTD[24], 50);
	TextDrawUseBox(PhoneTD[24], 0);
	TextDrawSetProportional(PhoneTD[24], 1);
	TextDrawSetSelectable(PhoneTD[24], 0);

	PhoneTD[25] = TextDrawCreate(502.000000, 186.000000, "CALL");
	TextDrawFont(PhoneTD[25], 1);
	TextDrawLetterSize(PhoneTD[25], 0.224998, 1.000000);
	TextDrawTextSize(PhoneTD[25], 555.500000, 17.000000);
	TextDrawSetOutline(PhoneTD[25], 1);
	TextDrawSetShadow(PhoneTD[25], 0);
	TextDrawAlignment(PhoneTD[25], 1);
	TextDrawColor(PhoneTD[25], -1);
	TextDrawBackgroundColor(PhoneTD[25], 255);
	TextDrawBoxColor(PhoneTD[25], 50);
	TextDrawUseBox(PhoneTD[25], 0);
	TextDrawSetProportional(PhoneTD[25], 1);
	TextDrawSetSelectable(PhoneTD[25], 0);

	PhoneTD[26] = TextDrawCreate(497.000000, 227.000000, "SETTING");
	TextDrawFont(PhoneTD[26], 1);
	TextDrawLetterSize(PhoneTD[26], 0.224998, 1.000000);
	TextDrawTextSize(PhoneTD[26], 555.500000, 17.000000);
	TextDrawSetOutline(PhoneTD[26], 1);
	TextDrawSetShadow(PhoneTD[26], 0);
	TextDrawAlignment(PhoneTD[26], 1);
	TextDrawColor(PhoneTD[26], -1);
	TextDrawBackgroundColor(PhoneTD[26], 255);
	TextDrawBoxColor(PhoneTD[26], 50);
	TextDrawUseBox(PhoneTD[26], 0);
	TextDrawSetProportional(PhoneTD[26], 1);
	TextDrawSetSelectable(PhoneTD[26], 0);

	PhoneTD[27] = TextDrawCreate(497.000000, 272.000000, "CAMERA");
	TextDrawFont(PhoneTD[27], 1);
	TextDrawLetterSize(PhoneTD[27], 0.224998, 1.000000);
	TextDrawTextSize(PhoneTD[27], 555.500000, 17.000000);
	TextDrawSetOutline(PhoneTD[27], 1);
	TextDrawSetShadow(PhoneTD[27], 0);
	TextDrawAlignment(PhoneTD[27], 1);
	TextDrawColor(PhoneTD[27], -1);
	TextDrawBackgroundColor(PhoneTD[27], 255);
	TextDrawBoxColor(PhoneTD[27], 50);
	TextDrawUseBox(PhoneTD[27], 0);
	TextDrawSetProportional(PhoneTD[27], 1);
	TextDrawSetSelectable(PhoneTD[27], 0);

	PhoneTD[28] = TextDrawCreate(423.000000, 227.000000, "I-BANK");
	TextDrawFont(PhoneTD[28], 1);
	TextDrawLetterSize(PhoneTD[28], 0.224998, 1.000000);
	TextDrawTextSize(PhoneTD[28], 555.500000, 17.000000);
	TextDrawSetOutline(PhoneTD[28], 1);
	TextDrawSetShadow(PhoneTD[28], 0);
	TextDrawAlignment(PhoneTD[28], 1);
	TextDrawColor(PhoneTD[28], -1);
	TextDrawBackgroundColor(PhoneTD[28], 255);
	TextDrawBoxColor(PhoneTD[28], 50);
	TextDrawUseBox(PhoneTD[28], 0);
	TextDrawSetProportional(PhoneTD[28], 1);
	TextDrawSetSelectable(PhoneTD[28], 0);

	PhoneTD[29] = TextDrawCreate(421.000000, 272.000000, "TWITTER");
	TextDrawFont(PhoneTD[29], 1);
	TextDrawLetterSize(PhoneTD[29], 0.224998, 1.000000);
	TextDrawTextSize(PhoneTD[29], 555.500000, 17.000000);
	TextDrawSetOutline(PhoneTD[29], 1);
	TextDrawSetShadow(PhoneTD[29], 0);
	TextDrawAlignment(PhoneTD[29], 1);
	TextDrawColor(PhoneTD[29], -1);
	TextDrawBackgroundColor(PhoneTD[29], 255);
	TextDrawBoxColor(PhoneTD[29], 50);
	TextDrawUseBox(PhoneTD[29], 0);
	TextDrawSetProportional(PhoneTD[29], 1);
	TextDrawSetSelectable(PhoneTD[29], 0);

	PhoneTD[30] = TextDrawCreate(467.000000, 227.000000, "GPS");
	TextDrawFont(PhoneTD[30], 1);
	TextDrawLetterSize(PhoneTD[30], 0.224998, 1.000000);
	TextDrawTextSize(PhoneTD[30], 555.500000, 17.000000);
	TextDrawSetOutline(PhoneTD[30], 1);
	TextDrawSetShadow(PhoneTD[30], 0);
	TextDrawAlignment(PhoneTD[30], 1);
	TextDrawColor(PhoneTD[30], -1);
	TextDrawBackgroundColor(PhoneTD[30], 255);
	TextDrawBoxColor(PhoneTD[30], 50);
	TextDrawUseBox(PhoneTD[30], 0);
	TextDrawSetProportional(PhoneTD[30], 1);
	TextDrawSetSelectable(PhoneTD[30], 0);

	PhoneTD[31] = TextDrawCreate(462.000000, 272.000000, "APP");
	TextDrawFont(PhoneTD[31], 1);
	TextDrawLetterSize(PhoneTD[31], 0.224997, 1.000000);
	TextDrawTextSize(PhoneTD[31], 555.500000, 17.000000);
	TextDrawSetOutline(PhoneTD[31], 1);
	TextDrawSetShadow(PhoneTD[31], 0);
	TextDrawAlignment(PhoneTD[31], 1);
	TextDrawColor(PhoneTD[31], -1);
	TextDrawBackgroundColor(PhoneTD[31], 255);
	TextDrawBoxColor(PhoneTD[31], 50);
	TextDrawUseBox(PhoneTD[31], 0);
	TextDrawSetProportional(PhoneTD[31], 1);
	TextDrawSetSelectable(PhoneTD[31], 0);


	phoneclosetd = TextDrawCreate(459.000000, 316.500000, "ld_beat:chit");//close
	TextDrawFont(phoneclosetd, 4);
	TextDrawLetterSize(phoneclosetd, 0.600000, 2.000000);
	TextDrawTextSize(phoneclosetd, 27.000000, 27.000000);
	TextDrawSetOutline(phoneclosetd, 1);
	TextDrawSetShadow(phoneclosetd, 0);
	TextDrawAlignment(phoneclosetd, 1);
	TextDrawColor(phoneclosetd, -1);
	TextDrawBackgroundColor(phoneclosetd, 255);
	TextDrawBoxColor(phoneclosetd, 50);
	TextDrawUseBox(phoneclosetd, 1);
	TextDrawSetProportional(phoneclosetd, 1);
	TextDrawSetSelectable(phoneclosetd, 1);

	mesaagetd = TextDrawCreate(429.000000, 163.000000, "ld_chat:goodcha");
	TextDrawFont(mesaagetd, 4);
	TextDrawLetterSize(mesaagetd, 0.600000, 2.000000);
	TextDrawTextSize(mesaagetd, 14.000000, 14.000000);
	TextDrawSetOutline(mesaagetd, 1);
	TextDrawSetShadow(mesaagetd, 0);
	TextDrawAlignment(mesaagetd, 1);
	TextDrawColor(mesaagetd, -1);
	TextDrawBackgroundColor(mesaagetd, 255);
	TextDrawBoxColor(mesaagetd, 50);
	TextDrawUseBox(mesaagetd, 1);
	TextDrawSetProportional(mesaagetd, 1);
	TextDrawSetSelectable(mesaagetd, 1);

	contactstd = TextDrawCreate(467.000000, 163.000000, "ld_chat:badchat");
	TextDrawFont(contactstd, 4);
	TextDrawLetterSize(contactstd, 0.600000, 2.000000);
	TextDrawTextSize(contactstd, 14.000000, 14.000000);
	TextDrawSetOutline(contactstd, 1);
	TextDrawSetShadow(contactstd, 0);
	TextDrawAlignment(contactstd, 1);
	TextDrawColor(contactstd, -1);
	TextDrawBackgroundColor(contactstd, 255);
	TextDrawBoxColor(contactstd, 50);
	TextDrawUseBox(contactstd, 1);
	TextDrawSetProportional(contactstd, 1);
	TextDrawSetSelectable(contactstd, 1);

	cameratd = TextDrawCreate(504.000000, 251.000000, "ld_grav:flwr");
	TextDrawFont(cameratd, 4);
	TextDrawLetterSize(cameratd, 0.600000, 2.000000);
	TextDrawTextSize(cameratd, 14.000000, 14.000000);
	TextDrawSetOutline(cameratd, 1);
	TextDrawSetShadow(cameratd, 0);
	TextDrawAlignment(cameratd, 1);
	TextDrawColor(cameratd, -1);
	TextDrawBackgroundColor(cameratd, 255);
	TextDrawBoxColor(cameratd, 50);
	TextDrawUseBox(cameratd, 1);
	TextDrawSetProportional(cameratd, 1);
	TextDrawSetSelectable(cameratd, 1);

	banktd = TextDrawCreate(429.000000, 205.000000, "HUD:radar_cash");
	TextDrawFont(banktd, 4);
	TextDrawLetterSize(banktd, 0.600000, 2.000000);
	TextDrawTextSize(banktd, 14.000000, 14.000000);
	TextDrawSetOutline(banktd, 1);
	TextDrawSetShadow(banktd, 0);
	TextDrawAlignment(banktd, 1);
	TextDrawColor(banktd, -1);
	TextDrawBackgroundColor(banktd, 255);
	TextDrawBoxColor(banktd, 50);
	TextDrawUseBox(banktd, 1);
	TextDrawSetProportional(banktd, 1);
	TextDrawSetSelectable(banktd, 1);

	settingtd = TextDrawCreate(504.000000, 205.000000, "HUD:radar_waypoint");
	TextDrawFont(settingtd, 4);
	TextDrawLetterSize(settingtd, 0.600000, 2.000000);
	TextDrawTextSize(settingtd, 14.000000, 14.000000);
	TextDrawSetOutline(settingtd, 1);
	TextDrawSetShadow(settingtd, 0);
	TextDrawAlignment(settingtd, 1);
	TextDrawColor(settingtd, -1);
	TextDrawBackgroundColor(settingtd, 255);
	TextDrawBoxColor(settingtd, 50);
	TextDrawUseBox(settingtd, 1);
	TextDrawSetProportional(settingtd, 1);
	TextDrawSetSelectable(settingtd, 1);

	twittertd = TextDrawCreate(431.000000, 249.000000, "T");
	TextDrawFont(twittertd, 1);
	TextDrawLetterSize(twittertd, 0.562500, 1.799998);
	TextDrawTextSize(twittertd, 441.000000, 49.000000);
	TextDrawSetOutline(twittertd, 1);
	TextDrawSetShadow(twittertd, 0);
	TextDrawAlignment(twittertd, 1);
	TextDrawColor(twittertd, -1);
	TextDrawBackgroundColor(twittertd, 255);
	TextDrawBoxColor(twittertd, 50);
	TextDrawUseBox(twittertd, 0);
	TextDrawSetProportional(twittertd, 1);
	TextDrawSetSelectable(twittertd, 1);

	gpstd = TextDrawCreate(467.000000, 203.000000, "G");
	TextDrawFont(gpstd, 1);
	TextDrawLetterSize(gpstd, 0.495833, 1.799998);
	TextDrawTextSize(gpstd, 480.500000, 52.500000);
	TextDrawSetOutline(gpstd, 1);
	TextDrawSetShadow(gpstd, 0);
	TextDrawAlignment(gpstd, 1);
	TextDrawColor(gpstd, -1);
	TextDrawBackgroundColor(gpstd, 255);
	TextDrawBoxColor(gpstd, 50);
	TextDrawUseBox(gpstd, 0);
	TextDrawSetProportional(gpstd, 1);
	TextDrawSetSelectable(gpstd, 1);

	calltd = TextDrawCreate(505.000000, 161.000000, "C");
	TextDrawFont(calltd, 1);
	TextDrawLetterSize(calltd, 0.495833, 1.799998);
	TextDrawTextSize(calltd, 516.000000, 17.000000);
	TextDrawSetOutline(calltd, 1);
	TextDrawSetShadow(calltd, 0);
	TextDrawAlignment(calltd, 1);
	TextDrawColor(calltd, -1);
	TextDrawBackgroundColor(calltd, 255);
	TextDrawBoxColor(calltd, 50);
	TextDrawUseBox(calltd, 0);
	TextDrawSetProportional(calltd, 1);
	TextDrawSetSelectable(calltd, 1);

	apptd = TextDrawCreate(467.000000, 249.000000, "HUD:radar_datedisco");
	TextDrawFont(apptd, 4);
	TextDrawLetterSize(apptd, 0.495833, 1.799998);
	TextDrawTextSize(apptd, 15.000000, 16.500000);
	TextDrawSetOutline(apptd, 1);
	TextDrawSetShadow(apptd, 0);
	TextDrawAlignment(apptd, 1);
	TextDrawColor(apptd, -1);
	TextDrawBackgroundColor(apptd, 255);
	TextDrawBoxColor(apptd, 50);
	TextDrawUseBox(apptd, 0);
	TextDrawSetProportional(apptd, 1);
	TextDrawSetSelectable(apptd, 1);
}

Dialog:TogglePhone(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				pData[playerid][pPhoneStatus] = 1;
				Servers(playerid, "Berhasil menyalakan Handphone");
				return 0;
			}
			case 1:
			{
				pData[playerid][pPhoneStatus] = 0;
				Servers(playerid, "Berhasil mematikan Handphone");
				return 0;
			}
		}
	}
	return 1;
}
Dialog:PhoneDialNumber(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new
			string[16];

		if (isnull(inputtext) || !IsNumeric(inputtext))
			return Dialog_Show(playerid, PhoneDialNumber, DIALOG_STYLE_INPUT, "Dial Number", "Please enter the number that you wish to dial below:", "Dial", "Back");

		format(string, 16, "%d", strval(inputtext));
		callcmd::call(playerid, string);
	}
	else 
	{
		//callcmd::phone(playerid);
	}
	return 1;
}
Dialog:IsiKuota(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch (listitem) 
		{
			case 0:
			{
				new string[512], twitter[64];
				if(pData[playerid][pTwitter] < 1)
				{
					twitter = ""RED_E"Pasang";
				}
				else
				{
					twitter = ""LG_E"Terinstall";
				}
				download[playerid] = 1;
				format(string, sizeof(string),"Aplikasi\tStatus\n{7fffd4}Twitter ( 38mb )\t%s", twitter);
				Dialog_Show(playerid, Download, DIALOG_STYLE_TABLIST_HEADERS, "App Store",string,"Download","Batal");
			}
			case 1:
			{
				new mstr[128];
				format(mstr, sizeof(mstr), "Kuota\tHarga Pulsa\n{ffffff}Kuota 512MB\t{7fff00}3\n{ffffff}Kuota 1GB\t{7fff00}6\n{ffffff}Kuota 2GB\t{7fff00}12\n");
				Dialog_Show(playerid, Kuota, DIALOG_STYLE_TABLIST_HEADERS, "Isi Kuota", mstr, "Buy", "Cancel");
			}
		}
	}
	return 1;
}
Dialog:Download(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				new sisa = pData[playerid][pKuota]/1000;
				if(pData[playerid][pKuota] <= 38000)
					return Error(playerid, "Kuota yang anda miliki tidak mencukup ( Sisa %dmb )", sisa);

				SetTimerEx("DownloadTwitter", 10000, false, "i", playerid);
				GameTextForPlayer(playerid, "Downloading...", 10000, 4);
			}
		}
	}
	else
	{
		Servers(playerid, "Berhasil membatalkan Download Twitter");
	}
	return 1;
}
Dialog:Kuota(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				if(pData[playerid][pPhoneCredit] < 3)
					return Error(playerid, "Pulsa anda tidak mencukupi");

				pData[playerid][pKuota] += 512000;
				pData[playerid][pPhoneCredit] -= 3;
				Servers(playerid, "Berhasil membeli Kuota 512mb");
			}
			case 1:
			{
				if(pData[playerid][pPhoneCredit] < 6)
					return Error(playerid, "Pulsa anda tidak mencukupi");

				pData[playerid][pKuota] += 1000000;
				pData[playerid][pPhoneCredit] -= 6;
				Servers(playerid, "Berhasil membeli Kuota 1gb");
			}
			case 2:
			{
				if(pData[playerid][pPhoneCredit] < 12)
					return Error(playerid, "Pulsa anda tidak mencukupi");

				pData[playerid][pKuota] += 2000000;
				pData[playerid][pPhoneCredit] -= 6;
				Servers(playerid, "Berhasil membeli Kuota 2gb");
			}
		}
	}
	return 1;
}
Dialog:PhoneSendSMS(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new ph = strval(inputtext);

		if (isnull(inputtext) || !IsNumeric(inputtext))
			return Dialog_Show(playerid, PhoneSendSMS, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Dial", "Back");

		foreach(new ii : Player)
		{
			if(pData[ii][pPhone] == ph)
			{
				if(ii == INVALID_PLAYER_ID || !IsPlayerConnected(ii))
					return Dialog_Show(playerid, PhoneSendSMS, DIALOG_STYLE_INPUT, "Send Text Message", "Error: That number is not online right now.\n\nPlease enter the number that you wish to send a text message to:", "Dial", "Back");

				Dialog_Show(playerid, PhoneTextSMS, DIALOG_STYLE_INPUT, "Text Message", "Please enter the message to send", "Send", "Back");
				pData[playerid][pContact] = ph;
			}
		}
	}
	else 
	{
		//callcmd::phone(playerid);
	}
	return 1;
}

Dialog:PhoneTextSMS(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		if (isnull(inputtext))
			return Dialog_Show(playerid, PhoneTextSMS, DIALOG_STYLE_INPUT, "Text Message", "Error: Please enter a message to send.", "Send", "Back");

		new targetid = pData[playerid][pContact];
		foreach(new ii : Player)
		{
			if(pData[ii][pPhone] == targetid)
			{
				SendClientMessageEx(playerid, COLOR_YELLOW, "[SMS to %d]"WHITE_E" %s", targetid, inputtext);
				SendClientMessageEx(ii, COLOR_YELLOW, "[SMS from %d]"WHITE_E" %s", pData[playerid][pPhone], inputtext);
				Info(ii, "Gunakan "LB_E"'@<text>' "WHITE_E"untuk membalas SMS!");
				PlayerPlaySound(ii, 6003, 0,0,0);
				pData[ii][pSMS] = pData[playerid][pPhone];

				pData[playerid][pPhoneCredit] -= 1;
			}
		}
	}
	else {
		Dialog_Show(playerid, PhoneSendSMS, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Submit", "Back");
	}
	return 1;
}
Dialog:IBank(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				new str[200];
				format(str, sizeof(str), "{F6F6F6}You have "LB_E"%s {F6F6F6}in your bank account.", FormatMoney(pData[playerid][pBankMoney]));
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""LB_E"I-Bank", str, "Close", "");
			}
			case 1:
			{
				ShowPlayerDialog(playerid, DIALOG_BANKREKENING, DIALOG_STYLE_INPUT, ""LB_E"Bank", "Masukan jumlah uang:", "Transfer", "Cancel");
			}
			case 2:
			{
				DisplayPaycheck(playerid);
			}
		}
	}
	return 1;
}

CMD:phone(playerid, params[])
{
	if(pData[playerid][pPhone] == 0) return Error(playerid, "Anda tidak memiliki Ponsel!");
	if(pData[playerid][pInjured] == 1) return Error(playerid, "Anda tidak bisa menggunakan Handphone saat terluka!");
	//if(pData[playerid][pPhoneStatus] == 0) return Error(playerid, "Handphone anda sedang dimatikan");

	for(new i = 0; i < 33; i++) {
		TextDrawShowForPlayer(playerid, PhoneTD[i]);
	}
	TextDrawShowForPlayer(playerid, banktd);
	TextDrawShowForPlayer(playerid, mesaagetd);
	TextDrawShowForPlayer(playerid, calltd);
	TextDrawShowForPlayer(playerid, contactstd);
	TextDrawShowForPlayer(playerid, phoneclosetd);
	TextDrawShowForPlayer(playerid, apptd);
	TextDrawShowForPlayer(playerid, twittertd);
	TextDrawShowForPlayer(playerid, gpstd);
	TextDrawShowForPlayer(playerid, settingtd);
	TextDrawShowForPlayer(playerid, cameratd);
	SelectTextDraw(playerid, COLOR_LBLUE);
	return 1;
}

forward DownloadTwitter(playerid);
public DownloadTwitter(playerid)
{
	pData[playerid][pTwitter] = 1;
	pData[playerid][pTwitterStatus] = 0;
	new query[128];
	mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET twitter='1', twitterstatus='0' WHERE reg_id=%d", pData[playerid][pID]);
	mysql_tquery(g_SQL, query);
	SendClientMessageEx(playerid, COLOR_ARWIN, "APP: {ffffff}Twitter berhasil diinstall!");
	return 1;
}

CMD:selfie(playerid,params[])
{
	if(takingselfie[playerid] == 0)
	{
	    GetPlayerPos(playerid,Selfielx[playerid],Selfiely[playerid],Selfielz[playerid]);
		static Float: n1X, Float: n1Y;
		if(SelfieDegree[playerid] >= 360) SelfieDegree[playerid] = 0;
		SelfieDegree[playerid] += SelfieSpeed;
		n1X = Selfielx[playerid] + SelfieRadius * floatcos(SelfieDegree[playerid], degrees);
		n1Y = Selfiely[playerid] + SelfieRadius * floatsin(SelfieDegree[playerid], degrees);
		SetPlayerCameraPos(playerid, n1X, n1Y, Selfielz[playerid] + SelfieHeight);
		SetPlayerCameraLookAt(playerid, Selfielx[playerid], Selfiely[playerid], Selfielz[playerid]+1);
		SetPlayerFacingAngle(playerid, SelfieDegree[playerid] - 90.0);
		takingselfie[playerid] = 1;
		ApplyAnimation(playerid, "PED", "gang_gunstand", 4.1, 1, 1, 1, 1, 1, 1);
		return 1;
	}
    if(takingselfie[playerid] == 1)
	{
	    TogglePlayerControllable(playerid,1);
		SetCameraBehindPlayer(playerid);
	    takingselfie[playerid] = 0;
	    ApplyAnimation(playerid, "PED", "ATM", 4.1, 0, 1, 1, 0, 1, 1);
	    return 1;
	}
    return 1;
}
