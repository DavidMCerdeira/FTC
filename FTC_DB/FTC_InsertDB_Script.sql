USE FTCdb;

#INSERT PRIVELEGES
INSERT INTO Sys_Privelege (description) values ("lower");
INSERT INTO Sys_Privelege (description) values ("medium");
INSERT INTO Sys_Privelege (description) values ("higher");

#INSERT LOCATIONS
INSERT INTO Location (localName) values ("VIANA DO CASTELO");
INSERT INTO Location (localName) values ("BRAGA");
INSERT INTO Location (localName) values ("PORTO");
INSERT INTO Location (localName) values ("AVEIRO");
INSERT INTO Location (localName) values ("COIMBRA");
INSERT INTO Location (localName) values ("LEIRIA");
INSERT INTO Location (localName) values ("LISBOA");
INSERT INTO Location (localName) values ("SETUBAL");
INSERT INTO Location (localName) values ("BEJA");
INSERT INTO Location (localName) values ("FARO");
INSERT INTO Location (localName) values ("ÉVORA");
INSERT INTO Location (localName) values ("PORTALEGRE");
INSERT INTO Location (localName) values ("SANTARÉM");
INSERT INTO Location (localName) values ("CASTELO BRANCO");
INSERT INTO Location (localName) values ("GUARDA");
INSERT INTO Location (localName) values ("VISEU");
INSERT INTO Location (localName) values ("VILA REAL");
INSERT INTO Location (localName) values ("BRAGANÇA");

#INSERT DEPARTMENTS
INSERT INTO Department (depName) values ("ESRG");
INSERT INTO Department (depName) values ("CAR");
INSERT INTO Department (depName) values ("GEPE");
INSERT INTO Department (depName) values ("IST");

#INSERT JOBS
INSERT INTO Jobs (jobName) values ("Embedded Systems Engineer");
INSERT INTO Jobs (jobName) values ("Test Engineer");
INSERT INTO Jobs (jobName) values ("Robotics Engineer");
INSERT INTO Jobs (jobName) values ("Mechanical Engineer");
INSERT INTO Jobs (jobName) values ("GOAT");
