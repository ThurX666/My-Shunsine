
enum EDITPOINTDATA
{
	pEditObject,
	Float:pEditX,
	Float:pEditY,
	Float:pEditZ,
	Float:pEditRX,
	Float:pEditRY,
	Float:pEditRZ,
	
	Float:pSaveX,
	Float:pSaveY,
	Float:pSaveZ,
	Float:pSaveRX,
	Float:pSaveRY,
	Float:pSaveRZ,
	
	pEditObjectSel,
	pEditCallBack[32],
}
new pEditPoint[MAX_PLAYERS][EDITPOINTDATA];

stock PlayerEditPoint(playerid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, callback[], objectid = -1)
{
	if(pEditPoint[playerid][pEditObject] > -1)
		DestroyDynamicObject(pEditPoint[playerid][pEditObject]);

	if(objectid == -1)
	{
		pEditPoint[playerid][pEditObject] = CreateDynamicObject(1974,
					x,
					y,
					z,
					rx,
					ry,
					rz,
					-1, -1, playerid, .priority = 1);
	    SetDynamicObjectMaterial(pEditPoint[playerid][pEditObject], 0, 10765, "airportgnd_sfse", "white", -256);
	    format(pEditPoint[playerid][pEditCallBack], 32, "%s", callback);

	    pEditPoint[playerid][pEditX] = x;
	    pEditPoint[playerid][pEditY] = y;
	    pEditPoint[playerid][pEditZ] = z;
	    pEditPoint[playerid][pEditRX] = rx;
	    pEditPoint[playerid][pEditRY] = ry;
	    pEditPoint[playerid][pEditRZ] = rz;

	    pEditPoint[playerid][pSaveX] = x;
	    pEditPoint[playerid][pSaveY] = y;
	    pEditPoint[playerid][pSaveZ] = z;
	    pEditPoint[playerid][pSaveRX] = rx;
	    pEditPoint[playerid][pSaveRY] = ry;
	    pEditPoint[playerid][pSaveRZ] = rz;

		Streamer_Update(playerid);

		EditDynamicObject(playerid, pEditPoint[playerid][pEditObject]);
	}
	else
	{
		pEditPoint[playerid][pEditObjectSel] = objectid;

		format(pEditPoint[playerid][pEditCallBack], 32, "%s", callback);
		
		pEditPoint[playerid][pEditX] = x;
	    pEditPoint[playerid][pEditY] = y;
	    pEditPoint[playerid][pEditZ] = z;
	    pEditPoint[playerid][pEditRX] = rx;
	    pEditPoint[playerid][pEditRY] = ry;
	    pEditPoint[playerid][pEditRZ] = rz;

	    pEditPoint[playerid][pSaveX] = x;
	    pEditPoint[playerid][pSaveY] = y;
	    pEditPoint[playerid][pSaveZ] = z;
	    pEditPoint[playerid][pSaveRX] = rx;
	    pEditPoint[playerid][pSaveRY] = ry;
	    pEditPoint[playerid][pSaveRZ] = rz;

	    Streamer_Update(playerid);

        EditDynamicObject(playerid, pEditPoint[playerid][pEditObjectSel]);
	}
	
	return 1;
}

stock DestroyEditPoint(playerid)
{
	if(pEditPoint[playerid][pEditObject] != -1)
	{
		DestroyDynamicObject(pEditPoint[playerid][pEditObject]);
		pEditPoint[playerid][pEditObject] = -1;
	}
	return 1;
}
