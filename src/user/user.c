#include "user.h"

#include <stdio.h>
#include <string.h>

size_t load_users(const char *filename, User *users, size_t max_users){
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        return 0; // file may not exist yet
    }

    char line[256];
    size_t count = 0;

    //skip header
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) && count < max_users){
        User *u = &users[count];

        sscanf(
            line, "%63[^,],%ld,%d,%d,%d",
            u->name,
            &u->last_sign_on,
            &u->wins,
            &u->losses,
            &u->draws
        );
        count++;
    }

    fclose(fp);
    return count;
}

void save_users(const char *filename, const User *users, size_t count){
    FILE *fp = fopen(filename, "W");
    if (!fp){
        return;
    }

    fprintf(fp, "name,last_sign_on,wins,losses,draws\n");

    for (size_t i = 0; i < count; i++){
        fprintf(
            fp, "%s,%ld,%d,%d,%d\n",
            users[i].name,
            users[i].last_sign_on,
            users[i].wins,
            users[i].losses,
            users[i].draws
        );
    }

    fclose(fp);
}

User *find_user(User *users, size_t count, const char *name){
    for (size_t i = 0; i < count; i++) {
        if (strcmp(users[i].name, name) == 0) {
            return &users[i];
        }
    }
    return NULL;
}

User *create_user(User *users, size_t *count, const char *name) {
    User *u = &users[*count];

    strncpy(u->name, name, MAX_NAME_LEN - 1);
    u->name[MAX_NAME_LEN - 1] = '\0';
    u->last_sign_on = time(NULL);
    u->wins = 0;
    u->losses = 0;
    u->draws = 0;

    (*count)++;
    return u;
}