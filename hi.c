// File: final.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants and macros for configuration
#define USER_INFO_FILE "users_info.txt"
#define FLIGHTS_FILE "flights.txt"
#define BOOKINGS_FILE "bookings.txt"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"
#define MAX_FLIGHTS 8
#define MAX_USERNAME 50
#define MAX_PASSWORD 50



#define FLIGHTS_FILE "flights.txt"
#define BOOKINGS_FILE "bookings.txt"
#define MAX_FLIGHTS 8

typedef struct {
    char flight_number[10];
    char departure[30];
    char destination[30];
    char time[10];
    char date[15];
    float price_per_seat;
    int total_seats;
} Flight;

typedef struct {
    char name[50];
    int age;
    char flight_number[10];
    int seat_number;
    float price;
} Booking;



// Structs for managing flights and bookings
typedef struct {
    char flight_number[10];
    char departure[30];
    char destination[30];
    char time[10];
    char date[15];
    float price_per_seat;
    int total_seats;
} Flight;

typedef struct {
    char name[50];
    int age;
    char flight_number[10];
    int seat_number;
    float price;
} Booking;

// Global variables
Flight flights[MAX_FLIGHTS];
int flight_count = 0;

// Function prototypes
void adminLoginPortal();
void userLoginPortal();
void adminDashboard();
void userDashboard();
void signup();
void login();
void viewAvailableFlights();
void addNewFlight();
void updateFlight();
void bookTickets();
void updateBooking();
void viewFlights();

int main() {
    int choice;
    while (1) {
        system("cls");
        printf("============================================================\n");
        printf("        Welcome to the Flight Reservation System            \n");
        printf("============================================================\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminLoginPortal();
                break;
            case 2:
                userLoginPortal();
                break;
            case 3:
                printf("\nExiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void adminLoginPortal() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    int attempts = 3;

    while (attempts--) {
        system("cls");
        printf("Admin Login Portal\n");
        printf("Enter Admin Username: ");
        scanf(" %[^\n]", username);
        printf("Enter Admin Password: ");
        scanf(" %[^\n]", password);

        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("Login Successful!\n");
            system("pause");
            adminDashboard();
            return;
        } else {
            printf("Invalid credentials. Attempts left: %d\n", attempts);
        }
    }
    printf("Too many failed attempts. Exiting...\n");
    exit(1);
}

void userLoginPortal() {
    int choice;
    while (1) {
        system("cls");
        printf("User Login Portal\n");
        printf("1. Sign Up\n");
        printf("2. Login\n");
        printf("3. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                login();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void signup() {
    FILE *file = fopen(USER_INFO_FILE, "a");
    char username[MAX_USERNAME], password[MAX_PASSWORD], confirm[MAX_PASSWORD];

    if (!file) {
        printf("Error opening file for signup.\n");
        return;
    }

    system("cls");
    printf("Sign Up\n");
    printf("Enter username: ");
    scanf(" %[^\n]", username);
    printf("Enter password: ");
    scanf(" %[^\n]", password);
    printf("Confirm password: ");
    scanf(" %[^\n]", confirm);

    if (strcmp(password, confirm) != 0) {
        printf("Passwords do not match.\n");
        fclose(file);
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    printf("Account created successfully. You can now log in.\n");
}

void login() {
    FILE *file = fopen(USER_INFO_FILE, "r");
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    char stored_username[MAX_USERNAME], stored_password[MAX_PASSWORD];
    int logged_in = 0;

    if (!file) {
        printf("Error opening user file. Have you signed up?\n");
        return;
    }

    printf("Log In\n");
    printf("Enter username: ");
    scanf(" %[^\n]", username);
    printf("Enter password: ");
    scanf(" %[^\n]", password);

    while (fscanf(file, "%s %s", stored_username, stored_password) != EOF) {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
            logged_in = 1;
            break;
        }
    }
    fclose(file);

    if (logged_in) {
        printf("Login successful!\n");
        system("pause");
        userDashboard();
    } else {
        printf("Invalid credentials.\n");
    }
}

void adminDashboard() {
    int choice;
    while (1) {
        system("cls");
        printf("Admin Dashboard\n");
        printf("1. View Flights\n");
        printf("2. Add Flight\n");
        printf("3. Update Flight\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAvailableFlights();
                break;
            case 2:
                addNewFlight();
                break;
            case 3:
                updateFlight();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void userDashboard() {
    int choice;
    while (1) {
        system("cls");
        printf("User Dashboard\n");
        printf("1. Book Tickets\n");
        printf("2. View Flights\n");
        printf("3. Update Booking\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookTickets();
                break;
            case 2:
                viewFlights();
                break;
            case 3:
                updateBooking();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// View available flights
void viewAvailableFlights() {
    FILE *file = fopen(FLIGHTS_FILE, "r");
    char buffer[200];
    int count = 0;

    if (file == NULL) {
        printf("Error: Could not open flights file.\n");
        system("pause");
        return;
    }

    system("cls");
    printf("============================================================\n");
    printf("                   Available Flights                        \n");
    printf("============================================================\n");

    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%d. %s", ++count, buffer);  // Display each flight with an index
    }

    if (count == 0) {
        printf("No flights are currently available.\n");
    }

    fclose(file);
    printf("============================================================\n");
    system("pause");
}

// Add a new flight
void addNewFlight() {
    FILE *file = fopen(FLIGHTS_FILE, "a");
    if (file == NULL) {
        printf("Error: Could not open flights file.\n");
        system("pause");
        return;
    }

    Flight new_flight;

    system("cls");
    printf("============================================================\n");
    printf("                     Add New Flight                         \n");
    printf("============================================================\n");
    printf("Enter Flight Number: ");
    scanf(" %[^\n]", new_flight.flight_number);
    printf("Enter Departure Location: ");
    scanf(" %[^\n]", new_flight.departure);
    printf("Enter Destination Location: ");
    scanf(" %[^\n]", new_flight.destination);
    printf("Enter Time (e.g., 10:30 AM): ");
    scanf(" %[^\n]", new_flight.time);
    printf("Enter Date (e.g., 12-Dec-2024): ");
    scanf(" %[^\n]", new_flight.date);
    printf("Enter Price per Seat: ");
    scanf("%f", &new_flight.price_per_seat);
    printf("Enter Total Seats: ");
    scanf("%d", &new_flight.total_seats);

    fprintf(file, "%s, %s, %s, %s, %s, %.2f, %d\n",
            new_flight.flight_number,
            new_flight.departure,
            new_flight.destination,
            new_flight.time,
            new_flight.date,
            new_flight.price_per_seat,
            new_flight.total_seats);

    fclose(file);
    printf("\nFlight added successfully!\n");
    system("pause");
}

// Book a ticket
void bookTickets() {
    FILE *flightsFile = fopen(FLIGHTS_FILE, "r");
    FILE *bookingsFile = fopen(BOOKINGS_FILE, "a");
    if (flightsFile == NULL || bookingsFile == NULL) {
        printf("Error: Could not open necessary files.\n");
        system("pause");
        return;
    }

    Booking new_booking;
    char buffer[200];
    int flight_choice, count = 0;
    float price_per_seat = 0.0;
    int available_seats = 0;

    system("cls");
    printf("============================================================\n");
    printf("                   Available Flights                        \n");
    printf("============================================================\n");

    while (fgets(buffer, sizeof(buffer), flightsFile)) {
        printf("%d. %s", ++count, buffer);  // Display flights with indices
    }

    if (count == 0) {
        printf("No flights available for booking.\n");
        fclose(flightsFile);
        fclose(bookingsFile);
        system("pause");
        return;
    }

    rewind(flightsFile);

    printf("============================================================\n");
    printf("Enter the flight number you want to book (1-%d): ", count);
    scanf("%d", &flight_choice);

    if (flight_choice < 1 || flight_choice > count) {
        printf("Invalid choice. Returning to dashboard...\n");
        fclose(flightsFile);
        fclose(bookingsFile);
        system("pause");
        return;
    }

    count = 0;  // Reuse count for finding the selected flight
    while (fgets(buffer, sizeof(buffer), flightsFile)) {
        count++;
        if (count == flight_choice) {
            sscanf(buffer, " %[^,], %*[^,], %*[^,], %*[^,], %*[^,], %f, %d",
                   new_booking.flight_number, &price_per_seat, &available_seats);
            break;
        }
    }

    fclose(flightsFile);

    if (available_seats <= 0) {
        printf("No seats available on this flight. Returning to dashboard...\n");
        fclose(bookingsFile);
        system("pause");
        return;
    }

    printf("Enter Your Name: ");
    scanf(" %[^\n]", new_booking.name);
    printf("Enter Your Age: ");
    scanf("%d", &new_booking.age);
    printf("Enter Seat Number (1-%d): ", available_seats);
    scanf("%d", &new_booking.seat_number);

    if (new_booking.seat_number < 1 || new_booking.seat_number > available_seats) {
        printf("Invalid seat selection. Returning to dashboard...\n");
        fclose(bookingsFile);
        system("pause");
        return;
    }

    new_booking.price = price_per_seat;

    fprintf(bookingsFile, "%s, %d, %s, %d, %.2f\n",
            new_booking.name,
            new_booking.age,
            new_booking.flight_number,
            new_booking.seat_number,
            new_booking.price);

    fclose(bookingsFile);

    printf("\nBooking successful! Total Price: $%.2f\n", new_booking.price);
    system("pause");
}