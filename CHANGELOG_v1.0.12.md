# Changelog v1.0.12

## Added

* **SAMD Interior Mapping** - Penambahan mapping interior baru untuk San Andreas Medical Department (SAMD) yang meliputi:
  * Area reception, pharmacy, dan administrasi.
  * Ruang inspeksi/IGD (4 ruang) dengan penanda nomor.
  * Rooftop dan basement.
  * Ruang staff, security post, dan area tunggu pasien.
  * Toilet pria & wanita.
  * Perlengkapan medis lengkap (tempat tidur, lemari obat, komputer administrasi, kursi tunggu, dan furnitur pendukung lainnya).
  * Signage dan penanda ruangan yang jelas (ALL SAINTS GENERAL HOSPITAL, PHARMACY, RECEPTION, EMERGENCY ROOM, INSPECTION ROOM, STAFF ROOM, SECURITY, BASEMENT, ROOFTOP).
  * Interior fully mapped dengan dynamic object dan material textures.

* **Auto Drop Gun Saat Injured** - Saat player down/pingsan/injured, senjata otomatis dijatuhkan ke ground dengan jumlah ammo yang sesuai dari slot senjata player.

* **Pickup Dropped Weapon Inventory** - Sistem pickup existing di inventory sekarang bisa mengambil dropped weapon dari auto drop, termasuk weapon ID, ammo, dan type ammo.

* **Faction Vehicle Trunk Weapon Storage** - Kendaraan faction goodside sekarang mendukung penyimpanan senjata di trunk, termasuk kendaraan faction static.

* **Siren Toggle SAPD** - Menambahkan command `/togsiren` untuk SAPD agar siren kendaraan bisa di-toggle seperti sistem GM lama.

* **Suit / Gunting Batu Kertas** - Menambahkan fitur `/suit` untuk challenge suit antar player:
  * `/suit [playerid/nama] [batu/gunting/kertas]` untuk menantang.
  * `/suit accept [batu/gunting/kertas]` untuk menerima dan memilih.
  * `/suit deny` untuk menolak.
  * `/suit cancel` untuk membatalkan challenge aktif.

* **Inventory Amount Button** - Tombol `Amount` di inventory sekarang bisa digunakan untuk menentukan jumlah item sebelum `Give` atau `Drop`.

## Changed

* **Stats Player** - Tampilan `/stats` dirapikan dan sekarang menampilkan faction, rank faction, family, dan rank family dengan penggunaan newline yang lebih tertata.

* **Mechanic Repair Engine** - Repair engine kendaraan sekarang mengikuti upgrade engine. Kendaraan tanpa upgrade tetap 1000 HP, kendaraan dengan upgrade engine bisa kembali ke 2000 HP setelah direpair.

* **Miner Energy Flow** - Saat energi miner habis, mining dihentikan otomatis dari proses kerja, namun player tetap wajib menggunakan `/stopmine` untuk menerima bayaran.

* **Vehicle Trunk Component Limit** - Bagasi kendaraan dapat menyimpan component sampai 2000 sesuai tampilan trunk. Ini tidak harus menggunakan towtruck; towtruck/pickup mechanic hanya dipakai untuk flow kerja load/unload component mechanic.

## Fixed Bugs

* **Vehicle Last Spawn Exit Interior/VW** - Fix bug teleport ke interior rumah orang saat player keluar dari kendaraan/interior. Virtual world dan interior kendaraan pada respawn/last spawn exit sekarang diset dengan urutan yang benar.

* **SAPD Vehicle HP Setelah Repair** - Fix kendaraan SAPD atau kendaraan lain yang sudah upgrade engine tetap 1000 HP setelah repair. Sekarang sistem repair engine membaca status upgrade kendaraan dengan benar.

* **Vehicle Upgrade Index Mechanic Dialog** - Fix indexing vehicle ID pada dialog upgrade mechanic agar upgrade tersimpan dan terbaca ke kendaraan yang benar.

* **Faction Trunk Tidak Bisa Simpan M4** - Fix trunk kendaraan faction yang tidak menampilkan opsi/penyimpanan senjata tertentu seperti M4.

* **Miner Tidak Dapat Bayaran Saat Energi Habis** - Fix kondisi energi habis yang sebelumnya menghentikan miner tetapi tidak memberi alur pembayaran yang jelas. Sekarang player mendapat notifikasi dan diarahkan menggunakan `/stopmine`.

* **Auto Drop Gun Tidak Pakai Sistem Pickup Existing** - Auto drop weapon saat injured disesuaikan agar memakai data drop/pickup di `Inventory.pwn`, bukan sistem pickup custom terpisah.

* **Tidak Bisa Beli Towtruck di Point Mechanic** - `/buytowtruck` sekarang membaca mechanic point yang aktif, termasuk point job mechanic yang tampil di map.

* **Payticket Tidak Keluar di Kantor PD** - `/payticket` dan `/unlocktire` sekarang menampilkan tabel setelah pencarian kendaraan selesai, serta memberi error jika tidak ada tagihan atau tidak berada di payment point.

* **Inventory Amount Tidak Terpakai** - `Give` dan `Drop` inventory sekarang wajib memakai angka dari tombol `Amount`; label `Amount` berubah menjadi angka yang dimasukkan player.

* **Inventory Give Item Terbatas** - Item stack seperti component, pill, seed, hasil panen, toll card, dan schematic sekarang bisa dipindahkan melalui inventory give dengan jumlah yang benar.

* **Pill RS Bisa Disalahgunakan** - `/takepills` dan dialog pengambilan pill sekarang validasi ulang faction SAMD, duty, dan posisi pharmacy. `/givepills` juga hanya bisa digunakan SAMD yang sedang on duty.

* **Vehicle Spawn Kadang Tidak Muncul** - Status despawn kendaraan sekarang di-reset saat vehicle respawn, sehingga kendaraan yang sebelumnya dipindah ke virtual world tersembunyi tidak nyangkut.

**Catatan:**
```- Kendaraan yang ingin kembali ke 2000 HP setelah repair harus memiliki upgrade engine.
- Saat mining berhenti karena energi habis, player tetap harus menggunakan `/stopmine` untuk mengambil bayaran.
- Dropped weapon dari injured diambil lewat sistem pickup inventory yang sudah ada.
- Command suit tidak memakai uang/reward otomatis, hanya menentukan pemenang secara fair setelah dua player memilih.
- Trunk component maksimal 2000 tidak membutuhkan towtruck; towtruck tetap kendaraan kerja mechanic untuk towing/load component.
- Gamemode sudah berhasil dicompile dengan `pawncc` tanpa error/warning setelah perubahan kode.```

@everyone
