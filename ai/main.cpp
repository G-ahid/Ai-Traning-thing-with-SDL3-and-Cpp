#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "src/ai.hpp"

int main() {
    std::unique_ptr<AI> mainAI;
    // Loading the json
    std::ifstream configFile("config.json");
    if (!configFile.is_open()) {
        std::cout << "No config file found, making config.json...\n";
        json defaultConfig;

        defaultConfig["NumberOfChildren"]  = 30;
        defaultConfig["NumberOfMoves"]     = 36000;
        defaultConfig["NumberOfMutations"] = 100;
        defaultConfig["NumberOfWinner"]    = 3;

        std::ofstream out("config.json");
        out << defaultConfig.dump(4);

        std::cout << "Config file created. Restart the program.\n";
        return 0;

    } else {
        // initializing a new AI system with config.json
        json config;
        configFile >> config;
        int NumberOfChildren  = config.value("NumberOfChildren", 30);
        int NumberOfMoves     = config.value("NumberOfMoves", 36000);
        int NumberOfMutations = config.value("NumberOfMutations", 100);
        int NumberOfWinners   = config.value("NumberOfWinners", 3);

        mainAI = std::make_unique<AI>(
            NumberOfChildren,
            NumberOfMoves,
            NumberOfMutations,
            NumberOfWinners
        );
    }
    mainAI->init();

    // Getting Inputs
    std::string savename;
    std::string RawGenerations;
    std::cout << "Input how many Generations do you want to simulate : ";
    std::getline(std::cin, RawGenerations);
    double Generations = std::stoi(RawGenerations);
    
    std::cout << "Enter save file name(empty -> 'result') : ";
    std::getline(std::cin, savename);
    if (savename.empty()) {
        savename = "result";
    }

    // Evolving it
    for (int i = 0; i < Generations; i++) {
        mainAI->evolve();
    }

    auto result = mainAI->evolve();
    // Saving the Result
    std::ofstream save(savename + ".aig");
    for (size_t i = 0; i < result.size() ; i++) {
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
