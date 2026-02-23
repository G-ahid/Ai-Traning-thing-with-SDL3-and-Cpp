#include "child.hpp"
#include <vector>

class AI {
    public:
        AI(size_t numchildren, size_t moves, size_t mutations, size_t winners);
        void init();
        std::vector<Child> evolve();

    private:
        size_t NumberOfMoves;
        size_t NumberOfMutations;
        size_t NumberOfChildren;
        size_t NumberOfWinner;

        std::vector<Child> children;
};