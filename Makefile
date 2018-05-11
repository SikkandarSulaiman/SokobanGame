BIN_FILE_NAME = sokoban_engine.bin

inc_paths = -I $(INC_DIR)
link_paths = -L .

INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

ofiles = ${patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, ${wildcard $(SRC_DIR)/*.c}}

CFLAGS = $(inc_paths)
LIBFLAGS = $(link_paths)

.PHONY: clean flash

$(BIN_DIR)/$(BIN_FILE_NAME): $(ofiles)
	gcc -o $@ $^ $(LIBFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(CFLAGS) -c -o $@ $< -Wall

clean:
	rm -f $(BIN_DIR)/$(BIN_FILE_NAME)
	rm -f $(ofiles)
