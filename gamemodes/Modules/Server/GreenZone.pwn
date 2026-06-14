#define MAX_GREENZONE (14)

new 
    GreenZoneArea[MAX_GREENZONE] = {INVALID_STREAMER_ID, ...}, 
	FarmArea[6],
	GangZoneID;

new Float:asgh_Point[] = {
	1142.0, -1384.5, 1193.0, -1284.5 
};
new Float:sapd_Point[] = {
	1532.0, -1723.5, 1583.0, -1595.5 
};
new Float:cityHall_Point[] = {
	1395.0, -1830.5, 1562.0, -1740.5 
};
new Float:sana_Point[] = {
	642.0, -1390.5, 793.0, -1319.5 
};
new unity_Point[] = {
	1696, -1885, 1858, -1820
};

//Citty Prison 
/*
{ "Zone 7", 57.5, -2843.375, 2985.5, 520.625, 0xFF0000FF },
{ "Zone 8", -1022.4998779296875, -334.5, 57.5001220703125, 401.5, 0xFF0000FF },
{ "Zone 10", -147.8541259765625, -917.5, 58.1458740234375, -753.5, 0xFF0000FF },
{ "Zone 11", 941.14599609375, 520.6249084472656, 1354.14599609375, 620.6249084472656, 0xFF0000FF },
{ "Zone 9", -286.8541259765625, -753.5, 58.1458740234375, -334.5, 0xFF0000FF },
*/