#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plansza.h"

int all_safe_fields_revealed(char **state_board, int rows, int cols, int mines) {
    int revealed_fields = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (state_board[i][j] != 'X' && state_board[i][j] != 'F') {
                revealed_fields++;
            }
        }
    }
    return revealed_fields;
}

void save_score(const char *name, int score) {
    typedef struct {
        char name[50];
        int score;
    } ScoreEntry;

    FILE *file = fopen("scores.txt", "r+");
    if (!file) {
        printf("Nie można otworzyć pliku scores.txt. Tworzę nowy.\n");
        file = fopen("scores.txt", "w+");
        if (!file) {
            printf("Nie udało się utworzyć pliku scores.txt.\n");
            return;
        }
    }

    ScoreEntry entries[100];
    int count = 0;

    while (fscanf(file, "%49s %d", entries[count].name, &entries[count].score) == 2) {
        count++;
    }

    strcpy(entries[count].name, name);
    entries[count].score = score;
    count++;

    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (entries[j].score > entries[i].score) {
                ScoreEntry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
    }

    rewind(file);

    for (int i = 0; i < count; ++i) {
        fprintf(file, "%s %d\n", entries[i].name, entries[i].score);
    }

    fclose(file);
}

void reveal_adjacent_zeros(char **board, char **state_board, int rows, int cols, int x, int y) {
    if (x < 0 || x >= rows || y < 0 || y >= cols || state_board[x][y] != 'X') {
        return;
    }

    state_board[x][y] = board[x][y];

    if (board[x][y] == '0') {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx != 0 || dy != 0) {
                    reveal_adjacent_zeros(board, state_board, rows, cols, x + dx, y + dy);
                }
            }
        }
    }
}

void game_loop(char **board, char **state_board, int rows, int cols, int mines, int difficulty) {
    int score = 0;
    char name[50];
    int flags_placed = 0;
    int total_safe_fields = rows * cols - mines;

    while (1) {
        print_state_board_with_labels(state_board, rows, cols);

        printf("Podaj ruch (f x y lub r x y): ");
        char action;
        int x, y;
        if (scanf(" %c %d %d", &action, &x, &y) != 3) {
            printf("Błędny format ruchu.\n");
            continue;
        }

        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            printf("Współrzędne poza zakresem.\n");
            continue;
        }

        if (action == 'f') {
            if (state_board[x][y] == 'X') {
                state_board[x][y] = 'F';
                flags_placed++;
            } else {
                printf("Pole już oznaczone lub odkryte.\n");
            }
        } else if (action == 'r') {
            if (state_board[x][y] != 'X') {
                printf("Pole już odkryte lub oznaczone flagą.\n");
                continue;
            }
            if (board[x][y] == 'M') {
                printf("Przegrana!\n");
                print_full_board(board, rows, cols);
                printf("Podaj swoje imię: ");
                scanf("%s", name);
                save_score(name, score);
                break;
            } else {
                reveal_adjacent_zeros(board, state_board, rows, cols, x, y);
                score += difficulty;
            }
        } else {
            printf("Nieprawidłowy ruch.\n");
        }

        int revealed_fields = all_safe_fields_revealed(state_board, rows, cols, mines);
        if (flags_placed == mines && revealed_fields == total_safe_fields) {
            printf("Wygrana!\n");
            printf("Podaj swoje imię: ");
            scanf("%s", name);
            save_score(name, score);
            break;
        } else {
            printf("Odkryto %d pól z %d.\n", revealed_fields, total_safe_fields);
        }
    }
}
