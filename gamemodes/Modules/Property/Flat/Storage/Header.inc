#define MAX_FLAT_STORAGE  (5)

enum flatStorage {
  rItemID,
  rItemName[32 char],
  rItemModel,
  rItemQuantity
};
new FlatStorage[MAX_FLAT_ROOM][MAX_FLAT_STORAGE][flatStorage],
  Iterator:FlatStorages[MAX_FLAT_ROOM]<MAX_FLAT_STORAGE>;
