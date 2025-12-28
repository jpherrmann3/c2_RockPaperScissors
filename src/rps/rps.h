#ifndef RPS_H
#define RPS_H

typedef enum {
    RPS_EXIT = 0,
    RPS_ROCK = 1,
    RPS_PAPER = 2,
    RPS_SCISSORS = 3
} RPSChoice;

typedef enum {
    RESULT_DRAW,
    RESULT_USER_WIN,
    RESULT_COMPUTER_WIN
} RPSResult;

RPSChoice rps_random_choice(void);
RPSResult rps_decide_winner(RPSChoice user, RPSChoice computer);

const char *rps_choice_to_string(RPSChoice choice);

#endif