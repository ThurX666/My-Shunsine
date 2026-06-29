# Design: Gamemode v1.0.19

## Execution Order
1. Investigasi bug weapon random sampai root cause terbukti.
2. Investigasi bug /fish sampai root cause terbukti.
3. Patch bug prioritas dengan diff kecil.
4. Implement SAPD rank 1-16.
5. Implement faction bank locker.
6. Implement sidejob Milker (map objects + flow).
7. Compile/test setelah setiap area besar.

## Feature Targets

### SAPD Rank 1-16
- Cari definisi rank SAPD saat ini (berapa rank existing, nama rank).
- Tambah rank 1-16 termasuk Chief sebagai rank tertinggi.
- Pastikan perintah faction (promote/demote, locker, gaji) scale dengan rank baru.

### Faction Bank Locker
- Tambah sistem bank terpisah per faction (field baru di tabel faction atau tabel baru `faction_bank`).
- Tambah menu bank di locker faction: deposit (semua rank), withdraw (leader/deputy/commissioner only).
- Validasi rank untuk withdraw: leader = rank tertinggi, deputy = rank ke-2, commissioner = rank ke-3 (atau sesuai definisi existing).
- Log transaksi untuk audit.

### Sidejob Milker
- Map objects dari file texture studio sudah siap; load di OnGameModeInit.
- Start job di locker (koordinat 1556.2843,-32.5951,21.3849).
- 6 CP random di posisi sapi (6 titik yang sudah diberikan).
- /perahsusu atau KEY_NO (N) untuk memerah sapi saat di CP.
- Animasi jongkok saat memerah (ApplyAnimation).
- Setelah memerah, karakter angkat box (attach object).
- Bawa ke tempat menaruh susu (1541.9679,-41.2531,21.2003).
- Ulangi 10x, selesai → salary $250.

## Bug Targets

### Weapon Random Saat Kerja
- Investigasi apakah ada timer/callback yang memberikan weapon secara otomatis ke player yang bekerja.
- Trace flow: OnPlayerSpawn, OnPlayerRequestClass, gang zone weapon, job reward system.
- Cek apakah weapon dari faction/rank system meng-override inventory saat kerja.
- Cek kemungkinan bug dari perubahan v1.0.18 (toys slot, pTask weapon cleanup).

### /fish Tidak Dapat Ikan
- Trace cmd:fish → dialog → area check → reward flow.
- Cek query item/fish di database.
- Cek apakah ada perubahan inventory/items system yang broken.
