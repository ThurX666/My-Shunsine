# Changelog v1.0.19 Milker

## Added

* **Sidejob Milker** - Sidejob baru memerah susu sapi! Player bisa `/startmilker` di locker area Blueberry, ikuti checkpoint ke 6 posisi sapi, tekan `N` atau `/perahsusu` untuk mulai memerah. Susu yang terkumpul diantar ke drop-off point. Selesaikan 10 siklus untuk gaji $250.
* **Faction Bank Locker** - Setiap faction (SAPD, SAGS, SAMD, SANA) kini memiliki bank sendiri di locker. Semua rank bisa deposit, hanya leader/deputy/commissioner (rank 14+) yang bisa withdraw. Dilengkapi transaction history 20 transaksi terakhir.
* **SAPD Rank 1-16** - Pangkat SAPD diperluas dari 6 menjadi 16 tingkatan dengan rank names (Recruit → Chief). Command `/setfaction`, `/osetfaction`, `/setrank`, `/setleader` sudah diupdate. Rank name otomatis terganti.

## Changed

* **Version bump** - Server version kini `v1.0.19 Milker`.

## Fixed

* **Inventory/Weapon Data Leak** - Memperbaiki bug dimana player bisa mendapatkan item random (drugs, weapons, materials) dari player sebelumnya. Root cause: callback `AssignPlayerData` tidak memiliki race check guard, sehingga data player lama bisa tertimpa ke player baru saat session ID reuse.
* **Anti-Cheat Weapon Saat Kerja** - Work tools (chainsaw, sekop, dll.) tidak lagi memicu false positive anti-cheat yang mereset senjata player. RefreshWeapon sekarang hanya berjalan untuk heavy weapons 34-38.
* **Fishing Tool & Umpan** - Tool pancing dan umpan sekarang hanya berkurang ketika ikan **berhasil** ditangkap, bukan setiap kali command `/fish` dipakai.

**Catatan:**
> _"Update ini fokus pada stabilitas data player dengan memperbaiki root cause item leak yang sudah lama dilaporkan. Sidejob Milker hadir sebagai aktivitas baru yang ringan dan menghasilkan. Selamat memerah susu!"_

@everyone
