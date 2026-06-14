
enum lockerinfo
{
	lType,
	Float:lPosX,
	Float:lPosY,
	Float:lPosZ,
	lInt,
	Text3D:lLabel,
	lPickup
};

new lData[MAX_LOCKERS][lockerinfo],
	Iterator: Lockers<MAX_LOCKERS>;
	