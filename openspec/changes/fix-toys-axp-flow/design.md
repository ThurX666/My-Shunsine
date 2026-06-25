# Design: Toys AXP Flow Investigation

## Current Concepts
- FSTOYS temporary/preview toys berada di gamemodes/Modules/Toys.pwn dan dipasang langsung lewat SetPlayerAttachedObject oleh /axp dan /toysaxp.
- Persistent toys database berada di sistem aksesoris: LoadPlayerToys, MySQL_SavePlayerToys, Aksesoris_Attach, dan Dyoc_Attach.
- RemoveFSToys(playerid) membersihkan attached object temporary dan tetap boleh dipanggil saat spawn/disconnect jika terbukti hanya membersihkan FSTOYS.

## Investigation Targets
- Trace cmd:axp -> dialog 2000 -> dialog 2001..2006 -> SetPlayerAttachedObject slot 0..5.
- Trace cmd:toysaxp -> dialog 3000 -> ApplyToySet -> RemoveFSToys -> SetPlayerAttachedObject set VIP.
- Trace weapon cleanup di pTask.pwn, terutama loop slot 5..8 dan GetWeaponObjectSlot(weaponid).
- Buktikan apakah object slot 5 dari temporary toys dihapus oleh weapon cleanup saat player tidak punya weapon di slot terkait.

## Patch Constraints
- Jangan ubah persistent aksesoris kecuali root cause terbukti di boundary temporary/persistent.
- Jangan hapus OnPlayerSpawn atau OnPlayerDisconnect cleanup dari Toys.pwn tanpa bukti kuat.
- Patch maksimal di file yang langsung terkait flow temporary toys atau cleanup weapon slot.
