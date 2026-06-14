#include <YSI\y_hooks>
//HBE SA STYLE
new Text:SaStyleTD[6];
new PlayerText:SAPHungerTD[MAX_PLAYERS];
new PlayerText:SAPThirstTD[MAX_PLAYERS];
new Text:SAStyleVehicleTD[10];
new PlayerText:SAVNameTD[MAX_PLAYERS];
new PlayerText:SAVHealthTD[MAX_PLAYERS];
new PlayerText:SAVFuelTD[MAX_PLAYERS];
new PlayerText:SAPVSpeedTD[MAX_PLAYERS];
//Variables HBE Simple
new Text:simpletd[10];
new PlayerText:JGHUNGER[MAX_PLAYERS];
new PlayerText:JGTHIRST[MAX_PLAYERS];
new PlayerText:JGVHP[MAX_PLAYERS];
new PlayerText:JGVSPEED[MAX_PLAYERS];
new PlayerText:JGVFUEL[MAX_PLAYERS];
//Variables HBE Old School
new Text:SimpleStyleTD[4];
new PlayerText:PHungerTD[MAX_PLAYERS];
new PlayerText:PThirstTD[MAX_PLAYERS];
new Text:SimpleVehicleTD[5];
new PlayerText:VSpeedTD[MAX_PLAYERS];
new PlayerText:VFuelTD[MAX_PLAYERS];
new PlayerText:VHealthTD[MAX_PLAYERS];
new PlayerText:VNameTD[MAX_PLAYERS];

    PlayerHBECreate(playerid) {
    //hbe sa style
    SAPHungerTD[playerid] = CreatePlayerTextDraw(playerid, 42.000000, 229.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, SAPHungerTD[playerid], 4);
    PlayerTextDrawLetterSize(playerid, SAPHungerTD[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, SAPHungerTD[playerid], 53.000000, 8.000000);
    PlayerTextDrawSetOutline(playerid, SAPHungerTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, SAPHungerTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, SAPHungerTD[playerid], 1);
    PlayerTextDrawColor(playerid, SAPHungerTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, SAPHungerTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, SAPHungerTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, SAPHungerTD[playerid], 1);
    PlayerTextDrawSetProportional(playerid, SAPHungerTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, SAPHungerTD[playerid], 0);

    SAPThirstTD[playerid] = CreatePlayerTextDraw(playerid, 42.000000, 246.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, SAPThirstTD[playerid], 4);
    PlayerTextDrawLetterSize(playerid, SAPThirstTD[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, SAPThirstTD[playerid], 53.000000, 8.000000);
    PlayerTextDrawSetOutline(playerid, SAPThirstTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, SAPThirstTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, SAPThirstTD[playerid], 1);
    PlayerTextDrawColor(playerid, SAPThirstTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, SAPThirstTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, SAPThirstTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, SAPThirstTD[playerid], 1);
    PlayerTextDrawSetProportional(playerid, SAPThirstTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, SAPThirstTD[playerid], 0);

    //hbe sa style vehicle
    SAVNameTD[playerid] = CreatePlayerTextDraw(playerid, 52.000000, 266.000000, "Police car (lspd)");
    PlayerTextDrawFont(playerid, SAVNameTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, SAVNameTD[playerid], 0.262499, 1.450000);
    PlayerTextDrawTextSize(playerid, SAVNameTD[playerid], 400.000000, 89.000000);
    PlayerTextDrawSetOutline(playerid, SAVNameTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, SAVNameTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, SAVNameTD[playerid], 2);
    PlayerTextDrawColor(playerid, SAVNameTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, SAVNameTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, SAVNameTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, SAVNameTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, SAVNameTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, SAVNameTD[playerid], 0);

    SAVHealthTD[playerid] = CreatePlayerTextDraw(playerid, 106.000000, 266.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, SAVHealthTD[playerid], 4);
    PlayerTextDrawLetterSize(playerid, SAVHealthTD[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, SAVHealthTD[playerid], 7.000000, -42.000000);
    PlayerTextDrawSetOutline(playerid, SAVHealthTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, SAVHealthTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, SAVHealthTD[playerid], 1);
    PlayerTextDrawColor(playerid, SAVHealthTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, SAVHealthTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, SAVHealthTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, SAVHealthTD[playerid], 1);
    PlayerTextDrawSetProportional(playerid, SAVHealthTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, SAVHealthTD[playerid], 0);

    SAVFuelTD[playerid] = CreatePlayerTextDraw(playerid, 123.000000, 266.000000, "ld_drv:blkdot");
    PlayerTextDrawFont(playerid, SAVFuelTD[playerid], 4);
    PlayerTextDrawLetterSize(playerid, SAVFuelTD[playerid], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, SAVFuelTD[playerid], 7.000000, -42.000000);
    PlayerTextDrawSetOutline(playerid, SAVFuelTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, SAVFuelTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, SAVFuelTD[playerid], 1);
    PlayerTextDrawColor(playerid, SAVFuelTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, SAVFuelTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, SAVFuelTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, SAVFuelTD[playerid], 1);
    PlayerTextDrawSetProportional(playerid, SAVFuelTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, SAVFuelTD[playerid], 0);

    SAPVSpeedTD[playerid] = CreatePlayerTextDraw(playerid, 118.000000, 287.000000, "0");
    PlayerTextDrawFont(playerid, SAPVSpeedTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, SAPVSpeedTD[playerid], 0.304166, 1.549999);
    PlayerTextDrawTextSize(playerid, SAPVSpeedTD[playerid], 400.000000, 21.500000);
    PlayerTextDrawSetOutline(playerid, SAPVSpeedTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, SAPVSpeedTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, SAPVSpeedTD[playerid], 2);
    PlayerTextDrawColor(playerid, SAPVSpeedTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, SAPVSpeedTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, SAPVSpeedTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, SAPVSpeedTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, SAPVSpeedTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, SAPVSpeedTD[playerid], 0);

    //Player Textdraws HBE Old School
    PHungerTD[playerid] = CreatePlayerTextDraw(playerid, 547.000000, 424.000000, "100%");
    PlayerTextDrawFont(playerid, PHungerTD[playerid], 2);
    PlayerTextDrawLetterSize(playerid, PHungerTD[playerid], 0.275000, 1.400000);
    PlayerTextDrawTextSize(playerid, PHungerTD[playerid], 607.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PHungerTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, PHungerTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, PHungerTD[playerid], 1);
    PlayerTextDrawColor(playerid, PHungerTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, PHungerTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, PHungerTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, PHungerTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, PHungerTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, PHungerTD[playerid], 0);

    PThirstTD[playerid] = CreatePlayerTextDraw(playerid, 603.000000, 424.000000, "100%");
    PlayerTextDrawFont(playerid, PThirstTD[playerid], 2);
    PlayerTextDrawLetterSize(playerid, PThirstTD[playerid], 0.275000, 1.400000);
    PlayerTextDrawTextSize(playerid, PThirstTD[playerid], 607.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PThirstTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, PThirstTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, PThirstTD[playerid], 1);
    PlayerTextDrawColor(playerid, PThirstTD[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, PThirstTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, PThirstTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, PThirstTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, PThirstTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, PThirstTD[playerid], 0);

    //Old School style vehicle
    VSpeedTD[playerid] = CreatePlayerTextDraw(playerid, 534.000000, 349.000000, "48");
    PlayerTextDrawFont(playerid, VSpeedTD[playerid], 3);
    PlayerTextDrawLetterSize(playerid, VSpeedTD[playerid], 0.391665, 1.500000);
    PlayerTextDrawTextSize(playerid, VSpeedTD[playerid], 565.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, VSpeedTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, VSpeedTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, VSpeedTD[playerid], 1);
    PlayerTextDrawColor(playerid, VSpeedTD[playerid], 1097458175);
    PlayerTextDrawBackgroundColor(playerid, VSpeedTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, VSpeedTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, VSpeedTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, VSpeedTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, VSpeedTD[playerid], 0);

    VFuelTD[playerid] = CreatePlayerTextDraw(playerid, 557.000000, 362.000000, "99L");
    PlayerTextDrawFont(playerid, VFuelTD[playerid], 2);
    PlayerTextDrawLetterSize(playerid, VFuelTD[playerid], 0.224999, 1.399999);
    PlayerTextDrawTextSize(playerid, VFuelTD[playerid], 565.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, VFuelTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, VFuelTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, VFuelTD[playerid], 1);
    PlayerTextDrawColor(playerid, VFuelTD[playerid], -764862721);
    PlayerTextDrawBackgroundColor(playerid, VFuelTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, VFuelTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, VFuelTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, VFuelTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, VFuelTD[playerid], 0);

    VHealthTD[playerid] = CreatePlayerTextDraw(playerid, 567.000000, 374.000000, "100%");
    PlayerTextDrawFont(playerid, VHealthTD[playerid], 2);
    PlayerTextDrawLetterSize(playerid, VHealthTD[playerid], 0.224999, 1.399999);
    PlayerTextDrawTextSize(playerid, VHealthTD[playerid], 565.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, VHealthTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, VHealthTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, VHealthTD[playerid], 1);
    PlayerTextDrawColor(playerid, VHealthTD[playerid], -16776961);
    PlayerTextDrawBackgroundColor(playerid, VHealthTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, VHealthTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, VHealthTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, VHealthTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, VHealthTD[playerid], 0);

    VNameTD[playerid] = CreatePlayerTextDraw(playerid, 569.000000, 387.000000, "sultan");
    PlayerTextDrawFont(playerid, VNameTD[playerid], 2);
    PlayerTextDrawLetterSize(playerid, VNameTD[playerid], 0.224999, 1.399999);
    PlayerTextDrawTextSize(playerid, VNameTD[playerid], 635.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, VNameTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, VNameTD[playerid], 0);
    PlayerTextDrawAlignment(playerid, VNameTD[playerid], 1);
    PlayerTextDrawColor(playerid, VNameTD[playerid], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, VNameTD[playerid], 255);
    PlayerTextDrawBoxColor(playerid, VNameTD[playerid], 50);
    PlayerTextDrawUseBox(playerid, VNameTD[playerid], 0);
    PlayerTextDrawSetProportional(playerid, VNameTD[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, VNameTD[playerid], 0);
    
    //HBE MINIMALIST
	JGVSPEED[playerid] = CreatePlayerTextDraw(playerid, 636.000000, 288.000000, "0 mph");
	PlayerTextDrawFont(playerid, JGVSPEED[playerid], 3);
	PlayerTextDrawLetterSize(playerid, JGVSPEED[playerid], 0.250000, 1.209999);
	PlayerTextDrawAlignment(playerid, JGVSPEED[playerid], 3);
	PlayerTextDrawColor(playerid, JGVSPEED[playerid], 0xFFFFFFFFFFFFFFFF);
	PlayerTextDrawSetProportional(playerid, JGVSPEED[playerid], 1);
	PlayerTextDrawTextSize(playerid, JGVSPEED[playerid], 0.000000, 0.000000);
	PlayerTextDrawSetShadow(playerid, JGVSPEED[playerid], 0);
	PlayerTextDrawSetOutline(playerid, JGVSPEED[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, JGVSPEED[playerid], 0x000000FF);
	PlayerTextDrawSetSelectable(playerid, JGVSPEED[playerid], 0);

	JGVHP[playerid] = CreatePlayerTextDraw(playerid, 636.000000, 306.000000, "100%");
	PlayerTextDrawFont(playerid, JGVHP[playerid], 3);
	PlayerTextDrawLetterSize(playerid, JGVHP[playerid], 0.300000, 1.300000);
	PlayerTextDrawAlignment(playerid, JGVHP[playerid], 3);
	PlayerTextDrawColor(playerid, JGVHP[playerid], 0xFFFFFFFFFFFFFFFF);
	PlayerTextDrawSetProportional(playerid, JGVHP[playerid], 1);
	PlayerTextDrawTextSize(playerid, JGVHP[playerid], 0.000000, 0.000000);
	PlayerTextDrawSetShadow(playerid, JGVHP[playerid], 0);
	PlayerTextDrawSetOutline(playerid, JGVHP[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, JGVHP[playerid], 0x000000FF);
	PlayerTextDrawSetSelectable(playerid, JGVHP[playerid], 0);

	JGVFUEL[playerid] = CreatePlayerTextDraw(playerid, 636.000000, 329.000000, "100%");
	PlayerTextDrawFont(playerid, JGVFUEL[playerid], 3);
	PlayerTextDrawLetterSize(playerid, JGVFUEL[playerid], 0.300000, 1.300000);
	PlayerTextDrawAlignment(playerid, JGVFUEL[playerid], 3);
	PlayerTextDrawColor(playerid, JGVFUEL[playerid], 0xFFFFFFFFFFFFFFFF);
	PlayerTextDrawSetProportional(playerid, JGVFUEL[playerid], 1);
	PlayerTextDrawTextSize(playerid, JGVFUEL[playerid], 0.000000, 0.000000);
	PlayerTextDrawSetShadow(playerid, JGVFUEL[playerid], 0);
	PlayerTextDrawSetOutline(playerid, JGVFUEL[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, JGVFUEL[playerid], 0x000000FF);
	PlayerTextDrawSetSelectable(playerid, JGVFUEL[playerid], 0);

	JGTHIRST[playerid] = CreatePlayerTextDraw(playerid, 636.000000, 387.000000, "90%");
	PlayerTextDrawFont(playerid, JGTHIRST[playerid], 3);
	PlayerTextDrawLetterSize(playerid, JGTHIRST[playerid], 0.400000, 1.500000);
	PlayerTextDrawAlignment(playerid, JGTHIRST[playerid], 3);
	PlayerTextDrawColor(playerid, JGTHIRST[playerid], 0xFFFFFFFFFFFFFFFF);
	PlayerTextDrawSetProportional(playerid, JGTHIRST[playerid], 1);
	PlayerTextDrawTextSize(playerid, JGTHIRST[playerid], 0.000000, 0.000000);
	PlayerTextDrawSetShadow(playerid, JGTHIRST[playerid], 0);
	PlayerTextDrawSetOutline(playerid, JGTHIRST[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, JGTHIRST[playerid], 0x000000FF);
	PlayerTextDrawSetSelectable(playerid, JGTHIRST[playerid], 0);

	JGHUNGER[playerid] = CreatePlayerTextDraw(playerid, 636.000000, 362.000000, "77%");
	PlayerTextDrawFont(playerid, JGHUNGER[playerid], 3);
	PlayerTextDrawLetterSize(playerid, JGHUNGER[playerid], 0.400000, 1.500000);
	PlayerTextDrawAlignment(playerid, JGHUNGER[playerid], 3);
	PlayerTextDrawColor(playerid, JGHUNGER[playerid], 0xFFFFFFFFFFFFFFFF);
	PlayerTextDrawSetProportional(playerid, JGHUNGER[playerid], 1);
	PlayerTextDrawTextSize(playerid, JGHUNGER[playerid], 0.000000, 0.000000);
	PlayerTextDrawSetShadow(playerid, JGHUNGER[playerid], 0);
	PlayerTextDrawSetOutline(playerid, JGHUNGER[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, JGHUNGER[playerid], 0x000000FF);
	PlayerTextDrawSetSelectable(playerid, JGHUNGER[playerid], 0);
}

HBECreate() {
    //Hbe sa style
    SaStyleTD[0] = TextDrawCreate(3.000000, 220.000000, "ld_drv:blkdot");
    TextDrawFont(SaStyleTD[0], 4);
    TextDrawLetterSize(SaStyleTD[0], 0.600000, 2.000000);
    TextDrawTextSize(SaStyleTD[0], 97.000000, 41.500000);
    TextDrawSetOutline(SaStyleTD[0], 1);
    TextDrawSetShadow(SaStyleTD[0], 0);
    TextDrawAlignment(SaStyleTD[0], 1);
    TextDrawColor(SaStyleTD[0], 234);
    TextDrawBackgroundColor(SaStyleTD[0], 255);
    TextDrawBoxColor(SaStyleTD[0], 50);
    TextDrawUseBox(SaStyleTD[0], 1);
    TextDrawSetProportional(SaStyleTD[0], 1);
    TextDrawSetSelectable(SaStyleTD[0], 0);

    SaStyleTD[1] = TextDrawCreate(2.000000, 206.000000, "Stats");
    TextDrawFont(SaStyleTD[1], 0);
    TextDrawLetterSize(SaStyleTD[1], 0.600000, 2.000000);
    TextDrawTextSize(SaStyleTD[1], 400.000000, 17.000000);
    TextDrawSetOutline(SaStyleTD[1], 1);
    TextDrawSetShadow(SaStyleTD[1], 0);
    TextDrawAlignment(SaStyleTD[1], 1);
    TextDrawColor(SaStyleTD[1], -1);
    TextDrawBackgroundColor(SaStyleTD[1], 255);
    TextDrawBoxColor(SaStyleTD[1], 50);
    TextDrawUseBox(SaStyleTD[1], 0);
    TextDrawSetProportional(SaStyleTD[1], 1);
    TextDrawSetSelectable(SaStyleTD[1], 0);

    SaStyleTD[2] = TextDrawCreate(6.000000, 225.000000, "Hunger");
    TextDrawFont(SaStyleTD[2], 1);
    TextDrawLetterSize(SaStyleTD[2], 0.262500, 1.450000);
    TextDrawTextSize(SaStyleTD[2], 400.000000, 17.000000);
    TextDrawSetOutline(SaStyleTD[2], 1);
    TextDrawSetShadow(SaStyleTD[2], 0);
    TextDrawAlignment(SaStyleTD[2], 1);
    TextDrawColor(SaStyleTD[2], -1);
    TextDrawBackgroundColor(SaStyleTD[2], 255);
    TextDrawBoxColor(SaStyleTD[2], 50);
    TextDrawUseBox(SaStyleTD[2], 0);
    TextDrawSetProportional(SaStyleTD[2], 1);
    TextDrawSetSelectable(SaStyleTD[2], 0);

    SaStyleTD[3] = TextDrawCreate(6.000000, 243.000000, "Thirst");
    TextDrawFont(SaStyleTD[3], 1);
    TextDrawLetterSize(SaStyleTD[3], 0.262500, 1.450000);
    TextDrawTextSize(SaStyleTD[3], 400.000000, 17.000000);
    TextDrawSetOutline(SaStyleTD[3], 1);
    TextDrawSetShadow(SaStyleTD[3], 0);
    TextDrawAlignment(SaStyleTD[3], 1);
    TextDrawColor(SaStyleTD[3], -1);
    TextDrawBackgroundColor(SaStyleTD[3], 255);
    TextDrawBoxColor(SaStyleTD[3], 50);
    TextDrawUseBox(SaStyleTD[3], 0);
    TextDrawSetProportional(SaStyleTD[3], 1);
    TextDrawSetSelectable(SaStyleTD[3], 0);

    SaStyleTD[4] = TextDrawCreate(42.000000, 229.000000, "ld_drv:blkdot");
    TextDrawFont(SaStyleTD[4], 4);
    TextDrawLetterSize(SaStyleTD[4], 0.600000, 2.000000);
    TextDrawTextSize(SaStyleTD[4], 53.000000, 8.000000);
    TextDrawSetOutline(SaStyleTD[4], 1);
    TextDrawSetShadow(SaStyleTD[4], 0);
    TextDrawAlignment(SaStyleTD[4], 1);
    TextDrawColor(SaStyleTD[4], 1296911871);
    TextDrawBackgroundColor(SaStyleTD[4], 255);
    TextDrawBoxColor(SaStyleTD[4], 50);
    TextDrawUseBox(SaStyleTD[4], 1);
    TextDrawSetProportional(SaStyleTD[4], 1);
    TextDrawSetSelectable(SaStyleTD[4], 0);

    SaStyleTD[5] = TextDrawCreate(42.000000, 246.000000, "ld_drv:blkdot");
    TextDrawFont(SaStyleTD[5], 4);
    TextDrawLetterSize(SaStyleTD[5], 0.600000, 2.000000);
    TextDrawTextSize(SaStyleTD[5], 53.000000, 8.000000);
    TextDrawSetOutline(SaStyleTD[5], 1);
    TextDrawSetShadow(SaStyleTD[5], 0);
    TextDrawAlignment(SaStyleTD[5], 1);
    TextDrawColor(SaStyleTD[5], 1296911871);
    TextDrawBackgroundColor(SaStyleTD[5], 255);
    TextDrawBoxColor(SaStyleTD[5], 50);
    TextDrawUseBox(SaStyleTD[5], 1);
    TextDrawSetProportional(SaStyleTD[5], 1);
    TextDrawSetSelectable(SaStyleTD[5], 0);

    //hbe sa style vehicle
    SAStyleVehicleTD[0] = TextDrawCreate(3.000000, 266.000000, "ld_drv:blkdot");
    TextDrawFont(SAStyleVehicleTD[0], 4);
    TextDrawLetterSize(SAStyleVehicleTD[0], 0.600000, 2.000000);
    TextDrawTextSize(SAStyleVehicleTD[0], 97.000000, 15.500000);
    TextDrawSetOutline(SAStyleVehicleTD[0], 1);
    TextDrawSetShadow(SAStyleVehicleTD[0], 0);
    TextDrawAlignment(SAStyleVehicleTD[0], 1);
    TextDrawColor(SAStyleVehicleTD[0], 234);
    TextDrawBackgroundColor(SAStyleVehicleTD[0], 255);
    TextDrawBoxColor(SAStyleVehicleTD[0], 50);
    TextDrawUseBox(SAStyleVehicleTD[0], 1);
    TextDrawSetProportional(SAStyleVehicleTD[0], 1);
    TextDrawSetSelectable(SAStyleVehicleTD[0], 0);

    SAStyleVehicleTD[1] = TextDrawCreate(103.000000, 220.000000, "ld_drv:blkdot");
    TextDrawFont(SAStyleVehicleTD[1], 4);
    TextDrawLetterSize(SAStyleVehicleTD[1], 0.600000, 2.000000);
    TextDrawTextSize(SAStyleVehicleTD[1], 13.000000, 61.500000);
    TextDrawSetOutline(SAStyleVehicleTD[1], 1);
    TextDrawSetShadow(SAStyleVehicleTD[1], 0);
    TextDrawAlignment(SAStyleVehicleTD[1], 1);
    TextDrawColor(SAStyleVehicleTD[1], 234);
    TextDrawBackgroundColor(SAStyleVehicleTD[1], 255);
    TextDrawBoxColor(SAStyleVehicleTD[1], 50);
    TextDrawUseBox(SAStyleVehicleTD[1], 1);
    TextDrawSetProportional(SAStyleVehicleTD[1], 1);
    TextDrawSetSelectable(SAStyleVehicleTD[1], 0);

    SAStyleVehicleTD[2] = TextDrawCreate(120.000000, 220.000000, "ld_drv:blkdot");
    TextDrawFont(SAStyleVehicleTD[2], 4);
    TextDrawLetterSize(SAStyleVehicleTD[2], 0.600000, 2.000000);
    TextDrawTextSize(SAStyleVehicleTD[2], 13.000000, 61.500000);
    TextDrawSetOutline(SAStyleVehicleTD[2], 1);
    TextDrawSetShadow(SAStyleVehicleTD[2], 0);
    TextDrawAlignment(SAStyleVehicleTD[2], 1);
    TextDrawColor(SAStyleVehicleTD[2], 234);
    TextDrawBackgroundColor(SAStyleVehicleTD[2], 255);
    TextDrawBoxColor(SAStyleVehicleTD[2], 50);
    TextDrawUseBox(SAStyleVehicleTD[2], 1);
    TextDrawSetProportional(SAStyleVehicleTD[2], 1);
    TextDrawSetSelectable(SAStyleVehicleTD[2], 0);

    SAStyleVehicleTD[3] = TextDrawCreate(121.000000, 268.000000, "HUD:radar_centre");
    TextDrawFont(SAStyleVehicleTD[3], 4);
    TextDrawLetterSize(SAStyleVehicleTD[3], 0.600000, 2.000000);
    TextDrawTextSize(SAStyleVehicleTD[3], 11.500000, 11.000000);
    TextDrawSetOutline(SAStyleVehicleTD[3], 1);
    TextDrawSetShadow(SAStyleVehicleTD[3], 0);
    TextDrawAlignment(SAStyleVehicleTD[3], 1);
    TextDrawColor(SAStyleVehicleTD[3], -1);
    TextDrawBackgroundColor(SAStyleVehicleTD[3], 255);
    TextDrawBoxColor(SAStyleVehicleTD[3], 50);
    TextDrawUseBox(SAStyleVehicleTD[3], 1);
    TextDrawSetProportional(SAStyleVehicleTD[3], 1);
    TextDrawSetSelectable(SAStyleVehicleTD[3], 0);

    SAStyleVehicleTD[4] = TextDrawCreate(106.000000, 267.000000, "H");
    TextDrawFont(SAStyleVehicleTD[4], 1);
    TextDrawLetterSize(SAStyleVehicleTD[4], 0.262499, 1.450000);
    TextDrawTextSize(SAStyleVehicleTD[4], 400.000000, 17.000000);
    TextDrawSetOutline(SAStyleVehicleTD[4], 1);
    TextDrawSetShadow(SAStyleVehicleTD[4], 0);
    TextDrawAlignment(SAStyleVehicleTD[4], 1);
    TextDrawColor(SAStyleVehicleTD[4], -1);
    TextDrawBackgroundColor(SAStyleVehicleTD[4], 255);
    TextDrawBoxColor(SAStyleVehicleTD[4], 50);
    TextDrawUseBox(SAStyleVehicleTD[4], 0);
    TextDrawSetProportional(SAStyleVehicleTD[4], 1);
    TextDrawSetSelectable(SAStyleVehicleTD[4], 0);

    SAStyleVehicleTD[5] = TextDrawCreate(106.000000, 224.000000, "ld_drv:blkdot");
    TextDrawFont(SAStyleVehicleTD[5], 4);
    TextDrawLetterSize(SAStyleVehicleTD[5], 0.600000, 2.000000);
    TextDrawTextSize(SAStyleVehicleTD[5], 7.000000, 42.000000);
    TextDrawSetOutline(SAStyleVehicleTD[5], 1);
    TextDrawSetShadow(SAStyleVehicleTD[5], 0);
    TextDrawAlignment(SAStyleVehicleTD[5], 1);
    TextDrawColor(SAStyleVehicleTD[5], 1296911871);
    TextDrawBackgroundColor(SAStyleVehicleTD[5], 255);
    TextDrawBoxColor(SAStyleVehicleTD[5], 50);
    TextDrawUseBox(SAStyleVehicleTD[5], 1);
    TextDrawSetProportional(SAStyleVehicleTD[5], 1);
    TextDrawSetSelectable(SAStyleVehicleTD[5], 0);

    SAStyleVehicleTD[6] = TextDrawCreate(123.000000, 224.000000, "ld_drv:blkdot");
    TextDrawFont(SAStyleVehicleTD[6], 4);
    TextDrawLetterSize(SAStyleVehicleTD[6], 0.600000, 2.000000);
    TextDrawTextSize(SAStyleVehicleTD[6], 7.000000, 42.000000);
    TextDrawSetOutline(SAStyleVehicleTD[6], 1);
    TextDrawSetShadow(SAStyleVehicleTD[6], 0);
    TextDrawAlignment(SAStyleVehicleTD[6], 1);
    TextDrawColor(SAStyleVehicleTD[6], 1296911871);
    TextDrawBackgroundColor(SAStyleVehicleTD[6], 255);
    TextDrawBoxColor(SAStyleVehicleTD[6], 50);
    TextDrawUseBox(SAStyleVehicleTD[6], 1);
    TextDrawSetProportional(SAStyleVehicleTD[6], 1);
    TextDrawSetSelectable(SAStyleVehicleTD[6], 0);

    SAStyleVehicleTD[7] = TextDrawCreate(103.000000, 286.000000, "ld_drv:blkdot");
    TextDrawFont(SAStyleVehicleTD[7], 4);
    TextDrawLetterSize(SAStyleVehicleTD[7], 0.600000, 2.000000);
    TextDrawTextSize(SAStyleVehicleTD[7], 30.000000, 28.500000);
    TextDrawSetOutline(SAStyleVehicleTD[7], 1);
    TextDrawSetShadow(SAStyleVehicleTD[7], 0);
    TextDrawAlignment(SAStyleVehicleTD[7], 1);
    TextDrawColor(SAStyleVehicleTD[7], 234);
    TextDrawBackgroundColor(SAStyleVehicleTD[7], 255);
    TextDrawBoxColor(SAStyleVehicleTD[7], 50);
    TextDrawUseBox(SAStyleVehicleTD[7], 1);
    TextDrawSetProportional(SAStyleVehicleTD[7], 1);
    TextDrawSetSelectable(SAStyleVehicleTD[7], 0);

    SAStyleVehicleTD[8] = TextDrawCreate(118.000000, 300.000000, "KM/H");
    TextDrawFont(SAStyleVehicleTD[8], 1);
    TextDrawLetterSize(SAStyleVehicleTD[8], 0.216666, 1.250000);
    TextDrawTextSize(SAStyleVehicleTD[8], 400.000000, 22.000000);
    TextDrawSetOutline(SAStyleVehicleTD[8], 1);
    TextDrawSetShadow(SAStyleVehicleTD[8], 0);
    TextDrawAlignment(SAStyleVehicleTD[8], 2);
    TextDrawColor(SAStyleVehicleTD[8], -1);
    TextDrawBackgroundColor(SAStyleVehicleTD[8], 255);
    TextDrawBoxColor(SAStyleVehicleTD[8], 50);
    TextDrawUseBox(SAStyleVehicleTD[8], 0);
    TextDrawSetProportional(SAStyleVehicleTD[8], 1);
    TextDrawSetSelectable(SAStyleVehicleTD[8], 0);

    SAStyleVehicleTD[9] = TextDrawCreate(3.000000, 287.000000, "Speedometer");
    TextDrawFont(SAStyleVehicleTD[9], 0);
    TextDrawLetterSize(SAStyleVehicleTD[9], 0.658333, 2.399999);
    TextDrawTextSize(SAStyleVehicleTD[9], 400.000000, 17.000000);
    TextDrawSetOutline(SAStyleVehicleTD[9], 1);
    TextDrawSetShadow(SAStyleVehicleTD[9], 0);
    TextDrawAlignment(SAStyleVehicleTD[9], 1);
    TextDrawColor(SAStyleVehicleTD[9], -1);
    TextDrawBackgroundColor(SAStyleVehicleTD[9], 255);
    TextDrawBoxColor(SAStyleVehicleTD[9], 50);
    TextDrawUseBox(SAStyleVehicleTD[9], 0);
    TextDrawSetProportional(SAStyleVehicleTD[9], 1);
    TextDrawSetSelectable(SAStyleVehicleTD[9], 0);
    
    //HBE OLD SCHOOL
    SimpleStyleTD[0] = TextDrawCreate(585.000000, 421.000000, "ld_drv:blkdot");
    TextDrawFont(SimpleStyleTD[0], 4);
    TextDrawLetterSize(SimpleStyleTD[0], 0.600000, 2.000000);
    TextDrawTextSize(SimpleStyleTD[0], 50.000000, 20.500000);
    TextDrawSetOutline(SimpleStyleTD[0], 1);
    TextDrawSetShadow(SimpleStyleTD[0], 0);
    TextDrawAlignment(SimpleStyleTD[0], 1);
    TextDrawColor(SimpleStyleTD[0], 212);
    TextDrawBackgroundColor(SimpleStyleTD[0], 255);
    TextDrawBoxColor(SimpleStyleTD[0], 50);
    TextDrawUseBox(SimpleStyleTD[0], 1);
    TextDrawSetProportional(SimpleStyleTD[0], 1);
    TextDrawSetSelectable(SimpleStyleTD[0], 0);

    SimpleStyleTD[1] = TextDrawCreate(529.000000, 421.000000, "ld_drv:blkdot");
    TextDrawFont(SimpleStyleTD[1], 4);
    TextDrawLetterSize(SimpleStyleTD[1], 0.600000, 2.000000);
    TextDrawTextSize(SimpleStyleTD[1], 50.000000, 20.500000);
    TextDrawSetOutline(SimpleStyleTD[1], 1);
    TextDrawSetShadow(SimpleStyleTD[1], 0);
    TextDrawAlignment(SimpleStyleTD[1], 1);
    TextDrawColor(SimpleStyleTD[1], 212);
    TextDrawBackgroundColor(SimpleStyleTD[1], 255);
    TextDrawBoxColor(SimpleStyleTD[1], 50);
    TextDrawUseBox(SimpleStyleTD[1], 1);
    TextDrawSetProportional(SimpleStyleTD[1], 1);
    TextDrawSetSelectable(SimpleStyleTD[1], 0);

    SimpleStyleTD[2] = TextDrawCreate(532.000000, 425.000000, "HUD:radar_pizza");
    TextDrawFont(SimpleStyleTD[2], 4);
    TextDrawLetterSize(SimpleStyleTD[2], 0.600000, 2.000000);
    TextDrawTextSize(SimpleStyleTD[2], 12.000000, 13.000000);
    TextDrawSetOutline(SimpleStyleTD[2], 1);
    TextDrawSetShadow(SimpleStyleTD[2], 0);
    TextDrawAlignment(SimpleStyleTD[2], 1);
    TextDrawColor(SimpleStyleTD[2], -1);
    TextDrawBackgroundColor(SimpleStyleTD[2], 255);
    TextDrawBoxColor(SimpleStyleTD[2], 50);
    TextDrawUseBox(SimpleStyleTD[2], 1);
    TextDrawSetProportional(SimpleStyleTD[2], 1);
    TextDrawSetSelectable(SimpleStyleTD[2], 0);

    SimpleStyleTD[3] = TextDrawCreate(588.000000, 425.000000, "HUD:radar_diner");
    TextDrawFont(SimpleStyleTD[3], 4);
    TextDrawLetterSize(SimpleStyleTD[3], 0.600000, 2.000000);
    TextDrawTextSize(SimpleStyleTD[3], 12.000000, 13.000000);
    TextDrawSetOutline(SimpleStyleTD[3], 1);
    TextDrawSetShadow(SimpleStyleTD[3], 0);
    TextDrawAlignment(SimpleStyleTD[3], 1);
    TextDrawColor(SimpleStyleTD[3], -1);
    TextDrawBackgroundColor(SimpleStyleTD[3], 255);
    TextDrawBoxColor(SimpleStyleTD[3], 50);
    TextDrawUseBox(SimpleStyleTD[3], 1);
    TextDrawSetProportional(SimpleStyleTD[3], 1);
    TextDrawSetSelectable(SimpleStyleTD[3], 0);

    //Old School style vehicle
    SimpleVehicleTD[0] = TextDrawCreate(528.000000, 324.000000, "I");
    TextDrawFont(SimpleVehicleTD[0], 1);
    TextDrawLetterSize(SimpleVehicleTD[0], 0.308333, 10.649996);
    TextDrawTextSize(SimpleVehicleTD[0], 400.000000, 17.000000);
    TextDrawSetOutline(SimpleVehicleTD[0], 1);
    TextDrawSetShadow(SimpleVehicleTD[0], 0);
    TextDrawAlignment(SimpleVehicleTD[0], 1);
    TextDrawColor(SimpleVehicleTD[0], -1);
    TextDrawBackgroundColor(SimpleVehicleTD[0], 255);
    TextDrawBoxColor(SimpleVehicleTD[0], 50);
    TextDrawUseBox(SimpleVehicleTD[0], 0);
    TextDrawSetProportional(SimpleVehicleTD[0], 1);
    TextDrawSetSelectable(SimpleVehicleTD[0], 0);

    SimpleVehicleTD[1] = TextDrawCreate(561.000000, 350.000000, "km/h");
    TextDrawFont(SimpleVehicleTD[1], 2);
    TextDrawLetterSize(SimpleVehicleTD[1], 0.170833, 1.450000);
    TextDrawTextSize(SimpleVehicleTD[1], 400.000000, 17.000000);
    TextDrawSetOutline(SimpleVehicleTD[1], 1);
    TextDrawSetShadow(SimpleVehicleTD[1], 0);
    TextDrawAlignment(SimpleVehicleTD[1], 1);
    TextDrawColor(SimpleVehicleTD[1], -1);
    TextDrawBackgroundColor(SimpleVehicleTD[1], 255);
    TextDrawBoxColor(SimpleVehicleTD[1], 50);
    TextDrawUseBox(SimpleVehicleTD[1], 0);
    TextDrawSetProportional(SimpleVehicleTD[1], 1);
    TextDrawSetSelectable(SimpleVehicleTD[1], 0);

    SimpleVehicleTD[2] = TextDrawCreate(534.000000, 362.000000, "fuel:");
    TextDrawFont(SimpleVehicleTD[2], 2);
    TextDrawLetterSize(SimpleVehicleTD[2], 0.170833, 1.450000);
    TextDrawTextSize(SimpleVehicleTD[2], 400.000000, 17.000000);
    TextDrawSetOutline(SimpleVehicleTD[2], 1);
    TextDrawSetShadow(SimpleVehicleTD[2], 0);
    TextDrawAlignment(SimpleVehicleTD[2], 1);
    TextDrawColor(SimpleVehicleTD[2], -1);
    TextDrawBackgroundColor(SimpleVehicleTD[2], 255);
    TextDrawBoxColor(SimpleVehicleTD[2], 50);
    TextDrawUseBox(SimpleVehicleTD[2], 0);
    TextDrawSetProportional(SimpleVehicleTD[2], 1);
    TextDrawSetSelectable(SimpleVehicleTD[2], 0);

    SimpleVehicleTD[3] = TextDrawCreate(534.000000, 374.000000, "health:");
    TextDrawFont(SimpleVehicleTD[3], 2);
    TextDrawLetterSize(SimpleVehicleTD[3], 0.170833, 1.450000);
    TextDrawTextSize(SimpleVehicleTD[3], 400.000000, 17.000000);
    TextDrawSetOutline(SimpleVehicleTD[3], 1);
    TextDrawSetShadow(SimpleVehicleTD[3], 0);
    TextDrawAlignment(SimpleVehicleTD[3], 1);
    TextDrawColor(SimpleVehicleTD[3], -1);
    TextDrawBackgroundColor(SimpleVehicleTD[3], 255);
    TextDrawBoxColor(SimpleVehicleTD[3], 50);
    TextDrawUseBox(SimpleVehicleTD[3], 0);
    TextDrawSetProportional(SimpleVehicleTD[3], 1);
    TextDrawSetSelectable(SimpleVehicleTD[3], 0);

    SimpleVehicleTD[4] = TextDrawCreate(534.000000, 387.000000, "VEHICLE:");
    TextDrawFont(SimpleVehicleTD[4], 2);
    TextDrawLetterSize(SimpleVehicleTD[4], 0.170833, 1.450000);
    TextDrawTextSize(SimpleVehicleTD[4], 616.000000, 17.000000);
    TextDrawSetOutline(SimpleVehicleTD[4], 1);
    TextDrawSetShadow(SimpleVehicleTD[4], 0);
    TextDrawAlignment(SimpleVehicleTD[4], 1);
    TextDrawColor(SimpleVehicleTD[4], -1);
    TextDrawBackgroundColor(SimpleVehicleTD[4], 255);
    TextDrawBoxColor(SimpleVehicleTD[4], 50);
    TextDrawUseBox(SimpleVehicleTD[4], 0);
    TextDrawSetProportional(SimpleVehicleTD[4], 1);
    TextDrawSetSelectable(SimpleVehicleTD[4], 0);
    
    //HBEMINIMALIST
	simpletd[0] = TextDrawCreate(570.000000, 355.000000, "_~n~_~n~_~n~_~n~_~n~_~n~_");
	TextDrawFont(simpletd[0], 3);
	TextDrawLetterSize(simpletd[0], 0.500000, 0.850000);
	TextDrawAlignment(simpletd[0], 1);
	TextDrawColor(simpletd[0], 0xFFFFFFFFFFFFFFFF);
	TextDrawSetProportional(simpletd[0], 1);
	TextDrawUseBox(simpletd[0], 1);
	TextDrawBoxColor(simpletd[0], 0x000000AA);
	TextDrawTextSize(simpletd[0], 640.000000, 10.000000);
	TextDrawSetShadow(simpletd[0], 0);
	TextDrawSetOutline(simpletd[0], 1);
	TextDrawBackgroundColor(simpletd[0], 0x000000FF);
	TextDrawSetSelectable(simpletd[0], 0);

	simpletd[1] = TextDrawCreate(636.000000, 387.000000, "90%");
	TextDrawFont(simpletd[1], 3);
	TextDrawLetterSize(simpletd[1], 0.400000, 1.500000);
	TextDrawAlignment(simpletd[1], 3);
	TextDrawColor(simpletd[1], 0xFFFFFFFFFFFFFFFF);
	TextDrawSetProportional(simpletd[1], 1);
	TextDrawTextSize(simpletd[1], 0.000000, 0.000000);
	TextDrawSetShadow(simpletd[1], 0);
	TextDrawSetOutline(simpletd[1], 1);
	TextDrawBackgroundColor(simpletd[1], 0x000000FF);
	TextDrawSetSelectable(simpletd[1], 0);

	simpletd[2] = TextDrawCreate(636.000000, 362.000000, "77%");
	TextDrawFont(simpletd[2], 3);
	TextDrawLetterSize(simpletd[2], 0.400000, 1.500000);
	TextDrawAlignment(simpletd[2], 3);
	TextDrawColor(simpletd[2], 0xFFFFFFFFFFFFFFFF);
	TextDrawSetProportional(simpletd[2], 1);
	TextDrawTextSize(simpletd[2], 0.000000, 0.000000);
	TextDrawSetShadow(simpletd[2], 0);
	TextDrawSetOutline(simpletd[2], 1);
	TextDrawBackgroundColor(simpletd[2], 0x000000FF);
	TextDrawSetSelectable(simpletd[2], 0);

	simpletd[3] = TextDrawCreate(575.000000, 360.000000, "HUD:radar_dateFood");
	TextDrawFont(simpletd[3], 4);
	TextDrawLetterSize(simpletd[3], 0.480000, 1.120000);
	TextDrawAlignment(simpletd[3], 0);
	TextDrawColor(simpletd[3], 0xFFFFFFFFFFFFFFFF);
	TextDrawSetProportional(simpletd[3], 1);
	TextDrawTextSize(simpletd[3], 18.000000, 18.000000);
	TextDrawSetShadow(simpletd[3], 2);
	TextDrawSetOutline(simpletd[3], 0);
	TextDrawBackgroundColor(simpletd[3], 0x000000FF);
	TextDrawSetSelectable(simpletd[3], 0);

	simpletd[4] = TextDrawCreate(570.000000, 285.000000, "_~n~_~n~_~n~_~n~_~n~_~n~_");
	TextDrawFont(simpletd[4], 3);
	TextDrawLetterSize(simpletd[4], 0.500000, 1.000000);
	TextDrawAlignment(simpletd[4], 1);
	TextDrawColor(simpletd[4], 0xFFFFFFFFFFFFFFFF);
	TextDrawSetProportional(simpletd[4], 1);
	TextDrawUseBox(simpletd[4], 1);
	TextDrawBoxColor(simpletd[4], 0x000000AF);
	TextDrawTextSize(simpletd[4], 640.000000, 10.000000);
	TextDrawSetShadow(simpletd[4], 0);
	TextDrawSetOutline(simpletd[4], 1);
	TextDrawBackgroundColor(simpletd[4], 0x000000FF);
	TextDrawSetSelectable(simpletd[4], 0);

	simpletd[5] = TextDrawCreate(575.000000, 305.000000, "HUD:radar_modGarage");
	TextDrawFont(simpletd[5], 4);
	TextDrawLetterSize(simpletd[5], 0.480000, 1.120000);
	TextDrawAlignment(simpletd[5], 0);
	TextDrawColor(simpletd[5], 0xFFFFFFFFFFFFFFFF);
	TextDrawSetProportional(simpletd[5], 1);
	TextDrawTextSize(simpletd[5], 18.000000, 18.000000);
	TextDrawSetShadow(simpletd[5], 2);
	TextDrawSetOutline(simpletd[5], 0);
	TextDrawBackgroundColor(simpletd[5], 0x000000FF);
	TextDrawSetSelectable(simpletd[5], 0);

	simpletd[6] = TextDrawCreate(575.000000, 325.000000, "HUD:radar_spray");
	TextDrawFont(simpletd[6], 4);
	TextDrawLetterSize(simpletd[6], 0.480000, 1.120000);
	TextDrawAlignment(simpletd[6], 0);
	TextDrawColor(simpletd[6], 0xFFFFFFFFFFFFFFFF);
	TextDrawSetProportional(simpletd[6], 1);
	TextDrawTextSize(simpletd[6], 18.000000, 18.000000);
	TextDrawSetShadow(simpletd[6], 2);
	TextDrawSetOutline(simpletd[6], 0);
	TextDrawBackgroundColor(simpletd[6], 0x000000FF);
	TextDrawSetSelectable(simpletd[6], 0);

	simpletd[7] = TextDrawCreate(575.000000, 285.000000, "HUD:radar_impound");
	TextDrawFont(simpletd[7], 4);
	TextDrawLetterSize(simpletd[7], 0.480000, 1.120000);
	TextDrawAlignment(simpletd[7], 0);
	TextDrawColor(simpletd[7], 0xFFFFFFFFFFFFFFFF);
	TextDrawSetProportional(simpletd[7], 1);
	TextDrawTextSize(simpletd[7], 18.000000, 18.000000);
	TextDrawSetShadow(simpletd[7], 2);
	TextDrawSetOutline(simpletd[7], 0);
	TextDrawBackgroundColor(simpletd[7], 0x000000FF);
	TextDrawSetSelectable(simpletd[7], 0);

	simpletd[8] = TextDrawCreate(575.000000, 385.000000, "HUD:radar_diner");
	TextDrawFont(simpletd[8], 4);
	TextDrawLetterSize(simpletd[8], 0.480000, 1.120000);
	TextDrawAlignment(simpletd[8], 0);
	TextDrawColor(simpletd[8], 0xFFFFFFFFFFFFFFFF);
	TextDrawSetProportional(simpletd[8], 1);
	TextDrawTextSize(simpletd[8], 18.000000, 18.000000);
	TextDrawSetShadow(simpletd[8], 2);
	TextDrawSetOutline(simpletd[8], 0);
	TextDrawBackgroundColor(simpletd[8], 0x000000FF);
	TextDrawSetSelectable(simpletd[8], 0);
}

PlayerHBEHide(playerid) {
    switch(pData[playerid][pHBEMode]) {
        case 1: {
            //HBE SA STYLE
			for(new i; i < 6; i++)
			{
				TextDrawHideForPlayer(playerid, SaStyleTD[i]);
			}
			PlayerTextDrawHide(playerid, SAPHungerTD[playerid]);
			PlayerTextDrawHide(playerid, SAPThirstTD[playerid]);
        }
        case 2: {
            //HBE Simple
            TextDrawHideForPlayer(playerid, simpletd[0]);
            PlayerTextDrawHide(playerid, JGHUNGER[playerid]);
            PlayerTextDrawHide(playerid, JGTHIRST[playerid]);
            TextDrawHideForPlayer(playerid, simpletd[3]);
            TextDrawHideForPlayer(playerid, simpletd[8]);
        }
        case 3: {
            //HBE Old School
            for(new i; i < 4; i++)
			{
				TextDrawHideForPlayer(playerid, SimpleStyleTD[i]);
			}
			PlayerTextDrawHide(playerid, PHungerTD[playerid]);
			PlayerTextDrawHide(playerid, PThirstTD[playerid]);
        }
    }
    return 1;
}

PlayerHBEShow(playerid) {
    switch(pData[playerid][pHBEMode]) {
        case 1: {
            //HBE SA STYLE
			for(new i; i < 6; i++)
			{
				TextDrawShowForPlayer(playerid, SaStyleTD[i]);
			}
			PlayerTextDrawShow(playerid, SAPHungerTD[playerid]);
			PlayerTextDrawShow(playerid, SAPThirstTD[playerid]);
        }
        case 2: {
            //HBE Simple
            TextDrawShowForPlayer(playerid, simpletd[0]);
            PlayerTextDrawShow(playerid, JGHUNGER[playerid]);
            PlayerTextDrawShow(playerid, JGTHIRST[playerid]);
            TextDrawShowForPlayer(playerid, simpletd[3]);
            TextDrawShowForPlayer(playerid, simpletd[8]);
        }
        case 3: {
            //HBE Old School
            for(new i; i < 4; i++)
			{
				TextDrawShowForPlayer(playerid, SimpleStyleTD[i]);
			}
			PlayerTextDrawShow(playerid, PHungerTD[playerid]);
			PlayerTextDrawShow(playerid, PThirstTD[playerid]);
        }
    }
    return 1;
}

VehicleHBEHide(playerid) {
    switch(pData[playerid][pHBEMode]) {
        case 1: {
            //HBE Modern
			for(new i; i < 10; i++)
			{
				TextDrawHideForPlayer(playerid, SAStyleVehicleTD[i]);
			}
			PlayerTextDrawHide(playerid, SAVNameTD[playerid]);
			PlayerTextDrawHide(playerid, SAVHealthTD[playerid]);
			PlayerTextDrawHide(playerid, SAVFuelTD[playerid]);
			PlayerTextDrawHide(playerid, SAPVSpeedTD[playerid]);
        }
        case 2: {
            //HBE Simple
            PlayerTextDrawHide(playerid, JGVHP[playerid]);
            PlayerTextDrawHide(playerid, JGVFUEL[playerid]);
            PlayerTextDrawHide(playerid, JGVSPEED[playerid]);
            TextDrawHideForPlayer(playerid, simpletd[4]);
            TextDrawHideForPlayer(playerid, simpletd[5]);
            TextDrawHideForPlayer(playerid, simpletd[6]);
            TextDrawHideForPlayer(playerid, simpletd[7]);
        }
        case 3: {
            //HBE Old School
			for(new i; i < 5; i++)
			{
				TextDrawHideForPlayer(playerid, SimpleVehicleTD[i]);
			}
			PlayerTextDrawHide(playerid, VSpeedTD[playerid]);
			PlayerTextDrawHide(playerid, VFuelTD[playerid]);
			PlayerTextDrawHide(playerid, VHealthTD[playerid]);
			PlayerTextDrawHide(playerid, VNameTD[playerid]);
        }
    }
    return 1;
}
