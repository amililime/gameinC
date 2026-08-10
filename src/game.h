#pragma once

#include "board.h"
#include "piece.h"

typedef enum {
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAME_OVER,
} GameState;

typedef struct {
    Board     board;
    Piece     current;
    Piece     next;
    GameState state;
    int       score;
    int       level;
    int       lines;
    double    fall_timer;
    double    fall_interval;
} Game;

void game_init(Game *g);
void game_update(Game *g, double dt);
void game_handle_input(Game *g);
