
task SystemUpdate[900000]()
{
    for (new id = 0; id != MAX_BISNIS; id ++) if(strcmp(bData[id][bOwner], "-")) {
        if ((gettime()-bData[id][bLastVisited]) > (AUTOSELLDAYS * 86400)) {
            format(bData[id][bOwner], MAX_PLAYER_NAME, "-");
            bData[id][bLastVisited] = 0;
            bData[id][bProd] = 0;
            bData[id][bPrice] = 99999999;
            BusinessEmployee_RemoveAll(id);

            new query[256];
            format(query, sizeof(query), "INSERT INTO `auction_queue` SET ID = '%d', Property = '1', Location = '%s', Date = UNIX_TIMESTAMP(), Type = '0'", id, GetLocation(bData[id][bExtposX], bData[id][bExtposY], bData[id][bExtposZ]));
            mysql_tquery(g_SQL, query);

            Bisnis_Refresh(id);
            Bisnis_Save(id);
        }
    }

    foreach (new id : Houses) if(strcmp(hData[id][hOwner], "-"))
    {
        if((gettime()-hData[id][hLastVisited]) > (AUTOSELLDAYS * 86400)) {
            hData[id][hMoney] = 0;
            hData[id][hLocked] = 1;
            hData[id][hLastVisited] = 0;
            hData[id][houseBuilder] = 0;
            hData[id][houseBuilderTime] = 0;
            hData[id][hPrice] = 99999999;
            for (new j = 0; j < 10; j ++) {
                hData[id][hWeapon][j] = 0;
                hData[id][hAmmo][j] = 0;
            }

            House_RemoveFurniture(id);
            HouseStructure_DeleteAll(id);

            new query[1024];
            format(query, sizeof(query), "INSERT INTO `auction_queue` SET ID='%d', Property='2', Location='%s', Date = UNIX_TIMESTAMP(), Type = '%d'", id, GetLocation(hData[id][hExtposX], hData[id][hExtposY], hData[id][hExtposZ]));
            mysql_tquery(g_SQL, query);

            format(hData[id][hOwner], MAX_PLAYER_NAME, "-");

            House_Refresh(id);
            House_Save(id);
        }
    }

    foreach (new id : FlatRooms) if(FlatRoom[id][flatRoomOwner]) {
        if((gettime()-FlatRoom[id][flatRoomLastVisited]) > (AUTOSELLDAYS * 86400)) {
            FlatRoom[id][flatRoomOwner] = 0;
            FlatRoom[id][flatRoomMoney] = 0;
            FlatRoom[id][flatRoomLocked] = 1;
            FlatRoom[id][flatRoomBuilder] = 0;
            FlatRoom[id][flatRoomBuilderTime] = 0;
            FlatRoom[id][flatRoomPrice] = 99999999;

            FlatFurniture_DeleteAll(id);
            Flat_RemoveAllItems(id);
            FlatStructure_DeleteAll(id, true);

            new query[1024], location[24], flatBase = Flat_ReturnID(id);

            if (flatBase != -1) {
                FlatRoom_GetAddress(id, location);
                format(query, sizeof(query), "INSERT INTO `auction_queue` SET ID='%d', Property='6', Location='%s', Date = UNIX_TIMESTAMP(), Type = '%d'", id, location, FlatData[flatBase][flatType]);
                mysql_tquery(g_SQL, query);

                FlatRoom_Refresh(id);
                FlatRoom_Save(id);
            }
        }
    }
    // foreach (new i : WORKSHOPS) if(strcmp(wData[i][wOwner], "-")) {
    //     if ((gettime()-wData[i][wLastVisited]) > (AUTOSELLDAYS * 86400)) {
    //         format(wData[i][wOwner],MAX_PLAYER_NAME,"-");
    //         wData[i][wComponent] = 0;
    //         wData[i][wMoney] = 0;
    //         wData[i][wStatus] = 0;
    //         wData[i][wPrice] = 99999999;
            
    //         new query[256];

    //         mysql_format(g_SQL, query, sizeof(query), "SELECT reg_id FROM players WHERE workshop='%d'", i);
	//         mysql_tquery(g_SQL, query, "aSellWorkshop");
            
    //         format(query, sizeof(query), "INSERT INTO `auction_queue` SET ID='%d', Property='4', Location='%s', Date=UNIX_TIMESTAMP(), Type='0'", i, GetLocation(wData[i][wExtposX], wData[i][wExtposY], wData[i][wExtposZ]));
    //         mysql_tquery(g_SQL, query);

    //         Workshop_Refresh(i);
    //         Workshop_Save(i);
    //     }
    // }
}

// function aSellWorkshop()
// {
// 	if(cache_num_rows() > 1)
// 	{
// 	    new RegID;
// 	    new obannedbyirwan = -1;
// 		cache_get_value_index_int(0, 0, RegID);
// 		new query[512];
// 		mysql_format(g_SQL, query, sizeof(query), "UPDATE players SET workshop=%d, workshoprank='%d' WHERE reg_id=%d", obannedbyirwan, obannedbyirwan, RegID);
// 		mysql_tquery(g_SQL, query);
// 	}
// 	return 1;
// }
