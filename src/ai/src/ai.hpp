#include "simulation.hpp"
#include <array>

class AI {
    std::array<Child, 30> children;

    public:
        void init();
        std::array<Child, 30> evolve();
};