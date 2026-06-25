# Change: Fix Toys AXP Flow Investigation

## Why
Toys dari /axp dan /toysaxp dilaporkan muncul lalu hilang. Investigasi sebelumnya salah menganggap RemoveFSToys(playerid) di OnPlayerSpawn sebagai root cause, padahal FSTOYS adalah temporary/preview toys dan cleanup spawn/disconnect kemungkinan memang dibutuhkan.

## What Changes
- Investigasi ulang flow cmd:axp dan cmd:toysaxp dari dialog select sampai SetPlayerAttachedObject.
- Bedakan temporary FSTOYS dari /axp / /toysaxp dengan persistent toys database aksesoris.
- Validasi apakah slot temporary toys 0-5 bentrok dengan weapon attached object cleanup di gamemodes/Modules/pTask.pwn.
- Patch hanya root cause yang terbukti; jangan hapus cleanup spawn/disconnect tanpa bukti.

## Out of Scope
- Bug schematic, Bombox, Sidejobs, /ostats, dan bug lain.
- Refactor besar sistem toys, weapon, atau database.
- Commit git.
