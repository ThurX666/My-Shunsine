# Tasks

## Bug Fixes
- [ ] Finish Toys/AXP validation from fix-toys-axp-flow.
- [x] Investigate and fix Bombox play log spam.
- [x] Investigate and fix schematic menu/log weapon mismatch.
- [ ] Investigate and fix sidejobs route C/D.
- [ ] Investigate and fix otot N neon camera zoom.
- [ ] Investigate and fix /ostats wrong display.

## Features
- [ ] Add /e animation dialog with ApplyAnimation entries.
- [ ] Add autorp handling in OnPlayerText without slash commands.
- [ ] Add /gajiserver from actual job/sidejob salaries.
- [ ] Add +2 non-VIP toys slots.
- [ ] Add family member list to /finfo.
- [ ] Add offline family kick through /osetfamily <id> 0.

## Release
- [ ] Compile gamemodes/main.pwn.
- [ ] Update CHANGELOG_v1.0.18.md with implemented changes only.

## Investigation Notes

- Schematic root cause: /buyschematic used DIALOG_STYLE_LIST with a header row, causing listitem to shift by one. Switched to DIALOG_STYLE_TABLIST_HEADERS so Desert Eagle, MP5, and AK47 map to the intended cases.

- Bombox root cause: OnPlayerEnterDynamicArea had a duplicate boombox loop that replayed audio and sent SendCustomMessage to the boombox owner every time any player entered the radio area. Removed the duplicate block; the first enter-area handler still plays audio for the entering player.
