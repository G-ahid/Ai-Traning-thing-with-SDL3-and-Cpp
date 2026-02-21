#pragma once

#include <array>
#include <SDL3/SDL.h>

#include "lib.h"
#include "blocks.h"

struct Player {
    float x = 200;
    float y = 200;
    float dy = 0.0f;

    bool touching = false;

    const float speed = 500.0f;
    const float gravity = 2000.0f;
    const float jumpForce = -800.0f;
    const float terminalVelocity = 1200.0f;

    const unsigned int size = 20;
    const int color[3] = {255,255,255};

    std::array<int,4> split();

    bool update(double dt);
};

extern Player player;