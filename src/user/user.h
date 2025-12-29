#ifndef USER_H
#define USER_H

#include <time.h>

#define MAX_NAME_LEN 64

typedef struct {
    char name[MAX_NAME_LEN];
    time_t last_sign_on;
    int wins;
    int losses;
    int draws;
} User;

size_t load_users(const char *filename, User *users, size_t max_users);

void save_users(const char *filename, const User *users, size_t count);

User *find_user(User *users, size_t count, const char *name);

User *create_user(User *users, size_t *count, const char *name);

#endif