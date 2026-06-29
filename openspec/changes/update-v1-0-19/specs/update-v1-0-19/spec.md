## ADDED Requirements

### Requirement: SAPD rank system shall support 16 ranks including Chief
SAPD faction must have ranks 1 through 16, with rank 16 designated as Chief.

#### Scenario: Leader can promote to rank 16 (Chief)
- GIVEN a SAPD leader uses promote command
- WHEN promoting a member
- THEN ranks 1 through 16 are valid targets, with rank 16 labeled "Chief"

### Requirement: Faction bank locker shall restrict withdraw by rank
Each faction locker must have a bank menu where deposit is available to all ranks and withdraw is restricted to leader, deputy, and commissioner.

#### Scenario: Non-leader rank cannot withdraw
- GIVEN a faction member who is not leader/deputy/commissioner
- WHEN the member selects withdraw in faction bank
- THEN the system rejects the action

#### Scenario: All ranks can deposit
- GIVEN any faction member
- WHEN the member selects deposit in faction bank
- THEN the deposit is accepted

### Requirement: Sidejob Milker shall use the specified flow and coordinates
The Milker sidejob must implement: locker start → CP at cow positions → /perahsusu or KEY_NO to milk → squat animation → carry box → deliver to drop-off point → repeat 10x → finish → salary $250.

#### Scenario: Player completes 10 milk cycles
- GIVEN a player starts the Milker sidejob
- WHEN the player milks all 10 cows and drops off milk each time
- THEN the job completes and the player receives $250

### Requirement: Bug weapon spawn shall be investigated before patching
Weapon random appearance during work must have root cause identified in code before any patch.

#### Scenario: Weapon source is traced
- GIVEN a player working a job
- WHEN AK47/Sawnoff/Deagle/MP5 appears unexpectedly
- THEN the investigation identifies which code path gave the weapon

### Requirement: Bug /fish shall be investigated before patching
Fishing not giving fish must have root cause identified before any patch.

#### Scenario: Fish reward flow is traced
- GIVEN a player uses /fish
- WHEN the fishing dialog/minigame completes successfully
- THEN the investigation identifies where the reward assignment fails
