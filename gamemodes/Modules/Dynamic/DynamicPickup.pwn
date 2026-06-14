#include <YSI\y_hooks>
hook OnGameModeInit()
{
	new strings[500];

	CreateDynamicPickup(1239, 23, 2591.9897,-2218.4592,13.5469, -1);
	format(strings, sizeof(strings), "{00FFFF}[Starterpack]\n"YELLOW_E"'/starterpack' "WHITE_E"- To get a starter pack");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 2591.9897,-2218.4592,13.5469, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // starterpack
	CreateDynamicActor(71, 2590.9800,-2218.5249,13.5469,270.4465, true, 100.0, 0, 0);
	
	//
	CreateDynamicPickup(1239, 23, 1424.31, 1546.21, 3010.83, -1);
	format(strings, sizeof(strings), "{00FFFF}[City Hall]\n"YELLOW_E"'/sellproperty' "WHITE_E"- To sell your property\n"YELLOW_E"'/giveworkshop' "WHITE_E"- To give your bisnis workshop to other players\n"YELLOW_E"'/givehouse' "WHITE_E"- To give your house to other players\n"YELLOW_E"'/givebisnis' "WHITE_E"- To give your bisnis to other players\n"YELLOW_E"'/giveflat' "WHITE_E"- To give your flat to other players");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 1424.31, 1546.21, 3010.83, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // ID Card

	// CreateDynamicPickup(1239, 23, 1657.9524,-1394.4664,13.5469, -1);
	// format(strings, sizeof(strings), "{00FFFF}[Insurance]\n"YELLOW_E"/buyinsurance "WHITE_E"- buy insurance\n"YELLOW_E"/claiminsurance - "WHITE_E"claim insurance\n"YELLOW_E"/sellpv - "WHITE_E"sell vehicle");
	// CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 1657.9524,-1394.4664,13.5469, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Veh insurance

	//IMPOUND
 	CreateDynamic3DTextLabel(""YELLOW_E"Impound Center\n{00FFFF}'/unimpound' "WHITE_E"untuk mengunimpound kendaraan", COLOR_WHITE, 1579.75, -1631.52, 13.38, 10.0);
 	CreateDynamicPickup(1239, 23, 1579.75, -1631.52, 13.38, -1); // TEMPAT UNTUK UNIMPOUND

	// CreateDynamicPickup(1239, 23, 1320.6910,739.4119,111.3203, -1);
	// format(strings, sizeof(strings), "{00FFFF}[Ticket]\n"YELLOW_E"/payticket - "WHITE_E"to pay ticket\n"YELLOW_E"/unlocktire - "WHITE_E"to unlock tire vehicle\n"YELLOW_E"/buyyplate - "WHITE_E"untuk membeli plate");
	// CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 1320.6910,739.4119,111.3203, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Ticket
	
	// CreateDynamicPickup(1247, 23, 226.8309, 114.6640, 999.0156, -1);
	// format(strings, sizeof(strings), "{00FFFF}[Arrest Point]\n"YELLOW_E"/arrest - arrest wanted player");
	// CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 226.8309, 114.6640, 999.0156, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // arrest
	
	CreateDynamicPickup(1240, 23, 1142.38, -1330.74, 13.62, -1);
	format(strings, sizeof(strings), "{00FFFF}[Hospital]\n"YELLOW_E"/dropinjured");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 1142.38, -1330.74, 13.62, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // hospital

	CreateDynamicPickup(1240, 23, 1355.18, 1543.21, 2223.087, -1);
	format(strings, sizeof(strings), "{00FFFF}[Pharmacy]\n"YELLOW_E"/takepills");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 1355.18, 1543.21, 2223.08, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // hospital

	// CreateDynamicPickup(1274, 23, 1429.3341,-985.9102,996.1050, -1);
	// format(strings, sizeof(strings), "{00FFFF}[Bank Center]\n"YELLOW_E"/bank\n"YELLOW_E"/deposit\n"YELLOW_E"/withdraw\n/newrek\n "WHITE_E"- access rekening");
	// CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 1429.3341,-985.9102,996.1050, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // bank
	
	// CreateDynamicPickup(1239, 23, 1515.9568,1421.7207,489.6216, -1);
	// format(strings, sizeof(strings), "{00FFFF}[Advertisement]\n"YELLOW_E"/ad "WHITE_E"- public ads");
	// CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 1515.9568,1421.7207,489.6216, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // iklan

	// CreateDynamicPickup(1239, 23, 144.52, -1886.32, 1.56, -1);
	// format(strings, sizeof(strings), "{00FFFF}[Boat Dealership]\n"YELLOW_E"/buyboat "WHITE_E"to purchase a boat");
	// CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 144.52, -1886.32, 1.56, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	// format(strings, sizeof(strings), "{00FFFF}[Bike Dealer]\n"YELLOW_E"/buyvehicle "WHITE_E"to purchase a bicycle");
	// CreateDynamic3DTextLabel(strings, -1,701.6057,-518.9899,16.3284,10.0);
	// CreateDynamicPickup(1239, 23, 701.6057,-518.9899,16.3284, -1);
	
	//ShowroomVIP
	CreateDynamicPickup(1239, 23, 563.3856,-1292.2179,17.2482, -1);
	format(strings, sizeof(strings), "{00FFFF}[VIP Dealership]\n"YELLOW_E"/buyvehicle "WHITE_E"To purchase exclusive vehicles for donators");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 563.3856,-1292.2179,17.2482, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamicPickup(1239, 23, 2131.7900,-1151.1900,24.0600, -1);
	format(strings, sizeof(strings), "{00FFFF}[Suv Dealership]\n"YELLOW_E"/buyvehicle "WHITE_E"To purchase a vehicle");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 2131.7900,-1151.1900,24.0600, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamicPickup(1239, 23, -265.70, -2213.12, 29.04, -1);
	format(strings, sizeof(strings), "{00FFFF}[Jobs Dealership]\n"YELLOW_E"/buyvehicle "WHITE_E"To purchase a vehicle");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, -265.70, -2213.12, 29.04, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamicPickup(1239, 23, 2357.6700,-1990.5500,13.5400, -1);
	format(strings, sizeof(strings), "{00FFFF}[Saloons Dealership]\n"YELLOW_E"/buyvehicle "WHITE_E"To purchase a vehicle");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 2357.6700,-1990.5500,13.5400, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamicPickup(1239, 23, 2281.3900, -2364.770, 13.5500, -1);
	format(strings, sizeof(strings), "{00FFFF}[Sports Dealership]\n"YELLOW_E"/buyvehicle "WHITE_E"To purchase a vehicle");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 2281.3900, -2364.770, 13.5500, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamicPickup(1239, 23, 1083.1200, -1226.7700,  15.8200, -1);
	format(strings, sizeof(strings), "{00FFFF}[Lowriders Dealership]\n"YELLOW_E"/buyvehicle "WHITE_E"To purchase a vehicle");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 1083.1200, -1226.7700,  15.8200, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamicPickup(1239, 23, 1685.4528,-1464.4073,13.5469, -1);
	format(strings, sizeof(strings), ""AQUA_E"Job: Taxi Driver\n"YELLOW_E"/joinjob - "WHITE_E"To Join Job\n"WHITE_E"You can buy Taxi here using "YELLOW_E"/buytaxi");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 1685.4528,-1464.4073,13.5469, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamicPickup(1239, 23, 1289.0930,-1272.1663,13.5422, -1);
	format(strings, sizeof(strings), ""AQUA_E"Job: Builder\n"YELLOW_E"/joinjob - "WHITE_E"To Join Job");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 1289.0930,-1272.1663,13.5422, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamicPickup(1239, 23, -1432.7500,-1538.4900,102.2578, -1);
	format(strings, sizeof(strings), ""AQUA_E"Job: Lumberjack\n"YELLOW_E"/joinjob "WHITE_E"to be a Lumberjack\n"YELLOW_E"/buychainsaw "WHITE_E"to buy chainsaw");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, -1432.7500,-1538.4900,102.2578, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamicPickup(1239, 23, -77.1687,-1136.5388,1.0781, -1);
	format(strings, sizeof(strings), ""AQUA_E"Job: Trucker Driver\n"YELLOW_E"/joinjob - "WHITE_E"To Join Job\n"WHITE_E"You can buy Truck here using "YELLOW_E"/buytruck");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, -77.1687,-1136.5388,1.0781, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamicPickup(1239, 23, -382.7033,-1438.9998,26.1691, -1);
	format(strings, sizeof(strings), ""AQUA_E"Job: Farmer\n"YELLOW_E"/joinjob - "WHITE_E"To Join Job");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, -382.7033,-1438.9998,26.1691, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamicPickup(1239, 23, 2844.0684,-1516.6871,11.3002, -1);
	format(strings, sizeof(strings), "{00FFFF}Fish Factory\n"YELLOW_E"/Sellallfish "WHITE_E"- to sell fish");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 2844.0684,-1516.6871,11.3002, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamicPickup(1239, 23, -769.01, 1637.18, 27.32, -1);
	format(strings, sizeof(strings), "{00FFFF}Fish Factory\n"YELLOW_E"/Sellallfish "WHITE_E"- to sell fish");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, -769.01, 1637.18, 27.32, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	//Plant unload Component
	CreateDynamicPickup(1271, 23, 2792.4355,-2456.1199,13.6325, -1);
	format(strings, sizeof(strings), ""AQUA_E"Plant/Timber Dropoff\n"WHITE_E"use "YELLOW_E"'/unloadcrate' "WHITE_E"to unload crate");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 2792.4355,-2456.1199,13.6325, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate
	
	//Crate Component
	CreateDynamicPickup(1271, 23, 335.0611, 896.4723, 21.2162, -1);
	format(strings, sizeof(strings), "== [Component crate] ==\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup crate");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 335.0611, 896.4723, 21.2162, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate
	
	//Crate unload Component
	CreateDynamicPickup(1271, 23, 797.7953,-616.8799,16.3359, -1);
	format(strings, sizeof(strings), ""AQUA_E"Component Dropoff\n"WHITE_E"use "YELLOW_E"'/unloadcrate' "WHITE_E"to unload crates.");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 797.7953,-616.8799,16.3359, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate
	
	// CreateDynamicPickup(1271, 23, 2836.9445,-1539.5584,11.0991, -1);
	// format(strings, sizeof(strings), "{00FFFF}Canned Fish Crates\n"WHITE_E"Use "YELLOW_E"'/getcrate' "WHITE_E"to pickup crate\nFish Available: "GREEN_E"%d "YELLOW_E"/ 40", StockCrateFish);
	// CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 2836.3945,-1541.1984,11.0991, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	//Crate Unload Fish
	CreateDynamicPickup(1271, 23, -577.1335,-503.6530,25.5107, -1);
	format(strings, sizeof(strings), ""AQUA_E"Fish Dropoff\n"WHITE_E"use "YELLOW_E"'/unloadcrate' "WHITE_E"to unload crate");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, -577.1335,-503.6530,25.5107, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	//GARAGE PICKUP NEWS
	GaragePickup[0] = CreateDynamicCP(2485.8213,2379.3203,7.0685, 4.0, -1, 5, -1, 5.0); // untuk keluar
	CreateDynamicPickup(19130, 23, 2485.8213,2379.3203,7.0685, -1, 5, -1, 7);
	CreateDynamic3DTextLabel(""AQUA_E"[PG:1]\n"WHITE_E"News Parking Garage", COLOR_YELLOW, 2485.8213,2379.3203,7.0685+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 5);
	GaragePickup[1] = CreateDynamicCP(656.4168,-1326.0953,13.5521, 4.0, -1, -1, -1, 5.0); // untuk masuk
	CreateDynamicPickup(19130, 23, 656.4168,-1326.0953,13.5521, -1, -1, -1, 7);
	CreateDynamic3DTextLabel(""AQUA_E"[PG:1]\n"WHITE_E"News Parking Garage", COLOR_YELLOW, 656.4168,-1326.0953,13.5521+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1);

	//GARAGE PICKUP RS
	GaragePickup[2] = CreateDynamicCP(2485.8213,2379.3203,7.0685, 4.0, -1, 6, -1, 5.0); // untuk keluar
	CreateDynamicPickup(19130, 23, 2485.8213,2379.3203,7.0685, -1, 6, -1, 7);
	CreateDynamic3DTextLabel(""AQUA_E"[PG:2]\n"WHITE_E"ASGH Parking Garage", COLOR_YELLOW, 2485.8213,2379.3203,7.0685+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 6);
	GaragePickup[3] = CreateDynamicCP(1178.5835,-1308.4675,13.7781, 4.0, -1, -1, -1, 5.0); // untuk masuk
	CreateDynamic3DTextLabel(""AQUA_E"[PG:2]\n"WHITE_E"ASGH Parking Garage", COLOR_YELLOW, 1178.5835,-1308.4675,13.7781+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1);
	CreateDynamicPickup(19130, 23, 1178.5835,-1308.4675,13.7781, -1, -1, -1, 7);
	
	//GARAGE PICKUP SAGS
	GaragePickup[4] = CreateDynamicCP(1133.8325,-2136.0264,-7.1010, 4.0, -1, -1, -1, 5.0); // untuk keluar
	CreateDynamicPickup(19130, 23, 1133.8325,-2136.0264,-7.1010, -1, -1, -1, 7);
	CreateDynamic3DTextLabel(""AQUA_E"[PG:3]\n"WHITE_E"SAGS Parking Garage", COLOR_YELLOW, 1133.8325,-2136.0264,-7.1010+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1);
	GaragePickup[5] = CreateDynamicCP(1470.6168,-1840.9789,13.5469, 4.0, -1, -1, -1, 5.0); // untuk masuk
	CreateDynamicPickup(19130, 23, 1470.6168,-1840.9789,13.5469, -1, -1, -1, 7);
	CreateDynamic3DTextLabel(""AQUA_E"[PG:3]\n"WHITE_E"SAGS Parking Garage", COLOR_YELLOW, 1470.6168,-1840.9789,13.5469+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1);
	
	//GARAGE PICKUP STASIUN
	GaragePickup[6] = CreateDynamicCP(2485.8213,2379.3203,7.0685, 4.0, -1, 8, -1, 5.0); // untuk keluar
	CreateDynamic3DTextLabel(""AQUA_E"[PG:4]\n"WHITE_E"Unity Parking Garage", COLOR_YELLOW, 2485.8213,2379.3203,7.0685+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 7);
	CreateDynamicPickup(19130, 23, 2485.8213,2379.3203,7.0685, -1, 8, -1, 7);
	GaragePickup[7] = CreateDynamicCP(1562.7300, -1606.2500, 13.3800, 4.0, -1, -1, -1, 5.0); // untuk masuk
	CreateDynamic3DTextLabel(""AQUA_E"[PG:4]\n"WHITE_E"Unity Parking Garage", COLOR_YELLOW, 1767.5198,-1887.3687,13.5916+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1);
	CreateDynamicPickup(19130, 23, 1562.7300, -1606.2500, 13.3800, -1, -1, -1, 7);

	//GARAGE PICKUP SAPD
	GaragePickup[8] = CreateDynamicCP(2485.8213,2379.3203,7.0685, 4.0, -1, 7, -1, 5.0); // untuk keluar
	CreateDynamic3DTextLabel(""AQUA_E"[PG:5]\n"WHITE_E"SAPD Parking Garage", COLOR_YELLOW, 2485.8213,2379.3203,7.0685+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, 8);
	CreateDynamicPickup(19130, 23, 2485.8213,2379.3203,7.0685, -1, 7, -1, 7);
	GaragePickup[9] = CreateDynamicCP(1562.73, -1606.25, 13.38, 4.0, -1, -1, -1, 5.0); // untuk masuk
	CreateDynamic3DTextLabel(""AQUA_E"[PG:5]\n"WHITE_E"SAPD Parking Garage", COLOR_YELLOW, 1562.73, -1606.25, 13.38+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1);
	CreateDynamicPickup(19130, 23, 1562.73, -1606.25, 13.38, -1, -1, -1, 7);

	//GARAGE PICKUP SAPD
	GaragePickup[8] = CreateDynamicCP(1601.53, -1670.24, 5.88, 4.0, -1, -1, -1, 5.0); // untuk keluar
	CreateDynamic3DTextLabel(""AQUA_E"[PG:6]\n"BLUE_E"SAPD Basement", COLOR_YELLOW, 1601.53, -1670.24, 5.88+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1);
	CreateDynamicPickup(19130, 23, 1601.53, -1670.24, 5.88, -1, -1, -1, 7);
	GaragePickup[9] = CreateDynamicCP(1584.49, -1632.83, 13.38, 4.0, -1, -1, -1, 5.0); // untuk masuk
	CreateDynamic3DTextLabel(""AQUA_E"[PG:6]\n"BLUE_E"SAPD Basement", COLOR_YELLOW, 1584.49, -1632.83, 13.38+0.7, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1);
	CreateDynamicPickup(19130, 23, 1584.49, -1632.83, 13.38, -1, -1, -1, 7);

	//FARMER
	CreateDynamicPickup(1239, 23, -372.3396, -1427.8840, 25.7266, -1); // jual BIBIT
	CreateDynamic3DTextLabel(""AQUA_E"Farm Storage\n"WHITE_E"Use "YELLOW_E"'/sellallplant' "WHITE_E"to sell harvested plants\n"WHITE_E"Use "YELLOW_E"'/buyseeds' "WHITE_E"to buy plant seeds\n\n"WHITE_E"Use "YELLOW_E"'/sellberries' "WHITE_E"to sell wild berries", COLOR_ARWIN,-372.3396, -1427.8840, 25.7266,10.0);

	//Mechanic
	CreateDynamicPickup(1239, 23, 1809.17, -2064.89, 13.55, -1);
	format(strings, sizeof(strings), "{00FFFF}[Mechanic Job]\n"YELLOW_E"/joinjob - "WHITE_E"To Join Job\n"WHITE_E"You can buy Tow Truck here using "YELLOW_E"/buytowtruck");
	CreateDynamic3DTextLabel(strings, COLOR_ARWIN, 1809.17, -2064.89, 13.55, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1); // Plate

	CreateDynamic3DTextLabel("[Bait Store]\n{00FFFF}'/buybait' "WHITE_E"untuk membeli Umpan ", COLOR_ARWIN,361.2099,-2032.1703,7.8359,10.0);
    CreateDynamicPickup(1239, 23, 361.2099,-2032.1703,7.8359, -1); // buybait
	return 1;
}
