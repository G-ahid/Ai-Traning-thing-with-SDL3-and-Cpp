#include "simulation.hpp"
#include "../../game/src/player.hpp"

float evaluateChild(const Child& child) {
    float score = 10.0f;
    //1. Make a copy of the player
    Player player;
    //2. Go through child.moves one by one
    float last_x = 0;
    for (size_t i = 0; i < child.moves.size(); i++) {
        // if he dies
        if (player.update(0.016, child.moves[i] == 1,child.moves[i] == 2, child.moves[i] == 3)) {
            return score /* - 1000*/;
        }
        if (last_x < player.x) {
            score += 500;
        } else {
            score -= 50;
        }

        last_x = player.x;
        score -= i * 50;
    }
    
    return score;
}
