## ADDED Requirements

### Requirement: v1.0.18 changes shall match requested scope
The implementation MUST only include features and bug fixes listed in the v1.0.18 request.

#### Scenario: Release changelog is generated from actual changes
- GIVEN a change is implemented for v1.0.18
- WHEN CHANGELOG_v1.0.18.md is updated
- THEN it lists only changes that were actually made or investigated

### Requirement: Bugs shall be investigated before patching
Bug fixes MUST identify root cause in code before changing behavior.

#### Scenario: Bug patch is evidence based
- GIVEN a reported bug
- WHEN a patch is proposed
- THEN the relevant source flow and root cause have been traced first

### Requirement: Requested features shall use existing systems first
New features MUST reuse existing commands, dialogs, salary data, family data, and animation patterns where available.

#### Scenario: Feature implementation reuses current data
- GIVEN a requested v1.0.18 feature overlaps existing gamemode data or commands
- WHEN the feature is implemented
- THEN it reuses the existing source of truth instead of hardcoding a conflicting duplicate
