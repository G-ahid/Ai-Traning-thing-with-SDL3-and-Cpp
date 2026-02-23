#include "ai.hpp"
#include "../../game/src/lib.hpp"
#include "simulation.hpp"
#include "child.hpp"
#include <vector>
#include <cstddef>

AI::AI(size_t numchildren,
       size_t moves,
       size_t mutations,
       size_t winners)
{
    NumberOfChildren = numchildren;
    NumberOfMoves = moves;
    NumberOfMutations = mutations;
    NumberOfWinner = winners;

    children.reserve(NumberOfChildren);

    for (size_t i = 0; i < NumberOfChildren; i++) {
        children.emplace_back(NumberOfMoves, NumberOfMutations);
    }
}

void AI::init() {
    // Initialize the childen
    for (size_t i = 0; i < children.size() ; i++) {
        children[i].init();
    }
}
std::vector<Child> AI::evolve() {
    // Giving each Child a score
    for (size_t i = 0; i < children.size() ; i++) {
        children[i].fitness = evaluateChild(children[i]);
    }

    // Choosing the top 3
    std::vector<Child> winners;
    winners.reserve(3);
    for (int i = 0; i < 3; i++) {

        int index = 0;
        Child* winner = &children[0];

        for (size_t j = 1; j < children.size(); j++) {

            if (children[j].fitness > winner->fitness) {
                winner = &children[j];
                index = j;
            }
        }

        winners.push_back(*winner);

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