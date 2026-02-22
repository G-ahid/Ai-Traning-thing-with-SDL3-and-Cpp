#include "game.h"

Player player;

void loop(float dt, SDL_Renderer* r, Game* game) {

    // -------- UPDATE FIRST --------
    const bool* keys = SDL_GetKeyboardState(NULL);
    if (player.update(dt, keys[SDL_SCANCODE_A], keys[SDL_SCANCODE_D], keys[SDL_SCANCODE_SPACE])) {
        game->over = true;
    }
    

    // -------- CAMERA --------
    static float cameraX = 0.0f;
    static float cameraY = 0.0f;

    float targetX = player.x - 400; // half screen width
    float targetY = player.y - 300; // half screen height

    if (targetX < 0) targetX = 0;
    if (targetY < 0) targetY = 0;

    // Smooth follow
    cameraX += (targetX - cameraX) * 0.1f;
    cameraY += (targetY - cameraY) * 0.1f;

    // -------- RENDER --------
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);

    // --- Draw blocks ---
    SDL_SetRenderDrawColor(r, 0, 255, 0, 255);

    for (int i = 0; i < blocks.size(); i++) {

        SDL_FRect blockRect = {
            blocks[i][0] - cameraX,
            blocks[i][1] - cameraY,
            (float)blocks[i][2],
            (float)blocks[i][3]
        };

        SDL_RenderFillRect(r, &blockRect);
    }

    // --- Draw player ---
    SDL_SetRenderDrawColor(r,
        player.color[0],
        player.color[1],
        player.color[2],
        255
    );

    SDL_FRect playerRect = {
        player.x - cameraX,
        player.y - cameraY,
        (float)player.size,
        (float)player.size
    };

    SDL_RenderFillRect(r, &playerRect);

    SDL_RenderPresent(r);
}