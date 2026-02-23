#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

class Child {
    public:
        float fitness = 0.f;
        std::vector<uint8_t> moves;
        
        Child(size_t numberOfMoves, size_t defaultMutations);
        void init();
        void mutate(int numberOfMutations = -1);

    private:
        size_t DefaultMutations;
};