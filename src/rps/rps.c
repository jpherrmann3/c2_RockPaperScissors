#include <stdlib.h>

#include "rps.h"

RPSChoice rps_random_choice(void) {
    return (RPSChoice)((rand() % 3) + 1); // 1-3
}

RPSResult rps_decide_winner(RPSChoice user, RPSChoice computer) {
    if (user == computer) {
        return RESULT_DRAW;
    }

    if (
        (user == RPS_ROCK       && computer == RPS_SCISSORS) ||
        (user == RPS_PAPER      && computer == RPS_ROCK) ||
        (user == RPS_SCISSORS   && computer == RPS_PAPER)
    ) {
        return RESULT_USER_WIN;
    }

    return RESULT_COMPUTER_WIN;
}

const char *rps_choice_to_string(RPSChoice choice){
    switch (choice) {
        case RPS_ROCK:      return "Rock";
        case RPS_PAPER:     return "Paper";
        case RPS_SCISSORS:  return "Scissors";
        default:            return "Unknown";
    }
}