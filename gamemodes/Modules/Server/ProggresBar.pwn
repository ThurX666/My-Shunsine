#include <YSI\y_hooks>
new PlayerText:ProggresBar[MAX_PLAYERS][3];
new PlayerLoadingBar[MAX_PLAYERS][3];

hook OnPlayerConnect(playerid) {
    ProggresBar[playerid][0] = CreatePlayerTextDraw(playerid, 269.000000, 221.000000, "_");
    PlayerTextDrawFont(playerid, ProggresBar[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, ProggresBar[playerid][0], 0.600000, 1.950000);
    PlayerTextDrawTextSize(playerid, ProggresBar[playerid][0], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, ProggresBar[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, ProggresBar[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, ProggresBar[playerid][0], 1);
    PlayerTextDrawColor(playerid, ProggresBar[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, ProggresBar[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, ProggresBar[playerid][0], 68);
    PlayerTextDrawUseBox(playerid, ProggresBar[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, ProggresBar[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, ProggresBar[playerid][0], 0);

    ProggresBar[playerid][1] = CreatePlayerTextDraw(playerid, 269.000000, 221.000000, "ld_dual:white");
    PlayerTextDrawFont(playerid, ProggresBar[playerid][1], 4);
    PlayerTextDrawLetterSize(playerid, ProggresBar[playerid][1], 0.600000, 1.250000);
    PlayerTextDrawTextSize(playerid, ProggresBar[playerid][1], 131.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, ProggresBar[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, ProggresBar[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, ProggresBar[playerid][1], 1);
    PlayerTextDrawColor(playerid, ProggresBar[playerid][1], -1094795626);
    PlayerTextDrawBackgroundColor(playerid, ProggresBar[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, ProggresBar[playerid][1], -1094795521);
    PlayerTextDrawUseBox(playerid, ProggresBar[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, ProggresBar[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, ProggresBar[playerid][1], 0);

    ProggresBar[playerid][2] = CreatePlayerTextDraw(playerid, 333.000000, 202.000000, "Installing Upgrade");
    PlayerTextDrawFont(playerid, ProggresBar[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, ProggresBar[playerid][2], 0.387499, 1.649999);
    PlayerTextDrawTextSize(playerid, ProggresBar[playerid][2], 400.000000, 193.000000);
    PlayerTextDrawSetOutline(playerid, ProggresBar[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, ProggresBar[playerid][2], 1);
    PlayerTextDrawAlignment(playerid, ProggresBar[playerid][2], 2);
    PlayerTextDrawColor(playerid, ProggresBar[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, ProggresBar[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, ProggresBar[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, ProggresBar[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, ProggresBar[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, ProggresBar[playerid][2], 0);
    PlayerLoadingBar[playerid][0] = PlayerLoadingBar[playerid][1] = PlayerLoadingBar[playerid][2] = 0;
    return 1;
}

SetProgressBar(playerid, value) {
    PlayerTextDrawTextSize(playerid, ProggresBar[playerid][1], value*131.0/100, 17.0);
    PlayerTextDrawShow(playerid, ProggresBar[playerid][1]);
    return 1;
}

HideProgressBar(playerid) {
    for (new i; i < 3; i++) PlayerTextDrawHide(playerid, ProggresBar[playerid][i]);
    if(pData[playerid][pActivity] != 0)
    {
        KillTimer(pData[playerid][pActivity]);
        pData[playerid][pActivity] = 0;
    }
    pData[playerid][pActivityTime] = 0;
    return 1;
}
