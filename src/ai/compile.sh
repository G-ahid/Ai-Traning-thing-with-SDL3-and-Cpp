#g++ -std=c++20 main.cpp src/*.cpp -o game $(pkg-config --cflags --libs sdl3)
g++ -std=c++20 -Wall -Wextra main.cpp src/*.cpp ../*.cpp -o ai $(pkg-config --cflags --libs sdl3)