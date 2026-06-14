
CMD:createspeed(playerid, params[])
{
    static
        Float:limit,
        Float:range;

    if (pData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    if(sscanf(params, "ff", limit, range))
        return Usage(playerid, "/createspeed [speed limit] [range] (default range: 30)");

    if(limit < 5.0 || limit > 150.0)
        return Error(playerid, "The speed limit can't be below 5 or above 150.");

    if(range < 5.0 || range > 50.0)
        return Error(playerid, "The range can't be below 5 or above 50.");

    if(Speed_Nearest(playerid) != -1)
        return Error(playerid, "You can't do this in range another speed camera.");

    new id = Speed_Create(playerid, limit, range);

    if(id == -1)
        return Error(playerid, "The server has reached the limit for speed cameras.");

    Servers(playerid, "You have created speed camera ID: %d.", id);
    return 1;
}

CMD:editspeed(playerid, params[]) {
    if (pData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new option[24], optionalParams[32];
    if (sscanf(params, "s[24]S()[32]", option, optionalParams))
        return Usage(playerid, "/editspeed [pos/speedlimit/range]");

    if (!strcmp(option, "pos", true)) {
        new speedId;
        if (sscanf(optionalParams, "d", speedId))
            return Usage(playerid, "/editspeed pos [speed id]");

        if((speedId < 0 || speedId >= MAX_SPEED_CAMERAS) || !SpeedData[speedId][speedExists])
            return Error(playerid, "You have specified an invalid speed camera ID.");

        pData[playerid][pEditSpeed] = speedId;
        EditDynamicObject(playerid, SpeedData[speedId][speedObject]);
        SendCustomMessage(playerid, "SPEEDCAM", "You're now editing Speed Camera id: "YELLOW_E"%d", speedId);
    } else if (!strcmp(option, "speedlimit", true)) {
        new speedId, Float:limit;
        if (sscanf(optionalParams, "df", speedId, limit))
            return Usage(playerid, "/editspeed speedlimit [speed id] [speed limit (mph)]");

        if((speedId < 0 || speedId >= MAX_SPEED_CAMERAS) || !SpeedData[speedId][speedExists])
            return Error(playerid, "You have specified an invalid speed camera ID.");

        SpeedData[speedId][speedLimit] = limit;
        Speed_Refresh(speedId);
        Speed_Save(speedId);
        SendCustomMessage(playerid, "SPEEDCAM", "You've been changed speed limit of Speed Camera id: "YELLOW_E"%d", speedId);
    } else if (!strcmp(option, "range", true)) {
        new speedId, Float:range;
        if (sscanf(optionalParams, "df", speedId, range))
            return Usage(playerid, "/editspeed speedlimit [speed id] [speed range]");

        if((speedId < 0 || speedId >= MAX_SPEED_CAMERAS) || !SpeedData[speedId][speedExists])
            return Error(playerid, "You have specified an invalid speed camera ID.");

        SpeedData[speedId][speedRange] = range;
        Speed_Refresh(speedId);
        Speed_Save(speedId);
        SendCustomMessage(playerid, "SPEEDCAM", "You've been changed range of Speed Camera id: "YELLOW_E"%d", speedId);
    } else Usage(playerid, "/editspeed [pos/speedlimit/range]");
    return 1;
}

CMD:destroyspeed(playerid, params[])
{
    static
        id = 0;

    if (pData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    if(sscanf(params, "d", id))
        return Usage(playerid, "/destroyspeed [speed id]");

    if((id < 0 || id >= MAX_SPEED_CAMERAS) || !SpeedData[id][speedExists])
        return Error(playerid, "You have specified an invalid speed camera ID.");

    Speed_Delete(id);
    Servers(playerid, "You have successfully destroyed speed camera ID: %d.", id);
    return 1;
}
