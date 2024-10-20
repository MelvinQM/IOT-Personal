-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema database_name
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema database_name
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `database_name` ;
USE `database_name` ;

-- -----------------------------------------------------
-- Table `database_name`.`Player`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `database_name`.`Player` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `id_UNIQUE` (`id` ASC) VISIBLE)
ENGINE = InnoDB
AUTO_INCREMENT = 2;


-- -----------------------------------------------------
-- Table `database_name`.`Difficulty`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `database_name`.`Difficulty` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `id_UNIQUE` (`id` ASC) VISIBLE)
ENGINE = InnoDB
AUTO_INCREMENT = 2;


-- -----------------------------------------------------
-- Table `database_name`.`Session`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `database_name`.`Session` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `completed` TINYINT NULL DEFAULT 0,
  `start_time` DATETIME NULL,
  `end_time` DATETIME NULL,
  `player_id` INT(11) NULL,
  `difficulty_id` INT(11) NULL DEFAULT 1,
  `use_gyro` TINYINT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `id_UNIQUE` (`id` ASC) VISIBLE,
  INDEX `fk_session_player_idx` (`player_id` ASC) VISIBLE,
  INDEX `fk_session_difficulty_idx` (`difficulty_id` ASC) VISIBLE,
  CONSTRAINT `fk_session_player`
    FOREIGN KEY (`player_id`)
    REFERENCES `database_name`.`Player` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_session_difficulty`
    FOREIGN KEY (`difficulty_id`)
    REFERENCES `database_name`.`Difficulty` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 2;


-- -----------------------------------------------------
-- Table `database_name`.`Score`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `database_name`.`Score` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `session_id` INT(11) NOT NULL,
  `score` VARCHAR(45) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  INDEX `fk_score_session_idx` (`session_id` ASC) VISIBLE,
  CONSTRAINT `fk_score_session`
    FOREIGN KEY (`session_id`)
    REFERENCES `database_name`.`Session` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- -----------------------------------------------------
-- Data for table `database_name`.`Difficulty`
-- -----------------------------------------------------
START TRANSACTION;
USE `database_name`;
INSERT INTO `database_name`.`Difficulty` (`id`, `name`) VALUES (1, 'Easy');
INSERT INTO `database_name`.`Difficulty` (`id`, `name`) VALUES (2, 'Normal');
INSERT INTO `database_name`.`Difficulty` (`id`, `name`) VALUES (3, 'Hard');

COMMIT;

