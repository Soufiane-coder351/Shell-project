#pragma once
#include <string>
#include <unordered_set>

void handleEcho(const std::string& rest);
void handleType(const std::string& rest, const std::unordered_set<std::string>& knownCommands);
bool tryRunExecutable(const std::string& userCommand, const std::string& firstWord);
