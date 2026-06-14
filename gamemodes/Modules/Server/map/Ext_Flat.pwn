RemoveExt_Flat(playerid)
{
	//Idlewood
	RemoveBuildingForPlayer(playerid, 3644, 2070.760, -1586.020, 15.062, 0.250);
	RemoveBuildingForPlayer(playerid, 3645, 2070.760, -1586.020, 15.062, 0.250);
	RemoveBuildingForPlayer(playerid, 3644, 2069.620, -1556.699, 15.062, 0.250);
	RemoveBuildingForPlayer(playerid, 3645, 2069.620, -1556.699, 15.062, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 2086.459, -1594.319, 13.765, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 2086.459, -1599.589, 13.765, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 2083.770, -1602.229, 13.765, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 2078.489, -1602.229, 13.765, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 2063.330, -1602.229, 13.765, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 2058.050, -1602.229, 13.765, 0.250);
	RemoveBuildingForPlayer(playerid, 1524, 2074.179, -1579.150, 14.031, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 2055.270, -1594.229, 13.765, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 2055.270, -1599.500, 13.765, 0.250);
	RemoveBuildingForPlayer(playerid, 1283, 2092.989, -1604.160, 15.601, 0.250);
}

CreateExt_Flat()
{
	//Idlewood
	tmpobjid = CreateDynamicObject(19865, 2055.062500, -1599.583496, 12.546875, 0.000000, -0.000001, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 6487, "councl_law2", "lanlabra1_M", 0x00000000);
	tmpobjid = CreateDynamicObject(19866, 2055.062255, -1599.734863, 12.141864, 0.000000, -0.000001, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19865, 2055.062500, -1594.583984, 12.546875, 0.000000, -0.000004, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 6487, "councl_law2", "lanlabra1_M", 0x00000000);
	tmpobjid = CreateDynamicObject(19449, 2079.843261, -1565.291381, 13.586839, 90.000000, -0.000001, 180.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10031, "chinatown2", "ws_plasterwall2", 0x00000000);
	tmpobjid = CreateDynamicObject(19449, 2079.864257, -1583.831176, 13.586839, 90.000000, 0.000000, -179.999984, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10031, "chinatown2", "ws_plasterwall2", 0x00000000);
	tmpobjid = CreateDynamicObject(3456, 2070.089355, -1574.622680, 15.456839, -0.000001, 0.000007, -179.999984, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19866, 2055.062255, -1594.735351, 12.141864, 0.000000, -0.000004, 0.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19866, 2055.062255, -1591.520385, 12.021874, 90.000000, 0.000000, -0.000004, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19866, 2054.958007, -1602.135986, 12.021874, 90.000000, 0.000000, 89.999992, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19866, 2058.189697, -1602.137207, 12.141864, 0.000000, -0.000001, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19865, 2058.189941, -1602.135986, 12.546875, 0.000000, -0.000001, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 6487, "councl_law2", "lanlabra1_M", 0x00000000);
	tmpobjid = CreateDynamicObject(19866, 2063.178710, -1602.137207, 12.141864, 0.000000, -0.000001, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19865, 2063.164062, -1602.135986, 12.546875, 0.000000, -0.000001, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 6487, "councl_law2", "lanlabra1_M", 0x00000000);
	tmpobjid = CreateDynamicObject(19865, 2068.153076, -1602.135986, 12.546875, 0.000000, -0.000001, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 6487, "councl_law2", "lanlabra1_M", 0x00000000);
	tmpobjid = CreateDynamicObject(19865, 2073.127197, -1602.135986, 12.546875, 0.000000, -0.000001, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 6487, "councl_law2", "lanlabra1_M", 0x00000000);
	tmpobjid = CreateDynamicObject(18662, 2076.710693, -1602.531860, 14.496918, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterialText(tmpobjid, 0, "Idle", 50, "Ariel", 40, 1, 0xFFFFFFFF, 0x00000000, 1);
	tmpobjid = CreateDynamicObject(19865, 2083.135009, -1602.135986, 12.546875, 0.000000, -0.000001, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 6487, "councl_law2", "lanlabra1_M", 0x00000000);
	tmpobjid = CreateDynamicObject(19866, 2068.182617, -1602.137207, 12.141864, 0.000000, -0.000001, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19866, 2073.186523, -1602.137207, 12.141864, 0.000000, -0.000001, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(18662, 2077.931884, -1602.531860, 14.496918, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterialText(tmpobjid, 0, "wood", 50, "Ariel", 40, 1, 0xFFFFFFFF, 0x00000000, 1);
	tmpobjid = CreateDynamicObject(19866, 2083.186523, -1602.137207, 12.141864, 0.000000, -0.000001, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19866, 2085.613281, -1602.135986, 12.021874, 90.000000, 0.000000, 89.999992, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19448, 2082.629638, -1583.880737, 12.391568, 0.000000, 89.999992, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 8486, "ballys02", "Grass_concpath_128HV", 0x00000000);
	tmpobjid = CreateDynamicObject(8132, 2076.618896, -1601.723999, 14.800399, 0.000000, 0.000000, -77.499969, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 2, 18646, "matcolours", "grey-90-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(18662, 2077.395751, -1602.531860, 13.641900, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterialText(tmpobjid, 0, "Flats", 50, "Ariel", 30, 1, 0xFFFFFFFF, 0x00000000, 1);
	tmpobjid = CreateDynamicObject(19448, 2082.629638, -1565.352172, 12.301566, 0.000000, 89.999992, 90.000000, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 8486, "ballys02", "Grass_concpath_128HV", 0x00000000);
	tmpobjid = CreateDynamicObject(19866, 2086.269287, -1599.554687, 12.141863, 0.000000, -0.000000, -179.999984, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	tmpobjid = CreateDynamicObject(19865, 2086.262451, -1599.568481, 12.546875, 0.000000, -0.000001, -179.999984, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 6487, "councl_law2", "lanlabra1_M", 0x00000000);
	tmpobjid = CreateDynamicObject(19866, 2086.283447, -1597.091064, 12.021874, 90.000000, 0.000000, -179.999984, -1, -1, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "white", 0x00000000);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tmpobjid = CreateDynamicObject(1569, 2079.885498, -1566.110717, 12.356739, -0.000006, -0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(1569, 2079.906005, -1584.650756, 12.461743, -0.000006, -0.000000, 90.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(3507, 2084.788574, -1596.853271, 12.432135, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(3507, 2084.788574, -1556.387939, 12.432135, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(8991, 2080.299072, -1563.003540, 12.387502, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(8991, 2080.299072, -1567.177612, 12.387502, 0.000000, 0.000000, -179.999984, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(8991, 2080.299072, -1585.736206, 12.387502, 0.000000, 0.000000, -179.999984, -1, -1, -1, 300.00, 300.00);
	tmpobjid = CreateDynamicObject(8991, 2080.299072, -1581.532104, 12.387502, 0.000000, 0.000000, -179.999984, -1, -1, -1, 300.00, 300.00);
}
