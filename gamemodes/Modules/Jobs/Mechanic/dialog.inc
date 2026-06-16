
Dialog:MechanicExamine(playerid, response, listitem, inputtext[]) {
    if(response) {
        new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);
        if(!GetHoodStatus(vehicleid) && !IsABike(vehicleid)) return Error(playerid,"Please open the vehicle Hood before checking services");
        if(vehicleid == INVALID_VEHICLE_ID) return Error(playerid, "Anda tidak berada di dekat kendaraan mana pun.");
        if(pData[playerid][pActivityTime] > 5) return Error(playerid, "You are currently doing another task!");
        Mechanic[playerid] = 0;
        pData[playerid][pActivityTime] = 0;
        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Examining Vehicle");
        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
        SendVehicleOwnedMessage(vehicleid, sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started examining your {00FFFF}%s", ReturnName2(playerid), GetVehicleName(vehicleid)));	
    }
    return 1;
}

Dialog:ImpoundTow(playerid, response, listitem, inputtext[]) {
    new i = gListedItems[playerid][listitem];
    if(response)  {
        PlayerTowImpound[playerid] = i;
        pvData[i][cimpoundTake] = playerid;
		SetPlayerRaceCheckpoint(playerid, 1, pvData[i][cPosX], pvData[i][cPosY], pvData[i][cPosZ], pvData[i][cPosX], pvData[i][cPosY], pvData[i][cPosZ], 3);
        SendCustomMessage(playerid, "HINT", "Ikuti Checkpoint untuk menderek mobil yang ingin di impound");
        SendCustomMessage(playerid, "NOTE", "Gunakan command '/tows' untuk mengaitkan kendaraan ke derek mobil anda");
    }
    return 1;
}

Dialog:DialogService(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    new Float:health, comp;
                    GetVehicleHealth(pData[playerid][pMechVeh], health);
                    if(health > 1000.0) health = 1000.0;
                    if(health > 0.0) health *= -1;
                    comp = floatround(health, floatround_round) / 10 + 100;
                    
                    if(pData[playerid][pComponent] < comp) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= comp;
                    pData[playerid][pScoreMecha] += comp;
                    SendClientMessageEx(playerid, COLOR_ARWIN, "MECHANIC: "WHITE_E"You repair the vehicle engine with the "YELLOW_E"%d component", comp);
                    Mechanic[playerid] = 1;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Fixing Engine");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"Have started repairing your {00FFFF}%s "WHITE_E"engine", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));	
                }
            }
            case 1:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    SendClientMessageEx(playerid, COLOR_ARWIN, "MECHANIC: "WHITE_E"You repair the vehicle wheels with "YELLOW_E"50 components");
                    Mechanic[playerid] = 2;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Fixing Tires");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"Have started repairing your {00FFFF}%s "WHITE_E"wheels", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));	
                }
            }
            case 2:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    new panels, doors, light, tires, comp;
                    
                    GetVehicleDamageStatus(pData[playerid][pMechVeh], panels, doors, light, tires);
                    new cpanels = panels / 1000000;
                    new lights = light / 2;
                    new pintu;
                    if(doors != 0) pintu = 5;
                    if(doors == 0) pintu = 0;
                    comp = cpanels + lights + pintu + 20;
                    
                    if(pData[playerid][pComponent] < comp) return Error(playerid, "Component anda kurang!");
                    if(comp <= 0) return Error(playerid, "This vehicle can't be fixing.");
                    pData[playerid][pComponent] -= comp;
                    pData[playerid][pScoreMecha] += comp;
                    
                    SendClientMessageEx(playerid, COLOR_ARWIN, "MECHANIC: "WHITE_E"You repair the vehicle body with "YELLOW_E"%d component", comp);
                    Mechanic[playerid] = 3;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Fixing Body");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"Have started repairing your {00FFFF}%s "WHITE_E"body", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));	
                }
            }
            case 3:
            {
                if(pData[playerid][pSkillMecha] < 2) return Error(playerid, "Skill Mechanic Anda harus level 2!");
                Dialog_Show(playerid, ChangeColor, DIALOG_STYLE_LIST, "Vehicle Menu", "Spray Car\nPaint Job Car", "Service", "Cancel");	
            }
            case 4:
            {
                if(pData[playerid][pSkillMecha] < 3) return Error(playerid, "Skill Mechanic Anda harus level 3!");
                Dialog_Show(playerid, DialogUpgrade, DIALOG_STYLE_LIST, "Vehicle Menu", "Reinforce Engine\t250 Component\nReinforce Body\t250 Component", "Upgrade", "Cancel");	
            }
            case 5:
            {
                if(pData[playerid][pSkillMecha] < 4) return Error(playerid, "Skill Mechanic Anda harus level 4!");
                new id = -1, info[256], name[64], count = 0;
                if((id = Vehicle_GetID(GetNearestVehicleToPlayer(playerid,4.0,false))) != -1 && pvData[id][cVeh] == GetNearestVehicleToPlayer(playerid,4.0,false)) {
                    strcat(info, "Model\tName\n");
                    strcat(info, sprintf("%d\tUninstall Paintjob\n", pvData[id][cPaintJob])), count++;
                    MechanicModification[playerid][0] = 0; // sentinel for paintjob row (listitem == 0)

                    for (new x = 0; x < 14; x ++) if (pvData[id][cMod][x] > 0) {
                        GetVehicleComponentName(pvData[id][cMod][x], name, sizeof(name));
                        strcat(info, sprintf("%d\t%s\n", pvData[id][cMod][x], name));
                        MechanicModification[playerid][count] = pvData[id][cMod][x];
                        count++;
                    }
                    if (count) Dialog_Show(playerid, UninstallMods, DIALOG_STYLE_TABLIST_HEADERS, "Uninstall Mods", info, "Uninstall", "Close");
                    else Error(playerid, "This vehicle doesn't have any mods!");
                }
                else if((id = VehicleData_GetID(GetNearestVehicleToPlayer(playerid,4.0,false))) != -1 && VehicleData[id][Vehicle] == GetNearestVehicleToPlayer(playerid,4.0,false)) {
                    strcat(info, "Model\tName\n");
                    strcat(info, sprintf("%d\tUninstall Paintjob\n", VehicleData[id][PaintJob])), count++;
                    MechanicModification[playerid][0] = 0; // sentinel for paintjob row (listitem == 0)

                    for (new x = 0; x < 14; x ++) if (VehicleData[id][Mod][x] > 0) {
                        GetVehicleComponentName(VehicleData[id][Mod][x], name, sizeof(name));
                        strcat(info, sprintf("%d\t%s\n", VehicleData[id][Mod][x], name));
                        MechanicModification[playerid][count] = VehicleData[id][Mod][x];
                        count++;
                    }
                    if (count) Dialog_Show(playerid, UninstallMod, DIALOG_STYLE_TABLIST_HEADERS, "Uninstall Mods", info, "Uninstall", "Close");
                    else Error(playerid, "This vehicle doesn't have any mods!");
                }
            }
            case 6:
            {
                if(pData[playerid][pSkillMecha] < 4) return Error(playerid, "Skill Mechanic Anda harus level 4!");
                new info[999], count = 0, modelid = GetVehicleModel(GetNearestVehicleToPlayer(playerid,4.0,false)), componentid, array[MAX_VEHICLE_COMPONENTS], name[MAX_VEHICLE_COMPONENT_NAME];
                strcat(info, "Modification\tComponent Cost\n");
                foreach(new wsid : Workshop) if(IsPlayerInRangeOfPoint(playerid, 10, WorkshopData[wsid][WorkshopPos][0], WorkshopData[wsid][WorkshopPos][1], WorkshopData[wsid][WorkshopPos][2])) {
                    if(!OwnerWorkshop(playerid, wsid) && !Workshop_IsEmployee(playerid, wsid)) return Error(playerid, "You're not employee or owner of this business.");
                    switch(WorkshopData[wsid][Type]) {
                        case 0: {
                            if(IsAVehicleTransfender(GetNearestVehicleToPlayer(playerid,4.0,false)) || IsAVehicleNone(GetNearestVehicleToPlayer(playerid,4.0,false)))
                            {
                                GetVehicleCompatibleUpgrades(modelid, array, sizeof(array), count);
                                for (new j; j < count; j++)
                                {
                                    componentid = array[j];
                                    if (IsVehicleUpgradeCompatible(modelid, componentid))
                                    {
                                        GetVehicleComponentName(componentid, name, sizeof(name));
                                        strcat(info, sprintf("%s\t50\n", name));
                                        MechanicModification[playerid][j] = componentid;
                                    }
                                }
                                Dialog_Show(playerid, InstallMods, DIALOG_STYLE_TABLIST_HEADERS, "Installing Modification", info, "Install", "Close");
                            }
                            else return Error(playerid, "Mobil type ini tidak cocok di workshop Transfender");
                        }
                        case 1: {
                            if(IsAVehicleWaaLocolow(GetNearestVehicleToPlayer(playerid,4.0,false)) || IsAVehicleNone(GetNearestVehicleToPlayer(playerid,4.0,false)))
                            {
                                GetVehicleCompatibleUpgrades(modelid, array, sizeof(array), count);
                                for (new j; j < count; j++)
                                {
                                    componentid = array[j];
                                    if (IsVehicleUpgradeCompatible(modelid, componentid))
                                    {
                                        GetVehicleComponentName(componentid, name, sizeof(name));
                                        strcat(info, sprintf("%s\t50\n", name));
                                        MechanicModification[playerid][j] = componentid;
                                    }
                                }
                                Dialog_Show(playerid, InstallMods, DIALOG_STYLE_TABLIST_HEADERS, "Installing Modification", info, "Install", "Close");
                            }
                            else return Error(playerid, "Mobil type ini tidak cocok di workshop WAA & Locolow");
                        }
                    }
                }
            }
        }
    }
    return 1;
}

Dialog:InstallMods(playerid, response, listitem, inputtext[]) {
    if (response) {
        new vehicleid = GetNearestVehicleToPlayer(playerid,4.0,false);
        if (vehicleid == INVALID_VEHICLE_ID) return Error(playerid, "You're not nearest any vehicle!");
        new component = MechanicModification[playerid][listitem];
        if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
        
        Mechanic[playerid] = 8;
        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
        
        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s "WHITE_E"mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
        pData[playerid][pMechColor1] = component;
        pData[playerid][pMechColor2] = 0;
    }
    return 1;
}

Dialog:UninstallMods(playerid, response, listitem, inputtext[]) {
    if (response) {
        new id = -1, vehicleid = GetNearestVehicleToPlayer(playerid,4.0,false), name[64];
        
        if (vehicleid == INVALID_VEHICLE_ID) return Error(playerid, "You're not nearest any vehicle!");
            
        if ((id = Vehicle_GetID(vehicleid)) != -1) {
            if (!listitem) {
                if (pvData[id][cPaintJob] == -1) return Error(playerid, "This vehicle doesn't have installed paintjob");

                pvData[id][cPaintJob] = -1;
                pData[playerid][pComponent] -= 50;
                pData[playerid][pScoreMecha] += 50;
                SendCustomMessage(playerid, "MECHANIC", "You've been successfully uninstalled paintjob");
                ChangeVehiclePaintjob(pvData[id][cVeh], 3);
                SendVehicleOwnedMessage(vehicleid, sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod removal", ReturnName2(playerid), GetVehicleName(vehicleid)));	
            } else {
                // TABLIST_HEADERS click doesn't guarantee inputtext contains component id.
                // Use stored mapping by listitem index.
                new component = MechanicModification[playerid][listitem];

                RemoveComponent(pvData[id][cVeh], component);
                GetVehicleComponentName(component, name, sizeof(name));
                pData[playerid][pComponent] -= 50;
                pData[playerid][pScoreMecha] += 50;
            }
        }
    }
    return 1;
}

Dialog:UninstallMod(playerid, response, listitem, inputtext[]) {
    if (response) {
        new id = -1, vehicleid = GetNearestVehicleToPlayer(playerid,4.0,false), name[64];
        
        if (vehicleid == INVALID_VEHICLE_ID) return Error(playerid, "You're not nearest any vehicle!");
            
        if ((id = VehicleData_GetID(vehicleid)) != -1) {
            if (!listitem) {
                if (VehicleData[id][PaintJob] == -1) return Error(playerid, "This vehicle doesn't have installed paintjob");

                VehicleData[id][PaintJob] = -1;
                pData[playerid][pComponent] -= 50;
                pData[playerid][pScoreMecha] += 50;
                SendCustomMessage(playerid, "MECHANIC", "You've been successfully uninstalled paintjob");
                ChangeVehiclePaintjob(VehicleData[id][Vehicle], 3);
            } else {
                new component = MechanicModification[playerid][listitem];

                RemoveComponentStatic(VehicleData[id][Vehicle], component);
                GetVehicleComponentName(component, name, sizeof(name));
                pData[playerid][pComponent] -= 50;
                pData[playerid][pScoreMecha] += 50;
            }
        }
    }
    return 1;
}

Dialog:ChangeColor(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(pData[playerid][pComponent] < 40) return Error(playerid, "Component anda kurang!");
                Dialog_Show(playerid, ServiceColor, DIALOG_STYLE_INPUT, "Respray Vehicle", "Input Color: contoh 1 1\n"RED_E"NOTE: "YELLOW_E"Tidak bisa lebih dari 255 atau kurang dari 0", "Next", "Close");
            }
            case 1:
            {
                if(pData[playerid][pComponent] < 40) return Error(playerid, "Component anda kurang!");
                Dialog_Show(playerid, Servicepaintjob, DIALOG_STYLE_INPUT, "Paintjob", "Enter the vehicle paintjob id:(0 - 2 | 3 - Remove paintJob)", "Paintjob", "Close");
            }
        }
    }
    return 1;
}

Dialog:ServiceColor(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new pos[2];
        if(!sscanf(inputtext, "dd",pos[0],pos[1])) 
        {
            pData[playerid][pMechColor1] = pos[0];
            pData[playerid][pMechColor2] = pos[1];
            if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
            if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
            {	
                if(pData[playerid][pComponent] < 40) return Error(playerid, "Component anda kurang!");
                pData[playerid][pComponent] -= 40;
                pData[playerid][pScoreMecha] += 40;
                Mechanic[playerid] = 4;
                PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Spraying Vehicle");
                for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                
                SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s changing color", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
            }
        }
    }
    return 1;
}

Dialog:Servicepaintjob(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        pData[playerid][pMechColor1] = floatround(strval(inputtext));
        
        if(pData[playerid][pMechColor1] < 0 || pData[playerid][pMechColor1] > 3)
            return Dialog_Show(playerid, DIALOG_SERVICE_PAINTJOB, DIALOG_STYLE_INPUT, "Paintjob", "Enter the vehicle paintjob id:(0 - 2 | 3 - Remove paintJob)", "Paintjob", "Close");
        
        if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
        if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
        {	
            if(pData[playerid][pComponent] < 40) return Error(playerid, "Component anda kurang!");
            pData[playerid][pComponent] -= 40;
            Mechanic[playerid] = 40;
            PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Painting Car");
            for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
            
            SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s paintjob", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
        }
    }
    return 1;
}

Dialog:DialogUpgrade(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new vehid = Vehicle_GetID(pData[playerid][pMechVeh]);
                if(vehid == -1 || pvData[vehid][cVeh] != pData[playerid][pMechVeh]) return Error(playerid, "Upgrade hanya bisa untuk kendaraan pribadi.");
                if(pvData[vehid][cMesinUpgrade] == 1) return Error(playerid, "Mobil ini sudah di upgrade!");
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 250) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 250;
                    pData[playerid][pScoreMecha] += 250;
                    
                    SendClientMessageEx(playerid, COLOR_ARWIN, "MECHANIC: "WHITE_E"You upgrade the vehicle engine with a "YELLOW_E"250 components");
                    Mechanic[playerid] = 6;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Upgrade Engine");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s upgrade engine", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 1:
            {
                new vehid = Vehicle_GetID(pData[playerid][pMechVeh]);
                if(vehid == -1 || pvData[vehid][cVeh] != pData[playerid][pMechVeh]) return Error(playerid, "Upgrade hanya bisa untuk kendaraan pribadi.");
                if(pvData[vehid][pvBodyUpgrade] == 1) return Error(playerid, "Mobil ini sudah di upgrade!");
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 250) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 250;
                    pData[playerid][pScoreMecha] += 250;
                    
                    SendClientMessageEx(playerid, COLOR_ARWIN, "MECHANIC: "WHITE_E"You upgrade the vehicle body with a "YELLOW_E"250 components");
                    Mechanic[playerid] = 7;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Upgrade Body");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s upgrade body", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
        }
    }
    return 1;
}

Dialog:MechaModification(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, ServiceWheels, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar", "Confirm", "back");
                }
            }
            case 1:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, ServiceSpoiler,DIALOG_STYLE_LIST,"Choose below","Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n","Choose","back");
                }
            }
            case 2:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, ServiceHoods, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n", "Confirm", "back");
                }
            }
            case 3:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, ServiceVents, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n", "Confirm", "back");
                }
            }
            case 4:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, ServiceLight, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n", "Confirm", "back");
                }
            }
            case 5:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, ServiceExhausts, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust", "Confirm", "back");
                }
            }
            case 6:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, ServiceFrontBumpers, DIALOG_STYLE_LIST, "Front bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper", "Confirm", "back");
                }
            }
            case 7:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, ServiceRearBumpers, DIALOG_STYLE_LIST, "Rear bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper", "Confirm", "back");
                }
            }
            case 8:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, ServiceRoofs, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop", "Confirm", "back");
                }
            }
            case 9:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, ServiceSideKirt, DIALOG_STYLE_LIST, "Side skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt", "Confirm", "back");
                }
            }
            case 10:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, ServiceBullbars, DIALOG_STYLE_LIST, "Bull bars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar", "Confirm", "back");
                }
            }
            case 11:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, DIALOG_SERVICE_SIDE_SKIRTS, DIALOG_STYLE_LIST, "Side skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt", "Confirm", "back");
                }
            }
            case 12:
            {
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    Dialog_Show(playerid, DIALOG_SERVICE_BULLBARS, DIALOG_STYLE_LIST, "Bull bars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar", "Confirm", "back");
                }
            }
            case 13:
            {
                pData[playerid][pMechColor1] = 1086;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 14:
            {
                pData[playerid][pMechColor1] = 1087;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 15:
            {
                pData[playerid][pMechColor1] = 1009;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 16:
            {
                pData[playerid][pMechColor1] = 1008;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 17:
            {
                pData[playerid][pMechColor1] = 1010;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
        }
    }
    return 1;
}

Dialog:ServiceWheels(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                pData[playerid][pMechColor1] = 1025;
                pData[playerid][pMechColor2] = 0;

                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 1:
            {
                pData[playerid][pMechColor1] = 1074;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 2:
            {
                pData[playerid][pMechColor1] = 1076;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 3:
            {
                pData[playerid][pMechColor1] = 1078;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 4:
            {
                pData[playerid][pMechColor1] = 1081;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 5:
            {
                pData[playerid][pMechColor1] = 1082;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 6:
            {
                pData[playerid][pMechColor1] = 1085;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 7:
            {
                pData[playerid][pMechColor1] = 1096;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 8:
            {
                pData[playerid][pMechColor1] = 1097;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 9:
            {
                pData[playerid][pMechColor1] = 1098;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 10:
            {
                pData[playerid][pMechColor1] = 1084;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 11:
            {
                pData[playerid][pMechColor1] = 1073;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 12:
            {
                pData[playerid][pMechColor1] = 1075;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 13:
            {
                pData[playerid][pMechColor1] = 1077;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 14:
            {
                pData[playerid][pMechColor1] = 1079;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 15:
            {
                pData[playerid][pMechColor1] = 1080;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
            case 16:
            {
                pData[playerid][pMechColor1] = 1083;
                pData[playerid][pMechColor2] = 0;
        
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {	
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    Mechanic[playerid] = 8;
                    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                    SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                }
            }
        }
    }
    return 1;
}

Dialog:ServiceSpoiler(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 70) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 562 ||
                    VehicleModel == 565 ||
                    VehicleModel == 559 ||
                    VehicleModel == 561 ||
                    VehicleModel == 558 ||
                    VehicleModel == 560)
                    {
                        if(VehicleModel == 562)
                        {
                            pData[playerid][pMechColor1] = 1147;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 565)
                        {
                            pData[playerid][pMechColor1] = 1049;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 559)
                        {
                            pData[playerid][pMechColor1] = 1162;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 561)
                        {
                            pData[playerid][pMechColor1] = 1058;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 558)
                        {
                            pData[playerid][pMechColor1] = 1164;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 560)
                        {
                            pData[playerid][pMechColor1] = 1138;
                            pData[playerid][pMechColor2] = 0;
                        }
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 1:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 562 ||
                    VehicleModel == 565 ||
                    VehicleModel == 559 ||
                    VehicleModel == 561 ||
                    VehicleModel == 558 ||
                    VehicleModel == 560)
                    {
                        if(VehicleModel == 562)
                        {
                            pData[playerid][pMechColor1] = 1146;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 565)
                        {
                            pData[playerid][pMechColor1] = 1050;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 559)
                        {
                            pData[playerid][pMechColor1] = 1158;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 561)
                        {
                            pData[playerid][pMechColor1] = 1060;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 558)
                        {
                            pData[playerid][pMechColor1] = 1163;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 560)
                        {
                            pData[playerid][pMechColor1] = 1139;
                            pData[playerid][pMechColor2] = 0;
                        }
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 2:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 401 ||
                    VehicleModel == 518 ||
                    VehicleModel == 527 ||
                    VehicleModel == 415 ||
                    VehicleModel == 546 ||
                    VehicleModel == 603 ||
                    VehicleModel == 426 ||
                    VehicleModel == 436 ||
                    VehicleModel == 405 ||
                    VehicleModel == 477 ||
                    VehicleModel == 580 ||
                    VehicleModel == 550 ||
                    VehicleModel == 549)
                    {
            
                        pData[playerid][pMechColor1] = 1001;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 3:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 518 ||
                    VehicleModel == 415 ||
                    VehicleModel == 546 ||
                    VehicleModel == 517 ||
                    VehicleModel == 603 ||
                    VehicleModel == 405 ||
                    VehicleModel == 477 ||
                    VehicleModel == 580 ||
                    VehicleModel == 550 ||
                    VehicleModel == 549)
                    {
            
                        pData[playerid][pMechColor1] = 1023;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 4:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 518 ||
                    VehicleModel == 415 ||
                    VehicleModel == 401 ||
                    VehicleModel == 517 ||
                    VehicleModel == 426 ||
                    VehicleModel == 436 ||
                    VehicleModel == 477 ||
                    VehicleModel == 547 ||
                    VehicleModel == 550 ||
                    VehicleModel == 549)
                    {
            
                        pData[playerid][pMechColor1] = 1003;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 5:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 589 ||
                    VehicleModel == 492 ||
                    VehicleModel == 547 ||
                    VehicleModel == 405)
                    {
            
                        pData[playerid][pMechColor1] = 1000;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 6:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 527 ||
                    VehicleModel == 542 ||
                    VehicleModel == 405)
                    {
            
                        pData[playerid][pMechColor1] = 1014;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 7:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 527 ||
                    VehicleModel == 542)
                    {
            
                        pData[playerid][pMechColor1] = 1015;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 8:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 546 ||
                    VehicleModel == 517)
                    {
            
                        pData[playerid][pMechColor1] = 1002;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
        }
    }
    return 1;
}

Dialog:ServiceHoods(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(
                    VehicleModel == 401 ||
                    VehicleModel == 518 ||
                    VehicleModel == 589 ||
                    VehicleModel == 492 ||
                    VehicleModel == 426 ||
                    VehicleModel == 550)
                    {
            
                        pData[playerid][pMechColor1] = 1005;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 1:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(
                    VehicleModel == 401 ||
                    VehicleModel == 402 ||
                    VehicleModel == 546 ||
                    VehicleModel == 426 ||
                    VehicleModel == 550)
                    {
            
                        pData[playerid][pMechColor1] = 1004;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 2:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 401)
                    {
            
                        pData[playerid][pMechColor1] = 1011;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 3:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 549)
                    {
            
                        pData[playerid][pMechColor1] = 1012;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
        }
    }
    return 1;
}

Dialog:ServiceVents(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 401 ||
                    VehicleModel == 518 ||
                    VehicleModel == 546 ||
                    VehicleModel == 517 ||
                    VehicleModel == 603 ||
                    VehicleModel == 547 ||
                    VehicleModel == 439 ||
                    VehicleModel == 550 ||
                    VehicleModel == 549)
                    {
            
                        pData[playerid][pMechColor1] = 1142;
                        pData[playerid][pMechColor2] = 1143;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 1:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 401 ||
                    VehicleModel == 518 ||
                    VehicleModel == 589 ||
                    VehicleModel == 546 ||
                    VehicleModel == 517 ||
                    VehicleModel == 603 ||
                    VehicleModel == 439 ||
                    VehicleModel == 550 ||
                    VehicleModel == 549)
                    {
            
                        pData[playerid][pMechColor1] = 1144;
                        pData[playerid][pMechColor2] = 1145;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
        }
    }
    return 1;
}

Dialog:ServiceLight(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 401 ||
                    VehicleModel == 518 ||
                    VehicleModel == 589 ||
                    VehicleModel == 400 ||
                    VehicleModel == 436 ||
                    VehicleModel == 439)
                    {
            
                        pData[playerid][pMechColor1] = 1013;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 1:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 589 ||
                    VehicleModel == 603 ||
                    VehicleModel == 400)
                    {
            
                        pData[playerid][pMechColor1] = 1024;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
        }
    }
    return 1;
}

Dialog:ServiceExhausts(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 562 ||
                    VehicleModel == 565 ||
                    VehicleModel == 559 ||
                    VehicleModel == 558 ||
                    VehicleModel == 561 ||
                    VehicleModel == 560)
                    {
                        if(VehicleModel == 562)
                        {
                            pData[playerid][pMechColor1] = 1034;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 565)
                        {
                            pData[playerid][pMechColor1] = 1046;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 559)
                        {
                            pData[playerid][pMechColor1] = 1065;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 561)
                        {
                            pData[playerid][pMechColor1] = 1064;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 560)
                        {
                            pData[playerid][pMechColor1] = 1028;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 558)
                        {
                            pData[playerid][pMechColor1] = 1089;
                            pData[playerid][pMechColor2] = 0;
                        }
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 1:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 70) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 562 ||
                    VehicleModel == 565 ||
                    VehicleModel == 559 ||
                    VehicleModel == 558 ||
                    VehicleModel == 561 ||
                    VehicleModel == 560)
                    {
                        if(VehicleModel == 562)
                        {
                            pData[playerid][pMechColor1] = 1037;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 565)
                        {
                            pData[playerid][pMechColor1] = 1045;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 559)
                        {
                            pData[playerid][pMechColor1] = 1066;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 561)
                        {
                            pData[playerid][pMechColor1] = 1059;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 560)
                        {
                            pData[playerid][pMechColor1] = 1029;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 558)
                        {
                            pData[playerid][pMechColor1] = 1092;
                            pData[playerid][pMechColor2] = 0;
                        }
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 2:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 575 ||
                    VehicleModel == 534 ||
                    VehicleModel == 567 ||
                    VehicleModel == 536 ||
                    VehicleModel == 576 ||
                    VehicleModel == 535)
                    {
                        if(VehicleModel == 575)
                        {
                            pData[playerid][pMechColor1] = 1044;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 534)
                        {
                            pData[playerid][pMechColor1] = 1126;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 567)
                        {
                            pData[playerid][pMechColor1] = 1129;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 536)
                        {
                            pData[playerid][pMechColor1] = 1104;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 576)
                        {
                            pData[playerid][pMechColor1] = 1113;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 535)
                        {
                            pData[playerid][pMechColor1] = 1136;
                            pData[playerid][pMechColor2] = 0;
                        }
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 3:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 575 ||
                    VehicleModel == 534 ||
                    VehicleModel == 567 ||
                    VehicleModel == 536 ||
                    VehicleModel == 576 ||
                    VehicleModel == 535)
                    {
                        if(VehicleModel == 575)
                        {
                            pData[playerid][pMechColor1] = 1043;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 534)
                        {
                            pData[playerid][pMechColor1] = 1127;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 567)
                        {
                            pData[playerid][pMechColor1] = 1132;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 536)
                        {
                            pData[playerid][pMechColor1] = 1105;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 576)
                        {
                            pData[playerid][pMechColor1] = 1135;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 535)
                        {
                            pData[playerid][pMechColor1] = 1114;
                            pData[playerid][pMechColor2] = 0;
                        }
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 4:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(
                    VehicleModel == 401 ||
                    VehicleModel == 518 ||
                    VehicleModel == 527 ||
                    VehicleModel == 542 ||
                    VehicleModel == 589 ||
                    VehicleModel == 400 ||
                    VehicleModel == 517 ||
                    VehicleModel == 603 ||
                    VehicleModel == 426 ||
                    VehicleModel == 547 ||
                    VehicleModel == 405 ||
                    VehicleModel == 580 ||
                    VehicleModel == 550 ||
                    VehicleModel == 549 ||
                    VehicleModel == 477)
                    {
                        
                        pData[playerid][pMechColor1] = 1020;
                        pData[playerid][pMechColor2] = 0;
                            
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 5:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(
                    VehicleModel == 527 ||
                    VehicleModel == 542 ||
                    VehicleModel == 400 ||
                    VehicleModel == 426 ||
                    VehicleModel == 436 ||
                    VehicleModel == 547 ||
                    VehicleModel == 405 ||
                    VehicleModel == 477)
                    {
                        
                        pData[playerid][pMechColor1] = 1021;
                        pData[playerid][pMechColor2] = 0;
                            
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 6:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 436)
                    {
                        
                        pData[playerid][pMechColor1] = 1022;
                        pData[playerid][pMechColor2] = 0;
                            
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 7:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(
                    VehicleModel == 518 ||
                    VehicleModel == 415 ||
                    VehicleModel == 542 ||
                    VehicleModel == 546 ||
                    VehicleModel == 400 ||
                    VehicleModel == 517 ||
                    VehicleModel == 603 ||
                    VehicleModel == 426 ||
                    VehicleModel == 436 ||
                    VehicleModel == 547 ||
                    VehicleModel == 405 ||
                    VehicleModel == 550 ||
                    VehicleModel == 549 ||
                    VehicleModel == 477)
                    {
                        
                        pData[playerid][pMechColor1] = 1019;
                        pData[playerid][pMechColor2] = 0;
                            
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 8:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(
                    VehicleModel == 401 ||
                    VehicleModel == 518 ||
                    VehicleModel == 415 ||
                    VehicleModel == 542 ||
                    VehicleModel == 546 ||
                    VehicleModel == 400 ||
                    VehicleModel == 517 ||
                    VehicleModel == 603 ||
                    VehicleModel == 426 ||
                    VehicleModel == 415 ||
                    VehicleModel == 547 ||
                    VehicleModel == 405 ||
                    VehicleModel == 550 ||
                    VehicleModel == 549 ||
                    VehicleModel == 477)
                    {
                        
                        pData[playerid][pMechColor1] = 1018;
                        pData[playerid][pMechColor2] = 0;
                            
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
        }
    }
    return 1;
}

Dialog:ServiceFrontBumpers(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 562 ||
                    VehicleModel == 565 ||
                    VehicleModel == 559 ||
                    VehicleModel == 561 ||
                    VehicleModel == 558 ||
                    VehicleModel == 560)
                    {
                        if(VehicleModel == 562)
                        {
                            pData[playerid][pMechColor1] = 1171;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 565)
                        {
                            pData[playerid][pMechColor1] = 1153;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 559)
                        {
                            pData[playerid][pMechColor1] = 1160;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 561)
                        {
                            pData[playerid][pMechColor1] = 1155;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 558)
                        {
                            pData[playerid][pMechColor1] = 1166;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 560)
                        {
                            pData[playerid][pMechColor1] = 1169;
                            pData[playerid][pMechColor2] = 0;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 1:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 562 ||
                    VehicleModel == 565 ||
                    VehicleModel == 559 ||
                    VehicleModel == 561 ||
                    VehicleModel == 558 ||
                    VehicleModel == 560)
                    {
                        if(VehicleModel == 562)
                        {
                            pData[playerid][pMechColor1] = 1172;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 565)
                        {
                            pData[playerid][pMechColor1] = 1152;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 559)
                        {
                            pData[playerid][pMechColor1] = 1173;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 561)
                        {
                            pData[playerid][pMechColor1] = 1157;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 558)
                        {
                            pData[playerid][pMechColor1] = 1165;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 560)
                        {
                            pData[playerid][pMechColor1] = 1170;
                            pData[playerid][pMechColor2] = 0;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 2:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 575 ||
                    VehicleModel == 534 ||
                    VehicleModel == 567 ||
                    VehicleModel == 536 ||
                    VehicleModel == 576 ||
                    VehicleModel == 535)
                    {
                        if(VehicleModel == 575)
                        {
                            pData[playerid][pMechColor1] = 1174;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 534)
                        {
                            pData[playerid][pMechColor1] = 1179;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 567)
                        {
                            pData[playerid][pMechColor1] = 1189;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 536)
                        {
                            pData[playerid][pMechColor1] = 1182;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 576)
                        {
                            pData[playerid][pMechColor1] = 1191;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 535)
                        {
                            pData[playerid][pMechColor1] = 1115;
                            pData[playerid][pMechColor2] = 0;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 3:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 575 ||
                    VehicleModel == 534 ||
                    VehicleModel == 567 ||
                    VehicleModel == 536 ||
                    VehicleModel == 576 ||
                    VehicleModel == 535)
                    {
                        if(VehicleModel == 575)
                        {
                            pData[playerid][pMechColor1] = 1175;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 534)
                        {
                            pData[playerid][pMechColor1] = 1185;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 567)
                        {
                            pData[playerid][pMechColor1] = 1188;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 536)
                        {
                            pData[playerid][pMechColor1] = 1181;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 576)
                        {
                            pData[playerid][pMechColor1] = 1190;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 535)
                        {
                            pData[playerid][pMechColor1] = 1116;
                            pData[playerid][pMechColor2] = 0;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
        }
    }
    return 1;
}

Dialog:ServiceRearBumpers(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 562 ||
                    VehicleModel == 565 ||
                    VehicleModel == 559 ||
                    VehicleModel == 561 ||
                    VehicleModel == 558 ||
                    VehicleModel == 560)
                    {
                        if(VehicleModel == 562)
                        {
                            pData[playerid][pMechColor1] = 1149;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 565)
                        {
                            pData[playerid][pMechColor1] = 1150;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 559)
                        {
                            pData[playerid][pMechColor1] = 1159;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 561)
                        {
                            pData[playerid][pMechColor1] = 1154;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 558)
                        {
                            pData[playerid][pMechColor1] = 1168;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 560)
                        {
                            pData[playerid][pMechColor1] = 1141;
                            pData[playerid][pMechColor2] = 0;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 1:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 562 ||
                    VehicleModel == 565 ||
                    VehicleModel == 559 ||
                    VehicleModel == 561 ||
                    VehicleModel == 558 ||
                    VehicleModel == 560)
                    {
                        if(VehicleModel == 562)
                        {
                            pData[playerid][pMechColor1] = 1148;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 565)
                        {
                            pData[playerid][pMechColor1] = 1151;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 559)
                        {
                            pData[playerid][pMechColor1] = 1161;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 561)
                        {
                            pData[playerid][pMechColor1] = 1156;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 558)
                        {
                            pData[playerid][pMechColor1] = 1167;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 560)
                        {
                            pData[playerid][pMechColor1] = 1140;
                            pData[playerid][pMechColor2] = 0;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 2:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 575 ||
                    VehicleModel == 534 ||
                    VehicleModel == 567 ||
                    VehicleModel == 536 ||
                    VehicleModel == 576 ||
                    VehicleModel == 535)
                    {
                        if(VehicleModel == 575)
                        {
                            pData[playerid][pMechColor1] = 1176;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 534)
                        {
                            pData[playerid][pMechColor1] = 1180;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 567)
                        {
                            pData[playerid][pMechColor1] = 1187;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 536)
                        {
                            pData[playerid][pMechColor1] = 1184;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 576)
                        {
                            pData[playerid][pMechColor1] = 1192;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 535)
                        {
                            pData[playerid][pMechColor1] = 1109;
                            pData[playerid][pMechColor2] = 0;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 3:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 575 ||
                    VehicleModel == 534 ||
                    VehicleModel == 567 ||
                    VehicleModel == 536 ||
                    VehicleModel == 576 ||
                    VehicleModel == 535)
                    {
                        if(VehicleModel == 575)
                        {
                            pData[playerid][pMechColor1] = 1177;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 534)
                        {
                            pData[playerid][pMechColor1] = 1178;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 567)
                        {
                            pData[playerid][pMechColor1] = 1186;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 536)
                        {
                            pData[playerid][pMechColor1] = 1183;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 576)
                        {
                            pData[playerid][pMechColor1] = 1193;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 535)
                        {
                            pData[playerid][pMechColor1] = 1110;
                            pData[playerid][pMechColor2] = 0;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
        }
    }
    return 1;
}

Dialog:ServiceRoofs(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 562 ||
                    VehicleModel == 565 ||
                    VehicleModel == 559 ||
                    VehicleModel == 561 ||
                    VehicleModel == 558 ||
                    VehicleModel == 560)
                    {
                        if(VehicleModel == 562)
                        {
                            pData[playerid][pMechColor1] = 1038;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 565)
                        {
                            pData[playerid][pMechColor1] = 1054;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 559)
                        {
                            pData[playerid][pMechColor1] = 1067;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 561)
                        {
                            pData[playerid][pMechColor1] = 1055;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 558)
                        {
                            pData[playerid][pMechColor1] = 1088;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 560)
                        {
                            pData[playerid][pMechColor1] = 1032;
                            pData[playerid][pMechColor2] = 0;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 1:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 562 ||
                    VehicleModel == 565 ||
                    VehicleModel == 559 ||
                    VehicleModel == 561 ||
                    VehicleModel == 558 ||
                    VehicleModel == 560)
                    {
                        if(VehicleModel == 562)
                        {
                            pData[playerid][pMechColor1] = 1038;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 565)
                        {
                            pData[playerid][pMechColor1] = 1053;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 559)
                        {
                            pData[playerid][pMechColor1] = 1068;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 561)
                        {
                            pData[playerid][pMechColor1] = 1061;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 558)
                        {
                            pData[playerid][pMechColor1] = 1091;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 560)
                        {
                            pData[playerid][pMechColor1] = 1033;
                            pData[playerid][pMechColor2] = 0;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 2:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 567 ||
                    VehicleModel == 536)
                    {
                        if(VehicleModel == 567)
                        {
                            pData[playerid][pMechColor1] = 1130;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 536)
                        {
                            pData[playerid][pMechColor1] = 1128;
                            pData[playerid][pMechColor2] = 0;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 3:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 567 ||
                    VehicleModel == 536)
                    {
                        if(VehicleModel == 567)
                        {
                            pData[playerid][pMechColor1] = 1131;
                            pData[playerid][pMechColor2] = 0;
                        }
                        if(VehicleModel == 536)
                        {
                            pData[playerid][pMechColor1] = 1103;
                            pData[playerid][pMechColor2] = 0;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 4:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(
                    VehicleModel == 401 ||
                    VehicleModel == 518 ||
                    VehicleModel == 589 ||
                    VehicleModel == 492 ||
                    VehicleModel == 546 ||
                    VehicleModel == 603 ||
                    VehicleModel == 426 ||
                    VehicleModel == 436 ||
                    VehicleModel == 580 ||
                    VehicleModel == 550 ||
                    VehicleModel == 477)
                    {

                        pData[playerid][pMechColor1] = 1006;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
        }
    }
    return 1;
}

Dialog:ServiceSideKirt(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 562 ||
                    VehicleModel == 565 ||
                    VehicleModel == 559 ||
                    VehicleModel == 561 ||
                    VehicleModel == 558 ||
                    VehicleModel == 560)
                    {
                        if(VehicleModel == 562)
                        {
                            pData[playerid][pMechColor1] = 1036;
                            pData[playerid][pMechColor2] = 1040;
                        }
                        if(VehicleModel == 565)
                        {
                            pData[playerid][pMechColor1] = 1047;
                            pData[playerid][pMechColor2] = 1051;
                        }
                        if(VehicleModel == 559)
                        {
                            pData[playerid][pMechColor1] = 1069;
                            pData[playerid][pMechColor2] = 1071;
                        }
                        if(VehicleModel == 561)
                        {
                            pData[playerid][pMechColor1] = 1056;
                            pData[playerid][pMechColor2] = 1062;
                        }
                        if(VehicleModel == 558)
                        {
                            pData[playerid][pMechColor1] = 1090;
                            pData[playerid][pMechColor2] = 1094;
                        }
                        if(VehicleModel == 560)
                        {
                            pData[playerid][pMechColor1] = 1026;
                            pData[playerid][pMechColor2] = 1027;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 1:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 562 ||
                    VehicleModel == 565 ||
                    VehicleModel == 559 ||
                    VehicleModel == 561 ||
                    VehicleModel == 558 ||
                    VehicleModel == 560)
                    {
                        if(VehicleModel == 562)
                        {
                            pData[playerid][pMechColor1] = 1039;
                            pData[playerid][pMechColor2] = 1041;
                        }
                        if(VehicleModel == 565)
                        {
                            pData[playerid][pMechColor1] = 1048;
                            pData[playerid][pMechColor2] = 1052;
                        }
                        if(VehicleModel == 559)
                        {
                            pData[playerid][pMechColor1] = 1070;
                            pData[playerid][pMechColor2] = 1072;
                        }
                        if(VehicleModel == 561)
                        {
                            pData[playerid][pMechColor1] = 1057;
                            pData[playerid][pMechColor2] = 1063;
                        }
                        if(VehicleModel == 558)
                        {
                            pData[playerid][pMechColor1] = 1093;
                            pData[playerid][pMechColor2] = 1095;
                        }
                        if(VehicleModel == 560)
                        {
                            pData[playerid][pMechColor1] = 1031;
                            pData[playerid][pMechColor2] = 1030;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 2:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 575 ||
                    VehicleModel == 536 ||
                    VehicleModel == 576 ||
                    VehicleModel == 567)
                    {
                        if(VehicleModel == 575)
                        {
                            pData[playerid][pMechColor1] = 1042;
                            pData[playerid][pMechColor2] = 1099;
                        }
                        if(VehicleModel == 536)
                        {
                            pData[playerid][pMechColor1] = 1108;
                            pData[playerid][pMechColor2] = 1107;
                        }
                        if(VehicleModel == 576)
                        {
                            pData[playerid][pMechColor1] = 1134;
                            pData[playerid][pMechColor2] = 1137;
                        }
                        if(VehicleModel == 567)
                        {
                            pData[playerid][pMechColor1] = 1102;
                            pData[playerid][pMechColor2] = 1133;
                        }
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 3:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 534)
                    {
            
                        pData[playerid][pMechColor1] = 1102;
                        pData[playerid][pMechColor2] = 1101;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 4:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 534)
                    {
            
                        pData[playerid][pMechColor1] = 1106;
                        pData[playerid][pMechColor2] = 1124;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 5:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 535)
                    {
            
                        pData[playerid][pMechColor1] = 1118;
                        pData[playerid][pMechColor2] = 1120;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 6:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 535)
                    {
            
                        pData[playerid][pMechColor1] = 1119;
                        pData[playerid][pMechColor2] = 1121;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 7:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(
                    VehicleModel == 401 ||
                    VehicleModel == 518 ||
                    VehicleModel == 527 ||
                    VehicleModel == 415 ||
                    VehicleModel == 589 ||
                    VehicleModel == 546 ||
                    VehicleModel == 517 ||
                    VehicleModel == 603 ||
                    VehicleModel == 436 ||
                    VehicleModel == 439 ||
                    VehicleModel == 580 ||
                    VehicleModel == 549 ||
                    VehicleModel == 477)
                    {
            
                        pData[playerid][pMechColor1] = 1007;
                        pData[playerid][pMechColor2] = 1017;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
        }
    }
    return 1;
}

Dialog:ServiceBullbars(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 534)
                    {
            
                        pData[playerid][pMechColor1] = 1100;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 1:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 534)
                    {
            
                        pData[playerid][pMechColor1] = 1123;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 2:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 534)
                    {
            
                        pData[playerid][pMechColor1] = 1125;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
            case 3:
            {
                new VehicleModel = GetVehicleModel(pData[playerid][pMechVeh]);
                
                if(Mechanic[playerid] != -1) return Error(playerid, "You already checking vehicle!");
                if(GetNearestVehicleToPlayer(playerid, 3.8, false) == pData[playerid][pMechVeh])
                {
                    if(pData[playerid][pComponent] < 50) return Error(playerid, "Component anda kurang!");
                    if(VehicleModel == 534)
                    {
            
                        pData[playerid][pMechColor1] = 1117;
                        pData[playerid][pMechColor2] = 0;
                        
                        pData[playerid][pComponent] -= 50;
                        pData[playerid][pScoreMecha] += 50;
                        Mechanic[playerid] = 8;
                        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Installing mod");
                        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
                        
                        SendVehicleOwnedMessage(pData[playerid][pMechVeh], sprintf("MECHANIC: "YELLOW_E"%s "WHITE_E"has started on your {00FFFF}%s mod installation", ReturnName2(playerid), GetVehicleName(pData[playerid][pMechVeh])));
                    }
                    else return Error(playerid, "This vehicle is not supported!");
                }
            }
        }
    }
    return 1;
}
