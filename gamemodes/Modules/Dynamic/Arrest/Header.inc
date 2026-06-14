#define MAX_ARREST 100

enum dynamicarrest {
    arrestID,
    Float:arrestPos[3],
    Float:arrestCell[3],
    arrestIntCell,
    arrestWorldCell,
    arrestInt,
    arrestWorld,
    Text3D:arrestLabel,
	arrestPickup
}
new DynArrest[MAX_ARREST][dynamicarrest],
    Iterator:DynArrests<MAX_ARREST>;