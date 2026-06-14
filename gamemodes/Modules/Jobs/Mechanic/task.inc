ptask MechanicExam[150](playerid) {
    if(pData[playerid][pJob] == 2 || pData[playerid][pJob2] == 2) {
        if(Mechanic[playerid] == 0) {
            pData[playerid][pActivityTime]++;
            SetProgressBar(playerid, pData[playerid][pActivityTime]);
            if(pData[playerid][pActivityTime] >= 100)
            {
                pData[playerid][pMechVeh] = GetNearestVehicleToPlayer(playerid, 3.5, false);
                Mechanic[playerid] = -1;
                pData[playerid][pActivityTime] = 0;
                for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
                ClearAnimations(playerid);
                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
            }
        }
    }
    return 1;
}

ptask MechanicRepair[500](playerid) {
    new id = -1;
    if(pData[playerid][pJob] == 2 || pData[playerid][pJob2] == 2) {
        switch(Mechanic[playerid]) {
            case 1: {
                pData[playerid][pActivityTime]++;
                SetProgressBar(playerid, pData[playerid][pActivityTime]);
                
                if(pData[playerid][pActivityTime] >= 100)
                {
                    new vehicleid = pData[playerid][pMechVeh];
                    if(vehicleid != INVALID_VEHICLE_ID)
                    {
                        if ((id = Vehicle_GetID(vehicleid)) != -1 && pvData[id][cVeh] == vehicleid && pvData[id][cMesinUpgrade]) {
                            SetVehicleHealth(vehicleid, 2000.0); 
                        }
                        else SetVehicleHealth(vehicleid, 1000.0);
                    }
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    pData[playerid][pActivityTime] = 0;
                    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
                    ClearAnimations(playerid);
                    Mechanic[playerid] = -1;
                }
            }
            case 2: {
                pData[playerid][pActivityTime]++;
                SetProgressBar(playerid, pData[playerid][pActivityTime]);
                
                if(pData[playerid][pActivityTime] >= 100)
                {
                    new panels, doors, light, tires, vehicleid = pData[playerid][pMechVeh];
                    if(vehicleid != INVALID_VEHICLE_ID)
                    {
                        GetVehicleDamageStatus(vehicleid, panels, doors, light, tires);		
                        UpdateVehicleDamageStatus(vehicleid, panels, doors, light, 0);
                    }
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    pData[playerid][pActivityTime] = 0;
                    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
                    ClearAnimations(playerid);
                    Mechanic[playerid] = -1;
                }
            }
            case 3: {
                pData[playerid][pActivityTime]++;
                SetProgressBar(playerid, pData[playerid][pActivityTime]);
                
                if(pData[playerid][pActivityTime] >= 100)
                {
                    new panels, doors, light, tires, vehicleid = pData[playerid][pMechVeh];
                    if(vehicleid != INVALID_VEHICLE_ID)
                    {
                        GetVehicleDamageStatus(vehicleid, panels, doors, light, tires);		
                        UpdateVehicleDamageStatus(vehicleid, 0, 0, 0, tires);
                    }
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    pData[playerid][pActivityTime] = 0;
                    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
                    ClearAnimations(playerid);
                    Mechanic[playerid] = -1;
                }
            }
        }
    }
    return 1;
}

ptask MechanicRepaint[800](playerid) {
    if(pData[playerid][pJob] == 2 || pData[playerid][pJob2] == 2) {
        new id = -1;
        new vehicleid = pData[playerid][pMechVeh];
        switch(Mechanic[playerid]) {
            case 4: {
                pData[playerid][pActivityTime]++;
                SetProgressBar(playerid, pData[playerid][pActivityTime]);
                
                if(pData[playerid][pActivityTime] >= 100)
                {
                    if(vehicleid != INVALID_VEHICLE_ID)
                        ChangeVehicleColor(vehicleid, pData[playerid][pMechColor1], pData[playerid][pMechColor2]);
                    PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                    pData[playerid][pActivityTime] = 0;
                    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
                    ClearAnimations(playerid);
                    Mechanic[playerid] = -1;
                }
            }
            case 5: {
                pData[playerid][pActivityTime]++;
                SetProgressBar(playerid, pData[playerid][pActivityTime]);
                
                if(pData[playerid][pActivityTime] >= 100)
                {
                    if(vehicleid != INVALID_VEHICLE_ID)
                    {
                        ChangeVehiclePaintjob(vehicleid, pData[playerid][pMechColor1]);
                        if ((id = Vehicle_GetID(vehicleid)) != -1 && pvData[id][cVeh] == vehicleid) pvData[id][cPaintJob] = pData[playerid][pMechColor1];
                        else if ((id = VehicleData_GetID(vehicleid)) != -1 && VehicleData[id][Vehicle] == vehicleid) VehicleData[id][PaintJob] = pData[playerid][pMechColor1];
                    }
                    PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
                    pData[playerid][pActivityTime] = 0;
                    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
                    ClearAnimations(playerid);
                    Mechanic[playerid] = -1;
                }
            }
        }
    }
    return 1;
}

ptask MechanicUp[1300](playerid) {
    if(pData[playerid][pJob] == 2 || pData[playerid][pJob2] == 2)
    {
        new id = -1;
        new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);
        switch(Mechanic[playerid]){
            case 6: {
                pData[playerid][pActivityTime]++;
                SetProgressBar(playerid, pData[playerid][pActivityTime]);
                
                if(pData[playerid][pActivityTime] >= 100)
                {
                    if ((id = Vehicle_GetID(vehicleid)) != -1 && pvData[id][cVeh] == vehicleid) pvData[id][cMesinUpgrade] = 1;
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    pData[playerid][pActivityTime] = 0;
                    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
                    ClearAnimations(playerid);
                    Mechanic[playerid] = -1;
                }
            }
            case 7: {
                pData[playerid][pActivityTime]++;
                SetProgressBar(playerid, pData[playerid][pActivityTime]);
                
                if(pData[playerid][pActivityTime] >= 100)
                {
                    if ((id = Vehicle_GetID(vehicleid)) != -1 && pvData[id][cVeh] == vehicleid) pvData[id][pvBodyUpgrade] = 1;
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    pData[playerid][pActivityTime] = 0;
                    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
                    ClearAnimations(playerid);
                    Mechanic[playerid] = -1;
                }
            }
        }
	}
    return 1;
}

ptask MechanicModif[1000](playerid) {
    if(pData[playerid][pJob] == 2 || pData[playerid][pJob2] == 2)
    {
        new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);
        switch(Mechanic[playerid]){
            case 8: {
                pData[playerid][pActivityTime]++;
                SetProgressBar(playerid, pData[playerid][pActivityTime]);
                
                if(pData[playerid][pActivityTime] >= 100)
                {
                    if(GetVehicleModel(vehicleid) == 562 ||
                    GetVehicleModel(vehicleid) == 565 ||
                    GetVehicleModel(vehicleid) == 559 ||
                    GetVehicleModel(vehicleid) == 561 ||
                    GetVehicleModel(vehicleid) == 558 ||
                    GetVehicleModel(vehicleid) == 560)
                    {
                        if(GetVehicleModel(vehicleid) == 562 && pData[playerid][pMechColor1] == 1036) pData[playerid][pMechColor2] = 1040;
                        else if(GetVehicleModel(vehicleid) == 565 && pData[playerid][pMechColor1] == 1047) pData[playerid][pMechColor2] = 1051;
                        else if(GetVehicleModel(vehicleid) == 559 && pData[playerid][pMechColor1] == 1069) pData[playerid][pMechColor2] = 1071;
                        else if(GetVehicleModel(vehicleid) == 561 && pData[playerid][pMechColor1] == 1056) pData[playerid][pMechColor2] = 1062;
                        else if(GetVehicleModel(vehicleid) == 558 && pData[playerid][pMechColor1] == 1090) pData[playerid][pMechColor2] = 1094;
                        else if(GetVehicleModel(vehicleid) == 560 && pData[playerid][pMechColor1] == 1026) pData[playerid][pMechColor2] = 1027;
                    }
                    else if(GetVehicleModel(vehicleid) == 562 ||
                    GetVehicleModel(vehicleid) == 565 ||
                    GetVehicleModel(vehicleid) == 559 ||
                    GetVehicleModel(vehicleid) == 561 ||
                    GetVehicleModel(vehicleid) == 558 ||
                    GetVehicleModel(vehicleid) == 560)
                    {
                        if(GetVehicleModel(vehicleid) == 562 && pData[playerid][pMechColor1] == 1039) pData[playerid][pMechColor2] = 1041;
                        else if(GetVehicleModel(vehicleid) == 565 && pData[playerid][pMechColor1] == 1048) pData[playerid][pMechColor2] = 1052;
                        else if(GetVehicleModel(vehicleid) == 559 && pData[playerid][pMechColor1] == 1070) pData[playerid][pMechColor2] = 1072;
                        else if(GetVehicleModel(vehicleid) == 561 && pData[playerid][pMechColor1] == 1057) pData[playerid][pMechColor2] = 1063;
                        else if(GetVehicleModel(vehicleid) == 558 && pData[playerid][pMechColor1] == 1093) pData[playerid][pMechColor2] = 1095;
                        else if(GetVehicleModel(vehicleid) == 560 && pData[playerid][pMechColor1] == 1031) pData[playerid][pMechColor2] = 1030;
                    }
                    else if(GetVehicleModel(vehicleid) == 575 ||
                    GetVehicleModel(vehicleid) == 536 ||
                    GetVehicleModel(vehicleid) == 576 ||
                    GetVehicleModel(vehicleid) == 567)
                    {
                        if(GetVehicleModel(vehicleid) == 575 && pData[playerid][pMechColor1] == 1042) pData[playerid][pMechColor2] = 1099;
                        else if(GetVehicleModel(vehicleid) == 536 && pData[playerid][pMechColor1] == 1108) pData[playerid][pMechColor2] = 1107;
                        else if(GetVehicleModel(vehicleid) == 576 && pData[playerid][pMechColor1] == 1134) pData[playerid][pMechColor2] = 1137;
                        else if(GetVehicleModel(vehicleid) == 567 && pData[playerid][pMechColor1] == 1102) pData[playerid][pMechColor2] = 1133;
                    }
                    else if(GetVehicleModel(vehicleid) == 534 && pData[playerid][pMechColor1] == 1102) pData[playerid][pMechColor2] = 1101;
                    else if(GetVehicleModel(vehicleid) == 534 && pData[playerid][pMechColor1] == 1106) pData[playerid][pMechColor2] = 1124;
                    else if(GetVehicleModel(vehicleid) == 535 && pData[playerid][pMechColor1] == 1118) pData[playerid][pMechColor2] = 1120;
                    else if(GetVehicleModel(vehicleid) == 535 && pData[playerid][pMechColor1] == 1119) pData[playerid][pMechColor2] = 1121;
                    else if(
                    GetVehicleModel(vehicleid) == 401 ||
                    GetVehicleModel(vehicleid) == 518 ||
                    GetVehicleModel(vehicleid) == 527 ||
                    GetVehicleModel(vehicleid) == 415 ||
                    GetVehicleModel(vehicleid) == 589 ||
                    GetVehicleModel(vehicleid) == 546 ||
                    GetVehicleModel(vehicleid) == 517 ||
                    GetVehicleModel(vehicleid) == 603 ||
                    GetVehicleModel(vehicleid) == 436 ||
                    GetVehicleModel(vehicleid) == 439 ||
                    GetVehicleModel(vehicleid) == 580 ||
                    GetVehicleModel(vehicleid) == 549 ||
                    GetVehicleModel(vehicleid) == 477 && pData[playerid][pMechColor1] == 1007) pData[playerid][pMechColor2] = 1017;	
                    InstallComponentStatic(vehicleid, pData[playerid][pMechColor1]);
                    if(pData[playerid][pMechColor2] != 0) InstallComponentStatic(vehicleid, pData[playerid][pMechColor2]);
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    pData[playerid][pActivityTime] = 0;
                    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
                    pData[playerid][pComponent] -= 50;
                    pData[playerid][pScoreMecha] += 50;
                    ClearAnimations(playerid);
                    Mechanic[playerid] = -1;
                }
            }
        }
	}
    return 1;
}