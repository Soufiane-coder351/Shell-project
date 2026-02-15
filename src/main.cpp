#include <iostream>
#include <string>
#include <unordered_set>
#include "helpers.h"
#include "commands.h"
#include "navigation.h"

int main()
{
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    const std::unordered_set<std::string> knownCommands = {"echo", "exit", "type", "pwd", "cd"};

    std::cout << "$ ";
    std::string userCommand;
    while (std::getline(std::cin, userCommand))
    {
        auto [firstWord, rest] = splitFirstWord(userCommand);

        if (firstWord == "exit")
            break;

        if (firstWord == "echo") {
            handleEcho(rest);
        } else if (firstWord == "type") {
            handleType(rest, knownCommands);
        } else if (firstWord == "pwd") {
            handlePwd();
        } else if (firstWord == "cd") {
            handleCd(rest);
        } else {
            if (!tryRunExecutable(userCommand, firstWord)) {
                std::cout << userCommand << ": command not found" << std::endl;
            }
        }
        std::cout << "$ ";
    }
}
