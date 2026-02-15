#include "commands.h"
#include "helpers.h"
#include <iostream>
#include <cstdlib>

void handleEcho(const std::string& rest) {
    std::string result;
    size_t i = 0;
    while (i < rest.size()) {
        // Skip leading spaces outside quotes
        while (i < rest.size() && rest[i] == ' ') ++i;
        if (i >= rest.size()) break;

        if (rest[i] == '\'') {
            // Inside single quotes: take everything literally until next quote
            ++i;
            while (i < rest.size() && rest[i] != '\'') {
                result += rest[i++];
            }
            if (i < rest.size() && rest[i] == '\'') ++i; // skip closing quote
        } else {
            // Outside quotes: take until next space or quote
            while (i < rest.size() && rest[i] != ' ' && rest[i] != '\'') {
                result += rest[i++];
            }
        }
    }
    std::cout << result << "\n";
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
