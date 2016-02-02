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
  `idSchedulle` INT NOT NULL,
  `enterTime` VARCHAR(45) NULL,
  `leaveTime` VARCHAR(45) NULL,
  PRIMARY KEY (`idSchedulle`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Location`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Location` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Location` (
  `idLocation` INT NOT NULL,
  `name` VARCHAR(45) NULL,
  PRIMARY KEY (`idLocation`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Jobs`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Jobs` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Jobs` (
  `idJob` INT NOT NULL,
  `name` VARCHAR(45) NULL,
  PRIMARY KEY (`idJob`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Priveledge`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Priveledge` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Priveledge` (
  `idPrivele` INT NOT NULL,
  `password` VARCHAR(45) NULL,
  `description` VARCHAR(45) NULL,
  PRIMARY KEY (`idPrivele`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Worker`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Worker` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Worker` (
  `idWorker` INT NOT NULL,
  `name` VARCHAR(45) NOT NULL,
  `gender` VARCHAR(1) NOT NULL,
  `email` VARCHAR(100) NULL,
  `contact_number` VARCHAR(9) NOT NULL,
  `idSchedulle` INT NOT NULL,
  `idLocation` INT NOT NULL,
  `idJob` INT NOT NULL,
  `face` VARCHAR(450) NULL,
  `idPriveledge` INT NOT NULL,
  PRIMARY KEY (`idWorker`),
  INDEX `fk_Schedulle_idx` (`idSchedulle` ASC),
  INDEX `fk_Location_idx` (`idLocation` ASC),
  INDEX `fk_Job_idx` (`idJob` ASC),
  INDEX `fk_Priveledge_idx` (`idPriveledge` ASC),
  CONSTRAINT `fk_Schedulle`
    FOREIGN KEY (`idSchedulle`)
    REFERENCES `FTCdb`.`Schedulle` (`idSchedulle`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Location`
    FOREIGN KEY (`idLocation`)
    REFERENCES `FTCdb`.`Location` (`idLocation`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Job`
    FOREIGN KEY (`idJob`)
    REFERENCES `FTCdb`.`Jobs` (`idJob`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Priveledge`
    FOREIGN KEY (`idPriveledge`)
    REFERENCES `FTCdb`.`Priveledge` (`idPrivele`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Department`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Department` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Department` (
  `idDepartment` INT NOT NULL,
  `name` VARCHAR(45) NULL,
  PRIMARY KEY (`idDepartment`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`List_Department_Worker`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`List_Department_Worker` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`List_Department_Worker` (
  `idDepartment` INT NOT NULL,
  `idWorker` INT NOT NULL,
  PRIMARY KEY (`idDepartment`, `idWorker`),
  INDEX `fk_Worker_idx` (`idWorker` ASC),
  CONSTRAINT `fk_Department`
    FOREIGN KEY (`idDepartment`)
    REFERENCES `FTCdb`.`Department` (`idDepartment`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Worker_LstDep`
    FOREIGN KEY (`idWorker`)
    REFERENCES `FTCdb`.`Worker` (`idWorker`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `FTCdb`.`Messages`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `FTCdb`.`Messages` ;

CREATE TABLE IF NOT EXISTS `FTCdb`.`Messages` (
  `idMessages` INT NOT NULL,
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
  `idWorker` INT NOT NULL,
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
  `idWorker` INT NOT NULL,
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
