// Poprawiony plik gra.h
#ifndef _GRA
#define _GRA

// Funkcja sprawdzająca, czy wszystkie bezpieczne pola zostały odkryte
int all_safe_fields_revealed(char **state_board, int rows, int cols, int mines);

// Główna pętla gry
void game_loop(char **board, char **state_board, int rows, int cols, int mines, int difficulty);

// Funkcja zapisująca wynik gracza do pliku
void save_score(const char *name, int score);

// Funkcja odkrywająca sąsiednie zera
void reveal_adjacent_zeros(char **board, char **state_board, int rows, int cols, int x, int y);

#endif