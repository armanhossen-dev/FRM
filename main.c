#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define FILENAME "users_info.txt"
#define USER_OR_PASS_LEN 10

typedef struct passenger{
    char name[50];
    int  age;
    char flight_number[10];
    char destination[50];
    char departure[10];
    char date[15];
    struct passenger* next;
} passenger_info;

//making the head null
passenger_info* head = NULL;


int user_exists(const char *u_name, const char *pass);
void singup();
void login();
int menu();

void Book_Tickets_Page();
void book_New_Tickets();
/*
void display_Past_Bookings();
void Check_Tickets();
void Cancel_Tickets();
void Update_Tickets();
*/

int main()
{
/**/
    system("cls");
    int choice;
home_screen_login_singup_again:
    printf("\n\n=============================================");
      printf("\n   Welcome to the Flight Reservation System  ");
      printf("\n=============================================");
    /*Seamless Flight Booking Made Easy! You Can
    Book, Check, Update Or Cancel Tickets Here.*/
 printf("\n\n \"Seamless Flight Booking Made Easy! You Can");
    printf("\n Book, Check, Update Or Cancel Tickets Here\"");
    printf("\n\n1. Login");
    printf("\n2. Sign Up");
    printf("\n3. Exit");
    printf("\n=============================================");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
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
        printf("\n\nExiting the program. Goodbye!...........\n\n\n\n");
        exit(0);
    default:
        printf("\nInvalid input. Please Try again.\n");
        system("pause");
        system("cls");
        goto home_screen_login_singup_again;
    }    
}

void singup()
{
    char user[USER_OR_PASS_LEN], pass[USER_OR_PASS_LEN];
    FILE *file_pointer;
signuppage:
    printf("\n\n=============================================");
    printf("\n             Signup Page                ");
    printf("\n=============================================");
    printf("\n\nEnte New Username: ");
    scanf("%s", &user);
    printf("Ente New Password: ");
    scanf("%s", &pass);
    printf("\nchecking...............................");

    // now system will check if the same user name is registerd before or not
    if (user_exists(user, NULL))
    {
        system("cls");
        printf("\nUsername already taken, give a new one");
        goto signuppage;
    }
    else
    {
        file_pointer = fopen(FILENAME, "a"); //"a" mode to add to the existing content
        if (file_pointer == NULL){
            printf("Error opening file\n");
            //or perror("Error opening file");
            return;
        }
        fprintf(file_pointer, "%s %s\n ", user, pass);
        fclose(file_pointer);
        printf("\nSignup successful! You can now login.\n");
        getchar();
        getchar();
        system("cls");
        login();
    }
}

int user_exists(const char *u_name, const char *pass){
    char store_user_name[USER_OR_PASS_LEN], store_user_pass[USER_OR_PASS_LEN];
    FILE *file = fopen(FILENAME, "r");

    if(file == NULL){
        printf("File Not found\n");
        return 0;
    }
    
    while(fscanf(file, "%s %s", store_user_name,store_user_pass) != EOF){
        if(strcmp(store_user_name,u_name) == 0){
            if(strcmp(store_user_pass, pass)==0){
                fclose(file);
                return 1; // 1 means true , 
            }
        }
        break;
    }
    fclose(file);
    return 0;
}

void login()
{
    char user[USER_OR_PASS_LEN], pass[USER_OR_PASS_LEN];
    loginpage:
        printf("\n\n=============================================");
        printf("\n             Login  Page                ");
        printf("\n=============================================");
        printf("\n\nEnter username: ");
        scanf("%s",&user);
        printf("Enter password: ");
        scanf("%s",&pass);
        printf("=============================================");
        printf("\nProcessing..............................");
    
    if(user_exists(user,pass)){
        printf("\nLogin successfull! Welcome %s.\n",user);
        getchar();
        system("cls");
        menu();
    }else{
        int nn;
        printf("\n\nInvalid username or password.\n\n");
        printf("1.Try again.\n");
        printf("2.Create new account.\n");
        printf("Enter decision (1 or 2): ");
        getchar();
        scanf("%d",&nn);
        switch (nn)
        {
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
        getchar();
    }
}    

int menu(){
        int num;
    menu_screen:
        printf("\n\n=============================================");
        printf("\n        Flight Reservation Management        ");
        printf("\n=============================================");
        printf("\n\n1. Book Tickets");
        printf("\n2. Check Tickets");
        printf("\n3. Update Tickets");
        printf("\n4. Cancel Tickets");
        printf("\n5. Exit");
        printf("\n=============================================");
        printf("\nEnter your choice: ");
        scanf("%d",&num);
      switch(num){
      case 1:
        getchar();
        system("cls");
        printf("booking tickets\n");
        Book_Tickets_Page();
        exit(0);
        break;

      case 2:
        getchar();
        system("cls");
        printf("Working bruh\n");
        //Check_Tickets();
        break;

      case 3:
        getchar();
        system("cls");
        printf("Working bruh\n");
        //Update_Tickets();
        break;

      case 4:
        getchar();
        system("cls");
        printf("Working bruh\n");
        //Cancel_Tickets();
        break;

      case 5:
        getchar();
        system("cls");
        printf("Working bruh\n");
        getchar();
        system("pause");
        main();
        break;

      default:
        printf("Invalid choice, choose again\n");
        system("pause");
        goto menu_screen;
        break;
      }
}



void Book_Tickets_Page(){
    int n;
    bookpage:
        system("cls"); // Clear screen (use "clear" on Linux/Mac)
        printf("=============================================\n");
        printf("        Flight Reservation Management        \n");
        printf("=============================================\n");
        printf("1. Book New Tickets\n");
        printf("2. Display Past Bookings\n");
        printf("3. Exit\n");
        printf("=============================================\n");
        printf("Enter your choice: ");
        scanf("%d",&n);

    switch (n)
    {
    case 1:
        system("cls");
        book_New_Tickets();
        break;

    case 2:
        system("cls");
        //display_Past_Bookings();
        break;

    case 3:
        system("cls");
        menu();
        break;
    
    default:
        printf("Invalid choice, choose again\n");
        system("pause");
        goto bookpage;
        break;
    }
}

void book_New_Tickets(){
    //available flights
    system("cls");
    printf("================================================================\n");
    printf("                            Book Tickets                          \n");
    printf("================================================================\n");
    printf("                        *Available Flights*                       \n");
    printf("----------------------------------------------------------------\n");
    printf("| Flight No | Departure  | Destination | Time     |    Date    |\n");
    printf("|-----------|------------|-------------|----------|------------|\n");
    printf("| BG001     | Dhaka      | Chattogram  | 08:00 AM | 01-Dec-2024|\n");
    printf("| BG002     | Dhaka      | Sylhet      | 09:30 AM | 01-Dec-2024|\n");
    printf("| BG003     | Dhaka      | Cox's Bazar | 11:00 AM | 01-Dec-2024|\n");
    printf("| BG004     | Dhaka      | Barisal     | 01:30 PM | 01-Dec-2024|\n");
    printf("| BG005     | Dhaka      | Jessore     | 03:00 PM | 01-Dec-2024|\n");
    printf("------------------------------------------------------------------\n");

    passenger_info* jatri = NULL; // this will hold passenger dynamically
    int n_seats;
    char f_num[10], desti, date_of_fly[15], depart[10];
    
    printf("Enter Flight Number (e.g., BG001): ");
    scanf(" %[^\n]", f_num);
    
    printf("Enter Destination (e.g., Cox's Bazar): ");
    scanf(" %[^\n]", desti);

    /*printf("Enter Departure Time (e.g., 11:00 AM): ");
    scanf(" %[^\n]", depart);*/
    
    printf("Enter Date (e.g., 01-Dec-2024): ");
    scanf(" %[^\n]", date_of_fly);
    
    printf("\n\nHow many seat do you want to book?\n");
    scanf("%d", &n_seats);

    jatri = (passenger_info*)malloc(n_seats*sizeof(passenger_info));
    if(jatri == NULL){
        printf("Memory Allocation Failed\n");
        return;
    }
    /*typedef struct passenger{
    char name[50];
    int  age;
    char flight_number[10];
    char destination[50];
    char departure[10];
    char date[15];
    struct passenger* next;
} passenger_info;

int n_seats;
char f_num[10], desti, date[15];
*/
    //input each passenger details
    for(int i = 0; i< n_seats; i++){
        printf("\nEnter Details For Passenger %d:\n",i+1);
        printf("Name: ");
        scanf("%[^\n]", jatri[i].name);
        printf("Age: ");
        scanf("%d", &jatri[i].age);
        strcpy(jatri[i].flight_number, f_num);
        strcpy(jatri[i].destination, desti);
        /*strcpy(jatri[i].departure, depart);*/
        strcpy(jatri[i].date, date_of_fly);
    }

    FILE* passenger_info_file = fopen("passenger_bookings.txt", "a");
    if(passenger_info_file = NULL){
        printf("Error opening file!\n");
        free(jatri);
        return;
    }
    fprintf(passenger_info_file, "=============================================\n");
    fprintf(passenger_info_file, "Flight Number: %s\n", f_num);
    fprintf(passenger_info_file, "Destination: %s\n", desti);
    fprintf(passenger_info_file, "Departure Time: %s\n", depart);
    fprintf(passenger_info_file, "Date: %s\n", date_of_fly);
    fprintf(passenger_info_file, "Number of Seats: %d\n", n_seats);
    fprintf(passenger_info_file, "---------------------------------------------\n");

    for(int i = 0; i < n_seats; i++){
        fprintf(passenger_info_file, "Passenger %d:\n", i+1);
        fprintf(passenger_info_file, " Name: %s\n", jatri[i].name);
        fprintf(passenger_info_file, " Age: %d\n", jatri[i].age);
    }
    fprintf(passenger_info_file, "=============================================\n");
    fclose(passenger_info_file);

    //Free the allocated memory
    free(jatri);
    system("pause");
}
/*

void display_Past_Bookings();
void Check_Tickets();
void Cancel_Tickets();
void Update_Tickets();


*/