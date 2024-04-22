#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include<string.h>
#include<stdio.h>
void admintools();
void add() {
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
    char query[200];
    int x;
    char name[20];
    int input;
    printf("id: ");
    scanf("%d",&id);
    printf("name: ");
    scanf("%s",name);
    sprintf(query,"INSERT INTO service (id,nom) VALUES(%d,'%s')",id,name);
    insert(db,query);
    sqlite3_close(db);
}
void edit() {
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
    sqlite3_stmt *stmt;
    int input;
    executeSelectQuery(db,request);
    printf("give idd to edit : ");
    scanf("%d",&input);
    sprintf(request,"SELECT COUNT(id) FROM service WHERE id=%d;",input);

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

    int x;
    char name[20];
    printf("id: ");
    scanf("%d",&id);
    printf("name: ");
    scanf("%s",name);
    sprintf(request,"UPDATE service SET id= %d , nom= '%s' WHERE id = %d",id,name,input);
    printf("%s\n",request);
    insert(db,request);
        sqlite3_close(db);

}
void del() {
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
    sqlite3_stmt *stmt;
    int input;
    executeSelectQuery(db,request);
    printf("give id to delete : ");
    scanf("%d",&input);
        sprintf(request,"SELECT COUNT(id) FROM service WHERE id=%d;",input);

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
    sprintf(request,"DELETE FROM service WHERE id=%d",input);
    executeSelectQuery(db,request);

    sqlite3_close(db);
}
void gerer_les_services() {
    switch (option("1)aadd 2)edit 3)delete"))
    {
    case 1:
        add();
        admintools();
        break;
    case 2:
        edit();
        admintools();
        break;
    case 3:
        del();
        admintools();
        break;
    case 0:
        admintools();
        break;
    default:
        break;
    }
}
