# Changelog v1.0.19

## Bug Fixes
- **[Inventory/Weapon]** Fix cross-session data leak — `AssignPlayerData` callback sekarang pake `g_MysqlRaceCheck` untuk cegah data player sebelumnya (drugs, weapons, materials) ketimpa ke player baru saat session ID reuse. Root cause: race condition di `loadPlayerChars` → `AssignPlayerData` yang gak punya race check guard.
- **[Weapon]** Prevent anti-cheat `RefreshWeapon` dari trigger saat kerja — work tools (chainsaw, sekop, dll.) gak lagi trigger false positive yang reset senjata player. RefreshWeapon sekarang cuma jalan untuk heavy weapons 34-38.
- **[Fishing]** Fix `/fish` tidak dapat ikan — decrement `pWorm` dan `pFishTool` dipindah dari command `/fish` ke `AddFish()`. Tool dan umpan sekarang cuma berkurang ketika ikan **berhasil** ditangkap.

## Features
- **[SAPD]** Faction rank diperluas dari 6 menjadi 16 tingkatan dengan rank names (Recruit → Chief). Update `/setfaction`, `/osetfaction`, `/setrank`, `/setleader`. Auto-set rank name via `SetDefaultFactionRankName()`.
- **[Faction Bank]** Locker bank untuk semua faction (SAPD, SAGS, SAMD, SANA):
  - Deposit — semua rank bisa deposit
  - Withdraw — hanya leader/deputy/commissioner (rank 14+ atau FactionLead)
  - Transaction History — 20 transaksi terakhir dari tabel `factionmanage`
  - Balance tersimpan di database (Server_Save/LoadServer)
- **[Sidejob: Milker]** Sidejob baru memerah susu sapi:
  - `/startmilker` di locker (area Blueberry)
  - Random CP ke 6 posisi sapi
  - `/perahsusu` atau tekan `N` di dekat sapi → animasi squat 3 detik
  - Bucket susu ter-attach, bawa ke drop-off point
  - 10 siklus selesai → gaji $250 + cooldown 15 menit
  - 44 map objects (kandang, pagar, pohon, milk crate)

## Technical
- Compiled with Pawn 3.10.8 (0 errors, 0 warnings)
- Total requirements: ~145 MB
