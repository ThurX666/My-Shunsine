
enum weaponSettings
{
    Float:Position[6],
    Bone,
    Hidden
}
new WeaponSettings[MAX_PLAYERS][50][weaponSettings], WeaponTick[MAX_PLAYERS], EditingWeapon[MAX_PLAYERS];
 
stock const g_aWeaponSlots[] = {
    0, // Fist
    0, // Brass Knuckle
    1, // Golf Club
    1, // Nightstick
    1, // Knife
    1, // Baseball Bat
    1, // Shovel
    1, // Pool Clue
    1, // Katana
    1, // Chainsaw
    10, //Purple Dildo
    10, // Dildo
    10, // Vibrator
    10, // Silver Vibrator
    10, // Flowers
    10, // Cane
    8, // Grenade
    8, // Teargas (17)
    8, // Molotov Cocktail (18)
    0, // (unused) (19)
    0, // (unused) (20)
    0, // (unused) (21)
    2, // 9mm
    2, // Silenced 9mm
    2, // Desert Eagle
    3, // Shotgun
    3, // Sawnoff Shotgun
    3, // Combat Shotgun
    4, // Micro SMG/Uzi
    4, // MP5
    5, // AK47
    5, // M4
    4, //TEC-9
    6, //County Rifle
    6, // Sniper Rifle
    7, // RPG
    7, // HS Rocket
    7, // Flamethrower
    7, // Minigun
    8, // Satchel Charge
    12, // Detonator
    9, // Spraycan
    9, // Fire Extinguisher
    9, // Camera 
    11, // Night Vision Goggles
    11, // Thermal Googgles
    11 // Parachute
};
