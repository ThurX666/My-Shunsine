# Changelog v1.1.0 — REFACTOR

## Added

* **Economy Configuration System** — Admin level 6+ bisa atur semua payout & harga via `/economy` dialog multi-level. 12 key: taxi, mechanic, courier, bus, trucker, lumber, milker, farmer, faction duty, fuel, toll, fish. Semua value dalam dollar-cents, bisa reset ke default kapan saja.
* **House Sealing & Auction** — Admin level 6+ bisa segel rumah player yang inactive 15+ hari via `/segelrumah`. Owner bisa tebus dalam 7 hari dengan bayar 25% dari harga rumah via `/tebusrumah`. Info segel via `/infosegel`. Rumah tersegel terkunci, tidak bisa dimasuki, dan label 3D-nya berwarna merah.
* **Vehicle Maskot Fix** — Kendaraan player tidak auto-spawn saat login jika lokasinya > 30 meter dari posisi player. Player dapat notifikasi untuk respawn manual via `/spawn`. Mencegah kendaraan disalahgunakan orang lain saat owner tidak di dekatnya.
* **KEY H / CTRL — Freeze Animasi** — Tekan tombol H (CTRL) untuk langsung menghentikan animasi lari/terjun. Bermanfaat untuk berhenti mendadak dan mencegah jatuh ke jurang atau menabrak.
* **Auto-RP `rpperiksa` untuk SAMD** — Medic SAMD bisa chat "rpperiksa" (huruf kecil semua) di dekat player untuk auto-RP memeriksa kesehatan. Mencari player terdekat dalam radius 5 meter, menampilkan dialog health + RP message.

## Fixed

* **Pemerah Susu (Milker) Sidejob:** Full Fix.
* **Inventory Item Bug** — Fix data leak item inventory (makan/minum hilang diganti pil). Race condition di `OnPlayerDataLoaded1` dan `LoadPlayerVehicle` sudah dicegah dengan race check.
* **Radio → Boombox, vradio → Vsong** — Tabrakan suara radio antar sistem sudah diperbaiki. `/radio` sekarang `/boombox` (hanya place-based), `/vradio` sekarang `/vsong` (hanya di kendaraan, auto-stop saat keluar mobil).
* **`/setfaction 0`** — Sekarang bisa keluarkan player dari faction dengan `/setfaction [playerid] 0`. Sebelumnya error karena rank validation memblokir rank 0.
* **Vehicle Spawn Bug** — Error "Cannot spawn vehicles that have not spawned" teratasi otomatis oleh Maskot fix.
* **HBE Warna Persentase** — Indikator lapar dan haus sekarang berwarna: hijau (61-100%), kuning (31-60%), merah (0-30%).
* **Command Uang Submit** — Semua command uang (`/pay`, `/deposit`, `/withdraw`, `/transfer`, `/givemoneyall`, `/takemoney`) sekarang konsisten menggunakan dollar-cents. Player ketik `50` = $50.00, bukan $0.50.
* **Boombox Radius** — Radius audio boombox dikurangi dari 30 meter menjadi 15 meter sesuai laporan player.

## Changed

* **Version Bump** — Server version kini `v1.1.0`.
* **Rebalance Harga Kendaraan** — 80+ kendaraan di dealer direbalance berdasarkan kelas.
* **Rebalance Harga Produk Bisnis** — Default harga di semua tipe toko disesuaikan.
* **FormatMoney Rewrite** — Tampilan uang sekarang menggunakan pemisah ribuan (koma) dan tanda dollar. Contoh: $1,500.00, $50,000.00.
* **Penghasilan Job & Sidejob — Rebalance ke $5,000/hari** — Semua gaji disesuaikan berdasarkan perhitungan waktu kerja. Maksimal pendapatan player adalah $5,000.00 dalam 24 jam grinding. Miner dan Farmer juga diperbaiki agar tidak overpowered maupun terlalu rendah.

**Catatan:**
> _"v1.1.0 REFACTOR — fokus pada perbaikan ekonomi server (rebalance harga kendaraan & produk bisnis, Economy Config System), fix crash Milker sidejob, implementasi House Sealing & Auction, refactor Radio/VRradio, standardisasi input dollar-cents, penambahan KEY_CTRL_BACK freeze animasi, HBE warna, dan perbaikan command `/setfaction 0`. Terima kasih atas laporan dan masukannya!"_

@everyone
