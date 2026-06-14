
CreateArmsPoint()
{
	//JOBS
	new strings[214], strings2[214];
	CreateDynamicPickup(1239, 23, 321.5652,1121.2504,1083.8828, -1);
	format(strings, sizeof(strings), ""RED_E"Job: Arms Dealer\n"YELLOW_E"'/joinjob' "WHITE_E"to be an Arms Dealer\n"YELLOW_E"'/buyschematic' "WHITE_E"to buy gun schematic\n"YELLOW_E"'/buypacket' "WHITE_E"to buy gun material package\nAvailable packages: "GREEN_E"%d", StockMaterial);
	Material = CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 321.5652,1121.2504,1083.8828, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); //

	CreateDynamicPickup(1239, 23, -882.1044,1110.8616,5442.8203, -1, -1, -1, 5.0);
	format(strings2, sizeof(strings2), ""RED_E"Job: Drugs  Dealer\n"YELLOW_E"'/joinjob' "WHITE_E"to be an Drug Dealer\n"YELLOW_E"'/buypacket' "WHITE_E"to buy drugs package\nAvailable packages: "GREEN_E"%d", StockCrack);
	Crack = CreateDynamic3DTextLabel(strings2, COLOR_ARWIN, -882.1044,1110.8616,5442.8203, 5.0); // product

	CreateDynamicPickup(1239, 23, 1273.3732,392.2403,19.5614, -1, -1, -1, 5.0);
	format(strings2, sizeof(strings2), ""RED_E"Job: Smuggle  Dealer\n"YELLOW_E"'/joinjob' "WHITE_E"to be an Smuggle Dealer");
	CreateDynamic3DTextLabel(strings2, COLOR_ARWIN, 1273.3732,392.2403,19.5614, 5.0); // product
}
