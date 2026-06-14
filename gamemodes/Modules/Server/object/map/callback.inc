
#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
  foreach(new slotremove : RemoveBuild) if(RemoveObj[slotremove][rModel]) RemoveBuildingForPlayer(playerid, RemoveObj[slotremove][rModel], RemoveObj[slotremove][rX], RemoveObj[slotremove][rY], RemoveObj[slotremove][rZ], 0.250);
  return 1;
}

hook OnGameModeExit()
{
	foreach(new slot : DynamicObjects)
	{
	    DestroyDynamicObject(DynamicObject[slot]);
	}
	Iter_Clear(DynamicObjects);
    foreach(new slot : DynObject)
    {
        DestroyDynamicObject(DynObj[slot]);
        format(DynObjName[slot], 52, "");
    }
    Iter_Clear(DynObject);
    foreach(new remoid : RemoveBuild) format(RemoveObj[remoid][rName], 52, "");
    Iter_Clear(RemoveBuild);
}

hook OnPlayerDisconnect(playerid, reason)
{
	if(GetPVarType(playerid,"EditingObject") > 0)
	{
	    new slot = GetPVarInt(playerid,"EditingObject");
		DeletePVar(playerid,"EditingObject");
	    ObjectEditor[slot] = INVALID_PLAYER_ID;
	}
}
