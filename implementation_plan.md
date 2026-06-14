# Implementation Plan

[Overview]  
The goal is to ensure that all sensitive commands related to currency or item transactions cannot target the issuing player. This includes commands like `/transfer`, `/pay`, `/give`, and their equivalents across various modules like PlayerCommand.inc, Bisnis System, AdminCommand, and ATM commands. This implementation aims to mitigate economic exploits, enabling a balanced and fair server economy while eliminating potential pathways for self-targeting abuses.

The implementation includes identifying and patching all self-targeting vulnerabilities, improving validation logic, and lastly, consolidating testing to prevent any unnoticed bypasses or loopholes.

[Types]  
No type changes are introduced in this implementation directly, but enhancements might involve logical checks on existing data types like `playerid` that redefine system interaction safety.

[Files]  
Modifications and reviews span multiple files where commands are implemented:
- **Player Commands**: `gamemodes/Modules/Command/PlayerCommand.inc`
- **Admin-Specific Commands**: `gamemodes/Modules/Command/AdminCommand.inc`
- **Business Commands**: `gamemodes/Modules/Property/bisnis/Command.inc`
- **ATM Commands**: `gamemodes/Modules/Dynamic/atm/cmd.inc`

Validation checks will be added across these commands to ensure safe targeting conditions.

[Functions]  
Precise function enhancements focus on existing command functions:
- **New Validation Logic Functions**:
  - `IsValidTarget(playerid, targetid)`:
    Verifies that target-id is connected, valid, and different from `playerid`.
  - Integration into existing command handlers like `/pay`, `/transfer`, `/givemoneyall`, `/charity`, `/givebisnis`, `/bwithdraw`.

- **Modified Commands**: Maintain logic integrity and improved parameters on existing handlers:
  - Add validation in `CMD:pay`, `CMD:givebisnis`, `CMD:bwithdraw`, and similar.

[Classes]  
No new classes required for this implementation.

[Dependencies]  
No new dependencies are introduced. All enhancements integrate directly into existing modules.

[Testing]  
Testing follows these strategies:
1. Unit Testing:
   - Test each command's behaviour using various edge cases.
   - Validate proper rejection of self-targeting attempts.
   - Confirm success with valid parameters.

2. Functional Testing:
   - Test transactional consistency across all interaction command implementations.
   - Simulate simultaneous misuse attempt scenarios to inspect economic safety.

3. QA Checklist:
   - Interactions involving self-target regression.
   - Transactional database effects won't show anomalies after validations.

[Implementation Order]  
1. Define the `IsValidTarget(playerid, targetid)` validation logic.
2. Integrate validation into key commands (Player Commands, Admin Commands, Business Commands, ATM Commands).
3. Patch existing commands with centralized validation logic and call appropriate validation/test function per module.
4. Unit-test individual commands for compliance.
5. Consolidate and confirm using functional economic test runs for potential bugs or bypasses.
6. Final post implementation deployment analysis.