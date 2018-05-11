#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

#include <sokoban.h>

enum bit_label {
	BIT_SPACE = 0,
	BIT_PLAYER = (1 << 0),
	BIT_TARGET = (1 << 1),
	BIT_WALL = (1 << 2),
	BIT_BOX = (1 << 3)
};

enum general {
	ABORT = -2,
	FAILURE,
	SUCCESS
};

enum redirect_indices {
	INPUT_END = 0,
	INPUT_PROCESS,
	GET_BOARD,
	GAME_LOGIC,
	OUTPUT_END,
	QUIT_GAME
};

#define GAME_START 0x01
#define LEVEL_START 0x02

typedef struct {
	int err;
	int sys_cmd;
	int col_count;
	int row_count;
	int player_pos;
	int game_status;
	long next_level;
	long current_level;
	char user_cmd[CMD_LEN_MAX];
	char level[MAX_ROW][MAX_COL];
} game_data_t;


#define ERR_BIT 0x4000
#define ERR_IO 0x400
#define ERR_INT 0x200
#define ERR_BOARD 0x100

#define ERR_USER_CMD (ERR_BIT | ERR_IO | 2)
#define ERR_NO_GAME (ERR_BIT | ERR_IO | 3)

#define ERR_PLAYER (ERR_BIT | ERR_BOARD | 3)
#define ERR_MOVE (ERR_BIT | ERR_BOARD | 4)

#define ERR_NO_PLAYER (ERR_BIT | ERR_BOARD | 5)
#define ERR_NO_TARGET (ERR_BIT | ERR_BOARD | 7)
#define ERR_BOX_TARGET_COUNT (ERR_BIT | ERR_BOARD | 6)
#define ERR_LEFT_WALL (ERR_BIT | ERR_BOARD | 8)
#define ERR_TOP_WALL (ERR_BIT | ERR_BOARD | 9)
#define ERR_RIGHT_WALL (ERR_BIT | ERR_BOARD | 10)
#define ERR_BOTTOM_WALL (ERR_BIT | ERR_BOARD | 11)

#define ERR_OPEN_LEVEL_FILE (ERR_BIT | ERR_INT | 1)
#define ERR_CLOSE_LEVEL_FILE (ERR_BIT | ERR_INT | 2)

#define ERR_GAME_FINISHED (ERR_BIT | ERR_INT | 3)

#endif
