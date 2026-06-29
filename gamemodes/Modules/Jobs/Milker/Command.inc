CMD:startmilker(playerid, params[])
{
    if(pData[playerid][pFaction] > 0)
        return Error(playerid, "Kamu anggota faction, tidak bekerja jobs/sidejob.");

    if(MilkerActive[playerid])
        return Error(playerid, "Anda sudah memulai Milker sidejob!");

    if(DelayPlayer[playerid][DelayMilker] > 0)
        return Error(playerid, "Kamu masih cooldown, tunggu %d detik lagi.", DelayPlayer[playerid][DelayMilker]);

    if(!IsPlayerInRangeOfPoint(playerid, 3.0, g_MilkerLocker[0], g_MilkerLocker[1], g_MilkerLocker[2]))
        return Error(playerid, "Anda harus berada di locker Milker!");

    if(pData[playerid][pEnergy] < 20)
        return Error(playerid, "Anda terlalu lelah untuk memerah susu!");

    pData[playerid][pSideJob] = SIDEJOB_MILKER;
    MilkerActive[playerid] = 1;
    MilkerCycles[playerid] = 0;
    MilkerMilkCount[playerid] = 0;
    MilkerCowIndex[playerid] = -1;
    MilkerObjects[playerid] = -1;

    new pointStr[256];
    format(pointStr, sizeof(pointStr),
        ""YELLOW_E"Sidejob Milker dimulai!\n\n"WHITE_E\
        "Pergi ke sapi untuk memerah susu.\n"\
        "Tekan "GREEN_E"'N' "WHITE_E"atau ketik "YELLOW_E"'/perahsusu' "WHITE_E"di dekat sapi.\n\n"\
        "Sapi: "GREEN_E"6 posisi\n"\
        "Target: "GREEN_E"10 siklus\n"\
        "Gaji: "GREEN_E"$250.00\n\n"\
        ""YELLOW_E"Tips: "WHITE_E"Antar susu ke drop-off point setelah memerah."
    );
    Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "MILKER - Sidejob Pemerah Susu", pointStr, "Mulai", "");

    SendCustomMessage(playerid, "MILKER", "Sidejob Milker dimulai! Pergi ke sapi untuk memerah susu.");
    SendCustomMessage(playerid, "MILKER", "Gunakan "YELLOW_E"'N' "WHITE_E"atau "YELLOW_E"'/perahsusu' "WHITE_E"setelah berada di dekat sapi.");

    MilkerNextCow(playerid);
    return 1;
}

CMD:perahsusu(playerid, params[])
{
    if(!MilkerActive[playerid])
        return Error(playerid, "Anda tidak sedang melakukan Milker sidejob!");

    if(MilkerCowIndex[playerid] == -1)
        return Error(playerid, "Tidak ada sapi di sekitar anda!");

    if(!IsPlayerInRangeOfPoint(playerid, 3.0, g_MilkerCowPos[MilkerCowIndex[playerid]][0], g_MilkerCowPos[MilkerCowIndex[playerid]][1], g_MilkerCowPos[MilkerCowIndex[playerid]][2]))
        return Error(playerid, "Anda harus berada di dekat sapi!");

    StartMilking(playerid);
    return 1;
}

CMD:stopmilker(playerid, params[])
{
    if(!MilkerActive[playerid])
        return Error(playerid, "Anda tidak sedang melakukan Milker sidejob!");

    StopMilkerJob(playerid);
    SendCustomMessage(playerid, "MILKER", "Sidejob Milker dihentikan.");
    return 1;
}
