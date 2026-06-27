-- Migration: Add faction bank columns to server table
-- Required for Faction Bank Locker feature

ALTER TABLE `server`
  ADD COLUMN `factionbanksapd` INT(11) NOT NULL DEFAULT 0 AFTER `balancesan`,
  ADD COLUMN `factionbanksags` INT(11) NOT NULL DEFAULT 0 AFTER `factionbanksapd`,
  ADD COLUMN `factionbanksamd` INT(11) NOT NULL DEFAULT 0 AFTER `factionbanksags`,
  ADD COLUMN `factionbanksan` INT(11) NOT NULL DEFAULT 0 AFTER `factionbanksamd`;
