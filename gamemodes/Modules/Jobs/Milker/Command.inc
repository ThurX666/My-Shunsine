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

    new pointStr[512];
    format(pointStr, sizeof(pointStr),
        "{FFFF00}Sidejob Milker dimulai!{FFFFFF}\n\n"\
        "Pergi ke sapi untuk memerah susu.\n"\
        "Tekan {00FF00}'N' {FFFFFF}atau ketik {FFFF00}'/perahsusu' {FFFFFF}di dekat sapi.\n\n"\
        "{FFFFFF}Sapi: {00FFFF}6 posisi\n"\
        "{FFFFFF}Target: {FFFF00}10 siklus\n"\
        "{FFFFFF}Gaji: {00FF00}$250.00\n\n"\
        "{FFFF00}Tips: {FFFFFF}Antar susu ke drop-off point setelah memerah."
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
