BIN_FILE_NAME = ncurses_display

inc_paths = -I $(INC_DIR)
link_paths = -L .

DIRS_PATH = ./

INC_DIR = $(DIRS_PATH)include/
SRC_DIR = $(DIRS_PATH)src/
OBJ_DIR = $(DIRS_PATH)obj/
BIN_DIR = $(DIRS_PATH)bin/

hfiles = ${wildcard $(INC_DIR)*.h}
cfiles = ${wildcard $(SRC_DIR)*.c}
ofiles = ${patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(cfiles)}
binfile = $(BIN_DIR)$(BIN_FILE_NAME)

CFLAGS = $(inc_paths)
LIBFLAGS = $(link_paths) -lncurses

.PHONY: clean

$(binfile): $(ofiles)
	gcc -o $@ $^ $(LIBFLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(hfiles)
	gcc $(CFLAGS) -c -o $@ $< -Wall

clean:
	rm -f $(binfile)
	rm -f $(ofiles)
