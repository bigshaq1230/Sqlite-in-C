#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void insert(sqlite3 *db, char *request) {
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_exec(db, request, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        printf("success!\n");
    }
}
int option(char string[])
{
    int input;
    printf("%s\n", string);
    scanf("%d", &input);
    return input;
}
int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    printf("%s: ", (const char *)data);

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}
int errorCallback(void *data, int errorCode, char **errorMsg, char **sqlStatement)
{
    fprintf(stderr, "Error: %s\n", *errorMsg);
    fprintf(stderr, "SQL statement: %s\n", *sqlStatement);
    return 0; // Returning 0 continues the normal processing of the SQLite API
}
int executeSelectQuery(sqlite3 *db, const char *query)
{
    char *errMsg = NULL;

    // Execute the query using sqlite3_exec
    int result = sqlite3_exec(db, query, callback, 0, &errMsg);

    // Check for errors
    if (result != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 0;
    }
    return 1;
}
bool isLeapYear(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}
bool isValidDateString(const char *dateString)

{
    int day, month, year;
    if (sscanf(dateString, "%d/%d/%d", &day, &month, &year) != 3)
    {
        return false; // Failed to parse three integers
    }

    // Check if month is valid
    if (month < 1 || month > 12)
    {
        return false;
    }

    // Array to store the maximum number of days in each month
    int maxDaysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Adjust max days in February for leap years
    if (month == 2 && isLeapYear(year))
    {
        maxDaysInMonth[2] = 29;
    }

    // Check if day is valid for the given month
    return (day >= 1 && day <= maxDaysInMonth[month]);
}
