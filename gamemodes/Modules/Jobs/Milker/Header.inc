// Sidejob Milker Definitions
#define MAX_MILKER_CYCLES 10
#define MILKER_SALARY 6700 // $67.00
#define SIDEJOB_MILKER 402

// Milker Cow Positions (6 points)
new const Float:g_MilkerCowPos[6][3] = {
    {1529.3584, -43.0759, 20.0414},
    {1537.5991, -49.1459, 20.0314},
    {1529.7710, -56.7886, 19.5014},
    {1532.6249, -70.1318, 18.9613},
    {1538.8887, -62.4726, 19.5014},
    {1544.1086, -55.1759, 20.0114}
};

// Milker Drop-off Point
new const Float:g_MilkerDropOff[3] = {1541.9679, -41.2531, 21.2003};

// Milker Locker Start Point
new const Float:g_MilkerLocker[4] = {1556.2843, -32.5951, 21.3849, 90.0};

new
    MilkerCycles[MAX_PLAYERS],
    MilkerMilkCount[MAX_PLAYERS],
    MilkerActive[MAX_PLAYERS],
    MilkerCowIndex[MAX_PLAYERS],
    MilkerObjects[MAX_PLAYERS],
    MilkerCP[MAX_PLAYERS];   // Dynamic checkpoint ID
