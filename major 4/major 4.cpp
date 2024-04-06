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
void displayLeastFareDetails(struct Flight flights[], int total_count) {
    int min_fare = flights[0].fare;
    int index = 0;
    for (int i = 1; i < total_count; i++) {
        if (flights[i].fare < min_fare) {
            min_fare = flights[i].fare;
            index = i;
        }
    }
    printf("%s: %s to %s, Fare $%d\n", flights[index].airline, flights[index].source, flights[index].destination, flights[index].fare);
}

int main() {
    FILE* flights_file = fopen("flights.txt", "r");
    if (flights_file == NULL) {
        printf("Error: Could not open flights.txt\n");
        return 1;
    }
    char filename[MAX_FILENAME_LENGTH];
    struct Flight flights[MAX_FLIGHTS];
    int total_count = 0;
    while (fgets(filename, sizeof(filename), flights_file) != NULL) {
        filename[strcspn(filename, "\n")] = 0; // Remove newline character
        if (!processFlight(filename, flights, &total_count)) {
            fclose(flights_file);
            return 1;
        }
    }
    fclose(flights_file);
    displayLeastFareDetails(flights, total_count);
    return 0;
}
