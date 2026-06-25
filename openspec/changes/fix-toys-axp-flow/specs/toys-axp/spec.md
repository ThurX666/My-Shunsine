## ADDED Requirements

### Requirement: Toys AXP flow shall be investigated before patching
The implementation MUST trace temporary Toys AXP behavior before changing cleanup logic.

#### Scenario: Temporary FSTOYS are selected from /axp
- GIVEN a player uses cmd:axp
- WHEN the player selects a toy category and toy item
- THEN the selected item is applied as temporary/preview attached object using the intended slot

#### Scenario: VIP FSTOYS are selected from /toysaxp
- GIVEN a VIP player uses cmd:toysaxp
- WHEN the player selects a VIP toy set
- THEN old temporary toys are cleared and the selected VIP set is applied without touching persistent database toys

### Requirement: Temporary and persistent toys shall remain distinct
The implementation MUST NOT treat FSTOYS temporary/preview toys as persistent aksesoris database toys.

#### Scenario: Persistent toys load separately
- GIVEN persistent toys exist in aksesoris storage
- WHEN LoadPlayerToys, Aksesoris_Attach, or Dyoc_Attach runs
- THEN that flow remains separate from /axp and /toysaxp temporary preview toys

### Requirement: Cleanup shall preserve intended behavior
RemoveFSToys(playerid) in spawn/disconnect cleanup MUST remain unless code evidence proves it deletes persistent toys or causes the reported temporary toy disappearance.

#### Scenario: Weapon cleanup is evaluated for slot conflicts
- GIVEN pTask.pwn removes attached objects in weapon slots
- WHEN temporary toys use overlapping attached object slots
- THEN the implementation protects temporary toys only if an actual slot cleanup conflict is proven
