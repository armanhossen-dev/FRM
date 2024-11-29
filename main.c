#include<stdio.h> 
#include<stdlib.h>
#include<string.h>

#define FILENAME "users_info.txt"
#define USER_OR_PASS_LEN 10


int user_exists(const char *u_name, const char *pass);
void signup();
void login();
int menu();
//void Book_Tickets();
//void Check_Tickets();
//void Cancel_Tickets();
//void Update_Tickets();


int main()
{
/**/system("cls");
    int choice;
home_screen_login_signup_again:
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
        signup();
        break;
    case 3:
        system("cls");
        printf("\n\nExiting the program. Goodbye!...........\n\n\n\n");
        exit(0);
    default:
        printf("\nInvalid input. Please Try again.\n");
        system("pause");
        system("cls");
        goto home_screen_login_signup_again;
    }    
}

void signup()
{
    char user[USER_OR_PASS_LEN], pass[USER_OR_PASS_LEN];
    FILE *file_pointer;
signuppage:
    printf("\n\n=============================================");
      printf("\n             Signup Page                     ");
      printf("\n=============================================");
    printf("\n\nEnte New Username: ");
    scanf("%s", &user);
        printf("Ente New Password: ");
    scanf("%s", &pass);
     printf("\nchecking.....................................\n");
 
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
    }else{
        int n;
        printf("\nInvalid username or password. Try again.\n");
        getchar();
        printf("1. Try Again\n2. Create a New Account\n");
        scanf("%d",&n);
        switch(n){
            case 1:
                system("cls");
                goto loginpage;
                break;
            case 2:
                system("cls");
                signup();
                break;
            default:
                system("cls");
                goto loginpage;
                break;
        }
    }
    getchar();
    system("cls");
    menu();
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
        printf("\n5. Menu");
        printf("\n=============================================");
        printf("\nEnter your choice: ");
        scanf("%d",&num);
      switch(num){
        case 1:
            getchar();
            system("cls");
            printf("booking tickets\n");
            //Book_Tickets();
            exit(0);
            break;

        case 2:
            getchar();
            system("cls");
            printf("Checking tickets\n");
            system("pause");
            //Check_Tickets();
            break;

        case 3:
            getchar();
            system("cls");
            printf("Update tickets\n");
            system("pause");
            //Update_Tickets();
            break;

        case 4:
            getchar();
            system("cls");
            printf("Cancel tickets\n");
            system("pause");
            //Cancel_Tickets();
            break;

        case 5:
            getchar();
            system("cls");
            system("pause");
            system("cls");
            main();
            break;

        default:
            printf("Invalid choice, Please Try again.\n");
            system("pause");
            goto menu_screen;
            break;
      }
}
//void Book_Tickets();
//void Check_Tickets();
//void Cancel_Tickets();
//void Update_Tickets();


