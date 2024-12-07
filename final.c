#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define USER_INFO_FILE "users_info.txt"
#define USER_PASS_SIZE 10 // user or password length

// Permanent credentials for admin
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

#define MAX_FLIGHTS 8

// Flight structure
typedef struct {
    char flight_number[10];
    char departure[30];
    char destination[30];
    char time[10];
    char date[15];
    float price_per_seat;
    int total_seats;
} Flight;


Flight flights[MAX_FLIGHTS];
int flight_count = 0;

//for passenger info
typedef struct p{
    char name[50]; 
    int age;
    int chose_flight_num;
    int seat_nibo;
    int have_to_pay;
}p_info; //passenger info

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

int main(){
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

    switch (choice){
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

void  User_Login_Portal(){
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



void admin_Login_Portal() {
    char username[50], password[50];
    int login_attempts = 3; // Limit the number of login attempts

    while (login_attempts > 0) {
        system("cls");
        printf("============================================================\n");
        printf("                       Admin Login Portal                   \n");                                         
        printf("============================================================\n\n");

        printf("Enter Admin Username: ");
        scanf(" %[^\n]", username);

        printf("Enter Admin Password: ");
        scanf(" %[^\n]", password);

        // Check credentials
        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("\nLogin Successful! Welcome, Admin!\n");
            system("pause");
            system("cls");
            admin_dashboard();  
        } else {
            login_attempts--;
            printf("\nInvalid credentials. You have %d attempt(s) left.\n", login_attempts);
            system("pause");
        }
    }
    printf("\nToo many failed login attempts. Access Denied!\n");
    system("pause");
    main();
}

void admin_Dashboard() {
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

        switch (ad_choice) {
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
