
public OnPlayerSelectionMenuResponse(playerid, extraid, response, listitem, modelid)
{
	switch(extraid)
	{
        case MODEL_SELECTION_SAPDMale:
        {
            if(response)
	        {
                pData[playerid][pFacSkin] = modelid;
                SetPlayerSkin(playerid, modelid);
                Servers(playerid, ""YELLOW_E"You have changed your skin duty");
            }    
        }
        case MODEL_SELECTION_SAPDMale03DL:
        {
            if(response)
	        {
                pData[playerid][pFacSkin] = modelid;
                SetPlayerSkin(playerid, modelid);
                Servers(playerid, ""YELLOW_E"You have changed your skin duty");
            }    
        }
        case MODEL_SELECTION_SAPDFemale:
        {
            if(response)
	        {
                pData[playerid][pFacSkin] = modelid;
                SetPlayerSkin(playerid, modelid);
                Servers(playerid, ""YELLOW_E"You have changed your skin duty");
                pData[playerid][pUndercover] = (pData[playerid][pUndercover])?(0):(1);
                switch(pData[playerid][pUndercover])
                {
                    case 0:
                    {
                        SetFactionColor(playerid);
                    }
                    case 1:
                    {
                        SetPlayerColor(playerid, COLOR_WHITE);
                        if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                            UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s {ffffff}(%d)", ReturnName(playerid), playerid)));
                    }
                }
                SendCustomMessage(playerid, "DUTY","You're %s undercover",(pData[playerid][pUndercover])?("now"):("now no longer"));
            }    
        }
        case MODEL_SELECTION_SAPDWar:
        {
            if(response)
	        {
                pData[playerid][pFacSkin] = modelid;
                SetPlayerSkin(playerid, modelid);
                Servers(playerid, ""YELLOW_E"You have changed your skin duty");
                pData[playerid][pUndercover] = (pData[playerid][pUndercover])?(0):(1);
                switch(pData[playerid][pUndercover])
                {
                    case 0:
                    {
                        SetFactionColor(playerid);
                    }
                    case 1:
                    {
                        SetPlayerColor(playerid, COLOR_WHITE);
                        if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                            UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s (%d)", ReturnName2(playerid), playerid)));
                    }
                }
                SendCustomMessage(playerid, "DUTY","You're %s undercover",(pData[playerid][pUndercover])?("now"):("now no longer"));
            }    
        }
        case MODEL_SELECTION_SAMDMale:
        {
            if(response)
	        {
                pData[playerid][pFacSkin] = modelid;
                SetPlayerSkin(playerid, modelid);
                Servers(playerid, ""YELLOW_E"You have changed your skin duty");
            }    
        }
        case MODEL_SELECTION_SAMDFemale:
        {
            if(response)
	        {
                pData[playerid][pFacSkin] = modelid;
                SetPlayerSkin(playerid, modelid);
                Servers(playerid, ""YELLOW_E"You have changed your skin duty");
            }    
        }
        case MODEL_SELECTION_SANEWSMale:
        {
            if(response)
	        {
                pData[playerid][pFacSkin] = modelid;
                SetPlayerSkin(playerid, modelid);
                Servers(playerid, ""YELLOW_E"You have changed your skin duty");
            }    
        }
        case MODEL_SELECTION_SANEWSFemale:
        {
            if(response)
	        {
                pData[playerid][pFacSkin] = modelid;
                SetPlayerSkin(playerid, modelid);
                Servers(playerid, ""YELLOW_E"You have changed your skin duty");
            }    
        }
        case MODEL_SELECTION_Waa:
	    {
	        if(response)
	        {
                new
                price = 5000,
                vehicleid
                ;

                if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
                    return Error(playerid, "You need to be inside vehicle as driver");

                vehicleid = Player_EditVehicleObject[playerid];

                if(vehicleid == -1)
                    return 0;

                Vehicle_ObjectAddObjects(playerid, vehicleid, modelid, OBJECT_TYPE_BODY);

                SendClientMessageEx(playerid, COLOR_ARWIN,"MODSHOP: "WHITE_E"You have purchased a {00FFFF}%s "WHITE_E"for "GREEN_E"$%s.", GetVehObjectNameByModel(modelid), FormatMoney(price));
            }
        } 
        case MODEL_SELECTION_Loco:
	    {
	        if(response)
	        {
                new
                price = 5000,
                vehicleid
                ;

                if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
                    return Error(playerid, "You need to be inside vehicle as driver");

                vehicleid = Player_EditVehicleObject[playerid];

                if(vehicleid == -1)
                    return 0;

                Vehicle_ObjectAddObjects(playerid, vehicleid, modelid, OBJECT_TYPE_BODY);

                SendClientMessageEx(playerid, COLOR_ARWIN,"MODSHOP: "WHITE_E"You have purchased a {00FFFF}%s "WHITE_E"for "GREEN_E"$%s.", GetVehObjectNameByModel(modelid), FormatMoney(price));
            }
        } 
        case MODEL_SELECTION_Transfender:
	    {
	        if(response)
	        {
                new
                price = 5000,
                vehicleid
                ;

                if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
                    return Error(playerid, "You need to be inside vehicle as driver");

                vehicleid = Player_EditVehicleObject[playerid];

                if(vehicleid == -1)
                    return 0;

                Vehicle_ObjectAddObjects(playerid, vehicleid, modelid, OBJECT_TYPE_BODY);

                SendClientMessageEx(playerid, COLOR_ARWIN,"MODSHOP: "WHITE_E"You have purchased a {00FFFF}%s "WHITE_E"for "GREEN_E"$%s.", GetVehObjectNameByModel(modelid), FormatMoney(price));
            }
        } 
        case MODEL_SELECTION_SkinFemale:
	    {
	        if(response)
	        {
                new bizid = pData[playerid][pInBiz], price;
                price = bData[bizid][bP][0];
                pData[playerid][pSkin] = modelid;
                SetPlayerSkin(playerid, modelid);
                GivePlayerMoneyEx(playerid, -price);
                
                bData[bizid][bProd]--;
                bData[bizid][bMoney] += Server_Percent(price);
                Server_AddPercent(price);
                Bisnis_Save(bizid);
                SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}Skin {ffffff}for {00ff00}$%s",FormatMoney(price));
            }
        }   
        case MODEL_SELECTION_SkinMale:
	    {
	        if(response)
	        {
                new bizid = pData[playerid][pInBiz], price;
                price = bData[bizid][bP][0];
                pData[playerid][pSkin] = modelid;
                SetPlayerSkin(playerid, modelid);
                GivePlayerMoneyEx(playerid, -price);
                
                bData[bizid][bProd]--;
                bData[bizid][bMoney] += Server_Percent(price);
                Server_AddPercent(price);
                Bisnis_Save(bizid);
                SendClientMessageEx(playerid, COLOR_ARWIN, "SHOP: {ffffff}You've purchased {ffff00}Skin {ffffff}for {00ff00}$%s",FormatMoney(price));
            }
        }        
        case MODEL_SELECTION_Barricade:
	    {
	        if(response)
	        {
                static
				Float:fX,Float:fY,Float:fZ;
			
                new index;
                if((index = Barricade_Create(playerid, 2, modelid, "-")) != -1) 
                {
                    SendFactionMessage(pData[playerid][pFaction], COLOR_RADIO, "RADIO: %s has dropped a roadblock at %s. (( ID %d ))", ReturnName(playerid), GetLocation(fX, fY, fZ), index);
                    pData[playerid][pEditingMode] = 2;
                    pData[playerid][pEditRoadblock] = index;
                    EditDynamicObject(playerid, BarricadeData[index][cadeObject]);
                }
                else 
                {
                    Error(playerid, "Roadblock sudah mencapai batas maksimal ("#MAX_DYNAMIC_ROADBLOCK" roadblock).");
                }
			}
	    }
        case MODEL_SELECTION_Motorcycle:
	    {
	        if(response)
	        {
                new Float: x, Float: y, Float: z, Float: a, harga, String[212];
                new d = GetPVarInt(playerid, "editingcd");
                GetPlayerPos(playerid,x,y,z);
                GetPlayerFacingAngle(playerid, a);
                if(CarDealershipInfo[d][cdTill] >= GetVehicleDealerCost(modelid))
                {
                    harga = GetVehicleDealerCost(modelid);
                }
                else
                {
                    SendClientMessageEx(playerid, COLOR_GRAD2, "Anda harus mempunyai modal sebesar "GREEN_E"$%s", FormatMoney(GetVehicleDealerCost(modelid)));
                    return 1;
                }
                if(modelid < 400||modelid > 611||modelid == 411||modelid == 415||modelid == 424||modelid == 434||modelid == 451||modelid == 494||modelid == 502||modelid == 503||modelid == 495||modelid == 506||modelid == 503)
                {
                    SendClientMessageEx(playerid, COLOR_GREY, "ID Kendaraan tidak diperbolehkan!");
                    return 1;
                }
                new cdvehicleid = pData[playerid][pListitems];
                DestroyDynamic3DTextLabel(CarDealershipInfo[d][cdVehicleLabel][cdvehicleid]);
                if(CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid] == 0.0 && CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid] == 0.0)
                {
                    new vehicleid = CreateVehicle(modelid, x, y, z, a, -1, -1, 6);
                    CarDealershipInfo[d][cdVehicleId][cdvehicleid] = vehicleid;
                    CarDealershipInfo[d][cdVehicleModel][cdvehicleid] = modelid;
                    CarDealershipInfo[d][cdVehicleCost][cdvehicleid] = harga;
                    CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid] = x;
                    CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid] = y;
                    CarDealershipInfo[d][cdVehicleSpawnZ][cdvehicleid] = z;
                    CarDealershipInfo[d][cdVehicleSpawnAngle][cdvehicleid] = a;
                    PutPlayerInVehicle(playerid, vehicleid, 0);
                    format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",cdvehicleid, GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[d][cdVehicleCost][cdvehicleid]));
                    CarDealershipInfo[d][cdVehicleLabel][cdvehicleid] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,5.0,INVALID_PLAYER_ID,vehicleid,1);
                }
                else
                {
                    new vehicleid = CreateVehicle(modelid, CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnZ][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnAngle][cdvehicleid], -1, -1, 6);
                    CarDealershipInfo[d][cdVehicleId][cdvehicleid] = vehicleid;
                    CarDealershipInfo[d][cdVehicleModel][cdvehicleid] = modelid;
                    CarDealershipInfo[d][cdVehicleCost][cdvehicleid] = harga;
                    
                    format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",cdvehicleid, GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[d][cdVehicleCost][cdvehicleid]));
                    CarDealershipInfo[d][cdVehicleLabel][cdvehicleid] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,5.0,INVALID_PLAYER_ID,vehicleid,1);
                }
                SendClientMessageEx(playerid, COLOR_YELLOW, "You have created Car Dealership ID %d for Dealership ID %d to your position.", cdvehicleid, d);
                SavecDealership(d);
                CarDealershipInfo[d][cdTill] -= harga;
            }
        }   
        case MODEL_SELECTION_SUV:
	    {
	        if(response)
	        {
                new Float: x, Float: y, Float: z, Float: a, harga, String[212];
                new d = GetPVarInt(playerid, "editingcd");
                GetPlayerPos(playerid,x,y,z);
                GetPlayerFacingAngle(playerid, a);
                if(CarDealershipInfo[d][cdTill] >= GetVehicleDealerCost(modelid))
                {
                    harga = GetVehicleDealerCost(modelid);
                }
                else
                {
                    SendClientMessageEx(playerid, COLOR_GRAD2, "Anda harus mempunyai modal sebesar "GREEN_E"$%s", FormatMoney(GetVehicleDealerCost(modelid)));
                    return 1;
                }
                if(modelid < 400||modelid > 611||modelid == 411||modelid == 415||modelid == 424||modelid == 434||modelid == 451||modelid == 494||modelid == 502||modelid == 503||modelid == 495||modelid == 506||modelid == 503)
                {
                    SendClientMessageEx(playerid, COLOR_GREY, "ID Kendaraan tidak diperbolehkan!");
                    return 1;
                }
                new cdvehicleid = pData[playerid][pListitems];
                DestroyDynamic3DTextLabel(CarDealershipInfo[d][cdVehicleLabel][cdvehicleid]);
                if(CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid] == 0.0 && CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid] == 0.0)
                {
                    new vehicleid = CreateVehicle(modelid, x, y, z, a, -1, -1, 6);
                    CarDealershipInfo[d][cdVehicleId][cdvehicleid] = vehicleid;
                    CarDealershipInfo[d][cdVehicleModel][cdvehicleid] = modelid;
                    CarDealershipInfo[d][cdVehicleCost][cdvehicleid] = harga;
                    CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid] = x;
                    CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid] = y;
                    CarDealershipInfo[d][cdVehicleSpawnZ][cdvehicleid] = z;
                    CarDealershipInfo[d][cdVehicleSpawnAngle][cdvehicleid] = a;
                    PutPlayerInVehicle(playerid, vehicleid, 0);
                    format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",cdvehicleid, GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[d][cdVehicleCost][cdvehicleid]));
                    CarDealershipInfo[d][cdVehicleLabel][cdvehicleid] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,5.0,INVALID_PLAYER_ID,vehicleid,1);
                }
                else
                {
                    new vehicleid = CreateVehicle(modelid, CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnZ][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnAngle][cdvehicleid], -1, -1, 6);
                    CarDealershipInfo[d][cdVehicleId][cdvehicleid] = vehicleid;
                    CarDealershipInfo[d][cdVehicleModel][cdvehicleid] = modelid;
                    CarDealershipInfo[d][cdVehicleCost][cdvehicleid] = harga;
                    
                    format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",cdvehicleid, GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[d][cdVehicleCost][cdvehicleid]));
                    CarDealershipInfo[d][cdVehicleLabel][cdvehicleid] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,5.0,INVALID_PLAYER_ID,vehicleid,1);
                }
                SendClientMessageEx(playerid, COLOR_YELLOW, "You have created Car Dealership ID %d for Dealership ID %d to your position.", cdvehicleid, d);
                SavecDealership(d);
                CarDealershipInfo[d][cdTill] -= harga;
            }
        }  
        case MODEL_SELECTION_PickupVehicles:
	    {
	        if(response)
	        {
                new Float: x, Float: y, Float: z, Float: a, harga, String[212];
                new d = GetPVarInt(playerid, "editingcd");
                GetPlayerPos(playerid,x,y,z);
                GetPlayerFacingAngle(playerid, a);
                if(CarDealershipInfo[d][cdTill] >= GetVehicleDealerCost(modelid))
                {
                    harga = GetVehicleDealerCost(modelid);
                }
                else
                {
                    SendClientMessageEx(playerid, COLOR_GRAD2, "Anda harus mempunyai modal sebesar "GREEN_E"$%s", FormatMoney(GetVehicleDealerCost(modelid)));
                    return 1;
                }
                if(modelid < 400||modelid > 611||modelid == 411||modelid == 415||modelid == 424||modelid == 434||modelid == 451||modelid == 494||modelid == 502||modelid == 503||modelid == 495||modelid == 506||modelid == 503)
                {
                    SendClientMessageEx(playerid, COLOR_GREY, "ID Kendaraan tidak diperbolehkan!");
                    return 1;
                }
                new cdvehicleid = pData[playerid][pListitems];
                DestroyDynamic3DTextLabel(CarDealershipInfo[d][cdVehicleLabel][cdvehicleid]);
                if(CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid] == 0.0 && CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid] == 0.0)
                {
                    new vehicleid = CreateVehicle(modelid, x, y, z, a, -1, -1, 6);
                    CarDealershipInfo[d][cdVehicleId][cdvehicleid] = vehicleid;
                    CarDealershipInfo[d][cdVehicleModel][cdvehicleid] = modelid;
                    CarDealershipInfo[d][cdVehicleCost][cdvehicleid] = harga;
                    CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid] = x;
                    CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid] = y;
                    CarDealershipInfo[d][cdVehicleSpawnZ][cdvehicleid] = z;
                    CarDealershipInfo[d][cdVehicleSpawnAngle][cdvehicleid] = a;
                    PutPlayerInVehicle(playerid, vehicleid, 0);
                    format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",cdvehicleid, GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[d][cdVehicleCost][cdvehicleid]));
                    CarDealershipInfo[d][cdVehicleLabel][cdvehicleid] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,5.0,INVALID_PLAYER_ID,vehicleid,1);
                }
                else
                {
                    new vehicleid = CreateVehicle(modelid, CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnZ][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnAngle][cdvehicleid], -1, -1, 6);
                    CarDealershipInfo[d][cdVehicleId][cdvehicleid] = vehicleid;
                    CarDealershipInfo[d][cdVehicleModel][cdvehicleid] = modelid;
                    CarDealershipInfo[d][cdVehicleCost][cdvehicleid] = harga;
                    
                    format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",cdvehicleid, GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[d][cdVehicleCost][cdvehicleid]));
                    CarDealershipInfo[d][cdVehicleLabel][cdvehicleid] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,5.0,INVALID_PLAYER_ID,vehicleid,1);
                }
                SendClientMessageEx(playerid, COLOR_YELLOW, "You have created Car Dealership ID %d for Dealership ID %d to your position.", cdvehicleid, d);
                SavecDealership(d);
                CarDealershipInfo[d][cdTill] -= harga;
            }
        }  
        case MODEL_SELECTION_Lowriders:
	    {
	        if(response)
	        {
                new Float: x, Float: y, Float: z, Float: a, harga, String[212];
                new d = GetPVarInt(playerid, "editingcd");
                GetPlayerPos(playerid,x,y,z);
                GetPlayerFacingAngle(playerid, a);
                if(CarDealershipInfo[d][cdTill] >= GetVehicleDealerCost(modelid))
                {
                    harga = GetVehicleDealerCost(modelid);
                }
                else
                {
                    SendClientMessageEx(playerid, COLOR_GRAD2, "Anda harus mempunyai modal sebesar "GREEN_E"$%s", FormatMoney(GetVehicleDealerCost(modelid)));
                    return 1;
                }
                if(modelid < 400||modelid > 611||modelid == 411||modelid == 415||modelid == 424||modelid == 434||modelid == 451||modelid == 494||modelid == 502||modelid == 503||modelid == 495||modelid == 506||modelid == 503)
                {
                    SendClientMessageEx(playerid, COLOR_GREY, "ID Kendaraan tidak diperbolehkan!");
                    return 1;
                }
                new cdvehicleid = pData[playerid][pListitems];
                DestroyDynamic3DTextLabel(CarDealershipInfo[d][cdVehicleLabel][cdvehicleid]);
                if(CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid] == 0.0 && CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid] == 0.0)
                {
                    new vehicleid = CreateVehicle(modelid, x, y, z, a, -1, -1, 6);
                    CarDealershipInfo[d][cdVehicleId][cdvehicleid] = vehicleid;
                    CarDealershipInfo[d][cdVehicleModel][cdvehicleid] = modelid;
                    CarDealershipInfo[d][cdVehicleCost][cdvehicleid] = harga;
                    CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid] = x;
                    CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid] = y;
                    CarDealershipInfo[d][cdVehicleSpawnZ][cdvehicleid] = z;
                    CarDealershipInfo[d][cdVehicleSpawnAngle][cdvehicleid] = a;
                    PutPlayerInVehicle(playerid, vehicleid, 0);
                    format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",cdvehicleid, GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[d][cdVehicleCost][cdvehicleid]));
                    CarDealershipInfo[d][cdVehicleLabel][cdvehicleid] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,5.0,INVALID_PLAYER_ID,vehicleid,1);
                }
                else
                {
                    new vehicleid = CreateVehicle(modelid, CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnZ][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnAngle][cdvehicleid], -1, -1, 6);
                    CarDealershipInfo[d][cdVehicleId][cdvehicleid] = vehicleid;
                    CarDealershipInfo[d][cdVehicleModel][cdvehicleid] = modelid;
                    CarDealershipInfo[d][cdVehicleCost][cdvehicleid] = harga;
                    
                    format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",cdvehicleid, GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[d][cdVehicleCost][cdvehicleid]));
                    CarDealershipInfo[d][cdVehicleLabel][cdvehicleid] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,5.0,INVALID_PLAYER_ID,vehicleid,1);
                }
                SendClientMessageEx(playerid, COLOR_YELLOW, "You have created Car Dealership ID %d for Dealership ID %d to your position.", cdvehicleid, d);
                SavecDealership(d);
                CarDealershipInfo[d][cdTill] -= harga;
            }
        }  
        case MODEL_SELECTION_Saloons:
	    {
	        if(response)
	        {
                new Float: x, Float: y, Float: z, Float: a, harga, String[212];
                new d = GetPVarInt(playerid, "editingcd");
                GetPlayerPos(playerid,x,y,z);
                GetPlayerFacingAngle(playerid, a);
                if(CarDealershipInfo[d][cdTill] >= GetVehicleDealerCost(modelid))
                {
                    harga = GetVehicleDealerCost(modelid);
                }
                else
                {
                    SendClientMessageEx(playerid, COLOR_GRAD2, "Anda harus mempunyai modal sebesar "GREEN_E"$%s", FormatMoney(GetVehicleDealerCost(modelid)));
                    return 1;
                }
                if(modelid < 400||modelid > 611||modelid == 411||modelid == 415||modelid == 424||modelid == 434||modelid == 451||modelid == 494||modelid == 502||modelid == 503||modelid == 495||modelid == 506||modelid == 503)
                {
                    SendClientMessageEx(playerid, COLOR_GREY, "ID Kendaraan tidak diperbolehkan!");
                    return 1;
                }
                new cdvehicleid = pData[playerid][pListitems];
                DestroyDynamic3DTextLabel(CarDealershipInfo[d][cdVehicleLabel][cdvehicleid]);
                if(CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid] == 0.0 && CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid] == 0.0)
                {
                    new vehicleid = CreateVehicle(modelid, x, y, z, a, -1, -1, 6);
                    CarDealershipInfo[d][cdVehicleId][cdvehicleid] = vehicleid;
                    CarDealershipInfo[d][cdVehicleModel][cdvehicleid] = modelid;
                    CarDealershipInfo[d][cdVehicleCost][cdvehicleid] = harga;
                    CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid] = x;
                    CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid] = y;
                    CarDealershipInfo[d][cdVehicleSpawnZ][cdvehicleid] = z;
                    CarDealershipInfo[d][cdVehicleSpawnAngle][cdvehicleid] = a;
                    PutPlayerInVehicle(playerid, vehicleid, 0);
                    format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",cdvehicleid, GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[d][cdVehicleCost][cdvehicleid]));
                    CarDealershipInfo[d][cdVehicleLabel][cdvehicleid] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,5.0,INVALID_PLAYER_ID,vehicleid,1);
                }
                else
                {
                    new vehicleid = CreateVehicle(modelid, CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnZ][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnAngle][cdvehicleid], -1, -1, 6);
                    CarDealershipInfo[d][cdVehicleId][cdvehicleid] = vehicleid;
                    CarDealershipInfo[d][cdVehicleModel][cdvehicleid] = modelid;
                    CarDealershipInfo[d][cdVehicleCost][cdvehicleid] = harga;
                    
                    format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",cdvehicleid, GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[d][cdVehicleCost][cdvehicleid]));
                    CarDealershipInfo[d][cdVehicleLabel][cdvehicleid] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,5.0,INVALID_PLAYER_ID,vehicleid,1);
                }
                SendClientMessageEx(playerid, COLOR_YELLOW, "You have created Car Dealership ID %d for Dealership ID %d to your position.", cdvehicleid, d);
                SavecDealership(d);
                CarDealershipInfo[d][cdTill] -= harga;
            }
        }  
        case MODEL_SELECTION_Sport:
	    {
	        if(response)
	        {
                new Float: x, Float: y, Float: z, Float: a, harga, String[212];
                new d = GetPVarInt(playerid, "editingcd");
                GetPlayerPos(playerid,x,y,z);
                GetPlayerFacingAngle(playerid, a);
                if(CarDealershipInfo[d][cdTill] >= GetVehicleDealerCost(modelid))
                {
                    harga = GetVehicleDealerCost(modelid);
                }
                else
                {
                    SendClientMessageEx(playerid, COLOR_GRAD2, "Anda harus mempunyai modal sebesar "GREEN_E"$%s", FormatMoney(GetVehicleDealerCost(modelid)));
                    return 1;
                }
                if(modelid < 400||modelid > 611||modelid == 411||modelid == 415||modelid == 424||modelid == 434||modelid == 451||modelid == 494||modelid == 502||modelid == 503||modelid == 495||modelid == 506||modelid == 503)
                {
                    SendClientMessageEx(playerid, COLOR_GREY, "ID Kendaraan tidak diperbolehkan!");
                    return 1;
                }
                new cdvehicleid = pData[playerid][pListitems];
                DestroyDynamic3DTextLabel(CarDealershipInfo[d][cdVehicleLabel][cdvehicleid]);
                if(CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid] == 0.0 && CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid] == 0.0)
                {
                    new vehicleid = CreateVehicle(modelid, x, y, z, a, -1, -1, 6);
                    CarDealershipInfo[d][cdVehicleId][cdvehicleid] = vehicleid;
                    CarDealershipInfo[d][cdVehicleModel][cdvehicleid] = modelid;
                    CarDealershipInfo[d][cdVehicleCost][cdvehicleid] = harga;
                    CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid] = x;
                    CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid] = y;
                    CarDealershipInfo[d][cdVehicleSpawnZ][cdvehicleid] = z;
                    CarDealershipInfo[d][cdVehicleSpawnAngle][cdvehicleid] = a;
                    PutPlayerInVehicle(playerid, vehicleid, 0);
                    format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",cdvehicleid, GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[d][cdVehicleCost][cdvehicleid]));
                    CarDealershipInfo[d][cdVehicleLabel][cdvehicleid] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,5.0,INVALID_PLAYER_ID,vehicleid,1);
                }
                else
                {
                    new vehicleid = CreateVehicle(modelid, CarDealershipInfo[d][cdVehicleSpawnX][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnY][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnZ][cdvehicleid], CarDealershipInfo[d][cdVehicleSpawnAngle][cdvehicleid], -1, -1, 6);
                    CarDealershipInfo[d][cdVehicleId][cdvehicleid] = vehicleid;
                    CarDealershipInfo[d][cdVehicleModel][cdvehicleid] = modelid;
                    CarDealershipInfo[d][cdVehicleCost][cdvehicleid] = harga;
                    
                    format(String, sizeof(String), "[slot:%d]\n{00FFFF}%s\n"WHITE_E"Price: "GREEN_E"$%s\n"WHITE_E"Fuel Capacity: "YELLOW_E"100.0\n"WHITE_E"Fuel Total: "YELLOW_E"100.0",cdvehicleid, GetVehicleName(vehicleid), FormatMoney(CarDealershipInfo[d][cdVehicleCost][cdvehicleid]));
                    CarDealershipInfo[d][cdVehicleLabel][cdvehicleid] = CreateDynamic3DTextLabel(String,COLOR_ARWIN,0.0, 0.0, 0.0,5.0,INVALID_PLAYER_ID,vehicleid,1);
                }
                SendClientMessageEx(playerid, COLOR_YELLOW, "You have created Car Dealership ID %d for Dealership ID %d to your position.", cdvehicleid, d);
                SavecDealership(d);
                CarDealershipInfo[d][cdTill] -= harga;
            }
        }       
        case MODEL_SELECTION_Aksesoris:
        {
            Aksesoris_Create(playerid, modelid, GetAksesorisNameByModel(modelid));
                
            SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"Use "YELLOW_E"/dyoc "WHITE_E"to wear/edit this");
        }
        case MODEL_SELECTION_FVEHICLE:
	    {
	        if(response)
	        {
                new harga = GetVehicleDealerCost(modelid);
                if(GetPlayerMoney(playerid) <= GetVehicleDealerCost(modelid))
                {
                    SendClientMessageEx(playerid, COLOR_GRAD2, "Anda harus mempunyai modal sebesar "GREEN_E"$%s", FormatMoney(GetVehicleDealerCost(modelid)));
                    return 1;
                }
                new bid = pData[playerid][pFamily];
                if(fData[bid][fVehicleModel][0] == 0)
                {
                    fData[bid][fVehicleModel][0] = modelid;
                    fData[bid][fVehicleFuel][0] = 1000;
                    fData[bid][fVehicleHealth][0] = 2000;
                    GetPlayerPos(playerid, fData[bid][fVehiclePos][0], fData[bid][fVehiclePos][1], fData[bid][fVehiclePos][2]);
                    Family_Save(bid);
                    Family_Refresh(bid);
                    GivePlayerMoneyEx(playerid, -harga);
                    SendCustomMessage(playerid, "FAMILY", "You successfully purchased a vehicle for the family at a price of "GREEN_E"$%s", FormatMoney(harga));
                }
                else if(fData[bid][fVehicleModel][1] == 0)
                {
                    fData[bid][fVehicleModel][1] = modelid;
                    fData[bid][fVehicleFuel][1] = 1000;
                    fData[bid][fVehicleHealth][1] = 2000;
                    GetPlayerPos(playerid, fData[bid][fVehiclePos1][0], fData[bid][fVehiclePos1][1], fData[bid][fVehiclePos1][2]);
                    Family_Save(bid);
                    Family_Refresh(bid);
                    GivePlayerMoneyEx(playerid, -harga);
                    SendCustomMessage(playerid, "FAMILY", "You successfully purchased a vehicle for the family at a price of "GREEN_E"$%s", FormatMoney(harga));
                }
                else if(fData[bid][fVehicleModel][2] == 0)
                {
                    fData[bid][fVehicleModel][2] = modelid;
                    fData[bid][fVehicleFuel][2] = 1000;
                    fData[bid][fVehicleHealth][2] = 2000;
                    GetPlayerPos(playerid, fData[bid][fVehiclePos2][0], fData[bid][fVehiclePos2][1], fData[bid][fVehiclePos2][2]);
                    Family_Save(bid);
                    Family_Refresh(bid);
                    GivePlayerMoneyEx(playerid, -harga);
                    SendCustomMessage(playerid, "FAMILY", "You successfully purchased a vehicle for the family at a price of "GREEN_E"$%s", FormatMoney(harga));
                }
                else if(fData[bid][fVehicleModel][3] == 0)
                {
                    fData[bid][fVehicleModel][3] = modelid;
                    fData[bid][fVehicleFuel][3] = 1000;
                    fData[bid][fVehicleHealth][3] = 2000;
                    GetPlayerPos(playerid, fData[bid][fVehiclePos3][0], fData[bid][fVehiclePos3][1], fData[bid][fVehiclePos3][2]);
                    Family_Save(bid);
                    Family_Refresh(bid);
                    GivePlayerMoneyEx(playerid, -harga);
                    SendCustomMessage(playerid, "FAMILY", "You successfully purchased a vehicle for the family at a price of "GREEN_E"$%s", FormatMoney(harga));
                }
                else if(fData[bid][fVehicleModel][4] == 0)
                {
                    fData[bid][fVehicleModel][4] = modelid;
                    fData[bid][fVehicleFuel][4] = 1000;
                    fData[bid][fVehicleHealth][4] = 2000;
                    GetPlayerPos(playerid, fData[bid][fVehiclePos4][0], fData[bid][fVehiclePos4][1], fData[bid][fVehiclePos4][2]);
                    Family_Save(bid);
                    Family_Refresh(bid);
                    GivePlayerMoneyEx(playerid, -harga);
                    SendCustomMessage(playerid, "FAMILY", "You successfully purchased a vehicle for the family at a price of "GREEN_E"$%s", FormatMoney(harga));
                }
            }
        }       
	}
    
	return 1;
}

public OnCustomSelectionResponse(playerid, extraid, modelid, response)
{
    if(response)
    {
        switch(extraid)
        {
            case MODEL_SELECTION_AKSESORIS:
            {
                Aksesoris_Create(playerid, modelid, GetAksesorisNameByModel(modelid));
                
                SendClientMessageEx(playerid, COLOR_ARWIN, "HINT: "WHITE_E"Use "YELLOW_E"/dyoc "WHITE_E"to wear/edit this");
                
            }
            case MODEL_SELECTION_FURNITURE:
            {
                new id = FurnObject_Add(playerid, modelid, ManageFurnStore[playerid]);

                if(id == cellmin)
                    return Error(playerid, "Furniture object untuk furniture store ini sudah mencapai batas maksimal.");

                ManageFurnObject[playerid] = id;
                Dialog_Show(playerid, ManageFurnObject, DIALOG_STYLE_LIST, "Manage Object", "Produce\nMove\nSet Name\nSet Price\nTexture\nDelete", "Select", "Close");

                Servers(playerid, "Object baru telah di buat, silahkan untuk memposisikan object dengan benar Menyalah gunakan akan mendapat sanksi berupa BANNED 3 hari.", 5000);
            }
        }
    }
    return 1;
}
