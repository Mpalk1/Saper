#ifndef _PLANSZA
#define _PLANSZA

typedef struct {
    int rows;
    int cols;
    int mines;
    char **board;
} Plansza_t;

// Funkcja inicjalizująca planszę z minami
Plansza_t board_init(int rows, int cols, int mines);

// Funkcja inicjalizująca tablicę stanu gry
char **init_state_board(Plansza_t board);

// Funkcja wyświetlająca aktualny stan tablicy
void print_state_board(char **state_board, int rows, int cols);

// Funkcja wyświetlająca całą planszę z minami
void print_full_board(char **board, int rows, int cols);

void print_state_board_with_labels(char **state_board, int rows, int cols);
#endif
