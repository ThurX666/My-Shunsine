
/*CMD:setskill(playerid, params[])
{
   if(pData[playerid][pAdmin] < 6)
      return PermissionError(playerid);

   new name[64], string[128], otherid;
   if(sscanf(params, "ds[64]S()[128]",otherid, name, string))
   {
      Usage(playerid, "/setskill [playerid] [name] [score]");
      SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} [mechanic], [fishing], [trucker]");
      return 1;
   }
   if(!strcmp(name, "mechanic", true))
   {
      new stok;
      if(sscanf(string, "d", stok))
            return Usage(playerid, "/setskill [playerid] [mechanic] [stok]");

      if(stok < 0 || stok > 5)
            return Error(playerid, "You must specify at least 0 or 5");

      pData[otherid][pSkillMecha] = stok;
      Info(otherid, "Skill Mechanic Anda Telah di set oleh admin %s", pData[playerid][pAdminname]);
      SendAdminMessage(COLOR_RED, "AdmWarn: %s set skill mechanic player %s.", pData[playerid][pAdminname], ReturnName(otherid));
   }
   else if(!strcmp(name, "fishing", true))
   {
      new stok;
      if(sscanf(string, "d", stok))
            return Usage(playerid, "/setskill [playerid] [fishing] [stok]");

      if(stok < 0 || stok > 2)
            return Error(playerid, "You must specify at least 0 or 2");

      pData[otherid][pSkillFishing] = stok;
      Info(otherid, "Skill Fishing Anda Telah di set oleh admin %s", pData[playerid][pAdminname]);
      SendAdminMessage(COLOR_RED, "AdmWarn: %s set skill Fishing player %s.", pData[playerid][pAdminname], ReturnName(otherid));
   }
   else if(!strcmp(name, "trucker", true))
   {
      new stok;
      if(sscanf(string, "d", stok))
            return Usage(playerid, "/setskill [playerid] [trucker] [stok]");

      if(stok < 0 || stok > 5)
            return Error(playerid, "You must specify at least 0 or 5");

      pData[otherid][pSkillTrucker] = stok;
      Info(otherid, "Skill Trucker Anda Telah di set oleh admin %s", pData[playerid][pAdminname]);
      SendAdminMessage(COLOR_RED, "AdmWarn: %s set skill Trucker player %s.", pData[playerid][pAdminname], ReturnName(otherid));
   }
   return 1;
}*/

CMD:setskill(playerid, params[])
{
   if(pData[playerid][pAdmin] < 6)
      return PermissionError(playerid);

   new name[64], string[128], otherid;
   if(sscanf(params, "ds[64]S()[128]",otherid, name, string))
   {
      Usage(playerid, "/setscoreskill [playerid] [name] [score]");
      SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} [mechanic], [fishing], [trucker]");
      return 1;
   }
   if(!strcmp(name, "mechanic", true))
   {
      new stok;
      if(sscanf(string, "d", stok))
            return Usage(playerid, "/setskill [playerid] [mechanic] [stok]");

      pData[otherid][pScoreMecha] = stok;
      Info(otherid, "Skill Mechanic Anda Telah di set oleh admin %s", pData[playerid][pAdminname]);
      SendAdminMessage(COLOR_RED, "AdmWarn: %s set skill mechanic player %s.", pData[playerid][pAdminname], ReturnName(otherid));
   }
   else if(!strcmp(name, "fishing", true))
   {
      new stok;
      if(sscanf(string, "d", stok))
            return Usage(playerid, "/setskill [playerid] [fishing] [stok]");

      pData[otherid][pScoreFishing] = stok;
      Info(otherid, "Skill Fishing Anda Telah di set oleh admin %s", pData[playerid][pAdminname]);
      SendAdminMessage(COLOR_RED, "AdmWarn: %s set skill Fishing player %s.", pData[playerid][pAdminname], ReturnName(otherid));
   }
   else if(!strcmp(name, "trucker", true))
   {
      new stok;
      if(sscanf(string, "d", stok))
            return Usage(playerid, "/setskill [playerid] [trucker] [stok]");

      pData[otherid][pScoreTrucker] = stok;
      Info(otherid, "Skill Trucker Anda Telah di set oleh admin %s", pData[playerid][pAdminname]);
      SendAdminMessage(COLOR_RED, "AdmWarn: %s set skill Trucker player %s.", pData[playerid][pAdminname], ReturnName(otherid));
   }
   return 1;
}

CMD:skills(playerid)
{
   if(pData[playerid][IsLoggedIn] == false)
      return Error(playerid, "You must logged in!");
   new string[1000];
   format(string, sizeof(string), "Name Skills\tScore\tLevel\n");

   if(pData[playerid][pScoreTrucker] != -1)
   {
      if(pData[playerid][pScoreTrucker] <= 50) 
      {
         format(string, sizeof(string), "%sTrucker\t"YELLOW_E"[%d/50]\t"WHITE_E"1\n", string, pData[playerid][pScoreTrucker]);
      }
      else if(pData[playerid][pScoreTrucker] <= 150)
      {
         format(string, sizeof(string), "%sTrucker\t"YELLOW_E"[%d/150]\t"WHITE_E"2\n", string, pData[playerid][pScoreTrucker]);
      }
      else if(pData[playerid][pScoreTrucker] <= 200)
      {
         format(string, sizeof(string), "%sTrucker\t"YELLOW_E"[%d/200]\t"WHITE_E"3\n", string, pData[playerid][pScoreTrucker]);
      }
      else if(pData[playerid][pScoreTrucker] <= 300)
      {
         format(string, sizeof(string), "%sTrucker\t"YELLOW_E"[%d/300]\t"WHITE_E"4\n", string, pData[playerid][pScoreTrucker]);
      }
      else if(pData[playerid][pScoreTrucker] >= 300)
      {
         format(string, sizeof(string), "%sTrucker\t"YELLOW_E"[%d/350]\t"WHITE_E"5\n", string, pData[playerid][pScoreTrucker]);
      }
   }
   if(pData[playerid][pScoreFishing] != -1)
   {
      if(pData[playerid][pScoreFishing] <= 99)
      {
         format(string, sizeof(string), "%sFish\t"YELLOW_E"[%d/100]\t"WHITE_E"1\n", string, pData[playerid][pScoreFishing]);
      }
      if(pData[playerid][pScoreFishing] >= 99)
      {
         format(string, sizeof(string), "%sFish\t"YELLOW_E"[%d/200]\t"WHITE_E"2\n", string, pData[playerid][pScoreFishing]);
      }
   }
   if(pData[playerid][pScoreMecha] != -1)
   {
      if(pData[playerid][pScoreMecha] <= 500)
      {
         format(string, sizeof(string), "%sMechanic\t"YELLOW_E"[%d/500]\t"WHITE_E"1\n", string, pData[playerid][pScoreMecha]);
      }
      else if(pData[playerid][pScoreMecha] <= 1500)
      {
         format(string, sizeof(string), "%sMechanic\t"YELLOW_E"[%d/1500]\t"WHITE_E"2\n", string, pData[playerid][pScoreMecha]);
      }
      else if(pData[playerid][pScoreMecha] <= 2500)
      {
         format(string, sizeof(string), "%sMechanic\t"YELLOW_E"[%d/2500]\t"WHITE_E"3\n", string, pData[playerid][pScoreMecha]);
      }
      else if(pData[playerid][pScoreMecha] <= 3500)
      {
         format(string, sizeof(string), "%sMechanic\t"YELLOW_E"[%d/3500]\t"WHITE_E"4\n", string, pData[playerid][pScoreMecha]);
      }
      else if(pData[playerid][pScoreMecha] >= 3500)
      {
         format(string, sizeof(string), "%sMechanic\t"YELLOW_E"[%d/3500]\t"WHITE_E"5\n", string, pData[playerid][pScoreMecha]);
      }
   }
   if(pData[playerid][pScoreFarmer] != -1)
   {
      if(pData[playerid][pScoreFarmer] <= 1500)
      {
         format(string, sizeof(string), "%sFarmer\t"YELLOW_E"[%d/1500]\t"WHITE_E"1\n", string, pData[playerid][pScoreFarmer]);
      }
      else if(pData[playerid][pScoreFarmer] <= 3500)
      {
         format(string, sizeof(string), "%sFarmer\t"YELLOW_E"[%d/3500]\t"WHITE_E"2\n", string, pData[playerid][pScoreFarmer]);
      }
      else if(pData[playerid][pScoreFarmer] <= 6500)
      {
         format(string, sizeof(string), "%sFarmer\t"YELLOW_E"[%d/6500]\t"WHITE_E"3\n", string, pData[playerid][pScoreFarmer]);
      }
      else if(pData[playerid][pScoreFarmer] <= 8500)
      {
         format(string, sizeof(string), "%sFarmer\t"YELLOW_E"[%d/8500]\t"WHITE_E"4\n", string, pData[playerid][pScoreFarmer]);
      }
      else if(pData[playerid][pScoreFarmer] >= 8500)
      {
         format(string, sizeof(string), "%sFarmer\t"YELLOW_E"[%d/8500]\t"WHITE_E"5\n", string, pData[playerid][pScoreFarmer]);
      }
   }
   format(string, sizeof(string), "%sFight Style\t"YELLOW_E"%s"WHITE_E"\n", string, GetFightStyleName(playerid));
   format(string, sizeof(string), "%sCountry Rifle\t"YELLOW_E"%d"WHITE_E"\n", string, pData[playerid][pSkillWeapon][0]);
   format(string, sizeof(string), "%sShotgun\t"YELLOW_E"%d"WHITE_E"\n", string, pData[playerid][pSkillWeapon][1]);
   format(string, sizeof(string), "%sDesert Eagle\t"YELLOW_E"%d"WHITE_E"\n", string, pData[playerid][pSkillWeapon][2]);
   format(string, sizeof(string), "%sMP5\t"YELLOW_E"%d"WHITE_E"\n", string, pData[playerid][pSkillWeapon][3]);
   format(string, sizeof(string), "%sAK47\t"YELLOW_E"%d"WHITE_E"\n", string, pData[playerid][pSkillWeapon][4]);
   Dialog_Show(playerid, SkillPlayer, DIALOG_STYLE_TABLIST_HEADERS, "Skills Player", string, "Pilih", "Close");
   return 1;
}

Dialog:SkillPlayer(playerid, response, listitem, inputtext[])
{
   if(response)
   {
      switch (listitem)
      {
         case 0:
         {
            new tstr[500];
            format(tstr, sizeof(tstr), "Kegunaan Skil Player\n- {00FFFF}Level "YELLOW_E"2 {00FFFF}Mendapatkan Bonus "YELLOW_E"5\n- {00FFFF}Level "YELLOW_E"3 {00FFFF}Mendapatkan Bonus "YELLOW_E"10\n- {00FFFF}Level "YELLOW_E"4 {00FFFF}Mendapatkan Bonus "YELLOW_E"15\n- {00FFFF}Level "YELLOW_E"5 {00FFFF}Mendapatkan Bonus "YELLOW_E"20");
            ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Skill Player Trucker:", tstr, "Close", "");
         }
         case 1:
         {
            new tstr[500];
            format(tstr, sizeof(tstr), "Kegunaan Skil Player\n- {00FFFF}Level "YELLOW_E"1 {00FFFF}Hanya bisa mancing di pemancingan\n- {00FFFF}Level "YELLOW_E"2 {00FFFF}Bisa mancing di tengah laut dan di pemancingan");
            ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Skill Player Fishing:", tstr, "Close", "");
         }
         case 2:
         {
            new tstr[500];
            format(tstr, sizeof(tstr), "Kegunaan Skil Player\n- {00FFFF}Level "YELLOW_E"1 {00FFFF}Hanya bisa merepair kendaraan\n- {00FFFF}Level "YELLOW_E"2 {00FFFF}Bisa merespray/ganti warna kendaraan\n- {00FFFF}Level "YELLOW_E"3 {00FFFF}Bisa upgrade kendaraaan\n- {00FFFF}Level "YELLOW_E"4 {00FFFF}Bisa memodif kendaraan (pegawai workshop)");
            ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Skill Player Mechanic:", tstr, "Close", "");
         }
      }
   }
   return 1;
}

CMD:buyfightstyle(playerid, params[])
{
   new String[212], S3MP4K[212];
   if(!IsPlayerInRangeOfPoint(playerid, 3.0, 758.5930,-77.6466,1000.6508)) return Error(playerid, "Kamu tidak berada di tempat GYM / TRAINING");
   strcat(S3MP4K, "Name Fight\tCoast\n");
   format(String, sizeof(String),"Normal\t$125.00\n");
   strcat(S3MP4K, String);
   format(String, sizeof(String),"Boxing\t$125.00\n");
   strcat(S3MP4K, String);
   format(String, sizeof(String),"Kung-fu\t$125.00\n");
   strcat(S3MP4K, String);
   format(String, sizeof(String),"Kneehead\t$125.00\n");
   strcat(S3MP4K, String);
   format(String, sizeof(String),"GrabKick\t$125.00\n");
   strcat(S3MP4K, String);
   format(String, sizeof(String),"Elbow\t$125.00");
   strcat(S3MP4K, String);
   ShowPlayerDialog(playerid, DIALOG_FIGHTSTYLE, DIALOG_STYLE_TABLIST_HEADERS, "Fight Style", S3MP4K, "Select", "Cancel");
   return 1;
}
