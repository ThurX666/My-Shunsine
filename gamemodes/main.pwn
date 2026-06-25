
#include <a_samp>
#undef  MAX_PLAYERS
#define MAX_PLAYERS 100
#include <a_mysql>
#include <a_zones>
#include <streamer>
#include <sscanf2> 
#include <gvar>
#include <chrono>                   //by Southclaws
#include <crashdetect>
#include <YSI\y_timers>
#include <easyDialog> 
#include <eSelectionv2>             //by Emmet edited by Agus Syahputra
#include <selection>                // New Selection Dialog
#include <progress2>
#include <Pawn.CMD>
#include <PreviewModelDialog>       //by Gammix
#define ENABLE_3D_TRYG_YSI_SUPPORT
#include <3DTryg>
#include <EVF2>
#include <yom_buttons>
#include <garageblock>
#include <callbacks>
#include <nex-ac>                   //BY Nexus
#include <strlib>                   //by Slice      

#pragma option -E 
new DB:AO_DB, DBResult:AO_RESULT;

#define Production
//#define Local
//#define DEBUG_MODE

main(){}

//-----[ Modular Callback]-----
#include "./Modules/Components.inc"
#include "./Modules/Server/Color.pwn"
#include "./Modules/Server/editing.pwn"
#include "./Modules/mysql.pwn"
#include "./Modules/Define.pwn"
#include "./Modules/Variables.pwn"
#include "./Modules/Enums.pwn"
#include "./Modules/Toys.pwn"
#include "./Modules/Textdraw.pwn"
// #include "./Modules/Pack.inc"
//-----[ Modular Server ]-----
#include "./Modules/Server/Stock.pwn"
#include "./Modules/Server/FactionVehicle.pwn"
#include "./Modules/Server/Anims.pwn"
#include "./Modules/Server/Server.pwn"
#include "./Modules/Server/SchoolLicense.pwn"
#include "./Modules/Server/AllTexture.pwn"
#include "./Modules/Server/GreenZone.pwn"
#include "./Modules/Server/ProggresBar.pwn"
#include "./Modules/Inventory.pwn"
#include "./Modules/PHONE.pwn"
//-----[ Modular Property]-----
#include "./Modules/Property/Farm.pwn"
#include "./Modules/Property/Family.pwn"
#include "./Modules/Property/House.pwn"
#include "./Modules/Property/workshop.pwn"
#include "./Modules/Property/GasStation.pwn"
#include "./Modules/Property/PrivateGarage.pwn"
#include "./Modules/Property/Suite.pwn"
//-----[ Modular Dynamic]-----
#include "./Modules/Dynamic/DynamicLocation.pwn"
#include "./Modules/Dynamic/DynamicBasement.pwn"
#include "./Modules/Dynamic/DynamicDoor.pwn"
#include "./Modules/Dynamic/DynamicLocker.pwn"
#include "./Modules/Dynamic/DynamicGate.pwn"
#include "./Modules/Dynamic/DynamicAtm.pwn"
#include "./Modules/Dynamic/DynamicMapIcon.pwn"
#include "./Modules/Dynamic/DynamicPickup.pwn"
#include "./Modules/Dynamic/DynamicSpeedCam.pwn"
#include "./Modules/Dynamic/DynamicToll.pwn"
#include "./Modules/Dynamic/DyanmicActor.pwn"
#include "./Modules/Dynamic/DynamicForeger.pwn"
#include "./Modules/Dynamic/DynamicArrest.pwn"
#include "./Modules/Dynamic/DynamicDoorFaction.pwn"
//-----[ Modular Player]-----
#include "./Modules/Players/PlayerHBE.pwn"
#include "./Modules/Players/Basketball.pwn"
#include "./Modules/Players/PlayerHelmet.pwn"
#include "./Modules/Players/AdsPlayer.pwn"
#include "./Modules/Players/Contatcs.pwn"
#include "./Modules/Players/SkillsPlayer.pwn"
#include "./Modules/Players/Voucher.pwn"
#include "./Modules/Players/Report.pwn"
#include "./Modules/Players/WeaponBody.pwn"
#include "./Modules/Players/PlayerVehicle.pwn"
#include "./Modules/Players/MultiChar.pwn"
#include "./Modules/Players/PlayerRent.pwn"
#include "./Modules/Players/PlayerTags.pwn"
#include "./Modules/Players/Event.pwn"
#include "./Modules/Players/AskPlayer.pwn"
#include "./Modules/Players/ToysNew.pwn"
#include "./Modules/Players/weapon.pwn"
#include "./Modules/Players/Damage.pwn"
#include "./Modules/Players/Race.pwn"
#include "./Modules/Players/levelup.pwn"
#include "./Modules/Players/PlayerGPS.pwn"
#include "./Modules/Players/MyWarns.pwn"
#include "./Modules/Players/PlayerAFK.pwn"
#include "./Modules/Players/anti_spam.pwn"
//-----[ Modular Property]-----
#include "./Modules/Property/Flat.pwn"
#include "./Modules/Property/FurnStore.pwn"
#include "./Modules/Property/Dealership.pwn"
#include "./Modules/Property/Bisnis.pwn"
#include "./Modules/Property/GYM.pwn"
//-----[ Modular Vehicle Data]-----
#include "./Modules/VehicleData.pwn"
//-----[ Modular Jobs]-----
#include "./Modules/Jobs/ArmsDealer.pwn"
#include "./Modules/Jobs/Taxi.pwn"
#include "./Modules/Jobs/Mechanic.pwn"
#include "./Modules/Jobs/LumberJack.pwn"
#include "./Modules/Jobs/Trucker.pwn"
#include "./Modules/Jobs/Fishing.pwn"
#include "./Modules/Jobs/Farmer.pwn"
#include "./Modules/Jobs/Forklift.pwn"
#include "./Modules/Jobs/BusDriver.pwn"
#include "./Modules/Jobs/Sweeper.pwn"
#include "./Modules/Jobs/Smuggle.pwn"
#include "./Modules/Jobs/Trashmasters.pwn"
#include "./Modules/Jobs/Courier.pwn"
#include "./Modules/Jobs/Miner.pwn"
//-----[ Modular Command]-----
#include "./Modules/Command/Command.pwn"

//-----[ Modular Validation]-----
#include "./Modules/Validation/IsValidTarget.inc"
//-----[ Modular Faction]-----
#include "./Modules/Faction//Taser.pwn"
#include "./Modules/Faction/Spike.pwn"
#include "./Modules/Faction/Elm.pwn"
#include "./Modules/Faction/RoadBlock.pwn"
#include "./Modules/Faction/MDC.pwn"
#include "./Modules/Faction/CrimeRecod.pwn"
#include "./Modules/Faction/factionlocker.pwn"
#include "./Modules/Faction/FactionManage.pwn"
//-----[ Modular Modshop]-----
#include "./Modules/Modshop/Modshop.pwn"
//-----[ Modular Server]-----
#include "./Modules/Server/Selection.pwn"
#include "./Modules/Server/MappingServer.pwn"
#include "./Modules/Server/Map.pwn"
#include "./Modules/Server/anticheat.pwn"
//Player Auction
#include "./Modules/Players/NewbieSchool.pwn"
#include "./Modules/Players/Salary.pwn"
#include "./Modules/Players/Training.pwn"
//-----[ Modular Callback]-----
#include "./Modules/Function.pwn"
#include "./Modules/pTask.pwn"
#include "./Modules/Native.pwn"
#include "./Modules/OnPlayerLoad.pwn"
#include "./Modules/OnDialogResponse.pwn"
#include "./Modules/Elevator.pwn"

public OnGameModeInit()
{
	new MySQLOpt: option_id = mysql_init_options();
	mysql_set_option(option_id, AUTO_RECONNECT, true);
	g_SQL = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, option_id);
	if (g_SQL == MYSQL_INVALID_HANDLE || mysql_errno(g_SQL) != 0)
	{
		print("MySQL connection failed. Server is shutting down.");
		return 1;
	}
	print("MySQL connection is successful.");
	/*if((AO_DB = db_open("allbuildings.db")) == DB:0) print("All Buildings - Loading Failed (Database Could Not Be Opened).");
	else print("All Buildings - Loading Loaded (Database Opened).");*/
	mysql_tquery(g_SQL, "SELECT * FROM `server`", "LoadServer");
	mysql_tquery(g_SQL, "SELECT * FROM `crate`", "LoadCrate");
	mysql_tquery(g_SQL, "SELECT * FROM `doors`", "LoadDoors");
	mysql_tquery(g_SQL, "SELECT * FROM `familys`", "LoadFamilys");
	mysql_tquery(g_SQL, "SELECT * FROM `houses`", "LoadHouses");
	mysql_tquery(g_SQL, "SELECT * FROM `bisnis`", "LoadBisnis");
	mysql_tquery(g_SQL, "SELECT * FROM `lockers` ORDER BY `id` ASC", "LoadLockers");
	mysql_tquery(g_SQL, "SELECT * FROM `gstations`", "LoadGStations");
	mysql_tquery(g_SQL, "SELECT * FROM `atms`", "LoadATM");
	mysql_tquery(g_SQL, "SELECT * FROM `gates`", "LoadGates");
	mysql_tquery(g_SQL, "SELECT * FROM `trees`", "LoadTrees");
	mysql_tquery(g_SQL, "SELECT * FROM `plants`", "LoadPlants");
	mysql_tquery(g_SQL, "SELECT * FROM `privategarage`", "PvGarageLoad");
	mysql_tquery(g_SQL, "SELECT * FROM `ladang`", "LoadFarm");
	mysql_tquery(g_SQL, "SELECT * FROM `workshop`", "WorkshopLoad");
	mysql_tquery(g_SQL, "SELECT * FROM `fishingarea`", "FishingAreaLoad");
	mysql_tquery(g_SQL, "SELECT * FROM `cd`", "LoadcDealerships");
	mysql_tquery(g_SQL, "SELECT * FROM `rentplayer`", "Rent_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `maps`", "Maps_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `furnstore` ORDER BY `id` ASC", "FurnStore_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `furnobject` ORDER BY `id` ASC", "FurnObject_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `flat`", "Flat_Load");
  	mysql_tquery(g_SQL, "SELECT * FROM `flatroom`", "FlatRoom_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `suiteroom`", "SuiteRoom_Loaded");
	mysql_tquery(g_SQL, "SELECT * FROM `gymobjects`", "GYMObject_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `tags` ORDER BY `tagId` ASC LIMIT "#MAX_DYNAMIC_TAGS";", "Tags_Load", "");
	mysql_tquery(g_SQL, "SELECT * FROM `tollgate`", "TollGate_Load", "");
	mysql_tquery(g_SQL, "SELECT * FROM `actor`", "Actor_Load", "");
	mysql_tquery(g_SQL, "SELECT * FROM `speedcameras`", "Speed_Load", "");
	mysql_tquery(g_SQL, "SELECT * FROM `vehicledata`", "LoadVehicleData");
	mysql_tquery(g_SQL, "SELECT * FROM `bush_forager`", "Bush_Load", "");
	mysql_tquery(g_SQL, "SELECT * FROM `dynarrests`", "LoadDynArrest");
	mysql_tquery(g_SQL, "SELECT * FROM `doorfaction`", "DoorFaction_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `location`", "Location_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `basement`", "Basement_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `ores`", "LoadOres");
    mysql_tquery(g_SQL, "SELECT * FROM `garbage` ORDER BY `garbageID` ASC", "Garbage_Load", "");

	SetGameModeText(TEXT_GAMEMODE);
	SendRconCommand(TEXT_WEBURL);
	SendRconCommand(TEXT_LANGUAGE);
	SendRconCommand("mapname San Andreas");
	ManualVehicleEngineAndLights();
	EnableStuntBonusForAll(0);
	AllowInteriorWeapons(1);
	DisableInteriorEnterExits();
	LimitPlayerMarkerRadius(15.0);
	ShowNameTags(0);
	SetNameTagDrawDistance(8.0);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
	BlockGarages(.text="NO ENTER");
	//SetWorldTime(WorldTime);
	gettime(current_hour, _);
    SetWorldTime(current_hour);

	HBECreate();
	CreateTextDraw();
	CreateServerPoint();
	CreateArmsPoint();
	LoadTazerSAPD();
	CreateMapIcon();
	CreateVehicleFaction();
	MappingServer();
	AddFurnStoreObject();
	MappingFlat();
	TextDrawInitHauling();
	MappingNewbieSchool();
	//Sapd Button
 	// SAPDLobbyBtn[0] = CreateButton(1327.621704, 728.623413, 111.940315, 270.000000);
	// SAPDLobbyBtn[1] = CreateButton(1327.881958, 730.843139, 111.940315, 450.000000);
	// SAPDLobbyDoor[0] = CreateDynamicObject(1569, 1327.769531, 728.931030, 110.300323, 0.000000, 0.000000, 90.000000);

	GreenZoneArea[1] = CreateDynamicRectangle(asgh_Point[0], asgh_Point[1], asgh_Point[2], asgh_Point[3], 0, 0);
	GreenZoneArea[2] = CreateDynamicRectangle(sapd_Point[0], sapd_Point[1], sapd_Point[2], sapd_Point[3], 0, 0);
	GreenZoneArea[3] = CreateDynamicRectangle(cityHall_Point[0], cityHall_Point[1], cityHall_Point[2], cityHall_Point[3], 0, 0);
	GreenZoneArea[4] = CreateDynamicRectangle(sana_Point[0], sana_Point[1], sana_Point[2], sana_Point[3], 0, 0);
	GreenZoneArea[5] = CreateDynamicRectangle(unity_Point[0], unity_Point[1], unity_Point[2], unity_Point[3], 0, 0);
	
	//MechanicArea[0] = CreateDynamicRectangle(1791.42, -2076.94, 13.57, 191.91, 0, 0);
	//MechanicArea[1] = CreateDynamicRectangle(1791.42, -2076.94, 13.57, 191.91, 0, 0);
	//MechanicArea[2] = CreateDynamicRectangle(-274.0, 1207.5, -215.0, 1228.5, 0, 0);
	
	FarmArea[0] = CreateDynamicRectangle(-339.0, -1561.5, -203.0, -1461.5, 0, 0);
	FarmArea[1] = CreateDynamicRectangle(-334.0, -1424.5, -160.0, -1303.5, 0, 0);
	FarmArea[2] = CreateDynamicRectangle(-597.0, -1385.5, -364.0, -1285.5, 0, 0);
	FarmArea[3] = CreateDynamicRectangle(-597.0, -1410.5, -385.0, -1385.5, 0, 0);
	FarmArea[4] = CreateDynamicRectangle(-583.0, -1437.5, -517.0, -1410.5, 0, 0);
	FarmArea[5] = CreateDynamicRectangle(-452.0, -1334.5, -348.0, -1266.5, 0, 0);

	GangZoneID = GangZoneCreate(-3000, -3000, 3000, 3000);

	for (new i; i < sizeof(ColorList); i++) format(color_string, sizeof(color_string), "%s{%06x}%03d %s", color_string, ColorList[i] >>> 8, i, ((i+1) % 16 == 0) ? ("\n") : (""));
    for (new i; i < sizeof(FontNames); i++) format(object_font, sizeof(object_font), "%s%s\n", object_font, FontNames[i]);
	printf("[Object] Number of Dynamic objects loaded: %d", CountDynamicObjects());

	return 1;
}

public OnGameModeExit()
{
   	print("\n--------------------------------------");
	print("./SERVER DIMATIKAN / DIRESTART");
	
	foreach(new gsid : GStation) if(Iter_Contains(GStation, gsid)) GStation_Save(gsid);
	foreach(new pid : Plants) if(Iter_Contains(Plants, pid)) Plant_Save(pid);
	foreach (new i : GYMObjects) GYMObject_Save(i);
	for (new i = 0, j = GetPlayerPoolSize(); i <= j; i++) 
	{
		if (IsPlayerConnected(i))
		{
			UpdatePlayerData(i);	
			RemovePlayerVehicle(i);
		}
	}
	Iter_Clear(GStation);
	Iter_Clear(GYMObjects);
	Iter_Clear(Maps);
	//==============//
	UnloadTazerSAPD();
	mysql_close(g_SQL);
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    #if defined DEBUG_MODE
        printf("[Callback: OnPlayerRequestClass]: Player ID: %d, Class ID: %d", playerid, classid);
    #endif

    if(IsPlayerNPC(playerid))
        return 1;
	if(!pData[playerid][IsLoggedIn])
	{
		SetPlayerHealth(playerid,100.0);
    	SetPlayerPos(playerid, 1761.7881,-1938.6140,13.5815);
		SetPlayerVirtualWorld(playerid, (playerid+1));

		for (new i = 0; i < 3; i++) 
		{
			TextDrawShowForPlayer(playerid, MYSUNSHINE[i]);
		}

		SetTimerEx("SafeLogin", 4000, false, "d", playerid);
    }
    return 1;
}

public OnPlayerRequestSpawn(playerid)
{
    #if defined DEBUG_MODE
        printf("[Callback: OnPlayerRequestSpawn]: Player ID: %d", playerid);
    #endif

    KickEx(playerid);
    return 1;
}

public OnPlayerConnect(playerid)
{
	new PlayerIP[16];
	g_MysqlRaceCheck[playerid]++;
	ResetVariables(playerid);
	CreatePlayerTextDraws(playerid);
	StopAudioStreamForPlayer(playerid);
	GetPlayerName(playerid, charData[playerid][cName], MAX_PLAYER_NAME);
	GetPlayerIp(playerid, PlayerIP, sizeof(PlayerIP));
	pData[playerid][pIP] = PlayerIP;
	PlayerLabel[playerid] = CreateDynamic3DTextLabel((sprintf("%s (%d)", ReturnName2(playerid), playerid)), COLOR_WHITE, 0.0, 0.0, 0.2, 20.0, .attachedplayer = playerid, .testlos = 1);

	if(pData[playerid][IsLoggedIn]==true)return true;
	
	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 500, playerid);
	Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 0.8, playerid);
	pData[playerid][activitybar] = CreatePlayerProgressBar(playerid, 262.000000, 226.000000, 121.500000, 18.000000, -1, 100.000000, 0);
	
	PlayerHBECreate(playerid);
	CreatePlayerInv(playerid);

	pData[playerid][hungrybar] = CreatePlayerProgressBar(playerid, 545.000000, 415.000000, 57.000000, 6.500000, 16711935, 100.0, 0);
    pData[playerid][energybar] = CreatePlayerProgressBar(playerid, 545.000000, 427.000000, 57.000000, 6.500000, 16711935, 100.0, 0);
    pData[playerid][healtbar] = CreatePlayerProgressBar(playerid, 545.000000, 382.000000, 57.000000, 6.500000, -16776961, 100.0, 0);
    pData[playerid][armorbar] = CreatePlayerProgressBar(playerid, 545.000000, 395.000000, 57.000000, 6.500000, -1, 100.0, 0);
    pData[playerid][damagebar] = CreatePlayerProgressBar(playerid, 391.000000, 388.000000, 83.500000, 10.500000, 16711935, 1000.0, 0);
    pData[playerid][fuelbar] = CreatePlayerProgressBar(playerid, 391.000000, 428.000000, 83.500000, 10.500000, 16711935, 1000.0, 0);
	
	RemoveMappingServer(playerid);
	return 1;
}

forward CBugFreezeOver(playerid);
public CBugFreezeOver(playerid)
{
	TogglePlayerControllable(playerid, true);

	pCBugging[playerid] = false;
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(IsValidDynamic3DTextLabel(PlayerLabel[playerid])) 
	DestroyDynamic3DTextLabel(PlayerLabel[playerid]);
	ResetCbug(playerid);
	PlayerHBEHide(playerid);
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	foreach(new ii : Player)
	{
		if(pData[ii][pSpec] == playerid)
		{
			pData[pData[ii][pSpec]][playerSpectated]--;
			PlayerSpectatePlayer(ii, INVALID_PLAYER_ID);
			PlayerSpectateVehicle(ii, INVALID_VEHICLE_ID);

			SetSpawnInfo(ii, 0, pData[ii][pSkin], pData[ii][pPosX], pData[ii][pPosY], pData[ii][pPosZ], pData[ii][pPosA], 0, 0, 0, 0, 0, 0);
			TogglePlayerSpectating(ii, false);
			pData[ii][pSpec] = INVALID_PLAYER_ID;
			PlayerTextDrawHide(ii, SpecTD[ii][1]);
			PlayerTextDrawHide(ii, SpecTD[ii][0]);
		}
		if(IsPlayerInRangeOfPoint(ii, 40.0, x, y, z))
		{
			switch(reason)
			{
				case 0: SendClientMessageEx(ii, COLOR_ARWIN, "SERVER: "RED_E"%s "YELLOW_E"has left the server.(Timeout / Lost Connection / crash)", ReturnName(playerid));
				case 1: SendClientMessageEx(ii, COLOR_ARWIN, "SERVER: "RED_E"%s "YELLOW_E"has left the server.(Disconnected)", ReturnName(playerid));
				case 2: SendClientMessageEx(ii, COLOR_ARWIN, "SERVER: "RED_E"%s "YELLOW_E"has left the server.(kicked / banned)", ReturnName(playerid));
			}
		}
	}
    KillTimer(pData[playerid][LoginTimer]);
	KillTimer(pData[playerid][pFreezeTimer]);
	KillTimer(pData[playerid][pDragTimer]);
	KillTimer(pData[playerid][pFareTimer]);
	KillTimer(pData[playerid][pActivity]);
	KillTimer(pData[playerid][pMechanic]);
	KillTimer(pData[playerid][pProducting]);
	KillTimer(pData[playerid][pCooking]);
	KillTimer(pData[playerid][pArmsDealer]);
	g_MysqlRaceCheck[playerid]++;
	DestroyVehicle(TrailerHauling[playerid]);
	if (GetPVarInt(playerid, "sedangNganter")) {
		if ((pData[playerid][pJob] == 8 || pData[playerid][pJob2] == 8) && pData[playerid][pSmugglerPick]) {
			new Float:pos[3];
			GetPlayerLocationEx(playerid, pos[0], pos[1], pos[2]);
			packetObject[selectedLocation] = CreateDynamicObject(1279, pos[0], pos[1], pos[2]-0.9, 0.0, 0.0, 0.0, 0, 0);
			packetLabel[selectedLocation] = CreateDynamic3DTextLabel("[Packet]\n"WHITE_E"Type "YELLOW_E"/pickpacket"WHITE_E" to pick the packet.", COLOR_ARWIN, pos[0], pos[1], pos[2]+0.5, 7.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1);
			packetPlayerid[selectedLocation] = INVALID_PLAYER_ID;
			pData[playerid][pSmugglerPick] = 0;
			pData[playerid][pSmugglerFind] = 0;
			DisablePlayerRaceCheckpoint(playerid);
			SendCustomMessage(playerid, "SMUGGLER", "You've failed store a packet.");
			DeletePVar(playerid, "sedangSmuggler");
			DeletePVar(playerid, "sedangNganter");
		}
	}
	for(new i; i < 10; i++) // 9 = Total Dialog , Jadi kita mau tau kalau Player Ini Apakah Ambil Dialog dari 3 tersebut apa ga !
	{
		if(DialogSaya[playerid][i] == true) // Cari apakah dia punya salah satu diantara 10 dialog tersebut
		{
			if(IsABusABVeh(GetPlayerVehicleID(playerid))) {
				DialogBus[i]--; // Jadi ga ada yang punya nih dialog
				RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
			}
			if(IsABusCDVeh(GetPlayerVehicleID(playerid))) {
				DialogBusCD[i]--; // Jadi ga ada yang punya nih dialog
				RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
			}
			if(IsASweeperVeh(GetPlayerVehicleID(playerid))) {
				DialogSweeper[i] = false; // Jadi ga ada yang punya nih dialog
				RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
			}
			DialogSaya[playerid][i] = false; // Ubah Jadi Dia ga punya dialog lagi Kalau Udah Disconnect (Bukan dia lagi pemilik)
			DialogHauling[i] = false; // Jadi ga ada yang punya nih dialog
			TextDrawSetString(TDMoneyHauling[1], (DialogHauling[1] == true) ? ("~r~Taken") : ("~g~$300.00"));
			TextDrawSetString(TDMoneyHauling[2], (DialogHauling[2] == true) ? ("~r~Taken") : ("~g~$250.00"));
			TextDrawSetString(TDMoneyHauling[3], (DialogHauling[3] == true) ? ("~r~Taken") : ("~g~$270.00"));
			TextDrawSetString(TDMoneyHauling[4], (DialogHauling[4] == true) ? ("~r~Taken") : ("~g~$399.00"));
			TextDrawSetString(TDMoneyHauling[5], (DialogHauling[5] == true) ? ("~r~Taken") : ("~g~$200.00"));
			TextDrawSetString(TDMoneyHauling[6], (DialogHauling[6] == true) ? ("~r~Taken") : ("~g~$310.00"));
			TextDrawSetString(TDMoneyHauling[7], (DialogHauling[7] == true) ? ("~r~Taken") : ("~g~$333.00"));
			TextDrawSetString(TDMoneyHauling[8], (DialogHauling[8] == true) ? ("~r~Taken") : ("~g~$290.00"));
			TextDrawSetString(TDMoneyHauling[9], (DialogHauling[9] == true) ? ("~r~Taken") : ("~g~$255.00"));
			if(DialogHauling[0] == false) TextDrawBoxColor(TDBoxHauling[0], 9109759);
			if(DialogHauling[1] == false) TextDrawBoxColor(TDBoxHauling[1], 9109759);
			if(DialogHauling[2] == false) TextDrawBoxColor(TDBoxHauling[2], 9109759);
			if(DialogHauling[3] == false) TextDrawBoxColor(TDBoxHauling[3], 9109759);
			if(DialogHauling[4] == false) TextDrawBoxColor(TDBoxHauling[4], 9109759);
			if(DialogHauling[5] == false) TextDrawBoxColor(TDBoxHauling[5], 9109759);
			if(DialogHauling[6] == false) TextDrawBoxColor(TDBoxHauling[6], 9109759);
			if(DialogHauling[7] == false) TextDrawBoxColor(TDBoxHauling[7], 9109759);
			if(DialogHauling[8] == false) TextDrawBoxColor(TDBoxHauling[8], 9109759);
			if(DialogHauling[9] == false) TextDrawBoxColor(TDBoxHauling[9], 9109759);
			foreach(new player : Player) {
				if(GetPVarInt(player, "UseMissions") == 1) {
					TextDrawShowForPlayer(player, TDBoxHauling[0]);
					TextDrawShowForPlayer(player, TDBoxHauling[1]);
					TextDrawShowForPlayer(player, TDBoxHauling[2]);
					TextDrawShowForPlayer(player, TDBoxHauling[3]);
					TextDrawShowForPlayer(player, TDBoxHauling[4]);
					TextDrawShowForPlayer(player, TDBoxHauling[5]);
					TextDrawShowForPlayer(player, TDBoxHauling[6]);
					TextDrawShowForPlayer(player, TDBoxHauling[7]);
					TextDrawShowForPlayer(player, TDBoxHauling[8]);
					TextDrawShowForPlayer(player, TDBoxHauling[9]);
				}
			}
		}
	}
	if(IsAForkliftVeh(GetPlayerVehicleID(playerid)))
	{
		RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
		DisablePlayerCheckpoint(playerid);
	}
    if(IsACourierVeh(GetPlayerVehicleID(playerid)) && CourierJob[playerid])
    {
        RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
    }
    if(IsVehicleTrashmaster(GetPlayerVehicleID(playerid)) && pData[playerid][pTrashmasterJob])
    {
    	new vehicleid = GetPlayerVehicleID(playerid);
    	CoreVehicles[vehicleid][vehTrash] = 0;
        RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
    }
	pData[playerid][pSmugglerPick] = 0;
	pData[playerid][pSmugglerFind] = 0;
	DeletePVar(playerid, "sedangSmuggler");
	DeletePVar(playerid, "sedangNganter");
	if (PlayerInGym[playerid][0]) {
        new id = GetPVarInt(playerid, "holdingGYMEquip"), bizid = pData[playerid][pInBiz];
        if (bizid != -1) {
            ClearAnimations(playerid, 1);
			
            GYMObject[id][objectStatus] = 1;
            GYMObject_Refresh(id);
            DeletePVar(playerid, "holdingGYMEquip");
            PlayerInGym[playerid][0] = 0;
            PlayerInGym[playerid][1] = 0;
        }
    }
	RemovePlayerVehicle(playerid);
	if(pData[playerid][IsLoggedIn] == true)
	{
		UpdatePlayerData(playerid);	
		
		Player_ResetCutting(playerid);
		Player_RemoveLumber(playerid);
		Player_ResetHarvest(playerid);
		pData[playerid][pAsk] = false;
		pData[playerid][pAskQ] = EOS;
		pData[playerid][pAskTime] = 0;
		Ask_Clear(playerid);
		// PlayerLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
		if(IsValidDynamic3DTextLabel(pData[playerid][pAdoTag])) DestroyDynamic3DTextLabel(pData[playerid][pAdoTag]);
		if(IsValidDynamicObject(pData[playerid][pFlare])) DestroyDynamicObject(pData[playerid][pFlare]);

		if(pData[playerid][pMaskOn] == 1)
		{
			pData[playerid][pMaskOn] = 0;
			DestroyDynamic3DTextLabel(MaskLabel[playerid]);
		}

		if (pData[playerid][LoginTimer])
		{
			KillTimer(pData[playerid][LoginTimer]);
			pData[playerid][LoginTimer] = 0;
		}
		DestroyEditPoint(playerid);
		Tags_Reset(playerid);
		for (new id = 0; id != MAX_DAMAGE; id++) if(DamageData[playerid][id][damageExists]) Damage_Save(playerid, id);
		pData[playerid][IsLoggedIn] = false;	
		pData[playerid][pAdoActive] = false;
		ResetVariables(playerid);
		for (new id = 0; id != MAX_ACC; id++) if(AccData[playerid][id][accExists]) MySQL_SavePlayerToys(playerid, id);
		KillTazerTimer(playerid);
		StopAudioStreamForPlayer(playerid);
		
		if(GetPVarType(playerid, "PlacedBB"))
		{
			DestroyDynamicObject(GetPVarInt(playerid, "PlacedBB"));
			DestroyDynamic3DTextLabel(Text3D:GetPVarInt(playerid, "BBLabel"));
			if(GetPVarType(playerid, "BBArea"))
			{
				foreach(new i : Player)
				{
					if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "BBArea")))
					{
						StopAudioStreamForPlayer(i);
						Info(playerid, "The boombox creator has disconnected from the server.");
					}
				}
			}
		}
		foreach(new vehid : PVehicles)
		{
			if(pvData[vehid][cVeh] == GetPlayerVehicleID(playerid))
			{
				GetVehicleDamageStatus(pvData[vehid][cVeh], pvData[vehid][cDamage0], pvData[vehid][cDamage1], pvData[vehid][cDamage2], pvData[vehid][cDamage3]);
				GetVehicleHealth(pvData[vehid][cVeh], pvData[vehid][cHealth]);
				pvData[vehid][cFuel] = GetVehicleFuel(pvData[vehid][cVeh]);
				GetVehiclePos(pvData[vehid][cVeh], pvData[vehid][cPosX], pvData[vehid][cPosY], pvData[vehid][cPosZ]);
				GetVehicleZAngle(pvData[vehid][cVeh],pvData[vehid][cPosA]);
			}
			return 1;
		}
	}
 	return 1;
}

public OnPlayerSpawn(playerid)
{
	StopAudioStreamForPlayer(playerid);
	SetCameraBehindPlayer(playerid);
	if (IsPlayerInEvent(playerid))  {
		eventWaitingSpawn[playerid] = 1;
		eventSpawn(playerid);
	}
	else {
		if(pData[playerid][pInjured]) {
			SetPlayerPos(playerid, pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ]);
			SendClientMessage(playerid, COLOR_RED, "WARNING:"WHITE_E" You was getting injured, please (/call 911 > medics).");
			TogglePlayerControllable(playerid, true);
		}
        foreach(new ii : Player) ShowPlayerNameTagForPlayer(playerid, ii, true);
        SetPVarInt(playerid, "TagNama", 1);
        format(pData[playerid][pUnit], 24, ""GREY_E"OFF");
		TogglePlayerControllable(playerid, 0);
		SetPlayerSpawn(playerid);
		SetPlayerSkillLevel(playerid, WEAPON_SILENCED, 1);
		SetPlayerSkillLevel(playerid, WEAPON_DEAGLE, pData[playerid][pSkillWeapon][2]);
		SetPlayerSkillLevel(playerid, WEAPON_SHOTGUN, pData[playerid][pSkillWeapon][1]);
		SetPlayerSkillLevel(playerid, WEAPON_SAWEDOFF, 1);
		SetPlayerSkillLevel(playerid, WEAPON_SHOTGSPA, 1);
		SetPlayerSkillLevel(playerid, WEAPON_UZI, 1);
		SetPlayerSkillLevel(playerid, WEAPON_MP5, pData[playerid][pSkillWeapon][3]);
		SetPlayerSkillLevel(playerid, WEAPON_AK47, pData[playerid][pSkillWeapon][4]);
		SetPlayerSkillLevel(playerid, WEAPON_M4, 1);
		SetPlayerSkillLevel(playerid, WEAPON_TEC9, 1);
		SetPlayerSkillLevel(playerid, WEAPON_RIFLE, pData[playerid][pSkillWeapon][0]);
		SetPlayerSkillLevel(playerid, WEAPON_SNIPER, 1);
		SetPlayerFightingStyle(playerid, pData[playerid][FightStyle]);
	    if(pData[playerid][pJailTime] > 0)
		{
	       	JailPlayer(playerid);
		} else {
			SetPlayerInterior(playerid, pData[playerid][pInt]);
			SetPlayerVirtualWorld(playerid, pData[playerid][pWorld]);
			SetPlayerPos(playerid, pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ]);
			SetPlayerFacingAngle(playerid, pData[playerid][pPosA]);
		}
	    SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 1);
        SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 1);
        SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 1);
	}

	//TextDrawShowForPlayer(playerid, LogoCostum);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	KillTimer(pData[playerid][pArmsDealer]);
	KillTimer(pData[playerid][LoginTimer]);
	KillTimer(pData[playerid][pFreezeTimer]);
	KillTimer(pData[playerid][pDragTimer]);
	KillTimer(pData[playerid][pFareTimer]);
	KillTimer(pData[playerid][pActivity]);
	KillTimer(pData[playerid][pMechanic]);
	KillTimer(pData[playerid][pProducting]);
	KillTimer(pData[playerid][pCooking]);
	DeletePVar(playerid, "UsingSprunk");
	SetPVarInt(playerid, "GiveUptime", -1);
	pData[playerid][pSpawned] = 0;
	Player_ResetCutting(playerid);
	Player_RemoveLumber(playerid);
	Player_ResetHarvest(playerid);
	HidePlayerProgressBar(playerid, pData[playerid][activitybar]);
	PlayerTextDrawHide(playerid, ActiveTD[playerid]);
	pData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
	pData[playerid][pActivityTime] = 0;
	
	pData[playerid][pMechDuty] = 0;
	pData[playerid][pTaxiDuty] = 0;
	pData[playerid][pMission] = -1;
	
	pData[playerid][pSideJob] = 0;
	if(pData[playerid][pMaskOn] == 1)
	{
		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			ShowPlayerNameTagForPlayer(i, playerid, false);
		}
	}
	DisablePlayerCheckpoint(playerid);
	DisablePlayerRaceCheckpoint(playerid);
	RemovePlayerAttachedObject(playerid, 9);
	SetPlayerArmedWeapon(playerid, 0);
	// foreach(new ii : Player) if(pData[ii][pAdmin] > 0) SendDeathMessageToPlayer(ii, killerid, playerid, reason);
	return 1;
}

TryAutoRoleplay(playerid, text[])
{
	new action[144];
	if(!strcmp(text, "rpcrash", true) || !strcmp(text, "crash", true) || !strcmp(text, "tabrakan", true))
		format(action, sizeof(action), "terlihat mengalami kecelakaan dan mencoba mengendalikan situasi.");
	else if(!strcmp(text, "rprun", true) || !strcmp(text, "kabur", true))
		format(action, sizeof(action), "terlihat berlari menjauh dari lokasi dengan tergesa-gesa.");
	else if(!strcmp(text, "rpcj", true) || !strcmp(text, "fight", true) || !strcmp(text, "berantem", true))
		format(action, sizeof(action), "bersiap melakukan perlawanan dengan gerakan tangan yang agresif.");
	else return 0;

	if(pData[playerid][pMaskOn] == 1) SendNearbyMessage(playerid, 20.0, 0xC2A2DAFF, "* Mask_%d %s", pData[playerid][pMaskID], action);
	else SendNearbyMessage(playerid, 20.0, 0xC2A2DAFF, "* %s %s", ReturnName2(playerid), action);
	return 1;
}

public OnPlayerText(playerid, text[])
{
	if(isnull(text)) return 0;
	
	printf("[CHAT] %s(%d) : %s", ReturnName(playerid), playerid, text);

    if(IsPlayerFlooding(playerid))
    {
        Error(playerid, "Chat flood protection!");
        return 0;
    }

	if(pData[playerid][pSpawned] == 0 && pData[playerid][IsLoggedIn] == false) 
		return 0;
		
	if(pData[playerid][pInjured]) 
	{
		SendClientMessage(playerid, COLOR_RED, "WARNING:"WHITE_E" You was getting injured, please (/call 911 > medics).");
		return 0;
	}

	if(pData[playerid][pTogChat]) text[0] = toupper(text[0]);
	if(pData[playerid][pCall] != INVALID_PLAYER_ID && !IsPlayerInEvent(playerid))
	{
		// Anti-Caps
		if(GetPVarType(playerid, "Caps")) UpperToLower(text);
		new lstr[1024], targetid = pData[playerid][pCall];
		format(lstr, sizeof(lstr), "%s [phone]: %s", ReturnName2(playerid), text);
		ProxDetector(10, playerid, lstr, 0xE6E6E6E6, 0xC8C8C8C8, 0xAAAAAAAA, 0x8C8C8C8C, 0x6E6E6E6E);

		new playername[24], rand = RandomEx(1,3);
		format(playername, sizeof(playername), "%s", GetContactNameByNumber(targetid, pData[playerid][pPhone]));
		if (!strcmp(playername, "Unknown", true)) format(playername, sizeof(playername), "%s", (pData[playerid][pGender] == 1) ? ("Male Caller") : ("Female Caller"));
		else format(playername, sizeof(playername), "%s", GetContactNameByNumber(targetid, pData[playerid][pPhone]));
		
		pData[playerid][pPhoneCredit] -= rand;
		SendClientMessageEx(targetid, COLOR_GREY, "%s [phone]: %s", playername, text);
		return 0;
	}
	if(Mobile[playerid] != INVALID_PLAYER_ID)
	{
		if(Mobile[playerid] == 914)
		{
			new String[211];
			if(!text[0]) return SendClientMessageEx(playerid, COLOR_ARWIN, "Dispatch: Sorry, I don't understand?");
			format(String, sizeof(String), ""RED_E"[911] Incident: ["YELLOW_E" %s "RED_E"]", text);
			SendFactionMessage(3, COLOR_ARWIN, String);
			format(String, sizeof(String), ""RED_E"[911] Reporter: [ "YELLOW_E"%s"RED_E" ] Phone: [ "YELLOW_E"%d"RED_E" ] Location: [ "YELLOW_E"%s "RED_E"]", ReturnName2(playerid), pData[playerid][pPhone], GetPlayerLocation(playerid));
			SendFactionMessage(3, COLOR_ARWIN, String);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
			pData[playerid][pCall] = INVALID_PLAYER_ID;
			Mobile[playerid] = INVALID_PLAYER_ID;
			return 0;
		}
		if(Mobile[playerid] == 913)
		{
			new String[211];
			format(String, sizeof(String), ""RED_E"[911] Incident: ["YELLOW_E" %s "RED_E"]", text);
			SendFactionMessage(1, COLOR_ARWIN, String);
			format(String, sizeof(String), ""RED_E"[911] Reporter: [ "YELLOW_E"%s"RED_E" ] Phone: [ "YELLOW_E"%d"RED_E" ] Location: [ "YELLOW_E"%s "RED_E"]", ReturnName2(playerid), pData[playerid][pPhone], GetPlayerLocation(playerid));
			SendFactionMessage(1, COLOR_ARWIN, String);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
			pData[playerid][pCall] = INVALID_PLAYER_ID;
			Mobile[playerid] = INVALID_PLAYER_ID;
			return 0;
		}
		if(Mobile[playerid] == 12332)
		{
			foreach(new tx : Player)
			{
				if((pData[tx][pJob] == 1 || pData[tx][pJob2] == 1) && pData[tx][pTaxiDuty] == 1)
				{
					SendClientMessageEx(tx, COLOR_BLUE, "DISPATCH: "WHITE_E"Client ["YELLOW_E"(%d) {00FFFF}%s "WHITE_E"] Last Know position: ["YELLOW_E"%s"WHITE_E"]", playerid, ReturnName2(playerid), GetPlayerLocation(playerid));
					SendClientMessageEx(tx, COLOR_ARWIN, "NOTE:  Use '/accepttaxi [playerid]' to respond to the call");
				}
			}
			format(pData[playerid][pServiceText], 128, "%s", text);
			SendClientMessageEx(playerid, COLOR_YELLOW, "Thank you. We will alert all taxi driver on duty.");
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
			pData[playerid][pCall] = INVALID_PLAYER_ID;
			Mobile[playerid] = INVALID_PLAYER_ID;
			pData[playerid][pTaxiCall] = 60;
			return 0;
		}
		if(Mobile[playerid] == 12333)
		{
			foreach(new tx : Player)
			{
				if((pData[tx][pJob] == 2 || pData[tx][pJob2] == 2) && pData[tx][pMechDuty] == 1)
				{
					SendClientMessageEx(tx, COLOR_BLUE, "DISPATCH: "WHITE_E"Client ["YELLOW_E"(%d) {00FFFF}%s "WHITE_E"] Last Know position: ["YELLOW_E"%s"WHITE_E"]", playerid, ReturnName2(playerid), GetPlayerLocation(playerid));
					SendClientMessageEx(tx, COLOR_ARWIN, "NOTE:  Use '/acceptmecha [playerid]' to respond to the call");
				}
			}
			format(pData[playerid][pServiceText], 128, "%s", text);
			SendClientMessageEx(playerid, COLOR_YELLOW, "Thank you. We will alert all mechanic on duty.");	
			pData[playerid][pMechaCall] = 60;
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
			pData[playerid][pCall] = INVALID_PLAYER_ID;
			Mobile[playerid] = INVALID_PLAYER_ID;
			return 0;
		}
		if(Mobile[playerid] == 911)
		{
			if(!text[0]) return SendClientMessageEx(playerid, COLOR_ARWIN, "EMERGENCY: "WHITE_E"Sorry, I don't understand - police or paramedic?");
			else if (strcmp("police", text, true) == 0)
			{
				SendClientMessageEx(playerid, COLOR_ARWIN, "EMERGENCY: "WHITE_E"I am patching you to San Andreas Police Department headquarters, please hold...");
				Mobile[playerid] = 913;
				SendClientMessageEx(playerid, COLOR_ARWIN, "Police HQ: "WHITE_E"Please give me a short description of the crime.");
				return 0;
			}
			else if (strcmp("paramedic", text, true) == 0)
			{
				SendClientMessageEx(playerid, COLOR_ARWIN, "EMERGENCY: "WHITE_E"I am patching you to San Andreas Medical Department headquarters, please hold...");
				Mobile[playerid] = 914;
				SendClientMessageEx(playerid, COLOR_ARWIN, "Dispatch: "WHITE_E"Please give me a short description of the incident.");
				return 0;
			}
			else return SendClientMessageEx(playerid, COLOR_ARWIN, "EMERGENCY: "WHITE_E"Sorry, I don't understand - police or paramedic?");
		}
		if(Mobile[playerid] == 111)
		{
			if(!text[0]) return SendClientMessageEx(playerid, COLOR_ARWIN, "EMERGENCY: "WHITE_E"Sorry, I don't understand - taxi or mechanic?");
			else if (strcmp("taxi", text, true) == 0)
			{
				SendClientMessageEx(playerid, COLOR_ARWIN, "TAXI: "WHITE_E"I am patching you to taxi headquarters, please hold...");
				Mobile[playerid] = 12332;
				SendClientMessageEx(playerid, COLOR_ARWIN, "TAXI: "WHITE_E"Please give me you location.");
				return 0;
			}
			else if (strcmp("mechanic", text, true) == 0)
			{
				SendClientMessageEx(playerid, COLOR_ARWIN, "MECHANIC: "WHITE_E"I am patching you to mechanic headquarters, please hold...");
				Mobile[playerid] = 12333;
				SendClientMessageEx(playerid, COLOR_ARWIN, "MECHANIC: "WHITE_E"Please give me you location.");
				return 0;
			}
			else return SendClientMessageEx(playerid, COLOR_ARWIN, "EMERGENCY: "WHITE_E"Sorry, I don't understand - taxi or mechanic?");
		}
	}
	if(IsPlayerInNewbieSchool(playerid))
	{
		if(strlen(text) > 64)
		{
			if(pData[playerid][pMaskOn] == 1)
			{
				new name[52];
				format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
				SendNearbyMessage(playerid, 20.0, COLOR_RED, "%s:"WHITE_E" (( %.64s ..",name, text);
            	SendNearbyMessage(playerid, 20.0, COLOR_WHITE, ".. %s ))", text[64]);
			}
			else
			{
				SendNearbyMessage(playerid, 20.0, COLOR_RED, "%s:"WHITE_E" (( %.64s ..",ReturnName2(playerid), text);
            	SendNearbyMessage(playerid, 20.0, COLOR_WHITE, ".. %s ))", text[64]);
			}
		}
		else
        {
			if(pData[playerid][pMaskOn] == 1)
			{
				new name[52];
				format(name, sizeof(name), "Mask %d", pData[playerid][pMaskID]);
				SendNearbyMessage(playerid, 20.0, COLOR_RED, "%s:"WHITE_E" (( %s ))", name, text);
			}
			else SendNearbyMessage(playerid, 20.0, COLOR_RED, "%s:"WHITE_E" (( %s ))", ReturnName2(playerid), text);
        }
		return 0;
	}
	if(TryAutoRoleplay(playerid, text)) return 0;
	new String[500];
	if(pData[playerid][pAdminDuty] >= 1 && !IsPlayerInEvent(playerid) && !IsPlayerInNewbieSchool(playerid))
	{
		format(String, sizeof(String), "{FF0000}%s: {FFFFFF}((  %s ))", pData[playerid][pAdminname], text);
		ProxDetector(10, playerid, String, 0xE6E6E6E6, 0xC8C8C8C8, 0xAAAAAAAA, 0x8C8C8C8C, 0x6E6E6E6E);
		return 0;
	}
	if( pData[playerid][pAdminDuty] == 0 && !IsPlayerInEvent(playerid) && !IsPlayerInNewbieSchool(playerid))
	{
		if(pData[playerid][pMaskOn] == 1) format(String, sizeof(String), "Mask_%d says: %s",pData[playerid][pMaskID], text);
		else if(pData[playerid][pTogAccent] == 0) format(String, sizeof(String), "%s says: %s", ReturnName2(playerid), text);
		else if(pData[playerid][pTogAccent] == 1) format(String, sizeof(String), "%s says [%s Accent]: %s", ReturnName2(playerid), pData[playerid][pAccent], text);
		ProxDetector(10, playerid, String, 0xE6E6E6E6, 0xC8C8C8C8, 0xAAAAAAAA, 0x8C8C8C8C, 0x6E6E6E6E);
		return 0;
	}
	return 0;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
	if(pData[playerid][IsLoggedIn] == false) return Error(playerid, "You must be logged in to use command");

    if (result == -1) return SendClientMessageEx(playerid, COLOR_GREY, "ERROR: Unknown command, see '/help'");
	printf("[CMD]: %s(%d) menggunakan CMD '%s' (%s)", ReturnName2(playerid), playerid, cmd, params);
    return 1;
}

public OnPlayerPressButton(playerid, buttonid)
{
	if(buttonid == SAPDLobbyBtn[0] || buttonid == SAPDLobbyBtn[1])
	{
		if(pData[playerid][pFaction] == 1)
		{
			MoveDynamicObject(SAPDLobbyDoor[0], 1327.769531, 727.460327, 110.300323, 3);
			SetTimer("SAPDLobbyDoorClose", 5000, 0);
		}
		else return Error(playerid, "Access denied.");
	}
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
    if (clickedplayerid == playerid) return Error(playerid, "You cannot click yourself.");

    if (pData[playerid][pAdmin] > 0)if (pData[playerid][pSpawned]) {
		if (pData[clickedplayerid][pSpawned]) return DisplayStats(playerid, clickedplayerid);
		else return Error(playerid, "That player isn't logged in!");
	} else return Error(playerid, "You aren't logged in!");
    return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if(pData[playerid][pAdminDuty] > 0)
	{
        new vehicleid = GetPlayerVehicleID(playerid);
        if(vehicleid > 0 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) SetVehiclePos(vehicleid, fX, fY, fZ+3);
        else {
			SetPlayerPos(playerid, fX, fY, fZ+3);
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
        }
	} 
	if(IsPlayerInAnyVehicle(playerid)) foreach(new i : Player) if(GetPlayerState(i) == PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid)) {
		if(pData[i][pTaxiDuty] == 1) {
			SetPlayerRaceCheckpoint(i, 1, fX, fY, fZ, 0, 0, 0, 2.0);
			SendClientMessageEx(i, COLOR_ARWIN, "TAXI: "WHITE_E"Passenger has marked drop off location");
			return 1;
		}
	}
    return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_FIRE) || PRESSED(KEY_HANDBRAKE))
	{
		new weaponid;
		if((weaponid = GetWeapon(playerid)) != 0 && (!PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_ammo])) {
			TogglePlayerControllable(playerid, 0);
			ResetWeaponID(playerid, weaponid);
			TogglePlayerControllable(playerid, 1);
			SetCameraBehindPlayer(playerid);
			SendCustomMessage(playerid, "WEAPON", "Your weapon has been destroyed because it ran out of ammo.");
        }
	}
    if(gPlayerUsingLoopingAnim[playerid])
	{
		if(IsKeyJustDown(KEY_SPRINT,newkeys,oldkeys))
		{
			StopLoopingAnim(playerid);
			ClearAnimations(playerid);
			return 1;
		}
	}
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		// if(PRESSED(KEY_CTRL_BACK))
		// {
		// 	ClearAnimations(playerid);
		// 	StopLoopingAnim(playerid);
		// 	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		// }
		if(!pCBugging[playerid] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			if(PRESSED(KEY_FIRE))
			{
				switch(GetPlayerWeapon(playerid))
				{
					case WEAPON_DEAGLE, WEAPON_SHOTGUN, WEAPON_SNIPER:
					{
						ptsLastFiredWeapon[playerid] = gettime();
					}
				}
			}
			else if(PRESSED(KEY_CROUCH))
			{
				if((gettime() - ptsLastFiredWeapon[playerid]) < 1)
				{
					TogglePlayerControllable(playerid, false);

					pCBugging[playerid] = true;

					GameTextForPlayer(playerid, "~r~!! no c-bug !!", 5000, 6);

					KillTimer(ptmCBugFreezeOver[playerid]);
					ptmCBugFreezeOver[playerid] = SetTimerEx("CBugFreezeOver", 1500, false, "i", playerid);
				}
			}
		}
		// if((NetStats_GetConnectedTime(playerid) - pData[playerid][pBunnyHopTick] >= 1000) && (newkeys & KEY_JUMP) && !(oldkeys & KEY_JUMP) && !IsPlayerInEvent(playerid) && !pData[playerid][pAdminDuty]) {
		// 	CallLocalFunction("OnPlayerJumping", "i", playerid);
		// 	pData[playerid][pBunnyHopTick] = NetStats_GetConnectedTime(playerid);
		// }
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DRINK_SPRUNK && (newkeys & KEY_FIRE))
		{
			pData[playerid][pSprunk]--;
			pData[playerid][pEnergy] += 10;
			SendClientMessageEx(playerid, COLOR_ARWIN,"USE: "WHITE_E"Anda telah berhasil menggunakan sprunk.");
			InfoTD_MSG(playerid, 3000, "Restore +10 Hunger");
			SetTimerEx("CigarStop", 7000, 0, "i", playerid);
			return 1;
		}
		if(newkeys & KEY_FIRE && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY)
		{
			SendClientMessageEx(playerid, COLOR_ARWIN,"USE: "WHITE_E"Anda telah berhasil merokok.");
			SetTimerEx("CigarStop", 10000, 0, "i", playerid);
			return 1;
		}
		if((newkeys & KEY_SECONDARY_ATTACK))
		{
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 656.4168,-1326.0953,13.5521)) // masuk basemen news
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 2486.7585,2374.5234,6.8437);
					SetPlayerFacingAngle(playerid, 271.9420);
					SetPlayerInterior(playerid, 5);
					SetPlayerVirtualWorld(playerid, 0);
				}			
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 2485.8213,2379.3203,7.0685) && GetPlayerInterior(playerid) == 5) // keluar basemen news 
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 662.3588,-1326.5183,13.6027);
					SetPlayerFacingAngle(playerid, 3.4360);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);	
				}    		
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1178.5835,-1308.4675,13.7781)) // masuk basemen RS
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 2486.7585,2374.5234,6.8437);
					SetPlayerFacingAngle(playerid, 271.9420);
					SetPlayerInterior(playerid, 6);
					SetPlayerVirtualWorld(playerid, 0);
				}			
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 2485.8213,2379.3203,7.0685) && GetPlayerInterior(playerid) == 6) // keluar basemen news 
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 1180.2900,-1339.0264,13.5089);
					SetPlayerFacingAngle(playerid, 272.5181);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
				}	
			}  
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1767.5198,-1887.3687,13.5916)) // masuk basemen stasiun
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 2486.7585,2374.5234,6.8437);
					SetPlayerFacingAngle(playerid, 271.9420);
					SetPlayerInterior(playerid, 7);
					SetPlayerVirtualWorld(playerid, 0);
				}
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 2485.8213,2379.3203,7.0685) && GetPlayerInterior(playerid) == 7) // keluar basemen stasiun
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetPlayerPos(playerid, 1769.2347,-1893.7607,13.5916);
					SetPlayerFacingAngle(playerid, 270.3540);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
				}
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1562.73, -1606.25, 13.38)) // masuk basemen sapd
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 2486.7585,2374.5234,6.8437);
					SetPlayerFacingAngle(playerid, 271.9420);
					SetPlayerInterior(playerid, 8);
					SetPlayerVirtualWorld(playerid, 0);
				}
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 2485.8213,2379.3203,7.0685) && GetPlayerInterior(playerid) == 8) // keluar basemen sapd
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetPlayerPos(playerid, 1562.73, -1606.25, 13.38);
					SetPlayerFacingAngle(playerid, 264.89);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
				}
			}  
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1584.49, -1632.83, 13.38)) // masuk garage sapd
			{
				if(pData[playerid][pFaction] == 1)
				{
					if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
					{
						SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
						SetPlayerPos(playerid, 1593.74, -1669.95, 5.87);
						SetPlayerFacingAngle(playerid, 177.29);
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
					}
				}
				else return Error(playerid, "Access denied.");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1601.53, -1668.24, 5.88) && GetPlayerVirtualWorld(playerid) == 0) // keluar garage sapd
			{
				if(pData[playerid][pFaction] == 1)
				{
					if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
					{
						SetPlayerPos(playerid, 1589.91, -1633.35, 13.38);
						SetPlayerFacingAngle(playerid, 358.06);
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
					}
				}
				else return Error(playerid, "Access denied.");
			}
			foreach(new did : Doors) {
				if(IsPlayerInDynamicCP(playerid, dData[did][dCP][0]))
				{
					if(!Door_HasInterior(did)) return Error(playerid, "Interior entrance masih kosong, atau tidak memiliki interior.");
					if(dData[did][dLocked]) return Error(playerid, "This entrance is locked at the moment.");
					if(pData[playerid][pArrest] == 1) return Error(playerid, "You are under arrest!");
					if(dData[did][dFaction] > 0) if(dData[did][dFaction] != pData[playerid][pFaction]) return Error(playerid, "This door only for faction.");
					if(dData[did][dFamily] > 0) if(dData[did][dFamily] != pData[playerid][pFamily]) return Error(playerid, "This door only for family.");
					if(dData[did][dVip] > pData[playerid][pVip]) return Error(playerid, "Your VIP level not enough to enter this door.");
					if(dData[did][dAdmin] > pData[playerid][pAdmin]) return Error(playerid, "Your admin level not enough to enter this door.");
						
					if(strlen(dData[did][dPass]))
					{
						new params[256];
						if(sscanf(params, "s[256]", params)) return Usage(playerid, "/enter [password]");
						if(strcmp(params, dData[did][dPass])) return Error(playerid, "Invalid door password.");
						
						if(dData[did][dCustom]) SetPlayerPositionEx(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
						else SetPlayerPositionEx(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
						pData[playerid][pInDoor] = did;
						SetPlayerInterior(playerid, dData[did][dIntint]);
						SetPlayerVirtualWorld(playerid, dData[did][dIntvw]);
						SetCameraBehindPlayer(playerid);
						SetPlayerWeather(playerid, 0);
					}
					else
					{
						if(dData[did][dCustom]) SetPlayerPositionEx(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
						else SetPlayerPositionEx(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
						pData[playerid][pInDoor] = did;
						SetPlayerInterior(playerid, dData[did][dIntint]);
						SetPlayerVirtualWorld(playerid, dData[did][dIntvw]);
						SetCameraBehindPlayer(playerid);
						SetPlayerWeather(playerid, 0);
					}
				}
				if(IsPlayerInDynamicCP(playerid, dData[did][dCP][1])) {
					if(dData[did][dFaction] > 0) if(dData[did][dFaction] != pData[playerid][pFaction]) return Error(playerid, "This door only for faction.");
					if(pData[playerid][pArrest] == 1) return Error(playerid, "You are under arrest!");

					if(dData[did][dCustom]) SetPlayerPositionEx(playerid, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtposA]);
					else SetPlayerPositionEx(playerid, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtposA]);

					pData[playerid][pInDoor] = -1;
					SetPlayerInterior(playerid, dData[did][dExtint]);
					SetPlayerVirtualWorld(playerid, dData[did][dExtvw]);
					SetCameraBehindPlayer(playerid);
					SetPlayerWeather(playerid, current_weather);
					Streamer_UpdateEx(playerid, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ]);
					pData[playerid][pInt] = 0;
					pData[playerid][pWorld] = 0;
				}
			}
			foreach(new flatid : Flat) {
				if(IsPlayerInDynamicCP(playerid, FlatData[flatid][flatCPExt])) {
					if (FlatData[flatid][flatIntPos][0] == 0.0 && FlatData[flatid][flatIntPos][1] == 0.0 && FlatData[flatid][flatIntPos][2] == 0.0)
						return Error(playerid, "Flat is not initialized");
					
					SetPlayerPos(playerid, FlatData[flatid][flatIntPos][0],FlatData[flatid][flatIntPos][1],FlatData[flatid][flatIntPos][2]);
					SetPlayerVirtualWorld(playerid, FlatData[flatid][flatIntWorld]);
					SetPlayerInterior(playerid, FlatData[flatid][flatIntInterior]);
					SetPlayerWeather(playerid, 1);
					pData[playerid][pInFlat] = flatid;
				}
				if(IsPlayerInDynamicCP(playerid, FlatData[flatid][flatCPInt])) {
					SetPlayerPos(playerid, FlatData[flatid][flatPos][0],FlatData[flatid][flatPos][1],FlatData[flatid][flatPos][2]);
					SetPlayerWeather(playerid, current_weather);
					SetPlayerVirtualWorld(playerid, FlatData[flatid][flatWorld]);
					SetPlayerInterior(playerid, FlatData[flatid][flatInterior]);
					pData[playerid][pInFlat] = -1;
				}
			}
			//Bisnis
			foreach(new bid : Bisnis) {
				if(IsPlayerInDynamicCP(playerid, bData[bid][bCP][0]) && IsPlayerInRangeOfPoint(playerid, 3.0, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ])) {
					// Pastikan player tidak sedang di Plant CP (tanaman Farmer)
					new bool:in_plant = false;
					foreach(new pid : Plants) if(IsPlayerInDynamicCP(playerid, PlantData[pid][PlantCP])) { in_plant = true; break; }
					if(in_plant) continue;
					if(bData[bid][bIntposX] == 0.0 && bData[bid][bIntposY] == 0.0 && bData[bid][bIntposZ] == 0.0) return Error(playerid, "Interior bisnis masih kosong, atau tidak memiliki interior.");
					if(bData[bid][bLocked]) return GameTextForPlayer(playerid, "~w~Biz ~r~Locked!", 1000, 5);
					if(bData[bid][bSegel] == 1) return GameTextForPlayer(playerid, "~w~Biz ~r~Sealed", 1000, 5);
					pData[playerid][pInBiz] = bid;
					SetPlayerPositionEx(playerid, bData[bid][bIntposX], bData[bid][bIntposY], bData[bid][bIntposZ], bData[bid][bIntposA]);

					SetPlayerInterior(playerid, bData[bid][bInt]);
					SetPlayerVirtualWorld(playerid, bid);
					SetCameraBehindPlayer(playerid);
					SetPlayerWeather(playerid, 0);
					PlayStream(playerid, bData[bid][bStream], bData[bid][bIntposX], bData[bid][bIntposY], bData[bid][bIntposZ], 30.0, 1);
					return 1;
				}
				if(IsPlayerInDynamicCP(playerid, bData[bid][bCP][1]) && GetPlayerVirtualWorld(playerid) == bid) {
					SetPlayerPositionEx(playerid, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ], bData[bid][bExtposA]);

					SetPlayerInterior(playerid, bData[bid][bExtInt]);
					SetPlayerVirtualWorld(playerid, bData[bid][bExtVw]);
					SetCameraBehindPlayer(playerid);
					SetPlayerWeather(playerid, current_weather);
					StopStream(playerid);
					pData[playerid][pInt] = 0;
					pData[playerid][pWorld] = 0;
					return 1;
				}
			}
			//Houses
			foreach(new hid : Houses) {
				if(IsPlayerInDynamicCP(playerid, hData[hid][hCP][0])) {
					if(hData[hid][hIntposX] == 0.0 && hData[hid][hIntposY] == 0.0 && hData[hid][hIntposZ] == 0.0) return Error(playerid, "Interior house masih kosong, atau tidak memiliki interior.");
					if(hData[hid][hLocked]) return Error(playerid, "This house is locked!");
					pData[playerid][pInHouse] = hid;
					SetPlayerPositionEx(playerid, hData[hid][hIntposX], hData[hid][hIntposY], hData[hid][hIntposZ], hData[hid][hIntposA]);

					SetPlayerInterior(playerid, hData[hid][hInt]);
					SetPlayerVirtualWorld(playerid, hid);
					SetCameraBehindPlayer(playerid);
					SetPlayerWeather(playerid, 0);
					if(!hData[hid][house_Lights]) TextDrawShowForPlayer(playerid, HouseLight);
				}
				if(IsPlayerInDynamicCP(playerid, hData[hid][hCP][1])) {
					pData[playerid][pInHouse] = -1;
					SetPlayerPositionEx(playerid, hData[hid][hExtposX], hData[hid][hExtposY], hData[hid][hExtposZ], hData[hid][hExtposA]);
					
					SetPlayerInterior(playerid, hData[hid][hExtInt]);
					SetPlayerVirtualWorld(playerid, hData[hid][hExtVw]);
					pData[playerid][pInt] = 0;
					pData[playerid][pWorld] = 0;
					SetCameraBehindPlayer(playerid);
					SetPlayerWeather(playerid, current_weather);
					TextDrawHideForPlayer(playerid, HouseLight);
				}
			}
			//Family
			foreach(new fid : FAMILYS) {
				if(IsPlayerInRangeOfPoint(playerid, 2.8, fData[fid][fExtposX], fData[fid][fExtposY], fData[fid][fExtposZ])) {
					if(fData[fid][fIntposX] == 0.0 && fData[fid][fIntposY] == 0.0 && fData[fid][fIntposZ] == 0.0) return Error(playerid, "Interior masih kosong, atau tidak memiliki interior.");
					if(pData[playerid][pFaction] == 0) if(pData[playerid][pFamily] == -1) return Error(playerid, "You dont have registered for this door!");
					SetPlayerPositionEx(playerid, fData[fid][fIntposX], fData[fid][fIntposY], fData[fid][fIntposZ], fData[fid][fIntposA]);

					SetPlayerInterior(playerid, fData[fid][fInt]);
					SetPlayerVirtualWorld(playerid, fid);
					SetCameraBehindPlayer(playerid);
					SetPlayerWeather(playerid, 0);
				}
				if(IsPlayerInRangeOfPoint(playerid, 2.8, fData[fid][fIntposX], fData[fid][fIntposY], fData[fid][fIntposZ]))
				{
					SetPlayerPositionEx(playerid, fData[fid][fExtposX], fData[fid][fExtposY], fData[fid][fExtposZ], fData[fid][fExtposA]);

					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
					SetCameraBehindPlayer(playerid);
					SetPlayerWeather(playerid, current_weather);
					pData[playerid][pInt] = 0;
					pData[playerid][pWorld] = 0;
				}
			}
		}
		//SAPD Taser/Tazer
		if(newkeys & KEY_FIRE && TaserData[playerid][TaserEnabled] && GetPlayerWeapon(playerid) == 23 && !IsPlayerInAnyVehicle(playerid) && TaserData[playerid][TaserCharged])
		{
			TaserData[playerid][TaserCharged] = true;
			new Float:X, Float:Y, Float:Z, Float:health;
			foreach(new i : Player)
			{
				if(IsPlayerStreamedIn(i, playerid))
				{
					GetPlayerPos(i, X, Y, Z);
					if(IsPlayerAimingAt(playerid,X,Y,Z,1) && GetPlayerState(i) == PLAYER_STATE_ONFOOT && (GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)))
					{
						if(!IsPlayerConnected(i)) continue;
						if(playerid == i) continue;
						if(TaserData[i][TaserCountdown] != 0) continue;
						//ClearAnimations(i, 1);
						TogglePlayerControllable(i, false);
						PlayerPlaySound(i, 6003, 0,0,0);
						PlayerPlaySound(playerid, 6003, 0,0,0);
						GetPlayerHealth(i, health);
						TaserData[i][TaserCountdown] = TASER_BASETIME + floatround((100 - health) / 12);
						SendClientMessageEx(i, COLOR_ARWIN,"TASER: "WHITE_E"You got tased for %d secounds!", TaserData[i][TaserCountdown]);
						TaserData[i][GetupTimer] = SetTimerEx("TaserGetUp", 1000, true, "i", i);
						return 1;
					}
				}
			}
		}
	}
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER  || GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(GetPVarInt(playerid, "UseMissions") == 1)
		{
			for (new i; i < 10; i++) {
                if(i < 6) { TextDrawHideForPlayer(playerid, TDHauling[i]); }
				TextDrawHideForPlayer(playerid, TDDistanceHauling[i]);
				TextDrawHideForPlayer(playerid, TDNameHauling[i]);
				TextDrawHideForPlayer(playerid, TDMoneyHauling[i]);
				TextDrawHideForPlayer(playerid, TDBoxHauling[i]);
				CancelSelectTextDraw(playerid);
			}
			DeletePVar(playerid, "UseMissions");
		}
	}
	//Vehicle
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER  && IsPlayerInAnyVehicle(playerid)) 
	{
		if((newkeys & KEY_YES ))
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			new Float:POS[3];
			if(JB_IsBicycle(vehicleid))
			{
				GetPlayerPos(playerid, POS[0], POS[1], POS[2]);
				SetPlayerPos(playerid, POS[0], POS[1], POS[2] + 2.0);
				//RemovePlayerFromVehicle(playerid);
			}
			else
			{
				if(!GetEngineStatus(GetPlayerVehicleID(playerid)) && !GetPVarInt(playerid, "EngineOn")) {
					SendClientMessageEx(playerid, COLOR_WHITE, "ENGINE: Anda mencoba untuk menghidupkan Mesin.");
					SetTimerEx("EngineStatus", 3000, false, "id", playerid, vehicleid);
					// SetPVarInt(playerid, "EngineOn", 1);
				}
			}
		}
		if((newkeys & KEY_LOOK_BEHIND ))
		{
			if(IsPlayerInAnyVehicle(playerid)) Vehicle_Lock(GetPlayerVehicleID(playerid), playerid);
		}
		if(IsKeyJustDown(KEY_NO, newkeys, oldkeys))
		{
			if(IsPlayerInAnyVehicle(playerid)) return callcmd::toglight(playerid, "");
		}
		if((newkeys & KEY_YES ))
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			if(pData[playerid][pTogHandbrake] == 1) {
	            // if(JB_IsBicycle(vehicleid) && IsABike(vehicleid)) return 1;
				if(!pvData[vehicleid][cHandbrake]) {
					pvData[vehicleid][cHandbrake] = 1;
					SendClientMessage(playerid, -1, "VEHICLE: {FFFFFF}Handbrakes {00FF00}engaged");
				}
	        }
			if(GetEngineStatus(GetPlayerVehicleID(playerid))) {
				SendClientMessageEx(playerid, COLOR_WHITE, "ENGINE: Anda telah mematikan Mesin");
				SwitchVehicleEngine(GetPlayerVehicleID(playerid), false);
				SwitchVehicleLight(GetPlayerVehicleID(playerid), false);
			}
		}
		if(IsKeyJustDown(KEY_CROUCH, newkeys, oldkeys))
		{	
			new id = -1;
			if ((id = TollGate_Nearest(playerid)) != -1) TollGate_Operate(playerid, id);
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1534.3633,-1456.2278,12.9216)) // masuk basemen news
			{
				MoveDynamicObject(gatestealingjobs, 1534.755371, -1451.642211, 8.465853, 3);
				SetTimer("StealingCloseDoor", 5000, 0);
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1534.8777,-1446.6173,13.3828)) // masuk basemen news
			{
				MoveDynamicObject(gatestealingjobs, 1534.755371, -1451.642211, 8.465853, 3);
				SetTimer("StealingCloseDoor", 5000, 0);
			}
			// Dynamic Gates
			foreach(new idx : Gates)
			{
				if(gData[idx][gModel] && IsPlayerInRangeOfPoint(playerid, 10, gData[idx][gCX], gData[idx][gCY], gData[idx][gCZ]))
				{
					if(gData[idx][gFaction] > 0)
					{
						if(gData[idx][gFaction] != pData[playerid][pFaction])
							return Error(playerid, "This gate only for faction.");
					}
					if(gData[idx][gFamily] > -1)
					{
						if(gData[idx][gFamily] != pData[playerid][pFamily])
							return Error(playerid, "This gate only for family.");
					}
					
					if(gData[idx][gVip] > pData[playerid][pVip])
						return Error(playerid, "Your VIP level not enough to enter this gate.");
					
					if(gData[idx][gAdmin] > pData[playerid][pAdmin])
						return Error(playerid, "Your admin level not enough to enter this gate.");
					
					if(!gData[idx][gStatus])
					{
						gData[idx][gStatus] = 1;
						MoveDynamicObject(gData[idx][gObjID], gData[idx][gOX], gData[idx][gOY], gData[idx][gOZ], gData[idx][gSpeed]);
						SetDynamicObjectRot(gData[idx][gObjID], gData[idx][gORX], gData[idx][gORY], gData[idx][gORZ]);
						SetTimerEx("DynamicGateClose", 4000, 0, "d", idx);
					}
					else
					{
						gData[idx][gStatus] = 0;
						MoveDynamicObject(gData[idx][gObjID], gData[idx][gCX], gData[idx][gCY], gData[idx][gCZ], gData[idx][gSpeed]);
						SetDynamicObjectRot(gData[idx][gObjID], gData[idx][gCRX], gData[idx][gCRY], gData[idx][gCRZ]);
					}
					return 1;
				}
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 656.4168,-1326.0953,13.5521)) // masuk basemen news
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid); //2486.7585,2374.5234,6.8437,271.9420
					SetVehiclePosEx(GetPlayerVehicleID(playerid), 2486.7585,2374.5234,6.8437, 271.9420, 0, 5);
					SetPlayerInterior(playerid, 5);
					SetPlayerVirtualWorld(playerid, 0);                    
				}
				else
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 2486.7585,2374.5234,6.8437);
					SetPlayerFacingAngle(playerid, 271.9420);
					SetPlayerInterior(playerid, 5);
					SetPlayerVirtualWorld(playerid, 0);
				}			
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 2485.8213,2379.3203,7.0685) && GetPlayerInterior(playerid) == 5) // keluar basemen news 
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetVehiclePosEx(GetPlayerVehicleID(playerid), 662.3588,-1326.5183,13.6027, 3.4360, 0, 0);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);   
				}
				else
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 662.3588,-1326.5183,13.6027);
					SetPlayerFacingAngle(playerid, 3.4360);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);	
				}    		
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1178.5835,-1308.4675,13.7781)) // masuk basemen RS
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetVehiclePosEx(GetPlayerVehicleID(playerid), 2486.7585,2374.5234,6.8437, 271.9420, 0, 6);
					SetPlayerInterior(playerid, 6);
					SetPlayerVirtualWorld(playerid, 0);                   
				}
				else
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 2486.7585,2374.5234,6.8437);
					SetPlayerFacingAngle(playerid, 271.9420);
					SetPlayerInterior(playerid, 6);
					SetPlayerVirtualWorld(playerid, 0);
				}			
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 2485.8213,2379.3203,7.0685) && GetPlayerInterior(playerid) == 6) // keluar basemen news 
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetVehiclePosEx(GetPlayerVehicleID(playerid), 1180.2900,-1339.0264,13.5089, 272.5181, 0, 0);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);   
				}
				else
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 1180.2900,-1339.0264,13.5089);
					SetPlayerFacingAngle(playerid, 272.5181);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
				}	
			}  
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1767.5198,-1887.3687,13.5916)) // masuk basemen stasiun
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetVehiclePosEx(GetPlayerVehicleID(playerid), 2486.7585, 2374.5234, 6.8437, 271.9420, 0, 7);
					SetPlayerInterior(playerid, 7);
					SetPlayerVirtualWorld(playerid, 0);                   
				}
				else
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 2486.7585,2374.5234,6.8437);
					SetPlayerFacingAngle(playerid, 271.9420);
					SetPlayerInterior(playerid, 7);
					SetPlayerVirtualWorld(playerid, 0);
				}
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 2485.8213,2379.3203,7.0685) && GetPlayerInterior(playerid) == 7) // keluar basemen stasiun
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				{
					SetVehiclePosEx(GetPlayerVehicleID(playerid), 1769.2347,-1893.7607,13.5916, 270.3540, 0, 0);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
				}
				else
				{
					SetPlayerPos(playerid, 1769.2347,-1893.7607,13.5916);
					SetPlayerFacingAngle(playerid, 270.3540);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
				}
			} 
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1562.73, -1606.25, 13.38)) // masuk basemen sapd
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetVehiclePosEx(GetPlayerVehicleID(playerid), 2486.7585, 2374.5234, 6.8437, 271.9420, 0, 8);
					SetPlayerInterior(playerid, 8);
					SetPlayerVirtualWorld(playerid, 0);                   
				}
				else
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 2486.7585,2374.5234,6.8437);
					SetPlayerFacingAngle(playerid, 271.9420);
					SetPlayerInterior(playerid, 8);
					SetPlayerVirtualWorld(playerid, 0);
				}
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 2485.8213,2379.3203,7.0685) && GetPlayerInterior(playerid) == 8) // keluar basemen sapd
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
				{
					SetVehiclePosEx(GetPlayerVehicleID(playerid), 1562.73, -1606.25, 13.38, 264.89, 0, 0);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
				}
				else
				{
					SetPlayerPos(playerid, 1562.73, -1606.25, 13.38);
					SetPlayerFacingAngle(playerid, 270.3540);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
				}
			} 
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1584.49, -1631.83, 13.38)) // masuk garage sapd
			{
				if(pData[playerid][pFaction] == 1)
				{
					if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
					{
						SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
						SetVehiclePosEx(GetPlayerVehicleID(playerid), 1593.74, -1669.95, 5.87, 177.29, 0, 0);
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);             
					}
					else
					{
						SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
						SetPlayerPos(playerid, 1593.74, -1669.95, 5.87);
						SetPlayerFacingAngle(playerid, 177.29);
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
					}
				}
				else return Error(playerid, "Access denied.");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1601.53, -1670.24, 5.88) && GetPlayerVirtualWorld(playerid) == 0) // keluar garage sapd
			{
				if(pData[playerid][pFaction] == 1)
				{
					if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
					{
						SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
						SetVehiclePosEx(GetPlayerVehicleID(playerid), 1589.91, -1633.35, 13.38, 358.06, 0, 0);
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
					}
					else
					{
						SetPlayerPos(playerid, 1589.91, -1633.35, 13.38);
						SetPlayerFacingAngle(playerid, 358.06);
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
					}
				}
				else return Error(playerid, "Access denied.");
			} 
		}
		if(PRESSED( KEY_FIRE ))
		{
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 656.4168,-1326.0953,13.5521)) // masuk basemen news
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 2486.7585,2374.5234,6.8437);
					SetPlayerFacingAngle(playerid, 271.9420);
					SetPlayerInterior(playerid, 5);
					SetPlayerVirtualWorld(playerid, 0);
				}			
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 2485.8213,2379.3203,7.0685) && GetPlayerInterior(playerid) == 5) // keluar basemen news 
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 662.3588,-1326.5183,13.6027);
					SetPlayerFacingAngle(playerid, 3.4360);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);	
				}    		
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1178.5835,-1308.4675,13.7781)) // masuk basemen RS
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 2486.7585,2374.5234,6.8437);
					SetPlayerFacingAngle(playerid, 271.9420);
					SetPlayerInterior(playerid, 6);
					SetPlayerVirtualWorld(playerid, 0);
				}			
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 2485.8213,2379.3203,7.0685) && GetPlayerInterior(playerid) == 6) // keluar basemen news 
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 1180.2900,-1339.0264,13.5089);
					SetPlayerFacingAngle(playerid, 272.5181);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
				}	
			}  
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1767.5198,-1887.3687,13.5916)) // masuk basemen stasiun
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 2486.7585,2374.5234,6.8437);
					SetPlayerFacingAngle(playerid, 271.9420);
					SetPlayerInterior(playerid, 7);
					SetPlayerVirtualWorld(playerid, 0);
				}
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 2485.8213,2379.3203,7.0685) && GetPlayerInterior(playerid) == 7) // keluar basemen stasiun
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetPlayerPos(playerid, 1769.2347,-1893.7607,13.5916);
					SetPlayerFacingAngle(playerid, 270.3540);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
				}
			}  
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1562.73, -1606.25, 13.38)) // masuk basemen sapd
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
					SetPlayerPos(playerid, 2486.7585,2374.5234,6.8437);
					SetPlayerFacingAngle(playerid, 271.9420);
					SetPlayerInterior(playerid, 8);
					SetPlayerVirtualWorld(playerid, 0);
				}
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 2485.8213,2379.3203,7.0685) && GetPlayerInterior(playerid) == 8) // keluar basemen sapd
			{
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				{
					SetPlayerPos(playerid, 1562.73, -1606.25, 13.38);
					SetPlayerFacingAngle(playerid, 264.89);
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
				}
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1584.49, -1631.83, 13.38)) // masuk garage sapd
			{
				if(pData[playerid][pFaction] == 1)
				{
					if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
					{
						SetTimerEx("EnterExitTimer", 8000, false, "i", playerid);
						SetPlayerPos(playerid, 1593.74, -1669.95, 5.87);
						SetPlayerFacingAngle(playerid, 177.29);
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 1);
					}
				}
				else return Error(playerid, "Access denied.");
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, 1601.53, -1670.24, 5.88) && GetPlayerVirtualWorld(playerid) == 1) // keluar garage sapd
			{
				if(pData[playerid][pFaction] == 1)
				{
					if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
					{
						SetPlayerPos(playerid, 1589.91, -1633.35, 13.38);
						SetPlayerFacingAngle(playerid, 358.06);
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 0);
					}
				}
				else return Error(playerid, "Access denied.");
			}
			foreach(new did : Doors)
			{
				if(IsPlayerInDynamicCP(playerid, dData[did][dPickupext]))
				{
					if(dData[did][dGarage] == 1)
					{
						if(!Door_HasInterior(did))
							return Error(playerid, "Interior entrance masih kosong, atau tidak memiliki interior.");

						if(dData[did][dLocked])
							return Error(playerid, "This entrance is locked at the moment.");
							
						if(dData[did][dFaction] > 0)
						{
							if(dData[did][dFaction] != pData[playerid][pFaction])
								return Error(playerid, "This door only for faction.");
						}
						if(dData[did][dFamily] > 0)
						{
							if(dData[did][dFamily] != pData[playerid][pFamily])
								return Error(playerid, "This door only for family.");
						}
						
						if(dData[did][dVip] > pData[playerid][pVip])
							return Error(playerid, "Your VIP level not enough to enter this door.");
						
						if(dData[did][dAdmin] > pData[playerid][pAdmin])
							return Error(playerid, "Your admin level not enough to enter this door.");
							
						if(strlen(dData[did][dPass]))
						{
							new params[256];
							if(sscanf(params, "s[256]", params)) return Usage(playerid, "/enter [password]");
							if(strcmp(params, dData[did][dPass])) return Error(playerid, "Invalid door password.");
							
							if(dData[did][dCustom])
							{
								SetPlayerPositionEx(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
							}
							else
							{
								SetPlayerPositionEx(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]); 
							}
							pData[playerid][pInDoor] = did;
							SetPlayerInterior(playerid, dData[did][dIntint]);
							SetPlayerVirtualWorld(playerid, dData[did][dIntvw]);
							SetCameraBehindPlayer(playerid);
							SetPlayerWeather(playerid, 0);
						}
						else
						{
							if(dData[did][dCustom])
							{
								SetPlayerPositionEx(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
							}
							else
							{
								SetPlayerPositionEx(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
							}
							pData[playerid][pInDoor] = did;
							SetCameraBehindPlayer(playerid);
							SetPlayerWeather(playerid, 0);
							SetPlayerInterior(playerid, dData[did][dIntint]);
							SetPlayerVirtualWorld(playerid, dData[did][dIntvw]);
						}
					}
				}
				if(IsPlayerInDynamicCP(playerid, dData[did][dPickupint]))
				{
					if(dData[did][dGarage] == 1)
					{
						if(dData[did][dFaction] > 0)
						{
							if(dData[did][dFaction] != pData[playerid][pFaction])
								return Error(playerid, "This door only for faction.");
						}
					
						if(dData[did][dCustom])
						{
							SetVehiclePosEx(GetPlayerVehicleID(playerid), dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtposA], dData[did][dExtvw], dData[did][dExtint]); 
						}
						else
						{
							SetVehiclePosEx(GetPlayerVehicleID(playerid), dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtposA], dData[did][dExtvw], dData[did][dExtint]); 
						}
						pData[playerid][pInDoor] = -1;
						SetCameraBehindPlayer(playerid);
						SetPlayerWeather(playerid, current_weather);
						SetPlayerInterior(playerid, dData[did][dExtint]);
						SetPlayerVirtualWorld(playerid, dData[did][dExtvw]);
						Streamer_UpdateEx(playerid, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ]);
					}
				}
			}
		}
	}
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	//Spec Player
	new vehicleid = GetPlayerVehicleID(playerid);
	if(newstate == PLAYER_STATE_WASTED) {
		if(!IsPlayerInEvent(playerid)) {
			pData[playerid][pInt] = GetPlayerInterior(playerid);
			pData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
			GetPlayerPos(playerid, pData[playerid][pPosX], pData[playerid][pPosY], pData[playerid][pPosZ]);
			GetPlayerFacingAngle(playerid, pData[playerid][pPosA]);
			AutoDropPlayerGuns(playerid);
			// ApplyAnimation(playerid, "PED", "BIKE_fall_off", 4.0, 0, 0, 0, 1, 0, 1);
			ApplyAnimation(playerid, "PED", "KO_skid_front", 4.0, 0, 0, 0, 1, 0, 1);
			TextDrawShowForPlayer(playerid, injuredtextdraw);
			SetPlayerHealthEx(playerid, 100);
			pData[playerid][pInjured] = 1;
			if (GetPVarInt(playerid, "sedangNganter")) {
				if ((pData[playerid][pJob] == 8 || pData[playerid][pJob2] == 8) && pData[playerid][pSmugglerPick]) {
					new Float:pos[3];
					GetPlayerLocationEx(playerid, pos[0], pos[1], pos[2]);
					packetObject[selectedLocation] = CreateDynamicObject(1279, pos[0], pos[1], pos[2]-0.9, 0.0, 0.0, 0.0, 0, 0);
					packetLabel[selectedLocation] = CreateDynamic3DTextLabel("[Packet]\n"WHITE_E"Type "YELLOW_E"/pickpacket"WHITE_E" to pick the packet.", COLOR_ARWIN, pos[0], pos[1], pos[2]+0.5, 7.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1);
					packetPlayerid[selectedLocation] = INVALID_PLAYER_ID;
					pData[playerid][pSmugglerPick] = 0;
					pData[playerid][pSmugglerFind] = 0;
					DisablePlayerRaceCheckpoint(playerid);
					SendCustomMessage(playerid, "SMUGGLER", "You've failed store a packet.");
					DeletePVar(playerid, "sedangSmuggler");
					DeletePVar(playerid, "sedangNganter");
				}
			}
		}
    }
	if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
    {
		TextDrawHideForPlayer(playerid, TDEditor_TD[0]);
		TextDrawHideForPlayer(playerid, DPvehfare[playerid]);
		StopAudioStreamForPlayer(playerid);
		pData[playerid][pRadioVehicleOn] = 0;
		
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CARRY || GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) return RemovePlayerFromVehicle(playerid);

		VehicleHBEHide(playerid);

		foreach(new fishing : FishingArea) if(IsValidDynamicMapIcon(mapiconfishing[playerid][fishing])) DestroyDynamicMapIcon(mapiconfishing[playerid][fishing]);
		for(new i = 0; i < 2; i++) 
		{
			TextDrawHideForPlayer(playerid, PlayerCrateTD);
			PlayerTextDrawHide(playerid, PlayerCrate[playerid][i]);
		}
		if(pData[playerid][pTaxiDuty] == 1)
		{
			pData[playerid][pTaxiDuty] = 0;
			SetPlayerColor(playerid, COLOR_WHITE);
		    if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
        		UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s {ffffff}(%d)", ReturnName2(playerid), playerid)));
			SendCustomMessage(playerid, "JOB", ""YELLOW_E"You are no longer on taxi duty!");
		}
		if(pData[playerid][pFare] == 1)
		{
			KillTimer(pData[playerid][pFareTimer]);
			SendClientMessageEx(playerid, COLOR_ARWIN,"JOB: "WHITE_E"Anda telah menonaktifkan taxi fare pada total: {00FF00}$%s", FormatMoney(pData[playerid][pTotalFare]));
			pData[playerid][pFare] = 0;
			pData[playerid][pTotalFare] = 0;
		}
		if(IsAForkliftVeh(GetPlayerVehicleID(playerid)))
		{
			DisablePlayerRaceCheckpoint(playerid);
			RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
			DisablePlayerCheckpoint(playerid);
			return 1;
		}
		if(CourierJob[playerid])
		{
			TimerCourier[playerid] = 61;
			SendCustomMessage(playerid, "COURIER", "Silahkan ke trunk untuk mengambil paket lalu antarkan kerumah!");
			new Float:x1, Float:y1, Float:z1;
			GetVehiclePartPos(pData[playerid][pLastCar], VEHICLE_PART_TRUNK, x1, y1, z1);
			SetPlayerRaceCheckpoint(playerid, 1, x1, y1, z1, x1, y1, z1, 1);
			CourierCrate[playerid] = 1;
			SetVehicleParamsForPlayer(pData[playerid][pLastCar],playerid,1,0);
			return 1;
		}
        foreach (new ii : Player) if(pData[ii][pSpec] == playerid) {
            PlayerSpectatePlayer(ii, playerid);
        }
	}
	if(newstate == PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_PASSENGER)
	{
		foreach(new pv : PVehicles)
		{
			if(vehicleid == pvData[pv][cVeh])
			{
				if(pvData[pv][cComponent] > 0)
				{
					TextDrawShowForPlayer(playerid, PlayerCrateTD);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
					new String2[212];
					format(String2,sizeof(String2),"Component~n~%d units", pvData[pv][cComponent]);
					PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
				}
				if(pvData[pv][cCrateComponent] > 0)
				{
					TextDrawShowForPlayer(playerid, PlayerCrateTD);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
					new String2[212];
					format(String2,sizeof(String2),"Crate (Component)~n~%d units", pvData[pv][cCrateComponent]);
					PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
				}
				if(pvData[pv][cCrateFish] > 0)
				{
					TextDrawShowForPlayer(playerid, PlayerCrateTD);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
					new String2[212];
					format(String2,sizeof(String2),"Crate (Fish)~n~%d units", pvData[pv][cCrateFish]);
					PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
				}
				if(pvData[pv][cCrateFish2] > 0)
				{
					TextDrawShowForPlayer(playerid, PlayerCrateTD);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
					new String2[212];
					format(String2,sizeof(String2),"Crate (Fish)~n~%d units", pvData[pv][cCrateFish2]);
					PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
				}
				if(pvData[pv][cCratePlant] > 0)
				{
					TextDrawShowForPlayer(playerid, PlayerCrateTD);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
					new String2[212];
					format(String2,sizeof(String2),"Crate (Plant)~n~%d units", pvData[pv][cCratePlant]);
					PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
				}
				if(pvData[pv][cCrateLumber] > 0)
				{
					TextDrawShowForPlayer(playerid, PlayerCrateTD);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
					new String2[212];
					format(String2,sizeof(String2),"Crate (Lumber)~n~%d units", pvData[pv][cCrateLumber]);
					PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
				}
				if(pvData[pv][cWheat] > 0)
				{
					TextDrawShowForPlayer(playerid, PlayerCrateTD);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
					new String2[212];
					format(String2,sizeof(String2),"plant (wheat)~n~%d units", pvData[pv][cWheat]);
					PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
				}
				if(pvData[pv][cOnion] > 0)
				{
					TextDrawShowForPlayer(playerid, PlayerCrateTD);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
					new String2[212];
					format(String2,sizeof(String2),"plant (Onion)~n~%d units", pvData[pv][cOnion]);
					PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
				}
				if(pvData[pv][cCarrot] > 0)
				{
					TextDrawShowForPlayer(playerid, PlayerCrateTD);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
					new String2[212];
					format(String2,sizeof(String2),"plant (Carrot)~n~%d units", pvData[pv][cCarrot]);
					PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
				}
				if(pvData[pv][cPotato] > 0)
				{
					TextDrawShowForPlayer(playerid, PlayerCrateTD);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
					new String2[212];
					format(String2,sizeof(String2),"plant (Potato)~n~%d units", pvData[pv][cPotato]);
					PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
				}
				if(pvData[pv][cCorn] > 0)
				{
					TextDrawShowForPlayer(playerid, PlayerCrateTD);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
					new String2[212];
					format(String2,sizeof(String2),"plant (Corn)~n~%d units", pvData[pv][cCorn]);
					PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
				}
				if(pvData[pv][cLumber] > 0)
				{
					TextDrawShowForPlayer(playerid, PlayerCrateTD);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][0]);
					PlayerTextDrawShow(playerid, PlayerCrate[playerid][1]);
					new String2[212];
					format(String2,sizeof(String2),"Timber~n~%d units", pvData[pv][cLumber]);
					PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
				}
			}
		}
		if(IsABoat(GetPlayerVehicleID(playerid)))
		{
			foreach(new fishing : FishingArea) {
				switch(FishingData[fishing][Type]) {
					case 0: mapiconfishing[playerid][fishing] = CreateDynamicMapIcon(FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2], 0, COLOR_RED, 0, 0, playerid, 1000, MAPICON_LOCAL);
					case 1: mapiconfishing[playerid][fishing] = CreateDynamicMapIcon(FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2], 0, COLOR_YELLOW, 0, 0, playerid, 1000, MAPICON_LOCAL);
					case 2: mapiconfishing[playerid][fishing] = CreateDynamicMapIcon(FishingData[fishing][Pos][0], FishingData[fishing][Pos][1], FishingData[fishing][Pos][2], 0, COLOR_GREEN, 0, 0, playerid, 1000, MAPICON_LOCAL);
				}
			}
		}
		if(!IsEngineVehicle(vehicleid)) SwitchVehicleEngine(vehicleid, true);
		if(IsEngineVehicle(vehicleid)) {
			if(!IsABoat(GetPlayerVehicleID(playerid)) && pData[playerid][pDriveLic] <= 0) SendClientMessageEx(playerid, COLOR_RED,"WARNING: "YELLOW_E"You do not have a Driver License or your Driver License is expired.");
			else if(IsABoat(GetPlayerVehicleID(playerid)) && pData[playerid][pBoatLic] <= 0) SendClientMessageEx(playerid, COLOR_RED,"WARNING: "YELLOW_E"You do not have a Boat License or your Driver License is expired.");
		}
		if(IsEngineVehicle(vehicleid) && !GetEngineStatus(vehicleid)) SendClientMessageEx(playerid, COLOR_GREY,"ENGINEINFO: Mesin masih mati, tekan tombol "RED_E"'Y'"GREY_E" atau command /engine "GREY_E"untuk menghidupkannya.");

		if(pData[playerid][pHBEMode] == 1)
		{
			if(!JB_IsBicycle(vehicleid))
			{
				new color1, color2;
				GetVehicleColor(vehicleid, color1, color2);
				for(new i; i < 10; i++)
				{
					TextDrawShowForPlayer(playerid, SAStyleVehicleTD[i]);
				}
				PlayerTextDrawShow(playerid, SAVNameTD[playerid]);
				PlayerTextDrawShow(playerid, SAVHealthTD[playerid]);
				PlayerTextDrawShow(playerid, SAVFuelTD[playerid]);
				PlayerTextDrawShow(playerid, SAPVSpeedTD[playerid]);
			}
			else
			{
				new color1, color2;
				GetVehicleColor(vehicleid, color1, color2);

				for(new i; i < 10; i++)
				{
					TextDrawShowForPlayer(playerid, SAStyleVehicleTD[i]);
				}
				PlayerTextDrawShow(playerid, SAVNameTD[playerid]);
				PlayerTextDrawShow(playerid, SAVHealthTD[playerid]);
				PlayerTextDrawShow(playerid, SAVFuelTD[playerid]);
				PlayerTextDrawShow(playerid, SAPVSpeedTD[playerid]);
			}
		}
		if(pData[playerid][pHBEMode] == 2)
		{
			if(!JB_IsBicycle(vehicleid))
			{
				PlayerTextDrawShow(playerid, JGVHP[playerid]);
				PlayerTextDrawShow(playerid, JGVFUEL[playerid]);
				PlayerTextDrawShow(playerid, JGVSPEED[playerid]);
				TextDrawShowForPlayer(playerid, simpletd[4]);
				TextDrawShowForPlayer(playerid, simpletd[5]);
				TextDrawShowForPlayer(playerid, simpletd[6]);
				TextDrawShowForPlayer(playerid, simpletd[7]);
			}
			else
			{
				PlayerTextDrawHide(playerid, JGVHP[playerid]);
				PlayerTextDrawHide(playerid, JGVFUEL[playerid]);
				PlayerTextDrawShow(playerid, JGVSPEED[playerid]);
				TextDrawShowForPlayer(playerid, simpletd[4]);
				TextDrawShowForPlayer(playerid, simpletd[5]);
				TextDrawShowForPlayer(playerid, simpletd[6]);
				TextDrawShowForPlayer(playerid, simpletd[7]);
			}
		}
		if(pData[playerid][pHBEMode] == 3)
		{
			if(!JB_IsBicycle(vehicleid))
			{
				for(new i; i < 5; i++)
				{
					TextDrawShowForPlayer(playerid, SimpleVehicleTD[i]);
				}
				PlayerTextDrawShow(playerid, VSpeedTD[playerid]);
				PlayerTextDrawShow(playerid, VFuelTD[playerid]);
				PlayerTextDrawShow(playerid, VHealthTD[playerid]);
				PlayerTextDrawShow(playerid, VNameTD[playerid]);
			}
			else
			{
				for(new i; i < 5; i++)
				{
					TextDrawShowForPlayer(playerid, SimpleVehicleTD[i]);
				}
				PlayerTextDrawShow(playerid, VSpeedTD[playerid]);
				PlayerTextDrawShow(playerid, VFuelTD[playerid]);
				PlayerTextDrawShow(playerid, VHealthTD[playerid]);
				PlayerTextDrawShow(playerid, VNameTD[playerid]);
			}
		}
		if(IsACourierVeh(GetPlayerVehicleID(playerid)) && !CourierJob[playerid]) 
		{
			Dialog_Show(playerid, CourierSidejob, DIALOG_STYLE_MSGBOX, "{ffffff}Sidejob: Courier", "Are you ready to start working sidejob as a Courier?", "Start", "Cancel");
			TogglePlayerControllable(playerid, 0);
		}
		if(IsAVehicleDealerVeh(vehicleid))
		{
			new string[212];
			format(string, sizeof(string),"Would you like to buy this {00FFFF}%s?\n\n"WHITE_E"This vehicle costs {00FF00}$%s.", GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[GetCarDealershipId(vehicleid)][cdVehicleCost][GetCarDealershipVehicleId(vehicleid)]));
			ShowPlayerDialog(playerid,DIALOG_CDBUY,DIALOG_STYLE_MSGBOX,"Buying Vehicle:",string,"Buy","Cancel");
		}
		foreach (new ii : Player) if(pData[ii][pSpec] == playerid)  PlayerSpectateVehicle(ii, GetPlayerVehicleID(playerid));
	}
	if(newstate != PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_PASSENGER)
    {
		foreach(new i : Player) if(GetPlayerState(i) == PLAYER_STATE_DRIVER && GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid)) if(pData[i][pTaxiDuty] == 1) {
			SendClientMessageEx(playerid, COLOR_ARWIN, "TAXI: "WHITE_E"Please Mark your destination on maps");
		}
	}
	return 1;
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{
    #if defined DEBUG_MODE
        printf("[Callback: OnPlayerEnterDynamicArea]: Player ID: %d, Area ID: %d", playerid, areaid);
    #endif
    
    // Boombox - play audio for players entering the area
    foreach(new i : Player)
    {
        if(GetPVarType(i, "BBArea") && GetPVarInt(i, "BBArea") == areaid)
        {
            if(GetPVarType(i, "BBStation"))
            {
                new station[128];
                GetPVarString(i, "BBStation", station, sizeof(station));
                if(!isnull(station))
                {
                    if(GetPVarType(playerid, "pAudioStream")) StopAudioStreamForPlayer(playerid);
                    else SetPVarInt(playerid, "pAudioStream", 1);
                    PlayAudioStreamForPlayer(playerid, station, GetPVarFloat(i, "BBX"), GetPVarFloat(i, "BBY"), GetPVarFloat(i, "BBZ"), 30.0, 1);
                }
            }
            break;
        }
    }
	for (new i = 0; i < MAX_GREENZONE; i ++) if (areaid == GreenZoneArea[i]) {
        if (i == 1 || i == 2 || i == 3 || i == 12 || i == 13) {
            GangZoneShowForPlayer(playerid, GangZoneID, 0x0000FF66);
            GangZoneFlashForPlayer(playerid, GangZoneID, 0x0000FF66);
			// SendClientMessage(playerid, COLOR_GREY, "[!] YOU ARE IN BLUEZONE");
        } else {
			// SendClientMessage(playerid, COLOR_GREY, "[!] YOU ARE IN GREENZONE");
            GangZoneShowForPlayer(playerid, GangZoneID, 0x00FF0066);
            GangZoneFlashForPlayer(playerid, GangZoneID, 0x00FF0066);
        }
    }

    return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	for (new i = 0; i < MAX_GREENZONE; i ++) if (areaid == GreenZoneArea[i]) {
        GangZoneHideForPlayer(playerid, GangZoneID);
        GangZoneStopFlashForPlayer(playerid, GangZoneID);
    }
	/*if(areaid == MechanicArea[0] || areaid == MechanicArea[1] || areaid == MechanicArea[2])
	{
		if(pData[playerid][pMechDuty] == 1) {
			pData[playerid][pMechDuty] = 0;
			SetPlayerColor(playerid, COLOR_WHITE);
		    if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
        		UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s {ffffff}(%d)", ReturnName2(playerid), playerid)));
			SendClientMessageEx(playerid, COLOR_ARWIN, "JOB: "WHITE_E"You are now off duty mechanic!");
		}
	}*/
	return 1;
}

public OnPlayerPickUpDynamicPickup(playerid, pickupid) {
	return 1;
}

public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
	#if defined DEBUG_MODE
	    printf("[debug] OnPlayerEnterDynamicCP(PID : %d CID : %d)", playerid, checkpointid);
	#endif
	for(new id = 0; id < 10; id++) if(checkpointid == GaragePickup[id]) GameTextForPlayer(playerid, "~w~PRESS ~r~ENTER~w~ OR~n~~r~H~n~~w~TO ENTER/EXIT", 3000, 4);
	//foreach(new i : DoorBasement) if(checkpointid == Basement[i][dbCP][0] || checkpointid == Basement[i][dbCP][1]) GameTextForPlayer(playerid, "~w~PRESS ~r~ENTER~w~ OR~n~~r~H~n~~w~TO ENTER/EXIT", 3000, 4);
	foreach(new did : Doors) if(checkpointid == dData[did][dPickupext]) GameTextForPlayer(playerid, "~w~PRESS ~r~ENTER~w~ OR ~r~F~n~~w~TO ENTER/EXIT", 3000, 4);
	foreach(new atm : ATMS) if(checkpointid == AtmData[atm][atmpickup]) GameTextForPlayer(playerid, "~p~ATM MACHINE~n~~w~USE '~y~/ATM~w~' TO USE ATM", 3000, 4);
	foreach(new bid : Bisnis) {
		if(checkpointid == bData[bid][bCP][0] && IsPlayerInRangeOfPoint(playerid, 3.0, bData[bid][bExtposX], bData[bid][bExtposY], bData[bid][bExtposZ])) {
			// Jangan trigger hint bisnis jika player sedang di Plant CP (tanaman Farmer)
			new bool:in_plant_cp = false;
			foreach(new pid : Plants) if(IsPlayerInDynamicCP(playerid, PlantData[pid][PlantCP])) { in_plant_cp = true; break; }
			if(!in_plant_cp) GameTextForPlayer(playerid, "~w~PRESS ~r~ENTER~w~ OR ~r~F~n~~w~TO ENTER/EXIT", 3000, 4);
		}
		else if(checkpointid == bData[bid][bCP][1] && GetPlayerVirtualWorld(playerid) == bid) {
			GameTextForPlayer(playerid, "~w~PRESS ~r~ENTER~w~ OR ~r~F~n~~w~TO ENTER/EXIT", 3000, 4);
		}
	}
	foreach(new flatid : Flat) if(checkpointid == FlatData[flatid][flatCPInt]) if(checkpointid == FlatData[flatid][flatCPExt]) GameTextForPlayer(playerid, "~w~PRESS ~r~ENTER~w~ OR ~r~F~n~~w~TO ENTER/EXIT", 3000, 4);
	foreach(new houseid : Houses)
	{
		if(checkpointid == hData[houseid][hCP])
		{
			GameTextForPlayer(playerid, "~w~PRESS ~r~ENTER~w~ OR ~r~F~n~~w~TO ENTER/EXIT", 3000, 4);
			if(CourierJob[playerid] == true && CourierCrate[playerid] == 2) {
				for(new id = 0; id < 11; id++){
					if(CourierID[playerid][id] == houseid) {
						RemovePlayerAttachedObject(playerid, 9);
						CourierStatus[playerid][id] = true;
						CourierID[playerid][id] = -1;
						RemovePlayerMapIcon(playerid, 50+id);
						ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
						CourierCount[playerid]++;
						SendClientMessageEx(playerid, COLOR_ARWIN, "COURIER: {ffffff}Delivered {3BBD44}%d {ffffff}out of {ffff00}10", CourierCount[playerid]);
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
						if(CourierCount[playerid] == 10)
						{
							SendClientMessageEx(playerid, COLOR_ARWIN, "COURIER: {3BBD44}Delivered all crates, {ffffff}Please return the delivery vehicle back to the warehouse!");
							SendClientMessageEx(playerid, COLOR_ARWIN, "COURIER: {ffffff}You've delivered 10 packages, please return the delivery vehicle now!");
							SetPlayerRaceCheckpoint(playerid, 1, 1778.1998,-1693.6936,13.4569, 0.0, 0.0, 0.0, 5.0);
							for(new i; i < 11; i++) RemovePlayerMapIcon(playerid, 50+id);
						}
					}
				}
			}
		}
	}
	return 0;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	if(pData[playerid][pSideJob] == 401)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(GetVehicleModel(vehicleid) == 530)
		{
			if(pData[playerid][pSideJob] == 401)
			{
				KillTimer(pData[playerid][pActivity]);
				pData[playerid][pActivityTime] = 0;
				HidePlayerProgressBar(playerid, pData[playerid][activitybar]);
				PlayerTextDrawHide(playerid, ActiveTD[playerid]);
			}
		}
	}
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	if(CourierJob[playerid] && CourierCrate[playerid] == 1 && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
		CourierCrate[playerid] = 2;
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_CARRY);
		SetPlayerAttachedObject(playerid, 9, 1220, 1, 0.002953, 0.469660, -0.009797, 269.851104, 34.443557, 0.000000, 0.804894, 0.800000, 0.822361 );
		DisablePlayerRaceCheckpoint(playerid);
	}
	if(CourierJob[playerid] && CourierCount[playerid] == 10 && IsACourierVeh(GetPlayerVehicleID(playerid)) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
		for(new i = 0; i < 2; i++) 
		{
			TextDrawHideForPlayer(playerid, PlayerCrateTD);
			PlayerTextDrawHide(playerid, PlayerCrate[playerid][i]);
		}
		AddPlayerSalary(playerid, "San Andreas Express", "Delivered 10 packages", 25000);	
        SendClientMessageEx(playerid, COLOR_ARWIN, "COURIER: {ffffff}Courier sidejob completed, {3BBD44}$250.00 {ffffff}has been issued for your next paycheck");
        SendClientMessageEx(playerid, COLOR_ARWIN, "SALARY: {ffffff}Your salary statement has been updated, please check command {ffff00}'/mysalary'");
        TimerCourier[playerid] = 0;
        CourierJob[playerid] = false;
        CourierCount[playerid] = 0;
        RemovePlayerFromVehicle(playerid);
        RespawnSidejobVehicle(GetPlayerVehicleID(playerid));
		DelayPlayer[playerid][DelayCourier] = 3600;
		DisablePlayerRaceCheckpoint(playerid);
    }
	if(InRace[playerid] && RaceIndex[playerid] != -1) {
		RaceIndex[playerid]++;
		if(RaceIndex[playerid] < 9) SetPlayerRaceCheckpoint(playerid, 0, RacePos[RaceWith[playerid]][RaceIndex[playerid]][0], RacePos[RaceWith[playerid]][RaceIndex[playerid]][1], RacePos[RaceWith[playerid]][RaceIndex[playerid]][2], RacePos[RaceWith[playerid]][RaceIndex[playerid]+1][0], RacePos[RaceWith[playerid]][RaceIndex[playerid]+1][1], RacePos[RaceWith[playerid]][RaceIndex[playerid]+1][2], 5.0);
		else
		{
			for(new i = 0; i < MAX_ROUTE; i++) {
				RacePos[playerid][i][0] = 0;
				RacePos[playerid][i][1] = 0;
				RacePos[playerid][i][2] = 0;
			}
			InRace[playerid] = false;
			RaceIndex[playerid] = -1;
			RaceWith[playerid] = INVALID_PLAYER_ID;
			DisablePlayerRaceCheckpoint(playerid);	
			GameTextForPlayer(playerid, "Balapan Finish!", 3000, 5);	
		}
		return 1;
	}
	if(pData[playerid][pTrackCar] == 1)
	{
		new S3MP4K[212];
	    format(S3MP4K, sizeof(S3MP4K), "HINT: {FFFFFF}Anda telah berhasil menemukan kendaraan anda.");
		SendClientMessageEx(playerid, COLOR_ARWIN, S3MP4K);			
		pData[playerid][pTrackCar] = 0;
		DisablePlayerRaceCheckpoint(playerid);
	}
	if(pData[playerid][pTrackHouse] == 1)
	{
		new S3MP4K[212];
	    format(S3MP4K, sizeof(S3MP4K), "HINT: {FFFFFF}Anda telah berhasil menemukan rumah anda.");
		SendClientMessageEx(playerid, COLOR_ARWIN, S3MP4K);		
		pData[playerid][pTrackHouse] = 0;
		DisablePlayerRaceCheckpoint(playerid);
	}
	if(pData[playerid][pTrackBisnis] == 1)
	{
		new S3MP4K[212];
	    format(S3MP4K, sizeof(S3MP4K), "HINT: {FFFFFF}Anda telah berhasil menemukan bisnis anda.");
		SendClientMessageEx(playerid, COLOR_ARWIN, S3MP4K);		
		pData[playerid][pTrackBisnis] = 0;
		DisablePlayerRaceCheckpoint(playerid);
	}
	if(pData[playerid][pMission] > -1)
	{
		DisablePlayerRaceCheckpoint(playerid);
		SendClientMessageEx(playerid, COLOR_ARWIN,"TRUCKER: "WHITE_E"/buy , /gps(My Mission) , /storeproduct.");
	}
	if(pData[playerid][pHauling] > -1)
	{
		DisablePlayerRaceCheckpoint(playerid);
		SendClientMessageEx(playerid, COLOR_ARWIN,"TRUCKER: "WHITE_E"/buy , /gps(My Hauling) , /storegas.");
	}
	//DisablePlayerRaceCheckpoint(playerid);
	return 1;
}

public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z)
{
	if((!pData[playerid][pAdminDuty] || !eventJoin[playerid]) && GetWeapon(playerid) == weaponid)
	{
		if(--PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_ammo] <= 0) {
			ResetWeaponID(playerid, weaponid);
			SendCustomMessage(playerid, "WEAPON", "Your weapon has been destroyed because it ran out of ammo.");
		}
	}
	new string[144];
	foreach(new slot : DynamicObjects)
	{
	    if(DynamicObject[slot] == objectid)
	    { 
			if(SelectObjectType[playerid] == OBJECT_SELECT_EDITOR)
	    	{
	    		if((ObjectEditor[slot] != INVALID_PLAYER_ID) && (GetPVarInt(ObjectEditor[slot],"EditingObject") == slot))
		        {
		            new playername[MAX_PLAYER_NAME];
		            GetPlayerName(ObjectEditor[slot],playername,sizeof(playername));
				    format(string,sizeof(string),"ERROR: "RED_E"%s "GREY_E"is currently editing this object!",playername);
					return SendClientMessageEx(playerid,COLOR_ARWIN,string);
		        }
		        format(string,sizeof(string),"OBJECT: "WHITE_E"Selected object with "YELLOW_E"id %d",slot);
				ObjectEditor[slot] = playerid;
		        SetPVarInt(playerid,"EditingObject",slot);
		    	EditDynamicObject(playerid,objectid);
		    	SendClientMessageEx(playerid,COLOR_ARWIN,string);
	    	}
			else if(SelectObjectType[playerid] == OBJECT_SELECT_PAINT)
	    	{
	    		new index,model,txdname[32],texture[32],color;
		        GetPVarString(playerid,"PaintParam",string,sizeof(string));
		        unformat(string,"p<|>dds[32]s[32]d",index,model,txdname,texture,color);
		        SetDynamicObjectMaterial(DynamicObject[slot],index,model,txdname,texture,color);
				DynamicObjectMaterial[slot][index] = MATERIAL_TYPE_TEXTURE;
		        break;
	    	}
	    	else if(SelectObjectType[playerid] == OBJECT_SELECT_CLEAN)
	    	{
	    		new model,Float:cPos[3],Float:cRot[3];
				model = Streamer_GetIntData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_MODEL_ID);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_X,cPos[0]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Y,cPos[1]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Z,cPos[2]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_X,cRot[0]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_Y,cRot[1]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_Z,cRot[2]);
                DestroyDynamicObject(DynamicObject[slot]);
				Looping(index,MAX_OBJECT_MATERIAL_SLOT)
				{
					DynamicObjectMaterial[slot][index] = MATERIAL_TYPE_NONE;
				}
				DynamicObject[slot] = CreateDynamicObject(model,cPos[0],cPos[1],cPos[2],cRot[0],cRot[1],cRot[2]);
				Streamer_Update(playerid);
				break;
	    	}
	        break;
	    }
	}
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if((!pData[playerid][pAdminDuty] || !eventJoin[playerid]) && GetWeapon(playerid) == weaponid)
	{
		if(--PlayerGuns[playerid][g_aWeaponSlots[weaponid]][weapon_ammo] <= 0) {
			ResetWeaponID(playerid, weaponid);
			SendCustomMessage(playerid, "WEAPON", "Your weapon has been destroyed because it ran out of ammo.");
		}
	}
	for(new id = 0; id < 15; id++) if(hitid == slottrain[playerid][id]) {
		CountTraining[playerid] += 2;
		TrainingRandom(playerid);
	}
	return 1;
}

forward LabelNormal(playerid);
public LabelNormal(playerid)
{
	if(pData[playerid][pOnDuty] >= 1) SetFactionColor(playerid);
    else if(pData[playerid][pAdminDuty] == 1)
    {
		if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
			UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_RED, (sprintf("%s (%d)", pData[playerid][pAdminname], playerid)));
	}
	else if(pData[playerid][pMaskOn] == 1)
	{
	    if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
	        UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("Mask_#%d", pData[playerid][pMaskID])));
	}
	else if(pData[playerid][pMechDuty] == 1)
	{
	    if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
	        UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_GREEN, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
	}
	else if(pData[playerid][pTaxiDuty] == 1)
	{
	    if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
	        UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_YELLOW, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
	} else {
    	if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
        	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
    }
    return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	#if defined DEBUG_MODE
	    printf("[debug] OnPlayerTakeDamage(PID %d : TID : %d Amount : %.2f WID : %d BodyPart : %d)", playerid, issuerid, amount, weaponid, bodypart);
	#endif

	if(weaponid == WEAPON_CHAINSAW)
	{
		SetPlayerHealth(playerid, GetHealth(playerid));
		SetPlayerArmour(playerid, GetArmour(playerid));
		return 0;
	}

    if(pData[playerid][pAdminDuty])
        return 0;

	Update_PlayerMask(playerid);

    new Float:datahp, Float:dataam;
    GetPlayerHealth(playerid, datahp);
    GetPlayerArmour(playerid, dataam);
    if(pData[playerid][pOnDuty] == 1)
    {
		if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
	       	UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_RED, (sprintf("H: %.1f A: %.1f\n%s (%d)", datahp, dataam, ReturnName2(playerid), playerid)));
	}
    else if(pData[playerid][pAdminDuty] == 1)
    {
		if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
			UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_RED, (sprintf("H: %.1f A: %.1f\n%s (%d)", datahp, dataam, pData[playerid][pAdminname], playerid)));
	}
	else if(pData[playerid][pMaskOn] == 1)
	{
	    if(IsValidDynamic3DTextLabel(MaskLabel[playerid]))
	        UpdateDynamic3DTextLabelText(MaskLabel[playerid], COLOR_RED, (sprintf("H: %.1f A: %.1f\nMask_#%d", datahp, dataam, pData[playerid][pMaskID])));
	}
	else if(pData[playerid][pMechDuty] == 1)
	{
	    if(IsValidDynamic3DTextLabel(MaskLabel[playerid]))
	        UpdateDynamic3DTextLabelText(MaskLabel[playerid], COLOR_RED, (sprintf("H: %.1f A: %.1f\n%s (%d)", datahp, dataam, ReturnName2(playerid), playerid)));
	}
	else if(pData[playerid][pTaxiDuty] == 1)
	{
	    if(IsValidDynamic3DTextLabel(MaskLabel[playerid]))
	        UpdateDynamic3DTextLabelText(MaskLabel[playerid], COLOR_RED, (sprintf("H: %.1f A: %.1f\n%s (%d)", datahp, dataam, ReturnName2(playerid), playerid)));
	} else {
		if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
			UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_RED, (sprintf("H: %.1f A: %.1f\n%s {ffffff}(%d)", datahp, dataam, ReturnName2(playerid), playerid)));
	}

    //Mengatur label ke semula dalam 0.6 detik
    SetTimerEx("LabelNormal", 600, false, "d", playerid);

	new 
		Float:armour = GetArmour(playerid), 
		Float:health = GetHealth(playerid);
	amount = amount/2.5;
	if(GetWeapon(issuerid) && PlayerGuns[issuerid][g_aWeaponSlots[weaponid]][weapon_typesurplus] == 1) {
		amount = amount*2.0;
	}
	if(GetWeapon(issuerid) && PlayerGuns[issuerid][g_aWeaponSlots[weaponid]][weapon_typesurplus] == 2) {
		amount = amount*2.5;
	}
	// if(pData[playerid][pAdminDuty] > 0) return SetHealth(playerid, health);
	if(pData[playerid][pInjured] > 0) return SetHealth(playerid, health);
	if (!IsPlayerInEvent(playerid)) 
    {
		if (IsNotFirearmsWeapon(weaponid)) 
        {
            if (ReturnArmour2(playerid)) SetPlayerArmour(playerid, ReturnArmour2(playerid));
            if (ReturnHealth2(playerid)) SetPlayerHealth(playerid, (ReturnHealth2(playerid)-amount));
        }
		if(weaponid >= 0  && weaponid <= 8 && armour >= 0)
		{
			SetHealth(playerid, health-amount);
			AddDamage(playerid, bodypart, weaponid);
		}
		
		if(issuerid == INVALID_PLAYER_ID)
		{
			// Environmental damage with complex wound types
			switch(weaponid)
			{
 			case 54: // Fall damage / jatuh dari ketinggian (SA-MP weaponid 54 = Splat)
 			{
 				new Float:fall_amt = amount;
 				if(fall_amt > 60.0) fall_amt = 60.0; // cap
 				
 				SetHealth(playerid, health - fall_amt);
 				AddDamage(playerid, BODY_PART_TORSO, 54);
 				
 				// Additional heavy damage to legs
 				if(fall_amt > 30.0)
 				{
 					AddDamage(playerid, BODY_PART_LEFT_LEG, 54);
 					AddDamage(playerid, BODY_PART_RIGHT_LEG, 54);
 				}
 			}
				case 49: // Vehicle collision / ditabrak kendaraan
				{
					new Float:crash_amt = amount;
					if(crash_amt > 70.0) crash_amt = 70.0; // cap
					
					SetHealth(playerid, health - crash_amt);
					AddDamage(playerid, BODY_PART_TORSO, 49);
					
					// Random limb damage from vehicle impact
					new random_limb = random(4);
					switch(random_limb)
					{
						case 0: AddDamage(playerid, BODY_PART_RIGHT_ARM, 49);
						case 1: AddDamage(playerid, BODY_PART_LEFT_ARM, 49);
						case 2: AddDamage(playerid, BODY_PART_RIGHT_LEG, 49);
						case 3: AddDamage(playerid, BODY_PART_LEFT_LEG, 49);
					}
				}
				case 50: // Helicopter blade
				{
					new Float:blade_amt = amount;
					if(blade_amt > 80.0) blade_amt = 80.0; // cap
					
					SetHealth(playerid, health - blade_amt);
					AddDamage(playerid, BODY_PART_TORSO, 50);
					
					// Usually hits arms/head
					if(random(2) == 0) AddDamage(playerid, BODY_PART_RIGHT_ARM, 50);
					else AddDamage(playerid, BODY_PART_HEAD, 50);
				}
				case 51: // Explosion
				{
					new Float:explode_amt = amount;
					if(explode_amt > 80.0) explode_amt = 80.0; // cap
					
					SetHealth(playerid, health - explode_amt);
					AddDamage(playerid, BODY_PART_TORSO, 51);
					
					// Explosion affects multiple body parts
					AddDamage(playerid, BODY_PART_GROIN, 51);
					if(random(2) == 0) AddDamage(playerid, BODY_PART_RIGHT_ARM, 51);
					if(random(2) == 0) AddDamage(playerid, BODY_PART_LEFT_LEG, 51);
				}
				case 52: // Drowning / tenggelam
				{
					new Float:drown_amt = amount;
					if(drown_amt > 30.0) drown_amt = 30.0; // cap drowning
					
					SetHealth(playerid, health - drown_amt);
					AddDamage(playerid, BODY_PART_TORSO, 52);
				}
				default: // Other environmental damage
				{
					SetHealth(playerid, health-amount);
					if(weaponid > 0 && weaponid <= 15)
						AddDamage(playerid, bodypart, weaponid);
					else
						AddDamage(playerid, BODY_PART_TORSO, weaponid);
				}
			}
		}

        if(issuerid != INVALID_PLAYER_ID && BODY_PART_TORSO <= bodypart <= BODY_PART_HEAD)
        {
            if(weaponid >= 0  && weaponid <= 8 && armour >= 0)
            {
                SetHealth(playerid, health-amount);
                AddDamage(playerid, bodypart, weaponid);
            }
            else if(22 <= weaponid <= 46)
            {
                switch(bodypart)
                {
                    case BODY_PART_TORSO:
                    {
                        switch(weaponid)
                        {
                            case WEAPON_SNIPER:
                            {
                                SetHealth(playerid, health-80);
                                AddDamage(playerid, bodypart, weaponid);
                            }
                            default:
                            {
                                if(armour > 0)
                                {
                                    AddDamage(playerid, bodypart, weaponid);
                                    SetArmour(playerid, armour-amount);
                                }
                                else if(armour <= 0)
                                {
                                    AddDamage(playerid, bodypart, weaponid);
                                    SetHealth(playerid, health-amount);
                                }
                            }
                        }
                    }
                    case BODY_PART_HEAD:
                    {
                        switch(weaponid)
                        {
                           case WEAPON_SNIPER:
                           {
                                SetHealth(playerid, 0);
                                AddDamage(playerid, bodypart, weaponid);
                           }
                           default:
                           {
                                // Headshot: armour absorbs some damage, health takes reduced damage
                                if(armour > 0)
                                {
                                    AddDamage(playerid, bodypart, weaponid);
                                    SetArmour(playerid, armour-amount);
                                    SetHealth(playerid, health-(amount*0.3));
                                }
                                else
                                {
                                    AddDamage(playerid, bodypart, weaponid);
                                    SetHealth(playerid, health-amount);
                                }
                           }
                        }
                    }
                    default :
                    {
                        // Limb shots (arms/legs/groin): armour absorbs first, then health
                        if(armour > 0)
                        {
                            AddDamage(playerid, bodypart, weaponid);
                            SetArmour(playerid, armour-amount);
                        }
                        else
                        {
                            AddDamage(playerid, bodypart, weaponid);
                            SetHealth(playerid, health-amount);
                        }
                    }
                }
            }
        }
	}
	else
	{
		if(GetPlayerTeam(playerid) == GetPlayerTeam(issuerid) && EventData[eventTypes] == TYPE_TDM || EventData[eventTypes] == TYPE_ZOMBIE)
		{
			SetPlayerArmour(playerid, ReturnArmour2(playerid));
			SetPlayerHealth(playerid, ReturnHealth2(playerid));
		}
	}
    return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	#if defined DEBUG_MODE
	    printf("[debug] OnPlayerGiveDamage(PID : %d TID : %d Amount : %.2f WID : %d Body-Part : %d)", playerid, damagedid, amount, weaponid, bodypart);
	#endif

    if(weaponid == WEAPON_CHAINSAW)
    {
        SetPlayerHealth(damagedid, GetHealth(damagedid));
        SetPlayerArmour(damagedid, GetArmour(damagedid));
        return 0;
    }
    return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	if(GetPVarInt(playerid,"OnWork"))  DisablePlayerCheckpoint(playerid);

	if(GetPlayerGPSInfo(playerid, G_ENABLED) == GPS_STATUS_ON) if(IsPlayerInRangeOfPoint(playerid, 10.0, GetPlayerGPSInfo(playerid, G_POS_X), GetPlayerGPSInfo(playerid, G_POS_Y), GetPlayerGPSInfo(playerid, G_POS_Z))) DisablePlayerGPS(playerid);
	if(pData[playerid][pFindEms] != INVALID_PLAYER_ID)
	{
		pData[playerid][pFindEms] = INVALID_PLAYER_ID;
		DisablePlayerCheckpoint(playerid);
	}
	//DisablePlayerCheckpoint(playerid);
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
    #if defined DEBUG_MODE
        printf("[Callback: OnRconLoginAttempt]: IP: %s, Password: %s, Success: %d", ip, password, success);
    #endif

    if(!success)
    {
        foreach (new i : Player) if(!strcmp(pData[i][pIP], ip, true) && pData[i][pAdmin] < 6) KickEx(i);
        SendAdminMessage(TOMATO, "AdmWarn: RCON login attempt failed from \"%s\".", ip);
    }
    else
    {
        foreach (new i : Player) if(pData[i][pAdmin] < 6) {
            if(++pData[i][pRconAttemp] > 3)
            {
            	SendAdminMessage(TOMATO, "AdmWarn: %s was kicked for logging into RCON without authorization.", ReturnName(i));
               	KickEx(i);
            }
            break;
        }
    }
    return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
    // if(pData[playerid][pMaskOn]) ShowPlayerNameTagForPlayer(forplayerid, playerid, 0);
    // else ShowPlayerNameTagForPlayer(forplayerid, playerid, 1);

    if (pData[playerid][pFaction] == pData[forplayerid][pFaction] && pData[playerid][pUndercover] == 1)  SetPlayerMarkerForPlayer(forplayerid, playerid, COLOR_BLUE);
    return 1;
}

// Player clicked a dynamic object
public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
	if (pData[playerid][pEditFurnFlat] != -1) {
		new flatid = pData[playerid][pEditFurnFlat];

		foreach (new slot : FlatFurnitures[flatid]) if (objectid == FlatFurniture[flatid][slot][furnObject]) {
		switch (SelectFurnitureType[playerid]) {
			case FURNITURE_SELECT_MOVE: {
			pData[playerid][pEditFurniture] = slot;
			pData[playerid][pEditFurnFlat] = flatid;

			EditDynamicObject(playerid, FlatFurniture[flatid][slot][furnObject]);
			SendCustomMessage(playerid, "FURNITURE", "You are now editing the position of \"%s"WHITE_E"\".", FlatFurniture[flatid][slot][furnName]);
			break;
			}
			case FURNITURE_SELECT_DESTROY: {
			SendCustomMessage(playerid, "FURNITURE", "You have destroyed furniture \"%s"WHITE_E"\".", FlatFurniture[flatid][slot][furnName]);
			FlatFurniture_Delete(slot, flatid);

			CancelEdit(playerid);
			pData[playerid][pEditFurniture] = -1;
			pData[playerid][pEditFurnFlat] = -1;
			break;
			}
			case FURNITURE_SELECT_STORE: {
			if (FlatFurniture[flatid][slot][furnUnused])
				return Error(playerid, "This furniture already stored."), CancelEdit(playerid);
			
			FlatFurniture[flatid][slot][furnUnused] = 1;
			FlatFurniture_Refresh(slot, flatid);
			FlatFurniture_Save(slot, flatid);
			SendCustomMessage(playerid, "FURNITURE", "You have stored furniture \"%s"WHITE_E"\" into your flat.", FlatFurniture[flatid][slot][furnName]);
			break;
			}
		}
		}
	}
	if (pData[playerid][pEditFurnHouse] != -1) {
        new houseid = pData[playerid][pEditFurnHouse];

        foreach (new furnitureid : HouseFurnitures[houseid]) if (objectid == FurnitureData[houseid][furnitureid][furnitureObject]) {
            switch (SelectFurnitureType[playerid]) {
                case FURNITURE_SELECT_MOVE: {
                    pData[playerid][pEditingMode] = 4;
                    pData[playerid][pEditFurniture] = furnitureid;
                    EditDynamicObject(playerid, FurnitureData[houseid][furnitureid][furnitureObject]);
                    SendCustomMessage(playerid, "HOUSE", "You are now editing the position of item \"%s\".", FurnitureData[houseid][furnitureid][furnitureName]);
                    break;
                }
                case FURNITURE_SELECT_DESTROY:
                {
                    SendCustomMessage(playerid, "HOUSE", "You have destroyed furniture \"%s\".", FurnitureData[houseid][furnitureid][furnitureName]);
                    Furniture_Delete(furnitureid, houseid);

                    CancelEdit(playerid);
                    pData[playerid][pEditFurniture] = -1;
                    pData[playerid][pEditFurnHouse] = -1;
                    break;
                }
                case FURNITURE_SELECT_STORE: {
                    if (FurnitureData[houseid][furnitureid][furnitureUnused])
                        return Error(playerid, "This furniture is already stored"), CancelEdit(playerid);
                    
                    FurnitureData[houseid][furnitureid][furnitureUnused] = 1;
                    Furniture_Refresh(furnitureid, houseid);
                    Furniture_Save(furnitureid, houseid);
                    SendCustomMessage(playerid, "HOUSE", "You have stored furniture \"%s"WHITE_E"\" into your house.", FurnitureData[houseid][furnitureid][furnitureName]);
                    break;
                }
            }
            break;
        }
    }
	if (pData[playerid][pEditHouseStructure] != -1) {
        new houseid = pData[playerid][pEditHouseStructure];

        foreach (new i : HouseStruct[houseid]) {
            if (HouseStructure[houseid][i][structureObject] == objectid) {
                switch (SelectStructureType[playerid]) {
                    case STRUCTURE_SELECT_EDITOR: {
                        if (HouseStructure[houseid][i][structureType] == 0) {
                            pData[playerid][pEditStructure] = i;
                            pData[playerid][pEditingMode] = 3;
                            EditDynamicObject(playerid, HouseStructure[houseid][i][structureObject]);
                            SendCustomMessage(playerid, "BUILDER", "You're now editing %s.", GetStructureNameByModel(HouseStructure[houseid][i][structureModel]));
                            break;
                        }
                    }
                    case STRUCTURE_SELECT_RETEXTURE: {
                        SetPVarInt(playerid, "structureObj", i);
                        CancelEdit(playerid);
                        Dialog_Show(playerid, House_StructureRetexture, DIALOG_STYLE_INPUT, "Retexture House Structure", "Please input the texture name below:\n"YELLOW_E"[model] [txdname] [texture] [opt: alpha] [opt: red] [opt: green] [opt: blue]", "Retexture", "Cancel");
                        break;
                    }
                    case STRUCTURE_SELECT_DELETE: {
                        if (HouseStructure[houseid][i][structureType] == 0) {
                            SendCustomMessage(playerid, "BUILDER", "You've been successfully deleted %s", GetStructureNameByModel(HouseStructure[houseid][i][structureModel]));
                            HouseStructure_Delete(i, houseid);
                            break;
                        }
                    }
                    case STRUCTURE_SELECT_COPY: {
                        if (HouseStructure[houseid][i][structureType] == 0) {
                            new price;

                            for (new id = 0; id < sizeof(g_aHouseStructure); id ++) if (g_aHouseStructure[id][e_StructureModel] == HouseStructure[houseid][i][structureModel]) {
                                price = g_aHouseStructure[id][e_StructureCost];
                            }

                            if (pData[playerid][pComponent] < price)
                                return Error(playerid, "You need %d Component(s) to copy this structure.", price);

                            new copyId = HouseStructure_CopyObject(i, houseid);

                            if (copyId == cellmin)
                                return Error(playerid, "Your house has reached maximum of structure");

                            pData[playerid][pComponent] -= price;
                            pData[playerid][pEditStructure] = copyId;
                            pData[playerid][pEditingMode] = 3;
                            pData[playerid][pEditHouseStructure] = houseid;
                            EditDynamicObject(playerid, HouseStructure[houseid][copyId][structureObject]);
                            SendCustomMessage(playerid, "BUILDER", "You have copied structure for "GREEN_E"%d component(s)", price);
                            SendCustomMessage(playerid, "BUILDER", "You're now editing copied object of %s.", GetStructureNameByModel(HouseStructure[houseid][i][structureModel]));
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
	new string[144];
	foreach(new slot : DynamicObjects)
	{
	    if(DynamicObject[slot] == objectid)
	    {
	    	if(SelectObjectType[playerid] == OBJECT_SELECT_DELETE)
	    	{
	    		new next;
		        if(ObjectEditor[slot] != INVALID_PLAYER_ID)
                {
                    new editor = ObjectEditor[slot];
					if(GetPVarInt(editor,"EditingObject") == slot)
					{
						new playername[MAX_PLAYER_NAME];
			            GetPlayerName(ObjectEditor[slot],playername,sizeof(playername));
					    format(string,sizeof(string),"ERROR: "RED_E"%s "GREY_E"is currently editing this object!",playername);
						return SendClientMessageEx(playerid,COLOR_ARWIN,string);
					}
                }
                DestroyDynamicObject(DynamicObject[slot]);
				Looping(i,MAX_OBJECT_MATERIAL_SLOT)
				{
					DynamicObjectMaterial[slot][i] = MATERIAL_TYPE_NONE;
				}
				Iter_SafeRemove(DynamicObjects,slot,next);
                format(string,sizeof(string),"OBJECT: Object with ID %d has been deleted, total object: %d",slot,Iter_Count(DynamicObjects));
                slot = next;
                SendClientMessage(playerid,COLOR_ARWIN,string);
	    	}
	        break;
	    }
	}
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ )
{
	new weaponid = EditingWeapon[playerid];
	if(response == EDIT_RESPONSE_FINAL)
	{
		if(weaponid) {
			new enum_index = (weaponid >= 22 && weaponid <= 38) ? (weaponid - 22) : (weaponid + 15), weaponname[18], string[340];
            GetWeaponName(weaponid, weaponname, sizeof(weaponname));
            WeaponSettings[playerid][enum_index][Position][0] = fOffsetX;
            WeaponSettings[playerid][enum_index][Position][1] = fOffsetY;
            WeaponSettings[playerid][enum_index][Position][2] = fOffsetZ;
            WeaponSettings[playerid][enum_index][Position][3] = fRotX;
            WeaponSettings[playerid][enum_index][Position][4] = fRotY;
            WeaponSettings[playerid][enum_index][Position][5] = fRotZ;
            RemovePlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid));
            SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), WeaponSettings[playerid][enum_index][Bone], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, 1.0, 1.0, 1.0);
            SendCustomMessage(playerid, "SYOW", "You have successfully adjusted the position of your "AQUA_E"%s.", weaponname);
            mysql_format(g_SQL, string, sizeof(string), "INSERT INTO weaponsettings (Owner, WeaponID, PosX, PosY, PosZ, RotX, RotY, RotZ) VALUES ('%d', %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f) ON DUPLICATE KEY UPDATE PosX = VALUES(PosX), PosY = VALUES(PosY), PosZ = VALUES(PosZ), RotX = VALUES(RotX), RotY = VALUES(RotY), RotZ = VALUES(RotZ)", pData[playerid][pID], weaponid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
            mysql_tquery(g_SQL, string);
            EditingWeapon[playerid] = 0;
		}
		else if(pData[playerid][pAksesoris] != -1 && !EditingWeapon[playerid]) {
			new id = pData[playerid][pAksesoris];
            AccData[playerid][id][accOffset][0] = fOffsetX;
            AccData[playerid][id][accOffset][1] = fOffsetY;
            AccData[playerid][id][accOffset][2] = fOffsetZ;
            AccData[playerid][id][accRot][0] = fRotX;
            AccData[playerid][id][accRot][1] = fRotY;
            AccData[playerid][id][accRot][2] = fRotZ;
            AccData[playerid][id][accScale][0] = (fScaleX > 3.0) ? (3.0) : (fScaleX);
            AccData[playerid][id][accScale][1] = (fScaleY > 3.0) ? (3.0) : (fScaleY);
            AccData[playerid][id][accScale][2] = (fScaleZ > 3.0) ? (3.0) : (fScaleZ);
            Aksesoris_Attach(playerid, id);
            pData[playerid][pAksesoris] = -1;  
            SendCustomMessage(playerid, "DYOC","Accessory saved successfully!.");
		}
	}
	if(response == EDIT_RESPONSE_CANCEL) {
		if(weaponid) {
			new enum_index = (weaponid >= 22 && weaponid <= 38) ? (weaponid - 22) : (weaponid + 15);
			SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), WeaponSettings[playerid][enum_index][Bone], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, 1.0, 1.0, 1.0);
			EditingWeapon[playerid] = -1;
		}
		else if(pData[playerid][pAksesoris] != -1 && !EditingWeapon[playerid]) {
			Aksesoris_Attach(playerid, pData[playerid][pAksesoris]);
			pData[playerid][pAksesoris] = -1;
		}
	}
	return 1;
}

public OnPlayerEditDynamicObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(response == EDIT_RESPONSE_CANCEL)
	{
		if(pData[playerid][pEditHouseStructure] != -1 && pData[playerid][pEditStructure] != -1)
		{
			new houseid = pData[playerid][pEditHouseStructure], id = pData[playerid][pEditStructure];
			HouseStructure_Refresh(id, houseid);
			pData[playerid][pEditHouseStructure] = -1;
			pData[playerid][pEditStructure] = -1;
			pData[playerid][pEditingMode] = -1;
			return 1;
		}
	}
	if(response == EDIT_RESPONSE_FINAL)
	{
		if(GetPVarType(playerid,"EditingObject") > 0)
		{
		    new slot = GetPVarInt(playerid,"EditingObject");
		    DeletePVar(playerid,"EditingObject");
		    ObjectEditor[slot] = INVALID_PLAYER_ID;
		    SetDynamicObjectPos(objectid,x,y,z);
            SetDynamicObjectRot(objectid,rx,ry,rz);
		}
		if(pData[playerid][pEditFurnHouse] != -1 && pData[playerid][pEditFurniture] != -1) {
			new id = pData[playerid][pEditFurnHouse];
			FurnitureData[id][pData[playerid][pEditFurniture]][furniturePos][0] = x;
			FurnitureData[id][pData[playerid][pEditFurniture]][furniturePos][1] = y;
			FurnitureData[id][pData[playerid][pEditFurniture]][furniturePos][2] = z;
			FurnitureData[id][pData[playerid][pEditFurniture]][furnitureRot][0] = rx;
			FurnitureData[id][pData[playerid][pEditFurniture]][furnitureRot][1] = ry;
			FurnitureData[id][pData[playerid][pEditFurniture]][furnitureRot][2] = rz;
			
			SetDynamicObjectPos(objectid,x,y,z);
			SetDynamicObjectRot(objectid,rx,ry,rz);
			Furniture_Refresh(pData[playerid][pEditFurniture], id);
			Furniture_Save(pData[playerid][pEditFurniture], id);

			SendCustomMessage(playerid, "BUILDER", "Furniture position has been saved.");

			pData[playerid][pEditFurniture] = -1;
			pData[playerid][pEditFurnHouse] = -1;
			return 1;
		}
		if (pData[playerid][pEditSpeed] != -1 && SpeedData[pData[playerid][pEditSpeed]][speedExists]) {
			new id = pData[playerid][pEditSpeed];
			SpeedData[id][speedPos][0] = x;
			SpeedData[id][speedPos][1] = y;
			SpeedData[id][speedPos][2] = z;
			SpeedData[id][speedPos][3] = rz;
			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);
			
			Speed_Refresh(id);
			Speed_Save(id);
			SendCustomMessage(playerid, "SPEEDCAM", "Speed camera position has been saved.");
			pData[playerid][pEditSpeed] = -1;
		}
		if(pData[playerid][pEditHouseStructure] != -1 && pData[playerid][pEditStructure] != -1) {
			new houseid = pData[playerid][pEditHouseStructure], id = pData[playerid][pEditStructure];

			HouseStructure[houseid][id][structurePos][0] = x;
			HouseStructure[houseid][id][structurePos][1] = y;
			HouseStructure[houseid][id][structurePos][2] = z;
			HouseStructure[houseid][id][structureRot][0] = rx;
			HouseStructure[houseid][id][structureRot][1] = ry;
			HouseStructure[houseid][id][structureRot][2] = rz;

			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);
			HouseStructure_Refresh(id, houseid);
			HouseStructure_Save(id, houseid);

			SendCustomMessage(playerid, "BUILDER", "Structure position has been saved.");

			pData[playerid][pEditHouseStructure] = -1;
			pData[playerid][pEditStructure] = -1;
			pData[playerid][pEditingMode] = -1;
			return 1;
		}
		if (GetPVarInt(playerid, "editTollGateID") != -1) {
			new mode = GetPVarInt(playerid, "editTollGateMode");
			if (mode == 0) 
			{
				new id = GetPVarInt(playerid, "editTollGateID");
				TollGate_SetObjectPos(id, x, y, z, rx, ry, rz);

				TollGate_Refresh(id);
				TollGate_Save(id);
				SendCustomMessage(playerid, "TOLLGATE", "You've sucessfully editing toll gate position!");
				SetPVarInt(playerid, "editTollGateID", -1);
				SetPVarInt(playerid, "editTollGateMode", -1);
				return 1;
			} 
			else if (mode == 1) 
			{
				new id = GetPVarInt(playerid, "editTollGateID");
				TollGate_SetObjectMove(id, x, y, z, rx, ry, rz);

				TollGate_Refresh(id);
				TollGate_Save(id);
				SendCustomMessage(playerid, "TOLLGATE", "You've successfully editing toll gate move!");
				SetPVarInt(playerid, "editTollGateID", -1);
				SetPVarInt(playerid, "editTollGateMode", -1);
				return 1;
			}
		}
		if (GetPVarInt(playerid, "editDoorFactionID") != -1) {
			new mode = GetPVarInt(playerid, "editDoorFactionMode");
			if (mode == 0) 
			{
				new id = GetPVarInt(playerid, "editDoorFactionID");
				DoorFaction_SetObjectPos(id, x, y, z, rx, ry, rz);

				DoorFaction_Refresh(id);
				DoorFaction_Save(id);
				SendCustomMessage(playerid, "DOORFACTION", "You've sucessfully editing door faction position!");
				SetPVarInt(playerid, "editDoorFactionID", -1);
				SetPVarInt(playerid, "editDoorFactionMode", -1);
				return 1;
			} 
			else if (mode == 1) 
			{
				new id = GetPVarInt(playerid, "editDoorFactionID");
				DoorFaction_SetObjectMove(id, x, y, z, rx, ry, rz);

				DoorFaction_Refresh(id);
				DoorFaction_Save(id);
				SendCustomMessage(playerid, "DOORFACTION", "You've successfully editing door faction move!");
				SetPVarInt(playerid, "editDoorFactionID", -1);
				SetPVarInt(playerid, "editDoorFactionMode", -1);
				return 1;
			}
		}
		if (pData[playerid][pEditFurniture] != -1 && pData[playerid][pEditFurnFlat] != -1)
		{
			new flatid = pData[playerid][pEditFurnFlat],
      		slot = pData[playerid][pEditFurniture];
			if (flatid != -1 && (FlatRoom_IsOwner(playerid, flatid) || FlatRoom_IsBuilder(playerid, flatid))) 
			{
				if (!IsPointInDynamicArea(FlatRoom[flatid][flatRoomArea], x, y, z))
					return Error(playerid, "You can't place furniture outside the flat area"), CancelEdit(playerid), FlatFurniture_Refresh(slot, flatid);
				FlatFurniture[flatid][slot][furnPos][0] = x;
				FlatFurniture[flatid][slot][furnPos][1] = y;
				FlatFurniture[flatid][slot][furnPos][2] = z;
				FlatFurniture[flatid][slot][furnRot][0] = rx;
				FlatFurniture[flatid][slot][furnRot][1] = ry;
				FlatFurniture[flatid][slot][furnRot][2] = rz;
				
				SetDynamicObjectPos(objectid,x,y,z);
				SetDynamicObjectRot(objectid,rx,ry,rz);
				FlatFurniture_Refresh(slot, flatid);
				FlatFurniture_Save(slot, flatid);

				SendCustomMessage(playerid, "FURNITURE", "You have edited the position of item \"%s"WHITE_E"\".", FlatFurniture[flatid][slot][furnName]);

				pData[playerid][pEditFurniture] = -1;
				pData[playerid][pEditFurnHouse] = -1;
			}
			return 1;
		}
		if(objectid == pEditPoint[playerid][pEditObject] || objectid == pEditPoint[playerid][pEditObjectSel])
		{
			if(pEditPoint[playerid][pEditObjectSel])
		    {
			    CallLocalFunction(pEditPoint[playerid][pEditCallBack], "iiifffffffff",
			        playerid, objectid, response,
					x,
					y,
					z,
					rx,
					ry,
					rz,
					x - pEditPoint[playerid][pSaveX],
					y - pEditPoint[playerid][pSaveY],
					z - pEditPoint[playerid][pSaveZ]);
	            DestroyEditPoint(playerid);
		    }
		    else
		    {
			    CallLocalFunction(pEditPoint[playerid][pEditCallBack], "iiifffffffff",
			        playerid, objectid, response,
					pEditPoint[playerid][pEditX],
					pEditPoint[playerid][pEditY],
					pEditPoint[playerid][pEditZ],
					pEditPoint[playerid][pEditRX],
					pEditPoint[playerid][pEditRY],
					pEditPoint[playerid][pEditRZ],
					pEditPoint[playerid][pEditX] - pEditPoint[playerid][pSaveX],
					pEditPoint[playerid][pEditY] - pEditPoint[playerid][pSaveY],
					pEditPoint[playerid][pEditZ] - pEditPoint[playerid][pSaveZ]
				);
	            DestroyEditPoint(playerid);
			}
			return 1;
		}
		if(pData[playerid][pEditingMode] == 5) {
			if (pData[playerid][pEditGYMObject] != -1 && Iter_Contains(GYMObjects, pData[playerid][pEditGYMObject])) {
				new id = pData[playerid][pEditGYMObject], bizid = pData[playerid][pInBiz];

				if (bizid != -1) {
					GYMObject[id][objectPos][0] = x;
					GYMObject[id][objectPos][1] = y;
					GYMObject[id][objectPos][2] = z;
					GYMObject[id][objectRot][0] = rx;
					GYMObject[id][objectRot][1] = ry;
					GYMObject[id][objectRot][2] = rz;
					SetDynamicObjectPos(objectid, x, y, z);
					SetDynamicObjectRot(objectid, rx, ry, rz);

					GYMObject_Refresh(id);
					GYMObject_Save(id);

					SendCustomMessage(playerid, "GYMOBJECT", "GYM Object position has been saved.");

					pData[playerid][pEditGYMObject] = -1;
				}
			}
			pData[playerid][pEditingMode] = -1;
			return 1;
		}
		if(pData[playerid][pEditingMode] == 2)
		{
			new index = pData[playerid][pEditRoadblock];
			BarricadeData[index][cadePos][0] = x;
			BarricadeData[index][cadePos][1] = y;
			BarricadeData[index][cadePos][2] = z;
			BarricadeData[index][cadePos][3] = rx;
			BarricadeData[index][cadePos][4] = ry;
			BarricadeData[index][cadePos][5] = rz;
			Barricade_Sync(index);
			pData[playerid][pEditRoadblock] = -1;
			pData[playerid][pEditingMode] = -1;
			return 1;
		}
		if(Player_EditingObject[playerid] > 0)
        {
            new
                vehicleid = Player_EditVehicleObject[playerid],
                vehid = GetPlayerVehicleID(playerid),
                slot = Player_EditVehicleObjectSlot[playerid],
                Float:vx,
                Float:vy,
                Float:vz,
                Float:va,
                Float:real_x,
                Float:real_y,
                Float:real_z;

            GetVehiclePos(vehid, vx, vy, vz);
            GetVehicleZAngle(vehid, va); // Coba lagi

            real_x = x - vx;
            real_y = y - vy;
            real_z = z - vz;

            new Float:v_size[3];
            GetVehicleModelInfo(pvData[vehicleid][cModel], VEHICLE_MODEL_INFO_SIZE, v_size[0], v_size[1], v_size[2]);
            if(	(real_x >= v_size[0] || -v_size[0] >= real_x) ||
                (real_y >= v_size[1] || -v_size[1] >= real_y) ||
                (real_z >= v_size[2] || -v_size[2] >= real_z))
            {
                SendClientMessageEx(playerid, COLOR_ARWIN,"MODSHOP: "WHITE_E"Posisi object terlal jauh dari body kendaraan.");
                ResetEditing(playerid);
				Streamer_Update(playerid);
                return 1;
            }
			new Float:vpos[3];
			GetVehiclePos(vehid, vpos[0], vpos[1], vpos[2]);

			VehicleObjects[vehicleid][slot][vehObjectPosX] = x - vpos[0];
			VehicleObjects[vehicleid][slot][vehObjectPosY] = y - vpos[1];
			VehicleObjects[vehicleid][slot][vehObjectPosZ] = z - vpos[2];
			VehicleObjects[vehicleid][slot][vehObjectPosRX] = rx;
			VehicleObjects[vehicleid][slot][vehObjectPosRY] = ry;
			VehicleObjects[vehicleid][slot][vehObjectPosRZ] = rz;
		
			Vehicle_ObjectUpdate(vehicleid, slot);
			Vehicle_ObjectSave(vehicleid, slot);
			Streamer_Update(playerid);
            if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
            {
                Dialog_Show(playerid, VACCSE, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nChange Color\nRemove Modification\nSave", "Select", "Back");
            }
            else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_TEXT)
            {
                Dialog_Show(playerid, VACCSE1, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nText Name\nText Size\nText Font\nText Color\nRemove Modification\nSave", "Select", "Back");
            }
            else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_LIGHT)
            {
                Dialog_Show(playerid, VACCSE2, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nRemove Modification\nSave", "Select", "Back");
            }
			else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_PLATE)
            {
                Dialog_Show(playerid, VACCSE3, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nRemove Modification\nSave", "Select", "Back");
            }
			else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_NEON)
            {
                Dialog_Show(playerid, VACCSE4, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nRemove Modification\nSave", "Select", "Back");
            }
			return 1;
		}
		if(pData[playerid][EditingTreeID] != -1 && Iter_Contains(Trees, pData[playerid][EditingTreeID]))
		{
			new etid = pData[playerid][EditingTreeID];
	        TreeData[etid][treeX] = x;
	        TreeData[etid][treeY] = y;
	        TreeData[etid][treeZ] = z;
	        TreeData[etid][treeRX] = rx;
	        TreeData[etid][treeRY] = ry;
	        TreeData[etid][treeRZ] = rz;

	        SetDynamicObjectPos(objectid, TreeData[etid][treeX], TreeData[etid][treeY], TreeData[etid][treeZ]);
	        SetDynamicObjectRot(objectid, TreeData[etid][treeRX], TreeData[etid][treeRY], TreeData[etid][treeRZ]);
			Streamer_UpdateEx(playerid, TreeData[etid][treeX], TreeData[etid][treeY], TreeData[etid][treeZ]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, TreeData[etid][treeLabel], E_STREAMER_X, TreeData[etid][treeX]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, TreeData[etid][treeLabel], E_STREAMER_Y, TreeData[etid][treeY]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, TreeData[etid][treeLabel], E_STREAMER_Z, TreeData[etid][treeZ] + 1.5);

		    Tree_Save(etid);
	        pData[playerid][EditingTreeID] = -1;
			return 1;
		}
		if(pData[playerid][EditingATMID] != -1 && Iter_Contains(ATMS, pData[playerid][EditingATMID]))
		{
			new etid = pData[playerid][EditingATMID];
	        AtmData[etid][atmX] = x;
	        AtmData[etid][atmY] = y;
	        AtmData[etid][atmZ] = z;
	        AtmData[etid][atmRX] = rx;
	        AtmData[etid][atmRY] = ry;
	        AtmData[etid][atmRZ] = rz;

	        SetDynamicObjectPos(objectid, AtmData[etid][atmX], AtmData[etid][atmY], AtmData[etid][atmZ]);
	        SetDynamicObjectRot(objectid, AtmData[etid][atmRX], AtmData[etid][atmRY], AtmData[etid][atmRZ]);

			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, AtmData[etid][atmLabel], E_STREAMER_X, AtmData[etid][atmX]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, AtmData[etid][atmLabel], E_STREAMER_Y, AtmData[etid][atmY]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, AtmData[etid][atmLabel], E_STREAMER_Z, AtmData[etid][atmZ] + 0.3);

			Streamer_SetFloatData(STREAMER_TYPE_PICKUP, AtmData[etid][atmpickup], E_STREAMER_X, AtmData[etid][atmX]);
			Streamer_SetFloatData(STREAMER_TYPE_PICKUP, AtmData[etid][atmpickup], E_STREAMER_Y, AtmData[etid][atmY]+1);
			Streamer_SetFloatData(STREAMER_TYPE_PICKUP, AtmData[etid][atmpickup], E_STREAMER_Z, AtmData[etid][atmZ]);
			Streamer_UpdateEx(playerid, AtmData[etid][atmX], AtmData[etid][atmY], AtmData[etid][atmZ]);
		    Atm_Save(etid);
	        pData[playerid][EditingATMID] = -1;
			return 1;
		}
		if(pData[playerid][gEditID] != -1 && Iter_Contains(Gates, pData[playerid][gEditID]))
		{
			new id = pData[playerid][gEditID];
			if(pData[playerid][gEdit] == 1)
			{
				gData[id][gCX] = x;
				gData[id][gCY] = y;
				gData[id][gCZ] = z;
				gData[id][gCRX] = rx;
				gData[id][gCRY] = ry;
				gData[id][gCRZ] = rz;
				if(IsValidDynamic3DTextLabel(gData[id][gText])) DestroyDynamic3DTextLabel(gData[id][gText]);
				new str[64];
				format(str, sizeof(str), "Gate ID: %d", id);
				gData[id][gText] = CreateDynamic3DTextLabel(str, COLOR_WHITE, gData[id][gCX], gData[id][gCY], gData[id][gCZ], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 10.0);
				Streamer_UpdateEx(playerid, gData[id][gCX], gData[id][gCY], gData[id][gCZ]);
				pData[playerid][gEditID] = -1;
				pData[playerid][gEdit] = 0;
				SendCustomMessage(playerid, "EDIT", "You have finished editing gate ID %d's closing position.", id);
				gData[id][gStatus] = 0;
				Gate_Save(id);
				return 1;
			}
			else if(pData[playerid][gEdit] == 2)
			{
				gData[id][gOX] = x;
				gData[id][gOY] = y;
				gData[id][gOZ] = z;
				gData[id][gORX] = rx;
				gData[id][gORY] = ry;
				gData[id][gORZ] = rz;
				
				pData[playerid][gEditID] = -1;
				pData[playerid][gEdit] = 0;
				SendCustomMessage(playerid, "EDIT", "You have finished editing gate ID %d's opening position.", id);

				gData[id][gStatus] = 1;
				Gate_Save(id);
				return 1;
			}
		}
	}
	if(response == EDIT_RESPONSE_UPDATE)
	{
		if(objectid == pEditPoint[playerid][pEditObject] || objectid == pEditPoint[playerid][pEditObjectSel])
		{
			pEditPoint[playerid][pEditX] = x;
		    pEditPoint[playerid][pEditY] = y;
		    pEditPoint[playerid][pEditZ] = z;
		    pEditPoint[playerid][pEditRX] = rx;
		    pEditPoint[playerid][pEditRY] = ry;
		    pEditPoint[playerid][pEditRZ] = rz;

		    CallLocalFunction(pEditPoint[playerid][pEditCallBack], "iiifffffffff",
		        playerid, objectid, response, x, y, z, rx, ry, rz,
				pEditPoint[playerid][pEditX] - pEditPoint[playerid][pSaveX],
				pEditPoint[playerid][pEditY] - pEditPoint[playerid][pSaveY],
				pEditPoint[playerid][pEditZ] - pEditPoint[playerid][pSaveZ]
			);
			pEditPoint[playerid][pEditObject] = -1;
			return 1;
		}
	}
	if(response == EDIT_RESPONSE_CANCEL)
	{
		if(GetPVarType(playerid,"EditingObject") > 0)
		{
		    new slot = GetPVarInt(playerid,"EditingObject");
		    DeletePVar(playerid,"EditingObject");
		    ObjectEditor[slot] = INVALID_PLAYER_ID;
		    new Float:cPos[3],Float:cRot[3];
            Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_X,cPos[0]);
            Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Y,cPos[1]);
            Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_Z,cPos[2]);
            Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_X,cRot[0]);
            Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_Y,cRot[1]);
            Streamer_GetFloatData(STREAMER_TYPE_OBJECT,DynamicObject[slot],E_STREAMER_R_Z,cRot[2]);
            SetDynamicObjectPos(objectid,cPos[0],cPos[1],cPos[2]);
            SetDynamicObjectRot(objectid,cRot[0],cRot[1],cRot[2]);
		}
		if(Player_EditingObject[playerid] > 0)
		{
			new
                vehicleid = Player_EditVehicleObject[playerid],
                slot = Player_EditVehicleObjectSlot[playerid];
			if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
            {
                Dialog_Show(playerid, VACCSE, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nChange Color\nRemove Modification\nSave", "Select", "Back");
            }
            else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_TEXT)
            {
                Dialog_Show(playerid, VACCSE1, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nText Name\nText Size\nText Font\nText Color\nRemove Modification\nSave", "Select", "Back");
            }
            else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_LIGHT)
            {
                Dialog_Show(playerid, VACCSE2, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nRemove Modification\nSave", "Select", "Back");
            }
			Streamer_Update(playerid);
			SendCustomMessage(playerid, "MODSHOP", "You've been canceled editing modification.");
			return 1;
		}
		if(pData[playerid][EditingTreeID] != -1 && Iter_Contains(Trees, pData[playerid][EditingTreeID]))
		{
			new etid = pData[playerid][EditingTreeID];
	        SetDynamicObjectPos(objectid, TreeData[etid][treeX], TreeData[etid][treeY], TreeData[etid][treeZ]);
	        SetDynamicObjectRot(objectid, TreeData[etid][treeRX], TreeData[etid][treeRY], TreeData[etid][treeRZ]);
	        pData[playerid][EditingTreeID] = -1;
			return 1;
		}
		if(pData[playerid][EditingATMID] != -1 && Iter_Contains(ATMS, pData[playerid][EditingATMID]))
		{
			new etid = pData[playerid][EditingATMID];
	        SetDynamicObjectPos(objectid, AtmData[etid][atmX], AtmData[etid][atmY], AtmData[etid][atmZ]);
	        SetDynamicObjectRot(objectid, AtmData[etid][atmRX], AtmData[etid][atmRY], AtmData[etid][atmRZ]);
	        pData[playerid][EditingATMID] = -1;
			return 1;
		}
		if(pData[playerid][gEditID] != -1 && Iter_Contains(Gates, pData[playerid][gEditID]))
		{
			new id = pData[playerid][gEditID];
			SetDynamicObjectPos(objectid, gPosX[playerid], gPosY[playerid], gPosZ[playerid]);
			SetDynamicObjectRot(objectid, gRotX[playerid], gRotY[playerid], gRotZ[playerid]);
			gPosX[playerid] = 0; gPosY[playerid] = 0; gPosZ[playerid] = 0;
			gRotX[playerid] = 0; gRotY[playerid] = 0; gRotZ[playerid] = 0;
			SendCustomMessage(playerid, "EDIT", "You have canceled editing gate ID %d.", id);
			Gate_Save(id);
			pData[playerid][gEditID] = -1;
			return 1;
		}
		if(pData[playerid][pEditStructure] != -1) {
			
			new slot = pData[playerid][pEditStructure], houseid = pData[playerid][pEditHouseStructure];
			new Float:position[3], Float:rotation[3];
			if (houseid != -1) {
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,HouseStructure[houseid][slot][structureObject],E_STREAMER_X,position[0]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,HouseStructure[houseid][slot][structureObject],E_STREAMER_Y,position[1]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,HouseStructure[houseid][slot][structureObject],E_STREAMER_Z,position[2]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,HouseStructure[houseid][slot][structureObject],E_STREAMER_R_X,rotation[0]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,HouseStructure[houseid][slot][structureObject],E_STREAMER_R_Y,rotation[1]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,HouseStructure[houseid][slot][structureObject],E_STREAMER_R_Z,rotation[2]);
				SetDynamicObjectPos(objectid,position[0],position[1],position[2]);
				SetDynamicObjectRot(objectid,rotation[0],rotation[1],rotation[2]);

				pData[playerid][pEditHouseStructure] = -1;
				pData[playerid][pEditStructure] = -1;
			}
			return 1;
		}
		if(pData[playerid][pEditFurniture] != -1) {
			new slot = pData[playerid][pEditFurniture], houseid = pData[playerid][pInHouse];
			new Float:position[3], Float:rotation[3];
			if (houseid != -1 && Iter_Contains(HouseFurnitures[houseid], slot)) {
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,FurnitureData[houseid][slot][furnitureObject],E_STREAMER_X,position[0]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,FurnitureData[houseid][slot][furnitureObject],E_STREAMER_Y,position[1]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,FurnitureData[houseid][slot][furnitureObject],E_STREAMER_Z,position[2]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,FurnitureData[houseid][slot][furnitureObject],E_STREAMER_R_X,rotation[0]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,FurnitureData[houseid][slot][furnitureObject],E_STREAMER_R_Y,rotation[1]);
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT,FurnitureData[houseid][slot][furnitureObject],E_STREAMER_R_Z,rotation[2]);
				SetDynamicObjectPos(objectid,position[0],position[1],position[2]);
				SetDynamicObjectRot(objectid,rotation[0],rotation[1],rotation[2]);
			}
			pData[playerid][pEditFurniture] = -1;
			return 1;
		}
		if(pData[playerid][pEditSpeed] != -1) {
			new Float:position[3],Float:rotation[3];
			new slot = pData[playerid][pEditSpeed];
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT,SpeedData[slot][speedObject],E_STREAMER_X,position[0]);
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT,SpeedData[slot][speedObject],E_STREAMER_Y,position[1]);
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT,SpeedData[slot][speedObject],E_STREAMER_Z,position[2]);
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT,SpeedData[slot][speedObject],E_STREAMER_R_Z,rotation[2]);
			SetDynamicObjectPos(objectid,position[0],position[1],position[2]);
			SetDynamicObjectRot(objectid,rotation[0],rotation[1],rotation[2]);
			pData[playerid][pEditSpeed] = -1;
		}
		if (GetPVarInt(playerid, "editTollGateID") != -1) {
			new mode = GetPVarInt(playerid, "editTollGateMode");
			if(mode == 0 || mode == 1)
			{
				new id = GetPVarInt(playerid, "editTollGateID");
				TollGate_Refresh(id);

				SetPVarInt(playerid, "editTollGateID", -1);
				SetPVarInt(playerid, "editTollGateMode", -1);

				SendCustomMessage(playerid, "DOORFACTION", "You've canceled editing door faction.");
				return 1;
			}
		}
		if (GetPVarInt(playerid, "editDoorFactionID") != -1) {
			new mode = GetPVarInt(playerid, "editDoorFactionMode");
			if(mode == 0 || mode == 1)
			{
				new id = GetPVarInt(playerid, "editDoorFactionID");
				DoorFaction_Refresh(id);

				SetPVarInt(playerid, "editDoorFactionID", -1);
				SetPVarInt(playerid, "editDoorFactionMode", -1);

				SendCustomMessage(playerid, "DOORFACTION", "You've canceled editing door faction.");
				return 1;
			}
		}
		if (pData[playerid][pEditFurniture] != -1 && pData[playerid][pEditFurnFlat] != -1)
		{
			new flatid = pData[playerid][pEditFurnFlat],
      		slot = pData[playerid][pEditFurniture];
			FlatFurniture_Refresh(slot, flatid);
			pData[playerid][pEditFurniture] = -1;
			pData[playerid][pEditFurnHouse] = -1;
			return 1;
		}
		
		if(objectid == pEditPoint[playerid][pEditObject] || objectid == pEditPoint[playerid][pEditObjectSel])
		{
			CallLocalFunction(pEditPoint[playerid][pEditCallBack], "iiifffffffff",
		        playerid, objectid, response,
				pEditPoint[playerid][pSaveX],
				pEditPoint[playerid][pSaveY],
				pEditPoint[playerid][pSaveZ],
				pEditPoint[playerid][pSaveRX],
				pEditPoint[playerid][pSaveRY],
				pEditPoint[playerid][pSaveRZ],
				0.0, 0.0, 0.0
			);
            DestroyEditPoint(playerid);
			return 1;
		}
		if(pData[playerid][pEditGYMObject] != -1) {
			new Float:position[3],Float:rotation[3];
			new slot = pData[playerid][pEditGYMObject];
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT,GYMObject[slot][objectgym],E_STREAMER_X,position[0]);
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT,GYMObject[slot][objectgym],E_STREAMER_Y,position[1]);
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT,GYMObject[slot][objectgym],E_STREAMER_Z,position[2]);
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT,GYMObject[slot][objectgym],E_STREAMER_R_X,rotation[0]);
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT,GYMObject[slot][objectgym],E_STREAMER_R_Y,rotation[1]);
			Streamer_GetFloatData(STREAMER_TYPE_OBJECT,GYMObject[slot][objectgym],E_STREAMER_R_Z,rotation[2]);
			SetDynamicObjectPos(objectid,position[0],position[1],position[2]);
			SetDynamicObjectRot(objectid,rotation[0],rotation[1],rotation[2]);
			UpdateDynamic3DTextLabelText(GYMObject[slot][objectLabel], -1, sprintf(""AQUA_E"[id:%d]\n%s\n"WHITE_E"Durability"YELLOW_E"%d"WHITE_E"/3000",slot, GetGYMObjectStatus(slot), GYMObject[slot][objectCondition]));
			pData[playerid][pEditGYMObject] = -1;
			return 1;
		}
	}
	return 0;
}

// Player clicked a dynamic object; Fix For new streamer version
public OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ) return 0;

public OnPlayerInteriorChange(playerid,newinteriorid,oldinteriorid)
{
	if(pData[playerid][IsLoggedIn] == true)
	{
		pData[playerid][pInt] = newinteriorid;
		if(newinteriorid != 0)
		{
			SetPlayerWeather(playerid, 0);
		}
		else
		{
			SetPlayerWeather(playerid, current_weather);
			SetPlayerStreamerSettings(playerid);
		}
	}
    foreach(new i : Player) if(pData[i][pSpec] != INVALID_PLAYER_ID && pData[i][pSpec] == playerid) {
        SetPlayerInterior(i, GetPlayerInterior(playerid));
        SetPlayerVirtualWorld(i, GetPlayerVirtualWorld(playerid));
    }
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(clickedid == TDMoneyHauling[0])
	{
		if(DialogHauling[0] == false) // Kalau False atau tidak dipilih
		{
			DialogHauling[0] = true; // Dialog 0 telah di pilih
			DialogSaya[playerid][0] = true;
			SendClientMessage(playerid, COLOR_ARWIN,"TRUCKING: {FFFFFF}Go to marked checkpoint on your map");
			SetPlayerRaceCheckpoint(playerid, 1, 2791.4016, -2494.5452, 14.2522, 2791.4016, -2494.5452, 14.2522, 10.0);
			TrailerHauling[playerid] = CreateVehicle(435, 2791.4016, -2494.5452, 14.2522, 89.5366, 1, 1, -1);
			SedangHauling[playerid] = 1;
			TextDrawSetString(TDMoneyHauling[0], (DialogHauling[0] == true) ? ("~r~Taken") : ("~g~$350.00"));
			if(DialogHauling[0] == true) TextDrawBoxColor(TDBoxHauling[0], 255);
			foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[0]);
			for (new i; i < 10; i++) {
                if(i < 6) { TextDrawHideForPlayer(playerid, TDHauling[i]); }
				TextDrawHideForPlayer(playerid, TDDistanceHauling[i]);
				TextDrawHideForPlayer(playerid, TDNameHauling[i]);
				TextDrawHideForPlayer(playerid, TDMoneyHauling[i]);
				TextDrawHideForPlayer(playerid, TDBoxHauling[i]);
				CancelSelectTextDraw(playerid);
			}
			DeletePVar(playerid, "UseMissions");
		}
		else SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
	}
	if(clickedid == TDMoneyHauling[1])
	{
		if(DialogHauling[1] == false) // Kalau False atau tidak dipilih
		{
			DialogHauling[1] = true; // Dialog 1 telah di pilih
			DialogSaya[playerid][1] = true;
			SendClientMessage(playerid, COLOR_ARWIN,"TRUCKING: {FFFFFF}Go to marked checkpoint on your map");
			SetPlayerRaceCheckpoint(playerid, 1, 2784.3132, -2456.6299, 14.2415, 2784.3132, -2456.6299, 14.2415, 10.0);
			TrailerHauling[playerid] = CreateVehicle(591, 2784.3132, -2456.6299, 14.2415, 89.4938, 1, 1, -1);
			SedangHauling[playerid] = 3;
			TextDrawSetString(TDMoneyHauling[1], (DialogHauling[1] == true) ? ("~r~Taken") : ("~g~$300.00"));
			if(DialogHauling[1] == true) TextDrawBoxColor(TDBoxHauling[1], 255);
			foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[1]);
			for (new i; i < 10; i++) {
                if(i < 6) { TextDrawHideForPlayer(playerid, TDHauling[i]); }
				TextDrawHideForPlayer(playerid, TDDistanceHauling[i]);
				TextDrawHideForPlayer(playerid, TDNameHauling[i]);
				TextDrawHideForPlayer(playerid, TDMoneyHauling[i]);
				TextDrawHideForPlayer(playerid, TDBoxHauling[i]);
				CancelSelectTextDraw(playerid);
			}
			DeletePVar(playerid, "UseMissions");
		}
		else
			SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
	}
	if(clickedid == TDMoneyHauling[2])
	{
		if(DialogHauling[2] == false) // Kalau False atau tidak dipilih
		{
			DialogHauling[2] = true; // Dialog 2 telah di pilih
			DialogSaya[playerid][3] = true;
			SendClientMessage(playerid, COLOR_ARWIN,"TRUCKING: {FFFFFF}Go to marked checkpoint on your map");
			SetPlayerRaceCheckpoint(playerid, 1,-1963.0142, -2436.3079, 31.2311, -1963.0142, -2436.3079, 31.2311, 10.0);
			TrailerHauling[playerid] = CreateVehicle(450, -1963.0142, -2436.3079, 31.2311, 226.1548, 1, 1, -1);
			SedangHauling[playerid] = 5;
			TextDrawSetString(TDMoneyHauling[2], (DialogHauling[2] == true) ? ("~r~Taken") : ("~g~$250.00"));
			if(DialogHauling[2] == true) TextDrawBoxColor(TDBoxHauling[2], 255);
			foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[2]);
			for (new i; i < 10; i++) {
                if(i < 6) { TextDrawHideForPlayer(playerid, TDHauling[i]); }
				TextDrawHideForPlayer(playerid, TDDistanceHauling[i]);
				TextDrawHideForPlayer(playerid, TDNameHauling[i]);
				TextDrawHideForPlayer(playerid, TDMoneyHauling[i]);
				TextDrawHideForPlayer(playerid, TDBoxHauling[i]);
				CancelSelectTextDraw(playerid);
			}
			DeletePVar(playerid, "UseMissions");
		}
		else
			SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
	}
	if(clickedid == TDMoneyHauling[3])
	{
		if(DialogHauling[3] == false) // Kalau False atau tidak dipilih
		{
			DialogHauling[3] = true; // Dialog 0 telah di pilih
			DialogSaya[playerid][3] = true;
			SendClientMessage(playerid, COLOR_ARWIN,"TRUCKING: {FFFFFF}Go to marked checkpoint on your map");
			SetPlayerRaceCheckpoint(playerid, 1, -1966.5603, -2439.9380, 31.2306, -1966.5603, -2439.9380, 31.2306, 10.0);
			TrailerHauling[playerid] = CreateVehicle(450, -1966.5603, -2439.9380, 31.2306, 225.5799, 1, 1, -1);
			SedangHauling[playerid] = 7;
			TextDrawSetString(TDMoneyHauling[3], (DialogHauling[3] == true) ? ("~r~Taken") : ("~g~$270.00"));
			if(DialogHauling[3] == true) TextDrawBoxColor(TDBoxHauling[3], 255);
			foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[3]);
			for (new i; i < 10; i++) {
                if(i < 6) { TextDrawHideForPlayer(playerid, TDHauling[i]); }
				TextDrawHideForPlayer(playerid, TDDistanceHauling[i]);
				TextDrawHideForPlayer(playerid, TDNameHauling[i]);
				TextDrawHideForPlayer(playerid, TDMoneyHauling[i]);
				TextDrawHideForPlayer(playerid, TDBoxHauling[i]);
				CancelSelectTextDraw(playerid);
			}
			DeletePVar(playerid, "UseMissions");
		}
		else
			SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
	}
	if(clickedid == TDMoneyHauling[4])
	{
		if(DialogHauling[4] == false) // Kalau False atau tidak dipilih
		{
			DialogHauling[4] = true; // Dialog 1 telah di pilih
			DialogSaya[playerid][4] = true;
			SendClientMessage(playerid, COLOR_ARWIN,"TRUCKING: {FFFFFF}Go to marked checkpoint on your map");
			SetPlayerRaceCheckpoint(playerid, 1, -1863.1541, -1720.5603, 22.3558, -1863.1541, -1720.5603, 22.3558, 10.0);
			TrailerHauling[playerid] = CreateVehicle(450, -1863.1541, -1720.5603, 22.3558, 122.1463, 1, 1, -1);
			SedangHauling[playerid] = 9;
			TextDrawSetString(TDMoneyHauling[4], (DialogHauling[4] == true) ? ("~r~Taken") : ("~g~$399.00"));
			if(DialogHauling[4] == true) TextDrawBoxColor(TDBoxHauling[4], 255);
			foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[4]);
			for (new i; i < 10; i++) {
                if(i < 6) { TextDrawHideForPlayer(playerid, TDHauling[i]); }
				TextDrawHideForPlayer(playerid, TDDistanceHauling[i]);
				TextDrawHideForPlayer(playerid, TDNameHauling[i]);
				TextDrawHideForPlayer(playerid, TDMoneyHauling[i]);
				TextDrawHideForPlayer(playerid, TDBoxHauling[i]);
				CancelSelectTextDraw(playerid);
			}
			DeletePVar(playerid, "UseMissions");
		}
		else
			SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
	}
	if(clickedid == TDMoneyHauling[5])
	{
		if(DialogHauling[5] == false) // Kalau False atau tidak dipilih
		{
			DialogHauling[5] = true; // Dialog 2 telah di pilih
			DialogSaya[playerid][5] = true;
			SendClientMessage(playerid, COLOR_ARWIN,"TRUCKING: {FFFFFF}Go to marked checkpoint on your map");
			SetPlayerRaceCheckpoint(playerid, 1, -1855.7255, -1726.0389, 22.3566, -1855.7255, -1726.0389, 22.3566, 10.0);
			TrailerHauling[playerid] = CreateVehicle(450, -1855.7255, -1726.0389, 22.3566, 124.4187, 1, 1, -1);
			SedangHauling[playerid] = 11;
			TextDrawSetString(TDMoneyHauling[5], (DialogHauling[5] == true) ? ("~r~Taken") : ("~g~$200.00"));
			if(DialogHauling[5] == true) TextDrawBoxColor(TDBoxHauling[5], 255);
			foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[5]);
			for (new i; i < 10; i++) {
                if(i < 6) { TextDrawHideForPlayer(playerid, TDHauling[i]); }
				TextDrawHideForPlayer(playerid, TDDistanceHauling[i]);
				TextDrawHideForPlayer(playerid, TDNameHauling[i]);
				TextDrawHideForPlayer(playerid, TDMoneyHauling[i]);
				TextDrawHideForPlayer(playerid, TDBoxHauling[i]);
				CancelSelectTextDraw(playerid);
			}
			DeletePVar(playerid, "UseMissions");
		}
		else
			SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
	}
	if(clickedid == TDMoneyHauling[6])
	{
		if(DialogHauling[6] == false) // Kalau False atau tidak dipilih
		{
			DialogHauling[6] = true; // Dialog 0 telah di pilih
			DialogSaya[playerid][6] = true;
			SendClientMessage(playerid, COLOR_ARWIN,"TRUCKING: {FFFFFF}Go to marked checkpoint on your map");
			SetPlayerRaceCheckpoint(playerid, 1, -1053.6145, -658.6473, 32.6319, -1053.6145, -658.6473, 32.6319, 10.0);
			TrailerHauling[playerid] = CreateVehicle(584, -1053.6145, -658.6473, 32.6319, 260.6392, 1, 1, -1);
			SedangHauling[playerid] = 13;
			TextDrawSetString(TDMoneyHauling[6], (DialogHauling[6] == true) ? ("~r~Taken") : ("~g~$310.00"));
			if(DialogHauling[6] == true) TextDrawBoxColor(TDBoxHauling[6], 255);
			foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[6]);
			for (new i; i < 10; i++) {
                if(i < 6) { TextDrawHideForPlayer(playerid, TDHauling[i]); }
				TextDrawHideForPlayer(playerid, TDDistanceHauling[i]);
				TextDrawHideForPlayer(playerid, TDNameHauling[i]);
				TextDrawHideForPlayer(playerid, TDMoneyHauling[i]);
				TextDrawHideForPlayer(playerid, TDBoxHauling[i]);
				CancelSelectTextDraw(playerid);
			}
			DeletePVar(playerid, "UseMissions");
		}
		else
			SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
	}
	if(clickedid == TDMoneyHauling[7])
	{
		if(DialogHauling[7] == false) // Kalau False atau tidak dipilih
		{
			DialogHauling[7] = true; // Dialog 1 telah di pilih
			DialogSaya[playerid][7] = true;
			SendClientMessage(playerid, COLOR_ARWIN,"TRUCKING: {FFFFFF}Go to marked checkpoint on your map");
			SetPlayerRaceCheckpoint(playerid, 1, -459.3511, -48.3457, 60.5507, -459.3511, -48.3457, 60.5507, 10.0);
			TrailerHauling[playerid] = CreateVehicle(450, -459.3511, -48.3457, 60.5507, 182.7280, 1, 1, -1);
			SedangHauling[playerid] = 15;
			TextDrawSetString(TDMoneyHauling[7], (DialogHauling[7] == true) ? ("~r~Taken") : ("~g~$333.00"));
			if(DialogHauling[7] == true) TextDrawBoxColor(TDBoxHauling[7], 255);
			foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[7]);
			for (new i; i < 10; i++) {
                if(i < 6) { TextDrawHideForPlayer(playerid, TDHauling[i]); }
				TextDrawHideForPlayer(playerid, TDDistanceHauling[i]);
				TextDrawHideForPlayer(playerid, TDNameHauling[i]);
				TextDrawHideForPlayer(playerid, TDMoneyHauling[i]);
				TextDrawHideForPlayer(playerid, TDBoxHauling[i]);
				CancelSelectTextDraw(playerid);
			}
			DeletePVar(playerid, "UseMissions");
		}
		else
			SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
	}
	if(clickedid == TDMoneyHauling[8])
	{
		if(DialogHauling[8] == false) // Kalau False atau tidak dipilih
		{
			DialogHauling[8] = true; // Dialog 2 telah di pilih
			DialogSaya[playerid][8] = true;
			SendClientMessage(playerid, COLOR_ARWIN,"TRUCKING: {FFFFFF}Go to marked checkpoint on your map");
			SetPlayerRaceCheckpoint(playerid, 1, 847.0450, 921.0422, 13.9579, 847.0450, 921.0422, 13.9579, 10.0);
			TrailerHauling[playerid] = CreateVehicle(450, 847.0450, 921.0422, 13.9579, 201.2555, 1, 1, -1);
			SedangHauling[playerid] = 17;
			TextDrawSetString(TDMoneyHauling[8], (DialogHauling[8] == true) ? ("~r~Taken") : ("~g~$290.00"));
			if(DialogHauling[8] == true) TextDrawBoxColor(TDBoxHauling[8], 255);
			foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[8]);
			for (new i; i < 10; i++) {
                if(i < 6) { TextDrawHideForPlayer(playerid, TDHauling[i]); }
				TextDrawHideForPlayer(playerid, TDDistanceHauling[i]);
				TextDrawHideForPlayer(playerid, TDNameHauling[i]);
				TextDrawHideForPlayer(playerid, TDMoneyHauling[i]);
				TextDrawHideForPlayer(playerid, TDBoxHauling[i]);
				CancelSelectTextDraw(playerid);
			}
			DeletePVar(playerid, "UseMissions");
		}
		else
			SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
	}
	if(clickedid == TDMoneyHauling[9])
	{
		if(DialogHauling[9] == false) // Kalau False atau tidak dipilih
		{
			DialogHauling[9] = true; // Dialog 2 telah di pilih
			DialogSaya[playerid][9] = true;
			SendClientMessage(playerid, COLOR_ARWIN,"TRUCKING: {FFFFFF}Go to marked checkpoint on your map");
			SetPlayerRaceCheckpoint(playerid, 1, 249.6713, 1395.7150, 11.1923, 249.6713, 1395.7150, 11.1923, 10.0);
			TrailerHauling[playerid] = CreateVehicle(584, 249.6713, 1395.7150, 11.1923, 269.0699, 1, 1, -1);
			SedangHauling[playerid] = 19;
			TextDrawSetString(TDMoneyHauling[9], (DialogHauling[9] == true) ? ("~r~Taken") : ("~g~$255.00"));
			if(DialogHauling[9] == true) TextDrawBoxColor(TDBoxHauling[9], 255);
			foreach(new player : Player) if(GetPVarInt(player, "UseMissions") == 1) TextDrawShowForPlayer(player, TDBoxHauling[9]);
			for (new i; i < 10; i++) {
                if(i < 6) { TextDrawHideForPlayer(playerid, TDHauling[i]); }
				TextDrawHideForPlayer(playerid, TDDistanceHauling[i]);
				TextDrawHideForPlayer(playerid, TDNameHauling[i]);
				TextDrawHideForPlayer(playerid, TDMoneyHauling[i]);
				TextDrawHideForPlayer(playerid, TDBoxHauling[i]);
				CancelSelectTextDraw(playerid);
			}
			DeletePVar(playerid, "UseMissions");
		}
		else
			SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
	}
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	InventoryClickTextDraw(playerid, playertextid);
    return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{	
	if(CourierJob[playerid] && !IsACourierVeh(vehicleid)) {
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerPos(playerid, x, y, z);
		Error(playerid, "Anda tidak bisa menaiki kendaraan lain!");
	}
	if(KerjaBus[playerid] > 0 && !IsABusABVeh(vehicleid)) {
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerPos(playerid, x, y, z);
		Error(playerid, "Anda tidak bisa menaiki kendaraan lain!");
	}
	if(KerjaBusCD[playerid] > 0 && !IsABusCDVeh(vehicleid)) {
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerPos(playerid, x, y, z);
		Error(playerid, "Anda tidak bisa menaiki kendaraan lain!");
	}
	new Float:health;
	GetVehicleHealth(GetPlayerVehicleID(playerid), health);
	VehicleHealthSecurityData[GetPlayerVehicleID(playerid)] = health;
	VehicleHealthSecurity[GetPlayerVehicleID(playerid)] = true;
	SetPVarInt(playerid, "LastVehicleID", vehicleid);
	SetPVarInt(playerid, "CarID", vehicleid);
	pData[playerid][pLastCar] = vehicleid;
	new engine, lights, alarm, doors, bonnet, boot, objective;
	
	if(!ispassenger)
	{
		if(IsABike(vehicleid) || GetVehicleModel(vehicleid) == 424)
		{
			foreach(new vehid : PVehicles) 
			{
				if(pvData[vehid][cVeh] == vehicleid){
					if(pvData[vehid][cLocked] == 1)
					{
						new Float:x, Float:y, Float:z;
						GetPlayerPos(playerid, x, y, z);
						SetPlayerPos(playerid, x, y, z);
						Error(playerid, "This bike is locked by owner.");
						return 1;
					}
				}
			}
		}
		if(GetVehicleModel(vehicleid) == 548 || GetVehicleModel(vehicleid) == 417 || GetVehicleModel(vehicleid) == 487 || GetVehicleModel(vehicleid) == 488 ||
		GetVehicleModel(vehicleid) == 497 || GetVehicleModel(vehicleid) == 563 || GetVehicleModel(vehicleid) == 469)
		{
			if(pData[playerid][pLevel] < 5)
			{
				new Float:x, Float:y, Float:z;
				GetPlayerPos(playerid, x, y, z);
				SetPlayerPos(playerid, x, y, z);
				Error(playerid, "Your level is not sufficient to ride this vehicle!");
				return 1;
			}
		}
		if(IsAForkliftVeh(vehicleid))
		{
			Dialog_Show(playerid, StartForklift, DIALOG_STYLE_MSGBOX, "Side Job - Forklift", "Anda akan bekerja sebagai forklift?", "Start Job", "Close");
			return 1;
		}
		if(IsACourierVeh(vehicleid) && CourierJob[playerid])
		{
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, 0); // ONLY the engine param was changed to VEHICLE_PARAMS_ON (1)
			for(new i = 0; i < 2; i++) 
			{
				TextDrawShowForPlayer(playerid, PlayerCrateTD);
				PlayerTextDrawShow(playerid, PlayerCrate[playerid][i]);
			}
			new String2[212];
			format(String2,sizeof(String2),"Deliveries~n~%d/10", CourierCount[playerid]);
			PlayerTextDrawSetString(playerid, PlayerCrate[playerid][1], String2);
			return 1;
		}

	}
	return 1;
}

public OnPlayerUpdate(playerid)
{
    if(!pData[playerid][IsLoggedIn])
        return 0;

	if (IsValidVehicle(GetPlayerVehicleID(playerid)))
	{
		DisableVehicleSpeedCap(GetPlayerVehicleID(playerid));
	}

    new s_Keys, s_UpDown, s_LeftRight;    
    GetPlayerKeys( playerid, s_Keys, s_UpDown, s_LeftRight );

	if(GetPVarInt(playerid,"TagNama") == 0)
	{
		foreach(new ii : Player) ShowPlayerNameTagForPlayer(playerid, ii, false);
	}
	
    if(pData[playerid][pMaskOn] == 0)
    {
    	for(new i = 0; i < MAX_PLAYERS; i++)
    	{
    		ShowPlayerNameTagForPlayer(i, playerid, true);
    	}
    }
	if(pData[playerid][pMaskOn] == 1)
    {
    	for(new i = 0; i < MAX_PLAYERS; i++)
    	{
    		ShowPlayerNameTagForPlayer(i, playerid, false);
    	}
    }

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsEngineVehicle(GetPlayerVehicleID(playerid)))
    {
        new id = -1;
        new vehicleid = GetPlayerVehicleID(playerid);

        if((id = Speed_Nearest(playerid)) != -1 && GetVehicleSpeed(vehicleid) > SpeedData[id][speedLimit] && !pData[playerid][pSpeedTime])
        {
            if(!IsFactionVeh(vehicleid) || !IsABoat(vehicleid) || !IsAPlane(vehicleid) || !IsAHelicopter(vehicleid))
            {
                new Float:x, Float:y, Float:z, direction[12], plate[24], vehname[32];
                pData[playerid][pSpeedTime] = 5;

                GetPlayerPos(playerid, x, y, z);
                GetVehicleDirection(vehicleid, direction);
                GetVehicleNumberPlate(vehicleid, plate);
                GetVehicleNameByVehicle(vehicleid, vehname);

                SendSpeedCamMessageEx(1, COLOR_BLUE, "SPEEDTRAP:"YELLOW_E" Vehicle: [%s] Plate: [%s] Speed: [%.0f/%.0f] Area: [%s] Heading: [%s]", vehname, plate, GetVehicleSpeed(vehicleid), SpeedData[id][speedLimit], GetLocation(x, y, z), direction);

                Speed_UpdateSuspect(id, vehicleid);
            }
        }
    }
    return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	foreach(new vehicle : PVehicles) if(pvData[vehicle][cVeh] == vehicleid) {
        GetVehicleDamageStatus(pvData[vehicle][cVeh], pvData[vehicle][cDamage0], pvData[vehicle][cDamage1], pvData[vehicle][cDamage2], pvData[vehicle][cDamage3]);
        GetVehicleHealth(pvData[vehicle][cVeh], pvData[vehicle][cHealth]);
        pvData[vehicle][cFuel] = GetVehicleFuel(pvData[vehicle][cVeh]);
        GetVehiclePos(pvData[vehicle][cVeh], pvData[vehicle][cPosX], pvData[vehicle][cPosY], pvData[vehicle][cPosZ]);
        GetVehicleZAngle(pvData[vehicle][cVeh],pvData[vehicle][cPosA]);
    }
	return 1;
}	

public OnVehicleDeath(vehicleid, killerid)
{
	foreach(new ii : PVehicles)
	{
		if(pvData[ii][cVeh] == vehicleid && pvData[ii][cRent] == 0 && pvData[ii][cVehicleGarage] == -1)
		{
			pvData[ii][vDestroyed] = gettime() + 15;
			new S3MP4K[212];
			foreach(new pid : Player) 
			{
				if (pvData[ii][cOwner] == pData[pid][pID])
				{
					if(killerid != INVALID_PLAYER_ID) format(S3MP4K, sizeof(S3MP4K), "VEHICLE: "WHITE_E"Your "AQUA_E"%s "WHITE_E"has been destroyed by "YELLOW_E"%s", GetVehicleName(vehicleid), pData[killerid][pName]);
					else format(S3MP4K, sizeof(S3MP4K), "VEHICLE: "WHITE_E"Your "AQUA_E"%s "WHITE_E"has been destroyed", GetVehicleName(vehicleid));
					SendClientMessageEx(pid, COLOR_ARWIN, S3MP4K);
				}	
			}			
		}
	}
	return 1;
}

public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
{
    if(newstate)
    {
        ToggleVehicleLights(vehicleid, 1);
		pvData[vehicleid][vEmergencyLights] = 0;

		pvData[vehicleid][vELM] = true;
        pvData[vehicleid][vEmergencyLights] = 0;
		ToggleVehicleLights(vehicleid, pvData[vehicleid][vLights]);

		new panels, doors, lights, tires;
		GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
		UpdateVehicleDamageStatus(vehicleid, panels, doors, 0, tires);
		pvData[vehicleid][vELM] = false;
    }
    return 1;
}

public OnVehicleSpawn(vehicleid)
{
	new S3MP4K[212];
	foreach(new i : VehicleData) if(VehicleData[i][Vehicle] == vehicleid) {
		DestroyVehicle(VehicleData[i][Vehicle]);
		VehicleData[i][Vehicle] = INVALID_VEHICLE_ID;
		format(VehicleData[i][VehicleOwner], 52, "-");
		if(VehicleData[i][SpawnType] == 0) VehicleRespawn(i); 
	}
	foreach(new ii : PVehicles)
	{
		if(pvData[ii][cVeh] == vehicleid && pvData[ii][cRent] == 0 && pvData[ii][cVehicleGarage] == -1)
		{
			if(pvData[ii][vDestroyed] > gettime())
			{
				if(pvData[ii][cInsu] > 0)
				{
					pvData[ii][cInsu]--;
					pvData[ii][cClaim] = 1;
					pvData[ii][cClaimTime] = gettime() + (1 * 3600);
					foreach(new pid : Player) 
					{
						if (pvData[ii][cOwner] == pData[pid][pID])
						{
							format(S3MP4K, sizeof(S3MP4K), "INSURANCE: "WHITE_E"Your %s has been destroyed and will be respawned at Insurance Agency with "YELLOW_E"'/claiminsurance'", GetVehicleName(vehicleid));
							SendClientMessageEx(pid, COLOR_ARWIN, S3MP4K);
						}	
					}
					for(new f = 0 ; f < MAX_MODS; f++) RemoveVehicleComponent(pvData[ii][cVeh], GetVehicleComponentInSlot(pvData[ii][cVeh], f));
					for(new id = 0 ; id < MAX_VEHICLE_OBJECT; id++) Vehicle_ObjectDelete(pvData[ii][cVeh], id);
					pvData[ii][pvBodyUpgrade] = 0;
					pvData[ii][cMesinUpgrade] = 0;
					Vehicle_ObjectDestroy(pvData[ii][cVeh]);
					for(new id = 0; id < 5; id++) if(IsValidDynamicObject(ObjectVehicle[pvData[ii][cVeh]][id])) DestroyDynamicObject(ObjectVehicle[pvData[ii][cVeh]][id]);
					if(IsValidDynamicObject(ObjectVehicle[pvData[ii][cVeh]][0])) DestroyDynamicObject(ObjectVehicle[pvData[ii][cVeh]][0]);
					if(IsValidDynamicObject(ObjectVehicle[pvData[ii][cVeh]][1])) DestroyDynamicObject(ObjectVehicle[pvData[ii][cVeh]][1]);
					if(IsValidDynamicObject(ObjectVehicle[pvData[ii][cVeh]][2])) DestroyDynamicObject(ObjectVehicle[pvData[ii][cVeh]][2]);
					if(IsValidVehicle(pvData[ii][cVeh])) DestroyVehicle(pvData[ii][cVeh]);
					pvData[ii][cVeh] = INVALID_VEHICLE_ID;
				}
				else
				{
					foreach(new pid : Player) if (pvData[ii][cOwner] == pData[pid][pID])
					{
						Vehicle_ObjectDestroy(pvData[ii][cVeh]);
						for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++) Vehicle_ObjectDelete(vehicleid, slot);
						for(new id = 0; id < 5; id++) if(IsValidDynamicObject(ObjectVehicle[pvData[ii][cVeh]][id])) DestroyDynamicObject(ObjectVehicle[pvData[ii][cVeh]][id]);
						new query[128];
						mysql_format(g_SQL, query, sizeof(query), "DELETE FROM vehicle WHERE id = '%d'", pvData[pid][cID]);
						mysql_tquery(g_SQL, query);
						if(IsValidVehicle(pvData[ii][cVeh])) DestroyVehicle(pvData[ii][cVeh]);

						pvData[ii][cVeh] = INVALID_VEHICLE_ID;
						format(S3MP4K, sizeof(S3MP4K), "INSURANCE: Kendaraan anda hancur dan tidak memiliki insuransi");
						SendClientMessageEx(pid, COLOR_ARWIN, S3MP4K);
						Iter_SafeRemove(PVehicles, ii, ii);
					}
				}
			}
		}
	}
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	new panel, doors, lights, tires, Float: HP;
	foreach(new vehid : PVehicles)
	{
		if(vehicleid == pvData[vehid][cVeh])
		{
			if(pvData[vehid][pvBodyUpgrade] == 1)
			{
				GetVehicleHealth(pvData[vehid][cVeh], HP);
				GetVehicleDamageStatus(pvData[vehid][cVeh], panel, doors, lights, tires);
				if(HP > 1000) UpdateVehicleDamageStatus(pvData[vehid][cVeh], 0, 0, 0, 0);
			}
			else
			{
				GetVehicleHealth(pvData[vehid][cVeh], HP);
				GetVehicleDamageStatus(pvData[vehid][cVeh], panel, doors, lights, tires);
				if(HP < 1000)
				UpdateVehicleDamageStatus(pvData[vehid][cVeh], panel, doors, lights, tires);
				pvData[vehid][cHealth] = HP;
			}
		}
	}
	if(IsABusABVeh(GetPlayerVehicleID(playerid))) SendCustomMessage(playerid, "SIDEJOB", "{ffff00}WARNING!{ffffff}, please avoid damage or your job will be ended!");
	if(IsABusCDVeh(GetPlayerVehicleID(playerid))) SendCustomMessage(playerid, "SIDEJOB", "{ffff00}WARNING!{ffffff}, please avoid damage or your job will be ended!");
	if(IsASweeperVeh(GetPlayerVehicleID(playerid))) SendCustomMessage(playerid, "SIDEJOB", "{ffff00}WARNING!{ffffff}, please avoid damage or your job will be ended!");
	if(IsAForkliftVeh(GetPlayerVehicleID(playerid))) SendCustomMessage(playerid, "SIDEJOB", "{ffff00}WARNING!{ffffff}, please avoid damage or your job will be ended!");
	if(IsVehicleTrashmaster(GetPlayerVehicleID(playerid))) SendCustomMessage(playerid, "SIDEJOB", "{ffff00}WARNING!{ffffff}, please avoid damage or your job will be ended!");
	if(IsACourierVeh(GetPlayerVehicleID(playerid))) SendCustomMessage(playerid, "SIDEJOB", "{ffff00}WARNING!{ffffff}, please avoid damage or your job will be ended!");
	return 1;
}

public OnTrailerUnhooked(playerid,vehicleid,trailerid)
{
	SendCustomMessage(playerid, "TRUCKING","Your trailer is off your vehicle please reattach it");
	return 1;
}

public OnTrailerHooked(playerid,vehicleid,trailerid)
{
	if ((pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4) && SedangHauling[playerid] == 3) 
	{
		if (TrailerHauling[playerid] == trailerid) 
		{
			DisablePlayerRaceCheckpoint(playerid);
			SedangHauling[playerid] = 4;
			SendCustomMessage(playerid, "TRUCKING","Attach the trailer to your vehicle to order Location "YELLOW_E"%s", GetLocation(-576.2687, 2569.0842, 53.5156));
			SetPlayerRaceCheckpoint(playerid, 1, -576.2687, 2569.0842, 53.5156, 576.2687, 2569.0842, 53.5156, 10.0);
		}
		return 1;
	}
	else if ((pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4) && SedangHauling[playerid] == 1) 
	{
		if (TrailerHauling[playerid] == trailerid) 
		{
			DisablePlayerRaceCheckpoint(playerid);
			SedangHauling[playerid] = 2;
			SendCustomMessage(playerid, "TRUCKING","Attach the trailer to your vehicle to order Location "YELLOW_E"%s", GetLocation(-2471.2942, 783.0248, 35.1719));
			SetPlayerRaceCheckpoint(playerid, 1, -2471.2942, 783.0248, 35.1719, -2471.2942, 783.0248, 35.1719, 10.0);
		}
		return 1;
	}
	else if ((pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4) && SedangHauling[playerid] == 5) 
	{
		if (TrailerHauling[playerid] == trailerid) 
		{
			DisablePlayerRaceCheckpoint(playerid);
			SedangHauling[playerid] = 6;
			SendCustomMessage(playerid, "TRUCKING","Attach the trailer to your vehicle to order Location "YELLOW_E"%s", GetLocation(1424.8624, 2333.4939, 10.8203));
			SetPlayerRaceCheckpoint(playerid, 1, 1424.8624, 2333.4939, 10.8203, 1424.8624, 2333.4939, 10.8203, 10.0);
		}
		return 1;
	}
	else if ((pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4) && SedangHauling[playerid] == 7) 
	{
		if (TrailerHauling[playerid] == trailerid) 
		{
			DisablePlayerRaceCheckpoint(playerid);
			SedangHauling[playerid] = 8;
			SendCustomMessage(playerid, "TRUCKING","Attach the trailer to your vehicle to order Location "YELLOW_E"%s", GetLocation(-576.2687, 2569.0842, 53.5156));
			SetPlayerRaceCheckpoint(playerid, 1, -576.2687, 2569.0842, 53.5156, 576.2687, 2569.0842, 53.5156, 10.0);
		}
		return 1;
	}
	else if ((pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4) && SedangHauling[playerid] == 9) 
	{
		if (TrailerHauling[playerid] == trailerid) 
		{
			DisablePlayerRaceCheckpoint(playerid);
			SedangHauling[playerid] = 10;
			SendCustomMessage(playerid, "TRUCKING","Attach the trailer to your vehicle to order Location "YELLOW_E"%s", GetLocation(-576.2687, 2569.0842, 53.5156));
			SetPlayerRaceCheckpoint(playerid, 1, -576.2687, 2569.0842, 53.5156, 576.2687, 2569.0842, 53.5156, 10.0);
		}
		return 1;
	}
	else if ((pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4) && SedangHauling[playerid] == 11) 
	{
		if (TrailerHauling[playerid] == trailerid) 
		{
			DisablePlayerRaceCheckpoint(playerid);
			SedangHauling[playerid] = 12;
			SendCustomMessage(playerid, "TRUCKING","Attach the trailer to your vehicle to order Location "YELLOW_E"%s", GetLocation(-576.2687, 2569.0842, 53.5156));
			SetPlayerRaceCheckpoint(playerid, 1, -576.2687, 2569.0842, 53.5156, 576.2687, 2569.0842, 53.5156, 10.0);
		}
		return 1;
	}
	else if ((pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4) && SedangHauling[playerid] == 13) 
	{
		if (TrailerHauling[playerid] == trailerid) 
		{
			DisablePlayerRaceCheckpoint(playerid);
			SedangHauling[playerid] = 14;
			SendCustomMessage(playerid, "TRUCKING","Attach the trailer to your vehicle to order Location "YELLOW_E"%s", GetLocation(-576.2687, 2569.0842, 53.5156));
			SetPlayerRaceCheckpoint(playerid, 1, -576.2687, 2569.0842, 53.5156, 576.2687, 2569.0842, 53.5156, 10.0);
		}
		return 1;
	}
	else if ((pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4) && SedangHauling[playerid] == 15) 
	{
		if (TrailerHauling[playerid] == trailerid) 
		{
			DisablePlayerRaceCheckpoint(playerid);
			SedangHauling[playerid] = 16;
			SendCustomMessage(playerid, "TRUCKING","Attach the trailer to your vehicle to order Location "YELLOW_E"%s", GetLocation(-576.2687, 2569.0842, 53.5156));
			SetPlayerRaceCheckpoint(playerid, 1, -576.2687, 2569.0842, 53.5156, 576.2687, 2569.0842, 53.5156, 10.0);
		}
		return 1;
	}
	else if ((pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4) && SedangHauling[playerid] == 17) 
	{
		if (TrailerHauling[playerid] == trailerid) 
		{
			DisablePlayerRaceCheckpoint(playerid);
			SedangHauling[playerid] = 18;
			SendCustomMessage(playerid, "TRUCKING","Attach the trailer to your vehicle to order Location "YELLOW_E"%s", GetLocation(-576.2687, 2569.0842, 53.5156));
			SetPlayerRaceCheckpoint(playerid, 1, -576.2687, 2569.0842, 53.5156, 576.2687, 2569.0842, 53.5156, 10.0);
		}
		return 1;
	}
	else if ((pData[playerid][pJob] == 4 || pData[playerid][pJob2] == 4) && SedangHauling[playerid] == 19) 
	{
		if (TrailerHauling[playerid] == trailerid) 
		{
			DisablePlayerRaceCheckpoint(playerid);
			SedangHauling[playerid] = 20;
			SendCustomMessage(playerid, "TRUCKING","Attach the trailer to your vehicle to order Location "YELLOW_E"%s", GetLocation(-576.2687, 2569.0842, 53.5156));
			SetPlayerRaceCheckpoint(playerid, 1, -576.2687, 2569.0842, 53.5156, 576.2687, 2569.0842, 53.5156, 10.0);
		}
		return 1;
	}
  	return 1;
}

GetStructureNameByModel(model) {
    new name[32];

    for (new i = 0; i < sizeof(g_aHouseStructure); i ++) if (g_aHouseStructure[i][e_StructureModel] == model) {
        strcat(name, g_aHouseStructure[i][e_StructureName]);
        break;
    }
    if(isnull(name)) format(name, sizeof(name), "Model ID %d", model);
    return name;
}

// CMD:kontol(playerid, params[])
// {
// 	new Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz;
// 	new Float:zx, Float:zy, Float:zz, Float:zrx, Float:zry, Float:zrz;
// 	if(!pData[playerid][pAdminDuty]) return PermissionError(playerid);
// 	if(!sscanf(params, "ffffff", x, y, z, rx, ry, rz))
// 	{
// 		GetDynamicObjectPos(ObjectKontol[0], zx, zy, zz);
// 		GetDynamicObjectRot(ObjectKontol[0], zrx, zry, zrz);
// 		zx += x;
// 		zy += y;
// 		zz += z;
// 		zrx += rx;
// 		zry += ry;
// 		zrz += rz;
// 		SetDynamicObjectPos(ObjectKontol[0], zx, zy, zz);
// 		SetDynamicObjectRot(ObjectKontol[0], zrx, zry, zrz);
// 	}
// 	return 1;
// }


// CMD:tempek(playerid)
// {
// 	SetPVarInt(playerid, "TestLoad", 1);
// 	pData[playerid][pActivityTime] = 0;
//     PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Test Loading Bar");
//     for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
// }

// ptask Loadbar[200](playerid) {
// 	if(GetPVarInt(playerid, "TestLoad") == 1) {
// 		pData[playerid][pActivityTime]++;
// 		SetProgressBar(playerid, pData[playerid][pActivityTime]);
// 		if(pData[playerid][pActivityTime] >= 100)
// 		{
// 			DeletePVar(playerid, "TestLoad");
// 			pData[playerid][pActivityTime] = 0;
// 			HideProgressBar(playerid);
// 			ClearAnimations(playerid);
// 		}
// 	}
// }

// CMD:drunklevel(playerid, params[])
// {
// 	SetVehicleFuel(GetPlayerVehicleID(playerid), strval(params));
// 	return 1;
// }
