/*										
													
                            ROLEPLAY INDONESIA
							TEXTDRAW SYSTEM
*/
new PlayerText:JailTD[MAX_PLAYERS];
new Text:BoxStartTraining;
new Text:BoxTraining;
new PlayerText:TextStartTraining[MAX_PLAYERS];
new PlayerText:TextTraining[MAX_PLAYERS];
//new Text: LogoCostum;

new PlayerText:ServerTD[MAX_PLAYERS][2];
new Text:Webtd[3];
new Text:avenue;
new Text:roleplay;
new PlayerText:LSSLOGO[MAX_PLAYERS][3];
new PlayerText:AnimTD[MAX_PLAYERS];
new PlayerText:TogAmmo[MAX_PLAYERS];
new PlayerText:OffLamp[MAX_PLAYERS];
new Text:HouseLight;
new Text:PlayerCrateTD;
new PlayerText:PlayerCrate[MAX_PLAYERS][2];
new PlayerText:ActiveTD[MAX_PLAYERS];
new Text:DPvehfare[MAX_PLAYERS];
new Text:TDEditor_TD[1];
new Text:notifTD[2];
new Text:injuredtextdraw;
new PlayerText:InfoTD[MAX_PLAYERS];
new PlayerText:Avenuewm[MAX_PLAYERS];
new Text:Time, Text:Date;
new Text:DollarCents;
new PlayerText:Locationtd[MAX_PLAYERS];
new PlayerText:LocTd[MAX_PLAYERS];
new PlayerText:GPSLocation[MAX_PLAYERS];
new PlayerText:textdraw_footer[MAX_PLAYERS];

//Variable vRadio
new Text:vRadio[9];
new PlayerText:vRadioPlay[MAX_PLAYERS];
new PlayerText:vRadioPause[MAX_PLAYERS];
new PlayerText:vRadioLink[MAX_PLAYERS];
new PlayerText:vRadioPlayLink[MAX_PLAYERS];
new PlayerText:vRadioClose[MAX_PLAYERS];

new Text:EventTD[2];

//Variables Spectating
new PlayerText:SpecTD[MAX_PLAYERS][2];

new Text: MYSUNSHINE[3];
new Text: SUNSHINELOGO[3];

CreatePlayerTextDraws(playerid)
{
    //Anim
    AnimTD[playerid] = CreatePlayerTextDraw(playerid, 204.000000, 430.000000, "SPACE_~w~to_stop_the_animation");
    PlayerTextDrawFont(playerid, AnimTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, AnimTD[playerid], 0.420000, 1.700000);
    PlayerTextDrawTextSize(playerid, AnimTD[playerid], 416.000000, 0.000000);
    PlayerTextDrawSetOutline(playerid, AnimTD[playerid], 0);
    PlayerTextDrawSetShadow(playerid, AnimTD[playerid], 1);
    PlayerTextDrawAlignment(playerid, AnimTD[playerid], 0);
    PlayerTextDrawColor(playerid, AnimTD[playerid], -16776981);
    PlayerTextDrawBackgroundColor(playerid, AnimTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, AnimTD[playerid], 155);
    PlayerTextDrawUseBox(playerid, AnimTD[playerid], 1);
    PlayerTextDrawSetProportional(playerid, AnimTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, AnimTD[playerid], 0);
    //Avenue Logo
    Avenuewm[playerid] = CreatePlayerTextDraw(playerid, 634.000000, 432.000000, "www.MySunshine-rp.com");
    PlayerTextDrawFont(playerid, Avenuewm[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Avenuewm[playerid], 0.200000, 1.200000);
    PlayerTextDrawTextSize(playerid, Avenuewm[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, Avenuewm[playerid], 0);
    PlayerTextDrawSetShadow(playerid, Avenuewm[playerid], 0);
    PlayerTextDrawAlignment(playerid, Avenuewm[playerid], 3);
    PlayerTextDrawColor(playerid, Avenuewm[playerid], -101);
    PlayerTextDrawBackgroundColor(playerid, Avenuewm[playerid], 255);
    PlayerTextDrawBoxColor(playerid, Avenuewm[playerid], 50);
    PlayerTextDrawUseBox(playerid, Avenuewm[playerid], 0);
    PlayerTextDrawSetProportional(playerid, Avenuewm[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, Avenuewm[playerid], 1);

    //Footer
    textdraw_footer[playerid] = CreatePlayerTextDraw(playerid, 321.000000, 352.000793, "_");
    PlayerTextDrawLetterSize(playerid, textdraw_footer[playerid], 0.214499, 1.031875);
    PlayerTextDrawAlignment(playerid, textdraw_footer[playerid], 2);
    PlayerTextDrawColor(playerid, textdraw_footer[playerid], -1);
    PlayerTextDrawSetShadow(playerid, textdraw_footer[playerid], 0);
    PlayerTextDrawSetOutline(playerid, textdraw_footer[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, textdraw_footer[playerid], 255);
    PlayerTextDrawFont(playerid, textdraw_footer[playerid], 1);
    PlayerTextDrawSetProportional(playerid, textdraw_footer[playerid], 1);
    PlayerTextDrawSetShadow(playerid, textdraw_footer[playerid], 0);

	ServerTD[playerid][0] = CreatePlayerTextDraw(playerid, 231.000000, 3.000000, "Jomokgamers_Roleplay");
	PlayerTextDrawFont(playerid, ServerTD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, ServerTD[playerid][0], 0.21000, 1.450000);
	PlayerTextDrawTextSize(playerid, ServerTD[playerid][0], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, ServerTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, ServerTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, ServerTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, ServerTD[playerid][0], 35839);
	PlayerTextDrawBackgroundColor(playerid, ServerTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, ServerTD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, ServerTD[playerid][0], 0);
	PlayerTextDrawSetProportional(playerid, ServerTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, ServerTD[playerid][0], 0);

	ServerTD[playerid][1] = CreatePlayerTextDraw(playerid, 295.000000, 3.000000, "-_Finally_Here_V0.2.3d");
	PlayerTextDrawFont(playerid, ServerTD[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, ServerTD[playerid][1], 0.200000, 1.450000);
	PlayerTextDrawTextSize(playerid, ServerTD[playerid][1], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, ServerTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, ServerTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, ServerTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, ServerTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, ServerTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, ServerTD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, ServerTD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, ServerTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, ServerTD[playerid][1], 0);

	LSSLOGO[playerid][0] = CreatePlayerTextDraw(playerid, 320.000000, 34.000000, "MySunshine");
	PlayerTextDrawFont(playerid, LSSLOGO[playerid][0], 3);
	PlayerTextDrawLetterSize(playerid, LSSLOGO[playerid][0], 0.745832, 4.699999);
	PlayerTextDrawTextSize(playerid, LSSLOGO[playerid][0], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, LSSLOGO[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, LSSLOGO[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, LSSLOGO[playerid][0], 2);
	PlayerTextDrawColor(playerid, LSSLOGO[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, LSSLOGO[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, LSSLOGO[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, LSSLOGO[playerid][0], 0);
	PlayerTextDrawSetProportional(playerid, LSSLOGO[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, LSSLOGO[playerid][0], 0);

	LSSLOGO[playerid][1] = CreatePlayerTextDraw(playerid, 320.000000, 52.000000, "Roleplay");
	PlayerTextDrawFont(playerid, LSSLOGO[playerid][1], 0);
	PlayerTextDrawLetterSize(playerid, LSSLOGO[playerid][1], 1.287503, 3.799998);
	PlayerTextDrawTextSize(playerid, LSSLOGO[playerid][1], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, LSSLOGO[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, LSSLOGO[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, LSSLOGO[playerid][1], 2);
	PlayerTextDrawColor(playerid, LSSLOGO[playerid][1], 255);
	PlayerTextDrawBackgroundColor(playerid, LSSLOGO[playerid][1], -1);
	PlayerTextDrawBoxColor(playerid, LSSLOGO[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, LSSLOGO[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, LSSLOGO[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, LSSLOGO[playerid][1], 0);

    //Player Textdraws Spectating
    SpecTD[playerid][0] = CreatePlayerTextDraw(playerid, 240.336, 328.249, "_");
    PlayerTextDrawLetterSize(playerid, SpecTD[playerid][0], 0.000, 10.046);
    PlayerTextDrawTextSize(playerid, SpecTD[playerid][0], 401.000, 0.000);
    PlayerTextDrawAlignment(playerid, SpecTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, SpecTD[playerid][0], -1);
    PlayerTextDrawUseBox(playerid, SpecTD[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, SpecTD[playerid][0], 100);
    PlayerTextDrawSetShadow(playerid, SpecTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, SpecTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, SpecTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, SpecTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, SpecTD[playerid][0], 1);

    SpecTD[playerid][1] = CreatePlayerTextDraw(playerid, 319.822, 328.367, "_");
    PlayerTextDrawLetterSize(playerid, SpecTD[playerid][1], 0.321, 1.389);
    PlayerTextDrawAlignment(playerid, SpecTD[playerid][1], 2);
    PlayerTextDrawColor(playerid, SpecTD[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, SpecTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, SpecTD[playerid][1], 1);
    PlayerTextDrawBackgroundColor(playerid, SpecTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, SpecTD[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, SpecTD[playerid][1], 1);

	//Info textdraw
	InfoTD[playerid] = CreatePlayerTextDraw(playerid, 148.888, 361.385, "Welcome!");
 	PlayerTextDrawLetterSize(playerid, InfoTD[playerid], 0.326, 1.654);
	PlayerTextDrawAlignment(playerid, InfoTD[playerid], 1);
	PlayerTextDrawColor(playerid, InfoTD[playerid], -1);
	PlayerTextDrawSetOutline(playerid, InfoTD[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, InfoTD[playerid], 0x000000FF);
	PlayerTextDrawFont(playerid, InfoTD[playerid], 1);
	PlayerTextDrawSetProportional(playerid, InfoTD[playerid], 1);
	
    ActiveTD[playerid] = CreatePlayerTextDraw(playerid, 316.000000, 208.000000, "Installing Mod");
    PlayerTextDrawFont(playerid, ActiveTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, ActiveTD[playerid], 0.437500, 1.600000);
    PlayerTextDrawTextSize(playerid, ActiveTD[playerid], 400.000000, 172.000000);
    PlayerTextDrawSetOutline(playerid, ActiveTD[playerid], 0);
    PlayerTextDrawSetShadow(playerid, ActiveTD[playerid], 1);
    PlayerTextDrawAlignment(playerid, ActiveTD[playerid], 2);
    PlayerTextDrawColor(playerid, ActiveTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, ActiveTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, ActiveTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, ActiveTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, ActiveTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, ActiveTD[playerid], 0);

	DPvehfare[playerid] = TextDrawCreate(462.000000, 401.166687, "$500.000");
	TextDrawLetterSize(DPvehfare[playerid], 0.216000, 0.952498);
	TextDrawAlignment(DPvehfare[playerid], 1);
	TextDrawColor(DPvehfare[playerid], 16711935);
	TextDrawSetShadow(DPvehfare[playerid], 0);
	TextDrawSetOutline(DPvehfare[playerid], 1);
	TextDrawBackgroundColor(DPvehfare[playerid], 255);
	TextDrawFont(DPvehfare[playerid], 1);
	TextDrawSetProportional(DPvehfare[playerid], 1);
	TextDrawSetShadow(DPvehfare[playerid], 0);

	TDEditor_TD[0] = TextDrawCreate(427.000000, 400.583374, "Fare:");
	TextDrawLetterSize(TDEditor_TD[0], 0.360498, 1.022500);
	TextDrawAlignment(TDEditor_TD[0], 1);
	TextDrawColor(TDEditor_TD[0], -1);
	TextDrawSetShadow(TDEditor_TD[0], 0);
	TextDrawSetOutline(TDEditor_TD[0], 1);
	TextDrawBackgroundColor(TDEditor_TD[0], 255);
	TextDrawFont(TDEditor_TD[0], 1);
	TextDrawSetProportional(TDEditor_TD[0], 1);
	TextDrawSetShadow(TDEditor_TD[0], 0);

    TogAmmo[playerid] = CreatePlayerTextDraw(playerid, 522.000000, 62.000000, "No Ammo");
    PlayerTextDrawFont(playerid, TogAmmo[playerid], 1);
    PlayerTextDrawLetterSize(playerid, TogAmmo[playerid], 0.329166, 1.050000);
    PlayerTextDrawTextSize(playerid, TogAmmo[playerid], 603.000000, -73.000000);
    PlayerTextDrawSetOutline(playerid, TogAmmo[playerid], 1);
    PlayerTextDrawSetShadow(playerid, TogAmmo[playerid], 0);
    PlayerTextDrawAlignment(playerid, TogAmmo[playerid], 2);
    PlayerTextDrawColor(playerid, TogAmmo[playerid], 16777215);
    PlayerTextDrawBackgroundColor(playerid, TogAmmo[playerid], 255);
    PlayerTextDrawBoxColor(playerid, TogAmmo[playerid], 50);
    PlayerTextDrawUseBox(playerid, TogAmmo[playerid], 0);
    PlayerTextDrawSetProportional(playerid, TogAmmo[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TogAmmo[playerid], 0);

    OffLamp[playerid] = CreatePlayerTextDraw(playerid, 323.000000, 2.000000, "_");
    PlayerTextDrawFont(playerid, OffLamp[playerid], 1);
    PlayerTextDrawLetterSize(playerid, OffLamp[playerid], 1.058333, 49.300003);
    PlayerTextDrawTextSize(playerid, OffLamp[playerid], 298.500000, 645.000000);
    PlayerTextDrawSetOutline(playerid, OffLamp[playerid], 1);
    PlayerTextDrawSetShadow(playerid, OffLamp[playerid], 0);
    PlayerTextDrawAlignment(playerid, OffLamp[playerid], 2);
    PlayerTextDrawColor(playerid, OffLamp[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, OffLamp[playerid], 255);
    PlayerTextDrawBoxColor(playerid, OffLamp[playerid], 199);
    PlayerTextDrawUseBox(playerid, OffLamp[playerid], 1);
    PlayerTextDrawSetProportional(playerid, OffLamp[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, OffLamp[playerid], 0);

    PlayerCrate[playerid][0] = CreatePlayerTextDraw(playerid, 552.000000, 107.000000, "Storage");
    PlayerTextDrawFont(playerid, PlayerCrate[playerid][0], 0);
    PlayerTextDrawLetterSize(playerid, PlayerCrate[playerid][0], 0.479166, 1.850000);
    PlayerTextDrawTextSize(playerid, PlayerCrate[playerid][0], 755.000000, 167.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCrate[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCrate[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PlayerCrate[playerid][0], 2);
    PlayerTextDrawColor(playerid, PlayerCrate[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCrate[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCrate[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, PlayerCrate[playerid][0], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCrate[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCrate[playerid][0], 0);

    PlayerCrate[playerid][1] = CreatePlayerTextDraw(playerid, 507.000000, 133.000000, "Trash~n~0/10");
    PlayerTextDrawFont(playerid, PlayerCrate[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, PlayerCrate[playerid][1], 0.325000, 1.100000);
    PlayerTextDrawTextSize(playerid, PlayerCrate[playerid][1], 755.000000, 167.000000);
    PlayerTextDrawSetOutline(playerid, PlayerCrate[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, PlayerCrate[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PlayerCrate[playerid][1], 1);
    PlayerTextDrawColor(playerid, PlayerCrate[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PlayerCrate[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PlayerCrate[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, PlayerCrate[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, PlayerCrate[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PlayerCrate[playerid][1], 0);

    vRadioPlay[playerid] = CreatePlayerTextDraw(playerid, 275.000000, 200.000000, "ld_beat:chit");
    PlayerTextDrawFont(playerid, vRadioPlay[playerid], 4);
    PlayerTextDrawLetterSize(playerid, vRadioPlay[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, vRadioPlay[playerid], 35.500000, 30.500000);
    PlayerTextDrawSetOutline(playerid, vRadioPlay[playerid], 1);
    PlayerTextDrawSetShadow(playerid, vRadioPlay[playerid], 0);
    PlayerTextDrawAlignment(playerid, vRadioPlay[playerid], 1);
    PlayerTextDrawColor(playerid, vRadioPlay[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, vRadioPlay[playerid], 255);
    PlayerTextDrawBoxColor(playerid, vRadioPlay[playerid], 50);
    PlayerTextDrawUseBox(playerid, vRadioPlay[playerid], 1);
    PlayerTextDrawSetProportional(playerid, vRadioPlay[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, vRadioPlay[playerid], 1);

    vRadioPause[playerid] = CreatePlayerTextDraw(playerid, 313.000000, 200.000000, "ld_beat:chit");
    PlayerTextDrawFont(playerid, vRadioPause[playerid], 4);
    PlayerTextDrawLetterSize(playerid, vRadioPause[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, vRadioPause[playerid], 35.500000, 30.500000);
    PlayerTextDrawSetOutline(playerid, vRadioPause[playerid], 1);
    PlayerTextDrawSetShadow(playerid, vRadioPause[playerid], 0);
    PlayerTextDrawAlignment(playerid, vRadioPause[playerid], 1);
    PlayerTextDrawColor(playerid, vRadioPause[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, vRadioPause[playerid], 255);
    PlayerTextDrawBoxColor(playerid, vRadioPause[playerid], 50);
    PlayerTextDrawUseBox(playerid, vRadioPause[playerid], 1);
    PlayerTextDrawSetProportional(playerid, vRadioPause[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, vRadioPause[playerid], 1);

    vRadioLink[playerid] = CreatePlayerTextDraw(playerid, 226.000000, 285.000000, "URL link:");
    PlayerTextDrawFont(playerid, vRadioLink[playerid], 1);
    PlayerTextDrawLetterSize(playerid, vRadioLink[playerid], 0.179166, 0.949999);
    PlayerTextDrawTextSize(playerid, vRadioLink[playerid], 323.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, vRadioLink[playerid], 1);
    PlayerTextDrawSetShadow(playerid, vRadioLink[playerid], 0);
    PlayerTextDrawAlignment(playerid, vRadioLink[playerid], 1);
    PlayerTextDrawColor(playerid, vRadioLink[playerid], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, vRadioLink[playerid], 255);
    PlayerTextDrawBoxColor(playerid, vRadioLink[playerid], 50);
    PlayerTextDrawUseBox(playerid, vRadioLink[playerid], 0);
    PlayerTextDrawSetProportional(playerid, vRadioLink[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, vRadioLink[playerid], 1);

    vRadioPlayLink[playerid] = CreatePlayerTextDraw(playerid, 367.000000, 285.000000, "PLAY");
    PlayerTextDrawFont(playerid, vRadioPlayLink[playerid], 1);
    PlayerTextDrawLetterSize(playerid, vRadioPlayLink[playerid], 0.179166, 0.949999);
    PlayerTextDrawTextSize(playerid, vRadioPlayLink[playerid], 401.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, vRadioPlayLink[playerid], 1);
    PlayerTextDrawSetShadow(playerid, vRadioPlayLink[playerid], 0);
    PlayerTextDrawAlignment(playerid, vRadioPlayLink[playerid], 1);
    PlayerTextDrawColor(playerid, vRadioPlayLink[playerid], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, vRadioPlayLink[playerid], 255);
    PlayerTextDrawBoxColor(playerid, vRadioPlayLink[playerid], 50);
    PlayerTextDrawUseBox(playerid, vRadioPlayLink[playerid], 1);
    PlayerTextDrawSetProportional(playerid, vRadioPlayLink[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, vRadioPlayLink[playerid], 1);

    vRadioClose[playerid] = CreatePlayerTextDraw(playerid, 383.000000, 169.000000, "Close");
    PlayerTextDrawFont(playerid, vRadioClose[playerid], 1);
    PlayerTextDrawLetterSize(playerid, vRadioClose[playerid], 0.279166, 1.050000);
    PlayerTextDrawTextSize(playerid, vRadioClose[playerid], 404.000000, 23.000000);
    PlayerTextDrawSetOutline(playerid, vRadioClose[playerid], 1);
    PlayerTextDrawSetShadow(playerid, vRadioClose[playerid], 0);
    PlayerTextDrawAlignment(playerid, vRadioClose[playerid], 1);
    PlayerTextDrawColor(playerid, vRadioClose[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, vRadioClose[playerid], 255);
    PlayerTextDrawBoxColor(playerid, vRadioClose[playerid], 50);
    PlayerTextDrawUseBox(playerid, vRadioClose[playerid], 0);
    PlayerTextDrawSetProportional(playerid, vRadioClose[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, vRadioClose[playerid], 1);

    //Player Textdraws
    TextStartTraining[playerid] = CreatePlayerTextDraw(playerid, 583.000000, 103.000000, "~y~Start in~n~~w~10");
    PlayerTextDrawFont(playerid, TextStartTraining[playerid], 0);
    PlayerTextDrawLetterSize(playerid, TextStartTraining[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, TextStartTraining[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, TextStartTraining[playerid], 1);
    PlayerTextDrawSetShadow(playerid, TextStartTraining[playerid], 0);
    PlayerTextDrawAlignment(playerid, TextStartTraining[playerid], 3);
    PlayerTextDrawColor(playerid, TextStartTraining[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, TextStartTraining[playerid], 255);
    PlayerTextDrawBoxColor(playerid, TextStartTraining[playerid], 50);
    PlayerTextDrawUseBox(playerid, TextStartTraining[playerid], 0);
    PlayerTextDrawSetProportional(playerid, TextStartTraining[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TextStartTraining[playerid], 0);

    TextTraining[playerid] = CreatePlayerTextDraw(playerid, 561.000000, 103.000000, "~y~Time Left~n~~w~130~n~~y~Score~n~~w~130");
    PlayerTextDrawFont(playerid, TextTraining[playerid], 0);
    PlayerTextDrawLetterSize(playerid, TextTraining[playerid], 0.600000, 1.650000);
    PlayerTextDrawTextSize(playerid, TextTraining[playerid], 645.000000, 112.000000);
    PlayerTextDrawSetOutline(playerid, TextTraining[playerid], 1);
    PlayerTextDrawSetShadow(playerid, TextTraining[playerid], 0);
    PlayerTextDrawAlignment(playerid, TextTraining[playerid], 2);
    PlayerTextDrawColor(playerid, TextTraining[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, TextTraining[playerid], 255);
    PlayerTextDrawBoxColor(playerid, TextTraining[playerid], 50);
    PlayerTextDrawUseBox(playerid, TextTraining[playerid], 0);
    PlayerTextDrawSetProportional(playerid, TextTraining[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, TextTraining[playerid], 0);

    JailTD[playerid] = CreatePlayerTextDraw(playerid, 328.000000, 373.000000, "JAIL TIME: ~y~31312 ~w~SECOND");
    PlayerTextDrawFont(playerid, JailTD[playerid], 2);
    PlayerTextDrawLetterSize(playerid, JailTD[playerid], 0.487500, 1.900000);
    PlayerTextDrawTextSize(playerid, JailTD[playerid], 400.000000, 397.000000);
    PlayerTextDrawSetOutline(playerid, JailTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, JailTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, JailTD[playerid], 2);
    PlayerTextDrawColor(playerid, JailTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, JailTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, JailTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, JailTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, JailTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, JailTD[playerid], 0);

    Locationtd[playerid] = CreatePlayerTextDraw(playerid, 80.000000, 437.000000, "You are entering idlewood");
    PlayerTextDrawFont(playerid, Locationtd[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Locationtd[playerid], 0.170000, 0.750000);
    PlayerTextDrawTextSize(playerid, Locationtd[playerid], 12.000000, 640.000000);
    PlayerTextDrawSetOutline(playerid, Locationtd[playerid], 1);
    PlayerTextDrawSetShadow(playerid, Locationtd[playerid], 0);
    PlayerTextDrawAlignment(playerid, Locationtd[playerid], 2);
    PlayerTextDrawColor(playerid, Locationtd[playerid], -741092433);
    PlayerTextDrawBackgroundColor(playerid, Locationtd[playerid], 255);
    PlayerTextDrawBoxColor(playerid, Locationtd[playerid], 101);
    PlayerTextDrawUseBox(playerid, Locationtd[playerid], 0);
    PlayerTextDrawSetProportional(playerid, Locationtd[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, Locationtd[playerid], 0);

    Avenuewm[playerid] = CreatePlayerTextDraw(playerid, 634.000000, 432.000000, "www.MySunshine-rp.com");
    PlayerTextDrawFont(playerid, Avenuewm[playerid], 1);
    PlayerTextDrawLetterSize(playerid, Avenuewm[playerid], 0.200000, 1.200000);
    PlayerTextDrawTextSize(playerid, Avenuewm[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, Avenuewm[playerid], 0);
    PlayerTextDrawSetShadow(playerid, Avenuewm[playerid], 0);
    PlayerTextDrawAlignment(playerid, Avenuewm[playerid], 3);
    PlayerTextDrawColor(playerid, Avenuewm[playerid], -101);
    PlayerTextDrawBackgroundColor(playerid, Avenuewm[playerid], 255);
    PlayerTextDrawBoxColor(playerid, Avenuewm[playerid], 50);
    PlayerTextDrawUseBox(playerid, Avenuewm[playerid], 0);
    PlayerTextDrawSetProportional(playerid, Avenuewm[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, Avenuewm[playerid], 1);

    /*LocTd[playerid] = CreatePlayerTextDraw(playerid, 1.000000, 428.000000, "Willowfield");
    PlayerTextDrawFont(playerid, LocTd[playerid], 1);
    PlayerTextDrawLetterSize(playerid, LocTd[playerid], 0.533333, 1.450000);
    PlayerTextDrawTextSize(playerid, LocTd[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, LocTd[playerid], 0);
    PlayerTextDrawSetShadow(playerid, LocTd[playerid], 1);
    PlayerTextDrawAlignment(playerid, LocTd[playerid], 2);
    PlayerTextDrawColor(playerid, LocTd[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, LocTd[playerid], 255);
    PlayerTextDrawBoxColor(playerid, LocTd[playerid], 50);
    PlayerTextDrawUseBox(playerid, LocTd[playerid], 0);
    PlayerTextDrawSetProportional(playerid, LocTd[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, LocTd[playerid], 0);*/

    LocTd[playerid] = CreatePlayerTextDraw(playerid, 71.000000, 432.000000, "You are entering idlewood");
    PlayerTextDrawFont(playerid, LocTd[playerid], 1);
    PlayerTextDrawLetterSize(playerid, LocTd[playerid], 0.200000, 0.60000);
    PlayerTextDrawTextSize(playerid, LocTd[playerid], 12.000000, 640.000000);
    PlayerTextDrawSetOutline(playerid, LocTd[playerid], 1);
    PlayerTextDrawSetShadow(playerid, LocTd[playerid], 0);
    PlayerTextDrawAlignment(playerid, LocTd[playerid], 2);
    PlayerTextDrawColor(playerid, LocTd[playerid], -741092433);
    PlayerTextDrawBackgroundColor(playerid, LocTd[playerid], 255);
    PlayerTextDrawBoxColor(playerid, LocTd[playerid], 101);
    PlayerTextDrawUseBox(playerid, LocTd[playerid], 0);
    PlayerTextDrawSetProportional(playerid, LocTd[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, LocTd[playerid], 1);

    GPSLocation[playerid] = CreatePlayerTextDraw(playerid, 0.000000, 320.000000, "West, Idlewood");
    PlayerTextDrawFont(playerid, GPSLocation[playerid], 1);
    PlayerTextDrawLetterSize(playerid, GPSLocation[playerid], 0.470000, 1.500000);
    PlayerTextDrawTextSize(playerid, GPSLocation[playerid], 1280.000000, 1280.000000);
    PlayerTextDrawSetOutline(playerid, GPSLocation[playerid], 0);
    PlayerTextDrawSetShadow(playerid, GPSLocation[playerid], 1);
    PlayerTextDrawAlignment(playerid, GPSLocation[playerid], 0);
    PlayerTextDrawColor(playerid, GPSLocation[playerid], 0xFFFFFFFFFFFFFFFF);
    PlayerTextDrawBackgroundColor(playerid, GPSLocation[playerid], 255);
    PlayerTextDrawBoxColor(playerid, GPSLocation[playerid], 50);
    PlayerTextDrawUseBox(playerid, GPSLocation[playerid], 0);
    PlayerTextDrawSetProportional(playerid, GPSLocation[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, GPSLocation[playerid], 0);
}	

CreateTextDraw()
{
    MYSUNSHINE[0] = TextDrawCreate(-1.000, -1.000, "ld_dual:white");
    TextDrawLetterSize(MYSUNSHINE[0], 0.600, 2.000);
    TextDrawTextSize(MYSUNSHINE[0], 641.000, 449.500);
    TextDrawAlignment(MYSUNSHINE[0], 1);
    TextDrawColor(MYSUNSHINE[0], 255);
    TextDrawUseBox(MYSUNSHINE[0], 1);
    TextDrawBoxColor(MYSUNSHINE[0], 10);
    TextDrawSetShadow(MYSUNSHINE[0], 0);
    TextDrawSetOutline(MYSUNSHINE[0], 1);
    TextDrawBackgroundColor(MYSUNSHINE[0], 255);
    TextDrawFont(MYSUNSHINE[0], 4);
    TextDrawSetProportional(MYSUNSHINE[0], 1);

    MYSUNSHINE[1] = TextDrawCreate(320.000, 210.000, "MY:~y~SUNSHINE");
    TextDrawLetterSize(MYSUNSHINE[1], 1.289, 5.999);
    TextDrawTextSize(MYSUNSHINE[1], 0.000, 637.000);
    TextDrawAlignment(MYSUNSHINE[1], 2);
    TextDrawColor(MYSUNSHINE[1], -1);
    TextDrawSetShadow(MYSUNSHINE[1], 1);
    TextDrawSetOutline(MYSUNSHINE[1], 0);
    TextDrawBackgroundColor(MYSUNSHINE[1], 1768516095);
    TextDrawFont(MYSUNSHINE[1], 1);
    TextDrawSetProportional(MYSUNSHINE[1], 1);

    MYSUNSHINE[2] = TextDrawCreate(460.000, 206.000, "VERSION 1.0.19 MILKER");
    TextDrawLetterSize(MYSUNSHINE[2], 0.179, 0.999);
    TextDrawTextSize(MYSUNSHINE[2], 0.000, 637.000);
    TextDrawAlignment(MYSUNSHINE[2], 3);
    TextDrawColor(MYSUNSHINE[2], -1);
    TextDrawSetShadow(MYSUNSHINE[2], 1);
    TextDrawSetOutline(MYSUNSHINE[2], 0);
    TextDrawBackgroundColor(MYSUNSHINE[2], 1768516095);
    TextDrawFont(MYSUNSHINE[2], 1);
    TextDrawSetProportional(MYSUNSHINE[2], 1);

    //

    SUNSHINELOGO[0] = TextDrawCreate(320.000, 4.000, "S");
    TextDrawLetterSize(SUNSHINELOGO[0], 1.588, 3.098);
    TextDrawAlignment(SUNSHINELOGO[0], 2);
    TextDrawColor(SUNSHINELOGO[0], -65281);
    TextDrawSetShadow(SUNSHINELOGO[0], 1);
    TextDrawSetOutline(SUNSHINELOGO[0], 1);
    TextDrawBackgroundColor(SUNSHINELOGO[0], 150);
    TextDrawFont(SUNSHINELOGO[0], 1);
    TextDrawSetProportional(SUNSHINELOGO[0], 1);

    SUNSHINELOGO[1] = TextDrawCreate(320.000, 40.000, "MY:SUNSHINE");
    TextDrawLetterSize(SUNSHINELOGO[1], 0.239, 1.298);
    TextDrawAlignment(SUNSHINELOGO[1], 2);
    TextDrawColor(SUNSHINELOGO[1], -1);
    TextDrawSetShadow(SUNSHINELOGO[1], 1);
    TextDrawSetOutline(SUNSHINELOGO[1], 1);
    TextDrawBackgroundColor(SUNSHINELOGO[1], 150);
    TextDrawFont(SUNSHINELOGO[1], 1);
    TextDrawSetProportional(SUNSHINELOGO[1], 1);

    SUNSHINELOGO[2] = TextDrawCreate(320.000, 13.000, "M");
    TextDrawLetterSize(SUNSHINELOGO[2], 0.928, 3.198);
    TextDrawAlignment(SUNSHINELOGO[2], 2);
    TextDrawColor(SUNSHINELOGO[2], 512819199);
    TextDrawSetShadow(SUNSHINELOGO[2], 1);
    TextDrawSetOutline(SUNSHINELOGO[2], 1);
    TextDrawBackgroundColor(SUNSHINELOGO[2], 150);
    TextDrawFont(SUNSHINELOGO[2], 1);
    TextDrawSetProportional(SUNSHINELOGO[2], 1);

    //PngTXD
    /*LogoCostum = TextDrawCreate(293.000, -1.000, "mdl-2000:mave");
    TextDrawTextSize(LogoCostum, 58.000, 61.000);
    TextDrawAlignment(LogoCostum, 1);
    TextDrawColor(LogoCostum, -1);
    TextDrawSetShadow(LogoCostum, 0);
    TextDrawSetOutline(LogoCostum, 0);
    TextDrawBackgroundColor(LogoCostum, 255);
    TextDrawFont(LogoCostum, 4);
    TextDrawSetProportional(LogoCostum, 1);*/

    //Textdraws
    BoxStartTraining = TextDrawCreate(561.000000, 105.000000, "_");
    TextDrawFont(BoxStartTraining, 1);
    TextDrawLetterSize(BoxStartTraining, 0.600000, 3.949994);
    TextDrawTextSize(BoxStartTraining, 298.500000, 96.000000);
    TextDrawSetOutline(BoxStartTraining, 1);
    TextDrawSetShadow(BoxStartTraining, 0);
    TextDrawAlignment(BoxStartTraining, 2);
    TextDrawColor(BoxStartTraining, -1);
    TextDrawBackgroundColor(BoxStartTraining, 255);
    TextDrawBoxColor(BoxStartTraining, 210);
    TextDrawUseBox(BoxStartTraining, 1);
    TextDrawSetProportional(BoxStartTraining, 1);
    TextDrawSetSelectable(BoxStartTraining, 0);

    BoxTraining = TextDrawCreate(561.000000, 105.000000, "_");
    TextDrawFont(BoxTraining, 1);
    TextDrawLetterSize(BoxTraining, 0.600000, 7.249993);
    TextDrawTextSize(BoxTraining, 298.500000, 96.000000);
    TextDrawSetOutline(BoxTraining, 1);
    TextDrawSetShadow(BoxTraining, 0);
    TextDrawAlignment(BoxTraining, 2);
    TextDrawColor(BoxTraining, -1);
    TextDrawBackgroundColor(BoxTraining, 255);
    TextDrawBoxColor(BoxTraining, 210);
    TextDrawUseBox(BoxTraining, 1);
    TextDrawSetProportional(BoxTraining, 1);
    TextDrawSetSelectable(BoxTraining, 0);

    EventTD[0] = TextDrawCreate(575.000000, 110.000000, "_");
	TextDrawFont(EventTD[0], 1);
	TextDrawLetterSize(EventTD[0], 0.600000, 5.399991);
	TextDrawTextSize(EventTD[0], 298.500000, 119.000000);
	TextDrawSetOutline(EventTD[0], 1);
	TextDrawSetShadow(EventTD[0], 0);
	TextDrawAlignment(EventTD[0], 2);
	TextDrawColor(EventTD[0], -1);
	TextDrawBackgroundColor(EventTD[0], 255);
	TextDrawBoxColor(EventTD[0], 35734);
	TextDrawUseBox(EventTD[0], 1);
	TextDrawSetProportional(EventTD[0], 1);
	TextDrawSetSelectable(EventTD[0], 0);

	EventTD[1] = TextDrawCreate(513.000000, 109.000000, "-Score- target:_100 team_a:_100 team_b:_10");
	TextDrawFont(EventTD[1], 3);
	TextDrawLetterSize(EventTD[1], 0.345833, 1.350000);
	TextDrawTextSize(EventTD[1], 608.000000, 17.000000);
	TextDrawSetOutline(EventTD[1], 1);
	TextDrawSetShadow(EventTD[1], 0);
	TextDrawAlignment(EventTD[1], 1);
	TextDrawColor(EventTD[1], -1);
	TextDrawBackgroundColor(EventTD[1], 255);
	TextDrawBoxColor(EventTD[1], 0);
	TextDrawUseBox(EventTD[1], 1);
	TextDrawSetProportional(EventTD[1], 1);
	TextDrawSetSelectable(EventTD[1], 0);

    PlayerCrateTD = TextDrawCreate(552.000000, 110.000000, "_");
    TextDrawFont(PlayerCrateTD, 1);
    TextDrawLetterSize(PlayerCrateTD, 0.600000, 6.099998);
    TextDrawTextSize(PlayerCrateTD, 298.500000, 95.000000);
    TextDrawSetOutline(PlayerCrateTD, 1);
    TextDrawSetShadow(PlayerCrateTD, 0);
    TextDrawAlignment(PlayerCrateTD, 2);
    TextDrawColor(PlayerCrateTD, -1);
    TextDrawBackgroundColor(PlayerCrateTD, 255);
    TextDrawBoxColor(PlayerCrateTD, 190);
    TextDrawUseBox(PlayerCrateTD, 1);
    TextDrawSetProportional(PlayerCrateTD, 1);
    TextDrawSetSelectable(PlayerCrateTD, 0);

    DollarCents = TextDrawCreate(543.000000, 78.000000, ",   .");
    TextDrawFont(DollarCents, 3);
    TextDrawLetterSize(DollarCents, 0.490000, 2.400000);
    TextDrawTextSize(DollarCents, 1280.000000, 1280.000000);
    TextDrawSetOutline(DollarCents, 0);
    TextDrawSetShadow(DollarCents, 1);
    TextDrawAlignment(DollarCents, 0);
    TextDrawColor(DollarCents, 0x2F5A26FF);
    TextDrawBackgroundColor(DollarCents, 255);
    TextDrawBoxColor(DollarCents, 50);
    TextDrawUseBox(DollarCents, 0);
    TextDrawSetProportional(DollarCents, 1);
    TextDrawSetSelectable(DollarCents, 0);

	Webtd[0] = TextDrawCreate(454.000000, 420.000000, "~w~Forum: ''~y~jomokgamers.org~w~''~n~~w~UCP: ''~y~ucp.jg-gta.com~w~''");
	TextDrawFont(Webtd[0], 3);
	TextDrawLetterSize(Webtd[0], 0.299999, 1.000000);
	TextDrawTextSize(Webtd[0], 1280.000000, 1280.000000);
	TextDrawSetOutline(Webtd[0], 1);
	TextDrawSetShadow(Webtd[0], 1);
	TextDrawAlignment(Webtd[0], 0);
	TextDrawColor(Webtd[0], -1);
	TextDrawBackgroundColor(Webtd[0], 255);
	TextDrawBoxColor(Webtd[0], 50);
	TextDrawUseBox(Webtd[0], 0);
	TextDrawSetProportional(Webtd[0], 1);
	TextDrawSetSelectable(Webtd[0], 0);

	Webtd[1] = TextDrawCreate(454.000000, 420.000000, "Join our GTA V Server:~n~~w~JGvcrp at ~y~RageMP");
	TextDrawFont(Webtd[1], 3);
	TextDrawLetterSize(Webtd[1], 0.299999, 1.000000);
	TextDrawTextSize(Webtd[1], 400.000000, 17.000000);
	TextDrawSetOutline(Webtd[1], 1);
	TextDrawSetShadow(Webtd[1], 1);
	TextDrawAlignment(Webtd[1], 0);
	TextDrawColor(Webtd[1], -1);
	TextDrawBackgroundColor(Webtd[1], 255);
	TextDrawBoxColor(Webtd[1], 50);
	TextDrawUseBox(Webtd[1], 0);
	TextDrawSetProportional(Webtd[1], 1);
	TextDrawSetSelectable(Webtd[1], 0);

	Webtd[2] = TextDrawCreate(454.000000, 420.000000, "~w~RULES: ''~y~mysunshine/rules~w~''~n~~w~GUIDES: ''~y~mysunshine/guide~w~''");
	TextDrawFont(Webtd[2], 3);
	TextDrawLetterSize(Webtd[2], 0.299999, 1.000000);
	TextDrawTextSize(Webtd[2], 1280.000000, 1280.000000);
	TextDrawSetOutline(Webtd[2], 1);
	TextDrawSetShadow(Webtd[2], 1);
	TextDrawAlignment(Webtd[2], 0);
	TextDrawColor(Webtd[2], -1);
	TextDrawBackgroundColor(Webtd[2], 255);
	TextDrawBoxColor(Webtd[2], 50);
	TextDrawUseBox(Webtd[2], 0);
	TextDrawSetProportional(Webtd[2], 1);
	TextDrawSetSelectable(Webtd[2], 0);


    Date = TextDrawCreate(0.000000, 430.000000, "Mon, 29 Jul 2024");
    TextDrawFont(Date, 1);
    TextDrawLetterSize(Date, 0.470000, 1.500000);
    TextDrawAlignment(Date, 0);
    TextDrawColor(Date, 0xFFFFFFFFFFFFFFFF);
    TextDrawSetProportional(Date, 1);
    TextDrawTextSize(Date, 1280.000000, 1280.000000);
    TextDrawSetShadow(Date, 1);
    TextDrawSetOutline(Date, 0);
    TextDrawBackgroundColor(Date, 0x000000FF);
    TextDrawSetSelectable(Date, 0);

    /*Date = TextDrawCreate(71.000000, 430.000000, "24 March 2021");
    TextDrawFont(Date, 1);
    TextDrawLetterSize(Date, 0.308332, 1.349998);
    TextDrawTextSize(Date, 404.500000, 114.500000);
    TextDrawSetOutline(Date, 1);
    TextDrawSetShadow(Date, 0);
    TextDrawAlignment(Date, 2);
    TextDrawColor(Date, -1);
    TextDrawBackgroundColor(Date, 255);
    TextDrawBoxColor(Date, 50);
    TextDrawSetProportional(Date, 1);
    TextDrawSetSelectable(Date, 0);*/

    Time = TextDrawCreate(544.000000, 27.000000, "-:-:-");
    TextDrawFont(Time, 1);
    TextDrawLetterSize(Time, 0.500000, 1.800000);
    TextDrawTextSize(Time, 1280.000000, 1280.000000);
    TextDrawSetOutline(Time, 1);
    TextDrawSetShadow(Time, 2);
    TextDrawAlignment(Time, 0);
    TextDrawColor(Time, 0xFFFFFFFFFFFFFFFF);
    TextDrawBackgroundColor(Time, 255);
    TextDrawBoxColor(Time, 50);
    TextDrawUseBox(Time, 0);
    TextDrawSetProportional(Time, 1);
    TextDrawSetSelectable(Time, 0);

	avenue = TextDrawCreate(302.000000, 3.000000, "MySunshine");
	TextDrawFont(avenue, 3);
	TextDrawLetterSize(avenue, 0.341666, 1.500000);
	TextDrawAlignment(avenue, 0);
	TextDrawColor(avenue, 0xFFFFFFFFFFFFFFFF);
	TextDrawSetProportional(avenue, 1);
	TextDrawTextSize(avenue, 400.000000, 17.000000);
	TextDrawSetShadow(avenue, 0);
	TextDrawSetOutline(avenue, 1);
	TextDrawBackgroundColor(avenue, 0x000000FF);
	TextDrawSetSelectable(avenue, 0);

	roleplay = TextDrawCreate(297.000000, 10.000000, "Roleplay");
	TextDrawFont(roleplay, 0);
	TextDrawLetterSize(roleplay, 0.487500, 1.399999);
	TextDrawAlignment(roleplay, 0);
	TextDrawColor(roleplay, 0xFFFFFFFFC0C0C0FF);
	TextDrawSetProportional(roleplay, 1);
	TextDrawTextSize(roleplay, 400.000000, 17.000000);
	TextDrawSetShadow(roleplay, 0);
	TextDrawSetOutline(roleplay, 1);
	TextDrawBackgroundColor(roleplay, 0x000000FF);
	TextDrawSetSelectable(roleplay, 0);

	injuredtextdraw = TextDrawCreate(-2.000000, -8.000000, "LD_SPAC:white");
	TextDrawFont(injuredtextdraw, 4);
	TextDrawLetterSize(injuredtextdraw, 0.480000, 1.120000);
	TextDrawAlignment(injuredtextdraw, 0);
	TextDrawColor(injuredtextdraw, 0xFFFFFFFFFF000050);
	TextDrawSetProportional(injuredtextdraw, 1);
	TextDrawTextSize(injuredtextdraw, 647.000000, 517.000000);
	TextDrawSetShadow(injuredtextdraw, 0);
	TextDrawSetOutline(injuredtextdraw, 0);
	TextDrawBackgroundColor(injuredtextdraw, 0x000000FF);
	TextDrawSetSelectable(injuredtextdraw, 0);

    /*Time = TextDrawCreate(544.000000, 27.000000, "10:20:33");
    TextDrawFont(Time, 1);
    TextDrawLetterSize(Time, 0.500000, 1.800000);
    TextDrawTextSize(Time, 1280.000000, 1280.000000);
    TextDrawSetOutline(Time, 1);
    TextDrawSetShadow(Time, 2);
    TextDrawAlignment(Time, 0);
    TextDrawColor(Time, -1);
    TextDrawBackgroundColor(Time, 255);
    TextDrawBoxColor(Time, 50);
    TextDrawUseBox(Time, 0);
    TextDrawSetProportional(Time, 1);
    TextDrawSetSelectable(Time, 0);*/

	HouseLight = TextDrawCreate(666.000000, 0.000000, "_");
	TextDrawAlignment(HouseLight, 3);
	TextDrawBackgroundColor(HouseLight, 255);
	TextDrawFont(HouseLight, 1);
	TextDrawLetterSize(HouseLight, 1.190000, 50.099998);
	TextDrawColor(HouseLight, -1);
	TextDrawSetOutline(HouseLight, 0);
	TextDrawSetProportional(HouseLight, 1);
	TextDrawSetShadow(HouseLight, 1);
	TextDrawUseBox(HouseLight, 1);
	TextDrawBoxColor(HouseLight, 0x141313AA);
	TextDrawTextSize(HouseLight, 115.000000, 166.000000);
	TextDrawSetSelectable(HouseLight, 0);

    //NOTIF
    notifTD[0] = TextDrawCreate(361.000000, 24.000000, "ld_dual:white");
    TextDrawFont(notifTD[0], 4);
    TextDrawLetterSize(notifTD[0], 0.600000, 2.000000);
    TextDrawTextSize(notifTD[0], 115.000000, 11.000000);
    TextDrawSetOutline(notifTD[0], 1);
    TextDrawSetShadow(notifTD[0], 0);
    TextDrawAlignment(notifTD[0], 1);
    TextDrawColor(notifTD[0], 595705087);
    TextDrawBackgroundColor(notifTD[0], 255);
    TextDrawBoxColor(notifTD[0], 50);
    TextDrawUseBox(notifTD[0], 1);
    TextDrawSetProportional(notifTD[0], 1);
    TextDrawSetSelectable(notifTD[0], 0);

    notifTD[1] = TextDrawCreate(472.000000, 25.000000, "Tes_123 Menjual kendaraannya ke Tes_456");
    TextDrawFont(notifTD[1], 1);
    TextDrawLetterSize(notifTD[1], 0.129167, 0.750000);
    TextDrawTextSize(notifTD[1], 400.000000, 17.000000);
    TextDrawSetOutline(notifTD[1], 0);
    TextDrawSetShadow(notifTD[1], 0);
    TextDrawAlignment(notifTD[1], 3);
    TextDrawColor(notifTD[1], -1);
    TextDrawBackgroundColor(notifTD[1], 255);
    TextDrawBoxColor(notifTD[1], 50);
    TextDrawUseBox(notifTD[1], 0);
    TextDrawSetProportional(notifTD[1], 1);
    TextDrawSetSelectable(notifTD[1], 0);

    vRadio[0] = TextDrawCreate(314.000000, 173.000000, "_");
    TextDrawFont(vRadio[0], 1);
    TextDrawLetterSize(vRadio[0], 0.600000, 13.300003);
    TextDrawTextSize(vRadio[0], 298.500000, 188.500000);
    TextDrawSetOutline(vRadio[0], 1);
    TextDrawSetShadow(vRadio[0], 0);
    TextDrawAlignment(vRadio[0], 2);
    TextDrawColor(vRadio[0], -1);
    TextDrawBackgroundColor(vRadio[0], 255);
    TextDrawBoxColor(vRadio[0], 1296911871);
    TextDrawUseBox(vRadio[0], 1);
    TextDrawSetProportional(vRadio[0], 1);
    TextDrawSetSelectable(vRadio[0], 0);

    vRadio[1] = TextDrawCreate(314.000000, 185.000000, "_");
    TextDrawFont(vRadio[1], 1);
    TextDrawLetterSize(vRadio[1], 0.600000, 12.049998);
    TextDrawTextSize(vRadio[1], 298.500000, 182.500000);
    TextDrawSetOutline(vRadio[1], 1);
    TextDrawSetShadow(vRadio[1], 0);
    TextDrawAlignment(vRadio[1], 2);
    TextDrawColor(vRadio[1], -1);
    TextDrawBackgroundColor(vRadio[1], 255);
    TextDrawBoxColor(vRadio[1], 255);
    TextDrawUseBox(vRadio[1], 1);
    TextDrawSetProportional(vRadio[1], 1);
    TextDrawSetSelectable(vRadio[1], 0);

    vRadio[2] = TextDrawCreate(285.000000, 166.000000, "Audio HD");
    TextDrawFont(vRadio[2], 1);
    TextDrawLetterSize(vRadio[2], 0.295832, 1.649999);
    TextDrawTextSize(vRadio[2], 400.000000, 17.000000);
    TextDrawSetOutline(vRadio[2], 1);
    TextDrawSetShadow(vRadio[2], 0);
    TextDrawAlignment(vRadio[2], 1);
    TextDrawColor(vRadio[2], -1);
    TextDrawBackgroundColor(vRadio[2], 255);
    TextDrawBoxColor(vRadio[2], 50);
    TextDrawUseBox(vRadio[2], 0);
    TextDrawSetProportional(vRadio[2], 1);
    TextDrawSetSelectable(vRadio[2], 0);

    vRadio[3] = TextDrawCreate(287.000000, 206.000000, "ld_beat:right");
    TextDrawFont(vRadio[3], 4);
    TextDrawLetterSize(vRadio[3], 0.600000, 2.000000);
    TextDrawTextSize(vRadio[3], 15.000000, 18.000000);
    TextDrawSetOutline(vRadio[3], 1);
    TextDrawSetShadow(vRadio[3], 0);
    TextDrawAlignment(vRadio[3], 1);
    TextDrawColor(vRadio[3], 255);
    TextDrawBackgroundColor(vRadio[3], 255);
    TextDrawBoxColor(vRadio[3], 50);
    TextDrawUseBox(vRadio[3], 1);
    TextDrawSetProportional(vRadio[3], 1);
    TextDrawSetSelectable(vRadio[3], 0);

    vRadio[4] = TextDrawCreate(326.000000, 207.000000, "l");
    TextDrawFont(vRadio[4], 1);
    TextDrawLetterSize(vRadio[4], 0.295832, 1.649999);
    TextDrawTextSize(vRadio[4], 400.000000, 17.000000);
    TextDrawSetOutline(vRadio[4], 1);
    TextDrawSetShadow(vRadio[4], 0);
    TextDrawAlignment(vRadio[4], 1);
    TextDrawColor(vRadio[4], 255);
    TextDrawBackgroundColor(vRadio[4], 255);
    TextDrawBoxColor(vRadio[4], 50);
    TextDrawUseBox(vRadio[4], 0);
    TextDrawSetProportional(vRadio[4], 1);
    TextDrawSetSelectable(vRadio[4], 0);

    vRadio[5] = TextDrawCreate(332.000000, 207.000000, "l");
    TextDrawFont(vRadio[5], 1);
    TextDrawLetterSize(vRadio[5], 0.295832, 1.649999);
    TextDrawTextSize(vRadio[5], 400.000000, 17.000000);
    TextDrawSetOutline(vRadio[5], 1);
    TextDrawSetShadow(vRadio[5], 0);
    TextDrawAlignment(vRadio[5], 1);
    TextDrawColor(vRadio[5], 255);
    TextDrawBackgroundColor(vRadio[5], 255);
    TextDrawBoxColor(vRadio[5], 50);
    TextDrawUseBox(vRadio[5], 0);
    TextDrawSetProportional(vRadio[5], 1);
    TextDrawSetSelectable(vRadio[5], 0);

    vRadio[6] = TextDrawCreate(274.000000, 287.000000, "_");
    TextDrawFont(vRadio[6], 1);
    TextDrawLetterSize(vRadio[6], 0.600000, 0.500001);
    TextDrawTextSize(vRadio[6], 298.500000, 99.000000);
    TextDrawSetOutline(vRadio[6], 1);
    TextDrawSetShadow(vRadio[6], 0);
    TextDrawAlignment(vRadio[6], 2);
    TextDrawColor(vRadio[6], -1);
    TextDrawBackgroundColor(vRadio[6], 255);
    TextDrawBoxColor(vRadio[6], -121);
    TextDrawUseBox(vRadio[6], 1);
    TextDrawSetProportional(vRadio[6], 1);
    TextDrawSetSelectable(vRadio[6], 0);

    vRadio[7] = TextDrawCreate(288.000000, 230.000000, "Playing:");
    TextDrawFont(vRadio[7], 1);
    TextDrawLetterSize(vRadio[7], 0.287499, 1.149999);
    TextDrawTextSize(vRadio[7], 400.000000, 17.000000);
    TextDrawSetOutline(vRadio[7], 1);
    TextDrawSetShadow(vRadio[7], 0);
    TextDrawAlignment(vRadio[7], 1);
    TextDrawColor(vRadio[7], -1);
    TextDrawBackgroundColor(vRadio[7], 255);
    TextDrawBoxColor(vRadio[7], 50);
    TextDrawUseBox(vRadio[7], 0);
    TextDrawSetProportional(vRadio[7], 1);
    TextDrawSetSelectable(vRadio[7], 0);

    vRadio[8] = TextDrawCreate(384.000000, 287.000000, "_");
    TextDrawFont(vRadio[8], 1);
    TextDrawLetterSize(vRadio[8], 0.600000, 0.500001);
    TextDrawTextSize(vRadio[8], 298.500000, 35.000000);
    TextDrawSetOutline(vRadio[8], 1);
    TextDrawSetShadow(vRadio[8], 0);
    TextDrawAlignment(vRadio[8], 2);
    TextDrawColor(vRadio[8], -1);
    TextDrawBackgroundColor(vRadio[8], 255);
    TextDrawBoxColor(vRadio[8], -121);
    TextDrawUseBox(vRadio[8], 1);
    TextDrawSetProportional(vRadio[8], 1);
    TextDrawSetSelectable(vRadio[8], 0);
}
