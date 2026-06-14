#include <YSI\y_hooks>
hook OnPlayerEditAttachedObj(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ,Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
    #if defined DEBUG_MODE
        printf("[Callback: OnPlayerEditAttachedObj]: Playerid: %s", playerid);
    #endif
	
	return 1;
}
