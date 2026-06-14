
#define MAX_SUITE_FURNITURE 100
enum suiteFurniture {
  suitefurnID,
  suitefurnModel,
  suitefurnName[128],
  Float:suitefurnPos[3],
  Float:suitefurnRot[3],
  suitefurnMaterials[MAX_MATERIALS],
  suitefurnObject,
  suitefurnUnused
};
new SuiteFurniture[MAX_SUITE_ROOM][MAX_SUITE_FURNITURE][suiteFurniture],
  Iterator:SuiteFurnitures[MAX_SUITE_ROOM]<MAX_SUITE_FURNITURE>;
new ListedSuiteFurnitures[MAX_PLAYERS][MAX_SUITE_FURNITURE];
