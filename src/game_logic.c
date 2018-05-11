#include <stdlib.h>
#include <string.h>

#include <sys_game_cmds.h>
#include <game_logic.h>
#include <game_data.h>

#define NIBBLE 4
#define NIBBLE_MASK 0xF

#define MOVED 1
#define SET_BIT(mask, bit) (mask |= bit)
#define CLEAR_BIT(mask, bit) (mask &= ~(bit))


static int move(char level[][MAX_COL], int *x, int *y, int sys_cmd)
{
	int s1_x = *x;
	int s1_y = *y;
	int s2_x = *x;
	int s2_y = *y;

	switch (sys_cmd) {
	case S_UP:
		s1_x = *x - 1;
		s2_x = *x - 2;
		break;
	case S_DOWN:
		s1_x = *x + 1;
		s2_x = *x + 2;
		break;
	case S_LEFT:
		s1_y = *y - 1;
		s2_y = *y - 2;
		break;
	case S_RIGHT:
		s1_y = *y + 1;
		s2_y = *y + 2;
		break;
	default:
		return FAILURE;
	}

	if (level[s1_x][s1_y] & BIT_WALL) {
		return FAILURE;
	} else if (level[s1_x][s1_y] & BIT_BOX) {
		if (!((level[s2_x][s2_y] & BIT_WALL) ||
			(level[s2_x][s2_y] & BIT_BOX))) {

			SET_BIT(level[s1_x][s1_y], BIT_PLAYER);
			CLEAR_BIT(level[*x][*y], BIT_PLAYER);

			SET_BIT(level[s2_x][s2_y], BIT_BOX);
			CLEAR_BIT(level[s1_x][s1_y], BIT_BOX);
		} else {
			return FAILURE;
		}
	} else {
		SET_BIT(level[s1_x][s1_y], BIT_PLAYER);
		CLEAR_BIT(level[*x][*y], BIT_PLAYER);
	}

	*x = s1_x;
	*y = s1_y;

	return MOVED;
}

static int check_placed(char level[][MAX_COL], int rows, int cols)
{
	int i;
	int j;

	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			if ((level[i][j] & BIT_BOX) &&
				!(level[i][j] & BIT_TARGET))
				return FAILURE;

	return SUCCESS;
}

int exec_cmd(game_data_t *data, int *redirect_key)
{
	*redirect_key = OUTPUT_END;

	int ret;
	int player_x = data->player_pos >> NIBBLE;
	int player_y = data->player_pos & NIBBLE_MASK;

	ret = move(data->level, &player_x, &player_y, data->sys_cmd);
	if (ret != MOVED)
		return SUCCESS;

	data->player_pos =  player_x << NIBBLE;
	data->player_pos |= player_y;

	SET_BIT(data->game_status, LEVEL_START);
	ret = check_placed(data->level, data->row_count, data->col_count);
	if (ret == SUCCESS)
		CLEAR_BIT(data->game_status, LEVEL_START);

	return SUCCESS;
}
