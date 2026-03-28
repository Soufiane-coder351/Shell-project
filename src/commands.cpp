#include "commands.h"
#include "helpers.h"
#include <iostream>
#include <cstdlib>

void handleEcho(const std::string& rest) {
    std::vector<std::string> words;
    std::string word;
    bool inSingleQuote = false;
    bool inDoubleQuote = false;

    for (size_t i = 0; i < rest.size(); ++i) {
        char c = rest[i];

        // Handle backslash escaping outside quotes
        if (c == '\\' && !inSingleQuote && !inDoubleQuote) {
            if (i + 1 < rest.size()) {
                word += rest[++i];
            }
            continue;
        }

        if(c == '\\' && inDoubleQuote){
            if(rest[i+1] == '\"' || rest[i+1] == '\\'){
                word += rest[++i];
                continue;
            }
        }

        // Toggle double quotes (ignored inside single quotes)
        if (c == '"' && !inSingleQuote) {
            inDoubleQuote = !inDoubleQuote;
            continue;
        }

        // Toggle single quotes (ignored inside double quotes)
        if (c == '\'' && !inDoubleQuote) {
            inSingleQuote = !inSingleQuote;
            continue;
        }

        // Whitespace delimits words outside quotes
        if ((c == ' ' || c == '\t') && !inSingleQuote && !inDoubleQuote) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
            continue;
        }

        word += c;
    }

    if (!word.empty()) {
        words.push_back(word);
    }

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
