# Changelog v1.0.10

## Added

* **Bisnis MapIcon** — Setiap bisnis di kota sekarang memiliki logo/icon di radar map sehingga warga baru mudah menemukan tanpa perlu GPS.
  * Fast Food — Icon Burger
  * Market — Icon Shopping Cart
  * Clothes — Icon T-Shirt
  * Sportshop — Icon Baseball
  * Electronic — Icon Computer
  * GYM — Icon Dumbbell
  * Ammunation — Icon Gun

* **Workshop Dynamic Pickup** — Workshop type dynamic kini muncul dengan dynamic pickup (icon info) di posisi workshop sehingga lebih mudah ditemukan player.

* **Builder** — Hanya support untuk PC dan beberapa Client Android.

* **Complex Environmental Damage System** — Damage dari lingkungan sekarang tercatat di `/health` dan `/damagelog` dengan wound type yang lebih variatif:
  * Jatuh dari ketinggian (Splat): Torso + Kaki jika damage > 30
  * Tabrak kendaraan: Torso + 1 Limb random
  * Helicopter Blade: Torso + Arm atau Head
  * Explosion: Torso + Groin + Limbs random
  * Tenggelam: Torso

## Changed

* **Jangkauan `/wt` diperluas** — dari 220.0 unit menjadi 8000.0 unit sehingga mencakup seluruh map San Andreas. Player dalam channel yang sama kini bisa saling mendengar dari jarak manapun.

## Fixed Bugs

* **Fall damage tidak berpengaruh ke sistem health RP** — Sebelumnya damage jatuh hanya mengurangi health client-side tanpa tercatat di sistem damage. Sekarang damage jatuh otomatis menambah entry ke `AddDamage()`, muncul di `/health` dan `/damagelog` dengan weapon ID 54 (Splat).

* **Damage lingkungan lain tidak terdaftar** — Vehicle collision, explosion, helicopter blade, dan drowning kini juga tercatat dengan body part yang realistis dan damage limit yang sesuai (drowning max 30, explosion max 80, dll).

* **Damage tidak muncul di /health** — Fix bodypart offset mismatch (`+ 3`) di `Damage_CountByBodypart()` dan `GetPlayerBodypartStatus()` yang menyebabkan damage tidak ter-match saat ditampilkan. Juga fix `case 0` → `case 54` untuk fall damage weapon ID yang benar dari SA-MP. Ditambah wound status untuk weapon 49-54 (vehicle collision, helicopter blade, explosion, drowning, fall).

## Technical

* File yang dimodifikasi:
  - `gamemodes/main.pwn` — Callback `OnPlayerTakeDamage` (fix case 54 fall damage)
  - `gamemodes/Modules/Command/PlayerCommand.inc` — Range `/wt`
  - `gamemodes/Modules/Property/bisnis/Function.inc` — MapIcon per bisnis
  - `gamemodes/Modules/Property/workshop/Header.inc` — WorkshopPickup variable
  - `gamemodes/Modules/Property/workshop/Function.inc` — Create/destroy dynamic pickup
  - `gamemodes/Modules/Players/damage/function.inc` — Fix bodypart offset, tambah wound status weapon 49-54

**Catatan:**
- Untuk mengecek damage: `/health` atau `/damagelog`
- /wt sekarang bisa digunakan untuk komunikasi jarak jauh tanpa batas radius
- Android user harus menggunakan client yang support agar bisa menggunakan`/dyoh`

@everyone