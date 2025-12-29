#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "rps/rps.h"
#include "user/user.h"

#define MAX_USERS 100
#define USERS_FILE "users.csv"

void read_string(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // strip newline
    }
}

void print_users(const User *users, size_t count) {
    for (size_t i = 0; i < count; i++) {
        printf("%zu) %s (W:%d L:%d D:%d)\n",
        i +1,
        users[i].name,
        users[i].wins,
        users[i].losses,
        users[i].draws
        );
    }
}

User *startup_menu(User *users, size_t *user_count) {
    while (1) {
        printf("\n=== Rock Paper Scissors ===\n");

        if (*user_count ==0) {
            printf("No users found. Please create a new user.\n");
            printf("Enter your name: ");

            char name[MAX_NAME_LEN];
            read_string(name, sizeof(name));
            return create_user(users, user_count, name);
        }

        printf("1) Create new user\n");
        printf("2) Select existing user\n");
        printf("0) Exit\n");
        printf("> ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            return NULL;
        }

        // clear stdin buffer
        while (getchar() != '\n');

        if (choice == 0) {
            return NULL;
        }

        if (choice == 1) {
            char name[MAX_NAME_LEN];
            printf("Enter your name: ");
            read_string(name, sizeof(name));

            if (find_user(users, *user_count, name)) {
                printf("User already exists.\n");
                continue;
            }

            return create_user(users, user_count, name);
        }

        if (choice == 2) {
            print_users(users, *user_count);
            printf("Select user by number: ");

            size_t index;
            if (scanf("%zu", &index) != 1) {
                continue;
            }

            while (getchar() != '\n');

            if (index < 1 || index > *user_count) {
                printf("Invalid user selection.\n");
                continue;
            }

            return &users[index - 1];
        }

        printf("Invalid choice.\n");
    }
}

int main(void) {

    User users[MAX_USERS];
    size_t user_count = load_users(USERS_FILE, users, MAX_USERS);

    User *current_user = startup_menu(users, &user_count);
    if (!current_user) {
        printf("Goodbye.\n");
        return 0;
    }

    current_user->last_sign_on = time(NULL);

    printf("Welcome, %s! Let's play Rock Paper Scissors!\n", current_user->name);

    while (1){
        int input;

        printf("\nChoose:\n");
        printf("\t1) Rock\n");
        printf("\t2) Paper\n");
        printf("\t3) Scissors\n");
        printf("\t0) Exit\n");
        printf(">");

        if (scanf("%d", &input) != 1) {
            printf("invalid input.\n");
            break;
        }

        if (input == RPS_EXIT) {
            break;
        }

        if (input < 1 || input > 3) {
            printf("Please choose 1, 2, 3, or 0.\n");
            continue;
        }

        RPSChoice user = (RPSChoice)input;
        RPSChoice computer = rps_random_choice();

        printf("You chose: %s\n", rps_choice_to_string(user));
        printf("Computer chose: %s\n", rps_choice_to_string(computer));

        RPSResult result = rps_decide_winner(user, computer);

        switch (result)
        {
        case RESULT_USER_WIN:
            printf("You win!\n");
            current_user->wins++;
            break;
        case RESULT_COMPUTER_WIN:
            printf("You lose!\n");
            current_user->losses++;
            break;
        case RESULT_DRAW:
            printf("It's a draw!\n");
            current_user->draws++;
            break;
        default:
            printf("Something went wrong with the result!\n");
            break;
        }

        printf("Score - Wins: %d, Losses: %d, Draws: %d\n", current_user->wins, current_user->losses, current_user->draws);
    }

    printf("Final Score - Wins: %d, Losses: %d, Draws: %d\n", current_user->wins, current_user->losses, current_user->draws);
    save_users(USERS_FILE, users, user_count);
    printf("Goodbye, %s!\n", current_user->name);
    return 0;
}