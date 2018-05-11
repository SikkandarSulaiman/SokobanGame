#ifndef _FETCH_LEVEL_H_
#define _FETCH_LEVEL_H_

#include <sokoban.h>
#include <game_data.h>

#define LEVEL_FILE "text_file/100Boxes.txt"

/*
 *Prints Board
 */
int print_board(char [][MAX_COLS], int);

/*
 *Get Levels in Board
 */
int get_board(game_data_t*, int *);

#endif
