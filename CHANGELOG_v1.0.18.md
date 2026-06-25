# Changelog v1.0.18 Toys AXP & Update Plan

## Fixed Bugs

* **Bus Sidejob Route C/D** - Fix route C yang melewati checkpoint awal dan route D yang salah reset step saat lanjut lap.

* **Bombox Radio Log Spam** - Fix log/pesan radio yang muncul berulang saat player masuk area boombox dengan menghapus replay handler duplikat di `OnPlayerEnterDynamicArea`.

* **Schematic Buy Menu Mapping** - Fix pembelian schematic yang bergeser karena header dialog ikut dihitung sebagai item; beli Desert Eagle/MP5/AK47 sekarang masuk ke schematic yang sesuai.

* **Toys AXP Temporary Object Cleanup** - Fix awal bug toys `/axp` dan `/toysaxp` yang bisa muncul lalu hilang karena cleanup weapon di `pTask.pwn` menghapus attached object slot `5..8` tanpa memastikan object tersebut benar-benar object weapon.

## Changed

* **Weapon Attached Object Cleanup** - Cleanup weapon sekarang hanya melepas attached object yang sebelumnya dipasang oleh sistem weapon, sehingga temporary/preview toys `FSTOYS` di slot yang sama tidak ikut terhapus.

* **Toys AXP Investigation Flow** - Alur investigasi Toys AXP sekarang dibakukan lewat OpenSpec `fix-toys-axp-flow`, dengan pemisahan jelas antara temporary `FSTOYS` dan toys persistent database `aksesoris`.

## OpenSpec

* **fix-toys-axp-flow** - Change khusus untuk validasi ulang flow `cmd:axp`, `cmd:toysaxp`, temporary toys, persistent aksesoris, dan konflik slot weapon cleanup.

* **update-gamemode-v1-0-18** - Change rencana v1.0.18 untuk memastikan fitur dan bug fix sesuai request asli sebelum implementasi berikutnya.

## Pending v1.0.18 Request

* **New Features** - `/e` dialog animasi, autorp di `OnPlayerText` tanpa slash, `/gajiserver`, +2 slot toys non-VIP, `/finfo` list member family, dan `/osetfamily <id> 0`.

* **Bug Fixes Pending Investigation** - Otot N neon camera zoom dan `/ostats` display bug.

**Catatan:**
```
- Update ini belum final untuk seluruh v1.0.18; changelog akan ditambah setiap perubahan selesai dibuat.
- Cleanup `RemoveFSToys(playerid)` di spawn/disconnect tetap dipertahankan karena FSTOYS adalah temporary/preview toys.
- Tidak ada perubahan ke persistent toys database `aksesoris` pada fix ini.
```

@everyone
