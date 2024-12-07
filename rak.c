#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Seat {
    int seatNumber;
    int isBooked;
    struct Seat* next;
} Seat;

typedef struct Movie {
    char name[50];
    int price;
    Seat* seats;
    struct Movie* next;
} Movie;

Movie* movieList = NULL;

void addMovie(char* name, int price) {
    Movie* newMovie = (Movie*)malloc(sizeof(Movie));
    strcpy(newMovie->name, name);
    newMovie->price = price;
    newMovie->seats = NULL;

    for (int i = 1; i <= 10; i++) {
        Seat* newSeat = (Seat*)malloc(sizeof(Seat));
        newSeat->seatNumber = i;
        newSeat->isBooked = 0;
        newSeat->next = newMovie->seats;
        newMovie->seats = newSeat;
    }

    newMovie->next = movieList;
    movieList = newMovie;
}

void displayMovies() {
    Movie* temp = movieList;
    printf("Available Movies:\n");
    while (temp != NULL) {
        printf("Movie: %s, Price: $%d\n", temp->name, temp->price);
        temp = temp->next;
    }
}

void displaySeats(Movie* movie) {
    Seat* temp = movie->seats;
    printf("Seats for %s:\n", movie->name);
    while (temp != NULL) {
        printf("Seat %d - %s\n", temp->seatNumber, temp->isBooked ? "Booked" : "Available");
        temp = temp->next;
    }
}

void bookSeat(Movie* movie, int seatNumber) {
    Seat* temp = movie->seats;
    while (temp != NULL) {
        if (temp->seatNumber == seatNumber) {
            if (temp->isBooked) {
                printf("Seat already booked.\n");
                return;
            }
            temp->isBooked = 1;
            printf("Seat %d booked successfully for %s.\n", seatNumber, movie->name);
            return;
        }
        temp = temp->next;
    }
    printf("Seat not found.\n");
}

Movie* findMovie(char* name) {
    Movie* temp = movieList;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

int verifyAdmin() {
    char userId[50], password[50];
    printf("Enter Admin User ID: ");
    scanf("%s", userId);
    printf("Enter Admin Password: ");
    scanf("%s", password);
    
    if (strcmp(userId, "admin718") == 0 && strcmp(password, "admin") == 0) {
        return 1;
    } else {
        printf("Invalid User ID or Password.\n");
        return 0;
    }
}

int verifyUser() {
    char userId[50], password[50];
    printf("Enter User User ID: ");
    scanf("%s", userId);
    printf("Enter User Password: ");
    scanf("%s", password);
    
    if (strcmp(userId, "user807") == 0 && strcmp(password, "user") == 0) {
        return 1;
    } else {
        printf("Invalid User ID or Password.\n");
        return 0;
    }
}

void adminPanel() {
    if (!verifyAdmin()) {
        return;
    }

    char name[50];
    int price;
    printf("Enter movie name: ");
    scanf("%s", name);
    printf("Enter ticket price: ");
    scanf("%d", &price);
    addMovie(name, price);
    printf("Movie added successfully.\n");
}

void userPanel() {
    if (!verifyUser()) {
        return;
    }

    char movieName[50];
    int seatNumber;
    displayMovies();
    printf("Enter movie name to book: ");
    scanf("%s", movieName);
    Movie* movie = findMovie(movieName);
    if (movie != NULL) {
        displaySeats(movie);
        printf("Enter seat number to book: ");
        scanf("%d", &seatNumber);
        bookSeat(movie, seatNumber);
    } else {
        printf("Movie not found.\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Admin Panel\n2. User Panel\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                adminPanel();
                break;
            case 2:
                userPanel();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid option.\n");
        }
    }
    return 0;
}