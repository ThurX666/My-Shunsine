Dialog:EditingVehObject(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        Player_EditVehicleObjectSlot[playerid] = ListedVehObject[playerid][listitem];
        new vehicleid = Player_EditVehicleObject[playerid];
        if(!VehicleObjects[vehicleid][Player_EditVehicleObjectSlot[playerid]][vehObjectExists])
        {
            Dialog_Show(playerid, DialogModshop, DIALOG_STYLE_LIST, "Buying Modification", "Transfender Component\nWAA Component\nLoco Component\nSticker\nSpot Light\nNumber Plate (Medium)\nNeon Tube", "Okay", "Cancel");
        }
        else
        {
            new 
                slot = Player_EditVehicleObjectSlot[playerid]
            ;
            if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
            {
                Dialog_Show(playerid, VACCSE, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nChange Color\nRemove Modification\nSave", "Select", "Back");
            }
            else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_TEXT)
            {
                Dialog_Show(playerid, VACCSE1, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nText Name\nText Size\nText Font\nText Color\nRemove Modification\nSave", "Select", "Back");
            }
            else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_LIGHT)
            {
               Dialog_Show(playerid, VACCSE2, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nRemove Modification\nSave", "Select", "Back");
            }
            else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_PLATE)
            {
                Dialog_Show(playerid, VACCSE3, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nRemove Modification\nSave", "Select", "Back");
            }
            else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_NEON)
            {
                Dialog_Show(playerid, VACCSE4, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nRemove Modification\nSave", "Select", "Back");
            }
        }
    }
    return 1;
}


Dialog:DialogModshop(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch (listitem)
        {
            case 0:
            {   
                ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Transfender, "Modshop:", transfender, sizeof(transfender));
            }
            case 1:
            {   
                ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Waa, "Modshop:", waa, sizeof(waa));
            }
            case 2:
            {   
                ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Loco, "Modshop:", loco, sizeof(loco));
            }
            case 3:
            {
                if(pData[playerid][pVip] < 2) return PermissionError(playerid);
                static 
                    vehicle;
                
                vehicle = Player_EditVehicleObject[playerid];
                if(vehicle != INVALID_VEHICLE_ID) 
                {
                    Vehicle_TextAdd(playerid, vehicle, 18659, OBJECT_TYPE_TEXT);
                    Streamer_Update(playerid);
                    return 1;
                } 
                else Error(playerid, "Invalid vehicle id.");
            }
            case 4:
            {
                if(pData[playerid][pVip] < 2) return PermissionError(playerid);
                static 
                    vehicle;
                
                vehicle = Player_EditVehicleObject[playerid];
                if(vehicle != INVALID_VEHICLE_ID) 
                {
                    Vehicle_SpotLightAdd(playerid, vehicle, 19281, OBJECT_TYPE_LIGHT);
                    return 1;
                } 
                else Error(playerid, "Invalid vehicle id.");
            }
            case 5:
            {
                static 
                    vehicle;
                
                vehicle = Player_EditVehicleObject[playerid];
                if(vehicle != INVALID_VEHICLE_ID) 
                {
                    Vehicle_PlateAdd(playerid, vehicle, 19814, OBJECT_TYPE_PLATE);
                    return 1;
                } 
                else Error(playerid, "Invalid vehicle id.");
            }
            case 6:
            {
                static 
                    vehicle;
                
                vehicle = Player_EditVehicleObject[playerid];
                if(vehicle != INVALID_VEHICLE_ID) 
                {
                    Vehicle_NeonAdd(playerid, vehicle, 18652, OBJECT_TYPE_NEON);
                    return 1;
                } 
                else Error(playerid, "Invalid vehicle id.");
            }
        }
    }
    return 1;
}


Dialog:VACCSE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid],
            modelid = VehicleObjects[vehicleid][slot][vehObjectModel]
        ;

        switch(listitem)
        {
            case 0:
			{
				if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
				{
                    SetVehicleZAngle(GetPlayerVehicleID(playerid), 0.0);

					Vehicle_ObjectEdit(playerid, vehicleid, slot);
                    EditDynamicObject(playerid, VehicleObjects[vehicleid][slot][vehObject]);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
				else
				{
                    SetVehicleZAngle(GetPlayerVehicleID(playerid), 0.0);
					Vehicle_ObjectEdit(playerid, vehicleid, slot, true);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
			}
			case 1:
			{
                new string[512];
                format(string, sizeof(string), "Here you can input mod offset manually\nCurrent offset:\n{00FFFF}%.3f %.3f %.3f %.3f %.3f\n"WHITE_E"New offset: "GREEN_E"(input bellow)", 
                VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
                VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
                Dialog_Show(playerid, EditManually, DIALOG_STYLE_INPUT, "Modshop: Set Offset Manually", string, "input", "Back");
            }
            case 2:
            {
                Dialog_Show(playerid, VEH_OBJECT_COLOR, DIALOG_STYLE_INPUT, "Modification Color", color_string, "Select", "Close");
            }
            case 3:
            {
                Vehicle_ObjectDelete(vehicleid, slot);
                SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You removed "YELLOW_E"%s "WHITE_E"from your vehicle!", GetVehObjectNameByModel(modelid));
            }
            case 4:
            {
                Vehicle_ObjectSave(vehicleid, slot);
                callcmd::myov(playerid, "");
            }
        }
    }
    return 1;
}

Dialog:VACCSE1(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;

        switch(listitem)
        {
            case 0:
			{
				if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
				{
                    SetVehicleZAngle(GetPlayerVehicleID(playerid), 0.0);

					Vehicle_ObjectEdit(playerid, vehicleid, slot);
                    EditDynamicObject(playerid, VehicleObjects[vehicleid][slot][vehObject]);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
				else
				{
                    SetVehicleZAngle(GetPlayerVehicleID(playerid), 0.0);
					Vehicle_ObjectEdit(playerid, vehicleid, slot, true);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
			}
			case 1:
			{
                new string[512];
                format(string, sizeof(string), "Here you can input mod offset manually\nCurrent offset:\n{00FFFF}%.3f %.3f %.3f %.3f %.3f\n"WHITE_E"New offset: "GREEN_E"(input bellow)", 
                VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
                VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
                Dialog_Show(playerid, EditManually, DIALOG_STYLE_INPUT, "Modshop: Set Offset Manually", string, "input", "Back");
			}
            case 2:
			{
				Dialog_Show(playerid, VEH_OBJECT_TEXTNAME, DIALOG_STYLE_INPUT, "Input Text Name", "Input Text name 32 Character : ", "Update", "Close");
			}
			case 3:
			{
				Dialog_Show(playerid, VEH_OBJECT_TEXTSIZE, DIALOG_STYLE_INPUT, "Input Text Size", "Input Text Size Maximal Ukuran 200 : ", "Update", "Close");
			}
			case 4:
			{
				Dialog_Show(playerid, VEH_OBJECT_TEXTFONT, DIALOG_STYLE_LIST, "Input Text Font", object_font, "Update", "Close");
			}
			case 5:
			{
				Dialog_Show(playerid, VEH_OBJECT_TEXTCOLOR, DIALOG_STYLE_INPUT, "Input Text Color", color_string, "Update", "Close");
			}
            case 6:
            {
                Vehicle_ObjectDelete(vehicleid, slot);
                SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You removed vehicle text object!");
            }
            case 7:
            {
                Vehicle_ObjectSave(vehicleid, slot);
                callcmd::myov(playerid, "");
            }
        }
    }
    return 1;
}

Dialog:VACCSE2(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;

        switch(listitem)
        {
            case 0:
			{
				if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
				{
					Vehicle_ObjectEdit(playerid, vehicleid, slot);
                    EditDynamicObject(playerid, VehicleObjects[vehicleid][slot][vehObject]);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
				else
				{
					Vehicle_ObjectEdit(playerid, vehicleid, slot, true);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
			}
			case 1:
			{
                new string[512];
                format(string, sizeof(string), "Here you can input mod offset manually\nCurrent offset:\n{00FFFF}%.3f %.3f %.3f %.3f %.3f\n"WHITE_E"New offset: "GREEN_E"(input bellow)", 
                VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
                VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
                Dialog_Show(playerid, EditManually, DIALOG_STYLE_INPUT, "Modshop: Set Offset Manually", string, "input", "Back");
			}
            case 2:
            {
                Vehicle_ObjectDelete(vehicleid, slot);
                SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You removed "YELLOW_E"Spot Light "WHITE_E"from your vehicle!");
            }
            case 3:
            {
                Vehicle_ObjectSave(vehicleid, slot);
                callcmd::myov(playerid, "");
            }
        }
    }
    return 1;
}

Dialog:VACCSE3(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;

        switch(listitem)
        {
            case 0:
			{
				if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_PLATE)
				{
					Vehicle_ObjectEdit(playerid, vehicleid, slot);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
			}
			case 1:
			{
                new string[512];
                format(string, sizeof(string), "Here you can input mod offset manually\nCurrent offset:\n{00FFFF}%.3f %.3f %.3f %.3f %.3f\n"WHITE_E"New offset: "GREEN_E"(input bellow)", 
                VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
                VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
                Dialog_Show(playerid, EditManually, DIALOG_STYLE_INPUT, "Modshop: Set Offset Manually", string, "input", "Back");
			}
            case 2:
            {
                Vehicle_ObjectDelete(vehicleid, slot);
                SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You removed "YELLOW_E"Plate "WHITE_E"from your vehicle!");
            }
            case 3:
            {
                Vehicle_ObjectSave(vehicleid, slot);
                callcmd::myov(playerid, "");
            }
        }
    }
    return 1;
}

Dialog:VACCSE4(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;

        switch(listitem)
        {
            case 0:
			{
				if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_NEON)
				{
					Vehicle_ObjectEdit(playerid, vehicleid, slot);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
			}
			case 1:
			{
                new string[512];
                format(string, sizeof(string), "Here you can input mod offset manually\nCurrent offset:\n{00FFFF}%.3f %.3f %.3f %.3f %.3f\n"WHITE_E"New offset: "GREEN_E"(input bellow)", 
                VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
                VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
                Dialog_Show(playerid, EditManually, DIALOG_STYLE_INPUT, "Modshop: Set Offset Manually", string, "input", "Back");
			}
            case 2:
            {
                Vehicle_ObjectDelete(vehicleid, slot);
                SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You removed "YELLOW_E"Neon Tube "WHITE_E"from your vehicle!");
            }
            case 3:
            {
                Vehicle_ObjectSave(vehicleid, slot);
                callcmd::myov(playerid, "");
            }
        }
    }
    return 1;
}

Dialog:NeonTube(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;

        switch(listitem)
        {
            case 0:
			{
				if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_NEON)
				{
					Vehicle_ObjectEdit(playerid, vehicleid, slot);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
			}
			case 1:
			{
                new string[512];
                format(string, sizeof(string), "Here you can input mod offset manually\nCurrent offset:\n{00FFFF}%.3f %.3f %.3f %.3f %.3f\n"WHITE_E"New offset: "GREEN_E"(input bellow)", 
                VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
                VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
                Dialog_Show(playerid, EditManually, DIALOG_STYLE_INPUT, "Modshop: Set Offset Manually", string, "input", "Back");
			}
            case 2:
            {
                Dialog_Show(playerid, NeonTubeColor, DIALOG_STYLE_LIST, "Neon Color", "White\nRed\nGreen\nBlue\nYellow\nPink", "Select", "Cancel"); 
            }
        }
    }
    return 1;
}

Dialog:NeonTubeColor(playerid, response, listitem, inputtext[])
{
	if(response)
	{
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;

		switch(listitem)
		{
			case 0:
			{
				Vehicle_NeonColorSync(vehicleid, slot, 18652, playerid);
			}
			case 1:
			{
                Vehicle_NeonColorSync(vehicleid, slot, 18647, playerid);
			}
            case 2:
			{
				Vehicle_NeonColorSync(vehicleid, slot, 18649, playerid);
			}
			case 3:
			{
                Vehicle_NeonColorSync(vehicleid, slot, 18648, playerid);
			}
            case 4:
			{
				Vehicle_NeonColorSync(vehicleid, slot, 18650, playerid);
			}
			case 5:
			{
                Vehicle_NeonColorSync(vehicleid, slot, 18651, playerid);
			}
		}
	}
	return 1;
}

Dialog:VEH_OBJECT_COLOR(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]        
		;

		VehicleObjects[vehicleid][slot][vehObjectColor] = strval(inputtext);
		Vehicle_ObjectColorSync(vehicleid, slot);
        Dialog_Show(playerid, VACCSE, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nChange Color\nRemove Modification\nSave", "Select", "Back");
    }
	return 1;
}

Dialog:VEH_OBJECT_TEXT(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				Dialog_Show(playerid, VEH_OBJECT_TEXTNAME, DIALOG_STYLE_INPUT, "Input Text Name", "Input Text name 32 Character : ", "Update", "Close");
			}
			case 1:
			{
				Dialog_Show(playerid, VEH_OBJECT_TEXTSIZE, DIALOG_STYLE_INPUT, "Input Text Size", "Input Text Size Maximal Ukuran 200 : ", "Update", "Close");
			}
			case 2:
			{
				Dialog_Show(playerid, VEH_OBJECT_TEXTFONT, DIALOG_STYLE_LIST, "Input Text Font", object_font, "Update", "Close");
			}
			case 3:
			{
				Dialog_Show(playerid, VEH_OBJECT_TEXTCOLOR, DIALOG_STYLE_INPUT, "Input Text Color", color_string, "Update", "Close");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_MODSHOPMOVE(playerid, response, listitem, inputtext[])
{
	if(response)
	{
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;

		switch(listitem)
		{
			case 0:
			{
				if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
				{
                    SetVehicleZAngle(GetPlayerVehicleID(playerid), 0.0);

					Vehicle_ObjectEdit(playerid, vehicleid, slot);
                    EditDynamicObject(playerid, VehicleObjects[vehicleid][slot][vehObject]);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
				else
				{
                    SetVehicleZAngle(GetPlayerVehicleID(playerid), 0.0);
					Vehicle_ObjectEdit(playerid, vehicleid, slot, true);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
			}
			case 1:
			{
                new string[512];
                format(string, sizeof(string), "Here you can input mod offset manually\nCurrent offset:\n{00FFFF}%.3f %.3f %.3f %.3f %.3f\n"WHITE_E"New offset: "GREEN_E"(input bellow)", 
                VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
                VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
                Dialog_Show(playerid, EditManually, DIALOG_STYLE_INPUT, "Modshop: Set Offset Manually", string, "input", "Back");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_SPOTLIGHT(playerid, response, listitem, inputtext[])
{
	if(response)
	{
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;

		switch(listitem)
		{
			case 0:
			{
				if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
				{
                    SetVehicleZAngle(GetPlayerVehicleID(playerid), 0.0);

					Vehicle_ObjectEdit(playerid, vehicleid, slot);
                    EditDynamicObject(playerid, VehicleObjects[vehicleid][slot][vehObject]);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
				else
				{
                    SetVehicleZAngle(GetPlayerVehicleID(playerid), 0.0);
					Vehicle_ObjectEdit(playerid, vehicleid, slot, true);
					SendClientMessageEx(playerid, COLOR_ARWIN, "MODSHOP: "WHITE_E"You can now edit the location for the mod");
				}
			}
			case 1:
			{
                new string[512];
                format(string, sizeof(string), "Here you can input mod offset manually\nCurrent offset:\n{00FFFF}%.3f %.3f %.3f %.3f %.3f\n"WHITE_E"New offset: "GREEN_E"(input bellow)", 
                VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
                VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
                Dialog_Show(playerid, EditManually, DIALOG_STYLE_INPUT, "Modshop: Set Offset Manually", string, "input", "Back");
			}
            case 2:
            {
                Dialog_Show(playerid, DIALOG_SPOTLIGHT1, DIALOG_STYLE_LIST, "Light Color", "White\nRed\nGreen\nBlue", "Select", "Cancel"); 
            }
            case 3:
            {
                Vehicle_ObjectSave(vehicleid, slot);
                callcmd::myov(playerid, "");
            }
		}
	}
	return 1;
}

Dialog:DIALOG_SPOTLIGHT1(playerid, response, listitem, inputtext[])
{
	if(response)
	{
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;

		switch(listitem)
		{
			case 0:
			{
				Vehicle_LightColorSync(vehicleid, slot, 19281, playerid);
			}
			case 1:
			{
                Vehicle_LightColorSync(vehicleid, slot, 19282, playerid);
			}
            case 2:
			{
				Vehicle_LightColorSync(vehicleid, slot, 19283, playerid);
			}
			case 3:
			{
                Vehicle_LightColorSync(vehicleid, slot, 19284, playerid);
			}
		}
	}
	return 1;
}

Dialog:EditManually(playerid, response, listitem, inputtext[])
{
    new 
        slot = Player_EditVehicleObjectSlot[playerid],
        vehicleid = Player_EditVehicleObject[playerid]        
    ;
    if(response)
    {
        new Float:pos[6];
        if(!sscanf(inputtext, "ffffff",pos[0],pos[1],pos[2],pos[3],pos[4],pos[5])) 
        
        AttachDynamicObjectToVehicle(VehicleObjects[vehicleid][slot][vehObject], pvData[vehicleid][cVeh], 
        pos[0], 
        pos[1], 
        pos[2], 
        pos[3], 
        pos[4], 
        pos[5]);
        VehicleObjects[vehicleid][slot][vehObjectPosX] = pos[0];
        VehicleObjects[vehicleid][slot][vehObjectPosY] = pos[1];
        VehicleObjects[vehicleid][slot][vehObjectPosZ] = pos[2];
        VehicleObjects[vehicleid][slot][vehObjectPosRX] = pos[3];
        VehicleObjects[vehicleid][slot][vehObjectPosRY] = pos[4];
        VehicleObjects[vehicleid][slot][vehObjectPosRZ] = pos[5];
        
        new string[512];
        format(string, sizeof(string), "Here you can input mod offset manually\nCurrent offset:\n{00FFFF}%.3f %.3f %.3f %.3f %.3f\n"WHITE_E"New offset: "GREEN_E"(input bellow)", 
        VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
        VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
        Dialog_Show(playerid, EditManually, DIALOG_STYLE_INPUT, "Modshop: Set Offset Manually", string, "input", "Back");
    }
    else 
    {
        if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
        {
            Dialog_Show(playerid, VACCSE, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nChange Color\nRemove Modification\nSave", "Select", "Back");
        }
        else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_TEXT)
        {
            Dialog_Show(playerid, VACCSE1, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nText Name\nText Size\nText Font\nText Color\nRemove Modification\nSave", "Select", "Back");
        }
        else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_LIGHT)
        {
            Dialog_Show(playerid, VACCSE2, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nRemove Modification\nSave", "Select", "Back");
        }
        else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_PLATE)
        {
            Dialog_Show(playerid, VACCSE3, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nRemove Modification\nSave", "Select", "Back");
        }
    }
	return 1;
}

// Dialog:DIALOG_MSEDIT(playerid, response, listitem, inputtext[])
// {
// 	if(response)
// 	{
//         new 
//             slot = Player_EditVehicleObjectSlot[playerid],
//             vehicleid = Player_EditVehicleObject[playerid]
//         ;
// 		switch(listitem)
// 		{
// 			case 0: //X
// 			{
// 				new mstr[128];
//                 format(mstr, sizeof(mstr), ""WHITE_E"Current PosX: %f\nInput new PosX:(Float)", VehicleObjects[vehicleid][slot][vehObjectPosX]);
//                 Dialog_Show(playerid, DIALOG_MSEDITX, DIALOG_STYLE_INPUT, "PosX", mstr, "Edit", "Cancel");
// 			}
// 			case 1: //Y
// 			{
//                 new mstr[128];
//                 format(mstr, sizeof(mstr), ""WHITE_E"Current PosX: %f\nInput new PosY:(Float)", VehicleObjects[vehicleid][slot][vehObjectPosY]);
//                 Dialog_Show(playerid, DIALOG_MSEDITY, DIALOG_STYLE_INPUT, "PosY", mstr, "Edit", "Cancel");
// 			}
//             case 2: //Z
// 			{
//                 new mstr[128];
//                 format(mstr, sizeof(mstr), ""WHITE_E"Current PosX: %f\nInput new PosZ:(Float)", VehicleObjects[vehicleid][slot][vehObjectPosZ]);
//                 Dialog_Show(playerid, DIALOG_MSEDITZ, DIALOG_STYLE_INPUT, "PosZ", mstr, "Edit", "Cancel");
// 			}
//             case 3: //RX
// 			{
//                 new mstr[128];
//                 format(mstr, sizeof(mstr), ""WHITE_E"Current PosX: %f\nInput new PosRX:(Float)", VehicleObjects[vehicleid][slot][vehObjectPosRX]);
//                 Dialog_Show(playerid, DIALOG_MSEDITRX, DIALOG_STYLE_INPUT, "PosRX", mstr, "Edit", "Cancel");
// 			}
//             case 4: //RY
// 			{
//                 new mstr[128];
//                 format(mstr, sizeof(mstr), ""WHITE_E"Current PosX: %f\nInput new PosRY:(Float)", VehicleObjects[vehicleid][slot][vehObjectPosRY]);
//                 Dialog_Show(playerid, DIALOG_MSEDITRY, DIALOG_STYLE_INPUT, "PosRY", mstr, "Edit", "Cancel");
// 			}
//             case 5: //RZ
// 			{
//                 new mstr[128];
//                 format(mstr, sizeof(mstr), ""WHITE_E"Current PosX: %f\nInput new PosRZ:(Float)", VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
//                 Dialog_Show(playerid, DIALOG_MSEDITRZ, DIALOG_STYLE_INPUT, "PosRZ", mstr, "Edit", "Cancel");
// 			}
// 		}
// 	}
// 	return 1;
// }

// Dialog:DIALOG_MSEDITX(playerid, response, listitem, inputtext[])
// {
//     if(response)
//     {
//         new 
//             slot = Player_EditVehicleObjectSlot[playerid],
//             vehicleid = Player_EditVehicleObject[playerid]        
// 		;
//         new Float:posisi = floatstr(inputtext);
//         AttachDynamicObjectToVehicle(VehicleObjects[vehicleid][slot][vehObject], pvData[vehicleid][cVeh], 
//         posisi, 
//         VehicleObjects[vehicleid][slot][vehObjectPosY], 
//         VehicleObjects[vehicleid][slot][vehObjectPosZ], 
//         VehicleObjects[vehicleid][slot][vehObjectPosRX], 
//         VehicleObjects[vehicleid][slot][vehObjectPosRY], 
//         VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
//         //Vehicle_ObjectSave(vehicleid, slot);

//         VehicleObjects[vehicleid][slot][vehObjectPosX] = posisi;
//         new string[512];
//         format(string, sizeof(string), "PosX: %f\nPosY: %f\nPosZ: %f\nPosRX: %f\nPosRY: %f\nPosRZ: %f",
//         VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
//         VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
//         Dialog_Show(playerid, DIALOG_MSEDIT, DIALOG_STYLE_LIST, "Modshop", string, "Select", "Cancel");
//     }
// 	return 1;
// }

// Dialog:DIALOG_MSEDITY(playerid, response, listitem, inputtext[])
// {
//     if(response)
//     {
//         new 
//             slot = Player_EditVehicleObjectSlot[playerid],
//             vehicleid = Player_EditVehicleObject[playerid]        
// 		;
//         new Float:posisi = floatstr(inputtext);
//         AttachDynamicObjectToVehicle(VehicleObjects[vehicleid][slot][vehObject], pvData[vehicleid][cVeh], 
//         VehicleObjects[vehicleid][slot][vehObjectPosX], 
//         posisi, 
//         VehicleObjects[vehicleid][slot][vehObjectPosZ], 
//         VehicleObjects[vehicleid][slot][vehObjectPosRX], 
//         VehicleObjects[vehicleid][slot][vehObjectPosRY], 
//         VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
        

//         VehicleObjects[vehicleid][slot][vehObjectPosY] = posisi;
//         new string[512];
//         format(string, sizeof(string), "PosX: %f\nPosY: %f\nPosZ: %f\nPosRX: %f\nPosRY: %f\nPosRZ: %f",
//         VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
//         VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
//         Dialog_Show(playerid, DIALOG_MSEDIT, DIALOG_STYLE_LIST, "Modshop", string, "Select", "Cancel");
//     }
// 	return 1;
// }

// Dialog:DIALOG_MSEDITZ(playerid, response, listitem, inputtext[])
// {
//     if(response)
//     {
//         new 
//             slot = Player_EditVehicleObjectSlot[playerid],
//             vehicleid = Player_EditVehicleObject[playerid]        
// 		;
//         new Float:posisi = floatstr(inputtext);
//         AttachDynamicObjectToVehicle(VehicleObjects[vehicleid][slot][vehObject], pvData[vehicleid][cVeh], 
//         VehicleObjects[vehicleid][slot][vehObjectPosX], 
//         VehicleObjects[vehicleid][slot][vehObjectPosY], 
//         posisi, 
//         VehicleObjects[vehicleid][slot][vehObjectPosRX], 
//         VehicleObjects[vehicleid][slot][vehObjectPosRY], 
//         VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
        

//         VehicleObjects[vehicleid][slot][vehObjectPosZ] = posisi;
//         new string[512];
//         format(string, sizeof(string), "PosX: %f\nPosY: %f\nPosZ: %f\nPosRX: %f\nPosRY: %f\nPosRZ: %f",
//         VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
//         VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
//         Dialog_Show(playerid, DIALOG_MSEDIT, DIALOG_STYLE_LIST, "Modshop", string, "Select", "Cancel");
//     }
// 	return 1;
// }

// Dialog:DIALOG_MSEDITRX(playerid, response, listitem, inputtext[])
// {
//     if(response)
//     {
//         new 
//             slot = Player_EditVehicleObjectSlot[playerid],
//             vehicleid = Player_EditVehicleObject[playerid]        
// 		;
//         new Float:posisi = floatstr(inputtext);
//         AttachDynamicObjectToVehicle(VehicleObjects[vehicleid][slot][vehObject], pvData[vehicleid][cVeh], 
//         VehicleObjects[vehicleid][slot][vehObjectPosX], 
//         VehicleObjects[vehicleid][slot][vehObjectPosY], 
//         VehicleObjects[vehicleid][slot][vehObjectPosZ], 
//         posisi, 
//         VehicleObjects[vehicleid][slot][vehObjectPosRY], 
//         VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
        

//         VehicleObjects[vehicleid][slot][vehObjectPosRX] = posisi;
//         new string[512];
//         format(string, sizeof(string), "PosX: %f\nPosY: %f\nPosZ: %f\nPosRX: %f\nPosRY: %f\nPosRZ: %f",
//         VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
//         VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
//         Dialog_Show(playerid, DIALOG_MSEDIT, DIALOG_STYLE_LIST, "Modshop", string, "Select", "Cancel");
//     }
// 	return 1;
// }

// Dialog:DIALOG_MSEDITRY(playerid, response, listitem, inputtext[])
// {
//     if(response)
//     {
//         new 
//             slot = Player_EditVehicleObjectSlot[playerid],
//             vehicleid = Player_EditVehicleObject[playerid]        
// 		;
//         new Float:posisi = floatstr(inputtext);
//         AttachDynamicObjectToVehicle(VehicleObjects[vehicleid][slot][vehObject], pvData[vehicleid][cVeh], 
//         VehicleObjects[vehicleid][slot][vehObjectPosX], 
//         VehicleObjects[vehicleid][slot][vehObjectPosY], 
//         VehicleObjects[vehicleid][slot][vehObjectPosZ], 
//         VehicleObjects[vehicleid][slot][vehObjectPosRX], 
//         posisi, 
//         VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
        

//         VehicleObjects[vehicleid][slot][vehObjectPosRY] = posisi;
//         new string[512];
//         format(string, sizeof(string), "PosX: %f\nPosY: %f\nPosZ: %f\nPosRX: %f\nPosRY: %f\nPosRZ: %f",
//         VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
//         VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
//         Dialog_Show(playerid, DIALOG_MSEDIT, DIALOG_STYLE_LIST, "Modshop", string, "Select", "Cancel");
//     }
// 	return 1;
// }

// Dialog:DIALOG_MSEDITRZ(playerid, response, listitem, inputtext[])
// {
//     if(response)
//     {
//         new 
//             slot = Player_EditVehicleObjectSlot[playerid],
//             vehicleid = Player_EditVehicleObject[playerid]        
// 		;
//         new Float:posisi = floatstr(inputtext);
//         AttachDynamicObjectToVehicle(VehicleObjects[vehicleid][slot][vehObject], pvData[vehicleid][cVeh], 
//         VehicleObjects[vehicleid][slot][vehObjectPosX], 
//         VehicleObjects[vehicleid][slot][vehObjectPosY], 
//         VehicleObjects[vehicleid][slot][vehObjectPosZ], 
//         VehicleObjects[vehicleid][slot][vehObjectPosRX], 
//         VehicleObjects[vehicleid][slot][vehObjectPosRY], 
//         posisi);
        

//         VehicleObjects[vehicleid][slot][vehObjectPosRZ] = posisi;
//         new string[512];
//         format(string, sizeof(string), "PosX: %f\nPosY: %f\nPosZ: %f\nPosRX: %f\nPosRY: %f\nPosRZ: %f",
//         VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ],
//         VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
//         Dialog_Show(playerid, DIALOG_MSEDIT, DIALOG_STYLE_LIST, "Modshop", string, "Select", "Cancel");
//     }
// 	return 1;
// }

Dialog:VEH_OBJECT_TEXTNAME(playerid, response, listitem, inputtext[])
{
	if(response)
	{
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;

		if(isnull(inputtext))
			return Dialog_Show(playerid, VEH_OBJECT_TEXTNAME, DIALOG_STYLE_INPUT, "Input Text Name", "Error : Text tidak boleh kosong\n\nInput Text name 32 Character : ", "Select", "Close");

		format(VehicleObjects[vehicleid][slot][vehObjectText], 128, "%s", inputtext);
		Vehicle_ObjectTextSync(vehicleid, slot);
        Dialog_Show(playerid, VACCSE1, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nText Name\nText Size\nText Font\nText Color\nRemove Modification\nSave", "Select", "Back");
		
	}
	return 1;
}
Dialog:VEH_OBJECT_TEXTCOLOR(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]        
		;

        if(!(0 <= strval(inputtext) <= sizeof(ColorList)-1))
            return Dialog_Show(playerid, VEH_OBJECT_TEXTFONT, DIALOG_STYLE_INPUT, "Input Text Color", color_string, "Update", "Close");
		
		VehicleObjects[vehicleid][slot][vehObjectFontColor] = strval(inputtext);
		Vehicle_ObjectTextSync(vehicleid, slot);
        Dialog_Show(playerid, VACCSE1, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nText Name\nText Size\nText Font\nText Color\nRemove Modification\nSave", "Select", "Back");
    }
    return 1;
}
Dialog:VEH_OBJECT_TEXTSIZE(playerid, response, listitem, inputtext[])
{
	if(response)
	{
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;

		if(!(0 < strval(inputtext) <= 200))
			return Dialog_Show(playerid, VEH_OBJECT_TEXTSIZE, DIALOG_STYLE_INPUT, "Input Text Size", "Error: ukuran dibatasi mulai dari 1 sampai 200\n\nMasukkan ukuran font mulai dari angka 1 sampai 200 :", "Update", "Back");

		VehicleObjects[vehicleid][slot][vehObjectFontSize] = strval(inputtext);
		Vehicle_ObjectTextSync(vehicleid, slot);
        Dialog_Show(playerid, VACCSE1, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nText Name\nText Size\nText Font\nText Color\nRemove Modification\nSave", "Select", "Back");
	}
	return 1;
}

Dialog:VEH_OBJECT_TEXTFONT(playerid, response, listitem, inputtext[])
{
	if(response)
	{
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;

		if(listitem == sizeof(FontNames) - 1)
			return Dialog_Show(playerid, VEH_OBJECT_FONTCUSTOM, DIALOG_STYLE_INPUT, "Input Text Font - Custom Font", "Masukkan nama font yang akan kamu ubah:", "Input", "Back");

		format(VehicleObjects[vehicleid][slot][vehObjectFont], 32, "%s", inputtext);
		Vehicle_ObjectTextSync(vehicleid, slot);
        Dialog_Show(playerid, VACCSE1, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nText Name\nText Size\nText Font\nText Color\nRemove Modification\nSave", "Select", "Back");
	}
	return 1;
}
Dialog:VEH_OBJECT_FONTCUSTOM(playerid, response, listitem, inputtext[])
{
	if(response)
	{
        new 
            slot = Player_EditVehicleObjectSlot[playerid],
            vehicleid = Player_EditVehicleObject[playerid]
        ;
		if(!strlen(inputtext))
			return Dialog_Show(playerid, VEH_OBJECT_FONTCUSTOM, DIALOG_STYLE_INPUT, "Input Text Font - Custom Font", "Error : nama font tidak boleh kosong!\n\nMasukkan nama font yang akan kamu ubah\nPastikan nama font benar!:", "Input", "Back");

		format(VehicleObjects[vehicleid][slot][vehObjectFont], 32, "%s", inputtext);
		Vehicle_ObjectTextSync(vehicleid, slot);
        Dialog_Show(playerid, VACCSE1, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nText Name\nText Size\nText Font\nText Color\nRemove Modification\nSave", "Select", "Back");
	}
	return 1;
}		