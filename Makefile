CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g -I src
BUILD = build

APP = rock_paper_scissors
TEST = test_rock_paper_scissors

APP_SRCS = src/main.c src/rps/rps.c src/user/user.c
TEST_SRCS = tests/test_rps.c src/rps/rps.c src/user/user.c

all: $(APP)

$(APP): $(APP_SRCS)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST): $(TEST_SRCS)
	$(CC) $(CFLAGS) $^ -o $@

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(APP) $(TEST) *.log ./tests/test.log