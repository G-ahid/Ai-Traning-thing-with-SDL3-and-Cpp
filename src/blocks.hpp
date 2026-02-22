#pragma once

#include <array>
#include <vector>

// Declare generator function
std::vector<std::array<int,4>> genBlocks();

// Declare global block container (defined in blocks.cpp)
extern std::vector<std::array<int,4>> blocks;