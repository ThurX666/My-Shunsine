# Change: Update Gamemode v1.0.19

## Why
Kumpulan request update dan bug fix dari player setelah v1.0.18. Mencakup fitur faction bank locker, sidejob baru, perbaikan rank SAPD, dan bug report senjata random + fishing.

## What Changes
- **SAPD Rank 1-16**: Tambah rank SAPD dari 1 sampai 16, termasuk Chief (rank 16).
- **Faction Bank Locker**: Tambah faction bank locker di setiap locker faction. Withdraw hanya untuk leader, deputy, commissioner. Deposit untuk semua rank.
- **Bug Weapon Random**: Investigasi kenapa saat bekerja tiba-tiba muncul senjata AK47, Sawnoff, Deagle, MP5.
- **Bug /fish**: Investigasi kenapa /fish tidak memberikan ikan.
- **Sidejob Milker (Pemerah Susu)**: Job baru dengan flow: start di locker → CP random ke sapi → /perahsusu atau N untuk memerah → animasi jongkok → angkat box → bawa ke tempat menaruh susu → ulangi 10x → selesai → salary $250.
- Map objects sidejob milker sudah disediakan oleh requester (file texture studio).

## Out of Scope
- Refactor besar sistem rank faction.
- Perubahan sistem weapon attachment di luar scope investigasi bug.
- Sidejob lain di luar Milker.
- Commit otomatis.
