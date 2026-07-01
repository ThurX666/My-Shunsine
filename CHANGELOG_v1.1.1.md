# Changelog v1.1.1 — Hotfix

## Added

Tidak ada fitur baru di patch ini — fokus penuh pada perbaikan bug.

## Fixed

* **/pay — Dollar-Cents Input Support** — Command `/pay` sekarang support input dengan desimal. Sebelumnya harus ketik `5000` untuk kirim $50, sekarang bisa langsung ketik `50` atau `50.50` atau `0.01`. Format lama `5000` masih work.
* **/givemoneyall — Dollar-Cents Input Support** — Sama seperti `/pay`, admin sekarang bisa kasih uang ke semua player dengan `50` (bukan `5000`).
* **/setfaction 0 — Rank Jadi Opsional** — Saat admin ingin mengeluarkan player dari faction, tidak perlu lagi mengetik rank. Cukup `/setfaction [playerid] 0` dan selesai.
* **/deposit, /withdraw, /transfer — Decimal Input** — Semua command ATM di bank sekarang support input desimal ($0.01, $50.50, dll). Sebelumnya harus ketik cents mentah.
* **$$ Double Dollar Fix** — Tampilan harga di semua toko bisnis (Electronic, 24/7, Clothes, Sports, GYM, Food, Weapon) sekarang pakai 1 dollar saja, bukan 2 (contoh: `$1,500.00` bukan `$$1,500.00`). Fix 152 tempat di bisnis dialog.

## Changed

Tidak ada perubahan besar.

## Catatan

> _"v1.1.1 adalah hotfix untuk v1.1.0 REFACTOR. Fokus pada bug fix command uang (/pay, /givemoneyall, /deposit, /withdraw, /transfer) yang sekarang support input desimal dollar-cents, fix double dollar di display bisnis, dan /setfaction 0 tidak perlu rank. SQL migration tetap sama dengan v1.1.0."_

@everyone
