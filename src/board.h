#pragma once

#include "piece.h"

#define BOARD_WIDTH  10
#define BOARD_HEIGHT 20

typedef struct {
    int cells[BOARD_HEIGHT][BOARD_WIDTH];  // 0 = empty, 1-7 = piece color index
} Board;

void board_init(Board *b);
int  board_valid(const Board *b, Piece p);
void board_place(Board *b, Piece p);
int  board_clear_lines(Board *b);
