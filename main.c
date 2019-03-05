/*Csv2sql by: Noel Cortes
*
*This program is a C-based cmd tool to construct basic sql queries from .csv file data...
*WIP: .csv formatting rules to come...
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void populateInsert(char total[], char t1[], char t2[], char t3[], char t4[], int *elaborate, int *incorrectFormat);
void populate(char total[], char t1[], char t2[], char t3[], char t4[], char t5[], char t6[]);
void ins(char dml[], char table[], char column[], char data[], int *elaborate);
void upd(char dml[], char table[], char column[], char data[], char refColumn[], char refData[]);
void del(char dml[], char table[], char column[], char data[]);

int main()
{
    // printf("inside main\n");

    char dml[7];
    char table[20];
    char column[20];
    char data[20];
    char refColumn[20];
    char refData[20];
    char full[110];
    int elaborate = 0;
    int incorrectFormat = 0;

    puts("Enter in SQL data:\n");
    while (fgets(full, sizeof(full), stdin) != NULL) {
        // printf("inside while loop\n");
        if (full[0] == 'I') {
            populateInsert(full, dml, table, column, data, &elaborate, &incorrectFormat);
            if (incorrectFormat == 1) {
                return 2;
            }
        } else if (full[0] == 'U') {
            populate(full, dml, table, column, data, refColumn, refData);
        } else if (full[0] == 'D') {
            populate(full, dml, table, column, data, refColumn, refData);
        } else {
            printf("Error");
            return 2;
        }
        // populate(full, dml, table, column, data, refColumn, refData);
        // printf("%s %s %s %s %s %s\n", dml, table, column, data, refColumn, refData);

        switch (dml[0]) {
            case 'I':
                printf("case i\n");
                ins(dml, table, column, data, &elaborate);
                break;
            case 'U':
                printf("case u\n");
                upd(dml, table, column, data, refColumn, refData);
                break;
            case 'D':
                printf("case d\n");
                del(dml, table, column, data);
                break;
            default:
                printf("End of data.");
                return 0;
        }
    }

    // printf("end of main\n");
    return 0;
}

void populateInsert(char total[], char t1[], char t2[], char t3[], char t4[], int *elaborate, int *incorrectFormat) {
    char *token = strtok(total, ",");
    int counter = 0, repeat = 0;
    *elaborate = 0, *incorrectFormat = 0;
    printf("elaborate = %d\n", *elaborate);

    while (token != NULL)
    {
        if (strchr(token, '-')) {
            counter++;
            repeat = 0;
            token = strtok(NULL, ",");
            continue;
        }
        printf("%s\n", token);
        switch (counter) {
        case 0:
            strcpy(t1, "INSERT");
            break;
        case 1:
            strcpy(t2, token);
            break;
        case 2:
            if (repeat == 0) {
                strcpy(t3, token);
                repeat++;
                break;
            } else {
                strcat(t3, ",");
                strcat(t3, token);
                *elaborate = 1;
                printf("elaborate = %d\n", *elaborate);
                break;
            }
        case 3:
            if (repeat == 0) {
                strcpy(t4, token);
                repeat++;
                break;
            } else {
                strcat(t4, ",");
                strcat(t4, token);
                break;
            }
        }
        token = strtok(NULL, ",");
    }
    if(counter != 4) {
        *incorrectFormat = 1;
    }
}

void populate(char total[], char t1[], char t2[], char t3[], char t4[], char t5[], char t6[]) {
    char *token = strtok(total, ",");
    int counter = 0;

    while (token != NULL)
    {
        // printf("%s\n", token);
        switch (counter) {
        case 0:
            if (strchr(token, 'I')) {
                strcpy(t1, "INSERT");
            } else if (strchr(token, 'U')) {
                strcpy(t1, "UPDATE");
            } else if (strchr(token, 'D')) {
                strcpy(t1, "DELETE");
            } else {
                printf("DML Error\n");
                strcpy(t1, token);
                return;
            }
            break;
        case 1:
            strcpy(t2, token);
            break;
        case 2:
            strcpy(t3, token);
            break;
        case 3:
            strcpy(t4, token);
            break;
        case 4:
            strcpy(t5, token);
            break;
        case 5:
            strcpy(t6, token);
            break;
        }
        token = strtok(NULL, ",");
        counter++;
    }
}

void ins(char dml[], char table[], char column[], char data[], int *elaborate) {
    if (*elaborate) {
        printf("%s INTO %s(%s) VALUES=(%s);\n", dml, table, column, data);
    } else {
        printf("%s INTO %s VALUES=(%s);\n", dml, table, data);
    }
}

void upd(char dml[], char table[], char column[], char data[], char refColumn[], char refData[]) {
    printf("%s %s SET %s=%s WHERE %s=%s;\n", dml, table, column, data, refColumn, refData);
}

void del(char dml[], char table[], char column[], char data[]) {
    printf("%s FROM %s WHERE %s=%s;\n", dml, table, column, data);
}
