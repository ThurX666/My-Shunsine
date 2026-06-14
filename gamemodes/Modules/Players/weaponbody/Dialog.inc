
Dialog:WepPosition(playerid, response, listitem, inputtext[]) {
    if (response) {
        new weaponid = EditingWeapon[playerid];
        switch (listitem) {
            case 0: {
                new index = (weaponid >= 22 && weaponid <= 38) ? (weaponid - 22) : (weaponid + 15);
				SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), WeaponSettings[playerid][index][Bone], WeaponSettings[playerid][index][Position][0], WeaponSettings[playerid][index][Position][1], WeaponSettings[playerid][index][Position][2], WeaponSettings[playerid][index][Position][3], WeaponSettings[playerid][index][Position][4], WeaponSettings[playerid][index][Position][5], 1.0, 1.0, 1.0);
                EditAttachedObject(playerid, GetWeaponObjectSlot(weaponid));
                SetPlayerArmedWeapon(playerid, 0);
            }
            case 1: {
                new info[256], index = (weaponid >= 22 && weaponid <= 38) ? (weaponid - 22) : (weaponid + 15);

                format(info, sizeof(info), "Please input the weapon settings position below:\nCurrent value x y z rx ry rz:\n"YELLOW_E"%.3f %.3f %.3f %.3f %.3f %.3f", WeaponSettings[playerid][index][Position][0], WeaponSettings[playerid][index][Position][1], WeaponSettings[playerid][index][Position][2], WeaponSettings[playerid][index][Position][3], WeaponSettings[playerid][index][Position][4], WeaponSettings[playerid][index][Position][5]);
                Dialog_Show(playerid, WepPosition_Manual, DIALOG_STYLE_INPUT, "Weapon Settings Position", info, "Update", "Close");
            }
        }
    } else EditingWeapon[playerid] = 0;
    return 1;
}

Dialog:WepPosition_Manual(playerid, response, listitem, inputtext[]) {
    if (response) {
        new Float:pos[6], weaponid = EditingWeapon[playerid];
        if (!sscanf(inputtext, "F(-0.116)F(0.189)F(0.088)F(0)F(44.5)F(0)",pos[0],pos[1],pos[2],pos[3],pos[4],pos[5])) {
            new string[1024], index = (weaponid >= 22 && weaponid <= 38) ? (weaponid - 22) : (weaponid + 15);
            WeaponSettings[playerid][index][Position][0] = pos[0];
            WeaponSettings[playerid][index][Position][1] = pos[1];
            WeaponSettings[playerid][index][Position][2] = pos[2];
            WeaponSettings[playerid][index][Position][3] = pos[3];
            WeaponSettings[playerid][index][Position][4] = pos[4];
            WeaponSettings[playerid][index][Position][5] = pos[5];

            RemovePlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid));
            SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), WeaponSettings[playerid][index][Bone], WeaponSettings[playerid][index][Position][0], WeaponSettings[playerid][index][Position][1], WeaponSettings[playerid][index][Position][2], WeaponSettings[playerid][index][Position][3], WeaponSettings[playerid][index][Position][4], WeaponSettings[playerid][index][Position][5], 1.0, 1.0, 1.0);

            mysql_format(g_SQL, string, sizeof(string), "INSERT INTO weaponsettings VALUES (%d, %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %d, %d) ON DUPLICATE KEY UPDATE PosX = %.3f, PosY = %.3f, PosZ = %.3f, RotX = %.3f, RotY = %.3f, RotZ = %.3f", pData[playerid][pID], weaponid, WeaponSettings[playerid][index][Position][0], WeaponSettings[playerid][index][Position][1], WeaponSettings[playerid][index][Position][2], WeaponSettings[playerid][index][Position][3], WeaponSettings[playerid][index][Position][4], WeaponSettings[playerid][index][Position][5], WeaponSettings[playerid][index][Bone], WeaponSettings[playerid][index][Hidden], WeaponSettings[playerid][index][Position][0], WeaponSettings[playerid][index][Position][1], WeaponSettings[playerid][index][Position][2], WeaponSettings[playerid][index][Position][3], WeaponSettings[playerid][index][Position][4], WeaponSettings[playerid][index][Position][5]);
            mysql_tquery(g_SQL, string);

            format(string, sizeof(string), "Please input the weapon settings position below:\nCurrent value x y z rx ry rz:\n"YELLOW_E"%.3f %.3f %.3f %.3f %.3f %.3f", WeaponSettings[playerid][index][Position][0], WeaponSettings[playerid][index][Position][1], WeaponSettings[playerid][index][Position][2], WeaponSettings[playerid][index][Position][3], WeaponSettings[playerid][index][Position][4], WeaponSettings[playerid][index][Position][5]);
            Dialog_Show(playerid, WepPosition_Manual, DIALOG_STYLE_INPUT, "Weapon Settings Position", string, "Update", "Close");
            return 1;
        }
    } else EditingWeapon[playerid] = 0;
    return 1;
}
