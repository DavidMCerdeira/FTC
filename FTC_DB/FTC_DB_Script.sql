SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

DROP SCHEMA IF EXISTS `FTCdb` ;
CREATE SCHEMA IF NOT EXISTS `FTCdb` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `FTCdb` ;

-- -----------------------------------------------------
-- Table `FTCdb`.`Schedulle`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Schedulle` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Schedulle` (
  `idSchedulle` INT NOT NULL AUTO_INCREMENT,
  `enterTime` VARCHAR(45) NULL,
  `leaveTime` VARCHAR(45) NULL,
  PRIMARY KEY (`idSchedulle`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Jobs`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Jobs` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Jobs` (
  `idJob` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NULL,
  PRIMARY KEY (`idJob`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Sys_Privelege`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Sys_Privelege` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Sys_Privelege` (
  `idPrivelege` INT NOT NULL AUTO_INCREMENT,
  `description` VARCHAR(45) NULL,
  PRIMARY KEY (`idPrivelege`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Location`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Location` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Location` (
  `localName` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`localName`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Worker`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Worker` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Worker` (
  `idWorker` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(45) NOT NULL,
  `gender` VARCHAR(1) NOT NULL,
  `email` VARCHAR(100) NULL,
  `contact_number` VARCHAR(9) NOT NULL,
  `idSchedulle` INT NOT NULL,
  `localName` VARCHAR(45) NOT NULL,
  `idJob` INT NOT NULL,
  `face` VARCHAR(450) NULL,
  `idPrivelege` INT NOT NULL,
  `password` VARCHAR(15) NULL,
  PRIMARY KEY (`idWorker`),
  INDEX `fk_Schedulle_idx` (`idSchedulle` ASC),
  INDEX `fk_Job_idx` (`idJob` ASC),
  INDEX `fk_Priveledge_idx` (`idPrivelege` ASC),
  CONSTRAINT `fk_Schedulle`
    FOREIGN KEY (`idSchedulle`)
    REFERENCES `FTCdb`.`Schedulle` (`idSchedulle`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Job`
    FOREIGN KEY (`idJob`)
    REFERENCES `FTCdb`.`Jobs` (`idJob`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Privelege`
    FOREIGN KEY (`idPrivelege`)
    REFERENCES `FTCdb`.`Sys_Privelege` (`idPrivelege`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Local_`
    FOREIGN KEY ()
    REFERENCES `FTCdb`.`Location` ()
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Department`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Department` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Department` (
  `depName` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`depName`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`List_Department_Worker`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`List_Department_Worker` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`List_Department_Worker` (
  `depName` VARCHAR(45) NOT NULL,
  `idWorker` INT NOT NULL,
  PRIMARY KEY (`depName`, `idWorker`),
  INDEX `fk_Worker_idx` (`idWorker` ASC),
  CONSTRAINT `fk_Worker_LstDep`
    FOREIGN KEY (`idWorker`)
    REFERENCES `FTCdb`.`Worker` (`idWorker`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Department_`
    FOREIGN KEY (`depName`)
    REFERENCES `FTCdb`.`Department` (`depName`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Messages`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Messages` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Messages` (
  `idMessages` INT NOT NULL AUTO_INCREMENT,
  `content` VARCHAR(45) NULL,
  PRIMARY KEY (`idMessages`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`List_Sent_Messages`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`List_Sent_Messages` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`List_Sent_Messages` (
  `idMessages` INT NOT NULL,
  `idFromWorker` INT NOT NULL,
  PRIMARY KEY (`idMessages`, `idFromWorker`),
  INDEX `fk_Worker_idx` (`idFromWorker` ASC),
  CONSTRAINT `fk_Messages_sent`
    FOREIGN KEY (`idMessages`)
    REFERENCES `FTCdb`.`Messages` (`idMessages`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Worker_From`
    FOREIGN KEY (`idFromWorker`)
    REFERENCES `FTCdb`.`Worker` (`idWorker`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`List_Rcvd_Messages`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`List_Rcvd_Messages` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`List_Rcvd_Messages` (
  `idMessages` INT NOT NULL,
  `idToWorker` INT NOT NULL,
  PRIMARY KEY (`idMessages`, `idToWorker`),
  INDEX `fk_Worker_idx` (`idToWorker` ASC),
  CONSTRAINT `fk_Messages_rcvd`
    FOREIGN KEY (`idMessages`)
    REFERENCES `FTCdb`.`Messages` (`idMessages`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Worker_To`
    FOREIGN KEY (`idToWorker`)
    REFERENCES `FTCdb`.`Worker` (`idWorker`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Clock_In`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Clock_In` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Clock_In` (
  `idWorker` INT NOT NULL AUTO_INCREMENT,
  `dateTime` DATETIME NULL,
  PRIMARY KEY (`idWorker`),
  CONSTRAINT `fk_Worker_ClkIn`
    FOREIGN KEY (`idWorker`)
    REFERENCES `FTCdb`.`Worker` (`idWorker`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Clock_Out`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Clock_Out` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Clock_Out` (
  `idWorker` INT NOT NULL AUTO_INCREMENT,
  `dateTime` DATETIME NULL,
  PRIMARY KEY (`idWorker`),
  CONSTRAINT `fk_Worker__ClkOut`
    FOREIGN KEY (`idWorker`)
    REFERENCES `FTCdb`.`Worker` (`idWorker`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
