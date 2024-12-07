#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_INFO_FILE "users.txt"
#define FLIGHTS_FILE "flights.txt"
#define BOOKINGS_FILE "bookings.txt"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"
#define MAX_FLIGHTS 8
#define MAX_INPUT_SIZE 100

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

void clear_screen() {
    system("cls || clear");
}

void pause() {
    printf("\nPress Enter to continue...");
    getchar();
}

void admin_login();
void user_login();
void signup();
void login();
void admin_dashboard();
void view_available_flights();
void add_new_flight();
void update_flight();
void user_dashboard();
void book_ticket();
void view_flights();
void update_booking();
void load_flights();

// Global storage
Flight flights[MAX_FLIGHTS];
int flight_count = 0;

// Main function
int main() {
    int choice;

    while (1) {
        clear_screen();
        printf("============================================================\n");
        printf("            Welcome to the Flight Reservation System        \n");
        printf("============================================================\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume trailing newline

        switch (choice) {
        case 1:
            admin_login();
            break;
        case 2:
            user_login();
            break;
        case 3:
            printf("\nExiting the program. Goodbye!\n");
            exit(0);
        default:
            printf("\nInvalid choice. Try again.\n");
            pause();
        }
    }
    return 0;
}

// Admin login portal
void admin_login() {
    char username[MAX_INPUT_SIZE], password[MAX_INPUT_SIZE];
    int attempts = 3;

    while (attempts-- > 0) {
        clear_screen();
        printf("============================================================\n");
        printf("                       Admin Login                          \n");
        printf("============================================================\n");
        printf("Username: ");
        scanf(" %[^\n]", username);
        printf("Password: ");
        scanf(" %[^\n]", password);

        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("\nLogin successful! Welcome, Admin.\n");
            pause();
            admin_dashboard();
            return;
        } else {
            printf("\nInvalid credentials. %d attempt(s) remaining.\n", attempts);
        }
        pause();
    }

    printf("\nToo many failed attempts. Returning to main menu.\n");
    pause();
}

// User login portal
void user_login() {
    int choice;

    while (1) {
        clear_screen();
        printf("============================================================\n");
        printf("                       User Login Portal                    \n");
        printf("============================================================\n");
        printf("1. Create New Account\n");
        printf("2. Login to Existing Account\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

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
            printf("\nInvalid choice. Try again.\n");
            pause();
        }
    }
}

// Sign up for a new user
void signup() {
    FILE *file = fopen(USER_INFO_FILE, "a");
    char username[MAX_INPUT_SIZE], password[MAX_INPUT_SIZE], confirm_password[MAX_INPUT_SIZE];

    if (!file) {
        perror("Error opening user info file");
        pause();
        return;
    }

    clear_screen();
    printf("============================================================\n");
    printf("                          Sign Up                           \n");
    printf("============================================================\n");

    printf("Enter username: ");
    scanf(" %[^\n]", username);
    printf("Enter password: ");
    scanf(" %[^\n]", password);
    printf("Confirm password: ");
    scanf(" %[^\n]", confirm_password);

    if (strcmp(password, confirm_password) != 0) {
        printf("\nPasswords do not match. Try again.\n");
    } else {
        fprintf(file, "%s %s\n", username, password);
        printf("\nSign up successful! You can now log in.\n");
    }

    fclose(file);
    pause();
}

// Login for an existing user
void login() {
    FILE *file = fopen(USER_INFO_FILE, "r");
    char username[MAX_INPUT_SIZE], password[MAX_INPUT_SIZE];
    char stored_username[MAX_INPUT_SIZE], stored_password[MAX_INPUT_SIZE];
    int login_successful = 0;

    if (!file) {
        printf("No user accounts found. Please sign up first.\n");
        pause();
        return;
    }

    clear_screen();
    printf("============================================================\n");
    printf("                           Log In                           \n");
    printf("============================================================\n");

    printf("Enter username: ");
    scanf(" %[^\n]", username);
    printf("Enter password: ");
    scanf(" %[^\n]", password);

    while (fscanf(file, "%s %s", stored_username, stored_password) != EOF) {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
            login_successful = 1;
            break;
        }
    }

    fclose(file);

    if (login_successful) {
        printf("\nLogin successful! Welcome, %s.\n", username);
        pause();
        user_dashboard();
    } else {
        printf("\nInvalid username or password. Try again.\n");
        pause();
    }
}

// Admin dashboard
void admin_dashboard() {
    int choice;

    while (1) {
        clear_screen();
        printf("============================================================\n");
        printf("                       Admin Dashboard                      \n");
        printf("============================================================\n");
        printf("1. View Available Flights\n");
        printf("2. Add New Flight\n");
        printf("3. Update Existing Flight\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            view_available_flights();
            break;
        case 2:
            add_new_flight();
            break;
        case 3:
            update_flight();
            break;
        case 4:
            return;
        default:
            printf("\nInvalid choice. Try again.\n");
            pause();
        }
    }
}

// View all available flights
void view_available_flights() {
    FILE *file = fopen(FLIGHTS_FILE, "r");
    char flight_info[200];
    int count = 0;

    clear_screen();
    printf("============================================================\n");
    printf("                   Available Flights                        \n");
    printf("============================================================\n");

    if (!file) {
        printf("No flights found.\n");
    } else {
        while (fgets(flight_info, sizeof(flight_info), file)) {
            printf("%d. %s", ++count, flight_info);
        }
        fclose(file);
    }

    if (count == 0) {
        printf("No flights available.\n");
    }
    pause();
}

// Add a new flight
void add_new_flight() {
    FILE *file = fopen(FLIGHTS_FILE, "a");
    char flight_number[10], departure[30], destination[30], time[10], date[15];
    float price;
    int seats;

    if (!file) {
        perror("Error opening flights file");
        pause();
        return;
    }

    clear_screen();
    printf("============================================================\n");
    printf("                      Add New Flight                        \n");
    printf("============================================================\n");

    printf("Enter Flight Number: ");
    scanf(" %[^\n]", flight_number);
    printf("Enter Departure Location: ");
    scanf(" %[^\n]", departure);
    printf("Enter Destination Location: ");
    scanf(" %[^\n]", destination);
    printf("Enter Time: ");
    scanf(" %[^\n]", time);
    printf("Enter Date: ");
    scanf(" %[^\n]", date);
    printf("Enter Price Per Seat: ");
    scanf("%f", &price);
    printf("Enter Total Seats: ");
    scanf("%d", &seats);

    fprintf(file, "%s %s %s %s %s %.2f %d\n", flight_number, departure, destination, time, date, price, seats);
    fclose(file);

    printf("\nNew flight added successfully.\n");
    pause();
}

// Update an existing flight
void update_flight() {
    // Add logic for updating flights based on the existing implementation
}

// User dashboard
void user_dashboard() {
    int choice;

    while (1) {
        clear_screen();
        printf("============================================================\n");
        printf("                      User Dashboard                        \n");
        printf("============================================================\n");
        printf("1. Book Tickets\n");
        printf("2. View Available Flights\n");
        printf("3. Update Booking\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            book_ticket();
            break;
        case 2:
            view_flights();
            break;
        case 3:
            update_booking();
            break;
        case 4:
            return;
        default:
            printf("\nInvalid choice. Try again.\n");
            pause();
        }
    }
}

// Book a ticket
void book_ticket() {
    FILE *file = fopen(BOOKINGS_FILE, "a");
    Booking booking;

    if (!file) {
        perror("Error opening bookings file");
        pause();
        return;
    }

    clear_screen();
    printf("============================================================\n");
    printf("                      Book Ticket                           \n");
    printf("============================================================\n");

    printf("Enter Name: ");
    scanf(" %[^\n]", booking.name);
    printf("Enter Age: ");
    scanf("%d", &booking.age);
    printf("Enter Flight Number: ");
    scanf(" %[^\n]", booking.flight_number);
    printf("Enter Seat Number: ");
    scanf("%d", &booking.seat_number);
    booking.price = 500.0; // Example price, can be adjusted dynamically

    fprintf(file, "%s %d %s %d %.2f\n", booking.name, booking.age, booking.flight_number, booking.seat_number, booking.price);
    fclose(file);

    printf("\nTicket booked successfully! Total Price: %.2f\n", booking.price);
    pause();
}

// View flights
void view_flights() {
    view_available_flights();
}

// Update booking
void update_booking() {
    FILE *file = fopen(BOOKINGS_FILE, "r");
    FILE *tempFile = fopen("temp_bookings.txt", "w");
    char booking_info[200], name_to_update[50];
    int found = 0;
    int new_seat;
    float price_per_seat = 500.0; // Default price

    if (!file || !tempFile) {
        perror("Error accessing bookings file");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        pause();
        return;
    }

    clear_screen();
    printf("============================================================\n");
    printf("                     Update Booking                         \n");
    printf("============================================================\n");
    printf("Enter your name to find your booking: ");
    scanf(" %[^\n]", name_to_update);

    while (fgets(booking_info, sizeof(booking_info), file)) {
        Booking booking;
        sscanf(booking_info, " %[^,], %d, %[^,], %d, %f",
               booking.name, &booking.age, booking.flight_number, 
               &booking.seat_number, &booking.price);

        if (strcmp(booking.name, name_to_update) == 0) {
            found = 1;
            printf("\nCurrent Booking:\n");
            printf("Name: %s\nAge: %d\nFlight: %s\nSeat: %d\nPrice: %.2f\n",
                   booking.name, booking.age, booking.flight_number, 
                   booking.seat_number, booking.price);

            printf("\nEnter new seat number: ");
            scanf("%d", &new_seat);

            // Update seat and price
            booking.seat_number = new_seat;
            booking.price = price_per_seat;

            fprintf(tempFile, "%s, %d, %s, %d, %.2f\n",
                    booking.name, booking.age, booking.flight_number,
                    booking.seat_number, booking.price);

            printf("\nBooking updated successfully!\n");
        } else {
            fputs(booking_info, tempFile); // Write unchanged bookings
        }
    }

    if (!found) {
        printf("\nNo booking found for the name '%s'.\n", name_to_update);
    }

    fclose(file);
    fclose(tempFile);

    // Replace old bookings file with updated data
    remove(BOOKINGS_FILE);
    rename("temp_bookings.txt", BOOKINGS_FILE);

    pause();
}
