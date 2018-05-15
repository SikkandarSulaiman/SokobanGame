#ifndef _SOKOBAN_H_
#define _SOKOBAN_H_

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 3000

#define CMD_LEN_MAX 5
#define MAX_ROW 20
#define MAX_COL 20
#define INFO_MSG_LEN 100

#define U_UP "w"
#define U_DOWN "s"
#define U_LEFT "a"
#define U_RIGHT "d"

#define U_START "b"
#define U_QUIT "q"
#define U_RESET "r"
#define U_NEXT "n"

enum char_labels {
	CHAR_PLAYER = '@',
	CHAR_TARGET = '.',
	CHAR_PLACED = '*',
	CHAR_P_ON_T = '+',
	CHAR_BOX = '$',
	CHAR_WALL = '#',
	CHAR_SPACE = ' '
};

typedef struct {
	int err_flag;
	int col_count;
	int row_count;
	char err_msg[INFO_MSG_LEN];
	char level[MAX_ROW][MAX_COL];
} out_data_t;

#endif

