#include <iostream>
#include <string>
#include <utility>
#include <unordered_set>

std::pair<std::string, std::string> splitFirstWord(std::string s){
    std::string firstWord, rest;
    // get the first word
    size_t i = 0;
    while (s[i] == ' ') i++;
    while (i < s.length() && s[i] != ' ') {
        firstWord += s[i];
        i++;
    }
    // get the rest
    i++;
    while (i < s.size()) {
        rest += s[i];
        i++;
    }

    return {firstWord, rest};
}



int main()
{
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // TODO: Uncomment the code below to pass the first stage
    std::cout << "$ ";
    while (true)
    {

        std::string userCommand;
        std::getline(std::cin, userCommand);

        if (userCommand == "exit") break;

        auto [firstWord, rest] = splitFirstWord(userCommand);

        if (firstWord == "echo") {
            std::cout << rest << "\n";
        }else if(firstWord == "type"){
            std::unordered_set<std::string> knownCommands = {"echo", "exit", "type"};
            if(knownCommands.count(rest)){
                std::cout << firstWord << " is a shell builtin\n";
            }else{
                std::cout << rest << ": not found\n";
            }

        } else{
            std::cout << userCommand << ": command not found" << std::endl;
        }
        std::cout << "$ ";
    }
}
