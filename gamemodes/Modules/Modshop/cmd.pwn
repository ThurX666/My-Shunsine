
CMD:myov(playerid, params[])
{
    new 
		vid = GetPlayerVehicleID(playerid),
        string[1024],
        count
	;
	if(!IsPlayerInAnyVehicle(playerid))
        return Error(playerid, "You need to be driver to use this command.");

    if(IsPlayerInRangeOfPoint(playerid, 4.0, 1808.23, -2028.51, 13.72) || IsPlayerInRangeOfPoint(playerid, 4.0, 1799.39, -2028.54, 13.72) || IsPlayerInRangeOfPoint(playerid, 4.0, 1790.63, -2028.55, 13.72) || IsPlayerInRangeOfPoint(playerid, 4.0, 1779.09, -2042.56, 13.72)) //
    {
        foreach(new vehid : PVehicles)
        {
            if(vid == pvData[vehid][cVeh]) 
            { 
                if(pvData[vehid][cOwner] == pData[playerid][pID])
                {
                    if(GetEngineStatus(GetPlayerVehicleID(playerid)))
                        return Error(playerid, "Turn off vehicle engine first.");
                    format(string,sizeof(string),"Slot\tMod Type\tModel\n");
                    if(pData[playerid][pVip] > 1)
                    {
                        for (new i = 0; i < MAX_VEHICLE_OBJECT; i++)
                        {
                            if(VehicleObjects[vehid][i][vehObjectExists])
                            {
                                if(VehicleObjects[vehid][i][vehObjectType] == OBJECT_TYPE_BODY)
                                {
                                    format(string,sizeof(string),"%s%d\t"GREEN_E"Mod\t"WHITE_E"%s\n", string, i, GetVehObjectNameByModel(VehicleObjects[vehid][i][vehObjectModel]));
                                }
                                else if(VehicleObjects[vehid][i][vehObjectType] == OBJECT_TYPE_TEXT)
                                {
                                    format(string,sizeof(string),"%s%d\t"GREEN_E"Sticker\t"WHITE_E"%s\n", string, i, VehicleObjects[vehid][i][vehObjectText]);
                                }
                                else if(VehicleObjects[vehid][i][vehObjectType] == OBJECT_TYPE_LIGHT)
                                {
                                    format(string,sizeof(string),"%s%d\t"YELLOW_E"Light\t"WHITE_E"Spot Light\n", string, i);
                                }
                                else if(VehicleObjects[vehid][i][vehObjectType] == OBJECT_TYPE_PLATE)
                                {
                                    format(string,sizeof(string),"%s%d\t"AQUA_E"Plate\t"WHITE_E"(number plate)\n", string, i);
                                }
                                else if(VehicleObjects[vehid][i][vehObjectType] == OBJECT_TYPE_NEON)
                                {
                                    format(string,sizeof(string),"%s%d\t"YELLOW_E"Light\t"WHITE_E"Neon Tube\n", string, i);
                                }
                            }
                            else
                            {
                                format(string, sizeof(string), "%sNew\tMod\n", string);
                            }
                            if (count < 10)
                            {
                                ListedVehObject[playerid][count] = i;
                                count = count + 1;
                            }
                        }
                    }
                    else
                    {
                        for (new i = 0; i < 3; i ++)
                        {
                            if(VehicleObjects[vehid][i][vehObjectExists])
                            {
                                if(VehicleObjects[vehid][i][vehObjectType] == OBJECT_TYPE_BODY)
                                {
                                    format(string,sizeof(string),"%s%d\t"GREEN_E"Mod\t"WHITE_E"%s\n", string, i, GetVehObjectNameByModel(VehicleObjects[vehid][i][vehObjectModel]));
                                }
                                else if(VehicleObjects[vehid][i][vehObjectType] == OBJECT_TYPE_TEXT)
                                {
                                    format(string,sizeof(string),"%s%d\t"GREEN_E"Sticker\t"WHITE_E"%s\n", string, i, VehicleObjects[vehid][i][vehObjectText]);
                                }
                                else if(VehicleObjects[vehid][i][vehObjectType] == OBJECT_TYPE_LIGHT)
                                {
                                    format(string,sizeof(string),"%s%d\t"YELLOW_E"Light\t"WHITE_E"Spot Light\n", string, i);
                                }
                                else if(VehicleObjects[vehid][i][vehObjectType] == OBJECT_TYPE_PLATE)
                                {
                                    format(string,sizeof(string),"%s%d\t"AQUA_E"Plate\t"WHITE_E"(number plate)\n", string, i);
                                }
                                else if(VehicleObjects[vehid][i][vehObjectType] == OBJECT_TYPE_NEON)
                                {
                                    format(string,sizeof(string),"%s%d\t"YELLOW_E"Light\t"WHITE_E"Neon Tube\n", string, i);
                                }
                            }
                            else
                            {
                                format(string, sizeof(string), "%sNew\tMod\n", string);
                            }
                            if (count < 10)
                            {
                                ListedVehObject[playerid][count] = i;
                                count = count + 1;
                            }
                        }
                    }

                    if(!count) 
                    {
                        Error(playerid, "You don't have vehicle toys installed!");
                    }
                    else 
                    {
                        Player_EditVehicleObject[playerid] = vehid;
                        Dialog_Show(playerid, EditingVehObject, DIALOG_STYLE_TABLIST_HEADERS, "Modshop: List", string, "Select","Exit");
                    }
                }
                else return Error(playerid, "This isn't owned by you");
            }
        }
    }    
    else return Error(playerid, "You're not in a modshop.");
    return 1;
}
