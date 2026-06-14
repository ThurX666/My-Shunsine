# Changelog v1.0.11 Dupe

## Added

* **Furniture Store GPS** - Menu `/gps` sekarang memiliki opsi Furniture Store sehingga player bisa menargetkan checkpoint ke lokasi furniture store yang tersedia.

* **Auto-destroy Weapon System** - Senjata otomatis di-reset/destroy dari slot player ketika ammo habis, baik saat player mencoba menembak tanpa ammo maupun ketika ammo habis setelah shot.

* **Boombox Audio on Area Enter** - Player yang masuk ke dynamic area boombox sekarang otomatis mendapat stream radio dari boombox tersebut lewat `OnPlayerEnterDynamicArea`.

## Changed

* **Radius mechanic point untuk `/jobduty mechanic` dan `/vm`** - Pengecekan mechanic center dan mechanic desert sekarang menggunakan radius `30.0`.

* **Workshop dynamic label** - Workshop type dynamic sekarang menampilkan label berbeda sesuai status kepemilikan:
  * Jika sudah dimiliki: `[id:x]`, nama workshop, dan owner.
  * Jika belum dimiliki: nama workshop, status dijual, type, dan price.

## Fixed Bugs

* **/jobduty mechanic & /vm location check** - Command mechanic sekarang valid di mechanic center, mechanic desert, atau workshop dalam radius `30.0`. Penggunaan di workshop hanya bisa untuk owner/employee workshop.

* **Boombox no sound for newly-entered players** - `OnPlayerEnterDynamicArea` sekarang mencari pemilik boombox berdasarkan `BBArea` dan memutar `BBStation` ke player yang baru masuk area.

* **Radio double log on boombox dialog** - Loop player pada dialog radio boombox hanya memutar audio ke player sekitar; pesan `RADIO` hanya dikirim sekali ke player yang memasang URL.

* **Transfer dupe bug** - `/transfer` sekarang menolak transfer ke diri sendiri setelah target berhasil diparse.

* **Buyschematic / creategun format cleanup** - Tampilan `/creategun` menggunakan jumlah parameter `SchematicRequire` yang sesuai dengan format string untuk warga biasa dan anggota family.

* **Create gun delay system** - `/creategun` menolak crafting saat `DelayWeaponCreate` masih aktif, dan crafting senjata mengatur delay ke `600` detik.

## Technical

* File yang dimodifikasi:
  - `gamemodes/main.pwn` - Auto-destroy weapon saat ammo habis dan audio boombox saat masuk area.
  - `gamemodes/Modules/Command/PlayerCommand.inc` - Menu `/gps` Furniture Store dan validasi `/jobduty mechanic`.
  - `gamemodes/Modules/Command/Modules/Dialog.inc` - Dialog GPS Furniture Store dan update menu GPS.
  - `gamemodes/Modules/Dynamic/atm/cmd.inc` - Validasi `/transfer` agar tidak bisa transfer ke diri sendiri.
  - `gamemodes/Modules/Jobs/Mechanic/function.inc` - Helper pengecekan mechanic point dan workshop owner/employee.
  - `gamemodes/Modules/Jobs/Mechanic/cmd.inc` - Validasi lokasi `/vm` untuk mechanic center/desert/workshop.
  - `gamemodes/Modules/Property/workshop/Function.inc` - Format label dynamic workshop berdasarkan status owner.
  - `gamemodes/Modules/Property/workshop/Command.inc` - Urutan refresh label saat membuat workshop dynamic.

**Catatan:**
- Respray color di `/vm` sudah tersedia melalui `ServiceColor` dengan input `color1 color2`.
- Command `/quiz create/answer/end` sudah ada dan pesan quiz dikirim lewat `SendQuizVoteMessage`; player dengan toggle quiz/vote off tidak menerima pesan.
- Cooldown `DelayWeaponCreate` memang dibuat untuk mencegah spam craft senjata.
- Gamemode sudah berhasil dicompile dengan `pawncc` tanpa error/warning setelah perubahan kode.

@everyone
