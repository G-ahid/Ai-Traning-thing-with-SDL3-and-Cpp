#include "child.hpp"
#include "../../game/src/lib.hpp"

Child::Child(size_t numberOfMoves, size_t defaultMutations):moves(numberOfMoves),DefaultMutations(defaultMutations){}

void Child::init() {
    for (size_t i = 0; i < moves.size(); i++) {
        moves[i] = randomInt(1, 3);
    }
}

void Child::mutate(int numberOfMutations) {
    if (numberOfMutations == -1) {
        numberOfMutations = DefaultMutations;
    }

    for (int i = 0; i < numberOfMutations; i++) {
        moves[randomInt(0, moves.size() - 1)] = randomInt(1, 3);
    }
}