# Design: Gamemode v1.0.18

## Execution Order
1. Investigasi bug sampai root cause terbukti.
2. Patch bug prioritas dengan diff kecil.
3. Implement fitur baru sesuai request.
4. Compile/test setelah setiap area besar.
5. Update CHANGELOG_v1.0.18.md dari perubahan aktual.

## Feature Targets
- /e membuka dialog list animasi dan pilihan langsung ApplyAnimation.
- Autorp ditangani di OnPlayerText tanpa slash.
- /gajiserver membaca/menampilkan salary sesuai job dan sidejob asli.
- Toys non-VIP bertambah 2 slot tanpa bergantung /toysaxp VIP.
- /finfo menampilkan list member family.
- /osetfamily <id> 0 mengeluarkan player offline dari family.

## Bug Targets
- Toys/AXP: temporary FSTOYS tidak hilang karena cleanup weapon slot.
- Bombox: log play cukup 1x per aksi/session yang relevan.
- Schematic: text/log pembelian sesuai item menu.
- Sidejobs route C/D: root cause dicari sebelum patch.
- Neon otot N: kamera tidak zoom saat toggle neon.
- /ostats: faction/family/admin/OOC display sesuai data sebenarnya.
