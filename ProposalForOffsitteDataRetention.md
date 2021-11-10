CREATE DATABASE `smorts`;
USE smorts;
CREATE TABLE `lights` (`id` SMALLINT unsigned NOT NULL AUTO_INCREMENT,`name` TEXT,`status` BOOLEAN NOT NULL,`added` DATE,PRIMARY KEY (`id`));
CREATE TABLE `shutter` (`id` SMALLINT unsigned NOT NULL AUTO_INCREMENT,`status` BOOLEAN,`added` DATE,`location` VARCHAR,`name` VARCHAR,PRIMARY KEY (`id`));
CREATE TABLE `sensor` (`id` SMALLINT unsigned NOT NULL AUTO_INCREMENT,`level` SMALLINT unsigned,`lastchange` DATE,`added` DATE,`location` VARCHAR,PRIMARY KEY (`id`));
