#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

#include <fetch_level.h>
#include <sys_game_cmds.h>
#include <validate_level.h>
#include <game_data.h>
#include <bitfields_tr.h>


#define END_OF_FILE -1
#define QUIT_LEVEL -2

static int get_level(FILE *level_file_fd, char level[][MAX_COL], int *row_len)
{
	char str_buf[LINE_MAX];
	char *retp;
	int row_count = 0;

	while (1) {
		retp = fgets(str_buf, LINE_MAX, level_file_fd);
		if (retp == NULL) {
			if (ferror(level_file_fd))
				error(1, errno, "error getting data from file");
			else
				return END_OF_FILE;
		}

		if (str_buf[0] == ';')
			break;
		str_buf[strcspn(str_buf, "\n")] = '\0';

		if (strlen(str_buf) != 0) {
			strcpy(level[row_count], str_buf);
			row_count++;
		}
	}
	*row_len = row_count;

	return SUCCESS;

}

static int find_max_column(char level[][MAX_COL], int row_len)
{
	int row;
	int col_len;
	int max_col = 0;

	for (row = 0; row < row_len; row++) {
		col_len = strlen(level[row]);

		if (col_len > max_col)
			max_col = col_len;
	}
	return max_col;
}

static void append_space_to_board(char level[][MAX_COL], int row_len)
{
	int row;
	int col;
	int max_col;
	int col_len;

	max_col = find_max_column(level, row_len);

	for (row = 0; row < row_len; row++) {

		col_len = strlen(level[row]);

		for (col = col_len; col < max_col; col++)
			level[row][col] = CHAR_SPACE;

		level[row][col] = '\0';
	}
}

static int set_level(FILE *level_file_fd, game_data_t *data)
{
	int ret;

	if (data->sys_cmd == S_START) {
		ret = fseek(level_file_fd, 0, SEEK_SET);
		if (ret == FAILURE)
			error(1, errno, "Error setting fseek start");
		data->current_level = 0;
	}

	if (data->sys_cmd == S_NEXT) {
		ret = fseek(level_file_fd, data->next_level, SEEK_SET);
		if (ret == FAILURE)
			error(1, errno, "Error setting fseek next level");
		data->current_level = data->next_level;
	}

	if (data->sys_cmd == S_RESET) {
		ret = fseek(level_file_fd, data->current_level, SEEK_SET);
		if (ret == FAILURE)
			error(1, errno, "Error setting fseek reset");
	}
	return 0;

}

int get_player_pos(char level[][MAX_COL], int rows, int cols)
{
	int i;
	int j;
	int pos;

	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++) {
			if (level[i][j] & BIT_PLAYER) {
				pos = (i << 4);
				pos |= j;
				return pos;
			}
		}

	return FAILURE;
}

int get_board(game_data_t *data, int *redirect_key)
{
	char char_map[MAX_ROW][MAX_COL];
	FILE *level_file_fd;
	int row_count;
	int ret;

	*redirect_key = GAME_LOGIC;

	level_file_fd = fopen(LEVEL_FILE, "r");
	if (level_file_fd == NULL) {
		*redirect_key = OUTPUT_END;
		data->err = ERR_OPEN_LEVEL_FILE;
		return FAILURE;
	}

	ret = set_level(level_file_fd, data);

	ret = get_level(level_file_fd, char_map, &row_count);

	data->next_level = ftell(level_file_fd);
	if (data->next_level == FAILURE)
		error(1, errno, "Error getting next level");

	if (ret == END_OF_FILE) {
		printf("END OF GAME\n");
		*redirect_key = OUTPUT_END;
		data->err = ERR_GAME_FINISHED;
		return FAILURE;
	}
	data->row_count = row_count;
	append_space_to_board(char_map, data->row_count);

	ret = validate_board(char_map, data->row_count);
	if (ret != SUCCESS) {
		*redirect_key = OUTPUT_END;
		data->err = ret;
		return FAILURE;
	}

	data->col_count = strlen(char_map[0]);
	chars_to_bits(char_map, data->level, data->row_count, data->col_count);
	data->player_pos = get_player_pos(data->level, data->row_count,
		data->col_count);

	ret = fclose(level_file_fd);
	if (ret == FAILURE) {
		*redirect_key = OUTPUT_END;
		data->err = ERR_CLOSE_LEVEL_FILE;
		return FAILURE;
	}

	data->game_status |= LEVEL_START;
	return SUCCESS;
}
