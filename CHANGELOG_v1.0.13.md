# Changelog v1.0.13

## Added

* **Door ASGH Basement** - Menambahkan door untuk akses basement ASGH.

* **Toggle Quiz and Votes** - Menambahkan dukungan `/toggle` untuk pesan Quiz and Votes.

## Changed

* **Buy Point Chainsaw** - Point pembelian chainsaw sudah diperbaiki agar flow pembelian lebih sesuai.

## Fixed Bugs

* **Chainsaw Damage Player** - Chainsaw sekarang tidak bisa memberikan damage ke player.

* **Wrong Enter Door ID** - Fix bug door tanpa interior yang bisa membuat player masuk dan ter-teleport ke ID door lain.

* **Quiz Broadcast** - Fix pesan quiz yang tidak muncul global setelah quiz berhasil dibuat.

**Catatan:**
```- Door yang belum memiliki interior sekarang tidak bisa dimasuki.
- Pesan Quiz and Votes mengikuti toggle player: enabled akan menerima pesan, disabled tidak menerima pesan.
- Gamemode sudah berhasil dicompile dengan `pawncc` tanpa error/warning setelah perubahan kode.```

@everyone
