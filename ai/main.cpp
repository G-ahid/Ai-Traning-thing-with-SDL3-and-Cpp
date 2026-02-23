#include <fstream>
#include <iostream>
#include <string>

#include "src/ai.hpp"


int main() {
    double Generations;
    std::cout << "Input how many Generations do you want to simulate : ";
    std::cin >> Generations;
    
    // initializing a new AI system
    AI mainAI;
    mainAI.init();
    // Evolving it
    for (int i = 0; i < Generations - 1; i++) {
        mainAI.evolve();
    }

    std::array<Child, 30> result = mainAI.evolve();
    // Saving the Result
    std::ofstream save("result.data");
    for (int i = 0; i < 30; i++) {
        std::string line;
        line += std::to_string(result[i].fitness);
        line += " | {";
        int moves = result[i].moves.size();
        for (int j = 0; j < moves; j++) {
            line += std::to_string((int)result[i].moves[j]);
            if (j != moves-1)
                line += " , ";
        }
        line += "}";

        save << line << std::endl;
    }

    return 0;

}
