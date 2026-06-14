#define MAX_FURNSTORE				10
#define MAX_EMPLOYE					3

#define MAX_FURN_OBJECT				(MAX_FURNSTORE*100)
#define MAX_FURNSTORE_OBJECT		50

new ManageFurnStore[MAX_PLAYERS] = {-1, ...},
	ManageFurnObject[MAX_PLAYERS] = {-1, ...},
	SelectToFired[MAX_PLAYERS][MAX_EMPLOYE],
	ListedFurnObject[MAX_PLAYERS][MAX_FURNSTORE_OBJECT],
	editFurnPosition[MAX_PLAYERS] = {-1, ...};
		
new produceObject[MAX_PLAYERS] = {INVALID_OBJECT_ID, ...},
	bool:startProduce[MAX_PLAYERS],
	productionCount[MAX_PLAYERS],
	productionAdd[MAX_PLAYERS];

new production;

new Float:production_Array[] =
{
	1492.01, 1791.86,
	1491.96, 1786.34,
	1487.19, 1786.48,
	1487.16, 1792.00
};

enum E_FURNSTORE
{
	storeID,
	storeName[32],
	storeOwnerName[MAX_PLAYER_NAME],
	Float:storePos[3],
	Float:storeIntPos[3],
	storeOwner,
	storePrice,
	storeVault,
	storeEmploye[MAX_EMPLOYE],
	storeSeal,
	storeLocked,
	storePickup,
	Text3D:storeLabel,
	storeCP
};

new storeData[MAX_FURNSTORE][E_FURNSTORE],
	Iterator:FurnStore<MAX_FURNSTORE>;


enum E_FURNPROP {
	furnID,
	furnName[32],
	Float:furnPos[3],
	Float:furnRot[3],
	furnPrice,
	furnStock,
	furnModel,
	furnStoreId,
	furnMaterials[MAX_MATERIALS],
	Text3D:furnLabel,
	furnObject
};
new FurnStore[MAX_FURN_OBJECT][E_FURNPROP],
	Iterator:FurnObject<MAX_FURN_OBJECT>;



stock const g_aFurnitureTypes[][] = {
    {"Frames"},
    {"Tables"},
    {"Chairs"},
    {"Beds"},
    {"Cabinets"},
    {"Television Sets"},
    {"Kitchen Appliances"},
    {"Bathroom Appliances"},
    {"Decoration"},
    {"Misc Furniture"}
};
