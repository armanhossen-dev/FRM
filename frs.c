#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define FILENAME "users_info.txt"
#define USER_OR_PASS_LEN 10

typedef struct passenger {
    char name[50];
    int age;
    char flight_number[10];
    char destination[50];
    char departure[10];
    char date[15];
} passenger_info;

int user_exists(const char *u_name, const char *pass);
void singup();
void login();
int menu();

void Book_Tickets_Page();
void book_New_Tickets();

int main() {
    int choice;
home_screen_login_singup_again:
    printf("\n\n___________________________________________________\n");
    printf("\n   Greetings from the Flight Reservation System.  ");
    printf("\n___________________________________________________");
    printf("\n\n \"Experience Seamless Flight Booking with Ease. Here, you");
    printf("\n can book, check, update, or cancel your tickets effortlessly\"");
    printf("\n\n1. Login");
    printf("\n2. Sign Up");
    printf("\n3. Exit\n");
    //printf("\n___________________________________________________\n");
    printf("\nPlease select your desired option: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            system("cls");
            login();
            break;
        case 2:
            system("cls");
            singup();
            break;
        case 3:
            system("cls");
            printf("\n\nExiting the program. Goodbye!\n\n\n\n");
            exit(0);
        default:
            printf("\nInvalid input. Please try again.\n");
            system("pause");
            system("cls");
            goto home_screen_login_singup_again;
    }
}

void singup() {
    char user[USER_OR_PASS_LEN], pass[USER_OR_PASS_LEN];
    FILE *file_pointer;
signuppage:
    printf("\n\n___________________________________________________\n");
    printf("\n             Signup Page                ");
    printf("\n___________________________________________________");
    printf("\n\nEnter New Username:(e,g admin) ");
    scanf("%s", user);
    printf("Enter New Password:(e,g 12345) ");
    scanf("%s", pass);
    printf("\nChecking...");

    if (user_exists(user, NULL)) {
        system("cls");
        printf("\nUsername already taken, please choose a new one.\n");
        goto signuppage;
    } else {
        file_pointer = fopen(FILENAME, "a");
        if (file_pointer == NULL) {
            printf("Error opening file.\n");
            return;
        }
        fprintf(file_pointer, "%s %s\n", user, pass);
        fclose(file_pointer);
        printf("\nSignup successful! You can now login.\n");
        getchar();
        getchar();
        system("cls");
        login();
    }
}

int user_exists(const char *u_name, const char *pass) {
    char store_user_name[USER_OR_PASS_LEN], store_user_pass[USER_OR_PASS_LEN];
    FILE *file = fopen(FILENAME, "r");

    // Hardcoded admin credentials check
    if (strcmp(u_name, "admin") == 0 && strcmp(pass, "12345") == 0) {
        return 1;
    }

    if (file == NULL) {
        printf("File not found.\n");
        return 0;
    }

    while (fscanf(file, "%s %s", store_user_name, store_user_pass) != EOF) {
        if (strcmp(store_user_name, u_name) == 0) {
            if (pass == NULL || strcmp(store_user_pass, pass) == 0) {
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);
    return 0;
}

void login() {
    char user[USER_OR_PASS_LEN], pass[USER_OR_PASS_LEN];
loginpage:
    printf("\n\n___________________________________________________\n");
    printf("\n             Login Page                ");
    printf("\n___________________________________________________");
    printf("\n\nEnter Username:(e,g admin) ");
    scanf("%s", user);
    printf("Enter Password:(e,g 12345) ");
    scanf("%s", pass);
    printf("___________________________________________________\n");
    printf("\nProcessing..............................");

    if (user_exists(user, pass)) {
        printf("\nLogin successful! Welcome, %s.\n", user);
        getchar();
        system("cls");
        menu();
    } else {
        int nn;
        printf("\n\nInvalid username or password.\n\n");
        printf("1. Try again.\n");
        printf("2. Create new account.\n");
        printf("Please select your desired option(1 or 2): ");
        getchar();
        scanf("%d", &nn);
        switch (nn) {
            case 1:
                system("cls");
                goto loginpage;
                break;
            case 2:
                system("cls");
                singup();
                break;
            default:
                system("cls");
                main();
                break;
        }
    }
}

int menu() {
    int num;
menu_screen:
    printf("\n\n___________________________________________________\n");
    printf("\n        Flight Reservation Management        ");
    printf("\n___________________________________________________");
    printf("\n\n1. Book Tickets");
    printf("\n2. Check Tickets");
    printf("\n3. Update Tickets");
    printf("\n4. Cancel Tickets");
    printf("\n5. Exit");
    printf("\n___________________________________________________\n");
    printf("\nPlease select your desired option: ");
    scanf("%d", &num);
    switch (num) {
        case 1:
            getchar();
            system("cls");
            printf("Booking tickets...\n");
            Book_Tickets_Page();
            exit(0);
            break;
        case 2:
        case 3:
        case 4:
            getchar();
            system("cls");
            printf("Feature coming soon...\n");
            break;
        case 5:
            getchar();
            system("cls");
            printf("Goodbye!\n");
            getchar();
            system("pause");
            main();
            break;
        default:
            printf("Invalid choice, please try again.\n");
            system("pause");
            goto menu_screen;
    }
}

void Book_Tickets_Page() {
    int n;
bookpage:
    system("cls");
    printf("___________________________________________________\n");
    printf("        Flight Reservation Management        \n");
    printf("\n___________________________________________________\n");
    printf("1. Book New Tickets\n");
    printf("2. Display Past Bookings\n");
    printf("3. Exit\n");
    printf("___________________________________________________\n");
    printf("Please select your desired option: ");
    scanf("%d", &n);

    switch (n) {
        case 1:
            system("cls");
            book_New_Tickets();
            break;
        case 2:
            system("cls");
            printf("Feature coming soon...\n");
            break;
        case 3:
            system("cls");
            menu();
            break;
        default:
            printf("Invalid choice, please try again.\n");
            system("pause");
            goto bookpage;
    }
}

void book_New_Tickets() {
    passenger_info* jatri = NULL; // This will hold passenger details dynamically
    int n_seats;
    char f_num[10], desti[50], date_of_fly[15], depart[10];
    
    system("cls");
    printf("___________________________________________________\n");
    printf("                            Book Tickets                          \n");
    printf("___________________________________________________\n");
    printf("                        *Available Flights*                       \n");
    printf("________________________________________________________________\n");
    printf("| Flight No | Departure  | Destination | Time     |    Date    |\n");
    printf("|-----------|------------|-------------|----------|------------|\n");
    printf("| BG001     | Dhaka      | Chattogram  | 08:00 AM | 01-Dec-2024|\n");
    printf("| BG002     | Dhaka      | Sylhet      | 09:30 AM | 01-Dec-2024|\n");
    printf("| BG003     | Dhaka      | Cox's Bazar | 11:00 AM | 01-Dec-2024|\n");
    printf("| BG004     | Dhaka      | Barisal     | 01:30 PM | 01-Dec-2024|\n");
    printf("| BG005     | Dhaka      | Jessore     | 03:00 PM | 01-Dec-2024|\n");
    printf("________________________________________________________________\n");

    printf("\nEnter Flight Number (e.g., BG001): ");
    scanf(" %[^\n]", f_num);

    //printf("Enter Destination (e.g., Cox's Bazar): ");
    //scanf(" %[^\n]", desti);

    //printf("Enter Departure Time (e.g., 11:00 AM): ");
    //scanf(" %[^\n]", depart);

    //printf("Enter Date (e.g., 01-Dec-2024): ");
    //scanf(" %[^\n]", date_of_fly);

    printf("\n\nHow many seats do you want to book?\n");
    scanf("%d", &n_seats);

    jatri = (passenger_info*)malloc(n_seats * sizeof(passenger_info));
    if (jatri == NULL) {
        printf("Memory Allocation Failed\n");
        return;
    }

    // Input each passenger's details
    for (int i = 0; i < n_seats; i++) {
        printf("\nEnter Details For Passenger %d:\n", i + 1);
        printf("Name: ");
        getchar(); // Consume the leftover newline character
        scanf("%[^\n]", jatri[i].name);
        printf("Age: ");
        scanf("%d", &jatri[i].age);
        strcpy(jatri[i].flight_number, f_num);
        strcpy(jatri[i].destination, desti);
        strcpy(jatri[i].departure, depart);
        strcpy(jatri[i].date, date_of_fly);
    }

    FILE* passenger_info_file = fopen("passenger_bookings.txt", "a");
    if (passenger_info_file == NULL) {
        printf("Error opening file!\n");
        free(jatri);
        return;
    }

    fprintf(passenger_info_file, "___________________________________________________\n");
    fprintf(passenger_info_file, "Flight Number: %s\n", f_num);
    fprintf(passenger_info_file, "Destination: %s\n", desti);
    fprintf(passenger_info_file, "Departure Time: %s\n", depart);
    fprintf(passenger_info_file, "Date: %s\n", date_of_fly);
    fprintf(passenger_info_file, "Number of Seats: %d\n", n_seats);
    fprintf(passenger_info_file, "___________________________________________________\n");

    for (int i = 0; i < n_seats; i++) {
        fprintf(passenger_info_file, "Passenger %d:\n", i + 1);
        fprintf(passenger_info_file, " Name: %s\n", jatri[i].name);
        fprintf(passenger_info_file, " Age: %d\n", jatri[i].age);
    }
    fprintf(passenger_info_file, "___________________________________________________\n");
    fclose(passenger_info_file);

    printf("\nCongratulations, Tickets booked successfully.\n");

    // Free the allocated memory
    free(jatri);
    system("pause");
}

