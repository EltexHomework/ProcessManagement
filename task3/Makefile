CC := gcc
CFLAGS := -g -Werror -Wall -O2 -I$(SRC_DIR)/headers

SRC_DIR := src
BIN_DIR := bin

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SOURCES))

all: $(BIN_DIR) $(BIN_DIR)/main

$(BIN_DIR):
	@mkdir -p $@

# Compile .c files to .o files 
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Link .o files
$(BIN_DIR)/main: $(OBJECTS)
	@$(CC) $(OBJECTS) -o $@

clean:
	@rm -rf $(BIN_DIR)

.PHONY: all clean
