//ai.cpp
#include "ai.h"
#include <array>

void AI::init() {
    // Initialize the childen
    for (size_t i = 0; i < children.size() ; i++) {
        children[i].init();
    }
}
std::array<Child, 30> AI::evolve() {
    // Giving each Child a score
    for (size_t i = 0; i < children.size() ; i++) {
        children[i].fitness = evaluateChild(children[i]);
    }

    // Choosing the top 3
    Child winners[3];
    for (int i = 0; i < 3; i++) {

        int index = 0;
        Child* winner = &children[0];

        for (int j = 1; j < 30; j++) {

            if (children[j].fitness > winner->fitness) {
                winner = &children[j];
                index = j;
            }
        }

        winners[i] = *winner;

        // Removing winner from future selection
        children[index].fitness = -1e9;
    }

    // Making new babies(reproduction)
    for (size_t i = 0; i < children.size(); i++) {
        // Skip elite children 
        if (i < 3) continue;

        // Pick random parent from winners
        int parentIndex = randomInt(0, 2);

        children[i] = winners[parentIndex];

        // Mutate baby slightly
        children[i].mutate(1);
    }
    return children;
}