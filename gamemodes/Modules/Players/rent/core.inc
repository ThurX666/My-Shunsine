#define MAX_RENT 50

enum rentveh
{
    rID,
    Float:rX,
    Float:rY,
    Float:rZ,
    Float:rRX,
    Float:rRY,
    Float:rRZ,
    Float:rRA,
    rType,
    rPickup,
	Text3D:rLabelPoint
};
new rentData[MAX_RENT][rentveh],
    Iterator:Rents<MAX_RENT>;
