#include "game.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

static const int line_scores[5] = {0, 100, 300, 500, 800};

static void lock_and_advance(Game *g) {
    board_place(&g->board, g->current);

    int cleared = board_clear_lines(&g->board);
    if (cleared > 0 && cleared <= 4)
        g->score += line_scores[cleared] * g->level;
    g->lines += cleared;
    g->level  = g->lines / 10 + 1;

    double interval = 1.0 - (g->level - 1) * 0.08;
    g->fall_interval = interval < 0.05 ? 0.05 : interval;

    g->current = g->next;
    g->next    = piece_spawn();

    if (!board_valid(&g->board, g->current))
        g->state = STATE_GAME_OVER;
}

void game_init(Game *g) {
    srand((unsigned int)time(NULL));
    board_init(&g->board);
    g->current       = piece_spawn();
    g->next          = piece_spawn();
    g->state         = STATE_PLAYING;
    g->score         = 0;
    g->level         = 1;
    g->lines         = 0;
    g->fall_timer    = 0.0;
    g->fall_interval = 1.0;
}

void game_update(Game *g, double dt) {
    if (g->state != STATE_PLAYING) return;

    g->fall_timer += dt;
    if (g->fall_timer < g->fall_interval) return;
    g->fall_timer = 0.0;

    Piece dropped = g->current;
    dropped.y++;
    if (board_valid(&g->board, dropped))
        g->current = dropped;
    else
        lock_and_advance(g);
}

void game_handle_input(Game *g) {
    if (g->state == STATE_GAME_OVER) {
        if (IsKeyPressed(KEY_ENTER)) game_init(g);
        return;
    }

    if (IsKeyPressed(KEY_P)) {
        g->state = (g->state == STATE_PLAYING) ? STATE_PAUSED : STATE_PLAYING;
        return;
    }

    if (g->state != STATE_PLAYING) return;

    if (IsKeyPressed(KEY_LEFT)) {
        Piece moved = g->current;
        moved.x--;
        if (board_valid(&g->board, moved)) g->current = moved;
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        Piece moved = g->current;
        moved.x++;
        if (board_valid(&g->board, moved)) g->current = moved;
    }
    if (IsKeyPressed(KEY_UP)) {
        Piece rotated = piece_rotated(g->current, 1);
        if (board_valid(&g->board, rotated)) g->current = rotated;
    }
    if (IsKeyPressed(KEY_DOWN)) {
        Piece moved = g->current;
        moved.y++;
        if (board_valid(&g->board, moved)) {
            g->current    = moved;
            g->fall_timer = 0.0;
        }
    }
    if (IsKeyPressed(KEY_SPACE)) {
        // Hard drop
        Piece dropped = g->current;
        while (1) {
            Piece next = dropped;
            next.y++;
            if (!board_valid(&g->board, next)) break;
            dropped = next;
        }
        g->current = dropped;
        lock_and_advance(g);
        g->fall_timer = 0.0;
    }
}
