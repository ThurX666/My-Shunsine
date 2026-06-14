
Dialog:LocationAdd(playerid, response, listitem, inputtext[]) {
    if(response) {
        switch(listitem) {
            case 0: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 0;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 1: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 1;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 2: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 2;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 3: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 3;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 4: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 4;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 5: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 5;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 6: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 6;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 7: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 7;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 8: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 8;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 9: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 9;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 10: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 10;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 11: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 11;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 12: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 12;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
            case 13: {
                new id = Iter_Free(Locations);
                if(id == -1) return Error(playerid, "You can't create a location anymore!");
                GetPlayerPos(playerid, Location[id][locPos][0], Location[id][locPos][1], Location[id][locPos][2]);
                GetPlayerFacingAngle(playerid, Location[id][locPos][3]);
                Location[id][locInterior] = GetPlayerInterior(playerid);
                Location[id][locWorld] = GetPlayerVirtualWorld(playerid);
                Location[id][locType] = 13;
                Iter_Add(Locations, id);
                mysql_tquery(g_SQL, sprintf("INSERT INTO `location` (`Type`) VALUES ('%d')",Location[id][locType]), "OnLocationAdd", "d", id);
                SendCustomMessage(playerid, "LOCATION", "You have created a "AQUA_E"%s", inputtext);
            }
        }
    }
	return 1;
}
