#include <SDL3/SDL.h>
#include <iostream>
#include <chrono>

#include "src/loop.cpp"
#include "src/config.h"

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "SDL Init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        game.title,
        game.width,
        game.height,
        0
    );

    if (!window) {
        std::cout << "Window creation failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // NULL = default renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer) {
        std::cout << "Renderer creation failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;

    while (!game.over) {
        double dt = 0.0;

        std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();
        while (!game.over) {
            // Measure time at start of frame
            std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
            dt = std::chrono::duration<double>(now - last).count();
            last = now;

            // Handle events
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    game.over = true;
                }
            }

            loop(dt, renderer, &game);
        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}