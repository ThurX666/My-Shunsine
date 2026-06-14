
Dialog:Aksesoris(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        pData[playerid][pAksesoris] = ListedAcc[playerid][listitem];
        Dialog_Show(playerid, AksesorisEdit, DIALOG_STYLE_LIST, "Player Accesories", "Place %s\nChange Bone\nChange Placement\nPrimary Color\nSecondary Color\nDelete\nShare Placement\nChange Placement (Android)", "Select", "Exit", IsPlayerAttachedObjectSlotUsed(playerid, pData[playerid][pAksesoris]) ? ("Off") : ("On"));
    }
    return 1;
}

Dialog:AksesorisEdit(playerid, response, listitem, inputtext[])
{
    new id = pData[playerid][pAksesoris], str[256];
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(IsPlayerAttachedObjectSlotUsed(playerid, id))
                {
                    RemovePlayerAttachedObject(playerid, id);
                    AccData[playerid][id][accShow] = 0;
                    MySQL_SavePlayerToys(playerid, id);
                }
                else 
                {
                    AccData[playerid][id][accShow] = 1;
                    MySQL_SavePlayerToys(playerid, id);
                    Aksesoris_Attach(playerid, id);
                }
            }
            case 1:
            {
                new string[256+1];
                for(new i; i < sizeof(accBones); i++)
                {
                        format(string,sizeof(string),"%s%s\n",string,accBones[i]);
                }
                Dialog_Show(playerid, AksesorisBone, DIALOG_STYLE_LIST, "Edit Bone",string,"Select","Close");
            }
            case 2:
            {                    
                if(IsPlayerAttachedObjectSlotUsed(playerid, id))
                {
                    Servers(playerid, "Use "YELLOW_E"~k~~PED_SPRINT~"WHITE_E" to look around.");
                    EditAttachedObject(playerid, id);
                }
                else return SendCustomMessage(playerid, "DYOC","This accessory is not attached.");
            }
            case 3:
            {                    
                if(!IsPlayerAttachedObjectSlotUsed(playerid, id))
                    return SendCustomMessage(playerid, "DYOC","This accessory is not attached.");

                Dialog_Show(playerid, WarnaAksesoris, DIALOG_STYLE_INPUT, "Set Primary Color",color_string, "Set","Close");
                SetPVarInt(playerid, "Color", 1);
            }
            case 4:
            {
                if(!IsPlayerAttachedObjectSlotUsed(playerid, id))
                    return SendCustomMessage(playerid, "DYOC","This accessory is not attached.");
                        
                Dialog_Show(playerid, WarnaAksesoris, DIALOG_STYLE_INPUT, "Set Secondary Color",color_string, "Set","Close");
                SetPVarInt(playerid, "Color", 2);
            }
            case 5:
            {
                new string[128];
                AccData[playerid][id][accExists] = 0;
                AccData[playerid][id][accModel] = 0;
                
                if(IsPlayerAttachedObjectSlotUsed(playerid, id))
                {
                    RemovePlayerAttachedObject(playerid, id);
                    AccData[playerid][id][accShow] = 0;
                    MySQL_SavePlayerToys(playerid, id);
                }
                format(string,sizeof(string),"DELETE FROM `aksesoris` WHERE `ID`='%d'", AccData[playerid][id][accID]);
                mysql_tquery(g_SQL, string);
                
                SendCustomMessage(playerid, "DYOC","You have removed accessory index #%d.", id);
            }
            case 6: {
                format(str,sizeof(str),"Pos X: %.3f\n",AccData[playerid][id][accOffset][0]);
                format(str,sizeof(str),"%sPos Y: %.3f\n",str,AccData[playerid][id][accOffset][1]);
                format(str,sizeof(str),"%sPos Z: %.3f\n",str,AccData[playerid][id][accOffset][2]);
                format(str,sizeof(str),"%sPos RotX: %.3f\n",str,AccData[playerid][id][accRot][0]);
                format(str,sizeof(str),"%sPos RotY: %.3f\n",str,AccData[playerid][id][accRot][1]);
                format(str,sizeof(str),"%sPos RotZ: %.3f\n",str,AccData[playerid][id][accRot][2]);
                format(str,sizeof(str),"%sPos ScaleX: %.3f\n",str,AccData[playerid][id][accScale][0]);
                format(str,sizeof(str),"%sPos ScaleY: %.3f\n",str,AccData[playerid][id][accScale][1]);
                format(str,sizeof(str),"%sPos ScaleZ: %.3f",str,AccData[playerid][id][accScale][2]);
                Dialog_Show(playerid, DisplayOnly, DIALOG_STYLE_LIST, "Share Accessories Position", str, "Close", "");
            }
            case 7: {
                if(!IsPlayerAttachedObjectSlotUsed(playerid, id))
                    return SendCustomMessage(playerid, "DYOC","This accessory is not attached.");

                format(str,sizeof(str),"Position\tValue\n");
                format(str,sizeof(str),"%sX\t%.3f\n",str,AccData[playerid][id][accOffset][0]);
                format(str,sizeof(str),"%sY\t%.3f\n",str,AccData[playerid][id][accOffset][1]);
                format(str,sizeof(str),"%sZ\t%.3f\n",str,AccData[playerid][id][accOffset][2]);
                format(str,sizeof(str),"%sRotX\t%.3f\n",str,AccData[playerid][id][accRot][0]);
                format(str,sizeof(str),"%sRotY\t%.3f\n",str,AccData[playerid][id][accRot][1]);
                format(str,sizeof(str),"%sRotZ\t%.3f\n",str,AccData[playerid][id][accRot][2]);
                format(str,sizeof(str),"%sScaleX\t%.3f\n",str,AccData[playerid][id][accScale][0]);
                format(str,sizeof(str),"%sScaleY\t%.3f\n",str,AccData[playerid][id][accScale][1]);
                format(str,sizeof(str),"%sScaleZ\t%.3f",str,AccData[playerid][id][accScale][2]);
                Dialog_Show(playerid, EditAksesorisAndroid, DIALOG_STYLE_TABLIST_HEADERS, "Edit Placement (Android)", str, "Change", "Close");
            }
        }
    }
    return 1;
}

Dialog:WarnaAksesoris(playerid, response, listitem, inputtext[])
{
    new id = pData[playerid][pAksesoris];
    if(response)
    {
        new color = strval(inputtext);
        
        if(!(0 <= color <= sizeof(ColorList)-1)) 
            return Error(playerid, "Invalid color ID.");
        
        switch(GetPVarInt(playerid, "Color"))
        {
            case 1: GetRGB(ColorList[color], AccData[playerid][id][accColor1][0], AccData[playerid][id][accColor1][1], AccData[playerid][id][accColor1][2]);
            case 2: GetRGB(ColorList[color], AccData[playerid][id][accColor2][0], AccData[playerid][id][accColor2][1], AccData[playerid][id][accColor2][2]);
        }
        Aksesoris_Attach(playerid, id);
    }
    return 1;
}

Dialog:AksesorisBone(playerid, response, listitem, inputtext[])
{
    new id = pData[playerid][pAksesoris];
    if(response)
    {
        if (listitem != -1) {
            AccData[playerid][id][accBone] = listitem+1;
            if(IsPlayerAttachedObjectSlotUsed(playerid, id))
            {
                RemovePlayerAttachedObject(playerid, id);
                AccData[playerid][id][accScale][0] = AccData[playerid][id][accScale][1] = AccData[playerid][id][accScale][2] = 1.0;
                AccData[playerid][id][accOffset][0] = AccData[playerid][id][accOffset][1] = AccData[playerid][id][accOffset][2] = 0.0;
                AccData[playerid][id][accRot][0] = AccData[playerid][id][accRot][1] = AccData[playerid][id][accRot][2] = 0.0;
            
                Aksesoris_Attach(playerid, id);
                EditAttachedObject(playerid, id);
            }
            SendCustomMessage(playerid, "DYOC","You have been changed accessory bone index #%d to %s", id, accBones[listitem]);
        }
    }
    return 1;
}

Dialog:EditAksesorisAndroid(playerid, response, listitem, inputtext[]) {
    new id = pData[playerid][pAksesoris];
    if (response) {
        switch (listitem) {
            case 0: {
                new str[128];
                SetPVarInt(playerid, "aksesorisEdit", 1);
                format(str,sizeof(str),"Current X Position: %.3f\nInput new X Position below:", AccData[playerid][id][accOffset][0]);
                Dialog_Show(playerid, EditAksesorisPos, DIALOG_STYLE_INPUT, "Edit X Position", str, "Change", "Close");
            }
            case 1: {
                new str[128];
                SetPVarInt(playerid, "aksesorisEdit", 2);
                format(str,sizeof(str),"Current Y Position: %.3f\nInput new Y Position below:", AccData[playerid][id][accOffset][1]);
                Dialog_Show(playerid, EditAksesorisPos, DIALOG_STYLE_INPUT, "Edit Y Position", str, "Change", "Close");
            }
            case 2: {
                new str[128];
                SetPVarInt(playerid, "aksesorisEdit", 3);
                format(str,sizeof(str),"Current Z Position: %.3f\nInput new Z Position below:", AccData[playerid][id][accOffset][2]);
                Dialog_Show(playerid, EditAksesorisPos, DIALOG_STYLE_INPUT, "Edit Z Position", str, "Change", "Close");
            }
            case 3: {
                new str[128];
                SetPVarInt(playerid, "aksesorisEdit", 4);
                format(str,sizeof(str),"Current RotX Position: %.3f\nInput new RotX Position below:", AccData[playerid][id][accRot][0]);
                Dialog_Show(playerid, EditAksesorisPos, DIALOG_STYLE_INPUT, "Edit RotX Position", str, "Change", "Close");
            }
            case 4: {
                new str[128];
                SetPVarInt(playerid, "aksesorisEdit", 5);
                format(str,sizeof(str),"Current RotY Position: %.3f\nInput new RotY Position below:", AccData[playerid][id][accRot][1]);
                Dialog_Show(playerid, EditAksesorisPos, DIALOG_STYLE_INPUT, "Edit RotY Position", str, "Change", "Close");
            }
            case 5: {
                new str[128];
                SetPVarInt(playerid, "aksesorisEdit", 6);
                format(str,sizeof(str),"Current RotZ Position: %.3f\nInput new RotZ Position below:", AccData[playerid][id][accRot][2]);
                Dialog_Show(playerid, EditAksesorisPos, DIALOG_STYLE_INPUT, "Edit RotZ Position", str, "Change", "Close");
            }
            case 6: {
                new str[128];
                SetPVarInt(playerid, "aksesorisEdit", 7);
                format(str,sizeof(str),"Current ScaleX Position: %.3f\nInput new ScaleX Position below:", AccData[playerid][id][accScale][0]);
                Dialog_Show(playerid, EditAksesorisPos, DIALOG_STYLE_INPUT, "Edit ScaleX Position", str, "Change", "Close");
            }
            case 7: {
                new str[128];
                SetPVarInt(playerid, "aksesorisEdit", 8);
                format(str,sizeof(str),"Current ScaleY Position: %.3f\nInput new ScaleY Position below:", AccData[playerid][id][accScale][1]);
                Dialog_Show(playerid, EditAksesorisPos, DIALOG_STYLE_INPUT, "Edit ScaleY Position", str, "Change", "Close");
            }
            case 8: {
                new str[128];
                SetPVarInt(playerid, "aksesorisEdit", 9);
                format(str,sizeof(str),"Current ScaleZ Position: %.3f\nInput new ScaleZ Position below:", AccData[playerid][id][accScale][2]);
                Dialog_Show(playerid, EditAksesorisPos, DIALOG_STYLE_INPUT, "Edit ScaleZ Position", str, "Change", "Close");
            }
        }
    } else {
        pData[playerid][pAksesoris] = -1;
    }
    return 1;
}

Dialog:EditAksesorisPos(playerid, response, listitem, inputtext[]) {
    new id = pData[playerid][pAksesoris];
    if (response) {
        switch (GetPVarInt(playerid, "aksesorisEdit")) {
            // X Position
            case 1: {
                new Float:X = floatstr(inputtext);

                AccData[playerid][id][accOffset][0] = X;
                Aksesoris_Attach(playerid, id);
                pData[playerid][pAksesoris] = -1;  
                SetPVarInt(playerid, "aksesorisEdit", 0);
                SendCustomMessage(playerid, "DYOC","Accessory saved!.");
            }
            // Y Position
            case 2: {
                new Float:Y = floatstr(inputtext);

                AccData[playerid][id][accOffset][1] = Y;
                Aksesoris_Attach(playerid, id);
                pData[playerid][pAksesoris] = -1;  
                SetPVarInt(playerid, "aksesorisEdit", 0);
                SendCustomMessage(playerid, "DYOC","Accessory saved!.");
            }
            // Z Position
            case 3: {
                new Float:Z = floatstr(inputtext);

                AccData[playerid][id][accOffset][2] = Z;
                Aksesoris_Attach(playerid, id);
                pData[playerid][pAksesoris] = -1;  
                SetPVarInt(playerid, "aksesorisEdit", 0);
                SendCustomMessage(playerid, "DYOC","Accessory saved!.");
            }
            // RotX Position
            case 4: {
                new Float:RotX = floatstr(inputtext);

                AccData[playerid][id][accRot][0] = RotX;
                Aksesoris_Attach(playerid, id);
                pData[playerid][pAksesoris] = -1;  
                SetPVarInt(playerid, "aksesorisEdit", 0);
                SendCustomMessage(playerid, "DYOC","Accessory saved!.");
            }
            // RotY Position
            case 5: {
                new Float:RotY = floatstr(inputtext);

                AccData[playerid][id][accRot][1] = RotY;
                Aksesoris_Attach(playerid, id);
                pData[playerid][pAksesoris] = -1;  
                SetPVarInt(playerid, "aksesorisEdit", 0);
                SendCustomMessage(playerid, "DYOC","Accessory saved!.");
            }
            // RotZ Position
            case 6: {
                new Float:RotZ = floatstr(inputtext);

                AccData[playerid][id][accRot][2] = RotZ;
                Aksesoris_Attach(playerid, id);
                pData[playerid][pAksesoris] = -1;  
                SetPVarInt(playerid, "aksesorisEdit", 0);
                SendCustomMessage(playerid, "DYOC","Accessory saved!.");
            }
            // ScaleX Position
            case 7: {
                new Float:ScaleX = floatstr(inputtext);

                AccData[playerid][id][accScale][0] = ScaleX;
                Aksesoris_Attach(playerid, id);
                pData[playerid][pAksesoris] = -1;  
                SetPVarInt(playerid, "aksesorisEdit", 0);
                SendCustomMessage(playerid, "DYOC","Accessory saved!.");
            }
            // Scale Y Position
            case 8: {
                new Float:ScaleY = floatstr(inputtext);

                AccData[playerid][id][accScale][1] = ScaleY;
                Aksesoris_Attach(playerid, id);
                pData[playerid][pAksesoris] = -1;  
                SetPVarInt(playerid, "aksesorisEdit", 0);
                SendCustomMessage(playerid, "DYOC","Accessory saved!.");
            }
            // Scale Z Position
            case 9: {
                new Float:ScaleZ = floatstr(inputtext);

                AccData[playerid][id][accScale][2] = ScaleZ;
                Aksesoris_Attach(playerid, id);
                pData[playerid][pAksesoris] = -1;  
                SetPVarInt(playerid, "aksesorisEdit", 0);
                SendCustomMessage(playerid, "DYOC","Accessory saved!.");
            }
        }
    } else {
        pData[playerid][pAksesoris] = -1;
    }
    return 1;
}
 