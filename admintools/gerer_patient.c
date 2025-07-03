#include <stdio.h>
#include <stdlib.h>
#include "../libs/sqlite3/sqlite3.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
void admintools();
void gerer_les_patients();
void addp()
{
    sqlite3 *db;
    char request[150];
    int id;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return; // Error opening the database
    }
    executeSelectQuery(db, "PRAGMA foreign_keys = ON;");
    int patientID, serID;
    char nom[20];
    char date[10];
    char pass[10];
    char genre[6];
    printf("availeble services to choose from\n");
    strcpy(request, "SELECT * FROM service;");
    executeSelectQuery(db, request);

    //            patID, nom, date, genre, serID
    printf("id de patient: ");
    scanf("%d", &patientID);
    printf("nom: ");
    scanf("%s", nom);
    do
    {
        printf("add date:");
        scanf("%s", date);
    } while (isValidDateString(date) == false);
    printf("genre: ");
    scanf("%s", genre);
    printf("password: ");
    scanf("%s", pass);
    printf("id de service: ");
    scanf("%d", &serID);
    sprintf(request, "INSERT INTO patient (patID, nom, date, genre, password,serID) VALUES (%d,'%s','%s','%s','%s',%d);", patientID, nom, date, pass, genre, serID);
    insert(db, request);
    sprintf(request, "INSERT INTO list_service_patient (patID,serID) VALUES ('%d','%d')", patientID, serID);
    insert(db, request);
    sqlite3_close(db);
}
void editp()
{
    sqlite3 *db;
    char request[150];
    int id;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return; // Error opening the database
    }
    executeSelectQuery(db, "PRAGMA foreign_keys = ON;");
    int patientID, serID;
    char nom[20];
    char date[10];
    char pass[10];
    char genre[6];

    sqlite3_stmt *stmt;
    int input;
    printf("availeble services to choose from\n");
    strcpy(request, "SELECT * FROM Patient;");
    executeSelectQuery(db, request);
    printf("id to change");
    scanf("%d", &input);
    sprintf(request, "SELECT COUNT(patientID) FROM Patient WHERE patID=%d;", input);
    if (sqlite3_prepare_v2(db, request, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_step(stmt);
    if (sqlite3_column_int(stmt, 0) == 0)
    {
        printf("\nid not found\n");
        return;
    }
    sqlite3_finalize(stmt);

    printf("availeble services to choose from\n");
    strcpy(request, "SELECT * FROM service;");
    executeSelectQuery(db, request);

    //            patID, nom, date, genre, serID
    printf("id de patient: ");
    scanf("%d", &patientID);
    printf("nom: ");
    scanf("%s", nom);
    do
    {
        printf("add date:");
        scanf("%s", date);
    } while (isValidDateString(date) == false);
    printf("genre: ");
    scanf("%s", genre);
    printf("password: ");
    scanf("%s", pass);
    printf("id de service: ");
    scanf("%d", &serID);
    sprintf(request, "UPDATE patient SET patID =%d , nom='%s', date='%s', genre='%s', password='%s',serID= %d WHERE patID=%d", patientID, nom, date, pass, genre, serID, input);
    insert(db, request);
    sqlite3_close(db);
}
void delp()
{
    sqlite3 *db;
    int id;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return; // Error opening the database
    }
    executeSelectQuery(db, "PRAGMA foreign_keys = ON;");
    char request[100] = "SELECT * FROM Patient;";
    sqlite3_stmt *stmt;
    int input;
    executeSelectQuery(db, request);
    printf("give id to delete : ");
    scanf("%d", &input);
    sprintf(request, "SELECT COUNT(patID) FROM Patient WHERE patID=%d;", input);
    if (sqlite3_prepare_v2(db, request, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_step(stmt);
    if (sqlite3_column_int(stmt, 0) == 0)
    {
        printf("\nid not found\n");
        return;
    }
    sqlite3_finalize(stmt);
    sprintf(request, "DELETE FROM list_service_patient WHERE patID='%d'", input);
    insert(db, request);
    sprintf(request, "DELETE FROM Patient WHERE patID='%d'", input);
    insert(db, request);
    sqlite3_close(db);
}

void gerer_les_patients()
{
    switch (option("1)add 2)edit 3)delete"))
    {
    case 1:
        addp();
        admintools();
        break;
    case 2:
        editp();
        admintools();
        break;
    case 3:
        delp();
        admintools();
        break;
    case 0:
        admintools();
    default:
        break;
    }
}
