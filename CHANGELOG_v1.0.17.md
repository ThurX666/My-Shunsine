# Changelog v1.0.17 Stability

## Added

* **Progress Bar State Reset** - Menambahkan reset otomatis `pActivity` dan `pActivityTime` saat progress bar disembunyikan agar activity tidak tersangkut.

## Changed

* **Login Spawn Flow** - Spawn login sekarang mengembalikan `interior` dan `virtual world` player sebelum `SpawnPlayer` agar posisi terakhir lebih aman dimuat.

* **Radio Command Flow** - Command `/radio` sekarang memakai alur validasi yang lebih bersih untuk opsi `off` dan `set`.

* **House Structure Name Fallback** - List struktur house sekarang menampilkan fallback `Model ID` jika nama object tidak ditemukan di daftar struktur.

* **Offline Set Faction Remove Flow** - Command `/osetfaction` sekarang bisa memakai rank `0` untuk kick faction player offline dengan lebih mudah.

* **Offline Set Admin Remove Flow** - Command `/osetadmin` level `0` sekarang dipakai untuk melepas hak admin player offline.

## Fixed Bugs

* **Vehicle Progress Bar Stuck** - Fix progress bar vehicle/job yang bisa stuck karena activity state tidak ikut direset saat bar disembunyikan.

* **Vehicle Refuel Activity Stuck** - Fix activity refuel kendaraan yang tidak mengosongkan `pActivity` setelah selesai atau gagal.

* **Miner Last Spawn Login Fall** - Fix player yang login di area miner bisa langsung jatuh/mati karena interior dan virtual world belum direstore sebelum spawn.

* **House Structure Object Disappear** - Fix object house structure di `/dyoh` yang bisa hilang setelah cancel edit dengan me-refresh object ke posisi tersimpan.

* **House Structure Missing Name** - Fix nama object custom di `/dyoh` yang bisa kosong dengan menampilkan fallback model ID.

* **Radio Set Chat Log Duplicate** - Fix flow `/radio set` yang bisa memicu pesan/log radio muncul berulang.

**Catatan:**
```- Update ini berfokus membuat aktivitas player lebih aman dan tidak mudah stuck.
- Player yang login di lokasi terakhir sekarang lebih stabil dan tidak mudah jatuh karena world/interior belum siap.
- Builder, faction division, dan admin mendapat alur yang lebih jelas saat mengatur struktur house, kick faction offline, atau melepas admin offline.```

@everyone