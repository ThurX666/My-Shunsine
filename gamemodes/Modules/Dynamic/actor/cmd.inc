
// Commands
CMD:createactor(playerid, params[])
{
    static
        skin,
        name[24],
        id,
        Float:location[4];
        
    if (pData[playerid][pAdmin] < 5)
        return PermissionError(playerid);
        
    if(sscanf(params,"ds[24]",skin, name))
        return Usage(playerid, "/createactor [skin] [name]");
        
    if(strlen(name) > 24)
        return Error(playerid, "The name to long, maximum character is 24.");

    GetPlayerPos(playerid, location[0], location[1], location[2]);
    GetPlayerFacingAngle(playerid, location[3]);

    id = Actor_Create(name, skin, location[0], location[1], location[2], location[3], GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

    SetPlayerPos(playerid, location[0], location[1], location[2]+2);
    
    if(id == INVALID_ITERATOR_SLOT)
        return Error(playerid, "The server has reached the limit for actor.");

    Servers(playerid, "You have successfully created actor ID: %d (total actors: %d).", id, Iter_Count(Actors));
    return 1;
}

CMD:editactor(playerid, params[])
{
    if (pData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new opsi[15], id, string[128];

    if(sscanf(params, "ds[15]S()[24]", id, opsi, string))
        return Usage(playerid, "/editactor [actorid] [location/name/skin/animation]");

    if(!Iter_Contains(Actors, id))
        return Error(playerid, "Actor id does not exists.");

    if(!strcmp(opsi, "location", true))
    {
        GetPlayerPos(playerid, ActorData[id][actorPos][0],ActorData[id][actorPos][1],ActorData[id][actorPos][2]);
        GetPlayerFacingAngle(playerid, ActorData[id][actorPos][3]);
        ActorData[id][actorVirtualWorld] = GetPlayerVirtualWorld(playerid);
        ActorData[id][actorInterior] = GetPlayerInterior(playerid);

        Servers(playerid, "You've changed actor location for id %d.", id);
        Actor_Refresh(id);
        Actor_Save(id);
    }
    else if(!strcmp(opsi, "name", true))
    {
        new name[24];

        if(sscanf(string, "s[24]", name))
            return Usage(playerid, "/editactor id name [actor name]");

        if(strval(name) > 24)
            return Error(playerid, "Name is too long.");

        ActorData[id][actorName] = EOS;
        format(ActorData[id][actorName], 24, ColouredText(name));
        Servers(playerid, "You've changed actor name for id %d to %s.", id, ActorData[id][actorName]);
        Actor_Refresh(id);
        Actor_Save(id);
    }
    else if(!strcmp(opsi, "skin", true))
    {
        new skin;

        if(sscanf(string, "d", skin))
            return Usage(playerid, "/editactor id skin [actor skin id]");

        if(skin < 1 || skin > 311)
            return Error(playerid, "Invalid skin id.");

        ActorData[id][actorSkin] = skin;

        Servers(playerid, "You've changed actor skin for id %d to skin id %d.", id, ActorData[id][actorSkin], skin);
        Actor_Refresh(id);
        Actor_Save(id);
    }
    else if(!strcmp(opsi, "animation", true))
    {
        new animlib[32],
            animname[32];

        if(!GetPlayerAnimationIndex(playerid)) return Error(playerid, "You're not play animation on you.");

        GetAnimationName(GetPlayerAnimationIndex(playerid), animlib, sizeof(animlib), animname, sizeof(animname));
        format(ActorData[id][actorAnimlib], 32, animlib);
        format(ActorData[id][actorAnimname], 32, animname);
        Servers(playerid, "You've changed animation for actor id %d (animlib: %s | animname: %s)", id, ActorData[id][actorAnimlib], ActorData[id][actorAnimname]);
        Actor_Refresh(id);
        Actor_Save(id);
    }
    else
        return Usage(playerid, "/editactor [actorid] [location/name/skin/animation]");

    return 1;
}

CMD:destroyactor(playerid, params[])
{
    static
        id = 0;

    if (pData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    if(sscanf(params, "d", id))
        return Usage(playerid, "/destroyactor [actor id]");

    if(!Iter_Contains(Actors, id))
        return Error(playerid, "You have specified an invalid actor ID.");

    Actor_Delete(id);
    Servers(playerid, "You have successfully destroyed actor ID: %d.", id);
    return 1;
}