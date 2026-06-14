-- Add dynamic column to workshop table
-- dynamic: 0 = Static (with objects/gate/board), 1 = Dynamic (point only)
ALTER TABLE `workshop` ADD COLUMN `dynamic` int(11) NOT NULL DEFAULT 0 AFTER `type`;

-- Update the CREATE TABLE definition for fresh installs:
-- (Replace the existing CREATE TABLE `workshop` with this)
CREATE TABLE `workshop` (
  `ID` int(11) NOT NULL,
  `name` varchar(52) NOT NULL,
  `owner` varchar(52) NOT NULL DEFAULT '-',
  `price` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `dynamic` int(11) NOT NULL DEFAULT 0,
  `cash` int(11) NOT NULL,
  `component` int(11) NOT NULL,
  `status` int(11) NOT NULL,
  `text` varchar(128) NOT NULL,
  `wspos` varchar(52) NOT NULL DEFAULT '0.00|0.00|0.00|0.00|0.00|0.00	',
  `gateposf` varchar(52) NOT NULL DEFAULT '0.00|0.00|0.00|0.00|0.00|0.00	',
  `gateposr` varchar(52) NOT NULL DEFAULT '0.00|0.00|0.00|0.00|0.00|0.00	',
  `boardpos` varchar(52) NOT NULL DEFAULT '0.00|0.00|0.00|0.00|0.00|0.00	'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;