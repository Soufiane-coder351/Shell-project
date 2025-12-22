#include <iostream>
#include <string>
#include <utility>
#include <unordered_set>
#include <vector>
#include <filesystem>
#include <unistd.h>   // for access()


namespace fs = std::filesystem;


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

std::vector<std::string> splitPATH(){
    std::vector<std::string> dirs;
    std::string path = std::getenv("PATH") ? std::getenv("PATH") : "";

    size_t start = 0;

    while(true){
        size_t pos = path.find(':', start);
        if(pos == std::string::npos){
            dirs.push_back(path.substr(start));
            break;
        }
        dirs.push_back(path.substr(start, pos-start));
        start = pos+1;
    }
    return dirs;
}

std::string inPATH(std::string rest)
{
    std::vector<std::string> dirs = splitPATH();
    for(auto dir: dirs){
        if(dir.empty()) continue;
        fs::path p = fs::path(dir) / rest;
        if(fs::exists(p) && fs::is_regular_file(p) && access(p.string().c_str(), X_OK) == 0){
            return p.string();
        }
    }
    return "none";
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
                std::cout << rest << " is a shell builtin\n";
            }
            else if(inPATH(rest) != "none"){
                std::cout << rest << " is " << inPATH(rest) << std::endl;
            }
            else{
                std::cout << rest << ": not found\n";
            }

        } else{
            std::cout << userCommand << ": command not found" << std::endl;
        }
        std::cout << "$ ";
    }
}
