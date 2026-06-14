#define MAX_ROUTE 9 + 1 //Yang ke 10 finish

/* Vars */

new
	Float:RacePos[MAX_PLAYERS][MAX_ROUTE][3],//[3] ini array buat x, y, z.
	RaceIndex[MAX_PLAYERS],
	RaceWith[MAX_PLAYERS],
	bool:InRace[MAX_PLAYERS];
