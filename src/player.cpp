#include "player.h"

std::array<int,4> Player::split(){
    return {(int)x,(int)y,(int)size,(int)size};
}

bool Player::update(double dt) {

    if (dt > 0.05) dt = 0.05;

    const bool* keys = SDL_GetKeyboardState(NULL);

    float oldX = x;

    if (keys[SDL_SCANCODE_A])
        x -= speed * dt;

    if (keys[SDL_SCANCODE_D])
        x += speed * dt;

    for (auto &block : blocks) {
        if (collision(split(), block)) {
            x = oldX;
            break;
        }
    }

    if (keys[SDL_SCANCODE_SPACE] && touching) {
        dy = jumpForce;
        touching = false;
    }

    dy += gravity * dt;

    if (dy > terminalVelocity)
        dy = terminalVelocity;

    float oldY = y;
    y += dy * dt;

    touching = false;

    for (auto &block : blocks) {

        if (collision(split(), block)) {

            if (dy > 0) {
                y = block[1] - size;
                touching = true;
            }
            else if (dy < 0) {
                y = block[1] + block[3];
            }

            dy = 0;
            break;
        }
    }

    if (y > 1000)
        return true;

    return false;
}

Player player;