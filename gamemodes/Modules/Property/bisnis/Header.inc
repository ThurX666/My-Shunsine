
enum bisinfo
{
	bOwner[MAX_PLAYER_NAME],
	bName[128],
	bPrice,
	bType,
	bLocked,
	bMoney,
	bProd,
	bP[12],
	bInt,
	Float:bExtposX,
	Float:bExtposY,
	Float:bExtposZ,
	Float:bExtposA,
	Float:bIntposX,
	Float:bIntposY,
	Float:bIntposZ,
	Float:bIntposA,
	bLastVisited,
	bRestock,
	Float:bPointX,
	Float:bPointY,
	Float:bPointZ,
	bSegel,
	bPName0[128],
	bPName1[128],
	bPName2[128],
	bPName3[128],
	bPName4[128],
	bPName5[128],
	bPName6[128],
	bPName7[128],
	bPName8[128],
	bPName9[128],
	bPName10[128],
	bStream[128],
	bExtInt,
	bExtVw,
	Float:bDriveThru[3],
	//Not Saved
	bIcon,
	bPickPoint,
	Text3D:bLabelPoint,
	bPickup[2],
	bCP[2],
	Text3D:bLabel,
	BiznisID
};

enum bussinesgarage {
	Float:ExtPos[3],
	BizGarage,
	Text3D:GarageText,
	GaragePick
}
new BussinesGarage[MAX_BISNIS][bussinesgarage];

enum bussinesproduct {
	BussinesProduct[11]
}
new BusinnesProduct[MAX_BISNIS][bussinesproduct];

new bData[MAX_BISNIS][bisinfo],
	Iterator: Bisnis<MAX_BISNIS>;
