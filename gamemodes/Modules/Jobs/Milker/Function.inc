// Milker Sidejob Functions

stock MilkerNextCow(playerid)
{
    if(!MilkerActive[playerid]) return 0;

    if(MilkerCP[playerid] != -1) DestroyDynamicCP(MilkerCP[playerid]), MilkerCP[playerid] = -1;

    new rand = random(6);
    MilkerCowIndex[playerid] = rand;

    MilkerCP[playerid] = CreateDynamicCP(
        g_MilkerCowPos[rand][0],
        g_MilkerCowPos[rand][1],
        g_MilkerCowPos[rand][2],
        3.0, 0, 0, -1, 30.0
    );
    SendCustomMessage(playerid, "MILKER", "Ikuti checkpoint ke sapi! Sapi ke-{00FF00}%d{FFFFFF} dari 10.", MilkerCycles[playerid] + 1);
    return 1;
}

stock StartMilking(playerid)
{
    if(!MilkerActive[playerid]) return 0;
    if(MilkerMilkCount[playerid] > 0) return Error(playerid, "Antar susu ke drop-off point dulu!");

    if(pData[playerid][pActivity] != -1) KillTimer(pData[playerid][pActivity]), pData[playerid][pActivity] = -1;
    RemovePlayerAttachedObject(playerid, 9);

    ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.0, 1, 0, 0, 0, 0, 1);

    pData[playerid][pActivityTime] = 0;
    pData[playerid][pActivity] = SetTimerEx("UpdateMilkingProgress", 250, true, "i", playerid);

    SendCustomMessage(playerid, "MILKER", "Memerah susu...");

    if(IsPlayerConnected(playerid))
    {
        for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
        PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Memerah Susu...");
    }
    return 1;
}

function UpdateMilkingProgress(playerid)
{
    if(!IsPlayerConnected(playerid)) return 0;
    if(!MilkerActive[playerid])
    {
        if(pData[playerid][pActivity] != -1) KillTimer(pData[playerid][pActivity]), pData[playerid][pActivity] = -1;
        return 0;
    }

    pData[playerid][pActivityTime]++;

    if(pData[playerid][pActivityTime] >= 100)
    {
        if(pData[playerid][pActivity] != -1) KillTimer(pData[playerid][pActivity]), pData[playerid][pActivity] = -1;
        FinishMilking(playerid);
    }
    else
    {
        SetProgressBar(playerid, pData[playerid][pActivityTime]);
    }
    return 1;
}

function FinishMilking(playerid)
{
    if(!IsPlayerConnected(playerid)) return 0;
    if(!MilkerActive[playerid]) return 0;

    ClearAnimations(playerid);
    StopLoopingAnim(playerid);

    if(IsPlayerConnected(playerid))
    {
        for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
    }

    RemovePlayerAttachedObject(playerid, 9);
    SetPlayerAttachedObject(playerid, 9, 2912, 1, 0.233, 0.359, -0.198, 1.400, 0.000, 0.000, 0.640, 0.625, 0.654);

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);

    MilkerMilkCount[playerid]++;

    SendCustomMessage(playerid, "MILKER", "Susu berhasil diperah! Bawa ke tempat penyimpanan susu.");
    if(MilkerCP[playerid] != -1) DestroyDynamicCP(MilkerCP[playerid]), MilkerCP[playerid] = -1;
    MilkerCowIndex[playerid] = -1;

    pData[playerid][pActivity] = -1;
    MilkerCP[playerid] = CreateDynamicCP(
        g_MilkerDropOff[0],
        g_MilkerDropOff[1],
        g_MilkerDropOff[2],
        3.0, 0, 0, -1, 30.0
    );
    return 1;
}

stock DeliverMilk(playerid)
{
    if(!MilkerActive[playerid]) return 0;
    if(MilkerCP[playerid] == -1) return 0;

    if(!IsPlayerInDynamicCP(playerid, MilkerCP[playerid]))
        return 0;

    ClearAnimations(playerid);
    StopLoopingAnim(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    RemovePlayerAttachedObject(playerid, 9);
    MilkerMilkCount[playerid] = 0;
    MilkerCycles[playerid]++;

    SendCustomMessage(playerid, "MILKER", "Susu berhasil disimpan! ("GREEN_E"%d/10"WHITE_E")", MilkerCycles[playerid]);

    if(MilkerCycles[playerid] >= MAX_MILKER_CYCLES)
    {
        StopMilkerJob(playerid);
        AddPlayerSalary(playerid, "Milker", "Delivered 10 milk", MILKER_SALARY);
        SendCustomMessage(playerid, "MILKER", ""GREEN_E"Sidejob Milker selesai! Gaji $250.00 telah ditambahkan ke paycheck.");
        SendClientMessageEx(playerid, COLOR_ARWIN, "SALARY: {ffffff}Your salary statement has been updated, please check command {ffff00}'/mysalary'");
        DelayPlayer[playerid][DelayMilker] = 900;
        return 1;
    }

    MilkerNextCow(playerid);
    return 1;
}

stock StopMilkerJob(playerid)
{
    if(!MilkerActive[playerid]) return 0;

    if(pData[playerid][pActivity] != -1) KillTimer(pData[playerid][pActivity]), pData[playerid][pActivity] = -1;
    ClearAnimations(playerid);
    StopLoopingAnim(playerid);
    if(MilkerCP[playerid] != -1) DestroyDynamicCP(MilkerCP[playerid]), MilkerCP[playerid] = -1;
    RemovePlayerAttachedObject(playerid, 9);

    if(IsPlayerConnected(playerid))
    {
        for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
    }

    MilkerActive[playerid] = 0;
    MilkerCycles[playerid] = 0;
    MilkerMilkCount[playerid] = 0;
    MilkerCowIndex[playerid] = -1;
    MilkerObjects[playerid] = -1;
    MilkerCP[playerid] = -1;

    if(IsPlayerAttachedObjectSlotUsed(playerid, 9))
        RemovePlayerAttachedObject(playerid, 9);

    pData[playerid][pSideJob] = 0;
    return 1;
}
