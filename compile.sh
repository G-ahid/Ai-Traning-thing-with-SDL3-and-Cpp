#!/usr/bin/env bash
set -e

total_start=$(date +%s)

echo "----------------------------"
echo "Compiling the game [1/3]"
start=$(date +%s)

./compile.sh

end=$(date +%s)
echo "Compliled in $((end - start))s"
echo "----------------------------"

echo "Compiling the AI view [2/3]"
start=$(date +%s)

./_AiView_.compile.sh

end=$(date +%s)
echo "Compliled in $((end - start))s"
echo "----------------------------"

mkdir -p bin
mv game.x86_64 bin/
mv AiView.x86_64 bin/

echo "Compiling the AI training program [3/3]"
cd src/ai/

start=$(date +%s)

./compile.sh

end=$(date +%s)
echo "Compliled in $((end - start))s"
echo "----------------------------"

mv ai.x86_64 ../../bin/

total_end=$(date +%s)

echo "Full build completed in $((total_end - total_start))s"
echo "============================"