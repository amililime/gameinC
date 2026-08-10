#include "raylib.h"
#include "game.h"
#include "render.h"

#define WINDOW_WIDTH  550
#define WINDOW_HEIGHT 700
#define TARGET_FPS    60

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
    SetTargetFPS(TARGET_FPS);

    Game game;
    game_init(&game);

    while (!WindowShouldClose()) {
        game_handle_input(&game);
        game_update(&game, GetFrameTime());

        BeginDrawing();
            ClearBackground((Color){10, 10, 10, 255});
            render_frame(&game);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
