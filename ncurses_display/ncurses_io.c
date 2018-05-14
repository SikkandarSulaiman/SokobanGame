#include <ncurses.h>
#include <string.h>
#include <ncurses_io.h>
#include <sokoban.h>

#define WALL_COLOR 1
#define PLAYER_COLOR 2
#define BOX_COLOR 3
#define TARGET_COLOR 4
#define GOAL_COLOR 5
#define OTHER_COLOR 6

#define ESC_KEY 27
#define HEIGHT 20
#define WIDTH 80
#define R_C 3
#define STRING -1

static void init_ncurses(void)
{
	initscr();
	clear();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	box(stdscr, '#', '#');
}

static void define_color_pair(void)
{
	start_color();

	init_pair(WALL_COLOR, COLOR_GREEN, COLOR_BLACK);
	init_pair(PLAYER_COLOR, COLOR_WHITE, COLOR_BLACK);
	init_pair(BOX_COLOR, COLOR_BLUE, COLOR_BLACK);
	init_pair(TARGET_COLOR, COLOR_RED, COLOR_BLACK);
	init_pair(GOAL_COLOR, COLOR_YELLOW, COLOR_BLACK);
	init_pair(OTHER_COLOR, COLOR_CYAN, COLOR_BLACK);

}

static int find_color(char element, int *color)
{
	switch (element) {
	case CHAR_WALL:
		*color = WALL_COLOR;
		break;
	case CHAR_PLAYER:
		*color = PLAYER_COLOR;
		break;
	case CHAR_BOX:
		*color = BOX_COLOR;
		break;
	case CHAR_TARGET:
		*color = TARGET_COLOR;
		break;
	case CHAR_PLACED:
		*color = GOAL_COLOR;
		break;
	default:
		*color = OTHER_COLOR;
	}
	return 0;
}

int print_ui(char ui_data[][R_C], int startx, int starty)
{
	int row = 0;
	int col = 0;
	int i = 0;
	int j = 0;

	for (row = startx; row < startx + 3; row++) {
		for (col = starty; col < starty + 3; col++)
			mvprintw(row, col, "%c", ui_data[i][j++]);
		i++;
		j = 0;
	}
	return 0;
}

int create_ui(char data, int startx, int starty)
{
	char wall_dia[][R_C] = {"+++",
				"+ +",
				"+++"};

	char player_dia[][R_C] = {" O ",
				  "/|\\",
				  "/ \\"};

	char box_dia[][R_C] = {"---",
			       "| |",
			       "---"};

	char target_dia[][R_C] = {"   ",
				  " X ",
				  "   "};

	char placed_dia[][R_C] = {"---",
				  "|X|",
				  "---"};

	char p_on_t_dia[][R_C] = {" O ",
				  "/X\\",
				  "/ \\"};

	int row = 0;
	int col = 0;
	int color;

	find_color(data, &color);
	attron(A_BOLD | COLOR_PAIR(color));

	switch (data) {
	case CHAR_WALL:
		print_ui(wall_dia, startx, starty);
		break;
	case CHAR_PLAYER:
		print_ui(player_dia, startx, starty);
		break;
	case CHAR_BOX:
		print_ui(box_dia, startx, starty);
		break;
	case CHAR_TARGET:
		print_ui(target_dia, startx, starty);
		break;
	case CHAR_PLACED:
		print_ui(placed_dia, startx, starty);
		break;
	case CHAR_P_ON_T:
		print_ui(p_on_t_dia, startx, starty);
		break;
	case CHAR_SPACE:
		for (row = startx; row < startx + 3; row++) {
			for (col = starty; col < starty + 3; col++)
				mvprintw(row, col, "%c", data);
		}
		break;
	default:
		return STRING;
	}
	attroff(A_BOLD | COLOR_PAIR(color));
	return 0;
}

static void print_manual(void)
{
	int height;
	int width;
	int start_x;
	int row;

	char menu_option[][20] = {"RESTART GAME -> F2",
			     "NEXT_LEVEL   -> F3",
			     "RESET_LEVEL  -> F4",
			     "QUIT_GAME    -> ESC"};
	char key_data[][30] = {"MOVE UP  -> UP_ARROW",
				   "MOVE DOWN -> DOWN_ARROW",
				   "MOVE RIGHT -> RIGHT_ARROW",
				   "MOVE LEFT -> LEFT_ARROW"};

	getmaxyx(stdscr, height, width);

	start_x = 1;
	for (row = 0; row < 4; row++)
		mvprintw(start_x++, 2, "%s\n", menu_option[row]);

	start_x = height - 5;
	for (row = 0; row < 4; row++)
		mvprintw(start_x++, width - strlen(key_data[row]) - 5, "%s\n",
			key_data[row]);

}

int print_string(char str_data[][MAX_COL], int  row_len)
{
	int start_row;
	int start_col;
	int height;
	int width;
	int row;
	int col;
	int col_len = strlen(str_data[0]);

	attron(A_BOLD | COLOR_PAIR(OTHER_COLOR));
	print_manual();
	getmaxyx(stdscr, height, width);
	start_row = (height / 2) - (row_len / 2);

	for (row = 0; row < row_len; row++) {
		start_col = (width - col_len) / 2;

		for (col = 0; col < col_len; col++)
			mvprintw(start_row, start_col++, "%c",
				str_data[row][col]);

		printw("\n");
		start_row++;
	}

	attron(A_BOLD | COLOR_PAIR(OTHER_COLOR));

	return 0;
}

static int print_data(char board[][MAX_COL], int row_len)
{
	int row;
	int col;
	int col_len = strlen(board[0]);
	int color;
	int start_row = 1;
	int start_col = 1;
	int height;
	int width;
	int ret;
	int flag = 1;

	getmaxyx(stdscr, height, width);

	start_row = (height / 2) - (row_len * 3 / 2);

	for (row = 0; row < row_len && flag == 1; row++) {
		start_col = (width - col_len * 3) / 2;
		for (col = 0; col < col_len; col++) {
			ret = create_ui(board[row][col], start_row, start_col);
			if (ret == STRING) {
				print_string(board, row_len);
				flag = 0;
				break;
			}
			start_col = start_col + 3;
		}
		printw("\n");
		start_row = start_row + 3;
		start_col = 1;
	}

	return 0;
}

int display_ncurses(char board[][MAX_COL], int row_len)
{
	init_ncurses();
	if (has_colors() == FALSE) {
		endwin();
		printf("Terminal doesn't not support color\n");
		return 1;
	}
	define_color_pair();
	print_data(board, row_len);
	refresh();

	return SUCCESS;
}

int print_user_msg(char *user_msg)
{
	WINDOW *game_win;
	int startx;
	int starty;
	int height;
	int width;

	print_manual();

	getmaxyx(stdscr, height, width);

	starty = (height - HEIGHT) / 2;
	startx = (width - WIDTH) / 2;

	game_win = newwin(HEIGHT, WIDTH, starty, startx);
	box(game_win, '+', '+');
	curs_set(FALSE);

	getmaxyx(game_win, height, width);

	startx = height / 2;
	starty = (width - strlen(user_msg)) / 2;

	mvwprintw(game_win, startx, starty, "%s\n", user_msg);
	wrefresh(game_win);
	delwin(game_win);

	return 0;
}

int get_input_ncurses(char *str_input)
{
	int user_input;

	user_input = getch();
	switch (user_input) {
	case KEY_F(2):
		strcpy(str_input, U_START);
		break;
	case KEY_F(3):
		strcpy(str_input, U_NEXT);
		break;
	case KEY_F(4):
		strcpy(str_input, U_RESET);
		break;
	case ESC_KEY:
		strcpy(str_input, U_QUIT);
		break;
	case KEY_UP:
		strcpy(str_input, U_UP);
		break;
	case KEY_DOWN:
		strcpy(str_input, U_DOWN);
		break;
	case KEY_RIGHT:
		strcpy(str_input, U_RIGHT);
		break;
	case KEY_LEFT:
		strcpy(str_input, U_LEFT);
		break;
	default:
		sprintf(str_input, "%d", user_input);
	}
	endwin();

	return SUCCESS;
}
