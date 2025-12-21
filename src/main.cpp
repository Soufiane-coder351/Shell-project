#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  std::cout << "$ ";

  std::string userCommand;
  std::getline(std::cin, userCommand);
  std::cout << userCommand << std::endl;

  std::cout << userCommand << ": command not found" << std::endl;
}
