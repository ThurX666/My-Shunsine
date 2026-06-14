# Changelog v1.0.9

## Added

* Workshop system kini mendukung **Dynamic Workshop** (tanpa object visual).
* `/workshop create` kini memiliki parameter baru: `[0.Transfender/1.WAA&Lowrider] [0.Static/1.Dynamic]`
  * **0.Static** — Workshop dengan object lengkap (model, board, gate) seperti sebelumnya.
  * **1.Dynamic** — Workshop berupa point saja, tanpa object, board, atau gate fisik.
* Dynamic Workshop otomatis menampilkan **3D Text Label** berisi informasi ID, Nama Workshop, Type, dan Owner.
  * Label akan muncul di posisi workshop dan dapat dilihat dari jarak 20 meter.
  * Untuk workshop yang belum dibeli, label menampilkan "For Sale".
* Menambahkan field `dynamic` di database tabel `workshop`.
* Menambahkan array global `WorkshopObj[MAX_WORKSHOP]` untuk object utama workshop (terpisah dari enum).
* Menambahkan array `WorkshopLabel[MAX_WORKSHOP]` untuk 3D Text Label dynamic workshop.

## Changed

* Refactor `ObjectWorkshop` dari dalam enum `workshop` dipindahkan ke array global `WorkshopObj[]` agar lebih efisien.
* `WorkshopRefresh` kini hanya membuat object visual (model, board, gate) jika workshop bertipe **Static**.
* `WorkshopRefresh` kini membuat 3D Text Label jika workshop bertipe **Dynamic**.
* `WorkshopSave` dan `WorkshopLoad` kini menyimpan dan membaca field `dynamic`.

## Fixed Bugs

* Dynamic Workshop tidak bisa diakses fitur gate, board, dan edit posisi object (akan ditolak dengan pesan error).
* Penghapusan workshop kini juga menghancurkan 3D Text Label jika ada.

## Technical

* Menambahkan file `workshop_alter.sql` untuk migrasi database (ALTER TABLE + CREATE TABLE baru).
* Menambahkan konstanta `dynamic` pada enum `workshop` dengan nilai default 0 (Static).

**📌 Perintah Baru**
```
/workshop [create] [0.Transfender/1.WAA&Lowrider] [0.Static/1.Dynamic]
```
Contoh Dynamic: `/workshop create 0 1` — membuat workshop Transfender Dynamic.
Contoh Static: `/workshop create 1 0` — membuat workshop WAA & Lowrider Static.

@everyone