# Tasks

## Bug Investigation
- [x] Investigate weapon random muncul saat kerja (AK47, Sawnoff, Deagle, MP5).
- [x] Investigate /fish tidak dapat ikan.

## Bug Fix
- [x] Fix weapon random muncul saat kerja — narrowed RefreshWeapon trigger to heavy 34-38 only.
- [x] Fix /fish reward flow — move decrement from /fish to AddFish().

## Features
- [x] SAPD rank 1-16: trace existing rank definition.
- [x] SAPD rank 1-16: extend rank array/config to 16.
- [x] SAPD rank 1-16: update promote/demote, locker, gaji commands.
- [x] Faction bank locker: create tabel `faction_bank` (faction_id, balance, logs).
- [x] Faction bank locker: add deposit menu — all ranks can deposit.
- [x] Faction bank locker: add withdraw menu — leader/deputy/commissioner only.
- [x] Faction bank locker: add transaction log.
- [x] Sidejob Milker: load map objects in OnGameModeInit.
- [x] Sidejob Milker: implement start job at locker.
- [x] Sidejob Milker: implement CP random at cow positions (6 points).
- [x] Sidejob Milker: implement /perahsusu and KEY_NO handler.
- [x] Sidejob Milker: implement squat animation + carry box attach.
- [x] Sidejob Milker: implement drop-off at milk storage point.
- [x] Sidejob Milker: implement 10x cycle counter and salary $250.

## Release
- [ ] Compile gamemodes/main.pwn.
- [ ] Update CHANGELOG with v1.0.19 changes.
