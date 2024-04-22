#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
void home();
void addc(int id);
void patient_tools(int id);

void demande_certificat(int id)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return; // Error opening the database
    }
    executeSelectQuery(db, "PRAGMA foreign_keys = ON;");
    char request[150];
    int input;
    sprintf(request, "SELECT * FROM consultation WHERE accepted = 1 AND patID = %d", id);
    executeSelectQuery(db, request);
    printf("chooese id:");
    scanf("%d", &input);
    sprintf(request, "INSERT INTO certificat (consID, date, cause, state) VALUES (%d,'','',0);", input);
    printf("\n%s\n", request);
    insert(db, request);
    sqlite3_close(db);
    patient_tools(id);
}

void dossier(int id)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return; // Error opening the database
    }
    executeSelectQuery(db, "PRAGMA foreign_keys = ON;");
    char request[250];
    printf("\nordonnace: ");
    sprintf(request, "SELECT medicament FROM ordonnance,consultation WHERE consultation.patID = %d AND consultation.consID = ordonnance.consID", id);
    executeSelectQuery(db, request);

    printf("\nmaladie:");
    sprintf(request, "SELECT desc FROM maladie,consultation WHERE consultation.patID = %d AND consultation.consID = maladie.consID", id);
    executeSelectQuery(db, request);

    printf("\ncertificat:");
    sprintf(request, "SELECT certificat.date cause FROM certificat,consultation WHERE consultation.patID = %d AND consultation.consID = certificat.consID", id);
    // printf("\n%s\n",request);
    executeSelectQuery(db, request);

    printf("\nconsultation:");
    sprintf(request, "SELECT docID,date,accepted FROM consultation WHERE consultation.patID = %d;", id);
    // printf("\n%s\n",request);
    executeSelectQuery(db, request);
    sqlite3_close(db);
    patient_tools(id);
}
void patient_tools(int id)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return; // Error opening the database
    }
    executeSelectQuery(db, "PRAGMA foreign_keys = ON;");
    char request [150];
    sprintf(request,"SELECT * FROM consultation WHERE  date <= datetime('now', '+7 days') AND patID = %d ORDER BY date",id);
    executeSelectQuery(db,request);
            sqlite3_close(db);

    switch (option("\n1)demande une certificat 2)demander un rendez vous 3)dossier medical 0)return"))
    {
    case 1:
        demande_certificat(id);
        break;
    case 2:
        addc(id);
        break;
    case 3:
        dossier(id);
        break;
    case 0:
        home();
        break;
    default:
        break;
    }
}
void patient()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
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
    printf("Enter username:");
    scanf("%d", &username);
    printf("Enter password:");
    scanf("%s", password);

    sprintf(request, "SELECT COUNT(*) FROM patient WHERE patID =%d AND password = '%s';", username, password);

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
    patient_tools(username);
    sqlite3_close(db);

}

void addc(int id)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return; // Error opening the database
    }
    executeSelectQuery(db, "PRAGMA foreign_keys = ON;");
    int docID, consid;
    char date[15];

    sqlite3_stmt *stmt1;
    char request[200];
    sprintf(request, "SELECT id, service.nom FROM service,patient where patient.serID = service.id AND patient.patID = %d",id);
    printf("\n%s\n", request);
    executeSelectQuery(db, request);
    sprintf(request, "select doctor.nom,docID from doctor,patient where patient.patID = %d and patient.serID = doctor.serID", id);
    printf("\n%s\n", request);
    executeSelectQuery(db, request);
    printf("HOLIDAYS\n");
    sprintf(request, "SELECT date FROM holidays");
    executeSelectQuery(db, request);
    // Input for patID

    printf("Enter cons ID: ");
    scanf("%d", &consid);

    // Input for docID
    printf("Enter doctor ID: ");
    scanf("%d", &docID);

    // Input for date
    do
    {
        printf("add date:");
        scanf("%s", date);
    } while (isValidDateString(date) == false);

    sprintf(request, "SELECT COUNT(*) FROM holidays WHERE date = '%s'", date);
    if (sqlite3_prepare_v2(db, request, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_step(stmt);
    if (sqlite3_column_int(stmt, 0) != 0)
    {
        printf("\ndate jour ferier\n");
        return;
    }
    sqlite3_finalize(stmt);
    sprintf(request, "SELECT COUNT(*) FROM doctor,patient WHERE doctor.serID=patient.serID AND doctor.docID = %d AND patient.patID = %d", docID, id);
    printf("\n%s\n", request);
    if (sqlite3_prepare_v2(db, request, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_step(stmt);
    printf("%d", sqlite3_column_int(stmt, 0));
    if (sqlite3_column_int(stmt, 0) == 0)
    {
        printf("\npatient and doctor are not in the same service\n");
        return;
    }

    sprintf(request, "INSERT INTO consultation (consID, patID, docID, date,accepted) VALUES (%d,%d,%d,'%s',0)", consid, id, docID, date);
    printf("\n%s\n", request);
    insert(db, request);
    sqlite3_close(db);
    patient_tools(id);
}
