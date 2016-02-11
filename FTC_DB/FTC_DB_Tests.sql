#Worker Insertion Query
INSERT INTO Worker (name, gender, email, contact_number, localName, idJob, idPrivelege)
VALUES ("joão", "M", "joaoalves@FTC.com", "123123123", "PORTO", 1,  1);
INSERT INTO List_Department_Worker (idDepartment, idWorker) VALUES(1, 1);

INSERT INTO Worker (name, gender, email, contact_number, localName, idJob, idPrivelege)
VALUES ("david", "F", "Davidcerdeira@FTC.com", "234234234", "GUARDA", 1, 1);
INSERT INTO List_Department_Worker (idDepartment, idWorker) VALUES(1, 2);

INSERT INTO Worker (name, gender, email, contact_number, localName, idJob, idPrivelege)
VALUES ("José", "M", "JoseMartins@FTC.com", "234234234", "GUARDA", 2, 1);
INSERT INTO List_Department_Worker (idDepartment, idWorker) VALUES(4, 3);

INSERT INTO Worker (name, gender, email, contact_number, localName, idJob, idPrivelege)
VALUES ("Paulo", "F", "PauloFelix@FTC.com", "234234234", "BRAGA", 3, 1);
INSERT INTO List_Department_Worker (idDepartment, idWorker) VALUES(6, 4);

-- SELECT w.name, w.idWorker
-- FROM Worker w, List_Department_Worker ldw, Jobs j
-- WHERE w.idWorker=
