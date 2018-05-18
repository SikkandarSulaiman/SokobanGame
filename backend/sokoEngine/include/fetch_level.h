#ifndef _FETCH_LEVEL_H_
#define _FETCH_LEVEL_H_

#include <sokoban.h>
#include <game_data.h>

#define LEVEL_FILE_REL "../level_files/100Boxes.txt"
#define DIR_SEP '/'

/*
 *Prints Board
 */
int print_board(char [][MAX_COL], int);

/*
 *Get Levels in Board
 */
int get_board(game_data_t*, int *);

#endif
