# LEBOULENGER - LEFEBVRE
# Projet Algorithmie avancée
# Sujet : Fin du monopole
CC=gcc
CFLAGS= -Wall -Werror -g

SRC_DIR=src
OBJ_DIR=obj

CPPFLAGS=-Iinclude
SRC= $(wildcard $(SRC_DIR)/*.c)
OBJ= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXECS=monopole

all: $(EXECS)

$(EXECS): $(OBJ) 
	$(CC)  $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	if [ ! -d "obj" ]; then mkdir obj; fi
	$(CC)   $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

.PHONY: all clean

clean: 
	rm -rf $(OBJ_DIR)/* vgcore* $(EXECS)

