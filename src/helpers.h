#pragma once
#include <string>
#include <vector>
#include <utility>

std::pair<std::string, std::string> splitFirstWord(std::string s);
std::vector<std::string> splitPATH();
std::string inPATH(const std::string &rest);
