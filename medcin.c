#include <stdio.h>
#include <stdlib.h>
#include "libs/sqlite3/sqlite3.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
void home();
void medcintools(int id);
void rediger_ordonnances(int id)
{
    sqlite3 *db;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return; // Error opening the database
    }
    executeSelectQuery(db, "PRAGMA foreign_keys = ON;");

    int x;
    char desc[25];
    sqlite3_stmt *stmt;
    int input;
    char request[250];
    sprintf(request, "SELECT consID, consultation.patID, consultation.date,patient.nom FROM consultation,patient WHERE accepted = 1 AND docID = %d AND consultation.patID = patient.patID;", id);
    executeSelectQuery(db, request);
    printf("give constulation id:");
    scanf("%d", &input);
    sprintf(request,"SELECT COUNT(*) FROM consultation WHERE consID =  %d;",input);
    if (sqlite3_prepare_v2(db, request, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_step(stmt);
    if (sqlite3_column_int(stmt, 0) == 0)
    {
        printf("\nid dosen't exist\n");
        return;
    }
    sqlite3_finalize(stmt);
    printf("nombre de medicament");
    scanf("%d", &x);
    for (int i = 0; i < x; i++)
    {
        printf("donner ordonnance:");
        scanf("%s", desc);
        sprintf(request, "INSERT OR REPLACE INTO ordonnance (consID, medicament) VALUES (%d,'%s');", input, desc);
        insert(db, request);
    }
    sqlite3_close(db);
    medcintools(id);
}


void rediger_malade(int id)
{
    sqlite3 *db;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return; // Error opening the database
    }
    executeSelectQuery(db, "PRAGMA foreign_keys = ON;");

    char desc[25];
    sqlite3_stmt *stmt;
    int input;
    char request[250];
    sprintf(request, "SELECT consID, consultation.patID, consultation.date,patient.nom FROM consultation,patient WHERE accepted = 1 AND docID = %d AND consultation.patID = patient.patID;", id);
    executeSelectQuery(db, request);
    printf("give constulation id:");
    scanf("%d", &input);
    sprintf(request,"SELECT COUNT(*) FROM consultation WHERE consID = %d;",input);
    if (sqlite3_prepare_v2(db, request, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    printf("\n%s\n",request);
    sqlite3_step(stmt);
    if (sqlite3_column_int(stmt, 0) == 0)
    {
        printf("\nid dosen't exist\n");
        return;
    }
    sqlite3_finalize(stmt);

    printf("donner description maladie :");
    scanf("%s", desc);
    sprintf(request, "INSERT INTO maladie (consID, desc) VALUES (%d,'%s');", input, desc);
    insert(db, request);
    sqlite3_close(db);
    medcintools(id);
}

void rediger_certificats(int id)
{
    sqlite3 *db;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return; // Error opening the database
    }
    executeSelectQuery(db, "PRAGMA foreign_keys = ON;");

    char date[15];
    char cause[25];
    sqlite3_stmt *stmt;
    int input;
    char request[200];
    sprintf(request, "SELECT consID, consultation.patID, consultation.date,patient.nom FROM consultation,patient WHERE accepted = 1 AND docID = %d AND consultation.patID = patient.patID; ", id);
    executeSelectQuery(db, request);
    printf("give constulation id:");
    scanf("%d", &input);
    sprintf(request,"SELECT COUNT(*) FROM consultation WHERE consID = %d;",input);
    if (sqlite3_prepare_v2(db, request, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_step(stmt);
    if (sqlite3_column_int(stmt, 0) == 0)
    {
        printf("\nid dosen't exist\n");
        return;
    }
    sqlite3_finalize(stmt);

    printf("donner cause:");
    scanf("%s", cause);
    do
    {
        printf("donner date:");
        scanf("%s", date);
    } while (isValidDateString(date) == false);

    sprintf(request, "INSERT OR REPLACE INTO certificat (consID, date, cause, state) VALUES (%d,'%s','%s',0);", input, cause, date);
    printf("%s",request);
    insert(db, request);
    sqlite3_close(db);
    medcintools(id);
}

void medcintools(int id)
{
    switch (option("1)rédiger le dossier du malade 2)rédiger des ordonnances 3)rédiger des certificats 0)return"))
    {
    case 1:
        rediger_malade(id);
        break;
    case 2:
        rediger_ordonnances(id);
        break;
    case 3:
        rediger_certificats(id);
        break;
    case 0:
        home();
        break;
    default:
        medcintools(id);
        break;
    }
}
void medcin()
{
    sqlite3_stmt *stmt;
    sqlite3 *db;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return; // Error opening the database
    }
    executeSelectQuery(db, "PRAGMA foreign_keys = ON;");

    int username;
    char password[20];
    char request[150];
    printf("Enter username: \n");
    scanf("%d", &username);
    printf("Enter password: \n");
    scanf("%s", password);

    sprintf(request, "SELECT COUNT(*) FROM doctor WHERE docID =%d AND password = '%s';", username, password);

    if (sqlite3_prepare_v2(db, request, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_step(stmt);
    if (sqlite3_column_int(stmt, 0) == 0)
    {
        printf("\nINCORRECT PASSWORD OR ID\n");
        home();
        return;
    }
    sqlite3_finalize(stmt);
    medcintools(username);
    sqlite3_close(db);
}