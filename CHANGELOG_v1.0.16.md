# Changelog v1.0.16

**Title Update:** `Stronghold`

## Added

* **Offline Set Faction** - Menambahkan command `osetfaction` untuk set faction player secara offline.

* **Offline Set Admin** - Menambahkan command `osetadmin` untuk set level admin player secara offline.

* **Offline Check UCP Characters** - Menambahkan command `ocheckucp` untuk melihat daftar karakter dari UCP yang dituju dalam kondisi offline.

* **Custom Ammo Storage** - Menambahkan input jumlah ammo saat menyimpan senjata ke bagasi kendaraan faction dan private vehicle.

* **House Component Storage** - Menambahkan penyimpanan `component` di `/storage` house agar component bisa dipindahkan dari inventory ke safe rumah.

* **House Material Storage** - Menambahkan penyimpanan `material` di `/storage` house agar material tidak perlu terus dibawa player.

* **House Schematic Storage** - Menambahkan safe schematic per jenis senjata di `/storage` house untuk menyimpan dan mengambil schematic secara terpisah.

## Changed

* **Offline Command Validation** - Command offline sekarang akan menolak target yang sedang online dan menampilkan pesan error yang jelas.

* **Offline UCP Check Flow** - `ocheckucp` sekarang berfokus ke nama UCP dan memberi arahan untuk lanjut cek `/ostats` pada karakter offline yang dipilih.

* **House Weapon Capacity** - Kapasitas weapon storage house ditingkatkan menjadi 15 slot total.

* **House Storage Menu** - Menu `/storage` house sekarang menampilkan ringkasan weapon, component, material, schematic, money, crack, dan pot dalam satu tempat.

## Fixed Bugs

* **Offline Target Detection by Reg ID** - Fix validasi target offline agar input angka dibaca sebagai `reg_id` player, bukan salah dianggap `playerid` online.

* **Partial Ammo Trunk Storage** - Fix flow penyimpanan senjata ke trunk yang sebelumnya selalu memindahkan semua ammo tanpa pilihan jumlah.

* **House Weapon Ammo Type Reset** - Fix slot weapon house yang sebelumnya bisa menyisakan tipe ammo lama setelah senjata diambil dari storage.

* **Hidden House Weapon Slots** - Fix storage house yang sebelumnya hanya membuka 5 slot meskipun backend weapon storage sudah memiliki lebih banyak slot.

* **Vehicle Radio Passenger Sync** - Fix radio kendaraan yang sebelumnya kadang hanya terdengar di driver dan tidak ikut tersinkron ke penumpang atau listener terdekat.

* **Pickup Item Weapon Slot Check** - Fix `/pickupitem` yang bisa gagal mengambil dropped weapon karena slot senjata lama masih terbaca terisi walau tangan sudah kosong.

**Catatan:**
```- Withdraw component dari house tetap mengikuti batas bawaan inventory player, yaitu maksimal 250 component di tangan.
- Schematic house disimpan per jenis weapon schematic agar flow arms dealer tetap konsisten dengan inventory existing.
- Title release `Stronghold` dipakai untuk menandai update kontrol admin, penguatan storage, dan stabilisasi sistem.
- Gamemode sudah berhasil dicompile dengan `pawncc` tanpa error/warning setelah perubahan kode.```

@everyone
