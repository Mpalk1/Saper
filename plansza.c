#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "plansza.h"

int directions[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1},         {0, 1},
    {1, -1},  {1, 0},  {1, 1}
};

Plansza_t board_init(int rows, int cols, int mines) {
    Plansza_t board;
    board.rows = rows;
    board.cols = cols;
    board.mines = mines;

    board.board = (char**)malloc(rows * sizeof(char*));
    if (!board.board) {
        fprintf(stderr, "Błąd alokacji pamięci dla planszy.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; ++i) {
        board.board[i] = (char*)malloc(cols * sizeof(char));
        if (!board.board[i]) {
            fprintf(stderr, "Błąd alokacji pamięci dla wiersza %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            board.board[i][j] = '.';
        }
    }

    srand(time(NULL));
    int placed_mines = 0;
    while (placed_mines < mines) {
        int row = rand() % rows;
        int col = rand() % cols;
        if (board.board[row][col] != 'M') {
            board.board[row][col] = 'M';
            placed_mines++;
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board.board[i][j] != 'M') {
                int count = 0;
                for (int k = 0; k < 8; ++k) {
                    int newRow = i + directions[k][0];
                    int newCol = j + directions[k][1];
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                        if (board.board[newRow][newCol] == 'M') {
                            count++;
                        }
                    }
                }
                board.board[i][j] = count + '0';
            }
        }
    }

    return board;
}

char** init_state_board(Plansza_t board) {
    int rows = board.rows;
    int cols = board.cols;

    char** state_board = (char**)malloc(rows * sizeof(char*));
    if (!state_board) {
        fprintf(stderr, "Błąd alokacji pamięci dla tablicy stanu.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; ++i) {
        state_board[i] = (char*)malloc(cols * sizeof(char));
        if (!state_board[i]) {
            fprintf(stderr, "Błąd alokacji pamięci dla wiersza stanu %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            state_board[i][j] = 'X';
        }
    }

    return state_board;
}

void print_state_board(char **state_board, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%c ", state_board[i][j]);
        }
        printf("\n");
    }
}

void print_full_board(char **board, int rows, int cols) {
    printf("Cała plansza:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}
void print_state_board_with_labels(char **state_board, int rows, int cols) {
    printf("   ");
    for (int j = 0; j < cols; ++j) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < rows; ++i) {
        printf("%2d ", i);
        for (int j = 0; j < cols; ++j) {
            printf("%c  ", state_board[i][j]);
        }
        printf("\n");
    }
}