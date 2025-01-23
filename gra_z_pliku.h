#ifndef READ_GAME_FILE_H
#define READ_GAME_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include "plansza.h"


Plansza_t read_board(FILE *file);


int process_moves(FILE *file, Plansza_t *b, int *score, int *successful);


int play_game_from_file(const char *filename, int *correct_moves, int *score, int *success);

#endif