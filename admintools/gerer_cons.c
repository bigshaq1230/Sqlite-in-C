#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include<string.h>
#include<stdio.h>
void admintools();
void planifier_les_redez_vous() {
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
    sprintf(request,"SELECT * FROM consultation WHERE accepted = 0;");
    executeSelectQuery(db,request);
    printf("which one to accept: ");
    scanf("%d",&id);
    sprintf(request,"UPDATE consultation SET accepted = 1 WHERE consID = %d;",id);
    insert(db,request);
    sqlite3_close(db);
}
