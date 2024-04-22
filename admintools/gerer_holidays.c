#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
void gerer_holidays();

void addh()
{
    sqlite3* db;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;  // Error opening the database
    }
    executeSelectQuery(db,"PRAGMA foreign_keys = ON;");

    char request[100];
    char date[20];
    do
    {
        printf("add date:");
        scanf("%s", date);
    } while (isValidDateString(date) == false);
    sprintf(request, "INSERT INTO holidays (date) VALUES ('%s');", date);
    insert(db, request);
        sqlite3_close(db);

}

void delh()
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
    char date[20];
    sprintf(request,"SELECT * FROM holidays");
    executeSelectQuery(db,request);

    do
    {
        printf("add date:");
        scanf("%s", date);
    } while (isValidDateString(date) == false);
    sprintf(request, "DELETE FROM holidays WHERE date='%s';", date);
    insert(db,request);
        sqlite3_close(db);

}
void admintools();
void gerer_holidays()
{
    switch (option("1)add 2)del"))
    {
    case 1:
        addh();
        admintools();
        break;
    case 2:
        delh();
        admintools();
        break;
    case 0:
        admintools();
        break;
    default:
        break;
    }
}
