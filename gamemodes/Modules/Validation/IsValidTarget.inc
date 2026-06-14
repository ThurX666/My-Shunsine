// Validation to ensure target is valid and not self

stock IsValidTarget(playerid, targetid)
{
    if (targetid == INVALID_PLAYER_ID || !IsPlayerConnected(targetid))
    {
        return 0; // Target is invalid
    }

    if (playerid == targetid)
    {
        return 0; // Self-targeting not allowed
    }

    return 1; // Valid target
}