#define MAX_DEALERSHIPVEHICLES 10
#define MAX_CARDEALERSHIPS 8
#define DIALOG_CDCHANGETYPE 1339
#define DIALOG_CDEDIT 1329
#define DIALOG_CDTILL 1327
#define DIALOG_CDEDITCARS 1326
#define DIALOG_CDEDITPARK 1322
#define DIALOG_CDNEWVEH 1320
#define DIALOG_CDRADIUS 1319
#define DIALOG_CDNAME 1318
#define DIALOG_CDPRICE 1317
#define DIALOG_CDBUY 1316
#define DIALOG_CDWITHDRAW 1315
#define DIALOG_CDDEPOSIT 1314
#define DIALOG_CDSELL 1313
#define COLOR_REALRED 0xFF0606FF
//DEALER
enum cdInfo
{
	cdID,
    cdOwned,
	cdOwner[MAX_PLAYER_NAME],
	Float:cdEntranceX,
	Float:cdEntranceY,
	Float:cdEntranceZ,
	Float:cdExitX,
	Float:cdExitY,
	Float:cdExitZ,
	cdMessage[128],
	cdTill,
	cdInterior,
	Float: cdRadius,
	cdPrice,
	cdType,
	cdPickupID,
	Text3D:cdTextLabel,
	Text3D:cdVehicleLabel[MAX_DEALERSHIPVEHICLES],
	cdVehicleDBID[MAX_DEALERSHIPVEHICLES],
	cdVehicleModel[MAX_DEALERSHIPVEHICLES],
	cdVehicleCost[MAX_DEALERSHIPVEHICLES],
	cdVehicleId[MAX_DEALERSHIPVEHICLES],
	Float: cdVehicleSpawnX[MAX_DEALERSHIPVEHICLES],
	Float: cdVehicleSpawnY[MAX_DEALERSHIPVEHICLES],
	Float: cdVehicleSpawnZ[MAX_DEALERSHIPVEHICLES],
	Float: cdVehicleSpawnAngle[MAX_DEALERSHIPVEHICLES],
	Float: cdVehicleSpawn[4]
};
new CarDealershipInfo[MAX_CARDEALERSHIPS][cdInfo],
	Iterator: Dealership<MAX_CARDEALERSHIPS>;