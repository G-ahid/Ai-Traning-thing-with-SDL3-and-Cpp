// ai.h
#include "simulation.h"
#include <array>
#include <cstddef>

class AI {
    std::array<Child, 30> children;

    public:
        void init();
        std::array<Child, 30> evolve();
};