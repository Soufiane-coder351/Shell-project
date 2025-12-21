#include <iostream>
#include <string>

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

        // get the first word
        size_t i = 0;
        while (userCommand[i] == ' ') i++;
        std::string firstWord = "";
        while (i < userCommand.length() && userCommand[i] != ' ') {
            firstWord += userCommand[i];
            i++;
        }
        // get the rest
        std::string rest;
        i++;
        while (i < userCommand.size()) {
            rest += userCommand[i];
            i++;
        }

        if (firstWord == "echo") {
            std::cout << rest << "\n";
        } else{
            std::cout << userCommand << ": command not found" << std::endl;
        }
        std::cout << "$ ";
    }
}
