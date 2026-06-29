// Milker Sidejob Functions

stock MilkerNextCow(playerid)
{
    if(!MilkerActive[playerid]) return 0;

    new rand = random(6);
    MilkerCowIndex[playerid] = rand;

    SetPlayerCheckpoint(playerid, g_MilkerCowPos[rand][0], g_MilkerCowPos[rand][1], g_MilkerCowPos[rand][2], 3.0);
    SendCustomMessage(playerid, "MILKER", "Ikuti checkpoint ke sapi berikutnya! ("GREEN_E"%d/10"WHITE_E")", MilkerCycles[playerid] + 1);
    return 1;
}

stock StartMilking(playerid)
{
    if(!MilkerActive[playerid]) return 0;
    if(MilkerMilkCount[playerid] > 0) return Error(playerid, "Antar susu ke drop-off point dulu!");

    stop pData[playerid][pActivity];
    RemovePlayerAttachedObject(playerid, 9);

    ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.0, 1, 0, 0, 0, 0, 1);
    TogglePlayerControllable(playerid, 0);

    pData[playerid][pActivity] = SetTimerEx("FinishMilking", 3000, false, "i", playerid);

    SendCustomMessage(playerid, "MILKER", "Memerah susu...");
    SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.1180, 0.0669, 0.2469, 0.0000, 90.0, 0.0, 1.0, 1.0, 1.0);

    for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
    PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Memerah Susu...");
    return 1;
}

function FinishMilking(playerid)
{
    if(!MilkerActive[playerid]) return 0;

    TogglePlayerControllable(playerid, 1);
    ClearAnimations(playerid);
    StopLoopingAnim(playerid);

    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);

    RemovePlayerAttachedObject(playerid, 9);
    SetPlayerAttachedObject(playerid, 9, 1550, 5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);

    MilkerMilkCount[playerid]++;

    SendCustomMessage(playerid, "MILKER", "Susu berhasil diperah! Bawa ke tempat penyimpanan susu.");
    DisablePlayerCheckpoint(playerid);
    MilkerCowIndex[playerid] = -1;

    SetPlayerCheckpoint(playerid, g_MilkerDropOff[0], g_MilkerDropOff[1], g_MilkerDropOff[2], 3.0);
    return 1;
}

stock DeliverMilk(playerid)
{
    if(!MilkerActive[playerid]) return 0;

    if(!IsPlayerInRangeOfPoint(playerid, 4.0, g_MilkerDropOff[0], g_MilkerDropOff[1], g_MilkerDropOff[2]))
        return 0;

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

    stop pData[playerid][pActivity];
    TogglePlayerControllable(playerid, 1);
    ClearAnimations(playerid);
    StopLoopingAnim(playerid);
    DisablePlayerCheckpoint(playerid);
    RemovePlayerAttachedObject(playerid, 9);

    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);

    MilkerActive[playerid] = 0;
    MilkerCycles[playerid] = 0;
    MilkerMilkCount[playerid] = 0;
    MilkerCowIndex[playerid] = -1;
    MilkerObjects[playerid] = -1;

    if(IsPlayerAttachedObjectSlotUsed(playerid, 9))
        RemovePlayerAttachedObject(playerid, 9);

    pData[playerid][pSideJob] = 0;
    return 1;
}
