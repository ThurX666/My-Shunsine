
Vehicle_CrateComponentTotal(vehicleid)
{
	new count = 0;
    foreach(new pv : PVehicles)
    {
        if(vehicleid == pvData[pv][cVeh])
        {
            count += pvData[pv][cCrateComponent];
        }
    }        
	return count;
}

Vehicle_CratePlantTotal(vehicleid)
{
	new count = 0;
    foreach(new pv : PVehicles)
    {
        if(vehicleid == pvData[pv][cVeh])
        {
            count += pvData[pv][cCratePlant];
        }
    }        
	return count;
}

Vehicle_CrateLumberTotal(vehicleid)
{
	new count = 0;
    foreach(new pv : PVehicles)
    {
        if(vehicleid == pvData[pv][cVeh])
        {
            count += pvData[pv][cCrateLumber];
        }
    }        
	return count;
}

Vehicle_CrateFishTotal(vehicleid)
{
	new count = 0;
    foreach(new pv : PVehicles)
    {
        if(vehicleid == pvData[pv][cVeh])
        {
            count += pvData[pv][cCrateFish];
        }
        else if(vehicleid == pvData[pv][cVeh])
        {
            count += pvData[pv][cCrateFish2];
        }
    }    
	return count;
}

TextDrawInitHauling()
{
    //Textdraws
    TDHauling[0] = TextDrawCreate(317.000000, 70.000000, "_");
    TextDrawFont(TDHauling[0], 1);
    TextDrawLetterSize(TDHauling[0], 0.600000, 31.800003);
    TextDrawTextSize(TDHauling[0], 298.500000, 320.000000);
    TextDrawSetOutline(TDHauling[0], 1);
    TextDrawSetShadow(TDHauling[0], 0);
    TextDrawAlignment(TDHauling[0], 2);
    TextDrawColor(TDHauling[0], -1);
    TextDrawBackgroundColor(TDHauling[0], 255);
    TextDrawBoxColor(TDHauling[0], 255);
    TextDrawUseBox(TDHauling[0], 1);
    TextDrawSetProportional(TDHauling[0], 1);
    TextDrawSetSelectable(TDHauling[0], 0);

    TDHauling[1] = TextDrawCreate(243.000000, 69.000000, "Trucking Missions");
    TextDrawFont(TDHauling[1], 0);
    TextDrawLetterSize(TDHauling[1], 0.579166, 2.099999);
    TextDrawTextSize(TDHauling[1], 400.000000, 17.000000);
    TextDrawSetOutline(TDHauling[1], 1);
    TextDrawSetShadow(TDHauling[1], 0);
    TextDrawAlignment(TDHauling[1], 1);
    TextDrawColor(TDHauling[1], -1);
    TextDrawBackgroundColor(TDHauling[1], 255);
    TextDrawBoxColor(TDHauling[1], 50);
    TextDrawUseBox(TDHauling[1], 0);
    TextDrawSetProportional(TDHauling[1], 1);
    TextDrawSetSelectable(TDHauling[1], 0);

    TDHauling[2] = TextDrawCreate(161.000000, 96.000000, "MISSION");
    TextDrawFont(TDHauling[2], 3);
    TextDrawLetterSize(TDHauling[2], 0.470833, 1.500000);
    TextDrawTextSize(TDHauling[2], 400.000000, 17.000000);
    TextDrawSetOutline(TDHauling[2], 1);
    TextDrawSetShadow(TDHauling[2], 0);
    TextDrawAlignment(TDHauling[2], 1);
    TextDrawColor(TDHauling[2], 9145343);
    TextDrawBackgroundColor(TDHauling[2], 255);
    TextDrawBoxColor(TDHauling[2], 50);
    TextDrawUseBox(TDHauling[2], 0);
    TextDrawSetProportional(TDHauling[2], 1);
    TextDrawSetSelectable(TDHauling[2], 0);

    TDHauling[3] = TextDrawCreate(308.000000, 96.000000, "DISTANCE");
    TextDrawFont(TDHauling[3], 3);
    TextDrawLetterSize(TDHauling[3], 0.470833, 1.500000);
    TextDrawTextSize(TDHauling[3], 400.000000, 17.000000);
    TextDrawSetOutline(TDHauling[3], 1);
    TextDrawSetShadow(TDHauling[3], 0);
    TextDrawAlignment(TDHauling[3], 1);
    TextDrawColor(TDHauling[3], 9145343);
    TextDrawBackgroundColor(TDHauling[3], 255);
    TextDrawBoxColor(TDHauling[3], 50);
    TextDrawUseBox(TDHauling[3], 0);
    TextDrawSetProportional(TDHauling[3], 1);
    TextDrawSetSelectable(TDHauling[3], 0);

    TDHauling[4] = TextDrawCreate(404.000000, 96.000000, "PAYMENT");
    TextDrawFont(TDHauling[4], 3);
    TextDrawLetterSize(TDHauling[4], 0.470833, 1.500000);
    TextDrawTextSize(TDHauling[4], 400.000000, 17.000000);
    TextDrawSetOutline(TDHauling[4], 1);
    TextDrawSetShadow(TDHauling[4], 0);
    TextDrawAlignment(TDHauling[4], 1);
    TextDrawColor(TDHauling[4], 9145343);
    TextDrawBackgroundColor(TDHauling[4], 255);
    TextDrawBoxColor(TDHauling[4], 50);
    TextDrawUseBox(TDHauling[4], 0);
    TextDrawSetProportional(TDHauling[4], 1);
    TextDrawSetSelectable(TDHauling[4], 0);

    TDHauling[5] = TextDrawCreate(160.000000, 111.000000, "-------------------------------------------------");
    TextDrawFont(TDHauling[5], 1);
    TextDrawLetterSize(TDHauling[5], 0.429166, 0.850000);
    TextDrawTextSize(TDHauling[5], 620.000000, 17.000000);
    TextDrawSetOutline(TDHauling[5], 1);
    TextDrawSetShadow(TDHauling[5], 0);
    TextDrawAlignment(TDHauling[5], 1);
    TextDrawColor(TDHauling[5], 9145343);
    TextDrawBackgroundColor(TDHauling[5], 255);
    TextDrawBoxColor(TDHauling[5], 50);
    TextDrawUseBox(TDHauling[5], 0);
    TextDrawSetProportional(TDHauling[5], 1);
    TextDrawSetSelectable(TDHauling[5], 0);

    TDNameHauling[0] = TextDrawCreate(159.000000, 130.000000, "Ocean Dock Imports");
    TextDrawFont(TDNameHauling[0], 3);
    TextDrawLetterSize(TDNameHauling[0], 0.291666, 1.600000);
    TextDrawTextSize(TDNameHauling[0], 400.000000, 17.000000);
    TextDrawSetOutline(TDNameHauling[0], 2);
    TextDrawSetShadow(TDNameHauling[0], 4);
    TextDrawAlignment(TDNameHauling[0], 1);
    TextDrawColor(TDNameHauling[0], 1296911871);
    TextDrawBackgroundColor(TDNameHauling[0], 255);
    TextDrawBoxColor(TDNameHauling[0], 50);
    TextDrawUseBox(TDNameHauling[0], 0);
    TextDrawSetProportional(TDNameHauling[0], 1);
    TextDrawSetSelectable(TDNameHauling[0], 0);

    TDNameHauling[1] = TextDrawCreate(159.000000, 150.000000, "Ocean Dock Imports");
    TextDrawFont(TDNameHauling[1], 3);
    TextDrawLetterSize(TDNameHauling[1], 0.291666, 1.600000);
    TextDrawTextSize(TDNameHauling[1], 400.000000, 17.000000);
    TextDrawSetOutline(TDNameHauling[1], 2);
    TextDrawSetShadow(TDNameHauling[1], 4);
    TextDrawAlignment(TDNameHauling[1], 1);
    TextDrawColor(TDNameHauling[1], -1);
    TextDrawBackgroundColor(TDNameHauling[1], 255);
    TextDrawBoxColor(TDNameHauling[1], 50);
    TextDrawUseBox(TDNameHauling[1], 0);
    TextDrawSetProportional(TDNameHauling[1], 1);
    TextDrawSetSelectable(TDNameHauling[1], 0);

    TDNameHauling[2] = TextDrawCreate(159.000000, 170.000000, "Angel Pine Exports");
    TextDrawFont(TDNameHauling[2], 3);
    TextDrawLetterSize(TDNameHauling[2], 0.295833, 1.600000);
    TextDrawTextSize(TDNameHauling[2], 400.000000, 17.000000);
    TextDrawSetOutline(TDNameHauling[2], 2);
    TextDrawSetShadow(TDNameHauling[2], 4);
    TextDrawAlignment(TDNameHauling[2], 1);
    TextDrawColor(TDNameHauling[2], 1296911871);
    TextDrawBackgroundColor(TDNameHauling[2], 255);
    TextDrawBoxColor(TDNameHauling[2], 50);
    TextDrawUseBox(TDNameHauling[2], 0);
    TextDrawSetProportional(TDNameHauling[2], 1);
    TextDrawSetSelectable(TDNameHauling[2], 0);

    TDNameHauling[3] = TextDrawCreate(159.000000, 190.000000, "Angel Pine Exports");
    TextDrawFont(TDNameHauling[3], 3);
    TextDrawLetterSize(TDNameHauling[3], 0.291666, 1.600000);
    TextDrawTextSize(TDNameHauling[3], 400.000000, 17.000000);
    TextDrawSetOutline(TDNameHauling[3], 2);
    TextDrawSetShadow(TDNameHauling[3], 4);
    TextDrawAlignment(TDNameHauling[3], 1);
    TextDrawColor(TDNameHauling[3], -1);
    TextDrawBackgroundColor(TDNameHauling[3], 255);
    TextDrawBoxColor(TDNameHauling[3], 50);
    TextDrawUseBox(TDNameHauling[3], 0);
    TextDrawSetProportional(TDNameHauling[3], 1);
    TextDrawSetSelectable(TDNameHauling[3], 0);

    TDNameHauling[4] = TextDrawCreate(159.000000, 209.000000, "Chilliad Deport");
    TextDrawFont(TDNameHauling[4], 3);
    TextDrawLetterSize(TDNameHauling[4], 0.329166, 1.600000);
    TextDrawTextSize(TDNameHauling[4], 400.000000, 17.000000);
    TextDrawSetOutline(TDNameHauling[4], 2);
    TextDrawSetShadow(TDNameHauling[4], 4);
    TextDrawAlignment(TDNameHauling[4], 1);
    TextDrawColor(TDNameHauling[4], 1296911871);
    TextDrawBackgroundColor(TDNameHauling[4], 255);
    TextDrawBoxColor(TDNameHauling[4], 50);
    TextDrawUseBox(TDNameHauling[4], 0);
    TextDrawSetProportional(TDNameHauling[4], 1);
    TextDrawSetSelectable(TDNameHauling[4], 0);

    TDNameHauling[5] = TextDrawCreate(159.000000, 228.000000, "Chilliad Deport");
    TextDrawFont(TDNameHauling[5], 3);
    TextDrawLetterSize(TDNameHauling[5], 0.329166, 1.600000);
    TextDrawTextSize(TDNameHauling[5], 400.000000, 17.000000);
    TextDrawSetOutline(TDNameHauling[5], 2);
    TextDrawSetShadow(TDNameHauling[5], 4);
    TextDrawAlignment(TDNameHauling[5], 1);
    TextDrawColor(TDNameHauling[5], -1);
    TextDrawBackgroundColor(TDNameHauling[5], 255);
    TextDrawBoxColor(TDNameHauling[5], 50);
    TextDrawUseBox(TDNameHauling[5], 0);
    TextDrawSetProportional(TDNameHauling[5], 1);
    TextDrawSetSelectable(TDNameHauling[5], 0);

    TDNameHauling[6] = TextDrawCreate(159.000000, 248.000000, "Easter Import");
    TextDrawFont(TDNameHauling[6], 3);
    TextDrawLetterSize(TDNameHauling[6], 0.329166, 1.600000);
    TextDrawTextSize(TDNameHauling[6], 400.000000, 17.000000);
    TextDrawSetOutline(TDNameHauling[6], 2);
    TextDrawSetShadow(TDNameHauling[6], 4);
    TextDrawAlignment(TDNameHauling[6], 1);
    TextDrawColor(TDNameHauling[6], 1296911871);
    TextDrawBackgroundColor(TDNameHauling[6], 255);
    TextDrawBoxColor(TDNameHauling[6], 50);
    TextDrawUseBox(TDNameHauling[6], 0);
    TextDrawSetProportional(TDNameHauling[6], 1);
    TextDrawSetSelectable(TDNameHauling[6], 0);

    TDNameHauling[7] = TextDrawCreate(159.000000, 265.000000, "Blueberry Export");
    TextDrawFont(TDNameHauling[7], 3);
    TextDrawLetterSize(TDNameHauling[7], 0.308333, 1.600000);
    TextDrawTextSize(TDNameHauling[7], 400.000000, 17.000000);
    TextDrawSetOutline(TDNameHauling[7], 2);
    TextDrawSetShadow(TDNameHauling[7], 4);
    TextDrawAlignment(TDNameHauling[7], 1);
    TextDrawColor(TDNameHauling[7], -1);
    TextDrawBackgroundColor(TDNameHauling[7], 255);
    TextDrawBoxColor(TDNameHauling[7], 50);
    TextDrawUseBox(TDNameHauling[7], 0);
    TextDrawSetProportional(TDNameHauling[7], 1);
    TextDrawSetSelectable(TDNameHauling[7], 0);

    TDNameHauling[8] = TextDrawCreate(159.000000, 285.000000, "Las Venturas Deport");
    TextDrawFont(TDNameHauling[8], 3);
    TextDrawLetterSize(TDNameHauling[8], 0.266667, 1.600000);
    TextDrawTextSize(TDNameHauling[8], 400.000000, 17.000000);
    TextDrawSetOutline(TDNameHauling[8], 2);
    TextDrawSetShadow(TDNameHauling[8], 4);
    TextDrawAlignment(TDNameHauling[8], 1);
    TextDrawColor(TDNameHauling[8], 1296911871);
    TextDrawBackgroundColor(TDNameHauling[8], 255);
    TextDrawBoxColor(TDNameHauling[8], 50);
    TextDrawUseBox(TDNameHauling[8], 0);
    TextDrawSetProportional(TDNameHauling[8], 1);
    TextDrawSetSelectable(TDNameHauling[8], 0);

    TDNameHauling[9] = TextDrawCreate(159.000000, 306.000000, "Las Venturas Fuel & Gas");
    TextDrawFont(TDNameHauling[9], 3);
    TextDrawLetterSize(TDNameHauling[9], 0.266667, 1.600000);
    TextDrawTextSize(TDNameHauling[9], 400.000000, 17.000000);
    TextDrawSetOutline(TDNameHauling[9], 2);
    TextDrawSetShadow(TDNameHauling[9], 4);
    TextDrawAlignment(TDNameHauling[9], 1);
    TextDrawColor(TDNameHauling[9], -1);
    TextDrawBackgroundColor(TDNameHauling[9], 255);
    TextDrawBoxColor(TDNameHauling[9], 50);
    TextDrawUseBox(TDNameHauling[9], 0);
    TextDrawSetProportional(TDNameHauling[9], 1);
    TextDrawSetSelectable(TDNameHauling[9], 0);

    TDDistanceHauling[0] = TextDrawCreate(319.000000, 130.000000, "16.7 miles");
    TextDrawFont(TDDistanceHauling[0], 3);
    TextDrawLetterSize(TDDistanceHauling[0], 0.291666, 1.600000);
    TextDrawTextSize(TDDistanceHauling[0], 400.000000, 17.000000);
    TextDrawSetOutline(TDDistanceHauling[0], 2);
    TextDrawSetShadow(TDDistanceHauling[0], 4);
    TextDrawAlignment(TDDistanceHauling[0], 1);
    TextDrawColor(TDDistanceHauling[0], 1296911871);
    TextDrawBackgroundColor(TDDistanceHauling[0], 255);
    TextDrawBoxColor(TDDistanceHauling[0], 50);
    TextDrawUseBox(TDDistanceHauling[0], 0);
    TextDrawSetProportional(TDDistanceHauling[0], 1);
    TextDrawSetSelectable(TDDistanceHauling[0], 0);

    TDDistanceHauling[1] = TextDrawCreate(319.000000, 150.000000, "16.7 miles");
    TextDrawFont(TDDistanceHauling[1], 3);
    TextDrawLetterSize(TDDistanceHauling[1], 0.291666, 1.600000);
    TextDrawTextSize(TDDistanceHauling[1], 400.000000, 17.000000);
    TextDrawSetOutline(TDDistanceHauling[1], 2);
    TextDrawSetShadow(TDDistanceHauling[1], 4);
    TextDrawAlignment(TDDistanceHauling[1], 1);
    TextDrawColor(TDDistanceHauling[1], -1);
    TextDrawBackgroundColor(TDDistanceHauling[1], 255);
    TextDrawBoxColor(TDDistanceHauling[1], 50);
    TextDrawUseBox(TDDistanceHauling[1], 0);
    TextDrawSetProportional(TDDistanceHauling[1], 1);
    TextDrawSetSelectable(TDDistanceHauling[1], 0);

    TDDistanceHauling[2] = TextDrawCreate(319.000000, 169.000000, "16.7 miles");
    TextDrawFont(TDDistanceHauling[2], 3);
    TextDrawLetterSize(TDDistanceHauling[2], 0.291666, 1.600000);
    TextDrawTextSize(TDDistanceHauling[2], 400.000000, 17.000000);
    TextDrawSetOutline(TDDistanceHauling[2], 2);
    TextDrawSetShadow(TDDistanceHauling[2], 4);
    TextDrawAlignment(TDDistanceHauling[2], 1);
    TextDrawColor(TDDistanceHauling[2], 1296911871);
    TextDrawBackgroundColor(TDDistanceHauling[2], 255);
    TextDrawBoxColor(TDDistanceHauling[2], 50);
    TextDrawUseBox(TDDistanceHauling[2], 0);
    TextDrawSetProportional(TDDistanceHauling[2], 1);
    TextDrawSetSelectable(TDDistanceHauling[2], 0);

    TDDistanceHauling[3] = TextDrawCreate(319.000000, 187.000000, "16.7 miles");
    TextDrawFont(TDDistanceHauling[3], 3);
    TextDrawLetterSize(TDDistanceHauling[3], 0.291666, 1.600000);
    TextDrawTextSize(TDDistanceHauling[3], 400.000000, 17.000000);
    TextDrawSetOutline(TDDistanceHauling[3], 2);
    TextDrawSetShadow(TDDistanceHauling[3], 4);
    TextDrawAlignment(TDDistanceHauling[3], 1);
    TextDrawColor(TDDistanceHauling[3], -1);
    TextDrawBackgroundColor(TDDistanceHauling[3], 255);
    TextDrawBoxColor(TDDistanceHauling[3], 50);
    TextDrawUseBox(TDDistanceHauling[3], 0);
    TextDrawSetProportional(TDDistanceHauling[3], 1);
    TextDrawSetSelectable(TDDistanceHauling[3], 0);

    TDDistanceHauling[4] = TextDrawCreate(319.000000, 206.000000, "16.7 miles");
    TextDrawFont(TDDistanceHauling[4], 3);
    TextDrawLetterSize(TDDistanceHauling[4], 0.291666, 1.600000);
    TextDrawTextSize(TDDistanceHauling[4], 400.000000, 17.000000);
    TextDrawSetOutline(TDDistanceHauling[4], 2);
    TextDrawSetShadow(TDDistanceHauling[4], 4);
    TextDrawAlignment(TDDistanceHauling[4], 1);
    TextDrawColor(TDDistanceHauling[4], 1296911871);
    TextDrawBackgroundColor(TDDistanceHauling[4], 255);
    TextDrawBoxColor(TDDistanceHauling[4], 50);
    TextDrawUseBox(TDDistanceHauling[4], 0);
    TextDrawSetProportional(TDDistanceHauling[4], 1);
    TextDrawSetSelectable(TDDistanceHauling[4], 0);

    TDDistanceHauling[5] = TextDrawCreate(319.000000, 224.000000, "16.7 miles");
    TextDrawFont(TDDistanceHauling[5], 3);
    TextDrawLetterSize(TDDistanceHauling[5], 0.291666, 1.600000);
    TextDrawTextSize(TDDistanceHauling[5], 400.000000, 17.000000);
    TextDrawSetOutline(TDDistanceHauling[5], 2);
    TextDrawSetShadow(TDDistanceHauling[5], 4);
    TextDrawAlignment(TDDistanceHauling[5], 1);
    TextDrawColor(TDDistanceHauling[5], -1);
    TextDrawBackgroundColor(TDDistanceHauling[5], 255);
    TextDrawBoxColor(TDDistanceHauling[5], 50);
    TextDrawUseBox(TDDistanceHauling[5], 0);
    TextDrawSetProportional(TDDistanceHauling[5], 1);
    TextDrawSetSelectable(TDDistanceHauling[5], 0);

    TDDistanceHauling[6] = TextDrawCreate(319.000000, 243.000000, "16.7 miles");
    TextDrawFont(TDDistanceHauling[6], 3);
    TextDrawLetterSize(TDDistanceHauling[6], 0.291666, 1.600000);
    TextDrawTextSize(TDDistanceHauling[6], 400.000000, 17.000000);
    TextDrawSetOutline(TDDistanceHauling[6], 2);
    TextDrawSetShadow(TDDistanceHauling[6], 4);
    TextDrawAlignment(TDDistanceHauling[6], 1);
    TextDrawColor(TDDistanceHauling[6], 1296911871);
    TextDrawBackgroundColor(TDDistanceHauling[6], 255);
    TextDrawBoxColor(TDDistanceHauling[6], 50);
    TextDrawUseBox(TDDistanceHauling[6], 0);
    TextDrawSetProportional(TDDistanceHauling[6], 1);
    TextDrawSetSelectable(TDDistanceHauling[6], 0);

    TDDistanceHauling[7] = TextDrawCreate(319.000000, 262.000000, "16.7 miles");
    TextDrawFont(TDDistanceHauling[7], 3);
    TextDrawLetterSize(TDDistanceHauling[7], 0.291666, 1.600000);
    TextDrawTextSize(TDDistanceHauling[7], 400.000000, 17.000000);
    TextDrawSetOutline(TDDistanceHauling[7], 2);
    TextDrawSetShadow(TDDistanceHauling[7], 4);
    TextDrawAlignment(TDDistanceHauling[7], 1);
    TextDrawColor(TDDistanceHauling[7], -1);
    TextDrawBackgroundColor(TDDistanceHauling[7], 255);
    TextDrawBoxColor(TDDistanceHauling[7], 50);
    TextDrawUseBox(TDDistanceHauling[7], 0);
    TextDrawSetProportional(TDDistanceHauling[7], 1);
    TextDrawSetSelectable(TDDistanceHauling[7], 0);

    TDDistanceHauling[8] = TextDrawCreate(319.000000, 282.000000, "16.7 miles");
    TextDrawFont(TDDistanceHauling[8], 3);
    TextDrawLetterSize(TDDistanceHauling[8], 0.291666, 1.600000);
    TextDrawTextSize(TDDistanceHauling[8], 400.000000, 17.000000);
    TextDrawSetOutline(TDDistanceHauling[8], 2);
    TextDrawSetShadow(TDDistanceHauling[8], 4);
    TextDrawAlignment(TDDistanceHauling[8], 1);
    TextDrawColor(TDDistanceHauling[8], 1296911871);
    TextDrawBackgroundColor(TDDistanceHauling[8], 255);
    TextDrawBoxColor(TDDistanceHauling[8], 50);
    TextDrawUseBox(TDDistanceHauling[8], 0);
    TextDrawSetProportional(TDDistanceHauling[8], 1);
    TextDrawSetSelectable(TDDistanceHauling[8], 0);

    TDDistanceHauling[9] = TextDrawCreate(319.000000, 303.000000, "16.7 miles");
    TextDrawFont(TDDistanceHauling[9], 3);
    TextDrawLetterSize(TDDistanceHauling[9], 0.291666, 1.600000);
    TextDrawTextSize(TDDistanceHauling[9], 400.000000, 17.000000);
    TextDrawSetOutline(TDDistanceHauling[9], 2);
    TextDrawSetShadow(TDDistanceHauling[9], 4);
    TextDrawAlignment(TDDistanceHauling[9], 1);
    TextDrawColor(TDDistanceHauling[9], -1);
    TextDrawBackgroundColor(TDDistanceHauling[9], 255);
    TextDrawBoxColor(TDDistanceHauling[9], 50);
    TextDrawUseBox(TDDistanceHauling[9], 0);
    TextDrawSetProportional(TDDistanceHauling[9], 1);
    TextDrawSetSelectable(TDDistanceHauling[9], 0);

    TDBoxHauling[0] = TextDrawCreate(435.000000, 133.000000, "_");
    TextDrawFont(TDBoxHauling[0], 1);
    TextDrawLetterSize(TDBoxHauling[0], 0.600000, 0.850003);
    TextDrawTextSize(TDBoxHauling[0], 298.500000, 66.500000);
    TextDrawSetOutline(TDBoxHauling[0], 1);
    TextDrawSetShadow(TDBoxHauling[0], 0);
    TextDrawAlignment(TDBoxHauling[0], 2);
    TextDrawColor(TDBoxHauling[0], -1);
    TextDrawBackgroundColor(TDBoxHauling[0], 255);
    TextDrawBoxColor(TDBoxHauling[0], 9109759);
    TextDrawUseBox(TDBoxHauling[0], 1);
    TextDrawSetProportional(TDBoxHauling[0], 1);
    TextDrawSetSelectable(TDBoxHauling[0], 0);

    TDMoneyHauling[0] = TextDrawCreate(414.000000, 130.000000, "$278.90");
    TextDrawFont(TDMoneyHauling[0], 3);
    TextDrawLetterSize(TDMoneyHauling[0], 0.283333, 1.300000);
    TextDrawTextSize(TDMoneyHauling[0], 471.500000, 17.000000);
    TextDrawSetOutline(TDMoneyHauling[0], 1);
    TextDrawSetShadow(TDMoneyHauling[0], 0);
    TextDrawAlignment(TDMoneyHauling[0], 1);
    TextDrawColor(TDMoneyHauling[0], 9109757);
    TextDrawBackgroundColor(TDMoneyHauling[0], 255);
    TextDrawBoxColor(TDMoneyHauling[0], 16711935);
    TextDrawUseBox(TDMoneyHauling[0], 0);
    TextDrawSetProportional(TDMoneyHauling[0], 1);
    TextDrawSetSelectable(TDMoneyHauling[0], 1);

    TDBoxHauling[1] = TextDrawCreate(435.000000, 153.000000, "_");
    TextDrawFont(TDBoxHauling[1], 1);
    TextDrawLetterSize(TDBoxHauling[1], 0.600000, 0.700003);
    TextDrawTextSize(TDBoxHauling[1], 298.500000, 66.500000);
    TextDrawSetOutline(TDBoxHauling[1], 1);
    TextDrawSetShadow(TDBoxHauling[1], 0);
    TextDrawAlignment(TDBoxHauling[1], 2);
    TextDrawColor(TDBoxHauling[1], -1);
    TextDrawBackgroundColor(TDBoxHauling[1], 255);
    TextDrawBoxColor(TDBoxHauling[1], 9109759);
    TextDrawUseBox(TDBoxHauling[1], 1);
    TextDrawSetProportional(TDBoxHauling[1], 1);
    TextDrawSetSelectable(TDBoxHauling[1], 0);

    TDBoxHauling[2] = TextDrawCreate(435.000000, 172.000000, "_");
    TextDrawFont(TDBoxHauling[2], 1);
    TextDrawLetterSize(TDBoxHauling[2], 0.600000, 0.700003);
    TextDrawTextSize(TDBoxHauling[2], 298.500000, 66.500000);
    TextDrawSetOutline(TDBoxHauling[2], 1);
    TextDrawSetShadow(TDBoxHauling[2], 0);
    TextDrawAlignment(TDBoxHauling[2], 2);
    TextDrawColor(TDBoxHauling[2], -1);
    TextDrawBackgroundColor(TDBoxHauling[2], 255);
    TextDrawBoxColor(TDBoxHauling[2], 9109759);
    TextDrawUseBox(TDBoxHauling[2], 1);
    TextDrawSetProportional(TDBoxHauling[2], 1);
    TextDrawSetSelectable(TDBoxHauling[2], 0);

    TDBoxHauling[3] = TextDrawCreate(435.000000, 191.000000, "_");
    TextDrawFont(TDBoxHauling[3], 1);
    TextDrawLetterSize(TDBoxHauling[3], 0.600000, 0.700003);
    TextDrawTextSize(TDBoxHauling[3], 298.500000, 66.500000);
    TextDrawSetOutline(TDBoxHauling[3], 1);
    TextDrawSetShadow(TDBoxHauling[3], 0);
    TextDrawAlignment(TDBoxHauling[3], 2);
    TextDrawColor(TDBoxHauling[3], -1);
    TextDrawBackgroundColor(TDBoxHauling[3], 255);
    TextDrawBoxColor(TDBoxHauling[3], 9109759);
    TextDrawUseBox(TDBoxHauling[3], 1);
    TextDrawSetProportional(TDBoxHauling[3], 1);
    TextDrawSetSelectable(TDBoxHauling[3], 0);

    TDBoxHauling[4] = TextDrawCreate(435.000000, 210.000000, "_");
    TextDrawFont(TDBoxHauling[4], 1);
    TextDrawLetterSize(TDBoxHauling[4], 0.600000, 0.700003);
    TextDrawTextSize(TDBoxHauling[4], 298.500000, 66.500000);
    TextDrawSetOutline(TDBoxHauling[4], 1);
    TextDrawSetShadow(TDBoxHauling[4], 0);
    TextDrawAlignment(TDBoxHauling[4], 2);
    TextDrawColor(TDBoxHauling[4], -1);
    TextDrawBackgroundColor(TDBoxHauling[4], 255);
    TextDrawBoxColor(TDBoxHauling[4], 9109759);
    TextDrawUseBox(TDBoxHauling[4], 1);
    TextDrawSetProportional(TDBoxHauling[4], 1);
    TextDrawSetSelectable(TDBoxHauling[4], 0);

    TDBoxHauling[5] = TextDrawCreate(435.000000, 229.000000, "_");
    TextDrawFont(TDBoxHauling[5], 1);
    TextDrawLetterSize(TDBoxHauling[5], 0.600000, 0.700003);
    TextDrawTextSize(TDBoxHauling[5], 298.500000, 66.500000);
    TextDrawSetOutline(TDBoxHauling[5], 1);
    TextDrawSetShadow(TDBoxHauling[5], 0);
    TextDrawAlignment(TDBoxHauling[5], 2);
    TextDrawColor(TDBoxHauling[5], -1);
    TextDrawBackgroundColor(TDBoxHauling[5], 255);
    TextDrawBoxColor(TDBoxHauling[5], 9109759);
    TextDrawUseBox(TDBoxHauling[5], 1);
    TextDrawSetProportional(TDBoxHauling[5], 1);
    TextDrawSetSelectable(TDBoxHauling[5], 0);

    TDBoxHauling[6] = TextDrawCreate(435.000000, 247.000000, "_");
    TextDrawFont(TDBoxHauling[6], 1);
    TextDrawLetterSize(TDBoxHauling[6], 0.600000, 0.700003);
    TextDrawTextSize(TDBoxHauling[6], 298.500000, 66.500000);
    TextDrawSetOutline(TDBoxHauling[6], 1);
    TextDrawSetShadow(TDBoxHauling[6], 0);
    TextDrawAlignment(TDBoxHauling[6], 2);
    TextDrawColor(TDBoxHauling[6], -1);
    TextDrawBackgroundColor(TDBoxHauling[6], 255);
    TextDrawBoxColor(TDBoxHauling[6], 9109759);
    TextDrawUseBox(TDBoxHauling[6], 1);
    TextDrawSetProportional(TDBoxHauling[6], 1);
    TextDrawSetSelectable(TDBoxHauling[6], 0);

    TDBoxHauling[7] = TextDrawCreate(435.000000, 266.000000, "_");
    TextDrawFont(TDBoxHauling[7], 1);
    TextDrawLetterSize(TDBoxHauling[7], 0.600000, 0.700003);
    TextDrawTextSize(TDBoxHauling[7], 298.500000, 66.500000);
    TextDrawSetOutline(TDBoxHauling[7], 1);
    TextDrawSetShadow(TDBoxHauling[7], 0);
    TextDrawAlignment(TDBoxHauling[7], 2);
    TextDrawColor(TDBoxHauling[7], -1);
    TextDrawBackgroundColor(TDBoxHauling[7], 255);
    TextDrawBoxColor(TDBoxHauling[7], 9109759);
    TextDrawUseBox(TDBoxHauling[7], 1);
    TextDrawSetProportional(TDBoxHauling[7], 1);
    TextDrawSetSelectable(TDBoxHauling[7], 0);

    TDBoxHauling[8] = TextDrawCreate(435.000000, 286.000000, "_");
    TextDrawFont(TDBoxHauling[8], 1);
    TextDrawLetterSize(TDBoxHauling[8], 0.600000, 0.700003);
    TextDrawTextSize(TDBoxHauling[8], 298.500000, 66.500000);
    TextDrawSetOutline(TDBoxHauling[8], 1);
    TextDrawSetShadow(TDBoxHauling[8], 0);
    TextDrawAlignment(TDBoxHauling[8], 2);
    TextDrawColor(TDBoxHauling[8], -1);
    TextDrawBackgroundColor(TDBoxHauling[8], 255);
    TextDrawBoxColor(TDBoxHauling[8], 9109759);
    TextDrawUseBox(TDBoxHauling[8], 1);
    TextDrawSetProportional(TDBoxHauling[8], 1);
    TextDrawSetSelectable(TDBoxHauling[8], 0);

    TDBoxHauling[9] = TextDrawCreate(435.000000, 307.000000, "_");
    TextDrawFont(TDBoxHauling[9], 1);
    TextDrawLetterSize(TDBoxHauling[9], 0.600000, 0.700003);
    TextDrawTextSize(TDBoxHauling[9], 298.500000, 66.500000);
    TextDrawSetOutline(TDBoxHauling[9], 1);
    TextDrawSetShadow(TDBoxHauling[9], 0);
    TextDrawAlignment(TDBoxHauling[9], 2);
    TextDrawColor(TDBoxHauling[9], -1);
    TextDrawBackgroundColor(TDBoxHauling[9], 255);
    TextDrawBoxColor(TDBoxHauling[9], 9109759);
    TextDrawUseBox(TDBoxHauling[9], 1);
    TextDrawSetProportional(TDBoxHauling[9], 1);
    TextDrawSetSelectable(TDBoxHauling[9], 0);

    TDMoneyHauling[1] = TextDrawCreate(414.000000, 150.000000, "$278.90");
    TextDrawFont(TDMoneyHauling[1], 3);
    TextDrawLetterSize(TDMoneyHauling[1], 0.283333, 1.300000);
    TextDrawTextSize(TDMoneyHauling[1], 471.500000, 17.000000);
    TextDrawSetOutline(TDMoneyHauling[1], 1);
    TextDrawSetShadow(TDMoneyHauling[1], 0);
    TextDrawAlignment(TDMoneyHauling[1], 1);
    TextDrawColor(TDMoneyHauling[1], 9109757);
    TextDrawBackgroundColor(TDMoneyHauling[1], 255);
    TextDrawBoxColor(TDMoneyHauling[1], 16711935);
    TextDrawUseBox(TDMoneyHauling[1], 0);
    TextDrawSetProportional(TDMoneyHauling[1], 1);
    TextDrawSetSelectable(TDMoneyHauling[1], 1);

    TDMoneyHauling[2] = TextDrawCreate(414.000000, 169.000000, "$278.90");
    TextDrawFont(TDMoneyHauling[2], 3);
    TextDrawLetterSize(TDMoneyHauling[2], 0.283333, 1.300000);
    TextDrawTextSize(TDMoneyHauling[2], 471.500000, 17.000000);
    TextDrawSetOutline(TDMoneyHauling[2], 1);
    TextDrawSetShadow(TDMoneyHauling[2], 0);
    TextDrawAlignment(TDMoneyHauling[2], 1);
    TextDrawColor(TDMoneyHauling[2], 9109757);
    TextDrawBackgroundColor(TDMoneyHauling[2], 255);
    TextDrawBoxColor(TDMoneyHauling[2], 16711935);
    TextDrawUseBox(TDMoneyHauling[2], 0);
    TextDrawSetProportional(TDMoneyHauling[2], 1);
    TextDrawSetSelectable(TDMoneyHauling[2], 1);

    TDMoneyHauling[3] = TextDrawCreate(414.000000, 188.000000, "$278.90");
    TextDrawFont(TDMoneyHauling[3], 3);
    TextDrawLetterSize(TDMoneyHauling[3], 0.283333, 1.300000);
    TextDrawTextSize(TDMoneyHauling[3], 471.500000, 17.000000);
    TextDrawSetOutline(TDMoneyHauling[3], 1);
    TextDrawSetShadow(TDMoneyHauling[3], 0);
    TextDrawAlignment(TDMoneyHauling[3], 1);
    TextDrawColor(TDMoneyHauling[3], 9109757);
    TextDrawBackgroundColor(TDMoneyHauling[3], 255);
    TextDrawBoxColor(TDMoneyHauling[3], 16711935);
    TextDrawUseBox(TDMoneyHauling[3], 0);
    TextDrawSetProportional(TDMoneyHauling[3], 1);
    TextDrawSetSelectable(TDMoneyHauling[3], 1);

    TDMoneyHauling[4] = TextDrawCreate(414.000000, 206.000000, "$278.90");
    TextDrawFont(TDMoneyHauling[4], 3);
    TextDrawLetterSize(TDMoneyHauling[4], 0.283333, 1.300000);
    TextDrawTextSize(TDMoneyHauling[4], 471.500000, 17.000000);
    TextDrawSetOutline(TDMoneyHauling[4], 1);
    TextDrawSetShadow(TDMoneyHauling[4], 0);
    TextDrawAlignment(TDMoneyHauling[4], 1);
    TextDrawColor(TDMoneyHauling[4], 9109757);
    TextDrawBackgroundColor(TDMoneyHauling[4], 255);
    TextDrawBoxColor(TDMoneyHauling[4], 16711935);
    TextDrawUseBox(TDMoneyHauling[4], 0);
    TextDrawSetProportional(TDMoneyHauling[4], 1);
    TextDrawSetSelectable(TDMoneyHauling[4], 1);

    TDMoneyHauling[5] = TextDrawCreate(414.000000, 226.000000, "$278.90");
    TextDrawFont(TDMoneyHauling[5], 3);
    TextDrawLetterSize(TDMoneyHauling[5], 0.283333, 1.300000);
    TextDrawTextSize(TDMoneyHauling[5], 471.500000, 17.000000);
    TextDrawSetOutline(TDMoneyHauling[5], 1);
    TextDrawSetShadow(TDMoneyHauling[5], 0);
    TextDrawAlignment(TDMoneyHauling[5], 1);
    TextDrawColor(TDMoneyHauling[5], 9109757);
    TextDrawBackgroundColor(TDMoneyHauling[5], 255);
    TextDrawBoxColor(TDMoneyHauling[5], 16711935);
    TextDrawUseBox(TDMoneyHauling[5], 0);
    TextDrawSetProportional(TDMoneyHauling[5], 1);
    TextDrawSetSelectable(TDMoneyHauling[5], 1);

    TDMoneyHauling[6] = TextDrawCreate(414.000000, 244.000000, "$278.90");
    TextDrawFont(TDMoneyHauling[6], 3);
    TextDrawLetterSize(TDMoneyHauling[6], 0.283333, 1.300000);
    TextDrawTextSize(TDMoneyHauling[6], 471.500000, 17.000000);
    TextDrawSetOutline(TDMoneyHauling[6], 1);
    TextDrawSetShadow(TDMoneyHauling[6], 0);
    TextDrawAlignment(TDMoneyHauling[6], 1);
    TextDrawColor(TDMoneyHauling[6], 9109757);
    TextDrawBackgroundColor(TDMoneyHauling[6], 255);
    TextDrawBoxColor(TDMoneyHauling[6], 16711935);
    TextDrawUseBox(TDMoneyHauling[6], 0);
    TextDrawSetProportional(TDMoneyHauling[6], 1);
    TextDrawSetSelectable(TDMoneyHauling[6], 1);

    TDMoneyHauling[7] = TextDrawCreate(414.000000, 263.000000, "$278.90");
    TextDrawFont(TDMoneyHauling[7], 3);
    TextDrawLetterSize(TDMoneyHauling[7], 0.283333, 1.300000);
    TextDrawTextSize(TDMoneyHauling[7], 471.500000, 17.000000);
    TextDrawSetOutline(TDMoneyHauling[7], 1);
    TextDrawSetShadow(TDMoneyHauling[7], 0);
    TextDrawAlignment(TDMoneyHauling[7], 1);
    TextDrawColor(TDMoneyHauling[7], 9109757);
    TextDrawBackgroundColor(TDMoneyHauling[7], 255);
    TextDrawBoxColor(TDMoneyHauling[7], 16711935);
    TextDrawUseBox(TDMoneyHauling[7], 0);
    TextDrawSetProportional(TDMoneyHauling[7], 1);
    TextDrawSetSelectable(TDMoneyHauling[7], 1);

    TDMoneyHauling[8] = TextDrawCreate(414.000000, 282.000000, "$278.90");
    TextDrawFont(TDMoneyHauling[8], 3);
    TextDrawLetterSize(TDMoneyHauling[8], 0.283333, 1.300000);
    TextDrawTextSize(TDMoneyHauling[8], 471.500000, 17.000000);
    TextDrawSetOutline(TDMoneyHauling[8], 1);
    TextDrawSetShadow(TDMoneyHauling[8], 0);
    TextDrawAlignment(TDMoneyHauling[8], 1);
    TextDrawColor(TDMoneyHauling[8], 9109757);
    TextDrawBackgroundColor(TDMoneyHauling[8], 255);
    TextDrawBoxColor(TDMoneyHauling[8], 16711935);
    TextDrawUseBox(TDMoneyHauling[8], 0);
    TextDrawSetProportional(TDMoneyHauling[8], 1);
    TextDrawSetSelectable(TDMoneyHauling[8], 1);

    TDMoneyHauling[9] = TextDrawCreate(414.000000, 304.000000, "$278.90");
    TextDrawFont(TDMoneyHauling[9], 3);
    TextDrawLetterSize(TDMoneyHauling[9], 0.283333, 1.300000);
    TextDrawTextSize(TDMoneyHauling[9], 471.500000, 17.000000);
    TextDrawSetOutline(TDMoneyHauling[9], 1);
    TextDrawSetShadow(TDMoneyHauling[9], 0);
    TextDrawAlignment(TDMoneyHauling[9], 1);
    TextDrawColor(TDMoneyHauling[9], 9109757);
    TextDrawBackgroundColor(TDMoneyHauling[9], 255);
    TextDrawBoxColor(TDMoneyHauling[9], 16711935);
    TextDrawUseBox(TDMoneyHauling[9], 0);
    TextDrawSetProportional(TDMoneyHauling[9], 1);
    TextDrawSetSelectable(TDMoneyHauling[9], 1);
}
