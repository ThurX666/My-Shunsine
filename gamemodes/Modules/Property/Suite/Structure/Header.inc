
#define MAX_SUITE_STRUCTURE 50
enum suitestruct {
  suitestructID,
  suitestructModel,
  Float:suitestructPos[3],
  Float:suitestructRot[3],
  suitestructMaterial,
  suitestructColor,
  suitestructObject
};
new SuiteStructure[MAX_SUITE_ROOM][MAX_SUITE_STRUCTURE][suitestruct],
  Iterator:SuiteStructures[MAX_SUITE_ROOM]<MAX_SUITE_STRUCTURE>;
new ListedSuiteStructures[MAX_PLAYERS][MAX_SUITE_STRUCTURE] = {-1, ...};
