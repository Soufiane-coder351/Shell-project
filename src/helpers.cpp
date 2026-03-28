#include "helpers.h"
#include <cstdlib>
#include <filesystem>
#include <unistd.h>

namespace fs = std::filesystem;

std::vector<std::string> tokenizeCommandLine(const std::string& input)
{
    std::vector<std::string> words;
    std::string word;
    bool inSingleQuote = false;
    bool inDoubleQuote = false;

    for (size_t i = 0; i < input.size(); ++i)
    {
        char c = input[i];

        if (c == '\\' && !inSingleQuote && !inDoubleQuote)
        {
            if (i + 1 < input.size())
            {
                word += input[++i];
            }
            continue;
        }

        if (c == '\\' && inDoubleQuote)
        {
            if (input[i + 1] == '\"' || input[i + 1] == '\\')
            {
                word += input[++i];
                continue;
            }
        }

        if (c == '"' && !inSingleQuote)
        {
            inDoubleQuote = !inDoubleQuote;
            continue;
        }

        if (c == '\'' && !inDoubleQuote)
        {
            inSingleQuote = !inSingleQuote;
            continue;
        }

        if ((c == ' ' || c == '\t') && !inSingleQuote && !inDoubleQuote)
        {
            if (!word.empty())
            {
                words.push_back(word);
                word.clear();
            }
            continue;
        }

        word += c;
    }

    if (!word.empty())
    {
        words.push_back(word);
    }

    return words;
}

std::pair<std::string, std::string> splitFirstWord(std::string s)
{
    std::vector<std::string> words = tokenizeCommandLine(s);
    if (words.empty())
    {
        return {"", ""};
    }

    std::string firstWord = words[0];
    std::string rest;
    for (size_t i = 1; i < words.size(); ++i)
    {
        if (i > 1)
        {
            rest += ' ';
        }
        rest += words[i];
    }

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
