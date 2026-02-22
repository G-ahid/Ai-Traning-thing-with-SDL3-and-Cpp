#pragma once
#include <array>
#include <random>

static std::mt19937 rng(std::random_device{}());

// Declare collision function (defined in lib.cpp)
bool collision(const std::array<int,4>& p, const std::array<int,4>& b);
int randomInt(int min, int max);