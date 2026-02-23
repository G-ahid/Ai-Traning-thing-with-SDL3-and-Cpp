#!/usr/bin/env bash
g++ -std=c++20 -Wall -Wextra AiView.cpp ../game/src/*.cpp -o AiView.x86_64 $(pkg-config --cflags --libs sdl3)