#include <YSI\y_hooks>

// =================== [ DEFINES & VARIABLES ] ===================
#define MAX_INVENTORY 20 // Maksimal slot inventory yang dimiliki player
#define MAX_DROPPED_ITEMS 500

// Variable TextDraw Inventory
new PlayerText:INVNAME[MAX_PLAYERS][6];
new PlayerText:INVINFO[MAX_PLAYERS][11];
new PlayerText:NAMETD[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText:INDEXTD[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText:MODELTD[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText:AMOUNTTD[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText:GARISBAWAH[MAX_PLAYERS][MAX_INVENTORY];

new PlayerText:NOTIFBOX[MAX_PLAYERS][6];

new ItemSelected[MAX_PLAYERS] = {-1, ...};

// =================== [ ENUMS & DATA ] ===================
// Maksimal item yang bisa tergeletak di lantai server (sesuaikan jika perlu)
enum e_DropData {
    dExists,
    dItemName[32],
    dAmount,
    Float:dX,
    Float:dY,
    Float:dZ,
    dInt,
    dWorld,
    dObject,      // ID Dynamic Object
    Text3D:dLabel, // ID Dynamic 3D Text Label
    dWeaponID,    // ID senjata (0 jika bukan weapon)
    dWeaponAmmo,  // Ammo senjata
    dWeaponTypeSurplus // Tipe ammo (0=normal, 1=surplus, 2=JHP)
};
new DropData[MAX_DROPPED_ITEMS][e_DropData];

enum inventoryData
{
    invExists,           // Mengecek apakah slot ini ada isinya (1) atau kosong (0)
    invItem[32 char],    // Nama item (contoh: "Snack", "Water")
    invModel,            // Model ID object SAMP (untuk ditampilkan di TextDraw)
    invTotalQuantity,    // Berat/Kapasitas (jika kamu pakai sistem berat)
    invAmount            // Jumlah item yang dimiliki (Quantity)
};
new InventoryData[MAX_PLAYERS][MAX_INVENTORY][inventoryData];

enum e_InventoryItems
{
    e_InventoryItem[32], // Nama Item
    e_InventoryModel,    // ID Object SAMP untuk preview TextDraw
    e_InventoryTotal     // Bobot/Berat item
};

// =================== [ WEAPON NAME TO ID MAPPING ] ===================
// Mencocokkan nama senjata (dari GetWeaponName) ke weapon ID
stock GetWeaponIDFromName(const name[])
{
    static const g_aWeaponNames[][] = {
        "Brass Knuckle", "Golf Club", "Nightstick", "Knife",
        "Baseball Bat", "Shovel", "Pool Cue", "Katana",
        "Chainsaw", "Purple Dildo", "Dildo", "Vibrator",
        "Silver Vibrator", "Flowers", "Cane", "Grenade",
        "Tear Gas", "Molotov Cocktail", "", "", "",
        "", "Colt 45", "Silenced 9mm", "Desert Eagle",
        "Shotgun", "Sawnoff Shotgun", "Combat Shotgun",
        "Micro SMG/Uzi", "MP5", "AK-47", "M4", "Tec-9",
        "Rifle", "Sniper Rifle", "RPG", "HS Rocket",
        "Flamethrower", "Minigun", "Satchel Charge",
        "Detonator", "Spraycan", "Fire Extinguisher",
        "Camera", "Night Vision Goggles", "Thermal Goggles",
        "Parachute"
    };
    for (new i = 1; i < sizeof(g_aWeaponNames); i++) {
        if (!strcmp(name, g_aWeaponNames[i], true)) return i;
    }
    return 0;
}

stock BarangMasuk(playerid)
{
    // 1. Kita bersihkan dulu tampilan inventory-nya
    Inventory_Clear(playerid);

    // 2. Mulai mendeteksi variabel pData lu dan memasukkannya ke slot TextDraw
    // Format: Inventory_Addset(playerid, "Nama Item", Model_SAMP, Jumlahnya);

    if(pData[playerid][pMoney] > 0) Inventory_Addset(playerid, "Cash", 1212, pData[playerid][pMoney]);
    if(pData[playerid][pSnack] > 0) Inventory_Addset(playerid, "Snack", 2821, pData[playerid][pSnack]);
    if(pData[playerid][pSprunk] > 0) Inventory_Addset(playerid, "Sprunk", 2958, pData[playerid][pSprunk]);
    if(pData[playerid][pRokok] > 0) Inventory_Addset(playerid, "Cigarettes", 19625, pData[playerid][pRokok]);
    if(pData[playerid][pBandage] > 0) Inventory_Addset(playerid, "Bandage", 11736, pData[playerid][pBandage]);
    if(pData[playerid][pMedicine] > 0) Inventory_Addset(playerid, "Medicine", 1241, pData[playerid][pMedicine]);
    if(pData[playerid][pMedkit] > 0) Inventory_Addset(playerid, "Medkit", 11738, pData[playerid][pMedkit]);
    if(pData[playerid][pComponent] > 0) Inventory_Addset(playerid, "Component", 2808, pData[playerid][pComponent]);
    if(pData[playerid][pFood] > 0) Inventory_Addset(playerid, "Food", 2768, pData[playerid][pFood]);
    if(pData[playerid][pFishTool] > 0) Inventory_Addset(playerid, "Fish pole", 18632, pData[playerid][pFishTool]);
    if(pData[playerid][pWorm] > 0) Inventory_Addset(playerid, "Bait", 19566, pData[playerid][pWorm]);
    if(pData[playerid][pPayToll] > 0) Inventory_Addset(playerid, "Toll Card", 1581, pData[playerid][pPayToll]);
    
    // Pills
    if(pData[playerid][pCoughPills] > 0) Inventory_Addset(playerid, "Neladryl", 1241, pData[playerid][pCoughPills]);
    if(pData[playerid][pMigrainPills] > 0) Inventory_Addset(playerid, "Kratotamax", 1241, pData[playerid][pMigrainPills]);
    if(pData[playerid][pFiverPills] > 0) Inventory_Addset(playerid, "Lazattavitus", 1241, pData[playerid][pFiverPills]);

    // Drugs & Misc
    if(pData[playerid][pCrack] > 0) Inventory_Addset(playerid, "Crack", 1579, pData[playerid][pCrack]);
    if(pData[playerid][pPot] > 0) Inventory_Addset(playerid, "Pot", 860, pData[playerid][pPot]);
    if(pData[playerid][pMaterial] > 0) Inventory_Addset(playerid, "Material", 2041, pData[playerid][pMaterial]);

    // Seeds
    if(pData[playerid][pSeedWheat] > 0) Inventory_Addset(playerid, "Wheat Seed", 859, pData[playerid][pSeedWheat]);
    if(pData[playerid][pSeedOnion] > 0) Inventory_Addset(playerid, "Onion Seed", 859, pData[playerid][pSeedOnion]);
    if(pData[playerid][pSeedCarrot] > 0) Inventory_Addset(playerid, "Carrot Seed", 859, pData[playerid][pSeedCarrot]);
    if(pData[playerid][pSeedPotato] > 0) Inventory_Addset(playerid, "Potato Seed", 859, pData[playerid][pSeedPotato]);
    if(pData[playerid][pSeedCorn] > 0) Inventory_Addset(playerid, "Corn Seed", 859, pData[playerid][pSeedCorn]);

    // Plants
    if(pData[playerid][pWheat] > 0) Inventory_Addset(playerid, "Wheat", 862, pData[playerid][pWheat]);
    if(pData[playerid][pOnion] > 0) Inventory_Addset(playerid, "Onion", 862, pData[playerid][pOnion]);
    if(pData[playerid][pCarrot] > 0) Inventory_Addset(playerid, "Carrot", 862, pData[playerid][pCarrot]);
    if(pData[playerid][pPotato] > 0) Inventory_Addset(playerid, "Potato", 862, pData[playerid][pPotato]);
    if(pData[playerid][pCorn] > 0) Inventory_Addset(playerid, "Corn", 862, pData[playerid][pCorn]);
    if(pData[playerid][pBushForager] > 0) Inventory_Addset(playerid, "Wild Berries", 862, pData[playerid][pBushForager]);

    // Fish Array
    for(new i = 0; i < 5; i++) 
    {
        if(FishWeight[playerid][i] > 0.0) 
        {
            // Untuk ikan, kita bulatkan beratnya ke integer sebagai amount atau cukup taruh 1 slot per ikan
            Inventory_Addset(playerid, "Ocean Fish", 19630, floatround(FishWeight[playerid][i], floatround_ceil));
        }
    } 

    // Schematics
    if(pData[playerid][pSchematic][0] > 0) Inventory_Addset(playerid, "Sch: Rifle", 1872, pData[playerid][pSchematic][0]);
    if(pData[playerid][pSchematic][1] > 0) Inventory_Addset(playerid, "Sch: Shotgun", 1872, pData[playerid][pSchematic][1]);
    if(pData[playerid][pSchematic][2] > 0) Inventory_Addset(playerid, "Sch: Sawn", 1872, pData[playerid][pSchematic][2]);
    if(pData[playerid][pSchematic][3] > 0) Inventory_Addset(playerid, "Sch: Deagle", 1872, pData[playerid][pSchematic][3]);
    if(pData[playerid][pSchematic][4] > 0) Inventory_Addset(playerid, "Sch: MP-5", 1872, pData[playerid][pSchematic][4]);
    if(pData[playerid][pSchematic][5] > 0) Inventory_Addset(playerid, "Sch: AK-47", 1872, pData[playerid][pSchematic][5]);

    // ===================================
    // SISTEM SENJATA (UPDATE TERBARU)
    // ===================================
    for(new i = 0; i < 13; i++) // Ada 13 slot senjata di GTA SA
    {
        new wepid, ammo;
        GetPlayerWeaponData(playerid, i, wepid, ammo); // Baca langsung dari tangan player
        
        if(wepid > 0 && ammo > 0)
        {
            new wName[32];
            GetWeaponName(wepid, wName, sizeof(wName));
            
            // Masukkan ke slot inventory dengan object yang sesuai!
            Inventory_Addset(playerid, wName, GetWeaponModel(wepid), ammo); 
        }
    }
    return 1;
}

// Fungsi ini dipanggil saat player memencet tombol "USE" di TextDraw Inventory
stock OnPlayerUseInventoryItem(playerid, name[])
{
    if(!strcmp(name, "Bandage", true)) 
    {
        if(pData[playerid][pBandage] < 1) return Error(playerid, "Anda tidak memiliki perban.");
        
        new Float:darah;
        GetPlayerHealth(playerid, darah);
        if(darah+10 > 99) return Error(playerid, "You can't use bandage anymore");
        SetPlayerHealthEx(playerid, darah+10);
        
        pData[playerid][pBandage]--;
        SendClientMessageEx(playerid, COLOR_ARWIN, "USE: "WHITE_E"Anda telah berhasil menggunakan perban.");
    }
    else if(!strcmp(name, "Snack", true)) 
    {
        if(pData[playerid][pSnack] < 1) return Error(playerid, "Anda tidak memiliki snack.");
        
        pData[playerid][pSnack]--;
        if(pData[playerid][pHunger]+10 > 100) pData[playerid][pHunger] = 100;
        else pData[playerid][pHunger] += 10;
        SendClientMessageEx(playerid, COLOR_ARWIN, "USE: "WHITE_E"Anda telah berhasil menggunakan snack.");
        ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);      
    }
    else if(!strcmp(name, "Sprunk", true)) 
    {
        if(pData[playerid][pSprunk] < 1) return Error(playerid, "Anda tidak memiliki sprunk.");

        pData[playerid][pSprunk]--;
        if(pData[playerid][pEnergy]+10 > 100) pData[playerid][pEnergy] = 100;
        else pData[playerid][pEnergy] += 10;
        SendClientMessageEx(playerid, COLOR_ARWIN, "USE: "WHITE_E"Anda telah berhasil meminum sprunk.");
        ApplyAnimation(playerid, "VENDING", "VEND_Drink2_P", 4.1, 0, 0, 0, 0, 0, 1);
    }
    else if(!strcmp(name, "Cigarettes", true)) 
    {
        if(pData[playerid][pRokok] < 1) return Error(playerid, "Anda tidak memiliki rokok.");

        new Float:darah;
        GetPlayerHealth(playerid, darah);
        SetPlayerHealthEx(playerid, darah+10);
        ApplyAnimation(playerid,"SMOKING","M_smklean_loop",4.1, 0, 1, 1, 1, 1, 1);
        pData[playerid][pRokok]--;
    }
    else if(!strcmp(name, "Medicine", true)) 
    {
        if(pData[playerid][pMedicine] < 1) return Error(playerid, "Anda tidak memiliki medicine.");
        
        pData[playerid][pMedicine]--;
        pData[playerid][pSick] = 0;
        pData[playerid][pSickTime] = 0;
        SetPlayerDrunkLevel(playerid, 0);
        SendClientMessageEx(playerid, COLOR_ARWIN, "USE: "WHITE_E"Anda menggunakan medicine.");     
        ApplyAnimation(playerid,"SMOKING","M_smkstnd_loop",2.1,0,0,0,0,0);
    }
    else if(!strcmp(name, "Medkit", true))
    {
        if(pData[playerid][pMedkit] < 1) return Error(playerid, "Anda tidak memiliki medkit.");

        pData[playerid][pMedkit]--;
        pData[playerid][pSick] = 0;
        pData[playerid][pSickTime] = 0;
        
        new Float:darah;
        GetPlayerHealth(playerid, darah);
        if(darah+30 > 99) return Error(playerid, "You can't use medkit anymore");
        SetPlayerHealthEx(playerid, darah+30);
        
        SendClientMessageEx(playerid, COLOR_ARWIN, "USE: "WHITE_E"Anda menggunakan medkit.");
        ApplyAnimation(playerid,"SMOKING","M_smkstnd_loop",2.1,0,0,0,0,0);
    }
    else if(!strcmp(name, "Crack", true)) 
    {
        if(pData[playerid][pCrack] < 1) return Error(playerid, "You dont have crack.");
        if(pData[playerid][pCough] >= 20) return Error(playerid, "You have a severe illness, can not consume excessive crack!.");
        
        new Float:armor;
        GetPlayerArmour(playerid, armor);
        if(armor+10 > 90) return Error(playerid, "You can't use crack anymore");
        
        pData[playerid][pCrack]--;
        pData[playerid][pCough]++;
        pData[playerid][pDrugTime] += RandomEx(10,15);
        pData[playerid][pDrugUsed] = 1;
        SetPlayerArmourEx(playerid, armor+10);
        ApplyAnimation(playerid,"SMOKING","M_smkstnd_loop",2.1,0,0,0,0,0);
        SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 1000);
        SetPlayerWeather(playerid, -67);
        SetPlayerTime(playerid, 12, 12);
    }
    else if(!strcmp(name, "Pot", true)) 
    {
        if(pData[playerid][pPot] < 1) return Error(playerid, "You dont have pot.");
        if(pData[playerid][pCough] >= 20) return Error(playerid, "You have a severe illness, can not consume excessive pot!.");
        
        new Float:armor;
        GetPlayerArmour(playerid, armor);
        if(armor+5 > 25) return Error(playerid, "You can't use pot anymore");
        
        pData[playerid][pPot]--;
        pData[playerid][pCough]++;
        pData[playerid][pDrugTime] += RandomEx(10,15);
        pData[playerid][pDrugUsed] = 2;
        SetPlayerArmourEx(playerid, armor+5);
        ApplyAnimation(playerid,"SMOKING","M_smkstnd_loop",2.1,0,0,0,0,0);
        SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 1000);
        SetPlayerWeather(playerid, -67);
        SetPlayerTime(playerid, 12, 12);
    }
    else if(!strcmp(name, "Gas", true)) // Pastikan "Gas" di-add di BarangMasuk
    {
        if(pData[playerid][pGas] < 1) return Error(playerid, "Anda tidak memiliki gas.");
        if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Anda harus berada diluar kendaraan!");
        if(pData[playerid][pActivityTime] > 5) return Error(playerid, "Anda masih memiliki activity progress!");
        
        new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);
        if(IsValidVehicle(vehicleid))
        {
            new fuel = GetVehicleFuel(vehicleid);
            if(GetEngineStatus(vehicleid)) return Error(playerid, "Turn off vehicle engine.");
            if(fuel >= 999.0) return Error(playerid, "This vehicle gas is full.");
            if(!IsEngineVehicle(vehicleid)) return Error(playerid, "This vehicle can't be refull.");
            if(!GetHoodStatus(vehicleid)) return Error(playerid, "The hood must be opened before refull the vehicle.");
            
            pData[playerid][pGas]--;
            Info(playerid, "Don't move from your position or you will failed to refulling this vehicle.");
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
            PlayerTextDrawSetString(playerid, ProggresBar[playerid][2], "Refulling");
            for (new i; i < 3; i++) PlayerTextDrawShow(playerid, ProggresBar[playerid][i]);
            pData[playerid][pActivity] = SetTimerEx("RefullCar", 1000, true, "id", playerid, vehicleid);
            
            // Note: Untuk Gas mungkin lebih bagus Inventory_Close(playerid)
            // Biar UI nya hilang saat dia isi bensin
        }
    }
    // ==== PILLS ====
    else if(!strcmp(name, "Neladryl", true))
    {
        if(pData[playerid][pUsePills]) return Error(playerid, "Tidak dapat mengkonsumsi pill sekarang, tunggu hingga %d detik lagi.", pData[playerid][pUsePills]);
        if(pData[playerid][pCoughPills] < 1) return Error(playerid, "Anda tidak ada pil untuk penyakit ini.");
        if(pData[playerid][pCough] < 1) return Error(playerid, "Anda tidak dapat mengkonsumsi pil ini.");

        // Pengurangan & Efek
        pData[playerid][pCoughPills]--;
        pData[playerid][pCough] = 0;
        
        SendClientMessage(playerid, COLOR_ARWIN, "MEDICINEINFO: {FFff00}You've use Neladryl Acetate");
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "*%s take's out Neladryl Acetate and eat it.", ReturnName(playerid));
        
        pData[playerid][pUsePills] = 100; // Set cooldown
    }
    else if(!strcmp(name, "Kratotamax", true))
    {
        if(pData[playerid][pUsePills]) return Error(playerid, "Tidak dapat mengkonsumsi pill sekarang, tunggu hingga %d detik lagi.", pData[playerid][pUsePills]);
        if(pData[playerid][pMigrainPills] < 1) return Error(playerid, "Anda tidak ada pil untuk penyakit ini.");
        if(pData[playerid][pMigrainRate] < 1) return Error(playerid, "Anda tidak dapat mengkonsumsi pil ini.");

        // Pengurangan & Efek
        pData[playerid][pMigrainPills]--;
        if(++pData[playerid][pMigrainUsed] >= 5)
        {
            pData[playerid][pMigrainRate]  = 0;
            pData[playerid][pMigrainUsed] = 0;
        }
        
        SendClientMessage(playerid, COLOR_ARWIN, "MEDICINEINFO: {FFff00}You've use Kratotamax Plus");
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "*%s take's out Kratotamax Plus 1.0 and eat it.", ReturnName(playerid));
        
        pData[playerid][pUsePills] = 100; // Set cooldown
    }
    else if(!strcmp(name, "Lazattavitus", true))
    {
        if(pData[playerid][pUsePills]) return Error(playerid, "Tidak dapat mengkonsumsi pill sekarang, tunggu hingga %d detik lagi.", pData[playerid][pUsePills]);
        if(pData[playerid][pFiverPills] < 1) return Error(playerid, "Anda tidak ada pil untuk penyakit ini.");
        if(pData[playerid][pFever] < 1) return Error(playerid, "Anda tidak dapat mengkonsumsi pil ini.");

        // Pengurangan & Efek
        pData[playerid][pFiverPills]--;
        if(++pData[playerid][pFeverUsed] >= 5)
        {
            pData[playerid][pFeverUsed] = 0;
            pData[playerid][pFever] = 0;
        }
        
        SendClientMessage(playerid, COLOR_ARWIN, "MEDICINEINFO: {FFff00}You've use Lazattavitus Extra");
        SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "*%s take's out Lazattavitus Extra and eat it.", ReturnName(playerid));
        
        pData[playerid][pUsePills] = 100; // Set cooldown
    }
    // ==========================================
    // JIKA ITEM BUKAN USABLE (TIDAK BISA DIPAKAI)
    // ==========================================
    else
    {
        // Menampilkan pesan error jika item tidak masuk dalam daftar di atas
        Error(playerid, "Item '%s' tidak dapat digunakan secara langsung melalui inventory!", name);
    }

	Inventory_Close(playerid);
    return 1;
}

stock OnPlayerDropInventoryItem(playerid, name[])
{
    // Simpan nama item yang diklik ke memori sementara player
    SetPVarString(playerid, "DropItem", name);
    
    // Tampilkan dialog untuk memasukkan jumlah barang yang ingin dibuang
    new str[128];
    format(str, sizeof(str), "Item: %s\n\nMasukkan jumlah item yang ingin kamu buang:", name);
    Dialog_Show(playerid, InvDropItem, DIALOG_STYLE_INPUT, "Drop Item", str, "Buang", "Batal");
    
    return 1;
}

stock CreateDropItem(playerid, itemname[], amount)
{
    // Cari slot drop item yang kosong
    for(new i = 0; i < MAX_DROPPED_ITEMS; i++)
    {
        if(!DropData[i][dExists])
        {
            new Float:X, Float:Y, Float:Z;
            GetPlayerPos(playerid, X, Y, Z);
            
            // Simpan Data
            DropData[i][dExists] = 1;
            format(DropData[i][dItemName], 32, "%s", itemname);
            DropData[i][dAmount] = amount;
            DropData[i][dInt] = GetPlayerInterior(playerid);
            DropData[i][dWorld] = GetPlayerVirtualWorld(playerid);
            DropData[i][dX] = X + 0.5; // Sedikit di depan player
            DropData[i][dY] = Y + 0.5;
            DropData[i][dZ] = Z - 0.85; // Kurangi Z agar nempel di tanah (tidak melayang)

            // Buat Dynamic Object (Wadah/Kotak - Model 2663)
            DropData[i][dObject] = CreateDynamicObject(2663, DropData[i][dX], DropData[i][dY], DropData[i][dZ], 0.0, 0.0, 0.0, DropData[i][dWorld], DropData[i][dInt]);

            // Buat 3D Text Label
            new labelStr[128];
            format(labelStr, sizeof(labelStr), "[Dropped Item]\n{FFFFFF}%s\n{FFFF00}Amount: %d", itemname, amount);
            DropData[i][dLabel] = CreateDynamic3DTextLabel(labelStr, 0x00FF00FF, DropData[i][dX], DropData[i][dY], DropData[i][dZ] + 0.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DropData[i][dWorld], DropData[i][dInt]);

            return 1;
        }
    }
    return 0; // Jika server kepenuhan item di tanah
}

CMD:pickupitem(playerid, params[])
{
    // Animasi mengambil barang dari tanah
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
    
    for(new i = 0; i < MAX_DROPPED_ITEMS; i++)
    {
        if(DropData[i][dExists])
        {
            // Cek apakah player di dekat object (radius 2.0 meter) dan di world/interior yang sama
            if(IsPlayerInRangeOfPoint(playerid, 2.0, DropData[i][dX], DropData[i][dY], DropData[i][dZ]) && GetPlayerVirtualWorld(playerid) == DropData[i][dWorld] && GetPlayerInterior(playerid) == DropData[i][dInt])
            {
                new name[32], amount;
                format(name, sizeof(name), "%s", DropData[i][dItemName]);
                amount = DropData[i][dAmount];

                // =============================================
                // PROSES MENAMBAH BARANG KEMBALI KE PDATA
                // =============================================
                if(!strcmp(name, "Snack", true)) pData[playerid][pSnack] += amount;
                else if(!strcmp(name, "Sprunk", true)) pData[playerid][pSprunk] += amount;
                else if(!strcmp(name, "Food", true)) pData[playerid][pFood] += amount;
                else if(!strcmp(name, "Cigarettes", true)) pData[playerid][pRokok] += amount;
                else if(!strcmp(name, "Bandage", true)) pData[playerid][pBandage] += amount;
                else if(!strcmp(name, "Medicine", true)) pData[playerid][pMedicine] += amount;
                else if(!strcmp(name, "Medkit", true)) pData[playerid][pMedkit] += amount;
                
                // Pills
                else if(!strcmp(name, "Neladryl", true)) pData[playerid][pCoughPills] += amount;
                else if(!strcmp(name, "Kratotamax", true)) pData[playerid][pMigrainPills] += amount;
                else if(!strcmp(name, "Lazattavitus", true)) pData[playerid][pFiverPills] += amount;
                
                // Illegal & Misc
                else if(!strcmp(name, "Crack", true)) pData[playerid][pCrack] += amount;
                else if(!strcmp(name, "Pot", true)) pData[playerid][pPot] += amount;
                else if(!strcmp(name, "Material", true)) pData[playerid][pMaterial] += amount;
                else if(!strcmp(name, "Component", true)) pData[playerid][pComponent] += amount;
                
                // Tools
                else if(!strcmp(name, "Fish pole", true)) pData[playerid][pFishTool] += amount;
                else if(!strcmp(name, "Bait", true)) pData[playerid][pWorm] += amount;
                else if(!strcmp(name, "Toll Card", true)) pData[playerid][pPayToll] += amount;
                
                // Seeds
                else if(!strcmp(name, "Wheat Seed", true)) pData[playerid][pSeedWheat] += amount;
                else if(!strcmp(name, "Onion Seed", true)) pData[playerid][pSeedOnion] += amount;
                else if(!strcmp(name, "Carrot Seed", true)) pData[playerid][pSeedCarrot] += amount;
                else if(!strcmp(name, "Potato Seed", true)) pData[playerid][pSeedPotato] += amount;
                else if(!strcmp(name, "Corn Seed", true)) pData[playerid][pSeedCorn] += amount;
                
                // Plants
                else if(!strcmp(name, "Wheat", true)) pData[playerid][pWheat] += amount;
                else if(!strcmp(name, "Onion", true)) pData[playerid][pOnion] += amount;
                else if(!strcmp(name, "Carrot", true)) pData[playerid][pCarrot] += amount;
                else if(!strcmp(name, "Potato", true)) pData[playerid][pPotato] += amount;
                else if(!strcmp(name, "Corn", true)) pData[playerid][pCorn] += amount;
                else if(!strcmp(name, "Wild Berries", true)) pData[playerid][pBushForager] += amount;
                
                // Schematics
                else if(!strcmp(name, "Sch: Rifle", true)) pData[playerid][pSchematic][0] += amount;
                else if(!strcmp(name, "Sch: Shotgun", true)) pData[playerid][pSchematic][1] += amount;
                else if(!strcmp(name, "Sch: Sawn", true)) pData[playerid][pSchematic][2] += amount;
                else if(!strcmp(name, "Sch: Deagle", true)) pData[playerid][pSchematic][3] += amount;
                else if(!strcmp(name, "Sch: MP-5", true)) pData[playerid][pSchematic][4] += amount;
                else if(!strcmp(name, "Sch: AK-47", true)) pData[playerid][pSchematic][5] += amount;
                
                // Pesan sukses
                SendClientMessageEx(playerid, COLOR_ARWIN, "PICKUP: {FFFFFF}Anda telah mengambil %d %s dari lantai.", amount, name);

                // =============================================
                // MENGHAPUS OBJECT & LABEL DARI SERVER
                // =============================================
                DestroyDynamicObject(DropData[i][dObject]);
                DestroyDynamic3DTextLabel(DropData[i][dLabel]);

                // Reset variabel DropData agar slot bisa digunakan lagi
                DropData[i][dExists] = 0;
                DropData[i][dAmount] = 0;
                DropData[i][dItemName][0] = '\0';
                
				BarangMasuk(playerid); // Refresh inventory setelah mengambil barang
                return 1; // Hentikan loop jika sudah ketemu & berhasil diambil
            }
        }
    }
    
    // Jika tidak ada item di sekitarnya
    Error(playerid, "Tidak ada barang di sekitar Anda.");
    return 1;
}

stock OnPlayerGiveInventoryItem(playerid, name[])
{
    // Simpan nama item ke memori player
    SetPVarString(playerid, "GiveItem", name);
    
    // Munculkan dialog pertama (Meminta ID target)
    Dialog_Show(playerid, InvGiveItem, DIALOG_STYLE_INPUT, "Give Item - Target", "Masukkan ID player yang ingin Anda berikan barang ini:", "Lanjut", "Batal");
    
    return 1;
}

stock CreatePlayerInv(playerid)
{
    GARISBAWAH[playerid][0] = CreatePlayerTextDraw(playerid, 125.000, 170.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][0], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][0], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][0], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][0], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][0], 1);

	GARISBAWAH[playerid][1] = CreatePlayerTextDraw(playerid, 165.000, 170.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][1], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][1], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][1], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][1], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][1], 1);

	GARISBAWAH[playerid][2] = CreatePlayerTextDraw(playerid, 205.000, 170.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][2], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][2], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][2], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][2], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][2], 1);

	GARISBAWAH[playerid][3] = CreatePlayerTextDraw(playerid, 245.000, 170.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][3], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][3], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][3], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][3], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][3], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][3], 1);

	GARISBAWAH[playerid][4] = CreatePlayerTextDraw(playerid, 286.000, 170.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][4], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][4], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][4], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][4], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][4], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][4], 1);

	GARISBAWAH[playerid][5] = CreatePlayerTextDraw(playerid, 125.000, 226.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][5], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][5], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][5], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][5], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][5], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][5], 1);

	GARISBAWAH[playerid][6] = CreatePlayerTextDraw(playerid, 165.000, 226.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][6], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][6], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][6], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][6], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][6], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][6], 1);

	GARISBAWAH[playerid][7] = CreatePlayerTextDraw(playerid, 205.000, 226.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][7], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][7], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][7], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][7], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][7], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][7], 1);

	GARISBAWAH[playerid][8] = CreatePlayerTextDraw(playerid, 245.000, 226.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][8], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][8], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][8], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][8], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][8], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][8], 1);

	GARISBAWAH[playerid][9] = CreatePlayerTextDraw(playerid, 286.000, 226.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][9], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][9], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][9], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][9], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][9], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][9], 1);

	GARISBAWAH[playerid][10] = CreatePlayerTextDraw(playerid, 125.000, 282.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][10], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][10], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][10], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][10], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][10], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][10], 1);

	GARISBAWAH[playerid][11] = CreatePlayerTextDraw(playerid, 165.000, 282.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][11], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][11], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][11], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][11], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][11], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][11], 1);

	GARISBAWAH[playerid][12] = CreatePlayerTextDraw(playerid, 205.000, 282.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][12], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][12], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][12], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][12], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][12], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][12], 1);

	GARISBAWAH[playerid][13] = CreatePlayerTextDraw(playerid, 245.000, 282.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][13], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][13], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][13], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][13], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][13], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][13], 1);

	GARISBAWAH[playerid][14] = CreatePlayerTextDraw(playerid, 286.000, 282.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][14], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][14], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][14], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][14], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][14], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][14], 1);

	GARISBAWAH[playerid][15] = CreatePlayerTextDraw(playerid, 125.000, 338.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][15], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][15], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][15], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][15], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][15], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][15], 1);

	GARISBAWAH[playerid][16] = CreatePlayerTextDraw(playerid, 165.000, 338.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][16], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][16], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][16], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][16], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][16], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][16], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][16], 1);

	GARISBAWAH[playerid][17] = CreatePlayerTextDraw(playerid, 205.000, 338.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][17], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][17], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][17], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][17], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][17], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][17], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][17], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][17], 1);

	GARISBAWAH[playerid][18] = CreatePlayerTextDraw(playerid, 245.000, 338.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][18], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][18], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][18], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][18], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][18], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][18], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][18], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][18], 1);

	GARISBAWAH[playerid][19] = CreatePlayerTextDraw(playerid, 286.000, 338.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, GARISBAWAH[playerid][19], 39.000, 3.000);
	PlayerTextDrawAlignment(playerid, GARISBAWAH[playerid][19], 1);
	PlayerTextDrawColor(playerid, GARISBAWAH[playerid][19], 1097458175);
	PlayerTextDrawSetShadow(playerid, GARISBAWAH[playerid][19], 0);
	PlayerTextDrawSetOutline(playerid, GARISBAWAH[playerid][19], 0);
	PlayerTextDrawBackgroundColor(playerid, GARISBAWAH[playerid][19], 255);
	PlayerTextDrawFont(playerid, GARISBAWAH[playerid][19], 4);
	PlayerTextDrawSetProportional(playerid, GARISBAWAH[playerid][19], 1);

	INVNAME[playerid][0] = CreatePlayerTextDraw(playerid, 118.000, 96.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INVNAME[playerid][0], 213.000, 253.000);
	PlayerTextDrawAlignment(playerid, INVNAME[playerid][0], 1);
	PlayerTextDrawColor(playerid, INVNAME[playerid][0], 690964479);
	PlayerTextDrawSetShadow(playerid, INVNAME[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, INVNAME[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, INVNAME[playerid][0], 255);
	PlayerTextDrawFont(playerid, INVNAME[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, INVNAME[playerid][0], 1);

	INVNAME[playerid][1] = CreatePlayerTextDraw(playerid, 125.000, 115.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INVNAME[playerid][1], 199.000, 3.000);
	PlayerTextDrawAlignment(playerid, INVNAME[playerid][1], 1);
	PlayerTextDrawColor(playerid, INVNAME[playerid][1], 255);
	PlayerTextDrawSetShadow(playerid, INVNAME[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, INVNAME[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, INVNAME[playerid][1], 255);
	PlayerTextDrawFont(playerid, INVNAME[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, INVNAME[playerid][1], 1);

	INVNAME[playerid][2] = CreatePlayerTextDraw(playerid, 126.000, 115.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INVNAME[playerid][2], 165.000, 3.000);
	PlayerTextDrawAlignment(playerid, INVNAME[playerid][2], 1);
	PlayerTextDrawColor(playerid, INVNAME[playerid][2], 1097458175);
	PlayerTextDrawSetShadow(playerid, INVNAME[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, INVNAME[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, INVNAME[playerid][2], 255);
	PlayerTextDrawFont(playerid, INVNAME[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, INVNAME[playerid][2], 1);

	INVNAME[playerid][3] = CreatePlayerTextDraw(playerid, 126.000, 105.000, "Atsuko Tadashiu");
	PlayerTextDrawLetterSize(playerid, INVNAME[playerid][3], 0.140, 0.898);
	PlayerTextDrawAlignment(playerid, INVNAME[playerid][3], 1);
	PlayerTextDrawColor(playerid, INVNAME[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, INVNAME[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, INVNAME[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, INVNAME[playerid][3], 150);
	PlayerTextDrawFont(playerid, INVNAME[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, INVNAME[playerid][3], 1);

	INVNAME[playerid][4] = CreatePlayerTextDraw(playerid, 324.000, 105.000, "100/300");
	PlayerTextDrawLetterSize(playerid, INVNAME[playerid][4], 0.140, 0.699);
	PlayerTextDrawAlignment(playerid, INVNAME[playerid][4], 3);
	PlayerTextDrawColor(playerid, INVNAME[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, INVNAME[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, INVNAME[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, INVNAME[playerid][4], 150);
	PlayerTextDrawFont(playerid, INVNAME[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, INVNAME[playerid][4], 1);

	INVNAME[playerid][5] = CreatePlayerTextDraw(playerid, 295.000, 104.000, "H");
	PlayerTextDrawLetterSize(playerid, INVNAME[playerid][5], 0.200, 0.898);
	PlayerTextDrawAlignment(playerid, INVNAME[playerid][5], 3);
	PlayerTextDrawColor(playerid, INVNAME[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, INVNAME[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, INVNAME[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, INVNAME[playerid][5], 150);
	PlayerTextDrawFont(playerid, INVNAME[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, INVNAME[playerid][5], 1);

    INVINFO[playerid][0] = CreatePlayerTextDraw(playerid, 347.000, 168.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INVINFO[playerid][0], 55.000, 117.000);
	PlayerTextDrawAlignment(playerid, INVINFO[playerid][0], 1);
	PlayerTextDrawColor(playerid, INVINFO[playerid][0], 690964479);
	PlayerTextDrawSetShadow(playerid, INVINFO[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, INVINFO[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, INVINFO[playerid][0], 255);
	PlayerTextDrawFont(playerid, INVINFO[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, INVINFO[playerid][0], 1);

	INVINFO[playerid][1] = CreatePlayerTextDraw(playerid, 352.000, 174.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INVINFO[playerid][1], 45.000, 18.000);
	PlayerTextDrawAlignment(playerid, INVINFO[playerid][1], 1);
	PlayerTextDrawColor(playerid, INVINFO[playerid][1], 859394047);
	PlayerTextDrawSetShadow(playerid, INVINFO[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, INVINFO[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, INVINFO[playerid][1], 255);
	PlayerTextDrawFont(playerid, INVINFO[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, INVINFO[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, INVINFO[playerid][1], 1);

	INVINFO[playerid][2] = CreatePlayerTextDraw(playerid, 352.000, 195.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INVINFO[playerid][2], 45.000, 18.000);
	PlayerTextDrawAlignment(playerid, INVINFO[playerid][2], 1);
	PlayerTextDrawColor(playerid, INVINFO[playerid][2], 859394047);
	PlayerTextDrawSetShadow(playerid, INVINFO[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, INVINFO[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, INVINFO[playerid][2], 255);
	PlayerTextDrawFont(playerid, INVINFO[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, INVINFO[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, INVINFO[playerid][2], 1);

	INVINFO[playerid][3] = CreatePlayerTextDraw(playerid, 352.000, 216.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INVINFO[playerid][3], 45.000, 18.000);
	PlayerTextDrawAlignment(playerid, INVINFO[playerid][3], 1);
	PlayerTextDrawColor(playerid, INVINFO[playerid][3], 859394047);
	PlayerTextDrawSetShadow(playerid, INVINFO[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, INVINFO[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, INVINFO[playerid][3], 255);
	PlayerTextDrawFont(playerid, INVINFO[playerid][3], 4);
	PlayerTextDrawSetProportional(playerid, INVINFO[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, INVINFO[playerid][3], 1);

	INVINFO[playerid][4] = CreatePlayerTextDraw(playerid, 352.000, 237.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INVINFO[playerid][4], 45.000, 18.000);
	PlayerTextDrawAlignment(playerid, INVINFO[playerid][4], 1);
	PlayerTextDrawColor(playerid, INVINFO[playerid][4], 859394047);
	PlayerTextDrawSetShadow(playerid, INVINFO[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, INVINFO[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, INVINFO[playerid][4], 255);
	PlayerTextDrawFont(playerid, INVINFO[playerid][4], 4);
	PlayerTextDrawSetProportional(playerid, INVINFO[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, INVINFO[playerid][4], 1);

	INVINFO[playerid][5] = CreatePlayerTextDraw(playerid, 352.000, 258.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INVINFO[playerid][5], 45.000, 18.000);
	PlayerTextDrawAlignment(playerid, INVINFO[playerid][5], 1);
	PlayerTextDrawColor(playerid, INVINFO[playerid][5], 859394047);
	PlayerTextDrawSetShadow(playerid, INVINFO[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, INVINFO[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, INVINFO[playerid][5], 255);
	PlayerTextDrawFont(playerid, INVINFO[playerid][5], 4);
	PlayerTextDrawSetProportional(playerid, INVINFO[playerid][5], 1);
	PlayerTextDrawSetSelectable(playerid, INVINFO[playerid][5], 1);

	INVINFO[playerid][6] = CreatePlayerTextDraw(playerid, 375.000, 179.000, "Amount");
	PlayerTextDrawLetterSize(playerid, INVINFO[playerid][6], 0.150, 0.898);
	PlayerTextDrawAlignment(playerid, INVINFO[playerid][6], 2);
	PlayerTextDrawColor(playerid, INVINFO[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, INVINFO[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, INVINFO[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, INVINFO[playerid][6], 150);
	PlayerTextDrawFont(playerid, INVINFO[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, INVINFO[playerid][6], 1);

	INVINFO[playerid][7] = CreatePlayerTextDraw(playerid, 375.000, 199.000, "Use");
	PlayerTextDrawLetterSize(playerid, INVINFO[playerid][7], 0.150, 0.898);
	PlayerTextDrawAlignment(playerid, INVINFO[playerid][7], 2);
	PlayerTextDrawColor(playerid, INVINFO[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, INVINFO[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, INVINFO[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, INVINFO[playerid][7], 150);
	PlayerTextDrawFont(playerid, INVINFO[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, INVINFO[playerid][7], 1);

	INVINFO[playerid][8] = CreatePlayerTextDraw(playerid, 375.000, 220.000, "Give");
	PlayerTextDrawLetterSize(playerid, INVINFO[playerid][8], 0.150, 0.898);
	PlayerTextDrawAlignment(playerid, INVINFO[playerid][8], 2);
	PlayerTextDrawColor(playerid, INVINFO[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, INVINFO[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, INVINFO[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, INVINFO[playerid][8], 150);
	PlayerTextDrawFont(playerid, INVINFO[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, INVINFO[playerid][8], 1);

	INVINFO[playerid][9] = CreatePlayerTextDraw(playerid, 375.000, 242.000, "Drop");
	PlayerTextDrawLetterSize(playerid, INVINFO[playerid][9], 0.150, 0.898);
	PlayerTextDrawAlignment(playerid, INVINFO[playerid][9], 2);
	PlayerTextDrawColor(playerid, INVINFO[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, INVINFO[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, INVINFO[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, INVINFO[playerid][9], 150);
	PlayerTextDrawFont(playerid, INVINFO[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, INVINFO[playerid][9], 1);

	INVINFO[playerid][10] = CreatePlayerTextDraw(playerid, 375.000, 263.000, "Close");
	PlayerTextDrawLetterSize(playerid, INVINFO[playerid][10], 0.150, 0.898);
	PlayerTextDrawAlignment(playerid, INVINFO[playerid][10], 2);
	PlayerTextDrawColor(playerid, INVINFO[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, INVINFO[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, INVINFO[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, INVINFO[playerid][10], 150);
	PlayerTextDrawFont(playerid, INVINFO[playerid][10], 1);
	PlayerTextDrawSetProportional(playerid, INVINFO[playerid][10], 1);

	NAMETD[playerid][0] = CreatePlayerTextDraw(playerid, 128.000, 121.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][0], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][0], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][0], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][0], 1);

	NAMETD[playerid][1] = CreatePlayerTextDraw(playerid, 168.000, 121.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][1], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][1], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][1], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][1], 1);

	NAMETD[playerid][2] = CreatePlayerTextDraw(playerid, 208.000, 121.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][2], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][2], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][2], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][2], 1);

	NAMETD[playerid][3] = CreatePlayerTextDraw(playerid, 248.000, 121.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][3], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][3], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][3], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][3], 1);

	NAMETD[playerid][4] = CreatePlayerTextDraw(playerid, 287.000, 121.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][4], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][4], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][4], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][4], 1);

	NAMETD[playerid][5] = CreatePlayerTextDraw(playerid, 128.000, 176.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][5], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][5], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][5], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][5], 1);

	NAMETD[playerid][6] = CreatePlayerTextDraw(playerid, 168.000, 176.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][6], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][6], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][6], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][6], 1);

	NAMETD[playerid][7] = CreatePlayerTextDraw(playerid, 208.000, 176.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][7], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][7], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][7], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][7], 1);

	NAMETD[playerid][8] = CreatePlayerTextDraw(playerid, 248.000, 176.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][8], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][8], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][8], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][8], 1);

	NAMETD[playerid][9] = CreatePlayerTextDraw(playerid, 287.000, 176.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][9], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][9], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][9], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][9], 1);

	NAMETD[playerid][10] = CreatePlayerTextDraw(playerid, 128.000, 232.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][10], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][10], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][10], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][10], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][10], 1);

	NAMETD[playerid][11] = CreatePlayerTextDraw(playerid, 168.000, 232.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][11], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][11], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][11], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][11], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][11], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][11], 1);

	NAMETD[playerid][12] = CreatePlayerTextDraw(playerid, 208.000, 232.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][12], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][12], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][12], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][12], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][12], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][12], 1);

	NAMETD[playerid][13] = CreatePlayerTextDraw(playerid, 248.000, 232.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][13], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][13], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][13], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][13], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][13], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][13], 1);

	NAMETD[playerid][14] = CreatePlayerTextDraw(playerid, 287.000, 232.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][14], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][14], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][14], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][14], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][14], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][14], 1);

	NAMETD[playerid][15] = CreatePlayerTextDraw(playerid, 128.000, 287.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][15], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][15], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][15], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][15], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][15], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][15], 1);

	NAMETD[playerid][16] = CreatePlayerTextDraw(playerid, 168.000, 287.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][16], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][16], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][16], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][16], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][16], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][16], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][16], 1);

	NAMETD[playerid][17] = CreatePlayerTextDraw(playerid, 208.000, 287.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][17], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][17], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][17], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][17], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][17], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][17], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][17], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][17], 1);

	NAMETD[playerid][18] = CreatePlayerTextDraw(playerid, 248.000, 287.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][18], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][18], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][18], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][18], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][18], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][18], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][18], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][18], 1);

	NAMETD[playerid][19] = CreatePlayerTextDraw(playerid, 287.000, 287.000, "Uang");
	PlayerTextDrawLetterSize(playerid, NAMETD[playerid][19], 0.128, 0.699);
	PlayerTextDrawAlignment(playerid, NAMETD[playerid][19], 1);
	PlayerTextDrawColor(playerid, NAMETD[playerid][19], -1);
	PlayerTextDrawSetShadow(playerid, NAMETD[playerid][19], 0);
	PlayerTextDrawSetOutline(playerid, NAMETD[playerid][19], 0);
	PlayerTextDrawBackgroundColor(playerid, NAMETD[playerid][19], 150);
	PlayerTextDrawFont(playerid, NAMETD[playerid][19], 1);
	PlayerTextDrawSetProportional(playerid, NAMETD[playerid][19], 1);

	INDEXTD[playerid][0] = CreatePlayerTextDraw(playerid, 125.000, 120.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][0], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][0], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][0], 1);

	INDEXTD[playerid][1] = CreatePlayerTextDraw(playerid, 165.000, 120.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][1], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][1], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][1], 1);

	INDEXTD[playerid][2] = CreatePlayerTextDraw(playerid, 205.000, 120.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][2], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][2], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][2], 1);

	INDEXTD[playerid][3] = CreatePlayerTextDraw(playerid, 245.000, 120.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][3], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][3], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][3], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][3], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][3], 1);

	INDEXTD[playerid][4] = CreatePlayerTextDraw(playerid, 285.000, 120.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][4], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][4], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][4], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][4], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][4], 1);

	INDEXTD[playerid][5] = CreatePlayerTextDraw(playerid, 125.000, 176.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][5], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][5], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][5], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][5], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][5], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][5], 1);

	INDEXTD[playerid][6] = CreatePlayerTextDraw(playerid, 165.000, 176.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][6], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][6], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][6], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][6], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][6], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][6], 1);

	INDEXTD[playerid][7] = CreatePlayerTextDraw(playerid, 205.000, 176.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][7], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][7], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][7], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][7], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][7], 1);

	INDEXTD[playerid][8] = CreatePlayerTextDraw(playerid, 245.000, 176.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][8], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][8], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][8], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][8], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][8], 1);

	INDEXTD[playerid][9] = CreatePlayerTextDraw(playerid, 285.000, 176.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][9], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][9], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][9], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][9], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][9], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][9], 1);

	INDEXTD[playerid][10] = CreatePlayerTextDraw(playerid, 125.000, 232.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][10], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][10], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][10], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][10], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][10], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][10], 1);

	INDEXTD[playerid][11] = CreatePlayerTextDraw(playerid, 165.000, 232.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][11], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][11], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][11], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][11], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][11], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][11], 1);

	INDEXTD[playerid][12] = CreatePlayerTextDraw(playerid, 205.000, 232.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][12], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][12], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][12], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][12], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][12], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][12], 1);

	INDEXTD[playerid][13] = CreatePlayerTextDraw(playerid, 245.000, 232.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][13], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][13], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][13], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][13], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][13], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][13], 1);

	INDEXTD[playerid][14] = CreatePlayerTextDraw(playerid, 285.000, 232.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][14], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][14], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][14], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][14], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][14], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][14], 1);

	INDEXTD[playerid][15] = CreatePlayerTextDraw(playerid, 125.000, 288.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][15], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][15], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][15], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][15], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][15], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][15], 1);

	INDEXTD[playerid][16] = CreatePlayerTextDraw(playerid, 165.000, 288.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][16], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][16], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][16], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][16], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][16], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][16], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][16], 1);

	INDEXTD[playerid][17] = CreatePlayerTextDraw(playerid, 205.000, 288.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][17], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][17], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][17], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][17], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][17], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][17], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][17], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][17], 1);

	INDEXTD[playerid][18] = CreatePlayerTextDraw(playerid, 245.000, 288.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][18], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][18], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][18], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][18], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][18], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][18], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][18], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][18], 1);

	INDEXTD[playerid][19] = CreatePlayerTextDraw(playerid, 285.000, 288.000, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, INDEXTD[playerid][19], 39.000, 51.000);
	PlayerTextDrawAlignment(playerid, INDEXTD[playerid][19], 1);
	PlayerTextDrawColor(playerid, INDEXTD[playerid][19], 859394047);
	PlayerTextDrawSetShadow(playerid, INDEXTD[playerid][19], 0);
	PlayerTextDrawSetOutline(playerid, INDEXTD[playerid][19], 0);
	PlayerTextDrawBackgroundColor(playerid, INDEXTD[playerid][19], 255);
	PlayerTextDrawFont(playerid, INDEXTD[playerid][19], 4);
	PlayerTextDrawSetProportional(playerid, INDEXTD[playerid][19], 1);

	MODELTD[playerid][0] = CreatePlayerTextDraw(playerid, 129.000, 129.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][0], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][0], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][0], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][0], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][0], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][0], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][0], 1);

	MODELTD[playerid][1] = CreatePlayerTextDraw(playerid, 169.000, 129.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][1], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][1], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][1], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][1], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][1], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][1], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][1], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][1], 1);

	MODELTD[playerid][2] = CreatePlayerTextDraw(playerid, 209.000, 129.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][2], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][2], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][2], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][2], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][2], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][2], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][2], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][2], 1);

	MODELTD[playerid][3] = CreatePlayerTextDraw(playerid, 249.000, 129.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][3], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][3], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][3], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][3], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][3], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][3], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][3], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][3], 1);

	MODELTD[playerid][4] = CreatePlayerTextDraw(playerid, 289.000, 129.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][4], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][4], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][4], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][4], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][4], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][4], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][4], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][4], 1);

	MODELTD[playerid][5] = CreatePlayerTextDraw(playerid, 129.000, 185.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][5], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][5], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][5], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][5], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][5], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][5], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][5], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][5], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][5], 1);

	MODELTD[playerid][6] = CreatePlayerTextDraw(playerid, 169.000, 185.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][6], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][6], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][6], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][6], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][6], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][6], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][6], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][6], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][6], 1);

	MODELTD[playerid][7] = CreatePlayerTextDraw(playerid, 209.000, 185.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][7], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][7], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][7], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][7], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][7], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][7], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][7], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][7], 1);

	MODELTD[playerid][8] = CreatePlayerTextDraw(playerid, 249.000, 185.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][8], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][8], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][8], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][8], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][8], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][8], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][8], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][8], 1);

	MODELTD[playerid][9] = CreatePlayerTextDraw(playerid, 289.000, 185.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][9], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][9], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][9], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][9], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][9], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][9], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][9], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][9], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][9], 1);

	MODELTD[playerid][10] = CreatePlayerTextDraw(playerid, 129.000, 241.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][10], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][10], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][10], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][10], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][10], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][10], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][10], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][10], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][10], 1);

	MODELTD[playerid][11] = CreatePlayerTextDraw(playerid, 169.000, 241.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][11], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][11], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][11], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][11], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][11], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][11], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][11], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][11], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][11], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][11], 1);

	MODELTD[playerid][12] = CreatePlayerTextDraw(playerid, 209.000, 241.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][12], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][12], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][12], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][12], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][12], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][12], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][12], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][12], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][12], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][12], 1);

	MODELTD[playerid][13] = CreatePlayerTextDraw(playerid, 249.000, 241.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][13], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][13], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][13], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][13], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][13], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][13], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][13], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][13], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][13], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][13], 1);

	MODELTD[playerid][14] = CreatePlayerTextDraw(playerid, 289.000, 241.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][14], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][14], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][14], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][14], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][14], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][14], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][14], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][14], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][14], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][14], 1);

	MODELTD[playerid][15] = CreatePlayerTextDraw(playerid, 129.000, 297.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][15], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][15], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][15], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][15], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][15], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][15], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][15], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][15], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][15], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][15], 1);

	MODELTD[playerid][16] = CreatePlayerTextDraw(playerid, 169.000, 297.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][16], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][16], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][16], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][16], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][16], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][16], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][16], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][16], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][16], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][16], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][16], 1);

	MODELTD[playerid][17] = CreatePlayerTextDraw(playerid, 209.000, 297.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][17], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][17], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][17], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][17], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][17], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][17], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][17], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][17], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][17], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][17], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][17], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][17], 1);

	MODELTD[playerid][18] = CreatePlayerTextDraw(playerid, 249.000, 297.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][18], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][18], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][18], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][18], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][18], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][18], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][18], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][18], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][18], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][18], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][18], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][18], 1);

	MODELTD[playerid][19] = CreatePlayerTextDraw(playerid, 289.000, 297.000, "_");
	PlayerTextDrawTextSize(playerid, MODELTD[playerid][19], 30.000, 35.000);
	PlayerTextDrawAlignment(playerid, MODELTD[playerid][19], 1);
	PlayerTextDrawColor(playerid, MODELTD[playerid][19], -1);
	PlayerTextDrawSetShadow(playerid, MODELTD[playerid][19], 0);
	PlayerTextDrawSetOutline(playerid, MODELTD[playerid][19], 0);
	PlayerTextDrawBackgroundColor(playerid, MODELTD[playerid][19], 0);
	PlayerTextDrawFont(playerid, MODELTD[playerid][19], 5);
	PlayerTextDrawSetProportional(playerid, MODELTD[playerid][19], 0);
	PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][19], 1212);
	PlayerTextDrawSetPreviewRot(playerid, MODELTD[playerid][19], 0.000, 0.000, 0.000, 1.000);
	PlayerTextDrawSetPreviewVehCol(playerid, MODELTD[playerid][19], 0, 0);
	PlayerTextDrawSetSelectable(playerid, MODELTD[playerid][19], 1);

	AMOUNTTD[playerid][0] = CreatePlayerTextDraw(playerid, 126.000, 162.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][0], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][0], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][0], 1);

	AMOUNTTD[playerid][1] = CreatePlayerTextDraw(playerid, 166.000, 162.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][1], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][1], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][1], 1);

	AMOUNTTD[playerid][2] = CreatePlayerTextDraw(playerid, 206.000, 162.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][2], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][2], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][2], 1);

	AMOUNTTD[playerid][3] = CreatePlayerTextDraw(playerid, 246.000, 162.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][3], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][3], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][3], 1);

	AMOUNTTD[playerid][4] = CreatePlayerTextDraw(playerid, 286.000, 162.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][4], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][4], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][4], 1);

	AMOUNTTD[playerid][5] = CreatePlayerTextDraw(playerid, 126.000, 218.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][5], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][5], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][5], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][5], 1);

	AMOUNTTD[playerid][6] = CreatePlayerTextDraw(playerid, 166.000, 218.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][6], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][6], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][6], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][6], 1);

	AMOUNTTD[playerid][7] = CreatePlayerTextDraw(playerid, 206.000, 218.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][7], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][7], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][7], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][7], 1);

	AMOUNTTD[playerid][8] = CreatePlayerTextDraw(playerid, 246.000, 218.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][8], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][8], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][8], 1);

	AMOUNTTD[playerid][9] = CreatePlayerTextDraw(playerid, 286.000, 218.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][9], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][9], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][9], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][9], 1);

	AMOUNTTD[playerid][10] = CreatePlayerTextDraw(playerid, 126.000, 274.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][10], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][10], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][10], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][10], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][10], 1);

	AMOUNTTD[playerid][11] = CreatePlayerTextDraw(playerid, 166.000, 274.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][11], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][11], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][11], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][11], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][11], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][11], 1);

	AMOUNTTD[playerid][12] = CreatePlayerTextDraw(playerid, 206.000, 274.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][12], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][12], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][12], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][12], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][12], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][12], 1);

	AMOUNTTD[playerid][13] = CreatePlayerTextDraw(playerid, 246.000, 274.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][13], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][13], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][13], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][13], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][13], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][13], 1);

	AMOUNTTD[playerid][14] = CreatePlayerTextDraw(playerid, 286.000, 274.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][14], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][14], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][14], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][14], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][14], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][14], 1);

	AMOUNTTD[playerid][15] = CreatePlayerTextDraw(playerid, 126.000, 330.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][15], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][15], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][15], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][15], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][15], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][15], 1);

	AMOUNTTD[playerid][16] = CreatePlayerTextDraw(playerid, 166.000, 330.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][16], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][16], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][16], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][16], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][16], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][16], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][16], 1);

	AMOUNTTD[playerid][17] = CreatePlayerTextDraw(playerid, 206.000, 330.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][17], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][17], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][17], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][17], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][17], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][17], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][17], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][17], 1);

	AMOUNTTD[playerid][18] = CreatePlayerTextDraw(playerid, 246.000, 330.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][18], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][18], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][18], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][18], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][18], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][18], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][18], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][18], 1);

	AMOUNTTD[playerid][19] = CreatePlayerTextDraw(playerid, 286.000, 330.000, "10000x");
	PlayerTextDrawLetterSize(playerid, AMOUNTTD[playerid][19], 0.119, 0.598);
	PlayerTextDrawAlignment(playerid, AMOUNTTD[playerid][19], 1);
	PlayerTextDrawColor(playerid, AMOUNTTD[playerid][19], -1);
	PlayerTextDrawSetShadow(playerid, AMOUNTTD[playerid][19], 0);
	PlayerTextDrawSetOutline(playerid, AMOUNTTD[playerid][19], 0);
	PlayerTextDrawBackgroundColor(playerid, AMOUNTTD[playerid][19], 150);
	PlayerTextDrawFont(playerid, AMOUNTTD[playerid][19], 1);
	PlayerTextDrawSetProportional(playerid, AMOUNTTD[playerid][19], 1);

	NOTIFBOX[playerid][0] = CreatePlayerTextDraw(playerid, 391.000000, 347.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, NOTIFBOX[playerid][0], 4);
	PlayerTextDrawLetterSize(playerid, NOTIFBOX[playerid][0], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, NOTIFBOX[playerid][0], 43.500000, 47.000000);
	PlayerTextDrawSetOutline(playerid, NOTIFBOX[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, NOTIFBOX[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, NOTIFBOX[playerid][0], 1);
	PlayerTextDrawColor(playerid, NOTIFBOX[playerid][0], 859394047);// TANDA
	PlayerTextDrawBackgroundColor(playerid, NOTIFBOX[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, NOTIFBOX[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, NOTIFBOX[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, NOTIFBOX[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, NOTIFBOX[playerid][0], 0);

	NOTIFBOX[playerid][1] = CreatePlayerTextDraw(playerid, 391.000000, 347.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, NOTIFBOX[playerid][1], 4);
	PlayerTextDrawLetterSize(playerid, NOTIFBOX[playerid][1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, NOTIFBOX[playerid][1], 43.500000, 47.000000);
	PlayerTextDrawSetOutline(playerid, NOTIFBOX[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, NOTIFBOX[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, NOTIFBOX[playerid][1], 1);
	PlayerTextDrawColor(playerid, NOTIFBOX[playerid][1], 1296911871);
	PlayerTextDrawBackgroundColor(playerid, NOTIFBOX[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, NOTIFBOX[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, NOTIFBOX[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, NOTIFBOX[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, NOTIFBOX[playerid][1], 0);

	NOTIFBOX[playerid][2] = CreatePlayerTextDraw(playerid, 391.000000, 347.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, NOTIFBOX[playerid][2], 4);
	PlayerTextDrawLetterSize(playerid, NOTIFBOX[playerid][2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, NOTIFBOX[playerid][2], 1.500000, 47.000000);
	PlayerTextDrawSetOutline(playerid, NOTIFBOX[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, NOTIFBOX[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, NOTIFBOX[playerid][2], 1);
	PlayerTextDrawColor(playerid, NOTIFBOX[playerid][2], 1687547391);
	PlayerTextDrawBackgroundColor(playerid, NOTIFBOX[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, NOTIFBOX[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, NOTIFBOX[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, NOTIFBOX[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, NOTIFBOX[playerid][2], 0);

	NOTIFBOX[playerid][3] = CreatePlayerTextDraw(playerid, 394.000000, 386.000000, "NASI GORENG");
	PlayerTextDrawFont(playerid, NOTIFBOX[playerid][3], 1);
	PlayerTextDrawLetterSize(playerid, NOTIFBOX[playerid][3], 0.150000, 0.800000);
	PlayerTextDrawTextSize(playerid, NOTIFBOX[playerid][3], 494.500000, 98.500000);
	PlayerTextDrawSetOutline(playerid, NOTIFBOX[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, NOTIFBOX[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, NOTIFBOX[playerid][3], 1);
	PlayerTextDrawColor(playerid, NOTIFBOX[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, NOTIFBOX[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, NOTIFBOX[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, NOTIFBOX[playerid][3], 0);
	PlayerTextDrawSetProportional(playerid, NOTIFBOX[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, NOTIFBOX[playerid][3], 0);

	NOTIFBOX[playerid][4] = CreatePlayerTextDraw(playerid, 394.000000, 347.000000, "1X");
	PlayerTextDrawFont(playerid, NOTIFBOX[playerid][4], 1);
	PlayerTextDrawLetterSize(playerid, NOTIFBOX[playerid][4], 0.150000, 0.800000);
	PlayerTextDrawTextSize(playerid, NOTIFBOX[playerid][4], 494.500000, 98.500000);
	PlayerTextDrawSetOutline(playerid, NOTIFBOX[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, NOTIFBOX[playerid][4], 0);
	PlayerTextDrawAlignment(playerid, NOTIFBOX[playerid][4], 1);
	PlayerTextDrawColor(playerid, NOTIFBOX[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, NOTIFBOX[playerid][4], 255);
	PlayerTextDrawBoxColor(playerid, NOTIFBOX[playerid][4], 50);
	PlayerTextDrawUseBox(playerid, NOTIFBOX[playerid][4], 0);
	PlayerTextDrawSetProportional(playerid, NOTIFBOX[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, NOTIFBOX[playerid][4], 0);

	NOTIFBOX[playerid][5] = CreatePlayerTextDraw(playerid, 394.000000, 350.000000, "Preview_Model");
	PlayerTextDrawFont(playerid, NOTIFBOX[playerid][5], 5);
	PlayerTextDrawLetterSize(playerid, NOTIFBOX[playerid][5], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, NOTIFBOX[playerid][5], 35.000000, 38.000000);
	PlayerTextDrawSetOutline(playerid, NOTIFBOX[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, NOTIFBOX[playerid][5], 0);
	PlayerTextDrawAlignment(playerid, NOTIFBOX[playerid][5], 1);
	PlayerTextDrawColor(playerid, NOTIFBOX[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, NOTIFBOX[playerid][5], 0);
	PlayerTextDrawBoxColor(playerid, NOTIFBOX[playerid][5], 255);
	PlayerTextDrawUseBox(playerid, NOTIFBOX[playerid][5], 0);
	PlayerTextDrawSetProportional(playerid, NOTIFBOX[playerid][5], 1);
	PlayerTextDrawSetSelectable(playerid, NOTIFBOX[playerid][5], 0);
	PlayerTextDrawSetPreviewModel(playerid, NOTIFBOX[playerid][5], 1212);
	PlayerTextDrawSetPreviewRot(playerid, NOTIFBOX[playerid][5], -10.000000, 0.000000, -20.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, NOTIFBOX[playerid][5], 1, 1);
	return 1;
}

// ==========================================
// KUMPULAN FUNGSI CORE INVENTORY
// ==========================================

// Fungsi untuk mengecek slot kosong di inventory
stock Inventory_GetFreeID(playerid)
{
    for (new i = 0; i < MAX_INVENTORY; i ++)
    {
        if (!InventoryData[playerid][i][invExists])
            return i;
    }
    return -1;
}

// Fungsi untuk mengecek apakah item sudah ada di inventory atau belum
stock Inventory_GetItemID(playerid, item[])
{
    for (new i = 0; i < MAX_INVENTORY; i ++)
    {
        if (InventoryData[playerid][i][invExists])
        {
            new string[32];
            strunpack(string, InventoryData[playerid][i][invItem]);

            if (!strcmp(item, string, true))
                return i;
        }
    }
    return -1;
}

// Fungsi untuk menghapus tampilan layar inventory sementara
stock Inventory_Clear(playerid)
{
    for(new i = 0; i < MAX_INVENTORY; i++)
    {
        if (InventoryData[playerid][i][invExists])
        {
            InventoryData[playerid][i][invExists] = 0;
            InventoryData[playerid][i][invModel] = 0;
            InventoryData[playerid][i][invAmount] = 0;
        }
    }
    return 1;
}

// Fungsi untuk merakit data menjadi gambar dan teks di Inventory
stock Inventory_Addset(playerid, item[], model, amount = 1)
{
    new itemid = Inventory_GetItemID(playerid, item);

    if (itemid == -1) // Jika item belum ada, buat slot baru
    {
        itemid = Inventory_GetFreeID(playerid);

        if (itemid != -1)
        {
            InventoryData[playerid][itemid][invExists] = 1;
            InventoryData[playerid][itemid][invModel] = model;
            InventoryData[playerid][itemid][invAmount] = amount;

            strpack(InventoryData[playerid][itemid][invItem], item, 32 char);
            return itemid;
        }
        return -1;
    }
    else // Jika item sudah ada, tinggal tambahkan jumlahnya (ditumpuk/stack)
    {
        InventoryData[playerid][itemid][invAmount] += amount;
    }
    return itemid;
}

CMD:inventory(playerid, params[])
{
    Inventory_Show(playerid); // Fungsi ini yg nantinya manggil BarangMasuk()
    SelectTextDraw(playerid, 0x00FF00FF); // Munculin kursor mouse
    return 1;
}

Dialog:InvDropItem(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		DeletePVar(playerid, "DropItem"); // Hapus memori jika klik Batal
		return 1;
	}
	
	new amount = strval(inputtext); // Membaca angka yang dimasukkan player
	if(amount < 1) return Error(playerid, "Jumlah tidak valid!");
	
	new name[32];
	GetPVarString(playerid, "DropItem", name, sizeof(name)); // Mengambil nama item dari memori
	
	// ===============================================
	// LOGIKA PENGURANGAN PDATA BERDASARKAN NAMA ITEM
	// ===============================================
    
    // === MAKANAN, MINUMAN & MEDIS ===
    if(!strcmp(name, "Snack", true)) {
        if(pData[playerid][pSnack] < amount) return Error(playerid, "Snack Anda tidak cukup!");
        pData[playerid][pSnack] -= amount;
    }
    else if(!strcmp(name, "Sprunk", true)) {
        if(pData[playerid][pSprunk] < amount) return Error(playerid, "Sprunk Anda tidak cukup!");
        pData[playerid][pSprunk] -= amount;
    }
    else if(!strcmp(name, "Food", true)) {
        if(pData[playerid][pFood] < amount) return Error(playerid, "Food Anda tidak cukup!");
        pData[playerid][pFood] -= amount;
    }
    else if(!strcmp(name, "Cigarettes", true)) {
        if(pData[playerid][pRokok] < amount) return Error(playerid, "Rokok Anda tidak cukup!");
        pData[playerid][pRokok] -= amount;
    }
    else if(!strcmp(name, "Bandage", true)) {
        if(pData[playerid][pBandage] < amount) return Error(playerid, "Perban Anda tidak cukup!");
        pData[playerid][pBandage] -= amount;
    }
    else if(!strcmp(name, "Medicine", true)) {
        if(pData[playerid][pMedicine] < amount) return Error(playerid, "Medicine Anda tidak cukup!");
        pData[playerid][pMedicine] -= amount;
    }
    else if(!strcmp(name, "Medkit", true)) {
        if(pData[playerid][pMedkit] < amount) return Error(playerid, "Medkit Anda tidak cukup!");
        pData[playerid][pMedkit] -= amount;
    }

    // === OBAT-OBATAN (PILLS) ===
    else if(!strcmp(name, "Neladryl", true)) {
        if(pData[playerid][pCoughPills] < amount) return Error(playerid, "Pil Neladryl Anda tidak cukup!");
        pData[playerid][pCoughPills] -= amount;
    }
    else if(!strcmp(name, "Kratotamax", true)) {
        if(pData[playerid][pMigrainPills] < amount) return Error(playerid, "Pil Kratotamax Anda tidak cukup!");
        pData[playerid][pMigrainPills] -= amount;
    }
    else if(!strcmp(name, "Lazattavitus", true)) {
        if(pData[playerid][pFiverPills] < amount) return Error(playerid, "Pil Lazattavitus Anda tidak cukup!");
        pData[playerid][pFiverPills] -= amount;
    }

    // === ILLEGAL & MATERIAL ===
    else if(!strcmp(name, "Crack", true)) {
        if(pData[playerid][pCrack] < amount) return Error(playerid, "Crack Anda tidak cukup!");
        pData[playerid][pCrack] -= amount;
    }
    else if(!strcmp(name, "Pot", true)) {
        if(pData[playerid][pPot] < amount) return Error(playerid, "Pot Anda tidak cukup!");
        pData[playerid][pPot] -= amount;
    }
    else if(!strcmp(name, "Material", true)) {
        if(pData[playerid][pMaterial] < amount) return Error(playerid, "Material Anda tidak cukup!");
        pData[playerid][pMaterial] -= amount;
    }
    else if(!strcmp(name, "Component", true)) {
        if(pData[playerid][pComponent] < amount) return Error(playerid, "Component Anda tidak cukup!");
        pData[playerid][pComponent] -= amount;
    }

    // === TOOLS & MISC ===
    else if(!strcmp(name, "Fish pole", true)) {
        if(pData[playerid][pFishTool] < amount) return Error(playerid, "Fish Pole (Use) Anda tidak cukup!");
        pData[playerid][pFishTool] -= amount;
    }
    else if(!strcmp(name, "Bait", true)) {
        if(pData[playerid][pWorm] < amount) return Error(playerid, "Umpan Anda tidak cukup!");
        pData[playerid][pWorm] -= amount;
    }
    else if(!strcmp(name, "Toll Card", true)) {
        if(pData[playerid][pPayToll] < amount) return Error(playerid, "Toll Card Anda tidak cukup!");
        pData[playerid][pPayToll] -= amount;
    }

    // === FARMING (SEEDS) ===
    else if(!strcmp(name, "Wheat Seed", true)) {
        if(pData[playerid][pSeedWheat] < amount) return Error(playerid, "Bibit Wheat Anda tidak cukup!");
        pData[playerid][pSeedWheat] -= amount;
    }
    else if(!strcmp(name, "Onion Seed", true)) {
        if(pData[playerid][pSeedOnion] < amount) return Error(playerid, "Bibit Onion Anda tidak cukup!");
        pData[playerid][pSeedOnion] -= amount;
    }
    else if(!strcmp(name, "Carrot Seed", true)) {
        if(pData[playerid][pSeedCarrot] < amount) return Error(playerid, "Bibit Carrot Anda tidak cukup!");
        pData[playerid][pSeedCarrot] -= amount;
    }
    else if(!strcmp(name, "Potato Seed", true)) {
        if(pData[playerid][pSeedPotato] < amount) return Error(playerid, "Bibit Potato Anda tidak cukup!");
        pData[playerid][pSeedPotato] -= amount;
    }
    else if(!strcmp(name, "Corn Seed", true)) {
        if(pData[playerid][pSeedCorn] < amount) return Error(playerid, "Bibit Corn Anda tidak cukup!");
        pData[playerid][pSeedCorn] -= amount;
    }

    // === FARMING (PLANTS/HASIL PANEN) ===
    else if(!strcmp(name, "Wheat", true)) {
        if(pData[playerid][pWheat] < amount) return Error(playerid, "Wheat Anda tidak cukup!");
        pData[playerid][pWheat] -= amount;
    }
    else if(!strcmp(name, "Onion", true)) {
        if(pData[playerid][pOnion] < amount) return Error(playerid, "Onion Anda tidak cukup!");
        pData[playerid][pOnion] -= amount;
    }
    else if(!strcmp(name, "Carrot", true)) {
        if(pData[playerid][pCarrot] < amount) return Error(playerid, "Carrot Anda tidak cukup!");
        pData[playerid][pCarrot] -= amount;
    }
    else if(!strcmp(name, "Potato", true)) {
        if(pData[playerid][pPotato] < amount) return Error(playerid, "Potato Anda tidak cukup!");
        pData[playerid][pPotato] -= amount;
    }
    else if(!strcmp(name, "Corn", true)) {
        if(pData[playerid][pCorn] < amount) return Error(playerid, "Corn Anda tidak cukup!");
        pData[playerid][pCorn] -= amount;
    }
    else if(!strcmp(name, "Wild Berries", true)) {
        if(pData[playerid][pBushForager] < amount) return Error(playerid, "Wild Berries Anda tidak cukup!");
        pData[playerid][pBushForager] -= amount;
    }

    // === SCHEMATICS (BLUEPRINT SENJATA) ===
    else if(!strcmp(name, "Sch: Rifle", true)) {
        if(pData[playerid][pSchematic][0] < amount) return Error(playerid, "Schematic Anda tidak cukup!");
        pData[playerid][pSchematic][0] -= amount;
    }
    else if(!strcmp(name, "Sch: Shotgun", true)) {
        if(pData[playerid][pSchematic][1] < amount) return Error(playerid, "Schematic Anda tidak cukup!");
        pData[playerid][pSchematic][1] -= amount;
    }
    else if(!strcmp(name, "Sch: Sawn", true)) {
        if(pData[playerid][pSchematic][2] < amount) return Error(playerid, "Schematic Anda tidak cukup!");
        pData[playerid][pSchematic][2] -= amount;
    }
    else if(!strcmp(name, "Sch: Deagle", true)) {
        if(pData[playerid][pSchematic][3] < amount) return Error(playerid, "Schematic Anda tidak cukup!");
        pData[playerid][pSchematic][3] -= amount;
    }
    else if(!strcmp(name, "Sch: MP-5", true)) {
        if(pData[playerid][pSchematic][4] < amount) return Error(playerid, "Schematic Anda tidak cukup!");
        pData[playerid][pSchematic][4] -= amount;
    }
    else if(!strcmp(name, "Sch: AK-47", true)) {
        if(pData[playerid][pSchematic][5] < amount) return Error(playerid, "Schematic Anda tidak cukup!");
        pData[playerid][pSchematic][5] -= amount;
    }

    else
    {
        // Jika item benar-benar tidak terdaftar
        Error(playerid, "Item '%s' tidak dapat di-drop!", name);
        DeletePVar(playerid, "DropItem");
        return 1;
    }

    // Pesan sukses universal biar hemat baris kode
    SendClientMessageEx(playerid, COLOR_ARWIN, "DROP: {FFFFFF}Anda membuang %d %s.", amount, name);
	
	// Panggil fungsi pembuat object di lantai
    if(!CreateDropItem(playerid, name, amount))
    {
        // Jika slot drop item penuh, batalkan dan kembalikan barangnya ke player
        Error(playerid, "Terlalu banyak barang di lantai server! Barang Anda dikembalikan.");
        
        // ===============================================
        // REFUND BARANG KEMBALI KE PDATA
        // ===============================================
        if(!strcmp(name, "Snack", true)) pData[playerid][pSnack] += amount;
        else if(!strcmp(name, "Sprunk", true)) pData[playerid][pSprunk] += amount;
        else if(!strcmp(name, "Food", true)) pData[playerid][pFood] += amount;
        else if(!strcmp(name, "Cigarettes", true)) pData[playerid][pRokok] += amount;
        else if(!strcmp(name, "Bandage", true)) pData[playerid][pBandage] += amount;
        else if(!strcmp(name, "Medicine", true)) pData[playerid][pMedicine] += amount;
        else if(!strcmp(name, "Medkit", true)) pData[playerid][pMedkit] += amount;
        
        else if(!strcmp(name, "Neladryl", true)) pData[playerid][pCoughPills] += amount;
        else if(!strcmp(name, "Kratotamax", true)) pData[playerid][pMigrainPills] += amount;
        else if(!strcmp(name, "Lazattavitus", true)) pData[playerid][pFiverPills] += amount;
        
        else if(!strcmp(name, "Crack", true)) pData[playerid][pCrack] += amount;
        else if(!strcmp(name, "Pot", true)) pData[playerid][pPot] += amount;
        else if(!strcmp(name, "Material", true)) pData[playerid][pMaterial] += amount;
        else if(!strcmp(name, "Component", true)) pData[playerid][pComponent] += amount;
        
        else if(!strcmp(name, "Fish pole", true)) pData[playerid][pFishTool] += amount;
        else if(!strcmp(name, "Bait", true)) pData[playerid][pWorm] += amount;
        else if(!strcmp(name, "Toll Card", true)) pData[playerid][pPayToll] += amount;
        
        else if(!strcmp(name, "Wheat Seed", true)) pData[playerid][pSeedWheat] += amount;
        else if(!strcmp(name, "Onion Seed", true)) pData[playerid][pSeedOnion] += amount;
        else if(!strcmp(name, "Carrot Seed", true)) pData[playerid][pSeedCarrot] += amount;
        else if(!strcmp(name, "Potato Seed", true)) pData[playerid][pSeedPotato] += amount;
        else if(!strcmp(name, "Corn Seed", true)) pData[playerid][pSeedCorn] += amount;
        
        else if(!strcmp(name, "Wheat", true)) pData[playerid][pWheat] += amount;
        else if(!strcmp(name, "Onion", true)) pData[playerid][pOnion] += amount;
        else if(!strcmp(name, "Carrot", true)) pData[playerid][pCarrot] += amount;
        else if(!strcmp(name, "Potato", true)) pData[playerid][pPotato] += amount;
        else if(!strcmp(name, "Corn", true)) pData[playerid][pCorn] += amount;
        else if(!strcmp(name, "Wild Berries", true)) pData[playerid][pBushForager] += amount;
        
        else if(!strcmp(name, "Sch: Rifle", true)) pData[playerid][pSchematic][0] += amount;
        else if(!strcmp(name, "Sch: Shotgun", true)) pData[playerid][pSchematic][1] += amount;
        else if(!strcmp(name, "Sch: Sawn", true)) pData[playerid][pSchematic][2] += amount;
        else if(!strcmp(name, "Sch: Deagle", true)) pData[playerid][pSchematic][3] += amount;
        else if(!strcmp(name, "Sch: MP-5", true)) pData[playerid][pSchematic][4] += amount;
        else if(!strcmp(name, "Sch: AK-47", true)) pData[playerid][pSchematic][5] += amount;

        // Hapus memori sementara PVar agar bersih
        DeletePVar(playerid, "DropItem");
        return 1;
    }

	// Animasi membungkuk/membuang barang ke lantai
	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
	
	// Hapus memori sementara PVar
	DeletePVar(playerid, "DropItem");

	Inventory_Close(playerid); // Tutup inventory setelah drop
	return 1;
}
// ==========================================
// DIALOG 1: MENANGKAP ID PLAYER TARGET
// ==========================================
Dialog:InvGiveItem(playerid, response, listitem, inputtext[])
{
	if(!response) return DeletePVar(playerid, "GiveItem"), 1; // Hapus memori jika klik batal

	new targetid = strval(inputtext);

	// Validasi Target
	if(!IsPlayerConnected(targetid) || targetid == INVALID_PLAYER_ID)
		return Error(playerid, "Player tersebut tidak ditemukan/offline!"), DeletePVar(playerid, "GiveItem"), 1;

	if(targetid == playerid)
		return Error(playerid, "Anda tidak bisa memberikan barang ke diri sendiri!"), DeletePVar(playerid, "GiveItem"), 1;

	// Validasi Jarak (Harus berdekatan)
	new Float:x, Float:y, Float:z;
	GetPlayerPos(targetid, x, y, z);
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z) || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(targetid))
		return Error(playerid, "Player tersebut tidak berada di dekat Anda!"), DeletePVar(playerid, "GiveItem"), 1;

	// Simpan ID Target ke memori, lalu panggil Dialog 2
	SetPVarInt(playerid, "GiveTarget", targetid);
	
	new name[32], str[256];
	GetPVarString(playerid, "GiveItem", name, sizeof(name));
	format(str, sizeof(str), "Item: %s\nTarget: %s (ID: %d)\n\nMasukkan jumlah yang ingin Anda berikan:", name, ReturnName(targetid), targetid);
	Dialog_Show(playerid, InvGiveAmount, DIALOG_STYLE_INPUT, "Give Item - Jumlah", str, "Berikan", "Batal");
	
	return 1;
}

// ==========================================
// DIALOG 2: MENANGKAP JUMLAH & PROSES TRANSFER
// ==========================================
Dialog:InvGiveAmount(playerid, response, listitem, inputtext[])
{
	// Bersihkan semua memori jika batal
	if(!response) return DeletePVar(playerid, "GiveItem"), DeletePVar(playerid, "GiveTarget"), 1;

	new amount = strval(inputtext);
	if(amount < 1) return Error(playerid, "Jumlah tidak valid!"), DeletePVar(playerid, "GiveItem"), DeletePVar(playerid, "GiveTarget"), 1;

	new targetid = GetPVarInt(playerid, "GiveTarget");
	new name[32];
	GetPVarString(playerid, "GiveItem", name, sizeof(name));

	// Validasi ulang: Jaga-jaga target nge-disconnect atau lari saat dialog sedang terbuka
	if(!IsPlayerConnected(targetid))
		return Error(playerid, "Player target sudah disconnect!"), DeletePVar(playerid, "GiveItem"), DeletePVar(playerid, "GiveTarget"), 1;

	new Float:x, Float:y, Float:z;
	GetPlayerPos(targetid, x, y, z);
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z))
		return Error(playerid, "Player tersebut sudah menjauh dari Anda!"), DeletePVar(playerid, "GiveItem"), DeletePVar(playerid, "GiveTarget"), 1;

	// ===============================================
	// LOGIKA PENGURANGAN DAN PENAMBAHAN PDATA
	// ===============================================
	new bool:sukses = false;

	if(!strcmp(name, "Snack", true)) {
		if(pData[playerid][pSnack] < amount) return Error(playerid, "Snack Anda tidak cukup!");
		pData[playerid][pSnack] -= amount; pData[targetid][pSnack] += amount; sukses = true;
	}
	else if(!strcmp(name, "Sprunk", true)) {
		if(pData[playerid][pSprunk] < amount) return Error(playerid, "Sprunk Anda tidak cukup!");
		pData[playerid][pSprunk] -= amount; pData[targetid][pSprunk] += amount; sukses = true;
	}
	else if(!strcmp(name, "Bandage", true)) {
		if(pData[playerid][pBandage] < amount) return Error(playerid, "Perban Anda tidak cukup!");
		pData[playerid][pBandage] -= amount; pData[targetid][pBandage] += amount; sukses = true;
	}
	else if(!strcmp(name, "Medicine", true)) {
		if(pData[playerid][pMedicine] < amount) return Error(playerid, "Medicine Anda tidak cukup!");
		pData[playerid][pMedicine] -= amount; pData[targetid][pMedicine] += amount; sukses = true;
	}
	else if(!strcmp(name, "Medkit", true)) {
		if(pData[playerid][pMedkit] < amount) return Error(playerid, "Medkit Anda tidak cukup!");
		pData[playerid][pMedkit] -= amount; pData[targetid][pMedkit] += amount; sukses = true;
	}
	else if(!strcmp(name, "Material", true)) {
		if(pData[playerid][pMaterial] < amount) return Error(playerid, "Material Anda tidak cukup!");
		pData[playerid][pMaterial] -= amount; pData[targetid][pMaterial] += amount; sukses = true;
	}
	else if(!strcmp(name, "Crack", true)) {
		if(pData[playerid][pCrack] < amount) return Error(playerid, "Crack Anda tidak cukup!");
		pData[playerid][pCrack] -= amount; pData[targetid][pCrack] += amount; sukses = true;
	}
	else if(!strcmp(name, "Pot", true)) {
		if(pData[playerid][pPot] < amount) return Error(playerid, "Pot Anda tidak cukup!");
		pData[playerid][pPot] -= amount; pData[targetid][pPot] += amount; sukses = true;
	}
	// *Tambahkan 'else if' lagi untuk Seed, Fish, dll sesuai nama item kamu*
	else {
		Error(playerid, "Item '%s' tidak dapat dipindahtangankan!", name);
	}

	if(sukses)
	{
		// Animasi transaksi
		ApplyAnimation(playerid, "DEALER", "DEALER_DEAL", 4.1, 0, 0, 0, 0, 0, 1);
		
		// Pesan sukses
		SendClientMessageEx(playerid, COLOR_ARWIN, "GIVE: {FFFFFF}Anda memberikan %d %s kepada %s.", amount, name, ReturnName(targetid));
		SendClientMessageEx(targetid, COLOR_ARWIN, "GIVE: {FFFFFF}%s memberikan Anda %d %s.", ReturnName(playerid), amount, name);
		
		// Teks RP (Opsional, tapi bagus untuk roleplay)
		SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "* %s menyerahkan beberapa %s kepada %s.", ReturnName(playerid), name, ReturnName(targetid));

		// Refresh UI player yang memberi barang
		BarangMasuk(playerid);
	}

	// Hapus variabel PVar agar tidak nyangkut
	DeletePVar(playerid, "GiveItem");
	DeletePVar(playerid, "GiveTarget");
	
	return 1;
}

InventoryClickTextDraw(playerid, PlayerText:playertextid)
{
	// ==========================================
    // 1. KLIK SLOT ITEM (MEMILIH BARANG)
    // ==========================================
    for(new i = 0; i < MAX_INVENTORY; i++)
    {
        if(playertextid == MODELTD[playerid][i])
        {
            if(InventoryData[playerid][i][invExists])
            {
                MenuStore_UnselectRow(playerid); // Menghilangkan seleksi sebelumnya
                MenuStore_SelectRow(playerid, i); // Menyeleksi slot baru
                
                // Simpan slot yang dipilih ke database sementara
                ItemSelected[playerid] = i; 
            }
        }
    }

    // ==========================================
    // 2. KLIK TOMBOL "USE" (GUNAKAN)
    // ==========================================
    if(playertextid == INVINFO[playerid][2])
    {
        new id = ItemSelected[playerid];

        if(id == -1) // Jika player belum klik gambar item satupun
        {
            SendClientMessage(playerid, 0xAFAFAFFF, "ERROR: Pilih item terlebih dahulu!");
        }
        else
        {
            new string[64];
            strunpack(string, InventoryData[playerid][id][invItem]);

            // Langsung panggil Stock USE kita yang udah merangkum semua efek
            OnPlayerUseInventoryItem(playerid, string);
        }
    }

    // ==========================================
    // 3. KLIK TOMBOL "GIVE" (BERIKAN)
    // ==========================================
    else if(playertextid == INVINFO[playerid][3])
    {
        new id = ItemSelected[playerid];

        if(id == -1)
        {
            SendClientMessage(playerid, 0xAFAFAFFF, "ERROR: Pilih item terlebih dahulu!");
        }
        else
        {
            new string[64];
            strunpack(string, InventoryData[playerid][id][invItem]);

            // Langsung panggil Stock GIVE (akan memunculkan Dialog Target ID)
            OnPlayerGiveInventoryItem(playerid, string);
        }
    }

    // ==========================================
    // 4. KLIK TOMBOL "DROP" (BUANG) 
    // *Asumsi INVINFO[4] adalah tombol Drop di Textdraw lu
    // ==========================================
    else if(playertextid == INVINFO[playerid][4]) 
    {
        new id = ItemSelected[playerid];

        if(id == -1)
        {
            SendClientMessage(playerid, 0xAFAFAFFF, "ERROR: Pilih item terlebih dahulu!");
        }
        else
        {
            new string[64];
            strunpack(string, InventoryData[playerid][id][invItem]);

            // Langsung panggil Stock DROP (akan memunculkan Dialog Jumlah)
            OnPlayerDropInventoryItem(playerid, string);
        }
    }

    // ==========================================
    // 5. KLIK TOMBOL "CLOSE" (TUTUP)
    // ==========================================
    else if(playertextid == INVINFO[playerid][5])
    {
        Inventory_Close(playerid);
    }
}

// ===============================================
// FUNGSI ANIMASI KLIK & BUKA TUTUP INVENTORY
// ===============================================

stock MenuStore_SelectRow(playerid, row)
{
    ItemSelected[playerid] = row;
    PlayerTextDrawHide(playerid, INDEXTD[playerid][row]);
    PlayerTextDrawColor(playerid, INDEXTD[playerid][row], -65281); // Warna jadi gelap saat diklik
    PlayerTextDrawShow(playerid, INDEXTD[playerid][row]);
    return 1;
}

stock MenuStore_UnselectRow(playerid)
{
    new row = ItemSelected[playerid];
    if(row != -1)
    {
        PlayerTextDrawHide(playerid, INDEXTD[playerid][row]);
        PlayerTextDrawColor(playerid, INDEXTD[playerid][row], 859394047); // Warna normal
        PlayerTextDrawShow(playerid, INDEXTD[playerid][row]);
    }
    return 1;
}

stock Inventory_Show(playerid)
{
    if(!IsPlayerConnected(playerid)) return 0;

    new str[256], quantitybar, totalall;
    
    // Set Nama Player
    format(str, 128, "%s", ReturnName(playerid));
    PlayerTextDrawSetString(playerid, INVNAME[playerid][3], str);
    
    // Refresh Item & Reset Klik
    BarangMasuk(playerid);
    ItemSelected[playerid] = -1; 
    
    PlayerPlaySound(playerid, 1039, 0,0,0);
    SelectTextDraw(playerid, -1);
    
    for(new a = 0; a < 6; a++) PlayerTextDrawShow(playerid, INVNAME[playerid][a]);
    for(new a = 0; a < 11; a++) PlayerTextDrawShow(playerid, INVINFO[playerid][a]);
    
    for(new i = 0; i < MAX_INVENTORY; i++)
    {
        PlayerTextDrawShow(playerid, INDEXTD[playerid][i]);
        PlayerTextDrawShow(playerid, AMOUNTTD[playerid][i]);
        totalall += InventoryData[playerid][i][invTotalQuantity];
        
        if(InventoryData[playerid][i][invExists])
        {
            PlayerTextDrawShow(playerid, NAMETD[playerid][i]);
            PlayerTextDrawShow(playerid, GARISBAWAH[playerid][i]);
            PlayerTextDrawSetPreviewModel(playerid, MODELTD[playerid][i], InventoryData[playerid][i][invModel]);
            PlayerTextDrawShow(playerid, MODELTD[playerid][i]);
            
            new string[64];
            strunpack(string, InventoryData[playerid][i][invItem]);
            PlayerTextDrawSetString(playerid, NAMETD[playerid][i], string);
            
            format(str, sizeof(str), "%dx", InventoryData[playerid][i][invAmount]);
            PlayerTextDrawSetString(playerid, AMOUNTTD[playerid][i], str);
        }
        else
        {
            PlayerTextDrawHide(playerid, AMOUNTTD[playerid][i]);
        }
    }
    
    // Bar Kapasitas
    format(str, sizeof(str), "%.1f/850.0", float(totalall));
    PlayerTextDrawSetString(playerid, INVNAME[playerid][4], str);
    quantitybar = totalall * 199/850;
    PlayerTextDrawTextSize(playerid, INVNAME[playerid][2], quantitybar, 3.0);
    PlayerTextDrawShow(playerid, INVNAME[playerid][2]);
    
    return 1;
}

stock Inventory_Close(playerid)
{
    CancelSelectTextDraw(playerid);
    ItemSelected[playerid] = -1;
    
    for(new a = 0; a < 6; a++) PlayerTextDrawHide(playerid, INVNAME[playerid][a]);
    for(new a = 0; a < 11; a++) PlayerTextDrawHide(playerid, INVINFO[playerid][a]);
    
    for(new i = 0; i < MAX_INVENTORY; i++)
    {
        PlayerTextDrawHide(playerid, NAMETD[playerid][i]);
        PlayerTextDrawHide(playerid, INDEXTD[playerid][i]);
        PlayerTextDrawColor(playerid, INDEXTD[playerid][i], 859394047);
        PlayerTextDrawHide(playerid, MODELTD[playerid][i]);
        PlayerTextDrawHide(playerid, AMOUNTTD[playerid][i]);
        PlayerTextDrawHide(playerid, GARISBAWAH[playerid][i]);
    }
    return 1;
}