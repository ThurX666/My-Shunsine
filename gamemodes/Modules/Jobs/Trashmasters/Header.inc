
enum garbageData {
    garbageID,
    garbageExists,
    garbageModel,
    garbageCapacity,
    Float:garbagePos[4],
    garbageInterior,
    garbageWorld,
    garbageObject
};

new GarbageData[MAX_GARBAGE_BINS][garbageData];
new VehicleTrashmaster[4];