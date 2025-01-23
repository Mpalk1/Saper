#include "gra_z_pliku.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Plansza_t read_board(FILE *file) {
    Plansza_t b;
    fscanf(file, "%d %d %d", &b.rows, &b.cols, &b.mines);

    b.board = (char **)malloc(b.rows * sizeof(char *));
    if (!b.board) {
        fprintf(stderr, "Błąd alokacji pamięci dla planszy.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < b.rows; i++) {
        b.board[i] = (char *)malloc(b.cols * sizeof(char));
        if (!b.board[i]) {
            fprintf(stderr, "Błąd alokacji pamięci dla wiersza %d.\n", i);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < b.cols; j++) {
            fscanf(file, " %c", &b.board[i][j]);
        }
    }

    return b;
}

int process_moves(FILE *file, Plansza_t *b, int *score, int *successful) {
    char action;
    int x, y;
    int correct_moves = 0;
    *score = 0;
    *successful = 0;

    while (fscanf(file, " %c %d %d", &action, &x, &y) == 3) {
        if ((action != 'r' && action != 'f') || x < 0 || x >= b->rows || y < 0 || y >= b->cols) {
            fprintf(stderr, "Nieprawidłowy ruch: %c %d %d\n", action, x, y);
            continue;
        }

        if (action == 'r') {
            if (b->board[x][y] == 'M') { // Trafienie na minę
                *successful = 0;
                break;
            } else { 
                correct_moves++;
                *score += 1;
            }
        } else if (action == 'f') {
            
        }
    }

    int revealed_fields = 0;
    for (int i = 0; i < b->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            if (b->board[i][j] != 'M') {
                revealed_fields++;
            }
        }
    }

    if (revealed_fields == (b->rows * b->cols - b->mines)) {
        *successful = 1;
    }

    return correct_moves;
}

int play_game_from_file(const char *filename, int *correct_moves, int *score, int *success) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Nie można otworzyć pliku %s\n", filename);
        return -1;
    }

    Plansza_t b = read_board(file);
    *correct_moves = process_moves(file, &b, score, success);

    for (int i = 0; i < b.rows; i++) {
        free(b.board[i]);
    }
    free(b.board);

    fclose(file);
    return 0;
}
