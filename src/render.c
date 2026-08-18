#include "render.h"
#include "raylib.h"

#define CELL_SIZE      30
#define BOARD_OFFSET_X 50
#define BOARD_OFFSET_Y 50
#define PANEL_X        (BOARD_OFFSET_X + BOARD_WIDTH * CELL_SIZE + 20)

static const Color piece_colors[PIECE_COUNT] = {
    SKYBLUE,                        // I
    YELLOW,                         // O
    {128, 0, 128, 255},             // T  purple
    GREEN,                          // S
    RED,                            // Z
    BLUE,                           // J
    ORANGE,                         // L
};

static void draw_cell(int bx, int by, Color color) {
    DrawRectangle(
        BOARD_OFFSET_X + bx * CELL_SIZE,
        BOARD_OFFSET_Y + by * CELL_SIZE,
        CELL_SIZE - 1, CELL_SIZE - 1,
        color
    );
}

static void draw_piece(Piece p, int ox, int oy) {
    Color color = piece_colors[p.type];
    for (int row = 0; row < PIECE_SIZE; row++) {
        for (int col = 0; col < PIECE_SIZE; col++) {
            if (!piece_cell(p.type, p.rotation, row, col)) continue;
            int px = ox + col * CELL_SIZE;
            int py = oy + row * CELL_SIZE;
            DrawRectangle(px, py, CELL_SIZE - 1, CELL_SIZE - 1, color);
        }
    }
}

static void draw_board(const Board *b) {
    // Grid lines
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            DrawRectangleLines(
                BOARD_OFFSET_X + col * CELL_SIZE,
                BOARD_OFFSET_Y + row * CELL_SIZE,
                CELL_SIZE, CELL_SIZE,
                (Color){30, 30, 30, 255}
            );
        }
    }
    // Placed cells
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            int cell = b->cells[row][col];
            if (cell) draw_cell(col, row, piece_colors[cell - 1]);
        }
    }
}

static Piece ghost_piece(const Game *g) {
    Piece ghost = g->current;
    while (1) {
        Piece dropped = ghost;
        dropped.y++;
        if (!board_valid(&g->board, dropped)) break;
        ghost = dropped;
    }
    return ghost;
}

static void draw_ghost(const Game *g) {
    Piece ghost = ghost_piece(g);
    if (ghost.y == g->current.y) return;
    for (int row = 0; row < PIECE_SIZE; row++) {
        for (int col = 0; col < PIECE_SIZE; col++) {
            if (!piece_cell(ghost.type, ghost.rotation, row, col)) continue;
            int bx = ghost.x + col;
            int by = ghost.y + row;
            if (by >= 0 && by < BOARD_HEIGHT) {
                Color c = piece_colors[ghost.type];
                DrawRectangleLines(
                    BOARD_OFFSET_X + bx * CELL_SIZE,
                    BOARD_OFFSET_Y + by * CELL_SIZE,
                    CELL_SIZE - 1, CELL_SIZE - 1,
                    (Color){c.r, c.g, c.b, 100}
                );
            }
        }
    }
}

static void draw_current(const Game *g) {
    Piece p = g->current;
    for (int row = 0; row < PIECE_SIZE; row++) {
        for (int col = 0; col < PIECE_SIZE; col++) {
            if (!piece_cell(p.type, p.rotation, row, col)) continue;
            int bx = p.x + col;
            int by = p.y + row;
            if (by >= 0 && by < BOARD_HEIGHT)
                draw_cell(bx, by, piece_colors[p.type]);
        }
    }
}

static void draw_panel(const Game *g) {
    DrawText("SCORE",  PANEL_X, 50,  18, GRAY);
    DrawText(TextFormat("%d", g->score), PANEL_X, 72,  22, WHITE);
    DrawText("LINES",  PANEL_X, 115, 18, GRAY);
    DrawText(TextFormat("%d", g->lines), PANEL_X, 137, 22, WHITE);
    DrawText("LEVEL",  PANEL_X, 180, 18, GRAY);
    DrawText(TextFormat("%d", g->level), PANEL_X, 202, 22, WHITE);
    DrawText("NEXT",   PANEL_X, 265, 18, GRAY);
    draw_piece(g->next, PANEL_X, 290);
}

void render_frame(const Game *g) {
    // Board border
    DrawRectangleLines(
        BOARD_OFFSET_X - 1, BOARD_OFFSET_Y - 1,
        BOARD_WIDTH * CELL_SIZE + 2, BOARD_HEIGHT * CELL_SIZE + 2,
        WHITE
    );

    draw_board(&g->board);
    draw_ghost(g);
    draw_current(g);
    draw_panel(g);

    if (g->state == STATE_PAUSED) {
        DrawText("PAUSED", BOARD_OFFSET_X + 60, BOARD_OFFSET_Y + 280, 30, WHITE);
        DrawText("P to resume", BOARD_OFFSET_X + 45, BOARD_OFFSET_Y + 320, 18, GRAY);
    }

    if (g->state == STATE_GAME_OVER) {
        DrawRectangle(BOARD_OFFSET_X, BOARD_OFFSET_Y, BOARD_WIDTH * CELL_SIZE, BOARD_HEIGHT * CELL_SIZE,
                      (Color){0, 0, 0, 160});
        DrawText("GAME OVER", BOARD_OFFSET_X + 30, BOARD_OFFSET_Y + 265, 28, RED);
        DrawText("ENTER to restart", BOARD_OFFSET_X + 20, BOARD_OFFSET_Y + 305, 18, GRAY);
    }
}
