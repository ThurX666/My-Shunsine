# Changelog v1.0.18 Stability Update

## Added

* **Menu Animasi `/e`** - Player sekarang bisa membuka list animasi lewat `/e` atau `/emote`, lalu pilih animasi langsung dari dialog.
* **Autorp Chat** - Player sekarang bisa mengetik trigger seperti `crash`, `tabrakan`, `rprun`, `kabur`, `rpcj`, `fight`, atau `berantem` tanpa slash untuk menampilkan teks RP otomatis di sekitar player.
* **Gaji Server `/gajiserver`** - Player sekarang bisa melihat daftar gaji job dan sidejob langsung dari dalam game.
* **Info Family `/finfo`** - Menu `Family Member` di dalam `/finfo` sekarang menampilkan list yang rapi, berisi daftar seluruh member family (online maupun offline) lengkap dengan pangkatnya.
* **Kick Family Offline** - Admin sekarang bisa kick member family yang sedang offline lewat command `/osetfamily <nama/regid> 0`.

## Changed

* **Slot Tambahan Aksesoris** - Batas slot aksesoris di sistem dinaikkan (maksimal 7 slot toys) agar semua player mendapatkan lebih banyak kapasitas tanpa memerlukan VIP.
* **Tampilan List Family** - Layout command `/finfo` pada fitur Family Member dirombak menjadi daftar bertabel dengan header kolom nama, status koneksi, dan rank yang lebih jelas dibaca.
* **Stop Animasi Lebih Jelas** - Penghentian animasi looping sekarang lebih tegas mengacu pada tombol `SPACE` yang secara konstan tertera sebagai textdraw saat player sedang dalam animasi statik.
* **Weapon Attached Object Cleanup** - Cleanup senjata kini hanya melepas object yang memang dipasang oleh sistem weapon (Slot 5-8), sehingga tidak lagi konflik dan menghapus preview aksesoris temporer (`FSTOYS`).

## Fixed

* **Toys AXP** - Preview toys dari `/axp` dan `/toysaxp` tidak lagi otomatis hilang karena sistem attached weapon.
* **Pembelian Schematic** - Nama schematic yang dibeli sekarang sesuai dengan pilihan menu, termasuk Desert Eagle, MP5, dan AK47.
* **Boombox Radio** - Log/pesan play boombox tidak lagi spam saat banyak player masuk area radio.
* **Sidejob Bus Route C/D** - Rute C dan D sekarang berjalan dari checkpoint yang benar.
* **Toggle Neon Tombol N** - Neon/lampu kendaraan tidak lagi toggle berkali-kali saat tombol `N` ditahan.
* **Offline Stats `/ostats`** - Tampilan faction, family, admin, dan helper di `/ostats` sekarang sesuai data player.

@everyone
