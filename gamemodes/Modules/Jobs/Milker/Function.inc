// Milker Sidejob Functions

stock MilkerNextCow(playerid)
{
    if(!MilkerActive[playerid]) return 0;

    // Pick a random cow position
    new rand = random(6);
    MilkerCowIndex[playerid] = rand;

    // Set checkpoint at cow position
    SetPlayerCheckpoint(playerid, g_MilkerCowPos[rand][0], g_MilkerCowPos[rand][1], g_MilkerCowPos[rand][2], 3.0);
    SendCustomMessage(playerid, "MILKER", "Ikuti checkpoint ke sapi berikutnya! ("GREEN_E"%d/10"WHITE_E")", MilkerCycles[playerid] + 1);
    return 1;
}

stock StartMilking(playerid)
{
    if(!MilkerActive[playerid]) return 0;

    // Stop any existing timer
    stop pData[playerid][pActivity];
    RemovePlayerAttachedObject(playerid, 9);

    // Play squat animation
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.0, 1, 0, 0, 0, 0, 1);
    TogglePlayerControllable(playerid, 0);

    // Start activity timer (3 seconds to milk)
    pData[playerid][pActivity] = SetTimerEx("FinishMilking", 3000, false, "i", playerid);

    SendCustomMessage(playerid, "MILKER", "Memerah susu...");
    SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.1180, 0.0669, 0.2469, 0.0000, 90.0, 0.0, 1.0, 1.0, 1.0); // Milk bucket attached

    // Show progress bar
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

    // Hide progress bar
    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);

    RemovePlayerAttachedObject(playerid, 9);
    SetPlayerAttachedObject(playerid, 9, 1550, 5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0); // Carry box (milk carton model)

    MilkerMilkCount[playerid]++;

    SendCustomMessage(playerid, "MILKER", "Susu berhasil diperah! Bawa ke tempat penyimpanan susu.");
    DisablePlayerCheckpoint(playerid);
    MilkerCowIndex[playerid] = -1;

    // Set checkpoint to drop-off point
    SetPlayerCheckpoint(playerid, g_MilkerDropOff[0], g_MilkerDropOff[1], g_MilkerDropOff[2], 3.0);
    return 1;
}

stock DeliverMilk(playerid)
{
    if(!MilkerActive[playerid]) return 0;

    if(!IsPlayerInRangeOfPoint(playerid, 4.0, g_MilkerDropOff[0], g_MilkerDropOff[1], g_MilkerDropOff[2]))
        return 0;

    // Remove carry box
    RemovePlayerAttachedObject(playerid, 9);
    MilkerMilkCount[playerid] = 0;
    MilkerCycles[playerid]++;

    SendCustomMessage(playerid, "MILKER", "Susu berhasil disimpan! ("GREEN_E"%d/10"WHITE_E")", MilkerCycles[playerid]);

    if(MilkerCycles[playerid] >= MAX_MILKER_CYCLES)
    {
        // Job complete!
        StopMilkerJob(playerid);
        GivePlayerMoneyEx(playerid, MILKER_SALARY);
        SendCustomMessage(playerid, "MILKER", ""GREEN_E"Sidejob Milker selesai! Kamu mendapat $250.00");
        DelayPlayer[playerid][DelayCourier] = 900; // 15 min cooldown (reuse DelayCourier to avoid new global variable)
        return 1;
    }

    // Next cow
    MilkerNextCow(playerid);
    return 1;
}

stock StopMilkerJob(playerid)
{
    if(!MilkerActive[playerid]) return 0;

    // Cleanup
    stop pData[playerid][pActivity];
    TogglePlayerControllable(playerid, 1);
    ClearAnimations(playerid);
    StopLoopingAnim(playerid);
    DisablePlayerCheckpoint(playerid);
    RemovePlayerAttachedObject(playerid, 9);

    // Hide progress bar
    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);

    // Reset variables
    MilkerActive[playerid] = 0;
    MilkerCycles[playerid] = 0;
    MilkerMilkCount[playerid] = 0;
    MilkerCowIndex[playerid] = -1;
    MilkerObjects[playerid] = -1;

    // Remove milk bucket if attached
    if(IsPlayerAttachedObjectSlotUsed(playerid, 9))
        RemovePlayerAttachedObject(playerid, 9);

    pData[playerid][pSideJob] = 0;
    return 1;
}
