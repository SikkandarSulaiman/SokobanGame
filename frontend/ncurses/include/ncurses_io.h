#ifndef _NCURSES_IO_H
#define _NCURSES_IO_H

#define SUCCESS 0
#define FAILURE -1

#include <sokoban.h>

/*Display data in ncurses format*/
int display_ncurses(char[][MAX_COL], int);

/*Print Error Message*/
int print_user_msg(char *user_msg);

/*Get User Input*/
int get_input_ncurses(char *);

#endif

