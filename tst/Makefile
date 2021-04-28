CC=gcc
CFLAGS= -Wall -Werror 
CPPFLAGS=-MMD -MP -g
SRC_DIR=../src
OBJ_DIR=.
SRC= $(wildcard $(SRC_DIR)/*.c)
OBJ= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC=../include
EXECS=bruteforce

all: $(EXECS)

$(EXECS): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

.PHONY: all clean

clean: 
	rm -rf *.o vgcore* $(EXECS)

