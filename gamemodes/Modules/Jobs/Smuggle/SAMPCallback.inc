
#include <YSI\y_hooks>
hook OnPlayerEnterRaceCP(playerid)
{   
  if (pData[playerid][pJob] == 8 || pData[playerid][pJob2] == 8) {
    if (GetPVarInt(playerid, "sedangSmuggler") == 1) {
      GameTextForPlayer(playerid, "~p~SMUGGLER PACKET~n~~w~USE ~R~/GETPACKET~w~ TO PICKUP PACKET", 3000, 4);
    } else if (pData[playerid][pSmugglerPick] && GetPVarInt(playerid, "sedangNganter") == 1) {
      if (!IsPlayerInAnyVehicle(playerid) || !IsVehicleSmugglerVehicle(GetPlayerVehicleID(playerid))) {
        SendCustomMessage(playerid, "SMUGGLER", "You must deliver the packet using a Smuggler vehicle.");
        return 1;
      }
      GivePlayerMoneyEx(playerid, SMUGGLER_SALARY);
      pData[playerid][pSmugglerPick] = 0;
      pData[playerid][pSmugglerFind] = 0;
      packetPlayerid[selectedLocation] = INVALID_PLAYER_ID;
      packetStatus[selectedLocation] = 0;
      DeletePVar(playerid, "sedangSmuggler");
      DeletePVar(playerid, "sedangNganter");
      packetActive = 0;
      DelayPlayer[playerid][DelaySmuggler] = 3600;
      new strings[214];
      if(selectedLocation == 0)
      {
        StockMaterial += 5000;
        format(strings, sizeof(strings), ""RED_E"Job: Arms Dealer\n"YELLOW_E"'/joinjob' "WHITE_E"to be an Arms Dealer\n"YELLOW_E"'/buypacket' "WHITE_E"to buy gun material package\nAvailable packages: "GREEN_E"%d", StockMaterial);
        UpdateDynamic3DTextLabelText(Material, COLOR_ARWIN, strings);
      }
      else if(selectedLocation == 1)
      {
        StockMarijuana += 1000;
        format(strings, sizeof(strings), ""RED_E"Job: Drugs  Dealer\n"YELLOW_E"'/joinjob' "WHITE_E"to be an Drug Dealer\n"YELLOW_E"'/buypacket' "WHITE_E"to buy drugs package\nAvailable packages: "GREEN_E"%d", StockCrack);
        UpdateDynamic3DTextLabelText(Crack, COLOR_ARWIN, strings);
      }
      Server_Save();
      foreach (new i : Player) if (pData[i][pJob] == 8 || pData[i][pJob2] == 8) {
        pData[i][pSmugglerPick] = 0;
        pData[i][pSmugglerFind] = 0;
        DeletePVar(i, "sedangSmuggler");
        DeletePVar(i, "sedangNganter");
      }
      SendCustomMessage(playerid, "SMUGGLER", "You've been stored the packet and you'll received "GREEN_E"$%s", FormatMoney(SMUGGLER_SALARY));
    }
  }
  return 1;
}
