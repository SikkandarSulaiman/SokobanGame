#ifndef _SYS_GAME_CMDS_H_
#define _SYS_GAME_CMDS_H_

#define S_DIRECTION 0x200

#define S_LEVEL_CMD 0x100

#define S_UP (S_DIRECTION | 1)
#define S_DOWN (S_DIRECTION | 2)
#define S_LEFT (S_DIRECTION | 3)
#define S_RIGHT (S_DIRECTION | 4)

#define S_START (S_LEVEL_CMD | 0)
#define S_NEXT (S_LEVEL_CMD | 1)
#define S_RESET (S_LEVEL_CMD | 2)
#define S_QUIT (S_LEVEL_CMD | 3)

enum indices {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	START,
	QUIT,
	RESET,
	NEXT
};

#endif
