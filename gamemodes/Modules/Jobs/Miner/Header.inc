
#define MAX_ORES 100
#define ORE_RESPAWN 1200

enum    E_ORE
{
	Float: oreX,
	Float: oreY,
	Float: oreZ,
	Float: oreRX,
	Float: oreRY,
	Float: oreRZ,
	// temp
	oreSeconds,
	bool: oreGettingMiner,
	oreObjID,
	oreArea
}

new OreData[MAX_ORES][E_ORE],
	Iterator:Ores<MAX_ORES>;
	
new pTimeMiningOre[MAX_PLAYERS], pMiningOre[MAX_PLAYERS], pTotalCashOre[MAX_PLAYERS];
