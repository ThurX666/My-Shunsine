
function OnLocationAdd(id) {
    if (!Iter_Contains(Locations, id))
        return 0;

    Location[id][locID] = cache_insert_id();
    Location_Save(id);
    Location_Refresh(id);
    return 1;
}

function Location_Load() {
    new rows = cache_num_rows(), str[65];
    for (new i = 0; i < rows; i ++) {
        Iter_Add(Locations, i);

        cache_get_value_int(i, "ID", Location[i][locID]);
        cache_get_value_int(i, "Type", Location[i][locType]);
        cache_get_value(i, "Position", str);
        sscanf(str, "p<|>ffff", Location[i][locPos][0], Location[i][locPos][1], Location[i][locPos][2], Location[i][locPos][3]);
        cache_get_value_int(i, "Interior", Location[i][locInterior]);
        cache_get_value_int(i, "World", Location[i][locWorld]);
        Location_Refresh(i);
    }
    printf("*** [Database: Loaded] location data loaded (%d count)", rows);
    return 1;
}

Location_Refresh(i) {
    new strings[512];
    if (!Iter_Contains(Locations, i)) return 0;
    if(IsValidDynamic3DTextLabel(Location[i][locLabel])) DestroyDynamic3DTextLabel(Location[i][locLabel]);
    if(IsValidDynamicPickup(Location[i][locPickup])) DestroyDynamicPickup(Location[i][locPickup]);
    switch(Location[i][locType]) {
        case 0: {
            format(strings, sizeof(strings), "{00FFFF}Static vehicle spawnpoint\n"WHITE_E"Use "YELLOW_E"'/spawnveh' "WHITE_E"to spawn in static vehicle\n"WHITE_E"Use "YELLOW_E"'/despawnveh' "WHITE_E"to despawn your current static vehicle");
            Location[i][locPickup] = CreateDynamicPickup(1239, 23, Location[i][locPos][0], Location[i][locPos][1], Location[i][locPos][2], Location[i][locWorld], Location[i][locInterior]);
        }
        case 1: {
            format(strings, sizeof(strings), "{00FFFF}Plate Registration\n"WHITE_E"Use "YELLOW_E"'/buyplate' "WHITE_E"to register your vehicle plate number\nCoast: "GREEN_E"$25.00");
            Location[i][locPickup] = CreateDynamicPickup(1239, 23, Location[i][locPos][0], Location[i][locPos][1], Location[i][locPos][2], Location[i][locWorld], Location[i][locInterior]);
        }
        case 3: {
            format(strings, sizeof(strings), "{00FFFF}Ticket Payment\n"WHITE_E"Use "YELLOW_E"'/payticket' "WHITE_E"to pay any issued ticket\n"WHITE_E"Use "YELLOW_E"'/unlocktire' "WHITE_E"to remove tirelock from a vehicle");
            Location[i][locPickup] = CreateDynamicPickup(1239, 23, Location[i][locPos][0], Location[i][locPos][1], Location[i][locPos][2], Location[i][locWorld], Location[i][locInterior]);
        }
        case 4: {
            format(strings, sizeof(strings), "{00FFFF}Bank\n"WHITE_E"Use "YELLOW_E"'/deposit' "WHITE_E"to deposit money into the bank\n"WHITE_E"Use "YELLOW_E"'/withdraw' "WHITE_E"to withdraw money in the bank");
            Location[i][locPickup] = CreateDynamicPickup(1274, 23, Location[i][locPos][0], Location[i][locPos][1], Location[i][locPos][2], Location[i][locWorld], Location[i][locInterior]);
        }
        case 5: {
            format(strings, sizeof(strings), "{00FFFF}Insurance Company\n"YELLOW_E"'/buyinsurance' "WHITE_E"to buy vehicle insurance\n"YELLOW_E"'/claiminsurance' "WHITE_E"to claim insurance");
            Location[i][locPickup] = CreateDynamicPickup(1239, 23, Location[i][locPos][0], Location[i][locPos][1], Location[i][locPos][2], Location[i][locWorld], Location[i][locInterior]);
        }
        case 8: {
            format(strings, sizeof(strings), "{00FFFF}[Bike Dealer]\n"YELLOW_E"/buyvehicle "WHITE_E"to purchase a bicycle");
            Location[i][locPickup] = CreateDynamicPickup(1239, 23, Location[i][locPos][0], Location[i][locPos][1], Location[i][locPos][2], Location[i][locWorld], Location[i][locInterior]);
        }
        case 10: {
            format(strings, sizeof(strings), "{00FFFF}[Boat Dealership]\n"YELLOW_E"/buyboat "WHITE_E"to purchase a boat");
            Location[i][locPickup] = CreateDynamicPickup(1239, 23, Location[i][locPos][0], Location[i][locPos][1], Location[i][locPos][2], Location[i][locWorld], Location[i][locInterior]);
        }
        case 12: {
            format(strings, sizeof(strings), "San Andreas Network\n"WHITE_E"Use "YELLOW_E"'/ad' "WHITE_E"to create advertisement");
            Location[i][locPickup] = CreateDynamicPickup(1239, 23, Location[i][locPos][0], Location[i][locPos][1], Location[i][locPos][2], Location[i][locWorld], Location[i][locInterior]);
        }
        case 13: {
            format(strings, sizeof(strings), "[ID: %d]\nSan Andreas Police Department\n"GREEN_E"SAPD Central Armoury\n"WHITE_E"Stock: "YELLOW_E"%d/1000\n"GREEN_E"SAPD Central Ammo\n"WHITE_E"Stock: "YELLOW_E"%d/10000\n"WHITE_E"Use "YELLOW_E"'/armoury' "WHITE_E"to acces armoury\n"WHITE_E"Use "YELLOW_E"'/sapdammo' "WHITE_E"to acces ammo JHP", i, SAPDArmoury, SAPDAmmo);
            Location[i][locPickup] = CreateDynamicPickup(1242, 23, Location[i][locPos][0], Location[i][locPos][1], Location[i][locPos][2], Location[i][locWorld], Location[i][locInterior]);
        }
    }
    Location[i][locLabel] = CreateDynamic3DTextLabel(strings, -1, Location[i][locPos][0], Location[i][locPos][1], Location[i][locPos][2], 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, Location[i][locWorld], Location[i][locInterior]);
    return 1;
}

Location_Save(id) {
    if (!Iter_Contains(Locations, id))
        return 0;
    
    new query[256];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `location` SET `Type`='%d', `Position`='%.2f|%.2f|%.2f|%.2f', `Interior`='%d', `World`='%d' WHERE `ID`='%d'",
    Location[id][locType],
    Location[id][locPos][0],
    Location[id][locPos][1],
    Location[id][locPos][2],
    Location[id][locPos][3],
    Location[id][locInterior],
    Location[id][locWorld],
    Location[id][locID]);
    return mysql_tquery(g_SQL, query);
}
