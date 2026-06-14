
#define IsPlayerInEvent(%0)	eventJoin[%0]
enum _:E_EVENT_TEAM
{
	TEAM_NONE = 0,
	TEAM_A,
	TEAM_B
}

enum _:E_EVENT_TYPES
{
	TYPE_NONE = 0,
	TYPE_TDM,
	TYPE_DM,
	TYPE_ZOMBIE
}
enum _:E_EVENT
{
	eventMessage[128],
	eventTypes,
	eventCreated,
	eventStart,
	Float:eventHealths,
	Float:eventArmors,
	eventTargets,
	eventBonuses,
	eventSelectTeam,
	eventWinner,
	eventOpen,
	eventWorld,
	eventInt,
	eventWeapons[3],
	eventAmmo[3],
	eventCountdown,

	//DM enum's
	Float:eventSpawnX_DM,
	Float:eventSpawnY_DM,
	Float:eventSpawnZ_DM,

	//Team enum's
	eventSkin[2],
	eventTeamScore[2],
	eventScore[2],
	Float:eventSpawnX[2],
	Float:eventSpawnY[2],
	Float:eventSpawnZ[2],
	Float:eventSpawnA[2],

	//Zombie enum's
	eventHumans,
	eventTimer,
	eventMinutes,
};

new EventData[E_EVENT];
new
	eventJoin[MAX_PLAYERS] = {0, ...},
	eventTeams[MAX_PLAYERS] = {0, ...},
	eventWaitingSpawn[MAX_PLAYERS] = {0, ...},
  	eventScore_DM[MAX_PLAYERS] = {0, ...},
  	eventZombieSkin[MAX_PLAYERS],
  	eventZombieCD[MAX_PLAYERS]
;
