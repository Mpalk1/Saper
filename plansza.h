#ifndef _PLANSZA
#define _PLANSZA

typedef struct {
    int rows;
    int cols;
    int mines;
    char **board;
} Plansza_t;


Plansza_t board_init(int rows, int cols, int mines);

char **init_state_board(Plansza_t board);

void print_state_board(char **state_board, int rows, int cols);

void print_full_board(char **board, int rows, int cols);

void print_state_board_with_labels(char **state_board, int rows, int cols);

#endif
