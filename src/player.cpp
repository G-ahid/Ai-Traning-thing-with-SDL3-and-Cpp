#include "player.h"

std::array<int,4> Player::split(){
    // Used for collision
    return {(int)x,(int)y,(int)size,(int)size};
}

bool Player::update(double dt, bool left, bool right, bool jump) {

    if (dt > 0.05) dt = 0.05;
    float oldX = x;

    if (left)
        x -= speed * dt;

    if (right)
        x += speed * dt;

    for (auto &block : blocks) {
        if (collision(split(), block)) {
            x = oldX;
            break;
        }
    }

    if (jump && touching) {
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
