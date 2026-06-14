#define MAX_DAMAGE                      (55)
#define BODY_PART_TORSO                 (3)
#define BODY_PART_GROIN                 (4)
#define BODY_PART_RIGHT_ARM             (5)
#define BODY_PART_LEFT_ARM              (6)
#define BODY_PART_RIGHT_LEG             (7)
#define BODY_PART_LEFT_LEG              (8)
#define BODY_PART_HEAD                  (9)
enum damageData {
    damageID,
    damageExists,
    damageBodypart,
    damageWeapon,
    damageAmount,
    damageTime
};
new DamageData[MAX_PLAYERS][MAX_DAMAGE][damageData];