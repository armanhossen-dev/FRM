#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_INFO_FILE "users_info.txt"
#define USER_PASS_SIZE 10 // user or password length

// Permanent credentials for admin
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

#define MAX_FLIGHTS 8

// Flight structure
typedef struct
{
    char flight_number[10];
    char departure[30];
    char destination[30];
    char time[10];
    char date[15];
    float price_per_seat;
    int total_seats;
} Flight;


// Data structure for storing user bookings
typedef struct {
    char name[50];
    int age;
    char flight_number[10];
    int seat_number;
    float price;
} Booking;




Flight flights[MAX_FLIGHTS];
int flight_count = 0;

// for passenger info
typedef struct p
{
    char name[50];
    int age;
    int chose_flight_num;
    int seat_nibo;
    int have_to_pay;
} p_info; // passenger info

// function declaration
int user_exist(const char *user, const char *pass);
//? menu or dashboard same
void signup();
void login();

void admin_Login_Portal();
void User_Login_Portal();

void admin_dashboard();
void view_Available_Flights();
void add_New_Flight();
void update_Flight();

void user_dashboard();
void user_booking_tickets();
void view_flights();
void update_Booking();

int main()
{
    int choice;
home_screen:
    system("cls");
    printf("============================================================\n");
    printf("        Welcome to the Flight Reservation System       \n");
    printf("============================================================\n");
    printf("Please choose your role to proceed:\n");
    printf("------------------------------------------------------------\n\n");
    printf("1. Admin Login\n");
    printf("2. User Login\n\n");
    printf("3. Exit\n");
    printf("Enter your choice (e.g., 1): _");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        system("cls");
        admin_Login_Portal();
        break;
    case 2:
        system("cls");
        User_Login_Portal();
        break;
    case 3:
        system("cls");
        printf("\n\nExiting the program. Goodbye!...........\n\n\n");
        exit(0);
    default:
        system("cls");
        goto home_screen;
        break;
    }
    return 0;
}

void User_Login_Portal()
{
    int ch_a;
home_ulp:
    printf("============================================================\n");
    printf("                       User Login Portal                    \n");
    printf("============================================================\n");
    printf("Please choose an option:\n\n");
    printf("1. Create New Account\n");
    printf("2. Login to Existing Account\n");
    printf("------------------------------------------------------------\n\n");
    printf("Enter your choice: _\n");
    scanf("%d", &ch_a);
    switch (ch_a)
    {
    case 1:
        system("cls");
        signup();
        break;
    case 2:
        system("cls");
        login();
        break;
    default:
        system("cls");
        goto home_ulp;
        break;
    }
}

void signup()
{
    FILE *file = fopen("users.txt", "a");
    char username[50], password[50], confirm_password[50];

    if (file == NULL)
    {
        printf("Error opening file for signup.\n");
        return;
    }
signup_page:
    system("cls");
    printf("============================================================\n");
    printf("                          Sign Up                           \n");
    printf("============================================================\n\n");

    printf("Enter a username: ");
    scanf(" %[^\n]", username);

    printf("Enter a password: ");
    scanf(" %[^\n]", password);

    printf("Confirm your password: ");
    scanf(" %[^\n]", confirm_password);

    if (strcmp(password, confirm_password) != 0)
    {
        printf("\nPasswords do not match! Please try again.\n");
        fclose(file);
        system("pause");
        goto signup_page;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    printf("\nSign up successful! You can now log in.\n");
    system("pause");
    system("cls");
    login();
}

void login()
{
    FILE *file = fopen("users.txt", "r");
    char username[50], password[50];
    char stored_username[50], stored_password[50];
    int login_successful = 0;

    if (file == NULL)
    {
        printf("Error opening file for login. Have you signed up?\n");
        signup();
    }
login_page:
    system("cls");
    printf("============================================================\n");
    printf("                           Log In                           \n");
    printf("============================================================\n\n");

    printf("Enter your username: ");
    scanf(" %[^\n]", username);

    printf("Enter your password: ");
    scanf(" %[^\n]", password);

    // Read from file and check credentials
    while (fscanf(file, "%s %s", stored_username, stored_password) != EOF)
    {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0)
        {
            login_successful = 1; // 1 means true
            break;
        }
    }
    fclose(file);

    if (login_successful)
    {
        printf("\nLogin successful! Welcome, %s.\n", username);
        system("pause");
        system("cls");
        user_dashboard();
    }
    else
    {
        printf("\nInvalid username or password. Please try again.\n");
        system("pause");
        goto login_page;
    }
}

void admin_Login_Portal()
{
    char username[50], password[50];
    int login_attempts = 3; // Limit the number of login attempts

    while (login_attempts > 0)
    {
        system("cls");
        printf("============================================================\n");
        printf("                       Admin Login Portal                   \n");
        printf("============================================================\n\n");

        printf("Enter Admin Username: ");
        scanf(" %[^\n]", username);

        printf("Enter Admin Password: ");
        scanf(" %[^\n]", password);

        // Check credentials
        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0)
        {
            printf("\nLogin Successful! Welcome, Admin!\n");
            system("pause");
            system("cls");
            admin_dashboard();
        }
        else
        {
            login_attempts--;
            printf("\nInvalid credentials. You have %d attempt(s) left.\n", login_attempts);
            system("pause");
        }
    }
    printf("\nToo many failed login attempts. Access Denied!\n");
    system("pause");
    main();
}

void admin_Dashboard()
{
    int ad_choice;
admin_dash:
    system("cls");
    printf("============================================================\n");
    printf("                       Admin Dashboard                      \n");
    printf("============================================================\n\n");
    printf("1. View Available Flights\n");
    printf("2. Add New Flight\n");
    printf("3. Update Existing Flight\n");
    printf("4. Exit\n");
    printf("------------------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &ad_choice);

    switch (ad_choice)
    {
    case 1:
        view_Available_Flights();
        break;
    case 2:
        add_New_Flight();
        break;
    case 3:
        update_Flight();
        break;
    case 4:
        printf("\nExiting Admin Dashboard...\n");
        main();
    default:
        printf("\nInvalid choice. Please try again.\n");
        system("pause");
        goto admin_dash;
    }
}

void view_Available_Flights()
{
    FILE *file = fopen("flights.txt", "r");
    char flight_info[200];
    int flight_count = 0;

    system("cls");
    printf("============================================================\n");
    printf("                    Available Flights                       \n");
    printf("============================================================\n");

    if (file == NULL)
    {
        printf("No flights available.\n");
    }
    else
    {
        // Read and display all flight information
        while (fgets(flight_info, sizeof(flight_info), file) != NULL)
        {
            flight_count++;
            printf("%d. %s", flight_count, flight_info);
        }
        fclose(file);

        if (flight_count == 0)
        {
            printf("No flights available.\n");
        }
    }

    printf("\n------------------------------------------------------------\n");
    printf("Returning to the Admin Dashboard...\n");
    system("pause");   // Pause to allow the admin to view flights
    admin_Dashboard(); // Redirect to the admin dashboard
}

void add_New_Flight()
{
    FILE *file = fopen("flights.txt", "a");
    char flight_number[10], departure[50], destination[50], time[10], date[20];

    if (file == NULL)
    {
        printf("Error: Unable to open file for adding new flights.\n");
        system("pause");
        admin_Dashboard();
        return;
    }

    system("cls");
    printf("============================================================\n");
    printf("                     Add New Flight                         \n");
    printf("============================================================\n");

    printf("Enter Flight Number (e.g., BG001): ");
    scanf(" %[^\n]", flight_number);
    printf("Enter Departure Location (e.g., Dhaka): ");
    scanf(" %[^\n]", departure);
    printf("Enter Destination Location (e.g., Chattogram): ");
    scanf(" %[^\n]", destination);
    printf("Enter Time (e.g., 08:00 AM): ");
    scanf(" %[^\n]", time);
    printf("Enter Date (e.g., 01-Dec-2024): ");
    scanf(" %[^\n]", date);

    // Append the flight details to the file
    fprintf(file, "%s, %s to %s, %s, %s\n", flight_number, departure, destination, time, date);
    fclose(file);

    printf("\nNew flight added successfully!\n");
    printf("------------------------------------------------------------\n");
    printf("Returning to the Admin Dashboard...\n");
    system("pause");
    admin_Dashboard();
}

void update_Flight()
{
    FILE *file = fopen("flights.txt", "r");
    FILE *tempFile = fopen("temp_flights.txt", "w");
    char flight_info[200], updated_flight[200];
    char flight_number_to_update[10];
    int flight_count = 0, chosen_flight = 0, current_line = 0;

    if (file == NULL || tempFile == NULL)
    {
        printf("Error: Unable to open file for updating flights.\n");
        system("pause");
        admin_Dashboard();
        return;
    }

    system("cls");
    printf("============================================================\n");
    printf("                      Update Flight                         \n");
    printf("============================================================\n");

    // Display available flights
    printf("Available Flights:\n");
    printf("------------------------------------------------------------\n");
    while (fgets(flight_info, sizeof(flight_info), file) != NULL)
    {
        flight_count++;
        printf("%d. %s", flight_count, flight_info);
    }

    if (flight_count == 0)
    {
        printf("No flights available to update.\n");
        fclose(file);
        fclose(tempFile);
        system("pause");
        admin_Dashboard();
        return;
    }

    // Allow admin to choose a flight to update
    printf("------------------------------------------------------------\n");
    printf("Enter the number of the flight you want to update: ");
    scanf("%d", &chosen_flight);

    if (chosen_flight < 1 || chosen_flight > flight_count)
    {
        printf("Invalid choice. Returning to the dashboard...\n");
        fclose(file);
        fclose(tempFile);
        system("pause");
        admin_Dashboard();
        return;
    }

    // Rewind file pointer to start
    rewind(file);

    // Loop through the file and rewrite data
    while (fgets(flight_info, sizeof(flight_info), file) != NULL)
    {
        current_line++;
        if (current_line == chosen_flight)
        {
            printf("\nEditing Flight: %s", flight_info);
            char flight_number[10], departure[50], destination[50], time[10], date[20];

            printf("Enter New Flight Number (e.g., BG001): ");
            scanf(" %[^\n]", flight_number);
            printf("Enter New Departure Location (e.g., Dhaka): ");
            scanf(" %[^\n]", departure);
            printf("Enter New Destination Location (e.g., Chattogram): ");
            scanf(" %[^\n]", destination);
            printf("Enter New Time (e.g., 08:00 AM): ");
            scanf(" %[^\n]", time);
            printf("Enter New Date (e.g., 01-Dec-2024): ");
            scanf(" %[^\n]", date);

            // Create the updated flight string
            sprintf(updated_flight, "%s, %s to %s, %s, %s\n", flight_number, departure, destination, time, date);

            // Write the updated flight to the temp file
            fputs(updated_flight, tempFile);
        }
        else
        {
            // Write the existing flight to the temp file
            fputs(flight_info, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace old file with updated data
    remove("flights.txt");
    rename("temp_flights.txt", "flights.txt");

    printf("\nFlight updated successfully!\n");
    printf("------------------------------------------------------------\n");
    printf("Returning to the Admin Dashboard...\n");
    system("pause");
    admin_Dashboard();
}

void user_dashboard()
{
}

// User Dashboard
void user_dashboard() {
    int choice;
    system("cls");
    printf("============================================================\n");
    printf("                      User Dashboard                        \n");
    printf("============================================================\n");
    printf("\n1. Book Tickets\n");
    printf("2. View Available Flights\n");
    printf("3. Update Booking\n");
    printf("4. Logout\n");
    printf("------------------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            user_booking_tickets();
            break;
        case 2:
            view_flights();
            break;
        case 3:
            update_Booking();
            break;
        case 4:
            printf("Logging out...\n");
            system("pause");
            exit(0);
        default:
            printf("Invalid choice. Try again.\n");
            system("pause");
            user_dashboard();
    }
}

// User Booking Tickets
void user_booking_tickets() {
    FILE *file = fopen("bookings.txt", "a");
    if (file == NULL) {
        printf("Error: Unable to open bookings file.\n");
        system("pause");
        user_dashboard();
        return;
    }

    Booking new_booking;
    system("cls");
    printf("============================================================\n");
    printf("                      Book Tickets                          \n");
    printf("============================================================\n");

    printf("Enter Your Name: ");
    scanf(" %[^\n]", new_booking.name);
    printf("Enter Your Age: ");
    scanf("%d", &new_booking.age);
    printf("Enter Flight Number (e.g., BG001): ");
    scanf(" %[^\n]", new_booking.flight_number);
    printf("Enter Seat Number: ");
    scanf("%d", &new_booking.seat_number);

    // Example price per seat
    new_booking.price = 500.0;

    // Write booking to file
    fprintf(file, "%s, %d, %s, %d, %.2f\n", new_booking.name, new_booking.age, 
            new_booking.flight_number, new_booking.seat_number, new_booking.price);

    printf("Booking successful! Total Price: %.2f\n", new_booking.price);
    fclose(file);

    system("pause");
    user_dashboard();
}

// View Flights
void view_flights() {
    FILE *file = fopen("flights.txt", "r");
    char flight_info[200];
    system("cls");

    printf("============================================================\n");
    printf("                   Available Flights                        \n");
    printf("============================================================\n");

    if (file == NULL) {
        printf("No flights available. Please check later.\n");
    } else {
        while (fgets(flight_info, sizeof(flight_info), file) != NULL) {
            printf("%s", flight_info);
        }
        fclose(file);
    }

    printf("------------------------------------------------------------\n");
    system("pause");
    user_dashboard();
}

// Update Booking
void update_Booking() {
    FILE *file = fopen("bookings.txt", "r");
    FILE *tempFile = fopen("temp_bookings.txt", "w");
    char booking_info[200], name_to_update[50];
    int found = 0, new_seat;
    float price = 500.0;

    if (file == NULL || tempFile == NULL) {
        printf("Error: Unable to open file for updating bookings.\n");
        system("pause");
        user_dashboard();
        return;
    }

    system("cls");
    printf("============================================================\n");
    printf("                      Update Booking                        \n");
    printf("============================================================\n");

    printf("Enter Your Name to Update Booking: ");
    scanf(" %[^\n]", name_to_update);

    while (fgets(booking_info, sizeof(booking_info), file) != NULL) {
        Booking booking;
        sscanf(booking_info, " %[^,], %d, %[^,], %d, %f",
               booking.name, &booking.age, booking.flight_number, 
               &booking.seat_number, &booking.price);

        if (strcmp(booking.name, name_to_update) == 0) {
            found = 1;

            printf("Booking Found: %s, %d, %s, %d, %.2f\n",
                   booking.name, booking.age, booking.flight_number, 
                   booking.seat_number, booking.price);

            printf("Enter New Seat Number: ");
            scanf("%d", &new_seat);

            booking.seat_number = new_seat;
            booking.price = price;  // Recalculate price if needed

            fprintf(tempFile, "%s, %d, %s, %d, %.2f\n", booking.name, booking.age, 
                    booking.flight_number, booking.seat_number, booking.price);

            printf("Booking Updated Successfully!\n");
        } else {
            fprintf(tempFile, "%s", booking_info);  // Copy unchanged data
        }
    }

    if (!found) {
        printf("No booking found with the name '%s'.\n", name_to_update);
    }

    fclose(file);
    fclose(tempFile);

    // Replace old file with updated data
    remove("bookings.txt");
    rename("temp_bookings.txt", "bookings.txt");

    system("pause");
    user_dashboard();
}