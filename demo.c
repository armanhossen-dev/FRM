/*#include<stdio.h>
int main(){
    char name[50];
    scanf(" %[^\n]", name);
    printf("%s",name);
    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for flight information
typedef struct flight {
    char flight_number[10];
    char departure[50];
    char destination[50];
    char time[10];
    char date[15];
} flight_info;

// Structure for passenger information
typedef struct passenger {
    char name[50];
    int age;
    char flight_number[10];
    char destination[50];
    char date[15];
} passenger_info;

// Function prototypes
void admin_Add_Flight();
void user_Book_Tickets();
void view_Flights();

int main() {
    int choice;

    while (1) {
        system("cls");
        printf("============================================\n");
        printf("         Flight Reservation System          \n");
        printf("============================================\n");
        printf("1. Book Tickets (User)\n");
        printf("2. Add New Flights (Admin)\n");
        printf("3. View Available Flights\n");
        printf("4. Exit\n");
        printf("============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: user_Book_Tickets(); break;
            case 2: admin_Add_Flight(); break;
            case 3: view_Flights(); break;
            case 4: exit(0);
            default: printf("Invalid choice! Try again.\n"); system("pause");
        }
    }

    return 0;
}

// Admin function to add new flights
void admin_Add_Flight() {
    flight_info new_flight;
    FILE* flight_file = fopen("flights.txt", "a");

    if (flight_file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    system("cls");
    printf("============================================\n");
    printf("           Add New Flight (Admin)           \n");
    printf("============================================\n");

    printf("Enter Flight Number (e.g., BG001): ");
    scanf(" %[^\n]", new_flight.flight_number);
    printf("Enter Departure Location (e.g., Dhaka): ");
    scanf(" %[^\n]", new_flight.departure);
    printf("Enter Destination (e.g., Sylhet): ");
    scanf(" %[^\n]", new_flight.destination);
    printf("Enter Time (e.g., 09:30 AM): ");
    scanf(" %[^\n]", new_flight.time);
    printf("Enter Date (e.g., 01-Dec-2024): ");
    scanf(" %[^\n]", new_flight.date);

    // Save new flight to the file
    fprintf(flight_file, "%s,%s,%s,%s,%s\n",
            new_flight.flight_number,
            new_flight.departure,
            new_flight.destination,
            new_flight.time,
            new_flight.date);

    printf("New flight added successfully!\n");
    fclose(flight_file);
    system("pause");
}

// Function to view available flights
void view_Flights() {
    FILE* flight_file = fopen("flights.txt", "r");
    flight_info flight;
    char line[200];
    int count = 0;

    if (flight_file == NULL) {
        printf("No flights available. Admin should add flights first.\n");
        system("pause");
        return;
    }

    system("cls");
    printf("============================================\n");
    printf("               Available Flights            \n");
    printf("============================================\n");
    printf("| Flight No | Departure  | Destination   | Time     | Date         |\n");
    printf("|-----------|------------|---------------|----------|--------------|\n");

    while (fgets(line, sizeof(line), flight_file)) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^\n]",
               flight.flight_number,
               flight.departure,
               flight.destination,
               flight.time,
               flight.date);
        printf("| %-9s | %-10s | %-13s | %-8s | %-12s |\n",
               flight.flight_number,
               flight.departure,
               flight.destination,
               flight.time,
               flight.date);
        count++;
    }

    if (count == 0) {
        printf("| No flights available. Add flights first!                       |\n");
    }

    printf("============================================\n");
    fclose(flight_file);
    system("pause");
}

// User function to book tickets
void user_Book_Tickets() {
    char flight_number[10], destination[50], date[15];
    int n_seats;
    passenger_info* jatri = NULL;

    FILE* flight_file = fopen("flights.txt", "r");
    flight_info flight;
    char line[200];
    int flight_found = 0;

    if (flight_file == NULL) {
        printf("No flights available. Admin should add flights first.\n");
        system("pause");
        return;
    }

    view_Flights();

    printf("\nEnter Flight Number to book (e.g., BG001): ");
    scanf(" %[^\n]", flight_number);

    // Verify flight exists
    while (fgets(line, sizeof(line), flight_file)) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^\n]",
               flight.flight_number,
               flight.departure,
               flight.destination,
               flight.time,
               flight.date);
        if (strcmp(flight.flight_number, flight_number) == 0) {
            strcpy(destination, flight.destination);
            strcpy(date, flight.date);
            flight_found = 1;
            break;
        }
    }

    fclose(flight_file);

    if (!flight_found) {
        printf("Flight not found! Please try again.\n");
        system("pause");
        return;
    }

    printf("\nHow many seats do you want to book? ");
    scanf("%d", &n_seats);

    jatri = (passenger_info*)malloc(n_seats * sizeof(passenger_info));
    if (jatri == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Input passenger details
    for (int i = 0; i < n_seats; i++) {
        printf("\nEnter Details For Passenger %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", jatri[i].name);
        printf("Age: ");
        scanf("%d", &jatri[i].age);
        strcpy(jatri[i].flight_number, flight_number);
        strcpy(jatri[i].destination, destination);
        strcpy(jatri[i].date, date);
    }

    // Save passenger details to file
    FILE* passenger_file = fopen("passenger_bookings.txt", "a");
    if (passenger_file == NULL) {
        printf("Error opening file for writing!\n");
        free(jatri);
        return;
    }

    fprintf(passenger_file, "=============================================\n");
    fprintf(passenger_file, "Flight Number: %s\n", flight_number);
    fprintf(passenger_file, "Destination: %s\n", destination);
    fprintf(passenger_file, "Date: %s\n", date);
    fprintf(passenger_file, "Number of Seats: %d\n", n_seats);
    fprintf(passenger_file, "---------------------------------------------\n");

    for (int i = 0; i < n_seats; i++) {
        fprintf(passenger_file, "Passenger %d:\n", i + 1);
        fprintf(passenger_file, " Name: %s\n", jatri[i].name);
        fprintf(passenger_file, " Age: %d\n", jatri[i].age);
    }
    fprintf(passenger_file, "=============================================\n");
    fclose(passenger_file);

    printf("\nTickets booked successfully!\n");
    free(jatri);
    system("pause");
}
