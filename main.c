/*Csv2sql by: Noel Cortes
*
*This program is a C-based cmd tool to construct basic DML SQL queries from .csv file data...
*WIP: .csv formatting rules to come...
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

int main()
{
    // printf("inside main\n");

    char dml[7];
    char table[30];
    char column[200];
    char data[200];
    char refColumn[200];
    char refData[200];
    char full[850];
    int elaborate = 0;
    int incorrectFormat = 0;

    puts("Enter in SQL data:\n");
    while (fgets(full, sizeof(full), stdin) != NULL) {
        // printf("inside while loop\n");
        populate(full, dml, table, column, data, refColumn, refData, &elaborate, &incorrectFormat);
        if (incorrectFormat != 0) {
            printf("Error: Incorrect Format = %i", incorrectFormat);
            return 2;
        }
        // printf("%s %s %s %s %s %s\n", dml, table, column, data, refColumn, refData);

        switch (dml[0]) {
            case 'I':
                // printf("case i\n");
                ins(dml, table, column, data, &elaborate);
                break;
            case 'U':
                // printf("case u\n");
                upd(dml, table, column, data, refColumn, refData);
                break;
            case 'D':
                // printf("case d\n");
                del(dml, table, column, data);
                break;
            default:
                printf("End of data.");
                return 0;
        }
    }

    // printf("end of main\n");
    return 2;
}

void populate(char total[], char t1[], char t2[], char t3[], char t4[], char t5[], char t6[],
                    int *elaborate, int *incorrectFormat) {
    char *token = strtok(total, ",");
    int counter = 0, repeat = 0, dashBreaks = 0;
    *elaborate = 0, *incorrectFormat = 0;
    // printf("elaborate = %d\n", *elaborate);

    while (token != NULL) {
        if (strchr(token, '-')) {
            repeat = 0;
            counter++;
            dashBreaks++;
            if (dashBreaks > 1) {
                *incorrectFormat = 1;
                return;
            }
            // printf("%i\n", counter);
            token = strtok(NULL, ",");
            continue;
        } else {
            dashBreaks = 0;
        }
        // printf("%s\n", token);
        // printf("%i\n", counter);
        switch (counter) {
            case 0: /*DML Statement: INSERT, UPDATE, DELETE*/
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
            case 1: /*Table Name*/
                strcpy(t2, token);
                break;
            case 2: /*Column Name(s)*/
                    if (repeat == 0) {
                        strcpy(t3, token);
                        repeat++;
                        break;
                    } else {
                        if (t1[0] == 'U' || t1[0] == 'D') { /*Temp fix: If Update has repeats, flag incorrectFormat*/
                            *incorrectFormat = 1;
                            return;
                        } else {
                            strcat(t3, ",");
                            strcat(t3, token);
                            *elaborate = 1;
                            // printf("elaborate = %d\n", *elaborate);
                            break;
                        }
                    }
            case 3: /*Value(s) for Column Name(s)*/
                    if (repeat == 0) {
                        strcpy(t4, token);
                        repeat++;
                        break;
                    } else {
                        if (t1[0] == 'U' || t1[0] == 'D') { /*Temp fix: If Update has repeats, flag incorrectFormat*/
                            *incorrectFormat = 1;
                            return;
                        } else {
                            strcat(t4, ",");
                            strcat(t4, token);
                            break;
                        }
                    }
            case 4: /*Reference Column Name(s)*/
                if (t1[0] == 'I' || t1[0] == 'D') {
                    *incorrectFormat = 1;
                    return;
                } else if (repeat == 0) {
                    strcpy(t5, token);
                    repeat++;
                    break;
                } else {
                    if (t1[0] == 'U' || t1[0] == 'D') { /*Temp fix: If Update has repeats, flag incorrectFormat*/
                        *incorrectFormat = 1;
                        return;
                    } else {
                        strcat(t5, ",");
                        strcat(t5, token);
                        break;
                    }
                }
            case 5: /*Reference Value(s) for Reference Column Name(s)*/
                if (t1[0] == 'I' || t1[0] == 'D') {
                    *incorrectFormat = 1;
                    return;
                } else if (repeat == 0) {
                    strcpy(t6, token);
                    repeat++;
                    break;
                } else {
                    if (t1[0] == 'U' || t1[0] == 'D') { /*Temp fix: If Update has repeats, flag incorrectFormat*/
                        *incorrectFormat = 1;
                        return;
                    } else {
                        strcat(t6, ",");
                        strcat(t6, token);
                        break;
                    }
                }
        }
        token = strtok(NULL, ",");
    }
    if (counter == 3 && t1[0] == 'I') {
        strcpy(t4,t3);
        strcpy(t3,"");
        *elaborate = 0;
    } else if (counter != 4 && counter != 6) {
        *incorrectFormat = 1;
    }
}

void ins(char dml[], char table[], char column[], char data[], int *elaborate) {
    if (*elaborate == 1) {
        printf("\n%s INTO %s(%s) VALUES=(%s);\n\n", dml, table, column, data);
    } else {
        printf("\n%s INTO %s VALUES=(%s);\n\n", dml, table, data);
    }
}

void upd(char dml[], char table[], char column[], char data[], char refColumn[], char refData[]) {
    printf("\n%s %s SET %s=%s WHERE %s=%s;\n\n", dml, table, column, data, refColumn, refData);
}

void del(char dml[], char table[], char column[], char data[]) {
    printf("\n%s FROM %s WHERE %s=%s;\n\n", dml, table, column, data);
}
