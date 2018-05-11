#include <ncurses.h>
#include <string.h>
#include <ncurses_io.h>
<<<<<<< HEAD
#include <game_data.h>
#include <user_game_cmds.h>
=======
#include <sokoban.h>
>>>>>>> sikandar

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

#define HEIGHT 5
#define WIDTH 30

#define R_C 3

static void init_ncurses()
{
	initscr();
	clear();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	box(stdscr, '#' , '#');
}

static void define_color_pair()
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

<<<<<<< HEAD
int print_ui(char data, int startx, int starty)
{
	char wall[][R_C] = {"###",
			    "# #",
			    "###"};

	char player[][R_C] = {" O ",
			      "/|\\",
			      "/ \\"};

	char box[][R_C] = {"---",
			   "| |",
			   "---"};

	char target[][R_C] = {"   ",
			      " X ",
			      "   "};

	char placed[][R_C] = {"---",
			      "|X|",
			      "---"};

	char p_on_t[][R_C] = {" O ",
			      "/X\\",
			      "/ \\"};

	int row;
	int col;
 	int i = 0;
	int j = 0;

	switch (data) {
	case CHAR_WALL:
		for (row = startx; row < startx + 3; row++) {
			for (col = starty; col < starty + 3; col++)
				mvprintw(row, col, "%c", wall[i][j++]);
			i++;
			j = 0;
		}
		break;

	case CHAR_PLAYER:
		for (row = startx; row < startx + 3; row++) {
			for (col = starty; col < starty + 3; col++)
				mvprintw(row, col, "%c", player[i][j++]);
			i++;
			j = 0;
		}
		break;
	case CHAR_BOX:
		for (row = startx; row < startx + 3; row++) {
			for (col = starty; col < starty + 3; col++)
				mvprintw(row, col, "%c", box[i][j++]);
			i++;
			j = 0;
		}
		break;
	case CHAR_TARGET:
		for (row = startx; row < startx + 3; row++) {
			for (col = starty; col < starty + 3; col++)
				mvprintw(row, col, "%c", target[i][j++]);
			i++;
			j = 0;
		}
		break;
	case CHAR_PLACED:
		for (row = startx; row < startx + 3; row++) {
			for (col = starty; col < starty + 3; col++)
				mvprintw(row, col, "%c", placed[i][j++]);
			i++;
			j = 0;
		}
		break;
	case CHAR_P_ON_T:
		for (row = startx; row < startx + 3; row++) {
			for (col = starty; col < starty + 3; col++)
				mvprintw(row, col, "%c", p_on_t[i][j++]);
			i++;
			j = 0;
		}
		break;

	default:
		for (row = startx; row < startx + 3; row++) {
			for (col = starty; col < starty + 3; col++)
				mvprintw(row, col, "%c", data);
		}
	}
	return 0;
}

static int print_data(char board[][MAX_COLS], int row_len)
=======
int print_ui(char ui_data[][R_C], int startx, int starty)
>>>>>>> sikandar
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
<<<<<<< HEAD
	int start_row = 1;
	int start_col = 1;
=======

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

static void print_manual()
{
	int height;
	int width;
	int start_x;
	int row;

	char option[][20] = {"RESTART GAME -> F2",
			     "NEXT_LEVEL   -> F3",
			     "RESET_LEVEL  -> F4",
			     "QUIT_GAME    -> ESC"};
	char movement_key[][30] = {"MOVE UP  -> UP_ARROW",
				   "MOVE DOWN -> DOWN_ARROW",
				   "MOVE RIGHT -> RIGHT_ARROW",
				   "MOVE LEFT -> LEFT_ARROW"};

	getmaxyx(stdscr, height, width);

	start_x = 1;
	for (row = 0; row < 4; row++)
		mvprintw(start_x++, 2, "%s\n", option[row]);

	start_x = height - 5;
	for (row = 0; row < 4; row++)
		mvprintw(start_x++, width - strlen(movement_key[row]) - 5, "%s\n", movement_key[row]);

}

int print_string(char str_data[][MAX_COLS], int  row_len)
{
	int start_row;
	int start_col;
>>>>>>> sikandar
	int height;
	int width;
	int row;
	int col;
	int col_len = strlen(str_data[0]);

	attron(A_BOLD | COLOR_PAIR(OTHER_COLOR));
	print_manual();
	getmaxyx(stdscr, height, width);

	start_row = (height / 2) - (row_len * 3 / 2);

	for (row = 0; row < row_len; row++) {
		start_col = (width - col_len * 3) / 2;

<<<<<<< HEAD
		for (col = 0; col < col_len; col++) {
			find_color(board[row][col], &color);
			attron(A_BOLD | COLOR_PAIR(color));

			/* mvprintw(start_row, start_col++, "%c", board[row][col]); */
			print_ui(board[row][col], start_row, start_col);
			start_col = start_col + 3;

			attroff(A_BOLD | COLOR_PAIR(color));
		}

=======
		for (col = 0; col < col_len; col++)
			mvprintw(start_row, start_col++, "%c", str_data[row][col]);

>>>>>>> sikandar
		printw("\n");
		start_row = start_row + 3;
		start_col = 1;

		/* start_row++; */
	}

	attron(A_BOLD | COLOR_PAIR(OTHER_COLOR));

	return 0;
}

static int print_data(char level[][MAX_COLS], int row_len)
{
	int row;
	int col;
	int col_len = strlen(level[0]);
	int color;
	int start_row = 1;
	int start_col = 1;
	int height;
	int width;
	int ret;
	int flag = 1;

<<<<<<< HEAD
	char option[][20] = {"NEXT_LEVEL  -> F3",
			     "RESET_LEVEL -> F4",
			     "QUIT_GAME   -> ESC"};
	char movement_key[][30] = {"MOVE UP    -> UP_ARROW",
				   "MOVE DOWN  -> DOWN_ARROW",
				   "MOVE RIGHT -> RIGHT_ARROW",
				   "MOVE LEFT  -> LEFT_ARROW"};

	getmaxyx(stdscr, height, width);

	start_x = 1;
	for (row = 0; row < 3; row++)
		mvprintw(start_x++, 3, "%s\n", option[row]);

	start_x = height - 8;
	for (row = 0; row < 4; row++)
		mvprintw(start_x++, (width - strlen(movement_key[row])) / 2, "%s\n", movement_key[row]);
=======
	getmaxyx(stdscr, height, width);

	start_row = (height / 2) - (row_len * 3 / 2);
>>>>>>> sikandar

	for (row = 0; row < row_len && flag == 1; row++) {
		start_col = (width - col_len * 3) / 2;
		for (col = 0; col < col_len; col++) {
			ret = create_ui(level[row][col], start_row, start_col);
			if (ret == STRING) {
				print_string(level, row_len);
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

int display_ncurses(char level[][MAX_COLS], int row_len)
{
	endwin();
	init_ncurses();
	if (has_colors() == FALSE) {
		endwin();
		printf("Terminal doesn't not support color\n");
		return 1;
	}
	define_color_pair();
<<<<<<< HEAD
	print_data(board, row_len);
	/* print_manual(); */
=======
	print_data(level, row_len);
>>>>>>> sikandar
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

<<<<<<< HEAD
=======
	print_manual();

>>>>>>> sikandar
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
<<<<<<< HEAD
	/* getch(); */
=======
>>>>>>> sikandar
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
<<<<<<< HEAD
	/* endwin(); */
=======
	endwin();
>>>>>>> sikandar

	return SUCCESS;
}
