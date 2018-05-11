#include <stdio.h>
#include <stdlib.h>

#include <io_endpoint.h>
#include <input_process.h>
#include <fetch_level.h>
#include <game_logic.h>
#include <game_data.h>

#define CLEAR 0

int main(void)
{
	int ret;
	int redirect_index;
	game_data_t data;

	int (*blocks[])(game_data_t*, int*) = {
		[INPUT_END] = get_user_cmd,
		[INPUT_PROCESS] = process_input,
		[GET_BOARD] = get_board,
		[GAME_LOGIC] = exec_cmd,
		[OUTPUT_END] = respond
	};

	redirect_index = INPUT_END;

	while (1) {

<<<<<<< HEAD
		/* printf("error %X from %d\n", data.err, redirect_index); */
		if (redirect_index == INPUT_END)
			data.err = CLEAR;
		
		blocks[redirect_index](&data, &redirect_index);
=======
		if (redirect_index == INPUT_END)
			data.err = CLEAR;

		ret = blocks[redirect_index](&data, &redirect_index);
		if (ret == FAILURE) {
			printf("Fatal Error\n");
		}
>>>>>>> sikandar

		if (redirect_index == QUIT_GAME)
			break;
		
	}

	return 0;
}
