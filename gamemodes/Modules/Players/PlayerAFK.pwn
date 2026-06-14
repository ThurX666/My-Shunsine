#include <YSI\y_hooks>
new PlayerAFK[MAX_PLAYERS], PlayerPause[MAX_PLAYERS];

hook OnPlayerConnect(playerid) {
    PlayerAFK[playerid] = -1;
    PlayerPause[playerid] = -1;
    return 1;
}

public OnPlayerPause(playerid) {
    #if defined DEBUG_MODE
        printf("[Callback: OnPlayerPause]: Player ID: %d", playerid);
    #endif

    PlayerPause[playerid] = 1;
    return 1;
}

public OnPlayerResume(playerid, time) {
    #if defined DEBUG_MODE
        printf("[Callback: OnPlayerResume]: Player ID: %d, Time: %d", playerid, time);
    #endif

    PlayerPause[playerid] = 0;

    if (PlayerAFK[playerid]) {
        TogglePlayerControllable(playerid, 1);
        if(pData[playerid][pOnDuty] >= 1) SetFactionColor(playerid);
        else if(pData[playerid][pAdminDuty] == 1) 
        {
            SetPlayerColor(playerid, COLOR_RED);
            if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_RED, (sprintf("%s {ffffff}(%d)", ReturnName(playerid), playerid)));
        }
        else {
            SetPlayerColor(playerid, COLOR_WHITE);
            if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                            UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s {ffffff}(%d)", ReturnName(playerid), playerid)));
        }
        PlayerAFK[playerid] = 0;
        PlayerPause[playerid] = 0;
        // SendCustomMessage(playerid, "AFK", "You've been paused for "YELLOW_E"%d minute(s) "WHITE_E"and you are now is no longer in AFK Mode.", (time/60000));
    }
    return 1;
}

ptask Player_AFK[1000](playerid) {
    if (PlayerPause[playerid]) {
        if ((GetPlayerPausedTime(playerid)/1000) >= 180 && !PlayerAFK[playerid]) {
            TogglePlayerControllable(playerid, 0);
            PlayerAFK[playerid] = 1;
            SendClientMessage(playerid, COLOR_ARWIN, "SERVER: "YELLOW_E"You are now in AFK, use '"RED_E"/afk"YELLOW_E"' to exit AFK mode and resume playing!");
            SetPlayerColor(playerid, COLOR_GREY);
            if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
                UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_GREY, (sprintf("player is afk\n%s {ffffff}(%d)", ReturnName(playerid), playerid)));
        }
    }
    return 1;
}

// AFK SYSTEM
CMD:afk(playerid, params[]) {
    if (!IsPlayerConnected(playerid))
        return Error(playerid, "You are not logged in!");

    if (!PlayerAFK[playerid])
        return Error(playerid, "You're not in AFK Mode");

    if (PlayerAFK[playerid]) {
        TogglePlayerControllable(playerid, 1);
        if(pData[playerid][pOnDuty] >= 1) SetFactionColor(playerid);
        else SetPlayerColor(playerid, COLOR_WHITE);
        if(IsValidDynamic3DTextLabel(PlayerLabel[playerid]))
        UpdateDynamic3DTextLabelText(PlayerLabel[playerid], COLOR_WHITE, (sprintf("%s {ffffff}(%d)", ReturnName(playerid), playerid)));
        PlayerAFK[playerid] = 0;
        SendCustomMessage(playerid, "AFK", "You are now no longer in AFK Mode.");
    }
    return 1;
}

CMD:listafk(playerid, params[])
{
    new string[500], afkTime[24];
    format(string, sizeof(string), "Name\tType\tTime\n");
    foreach(new i : Player)
    {
        if (PlayerPause[playerid]) {
            FormatTimeleft((GetPlayerPausedTime(i)/1000), afkTime);
            format(string, sizeof(string), "%s%s\tPaused\t%s\n", string, ReturnName(i), afkTime);
        }
    }
    Dialog_Show(playerid, DisplayOnly, DIALOG_STYLE_TABLIST_HEADERS, "Afk List", string, "Close", "");
    return 1;
}
