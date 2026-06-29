#include <YSI\y_hooks>

// Phone Textdraws
new Text:PhoneTD[51];

//-----[ Selfie System ]-----
new takingselfie[MAX_PLAYERS];
new Float:SelfieDegree[MAX_PLAYERS];
const Float: SelfieRadius = 1.4; //do not edit this
const Float: SelfieSpeed  = 1.25; //do not edit this
const Float: SelfieHeight = 1.0; // do not edit this
new Float:Selfielx[MAX_PLAYERS];
new Float:Selfiely[MAX_PLAYERS];
new Float:Selfielz[MAX_PLAYERS];


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
	TextDrawSetString(PhoneTD[14], datestring);
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
	// PHONE TEXTDRAWS
	if(clickedid == PhoneTD[15]) // CALL
	{
		if(pData[playerid][pPhoneStatus] == 0) 
			return Error(playerid, "Handphone anda sedang dimatikan");
		
		Dialog_Show(playerid, PhoneDialNumber, DIALOG_STYLE_INPUT, "Dial Number", "Please enter the number that you wish to dial below:", "Dial", "Back");
	}
	if(clickedid == PhoneTD[16]) // CONTACT
	{
		if (pData[playerid][pPhoneStatus] == 0)
			return Error(playerid, "Your phone must be powered on.");

		if(pData[playerid][pPhoneBook] == 0)
			return Error(playerid, "You dont have a phone book.");

		ShowContacts(playerid);
	}
	if(clickedid == PhoneTD[17]) // M-BANK
	{
		if(pData[playerid][pPhoneStatus] == 0) 
			return Error(playerid, "Handphone anda sedang dimatikan");
		if(pData[playerid][pVip])
			return Dialog_Show(playerid, IBank, DIALOG_STYLE_LIST, "{6688FF}I-Bank", "Check Balance\nTransfer Money\nSign Paycheck", "Select", "Cancel");

		Dialog_Show(playerid, IBank, DIALOG_STYLE_LIST, "{6688FF}I-Bank", "Check Balance\nTransfer Money", "Select", "Cancel");
	}
	if(clickedid == PhoneTD[18]) // GPS
	{
		if(pData[playerid][pPhoneStatus] == 0) 
			return Error(playerid, "Handphone anda sedang dimatikan");
		callcmd::gps(playerid, "");
	}
	if(clickedid == PhoneTD[19]) // SETTINGS
	{
		Dialog_Show(playerid, TogglePhone, DIALOG_STYLE_LIST, "Setting", "Phone On\nPhone Off", "Select", "Back");
	}
	if(clickedid == PhoneTD[20]) // VALLET
	{
		Info(playerid, "Vallet: Coming Soon!");
	}
	if(clickedid == PhoneTD[21]) // TWEET
	{
		if(pData[playerid][pPhoneStatus] == 0) 
			return Error(playerid, "Handphone anda sedang dimatikan");
		if(pData[playerid][pTwitter] < 1)
			return Error(playerid, "Anda belum memiliki Twitter, harap download!");

		Error(playerid, "Untuk saat ini Twitter tidak dapat digunakan!");
	}
	if(clickedid == PhoneTD[22]) // ADS
	{
		ShowAdvertisements(playerid);
	}
	if(clickedid == PhoneTD[23]) // CAMERA
	{
		callcmd::selfie(playerid, "");
	}
	if(clickedid == PhoneTD[24]) // SMS
	{
		if(pData[playerid][pPhoneStatus] == 0) 
			return Error(playerid, "Handphone anda sedang dimatikan");

		Dialog_Show(playerid, PhoneSendSMS, DIALOG_STYLE_INPUT, "Send Text Message", "Please enter the number that you wish to send a text message to:", "Dial", "Back");
	}
	if(clickedid == PhoneTD[12]) // CLOSE
	{
 		for(new i = 0; i < 51; i++) {
			TextDrawHideForPlayer(playerid, PhoneTD[i]);
		}
		CancelSelectTextDraw(playerid);
	}
	return 1;
}

CreatePhoneTD()
{
	PhoneTD[0] = TextDrawCreate(395.000, 138.000, "LD_BEAT:chit");
	TextDrawLetterSize(PhoneTD[0], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[0], 26.000, 32.000);
	TextDrawAlignment(PhoneTD[0], 1);
	TextDrawColor(PhoneTD[0], 1280134911);
	TextDrawUseBox(PhoneTD[0], 1);
	TextDrawBoxColor(PhoneTD[0], 50);
	TextDrawSetShadow(PhoneTD[0], 0);
	TextDrawSetOutline(PhoneTD[0], 1);
	TextDrawBackgroundColor(PhoneTD[0], 255);
	TextDrawFont(PhoneTD[0], 4);
	TextDrawSetProportional(PhoneTD[0], 1);

	PhoneTD[1] = TextDrawCreate(495.000, 138.000, "LD_BEAT:chit");
	TextDrawLetterSize(PhoneTD[1], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[1], 27.000, 29.000);
	TextDrawAlignment(PhoneTD[1], 1);
	TextDrawColor(PhoneTD[1], 1280134911);
	TextDrawUseBox(PhoneTD[1], 1);
	TextDrawBoxColor(PhoneTD[1], 50);
	TextDrawSetShadow(PhoneTD[1], 0);
	TextDrawSetOutline(PhoneTD[1], 1);
	TextDrawBackgroundColor(PhoneTD[1], 255);
	TextDrawFont(PhoneTD[1], 4);
	TextDrawSetProportional(PhoneTD[1], 1);

	PhoneTD[2] = TextDrawCreate(495.000, 388.000, "LD_BEAT:chit");
	TextDrawLetterSize(PhoneTD[2], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[2], 27.000, 29.000);
	TextDrawAlignment(PhoneTD[2], 1);
	TextDrawColor(PhoneTD[2], 1280134911);
	TextDrawUseBox(PhoneTD[2], 1);
	TextDrawBoxColor(PhoneTD[2], 50);
	TextDrawSetShadow(PhoneTD[2], 0);
	TextDrawSetOutline(PhoneTD[2], 1);
	TextDrawBackgroundColor(PhoneTD[2], 255);
	TextDrawFont(PhoneTD[2], 4);
	TextDrawSetProportional(PhoneTD[2], 1);

	PhoneTD[3] = TextDrawCreate(396.000, 388.000, "LD_BEAT:chit");
	TextDrawLetterSize(PhoneTD[3], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[3], 27.000, 29.000);
	TextDrawAlignment(PhoneTD[3], 1);
	TextDrawColor(PhoneTD[3], 1280134911);
	TextDrawUseBox(PhoneTD[3], 1);
	TextDrawBoxColor(PhoneTD[3], 50);
	TextDrawSetShadow(PhoneTD[3], 0);
	TextDrawSetOutline(PhoneTD[3], 1);
	TextDrawBackgroundColor(PhoneTD[3], 255);
	TextDrawFont(PhoneTD[3], 4);
	TextDrawSetProportional(PhoneTD[3], 1);

	PhoneTD[4] = TextDrawCreate(406.000, 143.000, "LD_BUM:blkdot");
	TextDrawLetterSize(PhoneTD[4], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[4], 105.000, 268.500);
	TextDrawAlignment(PhoneTD[4], 1);
	TextDrawColor(PhoneTD[4], 1280134911);
	TextDrawUseBox(PhoneTD[4], 1);
	TextDrawBoxColor(PhoneTD[4], 50);
	TextDrawSetShadow(PhoneTD[4], 0);
	TextDrawSetOutline(PhoneTD[4], 1);
	TextDrawBackgroundColor(PhoneTD[4], 255);
	TextDrawFont(PhoneTD[4], 4);
	TextDrawSetProportional(PhoneTD[4], 1);

	PhoneTD[5] = TextDrawCreate(400.000, 157.000, "LD_BUM:blkdot");
	TextDrawLetterSize(PhoneTD[5], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[5], 24.000, 247.500);
	TextDrawAlignment(PhoneTD[5], 1);
	TextDrawColor(PhoneTD[5], 1280134911);
	TextDrawUseBox(PhoneTD[5], 1);
	TextDrawBoxColor(PhoneTD[5], 50);
	TextDrawSetShadow(PhoneTD[5], 0);
	TextDrawSetOutline(PhoneTD[5], 1);
	TextDrawBackgroundColor(PhoneTD[5], 255);
	TextDrawFont(PhoneTD[5], 4);
	TextDrawSetProportional(PhoneTD[5], 1);

	PhoneTD[6] = TextDrawCreate(494.000, 153.000, "LD_BUM:blkdot");
	TextDrawLetterSize(PhoneTD[6], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[6], 24.000, 247.500);
	TextDrawAlignment(PhoneTD[6], 1);
	TextDrawColor(PhoneTD[6], 1280134911);
	TextDrawUseBox(PhoneTD[6], 1);
	TextDrawBoxColor(PhoneTD[6], 50);
	TextDrawSetShadow(PhoneTD[6], 0);
	TextDrawSetOutline(PhoneTD[6], 1);
	TextDrawBackgroundColor(PhoneTD[6], 255);
	TextDrawFont(PhoneTD[6], 4);
	TextDrawSetProportional(PhoneTD[6], 1);

	PhoneTD[7] = TextDrawCreate(403.000, 163.000, "LD_BUM:blkdot");
	TextDrawLetterSize(PhoneTD[7], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[7], 111.000, 228.000);
	TextDrawAlignment(PhoneTD[7], 1);
	TextDrawColor(PhoneTD[7], 1334509567);
	TextDrawUseBox(PhoneTD[7], 1);
	TextDrawBoxColor(PhoneTD[7], 50);
	TextDrawSetShadow(PhoneTD[7], 0);
	TextDrawSetOutline(PhoneTD[7], 1);
	TextDrawBackgroundColor(PhoneTD[7], 255);
	TextDrawFont(PhoneTD[7], 4);
	TextDrawSetProportional(PhoneTD[7], 1);

	PhoneTD[8] = TextDrawCreate(458.000, 148.000, "Smartphone");
	TextDrawLetterSize(PhoneTD[8], 0.158, 1.098);
	TextDrawTextSize(PhoneTD[8], 400.000, 37.000);
	TextDrawAlignment(PhoneTD[8], 2);
	TextDrawColor(PhoneTD[8], -1);
	TextDrawSetShadow(PhoneTD[8], 0);
	TextDrawSetOutline(PhoneTD[8], 0);
	TextDrawBackgroundColor(PhoneTD[8], 255);
	TextDrawFont(PhoneTD[8], 1);
	TextDrawSetProportional(PhoneTD[8], 1);

	PhoneTD[9] = TextDrawCreate(492.000, 150.000, "LD_BEAT:chit");
	TextDrawLetterSize(PhoneTD[9], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[9], 6.000, 7.000);
	TextDrawAlignment(PhoneTD[9], 1);
	TextDrawColor(PhoneTD[9], -251662081);
	TextDrawUseBox(PhoneTD[9], 1);
	TextDrawBoxColor(PhoneTD[9], 50);
	TextDrawSetShadow(PhoneTD[9], 0);
	TextDrawSetOutline(PhoneTD[9], 1);
	TextDrawBackgroundColor(PhoneTD[9], 255);
	TextDrawFont(PhoneTD[9], 4);
	TextDrawSetProportional(PhoneTD[9], 1);

	PhoneTD[10] = TextDrawCreate(493.000, 151.000, "LD_BEAT:chit");
	TextDrawLetterSize(PhoneTD[10], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[10], 4.000, 5.000);
	TextDrawAlignment(PhoneTD[10], 1);
	TextDrawColor(PhoneTD[10], 168301567);
	TextDrawUseBox(PhoneTD[10], 1);
	TextDrawBoxColor(PhoneTD[10], 50);
	TextDrawSetShadow(PhoneTD[10], 0);
	TextDrawSetOutline(PhoneTD[10], 1);
	TextDrawBackgroundColor(PhoneTD[10], 255);
	TextDrawFont(PhoneTD[10], 4);
	TextDrawSetProportional(PhoneTD[10], 1);

	PhoneTD[11] = TextDrawCreate(517.000, 172.000, "LD_BUM:blkdot");
	TextDrawLetterSize(PhoneTD[11], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[11], 1.000, 39.000);
	TextDrawAlignment(PhoneTD[11], 1);
	TextDrawColor(PhoneTD[11], -1094795521);
	TextDrawUseBox(PhoneTD[11], 1);
	TextDrawBoxColor(PhoneTD[11], 50);
	TextDrawSetShadow(PhoneTD[11], 0);
	TextDrawSetOutline(PhoneTD[11], 1);
	TextDrawBackgroundColor(PhoneTD[11], 255);
	TextDrawFont(PhoneTD[11], 4);
	TextDrawSetProportional(PhoneTD[11], 1);

	PhoneTD[12] = TextDrawCreate(447.000, 388.000, "LD_BEAT:chit");
	TextDrawLetterSize(PhoneTD[12], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[12], 24.000, 26.000);
	TextDrawAlignment(PhoneTD[12], 1);
	TextDrawColor(PhoneTD[12], -251662081);
	TextDrawUseBox(PhoneTD[12], 1);
	TextDrawBoxColor(PhoneTD[12], 50);
	TextDrawSetShadow(PhoneTD[12], 0);
	TextDrawSetOutline(PhoneTD[12], 1);
	TextDrawBackgroundColor(PhoneTD[12], 255);
	TextDrawFont(PhoneTD[12], 4);
	TextDrawSetProportional(PhoneTD[12], 1);
	TextDrawSetSelectable(PhoneTD[12], 1);

	PhoneTD[13] = TextDrawCreate(449.000, 390.000, "LD_BEAT:chit");
	TextDrawLetterSize(PhoneTD[13], 0.600, 2.000);
	TextDrawTextSize(PhoneTD[13], 20.000, 22.000);
	TextDrawAlignment(PhoneTD[13], 1);
	TextDrawColor(PhoneTD[13], 168301567);
	TextDrawUseBox(PhoneTD[13], 1);
	TextDrawBoxColor(PhoneTD[13], 50);
	TextDrawSetShadow(PhoneTD[13], 0);
	TextDrawSetOutline(PhoneTD[13], 1);
	TextDrawBackgroundColor(PhoneTD[13], 255);
	TextDrawFont(PhoneTD[13], 4);
	TextDrawSetProportional(PhoneTD[13], 1);

	PhoneTD[14] = TextDrawCreate(460.000, 170.000, "12:12");
	TextDrawLetterSize(PhoneTD[14], 0.694, 5.048);
	TextDrawTextSize(PhoneTD[14], 461.000, 93.000);
	TextDrawAlignment(PhoneTD[14], 2);
	TextDrawColor(PhoneTD[14], -1);
	TextDrawSetShadow(PhoneTD[14], 0);
	TextDrawSetOutline(PhoneTD[14], 0);
	TextDrawBackgroundColor(PhoneTD[14], 255);
	TextDrawFont(PhoneTD[14], 1);
	TextDrawSetProportional(PhoneTD[14], 1);

	PhoneTD[15] = TextDrawCreate(406.000, 231.000, "LD_BUM:blkdot");
	TextDrawTextSize(PhoneTD[15], 23.000, 27.000);
	TextDrawAlignment(PhoneTD[15], 1);
	TextDrawColor(PhoneTD[15], 230);
	TextDrawSetShadow(PhoneTD[15], 0);
	TextDrawSetOutline(PhoneTD[15], 0);
	TextDrawBackgroundColor(PhoneTD[15], 255);
	TextDrawFont(PhoneTD[15], 4);
	TextDrawSetProportional(PhoneTD[15], 1);
	TextDrawSetSelectable(PhoneTD[15], 1);

	PhoneTD[16] = TextDrawCreate(434.000, 231.000, "LD_BUM:blkdot");
	TextDrawTextSize(PhoneTD[16], 23.000, 27.000);
	TextDrawAlignment(PhoneTD[16], 1);
	TextDrawColor(PhoneTD[16], 230);
	TextDrawSetShadow(PhoneTD[16], 0);
	TextDrawSetOutline(PhoneTD[16], 0);
	TextDrawBackgroundColor(PhoneTD[16], 255);
	TextDrawFont(PhoneTD[16], 4);
	TextDrawSetProportional(PhoneTD[16], 1);
	TextDrawSetSelectable(PhoneTD[16], 1);

	PhoneTD[17] = TextDrawCreate(462.000, 231.000, "LD_BUM:blkdot");
	TextDrawTextSize(PhoneTD[17], 23.000, 27.000);
	TextDrawAlignment(PhoneTD[17], 1);
	TextDrawColor(PhoneTD[17], 230);
	TextDrawSetShadow(PhoneTD[17], 0);
	TextDrawSetOutline(PhoneTD[17], 0);
	TextDrawBackgroundColor(PhoneTD[17], 255);
	TextDrawFont(PhoneTD[17], 4);
	TextDrawSetProportional(PhoneTD[17], 1);
	TextDrawSetSelectable(PhoneTD[17], 1);

	PhoneTD[18] = TextDrawCreate(489.000, 231.000, "LD_BUM:blkdot");
	TextDrawTextSize(PhoneTD[18], 23.000, 27.000);
	TextDrawAlignment(PhoneTD[18], 1);
	TextDrawColor(PhoneTD[18], 230);
	TextDrawSetShadow(PhoneTD[18], 0);
	TextDrawSetOutline(PhoneTD[18], 0);
	TextDrawBackgroundColor(PhoneTD[18], 255);
	TextDrawFont(PhoneTD[18], 4);
	TextDrawSetProportional(PhoneTD[18], 1);
	TextDrawSetSelectable(PhoneTD[18], 1);

	PhoneTD[19] = TextDrawCreate(406.000, 272.000, "LD_BUM:blkdot");
	TextDrawTextSize(PhoneTD[19], 23.000, 27.000);
	TextDrawAlignment(PhoneTD[19], 1);
	TextDrawColor(PhoneTD[19], 230);
	TextDrawSetShadow(PhoneTD[19], 0);
	TextDrawSetOutline(PhoneTD[19], 0);
	TextDrawBackgroundColor(PhoneTD[19], 255);
	TextDrawFont(PhoneTD[19], 4);
	TextDrawSetProportional(PhoneTD[19], 1);
	TextDrawSetSelectable(PhoneTD[19], 1);

	PhoneTD[20] = TextDrawCreate(434.000, 272.000, "LD_BUM:blkdot");
	TextDrawTextSize(PhoneTD[20], 23.000, 27.000);
	TextDrawAlignment(PhoneTD[20], 1);
	TextDrawColor(PhoneTD[20], 230);
	TextDrawSetShadow(PhoneTD[20], 0);
	TextDrawSetOutline(PhoneTD[20], 0);
	TextDrawBackgroundColor(PhoneTD[20], 255);
	TextDrawFont(PhoneTD[20], 4);
	TextDrawSetProportional(PhoneTD[20], 1);
	TextDrawSetSelectable(PhoneTD[20], 1);

	PhoneTD[21] = TextDrawCreate(462.000, 272.000, "LD_BUM:blkdot");
	TextDrawTextSize(PhoneTD[21], 23.000, 27.000);
	TextDrawAlignment(PhoneTD[21], 1);
	TextDrawColor(PhoneTD[21], 230);
	TextDrawSetShadow(PhoneTD[21], 0);
	TextDrawSetOutline(PhoneTD[21], 0);
	TextDrawBackgroundColor(PhoneTD[21], 255);
	TextDrawFont(PhoneTD[21], 4);
	TextDrawSetProportional(PhoneTD[21], 1);
	TextDrawSetSelectable(PhoneTD[21], 1);

	PhoneTD[22] = TextDrawCreate(489.000, 272.000, "LD_BUM:blkdot");
	TextDrawTextSize(PhoneTD[22], 23.000, 27.000);
	TextDrawAlignment(PhoneTD[22], 1);
	TextDrawColor(PhoneTD[22], 230);
	TextDrawSetShadow(PhoneTD[22], 0);
	TextDrawSetOutline(PhoneTD[22], 0);
	TextDrawBackgroundColor(PhoneTD[22], 255);
	TextDrawFont(PhoneTD[22], 4);
	TextDrawSetProportional(PhoneTD[22], 1);
	TextDrawSetSelectable(PhoneTD[22], 1);

	PhoneTD[23] = TextDrawCreate(406.000, 314.000, "LD_BUM:blkdot");
	TextDrawTextSize(PhoneTD[23], 23.000, 27.000);
	TextDrawAlignment(PhoneTD[23], 1);
	TextDrawColor(PhoneTD[23], 230);
	TextDrawSetShadow(PhoneTD[23], 0);
	TextDrawSetOutline(PhoneTD[23], 0);
	TextDrawBackgroundColor(PhoneTD[23], 255);
	TextDrawFont(PhoneTD[23], 4);
	TextDrawSetProportional(PhoneTD[23], 1);
	TextDrawSetSelectable(PhoneTD[23], 1);

	PhoneTD[24] = TextDrawCreate(434.000, 314.000, "LD_BUM:blkdot");
	TextDrawTextSize(PhoneTD[24], 23.000, 27.000);
	TextDrawAlignment(PhoneTD[24], 1);
	TextDrawColor(PhoneTD[24], 230);
	TextDrawSetShadow(PhoneTD[24], 0);
	TextDrawSetOutline(PhoneTD[24], 0);
	TextDrawBackgroundColor(PhoneTD[24], 255);
	TextDrawFont(PhoneTD[24], 4);
	TextDrawSetProportional(PhoneTD[24], 1);
	TextDrawSetSelectable(PhoneTD[24], 1);

	PhoneTD[25] = TextDrawCreate(414.000, 235.000, "LD_BEAT:chit");
	TextDrawTextSize(PhoneTD[25], 6.000, 9.000);
	TextDrawAlignment(PhoneTD[25], 1);
	TextDrawColor(PhoneTD[25], -1);
	TextDrawSetShadow(PhoneTD[25], 0);
	TextDrawSetOutline(PhoneTD[25], 0);
	TextDrawBackgroundColor(PhoneTD[25], 255);
	TextDrawFont(PhoneTD[25], 4);
	TextDrawSetProportional(PhoneTD[25], 1);

	PhoneTD[26] = TextDrawCreate(414.000, 233.000, "(");
	TextDrawLetterSize(PhoneTD[26], 0.389, 2.099);
	TextDrawAlignment(PhoneTD[26], 1);
	TextDrawColor(PhoneTD[26], -1);
	TextDrawSetShadow(PhoneTD[26], 0);
	TextDrawSetOutline(PhoneTD[26], 0);
	TextDrawBackgroundColor(PhoneTD[26], 150);
	TextDrawFont(PhoneTD[26], 1);
	TextDrawSetProportional(PhoneTD[26], 1);

	PhoneTD[27] = TextDrawCreate(414.000, 246.000, "LD_BEAT:chit");
	TextDrawTextSize(PhoneTD[27], 6.000, 9.000);
	TextDrawAlignment(PhoneTD[27], 1);
	TextDrawColor(PhoneTD[27], -1);
	TextDrawSetShadow(PhoneTD[27], 0);
	TextDrawSetOutline(PhoneTD[27], 0);
	TextDrawBackgroundColor(PhoneTD[27], 255);
	TextDrawFont(PhoneTD[27], 4);
	TextDrawSetProportional(PhoneTD[27], 1);

	PhoneTD[28] = TextDrawCreate(440.000, 237.000, "HUD:radar_saveGame");
	TextDrawTextSize(PhoneTD[28], 12.000, 14.000);
	TextDrawAlignment(PhoneTD[28], 1);
	TextDrawColor(PhoneTD[28], -1);
	TextDrawSetShadow(PhoneTD[28], 0);
	TextDrawSetOutline(PhoneTD[28], 0);
	TextDrawBackgroundColor(PhoneTD[28], 255);
	TextDrawFont(PhoneTD[28], 4);
	TextDrawSetProportional(PhoneTD[28], 1);

	PhoneTD[29] = TextDrawCreate(467.000, 237.000, "HUD:radar_cash");
	TextDrawTextSize(PhoneTD[29], 14.000, 15.000);
	TextDrawAlignment(PhoneTD[29], 1);
	TextDrawColor(PhoneTD[29], -1);
	TextDrawSetShadow(PhoneTD[29], 0);
	TextDrawSetOutline(PhoneTD[29], 0);
	TextDrawBackgroundColor(PhoneTD[29], 255);
	TextDrawFont(PhoneTD[29], 4);
	TextDrawSetProportional(PhoneTD[29], 1);

	PhoneTD[30] = TextDrawCreate(494.000, 238.000, "HUD:radar_waypoint");
	TextDrawTextSize(PhoneTD[30], 13.000, 13.000);
	TextDrawAlignment(PhoneTD[30], 1);
	TextDrawColor(PhoneTD[30], -1);
	TextDrawSetShadow(PhoneTD[30], 0);
	TextDrawSetOutline(PhoneTD[30], 0);
	TextDrawBackgroundColor(PhoneTD[30], 255);
	TextDrawFont(PhoneTD[30], 4);
	TextDrawSetProportional(PhoneTD[30], 1);

	PhoneTD[31] = TextDrawCreate(416.000, 274.000, "i");
	TextDrawLetterSize(PhoneTD[31], 0.729, 2.699);
	TextDrawAlignment(PhoneTD[31], 1);
	TextDrawColor(PhoneTD[31], -1);
	TextDrawSetShadow(PhoneTD[31], 0);
	TextDrawSetOutline(PhoneTD[31], 0);
	TextDrawBackgroundColor(PhoneTD[31], 150);
	TextDrawFont(PhoneTD[31], 1);
	TextDrawSetProportional(PhoneTD[31], 1);

	PhoneTD[32] = TextDrawCreate(441.000, 275.000, "V");
	TextDrawLetterSize(PhoneTD[32], 0.549, 2.199);
	TextDrawAlignment(PhoneTD[32], 1);
	TextDrawColor(PhoneTD[32], 1334509567);
	TextDrawSetShadow(PhoneTD[32], 0);
	TextDrawSetOutline(PhoneTD[32], 0);
	TextDrawBackgroundColor(PhoneTD[32], 150);
	TextDrawFont(PhoneTD[32], 1);
	TextDrawSetProportional(PhoneTD[32], 1);

	PhoneTD[33] = TextDrawCreate(440.000, 275.000, "V");
	TextDrawLetterSize(PhoneTD[33], 0.549, 2.198);
	TextDrawAlignment(PhoneTD[33], 1);
	TextDrawColor(PhoneTD[33], -1);
	TextDrawSetShadow(PhoneTD[33], 0);
	TextDrawSetOutline(PhoneTD[33], 0);
	TextDrawBackgroundColor(PhoneTD[33], 150);
	TextDrawFont(PhoneTD[33], 1);
	TextDrawSetProportional(PhoneTD[33], 1);

	PhoneTD[34] = TextDrawCreate(470.000, 275.000, "T");
	TextDrawLetterSize(PhoneTD[34], 0.549, 2.197);
	TextDrawAlignment(PhoneTD[34], 1);
	TextDrawColor(PhoneTD[34], 1334509567);
	TextDrawSetShadow(PhoneTD[34], 0);
	TextDrawSetOutline(PhoneTD[34], 0);
	TextDrawBackgroundColor(PhoneTD[34], 150);
	TextDrawFont(PhoneTD[34], 1);
	TextDrawSetProportional(PhoneTD[34], 1);

	PhoneTD[35] = TextDrawCreate(469.000, 274.000, "T");
	TextDrawLetterSize(PhoneTD[35], 0.559, 2.498);
	TextDrawAlignment(PhoneTD[35], 1);
	TextDrawColor(PhoneTD[35], 255);
	TextDrawSetShadow(PhoneTD[35], 0);
	TextDrawSetOutline(PhoneTD[35], 0);
	TextDrawBackgroundColor(PhoneTD[35], 150);
	TextDrawFont(PhoneTD[35], 1);
	TextDrawSetProportional(PhoneTD[35], 1);

	PhoneTD[36] = TextDrawCreate(494.000, 278.000, "Ads");
	TextDrawLetterSize(PhoneTD[36], 0.229, 1.498);
	TextDrawAlignment(PhoneTD[36], 1);
	TextDrawColor(PhoneTD[36], -6259969);
	TextDrawSetShadow(PhoneTD[36], 0);
	TextDrawSetOutline(PhoneTD[36], 0);
	TextDrawBackgroundColor(PhoneTD[36], 150);
	TextDrawFont(PhoneTD[36], 1);
	TextDrawSetProportional(PhoneTD[36], 1);

	PhoneTD[37] = TextDrawCreate(410.000, 322.000, "LD_BUM:blkdot");
	TextDrawTextSize(PhoneTD[37], 15.000, 13.000);
	TextDrawAlignment(PhoneTD[37], 1);
	TextDrawColor(PhoneTD[37], -1);
	TextDrawSetShadow(PhoneTD[37], 0);
	TextDrawSetOutline(PhoneTD[37], 0);
	TextDrawBackgroundColor(PhoneTD[37], 255);
	TextDrawFont(PhoneTD[37], 4);
	TextDrawSetProportional(PhoneTD[37], 1);

	PhoneTD[38] = TextDrawCreate(412.000, 322.000, "LD_BEAT:chit");
	TextDrawTextSize(PhoneTD[38], 11.000, 13.000);
	TextDrawAlignment(PhoneTD[38], 1);
	TextDrawColor(PhoneTD[38], 255);
	TextDrawSetShadow(PhoneTD[38], 0);
	TextDrawSetOutline(PhoneTD[38], 0);
	TextDrawBackgroundColor(PhoneTD[38], 255);
	TextDrawFont(PhoneTD[38], 4);
	TextDrawSetProportional(PhoneTD[38], 1);

	PhoneTD[39] = TextDrawCreate(413.000, 323.000, "LD_BEAT:chit");
	TextDrawTextSize(PhoneTD[39], 9.000, 11.000);
	TextDrawAlignment(PhoneTD[39], 1);
	TextDrawColor(PhoneTD[39], -1);
	TextDrawSetShadow(PhoneTD[39], 0);
	TextDrawSetOutline(PhoneTD[39], 0);
	TextDrawBackgroundColor(PhoneTD[39], 255);
	TextDrawFont(PhoneTD[39], 4);
	TextDrawSetProportional(PhoneTD[39], 1);

	PhoneTD[40] = TextDrawCreate(438.000, 319.000, "LD_CHAT:goodcha");
	TextDrawTextSize(PhoneTD[40], 15.000, 17.000);
	TextDrawAlignment(PhoneTD[40], 1);
	TextDrawColor(PhoneTD[40], -1);
	TextDrawSetShadow(PhoneTD[40], 0);
	TextDrawSetOutline(PhoneTD[40], 0);
	TextDrawBackgroundColor(PhoneTD[40], 255);
	TextDrawFont(PhoneTD[40], 4);
	TextDrawSetProportional(PhoneTD[40], 1);

	PhoneTD[41] = TextDrawCreate(417.000, 259.000, "Call");
	TextDrawLetterSize(PhoneTD[41], 0.190, 0.899);
	TextDrawAlignment(PhoneTD[41], 2);
	TextDrawColor(PhoneTD[41], -1);
	TextDrawSetShadow(PhoneTD[41], 0);
	TextDrawSetOutline(PhoneTD[41], 0);
	TextDrawBackgroundColor(PhoneTD[41], 150);
	TextDrawFont(PhoneTD[41], 1);
	TextDrawSetProportional(PhoneTD[41], 1);

	PhoneTD[42] = TextDrawCreate(446.000, 259.000, "Contact");
	TextDrawLetterSize(PhoneTD[42], 0.190, 0.899);
	TextDrawAlignment(PhoneTD[42], 2);
	TextDrawColor(PhoneTD[42], -1);
	TextDrawSetShadow(PhoneTD[42], 0);
	TextDrawSetOutline(PhoneTD[42], 0);
	TextDrawBackgroundColor(PhoneTD[42], 150);
	TextDrawFont(PhoneTD[42], 1);
	TextDrawSetProportional(PhoneTD[42], 1);

	PhoneTD[43] = TextDrawCreate(474.000, 259.000, "M-Bank");
	TextDrawLetterSize(PhoneTD[43], 0.190, 0.899);
	TextDrawAlignment(PhoneTD[43], 2);
	TextDrawColor(PhoneTD[43], -1);
	TextDrawSetShadow(PhoneTD[43], 0);
	TextDrawSetOutline(PhoneTD[43], 0);
	TextDrawBackgroundColor(PhoneTD[43], 150);
	TextDrawFont(PhoneTD[43], 1);
	TextDrawSetProportional(PhoneTD[43], 1);

	PhoneTD[44] = TextDrawCreate(501.000, 259.000, "Gps");
	TextDrawLetterSize(PhoneTD[44], 0.190, 0.899);
	TextDrawAlignment(PhoneTD[44], 2);
	TextDrawColor(PhoneTD[44], -1);
	TextDrawSetShadow(PhoneTD[44], 0);
	TextDrawSetOutline(PhoneTD[44], 0);
	TextDrawBackgroundColor(PhoneTD[44], 150);
	TextDrawFont(PhoneTD[44], 1);
	TextDrawSetProportional(PhoneTD[44], 1);

	PhoneTD[45] = TextDrawCreate(418.000, 300.000, "Settings");
	TextDrawLetterSize(PhoneTD[45], 0.190, 0.899);
	TextDrawAlignment(PhoneTD[45], 2);
	TextDrawColor(PhoneTD[45], -1);
	TextDrawSetShadow(PhoneTD[45], 0);
	TextDrawSetOutline(PhoneTD[45], 0);
	TextDrawBackgroundColor(PhoneTD[45], 150);
	TextDrawFont(PhoneTD[45], 1);
	TextDrawSetProportional(PhoneTD[45], 1);

	PhoneTD[46] = TextDrawCreate(446.000, 300.000, "Vallet");
	TextDrawLetterSize(PhoneTD[46], 0.190, 0.899);
	TextDrawAlignment(PhoneTD[46], 2);
	TextDrawColor(PhoneTD[46], -1);
	TextDrawSetShadow(PhoneTD[46], 0);
	TextDrawSetOutline(PhoneTD[46], 0);
	TextDrawBackgroundColor(PhoneTD[46], 150);
	TextDrawFont(PhoneTD[46], 1);
	TextDrawSetProportional(PhoneTD[46], 1);

	PhoneTD[47] = TextDrawCreate(474.000, 300.000, "Tweet");
	TextDrawLetterSize(PhoneTD[47], 0.190, 0.899);
	TextDrawAlignment(PhoneTD[47], 2);
	TextDrawColor(PhoneTD[47], -1);
	TextDrawSetShadow(PhoneTD[47], 0);
	TextDrawSetOutline(PhoneTD[47], 0);
	TextDrawBackgroundColor(PhoneTD[47], 150);
	TextDrawFont(PhoneTD[47], 1);
	TextDrawSetProportional(PhoneTD[47], 1);

	PhoneTD[48] = TextDrawCreate(501.000, 300.000, "Ads");
	TextDrawLetterSize(PhoneTD[48], 0.190, 0.899);
	TextDrawAlignment(PhoneTD[48], 2);
	TextDrawColor(PhoneTD[48], -1);
	TextDrawSetShadow(PhoneTD[48], 0);
	TextDrawSetOutline(PhoneTD[48], 0);
	TextDrawBackgroundColor(PhoneTD[48], 150);
	TextDrawFont(PhoneTD[48], 1);
	TextDrawSetProportional(PhoneTD[48], 1);

	PhoneTD[49] = TextDrawCreate(418.000, 342.000, "Camera");
	TextDrawLetterSize(PhoneTD[49], 0.190, 0.899);
	TextDrawAlignment(PhoneTD[49], 2);
	TextDrawColor(PhoneTD[49], -1);
	TextDrawSetShadow(PhoneTD[49], 0);
	TextDrawSetOutline(PhoneTD[49], 0);
	TextDrawBackgroundColor(PhoneTD[49], 150);
	TextDrawFont(PhoneTD[49], 1);
	TextDrawSetProportional(PhoneTD[49], 1);

	PhoneTD[50] = TextDrawCreate(446.000, 342.000, "Sms");
	TextDrawLetterSize(PhoneTD[50], 0.190, 0.899);
	TextDrawAlignment(PhoneTD[50], 2);
	TextDrawColor(PhoneTD[50], -1);
	TextDrawSetShadow(PhoneTD[50], 0);
	TextDrawSetOutline(PhoneTD[50], 0);
	TextDrawBackgroundColor(PhoneTD[50], 150);
	TextDrawFont(PhoneTD[50], 1);
	TextDrawSetProportional(PhoneTD[50], 1);
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

	for(new i = 0; i < 51; i++) {
		TextDrawShowForPlayer(playerid, PhoneTD[i]);
	}
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
