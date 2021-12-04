CREATE TABLE `activations` (`id` SMALLINT PRIMARY KEY NOT NULL AUTO_INCREMENT,`profileid` SMALLINT,`starttime` TIME,`actuatorid` SMALLINT);
CREATE TABLE `actuators` (`id` SMALLINT PRIMARY KEY NOT NULL AUTO_INCREMENT,`name` VARCHAR,`roomid` SMALLINT,`state` boolean,`color` MEDIUMINT,`intensity` SMALLINT);
CREATE TABLE `profiles` (`id` SMALLINT PRIMARY KEY NOT NULL AUTO_INCREMENT, `userid` SMALLINT, `dayofweek` VARCHAR,`lastmodified` TIMESTAMP NOT NULL);
CREATE TABLE `rooms` (`id` SMALLINT PRIMARY KEY NOT NULL AUTO_INCREMENT,`userid` SMALLINT,`name` VARCHAR);
CREATE TABLE `sensors` (`id` SMALLINT PRIMARY KEY NOT NULL AUTO_INCREMENT,`name` VARCHAR,`roomid` SMALLINT,`lastpolled` TIMESTAMP NOT NULL,`added` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,`temp` SMALLINT,`lightlevel` SMALLINT);
CREATE TABLE `users` (`id` SMALLINT PRIMARY KEY NOT NULL AUTO_INCREMENT,`name` VARCHAR,`lastactive` TIMESTAMP, `created` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP);

ALTER TABLE `activations` ADD FOREIGN KEY (`profileid`) REFERENCES `profiles` (`id`);
ALTER TABLE `activations` ADD FOREIGN KEY (`actuatorid`) REFERENCES `actuators` (`id`);
ALTER TABLE `actuators` ADD FOREIGN KEY (`roomid`) REFERENCES `rooms` (`id`);
ALTER TABLE `profiles` ADD FOREIGN KEY (`userid`) REFERENCES `users` (`id`);
ALTER TABLE `rooms` ADD FOREIGN KEY (`userid`) REFERENCES `users` (`id`);
ALTER TABLE `sensors` ADD FOREIGN KEY (`roomid`) REFERENCES `rooms` (`id`);