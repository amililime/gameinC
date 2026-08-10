#pragma once

#define PIECE_SIZE  4
#define PIECE_COUNT 7

typedef enum {
    PIECE_I = 0,
    PIECE_O,
    PIECE_T,
    PIECE_S,
    PIECE_Z,
    PIECE_J,
    PIECE_L,
} PieceType;

typedef struct {
    PieceType type;
    int       rotation;
    int       x, y;
} Piece;

int   piece_cell(PieceType type, int rotation, int row, int col);
Piece piece_spawn(void);
Piece piece_rotated(Piece p, int dir);
