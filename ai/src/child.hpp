#include <cstdint>
#include <array>


struct Child {
    // their score
    float fitness;
    // a minute of moves
    std::array<uint8_t, 36000> moves; 

    void init();
    void mutate(int NumberMutations = 100);
};