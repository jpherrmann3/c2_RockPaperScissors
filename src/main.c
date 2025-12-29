#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rps/rps.h"
#include "user/user.h"

int main(void){

    int wins = 0;
    int losses = 0;
    int draws = 0;

    srand((unsigned int)time(NULL));

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
            wins++;
            break;
        case RESULT_COMPUTER_WIN:
            printf("You lose!\n");
            losses++;
            break;
        case RESULT_DRAW:
            printf("It's a draw!\n");
            draws++;
            break;
        default:
            printf("Something went wrong with the result!\n");
            break;
        }

        printf("Score - Wins: %d, Losses: %d, Draws: %d\n", wins, losses, draws);
    }

    printf("Final Score - Wins: %d, Losses: %d, Draws: %d\n", wins, losses, draws);

    return 0;
}