
// Callback
function Actor_Load()
{
    new rows = cache_num_rows();

    for (new id = 0; id < rows; id ++)
    {
        cache_get_value_int(id, "actorID", ActorData[id][actorID]);
        cache_get_value_int(id, "actorSkin", ActorData[id][actorSkin]);
        cache_get_value_int(id, "actorVw", ActorData[id][actorVirtualWorld]);
        cache_get_value_int(id, "actorInt", ActorData[id][actorInterior]);
        
        cache_get_value(id, "actorName", ActorData[id][actorName], 24);
        cache_get_value(id, "animlib", ActorData[id][actorAnimlib], 32);
        cache_get_value(id, "animname", ActorData[id][actorAnimname], 32);

        cache_get_value_float(id, "actorX", ActorData[id][actorPos][0]);
        cache_get_value_float(id, "actorY", ActorData[id][actorPos][1]);
        cache_get_value_float(id, "actorZ", ActorData[id][actorPos][2]);
        cache_get_value_float(id, "actorA", ActorData[id][actorPos][3]);

        Iter_Add(Actors, id);
        Actor_Refresh(id);
    }
    printf("*** [Database: Loaded] actor data (%d count).", rows);
    return 1;
}

function OnActorCreated(id)
{
    if (!Iter_Contains(Actors, id))
        return 0;
    
    ActorData[id][actorID] = cache_insert_id();
    Actor_Save(id);
    return 1;
}

// Function
Actor_Create(name[], skin, Float:x, Float:y, Float:z, Float:angle, vw, interior)
{
    new id = INVALID_ITERATOR_SLOT;

    if ((id = Iter_Free(Actors)) != INVALID_ITERATOR_SLOT) {
        new string[225];
        format(ActorData[id][actorName],24,ColouredText(name));
        format(ActorData[id][actorAnimlib],32,"GRAVEYARD");
        format(ActorData[id][actorAnimname],32,"prst_loopa");

        ActorData[id][actorSkin] = skin;
        ActorData[id][actorPos][0] = x;
        ActorData[id][actorPos][1] = y;
        ActorData[id][actorPos][2] = z;
        ActorData[id][actorPos][3] = angle;
        ActorData[id][actorVirtualWorld] = vw;
        ActorData[id][actorInterior] = interior;

        Iter_Add(Actors, id);
        Actor_Refresh(id);

        format(string,sizeof(string),"INSERT INTO `actor` (`actorVw`) VALUES ('%d')",vw);
        mysql_tquery(g_SQL, string, "OnActorCreated", "d", id);
        return id;
    }
    return INVALID_ITERATOR_SLOT;
}

Actor_Refresh(id)
{
    if(!Iter_Contains(Actors, id))
        return 0;

    new string[225];
    
    if(IsValidDynamic3DTextLabel(ActorData[id][actorLabel]))
        DestroyDynamic3DTextLabel(ActorData[id][actorLabel]);

    if (IsValidDynamicActor(ActorData[id][actorDisplay]))
        DestroyDynamicActor(ActorData[id][actorDisplay]);

    ActorData[id][actorDisplay] = CreateDynamicActor(ActorData[id][actorSkin],ActorData[id][actorPos][0],ActorData[id][actorPos][1],ActorData[id][actorPos][2],ActorData[id][actorPos][3], 1, 100.0, ActorData[id][actorVirtualWorld], ActorData[id][actorInterior]);

    format(string,sizeof(string),""GREY_E"[Actor:%d]\n"WHITE_E"%s", id, ActorData[id][actorName]);
    ActorData[id][actorLabel] = CreateDynamic3DTextLabel(string, COLOR_ARWIN, ActorData[id][actorPos][0],ActorData[id][actorPos][1],ActorData[id][actorPos][2] + 1.2, 7.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,0, ActorData[id][actorVirtualWorld],ActorData[id][actorInterior]);

    ApplyDynamicActorAnimation(ActorData[id][actorDisplay], ActorData[id][actorAnimlib], ActorData[id][actorAnimname], 4.1, 1, 0, 0, 1, 0);
    return 1;
}

Actor_Save(id)
{
    static
        query[1024];

    format(query,sizeof(query),"UPDATE `actor` SET `actorName`='%s', `actorSkin`='%d', `actorX`='%f', `actorY`='%f', `actorZ`='%f', `actorA`='%f',`actorVw`='%d',`actorInt`='%d',`animlib`='%s', `animname`='%s' WHERE `actorID` = '%d'",
        ActorData[id][actorName],
        ActorData[id][actorSkin],
        ActorData[id][actorPos][0],
        ActorData[id][actorPos][1],
        ActorData[id][actorPos][2],
        ActorData[id][actorPos][3],
        ActorData[id][actorVirtualWorld],
        ActorData[id][actorInterior],
        ActorData[id][actorAnimlib],
        ActorData[id][actorAnimname],
        ActorData[id][actorID]
    );
    return mysql_tquery(g_SQL, query);
}

Actor_Delete(actorid)
{
    if (!Iter_Contains(Actors, actorid))
        return 0;

    new
        string[64];

    format(string, sizeof(string), "DELETE FROM `actor` WHERE `actorID` = '%d'", ActorData[actorid][actorID]);
    mysql_tquery(g_SQL, string);

    if(IsValidDynamic3DTextLabel(ActorData[actorid][actorLabel]))
        DestroyDynamic3DTextLabel(ActorData[actorid][actorLabel]);

    if(IsValidDynamicActor(ActorData[actorid][actorDisplay]))
        DestroyDynamicActor(ActorData[actorid][actorDisplay]);
    
    ActorData[actorid][actorID] = INVALID_ITERATOR_SLOT;
    ActorData[actorid][actorLabel] = Text3D:INVALID_STREAMER_ID;
    Iter_Remove(Actors, actorid);
    return 1;
}
