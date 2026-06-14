# Changelog v1.0.1 Beta

## Fixed Bugs

- Radio kendaraan: `StopAudioStreamForPlayer(playerid)` dan `pData[playerid][pRadioVehicleOn] = 0` sekarang sudah dikelola dengan benar di `OnPlayerStateChange`.
- Bisnis owner double: `Bisnis_Save` dan `Bisnis_Reset` diperbaiki, handling owner ditingkatkan, dan refresh data bisnis berjalan dengan benar.
- Bisnis elektronik: nomor telepon dari dialog `RandNumber` kini disimpan dengan benar, dan data phone langsung disimpan ke database setelah pembelian.
- Bisnis reset/delete: data bisnis reset sudah disimpan dengan benar dan `Bisnis_Refresh` dipanggil setelah reset/save.
- Arms Dealer schematic indexing: mapping schematic di dialog `BuySchematic` dikoreksi dan pengecekan schematic di `CreateGun` diperbaiki.
- Create gun / ammo: `createammo` sekarang memvalidasi jumlah ammo input, menghitung material dengan benar, mencegah overfill, dan fallback ke senjata ranged valid bila pemain tidak memegang senjata.
- `Dialog:CreateAmmo`: perbaikan logika fallback ke senjata ranged, validasi kondisi ammo penuh, validasi material, dan pesan error yang lebih jelas.
- Install aplikasi Twitter: `pTwitter` dan `twitterstatus` kini tersimpan dengan benar di `UpdatePlayerData` dan database.
- Compile fix: `main.pwn` kini berhasil dikompilasi tanpa error setelah menghapus invalid `break;` di `gamemodes/Modules/Property/bisnis/Dialog.inc`.
- Perbaikan tambahan: `gamemodes/Modules/Jobs/ArmsDealer/cmd.inc` kini bebas dari variabel `String[212]` yang tidak terpakai di `CMD:createammo`.

**📌 Hasil**
- `main.pwn` berhasil build dengan sukses.
- Stabilitas Pawn script dan mekanik Arms Dealer/Twitter kini lebih baik.