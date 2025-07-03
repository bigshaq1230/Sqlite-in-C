#include <stdio.h>
#include <stdlib.h>
#include "../libs/sqlite3/sqlite3.h"
#include<string.h>
#include<stdio.h>
#include <stdbool.h>
void admintools();
void gerer_les_medecins();
void addm() {
    sqlite3* db;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;  // Error opening the database
    }
    executeSelectQuery(db,"PRAGMA foreign_keys = ON;");
    // "doctorID", "nom", "date", "specialite", "sigateur", "serviceID"
    printf("regestred services:\n");
    char request[1000] = "SELECT * FROM service";
    executeSelectQuery(db,request);
    int id,serID;
    char nom[20];
    char date[20];
    char specialite[20];
    char sigateur[20];
    char genre[10];
    char pass[10];
    printf("Enter doctorID:");
    scanf("%d", &id);

    printf("Enter doctor_nom:");
    scanf("%s", nom);

    do
    {
        printf("add date:");
        scanf("%s", date);
    } while (isValidDateString(date) == false);

    printf("genre:");
    scanf("%s", genre);

    printf("Enter specialite: ");
    scanf("%s", specialite);

    printf("Enter signature: ");
    scanf("%s", sigateur);

    printf("Enter password: ");
    scanf("%s", pass);


    printf("Enter serviceID: ");
    scanf("%d", &serID);

    sprintf(request,"INSERT INTO doctor (docID, nom, date, genre, specialite, signature, password,serID) VALUES (%d,'%s','%s','%s','%s','%s','%s',%d)",id,nom,date,genre,specialite,sigateur,pass,serID);
    insert(db,request);
    sprintf(request,"INSERT INTO list_service_doctor (serID,docID) VALUES ('%d','%d')",serID,id);
    insert(db,request);
    sqlite3_close(db);

}
void editm(){
    sqlite3* db;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;  // Error opening the database
    }
    executeSelectQuery(db,"PRAGMA foreign_keys = ON;");
    sqlite3_stmt *stmt;
    char request[400] = "SELECT * FROM Doctor;";
    int input;
    executeSelectQuery(db,request);
    printf("give id to edit :");
    scanf("%d",&input);

    sprintf(request,"SELECT COUNT(docID) FROM Doctor WHERE docID=%d;",input);

    if (sqlite3_prepare_v2(db, request, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_step(stmt);
    if (sqlite3_column_int(stmt, 0)==0)
    {
        printf("\nid not found \n");
        return;
    }
    sqlite3_finalize(stmt);
    sprintf(request,"SELECT * FROM service");
    executeSelectQuery(db,request);
    int id,serID;
    char nom[20];
    char date[20];
    char specialite[20];
    char sigateur[20];
    char genre[10];
    char pass[10];

    printf("Enter doctorID:");
    scanf("%d", &id);

    printf("Enter doctor_nom:");
    scanf("%s", nom);

    do
    {
        printf("add date:");
        scanf("%s", date);
    } while (isValidDateString(date) == false);

    printf("genre:");
    scanf("%s", genre);

    printf("Enter specialite: ");
    scanf("%s", specialite);

    printf("Enter signature: ");
    scanf("%s", sigateur);

    printf("Enter password: ");
    scanf("%s", pass);

    printf("Enter serviceID: ");
    scanf("%d", &serID);

    sprintf(request,"UPDATE doctor SET docID = %d,nom = '%s',date = '%s',genre = '%s',specialite='%s',signature='%s',password='%s',serID=%d WHERE docID = %d;",id,nom,date,genre,specialite,sigateur,pass,serID,input);
    printf("%s",request);
    insert(db,request);
    sqlite3_close(db);

}
void delm(){
    sqlite3* db;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;  // Error opening the database
    }
    executeSelectQuery(db,"PRAGMA foreign_keys = ON;");
    sqlite3_stmt *stmt;
    char request[100] = "SELECT * FROM Doctor;";
    int input;
    executeSelectQuery(db,request);
    printf("give id to delete :");
    scanf("%d",&input);

    sprintf(request,"SELECT COUNT(docID) FROM Doctor WHERE docID=%d;",input);

    if (sqlite3_prepare_v2(db, request, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_step(stmt);
    if (sqlite3_column_int(stmt, 0)==0)
    {
        printf("\nid not found \n");
        return;
    }
    sqlite3_finalize(stmt);
    sprintf(request,"DELETE FROM list_service_doctor WHERE docID =%d;",input);
    insert(db,request);
    sprintf(request,"DELETE FROM doctor WHERE docID=%d;",input);
    insert(db,request);
    sqlite3_close(db);

}
void gerer_les_medecins() {
    switch (option("1)add 2)edit 3)delete"))
    {
    case 1:
        addm();
        admintools();
        break;
    case 2:
        editm();
        admintools();
        break;
    case 3:
        delm();
        admintools();
        break;
    case 0:
    admintools();
    default:
        break;
    }
}




