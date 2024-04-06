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

