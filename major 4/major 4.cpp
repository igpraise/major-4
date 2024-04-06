/*
* FILE : major 4
* PROJECT : SENG1000
* PROGRAMMER : Ignatius praise 
* FIRST VERSION : 2024-02-04
* DESCRIPTION :
* The functions in this file are used toWrite a program to display flight information where the least fare found for given source –
destination pair
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 100
#define MAX_FILENAME_LENGTH 50
#define MAX_LINE_LENGTH 100

struct Flight {
    char source[20];
    char destination[20];
    int fare;
    char airline[30];
};

int parseLine(char* source, char* destination, int* fare, char* line) {
    char* token = strtok(line, ",");
    if (token == NULL) return 0;
    strcpy(source, strtok(token, "-"));
    strcpy(destination, strtok(NULL, "-"));
    *fare = atoi(strtok(NULL, "-"));
    return 1;
}
int processFlight(char* filename, struct Flight flights[], int* total_count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 0;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL && *total_count < MAX_FLIGHTS) {
        if (line[0] == '\n') continue;
        char source[20], destination[20];
        int fare;
        if (!parseLine(source, destination, &fare, line)) {
            printf("Error: Invalid format in file %s\n", filename);
            fclose(file);
            return 0;
        }
        strcpy(flights[*total_count].source, source);
        strcpy(flights[*total_count].destination, destination);
        flights[*total_count].fare = fare;
        strcpy(flights[*total_count].airline, strtok(filename, "."));
        (*total_count)++;
    }
    fclose(file);
    return 1;
}
