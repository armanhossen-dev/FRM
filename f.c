#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_PASS_LEN 20

// Structures
typedef struct Flight {
    int flightID;
    char destination[50];
    char date[20];
    int seatsAvailable;
    struct Flight* next;
} Flight;

typedef struct User {
    char username[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];
} User;

// Flight Linked List
Flight* flightList = NULL;

// Admin Login Stack
typedef struct AdminStack {
    char username[MAX_NAME_LEN];
    struct AdminStack* next;
} AdminStack;

AdminStack* adminLoginStack = NULL;

// Function Prototypes
void adminLoginPortal();
void adminDashboard();
void viewAvailableFlights();
void addNewFlight();
void updateFlight();

void userLoginPortal();
void signup();
void login();

void userDashboard(char* username);
void bookTickets(char* username);
void updateBooking(char* username);
void viewFlights();

void loadFlights();
void saveFlights();
void loadUsers();
void saveUsers();
void pushAdminLogin(const char* username);
void popAdminLogin();
int isAdminStackEmpty();

// File names
const char* FLIGHT_FILE = "flights.txt";
const char* USER_FILE = "users.txt";

// Helper Functions
void clearScreen() {
    printf("\033[H\033[J"); // ANSI escape code to clear the screen
}

// Admin Stack Operations
void pushAdminLogin(const char* username) {
    AdminStack* newNode = (AdminStack*)malloc(sizeof(AdminStack));
    strcpy(newNode->username, username);
    newNode->next = adminLoginStack;
    adminLoginStack = newNode;
}

void popAdminLogin() {
    if (adminLoginStack) {
        AdminStack* temp = adminLoginStack;
        adminLoginStack = adminLoginStack->next;
        free(temp);
    }
}

int isAdminStackEmpty() {
    return adminLoginStack == NULL;
}

// File Handling
void loadFlights() {
    FILE* file = fopen(FLIGHT_FILE, "r");
    if (!file) return;

    Flight* temp;
    while (!feof(file)) {
        temp = (Flight*)malloc(sizeof(Flight));
        if (fscanf(file, "%d %s %s %d", &temp->flightID, temp->destination, temp->date, &temp->seatsAvailable) != 4) {
            free(temp);
            break;
        }
        temp->next = flightList;
        flightList = temp;
    }
    fclose(file);
}

void saveFlights() {
    FILE* file = fopen(FLIGHT_FILE, "w");
    if (!file) return;

    Flight* temp = flightList;
    while (temp) {
        fprintf(file, "%d %s %s %d\n", temp->flightID, temp->destination, temp->date, temp->seatsAvailable);
        temp = temp->next;
    }
    fclose(file);
}

void loadUsers() {
    FILE* file = fopen(USER_FILE, "r");
    if (!file) return;

    User user;
    while (fscanf(file, "%s %s", user.username, user.password) == 2) {
        // Reading user data, nothing dynamic here
    }
    fclose(file);
}

void saveUsers() {
    // Implementation for saving user data
}

// Admin Functions
void adminLoginPortal() {
    char username[MAX_NAME_LEN], password[MAX_PASS_LEN];
    printf("Admin Login\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        pushAdminLogin(username);
        printf("Login Successful!\n");
        adminDashboard();
    } else {
        printf("Invalid Credentials!\n");
    }
}

void adminDashboard() {
    int choice;
    do {
        clearScreen();
        printf("Admin Dashboard\n");
        printf("1. View Available Flights\n");
        printf("2. Add New Flight\n");
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
                popAdminLogin();
                printf("Logged Out!\n");
                return;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);
}

void viewAvailableFlights() {
    Flight* temp = flightList;
    printf("Available Flights:\n");
    while (temp) {
        printf("Flight ID: %d, Destination: %s, Date: %s, Seats Available: %d\n",
               temp->flightID, temp->destination, temp->date, temp->seatsAvailable);
        temp = temp->next;
    }
    getchar();
    printf("Press Enter to continue...");
    getchar();
}

void addNewFlight() {
    Flight* newFlight = (Flight*)malloc(sizeof(Flight));
    printf("Enter Flight ID: ");
    scanf("%d", &newFlight->flightID);
    printf("Enter Destination: ");
    scanf("%s", newFlight->destination);
    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", newFlight->date);
    printf("Enter Seats Available: ");
    scanf("%d", &newFlight->seatsAvailable);

    newFlight->next = flightList;
    flightList = newFlight;

    saveFlights();
    printf("Flight added successfully!\n");
    getchar();
    printf("Press Enter to continue...");
    getchar();
}

void updateFlight() {
    int flightID, seats;
    printf("Enter Flight ID to Update: ");
    scanf("%d", &flightID);

    Flight* temp = flightList;
    while (temp && temp->flightID != flightID) {
        temp = temp->next;
    }

    if (temp) {
        printf("Enter New Seats Available: ");
        scanf("%d", &seats);
        temp->seatsAvailable = seats;
        saveFlights();
        printf("Flight updated successfully!\n");
    } else {
        printf("Flight not found!\n");
    }
    getchar();
    printf("Press Enter to continue...");
    getchar();
}

// User Functions
void userLoginPortal() {
    int choice;
    do {
        clearScreen();
        printf("User Portal\n");
        printf("1. Signup\n");
        printf("2. Login\n");
        printf("3. Exit\n");
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
                printf("Invalid choice!\n");
        }
    } while (choice != 3);
}

void signup() {
    // User Signup Logic
}

void login() {
    // User Login Logic
}

void userDashboard(char* username) {
    int choice;
    do {
        clearScreen();
        printf("User Dashboard\n");
        printf("1. View Flights\n");
        printf("2. Book Tickets\n");
        printf("3. Update Booking\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewFlights();
                break;
            case 2:
                bookTickets(username);
                break;
            case 3:
                updateBooking(username);
                break;
            case 4:
                printf("Logged Out!\n");
                return;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);
}

void bookTickets(char* username) {
    // Ticket Booking Logic
}

void updateBooking(char* username) {
    // Update Booking Logic
}

void viewFlights() {
    viewAvailableFlights();
}

// Main Function
int main() {
    loadFlights();
    loadUsers();

    int choice;
    do {
        clearScreen();
        printf("Flight Reservation System\n");
        printf("1. Admin Portal\n");
        printf("2. User Portal\n");
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
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    saveFlights();
    return 0;
}
