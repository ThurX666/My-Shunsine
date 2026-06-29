# Phone UI Replacement — v1.0.21

## Goal
Replace existing `PhoneTD[33]` + 10 individual textdraws with unified `PhoneTD[51]` array using new layout data.

**File:** `gamemodes/Modules/PHONE.pwn`

---

## Changes Required

### 1. Array Size & Remove Individual Variables (lines 4-14)
- `new Text:PhoneTD[33];` → `new Text:PhoneTD[51];`
- Delete these 10 variables:
  `phoneclosetd`, `mesaagetd`, `contactstd`, `calltd`, `twittertd`, `banktd`, `apptd`, `gpstd`, `settingtd`, `cameratd`

### 2. Replace `CreatePhoneTD()` Content (lines 192-730)
- **Keep** the `CreatePhoneTD()` function shell
- **Delete** all existing PhoneTD[0]-PhoneTD[32] definitions (lines 194-643)
- **Delete** all individual textdraw creation (lines 644-730)
- **Insert** the 51 new textdraws using `PhoneTD[0]`–`PhoneTD[50]` naming (from user-provided `Text_Global[0]`–`Text_Global[50]` data)

### 3. Update Timer — Time Display (line 49)
- `TextDrawSetString(PhoneTD[13], datestring);` → `TextDrawSetString(PhoneTD[14], datestring);`

### 4. Update `OnPlayerClickTextDraw` (lines 63-189)
Replace individual variable comparisons with `PhoneTD[index]` comparisons:

| Old (variable) | New (index) | Action |
|---|---|---|
| `clickedid == phoneclosetd` | `clickedid == PhoneTD[12]` | Close phone |
| `clickedid == calltd` | `clickedid == PhoneTD[15]` | Dial number dialog |
| `clickedid == contactstd` | `clickedid == PhoneTD[16]` | ShowContacts |
| `clickedid == banktd` | `clickedid == PhoneTD[17]` | I-Bank dialog |
| `clickedid == gpstd` | `clickedid == PhoneTD[18]` | GPS menu |
| `clickedid == settingtd` | `clickedid == PhoneTD[19]` | Setting dialog |
| `clickedid == twittertd` | `clickedid == PhoneTD[21]` | Tweet/Twitter |
| `clickedid == cameratd` | `clickedid == PhoneTD[23]` | Selfie command |
| `clickedid == mesaagetd` | `clickedid == PhoneTD[24]` | Send SMS |
| `clickedid == apptd` | — | (HAPUS, tidak ada di layout baru) |

**New apps to wire:**
- `PhoneTD[20]` (Vallet/Wallet) → Dialog list: Cash Balance, Bank Balance, Close
- `PhoneTD[22]` (Ads) → Buka dialog ads/list iklan (sama seperti fitur iklan existing)

### 5. Update Close Handler (lines 155-171)
```
for(new i = 0; i < 51; i++) TextDrawHideForPlayer(playerid, PhoneTD[i]);
CancelSelectTextDraw(playerid);
```
Remove all individual `TextDrawHideForPlayer` calls (no longer needed since all 51 are in the array).

### 6. Update Show/Open Phone (lines 1003-1016)
```
for(new i = 0; i < 51; i++) TextDrawShowForPlayer(playerid, PhoneTD[i]);
SelectTextDraw(playerid, COLOR_LBLUE);
```
Remove all individual `TextDrawShowForPlayer` calls.

---

## App Index Mapping

| Index | App Name | Click Action | Icon Source |
|-------|----------|--------------|-------------|
| 12 | CLOSE | Close phone | LD_BEAT:chit |
| 15 | CALL | Dial number dialog | TextDraw[25]-[27] (dot+(+dot) |
| 16 | CONTACT | ShowContacts | TextDraw[28] (HUD:radar_saveGame) |
| 17 | M-BANK | I-Bank dialog | TextDraw[29] (HUD:radar_cash) |
| 18 | GPS | GPS menu | TextDraw[30] (HUD:radar_waypoint) |
| 19 | SETTINGS | Phone toggle | TextDraw[31] ("i" letter) |
| 20 | VALLET | Show money info | TextDraw[32]-[33] ("V" overlap) |
| 21 | TWEET | Twitter | TextDraw[34]-[35] ("T" overlap) |
| 22 | ADS | Ads list | TextDraw[36] ("Ads" text) |
| 23 | CAMERA | Selfie mode | TextDraw[37]-[39] (camera icon) |
| 24 | SMS | Send SMS dialog | TextDraw[40] (LD_CHAT:goodcha) |

**Row layout:**
- Row 1 (y=231): [15]x406, [16]x434, [17]x462, [18]x489
- Row 2 (y=272): [19]x406, [20]x434, [21]x462, [22]x489
- Row 3 (y=314): [23]x406, [24]x434

---

## Validation
1. Compile: `pawncc main.pwn -ipawno/include` → 0 errors
2. `/phone` → 51 textdraws render correctly
3. Click each of 10 apps → correct function triggered
4. Close button → phone hidden
5. Time display updates every second
6. No dangling references to deleted variables (`calltd`, `banktd`, etc.)
