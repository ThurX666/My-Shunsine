
enum vehicledata
{
	ID,
	Faction,
    Bisnis,
    Workshop,
	SpawnType,
	Model,
	Color[2],
	PaintJob,
	Locked,
	Plate[15],
	Float:Health,
	Fuel,
	Float:Pos[5],
	Interior,
	Virtual,
	Damage[5],
	Mod[MAX_MODS],
    Weapon[5],
	Ammo[5],
    TypeAmmo[5],
    Storage[5],
	Text3D:VehicleText,
	VehicleOwner[52],
	VehicleSpawnTime,
	Vehicle
};
new VehicleData[MAX_VEHICLES][vehicledata],
	Iterator:VehicleData<MAX_VEHICLES>;

//Storage[0] [Food(Bisnis)]
//Storage[1] [Component]