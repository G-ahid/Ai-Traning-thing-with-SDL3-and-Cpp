#!/usr/bin/env bash
g++ -std=c++20 main.cpp src/*.cpp -o game.x86_64 $(pkg-config --cflags --libs sdl3)