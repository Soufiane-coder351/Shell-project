#include "commands.h"
#include "helpers.h"
#include <iostream>
#include <cstdlib>

void handleEcho(const std::string& rest) {
    std::string output = rest;
    // Remove surrounding single or double quotes if present
    if ((output.size() >= 2) &&
        ((output.front() == '\'' && output.back() == '\'') ||
         (output.front() == '"' && output.back() == '"'))) {
        output = output.substr(1, output.size() - 2);
    }
    std::cout << output << "\n";
}

void handleType(const std::string& rest, const std::unordered_set<std::string>& knownCommands) {
    if (knownCommands.count(rest)) {
        std::cout << rest << " is a shell builtin\n";
    } else {
        std::string pathResult = inPATH(rest);
        if (!pathResult.empty()) {
            std::cout << rest << " is " << pathResult << std::endl;
        } else {
            std::cout << rest << ": not found\n";
        }
    }
}

bool tryRunExecutable(const std::string& userCommand, const std::string& firstWord) {
    std::string pathResult = inPATH(firstWord);
    if (!pathResult.empty()) {
        int ret = system(userCommand.c_str());
        (void)ret;
        return true;
    }
    return false;
}
