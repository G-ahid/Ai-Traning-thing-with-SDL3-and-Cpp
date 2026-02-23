#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"
mkdir -p bin

total_start=$(date +%s)

echo "----------------------------"
echo "Compiling the game [1/3]"
start=$(date +%s)
cd game/
./game.compile.sh
mv game.x86_64 ../bin/

end=$(date +%s)
echo "Compliled in $((end - start))s"
echo "----------------------------"

echo "Compiling the AI view [2/3]"
start=$(date +%s)
cd ../ai
./AiView.compile.sh
mv AiView.x86_64 ../bin/

end=$(date +%s)
echo "Compliled in $((end - start))s"
echo "----------------------------"

echo "Compiling the AI training program [3/3]"

start=$(date +%s)

./ai.compile.sh
mv ai.x86_64 ../bin/


end=$(date +%s)
echo "Compliled in $((end - start))s"
echo "----------------------------"


total_end=$(date +%s)

echo "Full build completed in $((total_end - total_start))s"
echo "============================"