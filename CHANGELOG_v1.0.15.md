# Changelog v1.0.15 - "Guard"

## Overview
A security-focused update that adds self-targeting validation across all sensitive money, currency, and item transfer commands to prevent economic exploits.

## Added
- **IsValidTarget Validation Include** (`gamemodes/Modules/Validation/IsValidTarget.inc`)
  - Connected into the main gamemode compilation chain

## Fixed
- **Admin Commands** - Added self-targeting protection (`IsValidTarget`) to 6 admin financial commands:
  - `/takemoney` - Prevented admins from taking money from themselves
  - `/takegold` - Prevented admins from taking gold from themselves
  - `/setmoney` - Prevented admins from setting money on themselves
  - `/setbankmoney` - Prevented admins from setting bank money on themselves
  - `/setgold` - Prevented admins from setting gold on themselves
  - `/givegold` - Prevented admins from giving gold to themselves

- **Business Commands** - Added self-targeting protection:
  - `/givebisnis` - Prevented players from transferring business ownership to themselves

## Changed
- Version updated from `1.0.14 "Fare"` to `1.0.15 "Guard"`
- `gamemodes/Modules/Define.pwn` - Updated TEXT_GAMEMODE define
- `gamemodes/Modules/Textdraw.pwn` - Updated login screen version textdraw
- Deleted deprecated CHANGELOG_v1.0.14.md

## Technical Details
- The `IsValidTarget(playerid, targetid)` stock function validates:
  - Target is not `INVALID_PLAYER_ID`
  - Target is connected (`IsPlayerConnected`)
  - Target is not the same as the command issuer (`playerid != targetid`)
- Pre-existing protections were already in place for `/pay` and `/transfer` commands

## Notes
- No new dependencies introduced
- All changes integrate into existing command modules
- Backward compatible - no breaking changes to valid use cases