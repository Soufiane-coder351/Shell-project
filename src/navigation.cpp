#include "navigation.h"
#include <iostream>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

void handlePwd() {
    std::string cwd = fs::current_path().string();
    std::cout << cwd << std::endl;
}

void handleCd(const std::string& rest) {
    if (rest.empty()) return;
    if (rest[0] == '/') {
        if (!fs::exists(rest) || !fs::is_directory(rest)) {
            std::cout << "cd: " << rest << ": No such file or directory" << std::endl;
        } else {
            fs::current_path(rest);
        }
    } else if (rest[0] == '~') {
        std::string home = std::getenv("HOME");
        fs::current_path(home);
    } else {
        fs::path cwd = fs::current_path();
        fs::path newPath = cwd / rest;
        if (!fs::exists(newPath) || !fs::is_directory(newPath)) {
            std::cout << "cd: " << rest << ": No such file or directory" << std::endl;
        } else {
            fs::current_path(newPath);
        }
    }
}
