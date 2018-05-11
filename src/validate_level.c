#include <stdio.h>
#include <string.h>

#include <game_data.h>

static int check_board_field(char level[][MAX_COLS], int row_len)
{
	int player_pos = 0;
	int player = 0;
	int target = 0;
	int box = 0;
	int row;
	int col;
	int col_len = strlen(level[0]);

	for (row = 0; row < row_len; row++) {

		for (col = 0; col < col_len; col++) {
			if (level[row][col] == CHAR_PLAYER || level[row][col] == CHAR_P_ON_T) {
				if (level[row][col]  == CHAR_P_ON_T)
					target++;
				player++;
				player_pos |= (row << 4);
				player_pos |= col;
			} else if (level[row][col] == CHAR_TARGET)
				target++;
			else if (level[row][col] == CHAR_BOX)
				box++;
		}
	}

	if (player != 1)
		return ERR_NO_PLAYER;
	
	if (target != box)
		return ERR_BOX_TARGET_COUNT;
	
	if (target == box && target == 0)
		return ERR_NO_TARGET;

	return SUCCESS;
}

static int check_row_order(char level[][MAX_COLS], int row_len)
{
	int row;
	int col;
	int col_len = strlen(level[0]);

	for (row = 0; row < row_len; row++) {

		for (col = 0; col < col_len; col++) {
			if (level[row][col] != CHAR_SPACE) {
				if (level[row][col] != CHAR_WALL)
					return ERR_LEFT_WALL;
				else
					break;
			}
		}
	}
	return SUCCESS;
}

static int check_column_order(char level[][MAX_COLS], int row_len)
{
	int row;
	int col;
	int col_len = strlen(level[0]);

	for (col = 0; col < col_len; col++) {

		for (row = 0; row < row_len; row++) {
			if (level[row][col] != CHAR_SPACE) {
				if (level[row][col] != CHAR_WALL)
					return ERR_TOP_WALL;
				else
					break;
			}
		}
	}
	return SUCCESS;
}

static int check_reverse_row_order(char level[][MAX_COLS], int row_len)
{
	int row;
	int col;
	int col_len = strlen(level[0]) - 1;

	for (row = 0; row < row_len; row++) {

		for (col = col_len; col >= 0; col--) {
			if (level[row][col] != CHAR_SPACE) {
				if (level[row][col] != CHAR_WALL)
					return ERR_RIGHT_WALL;
				else
					break;
			}
		}
	}
	return SUCCESS;
}

static int check_reverse_column_order(char level[][MAX_COLS], int row_len)
{
	int row;
	int col;
	int col_len = strlen(level[0]);

	for (col = 0; col < col_len; col++) {

		for (row = row_len - 1; row >= 0; row--) {
			if (level[row][col] != CHAR_SPACE) {
				if (level[row][col] != CHAR_WALL)
					return ERR_BOTTOM_WALL;
				else
					break;
			}
		}
	}
	return SUCCESS;
}

int validate_board(char level[][MAX_COLS], int row_len)
{
	int i;
	int ret;

	int (*check[])(char[][MAX_COLS], int) = {
		check_row_order,
		check_column_order,
		check_reverse_row_order,
		check_reverse_column_order,
		check_board_field
	};

	for (i = 0; i < sizeof(check)/sizeof(int *); i++) {
		ret = check[i](level, row_len);
		if (ret & ERR_BIT) {

			switch (ret) {
			case ERR_LEFT_WALL:
				printf("Map left boundary error\n");
				break;
			case ERR_TOP_WALL:
				printf("Map top boundary error\n");
				break;
			case ERR_RIGHT_WALL:
				printf("Map right boundary error\n");
				break;
			case ERR_BOTTOM_WALL:
				printf("Map bottom boundary error\n");
				break;
			case ERR_NO_PLAYER:
				printf("Map has no player entity\n");
				break;
			case ERR_NO_TARGET:
				printf("Map has no target entity\n");
				break;
			case ERR_BOX_TARGET_COUNT:
				printf("Boxes and targets are unequal\n");
				break;
			}
		}
	}

	return ret;
}
