#!/usr/bin/env bash
echo "Compilying the game[1/3]"
./compile.sh
echo "Compilying the AI view[2/3]"
./_AiView_.compile.sh
mkdir -p bin
mv game.x86_64 bin/
mv AiView.x86_64 bin/
cd src/ai/
echo "Compilying the AI traning program[3/3]"
./compile.sh
mv ai.x86_64 ../../bin/
echo "Done compilying"