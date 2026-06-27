//HARGA
new 
	HargaBensin,
	HargaAnggur, 
	HargaBlueberry, 
	HargaStrawberry, 
	HargaGandum, 
	HargaTomat, 
	FishPrice, 
	ServerMoney,
	SAPDArmoury,
	SAPDAmmo,
	BalanceSAPD,
	BalanceSAGS,
	BalanceSAMD,
	BalanceSAN,
	FactionBankSAPD,
	FactionBankSAGS,
	FactionBankSAMD,
	FactionBankSAN;

new 
	ammountsellwheat,
	ammountsellonion,
	ammountsellcarrot,
	ammountsellpotato,
	ammountsellcorn
;

new 
	StockMaterial,
	StockMarijuana,
	StockComponent,
	StockCrack,
	StockCrateFish,
	StockCrateFish2,
	StockCrateLumber,
	StockCratePlant;


new SELLFARM2, SELLFISH, SELLFISH2;	
new MoneyPickup,
	Text3D:MoneyText,
	// Fish1,
	Text3D:Fish2,
	Text3D:Fish3,
	Compo1,
	Text3D:Compo2,
	Text3D:Timber,
	Text3D:Material,
	Text3D:Crack,
	Text3D:PlantCrate;

CreateServerPoint()
{
	// StockCrateFish = 0;
	// StockCrateFish2 = 0;
	// StockCrateLumber = 0;
	// StockCratePlant = 0;

	FishStockRefresh();
	ComponentStockRefresh();

	FishPrice = Random(450, 800);
	HargaAnggur = Random(16,22);
	HargaBlueberry = Random(16,22);
	HargaStrawberry = Random(16,22);
	HargaGandum = Random(16,22);
	HargaTomat = Random(16,22);
	HargaBensin = Random(100,200);

	if(IsValidDynamic3DTextLabel(PlantCrate)) DestroyDynamic3DTextLabel(PlantCrate); 
	if(IsValidDynamic3DTextLabel(Timber)) DestroyDynamic3DTextLabel(Timber); 
	if(IsValidDynamic3DTextLabel(MoneyText))  DestroyDynamic3DTextLabel(MoneyText);
	if(IsValidDynamicPickup(MoneyPickup)) DestroyDynamicPickup(MoneyPickup);
		
	//Server Money
	new strings[512];
	//Fish Price
	DestroyDynamicObject(SELLFISH);
	SELLFISH = CreateDynamicObject(18244, 2843.075195, -1516.672241, 16.355049, 88.599990, 89.999992, 0.000000, -1, -1, -1, 300.00, 300.00); 
	format(strings,sizeof(strings),""PINK_E"Fish Factory\n"WHITE_E"Fish Price: \n"GREEN_E"$%s"WHITE_E"/lb", FormatMoney(FishPrice));
	SetDynamicObjectMaterialText(SELLFISH, 0, strings, 130, "Arial", 40, 1, 0xFFFFFFFF, 0xFF000000, 1);

	DestroyDynamicObject(SELLFISH2);
	SELLFISH2 = CreateDynamicObject(2790, -763.116272, 1637.763916, 29.076900, 0.000000, 0.000000, 0.500000, -1, -1, -1, 300.00, 300.00); 
	format(strings,sizeof(strings),""PINK_E"Fish Factory\n"WHITE_E"Fish Price: \n"GREEN_E"$%s"WHITE_E"/lb", FormatMoney(FishPrice));
	SetDynamicObjectMaterialText(SELLFISH2, 1, strings, 130, "Arial", 48, 1, -65366, -16777216, 1);
	
	//Plant Farmer
	DestroyDynamicObject(SELLFARM2);
	SELLFARM2 = CreateDynamicObject(18244, -371.336853, -1427.711547, 30.534753, 93.300041, -0.499999, -90.200012);
	format(strings,sizeof(strings),""PURPLE_E2"Plant Price\n{FFFFFF}Wheat: "GREEN_E"$0.%s"WHITE_E"\nOnion: "GREEN_E"$0.%s"WHITE_E"\nCarrot: "GREEN_E"$0.%s"WHITE_E"\nPotato: "GREEN_E"$0.%s"WHITE_E"\nCorn: "GREEN_E"$0.%s"WHITE_E"", FormatMoney(HargaAnggur), FormatMoney(HargaBlueberry), FormatMoney(HargaStrawberry), FormatMoney(HargaGandum), FormatMoney(HargaTomat));
	SetDynamicObjectMaterialText(SELLFARM2, 0, strings, 100, "Arial", 25, 1, 0xFFFFFFFF, 0xFF000000, 1);

	CreateDynamicPickup(1239, 23, -1425.73, -1528.01, 102.33, -1);
	format(strings, sizeof(strings), ""AQUA_E"Timber Storage\n"WHITE_E"Use "YELLOW_E"'/unloadtimber' "WHITE_E"to sell collected timber");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, -1425.73, -1528.01, 102.33, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate
	
	CreateDynamicPickup(1271, 23, -1446.71, -1544.53, 102.25, -1);
	format(strings, sizeof(strings), ""AQUA_E"Timber crate\n"WHITE_E"Available crates: "GREEN_E"%d "YELLOW_E"/ 40\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup a crate", StockCrateLumber);
	Timber = CreateDynamic3DTextLabel(strings, COLOR_ARWIN, -1446.71, -1544.53, 102.25, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	//Plant Component
	CreateDynamicPickup(1271, 23, -366.3686,-1419.0941,25.7266, -1);
	format(strings, sizeof(strings), ""AQUA_E"Plant crate\n"WHITE_E"Available crates: "GREEN_E"%d "YELLOW_E"/ 40\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup a crate", StockCratePlant);
	PlantCrate = CreateDynamic3DTextLabel(strings, COLOR_ARWIN, -366.3686,-1419.0941,25.7266, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate
}

Server_Percent(price)
{
    return floatround((float(price) / 100) * 85);
}

Server_AddPercent(price)
{
    new money = (price - Server_Percent(price));
    ServerMoney = ServerMoney + money;
    Server_Save();
}

Server_AddMoney(amount)
{
    ServerMoney = ServerMoney + amount;
    Server_Save();
}

Server_MinMoney(amount)
{
    ServerMoney -= amount;
    Server_Save();
}

Crate_Save()
{
    new str[2024];

	// CreateServerPoint();
    format(str, sizeof(str), "UPDATE crate SET fish='%d', fish2='%d', timber='%d', plant='%d' WHERE id=0",
	StockCrateFish,
	StockCrateFish2,
	StockCrateLumber,
	StockCratePlant
	);
    return mysql_tquery(g_SQL, str);
}

function LoadCrate()
{
	cache_get_value_name_int(0, "fish", StockCrateFish);
	cache_get_value_name_int(0, "fish2", StockCrateFish2);
	cache_get_value_name_int(0, "timber", StockCrateLumber);
	cache_get_value_name_int(0, "plant", StockCratePlant);
	// CreateServerPoint();
}

Server_Save()
{
    new str[2024];

	CreateServerPoint();
    format(str, sizeof(str), "UPDATE server SET component='%d', crack='%d', material='%d', armoury='%d', sapdammo='%d', balancesapd='%d', balancesags='%d', balancesamd='%d', balancesan='%d', factionbanksapd='%d', factionbanksags='%d', factionbanksamd='%d', factionbanksan='%d' WHERE id=0",
	StockComponent,
	StockCrack,
	StockMaterial,
	SAPDArmoury,
	SAPDAmmo,
	BalanceSAPD,
	BalanceSAGS,
	BalanceSAMD,
	BalanceSAN,
	FactionBankSAPD,
	FactionBankSAGS,
	FactionBankSAMD,
	FactionBankSAN
	);
    return mysql_tquery(g_SQL, str);
}

function LoadServer()
{
	cache_get_value_name_int(0, "component", StockComponent);
	cache_get_value_name_int(0, "crack", StockCrack);
	cache_get_value_name_int(0, "material", StockMaterial);
	cache_get_value_name_int(0, "armoury", SAPDArmoury);
	cache_get_value_name_int(0, "sapdammo", SAPDAmmo);
	cache_get_value_name_int(0, "balancesapd", BalanceSAPD);
	cache_get_value_name_int(0, "balancesags", BalanceSAGS);
	cache_get_value_name_int(0, "balancesamd", BalanceSAMD);
	cache_get_value_name_int(0, "balancesan", BalanceSAN);
	cache_get_value_name_int(0, "factionbanksapd", FactionBankSAPD);
	cache_get_value_name_int(0, "factionbanksags", FactionBankSAGS);
	cache_get_value_name_int(0, "factionbanksamd", FactionBankSAMD);
	cache_get_value_name_int(0, "factionbanksan", FactionBankSAN);
	CreateServerPoint();
}

FishStockRefresh()
{
	new strings[212];
	// if(IsValidDynamicPickup(Fish1)) DestroyDynamicPickup(Fish1);
	if(IsValidDynamic3DTextLabel(Fish2)) DestroyDynamic3DTextLabel(Fish2);
	if(IsValidDynamic3DTextLabel(Fish3)) DestroyDynamic3DTextLabel(Fish3);  
	//Crate Fish
	CreateDynamicPickup(1271, 23, 2836.9445,-1539.5584,11.0991, -1);
	CreateDynamicPickup(1271, 23, -759.54, 1640.60, 27.39, -1);
	format(strings, sizeof(strings), "{00FFFF}Canned Fish Crates\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup crate\nFish Available: "GREEN_E"%d "YELLOW_E"/ 40", StockCrateFish);
	Fish2 = CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 2836.9445,-1539.5584,11.0991, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate
	format(strings, sizeof(strings), "{00FFFF}Canned Fish Crates\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup crate\nFish Available: "GREEN_E"%d "YELLOW_E"/ 40", StockCrateFish2);
	Fish3 = CreateDynamic3DTextLabel(strings, COLOR_ARWIN, -759.54, 1640.60, 27.39, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate
}

ComponentStockRefresh()
{
	if(IsValidDynamicPickup(Compo1)) DestroyDynamicPickup(Compo1);
	if(IsValidDynamic3DTextLabel(Compo2)) DestroyDynamic3DTextLabel(Compo2); 
	new strings[212];
	Compo1 = CreateDynamicPickup(2969, 23, 854.5825,-605.2015,18.4219, -1);
	format(strings, sizeof(strings), "{00FFFF}Component Factory\n"WHITE_E"Price: "GREEN_E"$0.50 "WHITE_E"/ unit\n"WHITE_E"Stock: "GREEN_E"%d "YELLOW_E"/ 50000\n"WHITE_E"Use '"YELLOW_E"/buycomponent"WHITE_E"' to buy components", StockComponent);
	Compo2 = CreateDynamic3DTextLabel(strings, COLOR_WHITE, 854.5825,-605.2015,18.4219, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate
}
