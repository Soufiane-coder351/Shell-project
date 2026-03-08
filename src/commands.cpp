#include "commands.h"
#include "helpers.h"
#include <iostream>
#include <cstdlib>

void handleEcho(const std::string& rest) {
    std::vector<std::string> words;
    std::string word;
    size_t i = 0;
    bool inSingleQuote = false;
    bool inDoubleQuote = false;

    while (i < rest.size()) {
        // Toggle double quote (only outside single quotes)
        if (rest[i] == '"' && !inSingleQuote) {
            if(i > 0 && rest[i-1] == '\\') continue;
            inDoubleQuote = !inDoubleQuote;
            ++i;
            continue;
        }
        // Toggle single quote (only outside double quotes)
        if (rest[i] == '\'' && !inDoubleQuote) {
            if(i > 0 && rest[i-1] == '\\') continue;
            inSingleQuote = !inSingleQuote;
            ++i;
            continue;
        }
        // Whitespace is a delimiter only outside all quotes
        if (!inSingleQuote && !inDoubleQuote && !(i > 0 && rest[i-1] == '\\') && (rest[i] == ' ' || rest[i] == '\t')) {
            if (!word.empty()){

                words.push_back(word);
                word.clear();
            }
            // Skip consecutive spaces outside quotes
            while (i < rest.size() && (rest[i] == ' ' || rest[i] == '\t')) i++;
            continue;
        }
        if(!inSingleQuote && !inDoubleQuote && rest[i] == '\\'){
            ++i;
            continue;
        }
        word += rest[i++];
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    // Print words separated by a single space
    for (size_t j = 0; j < words.size(); ++j) {
        if (j > 0) std::cout << " ";
        std::cout << words[j];
    }
    std::cout << "\n";
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
