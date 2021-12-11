CREATE DATABASE `appdb` CHARACTER SET utf8 COLLATE utf8_swedish_ci;
CREATE TABLE `activations` (`id` SMALLINT unsigned NOT NULL AUTO_INCREMENT,`profileid` SMALLINT unsigned,`starttime` TIME,`actuatorid` SMALLINT unsigned, PRIMARY KEY (id));
CREATE TABLE `actuators` (`id` SMALLINT unsigned NOT NULL AUTO_INCREMENT,`name` VARCHAR(30),`roomid` SMALLINT unsigned,`state` BOOLEAN NOT NULL DEFAULT 0,`color` MEDIUMINT NOT NULL,`intensity` SMALLINT, PRIMARY KEY (id));
CREATE TABLE `profiles` (`id` SMALLINT unsigned NOT NULL AUTO_INCREMENT, `userid` SMALLINT unsigned, `dayofweek` VARCHAR(3),`lastmodified` TIMESTAMP, PRIMARY KEY (id));
CREATE TABLE `rooms` (`id` SMALLINT unsigned NOT NULL AUTO_INCREMENT,`userid` SMALLINT unsigned,`name` VARCHAR(30), PRIMARY KEY (id));
CREATE TABLE `sensors` (`id` SMALLINT unsigned NOT NULL AUTO_INCREMENT,`name` VARCHAR(30),`roomid` SMALLINT unsigned,`lastpolled` TIMESTAMP NOT NULL,`added` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,`temp` SMALLINT,`lightlevel` SMALLINT, PRIMARY KEY (id));
CREATE TABLE `users` (`id` SMALLINT unsigned NOT NULL AUTO_INCREMENT,`name` VARCHAR(30),`lastactive` TIMESTAMP, `created` TIMESTAMP DEFAULT CURRENT_TIMESTAMP, PRIMARY KEY (id));

ALTER TABLE `activations` ADD FOREIGN KEY (`profileid`) REFERENCES `profiles` (`id`);
ALTER TABLE `activations` ADD FOREIGN KEY (`actuatorid`) REFERENCES `actuators` (`id`);
ALTER TABLE `actuators` ADD FOREIGN KEY (`roomid`) REFERENCES `rooms` (`id`);
ALTER TABLE `profiles` ADD FOREIGN KEY (`userid`) REFERENCES `users` (`id`);
ALTER TABLE `rooms` ADD FOREIGN KEY (`userid`) REFERENCES `users` (`id`);
ALTER TABLE `sensors` ADD FOREIGN KEY (`roomid`) REFERENCES `rooms` (`id`);