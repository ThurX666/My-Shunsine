
function OnBisnisCreated(bid)
{
	Bisnis_Save(bid);
	return 1;
}

Bisnis_Save(id)
{
	new cQuery[2248];
	format(cQuery, sizeof(cQuery), "UPDATE bisnis SET owner='%s', name='%s', price='%d', type='%d', locked='%d', money='%d', prod='%d', bprice0='%d', bprice1='%d', bprice2='%d', bprice3='%d', bprice4='%d', bprice5='%d', bprice6='%d', bprice7='%d', bprice8='%d', bprice9='%d', bprice10='%d', bint='%d', extposx='%f', extposy='%f', extposz='%f', extposa='%f', intposx='%f', intposy='%f', intposz='%f', intposa='%f', pointx='%f', pointy='%f', pointz='%f', visit='%d', restock='%d', segel='%d', bpname0='%s', bpname1='%s', bpname2='%s', bpname3='%s', bpname4='%s', bpname5='%s', bpname6='%s', bpname7='%s', bpname8='%s', bpname9='%s', bpname10='%s', stream='%s', extvw='%d', extint='%d'",
	bData[id][bOwner],
	bData[id][bName],
	bData[id][bPrice],
	bData[id][bType],
	bData[id][bLocked],
	bData[id][bMoney],
	bData[id][bProd],
	bData[id][bP][0],
	bData[id][bP][1],
	bData[id][bP][2],
	bData[id][bP][3],
	bData[id][bP][4],
	bData[id][bP][5],
	bData[id][bP][6],
	bData[id][bP][7],
	bData[id][bP][8],
	bData[id][bP][9],
	bData[id][bP][10],
	bData[id][bInt],
	bData[id][bExtposX],
	bData[id][bExtposY],
	bData[id][bExtposZ],
	bData[id][bExtposA],
	bData[id][bIntposX],
	bData[id][bIntposY],
	bData[id][bIntposZ],
	bData[id][bIntposA],
	bData[id][bPointX],
	bData[id][bPointY],
	bData[id][bPointZ],
	bData[id][bLastVisited],
	bData[id][bRestock],
	bData[id][bSegel],
	bData[id][bPName0],
	bData[id][bPName1],
	bData[id][bPName2],
	bData[id][bPName3],
	bData[id][bPName4],
	bData[id][bPName5],
	bData[id][bPName6],
	bData[id][bPName7],
	bData[id][bPName8],
	bData[id][bPName9],
	bData[id][bPName10],
	bData[id][bStream],
	bData[id][bExtVw],
	bData[id][bExtInt]);

	format(cQuery, sizeof(cQuery), "%s, drivethru='%.2f|%.2f|%.2f', garagepos='%.2f|%.2f|%.2f|%d', bussinesstock='%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d' WHERE ID='%d'", 
	cQuery,
	bData[id][bDriveThru][0],
	bData[id][bDriveThru][1],
	bData[id][bDriveThru][2],
	BussinesGarage[id][ExtPos][0],
	BussinesGarage[id][ExtPos][1],
	BussinesGarage[id][ExtPos][2],
	BussinesGarage[id][BizGarage],
	BusinnesProduct[id][BussinesProduct][0],
	BusinnesProduct[id][BussinesProduct][1],
	BusinnesProduct[id][BussinesProduct][2],
	BusinnesProduct[id][BussinesProduct][3],
	BusinnesProduct[id][BussinesProduct][4],
	BusinnesProduct[id][BussinesProduct][5],
	BusinnesProduct[id][BussinesProduct][6],
	BusinnesProduct[id][BussinesProduct][7],
	BusinnesProduct[id][BussinesProduct][8],
	BusinnesProduct[id][BussinesProduct][9],
	BusinnesProduct[id][BussinesProduct][10],
	id
	);
	return mysql_tquery(g_SQL, cQuery);
}
	
Player_OwnsBisnis(playerid, id)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(id == -1) return 0;
	if(!strcmp(bData[id][bOwner], pData[playerid][pName], true)) return 1;
	return 0;
}

// Player_BisnisCount(playerid)
// {
// 	#if LIMIT_PER_PLAYER != 0
//     new count;
// 	foreach(new i : Bisnis)
// 	{
// 		if(Player_OwnsBisnis(playerid, i)) count++;
// 	}

// 	return count;
// 	#else
// 	return 0;
// 	#endif
// }

Bisnis_Reset(id)
{
	format(bData[id][bOwner], MAX_PLAYER_NAME, "-");
	bData[id][bLocked] = 1;
    bData[id][bMoney] = 0;
	bData[id][bProd] = 0;
	bData[id][bLastVisited] = 0;
	bData[id][bRestock] = 0;
	bData[id][bPrice] = 0;
	bData[id][bSegel] = 0;
	for(new i = 0; i < 12; i++) bData[id][bP][i] = 0;
	format(bData[id][bPName0], 128, "-");
	format(bData[id][bPName1], 128, "-");
	format(bData[id][bPName2], 128, "-");
	format(bData[id][bPName3], 128, "-");
	format(bData[id][bPName4], 128, "-");
	format(bData[id][bPName5], 128, "-");
	format(bData[id][bPName6], 128, "-");
	format(bData[id][bPName7], 128, "-");
	format(bData[id][bPName8], 128, "-");
	format(bData[id][bPName9], 128, "-");
	format(bData[id][bPName10], 128, "-");
	format(bData[id][bStream], 128, "");
	for(new i = 0; i < 11; i++) BusinnesProduct[id][BussinesProduct][i] = 0;
}

GetOwnedBisnis(playerid)
{
	new tmpcount;
	foreach(new bid : Bisnis)
	{
	    if(!strcmp(bData[bid][bOwner], ReturnName(playerid), true))
	    {
     		tmpcount++;
		}
	}
	return tmpcount;
}

ReturnPlayerBisnisID(playerid, hslot)
{
	new tmpcount;
	if(hslot < 1 && hslot > LIMIT_PER_PLAYER) return -1;
	foreach(new bid : Bisnis)
	{
	    if(!strcmp(ReturnName(playerid), bData[bid][bOwner], true))
	    {
     		tmpcount++;
       		if(tmpcount == hslot)
       		{
        		return bid;
  			}
	    }
	}
	return -1;
}

Bisnis_ProductStock(playerid, bizid)
{
    if(bizid <= -1) return 0;
    static string[512];
    switch (bData[bizid][bType])
    {
        case 1:
        {
            format(string, sizeof(string), "%s (Menu +40)\tStock %d unit(s)\n%s (Menu +30)\tStock %d unit(s)\n%s (Energy +40)\tStock %d unit(s)\n%s (Energy +30)\tStock %d unit(s)",
                ReplaceString(bData[bizid][bPName0]),
				BusinnesProduct[bizid][BussinesProduct][0],
				ReplaceString(bData[bizid][bPName1]),
                BusinnesProduct[bizid][BussinesProduct][1],
				ReplaceString(bData[bizid][bPName2]),
                BusinnesProduct[bizid][BussinesProduct][2],
				ReplaceString(bData[bizid][bPName3]),
                BusinnesProduct[bizid][BussinesProduct][3]
            );
            Dialog_Show(playerid, RestockProduct, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Select", "Cancel");
        }
        case 2:
        {
            format(string, sizeof(string), "%s (Snack)\tStock %d unit(s)\n%s (Water)\tStock %d unit(s)\n%s (Bandage)\tStock %d unit(s)\n%s (Pack of Cigarettes)\tStock %d unit(s)\n%s (Toll Card (50))\tStock %d unit(s)",
                ReplaceString(bData[bizid][bPName0]),
				BusinnesProduct[bizid][BussinesProduct][0],
				ReplaceString(bData[bizid][bPName1]),
                BusinnesProduct[bizid][BussinesProduct][1],
				ReplaceString(bData[bizid][bPName2]),
                BusinnesProduct[bizid][BussinesProduct][2],
				ReplaceString(bData[bizid][bPName3]),
                BusinnesProduct[bizid][BussinesProduct][3],
				ReplaceString(bData[bizid][bPName4]),
				BusinnesProduct[bizid][BussinesProduct][4]
            );
            Dialog_Show(playerid, RestockProduct, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Select", "Cancel");
        }
        case 3:
        {
            format(string, sizeof(string), "%s (Clothes)\tStock %d unit(s)\n%s (Caps)\tStock %d unit(s)\n%s (Bandana)\tStock %d unit(s)\n%s (Mask)\tStock %d unit(s)\n%s (Helmet)\tStock %d unit(s)\n%s (Watch)\tStock %d unit(s)\n%s (Glasses)\tStock %d unit(s)\n%s (Hair)\tStock %d unit(s)\n%s (Misc)\tStock %d unit(s)",
                ReplaceString(bData[bizid][bPName0]),
				BusinnesProduct[bizid][BussinesProduct][0],
				ReplaceString(bData[bizid][bPName1]),
                BusinnesProduct[bizid][BussinesProduct][1],
				ReplaceString(bData[bizid][bPName2]),
                BusinnesProduct[bizid][BussinesProduct][2],
				ReplaceString(bData[bizid][bPName3]),
                BusinnesProduct[bizid][BussinesProduct][3],
				ReplaceString(bData[bizid][bPName4]),
                BusinnesProduct[bizid][BussinesProduct][4],
				ReplaceString(bData[bizid][bPName5]),
                BusinnesProduct[bizid][BussinesProduct][5],
				ReplaceString(bData[bizid][bPName6]),
                BusinnesProduct[bizid][BussinesProduct][6],
				ReplaceString(bData[bizid][bPName7]),
                BusinnesProduct[bizid][BussinesProduct][7],
				ReplaceString(bData[bizid][bPName8]),
                BusinnesProduct[bizid][BussinesProduct][8]
            );
            Dialog_Show(playerid, RestockProduct, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Select", "Cancel");
        }
        case 4:
        {
            format(string, sizeof(string), "%s (Baseball bat)\tStock %d unit(s)\n%s (Shovel)\tStock %d unit(s)\n%s (Cane)\tStock %d unit(s)\n%s (Fish Tool)- %s\n%s (Mask)- %s",
                ReplaceString(bData[bizid][bPName0]),
				BusinnesProduct[bizid][BussinesProduct][0],
				ReplaceString(bData[bizid][bPName1]),
                BusinnesProduct[bizid][BussinesProduct][1],
				ReplaceString(bData[bizid][bPName2]),
                BusinnesProduct[bizid][BussinesProduct][2],
				ReplaceString(bData[bizid][bPName3]),
                BusinnesProduct[bizid][BussinesProduct][3],
				ReplaceString(bData[bizid][bPName4]),
                BusinnesProduct[bizid][BussinesProduct][4]
            );
            Dialog_Show(playerid, RestockProduct, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Select", "Cancel");
        }
		case 5:
        {
            format(string, sizeof(string), "%s (Handphone)\tStock %d unit(s)\n%s (GPS)\tStock %d unit(s)\n%s (Phone Credit (1000))\tStock %d unit(s)\n%s (Portable Radio)- %s",
                ReplaceString(bData[bizid][bPName0]),
				BusinnesProduct[bizid][BussinesProduct][0],
				ReplaceString(bData[bizid][bPName1]),
                BusinnesProduct[bizid][BussinesProduct][1],
				ReplaceString(bData[bizid][bPName2]),
                BusinnesProduct[bizid][BussinesProduct][2],
				ReplaceString(bData[bizid][bPName3]),
                BusinnesProduct[bizid][BussinesProduct][3]
            );
            Dialog_Show(playerid, RestockProduct, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Select", "Cancel");
        }
		case 6:
        {
            format(string, sizeof(string), "%s (GYM Membership)\tStock %d unit(s)\n%s (Energy Drink)\tStock %d unit(s)\n%s (Water)\tStock %d unit(s)\n%s (Snack)\tStock %d unit(s)",
                ReplaceString(bData[bizid][bPName0]),
				BusinnesProduct[bizid][BussinesProduct][0],
				ReplaceString(bData[bizid][bPName1]),
                BusinnesProduct[bizid][BussinesProduct][1],
				ReplaceString(bData[bizid][bPName2]),
                BusinnesProduct[bizid][BussinesProduct][2],
				ReplaceString(bData[bizid][bPName3]),
                BusinnesProduct[bizid][BussinesProduct][3]
            );
            Dialog_Show(playerid, RestockProduct, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Select", "Cancel");
        }
		case 7:
        {
            format(string, sizeof(string), "%s (Weapon AK47)\tStock %d unit(s)\n%s (Weapon MP5)\tStock %d unit(s)\n%s (Weapon Desert Eagle)\tStock %d unit(s)\n%s (Weapon Shotgun)\tStock %d unit(s)",
                ReplaceString(bData[bizid][bPName0]),
				BusinnesProduct[bizid][BussinesProduct][0],
				ReplaceString(bData[bizid][bPName1]),
                BusinnesProduct[bizid][BussinesProduct][1],
				ReplaceString(bData[bizid][bPName2]),
                BusinnesProduct[bizid][BussinesProduct][2],
				ReplaceString(bData[bizid][bPName3]),
                BusinnesProduct[bizid][BussinesProduct][3]
            );
            Dialog_Show(playerid, RestockProduct, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Select", "Cancel");
        }
    }
    return 1;
}

Bisnis_BuyMenu(playerid, bizid)
{
    if(bizid <= -1 )
        return 0;

    static
        string[512];

    switch(bData[bizid][bType])
    {
		case 1:
        {
            format(string, sizeof(string), "%s (Menu +20)  - %s\n%s (Menu +10)  - %s\n%s (Energy +20)  - %s\n%s (Energy +10) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3])
            );
            Dialog_Show(playerid, BisnisPlayerBuyProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Buy", "Cancel");
        }
        case 2:
        {
            format(string, sizeof(string), "%s (Snack) - %s\n%s (Water) - %s\n%s (Bandage) - %s\n%s (Pack of Cigarettes) - %s\n%s (Toll Card (50)) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3]),
				ReplaceString(bData[bizid][bPName4]),
				FormatMoney(bData[bizid][bP][4])
            );
            Dialog_Show(playerid, BisnisPlayerBuyProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Buy", "Cancel");
        }
        case 3:
        {
            format(string, sizeof(string), "%s (Clothes) - %s\n%s (Caps) - %s\n%s (Bandana) - %s\n%s (Mask) - %s\n%s (Helmet) - %s\n%s (Watch) - %s\n%s (Glasses) - %s\n%s (Hair) - %s\n%s (Misc) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3]),
				ReplaceString(bData[bizid][bPName4]),
                FormatMoney(bData[bizid][bP][4]),
				ReplaceString(bData[bizid][bPName5]),
                FormatMoney(bData[bizid][bP][5]),
				ReplaceString(bData[bizid][bPName6]),
                FormatMoney(bData[bizid][bP][6]),
				ReplaceString(bData[bizid][bPName7]),
                FormatMoney(bData[bizid][bP][7]),
				ReplaceString(bData[bizid][bPName8]),
                FormatMoney(bData[bizid][bP][8])
            );
            Dialog_Show(playerid, BisnisPlayerBuyProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Buy", "Cancel");
        }
        case 4:
        {
            format(string, sizeof(string), "%s (Baseball bat) - %s\n%s (Shovel) - %s\n%s (Cane) - %s\n%s (Fish Tool)- %s\n%s (Mask)- %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3]),
				ReplaceString(bData[bizid][bPName4]),
                FormatMoney(bData[bizid][bP][4])
            );
            Dialog_Show(playerid, BisnisPlayerBuyProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Buy", "Cancel");
        }
		case 5:
        {
            format(string, sizeof(string), "%s (Handphone) - %s\n%s (GPS) - %s\n%s (Phone Credit (1000)) - %s\n%s (Portable Radio)- %s\n%s (Phone Book)- %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3]),
				ReplaceString(bData[bizid][bPName4]),
                FormatMoney(bData[bizid][bP][4])
            );
            Dialog_Show(playerid, BisnisPlayerBuyProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Buy", "Cancel");
        }
		case 6:
        {
            format(string, sizeof(string), "%s (GYM Membership) - %s\n%s (Water) - %s\n%s (Snack) - %s\n%s (Fight Style) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3])
            );
            Dialog_Show(playerid, BisnisPlayerBuyProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Buy", "Cancel");
        }
		case 7:
        {
            format(string, sizeof(string), "%s (Weapon AK47) - %s\n%s (Weapon MP5) - %s\n%s (Weapon Desert Eagle) - %s\n%s (Weapon Shotgun) - %s\n%s (Training) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3]),
				ReplaceString(bData[bizid][bPName4]),
                FormatMoney(bData[bizid][bP][4])
            );
            Dialog_Show(playerid, BisnisPlayerBuyProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Buy", "Cancel");
        }
    }
    return 1;
}

Bisnis_ProductMenu(playerid, bizid)
{
    if(bizid <= -1) return 0;
    static string[512];
    switch (bData[bizid][bType])
    {
        case 1:
        {
            format(string, sizeof(string), "%s (Menu +40)  - %s\n%s (Menu +30)  - %s\n%s (Energy +40)  - %s\n%s (Energy +30) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3])
            );
            Dialog_Show(playerid, BisnisSetProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
        case 2:
        {
            format(string, sizeof(string), "%s (Snack) - %s\n%s (Water) - %s\n%s (Bandage) - %s\n%s (Pack of Cigarettes) - %s\n%s (Toll Card (50)) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3]),
				ReplaceString(bData[bizid][bPName4]),
				FormatMoney(bData[bizid][bP][4])
            );
            Dialog_Show(playerid, BisnisSetProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
        case 3:
        {
            format(string, sizeof(string), "%s (Clothes) - %s\n%s (Caps) - %s\n%s (Bandana) - %s\n%s (Mask) - %s\n%s (Helmet) - %s\n%s (Watch) - %s\n%s (Glasses) - %s\n%s (Hair) - %s\n%s (Misc) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3]),
				ReplaceString(bData[bizid][bPName4]),
                FormatMoney(bData[bizid][bP][4]),
				ReplaceString(bData[bizid][bPName5]),
                FormatMoney(bData[bizid][bP][5]),
				ReplaceString(bData[bizid][bPName6]),
                FormatMoney(bData[bizid][bP][6]),
				ReplaceString(bData[bizid][bPName7]),
                FormatMoney(bData[bizid][bP][7]),
				ReplaceString(bData[bizid][bPName8]),
                FormatMoney(bData[bizid][bP][8])
            );
            Dialog_Show(playerid, BisnisSetProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
        case 4:
        {
            format(string, sizeof(string), "%s (Baseball bat) - %s\n%s (Shovel) - %s\n%s (Cane) - %s\n%s (Fish Tool)- %s\n%s (Mask)- %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3]),
				ReplaceString(bData[bizid][bPName4]),
                FormatMoney(bData[bizid][bP][4])
            );
            Dialog_Show(playerid, BisnisSetProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
		case 5:
        {
            format(string, sizeof(string), "%s (Handphone) - %s\n%s (GPS) - %s\n%s (Phone Credit (1000)) - %s\n%s (Portable Radio)- %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3])
            );
            Dialog_Show(playerid, BisnisSetProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
		case 6:
        {
            format(string, sizeof(string), "%s (GYM Membership) - %s\n%s (Energy Drink) - %s\n%s (Water) - %s\n%s (Snack) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3])
            );
            Dialog_Show(playerid, BisnisSetProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
		case 7:
        {
            format(string, sizeof(string), "%s (Weapon AK47) - %s\n%s (Weapon MP5) - %s\n%s (Weapon Desert Eagle) - %s\n%s (Weapon Shotgun) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3])
            );
            Dialog_Show(playerid, BisnisSetProd, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
    }
    return 1;
}

Bisnis_ProductMenuName(playerid, bizid)
{
    if(bizid <= -1) return 0;
    static string[512];
    switch (bData[bizid][bType])
    {
        case 1:
        {
            format(string, sizeof(string), "%s (Menu +40)  - %s\n%s (Menu +30)  - %s\n%s (Energy +40)  - %s\n%s (Energy +30) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3])
            );
            Dialog_Show(playerid, BizEditProdName, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
        case 2:
        {
            format(string, sizeof(string), "%s (Snack) - %s\n%s (Water) - %s\n%s (Bandage) - %s\n%s (Pack of Cigarettes) - %s\n%s (Toll Card (50)) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3]),
				ReplaceString(bData[bizid][bPName4]),
				FormatMoney(bData[bizid][bP][4])
            );
            Dialog_Show(playerid, BizEditProdName, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
        case 3:
        {
            format(string, sizeof(string), "%s (Clothes) - %s\n%s (Caps) - %s\n%s (Bandana) - %s\n%s (Mask) - %s\n%s (Helmet) - %s\n%s (Watch) - %s\n%s (Glasses) - %s\n%s (Hair) - %s\n%s (Misc) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3]),
				ReplaceString(bData[bizid][bPName4]),
                FormatMoney(bData[bizid][bP][4]),
				ReplaceString(bData[bizid][bPName5]),
                FormatMoney(bData[bizid][bP][5]),
				ReplaceString(bData[bizid][bPName6]),
                FormatMoney(bData[bizid][bP][6]),
				ReplaceString(bData[bizid][bPName7]),
                FormatMoney(bData[bizid][bP][7]),
				ReplaceString(bData[bizid][bPName8]),
                FormatMoney(bData[bizid][bP][8])
            );
            Dialog_Show(playerid, BizEditProdName, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
        case 4:
        {
            format(string, sizeof(string), "%s (Baseball bat) - %s\n%s (Shovel) - %s\n%s (Cane) - %s\n%s (Fish Tool)- %s\n%s (Mask)- %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3]),
				ReplaceString(bData[bizid][bPName4]),
                FormatMoney(bData[bizid][bP][4])
            );
            Dialog_Show(playerid, BizEditProdName, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
		case 5:
        {
            format(string, sizeof(string), "%s (Handphone) - %s\n%s (GPS) - %s\n%s (Phone Credit (1000)) - %s\n%s (Portable Radio)- %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3])
            );
            Dialog_Show(playerid, BizEditProdName, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
		case 6:
        {
            format(string, sizeof(string), "%s (GYM Membership) - %s\n%s (Energy Drink) - %s\n%s (Water) - %s\n%s (Snack) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3])
            );
            Dialog_Show(playerid, BizEditProdName, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
		case 7:
        {
            format(string, sizeof(string), "%s (Weapon AK47) - %s\n%s (Weapon MP5) - %s\n%s (Weapon Desert Eagle) - %s\n%s (Weapon Shotgun) - %s",
                ReplaceString(bData[bizid][bPName0]),
				FormatMoney(bData[bizid][bP][0]),
				ReplaceString(bData[bizid][bPName1]),
                FormatMoney(bData[bizid][bP][1]),
				ReplaceString(bData[bizid][bPName2]),
                FormatMoney(bData[bizid][bP][2]),
				ReplaceString(bData[bizid][bPName3]),
                FormatMoney(bData[bizid][bP][3])
            );
            Dialog_Show(playerid, BizEditProdName, DIALOG_STYLE_LIST, ReplaceString(bData[bizid][bName]), string, "Change", "Cancel");
        }
    }
    return 1;
}

Bisnis_ProductNameRefresh(id)
{
    if(id != -1)
    {
		switch(bData[id][bType])
		{
			case 1:
			{
				if(!strcmp(bData[id][bPName0], "-")) format(bData[id][bPName0], 128, "Fried Chicken");
				if(!strcmp(bData[id][bPName1], "-")) format(bData[id][bPName1], 128, "Pizza Stack");
				if(!strcmp(bData[id][bPName2], "-")) format(bData[id][bPName2], 128, "Patty Burger");
				if(!strcmp(bData[id][bPName3], "-")) format(bData[id][bPName3], 128, "Sprunk");
			}
			case 2:
			{
				if(!strcmp(bData[id][bPName0], "-")) format(bData[id][bPName0], 128, "Snack");
				if(!strcmp(bData[id][bPName1], "-")) format(bData[id][bPName1], 128, "Sprunk");
				if(!strcmp(bData[id][bPName2], "-")) format(bData[id][bPName2], 128, "Bandage");
				if(!strcmp(bData[id][bPName3], "-")) format(bData[id][bPName3], 128, "Cigarretes");
				if(!strcmp(bData[id][bPName4], "-")) format(bData[id][bPName4], 128, "Toll Card");
			}	
			case 3:
			{
				if(!strcmp(bData[id][bPName0], "-")) format(bData[id][bPName0], 128, "Clothes");
				if(!strcmp(bData[id][bPName1], "-")) format(bData[id][bPName1], 128, "Hats");
				if(!strcmp(bData[id][bPName2], "-")) format(bData[id][bPName2], 128, "Glasses");
				if(!strcmp(bData[id][bPName3], "-")) format(bData[id][bPName3], 128, "Helm");
				if(!strcmp(bData[id][bPName4], "-")) format(bData[id][bPName4], 128, "Accessory");
				if(!strcmp(bData[id][bPName5], "-")) format(bData[id][bPName5], 128, "Mask (Accessory)");
				if(!strcmp(bData[id][bPName6], "-")) format(bData[id][bPName6], 128, "Hairs");
			}
			case 4:
			{	
				if(!strcmp(bData[id][bPName0], "-")) format(bData[id][bPName0], 128, "Baseball Bat");
				if(!strcmp(bData[id][bPName1], "-")) format(bData[id][bPName1], 128, "Shovel");
				if(!strcmp(bData[id][bPName2], "-")) format(bData[id][bPName2], 128, "Cane");
				if(!strcmp(bData[id][bPName3], "-")) format(bData[id][bPName3], 128, "Fishing Tools");
				if(!strcmp(bData[id][bPName4], "-")) format(bData[id][bPName4], 128, "Mask");
			}
			case 5:
			{	
				if(!strcmp(bData[id][bPName0], "-")) format(bData[id][bPName0], 128, "Handphone");
				if(!strcmp(bData[id][bPName1], "-")) format(bData[id][bPName1], 128, "GPS");
				if(!strcmp(bData[id][bPName2], "-")) format(bData[id][bPName2], 128, "Phone credit");
				if(!strcmp(bData[id][bPName3], "-")) format(bData[id][bPName3], 128, "Walkie talkie");
			}
			case 6:
			{	
				if(!strcmp(bData[id][bPName0], "-")) format(bData[id][bPName0], 128, "GYM Membership");
				if(!strcmp(bData[id][bPName1], "-")) format(bData[id][bPName1], 128, "Energy Drink");
				if(!strcmp(bData[id][bPName2], "-")) format(bData[id][bPName2], 128, "Water");
				if(!strcmp(bData[id][bPName3], "-")) format(bData[id][bPName3], 128, "Snack");
			}
			case 7:
			{	
				if(!strcmp(bData[id][bPName0], "-")) format(bData[id][bPName0], 128, "AK47");
				if(!strcmp(bData[id][bPName1], "-")) format(bData[id][bPName1], 128, "MP5");
				if(!strcmp(bData[id][bPName2], "-")) format(bData[id][bPName2], 128, "Desert Eagle");
				if(!strcmp(bData[id][bPName3], "-")) format(bData[id][bPName3], 128, "Shotgun");
			}
		}	
        
    }
    return 1;
}

Bisnis_Type(bisid)
{
	if(bData[bisid][bType] == 1) // Fast Food
	{
	    switch(random(2))
		{
			case 0:
			{
				bData[bisid][bIntposX] = 363.22;
				bData[bisid][bIntposY] = -74.86;
				bData[bisid][bIntposZ] = 1001.50;
				bData[bisid][bIntposA] = 319.72;
				bData[bisid][bInt] = 10;
				bData[bisid][bPointX] = 376.8142;
				bData[bisid][bPointY] = -68.0401;
				bData[bisid][bPointZ] = 1001.5151;
			}
			case 1: // ,,
			{
				bData[bisid][bIntposX] = 372.34;
				bData[bisid][bIntposY] = -133.25;
				bData[bisid][bIntposZ] = 1001.49;
				bData[bisid][bIntposA] = 4.80;
				bData[bisid][bInt] = 5;
				bData[bisid][bPointX] = 375.4402;
				bData[bisid][bPointY] = -119.9117;
				bData[bisid][bPointZ] = 1001.4995;
			} 
		}
	}
	if(bData[bisid][bType] == 2) //Market
	{
	    switch(random(2))
		{
			case 0: // 1.9983,-29.0117,1003.5494
			{
				bData[bisid][bIntposX] = 5.73;
				bData[bisid][bIntposY] = -31.04;
				bData[bisid][bIntposZ] = 1003.54;
				bData[bisid][bIntposA] = 355.73;
				bData[bisid][bInt] = 10;
				bData[bisid][bPointX] = 1.9983;
				bData[bisid][bPointY] = -29.0117;
				bData[bisid][bPointZ] = 1003.5494;
			}
			case 1: //-23.4406,-55.6324,1003.5469
			{
				bData[bisid][bIntposX] = -26.68;
				bData[bisid][bIntposY] = -57.92;
				bData[bisid][bIntposZ] = 1003.54;
				bData[bisid][bIntposA] = 357.58;
				bData[bisid][bInt] = 6;
				bData[bisid][bPointX] = -23.4406;
				bData[bisid][bPointY] = -55.6324;
				bData[bisid][bPointZ] = 1003.5469;
			}
		}
	}
	if(bData[bisid][bType] == 3) //Clothes
	{
	    switch(random(2))
		{
			case 0: // 207.5234,-100.7358,1005.2578
			{
				bData[bisid][bIntposX] = 207.55;
				bData[bisid][bIntposY] = -110.67;
				bData[bisid][bIntposZ] = 1005.13;
				bData[bisid][bIntposA] = 0.16;
				bData[bisid][bInt] = 15;
				bData[bisid][bPointX] = 207.5234;
				bData[bisid][bPointY] = -100.7358;
				bData[bisid][bPointZ] = 1005.2578;
			}
			case 1: // 204.3724,-159.6976,1000.5234
			{
				bData[bisid][bIntposX] = 204.49;
				bData[bisid][bIntposY] = -168.26;
				bData[bisid][bIntposZ] = 1000.52;
				bData[bisid][bIntposA] = 358.74;
				bData[bisid][bInt] = 14;
				bData[bisid][bPointX] = 204.3724;
				bData[bisid][bPointY] = -159.6976;
				bData[bisid][bPointZ] = 1000.5234;
			}
		}
	}
	if(bData[bisid][bType] == 4) // Sportshop
	{ //203.7197,-50.0292,1001.8047,5.1475
		bData[bisid][bIntposX] = 203.7197;
		bData[bisid][bIntposY] = -50.0292;
		bData[bisid][bIntposZ] = 1001.8047;
		bData[bisid][bIntposA] = 5.1475;
		bData[bisid][bInt] = 1;
		bData[bisid][bPointX] = 203.8431;
		bData[bisid][bPointY] = -43.2778;
		bData[bisid][bPointZ] = 1001.8047;
	}
	if(bData[bisid][bType] == 5) // Electronic
	{ //-2240.468505,137.060440,1035.414062	
		bData[bisid][bIntposX] = -2240.3938;
		bData[bisid][bIntposY] = 137.3993;
		bData[bisid][bIntposZ] = 1035.4141;
		bData[bisid][bIntposA] = 270.2590;
		bData[bisid][bInt] = 6;
		bData[bisid][bPointX] = -2235.4143;
		bData[bisid][bPointY] = 130.1577;
		bData[bisid][bPointZ] = 1035.4141;
	}
	if(bData[bisid][bType] == 6) // GYM
	{ //-2240.468505,137.060440,1035.414062	
		bData[bisid][bIntposX] = 773.9973;
		bData[bisid][bIntposY] = -78.0601;
		bData[bisid][bIntposZ] = 1000.6616;
		bData[bisid][bIntposA] = 356.1021;
		bData[bisid][bInt] = 7;
		bData[bisid][bPointX] = 758.4368;
		bData[bisid][bPointY] = -77.4804;
		bData[bisid][bPointZ] = 1000.6505;
		//Bike
		GYMObject_Add(bisid, 2630, 1, 774.794189, -66.758522, 999.638427, 0.000000, 0.000000, 270.000000, bData[bisid][bInt], bisid);
		GYMObject_Add(bisid, 2630, 1, 774.794189, -68.968551, 999.638427, 0.000000, 0.000000, 270.000000, bData[bisid][bInt], bisid);
		GYMObject_Add(bisid, 2630, 1, 774.794189, -71.088569, 999.638427, 0.000000, 0.000000, 270.000000, bData[bisid][bInt], bisid);
		//TreadMill
		GYMObject_Add(bisid, 2627, 2, 758.382629, -59.465457, 999.633666, 0.000000, 0.000000, 180.000000, bData[bisid][bInt], bisid);
		GYMObject_Add(bisid, 2627, 2, 760.803344, -59.465457, 999.633666, 0.000000, 0.000000, 180.000000, bData[bisid][bInt], bisid);
		GYMObject_Add(bisid, 2627, 2, 762.984191, -59.465457, 999.633666, 0.000000, 0.000000, 180.000000, bData[bisid][bInt], bisid);
		//Boxing
		GYMObject_Add(bisid, 1985, 3, 773.351989, -59.250000, 1002.590026, 0.000000, 0.000000, 0.000000, bData[bisid][bInt], bisid);
		GYMObject_Add(bisid, 1985, 3, 773.351989, -61.531299, 1002.590026, 0.000000, 0.000000, 0.000000, bData[bisid][bInt], bisid);
		GYMObject_Add(bisid, 1985, 3, 773.867004, -64.718803, 1002.590026, 0.000000, 0.000000, 0.000000, bData[bisid][bInt], bisid);
	}
	if(bData[bisid][bType] == 7) // Ammunation
	{ //286.148986,-40.644397,1001.515625
		bData[bisid][bIntposX] = 286.148986;
		bData[bisid][bIntposY] = -40.644397;
		bData[bisid][bIntposZ] = 1001.515625;
		bData[bisid][bIntposA] = 0;
		bData[bisid][bInt] = 1;
		bData[bisid][bPointX] = 295.4464;
		bData[bisid][bPointY] = -38.0804;
		bData[bisid][bPointZ] = 1001.5156;
	}
}

Bisnis_Refresh(id)
{
    if(id != -1)
    {
		if(IsValidDynamicMapIcon(bData[id][bIcon])) DestroyDynamicMapIcon(bData[id][bIcon]);
        if(IsValidDynamic3DTextLabel(bData[id][bLabel])) DestroyDynamic3DTextLabel(bData[id][bLabel]);
        if(IsValidDynamicPickup(bData[id][bPickup][0])) DestroyDynamicPickup(bData[id][bPickup][0]);
		if(IsValidDynamicPickup(bData[id][bPickup][1])) DestroyDynamicPickup(bData[id][bPickup][1]);
		if(IsValidDynamic3DTextLabel(bData[id][bLabelPoint])) DestroyDynamic3DTextLabel(bData[id][bLabelPoint]);
        if(IsValidDynamicPickup(bData[id][bPickPoint])) DestroyDynamicPickup(bData[id][bPickPoint]);
		if(IsValidDynamicCP(bData[id][bCP][0])) DestroyDynamicCP(bData[id][bCP][0]);
		if(IsValidDynamicCP(bData[id][bCP][1])) DestroyDynamicCP(bData[id][bCP][1]);
		if(IsValidDynamic3DTextLabel(BussinesGarage[id][GarageText])) DestroyDynamic3DTextLabel(BussinesGarage[id][GarageText]);
        if(IsValidDynamicPickup(BussinesGarage[id][GaragePick])) DestroyDynamicPickup(BussinesGarage[id][GaragePick]);

        static
        string[255], tstr[128];
		
		new type[128];
		if(bData[id][bType] == 1) type= "Fast Food";
		else if(bData[id][bType] == 2) type= "Market";
		else if(bData[id][bType] == 3) type= "Clothes";
		else if(bData[id][bType] == 4) type= "Sportshop";
		else if(bData[id][bType] == 5) type= "Electronic";
		else if(bData[id][bType] == 6) type= "GYM";
		else if(bData[id][bType] == 7) type= "Ammunation";
		else type= "Unknown";
		format(tstr, 128, "{00FFFF}[id:%d]\n"LG_E"Business buy point\n"WHITE_E"use /buy here", id);
		
        if(strcmp(bData[id][bOwner], "-")) {
			format(string, sizeof(string), "{00FFFF}[id:%d]\n{00FF00}%s{FFFFFF}\nOwner: {FFFF00}%s", id, ReplaceString(bData[id][bName]), bData[id][bOwner]);
			
        } else {
            format(string, sizeof(string), "{00FFFF}[id:%d]\n{00D900}this businesses for sale!\n{FFFF00}Type: {FFFFFF}%s\n{FFFFFF}Price: {00FF00}%s\n{00D900}use '/buy' for buy this businesess", id, type, FormatMoney(bData[id][bPrice]), type);
        } 
		if(bData[id][bSegel] == 1) {
			format(string, sizeof(string), "{00FFFF}[id:%d]\n{FF0000}This businesses sealed by authority\nOwner: {FFFF00}%s", id, bData[id][bOwner]);
		}
		switch(bData[id][bType])
		{
			case 1: bData[id][bIcon] = CreateDynamicMapIcon(bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ], 50, 0, 0, 0, -1, MAP_ICON_STREAM_DISTANCE, MAPICON_LOCAL); // Fast Food
			case 2: bData[id][bIcon] = CreateDynamicMapIcon(bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ], 17, 0, 0, 0, -1, MAP_ICON_STREAM_DISTANCE, MAPICON_LOCAL); // Market
			case 3: bData[id][bIcon] = CreateDynamicMapIcon(bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ], 45, 0, 0, 0, -1, MAP_ICON_STREAM_DISTANCE, MAPICON_LOCAL); // Clothes
			case 4: bData[id][bIcon] = CreateDynamicMapIcon(bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ], 25, 0, 0, 0, -1, MAP_ICON_STREAM_DISTANCE, MAPICON_LOCAL); // Sportshop
			case 5: bData[id][bIcon] = CreateDynamicMapIcon(bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ], 35, 0, 0, 0, -1, MAP_ICON_STREAM_DISTANCE, MAPICON_LOCAL); // Electronic
			case 6: bData[id][bIcon] = CreateDynamicMapIcon(bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ], 54, 0, 0, 0, -1, MAP_ICON_STREAM_DISTANCE, MAPICON_LOCAL); // GYM
			case 7: bData[id][bIcon] = CreateDynamicMapIcon(bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ], 6, 0, 0, 0, -1, MAP_ICON_STREAM_DISTANCE, MAPICON_LOCAL); // Ammunation
		}
		bData[id][bPickPoint] = CreateDynamicPickup(1274, 23, bData[id][bPointX], bData[id][bPointY], bData[id][bPointZ]+0.2, id, bData[id][bInt], _, 4);
		bData[id][bPickup][0] = CreateDynamicPickup(19133, 23, bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ]+0.2, 0, 0, _, 8.0);
		bData[id][bPickup][1] = CreateDynamicPickup(19133, 23, bData[id][bIntposX], bData[id][bIntposY], bData[id][bIntposZ]+0.2, id, bData[id][bInt], _, 8.0);

		bData[id][bLabelPoint] = CreateDynamic3DTextLabel(tstr, COLOR_YELLOW, bData[id][bPointX], bData[id][bPointY], bData[id][bPointZ]+0.5, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, id, bData[id][bInt]);
		bData[id][bCP][0] = CreateDynamicCP(bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ], 1, 0, 0, _, 3.0);
		bData[id][bCP][1] = CreateDynamicCP(bData[id][bIntposX], bData[id][bIntposY], bData[id][bIntposZ], 1, id, bData[id][bInt], _, 3.0);
		bData[id][bLabel] = CreateDynamic3DTextLabel(string, COLOR_GREEN, bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ]+0.5, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0);
	
		if(BussinesGarage[id][BizGarage] > 0)
		{
			new str[212];
			format(str, sizeof(str), "{00FFFF}[ID:%d]\n"GREEN_E"Bussines Garage\n"WHITE_E"Use '/storeveh' to store vehicle\nUse '/takeveh' to take vehicle\nUse '/switchveh' to switch vehicle", id);
			BussinesGarage[id][GarageText] = CreateDynamic3DTextLabel(str, COLOR_GREEN, BussinesGarage[id][ExtPos][0], BussinesGarage[id][ExtPos][1], BussinesGarage[id][ExtPos][2]+0.5, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0);
			BussinesGarage[id][GaragePick] = CreateDynamicPickup(1239, 23, BussinesGarage[id][ExtPos][0], BussinesGarage[id][ExtPos][1], BussinesGarage[id][ExtPos][2], -1, -1);
		}
	}
    return 1;
}

function LoadBisnis()
{
    static bid;
	new str[586];
	
	new rows = cache_num_rows(), owner[128], name[128], bpname0[128], bpname1[128], bpname2[128], bpname3[128], bpname4[128], bpname5[128], bpname6[128], bpname7[128], bpname8[128], bpname9[128], bpname10[128], stream[128];
 	if(rows)
  	{
		for(new i; i < rows; i++)
		{
			cache_get_value_name_int(i, "ID", bid);
			cache_get_value_name(i, "owner", owner);
			format(bData[bid][bOwner], 128, owner);
			cache_get_value_name(i, "name", name);
			format(bData[bid][bName], 128, name);
			cache_get_value_name_int(i, "type", bData[bid][bType]);
			cache_get_value_name_int(i, "price", bData[bid][bPrice]);
			cache_get_value_name_float(i, "extposx", bData[bid][bExtposX]);
			cache_get_value_name_float(i, "extposy", bData[bid][bExtposY]);
			cache_get_value_name_float(i, "extposz", bData[bid][bExtposZ]);
			cache_get_value_name_float(i, "extposa", bData[bid][bExtposA]);
			cache_get_value_name_float(i, "intposx", bData[bid][bIntposX]);
			cache_get_value_name_float(i, "intposy", bData[bid][bIntposY]);
			cache_get_value_name_float(i, "intposz", bData[bid][bIntposZ]);
			cache_get_value_name_float(i, "intposa", bData[bid][bIntposA]);
			cache_get_value_name_int(i, "bint", bData[bid][bInt]);
			cache_get_value_name_int(i, "money", bData[bid][bMoney]);
			cache_get_value_name_int(i, "locked", bData[bid][bLocked]);
			cache_get_value_name_int(i, "prod", bData[bid][bProd]);
			cache_get_value_name_int(i, "bprice0", bData[bid][bP][0]);
			cache_get_value_name_int(i, "bprice1", bData[bid][bP][1]);
			cache_get_value_name_int(i, "bprice2", bData[bid][bP][2]);
			cache_get_value_name_int(i, "bprice3", bData[bid][bP][3]);
			cache_get_value_name_int(i, "bprice4", bData[bid][bP][4]);
			cache_get_value_name_int(i, "bprice5", bData[bid][bP][5]);
			cache_get_value_name_int(i, "bprice6", bData[bid][bP][6]);
			cache_get_value_name_int(i, "bprice7", bData[bid][bP][7]);
			cache_get_value_name_int(i, "bprice8", bData[bid][bP][8]);
			cache_get_value_name_int(i, "bprice9", bData[bid][bP][9]);
			cache_get_value_name_int(i, "bprice10", bData[bid][bP][10]);
			cache_get_value_name_float(i, "pointx", bData[bid][bPointX]);
			cache_get_value_name_float(i, "pointy", bData[bid][bPointY]);
			cache_get_value_name_float(i, "pointz", bData[bid][bPointZ]);
			cache_get_value_name_int(i, "visit", bData[bid][bLastVisited]);
			cache_get_value_name_int(i, "restock", bData[bid][bRestock]);
			cache_get_value_name_int(i, "segel", bData[bid][bSegel]);
			cache_get_value_name(i, "bpname0", bpname0);
			format(bData[bid][bPName0], 128, bpname0);
			cache_get_value_name(i, "bpname1", bpname1);
			format(bData[bid][bPName1], 128, bpname1);
			cache_get_value_name(i, "bpname2", bpname2);
			format(bData[bid][bPName2], 128, bpname2);
			cache_get_value_name(i, "bpname3", bpname3);
			format(bData[bid][bPName3], 128, bpname3);
			cache_get_value_name(i, "bpname4", bpname4);
			format(bData[bid][bPName4], 128, bpname4);
			cache_get_value_name(i, "bpname5", bpname5);
			format(bData[bid][bPName5], 128, bpname5);
			cache_get_value_name(i, "bpname6", bpname6);
			format(bData[bid][bPName6], 128, bpname6);
			cache_get_value_name(i, "bpname7", bpname7);
			format(bData[bid][bPName7], 128, bpname7);
			cache_get_value_name(i, "bpname8", bpname8);
			format(bData[bid][bPName8], 128, bpname8);
			cache_get_value_name(i, "bpname9", bpname9);
			format(bData[bid][bPName9], 128, bpname9);
			cache_get_value_name(i, "bpname10", bpname10);
			format(bData[bid][bPName10], 128, bpname10);
			cache_get_value_name(i, "stream", stream);
			format(bData[bid][bStream], 128, stream);
			cache_get_value_name_int(i, "extvw", bData[bid][bExtVw]);
			cache_get_value_name_int(i, "extint", bData[bid][bExtInt]);
			cache_get_value(i, "drivethru", str);
      		sscanf(str, "p<|>fff", bData[bid][bDriveThru][0], bData[bid][bDriveThru][1], bData[bid][bDriveThru][2]);
			cache_get_value(i, "garagepos", str);
      		sscanf(str, "p<|>fffd", BussinesGarage[bid][ExtPos][0], BussinesGarage[bid][ExtPos][1], BussinesGarage[bid][ExtPos][2], BussinesGarage[bid][BizGarage]);
			cache_get_value(i, "bussinesstock", str);
      		sscanf(str, "p<|>ddddddddddd", 
			BusinnesProduct[bid][BussinesProduct][0],
			BusinnesProduct[bid][BussinesProduct][1],
			BusinnesProduct[bid][BussinesProduct][2],
			BusinnesProduct[bid][BussinesProduct][3],
			BusinnesProduct[bid][BussinesProduct][4],
			BusinnesProduct[bid][BussinesProduct][5],
			BusinnesProduct[bid][BussinesProduct][6],
			BusinnesProduct[bid][BussinesProduct][7],
			BusinnesProduct[bid][BussinesProduct][8],
			BusinnesProduct[bid][BussinesProduct][9],
			BusinnesProduct[bid][BussinesProduct][10]);

			bData[bid][BiznisID] = bid;
			Bisnis_Refresh(bid);
			Iter_Add(Bisnis, bid);
		}
		printf("*** [Database: Loaded] bisnis data (%d count).", rows);
	}
}

Business_IsEmployee(playerid, bizid) {
	new str[128], Cache: cache;
	format(str, sizeof(str), "SELECT * FROM `business_employee` WHERE `Name`='%s' AND `Biz`='%d'", ReturnName(playerid), bData[bizid][BiznisID]);
	cache = mysql_query(g_SQL, str);
	new result = cache_num_rows();
	cache_delete(cache);
	return result;
}

BusinessEmployee_Add(playerid, bizid)
{
	new str[128];
	format(str, sizeof(str), "INSERT INTO `business_employee` SET `Name`='%s', `Biz`='%d', `Time`=UNIX_TIMESTAMP()", ReturnName(playerid), bData[bizid][BiznisID]);
	mysql_tquery(g_SQL, str);
	return 1;
}

BusinessEmployee_Remove(id)
{
	new query[200];
	format(query,sizeof(query),"DELETE FROM `business_employee` WHERE `ID`='%d'", id);
	mysql_tquery(g_SQL, query);
	return 1;
}

BusinessEmployee_RemoveAll(bizid)
{
	new query[200];
	format(query,sizeof(query),"DELETE FROM `business_employee` WHERE `Biz`='%d'", bData[bizid][BiznisID]);
	mysql_tquery(g_SQL, query);
	return 1;
}

BusinessEmployee_GetCount(bizid)
{
	new query[144], Cache: check, count;
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `business_employee` WHERE `Biz` = '%d'", bData[bizid][BiznisID]);
	check = mysql_query(g_SQL, query);
	new result = cache_num_rows();
	if(result) {
		for(new i; i != result; i++) {
			count++;
		}
	}
	cache_delete(check);
	return count;
}

Business_ShowEmployee(playerid, id, type = 0)
{
	new query[255], Cache: cache;
	format(query, sizeof(query), "SELECT * FROM `business_employee` WHERE `Biz`='%d'", bData[id][BiznisID]);
	cache = mysql_query(g_SQL, query);

	if(!cache_num_rows()) return Error(playerid, "There are no one employee for this business.");
	
	format(query, sizeof(query), "#\tName\tDate Added\n");
	for(new i; i < cache_num_rows(); i++) {
		new biz,
            time,
			name[24];

        cache_get_value_int(i, "ID", biz);
		cache_get_value_int(i, "Time", time);
		cache_get_value(i, "Name", name, sizeof(name));
		format(query, sizeof(query), "%s%d\t%s\t%s\n", query, biz, name, experieddate(time,3));
	}
	if (!type)
		Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, "Business Employee", query, "Close", "");
	else
		Dialog_Show(playerid, Business_RemoveEmployee, DIALOG_STYLE_TABLIST_HEADERS, "Remove Employee", query, "Remove", "Close");

	cache_delete(cache);
	return 1;
}

Business_Inside(playerid)
{
	static bid;
	bData[bid][BiznisID] = bid;

    if(pData[playerid][pInBiz] != -1)
    {
        foreach (new i : Bisnis) if(bid == pData[playerid][pInBiz] && GetPlayerInterior(playerid) == bData[i][bInt] && GetPlayerVirtualWorld(playerid) > 0) {
            return i;
        }
    }
    return -1;
}