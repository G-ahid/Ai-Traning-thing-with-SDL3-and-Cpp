#pragma once

struct Game {
    static const unsigned int width  = 800;
    static const unsigned int height = 600;

    const char title[20] = "Epic AI Game";

    bool over = false;
};

// Declare global instance (do NOT define it here)
extern Game game;