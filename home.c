#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include"func.c"
#include"medcin.c"
#include"patient.c"
#include"admintools/admintools.c"


void home();



void admission()
{
    char username[20]; // Increased size
    char password[20]; // Increased size

    printf("Enter username: \n");
    scanf("%s", username);
    printf("Enter password: \n");
    scanf("%s", password);

   if (strcmp(username,"admin")!=0)
   {
        printf("incorrect username\n");
        home();
   }
   else if (strcmp(password,"admin")!=0)
   {
    printf("incorrect password\n");
    home();
   }
   else
   {
    printf("acess granted\n");
    admintools();
   }
}

void home()
{
    switch (option("1) Admission 2) Medicin 3) Patient"))
    {
    case 1:
        admission();
        break;
    case 2:
        medcin();
        break;
    case 3:
        patient();
        break;
    case 0:
        return;
    default:
        break;
    }
}

int main()
{
    //CREATE TABLE IF NOT EXIStTS 'service' ('id'	INTEGER NOT NULL,'nom'	TEXT NOT NULL,PRIMARY KEY('id'));   CREATE TABLE IF NOT EXISTS 'Patient' ('patientID'	INTEGER NOT NULL,'nom'	TEXT NOT NULL,'date'	TEXT NOT NULL,'serID'	INTEGER,FOREIGN KEY('serID') REFERENCES 'service'('id'),PRIMARY KEY('patientID'));CREATE IF NOT EXISTS TABLE 'Doctor' ('doctorID'	INTEGER NOT NULL,'nom'	TEXT NOT NULL,'date'	TEXT NOT NULL,'specialite'	TEXT NOT NULL,'sigateur'	INTEGER NOT NULL UNIQUE,'serviceID'	INTEGER NOT NULL UNIQUE,PRIMARY KEY('serviceID'));
    //CREATE TABLE IF NOT EXISTS 'Doctor' ('doctorID' INTEGER NOT NULL, 'nom' TEXT NOT NULL, 'date' TEXT NOT NULL, 'specialite' TEXT NOT NULL, 'sigateur' INTEGER NOT NULL UNIQUE, 'serviceID' INTEGER NOT NULL UNIQUE, PRIMARY KEY('serviceID'));
    sqlite3* db;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;  //si database 8alta
    }
    //
char req1[] = "PRAGMA foreign_keys = ON;"\
"CREATE TABLE IF NOT EXISTS service(id INTEGER NOT NULL, nom TEXT, PRIMARY KEY(id));"\
"CREATE TABLE IF NOT EXISTS list_service_doctor(serID INTEGER NOT NULL, docID INTEGER NOT NULL, PRIMARY KEY(serID, docID), CONSTRAINT id_serID FOREIGN KEY (serID) REFERENCES service (id) ON DELETE CASCADE ON UPDATE CASCADE, CONSTRAINT docID_docID FOREIGN KEY (docID) REFERENCES doctor (docID) ON DELETE CASCADE ON UPDATE CASCADE);"\
"CREATE TABLE IF NOT EXISTS list_service_patient(serID INTEGER NOT NULL, patID INTEGER NOT NULL, PRIMARY KEY(patID, serID), CONSTRAINT id_serID FOREIGN KEY (serID) REFERENCES service (id)ON DELETE CASCADE ON UPDATE CASCADE, CONSTRAINT patID_patID FOREIGN KEY (patID) REFERENCES patient (patID)ON DELETE CASCADE ON UPDATE CASCADE);"\
"CREATE TABLE IF NOT EXISTS doctor(docID INTEGER NOT NULL, nom TEXT, date TEXT, genre TEXT, specialite TEXT, signature TEXT,password TEXT, serID INT, PRIMARY KEY(docID), CONSTRAINT id_serID FOREIGN KEY (serID) REFERENCES service (id) ON DELETE CASCADE ON UPDATE CASCADE);"\
"CREATE TABLE IF NOT EXISTS patient(patID INTEGER NOT NULL, nom TEXT, date TEXT, genre TEXT,password TEXT, serID INTEGER, PRIMARY KEY(patID), CONSTRAINT id_serID FOREIGN KEY (serID) REFERENCES service (id)ON DELETE CASCADE ON UPDATE CASCADE);"\
"CREATE TABLE IF NOT EXISTS consultation(consID INTEGER  NOT NULL, patID INTEGER, docID INTEGER, date TEXT ,accepted INTEGER DEFAULT 0,PRIMARY KEY(consID), CONSTRAINT docID_docID FOREIGN KEY (docID) REFERENCES doctor (docID)ON DELETE CASCADE ON UPDATE CASCADE, CONSTRAINT patID_patID FOREIGN KEY (patID) REFERENCES patient (patID)ON DELETE CASCADE ON UPDATE CASCADE);"\
"CREATE TABLE IF NOT EXISTS maladie(consID INTEGER NOT NULL, desc TEXT, PRIMARY KEY(consID), CONSTRAINT consID_consID FOREIGN KEY (consID) REFERENCES consultation (consID)ON DELETE CASCADE ON UPDATE CASCADE);"\
"CREATE TABLE IF NOT EXISTS ordonnance(consID INTEGER, medicament TEXT, PRIMARY KEY(consID,medicament), CONSTRAINT consID_consID FOREIGN KEY (consID) REFERENCES consultation (consID)ON DELETE CASCADE ON UPDATE CASCADE);"\
"CREATE TABLE IF NOT EXISTS certificat(consID INTEGER NOT NULL,date TEXT,cause INTEGER,state INTEGER DEFAULT 0, PRIMARY KEY(consID),CONSTRAINT consID_consID FOREIGN KEY (consID) REFERENCES consultation (consID)ON DELETE CASCADE ON UPDATE CASCADE);"\
"CREATE TABLE IF NOT EXISTS holidays(date TEXT,PRIMARY KEY(date));";
    insert(db,req1);
    sqlite3_exec(db,"CREATE TRIGGER enforce_consultation_limit BEFORE INSERT ON consultation BEGIN SELECT RAISE(ABORT, 'Consultation limit exceeded') WHERE (SELECT COUNT(*) FROM consultation WHERE DATE(date) = DATE(NEW.date)) >= 20; END;",0,NULL,NULL);
    sqlite3_close(db);
    home();
    return 0;
}
