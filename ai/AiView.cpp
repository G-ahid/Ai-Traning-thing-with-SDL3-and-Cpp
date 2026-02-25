#include <SDL3/SDL.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>

#include <iostream>
#include "../game/src/player.hpp"
#include "../game/src/config.hpp"
#include "../game/src/blocks.hpp"
#include <string>

int main() {
    // Making a vector of lines
    std::vector<std::string> lines;
    // Getting the filename
    std::string filename;
    std::cout << "Result filename (empty -> result.aig) : ";
    std::getline(std::cin, filename);
    if (filename.empty()) {
        filename = "result.aig";
    }
    // Loading the file
    std::ifstream data(filename);
    if (!data) {
        std::cout << "Failed to open File :(\n";
        return 1;
    }
    // Temporary Loading all lines
    std::string line;
    while (std::getline(data, line)) {
        lines.push_back(line);
    }
    data.close();
    
    // Loading either all lines or just one
    std::cout << "Found " << lines.size() << " lines.\n";
    std::cout << "Enter index (1 - " << lines.size() << ") or * for all (empty -> *): ";

    std::string lineChoice;
    std::getline(std::cin, lineChoice);
    if (lineChoice.empty())
        lineChoice = "*";
    // If not all lines
    if (lineChoice != "*") {
        int index = std::stoi(lineChoice) - 1;
        // If outof bounds
        if (index < 0 || (unsigned int)index >= lines.size()) {
            std::cout << "Invalid index\n";
            return 1;
        }
        // Make lines just a Vector of one instance
        lines = {lines[index]};
    }
    // Making children
    std::vector<std::vector<int>> children;
    // Formatting lines into data
    for (const std::string& l : lines) {
        size_t start = l.find('{');
        size_t end   = l.find('}');
        // invalid line -> skip
        if (start == std::string::npos || end == std::string::npos)
            continue;

        std::string StringMoves = l.substr(start + 1, end - start - 1);
        std::stringstream ss(StringMoves);
        std::string temp;
        std::vector<int> moves;
        // Going over each number -> int
        while (std::getline(ss, temp, ',')) {
            moves.push_back(std::stoi(temp));
        }
        children.push_back(moves);
    }

    // Making a vector of {bool,bool,bool} -> {right,left,jump}
    std::vector<std::vector<std::array<bool, 3>>> moves(children.size());

    for (size_t i = 0; i < children.size(); i++) {
        for (size_t m = 0; m < children[i].size(); m++) {
            int value = children[i][m];
            if (value == 1) {
                moves[i].push_back({true,false,false});
            } else if (value == 2) {
                moves[i].push_back({false,true,false});
            } else if (value == 3) {
                moves[i].push_back({false,false,true});
            }
        }
    }
    // Making each a Player for each Vector of moves
    std::vector<Player> players(moves.size());
    std::cout << "Size of Players : " << players.size() << "\n";
    
    // Setting up the 2d engine
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "SDL failed :(\n" << SDL_GetError() << "\n";
        return 1;
    }
    // Making a new window
    SDL_Window* window = SDL_CreateWindow(
        game.title,
        game.width ,game.height,
        0
    );
    if(!window) {
        std::cout << "Window creation failed :(\n" << SDL_GetError() << "\n";
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer) {
        std::cout << "Render creation failed :(\n" << SDL_GetError() << "\n";
        return 1;
    } 

    // Actual Graphicing
    SDL_Event event;
    bool running = true;
    double dt = 0.0;
    std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();
    for (size_t move = 0; move < moves[0].size(); move++) {
        std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<double>(now - last).count();
        last = now;

        // Handle events(aka. User exiting)
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }  
        if (!running)
            break;
        
        // Now we're actually doing the shit
        for (size_t i = 0; i < players.size(); i++) {
            players[i].update(dt, moves[i][move][0], moves[i][move][1], moves[i][move][2]);
        }

        // -------- CAMERA --------
        static float cameraX = 0.0f;
        static float cameraY = 0.0f;
        const  int cameraSpeed = 850;
        // Get User Input
        const bool* keys = SDL_GetKeyboardState(NULL);
        // Move The Camera
        if (keys[SDL_SCANCODE_A]) {
            cameraX -= cameraSpeed * dt;
        }
        if (keys[SDL_SCANCODE_D]) {
            cameraX += cameraSpeed * dt;
        }
        if (keys[SDL_SCANCODE_S]) {
            cameraY += cameraSpeed * dt;
        }
        if (keys[SDL_SCANCODE_W]) {
            cameraY -= cameraSpeed * dt;
        }

        // Draw a black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the map
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        for (size_t i = 0; i < blocks.size(); i++) {

            SDL_FRect blockRect = {
                blocks[i][0] - cameraX,
                blocks[i][1] - cameraY,
                (float)blocks[i][2],
                (float)blocks[i][3]
            };

            SDL_RenderFillRect(renderer, &blockRect);
        }

        // Draw Players !!!!
        for (size_t i = 0; i < players.size(); i++) {
            // Set the Color
            SDL_SetRenderDrawColor(renderer,
                players[i].color[0],
                players[i].color[1],
                players[i].color[2],
                255
            );
            // Make a Rect
            SDL_FRect playerRect = {
                players[i].x- cameraX,
                players[i].y - cameraY,
                (float)players[i].size,
                (float)players[i].size
            };
            // Draw the Rect
            SDL_RenderFillRect(renderer, &playerRect);

        }

        SDL_RenderPresent(renderer);
    }

}