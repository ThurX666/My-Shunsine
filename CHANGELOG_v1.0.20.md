# Changelog v1.0.20

## Added

* **`/showlic`** - Command baru untuk menampilkan semua lisensi (Driver, Boat, Gun, Fly, Trucker) ke player lain di dekat anda. Sama seperti `/showidcard` tapi khusus lisensi.
* **Special Tag `@` di `/me`** - Sekarang `/me` mendukung tag `@playerid` yang otomatis diganti jadi nama player. Contoh: `/me mendorong @1` akan menampilkan `* Diego Theodore mendorong Diego Theodore`. Bisa multiple tag: `/me melihat @2 dan @3` jadi `* Diego Theodore melihat Jane Doe dan John Smith`.
* **Rank Names Semua Faction** - Tambah rank names default untuk SAGS (Intern → Governor), SAMD (Intern → Chief), dan SANA (Intern → Chief), selain SAPD yang sudah ada.
* **Phone Book di Electronic Store** - Produk baru (slot bPName4) di bisnis tipe Electronic. Player bisa beli Phone Book untuk akses manajemen kontak HP langsung dari toko.
* **Auto-RP `rpperiksa` untuk SAMD** - Medic SAMD bisa chat "rpperiksa" (exact lowercase) untuk auto-RP memeriksa kesehatan player terdekat dalam 5 meter.
* **Dynamic Pickup & Label di Milker** - Information icon (model 1239) dan 3D label di semua titik Milker (locker, 6 sapi, drop-off) dengan stream distance 30.0, membantu player menemukan area sidejob.
* **Phone UI Baru** - Layout phone dirombak total: 51 textdraws (sebelumnya 33 + 10 individual). App grid 4×3 rapi: 15=Call, 16=Contact, 17=M-Bank, 18=GPS, 19=Settings, 20=Vallet, 21=Tweet, 22=Ads, 23=Camera, 24=SMS. Close di index 12. App Store (IsiKuota) dihapus.

## Fixed

* **Pemerah Susu (Milker) Sidejob** - Beberapa bug diperbaiki:
  - `/startmilker` sekarang set `pSideJob` agar tidak konflik dengan sidejob lain (Courier, Forklift, dll).
  - Tombol `N` dan `/perahsusu` yang tidak bereaksi diperbaiki - sekarang key detection pakai edge-trigger (`!(oldkeys & KEY_NO)`) dan cek `PLAYER_STATE_ONFOOT`.
  - Cooldown Milker dipisah dari Courier (`DelayCourier` → `DelayMilker` baru) agar tidak saling timpang.
  - Gaji Milker sekarang masuk ke paycheck (`AddPlayerSalary`) konsisten dengan sidejob lain, bukan cash langsung.
  - Tambahan guard agar tidak bisa perah susu 2x sebelum mengantar susu sebelumnya ke drop-off point.
  - Dialog info saat memulai sidejob menampilkan target siklus, posisi sapi, dan gaji.
* **Rank SAPD/Faction Berantakan** - `SetDefaultFactionRankName` sebelumnya hanya handle SAPD, sehingga faction lain (SAGS, SAMD, SANA) kehilangan rank name saat `/setrank` atau accept invite. Sekarang semua faction punya rank name default masing-masing via `switch`.
* **Bug `TogAuto` Save** - Perbaiki parameter duplikat `pTogHandbrake` di `mysql_format` save settings (8 format specifier tapi 9 argumen).
* **Boombox radius 30.0 → 15.0** - Radius audio boombox dikurangi menjadi 15 meter sesuai laporan player suara masih terdengar dari jarak 4 kilometer.

## Changed

* **Version bump** - Server version kini `v1.0.20`.
* **Delay enum** - Tambah `DelayMilker` ke enum `delayplayer`, save/load MySQL, countdown timer, dan dialog `/delays`.
* **Phone UI** - `PhoneTD[33]` + 10 individual textdraws diganti jadi `PhoneTD[51]` dengan layout baru. Semua variable `calltd`, `banktd`, `mesaagetd`, dll. dihapus, diganti index-based click handler.

**Catatan:**
> _"Update ini fokus memperbaiki sidejob Milker, merombak total UI phone, menambah /showlic, @mention di /me, phone book di electronic store, rpperiksa SAMD, pickup/label Milker, merapikan rank name faction, dan mengecilkan radius boombox ke 15m."_

@everyone
