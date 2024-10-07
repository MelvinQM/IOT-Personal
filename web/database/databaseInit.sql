-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema databasename
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema databasename
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `databasename` ;
USE `databasename` ;

-- -----------------------------------------------------
-- Table `databasename`.`Player`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `databasename`.`Player` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `id_UNIQUE` (`id` ASC) VISIBLE)
ENGINE = InnoDB
AUTO_INCREMENT = 2;


-- -----------------------------------------------------
-- Table `databasename`.`Difficulty`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `databasename`.`Difficulty` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `id_UNIQUE` (`id` ASC) VISIBLE)
ENGINE = InnoDB
AUTO_INCREMENT = 2;


-- -----------------------------------------------------
-- Table `databasename`.`Session`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `databasename`.`Session` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `completed` TINYINT NULL DEFAULT 0,
  `start_time` DATETIME NULL,
  `end_time` DATETIME NULL,
  `player_id` INT(11) NULL,
  `difficulty_id` INT(11) NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `id_UNIQUE` (`id` ASC) VISIBLE,
  INDEX `fk_session_player_idx` (`player_id` ASC) VISIBLE,
  INDEX `fk_session_difficulty_idx` (`difficulty_id` ASC) VISIBLE,
  CONSTRAINT `fk_session_player`
    FOREIGN KEY (`player_id`)
    REFERENCES `databasename`.`Player` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_session_difficulty`
    FOREIGN KEY (`difficulty_id`)
    REFERENCES `databasename`.`Difficulty` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 2;


-- -----------------------------------------------------
-- Table `databasename`.`Score`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `databasename`.`Score` (
  `id` INT(11) NOT NULL AUTO_INCREMENT,
  `session_id` INT(11) NOT NULL,
  `score` VARCHAR(45) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  INDEX `fk_score_session_idx` (`session_id` ASC) INVISIBLE,
  CONSTRAINT `fk_score_session`
    FOREIGN KEY (`session_id`)
    REFERENCES `databasename`.`Session` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
