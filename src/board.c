#include "board.h"
#include <string.h>

void board_init(Board *b) {
    memset(b->cells, 0, sizeof(b->cells));
}

int board_valid(const Board *b, Piece p) {
    for (int row = 0; row < PIECE_SIZE; row++) {
        for (int col = 0; col < PIECE_SIZE; col++) {
            if (!piece_cell(p.type, p.rotation, row, col)) continue;
            int bx = p.x + col;
            int by = p.y + row;
            if (bx < 0 || bx >= BOARD_WIDTH)  return 0;
            if (by >= BOARD_HEIGHT)             return 0;
            if (by >= 0 && b->cells[by][bx])   return 0;
        }
    }
    return 1;
}

void board_place(Board *b, Piece p) {
    for (int row = 0; row < PIECE_SIZE; row++) {
        for (int col = 0; col < PIECE_SIZE; col++) {
            if (!piece_cell(p.type, p.rotation, row, col)) continue;
            int bx = p.x + col;
            int by = p.y + row;
            if (by >= 0 && by < BOARD_HEIGHT && bx >= 0 && bx < BOARD_WIDTH)
                b->cells[by][bx] = (int)p.type + 1;
        }
    }
}

int board_clear_lines(Board *b) {
    int cleared = 0;
    for (int row = BOARD_HEIGHT - 1; row >= 0; row--) {
        int full = 1;
        for (int col = 0; col < BOARD_WIDTH; col++) {
            if (!b->cells[row][col]) { full = 0; break; }
        }
        if (!full) continue;
        for (int r = row; r > 0; r--)
            memcpy(b->cells[r], b->cells[r - 1], sizeof(b->cells[r]));
        memset(b->cells[0], 0, sizeof(b->cells[0]));
        cleared++;
        row++;  // re-check the same index after shift
    }
    return cleared;
}
