#include "lib.h"

bool collision(const std::array<int,4>& p, const std::array<int,4>& b) {
    return (
        p[0] < b[0] + b[2] &&  // p.left < b.right
        p[0] + p[2] > b[0] &&  // p.right > b.left
        p[1] < b[1] + b[3] &&  // p.top < b.bottom
        p[1] + p[3] > b[1]     // p.bottom > b.top
    );
}