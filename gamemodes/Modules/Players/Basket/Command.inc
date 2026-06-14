CMD:basket(playerid, params[])
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	DestroyObject(Ball);
	Ball = CreateObject(2114, x+random(3), y+random(3), z-0.8, 0, 0, 96);
	return 1;
}