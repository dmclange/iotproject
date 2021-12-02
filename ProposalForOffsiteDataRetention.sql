CREATE TABLE `activations` (
  `id` SMALLINT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  `profileid` SMALLINT,
  `starttime` TIME,
  `actuatorid` SMALLINT
);

CREATE TABLE `actuators` (
  `id` SMALLINT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  `name` VARCHAR,
  `roomid` SMALLINT,
  `state` boolean,
  `color` MEDIUMINT,
  `intensity` SMALLINT
);

CREATE TABLE `profiles` (
  `id` SMALLINT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  `userid` SMALLINT,
  `dayofweek` VARCHAR,
  `lastmodified` TIMEDATE
);

CREATE TABLE `rooms` (
  `id` SMALLINT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  `userid` SMALLINT,
  `name` VARCHAR
);

CREATE TABLE `sensors` (
  `id` SMALLINT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  `name` VARCHAR,
  `roomid` SMALLINT,
  `lastpolled` TIMEDATE,
  `added` TIMEDATE,
  `temp` SMALLINT,
  `lightlevel` SMALLINT
);

CREATE TABLE `users` (
  `id` SMALLINT PRIMARY KEY NOT NULL AUTO_INCREMENT,
  `name` VARCHAR,
  `created` TIMEDATE,
  `lastactive` TIMEDATE
);

ALTER TABLE `activations` ADD FOREIGN KEY (`profileid`) REFERENCES `profiles` (`id`);

ALTER TABLE `activations` ADD FOREIGN KEY (`actuatorid`) REFERENCES `actuators` (`id`);

ALTER TABLE `actuators` ADD FOREIGN KEY (`roomid`) REFERENCES `rooms` (`id`);

ALTER TABLE `profiles` ADD FOREIGN KEY (`userid`) REFERENCES `users` (`id`);

ALTER TABLE `rooms` ADD FOREIGN KEY (`userid`) REFERENCES `users` (`id`);

ALTER TABLE `sensors` ADD FOREIGN KEY (`roomid`) REFERENCES `rooms` (`id`);
