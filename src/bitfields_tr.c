#include <bitfields_tr.h>
#include <game_data.h>

int chars_to_bits(char level[][MAX_COLS], char bits[][MAX_COLS], int rows, int cols)
{
	int i;
	int j;

	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			switch (level[i][j]) {
			case CHAR_PLAYER:
				bits[i][j] = BIT_PLAYER;
				break;
			case CHAR_TARGET:
				bits[i][j] = BIT_TARGET;
				break;
			case CHAR_PLACED:
				bits[i][j] = BIT_TARGET;
				bits[i][j] |= BIT_BOX;
				break;
			case CHAR_P_ON_T:
				bits[i][j] = BIT_PLAYER;
				bits[i][j] |= BIT_TARGET;
				break;
			case CHAR_BOX:
				bits[i][j] = BIT_BOX;
				break;
			case CHAR_WALL:
				bits[i][j] = BIT_WALL;
				break;
			case CHAR_SPACE:
				bits[i][j] = BIT_SPACE;
				break;
			default:
				return FAILURE;
			}

	return SUCCESS;
}

int bits_to_chars(char map[][MAX_COLS], char level[][MAX_COLS], int rows, int cols)
{
	int i;
	int j;

	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			switch (level[i][j]) {
			case BIT_PLAYER:
				map[i][j] = CHAR_PLAYER;
				break;
			case BIT_TARGET:
				map[i][j] = CHAR_TARGET;
				break;
			case BIT_TARGET | BIT_BOX:
				map[i][j] = CHAR_PLACED;
				break;
			case BIT_PLAYER | BIT_TARGET:
				map[i][j] = CHAR_P_ON_T;
				break;
			case BIT_BOX:
				map[i][j] = CHAR_BOX;
				break;
			case BIT_WALL:
				map[i][j] = CHAR_WALL;
				break;
			case BIT_SPACE:
				map[i][j] = CHAR_SPACE;
				break;
			default:
				return FAILURE;
			}

	return SUCCESS;
}
