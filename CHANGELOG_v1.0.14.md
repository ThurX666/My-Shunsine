# Changelog v1.0.14

## Fixed

* **CMD:joinjob** - Fix silent return saat player non-VIP daftar job2 di luar lokasi illegal jobs.
* **Dispatch Taxi/Mechanic (OnPlayerText)** - Fix operator precedence bug (`&&` vs `||`) pada filter taxi & mechanic dispatch. Sebelumnya `pJob == 1 || pJob2 == 1 && pTaxiDuty == 1` diartikan sebagai `pJob == 1` **OR** (`pJob2 == 1 && pTaxiDuty == 1`), menyebabkan primary job taxi driver menerima dispatch MESKIPUN off duty.
* **Dispatch Loop** - Fix `SendClientMessageEx(playerid, "Thank you...")` & `SetPlayerSpecialAction`, `pTaxiCall` dipanggil DI DALAM `foreach` loop, menyebabkan client menerima pesan berkali-kali & state ter-reset dalam loop. Dipindah ke luar `foreach`.
* **CMD:accepttaxi** - Tambah validasi `pTaxiDuty == 1`. Sebelumnya driver bisa accept order MESKIPUN off duty.
* **CMD:fare** - Fix `GetVehiclePassenger(vehicleid)` bisa return `INVALID_PLAYER_ID` saat passenger sudah turun. Sekarang pakai `pFarePassenger` (disimpan saat fare diaktifkan) & validasi `IsPlayerConnected()`.

## Added

* **CMD:buytaxi** di Job Help (DialogJobHelp case 0).
* **Enum `pFarePassenger`** - Variabel baru untuk menyimpan passenger ID saat fare aktif, agar safe saat deactivate.

## Changed

* **CMD:joinjob Error Messages** - Pesan error job2 non-VIP diubah jadi singkat & jelas.

## Job Taxi Flow

Berikut alur lengkap proses Job Taxi:

```
1. Daftar Job Taxi
   - /joinjob -> pilih Taxi Drivers (job ID 1)
   - Bisa slot pJob (primary) atau pJob2 (second)

2. Mulai Bekerja
   - /jobduty taxi -> set pTaxiDuty = 1, label kuning
   - /buytaxi -> beli kendaraan taxi (model 420 / 438)

3. Menerima Order (via Phone)
   - Client: /call 111 -> tulis "taxi" -> tulis lokasi
   - Dispatch kirim ke SEMUA driver yg on duty:
     "[DISPATCH] Client (ID) [Name] Last Know position: [loc]"
     "NOTE: Use '/accepttaxi [playerid]' to respond"
   - Driver: /accepttaxi [playerid]
     -> Set checkpoint ke lokasi client
     -> pTaxiCall client direset jadi -1

4. Penumpang Naik & Fare
   - Driver: /fare -> aktifkan argometer
     -> Timer FareUpdate tiap 1.1 detik
     -> Tambah $4-10 tiap 300 meter perjalanan
     -> TextDraw show fare amount
   - Matikan: /fare lagi
   
5. Selesai (Player keluar vehicle)
   - pTaxiDuty otomatis jadi 0
   - Fare otomatis dimatikan
```

**Catatan:**
```
- Non-VIP dengan 1 job terisi hanya bisa daftar illegal job sebagai job2.
- VIP (pVip > 3) tetap bisa daftar job apapun di slot 1 & 2.