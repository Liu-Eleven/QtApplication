PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE Student(
Name text,
Sex text,
Age integer,
id integer primary key,
addr text
);
INSERT INTO "Student" VALUES('LSY',' NV',21,1,' DHT');
INSERT INTO "Student" VALUES('RHZ',' NV',20,2,' XQZ');
INSERT INTO "Student" VALUES('ZY',' NV',20,3,' KZ');
INSERT INTO "Student" VALUES('NXY',' NV',20,4,' DG');
COMMIT;
