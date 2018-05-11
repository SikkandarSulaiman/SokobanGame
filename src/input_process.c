#include <stdio.h>
#include <string.h>

#include <input_process.h>
#include <fetch_level.h>
#include <game_data.h>
#include <sokoban.h>
#include <sys_game_cmds.h>

int process_input(game_data_t *data, int *redirect_key)
{
	int ret;

	*redirect_key = GAME_LOGIC;

	ret = match_cmd(data->user_cmd, &data->sys_cmd);
	if (ret == FAILURE) {
		data->err = ERR_USER_CMD;
		*redirect_key = OUTPUT_END;
		return SUCCESS;
	}
	
	if (data->sys_cmd & S_LEVEL_CMD) {

		if (data->sys_cmd == S_QUIT) {
			*redirect_key = QUIT_GAME;
			return SUCCESS;
		}

		if (!(data->game_status & GAME_START)) {
			if (data->sys_cmd == S_START) {
				data->game_status |= GAME_START;
			} else {
				data->err = ERR_NO_GAME;
				*redirect_key = OUTPUT_END;
				return SUCCESS;
			}
		}

		*redirect_key = GET_BOARD;
		return SUCCESS;
	}

	if (!(data->game_status & LEVEL_START)) {
		data->err = ERR_NO_GAME;
		*redirect_key = OUTPUT_END;
	}

	return SUCCESS;
}

int get_index(char str_data[][CMD_LEN_MAX], int arr_len, char *target_str)
{
	int i = 0;

	for (; i < arr_len; i++)
		if (!strcasecmp(str_data[i], target_str))
			return i;

	return FAILURE;
}

int match_cmd(char *user_cmd, int *sys_cmd)
{
	int u_index;
	char user_game_cmds[][CMD_LEN_MAX] = {
		[UP] = U_UP,
		[DOWN] = U_DOWN,
		[LEFT] = U_LEFT,
		[RIGHT] = U_RIGHT,
		[START] = U_START,
		[QUIT] = U_QUIT,
		[RESET] = U_RESET,
		[NEXT] = U_NEXT
	};
	int sys_game_cmds[] = {
		[UP] = S_UP,
		[DOWN] = S_DOWN,
		[LEFT] = S_LEFT,
		[RIGHT] = S_RIGHT,
		[START] = S_START,
		[QUIT] = S_QUIT,
		[RESET] = S_RESET,
		[NEXT] = S_NEXT
	};

	u_index = get_index(user_game_cmds,
			    sizeof(user_game_cmds)/CMD_LEN_MAX, user_cmd);
	if (u_index == FAILURE)
		return FAILURE;

	*sys_cmd = sys_game_cmds[u_index];
	return SUCCESS;
}

