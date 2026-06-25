# Tasks

## Bug Fixes
- [ ] Finish Toys/AXP validation from fix-toys-axp-flow.
- [x] Investigate and fix Bombox play log spam.
- [x] Investigate and fix schematic menu/log weapon mismatch.
- [x] Investigate and fix sidejobs route C/D.
- [x] Investigate and fix otot N neon camera zoom.
- [x] Investigate and fix /ostats wrong display.

## Features
- [x] Add /e animation dialog with ApplyAnimation entries.
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

- Sidejobs Route C/D root cause: Bus route C started/continued from BusRuteCD[step] -> [step+1] while step was initialized to 1, skipping the first route point. ContinueBusD reset BusCDSteps[playerid][0] instead of BusCDSteps[playerid][1], so route D did not restart from its route start.

- Neon N key root cause: OnPlayerKeyStateChange used a held-key check for KEY_NO, so /toglight could run repeatedly while N was held. Changed it to IsKeyJustDown(KEY_NO, newkeys, oldkeys) so light/neon toggles once per press.

- /ostats root cause: query selected admin as column 0, but LoadStats read column 0 as email. This shifted every offline stat field, causing faction/family/admin/helper labels to display wrong values. Added email to the select list and loaded gold from index 7.

- /e implementation: added dialog list that reuses existing animation commands through callcmd:: (`/sit`, `/lay`, `/wave`, `/handsup`, `/lean`, `/crossarms`, `/fall`, `/dance`). Existing looping animation flow still shows the SPACE stop textdraw and stops through KEY_SPRINT/space.
