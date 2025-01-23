#ifndef _GRA
#define _GRA


int all_safe_fields_revealed(char **state_board, int rows, int cols, int mines);


void game_loop(char **board, char **state_board, int rows, int cols, int mines, int difficulty);

void save_score(const char *name, int score);


void reveal_adjacent_zeros(char **board, char **state_board, int rows, int cols, int x, int y);

#endif