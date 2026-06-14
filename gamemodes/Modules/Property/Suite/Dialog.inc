Dialog:Dialog_ApartmentMenu(playerid,response,listitem,inputtext[]) {
    new suiteid;

    if ((suiteid = SuiteRoom_Inside(playerid)) != -1 && (Owner_SuiteRoom(playerid, suiteid))) {
        if (response) {
            switch (listitem) {
                case 0: SuiteFurniture_Show(playerid, suiteid);
                case 1: {
                    if (pData[playerid][pJob] != 9 && pData[playerid][pJob2] != 9) return Error(playerid, "You're not a Builder");
                    Dialog_Show(playerid, Apart_Structures, DIALOG_STYLE_LIST, "Select Suite Structure", "Add structure\nMove structure\nRetexture structure\nDestroy structure\nCopy structure\nDestroy all structure\nStructure list\nMove furniture\nDestroy furniture\nStore furniture\nFurniture list", "Select", "Back");
                }
            }
        }
    }
    return 1;
}
      