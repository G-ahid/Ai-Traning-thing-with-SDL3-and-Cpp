#include "child.hpp"
#include "../../lib.hpp"

void Child::init() {
    for (auto i = 0; i < Child::moves.size(); i++) {
        moves[i] = randomInt(1,3);
    }
}

void Child::mutate(int NumberMutations) {
    for(int i = 0; i < NumberMutations;i++) {
        moves[randomInt(0, moves.size()-1)] =randomInt(1, 3);
    }
} 