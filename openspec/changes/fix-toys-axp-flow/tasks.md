# Tasks

- [x] Confirm Toys.pwn still has RemoveFSToys(playerid) in OnPlayerSpawn and OnPlayerDisconnect.
- [x] Document every temporary slot used by /axp category dialogs and /toysaxp VIP sets.
- [x] Document persistent aksesoris load/save/attach flow and confirm it is separate from FSTOYS.
- [x] Trace pTask.pwn weapon attached object cleanup and identify whether it can remove FSTOYS slot 5 incorrectly.
- [x] If conflict is proven, patch the smallest safe condition to protect temporary toys without breaking weapon cleanup.
- [x] Compile gamemodes/main.pwn after patch.

## Investigation Result

- Root cause proven in gamemodes/Modules/pTask.pwn: weapon cleanup removed any attached object in slots 5..8, even if the object was FSTOYS temporary preview.
- /axp uses temporary slots 0..5; /toysaxp VIP sets can use slots 0..6, so slots 5..6 overlapped weapon cleanup.
- Persistent aksesoris database flow remains separate and was not patched.
- Patch tracks weapon-attached objects before removing them, preserving temporary FSTOYS.
