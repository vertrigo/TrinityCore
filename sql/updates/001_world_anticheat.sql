REPLACE INTO `command` (`name`,`security`,`help`) VALUES ('anticheat global', '2', 'Syntax: .anticheat
global returns the total amount reports and the average. (top three players)'), ('anticheat player', '2',
'Syntax: .anticheat player $name returns the players''s total amount of warnings, the average and the
amount of each cheat type.'), ('anticheat handle', '2', 'Syntax: .anticheat handle [on|off] Turn on/off the
AntiCheat-Detection .'),
('anticheat delete', '2', 'Syntax: .anticheat delete [deleteall|$name] Deletes the report records of all the players or deletes all the reports of player $name.');

REPLACE INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES
(11002, '|cFFFFFC00[ANTICHEAT]|cFF00FFFF[|cFF60FF00%s|cFF00FFFF] Banned for cheating!|r', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

