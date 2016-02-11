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
INSERT INTO List_Department_Worker (idDepartment, idWorker) VALUES(4, 4);

INSERT INTO Messages (content) VALUES ("Go to Work");
INSERT INTO List_Sent_Messages (idMessages, idFromWorker, dateTime) VALUES (1, 1, NOW());
INSERT INTO List_Rcvd_Messages (idMessages, idToWorker) VALUES (1, 2);

-- SELECT lrm.idMessages, m.content, lsm.dateTime  FROM Messages m, List_Sent_Messages lsm, List_Rcvd_Messages lrm WHERE lsm.idMessages = lrm.idMessages AND lrm.isRead=0 AND lrm.idToWor
-- ker=2;

SELECT lrm.idMessages, m.content, lsm.dateTime, w.name  FROM Messages m, List_Sent_Messages lsm, List_Rcvd_Messages lrm, Worker w WHERE lsm.idMessages = lrm.idMessages AND w.idWorker
= lsm.idFromWorker AND lrm.isRead=0 AND lrm.idToWorker=1;

INSERT INTO Messages (content) VALUES("GO TO WORK!!\n");
INSERT INTO List_Sent_Messages (idMessages, idFromWorker, dateTime)
VALUES (1, 1, NOW());
INSERT INTO List_Rcvd_Messages (idMessages, idToWorker)
VALUES(1, 2);



-- SELECT w.name, w.idWorker
-- FROM Worker w, List_Department_Worker ldw, Jobs j
-- WHERE w.idWorker=
