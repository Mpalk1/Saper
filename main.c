#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "plansza.h"
#include "gra.h"
#include "gra_z_pliku.h"
#include <bits/getopt_core.h>

int main(int argc, char *argv[]) {
    int opt;
    char *filename = NULL;

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-f filename]\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    if (filename) {
        int correct_moves, score, success;
        if (play_game_from_file(filename, &correct_moves, &score, &success) == 0) {
            printf("Poprawne ruchy: %d\n", correct_moves);
            printf("Punkty: %d\n", score);
            printf("Wynik: %s\n", success ? "Wygrana" : "Przegrana");
        } else {
            return EXIT_FAILURE;
        }
    } else {
        int rows, cols, mines;
        char choice;

        printf("Wybierz poziom trudnosci:\n");
        printf("1 - łatwy (9x9, 10 min)\n");
        printf("2 - średni (16x16, 40 min)\n");
        printf("3 - trudny (16x30, 99 min)\n");
        printf("4 - własna plansza\n");

        if (scanf(" %c", &choice) != 1) {
            fprintf(stderr, "Niepoprawny wybór.\n");
            return EXIT_FAILURE;
        }

        switch (choice) {
            case '1':
                rows = 9;
                cols = 9;
                mines = 10;
                break;
            case '2':
                rows = 16;
                cols = 16;
                mines = 40;
                break;
            case '3':
                rows = 16;
                cols = 30;
                mines = 99;
                break;
            case '4':
                printf("Podaj liczbę wierszy: ");
                if (scanf("%d", &rows) != 1 || rows <= 0) {
                    fprintf(stderr, "Niepoprawna liczba wierszy.\n");
                    return EXIT_FAILURE;
                }

                printf("Podaj liczbę kolumn: ");
                if (scanf("%d", &cols) != 1 || cols <= 0) {
                    fprintf(stderr, "Niepoprawna liczba kolumn.\n");
                    return EXIT_FAILURE;
                }

                printf("Podaj liczbę min: ");
                if (scanf("%d", &mines) != 1 || mines <= 0 || mines >= rows * cols) {
                    fprintf(stderr, "Niepoprawna liczba min.\n");
                    return EXIT_FAILURE;
                }
                break;
            default:
                fprintf(stderr, "Niepoprawny wybór.\n");
                return EXIT_FAILURE;
        }

        Plansza_t board = board_init(rows, cols, mines);
        char **state_board = init_state_board(board);
        if (!state_board) {
            fprintf(stderr, "Błąd inicjalizacji tablicy stanu.\n");
            return EXIT_FAILURE;
        }

        game_loop(board.board, state_board, rows, cols, mines, choice - '0');

        for (int i = 0; i < rows; ++i) {
            free(board.board[i]);
            free(state_board[i]);
        }
        free(board.board);
        free(state_board);
    }

    return EXIT_SUCCESS;
}
