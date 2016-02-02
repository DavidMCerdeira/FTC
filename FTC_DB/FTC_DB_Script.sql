SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`Schedulle`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Schedulle` (
  `idSchedulle` INT NOT NULL,
  `enterTime` VARCHAR(45) NULL,
  `leaveTime` VARCHAR(45) NULL,
  PRIMARY KEY (`idSchedulle`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Location`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Location` (
  `idLocation` INT NOT NULL,
  `name` VARCHAR(45) NULL,
  PRIMARY KEY (`idLocation`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Jobs`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Jobs` (
  `idJob` INT NOT NULL,
  `name` VARCHAR(45) NULL,
  PRIMARY KEY (`idJob`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Priveledge`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Priveledge` (
  `idPrivele` INT NOT NULL,
  `password` VARCHAR(45) NULL,
  `description` VARCHAR(45) NULL,
  PRIMARY KEY (`idPrivele`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Worker`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Worker` (
  `idWorker` INT NOT NULL,
  `name` VARCHAR(45) NULL,
  `gender` VARCHAR(1) NULL,
  `email` VARCHAR(100) NULL,
  `contact_number` VARCHAR(9) NULL,
  `idSchedulle` INT NULL,
  `idLocation` INT NULL,
  `idJob` INT NULL,
  `face` VARCHAR(450) NULL,
  `idPriveledge` INT NULL,
  PRIMARY KEY (`idWorker`),
  INDEX `fk_Schedulle_idx` (`idSchedulle` ASC),
  INDEX `fk_Location_idx` (`idLocation` ASC),
  INDEX `fk_Job_idx` (`idJob` ASC),
  CONSTRAINT `fk_Schedulle`
    FOREIGN KEY (`idSchedulle`)
    REFERENCES `mydb`.`Schedulle` (`idSchedulle`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Location`
    FOREIGN KEY (`idLocation`)
    REFERENCES `mydb`.`Location` (`idLocation`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Job`
    FOREIGN KEY (`idJob`)
    REFERENCES `mydb`.`Jobs` (`idJob`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Priveledge`
    FOREIGN KEY ()
    REFERENCES `mydb`.`Priveledge` ()
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Department`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Department` (
  `idDepartment` INT NOT NULL,
  `name` VARCHAR(45) NULL,
  PRIMARY KEY (`idDepartment`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`List_Department_Worker`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`List_Department_Worker` (
  `idDepartment` INT NOT NULL,
  `idWorker` INT NOT NULL,
  PRIMARY KEY (`idDepartment`, `idWorker`),
  INDEX `fk_Worker_idx` (`idWorker` ASC),
  CONSTRAINT `fk_Department`
    FOREIGN KEY (`idDepartment`)
    REFERENCES `mydb`.`Department` (`idDepartment`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Worker`
    FOREIGN KEY (`idWorker`)
    REFERENCES `mydb`.`Worker` (`idWorker`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Messages`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Messages` (
  `idMessages` INT NOT NULL,
  `content` VARCHAR(45) NULL,
  PRIMARY KEY (`idMessages`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`List_Sent_Messages`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`List_Sent_Messages` (
  `idMessages` INT NOT NULL,
  `idFromWorker` INT NOT NULL,
  PRIMARY KEY (`idMessages`, `idFromWorker`),
  INDEX `fk_Worker_idx` (`idFromWorker` ASC),
  CONSTRAINT `fk_Messages`
    FOREIGN KEY (`idMessages`)
    REFERENCES `mydb`.`Messages` (`idMessages`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Worker`
    FOREIGN KEY (`idFromWorker`)
    REFERENCES `mydb`.`Worker` (`idWorker`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`List_Rcvd_Messages`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`List_Rcvd_Messages` (
  `idMessages` INT NOT NULL,
  `idToWorker` INT NOT NULL,
  PRIMARY KEY (`idMessages`, `idToWorker`),
  INDEX `fk_Worker_idx` (`idToWorker` ASC),
  CONSTRAINT `fk_Messages`
    FOREIGN KEY (`idMessages`)
    REFERENCES `mydb`.`Messages` (`idMessages`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Worker`
    FOREIGN KEY (`idToWorker`)
    REFERENCES `mydb`.`Worker` (`idWorker`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Clock_In`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Clock_In` (
  `idWorker` INT NOT NULL,
  `dateTime` DATETIME NULL,
  PRIMARY KEY (`idWorker`),
  CONSTRAINT `fk_Worker`
    FOREIGN KEY (`idWorker`)
    REFERENCES `mydb`.`Worker` (`idWorker`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Clock_Out`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mydb`.`Clock_Out` (
  `idWorker` INT NOT NULL,
  `dateTime` DATETIME NULL,
  PRIMARY KEY (`idWorker`),
  CONSTRAINT `fk_Worker`
    FOREIGN KEY (`idWorker`)
    REFERENCES `mydb`.`Worker` (`idWorker`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
