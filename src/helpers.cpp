#include "helpers.h"
#include <cstdlib>
#include <filesystem>
#include <unistd.h>

namespace fs = std::filesystem;

std::pair<std::string, std::string> splitFirstWord(std::string s)
{
    std::string firstWord, rest;
    size_t i = 0;
    const size_t n = s.size();

    // Skip leading spaces
    while (i < n && s[i] == ' ') i++;

    if (i >= n) return {"", ""};

    // Quoted first token: '...' or "..."
    if (s[i] == '\'' || s[i] == '"')
    {
        char quoteChar = s[i++];
        while (i < n && s[i] != quoteChar)
        {
            firstWord += s[i++];
        }
        // Skip closing quote if found
        if (i < n && s[i] == quoteChar) i++;
    }
    else
    {
        // Unquoted first token
        while (i < n && s[i] != ' ')
        {
            firstWord += s[i++];
        }
    }

    // Skip spaces before rest
    while (i < n && s[i] == ' ') i++;

    // Remaining text
    if (i < n) rest = s.substr(i);

    return {firstWord, rest};
}

std::vector<std::string> splitPATH()
{
    std::vector<std::string> dirs;
    std::string path = std::getenv("PATH") ? std::getenv("PATH") : "";
    size_t start = 0;
    while (true)
    {
        size_t pos = path.find(':', start);
        if (pos == std::string::npos)
        {
            dirs.push_back(path.substr(start));
            break;
        }
        dirs.push_back(path.substr(start, pos - start));
        start = pos + 1;
    }
    return dirs;
}

std::string inPATH(const std::string &rest)
{
    std::vector<std::string> dirs = splitPATH();
    for (const auto &dir : dirs)
    {
        if (dir.empty())
            continue;
        fs::path p = fs::path(dir) / rest;
        if (fs::exists(p) && fs::is_regular_file(p) && access(p.string().c_str(), X_OK) == 0)
        {
            return p.string();
        }
    }
    return "";
}
